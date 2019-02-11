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

#include "VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u.h"
#include "../../VXLIB_channelCopy_1to1_i8u_o8u/c66/VXLIB_channelCopy_1to1_i8u_o8u.h"

CODE_SECTION(VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_core(const uint8_t src1[restrict],
                                            const uint8_t src2[restrict],
                                            uint8_t dst1[restrict],
                                            uint8_t dst2[restrict],
                                            uint8_t dst1_y[restrict],
                                            uint8_t dst2_y[restrict],
                                            int32_t width);

static void VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_core(const uint8_t src1[restrict],
                                            const uint8_t src2[restrict],
                                            uint8_t dst1[restrict],
                                            uint8_t dst2[restrict],
                                            uint8_t dst1_y[restrict],
                                            uint8_t dst2_y[restrict],
                                            int32_t width)
{
    int32_t    x;
    int64_t src1_8, src2_8;
    int64_t src1_4A, src1_4C, src1_4B, src1_4D, src2_4A, src2_4B, src2_4C, src2_4D;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)src2 % 8U) == 0) &&
       (((uint32_t)dst1 % 8U) == 0) &&
       (((uint32_t)dst2 % 8U) == 0) &&
       (((uint32_t)dst1_y % 8U) == 0) &&
       (((uint32_t)dst2_y % 8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 16 output pixels at a time*/
        /* 5/16 = 0.3125 cycles per pixel */
        for( x=0; x < ((width / 8) * 8); x+=8 ) {

            /* Fetch from input */
            src1_8 = _amem8_const(&src1[x]);
            src2_8 = _amem8_const(&src2[x]);

            /* Unpack all 8 bit values into 16-bit values, with top bits == 0 */
            src1_4A = _unpkbu4(_loll(src1_8));
            src1_4B = _unpkbu4(_hill(src1_8));
            src2_4A = _unpkbu4(_loll(src2_8));
            src2_4B = _unpkbu4(_hill(src2_8));

            /* Shift src1 and src2 up by 8 to prepare for packing via OR */
            src1_4C = _itoll(_hill(src1_4A) << 8U, _rotl(_loll(src1_4A), 8U));
            src1_4D = _itoll(_hill(src1_4B) << 8U, _rotl(_loll(src1_4B), 8U));
            src2_4C = _itoll(_hill(src2_4A) << 8U, _rotl(_loll(src2_4A), 8U));
            src2_4D = _itoll(_hill(src2_4B) << 8U, _rotl(_loll(src2_4B), 8U));

            /* OR shifted results together to output combined results */
            _amem8(&dst1[2*x])        = (uint64_t)src1_4C | (uint64_t)src1_4A;
            _amem8(&dst1[(2*x)+8])    = (uint64_t)src1_4D | (uint64_t)src1_4B;
            _amem8(&dst1_y[2*x])      = (uint64_t)src1_4C | (uint64_t)src1_4A;
            _amem8(&dst1_y[(2*x)+8])  = (uint64_t)src1_4D | (uint64_t)src1_4B;

            /* Same thing on dst2 */
            _amem8(&dst2[2*x])          = (uint64_t)src2_4C | (uint64_t)src2_4A;
            _amem8(&dst2[(2*x)+8])      = (uint64_t)src2_4D | (uint64_t)src2_4B;
            _amem8(&dst2_y[2*x])        = (uint64_t)src2_4C | (uint64_t)src2_4A;
            _amem8(&dst2_y[(2*x)+8])    = (uint64_t)src2_4D | (uint64_t)src2_4B;
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
        /* 10/16 = 0.625 cycles per pixel */
        for( x=0; x < ((width / 8) * 8); x+=8 ) {

            /* Fetch from input */
            src1_8 = _mem8_const(&src1[x]);
            src2_8 = _mem8_const(&src2[x]);

            /* Unpack all 8 bit values into 16-bit values, with top bits == 0 */
            src1_4A = _unpkbu4(_loll(src1_8));
            src1_4B = _unpkbu4(_hill(src1_8));
            src2_4A = _unpkbu4(_loll(src2_8));
            src2_4B = _unpkbu4(_hill(src2_8));

            /* Shift src1 and src2 up by 8 to prepare for packing via OR */
            src1_4C = _dshl(src1_4A, 8U);
            src1_4D = _dshl(src1_4B, 8U);
            src2_4C = _itoll(_hill(src2_4A) << 8U, _rotl(_loll(src2_4A), 8U));
            src2_4D = _itoll(_hill(src2_4B) << 8U, _rotl(_loll(src2_4B), 8U));

            /* OR shifted results together to output combined results */
            _mem8(&dst1[2*x])        = (uint64_t)src1_4C | (uint64_t)src1_4A;
            _mem8(&dst1[(2*x)+8])    = (uint64_t)src1_4D | (uint64_t)src1_4B;
            _mem8(&dst1_y[2*x])      = (uint64_t)src1_4C | (uint64_t)src1_4A;
            _mem8(&dst1_y[(2*x)+8])  = (uint64_t)src1_4D | (uint64_t)src1_4B;

            /* Same thing on dst2 */
            _mem8(&dst2[2*x])          = (uint64_t)src2_4C | (uint64_t)src2_4A;
            _mem8(&dst2[(2*x)+8])      = (uint64_t)src2_4D | (uint64_t)src2_4B;
            _mem8(&dst2_y[2*x])        = (uint64_t)src2_4C | (uint64_t)src2_4A;
            _mem8(&dst2_y[(2*x)+8])    = (uint64_t)src2_4D | (uint64_t)src2_4B;
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_ALIGNED8_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 8 */
    /* 5/2 = 2.5 cycle per pixel */
    for(; x < width; x++ ) {
       _mem2(&dst1[x * 2])   = (uint16_t)((uint16_t)src1[x] << 8) | src1[x];
       _mem2(&dst1_y[x * 2]) = (uint16_t)((uint16_t)src1[x] << 8) | src1[x];
       _mem2(&dst2[x * 2])   = (uint16_t)((uint16_t)src2[x] << 8) | src2[x];
       _mem2(&dst2_y[x * 2]) = (uint16_t)((uint16_t)src2[x] << 8) | src2[x];
    }

#endif


}

VXLIB_STATUS    VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u(const uint8_t src0[restrict],
                                  const VXLIB_bufParams2D_t * src0_addr,
                                  const uint8_t src1[restrict],
                                  const VXLIB_bufParams2D_t * src1_addr,
                                  const uint8_t src2[restrict],
                                  const VXLIB_bufParams2D_t * src2_addr,
                                  uint8_t dst0[restrict],
                                  const VXLIB_bufParams2D_t * dst0_addr,
                                  uint8_t dst1[restrict],
                                  const VXLIB_bufParams2D_t * dst1_addr,
                                  uint8_t dst2[restrict],
                                  const VXLIB_bufParams2D_t * dst2_addr)
{
    VXLIB_STATUS     status = VXLIB_SUCCESS;
    int32_t    y;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, 
                 src2, src2_addr, dst0, dst0_addr, dst1, dst1_addr, dst2, dst2_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t width = dst0_addr->dim_x / 2U;

        /* Copy Luma plane */
        status = VXLIB_channelCopy_1to1_i8u_o8u(src0, src0_addr, dst0, dst0_addr);

        for( y=0; (uint32_t)y < (dst0_addr->dim_y/2U); y++ ) {

            const uint8_t   *src1_t    = (const uint8_t *)&src1[ y * src1_addr->stride_y];
            const uint8_t   *src2_t    = (const uint8_t *)&src2[ y * src2_addr->stride_y];
            uint8_t         *dst1_t    = (uint8_t *)&dst1[ (2*y * dst1_addr->stride_y)];
            uint8_t         *dst2_t    = (uint8_t *)&dst2[ (2*y * dst2_addr->stride_y)];
            uint8_t         *dst1_y_t  = (uint8_t *)&dst1[ (((2*y)+1) * dst1_addr->stride_y)];
            uint8_t         *dst2_y_t  = (uint8_t *)&dst2[ (((2*y)+1) * dst2_addr->stride_y)];

            /* Process both planes */
            VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_core(src1_t, src2_t, dst1_t, dst2_t, dst1_y_t, dst2_y_t, (int32_t)width);
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u_checkParams(const uint8_t src0[],
                                           const VXLIB_bufParams2D_t *src0_addr,
                                           const uint8_t src1[],
                                           const VXLIB_bufParams2D_t *src1_addr,
                                           const uint8_t src2[],
                                           const VXLIB_bufParams2D_t *src2_addr,
                                           const uint8_t dst0[],
                                           const VXLIB_bufParams2D_t *dst0_addr,
                                           const uint8_t dst1[],
                                           const VXLIB_bufParams2D_t *dst1_addr,
                                           const uint8_t dst2[],
                                           const VXLIB_bufParams2D_t *dst2_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src0 == NULL) || (src1 == NULL) || (src2 == NULL) || (dst0 == NULL) || (dst1 == NULL) || (dst2 == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src0_addr->dim_x != dst0_addr->dim_x) ||
               (src0_addr->dim_y != dst0_addr->dim_y) ||
               (src0_addr->stride_y < src0_addr->dim_x) ||
               (src1_addr->stride_y < src1_addr->dim_x) ||
               (src2_addr->stride_y < src2_addr->dim_x) ||
               (dst0_addr->stride_y < dst0_addr->dim_x) ||
               (dst1_addr->stride_y < dst1_addr->dim_x) ||
               (dst2_addr->stride_y < dst2_addr->dim_x) ||
               (src0_addr->dim_x != (2*src1_addr->dim_x)) ||
               (src1_addr->dim_x != src2_addr->dim_x) ||
               (src0_addr->dim_y != (2*src1_addr->dim_y)) ||
               (src1_addr->dim_y != src2_addr->dim_y) ||
               (dst0_addr->dim_x != (dst1_addr->dim_x)) ||
               (dst1_addr->dim_x != dst2_addr->dim_x) ||
               (dst0_addr->dim_y != (dst1_addr->dim_y)) ||
               (dst1_addr->dim_y != dst2_addr->dim_y) ||
               ((src0_addr->dim_x % 2U) != 0) ||
               ((dst0_addr->dim_x % 2U) != 0)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
              (src1_addr->data_type != VXLIB_UINT8) ||
              (src2_addr->data_type != VXLIB_UINT8) ||
              (dst0_addr->data_type != VXLIB_UINT8) ||
              (dst1_addr->data_type != VXLIB_UINT8) ||
              (dst2_addr->data_type != VXLIB_UINT8) ) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (src2_addr->dim_x != src2_addr->stride_y) ||
            (dst0_addr->dim_x != dst0_addr->stride_y) ||
            (dst1_addr->dim_x != dst1_addr->stride_y) ||
            (dst2_addr->dim_x != dst2_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)src2 % 8U) != 0) ||
            (((uint32_t)dst0 % 8U) != 0) ||
            (((uint32_t)dst1 % 8U) != 0) ||
            (((uint32_t)dst2 % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((dst0_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_COLORCONVERT_IYUVTOYUV4_I8U_O8U_ALIGNED8_WIDTHS)
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

