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

#include "VXLIB_multiply_i8u_i8u_o8u.h"

CODE_SECTION(VXLIB_multiply_i8u_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_multiply_i8u_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_multiply_i8u_i8u_o8u_checkParams,  ".text:optimized")

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

static void VXLIB_multiply_i8u_i8u_o8u_core(const uint8_t src0[restrict],
                                 const uint8_t src1[restrict],
                                 uint8_t dst[restrict],
                                 int32_t width,
                                 uint16_t overflow_policy,
                                 VXLIB_F32 scale);

static void VXLIB_multiply_i8u_i8u_o8u_core(const uint8_t src0[restrict],
                                 const uint8_t src1[restrict],
                                 uint8_t dst[restrict],
                                 int32_t width,
                                 uint16_t overflow_policy,
                                 VXLIB_F32 scale)
{
    int32_t    x;
    int32_t    intermediate_result;
    __x128_t    mpy1, mpylo, mpyhi;
    int64_t    lo, hi, mpy2;

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ALIGNED8_WIDTHS)
    uint32_t    temp;
#endif
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
    int32_t    int_typed_result;
    VXLIB_D64   unscaled_result, scaled_result;
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
    int32_t f32_wrap_flag = 0, f32_sat_flag = 0;
    uint32_t convertScale_u8  = convertScale_i1 & 0xffU;
    uint32_t convertScale_x4  = (convertScale_u8 << 24) |
                                 (convertScale_u8 << 16) |
                                 (convertScale_u8 << 8) |
                                 (convertScale_u8);
    int64_t convertScale_i8   = _itoll(convertScale_x4, convertScale_x4);

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0) &&
       (((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        _nassert(((uint32_t)src0 % 8U) == 0);
        _nassert(((uint32_t)src1 % 8U) == 0);
        _nassert(((uint32_t)dst % 8U) == 0);
        if(overflow_policy == VXLIB_CONVERT_POLICY_WRAP) {

            if( (invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS) ) {
                /* Case 1A: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
                /* 2/8 = 0.25 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_amem8_const(&src0[x*8]), _amem8_const(&src1[x*8]));
                    lo = _dshru2(_lo128(mpy1), msb-DECIMAL_BITS);
                    hi = _dshru2(_hi128(mpy1), msb-DECIMAL_BITS);
                    _amem8(&dst[x*8]) = _itoll(_packl4(_hill(hi), _loll(hi)),
                                               _packl4(_hill(lo), _loll(lo)));
                }
                x*=8;
            } else if((convertScale_u32 & integerMask) == 0) {
                /* Case 1B: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == positive integer */
                /* 2/8 = 0.25 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_amem8_const(&src0[x*8]), _amem8_const(&src1[x*8]));
                    mpy2 = _itoll(_packl4(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                  _packl4(_get32_128(mpy1,1U), _get32_128(mpy1,0U)));
                    mpy1 = _dmpyu4(mpy2, convertScale_i8);
                    _amem8(&dst[x*8]) = _itoll(_packl4(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                               _packl4(_get32_128(mpy1,1U), _get32_128(mpy1,0U)));
                }
                x*=8;
            }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
            else {
                /* Case 1C: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /* 17/8 = 2.125 cycles per pixel (Potential for optimizations here) */
                f32_wrap_flag = 1;
            }
#endif
        } else { /* VXLIB_CONVERT_POLICY_SATURATE */
            if( (invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS) ) {
                /* Case 1D: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
                /* 2/8 = 0.25 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_amem8_const(&src0[x*8]), _amem8_const(&src1[x*8]));
                    lo = _dshru2(_lo128(mpy1), msb-DECIMAL_BITS);
                    hi = _dshru2(_hi128(mpy1), msb-DECIMAL_BITS);
                    _amem8(&dst[x*8])  = _itoll((uint32_t)_spacku4((int32_t)_hill(hi), (int32_t)_loll(hi)),
                                                (uint32_t)_spacku4((int32_t)_hill(lo), (int32_t)_loll(lo)));
                }
                x*=8;
            } else if( (convertScale_u32 & integerMask) == 0 ) {
                /* Case 1E: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == positive integer */
                /* 3/8 = 0.375 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_amem8_const(&src0[x*8]), _amem8_const(&src1[x*8]));
                    mpylo = _dmpyu2(_lo128(mpy1), convertScale_i4);
                    mpyhi = _dmpyu2(_hi128(mpy1), convertScale_i4);
                    lo = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpylo,3U), (int32_t)_get32_128(mpylo,2U)),
                                (uint32_t)_spack2((int32_t)_get32_128(mpylo,1U), (int32_t)_get32_128(mpylo,0)));
                    hi = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpyhi,3U), (int32_t)_get32_128(mpyhi,2U)),
                                (uint32_t)_spack2((int32_t)_get32_128(mpyhi,1U), (int32_t)_get32_128(mpyhi,0)));
                    _amem8(&dst[x*8])     = _itoll((uint32_t)_spacku4((int32_t)_hill(hi), (int32_t)_loll(hi)),
                                                   (uint32_t)_spacku4((int32_t)_hill(lo), (int32_t)_loll(lo)));
                }
                x*=8;
            }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
            else {
                /* Case 1F: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /* 17/8 = 2.125 cycles per pixel (Potential for optimizations here) */
                f32_sat_flag = 1;
            }
#endif
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {

        if((overflow_policy == VXLIB_CONVERT_POLICY_WRAP)) {

            if( (invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS)) {
                /* Case 2A: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
                /* 3/8 = 0.375 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_mem8_const(&src0[x*8]), _mem8_const(&src1[x*8]));
                    lo = _dshru2(_lo128(mpy1), msb-DECIMAL_BITS);
                    hi = _dshru2(_hi128(mpy1), msb-DECIMAL_BITS);
                    _mem8(&dst[x*8]) = _itoll(_packl4(_hill(hi), _loll(hi)),
                                              _packl4(_hill(lo), _loll(lo)));
                }
                x*=8;
            } else if((convertScale_u32 & integerMask) == 0) {
                /* Case 2B: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == positive integer */
                /* 3/8 = 0.375 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_mem8_const(&src0[x*8]), _mem8_const(&src1[x*8]));
                    mpy2 = _itoll(_packl4(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                  _packl4(_get32_128(mpy1,1U), _get32_128(mpy1,0U)));
                    mpy1 = _dmpyu4(mpy2, convertScale_i8);
                    _mem8(&dst[x*8]) = _itoll(_packl4(_get32_128(mpy1,3U), _get32_128(mpy1,2U)),
                                              _packl4(_get32_128(mpy1,1U), _get32_128(mpy1,0U)));
                }
                x*=8;

            }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
            else {
                /* Case 2C: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /* 17/8 = 2.125 cycles per pixel (Potential for optimizations here) */
                f32_wrap_flag = 1;
            }
#endif
        } else { /* VXLIB_CONVERT_POLICY_SATURATE */
            if( (invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS)) {
                /* Case 2D: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
                /* 3/8 = 0.375 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_mem8_const(&src0[x*8]), _mem8_const(&src1[x*8]));
                    lo = _dshru2(_lo128(mpy1), msb-DECIMAL_BITS);
                    hi = _dshru2(_hi128(mpy1), msb-DECIMAL_BITS);
                    _mem8(&dst[x*8])  = _itoll((uint32_t)_spacku4((int32_t)_hill(hi), (int32_t)_loll(hi)),
                                               (uint32_t)_spacku4((int32_t)_hill(lo), (int32_t)_loll(lo)));
                }
                x*=8;
            } else if( (convertScale_u32 & integerMask) == 0 ) {
                /* Case 2E: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /*          Optimized for scale == positive integer */
                /* 3/8 = 0.375 cycles per pixel */
                for( x=0; x < ((width / 8)); x++ ) {
                    mpy1 = _dmpyu4(_mem8_const(&src0[x*8]), _mem8_const(&src1[x*8]));
                    mpylo = _dmpyu2(_lo128(mpy1), convertScale_i4);
                    mpyhi = _dmpyu2(_hi128(mpy1), convertScale_i4);
                    lo = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpylo,3U), (int32_t)_get32_128(mpylo,2U)),
                                (uint32_t)_spack2((int32_t)_get32_128(mpylo,1U), (int32_t)_get32_128(mpylo,0)));
                    hi = _itoll((uint32_t)_spack2((int32_t)_get32_128(mpyhi,3U), (int32_t)_get32_128(mpyhi,2U)),
                                (uint32_t)_spack2((int32_t)_get32_128(mpyhi,1U), (int32_t)_get32_128(mpyhi,0)));
                    _mem8(&dst[x*8])     = _itoll((uint32_t)_spacku4((int32_t)_hill(hi), (int32_t)_loll(hi)),
                                                  (uint32_t)_spacku4((int32_t)_hill(lo), (int32_t)_loll(lo)));
                }
                x*=8;

            }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
            else {
                /* Case 2F: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
                /* 17/8 = 2.125 cycles per pixel (Potential for optimizations here) */
                f32_sat_flag = 1;
            }
#endif
        }
    }

#endif
    /* The non-optimized cases perform the same (for now) whether it is aligned or non-aligned, so put once here
     * to save instruction memory */
    if(f32_wrap_flag != 0) {
        /* Case xF: SIMD of 8 pixels at a time*/
        /* 17/8 = 2.125 cycles per pixel (Potential for optimizations here) */
        #pragma MUST_ITERATE(0,,8)
        for( x=0; x < ((width / 8) * 8); x++ ) {
            intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
            unscaled_result = (VXLIB_D64)intermediate_result;
            scaled_result = (VXLIB_D64)scale * unscaled_result;
            int_typed_result = (int32_t)scaled_result;
            dst[x] = (uint8_t)int_typed_result;
        }
    } else if(f32_sat_flag != 0) {
        /* Case xF: SIMD of 8 pixels at a time*/
        /* 17/8 = 2.125 cycles per pixel (Potential for optimizations here) */
        #pragma UNROLL(8)
        for( x=0; x < ((width / 8) * 8); x++ ) {
            intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
            unscaled_result = (VXLIB_D64)intermediate_result;
            scaled_result = (VXLIB_D64)scale * unscaled_result;
            int_typed_result = (int32_t)scaled_result;
            dst[x] = (int_typed_result > UINT8_MAX) ? UINT8_MAX : (uint8_t)int_typed_result;
        }
    } else {
        /* One of the optimized cases were already executed */
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ALIGNED8_WIDTHS)

    if( overflow_policy == VXLIB_CONVERT_POLICY_WRAP) {
        if((invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS) ) {
            /* Case 3A: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
            /* 2 cycle per pixel */
            for(; x < width; x++ ) {
                temp = (src0[x] * src1[x]) >> (msb-DECIMAL_BITS);
                dst[x] = (uint8_t)temp;
            }

        } else if((convertScale_u32 & integerMask) == 0) {
            /* Case 3B: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == positive integer */
            /* 2 cycles per pixel */
            for(; x < width; x++ ) {
                temp = ((uint32_t)src0[x] * (uint32_t)src1[x]) * convertScale_i1;
                dst[x] = (uint8_t)temp;
            }
        }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
        else {
            /* Case 3C: Process remaining pixels beyond multiple of 8 */
            /* 4 cycles per pixel (Potential for optimizations here) */
            for(; x < width; x++ ) {
                intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
                unscaled_result = (VXLIB_D64)intermediate_result;
                scaled_result = (VXLIB_D64)scale * unscaled_result;
                int_typed_result = (int32_t)scaled_result;
                dst[x] = (uint8_t)int_typed_result;
            }
        }
#endif
    } else { /* VXLIB_CONVERT_POLICY_SATURATE */
        if((invertScale_u32 == ((uint32_t)1<<msb)) && (msb > DECIMAL_BITS) ) {
            /* Case 3D: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == 1/2^n, where n = 1..15 ( power of 2 division ) */
            /* 2 cycle per pixel */
            for(; x < width; x++ ) {
                temp = (src0[x] * src1[x]) >> (msb-DECIMAL_BITS);
                dst[x] = (temp > (uint8_t)UINT8_MAX) ? UINT8_MAX : (uint8_t)temp;
            }

        } else if((convertScale_u32 & integerMask) == 0) {
            /* Case 3E: Process remaining pixels beyond multiple of 8 */
            /*          Optimized for scale == positive integer */
            /* 2 cycles per pixel */
            for(; x < width; x++ ) {
                temp = ((uint32_t)src0[x] * (uint32_t)src1[x]) * convertScale_i1;
                dst[x] = (temp > (uint8_t)UINT8_MAX) ? UINT8_MAX : (uint8_t)temp;
            }
        }
#if !defined(VXLIB_ARBITRARY_SCALE_DISABLED) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ARBITRARY_SCALE_DISABLED)
        else {
            /* Case 3F: Process remaining pixels beyond multiple of 8 */
            /* 4 cycles per pixel (Potential for optimizations here) */
            for(; x < width; x++ ) {
                intermediate_result = (int32_t)src0[x] * (int32_t)src1[x];
                unscaled_result = (VXLIB_D64)intermediate_result;
                scaled_result = (VXLIB_D64)scale * unscaled_result;
                int_typed_result = (int32_t)scaled_result;
                dst[x] = (int_typed_result > UINT8_MAX) ? UINT8_MAX : (uint8_t)int_typed_result;
            }
        }
#endif
    }
#endif
}

VXLIB_STATUS VXLIB_multiply_i8u_i8u_o8u(const uint8_t src0[restrict],
                             const VXLIB_bufParams2D_t *src0_addr,
                             const uint8_t src1[restrict],
                             const VXLIB_bufParams2D_t *src1_addr,
                             uint8_t dst[restrict],
                             const VXLIB_bufParams2D_t *dst_addr,
                             uint16_t overflow_policy,
                             VXLIB_F32 scale)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MULTIPLY_I8U_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_multiply_i8u_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr, overflow_policy, scale);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           (src1_addr->dim_x == src1_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y))
#endif
        {
            VXLIB_multiply_i8u_i8u_o8u_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y, overflow_policy, scale);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[y * src0_addr->stride_y];
                const uint8_t   *src1_t = (const uint8_t *)&src1[y * src1_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[y * dst_addr->stride_y];

                VXLIB_multiply_i8u_i8u_o8u_core(src0_t, src1_t, dst_t, src0_addr->dim_x, overflow_policy, scale);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MULTIPLY_I8U_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MULTIPLY_I8U_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_multiply_i8u_i8u_o8u_checkParams(const uint8_t src0[],
                                         const VXLIB_bufParams2D_t *src0_addr,
                                         const uint8_t src1[],
                                         const VXLIB_bufParams2D_t *src1_addr,
                                         const uint8_t dst[],
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
              (src1_addr->stride_y < src0_addr->dim_x) ||
              (dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
               (src1_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((overflow_policy != VXLIB_CONVERT_POLICY_WRAP) &&
               (overflow_policy != VXLIB_CONVERT_POLICY_SATURATE)) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_MULTIPLY_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_MULTIPLY_I8U_I8U_O8U_ALIGNED8_WIDTHS)
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

