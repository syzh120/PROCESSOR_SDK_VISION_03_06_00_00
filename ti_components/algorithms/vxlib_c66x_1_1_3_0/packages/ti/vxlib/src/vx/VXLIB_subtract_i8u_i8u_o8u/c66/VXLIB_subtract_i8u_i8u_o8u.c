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

#include "VXLIB_subtract_i8u_i8u_o8u.h"

CODE_SECTION(VXLIB_subtract_i8u_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_subtract_i8u_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_subtract_i8u_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_subtract_i8u_i8u_o8u_core(const uint8_t src0[restrict],
                            const uint8_t src1[restrict],
                            uint8_t dst[restrict],
                            int32_t width,
                            uint16_t overflow_policy);

static void VXLIB_subtract_i8u_i8u_o8u_core(const uint8_t src0[restrict],
                            const uint8_t src1[restrict],
                            uint8_t dst[restrict],
                            int32_t width,
                            uint16_t overflow_policy)
{
    int32_t   x;
    int64_t   src0_8, src1_8;
    int64_t   overflowing_result, mask;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_SUBTRACT_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    if((((uint32_t)src0 % 8U) == 0) &&
       (((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
        _nassert(((uint32_t)src0 % 8U) == 0);
        _nassert(((uint32_t)src1 % 8U) == 0);
        _nassert(((uint32_t)dst % 8U) == 0);
        if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
            /* 3/16 = 0.1875 cycles per pixel */
            #pragma MUST_ITERATE(0,,2)
            for( x=0; x < (((width / 8) / 2) * 2); x++ ) {
                src0_8 = _amem8_const(&src0[x*8]);
                src1_8 = _amem8_const(&src1[x*8]);
                _amem8(&dst[x*8]) = _itoll((uint32_t)_sub4((int32_t)_hill(src0_8), (int32_t)_hill(src1_8)),
                                           (uint32_t)_sub4((int32_t)_loll(src0_8), (int32_t)_loll(src1_8)));
            }
        } else {
            /* 3/16 = 0.1875 cycles per pixel */
            #pragma UNROLL(2)
            for( x=0; x < (((width / 8) / 2) * 2); x++ ) {
                src0_8 = _amem8_const(&src0[x*8]);
                src1_8 = _amem8_const(&src1[x*8]);
                mask = _dxpnd4(_dcmpgtu4(src0_8, src1_8));
                overflowing_result = _itoll((uint32_t)_sub4((int32_t)_hill(src0_8), (int32_t)_hill(src1_8)),
                                            (uint32_t)_sub4((int32_t)_loll(src0_8), (int32_t)_loll(src1_8)));
                _amem8(&dst[x*8]) = (uint64_t)overflowing_result & (uint64_t)mask;
            }
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_SUBTRACT_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/

        if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
            /* 3/8 = 0.375 cycles per pixel */
            for( x=0; x < (width / 8); x++ ) {
                src0_8 = _mem8_const(&src0[x*8]);
                src1_8 = _mem8_const(&src1[x*8]);
                _mem8(&dst[x*8]) = _itoll((uint32_t)_sub4((int32_t)_hill(src0_8), (int32_t)_hill(src1_8)),
                                          (uint32_t)_sub4((int32_t)_loll(src0_8), (int32_t)_loll(src1_8)));
            }
        } else {
            /* 3/8 = 0.375 cycles per pixel */
            for( x=0; x < (width / 8); x++ ) {
                src0_8 = _mem8_const(&src0[x*8]);
                src1_8 = _mem8_const(&src1[x*8]);
                mask = _dxpnd4(_dcmpgtu4(src0_8, src1_8));
                overflowing_result = _itoll((uint32_t)_sub4((int32_t)_hill(src0_8), (int32_t)_hill(src1_8)),
                                            (uint32_t)_sub4((int32_t)_loll(src0_8), (int32_t)_loll(src1_8)));
                _mem8(&dst[x*8]) = (uint64_t)overflowing_result & (uint64_t)mask;
            }
        }
    }
#endif

#if !defined(VXLIB_ALIGNED16_WIDTHS) && !defined(VXLIB_SUBTRACT_I8U_I8U_O8U_ALIGNED16_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 8 or 16 */
    /* 2 cycles per pixel */

    if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
        for( x*=8; x < width; x++ ) {
            dst[x] = src0[x] - src1[x];
        }
    } else {
        for( x*=8; x < width; x++ ) {
            int32_t overflowing_result4 = (int32_t)src0[x] - (int32_t)src1[x];
            dst[x] = (overflowing_result4 < 0) ? 0 : overflowing_result4;
        }
    }
#endif
}

VXLIB_STATUS VXLIB_subtract_i8u_i8u_o8u(const uint8_t src0[restrict],
                        const VXLIB_bufParams2D_t *src0_addr,
                        const uint8_t src1[restrict],
                        const VXLIB_bufParams2D_t *src1_addr,
                        uint8_t dst[restrict],
                        const VXLIB_bufParams2D_t *dst_addr,
                        uint16_t overflow_policy)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_SUBTRACT_I8U_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_subtract_i8u_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr, overflow_policy);
    if( status == VXLIB_SUCCESS )
#endif
    {


#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SUBTRACT_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           (src1_addr->dim_x == src1_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y))
#endif
        {
            VXLIB_subtract_i8u_i8u_o8u_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y, overflow_policy);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SUBTRACT_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[y * src0_addr->stride_y];
                const uint8_t   *src1_t = (const uint8_t *)&src1[y * src1_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[y * dst_addr->stride_y];

                VXLIB_subtract_i8u_i8u_o8u_core(src0_t, src1_t, dst_t, src0_addr->dim_x, overflow_policy);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_SUBTRACT_I8U_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_SUBTRACT_I8U_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_subtract_i8u_i8u_o8u_checkParams(const uint8_t src0[],
                                    const VXLIB_bufParams2D_t *src0_addr,
                                    const uint8_t src1[],
                                    const VXLIB_bufParams2D_t *src1_addr,
                                    const uint8_t dst[],
                                    const VXLIB_bufParams2D_t *dst_addr,
                                    uint16_t overflow_policy)
{
    VXLIB_STATUS    status;

    if((src0 == NULL) || (src1 == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src0_addr->dim_x != src1_addr->dim_x) ||
              (src0_addr->dim_x != dst_addr->dim_x) ||
              (src0_addr->dim_y != src1_addr->dim_y) ||
              (src0_addr->dim_y != dst_addr->dim_y) ||
              (src0_addr->stride_y < src0_addr->dim_x) ||
              (src1_addr->stride_y < src0_addr->dim_x) ||
              (dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
               (src1_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_SUBTRACT_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_SUBTRACT_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED16_WIDTHS) || defined(VXLIB_SUBTRACT_I8U_I8U_O8U_ALIGNED16_WIDTHS)
    else if(((src0_addr->dim_x % 16U) != 0) ||
            ((src1_addr->dim_x % 16U) != 0) ||
            ((dst_addr->dim_x % 16U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else if((overflow_policy != VXLIB_CONVERT_POLICY_WRAP) &&
             (overflow_policy != VXLIB_CONVERT_POLICY_SATURATE)) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

