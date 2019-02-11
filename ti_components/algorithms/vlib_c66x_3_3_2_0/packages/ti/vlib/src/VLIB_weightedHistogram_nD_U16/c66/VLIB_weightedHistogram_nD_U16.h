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

#ifndef VLIB_WEIGHTEDHISTOGRAM_ND_U16_H_
#define VLIB_WEIGHTEDHISTOGRAM_ND_U16_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_weightedHistogram_nD_U16 */
/** @ingroup  VLIB_weightedHistogram_nD_U16 */
/* @{ */

/**
 * @par Description
 *  Computes a weighted multi-dimensional histogram for 16-bit vector valued variables.
 *
 * @par
 *   @param [in]     *X            Array of input values, data arranged in planar form                        (UQ16.0)
 *   @param [in]      numX         Number of individual vector elements in X                                  (SQ31.0)
 *   @param [in]      dimX         Dimensionality of vectors in X                                             (SQ31.0)
 *   @param [in]     *binWeight    Array of size numX of weight that each element contributes to the histogram              (UQ16.0)
 *   @param [in]     *numBins      Array of size dimX, each element specifies the number of bins required in that dimension (UQ16.0)
 *   @param [in]     *normVals     Array of size dimX, each element containing the normalization factor for that dimension  (UQ0.16)
 *   @param [in]     *scrap        Buffer of size numX, for internal use                                      (UQ16.0)
 *   @param [in]     *H1           Buffer of size equal to total number of bins, for internal use             (UQ16.0)
 *   @param [in,out] *H            Array of size equal to total number of bins to hold computed histogram     (UQ16.0)
 *
 * @par Assumptions
 * - The vectors in X should be arranged in planar form (see Example below).
 * - H, scrap, and H1 should each be initialized to 0.
 * - All buffers should be 8-byte aligned.
 * - The normalization factor normVals[k] for each dimension k should be set as in following equation, where M is
 *   the maximum value in dimension k, and d > 0:
 *     - normVals[k] = 1/(M+d)
 *
 * @par Example
 *
 * Assume a 3-dimensional quantity:
 *  @verbatim
  F = [9 2 3;
       5 3 5;
       8 1 3;
       4 2 3;
       7 1 1];
@endverbatim
 *
 * Where the maximum possible value in each dimension is as follows:
 *  @verbatim
  Dim 1 = 10
  Dim 2 = 4
  Dim 3 = 5
@endverbatim
 *
 * The required output is a histogram with 352 bins:
 *  @verbatim
  Dim 1 = 3 bins
  Dim 2 = 5 bins
  Dim 3 = 2 bins
@endverbatim
 *
 * The following is the form of the input:
 *  @verbatim
  X = [9 5 8 4 7 2 3 1 2 1 3 5 3 3 1];
  numX = 5;
  dimX = 3;
  binWeight = 1 (or 1/5 for a normalized histogram)
  numBins = [3 5 2];
  normVals = [1/11 1/5 1/6] * 65536;
  scrap = array of 0s of size 5
  H1 = array of 0s of size 30
  H = array of 0s of size 30
@endverbatim
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_weightedHistogram_nD_U16(const uint16_t *restrict X,
                                      const int32_t numX,
                                      const int32_t dimX,
                                      const uint16_t *binWeight,
                                      const uint16_t *restrict numBins,
                                      const uint16_t *restrict normVals,
                                      uint16_t *restrict scrap,
                                      uint16_t *H1,
                                      uint16_t *H);

#endif /* VLIB_WEIGHTEDHISTOGRAM_ND_U16_H_*/
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_weightedHistogram_nD_U16.h                           */
/* ======================================================================== */

