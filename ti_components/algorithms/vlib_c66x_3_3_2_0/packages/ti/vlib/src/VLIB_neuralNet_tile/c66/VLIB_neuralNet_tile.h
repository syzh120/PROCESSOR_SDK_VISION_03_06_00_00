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

#ifndef VLIB_NEURALNET_TILE_H_
#define VLIB_NEURALNET_TILE_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_tiler.h"

/** @defgroup VLIB_neuralNet_tile */
/** @ingroup  VLIB_neuralNet_tile */
/* @{ */

/**
 * @par Description:
 *  Produces L dotproduct values where each dotproduct is of multiplication
 *  and addition of N 16-bit inputs and N 16-bit weights. Each dotproduct value
 *  is added with a bias, rounded then shifted down to a signed 16-bit range.
 *  Depending on the user defined mode different activation functions such as
 *  ReLU, Sigmoid, Tanh are performed prior to storing in the output array.
 *  This process is repeated for M outputs. <BR>
 *  @verbatim
    Data usage example (cols x rows):
                Input           : 1152 x 1          : N x M
                Weight          : 1152 x 92         : N x L
                Output          : 92 x 1            : L x M
    @endverbatim
 * @par
 *   @param [in]      *pInNodes        Pointer to N x M 16-bit input nodes
 *   @param [in]      *pWeight         Pointer to N x L 16-bit weights
 *   @param [in]      *pBias           Pointer to L 16-bit bias values
 *   @param [out]     *pOutNodes       Pointer to L x M 16-bit ouput nodes
 *   @param [in]       mode            To select activation type
 *                                     1-ReLU, 2-Sigmoid, 3-TanH
 *   @param [in]       shiftQ          Shift value to adjust output range
 *   @param [in]       coeffQ          Shift value to adjust co-efficient range
 *   @param [in]       dropOutQ        Additional shift value to added with
 *                                     shiftQ to adjust output range when
 *                                     dropout method is used while training
 *
 * @par Assumptions:
 *   - Input, output, weights and bias buffers are aligned to 8-byte boundary.
 *   - The number of cols in pWeight is assumed to be a multiple of 32.
 *
 * @par Implementation Notes:
 *      The code is interruptible. <BR>
 *
 */

void VLIB_neuralNet_tile(const sBuffer_t *pInNodes,
                         const sBuffer_t *pWeight,
                         const sBuffer_t *pBias,
                         const sBuffer_t *pOutNodes,
                         uint32_t mode,
                         uint32_t shiftQ,
                         uint32_t coeffQ,
                         uint32_t dropOutQ);

/** @} */
#endif /* VLIB_NEURALNET_TILE_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_neuralNet_tile.h                                     */
/* ======================================================================== */

