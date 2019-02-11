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

#include "VXLIB_channelCombine_yuyv_i8u_o8u.h"

CODE_SECTION(VXLIB_channelCombine_yuyv_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_channelCombine_yuyv_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_channelCombine_yuyv_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_channelCombine_yuyv_i8u_o8u_core(const uint8_t src0[restrict],
                                            const uint8_t src1[restrict],
                                            const uint8_t src2[restrict],
                                            uint8_t dst[restrict],
                                            int32_t width,
                                            int8_t yidx);

static void VXLIB_channelCombine_yuyv_i8u_o8u_core(const uint8_t src0[restrict],
                                            const uint8_t src1[restrict],
                                            const uint8_t src2[restrict],
                                            uint8_t dst[restrict],
                                            int32_t width,
                                            int8_t yidx)
{
    int32_t    x;
    int64_t src0_8A, src0_8B, src1_8, src2_8;
    __x128_t src0_8_128A, src0_8_128B, src1_8_128, src2_8_128;
    __x128_t src1_4A_128, src1_4B_128, src2_4A_128, src2_4B_128;
    __x128_t shift10 = _dup32_128(0x00000400U);

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0) &&
       (((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)src2 % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
        /* 5/16 = 0.3125 cycles per pixel */
        if(yidx == 0) {

            for( x=0; x < ((width / 16) * 16); x+=16 ) {
                src0_8A = _amem8_const(&src0[x]);
                src0_8B = _amem8_const(&src0[x+8]);
                src1_8 =  _amem8_const(&src1[x/2]);
                src2_8 =  _amem8_const(&src2[x/2]);

                /* Unpack all 8 bit values into 16-bit values */
                src0_8_128A = _dmpyu4(src0_8A, 0x0101010101010101 ); /* No shift */
                src0_8_128B = _dmpyu4(src0_8B, 0x0101010101010101 ); /* No shift */
                src1_8_128  = _dmpyu4(src1_8,  0x0101010101010101 ); /* No shift */
                src2_8_128  = _dmpyu4(src2_8,  0x0101010101010101 ); /* No shift */

                /* Unpack U/V channels to 32 bits, and upshift src1,2 to prepare for packing via OR */
                src1_4A_128 = _dmpy2(_lo128(src1_8_128), 0x0100010001000100); /* Shift +8 */
                src1_4B_128 = _dmpy2(_hi128(src1_8_128), 0x0100010001000100); /* Shift +8 */
                src2_4A_128 = _dmpy2(_lo128(src2_8_128), 0x4000400040004000); /* Shift +14 (need 10 more) */
                src2_4B_128 = _dmpy2(_hi128(src2_8_128), 0x4000400040004000); /* Shift +14 (need 10 more) */

                /* Shift src2 up by 10 so that it is fully shifted to 24 bits to prepare for packing via OR */
                src2_4A_128 = _qmpy32(src2_4A_128, shift10);
                src2_4B_128 = _qmpy32(src2_4B_128, shift10);

                /* OR shifted results together to output combined results */
                _amem8(&dst[x*2])      =    (uint64_t)_lo128(src0_8_128A) |
                                            (uint64_t)_lo128(src1_4A_128) |
                                            (uint64_t)_lo128(src2_4A_128);

                _amem8(&dst[(x*2)+8])    =    (uint64_t)_hi128(src0_8_128A) |
                                            (uint64_t)_hi128(src1_4A_128) |
                                            (uint64_t)_hi128(src2_4A_128);

                _amem8(&dst[(x*2)+16]) =    (uint64_t)_lo128(src0_8_128B) |
                                            (uint64_t)_lo128(src1_4B_128) |
                                            (uint64_t)_lo128(src2_4B_128);

                _amem8(&dst[(x*2)+24]) =    (uint64_t)_hi128(src0_8_128B) |
                                            (uint64_t)_hi128(src1_4B_128) |
                                            (uint64_t)_hi128(src2_4B_128);
            }
        } else {

            for( x=0; x < ((width / 16) * 16); x+=16 ) {
                __x128_t shift8 = _dup32_128(0x00000100U);

                src0_8A = _amem8_const(&src0[x]);
                src0_8B = _amem8_const(&src0[x+8]);
                src1_8 =  _amem8_const(&src1[x/2]);
                src2_8 =  _amem8_const(&src2[x/2]);

                /* Unpack all 8 bit values into 16-bit values */
                src0_8_128A = _dmpyu4(src0_8A, 0x0101010101010101 ); /* No shift */
                src0_8_128B = _dmpyu4(src0_8B, 0x0101010101010101 ); /* No shift */
                src1_8_128  = _dmpyu4(src1_8,  0x0101010101010101 ); /* No shift */
                src2_8_128  = _dmpyu4(src2_8,  0x0404040404040404 ); /* Shift 2 */

                /* Unpack U/V channels to 32 bits, and upshift src1,2 to prepare for packing via OR */
                src1_4A_128 = _dmpy2(_lo128(src1_8_128), 0x0001000100010001); /* No shift */
                src1_4B_128 = _dmpy2(_hi128(src1_8_128), 0x0001000100010001); /* No shift */
                src2_4A_128 = _dmpy2(_lo128(src2_8_128), 0x4000400040004000); /* Shift +14 (+2) = 16 */
                src2_4B_128 = _dmpy2(_hi128(src2_8_128), 0x4000400040004000); /* Shift +14 (+2) = 16 */

                /* Shift src0 up by 8 bits to prepare for packing via OR */
                src0_8_128A = _qmpy32(src0_8_128A, shift8);
                src0_8_128B = _qmpy32(src0_8_128B, shift8);

                /* OR shifted results together to output combined results */
                _amem8(&dst[x*2])      =    (uint64_t)_lo128(src0_8_128A) |
                                            (uint64_t)_lo128(src1_4A_128) |
                                            (uint64_t)_lo128(src2_4A_128);

                _amem8(&dst[(x*2)+8])    =    (uint64_t)_hi128(src0_8_128A) |
                                            (uint64_t)_hi128(src1_4A_128) |
                                            (uint64_t)_hi128(src2_4A_128);

                _amem8(&dst[(x*2)+16]) =    (uint64_t)_lo128(src0_8_128B) |
                                            (uint64_t)_lo128(src1_4B_128) |
                                            (uint64_t)_lo128(src2_4B_128);

                _amem8(&dst[(x*2)+24]) =    (uint64_t)_hi128(src0_8_128B) |
                                            (uint64_t)_hi128(src1_4B_128) |
                                            (uint64_t)_hi128(src2_4B_128);
            }
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 16 pixels at a time*/
        /* 8/16 = 0.5 cycles per pixel */
        for( x=0; x < ((width / 16) * 16); x+=16 ) {
            uint64_t dst0, dst1, dst2, dst3;

            src0_8A = _mem8_const(&src0[x]);
            src0_8B = _mem8_const(&src0[x+8]);
            src1_8 =  _mem8_const(&src1[x/2]);
            src2_8 =  _mem8_const(&src2[x/2]);

            /* Unpack all 8 bit values into 16-bit values */
            src0_8_128A = _dmpyu4(src0_8A, 0x0101010101010101 ); /* No shift */
            src0_8_128B = _dmpyu4(src0_8B, 0x0101010101010101 ); /* No shift */
            src1_8_128  = _dmpyu4(src1_8,  0x0101010101010101 ); /* No shift */
            src2_8_128  = _dmpyu4(src2_8,  0x0101010101010101 ); /* No shift */

            /* Unpack U/V channels to 32 bits, and upshift src1,2 to prepare for packing via OR */
            src1_4A_128 = _dmpy2(_lo128(src1_8_128), 0x0100010001000100); /* Shift +8 */
            src1_4B_128 = _dmpy2(_hi128(src1_8_128), 0x0100010001000100); /* Shift +8 */
            src2_4A_128 = _dmpy2(_lo128(src2_8_128), 0x4000400040004000); /* Shift +14 (need 10 more) */
            src2_4B_128 = _dmpy2(_hi128(src2_8_128), 0x4000400040004000); /* Shift +14 (need 10 more) */

            /* Shift src2 up by 10 so that it is fully shifted to 24 bits to prepare for packing via OR */
            src2_4A_128 = _qmpy32(src2_4A_128, shift10);
            src2_4B_128 = _qmpy32(src2_4B_128, shift10);

            /* OR shifted results together to output combined results */
            dst0 =  (uint64_t)_lo128(src0_8_128A) |
                    (uint64_t)_lo128(src1_4A_128) |
                    (uint64_t)_lo128(src2_4A_128);
            dst1 =  (uint64_t)_hi128(src0_8_128A) |
                    (uint64_t)_hi128(src1_4A_128) |
                    (uint64_t)_hi128(src2_4A_128);
            dst2 =  (uint64_t)_lo128(src0_8_128B) |
                    (uint64_t)_lo128(src1_4B_128) |
                    (uint64_t)_lo128(src2_4B_128);
            dst3 =  (uint64_t)_hi128(src0_8_128B) |
                    (uint64_t)_hi128(src1_4B_128) |
                    (uint64_t)_hi128(src2_4B_128);

            /* Swap bytes conditionally (since there is spare cycles for this in the non-aligned memory version */
            dst0 = (yidx) ? _itoll(_swap4(_hill((int64_t)dst0)), _swap4(_loll((int64_t)dst0))) : dst0;
            dst1 = (yidx) ? _itoll(_swap4(_hill((int64_t)dst1)), _swap4(_loll((int64_t)dst1))) : dst1;
            dst2 = (yidx) ? _itoll(_swap4(_hill((int64_t)dst2)), _swap4(_loll((int64_t)dst2))) : dst2;
            dst3 = (yidx) ? _itoll(_swap4(_hill((int64_t)dst3)), _swap4(_loll((int64_t)dst3))) : dst3;

            _mem8(&dst[x*2])      = dst0;
            _mem8(&dst[(x*2)+8])  = dst1;
            _mem8(&dst[(x*2)+16]) = dst2;
            _mem8(&dst[(x*2)+24]) = dst3;
        }
    }
#endif

#if !defined(VXLIB_ALIGNED16_WIDTHS) && !defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_ALIGNED16_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 16 */
    /* 1.5 cycle per pixel */
    for(; x < width; x+=2 ) {
        uint32_t result =   ((uint32_t)src2[x/2]   << 24) |
                             ((uint32_t)src0[x+1] << 16) |
                             ((uint32_t)src1[x/2]   << 8) |
                              src0[x];
        result = (yidx) ? _swap4(result) : result;
        _mem4(&dst[x*2]) = result;
    }

#endif
}

VXLIB_STATUS VXLIB_channelCombine_yuyv_i8u_o8u(const uint8_t src0[restrict],
                                        const VXLIB_bufParams2D_t *src0_addr,
                                        const uint8_t src1[restrict],
                                        const VXLIB_bufParams2D_t *src1_addr,
                                        const uint8_t src2[restrict],
                                        const VXLIB_bufParams2D_t *src2_addr,
                                        uint8_t dst[restrict],
                                        const VXLIB_bufParams2D_t *dst_addr,
                                        int8_t yidx)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_channelCombine_yuyv_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, src2, src2_addr, dst, dst_addr, yidx);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           (src1_addr->dim_x == src1_addr->stride_y) &&
           (src2_addr->dim_x == src2_addr->stride_y) &&
           ((2 * dst_addr->dim_x) == dst_addr->stride_y))
#endif
        {
            VXLIB_channelCombine_yuyv_i8u_o8u_core(src0, src1, src2, dst, dst_addr->dim_x * dst_addr->dim_y, yidx);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[ (y * src0_addr->stride_y)];
                const uint8_t   *src1_t = (const uint8_t *)&src1[ (y * src1_addr->stride_y)];
                const uint8_t   *src2_t = (const uint8_t *)&src2[ (y * src2_addr->stride_y)];
                uint8_t         *dst_t  = (uint8_t *)&dst[ (y * dst_addr->stride_y)];

                VXLIB_channelCombine_yuyv_i8u_o8u_core(src0_t, src1_t, src2_t, dst_t, dst_addr->dim_x, yidx);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_channelCombine_yuyv_i8u_o8u_checkParams(const uint8_t src0[],
                                                    const VXLIB_bufParams2D_t *src0_addr,
                                                    const uint8_t src1[],
                                                    const VXLIB_bufParams2D_t *src1_addr,
                                                    const uint8_t src2[],
                                                    const VXLIB_bufParams2D_t *src2_addr,
                                                    const uint8_t dst[],
                                                    const VXLIB_bufParams2D_t *dst_addr,
                                                    int8_t yidx)
{
    VXLIB_STATUS    status;

    if((src0 == NULL) || (src1 == NULL) || (src2 == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src0_addr->dim_x != (2 * src1_addr->dim_x)) ||
              (src0_addr->dim_x != (2 * src2_addr->dim_x)) ||
              (src0_addr->dim_x != dst_addr->dim_x) ||
              (src0_addr->dim_y != src1_addr->dim_y) ||
              (src0_addr->dim_y != dst_addr->dim_y) ||
              (src0_addr->stride_y < src0_addr->dim_x) ||
              (src1_addr->stride_y < src1_addr->dim_x) ||
              (src2_addr->stride_y < src2_addr->dim_x) ||
              (dst_addr->stride_y < (2 * dst_addr->dim_x))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
               (src1_addr->data_type != VXLIB_UINT8) ||
               (src2_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (src2_addr->dim_x != src2_addr->stride_y) ||
            ((2 * dst_addr->dim_x) != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)src2 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((src2_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED16_WIDTHS) || defined(VXLIB_CHANNELCOMBINE_YUYV_I8U_O8U_ALIGNED16_WIDTHS)
    else if(((src0_addr->dim_x % 16U) != 0) ||
            ((src1_addr->dim_x % 16U) != 0) ||
            ((src2_addr->dim_x % 16U) != 0) ||
            ((dst_addr->dim_x % 16U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else if((yidx > 1) || (yidx < 0)) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

