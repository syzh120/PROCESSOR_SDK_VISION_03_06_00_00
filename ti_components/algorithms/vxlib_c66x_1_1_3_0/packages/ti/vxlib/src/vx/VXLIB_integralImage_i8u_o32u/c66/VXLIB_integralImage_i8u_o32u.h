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

#ifndef VXLIB_INTEGRALIMAGE_I8U_O32U_H_
#define VXLIB_INTEGRALIMAGE_I8U_O32U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_integralImage_i8u_o32u */
/** @ingroup  VXLIB_integralImage_i8u_o32u */
/* @{ */
/**
 * @par Description:
 *  Computes the integral image of the input. Each output pixel is the sum of the
 *  corresponding input pixel and all other pixels above and to the left of it.
 *
 * @par Method:
 *  The integral image is computed using the following equation:
 *
 * @verbatim

    dst(x,y) = sum(x,y)

    where, for x>=0 and y>=0

    sum(x,y) = src(x,y) + sum(x-1,y) + sum(x,y-1) - sum(x-1,y-1)

    otherwise,

    sum(x,y)=0

   @endverbatim
 *
 *
 * @par
 *   @param [in]  src[]         Pointer to array containing first input image (UQ8.0)
 *   @param [in]  src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [out] dst[]         Pointer to array containing output image (UQ32.0)
 *   @param [in]  dst_addr[]    Pointer to structure containing dimensional information of dst
 *   @param [in]  prevRow[]     Pointer to array containing the last row from a previous execution
 *   @param [in]  prevCol[]     Pointer to array containing the last column from a previous execution (optional)
 *   @param [in]  prevRowUpdate Flag that indicates if the function should update the prevRow data (0: Don't update, 1: Update)
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - The number of elements in prevRow buffer should be equal to the width of the full image
 *    - The number of elements in prevCol buffer should be equal to the height of the full image
 *    - PARAMETER INITIALIZATION:
 *        - All prevRow entries should be externally initialized to zero before calling the function for the first time
 *          since it is always read by the function regardless if the function is being called once per image, or
 *          multiple times per image.
 *          - If calling only once per full image, prevRowUpdate can be set to 0 so that the zero initialized prevRow
 *            buffer doesn't get updated by the function, and can be re-used for subsequent images without re-initializing.
 *        - If a user wants to divide processing of the image into smaller blocks, then it can use the prevRow
 *          and prevCol arrays to store the state information between function calls (prevRowUpdate should be set to 1).
 *        - When using prevCol, all entries should be externally initialized to zero, before calling the function
 *          for the first time for each image.
 *        - As the function is called across different blocks of an image, be sure to change the prevRow and prevCol
 *          pointers to align with the y and x offset of the src and dst image pointers, respectivly.
 *        - If processing the image in horizontal strips (where the width of each strip is the width of the image),
 *          then prevCol may still be set to NULL.
 *        - If processing the image in vertical strips (where the height of each strip is the height of the image),
 *          then prevRowUpdate may be set to 0, and prevCol should be non-NULL.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Align all pointers to 8 byte boundaries
 *      - Set all stride values to a multiple of 8
 *      - Set all width values to a multiple of 8
 */
VXLIB_STATUS    VXLIB_integralImage_i8u_o32u(const uint8_t src[restrict],
                                     const VXLIB_bufParams2D_t * src_addr,
                                     uint32_t dst[restrict],
                                     const VXLIB_bufParams2D_t * dst_addr,
                                     uint32_t prevRow[restrict],
                                     uint32_t prevCol[restrict],
                                     uint32_t prevRowUpdate);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_integralImage_i8u_o32u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - All images shall have the same x and y dimensions
 *    - The strides of each image shall be equal to or greater than the x dimension
 *    - prevRowUpdate shall be either 0 or 1
 *
 * @par
 *   @param [in]  src[]         Pointer to array containing first input image (UQ8.0)
 *   @param [in]  src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [out] dst[]         Pointer to array containing output image (UQ32.0)
 *   @param [in]  dst_addr[]    Pointer to structure containing dimensional information of dst
 *   @param [in]  prevRow[]     Pointer to array containing the last row from a previous execution
 *   @param [in]  prevCol[]     Pointer to array containing the last column from a previous execution (optional)
 *   @param [in]  prevRowUpdate Flag that indicates if the function should update the prevRow data (0: Don't update, 1: Update)
 *
 */

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_checkParams(const uint8_t src[],
                                              const VXLIB_bufParams2D_t *src_addr,
                                              const uint32_t dst[],
                                              const VXLIB_bufParams2D_t *dst_addr,
                                              const uint32_t prevRow[],
                                              const uint32_t prevCol[],
                                              uint32_t prevRowUpdate);
/** @} */
#endif

