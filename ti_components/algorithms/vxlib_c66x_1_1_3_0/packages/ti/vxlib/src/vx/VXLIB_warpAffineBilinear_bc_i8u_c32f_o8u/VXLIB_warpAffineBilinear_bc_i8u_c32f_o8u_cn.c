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

#include "VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_cn.h"
#include <math.h>

/* Set float rounding mode to neg infinity when converting to integer */
#define FLOAT_RND_DOWN 1

CODE_SECTION(VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_cn(const uint8_t src[],
                                                     VXLIB_bufParams2D_t *src_addr,
                                                     uint8_t dst[],
                                                     VXLIB_bufParams2D_t *dst_addr,
                                                     const VXLIB_F32 warpMatrix[6],
                                                     uint8_t border_constant_value,
                                                     int16_t srcOffsetX,
                                                     int16_t srcOffsetY,
                                                     int16_t dstOffsetX,
                                                     int16_t dstOffsetY)
{
    uint32_t       x, y;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_checkParams_cn(src, src_addr, dst, dst_addr, warpMatrix, border_constant_value, srcOffsetX, srcOffsetY, dstOffsetX, dstOffsetY);
    if( status == VXLIB_SUCCESS )
#endif
    {
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

        for( y = 0u; y < dst_addr->dim_y; y++ ) {
            for( x = 0u; x < dst_addr->dim_x; x++ ) {

                /* Affine equation to compute input coordiantes from output coordinates */
                VXLIB_F32 src_x_f = (x+dstOffsetX) * warpMatrix[0] + (y+dstOffsetY) * warpMatrix[2] + warpMatrix[4];
                VXLIB_F32 src_y_f = (x+dstOffsetX) * warpMatrix[1] + (y+dstOffsetY) * warpMatrix[3] + warpMatrix[5];

                VXLIB_F32 xf = floorf(src_x_f);
                VXLIB_F32 yf = floorf(src_y_f);
                VXLIB_F32 dx = src_x_f - xf;
                VXLIB_F32 dy = src_y_f - yf;
                VXLIB_F32 a[4];

                int32_t src_x = (int32_t)(xf) - srcOffsetX;
                int32_t src_y = (int32_t)(yf) - srcOffsetY;

                uint8_t tl = 0;
                uint8_t tr = 0;
                uint8_t bl = 0;
                uint8_t br = 0;

                a[0] = (1.0f - dx) * (1.0f - dy);
                a[1] = (1.0f - dx) * (dy);
                a[2] = (dx)* (1.0f - dy);
                a[3] = (dx)* (dy);

                tl = (src_x < 0 || src_y < 0 || src_x > src_addr->dim_x-1 || src_y > src_addr->dim_y-1 ) ?
                     border_constant_value :
                     src[src_y*src_addr->stride_y + src_x];
                tr = (src_x+1 < 0 || src_y < 0 || src_x+1 > src_addr->dim_x-1 || src_y > src_addr->dim_y-1 ) ?
                     border_constant_value :
                     src[src_y*src_addr->stride_y + src_x + 1];
                bl = (src_x < 0 || src_y+1 < 0 || src_x > src_addr->dim_x-1 || src_y+1 > src_addr->dim_y-1 ) ?
                     border_constant_value :
                     src[(src_y+1)*src_addr->stride_y + src_x];
                br = (src_x+1 < 0 || src_y+1 < 0 || src_x+1 > src_addr->dim_x-1 || src_y+1 > src_addr->dim_y-1 ) ?
                     border_constant_value :
                     src[(src_y+1)*src_addr->stride_y + src_x + 1];

                dst[(y*dst_addr->stride_y) + x] = (uint8_t)(a[0]*tl + a[2]*tr + a[1]*bl + a[3]*br + 0.5f);
            }
        }
#ifdef FLOAT_RND_DOWN
        _setFADCR(fmode);
#endif
    }
    return (status);
}

VXLIB_STATUS VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u_checkParams_cn(const uint8_t src[],
                                                                 VXLIB_bufParams2D_t * src_addr,
                                                                 uint8_t dst[],
                                                                 VXLIB_bufParams2D_t * dst_addr,
                                                                 const VXLIB_F32 warpMatrix[6],
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

