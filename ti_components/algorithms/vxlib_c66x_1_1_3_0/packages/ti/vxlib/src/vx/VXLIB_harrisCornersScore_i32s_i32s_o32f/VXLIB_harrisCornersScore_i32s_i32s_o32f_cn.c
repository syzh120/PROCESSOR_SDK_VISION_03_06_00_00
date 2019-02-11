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

#include "VXLIB_harrisCornersScore_i32s_i32s_o32f_cn.h"

CODE_SECTION(VXLIB_harrisCornersScore_i32s_i32s_o32f_cn,              ".text:ansi")
CODE_SECTION(VXLIB_harrisCornersScore_i32s_i32s_o32f_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_harrisCornersScore_i32s_i32s_o32f_cn(int32_t src_x[],
                                                     VXLIB_bufParams2D_t * src_x_addr,
                                                     int32_t src_y[],
                                                     VXLIB_bufParams2D_t * src_y_addr,
                                                     VXLIB_F32 dst[],
                                                     VXLIB_bufParams2D_t * dst_addr,
                                                     VXLIB_F32 scratch[],
                                                     VXLIB_F32 sensitivity,
                                                     uint8_t gradient_size,
                                                     uint8_t block_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_harrisCornersScore_i32s_i32s_o32f_checkParams_cn(src_x, src_x_addr, src_y, src_y_addr, dst, dst_addr,
                                                                    scratch, sensitivity, gradient_size, block_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t        x, y, i, j;

        int32_t outWidth = VXLIB_min(dst_addr->dim_x, src_x_addr->dim_x - (block_size - 1));
        int32_t outHeight = VXLIB_min(dst_addr->dim_y, src_x_addr->dim_y - (block_size - 1));

        double scale = 1.0 / ((1 << (gradient_size - 1)) * block_size * 255.0);

        for(y=0; y < outHeight; y++) {
            for(x=0; x < outWidth; x++) {

                VXLIB_D64 sum_ix2   = 0.0;
                VXLIB_D64 sum_iy2   = 0.0;
                VXLIB_D64 sum_ixy   = 0.0;
                VXLIB_D64 det_A     = 0.0;
                VXLIB_D64 trace_A   = 0.0;
                VXLIB_D64 ktrace_A2 = 0.0;
                VXLIB_D64 M_c       = 0.0;

                for (j = 0; j < block_size; j++)
                {
                    for (i = 0; i < block_size; i++)
                    {
                        VXLIB_F32 gx = (VXLIB_F32)src_x[ (y + j)*src_x_addr->stride_y/4 + (x + i)];
                        VXLIB_F32 gy = (VXLIB_F32)src_y[ (y + j)*src_y_addr->stride_y/4 + (x + i)];

                        sum_ix2 += gx * gx * scale * scale;
                        sum_iy2 += gy * gy * scale * scale;
                        sum_ixy += gx * gy * scale * scale;
                    }
                }

                det_A = (sum_ix2 * sum_iy2) - (sum_ixy * sum_ixy);
                trace_A = sum_ix2 + sum_iy2;
                ktrace_A2 = (sensitivity * (trace_A * trace_A));

                M_c = det_A - ktrace_A2;

                dst[y*(dst_addr->stride_y/4)+x] = (VXLIB_F32)M_c;
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_harrisCornersScore_i32s_i32s_o32f_checkParams_cn(int32_t src_x[],
                                                                 VXLIB_bufParams2D_t * src_x_addr,
                                                                 int32_t src_y[],
                                                                 VXLIB_bufParams2D_t * src_y_addr,
                                                                 VXLIB_F32 dst[],
                                                                 VXLIB_bufParams2D_t * dst_addr,
                                                                 VXLIB_F32 scratch[],
                                                                 VXLIB_F32 sensitivity,
                                                                 uint8_t gradient_size,
                                                                 uint8_t block_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src_x == NULL) || (src_y == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_x_addr->dim_x != src_y_addr->dim_x) ||
               (src_x_addr->dim_x < dst_addr->dim_x) ||
               (src_x_addr->dim_y != src_y_addr->dim_y) ||
               ((src_x_addr->dim_y - (block_size - 1)) != dst_addr->dim_y) ||
               ((uint32_t)src_x_addr->stride_y < src_x_addr->dim_x*4) ||
               ((uint32_t)src_y_addr->stride_y < src_y_addr->dim_x*4) ||
               ((uint32_t)dst_addr->stride_y < dst_addr->dim_x*4)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_x_addr->data_type != VXLIB_INT32) ||
               (src_y_addr->data_type != VXLIB_INT32) ||
               (dst_addr->data_type != VXLIB_FLOAT32)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

