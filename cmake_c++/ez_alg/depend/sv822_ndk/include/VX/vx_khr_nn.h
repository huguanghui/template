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

#ifndef _VX_KHR_NN_H_
#define _VX_KHR_NN_H_

/*!
 * \file
 * \brief The Khronos Extension for Deep Convolutional Networks Functions.
 *
 * \defgroup group_cnn Extension: Deep Convolutional Networks API
 * \brief Convolutional Network Nodes.
 */

#define OPENVX_KHR_NN   "vx_khr_nn"

#include <vector>
#include <VX/vx.h>


#ifdef  __cplusplus
extern "C" {
#endif


/*==============================================================================
CONVOLUTIONAL_NETWORK structs and enums
=============================================================================*/

/*! \brief The Neural Network Extension Library Set
 * \ingroup group_cnn
 */
#define VX_LIBRARY_KHR_NN_EXTENSION (0x1) 

/*! \brief The list of Neural Network Extension Kernels.
 * \ingroup group_cnn
 */
enum vx_kernel_nn_ext_e {
    /*! \brief The Neural Network Extension convolution Kernel.
    * \see group_cnn
    */
    VX_KERNEL_CONVOLUTION_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x0,
    /*! \brief The Neural Network Extension fully connected Kernel.
    * \see group_cnn
    */
    VX_KERNEL_FULLY_CONNECTED_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x1,
    /*! \brief The Neural Network Extension pooling Kernel.
    * \see group_cnn
    */
    VX_KERNEL_POOLING_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x2,
    /*! \brief The Neural Network Extension softmax Kernel.
    * \see group_cnn
    */
    VX_KERNEL_SOFTMAX_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x3,
    /*! \brief The Neural Network Extension normalization Kernel.
    * \see group_cnn
    */
    VX_KERNEL_NORMALIZATION_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x4,
    /*! \brief The Neural Network Extension activation Kernel.
    * \see group_cnn
    */
    VX_KERNEL_ACTIVATION_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x5,
    /*! \brief The Neural Network POI Pooling Kernel.
    * \see group_cnn
    */
    VX_KERNEL_ROI_POOLING_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x6,
    /*! \brief The Neural Network Extension Deconvolution Kernel.
    * \see group_cnn
    */
    VX_KERNEL_DECONVOLUTION_LAYER = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_NN_EXTENSION) + 0x7,
};

/*! \brief NN extension type enums.
 * \ingroup group_cnn
 */
enum vx_nn_enum_e
{
    VX_ENUM_NN_ROUNDING_TYPE	= 0x1A,
    VX_ENUM_NN_POOLING_TYPE	= 0x1B,
    VX_ENUM_NN_NORMALIZATION_TYPE	= 0x1C,
    VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE	= 0x1D,
};

/*! \brief down scale rounding.
 * \details Due to different scheme of downscale size calculation in the various training frameworks. Implementation must support 2 rounding methods for down scale calculation.
 * The floor and the ceiling. In convolution and pooling functions.
 * Relevant when input size is even.
 * \ingroup group_cnn
 */
enum vx_nn_rounding_type_e
{
    /*! \brief floor rounding  */
    VX_NN_DS_SIZE_ROUNDING_FLOOR = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ROUNDING_TYPE) + 0x0,
    /*! \brief ceil rounding */
    VX_NN_DS_SIZE_ROUNDING_CEILING = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ROUNDING_TYPE) + 0x1
};


/*! \brief The Neural Network pooling type list.
 * \details kind of pooling done in pooling function
 * \ingroup group_cnn
 */
enum vx_nn_pooling_type_e
{
    /*! \brief max pooling*/
    VX_NN_POOLING_MAX = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_POOLING_TYPE) + 0x0,
    /*! \brief average pooling*/
    VX_NN_POOLING_AVG = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_POOLING_TYPE) + 0x1
};


/*! \brief The Neural Network normalization type list.
 * \ingroup group_cnn
 */
enum vx_nn_norm_type_e
{
    /*! \brief normalization is done on same IFM*/
    VX_NN_NORMALIZATION_SAME_MAP = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_NORMALIZATION_TYPE) + 0x0,
    /*! \brief Normalization is done across different IFMs*/
    VX_NN_NORMALIZATION_ACROSS_MAPS = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_NORMALIZATION_TYPE) + 0x1,
};



/*! \brief The Neural Network activation functions list.
 * \details
 * <table>
 * <tr><td> <B>Function name </B> <td> <B>Mathematical definition</B> <td> <B>Parameters</B> <td> <B>Parameters type</B>
 * <tr><td>logistic <td> \f$f(x)=1/(1+e^{-x}) \f$  <td>  <td>
 * <tr><td>hyperbolic tangent <td> \f$f(x)=a\cdot tanh(b\cdot x) \f$  <td> a,b  <td> VX_FLOAT32
 * <tr><td>relu <td> \f$f(x)=max(0,x)\f$  <td>  <td>
 * <tr><td>bounded relu <td> \f$f(x)=min(a,max(0,x)) \f$  <td> a  <td> VX_FLOAT32
 * <tr><td>soft relu <td> \f$f(x)=log(1+e^{x}) \f$  <td>  <td>
 * <tr><td>abs <td> \f$f(x)=\mid x\mid \f$  <td>  <td>
 * <tr><td>square <td> \f$f(x)= x^2 \f$  <td>  <td>
 * <tr><td>square root <td> \f$f(x)=\sqrt{x} \f$  <td>  <td>
 * <tr><td>linear <td> \f$f(x)=ax+b \f$  <td>  a,b  <td> VX_FLOAT32
 * </table>
 * \ingroup group_cnn
 */
enum vx_nn_activation_function_e
{
    VX_NN_ACTIVATION_LOGISTIC = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x0,
    VX_NN_ACTIVATION_HYPERBOLIC_TAN = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x1,
    VX_NN_ACTIVATION_RELU = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x2,
    VX_NN_ACTIVATION_BRELU = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x3,
    VX_NN_ACTIVATION_SOFTRELU = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x4,
    VX_NN_ACTIVATION_ABS = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x5,
    VX_NN_ACTIVATION_SQUARE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x6,
    VX_NN_ACTIVATION_SQRT = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x7,
    VX_NN_ACTIVATION_LINEAR = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x8,
    VX_NN_ACTIVATION_PRELU = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0x9,
    VX_NN_ACTIVATION_RELU6 = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0xA,
    VX_NN_ACTIVATION_HARDSIGMOID = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_NN_ACTIVATION_FUNCTION_TYPE) + 0xB,
};

/*! \brief The type enumeration lists all NN extension types.
 * \ingroup group_cnn
 */
enum vx_nn_type_e {
	VX_TYPE_NN_CONVOLUTION_PARAMS     = 0x025,/*!< \brief A <tt>\ref vx_nn_convolution_params_t</tt>. */
	VX_TYPE_NN_DECONVOLUTION_PARAMS   = 0x026,/*!< \brief A <tt>\ref vx_nn_deconvolution_params_t</tt>. */
	VX_TYPE_NN_ROI_POOL_PARAMS        = 0x027,/*!< \brief A <tt>\ref vx_nn_roi_pool_params_t</tt>. */
    VX_TYPE_NN_POOL_PARAMS            = 0x028,
	VX_TYPE_NN_PERMUTE_PARAMS         = 0x02D,
	VX_TYPE_NN_TENSOR_PYRAMID		  = 0x02E,
	VX_TYPE_NN_CUSTOM_PARAMS		  = 0x02F,
};

/*! \brief Input parameters for a convolution operation.
 * \ingroup group_cnn
 */
typedef struct _vx_nn_convolution_params_t
{
    vx_size padding_xl;                 /*!< \brief Number of elements added at each side in the x dimension of the input. */
	vx_size padding_xr;
    vx_size padding_yl;                 /*!< \brief Number of elements added at each side in the y dimension of the input. */
	vx_size padding_yr;
	vx_enum overflow_policy;         /*!< \brief A <tt> VX_TYPE_ENUM</tt> of the <tt> vx_convert_policy_e</tt> enumeration. */
    vx_enum rounding_policy;         /*!< \brief A <tt> VX_TYPE_ENUM</tt> of the <tt> vx_round_policy_e</tt> enumeration. */
    vx_enum down_scale_size_rounding; /*!< \brief Rounding method for calculating output dimensions. See <tt>\ref vx_nn_rounding_type_e</tt> */
    vx_size dilation_x;            /*!< \brief “inflate” the kernel by inserting zeros between the kernel elements in the x direction. The value is the number of zeros to insert.*/
    vx_size dilation_y;            /*!< \brief “inflate” the kernel by inserting zeros between the kernel elements in the y direction. The value is the number of zeros to insert.*/
	vx_size input_channel;
	vx_size input_channel_offset;
	vx_size input_channel_width;
	vx_size output_channel;
	vx_size output_channel_offset;
	vx_size output_channel_width;
	vx_size group;
	vx_size executor;
} vx_nn_convolution_params_t;

typedef struct _vx_nn_custom_params_t
{
    vx_size num;
	vx_float32 params[16];
}vx_nn_custom_params_t;

typedef struct _vx_nn_pooling_params_t 
{
    vx_enum pooling_type;
    vx_size pooling_size_x;
    vx_size pooling_size_y;
    vx_size pooling_padding_x;
    vx_size pooling_padding_y;
    vx_enum rounding_policy;
} vx_nn_pooling_params_t;

typedef struct _vx_tensor_array_t
{
	vx_size num;
	vx_tensor tensors[256];
}vx_tensor_array_t;

typedef struct _vx_nn_permute_params_t
{
    vx_size axis_order0;
    vx_size axis_order1;
    vx_size axis_order2;
    vx_size axis_order3;
}vx_nn_permute_params_t;

/*==============================================================================
    NN Nodes
=============================================================================*/
/*! \brief [Graph] Creates a Convolutional Network Convolution Layer Node.
 * \details This function implement Convolutional Network Convolution layer.
 *  For fixed-point data types, a fixed point calculation is performed with round and saturate according to the number of accumulator bits. The number of the accumulator bits are implementation defined,
 * and should be at least 16.\n
 * round: rounding according the <tt>vx_round_policy_e</tt> enumeration. \n
 * saturate: A saturation according the <tt>vx_convert_policy_e</tt> enumeration.
 * The following equation is implemented: \n
 * \f$ outputs[j,k,i] = saturate(round(\sum_{l} (\sum_{m,n} inputs[j+m,k+n,l] \times weights[m,n,l,i])+biasses[j,k,i])) \f$\n
 * Where \f$m,n\f$ are indexes on the convolution matrices. \f$ l\f$ is an index on all the convolutions per input.\f$ i\f$ is an index per output.
 * \f$ j,k \f$ are the inputs/outputs spatial indexes.
 * Convolution is done on the width and height dimensions of the <tt>\ref vx_tensor</tt>. Therefore, we use here the term x for index along the width dimension and y for index along the height dimension.\n
 * before the Convolution is done, a padding with zeros of the width and height input dimensions is performed.
 * Then down scale is done by picking the results according to a skip jump. The skip in the x and y is determined by the output size dimensions.
 * The relation between input to output is as follows: \n
 * \f$ width_{output} = round(\frac{(width_{input} + 2 * padding_x - kernel_x - (kernel_x -1) * dilation_x)}{skip_x} + 1) \f$\n
 * and \n
 * \f$ height_{output} = round(\frac{(height + 2 * padding_y - kernel_y - (kernel_y -1) * dilation_y)}{skip_y} + 1) \f$\n 
 * where \f$width\f$ is the size of the input width dimension. \f$height\f$ is the size of the input height dimension.
 * \f$width_{output}\f$ is the size of the output width dimension. \f$height_{output}\f$ is the size of the output height dimension.
 * \f$kernel_x\f$ and \f$kernel_y\f$ are the convolution sizes in width and height dimensions.
 * skip is calculated by the relation between input and output. In case of ambiguity in the inverse calculation of the skip. The minimum solution is chosen. Skip must be a positive non zero integer.
 * rounding is done according to <tt>\ref vx_nn_rounding_type_e</tt>.
 * Notice that this node creation function has more parameters than the corresponding kernel. Numbering of kernel parameters (required if you create this node using the generic interface) is explicitly specified here.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data. 3 lower dimensions represent a single input, all following dimensions represent number of batches, possibly nested.
 * The dimension order is [width, height, #IFM, #batches]\n. Implementations must support input tensor data types indicated by the extension strings 'KHR_NN_8' or 'KHR_NN_8 KHR_NN_16'.  (Kernel parameter #0)
 * \param [in] weights [static] Weights are 4d tensor with dimensions [kernel_x, kernel_y, #IFM, #OFM]. see <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt> \n Weights data type must match the data type of the inputs.  (Kernel parameter #1)
 * \param [in] biases [static] Optional, ignored if NULL. The biases, which may be shared (one per ofm) or unshared (one per ofm * output location). The possible layouts are
 * either [#OFM] or [width, height, #OFM]. Biases data type must match the data type of the inputs.   (Kernel parameter #2)
 * \param [in] convolution_params [static] Pointer to parameters of type <tt>\ref vx_nn_convolution_params_t</tt>.  (Kernel parameter #3)
 * \param [in] size_of_convolution_params [static] Size in bytes of convolution_params. Note that this parameter is not counted as one of the kernel parameters.
 * \param [out] outputs The output tensor data. Output will have the same number and structure of dimensions as input. Output tensor data type must be same as the inputs.  (Kernel parameter #4)
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_cnn
 */
VX_API_ENTRY vx_node VX_API_CALL vxConvolutionLayer(vx_graph graph, 
                                                    const vx_char* name,
                                                    vx_size name_len,
													vx_tensor inputs, 
													vx_tensor weights, 
													vx_tensor biases, 
													const vx_nn_convolution_params_t* convolution_params, 
													vx_size size_of_convolution_params, 
													vx_tensor outputs);

/*! \brief [Graph] Creates a Fully connected Convolutional Network Layer Node.
 * \details This function implement Fully connected Convolutional Network layers.
 * For fixed-point data types, a fixed point calculation is performed with round and saturate according to the number of accumulator bits. The number of the accumulator bits are implementation defined,
 * and should be at least 16.\n
 * round: rounding according the <tt>vx_round_policy_e</tt> enumeration. \n
 * saturate: A saturation according the <tt>vx_convert_policy_e</tt> enumeration.
 * The equation for Fully connected layer:\n
 * \f$ outputs[i] = saturate(round(\sum_{j} (inputs[j] \times weights[j,i])+biasses[i])) \f$\n
 * Where \f$j\f$ is a index on the input feature and \f$i\f$ is a index on the output.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data. There two possible input layouts:
 * 1. [#IFM, #batches]. See <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt>.
 * 2. [width, height, #IFM, #batches]. See <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt>\n
 * In both cases number of batches are optional and may be multidimensional.
 * The second option is a special case to deal with convolution layer followed by fully connected.
 * The dimension order is [#IFM, #batches]. See <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt>. Note that batch may be multidimensional. Implementations must support input tensor data types indicated by the extension strings 'KHR_NN_8' or 'KHR_NN_8 KHR_NN_16'. 
 * \param [in] weights [static] Number of dimensions is 2. Dimensions are [#IFM, #OFM]. See <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt>.\n Implementations must support input tensor data type same as the inputs.
 * \param [in] biases [static] Optional, ignored if NULL. The biases have one dimension [#OFM]. Implementations must support input tensor data type same as the inputs.
 * \param [in] overflow_policy [static] A <tt> VX_TYPE_ENUM</tt> of the <tt> vx_convert_policy_e</tt> enumeration.
 * \param [in] rounding_policy [static] A <tt> VX_TYPE_ENUM</tt> of the <tt> vx_round_policy_e</tt> enumeration.
 * \param [out] outputs The output tensor data. Output dimension layout is [#OFM,#batches]. See <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt>, where #batches may be multidimensional. Output tensor data type must be same as the inputs.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_cnn
 */
VX_API_ENTRY vx_node VX_API_CALL vxFullyConnectedLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor inputs, vx_tensor weights, vx_tensor biases, vx_enum overflow_policy, vx_enum rounding_policy, vx_tensor outputs);


/*! \brief [Graph] Creates a Convolutional Network Pooling Layer Node.
 * \details Pooling is done on the width and height dimensions of the <tt>\ref vx_tensor</tt>. Therefore, we use here the term x for the width dimension and y for the height dimension.\n
 * Pooling operation is a function operation over a rectangle size and then a nearest neighbour down scale.
 * Here we use pooling_size_x and pooling_size_y to specify the rectangle size on which the operation
 * is performed. \n
 * before the operation is done (average or maximum value). the data is padded with zeros in width and height dimensions .
 * The down scale is done by picking the results according to a skip jump. The skip in the x and y dimension is determined by the output size dimensions.
 * The first pixel of the down scale output is the first pixel in the input.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data. 3 lower dimensions represent a single input, 4th dimension for batch of inputs is optional.Dimension layout is [width, height, #IFM, #batches].
 * See <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt> 
 * Implementations must support input tensor data types indicated by the extension strings 'KHR_NN_8' or 'KHR_NN_8 KHR_NN_16'. 
 * \param [in] pooling_type [static] Either max pooling or average pooling (see <tt>\ref vx_nn_pooling_type_e</tt>).
 * \param [in] pooling_size_x [static] Size of the pooling region in the x dimension
 * \param [in] pooling_size_y [static] Size of the pooling region in the y dimension.
 * \param [in] pooling_padding_x [static] Padding size in the x dimension.
 * \param [in] pooling_padding_y [static] Padding size in the y dimension.
 * \param [in] rounding [static] Rounding method for calculating output dimensions. See <tt>\ref vx_nn_rounding_type_e</tt>
 * \param [out] outputs The output tensor data. Output will have the same number of dimensions as input. Output tensor data type must be same as the inputs.
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_cnn
 */
VX_API_ENTRY vx_node VX_API_CALL vxPoolingLayer(
    vx_graph graph,
    const vx_char* name,
    vx_size name_len,
    vx_tensor inputs,
    const vx_nn_pooling_params_t* pooling_params,
    vx_size size_of_pooling_params,
    vx_tensor outputs);

/*! \brief [Graph] Creates a Convolutional Network Softmax Layer Node.
 * \details  the softmax function, is a generalization of the logistic function that "squashes" a K-dimensional vector \f$ z \f$ of arbitrary real values to a K-dimensional vector
 * \f$ \sigma(z) \f$ of real values in the range (0, 1) that add up to 1. The function is given by:
 * \f$ \sigma(z) = \frac{\exp^z}{\sum_i \exp^{z_i}} \f$
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor,  with the number of dimensions according to the following scheme. 
 * In case IFM dimension is 1. Softmax is be calculated on that dimension.
 * In case IFM dimension is 2. Softmax is be calculated on the first dimension. The second dimension is batching.
 * In case IFM dimension is 3. Dimensions are [Width, Height, Classes]. And Softmax is calculated on the third dimension.
 * In case IFM dimension is 4. Dimensions are [Width, Height, Classes, batching]. Softmax is calculated on the third dimension.
 * Regarding the layout specification, see <tt>\ref vxCreateTensor</tt> and <tt>\ref vxCreateVirtualTensor</tt>.
 * In all cases Implementations must support input tensor data types indicated by the extension strings 'KHR_NN_8' or 'KHR_NN_8 KHR_NN_16'. 
 * \param [out] outputs The output tensor. Output will have the same number of dimensions as input. Output tensor data type must be same as the inputs.
 * \ingroup group_cnn
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */

VX_API_ENTRY vx_node VX_API_CALL vxSoftmaxLayer(vx_graph graph, vx_tensor inputs, vx_tensor outputs);

/*! \brief [Graph] Creates a Convolutional Network Activation Layer Node.
 * The function operate a specific function (Specified in <tt>\ref vx_nn_activation_function_e</tt>), On the input data.
 * the equation for the layer is:
 * \f$ outputs(i,j,k,l) = function(inputs(i,j,k,l), a, b) \f$ for all i,j,k,l.
 * \param [in] graph The handle to the graph.
 * \param [in] inputs The input tensor data.
 * Implementations must support input tensor data types indicated by the extension strings 'KHR_NN_8' or 'KHR_NN_8 KHR_NN_16'. 
 * \param [in] function [static] Non-linear function (see <tt>\ref vx_nn_activation_function_e</tt>). Implementations must support <tt>\ref VX_NN_ACTIVATION_LOGISTIC</tt>, <tt>\ref VX_NN_ACTIVATION_HYPERBOLIC_TAN</tt> and <tt>\ref VX_NN_ACTIVATION_RELU</tt>
 * \param [in] a [static] Function parameters a. must be positive.
 * \param [in] b [static] Function parameters b. must be positive.
 * \param [out] outputs The output tensor data. Output will have the same number of dimensions as input.
 * \ingroup group_cnn
 * \return <tt> vx_node</tt>.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_node VX_API_CALL vxActivationLayer(vx_graph graph, const vx_char* name, vx_size name_len, vx_tensor inputs, vx_enum function, vx_tensor weights, vx_tensor outputs);
	
#ifdef  __cplusplus
}
#endif


#endif
