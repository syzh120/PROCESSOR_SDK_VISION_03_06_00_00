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

#ifndef VLIB_BLOCK_STATISTICS_H_

#define VLIB_BLOCK_STATISTICS_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_blockStatistics */
/** @ingroup  VLIB_blockStatistics */
/* @{ */

/**
 * @par Description:
 *   This routine accepts an 8-bit grayscale input image of size imageWidth by
 *   imageHeight with a stride of imageStride. The image is divided into
 *   non-overlapping blocks of statBlockWidth by statBlockHeight. This kernel
 *   computes block statistics over these non-overlapping blocks. Statistics
 *   calculated are block minima, block maxima, block mean and block variance.
 *   Output of minimum, maximum , mean and variance are available in buffer
 *   pMinimum, pMaximum, pMean, pVariance respectively. User needs to allocate
 *   these output buffers appropriately.
 *
 * @par
 *   @param [in]  pInput[]         input data pointer                                (UQ8.0 )
 *   @param [in]  imageStride      stride between input lines, in elements           (UQ16.0)
 *   @param [in]  imageWidth       width of input data, in elements                  (UQ16.0)
 *   @param [in]  imageHeight      height of input data, in elements                 (UQ16.0)
 *   @param [in]  statBlockWidth   width of the statistics block                     (UQ8.0 )
 *   @param [in]  statBlockHeight  height of the statistics block                    (UQ8.0 )
 *   @param [out] pMinimum[]       data pointer for minimum value for each block     (UQ8.0 )
 *   @param [out] pMaximum[]       data pointer for maximum value for each block     (UQ8.0 )
 *   @param [out] pMean[]          data pointer for mean value for each block        (UQ16.0)
 *   @param [out] pVariance[]      data pointer for variance value for each block    (UQ32.0)
 *   @param [in]  pScratch[]       data pointer for scratch buffer                   (UQ8.0 )
 *   @param [in]  mode             optimization mode (0 or 1)                        (UQ8.0 )
 *
 * @par Method
 *  -# Minimum : This value is minimum value of the all the pixels present in given block
 *  -# Maximum : This value is maximum value of the all the pixels present in given block
 *  -# Mean    : This vlaue is equal to sum of all the pixels present in given block, which
 *               is equal to N*actual_mean of the pixels. Where N is total number of pixel
 *               in a block. In order to get actual mean, user must divide outputs by the block
 *               size.
 *  -# Variance: This value is sum of squares of all the pixel present in given block, times the
 *               number of pixels in the block, minus the square of sums of the block.
 *               (blockSize*sumSq - (blockSum)^2)
 *
 * @par Assumptions:
 *    - Input image data is of 8 bits.
 *    - Total number of pixels in each block should not be more than 256.
 *    - Output buffers needs to be allocated by user. If total number of
 *      output block is N then user needs to allocate the 'pMinimum' buffer
 *      of size (N+7). This 7 extra space is coming due to implementation
 *      restriction. Similarly for 'pVariance' user need to allocate
 *      4*(N+7).
 *    - Scratch buffer needs to be allocated by user. Size of the scratch buffer
 *      depends on value of 'mode'. If mode is zero then scratch buffer size
 *      required is 64 bytes. If the mode is one then size of scratch buffer
 *      required is (imageWidth*statBlockHeight + 64)
 *
 * @par Implementation Notes:
 *    - There are two optimization flow has been implemented for this kernel.
 *      These two flow can be selected by passing the value of 'mode' as either
 *      '0' and '1'.
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed and floating point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
uint32_t    VLIB_blockStatistics(
    const uint8_t pInput[restrict],
    uint16_t imageStride,
    uint16_t imageWidth,
    uint16_t imageHeight,
    uint8_t statBlockWidth,
    uint8_t statBlockHeight,
    uint8_t pMinimum[restrict],
    uint8_t pMaximum[restrict],
    uint16_t pMean[restrict],
    uint32_t pVariance[restrict],
    uint8_t pScratch[restrict],
    uint8_t mode
    );

#endif /* VLIB_BLOCK_STATISTICS_H_ */

/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_blockStatistics.h                                   */
/* ======================================================================== */

