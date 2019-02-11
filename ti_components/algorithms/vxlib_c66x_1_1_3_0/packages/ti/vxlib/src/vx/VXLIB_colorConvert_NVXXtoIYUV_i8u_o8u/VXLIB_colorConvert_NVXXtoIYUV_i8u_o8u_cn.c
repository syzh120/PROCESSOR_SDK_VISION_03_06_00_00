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

#include "VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_cn.h"

CODE_SECTION(VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_cn(uint8_t src0[],
                                  VXLIB_bufParams2D_t *src0_addr,
                                  uint8_t src1[],
                                  VXLIB_bufParams2D_t *src1_addr,
                                  uint8_t dst0[],
                                  VXLIB_bufParams2D_t *dst0_addr,
                                  uint8_t dst1[],
                                  VXLIB_bufParams2D_t *dst1_addr,
                                  uint8_t dst2[],
                                  VXLIB_bufParams2D_t *dst2_addr,
                                  uint8_t u_pix)
{
    uint32_t         x, y, src0Index, src1Index, dst0Index, dst1Index, dst2Index;
    uint8_t          v_pix = 1 - u_pix;
    VXLIB_STATUS     status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_checkParams_cn(src0, src0_addr, src1, src1_addr, dst0, dst0_addr, dst1, dst1_addr, dst2, dst2_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        for( y=0; y < dst0_addr->dim_y; y++ ) {

            for( x=0; x < dst0_addr->dim_x; x++ ) {
                src0Index = y * src0_addr->stride_y + x;
                src1Index = (y/2) * src1_addr->stride_y + 2*(x/2);
                dst0Index = y * dst0_addr->stride_y + x;
                dst1Index = (y/2) * dst1_addr->stride_y + (x/2);
                dst2Index = (y/2) * dst2_addr->stride_y + (x/2);

                dst0[dst0Index] = src0[src0Index];
                dst1[dst1Index] = src1[src1Index + u_pix];
                dst2[dst2Index] = src1[src1Index + v_pix];
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_checkParams_cn(uint8_t src0[],
                                              VXLIB_bufParams2D_t *src0_addr,
                                              uint8_t src1[],
                                              VXLIB_bufParams2D_t *src1_addr,
                                              uint8_t dst0[],
                                              VXLIB_bufParams2D_t *dst0_addr,
                                              uint8_t dst1[],
                                              VXLIB_bufParams2D_t *dst1_addr,
                                              uint8_t dst2[],
                                              VXLIB_bufParams2D_t *dst2_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src0 == NULL) || (src1 == NULL) || (dst0 == NULL) || (dst1 == NULL) || (dst2 == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src0_addr->dim_x != dst0_addr->dim_x ||
               src0_addr->dim_y != dst0_addr->dim_y ||
               src0_addr->stride_y < (src0_addr->dim_x) ||
               dst0_addr->stride_y < (dst0_addr->dim_x) ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
              (dst0_addr->data_type != VXLIB_UINT8) ) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}
