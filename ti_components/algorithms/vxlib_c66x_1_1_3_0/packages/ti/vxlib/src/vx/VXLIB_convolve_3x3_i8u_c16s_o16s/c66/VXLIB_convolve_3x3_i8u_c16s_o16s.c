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

#include "VXLIB_convolve_3x3_i8u_c16s_o16s.h"

#define CONV_SIZE 3

CODE_SECTION(VXLIB_convolve_3x3_i8u_c16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_convolve_3x3_i8u_c16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_convolve_3x3_i8u_c16s_o16s_checkParams,  ".text:optimized")

static void VXLIB_convolve_3x3_i8u_c16s_o16s_core(const uint8_t src[restrict],
                                  int16_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  const int16_t conv_mat[restrict],
                                  uint32_t shift);

static void VXLIB_convolve_3x3_i8u_c16s_o16s_core(const uint8_t src[restrict],
                                  int16_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  const int16_t conv_mat[restrict],
                                  uint32_t shift)
{
    int32_t x;
    int64_t mask_tmp;
    __x128_t mask_r02, mask_r12, mask_r22;

    int64_t ones = 0x0000010101010101;

    uint32_t negAdder = ((uint32_t)1<<shift)-1U;
    int64_t negAdder_2 = _itoll(negAdder, negAdder);

    /* Fetch and reverse the convolution matrix */
    mask_tmp = _mem8_const(&conv_mat[6]);
    mask_tmp =  _dpacklh2(mask_tmp, mask_tmp);
    mask_tmp = _itoll(_loll(mask_tmp), _hill(mask_tmp) & 0xffff0000U);
    mask_r02 = _llto128(mask_tmp, _dpackx2(_hill(mask_tmp), _loll(mask_tmp)));

    mask_tmp = _mem8_const(&conv_mat[3]);
    mask_tmp =  _dpacklh2(mask_tmp, mask_tmp);
    mask_tmp = _itoll(_loll(mask_tmp), _hill(mask_tmp) & 0xffff0000U);
    mask_r12 = _llto128(mask_tmp, _dpackx2(_hill(mask_tmp), _loll(mask_tmp)));

    mask_tmp = _mem8_const(&conv_mat[0]);
    mask_tmp =  _dpacklh2(mask_tmp, mask_tmp);
    mask_tmp = _itoll(_loll(mask_tmp), _hill(mask_tmp) & 0xffff0000U);
    mask_r22 = _llto128(mask_tmp, _dpackx2(_hill(mask_tmp), _loll(mask_tmp)));

    /* Case 1: SIMD of 4 output pixels at a time */
    /* 7/4 = 1.75 cycles per pixel */
    for(x=0; x < (outWidth/4); x++) {

        int64_t sum10_64, mask10_64, out10_64, sum32_64, mask32_64, out32_64;
        uint32_t out10_32, out32_32;

        /* Read 8 bytes from each of the 3 lines.  Only need 6 bytes,
         * so there is potential for reading 2 bytes beyond input buffer
         * in some cases, but these 2 bytes are not used  by the algo.  */
        int64_t r0_4 = _mem8_const(&src[(srcStride*0) + (x*4)]);
        int64_t r1_4 = _mem8_const(&src[(srcStride*1) + (x*4)]);
        int64_t r2_4 = _mem8_const(&src[(srcStride*2) + (x*4)]);

        /* Convert to 2 bytes per pixel */
        __x128_t r0 = _dmpyu4(r0_4, ones);
        __x128_t r1 = _dmpyu4(r1_4, ones);
        __x128_t r2 = _dmpyu4(r2_4, ones);

        /* Outputs 1 and 0: Convolve the 9 neighborhood pixels for each of 2 pixels */
        __x128_t r02 = _llto128(_lo128(r0), _lo128(r0));
        __x128_t r12 = _llto128(_lo128(r1), _lo128(r1));
        __x128_t r22 = _llto128(_lo128(r2), _lo128(r2));

        sum10_64 = _dadd(_dadd(_ddotp4h(r02, mask_r02), _ddotp4h(r12, mask_r12)),
                               _ddotp4h(r22, mask_r22));
        /* MISRA.BITS.NOT_UNSIGNED
         * MISRAC_2004 Rule_12.7
         * MISRAC_WAIVER:
         * The C6x DSP compiler treats all types as unsigned when it comes
         * to the following bitwise operations (&, |, ~, ^).  In this case,
         * the compiler document requires the 64bit bitwise operations to
         * use the type "int64_t".
         */
        mask10_64 = _dshr(sum10_64, 31U) & negAdder_2;
        out10_64 = _dshr(_dadd(sum10_64, mask10_64), shift);

        out10_32 = (uint32_t)_spack2((int32_t)_hill(out10_64), (int32_t)_loll(out10_64));

        /* Outputs 3 and 2: Convolve the 9 neighborhood pixels for each of 2 pixels */
        r02 = _ito128(_get32_128(r0, 2U), _get32_128(r0, 1U), _get32_128(r0, 2U), _get32_128(r0, 1U));
        r12 = _ito128(_get32_128(r1, 2U), _get32_128(r1, 1U), _get32_128(r1, 2U), _get32_128(r1, 1U));
        r22 = _ito128(_get32_128(r2, 2U), _get32_128(r2, 1U), _get32_128(r2, 2U), _get32_128(r2, 1U));

        sum32_64 = _dadd(_dadd(_ddotp4h(r02, mask_r02), _ddotp4h(r12, mask_r12)),
                               _ddotp4h(r22, mask_r22));
        /* MISRA.BITS.NOT_UNSIGNED
         * MISRAC_2004 Rule_12.7
         * MISRAC_WAIVER:
         * The C6x DSP compiler treats all types as unsigned when it comes
         * to the following bitwise operations (&, |, ~, ^).  In this case,
         * the compiler document requires the 64bit bitwise operations to
         * use the type "int64_t".
         */
        mask32_64 = _dshr(sum32_64, 31U) & negAdder_2;
        out32_64 = _dshr(_dadd(sum32_64, mask32_64), shift);

        out32_32 = (uint32_t)_spack2((int32_t)_hill(out32_64), (int32_t)_loll(out32_64));

        /* Pack the results in to 8 bytes */
        _mem8(&dst[x*4]) = _itoll(out32_32, out10_32);
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED4_WIDTHS) && !defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_ALIGNED4_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 4 */
    /* 5 cycle per pixel */
    for(x*=4; x < outWidth; x++) {
        int32_t sum = 0;
        int32_t j, k;
        int32_t result; 
        for(j=0; j < CONV_SIZE; j++) {
            for(k=0; k < CONV_SIZE; k++) {
                sum += ((int32_t)src[(j*srcStride) + (x+k)] * conv_mat[(CONV_SIZE*CONV_SIZE) - 1 - (j*CONV_SIZE) - k]);
            }
        }

        /* Downshift of a negative number rounds to negative infinity instead of toward 0 */
        if((sum < 0) && (shift > 0)) {
            uint32_t temp = (uint32_t)1<<shift;
            sum+=((int32_t)temp-1);
        }

        /* MISRA.BITS.NOT_UNSIGNED
         * MISRAC_2004 Rule_12.7
         * MISRAC_WAIVER:
         * An arithmetic right shift of the signed integer "sum" by msb is required
         * for performance reasons.  It can not be cast to an unsigned because that would
         * make a logical right shift instead of the arithmetic shift that I need (I need
         * the sign bit extension) to mantain negative values.  The above code takes care
         * of the direction of rounding to replicate a division by a power of 2.  I have
         * confirmed that the DSP compiler is doing as I expect with this code.
         */
        result = (int32_t)(sum>>shift);

        result = (result > INT16_MAX) ? INT16_MAX : result;
        result = (result < INT16_MIN) ? INT16_MIN : result;

        dst[x] = (int16_t)result;
    }
#endif
}

VXLIB_STATUS VXLIB_convolve_3x3_i8u_c16s_o16s(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            int16_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            const int16_t conv_mat[restrict],
                            uint32_t shift)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_CHECK_PARAMS)
    status = VXLIB_convolve_3x3_i8u_c16s_o16s_checkParams(src, src_addr, dst, dst_addr, conv_mat, shift);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           ((dst_addr->dim_x*2) == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_convolve_3x3_i8u_c16s_o16s_core(src, dst, src_addr->stride_y, ((dst_addr->stride_y/2) * dst_addr->dim_y) - (CONV_SIZE-1), conv_mat, shift);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-(CONV_SIZE-1)));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                int16_t         *dst_t  = (int16_t *)&dst[ y * (dst_addr->stride_y/2)];

                VXLIB_convolve_3x3_i8u_c16s_o16s_core(src_t, dst_t, src_addr->stride_y, width, conv_mat, shift);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_convolve_3x3_i8u_c16s_o16s_checkParams(const uint8_t src[restrict],
                                        const VXLIB_bufParams2D_t *src_addr,
                                        const int16_t dst[restrict],
                                        const VXLIB_bufParams2D_t *dst_addr,
                                        const int16_t conv_mat[restrict],
                                        uint32_t shift)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL) || (conv_mat == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x < dst_addr->dim_x) ||
               ((src_addr->dim_y-(CONV_SIZE-1)) !=  dst_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < (dst_addr->dim_x*2)) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(shift > 31U) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             ((dst_addr->dim_x*2) != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED4_WIDTHS) || defined(VXLIB_CONVOLVE_3X3_I8U_C16S_O16S_ALIGNED4_WIDTHS))
    else if((dst_addr->dim_x % 4U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
