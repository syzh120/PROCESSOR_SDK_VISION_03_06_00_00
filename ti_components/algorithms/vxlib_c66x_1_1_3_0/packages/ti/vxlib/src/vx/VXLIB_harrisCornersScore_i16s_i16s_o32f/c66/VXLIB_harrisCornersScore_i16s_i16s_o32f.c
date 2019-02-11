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

#include "VXLIB_harrisCornersScore_i16s_i16s_o32f.h"

CODE_SECTION(VXLIB_harrisCornersScore_i16s_i16s_o32f,              ".text:optimized")
CODE_SECTION(VXLIB_harrisCornersScore_i16s_i16s_o32f_core,         ".text:optimized")
CODE_SECTION(VXLIB_harrisCornersScore_i16s_i16s_o32f_checkParams,  ".text:optimized")

static void VXLIB_harrisCornersScore_i16s_i16s_o32f_core(const int16_t srcX[restrict],
                                                        const int16_t srcY[restrict],
                                                        VXLIB_F32 dst[restrict],
                                                        VXLIB_F32 scratch[restrict],
                                                        int32_t width,
                                                        int32_t height,
                                                        VXLIB_F32 scale,
                                                        VXLIB_F32 k,
                                                        uint8_t block_size,
                                                        int32_t *pixel_index,
                                                        int32_t lnOffset,
                                                        VXLIB_F32 *xx,
                                                        VXLIB_F32 *xy,
                                                        VXLIB_F32 *yy);

static void VXLIB_harrisCornersScore_i16s_i16s_o32f_core(const int16_t srcX[restrict],
                                                        const int16_t srcY[restrict],
                                                        VXLIB_F32 dst[restrict],
                                                        VXLIB_F32 scratch[restrict],
                                                        int32_t width,
                                                        int32_t height,
                                                        VXLIB_F32 scale,
                                                        VXLIB_F32 k,
                                                        uint8_t block_size,
                                                        int32_t *pixel_index,
                                                        int32_t lnOffset,
                                                        VXLIB_F32 *xx,
                                                        VXLIB_F32 *xy,
                                                        VXLIB_F32 *yy)
{
    int32_t    i;
    VXLIB_F32    zxx = *xx;
    VXLIB_F32    zxy = *xy;
    VXLIB_F32    zyy = *yy;

    int32_t    pixind = *pixel_index;
    int32_t    colind1 = width - (int32_t)block_size;
    int32_t    colind2 = 0;

    /* Pack the scale value for SIMD multiply */
    __float2_t scale2 = _ftof2(scale, scale);

    /* ----------------------------------------------------------------
     *  MISRAC Rule 17.1 Deviation: Every line in this file that
     *  indexes into the following pointer variables violate this rule:
     *     ZXX, ZXY, ZYY, ZXXB, ZXYB, ZYYB.
     *  The only way to comply with MISRAC for this rule is to pass
     *  six different pointers as arrays on the API, one for each of
     *  these.
     *  This is intentionally not done as it adds unnecessary stack
     *  operations for each call. All of these pointers are derived
     *  from the scratch pointer. The required size of this pointer
     *  is documented in the API to ensure that accesses are within the
     *  allocated buffer.
     * ---------------------------------------------------------------- */

    /* LOCAL BUFFER POINTER ASSIGMENTS WITHIN SCRATCH BUFFER */
    /* The buffer's total size must be 4*3*(1+block_size)*width bytes */

    /* These three circular buffers are used to store the running
     * column sums across the image (sum for each column across previous
     * block_size rows); size of each is width*4 bytes */
    VXLIB_F32 *restrict    ZXX = scratch;
    VXLIB_F32 *restrict    ZXY = ZXX + width;
    VXLIB_F32 *restrict    ZYY = ZXY + width;

    /* These three circular buffers are used to store the values for each
     * column and each row (for previous block_size rows); size of each
     * is (width*block_size)*4 bytes */
    VXLIB_F32 *restrict    ZXXB = ZYY + width;
    VXLIB_F32 *restrict    ZXYB = ZXXB + (width * (int32_t)block_size);
    VXLIB_F32 *restrict    ZYYB = ZXYB + (width * (int32_t)block_size);

    /* Loop over each pixel */
    for( i = 0; i < (height * width); i++ ) {
        int32_t    ind;

        /* Normalize the gradients for the current pixel */
        __float2_t dxdy = _dmpysp(_dintsp(_itoll((uint32_t)srcY[i], (uint32_t)srcX[i])), scale2);

        /* Second moments to accumulate */
        __float2_t   x2y2 = _dmpysp(dxdy, dxdy);
        VXLIB_F32    zxy1 = _hif2(dxdy)*_lof2(dxdy);
        VXLIB_F32    zxx1 = _lof2(x2y2);
        VXLIB_F32    zyy1 = _hif2(x2y2);

        /* Add the new bottom corner to the rightmost column,
         * and subtract the previous top corner
         *
         *      A      B
         *   ***A   ***    ***    ***D
         *   ***A - ***  + ***  = ***D
         *   ***    ***    ***C   ***D
         */
        ZXX[colind2] += (zxx1 - ZXXB[pixind]);
        ZXY[colind2] += (zxy1 - ZXYB[pixind]);
        ZYY[colind2] += (zyy1 - ZYYB[pixind]);

        /* Overwrite the previous corner buffer */
        ZXXB[pixind] = zxx1;
        ZXYB[pixind] = zxy1;
        ZYYB[pixind] = zyy1;

        /* Add the new rightmost column to the square,
         * and subtract the previous leftmost column
         *
         *   ***     ***D      E***    ***F
         *   ***  +  ***D   -  E*** =  ***F
         *   ***     ***D      E***    ***F
         */
        zxx += (ZXX[colind2] - ZXX[colind1]);
        zxy += (ZXY[colind2] - ZXY[colind1]);
        zyy += (ZYY[colind2] - ZYY[colind1]);

        /* Write each result to index zero until we have completed processing the entire
         * image up until the completion of the first full block, then increment pixel by pixel */
        ind = i - ((int32_t)block_size - 1) - (lnOffset * width);
        ind = ind > 0 ? ind : 0;

        /* Compute the cornerness value */
        {
            VXLIB_F32 det_2x2 = (zxx * zyy) - (zxy * zxy);
            VXLIB_F32 trace_2 = zxx + zyy;
            VXLIB_F32 ktrace_2 = (k * (trace_2 * trace_2));

            VXLIB_F32 out = det_2x2 - ktrace_2;

            dst[ind] = out;
        }

        /* All of these are circular buffers */
        pixind =  (pixind == (((int32_t)block_size * width) - 1))  ? 0 : (int32_t)pixind  + (int32_t)1;
        colind1 = (colind1 == ((int32_t)width - (int32_t)1)) ? 0 : (int32_t)colind1 + (int32_t)1;
        colind2 = (colind2 == ((int32_t)width - (int32_t)1)) ? 0 : (int32_t)colind2 + (int32_t)1;
    }
    *pixel_index = pixind;
    *xx = zxx;
    *xy = zxy;
    *yy = zyy;
}

VXLIB_STATUS VXLIB_harrisCornersScore_i16s_i16s_o32f(const int16_t src_x[restrict],
                                                 const VXLIB_bufParams2D_t * src_x_addr,
                                                 const int16_t src_y[restrict],
                                                 const VXLIB_bufParams2D_t * src_y_addr,
                                                 VXLIB_F32 dst[restrict],
                                                 const VXLIB_bufParams2D_t * dst_addr,
                                                 VXLIB_F32 scratch[restrict],
                                                 VXLIB_F32 sensitivity,
                                                 uint8_t gradient_size,
                                                 uint8_t block_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_CHECK_PARAMS)
    status = VXLIB_harrisCornersScore_i16s_i16s_o32f_checkParams(src_x, src_x_addr, src_y, src_y_addr, dst, dst_addr, scratch, sensitivity, gradient_size, block_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t i;
        uint32_t denom = ((uint32_t)1 << ((uint32_t)gradient_size - (uint32_t)1)) * (uint32_t)block_size * (uint32_t)255;
        VXLIB_F32 scale = 1.0f / (VXLIB_F32)denom;
        int32_t pixIdx = 0;
        VXLIB_F32 xx = 0.0;
        VXLIB_F32 xy = 0.0;
        VXLIB_F32 yy = 0.0;

        /* Clear scratch buffer */
        #pragma MUST_ITERATE(12,,6);
        for( i = 0; i < (uint32_t)((block_size+1U) * src_x_addr->dim_x * 3U); i++ ) {
            scratch[i] = 0.0f;
        }

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_EQUAL_WIDTH_STRIDE)
        if(((2U * src_x_addr->dim_x) == (uint32_t)src_x_addr->stride_y) &&
           ((2U * src_y_addr->dim_x) == (uint32_t)src_y_addr->stride_y) &&
           ((4U * dst_addr->dim_x) == (uint32_t)dst_addr->stride_y) &&
            (dst_addr->dim_x == src_x_addr->dim_x))
#endif
        {
            VXLIB_harrisCornersScore_i16s_i16s_o32f_core(src_x, src_y, dst, scratch, src_x_addr->dim_x, src_x_addr->dim_y,
                                                      scale, sensitivity, block_size, &pixIdx, (int32_t)block_size - 1,
                                                      &xx, &xy, &yy);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;
            uint16_t inHeight = VXLIB_min(dst_addr->dim_y + ((int16_t)block_size-1), src_x_addr->dim_y);
            uint16_t inWidth  = VXLIB_min(dst_addr->dim_x + ((int16_t)block_size-1), src_x_addr->dim_x);

            for( y=0; y < (int32_t)inHeight; y++ ) {
                VXLIB_F32 *dst_t;
                const int16_t   *src_x_t = (const int16_t *)&src_x[ y * (src_x_addr->stride_y / 2) ];
                const int16_t   *src_y_t = (const int16_t *)&src_y[ y * (src_y_addr->stride_y / 2) ];
                int32_t lnOffset = y - ((int32_t)block_size - 1);
                lnOffset = (lnOffset < 0) ? 0 : lnOffset;
                dst_t  = (VXLIB_F32 *)&dst[ lnOffset * (dst_addr->stride_y / 4)];

                VXLIB_harrisCornersScore_i16s_i16s_o32f_core(src_x_t, src_y_t, dst_t, scratch, (int32_t)inWidth, 1,
                                                          scale, sensitivity, block_size, &pixIdx, 0, &xx, &xy, &yy);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_CHECK_PARAMS))

VXLIB_STATUS VXLIB_harrisCornersScore_i16s_i16s_o32f_checkParams(const int16_t src_x[restrict],
                                                             const VXLIB_bufParams2D_t * src_x_addr,
                                                             const int16_t src_y[restrict],
                                                             const VXLIB_bufParams2D_t * src_y_addr,
                                                             VXLIB_F32 dst[restrict],
                                                             const VXLIB_bufParams2D_t * dst_addr,
                                                             VXLIB_F32 scratch[restrict],
                                                             VXLIB_F32 sensitivity,
                                                             uint8_t gradient_size,
                                                             uint8_t block_size)
{
    VXLIB_STATUS    status;

    if((src_x == NULL) || (src_y == NULL) || (dst == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_x_addr->dim_x != src_y_addr->dim_x) ||
               (src_x_addr->dim_x < dst_addr->dim_x) ||
               (src_x_addr->dim_y != src_y_addr->dim_y) ||
               ((src_x_addr->dim_y - ((int16_t)block_size - 1)) != dst_addr->dim_y) ||
               ((uint32_t)src_x_addr->stride_y < (src_x_addr->dim_x*2U)) ||
               ((uint32_t)src_y_addr->stride_y < (src_y_addr->dim_x*2U)) ||
               ((uint32_t)dst_addr->stride_y < (dst_addr->dim_x*4U))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_x_addr->data_type != VXLIB_INT16) ||
               (src_y_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_FLOAT32)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_HARRISCORNERSSCORE_I16S_I16S_O32F_EQUAL_WIDTH_STRIDE)
    else if(((2U * src_x_addr->dim_x) != (uint32_t)src_x_addr->stride_y) ||
             ((2U * src_y_addr->dim_x) != (uint32_t)src_y_addr->stride_y) ||
             ((4U * dst_addr->dim_x) != (uint32_t)dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

