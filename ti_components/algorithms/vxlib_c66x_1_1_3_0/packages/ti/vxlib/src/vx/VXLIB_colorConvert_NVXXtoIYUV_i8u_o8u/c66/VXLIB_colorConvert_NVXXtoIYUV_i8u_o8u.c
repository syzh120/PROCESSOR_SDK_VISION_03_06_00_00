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

#include "VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u.h"
#include "../../VXLIB_channelCopy_1to1_i8u_o8u/c66/VXLIB_channelCopy_1to1_i8u_o8u.h"

CODE_SECTION(VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_core(const uint8_t src1[restrict],
                                            uint8_t dst1[restrict],
                                            uint8_t dst2[restrict],
                                            int32_t width);

static void VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_core(const uint8_t src1[restrict],
                                            uint8_t dst1[restrict],
                                            uint8_t dst2[restrict],
                                            int32_t width)
{
    int32_t  x;
    int64_t  src1_8A, src1_8B;
    uint32_t dst0_4, dst1_4, dst2_4, dst3_4;
    uint64_t dst1_8, dst2_8;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)dst1 % 8U) == 0) &&
       (((uint32_t)dst2 % 8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time */
        /* 2/8 = 0.25 cycles per pixel */
        for( x=0; x < ((width / 8) * 8); x+=8 ) {
            src1_8A = _amem8_const(&src1[2*x]);
            src1_8B = _amem8_const(&src1[(2*x)+8]);

            dst0_4 = _packl4(_hill(src1_8A), _loll(src1_8A));
            dst1_4 = _packl4(_hill(src1_8B), _loll(src1_8B));

            dst2_4 = _packh4(_hill(src1_8A), _loll(src1_8A));
            dst3_4 = _packh4(_hill(src1_8B), _loll(src1_8B));

            dst2_8 = (uint64_t)_itoll(dst1_4, dst0_4);
            dst1_8 = (uint64_t)_itoll(dst3_4, dst2_4);

            _amem8(&dst1[x])     = (int64_t)dst1_8;
            _amem8(&dst2[x])     = (int64_t)dst2_8;
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time */
        /* 4/8 = 0.5 cycles per pixel */
        for( x=0; x < ((width / 8) * 8); x+=8 ) {
            src1_8A = _mem8_const(&src1[2*x]);
            src1_8B = _mem8_const(&src1[(2*x)+8]);

            dst0_4 = _packl4(_hill(src1_8A), _loll(src1_8A));
            dst1_4 = _packl4(_hill(src1_8B), _loll(src1_8B));

            dst2_4 = _packh4(_hill(src1_8A), _loll(src1_8A));
            dst3_4 = _packh4(_hill(src1_8B), _loll(src1_8B));

            dst2_8 = (uint64_t)_itoll(dst1_4, dst0_4);
            dst1_8 = (uint64_t)_itoll(dst3_4, dst2_4);

            _mem8(&dst1[x])     = (int64_t)dst1_8;
            _mem8(&dst2[x])     = (int64_t)dst2_8;
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_ALIGNED8_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 8 */
    /* 2 cycle per pixel */
    for(; x < width; x++ ) {
       dst1[x] = src1[(2*x)+1];
       dst2[x] = src1[2*x];
    }

#endif
}

VXLIB_STATUS    VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u(const uint8_t src0[restrict],
                                  const VXLIB_bufParams2D_t * src0_addr,
                                  const uint8_t src1[restrict],
                                  const VXLIB_bufParams2D_t * src1_addr,
                                  uint8_t dst0[restrict],
                                  const VXLIB_bufParams2D_t * dst0_addr,
                                  uint8_t dst1[restrict],
                                  const VXLIB_bufParams2D_t * dst1_addr,
                                  uint8_t dst2[restrict],
                                  const VXLIB_bufParams2D_t * dst2_addr,
                                  uint8_t u_pix)
{
    VXLIB_STATUS     status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, 
                 dst0, dst0_addr, dst1, dst1_addr, dst2, dst2_addr, u_pix);
    if( status == VXLIB_SUCCESS )
#endif
    {
        status = VXLIB_channelCopy_1to1_i8u_o8u(src0, src0_addr, dst0, dst0_addr);

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src1_addr->dim_x == src1_addr->stride_y) &&
           (dst1_addr->dim_x == dst1_addr->stride_y) &&
           (dst2_addr->dim_x == dst2_addr->stride_y))
#endif
        {
            if (u_pix == 1U) {
                VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_core(src1, dst1, dst2, (src1_addr->dim_x * src1_addr->dim_y) / 2);
            }
            else {
                VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_core(src1, dst2, dst1, (src1_addr->dim_x * src1_addr->dim_y) / 2);
            }
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t          y;

            for( y=0; y < dst1_addr->dim_y; y++ ) {

                const uint8_t   *src1_t = (const uint8_t *)&src1[y * src1_addr->stride_y];
                uint8_t         *dsta_t;
                uint8_t         *dstb_t;

                if (u_pix == 1U) {
                    dsta_t  = (uint8_t *)&dst1[y * dst1_addr->stride_y];
                    dstb_t  = (uint8_t *)&dst2[y * dst2_addr->stride_y];
                }
                else {
                    dsta_t  = (uint8_t *)&dst2[y * dst2_addr->stride_y];
                    dstb_t  = (uint8_t *)&dst1[y * dst1_addr->stride_y];
                }

                VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_core( src1_t, dsta_t, dstb_t, dst1_addr->dim_x );
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_checkParams(const uint8_t src0[],
                                           const VXLIB_bufParams2D_t *src0_addr,
                                           const uint8_t src1[],
                                           const VXLIB_bufParams2D_t *src1_addr,
                                           const uint8_t dst0[],
                                           const VXLIB_bufParams2D_t *dst0_addr,
                                           const uint8_t dst1[],
                                           const VXLIB_bufParams2D_t *dst1_addr,
                                           const uint8_t dst2[],
                                           const VXLIB_bufParams2D_t *dst2_addr,
                                           uint8_t u_pix)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src0 == NULL) || (src1 == NULL) || (dst0 == NULL) || (dst1 == NULL) || (dst2 == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src0_addr->dim_x != dst0_addr->dim_x) ||
               (src0_addr->dim_y != dst0_addr->dim_y) ||
               (src0_addr->stride_y < src0_addr->dim_x) ||
               (src1_addr->stride_y < src1_addr->dim_x) ||
               (dst0_addr->stride_y < dst0_addr->dim_x) ||
               (dst1_addr->stride_y < dst1_addr->dim_x) ||
               (src0_addr->dim_x != src1_addr->dim_x) ||
               (src0_addr->dim_y != (2*src1_addr->dim_y)) ||
               (dst0_addr->dim_x != (2*dst1_addr->dim_x)) ||
               (dst0_addr->dim_y != (2*dst1_addr->dim_y)) ||
               (dst1_addr->dim_x != dst2_addr->dim_x) ||
               (dst1_addr->dim_y != dst2_addr->dim_y) ||
               ((src0_addr->dim_x % 2U) != 0) ||
               ((dst0_addr->dim_x % 2U) != 0)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
              (src1_addr->data_type != VXLIB_UINT8) ||
              (dst0_addr->data_type != VXLIB_UINT8) ||
              (dst1_addr->data_type != VXLIB_UINT8) ||
              (dst2_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if( (uint32_t)u_pix > 1U ) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (dst0_addr->dim_x != dst0_addr->stride_y) ||
            (dst1_addr->dim_x != dst1_addr->stride_y) ||
            (dst2_addr->dim_x != dst2_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)dst0 % 8U) != 0) ||
            (((uint32_t)dst1 % 8U) != 0) ||
            (((uint32_t)dst2 % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((dst0_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_COLORCONVERT_NVXXTOIYUV_I8U_O8U_ALIGNED8_WIDTHS)
    else if(((src0_addr->dim_x % 8U) != 0) ||
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
