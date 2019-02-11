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
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
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

#ifndef VLIB_ORB_COMPUTEORIENTATION_H_
#define VLIB_ORB_COMPUTEORIENTATION_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_ORB_computeOrientation */
/** @ingroup  VLIB_ORB_computeOrientation */
/* @{ */

/**
 * @par Description:
 *  This function can be called after the fast corners are detected so that the feature list is populated.
 *  Ideally additional steps would be taken (like \ref VLIB_ORB_bestFeaturesToFront) to reduce the number of features
 *  that this function would operate on and save time, but not mandatory. This function simply computes the
 *  orientation of feature points in degrees.
 *
 * @par
 *  @param [in]  *inImg           Input 8 bit image data.
 *  @param [in]  imgWidth         Width of image in pixels.
 *  @param [in]  imgHeight        Height of image in pixels.
 *  @param [in]  imgPitch         Pitch of the input image in pixels.
 *  @param [in]  *featuresLoc     Co-ordinates of the feature points. It is bit packed 32 bit data for each feature point, where 16 bit LSB is x co-ordinate.
 *  @param [in]  numFeatures      Total number of feature points.
 *  @param [out] outAngles        Output angle corresponding for each feature points in degree.
 *  @param [in]  *momentPattern   Specific ORB pattern for moment calculation. One of such example is {15, 15, 15, 15, 14, 14, 14, 13, 13, 12, 11, 10, 9, 8, 6, 3}
 *  @param [in]  scratch          Scratch buffer of size 1991 bytes needed by API.
 *
 * @par Assumptions:
 *- momentPattern is normally constant for a complete use case. In scratch few mask pattern are created specific to moment pattern.
 *  If momentPattern pointer provided is NULL then already created mask in scratch area can be used for rest of the flow except
 *  first frame. Hence it advisable to pass non zero momentPattern pointer in first call, and later on it should be passed as
 *  NULL, along with same scratch buffer, so that computation related to const persitant data generation can be avoided in later frames.
 *- momentPattern[i] denotes range of pixels to be considered in moment calculation in (+) & (-) x directions for row (i) & (-i),
 *  assuming origin being placed at the center of 31x31 Orb patch. E.g. momentPattern[2] value is '15' then it indicates the pixels
 *  ranging from -15 to 15 is considered in row number (2) & (-2) in moment calculation.  The below Orb patch indicates a '1' for
 *  every pixel to be considered in the moment computation for the example momentPattern[]= {15, 15, 15, 15, 14, 14, 14, 13, 13, 12, 11, 10, 9, 8, 6, 3}.<BR>
 *  0000000000001111111000000000000 <BR>
 *  0000000001111111111111000000000 <BR>
 *  0000000111111111111111110000000 <BR>
 *  0000001111111111111111111000000 <BR>
 *  0000011111111111111111111100000 <BR>
 *  0000111111111111111111111110000 <BR>
 *  0001111111111111111111111111000 <BR>
 *  0011111111111111111111111111100 <BR>
 *  0011111111111111111111111111100 <BR>
 *  0111111111111111111111111111110 <BR>
 *  0111111111111111111111111111110 <BR>
 *  0111111111111111111111111111110 <BR>
 *  1111111111111111111111111111111 <BR>
 *  1111111111111111111111111111111 <BR>
 *  1111111111111111111111111111111 <BR>
 *  1111111111111111111111111111111 <BR>
 *  1111111111111111111111111111111 <BR>
 *  1111111111111111111111111111111 <BR>
 *  1111111111111111111111111111111 <BR>
 *  0111111111111111111111111111110 <BR>
 *  0111111111111111111111111111110 <BR>
 *  0111111111111111111111111111110 <BR>
 *  0011111111111111111111111111100 <BR>
 *  0011111111111111111111111111100 <BR>
 *  0001111111111111111111111111000 <BR>
 *  0000111111111111111111111110000 <BR>
 *  0000011111111111111111111100000 <BR>
 *  0000001111111111111111111000000 <BR>
 *  0000000111111111111111110000000 <BR>
 *  0000000001111111111111000000000 <BR>
 *  0000000000001111111000000000000
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

CORBResult    VLIB_ORB_computeOrientation(uint8_t inImg[restrict],
                                          uint16_t imgWidth,
                                          uint16_t imgHeight,
                                          uint16_t imgPitch,
                                          uint32_t featuresLoc[restrict],
                                          uint16_t numFeatures,
                                          int16_t outAngles[restrict],
                                          uint8_t momentPattern[restrict],
                                          uint8_t scratch[restrict]);

/** @} */
#endif /* VLIB_ORB_COMPUTEORIENTATION_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_computeOrientation.h                             */
/* ======================================================================== */

