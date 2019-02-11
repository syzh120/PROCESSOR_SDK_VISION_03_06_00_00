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

#include "VXLIB_sobel_5x5_i8u_o16s_o16s.h"

CODE_SECTION(VXLIB_sobel_5x5_i8u_o16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_sobel_5x5_i8u_o16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_sobel_5x5_i8u_o16s_o16s_checkParams,  ".text:optimized")

static void VXLIB_sobel_5x5_i8u_o16s_o16s_core(const uint8_t src[restrict],
                                    int16_t dst_x[restrict],
                                    int16_t dst_y[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth);

static void VXLIB_sobel_5x5_i8u_o16s_o16s_core(const uint8_t src[restrict],
                                    int16_t dst_x[restrict],
                                    int16_t dst_y[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth)
{
    int32_t x = 0;

    int64_t   row1_76543210,  row2_76543210,  row3_76543210;
    int64_t   row4_76543210,  row5_76543210;

    uint32_t  row1_3210,  row2_3210,  row3_3210;
    uint32_t  row4_3210,  row5_3210;

    uint32_t  row1_r4310,  row2_r4310,  row3_r4310;
    uint32_t  row4_r4310,  row5_r4310;

    uint32_t  row1_r5421,  row2_r5421,  row3_r5421;
    uint32_t  row4_r5421,  row5_r5421;

    uint32_t  row1_6543,    row2_6543,    row3_6543;
    uint32_t  row4_6543,    row5_6543;

    int32_t  sum_h0,     sum_h1,     sum_v0,     sum_v1;
    int32_t  sum_m0,     sum_m1;

    int32_t  mask_hr0,   mask_hr1,   mask_vr0,   mask_vr1,   mask_vr2;
    int32_t  mask_hc2, mask_hc3;

    uint32_t  data_r3232;

    /* -------------------------------------------------------------------- */
    /*  Initialize horizontal and vertical masks                            */
    /* -------------------------------------------------------------------- */
    mask_hc2 = 0x000c0006;
    mask_hc3 = 0x0c000600;

    mask_hr0 = 0x01040401;  /* +1 +4 (0) +4 +1 */
    mask_hr1 = 0x02080802;  /* +2 +8 (0) +8 +2 */
    mask_vr0 = 0x0102feff;
    mask_vr1 = 0x0408f8fc;
    mask_vr2 = 0x060cf4fa;

    /* Case 1: SIMD of 2 output pixels at a time */
    /* 11/2 = 5.5 cycles per pixel */
    for (x=0; x<(outWidth/2); x++) {
        /* ------------------------------------------------------------------ */
        /* (A) Load first 8 pixel values for rows 1 and 2 (will only use 6).  */
        /* ------------------------------------------------------------------ */
        row1_76543210 = _mem8_const(&src[(srcStride*0) + (x*2)]);
        row2_76543210 = _mem8_const(&src[(srcStride*1) + (x*2)]);

        /* ------------------------------------------------------------------ */
        /*  (B) Pack the 1st and 2nd row pixels for cols 4,3,,1,0.            */
        /* ------------------------------------------------------------------ */
        row1_3210 = _loll(row1_76543210);
        row1_6543 = (uint32_t)((uint64_t)row1_76543210 >> 24);
        row2_3210 = _loll(row2_76543210);
        row2_6543 = (uint32_t)((uint64_t)row2_76543210 >> 24);
        data_r3232 = _packh2(row2_3210, row1_3210);

        row1_r4310 = _pack2(row1_6543, row1_3210);
        row2_r4310 = _pack2(row2_6543, row2_3210);

        /* ------------------------------------------------------------------ */
        /*  (C) Calculate horizontal and vertical mask sums.                  */
        /* ------------------------------------------------------------------ */
        sum_h0 = _dotpsu4(mask_hr0, row1_r4310) + _dotpsu4(mask_hr1, row2_r4310);
        sum_v0 = _dotpsu4(mask_vr0, row1_r4310) + _dotpsu4(mask_vr1, row2_r4310);

        /* ------------------------------------------------------------------ */
        /*  (D) Calculate horizontal sum for pixel 2 in rows 1 and 2.   */
        /* ------------------------------------------------------------------ */
        sum_m0 = _dotpsu4(mask_hc2, data_r3232);

        /* ------------------------------------------------------------------ */
        /*  (E) Pack the 1st and 2nd row pixels for cols 5,4,,2,1.            */
        /* ------------------------------------------------------------------ */
        row1_r5421 = _pack2(_hill(row1_76543210), row1_3210 >> 8);
        row2_r5421 = _pack2(_hill(row2_76543210), row2_3210 >> 8);

        /* ------------------------------------------------------------------ */
        /*  (F) Calculate horizontal and vertical mask sums.                  */
        /* ------------------------------------------------------------------ */
        sum_h1 = _dotpsu4(mask_hr0, row1_r5421) + _dotpsu4(mask_hr1, row2_r5421);
        sum_v1 = _dotpsu4(mask_vr0, row1_r5421) + _dotpsu4(mask_vr1, row2_r5421);

        /* ------------------------------------------------------------------ */
        /*  (G) Calculate horizontal sum for pixel 3 in rows 1 and 2.         */
        /* ------------------------------------------------------------------ */
        sum_m1 = _dotpsu4(mask_hc3, data_r3232);


        /* ------------------------------------------------------------------ */
        /* ------------------------------------------------------------------ */
        /*  Repeat similar process (A - G) for the 4th and 5th rows.          */
        /* ------------------------------------------------------------------ */
        /* ------------------------------------------------------------------ */


        /* ------------------------------------------------------------------ */
        /* (A) Load first 8 pixel values for rows 4 and 5 (will only use 6).  */
        /* ------------------------------------------------------------------ */
        row4_76543210 = _mem8_const(&src[(srcStride*3) + (x*2)]);
        row5_76543210 = _mem8_const(&src[(srcStride*4) + (x*2)]);

        /* ------------------------------------------------------------------ */
        /*  (B) Pack the 5th and 4th row pixels for cols 4,3,,1,0.            */
        /* ------------------------------------------------------------------ */
        row4_3210 = _loll(row4_76543210);
        row4_6543 = (uint32_t)((uint64_t)row4_76543210 >> 24);
        row5_3210 = _loll(row5_76543210);
        row5_6543 = (uint32_t)((uint64_t)row5_76543210 >> 24);
        data_r3232 = _packh2(row4_3210, row5_3210);

        row4_r4310 = _pack2(row4_6543, row4_3210);
        row5_r4310 = _pack2(row5_6543, row5_3210);

        /* ------------------------------------------------------------------ */
        /*  (C) Calculate horizontal and vertical mask sums.  Subtract the    */
        /*      horizontal sum from (C) above to account for negative mask    */
        /*      values.  Add the vertical sum to (C) above.                   */
        /* ------------------------------------------------------------------ */
        sum_h0 = (_dotpsu4(mask_hr1, row4_r4310) + _dotpsu4(mask_hr0, row5_r4310)) - sum_h0;
        sum_v0 = (_dotpsu4(mask_vr1, row4_r4310) + _dotpsu4(mask_vr0, row5_r4310)) + sum_v0;

        /* ------------------------------------------------------------------ */
        /*  (D) Calculate horizontal sum for pixel 2 in rows 5 and 4.         */
        /*      Subtract the horizontal sum from (D) above to account for     */
        /*      negative mask values.                                         */
        /* ------------------------------------------------------------------ */
        sum_m0 = _dotpsu4(mask_hc2, data_r3232) - sum_m0;

        /* ------------------------------------------------------------------ */
        /*  (E) Pack the 5th and 4th row pixels for cols 5,4,,2,1.            */
        /* ------------------------------------------------------------------ */
        row4_r5421 = _pack2(_hill(row4_76543210), row4_3210 >> 8);
        row5_r5421 = _pack2(_hill(row5_76543210), row5_3210 >> 8);

        /* ------------------------------------------------------------------ */
        /*  (F) Calculate horizontal and vertical mask sums.  Subtract the    */
        /*      horizontal sum from (C) above to account for negative mask    */
        /*      values.  Add the vertical sum to (C) above.                   */
        /* ------------------------------------------------------------------ */
        sum_h1 = (_dotpsu4(mask_hr1, row4_r5421) + _dotpsu4(mask_hr0, row5_r5421)) - sum_h1;
        sum_v1 = (_dotpsu4(mask_vr1, row4_r5421) + _dotpsu4(mask_vr0, row5_r5421)) + sum_v1;

        /* ------------------------------------------------------------------ */
        /*  (G) Calculate horizontal sum for pixel 2 in rows 5 and 4.         */
        /*      Subtract the horizontal sum from (D) above to account for     */
        /*      negative mask values.                                         */
        /* ------------------------------------------------------------------ */
        sum_m1 = _dotpsu4(mask_hc3, data_r3232) - sum_m1;


        /* ------------------------------------------------------------------ */
        /* ------------------------------------------------------------------ */
        /*  Process the 3rd row for the vertical mask only                    */
        /* ------------------------------------------------------------------ */
        /* ------------------------------------------------------------------ */


        /* ------------------------------------------------------------------ */
        /*  Load first 8 pixel values for row 3 (will only use 6).            */
        /* ------------------------------------------------------------------ */
        row3_76543210 = _mem8_const(&src[(srcStride*2) + (x*2)]);

        /* ------------------------------------------------------------------ */
        /*  Pack the 3rd row pixels for cols 4,3,,1,0 and 5,4,,2,1.           */
        /* ------------------------------------------------------------------ */
        row3_3210 = _loll(row3_76543210);
        row3_6543 = (uint32_t)((uint64_t)row3_76543210 >> 24);

        row3_r4310 = _pack2(row3_6543, row3_3210);
        row3_r5421 = _pack2(_hill(row3_76543210), row3_3210 >> 8);

        /* ------------------------------------------------------------------ */
        /*  Calculate vertical mask partial sums for two outputs              */
        /*  simultaneously.                                                   */
        /* ------------------------------------------------------------------ */
        sum_v0 += _dotpsu4(mask_vr2, row3_r4310);
        sum_v1 += _dotpsu4(mask_vr2, row3_r5421);


        /* ------------------------------------------------------------------ */
        /* ------------------------------------------------------------------ */
        /*  Calculate two outputs.                                            */
        /* ------------------------------------------------------------------ */
        /* ------------------------------------------------------------------ */


        /* ------------------------------------------------------------------ */
        /*  Add all partial horizontal sums together.                         */
        /* ------------------------------------------------------------------ */
        sum_h0 += sum_m0;
        sum_h1 += sum_m1;

        /* ----------------------------------------------------------------- */
        /* Saturate and pack the result to store in the output arrays        */
        /* ----------------------------------------------------------------- */
        _mem4(&dst_x[x*2]) = (uint32_t)_spack2(sum_v1, sum_v0);
        _mem4(&dst_y[x*2]) = (uint32_t)_spack2(sum_h1, sum_h0);
    }

#if (!defined(VXLIB_ALIGNED2_WIDTHS) && !defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_ALIGNED2_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 8 cycles per pixel */
    for(x*=2; x < outWidth; x++) {
        int32_t i, j;
        int16_t sumx, sumy;
        int8_t coef[5][5] =  {{ -1,  -2, 0,  2, 1},
                               { -4,  -8, 0,  8, 4},
                               { -6, -12, 0, 12, 6},
                               { -4,  -8, 0,  8, 4},
                               { -1,  -2, 0,  2, 1}};
        sumx = 0;
        sumy = 0;
        for(j=0; j<5; j++) {
            for(i=0; i<5; i++) {
                sumx += ((int16_t)src[(j*srcStride) + (x+i)] * coef[j][i]);
                sumy += ((int16_t)src[(j*srcStride) + (x+i)] * coef[i][j]);
            }
        }
        dst_x[x] = sumx;
        dst_y[x] = sumy;
    }
#endif
}

VXLIB_STATUS VXLIB_sobel_5x5_i8u_o16s_o16s(const uint8_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               int16_t dst_x[restrict],
                               const VXLIB_bufParams2D_t *dst_x_addr,
                               int16_t dst_y[restrict],
                               const VXLIB_bufParams2D_t *dst_y_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_CHECK_PARAMS)
    status = VXLIB_sobel_5x5_i8u_o16s_o16s_checkParams(src, src_addr, dst_x, dst_x_addr, dst_y, dst_y_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_EQUAL_WIDTH_STRIDE)
        if( (src_addr->dim_x      == src_addr->stride_y) &&
           ((dst_x_addr->dim_x*2) == dst_x_addr->stride_y) &&
           ((dst_y_addr->dim_x*2) == dst_y_addr->stride_y) &&
            (dst_x_addr->dim_x    == src_addr->dim_x) &&
            (dst_y_addr->dim_x    == src_addr->dim_x))
#endif
        {
            VXLIB_sobel_5x5_i8u_o16s_o16s_core(src, dst_x, dst_y, src_addr->stride_y, ((dst_x_addr->stride_y/2) * dst_x_addr->dim_y) - 4);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_x_addr->dim_x, (src_addr->dim_x-4));

            for( y=0; y < dst_x_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                int16_t         *dstx_t  = (int16_t *)&dst_x[ y * (dst_x_addr->stride_y/2)];
                int16_t         *dsty_t  = (int16_t *)&dst_y[ y * (dst_y_addr->stride_y/2)];

                VXLIB_sobel_5x5_i8u_o16s_o16s_core(src_t, dstx_t, dsty_t, src_addr->stride_y, width);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_sobel_5x5_i8u_o16s_o16s_checkParams(const uint8_t src[restrict],
                                                  const VXLIB_bufParams2D_t *src_addr,
                                                  const int16_t dst_x[restrict],
                                                  const VXLIB_bufParams2D_t *dst_x_addr,
                                                  const int16_t dst_y[restrict],
                                                  const VXLIB_bufParams2D_t *dst_y_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if( (src == NULL) || (dst_x == NULL) || (dst_y == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src_addr->dim_x < dst_x_addr->dim_x) ||
                (src_addr->dim_x < dst_y_addr->dim_x) ||
               ((src_addr->dim_y-4) !=  dst_x_addr->dim_y) ||
               ((src_addr->dim_y-4) !=  dst_y_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_x_addr->stride_y < (dst_x_addr->dim_x*2)) ||
               (dst_y_addr->stride_y < (dst_y_addr->dim_x*2)) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_x_addr->data_type != VXLIB_INT16) ||
               (dst_y_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_EQUAL_WIDTH_STRIDE)
    else if( (src_addr->dim_x != src_addr->stride_y) ||
             ((dst_x_addr->dim_x*2) != dst_x_addr->stride_y) ||
             ((dst_y_addr->dim_x*2) != dst_y_addr->stride_y) ||
              (src_addr->dim_x != dst_x_addr->dim_x) ||
              (src_addr->dim_x != dst_y_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if (defined(VXLIB_ALIGNED2_WIDTHS) || defined(VXLIB_SOBEL_5X5_I8U_O16S_O16S_ALIGNED2_WIDTHS))
    else if(((dst_x_addr->dim_x % 2U) != 0) ||
             ((dst_y_addr->dim_x % 2U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
