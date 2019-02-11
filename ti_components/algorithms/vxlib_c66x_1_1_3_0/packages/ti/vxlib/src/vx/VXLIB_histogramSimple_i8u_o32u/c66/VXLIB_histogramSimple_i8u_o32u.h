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

#ifndef VXLIB_HISTOGRAMSIMPLE_I8U_O32U_H_
#define VXLIB_HISTOGRAMSIMPLE_I8U_O32U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_histogramSimple_i8u_o32u */
/** @ingroup  VXLIB_histogramSimple_i8u_o32u */
/* @{ */
/**
 * @par Description:
 *  Generates a distribution from an image. This kernel counts the number of occurrences of
 *  each pixel value and populates the distribution array.  It also returns the minimum value
 *  from the input image.
 *
 * @par
 *   @param [in]     src[]         Pointer to array containing first input image (UQ8.0)
 *   @param [in]     src_addr[]    Pointer to structure containing dimensional information of src
 *   @param [out]    dist[]        Pointer to array containing the distribution (UQ32.0)
 *   @param [in,out] scratch[]     Pointer to array containing the intermediate distribution data (UQ32.0)
 *   @param [out]    *minValue     Pointer to minimum input value in the image (UQ32.0)
 *   @param [in]     lastBlock     Flag that indicates if the function call is the final call for the image (0: intermediate call, 1: Final call)
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - dist buffer assumed to have 256 entries
 *    - scratch buffer assumed to have 1024 entries
 *    - scratch buffer pointer assumed to be 8-byte aligned.
 *    - PARAMETER INITIALIZATION:
 *        - All scratch entries should be externally initialized to zero before calling the function for the first time
 *          since it is always read by the function regardless if the function is being called once per image, or
 *          multiple times per image.
 *          - Scratch entries should not be re-initialized for each block of an image, only for each new image.
 *          - If calling only once per full image, lastBlock can be set to 1 so that dist array is populated.
 *        - If a user wants to divide processing of the image into smaller blocks, then user should set lastBlock to
 *          0 for all blocks except the final block in the image.
 *    - NOTE: The dist and minValue outputs of the function are only considered accurate for the whole image when
 *      the lastBlock parameter is set to 1.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set widths equal to strides
 *      - Align src pointer to 4 byte boundaries
 *      - Set all stride values to a multiple of 4
 *      - Set all width values to a multiple of 8
 */
VXLIB_STATUS    VXLIB_histogramSimple_i8u_o32u(const uint8_t src[restrict],
                                       const VXLIB_bufParams2D_t * src_addr,
                                       uint32_t dist[restrict],
                                       uint32_t scratch[restrict],
                                       uint32_t *minValue,
                                       uint8_t lastBlock);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_histogramSimple_i8u_o32u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - The strides of the src image shall be equal to or greater than the x dimension
 *    - lastBlock shall be either 0 or 1
 *
 * @par
 *   @param [in]     src[]        Pointer to array containing input image (UQ8.0)
 *   @param [in]     src_addr[]   Pointer to structure containing dimensional information of src
 *   @param [out]    dist[]       Pointer to array containing the distribution (UQ32.0)
 *   @param [in,out] scratch[]    Pointer to array containing the distribution (UQ32.0)
 *   @param [out]    *minValue    Pointer to minimum input value in the image (UQ32.0)
 *   @param [in]     lastBlock    Flag that indicates if the function call is the final call for the image (0: intermediate call, 1: Final call)
 *
 */

VXLIB_STATUS VXLIB_histogramSimple_i8u_o32u_checkParams(const uint8_t src[],
                                                const VXLIB_bufParams2D_t *src_addr,
                                                const uint32_t dist[],
                                                const uint32_t scratch[],
                                                const uint32_t *minValue,
                                                uint8_t lastBlock);
/** @} */
#endif

