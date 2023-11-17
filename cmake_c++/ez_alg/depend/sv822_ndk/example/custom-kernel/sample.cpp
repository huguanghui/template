#include <stdio.h>
#include <math.h>
#include <VX/vx.h>
#include <vx_ext_amd.h>
#include <vx_amd_nn.h>
#include <vx_log.h>
#include <net_api.h>

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


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

int DumpBlobsData(vx_graph graph, std::vector<std::string> & blobs_name, std::vector<vx_tensor> & blobs_tensor)
{
	for (int i = 0; i < blobs_name.size(); i++) {
		vx_size dims[4];
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_DIMS, dims, sizeof(dims)));
		vx_size data_size;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_SIZE, &data_size, sizeof(data_size)));
		vx_int8 * data;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_VIRT_ADDR, &data, sizeof(data)));	
		vx_size data_phys_addr;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_PHYS_ADDR, &data_phys_addr, sizeof(data_phys_addr)));	
		vx_size handle;
		ERROR_CHECK_STATUS(vxQueryTensor(blobs_tensor.at(i), VX_TENSOR_MEMORY_HANDLE, &handle, sizeof(handle)));
		VX_LOG("name: %s, dims: (%d, %d, %d, %d), data size: %d, virt: 0x%x, phys: 0x%x, handle: 0x%x\n", blobs_name.at(i).c_str(), dims[0], dims[1], dims[2], dims[3], data_size, data, data_phys_addr, handle);
		char out_file[512];
		sprintf(out_file, "%s.bin", blobs_name.at(i).c_str());
		RefineFileName(512, out_file);
		FILE * fin = fopen(out_file, "wb");
		fwrite(data, 1, data_size, fin);
		fclose(fin);
	}

	return 0;
}

vx_status RunGraph(vx_context context, vx_graph graph, char * running_dir, char * input_data_file)
{
	char curr_dir[512];
	vx_status status;	
	std::vector<std::string> input_blobs_name;
	std::vector<vx_tensor> input_blobs_tensor;
	std::vector<std::string> output_blobs_name;
	std::vector<vx_tensor> output_blobs_tensor;
	std::vector<std::string> intermediate_blobs_name;
	std::vector<vx_tensor> intermediate_blobs_tensor;

	getcwd(curr_dir, sizeof(curr_dir));
	if (access(running_dir, 0) != 0) {
		if (mkdir(running_dir, 0777) == -1) {
			VX_LOG("mkdir error!\n");
			return VX_FAILURE;
		}		
	}
	chdir(running_dir);

	// profile net
	ERROR_CHECK_STATUS(vxProfileGraph(graph));

	//set input data
	GetNetInputBlob(graph, input_blobs_name, input_blobs_tensor);	
	char data_file[512];
	sprintf(data_file, "../%s", input_data_file);	
	status = ImportNetInputDataFromDataFile(graph, input_blobs_name[0], data_file);
	if (status != VX_SUCCESS) {
		VX_LOG("import data error.\n");
		return VX_FAILURE;
	}
	
	ERROR_CHECK_STATUS(vxProcessGraph(graph));
	ERROR_CHECK_STATUS(vxFinish(context));

	//get output blobs
	GetNetOutputBlob(graph, output_blobs_name, output_blobs_tensor);
	DumpBlobsData(graph, output_blobs_name, output_blobs_tensor);
	GetNetIntermediateBlob(graph, intermediate_blobs_name, intermediate_blobs_tensor);
	DumpBlobsData(graph, intermediate_blobs_name, intermediate_blobs_tensor);

	VX_LOG("-------- finish running -----------\n");
	chdir(curr_dir);
	
	return VX_SUCCESS;
}

void axpy_layer(std::vector<vx_tensor>& input, std::vector<vx_float32>& params, std::vector<vx_tensor>& output)
{
	VX_LOG("^^^^^^^^^^^^^^^^^^^^^ axpy_layer ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	vx_size input_dims[4];
	ERROR_CHECK_STATUS(vxQueryTensor(input[0], VX_TENSOR_DIMS, input_dims, sizeof(input_dims)));
    int W = input_dims[0];
    int H = input_dims[1];
    int C = input_dims[2];
    int N = input_dims[3];
	int G = C / 16;	

	vx_size fl_in;
	ERROR_CHECK_STATUS(vxQueryTensor(input[0], VX_TENSOR_FIXED_POINT_POSITION, &fl_in, sizeof(fl_in)));

	vx_size input_data;
    ERROR_CHECK_STATUS(vxQueryTensor(input[0], VX_TENSOR_MEMORY_VIRT_ADDR, &input_data, sizeof(input_data)));
	int8_t* psrc = (int8_t*)input_data;

	vx_size fl_out;
	ERROR_CHECK_STATUS(vxQueryTensor(output[0], VX_TENSOR_FIXED_POINT_POSITION, &fl_out, sizeof(fl_out)));

	vx_size output_data;
    ERROR_CHECK_STATUS(vxQueryTensor(output[0], VX_TENSOR_MEMORY_VIRT_ADDR, &output_data, sizeof(output_data)));
	int8_t* pdst = (int8_t*)output_data;

	vx_size output_data_1;
    ERROR_CHECK_STATUS(vxQueryTensor(output[1], VX_TENSOR_MEMORY_VIRT_ADDR, &output_data_1, sizeof(output_data_1)));
	int8_t* pdst1 = (int8_t*)output_data_1;

	float alpha = params[0];
	float beta = params[1];
	float scale_in = 1.0f / pow(2, (float)fl_in);
	float scale_out = pow(2, (float)fl_out);
	for (int g = 0; g < G; g++) {
		int8_t* gdst = pdst + g*W*H * 16;
		int8_t* gsrc = psrc + g*W*H * 16;
		int8_t* gdst1 = pdst1 + g*W*H * 16;
		for (int w = 0; w < W; w++) {
			for (int h = 0; h < H; h++) {
				for (int c = 0; c < 16; c++) {
					float tmp = gsrc[w*H * 16 + h * 16 + c] * scale_in * alpha + beta;
					gdst[w*H * 16 + h * 16 + c] = round(tmp*scale_out);
					gdst1[w*H * 16 + h * 16 + c] = round(alpha*scale_out);
				}
			}
		}
	}
}

void const_layer(std::vector<vx_tensor>& input, std::vector<vx_float32>& params, std::vector<vx_tensor>& output)
{
	VX_LOG("^^^^^^^^^^^^^^^^^^^^^ const_layer ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	vx_size input_data;
    ERROR_CHECK_STATUS(vxQueryTensor(input[0], VX_TENSOR_MEMORY_VIRT_ADDR, &input_data, sizeof(input_data)));
	int8_t* psrc = (int8_t*)input_data;

	vx_size output_dims[4];
	ERROR_CHECK_STATUS(vxQueryTensor(output[0], VX_TENSOR_DIMS, output_dims, sizeof(output_dims)));
    int W = output_dims[0];
    int H = output_dims[1];
    int C = output_dims[2];
    int N = output_dims[3];
	int G = C / 16;
	vx_size output_data;
    ERROR_CHECK_STATUS(vxQueryTensor(output[0], VX_TENSOR_MEMORY_VIRT_ADDR, &output_data, sizeof(output_data)));
	int8_t* pdst = (int8_t*)output_data;
	vx_size fl_out;
	ERROR_CHECK_STATUS(vxQueryTensor(output[0], VX_TENSOR_FIXED_POINT_POSITION, &fl_out, sizeof(fl_out)));

	float alpha = params[4];
	float scale_out = pow(2, (float)fl_out);

	for (int g = 0; g < G; g++) {
		int8_t* gdst = pdst + g*W*H * 16;
		int8_t* gsrc = psrc + g*W*H * 16;
		for (int w = 0; w < W; w++) {
			for (int h = 0; h < H; h++) {
				for (int c = 0; c < 16; c++) {
					gdst[w*H * 16 + h * 16 + c] = round(alpha*scale_out);
				}
			}
		}
	}
}

int main(int argc, char * argv[])
{
	vx_graph graph;
	vx_int8 * net;
	vx_int8 * blobs;
	vx_uint64 start, end;
	
	//create context
	vx_context context = vxCreateContext();
	ERROR_CHECK_OBJECT(context);

	//load nn module
	ERROR_CHECK_STATUS(vxLoadKernels(context, "openvx-nn"));

	//register custom layer
	vxRegisterCustomLayerCallback(context, "AxPyLayer", axpy_layer);
	vxRegisterCustomLayerCallback(context, "ConstLayer", const_layer);

	ERROR_CHECK_STATUS(LoadNetModel(context, "gen_alpha.ezb", true, &net));
	ERROR_CHECK_STATUS(LoadNetModel(context, "gen_alpha.bin", true, &blobs));
	
	//create graph
	graph = CreateNetGraph(context, (vx_uint32*)net, blobs, false, false, -1, -1);		
	ERROR_CHECK_STATUS(vxVerifyGraph(graph));
	RunGraph(context, graph, "output", "data.bgr");
	ERROR_CHECK_STATUS(vxReleaseGraph(&graph));	

	vxUnRegisterCustomLayerCallBack(context, "AxPyLayer");
	vxUnRegisterCustomLayerCallBack(context, "ConstLayer");
	ERROR_CHECK_STATUS(vxUnloadKernels(context, "openvx-nn"));
	ERROR_CHECK_STATUS(vxReleaseContext(&context));
	UnLoadNetModel(blobs);
	UnLoadNetModel(net);

	VX_LOG("********* SUCCESS! *************\n");
	
	return 0;
}
