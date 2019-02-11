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

#include "VXLIB_histogramCdfLut_i32u_o8u.h"

/* for 16-bit support (U16 or S16), the code can be duplicated with NUM_BINS = 65536 and PIXEL = vx_uint16. */
#define NUM_BINS 256

CODE_SECTION(VXLIB_histogramCdfLut_i32u_o8u,                      ".text:optimized")
CODE_SECTION(VXLIB_histogramCdfLut_i32u_o8u_checkParams,          ".text:optimized")

VXLIB_STATUS VXLIB_histogramCdfLut_i32u_o8u(const uint32_t src[restrict],
                                    uint32_t cdf[restrict],
                                    uint8_t dst[restrict],
                                    uint32_t numPixels,
                                    uint32_t minValue)
{
    VXLIB_STATUS      status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_HISTOGRAMCDFLUT_I32U_O8U_CHECK_PARAMS)
    status = VXLIB_histogramCdfLut_i32u_o8u_checkParams(src, cdf, dst, numPixels, minValue);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    x;
        uint32_t   sum = 0;

        _nassert(((uint32_t)src % 8U) == 0);
        _nassert(((uint32_t)dst % 8U) == 0);
        _nassert(((uint32_t)cdf % 8U) == 0);

        /* calculate the cumulative distribution (summed histogram) */
        if(cdf != NULL) {
            /* 2/2 cycles per pixel */
            for( x = 0; x < NUM_BINS; x++ ) {
                sum += src[x];
                cdf[x] = sum;
            }
        }

        /* recompute the histogram to be a LUT for replacing pixel values */
        /* Reference original structure and do cdf at same time as lut since it
         * does not cost any more cycles */
        if(dst != NULL) {

            uint32_t cdfMin = src[minValue];
            uint32_t div_den = numPixels - cdfMin;
            VXLIB_F32 div_inverse = 255.0f / (VXLIB_F32)div_den;
            uint32_t cdfx;
            VXLIB_F32 p;
            int32_t temp;

            if( div_den > 0 ) {
                sum = 0;
                /* 1/1 cycles per pixel */
                for( x = 0; x < (int32_t)minValue; x++ ) {
                    dst[x] = 0;
                }
                if( (x % 2) == 1 ) {
                    sum += src[x];
                    cdfx = sum - cdfMin;
                    p = (VXLIB_F32)cdfx * div_inverse;
                    temp = _spint(p);
                    dst[x] = (uint8_t)temp;
                    x++;
                }
                /* 2/2 cycles per pixel */
                for( ; x < NUM_BINS; x+=2 ) {
                    int64_t in2 = _amem8_const(&src[x]);
                    sum += _loll(in2);
                    cdfx = sum - cdfMin;
                    p = (VXLIB_F32)cdfx * div_inverse;
                    temp = _spint(p);
                    dst[x] = (uint8_t)temp;
                    sum += _hill(in2);
                    cdfx = sum - cdfMin;
                    p = (VXLIB_F32)cdfx * div_inverse;
                    temp = _spint(p);
                    dst[x+1] = (uint8_t)temp;
                }
            } else {
                /* 2/4 cycles per pixel */
                for( x = 0; x < NUM_BINS; x++ ) {
                    dst[x] = (uint8_t)x;
                }
            }
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_HISTOGRAMCDFLUT_I32U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_HISTOGRAMCDFLUT_I32U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_histogramCdfLut_i32u_o8u_checkParams(const uint32_t src[restrict],
                                                const uint32_t cdf[restrict],
                                                const uint8_t dst[restrict],
                                                uint32_t numPixels,
                                                uint32_t minValue)
{
    VXLIB_STATUS    status;

    if(src == NULL) {
        status = VXLIB_ERR_NULL_POINTER;
    } 
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

