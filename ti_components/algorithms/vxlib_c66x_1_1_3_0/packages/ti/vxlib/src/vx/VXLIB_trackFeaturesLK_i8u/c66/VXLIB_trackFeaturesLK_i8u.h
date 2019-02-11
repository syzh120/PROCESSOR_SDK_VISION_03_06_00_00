/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2016 - 2017 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VXLIB_TRACKFEATURESLK_I8U_H_
#define VXLIB_TRACKFEATURESLK_I8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_trackFeaturesLK_i8u */
/** @ingroup  VXLIB_trackFeaturesLK_i8u */
/* @{ */
/**
 * @par Description:
 *  Performs the Lucas Kanade tracking method of features between two images.
 *
 * @par Method:
 *  
 *
 * @par
 *   @param [in]       old_image[]        Pointer to array containing old input image (UQ8.0)
 *   @param [in]      *old_image_addr     Pointer to structure containing dimensional information of old_image
 *   @param [in]       new_image[]        Pointer to array containing new input image (UQ8.0)
 *   @param [in]      *new_image_addr     Pointer to structure containing dimensional information of new_image
 *   @param [in]       old_gradX[]        Pointer to array containing old X gradient image (SQ15.0)
 *   @param [in]      *old_gradX_addr     Pointer to structure containing dimensional information of old_gradX
 *   @param [in]       old_gradY[]        Pointer to array containing old Y gradient image (SQ15.0)
 *   @param [in]      *old_gradY_addr     Pointer to structure containing dimensional information of old_gradY
 *   @param [in,out]   old_points[]       Pointer to array containing keypoint list from old_image (F32.0)
 *   @param [in,out]   new_points[]       Pointer to array containing keypoint list for new_image (F32.0)
 *   @param [in,out]   tracking_status[]  Status of each point in the list (0: not tracked; 1: tracked)
 *   @param [in]       num_points         Number of entries in each : old_points, new_points, and tracking_status arrays.
 *   @param [in]       max_iters          Maximum number of iterations allowed before terminating the algorithm for each point.
 *   @param [in]       epsilon            Maximum error allowed before terminating the algorithm for each point.
 *   @param [in]       scale              Scale factor to apply to both the old_points and new_points list before tracking.
 *   @param [in]       window_size        Window size
 *   @param [in]       level              Flag to indicate if tracking_status[] should be updated or not (0: update; non-zero: no update)
 *   @param [in]       termination        Termination criteria: VXLIB_TERM_ITERATIONS, VXLIB_TERM_EPSILON, or VXLIB_TERM_BOTH
 *   @param [in]       scratch[]          Scratch buffer.  Should allocate window_size*window_size*6 + 2 bytes.
 *   @param [in]       scratch_size       Size of the scratch buffer (for parameter checking)
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - The old_image and new_image should be the same size (although they may have different strides)
 *    - The old_gradX and old_gradY images should have the same size and strides.
 *    - Each 64-bit word in old_points[] and new_points[] arrays are composed of 2 32-bit float words representing
 *      x and y coordinates, such that old_points[i] = (y(i) << 32) | x(i);
 *    - The tracking_status[] array corresponds to the old_points and new_points lists
 *    - The scratch buffer should be at least window_size*window_size*6 + 2 bytes
 *
 */
VXLIB_STATUS VXLIB_trackFeaturesLK_i8u(const uint8_t old_image[restrict],
                                                   const VXLIB_bufParams2D_t *old_image_addr,
                                                   const uint8_t new_image[restrict],
                                                   const VXLIB_bufParams2D_t *new_image_addr,
                                                   const int16_t old_gradX[restrict],
                                                   const VXLIB_bufParams2D_t *old_gradX_addr,
                                                   const int16_t old_gradY[restrict],
                                                   const VXLIB_bufParams2D_t *old_gradY_addr,
                                                   __float2_t old_points[restrict],
                                                   __float2_t new_points[restrict],
                                                   uint8_t tracking_status[restrict],
                                                   uint32_t num_points,
                                                   uint32_t max_iters,
                                                   VXLIB_F32 epsilon,
                                                   VXLIB_F32 scale,
                                                   uint8_t window_size,
                                                   uint8_t level,
                                                   uint8_t termination,
                                                   uint8_t scratch[restrict],
                                                   uint32_t scratch_size);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_trackFeaturesLK_i8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - The old_image and new_image shall have the same dimentions
 *    - The old_gradX and old_gradY images shall have the same dimentions and strides
 *    - The termination value shall be in the valid range
 *    - The scratch memory shall be at least window_size*window_size*6 + 2 bytes
 *
 * @par
 *   @param [in]       old_image[]        Pointer to array containing old input image (UQ8.0)
 *   @param [in]      *old_image_addr     Pointer to structure containing dimensional information of old_image
 *   @param [in]       new_image[]        Pointer to array containing new input image (UQ8.0)
 *   @param [in]      *new_image_addr     Pointer to structure containing dimensional information of new_image
 *   @param [in]       old_gradX[]        Pointer to array containing old X gradient image (SQ15.0)
 *   @param [in]      *old_gradX_addr     Pointer to structure containing dimensional information of old_gradX
 *   @param [in]       old_gradY[]        Pointer to array containing old Y gradient image (SQ15.0)
 *   @param [in]      *old_gradY_addr     Pointer to structure containing dimensional information of old_gradY
 *   @param [in,out]   old_points[]       Pointer to array containing keypoint list from old_image (F32.0)
 *   @param [in,out]   new_points[]       Pointer to array containing keypoint list for new_image (F32.0)
 *   @param [in,out]   tracking_status[]  Status of each point in the list (0: not tracked; 1: tracked)
 *   @param [in]       num_points         Number of entries in each : old_points, new_points, and tracking_status arrays.
 *   @param [in]       max_iters          Maximum number of iterations allowed before terminating the algorithm for each point.
 *   @param [in]       epsilon            Maximum error allowed before terminating the algorithm for each point.
 *   @param [in]       scale              Scale factor to apply to both the old_points and new_points list before tracking.
 *   @param [in]       window_size        Window size
 *   @param [in]       level              Flag to indicate if tracking_status[] should be updated or not (0: update; non-zero: no update)
 *   @param [in]       termination        Termination criteria: VXLIB_TERM_ITERATIONS, VXLIB_TERM_EPSILON, or VXLIB_TERM_BOTH
 *   @param [in]       scratch[]          Scratch buffer.  Should allocate window_size*window_size*6 + 2 bytes.
 *   @param [in]       scratch_size       Size of the scratch buffer (for parameter checking)
 *
 */
VXLIB_STATUS    VXLIB_trackFeaturesLK_i8u_checkParams(const uint8_t old_image[restrict],
                                                   const VXLIB_bufParams2D_t *old_image_addr,
                                                   const uint8_t new_image[restrict],
                                                   const VXLIB_bufParams2D_t *new_image_addr,
                                                   const int16_t old_gradX[restrict],
                                                   const VXLIB_bufParams2D_t *old_gradX_addr,
                                                   const int16_t old_gradY[restrict],
                                                   const VXLIB_bufParams2D_t *old_gradY_addr,
                                                   const __float2_t old_points[restrict],
                                                   const __float2_t new_points[restrict],
                                                   const uint8_t tracking_status[restrict],
                                                   uint32_t num_points,
                                                   uint32_t max_iters,
                                                   VXLIB_F32 epsilon,
                                                   VXLIB_F32 scale,
                                                   uint8_t window_size,
                                                   uint8_t level,
                                                   uint8_t termination,
                                                   const uint8_t scratch[restrict],
                                                   uint32_t scratch_size);
/** @} */
#endif

