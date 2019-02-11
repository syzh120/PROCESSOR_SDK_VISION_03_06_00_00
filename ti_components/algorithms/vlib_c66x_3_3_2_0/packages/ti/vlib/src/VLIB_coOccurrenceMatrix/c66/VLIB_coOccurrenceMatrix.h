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

#ifndef VLIB_CO_OCCURRENCE_H_

#define VLIB_CO_OCCURRENCE_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_coOccurrenceMatrix */
/** @ingroup  VLIB_coOccurrenceMatrix */
/* @{ */
/**
 * @par Description:
 *   This routine accepts an 8-bit grayscale input image of size imageWidth by
 *   imageHeight with a stride of imagePitch and calculates gray scale
 *   co-occurrence for multiple angles. Angles are taken in terms of
 *   offsets in row and columns. E.g. rowOffset = -D and colOffset = D
 *   indicates pixel at 45 degree down from current pixel. In single call of this
 *   API output matrix can be calculated for multiple offsets ( or angles).
 *
 * @par
 *   @param [in]  pInput[]         input data pointer                                (UQ8.0 )
 *   @param [in]  pCoMatrix[]      Array of pointers for output matrices             (UQ16.0*)
 *   @param [in]  imageWidth       width of input data, in elements                  (UQ16.0)
 *   @param [in]  imageHeight      height of input data, in elements                 (UQ16.0)
 *   @param [in]  imagePitch       stride between input lines, in elements           (UQ16.0)
 *   @param [in]  loPixelVal       Input values less than or equal to lowPixelVal    (UQ8.0 )
 *                                 are scaled to 0.
 *   @param [in]  hiPixelVal       Input values more than or equal to hiPixelVal     (UQ8.0 )
 *                                 are scaled to (numLevels -1).
 *   @param [in]  numLevels        The range [lowPixelVal hiPixelVal] is divided     (UQ16.0 )
 *                                 into  numLevels equal width bins and values in a
 *                                 bin get mapped to a single gray level.
 *   @param [in]  numOffsets       Number of  directions for which out matrix is     (UQ8.0 )
 *                                 needed.
 *   @param [in]  rowOffsets       Pointer for the offsets in Y direction for pixel  (SQ8.0 )
 *                                 in interest and neighbour pixel.
 *   @param [in]  colOffsets       Pointer for the offsets in X direction for pixel  (SQ8.0 )
 *                                 in interest and neighbour pixel.
 *   @param [in]  scratch          Pointer to scratch area. This is not mandatory    (UQ8.0* )
 *                                 input.Application can provide this value as NULL,
 *                                 if scratch memory can not be provided. Cycle
 *                                 consumed will be lesser when scratch buffer is
 *                                 provided. Scratch buffer size need to be
 *                                 8*numLevels*numLevels, when it is provided. API
 *                                 checks the value of this argument against NULL, and
 *                                 accordingly appropriate flow chosen.
 *
 * @par Assumptions:
 *    - Input image data is of 8 bits.
 *    - Output data is saturated to 16 bits
 *    - I/O buffers are assumed to be not aliased.
 *    - Scratch buffer \c scratch should be 8-byte aligned in memory.
 *    - Active width (imageWidth - abs(colOffset)) should be at least 16 pixels
 *    - output buffer and scratch buffers are internally cleared to zero
 *    - loPixelVal value should be less than hiPixelVal
 *    - numLevels should be within the range [2 .. 256]
 *    - numLevels should be less than or equal hiPixelVal - loPixelVal + 1
 *
 * @par Implementation Notes:
 *    - There are two optimization flows have been implemented for this kernel.
 *      These two flow can be selected by:
 *          1: passing a valid scratch buffer or
 *          2: passing a NULL (0) pointer as the scratch buffer pointer
 *      Optimization flow with scratch buffer will have faster performance.
 *      Also if (hiPixelValue-loPixelValue+1)/numLevels is a positive power of two AND numLevels<=64
 *      then LUT usage while binning the pixels can be avoided which will give further
 *      performance improvement when the scratch buffer is passed.
 *    - For lower image size, non scratch flow will give better cycle performance number.
 *    - For larger image size , scratch buffer flow will give better cycle performance number.
 *    - In scratch buffer flow, 4 temporary histograms are used which needs to be reset to zero internally.
 *
 */
uint32_t VLIB_coOccurrenceMatrix(const uint8_t pInput[restrict],
                                 uint16_t *restrict pCoMatrix[],
                                 const uint16_t imageWidth,
                                 const uint16_t imageHeight,
                                 const uint16_t imagePitch,
                                 const uint8_t loPixelVal,
                                 const uint8_t hiPixelVal,
                                 const uint16_t numLevels,
                                 const uint8_t numOffsets,
                                 const int8_t rowOffsets[restrict],
                                 const int8_t colOffsets[restrict],
                                 uint8_t *scratch);
#endif /* VLIB_CO_OCCURRENCE_H_ */

/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_coOccurrenceMatrix.h                                 */
/* ======================================================================== */

