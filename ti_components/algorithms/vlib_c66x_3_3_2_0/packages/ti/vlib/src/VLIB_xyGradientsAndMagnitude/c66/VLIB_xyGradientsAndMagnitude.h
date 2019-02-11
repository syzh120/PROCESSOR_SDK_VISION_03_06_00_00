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

#ifndef VLIB_XYGRADIENTSANDMAGNITUDE_H_
#define VLIB_XYGRADIENTSANDMAGNITUDE_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_xyGradientsAndMagnitude */
/** @ingroup  VLIB_xyGradientsAndMagnitude */
/* @{ */

/**
 * @par Description:
 *  For each pixel in the image, the 2nd step in Canny edge detection extracts the horizontal and vertical 1st
 *  order gradients along with an approximation of the gradient magnitude. Gradients are 2D vectors which
 *  point in the direction of the greatest rate of change, in this case, in intensity.
 *  This function extracts the 2D gradient vector coordinates as well as magnitude.
 *
 * @par Method:
 *  The first order 3x3 gradient filter calculates the first derivative in both the horizontal and vertical directions,
 *  Gx and Gy, respectively. So for the image pixel I(x,y), we calculate the gradients and approximate the magnitude
 *  as shown in the following equations:
 *
 * @verbatim

    Gx = I(x+1,y) - I(x-1,y)
    Gy = I(x,y+1) - I(x,y-1)
    Gmag = (|Gx| + |Gy|)

    Gx, Gy and Gmag are all signed, 16-bit values.
   @endverbatim
 *
 *
 * @par
 *   @param [in]  *pIn       Pointer to array containing input image (UQ8.0)
 *   @param [out] *pGradX    Pointer to array containing X gradient (SQ15.0)
 *   @param [out] *pGradY    Pointer to array containing Y gradient (SQ15.0)
 *   @param [out] *pMag      Pointer to array containing magnitude (SQ15.0)
 *   @param [in]   width     Input width (UQ16.0)
 *   @param [in]   height    Input height (UQ16.0)
 *
 * @par Assumptions:
 *    - When this is used in the \ref VLIB_Canny_Edge_Detection function, the \ref VLIB_conv_7x7_i8_c8s function performs
 *      a 7x7 Gaussian filtering, which creates a 3-pixel border around the image that contains invalid data. In the
 *      interest of performance, the gradient filter processes these border pixels, but later stages will discount
 *      them appropriately.
 *    - The function processes only valid non-border pixels of the input correctly and this results
 *      in the output gradient and magnitude images being cropped to have only (\c width - 2) x (\c height - 2) valid
 *      pixels. This can be avoided by padding input and output borders with meaningful data.
 *    - The first output pixel is obtained by processing the first valid non-border
 *      input pixel, causing a shift in the output gradient and magnitude images with respect to the input image.
 *      The shift is one pixel to the left and one pixel to the top. The shift can be avoided
 *      by passing the pointer to the second pixel of the second row of the output images as the
 *      arguments \c pGradX, \c pGradY and \c pMag to the function.
 *    - Since the output is cropped, its border pixels do not contain valid data. If the shift is
 *      avoided as explained above, the output border pixels are invalid.
 *      If the shift is not avoided, two rightmost columns and two bottommost rows of the output
 *      gradient and magnitude images do not contain valid data. See @ref filter_shift for more information.
 *    - The gradient filter has no memory boundary alignment requirements.
 */
int32_t VLIB_xyGradientsAndMagnitude(const uint8_t *restrict pIn,
                                     int16_t *restrict pGradX,
                                     int16_t *restrict pGradY,
                                     int16_t *restrict pMag,
                                     uint16_t width,
                                     uint16_t height);

#endif
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_xyGradientsAndMagnitude.h                            */
/* ======================================================================== */

