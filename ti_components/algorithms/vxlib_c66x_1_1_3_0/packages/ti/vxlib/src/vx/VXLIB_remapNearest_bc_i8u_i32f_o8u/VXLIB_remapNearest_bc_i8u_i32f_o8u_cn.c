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

#include "VXLIB_remapNearest_bc_i8u_i32f_o8u_cn.h"
#include <math.h>

CODE_SECTION(VXLIB_remapNearest_bc_i8u_i32f_o8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_remapNearest_bc_i8u_i32f_o8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_remapNearest_bc_i8u_i32f_o8u_cn(uint8_t src[],
                               VXLIB_bufParams2D_t *src_addr,
                               uint8_t dst[],
                               VXLIB_bufParams2D_t *dst_addr,
                               VXLIB_F32 remap[],
                               VXLIB_bufParams2D_t * remap_addr,
                               uint8_t border_constant_value)
{
    uint32_t        x, y;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_remapNearest_bc_i8u_i32f_o8u_checkParams_cn(src, src_addr, dst, dst_addr, remap, remap_addr, border_constant_value);
    if( status == VXLIB_SUCCESS )
#endif
    {
        for( y=0; y < dst_addr->dim_y; y++ ) {

            uint32_t line_offset = y*remap_addr->stride_y/4;

            for( x=0; x < dst_addr->dim_x; x++ ) {

                VXLIB_F32 src_x_f = remap[line_offset + x*2];
                VXLIB_F32 src_y_f = remap[line_offset + x*2 + 1];

                VXLIB_F32 src_x_f_round = src_x_f + 0.5f;
                VXLIB_F32 src_y_f_round = src_y_f + 0.5f;

                if((src_x_f_round < 0) || 
                   (src_y_f_round < 0) || 
                   (src_x_f_round >= (VXLIB_F32)src_addr->dim_x) || 
                   (src_y_f_round >= (VXLIB_F32)src_addr->dim_y) )
                {
                    dst[y*dst_addr->stride_y + x] = border_constant_value;
                }
                else
                {
                    int32_t src_x = (int32_t)(src_x_f_round);
                    int32_t src_y = (int32_t)(src_y_f_round);

                    dst[y*dst_addr->stride_y + x] = src[src_y*src_addr->stride_y + src_x];
                }
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_remapNearest_bc_i8u_i32f_o8u_checkParams_cn(uint8_t src[],
                                          VXLIB_bufParams2D_t *src_addr,
                                          uint8_t dst[],
                                          VXLIB_bufParams2D_t *dst_addr,
                                          VXLIB_F32 remap[],
                                          VXLIB_bufParams2D_t * remap_addr,
                                          uint8_t border_constant_value)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if(remap_addr->dim_x != dst_addr->dim_x*2 ||
               remap_addr->dim_y != dst_addr->dim_y ||
               src_addr->stride_y < src_addr->dim_x ||
               dst_addr->stride_y < dst_addr->dim_x ||
               remap_addr->stride_y < remap_addr->dim_x*4 ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (remap_addr->data_type != VXLIB_FLOAT32) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

