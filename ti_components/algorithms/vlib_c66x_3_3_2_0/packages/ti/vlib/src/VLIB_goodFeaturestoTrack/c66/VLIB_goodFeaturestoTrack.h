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

#ifndef VLIB_GOODFEATURESTOTRACK_H_
#define VLIB_GOODFEATURESTOTRACK_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_goodFeaturestoTrack*/
/** @ingroup  VLIB_goodFeaturestoTrack */
/* @{ */

/**
 * @par Description
 *  This algorithm accepts an image array which contains scores of feature candidates, and
 *  produces an 8-bit binary mask (0 or 255) of the image based on a programmable quality threshold
 *  and number of desired features.
 *  \par
 *  This function first runs a non-maximal suppression on the image using the programmable threshold (\c thresh) and
 *  filter width parameters (\c patch).  It then prunes these results out using the \c qualitypar threshold.  Then it
 *  sorts these results by ranking scores.  If the number of results are still greater than the number of desired features
 *  (\c topNfeatures), then the results are further sorted by another round of a threshold-less nonmax suppression (spatial
 *  diversity) using the \c mindist parameter.  The patch size in this round of pruning is defined by mindist*mindist.  In
 *  other words, features which appear within the surrounding mindist*mindist pixels which have a lower score, are discarded.
 *  If spatial diversity prooves to prune too many features out of the list (features falls below topNfeatures), then spatial
 *  diversity is internally disabled, and the top ranking topNfeatures features are returned without considering spatial diversity.
 *
 * @par
 *  @param [in]   im                     16-bit input image                                  (UQ16.0)
 *  @param [out]  out                    8-bit binary output image (0 or 255)                (UQ8.0)
 *  @param [in]   width                  Width of the input image                            (SQ31.0)
 *  @param [in]   height                 Height of the input image                           (SQ31.0)
 *  @param [in]   thresh                 NONMAX-SUPR Threshold for pruning peaks             (SQ15.0)
 *  @param [in]   patch                  NONMAX-SUPR Filter width                            (UQ8.0)
 *  @param [in]   qualitypar             Quality threshold to keep stronger points           (UQ8.0)
 *  @param [in]   topNfeatures           Number of strongest ranking points to retain        (SQ15.0)
 *  @param [in]   mindist                Patch size used for spatial diversity of features
 *                                        patch size = mindist*mindist                        (UQ8.0)
 *  @param [in]   outTemp                Auxiliary buffer for intermediate operations        (UQ16.0)
 *  @param [out] *good_points_number     Number of points resulting                          (SQ31.0)
 *  @param [in]   pixIndex               NONMAX-SUPR Pixel index buffer                      (SQ15.0)
 *  @param [in]   internalBuf            NONMAX-SUPR Internal buffer                         (UQ16.0)
 *  @param [in]   ind                    Index buffer                                        (SQ31.0)
 *
 * @par Assumptions
 *  - The only acceptable values for \c patch are 3, 5, and 7, representing non-maximum suppression filter masks sizes
 *    3x3, 5x5, and 7x7, respectively.
 *  - The non-maximum suppression \c pixIndex buffer (\c pixIndex) size should be (2*w*h+2)*sizeof(uint16_t) bytes
 *  - The non-maximum suppression internal buffer (\c internalBuf) size should be at least ((2 * \c patch) + (\c width * \c height))*sizeof(uint16_t) bytes
 *  - The intermediate buffer (\c outTemp) size should be at least (w*h)*sizeof(uint16_t) bytes and initialized to 0s.
 *  - The index buffer (\c ind) size should be at least (w*h)*sizeof(int32_t) bytes
 *  - The output buffer (\c out) size should be at least w*h bytes and initialized to 0s.
 *  - The output buffer (\c out) will contain a value of 255 for each location containing the filtered feature.
 *  - The value returned in \c good_points_number will be equal to or less than topNfeatures.  If less than topNfeatures, then the \c qualitypar may be too
 *    high to produce topNfeatures points.
 *
 */
void    VLIB_goodFeaturestoTrack
(
    const uint16_t im[restrict],
    uint8_t out[restrict],
    int32_t width,
    int32_t height,
    int16_t thresh,
    uint8_t patch,
    uint8_t qualitypar,
    int16_t topNfeatures,
    uint8_t mindist,
    uint16_t outTemp[],
    int32_t * restrict good_points_number,
    int16_t pixIndex[restrict],
    uint16_t internalBuf[restrict],
    int32_t ind[restrict]
);

#endif /* VLIB_GOODFEATURESTOTRACK_H_ */

/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_goodFeaturestoTrack.h                                */
/* ======================================================================== */

