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

#include "VXLIB_sobel_7x7_i8u_o16s_o16s_cn.h"

CODE_SECTION(VXLIB_sobel_7x7_i8u_o16s_o16s_cn,              ".text:ansi")
CODE_SECTION(VXLIB_sobel_7x7_i8u_o16s_o16s_checkParams_cn,  ".text:ansi")

static inline int16_t saturateToS16(int32_t input) {
    int16_t output;
    if(input > 32767) {
        output = 32767;
    }
    else if(input < -32768) {
        output = -32768;
    }
    else {
        output = input;
    }

    return output;
}

VXLIB_STATUS VXLIB_sobel_7x7_i8u_o16s_o16s_cn(uint8_t src[],
                                         VXLIB_bufParams2D_t *src_addr,
                                         int16_t dst_x[],
                                         VXLIB_bufParams2D_t *dst_x_addr,
                                         int16_t dst_y[],
                                         VXLIB_bufParams2D_t *dst_y_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_sobel_7x7_i8u_o16s_o16s_checkParams_cn(src, src_addr, dst_x, dst_x_addr, dst_y, dst_y_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t x, y, i, j;
        int32_t sumx, sumy;
        int32_t outWidth, outHeight;

        int8_t coef[7][7] =  {{  -1,  -4,   -5, 0,   5,  4,  1},
                               {  -6, -24,  -30, 0,  30, 24,  6},
                               { -15, -60,  -75, 0,  75, 60, 15},
                               { -20, -80, -100, 0, 100, 80, 20},
                               { -15, -60,  -75, 0,  75, 60, 15},
                               {  -6, -24,  -30, 0,  30, 24,  6},
                               {  -1,  -4,   -5, 0,   5,  4,  1}};

        outWidth = VXLIB_min(dst_x_addr->dim_x, src_addr->dim_x-6);
        outHeight = VXLIB_min(dst_x_addr->dim_y, src_addr->dim_y-6);
        for(y=0; y < outHeight; y++) {
            for(x=0; x < outWidth; x++) {
                sumx = 0;
                sumy = 0;
                for(j=0; j<7; j++) {
                    for(i=0; i<7; i++) {
                        sumx += src[(y+j)*src_addr->stride_y + (x+i)] * coef[j][i];
                        sumy += src[(y+j)*src_addr->stride_y + (x+i)] * coef[i][j];
                    }
                }
                dst_x[y*dst_x_addr->stride_y/2 + x] = saturateToS16(sumx);
                dst_y[y*dst_y_addr->stride_y/2 + x] = saturateToS16(sumy);
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_sobel_7x7_i8u_o16s_o16s_checkParams_cn(uint8_t src[],
                                           VXLIB_bufParams2D_t *src_addr,
                                           int16_t dst_x[],
                                           VXLIB_bufParams2D_t *dst_x_addr,
                                           int16_t dst_y[],
                                           VXLIB_bufParams2D_t *dst_y_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || ((dst_x == NULL) && (dst_y == NULL))) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( (src_addr->dim_x < dst_x_addr->dim_x) ||
                (src_addr->dim_x < dst_y_addr->dim_x) ||
               ((src_addr->dim_y-6) !=  dst_x_addr->dim_y) ||
               ((src_addr->dim_y-6) !=  dst_y_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_x_addr->stride_y < (dst_x_addr->dim_x*2)) ||
               (dst_y_addr->stride_y < (dst_y_addr->dim_x*2)) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_x_addr->data_type != VXLIB_INT16) ||
               (dst_y_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
