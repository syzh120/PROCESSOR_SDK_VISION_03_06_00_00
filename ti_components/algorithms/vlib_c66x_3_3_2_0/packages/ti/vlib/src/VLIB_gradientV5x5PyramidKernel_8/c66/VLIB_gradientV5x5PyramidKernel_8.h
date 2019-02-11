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

#ifndef VLIB_GRADIENTV5X5PYRAMID_8_H_
#define VLIB_GRADIENTV5X5PYRAMID_8_H_

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_gradientV5x5PyramidKernel_8 */
/** @ingroup  VLIB_gradientV5x5PyramidKernel_8 */
/* @{ */

/**
 * @par Description
 *  This function can be used to calculate the horizontal portion of the next level of a pyramid. Given a pointer to a
 *  rectangular region of interest described by W (input data width), P (input data pitch),
 *  and H (input data height), this kernel returns (W-4)/2 x (H-3)/2 values. For example,
 *  if H=5, it will calculate a single row of results. The filter used is:
 *  @verbatim

            -1  -4  -6  -4  -1
            -2  -8  -12 -8  -2
    V5  =    0   0   0   0   0
             2   8   12  8   2
             1   4   6   4   1

    @endverbatim
 *  After the filtering step, the intermediate results are rounded and scaled to values
 *  0-255 (the output value of 128 indicates no gradient) as shown in the following equation:
 *  @verbatim

        Gv = ((conv2(A,V5) + 64) >> 7) + 128;
    @endverbatim
 *
 * @par
 *  @param [in]  *pIn     Input image                                     (UQ8.0)
 *  @param [in]  *pB      5 x (width-4) temporary array                   (UQ16.0)
 *  @param [in]   width   Input width                                     (UQ16.0)
 *  @param [in]   pitch   Pitch of the input data                         (UQ16.0)
 *  @param [in]   height  Input height                                    (UQ16.0)
 *  @param [out] *pOut    Output image                                    (UQ8.0)
 *
 * @par Assumptions
 * - (width-4) must be a multiple of 8
 * - pitch should be greater than or equal to width
 * - height must be greater than 4
 * - pIn is a pointer to an (pitch x height) array of unsigned 8 bit data
 * - pOut is a pointer to an (width-4)/2 x (height-3)/2 array of unsigned 8 bit data
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
*/

int32_t VLIB_gradientV5x5PyramidKernel_8(const uint8_t *restrict pIn,
                                         int16_t *restrict pB,
                                         uint16_t width,
                                         uint16_t pitch,
                                         uint16_t height,
                                         uint8_t *restrict pOut);

/** @} */
#endif /* VLIB_GRADIENTV5X5PYRAMID_8_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_gradientV5x5PyramidKernel_8.h                        */
/* ======================================================================== */

