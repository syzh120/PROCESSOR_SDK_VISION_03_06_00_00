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

#include "VXLIB_integralImage_i8u_o32u.h"

CODE_SECTION(VXLIB_integralImage_i8u_o32u,              ".text:optimized")
CODE_SECTION(VXLIB_integralImage_i8u_o32u_core,         ".text:optimized")
CODE_SECTION(VXLIB_integralImage_i8u_o32u_checkParams,  ".text:optimized")

static inline void VXLIB_integralImage_i8u_o32u_core(const uint8_t src[restrict],
                                               const uint32_t dstPrev[restrict],
                                               uint32_t dst[restrict],
                                               uint32_t width,
                                               uint32_t *rowSumSeed);

static inline void VXLIB_integralImage_i8u_o32u_core(const uint8_t src[restrict],
                                               const uint32_t dstPrev[restrict],
                                               uint32_t dst[restrict],
                                               uint32_t width,
                                               uint32_t *rowSumSeed)
{
    uint32_t z, R, R1, Ra, Rb, R1a, R1b;
    int64_t     uu, vv, ww, xx, yy;
    int64_t         v2, w2, x2, y2;
    int64_t     uu2a, uu2b, uu4loa, uu4lob, uu4hia, uu4hib;

    R = 0;

#if !defined(VXLIB_NO_TILE_SUPPORT) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_NO_TILE_SUPPORT)
    if(rowSumSeed != NULL) {
        R = *rowSumSeed;
    }
#endif

    R1b = R;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src % 8U) == 0) &&
       (((uint32_t)dstPrev % 8U) == 0) &&
       (((uint32_t)dst % 8U) == 0))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 5/8 = 0.625 cycles per pixel */
        for( z = 0; z < (width / 8U); z++ ) {

            /* read 8 inputs */
            uu = _amem8_const(&src[ z*8U ]);

            /* read 8 previous outputs */
            vv = _amem8_const(&dstPrev[ (z*8U) + 0 ]);
            ww = _amem8_const(&dstPrev[ (z*8U) + 2U ]);
            xx = _amem8_const(&dstPrev[ (z*8U) + 4U ]);
            yy = _amem8_const(&dstPrev[ (z*8U) + 6U ]);

            /* Initialize R from previous iteration */
            R  = R1b;

            /* Initialize R1 from previous iteration and sum the lower 4 pixels
             * to remove loop-carried dependency and upper pixels can be computed
             * in parallel */
            R1 = R1b + _dotpu4(0x01010101U, _loll(uu));

            /* Convert 8 packed bytes into 8 32bit registers */
            uu2a   = _mpyu4ll(_loll(uu), 0x01010101U);
            uu2b   = _mpyu4ll(_hill(uu), 0x01010101U);
            uu4loa = _mpy2ll((int32_t)_loll(uu2a), 0x00010001);
            uu4lob = _mpy2ll((int32_t)_hill(uu2a), 0x00010001);
            uu4hia = _mpy2ll((int32_t)_loll(uu2b), 0x00010001);
            uu4hib = _mpy2ll((int32_t)_hill(uu2b), 0x00010001);

            /* Compute interval pixels for lower 4 pixels */
            Ra = R  + _loll(uu4loa);
            Rb = Ra + _hill(uu4loa);
            v2 = _itoll(_hill(vv) + Rb, _loll(vv) + Ra);

            Ra = Rb + _loll(uu4lob);
            Rb = Ra + _hill(uu4lob);
            w2 = _itoll(_hill(ww) + Rb, _loll(ww) + Ra);

            /* Compute interval pixels for upper 4 pixels */
            R1a = R1  + _loll(uu4hia);
            R1b = R1a + _hill(uu4hia);
            x2 = _itoll(_hill(xx) + R1b, _loll(xx) + R1a);

            R1a = R1b + _loll(uu4hib);
            R1b = R1a + _hill(uu4hib);
            y2 = _itoll(_hill(yy) + R1b, _loll(yy) + R1a);

            /* Write out results */
            _amem8(&dst[ (z*8U) + 0 ]) = v2;
            _amem8(&dst[ (z*8U) + 2U]) = w2;
            _amem8(&dst[ (z*8U) + 4U]) = x2;
            _amem8(&dst[ (z*8U) + 6U]) = y2;
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 9/8 = 1.125 cycles per pixel */
        for( z = 0; z < (width / 8U); z++ ) {

            /* read 8 inputs */
            uu = _mem8_const(&src[ z*8U ]);

            /* read 8 previous outputs */
            vv = _mem8_const(&dstPrev[ (z*8U) + 0 ]);
            ww = _mem8_const(&dstPrev[ (z*8U) + 2U ]);
            xx = _mem8_const(&dstPrev[ (z*8U) + 4U ]);
            yy = _mem8_const(&dstPrev[ (z*8U) + 6U ]);

            /* Initialize R from previous iteration */
            R  = R1b;

            /* Initialize R1 from previous iteration and sum the lower 4 pixels
             * to remove loop-carried dependency and upper pixels can be computed
             * in parallel */
            R1 = R1b + _dotpu4(0x01010101U, _loll(uu));

            /* Convert 8 packed bytes into 8 32bit registers */
            uu2a   = _mpyu4ll(_loll(uu), 0x01010101U);
            uu2b   = _mpyu4ll(_hill(uu), 0x01010101U);
            uu4loa = _mpy2ll((int32_t)_loll(uu2a), 0x00010001);
            uu4lob = _mpy2ll((int32_t)_hill(uu2a), 0x00010001);
            uu4hia = _mpy2ll((int32_t)_loll(uu2b), 0x00010001);
            uu4hib = _mpy2ll((int32_t)_hill(uu2b), 0x00010001);

            /* Compute interval pixels for lower 4 pixels */
            Ra = R  + _loll(uu4loa);
            Rb = Ra + _hill(uu4loa);
            v2 = _itoll(_hill(vv) + Rb, _loll(vv) + Ra);

            Ra = Rb + _loll(uu4lob);
            Rb = Ra + _hill(uu4lob);
            w2 = _itoll(_hill(ww) + Rb, _loll(ww) + Ra);

            /* Compute interval pixels for upper 4 pixels */
            R1a = R1  + _loll(uu4hia);
            R1b = R1a + _hill(uu4hia);
            x2 = _itoll(_hill(xx) + R1b, _loll(xx) + R1a);

            R1a = R1b + _loll(uu4hib);
            R1b = R1a + _hill(uu4hib);
            y2 = _itoll(_hill(yy) + R1b, _loll(yy) + R1a);

            /* Write out results */
            _mem8(&dst[ (z*8U) + 0 ]) = v2;
            _mem8(&dst[ (z*8U) + 2U]) = w2;
            _mem8(&dst[ (z*8U) + 4U]) = x2;
            _mem8(&dst[ (z*8U) + 6U]) = y2;
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_ALIGNED8_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 8 */
    /* 2 cycles per pixel */
    for( z*=8U; z < width; z++ ) {
        R1b += src[z];
        dst[z] = dstPrev[z] + R1b;
    }
#endif

#if !defined(VXLIB_NO_TILE_SUPPORT) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_NO_TILE_SUPPORT)
    if(rowSumSeed != NULL) {
        *rowSumSeed = R1b;
    }
#endif

}


VXLIB_STATUS VXLIB_integralImage_i8u_o32u(const uint8_t src[restrict],
                                  const VXLIB_bufParams2D_t *src_addr,
                                  uint32_t dst[restrict],
                                  const VXLIB_bufParams2D_t *dst_addr,
                                  uint32_t prevRow[restrict],
                                  uint32_t prevCol[restrict],
                                  uint32_t prevRowUpdate)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_INTEGRALIMAGE_I8U_O32U_CHECK_PARAMS)
    status = VXLIB_integralImage_i8u_o32u_checkParams(src, src_addr, dst, dst_addr, prevRow, prevCol, prevRowUpdate);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t    y;
        uint32_t *R = NULL;

        /* calculate interval image one line at a time */
        for( y=0; y < src_addr->dim_y; y++ ) {

            int32_t dst_offset = dst_addr->stride_y / 4;
            uint32_t *prev = &dst[ (y-1) * dst_offset ];

            if(y == 0) {
                prev = prevRow;
            }

#if !defined(VXLIB_NO_TILE_SUPPORT) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_NO_TILE_SUPPORT)
            if(prevCol != NULL) {
                R = &prevCol[y];
            }
#endif

            VXLIB_integralImage_i8u_o32u_core(&src[ y * src_addr->stride_y],
                                      prev,
                                      &dst[ y * dst_offset ],
                                      src_addr->dim_x,
                                      R);

        }

#if !defined(VXLIB_NO_TILE_SUPPORT) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_NO_TILE_SUPPORT)
        /* Update the last row from output */
        if(prevRowUpdate != 0) {
            /* 1 cycles per pixel */
            for( y=0; y < src_addr->dim_x; y++ ) {
                prevRow[y] = dst[((src_addr->dim_y-1) * (dst_addr->stride_y / 4)) + y];
            }
        }
#endif

    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_INTEGRALIMAGE_I8U_O32U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_INTEGRALIMAGE_I8U_O32U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_integralImage_i8u_o32u_checkParams(const uint8_t src[],
                                              const VXLIB_bufParams2D_t *src_addr,
                                              const uint32_t dst[],
                                              const VXLIB_bufParams2D_t *dst_addr,
                                              const uint32_t prevRow[],
                                              const uint32_t prevCol[],
                                              uint32_t prevRowUpdate
)
{
    VXLIB_STATUS    status;

    if((src == NULL) || (dst == NULL) || (prevRow == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x != dst_addr->dim_x) ||
              (src_addr->dim_y != dst_addr->dim_y) ||
              (src_addr->stride_y < src_addr->dim_x) ||
              (dst_addr->stride_y < (4 * dst_addr->dim_x))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT32)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(prevRowUpdate > 1U) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_INTEGRALIMAGE_I8U_O32U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
            ((4 * dst_addr->dim_x) != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_INTEGRALIMAGE_I8U_O32U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            ((src_addr->stride_y % 8U) != 0) ||
            ((dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_INTEGRALIMAGE_I8U_O32U_ALIGNED8_WIDTHS)
    else if(((src_addr->dim_x % 8U) != 0) ||
            ((dst_addr->dim_x % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

