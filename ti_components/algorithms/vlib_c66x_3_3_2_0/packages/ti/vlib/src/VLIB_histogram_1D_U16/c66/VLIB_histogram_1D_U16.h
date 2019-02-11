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

#ifndef VLIB_HISTOGRAM1D16_H_
#define VLIB_HISTOGRAM1D16_H_ 1

#include "../../common/VLIB_types.h"


/** @defgroup VLIB_histogram_1D_U16 */
/** @ingroup  VLIB_histogram_1D_U16 */
/* @{ */

/**
 * @par Description
 *  Computes histogram from array of 16-bit unsigned integers using user-specified bins.
 *
 * @par
 *   @param [in]     *X            Input array of scalar                                                   (UQ16.0)
 *   @param [in]      numX         Number of elements in X                                                 (SQ31.0)
 *   @param [in]      numBins      Number of bins                                                          (SQ31.0)
 *   @param [in]      binWeight    Value to accumulate in histogram bins                                   (UQ16.0)
 *   @param [in]     *histArray    Array for internal use, initialized by \ref VLIB_histogram_1D_Init_U16  (UQ16.0)
 *   @param [in]     *H1           Array for internal use                                                  (UQ16.0)
 *   @param [in,out] *H            Array to hold the computed histogram                                    (UQ16.0)
 *
 * @par Assumptions
 * - histArray should be initialized by calling \ref VLIB_histogram_1D_Init_U16.
 * - H[k] will hold the number of elements that satisfy the following equation:
 *     - binEdges[k] <= X[i] < binEdges[k+1] (for k=0 .. numBins-2)
 * - The last bin H[numBins-1] will hold the number of elements that satisfy the following equation:
 *     - X[i] == binEdges[numBins-1]
 * - All values below binEdges[0] and above binEdges[numBins-1] will not be accumulated in any of the
 *   bins.
 * - H, and H1 should be of length numBins, initialized to 0.
 * - numX should be a multiple of 2
 * - X should be 4 byte aligned
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_histogram_1D_U16(const uint16_t *restrict X,
                              const int32_t numX,
                              const int32_t numBins,
                              const uint16_t binWeight,
                              const uint16_t *restrict histArray,
                              uint16_t *restrict H1,
                              uint16_t *restrict H);

/** @} */
#endif /* VLIB_HISTOGRAM1D16_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_histogram_1D_U16.h                                   */
/* ======================================================================== */

