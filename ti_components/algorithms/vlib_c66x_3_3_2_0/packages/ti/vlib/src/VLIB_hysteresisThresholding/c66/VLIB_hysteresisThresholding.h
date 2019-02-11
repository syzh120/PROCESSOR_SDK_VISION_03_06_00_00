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

#ifndef VLIB_HYSTERESISTHRESHOLDING_H_
#define VLIB_HYSTERESISTHRESHOLDING_H_ 1

/** @defgroup VLIB_hysteresisThresholding */
/** @ingroup VLIB_hysteresisThresholding */
/* @{ */

/**
 * @par Description
 * With an edge map containing possible edges, hysteresis thresholding identifies and follows edges.
 * Using both High and Low thresholds,it is able to maintain edge continuity by linking stronger edge
 * segments that are connected to weaker segments.
 *
 * @par
 *   @param [in]     *pInMagBlk         Pointer to array containing magnitude   (SQ15.0)
 *   @param [in,out] *edgeMap           Pointer to array Edge map               (UQ8.0)
 *   @param [in]     *scratch           Pointer to array strong edge list       (UQ8.0)
 *   @param [in]      blkHeight         Input height                            (UQ16.0)
 *   @param [in]      blkWidth          Input width                             (UQ16.0)
 *   @param [in]      blkPitch          Input pitch                             (UQ16.0)
 *   @param [in]      loThresh          Lower threshold                         (UQ8.0)
 *   @param [in]      hiThreshold       Upper thershold                         (UQ8.0)
 *
 * @par Assumptions
 *    - \c scratch size should be blkWidth*blkHeight*4
 *    - This function uses assumes that  the \c pInMagBlk and \c edgeMap buffers have the same pitch.
 *    - This function uses a 3x3 kernel and references the surrounding 8 pixels in the \c pInMagBlk for each
 *      pixel. Therefore, in order to make sure it accesses valid data, the minimum offset into the valid region
 *      of the magnitude buffer that \c pInMagBlk points to should be the second pixel of the
 *      second row. Likewise, the \c blkWidth should be at least 2 pixels less than the \c blkPitch, and the \c blkHeight
 *      should be at least 2 rows less than the valid data height of the magnitude buffer.
 *    - The width should be >= 8
 *
 */
int32_t VLIB_hysteresisThresholding(const int16_t *restrict pInMagBlk,
                                    uint8_t *edgeMap,
                                    uint8_t *restrict scratch,
                                    uint16_t blkHeight,
                                    uint16_t blkWidth,
                                    uint16_t blkPitch,
                                    uint8_t loThresh,
                                    uint8_t hiThreshold);

/** @} */
#endif /* VLIB_HYSTERESISTHRESHOLDING_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_hysteresisThresholding.h                             */
/* ======================================================================== */

