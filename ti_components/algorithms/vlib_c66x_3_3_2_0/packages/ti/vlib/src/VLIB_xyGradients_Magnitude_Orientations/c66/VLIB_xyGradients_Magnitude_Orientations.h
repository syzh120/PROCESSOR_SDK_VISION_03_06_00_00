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
**+--------------------------------------------------------------------------+*/

#ifndef VLIB_XYGRADIENTS_MAGNITUDE_ORIENTATIONS_H_
#define VLIB_XYGRADIENTS_MAGNITUDE_ORIENTATIONS_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_xyGradients_Magnitude_Orientations */
/** @ingroup  VLIB_xyGradients_Magnitude_Orientations */
/* @{ */

/**
 * @par Description:
 *  This function returns the magnitude of gradients and binned orientation
 *  of the gradients of an 8-bit input image. The number of orientations are
 *  programmable using the \c bins parameter. Gradient orientation values
 *  range from 0-180 and hence the maximum number of bins can be 180.
 *
 * @par Method:
 *  The image gradients are calculated with pixel subtraction and not by Sobel filter. The magnitude
 *  values returned are the sum of the absolute values of the x and y difference gradients.
 *  tan inverse of dy/dx gives the orientation direction. These orientations are mapped to
 *  one of the 0-(bins-1) bins. A pre computed look up table is built based on the number of bins.
 *  The computation cycle of this table depends on boundaries of the tan inverse values. The size
 *  of look-up table is 112kB. This gives the best through put of 1 cycle per pixel voting.
 *
 * @par
 *    @param [in]  img[]    Input image array (UQ8.0)
 *    @param [in]  Width    Input image width (UQ16.0)
 *    @param [in]  Height   Inpuy image height (UQ16.0)
 *    @param [in]  bins     Number of bins (UQ8.0)
 *    @param [out] Mag[]    Array for Magnitude (UQ32.0)
 *    @param [out] Orien[]  Array for Orientation (UQ32.0)
 *
 * @par Assumptions:
 *    - The function processes only valid non-border pixels of the input correctly and this results
 *      in the outputs being cropped to have only (\c Width - 2) x (\c Height - 2) pixels total.
 *    - The first output pixel is obtained by processing the first valid non-border
 *      input pixel, causing a shift in the output gradient images with respect to the input image.
 *      The shift is one pixel to the left and one pixel to the top.
 *    - The output is cropped and does not contain border pixels. The output is written into the first
 *      (\c Width - 2) x (\c Height - 2) contiguous pixels.
 */
void    VLIB_xyGradients_Magnitude_Orientations(const uint8_t img[restrict],
                                                uint16_t Width,
                                                uint16_t Height,
                                                uint8_t bins,
                                                uint32_t Mag[restrict],
                                                uint32_t Orien[restrict]);
/** @} */
#endif

/* ======================================================================== */
/*  End of file:  VLIB_xyGradients_Magnitude_Orientations.h                 */
/* ======================================================================== */

