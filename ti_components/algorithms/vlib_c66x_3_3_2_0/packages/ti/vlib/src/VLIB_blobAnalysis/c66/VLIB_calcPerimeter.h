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

#ifndef VLIB_CALCPERIMETER_H
#define VLIB_CALCPERIMETER_H 1

#include "../../common/VLIB_types.h"
#include "../../VLIB_Connected_Components_Labeling/AVMClasses.h"

/** @defgroup VLIB_calcBlobPerimeter */
/** @ingroup  VLIB_calcBlobPerimeter */
/* @{ */

/**
 * @par Description:
 *  This function calculates the perimeter of a blob. A pixel is considered to be on the border
 *  of the blob if at least one of its 4 closest neighbors (top, bottom, left, right) is not in
 *  the blob. In other words, if all 4 of these neighbors are in the blob, then it is NOT a border
 *  pixel. The perimeter is the sum of the border pixels.  If the blob has hole inside, then the perimeter
 *  of the hole is also counted.
 *
 * @par
 *    @param [in]  ccmapColor   The ccmap color of the blob. The ccmap is one of the outputs of connected component labeling. (Q32.0)
 *    @param [in]  width        The width of the ccmap, used to calculate some internal offset  (Q32.0)
 *    @param [in]  blob_ii      The pointer to interval image of the blob                       (AVMii)
 *    @param [in]  pBlobMap     The pointer to ccmap of uint8_t type of data                    (Q8.0)
 *    @param [out] perimeter    The output address of the perimeter. The output is single word. (Q32.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be not aliased.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66 floating-point processors
 *
 * @par Performance Notes:
 *      NA
 */
int32_t VLIB_calcBlobPerimeter(int32_t ccmapColor,
                               int32_t width,
                               const AVMii       *blob_ii,
                               uint8_t           *pBlobMap,
                               uint32_t          *perimeter);
/** @} */

#endif /* VLIB_CALCPERIMETER_H */

/* ======================================================================== */
/*  End of file:  VLIB_calcPerimeter.h                                      */
/* ======================================================================== */

