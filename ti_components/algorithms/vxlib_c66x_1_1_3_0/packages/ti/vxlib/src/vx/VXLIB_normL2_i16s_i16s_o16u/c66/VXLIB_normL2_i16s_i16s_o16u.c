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

#include "VXLIB_normL2_i16s_i16s_o16u.h"

CODE_SECTION(VXLIB_normL2_i16s_i16s_o16u,              ".text:optimized")
CODE_SECTION(VXLIB_normL2_i16s_i16s_o16u_core,         ".text:optimized")
CODE_SECTION(VXLIB_normL2_i16s_i16s_o16u_checkParams,  ".text:optimized")

static inline __float2_t sqrtsp2 (__float2_t a);

static void VXLIB_normL2_i16s_i16s_o16u_core(const int16_t src0[restrict],
                                         const int16_t src1[restrict],
                                         uint16_t dst[restrict],
                                         int32_t width);

/* This function is custom made to operate on SIMD of 2 
 * It doesn't take care to compare if > 0 or < MAX (done outside of function)
 * Only 1 iteration of Newton-Rhapson is done, so accuracy is 16 bits mantissa
 * instead of 23 bits (good enough for this algorithm) */
static inline __float2_t sqrtsp2 (__float2_t a)
{
    __float2_t    half  =  _ftof2(0.5f, 0.5f);
    __float2_t    OneP5 =  _ftof2(1.5f, 1.5f);
    __float2_t    x, y;
    __float2_t    xmults, xsub;

    x = _ftof2( _rsqrsp(_hif2(a)),
                _rsqrsp(_lof2(a)) );

    xmults = _dmpysp(_dmpysp(a, _dmpysp(x, x)), half);
    xsub = _dsubsp(OneP5, xmults);

    x = _dmpysp(x, xsub);
    y = _dmpysp(a, x);

    return (y);
}

static void VXLIB_normL2_i16s_i16s_o16u_core(const int16_t src0[restrict],
                                     const int16_t src1[restrict],
                                     uint16_t dst[restrict],
                                     int32_t width)
{
    int32_t    x;
    int64_t src0_4, src1_4;
    __x128_t src0_4_sqr, src1_4_sqr;
    int64_t sum_lo, sum_hi;
    uint32_t mask0, mask1, mask2, mask3;
    int64_t mask;
    __float2_t sum_lo_f,  sum_hi_f, norm_lo_f, norm_hi_f;
    int64_t norm_lo, norm_hi;
    int64_t output;
    uint64_t maskedOut;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_NORML2_I16S_I16S_O16U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0U) &&
       (((uint32_t)src1 % 8U) == 0U) &&
       (((uint32_t)dst % 8U) == 0U))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time*/
        /* 10/4 = 2.5 cycles per pixel */
        for( x=0; x < (width / 4); x++ ) {
            /* Fetch 4 pixels from memory from both x and y gradient images */
            src0_4 = _amem8_const(&src0[x*4]);
            src1_4 = _amem8_const(&src1[x*4]);

            /* Square each pixel in both x and y gradient images (dx^2, dy^2) */
            src0_4_sqr = _dmpy2(src0_4, src0_4);
            src1_4_sqr = _dmpy2(src1_4, src1_4);

            /* Add the x and y squares together (dx^2 + dy^2) */
            sum_lo = _dadd(_lo128(src0_4_sqr), _lo128(src1_4_sqr));
            sum_hi = _dadd(_hi128(src0_4_sqr), _hi128(src1_4_sqr));

            /* Create a mask of 1's for each sum which is > 0 */
            mask0 = (uint32_t)_ext(_loll(sum_lo) > 0U, 31U, 31U);
            mask1 = (uint32_t)_ext(_hill(sum_lo) > 0U, 31U, 31U);
            mask2 = (uint32_t)_ext(_loll(sum_hi) > 0U, 31U, 31U);
            mask3 = (uint32_t)_ext(_hill(sum_hi) > 0U, 31U, 31U);
            mask = _itoll( _pack2(mask3, mask2), _pack2(mask1, mask0));

            /* Convert sums to F32 */
            sum_lo_f = _dintsp(sum_lo);
            sum_hi_f = _dintsp(sum_hi);

            /* Find the sqrt of each floating point sum */
            norm_lo_f = sqrtsp2(sum_lo_f);
            norm_hi_f = sqrtsp2(sum_hi_f);

            /* Convert the sqrt results back to integer */
            norm_lo = _dspint(norm_lo_f);
            norm_hi = _dspint(norm_hi_f);

            /* Pack the output back to 16-bits per pixel */
            output = _itoll( _pack2(_hill(norm_hi), _loll(norm_hi)),
                             _pack2(_hill(norm_lo), _loll(norm_lo)));

            /* AND the mask with these results to ensure that sums of zero stay zero */
            maskedOut = (uint64_t)mask & (uint64_t)output;

            /* Write the results back to memory */
            _amem8(&dst[x*4]) = (int64_t)maskedOut;
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_NORML2_I16S_I16S_O16U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time*/
        /* 12/4 = 3 cycles per pixel */
        for( x=0; x < (width / 4); x++ ) {
            /* Fetch 4 pixels from memory from both x and y gradient images */
            src0_4 = _mem8_const(&src0[x*4]);
            src1_4 = _mem8_const(&src1[x*4]);

            /* Square each pixel in both x and y gradient images (dx^2, dy^2) */
            src0_4_sqr = _dmpy2(src0_4, src0_4);
            src1_4_sqr = _dmpy2(src1_4, src1_4);

            /* Add the x and y squares together (dx^2 + dy^2) */
            sum_lo = _dadd(_lo128(src0_4_sqr), _lo128(src1_4_sqr));
            sum_hi = _dadd(_hi128(src0_4_sqr), _hi128(src1_4_sqr));

            /* Create a mask of 1's for each sum which is > 0 */
            mask0 = (uint32_t)_ext(_loll(sum_lo) > 0U, 31U, 31U);
            mask1 = (uint32_t)_ext(_hill(sum_lo) > 0U, 31U, 31U);
            mask2 = (uint32_t)_ext(_loll(sum_hi) > 0U, 31U, 31U);
            mask3 = (uint32_t)_ext(_hill(sum_hi) > 0U, 31U, 31U);
            mask = _itoll( _pack2(mask3, mask2), _pack2(mask1, mask0));

            /* Convert sums to F32 */
            sum_lo_f = _dintsp(sum_lo);
            sum_hi_f = _dintsp(sum_hi);

            /* Find the sqrt of each floating point sum */
            norm_lo_f = sqrtsp2(sum_lo_f);
            norm_hi_f = sqrtsp2(sum_hi_f);

            /* Convert the sqrt results back to integer */
            norm_lo = _dspint(norm_lo_f);
            norm_hi = _dspint(norm_hi_f);

            /* Pack the output back to 16-bits per pixel */
            output = _itoll( _pack2(_hill(norm_hi), _loll(norm_hi)),
                             _pack2(_hill(norm_lo), _loll(norm_lo)));

            /* AND the mask with these results to ensure that sums of zero stay zero */
            maskedOut = (uint64_t)mask & (uint64_t)output;

            /* Write the results back to memory */
            _mem8(&dst[x*4]) = (int64_t)maskedOut;
        }
    }
#endif

#if !defined(VXLIB_ALIGNED4_WIDTHS) && !defined(VXLIB_NORML2_I16S_I16S_O16U_ALIGNED4_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 4 */
    /* 6 cycles per pixel */
    for(x*=4; x < width; x++ ) {

        /* Square each pixel in both x and y gradient images, and add together (dx^2 + dy^2) */
        int32_t sumSq = ((int32_t)src0[x] * (int32_t)src0[x]) +
                         ((int32_t)src1[x] * (int32_t)src1[x]);

        /* Create a mask of 1's if sum is > 0 */
        mask0 = (uint32_t)_ext((uint32_t)sumSq > 0U, 31U, 31U);

        /* Convert sum to F32 */
        sum_lo_f = _dintsp((int64_t)sumSq);

        /* Find the sqrt of the floating point sum */
        norm_lo_f = sqrtsp2(sum_lo_f);

        /* Convert the sqrt result back to integer */
        norm_lo = _dspint(norm_lo_f);

        /* AND the mask with the results to ensure that sums of zero stay zero
         * and write back to memory */
        dst[x] = (uint16_t) (mask0 & _loll(norm_lo));
    }
#endif
}

VXLIB_STATUS VXLIB_normL2_i16s_i16s_o16u(const int16_t src_x[restrict],
                                    const VXLIB_bufParams2D_t * src_x_addr,
                                    const int16_t src_y[restrict],
                                    const VXLIB_bufParams2D_t * src_y_addr,
                                    uint16_t dst[restrict],
                                    const VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_NORML2_I16S_I16S_O16U_CHECK_PARAMS)
    status = VXLIB_normL2_i16s_i16s_o16u_checkParams(src_x, src_x_addr, src_y, src_y_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_NORML2_I16S_I16S_O16U_EQUAL_WIDTH_STRIDE)
        if(((2 * (int32_t)src_x_addr->dim_x) == src_x_addr->stride_y) &&
           ((2 * (int32_t)src_y_addr->dim_x) == src_y_addr->stride_y) &&
           ((2 * (int32_t)dst_addr->dim_x) == dst_addr->stride_y))
#endif
        {
            int32_t width = (int32_t)src_x_addr->dim_x * (int32_t)src_x_addr->dim_y;
            VXLIB_normL2_i16s_i16s_o16u_core(src_x, src_y, dst, width);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_NORML2_I16S_I16S_O16U_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < (int32_t)src_x_addr->dim_y; y++ ) {
                const int16_t   *src_x_t = (const int16_t *)&src_x[ y * (src_x_addr->stride_y / 2) ];
                const int16_t   *src_y_t = (const int16_t *)&src_y[ y * (src_y_addr->stride_y / 2) ];
                uint16_t         *dst_t  = (uint16_t *)&dst[ y * (dst_addr->stride_y / 2)];

                VXLIB_normL2_i16s_i16s_o16u_core(src_x_t, src_y_t, dst_t, (int32_t)src_x_addr->dim_x);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_NORML2_I16S_I16S_O16U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_NORML2_I16S_I16S_O16U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_normL2_i16s_i16s_o16u_checkParams(const int16_t src_x[restrict],
                                    const VXLIB_bufParams2D_t * src_x_addr,
                                    const int16_t src_y[restrict],
                                    const VXLIB_bufParams2D_t * src_y_addr,
                                    uint16_t dst[restrict],
                                    const VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status;

    if((src_x == NULL) || (src_y == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_x_addr->dim_x != src_y_addr->dim_x) ||
              (src_x_addr->dim_x != dst_addr->dim_x) ||
              (src_x_addr->dim_y != src_y_addr->dim_y) ||
              (src_x_addr->dim_y != dst_addr->dim_y) ||
              ((uint32_t)src_x_addr->stride_y < src_x_addr->dim_x) ||
              ((uint32_t)src_y_addr->stride_y < src_y_addr->dim_x) ||
              ((uint32_t)dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_x_addr->data_type != VXLIB_INT16) ||
               (src_y_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_UINT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_NORML2_I16S_I16S_O16U_EQUAL_WIDTH_STRIDE)
    else if(((uint32_t)src_x_addr->dim_x != src_x_addr->stride_y) ||
            ((uint32_t)src_y_addr->dim_x != src_y_addr->stride_y) ||
            ((uint32_t)dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_NORML2_I16S_I16S_O16U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src_x % 8U) != 0) ||
            (((uint32_t)src_y % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src_x_addr->stride_y % 8U) != 0) ||
            ((src_y_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_NORML2_I16S_I16S_O16U_ALIGNED8_WIDTHS)
    else if(((src_x_addr->dim_x % 8U) != 0) ||
            ((src_y_addr->dim_x % 8U) != 0) ||
            ((dst_addr->dim_x % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

