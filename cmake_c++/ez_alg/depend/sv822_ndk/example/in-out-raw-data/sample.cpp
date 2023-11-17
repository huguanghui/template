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
	vx_status status;

	//create context
	vx_context context = vxCreateContext();
	ERROR_CHECK_OBJECT(context);
	
	//load nn module
	ERROR_CHECK_STATUS(vxLoadKernels(context, "openvx-nn"));
	
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

	//get net output blob
	std::vector<std::string> output_blobs_name;
	std::vector<vx_tensor> output_blobs_tensor;
	GetNetOutputBlob(graph, output_blobs_name, output_blobs_tensor);
	
	//load input raw data
	FILE * fin = fopen("orange_float.bin", "rb");
	fseek(fin, 0, SEEK_END);
	int flen = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	uint8_t * data = (uint8_t*)malloc(flen);
	fread(data, 1, flen, fin);
	fclose(fin);

	net_blob_data blob;
	blob.n = 1;
	blob.c = 3;
	blob.h = 224;
	blob.w = 224;
	blob.data = data;
	blob.layout = NHWC;
	blob.type = DFLOAT32;
	blob.need_quantize = true;

	EnableNetInputDataExtPreprocess(graph, input_blobs_name[0]);
	status = ImportNetInputDataFromRawData(graph, input_blobs_name[0], blob);
	if (status != VX_SUCCESS) {
		VX_LOG("load input data error.\n");
		exit(-1);
	}
	free(data);

	// profile net
	VX_LOG("-------- Profile Graph --------\n");
	ERROR_CHECK_STATUS(vxProfileGraph(graph));

	//process graph
	VX_LOG("-------- Process Graph --------\n");
	ERROR_CHECK_STATUS(vxProcessGraph(graph));
	ERROR_CHECK_STATUS(vxFinish(context));	
	DisableNetInputDataExtPreprocess(graph, input_blobs_name[0]);
	
	//dump output raw data
	for (int i = 0; i < output_blobs_name.size(); i++) {
		net_blob_data blob;
		blob.layout = NCHW;
		blob.need_quantize = false;
		ExportNetOutputRawData(graph, output_blobs_name.at(i), blob);

		int element_size;
		if (blob.type == DINT8)
			element_size = 1;
		else if(blob.type == DINT16) 
			element_size = 2;
		else
			element_size = 4;
		int size = blob.n * blob.c * blob.h * blob.w * element_size;

		char out_file[512];
		sprintf(out_file, "%s_chw.bin", output_blobs_name.at(i).c_str());
		RefineFileName(512, out_file);	
		FILE * fin = fopen(out_file, "wb");
		fwrite(blob.data, 1, size, fin);
		fclose(fin);
	}
		
	//release
	VX_LOG("-------- release --------\n");
	ERROR_CHECK_STATUS(vxReleaseGraph(&graph));	
	ERROR_CHECK_STATUS(vxUnloadKernels(context, "openvx-nn"));
	ERROR_CHECK_STATUS(vxReleaseContext(&context));

	VX_LOG("-------- SUCCESS! --------\n");

    return 0;
}