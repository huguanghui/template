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

#ifndef _OPENVX_H_
#define _OPENVX_H_

/*!
 * \file
 * \brief The top level OpenVX Header.
 */

/*! \brief Defines the length of the implementation name string, including the trailing zero.
 * \ingroup group_context
 */
#define VX_MAX_IMPLEMENTATION_NAME (64)

/*! \brief Defines the length of a kernel name string to be added to OpenVX, including the trailing zero.
 * \ingroup group_kernel
 */
#define VX_MAX_KERNEL_NAME (128)

#include <VX/vx_vendors.h>
#include <VX/vx_types.h>
#include <VX/vx_kernels.h>
#include <VX/vx_api.h>
#include <VX/vx_nodes.h>

/*! \brief Defines the major version number macro.
 * \ingroup group_basic_features
 */
#define VX_VERSION_MAJOR(x) ((x & 0xFF) << 8)

/*! \brief Defines the minor version number macro.
 * \ingroup group_basic_features
 */
#define VX_VERSION_MINOR(x) ((x & 0xFF) << 0)

/*! \brief Defines the predefined version number for 1.0.
 * \ingroup group_basic_features
 */
#define VX_VERSION_1_0      (VX_VERSION_MAJOR(1) | VX_VERSION_MINOR(0))

/*! \brief Defines the predefined version number for 1.1.
 * \ingroup group_basic_features
 */
#define VX_VERSION_1_1      (VX_VERSION_MAJOR(1) | VX_VERSION_MINOR(1))

/*! \brief Defines the predefined version number for 1.2.
 * \ingroup group_basic_features
 */
#define VX_VERSION_1_2      (VX_VERSION_MAJOR(1) | VX_VERSION_MINOR(2))

/*! \brief Defines the OpenVX Version Number.
 * \ingroup group_basic_features
 */
//#define VX_VERSION          VX_VERSION_1_2

#define BUILD_YEAR_CH0 (__DATE__[ 7])
#define BUILD_YEAR_CH1 (__DATE__[ 8])
#define BUILD_YEAR_CH2 (__DATE__[ 9])
#define BUILD_YEAR_CH3 (__DATE__[10])

#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')
#define BUILD_MONTH_CH0 ((BUILD_MONTH_IS_OCT || BUILD_MONTH_IS_NOV || BUILD_MONTH_IS_DEC) ? '1' : '0')
#define BUILD_MONTH_CH1 ( \
    (BUILD_MONTH_IS_JAN) ? '1' : \
    (BUILD_MONTH_IS_FEB) ? '2' : \
    (BUILD_MONTH_IS_MAR) ? '3' : \
    (BUILD_MONTH_IS_APR) ? '4' : \
    (BUILD_MONTH_IS_MAY) ? '5' : \
    (BUILD_MONTH_IS_JUN) ? '6' : \
    (BUILD_MONTH_IS_JUL) ? '7' : \
    (BUILD_MONTH_IS_AUG) ? '8' : \
    (BUILD_MONTH_IS_SEP) ? '9' : \
    (BUILD_MONTH_IS_OCT) ? '0' : \
    (BUILD_MONTH_IS_NOV) ? '1' : \
    (BUILD_MONTH_IS_DEC) ? '2' : '?'  \
)

#define BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define BUILD_DAY_CH1 (__DATE__[5])

#define BUILD_HOUR_CH0 (__TIME__[0])
#define BUILD_HOUR_CH1 (__TIME__[1])

#define BUILD_MIN_CH0 (__TIME__[3])
#define BUILD_MIN_CH1 (__TIME__[4])

#define BUILD_SEC_CH0 (__TIME__[6])
#define BUILD_SEC_CH1 (__TIME__[7])

#define VX_VERSION { \
    '1', \
    '.', \
    '4', \
    '.', \
    BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3, \
    BUILD_MONTH_CH0, BUILD_MONTH_CH1, \
    BUILD_DAY_CH0, BUILD_DAY_CH1, \
    '.', \
    BUILD_HOUR_CH0, BUILD_HOUR_CH1, \
    '\0' \
}

#endif
