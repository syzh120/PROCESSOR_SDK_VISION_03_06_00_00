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

#ifndef VLIB_BLOCKMEDIAN_H_
#define VLIB_BLOCKMEDIAN_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_blockMedian */
/** @ingroup  VLIB_blockMedian */
/* @{ */

/**
 * @par Description:
 *  This function finds the lower median value of each block in an 8-bit image.
 *  The blocks are defined by separate parameters for block width and heights,
 *  and step sizes in the horizontal and vertical directions.  Having step size
 *  parameters means that the neighboring blocks can be more flexibly configured
 *  as follows:
 *      - Overlapping (step size < block size),
 *      - Non-overlapping but adjacent (step size == block size), or
 *      - Sparse (step size > block size)
 *
 * @par
 *    @param [in]  pInput        Input image pointer                        (UQ8.0)
 *    @param [out] pMedian       Output median array pointer                (UQ8.0)
 *    @param [in]  pScratch      Scratch buffer                             (UQ16.0)
 *    @param [in]  imageWidth    Width of the image                         (UQ16.0)
 *    @param [in]  imageHeight   Height of the image                        (UQ16.0)
 *    @param [in]  imagePitch    Pitch of the input image (distance between start of each line) (UQ16.0)
 *    @param [in]  blockWidth    Width of the blocks                        (UQ16.0)
 *    @param [in]  blockHeight   Height of the blocks                       (UQ16.0)
 *    @param [in]  stepSizeHorz  Step Size of the blocks in the X direction (UQ16.0)
 *    @param [in]  stepSizeVert  Step Size of the blocks in the Y direction (UQ16.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be not aliased.
 *    - Output buffer \c pMedian should be of size [(imageHeight - blockHeight)/stepSizeVert + 1]
 *      * [(imageWidth - blockWidth)/stepSizeHorz + 1]
 *    - Scratch buffer \c pScratch should be of size 1024 and allocated in fast memory
 *    - pInput and pScratch buffers should be 8 byte aligned in memory.
 *    - Maximum number of pixels in a single block that can have the same value is 65535.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed-point processors
 *
 * @par Performance Notes:
 *    - Due to horizontal processing pipeline efficiency, the cycles per unit 'N' go down with
 *      respect to increasing blockWidth value
 *        - Where N = ((imageHeight - blockHeight)/stepSizeVert + 1) *
 *          ((imageWidth - blockWidth)/stepSizeHorz + 1) * blockHeight*blockWidth
 *
 */
void    VLIB_blockMedian(const uint8_t pInput[restrict],
                         uint8_t pMedian[restrict],
                         uint16_t pScratch[restrict],
                         uint16_t imageWidth,
                         uint16_t imageHeight,
                         uint16_t imagePitch,
                         uint16_t blockWidth,
                         uint16_t blockHeight,
                         uint16_t stepSizeHorz,
                         uint16_t stepSizeVert);

/** @} */
#endif /* VLIB_BLOCKMEDIAN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_blockMedian.h                                        */
/* ======================================================================== */

