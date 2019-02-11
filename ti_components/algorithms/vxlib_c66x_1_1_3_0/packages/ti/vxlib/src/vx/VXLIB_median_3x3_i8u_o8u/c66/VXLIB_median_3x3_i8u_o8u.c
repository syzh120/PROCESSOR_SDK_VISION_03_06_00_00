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

#include "VXLIB_median_3x3_i8u_o8u.h"

CODE_SECTION(VXLIB_median_3x3_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_median_3x3_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_median_3x3_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_median_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth);

static void VXLIB_median_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth)
{
    int32_t x;

    /* Prime the pipeline by partial sorting first 2
     * columns of first 3 rows */
    uint32_t x0_3210 = _mem4_const(&src[srcStride*0]);
    uint32_t x1_3210 = _mem4_const(&src[srcStride*1]);
    uint32_t x2_3210 = _mem4_const(&src[srcStride*2]);

    uint32_t x1_3210_a = _maxu4(x2_3210, x1_3210);
    uint32_t x2_3210_a = _minu4(x2_3210, x1_3210);

    uint32_t x0_3210_b = _maxu4(x0_3210, x1_3210_a);
    uint32_t x1_3210_b = _minu4(x0_3210, x1_3210_a);

    uint32_t x1_3210_c = _maxu4(x2_3210_a, x1_3210_b);
    uint32_t x2_3210_c = _minu4(x2_3210_a, x1_3210_b);

    uint32_t x01x00 = x0_3210_b << 16;
    uint32_t x11x10 = x1_3210_c << 16;
    uint32_t x21x20 = x2_3210_c << 16;

    /* Case 1: SIMD of 8 pixels at a time*/
    /* 9/8 = 1.125 cycles per pixel */
    for(x=0; x < (outWidth/8); x++) {

        /* Read 8 pixels across 3 rows, starting at col 2 */
        int64_t x0_76543210 = _mem8_const(&src[(srcStride*0) + (x*8) + 2]);
        int64_t x1_76543210 = _mem8_const(&src[(srcStride*1) + (x*8) + 2]);
        int64_t x2_76543210 = _mem8_const(&src[(srcStride*2) + (x*8) + 2]);

        /* Partial sort 3 rows from max to min */
        /*  x0_76543210_b, x1_76543210_c, x2_76543210_c */
        int64_t x1_76543210_a = _dmaxu4(x2_76543210, x1_76543210);
        int64_t x2_76543210_a = _dminu4(x2_76543210, x1_76543210);

        int64_t x0_76543210_b = _dmaxu4(x0_76543210, x1_76543210_a);
        int64_t x1_76543210_b = _dminu4(x0_76543210, x1_76543210_a);

        int64_t x1_76543210_c = _dmaxu4(x2_76543210_a, x1_76543210_b);
        int64_t x2_76543210_c = _dminu4(x2_76543210_a, x1_76543210_b);

        /* get 8 min of maxes (x0) */
        int64_t max0_76543210 = _itoll(_packlh2(_hill(x0_76543210_b), _loll(x0_76543210_b)),
                                        _packlh2(_loll(x0_76543210_b), x01x00));
        int64_t max1_76543210 = _itoll(_shlmb(_loll(x0_76543210_b), _hill(x0_76543210_b)),
                                        _shlmb(x01x00, _loll(x0_76543210_b)));
        int64_t minmax_76543210 = _dminu4(_dminu4(max0_76543210, max1_76543210), x0_76543210_b);

        /* get 8 max of mins (x2) */
        int64_t min0_76543210 = _itoll(_packlh2(_hill(x2_76543210_c), _loll(x2_76543210_c)),
                                        _packlh2(_loll(x2_76543210_c), x21x20));
        int64_t min1_76543210 = _itoll(_shlmb(_loll(x2_76543210_c), _hill(x2_76543210_c)),
                                        _shlmb(x21x20, _loll(x2_76543210_c)));
        int64_t maxmin_76543210 = _dmaxu4(_dmaxu4(min0_76543210, min1_76543210), x2_76543210_c);

        /* get 8 med of meds (x1) */
        int64_t med0_76543210 = _itoll(_packlh2(_hill(x1_76543210_c), _loll(x1_76543210_c)),
                                        _packlh2(_loll(x1_76543210_c), x11x10));
        int64_t med1_76543210 = _itoll(_shlmb(_loll(x1_76543210_c), _hill(x1_76543210_c)),
                                        _shlmb(x11x10, _loll(x1_76543210_c)));
        int64_t maxmed_76543210_0 = _dmaxu4(med1_76543210, x1_76543210_c);
        int64_t minmed_76543210_0 = _dminu4(med1_76543210, x1_76543210_c);
        int64_t minmed_76543210_1 = _dminu4(med0_76543210, maxmed_76543210_0);
        int64_t medmed_76543210   = _dmaxu4(minmed_76543210_1, minmed_76543210_0);

        /* final med of medmed, minmax, and maxmin */
        int64_t maxa_76543210 = _dmaxu4(maxmin_76543210, medmed_76543210);
        int64_t mina_76543210 = _dminu4(maxmin_76543210, medmed_76543210);
        int64_t minb_76543210 = _dminu4(minmax_76543210, maxa_76543210);
        int64_t med_76543210 = _dmaxu4(minb_76543210, mina_76543210);

        /* save overlap data for next iteration */
        x01x00 = (uint32_t)_mvd((int32_t)_hill(x0_76543210_b));
        x11x10 = (uint32_t)_mvd((int32_t)_hill(x1_76543210_c));
        x21x20 = (uint32_t)_mvd((int32_t)_hill(x2_76543210_c));

        /* store 8 median values */
        _mem8(&dst[x*8]) = med_76543210;
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MEDIAN_3X3_I8U_O8U_ALIGNED8_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 9 cycle per pixel */
    for(x*=8; x < outWidth; x++) {
        uint32_t r0 = _mem4_const(&src[(srcStride*0) + x]);
        uint32_t r1 = _mem4_const(&src[(srcStride*1) + x]);
        /* Last line read is different so that I don't read past the end of the buffer */
        uint32_t r2 = _mem2_const(&src[(srcStride*2) + x]) | ((uint32_t)src[(srcStride*2) + x + 2] << 16);

        uint32_t x1_a = _maxu4(r2, r1);
        uint32_t x2_a = _minu4(r2, r1);

        uint32_t x0_b = _maxu4(r0, x1_a);
        uint32_t x1_b = _minu4(r0, x1_a);

        uint32_t x1_c = _maxu4(x2_a, x1_b);
        uint32_t x2_c = _minu4(x2_a, x1_b);

        int64_t x0_4 = _mpyu4ll(x0_b, 0x01010101U);
        int64_t x1_4 = _mpyu4ll(x1_c, 0x01010101U);
        int64_t x2_4 = _mpyu4ll(x2_c, 0x01010101U);

        __x128_t x0_8 = _dmpyu2(x0_4, 0x0001000100010001);
        __x128_t x1_8 = _dmpyu2(x1_4, 0x0001000100010001);
        __x128_t x2_8 = _dmpyu2(x2_4, 0x0001000100010001);

        uint32_t minmax  = _minu4(_minu4(_get32_128(x0_8, 0), _get32_128(x0_8, 1U)), _get32_128(x0_8, 2U));
        uint32_t maxmin  = _maxu4(_maxu4(_get32_128(x2_8, 0), _get32_128(x2_8, 1U)), _get32_128(x2_8, 2U));
        uint32_t medmed  = _minu4(_maxu4(_get32_128(x1_8, 0), _get32_128(x1_8, 1U)), _get32_128(x1_8, 2U));
        uint32_t medmed1 = _maxu4(_minu4(_get32_128(x1_8, 0), _get32_128(x1_8, 1U)), medmed);

        uint32_t median  = _minu4(_maxu4(minmax, maxmin), medmed1);
        uint32_t median1 = _maxu4(_minu4(minmax, maxmin), median);

        dst[x] = (uint8_t)median1;
    }
#endif
}

VXLIB_STATUS VXLIB_median_3x3_i8u_o8u(const uint8_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               uint8_t dst[restrict],
                               const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MEDIAN_3X3_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_median_3x3_i8u_o8u_checkParams(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MEDIAN_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_median_3x3_i8u_o8u_core(src, dst, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - 2);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MEDIAN_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-2));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_median_3x3_i8u_o8u_core(src_t, dst_t, src_addr->stride_y, width);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MEDIAN_3X3_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MEDIAN_3X3_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_median_3x3_i8u_o8u_checkParams(const uint8_t src[restrict],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst[restrict],
                                           const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x < dst_addr->dim_x) ||
               ((src_addr->dim_y-2) !=  dst_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < dst_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_MEDIAN_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_MEDIAN_3X3_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_MEDIAN_3X3_I8U_O8U_ALIGNED8_WIDTHS))
    else if((dst_addr->dim_x % 8U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
