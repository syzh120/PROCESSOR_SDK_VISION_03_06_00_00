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

#include "VXLIB_remapNearest_bc_i8u_i32f_o8u.h"

CODE_SECTION(VXLIB_remapNearest_bc_i8u_i32f_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_remapNearest_bc_i8u_i32f_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_remapNearest_bc_i8u_i32f_o8u_checkParams,  ".text:optimized")

static void VXLIB_remapNearest_bc_i8u_i32f_o8u_core(const uint8_t src[restrict],
                               uint8_t dst[restrict],
                               const VXLIB_F32 remap[restrict],
                               int32_t width,
                               uint32_t src_width,
                               uint32_t src_height,
                               uint32_t src_stride,
                               uint8_t border_constant_value);

static void VXLIB_remapNearest_bc_i8u_i32f_o8u_core(const uint8_t src[restrict],
                                uint8_t dst[restrict],
                                const VXLIB_F32 remap[restrict],
                                int32_t width,
                                uint32_t src_width,
                                uint32_t src_height,
                                uint32_t src_stride,
                                uint8_t border_constant_value)
{
    int32_t    x;
    __float2_t remap_0f, remap_1f, remap_2f, remap_3f;
    int32_t remap_0, remap_1, remap_2, remap_3;
    uint32_t out0, out1, out2, out3;
    uint32_t out01, out23;
    uint32_t out_of_bounds_0, out_of_bounds_1, out_of_bounds_2, out_of_bounds_3;
    int32_t maxCmp = (int32_t)_pack2(src_height-1U, src_width-1U);
    uint32_t offsetCalc = (src_stride << 16) + 1U;

    /* Case 1: SIMD of 4 pixels at a time */
    /* 9/4 = 2.25 cycles per pixel */
    for( x=0; x < (width / 4); x++ ) {

        /* Fetch coordinates */
        remap_0f = _mem8_f2_const(&remap[x*8]);
        remap_1f = _mem8_f2_const(&remap[(x*8)+2]);
        remap_2f = _mem8_f2_const(&remap[(x*8)+4]);
        remap_3f = _mem8_f2_const(&remap[(x*8)+6]);

        /* Round coordinates to nearest neighbor */
        remap_0 = (int32_t)_dspinth(remap_0f);
        remap_1 = (int32_t)_dspinth(remap_1f);
        remap_2 = (int32_t)_dspinth(remap_2f);
        remap_3 = (int32_t)_dspinth(remap_3f);

        /* Check for out of bounds condition */
        out_of_bounds_0 = (uint32_t)_cmpgt2(0, remap_0) | (uint32_t)_cmpgt2(remap_0, maxCmp);
        out_of_bounds_1 = (uint32_t)_cmpgt2(0, remap_1) | (uint32_t)_cmpgt2(remap_1, maxCmp);
        out_of_bounds_2 = (uint32_t)_cmpgt2(0, remap_2) | (uint32_t)_cmpgt2(remap_2, maxCmp);
        out_of_bounds_3 = (uint32_t)_cmpgt2(0, remap_3) | (uint32_t)_cmpgt2(remap_3, maxCmp);

        /* Fetch pixels from src buffer */
        out0 = (out_of_bounds_0 != 0U) ? border_constant_value : src[_dotp2(remap_0, (int32_t)offsetCalc)];
        out1 = (out_of_bounds_1 != 0U) ? border_constant_value : src[_dotp2(remap_1, (int32_t)offsetCalc)];
        out2 = (out_of_bounds_2 != 0U) ? border_constant_value : src[_dotp2(remap_2, (int32_t)offsetCalc)];
        out3 = (out_of_bounds_3 != 0U) ? border_constant_value : src[_dotp2(remap_3, (int32_t)offsetCalc)];

        /* Pack output pixels together before writing */
        out01 = (out1 << 16) | out0;
        out23 = (out3 << 16) | out2;
        _mem4(&dst[x*4]) = _spacku4((int32_t)out23, (int32_t)out01);
    }

#if !defined(VXLIB_ALIGNED4_WIDTHS) && !defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_ALIGNED4_WIDTHS)

    /* Case 2: Process remaining pixels beyond multiple of 4 */
    /* 3 cycles per pixel */
    for(x*=4; x < width; x++ ) {
        /* Fetch coordinates */
        __float2_t remap_f = _mem8_f2_const(&remap[x*2]);

        /* Round coordinates to nearest neighbor */
        remap_0 = (int32_t)_dspinth(remap_f);

        /* Check for out of bounds condition */
        out_of_bounds_0 = (uint32_t)_cmpgt2(0, remap_0) | (uint32_t)_cmpgt2(remap_0, maxCmp);

        /* Fetch pixel from src buffer */
        dst[x] = (out_of_bounds_0 != 0U) ? border_constant_value : src[_dotp2(remap_0, (int32_t)offsetCalc)];
    }

#endif

}

VXLIB_STATUS VXLIB_remapNearest_bc_i8u_i32f_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            const VXLIB_F32 remap[restrict],
                            const VXLIB_bufParams2D_t * remap_addr,
                            uint8_t border_constant_value)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_CHECK_PARAMS)
    status = VXLIB_remapNearest_bc_i8u_i32f_o8u_checkParams(src, src_addr, dst, dst_addr, remap, remap_addr, border_constant_value);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_EQUAL_WIDTH_STRIDE)
        if((remap_addr->dim_x == ((uint32_t)remap_addr->stride_y/4U)) &&
           (dst_addr->dim_x == (uint32_t)dst_addr->stride_y) &&
           (dst_addr->dim_x == (remap_addr->dim_x/2U)))
#endif
        {
            uint32_t newWidth = dst_addr->dim_x * dst_addr->dim_y;

            VXLIB_remapNearest_bc_i8u_i32f_o8u_core(src, dst, remap, (int32_t)newWidth,
                              src_addr->dim_x, src_addr->dim_y, (uint32_t)src_addr->stride_y, border_constant_value);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < (int32_t)dst_addr->dim_y; y++ ) {

                const VXLIB_F32  *remap_t = (const VXLIB_F32 *)&remap[y * (remap_addr->stride_y/4)];
                uint8_t           *dst_t  = (uint8_t *)&dst[y * dst_addr->stride_y];

                VXLIB_remapNearest_bc_i8u_i32f_o8u_core(src, dst_t, remap_t, (int32_t)dst_addr->dim_x,
                                  src_addr->dim_x, src_addr->dim_y, (uint32_t)src_addr->stride_y, border_constant_value);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_remapNearest_bc_i8u_i32f_o8u_checkParams(const uint8_t src[restrict],
                                        const VXLIB_bufParams2D_t *src_addr,
                                        uint8_t dst[restrict],
                                        const VXLIB_bufParams2D_t *dst_addr,
                                        const VXLIB_F32 remap[restrict],
                                        const VXLIB_bufParams2D_t * remap_addr,
                                        uint8_t border_constant_value)
{
    VXLIB_STATUS    status;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((remap_addr->dim_x != (dst_addr->dim_x*2U)) ||
              (remap_addr->dim_y != dst_addr->dim_y) ||
              ((uint32_t)src_addr->stride_y < src_addr->dim_x) ||
              ((uint32_t)dst_addr->stride_y < dst_addr->dim_x) ||
              ((uint32_t)remap_addr->stride_y < (remap_addr->dim_x*4U))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (remap_addr->data_type != VXLIB_FLOAT32) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_EQUAL_WIDTH_STRIDE)
    else if(((remap_addr->dim_x*4U) != (uint32_t)remap_addr->stride_y) ||
            (dst_addr->dim_x != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED4_WIDTHS) || defined(VXLIB_REMAPNEAREST_BC_I8U_I32F_O8U_ALIGNED4_WIDTHS)
    else if(((remap_addr->dim_x % 8U) != 0) ||
            ((dst_addr->dim_x % 4U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

