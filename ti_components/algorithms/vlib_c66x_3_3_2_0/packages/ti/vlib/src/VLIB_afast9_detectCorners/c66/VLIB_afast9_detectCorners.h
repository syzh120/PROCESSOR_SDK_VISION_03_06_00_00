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

#ifndef VLIB_AFAST9_DETECTCORNERS_H_
#define VLIB_AFAST9_DETECTCORNERS_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_afast9_detectCorners */
/** @ingroup  VLIB_afast9_detectCorners */
/* @{ */

/**
 * @par Description:
 *  Accelerated FAST9.  This function detects and returns corners in image \c img based on FAST9 algorithm, but in a more DSP friendly manner.
 *
 * @par
 *  @param [in]  *image                 Pointer to the image buffer
 *  @param [in]   width                 Image width
 *  @param [in]   height                Image height
 *  @param [in]   pitch                 Image pitch - Number of bytes between the beginning of each line in memory.
 *  @param [in]   differenceThreshold   The FAST difference threshold. A pixel must be this much brighter/darker than the center to be considered "different"
 *  @param [out] *features              Pointer to a buffer to hold output corner bit packed information
 *  @param [in]  *scratchBuffer         Internal scratch buffer of size = 512 bytes needs to be provided. Base should be 8 byte aligned.

 * @par Assumptions:
 * - Output \c feature contains bit packed information( corner / no corner) about each pixel.
 * - E.g first word (32 bit) of output (\c feature) will contain corner information of pixel #4 (lowest bit) to pixel #35 (highest bit), assuming first pixel as pixel #1. Similarly next word will contain corner information of pixel #36 to pixel #67.
 * - Active image width (width - 2*marginPixels) should be multiple of 16. If it is not then active image width is internally rounded to 16.
 * - Buffer size of the \c feature should be equal to ((((width - 2*3) & 0xFFF0U)) >> 4)*(height - 2*3) bytes.
 * - E.g. if the image size is of 140 x 140 then in every row ((140 - 2*3) & 0xFFF0U) >> 0x4 half words will be produced for every row. 3 pixel and 9 pixels are ignored at left and right boundary respectively.
 * - 3 row pixel at top and bottom is also ignored because of unavailability of required pixels for corner detection.
 * - It is advisable to keep the scratch buffer into L1D for better performance result.
 * - Scratch buffer must of double word( 8 byte) aligned.
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_afast9_detectCorners(const uint8_t *restrict image,
                                  uint16_t width,
                                  uint16_t height,
                                  uint32_t pitch,
                                  uint8_t differenceThreshold,
                                  uint16_t *restrict features,
                                  uint8_t *restrict scratchBuffer);


/** @} */
#endif /* VLIB_AFAST9_DETECTCORNERS_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_afast9_detectCorners.h                               */
/* ======================================================================== */

