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

#ifndef VLIB_ORB_COMPUTERBRIEF_H_
#define VLIB_ORB_COMPUTERBRIEF_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_ORB_computeRBrief */
/** @ingroup  VLIB_ORB_computeRBrief */
/* @{ */

/**
 * @par Description:
 *  Computes the brief descriptor for each feature. This function can be called after the fast corners are detected.
 *  Additionally, since this function requires angles to be defined for each feature, \ref VLIB_ORB_computeOrientation
 *  should have been run.  Finally, this function requires that an integral image is available in the intgrlImg
 *  pointer.
 *
 * @par
 *  @param [in]  *intgrlImg          Integral image of the input image
 *  @param [in]  *intgrlImgPitch     Pitch of the integral image in pixels
 *  @param [in]   imgWidth           Width of the image in pixels
 *  @param [in]   imgHeight          Height of the image in pixels
 *  @param [in]  *featuresLoc        Location of feature points in 32 bit packed form. lower 16 bit has to be x co ordinate
 *  @param [in]  *featuresWedge      Angle bin for each feature point
 *  @param [in]   numFeatures        Total number of feature points
 *  @param [in]  *relativePattern    Top left byte offset for each pattern location from center location. One word for one offset
 *  @param [out] *outFeatureDesc     output pointer where output descriptor (of 256 bits) for each feature point
 *
 * @par Assumptions:
 * - \c intgrlImg buffer should be word aligned.
 * - \c relativePattern should be double word aligned
 * - One of the following FAST corner detectors is run prior to this function:
 *     - @ref VLIB_afast9_detectCorners
 *     - @ref VLIB_originalfast9_detectCorners
 *     - @ref VLIB_afast12_detectCorners
 *     - @ref VLIB_originalfast12_detectCorners
 * - \ref VLIB_ORB_computeOrientation should be run before running this function.
 * - \ref VLIB_integralImage8 should be run before running this function.
 * - The list of features passed to this function should NOT be within the border area of the image (w/in 16 pixels * 1.42 of the edge
 *   of the image) since this function uses an orientation independent 32x32 patch size around the feature to compute descriptor
 * - Angle of each feature point has to found , and then that has to be binned outside the kernel, and should be passed through \c featuresWedge
 * - size of the \c relativePattern buffer is 30 ( total angle bins) * 256 ( 256 point set) * 2 (2 sets of points) * 4 (sizeof(int))
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
uint32_t    VLIB_ORB_computeRBrief(const uint32_t intgrlImg[restrict],
                                   uint16_t intgrlImgPitch,
                                   uint16_t imgWidth,
                                   uint16_t imgHeight,
                                   const uint32_t featuresLoc[restrict],
                                   const uint8_t featuresWedge[restrict],
                                   uint32_t numFeatures,
                                   const int32_t relativePattern[restrict],
                                   uint8_t outFeatureDesc[restrict]);

/** @} */
#endif /* VLIB_ORB_COMPUTERBRIEF_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_computeRBrief.h                                  */
/* ======================================================================== */

