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

#include "VXLIB_convolve_5x5_i8u_c16s_o8u.h"

#define CONV_SIZE 5

CODE_SECTION(VXLIB_convolve_5x5_i8u_c16s_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_convolve_5x5_i8u_c16s_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_convolve_5x5_i8u_c16s_o8u_checkParams,  ".text:optimized")

static void VXLIB_convolve_5x5_i8u_c16s_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  const int16_t conv_mat[restrict],
                                  uint32_t shift);

static void VXLIB_convolve_5x5_i8u_c16s_o8u_core(const uint8_t src[restrict],
                                  uint8_t dst[restrict],
                                  int32_t srcStride,
                                  int32_t outWidth,
                                  const int16_t conv_mat[restrict],
                                  uint32_t shift)
{
    int32_t x;
    int64_t mask_tmp, mask3_0, mask7_4, mask11_8, mask15_12, mask19_16, mask23_20;

    uint32_t mask44,     mask55,     mask24;
    uint32_t mask15_15,  mask24_24,  mask14_14;

    int64_t ones = 0x0000010101010101;

    /* Fetch and reverse the convolution matrix */
    mask_tmp  = _mem8_const(&conv_mat[21]);
    mask_tmp  =  _dpacklh2(mask_tmp, mask_tmp);
    mask3_0   = _itoll(_loll(mask_tmp), _hill(mask_tmp));

    mask_tmp  = _mem8_const(&conv_mat[17]);
    mask_tmp  =  _dpacklh2(mask_tmp, mask_tmp);
    mask7_4   = _itoll(_loll(mask_tmp), _hill(mask_tmp));

    mask_tmp  = _mem8_const(&conv_mat[13]);
    mask_tmp  =  _dpacklh2(mask_tmp, mask_tmp);
    mask11_8  = _itoll(_loll(mask_tmp), _hill(mask_tmp));

    mask_tmp  = _mem8_const(&conv_mat[9]);
    mask_tmp  =  _dpacklh2(mask_tmp, mask_tmp);
    mask15_12 = _itoll(_loll(mask_tmp), _hill(mask_tmp));

    mask_tmp  = _mem8_const(&conv_mat[5]);
    mask_tmp  =  _dpacklh2(mask_tmp, mask_tmp);
    mask19_16 = _itoll(_loll(mask_tmp), _hill(mask_tmp));

    mask_tmp  = _mem8_const(&conv_mat[1]);
    mask_tmp  =  _dpacklh2(mask_tmp, mask_tmp);
    mask23_20 = _itoll(_loll(mask_tmp), _hill(mask_tmp));
    
    mask24    = (uint32_t)conv_mat[0];

    mask44    = _pack2 (_loll(mask7_4),  _loll(mask7_4));
    mask55    = _packh2(_loll(mask7_4),  _loll(mask7_4));
    mask14_14 = _pack2 (_hill(mask15_12),_hill(mask15_12));
    mask15_15 = _packh2(_hill(mask15_12),_hill(mask15_12));
    mask24_24 = _pack2 (mask24,mask24);


    /* Case 1: SIMD of 2 output pixels at a time */
    /* 9/2 = 4.5 cycles per pixel */
    for(x=0; x < (outWidth/2); x++) {

        __x128_t row;
        int64_t temp1, temp2, temp3, r1, row_5432, sum_2;
        uint32_t      row_10;

        /* ---------------- */
        /* Operate on row 0 */
        /* ---------------- */

        /* Read 8 bytes from first line (will only use first 6 pixels to generate 2 outputs */
        r1    =   _mem8_const(&src[(srcStride*0) + (x*2)]);

        /* Convert to 2 bytes per pixel */
        row = _dmpyu4(r1,ones);

        /* Perform the partial multiplications of input pixel with corre- */
        /* ponding mask for the first and second sample outputs           */
        temp1       = _ddotpl2(_lo128(row),_loll(mask3_0));
        temp2       = _ddotpl2(_itoll(_get32_128(row, 2U),_get32_128(row, 1U)),_hill(mask3_0));
        temp3       = _mpy2ll((int32_t)_get32_128(row, 2U) , (int32_t)mask44);

        /* Add intermediate sums for the two output pixels */
        sum_2      = _dadd(_dadd(temp1, temp2), temp3);



        /* ---------------- */
        /* Operate on row 1 */
        /* ---------------- */

        /* Read 8 bytes from second line (will only use first 6 pixels to generate 2 outputs */
        r1          = _mem8_const(&src[(srcStride*1) + (x*2)]);

        /* Convert to 2 bytes per pixel */
        row_5432    = _itoll(_unpklu4(_hill(r1)),_unpkhu4(_loll(r1)) );
        row_10      = _unpklu4(_loll(r1));

        /* Perform the partial multiplications of input pixel with corre- */
        /* ponding mask for the first and second sample outputs           */
        temp1       = _ddotph2(_itoll(_loll(row_5432),row_10),_hill(mask7_4));
        temp2       = _ddotph2(row_5432, _loll(mask11_8));
        temp3       = _mpy2ll((int32_t)row_10 , (int32_t)mask55);

        /* Add intermediate sums for the two output pixels */
        sum_2      = _dadd(_dadd(temp1, temp2), _dadd(temp3, sum_2));



        /* ---------------- */
        /* Operate on row 2 */
        /* ---------------- */

        /* Read 8 bytes from third line (will only use first 6 pixels to generate 2 outputs */
        r1          = _mem8_const(&src[(srcStride*2) + (x*2)]);

        /* Convert to 2 bytes per pixel */
        row = _dmpyu4(r1,ones);
        
        /* Perform the partial multiplications of input pixel with corre- */
        /* ponding mask for the first and second sample outputs           */
        temp1       = _ddotpl2(_lo128(row),_hill(mask11_8));
        temp2       = _ddotpl2(_itoll(_get32_128(row, 2U),_get32_128(row, 1U)),_loll(mask15_12));
        temp3       = _mpy2ll((int32_t)_get32_128(row, 2U) , (int32_t)mask14_14);

        /* Add intermediate sums for the two output pixels */
        sum_2      = _dadd(_dadd(temp1, temp2), _dadd(temp3, sum_2));



        /* ---------------- */
        /* Operate on row 3 */
        /* ---------------- */

        /* Read 8 bytes from fourth line (will only use first 6 pixels to generate 2 outputs */
        r1          = _mem8_const(&src[(srcStride*3) + (x*2)]);

        /* Convert to 2 bytes per pixel */
        row_5432 = _itoll(_unpklu4(_hill(r1)),_unpkhu4(_loll(r1)) );
        row_10      = _unpklu4(_loll(r1));

        /* Perform the partial multiplications of input pixel with corre- */
        /* ponding mask for the first and second sample outputs           */
        temp1       = _ddotph2(_itoll(_loll(row_5432),row_10),_loll(mask19_16));
        temp2       = _ddotph2(row_5432,_hill(mask19_16));
        temp3       = _mpy2ll((int32_t)row_10 , (int32_t)mask15_15);

        /* Add intermediate sums for the two output pixels */
        sum_2      = _dadd(_dadd(temp1, temp2), _dadd(temp3, sum_2));



        /* ---------------- */
        /* Operate on row 4 */
        /* ---------------- */

        /* Read 8 bytes from fourth line (will only use first 6 pixels to generate 2 outputs */
        r1          = _mem8_const(&src[(srcStride*4) + (x*2)]);

        /* Convert to 2 bytes per pixel */
        row = _dmpyu4(r1,ones);

        /* Perform the partial multiplications of input pixel with corre- */
        /* ponding mask for the first and second sample outputs           */
        temp1       = _ddotpl2(_lo128(row),_loll(mask23_20));
        temp2       = _ddotpl2(_itoll(_get32_128(row, 2U),_get32_128(row, 1U)),_hill(mask23_20));
        temp3       = _mpy2ll((int32_t)_get32_128(row, 2U), (int32_t)mask24_24);

        /* Add intermediate sums for the two output pixels */
        sum_2      = _dadd(_dadd(temp1, temp2), _dadd(temp3, sum_2));




        /* shift the sum to fall in byte range with user defined value    */
        sum_2       = _dshr(sum_2, shift);

        /* check for saturation and pack two bytes to store using mem2    */
        _mem2(&dst[x*2]) = (uint16_t)_spacku4(0, _spack2((int32_t)_hill(sum_2), (int32_t)_loll(sum_2)));
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 1 || (!defined(VXLIB_ALIGNED2_WIDTHS) && !defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_ALIGNED2_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 2 */
    /* 16 cycle per pixel */
    for(x*=2; x < outWidth; x++) {
        int32_t sum = 0;
        int32_t j, k;
        uint32_t result; 
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

VXLIB_STATUS VXLIB_convolve_5x5_i8u_c16s_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            const int16_t conv_mat[restrict],
                            uint32_t shift)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_CHECK_PARAMS)
    status = VXLIB_convolve_5x5_i8u_c16s_o8u_checkParams(src, src_addr, dst, dst_addr, conv_mat, shift);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_convolve_5x5_i8u_c16s_o8u_core(src, dst, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - (CONV_SIZE-1), conv_mat, shift);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-(CONV_SIZE-1)));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_convolve_5x5_i8u_c16s_o8u_core(src_t, dst_t, src_addr->stride_y, width, conv_mat, shift);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_convolve_5x5_i8u_c16s_o8u_checkParams(const uint8_t src[restrict],
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
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
/* Setting macro to 0 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if 0 && (defined(VXLIB_ALIGNED2_WIDTHS) || defined(VXLIB_CONVOLVE_5X5_I8U_C16S_O8U_ALIGNED2_WIDTHS))
    else if((dst_addr->dim_x % 2U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
