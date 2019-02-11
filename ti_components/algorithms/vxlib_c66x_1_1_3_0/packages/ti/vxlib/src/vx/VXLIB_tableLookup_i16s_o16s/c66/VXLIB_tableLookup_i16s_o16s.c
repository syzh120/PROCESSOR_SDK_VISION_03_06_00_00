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

#include "VXLIB_tableLookup_i16s_o16s.h"

CODE_SECTION(VXLIB_tableLookup_i16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_tableLookup_i16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_tableLookup_i16s_o16s_checkParams,  ".text:optimized")

static void VXLIB_tableLookup_i16s_o16s_core(const int16_t src[restrict],
                            int16_t dst[restrict],
                            const int16_t lut[restrict],
                            int32_t width,
                            size_t count);

static void VXLIB_tableLookup_i16s_o16s_core(const int16_t src[restrict],
                            int16_t dst[restrict],
                            const int16_t lut[restrict],
                            int32_t width,
                            size_t count)
{
    int32_t    x;
    int64_t in4_1;
    int16_t out0, out1, out2, out3;
    uint32_t out01, out23;
    int64_t ones4 = 0x0001000100010001;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_TABLELOOKUP_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    if((((uint32_t)src % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        __x128_t in4_2;

        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time */
        /* 3/4 = 0.75 cycles per pixel */
        for( x=0; x < (width / 4); x++ ) {
            in4_1 = _amem8_const(&src[x*4]);
            in4_2 = _dmpy2(in4_1, ones4);
            out0 = lut[(int32_t)_get32_128(in4_2, 0)];
            out1 = lut[(int32_t)_get32_128(in4_2, 1U)];
            out2 = lut[(int32_t)_get32_128(in4_2, 2U)];
            out3 = lut[(int32_t)_get32_128(in4_2, 3U)];
            out01 = _pack2((uint32_t)out1, (uint32_t)out0);
            out23 = _pack2((uint32_t)out3, (uint32_t)out2);
            _amem8(&dst[x*4]) = _itoll(out23, out01);
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_TABLELOOKUP_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    else {
        int32_t ones2 = (int32_t)_loll(ones4);
        int64_t lo, hi;

        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time */
        /* 4/4 = 1.00 cycles per pixel */
        for( x=0; x < (width / 4); x++ ) {
            in4_1 = _mem8_const(&src[x*4]);
            lo = _mpy2ll((int32_t)_loll(in4_1), ones2);
            hi = _mpy2ll((int32_t)_hill(in4_1), ones2);
            out0 = lut[(int32_t)_loll(lo)];
            out1 = lut[(int32_t)_hill(lo)];
            out2 = lut[(int32_t)_loll(hi)];
            out3 = lut[(int32_t)_hill(hi)];
            out01 = _pack2((uint32_t)out1, (uint32_t)out0);
            out23 = _pack2((uint32_t)out3, (uint32_t)out2);
            _mem8(&dst[x*4]) = _itoll(out23, out01);
        }
    }
#endif

#if !defined(VXLIB_ALIGNED4_WIDTHS) && !defined(VXLIB_TABLELOOKUP_I16S_O16S_ALIGNED4_WIDTHS)

    /* Case 3: Process remaining pixels beyond multiple of 4 */
    /* 2 cycles per pixel */
    for(x*=4; x < width; x++ ) {
        dst[x] = lut[(int16_t)src[x]];
    }

#endif

}

VXLIB_STATUS VXLIB_tableLookup_i16s_o16s(const int16_t src[restrict],
                        const VXLIB_bufParams2D_t *src_addr,
                        int16_t dst[restrict],
                        const VXLIB_bufParams2D_t *dst_addr,
                        const int16_t lut[restrict],
                        uint32_t count,
                        uint16_t offset)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_TABLELOOKUP_I16S_O16S_CHECK_PARAMS)
    status = VXLIB_tableLookup_i16s_o16s_checkParams(src, src_addr, dst, dst_addr, lut, count, offset);
    if( status == VXLIB_SUCCESS )
#endif
    {
        const int16_t *pLut = &lut[offset];

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_TABLELOOKUP_I16S_O16S_EQUAL_WIDTH_STRIDE)
        if(((src_addr->dim_x * 2) == src_addr->stride_y) &&
           ((dst_addr->dim_x * 2) == dst_addr->stride_y))
#endif
        {
            VXLIB_tableLookup_i16s_o16s_core(src, dst, pLut, src_addr->dim_x * src_addr->dim_y, count);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_TABLELOOKUP_I16S_O16S_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src_addr->dim_y; y++ ) {

                const int16_t   *src_t = (const int16_t *)&src[y * (src_addr->stride_y / 2)];
                int16_t         *dst_t  = (int16_t *)&dst[y * (dst_addr->stride_y / 2)];

                VXLIB_tableLookup_i16s_o16s_core(src_t, dst_t, pLut, src_addr->dim_x, count);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_TABLELOOKUP_I16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_TABLELOOKUP_I16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_tableLookup_i16s_o16s_checkParams(const int16_t src[],
                                    const VXLIB_bufParams2D_t *src_addr,
                                    const int16_t dst[],
                                    const VXLIB_bufParams2D_t *dst_addr,
                                    const int16_t lut[],
                                    uint32_t count,
                                    uint16_t offset)
{
    int32_t         i, j, srcIndex, lutIndex;
    VXLIB_STATUS    status;

    if((src == NULL) || (dst == NULL) || (lut == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x != dst_addr->dim_x) ||
              (src_addr->dim_y != dst_addr->dim_y) ||
              (src_addr->stride_y < (src_addr->dim_x * 2)) ||
              (dst_addr->stride_y < (dst_addr->dim_x * 2))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((count > 65536U) || ((uint32_t)offset >= count) ) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_TABLELOOKUP_I16S_O16S_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_TABLELOOKUP_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED4_WIDTHS) || defined(VXLIB_TABLELOOKUP_I16S_O16S_ALIGNED4_WIDTHS)
    else if(((src_addr->dim_x % 4U) != 0) ||
            ((dst_addr->dim_x % 4U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    if( status == VXLIB_SUCCESS ) {
        for( i = 0; i < src_addr->dim_y; i++ ) {
            for( j = 0; j < src_addr->dim_x; j++ ) {
                srcIndex = (i * (src_addr->stride_y / 2)) + j;
                lutIndex = (int32_t)offset + (int32_t)src[srcIndex];
                if((lutIndex < 0) || ((uint32_t)lutIndex >= count) ) {
                    status = VXLIB_ERR_INVALID_DIMENSION;
                    break;
                }
            }
        }
    }
    return (status);
}

#endif

