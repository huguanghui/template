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

#ifndef _OPENVX_KERNELS_H_
#define _OPENVX_KERNELS_H_

/*!
 * \file
 * \brief The list of supported kernels in the OpenVX standard.
 */

#ifdef  __cplusplus
extern "C" {
#endif

/*!
 * \brief The standard list of available libraries
 * \ingroup group_kernel
 */
enum vx_library_e {
    /*! \brief The base set of kernels as defined by Khronos. */
    VX_LIBRARY_KHR_BASE = 0x0,
};

/*!
 * \brief The standard list of available vision kernels.
 *
 * Each kernel listed here can be used with the <tt>\ref vxGetKernelByEnum</tt> call.
 * When programming the parameters, use
 * \arg <tt>\ref VX_INPUT</tt> for [in]
 * \arg <tt>\ref VX_OUTPUT</tt> for [out]
 * \arg <tt>\ref VX_BIDIRECTIONAL</tt> for [in,out]
 *
 * When programming the parameters, use
 * \arg <tt>\ref VX_TYPE_IMAGE</tt> for a <tt>\ref vx_image</tt> in the size field of <tt>\ref vxGetParameterByIndex</tt> or <tt>\ref vxSetParameterByIndex</tt>  * \arg <tt>\ref VX_TYPE_ARRAY</tt> for a <tt>\ref vx_array</tt> in the size field of <tt>\ref vxGetParameterByIndex</tt> or <tt>\ref vxSetParameterByIndex</tt>  * \arg or other appropriate types in \ref vx_type_e.
 * \ingroup group_kernel
 */
enum vx_kernel_e {
            
    /*! \brief The tensor multiply Kernel.
    * \see group_vision_function_tensor_multiply
    */
    VX_KERNEL_TENSOR_MULTIPLY = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_BASE) + 0x30,

    /*! \brief The tensor add Kernel.
    * \see group_vision_function_tensor_add
    */
    VX_KERNEL_TENSOR_ADD = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_BASE) + 0x31,

    /*! \brief The tensor subtract Kernel.
    * \see group_vision_function_tensor_subtract
    */
    VX_KERNEL_TENSOR_SUBTRACT = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_BASE) + 0x32,

    /*! \brief The tensor table look up Kernel.
    * \see group_vision_function_tensor_tablelookup
    */
    VX_KERNEL_TENSOR_TABLE_LOOKUP = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_BASE) + 0x33,
           
    /*! \brief The tensor matrix multiply Kernel.
    * \see group_vision_function_tensor_matrix_multiply
    */
    VX_KERNEL_TENSOR_MATRIX_MULTIPLY = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_BASE) + 0x36,

    /*! \brief The data object copy kernel.
    * \see group_vision_function_copy
    */
    VX_KERNEL_COPY = VX_KERNEL_BASE(VX_ID_KHRONOS, VX_LIBRARY_KHR_BASE) + 0x37,
        
};

#ifdef  __cplusplus
}
#endif

#endif  /* _OPEN_VISION_LIBRARY_KERNELS_H_ */
