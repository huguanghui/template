/*

 * Copyright (c) 2012-2017 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _OPENVX_NODES_H_
#define _OPENVX_NODES_H_

/*!
 * \file vx_nodes.h
 * \brief The "Simple" API interface for OpenVX. These APIs are just
 * wrappers around the more verbose functions defined in <tt>\ref vx_api.h</tt>.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief [Graph] Performs element wise multiplications on element values in the input tensor data with a scale.
 * \param [in] graph The handle to the graph.
 * \param [in] input1 Input tensor data.  Implementations must support input tensor data type <tt>\ref VX_TYPE_INT16</tt> with fixed_point_position 8,
 * and tensor data types <tt>\ref VX_TYPE_UINT8</tt> and <tt>\ref VX_TYPE_INT8</tt>, with fixed_point_position 0.  
 * \param [in] input2 Input tensor data. The dimensions and sizes of input2 match those of input1, unless the vx_tensor of one or more dimensions in input2 is 1.
 * In this case, those dimensions are treated as if this tensor was expanded to match the size of the corresponding dimension of input1,
 * and data was duplicated on all terms in that dimension. After this expansion, the dimensions will be equal.
 * The data type must match the data type of Input1.
 * \param [in] scale A non-negative <tt>\ref VX_TYPE_FLOAT32</tt> multiplied to each product before overflow handling.
 * \param [in] overflow_policy A <tt>\ref vx_convert_policy_e</tt> enumeration.
 * \param [in] rounding_policy A <tt>\ref vx_round_policy_e</tt> enumeration.
 * \param [out] output The output tensor data with the same dimensions as the input tensor data.
 * \ingroup group_vision_function_tensor_multiply
 * \return <tt>\ref vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxTensorMultiplyNode(vx_graph graph, vx_tensor input1, vx_tensor input2, vx_scalar scale, vx_enum overflow_policy,
        vx_enum rounding_policy, vx_tensor output);

/*! \brief [Graph] Performs arithmetic addition on element values in the input tensor data.
 * \param [in] graph The handle to the graph.
 * \param [in] input1 Input tensor data.  Implementations must support input tensor data type <tt>\ref VX_TYPE_INT16</tt> with fixed_point_position 8,
 * and tensor data types <tt>\ref VX_TYPE_UINT8</tt> and <tt>\ref VX_TYPE_INT8</tt>, with fixed_point_position 0.  
 * \param [in] input2 Input tensor data. The dimensions and sizes of input2 match those of input1, unless the vx_tensor of one or more dimensions in input2 is 1.
 * In this case, those dimensions are treated as if this tensor was expanded to match the size of the corresponding dimension of input1,
 * and data was duplicated on all terms in that dimension. After this expansion, the dimensions will be equal. 
 * The data type must match the data type of Input1. 
 * \param [in] policy A <tt>\ref vx_convert_policy_e</tt> enumeration.
 * \param [out] output The output tensor data with the same dimensions as the input tensor data.
 * \ingroup group_vision_function_tensor_add
 * \return <tt>\ref vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxTensorAddNode(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor input1, vx_tensor input2, vx_enum policy, vx_tensor output);

/*! \brief [Graph] Performs arithmetic subtraction on element values in the input tensor data.
 * \param [in] graph The handle to the graph.
 * \param [in] input1 Input tensor data.  Implementations must support input tensor data type <tt>\ref VX_TYPE_INT16</tt> with fixed_point_position 8,
 * and tensor data types <tt>\ref VX_TYPE_UINT8</tt> and <tt>\ref VX_TYPE_INT8</tt>, with fixed_point_position 0.  
 * \param [in] input2 Input tensor data. The dimensions and sizes of input2 match those of input1, unless the vx_tensor of one or more dimensions in input2 is 1.
 * In this case, those dimensions are treated as if this tensor was expanded to match the size of the corresponding dimension of input1,
 * and data was duplicated on all terms in that dimension. After this expansion, the dimensions will be equal. 
 * The data type must match the data type of Input1. 
 * \param [in] policy A <tt>\ref vx_convert_policy_e</tt> enumeration.
 * \param [out] output The output tensor data with the same dimensions as the input tensor data.
 * \ingroup group_vision_function_tensor_subtract
 * \return <tt>\ref vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxTensorSubtractNode(vx_graph graph, vx_tensor input1, vx_tensor input2, vx_enum policy, vx_tensor output);

/*! \brief [Graph] Performs LUT on element values in the input tensor data.
 * \param [in] graph The handle to the graph.
 * \param [in] input1 Input tensor data. Implementations must support input tensor data type <tt>\ref VX_TYPE_INT16</tt> with fixed_point_position 8, 
 * and tensor data types <tt>\ref VX_TYPE_UINT8</tt>, with fixed_point_position 0. 
 * \param [in] lut The look-up table to use, of type <tt>\ref vx_lut</tt>.
 * The elements of input1 are treated as unsigned integers to determine an index into the look-up table.
 * The data type of the items in the look-up table must match that of the output tensor.
 * \param [out] output The output tensor data with the same dimensions as the input tensor data.
 * \ingroup group_vision_function_tensor_tablelookup
 * \return <tt>\ref vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxTensorTableLookupNode(vx_graph graph, vx_tensor input1, vx_lut lut, vx_tensor output);

/*! \brief Copy data from one object to another.
 * \note An implementation may optimize away the copy when virtual data objects are used.
 * \param [in] graph The reference to the graph.
 * \param [in] input The input data object.
 * \param [out] output The output data object with meta-data identical to the input data object.
 * \return <tt>\ref vx_node</tt>.
 * \retval vx_node A node reference. Any possible errors preventing a successful creation
 * should be checked using <tt>\ref vxGetStatus</tt>
 * \ingroup group_vision_function_copy
 */
VX_API_ENTRY vx_node VX_API_CALL vxCopyNode(vx_graph graph, vx_reference input, vx_reference output);

#ifdef __cplusplus
}
#endif

#endif
