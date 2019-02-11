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

#include "VXLIB_gaussian_5x5_br_i8u_o8u.h"

#define CONV_SIZE 5

CODE_SECTION(VXLIB_gaussian_5x5_br_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_gaussian_5x5_br_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_gaussian_5x5_br_i8u_o8u_checkParams,  ".text:optimized")

static inline void VXLIB_gaussian_5x5_br_i8u_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  int32_t innerMax,
                                  uint8_t shift,
                                  int16_t startX,
                                  int32_t s0,
                                  int32_t s1,
                                  int32_t s2,
                                  int32_t s3,
                                  int32_t s4);

static inline void VXLIB_gaussian_5x5_br_i8u_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  int32_t innerMax,
                                  uint8_t shift,
                                  int16_t startX,
                                  int32_t s0,
                                  int32_t s1,
                                  int32_t s2,
                                  int32_t s3,
                                  int32_t s4)
{
    int32_t x;

    int64_t mask_ones  = 0x0101010101010101;
    int64_t mask_fours = 0x0404040404040404;
    int64_t mask_sixes = 0x0606060606060606;

    int64_t mask_r0_0 = 0x0004000600040001;
    int64_t mask_r0_1 = 0x0006000400010000;

    int64_t r0, r1, r2, r3, r4;
    __x128_t r0x, r1x, r2x, r3x, r4x;
    int64_t c3210_01, c3210_23, c3210_4, c3210;
    int64_t c7654_01, c7654_23, c7654_4, c7654;
    int64_t c5432;
    uint32_t out0, out1, out2, out3, out10, out32;
    uint32_t c4;
    uint32_t r0_10, r1_10, r2_10, r3_10, r4_10;

    /* Case 1: Left border */
    /* 8 cycle per pixel */
    for(x=startX; x < 2; x++) {

        /* Left border - 2 */
        if(x==0) {
            r0_10 = _mem2_const(&src[(srcStride*s0) + x]);
            r1_10 = _mem2_const(&src[(srcStride*s1) + x]);
            r2_10 = _mem2_const(&src[(srcStride*s2) + x]);
            r3_10 = _mem2_const(&src[(srcStride*s3) + x]);
            r4_10 = _mem2_const(&src[(srcStride*s4) + x]);

            r0_10 = (r0_10 << 16) | ((r0_10 & 0xffU) << 8) | (r0_10 & 0xffU);
            r1_10 = (r1_10 << 16) | ((r1_10 & 0xffU) << 8) | (r1_10 & 0xffU);
            r2_10 = (r2_10 << 16) | ((r2_10 & 0xffU) << 8) | (r2_10 & 0xffU);
            r3_10 = (r3_10 << 16) | ((r3_10 & 0xffU) << 8) | (r3_10 & 0xffU);
            r4_10 = (r4_10 << 16) | ((r4_10 & 0xffU) << 8) | (r4_10 & 0xffU);

        /* Left border - 1 */
        } else {
            r0_10 = _mem4_const(&src[(srcStride*s0)]);
            r1_10 = _mem4_const(&src[(srcStride*s1)]);
            r2_10 = _mem4_const(&src[(srcStride*s2)]);
            r3_10 = _mem4_const(&src[(srcStride*s3)]);
            r4_10 = _mem4_const(&src[(srcStride*s4)]);

            r0_10 = (r0_10 << 8) | (r0_10 & 0xffU);
            r1_10 = (r1_10 << 8) | (r1_10 & 0xffU);
            r2_10 = (r2_10 << 8) | (r2_10 & 0xffU);
            r3_10 = (r3_10 << 8) | (r3_10 & 0xffU);
            r4_10 = (r4_10 << 8) | (r4_10 & 0xffU);
        }

        /* Read 5 bytes from each of the 5 lines */
        r0 = _itoll((uint32_t)src[(srcStride*s0) + x + 2], r0_10);
        r1 = _itoll((uint32_t)src[(srcStride*s1) + x + 2], r1_10);
        r2 = _itoll((uint32_t)src[(srcStride*s2) + x + 2], r2_10);
        r3 = _itoll((uint32_t)src[(srcStride*s3) + x + 2], r3_10);
        r4 = _itoll((uint32_t)src[(srcStride*s4) + x + 2], r4_10);
    
        /* Apply the vertical mask */
        r0x = _dmpyu4(r0, mask_ones);
        r1x = _dmpyu4(r1, mask_fours);
        r2x = _dmpyu4(r2, mask_sixes);
        r3x = _dmpyu4(r3, mask_fours);
        r4x = _dmpyu4(r4, mask_ones);

        /* Sum each column for all 8 columns */
        c3210_01 = _dadd2(_lo128(r0x), _lo128(r1x));
        c3210_23 = _dadd2(_lo128(r2x), _lo128(r3x));
        c3210_4  = _dadd2(_lo128(r4x), c3210_01);
        c3210    = _dadd2(c3210_23, c3210_4);
        c4       = _get32_128(r0x,2U) + _get32_128(r1x,2U) +
                   _get32_128(r2x,2U) + _get32_128(r3x,2U) +
                   _get32_128(r4x,2U);

        /* Apply horizontal mask to sums using dot product, and right shift */
        out0 = ( (uint32_t)_dotp4h(c3210, mask_r0_0) + c4) >> shift;
        dst[x-startX] = (uint8_t)out0;
    }

    /* Case 2: SIMD of 4 output pixels at a time (not border) */
    /* 7/4 = 1.75 cycles per pixel */
    /* x in this loop will represent the left most pixel index in the src image needed to read for each output */
    for(x=x-2; x < (innerMax - 3); x+=4) {

        /* Read 8 bytes from each of the 5 lines */
        r0 = _mem8_const(&src[(srcStride*s0) + x]);
        r1 = _mem8_const(&src[(srcStride*s1) + x]);
        r2 = _mem8_const(&src[(srcStride*s2) + x]);
        r3 = _mem8_const(&src[(srcStride*s3) + x]);
        r4 = _mem8_const(&src[(srcStride*s4) + x]);

        /* Apply the vertical mask */
        r0x = _dmpyu4(r0, mask_ones);
        r1x = _dmpyu4(r1, mask_fours);
        r2x = _dmpyu4(r2, mask_sixes);
        r3x = _dmpyu4(r3, mask_fours);
        r4x = _dmpyu4(r4, mask_ones);

        /* Sum each column for all 8 columns */
        c3210_01 = _dadd2(_lo128(r0x), _lo128(r1x));
        c3210_23 = _dadd2(_lo128(r2x), _lo128(r3x));
        c3210_4  = _dadd2(_lo128(r4x), c3210_01);
        c3210    = _dadd2(c3210_23, c3210_4);
        c7654_01 = _dadd2(_hi128(r0x), _hi128(r1x));
        c7654_23 = _dadd2(_hi128(r2x), _hi128(r3x));
        c7654_4  = _dadd2(_hi128(r4x), c7654_01);
        c7654    = _dadd2(c7654_23, c7654_4);
                       
        /* Repack column sums */
        c5432 = _itoll(_loll(c7654), _hill(c3210));

        /* Apply horizontal mask to sums using dot product */
        out0 =  (uint32_t)_dotp4h(c3210, mask_r0_0) +  (_loll(c7654) & 0xffffU);
        out1 =  (uint32_t)_dotp4h(c3210, mask_r0_1) + ((_loll(c7654) & 0xffffU) << 2) + (_loll(c7654) >> 16);
        out2 =  (uint32_t)_dotp4h(c5432, mask_r0_0) +  (_hill(c7654) & 0xffffU);
        out3 =  (uint32_t)_dotp4h(c5432, mask_r0_1) + ((_hill(c7654) & 0xffffU) << 2) + (_hill(c7654) >> 16);

        /* Pack output appropriatly with right shift and write to memory */
        out10 = _shru2(_pack2(out1, out0), (uint32_t)shift);
        out32 = _shru2(_pack2(out3, out2), (uint32_t)shift);
        _mem4(&dst[(x+2)-startX]) = _spacku4((int32_t)out32, (int32_t)out10);
    }

    /* Case 3: Process remaining pixels beyond multiple of 4 */
    /* 8 cycle per pixel */
    for(; x < innerMax; x++) {

        /* Read 5 bytes from each of the 5 lines */
        r0 = _itoll((uint32_t)src[(srcStride*s0) + x + 4], _mem4_const(&src[(srcStride*s0) + x]));
        r1 = _itoll((uint32_t)src[(srcStride*s1) + x + 4], _mem4_const(&src[(srcStride*s1) + x]));
        r2 = _itoll((uint32_t)src[(srcStride*s2) + x + 4], _mem4_const(&src[(srcStride*s2) + x]));
        r3 = _itoll((uint32_t)src[(srcStride*s3) + x + 4], _mem4_const(&src[(srcStride*s3) + x]));
        r4 = _itoll((uint32_t)src[(srcStride*s4) + x + 4], _mem4_const(&src[(srcStride*s4) + x]));

        /* Apply the vertical mask */
        r0x = _dmpyu4(r0, mask_ones);
        r1x = _dmpyu4(r1, mask_fours);
        r2x = _dmpyu4(r2, mask_sixes);
        r3x = _dmpyu4(r3, mask_fours);
        r4x = _dmpyu4(r4, mask_ones);

        /* Sum each column for all 8 columns */
        c3210_01 = _dadd2(_lo128(r0x), _lo128(r1x));
        c3210_23 = _dadd2(_lo128(r2x), _lo128(r3x));
        c3210_4  = _dadd2(_lo128(r4x), c3210_01);
        c3210    = _dadd2(c3210_23, c3210_4);
        c4       = _get32_128(r0x,2U) + _get32_128(r1x,2U) +
                   _get32_128(r2x,2U) + _get32_128(r3x,2U) +
                   _get32_128(r4x,2U);

        /* Apply horizontal mask to sums using dot product, and right shift */
        out0 = ( (uint32_t)_dotp4h(c3210, mask_r0_0) + c4) >> shift;
        dst[(x+2)-startX] = (uint8_t)out0;
    }

    /* Case 4: Process right border pixels */
    /* 8 cycle per pixel */
    for(; x < ((outWidth+startX)-2); x++) {

        uint32_t r0_4, r1_4, r2_4, r3_4, r4_4;

        /* Right border + 1 */
        if(x==((outWidth+startX)-4)) {
            r0_10 = _mem4_const(&src[(srcStride*s0) + x]);
            r1_10 = _mem4_const(&src[(srcStride*s1) + x]);
            r2_10 = _mem4_const(&src[(srcStride*s2) + x]);
            r3_10 = _mem4_const(&src[(srcStride*s3) + x]);
            r4_10 = _mem4_const(&src[(srcStride*s4) + x]);

            r0_4 = r0_10 >> 24;
            r1_4 = r1_10 >> 24;
            r2_4 = r2_10 >> 24;
            r3_4 = r3_10 >> 24;
            r4_4 = r4_10 >> 24;

        /* Right border + 2 */
        } else {
            r0_10 = _mem2_const(&src[(srcStride*s0) + x]);
            r1_10 = _mem2_const(&src[(srcStride*s1) + x]);
            r2_10 = _mem2_const(&src[(srcStride*s2) + x]);
            r3_10 = _mem2_const(&src[(srcStride*s3) + x]);
            r4_10 = _mem2_const(&src[(srcStride*s4) + x]);

            r0_4 = (uint32_t)src[(srcStride*s0) + x + 2];
            r1_4 = (uint32_t)src[(srcStride*s1) + x + 2];
            r2_4 = (uint32_t)src[(srcStride*s2) + x + 2];
            r3_4 = (uint32_t)src[(srcStride*s3) + x + 2];
            r4_4 = (uint32_t)src[(srcStride*s4) + x + 2];

            r0_10 |= (r0_4 << 24) | (r0_4 << 16);
            r1_10 |= (r1_4 << 24) | (r1_4 << 16);
            r2_10 |= (r2_4 << 24) | (r2_4 << 16);
            r3_10 |= (r3_4 << 24) | (r3_4 << 16);
            r4_10 |= (r4_4 << 24) | (r4_4 << 16);
        }

        /* Read 5 bytes from each of the 5 lines */
        r0 = _itoll(r0_4, r0_10);
        r1 = _itoll(r1_4, r1_10);
        r2 = _itoll(r2_4, r2_10);
        r3 = _itoll(r3_4, r3_10);
        r4 = _itoll(r4_4, r4_10);

        /* Apply the vertical mask */
        r0x = _dmpyu4(r0, mask_ones);
        r1x = _dmpyu4(r1, mask_fours);
        r2x = _dmpyu4(r2, mask_sixes);
        r3x = _dmpyu4(r3, mask_fours);
        r4x = _dmpyu4(r4, mask_ones);

        /* Sum each column for all 8 columns */
        c3210_01 = _dadd2(_lo128(r0x), _lo128(r1x));
        c3210_23 = _dadd2(_lo128(r2x), _lo128(r3x));
        c3210_4  = _dadd2(_lo128(r4x), c3210_01);
        c3210    = _dadd2(c3210_23, c3210_4);
        c4       = _get32_128(r0x,2U) + _get32_128(r1x,2U) +
                   _get32_128(r2x,2U) + _get32_128(r3x,2U) +
                   _get32_128(r4x,2U);

        /* Apply horizontal mask to sums using dot product, and right shift */
        out0 = ( (uint32_t)_dotp4h(c3210, mask_r0_0) + c4) >> shift;
        dst[(x+2)-startX] = (uint8_t)out0;
    }
}

VXLIB_STATUS VXLIB_gaussian_5x5_br_i8u_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            uint8_t shift,
                            int16_t dstOffsetX,
                            int16_t dstOffsetY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_gaussian_5x5_br_i8u_o8u_checkParams(src, src_addr, dst, dst_addr, shift, dstOffsetX, dstOffsetY);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    y;
        int32_t    outHeight = dst_addr->dim_y;
        int32_t    outWidth = dst_addr->dim_x;
        int32_t    inHeight = src_addr->dim_y;
        int32_t    inWidth = src_addr->dim_x;
        int32_t    r0, r1, r2, r3, r4;
        int32_t    innerInMax = inWidth-4;
        int32_t    innerOutMax = outWidth-(2-(int32_t)dstOffsetX);
        int32_t    innerMax = VXLIB_min(innerInMax, innerOutMax);

        for( y=0; y < outHeight; y++ ) {

            const uint8_t  *src_t;
            uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];
            int32_t          y_mod = y+dstOffsetY;

            /* Top 2 border rows */
            if(y_mod == 0) {
                r0 = 0; r1 = 0; r2 = 0; r3 = 1; r4 = 2;
                src_t = (const uint8_t *)&src[0];
            } else if( y_mod == 1 ) {
                r0 = 0; r1 = 0; r2 = 1; r3 = 2; r4 = 3;
                src_t = (const uint8_t *)&src[0];

            /* Bottom 2 border rows */
            } else if( y_mod == (inHeight - 1 - 1)) {
                r0 = 1; r1 = 2; r2 = 3; r3 = 4; r4 = 4;
                src_t = (const uint8_t *)&src[ (y_mod-3) * src_addr->stride_y];
            } else if( y_mod == (inHeight - 1)) {
                r0 = 2; r1 = 3; r2 = 4; r3 = 4; r4 = 4;
                src_t = (const uint8_t *)&src[ (y_mod-4) * src_addr->stride_y];

            /* Interior rows */
            } else {
                r0 = 0; r1 = 1; r2 = 2; r3 = 3; r4 = 4;
                src_t = (const uint8_t *)&src[ (y_mod-2) * src_addr->stride_y];
            }

            VXLIB_gaussian_5x5_br_i8u_o8u_core(src_t, dst_t, src_addr->stride_y, outWidth, innerMax, shift, dstOffsetX,
                                               r0, r1, r2, r3, r4);

        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_gaussian_5x5_br_i8u_o8u_checkParams(const uint8_t src[restrict],
                                        const VXLIB_bufParams2D_t *src_addr,
                                        const uint8_t dst[restrict],
                                        const VXLIB_bufParams2D_t *dst_addr,
                                        uint8_t shift,
                                        int16_t dstOffsetX,
                                        int16_t dstOffsetY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x < dst_addr->dim_x) ||
               (src_addr->dim_y < dst_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < dst_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if( shift > 15U ) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_GAUSSIAN_5X5_BR_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
