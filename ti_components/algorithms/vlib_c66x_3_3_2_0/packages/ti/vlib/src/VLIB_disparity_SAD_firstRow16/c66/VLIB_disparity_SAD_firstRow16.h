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

#ifndef VLIB_DISPARITY_SAD_FIRSTROW16_H_
#define VLIB_DISPARITY_SAD_FIRSTROW16_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_disparity_SAD_firstRow16*/
/** @ingroup  VLIB_disparity_SAD_firstRow16 */
/* @{ */

/**
 * @par Description
 *  This function calculates the disparity at each position in the first row of an 16-bit stereo image pair. Subsequent
 *  rows should use the \ref VLIB_disparity_SAD16 function.
 *
 * @par
 *  @param [in]     *pLeft          Pointer to left image                      (UQ15.0)
 *  @param [in]     *pRight         Pointer to right image                     (UQ15.0)
 *  @param [in,out] *pCost          Cost corresponding to current displacement (UQ32.0)
 *  @param [in,out] *pMinCost       Minimum cost across all displacements      (UQ32.0)
 *  @param [in,out] *pScratch       Scratch Memory                             (UQ32.0)
 *  @param [in,out] *pDisparity     Displacement having the minimum cost       (SQ8.0)
 *  @param [in]      displacement   Current displacement                       (in pixels)
 *  @param [in]      width          Output width of disparity row              (in pixels)
 *  @param [in]      pitch          Pitch of the input images                  (in pixels)
 *  @param [in]      windowSize     Size of the block used for computing SAD   (in pixels)
 *                                   (eg. a value of 5 represents a 5x5 window block size)
 *
 * @par Assumptions
 * - This function should only be called to compute the first row disparities (adjusted by windowSize) of an image.
 *   Subsequent rows should be computed by calling the \ref VLIB_disparity_SAD16 function in order from top to bottom of the image.
 * - This function should be called multiple times for the first row of the image: once for each displacement to search.
 *   Each time, the \e pRight pointer and \e displacement variable should be modified to search for disparities
 *   at each displacement required. Each invocation of the function updatest the pCost, pMinCost, and pDisparity buffers.
 * - Before calling this function the first time, the following buffers should be set accordingly:
 *     - pMinCost should be filled with 0x7FFFFFFF's (max value of a signed 32 bit variable).
 *     - pDisparity should be filled with 0's.
 * - The pCost buffer should never be altered in between subsequent calls to this function throughout the entire
 *   frame.  It is used to store inter-row state information.
 * - windowSize should be an odd value.
 * - pitch should be >= (width + (number of disparities to search - 1) + (windowSize - 1)).  This is required in order
 *   to ensure that disparities are not calculated based on wrap-around from other lines in the input images.
 * - The following list minimum buffer requirements:
 *       pMinCost   = width elements rounded up to the nearest multiple of 4 plus 1
 *       pCost      = width elements rounded up to the nearest multiple of 4 plus 1, times the number of disparities to
 *                    search.
 *       pDisparity = width elements rounded up to the nearest multiple of 4 plus 1, times the number of lines to output
 *       pScratch   = width elements + windowSize rounded up to the nearest multiple of 4
 * - The pointer values for pLeft and pRight should account for the windowSize.  For example, if windowSize=5, then
 *   the pointer values should be adjusted at least windowSize/2 (5/2=2) pixels from the left border, and windowSize/2
 *   (5/2=2) lines from the top or bottom of the image ... otherwise, the algorithm would access out of bound memory.
 * - Due to an optimization using the _sub2() instruction, which works on signed 16 bit inputs, the most significant bit of
 *   the input (bit 15) should be 0.  This means the effective dynamic range of the input data is 15 bits, not 16. If a full
 *   16 bits is required, please contact TI to make us aware of the priority this use case.
 * - The pScratch buffer should be 8-byte aligned.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_disparity_SAD_firstRow16(const uint16_t *restrict pLeft,
                                      const uint16_t *restrict pRight,
                                      uint32_t *restrict pCost,
                                      uint32_t *restrict pMinCost,
                                      uint32_t *restrict pScratch,
                                      int8_t *restrict pDisparity,
                                      int32_t displacement,
                                      int32_t width,
                                      int32_t pitch,
                                      int32_t windowSize);

/** @} */
#endif /* VLIB_DISPARITY_SAD_FIRSTROW16_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_disparity_SAD_firstRow16.h                           */
/* ======================================================================== */

