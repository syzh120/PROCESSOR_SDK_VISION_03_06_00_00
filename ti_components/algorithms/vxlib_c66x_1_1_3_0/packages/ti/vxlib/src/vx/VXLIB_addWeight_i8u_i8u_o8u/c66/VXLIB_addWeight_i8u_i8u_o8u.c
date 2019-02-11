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

#include "VXLIB_addWeight_i8u_i8u_o8u.h"

CODE_SECTION(VXLIB_addWeight_i8u_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_addWeight_i8u_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_addWeight_i8u_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_addWeight_i8u_i8u_o8u_core(const uint8_t src0[restrict],
                               const uint8_t src1[restrict],
                               uint8_t dst[restrict],
                               int32_t width,
                               VXLIB_F32 alpha);

static void VXLIB_addWeight_i8u_i8u_o8u_core(const uint8_t src0[restrict],
                               const uint8_t src1[restrict],
                               uint8_t dst[restrict],
                               int32_t width,
                               VXLIB_F32 alpha)
{
    int32_t    x;

    VXLIB_F32   alpha_inv = 1.0f - alpha;
    int64_t    src0_8, src1_8;
    __x128_t    src0_8x2, src1_8x2;
    int64_t    ones = 0x0101010101010101;
    __float2_t  alpha_2    = _ftof2(alpha, alpha);
    __float2_t  alpha_inv2 = _ftof2(alpha_inv, alpha_inv);
    __float2_t  src0_fA, src0_fB, src0_fC, src0_fD;
    __float2_t  src1_fA, src1_fB, src1_fC, src1_fD;
    __float2_t  sum_fA, sum_fB, sum_fC, sum_fD;

#ifdef FLOAT_TRUNC
    /* This code will configure the floating point instructions to
     * trunc toward zero during the operations instead of rounding.
     * The natural c version uses the SPTRUNC instruction when doing
     * a cast from f32 to int (as expected), however this optimized
     * code uses dspinth instruction, which rounds by default, unless
     * this configuration is done.  The problem is that the exact
     * match between this function and natural c won't happen unless
     * this code is also surrounding the natural c code since it
     * also affects the rounding of the floating point adds which
     * are in both functions, so disabling for now since I don't
     * want to add this code to the natural c function. */

    uint32_t fmode          = _getFADCR();
    uint32_t roundModeMask  = 0x06000600;
    uint32_t roundModeTrunc = 0x02000200;
    uint32_t setMode = (fmode & ~(roundModeMask)) | roundModeTrunc;

    _setFADCR(setMode);
#endif

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0) &&
       (((uint32_t)src1 % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 5/8 = 0.625 cycles per pixel */
        for( x=0; x < ((width / 8) * 8); x+=8 ) {
            /* Read 8 pixels at once */
            src0_8 = _amem8_const(&src0[x]);
            src1_8 = _amem8_const(&src1[x]);

            /* Expand from 1 byte each to 2 bytes each */
            src0_8x2 = _dmpyu4(src0_8, ones);
            src1_8x2 = _dmpyu4(src1_8, ones);

            /* Convert all to float */
            src0_fA = _dinthspu(_get32_128(src0_8x2, 0));
            src0_fB = _dinthspu(_get32_128(src0_8x2, 1U));
            src0_fC = _dinthspu(_get32_128(src0_8x2, 2U));
            src0_fD = _dinthspu(_get32_128(src0_8x2, 3U));
            src1_fA = _dinthspu(_get32_128(src1_8x2, 0));
            src1_fB = _dinthspu(_get32_128(src1_8x2, 1U));
            src1_fC = _dinthspu(_get32_128(src1_8x2, 2U));
            src1_fD = _dinthspu(_get32_128(src1_8x2, 3U));

            /* Multiply all against weight */
            src0_fA = _dmpysp(alpha_2, src0_fA);
            src0_fB = _dmpysp(alpha_2, src0_fB);
            src0_fC = _dmpysp(alpha_2, src0_fC);
            src0_fD = _dmpysp(alpha_2, src0_fD);
            src1_fA = _dmpysp(alpha_inv2, src1_fA);
            src1_fB = _dmpysp(alpha_inv2, src1_fB);
            src1_fC = _dmpysp(alpha_inv2, src1_fC);
            src1_fD = _dmpysp(alpha_inv2, src1_fD);

            /* Add weighted sources */
            sum_fA = _daddsp(src0_fA, src1_fA);
            sum_fB = _daddsp(src0_fB, src1_fB);
            sum_fC = _daddsp(src0_fC, src1_fC);
            sum_fD = _daddsp(src0_fD, src1_fD);

            /* Convert to u8 */
            _amem8(&dst[x]) = _dspacku4(_itoll(_dspinth(sum_fB), _dspinth(sum_fA)),
                                        _itoll(_dspinth(sum_fD), _dspinth(sum_fC)));
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 6/8 = 0.75 cycles per pixel */
        for( x=0; x < ((width / 8) * 8); x+=8 ) {
            /* Read 8 pixels at once */
            src0_8 = _mem8_const(&src0[x]);
            src1_8 = _mem8_const(&src1[x]);

            /* Expand from 1 byte each to 2 bytes each */
            src0_8x2 = _dmpyu4(src0_8, ones);
            src1_8x2 = _dmpyu4(src1_8, ones);

            /* Convert all to float */
            src0_fA = _dinthspu(_get32_128(src0_8x2, 0));
            src0_fB = _dinthspu(_get32_128(src0_8x2, 1U));
            src0_fC = _dinthspu(_get32_128(src0_8x2, 2U));
            src0_fD = _dinthspu(_get32_128(src0_8x2, 3U));
            src1_fA = _dinthspu(_get32_128(src1_8x2, 0));
            src1_fB = _dinthspu(_get32_128(src1_8x2, 1U));
            src1_fC = _dinthspu(_get32_128(src1_8x2, 2U));
            src1_fD = _dinthspu(_get32_128(src1_8x2, 3U));

            /* Multiply all against weight */
            src0_fA = _dmpysp(alpha_2, src0_fA);
            src0_fB = _dmpysp(alpha_2, src0_fB);
            src0_fC = _dmpysp(alpha_2, src0_fC);
            src0_fD = _dmpysp(alpha_2, src0_fD);
            src1_fA = _dmpysp(alpha_inv2, src1_fA);
            src1_fB = _dmpysp(alpha_inv2, src1_fB);
            src1_fC = _dmpysp(alpha_inv2, src1_fC);
            src1_fD = _dmpysp(alpha_inv2, src1_fD);

            /* Add weighted sources */
            sum_fA = _daddsp(src0_fA, src1_fA);
            sum_fB = _daddsp(src0_fB, src1_fB);
            sum_fC = _daddsp(src0_fC, src1_fC);
            sum_fD = _daddsp(src0_fD, src1_fD);

            /* Convert to u8 */
            _mem8(&dst[x]) = _dspacku4(_itoll(_dspinth(sum_fB), _dspinth(sum_fA)),
                                       _itoll(_dspinth(sum_fD), _dspinth(sum_fC)));
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_ALIGNED8_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 8 */
    /* 2 cycle per pixel */
    for(; x < width; x++ ) {
        VXLIB_F32 temp1 = alpha_inv * (VXLIB_F32)src1[x];
        VXLIB_F32 temp2 = alpha * (VXLIB_F32)src0[x];
        VXLIB_F32 result = temp1 + temp2;
        int32_t  tempDst = (int32_t)result;
        dst[x] = (uint8_t)tempDst;
    }

#endif
#ifdef FLOAT_TRUNC
    _setFADCR(fmode);
#endif
}

VXLIB_STATUS VXLIB_addWeight_i8u_i8u_o8u(const uint8_t src0[restrict],
                           const VXLIB_bufParams2D_t *src0_addr,
                           const uint8_t src1[restrict],
                           const VXLIB_bufParams2D_t *src1_addr,
                           uint8_t dst[restrict],
                           const VXLIB_bufParams2D_t *dst_addr,
                           VXLIB_F32 alpha)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_addWeight_i8u_i8u_o8u_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr, alpha);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           (src1_addr->dim_x == src1_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y))
#endif
        {
            VXLIB_addWeight_i8u_i8u_o8u_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y, alpha);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[y * src0_addr->stride_y];
                const uint8_t   *src1_t = (const uint8_t *)&src1[y * src1_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[y * dst_addr->stride_y];

                VXLIB_addWeight_i8u_i8u_o8u_core(src0_t, src1_t, dst_t, src0_addr->dim_x, alpha);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_addWeight_i8u_i8u_o8u_checkParams(const uint8_t src0[],
                                       const VXLIB_bufParams2D_t *src0_addr,
                                       const uint8_t src1[],
                                       const VXLIB_bufParams2D_t *src1_addr,
                                       const uint8_t dst[],
                                       const VXLIB_bufParams2D_t *dst_addr,
                                       VXLIB_F32 alpha)
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
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            (src1_addr->dim_x != src1_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src0 % 8U) != 0) ||
            (((uint32_t)src1 % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src0_addr->stride_y % 8U) != 0) ||
            ((src1_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_ADDWEIGHT_I8U_I8U_O8U_ALIGNED8_WIDTHS)
    else if(((src0_addr->dim_x % 8U) != 0) ||
            ((src1_addr->dim_x % 8U) != 0) ||
            ((dst_addr->dim_x % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else if((alpha < 0.0f) || (alpha > 1.0f)) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

