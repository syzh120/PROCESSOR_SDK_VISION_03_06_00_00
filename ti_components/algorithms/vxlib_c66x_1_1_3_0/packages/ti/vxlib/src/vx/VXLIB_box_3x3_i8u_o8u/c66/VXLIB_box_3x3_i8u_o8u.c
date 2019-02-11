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

#include "VXLIB_box_3x3_i8u_o8u.h"

CODE_SECTION(VXLIB_box_3x3_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_box_3x3_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_box_3x3_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_box_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth);

static void VXLIB_box_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth)
{
    int32_t x;
    int64_t mask = 0x0101010101010101;
    int64_t mask1 = 0x0001000100010001;
    uint32_t mask_a = _loll(mask);
    uint32_t div9Mult = 0x38e38e39U;

    /* Save cost of data fetch and re-use computation from iteration to
     * iteration by fetching first 2 columns and finding max.  Update this state
     * for every iteration. */
    uint32_t x0_3210 = _mem4_const(&src[srcStride*0]);
    uint32_t x1_3210 = _mem4_const(&src[srcStride*1]);
    uint32_t x2_3210 = _mem4_const(&src[srcStride*2]);

    /* Convert from 8bpp to 16bpp so we can do SIMD addition of rows */
    int64_t x0_2 = _mpyu4ll(x0_3210, mask_a);
    int64_t x1_2 = _mpyu4ll(x1_3210, mask_a);
    int64_t x2_2 = _mpyu4ll(x2_3210, mask_a);

    /* Add rows 0+1+2, column-wise */
    int32_t x01    = _add2((int32_t)_loll(x0_2), (int32_t)_loll(x1_2));
    uint32_t xaxb  = (uint32_t)_add2(x01, (int32_t)_loll(x2_2));

    /* Case 1: SIMD of 8 output pixels at a time */
    /* 7/8 = 0.875 cycles per pixel */
    for(x=0; x < (outWidth/8); x++) {
        /* Read 8 bytes from each of the 3 lines. */
        int64_t r0 = _mem8_const(&src[(srcStride*0) + (x*8) + 2]);
        int64_t r1 = _mem8_const(&src[(srcStride*1) + (x*8) + 2]);
        int64_t r2 = _mem8_const(&src[(srcStride*2) + (x*8) + 2]);

        /* Convert from 8bpp to 16bpp so we can do SIMD addition of rows */
        __x128_t r0_2 = _dmpyu4(r0, mask);
        __x128_t r1_2 = _dmpyu4(r1, mask);
        __x128_t r2_2 = _dmpyu4(r2, mask);

        /* Add rows 0+1, column-wise */
        int64_t r01_lo = _dadd2(_lo128(r0_2), _lo128(r1_2));
        int64_t r01_hi = _dadd2(_hi128(r0_2), _hi128(r1_2));

        /* Add previous sum to row 2, column-wise */
        int64_t r012_lo = _dadd2(r01_lo, _lo128(r2_2));
        int64_t r012_hi = _dadd2(r01_hi, _hi128(r2_2));

        /* Left shift this sum by one pixel, and 2 pixels respectively, using history */
        int64_t r012_lo_d1 = _itoll(_packlh2(_hill(r012_lo), _loll(r012_lo)),
                                     _packlh2(_loll(r012_lo), xaxb));
        int64_t r012_hi_d1 = _itoll(_packlh2(_hill(r012_hi), _loll(r012_hi)),
                                     _packlh2(_loll(r012_hi), _hill(r012_lo)));
    
        int64_t r012_lo_d2 = _itoll(_loll(r012_lo), xaxb);
        int64_t r012_hi_d2 = _itoll(_loll(r012_hi), _hill(r012_lo));

        /* Now add adjacent columns together to find neigborhood sums */
        /*    7 6 5 4 3 2 1 0 = r012
         *  + 6 5 4 3 2 1 0 a = r012_d1
         *  + 5 4 3 2 1 0 a b = r012_d2
         * --------------------
         *              c012
         */
        int64_t c01_lo  = _dadd2(r012_lo, (int64_t)r012_lo_d1);
        int64_t c012_lo = _dadd2(c01_lo, r012_lo_d2);

        int64_t c01_hi  = _dadd2(r012_hi, (int64_t)r012_hi_d1);
        int64_t c012_hi = _dadd2(c01_hi, r012_hi_d2);

        /* Convert 16bbp sums into 32bpp register sums */
        __x128_t sum4_lo = _dmpyu2(c012_lo, mask1);
        __x128_t sum4_hi = _dmpyu2(c012_hi, mask1);

        /* Divide each sum by 9, using fixed point trick */
        uint32_t out0 = _hill(_mpy32u(_get32_128(sum4_lo, 0 ), div9Mult)) / 2U;
        uint32_t out1 = _hill(_mpy32u(_get32_128(sum4_lo, 1U), div9Mult)) / 2U;
        uint32_t out2 = _hill(_mpy32u(_get32_128(sum4_lo, 2U), div9Mult)) / 2U;
        uint32_t out3 = _hill(_mpy32u(_get32_128(sum4_lo, 3U), div9Mult)) / 2U;
        uint32_t out4 = _hill(_mpy32u(_get32_128(sum4_hi, 0 ), div9Mult)) / 2U;
        uint32_t out5 = _hill(_mpy32u(_get32_128(sum4_hi, 1U), div9Mult)) / 2U;
        uint32_t out6 = _hill(_mpy32u(_get32_128(sum4_hi, 2U), div9Mult)) / 2U;
        uint32_t out7 = _hill(_mpy32u(_get32_128(sum4_hi, 3U), div9Mult)) / 2U;

        /* Convert 32bbp results back into 8bpp, write to memory */
        uint32_t out10 = _pack2(out1, out0);
        uint32_t out32 = _pack2(out3, out2);
        uint32_t out54 = _pack2(out5, out4);
        uint32_t out76 = _pack2(out7, out6);

        /* save overlap data for next iteration */
        xaxb = (uint32_t)_mvd((int32_t)_hill(r012_hi));

        /* store 8 box filter values */
        _mem8(&dst[x*8]) = _itoll(_spacku4((int32_t)out76, (int32_t)out54),
                                  _spacku4((int32_t)out32, (int32_t)out10));
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED4_WIDTHS) && !defined(VXLIB_BOX_3X3_I8U_O8U_ALIGNED4_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 4 */
    /* 5 cycle per pixel */
    for(x*=8; x < outWidth; x++) {

        dst[x] = (  src[(0*srcStride) + (x+0)] + 
                    src[(0*srcStride) + (x+1)] +
                    src[(0*srcStride) + (x+2)] +
                    src[(1*srcStride) + (x+0)] +
                    src[(1*srcStride) + (x+1)] +
                    src[(1*srcStride) + (x+2)] +
                    src[(2*srcStride) + (x+0)] +
                    src[(2*srcStride) + (x+1)] +
                    src[(2*srcStride) + (x+2)]   )  / 9U;
    }
#endif
}

VXLIB_STATUS VXLIB_box_3x3_i8u_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_BOX_3X3_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_box_3x3_i8u_o8u_checkParams(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_BOX_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_box_3x3_i8u_o8u_core(src, dst, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - 2);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_BOX_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-2));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_box_3x3_i8u_o8u_core(src_t, dst_t, src_addr->stride_y, width);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_BOX_3X3_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_BOX_3X3_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_box_3x3_i8u_o8u_checkParams(const uint8_t src[restrict],
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
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_BOX_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED4_WIDTHS) || defined(VXLIB_BOX_3X3_I8U_O8U_ALIGNED4_WIDTHS))
    else if((dst_addr->dim_x % 4U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
