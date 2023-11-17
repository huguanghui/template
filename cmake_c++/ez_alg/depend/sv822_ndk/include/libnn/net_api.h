#ifndef _NET_API_H_
#define _NET_API_H_

#include <vector>
#include <VX/vx.h>
#include <vx_ext_amd.h>

typedef enum ImageFormat_E {
	YUV420_SP = 0x02,
	YVU420_SP = 0x04,
	NNA_BGRA  = 0x09,
	NNA_GRAY  = 0x07,
} img_fmt;

typedef enum ImageOperation_E {
	CVT  = 1001,
	WARP = 1002,
} img_op;

typedef enum ImageDataLayout_E {
	CHW = 2001,
	HWC = 2002,
	WHC = 2003,
} img_data_layout;

typedef struct ImageConvertParam_S {
	img_fmt input_fmt;
	int input_width;
	int input_height;
	int roi_in_x;
	int roi_in_y;
	int roi_in_w;
	int roi_in_h;
	int input_color_range;
	img_fmt output_fmt;
	int output_width;
	int output_height;
	int crop_out_x;
	int crop_out_y;
	int crop_out_w;
	int crop_out_h;
} img_cvt_param;

typedef struct MbgParam_S {
	int input_width;
	int input_height;
	int blk_width;
	int blk_height;
	int threshold_enable;
	int threshold;
	int alpha;
	int reset_flag;
	int mask_threshold;
} mbg_param;

typedef struct ImageWarpParam_S {
	img_fmt input_fmt;
	int input_width;
	int input_height;
	int roi_in_x;
	int roi_in_y;
	int roi_in_w;
	int roi_in_h;
	int roi_out_x;
	int roi_out_y;
	int roi_out_w;
	int roi_out_h;
	int output_width;
	int output_height;
	int flip;
	float mat[6];
} img_warp_param;

typedef struct ImageWarp3dParam_S {
	img_fmt input_fmt;
	int input_width;
	int input_height;
	int roi_out_x;
	int roi_out_y;
	int roi_out_w;
	int roi_out_h;
	int output_width;
	int output_height;
	int crop_out_x;
	int crop_out_y;
	int crop_out_w;
	int crop_out_h;
	int flip;
	int perspective_enable;
	float mat_r[9];
	float mat_m[9];
	float mat_dist[5];
} img_warp3d_param;

typedef struct InputImage_S {
	img_op op;
	img_fmt fmt;
	int width;
	int height; 
	int roi_in_x;
	int roi_in_y;
	int roi_in_w;
	int roi_in_h;
	union {
		struct {			
			int color_range;
		} cvt_param;
		struct {
			int flip;
			float mat[6];
		} warp_param;
	} u;		
	vx_size phys_addr;
	vx_size phys_addr_uv;	
} input_image;

typedef enum NetDataLayout_E {
	NCHW = 3001,
	NHWC = 3002,
	NWHC = 3003,
} net_data_layout;

typedef enum NetDataType_E {
	DINT8    = 4001,
	DINT16   = 4002,
	DFLOAT32 = 4003,
} net_data_type;

typedef struct NetBlobData_S {
	int n;
	int c;
	int h;
	int w;
	void* data;
	bool need_quantize;
	net_data_type type;
	net_data_layout layout;
} net_blob_data;

typedef struct RoiAlignParam_S {
	int input_width;
	int input_height;
	int input_channel;
	int crop_in_c_st;
	int crop_in_c_wd;
	float roi_in_start_w;
	float roi_in_end_w;
	float roi_in_start_h;
	float roi_in_end_h;
	int output_width;
	int output_height;
	int output_channel;
	int crop_out_x_st;
	int crop_out_y_st;
	int crop_out_c_st;
	int bit_width;
	int pooled_w;
	int pooled_h;
	int aligned;
	float spatial_ratio;
	float sampling_ratio;
} roi_align_param;

/*
 * network
 */
VX_API_ENTRY vx_graph VX_API_CALL CreateNetGraph(
	vx_context context,
	vx_uint32 * net_topo,
	vx_int8 * net_blobs,
	bool on_chip_mem_enable = false,
	bool io_mem_shared = false,
	int hold_block_idx = 0x7FFFFFFF,
	int up_to_block_count = -1);

VX_API_ENTRY vx_status VX_API_CALL GetNetInputBlob(
	vx_graph graph, 
	std::vector<std::string> & names, 
	std::vector<vx_tensor> & blobs);

VX_API_ENTRY vx_status VX_API_CALL GetNetOutputBlob(
	vx_graph graph,
	std::vector<std::string> & names,
	std::vector<vx_tensor> & blobs);

VX_API_ENTRY vx_status VX_API_CALL GetNetIntermediateBlob(
	vx_graph graph,
	std::vector<std::string>& names,
	std::vector<vx_tensor>& blobs);

VX_API_ENTRY vx_status VX_API_CALL GetNetBlobOriginDims(
	vx_graph graph,
	std::string& blob_name,
	std::vector<int>& dims);

/*
 * batch network
 */
VX_API_ENTRY vx_graph VX_API_CALL CreateBatchNetGraph(
	vx_context context,
	vx_uint32* net_topo,
	vx_int8* net_blobs,
	int batch,
	bool io_mem_shared = false);

VX_API_ENTRY vx_status VX_API_CALL GetBatchNetInputBlob(
	vx_graph graph,
	std::vector<std::string>& names,
	std::vector<std::vector<vx_tensor>>& blobs);

VX_API_ENTRY vx_status VX_API_CALL GetBatchNetOutputBlob(
	vx_graph graph,
	std::vector<std::string>& names,
	std::vector<std::vector<vx_tensor>>& blobs);

/*
 * roi align net
 */
VX_API_ENTRY vx_graph VX_API_CALL CreateRoiAlignNetGraph(
	vx_context context,
	vx_uint32* pool_net_topo,
	vx_int8* pool_net_blobs,
	vx_uint32* net_topo,
	vx_int8* net_blobs,
	int hold_block_idx = 0x7FFFFFFF,
	int up_to_block_count = -1);

VX_API_ENTRY vx_status VX_API_CALL ProcessRoiAlignGraph(
	vx_size input_handle,
	roi_align_param& param,
	vx_graph graph);

/*
 * config input buffer
 */
VX_API_ENTRY vx_status VX_API_CALL SetNetInputBuffer(
	vx_graph graph,
	std::string& blob_name,
	vx_size handle,
	int batch_idx = 0);

VX_API_ENTRY vx_status VX_API_CALL ResetNetDefaultInputBuffer(
	vx_graph graph,
	std::string& blob_name,
	int batch_idx = 0);

/*
 * import and export network data
 */
VX_API_ENTRY vx_status VX_API_CALL ImportNetInputDataFromImage(
	vx_graph graph,
	std::string& blob_name,
	input_image* image,
	int batch_idx = 0);

VX_API_ENTRY vx_status VX_API_CALL ImportNetInputDataFromMem(
	vx_graph graph, 
	std::string & blob_name, 
	int mem_data_len, 
	vx_uint8* mem_data, 
	int batch_idx = 0);

VX_API_ENTRY vx_status VX_API_CALL ImportNetInputDataFromDataFile(
	vx_graph graph,
	std::string& blob_name,
	char* fname,
	int batch_idx = 0);

VX_API_ENTRY vx_status VX_API_CALL EnableNetInputDataExtPreprocess(
	vx_graph graph,
	std::string& blob_name);

VX_API_ENTRY vx_status VX_API_CALL DisableNetInputDataExtPreprocess(
	vx_graph graph,
	std::string& blob_name);

VX_API_ENTRY vx_status VX_API_CALL ImportNetInputDataFromRawData(
	vx_graph graph,
	std::string& blob_name,
	net_blob_data& blob_data,
	int batch_idx = 0);

VX_API_ENTRY vx_status VX_API_CALL ExportNetOutputRawData(
	vx_graph graph,
	std::string& blob_name,
	net_blob_data& blob_data,
	int batch_idx = 0);

/*
 * image process
 */
VX_API_ENTRY vx_size VX_API_CALL AllocDeviceImageBuffer(
	vx_context context, 
	img_fmt fmt, 
	int width, 
	int height);

VX_API_ENTRY vx_size VX_API_CALL AllocDeviceMbgMaskImageBuffer(
	vx_context context, 
	int width, 
	int height, 
	int blk_width, 
	int blk_height);

VX_API_ENTRY vx_status VX_API_CALL FreeDeviceImageBuffer(
	vx_context context, 
	vx_size handle);

VX_API_ENTRY vx_status VX_API_CALL ImageConvert(
	vx_context context, 
	img_cvt_param * param, 
	vx_size input_phys_addr,
	vx_size input_phys_addr_uv,
	vx_size output_handle);

VX_API_ENTRY vx_status VX_API_CALL BackgroundModeling(
	vx_context context, 
	mbg_param * param, 
	vx_size input_phys_addr,
	vx_size input_phys_addr_bg,
	vx_size output_handle_bg,
	vx_size output_handle_mask);

VX_API_ENTRY vx_status VX_API_CALL ImageWarp(
	vx_context context, 
	img_warp_param * param, 
	vx_size input_phys_addr, 
	vx_size input_phys_addr_uv,
	vx_size output_handle);

VX_API_ENTRY vx_status VX_API_CALL ImageWarp3D(
	vx_context context,
	img_warp3d_param* param,
	vx_size input_phys_addr,
	vx_size input_phys_addr_uv,
	vx_size input_lut_phys_addr,
	vx_size output_handle);

VX_API_ENTRY vx_status VX_API_CALL RgbImageConvert(
	int w, 
	int h, 
	img_data_layout layout, 
	vx_uint8 * src, 
	vx_uint8 * dst);
	
VX_API_ENTRY vx_status VX_API_CALL RgbImageRevert(
	int w, 
	int h, 
	vx_uint8 * src, 
	img_data_layout layout, 
	vx_uint8 * dst);

/*
 * utility
 */
VX_API_ENTRY vx_status VX_API_CALL LoadNetModel(
	vx_context context,
	const char * model_file, 
	bool encrypted,
	vx_int8 ** model);

VX_API_ENTRY vx_status VX_API_CALL LoadNetModelFromMem(
	vx_context context,
	vx_int8 * model_data,
	int model_len,
	bool encrypted,
	vx_int8 ** model);

VX_API_ENTRY vx_status VX_API_CALL GetNetModelVersion(
	vx_int8* net_proto, 
	std::string& version);

VX_API_ENTRY vx_status VX_API_CALL UnLoadNetModel(vx_int8 * model);

#endif
