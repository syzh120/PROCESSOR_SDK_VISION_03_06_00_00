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
/*
 * Copyright (c) 2012-2016 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
 * KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
 * SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
 *    https://www.khronos.org/registry/
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 */

#include "VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_cn.h"

CODE_SECTION(VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_checkParams_cn,  ".text:ansi")

static uint8_t usat8(int32_t a);

static void yuv2rgb(uint8_t y, uint8_t cb, uint8_t cr,
                          uint8_t *r, uint8_t *g, uint8_t *b,
                          VXLIB_D64 fr_fv, VXLIB_D64 fg_fu, VXLIB_D64 fg_fv, VXLIB_D64 fb_fu);

static uint8_t usat8(int32_t a)
{
    if (a > 255)
        a = 255;
    if (a < 0)
        a = 0;
    return (uint8_t)a;
}
// 128, 0, 250
static void yuv2rgb(uint8_t y, uint8_t cb, uint8_t cr,
                          uint8_t *r, uint8_t *g, uint8_t *b,
                          VXLIB_D64 fr_fv, VXLIB_D64 fg_fu, VXLIB_D64 fg_fv, VXLIB_D64 fb_fu)
{
    /*
    R'= Y' + 0.0000*U + 1.5748*V
    G'= Y' - 0.1873*U - 0.4681*V
    B'= Y' + 1.8556*U + 0.0000*V
    */
    VXLIB_D64 f_y = (VXLIB_D64)y;
    VXLIB_D64 f_u = (VXLIB_D64)cb - 128; // -128
    VXLIB_D64 f_v = (VXLIB_D64)cr - 128; // 122
    VXLIB_D64 f_r = f_y + fr_fv*f_v; // 128 + 1.403*122
    VXLIB_D64 f_g = f_y - fg_fu*f_u - fg_fv*f_v; //128 - 0.344*(-128) - 0.714*122
    VXLIB_D64 f_b = f_y + fb_fu*f_u; // 128 + 1.773*(-128)
    int32_t i_r = (int32_t)f_r;
    int32_t i_g = (int32_t)f_g;
    int32_t i_b = (int32_t)f_b;
    *r = usat8(i_r);
    *g = usat8(i_g);
    *b = usat8(i_b);
}

VXLIB_STATUS VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_cn(uint8_t src0[],
                                  VXLIB_bufParams2D_t *src_addr,
                                  uint8_t dst[],
                                  VXLIB_bufParams2D_t *dst_addr,
                                  uint8_t x_value,
                                  uint8_t src_space)
{
    uint32_t         x, y, src0Index, dstIndex;
    VXLIB_STATUS     status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_checkParams_cn(src0, src_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        for( y=0; y < dst_addr->dim_y; y++ ) {

            for( x=0; x < dst_addr->dim_x; x+=2 ) {

                src0Index = y * src_addr->stride_y + x * 2;
                dstIndex  = y * dst_addr->stride_y + x * 4;

                dst[dstIndex+3] = dst[dstIndex+7] = 255;

                if (src_space == VXLIB_COLOR_SPACE_BT601_525 ||
                        src_space == VXLIB_COLOR_SPACE_BT601_625)
                {
                    yuv2rgb(src0[src0Index+x_value],src0[src0Index+1-x_value],src0[src0Index+3-x_value],
                                  &dst[dstIndex],&dst[dstIndex+1],&dst[dstIndex+2],
                                  1.403f, 0.344f, 0.714f, 1.773f);

                    yuv2rgb(src0[src0Index+2+x_value],src0[src0Index+1-x_value],src0[src0Index+3-x_value],
                                  &dst[dstIndex+4],&dst[dstIndex+5],&dst[dstIndex+6],
                                  1.403f, 0.344f, 0.714f, 1.773f);
                }
                else
                {

                    yuv2rgb(src0[src0Index+x_value],src0[src0Index+1-x_value],src0[src0Index+3-x_value],
                                  &dst[dstIndex],&dst[dstIndex+1],&dst[dstIndex+2],
                                  1.5748f, 0.1873f, 0.4681f, 1.8556f);

                   yuv2rgb(src0[src0Index+2+x_value],src0[src0Index+1-x_value],src0[src0Index+3-x_value],
                                  &dst[dstIndex+4],&dst[dstIndex+5],&dst[dstIndex+6],
                                  1.5748f, 0.1873f, 0.4681f, 1.8556f);
                }
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_checkParams_cn(uint8_t src0[],
                                              VXLIB_bufParams2D_t *src_addr,
                                              uint8_t dst[],
                                              VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src0 == NULL) || (dst == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->dim_x != dst_addr->dim_x ||
               src_addr->dim_y != dst_addr->dim_y ||
               src_addr->stride_y < (2*src_addr->dim_x) ||
               dst_addr->stride_y < (4*dst_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
              (dst_addr->data_type != VXLIB_UINT32) ) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

