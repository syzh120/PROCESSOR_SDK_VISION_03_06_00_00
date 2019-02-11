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

#ifndef VXLIB_DOUBLETHRESHOLD_I16U_I8U_H_
#define VXLIB_DOUBLETHRESHOLD_I16U_I8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_doubleThreshold_i16u_i8u */
/** @ingroup  VXLIB_doubleThreshold_i16u_i8u */
/* @{ */
/**
 * @par Description:
 *  Applies a double theshold to the edgeMap based on the magnitude values.
 *
 * @par Method:
 *  For each pixel in the edgeMap:
 *    - If value was 127 and is above high threshold, then it is now 255
 *    - If value was 127 and is above low threshold, then it is still 127
 *    - If value was 127 and is below low threshold, then it is now 0
 *    - If value was   0, then it is still 0
 *
 * @par
 *   @param [in]     src_mag[]          Pointer to array containing magnitude input image (UQ16.0)
 *   @param [in]     src_mag_addr[]     Pointer to structure containing dimensional information of src_mag
 *   @param [in,out] edgeMap[]          Pointer to array containing edge map image image (UQ8.0)
 *   @param [in]     edgeMap_addr[]     Pointer to structure containing dimensional information of edgeMap
 *   @param [in]     edgeMapLineOffset  Line offset of the full edgeMap in external memory.
 *                                       This is normally equal to edgeMap_addr.stride_y, but if this is being
 *                                       called on smaller blocks which have been copied to a separate memory than
 *                                       the original image, then this value should be set to the original stride
 *                                       of the full image in memory so that the edgeList indices are computed relative
 *                                       to the full image for downstream processing.
 *   @param [out]    edgeList[]         Pointer to array containing list of strong edges (UQ32.0)
 *   @param [in]     edgeListCapacity   Number of entries allocated in the edgeList array
 *   @param [out]    *numEdges          Number of strong edges added to the edgeList array
 *   @param [in]     startPosition      Number corresponding to the starting index of a larger array
 *                                       This is normally zero, but if this is being called on blocks, then the
 *                                       index of the pixel associated with the starting pixel of this block can
 *                                       be put here, and downstream processing can index into the full image.
 *   @param [in]     loThreshold        Magnitudes less than or equal to this value will be marked as non-edges
 *   @param [in]     hiThreshold        Magnitudes greater than this value will be marked as edges
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - Max value of magnitude supported is 0xfffe.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set all width values to a multiple of 4
 */
VXLIB_STATUS    VXLIB_doubleThreshold_i16u_i8u(const uint16_t src_mag[restrict],
                                               const VXLIB_bufParams2D_t * src_mag_addr,
                                               uint8_t edgeMap[restrict],
                                               const VXLIB_bufParams2D_t * edgeMap_addr,
                                               uint16_t edgeMapLineOffset,
                                               uint32_t edgeList[restrict],
                                               uint32_t edgeListCapacity,
                                               uint32_t *numEdges,
                                               uint32_t startPosition,
                                               uint32_t loThreshold,
                                               uint32_t hiThreshold);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_doubleThreshold_i16u_i8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - edgeListCapacity shall be > 0 
 *    - The strides of each image shall be equal to or greater than the x dimension
 *    - The hiThreshold must be > than loThreshold
 *
 * @par
 *   @param [in]     src_mag[]          Pointer to array containing magnitude input image (UQ16.0)
 *   @param [in]     src_mag_addr[]     Pointer to structure containing dimensional information of src_mag
 *   @param [in,out] edgeMap[]          Pointer to array containing edge map image image (UQ8.0)
 *   @param [in]     edgeMap_addr[]     Pointer to structure containing dimensional information of edgeMap
 *   @param [in]     edgeMapLineOffset  Line offset of the full edgeMap in external memory.
 *                                       This is normally equal to edgeMap_addr.stride_y, but if this is being
 *                                       called on smaller blocks which have been copied to a separate memory than
 *                                       the original image, then this value should be set to the original stride
 *                                       of the full image in memory so that the edgeList indices are computed relative
 *                                       to the full image for downstream processing.
 *   @param [out]    edgeList[]         Pointer to array containing list of strong edges (UQ32.0)
 *   @param [in]     edgeListCapacity   Number of entries allocated in the edgeList array
 *   @param [out]    *numEdges          Number of strong edges added to the edgeList array
 *   @param [in]     startPosition      Number corresponding to the starting index of a larger array
 *                                       This is normally zero, but if this is being called on blocks, then the
 *                                       index of the pixel associated with the starting pixel of this block can
 *                                       be put here, and downstream processing can index into the full image.
 *   @param [in]     loThreshold        Magnitudes less than or equal to this value will be marked as non-edges
 *   @param [in]     hiThreshold        Magnitudes greater than this value will be marked as edges
 *
 */

VXLIB_STATUS VXLIB_doubleThreshold_i16u_i8u_checkParams(const uint16_t src_mag[restrict],
                                                        const VXLIB_bufParams2D_t * src_mag_addr,
                                                        const uint8_t edgeMap[restrict],
                                                        const VXLIB_bufParams2D_t * edgeMap_addr,
                                                        uint16_t edgeMapLineOffset,
                                                        const uint32_t edgeList[restrict],
                                                        uint32_t edgeListCapacity,
                                                        const uint32_t *numEdges,
                                                        uint32_t startPosition,
                                                        uint32_t loThreshold,
                                                        uint32_t hiThreshold);
/** @} */
#endif

