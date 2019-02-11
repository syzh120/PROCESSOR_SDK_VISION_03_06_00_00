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

#ifndef VXLIB_HARRISCORNERSNMS_I32F_H_
#define VXLIB_HARRISCORNERSNMS_I32F_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_harrisCornersNMS_i32f */
/** @ingroup  VXLIB_harrisCornersNMS_i32f */
/* @{ */
/**
 * @par Description:
 *  Performs the Euclidian distance based non-max suppression for harris corner detector.
 *
 * @par Method:
 *  If all input features are sorted from largest to smallest, then each feature is added
 *  to the output list if there is not already a feature in this output list which is within
 *  the Euclidean distance given.
 *
 * @par
 *   @param [in]       corners_in[]          Pointer to array containing input corner keypoint list (UQ32.0)
 *   @param [in]       strengths_in[]        Pointer to array containing input strength list, coresponding to corners_in[] (F32)
 *   @param [in]       num_corners_in        Total number of corners in the corners_in list.
 *   @param [out]      corners_out[]         Pointer to array containing output corner keypoint list (UQ32.0)
 *   @param [out]      strengths_out[]       Pointer to array containing output strength list, coresponding to corners_out[] (F32)
 *   @param [in]       corners_out_capacity  Number of keypoints allocated in the corners and strengths output buffers.
 *   @param [out]     *num_corners_out      Total number of corners returned in the corners_out list.
 *   @param [in]       scratch[]             Pointer to scratch buffer (UQ8.0)
 *   @param [in]       scratch_size          Size of the scratch buffer (for parameter checking)
 *   @param [in]       min_distance          Radial Euclidean distance for non-maximum suppression
 *   @param [in,out]  *iterations            [Input] Maximum number of iterations, [Output] Actual number of iterations
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - The corners_in[] array is ordered in raster-scan across and image
 *    - Each 32-bit word in corners_in[] array is composed of 2 16-bit half words representing
 *      x and y coordinates, such that corners_in[i] = (y(i) << 16) | x(i);
 *    - The strengths_in[] array corresponds to the corners_in list
 *    - The corners_out[] array is ordered in raster-scan across and image
 *    - Each 32-bit word in corners_out[] array is composed of 2 16-bit half words representing
 *      x and y coordinates, such that corners_out[i] = (y(i) << 16) | x(i);
 *    - The strengths_out[] array corresponds to the corners_out list
 *    - The scratch buffer should be 2 byte aligned.
 *    - The scratch buffer should be at least 2*min( ((min_distance+1)*2)^2 / 9, num_corners_in) + num_corners_in bytes
 *    - The iterations parameter may be set to NULL in most cases.  The algorithm may take a few iterations to converge
 *      on the answer, but it typically converges in less than 5 iterations.
 *      - The user can pass a pointer to a location with a non-zero number to set the the maximum number of iterations,
 *        but if this number is too small, too many features will be suppressed.  In this case, the algorithm will
 *        return the actual number of iterations it took.
 *      - If the user passes a pointer to a location with a zero, then the algorithm will take as many iterations as it needs
 *        and return the actual number of iterations it took.
 *
 */
VXLIB_STATUS    VXLIB_harrisCornersNMS_i32f(const uint32_t corners_in[restrict],
                                        const VXLIB_F32 strengths_in[restrict],
                                        uint32_t num_corners_in,
                                        uint32_t corners_out[restrict],
                                        VXLIB_F32 strengths_out[restrict],
                                        uint32_t corners_out_capacity,
                                        uint32_t *num_corners_out,
                                        int8_t scratch[restrict],
                                        uint32_t scratch_size,
                                        VXLIB_F32 min_distance,
                                        uint8_t *iterations);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_harrisCornersNMS_i32f function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - The scratch memory should be at least 2*min( ((min_distance+1)*2)^2 / 9, num_corners_in) + num_corners_in bytes
 *
 * @par
 *   @param [in]       corners_in[]          Pointer to array containing input corner keypoint list (UQ32.0)
 *   @param [in]       strengths_in[]        Pointer to array containing input strength list, coresponding to corners_in[] (F32)
 *   @param [in]       num_corners_in        Total number of corners in the corners_in list.
 *   @param [out]      corners_out[]         Pointer to array containing output corner keypoint list (UQ32.0)
 *   @param [out]      strengths_out[]       Pointer to array containing output strength list, coresponding to corners_out[] (F32)
 *   @param [in]       corners_out_capacity  Number of keypoints allocated in the corners and strengths output buffers.
 *   @param [out]     *num_corners_out      Total number of corners returned in the corners_out list.
 *   @param [in]       scratch[]             Pointer to scratch buffer (UQ8.0)
 *   @param [in]       scratch_size          Size of the scratch buffer (for parameter checking)
 *   @param [in]       min_distance          Radial Euclidean distance for non-maximum suppression
 *   @param [in,out]  *iterations            [Input] Maximum number of iterations, [Output] Actual number of iterations
 *
 */
VXLIB_STATUS    VXLIB_harrisCornersNMS_i32f_checkParams(const uint32_t corners_in[],
                                                    const VXLIB_F32 strengths_in[],
                                                    uint32_t num_corners_in,
                                                    const uint32_t corners_out[],
                                                    const VXLIB_F32 strengths_out[],
                                                    uint32_t corners_out_capacity,
                                                    const uint32_t *num_corners_out,
                                                    const int8_t scratch[],
                                                    uint32_t scratch_size,
                                                    VXLIB_F32 min_distance,
                                                    const uint8_t *iterations);
/** @} */
#endif

