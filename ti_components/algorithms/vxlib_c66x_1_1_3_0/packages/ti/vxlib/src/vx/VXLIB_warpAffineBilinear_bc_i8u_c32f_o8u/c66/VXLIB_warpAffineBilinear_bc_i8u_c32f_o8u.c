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

#include "VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u.h"

/* Set float rounding mode to neg infinity when converting to integer */
#define FLOAT_RND_DOWN 1

CODE_SECTION(VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_checkParams,  ".text:optimized")

static inline void VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_core(const uint8_t src[restrict],
                                                       uint8_t dst[restrict],
                                                       __float2_t m10,
                                                       __float2_t m32,
                                                       __float2_t m54,
                                                       int32_t width,
                                                       __float2_t srcOffset,
                                                       uint32_t outputStartX,
                                                       uint32_t outputStartY,
                                                       uint32_t src_width,
                                                       uint32_t src_height,
                                                       uint32_t src_stride,
                                                       uint8_t border_constant_value);

static inline void VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_core(const uint8_t src[restrict],
                                                       uint8_t dst[restrict],
                                                       __float2_t m10,
                                                       __float2_t m32,
                                                       __float2_t m54,
                                                       int32_t width,
                                                       __float2_t srcOffset,
                                                       uint32_t outputStartX,
                                                       uint32_t outputStartY,
                                                       uint32_t src_width,
                                                       uint32_t src_height,
                                                       uint32_t src_stride,
                                                       uint8_t border_constant_value)
{
    int32_t    x;
    __float2_t remap_f, remap_f_trunc, deltas, one_minus_deltas;
    int32_t remap_tl, remap_tr, remap_bl, remap_br;
    VXLIB_F32 coef_tl, coef_tr, coef_bl, coef_br, outf;
    uint32_t tl, tr, bl, br;
    uint32_t out_of_boundsTL, out_of_boundsTR, out_of_boundsBL, out_of_boundsBR;
    __float2_t ones = _ftof2(1.0f, 1.0f);
    int32_t out;

    int32_t maxCmp = (int32_t)_pack2(src_height-1U, src_width-1U);
    uint32_t offsetCalc = (src_stride << 16) + 1U;

    /* Prepare registers for y coordiate SIMD computation */
    __float2_t y2     = _dintspu(_itoll(outputStartY, outputStartY));

    /* Affine equations: */
    /*
     *       | Inside  | Outside loop   |
     *   x' = x * m[0] + y * m[2] + m[4];
     *   y' = x * m[1] + y * m[3] + m[5];
     *
     * The y and offset terms can be computed outside the loop
     */
    __float2_t ym32    = _dmpysp(y2, m32);
    __float2_t ym32m54 = _dsubsp(_daddsp(ym32, m54), srcOffset);

    /* Prepare registers for x coordiate SIMD computation: initialization */
    __float2_t x2_0 = _dintspu(_itoll(outputStartX, outputStartX));

    /* 17/2 = 8.5 cycles per pixel */
    #pragma UNROLL(2)
    for( x=0; x < (width / 1); x++ ) {

        /* Add x terms of affine function to complete equation */
        remap_f = _daddsp(_dmpysp(x2_0, m10), ym32m54);

        /* Round Coordinates down toward negative infinity (finds top-left pixel in source) */
        remap_tl = (int32_t)_dspinth(remap_f);
        remap_tr = _add2(remap_tl, 0x00000001);
        remap_bl = _add2(remap_tl, 0x00010000);
        remap_br = _add2(remap_tl, 0x00010001);

        /* Convert back to float */
        remap_f_trunc = _dinthsp((uint32_t)remap_tl);

        /* Find the deltas */
        deltas = _dsubsp(remap_f, remap_f_trunc);

        /* Calculate the coefficients */
        one_minus_deltas = _dsubsp(ones, deltas);

        coef_tl = _lof2(one_minus_deltas) * _hif2(one_minus_deltas);
        coef_bl = _lof2(one_minus_deltas) * _hif2(deltas);
        coef_tr = _lof2(deltas) * _hif2(one_minus_deltas);
        coef_br = _lof2(deltas) * _hif2(deltas);

        /* Check for out of bounds condition */
        out_of_boundsTL = (uint32_t)_cmpgt2(0, remap_tl) | (uint32_t)_cmpgt2(remap_tl, maxCmp);
        out_of_boundsTR = (uint32_t)_cmpgt2(0, remap_tr) | (uint32_t)_cmpgt2(remap_tr, maxCmp);
        out_of_boundsBL = (uint32_t)_cmpgt2(0, remap_bl) | (uint32_t)_cmpgt2(remap_bl, maxCmp);
        out_of_boundsBR = (uint32_t)_cmpgt2(0, remap_br) | (uint32_t)_cmpgt2(remap_br, maxCmp);

        /* Fetch pixels from src buffer */
        tl = border_constant_value;
        tr = border_constant_value;
        bl = border_constant_value;
        br = border_constant_value;
        if (out_of_boundsTL == 0U)  { tl = src[_dotp2(remap_tl, (int32_t)offsetCalc)]; }
        if (out_of_boundsTR == 0U)  { tr = src[_dotp2(remap_tr, (int32_t)offsetCalc)]; }
        if (out_of_boundsBL == 0U)  { bl = src[_dotp2(remap_bl, (int32_t)offsetCalc)]; }
        if (out_of_boundsBR == 0U)  { br = src[_dotp2(remap_br, (int32_t)offsetCalc)]; }

        /* Perform bilinear interpolation */
        outf = (coef_tl*(VXLIB_F32)tl) + (coef_tr*(VXLIB_F32)tr) + (coef_bl*(VXLIB_F32)bl) + (coef_br*(VXLIB_F32)br) + 0.5f;
        out = (int32_t)outf;

        /* Put result in output buffer */
        dst[x] = (uint8_t)out;

        /* Prepare registers for x coordiate SIMD computation: update for next iteration */
        x2_0 = _daddsp(x2_0, ones);
    }
}

VXLIB_STATUS VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u(const uint8_t src[restrict],
                                                  const VXLIB_bufParams2D_t *src_addr,
                                                  uint8_t dst[restrict],
                                                  const VXLIB_bufParams2D_t *dst_addr,
                                                  const VXLIB_F32 warpMatrix[6],
                                                  uint8_t border_constant_value,
                                                  int16_t srcOffsetX,
                                                  int16_t srcOffsetY,
                                                  int16_t dstOffsetX,
                                                  int16_t dstOffsetY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_CHECK_PARAMS)
    status = VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_checkParams(src, src_addr, dst, dst_addr, warpMatrix, border_constant_value, srcOffsetX, srcOffsetY, dstOffsetX, dstOffsetY);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    y;

        /* Fetch affine coordinates */
        __float2_t m10    = _mem8_f2_const(&warpMatrix[0]);
        __float2_t m32    = _mem8_f2_const(&warpMatrix[2]);
        __float2_t m54    = _mem8_f2_const(&warpMatrix[4]);

        /* Prepare source offset */
        __float2_t srcOffset = _dinthsp(_pack2((uint32_t)srcOffsetY, (uint32_t)srcOffsetX));

#ifdef FLOAT_RND_DOWN
        /* This code will configure the floating point instructions to
         * trunc toward neg infinity during the operations instead of rounding */

        uint32_t fmode, setMode;
        uint32_t roundModeMask  = 0x06000600U;
        uint32_t roundModeTrunc = 0x06000600U;

        fmode = _getFADCR();
        setMode = (fmode & ~(roundModeMask)) | roundModeTrunc;

        _setFADCR(setMode);
#endif

        for( y=0; y < (int32_t)dst_addr->dim_y; y++ ) {

            uint8_t *dst_t  = (uint8_t *)&dst[y * dst_addr->stride_y];

            VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_core(src, dst_t, m10, m32, m54, dst_addr->dim_x, srcOffset, (uint32_t)dstOffsetX, (uint32_t)y+(uint32_t)dstOffsetY,
                                                      src_addr->dim_x, src_addr->dim_y,
                                                      (uint32_t)src_addr->stride_y, border_constant_value);
        }
#ifdef FLOAT_RND_DOWN
        _setFADCR(fmode);
#endif

    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_checkParams(const uint8_t src[restrict],
                                                              const VXLIB_bufParams2D_t *src_addr,
                                                              uint8_t dst[restrict],
                                                              const VXLIB_bufParams2D_t *dst_addr,
                                                              const VXLIB_F32 warpMatrix[6],
                                                              uint8_t border_constant_value,
                                                              int16_t srcOffsetX,
                                                              int16_t srcOffsetY,
                                                              int16_t dstOffsetX,
                                                              int16_t dstOffsetY)
{
    VXLIB_STATUS    status;

    if((src == NULL) || (dst == NULL) || (warpMatrix == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < dst_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_ALIGNED4_WIDTHS) || defined(VXLIB_WARPAFFINEBILINEAR_BC_I8U_C32F_O8U_ALIGNED4_WIDTHS)
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
