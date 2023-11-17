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


#ifndef _VX_AMD_NN_H_
#define _VX_AMD_NN_H_

#include <VX/vx.h>
#include <VX/vx_khr_nn.h>
#include <vx_ext_amd.h>

/*! \brief [Graph] Creates a Scale Layer Node.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data.
 * \param [in] inputs The scale tensor data.
 * \param [in] inputs The bias tensor data.
 * \param [out] outputs The output tensor data.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxScaleLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor inputs, vx_tensor scale, vx_tensor bias, vx_tensor output);

/*! \brief [Graph] Creates a Concat Layer Node.
 * \param [in] graph The handle to the graph.
 * \param [out] outputs The output tensor data.
 * \param [in] inputs The input 1 tensor data.
 * \param [in] inputs The input 2 tensor data.
 * \param [in] inputs The input 3 tensor data.
 * \param [in] inputs The input 4 tensor data.
 * \param [in] inputs The input 5 tensor data.
 * \param [in] inputs The input 6 tensor data.
 * \param [in] inputs The input 7 tensor data.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxConcatLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_size axis, vx_tensor_array_t * input_tensors, vx_size size_of_input_tensors, vx_tensor output);

/*! \brief [Graph] Creates a Slice Layer Node.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data.
 * \param [out] inputs The output 1 tensor data.
 * \param [out] inputs The output 2 tensor data.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
//VX_API_ENTRY vx_node VX_API_CALL vxSliceLayer(vx_graph graph, vx_tensor input, vx_tensor output1, vx_tensor output2, vx_tensor output3, vx_tensor output4, vx_tensor output5, vx_tensor output6, vx_tensor output7, vx_tensor output8);
VX_API_ENTRY vx_node VX_API_CALL vxSliceLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor input, vx_size axis, vx_tensor_array_t * output_tensors, vx_size size_of_output_tensors);

/*! \brief [Graph] Creates a Convolutional Network Upsampling Layer Node.
 * \details Upsampling is done on the width and height dimensions of the <tt>\ref vx_tensor</tt>. Therefore, we use here the term x for the width dimension and y for the height dimension.\n
 * The Upsampling accept input images as tensors of several types. They always output resized images as float32 tensors.
 * This function supports 4D and 3D tensors as input and output. 4D tensors are for batches of images, 3D tensors for individual images.
 * Upsampling use resize method NEAREST_NEIGHBOR.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data.
 * \param [out] outputs The output tensor data. Output will have the same number of dimensions as input. Output tensor data type must be same as the inputs. The width and height dimensions of output must be integer multiple of input. The batch and channel dimensions of output and input must be same.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxUpsampleLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor input, vx_tensor output);

/*! \brief [Graph] Creates a Convolutional Network Reshape Layer Node.
 * \details Reshaping is done with alias if available (output tensor will point to input tensor memory). Otherwise it will do a copy.\n
 * This function supports 4D tensors as input and output.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data.
 * \param [out] outputs The output tensor data. Output will have the same number of dimensions as input. Output tensor data type must be same as the inputs. The width and height dimensions of output must be integer multiple of input. The batch and channel dimensions of output and input must be same.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxReshapeLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor input, vx_tensor output);
VX_API_ENTRY vx_node VX_API_CALL vxExecuteLayerDummy(vx_graph graph, vx_tensor inputs, vx_tensor outputs);
VX_API_ENTRY vx_node VX_API_CALL vxEndLayerDummy(vx_graph graph, vx_tensor inputs, vx_tensor outputs);
VX_API_ENTRY vx_node VX_API_CALL vxSyncLayerDummy(vx_graph graph, vx_tensor inputs, vx_tensor outputs);
VX_API_ENTRY vx_node VX_API_CALL vxPermuteLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor inputs, const vx_nn_permute_params_t* permute_params, vx_size size_of_permute_params, vx_tensor outputs);
VX_API_ENTRY vx_node VX_API_CALL vxDummyDataLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor outputs);
VX_API_ENTRY vx_node VX_API_CALL vxCropLayer(vx_graph graph, vx_tensor inputs1, vx_tensor inputs2, vx_tensor outputs);
VX_API_ENTRY vx_node VX_API_CALL vxSplitLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor input, vx_tensor_array_t * output_tensors, vx_size size_of_output_tensors);
VX_API_ENTRY vx_node VX_API_CALL vxCustomLayer(vx_graph graph, vx_tensor_array_t* input_tensors, vx_size size_of_input_tensors, const vx_char * type, vx_nn_custom_params_t* custom_params, vx_size size_of_custom_params, vx_tensor_array_t* output_tensors, vx_size size_of_output_tensors);
typedef void (*custom_layer_callback)(std::vector<vx_tensor>& input_tensors, std::vector<vx_float32>& custom_params, std::vector<vx_tensor>& output_tensors);
VX_API_ENTRY vx_status VX_API_CALL vxRegisterCustomLayerCallback(vx_context context, const char* name, custom_layer_callback callback);
VX_API_ENTRY vx_status VX_API_CALL vxUnRegisterCustomLayerCallBack(vx_context context, const char* name);

#endif
