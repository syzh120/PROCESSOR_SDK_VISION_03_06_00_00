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

#ifndef VLIB_LEGENDREMOMENTS_H_
#define VLIB_LEGENDREMOMENTS_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_legendreMoments */
/** @ingroup  VLIB_legendreMoments */
/* @{ */

/**
 * @par Description
 *  The function returns a square matrix M of dimension (Order+1) where Order is the specified maximum order of moments required.
 *  Entries M(i,j) such that i+j < Order correspond to the required Legendre moments.
 *
 * @par
 * @param [in]      Im[]       Input image patch                                            (SQ0.15)
 * @param [in,out]  LMoments[] Buffer to hold the computed Legendre moments                 (SQ0.15)
 * @param [in]      LPoly[]    Buffer returned from call to \ref VLIB_legendreMoments_Init  (SQ0.15)
 * @param [in]      Order      Required order of moments                                    (SQ31.0)
 * @param [in]      ImH        Image height                                                 (SQ31.0)
 * @param [in]      Factor1    Constant value returned by \ref VLIB_legendreMoments_Init    (SQ0.15)
 *
 * @par Assumptions
 *   -   The pixel intensities should be normalized to be in [0,1].
 *   -   The image should be square, image height = image width.
 *   -   The ImH parameter should be a multiple of 4.
 *   -   The largest image supported is 256x256.
 *   -   The largest order of moments supported is 40.
 *   -   LMoments should be initialized to 0
 *   -   LPoly is independent of the pixel intensities, and is dependent only on the size of the image (ImH) and the
 *       Order of the moment values required
 *   -   LPoly must be of dimension (Order+1)x(ImH)
 *   -   LMoments must be of dimension (Order+1)x(Order+1)
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_legendreMoments(const int16_t Im[restrict],
                             int16_t LMoments[restrict],
                             const int16_t LPoly[restrict],
                             const int32_t Order,
                             const int32_t ImH,
                             const int16_t Factor1);

/** @} */
#endif /* VLIB_LEGENDREMOMENTS_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_legendreMoments .h                                   */
/* ======================================================================== */

