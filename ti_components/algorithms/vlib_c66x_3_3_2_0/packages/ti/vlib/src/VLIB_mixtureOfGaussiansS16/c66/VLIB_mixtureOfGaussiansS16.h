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

#ifndef VLIB_MIXTUREOFGAUSSIANSS16_H_
#define VLIB_MIXTUREOFGAUSSIANSS16_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_mixtureOfGaussiansS16 */
/** @ingroup  VLIB_mixtureOfGaussiansS16 */
/* @{ */

/**
 * @par Description:
 *   Maintain a Gaussian mixture model (GMM) for each pixel in a 16-bit video frame, and
 *   return a packed binary mask corresponding to the computed foreground regions for the input frame.
 *   This function assumes that the input stream contains a single channel (such as, luminance),
 *   and uses a maximum of 3 Gaussian components to model the pixel intensity variations.
 *
 * @par
 *  @param [in]  *Im           Input image buffer                        (UQ8.0)
 *  @param [in]  *wt           Buffer for current weights                (SQ0.15)
 *  @param [in]  *mu           Buffer for current means                  (SQ8.7)
 *  @param [in]  *var          Buffer for current variances              (SQ12.3)
 *  @param [in]  *compNum      Buffer for indices indicating which mode a pixel belongs to  (UQ8.0)
 *  @param [in]  *updateMask8  Buffer for internal use                   (UQ8.0)
 *  @param [out] *Im_mask      Computed binary foreground mask           (32-bit packed binary)
 *  @param [in]   im_size      Pixel count of input image buffer         (SQ31.0)
 *  @param [in]   alpha        Update rate for weights                   (SQ0.15)
 *  @param [in]   rho          Update rate for heights                   (SQ0.15)
 *  @param [in]   delta        Mahalanobis distance threshold            (SQ4.11)
 *  @param [in]   T            Background subtraction threshold          (SQ0.15)
 *  @param [in]   ini_wt       Initial weight for new component          (SQ0.15)
 *  @param [in]   ini_var      Initial variance for new component        (SQ12.3)
 *
 * @par Assumptions
 * - If the input image contains N pixels, the input buffers should have the following sizes:
 *     - wt: 3.N data elements
 *     - mu: 3.N data elements
 *     - var: 3.N data elements
 *     - compNum: N data elements
 *     - updateMask8: N data elements
 *     - Im_mask: N/32 data elements
 * - wt, mu, and var buffers should be initialized to 0 before invoking the function for the first time.
 * - I/O buffers are assumed to be 64-bit aligned in memory.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_mixtureOfGaussiansS16(const uint8_t *restrict Im,
                                   int16_t *restrict wt,
                                   int16_t *restrict mu,
                                   int16_t *restrict var,
                                   uint8_t *restrict compNum,
                                   uint8_t *restrict updateMask8,
                                   uint32_t *restrict Im_mask,
                                   const int32_t im_size,
                                   const int16_t alpha,
                                   const int16_t rho,
                                   const int16_t delta,
                                   const int16_t T,
                                   const int16_t ini_wt,
                                   const int16_t ini_var);

/** @} */
#endif /* VLIB_MIXTUREOFGAUSSIANSS16_H_ */
/* ======================================================================== */
/*  End of file:  VLIB_mixtureOfGaussiansS16.h                              */
/* ======================================================================== */

