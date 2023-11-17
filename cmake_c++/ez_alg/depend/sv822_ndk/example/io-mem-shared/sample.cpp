#include <stdio.h>
#include <VX/vx.h>
#include <vx_ext_amd.h>
#include <vx_log.h>
#include <net_api.h>
#include <sys/time.h>

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <string.h>

void RefineFileName(int len, char * fname)
{
	for (int n = 0; n < len; n++) {
		if (fname[n] == '/' || 
			fname[n] == '(' || 
			fname[n] == ')' ||
			fname[n] == ',' ||
			fname[n] == ' ' ||
			fname[n] == '[' ||
			fname[n] == ']' ||
			fname[n] == ':') 
		{
			fname[n] = '_';
		}
	}
}

struct Arg{
	vx_context context;
	vx_graph graph;
	std::string input_file;
	int loop_num;
	int thread_id;
};

void * RunGraph(void * arg)
{
	Arg * thread_arg = (Arg*)arg;
	vx_context context = thread_arg->context;
	vx_graph graph = thread_arg->graph;	

	std::vector<std::string> input_blobs_name;
	std::vector<vx_tensor> input_blobs_tensor;
	std::vector<std::string> output_blobs_name;
	std::vector<vx_tensor> output_blobs_tensor;

	//set input data
	GetNetInputBlob(graph, input_blobs_name, input_blobs_tensor);
	while (1) {
		char data_file[512];	
		sprintf(data_file, "%s", thread_arg->input_file.c_str());
		VX_LOG("tid: %d want to infer graph...\n", thread_arg->thread_id);
		vxLockInOutSharedMemory(graph);	
		VX_LOG("tid: %d running graph...\n", thread_arg->thread_id);
		vx_status status = ImportNetInputDataFromDataFile(graph, input_blobs_name[0], data_file);
		if (status != VX_SUCCESS) {
			VX_LOG("import data error.\n");
			return (void*)-1;
		}	

		ERROR_CHECK_STATUS(vxProcessGraph(graph));
		ERROR_CHECK_STATUS(vxFinish(context));

		GetNetOutputBlob(graph, output_blobs_name, output_blobs_tensor);
		for (int i = 0; i < output_blobs_name.size(); i++) {
			vx_size dims[4];
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensor.at(i), VX_TENSOR_DIMS, dims, sizeof(dims)));
			vx_size data_size;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensor.at(i), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));
			vx_int8 * data;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensor.at(i), VX_TENSOR_MEMORY_VIRT_ADDR, &data, sizeof(data)));	
			VX_LOG("No.%d: name: %s, dims: (%d, %d, %d, %d), data size: %d, virt: 0x%x\n", i, output_blobs_name.at(i).c_str(), dims[0], dims[1], dims[2], dims[3], data_size, data);
			char out_file[512];
			sprintf(out_file, "%s_%d.bin", output_blobs_name.at(i).c_str(), thread_arg->loop_num);
			thread_arg->loop_num++;
			RefineFileName(512, out_file);
			FILE * fin = fopen(out_file, "wb");
			fwrite(data, 1, data_size, fin);
			fclose(fin);
		}
		output_blobs_name.clear();
		output_blobs_tensor.clear();
		vxUnLockInOutSharedMemory(graph);
		VX_LOG("tid: %d finish graph...\n", thread_arg->thread_id);

		pthread_testcancel();
	}

	return (void*)0;
}

int main(int argc, char * argv[])
{
	int ret;
	vx_graph graph_1, graph_2;
	vx_int8 * net_1, * net_2;
	vx_int8 * blobs_1, * blobs_2;
	std::vector<vx_size> mem_size;
	std::vector<vx_size> virt_addr;
	std::vector<vx_size> phys_addr;
	
	//create context
	vx_context context = vxCreateContext();
	ERROR_CHECK_OBJECT(context);

	//load nn module
	ERROR_CHECK_STATUS(vxLoadKernels(context, "openvx-nn"));

	ERROR_CHECK_STATUS(LoadNetModel(context, "r18.ezb", true, &net_1));
	ERROR_CHECK_STATUS(LoadNetModel(context, "r18.bin", true, &blobs_1));
	ERROR_CHECK_STATUS(LoadNetModel(context, "mobilenet_v2_quantized.ezb", true, &net_2));
	ERROR_CHECK_STATUS(LoadNetModel(context, "mobilenet_v2_quantized.bin", true, &blobs_2));

	//create graph
	graph_1 = CreateNetGraph(context, (vx_uint32*)net_1, blobs_1, false, true);//, -1, -1);
	ERROR_CHECK_STATUS(vxVerifyGraph(graph_1));
	graph_2 = CreateNetGraph(context, (vx_uint32*)net_2, blobs_2, false, true);//, -1, -1);
	ERROR_CHECK_STATUS(vxVerifyGraph(graph_2));	
	
	//config io shared memory
	vxDeviceMemoryInfo(context, mem_size, virt_addr, phys_addr);
	for (int i = 0; i < mem_size.size(); i++) {
		VX_LOG("context mem: virt: 0x%x, phys: 0x%x, size: %d\n", virt_addr[i], phys_addr[i], mem_size[i]);
	}
	vx_size io_mem_size_1 = vxGetGraphInOutMemorySize(graph_1);
	vx_size io_mem_size_2 = vxGetGraphInOutMemorySize(graph_2);
	vx_size io_shared_mem_size = io_mem_size_1 > io_mem_size_2 ? io_mem_size_1 : io_mem_size_2;
	vx_size io_shared_handle = vxAllocateDeviceMemory(context, io_shared_mem_size);
	VX_LOG("io_mem_size_1: %d, io_mem_size_2: %d, io_shared_mem_size: %d\n", io_mem_size_1, io_mem_size_2, io_shared_mem_size);
	vxConfigInOutSharedMemory(context, io_shared_handle);
	mem_size.clear();
	virt_addr.clear();
	phys_addr.clear();
	vxDeviceMemoryInfo(context, mem_size, virt_addr, phys_addr);
	for (int i = 0; i < mem_size.size(); i++) {
		VX_LOG("context mem: virt: 0x%x, phys: 0x%x, size: %d\n", virt_addr[i], phys_addr[i], mem_size[i]);
	}

	//thread
	Arg thread_1_arg = {context, graph_1, "orange_hw.bin", 0, 1};
	Arg thread_2_arg = {context, graph_2, "eagle_hw.bin",  0, 2};

	pthread_t thread_1;
	pthread_t thread_2;

	ret = pthread_create(&thread_1, nullptr, RunGraph, (void*)&thread_1_arg);
	if (ret != 0) {
		VX_LOG("create thread 1 error\n");
		exit(-1);
	}

	ret = pthread_create(&thread_2, nullptr, RunGraph, (void*)&thread_2_arg);
	if (ret != 0) {
		VX_LOG("create thread 2 error\n");
		exit(-1);
	}

	sleep(1);

	pthread_cancel(thread_1);
	pthread_cancel(thread_2);
	pthread_join(thread_1, nullptr);
	pthread_join(thread_2, nullptr);

	vxFreeDeviceMemory(context, io_shared_handle);
	ERROR_CHECK_STATUS(vxReleaseGraph(&graph_1));
	ERROR_CHECK_STATUS(vxReleaseGraph(&graph_2));
	ERROR_CHECK_STATUS(vxUnloadKernels(context, "openvx-nn"));
	ERROR_CHECK_STATUS(vxReleaseContext(&context));
	UnLoadNetModel(blobs_1);
	UnLoadNetModel(net_1);
	UnLoadNetModel(blobs_2);
	UnLoadNetModel(net_2);

	VX_LOG("********* SUCCESS! *************\n");
	
	return 0;
}
