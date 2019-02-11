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

#include "VXLIB_erode_3x3_i8u_o8u.h"

CODE_SECTION(VXLIB_erode_3x3_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_erode_3x3_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_erode_3x3_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_erode_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth);

static void VXLIB_erode_3x3_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth)
{
    int32_t x;
    int64_t r0_76543210, r1_76543210, r2_76543210, min8, min8_a, min8_b, min8_d1, min8_d2;
    uint32_t r0_98, r1_98, r2_98, min2;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_ERODE_3X3_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0) &&
        ((srcStride % 8) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
        /* 7/16 = 0.4375 cycles per pixel */
        #pragma UNROLL(2)
        for(x=0; x < ((outWidth/16)*2); x++) {

            /* Read 10 bytes from each of the 3 lines to produce 8 outputs. */
            r0_76543210 = _amem8_const(&src[(srcStride*0) + (x*8)]);
            r1_76543210 = _amem8_const(&src[(srcStride*1) + (x*8)]);
            r2_76543210 = _amem8_const(&src[(srcStride*2) + (x*8)]);
            r0_98 = _amem2_const(&src[(srcStride*0) + (x*8) + 8]);
            r1_98 = _amem2_const(&src[(srcStride*1) + (x*8) + 8]);
            r2_98 = _amem2_const(&src[(srcStride*2) + (x*8) + 8]);

            /* Find min of each column */
            min8 = _dminu4(r0_76543210, r1_76543210);
            min8 = _dminu4(min8, r2_76543210);
            min2 = _minu4(r0_98, r1_98);
            min2 = _minu4(min2, r2_98);

            /* Shift and find min of result twice */
            /*    7 6 5 4 3 2 1 0 = min8
             *    8 7 6 5 4 3 2 1 = min8_d1
             *    9 8 7 6 5 4 3 2 = min8_d2
             */

            /* Create shifted copies of min8, and column-wise find the min */
            min8_d1 = _itoll(_shrmb(min2, _hill(min8)), _shrmb(_hill(min8), _loll(min8)));
            min8_d2 = _itoll(_packlh2(min2, _hill(min8)), _packlh2(_hill(min8), _loll(min8)));

            min8_a = _dminu4(min8, min8_d1);
            min8_b = _dminu4(min8_a, min8_d2);

            /* store 8 min values */
            _amem8(&dst[x*8]) = min8_b;
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_ERODE_3X3_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Since unaligned loads are bottleneck, save cost of data fetch
         * by fetching first 2 columns and finding min.  Update this state
         * for every iteration. */
        uint32_t x0_3210 = _mem4_const(&src[srcStride*0]);
        uint32_t x1_3210 = _mem4_const(&src[srcStride*1]);
        uint32_t x2_3210 = _mem4_const(&src[srcStride*2]);

        uint32_t min2a = _minu4(x2_3210, x1_3210);
        uint32_t xaxb  = _minu4(min2a, x0_3210) << 16;

        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 4/8 = 0.5 cycles per pixel */
        for(x=0; x < (outWidth/8); x++) {

            /* Read 10 bytes from each of the 3 lines to produce 8 outputs. */
            r0_76543210 = _mem8_const(&src[(srcStride*0) + (x*8) + 2]);
            r1_76543210 = _mem8_const(&src[(srcStride*1) + (x*8) + 2]);
            r2_76543210 = _mem8_const(&src[(srcStride*2) + (x*8) + 2]);

            /* Find min of each column */
            min8 = _dminu4(r0_76543210, r1_76543210);
            min8 = _dminu4(min8, r2_76543210);

            /* Shift and find min of result twice */
            /*    7 6 5 4 3 2 1 0 = min8
             *    6 5 4 3 2 1 0 a = min8_d1
             *    5 4 3 2 1 0 a b = min8_d2
             */

            /* Create shifted copies of min8, and column-wise find the min */
            min8_d1 = _itoll(_shlmb(_loll(min8), _hill(min8)), _shlmb(xaxb, _loll(min8)));
            min8_d2 = _itoll(_packlh2(_hill(min8), _loll(min8)), _packlh2(_loll(min8), xaxb));

            min8_a = _dminu4(min8, min8_d1);
            min8_b = _dminu4(min8_a, min8_d2);

            /* save overlap data for next iteration */
            xaxb = (uint32_t)_mvd((int32_t)_hill(min8));

            /* store 8 min values */
            _mem8(&dst[x*8]) = min8_b;
        }
    }
#endif

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED16_WIDTHS) && !defined(VXLIB_ERODE_3X3_I8U_O8U_ALIGNED16_WIDTHS))
    /* Case 3: Process remaining pixels beyond multiple of 8 or 16 */
    /* 5 cycle per pixel */
    for(x*=8; x < outWidth; x++) {
        int32_t j, k;
        uint8_t min = 255U;
        for(j=0; j < 3; j++) {
            for(k=0; k < 3; k++) {
                min = VXLIB_min(src[(j*srcStride) + (x+k)], min);
            }
        }

        dst[x] = min;
    }
#endif
}

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_ERODE_3X3_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_erode_3x3_i8u_o8u_checkParams(src, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_ERODE_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_erode_3x3_i8u_o8u_core(src, dst, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - 2);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_ERODE_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-2));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_erode_3x3_i8u_o8u_core(src_t, dst_t, src_addr->stride_y, width);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_ERODE_3X3_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_ERODE_3X3_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_erode_3x3_i8u_o8u_checkParams(const uint8_t src[restrict],
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
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_ERODE_3X3_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_ERODE_3X3_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED16_WIDTHS) || defined(VXLIB_ERODE_3X3_I8U_O8U_ALIGNED16_WIDTHS))
    else if((dst_addr->dim_x % 16U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
