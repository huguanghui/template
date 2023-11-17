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

#ifndef _OPENVX_API_H_
#define _OPENVX_API_H_

/*!
 * \file
 * \brief The API definition for OpenVX.
 */

#ifdef  __cplusplus
extern "C" {
#endif

/*==============================================================================
 CONTEXT
 =============================================================================*/

/*! \brief Creates a <tt>\ref vx_context</tt>.
 * \details This creates a top-level object context for OpenVX.
 * \note This is required to do anything else.
 * \returns The reference to the implementation context <tt>\ref vx_context</tt>. Any possible errors
 * preventing a successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_context
 * \post <tt>\ref vxReleaseContext</tt>
 */
VX_API_ENTRY vx_context VX_API_CALL vxCreateContext(void);

/*! \brief Releases the OpenVX object context.
 * \details All reference counted objects are garbage-collected by the return of this call.
 * No calls are possible using the parameter context after the context has been
 * released until a new reference from <tt>\ref vxCreateContext</tt> is returned.
 * All outstanding references to OpenVX objects from this context are invalid
 * after this call.
 * \param [in] context The pointer to the reference to the context.
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE context is not a valid <tt>\ref vx_context</tt> reference.
 * \ingroup group_context
 * \pre <tt>\ref vxCreateContext</tt>
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseContext(vx_context *context);

/*! \brief Retrieves the context from any reference from within a context.
 * \param [in] reference The reference from which to extract the context.
 * \ingroup group_context
 * \return The overall context that created the particular
 * reference. Any possible errors preventing a successful completion of this function
 * should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_context VX_API_CALL vxGetContext(vx_reference reference);

/*! \brief Queries the context for some specific information.
 * \param [in] context The reference to the context.
 * \param [in] attribute The attribute to query. Use a <tt>\ref vx_context_attribute_e</tt>.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size in bytes of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE context is not a valid <tt>\ref vx_context</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If any of the other parameters are incorrect.
 * \retval VX_ERROR_NOT_SUPPORTED If the attribute is not supported on this implementation.
 * \ingroup group_context
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryContext(vx_context context, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Sets an attribute on the context.
 * \param [in] context The handle to the overall context.
 * \param [in] attribute The attribute to set from <tt>\ref vx_context_attribute_e</tt>.
 * \param [in] ptr The pointer to the data to which to set the attribute.
 * \param [in] size The size in bytes of the data to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE context is not a valid <tt>\ref vx_context</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If any of the other parameters are incorrect.
 * \retval VX_ERROR_NOT_SUPPORTED If the attribute is not settable.
 * \ingroup group_context
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetContextAttribute(vx_context context, vx_enum attribute, const void *ptr, vx_size size);

/*! \brief Provides a generic API to give platform-specific hints to the implementation.
 * \param [in] reference The reference to the object to hint at.
 * This could be <tt>\ref vx_context</tt>, <tt>\ref vx_graph</tt>, <tt>\ref vx_node</tt>, <tt>\ref vx_image</tt>, <tt>\ref vx_array</tt>, or any other reference.
 * \param [in] hint A <tt>\ref vx_hint_e</tt> \a hint to give to a \ref vx_context. This is a platform-specific optimization or implementation mechanism.
 * \param [in] data Optional vendor specific data.
 * \param [in] data_size Size of the data structure \p data.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE reference is not a valid <tt>\ref vx_reference</tt> reference.
 * \retval VX_ERROR_NOT_SUPPORTED If the hint is not supported.
 * \ingroup group_hint
 */
VX_API_ENTRY vx_status VX_API_CALL vxHint(vx_reference reference, vx_enum hint, const void* data, vx_size data_size);

/*! \brief Provides a generic API to give platform-specific directives to the implementations.
 * \param [in] reference The reference to the object to set the directive on.
 * This could be <tt>\ref vx_context</tt>, <tt>\ref vx_graph</tt>, <tt>\ref vx_node</tt>, <tt>\ref vx_image</tt>, <tt>\ref vx_array</tt>, or any other reference.
 * \param [in] directive The directive to set. See <tt>\ref vx_directive_e</tt>.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE reference is not a valid <tt>\ref vx_reference</tt> reference.
 * \retval VX_ERROR_NOT_SUPPORTED If the directive is not supported.
 * \note The performance counter directives are only available for the reference \ref vx_context.
 *       Error VX_ERROR_NOT_SUPPORTED is returned when used with any other reference.
 * \ingroup group_directive
 */
VX_API_ENTRY vx_status VX_API_CALL vxDirective(vx_reference reference, vx_enum directive);

/*! \brief Provides a generic API to return status values from Object constructors if they
 * fail.
 * \note Users do not need to strictly check every object creator as the errors
 * should properly propagate and be detected during verification time or run-time.
 * \code
 * vx_image img = vxCreateImage(context, 639, 480, VX_DF_IMAGE_UYVY);
 * vx_status status = vxGetStatus((vx_reference)img);
 * // status == VX_ERROR_INVALID_DIMENSIONS
 * vxReleaseImage(&img);
 * \endcode
 * \pre Appropriate Object Creator function.
 * \post Appropriate Object Release function.
 * \param [in] reference The reference to check for construction errors.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval * Some error occurred, please check enumeration list and constructor.
 * \ingroup group_basic_features
 */
VX_API_ENTRY vx_status VX_API_CALL vxGetStatus(vx_reference reference);

/*!
 * \brief Registers user-defined structures to the context.
 * \param [in] context  The reference to the implementation context.
 * \param [in] size     The size of user struct in bytes.
 * \return A <tt>\ref vx_enum</tt> value that is a type given to the User
 * to refer to their custom structure when declaring a <tt>\ref vx_array</tt>
 * of that structure.
 * \retval VX_TYPE_INVALID If the namespace of types has been exhausted.
 * \note This call should only be used once within the lifetime of a context for
 * a specific structure.
 * \ingroup group_adv_array
 */
VX_API_ENTRY vx_enum VX_API_CALL vxRegisterUserStruct(vx_context context, vx_size size);

/*!
 * \brief Allocates and registers user-defined kernel enumeration to a context.
 * The allocated enumeration is from available pool of 4096 enumerations reserved
 * for dynamic allocation from VX_KERNEL_BASE(VX_ID_USER,0).
 * \param [in] context  The reference to the implementation context.
 * \param [out] pKernelEnumId  pointer to return <tt>\ref vx_enum</tt> for user-defined kernel.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE If the context is not a valid <tt>\ref vx_context</tt> reference.
 * \retval VX_ERROR_NO_RESOURCES The enumerations has been exhausted.
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxAllocateUserKernelId(vx_context context, vx_enum * pKernelEnumId);

/*!
 * \brief Allocates and registers user-defined kernel library ID to a context.
 *
 * The allocated library ID is from available pool of library IDs (1..255)
 * reserved for dynamic allocation. The returned libraryId can be used by
 * user-kernel library developer to specify individual kernel enum IDs in
 * a header file, shown below:
 * \code
 * #define MY_KERNEL_ID1(libraryId) (VX_KERNEL_BASE(VX_ID_USER,libraryId) + 0);
 * #define MY_KERNEL_ID2(libraryId) (VX_KERNEL_BASE(VX_ID_USER,libraryId) + 1);
 * #define MY_KERNEL_ID3(libraryId) (VX_KERNEL_BASE(VX_ID_USER,libraryId) + 2);
 * \endcode
 * \param [in] context  The reference to the implementation context.
 * \param [out] pLibraryId  pointer to <tt>\ref vx_enum</tt> for user-kernel libraryId.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_NO_RESOURCES The enumerations has been exhausted.
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxAllocateUserKernelLibraryId(vx_context context, vx_enum * pLibraryId);

/*! \brief Sets the default target of the immediate mode. Upon successful execution of this
 * function any future execution of immediate mode function is attempted on the new default
 * target of the context.
 * \param [in] context  The reference to the implementation context.
 * \param [in] target_enum  The default immediate mode target enum to be set
 * to the <tt>\ref vx_context</tt> object. Use a <tt>\ref vx_target_e</tt>.
 * \param [in] target_string  The target name ASCII string. This contains a valid value
 * when target_enum is set to <tt>\ref VX_TARGET_STRING</tt>, otherwise it is ignored.
 * \ingroup group_context
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Default target set; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE If the context is not a valid <tt>\ref vx_context</tt> reference.
 * \retval VX_ERROR_NOT_SUPPORTED If the specified target is not supported in this context.
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetImmediateModeTarget(vx_context context, vx_enum target_enum, const char* target_string);

/*==============================================================================
 KERNEL
 =============================================================================*/

/*! \brief Loads a library of kernels, called module, into a context.
 *
 * The module must be a dynamic library with by convention, two exported functions
 * named <tt>vxPublishKernels</tt> and <tt>vxUnpublishKernels</tt>.
 *
 * <tt>vxPublishKernels</tt> must have type <tt>\ref vx_publish_kernels_f</tt>,
 * and must add kernels to the context by calling <tt>\ref vxAddUserKernel</tt>
 * for each new kernel. <tt>vxPublishKernels</tt> is called by <tt>\ref vxLoadKernels</tt>.
 *
 * <tt>vxUnpublishKernels</tt> must have type <tt>\ref vx_unpublish_kernels_f</tt>,
 * and must remove kernels from the context by calling <tt>\ref vxRemoveKernel</tt>
 * for each kernel the <tt>vxPublishKernels</tt> has added.
 * <tt>vxUnpublishKernels</tt> is called by <tt>\ref vxUnloadKernels</tt>.
 *
 * \note When all references to loaded kernels are released, the module
 * may be automatically unloaded.
 * \param [in] context The reference to the context the kernels must be added to.
 * \param [in] module The short name of the module to load. On systems where
 * there are specific naming conventions for modules, the name passed
 * should ignore such conventions. For example: \c libxyz.so should be
 * passed as just \c xyz and the implementation will <i>do the right thing</i> that
 * the platform requires.
 * \note This API uses the system pre-defined paths for modules.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE context is not a valid <tt>\ref vx_context</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If any of the other parameters are incorrect.
 * \ingroup group_user_kernels
 * \see vxGetKernelByName
 */
VX_API_ENTRY vx_status VX_API_CALL vxLoadKernels(vx_context context, const vx_char *module);

/*! \brief Unloads all kernels from the OpenVX context that had been loaded from
 * the module using the \ref vxLoadKernels function.
 *
 * The kernel unloading is performed by calling the <tt>vxUnpublishKernels</tt>
 * exported function of the module.
 * \note <tt>vxUnpublishKernels</tt> is defined in the description of
 * <tt>\ref vxLoadKernels</tt>.
 *
 * \param [in] context The reference to the context the kernels must be removed from.
 * \param [in] module The short name of the module to unload. On systems where
 * there are specific naming conventions for modules, the name passed
 * should ignore such conventions. For example: \c libxyz.so should be
 * passed as just \c xyz and the implementation will <i>do the right thing</i>
 * that the platform requires.
 * \note This API uses the system pre-defined paths for modules.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE context is not a valid <tt>\ref vx_context</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If any of the other parameters are
 incorrect.
 * \ingroup group_user_kernels
 * \see vxLoadKernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxUnloadKernels(vx_context context, const vx_char *module);

/*! \brief Obtains a reference to a kernel using a string to specify the name.
 * \details User Kernels follow a "dotted" heirarchical syntax. For example:
 * "com.company.example.xyz". The following are strings specifying the kernel names:

 * org.khronos.openvx.color_convert

 * org.khronos.openvx.channel_extract

 * org.khronos.openvx.channel_combine

 * org.khronos.openvx.sobel_3x3

 * org.khronos.openvx.magnitude

 * org.khronos.openvx.phase

 * org.khronos.openvx.scale_image

 * org.khronos.openvx.table_lookup

 * org.khronos.openvx.histogram

 * org.khronos.openvx.equalize_histogram

 * org.khronos.openvx.absdiff

 * org.khronos.openvx.mean_stddev

 * org.khronos.openvx.threshold

 * org.khronos.openvx.integral_image

 * org.khronos.openvx.dilate_3x3

 * org.khronos.openvx.erode_3x3

 * org.khronos.openvx.median_3x3

 * org.khronos.openvx.box_3x3

 * org.khronos.openvx.gaussian_3x3

 * org.khronos.openvx.custom_convolution

 * org.khronos.openvx.gaussian_pyramid

 * org.khronos.openvx.accumulate

 * org.khronos.openvx.accumulate_weighted

 * org.khronos.openvx.accumulate_square

 * org.khronos.openvx.minmaxloc

 * org.khronos.openvx.convertdepth

 * org.khronos.openvx.canny_edge_detector

 * org.khronos.openvx.and

 * org.khronos.openvx.or

 * org.khronos.openvx.xor

 * org.khronos.openvx.not

 * org.khronos.openvx.multiply

 * org.khronos.openvx.add

 * org.khronos.openvx.subtract

 * org.khronos.openvx.warp_affine

 * org.khronos.openvx.warp_perspective

 * org.khronos.openvx.harris_corners

 * org.khronos.openvx.fast_corners

 * org.khronos.openvx.optical_flow_pyr_lk

 * org.khronos.openvx.remap

 * org.khronos.openvx.halfscale_gaussian

 * org.khronos.openvx.laplacian_pyramid

 * org.khronos.openvx.laplacian_reconstruct

 * org.khronos.openvx.non_linear_filter

 * org.khronos.openvx.match_template

 * org.khronos.openvx.lbp

 * org.khronos.openvx.hough_lines_p

 * org.khronos.openvx.tensor_multiply
 
 * org.khronos.openvx.tensor_add
 
 * org.khronos.openvx.tensor_subtract
 
 * org.khronos.openvx.tensor_table_lookup
 
 * org.khronos.openvx.tensor_transpose
 
 * org.khronos.openvx.tensor_convert_depth
 
 * org.khronos.openvx.tensor_matrix_multiply
 
 * org.khronos.openvx.copy
 
 * org.khronos.openvx.non_max_suppression
 
 * org.khronos.openvx.scalar_operation
 
 * org.khronos.openvx.hog_features
 
 * org.khronos.openvx.hog_cells
 
 * org.khronos.openvx.bilateral_filter

 * org.khronos.openvx.select

 * org.khronos.openvx.min

 * org.khronos.openvx.max

 * \param [in] context The reference to the implementation context.
 * \param [in] name The string of the name of the kernel to get.
 * \return A kernel reference. Any possible errors preventing a successful
 * completion of the function should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_kernel
 * \pre <tt>\ref vxLoadKernels</tt> if the kernel is not provided by the
 * OpenVX implementation.
 * \note User Kernels should follow a "dotted" hierarchical syntax. For example:
 * "com.company.example.xyz".
 */
VX_API_ENTRY vx_kernel VX_API_CALL vxGetKernelByName(vx_context context, const vx_char *name);

/*! \brief Obtains a reference to the kernel using the <tt>\ref vx_kernel_e</tt> enumeration.
 * \details Enum values above the standard set are assumed to apply to
 * loaded libraries.
 * \param [in] context The reference to the implementation context.
 * \param [in] kernel A value from <tt>\ref vx_kernel_e</tt> or a vendor or client-defined value.
 * \return A <tt>\ref vx_kernel</tt> reference. Any possible errors preventing a successful completion
 * of the function should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_kernel
 * \pre <tt>\ref vxLoadKernels</tt> if the kernel is not provided by the
 * OpenVX implementation.
 */
VX_API_ENTRY vx_kernel VX_API_CALL vxGetKernelByEnum(vx_context context, vx_enum kernel);

/*! \brief This allows the client to query the kernel to get information about
 * the number of parameters, enum values, etc.
 * \param [in] kernel The kernel reference to query.
 * \param [in] attribute The attribute to query. Use a <tt>\ref vx_kernel_attribute_e</tt>.
 * \param [out] ptr The pointer to the location at which to store the resulting value.
 * \param [in] size The size of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE kernel is not a valid <tt>\ref vx_kernel</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If any of the other parameters are incorrect.
 * \retval VX_ERROR_NOT_SUPPORTED If the attribute value is not supported in this implementation.
 * \ingroup group_kernel
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryKernel(vx_kernel kernel, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Release the reference to the kernel.
 * The object may not be garbage collected until its total reference count is zero.
 * \param [in] kernel The pointer to the kernel reference to release.
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE kernel is not a valid <tt>\ref vx_kernel</tt> reference.
 * \ingroup group_kernel
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseKernel(vx_kernel *kernel);

/*! \brief Allows users to add custom kernels to a context at run-time.
 * \param [in] context The reference to the context the kernel must be added to.
 * \param [in] name The string to use to match the kernel.
 * \param [in] enumeration The enumerated value of the kernel to be used by clients.
 * \param [in] func_ptr The process-local function pointer to be invoked.
 * \param [in] numParams The number of parameters for this kernel.
 * \param [in] validate The pointer to <tt>\ref vx_kernel_validate_f</tt>, which validates
 * parameters to this kernel.
 * \param [in] init The kernel initialization function.
 * \param [in] deinit The kernel de-initialization function.
 * \return A <tt>\ref vx_kernel</tt> reference. Any possible errors
 * preventing a successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_kernel VX_API_CALL vxAddUserKernel(vx_context context,
                             const vx_char name[VX_MAX_KERNEL_NAME],
                             vx_enum enumeration,
                             vx_kernel_f func_ptr,
                             vx_uint32 numParams,
                             vx_kernel_validate_f validate,
                             vx_kernel_initialize_f init,
                             vx_kernel_deinitialize_f deinit);

/*! \brief This API is called after all parameters have been added to the
 * kernel and the kernel is \e ready to be used. Notice that the reference to the kernel created
 * by vxAddUserKernel is still valid after the call to vxFinalizeKernel.
 * If an error occurs, the kernel is not available for usage by the clients of OpenVX. Typically
 * this is due to a mismatch between the number of parameters requested and given.
 * \param [in] kernel The reference to the loaded kernel from <tt>\ref vxAddUserKernel</tt>.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE kernel is not a valid <tt>\ref vx_kernel</tt> reference.
 * \pre <tt>\ref vxAddUserKernel</tt> and <tt>\ref vxAddParameterToKernel</tt>
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxFinalizeKernel(vx_kernel kernel);

/*! \brief Allows users to set the signatures of the custom kernel.
 * \param [in] kernel The reference to the kernel added with <tt>\ref vxAddUserKernel</tt>.
 * \param [in] index The index of the parameter to add.
 * \param [in] dir The direction of the parameter. This must be either <tt>\ref VX_INPUT</tt> or
 * <tt>\ref VX_OUTPUT</tt>. <tt>\ref VX_BIDIRECTIONAL</tt> is not supported for this function.
 * \param [in] data_type The type of parameter. This must be a value from <tt>\ref vx_type_e</tt>.
 * \param [in] state The state of the parameter (required or not). This must be a value from <tt>\ref vx_parameter_state_e</tt>.
 * \return A <tt>\ref vx_status_e</tt> enumerated value.
 * \retval VX_SUCCESS Parameter is successfully set on kernel; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE kernel is not a valid <tt>\ref vx_kernel</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If the parameter is not valid for any reason.
 * \pre <tt>\ref vxAddUserKernel</tt>
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxAddParameterToKernel(vx_kernel kernel, vx_uint32 index, vx_enum dir, vx_enum data_type, vx_enum state);

/*! \brief Removes a custom kernel from its context and releases it.
 * \param [in] kernel The reference to the kernel to remove. Returned from <tt>\ref vxAddUserKernel</tt>.
 * \note Any kernel enumerated in the base standard
 * cannot be removed; only kernels added through <tt>\ref vxAddUserKernel</tt> can
 * be removed.
 * \return A <tt>\ref vx_status_e</tt> enumeration. The function returns to the
 * application full control over the memory resources provided at the kernel creation time.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE kernel is not a valid <tt>\ref vx_kernel</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS If a base kernel is passed in.
 * \retval VX_FAILURE If the application has not released all references to the kernel
 * object OR if the application has not released all references to a node that is using
 * this kernel OR if the application has not released all references to a graph which
 * has nodes that is using this kernel.
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxRemoveKernel(vx_kernel kernel);

/*! \brief Sets kernel attributes.
 * \param [in] kernel The reference to the kernel.
 * \param [in] attribute The enumeration of the attributes. See <tt>\ref vx_kernel_attribute_e</tt>.
 * \param [in] ptr The pointer to the location from which to read the attribute.
 * \param [in] size The size in bytes of the data area indicated by \a ptr in bytes.
 * \note After a kernel has been passed to <tt>\ref vxFinalizeKernel</tt>, no attributes
 * can be altered.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE kernel is not a valid <tt>\ref vx_kernel</tt> reference.
 * \ingroup group_user_kernels
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetKernelAttribute(vx_kernel kernel, vx_enum attribute, const void *ptr, vx_size size);

/*! \brief Retrieves a <tt>\ref vx_parameter</tt> from a <tt>\ref vx_kernel</tt>.
 * \param [in] kernel The reference to the kernel.
 * \param [in] index The index of the parameter.
 * \return A <tt>\ref vx_parameter</tt> reference. Any possible errors preventing a
 * successful completion of the function should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_parameter
 */
VX_API_ENTRY vx_parameter VX_API_CALL vxGetKernelParameterByIndex(vx_kernel kernel, vx_uint32 index);

/*==============================================================================
 GRAPH
 =============================================================================*/

/*! \brief Creates an empty graph.
 * \param [in] context The reference to the implementation context.
 * \returns A graph reference <tt>\ref vx_graph</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_graph VX_API_CALL vxCreateGraph(vx_context context);

/*! \brief Releases a reference to a graph.
 * The object may not be garbage collected until its total reference count is zero.
 * Once the reference count is zero, all node references in the graph are automatically
 * released as well. Releasing the graph will only release the nodes if the nodes were
 * not previously released by the application. Data referenced by those nodes may not
 * be released as the user may still have references to the data.
 * \param [in] graph The pointer to the graph to release.
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseGraph(vx_graph *graph);

/*! \brief Verifies the state of the graph before it is executed.
 * This is useful to catch programmer errors and contract errors. If not verified,
 * the graph verifies before being processed.
 * \pre Memory for data objects is not guarenteed to exist before
 * this call. \post After this call data objects exist unless
 * the implementation optimized them out.
 * \param [in] graph The reference to the graph to verify.
 * \return A status code for graphs with more than one error; it is
 * undefined which error will be returned. Register a log callback using <tt>\ref vxRegisterLogCallback</tt>
 * to receive each specific error in the graph.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference.
 * \retval VX_ERROR_MULTIPLE_WRITERS If the graph contains more than one writer
 * to any data object.
 * \retval VX_ERROR_INVALID_NODE If a node in the graph is invalid or failed be created.
 * \retval VX_ERROR_INVALID_GRAPH If the graph contains cycles or some other invalid topology.
 * \retval VX_ERROR_INVALID_TYPE If any parameter on a node is given the wrong type.
 * \retval VX_ERROR_INVALID_VALUE If any value of any parameter is out of bounds of specification.
 * \retval VX_ERROR_INVALID_FORMAT If the image format is not compatible.
 * \ingroup group_graph
 * \see vxProcessGraph
 */
VX_API_ENTRY vx_status VX_API_CALL vxVerifyGraph(vx_graph graph);

/*! \brief This function causes the synchronous processing of a graph. If the graph
 * has not been verified, then the implementation verifies the graph
 * immediately. If verification fails this function returns a status
 * identical to what <tt>\ref vxVerifyGraph</tt> would return. After
 * the graph verfies successfully then processing occurs. If the graph was
 * previously verified via <tt>\ref vxVerifyGraph</tt> or <tt>\ref vxProcessGraph</tt>
 * then the graph is processed. This function blocks until the graph is completed.
 * \param [in] graph The graph to execute.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Graph has been processed; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference.
 * \retval VX_FAILURE A catastrophic error occurred during processing.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_status VX_API_CALL vxProcessGraph(vx_graph graph);
VX_API_ENTRY vx_status VX_API_CALL vxProcessSubGraph(vx_graph graph, int start_blk_idx, int blk_count);


/*! \brief Allows the user to query attributes of the Graph.
 * \param [in] graph The reference to the created graph.
 * \param [in] attribute The <tt>\ref vx_graph_attribute_e</tt> type needed.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size in bytes of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryGraph(vx_graph graph, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Allows the attributes of the Graph to be set to the provided value.
 * \param [in] graph The reference to the graph.
 * \param [in] attribute The <tt>\ref vx_graph_attribute_e</tt> type needed.
 * \param [in] ptr The location from which to read the value.
 * \param [in] size The size in bytes of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphAttribute(vx_graph graph, vx_enum attribute, const void *ptr, vx_size size);

/*! \brief Adds the given parameter extracted from a <tt>\ref vx_node</tt> to the graph.
 * \param [in] graph The graph reference that contains the node.
 * \param [in] parameter The parameter reference to add to the graph from the node.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Parameter added to Graph; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference or parameter is not a valid <tt>\ref vx_parameter</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS The parameter is of a node not in this
 * graph.
 * \ingroup group_graph_parameters
 */
VX_API_ENTRY vx_status VX_API_CALL vxAddParameterToGraph(vx_graph graph, vx_parameter parameter);

/*! \brief Sets a reference to the parameter on the graph. The implementation
 * must set this parameter on the originating node as well.
 * \param [in] graph The graph reference.
 * \param [in] index The parameter index.
 * \param [in] value The reference to set to the parameter.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Parameter set to Graph; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference or
 * value is not a valid <tt>\ref vx_reference</tt>.
 * \retval VX_ERROR_INVALID_PARAMETERS The parameter index is out of bounds or the
 * dir parameter is incorrect.
 * \ingroup group_graph_parameters
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetGraphParameterByIndex(vx_graph graph, vx_uint32 index, vx_reference value);

/*! \brief Retrieves a <tt>\ref vx_parameter</tt> from a <tt>\ref vx_graph</tt>.
 * \param [in] graph The graph.
 * \param [in] index The index of the parameter.
 * \return <tt>\ref vx_parameter</tt> reference. Any possible errors preventing a successful
 * function completion should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_graph_parameters
 */
VX_API_ENTRY vx_parameter VX_API_CALL vxGetGraphParameterByIndex(vx_graph graph, vx_uint32 index);

/*! \brief Returns a Boolean to indicate the state of graph verification.
 * \param [in] graph The reference to the graph to check.
 * \return A <tt>\ref vx_bool</tt> value.
 * \retval vx_true_e The graph is verified.
 * \retval vx_false_e The graph is not verified. It must be verified before
 * execution either through <tt>\ref vxVerifyGraph</tt> or automatically through
 * <tt>\ref vxProcessGraph</tt> or <tt>\ref vxScheduleGraph</tt>.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_bool VX_API_CALL vxIsGraphVerified(vx_graph graph);

/*==============================================================================
 NODE
 =============================================================================*/

/*! \brief Creates a reference to a node object for a given kernel.
 * \details This node has no references assigned as parameters after completion.
 * The client is then required to set these parameters manually by <tt>\ref vxSetParameterByIndex</tt>.
 * When clients supply their own node creation functions (for use with User Kernels), this is the API
 * to use along with the parameter setting API.
 * \param [in] graph The reference to the graph in which this node exists.
 * \param [in] kernel The kernel reference to associate with this new node.
 * \returns A node reference <tt>\ref vx_node</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \note A call to this API sets all parameters to NULL.
 * \ingroup group_adv_node
 * \post Call <tt>\ref vxSetParameterByIndex</tt> for as many parameters as needed to be set.
 */
VX_API_ENTRY vx_node VX_API_CALL vxCreateGenericNode(vx_graph graph, vx_kernel kernel);

/*! \brief Allows a user to query information out of a node.
 * \param [in] node The reference to the node to query.
 * \param [in] attribute Use <tt>\ref vx_node_attribute_e</tt> value to query for information.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size in bytesin bytes of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS The type or size is incorrect.
 * \ingroup group_node
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryNode(vx_node node, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Allows a user to set attribute of a node before Graph Validation.
 * \param [in] node The reference to the node to set.
 * \param [in] attribute Use <tt>\ref vx_node_attribute_e</tt> value to set the desired attribute.
 * \param [in] ptr The pointer to the desired value of the attribute.
 * \param [in] size The size in bytes of the objects to which \a ptr points.
 * \note Some attributes are inherited from the <tt>\ref vx_kernel</tt>, which was used
 * to create the node. Some of these can be overridden using this API, notably
 * \ref VX_NODE_LOCAL_DATA_SIZE and \ref VX_NODE_LOCAL_DATA_PTR.
 * \ingroup group_node
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS The attribute was set; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS size is not correct for the type needed.
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetNodeAttribute(vx_node node, vx_enum attribute, const void *ptr, vx_size size);

/*! \brief Releases a reference to a Node object.
 * The object may not be garbage collected until its total reference count is zero.
 * \param [in] node The pointer to the reference of the node to release.
 * \ingroup group_node
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseNode(vx_node *node);

/*! \brief Removes a Node from its parent Graph and releases it.
 * \param [in] node The pointer to the node to remove and release.
 * \ingroup group_node
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxRemoveNode(vx_node *node);

/*! \brief Assigns a callback to a node.
 * If a callback already exists in this node, this function must return an error
 * and the user may clear the callback by passing a NULL pointer as the callback.
 * \param [in] node The reference to the node.
 * \param [in] callback The callback to associate with completion of this
 * specific node.
 * \warning This must be used with <b><i>extreme</i></b> caution as it can \e ruin
 * optimizations in the power/performance efficiency of a graph.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Callback assigned; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference.
 * \ingroup group_node_callback
 */
VX_API_ENTRY vx_status VX_API_CALL vxAssignNodeCallback(vx_node node, vx_nodecomplete_f callback);

/*! \brief Retrieves the current node callback function pointer set on the node.
 * \param [in] node The reference to the <tt>\ref vx_node</tt> object.
 * \ingroup group_node_callback
 * \return vx_nodecomplete_f The pointer to the callback function.
 * \retval NULL No callback is set.
 * \retval * The node callback function.
 */
VX_API_ENTRY vx_nodecomplete_f VX_API_CALL vxRetrieveNodeCallback(vx_node node);

/*! \brief Sets the node target to the provided value. A success invalidates the graph
 * that the node belongs to (<tt>\ref vxVerifyGraph</tt> must be called before the next execution)
 * \param [in] node  The reference to the <tt>\ref vx_node</tt> object.
 * \param [in] target_enum  The target enum to be set to the <tt>\ref vx_node</tt> object.
 * Use a <tt>\ref vx_target_e</tt>.
 * \param [in] target_string  The target name ASCII string. This contains a valid value
 * when target_enum is set to <tt>\ref VX_TARGET_STRING</tt>, otherwise it is ignored.
 * \ingroup group_node
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Node target set; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference.
 * \retval VX_ERROR_NOT_SUPPORTED If the node kernel is not supported by the specified target.
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetNodeTarget(vx_node node, vx_enum target_enum, const char* target_string);

/*! \brief Creates replicas of the same node first_node to process a set of objects
 * stored in <tt>\ref vx_pyramid</tt> or <tt>\ref vx_object_array</tt>.
 * first_node needs to have as parameter levels 0 of a <tt>\ref vx_pyramid</tt> or the index 0 of a <tt>\ref vx_object_array</tt>.
 * Replica nodes are not accessible by the application through any means. An application request for removal of
 * first_node from the graph will result in removal of all replicas. Any change of parameter or attribute of
 * first_node will be propagated to the replicas. <tt>\ref vxVerifyGraph</tt> shall enforce consistency of parameters and attributes
 * in the replicas.
 * \param [in] graph The reference to the graph.
 * \param [in] first_node The reference to the node in the graph that will be replicated.
 * \param [in] replicate an array of size equal to the number of node parameters, vx_true_e for the parameters
 * that should be iterated over (should be a reference to a vx_pyramid or a vx_object_array),
 * vx_false_e for the parameters that should be the same across replicated nodes and for optional
 * parameters that are not used. Should be vx_true_e for all output and bidirectional parameters.
 * \param [in] number_of_parameters number of elements in the replicate array
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference, or first_node is not a
 * valid <tt>\ref vx_node</tt> reference.
 * \retval VX_ERROR_NOT_COMPATIBLE At least one of replicated parameters is not of level 0 of a pyramid or at index 0 of an object array.
 * \retval VX_FAILURE If the node does not belong to the graph, or the number of objects in the parent objects of inputs and output are not the same.
 * \ingroup group_node
 */
VX_API_ENTRY vx_status VX_API_CALL vxReplicateNode(vx_graph graph, vx_node first_node, vx_bool replicate[], vx_uint32 number_of_parameters);

/*==============================================================================
 PARAMETER
 =============================================================================*/

/*! \brief Retrieves a <tt>\ref vx_parameter</tt> from a <tt>\ref vx_node</tt>.
 * \param [in] node The node from which to extract the parameter.
 * \param [in] index The index of the parameter to which to get a reference.
 * \return A parameter reference <tt>\ref vx_parameter</tt>. Any possible errors preventing a successful
 * completion of the function should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_parameter
 */
VX_API_ENTRY vx_parameter VX_API_CALL vxGetParameterByIndex(vx_node node, vx_uint32 index);

/*! \brief Releases a reference to a parameter object.
 * The object may not be garbage collected until its total reference count is zero.
 * \param [in] param The pointer to the parameter to release.
 * \ingroup group_parameter
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE param is not a valid <tt>\ref vx_parameter</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseParameter(vx_parameter *param);

/*! \brief Sets the specified parameter data for a kernel on the node.
 * \param [in] node The node that contains the kernel.
 * \param [in] index The index of the parameter desired.
 * \param [in] value The desired value of the parameter.
 * \note A user may not provide a NULL value for a mandatory parameter of this API.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE node is not a valid <tt>\ref vx_node</tt> reference, or value
 * is not a valid <tt>\ref vx_reference</tt> reference.
 * \ingroup group_parameter
 * \see vxSetParameterByReference
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetParameterByIndex(vx_node node, vx_uint32 index, vx_reference value);

/*! \brief Associates a parameter reference and a data reference with a kernel
 * on a node.
 * \param [in] parameter The reference to the kernel parameter.
 * \param [in] value The value to associate with the kernel parameter.
 * \note A user may not provide a NULL value for a mandatory parameter of this API.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE parameter is not a valid <tt>\ref vx_parameter</tt> reference,
 * or value is not a valid <tt>\ref vx_reference</tt> reference..
 * \ingroup group_parameter
 * \see vxGetParameterByIndex
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetParameterByReference(vx_parameter parameter, vx_reference value);

/*! \brief Allows the client to query a parameter to determine its meta-information.
 * \param [in] parameter The reference to the parameter.
 * \param [in] attribute The attribute to query. Use a <tt>\ref vx_parameter_attribute_e</tt>.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size in bytes of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE parameter is not a valid <tt>\ref vx_parameter</tt> reference.
 * \ingroup group_parameter
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryParameter(vx_parameter parameter, vx_enum attribute, void *ptr, vx_size size);

/*==============================================================================
 SCALAR
 =============================================================================*/

/*! \brief Creates a reference to a scalar object. Also see \ref sub_node_parameters.
 * \param [in] context The reference to the system context.
 * \param [in] data_type The type of data to hold. Must be greater than
 * <tt>\ref VX_TYPE_INVALID</tt> and less than or equal to <tt>\ref VX_TYPE_VENDOR_STRUCT_END</tt>.
 * Or must be a <tt>\ref vx_enum</tt> returned from <tt>\ref vxRegisterUserStruct</tt>.
 * \param [in] ptr The pointer to the initial value of the scalar.
 * \ingroup group_scalar
 * \returns A scalar reference <tt>\ref vx_scalar</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_scalar VX_API_CALL vxCreateScalar(vx_context context, vx_enum data_type, const void *ptr);

/*! \brief Creates a reference to a scalar object. Also see \ref sub_node_parameters.
 * \param [in] context The reference to the system context.
 * \param [in] data_type The type of data to hold. Must be greater than
 * <tt>\ref VX_TYPE_INVALID</tt> and less than or equal to <tt>\ref VX_TYPE_VENDOR_STRUCT_END</tt>.
 * Or must be a <tt>\ref vx_enum</tt> returned from <tt>\ref vxRegisterUserStruct</tt>.
 * \param [in] ptr The pointer to the initial value of the scalar.
 * \param [in] size Size of data at ptr in bytes.
 * \ingroup group_scalar
 * \returns A scalar reference <tt>\ref vx_scalar</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_scalar VX_API_CALL vxCreateScalarWithSize(vx_context context, vx_enum data_type, const void *ptr, vx_size size);
VX_API_ENTRY vx_scalar VX_API_CALL vxCreateGraphScalarWithSize(vx_graph graph, vx_enum data_type, const void* ptr, vx_size size);

/*! \brief Creates an opaque reference to a scalar object with no direct user access.
 * \param [in] graph The reference to the parent graph.
 * \param [in] data_type The type of data to hold. Must be greater than
 * <tt>\ref VX_TYPE_INVALID</tt> and less than or equal to <tt>\ref VX_TYPE_VENDOR_STRUCT_END</tt>.
 * Or must be a <tt>\ref vx_enum</tt> returned from <tt>\ref vxRegisterUserStruct</tt>.
 * \see <tt>\ref vxCreateScalar</tt>
 * \ingroup group_scalar
 * \returns A scalar reference <tt>\ref vx_scalar</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 */
VX_API_ENTRY vx_scalar VX_API_CALL vxCreateVirtualScalar(vx_graph graph, vx_enum data_type);

/*! \brief Releases a reference to a scalar object.
 * The object may not be garbage collected until its total reference count is zero.
 * \param [in] scalar The pointer to the scalar to release.
 * \ingroup group_scalar
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE scalar is not a valid <tt>\ref vx_scalar</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseScalar(vx_scalar *scalar);

/*! \brief Queries attributes from a scalar.
 * \param [in] scalar The scalar object.
 * \param [in] attribute The enumeration to query. Use a <tt>\ref vx_scalar_attribute_e</tt> enumeration.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE scalar is not a valid <tt>\ref vx_scalar</tt> reference.
 * \ingroup group_scalar
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryScalar(vx_scalar scalar, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Allows the application to copy from/into a scalar object.
 * \param [in] scalar The reference to the scalar object that is the source or the
 * destination of the copy.
 * \param [in] user_ptr The address of the memory location where to store the requested data
 * if the copy was requested in read mode, or from where to get the data to store into the
 * scalar object if the copy was requested in write mode. In the user memory, the scalar is
 * a variable of the type corresponding to <tt>\ref VX_SCALAR_TYPE</tt>.
 * The accessible memory must be large enough to contain this variable.
 * \param [in] usage This declares the effect of the copy with regard to the scalar object
 * using the <tt>\ref vx_accessor_e</tt> enumeration. Only <tt>\ref VX_READ_ONLY</tt> and <tt>\ref VX_WRITE_ONLY</tt>
 * are supported:
 * \arg <tt>\ref VX_READ_ONLY</tt> means that data are copied from the scalar object into the user memory.
 * \arg <tt>\ref VX_WRITE_ONLY</tt> means that data are copied into the scalar object from the user memory.
 * \param [in] user_mem_type A <tt>\ref vx_memory_type_e</tt> enumeration that specifies
 * the memory type of the memory referenced by the user_addr.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE scalar is not a valid <tt>\ref vx_scalar</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS An other parameter is incorrect.
 * \ingroup group_scalar
 */
VX_API_ENTRY vx_status VX_API_CALL vxCopyScalar(vx_scalar scalar, void *user_ptr, vx_enum usage, vx_enum user_mem_type);

/*! \brief Allows the application to copy from/into a scalar object with size.
 * \param [in] scalar The reference to the scalar object that is the source or the
 * destination of the copy.
 * \param [in] size The size in bytes of the container to which \a user_ptr points.
 * \param [in] user_ptr The address of the memory location where to store the requested data
 * if the copy was requested in read mode, or from where to get the data to store into the
 * scalar object if the copy was requested in write mode. In the user memory, the scalar is
 * a variable of the type corresponding to <tt>\ref VX_SCALAR_TYPE</tt>.
 * The accessible memory must be large enough to contain this variable.
 * \param [in] usage This declares the effect of the copy with regard to the scalar object
 * using the <tt>\ref vx_accessor_e</tt> enumeration. Only <tt>\ref VX_READ_ONLY</tt> and <tt>\ref VX_WRITE_ONLY</tt>
 * are supported:
 * \arg <tt>\ref VX_READ_ONLY</tt> means that data are copied from the scalar object into the user memory.
 * \arg <tt>\ref VX_WRITE_ONLY</tt> means that data are copied into the scalar object from the user memory.
 * \param [in] user_mem_type A <tt>\ref vx_memory_type_e</tt> enumeration that specifies
 * the memory type of the memory referenced by the user_addr.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_ERROR_INVALID_REFERENCE The scalar reference is not actually a scalar reference.
 * \retval VX_ERROR_INVALID_PARAMETERS An other parameter is incorrect.
 * \ingroup group_scalar
 */
VX_API_ENTRY vx_status VX_API_CALL vxCopyScalarWithSize(vx_scalar scalar, vx_size size, void *user_ptr, vx_enum usage, vx_enum user_mem_type);

/*==============================================================================
 REFERENCE
 =============================================================================*/

/*! \brief Queries any reference type for some basic information like count or type.
 * \param [in] ref The reference to query.
 * \param [in] attribute The value for which to query. Use <tt>\ref vx_reference_attribute_e</tt>.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size in bytes of the container to which ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE ref is not a valid <tt>\ref vx_reference</tt> reference.
 * \ingroup group_reference
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryReference(vx_reference ref, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Releases a reference. The reference may potentially refer to multiple OpenVX objects of different types.
 * This function can be used instead of calling a specific release function for each individual object type
 * (e.g. vxRelease<object>). The object will not be destroyed until its total reference count is zero.
 * \note After returning from this function the reference is zeroed.
 * \param [in] ref_ptr The pointer to the reference of the object to release.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE ref_ptr is not a valid <tt>\ref vx_reference</tt> reference.
 * \ingroup group_reference
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseReference(vx_reference* ref_ptr);

/*!
 * \brief Increments the reference counter of an object
 * This function is used to express the fact that the OpenVX object is referenced
 * multiple times by an application. Each time this function is called for
 * an object, the application will need to release the object one additional
 * time before it can be destructed
 * \param [in] ref The reference to retain.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE ref is not a valid <tt>\ref vx_reference</tt> reference.
 * \ingroup group_reference
 */
VX_API_ENTRY vx_status VX_API_CALL vxRetainReference(vx_reference ref);
VX_API_ENTRY vx_status VX_API_CALL vxRetainTensor(vx_tensor tensor);
VX_API_ENTRY vx_status VX_API_CALL vxRetainNode(vx_node node);

/*! \brief Name a reference
 * \ingroup group_reference
 *
 * This function is used to associate a name to a referenced object. This name
 * can be used by the OpenVX implementation in log messages and any
 * other reporting mechanisms.
 *
 * The OpenVX implementation will not check if the name is unique in
 * the reference scope (context or graph). Several references can then
 * have the same name.
 *
 * \param [in] ref The reference to the object to be named.
 * \param [in] name Pointer to the '\0' terminated string that identifies
 *             the referenced object.
 *             The string is copied by the function so that it
 *             stays the property of the caller.
 *             NULL means that the reference is not named.
 *             The length of the string shall be lower than VX_MAX_REFERENCE_NAME bytes.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE ref is not a valid <tt>\ref vx_reference</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetReferenceName(vx_reference ref, const vx_char *name);

/*==============================================================================
 DELAY
 =============================================================================*/

/*! \brief Queries a <tt>\ref vx_delay</tt> object attribute.
 * \param [in] delay The reference to a delay object.
 * \param [in] attribute The attribute to query. Use a <tt>\ref vx_delay_attribute_e</tt> enumeration.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE delay is not a valid <tt>\ref vx_delay</tt> reference.
 * \ingroup group_delay
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryDelay(vx_delay delay, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Releases a reference to a delay object.
 * The object may not be garbage collected until its total reference count is zero.
 * \param [in] delay The pointer to the delay object reference to release.
 * \post After returning from this function the reference is zeroed.
 * \ingroup group_delay
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE delay is not a valid <tt>\ref vx_delay</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseDelay(vx_delay *delay);


/*! \brief Creates a Delay object.
 * \details This function creates a delay object with \p num_slots slots. Each slot
 * contains a clone of the exemplar. The clones only inherit the metadata of the
 * exemplar. The data content of the exemplar is ignored and the clones have their
 * data undefined at delay creation time.
 * The function does not alter the exemplar. Also, it doesn't retain or release the
 * reference to the exemplar.
 * \note For the definition of metadata attributes see \ref vxSetMetaFormatAttribute.
 * \param [in] context The reference to the context.
 * \param [in] exemplar The exemplar object. Supported exemplar object types are:<br>
 * \arg \ref VX_TYPE_ARRAY
 * \arg \ref VX_TYPE_CONVOLUTION
 * \arg \ref VX_TYPE_DISTRIBUTION
 * \arg \ref VX_TYPE_IMAGE
 * \arg \ref VX_TYPE_LUT
 * \arg \ref VX_TYPE_MATRIX
 * \arg \ref VX_TYPE_OBJECT_ARRAY
 * \arg \ref VX_TYPE_PYRAMID
 * \arg \ref VX_TYPE_REMAP
 * \arg \ref VX_TYPE_SCALAR
 * \arg \ref VX_TYPE_THRESHOLD
 * \arg \ref VX_TYPE_TENSOR
 * \param [in] num_slots The number of objects in the delay. This value must be greater than zero.
 * \returns A delay reference <tt>\ref vx_delay</tt>. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_delay
 */
VX_API_ENTRY vx_delay VX_API_CALL vxCreateDelay(vx_context context,
                              vx_reference exemplar,
                              vx_size num_slots);

/*! \brief Retrieves a reference to a delay slot object.
 * \param [in] delay The reference to the delay object.
 * \param [in] index The index of the delay slot from which to extract the object reference.
 * \return <tt>\ref vx_reference</tt>. Any possible errors preventing a successful
 * completion of the function should be checked using <tt>\ref vxGetStatus</tt>.
 * \note The delay index is in the range \f$ [-count+1,0] \f$. 0 is always the
 * \e current object.
 * \ingroup group_delay
 * \note A reference retrieved with this function must not be given to its associated
 * release API (e.g. <tt>\ref vxReleaseImage</tt>) unless <tt>\ref vxRetainReference</tt> is used.
 */
VX_API_ENTRY vx_reference VX_API_CALL vxGetReferenceFromDelay(vx_delay delay, vx_int32 index);

/*! \brief Shifts the internal delay ring by one.
 *
 * This function performs a shift of the internal delay ring by one. This means that,
 * the data originally at index 0 move to index -1 and so forth until index
 * \f$ -count+1 \f$. The data originally at index \f$ -count+1 \f$ move to index 0.
 * Here \f$ count \f$ is the number of slots in delay ring.
 * When a delay is aged, any graph making use of this delay (delay object itself or data
 * objects in delay slots) gets its data automatically updated accordingly.
 * \param [in] delay
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS Delay was aged; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE delay is not a valid <tt>\ref vx_delay</tt> reference.
 * \ingroup group_delay
 */
VX_API_ENTRY vx_status VX_API_CALL vxAgeDelay(vx_delay delay);

/*! \brief Register a delay for auto-aging.
 *
 * This function registers a delay object to be auto-aged by the graph.
 * This delay object will be automatically aged after each successful completion of
 * this graph. Aging of a delay object cannot be called during graph execution.
 * A graph abandoned due to a node callback will trigger an auto-aging.
 *
 * If a delay is registered for auto-aging multiple times in a same graph,
 * the delay will be only aged a single time at each graph completion.
 * If a delay is registered for auto-aging in multiple graphs, this delay will
 * aged automatically after each successful completion of any of these graphs.
 *
 * \param [in] graph The graph to which the delay is registered for auto-aging.
 * \param [in] delay The delay to automatically age.
 *
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE graph is not a valid <tt>\ref vx_graph</tt> reference, or
 * delay is not a valid <tt>\ref vx_delay</tt> reference.
 * \ingroup group_graph
 */
VX_API_ENTRY vx_status VX_API_CALL vxRegisterAutoAging(vx_graph graph, vx_delay delay);

/*==============================================================================
 META FORMAT
 =============================================================================*/

/*! \brief This function allows a user to set the attributes of a <tt>\ref vx_meta_format</tt> object in a kernel output validator.
 *
 * The \ref vx_meta_format object contains two types of information: data object meta data and
 * some specific information that defines how the valid region of an image changes
 *
 * The meta data attributes that can be set are identified by this list:
 * - \ref vx_image : \ref VX_IMAGE_FORMAT, \ref VX_IMAGE_HEIGHT, \ref VX_IMAGE_WIDTH
 * - \ref vx_array : \ref VX_ARRAY_CAPACITY, \ref VX_ARRAY_ITEMTYPE
 * - \ref vx_pyramid : \ref VX_PYRAMID_FORMAT, \ref VX_PYRAMID_HEIGHT, \ref VX_PYRAMID_WIDTH, \ref VX_PYRAMID_LEVELS, \ref VX_PYRAMID_SCALE
 * - \ref vx_scalar : \ref VX_SCALAR_TYPE
 * - \ref vx_matrix : \ref VX_MATRIX_TYPE, \ref VX_MATRIX_ROWS, \ref VX_MATRIX_COLUMNS
 * - \ref vx_distribution : \ref VX_DISTRIBUTION_BINS, \ref VX_DISTRIBUTION_OFFSET, \ref VX_DISTRIBUTION_RANGE
 * - \ref vx_remap : \ref VX_REMAP_SOURCE_WIDTH, \ref VX_REMAP_SOURCE_HEIGHT, \ref VX_REMAP_DESTINATION_WIDTH, \ref VX_REMAP_DESTINATION_HEIGHT
 * - \ref vx_lut : \ref VX_LUT_TYPE, \ref VX_LUT_COUNT
 * - \ref vx_threshold : \ref VX_THRESHOLD_TYPE, \ref VX_THRESHOLD_INPUT_FORMAT, \ref VX_THRESHOLD_INPUT_FORMAT
 * - \ref vx_object_array : \ref VX_OBJECT_ARRAY_NUMITEMS, \ref VX_OBJECT_ARRAY_ITEMTYPE
 * - \ref vx_tensor : \ref VX_TENSOR_NUMBER_OF_DIMS, \ref VX_TENSOR_DIMS, \ref VX_TENSOR_DATA_TYPE, \ref VX_TENSOR_FIXED_POINT_POSITION
 * - \ref VX_VALID_RECT_CALLBACK
 * \note For vx_image, a specific attribute can be used to specify the valid region evolution. This information is not a meta data.
 *
 * \param [in] meta The reference to the \ref vx_meta_format struct to set
 * \param [in] attribute Use the subset of data object attributes that define the meta data of this object or attributes from <tt>\ref vx_meta_format</tt>.
 * \param [in] ptr The input pointer of the value to set on the meta format object.
 * \param [in] size The size in bytes of the object to which \a ptr points.
 * \ingroup group_user_kernels
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS The attribute was set; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE meta is not a valid <tt>\ref vx_meta_format</tt> reference.
 * \retval VX_ERROR_INVALID_PARAMETERS size was not correct for the type needed.
 * \retval VX_ERROR_NOT_SUPPORTED the object attribute was not supported on the meta format object.
 * \retval VX_ERROR_INVALID_TYPE attribute type did not match known meta format type.
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetMetaFormatAttribute(vx_meta_format meta, vx_enum attribute, const void *ptr, vx_size size);

/*! \brief Set a meta format object from an exemplar data object reference
 *
 * This function sets a \ref vx_meta_format object from the meta data of the exemplar
 *
 * \param [in] meta The meta format object to set
 * \param [in] exemplar The exemplar data object.
 * \ingroup group_user_kernels
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS The meta format was correctly set; any other value indicates failure.
 * \retval VX_ERROR_INVALID_REFERENCE meta is not a valid <tt>\ref vx_meta_format</tt> reference,
 * or exemplar is not a valid <tt>\ref vx_reference</tt> reference.
 */
VX_API_ENTRY vx_status VX_API_CALL vxSetMetaFormatFromReference(vx_meta_format meta, vx_reference exemplar);
/*==============================================================================
    TENSOR DATA FUNCTIONS
=============================================================================*/
/*! \brief Creates an opaque reference to a tensor data buffer.
 * \details Not guaranteed to exist until the <tt>\ref vx_graph</tt> containing it has been verified.
 * Since functions using tensors, need to understand the context of each dimension. We describe a layout of the dimensions in each function using tensors.
 * That layout is not mandatory. It is done specifically to explain the functions and not to mandate layout. Different implementation may have different layout.
 * Therefore the layout description is logical and not physical. It refers to the order of dimensions given in this function.
 * \param [in] context The reference to the implementation context.
 * \param [in] number_of_dims The number of dimensions.
 * \param [in] dims Dimensions sizes in elements.
 * \param [in] data_type The <tt>\ref vx_type_e</tt> that represents the data type of the tensor data elements. 
 * \param [in] fixed_point_position Specifies the fixed point position when the input element type is integer. if 0, calculations are performed in integer math.
 * \return A tensor data reference. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_object_tensor
 */
VX_API_ENTRY vx_tensor VX_API_CALL vxCreateTensor(vx_context context, vx_size number_of_dims, const vx_size * dims, vx_enum data_type,vx_int8 fixed_point_position);

/*! \brief Creates a tensor data from another tensor data given a view. This second
 * reference refers to the data in the original tensor data. Updates to this tensor data
 * updates the parent tensor data. The view must be defined within the dimensions
 * of the parent tensor data.
 * \param [in] tensor The reference to the parent tensor data.
 * \param [in] number_of_dims Number of dimensions in the view. Error return if 0 or greater than number of
 * tensor dimensions. If smaller than number of tensor dimensions, the lower dimensions are assumed.
 * \param [in] view_start View start coordinates
 * \param [in] view_end View end coordinates
 * \return The reference to the sub-tensor. Any possible errors preventing a
 * successful creation should be checked using <tt>\ref vxGetStatus</tt>.
 * \ingroup group_object_tensor
 */
VX_API_ENTRY vx_tensor VX_API_CALL vxCreateTensorFromView(vx_tensor tensor, vx_size number_of_dims, const vx_size * view_start, const vx_size * view_end);

/*! \brief Retrieves various attributes of a tensor data.
 * \param [in] tensor The reference to the tensor data to query.
 * \param [in] attribute The attribute to query. Use a <tt>\ref vx_tensor_attribute_e</tt>.
 * \param [out] ptr The location at which to store the resulting value.
 * \param [in] size The size of the container to which \a ptr points.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors.
 * \retval VX_ERROR_INVALID_REFERENCE If data is not a <tt>\ref vx_tensor</tt>.
 * \retval VX_ERROR_INVALID_PARAMETERS If any of the other parameters are incorrect.
 * \ingroup group_object_tensor
 */
VX_API_ENTRY vx_status VX_API_CALL vxQueryTensor(vx_tensor tensor, vx_enum attribute, void *ptr, vx_size size);

/*! \brief Releases a reference to a tensor data object.
 * The object may not be garbage collected until its total reference count is zero.
 * \param [in] tensor The pointer to the tensor data to release.
 * \post After returning from this function the reference is zeroed.
 * \return A <tt>\ref vx_status_e</tt> enumeration.
 * \retval VX_SUCCESS No errors; all other values indicate failure
 * \retval * An error occurred. See <tt>\ref vx_status_e</tt>.
 * \ingroup group_object_tensor
 */
VX_API_ENTRY vx_status VX_API_CALL vxReleaseTensor(vx_tensor *tensor);

#ifdef  __cplusplus
}
#endif

#endif
