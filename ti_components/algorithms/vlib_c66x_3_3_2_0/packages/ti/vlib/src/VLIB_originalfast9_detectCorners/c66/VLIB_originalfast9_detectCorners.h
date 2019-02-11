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

#ifndef VLIB_ORIGINALFAST9_DETECTCORNERS_H_
#define VLIB_ORIGINALFAST9_DETECTCORNERS_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_originalfast9_detectCorners */
/** @ingroup  VLIB_originalfast9_detectCorners */
/* @{ */

/**
 * @par Description:
 *  Detects and returns corners in image \c im based on FAST9 algorithm.
 *
 * @par
 *  @param [in]  *im                Pointer to the image buffer - Must be double-word(64-bit) aligned.
 *  @param [in]   xsize             Image width - Must be a multiple of 8.
 *  @param [in]   ysize             Image height - Must be a multiple of 8.
 *  @param [in]   stride            Image stride
 *  @param [in]   marginPixels      Fast corners will not be found within this distance from each edge of the image
 *  @param [in]   b                 The FAST difference threshold. A pixel must be this much brighter/darker than the center to be considered different
 *  @param [out]  ret_n_features    The number of features detected
 *  @param [out] *ret_features      A pointer to allocated memory, to store the detected features - Must be double-word(64-bit) aligned.
 *
 * @par Assumptions:
 * - \c im and \c ret_features must both be double-word(64-bit) aligned.
 * - \c xsize and \c ysize must both be a multiple of 8
 * - \c xsize must be greater than CEILING(\c marginPixels, 4) * 2.
 * - \c ysize must be greater than 2 * \c marginPixels.
 * - Max number of features to find is set to \ref CORB_MAX_FEATURES, therefore, the \c ret_features buffer should be allocated
 *   \ref CORB_MAX_FEATURES*sizeof(\ref CORBFeature)
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void VLIB_originalfast9_detectCorners(const uint8_t *restrict im,
                                      int32_t xsize,
                                      int32_t ysize,
                                      int32_t stride,
                                      int32_t marginPixels,
                                      int32_t b,
                                      int32_t *ret_n_features,
                                      CORBFeature *ret_features);

/** @} */
#endif /* VLIB_ORIGINALFAST9_DETECTCORNERS_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_originalfast9_detectCorners.h                        */
/* ======================================================================== */

