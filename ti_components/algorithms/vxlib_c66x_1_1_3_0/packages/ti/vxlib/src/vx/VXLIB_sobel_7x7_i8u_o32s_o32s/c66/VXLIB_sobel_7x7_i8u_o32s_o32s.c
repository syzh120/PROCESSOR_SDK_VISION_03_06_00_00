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

#include "VXLIB_sobel_7x7_i8u_o32s_o32s.h"

CODE_SECTION(VXLIB_sobel_7x7_i8u_o32s_o32s,              ".text:optimized")
CODE_SECTION(VXLIB_sobel_7x7_i8u_o32s_o32s_core,         ".text:optimized")
CODE_SECTION(VXLIB_sobel_7x7_i8u_o32s_o32s_checkParams,  ".text:optimized")

static void VXLIB_sobel_7x7_i8u_o32s_o32s_core(const uint8_t src[restrict],
                                    int32_t dst_x[restrict],
                                    int32_t dst_y[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth);

static void VXLIB_sobel_7x7_i8u_o32s_o32s_core(const uint8_t src[restrict],
                                    int32_t dst_x[restrict],
                                    int32_t dst_y[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth)
{
    int32_t x = 0;

    int64_t   row1, row2, row3, row4, row5, row6, row7;
    __x128_t  row3_128, row5_128;
    int32_t  sum_x, sum_y;
    int64_t  dsum_x, dsum_y;

    /* -------------------------------------------------------------------- */
    /*  Initialize horizontal and vertical masks                            */
    /* -------------------------------------------------------------------- */
    int32_t maskx_r1_hi = 0x00010405;
    int32_t maskx_r1_lo = 0x00fbfcff;

    int32_t maskx_r2_hi = 0x0006181e;
    int32_t maskx_r2_lo = 0x00e2e8fa;

    int32_t maskx_r4_hi = 0x00145064;
    int32_t maskx_r4_lo = 0x009cb0ec;

    int32_t masky_r1_hi = 0x0001060f;
    int32_t masky_r1_lo = 0x140f0601;

    int32_t masky_r2_hi = 0x0004183c;
    int32_t masky_r2_lo = 0x503c1804;

    __x128_t maskx3 = _llto128(0x0000000f003c004b, 0x0000ffb5ffc4fff1);
    __x128_t masky3 = _llto128(0x00000005001e004b, 0x0064004b001e0005);

    int64_t ones = 0x0101010101010101;

    /* 1 output pixel at a time */
    /* 12/1 = 12 cycles per pixel */
    /* Note: In this approach, I use a mixture of using the 4x8bit dot products, and 8x16bit dot products
     * If the full loop used the 8x16bit dot product instructions, we run out of register space (18cy/px)
     * If the full loop used the 4x8bit dot product instructions, we get 13 cy/px with some extra registers.
     * So this hybrid approach gains 1 cycle back to utilize these extra registers
     */
    for (x=0; x<(outWidth); x++) {

        /* ----------------------------------------------------------------- */
        /* Fetch each row, and perform dot products on each, one at a time   */
        /* ----------------------------------------------------------------- */

        /* Process row 1 (calculate the 8bit dot product of 2 halves of the input, and sum) */
        row1     = _mem8_const(&src[(srcStride*0) + (x)]);
        sum_x = _dotpsu4(maskx_r1_hi, _hill(row1)) + _dotpsu4(maskx_r1_lo, _loll(row1));
        sum_y = _dotpsu4(masky_r1_hi, _hill(row1)) + _dotpsu4(masky_r1_lo, _loll(row1));

        /* Process row 2 (calculate the 8bit dot product of 2 halves of the input, and sum) */
        row2     = _mem8_const(&src[(srcStride*1) + (x)]);
        sum_x = _dotpsu4(maskx_r2_hi, _hill(row2)) + _dotpsu4(maskx_r2_lo, _loll(row2)) + sum_x;
        sum_y = _dotpsu4(masky_r2_hi, _hill(row2)) + _dotpsu4(masky_r2_lo, _loll(row2)) + sum_y;

        /* Process row 3 (convert to 16 bit, then calculate the 16bit dot product entire input) */
        row3     = _mem8_const(&src[(srcStride*2) + (x)]);
        row3_128 = _dmpyu4(row3, ones);
        dsum_x = _ddotp4h(maskx3,row3_128);
        dsum_y = _ddotp4h(masky3,row3_128);

        /* Process row 4 (calculate the 8bit dot product of 2 halves of the input, and sum) */
        row4     = _mem8_const(&src[(srcStride*3) + (x)]);
        sum_x = _dotpsu4(maskx_r4_hi, _hill(row4)) + _dotpsu4(maskx_r4_lo, _loll(row4)) + sum_x;

        /* Process row 5 (convert to 16 bit, then calculate the 16bit dot product entire input) */
        row5     = _mem8_const(&src[(srcStride*4) + (x)]);
        row5_128 = _dmpyu4(row5, ones);
        dsum_x = _dadd(_ddotp4h(maskx3,row5_128), dsum_x);
        dsum_y = _dsub(_ddotp4h(masky3,row5_128), dsum_y);

        /* Add the results of the 16-bit dot products together, and to the previous sums */
        sum_x = ((int32_t)_hill(dsum_x) + (int32_t)_loll(dsum_x)) + sum_x;
        sum_y = ((int32_t)_hill(dsum_y) + (int32_t)_loll(dsum_y)) - sum_y;

        /* Process row 6 (calculate the 8bit dot product of 2 halves of the input, and sum) */
        row6     = _mem8_const(&src[(srcStride*5) + (x)]);
        sum_x = _dotpsu4(maskx_r2_hi, _hill(row6)) + _dotpsu4(maskx_r2_lo, _loll(row6)) + sum_x;
        sum_y = _dotpsu4(masky_r2_hi, _hill(row6)) + _dotpsu4(masky_r2_lo, _loll(row6)) + sum_y;

        /* Process row 7 (calculate the 8bit dot product of 2 halves of the input, and sum) */
        row7     = _mem8_const(&src[(srcStride*6) + (x)]);
        sum_x = _dotpsu4(maskx_r1_hi, _hill(row7)) + _dotpsu4(maskx_r1_lo, _loll(row7)) + sum_x;
        sum_y = _dotpsu4(masky_r1_hi, _hill(row7)) + _dotpsu4(masky_r1_lo, _loll(row7)) + sum_y;

        /* ----------------------------------------------------------------- */
        /* Store in the output arrays                                        */
        /* ----------------------------------------------------------------- */
        dst_x[x] = sum_x;
        dst_y[x] = sum_y;
    }
}

VXLIB_STATUS VXLIB_sobel_7x7_i8u_o32s_o32s(const uint8_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               int32_t dst_x[restrict],
                               const VXLIB_bufParams2D_t *dst_x_addr,
                               int32_t dst_y[restrict],
                               const VXLIB_bufParams2D_t *dst_y_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_SOBEL_7X7_I8U_O32S_O32S_CHECK_PARAMS)
    status = VXLIB_sobel_7x7_i8u_o32s_o32s_checkParams(src, src_addr, dst_x, dst_x_addr, dst_y, dst_y_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SOBEL_7X7_I8U_O32S_O32S_EQUAL_WIDTH_STRIDE)
        if( (src_addr->dim_x      == src_addr->stride_y) &&
           ((dst_x_addr->dim_x*4) == dst_x_addr->stride_y) &&
           ((dst_y_addr->dim_x*4) == dst_y_addr->stride_y) &&
            (dst_x_addr->dim_x    == src_addr->dim_x) &&
            (dst_y_addr->dim_x    == src_addr->dim_x))
#endif
        {
            VXLIB_sobel_7x7_i8u_o32s_o32s_core(src, dst_x, dst_y, src_addr->stride_y, ((dst_x_addr->stride_y/4) * dst_x_addr->dim_y) - 4);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SOBEL_7X7_I8U_O32S_O32S_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_x_addr->dim_x, (src_addr->dim_x-4));

            for( y=0; y < dst_x_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                int32_t         *dstx_t  = (int32_t *)&dst_x[ y * (dst_x_addr->stride_y/4)];
                int32_t         *dsty_t  = (int32_t *)&dst_y[ y * (dst_y_addr->stride_y/4)];

                VXLIB_sobel_7x7_i8u_o32s_o32s_core(src_t, dstx_t, dsty_t, src_addr->stride_y, width);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_SOBEL_7X7_I8U_O32S_O32S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_SOBEL_7X7_I8U_O32S_O32S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_sobel_7x7_i8u_o32s_o32s_checkParams(const uint8_t src[restrict],
                                                  const VXLIB_bufParams2D_t *src_addr,
                                                  const int32_t dst_x[restrict],
                                                  const VXLIB_bufParams2D_t *dst_x_addr,
                                                  const int32_t dst_y[restrict],
                                                  const VXLIB_bufParams2D_t *dst_y_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if( (src == NULL) || (dst_x == NULL) || (dst_y == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src_addr->dim_x < dst_x_addr->dim_x) ||
                (src_addr->dim_x < dst_y_addr->dim_x) ||
               ((src_addr->dim_y-6) !=  dst_x_addr->dim_y) ||
               ((src_addr->dim_y-6) !=  dst_y_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_x_addr->stride_y < (dst_x_addr->dim_x*4)) ||
               (dst_y_addr->stride_y < (dst_y_addr->dim_x*4)) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_x_addr->data_type != VXLIB_INT32) ||
               (dst_y_addr->data_type != VXLIB_INT32)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_SOBEL_7X7_I8U_O32S_O32S_EQUAL_WIDTH_STRIDE)
    else if( (src_addr->dim_x != src_addr->stride_y) ||
             ((dst_x_addr->dim_x*4) != dst_x_addr->stride_y) ||
             ((dst_y_addr->dim_x*4) != dst_y_addr->stride_y) ||
              (src_addr->dim_x != dst_x_addr->dim_x) ||
              (src_addr->dim_x != dst_y_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
