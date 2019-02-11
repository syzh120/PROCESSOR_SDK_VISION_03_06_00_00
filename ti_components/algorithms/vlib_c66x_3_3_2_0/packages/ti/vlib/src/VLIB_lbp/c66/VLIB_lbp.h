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
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/


#ifndef VLIB_LBP_H_
#define VLIB_LBP_H_

/** @defgroup VLIB_LBP */
/** @ingroup  VLIB_LBP */
/* @{ */

/**
 * @par Description:
 *  Local binary patterns (LBP) is a type of feature used for classification in
 *  computer vision. This function extract LBP features of a 8bit gray image
 *
 * @par
 *    @param [in]  pInput        Input image pointer                        (UQ8.0)
 *    @param [in]  pMapTbl       Pointer to the mapping table               (UQ8.0)
 *    @param [in]  pScratch      Scratch buffer                             (UQ8.0)
 *    @param [out] pOutHistogram Output LBP histagram                       (UQ32.0)
 *    @param [in]  imageWidth    Width of the image                         (UQ32.0)
 *    @param [in]  imageHeight   Height of the image                        (UQ32.0)
 *    @param [in]  numNeighbors  Number of surrounding pixels               (UQ32.0)
 *    @param [in]  radius        Radius from center to the surrounding pixels in number of pixels. (UQ32.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be not aliased.
 *    - pMapTbl can be uniformed mapping table, or any other user specified mapping table
 *    - The size of the pMapTbl buffer is expected to be equal to 2^numNeighbors entries (2^8=256 entries).
 *    - Output buffer \c pOutHistogram is of size num of bins of the histogram and should be initialized to zero.  Effectively, the
 *      minimum required size of this buffer is equal to the max value in the pMapTbl+1.
 *    - Scratch buffer \c pScratch should be of size imageWidth*imageHeight*6 in bytes and allocated in fast memory
 *    - pScratch buffer pointer should be 8 byte aligned in memory.
 *    - Only numNeighbors = 8 is supported at this time
 *    - Only radius = 1 is supported at this time
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code only compatible with C66 processors
 *
 * @par Performance Notes:
 *    - None
 */
void    VLIB_lbp(const uint8_t pInput[restrict],
                 uint8_t pMapTbl[restrict],
                 uint8_t pScratch[restrict],
                 uint32_t pOutHistogram[restrict],
                 uint32_t imageWidth,
                 uint32_t imageHeight,
                 uint32_t numNeighbors,
                 uint32_t radius);

/** @} */
#endif

/* ======================================================================== */
/*  End of file:  VLIB_lbp.h                                                */
/* ======================================================================== */

