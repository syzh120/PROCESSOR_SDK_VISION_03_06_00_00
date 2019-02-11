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

#include "VXLIB_doubleThreshold_i16u_i8u_cn.h"

CODE_SECTION(VXLIB_doubleThreshold_i16u_i8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_doubleThreshold_i16u_i8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_doubleThreshold_i16u_i8u_cn(uint16_t src_mag[],
                                               VXLIB_bufParams2D_t * src_mag_addr,
                                               uint8_t edgeMap[],
                                               VXLIB_bufParams2D_t * edgeMap_addr,
                                               uint16_t edgeMapLineOffset,
                                               uint32_t edgeList[],
                                               uint32_t edgeListCapacity,
                                               uint32_t *numEdges,
                                               uint32_t startPosition,
                                               uint32_t loThreshold,
                                               uint32_t hiThreshold)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_doubleThreshold_i16u_i8u_checkParams_cn(src_mag, src_mag_addr, edgeMap, edgeMap_addr, edgeMapLineOffset, edgeList, edgeListCapacity, numEdges, startPosition, loThreshold, hiThreshold);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t numItems = 0;
        uint32_t x, y;
        
        for(y=0; y<edgeMap_addr->dim_y; y++) {
            for(x=0; x<edgeMap_addr->dim_x; x++) {
                uint16_t norm = src_mag[y*(src_mag_addr->stride_y/2)+x];
                uint8_t edge = edgeMap[y*(edgeMap_addr->stride_y)+x];
                if(edge) {
                    if(norm <= loThreshold) {
                        edge = 0;
                    } else if (norm > hiThreshold) {
                        edge = 255;
                        edgeList[numItems] = y*(edgeMapLineOffset)+x+startPosition;
                        numItems++;
                        if(numItems >= edgeListCapacity) {
                            status = VXLIB_ERR_BUFFER_TOO_SMALL;
                            return status;
                        }
                    }
                    edgeMap[y*(edgeMap_addr->stride_y)+x] = edge;
                }
            }
        }
        *numEdges = numItems;
    }
    return (status);
}

VXLIB_STATUS VXLIB_doubleThreshold_i16u_i8u_checkParams_cn(uint16_t src_mag[],
                                                           VXLIB_bufParams2D_t * src_mag_addr,
                                                           uint8_t edgeMap[],
                                                           VXLIB_bufParams2D_t * edgeMap_addr,
                                                           uint16_t edgeMapLineOffset,
                                                           uint32_t edgeList[],
                                                           uint32_t edgeListCapacity,
                                                           uint32_t *numEdges,
                                                           uint32_t startPosition,
                                                           uint32_t loThreshold,
                                                           uint32_t hiThreshold)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((edgeMap == NULL) || (src_mag == NULL) || (edgeList == NULL) || (edgeListCapacity == 0)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((edgeMap_addr->dim_x > src_mag_addr->dim_x) ||
               (edgeMap_addr->dim_y > src_mag_addr->dim_y) ||
               ((uint32_t)src_mag_addr->stride_y < src_mag_addr->dim_x*2) ||
               ((uint32_t)edgeMap_addr->stride_y < edgeMap_addr->dim_x) ||
               ((uint32_t)edgeMapLineOffset < edgeMap_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_mag_addr->data_type != VXLIB_UINT16) ||
               (edgeMap_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(loThreshold > hiThreshold) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    return (status);
}

