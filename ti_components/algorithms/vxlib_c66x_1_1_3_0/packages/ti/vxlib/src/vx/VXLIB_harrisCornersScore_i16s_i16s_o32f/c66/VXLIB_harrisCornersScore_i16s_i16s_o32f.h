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

#ifndef VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_H_
#define VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_harrisCornersScore_i16s_i16s_o32f */
/** @ingroup  VXLIB_harrisCornersScore_i16s_i16s_o32f */
/* @{ */
/**
 * @par Description:
 *  Given the image x and y gradients, this performs the harris score computation
 *  for a programmable neighborhood size (block_size) of each pixel.
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
 *   @param [out] dst[]              Pointer to array containing output strengths (F32)
 *   @param [in]  dst_addr[]         Pointer to structure containing dimensional information of dst
 *   @param [in]  scratch[]          Pointer to scratch buffer of size = 4*3*(block_size+1)*width bytes
 *   @param [in]  sensitivity        Sensitivity threshold 'k' from the Harris-Stephens equation
 *   @param [in]  gradient_size      Gradient size used to generate the sobel gradient inputs (3, 5, or 7)
 *   @param [in]  block_size         Block size to use in the Harris Score computation (3, 5, or 7)
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - Valid output data in dst buffer is (block_size-1) pixels smaller in both horizontal and vertical
 *      directions due to neighborhood computation.
 *    - Valid gradient_size values are 3 (for 3x3 sobel), 5 (for 5x5 sobel), or 7(for 7x7 sobel)
 *    - Valid block_size values are 3 (for 3x3), 5 (for 5x5), or 7(for 7x7)
 *    - The scratch buffer should be allocated at least a buffer of size 4*3*(block_size+1)*width bytes
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set widths equal to strides
 *      - Allocate scratch buffer in fast memory
 */
VXLIB_STATUS    VXLIB_harrisCornersScore_i16s_i16s_o32f(const int16_t src_x[restrict],
                                                     const VXLIB_bufParams2D_t * src_x_addr,
                                                     const int16_t src_y[restrict],
                                                     const VXLIB_bufParams2D_t * src_y_addr,
                                                     VXLIB_F32 dst[restrict],
                                                     const VXLIB_bufParams2D_t * dst_addr,
                                                     VXLIB_F32 scratch[restrict],
                                                     VXLIB_F32 sensitivity,
                                                     uint8_t gradient_size,
                                                     uint8_t block_size);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_harrisCornersScore_i16s_i16s_o32f function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - All inputs shall have the same x and y dimensions
 *    - Output shall have have a y dimension of at least (block_size-1) rows less than input y dimension
 *    - The strides of each image shall be equal to or greater than the x dimension
 *
 * @par
 *   @param [in]  src_x[]            Pointer to array containing x gradient input image (SQ15.0)
 *   @param [in]  src_x_addr[]       Pointer to structure containing dimensional information of src_x
 *   @param [in]  src_y[]            Pointer to array containing y gradient input image (SQ15.0)
 *   @param [in]  src_y_addr[]       Pointer to structure containing dimensional information of src_y
 *   @param [out] dst[]              Pointer to array containing output strengths (F32)
 *   @param [in]  dst_addr[]         Pointer to structure containing dimensional information of dst
 *   @param [in]  scratch[]          Pointer to scratch buffer of size = 4*3*(block_size+1)*width bytes
 *   @param [in]  sensitivity        Sensitivity threshold 'k' from the Harris-Stephens equation
 *   @param [in]  gradient_size      Gradient size used to generate the sobel gradient inputs (3, 5, or 7)
 *   @param [in]  block_size         Block size to use in the Harris Score computation (3, 5, or 7)
 *
 */

VXLIB_STATUS VXLIB_harrisCornersScore_i16s_i16s_o32f_checkParams(const int16_t src_x[restrict],
                                                     const VXLIB_bufParams2D_t * src_x_addr,
                                                     const int16_t src_y[restrict],
                                                     const VXLIB_bufParams2D_t * src_y_addr,
                                                     VXLIB_F32 dst[restrict],
                                                     const VXLIB_bufParams2D_t * dst_addr,
                                                     VXLIB_F32 scratch[restrict],
                                                     VXLIB_F32 sensitivity,
                                                     uint8_t gradient_size,
                                                     uint8_t block_size);
/** @} */
#endif

