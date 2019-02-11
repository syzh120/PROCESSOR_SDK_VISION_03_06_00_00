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

#include "VXLIB_thresholdRange_i8u_o8u.h"

CODE_SECTION(VXLIB_thresholdRange_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_thresholdRange_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_thresholdRange_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_thresholdRange_i8u_o8u_core(const uint8_t src[restrict],
                                       uint8_t dst[restrict],
                                       int32_t width,
                                       uint8_t upper,
                                       uint8_t lower,
                                       uint8_t trueVal,
                                       uint8_t falseVal);

static void VXLIB_thresholdRange_i8u_o8u_core(const uint8_t src[restrict],
                                       uint8_t dst[restrict],
                                       int32_t width,
                                       uint8_t upper,
                                       uint8_t lower,
                                       uint8_t trueVal,
                                       uint8_t falseVal)
{
    int32_t     x;
    uint32_t   upper4, lower4, tv4, fv4;
    uint64_t   upper8, lower8, tv8, fv8;
    uint64_t   mask, tv, fv;
    int64_t    src8, src8_2;

    /* Replicating the values across a 64-bit word for SIMD operations */
    upper4 = _pack2((uint32_t)upper, (uint32_t)upper);
    upper4 = _packl4(upper4, upper4);
    upper8 = (uint64_t)_itoll(upper4, upper4);
    lower4 = _pack2((uint32_t)lower, (uint32_t)lower);
    lower4 = _packl4(lower4, lower4);
    lower8 = (uint64_t)_itoll(lower4, lower4);
    tv4 = _pack2((uint32_t)trueVal, (uint32_t)trueVal);
    tv4 = _packl4(tv4, tv4);
    tv8 = (uint64_t)_itoll(tv4, tv4);
    fv4 = _pack2((uint32_t)falseVal, (uint32_t)falseVal);
    fv4 = _packl4(fv4, fv4);
    fv8 = (uint64_t)_itoll(fv4, fv4);

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_THRESHOLDRANGE_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    if((((uint32_t)src % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        if((trueVal == 255U) && (falseVal == 0)) {
            /* Case 1A: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
            /* 2/16 = 0.125 cycles per pixel */
            for( x=0; x < ((width / 16) * 2); x+=2 ) {
                src8 = _amem8_const(&src[x*8]);
                src8_2 = _amem8_const(&src[(x+1)*8]);
                _amem8(&dst[x*8]) = (uint64_t)_dxpnd4(~(_dcmpgtu4(src8, (int64_t)upper8) | _dcmpgtu4((int64_t)lower8, src8)));
                _amem8(&dst[(x+1)*8]) = (uint64_t)_dxpnd4(~(_dcmpgtu4(src8_2, (int64_t)upper8) | _dcmpgtu4((int64_t)lower8, src8_2)));
            }
        } else {
            /* Case 1B: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
            /* 3/16 = 0.1875 cycles per pixel */
            #pragma UNROLL(2)
            for( x=0; x < ((width / 16) * 2); x++ ) {
                src8 = _amem8_const(&src[x*8]);
                mask = (uint64_t)_dxpnd4(_dcmpgtu4(src8, (int64_t)upper8) | _dcmpgtu4((int64_t)lower8, src8));
                tv = ~mask & tv8;
                fv = mask & fv8;
                _amem8(&dst[x*8]) = tv | fv;
            }
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_THRESHOLDRANGE_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 2/8 = 0.25 cycles per pixel */
        for( x=0; x < (width / 8); x++ ) {
            src8 = _mem8(&src[x*8]);
            mask = (uint64_t)_dxpnd4(_dcmpgtu4(src8, (int64_t)upper8) | _dcmpgtu4((int64_t)lower8, src8));
            tv = ~mask & tv8;
            fv = mask & fv8;
            _mem8(&dst[x*8]) = tv | fv;
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_THRESHOLDRANGE_I8U_O8U_ALIGNED8_WIDTHS)

    /* Case 3: Process remaining pixels beyond multiple of 8 or 16 */
    /* 2 cycle per pixel */
    for( x*=8; x < width; x++ ) {
        dst[x] = ((src[x] > upper) || (src[x] < lower)) ? falseVal : trueVal;
    }

#endif
}

VXLIB_STATUS VXLIB_thresholdRange_i8u_o8u(const uint8_t src[restrict],
                                   const VXLIB_bufParams2D_t *src_addr,
                                   uint8_t dst[restrict],
                                   const VXLIB_bufParams2D_t *dst_addr,
                                   uint8_t upper,
                                   uint8_t lower,
                                   uint8_t trueVal,
                                   uint8_t falseVal)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_THRESHOLDRANGE_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_thresholdRange_i8u_o8u_checkParams(src, src_addr, dst, dst_addr, upper, lower);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_THRESHOLDRANGE_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y))
#endif
        {
            VXLIB_thresholdRange_i8u_o8u_core(src, dst, src_addr->dim_x * src_addr->dim_y, upper, lower, trueVal, falseVal);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_THRESHOLDRANGE_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src_addr->dim_y; y++ ) {

                const uint8_t   *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_thresholdRange_i8u_o8u_core(src_t, dst_t, src_addr->dim_x, upper, lower, trueVal, falseVal);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_THRESHOLDRANGE_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_THRESHOLDRANGE_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_thresholdRange_i8u_o8u_checkParams(const uint8_t src[],
                                               const VXLIB_bufParams2D_t *src_addr,
                                               const uint8_t dst[],
                                               const VXLIB_bufParams2D_t *dst_addr,
                                               uint8_t upper,
                                               uint8_t lower)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x != dst_addr->dim_x) ||
              (src_addr->dim_y != dst_addr->dim_y) ||
              (src_addr->stride_y < src_addr->dim_x) ||
              (dst_addr->stride_y < dst_addr->dim_x) ||
              (upper < lower)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_THRESHOLDRANGE_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_THRESHOLDRANGE_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED16_WIDTHS) || defined(VXLIB_THRESHOLDRANGE_I8U_O8U_ALIGNED16_WIDTHS)
    else if(((src_addr->dim_x % 16U) != 0) ||
            ((dst_addr->dim_x % 16U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else if(upper < lower) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

