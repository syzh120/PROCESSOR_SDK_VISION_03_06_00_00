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

#ifndef VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_H_
#define VXLIB_ACCUMULATESQUAREIMAGE_I8U_IO16S_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_accumulateSquareImage_i8u_io16s */
/** @ingroup  VXLIB_accumulateSquareImage_i8u_io16s */
/* @{ */
/**
 * @par Description:
 *  Accumulates a squared value from an input image to an output image.
 *
 * @par Method:
 *  Accumulate squares is computed by:
 *
 * @verbatim

    dst(x,y) = saturateINT16( (uint16)dst(x,y) + (((uint16)src(x,y)^2)>>(shift)) )

   @endverbatim
 *
 *
 * @par
 *   @param [in]     src[]         Pointer to array containing first input image (UQ8.0)
 *   @param [in]     src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [in,out] dst[]         Pointer to array containing output image (SQ15.0)
 *   @param [in]     dst_addr[]    Pointer to structure containing dimensional information of dst
 *   @param [in]     shift         Parameter indicating shift value, where 0 <= shift <= 15
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set widths equal to strides
 *      - Set all stride values to a multiple of 8
 *      - Set all width values to a multiple of 8
 */
VXLIB_STATUS    VXLIB_accumulateSquareImage_i8u_io16s(const uint8_t src[restrict],
                                        const VXLIB_bufParams2D_t * src_addr,
                                        int16_t dst[restrict],
                                        const VXLIB_bufParams2D_t * dst_addr,
                                        uint32_t shift);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_accumulateImage_i8u_io16s function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - All images shall have the same x and y dimensions
 *    - The strides of each image shall be equal to or greater than the x dimension
 *    - The shift parameter shall be < 16
 *
 * @par
 *   @param [in]     src[]         Pointer to array containing first input image (UQ8.0)
 *   @param [in]     src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [in,out] dst[]         Pointer to array containing output image (SQ15.0)
 *   @param [in]     dst_addr[]    Pointer to structure containing dimensional information of dst
 *   @param [in]     shift         Parameter indicating shift value, where 0 <= shift <= 15
 *
 */

VXLIB_STATUS VXLIB_accumulateSquareImage_i8u_io16s_checkParams(const uint8_t src[],
                                                 const VXLIB_bufParams2D_t *src_addr,
                                                 const int16_t dst[],
                                                 const VXLIB_bufParams2D_t *dst_addr,
                                                 uint32_t shift);
/** @} */
#endif

