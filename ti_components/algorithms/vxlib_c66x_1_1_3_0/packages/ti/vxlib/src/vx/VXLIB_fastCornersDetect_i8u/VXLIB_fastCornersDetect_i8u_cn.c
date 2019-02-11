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

#include "VXLIB_fastCornersDetect_i8u_cn.h"

CODE_SECTION(VXLIB_fastCornersDetect_i8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_fastCornersDetect_i8u_checkParams_cn,  ".text:ansi")

#define PERMUTATIONS 16
#define APERTURE 3

static uint8_t indexes[PERMUTATIONS][9] =
{
    {  0,  1,  2,  3,  4,  5,  6,  7,  8 },
    { 15,  0,  1,  2,  3,  4,  5,  6,  7 },
    { 14, 15,  0,  1,  2,  3,  4,  5,  6 },
    { 13, 14, 15,  0,  1,  2,  3,  4,  5 },
    { 12, 13, 14, 15,  0,  1,  2,  3,  4 },
    { 11, 12, 13, 14, 15,  0,  1,  2,  3 },
    { 10, 11, 12, 13, 14, 15,  0,  1,  2 },
    {  9, 10, 11, 12, 13, 14, 15,  0,  1 },
    {  8,  9, 10, 11, 12, 13, 14, 15,  0 },
    {  7,  8,  9, 10, 11, 12, 13, 14, 15 },
    {  6,  7,  8,  9, 10, 11, 12, 13, 14 },
    {  5,  6,  7,  8,  9, 10, 11, 12, 13 },
    {  4,  5,  6,  7,  8,  9, 10, 11, 12 },
    {  3,  4,  5,  6,  7,  8,  9, 10, 11 },
    {  2,  3,  4,  5,  6,  7,  8,  9, 10 },
    {  1,  2,  3,  4,  5,  6,  7,  8,  9 },
};

/* offsets from "p" */
static int32_t    offsets[16][2] =
{
    {  0, -3 },
    {  1, -3 },
    {  2, -2 },
    {  3, -1 },
    {  3,  0 },
    {  3,  1 },
    {  2,  2 },
    {  1,  3 },
    {  0,  3 },
    { -1,  3 },
    { -2,  2 },
    { -3,  1 },
    { -3,  0 },
    { -3, -1 },
    { -2, -2 },
    { -1, -3 },
};


static bool VXLIB_IsFastCorner(const uint8_t *buf, uint8_t p, uint8_t tolerance)
{
    int32_t    i, a, j, v;

    for( a = 0; a < PERMUTATIONS; a++ ) {
        bool    isacorner = true;

        for( i = 0; i < (sizeof(indexes[a]) / sizeof(indexes[a][0])); i++ ) {
            j = indexes[a][i];
            v = buf[j];
            if( v <= (p + tolerance)) {
                isacorner = false;
            }
        }

        if( isacorner == true ) {
            return (isacorner);
        }
        isacorner = true;

        for( i = 0; i < (sizeof(indexes[a]) / sizeof(indexes[a][0])); i++ ) {
            j = indexes[a][i];
            v = buf[j];
            if( v >= (p - tolerance)) {
                isacorner = false;
            }
        }

        if( isacorner == true ) {
            return (isacorner);
        }
    }

    return (false);
}

static uint8_t VXLIB_GetFastCornerStrength(int32_t x, int32_t y, uint8_t src[],
                                           VXLIB_bufParams2D_t *src_addr,
                                           uint8_t tolerance)
{
    if( x < APERTURE || y < APERTURE || x >= src_addr->dim_x - APERTURE || y >= src_addr->dim_y - APERTURE ) {
        return (0);
    }
    {
        uint32_t    srcIndex0 = (y * src_addr->stride_y) + x;
        uint32_t    srcIndex1;
        uint8_t     buf[16], c;
        int32_t     j;
        uint8_t     a, b = 255;

        for( j = 0; j < 16; j++ ) {
            srcIndex1 = ((y + offsets[j][1]) * src_addr->stride_y) + (x + offsets[j][0]);
            buf[j] = src[srcIndex1];
        }

        if( !VXLIB_IsFastCorner(buf, src[srcIndex0], tolerance)) {
            return (0);
        }
        a = tolerance;

        while( b - a > 1 ) {
            c = (a + b) / 2;
            if( VXLIB_IsFastCorner(buf, src[srcIndex0], c)) {
                a = c;
            } else {
                b = c;
            }
        }

        return (a);
    }
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_cn(uint8_t src[],
                                   VXLIB_bufParams2D_t *src_addr,
                                   uint16_t corners[],
                                   uint32_t corners_capacity,
                                   uint8_t strength_thresh,
                                   uint32_t *num_corners)
{
    uint32_t        x, y;
    uint8_t         strength;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_fastCornersDetect_i8u_checkParams_cn(src, src_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        *num_corners = 0;
        for( y = APERTURE; y < (int32_t)(src_addr->dim_y - APERTURE); y++ ) {
            for( x = APERTURE; x < (int32_t)(src_addr->dim_x - APERTURE); x++ ) {
                strength = VXLIB_GetFastCornerStrength(x, y, src, src_addr, strength_thresh);
                if( strength > 0 ) {
                    if( 0 ) {
                        if( strength >= VXLIB_GetFastCornerStrength(x - 1, y - 1, src, src_addr, strength_thresh) &&
                            strength >= VXLIB_GetFastCornerStrength(x, y - 1, src, src_addr, strength_thresh) &&
                            strength >= VXLIB_GetFastCornerStrength(x + 1, y - 1, src, src_addr, strength_thresh) &&
                            strength >= VXLIB_GetFastCornerStrength(x - 1, y, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x + 1, y, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x - 1, y + 1, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x, y + 1, src, src_addr, strength_thresh) &&
                            strength > VXLIB_GetFastCornerStrength(x + 1, y + 1, src, src_addr, strength_thresh)) {
                            ;
                        } else {
                            continue;
                        }
                    }
                    if( *num_corners < corners_capacity ) {
                        corners[*num_corners*2+0] = x;
                        corners[*num_corners*2+1] = y;
                        //corners[*num_corners*3+2] = strength;
                    }
                    ++(*num_corners);
                }
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_checkParams_cn(uint8_t src[],
                                               VXLIB_bufParams2D_t *src_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(src_addr->data_type != VXLIB_UINT8) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

