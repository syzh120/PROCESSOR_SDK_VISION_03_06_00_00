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

#include "VXLIB_fastCornersDetect_i8u.h"

CODE_SECTION(VXLIB_fastCornersDetect_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_fastCornersDetect_i8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_fastCornersDetect_i8u_checkParams,  ".text:optimized")

static void fastCorners_make_offsets_9(int32_t pixl[], uint32_t row_stride);

static uint32_t VXLIB_fastCornersDetect_i8u_core(const uint8_t image[restrict],
                                         uint32_t width,
                                         uint32_t pitch,
                                         uint16_t startY,
                                         uint8_t differenceThreshold,
                                         uint32_t features[restrict],
                                         int32_t features_capacity,
                                         uint8_t scratchBuffer[restrict]);

#define MARGIN_PIXELS       (3)
#define NUM_PIXELS_IN_RING  (16)

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

static uint32_t VXLIB_fastCornersDetect_i8u_core(const uint8_t image[restrict],
                                         uint32_t width,
                                         uint32_t pitch,
                                         uint16_t startY,
                                         uint8_t differenceThreshold,
                                         uint32_t features[restrict],
                                         int32_t features_capacity,
                                         uint8_t scratchBuffer[restrict])
{
    uint32_t    n_featuresFound = 0;

    uint32_t          j;
    int32_t           k;

    const uint8_t *restrict    ptrCenter    = image;
    uint8_t        *restrict    scratch      = scratchBuffer;

    int64_t    centerVal76543210;
    int64_t    ringVal1, ringVal2;
    uint64_t    centerValDown, centerValDown_2;
    int64_t    centerValBoost, centerValBoost_2, fwDoubleResultVec;
    uint32_t    tempu32_1, tempu32_2, tempu32_3, tempu32_4, tempu32_5;
    uint32_t    cornerResult, backSingleResultVec;
    int64_t    tempu64_1, tempu64_2, tempu64_3;
    uint16_t    isCorner;
    uint64_t    subMask;
    uint8_t     circIndex;
    int32_t     offset[16];
    uint16_t    x, y;

    uint8_t     diffTh    = differenceThreshold;
    uint32_t    diffThPkd = ((uint32_t)diffTh << 0x18U) |
                            ((uint32_t)diffTh << 0x10U) |
                            ((uint32_t)diffTh << 0x8U) |
                            (uint32_t)diffTh;

    int64_t    u64diffThPkd = _itoll(diffThPkd, diffThPkd);

    /* Fetch ring offsets based on pitch */
    fastCorners_make_offsets_9(offset, pitch);

    /* Set pixel center */
    ptrCenter = image + ((3U * pitch) + 3U);

    /* Case 1: SIMD of 16 pixels at a time */
    for( j = 0; j < (width/16U); j++ ) {

        uint32_t cornerWord, bitnum;

        centerVal76543210 = _mem8_const(ptrCenter);

        /* Boost (cur + th) value calculation for first
           8 pixels.
          */
        tempu32_1       = _saddu4(_loll(centerVal76543210), diffThPkd);
        tempu32_2       = _saddu4(_hill(centerVal76543210), diffThPkd);
        centerValBoost  = _itoll(tempu32_2, tempu32_1);

        /* Down (cur - th) value calculation for first
           8 pixels. Since there is no subtract and
           saturation instruction at 8 bit level, hence
           checking the saturation condition explicitly.
          */
        subMask         = ~(uint64_t)_dxpnd4(_dcmpgtu4(u64diffThPkd, centerVal76543210));
        tempu32_1       = (uint32_t)_sub4((int32_t)_loll(centerVal76543210), (int32_t)diffThPkd);
        tempu32_2       = (uint32_t)_sub4((int32_t)_hill(centerVal76543210), (int32_t)diffThPkd);
        centerValDown   = (uint64_t)_itoll(tempu32_2, tempu32_1) & subMask;


        centerVal76543210 = _mem8_const(ptrCenter + 8);
        /* Boost (cur + th) value calculation for next
           8 pixels.
          */
        tempu32_1         = _saddu4(_loll(centerVal76543210), diffThPkd);
        tempu32_2         = _saddu4(_hill(centerVal76543210), diffThPkd);
        centerValBoost_2  = _itoll(tempu32_2, tempu32_1);

        /* Down (cur - th) value calculation for next
           8 pixels.Since there is no subtract and
           saturation instruction at 8 bit level, hence
           checking the saturation condition explicitly.
          */
        subMask           = ~(uint64_t)_dxpnd4(_dcmpgtu4(u64diffThPkd, centerVal76543210));
        tempu32_1         = (uint32_t)_sub4((int32_t)_loll(centerVal76543210), (int32_t)diffThPkd);
        tempu32_2         = (uint32_t)_sub4((int32_t)_hill(centerVal76543210), (int32_t)diffThPkd);
        centerValDown_2   = (uint64_t)_itoll(tempu32_2, tempu32_1) & subMask;

        for( k = 0; k < NUM_PIXELS_IN_RING; k+= 2 ) {
            /* Even 'k' execution
               Compare kth pixel in ring with boost and down pixel
               threshold calculated just outside this loop
              */
            ringVal1   = _mem8_const(ptrCenter + offset[k]);
            ringVal2   = _mem8_const(ptrCenter + offset[k] + 8);

            tempu32_1  = _dcmpgtu4(ringVal1, centerValBoost);
            tempu32_3  = _dcmpgtu4(ringVal2, centerValBoost_2);
            tempu64_1  = _itoll(tempu32_3, tempu32_1);

            tempu32_2  = _dcmpgtu4((int64_t)centerValDown, ringVal1);
            tempu32_4  = _dcmpgtu4((int64_t)centerValDown_2, ringVal2);
            tempu64_2  = _itoll(tempu32_4, tempu32_2);

            tempu64_3   = _dpackl4(tempu64_2, tempu64_1);

            tempu32_1       = (uint32_t)_hill(tempu64_3) << 0x8U;
            _amem4(scratch) = tempu32_1 | (_loll(tempu64_3));

            scratch += 4;

            /* Odd 'k' execution
               Compare k+1th pixel in ring with boost and down pixel
               threshold calculated just outside this loop
              */
            ringVal1   = _mem8_const(ptrCenter + offset[k + 1]);
            ringVal2   = _mem8_const(ptrCenter + offset[k + 1] + 8);

            tempu32_1  = _dcmpgtu4(ringVal1, centerValBoost);
            tempu32_3  = _dcmpgtu4(ringVal2, centerValBoost_2);
            tempu64_1  = _itoll(tempu32_3, tempu32_1);

            tempu32_2  = _dcmpgtu4((int64_t)centerValDown, ringVal1);
            tempu32_4  = _dcmpgtu4((int64_t)centerValDown_2, ringVal2);
            tempu64_2  = _itoll(tempu32_4, tempu32_2);

            tempu64_3   = _dpackl4(tempu64_2, tempu64_1);

            tempu32_1       = (uint32_t)_hill(tempu64_3) << 0x8U;
            _amem4(scratch) = tempu32_1 | (_loll(tempu64_3));

            scratch += 4;
        }

        scratch = scratchBuffer;
        /* Lets assume ring pixels are indexed from 0-15. Ring vector is the
           16 pixels starting from each ring pixel. From previous loop
           for each ring vector "boost" and "down" binary result is stored
           in scratch buffer. In scratch buffer in every word (result vector)
           lower 16 bit is the binary result corresponding to "boost" checking,
           whereas higher 16 bit is the binary result corresponding to "down"
           checking.
           9 continuous ones are detected by doing logical AND of 9 result vectors.
           This result is logical ORed with final result of corners.In below loop
           logical AND of 8 result vector , in pair,is maintained as tempu32_1,
           tempu32_2, tempu32_3, tempu32_4.
           Every iteration of loop two pixels in rings are checked.
         */
        tempu64_1 = _amem8(scratch);
        tempu32_1 = _loll(tempu64_1) & _hill(tempu64_1);
        tempu64_2 = _amem8(scratch + 8);
        tempu32_2 = _loll(tempu64_2) & _hill(tempu64_2);
        tempu64_1 = _amem8(scratch + 16);
        tempu32_3 = _loll(tempu64_1) & _hill(tempu64_1);
        tempu64_2 = _amem8(scratch + 24);
        tempu32_4 = _loll(tempu64_2) & _hill(tempu64_2);
        cornerResult = 0x0;

        #pragma UNROLL(2)
        for( k = 0; k < NUM_PIXELS_IN_RING; k+=2 ) {
            tempu32_5 = tempu32_2 & (tempu32_3 & tempu32_4);

            backSingleResultVec = _amem4(scratch + (((uint32_t)k + 1U) * 4U));

            circIndex = ((uint8_t)k + 8U)  & 0xFU;
            fwDoubleResultVec = _amem8(scratch + (uint8_t)(circIndex << 2));

            cornerResult |= tempu32_5 &
                            (tempu32_1 &
                             _loll(fwDoubleResultVec));

            cornerResult |= tempu32_5 &
                            (_loll(fwDoubleResultVec) &
                             (_hill(fwDoubleResultVec) &
                     backSingleResultVec));

            tempu32_1 = tempu32_2;
            tempu32_2 = tempu32_3;
            tempu32_3 = tempu32_4;
            tempu32_4 = _loll(fwDoubleResultVec) & _hill(fwDoubleResultVec);
        }

        isCorner         = (uint16_t)(cornerResult | (cornerResult >> 0x10U));
        ptrCenter       += 16;

        cornerWord = _bitr((uint32_t)isCorner);
        bitnum = _lmbd(1U, cornerWord);

        while( bitnum < 32U) {
            if( (int32_t)n_featuresFound < features_capacity ) {
                x = (uint16_t)((j*16U)+bitnum+3U);
                y = startY + 3U;
                _amem4(&features[n_featuresFound]) = ((uint32_t)y << 16) | x;
            }
            n_featuresFound++;

            /* Mask out the bit we just checked */
            cornerWord &= ~((uint32_t)1<<(31U-bitnum));
            bitnum = _lmbd(1U, cornerWord);
        }
    }

    /* Case 2: Process remaining pixels beyond multiple of 16 */
    #pragma MUST_ITERATE(0, 15, 1)
    for( j*=16U; j < width; j++ ) {
        uint8_t centerVal = *ptrCenter;

        /* Boost (cur + th) value calculation */
        uint32_t centerValBoost_1 = _saddu4((uint32_t)centerVal, (uint32_t)differenceThreshold);
        uint32_t centerValBoost_x2 = ((centerValBoost_1 << 8) | centerValBoost_1);
        uint32_t centerValBoost_4 = _pack2(centerValBoost_x2, centerValBoost_x2);
        int64_t centerValBoost_8 = _itoll( centerValBoost_4, centerValBoost_4);

        /* Down (cur - th) value calculation */
        uint32_t centerValDown_1 = (differenceThreshold > centerVal) ? 0 : centerVal - differenceThreshold;
        uint32_t centerValDown_x2 = (centerValDown_1 << 8) | centerValDown_1;
        uint32_t centerValDown_4 = _pack2(centerValDown_x2, centerValDown_x2);
        int64_t centerValDown_8 = _itoll( centerValDown_4, centerValDown_4);

        uint32_t boostCmp=0, downCmp=0;

        /* Manually unroll loop to compare center pixel with ring pixels */
        {
            /* Compare first 8 pixels */
            uint16_t ringVal_0  = _mem2_const(&ptrCenter[offset[0]]);
            uint8_t ringVal_2   = ptrCenter[offset[2]];
            uint8_t ringVal_3   = ptrCenter[offset[3]];
            uint8_t ringVal_4   = ptrCenter[offset[4]];
            uint8_t ringVal_5   = ptrCenter[offset[5]];
            uint8_t ringVal_6   = ptrCenter[offset[6]];
            uint8_t ringVal_7   = ptrCenter[offset[7]];

            uint32_t ringVal10 = ringVal_0;
            uint32_t ringVal32 = ((uint32_t)ringVal_3 << 8) | ringVal_2;
            uint32_t ringVal3210 = _pack2(ringVal32, ringVal10);
            uint32_t ringVal54 = ((uint32_t)ringVal_5 << 8) | ringVal_4;
            uint32_t ringVal76 = ((uint32_t)ringVal_7 << 8) | ringVal_6;
            uint32_t ringVal7654 = _pack2(ringVal76, ringVal54);

            int64_t ringVal76543210 = _itoll(ringVal7654, ringVal3210);

            boostCmp = _dcmpgtu4(ringVal76543210, centerValBoost_8) << 8;
            downCmp  = _dcmpgtu4(centerValDown_8, ringVal76543210) << 8;

            /* Compare next 8 pixels */
            ringVal_0   = _mem2_const(&ptrCenter[offset[9]]);
            ringVal_2   = ptrCenter[offset[10]];
            ringVal_3   = ptrCenter[offset[11]];
            ringVal_4   = ptrCenter[offset[12]];
            ringVal_5   = ptrCenter[offset[13]];
            ringVal_6   = ptrCenter[offset[14]];
            ringVal_7   = ptrCenter[offset[15]];

            ringVal10 = _swap4((uint32_t)ringVal_0);
            ringVal32 = ((uint32_t)ringVal_3 << 8) | ringVal_2;
            ringVal3210 = _pack2(ringVal32, ringVal10);
            ringVal54 = ((uint32_t)ringVal_5 << 8) | ringVal_4;
            ringVal76 = ((uint32_t)ringVal_7 << 8) | ringVal_6;
            ringVal7654 = _pack2(ringVal76, ringVal54);
            
            ringVal76543210 = _itoll(ringVal7654, ringVal3210);

            boostCmp |= _dcmpgtu4(ringVal76543210, centerValBoost_8);
            downCmp  |= _dcmpgtu4(centerValDown_8, ringVal76543210);
        }

        boostCmp |= boostCmp<<16;
        downCmp  |= downCmp<<16;

        /* Shift and AND a total of 8 positions (using 4, 2, 1, 1 to eliminate all ones that are
         * not part of a contiguous 9 pixels) to find 9 contiguous 1s */
        boostCmp &= _rotl(boostCmp, 4U);
        downCmp  &= _rotl(downCmp, 4U);
        boostCmp &= _rotl(boostCmp, 2U);
        downCmp  &= _rotl(downCmp, 2U);
        boostCmp &= _rotl(boostCmp, 1U);
        downCmp  &= _rotl(downCmp, 1U);
        boostCmp &= _rotl(boostCmp, 1U);
        downCmp  &= _rotl(downCmp, 1U);

        /* Only write out the position of the feature if found */
        if( (boostCmp != 0) || (downCmp != 0) ) {
            if( (int32_t)n_featuresFound < features_capacity ) {
                x = (uint16_t)j + 3U;
                y = startY + 3U;
                _amem4(&features[n_featuresFound]) = ((uint32_t)y << 16) | x;
            }
            n_featuresFound++;
        }
        ptrCenter++;
    }

    return (n_featuresFound);
}

VXLIB_STATUS VXLIB_fastCornersDetect_i8u(const uint8_t src[],
                                      const VXLIB_bufParams2D_t *src_addr,
                                      uint32_t corners[],
                                      uint32_t corners_capacity,
                                      uint8_t strength_thresh,
                                      uint32_t *num_corners,
                                      uint8_t scratch[],
                                      uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_FASTCORNERSDETECT_I8U_CHECK_PARAMS)
    status = VXLIB_fastCornersDetect_i8u_checkParams(src, src_addr, corners, corners_capacity, strength_thresh, num_corners, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t   nCorners = 0;
        uint32_t   y;

        for( y=0; y < (src_addr->dim_y-6U); y++ ) {

            const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
            int32_t capacity = (int32_t)corners_capacity-(int32_t)nCorners; 

            nCorners += VXLIB_fastCornersDetect_i8u_core(src_t, src_addr->dim_x - 6U, src_addr->stride_y, (uint16_t)y,
                                                      strength_thresh, &corners[nCorners], capacity, scratch);

        }
        *num_corners = nCorners;
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_FASTCORNERSDETECT_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_FASTCORNERSDETECT_I8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_fastCornersDetect_i8u_checkParams(const uint8_t src[],
                                                  const VXLIB_bufParams2D_t *src_addr,
                                                  const uint32_t corners[],
                                                  uint32_t corners_capacity,
                                                  uint8_t strength_thresh,
                                                  const uint32_t *num_corners,
                                                  const uint8_t scratch[],
                                                  uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (corners == NULL) || (num_corners == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if(src_addr->data_type != VXLIB_UINT8) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if(scratch_size < 64U) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}
#endif
