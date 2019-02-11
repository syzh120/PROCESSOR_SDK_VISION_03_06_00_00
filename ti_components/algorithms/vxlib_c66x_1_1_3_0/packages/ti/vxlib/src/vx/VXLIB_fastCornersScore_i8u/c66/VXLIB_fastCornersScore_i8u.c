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

#include "VXLIB_fastCornersScore_i8u.h"

CODE_SECTION(VXLIB_fastCornersScore_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_fastCornersScore_i8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_fastCornersScore_i8u_checkParams,  ".text:optimized")

static void fastCorners_make_offsets_9(int32_t pixl[], uint32_t row_stride);

static int32_t fast9_corner_score(const uint8_t *restrict p, const uint8_t co[], int32_t bstart);

static void VXLIB_fastCornersScore_i8u_core(const uint8_t img[restrict],
                                          uint16_t stride,
                                          uint8_t  b,
                                          const uint32_t featuresLoc[restrict],
                                          uint8_t  score[restrict],
                                          uint32_t numFeatures,
                                          uint8_t  scratch[restrict]);

#define MARGIN_PIXELS       (3)
#define NUM_PIXELS_IN_RING  ((uint8_t)16)

static void fastCorners_make_offsets_9(int32_t pixl[], uint32_t row_stride)
{
    pixl[0] = (int32_t)0 + ((int32_t)row_stride * (int32_t)3);
    pixl[1] = (int32_t)1 + ((int32_t)row_stride * (int32_t)3);
    pixl[2] = (int32_t)2 + ((int32_t)row_stride * (int32_t)2);
    pixl[3] = (int32_t)3 + ((int32_t)row_stride * (int32_t)1);
    pixl[4] = (int32_t)3 + ((int32_t)row_stride * (int32_t)0);
    pixl[5] = (int32_t)3 + ((int32_t)row_stride * (int32_t)-1);
    pixl[6] = (int32_t)2 + ((int32_t)row_stride * (int32_t)-2);
    pixl[7] = (int32_t)1 + ((int32_t)row_stride * (int32_t)-3);
    pixl[8] = (int32_t)0 + ((int32_t)row_stride * (int32_t)-3);
    pixl[9] = (int32_t)-1 + ((int32_t)row_stride * (int32_t)-3);
    pixl[10] = (int32_t)-2 + ((int32_t)row_stride * (int32_t)-2);
    pixl[11] = (int32_t)-3 + ((int32_t)row_stride * (int32_t)-1);
    pixl[12] = (int32_t)-3 + ((int32_t)row_stride * (int32_t)0);
    pixl[13] = (int32_t)-3 + ((int32_t)row_stride * (int32_t)1);
    pixl[14] = (int32_t)-2 + ((int32_t)row_stride * (int32_t)2);
    pixl[15] = (int32_t)-1 + ((int32_t)row_stride * (int32_t)3);
}

static int32_t fast9_corner_score(const uint8_t *restrict p, const uint8_t co[], int32_t bstart)
{
    uint8_t    startpos, i;
    uint8_t    Bscore[16], Dscore[16];
    uint8_t    score_b, score_d;
    uint8_t    pMin, pMax;
    uint8_t    cb;
    int32_t    score;

    cb = *p;

    for( startpos=0; startpos < (uint8_t)16; startpos++ ) {
        pMin = co[startpos];
        pMax = pMin;

        for( i=(uint8_t)1; i < (uint8_t)9; i++ ) {
            if( pMax < co[startpos + i] ) {
                pMax = co[startpos + i];
            }
            if( pMin > co[startpos + i] ) {
                pMin = co[startpos + i];
            }
        }

        Bscore[startpos] = pMax;
        Dscore[startpos] = pMin;
    }

    score_b = Bscore[0];
    score_d = Dscore[0];

    for( i=(uint8_t)1; i < (uint8_t)16; i++ ) {
        if( score_b > Bscore[i] ) {
            score_b = Bscore[i];
        }
        if( score_d < Dscore[i] ) {
            score_d = Dscore[i];
        }
    }

    if((score_b > cb) && (score_d > cb)) {
        if( score_b > score_d ) {
            score = (int32_t)score_d - (int32_t)cb - 1;
        } else {
            score = (int32_t)score_b - (int32_t)cb - 1;
        }
    } else if((score_b < cb) && (score_d < cb)) {
        if( score_b > score_d ) {
            score = (int32_t)cb - (int32_t)score_b - 1;
        } else {
            score = (int32_t)cb - (int32_t)score_d - 1;
        }
    } else {
        /* Ideally control should never come to this portion of the code. This situation
           indicates that with no threshold current pixel can be a corner. Hence in that
           situation just return the start threshold.
        */
        score = bstart;
    }

    /* Below is the situation when start threshold itself is higher than calculated threshold.
       Ideally this situation should not come, so in that case just return the start threshold
    */
    if( bstart > score ) {
        score = bstart;
    }

    return (score);
}

static void VXLIB_fastCornersScore_i8u_core(const uint8_t img[restrict],
                                         uint16_t stride,
                                         uint8_t  b,
                                         const uint32_t featuresLoc[restrict],
                                         uint8_t  score[restrict],
                                         uint32_t numFeatures,
                                         uint8_t  scratch[restrict])
{
    int32_t    n0, i;

    int32_t    ringPixOffsets[17];
    int32_t    curOffset;

    const uint8_t *restrict    pu8imgF1;
    const uint8_t *restrict    pu8imgF2;
    const uint8_t *restrict    pu8imgF3;
    const uint8_t *restrict    pu8imgF4;
    const uint8_t *restrict    pu8imgF5;
    const uint8_t *restrict    pu8imgF6;
    const uint8_t *restrict    pu8imgF7;
    const uint8_t *restrict    pu8imgF8;

    uint32_t    stridepkd = ((uint32_t)stride << 0x10U) | 0x1U;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * The following code is taking a scratch pointer, which may not be properly
     * aligned, and aligning it to an 8 byte boundary.  For this, a pointer must be
     * cast to an integral type to compute the boundary, and then cast it back to a pointer.
     * size_t is used to ensure that the integral type can contain the full value of the pointer
     * depending on the architecture.
     */
    uint8_t   *scratchAligned = scratch + 0x7U;
    size_t     pu64scratchBaseVal = (((size_t)scratchAligned / (size_t)8) * (size_t)8);
    int64_t   *pu64scratchBase = (int64_t *)pu64scratchBaseVal;
    int64_t   *pu64scratch     = pu64scratchBase;

    int64_t *restrict    pu64RSrc;
    int64_t *restrict    pu64R1Src;
    int64_t *restrict    pu64RDst;
    int64_t *restrict    pu64R1Dst;

    uint32_t    u32temp1, u32temp2, u32temp3, u32temp4, u32temp5, u32temp6;
    int64_t    u64temp1, u64temp2, u64temp3, u64temp4, centerPix;
    int64_t    maxResult, minResult;
    uint32_t    b_tmp = (uint32_t)b;
    uint8_t     bStartPlus1  = (b_tmp < 255U) ? (b + 1U) : b;
    uint32_t    u32bPkd      = ((uint32_t)bStartPlus1 << 0x18U) |
                               ((uint32_t)bStartPlus1 << 0x10U) |
                               ((uint32_t)bStartPlus1 << 0x8U)  |
                               (uint32_t)bStartPlus1;
    int64_t    u64bPkd = _itoll(u32bPkd, u32bPkd);

    fastCorners_make_offsets_9(&ringPixOffsets[1], (uint32_t)stride);
    /* First offset is for center pixel. This is done so that
       center pixels for all the 8 feature can be fetched in loop
       while fetching the ring pixels.
     */
    ringPixOffsets[0] = 0x0;

    for( n0 = 0; (uint32_t)n0 < (numFeatures/8U); n0++ ) {

        pu64scratch     = pu64scratchBase;
        /* For all 8 features , take out the ring pixels and put them
           in transposed vector form in scratch buffer. Lets assume
           pixels corresponding to feature point #i are Fi1,Fi2,Fi3..
           Fi16. Then in scratch buffer it will be placed like
           Fi1  F(i+1)1   F(i+2)1  ............  F(i+7)1  F(i+8)1
           Fi2  F(i+1)2   F(i+2)2  ............  F(i+7)2  F(i+8)2
           Fi3  F(i+1)3   F(i+2)3  ............  F(i+7)3  F(i+8)3
           .... .......   .......  ............  .......  .......
           .... .......   .......  ............  ....... .......
           Fi15 F(i+1)15  F(i+2)15 ............  F(i+7)15 F(i+8)15
           Fi16 F(i+1)16  F(i+2)16 ............  F(i+7)16 F(i+8)16

           ~50 % of cycle is going in making this kind of data
           arrangement. This will allow to SIMD operation of
           max and min instructions.
          */
        pu8imgF1   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 0], (int32_t)stridepkd);
        pu8imgF2   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 1], (int32_t)stridepkd);
        pu8imgF3   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 2], (int32_t)stridepkd);
        pu8imgF4   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 3], (int32_t)stridepkd);
        pu8imgF5   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 4], (int32_t)stridepkd);
        pu8imgF6   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 5], (int32_t)stridepkd);
        pu8imgF7   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 6], (int32_t)stridepkd);
        pu8imgF8   = img + _dotp2((int32_t)featuresLoc[(n0*8) + 7], (int32_t)stridepkd);

        for( i = 0; i < 17; i++ ) {

            curOffset   = ringPixOffsets[i];

            u32temp1    = pu8imgF1[curOffset];
            u32temp2    = pu8imgF2[curOffset];
            u32temp3    = pu8imgF3[curOffset];
            u32temp4    = pu8imgF4[curOffset];

            u64temp1    = _itoll(u32temp2, u32temp1);
            u64temp2    = _itoll(u32temp4, u32temp3);
            u64temp3    = _dpackl4(u64temp2, u64temp1);
            u32temp5    = ((uint32_t)_hill(u64temp3) << 0x8U) | _loll(u64temp3);

            u32temp1    = pu8imgF5[curOffset];
            u32temp2    = pu8imgF6[curOffset];
            u32temp3    = pu8imgF7[curOffset];
            u32temp4    = pu8imgF8[curOffset];

            u64temp1    = _itoll(u32temp2, u32temp1);
            u64temp2    = _itoll(u32temp4, u32temp3);
            u64temp3    = _dpackl4(u64temp2, u64temp1);
            u32temp6    = ((uint32_t)_hill(u64temp3) << 0x8U) | _loll(u64temp3);

            u64temp1    = _itoll(u32temp6, u32temp5);
            /* To find the minimum and maximum of sliding 9 pixels among the
               ring pixel, it is required that top pixels are repeated at bottom.
               Here all the 16 pixels are repeated to avoid avoid any condition
               check. However extra 8 pixels repeated will be not needed by
               code, hence will be used are scratch area in later part of the
               code.
             */
            _amem8(pu64scratch + 16) = u64temp1;
            _amem8(pu64scratch) = u64temp1;
            pu64scratch++;
        }

        /* Scratch Buffer Organization :
           pu64scratch
             |
             v
           currentPixel   ( center pixels for all the 8 feature points)
           DoubleWord #0  ( first ring pixel for 8 feature points)
           DoubleWord #1  ( second ring pixel for 8 feature points)
           DoubleWord #2  ( third ring pixel for 8 feature points)
           .............
           .............
           DoubleWord #15 ( last ring pixel for 8 feature points)
           DoubleWord #16 ( first ring pixel for 8 feature points)
           ..............
           DoubleWord #23 ( eighth ring pixel for 8 feature points)
           DoubleWord (R) #0
           .............
           DoubleWord (R) #15
           DoubleWord (R1) #0
           .............
           DoubleWord (R1) #15

           Hence total scratch size is (1+ 24+ 16+ 16)*8 = 456 bytes + 7bytes
           for for double word alignment, total = 463 bytes.
         */
        pu64scratch         = pu64scratchBase + 1;
        pu64RSrc            = pu64scratch + 7;
        pu64R1Src           = pu64scratch + 15;
        pu64RDst            = pu64scratch + 24;
        pu64R1Dst           = pu64scratch + 24 + 16;

        u64temp1            = 0x0;
        u64temp2            = 0x0;
        u64temp3            = (int64_t)0xFFFFFFFFFFFFFFFFU;
        u64temp4            = (int64_t)0xFFFFFFFFFFFFFFFFU;

        /* pu64RDst[2*i] is the maximum of elements starting from
           (7) to (7 + i)th pixel in ring pixels.
           pu64RDst[2*i +1] is the minimum of elements starting from
           (7) to (7 + i)th pixel in ring pixels.
           pu64R1Dst[2*i] is the maximum of elements starting from
           (15) to (15 + i)th pixel in ring pixels.
           pu64R1Dst[2*i + 1] is the minimum of elements starting from
           (15) to (15 + i)th pixel in ring pixels.
         */
        for( i = 0; i < 8; i++ ) {

            u64temp1           = _dmaxu4(u64temp1, _amem8(pu64RSrc));
            _amem8(pu64RDst)   = u64temp1;
            pu64RDst++;

            u64temp2           = _dmaxu4(u64temp2, _amem8(pu64R1Src));
            _amem8(pu64R1Dst)  = u64temp2;
            pu64R1Dst++;


            u64temp3           = _dminu4(u64temp3, _amem8(pu64RSrc));
            pu64RSrc--;
            _amem8(pu64RDst)   = u64temp3;
            pu64RDst++;

            u64temp4           = _dminu4(u64temp4, _amem8(pu64R1Src));
            pu64R1Src--;
            _amem8(pu64R1Dst)  = u64temp4;
            pu64R1Dst++;
        }

        pu64RSrc        = pu64scratch + 8;
        pu64R1Src       = pu64scratch + 16;
        pu64RDst        = pu64scratch + 24 + 15;
        pu64R1Dst       = pu64scratch + 24 + 16 + 15;
        maxResult       = 0x0;
        minResult       = (int64_t)0xFFFFFFFFFFFFFFFFU;
        u64temp1        = 0x0;
        u64temp2        = 0x0;
        u64temp3        = (int64_t)0xFFFFFFFFFFFFFFFFU;
        u64temp4        = (int64_t)0xFFFFFFFFFFFFFFFFU;

        /* Below loop calculates the sliding maximum and
           minimum of 9 pixels. And then minimum of maximum
           found, and maximum of minimum found.
         */
        for( i = 0; i < 8; i++ ) {
            u64temp3      = _dminu4(u64temp3, _amem8(pu64RSrc));
            maxResult     = _dmaxu4(maxResult, _dminu4(u64temp3, _amem8(pu64RDst)));
            pu64RDst--;

            u64temp4      = _dminu4(u64temp4, _amem8(pu64R1Src));
            maxResult     = _dmaxu4(maxResult, _dminu4(u64temp4, _amem8(pu64R1Dst)));
            pu64R1Dst--;

            u64temp1      = _dmaxu4(u64temp1, _amem8(pu64RSrc));
            pu64RSrc++;
            minResult     = _dminu4(minResult, _dmaxu4(u64temp1, _amem8(pu64RDst)));
            pu64RDst--;

            u64temp2      = _dmaxu4(u64temp2, _amem8(pu64R1Src));
            pu64R1Src++;
            minResult     = _dminu4(minResult, _dmaxu4(u64temp2, _amem8(pu64R1Dst)));
            pu64R1Dst--;
        }

        centerPix       = _amem8_const(pu64scratchBase);

        /* MISRA.BITS.NOT_UNSIGNED
         * MISRAC_2004 Rule_12.7
         * MISRAC_WAIVER:
         * The C6x DSP compiler treats all types as unsigned when it comes
         * to the following bitwise operations (&, |, ~, ^).  In this case,
         * the compiler document requires the 64bit bitwise operations to
         * use the type "int64_t". This waiver applies to all the instances
         * of the '&' and '|' operator on int64 bit types below (before the
         * next close bracket '}'):
         */

        /* if((score_b > cb) && (score_d > cb) && (score_b > score_d))
           score = score_d - cb - 1;
          */
        u32temp1 = _dcmpgtu4(minResult, centerPix) &
                   _dcmpgtu4(maxResult, centerPix);
        u32temp2 = u32temp1 & _dcmpgtu4(minResult, maxResult);
        u64temp1 = _dxpnd4(u32temp2) &
                   _itoll((uint32_t)_sub4((int32_t)_hill(maxResult), (int32_t)_hill(centerPix)),
                          (uint32_t)_sub4((int32_t)_loll(maxResult), (int32_t)_loll(centerPix)));
        /* if((score_b > cb) && (score_d > cb) && (score_b <= score_d))
           score = score_b - cb - 1;
          */
        u32temp3 = u32temp1 & ~(_dcmpgtu4(minResult, maxResult));
        u64temp2 = _dxpnd4(u32temp3) &
                   _itoll((uint32_t)_sub4((int32_t)_hill(minResult), (int32_t)_hill(centerPix)),
                          (uint32_t)_sub4((int32_t)_loll(minResult), (int32_t)_loll(centerPix)));

        u64temp3 = u64temp1 | u64temp2;
        u32temp4 = u32temp2 | u32temp3;


        /* if ((score_b < cb) && (score_d < cb) && (score_b > score_d))
           score = cb - score_b - 1;
          */
        u32temp1 = _dcmpgtu4(centerPix, minResult) &
                   _dcmpgtu4(centerPix, maxResult);
        u32temp2 = u32temp1 & _dcmpgtu4(minResult, maxResult);
        u64temp1 = _dxpnd4(u32temp2) &
                   _itoll((uint32_t)_sub4((int32_t)_hill(centerPix), (int32_t)_hill(minResult)),
                          (uint32_t)_sub4((int32_t)_loll(centerPix), (int32_t)_loll(minResult)));

        /* if ((score_b < cb) && (score_d < cb) && (score_b <= score_d))
           score = cb - score_d - 1;
          */
        u32temp3 = u32temp1 & ~(_dcmpgtu4(minResult, maxResult));
        u64temp2 = _dxpnd4(u32temp3) &
                   _itoll((uint32_t)_sub4((int32_t)_hill(centerPix), (int32_t)_hill(maxResult)),
                          (uint32_t)_sub4((int32_t)_loll(centerPix), (int32_t)_loll(maxResult)));

        /* else
           score = bstart;
         */
        u64temp3 |= u64temp1 | u64temp2;
        u32temp4 |= u32temp2 | u32temp3;
        u32temp4  = ~u32temp4;
        u64temp3 |= _dxpnd4(u32temp4) & u64bPkd;

        /*if(bstart > score)
          score = bstart;
         */
        u64temp1  = _dxpnd4(_dcmpgtu4(u64bPkd, u64temp3));
        u64temp3  = (u64temp1 & u64bPkd) | (~u64temp1 & u64temp3);
        u64temp3  = _itoll((uint32_t)_sub4((int32_t)_hill(u64temp3), 0x01010101),
                           (uint32_t)_sub4((int32_t)_loll(u64temp3), 0x01010101));

        _amem8(&score[n0*8]) = u64temp3;
    }

    n0*=8;
    if(n0 < (int32_t)numFeatures)
    {
        int32_t          offsets[24];
        uint8_t          ringPixels[24];
        const uint8_t   *centerPixel;
        uint32_t         curFeatureLoc;

        fastCorners_make_offsets_9(offsets, (uint32_t)stride);

        offsets[16] = offsets[0];
        offsets[17] = offsets[1];
        offsets[18] = offsets[2];
        offsets[19] = offsets[3];
        offsets[20] = offsets[4];
        offsets[21] = offsets[5];
        offsets[22] = offsets[6];
        offsets[23] = offsets[7];

        for( ; n0 < (int32_t)numFeatures; n0++ ) {

            curFeatureLoc = featuresLoc[n0];

            centerPixel = img + ((curFeatureLoc >> 0x10U) * stride) + (curFeatureLoc & 0xFFFFU);

            for( i = 0; i < 24; i++ ) {
                ringPixels[i] = centerPixel[offsets[i]];
            }

            score[n0] = (uint8_t)fast9_corner_score(centerPixel, ringPixels, (int32_t)b);
        }
    }
}

VXLIB_STATUS VXLIB_fastCornersScore_i8u(const uint8_t src[],
                                     const VXLIB_bufParams2D_t * src_addr,
                                     const uint32_t corners[],
                                     uint8_t strengths[],
                                     uint8_t strength_thresh,
                                     uint32_t num_corners,
                                     uint8_t scratch[],
                                     uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_FASTCORNERSSCORE_I8U_CHECK_PARAMS)
    status = VXLIB_fastCornersScore_i8u_checkParams(src, src_addr, corners, strengths, strength_thresh, num_corners, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        VXLIB_fastCornersScore_i8u_core(src, src_addr->stride_y, strength_thresh,
                                     corners, strengths, num_corners, scratch);
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_FASTCORNERSSCORE_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_FASTCORNERSSCORE_I8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_fastCornersScore_i8u_checkParams(const uint8_t src[],
                                                 const VXLIB_bufParams2D_t * src_addr,
                                                 const uint32_t corners[],
                                                 const uint8_t strengths[],
                                                 uint8_t strength_thresh,
                                                 uint32_t num_corners,
                                                 const uint8_t scratch[],
                                                 uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (corners == NULL) || (strengths == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if( src_addr->data_type != VXLIB_UINT8 ) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(scratch_size < 463U) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}
#endif
