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

#ifndef VLIB_HOUGHLINEFROMLIST_H_
#define VLIB_HOUGHLINEFROMLIST_H_ 1


/** @defgroup VLIB_houghLineFromList*/
/** @ingroup VLIB_houghLineFromList */
/* @{ */

/**
 * @par Description
 *  This function calculates the Hough space values from the list of edge points.
 *
 * @par
 *    @param [in]  *pEdgeMapList      Points to a list of 2xlistSize values of type uint16_t
 *                                      which represent x and y values of edge points         (UQ16.0)
 *    @param [out] *pOutHoughSpace    Points to the Hough space                               (UQ16.0)
 *    @param [in]   outBlkWidth       Width of the original image                             (UQ16.0)
 *    @param [in]   outBlkHeight      Height of original image                                (UQ16.0)
 *    @param [in]   listSize          Size of the edge list                                   (UQ32.0)
 *    @param [in]   thetaRange        Number of samples for theta Range                       (UQ16.0)
 *    @param [in]   rhoMaxLength      Number of samples for rho Range                         (UQ16.0)
 *    @param [in]  *pSIN              Sine lookup tables                                      (SQ15.0)
 *    @param [in]  *pCOS              Cosine lookup tables                                    (SQ15.0)
 *    @param [in]  *ping              Array of rhoMaxLength+4 elements                        (UQ16.0)
 *    @param [in]  *pong              Array of rhoMaxLength+4 elements                        (UQ16.0)
 *    @param [in]  *pang              Array of rhoMaxLength+4 elements                        (UQ16.0)
 *    @param [in]  *peng              Array of rhoMaxLength+4 elements                        (UQ16.0)
 *
 *
 *  @par Assumptions
 *  - The following buffers should be 8 byte aligned in memory: pEdgeMapList, ping, pong, pang, & peng.
 *  - pEdgeMapList points to a list of (2 * \c listSize) values of type uint16_t, which represent x and y
 *    values of edge points: x1,y1,x2,y2, ... While it should be located in the fastest memory available, its
 *    role is cache friendly so it can be stored in the external memory.
 *  - pOutHoughSpace points to the Hough space, which is a (\c thetaRange * \c rhoMaxLength) array of uint16_t.
 *    While it should be located in the fastest memory available, its role is cache friendly so it can be
 *    stored in the external memory.
 *  - outBlkWidth and outBlkHeight represent width and height of the original image
 *  - pSIN and pCOS are lookup tables for sine and cosine and can be generated during initialization.
 *    While it should be located in the fastest memory available, its role is cache friendly so it can
 *    be stored in the external memory.
 *  - ping, pong, pang, and peng are arrays of rhoMaxLength+4 elements of type uint16_t. These arrays
 *    should be stored in the fastest available memory.
 *  - The function is written so that the list of edge points can be broken into sublists and the function
 *    called on them separately. This is useful if the list needs to be in the fast memory, but is too big
 *    to fit there. In that case, the Hough space should be cleared only before the call on the first sublist.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_houghLineFromList(const uint16_t *restrict pEdgeMapList,
                               uint16_t *restrict pOutHoughSpace,
                               uint16_t outBlkWidth,
                               uint16_t outBlkHeight,
                               uint32_t listSize,
                               uint16_t thetaRange,
                               uint16_t rhoMaxLength,
                               const int16_t *pSIN,
                               const int16_t *pCOS,
                               uint16_t *restrict ping,
                               uint16_t *restrict pong,
                               uint16_t *restrict pang,
                               uint16_t *restrict peng);


#endif /* VLIB_HOUGHLINEFROMLIST_H_ */
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_houghLineFromList.h                                  */
/* ======================================================================== */

