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

#include "VXLIB_colorConvert_RGBtoYUV4_i8u_o8u.h"

CODE_SECTION(VXLIB_colorConvert_RGBtoYUV4_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_core(const uint8_t src[restrict],
                                                       uint8_t dst0[restrict],
                                                       uint8_t dst1[restrict],
                                                       uint8_t dst2[restrict],
                                                       int32_t width);

static void VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_core(const uint8_t src[restrict],
                                                       uint8_t dst0[restrict],
                                                       uint8_t dst1[restrict],
                                                       uint8_t dst2[restrict],
                                                       int32_t width)
{
    int32_t    x;
    uint32_t    s0, s1, s2, s3, s4, s5, s6, s7;
    uint32_t    s10, s32, s54, s76;
    int64_t    s5410, s7632, s3210, s7654;

    /*
        Floating point coefficients:
        Y'= 0.2126*R' + 0.7152*G' + 0.0722*B'
        U'=-0.1146*R' - 0.3854*G' + 0.5000*B'
        V'= 0.5000*R' - 0.4542*G' - 0.0458*B'

        8-bit fixed point version used here
          - 8 bit unsigned precision for Y', and
          - 7 bit signed precision for U' and V'

        Y'=  (( 54*R' + 183*G' + 18*B')+128)/256
        U'=  ((-15*R' -  49*G' + 64*B')+64)/128 + 128
        V'=  (( 64*R' -  58*G' -  6*B')+64)/128 + 128
    */
    uint32_t yCoef =   (((uint32_t)18 & 0xffU) << 16) | (((uint32_t)183 & 0xffU) << 8) |  ((uint32_t)54 & 0xffU);
    uint32_t uCoef =   (((uint32_t)64 & 0xffU) << 16) | (((uint32_t)-49 & 0xffU) << 8) | ((uint32_t)-15 & 0xffU);
    uint32_t vCoef =   (((uint32_t)-6 & 0xffU) << 16) | (((uint32_t)-58 & 0xffU) << 8) | ((uint32_t)64U & 0xffU);

    int64_t x128 = _itoll(((uint32_t)128 << 16) | (uint32_t)128, ((uint32_t)128 << 16) | (uint32_t)128);
    int64_t x64 = _itoll(((((uint32_t)128 << 7) + (uint32_t)64) << 16) | (((uint32_t)128 << 7) + (uint32_t)64),
                          ((((uint32_t)128 << 7) + (uint32_t)64) << 16) | (((uint32_t)128 << 7) + (uint32_t)64));

    /* Case 1: SIMD of 8 pixels at a time */
    /* 12/8 = 1.50 cycles per pixel */
    for( x=0; x < (width / 8); x++ ) {

        /* Fetch 8 3-channel inputs */
        int64_t src_8A = _mem8_const(&src[(x*24)+0]);
        int64_t src_8B = _mem8_const(&src[(x*24)+8]);
        int64_t src_8C = _mem8_const(&src[(x*24)+16]);

        /* Rearrange them into the 8 inputs */
        uint32_t src0_4 = _loll(src_8A);
        uint32_t src1_4 = _packlh2(_hill(src_8A), _loll(src_8A)) >> 8;
        uint32_t src2_4 = _packlh2(_loll(src_8B), _hill(src_8A));
        uint32_t src3_4 = _loll(src_8B) >> 8;
        uint32_t src4_4 = _hill(src_8B);
        uint32_t src5_4 = _packlh2(_loll(src_8C), _hill(src_8B)) >> 8;
        uint32_t src6_4 = _packlh2(_hill(src_8C), _loll(src_8C));
        uint32_t src7_4 = _hill(src_8C) >> 8;



        /*
         *  Process Y' Channel
         */

        /* Perform dot product for all Y' channel pixels */
        s0 = _dotpu4(src0_4, yCoef);
        s1 = _dotpu4(src1_4, yCoef);
        s2 = _dotpu4(src2_4, yCoef);
        s3 = _dotpu4(src3_4, yCoef);
        s4 = _dotpu4(src4_4, yCoef);
        s5 = _dotpu4(src5_4, yCoef);
        s6 = _dotpu4(src6_4, yCoef);
        s7 = _dotpu4(src7_4, yCoef);

        /* Pack the sums from 32 bit containers to 16 bit containers */
        s10 = _pack2(s1, s0);
        s32 = _pack2(s3, s2);
        s54 = _pack2(s5, s4);
        s76 = _pack2(s7, s6);

        /* Store as long long types for SIMD operations later */
        s5410 = _itoll(s54, s10);
        s7632 = _itoll(s76, s32);

        /* Add 128 to each sum before dividing by 256 for round operation */
        s5410 = _dadd2(s5410, x128);
        s7632 = _dadd2(s7632, x128);

        /* Divide by 256 and pack to 8 bits to get back to integer precision */
        _mem8(&dst0[(x * 8)]) = _dpackh4(s7632, s5410);



        /*
         *  Process U' Channel
         */

        /* Perform dot product for all U' channel pixels */
        s0 = (uint32_t)_dotpus4(src0_4, (int32_t)uCoef);
        s1 = (uint32_t)_dotpus4(src1_4, (int32_t)uCoef);
        s2 = (uint32_t)_dotpus4(src2_4, (int32_t)uCoef);
        s3 = (uint32_t)_dotpus4(src3_4, (int32_t)uCoef);
        s4 = (uint32_t)_dotpus4(src4_4, (int32_t)uCoef);
        s5 = (uint32_t)_dotpus4(src5_4, (int32_t)uCoef);
        s6 = (uint32_t)_dotpus4(src6_4, (int32_t)uCoef);
        s7 = (uint32_t)_dotpus4(src7_4, (int32_t)uCoef);

        /* Pack the sums from 32 bit containers to 16 bit containers */
        s10 = (uint32_t)_spack2((int32_t)s1, (int32_t)s0);
        s32 = (uint32_t)_spack2((int32_t)s3, (int32_t)s2);
        s54 = (uint32_t)_spack2((int32_t)s5, (int32_t)s4);
        s76 = (uint32_t)_spack2((int32_t)s7, (int32_t)s6);

        /* Store as long long types for SIMD operations later */
        s3210 = _itoll(s32, s10);
        s7654 = _itoll(s76, s54);

        /* Add 64 to each sum and divide by 128 for round operation */
        s3210 = _dshr2(_dsadd2(s3210, x64), 7U);
        s7654 = _dshr2(_dsadd2(s7654, x64), 7U);

        /* Pack the lower 8 bits to get back to integer precision */
        _mem8(&dst1[(x * 8)]) = _dspacku4(s3210, s7654);

        /*
         *  Process V' Channel
         */

        /* Perform dot product for all V' channel pixels */
        s0 = (uint32_t)_dotpus4(src0_4, (int32_t)vCoef);
        s1 = (uint32_t)_dotpus4(src1_4, (int32_t)vCoef);
        s2 = (uint32_t)_dotpus4(src2_4, (int32_t)vCoef);
        s3 = (uint32_t)_dotpus4(src3_4, (int32_t)vCoef);
        s4 = (uint32_t)_dotpus4(src4_4, (int32_t)vCoef);
        s5 = (uint32_t)_dotpus4(src5_4, (int32_t)vCoef);
        s6 = (uint32_t)_dotpus4(src6_4, (int32_t)vCoef);
        s7 = (uint32_t)_dotpus4(src7_4, (int32_t)vCoef);

        /* Pack the sums from 32 bit containers to 16 bit containers */
        s10 = (uint32_t)_spack2((int32_t)s1, (int32_t)s0);
        s32 = (uint32_t)_spack2((int32_t)s3, (int32_t)s2);
        s54 = (uint32_t)_spack2((int32_t)s5, (int32_t)s4);
        s76 = (uint32_t)_spack2((int32_t)s7, (int32_t)s6);

        /* Store as long long types for SIMD operations later */
        s3210 = _itoll(s32, s10);
        s7654 = _itoll(s76, s54);

        /* Add 64 to each sum and divide by 128 for round operation */
        s3210 = _dshr2(_dsadd2(s3210, x64), 7U);
        s7654 = _dshr2(_dsadd2(s7654, x64), 7U);

        /* Pack the lower 8 bits to get back to integer precision */
        _mem8(&dst2[(x * 8)]) = _dspacku4(s3210, s7654);
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_ALIGNED8_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 3 cycle per pixel */
    for(x*=8; x < width; x++ ) {

        uint32_t adder = ((uint32_t)128 << 7) + (uint32_t)64;
        int32_t tmp;
        uint32_t src4 = _mem4_const(&src[x*3]);

        s0 = (_dotpu4(src4, yCoef) + 128U) >> 8;
        dst0[x] = (uint8_t)s0;

        tmp = _dotpus4(src4, (int32_t)uCoef) + (int32_t)adder;
        s0 = (uint32_t)tmp >> 7;
        dst1[x] = (uint8_t)_spacku4(0, (int32_t)s0);

        tmp = _dotpus4(src4, (int32_t)vCoef) + (int32_t)adder;
        s0 = (uint32_t)tmp >> 7;
        dst2[x] = (uint8_t)_spacku4(0, (int32_t)s0);
    }

#endif
}


VXLIB_STATUS    VXLIB_colorConvert_RGBtoYUV4_i8u_o8u(const uint8_t src[restrict],
                                  const VXLIB_bufParams2D_t * src_addr,
                                  uint8_t dst0[restrict],
                                  const VXLIB_bufParams2D_t * dst0_addr,
                                  uint8_t dst1[restrict],
                                  const VXLIB_bufParams2D_t * dst1_addr,
                                  uint8_t dst2[restrict],
                                  const VXLIB_bufParams2D_t * dst2_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_checkParams(src, src_addr, dst0, dst0_addr, 
        dst1, dst1_addr, dst2, dst2_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if(((3 * src_addr->dim_x) == src_addr->stride_y) &&
            (dst0_addr->dim_x == dst0_addr->stride_y) &&
            (dst1_addr->dim_x == dst1_addr->stride_y) &&
            (dst2_addr->dim_x == dst2_addr->stride_y))
#endif
        {
            VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_core(src, dst0, dst1, dst2, dst0_addr->dim_x * dst0_addr->dim_y);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < dst0_addr->dim_y; y++ ) {

                const uint8_t   *src_t = (const uint8_t *)&src[ (y * src_addr->stride_y)];
                uint8_t         *dst0_t  = (uint8_t *)&dst0[ (y * dst0_addr->stride_y)];
                uint8_t         *dst1_t  = (uint8_t *)&dst1[ (y * dst1_addr->stride_y)];
                uint8_t         *dst2_t  = (uint8_t *)&dst2[ (y * dst2_addr->stride_y)];

                VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_core(src_t, dst0_t, dst1_t, dst2_t, dst0_addr->dim_x);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_checkParams(const uint8_t src[],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst0[],
                                           const VXLIB_bufParams2D_t *dst0_addr,
                                           const uint8_t dst1[],
                                           const VXLIB_bufParams2D_t *dst1_addr,
                                           const uint8_t dst2[],
                                           const VXLIB_bufParams2D_t *dst2_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst0 == NULL) || (dst1 == NULL) || (dst2 == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src_addr->dim_x != dst0_addr->dim_x) ||
                (src_addr->dim_y != dst0_addr->dim_y) ||
                (src_addr->stride_y < (3*src_addr->dim_x)) ||
                (dst0_addr->dim_x != dst1_addr->dim_x) ||
                (dst0_addr->dim_y != dst1_addr->dim_y) ||
                (dst1_addr->dim_x != dst2_addr->dim_x) ||
                (dst1_addr->dim_y != dst2_addr->dim_y) ||
                (dst0_addr->stride_y < dst0_addr->dim_x) ||
                (dst1_addr->stride_y < dst1_addr->dim_x) ||
                (dst2_addr->stride_y < dst2_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT24) ||
              (dst0_addr->data_type != VXLIB_UINT8) ||
              (dst1_addr->data_type != VXLIB_UINT8) ||
              (dst2_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_COLORCONVERT_RGBTOYUV4_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((3 * src_addr->dim_x != src_addr->stride_y) ||
            (dst0_addr->dim_x != dst0_addr->stride_y) ||
            (dst1_addr->dim_x != dst1_addr->stride_y) ||
            (dst2_addr->dim_x != dst2_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_COLORCONVERT_RGBTOYUV4_ALIGNED8_WIDTHS)
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
