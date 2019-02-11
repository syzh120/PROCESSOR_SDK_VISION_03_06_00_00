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

#ifndef VLIB_NONMAXSUPRESS_U16_H_
#define VLIB_NONMAXSUPRESS_U16_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_nonMaxSuppress_U16 */
/** @ingroup  VLIB_nonMaxSuppress_U16 */
/* @{ */

/**
 * @par Description
 *  This function implements a non-maximum suppression algorithm with programmable filter size.  It compares
 *  the value of each input pixel against its neighbors.  For an output pixel to be "on" (coordinate pair
 *  included in the \c pixIndex list), the input pixel value must be both:
 *  - Greater than or equal to its neighbors
 *  - Greater than the \c threshold value
 *
 *  If the above conditions are not met simultanously, the output coordinate will not be included in the \c pixIndex list.
 *
 * @par
 *  @param [in]   im[]            Input image                                 (UQ16.0)
 *  @param [in]   w               Image width                                 (SQ31.0)
 *  @param [in]   h               Image height                                (SQ31.0)
 *  @param [in]   filterWidth     Filter width                                (SQ31.0)
 *  @param [in]   threshold       Threshold for the Maxima                    (UQ32.0)
 *  @param [in]   buffer[]        Buffer for internal use                     (UQ16.0)
 *  @param [out]  pixIndex[]      List of coordinates of non-maxima locations (SQ15.0)
 *
 * @par Assumptions
 *  - The only acceptable values for \c filterWidth are 3, 5, and 7, representing filter masks sizes 3x3, 5x5, and 7x7, respectively.
 *  - The internal buffer (\c buffer) size should be at least ((2 * \c filterWidth) + (\c w * \c h))*sizeof(uint16_t) bytes
 *  - The output buffer (\c pixIndex) size should be (2*w*h+2)*sizeof(uint16_t) bytes
 *  - The format of the output buffer (\c pixIndex) is as follows:
 *      - \c pixIndex[] = {numPoints, 0, y1, x1, y2, x2, y3, x3,  yn, xn}
 *          - where \e n = numPoints = the number of points contained in the list.
 *  - Due the the method of filtering, the output list will not include pixel coordinates which are located within the border of the
 *    input image.  The number of border pixels is defined by the following equation: border pixels = (filterWidth-1)/2.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 */
int32_t    VLIB_nonMaxSuppress_U16(const uint16_t im[restrict],
                                   int32_t w,
                                   int32_t h,
                                   int32_t filterWidth,
                                   uint32_t threshold,
                                   uint16_t buffer[restrict],
                                   int16_t pixIndex[restrict]);

/** @} */
#endif /* VLIB_NONMAXSUPRESS_U16_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_nonMaxSuppress_U16.h                                 */
/* ======================================================================== */

