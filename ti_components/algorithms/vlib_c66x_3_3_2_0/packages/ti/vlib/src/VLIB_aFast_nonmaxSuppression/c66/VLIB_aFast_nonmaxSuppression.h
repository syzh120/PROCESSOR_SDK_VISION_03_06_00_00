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

#ifndef VLIB_AFAST_NONMAXSUPPRESSION_H_
#define VLIB_AFAST_NONMAXSUPPRESSION_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_aFast_nonmaxSuppression */
/** @ingroup  VLIB_aFast_nonmaxSuppression */
/* @{ */

/**
 * @par Description:
 *  This function performs sparse non-maximum suppression. It finds those features that are local maxima based on
 *  the fast score, and places them at the beginning of the list.
 *
 * @par
 *  @param [in]     *score              The input score list of feature points on which NMS has to be applied.
 *  @param [in,out] *posyxPkd           Location of feature points in packed 32 bit format where lower 16 bit is
 *                                      x co-ordinate and higher 16 bit is y co-ordinate. There should be one to one
 *                                      correspondence between \c score and \c posyxPkd. Also all feature points are in
 *                                      raster scan order.
 *  @param [out]    *scoreOut           Output scores of feature points after non maxima supression.
 *  @param [out]    *posyxPkdOut        Output location for non maxima supressed feature points. Format of this
 *                                      is same as \c posyxPkd. There will one to one correspondence between
 *                                      \c scoreOut and \c posyxPkdOut.
 *  @param  [in]    inNumScores         Total number of input feature points.
 *  @param  [in]    imgWidth            Input image width in pixels.
 *  @param  [in]    imgHeight           Input image height in pixels.
 *  @param  [in]    scratch             Input scratch memory area needed by this kernel. Size of this should be
 *                                      \c inNumScores * 2 + \ imgWidth *4 + 16
 *  @return                             This kernel returns total number of valid scores. Kernel returns '0' if
                                        any invalid parameter is passed to the kernel.
 * @par Assumptions:
 * - \c scratch should be double word aligned.
 * - \c posyxPkd and \c posyxPkdOut should be word aligned.
 * - \c inNumScores should be multiple of 4.
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
uint16_t    VLIB_aFast_nonmaxSuppression(const uint8_t score[restrict],
                                         uint32_t posyxPkd[restrict],
                                         uint8_t scoreOut[restrict],
                                         uint32_t posyxPkdOut[restrict],
                                         uint16_t inNumScores,
                                         uint16_t imgWidth,
                                         uint16_t imgHeight,
                                         uint8_t scratch[restrict]);


/** @} */
#endif /* VLIB_AFAST_NONMAXSUPPRESSION_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_aFast_nonmaxSuppression.h                            */
/* ======================================================================== */

