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

#ifndef VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_H_
#define VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_cannyNMS_i16s_i16s_i16u_o8u */
/** @ingroup  VXLIB_cannyNMS_i16s_i16s_i16u_o8u */
/* @{ */
/**
 * @par Description:
 *  Given the image x and y gradients and associated magnitude image, this performs
 *  the non-maximum suppression given the 3x3 neighborhood of each pixel.
 *  Pixels are retained (output of 127), if the magnitude is greater than
 *  or equal to the pixels in the direction perpendicular to its edge orientation.
 *  Suppressed pixels are output as value 0.
 *
 * @par Method:
 * 
 *
 *
 * @par
 *   @param [in]  src_x[]            Pointer to array containing x gradient input image (SQ15.0)
 *   @param [in]  src_x_addr[]       Pointer to structure containing dimensional information of src_x
 *   @param [in]  src_y[]            Pointer to array containing y gradient input image (SQ15.0)
 *   @param [in]  src_y_addr[]       Pointer to structure containing dimensional information of src_y
 *   @param [in]  src_mag[]          Pointer to array containing magnitude input image (UQ16.0)
 *   @param [in]  src_mag_addr[]     Pointer to structure containing dimensional information of src_mag
 *   @param [out] dst[]              Pointer to array containing output image (UQ8.0)
 *   @param [in]  dst_addr[]         Pointer to structure containing dimensional information of dst
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - Valid output data is 2 pixels smaller in horizontal direction, and 2 pixels smaller in vertical
 *      direction due to neighborhood comparison.
 *    - Max value of magnitude supported is 0xfffe.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set widths equal to strides
 *      - Set all stride values to a multiple of 2
 *      - Set all width values to a multiple of 2
 */
VXLIB_STATUS    VXLIB_cannyNMS_i16s_i16s_i16u_o8u(const int16_t src_x[restrict],
                                                  const VXLIB_bufParams2D_t * src_x_addr,
                                                  const int16_t src_y[restrict],
                                                  const VXLIB_bufParams2D_t * src_y_addr,
                                                  const uint16_t src_mag[restrict],
                                                  const VXLIB_bufParams2D_t * src_mag_addr,
                                                  uint8_t dst[restrict],
                                                  const VXLIB_bufParams2D_t * dst_addr);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_cannyNMS_i16s_i16s_i16u_o8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - All inputs shall have the same x and y dimensions
 *    - Output shall have have a y dimension of at least 2 rows less than input y dimension
 *    - The strides of each image shall be equal to or greater than the x dimension
 *
 * @par
 *   @param [in]  src_x[]            Pointer to array containing x gradient input image (SQ15.0)
 *   @param [in]  src_x_addr[]       Pointer to structure containing dimensional information of src_x
 *   @param [in]  src_y[]            Pointer to array containing y gradient input image (SQ15.0)
 *   @param [in]  src_y_addr[]       Pointer to structure containing dimensional information of src_y
 *   @param [in]  src_mag[]          Pointer to array containing magnitude input image (UQ16.0)
 *   @param [in]  src_mag_addr[]     Pointer to structure containing dimensional information of src_mag
 *   @param [out] dst[]              Pointer to array containing output image (UQ8.0)
 *   @param [in]  dst_addr[]         Pointer to structure containing dimensional information of dst
 *
 */

VXLIB_STATUS VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams(const int16_t src_x[restrict],
                                                           const VXLIB_bufParams2D_t * src_x_addr,
                                                           const int16_t src_y[restrict],
                                                           const VXLIB_bufParams2D_t * src_y_addr,
                                                           const uint16_t src_mag[restrict],
                                                           const VXLIB_bufParams2D_t * src_mag_addr,
                                                           uint8_t dst[restrict],
                                                           const VXLIB_bufParams2D_t * dst_addr);
/** @} */
#endif

