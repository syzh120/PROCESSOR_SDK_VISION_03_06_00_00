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

#include "VXLIB_meanStdDev_i8u_o32f.h"
#include <float.h>

CODE_SECTION(VXLIB_meanStdDev_i8u_o32f,              ".text:optimized")
CODE_SECTION(VXLIB_meanStdDev_i8u_o32f_checkParams,  ".text:optimized")

static VXLIB_D64 sqrtdp (VXLIB_D64 a);

static void VXLIB_meanStdDev_i8u_o32f_core(const uint8_t src[],
                                    int32_t width,
                                    VXLIB_F32 *sum,
                                    VXLIB_F32 *sqsum);

static VXLIB_D64 sqrtdp (VXLIB_D64 a)
{
    VXLIB_D64    half  =  0.5;
    VXLIB_D64    OneP5 =  1.5;
    VXLIB_D64    x, y;
    int32_t     i;

    x = _rsqrdp(a);

    #pragma UNROLL(1)

    for( i = 0; i < 3; i++ ) {
        x = x * (OneP5 - (a * x * x * half));
    }

    y = a * x;

    if( a <= 0.0 ) {
        y = 0.0;
    }
    if( a > DBL_MAX ) {
        y = DBL_MAX;
    }

    return (y);
}

static void VXLIB_meanStdDev_i8u_o32f_core(const uint8_t src[],
                                    int32_t width,
                                    VXLIB_F32 *sum,
                                    VXLIB_F32 *sqsum)
{
    int32_t    x;
    uint32_t   sum_i, sqsum_i;
    VXLIB_F32   sum_f=0.f, sqsum_f=0.f;

    /* Case 1: SIMD of 16 pixels at a time*/
    /* 4/16 = 0.25 cycles per pixel */
    #pragma UNROLL(2)
    for( x = 0; x < ((width / 16) * 16); x+=8 ) {
        int64_t in8 = _mem8_const(&src[x]);
        sum_i = _dotpu4(_loll(in8), 0x01010101U) +
                _dotpu4(_hill(in8), 0x01010101U);
        sum_f += (VXLIB_F32)sum_i;

        sqsum_i = _dotpu4(_loll(in8), _loll(in8)) +
                  _dotpu4(_hill(in8), _hill(in8));
        sqsum_f += (VXLIB_F32)sqsum_i;
    }

    sum_i = 0;
    sqsum_i = 0;

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_MEANSTDDEV_I8U_O32F_ALIGNED8_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 16 */
    /* 1 cycle per pixel */
    for(; x < width; x++ ) {
        sum_i += src[x];
        sqsum_i += ((uint32_t)src[x] * (uint32_t)src[x]);
    }
#endif
    *sum += (sum_f + (VXLIB_F32)sum_i);
    *sqsum += (sqsum_f + (VXLIB_F32)sqsum_i);
}

VXLIB_STATUS VXLIB_meanStdDev_i8u_o32f(const uint8_t src[restrict],
                               const VXLIB_bufParams2D_t *src_addr,
                               VXLIB_F32 *fmean,
                               VXLIB_F32 *fstddev,
                               uint32_t *pixelsProcessed,
                               VXLIB_F32 *fcurrentSum,
                               VXLIB_F32 *fcurrentSqSum)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    uint32_t  lpixelsProcessed = *pixelsProcessed;
    VXLIB_F32 lcurrentSum = *fcurrentSum;
    VXLIB_F32 lcurrentSqSum = *fcurrentSqSum;
    *fmean = *fstddev = 0.0f;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_MEANSTDDEV_I8U_O32F_CHECK_PARAMS)
    status = VXLIB_meanStdDev_i8u_o32f_checkParams(src, src_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        VXLIB_F32 presqrt;

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MEANSTDDEV_I8U_O32F_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y))
#endif
        {
            VXLIB_meanStdDev_i8u_o32f_core(src, src_addr->dim_y * src_addr->dim_x, &lcurrentSum, &lcurrentSqSum);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_MEANSTDDEV_I8U_O32F_EQUAL_WIDTH_STRIDE)
        else {
            int32_t         y;

            for( y=0; y < src_addr->dim_y; y++ ) {
                VXLIB_meanStdDev_i8u_o32f_core(&src[y * src_addr->stride_y], src_addr->dim_x, &lcurrentSum, &lcurrentSqSum);
            }
        }
#endif
        lpixelsProcessed += (src_addr->dim_x * src_addr->dim_y);
        *fmean = lcurrentSum / (VXLIB_F32)lpixelsProcessed;
        presqrt = (lcurrentSqSum - ((lcurrentSum * lcurrentSum) / (VXLIB_F32)lpixelsProcessed)) / (VXLIB_F32)lpixelsProcessed;
        *fstddev = (VXLIB_F32)sqrtdp((VXLIB_D64)presqrt);
        *pixelsProcessed = lpixelsProcessed;
        *fcurrentSum = lcurrentSum;
        *fcurrentSqSum = lcurrentSqSum;
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_MEANSTDDEV_I8U_O32F_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_MEANSTDDEV_I8U_O32F_CHECK_PARAMS))

VXLIB_STATUS VXLIB_meanStdDev_i8u_o32f_checkParams(const uint8_t src[],
                                           const VXLIB_bufParams2D_t *src_addr)
{
    VXLIB_STATUS    status;

    if( src == NULL ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if( src_addr->data_type != VXLIB_UINT8 ) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_MEANSTDDEV_I8U_O32F_EQUAL_WIDTH_STRIDE)
    else if( src_addr->dim_x != src_addr->stride_y ) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_MEANSTDDEV_I8U_O32F_ALIGNED8_WIDTHS)
    else if((src_addr->dim_x % 8U) != 0 ) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

