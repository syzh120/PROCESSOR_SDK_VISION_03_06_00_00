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

#include "VXLIB_subtract_i16s_i16s_o16s.h"

CODE_SECTION(VXLIB_subtract_i16s_i16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_subtract_i16s_i16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_subtract_i16s_i16s_o16s_checkParams,  ".text:optimized")

static void VXLIB_subtract_i16s_i16s_o16s_core(const int16_t src0[restrict],
                             const int16_t src1[restrict],
                             int16_t dst[restrict],
                             int32_t width,
                             uint16_t overflow_policy);

static void VXLIB_subtract_i16s_i16s_o16s_core(const int16_t src0[restrict],
                             const int16_t src1[restrict],
                             int16_t dst[restrict],
                             int32_t width,
                             uint16_t overflow_policy)
{
    int32_t    x;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_SUBTRACT_I16S_I16S_O16S_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0) &&
       (((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)dst %  8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 3/8 = 0.375 cycles per pixel */
        _nassert(((uint32_t)src0 % 8U) == 0);
        _nassert(((uint32_t)src1 % 8U) == 0);
        _nassert(((uint32_t)dst % 8U) == 0);
        if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
            #pragma MUST_ITERATE(0,,8)

            for( x=0; x < ((width / 8) * 8); x++ ) {
                dst[x] = src0[x] - src1[x];
            }
        } else {
            #pragma MUST_ITERATE(0,,8)

            for( x=0; x < ((width / 8) * 8); x++ ) {
                dst[x] = (int16_t)_ssub2((int32_t)src0[x], (int32_t)src1[x]);
            }
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_SUBTRACT_I16S_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time*/
        /* 3/4 = 0.75 cycles per pixel */
        if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
            #pragma MUST_ITERATE(0,,4)

            for( x=0; x < ((width / 4) * 4); x++ ) {
                dst[x] = src0[x] - src1[x];
            }
        } else {
            #pragma MUST_ITERATE(0,,4)

            for( x=0; x < ((width / 4) * 4); x++ ) {
                dst[x] = (int16_t)_ssub2((int32_t)src0[x], (int32_t)src1[x]);
            }
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_SUBTRACT_I16S_I16S_O16S_ALIGNED8_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 4 or 8 */
    /* 2 cycles per pixel */
    if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
        for(; x < width; x++ ) {
            dst[x] = src0[x] - src1[x];
        }
    } else {
        for(; x < width; x++ ) {
            dst[x] = (int16_t)_ssub2((int32_t)src0[x], (int32_t)src1[x]);
        }
    }
#endif

}

VXLIB_STATUS VXLIB_subtract_i16s_i16s_o16s(const int16_t src0[restrict],
                         const VXLIB_bufParams2D_t *src0_addr,
                         const int16_t src1[restrict],
                         const VXLIB_bufParams2D_t *src1_addr,
                         int16_t dst[restrict],
                         const VXLIB_bufParams2D_t *dst_addr,
                         uint16_t overflow_policy)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_SUBTRACT_I16S_I16S_O16S_CHECK_PARAMS)
    status = VXLIB_subtract_i16s_i16s_o16s_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr, overflow_policy);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SUBTRACT_I16S_I16S_O16S_EQUAL_WIDTH_STRIDE)
        if(((2 * src0_addr->dim_x) == src0_addr->stride_y) &&
           ((2 * src1_addr->dim_x) == src1_addr->stride_y) &&
           ((2 * dst_addr->dim_x) == dst_addr->stride_y))
#endif
        {
            VXLIB_subtract_i16s_i16s_o16s_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y, overflow_policy);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_SUBTRACT_I16S_I16S_O16S_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {
                const int16_t   *src0_t = (const int16_t *)&src0[ y * (src0_addr->stride_y / 2) ];
                const int16_t   *src1_t = (const int16_t *)&src1[ y * (src1_addr->stride_y / 2) ];
                int16_t         *dst_t  = (int16_t *)&dst[ y * (dst_addr->stride_y / 2) ];

                VXLIB_subtract_i16s_i16s_o16s_core(src0_t, src1_t, dst_t, src0_addr->dim_x, overflow_policy);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_SUBTRACT_I16S_I16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_SUBTRACT_I16S_I16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_subtract_i16s_i16s_o16s_checkParams(const int16_t src0[],
                                     const VXLIB_bufParams2D_t *src0_addr,
                                     const int16_t src1[],
                                     const VXLIB_bufParams2D_t *src1_addr,
                                     const int16_t dst[],
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
    } else if((src0_addr->data_type != VXLIB_INT16) ||
               (src1_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_SUBTRACT_I16S_I16S_O16S_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_SUBTRACT_I16S_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_SUBTRACT_I16S_I16S_O16S_ALIGNED8_WIDTHS)
    else if(((src0_addr->dim_x % 8U) != 0) ||
            ((src1_addr->dim_x % 8U) != 0) ||
            ((dst_addr->dim_x % 8U) != 0)) {
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

