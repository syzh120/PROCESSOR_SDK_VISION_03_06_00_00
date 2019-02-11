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

#include "VXLIB_cannyNMS_i16s_i16s_i16u_o8u.h"

#define BITS 15
#define TAN22 0.4142135623730950488016887242097

CODE_SECTION(VXLIB_cannyNMS_i16s_i16s_i16u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_cannyNMS_i16s_i16s_i16u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams,  ".text:optimized")

static void VXLIB_cannyNMS_i16s_i16s_i16u_o8u_core(const int16_t srcX[restrict],
                                                    const int16_t srcY[restrict],
                                                    const uint16_t srcMag[restrict],
                                                    uint8_t dst[restrict],
                                                    int32_t width,
                                                    int32_t XStride,
                                                    int32_t YStride,
                                                    int32_t MagStride);

static void VXLIB_cannyNMS_i16s_i16s_i16u_o8u_core(const int16_t srcX[restrict],
                                                    const int16_t srcY[restrict],
                                                    const uint16_t srcMag[restrict],
                                                    uint8_t dst[restrict],
                                                    int32_t width,
                                                    int32_t XStride,
                                                    int32_t YStride,
                                                    int32_t MagStride)
{
    uint32_t        x;
    int32_t absX, absY;
    uint32_t tan22x_hi, tan22x_lo, tan22x;
    int32_t tan67x_hi, tan67x_lo, tan67x;
    uint32_t mask_horz, mask_vert;
    const int64_t sub64 = 0x7fff7fff7fff7fff;
    int64_t mag_r0_3210, mag_r1_3210, mag_r2_3210;
    uint32_t mag_r1_21;
    int64_t  mag_r1_2121, mag_r1_3210_sub, mag_v_r0r2;
    uint32_t horz, vert;
    uint32_t mag_r2_21, mag_r2_21_sub; 
    int64_t mag_dp_r0r2, mag_dn_r0r2;
    uint32_t dp, dn, xor_xy, slope, diag, final;

    /* Constant values for tan(22.5 degrees) and tan(67.5 degrees) as
     * the border between the octants */
    VXLIB_D64 tan22d = ((TAN22*(VXLIB_D64)((uint32_t)1<<BITS)) + 0.5);
    const int32_t tan22 = (int32_t)tan22d;
    int32_t tan67 = tan22+(int32_t)((uint32_t)1<<(BITS+1));

    /* Case 1: SIMD of 2 pixels at a time */
    /* 10/2 = 5 cycles per pixel */
    for( x=0; x < ((uint32_t)width / 2U); x++ ) {

        /* Fetch two X and Y gradient pixels from center row */
        uint32_t x_21  = _mem4_const(&srcX[((uint32_t)XStride/2U) + (x*2U) + 1U]);
        uint32_t y_21  = _mem4_const(&srcY[((uint32_t)YStride/2U) + (x*2U) + 1U]);

        /* Determine the octant of the gradient direction
         * - Take the absolute value of the gradients so we consider
         *   only three regions within the positive quadrant.
         * - These three regions are defined to determine if the
         *   direction of the quadrant is:
         *   1. horizontal (to compare against neighbor pixels to the
         *       left and right of center pixel), defined by
         *       tan(22.5 degrees)
         *   2. vertical (to compare against the neighbor pixels to the
         *       top and bottom of the center pixel), defined by
         *       tan(67.5 degrees)
         *   3. diagonal (to compare against the neighbor pixels in the
         *       respective corners), defined by the else condition of
         *       1 & 2 above.
         *
         *   +-----------(+)
         *   |\``--__       Y-gradient < tan(22.5 degress) = horizontal
         *   | \     ```--
         *   |  \  tan(22.5 degress) <= Y-gradient <= tan(67.5 degress) = diagonal
         *  (+)
         *      Y-gradient < tan(67.5 degress) = vertical
         */

        /* Compute absolute value of the gradients for octant determination */
        absX = _abs2((int32_t)x_21);
        absY = _abs2((int32_t)y_21);

        /* Considered mpy2ir, but not M unit constrained */
        tan22x_hi = (uint32_t)_mpyhir(absX, tan22);
        tan22x_lo = (uint32_t)_mpylir(absX, tan22);
        tan22x    = _pack2(tan22x_hi, tan22x_lo);

        /* Considered mpy2ir, but not M unit constrained */
        tan67x_hi = _mpyhir(absX, tan67);
        tan67x_lo = _mpylir(absX, tan67);
        tan67x    = _spack2(tan67x_hi, tan67x_lo);

        /* Compute the mask of pixels that have horizontal or vertical
         * gradients */
        mask_horz = (uint32_t)_cmpgt2((int32_t)tan22x, absY);
        mask_vert = (uint32_t)_cmpgt2(absY, tan67x);

        /* Fetch 4 magnitude pixels at a time from row, and subtract half the range to
         * fit into signed range */
        mag_r0_3210 = _dsub2(_mem8_const(&srcMag[(0U*((uint32_t)MagStride/2U)) + (x*2U)]), sub64);
        mag_r1_3210 = _dsub2(_mem8_const(&srcMag[(1U*((uint32_t)MagStride/2U)) + (x*2U)]), sub64);
        mag_r2_3210 = _dsub2(_mem8_const(&srcMag[(2U*((uint32_t)MagStride/2U)) + (x*2U)]), sub64);

        /* Get the center magnitude pixels into a single register for comparisons */
        mag_r1_21   = (uint32_t)((uint64_t)mag_r1_3210 >> 16);
        mag_r1_2121 = _itoll(mag_r1_21, mag_r1_21);

        /* Horizontal compares */
        mag_r1_3210_sub = _dsub2(mag_r1_3210, 0x0001000100000000);
        horz           = _dcmpgt2(mag_r1_2121, mag_r1_3210_sub);

        /* Vertical compares */
        mag_r2_21 = (uint32_t)((uint64_t)mag_r2_3210 >> 16);
        mag_r2_21_sub  = (uint32_t)_sub2((int32_t)mag_r2_21, 0x00010001);
        mag_v_r0r2      = _itoll((uint32_t)((uint64_t)mag_r0_3210 >> 16), mag_r2_21_sub);
        vert           = _dcmpgt2(mag_r1_2121, mag_v_r0r2);

        /* Diagonal compares (positive and negative slopes)
         * - The sobel gradients used have positive gradients
         *   in the direction of increasing column number (horizontally)
         *   and increasing row number (vertically).
         * - Therefore, a positive slope is along the diagonals in Q0
         *   and Q3, whereas a negative slope is along the diagonal in
         *   Q1 and Q2
         *
         *   Q0         (-)          Q1
         *       +       |       -
         *          +    |    -
         *             + | -
         *  (-)----------+-----------(+)
         *             - | +
         *          -    |    +
         *       -       |       +
         *   Q2         (+)          Q3
         *
         */
        mag_dp_r0r2 = _itoll(_loll(mag_r0_3210), _hill(mag_r2_3210));
        mag_dn_r0r2 = _itoll(_hill(mag_r0_3210), _loll(mag_r2_3210));

        dp = _dcmpgt2(mag_r1_2121, mag_dp_r0r2);
        dn = _dcmpgt2(mag_r1_2121, mag_dn_r0r2);

        /* Find slope of gradient (0: -1, 1: +1) */
        xor_xy = x_21 ^ y_21;
        slope = (uint32_t)_cmpgt2((int32_t)xor_xy, (int32_t)0xFFFFFFFFU);

        /* Consolidate the bits from the compare for each pixel,
         * and AND with respective mask for octant of gradient direction */
        horz &= horz >> 2;
        horz &= mask_horz;
        
        vert &= vert >> 2;
        vert &= mask_vert;
        
        dp &= dp >> 2;
        dp &= slope;

        dn &= dn >> 2;
        dn &= ~slope;

        diag = dp | dn;
        diag &= ~(mask_horz | mask_vert);

        /* OR the octant result bits */
        final = horz | vert | diag;

        /* Expand the mask bits to 8 bits for each pixel, and label the
         * possible edges as value = '127' */
        _mem2(&dst[x*2U]) = (uint16_t)_xpnd4(final) & 0x7F7FU;
    }

#if !defined(VXLIB_ALIGNED2_WIDTHS) && !defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_ALIGNED2_WIDTHS)
    /* Case 2: Process remaining pixels beyond multiple of 2 */
    /* 10 cycles per pixel */
    #pragma MUST_ITERATE(0,1,1)
    for(x*=2U; x < (uint32_t)width; x++ ) {

        /* Fetch X and Y gradient pixels from center row */
        uint32_t x_1  = (uint32_t)_mem2_const(&srcX[((uint32_t)XStride/2U) + x + 1U]);
        uint32_t y_1  = (uint32_t)_mem2_const(&srcY[((uint32_t)YStride/2U) + x + 1U]);

        /* Determine the octant of the gradient direction
         * - Take the absolute value of the gradients so we consider
         *   only three regions within the positive quadrant.
         * - These three regions are defined to determine if the
         *   direction of the quadrant is:
         *   1. horizontal (to compare against neighbor pixels to the
         *       left and right of center pixel), defined by
         *       tan(22.5 degrees)
         *   2. vertical (to compare against the neighbor pixels to the
         *       top and bottom of the center pixel), defined by
         *       tan(67.5 degrees)
         *   3. diagonal (to compare against the neighbor pixels in the
         *       respective corners), defined by the else condition of
         *       1 & 2 above.
         *
         *   +-----------(+)
         *   |\``--__       Y-gradient < tan(22.5 degress) = horizontal
         *   | \     ```--
         *   |  \  tan(22.5 degress) <= Y-gradient <= tan(67.5 degress) = diagonal
         *  (+)
         *      Y-gradient < tan(67.5 degress) = vertical
         */

        /* Compute absolute value of the gradients for octant determination */
        absX = _abs2((int32_t)x_1);
        absY = _abs2((int32_t)y_1);

        tan22x = (uint32_t)_mpylir(absX, tan22);
        tan67x = _spack2(0, _mpylir(absX, tan67));

        /* Compute the mask of pixels that have horizontal or vertical
         * gradients */
        mask_horz = (uint32_t)_cmpgt2((int32_t)tan22x, absY);
        mask_vert = (uint32_t)_cmpgt2(absY, tan67x);

        /* Fetch 4 magnitude pixels at a time from row, and subtract half the range to
         * fit into signed range */
        mag_r0_3210 = _dsub2(_mem8_const(&srcMag[(0U*((uint32_t)MagStride/2U)) + x]), sub64);
        mag_r1_3210 = _dsub2(_mem8_const(&srcMag[(1U*((uint32_t)MagStride/2U)) + x]), sub64);
        mag_r2_3210 = _dsub2(_mem8_const(&srcMag[(2U*((uint32_t)MagStride/2U)) + x]), sub64);

        /* Get the center magnitude pixels into a single register for comparisons */
        mag_r1_21   = (uint32_t)((uint64_t)mag_r1_3210 >> 16);
        mag_r1_2121 = _itoll(mag_r1_21, mag_r1_21);

        /* Horizontal compares */
        mag_r1_3210_sub = _dsub2(mag_r1_3210, 0x0001000100000000);
        horz           = _dcmpgt2(mag_r1_2121, mag_r1_3210_sub);

        /* Vertical compares */
        mag_r2_21 = (uint32_t)((uint64_t)mag_r2_3210 >> 16);
        mag_r2_21_sub  = (uint32_t)_sub2((int32_t)mag_r2_21, 0x00010001);
        mag_v_r0r2      = _itoll((uint32_t)((uint64_t)mag_r0_3210 >> 16), mag_r2_21_sub);
        vert           = _dcmpgt2(mag_r1_2121, mag_v_r0r2);

        /* Diagonal compares (positive and negative slopes)
         * - The sobel gradients used have positive gradients
         *   in the direction of increasing column number (horizontally)
         *   and increasing row number (vertically).
         * - Therefore, a positive slope is along the diagonals in Q0
         *   and Q3, whereas a negative slope is along the diagonal in
         *   Q1 and Q2
         *
         *   Q0         (-)          Q1
         *       +       |       -
         *          +    |    -
         *             + | -
         *  (-)----------+-----------(+)
         *             - | +
         *          -    |    +
         *       -       |       +
         *   Q2         (+)          Q3
         *
         */
        mag_dp_r0r2 = _itoll(_loll(mag_r0_3210), _hill(mag_r2_3210));
        mag_dn_r0r2 = _itoll(_hill(mag_r0_3210), _loll(mag_r2_3210));

        dp = _dcmpgt2(mag_r1_2121, mag_dp_r0r2);
        dn = _dcmpgt2(mag_r1_2121, mag_dn_r0r2);

        /* Find slope of gradient (0: -1, 1: +1) */
        xor_xy = x_1 ^ y_1;
        slope = (uint32_t)_cmpgt2((int32_t)xor_xy, (int32_t)0xFFFFFFFFU);

        /* Consolidate the bits from the compare for each pixel,
         * and AND with respective mask for octant of gradient direction */
        horz &= horz >> 2;
        horz &= mask_horz;
        
        vert &= vert >> 2;
        vert &= mask_vert;
        
        dp &= dp >> 2;
        dp &= slope;

        dn &= dn >> 2;
        dn &= ~slope;

        diag = dp | dn;
        diag &= ~(mask_horz | mask_vert);

        /* OR the octant result bits */
        final = horz | vert | diag;

        /* Expand the mask bits to 8 bits for each pixel, and label the
         * possible edges as value = '127' */
        dst[x] = (uint8_t)_xpnd4(final) & 0x7FU;
    }
#endif
}

VXLIB_STATUS VXLIB_cannyNMS_i16s_i16s_i16u_o8u(const int16_t src_x[restrict],
                                               const VXLIB_bufParams2D_t * src_x_addr,
                                               const int16_t src_y[restrict],
                                               const VXLIB_bufParams2D_t * src_y_addr,
                                               const uint16_t src_mag[restrict],
                                               const VXLIB_bufParams2D_t * src_mag_addr,
                                               uint8_t dst[restrict],
                                               const VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_CHECK_PARAMS)
    status = VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams(src_x, src_x_addr, src_y, src_y_addr, src_mag, src_mag_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_EQUAL_WIDTH_STRIDE)
        if(((2U * src_x_addr->dim_x) == (uint32_t)src_x_addr->stride_y) &&
           ((2U * src_y_addr->dim_x) == (uint32_t)src_y_addr->stride_y) &&
           ((2U * src_mag_addr->dim_x) == (uint32_t)src_mag_addr->stride_y) &&
           ((1U * dst_addr->dim_x) == (uint32_t)dst_addr->stride_y) &&
            (dst_addr->dim_x == src_x_addr->dim_x))
#endif
        {
            int32_t width = (int32_t)dst_addr->stride_y * (int32_t)dst_addr->dim_y;
            VXLIB_cannyNMS_i16s_i16s_i16u_o8u_core(src_x, src_y, src_mag, dst, width, src_x_addr->stride_y, src_y_addr->stride_y, src_mag_addr->stride_y);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_EQUAL_WIDTH_STRIDE)
        else {
            int32_t    y;

            for( y=0; y < (int32_t)dst_addr->dim_y; y++ ) {
                const int16_t   *src_x_t = (const int16_t *)&src_x[ y * (src_x_addr->stride_y / 2) ];
                const int16_t   *src_y_t = (const int16_t *)&src_y[ y * (src_y_addr->stride_y / 2) ];
                const uint16_t  *src_mag_t = (const uint16_t *)&src_mag[ y * (src_mag_addr->stride_y / 2) ];
                uint8_t          *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_cannyNMS_i16s_i16s_i16u_o8u_core(src_x_t, src_y_t, src_mag_t, dst_t, (int32_t)dst_addr->dim_x, src_x_addr->stride_y, src_y_addr->stride_y, src_mag_addr->stride_y);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams(const int16_t src_x[restrict],
                                                           const VXLIB_bufParams2D_t * src_x_addr,
                                                           const int16_t src_y[restrict],
                                                           const VXLIB_bufParams2D_t * src_y_addr,
                                                           const uint16_t src_mag[restrict],
                                                           const VXLIB_bufParams2D_t * src_mag_addr,
                                                           uint8_t dst[restrict],
                                                           const VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status;

    if((src_x == NULL) || (src_y == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_x_addr->dim_x != src_y_addr->dim_x) ||
               (src_x_addr->dim_x != src_mag_addr->dim_x) ||
               (src_x_addr->dim_x < dst_addr->dim_x) ||
               (src_x_addr->dim_y != src_y_addr->dim_y) ||
               (src_x_addr->dim_y != src_mag_addr->dim_y) ||
               ((src_x_addr->dim_y-2) != dst_addr->dim_y) ||
               ((uint32_t)src_x_addr->stride_y < (src_x_addr->dim_x*2U)) ||
               ((uint32_t)src_y_addr->stride_y < (src_y_addr->dim_x*2U)) ||
               ((uint32_t)src_mag_addr->stride_y < (src_mag_addr->dim_x*2U)) ||
               ((uint32_t)dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_x_addr->data_type != VXLIB_INT16) ||
               (src_y_addr->data_type != VXLIB_INT16) ||
               (src_mag_addr->data_type != VXLIB_UINT16) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_EQUAL_WIDTH_STRIDE)
    else if((2U * src_x_addr->dim_x != (uint32_t)src_x_addr->stride_y) ||
             (2U * src_y_addr->dim_x != (uint32_t)src_y_addr->stride_y) ||
             (2U * src_mag_addr->dim_x != (uint32_t)src_mag_addr->stride_y) ||
             (dst_addr->dim_x != (uint32_t)dst_addr->stride_y)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED2_WIDTHS) || defined(VXLIB_CANNYNMS_I16S_I16S_I16U_O8U_ALIGNED2_WIDTHS)
    else if((dst_addr->dim_x % 2U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

