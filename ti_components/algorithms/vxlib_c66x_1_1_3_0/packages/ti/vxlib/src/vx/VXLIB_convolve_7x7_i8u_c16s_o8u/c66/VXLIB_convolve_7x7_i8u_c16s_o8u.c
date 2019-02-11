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

#include "VXLIB_convolve_7x7_i8u_c16s_o8u.h"

#define CONV_SIZE 7

CODE_SECTION(VXLIB_convolve_7x7_i8u_c16s_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_convolve_7x7_i8u_c16s_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_convolve_7x7_i8u_c16s_o8u_checkParams,  ".text:optimized")

static void VXLIB_convolve_7x7_i8u_c16s_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  const int16_t conv_mat[restrict],
                                  const int16_t conv_mat_scratch[restrict],
                                  uint32_t shift);

static void VXLIB_convolve_7x7_i8u_c16s_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  const int16_t conv_mat[restrict],
                                  const int16_t conv_mat_scratch[restrict],
                                  uint32_t shift)
{
    int32_t x, k;
    int64_t ones = 0x0101010101010101;

    /* Case 1: SIMD of 8 output pixels at a time */
    /* 77/8 = 9.625 cycles per pixel */
    for(x=0; x < (outWidth/8); x++) {

        int64_t  sum0=0, sum1=0, sum2=0, sum3=0;
        int64_t  sum4=0, sum5=0, sum6=0, sum7=0;
        int32_t sum0_32, sum1_32, sum2_32, sum3_32;
        int32_t sum4_32, sum5_32, sum6_32, sum7_32;
        int64_t  sum01, sum23, sum45, sum67;

        /*  This loop calculates 8 convolution sums for a single row */
        /* 7/8 = 0.875 cycles per pixel per row + 21 (70 cycles for 8 pixels for all rows) */
        #pragma MUST_ITERATE(7,7,7);
        for (k=0; k<7; k++) {

            /* Load coefficients for row 'k' */
            int64_t mask00   = _mem8_const(&conv_mat_scratch[(k * 8) + 0]);
            int64_t mask01   = _mem8_const(&conv_mat_scratch[(k * 8) + 4]);

            /* Prepare 2 alignments of coefficients for dot product with input row */
            __x128_t mask0 = _llto128(mask01, mask00);
            uint64_t mask0_shft_lo = (uint64_t)_lo128(mask0)<<16;
            __x128_t mask1 = _llto128(_itoll(_packlh2(_get32_128(mask0, 3U), _get32_128(mask0, 2U)),
                                             _packlh2(_get32_128(mask0, 2U), _get32_128(mask0, 1U))),
                                      (int64_t)mask0_shft_lo);

            /* Load 14 pixels that can be used to calculate eight output pixels  */
            int64_t r01    =   _mem8_const(&src[(srcStride*k) + (x*8)]);
            int64_t r67    =   _mem8_const(&src[(srcStride*k) + (x*8)+6]);
            int64_t r23    =   _itoll(_loll(r67), _packlh2(_hill(r01), _loll(r01)));
            int64_t r45    =   _itoll(_packlh2(_hill(r67), _loll(r67)), _hill(r01));

            /* Convert to 2 bytes per pixel */
            __x128_t r01_2 = _dmpyu4(r01, ones);
            __x128_t r67_2 = _dmpyu4(r67, ones);
            __x128_t r23_2 = _dmpyu4(r23, ones);
            __x128_t r45_2 = _dmpyu4(r45, ones);

            /* Dot product of mask to appropriate input for 8 output pixels */
            sum0 = _dadd(_ddotp4h(mask0, r01_2), sum0);
            sum1 = _dadd(_ddotp4h(mask1, r01_2), sum1);
            sum2 = _dadd(_ddotp4h(mask0, r23_2), sum2);
            sum3 = _dadd(_ddotp4h(mask1, r23_2), sum3);
            sum4 = _dadd(_ddotp4h(mask0, r45_2), sum4);
            sum5 = _dadd(_ddotp4h(mask1, r45_2), sum5);
            sum6 = _dadd(_ddotp4h(mask0, r67_2), sum6);
            sum7 = _dadd(_ddotp4h(mask1, r67_2), sum7);
        }

        /* Sum each pair of sums together for final sums */
        sum0_32 = (int32_t)_hill(sum0) + (int32_t)_loll(sum0);
        sum1_32 = (int32_t)_hill(sum1) + (int32_t)_loll(sum1);
        sum2_32 = (int32_t)_hill(sum2) + (int32_t)_loll(sum2);
        sum3_32 = (int32_t)_hill(sum3) + (int32_t)_loll(sum3);
        sum4_32 = (int32_t)_hill(sum4) + (int32_t)_loll(sum4);
        sum5_32 = (int32_t)_hill(sum5) + (int32_t)_loll(sum5);
        sum6_32 = (int32_t)_hill(sum6) + (int32_t)_loll(sum6);
        sum7_32 = (int32_t)_hill(sum7) + (int32_t)_loll(sum7);


        /* Shift the sums to fall in byte range with user defined value */
        sum01 = _dshr(_itoll((uint32_t)sum1_32, (uint32_t)sum0_32), shift);
        sum23 = _dshr(_itoll((uint32_t)sum3_32, (uint32_t)sum2_32), shift);
        sum45 = _dshr(_itoll((uint32_t)sum5_32, (uint32_t)sum4_32), shift);
        sum67 = _dshr(_itoll((uint32_t)sum7_32, (uint32_t)sum6_32), shift);

        /* check for saturation and pack 8 bytes to store output */
        _mem8(&dst[x*8]) = _dspacku4(_itoll((uint32_t)_spack2((int32_t)_hill(sum23), (int32_t)_loll(sum23)),
                                            (uint32_t)_spack2((int32_t)_hill(sum01), (int32_t)_loll(sum01))),
                                     _itoll((uint32_t)_spack2((int32_t)_hill(sum67), (int32_t)_loll(sum67)),
                                            (uint32_t)_spack2((int32_t)_hill(sum45), (int32_t)_loll(sum45))));
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_ALIGNED8_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    for(x*=8; x < outWidth; x++) {
        int32_t sum = 0;
        int32_t j;
        uint32_t result; 
        /* 54 cycles per pixel for one pixel for all 7 rows */
        for(j=0; j < CONV_SIZE; j++) {
            for(k=0; k < CONV_SIZE; k++) {
                sum += ((int32_t)src[(j*srcStride) + (x+k)] * conv_mat[(CONV_SIZE*CONV_SIZE) - 1 - (j*CONV_SIZE) - k]);
            }
        }
        result = (sum < 0) ? 0 : sum;
        result >>= shift;
        result = (result > 255U) ? 255U : result;

        dst[x] = (uint8_t)result;
    }
#endif
}

VXLIB_STATUS VXLIB_convolve_7x7_i8u_c16s_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            const int16_t conv_mat[restrict],
                            uint32_t shift)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_CHECK_PARAMS)
    status = VXLIB_convolve_7x7_i8u_c16s_o8u_checkParams(src, src_addr, dst, dst_addr, conv_mat, shift);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t i;
        int16_t scratch[7*8];

        /* Since not all of the coefficients can fit in registers at once,
         * need to reverse them once and store in scratch memory in order
         * to make it faster for the loop to LOAD one line at a time for each
         * of the 8 output pixels */
        for(i=0; i<7; i++) {
            uint64_t mask00  = _mem8_const(&conv_mat[((6-i) * 7) + 0]);
            int64_t mask01   = _mem8_const(&conv_mat[((6-i) * 7) + 3]);

            mask01  = _dpacklh2(mask01, mask01);
            mask01  = _itoll(_loll(mask01), _hill(mask01));

            mask00  = _dpacklh2(mask00, mask00);
            mask00  = (uint64_t)_itoll(_loll((int64_t)mask00), _hill((int64_t)mask00)) >> 16;
    
            _mem8(&scratch[(i*8)+0]) = mask01;
            _mem8(&scratch[(i*8)+4]) = mask00;
        }

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_convolve_7x7_i8u_c16s_o8u_core(src, dst, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - (CONV_SIZE-1), conv_mat, scratch, shift);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-(CONV_SIZE-1)));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_convolve_7x7_i8u_c16s_o8u_core(src_t, dst_t, src_addr->stride_y, width, conv_mat, scratch, shift);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_convolve_7x7_i8u_c16s_o8u_checkParams(const uint8_t src[restrict],
                                        const VXLIB_bufParams2D_t *src_addr,
                                        const uint8_t dst[restrict],
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
               (dst_addr->stride_y < dst_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(shift > 31U) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_CONVOLVE_7X7_I8U_C16S_O8U_ALIGNED8_WIDTHS))
    else if((dst_addr->dim_x % 8U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
