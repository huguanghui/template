#include <stdio.h>
#include <stdlib.h>
#include <VX/vx.h>
#include <vx_ext_amd.h>
#include <net_api.h>
#include <math.h>
#include <memory.h>
#include <vx_log.h>

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

int main()
{
	vx_int8 * net;
	vx_int8 * blobs;

	//create context
	vx_context context = vxCreateContext();
	ERROR_CHECK_OBJECT(context);

	//load nn module
	ERROR_CHECK_STATUS(vxLoadKernels(context, "openvx-nn"));
	
	//load model 
	LoadNetModel(context, "r18.ezb", true, &net);
	LoadNetModel(context, "r18.bin", true, &blobs);

	//create graph
	vx_graph graph = CreateBatchNetGraph(context, (vx_uint32*)net, blobs, 2);
	ERROR_CHECK_STATUS(vxVerifyGraph(graph));

	//unload model
	UnLoadNetModel(blobs);
	UnLoadNetModel(net);

	//get net input blob 
	std::vector<std::string> input_blobs_name;
	std::vector<std::vector<vx_tensor>> input_blobs_tensors;
	GetBatchNetInputBlob(graph, input_blobs_name, input_blobs_tensors);
	VX_LOG("-------- input blobs: --------\n");
	for (int i = 0; i < input_blobs_name.size(); i++) {
		VX_LOG("name: %s\n", input_blobs_name.at(i).c_str());
		for (int j = 0; j < input_blobs_tensors.at(i).size(); j++) {
			vx_size dims[4];
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_DIMS, dims, sizeof(dims)));		
			vx_enum data_type;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_DATA_TYPE, &data_type, sizeof(data_type)));
			vx_size fixed_pos;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_FIXED_POINT_POSITION, &fixed_pos, sizeof(fixed_pos)));
			vx_size data_size;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));
			vx_size data_handle;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_HANDLE, &data_handle, sizeof(data_handle)));		
			vx_size data_virt_addr;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_VIRT_ADDR, &data_virt_addr, sizeof(data_virt_addr)));
			vx_size data_phys_addr;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_PHYS_ADDR, &data_phys_addr, sizeof(data_phys_addr)));
		
			VX_LOG("\t(w, h, c, b): (%d, %d, %d, %d)\n", dims[0], dims[1], dims[2], dims[3]);
			VX_LOG("\tdata type: %d\n", data_type);
			VX_LOG("\tfixed position: %d\n", fixed_pos);
			VX_LOG("\tdata size: %d\n", data_size);
			VX_LOG("\tdata handle: 0x%x\n", data_handle);
			VX_LOG("\tdata virt addr: 0x%x\n", data_virt_addr);
			VX_LOG("\tdata phys addr: 0x%x\n", data_phys_addr);
		}
	}

	//get net output blob
	std::vector<std::string> output_blobs_name;
	std::vector<std::vector<vx_tensor>> output_blobs_tensors;
	GetBatchNetOutputBlob(graph, output_blobs_name, output_blobs_tensors);
	VX_LOG("-------- output blobs: --------\n");
	for (int i = 0; i < output_blobs_name.size(); i++) {
		VX_LOG("name: %s\n", output_blobs_name.at(i).c_str());
		for (int j = 0; j < output_blobs_tensors.at(i).size(); j++) {
			vx_size dims[4];
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_DIMS, dims, sizeof(dims)));		
			vx_enum data_type;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_DATA_TYPE, &data_type, sizeof(data_type)));
			vx_size fixed_pos;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_FIXED_POINT_POSITION, &fixed_pos, sizeof(fixed_pos)));
			vx_size data_size;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));
			vx_size data_handle;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_HANDLE, &data_handle, sizeof(data_handle)));		
			vx_size data_virt_addr;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_VIRT_ADDR, &data_virt_addr, sizeof(data_virt_addr)));
			vx_size data_phys_addr;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_PHYS_ADDR, &data_phys_addr, sizeof(data_phys_addr)));
		
			VX_LOG("\t(w, h, c, b): (%d, %d, %d, %d)\n", dims[0], dims[1], dims[2], dims[3]);
			VX_LOG("\tdata type: %d\n", data_type);
			VX_LOG("\tfixed position: %d\n", fixed_pos);
			VX_LOG("\tdata size: %d\n", data_size);
			VX_LOG("\tdata handle: 0x%x\n", data_handle);
			VX_LOG("\tdata virt addr: 0x%x\n", data_virt_addr);
			VX_LOG("\tdata phys addr: 0x%x\n", data_phys_addr);
		}
	}

	//import yuv image data
	VX_LOG("-------- load input data --------\n");
	ImportNetInputDataFromDataFile(graph, input_blobs_name[0], "orange_hw.bin", 0);
	ImportNetInputDataFromDataFile(graph, input_blobs_name[0], "eagle_hw.bin", 1);

	// profile net
	VX_LOG("-------- Profile Graph --------\n");
	ERROR_CHECK_STATUS(vxProfileGraph(graph));

	//process graph
	VX_LOG("-------- Process Graph --------\n");
	vx_uint64 start = vxGetSysTime(); 
	ERROR_CHECK_STATUS(vxProcessGraph(graph));
	ERROR_CHECK_STATUS(vxFinish(context));
	vx_uint64 end = vxGetSysTime();
	VX_LOG("process graph time: %lld(ms)\n", end - start);

	//save data
	for (int i = 0; i < input_blobs_name.size(); i++) {
		for (int j = 0; j < input_blobs_tensors.at(i).size(); j++) {
			vx_size data_size;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));	
			vx_size data_virt_addr;
			ERROR_CHECK_STATUS(vxQueryTensor(input_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_VIRT_ADDR, &data_virt_addr, sizeof(data_virt_addr)));		
			//write
			char out_file[512];
			sprintf(out_file, "%s_%d.bin", input_blobs_name.at(i).c_str(), j);
			RefineFileName(512, out_file);
			FILE * fin = fopen(out_file, "wb");
			fwrite((void*)data_virt_addr, 1, data_size, fin);
			fclose(fin);
		}
	}

	for (int i = 0; i < output_blobs_name.size(); i++) {
		for (int j = 0; j < output_blobs_tensors.at(i).size(); j++) {
			vx_size data_size;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));		
			vx_size data_virt_addr;
			ERROR_CHECK_STATUS(vxQueryTensor(output_blobs_tensors.at(i).at(j), VX_TENSOR_MEMORY_VIRT_ADDR, &data_virt_addr, sizeof(data_virt_addr)));		
			//write
			char out_file[512];
			sprintf(out_file, "%s_%d.bin", output_blobs_name.at(i).c_str(), j);
			RefineFileName(512, out_file);
			FILE * fin = fopen(out_file, "wb");
			fwrite((void*)data_virt_addr, 1, data_size, fin);
			fclose(fin);
		}
	}

	//release
	VX_LOG("-------- release --------\n");
	ERROR_CHECK_STATUS(vxReleaseGraph(&graph));
	ERROR_CHECK_STATUS(vxUnloadKernels(context, "openvx-nn"));
	ERROR_CHECK_STATUS(vxReleaseContext(&context));
	
	VX_LOG("-------- SUCCESS! --------\n");

    return 0;
}