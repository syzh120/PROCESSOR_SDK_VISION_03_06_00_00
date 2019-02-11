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

#include "VXLIB_harrisCornersDetect_i32f.h"

CODE_SECTION(VXLIB_harrisCornersDetect_i32f,              ".text:optimized")
CODE_SECTION(VXLIB_harrisCornersDetect_i32f_core,         ".text:optimized")
CODE_SECTION(VXLIB_harrisCornersDetect_i32f_checkParams,  ".text:optimized")

static inline void VXLIB_harrisCornersDetect_i32f_core(const VXLIB_F32 src[restrict],
                                               uint32_t corners[restrict],
                                               VXLIB_F32 strengths[restrict],
                                               int32_t width,
                                               int32_t height,
                                               int32_t stride,
                                               int16_t xStart,
                                               int16_t yStart,
                                               uint32_t corners_capacity,
                                               VXLIB_F32 strength_thresh,
                                               uint32_t *num_corners);

static inline void VXLIB_harrisCornersDetect_i32f_core(const VXLIB_F32 src[restrict],
                                               uint32_t corners[restrict],
                                               VXLIB_F32 strengths[restrict],
                                               int32_t width,
                                               int32_t height,
                                               int32_t stride,
                                               int16_t xStart,
                                               int16_t yStart,
                                               uint32_t corners_capacity,
                                               VXLIB_F32 strength_thresh,
                                               uint32_t *num_corners)
{
    int32_t    i, j, k, x, y;
    uint32_t    n_featuresFound = 0;

    /* Store threshold in 2 adjacent registers for comparison during loop */
    __float2_t threshhold = _ftof2(strength_thresh, strength_thresh);

    /* Case 1: SIMD of 2 pixels at a time */
    /* 11/2 = 5.5 cycles per pixel */
    for( j = 0; j < (height-2); j++ ) {
        for( i = 0; i < ((width-2)-1); i+=2 ) {

            /* In order to process 2 pixels (x's below), we need to fetch 3 rows of 4 pixels */
            /*    0   1   2   3
             *    0   x   x   3
             *    0   1   2   3
             */
            __float2_t row0_10 = _mem8_f2_const(&src[ ((j+0)*(stride/4)) + (i+0) ]);
            __float2_t row0_32 = _mem8_f2_const(&src[ ((j+0)*(stride/4)) + (i+2) ]);
            __float2_t row1_10 = _mem8_f2_const(&src[ ((j+1)*(stride/4)) + (i+0) ]);
            __float2_t row1_32 = _mem8_f2_const(&src[ ((j+1)*(stride/4)) + (i+2) ]);
            __float2_t row2_10 = _mem8_f2_const(&src[ ((j+2)*(stride/4)) + (i+0) ]);
            __float2_t row2_32 = _mem8_f2_const(&src[ ((j+2)*(stride/4)) + (i+2) ]);

            __float2_t row0_21 = _ftof2(_lof2(row0_32), _hif2(row0_10));
            __float2_t row1_21 = _ftof2(_lof2(row1_32), _hif2(row1_10));
            __float2_t row2_21 = _ftof2(_lof2(row2_32), _hif2(row2_10));

            /* The DSP can not do SIMD comparisons on F32, however, it can do SIMD2
             * subtractions.  We can subtract the center pixel against each of the
             * neighborhood pixels and the threshold.  Since we only care about the
             * sign bit, we can perform ANDs and ORs on the results of the subtraction to
             * get our final value, and finally check the sign bit of the resuts to
             * see if it is a local maximum.
             */

            /* Compare the center pixel with the threshold */
            uint64_t thresh2 = (uint64_t)_f2toll(_dsubsp(row1_21, threshhold));

            /* Compare the center pixel with the top row, and pixel to the left (center >= neighbor) */
            uint64_t tl2 = (uint64_t)_f2toll(_dsubsp(row1_21, row0_10));
            uint64_t tc2 = (uint64_t)_f2toll(_dsubsp(row1_21, row0_21));
            uint64_t tr2 = (uint64_t)_f2toll(_dsubsp(row1_21, row0_32));
            uint64_t cl2 = (uint64_t)_f2toll(_dsubsp(row1_21, row1_10));
            uint64_t ors2 = thresh2 | tl2 | tc2 | tr2 | cl2;

            /* Compare the center pixel with the bottom row, and pixel to the right (center > neighbor) */
            uint64_t cr2 = (uint64_t)_f2toll(_dsubsp(row1_32, row1_21));
            uint64_t bl2 = (uint64_t)_f2toll(_dsubsp(row2_10, row1_21));
            uint64_t bc2 = (uint64_t)_f2toll(_dsubsp(row2_21, row1_21));
            uint64_t br2 = (uint64_t)_f2toll(_dsubsp(row2_32, row1_21));
            uint64_t ands2 = cr2 & bl2 & bc2 & br2;

            /* Combine the results of the >= operations and the > operations */
            uint64_t comb2 = ors2 | ~ands2;

            uint64_t center2 = (uint64_t)_f2toll(row1_21);

            /* Check each pixel, and conditionally add it to the list if it is
             * a local maximum and above the threshold */
            for( k = 0; k<2; k++) {
                if( (_loll((int64_t)comb2) & 0x80000000U) == 0) {
                    if( n_featuresFound < corners_capacity ) {
                        x = i+k+(int32_t)xStart;
                        y = j+(int32_t)yStart;
                        _amem4(&corners[n_featuresFound]) = ((uint32_t)y << 16) | (uint32_t)x;
                        _amem4(&strengths[n_featuresFound]) = _loll((int64_t)center2);
                        n_featuresFound++;
                    }
                }
                center2 >>= 32;
                comb2 >>= 32;
            }
        }

        /* Case 2: Process remaining pixels beyond multiple of 2 */
        /* 7 cycles per pixel */
        for( ; i < (width-2); i++ ) {

            /* Only fetch the 3x3 neighborhood around the pixel */
            __float2_t row0_10a = _mem8_f2_const(&src[ ((j+0)*(stride/4)) + (i+0) ]);
            __float2_t row1_10a = _mem8_f2_const(&src[ ((j+1)*(stride/4)) + (i+0) ]);
            __float2_t row2_10a = _mem8_f2_const(&src[ ((j+2)*(stride/4)) + (i+0) ]);
            VXLIB_F32  row0_2  = src[ ((j+0)*(stride/4)) + (i+2) ];
            VXLIB_F32  row1_2  = src[ ((j+1)*(stride/4)) + (i+2) ];
            VXLIB_F32  row2_2  = src[ ((j+2)*(stride/4)) + (i+2) ];

            /* Compare the center pixel with the threshold */
            uint32_t thresh = _ftoi(_hif2(row1_10a) - strength_thresh);

            /* Compare the center pixel with the top row, and pixel to the left (center >= neighbor) */
            uint32_t tl = _ftoi(_hif2(row1_10a) - _lof2(row0_10a));
            uint32_t tc = _ftoi(_hif2(row1_10a) - _hif2(row0_10a));
            uint32_t tr = _ftoi(_hif2(row1_10a) - row0_2);
            uint32_t cl = _ftoi(_hif2(row1_10a) - _lof2(row1_10a));
            uint32_t ors = thresh | tl | tc | tr | cl;

            /* Compare the center pixel with the bottom row, and pixel to the right (center > neighbor) */
            uint32_t cr = _ftoi(row1_2 - _hif2(row1_10a));
            uint32_t bl = _ftoi(_lof2(row2_10a) - _hif2(row1_10a));
            uint32_t bc = _ftoi(_hif2(row2_10a) - _hif2(row1_10a));
            uint32_t br = _ftoi(row2_2 - _hif2(row1_10a));
            uint32_t ands = cr & bl & bc & br;

            /* Combine the results of the >= operations and the > operations */
            uint32_t comb = ors | ~ands;

            /* Conditionally add it to the list if it is a local maximum
             * and above the threshold */
            if( (comb & 0x80000000U) == 0) {
                if( n_featuresFound < corners_capacity ) {
                    x = i+xStart;
                    y = j+yStart;
                    _amem4(&corners[n_featuresFound]) = ((uint32_t)y << 16) | (uint32_t)x;
                    _amem4(&strengths[n_featuresFound]) = _hill(_f2toll(row1_10a));
                    n_featuresFound++;
                }
            }
        }
    }

    *num_corners = n_featuresFound;
}

VXLIB_STATUS VXLIB_harrisCornersDetect_i32f(const VXLIB_F32 src[restrict],
                                  const VXLIB_bufParams2D_t * src_addr,
                                  uint32_t corners[restrict],
                                  VXLIB_F32 strengths[restrict],
                                  uint32_t corners_capacity,
                                  uint32_t *num_corners,
                                  VXLIB_F32 strength_thresh,
                                  uint16_t startX,
                                  uint16_t startY)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_HARRISCORNERSDETECT_I32F_CHECK_PARAMS)
    status = VXLIB_harrisCornersDetect_i32f_checkParams(src, src_addr, corners, strengths, corners_capacity, num_corners, strength_thresh, startX, startY);
    if( status == VXLIB_SUCCESS )
#endif
    {
        VXLIB_harrisCornersDetect_i32f_core(src, corners, strengths, src_addr->dim_x, src_addr->dim_y, src_addr->stride_y,
                                  (int16_t)startX+1, (int16_t)startY+1, corners_capacity, strength_thresh, num_corners);
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_HARRISCORNERSDETECT_I32F_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_HARRISCORNERSDETECT_I32F_CHECK_PARAMS))

VXLIB_STATUS VXLIB_harrisCornersDetect_i32f_checkParams(const VXLIB_F32 src[],
                                              const VXLIB_bufParams2D_t * src_addr,
                                              const uint32_t corners[],
                                              const VXLIB_F32 strengths[],
                                              uint32_t corners_capacity,
                                              const uint32_t *num_corners,
                                              VXLIB_F32 strength_thresh,
                                              uint16_t startX,
                                              uint16_t startY)
{
    VXLIB_STATUS    status;

    if((src == NULL) || (corners == NULL) || (strengths == NULL) || (num_corners == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((uint32_t)src_addr->stride_y < (src_addr->dim_x*4U)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(src_addr->data_type != VXLIB_FLOAT32) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

