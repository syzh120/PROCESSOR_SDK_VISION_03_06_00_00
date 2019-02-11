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

#ifndef VLIB_CONVERTUYVYINT_TO_HSLPL_H_
#define VLIB_CONVERTUYVYINT_TO_HSLPL_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_convertUYVYint_to_HSLpl */
/** @ingroup  VLIB_convertUYVYint_to_HSLpl */
/* @{ */

/**
 * @par Introduction and Use Cases:
 *   HSL (Hue Saturation Lightness), also known as HSI (Hue Saturation Intensity), or HSB (Hue Saturation
 *   Brightness) is a popular color space for image representation, especially in computer graphics and other
 *   applications where color perception needs to be modeled better than with RGB. If the input data is in
 *   the interleaved YUV422 color format, this function transforms the data into the HSL format and separates
 *   the three color channels into separate buffers, color planes.
 *
 * @par Description:
 *   This function calculates HSL (Hue,Saturation and Lightness) representation of pixels
 *   represented in interleaved YUV422 format.
 * @par
 *   The matrix coefficients specified by the array coeff are typically as shown
 *   in Equation (a) for the case of RGB levels that correspond the 219-level range
 *   of Y. Expected ranges are [16..235] for Y and [16..240] for Cb and Cr.
 *   - coeff[] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 } ;  (a)
 * @par
 *   Alternatively, as shown in Equation (b), for the case of RGB conversion with
 *   the 219-level range of Y expanded to fill the full RGB dynamic range.
 *   Expected ranges are [16..235] for Y and [16..240] for Cb and Cr.
 *   - coeff[] = { 0x2543, 0x3313, -0x0C8A, -0x1A04, 0x408D } ; (b)
 * @par
 *   The division table is used to provide an LUT to replace integer divisions
 *   by multiplications with corresponding inverses, shifted left by 15.
 *
 * @par
 *   @param [in]  *yc         Interleaved luma/chroma                      (UQ8.0)
 *   @param [in]   width      Width of input image (number of luma pixels) (in pixels)
 *   @param [in]   pitch      Pitch of input image (number of luma pixels) (in pixels)
 *   @param [in]   height     Height of input image(number of luma pixels) (in pixels)
 *   @param [in]   coeff      Matrix coefficients                          (SQ15.0)
 *   @param [in]   div_table  Division table                               (UQ16.0)
 *   @param [out] *H          Pointer to H plane (16-bit)                  (UQ16.0)
 *   @param [out] *S          Pointer to S plane (8-bit)                   (UQ8.0)
 *   @param [out] *L          Pointer to L plane (8-bit)                   (UQ8.0)
 *
 * @par Assumptions
 *  - All arrays should be 64-bit aligned.
 *  - width should be a multiple of 8, and greater than 0
 *  - pitch should be a multiple of 4, and >= width
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 * @par References:
 *  -# <em> Digital Image Processing </em> by R.C.Gonzales and R.E.Woods, Prentice-Hall, 2007
 *
 */
int32_t VLIB_convertUYVYint_to_HSLpl(const uint8_t *yc,
                                     uint32_t width,
                                     int32_t pitch,
                                     uint32_t height,
                                     const int16_t coeff[5],
                                     const uint16_t div_table[510],
                                     uint16_t *restrict H,
                                     uint8_t *restrict S,
                                     uint8_t *restrict L);

/** @} */
#endif /* VLIB_CONVERTUYVYINT_TO_HSLPL_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_HSLpl.h                            */
/* ======================================================================== */

