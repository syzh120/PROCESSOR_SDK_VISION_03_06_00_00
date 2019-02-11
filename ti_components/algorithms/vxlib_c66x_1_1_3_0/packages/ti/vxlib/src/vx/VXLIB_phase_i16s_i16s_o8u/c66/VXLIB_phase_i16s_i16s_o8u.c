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

#include "VXLIB_phase_i16s_i16s_o8u.h"

CODE_SECTION(VXLIB_phase_i16s_i16s_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_phase_i16s_i16s_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_phase_i16s_i16s_o8u_checkParams,  ".text:optimized")

static inline uint8_t atan2_8b_core (const int16_t y, const int16_t x);

static void VXLIB_phase_i16s_i16s_o8u_core(const int16_t src0[restrict],
                              const int16_t src1[restrict],
                              uint8_t dst[restrict],
                              int32_t width);

#define PIBY4_8b      (uint32_t)(32)
#define PI_8b         (PIBY4_8b*4U)
#define PIBY2_8b      (PIBY4_8b*2U)
#define ThreePIBY2_8b (PIBY2_8b*3U)
#define TwoPI_8b      (PI_8b*2U)

#define rnd7 ((uint32_t)1 << (7-1))
#define rndh ((uint32_t)1 << (16-1))
#define Q7toQ8 ((uint32_t)1 << 1)

#define DIV_TBL_SIZE 32
#define DIV_TBL_Q 14

static inline uint8_t atan2_8b_core (const int16_t y, const int16_t x)
{
    int32_t tL, est, poly_x, poly_acc;
    int32_t is_absx_gteq_absy;
    uint32_t xbig, ysmall, temp, shifts, k2k1, angle;
    uint32_t octantDecisionIndx, octantDecision_t0, octantDecision_t1;

    static const int16_t atan2_8b_divTbl[32] = {
        /* 
        Values in Q(DIV_TBL_Q), ith (0-base) entry is 
        {2^DIV_TBL_Q * (1 / (0.5 + 2^(-log2(DIV_TBL_SIZE)-1) * i)} 
        */
        32767, 31775, 30840, 29959, 29127, 28340, 27594, 26887,
        26214, 25575, 24966, 24385, 23831, 23302, 22795, 22310,
        21845, 21400, 20972, 20560, 20165, 19784, 19418, 19065, 
        18725, 18396, 18079, 17772, 17476, 17190, 16913, 16644
    };

    /* 
        octant table to find angle adjustment factors, two 16-bit factors
        coded as packed single int instead of two tables for 
        potentially more efficient memory loads 
    */
    static const uint32_t atan2_8b_octantKs[] = {
        /*  (k1 << 16) | k2                                (x >= 0) (y >= 0) (|x| > |y|) */
        ( ((ThreePIBY2_8b << 7) + rnd7) << 16) | ((uint32_t)-1 & 0x0000FFFFU), /*  0       0        0  */
        ( ((PI_8b         << 7) + rnd7) << 16) | ((uint32_t) 1 & 0x0000FFFFU), /*  0       0        1  */
        ( ((PIBY2_8b      << 7) + rnd7) << 16) | ((uint32_t) 1 & 0x0000FFFFU),
        ( ((PI_8b         << 7) + rnd7) << 16) | ((uint32_t)-1 & 0x0000FFFFU),
        ( ((ThreePIBY2_8b << 7) + rnd7) << 16) | ((uint32_t) 1 & 0x0000FFFFU),
        ( ((TwoPI_8b      << 7) + rnd7) << 16) | ((uint32_t)-1 & 0x0000FFFFU),
        ( ((PIBY2_8b      << 7) + rnd7) << 16) | ((uint32_t)-1 & 0x0000FFFFU),
        ( (((uint32_t)0  << 7) + rnd7) << 16) | ((uint32_t) 1 & 0x0000FFFFU)  /* 1       1        1 */
    };

    /* assume x is big and y is small */
    xbig = (uint32_t)_abs((int32_t)x);
    ysmall = (uint32_t)_abs((int32_t)y);

    is_absx_gteq_absy = (int32_t)(xbig >= ysmall);
     
    /* swap if necessary to make x big and y small */
    if (is_absx_gteq_absy == 0) {
        temp = xbig;
        xbig = ysmall;
        ysmall = temp;
    }

    /* normalize xbig and scale ysmall to same scale */
    shifts = _norm((int32_t)xbig);
    xbig = xbig << shifts;
    ysmall = ysmall << shifts;

    /* 
    perform 1/xs using Newton Raphson method 
    */

    /* initial guess using upper 5 bits after left shift by 2 
    to ignore redundant sign and "1" bits */
    est = atan2_8b_divTbl[_extu(xbig, 2U, (uint32_t)(32-5))]; /* est in Q14 */

    /* 1st iteration  est = est * (2 - xbig * est) */
    tL = 0x7fffffff /*(2* (1L << 30) - 1L)*/ - _smpyhl((int32_t)xbig, est); /* tL = Q30 */
    est = _sshl(_smpyhl(tL, est),1U); /* tL(Q(30-16))*est(Q14) << 1+1 = Q30 */

    /* 2nd iteration est = est * (2 - xbig * est)
     xbig(Q15) * est(Q(30-16)) << 1= Q30 */
    tL = 0x7fffffff /*(2* (1L << 30) - 1L)*/ - _smpyh((int32_t)xbig, est);
    est = _sshl(_smpyh(tL,est),1U); /* tL(Q(30-16))*est(Q(30-16)) <<(1+1)= Q30*/

    /* ysmall*(1/xbig) */
    poly_x = _sshl(_smpyh(est,(int32_t)ysmall),1U); /* ysmalll(Q15)*est(Q(30-16)) << 2 = Q31 */

    /* 
    4th order polynomial using Matlab as follows..
    >x = x = (0:1:(2^15-1))./2^15;
    >plot(x,atan(x)*4/pi*32)
    Use Tools->Basic Fitting, check "4th degree polynomial" and get equation
    Note here x is actually y/x mapped in first octant
    
    5.7655 * x^4 -13.9883 * x^3 -0.6609 * x^2 + 40.9001 * x -0.0064 

    Q12(5.7655)   = 23616
    Q27(-13.9883) = -1877477845
    Q26(-0.6609)  = -44352248 
    Q25(40.9001)  = 1372379624
    Q24(-0.0064)  = -107374
    */

    poly_acc = _mpyhl(poly_x, 23616L) - 1877477845L;   /* Q(31-16) + Q12 = Q27 */
    poly_acc = _mpyh(poly_x, poly_acc) - 44352248L;       /* Q15 + Q(27-16) = Q26 */
    poly_acc = _mpyh(poly_x, poly_acc) + 1372379624L;     /* Q15 + Q(26-16) = Q25 */
    poly_acc = (_mpyh(poly_x, poly_acc) - 107374L) + (int32_t)rndh;  /* Q15 + Q(25-16) = Q24 */

    /* adjust for angle position in octants */
    octantDecision_t0 = (uint32_t)(x >= 0);
    octantDecision_t1 = (uint32_t)(y >= 0);
    octantDecisionIndx = (octantDecision_t0 << 2) | (octantDecision_t1 << 1) | (uint32_t)is_absx_gteq_absy;
    k2k1 = atan2_8b_octantKs[octantDecisionIndx];

    /* Q(poly_acch) = Q(24-16) = Q8 */
    angle = _mpyhlu((uint32_t)poly_acc, k2k1) + _mpyhlu(k2k1, Q7toQ8); 
    angle = angle >> 8; 

    return (uint8_t)angle;
}

static void VXLIB_phase_i16s_i16s_o8u_core(const int16_t src0[restrict],
                              const int16_t src1[restrict],
                              uint8_t dst[restrict],
                              int32_t width)
{
    int32_t    x;

    #pragma UNROLL(2)
    for( x=0; x < width; x++ ) {
        dst[x] = atan2_8b_core(src1[x], src0[x]);
    }
}


VXLIB_STATUS VXLIB_phase_i16s_i16s_o8u(const int16_t src0[restrict],
                          const VXLIB_bufParams2D_t *src0_addr,
                          const int16_t src1[restrict],
                          const VXLIB_bufParams2D_t *src1_addr,
                          uint8_t dst[restrict],
                          const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_PHASE_I16S_I16S_O8U_CHECK_PARAMS)
    status = VXLIB_phase_i16s_i16s_o8u_checkParams(src0, src0_addr, src1, src1_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_PHASE_I16S_I16S_O8U_EQUAL_WIDTH_STRIDE)
        if(((2 * src0_addr->dim_x) == src0_addr->stride_y) &&
           ((2 * src1_addr->dim_x) == src1_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y))
#endif
        {
            VXLIB_phase_i16s_i16s_o8u_core(src0, src1, dst, src0_addr->dim_x * src0_addr->dim_y);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_PHASE_I16S_I16S_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;

            for( y=0; y < src0_addr->dim_y; y++ ) {

                const int16_t   *src0_t = (const int16_t *)&src0[ y * (src0_addr->stride_y / 2) ];
                const int16_t   *src1_t = (const int16_t *)&src1[ y * (src1_addr->stride_y / 2) ];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y ];

                VXLIB_phase_i16s_i16s_o8u_core(src0_t, src1_t, dst_t, src0_addr->dim_x);
            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_PHASE_I16S_I16S_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_PHASE_I16S_I16S_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_phase_i16s_i16s_o8u_checkParams(const int16_t src0[],
                                      const VXLIB_bufParams2D_t *src0_addr,
                                      const int16_t src1[],
                                      const VXLIB_bufParams2D_t *src1_addr,
                                      const uint8_t dst[],
                                      const VXLIB_bufParams2D_t *dst_addr)
{
    VXLIB_STATUS    status;

    if((src0 == NULL) || (src1 == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src0_addr->dim_x != src1_addr->dim_x) ||
              (src0_addr->dim_x != dst_addr->dim_x) ||
              (src0_addr->dim_y != src1_addr->dim_y) ||
              (src0_addr->dim_y != dst_addr->dim_y) ||
              (src0_addr->stride_y < (2 * src0_addr->dim_x)) ||
              (src1_addr->stride_y < (2 * src0_addr->dim_x)) ||
              (dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src0_addr->data_type != VXLIB_INT16) ||
               (src1_addr->data_type != VXLIB_INT16) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

