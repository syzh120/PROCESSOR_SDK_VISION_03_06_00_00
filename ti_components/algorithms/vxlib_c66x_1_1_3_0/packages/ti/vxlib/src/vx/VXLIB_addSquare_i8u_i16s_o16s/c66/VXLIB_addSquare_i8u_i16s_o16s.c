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

#include "VXLIB_addSquare_i8u_i16s_o16s.h"

CODE_SECTION(VXLIB_addSquare_i8u_i16s_o16s,              ".text:optimized")
CODE_SECTION(VXLIB_addSquare_i8u_i16s_o16s_core,         ".text:optimized")
CODE_SECTION(VXLIB_addSquare_i8u_i16s_o16s_checkParams,  ".text:optimized")

static void VXLIB_addSquare_i8u_i16s_o16s_core(const uint8_t src0[restrict],
                               const int16_t src1[restrict],
                               int16_t dst[restrict],
                               int32_t width,
                               uint32_t shift);

static void VXLIB_addSquare_i8u_i16s_o16s_core(const uint8_t src0[restrict],
                               const int16_t src1[restrict],
                               int16_t dst[restrict],
                               int32_t width,
                               uint32_t shift)
{
    /* MISRA.BITS.NOT_UNSIGNED
     * MISRAC_2004 Rule_12.7
     * MISRAC_WAIVER:
     * The C6x DSP compiler treats all types as unsigned when it comes
     * to the following bitwise operations (&, |, ~, ^).  In this case,
     * the compiler document requires the 64bit bitwise operations to
     * use the type "int64_t".  This waiver is for all instances of
     * bitwise operations (&, |) in this function.
     */

    int32_t    x;
    __x128_t square8;
    int64_t lo4, hi4, src1lo4, src1hi4;
    int64_t msklo4, mskhi4;
    int64_t maxS16 = 0x7fff7fff7fff7fff;
    int64_t zeros = 0;

    /* Case 1: SIMD of 8 pixels at a time (in this case, aligned and non-aligned
     *         performance is the same, so just have one version for non-aligned) */
    /* 5/8 = 0.625 cycles per pixel */
    for( x=0; x < ((width / 8) * 8); x+=8 ) {

        /* Square and shift input, and assign to register pairs */
        square8 = _dmpyu4(_mem8_const(&src0[x]), _mem8_const(&src0[x]));
        lo4 = _dshru2(_lo128(square8), shift);
        hi4 = _dshru2(_hi128(square8), shift);

        /* Fetch src1 and assign to register pairs */
        src1lo4 = _mem8_const(&src1[x]);
        src1hi4 = _mem8_const(&src1[x+4]);

        /* Saturate src1 to int16 */
        msklo4  = maxS16 & _dxpnd2(_dcmpgt2(zeros, src1lo4));
        mskhi4  = maxS16 & _dxpnd2(_dcmpgt2(zeros, src1hi4));

        src1lo4 = (src1lo4 & maxS16) | msklo4;
        src1hi4 = (src1hi4 & maxS16) | mskhi4;

        /* Saturate shifted square of src0 to int16 */
        msklo4  = maxS16 & _dxpnd2(_dcmpgt2(zeros, lo4));
        mskhi4  = maxS16 & _dxpnd2(_dcmpgt2(zeros, hi4));

        lo4 = (lo4 & maxS16) | msklo4;
        hi4 = (hi4 & maxS16) | mskhi4;

        /* Saturated add of shifted square and src1 */
        _mem8(&dst[x]) = _dsadd2(lo4, src1lo4);
        _mem8(&dst[x+4]) = _dsadd2(hi4, src1hi4);
    }

#if !defined(VXLIB_ALIGNED8_WIDTHS) && !defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_ALIGNED8_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 8 */
    /* 2 cycles per pixel */
    for(; x < width; x++ ) {
        uint32_t square = (uint32_t)src0[x] * (uint32_t)src0[x];
        uint16_t acc = (uint16_t)src1[x];
        uint32_t res = (uint32_t)acc + (square >> shift);
        dst[x] = (res > (uint32_t)INT16_MAX) ? INT16_MAX : (int16_t)res;
    }

#endif
}

VXLIB_STATUS VXLIB_addSquare_i8u_i16s_o16s(const uint8_t src0[restrict],
                           const VXLIB_bufParams2D_t *src0_addr,
                           const int16_t src1[restrict],
                           const VXLIB_bufParams2D_t *src1_addr,
                           int16_t dst[restrict],
                           const VXLIB_bufParams2D_t *dst_addr,
                           uint32_t shift)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_CHECK_PARAMS)
    status = VXLIB_addSquare_i8u_i16s_o16s_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr, shift);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_EQUAL_WIDTH_STRIDE)
        if((src0_addr->dim_x == src0_addr->stride_y) &&
           ((2 * src1_addr->dim_x) == src1_addr->stride_y) &&
           ((2 * dst_addr->dim_x) == dst_addr->stride_y))
#endif
        {
            VXLIB_addSquare_i8u_i16s_o16s_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y, shift);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const uint8_t   *src0_t = (const uint8_t *)&src0[ y * src0_addr->stride_y ];
                const int16_t   *src1_t = (const int16_t *)&src1[ y * (src1_addr->stride_y / 2) ];
                int16_t         *dst_t  = (int16_t *)&dst[ y * (dst_addr->stride_y / 2) ];

                VXLIB_addSquare_i8u_i16s_o16s_core(src0_t, src1_t, dst_t, src0_addr->dim_x, shift);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_CHECK_PARAMS))

VXLIB_STATUS VXLIB_addSquare_i8u_i16s_o16s_checkParams(const uint8_t src0[],
                                       const VXLIB_bufParams2D_t *src0_addr,
                                       const int16_t src1[],
                                       const VXLIB_bufParams2D_t *src1_addr,
                                       const int16_t dst[],
                                       const VXLIB_bufParams2D_t *dst_addr,
                                       uint32_t shift)
{
    VXLIB_STATUS    status;

    if((src0 == NULL) || (src1 == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src0_addr->dim_x != src1_addr->dim_x) ||
              (src0_addr->dim_x != dst_addr->dim_x) ||
              (src0_addr->dim_y != src1_addr->dim_y) ||
              (src0_addr->dim_y != dst_addr->dim_y) ||
              (src0_addr->stride_y < src0_addr->dim_x) ||
              (src1_addr->stride_y < src0_addr->dim_x) ||
              (dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_UINT8) ||
               (src1_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_EQUAL_WIDTH_STRIDE)
    else if((src0_addr->dim_x != src0_addr->stride_y) ||
            ((2 * src1_addr->dim_x) != src1_addr->stride_y) ||
            ((2 * dst_addr->dim_x) != dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_ADDSQUARE_I8U_I16S_O16S_ALIGNED8_WIDTHS)
    else if(((src0_addr->dim_x % 8U) != 0) ||
            ((src1_addr->dim_x % 8U) != 0) ||
            ((dst_addr->dim_x % 8U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else if(shift > 15U) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

