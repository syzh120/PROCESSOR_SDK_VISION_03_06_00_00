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

#ifndef VLIB_RELU_MAXPOOLING_2X2_SKIP2_TILE_H_
#define VLIB_RELU_MAXPOOLING_2X2_SKIP2_TILE_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_tiler.h"

/** @defgroup VLIB_ReLU_MaxPooling_2x2_skip2_tile */
/** @ingroup  VLIB_ReLU_MaxPooling_2x2_skip2_tile */
/* @{ */

/**
 * @par Description:
 *  Performs 2x2 ReLU and MaxPooling operations on N 32-bit input channels producing N 32-bit
 *  output channels.<BR>
 *
 *  After maxpooling operation, each W x H 32-bit inputs of a single input channel are skipped
 *  in alternate horizontal and vertical direction, to produce one (W/2) x (H/2) 32-bit outputs.
 *  This output is then rounded and shifted down to a 16-bit range.
 *  It is then fed to ReLU operation to remove negative values and stored as output.
 *
 * @par
 *   @param [in]      *pInChannel       Pointer to N 32-bit input channels
 *   @param [out]     *pOutChannel      Pointer to N 16-bit ouput channels
 *   @param [in]      *shiftQ           Shift factor to adjust output range
 *   @param [in]      *coeffQ           Shift factor to adjust coefficient range
 *
 * @par Assumptions:
 *   - Input and output buffer address is aligned to 8-bytes
 *   - Width and height of the buffer must be a multiple of 2
 *
 * @par Implementation Notes:
 *      The code is interruptible. <BR>
 *
 */

void VLIB_ReLU_MaxPooling_2x2_skip2_tile(const sBuffer_t *pInChannel,
                                         const sBuffer_t *pOutChannel,
                                         uint32_t shiftQ,
                                         uint32_t coeffQ);

/** @} */
#endif /* VLIB_RELU_MAXPOOLING_2X2_SKIP2_TILE_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_ReLU_MaxPooling_2x2_skip2_tile.h                     */
/* ======================================================================== */

