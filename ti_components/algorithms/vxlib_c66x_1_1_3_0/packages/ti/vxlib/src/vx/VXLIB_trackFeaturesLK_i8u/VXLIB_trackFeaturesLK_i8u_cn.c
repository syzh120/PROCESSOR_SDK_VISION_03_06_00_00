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

#include "VXLIB_trackFeaturesLK_i8u_cn.h"
#include <math.h>

CODE_SECTION(VXLIB_trackFeaturesLK_i8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_trackFeaturesLK_i8u_checkParams_cn,  ".text:ansi")

#define  INT_ROUND(x,n)     (((x) + (1 << ((n)-1))) >> (n))

VXLIB_STATUS VXLIB_trackFeaturesLK_i8u_cn(const uint8_t old_image[],
                                           const VXLIB_bufParams2D_t *old_image_addr,
                                           const uint8_t new_image[],
                                           const VXLIB_bufParams2D_t *new_image_addr,
                                           const int16_t old_gradX[],
                                           const VXLIB_bufParams2D_t *old_gradX_addr,
                                           const int16_t old_gradY[],
                                           const VXLIB_bufParams2D_t *old_gradY_addr,
                                           __float2_t old_points[],
                                           __float2_t new_points[],
                                           uint8_t tracking_status[],
                                           uint32_t num_points,
                                           uint32_t max_iters,
                                           VXLIB_F32 epsilon,
                                           VXLIB_F32 scale,
                                           uint8_t window_size,
                                           uint8_t level,
                                           uint8_t termination,
                                           uint8_t scratch[],
                                           uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_trackFeaturesLK_i8u_checkParams_cn(old_image, old_image_addr, new_image, new_image_addr,
                                                     old_gradX, old_gradX_addr, old_gradY, old_gradY_addr,
                                                     old_points, new_points, tracking_status, num_points, max_iters,
                                                     epsilon, scale, window_size, level, termination, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t i, j, k;
        int32_t winDiv2 = window_size/2;
        int32_t width = old_image_addr->dim_x;
        int32_t height = old_image_addr->dim_y;

        int16_t *wim1 = (int16_t *)&scratch[0];
        int16_t *wim2 = (int16_t *)&scratch[2 * window_size * window_size];
        int16_t *wdx1 = (int16_t *)&scratch[4 * window_size * window_size];
        int16_t *wdy1 = (int16_t *)&scratch[6 * window_size * window_size];

        for(i = 0; i < num_points; i++)
        {
            /* Update points according to scale */
            old_points[i] = _ftof2(_hif2(old_points[i]) * scale, _lof2(old_points[i]) * scale);
            new_points[i] = _ftof2(_hif2(new_points[i]) * scale, _lof2(new_points[i]) * scale);

            /* Only operate on valid points */
            if (tracking_status[i])
            {
                int32_t outOfBounds = 0;

                /* Get points for center of window */
                VXLIB_F32 oldXf = _lof2(old_points[i]);
                VXLIB_F32 oldYf = _hif2(old_points[i]);
                int32_t oldXi = (int32_t)oldXf;
                int32_t oldYi = (int32_t)oldYf;

                /* Ignore the borders (+1 accounts for gradient borders)*/
                outOfBounds |= oldXi < (winDiv2 + 1);
                outOfBounds |= oldXi > (width - winDiv2 - 2);
                outOfBounds |= oldYi < (winDiv2 + 1);
                outOfBounds |= oldYi > (height - winDiv2 - 2);

                if( outOfBounds ) {
                    if(level == 0) {
                        tracking_status[i] = 0;
                    }
                } else {

                    VXLIB_F32 dx = oldXf - (VXLIB_F32)oldXi;
                    VXLIB_F32 dy = oldYf - (VXLIB_F32)oldYi;
                    int32_t a[4];
                    VXLIB_D64 XX = 0.0;
                    VXLIB_D64 XY = 0.0;
                    VXLIB_D64 YY = 0.0;
                    VXLIB_D64 D;
                    VXLIB_F32 minEig;
                    VXLIB_F32 prevDelta_x, prevDelta_y;

                    const int32_t W_BITS  = 14;
                    const int32_t W_BITS1 = 14;
                    const VXLIB_F32 FLT_SCALE = 1.f/(1 << 20);

                    a[0] = (int32_t)(((1.0f - dx) * (1.0f - dy) * (1 << W_BITS)) + 0.5f);
                    a[1] = (int32_t)((       (dx) * (1.0f - dy) * (1 << W_BITS)) + 0.5f);
                    a[2] = (int32_t)(((1.0f - dx) * (dy)        * (1 << W_BITS)) + 0.5f);
                    a[3] = (1 << W_BITS) - a[0] - a[1] - a[2];

                    /* Get input window for old image, and both derivatives, using bilinear interpolation */
                    for( j = 0; j < window_size; j++ ) {
                        const uint8_t   *imRow1 = old_image + (j+oldYi-winDiv2)*old_image_addr->stride_y + (oldXi-winDiv2);
                        const uint8_t   *imRow2 = imRow1 + old_image_addr->stride_y;
                        const int16_t   *gxRow1 = old_gradX + (j+oldYi-winDiv2)*(old_gradX_addr->stride_y/2) + (oldXi-winDiv2);
                        const int16_t   *gxRow2 = gxRow1 + (old_gradX_addr->stride_y/2);
                        const int16_t   *gyRow1 = old_gradY + (j+oldYi-winDiv2)*(old_gradY_addr->stride_y/2) + (oldXi-winDiv2);
                        const int16_t   *gyRow2 = gyRow1 + (old_gradY_addr->stride_y/2);

                        for( k = 0; k < window_size; k++ ) {

                            int16_t xval, yval;

                            uint8_t imtl = imRow1[k];
                            uint8_t imtr = imRow1[k + 1];
                            uint8_t imbl = imRow2[k];
                            uint8_t imbr = imRow2[k + 1];

                            int32_t interp  = INT_ROUND((a[0] * imtl) + (a[1] * imtr) +
                                                         (a[2] * imbl) + (a[3] * imbr), W_BITS1-5);

                            int16_t imval = interp;

                            int16_t grtl = gxRow1[k];
                            int16_t grtr = gxRow1[k + 1];
                            int16_t grbl = gxRow2[k];
                            int16_t grbr = gxRow2[k + 1];

                            interp = INT_ROUND((a[0] * grtl) + (a[1] * grtr) +
                                               (a[2] * grbl) + (a[3] * grbr), W_BITS1);

                            xval = interp;

                            grtl = gyRow1[k];
                            grtr = gyRow1[k + 1];
                            grbl = gyRow2[k];
                            grbr = gyRow2[k + 1];

                            interp = INT_ROUND((a[0] * grtl) + (a[1] * grtr) +
                                               (a[2] * grbl) + (a[3] * grbr), W_BITS1);

                            yval = interp;

                            wim1[j * window_size + k] = imval;
                            wdx1[j * window_size + k] = xval;
                            wdy1[j * window_size + k] = yval;

                            XX += (VXLIB_F32)(xval*xval);
                            XY += (VXLIB_F32)(xval*yval);
                            YY += (VXLIB_F32)(yval*yval);
                        }
                    }

                    XX *= FLT_SCALE;
                    XY *= FLT_SCALE;
                    YY *= FLT_SCALE;

                    D = XX*YY - XY*XY;
                    minEig = (VXLIB_F32)(YY + XX - sqrt((XX-YY)*(XX-YY) +
                                         4.0f*XY*XY))/(2*window_size*window_size);

                    if( minEig < 1.0e-04F || D < 1.0e-07F )
                    {
                        if( level == 0 )
                        {
                            tracking_status[i] = 0;
                        }
                        continue;
                    }

                    D = 1.0f/D;

                    prevDelta_x = 0.0f;
                    prevDelta_y = 0.0f;

                    j = 0;
                    while(j < max_iters || termination == VXLIB_TERM_EPSILON)
                    {

                        /* Get new points for center of window */
                        VXLIB_F32 newXf = _lof2(new_points[i]);
                        VXLIB_F32 newYf = _hif2(new_points[i]);
                        int32_t newXi = (int32_t)newXf;
                        int32_t newYi = (int32_t)newYf;
                        int32_t x, y;
                        VXLIB_D64    zx, zy;
                        VXLIB_F32 delta_x, delta_y;

                        /* Ignore the borders (+1 accounts for gradient borders)*/
                        outOfBounds |= newXi < (winDiv2 + 1);
                        outOfBounds |= newXi > (width - winDiv2 - 2);
                        outOfBounds |= newYi < (winDiv2 + 1);
                        outOfBounds |= newYi > (height - winDiv2 - 2);

                        if( outOfBounds ) {
                            if(level == 0) {
                                tracking_status[i] = 0;
                            }
                            break;
                        }

                        dx = newXf - (VXLIB_F32)newXi;
                        dy = newYf - (VXLIB_F32)newYi;

                        a[0] = (int32_t)(((1.0f - dx) * (1.0f - dy) * (1 << W_BITS)) + 0.5f);
                        a[1] = (int32_t)((       (dx) * (1.0f - dy) * (1 << W_BITS)) + 0.5f);
                        a[2] = (int32_t)(((1.0f - dx) * (dy)        * (1 << W_BITS)) + 0.5f);
                        a[3] = (1 << W_BITS) - a[0] - a[1] - a[2];

                        /* Get input window for new image, using bilinear interpolation */
                        for( y = 0; y < window_size; y++ ) {
                            const uint8_t   *imRow1 = new_image + (y+newYi-winDiv2)*new_image_addr->stride_y + (newXi-winDiv2);
                            const uint8_t   *imRow2 = imRow1 + new_image_addr->stride_y;

                            for( x = 0; x < window_size; x++ ) {

                                int16_t imval;

                                uint8_t imtl = imRow1[x];
                                uint8_t imtr = imRow1[x + 1];
                                uint8_t imbl = imRow2[x];
                                uint8_t imbr = imRow2[x + 1];

                                int32_t interp  = INT_ROUND((a[0] * imtl) + (a[1] * imtr) +
                                                             (a[2] * imbl) + (a[3] * imbr), W_BITS1-5);

                                imval = interp;

                                wim2[y * window_size + x] = imval;
                            }
                        }

                        zx = 0;
                        zy = 0;

                        for( y = 0; y < window_size; y++ ) {
                            for( x = 0; x < window_size; x++ ) {
                                int32_t    diff = wim2[y * window_size + x] - wim1[y * window_size + x];

                                zx += (VXLIB_F32)(wdx1[y * window_size + x] * diff);
                                zy += (VXLIB_F32)(wdy1[y * window_size + x] * diff);

                                //nexterr += abs(diff);
                            }
                        }

                        zx *= FLT_SCALE;
                        zy *= FLT_SCALE;

                        delta_x = (VXLIB_F32)((XY*zy - YY*zx) * D);
                        delta_y = (VXLIB_F32)((XY*zx - XX*zy) * D);

                        newXf += delta_x;
                        newYf += delta_y;

                        new_points[i] = _ftof2(newYf, newXf);

                        if( (delta_x*delta_x + delta_y*delta_y) <= epsilon &&
                            (termination == VXLIB_TERM_EPSILON || termination == VXLIB_TERM_BOTH))
                            break;

                        if( j > 0 && fabs(delta_x + prevDelta_x) < 0.01 &&
                           fabs(delta_y + prevDelta_y) < 0.01 )
                        {
                            newXf -= delta_x*0.5f;
                            newYf -= delta_y*0.5f;
                            new_points[i] = _ftof2(newYf, newXf);
                            break;
                        }
                        prevDelta_x = delta_x;
                        prevDelta_y = delta_y;
                        j++;
                    }
                }
            }
        }
    }

    return (status);
}

VXLIB_STATUS    VXLIB_trackFeaturesLK_i8u_checkParams_cn(const uint8_t old_image[],
                                                   const VXLIB_bufParams2D_t *old_image_addr,
                                                   const uint8_t new_image[],
                                                   const VXLIB_bufParams2D_t *new_image_addr,
                                                   const int16_t old_gradX[],
                                                   const VXLIB_bufParams2D_t *old_gradX_addr,
                                                   const int16_t old_gradY[],
                                                   const VXLIB_bufParams2D_t *old_gradY_addr,
                                                   const __float2_t old_points[],
                                                   const __float2_t new_points[],
                                                   const uint8_t tracking_status[],
                                                   uint32_t num_points,
                                                   uint32_t max_iters,
                                                   VXLIB_F32 epsilon,
                                                   VXLIB_F32 scale,
                                                   uint8_t window_size,
                                                   uint8_t level,
                                                   uint8_t termination,
                                                   const uint8_t scratch[],
                                                   uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((old_image == NULL) || (new_image == NULL) || (old_gradX == NULL) ||
       (old_gradY == NULL) || (old_points == NULL) || (new_points == NULL) ||
       (tracking_status == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((old_image_addr->dim_x != new_image_addr->dim_x) ||
              (old_gradX_addr->dim_x != old_gradY_addr->dim_x) ||
              (old_image_addr->dim_y != new_image_addr->dim_y) ||
              (old_gradX_addr->dim_y != old_gradY_addr->dim_y) ||
              (old_image_addr->stride_y < old_image_addr->dim_x) ||
              (new_image_addr->stride_y < new_image_addr->dim_x) ||
              (old_gradX_addr->stride_y != old_gradY_addr->stride_y) ||
              (old_gradX_addr->stride_y < old_gradX_addr->dim_x*2)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((old_image_addr->data_type != VXLIB_UINT8) ||
               (new_image_addr->data_type != VXLIB_UINT8) ||
               (old_gradX_addr->data_type != VXLIB_INT16) ||
               (old_gradY_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((termination != VXLIB_TERM_ITERATIONS) &&
             (termination != VXLIB_TERM_EPSILON) &&
             (termination != VXLIB_TERM_BOTH)) {
        status = VXLIB_ERR_INVALID_VALUE;
    } else if((int32_t)scratch_size < window_size*window_size*8) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}


