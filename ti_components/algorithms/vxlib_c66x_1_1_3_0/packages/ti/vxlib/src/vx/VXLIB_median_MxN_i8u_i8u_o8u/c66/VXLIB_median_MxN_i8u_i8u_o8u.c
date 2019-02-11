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

#include "VXLIB_median_MxN_i8u_i8u_o8u.h"

CODE_SECTION(VXLIB_median_MxN_i8u_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_median_MxN_i8u_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_median_MxN_i8u_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_median_MxN_i8u_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    const uint8_t mask[restrict],
                                    const uint16_t offsetList[restrict],
                                    uint8_t cnt,
                                    int64_t scratch[restrict],
                                    int32_t outWidth,
                                    int32_t maskWidth,
                                    int32_t maskHeight);

static void VXLIB_median_MxN_i8u_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    const uint8_t mask[restrict],
                                    const uint16_t offsetList[restrict],
                                    uint8_t cnt,
                                    int64_t scratch[restrict],
                                    int32_t outWidth,
                                    int32_t maskWidth,
                                    int32_t maskHeight)
{
    int32_t x, j, i;
    uint32_t offsetImage;

    /* Case 1: SIMD of 16 pixels at a time */
    /* 4/16*maskTrueCnt + 2/16*(maskTrueCnt-1)*(maskTrueCnt-1) cycles per output pixel */
    for(x=0; x < (outWidth/16); x++) {

        offsetImage = (uint32_t)x*16U;

        /* Fetch input pixels into scratch buffer, according to mask */
        /* 4/16 * cnt + 12 cycles */
        #pragma MUST_ITERATE(2, 81, );
        for(i=0; i < (int32_t)cnt; i++) {

            /* Fetch 16 input pixels for each mask value */
            scratch[(i*2)+0] = _mem8(&src[offsetImage+(uint32_t)offsetList[i]]);
            scratch[(i*2)+1] = _mem8(&src[offsetImage+(uint32_t)offsetList[i]+8U]);
        }

        /* Sort the values in window from largest to smallest */
        for(j=0; j < ((int32_t)cnt-1); j++) {

            int64_t scratch8_0 = scratch[0];
            int64_t scratch8_1 = scratch[1];

            /* 2/16 * (cnt-1) + 8 cycles */
            for(i=0; i < ((int32_t)cnt-1); i++) {
                int64_t min8_0 = _dminu4(scratch[(i*2)+2], scratch8_0);
                int64_t min8_1 = _dminu4(scratch[(i*2)+3], scratch8_1);
                int64_t max8_0 = _dmaxu4(scratch[(i*2)+2], scratch8_0);
                int64_t max8_1 = _dmaxu4(scratch[(i*2)+3], scratch8_1);
                scratch[(i*2)+0] = max8_0;
                scratch[(i*2)+1] = max8_1;
                scratch8_0 = min8_0;
                scratch8_1 = min8_1;
            }

            scratch[(i*2)+0] = scratch8_0;
            scratch[(i*2)+1] = scratch8_1;

        }

        /* Write out the results of the median of the full structuring element patch */
        _mem8(&dst[x*16])     = scratch[cnt & 0xFEU];
        _mem8(&dst[(x*16)+8]) = scratch[(cnt & 0xFEU) + 1U];
    }

#if (!defined(VXLIB_ALIGNED16_WIDTHS) && !defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_ALIGNED16_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 16 */
    /* 2*maskWidth*maskHeight cycles per output pixel (3x3 = 27; 5x5 = 75) cycle per pixel */
    for(x*=16; x < outWidth; x++) {

        offsetImage = (uint32_t)x;
        j = 0;

        for(i=0; i < (int32_t)cnt; i++) {

            /* Fetch 1 input pixels for each mask value */
            _amem4(&scratch[i])   = (uint32_t)src[offsetImage+(uint32_t)offsetList[i]];
        }

        /* Sort the values in window from largest to smallest */
        for(j=0; j < ((int32_t)cnt-1); j++) {

            uint32_t scratch0 = _amem4(&scratch[0]);

            for(i=0; i < ((int32_t)cnt-1); i++) {
                uint32_t min4_0 = _minu4(_amem4(&scratch[i+1]), scratch0);
                uint32_t max4_0 = _maxu4(_amem4(&scratch[i+1]), scratch0);
                _amem4(&scratch[i]) = max4_0;
                scratch0 = min4_0;
            }

            _amem4(&scratch[i]) = scratch0;
        }

        /* Write out the results of the min of the full structuring element patch */
        dst[x] = (uint8_t)scratch[cnt/2U];
    }
#endif
}

VXLIB_STATUS VXLIB_median_MxN_i8u_i8u_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            const uint8_t mask[restrict],
                            const VXLIB_bufParams2D_t *mask_addr,
                            int64_t scratch[restrict],
                            uint32_t scratchSize)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_median_MxN_i8u_i8u_o8u_checkParams(src, src_addr, dst, dst_addr, mask, mask_addr, scratch, scratchSize);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t i, j, cnt = 0;
        uint16_t offsetList[9*9];

        /* Scan through the mask and extract the offsets of the TRUE values */
        /* 2 cycles per mask value */
        for(j=0; j<mask_addr->dim_y; j++) {
            for(i=0; i<mask_addr->dim_x; i++){
                if(mask[(j*mask_addr->dim_x)+i] != 0) {
                    offsetList[cnt] = ((uint16_t)j*(uint16_t)src_addr->stride_y)+(uint16_t)i;
                    cnt++;
                }
            }
        }

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_median_MxN_i8u_i8u_o8u_core(src, dst, mask, offsetList, (uint8_t)cnt, scratch,
                                              (dst_addr->stride_y * dst_addr->dim_y) - (mask_addr->dim_x-1),
                                              mask_addr->dim_x, mask_addr->dim_y);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-(mask_addr->dim_x-1)));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_median_MxN_i8u_i8u_o8u_core(src_t, dst_t, mask, offsetList, (uint8_t)cnt, scratch,
                                                  width, (int32_t)mask_addr->dim_x, (int32_t)mask_addr->dim_y);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_median_MxN_i8u_i8u_o8u_checkParams(const uint8_t src[restrict],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst[restrict],
                                           const VXLIB_bufParams2D_t *dst_addr,
                                           const uint8_t mask[restrict],
                                           const VXLIB_bufParams2D_t *mask_addr,
                                           const int64_t scratch[restrict],
                                           uint32_t scratchSize)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL) || (mask == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x < dst_addr->dim_x) ||
               ((src_addr->dim_y-(mask_addr->dim_y-1)) !=  dst_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < dst_addr->dim_x) ||
               (mask_addr->stride_y != mask_addr->dim_x) ||
               (mask_addr->dim_x < 1) ||
               (mask_addr->dim_y < 1) ||
               (mask_addr->dim_x > 9) ||
               (mask_addr->dim_y > 9)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8) ||
               (mask_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if (defined(VXLIB_ALIGNED16_WIDTHS) || defined(VXLIB_MEDIAN_MXN_I8U_I8U_O8U_ALIGNED16_WIDTHS))
    else if((dst_addr->dim_x % 16U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else if(((uint32_t)scratch % 8U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
    else {

        int32_t i, j, cnt = 0;

        /* Scan through the mask and count the TRUE values */
        for(j=0; j<mask_addr->dim_y; j++) {
            for(i=0; i<mask_addr->dim_x; i++){
                if(mask[(j*mask_addr->dim_x)+i] != 0) {
                    cnt++;
                }
            }
        }

        if( (int32_t)scratchSize < (cnt*2*8) ) {
            status = VXLIB_ERR_BUFFER_TOO_SMALL;
        } else {
            status = VXLIB_SUCCESS;
        }
    }
    return (status);
}

#endif
