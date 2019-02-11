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

#ifndef VLIB_NORMALFLOW_H_
#define VLIB_NORMALFLOW_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_normal_16 */
/** @ingroup  VLIB_normal_16 */
/* @{ */

/**
 * @par Description
 *  This function takes as input the x and y gradients, the gradient magnitude, and the pixel-wise image difference
 *  and computes the normal flow vectors in the x and y directions.
 *
 * @par
 *    @param [in]  *imDiff        Image difference array            (SQ15.0)
 *    @param [in]  *Emag          Array for magnitude               (SQ15.0)
 *    @param [in]  *Ex            Array for X direction gradients   (SQ15.0)
 *    @param [in]  *Ey            Array for y direction gradients   (SQ15.0)
 *    @param [in]  *LUT           LUT array for integer division    (SQ0.15)
 *    @param [in]   T             Threshold on gradient magnitude   (SQ15.0)
 *    @param [in]   numEls        Number of input pixels            (SQ31.0)
 *    @param [out] *normalFlowU   Normal flow U array               (SQ8.7)
 *    @param [out] *normalFlowV   Normal flow V array               (SQ8.7)
 *
 * @par Assumptions
 *  -  The LUT (look-up table) array should hold values such that LUT[n] = X, where X is the value 1/n represented in SQ0.15 format.
 *  -  The LUT array size should be at least equal to the largest expected value in the Emag array + 1.
 *  -  The threshold, T, on gradient magnitude ensures that only those pixels with gradient magnitude greater than T will be processed.
 *     Normal flow values for pixels that do not pass the threshold will be 0.
 *  -  Minimum number of pixels allowed is 20 (numPixels >= 20)
 *  -  Number of pixels to be processed should be a multiple of 4.
 *  -  All arrays should be double word (64-bit) aligned.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void VLIB_normalFlow_16(const int16_t *restrict imDiff,    /* SQ15.0*/
                        const int16_t *restrict Emag,      /* SQ15.0*/
                        const int16_t *restrict Ex,        /* SQ15.0*/
                        const int16_t *restrict Ey,        /* SQ15.0*/
                        const int16_t *restrict LUT,       /* SQ0.15*/
                        int16_t T,                         /* SQ15.0*/
                        int32_t numEls,                    /* SQ31.0*/
                        int16_t *normalFlowU,              /* SQ8.7*/
                        int16_t *normalFlowV);             /* SQ8.7*/
/** @} */
#endif /* VLIB_NORMALFLOW_H_ */
/* ======================================================================== */
/*  End of file:  VLIB_normalFlow_16.h                                      */
/* ======================================================================== */

