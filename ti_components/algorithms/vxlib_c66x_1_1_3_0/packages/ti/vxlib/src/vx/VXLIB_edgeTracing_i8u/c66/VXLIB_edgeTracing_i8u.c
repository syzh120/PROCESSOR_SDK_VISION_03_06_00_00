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
**|         Copyright (c) 2016 - 2017 Texas Instruments Incorporated         |**
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

#include "VXLIB_edgeTracing_i8u.h"

CODE_SECTION(VXLIB_edgeTracing_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_edgeTracing_i8u_checkParams,  ".text:optimized")

static inline uint8_t* getPtrU8(uint8_t ptr[], int16_t offset);

static inline uint8_t* getPtrU8(uint8_t ptr[], int16_t offset) {
    return &ptr[offset];
}

VXLIB_STATUS VXLIB_edgeTracing_i8u(uint8_t edgeMap[],
                                   const VXLIB_bufParams2D_t * edgeMap_addr,
                                   uint32_t edgeList[],
                                   uint32_t edgeListCapacity,
                                   uint32_t numEdgesIn,
                                   uint32_t *numEdgesOut)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_EDGETRACING_I8U_CHECK_PARAMS)
    status = VXLIB_edgeTracing_i8u_checkParams(edgeMap, edgeMap_addr, edgeList, edgeListCapacity, numEdgesIn, numEdgesOut);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t    checkLocation;

        uint8_t    addTL;
        uint8_t    addTC;
        uint8_t    addTR;
        uint8_t    addLC;
        uint8_t    addRC;
        uint8_t    addBL;
        uint8_t    addBC;
        uint8_t    addBR;

        int16_t    offsetTL;
        int16_t    offsetTC;
        int16_t    offsetTR;
        int16_t    offsetRC;
        int16_t    offsetBR;
        int16_t    offsetBC;
        int16_t    offsetBL;
        int16_t    offsetLC;

        uint8_t *restrict mapTL;
        uint8_t *restrict mapTC;
        uint8_t *restrict mapTR;
        uint8_t *restrict mapLC;
        uint8_t *restrict mapRC;
        uint8_t *restrict mapBL;
        uint8_t *restrict mapBC;
        uint8_t *restrict mapBR;
        uint8_t *restrict mapC;

        /* Initialize the totalEdges variable with the number of strong edges
         * already in the list */
        uint32_t totalEdges = numEdgesIn;
        uint32_t oldNum;

        /* Initialize the sufficientCapacity variable with an 8 entry buffer before running
         * out of memory */
        uint32_t sufficientCapacity = (uint32_t)(numEdgesIn < (edgeListCapacity-8U));

        offsetTL = (int16_t)-1 - edgeMap_addr->stride_y;
        offsetTC = (int16_t)-0 - edgeMap_addr->stride_y;
        offsetTR = (int16_t)+1 - edgeMap_addr->stride_y;
        offsetRC = (int16_t)+1;
        offsetBR = (int16_t)+1 + edgeMap_addr->stride_y;
        offsetBC = (int16_t)-0 + edgeMap_addr->stride_y;
        offsetBL = (int16_t)-1 + edgeMap_addr->stride_y;
        offsetLC = (int16_t)-1;

        /* Revisit edge list; examine edge neighbor for possible edge continuity
         * Stop processing if we have reached the end of the list, or if we are
         * at risk of overflowing the list and overrun memory */
        while( (numEdgesIn > 0) && (sufficientCapacity != 0)) {

            /* Decrment the stack index as we will consider the end of the stack (list)
             * first */
            numEdgesIn--;

            /* Get the offset location from the end of the strong edge list */
            checkLocation = edgeList[numEdgesIn];
            
            /* Get pointer address the strong edge from the list */
            mapC = edgeMap + checkLocation;

            /* Get pointers of each neighbor of the strong edge */
            mapTL = getPtrU8(mapC, offsetTL);
            mapTC = getPtrU8(mapC, offsetTC);
            mapTR = getPtrU8(mapC, offsetTR);
            mapLC = getPtrU8(mapC, offsetLC);
            mapRC = getPtrU8(mapC, offsetRC);
            mapBR = getPtrU8(mapC, offsetBR);
            mapBC = getPtrU8(mapC, offsetBC);
            mapBL = getPtrU8(mapC, offsetBL);

            /* Set flags if neighbor pixels are possible edges */
            addTL = (uint8_t)(*mapTL == 127U);
            addTC = (uint8_t)(*mapTC == 127U);
            addTR = (uint8_t)(*mapTR == 127U);
            addRC = (uint8_t)(*mapRC == 127U);
            addBR = (uint8_t)(*mapBR == 127U);
            addBC = (uint8_t)(*mapBC == 127U);
            addBL = (uint8_t)(*mapBL == 127U);
            addLC = (uint8_t)(*mapLC == 127U);

            /* If the neighbor is a possible edge (127), promote to strong edge (255) */
            *mapTL += (uint8_t)(addTL << 7);
            *mapTC += (uint8_t)(addTC << 7);
            *mapTR += (uint8_t)(addTR << 7);
            *mapRC += (uint8_t)(addRC << 7);
            *mapBR += (uint8_t)(addBR << 7);
            *mapBC += (uint8_t)(addBC << 7);
            *mapBL += (uint8_t)(addBL << 7);
            *mapLC += (uint8_t)(addLC << 7);

            /* Save a temporary variable of the number of edges in the list before
             * we add more edges to the list */
            oldNum = numEdgesIn;

            /* For each neighbor, add the index of the neighbor to the list if it is
             * promoted to a strong edge */
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetTL;
            numEdgesIn += addTL;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetTC;
            numEdgesIn += addTC;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetTR;
            numEdgesIn += addTR;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetRC;
            numEdgesIn += addRC;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetBR;
            numEdgesIn += addBR;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetBC;
            numEdgesIn += addBC;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetBL;
            numEdgesIn += addBL;
            edgeList[numEdgesIn] = checkLocation + (uint32_t)offsetLC;
            numEdgesIn += addLC;

            /* Increment the total edges variable by the number of edges added
             * to the list (new strong edges) */
            totalEdges += (numEdgesIn-oldNum);

            /* Update the sufficientCapacity variable with an 8 entry buffer before running
             * out of memory (since we may have added entries to the list) */
            sufficientCapacity = (uint32_t)(numEdgesIn < (edgeListCapacity-8U));
        }

        /* Write out the final number of strong edges in the edgeMap */
        *numEdgesOut = totalEdges;

        /* If we ran out of buffer, report error */
        status = (sufficientCapacity == 1U) ? VXLIB_SUCCESS : VXLIB_ERR_BUFFER_TOO_SMALL;
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_EDGETRACING_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_EDGETRACING_I8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_edgeTracing_i8u_checkParams(uint8_t edgeMap[],
                                               const VXLIB_bufParams2D_t * edgeMap_addr,
                                               uint32_t edgeList[],
                                               uint32_t edgeListCapacity,
                                               uint32_t numEdgesIn,
                                               const uint32_t *numEdgesOut)
{
    VXLIB_STATUS    status;

    if((edgeMap == NULL) || (edgeList == NULL) || (numEdgesOut == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((uint32_t)edgeMap_addr->stride_y < edgeMap_addr->dim_x) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(edgeMap_addr->data_type != VXLIB_UINT8) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((int32_t)edgeListCapacity < ((int32_t)numEdgesIn-8)) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

