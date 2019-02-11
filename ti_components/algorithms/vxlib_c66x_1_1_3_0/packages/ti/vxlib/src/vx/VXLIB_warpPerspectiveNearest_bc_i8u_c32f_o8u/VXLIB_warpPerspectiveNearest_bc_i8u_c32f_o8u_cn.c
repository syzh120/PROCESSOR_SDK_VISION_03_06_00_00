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

#include "VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_cn.h"

CODE_SECTION(VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_cn(const uint8_t src[],
                                                     VXLIB_bufParams2D_t *src_addr,
                                                     uint8_t dst[],
                                                     VXLIB_bufParams2D_t *dst_addr,
                                                     const VXLIB_F32 warpMatrix[9],
                                                     uint8_t border_constant_value,
                                                     int16_t srcOffsetX,
                                                     int16_t srcOffsetY,
                                                     int16_t dstOffsetX,
                                                     int16_t dstOffsetY)
{
    uint32_t       x, y;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_checkParams_cn(src, src_addr, dst, dst_addr, warpMatrix, border_constant_value, srcOffsetX, srcOffsetY, dstOffsetX, dstOffsetY);
    if( status == VXLIB_SUCCESS )
#endif
    {
        for( y = 0u; y < dst_addr->dim_y; y++ ) {
            for( x = 0u; x < dst_addr->dim_x; x++ ) {

                VXLIB_F32           xf, yf, zf;
                bool            out_of_bounds;
                uint8_t output;
                int32_t    bx, by;

                /* Perspective equation to compute input coordiantes from output coordinates */
                zf =  (x+dstOffsetX) * warpMatrix[2] + (y+dstOffsetY) * warpMatrix[5] + warpMatrix[8];
                xf = ((x+dstOffsetX) * warpMatrix[0] + (y+dstOffsetY) * warpMatrix[3] + warpMatrix[6]) * _rcpsp(zf);
                yf = ((x+dstOffsetX) * warpMatrix[1] + (y+dstOffsetY) * warpMatrix[4] + warpMatrix[7]) * _rcpsp(zf);

                /* nearest neighbor x/y ( USE intrinsic rounding conversion here to be bit exact with opt version) */
                bx = _spint(xf) - srcOffsetX;
                by = _spint(yf) - srcOffsetY;

                out_of_bounds = (bx < 0 || by < 0 || bx > (src_addr->dim_x-1) || by > (src_addr->dim_y-1) );

                output = (out_of_bounds) ? border_constant_value : (uint8_t)src[(by * src_addr->stride_y) + bx];

                dst[(y * dst_addr->stride_y) + x] = output;
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u_checkParams_cn(const uint8_t src[],
                                                                 VXLIB_bufParams2D_t * src_addr,
                                                                 uint8_t dst[],
                                                                 VXLIB_bufParams2D_t * dst_addr,
                                                                 const VXLIB_F32 warpMatrix[9],
                                                                 uint8_t border_constant_value,
                                                                 int16_t srcOffsetX,
                                                                 int16_t srcOffsetY,
                                                                 int16_t dstOffsetX,
                                                                 int16_t dstOffsetY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL) || (warpMatrix == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if(src_addr->stride_y < src_addr->dim_x ||
               dst_addr->stride_y < dst_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

