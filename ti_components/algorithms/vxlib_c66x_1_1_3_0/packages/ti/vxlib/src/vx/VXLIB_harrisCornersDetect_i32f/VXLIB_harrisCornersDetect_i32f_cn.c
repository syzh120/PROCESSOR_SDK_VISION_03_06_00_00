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

#include "VXLIB_harrisCornersDetect_i32f_cn.h"

CODE_SECTION(VXLIB_harrisCornersDetect_i32f_cn,              ".text:ansi")
CODE_SECTION(VXLIB_harrisCornersDetect_i32f_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_harrisCornersDetect_i32f_cn(VXLIB_F32 src[],
                                     VXLIB_bufParams2D_t * src_addr,
                                     uint32_t corners[],
                                     VXLIB_F32 strengths[],
                                     uint32_t corners_capacity,
                                     uint32_t *num_corners,
                                     VXLIB_F32 strength_thresh,
                                     uint16_t startX,
                                     uint16_t startY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_harrisCornersDetect_i32f_checkParams_cn(src, src_addr, corners, strengths, corners_capacity, num_corners,
                                                           strength_thresh, startX, startY);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t x, y;
        int32_t n_corners = 0;

        for (y = 1; y < src_addr->dim_y - 1; y++)
        {
            for (x = 1; x < src_addr->dim_x - 1; x++)
            {
                if(n_corners < corners_capacity)
                {
                    // Fast non max suppression & keypoint list building
                    VXLIB_F32 center = src[y*src_addr->stride_y/4 + x];
                    VXLIB_F32 tl     = src[(y-1)*src_addr->stride_y/4 + (x - 1)];
                    VXLIB_F32 tc     = src[(y-1)*src_addr->stride_y/4 + (x)];
                    VXLIB_F32 tr     = src[(y-1)*src_addr->stride_y/4 + (x + 1)];
                    VXLIB_F32 cl     = src[y*src_addr->stride_y/4 + (x - 1)];
                    VXLIB_F32 cr     = src[y*src_addr->stride_y/4 + (x + 1)];
                    VXLIB_F32 bl     = src[(y+1)*src_addr->stride_y/4 + (x - 1)];
                    VXLIB_F32 bc     = src[(y+1)*src_addr->stride_y/4 + (x)];
                    VXLIB_F32 br     = src[(y+1)*src_addr->stride_y/4 + (x + 1)];

                    if ((center >= strength_thresh) &&
                       ((center >= tl) &&
                        (center >= tc) &&
                        (center >= tr) &&
                        (center >= cl) &&
                        (center > cr) &&
                        (center > bl) &&
                        (center > bc) &&
                        (center > br))
                        )
                    {
                        corners[n_corners] = ((y+startY) << 16) | (x+startX);
                        strengths[n_corners] = center;
                        n_corners++;
                    }
                }
            }
        }
        *num_corners = n_corners;
    }
    return (status);
}

VXLIB_STATUS VXLIB_harrisCornersDetect_i32f_checkParams_cn(VXLIB_F32 src[],
                                                 VXLIB_bufParams2D_t * src_addr,
                                                 uint32_t corners[],
                                                 VXLIB_F32 strengths[],
                                                 uint32_t corners_capacity,
                                                 uint32_t *num_corners,
                                                 VXLIB_F32 strength_thresh,
                                                 uint16_t startX,
                                                 uint16_t startY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (corners == NULL) || (strengths == NULL) || (num_corners == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((uint32_t)src_addr->stride_y < src_addr->dim_x*4) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(src_addr->data_type != VXLIB_FLOAT32) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

