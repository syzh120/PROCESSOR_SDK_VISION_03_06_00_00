/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/* -------------------------------------------------------------------- */
/* NAME : evelib_harris_corner_detection.c                              */
/*                                                                      */
/* DESCRIPTION:                                                         */
/*                                                                      */
/* This file contains an Harris corner detection implementaion          */
/*                                                                      */
/* Author: Venkat Peddigari <venkatrpeddigari@ti.com>                   */
/* -------------------------------------------------------------------- */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <vcop/vcop.h>
#include "common/eve_algo_dma_auto_incr.h"
#include "evelib_harris_corner_detection.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"
#include "vcop_harrisScore_7x7_kernel.h"
#include "vcop_nonMaxSuppress_mxn_16s_kernel.h"

#define NOT_MXN_NMS (0)

static unsigned int vcop_harrisCornerDetection_init
(
uint8_t  *pIn,
uint32_t  inCols,
uint32_t  inRows,
uint8_t  *pOut,
int8_t   *pTmp,
uint16_t *pBlockGradient,
uint16_t *pBlockHarrisScore_1,
uint16_t *pBlockHarrisScore_2,
uint16_t *pBlockNonMaxSuppress_7x7_16s,
int16_t   inHarrisScoreScaling,
int16_t   inNMSThresh
);

int vcop_harrisScore_7x7_init
(
    short *  gradX,
    short *  gradY,
    int width,
    int height,
    unsigned int srcPitch,
    unsigned int dstPitch,
    short *  outm,
    short k,
    int * XX,
    int * YY,
    int * XY,
    unsigned int * detL,
    int * detH,
    uint16_t *pBlockHarrisScore_1,
    uint16_t *pBlockHarrisScore_2
)
{
   unsigned int cnt1 = 0;
   unsigned int cnt2 = 0;
   unsigned int retVal = 0;
   char *pIn1 = (char *) (XX);
   char *pIn2 = (char *) (YY);
   char *pIn3 = (char *) (XY);

    cnt1 = vcop_harrisScore_7x7_1_init(
                gradX,
                gradY,
                width,
                height,
                srcPitch,
                dstPitch,
                XX,
                YY,
                XY,
                pBlockHarrisScore_1);

    cnt2 = vcop_harrisScore_7x7_2_init(
                width-6,
                height-6,
                dstPitch,
                dstPitch,
                outm,
                k,
                XX,
                YY,
                XY,
                (unsigned short *) (pIn1),
                (unsigned short *) (pIn2),
                (unsigned short *) (pIn3),
                (short *)          (pIn1 + 2),
                (short *)          (pIn2 + 2),
                (short *)          (pIn3 + 2),
                detL,
                detH,
                pBlockHarrisScore_2);

    retVal = cnt1 + cnt2;

  return retVal;
}


/**
*  @brief      Compute corners for a given grayscale image using
*              Shi & Tomasi corner detector which is based Harris
*              Corner Detection algorithm
*
*  @param[in]  src                        source image pointer
*  @param[in]  srcImageWidth              source image width in pixels
*  @param[in]  srcImageHeight             source image height in pixels
*  @param[in]  srcBufferPitch             source buffer pitch in bytes
*  @param[in]  srcBufferHeight            source buffer height in bytes
*  @param[in]  srcBytesPP                 source bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[out] dst                        destimation image pointer
*  @param[in]  dstImageWidth              destination image width in pixels
*  @param[in]  dstImageHeight             destination image height in pixels
*  @param[in]  dstBufferPitch             destination buffer pitch in bytes
*  @param[in]  dstBufferHeight            destination buffer height in bytes
*  @param[in]  dstBytesPP                 dest bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[in]  harrisScoreScalingFactor   scaling factor used by harris score kernel
*  @param[in]  nmsThresh                  threshold parameter for non maximum suppression kernel
*
*  @remarks    Harris corner detector function.
*  @remarks    Currently, the algorithm works fine when srcImageWidth*srcBytesPP or srcImagePitch is a multiple of 16.
*  @remarks    Further investigation is required to extend support for multiple of 32.
*
*  @sa         EVELIB_algoDMAAutoIncrInit(), EVELIB_algoDMAAutoIncrProcess(), EVELIB_algoDMAAutoIncrDeInit()
*/
void EVELIB_harrisCornerDetection(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcBufferPitch,
    int                 srcBufferHeight,
    unsigned int        srcBytesPP,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstBufferPitch,
    int                 dstBufferHeight,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    unsigned int        dstBytesPP,
    short               harrisScoreScalingFactor,
    short               nmsThresh
    )
{
    uint8_t *srcBlk;
    uint8_t *dstBlk;
    int8_t *scratch_data;

    uint32_t srcBlkPadX = 16;
    uint32_t srcBlkPadY = 16;

    uint32_t dstImageWidthBytes = dstImageWidth * dstBytesPP; //convert to bytes

    //uint32_t srcBlkWidth = 16;
    //uint32_t srcBlkHeight= 16;

    uint32_t srcProcWidth = srcBufferPitch;
    uint32_t srcProcHeight= srcBufferHeight;

    uint32_t srcBlkPitch = (srcBlkWidth+srcBlkPadX);
    uint32_t srcBlkHeightTot = (srcBlkHeight+srcBlkPadY);

    uint32_t dstBlkWidth  = (srcBlkWidth);
    uint32_t dstBlkHeight = (srcBlkHeight);
    //uint32_t dstBlkPitch  = (srcBlkPitch);
    uint32_t dstBlkPitch  = (dstBlkWidth);


    EVELIB_KernelFuncType execFunc[] = {
            (EVELIB_KernelFuncType)vcop_vec_gradients_xy_and_magnitude_vloops,
            (EVELIB_KernelFuncType)vcop_harrisScore_7x7_1_vloops,
            (EVELIB_KernelFuncType)vcop_harrisScore_7x7_2_vloops,
#if NOT_MXN_NMS
            (EVELIB_KernelFuncType)vcop_nonMaxSuppress_7x7_16s_vloops
#else
            (EVELIB_KernelFuncType)vcop_nonMaxSuppress_mxn_16s_vloops
#endif
    };

    EVELIB_KernelContextType context[] = {
        (EVELIB_KernelContextType)__pblock_vcop_vec_gradients_xy_and_magnitude,
        (EVELIB_KernelContextType)__pblock_vcop_harrisScore_7x7_1,
        (EVELIB_KernelContextType)__pblock_vcop_harrisScore_7x7_2,
#if NOT_MXN_NMS
        (EVELIB_KernelContextType)__pblock_vcop_nonMaxSuppress_7x7_16s
#else
        (EVELIB_KernelContextType)__pblock_vcop_nonMaxSuppress_mxn_16s
#endif
    };
    unsigned int numKernels = 4;

    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    srcBlk = (unsigned char *)vcop_malloc(VCOP_IBUFLA, 15*1024);
    dstBlk = (unsigned char *)vcop_malloc(VCOP_IBUFHA, 15*1024);
    scratch_data = (int8_t *)vcop_malloc(VCOP_WMEM,    15*1024);

    vcop_harrisCornerDetection_init(srcBlk, srcBlkPitch,
        srcBlkHeightTot, dstBlk, scratch_data,
        __pblock_vcop_vec_gradients_xy_and_magnitude,
        __pblock_vcop_harrisScore_7x7_1,
        __pblock_vcop_harrisScore_7x7_2,
#if NOT_MXN_NMS
        __pblock_vcop_nonMaxSuppress_7x7_16s,
#else
        __pblock_vcop_nonMaxSuppress_mxn_16s,
#endif
        harrisScoreScalingFactor,
        nmsThresh);

    EVELIB_algoDMAAutoIncrInit(
        src,
        srcProcWidth,
        srcProcHeight,
        srcBufferPitch,
        dst+(((srcBlkPadY/2)-1)*dstImageWidth)+((srcBlkPadX/2) - 1),
        dstImageWidthBytes,
        dstImageHeight,
        dstBufferPitch,
        srcBlk,
        srcBlkWidth,
        srcBlkHeight,
        srcBlkPitch,
        //dstBlk+((srcBlkPadY/2)*(srcBlkPitch)+(srcBlkPadX/2)-1),
        dstBlk,
        dstBlkWidth,
        dstBlkHeight,
        dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY);

    EVELIB_algoDMAAutoIncrProcess(
        src,
        srcProcWidth,
        srcProcHeight,
        srcBufferPitch,
        dst+(((srcBlkPadY/2)-1)*dstImageWidth)+((srcBlkPadX/2) - 1),
        dstImageWidthBytes,
        dstImageHeight,
        dstBufferPitch,
        srcBlk,
        srcBlkWidth,
        srcBlkHeight,
        srcBlkPitch,
        dstBlk,
        dstBlkWidth,
        dstBlkHeight,
        dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY,
        execFunc,
        context,
        numKernels,
        0);

    EVELIB_algoDMAAutoIncrDeInit();


    vcop_free(srcBlk);
    vcop_free(dstBlk);
    vcop_free(scratch_data);
}

static unsigned int vcop_harrisCornerDetection_init
(
uint8_t  *pIn,
uint32_t  inCols,
uint32_t  inRows,
uint8_t  *pOut,
int8_t   *pTmp,
uint16_t *pBlockGradient,
uint16_t *pBlockHarrisScore_1,
uint16_t *pBlockHarrisScore_2,
uint16_t *pBlockNonMaxSuppress_7x7_16s,
int16_t   inHarrisScoreScaling,
int16_t   inNMSThresh
)
{
  unsigned int cnt = 0;

  cnt += vcop_vec_gradients_xy_and_magnitude_init(
              pIn,
              (int16_t *) (pTmp),
              (int16_t *) (pOut),
              (int16_t *) (pTmp + 2 * inCols * inRows),
              (uint16_t ) inCols,
              (uint16_t ) (inCols - 2),
              (uint16_t ) (inRows - 2),
              pBlockGradient);

  cnt += vcop_harrisScore_7x7_init(
              (int16_t *) pTmp,
              (int16_t *) (pOut),
              (inCols-8+6),
              (inRows-8+6),
              inCols-2,
              inCols-8,
              (int16_t *) (pIn),
              inHarrisScoreScaling,
              (int32_t *)(pIn),
              (int32_t *)(pTmp  + 4 * (inCols-8) * (inRows-8)),
              (int32_t *)(pOut  + 4 * (inCols-8) * (inRows-8)),
              (uint32_t *)(pTmp),
              (int32_t *)(pOut),
              pBlockHarrisScore_1,
              pBlockHarrisScore_2);

#if NOT_MXN_NMS
  cnt += vcop_nonMaxSuppress_7x7_16s_init(
              (uint16_t *)(pTmp),
              pOut,
              (uint16_t *)(pIn),
              (uint16_t *)(pOut + 1 * inCols * inRows),
              (inCols -16 + 6),
              (inRows -16 + 6),
	            (inCols-8),
	            (inCols-16),
              inNMSThresh,
              pBlockNonMaxSuppress_7x7_16s);

#else
  cnt += vcop_nonMaxSuppress_mxn_16s_init(
              (uint16_t *)(pIn),
              pOut,
              (uint16_t *)(pTmp),
              (uint16_t *)(pTmp  + 2 * (inCols-8) * (inRows-8)),
              (inCols -16 + 6),
              (inRows -16 + 6),
	            (inCols-8),
	            (inCols-16),
              7,
              7,
              inNMSThresh,
              pBlockNonMaxSuppress_7x7_16s);


#endif

  return cnt;
}
