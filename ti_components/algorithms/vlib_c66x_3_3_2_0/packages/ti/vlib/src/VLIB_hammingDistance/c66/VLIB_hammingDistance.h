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
**|  with devices manufactured by or for TI ('TI Devices').  No hardware     |**
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

#ifndef VLIB_HAMMINGDISTANCE_H_
#define VLIB_HAMMINGDISTANCE_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_hammingDistance */
/** @ingroup  VLIB_hammingDistance */
/* @{ */

/**
 * @par Description:
 *  This function implements hamming distance on a 2D array of bytes.
 *  The first dimension is an array of xSize bytes, while the second dimension is of ySize arrays.
 *  There are two modes.
 *    - Mode 0 - One-to-One i.e., pHammingDistance[i] = HammingDistance(pString1[i], pString2[i]); i = 0,1,2, ...ySize-1
 *    - Mode 1 - Many-to-One i.e., pHammingDistance[i] = HammingDistance(pString1[i], pString2[0]); i = 0,1,2, ...ySize-1
 *  @par
 *  pHamming distance is an array of ySize words.
 *
 * @par
 *    @param [in]  pString1             Pointer to an array of byte arrays          (UQ8.0)
 *    @param [in]  pString2             Pointer to an array of byte arrays          (UQ8.0)
 *    @param [in]  xSize                Number of bytes in the first dimension      (UQ32.0)
 *    @param [in]  ySize                Number of rows (size of second dimension)   (UQ32.0)
 *    @param [in]  mode                 0: one-to-one\n
 *                                      1: many-to-one
 *    @param [in]  xPitch               Number of bytes between start of each string (UQ32.0)
 *    @param [out] pHammingDistance     Output array of hamming distances (size = ySize) (UQ32.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be four byte aligned and not aliased.
 *    - xSize is assumed to be a multiple of 4.
 *    - For Mode 0, pString1 and pString2 should be equal size (xSize * ySize) bytes
 *    - For Mode 1, pString1 should be of size (xSize * ySize) bytes, while pString2 should
 *      at least be of size xSize bytes.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed-point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_hammingDistance(const uint8_t pString1[restrict],
                             const uint8_t pString2[restrict],
                             uint32_t xSize,
                             uint32_t ySize,
                             uint32_t mode,
                             uint32_t xPitch,
                             uint32_t pHammingDistance[restrict]);
/** @} */
#endif /* VLIB_HAMMINGDISTANCE_H_ */


/* ======================================================================== */
/*  End of file:  VLIB_hammingDistance.h                                   */
/* ======================================================================== */

