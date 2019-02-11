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
**|        Copyright (c) 2007 - 2014 Texas Instruments Incorporated          |**
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

#ifndef VLIB_ORIGINALFAST9_SCORE_H_
#define VLIB_ORIGINALFAST9_SCORE_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_originalfast9_score */
/** @ingroup  VLIB_originalfast9_score */
/* @{ */

/**
 * @par Description:
 *  This function computes the FAST9 score for a list of corners.
 *
 * @par
 *  @param [in]     *img           Pointer to the image buffer.
 *  @param [in]      stride        The stride of the image.
 *  @param [in]     *featuresLoc   Co-ordinates of feature point. x and y ordinate each of unsigned 16 bit packed into 32 bit. Lower 16 bit should be x location.
 *  @param [in]      numFeatures   Number of feature points given to API. Must be multiple of 8.
 *  @param [in]      b             The threshold used while finding the fast9 corners. In practical scenario this value will not used.
 *  @param [out]     score         Output score for each input feature point
 *  @param [in]      scratch       Scratch buffer needed by kernel. User should provide 463 bytes buffer no alignment is needed.
 *
 * @par Assumptions:
 * - \c score size should be at least as large as the \c numFeatures value.
 * - \c numFeatures should be multiple of 8.
 * - If all the corners given to API is the real corner points found through fast9 algorithm then input \b will not be used inside this kernel.
 * - input \c b will be returned as a score for a point, if that point is not a candidate for corner. like for flat image no point can be a corner.
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void VLIB_originalfast9_score(const uint8_t  *restrict img,
                              uint16_t stride,
                              const uint32_t *featuresLoc,
                              uint32_t numFeatures,
                              uint8_t b,
                              uint8_t  *restrict score,
                              uint8_t  *restrict scratch);
/** @} */
#endif /* VLIB_ORIGINALFAST9_SCORE_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_originalfast9_score.h                                */
/* ======================================================================== */

