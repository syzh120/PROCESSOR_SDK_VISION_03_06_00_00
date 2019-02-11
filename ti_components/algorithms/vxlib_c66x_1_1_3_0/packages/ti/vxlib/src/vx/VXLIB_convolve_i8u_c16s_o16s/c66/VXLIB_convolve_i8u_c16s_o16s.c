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

#include "VXLIB_convolve_i8u_c16s_o16s.h"
#include "../../VXLIB_convolve_3x3_i8u_c16s_o16s/c66/VXLIB_convolve_3x3_i8u_c16s_o16s.h"
#include "../../VXLIB_convolve_5x5_i8u_c16s_o16s/c66/VXLIB_convolve_5x5_i8u_c16s_o16s.h"
#include "../../VXLIB_convolve_7x7_i8u_c16s_o16s/c66/VXLIB_convolve_7x7_i8u_c16s_o16s.h"

CODE_SECTION(VXLIB_convolve_i8u_c16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_convolve_i8u_c16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_convolve_i8u_c16s_o16s_checkParams,  ".text:optimized")

static void VXLIB_convolve_i8u_c16s_o16s_core(const uint8_t src[restrict],
                                    int16_t dst[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth,
                                    const int16_t conv_mat[restrict],
                                    int32_t conv_width,
                                    int32_t conv_height,
                                    uint32_t msb);

static void VXLIB_convolve_i8u_c16s_o16s_core(const uint8_t src[restrict],
                                    int16_t dst[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth,
                                    const int16_t conv_mat[restrict],
                                    int32_t conv_width,
                                    int32_t conv_height,
                                    uint32_t msb)
{
    int32_t x;

    /* Case 1: Catch all case for un-optimized fixed conv sizes */
    for(x=0; x < outWidth; x++) {
        int32_t sum = 0;
        int32_t j, k;
        int32_t result; 
        #pragma MUST_ITERATE(3, 9, );
        for(j=0; j < conv_height; j++) {
            #pragma MUST_ITERATE(3, 9, );
            for(k=0; k < conv_width; k++) {
                sum += ((int32_t)src[(j*srcStride) + (x+k)] * conv_mat[(conv_width*conv_height) - 1 - (j*conv_width) - k]);
            }
        }

        /* Downshift of a negative number rounds to negative infinity instead of toward 0 */
        if((sum < 0) && (msb > 0)) {
            uint32_t temp = (uint32_t)1<<msb;
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
        result = (int32_t)(sum>>msb);
        result = (result < INT16_MIN) ? INT16_MIN : result;
        result = (result > INT16_MAX) ? INT16_MAX : result;

        dst[x] = (int16_t)result;
    }
}

VXLIB_STATUS VXLIB_convolve_i8u_c16s_o16s(const uint8_t src[restrict],
                                const VXLIB_bufParams2D_t *src_addr,
                                int16_t dst[restrict],
                                const VXLIB_bufParams2D_t *dst_addr,
                                const int16_t conv_mat[restrict],
                                int32_t conv_width,
                                int32_t conv_height,
                                uint32_t conv_scale)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CONVOLVE_I8U_C16S_O16S_CHECK_PARAMS)
    status = VXLIB_convolve_i8u_c16s_o16s_checkParams(src, src_addr, dst, dst_addr, conv_mat, conv_width, conv_height, conv_scale);
    if( status == VXLIB_SUCCESS )
#endif
    {

        uint32_t msb = 31U - _lmbd(1U, conv_scale);
        
        if((conv_width == conv_height) && (conv_width == 3)) {

            status = VXLIB_convolve_3x3_i8u_c16s_o16s(src, src_addr, dst, dst_addr, conv_mat, msb);

        } else if((conv_width == conv_height) && (conv_width == 5)) {

            status = VXLIB_convolve_5x5_i8u_c16s_o16s(src, src_addr, dst, dst_addr, conv_mat, msb);

        } else if((conv_width == conv_height) && (conv_width == 7)) {

            status = VXLIB_convolve_7x7_i8u_c16s_o16s(src, src_addr, dst, dst_addr, conv_mat, msb);

        } else {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_I8U_C16S_O16S_EQUAL_WIDTH_STRIDE)
            if((src_addr->dim_x == src_addr->stride_y) &&
               ((dst_addr->dim_x*2) == dst_addr->stride_y) &&
               (dst_addr->dim_x == src_addr->dim_x))
#endif
            {
                VXLIB_convolve_i8u_c16s_o16s_core(src, dst, src_addr->stride_y, ((dst_addr->stride_y/2) * dst_addr->dim_y) - (conv_width-1),
                                       conv_mat, conv_width, conv_height, msb);
            }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CONVOLVE_I8U_C16S_O16S_EQUAL_WIDTH_STRIDE)
            else {

                int32_t    y;
                int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-(conv_width-1)));

                for( y=0; y < dst_addr->dim_y; y++ ) {

                    const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                    int16_t         *dst_t  = (int16_t *)&dst[ y * (dst_addr->stride_y/2)];

                    VXLIB_convolve_i8u_c16s_o16s_core(src_t, dst_t, src_addr->stride_y, width,
                                           conv_mat, conv_width, conv_height, msb);

                }
            }
#endif
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CONVOLVE_I8U_C16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CONVOLVE_I8U_C16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_convolve_i8u_c16s_o16s_checkParams(const uint8_t src[restrict],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const int16_t dst[restrict],
                                           const VXLIB_bufParams2D_t *dst_addr,
                                           const int16_t conv_mat[restrict],
                                           int32_t conv_width,
                                           int32_t conv_height,
                                           uint32_t conv_scale)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    uint32_t msb = 31U - _lmbd(1U, conv_scale);

    if((src == NULL) || (dst == NULL) || (conv_mat == NULL))  {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x < dst_addr->dim_x) ||
               ((src_addr->dim_y-(conv_height-1)) !=  dst_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < (dst_addr->dim_x*2)) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((conv_width < 3) ||
               (conv_width > 9) ||
               (conv_height < 3) ||
               (conv_height > 9) ||
               (conv_scale < 1U) ||
               ((conv_scale & ~((uint32_t)1 << msb)) != 0 )) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
