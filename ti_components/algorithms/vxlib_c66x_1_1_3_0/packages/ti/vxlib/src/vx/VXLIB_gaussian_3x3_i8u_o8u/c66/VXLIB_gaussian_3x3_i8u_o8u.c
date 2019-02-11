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

#include "VXLIB_gaussian_3x3_i8u_o8u.h"

CODE_SECTION(VXLIB_gaussian_3x3_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_gaussian_3x3_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_gaussian_3x3_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_gaussian_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                      uint8_t dst[restrict],
                                      int32_t srcStride,
                                      int32_t outWidth);

static void VXLIB_gaussian_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                      uint8_t dst[restrict],
                                      int32_t srcStride,
                                      int32_t outWidth)
{
    int32_t x;

    int64_t mask_ones = 0x0101010101010101;
    int64_t mask_twos = 0x0202020202020202;
    uint32_t mask_ones_w = _loll(mask_ones);
    uint32_t mask_twos_w = _loll(mask_twos);

    int64_t mask_r0_0 = 0x0000000100020001;
    int64_t mask_r0_1 = 0x0001000200010000;

    int64_t r0, r1, r2;
    __x128_t r0x, r1x, r2x;
    int64_t c3210_01, c3210;
    int64_t c7654_01, c7654;
    int64_t c5432, c10ab;
    uint32_t out0, out1, out2, out3, out4, out5, out6, out7, out10, out32, out54, out76;

    /* Save cost of data fetch and re-use computation from iteration to
     * iteration by fetching first 2 columns and finding max.  Update this state
     * for every iteration. */
    uint32_t x0_3210 = _mem4_const(&src[srcStride*0]);
    uint32_t x1_3210 = _mem4_const(&src[srcStride*1]);
    uint32_t x2_3210 = _mem4_const(&src[srcStride*2]);

    /* Apply the vertical mask */
    int64_t x0_2 = _mpyu4ll(x0_3210, mask_ones_w);
    int64_t x1_2 = _mpyu4ll(x1_3210, mask_twos_w);
    int64_t x2_2 = _mpyu4ll(x2_3210, mask_ones_w);

    /* Add rows 0+1+2, column-wise */
    int32_t x01    = _add2((int32_t)_loll(x0_2), (int32_t)_loll(x1_2));
    uint32_t xaxb  = (uint32_t)_add2(x01, (int32_t)_loll(x2_2));

    /* Case 1: SIMD of 16 output pixels at a time */
    /* 12/16 = 0.75 cycles per pixel */
    #pragma UNROLL(2)
    for(x=0; x < (outWidth/8); x++) {

        /* Read 8 bytes from each of the 3 lines */
        r0 = _mem8_const(&src[(srcStride*0) + (x*8) + 2]);
        r1 = _mem8_const(&src[(srcStride*1) + (x*8) + 2]);
        r2 = _mem8_const(&src[(srcStride*2) + (x*8) + 2]);

        /* Apply the vertical mask */
        r0x = _dmpyu4(r0, mask_ones);
        r1x = _dmpyu4(r1, mask_twos);
        r2x = _dmpyu4(r2, mask_ones);

        /* Sum each column for all 8 columns */
        c3210_01 = _dadd2(_lo128(r0x), _lo128(r1x));
        c3210    = _dadd2(_lo128(r2x), c3210_01);
        c7654_01 = _dadd2(_hi128(r0x), _hi128(r1x));
        c7654    = _dadd2(_hi128(r2x), c7654_01);

        /* Repack column sums */
        c10ab = _itoll(_loll(c3210), xaxb);
        c5432 = _itoll(_loll(c7654), _hill(c3210));

        /* save overlap data for next iteration */
        xaxb = _hill(c7654);

        /* Apply horizontal mask to sums using dot product */
        out0 = (uint32_t)_dotp4h(c10ab, mask_r0_0);
        out1 = (uint32_t)_dotp4h(c10ab, mask_r0_1);
        out2 = (uint32_t)_dotp4h(c3210, mask_r0_0);
        out3 = (uint32_t)_dotp4h(c3210, mask_r0_1);
        out4 = (uint32_t)_dotp4h(c5432, mask_r0_0);
        out5 = (uint32_t)_dotp4h(c5432, mask_r0_1);
        out6 = (uint32_t)_dotp4h(c7654, mask_r0_0);
        out7 = (uint32_t)_dotp4h(c7654, mask_r0_1);

        /* Pack output appropriatly and right shift by 4 */
        out10 = _shru2(_pack2(out1, out0), 4U);
        out32 = _shru2(_pack2(out3, out2), 4U);
        out54 = _shru2(_pack2(out5, out4), 4U);
        out76 = _shru2(_pack2(out7, out6), 4U);

        /* Further packing and write to memory */
        _mem8(&dst[x*8]) = _itoll(_spacku4((int32_t)out76, (int32_t)out54),
                                  _spacku4((int32_t)out32, (int32_t)out10));
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_ALIGNED8_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 4 */
    /* 5 cycle per pixel */
    for(x*=8; x < outWidth; x++) {

        int32_t out = (int32_t)(        (int32_t)src[(0*srcStride) + (x+0)] + 
                                     _mpy((int32_t)src[(0*srcStride) + (x+1)], 2) +
                                          (int32_t)src[(0*srcStride) + (x+2)]+
                                     _mpy((int32_t)src[(1*srcStride) + (x+0)], 2) +
                                     _mpy((int32_t)src[(1*srcStride) + (x+1)], 4) +
                                     _mpy((int32_t)src[(1*srcStride) + (x+2)], 2) +
                                          (int32_t)src[(2*srcStride) + (x+0)]+
                                     _mpy((int32_t)src[(2*srcStride) + (x+1)], 2) +
                                          (int32_t)src[(2*srcStride) + (x+2)]);

        dst[x] = (uint8_t)((uint32_t)out >> 4U);
    }
#endif
}

VXLIB_STATUS VXLIB_gaussian_3x3_i8u_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_gaussian_3x3_i8u_o8u_checkParams(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_gaussian_3x3_i8u_o8u_core(src, dst, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - 2);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-2));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_gaussian_3x3_i8u_o8u_core(src_t, dst_t, src_addr->stride_y, width);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_gaussian_3x3_i8u_o8u_checkParams(const uint8_t src[restrict],
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
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_GAUSSIAN_3X3_I8U_O8U_ALIGNED8_WIDTHS))
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
