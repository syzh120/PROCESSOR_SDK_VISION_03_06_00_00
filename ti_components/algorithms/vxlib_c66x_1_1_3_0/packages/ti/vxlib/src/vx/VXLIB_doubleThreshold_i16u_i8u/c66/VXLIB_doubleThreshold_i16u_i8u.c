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

#include "VXLIB_doubleThreshold_i16u_i8u.h"

CODE_SECTION(VXLIB_doubleThreshold_i16u_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_doubleThreshold_i16u_i8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_doubleThreshold_i16u_i8u_checkParams,  ".text:optimized")

static VXLIB_STATUS VXLIB_doubleThreshold_i16u_i8u_core(const uint16_t srcMag[restrict],
                                                         uint8_t edgeMap[restrict],
                                                         int32_t width,
                                                         uint32_t edgeList[restrict],
                                                         uint32_t edgeListCapacity,
                                                         uint32_t *numEdges,
                                                         uint32_t startPosition,
                                                         uint32_t loThreshold,
                                                         uint32_t hiThreshold);

static VXLIB_STATUS VXLIB_doubleThreshold_i16u_i8u_core(const uint16_t srcMag[restrict],
                                                         uint8_t edgeMap[restrict],
                                                         int32_t width,
                                                         uint32_t edgeList[restrict],
                                                         uint32_t edgeListCapacity,
                                                         uint32_t *numEdges,
                                                         uint32_t startPosition,
                                                         uint32_t loThreshold,
                                                         uint32_t hiThreshold)
{
    VXLIB_STATUS    status;
    uint32_t        x;
    uint32_t     numItems = 0;
    uint32_t     sufficientCapacity = 1U;
    const int64_t sub64 = 0x7fff7fff7fff7fff;

    uint32_t    lo2 = _pack2(loThreshold, loThreshold);
    int64_t     lo4 = _dsub2(_itoll(lo2, lo2), sub64);
    uint32_t    hi2 = _pack2(hiThreshold, hiThreshold);
    int64_t     hi4 = _dsub2(_itoll(hi2, hi2), sub64);

    /* Case 1: SIMD of 4 pixels at a time */
    /* 9/4 = 2.25 cycles per pixel */
    /* Note: Loop-carried dependency=9 due to code that writes out list.
     *       Without this, I can achieve 3/4 cycles per pixel */
    for( x=0; x < ((uint32_t)width / 4U); x++ ) {
        uint32_t i;

        /* Fetch 4 contiguous magnitudes and subtract 0x7FFF from each */
        int64_t  mag4 = _dsub2(_mem8_const(&srcMag[x*4U]), sub64) ;

        /* Fetch 4 contiguous edge values from non-max suppression output
         * (value is either 0 or 127) */
        uint32_t value4 = _mem4_const(&edgeMap[x*4U]);

        /* Set flag if the edge is non-zero */
        uint32_t isEdge = _cmpgtu4(value4, 0);

        /* Set flag if magnitude is greater than low threshold */
        uint32_t aboveLow4  = _xpnd4(_dcmpgt2(mag4, lo4));

        /* Set flag if magnitude is greater than high threshold */
        uint32_t aboveHigh4 = _dcmpgt2(mag4, hi4);

        /* Set flag if should promote to strong edge */
        uint32_t addEdge4 = aboveHigh4 & isEdge;

        /* Make a value of "128" for each strong edge */
        uint32_t addEdge4_plus = _xpnd4(addEdge4) & 0x80808080U;

        /* Compute new value
         * If value was 127 and is above high threshold, then it is now 255
         * If value was 127 and is above low threshold, then it is still 127
         * If value was 127 and is below low threshold, then it is now 0
         * If value was   0, then it is still 0 */
        uint32_t sum4 = value4 | addEdge4_plus;
        uint32_t result4 = sum4 & aboveLow4;

        /* Set flag if there is still room to add edges to buffer */
        uint32_t newEdges = _bitc4(addEdge4);
        sufficientCapacity = (uint32_t)((numItems + newEdges) <= edgeListCapacity);

        /* For each of the four pixels, add only strong edges to list */
        for(i=0; i < 4U; i++) {
            edgeList[numItems] = startPosition + (x*4U) + i;
            numItems += ((addEdge4 & (uint32_t)1) & sufficientCapacity);
            addEdge4>>=1;
        }

        /* Output the updated edge map */
        _mem4(&edgeMap[x*4U]) = result4;
    }

#if !defined(VXLIB_ALIGNED4_WIDTHS) && !defined(VXLIB_DOUBLETHRESHOLD_I16U_I8U_ALIGNED4_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 4 */
    /* 3 cycles per pixel */
    for( x*=4U; x < (uint32_t)width; x++ ) {

        /* Set flag if magnitude is greater than low threshold */
        int16_t aboveLowBool = (int16_t)(srcMag[x] > (uint16_t)loThreshold);
        uint8_t aboveLow=(uint8_t)aboveLowBool;

        /* Set flag if magnitude is greater than high threshold */
        int16_t aboveHighBool = (int16_t)(srcMag[x] > (uint16_t)hiThreshold);
        uint8_t aboveHigh=(uint8_t)aboveHighBool;

        /* Fetch the edge value from non-max suppression output */
        uint8_t value = edgeMap[x];

        /* Set flag if should promote to strong edge */
        uint8_t addEdge  = value & aboveHigh;

        /* Set flag if there is still room to add edges to buffer */
        sufficientCapacity = (uint32_t)(numItems < edgeListCapacity);

        /* Compute new value
         * If value was 127 and is above high threshold, then it is now 255
         * If value was 127 and is above low threshold, then it is still 127
         * If value was 127 and is below low threshold, then it is now 0
         * If value was   0, then it is still 0 */
        value  = (value + (addEdge * 128U)) * aboveLow;

        /* Update edge map and edge list */
        edgeMap[x]=value;
        edgeList[numItems] = (uint32_t)startPosition + x;
        numItems += (addEdge & sufficientCapacity);
    }
#endif

    /* Return number of points added to list */
    *numEdges = numItems;

    /* If we ran out of buffer, report error */
    status = (sufficientCapacity == 1U) ? VXLIB_SUCCESS : VXLIB_ERR_BUFFER_TOO_SMALL;

    return status;
}

VXLIB_STATUS VXLIB_doubleThreshold_i16u_i8u(const uint16_t src_mag[restrict],
                                            const VXLIB_bufParams2D_t * src_mag_addr,
                                            uint8_t edgeMap[restrict],
                                            const VXLIB_bufParams2D_t * edgeMap_addr,
                                            uint16_t edgeMapLineOffset,
                                            uint32_t edgeList[restrict],
                                            uint32_t edgeListCapacity,
                                            uint32_t *numEdges,
                                            uint32_t startPosition,
                                            uint32_t loThreshold,
                                            uint32_t hiThreshold)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_DOUBLETHRESHOLD_I16U_I8U_CHECK_PARAMS)
    status = VXLIB_doubleThreshold_i16u_i8u_checkParams(src_mag, src_mag_addr, edgeMap, edgeMap_addr, edgeMapLineOffset, edgeList, edgeListCapacity, numEdges, startPosition, loThreshold, hiThreshold);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    y;
        uint32_t numItems = 0;
        uint32_t localSize = 0;

        for( y=0; y < (int32_t)edgeMap_addr->dim_y; y++ ) {
            const uint16_t  *src_mag_t = (const uint16_t *)&src_mag[ y * (src_mag_addr->stride_y / 2) ];
            uint8_t          *edgeMap_t  = (uint8_t *)&edgeMap[ y * edgeMap_addr->stride_y];
            uint32_t         internalStart = ((uint32_t)y * (uint32_t)edgeMapLineOffset) + startPosition;
            uint32_t         *edgeList_t  = (uint32_t *)&edgeList[ numItems ];
            uint32_t         localCapacity = edgeListCapacity-numItems;

            status = VXLIB_doubleThreshold_i16u_i8u_core(src_mag_t, edgeMap_t, (int32_t)edgeMap_addr->dim_x, edgeList_t, localCapacity, &localSize, internalStart, loThreshold, hiThreshold );
            numItems += localSize;
        }
        *numEdges = numItems;
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_DOUBLETHRESHOLD_I16U_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_DOUBLETHRESHOLD_I16U_I8U_CHECK_PARAMS))

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
                                                        uint32_t hiThreshold)
{
    VXLIB_STATUS    status;

    if((edgeMap == NULL) || (src_mag == NULL) || (edgeList == NULL) ||
       (numEdges == NULL) || (edgeListCapacity == 0)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((edgeMap_addr->dim_x > src_mag_addr->dim_x) ||
               (edgeMap_addr->dim_y > src_mag_addr->dim_y) ||
               ((uint32_t)src_mag_addr->stride_y < (src_mag_addr->dim_x*2U)) ||
               ((uint32_t)edgeMap_addr->stride_y < edgeMap_addr->dim_x) ||
               ((uint32_t)edgeMapLineOffset < edgeMap_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_mag_addr->data_type != VXLIB_UINT16) ||
               (edgeMap_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(loThreshold > hiThreshold) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_ALIGNED4_WIDTHS) || defined(VXLIB_DOUBLETHRESHOLD_I16U_I8U_ALIGNED4_WIDTHS)
    else if((edgeMap_addr->dim_x % 4U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

