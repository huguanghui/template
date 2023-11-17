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

#ifndef _OPENVX_TYPES_H_
#define _OPENVX_TYPES_H_

/*!
 * \file vx_types.h
 * \brief The type definitions required by OpenVX Library.
 */

#include <stdint.h>
#include <stddef.h>

/*!
 * \internal
 * \def VX_API_ENTRY
 * \brief This is a tag used to identify exported, public API functions as
 * distinct from internal functions, helpers, and other non-public interfaces.
 * It can optionally be defined in the make system according the the compiler and intent.
 * \ingroup group_basic_features
 */

/*!
 * \def VX_API_CALL
 * \brief Defines calling convention for OpenVX API.
 * \ingroup group_basic_features
 */

/*!
 * \def VX_CALLBACK
 * \brief Defines calling convention for user callbacks.
 * \ingroup group_basic_features
 */

#ifndef VX_API_ENTRY
#if defined(_WIN32)
#define VX_API_ENTRY __declspec(dllexport)
#define VX_API_DEPRECATED __declspec(deprecated)
#else
#define VX_API_ENTRY __attribute((visibility("default")))
#define VX_API_DEPRECATED __attribute((deprecated))
#endif
#endif
#ifndef VX_API_CALL
#if defined(_WIN32)
#define VX_API_CALL __stdcall
#else
#define VX_API_CALL
#endif
#endif
#ifndef VX_CALLBACK
#if defined(_WIN32)
#define VX_CALLBACK __stdcall
#else
#define VX_CALLBACK
#endif
#endif

/*! \brief An 8 bit ASCII character.
 * \ingroup group_basic_features
 */
typedef char     vx_char;

/*! \brief An 8-bit unsigned value.
 * \ingroup group_basic_features
 */
typedef uint8_t  vx_uint8;

/*! \brief A 16-bit unsigned value.
 * \ingroup group_basic_features
 */
typedef uint16_t vx_uint16;

/*! \brief A 32-bit unsigned value.
 * \ingroup group_basic_features
 */
typedef uint32_t vx_uint32;

/*! \brief A 64-bit unsigned value.
 * \ingroup group_basic_features
 */
typedef uint64_t vx_uint64;

/*! \brief An 8-bit signed value.
 * \ingroup group_basic_features
 */
typedef int8_t   vx_int8;

/*! \brief A 16-bit signed value.
 * \ingroup group_basic_features
 */
typedef int16_t  vx_int16;

/*! \brief A 32-bit signed value.
 * \ingroup group_basic_features
 */
typedef int32_t  vx_int32;

/*! \brief A 64-bit signed value.
 * \ingroup group_basic_features
 */
typedef int64_t  vx_int64;

typedef uint32_t vx_bitfield;

#if defined(EXPERIMENTAL_PLATFORM_SUPPORTS_16_FLOAT)

/*! \brief A 16-bit float value.
 * \ingroup group_basic_features
 */
typedef hfloat   vx_float16;
#endif

/*! \brief A 32-bit float value.
 * \ingroup group_basic_features
 */
typedef float    vx_float32;

/*! \brief A 64-bit float value (aka double).
 * \ingroup group_basic_features
 */
typedef double   vx_float64;

/*! \brief A generic opaque reference to any object within OpenVX.
 * \details A user of OpenVX should not assume that this can be cast directly to anything;
 * however, any object in OpenVX can be cast back to this for the purposes of
 * querying attributes of the object or for passing the object as a parameter to
 * functions that take a <tt>\ref vx_reference</tt> type.
 * If the API does not take that specific type but may take others, an
 * error may be returned from the API.
 * \ingroup group_reference
 */
typedef struct _vx_reference *vx_reference;

/*! \brief Sets the standard enumeration type size to be a fixed quantity.
 * \details All enumerable fields must use this type as the container to
 * enforce enumeration ranges and sizeof() operations.
 * \ingroup group_basic_features
 */
typedef int32_t vx_enum;

/*! \brief A wrapper of <tt>size_t</tt> to keep the naming convention uniform.
 * \ingroup group_basic_features
 */
typedef size_t vx_size;

/*! \brief Used to hold a VX_DF_IMAGE code to describe the pixel format and color space.
 * \ingroup group_basic_features
 */
typedef uint32_t vx_df_image;

/*! \brief An opaque reference to a scalar.
 * \details A scalar can be up to 64 bits wide.
 * \see vxCreateScalar
 * \ingroup group_scalar
 * \extends vx_reference
 */
typedef struct _vx_scalar *vx_scalar;

/*! \brief An opaque reference to an image.
 * \see vxCreateImage
 * \ingroup group_image
 * \extends vx_reference
 */
typedef struct _vx_image *vx_image;

/*! \brief An opaque reference to the descriptor of a kernel.
 * \see vxGetKernelByName
 * \see vxGetKernelByEnum
 * \ingroup group_kernel
 * \extends vx_reference
 */
typedef struct _vx_kernel *vx_kernel;

/*! \brief An opaque reference to a single parameter.
 * \see vxGetParameterByIndex
 * \ingroup group_parameter
 * \extends vx_reference
 */
typedef struct _vx_parameter *vx_parameter;

/*! \brief An opaque reference to a kernel node.
 * \see vxCreateGenericNode
 * \ingroup group_node
 * \extends vx_reference
 */
typedef struct _vx_node *vx_node;

/*! \brief An opaque reference to a graph
 * \see vxCreateGraph
 * \ingroup group_graph
 * \extends vx_reference
 */
typedef struct _vx_graph *vx_graph;

/*! \brief An opaque reference to the implementation context.
 * \see vxCreateContext
 * \ingroup group_context
 * \extends vx_reference
 */
typedef struct _vx_context *vx_context;

/*! \brief The delay object. This is like a ring buffer of objects that is
 * maintained by the OpenVX implementation.
 * \see vxCreateDelay
 * \extends vx_reference
 * \ingroup group_delay
 */
typedef struct _vx_delay *vx_delay;

/*! \brief The Look-Up Table (LUT) Object.
 * \extends vx_reference
 * \ingroup group_lut
 */
typedef struct _vx_lut *vx_lut;

/*! \brief The Distribution object. This has a user-defined number of bins over
 * a user-defined range (within a uint32_t range).
 * \extends vx_reference
 * \ingroup group_distribution
 */
typedef struct _vx_distribution *vx_distribution;

/*! \brief The Matrix Object. An MxN matrix of some unit type.
 * \extends vx_reference
 * \ingroup group_matrix
 */
typedef struct _vx_matrix *vx_matrix;

/*! \brief The Image Pyramid object. A set of scaled images.
 * \extends vx_reference
 * \ingroup group_pyramid
 */
typedef struct _vx_pyramid *vx_pyramid;

/*! \brief The Threshold Object. A thresholding object contains the types and
 * limit values of the thresholding required.
 * \extends vx_reference
 * \ingroup group_threshold
 */
typedef struct _vx_threshold *vx_threshold;

/*! \brief The Convolution Object. A user-defined convolution kernel of MxM elements.
 * \extends vx_reference
 * \ingroup group_convolution
 */
typedef struct _vx_convolution *vx_convolution;

/*! \brief The remap table Object. A remap table contains per-pixel mapping of
 * output pixels to input pixels.
 * \ingroup group_remap
 */
typedef struct _vx_remap *vx_remap;

/*! \brief The Array Object. Array is a strongly-typed container for other data structures.
 * \ingroup group_array
 */
typedef struct _vx_array *vx_array;

/*! \brief The ObjectArray Object. ObjectArray is a strongly-typed container of OpenVX data-objects.
 * \ingroup group_object_array
 */
typedef struct _vx_object_array *vx_object_array;
 
 /*! \brief The multidimensional data object (Tensor).
 * \see vxCreateTensor
 * \ingroup group_object_tensor
 * \extends vx_reference
 */
typedef struct _vx_tensor_t * vx_tensor;



/*! \brief A Boolean value.
 * This allows 0 to be FALSE, as it is in C, and any non-zero to be TRUE.
 * \code
 * vx_bool ret = vx_true_e;
 * if (ret) printf("true!\n");
 * ret = vx_false_e;
 * if (!ret) printf("false!\n");
 * \endcode
 * This would print both strings.
 * \see vx_bool
 * \ingroup group_basic_features
 */
typedef enum _vx_bool_e {
    /*! \brief The "false" value. */
    vx_false_e = 0,
    /*! \brief The "true" value. */
    vx_true_e,
} vx_bool_e;

/*! \brief A formal boolean type with known fixed size.
 * \see vx_bool_e
 * \ingroup group_basic_features
 */
typedef vx_enum vx_bool;

/*!
 * \brief This object is used by output validation functions to specify the meta data
 * of the expected output data object.
 * \note When the actual output object of the user node is virtual, the information
 * given through the vx_meta_format object allows the OpenVX framework to automatically
 * create the data object when meta data were not specified by the application at object
 * creation time.
 * \ingroup group_user_kernels
 */
typedef struct _vx_meta_format* vx_meta_format;

/*! \brief The type enumeration lists all the known types in OpenVX.
 * \ingroup group_basic_features
 */
enum vx_type_e {
    VX_TYPE_INVALID         = 0x000,/*!< \brief An invalid type value. When passed an error must be returned. */
    VX_TYPE_CHAR            = 0x001,/*!< \brief A <tt>\ref vx_char</tt>. */
    VX_TYPE_INT8            = 0x002,/*!< \brief A <tt>\ref vx_int8</tt>. */
    VX_TYPE_UINT8           = 0x003,/*!< \brief A <tt>\ref vx_uint8</tt>. */
    VX_TYPE_INT16           = 0x004,/*!< \brief A <tt>\ref vx_int16</tt>. */
    VX_TYPE_UINT16          = 0x005,/*!< \brief A <tt>\ref vx_uint16</tt>. */
    VX_TYPE_INT32           = 0x006,/*!< \brief A <tt>\ref vx_int32</tt>. */
    VX_TYPE_UINT32          = 0x007,/*!< \brief A <tt>\ref vx_uint32</tt>. */
    VX_TYPE_INT64           = 0x008,/*!< \brief A <tt>\ref vx_int64</tt>. */
    VX_TYPE_UINT64          = 0x009,/*!< \brief A <tt>\ref vx_uint64</tt>. */
    VX_TYPE_FLOAT32         = 0x00A,/*!< \brief A <tt>\ref vx_float32</tt>. */
    VX_TYPE_FLOAT64         = 0x00B,/*!< \brief A <tt>\ref vx_float64</tt>. */
    VX_TYPE_ENUM            = 0x00C,/*!< \brief A <tt>\ref vx_enum</tt>. Equivalent in size to a <tt>\ref vx_int32</tt>. */
    VX_TYPE_SIZE            = 0x00D,/*!< \brief A <tt>\ref vx_size</tt>. */
    VX_TYPE_BOOL            = 0x010,/*!< \brief A <tt>\ref vx_bool</tt>. */

    VX_TYPE_RECTANGLE       = 0x020,/*!< \brief A <tt>\ref vx_rectangle_t</tt>. */
    VX_TYPE_KEYPOINT        = 0x021,/*!< \brief A <tt>\ref vx_keypoint_t</tt>. */
    VX_TYPE_COORDINATES2D   = 0x022,/*!< \brief A <tt>\ref vx_coordinates2d_t</tt>. */
    VX_TYPE_COORDINATES3D   = 0x023,/*!< \brief A <tt>\ref vx_coordinates3d_t</tt>. */
    VX_TYPE_COORDINATES2DF  = 0x024,/*!< \brief A <tt>\ref vx_coordinates2df_t</tt>. */
		
    VX_TYPE_USER_STRUCT_START    = 0x100,/*!< \brief A user-defined struct base index.*/
    VX_TYPE_VENDOR_STRUCT_START  = 0x400,/*!< \brief A vendor-defined struct base index.*/
    VX_TYPE_KHRONOS_OBJECT_START = 0x800,/*!< \brief A Khronos defined object base index. */
    VX_TYPE_VENDOR_OBJECT_START  = 0xC00,/*!< \brief A vendor defined object base index. */

    VX_TYPE_KHRONOS_STRUCT_MAX   = VX_TYPE_USER_STRUCT_START - 1,/*!< \brief A value for comparison between Khronos defined structs and user structs. */

    VX_TYPE_USER_STRUCT_END      = VX_TYPE_VENDOR_STRUCT_START - 1,/*!< \brief A value for comparison between user structs and vendor structs. */
    VX_TYPE_VENDOR_STRUCT_END    = VX_TYPE_KHRONOS_OBJECT_START - 1,/*!< \brief A value for comparison between vendor structs and Khronos defined objects. */
    VX_TYPE_KHRONOS_OBJECT_END   = VX_TYPE_VENDOR_OBJECT_START - 1,/*!< \brief A value for comparison between Khronos defined objects and vendor structs. */
    VX_TYPE_VENDOR_OBJECT_END    = 0xFFF,/*!< \brief A value used for bound checking of vendor objects */


    VX_TYPE_REFERENCE       = 0x800,/*!< \brief A <tt>\ref vx_reference</tt>. */
    VX_TYPE_CONTEXT         = 0x801,/*!< \brief A <tt>\ref vx_context</tt>. */
    VX_TYPE_GRAPH           = 0x802,/*!< \brief A <tt>\ref vx_graph</tt>. */
    VX_TYPE_NODE            = 0x803,/*!< \brief A <tt>\ref vx_node</tt>. */
    VX_TYPE_KERNEL          = 0x804,/*!< \brief A <tt>\ref vx_kernel</tt>. */
    VX_TYPE_PARAMETER       = 0x805,/*!< \brief A <tt>\ref vx_parameter</tt>. */
    VX_TYPE_DELAY           = 0x806,/*!< \brief A <tt>\ref vx_delay</tt>. */
    VX_TYPE_SCALAR          = 0x80D,/*!< \brief A <tt>\ref vx_scalar</tt>. when needed to be completely generic for kernel validation. */    
    VX_TYPE_ERROR           = 0x811,/*!< \brief An error object which has no type. */
    VX_TYPE_META_FORMAT     = 0x812,/*!< \brief A <tt>\ref vx_meta_format</tt>. */
    VX_TYPE_OBJECT_ARRAY    = 0x813,/*!< \brief A <tt>\ref vx_object_array</tt>. */
    VX_TYPE_TENSOR          = 0x815,/*!< \brief A <tt>\ref vx_tensor</tt>. */
	VX_TYPE_TENSOR_ARRAY	= 0x817,
    VX_TYPE_DEVICE_MEMORY_HANDLE = 0x818,
};

/*! \brief The enumeration of all status codes.
 * \see vx_status.
 * \ingroup group_basic_features
 */
enum vx_status_e {
    VX_STATUS_MIN                       = -25,/*!< \brief Indicates the lower bound of status codes in VX. Used for bounds checks only. */
    /* add new codes here */
    VX_ERROR_REFERENCE_NONZERO          = -24,/*!< \brief Indicates that an operation did not complete due to a reference count being non-zero. */
    VX_ERROR_MULTIPLE_WRITERS           = -23,/*!< \brief Indicates that the graph has more than one node outputting to the same data object. This is an invalid graph structure. */
    VX_ERROR_GRAPH_ABANDONED            = -22,/*!< \brief Indicates that the graph is stopped due to an error or a callback that abandoned execution. */
    VX_ERROR_GRAPH_SCHEDULED            = -21,/*!< \brief Indicates that the supplied graph already has been scheduled and may be currently executing. */
    VX_ERROR_INVALID_SCOPE              = -20,/*!< \brief Indicates that the supplied parameter is from another scope and cannot be used in the current scope. */
    VX_ERROR_INVALID_NODE               = -19,/*!< \brief Indicates that the supplied node could not be created.*/
    VX_ERROR_INVALID_GRAPH              = -18,/*!< \brief Indicates that the supplied graph has invalid connections (cycles). */
    VX_ERROR_INVALID_TYPE               = -17,/*!< \brief Indicates that the supplied type parameter is incorrect. */
    VX_ERROR_INVALID_VALUE              = -16,/*!< \brief Indicates that the supplied parameter has an incorrect value. */
    VX_ERROR_INVALID_DIMENSION          = -15,/*!< \brief Indicates that the supplied parameter is too big or too small in dimension. */
    VX_ERROR_INVALID_FORMAT             = -14,/*!< \brief Indicates that the supplied parameter is in an invalid format. */
    VX_ERROR_INVALID_LINK               = -13,/*!< \brief Indicates that the link is not possible as specified. The parameters are incompatible. */
    VX_ERROR_INVALID_REFERENCE          = -12,/*!< \brief Indicates that the reference provided is not valid. */
    VX_ERROR_INVALID_MODULE             = -11,/*!< \brief This is returned from <tt>\ref vxLoadKernels</tt> when the module does not contain the entry point. */
    VX_ERROR_INVALID_PARAMETERS         = -10,/*!< \brief Indicates that the supplied parameter information does not match the kernel contract. */
    VX_ERROR_OPTIMIZED_AWAY             = -9,/*!< \brief Indicates that the object refered to has been optimized out of existence. */
    VX_ERROR_NO_MEMORY                  = -8,/*!< \brief Indicates that an internal or implicit allocation failed. Typically catastrophic. After detection, deconstruct the context. \see vxVerifyGraph. */
    VX_ERROR_NO_RESOURCES               = -7,/*!< \brief Indicates that an internal or implicit resource can not be acquired (not memory). This is typically catastrophic. After detection, deconstruct the context. \see vxVerifyGraph. */
    VX_ERROR_NOT_COMPATIBLE             = -6,/*!< \brief Indicates that the attempt to link two parameters together failed due to type incompatibilty. */
    VX_ERROR_NOT_ALLOCATED              = -5,/*!< \brief Indicates to the system that the parameter must be allocated by the system.  */
    VX_ERROR_NOT_SUFFICIENT             = -4,/*!< \brief Indicates that the given graph has failed verification due to an insufficient number of required parameters, which cannot be automatically created. Typically this indicates required atomic parameters. \see vxVerifyGraph. */
    VX_ERROR_NOT_SUPPORTED              = -3,/*!< \brief Indicates that the requested set of parameters produce a configuration that cannot be supported. Refer to the supplied documentation on the configured kernels. \see vx_kernel_e. This is also returned if a function to set an attribute is called on a Read-only attribute.*/
    VX_ERROR_NOT_IMPLEMENTED            = -2,/*!< \brief Indicates that the requested kernel is missing. \see vx_kernel_e vxGetKernelByName. */
    VX_FAILURE                          = -1,/*!< \brief Indicates a generic error code, used when no other describes the error. */
    VX_SUCCESS                          =  0,/*!< \brief No error. */
};

/*! \brief A formal status type with known fixed size.
 * \see vx_status_e
 * \ingroup group_basic_features
 */
typedef vx_enum vx_status;

/*! \brief The formal typedef of the response from the callback.
 * \see vx_action_e
 * \ingroup group_node_callback
 */
typedef vx_enum vx_action;

/*! \brief A callback to the client after a particular node has completed.
 * \see vx_action
 * \see vxAssignNodeCallback
 * \param [in] node The node to which the callback was attached.
 * \return An action code from <tt>\ref vx_action_e</tt>.
 * \ingroup group_node_callback
 */
typedef vx_action (VX_CALLBACK *vx_nodecomplete_f)(vx_node node);

/*! \brief Vendor IDs are 2 nibbles in size and are located in the upper byte of
 * the 4 bytes of an enumeration.
 * \ingroup group_basic_features
 */
#define VX_VENDOR_MASK                      (0xFFF00000)

/*! \brief A type mask removes the scalar/object type from the attribute.
 * It is 3 nibbles in size and is contained between the third and second byte.
 * \see vx_type_e
 * \ingroup group_basic_features
 */
#define VX_TYPE_MASK                        (0x000FFF00)

/*! \brief A library is a set of vision kernels with its own ID supplied by a vendor.
 * The vendor defines the library ID. The range is \f$ [0,2^{8}-1] \f$ inclusive.
 * \ingroup group_basic_features
 */
#define VX_LIBRARY_MASK                     (0x000FF000)

/*! \brief An individual kernel in a library has its own unique ID within \f$ [0,2^{12}-1] \f$ (inclusive).
 * \ingroup group_basic_features
 */
#define VX_KERNEL_MASK                      (0x00000FFF)

/*! \brief An object's attribute ID is within the range of \f$ [0,2^{8}-1] \f$ (inclusive).
 * \ingroup group_basic_features
 */
#define VX_ATTRIBUTE_ID_MASK                (0x000000FF)

/*! \brief A type of enumeration. The valid range is between \f$ [0,2^{8}-1] \f$ (inclusive).
 * \ingroup group_basic_features
 */
#define VX_ENUM_TYPE_MASK                   (0x000FF000)

/*! \brief A generic enumeration list can have values between \f$ [0,2^{12}-1] \f$ (inclusive).
 * \ingroup group_basic_features
 */
#define VX_ENUM_MASK                        (0x00000FFF)

/*! \brief A macro to extract the vendor ID from the enumerated value.
 * \ingroup group_basic_features
 */
#define VX_VENDOR(e)                        (((vx_uint32)e & VX_VENDOR_MASK) >> 20)

/*! \brief A macro to extract the type from an enumerated attribute value.
 * \ingroup group_basic_features
 */
#define VX_TYPE(e)                          (((vx_uint32)e & VX_TYPE_MASK) >> 8)

/*! \brief A macro to extract the enum type from an enumerated value.
 * \ingroup group_basic_features
 */
#define VX_ENUM_TYPE(e)                     (((vx_uint32)e & VX_ENUM_TYPE_MASK) >> 12)

/*! \brief A macro to extract the kernel library enumeration from a enumerated kernel value.
 * \ingroup group_basic_features
 */
#define VX_LIBRARY(e)                       (((vx_uint32)e & VX_LIBRARY_MASK) >> 12)

/*! \def VX_DF_IMAGE
 * \brief Converts a set of four chars into a \c uint32_t container of a VX_DF_IMAGE code.
 * \note Use a <tt>\ref vx_df_image</tt> variable to hold the value.
 * \ingroup group_basic_features
 */
#define VX_DF_IMAGE(a,b,c,d)                  ((a) | (b << 8) | (c << 16) | (d << 24))

/*! \def VX_ATTRIBUTE_BASE
 * \brief Defines the manner in which to combine the Vendor and Object IDs to get
 * the base value of the enumeration.
 * \ingroup group_basic_features
 */
#define VX_ATTRIBUTE_BASE(vendor, object)   (((vendor) << 20) | (object << 8))

/*! \def VX_KERNEL_BASE
 * \brief Defines the manner in which to combine the Vendor and Library IDs to get
 * the base value of the enumeration.
 * \ingroup group_basic_features
 */
#define VX_KERNEL_BASE(vendor, lib)         (((vendor) << 20) | (lib << 12))

/*! \def VX_ENUM_BASE
 * \brief Defines the manner in which to combine the Vendor and Object IDs to get
 * the base value of the enumeration.
 * \details From any enumerated value (with exceptions), the vendor, and enumeration
 * type should be extractable. Those types that are exceptions are
 * <tt>\ref vx_vendor_id_e</tt>, <tt>\ref vx_type_e</tt>, <tt>\ref vx_enum_e</tt>, <tt>\ref vx_df_image_e</tt>, and \c vx_bool.
 * \ingroup group_basic_features
 */
#define VX_ENUM_BASE(vendor, id)            (((vendor) << 20) | (id << 12))

/*! \brief The set of supported enumerations in OpenVX.
 * \details These can be extracted from enumerated values using <tt>\ref VX_ENUM_TYPE</tt>.
 * \ingroup group_basic_features
 */
enum vx_enum_e {
    VX_ENUM_DIRECTION       = 0x00, /*!< \brief Parameter Direction. */
    VX_ENUM_ACTION          = 0x01, /*!< \brief Action Codes. */
    VX_ENUM_HINT            = 0x02, /*!< \brief Hint Values. */
    VX_ENUM_DIRECTIVE       = 0x03, /*!< \brief Directive Values. */
    VX_ENUM_INTERPOLATION   = 0x04, /*!< \brief Interpolation Types. */
    VX_ENUM_OVERFLOW        = 0x05, /*!< \brief Overflow Policies. */
    VX_ENUM_COLOR_SPACE     = 0x06, /*!< \brief Color Space. */
    VX_ENUM_COLOR_RANGE     = 0x07, /*!< \brief Color Space Range. */
    VX_ENUM_PARAMETER_STATE = 0x08, /*!< \brief Parameter State. */
    VX_ENUM_CHANNEL         = 0x09, /*!< \brief Channel Name. */
    VX_ENUM_CONVERT_POLICY  = 0x0A, /*!< \brief Convert Policy. */
    VX_ENUM_THRESHOLD_TYPE  = 0x0B, /*!< \brief Threshold Type List. */
    VX_ENUM_BORDER          = 0x0C, /*!< \brief Border Mode List. */
    VX_ENUM_COMPARISON      = 0x0D, /*!< \brief Comparison Values. */
    VX_ENUM_MEMORY_TYPE     = 0x0E, /*!< \brief The memory type enumeration. */
    VX_ENUM_TERM_CRITERIA   = 0x0F, /*!< \brief A termination criteria. */
    VX_ENUM_NORM_TYPE       = 0x10, /*!< \brief A norm type. */
    VX_ENUM_ACCESSOR        = 0x11, /*!< \brief An accessor flag type. */
    VX_ENUM_ROUND_POLICY    = 0x12, /*!< \brief Rounding Policy. */
    VX_ENUM_TARGET          = 0x13, /*!< \brief Target. */
    VX_ENUM_BORDER_POLICY   = 0x14, /*!< \brief Unsupported Border Mode Policy List. */
    VX_ENUM_GRAPH_STATE     = 0x15, /*!< \brief Graph attribute states. */
    VX_ENUM_NONLINEAR       = 0x16, /*!< \brief Non-linear function list. */
    VX_ENUM_PATTERN         = 0x17, /*!< \brief Matrix pattern enumeration. */
    VX_ENUM_LBP_FORMAT      = 0x18, /*!< \brief Lbp format. */
    VX_ENUM_COMP_METRIC     = 0x19, /*!< \brief Compare metric. */
    VX_ENUM_SCALAR_OPERATION= 0X20  /*!< \brief Scalar operation list. */
};

/*! \brief A return code enumeration from a <tt>\ref vx_nodecomplete_f</tt> during execution.
 * \see <tt>vxAssignNodeCallback</tt>
 * \ingroup group_node_callback
 */
enum vx_action_e {
    /*! \brief Continue executing the graph with no changes. */
    VX_ACTION_CONTINUE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ACTION) + 0x0,
    /*! \brief Stop executing the graph. */
    VX_ACTION_ABANDON  = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ACTION) + 0x1,
};

/*! \brief An indication of how a kernel will treat the given parameter.
 * \ingroup group_parameter
 */
enum vx_direction_e {
    /*! \brief The parameter is an input only. */
    VX_INPUT = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_DIRECTION) + 0x0,
    /*! \brief The parameter is an output only. */
    VX_OUTPUT = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_DIRECTION) + 0x1,
    /*! \brief The parameter is both an input and output. */
    VX_BIDIRECTIONAL = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_DIRECTION) + 0x2,
};

/*! \brief The Graph State Enumeration.
 * \ingroup group_graph
 */
enum vx_graph_state_e {
   /*! \brief The graph should be verified before execution */
   VX_GRAPH_STATE_UNVERIFIED = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_GRAPH_STATE) + 0x0,
   /*! \brief The graph has been verified and has not been executed or scheduled for execution yet */
   VX_GRAPH_STATE_VERIFIED = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_GRAPH_STATE) + 0x1,
   /*! \brief The graph either has been scheduled and not completed, or is being executed */
   VX_GRAPH_STATE_RUNNING = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_GRAPH_STATE) + 0x2,
   /*! \brief The graph execution was abandoned */
   VX_GRAPH_STATE_ABANDONED = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_GRAPH_STATE) + 0x3,
   /*! \brief The graph execution is completed and the graph is not scheduled for execution */
   VX_GRAPH_STATE_COMPLETED = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_GRAPH_STATE) + 0x4,
};

/*! \brief The graph attributes list.
 * \ingroup group_graph
 */
enum vx_graph_attribute_e {
    /*! \brief Returns the number of nodes in a graph. Read-only. Use a <tt>\ref vx_uint32</tt> parameter.*/
    VX_GRAPH_NUMNODES = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_GRAPH) + 0x0,
    /*! \brief Returns the overall performance of the graph. Read-only. Use a <tt>\ref vx_perf_t</tt> parameter.
     * The accuracy of timing information is platform dependent.
     * \note Performance tracking must have been enabled. See <tt>\ref vx_directive_e</tt>
     */
    VX_GRAPH_PERFORMANCE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_GRAPH) + 0x2,
    /*! \brief Returns the number of explicitly declared parameters on the graph. Read-only. Use a <tt>\ref vx_uint32</tt> parameter. */
    VX_GRAPH_NUMPARAMETERS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_GRAPH) + 0x3,
    /*! \brief Returns the state of the graph. See <tt>\ref vx_graph_state_e</tt> enum. */
    VX_GRAPH_STATE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_GRAPH) + 0x4,
};

/*! \brief The Conversion Policy Enumeration.
 * \ingroup group_basic_features
 */
enum vx_convert_policy_e {
    /*! \brief Results are the least significant bits of the output operand, as if
     * stored in two's complement binary format in the size of its bit-depth.
     */
    VX_CONVERT_POLICY_WRAP = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_CONVERT_POLICY) + 0x0,
    /*! \brief Results are saturated to the bit depth of the output operand. */
    VX_CONVERT_POLICY_SATURATE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_CONVERT_POLICY) + 0x1,
};

/*! \brief The Target Enumeration.
 * \ingroup group_basic_features
 */
enum vx_target_e {
    /*! \brief Any available target. An OpenVX implementation must support at least one target associated with this value */
    VX_TARGET_ANY = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_TARGET) + 0x0000,
    /*! \brief Target, explicitly specified by its (case-insensitive) name string. */
    VX_TARGET_STRING = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_TARGET) + 0x0001,
    /*! \brief Start of Vendor specific target enumerates. */
    VX_TARGET_VENDOR_BEGIN = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_TARGET) + 0x1000,
};

/*! \brief The reference attributes list.
 * \ingroup group_reference
 */
enum vx_reference_attribute_e {
    /*! \brief Returns the reference count of the object. Read-only. Use a <tt>\ref vx_uint32</tt> parameter. */
    VX_REFERENCE_COUNT = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_REFERENCE) + 0x0,
    /*! \brief Returns the <tt>\ref vx_type_e</tt> of the reference. Read-only. Use a <tt>\ref vx_enum</tt> parameter. */
    VX_REFERENCE_TYPE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_REFERENCE) + 0x1,
    /*! \brief Used to query the reference for its name. Read-write. Use a *<tt>\ref vx_char</tt> parameter. */
    VX_REFERENCE_NAME = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_REFERENCE) + 0x2,
};

/*! \brief A list of context attributes.
 * \ingroup group_context
 */
enum vx_context_attribute_e {
    /*! \brief Queries the unique vendor ID. Read-only. Use a <tt>\ref vx_uint16</tt>. */
    VX_CONTEXT_VENDOR_ID = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x0,
    /*! \brief Queries the OpenVX Version Number. Read-only. Use a <tt>\ref vx_uint16</tt> */
    VX_CONTEXT_VERSION = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x1,
    /*! \brief Queries the context for the number of \e unique kernels. Read-only. Use a <tt>\ref vx_uint32</tt> parameter. */
    VX_CONTEXT_UNIQUE_KERNELS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x2,
    /*! \brief Queries the context for the number of active modules. Read-only. Use a <tt>\ref vx_uint32</tt> parameter. */
    VX_CONTEXT_MODULES = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x3,
    /*! \brief Queries the context for the number of active references. Read-only. Use a <tt>\ref vx_uint32</tt> parameter. */
    VX_CONTEXT_REFERENCES = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x4,
    /*! \brief Queries the context for it's implementation name. Read-only. Use a <tt>\ref vx_char</tt>[<tt>\ref VX_MAX_IMPLEMENTATION_NAME</tt>] array */
    VX_CONTEXT_IMPLEMENTATION = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x5,
    /*! \brief Queries the number of bytes in the extensions string. Read-only. Use a <tt>\ref vx_size</tt> parameter. */
    VX_CONTEXT_EXTENSIONS_SIZE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x6,
    /*! \brief Retrieves the extensions string. Read-only.
     * This is a space-separated string of extension names. Each OpenVX official extension has a unique identifier,
     * comprised of capital letters, numbers and the underscore character, prefixed with "KHR_", for example "KHR_NEW_FEATURE".
     * Use a <tt>\ref vx_char</tt> pointer allocated to the size returned from <tt>\ref VX_CONTEXT_EXTENSIONS_SIZE</tt>.
     */
    VX_CONTEXT_EXTENSIONS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x7,
    /*! \brief The maximum width or height of a convolution matrix.
     * Read-only. Use a <tt>\ref vx_size</tt> parameter.
     * Each vendor must support centered kernels of size w X h, where both w
     * and h are odd numbers, 3 <= w <= n and 3 <= h <= n, where n is the value of the
     * <tt>\ref VX_CONTEXT_CONVOLUTION_MAX_DIMENSION</tt> attribute. n is an odd
     * number that should not be smaller than 9. w and h may or may not be equal to
     * each other. All combinations of w and h meeting the conditions above must be
     * supported. The behavior of <tt>\ref vxCreateConvolution</tt> is undefined for values
     * larger than the value returned by this attribute.
     */
    VX_CONTEXT_CONVOLUTION_MAX_DIMENSION = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x8,
    /*! \brief The maximum window dimension of the OpticalFlowPyrLK kernel. The value of this attribute shall be equal to or greater than '9'.
     * \see <tt>\ref VX_KERNEL_OPTICAL_FLOW_PYR_LK</tt>. Read-only. Use a <tt>\ref vx_size</tt> parameter.
     */
    VX_CONTEXT_OPTICAL_FLOW_MAX_WINDOW_DIMENSION = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0x9,
    /*! \brief The border mode for immediate mode functions.
     * \details Graph mode functions are unaffected by this attribute. Read-write. Use a pointer to a <tt>\ref vx_border_t</tt> structure as parameter.
     * \note The assumed default value for immediate mode functions is <tt>\ref VX_BORDER_UNDEFINED</tt>.
     */
    VX_CONTEXT_IMMEDIATE_BORDER = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0xA,
    /*! \brief Returns the table of all unique the kernels that exist in the context.
     *  Read-only. Use a <tt>\ref vx_kernel_info_t</tt> array.
     * \pre You must call <tt>\ref vxQueryContext</tt> with <tt>\ref VX_CONTEXT_UNIQUE_KERNELS</tt>
     * to compute the necessary size of the array.
     */
    VX_CONTEXT_UNIQUE_KERNEL_TABLE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0xB,
    /*! \brief The unsupported border mode policy for immediate mode functions. Read-Write.
     * \details Graph mode functions are unaffected by this attribute. Use a <tt>\ref vx_enum</tt> as parameter. Will contain a <tt>\ref vx_border_policy_e</tt>.
     * \note The assumed default value for immediate mode functions is <tt>\ref VX_BORDER_POLICY_DEFAULT_TO_UNDEFINED</tt>. Users should refer to the documentation of their implementation to determine what border modes are supported by each kernel.
     */
    VX_CONTEXT_IMMEDIATE_BORDER_POLICY = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0xC,
    /*! \brief The dimension of the largest nonlinear filter supported. See <tt>\ref vxNonLinearFilterNode</tt>.
     * \details The implementation must support all dimensions (height or width, not necessarily the same)
     * up to the value of this attribute.  The lowest value that must be supported for this attribute is 9.
     * Read-only. Use a <tt>\ref vx_size</tt> parameter.
     */
    VX_CONTEXT_NONLINEAR_MAX_DIMENSION = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0xd,
    /*! \brief tensor Data maximal number of dimensions supported by the implementation. */
    VX_CONTEXT_MAX_TENSOR_DIMS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_CONTEXT) + 0xE,
};

/*! \brief The kernel attributes list
 * \ingroup group_kernel
 */
enum vx_kernel_attribute_e {
    /*! \brief Queries a kernel for the number of parameters the kernel
     * supports. Read-only. Use a <tt>\ref vx_uint32</tt> parameter.
     */
    VX_KERNEL_PARAMETERS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_KERNEL) + 0x0,
    /*! \brief Queries the name of the kernel. Not settable.
     *  Read-only. Use a <tt>\ref vx_char</tt>[<tt>\ref VX_MAX_KERNEL_NAME</tt>] array (not a <tt>\ref vx_array</tt>).
     */
    VX_KERNEL_NAME = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_KERNEL) + 0x1,
    /*! \brief Queries the enum of the kernel. Not settable.
     *  Read-only. Use a <tt>\ref vx_enum</tt> parameter.
     */
    VX_KERNEL_ENUM = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_KERNEL) + 0x2,
    /*! \brief The local data area allocated with each kernel when it becomes a
     * node.  Read-write. Can be written only before user-kernel finalization.
     * Use a <tt>\ref vx_size</tt> parameter.
     * \note If not set it will default to zero.
     */
    VX_KERNEL_LOCAL_DATA_SIZE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_KERNEL) + 0x3,
};

/*! \brief The kernel object attributes for global and local memory.
* \ingroup group_kernel
*/
enum vx_kernel_attribute_memory_e {
	/*! \brief The global data pointer size to be shared across all instances of
	* the kernel (nodes are instances of kernels).
	* Use a \ref vx_size parameter.
	* \note If not set it will default to zero.
	*/
	VX_KERNEL_GLOBAL_DATA_SIZE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_KERNEL) + 0x5,
	/*! \brief The global data pointer to the shared across all the instances of
	* the kernel (nodes are instances of the kernels).
	* Use a \ref void * parameter.
	*/
	VX_KERNEL_GLOBAL_DATA_PTR = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_KERNEL) + 0x6,
};

/*! \brief The node attributes list.
 * \ingroup group_node
 */
enum vx_node_attribute_e {
    /*! \brief Queries the status of node execution. Read-only. Use a <tt>\ref vx_status</tt> parameter. */
    VX_NODE_STATUS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_NODE) + 0x0,    
    /*! \brief Indicates the number of node parameters, including optional parameters that are not passed.
     * Read-only. Use a <tt>\ref vx_uint32</tt> parameter.
     */
    VX_NODE_PARAMETERS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_NODE) + 0x5,
    /*! \brief Indicates whether the node is replicated. Read-only.
     * Use a <tt>\ref vx_bool</tt> parameter.
     */
    VX_NODE_IS_REPLICATED = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_NODE) + 0x6,
    /*! \brief Indicates the replicated parameters. Read-only.
     * Use a <tt>\ref vx_bool</tt>* parameter.
     */
    VX_NODE_REPLICATE_FLAGS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_NODE) + 0x7,
};

/*! \brief The parameter attributes list
 * \ingroup group_parameter
 */
enum vx_parameter_attribute_e {
    /*! \brief Queries a parameter for its index value on the kernel with which it is associated. Read-only. Use a <tt>\ref vx_uint32</tt> parameter. */
    VX_PARAMETER_INDEX = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_PARAMETER) + 0x0,
    /*! \brief Queries a parameter for its direction value on the kernel with which it is associated. Read-only. Use a <tt>\ref vx_enum</tt> parameter. */
    VX_PARAMETER_DIRECTION = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_PARAMETER) + 0x1,
    /*! \brief Queries a parameter for its type, \ref vx_type_e is returned. Read-only. The size of the parameter is implied for plain data objects. For opaque data objects like images and arrays a query to their attributes has to be called to determine the size. */
    VX_PARAMETER_TYPE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_PARAMETER) + 0x2,
    /*! \brief Queries a parameter for its state. A value in <tt>\ref vx_parameter_state_e</tt> is returned. Read-only. Use a <tt>\ref vx_enum</tt> parameter. */
    VX_PARAMETER_STATE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_PARAMETER) + 0x3,
    /*! \brief Use to extract the reference contained in the parameter. Read-only. Use a <tt>\ref vx_reference</tt> parameter.  */
    VX_PARAMETER_REF = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_PARAMETER) + 0x4,
};


/*! \brief The scalar attributes list.
 * \ingroup group_scalar
 */
enum vx_scalar_attribute_e {
    /*! \brief Queries the type of atomic that is contained in the scalar. Read-only. Use a <tt>\ref vx_enum</tt> parameter.*/
    VX_SCALAR_TYPE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_SCALAR) + 0x0,
};

/*! \brief A type of operation in which both operands are scalars.
 * \see group_scalar
 * \ingroup group_scalar
 */
enum vx_scalar_operation_e {
    /*! \brief logical and. */
    VX_SCALAR_OP_AND = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x0,
    /*! \brief logical or. */
    VX_SCALAR_OP_OR = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x1,
    /*! \brief logical exclusive or. */
    VX_SCALAR_OP_XOR = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x2,
    /*! \brief logical nand. */
    VX_SCALAR_OP_NAND = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x3,  
    /*! \brief comparison (equal). */
    VX_SCALAR_OP_EQUAL = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x4,
    /*! \brief comparison (not equal). */
    VX_SCALAR_OP_NOTEQUAL = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x5,
    /*! \brief comparison (less than). */
    VX_SCALAR_OP_LESS = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x6,
    /*! \brief comparison (less than or equal to). */
    VX_SCALAR_OP_LESSEQ = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x7,  
    /*! \brief comparison (greater than). */
    VX_SCALAR_OP_GREATER = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x8,
    /*! \brief comparison (greater than or equal to). */
    VX_SCALAR_OP_GREATEREQ = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x9,  
    /*! \brief arithmetic addition. */
    VX_SCALAR_OP_ADD = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0xA,  
    /*! \brief arithmetic subtraction. */
    VX_SCALAR_OP_SUBTRACT = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0xB,
    /*! \brief arithmetic multiplication. */
    VX_SCALAR_OP_MULTIPLY = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0xC,
    /*! \brief arithmetic division. */
    VX_SCALAR_OP_DIVIDE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0xD,
    /*! \brief arithmetic (modulo operator). */
    VX_SCALAR_OP_MODULUS = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0xE,  
    /*! \brief minimum of two scalars. */
    VX_SCALAR_OP_MIN = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0xF,
    /*! \brief maximum of two scalars. */
    VX_SCALAR_OP_MAX = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_SCALAR_OPERATION) + 0x10,      
};

/*! \brief tensor Data attributes.
 * \ingroup group_object_tensor
 */
enum vx_tensor_attribute_e
{
    /*! \brief Number of dimensions. */
    VX_TENSOR_NUMBER_OF_DIMS = VX_ATTRIBUTE_BASE( VX_ID_KHRONOS, VX_TYPE_TENSOR ) + 0x0,
    /*! \brief Dimension sizes. */
    VX_TENSOR_DIMS        = VX_ATTRIBUTE_BASE( VX_ID_KHRONOS, VX_TYPE_TENSOR ) + 0x1,
    /*! \brief tensor Data element data type. <tt>vx_type_e</tt> */
    VX_TENSOR_DATA_TYPE   = VX_ATTRIBUTE_BASE( VX_ID_KHRONOS, VX_TYPE_TENSOR ) + 0x2,
};

/*! \brief The meta valid rectangle attributes.
 * \ingroup group_user_kernels
 */
enum vx_meta_valid_rect_attribute_e {
    /*! \brief Valid rectangle callback during output parameter validation. Write-only. */
    VX_VALID_RECT_CALLBACK = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_META_FORMAT) + 0x1,
};

/*! \brief An enumeration of memory import types.
 * \ingroup group_context
 */
enum vx_memory_type_e {
    /*! \brief For memory allocated through OpenVX, this is the import type. */
    VX_MEMORY_TYPE_NONE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_MEMORY_TYPE) + 0x0,

    /*! \brief The default memory type to import from the Host. */
    VX_MEMORY_TYPE_HOST = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_MEMORY_TYPE) + 0x1,

    /*! \brief The default memory type to import from the Device. */
    VX_MEMORY_TYPE_DEVICE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_MEMORY_TYPE) + 0x2,
};

/*! \brief The parameter state type.
 * \ingroup group_parameter
 */
enum vx_parameter_state_e {
    /*! \brief Default. The parameter must be supplied. If not set, during
     * Verify, an error is returned.
     */
    VX_PARAMETER_STATE_REQUIRED = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_PARAMETER_STATE) + 0x0,
    /*! \brief The parameter may be unspecified. The kernel takes care not
     * to deference optional parameters until it is certain they are valid.
     */
    VX_PARAMETER_STATE_OPTIONAL = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_PARAMETER_STATE) + 0x1,
};

/*! \brief The delay attribute list.
 * \ingroup group_delay
 */
enum vx_delay_attribute_e {
    /*! \brief The type of objects in the delay. Read-only. Use a <tt>\ref vx_enum</tt> parameter. */
    VX_DELAY_TYPE = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_DELAY) + 0x0,
    /*! \brief The number of items in the delay. Read-only. Use a <tt>\ref vx_size</tt> parameter.*/
    VX_DELAY_SLOTS = VX_ATTRIBUTE_BASE(VX_ID_KHRONOS, VX_TYPE_DELAY) + 0x1,
};

/*! \brief The memory accessor hint flags.
 * These enumeration values are used to indicate desired \e system behavior,
 * not the \b User intent. For example: these can be interpretted as hints to the
 * system about cache operations or marshalling operations.
 * \ingroup group_context
 */
enum vx_accessor_e {
    /*! \brief The memory shall be treated by the system as if it were read-only.
     * If the User writes to this memory, the results are implementation defined.
     */
    VX_READ_ONLY = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ACCESSOR) + 0x1,
    /*! \brief The memory shall be treated by the system as if it were write-only.
     * If the User reads from this memory, the results are implementation defined.
     */
    VX_WRITE_ONLY = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ACCESSOR) + 0x2,
    /*! \brief The memory shall be treated by the system as if it were readable and writeable.
     */
    VX_READ_AND_WRITE = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ACCESSOR) + 0x3,
};

/*! \brief The Round Policy Enumeration.
 * \ingroup group_context
 */
enum vx_round_policy_e {
    /*! \brief When scaling, this truncates the least significant values that are lost in operations. */
    VX_ROUND_POLICY_TO_ZERO = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ROUND_POLICY) + 0x1,
    /*! \brief When scaling, this rounds to nearest even output value. */
    VX_ROUND_POLICY_TO_NEAREST_EVEN = VX_ENUM_BASE(VX_ID_KHRONOS, VX_ENUM_ROUND_POLICY) + 0x2,
};

/*! \brief Local binary pattern supported.
 * \ingroup group_vision_function_lbp
 */
enum vx_lbp_format_e
{
    /*! \brief local binary pattern 
	*/
    VX_LBP  = VX_ENUM_BASE( VX_ID_KHRONOS, VX_ENUM_LBP_FORMAT ) + 0x0,
    /*! \brief Modified Local Binary Patterns
	*/
	
    VX_MLBP = VX_ENUM_BASE( VX_ID_KHRONOS, VX_ENUM_LBP_FORMAT ) + 0x1,
    /*! \brief Uniform local binary pattern 
	*/
    VX_ULBP = VX_ENUM_BASE( VX_ID_KHRONOS, VX_ENUM_LBP_FORMAT ) + 0x2
};

#if defined(_WIN32) || defined(UNDER_CE)
#if defined(_WIN64)
/*! \brief Use to aid in debugging values in OpenVX.
 * \ingroup group_basic_features
 */
#define VX_FMT_REF  "%I64u"
/*! \brief Use to aid in debugging values in OpenVX.
 * \ingroup group_basic_features
 */
#define VX_FMT_SIZE "%I64u"
#else
/*! \brief Use to aid in debugging values in OpenVX.
 * \ingroup group_basic_features
 */
#define VX_FMT_REF  "%lu"
/*! \brief Use to aid in debugging values in OpenVX.
 * \ingroup group_basic_features
 */
#define VX_FMT_SIZE "%lu"
#endif
#else
/*! \brief Use to aid in debugging values in OpenVX.
 * \ingroup group_basic_features
 */
#define VX_FMT_REF  "%p"
/*! \brief Use to aid in debugging values in OpenVX.
 * \ingroup group_basic_features
 */
#define VX_FMT_SIZE "%zu"
#endif
/*! \brief Use to indicate the 1:1 ratio in Q22.10 format.
 * \ingroup group_basic_features
 */
#define VX_SCALE_UNITY (1024u)

/*! \brief The Kernel Information Structure. This is returned by the Context
 * to indicate which kernels are available in the OpenVX implementation.
 * \ingroup group_kernel
 */
typedef struct _vx_kernel_info_t {
    /*! \brief The kernel enumeration value from <tt>\ref vx_kernel_e</tt> (or an
     * extension thereof).
     * \see vxGetKernelByEnum
     */
    vx_enum enumeration;

    /*! \brief The kernel name in dotted hierarchical format.
     * e.g. "org.khronos.openvx.sobel_3x3"
     * \see vxGetKernelByName
     */
    vx_char name[VX_MAX_KERNEL_NAME];
} vx_kernel_info_t;

/*! \brief Use to indicate a half-scale pyramid.
 * \ingroup group_pyramid
 */
#define VX_SCALE_PYRAMID_HALF       (0.5f)

/*! \brief Use to indicate a ORB scaled pyramid whose scaling factor is \f$ \frac{1}{\root 4 \of {2}} \f$.
 * \ingroup group_pyramid
 */
#define VX_SCALE_PYRAMID_ORB        ((vx_float32)0.8408964f)

/*!
* \brief The type of the <tt>vxPublishKernels</tt> entry function of modules loaded
* by <tt>\ref vxLoadKernels</tt> and unloaded by <tt>\ref vxUnloadKernels</tt>.
* \param [in] context The reference to the context kernels must be added to.
* \ingroup group_user_kernels
*/
typedef vx_status(VX_API_CALL *vx_publish_kernels_f)(vx_context context);

/*!
* \brief The type of the <tt>vxUnpublishKernels</tt> entry function of modules loaded
* by <tt>\ref vxLoadKernels</tt> and unloaded by <tt>\ref vxUnloadKernels</tt>.
* \param [in] context The reference to the context kernels have been added to.
* \ingroup group_user_kernels
*/
typedef vx_status(VX_API_CALL *vx_unpublish_kernels_f)(vx_context context);

/*!
* \brief The pointer to the Host side kernel.
* \param [in] node The handle to the node that contains this kernel.
* \param [in] parameters The array of parameter references.
* \param [in] num The number of parameters.
* \ingroup group_user_kernels
*/
typedef vx_status(VX_CALLBACK *vx_kernel_f)(vx_node node, const vx_reference *parameters, vx_uint32 num);

/*!
* \brief The pointer to the kernel initializer. If the host code requires a call
* to initialize data once all the parameters have been validated, this function is called
* if not NULL.
* \param [in] node The handle to the node that contains this kernel.
* \param [in] parameters The array of parameter references.
* \param [in] num The number of parameters.
* \ingroup group_user_kernels
*/
typedef vx_status(VX_CALLBACK *vx_kernel_initialize_f)(vx_node node, const vx_reference *parameters, vx_uint32 num);

/*!
* \brief The pointer to the kernel deinitializer. If the host code requires a call
* to deinitialize data during a node garbage collection, this function is called
* if not NULL.
* \param [in] node The handle to the node that contains this kernel.
* \param [in] parameters The array of parameter references.
* \param [in] num The number of parameters.
* \ingroup group_user_kernels
*/
typedef vx_status(VX_CALLBACK *vx_kernel_deinitialize_f)(vx_node node, const vx_reference *parameters, vx_uint32 num);

typedef vx_status(VX_CALLBACK *vx_kernel_dump_f)(vx_node node, const vx_reference * parameters, vx_uint32 num, void * info_file);

/*!
* \brief The user-defined kernel node parameters validation function. The function only
* needs to fill in the meta data structure(s).
* \note This function is called once for whole set of parameters.
* \param [in] node The handle to the node that is being validated.
* \param [in] parameters The array of parameters to be validated.
* \param [in] num Number of parameters to be validated.
* \param [in] metas A pointer to a pre-allocated array of structure references that the system holds.
* The system pre-allocates a number of vx_meta_format structures for the output parameters only,
* indexed by the same indices as parameters[]. The validation function fills in the correct type, format,
* and dimensionality for the system to use either to create memory or to check against existing memory.
* \return An error code describing the validation status on parameters.
* \ingroup group_user_kernels
*/
typedef vx_status(VX_CALLBACK *vx_kernel_validate_f)(vx_node node, const vx_reference parameters[], vx_uint32 num, vx_meta_format metas[]);

#endif
