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

#ifndef VXLIB_HARRISCORNERSDETECT_I32F_H_
#define VXLIB_HARRISCORNERSDETECT_I32F_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_harrisCornersDetect_i32f */
/** @ingroup  VXLIB_harrisCornersDetect_i32f */
/* @{ */
/**
 * @par Description:
 *  Given the harris score for each pixel, this function performs a threshold and non-maximum
 *  suppression operation on the immediate neighborhood pixels.  The outputs of the operation are
 *  2 arrays: 1 array for the coordinates of the possible corners, and its associated list of strength
 *  values for further processing.
 *
 * @par Method:
 * 
 *
 *
 * @par
 *   @param [in]  src[]             Pointer to array containing harris strength values (F32)
 *   @param [in]  src_addr[]        Pointer to structure containing dimensional information of src
 *   @param [out] corners[]         Pointer to array containing corner keypoint list (UQ32.0)
 *   @param [out] strengths[]       Pointer to array containing corner strength list corresponding to corners[] list (F32)
 *   @param [in]  corners_capacity  Number of keypoints allocated in the corners and strengths buffers.
 *   @param [out] num_corners       Total number of corners found in the image.
 *   @param [in]  strength_thresh   Threshold on minimum strength value for a corner to be considered.
 *   @param [in]  startX            Starting x coordinate corresponding to the pixel at the src[] pointer
 *   @param [in]  startY            Starting y coordinate corresponding to the pixel at the src[] pointer
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - The minimum image width and height are both 3.
 *    - Corners can not be detected in the 1 pixel that makes up the image border.
 *    - Each 32-bit word in corners[] array is composed of 2 16-bit half words representing
 *      x and y coordinates, such that corners[i] = (y(i) << 16) | x(i);
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Width as a multiple of 2
 */
VXLIB_STATUS    VXLIB_harrisCornersDetect_i32f(const VXLIB_F32 src[restrict],
                                     const VXLIB_bufParams2D_t * src_addr,
                                     uint32_t corners[restrict],
                                     VXLIB_F32 strengths[restrict],
                                     uint32_t corners_capacity,
                                     uint32_t *num_corners,
                                     VXLIB_F32 strength_thresh,
                                     uint16_t startX,
                                     uint16_t startY);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_harrisCornersDetect_i32f function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - The strides of each image shall be equal to or greater than the x dimension
 *
 * @par
 *   @param [in]  src[]             Pointer to array containing harris strength values (F32)
 *   @param [in]  src_addr[]        Pointer to structure containing dimensional information of src
 *   @param [out] corners[]         Pointer to array containing corner keypoint list (UQ32.0)
 *   @param [out] strengths[]       Pointer to array containing corner strength list corresponding to corners[] list (F32)
 *   @param [in]  corners_capacity  Number of keypoints allocated in the corners and strengths buffers.
 *   @param [out] num_corners       Total number of corners found in the image.
 *   @param [in]  strength_thresh   Threshold on minimum strength value for a corner to be considered.
 *   @param [in]  startX            Starting x coordinate corresponding to the pixel at the src[] pointer
 *   @param [in]  startY            Starting y coordinate corresponding to the pixel at the src[] pointer
 *
 */

VXLIB_STATUS VXLIB_harrisCornersDetect_i32f_checkParams(const VXLIB_F32 src[],
                                              const VXLIB_bufParams2D_t * src_addr,
                                              const uint32_t corners[],
                                              const VXLIB_F32 strengths[],
                                              uint32_t corners_capacity,
                                              const uint32_t *num_corners,
                                              VXLIB_F32 strength_thresh,
                                              uint16_t startX,
                                              uint16_t startY);
/** @} */
#endif

