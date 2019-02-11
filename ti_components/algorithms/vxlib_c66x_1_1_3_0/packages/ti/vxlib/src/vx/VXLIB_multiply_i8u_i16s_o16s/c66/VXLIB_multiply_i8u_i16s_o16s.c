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

#include "VXLIB_multiply_i8u_i16s_o16s.h"

CODE_SECTION(VXLIB_multiply_i8u_i16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_multiply_i8u_i16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_multiply_i8u_i16s_o16s_checkParams,  ".text:optimized")

/* There are 2 approximations being done in this algorithm to find out
 * if the scale == 1/2^n or a positive integer:
 * 1. The DECIMAL_BITS parameter uses 8 bits of Q point when converting
 *    the float to an int for a integer comparison.
 * 2. The reciprical of the scale is using the _rcpsp() recipricol
 *    approximation, which has accurate exponent and 8bits of mantissa
 *    accuracy
 * If it is found that this is not appropriate, then better precision
 * can be found by increasing DECIMAL_BITS and/or using the Newton-Rhapson
 * algorithm to iterativly double the mantissa precision (see RCPSP
 * instruction in the C6X instruction manual
 */
#define DECIMAL_BITS 8U

static void VXLIB_multiply_i8u_i16s_o16s_core(const uint8_t src0[restrict],
                                       const int16_t src1[restrict],
                                       int16_t dst[restrict],
                                       int32_t width,
                                       uint16_t overflow_policy,
                                       VXLIB_F32 scale);

static void VXLIB_multiply_i8u_i16s_o16s_core(const uint8_t src0[restrict],
                                       const int16_t src1[restrict],
                                       int16_t dst[restrict],
                                       int32_t width,
                                       uint16_t overflow_policy,
                                       VXLIB_F32 scale)
{
    int32_t    x;
    int32_t    intermediate_result;
    __x128_t    mpy1;
    int64_t    mpy2;
    int64_t src0_8, src1_8;
    int32_t ones32 = 0x01010101;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_MULTIPLY_I16S_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    int64_t    hi, lo;
    int64_t negAdder_2, mask32_64;
    uint32_t negAdder;
#endif
#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ALIGNED8_WIDTHS)
    int32_t    temp;
#endif
#if !defined(VXLIB_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_SCALE_DISABLED)
    int32_t     int_typed_result;
    VXLIB_D64    unscaled_result, scaled_result;
#endif

    VXLIB_F32 invertScale_f    = _rcpsp(scale)*(VXLIB_F32)((uint32_t)1<<DECIMAL_BITS);
    int32_t invertScale_s32   = (int32_t)invertScale_f;
    uint32_t invertScale_u32  = (uint32_t)invertScale_s32;
    uint32_t msb              = 31U - _lmbd(1U, invertScale_u32);
    VXLIB_F32 convertScale_f   = scale*(VXLIB_F32)((uint32_t)1<<DECIMAL_BITS);
    int32_t convertScale_s32  = (int32_t)convertScale_f;
    uint32_t convertScale_u32 = (uint32_t)convertScale_s32;
    uint32_t convertScale_i1  = convertScale_u32>>DECIMAL_BITS;
    uint32_t convertScale_i2  = ((convertScale_i1 & 0xffffU) << 16) |
                                  (convertScale_i1 & 0xffffU);
    int64_t convertScale_i4   = _itoll(convertScale_i2, convertScale_i2);
    uint32_t integerMask      = ((uint32_t)1<<DECIMAL_BITS)-1U;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0) &&
       (((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0) &&
       ((convertScale_u32 & integerMask) == 0) &&
       ((invertScale_u32 != ((uint32_t)1<<msb)) || (msb <= DECIMAL_BITS)) ) 
#endif
    {
        _nassert(((uint32_t)src0 % 8U) == 0);
        _nassert(((uint32_t)src1 % 8U) == 0);
        _nassert(((uint32_t)dst % 8U) == 0);
        if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP ) {
            /* Case 1B: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
            /*          Optimized for scale == positive integer */
            /* 3/8 = 0.375 cycles per pixel */
            #pragma UNROLL(2)
            for( x=0; x < ((width / 8) * 2); x++ ) {
                src0_8    = _mpysu4ll(ones32, _amem4_const(&src0[x*4]));
                src1_8    = _amem8_const(&src1[x*4]);

                mpy1 = _dmpy2(src0_8, src1_8);
                mpy2 = _itoll(_pack2(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                              _pack2(_get32_128(mpy1,1U), _get32_128(mpy1,0)));
                mpy1 = _dmpy2(mpy2, convertScale_i4);
                _amem8(&dst[x*4]) = _itoll(_pack2(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                           _pack2(_get32_128(mpy1,1U), _get32_128(mpy1,0)));
            }
            x*=4;
        } else { /* VXLIB_CONVERT_POLICY_SATURATE */
            /* Case 1E: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
            /*          Optimized for scale == positive integer */
            /* 4/8 = 0.5 cycles per pixel */
            #pragma UNROLL(2)
            for( x=0; x < ((width / 8) * 2); x++ ) {
                src0_8    = _mpysu4ll(ones32, _amem4_const(&src0[x*4]));
                src1_8    = _amem8_const(&src1[x*4]);

                mpy1 = _dmpy2(src0_8, src1_8);
                mpy2 = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpy1,3U), (int32_t)_get32_128(mpy1,2U)),
                              (uint32_t)_spack2((int32_t)_get32_128(mpy1,1U), (int32_t)_get32_128(mpy1,0)));
                mpy1 = _dmpy2(mpy2, convertScale_i4);
                _amem8(&dst[x*4]) = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpy1,3U), (int32_t)_get32_128(mpy1,2U)),
                                           (uint32_t)_spack2((int32_t)_get32_128(mpy1,1U), (int32_t)_get32_128(mpy1,0)));
            }
            x*=4;
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    else {

        if((overflow_policy == VXLIB_CONVERT_POLICY_WRAP) ) {
            if((invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS)) {

                negAdder = ((uint32_t)1<<(msb-DECIMAL_BITS))-1U;
                negAdder_2 = _itoll(negAdder, negAdder);

                /* Case 2A: SIMD of 4 pixels at a time*/
                /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
                /* 3/4 = 0.75 cycles per pixel */
                #pragma UNROLL(1)
                for( x=0; x < (width / 4); x++ ) {
                    src0_8    = _mpysu4ll(ones32, _mem4_const(&src0[x*4]));
                    src1_8    = _mem8_const(&src1[x*4]);

                    mpy1 = _dmpy2(src0_8, src1_8);

                    /* Mask code required if value is negative, to round to zero */
                    /* MISRA.BITS.NOT_UNSIGNED
                     * MISRAC_2004 Rule_12.7
                     * MISRAC_WAIVER:
                     * The C6x DSP compiler treats all types as unsigned when it comes
                     * to the following bitwise operations (&, |, ~, ^).  In this case,
                     * the compiler document requires the 64bit bitwise operations to
                     * use the type "int64_t".
                     */
                    mask32_64 = _dshr(_lo128(mpy1), 31U) & negAdder_2;
                    lo = _dshr(_dadd(_lo128(mpy1), mask32_64), msb-DECIMAL_BITS);
                    mask32_64 = _dshr(_hi128(mpy1), 31U) & negAdder_2;
                    hi = _dshr(_dadd(_hi128(mpy1), mask32_64), msb-DECIMAL_BITS);

                    _mem8(&dst[x*4])   = _itoll(_pack2(_hill(hi), _loll(hi)),
                                                _pack2(_hill(lo), _loll(lo)));
                }
                x*=4;
            } else if((convertScale_u32 & integerMask) == 0) {
                /* Case 2B: Not all pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time*/
                /*          Optimized for scale == positive integer */
                /* 5/8 = 0.625 cycles per pixel */
                #pragma UNROLL(2)
                for( x=0; x < ((width / 8) * 2); x++ ) {
                    src0_8    = _mpysu4ll(ones32, _mem4_const(&src0[x*4]));
                    src1_8    = _mem8_const(&src1[x*4]);

                    mpy1 = _dmpy2(src0_8, src1_8);
                    mpy2 = _itoll(_pack2(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                  _pack2(_get32_128(mpy1,1U), _get32_128(mpy1,0)));
                    mpy1 = _dmpy2(mpy2, convertScale_i4);
                    _mem8(&dst[x*4]) = _itoll(_pack2(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                              _pack2(_get32_128(mpy1,1U), _get32_128(mpy1,0)));
                }
                x*=4;
            }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ARBITRARY_SCALE_DISABLED)
            else {
                /* Case 2C: SIMD of 8 pixels at a time*/
                /* 8/4 = 2 cycles per pixel (Potential for optimizations here) */
                #pragma MUST_ITERATE(0,,8)
                for( x=0; x < ((width / 8) * 8); x++ ) {
                    intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
                    unscaled_result = (VXLIB_D64)intermediate_result;
                    scaled_result = (VXLIB_D64)scale * unscaled_result;
                    dst[x] = (int16_t)scaled_result;
                }
            }
#endif
        } else { /* VXLIB_CONVERT_POLICY_SATURATE */
            if((invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS)) {

                negAdder = ((uint32_t)1<<(msb-DECIMAL_BITS))-1U;
                negAdder_2 = _itoll(negAdder, negAdder);

                /* Case 2D: SIMD of 4 pixels at a time*/
                /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
                /* 6/8 = 0.75 cycles per pixel */
                #pragma UNROLL(2)
                for( x=0; x < ((width / 8) * 2); x++ ) {
                    src0_8    = _mpysu4ll(ones32, _mem4_const(&src0[x*4]));
                    src1_8    = _mem8_const(&src1[x*4]);

                    mpy1 = _dmpy2(src0_8, src1_8);

                    /* Mask code required if value is negative, to round to zero */
                    /* MISRA.BITS.NOT_UNSIGNED
                     * MISRAC_2004 Rule_12.7
                     * MISRAC_WAIVER:
                     * The C6x DSP compiler treats all types as unsigned when it comes
                     * to the following bitwise operations (&, |, ~, ^).  In this case,
                     * the compiler document requires the 64bit bitwise operations to
                     * use the type "int64_t".
                     */
                    mask32_64 = _dshr(_lo128(mpy1), 31U) & negAdder_2;
                    lo = _dshr(_dadd(_lo128(mpy1), mask32_64), msb-DECIMAL_BITS);
                    mask32_64 = _dshr(_hi128(mpy1), 31U) & negAdder_2;
                    hi = _dshr(_dadd(_hi128(mpy1), mask32_64), msb-DECIMAL_BITS);

                    _mem8(&dst[x*4])   = _itoll((uint32_t)_spack2((int32_t)_hill(hi), (int32_t)_loll(hi)),
                                                (uint32_t)_spack2((int32_t)_hill(lo), (int32_t)_loll(lo)));
                }
                x*=4;
            } else if( (convertScale_u32 & integerMask) == 0 ) {
                /* Case 2E: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == positive integer */
                /* 5/8 = 0.625 cycles per pixel */
                #pragma UNROLL(2)
                for( x=0; x < ((width / 8) * 2); x++ ) {
                    src0_8    = _mpysu4ll(ones32, _mem4_const(&src0[x*4]));
                    src1_8    = _mem8_const(&src1[x*4]);

                    mpy1 = _dmpy2(src0_8, src1_8);
                    mpy2 = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpy1,3U), (int32_t)_get32_128(mpy1,2U)),
                                  (uint32_t)_spack2((int32_t)_get32_128(mpy1,1U), (int32_t)_get32_128(mpy1,0)));
                    mpy1 = _dmpy2(mpy2, convertScale_i4);
                    _mem8(&dst[x*4]) = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpy1,3U), (int32_t)_get32_128(mpy1,2U)),
                                              (uint32_t)_spack2((int32_t)_get32_128(mpy1,1U), (int32_t)_get32_128(mpy1,0)));
                }
                x*=4;

            }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ARBITRARY_SCALE_DISABLED)
            else {
                /* Case 2F: SIMD of 8 pixels at a time*/
                /* 20/8 = 2.5 cycles per pixel (Potential for optimizations here) */
                #pragma UNROLL(8)
                for( x=0; x < ((width / 8) * 8); x++ ) {
                    intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
                    unscaled_result = (VXLIB_D64)intermediate_result;
                    scaled_result = (VXLIB_D64)scale * unscaled_result;
                    int_typed_result = (int32_t)scaled_result;
                    dst[x] = (int16_t)_spack2(0, int_typed_result);
                }
            }
#endif
        }
    }

#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ALIGNED8_WIDTHS)

    if(overflow_policy == VXLIB_CONVERT_POLICY_WRAP) {
        if( (invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS) ) {
            /* Case 3A: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
            /* 2 cycle per pixel */
            for(; x < width; x++ ) {
                temp = (int32_t)src0[x] * (int32_t)src1[x];
                if(temp < 0) {
                    uint32_t shft = (uint32_t)1<<(msb-DECIMAL_BITS);
                    temp+=((int32_t)shft-1);
                }
                /* MISRA.BITS.NOT_UNSIGNED
                 * MISRAC_2004 Rule_12.7
                 * MISRAC_WAIVER:
                 * An arithmetic right shift of the signed integer "temp" by msb-DECIMAL_BITS is required
                 * for performance reasons.  It can not be cast to an unsigned because that would
                 * make a logical right shift instead of the arithmetic shift that I need (I need
                 * the sign bit extension) to mantain negative values.  The above code takes care
                 * of the direction of rounding to replicate a division by a power of 2.  I have
                 * confirmed that the DSP compiler is doing as I expect with this code.
                 */
                temp >>= msb-DECIMAL_BITS;
                dst[x] = (int16_t)temp;
            }
        } else if((convertScale_u32 & integerMask) == 0) {
            /* Case 3B: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == positive integer */
            /* 2 cycles per pixel */
            for(; x < width; x++ ) {
                temp = ((int32_t)src0[x] * (int32_t)src1[x]) * (int32_t)convertScale_i1;
                dst[x] = (int16_t)temp;
            }
        }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ARBITRARY_SCALE_DISABLED)
        else {
            /* Case 3C: Process remaining pixels beyond multiple of 8 */
            /* 4 cycles per pixel (Potential for optimizations here) */
            for(; x < width; x++ ) {
                intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
                unscaled_result = (VXLIB_D64)intermediate_result;
                scaled_result = (VXLIB_D64)scale * unscaled_result;
                dst[x] = (int16_t)scaled_result;
            }
        }
#endif
    } else { /* VXLIB_CONVERT_POLICY_SATURATE */
        if( (invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS) ) {

            uint32_t nAdder = ((uint32_t)1<<(msb-DECIMAL_BITS))-1U;
            int32_t mask;

            /* Case 3D: Process remaining pixels beyond multiple of 4 */
            /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
            /* 2 cycle per pixel */
            for(; x < width; x++ ) {
                int32_t mask_ones;
                uint32_t mask_unsigned;
                temp = (int32_t)src0[x] * (int32_t)src1[x];
                /* MISRA.BITS.NOT_UNSIGNED
                 * MISRAC_2004 Rule_12.7
                 * MISRAC_WAIVER:
                 * An arithmetic right shift of the signed integer "temp" by 31U and again by
                 * msb-DECIMAL_BITS  in 2 out of the next 3 lines is required
                 * for performance reasons.  It can not be cast to an unsigned because that would
                 * make a logical right shift instead of the arithmetic shift that I need (I need
                 * the sign bit extension) to mantain negative values.  The above code takes care
                 * of the direction of rounding to replicate a division by a power of 2.  I have
                 * confirmed that the DSP compiler is doing as I expect with this code.
                 *
                 * Likewise the DSP compiler considers all bitwise operations
                 * ("&" for example in the next line) as unsigned, which is what I expect in the code below.
                 */
                mask_ones = temp>>31;
                mask_unsigned = (uint32_t)mask_ones & nAdder;
                mask =  (int32_t)mask_unsigned;
                temp += mask;
                temp >>= msb-DECIMAL_BITS;
                dst[x] = (int16_t)_spack2(0, temp);
            }
        } else if((convertScale_u32 & integerMask) == 0) {
            /* Case 3E: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == positive integer */
            /* 2 cycles per pixel */
            for(; x < width; x++ ) {
                temp = ((int32_t)src0[x] * (int32_t)src1[x]) * (int32_t)convertScale_i1;
                dst[x] = (int16_t)_spack2(0, temp);
            }
        }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ARBITRARY_SCALE_DISABLED)
        else {
            /* Case 3F: Process remaining pixels beyond multiple of 8 */
            /* 4 cycles per pixel (Potential for optimizations here) */
            for(; x < width; x++ ) {
                intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
                unscaled_result = (VXLIB_D64)intermediate_result;
                scaled_result = (VXLIB_D64)scale * unscaled_result;
                int_typed_result = (int32_t)scaled_result;
                dst[x] = (int16_t)_spack2(0, int_typed_result);
            }
        }
#endif
    }
#endif
}

VXLIB_STATUS VXLIB_multiply_i8u_i16s_o16s(const uint8_t src0[restrict],
                                   const VXLIB_bufParams2D_t *src0_addr,
                                   const int16_t src1[restrict],
                                   const VXLIB_bufParams2D_t *src1_addr,
                                   int16_t dst[restrict],
                                   const VXLIB_bufParams2D_t *dst_addr,
                                   uint16_t overflow_policy,
                                   VXLIB_F32 scale)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MULTIPLY_I8U_I16S_O16S_CHECK_PARAMS)
    status = VXLIB_multiply_i8u_i16s_o16s_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr, overflow_policy, scale);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           ((2 * src1_addr->dim_x) == src1_addr->stride_y) &&
           ((2 * dst_addr->dim_x) == dst_addr->stride_y))
#endif
        {
            VXLIB_multiply_i8u_i16s_o16s_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y, overflow_policy, scale);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[ y * src0_addr->stride_y];
                const int16_t   *src1_t = (const int16_t *)&src1[ y * (src1_addr->stride_y / 2) ];
                int16_t         *dst_t  = (int16_t *)&dst[ y * (dst_addr->stride_y / 2) ];

                VXLIB_multiply_i8u_i16s_o16s_core(src0_t, src1_t, dst_t, src0_addr->dim_x, overflow_policy, scale);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MULTIPLY_I8U_I16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MULTIPLY_I8U_I16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_multiply_i8u_i16s_o16s_checkParams(const uint8_t src0[],
                                               const VXLIB_bufParams2D_t *src0_addr,
                                               const int16_t src1[],
                                               const VXLIB_bufParams2D_t *src1_addr,
                                               const int16_t dst[],
                                               const VXLIB_bufParams2D_t *dst_addr,
                                               uint16_t overflow_policy,
                                               VXLIB_F32 scale)
{
    VXLIB_STATUS    status;

    if((src0 == NULL) || (src1 == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src0_addr->dim_x != src1_addr->dim_x) ||
              (src0_addr->dim_x != dst_addr->dim_x) ||
              (src0_addr->dim_y != src1_addr->dim_y) ||
              (src0_addr->dim_y != dst_addr->dim_y) ||
              (src0_addr->stride_y < src0_addr->dim_x) ||
              (src1_addr->stride_y < (2 * src0_addr->dim_x)) ||
              (dst_addr->stride_y < (2 * dst_addr->dim_x))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
               (src1_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((overflow_policy != VXLIB_CONVERT_POLICY_WRAP) &&
               (overflow_policy != VXLIB_CONVERT_POLICY_SATURATE)) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_MULTIPLY_I8U_I16S_O16S_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            ((2 * src1_addr->dim_x) != src1_addr->stride_y) ||
            ((2 * dst_addr->dim_x) != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_MULTIPLY_I8U_I16S_O16S_ALIGNED8_WIDTHS)
    else if(((src0_addr->dim_x % 8U) != 0) ||
            ((src1_addr->dim_x % 8U) != 0) ||
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

