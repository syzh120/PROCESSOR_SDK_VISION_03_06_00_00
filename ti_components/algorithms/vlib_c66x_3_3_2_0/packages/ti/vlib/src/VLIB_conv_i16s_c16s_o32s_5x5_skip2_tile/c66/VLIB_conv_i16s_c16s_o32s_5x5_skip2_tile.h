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
**|        Copyright (c) 2007 - 2015 Texas Instruments Incorporated          |**
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

#ifndef VLIB_CONV_I16S_C16S_O32S_5X5_SKIP2_TILE_H_
#define VLIB_CONV_I16S_C16S_O32S_5X5_SKIP2_TILE_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_tiler.h"

/** @defgroup VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile */
/** @ingroup  VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile */
/* @{ */

/**
 * @par Description:
 *  Performs 5x5 convolution of N 16-bit inputs with N x M 16-bit weights producing M
 *  32-bit outputs.<BR>
 *  Each W x H 16-bit inputs, skipped in alternate horizontal and vertical pixels, are convolved with
 *  corresponding K x K 16bit weights and accumulated N times to produce one (((W - K) + 1)/ 2) x (((H - K) + 1)/2)
 *  32-bit output.
 *  This output is then rounded and shifted down to a 32-bit range prior to storing
 *  in the output array. This process is repeated for M outputs.
 *
 * @par
 *   @param [in]      *pInChannel       Pointer to N 16-bit input channels
 *   @param [in]      *pWeights         Pointer to N x M 16-bit weights
 *   @param [in]      *pBias            Pointer to M 16-bit bias values
 *   @param [out]     *pOutChannel      Pointer to M 32-bit ouput channels
 *   @param [in]      *shiftQ           Shift factor to adjust output range
 *   @param [in]      *coeffQ           Shift factor to adjust coefficient range
 *
 * @par Assumptions:
 *   - Input, output, weights, bias buffer address is aligned to 8-bytes
 *   - Pitch of input, output, weights must be multiple of 8
 *   - Weights value must be zero padded.
 *     A 5x5 kernel must be stored as 8x5 matrix with last 3 columns zeroed out.
 *     Eg: 1 1 1 1 1 0 0 0
 *         2 2 2 2 2 0 0 0
 *         3 3 3 3 3 0 0 0
 *         4 4 4 4 4 0 0 0
 *         5 5 5 5 5 0 0 0
 *
 * @par Implementation Notes:
 *      The code is interruptible. <BR>
 *      This code is compatible with C66x processors. <BR>
 *
 */

void VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile(const sBuffer_t *pInChannel,
                                             const sBuffer_t *pWeights,
                                             const sBuffer_t *pBias,
                                             const sBuffer_t *pOutChannel,
                                             uint32_t shiftQ,
                                             uint32_t coeffQ);

/** @} */
#endif /* VLIB_CONV_I16S_C16S_O32S_5X5_SKIP2_TILE_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_conv_i16s_c16s_o32s_5x5_skip2_tile.h                 */
/* ======================================================================== */

