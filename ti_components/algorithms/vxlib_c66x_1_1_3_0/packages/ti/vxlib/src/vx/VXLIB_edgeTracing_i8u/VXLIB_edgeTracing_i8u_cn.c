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

#include "VXLIB_edgeTracing_i8u_cn.h"

CODE_SECTION(VXLIB_edgeTracing_i8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_edgeTracing_i8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_edgeTracing_i8u_cn(uint8_t edgeMap[],
                                      VXLIB_bufParams2D_t * edgeMap_addr,
                                      uint32_t edgeList[],
                                      uint32_t edgeListCapacity,
                                      uint32_t numEdgesIn,
                                      uint32_t *numEdgesOut)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_edgeTracing_i8u_checkParams_cn(edgeMap, edgeMap_addr, edgeList, edgeListCapacity, numEdgesIn, numEdgesOut);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    checkLocation;

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

        uint8_t *mapTL;
        uint8_t *mapTC;
        uint8_t *mapTR;
        uint8_t *mapLC;
        uint8_t *mapRC;
        uint8_t *mapBL;
        uint8_t *mapBC;
        uint8_t *mapBR;
        uint8_t *mapC;

        uint32_t totalEdges = numEdgesIn;
        uint32_t oldNum;
        uint32_t sufficientCapacity = (numEdgesIn < (edgeListCapacity-8));

        offsetTL = -1 - edgeMap_addr->stride_y;
        offsetTC = -0 - edgeMap_addr->stride_y;
        offsetTR = +1 - edgeMap_addr->stride_y;
        offsetRC = +1;
        offsetBR = +1 + edgeMap_addr->stride_y;
        offsetBC = -0 + edgeMap_addr->stride_y;
        offsetBL = -1 + edgeMap_addr->stride_y;
        offsetLC = -1;

        /* /////////////////////////////////////////////////////////////////////// */
        /* Revisit edge list; examine edge neighbors for possible edge continuity */

        while( numEdgesIn && sufficientCapacity) {
            numEdgesIn--;
            checkLocation = edgeList[numEdgesIn];
            
            mapC = edgeMap + checkLocation;

            mapTL = mapC + offsetTL;
            mapTC = mapC + offsetTC;
            mapTR = mapC + offsetTR;
            mapLC = mapC + offsetLC;
            mapRC = mapC + offsetRC;
            mapBR = mapC + offsetBR;
            mapBC = mapC + offsetBC;
            mapBL = mapC + offsetBL;

            addTL = (*mapTL == 127);
            addTC = (*mapTC == 127);
            addTR = (*mapTR == 127);
            addRC = (*mapRC == 127);
            addBR = (*mapBR == 127);
            addBC = (*mapBC == 127);
            addBL = (*mapBL == 127);
            addLC = (*mapLC == 127);

            *mapTL += addTL << 7;
            *mapTC += addTC << 7;
            *mapTR += addTR << 7;
            *mapRC += addRC << 7;
            *mapBR += addBR << 7;
            *mapBC += addBC << 7;
            *mapBL += addBL << 7;
            *mapLC += addLC << 7;

            oldNum = numEdgesIn;

            edgeList[numEdgesIn] = checkLocation + offsetTL;
            numEdgesIn += addTL;
            edgeList[numEdgesIn] = checkLocation + offsetTC;
            numEdgesIn += addTC;
            edgeList[numEdgesIn] = checkLocation + offsetTR;
            numEdgesIn += addTR;
            edgeList[numEdgesIn] = checkLocation + offsetRC;
            numEdgesIn += addRC;
            edgeList[numEdgesIn] = checkLocation + offsetBR;
            numEdgesIn += addBR;
            edgeList[numEdgesIn] = checkLocation + offsetBC;
            numEdgesIn += addBC;
            edgeList[numEdgesIn] = checkLocation + offsetBL;
            numEdgesIn += addBL;
            edgeList[numEdgesIn] = checkLocation + offsetLC;
            numEdgesIn += addLC;

            totalEdges += numEdgesIn-oldNum;
            sufficientCapacity = (numEdgesIn < edgeListCapacity-8);
        }
        *numEdgesOut = totalEdges;

        /* If we ran out of buffer, report error */
        status = (sufficientCapacity == 1U) ? VXLIB_SUCCESS : VXLIB_ERR_BUFFER_TOO_SMALL;
    }
    return (status);
}

VXLIB_STATUS VXLIB_edgeTracing_i8u_checkParams_cn(uint8_t edgeMap[],
                                                  VXLIB_bufParams2D_t * edgeMap_addr,
                                                  uint32_t edgeList[],
                                                  uint32_t edgeListCapacity,
                                                  uint32_t numEdgesIn,
                                                  uint32_t *numEdgesOut)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((edgeMap == NULL) || (edgeList == NULL) || (numEdgesOut == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((uint32_t)edgeMap_addr->stride_y < edgeMap_addr->dim_x) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(edgeMap_addr->data_type != VXLIB_UINT8) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((int32_t)edgeListCapacity < ((int32_t)numEdgesIn-8)) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    }
    return (status);
}

