#include <stdio.h>
#include <stdlib.h>
#include <VX/vx.h>
#include <vx_ext_amd.h>
#include <net_api.h>
#include <math.h>
#include <memory.h>
#include <vx_log.h>

#define LOAD_INPUT_FROM_FILE 
//#define ASYNC_PROCESS
//#define SUBGRAPH_PROCESS

int yuv_width = 960;
int yuv_height = 640;
char * y_data = "orange_y.bin";
char * uv_data = "orange_uv.bin";
char * nna_bgra_data = "orange_hw.bin";

int LoadInputYuvData(vx_context context, vx_graph graph, std::string & input_blob_name, vx_tensor & input_blob_tensor, int w, int h, img_fmt fmt, char * y_file, char * uv_file)
{
	FILE * fin;
	int flen;

	//malloc yuv buffer & load data
    vx_size src_handle = AllocDeviceImageBuffer(context, fmt, w, h);
    if (src_handle == 0) {
        VX_LOG("alloc yuv image buffer error.\n");
        return -1;
    }
    vx_size src_phys_addr = vxGetDeviceMemoryPhysicalAddress(src_handle);
	vx_size src_virt_addr = vxGetDeviceMemoryVirtualAddress(src_handle);

	fin = fopen(y_file, "rb");
	if (fin == NULL) {
		VX_LOG("open image file fail!\n");
		FreeDeviceImageBuffer(context, src_handle);
        return -1;
	}
	fseek(fin, 0, SEEK_END);
	flen = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	fread((vx_int8*)src_virt_addr, 1, flen, fin);
	fclose(fin);
    
	fin = fopen(uv_file, "rb");
	if (fin == NULL) {
		VX_LOG("open image file fail!\n");
		FreeDeviceImageBuffer(context, src_handle);
        return -1;
	}
	fseek(fin, 0, SEEK_END);
	flen = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	fread((vx_int8*)src_virt_addr + w * h, 1, flen, fin);
	fclose(fin);

	//flush cache
	vxFlushDeviceMemoryCache(context, src_handle);

	vx_size dims[4];
	ERROR_CHECK_STATUS(vxQueryTensor(input_blob_tensor, VX_TENSOR_DIMS, dims, sizeof(dims)));	

	//config input image
	input_image input_img;
	input_img.op = CVT;
	input_img.fmt = fmt;
	input_img.width = w;
	input_img.height = h;
	input_img.roi_in_x = 0;
	input_img.roi_in_y = 0;
	input_img.roi_in_w = w;
	input_img.roi_in_h = h;
	input_img.u.cvt_param.color_range = 0;
	input_img.phys_addr = src_phys_addr;
	input_img.phys_addr_uv = src_phys_addr + w * h;

	//import yuv to net
	vx_status status = ImportNetInputDataFromImage(graph, input_blob_name, &input_img);
	if (status != VX_SUCCESS) {
		VX_LOG("import data error.\n");
		FreeDeviceImageBuffer(context, src_handle);
		return -1;
	}
	FreeDeviceImageBuffer(context, src_handle);

	return 0;
}

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

int DumpBlobsInfo(std::vector<std::string> & blobs_name, std::vector<vx_tensor> & blobs_tensor)
{
	for (int i = 0; i < blobs_name.size(); i++) {
		vx_size dims[4];
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_DIMS, dims, sizeof(dims)));		
		vx_enum data_type;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_DATA_TYPE, &data_type, sizeof(data_type)));
		vx_size fixed_pos;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_FIXED_POINT_POSITION, &fixed_pos, sizeof(fixed_pos)));
		vx_size data_size;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));
		vx_size data_handle;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_HANDLE, &data_handle, sizeof(data_handle)));		
		vx_size data_virt_addr;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_VIRT_ADDR, &data_virt_addr, sizeof(data_virt_addr)));
		vx_size data_phys_addr;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_PHYS_ADDR, &data_phys_addr, sizeof(data_phys_addr)));
		
		VX_LOG("name: %s\n", blobs_name.at(i).c_str());
		VX_LOG("\t(w, h, c, b): (%d, %d, %d, %d)\n", dims[0], dims[1], dims[2], dims[3]);
		VX_LOG("\tdata type: %d\n", data_type);
		VX_LOG("\tfixed position: %d\n", fixed_pos);
		VX_LOG("\tdata size: %d\n", data_size);
		VX_LOG("\tdata handle: 0x%x\n", data_handle);
		VX_LOG("\tdata virt addr: 0x%x\n", data_virt_addr);
		VX_LOG("\tdata phys addr: 0x%x\n", data_phys_addr);
	}

	return 0;
}

int DumpBlobsData(std::vector<std::string> & blobs_name, std::vector<vx_tensor> & blobs_tensor)
{
	for (int i = 0; i < blobs_name.size(); i++) {
		vx_size dims[4];
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_DIMS, dims, sizeof(dims)));
		vx_size data_size;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));
		vx_int8 * data;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_VIRT_ADDR, &data, sizeof(data)));	
		VX_LOG("name: %s, dims: (%d, %d, %d, %d), data size: %d\n", blobs_name.at(i).c_str(), dims[0], dims[1], dims[2], dims[3], data_size);
		char out_file[512];
		sprintf(out_file, "%s.bin", blobs_name.at(i).c_str());
		RefineFileName(512, out_file);
		FILE * fin = fopen(out_file, "wb");
		fwrite(data, 1, data_size, fin);
		fclose(fin);
	}

	return 0;
}

int main()
{
	vx_int8 * net;
	vx_int8 * blobs;
	vx_status status;

	//create context
	vx_context context = vxCreateContext();
	ERROR_CHECK_OBJECT(context);
	
	//load nn module
	ERROR_CHECK_STATUS(vxLoadKernels(context, "openvx-nn"));

#if 1
	int freq;
	vxGetDeviceFreq(context, "nu", &freq);
	VX_LOG("-------- current npu freq: %d --------\n", freq);
	vxSetDeviceFreq(context, "nu", 750);
	vxGetDeviceFreq(context, "nu", &freq);
	VX_LOG("-------- updated npu freq: %d --------\n", freq);

  	int nu_timeout, vu_timeout; 
  	vxGetDeviceTimeOut(context, "nu", &nu_timeout);
  	vxGetDeviceTimeOut(context, "vu", &vu_timeout);
  	VX_LOG("nu_timeout(ms): %d, vu_timeout(ms): %d\n", nu_timeout, vu_timeout);
  	vxSetDeviceTimeOut(context, "nu", 6000);
  	vxSetDeviceTimeOut(context, "vu", 6000);
  	vxGetDeviceTimeOut(context, "nu", &nu_timeout);
  	vxGetDeviceTimeOut(context, "vu", &vu_timeout);
  	VX_LOG("nu_timeout(ms): %d, vu_timeout(ms): %d\n", nu_timeout, vu_timeout);
#endif
	
	//load model 
	LoadNetModel(context, "r18.ezb", true, &net);
	LoadNetModel(context, "r18.bin", true, &blobs);

	//create graph
	vx_graph graph = CreateNetGraph(context, (vx_uint32*)net, blobs, false, false, -1, -1);
	ERROR_CHECK_STATUS(vxVerifyGraph(graph));

	//unload model
	UnLoadNetModel(blobs);
	UnLoadNetModel(net);

	//get net input blob 
	std::vector<std::string> input_blobs_name;
	std::vector<vx_tensor> input_blobs_tensor;
	GetNetInputBlob(graph, input_blobs_name, input_blobs_tensor);
	VX_LOG("-------- input blobs: --------\n");
	DumpBlobsInfo(input_blobs_name, input_blobs_tensor);

	//get net output blob
	std::vector<std::string> output_blobs_name;
	std::vector<vx_tensor> output_blobs_tensor;
	GetNetOutputBlob(graph, output_blobs_name, output_blobs_tensor);
	VX_LOG("-------- output blobs: --------\n");
	DumpBlobsInfo(output_blobs_name, output_blobs_tensor);

	//get net intermediate blob 
	std::vector<std::string> intermediate_blobs_name;
	std::vector<vx_tensor> intermediate_blobs_tensor;
	GetNetIntermediateBlob(graph, intermediate_blobs_name, intermediate_blobs_tensor);
	VX_LOG("-------- intermediate blobs: --------\n");
	DumpBlobsInfo(intermediate_blobs_name, intermediate_blobs_tensor);
	
#ifdef LOAD_INPUT_FROM_FILE
	VX_LOG("-------- load input nna_bgra data --------\n");
	status = ImportNetInputDataFromDataFile(graph, input_blobs_name[0], nna_bgra_data);
	if (status != VX_SUCCESS) {
		VX_LOG("load input data error.\n");
		exit(-1);
	}
#else 
	VX_LOG("-------- load input yuv data --------\n");
	int ret = LoadInputYuvData(context, graph, input_blobs_name[0], input_blobs_tensor[0], yuv_width, yuv_height, YUV420_SP, y_data, uv_data);
	if (ret == -1) {
		exit(-1);
	}
#endif

	// profile net
	VX_LOG("-------- Profile Graph --------\n");
	ERROR_CHECK_STATUS(vxProfileGraph(graph));

	//process graph
	VX_LOG("-------- Process Graph --------\n");
#if defined SUBGRAPH_PROCESS
	int count = vxGetGraphLayerBlockCount(graph);
	VX_LOG("graph block count: %d\n", count);
	for (int idx = 0; idx < count; idx++) {
		vxProcessSubGraph(graph, idx, 1);
	}
#elif defined ASYNC_PROCESS
	ERROR_CHECK_STATUS(vxProcessGraph(graph));
	ERROR_CHECK_STATUS(vxFlush(context));
	vxWaitSync(context, graph);
#else
	ERROR_CHECK_STATUS(vxProcessGraph(graph));
	ERROR_CHECK_STATUS(vxFinish(context));
#endif
	
	//save data
	VX_LOG("------- dump blob data ---------\n");
#ifndef LOAD_INPUT_FROM_FILE
	vxInvalidateDeviceMemoryCacheAll(context);//ImportNetInputDataFromImage，硬件生成输入数据
#endif
	DumpBlobsData(input_blobs_name, input_blobs_tensor);
	DumpBlobsData(output_blobs_name, output_blobs_tensor);
	DumpBlobsData(intermediate_blobs_name, intermediate_blobs_tensor);

	//release
	VX_LOG("-------- release --------\n");
	ERROR_CHECK_STATUS(vxReleaseGraph(&graph));	
	ERROR_CHECK_STATUS(vxUnloadKernels(context, "openvx-nn"));
	ERROR_CHECK_STATUS(vxReleaseContext(&context));

	VX_LOG("-------- SUCCESS! --------\n");

    return 0;
}