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

#ifndef VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_H_
#define VXLIB_COLORCONVERT_RGBTORGBX_I8U_O8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_colorConvert_RGBtoRGBX_i8u_o8u */
/** @ingroup  VXLIB_colorConvert_RGBtoRGBX_i8u_o8u */
/* @{ */
/**
 * @par Description:
 *  Performs a color conversion operation from RGB interleaved to RGBX interleaved.
 *
 * @par Method:
 *  Copy all channels, and insert an X value of 255.
 *
 * @par
 *   @param [in]  src[]         Pointer to array containing input RGB image (UQ8.0)
 *   @param [in]  src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [out] dst[]         Pointer to array containing output RGBX image (UQ8.0)
 *   @param [in]  dst_addr[]    Pointer to structure containing dimensional information of dst
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - RGB Input (1 plane): src_addr
 *      - 'dim_x' refers to the number of RGB pixel units per line
 *      - 'dim_y' refers to the number of lines in the image
 *      - 'stride_y' should be at least ('dim_x' * 3 * 1) bytes
 *    - RGBX (1 plane): dst_addr
 *      - 'dim_x' refers to the number of RGBX pixel units per line
 *      - 'dim_y' refers to the number of lines in the image
 *      - 'stride_y' should be at least ('dim_x' * 4 * 1) bytes
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set widths equal to strides
 *      - Align all pointers to 8 byte boundaries
 *      - Set all stride and width values to a multiple of 8
 */
VXLIB_STATUS    VXLIB_colorConvert_RGBtoRGBX_i8u_o8u(const uint8_t src[restrict],
                                  const VXLIB_bufParams2D_t * src_addr,
                                  uint8_t dst[restrict],
                                  const VXLIB_bufParams2D_t * dst_addr);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_colorConvert_RGBtoRGBX_i8u_o8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - Both images shall have the same x and y dimensions
 *    - The stride_y of the src image shall be equal to or greater than dim_x * 3
 *    - The stride_y of the dst image shall be equal to or greater than dim_x * 4
 *
 * @par
 *   @param [in]  src[]         Pointer to array containing input RGB image (UQ8.0)
 *   @param [in]  src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [out] dst[]         Pointer to array containing output RGBX image (UQ8.0)
 *   @param [in]  dst_addr[]    Pointer to structure containing dimensional information of dst
 *
 */

VXLIB_STATUS VXLIB_colorConvert_RGBtoRGBX_i8u_o8u_checkParams(const uint8_t src[],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst[],
                                           const VXLIB_bufParams2D_t *dst_addr);
/** @} */
#endif

