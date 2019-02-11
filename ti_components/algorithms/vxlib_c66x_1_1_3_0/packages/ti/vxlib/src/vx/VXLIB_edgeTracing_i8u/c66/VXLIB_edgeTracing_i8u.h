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

#ifndef VXLIB_EDGETRACING_I8U_H_
#define VXLIB_EDGETRACING_I8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_edgeTracing_i8u */
/** @ingroup  VXLIB_edgeTracing_i8u */
/* @{ */
/**
 * @par Description:
 *  Promotes possible edges to strong edges if they touch strong edges.  Since
 *  a possible edge can be promoted to a strong edge, the processing must consider
 *  possible edges that are touching other possible edges that are promoted to
 *  strong edges (a kind of recursive processing).
 *
 * @par Method:
 *  For each strong edge in the edgeList array:
 *    - Remove coordinate from list
 *    - Promote possible edges (127) that are in the 8 pixel neighborhood of the
 *      strong edge, to a strong edge (255)
 *    - Add the new strong edge to the list for consideration of its neighborhood
 *
 * @par
 *   @param [in,out] edgeMap[]          Pointer to array containing edge map image image (UQ8.0)
 *   @param [in]     edgeMap_addr[]     Pointer to structure containing dimensional information of edgeMap
 *   @param [in,out] edgeList[]         Pointer to array containing list of strong edges
 *                                       This list is modified during processing such that output is not meaningful (UQ32.0)
 *   @param [in]     edgeListCapacity   Number of entries allocated in the edgeList array
 *   @param [in]     numEdgesIn         Number of strong edges listed in the edgeList array
 *   @param [out]    *numEdgesOut       Number of strong edges in the edgeMap after processing is complete.
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - The one pixel border of edgeMap should all be 0's (non-edges) before calling this function since this function
 *      does not support border processing and may perform out of memory access if the border has any non-zeros.
 *      - The edgeList should also not have any indices of pixels in the one pixel border.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 */
VXLIB_STATUS    VXLIB_edgeTracing_i8u(uint8_t edgeMap[],
                                      const VXLIB_bufParams2D_t * edgeMap_addr,
                                      uint32_t edgeList[],
                                      uint32_t edgeListCapacity,
                                      uint32_t numEdgesIn,
                                      uint32_t *numEdgesOut);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_edgeTracing_i8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *    - edgeListCapacity shall be > numEdgesIn-8 
 *    - The strides of each image shall be equal to or greater than the x dimension
 *
 * @par
 *   @param [in,out] edgeMap[]          Pointer to array containing edge map image image (UQ8.0)
 *   @param [in]     edgeMap_addr[]     Pointer to structure containing dimensional information of edgeMap
 *   @param [in,out] edgeList[]         Pointer to array containing list of strong edges
 *                                       This list is modified during processing such that output is not meaningful (UQ32.0)
 *   @param [in]     edgeListCapacity   Number of entries allocated in the edgeList array
 *   @param [in]     numEdgesIn         Number of strong edges listed in the edgeList array
 *   @param [out]    *numEdgesOut       Number of strong edges in the edgeMap after processing is complete.
 *
 */

VXLIB_STATUS VXLIB_edgeTracing_i8u_checkParams(uint8_t edgeMap[],
                                               const VXLIB_bufParams2D_t * edgeMap_addr,
                                               uint32_t edgeList[],
                                               uint32_t edgeListCapacity,
                                               uint32_t numEdgesIn,
                                               const uint32_t *numEdgesOut);
/** @} */
#endif

