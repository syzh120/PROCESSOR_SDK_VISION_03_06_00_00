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
**|        Copyright (c) 2016 - 2017 Texas Instruments Incorporated          |**
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

#ifndef VXLIB_HISTOGRAMCDFLUT_I32U_O8U_H_
#define VXLIB_HISTOGRAMCDFLUT_I32U_O8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_histogramCdfLut_i32u_o8u */
/** @ingroup  VXLIB_histogramCdfLut_i32u_o8u */
/* @{ */
/**
 * @par Description:
 *  Used as part of histogram equalization, it takes, as input, the histogram of an image,
 *  generates the CDF (cumulative distribution function) of the histogram, and then generates
 *  a lookup table that can be used against the input image to generate an output image with
 *  an equalized histogram.
 *
 *  The VXLIB_equalizeHist_i8u_o8u function can do all of this in one shot, however, if the image
 *  processing is to be broken up into blocks (for DMA for example), then the user needs access to
 *  this function separate from the image access functions.  The order of operation would be to use:
 *  -# VXLIB_histogramSimple_i8u_o32u (for every block in the image)
 *  -# VXLIB_histogramCdfLut_i32u_o8u (once on the final output histogram of VXLIB_histogramSimple_i8u_o32u)
 *  -# VXLIB_tableLookup_i8u_o8u (for every block in the image)
 *
 * @par
 *   @param [in]     src[]       Pointer to histogram of an image containing 256 bins (UQ32.0)
 *   @param [out]    cdf[]       Pointer to cumulative distribution output containing 256 bins (optional) (UQ32.0)
 *   @param [out]    dst[]       Pointer to lookup table output containing 256 entries (optional) (UQ8.0)
 *   @param [in]     numPixels   Number of pixels in the image that the src[] histogram comes from (UQ32.0)
 *   @param [in]     minValue    Minimum value in the image that the src[] histogram comes from (UQ32.0)
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - All buffer pointers are 8 byte aligned
 *    - All buffer pointers point to arrays of 256 entries each
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Both cdf and dst buffers are optional.  Put a NULL pointer for the output which is not needed.
 */
VXLIB_STATUS    VXLIB_histogramCdfLut_i32u_o8u(const uint32_t src[restrict],
                                       uint32_t cdf[restrict],
                                       uint8_t dst[restrict],
                                       uint32_t numPixels,
                                       uint32_t minValue);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_histogramCdfLut_i32u_o8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - src pointer shall not be NULL
 *
 * @par
 *   @param [in]     src[]       Pointer to histogram of an image containing 256 bins (UQ32.0)
 *   @param [out]    cdf[]       Pointer to cumulative distribution output containing 256 bins (optional) (UQ32.0)
 *   @param [out]    dst[]       Pointer to lookup table output containing 256 entries (optional) (UQ8.0)
 *   @param [in]     numPixels   Number of pixels in the image that the src[] histogram comes from (UQ32.0)
 *   @param [in]     minValue    Minimum value in the image that the src[] histogram comes from (UQ32.0)
 */

VXLIB_STATUS VXLIB_histogramCdfLut_i32u_o8u_checkParams(const uint32_t src[restrict],
                                                const uint32_t cdf[restrict],
                                                const uint8_t dst[restrict],
                                                uint32_t numPixels,
                                                uint32_t minValue);
/** @} */
#endif

