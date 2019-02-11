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

#include "VXLIB_fastCornersNMS_i8u.h"

CODE_SECTION(VXLIB_fastCornersNMS_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_fastCornersNMS_i8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_fastCornersNMS_i8u_checkParams,  ".text:optimized")

static void VXLIB_fastCornersNMS_i8u_core(const uint8_t score[restrict],
                                        const uint32_t posyxPkd[restrict],
                                        uint8_t scoreOut[restrict],
                                        uint32_t posyxPkdOut[restrict],
                                        uint32_t inNumScores,
                                        uint16_t imgWidth,
                                        uint16_t imgHeight,
                                        uint32_t yScorePkd[restrict],
                                        uint8_t validIndex[restrict],
                                        uint32_t *outNumScores);


static void VXLIB_fastCornersNMS_i8u_core(const uint8_t score[restrict],
                                        const uint32_t posyxPkd[restrict],
                                        uint8_t scoreOut[restrict],
                                        uint32_t posyxPkdOut[restrict],
                                        uint32_t inNumScores,
                                        uint16_t imgWidth,
                                        uint16_t imgHeight,
                                        uint32_t yScorePkd[restrict],
                                        uint8_t validIndex[restrict],
                                        uint32_t *outNumScores)
{
    int32_t     i;
    uint32_t    curX, curY, prevX, prevY, absPosXDiff;
    int32_t     curIndex;
    uint32_t    supress, tempDecision;
    uint32_t    curScore;

    uint32_t    u32temp1, u32temp2;
    uint32_t    activeFeatureCnt   = 0x0;
    uint32_t    curYScorePkd, topYScorePkd, topLeftYScorePkd, topRightYScorePkd, tempYScorePkd, temp1YScorePkd;
    int64_t     u64temp1;

    prevX           = (uint32_t)imgWidth - 1U;
    prevY           = (uint32_t)imgHeight - 1U;
    tempYScorePkd   = 0;
    temp1YScorePkd  = 0;

    /* Go through full list, checking only top features and left feature, and labeling in scratch if suppress */
    for( curIndex = 0; curIndex < (int32_t)inNumScores; curIndex++ ) {

        /* Get current location and score */
        u32temp1 = _amem4_const(&posyxPkd[curIndex]);
        curX     = u32temp1 & 0xFFFFU;
        curY     = u32temp1 >> 0x10U;

        curScore = score[curIndex];

        /* Pack Y and score for comparing with surrounding pixels' Y and score */
        curYScorePkd =  (u32temp1 & 0xFFFF0000U) | curScore;

        /* Read TopLeft and Top packed words, and add 1 to the Y values */
        u64temp1              = _mem8(&yScorePkd[curX - 1U]);
        u64temp1              = _dadd2(u64temp1, 0x0001000000010000);

        /* If previous feature was the pixel to the left, then top-left memory in scratch
         * has already been over-written, so we need to check and take top from previous feature
         * instead of scratch if it is the case */
        if( (prevX == (curX - 1U)) && (prevY == curY) ) {
            /* Top from previous feature */
            topLeftYScorePkd = temp1YScorePkd + 0x00010000U;
        } else {
            /* Top left from scratch */
            topLeftYScorePkd = _loll(u64temp1);
        }

        /* Top from scratch */
        topYScorePkd          = _hill(u64temp1);

        /* Top right from scratch */
        u32temp2              = _amem4(yScorePkd + (curX + 1U));
        topRightYScorePkd     = u32temp2 + 0x00010000U;

        /* Check each of 3 top pixels */
        supress = 0x0;
        if(((curYScorePkd < topYScorePkd))) {
            supress = 0x1U;
        }
        if(((curYScorePkd < topLeftYScorePkd))) {
            supress = 0x1U;
        }
        if(((curYScorePkd < topRightYScorePkd))) {
            supress = 0x1U;
        }

        /* Check left pixel */
        if( curYScorePkd < tempYScorePkd ) {
            tempDecision = 0x1U;
        } else {
            tempDecision = 0x0;
        }
        absPosXDiff   = curX - prevX;

        if((tempDecision == 0x1U) && (absPosXDiff == 0x1U)) {
            supress = 0x1U;
        }

        /* probably temp1YScorePkd can become top-left */
        temp1YScorePkd      = yScorePkd[curX];

        /* probably tempYScorePkd can become left, top, top-right */
        tempYScorePkd       = curYScorePkd;
        yScorePkd[curX]     = curYScorePkd;

        prevX               = curX;
        prevY               = curY;

        /* Final suppression */
        if( supress != 0x0 ) {
            validIndex[curIndex] = 0x1U;
        }
    }

    /* Clear scratch memory for backward pass */
    /* Enforce scratch size for padding to multiple of 4 past width above because of this loop optimization */
    #pragma MUST_ITERATE(,,2)
    for( i=0; i < (((int32_t)imgWidth / 4) * 2); i++ ) {
        _amem8(yScorePkd + (2 * i)) = 0x0;
    }

    yScorePkd [imgWidth - 1U] = 0x0;

    prevX           = (uint32_t)imgWidth - 1U;
    prevY           = (uint32_t)imgHeight - 1U;
    tempYScorePkd   = 0;

    /* Go through full list backward, checking only bottom features and right feature, and labeling in scratch if suppress */
    for( curIndex = (int32_t)inNumScores - 1; curIndex >= 0; curIndex-- ) {

        /* Get current location and score */
        u32temp1 = _amem4_const(posyxPkd + curIndex);
        curX     = u32temp1 & 0xFFFFU;
        curY     = ((uint32_t)imgHeight - 0x1U) - (u32temp1 >> 0x10U);

        curScore = score[curIndex];

        /* Pack Y and score for comparing with surrounding pixels' Y and score */
        curYScorePkd =  (curY << 0x10U) | curScore;

        /* Read BottomLeft and Bottom packed words, and add 1 to the Y values */
        u64temp1              = _mem8(yScorePkd + (curX - 1U));
        u64temp1              = _dadd2(u64temp1, 0x0001000000010000);

        /* If previous feature was the pixel to the right, then bottom-right memory in scratch
         * has already been over-written, so we need to check and take bottom from previous feature
         * instead of scratch if it is the case */
        if( (prevX == (curX + 1U))  && (prevY == curY) ) {
            /* Bottom from previous feature */
            topLeftYScorePkd = temp1YScorePkd + 0x00010000U;
        } else {
            /* Top right from scratch */
            topLeftYScorePkd = _amem4(yScorePkd + (curX + 1U)) + 0x00010000U;
        }

        /* Bottom from scratch */
        topYScorePkd          = _hill(u64temp1);

        /* Bottom left from scratch */
        u32temp2              = _loll(u64temp1);
        topRightYScorePkd     = u32temp2;

        /* Check each of 3 bottom pixels */
        supress = 0x0;
        if(((curYScorePkd <= topYScorePkd))) {
            supress = 0x1U;
        }
        if(((curYScorePkd <= topLeftYScorePkd))) {
            supress = 0x1U;
        }
        if(((curYScorePkd <= topRightYScorePkd))) {
            supress = 0x1U;
        }

        /* Check right pixel */
        if( curYScorePkd <= tempYScorePkd ) {
            tempDecision = 0x1U;
        } else {
            tempDecision = 0x0;
        }
        absPosXDiff   = prevX - curX;

        if((tempDecision == 0x1U) && (absPosXDiff == 0x1U)) {
            supress = 0x1U;
        }

        /* probably temp1YScorePkd can become top-left */
        temp1YScorePkd      = yScorePkd[curX];

        /* probably tempYScorePkd can become left, top, top-right */
        tempYScorePkd       = curYScorePkd;

        yScorePkd[curX]     = curYScorePkd;

        prevX               = curX;
        prevY               = curY;

        /* Final suppression */
        if( supress != 0x0 ) {
            validIndex[curIndex] = 0x1U;
        }
    }

    /* Iterate through list, only writing out the maximal items */
    for( i = 0; (uint32_t)i < (inNumScores/4U); i++ ) {
        uint32_t valid4 = _amem4(&validIndex[i*4]);
        uint8_t k;
        #pragma MUST_ITERATE(4,4,4)
        for(k = 0; k < (uint8_t)4; k++) {
            if( (valid4 & 0xffU) == 0 ) {
                scoreOut[activeFeatureCnt]    = score[(i*4)+(int32_t)k];
                posyxPkdOut[activeFeatureCnt] = posyxPkd[(i*4)+(int32_t)k];
                activeFeatureCnt++;
            }
            valid4 >>= 8;
        }
    }
    for( i*=4; (uint32_t)i < inNumScores; i++ ) {
        if( validIndex[i] != 0x1U ) {
            scoreOut[activeFeatureCnt]    = score[i];
            posyxPkdOut[activeFeatureCnt] = posyxPkd[i];
            activeFeatureCnt++;
        }
    }
    *outNumScores = activeFeatureCnt;
}

VXLIB_STATUS VXLIB_fastCornersNMS_i8u(const VXLIB_bufParams2D_t * src_addr,
                                   const uint32_t corners_in[],
                                   const uint8_t strengths_in[],
                                   uint32_t num_corners_in,
                                   uint32_t corners_out[],
                                   uint8_t strengths_out[],
                                   uint32_t *num_corners_out,
                                   uint8_t scratch[],
                                   uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_FASTCORNERSNMS_I8U_CHECK_PARAMS)
    status = VXLIB_fastCornersNMS_i8u_checkParams(src_addr, corners_in, strengths_in, num_corners_in, corners_out, strengths_out, num_corners_out, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint8_t *validIndex = &scratch[(((4 * src_addr->dim_x) + 15) / 16) * 16];

        VXLIB_fastCornersNMS_i8u_core(strengths_in, corners_in, strengths_out, corners_out, num_corners_in,
                                   src_addr->dim_x, src_addr->dim_y, (uint32_t *)scratch, validIndex, num_corners_out);
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_FASTCORNERSNMS_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_FASTCORNERSNMS_I8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_fastCornersNMS_i8u_checkParams(const VXLIB_bufParams2D_t * src_addr,
                                               const uint32_t corners_in[],
                                               const uint8_t strengths_in[],
                                               uint32_t num_corners_in,
                                               const uint32_t corners_out[],
                                               const uint8_t strengths_out[],
                                               const uint32_t *num_corners_out,
                                               const uint8_t scratch[],
                                               uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((corners_in == NULL) || (strengths_in == NULL) || (corners_out == NULL) ||
       (strengths_out == NULL) || (num_corners_out == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if(scratch_size < ((4U * src_addr->dim_x) + num_corners_in + 15U) ) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else if( src_addr->data_type != VXLIB_UINT8 ) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}
#endif
