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

#include "VXLIB_normL1_i16s_i16s_o16u.h"

CODE_SECTION(VXLIB_normL1_i16s_i16s_o16u,              ".text:optimized")
CODE_SECTION(VXLIB_normL1_i16s_i16s_o16u_core,         ".text:optimized")
CODE_SECTION(VXLIB_normL1_i16s_i16s_o16u_checkParams,  ".text:optimized")

static void VXLIB_normL1_i16s_i16s_o16u_core(const int16_t src0[restrict],
                                              const int16_t src1[restrict],
                                              uint16_t dst[restrict],
                                              int32_t width);

static void VXLIB_normL1_i16s_i16s_o16u_core(const int16_t src0[restrict],
                                              const int16_t src1[restrict],
                                              uint16_t dst[restrict],
                                              int32_t width)
{
    int32_t    x;
    int64_t src0_4, src1_4, src0_4_abs, src1_4_abs;

#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_NORML1_I16S_I16S_O16U_ALIGNED8_PTRS_STRIDES)

    if((((uint32_t)src0 % 8U) == 0U) &&
       (((uint32_t)src1 % 8U) == 0U) &&
       (((uint32_t)dst % 8U) == 0U))
#endif
    {
        /* Case 1: All pointers are aligned to 8 byte boundaries, SIMD of 8 pixels at a time*/
        /* 3/8 = 0.375 cycles per pixel */
        #pragma MUST_ITERATE(0,,2)

        for( x=0; x < ((width / 8)*2); x++ ) {
            /* Fetch 4 pixels at a time from each input */
            src0_4 = _amem8_const(&src0[x*4]);
            src1_4 = _amem8_const(&src1[x*4]);

            /* Perform absolute difference operation on them, saturating to 0x7FFF */
            src0_4_abs = _dapys2(src0_4, src0_4);
            src1_4_abs = _dapys2(src1_4, src1_4);

            /* Add the absolute difference results and store back to memory */
            _amem8(&dst[x*4]) = _dadd2(src0_4_abs, src1_4_abs);
        }
    }
#if !defined(VXLIB_ALIGNED8_PTRS_STRIDES) && !defined(VXLIB_NORML1_I16S_I16S_O16U_ALIGNED8_PTRS_STRIDES)
    else {
        /* Case 2: Not all pointers are aligned to 8 byte boundaries, SIMD of 4 pixels at a time*/
        /* 3/4 = 0.75 cycles per pixel */
        for( x=0; x < ((width / 4)); x++ ) {
            /* Fetch 4 pixels at a time from each input */
            src0_4 = _mem8_const(&src0[x*4]);
            src1_4 = _mem8_const(&src1[x*4]);

            /* Perform absolute difference operation on them, saturating to 0x7FFF */
            src0_4_abs = _dapys2(src0_4, src0_4);
            src1_4_abs = _dapys2(src1_4, src1_4);

            /* Add the absolute difference results and store back to memory */
            _mem8(&dst[x*4]) = _dadd2(src0_4_abs, src1_4_abs);
        }
    }
#endif

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_NORML1_I16S_I16S_O16U_ALIGNED8_WIDTHS)
    /* Case 3: Process remaining pixels beyond multiple of 4 or 8 */
    /* 2 cycles per pixel */
    for(x*=4; x < width; x++ ) {
        int32_t dx = (int32_t)src0[x];
        int32_t dy = (int32_t)src1[x];
        int32_t sum = VXLIB_min(_abs(dx), 0x7FFF) + VXLIB_min(_abs(dy), 0x7FFF);

        dst[x] = (uint16_t)sum;
    }
#endif
}

VXLIB_STATUS VXLIB_normL1_i16s_i16s_o16u(const int16_t src_x[restrict],
                                    const VXLIB_bufParams2D_t * src_x_addr,
                                    const int16_t src_y[restrict],
                                    const VXLIB_bufParams2D_t * src_y_addr,
                                    uint16_t dst[restrict],
                                    const VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_NORML1_I16S_I16S_O16U_CHECK_PARAMS)
    status = VXLIB_normL1_i16s_i16s_o16u_checkParams(src_x, src_x_addr, src_y, src_y_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_NORML1_I16S_I16S_O16U_EQUAL_WIDTH_STRIDE)
        if(((2U * src_x_addr->dim_x) == (uint32_t)src_x_addr->stride_y) &&
           ((2U * src_y_addr->dim_x) == (uint32_t)src_y_addr->stride_y) &&
           ((2U * dst_addr->dim_x) == (uint32_t)dst_addr->stride_y))
#endif
        {
            int32_t width = (int32_t)src_x_addr->dim_x * (int32_t)src_x_addr->dim_y;
            VXLIB_normL1_i16s_i16s_o16u_core(src_x, src_y, dst, width);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_NORML1_I16S_I16S_O16U_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < (int32_t)src_x_addr->dim_y; y++ ) {
                const int16_t   *src_x_t = (const int16_t *)&src_x[ y * (src_x_addr->stride_y / 2) ];
                const int16_t   *src_y_t = (const int16_t *)&src_y[ y * (src_y_addr->stride_y / 2) ];
                uint16_t         *dst_t  = (uint16_t *)&dst[ y * (dst_addr->stride_y / 2)];

                VXLIB_normL1_i16s_i16s_o16u_core(src_x_t, src_y_t, dst_t, (int32_t)src_x_addr->dim_x);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_NORML1_I16S_I16S_O16U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_NORML1_I16S_I16S_O16U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_normL1_i16s_i16s_o16u_checkParams(const int16_t src_x[restrict],
                                    const VXLIB_bufParams2D_t * src_x_addr,
                                    const int16_t src_y[restrict],
                                    const VXLIB_bufParams2D_t * src_y_addr,
                                    uint16_t dst[restrict],
                                    const VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status;

    if((src_x == NULL) || (src_y == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_x_addr->dim_x != src_y_addr->dim_x) ||
              (src_x_addr->dim_x != dst_addr->dim_x) ||
              (src_x_addr->dim_y != src_y_addr->dim_y) ||
              (src_x_addr->dim_y != dst_addr->dim_y) ||
              ((uint32_t)src_x_addr->stride_y < src_x_addr->dim_x) ||
              ((uint32_t)src_y_addr->stride_y < src_y_addr->dim_x) ||
              ((uint32_t)dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_x_addr->data_type != VXLIB_INT16) ||
               (src_y_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_UINT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_NORML1_I16S_I16S_O16U_EQUAL_WIDTH_STRIDE)
    else if((src_x_addr->dim_x != (uint32_t)src_x_addr->stride_y) ||
            (src_y_addr->dim_x != (uint32_t)src_y_addr->stride_y) ||
            (dst_addr->dim_x != (uint32_t)dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_PTRS_STRIDES) || defined(VXLIB_NORML1_I16S_I16S_O16U_ALIGNED8_PTRS_STRIDES)
    else if((((uint32_t)src_x % 8U) != 0) ||
            (((uint32_t)src_y % 8U) != 0) ||
            (((uint32_t)dst % 8U) != 0) ||
            (((uint32_t)src_x_addr->stride_y % 8U) != 0) ||
            (((uint32_t)src_y_addr->stride_y % 8U) != 0) ||
            (((uint32_t)dst_addr->stride_y % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_NORML1_I16S_I16S_O16U_ALIGNED8_WIDTHS)
    else if(((src_x_addr->dim_x % 8U) != 0) ||
            ((src_y_addr->dim_x % 8U) != 0) ||
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

