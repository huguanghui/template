/* 
Copyright (c) 2015 Advanced Micro Devices, Inc. All rights reserved.
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#ifndef _VX_EXT_AMD_H_
#define _VX_EXT_AMD_H_

#include <VX/vx.h>
#include <VX/vx_khr_nn.h>
#ifdef __cplusplus
#include <string>
#include <vector>
#include <map>
#endif

/*! \brief AMD internal parameters. [TODO: This needs to be moved to ago_internal.h]
*/
#define AGO_MAX_PARAMS                                    8
#define AGO_MERGE_RULE_MAX_FIND                           4
#define AGO_MERGE_RULE_MAX_REPLACE                        4
#define AGO_MERGE_RULE_SOLITARY_FLAG                   0x20

/*! \brief Maximum size of scalar string buffer. The local buffers used for accessing scalar strings 
* should be of size VX_MAX_STRING_BUFFER_SIZE_AMD and the maximum allowed string length is
* VX_MAX_STRING_BUFFER_SIZE_AMD-1.
* \ingroup group_scalar
*/
#define VX_MAX_STRING_BUFFER_SIZE_AMD                   128

/*! \brief The Neural Network activation functions vx_nn_activation_function_e extension.
 */
#define VX_NN_ACTIVATION_LEAKY_RELU  (VX_ENUM_BASE(VX_ID_AMD, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x9)

/*! \brief The type enumeration lists all the AMD specific types in OpenVX.
*/
enum ago_type_public_e {
	/*! \brief AMD data types
	*/
	VX_TYPE_FLOAT16             = 0x00F,                     // 16-bit float data type
	VX_TYPE_STRING_AMD          = 0x011,                     // scalar data type for string

};

/*! \brief The AMD context attributes list.
*/
enum vx_context_attribute_amd_e {
	/*! \brief set a text macro definition. Use a <tt>\ref AgoContextMacroInfo</tt> parameter.*/
	VX_CONTEXT_ATTRIBUTE_AMD_SET_TEXT_MACRO = VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_CONTEXT) + 0x03,
	/*! \brief set a merge rule. Use a <tt>\ref AgoNodeMergeRule</tt> parameter.*/
	VX_CONTEXT_ATTRIBUTE_AMD_SET_MERGE_RULE = VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_CONTEXT) + 0x04,
	/*! \brief tensor Data max num of dimensions supported by HW. */
	VX_CONTEXT_MAX_TENSOR_DIMENSIONS = VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_CONTEXT) + 0x05,
};

/*! \brief The AMD kernel attributes list.
*/
enum vx_kernel_attribute_amd_e {
	/*! \brief kernel callback for node regeneration. Use a <tt>\ref amd_kernel_node_regen_callback_f</tt> parameter.*/
	VX_KERNEL_ATTRIBUTE_AMD_NODE_REGEN_CALLBACK     = VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_KERNEL) + 0x03,
};

/*! \brief The AMD graph attributes list.
*/
enum vx_graph_attribute_amd_e {
	/*! \brief graph optimizer flags. Use a <tt>\ref vx_uint32</tt> parameter.*/
	VX_GRAPH_ATTRIBUTE_AMD_OPTIMIZER_FLAGS              = VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_GRAPH) + 0x04,
};

/*! \brief tensor Data attributes.
* \ingroup group_tensor
*/
enum vx_tensor_attribute_amd_e {
	VX_TENSOR_MEMORY_TYPE			= VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_TENSOR) + 0x8,
	VX_TENSOR_MEMORY_HANDLE			= VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_TENSOR) + 0x9,
	VX_TENSOR_MEMORY_PHYS_ADDR		= VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_TENSOR) + 0xa,
	VX_TENSOR_MEMORY_VIRT_ADDR		= VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_TENSOR) + 0xb,
	VX_TENSOR_MEMORY_SIZE			= VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_TENSOR) + 0xc,
	VX_TENSOR_FIXED_POINT_POSITION	= VX_ATTRIBUTE_BASE(VX_ID_AMD, VX_TYPE_TENSOR) + 0xd,
};

/*! \brief The image color space list used by the <tt>\ref VX_IMAGE_SPACE</tt> attribute of a <tt>\ref vx_image</tt>.
* \ingroup group_image
*/
enum vx_color_space_amd_e {
	/*! \brief Use to indicate that the BT.2020 coefficients are used for conversions. */
	VX_COLOR_SPACE_BT2020 = VX_ENUM_BASE(VX_ID_AMD, VX_ENUM_COLOR_SPACE) + 0x1,
};

enum vx_action_vpu_e {
	VX_ACTION_VPU_RSZ = VX_ENUM_BASE(VX_ID_AMD, VX_ENUM_ACTION) + 0x10,
	VX_ACTION_VPU_MBG = VX_ENUM_BASE(VX_ID_AMD, VX_ENUM_ACTION) + 0x11,
};

/*! \brief The multidimensional data object (Tensor).
* \see vxCreateTensor
* \ingroup group_tensor
* \extends vx_reference
*/
typedef struct _vx_tensor_t * vx_tensor;

/*! \brief AMD data structure to set a text macro.
*/
typedef struct {
	vx_char macroName[256];
	vx_char * text;
} AgoContextTextMacroInfo;

/*! \brief AMD data structure to import a graph from a text.
**    text:
**      "macro <macro-name>" to use a pre-defined macro
**      "file <file-name>" to load from a file
**      otherwise use the text as is
*/
typedef struct {
	vx_char * text;
	vx_uint32 num_ref;
	vx_reference * ref;
	vx_int32 dumpToConsole;
	void (VX_CALLBACK * data_registry_callback_f) (void * obj, vx_reference ref, const char * name, const char * app_params);
	void * data_registry_callback_obj;
} AgoGraphImportInfo;

/*! \brief AMD data structure to export a graph to a text.
*/
typedef struct {
	vx_char fileName[256];
	vx_uint32 num_ref;
	vx_reference * ref;
	vx_char comment[64];
} AgoGraphExportInfo;

/*! \brief AMD data structure to get internal performance data.
*/
typedef struct {
	vx_uint64 kernel_enqueue;
	vx_uint64 kernel_wait;
	vx_uint64 buffer_read;
	vx_uint64 buffer_write;
} AgoGraphPerfInternalInfo;

/*! \brief AMD data structure to specify node merge rule.
*/
typedef struct AgoNodeMergeRule_t {
	struct {
		vx_enum    kernel_id;
		vx_uint32  arg_spec[AGO_MAX_PARAMS];
	} find[AGO_MERGE_RULE_MAX_FIND];
	struct {
		vx_enum    kernel_id;
		vx_uint32  arg_spec[AGO_MAX_PARAMS];
	} replace[AGO_MERGE_RULE_MAX_REPLACE];
} AgoNodeMergeRule;


#ifdef __cplusplus

/*! \brief AMD usernode callback for regenerating a node.
*/
typedef vx_status(VX_CALLBACK * amd_drama_add_node_f)(vx_node node, vx_enum kernel_id, vx_reference * paramList, vx_uint32 paramCount);
typedef vx_status(VX_CALLBACK * amd_kernel_node_regen_callback_f)(vx_node node, amd_drama_add_node_f add_node_f, vx_bool& replace_original);

#endif

#ifdef  __cplusplus
extern "C" {
#endif

/**
* \brief Retrieve the name of a reference
* \ingroup vx_framework_reference
*
* This function is used to retrieve the name of a reference.
*
* \param [in] ref The reference.
* \param [out] name Pointer to copy the name of the reference.
* \param [in] size Size of the name buffer.
* \return A \ref vx_status_e enumeration.
* \retval VX_SUCCESS No errors.
* \retval VX_ERROR_INVALID_REFERENCE if reference is not valid.
*/
VX_API_ENTRY vx_status VX_API_CALL vxGetReferenceName(vx_reference ref, vx_char name[], vx_size size);

/* Tensor */
VX_API_ENTRY vx_tensor VX_API_CALL vxCreateGraphTensorFromHandle(vx_graph graph, vx_size number_of_dims, const vx_size* dims, vx_enum data_type, vx_int8 fixed_point_position, const vx_size* stride, void* ptr, vx_enum memory_type);

/* extend for nna device */
VX_API_ENTRY vx_graph VX_API_CALL vxGetScopeGraph(vx_reference reference);
VX_API_ENTRY vx_bool VX_API_CALL vxGraphProfEnable(vx_graph graph);
VX_API_ENTRY vx_size VX_API_CALL vxAllocateDeviceMemory(vx_context context, vx_size size);
VX_API_ENTRY vx_status VX_API_CALL vxFreeDeviceMemory(vx_context context, vx_size handle);
VX_API_ENTRY vx_status VX_API_CALL vxReserveDeviceMemory(vx_size size);
VX_API_ENTRY vx_status VX_API_CALL vxUnReserveDeviceMemory();
VX_API_ENTRY vx_size VX_API_CALL vxGetDeviceMemorySize(vx_size handle);
VX_API_ENTRY vx_size VX_API_CALL vxGetDeviceMemoryPhysicalAddress(vx_size handle);
VX_API_ENTRY vx_size VX_API_CALL vxGetDeviceMemoryVirtualAddress(vx_size handle);
VX_API_ENTRY vx_status VX_API_CALL vxInvalidateDeviceMemoryCache(vx_context context, vx_size handle);
VX_API_ENTRY vx_status VX_API_CALL vxInvalidateDeviceMemoryCacheAll(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxFlushDeviceMemoryCache(vx_context context, vx_size handle);
VX_API_ENTRY vx_status VX_API_CALL vxFlushDeviceMemoryCacheAll(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxDeviceMemoryInfo(vx_context context, std::vector<vx_size>& mem_size, std::vector<vx_size>& virt_addr, std::vector<vx_size>& phys_addr);

VX_API_ENTRY vx_status VX_API_CALL vxConfigGraphMemory(vx_graph graph, vx_size cmd_handle, bool dynamic_params, vx_size wt_handle, bool on_chip_mem, vx_size io_handle_size, vx_size io_handle);
VX_API_ENTRY vx_int32 VX_API_CALL vxGetGraphInOutMemorySize(vx_graph graph);

VX_API_ENTRY vx_status VX_API_CALL vxConfigInOutSharedMemory(vx_context context, vx_size handle);
VX_API_ENTRY vx_status VX_API_CALL vxLockInOutSharedMemory(vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxUnLockInOutSharedMemory(vx_graph graph);

VX_API_ENTRY vx_status VX_API_CALL vxSetGraphCommandParams(vx_graph graph, std::vector<int>& cmd_offset, std::vector<int>& cmd_length);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphCommandPacketParams(vx_graph graph, int cmd_blk_num, int first_cmd_len, int offset, int length, bool on_chip_mem_enable, bool next_soft_kernel);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphLayerBlockCommandParams(vx_graph graph, std::vector<int>& block_cmd_first, std::vector<int>& block_cmd_count, std::vector<int>& layers_of_block);
VX_API_ENTRY vx_int32 VX_API_CALL vxGetGraphLayerBlockCount(vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxQueueCommand(vx_context context, vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxProcessCommand(vx_context context, vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxPushGraphSoftBlockPerf(vx_graph graph, int time_eval);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphBlockType(vx_graph graph, int node_type, int block_idx);
VX_API_ENTRY vx_size VX_API_CALL vxCreateHandleFromDeviceMemory(vx_context context, vx_size offset, vx_size length, vx_size dev_mem_handle);
VX_API_ENTRY vx_status VX_API_CALL vxReleaseDeviceMemoryHandle(vx_context context, vx_size dev_mem_handle);
VX_API_ENTRY vx_status VX_API_CALL vxVerifyDeviceMemoryHandle(vx_context context, vx_size dev_mem_handle);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphInputTensor(vx_graph graph, int batch_idx, std::string name, std::vector<int>& dims, std::vector<int>& channels, int align_mode, vx_tensor tensor);
VX_API_ENTRY vx_status VX_API_CALL vxGetGraphInputBlob(vx_graph graph, std::map<std::string, std::vector<std::vector<void*>>>& input_blobs);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphOutputTensor(vx_graph graph, int batch_idx, bool final_output, std::string name, std::vector<int> & dims, std::vector<int>& channels, int align_mode, vx_tensor tensor);
VX_API_ENTRY vx_status VX_API_CALL vxGetGraphOutputBlob(vx_graph graph, std::map<std::string, std::vector<std::vector<void*>>>& output_blobs);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphInputBlobPosition(vx_graph graph, std::map<std::string, std::vector<std::pair<int, int>>>& input_data_pos, std::map<std::string, std::vector<std::vector<std::tuple<int, int, int>>>>& input_cmd_pos);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphInputHandle(vx_graph graph, std::string& name, vx_size handle, int batch_idx);
VX_API_ENTRY vx_status VX_API_CALL vxResetGraphInputHandle(vx_graph graph, std::string& name, int batch_idx);
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphQuantizationParam(vx_graph graph, std::string& name, bool qen);

VX_API_ENTRY vx_uint64 VX_API_CALL vxGetSysTime();
VX_API_ENTRY vx_int32 VX_API_CALL vxGetDeviceID(vx_context context, const vx_char* dev_name);
VX_API_ENTRY vx_int32 VX_API_CALL vxGetDeviceVersion(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxSetDeviceFreq(vx_context context, const vx_char* dev_name, int freq);
VX_API_ENTRY vx_status VX_API_CALL vxGetDeviceFreq(vx_context context, const vx_char* dev_name, int* freq);
VX_API_ENTRY vx_status VX_API_CALL vxSetDeviceTimeOut(vx_context context, const vx_char * dev_name, int timeout);
VX_API_ENTRY vx_status VX_API_CALL vxGetDeviceTimeOut(vx_context context, const vx_char * dev_name, int * timeout);
VX_API_ENTRY vx_status VX_API_CALL vxNpuDeviceRun(vx_context context, int cmd_blk_num, int first_cmd_len, vx_size internal_phys_base_addr, vx_size input_phys_base_addr, vx_size output_phys_base_addr, vx_size size_of_cmd, vx_uint32* cmd);
VX_API_ENTRY vx_status VX_API_CALL vxProfileGraph(vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxExecuteCommand(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxFinish(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxFlush(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxWaitSync(vx_context context, vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxQueueVpuCommand(vx_context context, vx_int32 cmd_num, vx_int32 first_cmd_len, vx_int32 size_of_cmd, vx_uint32* cmd);
VX_API_ENTRY vx_status VX_API_CALL vxVpuFinish(vx_context context);
VX_API_ENTRY vx_status VX_API_CALL vxBuildRoiAlignGraph(vx_graph pool_graph, vx_int32 pool_wt_offset, vx_int32 pool_io_offset, vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxProcessRoiAlignGraph(vx_int32 width, vx_int32 height, vx_size input_handle, vx_uint32* roi_align_cmd, vx_graph graph);

#ifdef  __cplusplus
}
#endif

#endif
