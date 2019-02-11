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

#include "VXLIB_minMaxLoc_i8u.h"

CODE_SECTION(VXLIB_minMaxLoc_i8u,               ".text:optimized")
CODE_SECTION(VXLIB_minMaxLoc_i8u_findMinMaxVal, ".text:optimized")
CODE_SECTION(VXLIB_minMaxLoc_i8u_findMinMaxCnt, ".text:optimized")
CODE_SECTION(VXLIB_minMaxLoc_i8u_findMinMaxLoc, ".text:optimized")
CODE_SECTION(VXLIB_minMaxLoc_i8u_checkParams,   ".text:optimized")

static void VXLIB_minMaxLoc_i8u_findMinMaxVal(const uint8_t src[restrict],
                                            int32_t width,
                                            int64_t *pmin8,
                                            int64_t *pmax8);

static void VXLIB_minMaxLoc_i8u_findMinMaxCnt(const uint8_t src[restrict],
                                            int32_t width,
                                            int64_t min8,
                                            int64_t max8,
                                            uint32_t *minCount,
                                            uint32_t *maxCount);

static inline void VXLIB_minMaxLoc_i8u_findMinMaxLoc(const uint8_t src[restrict],
                                            uint32_t width,
                                            uint32_t height,
                                            uint32_t stride,
                                            int64_t min8,
                                            int64_t max8,
                                            uint32_t minCount,
                                            uint32_t maxCount,
                                            uint32_t minLoc[restrict],
                                            uint32_t maxLoc[restrict],
                                            uint16_t startX,
                                            uint16_t startY);

static void VXLIB_minMaxLoc_i8u_findMinMaxVal(const uint8_t src[restrict],
                                            int32_t width,
                                            int64_t *pmin8,
                                            int64_t *pmax8)
{
    int32_t    x;
    int64_t min8 = *pmin8;
    int64_t max8 = *pmax8;

    /* Case 1: SIMD of 8 pixels at a time */
    /* 1/8 = 0.125 cycles per pixel */
    for(x=0; x < (width / 8); x++) {
        int64_t src8 = _mem8_const(&src[x*8]);
        min8 = _dminu4(src8, min8);
        max8 = _dmaxu4(src8, max8);
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MINMAXLOC_I8U_ALIGNED8_WIDTHS)

    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 2 cycles per pixel */
    for(x*=8; x < width; x++) {
        uint64_t min8_tmp = 0xFFFFFFFFFFFFFF00U | src[x];
        int64_t max8_tmp = (int64_t)src[x];
        min8 = _dminu4((int64_t)min8_tmp, min8);
        max8 = _dmaxu4(max8_tmp, max8);
    }

#endif

    *pmin8 = min8;
    *pmax8 = max8;
    
    return;
}

static void VXLIB_minMaxLoc_i8u_findMinMaxCnt(const uint8_t src[restrict],
                                            int32_t width,
                                            int64_t min8,
                                            int64_t max8,
                                            uint32_t *minCount,
                                            uint32_t *maxCount)
{
    int32_t    x;
    uint32_t mincnt = *minCount;
    uint32_t maxcnt = *maxCount;

    /* Case 1: SIMD of 8 pixels at a time */
    /* 1/8 = 0.125 cycles per pixel */
    for(x=0; x < (width / 8); x++) {
        int64_t src8 = _mem8_const(&src[x*8]);
        mincnt += _bitc4(_dcmpeq4(src8, min8));
        maxcnt += _bitc4(_dcmpeq4(src8, max8));
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MINMAXLOC_I8U_ALIGNED8_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 1 cycles per pixel */
    for(x*=8; x < width; x++) {
        if((_loll(min8) & 0xffU) == src[x]) {
            mincnt++;
        }
        if((_loll(max8) & 0xffU) == src[x]) {
            maxcnt++;
        }
    }
#endif

    *minCount = mincnt;
    *maxCount = maxcnt;
    
    return;
}

static inline void VXLIB_minMaxLoc_i8u_findMinMaxLoc(const uint8_t src[restrict],
                                            uint32_t width,
                                            uint32_t height,
                                            uint32_t stride,
                                            int64_t min8,
                                            int64_t max8,
                                            uint32_t minCount,
                                            uint32_t maxCount,
                                            uint32_t minLoc[restrict],
                                            uint32_t maxLoc[restrict],
                                            uint16_t startX,
                                            uint16_t startY)
{
    uint32_t x, y, z;
    uint32_t mincnt_l, maxcnt_l;
    uint32_t mincnt = 0;
    uint32_t maxcnt = 0;

    /* Case 1: SIMD of 8 pixels at a time */
    for(y=0; y < height; y++) {
        for(x=0; x < (width / 8U); x++) {
            int64_t src8 = _mem8_const(&src[(y*stride) + (x*8U)]);
            mincnt_l = _dcmpeq4(src8, min8);
            maxcnt_l = _dcmpeq4(src8, max8);

            if((mincnt / 2U) < minCount) {
                z = 0;
                #pragma MUST_ITERATE(0,8,1)
                while(mincnt_l != 0) { 
                    if(((mincnt_l & 1U) != 0) && (mincnt < (minCount*2U))) {
                        minLoc[mincnt] = ((x*8U)+z)+(uint32_t)startX;
                        mincnt++;
                        minLoc[mincnt] = y+startY;
                        mincnt++;
                    }
                    mincnt_l >>= 1;
                    z++;
                }
            }

            if((maxcnt / 2U) < maxCount) {
                z = 0;
                #pragma MUST_ITERATE(0,8,1)
                while(maxcnt_l != 0) {
                    if(((maxcnt_l & 1U) != 0) && (maxcnt < (maxCount*2U))) {
                        maxLoc[maxcnt] = ((x*8U)+z)+startX;
                        maxcnt++;
                        maxLoc[maxcnt] = y+startY;
                        maxcnt++;
                    }
                    maxcnt_l >>= 1;
                    z++;
                }
            }
        }
#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MINMAXLOC_I8U_ALIGNED8_WIDTHS)
        /* Case 2: Process remaining pixels beyond multiple of 8 */
        for(x*=8U; x < width; x++) {

            if((mincnt / 2U) < minCount) {
                if((uint32_t)src[(y*stride) + x] == (_loll(min8) & 0xffU)) {
                    minLoc[mincnt] = x+startX;
                    mincnt++;
                    minLoc[mincnt] = y+startY;
                    mincnt++;
                }
            }

            if((maxcnt / 2U) < maxCount) {
                if((uint32_t)src[(y*stride) + x] == (_loll(max8) & 0xffU)) {
                    maxLoc[maxcnt] = x+startX;
                    maxcnt++;
                    maxLoc[maxcnt] = y+startY;
                    maxcnt++;
                }
            }
        }
#endif
        /* Early exit condition */
        if(((mincnt / 2U) >= minCount) && ((maxcnt / 2U) >= maxCount)) {
            break;
        }
    }

    return;
}

VXLIB_STATUS VXLIB_minMaxLoc_i8u(const uint8_t src[restrict],
                              const VXLIB_bufParams2D_t *src_addr,
                              uint8_t *pMinVal,
                              uint8_t *pMaxVal,
                              uint32_t *pMinCount,
                              uint32_t *pMaxCount,
                              size_t minLocCapacity,
                              size_t maxLocCapacity,
                              uint32_t minLoc[restrict],
                              uint32_t maxLoc[restrict],
                              uint16_t startX,
                              uint16_t startY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MINMAXLOC_I8U_CHECK_PARAMS)
    status = VXLIB_minMaxLoc_i8u_checkParams(src, src_addr, pMinVal, pMaxVal);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t min4, min2, min1, max4, max2, max1;

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MINMAXLOC_I16S_EQUAL_WIDTH_STRIDE)
        const uint8_t   *src_t;
#endif

        /**************************************************************/
        /** PASS 1: Find min/max values                              **/
        /**************************************************************/

        /* Replicate min/max value to 8 lanes */
        uint32_t  min = *pMinVal;
        uint32_t  max = *pMaxVal;
        uint32_t  origMin = min;
        uint32_t  origMax = max;
        uint32_t origMinCnt = 0, origMaxCnt = 0;
        uint32_t minCount = 0, maxCount = 0;
        int64_t min8 = _itoll((min << 24) | (min << 16) | (min << 8) | min,
                               (min << 24) | (min << 16) | (min << 8) | min);
        int64_t max8 = _itoll((max << 24) | (max << 16) | (max << 8) | max,
                               (max << 24) | (max << 16) | (max << 8) | max);

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MINMAXLOC_I8U_EQUAL_WIDTH_STRIDE)
        if(src_addr->dim_x == src_addr->stride_y)
#endif
        {
            VXLIB_minMaxLoc_i8u_findMinMaxVal(src, src_addr->dim_x * src_addr->dim_y, &min8, &max8);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MINMAXLOC_I8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src_addr->dim_y; y++ ) {

                src_t = (const uint8_t *)&src[y * src_addr->stride_y];

                VXLIB_minMaxLoc_i8u_findMinMaxVal(src_t, src_addr->dim_x, &min8, &max8);
            }
        }
#endif
        /* Reduce 8 lanes down to a single min and max value */
        min4 = _minu4(_hill(min8), _loll(min8));
        min2 = _minu4(min4, min4 >> 16);
        min1 = _minu4(min2, min2 >> 8) & 0xffU;

        max4 = _maxu4(_hill(max8), _loll(max8));
        max2 = _maxu4(max4, max4 >> 16);
        max1 = _maxu4(max2, max2 >> 8) & 0xffU;

        *pMinVal = (uint8_t)min1;
        *pMaxVal = (uint8_t)max1;

        /**************************************************************/
        /** PASS 2: (Optional) Find min/max counts                   **/
        /**************************************************************/

        /* If the optional parameters for min or max count are available ... */
        if((pMinCount != NULL) || (pMaxCount != NULL)) {

            minCount = 0;
            maxCount = 0;

            /* Starting counters are taken from input if the optional parameter
             * is available and the new min/max values are matching the values
             * given on the input (perhaps from a previous block).
             * This allows for this function to be called on multiple blocks
             * of an image iteratively without externally keeping track of the
             * values/counts during processing */
            if((pMinCount != NULL) && (origMin == min1)) {
                minCount = *pMinCount;
                origMinCnt = minCount;
            }
            if((pMaxCount != NULL) && (origMax == max1)) {
                maxCount = *pMaxCount;
                origMaxCnt = maxCount;
            }

            min8 = _itoll((min1 << 24) | (min1 << 16) | (min1 << 8) | min1,
                          (min1 << 24) | (min1 << 16) | (min1 << 8) | min1);
            max8 = _itoll((max1 << 24) | (max1 << 16) | (max1 << 8) | max1,
                          (max1 << 24) | (max1 << 16) | (max1 << 8) | max1);

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MINMAXLOC_I8U_EQUAL_WIDTH_STRIDE)
            if(src_addr->dim_x == src_addr->stride_y)
#endif
            {
                VXLIB_minMaxLoc_i8u_findMinMaxCnt(src, src_addr->dim_x * src_addr->dim_y, min8, max8, &minCount, &maxCount);
            }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MINMAXLOC_I8U_EQUAL_WIDTH_STRIDE)
            else {

                int32_t    y;

                for( y=0; y < src_addr->dim_y; y++ ) {

                    src_t = (const uint8_t *)&src[y * src_addr->stride_y];

                    VXLIB_minMaxLoc_i8u_findMinMaxCnt(src_t, src_addr->dim_x, min8, max8, &minCount, &maxCount);
                }
            }
#endif
            if(pMinCount != NULL) {
                *pMinCount = minCount;
            }
            if(pMaxCount != NULL) {
                *pMaxCount = maxCount;
            }
        

            /**************************************************************/
            /** PASS 3: (Optional) Find min/max locations                **/
            /**************************************************************/

            /* If the optional parameters for min or max locations are available AND
             * if one of the min/max counts have changed during this block iteration ...*/
            if(((minLoc != NULL) && ((origMin != min1) || (origMinCnt != minCount))) ||
               ((maxLoc != NULL) && ((origMax != max1) || (origMaxCnt != maxCount)))) {

                /* Initialize local variables assuming starting at beginning of buffers */
                uint32_t *pMinLoc = minLoc;
                uint32_t *pMaxLoc = maxLoc;
                int32_t minLocCount = (minLocCapacity < minCount) ? minLocCapacity : minCount;
                int32_t maxLocCount = (maxLocCapacity < maxCount) ? maxLocCapacity : maxCount;

                /* Starting location offsets pointers are adjusted if the new min/max values
                 * are matching the values given on the input (perhaps from a previous block).
                 * This allows for this function to be called on multiple blocks
                 * of an image iterativly without externally keeping track of the
                 * locations during processing */
                if((minLoc != NULL) && (origMin == min1)) {
                    pMinLoc = &minLoc[origMinCnt*2U];
                    minLocCount -= (int32_t)origMinCnt;
                    if(minLocCount < 0)
                    {
                        minLocCount = 0;
                    }
                }
                if((maxLoc != NULL) && (origMax == max1)) {
                    pMaxLoc = &maxLoc[origMaxCnt*2U];
                    maxLocCount -= (int32_t)origMaxCnt;
                    if(maxLocCount < 0)
                    {
                        maxLocCount = 0;
                    }
                }

                if((minLocCount > 0) || (maxLocCount > 0)) {
                    VXLIB_minMaxLoc_i8u_findMinMaxLoc(src, src_addr->dim_x, src_addr->dim_y, src_addr->stride_y,
                                                   min8, max8, (uint32_t)minLocCount, (uint32_t)maxLocCount, pMinLoc, pMaxLoc, startX, startY);
                }
            }
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MINMAXLOC_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MINMAXLOC_I8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_minMaxLoc_i8u_checkParams(const uint8_t src[],
                                          const VXLIB_bufParams2D_t *src_addr,
                                          const uint8_t *pMinVal,
                                          const uint8_t *pMaxVal)
{
    VXLIB_STATUS    status;

    if((src == NULL) || (pMinVal == NULL) || (pMaxVal == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if(src_addr->stride_y < src_addr->dim_x) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if( src_addr->data_type != VXLIB_UINT8 ) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_MINMAXLOC_I8U_EQUAL_WIDTH_STRIDE)
    else if(src_addr->dim_x != src_addr->stride_y) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_MINMAXLOC_I8U_ALIGNED8_WIDTHS)
    else if((src_addr->dim_x % 8U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }

    return (status);
}

#endif
