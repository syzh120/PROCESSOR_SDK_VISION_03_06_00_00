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

#include "VXLIB_channelCombine_4to1_i8u_o8u.h"

CODE_SECTION(VXLIB_channelCombine_4to1_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_channelCombine_4to1_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_channelCombine_4to1_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_channelCombine_4to1_i8u_o8u_core(const uint8_t src0[restrict],
                                            const uint8_t src1[restrict],
                                            const uint8_t src2[restrict],
                                            const uint8_t src3[restrict],
                                            uint8_t dst[restrict],
                                            int32_t width);

static void VXLIB_channelCombine_4to1_i8u_o8u_core(const uint8_t src0[restrict],
                                            const uint8_t src1[restrict],
                                            const uint8_t src2[restrict],
                                            const uint8_t src3[restrict],
                                            uint8_t dst[restrict],
                                            int32_t width)
{
    int32_t    x;

    /* Case 1: SIMD of 8 pixels at a time*/
    /* 8/8 = 1.00 cycles per pixel */
    for( x=0; x < ((width / 8) * 8); x+=8 ) {
        int64_t src0_8 = _mem8_const(&src0[x]);
        int64_t src1_8 = _mem8_const(&src1[x]);
        int64_t src2_8 = _mem8_const(&src2[x]);
        int64_t src3_8 = _mem8_const(&src3[x]);

        /* Unpack all 8 bit values into 16-bit values, and upshift the src2 and src1 a little */
        __x128_t src0_8_128 = _dmpyu4(src0_8, 0x0101010101010101 ); /* No shift */
        __x128_t src1_8_128 = _dmpyu4(src1_8, 0x0101010101010101 ); /* No shift */
        __x128_t src2_8_128 = _dmpyu4(src2_8, 0x1010101010101010 ); /* Shift 4  */
        __x128_t src3_8_128 = _dmpyu4(src3_8, (int64_t)0x8080808080808080U ); /* Shift 7  */

        /* Unpack to 32 bits, and upshift src1,2, & 3 to prepare for packing via OR */
        __x128_t src0_4A_128 = _dmpy2(_lo128(src0_8_128), 0x0001000100010001); /* No shift */
        __x128_t src0_4B_128 = _dmpy2(_hi128(src0_8_128), 0x0001000100010001); /* No shift */
        __x128_t src1_4A_128 = _dmpy2(_lo128(src1_8_128), 0x0100010001000100); /* Shift +8 */
        __x128_t src1_4B_128 = _dmpy2(_hi128(src1_8_128), 0x0100010001000100); /* Shift +8 */
        __x128_t src2_4A_128 = _dmpy2(_lo128(src2_8_128), 0x1000100010001000); /* Shift +12 (+4) = 16 */
        __x128_t src2_4B_128 = _dmpy2(_hi128(src2_8_128), 0x1000100010001000); /* Shift +12 (+4) = 16 */
        __x128_t src3_4A_128 = _dmpy2(_lo128(src3_8_128), 0x4000400040004000); /* Shift +14 (+7) = 21 (need 3 more) */
        __x128_t src3_4B_128 = _dmpy2(_hi128(src3_8_128), 0x4000400040004000); /* Shift +14 (+7) = 21 (need 3 more) */

        /* Shift src3 up by 3 so that it is fully shifted to 24 bits to prepare for packing via OR */
        uint64_t src3_4A_64A = (uint64_t)_lo128(src3_4A_128) << 3;
        uint64_t src3_4A_64B = (uint64_t)_hi128(src3_4A_128) << 3;
        uint64_t src3_4B_64A = (uint64_t)_lo128(src3_4B_128) << 3;
        uint64_t src3_4B_64B = (uint64_t)_hi128(src3_4B_128) << 3;

        /* OR shifted results together to output combined results */
        _mem8(&dst[x*4])      = (uint64_t)_lo128(src0_4A_128) |
                                (uint64_t)_lo128(src1_4A_128) |
                                (uint64_t)_lo128(src2_4A_128) |
                                                  src3_4A_64A;
        _mem8(&dst[(x*4)+8])  = (uint64_t)_hi128(src0_4A_128) |
                                (uint64_t)_hi128(src1_4A_128) |
                                (uint64_t)_hi128(src2_4A_128) |
                                                  src3_4A_64B;
        _mem8(&dst[(x*4)+16]) = (uint64_t)_lo128(src0_4B_128) |
                                (uint64_t)_lo128(src1_4B_128) |
                                (uint64_t)_lo128(src2_4B_128) |
                                                  src3_4B_64A;
        _mem8(&dst[(x*4)+24]) = (uint64_t)_hi128(src0_4B_128) |
                                (uint64_t)_hi128(src1_4B_128) |
                                (uint64_t)_hi128(src2_4B_128) |
                                                  src3_4B_64B;
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_ALIGNED8_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 3 cycle per pixel */
    for(; x < width; x++ ) {
        _mem4(&dst[x*4])   = ((uint32_t)src3[x] << 24) |
                             ((uint32_t)src2[x] << 16) |
                             ((uint32_t)src1[x] << 8) |
                              src0[x];
    }

#endif
}

VXLIB_STATUS VXLIB_channelCombine_4to1_i8u_o8u(const uint8_t src0[restrict],
                                        const VXLIB_bufParams2D_t *src0_addr,
                                        const uint8_t src1[restrict],
                                        const VXLIB_bufParams2D_t *src1_addr,
                                        const uint8_t src2[restrict],
                                        const VXLIB_bufParams2D_t *src2_addr,
                                        const uint8_t src3[restrict],
                                        const VXLIB_bufParams2D_t *src3_addr,
                                        uint8_t dst[restrict],
                                        const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_channelCombine_4to1_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, src2, src2_addr, src3, src3_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           (src1_addr->dim_x == src1_addr->stride_y) &&
           (src2_addr->dim_x == src2_addr->stride_y) &&
           (src3_addr->dim_x == src3_addr->stride_y) &&
           ((4 * dst_addr->dim_x) == dst_addr->stride_y))
#endif
        {
            VXLIB_channelCombine_4to1_i8u_o8u_core(src0, src1, src2, src3, dst, src0_addr->dim_x * src0_addr->dim_y);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[ (y * src0_addr->stride_y)];
                const uint8_t   *src1_t = (const uint8_t *)&src1[ (y * src1_addr->stride_y)];
                const uint8_t   *src2_t = (const uint8_t *)&src2[ (y * src2_addr->stride_y)];
                const uint8_t   *src3_t = (const uint8_t *)&src3[ (y * src3_addr->stride_y)];
                uint8_t         *dst_t  = (uint8_t *)&dst[ (y * dst_addr->stride_y)];

                VXLIB_channelCombine_4to1_i8u_o8u_core(src0_t, src1_t, src2_t, src3_t, dst_t, src0_addr->dim_x);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_channelCombine_4to1_i8u_o8u_checkParams(const uint8_t src0[],
                                                    const VXLIB_bufParams2D_t *src0_addr,
                                                    const uint8_t src1[],
                                                    const VXLIB_bufParams2D_t *src1_addr,
                                                    const uint8_t src2[],
                                                    const VXLIB_bufParams2D_t *src2_addr,
                                                    const uint8_t src3[],
                                                    const VXLIB_bufParams2D_t *src3_addr,
                                                    const uint8_t dst[],
                                                    const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status;

    if((src0 == NULL) || (src1 == NULL) || (src2 == NULL) || (src3 == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src0_addr->dim_x != src1_addr->dim_x) ||
              (src0_addr->dim_x != src2_addr->dim_x) ||
              (src0_addr->dim_x != dst_addr->dim_x) ||
              (src0_addr->dim_y != src1_addr->dim_y) ||
              (src0_addr->dim_y != dst_addr->dim_y) ||
              (src0_addr->stride_y < src0_addr->dim_x) ||
              (src1_addr->stride_y < src0_addr->dim_x) ||
              (src2_addr->stride_y < src0_addr->dim_x) ||
              (src3_addr->stride_y < src0_addr->dim_x) ||
              (dst_addr->stride_y < (4 * dst_addr->dim_x))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
               (src1_addr->data_type != VXLIB_UINT8) ||
               (src2_addr->data_type != VXLIB_UINT8) ||
               (src3_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT32)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (src2_addr->dim_x != src2_addr->stride_y) ||
            (src3_addr->dim_x != src2_addr->stride_y) ||
            ((4 * dst_addr->dim_x) != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)src2 % 8U) != 0) ||
            (((uint32_t)src3 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((src2_addr->stride_y % 8U) != 0) ||
            ((src3_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_CHANNELCOMBINE_4TO1_I8U_O8U_ALIGNED8_WIDTHS)
    else if(((src0_addr->dim_x % 8U) != 0) ||
            ((src1_addr->dim_x % 8U) != 0) ||
            ((src2_addr->dim_x % 8U) != 0) ||
            ((src3_addr->dim_x % 8U) != 0) ||
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

