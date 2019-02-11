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

#include "VXLIB_colorConvert_RGBXtoNV12_i8u_o8u.h"
#include "../../VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u/c66/VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u.h"

CODE_SECTION(VXLIB_colorConvert_RGBXtoNV12_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_core(const uint8_t tmp1_line1[restrict],
                                               const uint8_t tmp1_line2[restrict],
                                               const uint8_t tmp2_line1[restrict],
                                               const uint8_t tmp2_line2[restrict],
                                               uint8_t dst1[restrict],
                                               int32_t width,
                                               int32_t y);

static void VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_core(const uint8_t tmp1_line1[restrict],
                                               const uint8_t tmp1_line2[restrict],
                                               const uint8_t tmp2_line1[restrict],
                                               const uint8_t tmp2_line2[restrict],
                                               uint8_t dst1[restrict],
                                               int32_t width,
                                               int32_t y)
{
    int32_t x;
    int64_t src8_1, src8_1_y, src8_2, src8_2_y;
    uint64_t src8_1_clear, src8_1_y_clear, src8_2_clear, src8_2_y_clear;
    uint64_t src8_1_shift_clear, src8_1_y_shift_clear, src8_2_shift_clear, src8_2_y_shift_clear;
    int64_t sum_intermediate_1, sum_intermediate_2, sum2_intermediate_1, sum2_intermediate_2;
    uint64_t average_1, average_2;

    /* Case 1: SIMD of 8 pixels at a time */
    /* 7/8 = 0.875 cycles per pixel */
    for( x=0; x < (width / 8); x++ ) {

        /* Load values */
        src8_1   = _mem8_const(&tmp1_line1[(x*8)]);
        src8_1_y = _mem8_const(&tmp1_line2[(x*8)]);
        src8_2   = _mem8_const(&tmp2_line1[(x*8)]);
        src8_2_y = _mem8_const(&tmp2_line2[(x*8)]);

        /* Shift the second byte of each pair and clear to prepare for adding */
        src8_1_shift_clear   = (uint64_t)_itoll(_shrmb(0, _hill(src8_1)),   _shrmb( _hill(src8_1), _loll(src8_1)))     & 0x00FF00FF00FF00FFU;
        src8_1_y_shift_clear = (uint64_t)_itoll(_shrmb(0, _hill(src8_1_y)), _shrmb( _hill(src8_1_y), _loll(src8_1_y))) & 0x00FF00FF00FF00FFU;
        src8_2_shift_clear   = (uint64_t)_itoll(_shrmb(0, _hill(src8_2)),   _shrmb( _hill(src8_2), _loll(src8_2)))     & 0x00FF00FF00FF00FFU;
        src8_2_y_shift_clear = (uint64_t)_itoll(_shrmb(0, _hill(src8_2_y)), _shrmb( _hill(src8_2_y), _loll(src8_2_y))) & 0x00FF00FF00FF00FFU;

        /* Clear second byte to prepare for adding */
        src8_1_clear   = (uint64_t)src8_1   & 0x00FF00FF00FF00FFU;
        src8_1_y_clear = (uint64_t)src8_1_y & 0x00FF00FF00FF00FFU;
        src8_2_clear   = (uint64_t)src8_2   & 0x00FF00FF00FF00FFU;
        src8_2_y_clear = (uint64_t)src8_2_y & 0x00FF00FF00FF00FFU;

        /* Intermediate adding */
        sum_intermediate_1 = _dadd2((int64_t)src8_1_clear, (int64_t)src8_1_y_clear);
        sum_intermediate_2 = _dadd2((int64_t)src8_1_shift_clear, (int64_t)src8_1_y_shift_clear);

        sum2_intermediate_1 = _dadd2((int64_t)src8_2_clear, (int64_t)src8_2_y_clear);
        sum2_intermediate_2 = _dadd2((int64_t)src8_2_shift_clear, (int64_t)src8_2_y_shift_clear);

        /* Final sum then shift for average */
        average_1 = (uint64_t)_dshru2(_dadd2(sum_intermediate_1, sum_intermediate_2), 2U) & 0x00FF00FF00FF00FFU;
        /* Combines a shift right by 2 for average and a shift left by 2 8 for correct packing */
        average_2 = (uint64_t)_dshl2(_dadd2(sum2_intermediate_1, sum2_intermediate_2), 6U) & 0xFF00FF00FF00FF00U;

        /* pack these values */
        _mem8(&dst1[x*8]) = average_1 | average_2;
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_ALIGNED8_WIDTHS)

    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 5/2 = 2.5 cycles per pixel */
    for(x*=8; x < (width); x+=2 ) {
        dst1[x] = (tmp1_line1[x] + tmp1_line1[x+1] + tmp1_line2[x] + tmp1_line2[x+1]) >> 2;
        dst1[(x)+1] = (tmp2_line1[x] + tmp2_line1[x+1] + tmp2_line2[x] + tmp2_line2[x+1]) >> 2;
    }

#endif
}

VXLIB_STATUS    VXLIB_colorConvert_RGBXtoNV12_i8u_o8u(const uint8_t src[restrict],
                                  const VXLIB_bufParams2D_t * src_addr,
                                  uint8_t dst0[restrict],
                                  const VXLIB_bufParams2D_t * dst0_addr,
                                  uint8_t dst1[restrict],
                                  const VXLIB_bufParams2D_t * dst1_addr,
                                  uint8_t scratch[restrict],
                                  uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    int32_t  y;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_checkParams(src, src_addr, dst0, dst0_addr, dst1, dst1_addr, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        const uint8_t   *src_t;
        uint8_t         *dst0_t;
        uint8_t         *dst1_t;
        uint8_t         *tmp_dst1_line1;
        uint8_t         *tmp_dst1_line2;
        uint8_t         *tmp_dst2_line1;
        uint8_t         *tmp_dst2_line2;

        VXLIB_bufParams2D_t src_params, dst0_params, dst1_params;

        src_params.dim_x = src_addr->dim_x;
        src_params.dim_y = 1;
        src_params.stride_y = src_addr->stride_y;
        src_params.data_type = VXLIB_UINT32;

        dst0_params.dim_x = dst0_addr->dim_x;
        dst0_params.dim_y = 1;
        dst0_params.stride_y = dst0_addr->dim_x;
        dst0_params.data_type = VXLIB_UINT8;

        dst1_params.dim_x = dst1_addr->dim_x;
        dst1_params.dim_y = 1;
        dst1_params.stride_y = dst1_addr->dim_x;
        dst1_params.data_type = VXLIB_UINT8;

        for( y=0; y < (dst0_addr->dim_y); y+=2 ) {

            src_t   = (const uint8_t *)&src[ (y * src_addr->stride_y)];
            dst0_t  = (uint8_t *)&dst0[ (y * dst0_addr->stride_y)];
            dst1_t  = (uint8_t *)&dst1[ (y/2) * dst1_addr->stride_y];
            tmp_dst1_line1    =  (uint8_t *)&scratch[ dst0_addr->dim_x * 0 * sizeof(uint8_t)];
            tmp_dst1_line2    =  (uint8_t *)&scratch[ dst0_addr->dim_x * 1 * sizeof(uint8_t)];
            tmp_dst2_line1    =  (uint8_t *)&scratch[ dst0_addr->dim_x * 2 * sizeof(uint8_t)];
            tmp_dst2_line2    =  (uint8_t *)&scratch[ dst0_addr->dim_x * 3 * sizeof(uint8_t)];

            status = VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u(src_t, &src_params, dst0_t, &dst0_params, tmp_dst1_line1, &dst1_params, tmp_dst2_line1, &dst1_params);

            if( status == VXLIB_SUCCESS )
            {
                src_t   = (const uint8_t *)&src[ ((y+1) * src_addr->stride_y)];
                dst0_t  = (uint8_t *)&dst0[ ((y+1) * dst0_addr->stride_y)];

                status = VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u(src_t, &src_params, dst0_t, &dst0_params, tmp_dst1_line2, &dst1_params, tmp_dst2_line2, &dst1_params);
            }

            VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_core(tmp_dst1_line1, tmp_dst1_line2,
                                                       tmp_dst2_line1, tmp_dst2_line2,
                                                       dst1_t, dst0_addr->dim_x, y);
            if ( status != VXLIB_SUCCESS)
            {
                break;
            }
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_colorConvert_RGBXtoNV12_i8u_o8u_checkParams(const uint8_t src[],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst0[],
                                           const VXLIB_bufParams2D_t *dst0_addr,
                                           const uint8_t dst1[],
                                           const VXLIB_bufParams2D_t *dst1_addr,
                                           const uint8_t scratch[],
                                           const uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst0 == NULL) || (dst1 == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src_addr->dim_x != dst0_addr->dim_x) ||
                (src_addr->dim_y != dst0_addr->dim_y) ||
                (src_addr->stride_y < (4*src_addr->dim_x)) ||
                (dst0_addr->stride_y < dst0_addr->dim_x) ||
                (dst1_addr->stride_y < dst0_addr->dim_x) ||
                (dst0_addr->dim_x != dst1_addr->dim_x) ||
                (dst0_addr->dim_y != (2*dst1_addr->dim_y)) ||
                (dst0_addr->stride_y < dst0_addr->dim_x) ||
                (dst1_addr->stride_y < dst1_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT32) ||
              (dst0_addr->data_type != VXLIB_UINT8) ||
              (dst1_addr->data_type != VXLIB_UINT8) ) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(scratch_size < (4U*dst0_addr->stride_y) ) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_COLORCONVERT_RGBXTONV12_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((3 * src_addr->dim_x != src_addr->stride_y) ||
             (dst0_addr->dim_x != dst0_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_COLORCONVERT_RGBXTONV12_ALIGNED8_WIDTHS)
    else if((dst0_addr->dim_x % 8U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}
#endif

