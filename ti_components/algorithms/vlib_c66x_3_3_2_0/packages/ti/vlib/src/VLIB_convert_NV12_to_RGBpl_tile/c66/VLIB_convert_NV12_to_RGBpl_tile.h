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
**|        Copyright (c) 2007 - 2015 Texas Instruments Incorporated          |**
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

#ifndef VLIB_CONVERT_NV12_TO_RGBPL_TILE_H_
#define VLIB_CONVERT_NV12_TO_RGBPL_TILE_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_tiler.h"

/** @defgroup VLIB_convert_NV12_to_RGBpl_tile */
/** @ingroup  VLIB_convert_NV12_to_RGBpl_tile */
/* @{ */

/**
 * @par Description:
 *   This function transforms the NV12 color format data into the RGB format and separates
 *   the three color channels into separate buffers, color planes.
 * @par
 *   The matrix coefficients specified by the array coeff are typically as shown in
 *   Equation (a) for the case of RGB levels that correspond the 219-level range
 *   of Y. Expected ranges are [16..235] for Y and [16..240] for Cb and Cr.
 *   - coeff[] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 }; (a)
 *
 * @par
 *   @param [in]   *yData      Luma data                                  (UQ8.0)
 *   @param [in]   *cbcrData   Interleaved CbCr data                      (UQ8.0)
 *   @param [in]    coeff      Matrix coefficients                        (SQ15.0)
 *   @param [out]  *rgbData    Base pointer to R, G and B planes (8-bit)  (UQ8.0)
 *
 * @par Assumptions
 *  - All arrays should be 8-byte aligned.
 *  - All widths should be a multiple of 8
 *
 * @par References:
 *  -# <em> Digital Image Processing </em> by R.C.Gonzales and R.E.Woods, Prentice-Hall, 2007
 *
 */

int32_t VLIB_convert_NV12_to_RGBpl_tile(const sBuffer_t *yData,
                                        const sBuffer_t *cbcrData,
                                        const int16_t coeff[5],
                                        const sBuffer_t *rgbData);

/** @} */
#endif /* VLIB_CONVERT_NV12_TO_RGBPL_TILE_H_ */

/* ======================================================================== */
/*  End of file: VLIB_convert_NV12_to_RGBpl_tile.h                             */
/* ======================================================================== */

