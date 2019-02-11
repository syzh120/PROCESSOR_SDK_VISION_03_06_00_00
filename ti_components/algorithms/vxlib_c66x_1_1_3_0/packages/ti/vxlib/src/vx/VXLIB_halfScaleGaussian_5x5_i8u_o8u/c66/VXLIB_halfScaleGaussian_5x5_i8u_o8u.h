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

#ifndef VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_H_
#define VXLIB_HALFSCALEGAUSSIAN_5X5_I8U_O8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_halfScaleGaussian_5x5_i8u_o8u */
/** @ingroup  VXLIB_halfScaleGaussian_5x5_i8u_o8u */
/* @{ */
/**
 * @par Description:
 *  Computes a gaussian filter over the 5x5 neighborhood of each input pixel, then
 *  half scales the image in both horizontal and vertical using nearest neighbor
 *  interpolation.  
 *
 * @par Method:
 *  This filter uses the following convolution matrix:
 *
 * @verbatim

            | 1  4  6  4  1 |
            | 4 16 24 16  4 |
       K =  | 6 24 36 24  6 | * 1/256
            | 4 16 24 16  4 |
            | 1  4  6  4  1 |

   @endverbatim
 *
 *
 * @par
 *   @param [in]  src[]             Pointer to array containing input image (UQ8.0)
 *   @param [in]  src_addr[]        Pointer to structure containing dimensional information of src
 *   @param [out] dst[]             Pointer to array containing output image (UQ8.0)
 *   @param [in]  dst_addr[]        Pointer to structure containing dimensional information of dst
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - Input height should be >= (Output width + 2) * 2
 *    - Input height should be == (Output height + 2) * 2
 *    - When breaking input image processing into blocks, be sure to fetch enough overlap pixels from the input
 *      for interior edges for the rescale, or else the function may put a false border within the block edge of
 *      of the output image.  For each dimension, the required fetch amount should be:
 *          - input block width to fetch  = (output block width  + 2) * 2
 *          - input block height to fetch = (output block height + 2) * 2
 *
 *      And the amount of left/top overlap to refetch should be:
 *          - left edge overlap = 2
 *          - top edge overlap = 2
 */
VXLIB_STATUS    VXLIB_halfScaleGaussian_5x5_i8u_o8u(const uint8_t src[restrict],
                                const VXLIB_bufParams2D_t *src_addr,
                                uint8_t dst[restrict],
                                const VXLIB_bufParams2D_t *dst_addr);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_halfScaleGaussian_5x5_i8u_o8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - Input height should be >= (Output width + 2) * 2
 *    - Input height should be == (Output height + 2) * 2
 *    - The strides of each image shall be equal to or greater than the x dimension
 *
 * @par
 *   @param [in]  src[]             Pointer to array containing input image (UQ8.0)
 *   @param [in]  src_addr[]        Pointer to structure containing dimensional information of src
 *   @param [out] dst[]             Pointer to array containing output image (UQ8.0)
 *   @param [in]  dst_addr[]        Pointer to structure containing dimensional information of dst
 *
 */
VXLIB_STATUS    VXLIB_halfScaleGaussian_5x5_i8u_o8u_checkParams(const uint8_t src[restrict],
                                            const VXLIB_bufParams2D_t *src_addr,
                                            const uint8_t dst[restrict],
                                            const VXLIB_bufParams2D_t *dst_addr);
/** @} */
#endif
