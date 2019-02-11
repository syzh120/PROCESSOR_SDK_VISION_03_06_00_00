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

#include "VXLIB_colorConvert_YUVXtoNV12_i8u_o8u.h"
#include "../../VXLIB_channelExtract_1of2_i8u_o8u/c66/VXLIB_channelExtract_1of2_i8u_o8u.h"

CODE_SECTION(VXLIB_colorConvert_YUVXtoNV12_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_noshift, ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_shift,   ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_noshift(const uint8_t src[restrict],
                                               const uint8_t src_y[restrict],
                                               uint8_t dst1[restrict],
                                               int32_t width);

static void VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_shift(const uint8_t src[restrict],
                                               const uint8_t src_y[restrict],
                                               uint8_t dst1[restrict],
                                               int32_t width);

static void VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_noshift(const uint8_t src[restrict],
                                               const uint8_t src_y[restrict],
                                               uint8_t dst1[restrict],
                                               int32_t width)
{
    int32_t    x;
    int64_t    src8_0, src8_1, src8_0_y, src8_1_y;
    int64_t    avg_0, avg_1;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src % 8U)   == 0) &&
       (((uint32_t)src_y % 8U) == 0) &&
       (((uint32_t)dst1 % 8U)  == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time */
        /* 5/16 = 0.3125 cycles per pixel */
        #pragma MUST_ITERATE(,,2)
        #pragma UNROLL(2)
        for( x=0; x < ((width / 16) * 2); x++ ) {

            src8_0   = _amem8_const(&src[(x*16)]);
            src8_1   = _amem8_const(&src[(x*16)+8]);
            src8_0_y = _amem8_const(&src_y[(x*16)]);
            src8_1_y = _amem8_const(&src_y[(x*16)+8]);

            /* take the average */
            avg_0 = _davgnru4(src8_0, src8_0_y);
            avg_1 = _davgnru4(src8_1, src8_1_y);

            _amem8(&dst1[x*8]) = _dpackl4(  _itoll( _hill(avg_1), _hill(avg_0) ),
                                     _itoll( _loll(avg_1), _loll(avg_0) ) );
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {

        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time */
        /* 5/8 = 0.625 cycles per pixel */
        for( x=0; x < (width / 8); x++ ) {

            src8_0   = _mem8_const(&src[(x*16)]);
            src8_1   = _mem8_const(&src[(x*16)+8]);
            src8_0_y = _mem8_const(&src_y[(x*16)]);
            src8_1_y = _mem8_const(&src_y[(x*16)+8]);

            /* take the average */
            avg_0 = _davgnru4(src8_0, src8_0_y);
            avg_1 = _davgnru4(src8_1, src8_1_y);

            _mem8(&dst1[x*8]) = _dpackl4(  _itoll( _hill(avg_1), _hill(avg_0) ),
                                     _itoll( _loll(avg_1), _loll(avg_0) ) );
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_WIDTHS)

    /* Case 3: Process remaining pixels beyond multiple of 8 or 16 */
    /* 3 cycles per pixel */
    for(x*=8; x < width; x+=2 ) {
        dst1[x] = (src[(x*2)] + src_y[(x*2)]) >> 1;
        dst1[x+1] = (src[(x*2)+2] + src_y[(x*2)+2]) >> 1;
    }

#endif
}

static void VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_shift(const uint8_t src[restrict],
                                               const uint8_t src_y[restrict],
                                               uint8_t dst1[restrict],
                                               int32_t width)
{
    int32_t    x;
    int64_t src8_0, src8_1, src8_0_y, src8_1_y;
    int64_t avg_0, avg_1;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src % 8U)   == 0) &&
       (((uint32_t)src_y % 8U) == 0) &&
       (((uint32_t)dst1 % 8U)  == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time */
        /* 5/16 = 0.3125 cycles per pixel */
        #pragma MUST_ITERATE(,,2)
        #pragma UNROLL(2)
        for( x=0; x < ((width / 16) * 2); x++ ) {

            src8_0   = _dshru2(_amem8_const(&src[(x*16)+0]), 8U);
            src8_1   = _dshru2(_amem8_const(&src[(x*16)+8]), 8U);
            src8_0_y = _dshru2(_amem8_const(&src_y[(x*16)+0]), 8U);
            src8_1_y = _dshru2(_amem8_const(&src_y[(x*16)+8]), 8U);

            /* take the average */
            avg_0 = _davgnru4(src8_0, src8_0_y);
            avg_1 = _davgnru4(src8_1, src8_1_y);

            _amem8(&dst1[x*8]) = _dpackl4(  _itoll( _hill(avg_1), _hill(avg_0) ),
                                     _itoll( _loll(avg_1), _loll(avg_0) ) );
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {

        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time */
        /* 5/8 = 0.625 cycles per pixel */
        for( x=0; x < (width / 8); x++ ) {

            src8_0   = _dshru2(_mem8_const(&src[(x*16)+0]), 8U);
            src8_1   = _dshru2(_mem8_const(&src[(x*16)+8]), 8U);
            src8_0_y = _dshru2(_mem8_const(&src_y[(x*16)+0]), 8U);
            src8_1_y = _dshru2(_mem8_const(&src_y[(x*16)+8]), 8U);

            /* take the average */
            avg_0 = _davgnru4(src8_0, src8_0_y);
            avg_1 = _davgnru4(src8_1, src8_1_y);

            _mem8(&dst1[x*8]) = _dpackl4(  _itoll( _hill(avg_1), _hill(avg_0) ),
                                     _itoll( _loll(avg_1), _loll(avg_0) ) );
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_WIDTHS)

    /* Case 3: Process remaining pixels beyond multiple of 8 or 16 */
    /* 3 cycles per pixel */
    for(x*=8; x < width; x+=2 ) {
        dst1[x] = (src[(x*2)+1] + src_y[(x*2)+1]) >> 1;
        dst1[x+1] = (src[(x*2)+3] + src_y[(x*2)+3]) >> 1;
    }

#endif
}

VXLIB_STATUS    VXLIB_colorConvert_YUVXtoNV12_i8u_o8u(const uint8_t src[restrict],
                                  const VXLIB_bufParams2D_t * src_addr,
                                  uint8_t dst0[restrict],
                                  const VXLIB_bufParams2D_t * dst0_addr,
                                  uint8_t dst1[restrict],
                                  const VXLIB_bufParams2D_t * dst1_addr,
                                  uint8_t x_value)
{
    int32_t          y;
    VXLIB_STATUS     status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_checkParams(src, src_addr, dst0, dst0_addr, dst1, dst1_addr, x_value);
    if( status == VXLIB_SUCCESS )
#endif
    {
        const uint8_t   *src_t;
        const uint8_t   *src_y_t;
        uint8_t         *dst1_t;

        if (x_value == 0U)
        {
            status = VXLIB_channelExtract_1of2_i8u_o8u(src, src_addr, dst0, dst0_addr, 0U);
            for( y=0; (uint32_t)y < dst1_addr->dim_y; y++ ) {

                src_t = (const uint8_t *)&src[ ((2*y) * src_addr->stride_y)];
                src_y_t = (const uint8_t *)&src[ ((2*y)+1) * src_addr->stride_y];
                dst1_t  = (uint8_t *)&dst1[ (y * dst1_addr->stride_y)];

                VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_shift(src_t, src_y_t, dst1_t, dst1_addr->dim_x);
            }
        }
        else
        {
            status = VXLIB_channelExtract_1of2_i8u_o8u(src, src_addr, dst0, dst0_addr, 1U);
            for( y=0; (uint32_t)y < dst1_addr->dim_y; y++ ) {

                src_t = (const uint8_t *)&src[ ((2*y) * src_addr->stride_y)];
                src_y_t = (const uint8_t *)&src[ ((2*y)+1) * src_addr->stride_y];
                dst1_t  = (uint8_t *)&dst1[ (y * dst1_addr->stride_y)];

                VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_core_noshift(src_t, src_y_t, dst1_t, dst1_addr->dim_x);
            }
        }

    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_colorConvert_YUVXtoNV12_i8u_o8u_checkParams(const uint8_t src[],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst0[],
                                           const VXLIB_bufParams2D_t *dst0_addr,
                                           const uint8_t dst1[],
                                           const VXLIB_bufParams2D_t *dst1_addr,
                                           uint8_t x_value)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst0 == NULL) || (dst1 == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src_addr->dim_x != dst0_addr->dim_x) ||
               (src_addr->dim_y != dst0_addr->dim_y) ||
               (src_addr->stride_y < (2U*src_addr->dim_x)) ||
               (dst0_addr->stride_y < dst0_addr->dim_x) ||
               (dst1_addr->stride_y < dst1_addr->dim_x) ||
               (dst0_addr->dim_x != dst1_addr->dim_x) ||
               (dst0_addr->dim_y != (2*dst1_addr->dim_y)) ||
               (dst0_addr->stride_y < dst0_addr->dim_x) ||
               (dst1_addr->stride_y < dst1_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
              (dst0_addr->data_type != VXLIB_UINT8) ||
              (dst1_addr->data_type != VXLIB_UINT8) ) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if (x_value > 1U) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
            (dst0_addr->dim_x != dst0_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src % 8U) != 0) ||
            (((uint32_t)dst0 % 8U) != 0) ||
            (((uint32_t)dst1 % 8U) != 0) ||
            ((src_addr->stride_y % 8U) != 0) ||
            ((dst0_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_COLORCONVERT_YUVXTONV12_I8U_O8U_ALIGNED8_WIDTHS)
    else if(((src_addr->dim_x % 8U) != 0) ||
            ((dst0_addr->dim_x % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
