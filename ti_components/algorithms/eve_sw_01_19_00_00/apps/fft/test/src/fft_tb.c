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


/*==========================================================================*/
/**
 *  @file:      fft_tb.c
 *
 *  @brief:     This file contains test code for FFT applet
 *
 *
 *  @date:      March 2016
 *
 *  @description:
 *    This file contains test code to validate the frame level applet for
 *    FFT. It also checks the output against c reference
 *    outputs and profiles the performance and computes the system
 *    overheads.
 **/
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>
#include <math.h>
#pragma RESET_MISRA ("required")

#include "xdais_types.h"

#include "evestarterware.h"
#include "alg_osal.h"
#include "eve_profile.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"

#include "fft_config.h"
#include "ifft_ti.h"
#include "vcop_fft_npt_16ix16o_cn.h"
#include "vcop_fft_npt_16ix16o_32inter_cn.h"
#include "vcop_dcoffset_windowing_cn.h"

#if _DUMP
FILE *natcDumpFid;
#endif

#define ENABLE_TRACES     (0U)
#define ENABLE_PROFILE    (1U)
#define COMPARE_REFERENCE (1U)


#define MAX_CONFIG_LINE_SIZE     (300U)
#define MAX_FILE_NAME_SIZE       (200U)
#define MAX_PARAM_STRING_SIZE    (30U)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERROR_MSG() printf("Error at line: %5d in file: %22s of function: %s\n",__LINE__,__FILE__,__FUNCTION__)
#define ALIGN(x,y)        (((x + y - 1)/y)*y)
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

#define FIXED_PATTERN 0
#define SMALL_INPUT 0
#define DMEM_SIZE (16*1024U)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;


TIMemObject memObj_DMEM;

void fft32o_cn(IVISION_InBufs * inBufs,
            FFT_TI_CreateParams * createParams,
            FFT_TI_InArgs        * inArgs,
            FFT_TI_OutArgs       * outArgs,
            FFT_TI_OutArgs       * outArgsTarget,
            int32_t *outputDataPtr,
            FFT_TI_BufferDescriptor * outputBufDescriptor);

void* TestApp_AlignedMalloc(size_t required_bytes, size_t alignment)
{
    void* p1; // original block
    void** p2; // aligned block
    int offset = alignment - 1 + sizeof(void*);
    if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
    {
        return NULL;
    }
    p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void TestApp_AlignedFree(void *p)
{
    free(((void**)p)[-1]);
}


int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
    int32_t i;
    TIMemHandle memHdl_DMEM = &memObj_DMEM;
    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].space == IALG_DARAM0) {
            memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
        }
        else {
            memRec[i].base = (Void *) malloc( memRec[i].size);
        }
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
    }
    return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
    int32_t i;
    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
        if(memRec[i].space != IALG_DARAM0) {
            free(memRec[i].base);
        }
    }
    return IALG_EOK;
}

typedef struct IM_Fxns
{
    IVISION_Fxns * ivision;

} IM_Fxns;


char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
    {
        LinePtr++;
    }
    return(LinePtr);
}


#define MAX_NUM_POINTS (1024)
#define DCOFFSET_WINDOWING_SATURATION_LIMIT (16384U)

void memcpy2D(
        void        *dstPtr,
        const void  *srcPtr,
        uint16_t     width,
        uint16_t     height,
        int32_t      dstStride,
        int32_t      srcStride
)
{
    uint32_t rowCnt;

    for (rowCnt = 0 ; rowCnt < height; rowCnt++)
    {
        memcpy ((uint8_t *)dstPtr + rowCnt * dstStride, (uint8_t *)srcPtr + rowCnt * srcStride, width);
    }

    return;
}

typedef enum{
    DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION         = (uint32_t)1U << 0U,
    DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT = (uint32_t)1U << 1U,
    DCOFFSET_WINDOWING_ENABLE_DCOFFSET              = (uint32_t)1U << 2U,
    DCOFFSET_WINDOWING_ENABLE_WINDOWING             = (uint32_t)1U << 3U,
    DCOFFSET_WINDOWING_ENABLE_ALL                   = 0xFFFFU
}eBAM_DCOFFSET_WINDOWING_CONFIG;


void fft_cn(IVISION_InBufs * inBufs,
            FFT_TI_CreateParams * createParams,
            FFT_TI_InArgs        * inArgs,
            FFT_TI_OutArgs       * outArgs,
            FFT_TI_OutArgs       * outArgsTarget,
            int16_t *outputDataPtr,
            FFT_TI_BufferDescriptor * outputBufDescriptor)
{
    int16_t * pInput;
    int16_t * pOutput;
    int16_t * pTwiddleFactorBuf = NULL;
    int16_t * pWindowingOutputBuf = NULL;
    int16_t * pInterferenceOutBuf = NULL;
    int16_t * pDcOffsetBuf = NULL;
    int16_t * winCoefficientsBuf = NULL;
    int16_t * fftOutputBuf = NULL;
    int32_t * minMaxBuf = NULL;
    int32_t * scratchBufRef = NULL;
    int16_t * dopplerCorrectionBuf;
    uint32_t i;
    uint32_t twiddleFactorBufSize;
    uint32_t isWindowingRequired = 1;
    uint32_t chunkIdx, j, antennaIdx;
    int16_t * chunkBasePtr;
    int16_t * fftOutputBasePtr;
    uint32_t pitchInWords;
    uint32_t fftPitchRefOutput;
    uint32_t numPointsOffset;
    uint32_t windowingScaleFactor;
    uint32_t numPointFFTdirection;
    uint32_t numVertPointPreviousChunk;
    uint32_t numVertPointCurrChunk;
    uint32_t numActualPoints;
    uint32_t winOutputPitch;
    uint32_t configMask = 0;
    int16_t  *pSignExtOutput;
    int16_t  *pInterferenceIn;
    int16_t  *pInterferenceOut;
    int16_t  *pWindowingIn;
    uint16_t signExtOutPitch;
    uint16_t interferenceOutPitch;
    uint32_t       enableSignExtension;
    uint16_t saturationLimit;
    uint32_t overFlowMask;
    uint32_t maxNumBits;
    uint32_t numBits;
    uint32_t stageWithoutOverflow;
    uint32_t temp;
    uint16_t scaleFactorsIn[5];

    if ( createParams->fftDirection == FFT_TI_DIRECTION_HORIZONTAL)
    {
        numActualPoints = inArgs->bufDescription.numHorzPoints[0];
    }
    else
    {
        numActualPoints = inArgs->bufDescription.numVertPoints;
    }

    numPointFFTdirection = numActualPoints + inArgs->numPointsZeroPadding;

    winOutputPitch  = numPointFFTdirection * sizeof(int16_t)* 2;

    enableSignExtension = (inArgs->numValidBits == 16U )? 0 : 1;

    for ( chunkIdx = 0; chunkIdx < inArgs->bufDescription.numChunks; chunkIdx++)
    {
        pDcOffsetBuf = (int16_t *) malloc(inArgs->bufDescription.numVertPoints * sizeof(int16_t) * 2 * inArgs->bufDescription.numAntennas);
        winCoefficientsBuf = (int16_t *) malloc(numActualPoints * sizeof(int16_t));
        pWindowingOutputBuf = (int16_t *) malloc(MAX_NUM_POINTS * inArgs->bufDescription.numVertPoints *  sizeof(int16_t) *
                                                 inArgs->bufDescription.numAntennas * 2 );
        pInterferenceOutBuf = (int16_t *) malloc(MAX_NUM_POINTS * inArgs->bufDescription.numVertPoints *  sizeof(int16_t) *
                                                 inArgs->bufDescription.numAntennas * 2 );
        scratchBufRef   = (int32_t *)malloc(MAX_NUM_POINTS * sizeof(uint32_t) * 2);
        minMaxBuf  = (int32_t *) malloc(FFT_TI_MAX_NUM_STAGES * 2 *  sizeof(int32_t));

        for ( i = 0; i < 5; i++)
        {
            *(minMaxBuf + 2 * i) = 0x7FFFFFFF;
            *(minMaxBuf + 2 * i +1) = 0x80000000;
        }

        /* Remove pitch from the input data first */
        if ( createParams->fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
        {
            uint16_t antennaIdxTemp;
            uint16_t horzIdx;
            uint16_t vertIdx;
            uint16_t idx;
            uint32_t pitch1WordsIn;
            uint32_t pitch2WordsIn;
            uint32_t verticalJumpWordsIn;
            uint32_t pitch1WordsOut;
            uint32_t pitch2WordsOut;
            uint32_t verticalJumpWordsOut;

            pInput = (int16_t *)inBufs->bufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufPlanes[0].buf;

            if (inArgs->bufDescription.irregularityFrequency == 0 )
            {
                pitch1WordsIn = inArgs->bufDescription.offsetBwAntennas[0] / (sizeof(int16_t) * 2);
                pitch2WordsIn = pitch1WordsIn;

                pitch1WordsOut = inArgs->bufDescription.numHorzPoints[0];
                pitch2WordsOut = pitch1WordsOut;
            }
            else
            {
                pitch1WordsIn = inArgs->bufDescription.offsetBwAntennas[0] / (sizeof(int16_t) * 2);
                pitch2WordsIn = (inArgs->bufDescription.irregularityFrequency * inArgs->bufDescription.offsetBwAntennas[0] +
                        inArgs->bufDescription.offsetBwAntennas1[0]) / (sizeof(int16_t) * 2);

                pitch1WordsOut = inArgs->bufDescription.numHorzPoints[0];
                pitch2WordsOut = inArgs->bufDescription.numHorzPoints[0] * (inArgs->bufDescription.irregularityFrequency + 1);

            }
            verticalJumpWordsIn = pitch2WordsIn * (inArgs->bufDescription.numAntennas / (inArgs->bufDescription.irregularityFrequency + 1));
            verticalJumpWordsOut = pitch2WordsOut * (inArgs->bufDescription.numAntennas / (inArgs->bufDescription.irregularityFrequency + 1));



            {
                for ( vertIdx = 0; vertIdx < inArgs->bufDescription.numVertPoints;vertIdx++)
                {
                    for ( antennaIdxTemp = 0; antennaIdxTemp < (inArgs->bufDescription.numAntennas / (inArgs->bufDescription.irregularityFrequency + 1));antennaIdxTemp++)
                    {
                        for ( idx = 0; idx < (inArgs->bufDescription.irregularityFrequency + 1);idx++)
                        {
                            for ( horzIdx = 0; horzIdx < inArgs->bufDescription.numHorzPoints[0];horzIdx++)
                            {
                                pWindowingOutputBuf[ 2 * (horzIdx + idx * pitch1WordsOut + antennaIdxTemp * pitch2WordsOut + vertIdx * verticalJumpWordsOut)]=
                                        pInput[ 2 * (horzIdx + idx * pitch1WordsIn + antennaIdxTemp * pitch2WordsIn + vertIdx * verticalJumpWordsIn)] ;
                                pWindowingOutputBuf[ 2 * (horzIdx + idx * pitch1WordsOut + antennaIdxTemp * pitch2WordsOut + vertIdx * verticalJumpWordsOut) + 1]=
                                        pInput[ 2 * (horzIdx + idx * pitch1WordsIn + antennaIdxTemp * pitch2WordsIn + vertIdx * verticalJumpWordsIn) + 1] ;
                            }
                        }
                    }
                }

                memcpy(pInput,pWindowingOutputBuf, inArgs->bufDescription.numHorzPoints[0] *
                       inArgs->bufDescription.numAntennas *
                       inArgs->bufDescription.numVertPoints * sizeof(int16_t) * 2);
            }
        }
        if ( enableSignExtension)
        {
            configMask = DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION;
        }
        if ( inArgs->enableInterferenceZeroOut)
        {
            configMask |= DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT;
        }
        if ( inArgs->enableDcOffset)
        {
            configMask |= DCOFFSET_WINDOWING_ENABLE_DCOFFSET;
            configMask |= DCOFFSET_WINDOWING_ENABLE_WINDOWING;
        }
        if ( inArgs->enableWindowing)
        {
            configMask |= DCOFFSET_WINDOWING_ENABLE_WINDOWING;
        }

        if ( configMask == 0 )
        {
            configMask = DCOFFSET_WINDOWING_ENABLE_WINDOWING;
        }

        if ( chunkIdx == 0 )
        {
            pInput = (int16_t *)inBufs->bufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufPlanes[0].buf;
            pOutput = outputDataPtr;
        }
        else
        {
            numVertPointPreviousChunk = ((inArgs->bufDescription.numHorzPoints[chunkIdx - 1] * numPointFFTdirection) / outputBufDescriptor->numHorzPoints[0]);
            pInput = (int16_t *)((uint8_t *)pInput +
                    inArgs->bufDescription.pitch[chunkIdx - 1] * inArgs->bufDescription.numVertPoints);
            pOutput = (int16_t *)((uint8_t *)pOutput +
                    outputBufDescriptor->pitch[0] * numVertPointPreviousChunk);
        }

        /* Following are the possible configuration
      configMask   Windowing    DC Offset    InterferenceZeroOut   SignExtension
      0                0                        0                0                        0
      1                0                        0                0                        1
      2                0                        0                1                        0
      3                0                        0                1                        1
      4                0                        1                0                        0
      5                0                        1                0                        1
      6                0                        1                1                        0
      7                0                        1                1                        1
      8                1                        0                0                        0
      9                1                        0                0                        1
      10                1                        0                1                        0
      11                1                        0                1                        1
      12                1                        1                0                        0
      13                1                        1                0                        1
      14                1                        1                1                        0
      15                1                        1                1                        1

       Here 4,5,6,7 config is same as 12,13,14,15 as whenever DC offset is enabled
       windowing is automatically enabled
         */
        switch (configMask)
        {
        case 0 :
            pInterferenceIn      = pInput;
            pInterferenceOut     = pWindowingOutputBuf;
            interferenceOutPitch = winOutputPitch;
            break;
        case 1 :
            pSignExtOutput  = pWindowingOutputBuf;
            signExtOutPitch = winOutputPitch;
            break;
        case 2:
            pInterferenceIn      = pInput;
            pInterferenceOut     = pWindowingOutputBuf;
            interferenceOutPitch = winOutputPitch;
            break;
        case 3:
            pSignExtOutput  = pInterferenceOutBuf;
            signExtOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pInterferenceIn      = pSignExtOutput;
            pInterferenceOut     = pWindowingOutputBuf;
            interferenceOutPitch = winOutputPitch;
            break;
        case 8:
            pWindowingIn         = pInput;
            break;
        case 9 :
            pSignExtOutput  = pInterferenceOutBuf;
            signExtOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pWindowingIn         = pSignExtOutput;
            break;
        case 10 :
            pInterferenceIn      = pInput;
            pInterferenceOut     = pInterferenceOutBuf;
            interferenceOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pWindowingIn         = pInterferenceOut;
            break;
        case 11 :
            pSignExtOutput  = pWindowingOutputBuf;
            signExtOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pInterferenceIn      = pSignExtOutput;
            pInterferenceOut     = pInterferenceOutBuf;
            interferenceOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pWindowingIn         = pInterferenceOut;
            break;
        case 12 :
            pWindowingIn         = pInput;
            break;
        case 13:
            pSignExtOutput  = pInterferenceOutBuf;
            signExtOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pWindowingIn         = pSignExtOutput;
            break;
        case 14:
            pInterferenceIn      = pInput;
            pInterferenceOut     = pInterferenceOutBuf;
            interferenceOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pWindowingIn         = pInterferenceOut;
            break;
        case 15:
            pSignExtOutput  = pWindowingOutputBuf;
            signExtOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pInterferenceIn      = pSignExtOutput;
            pInterferenceOut     = pInterferenceOutBuf;
            interferenceOutPitch = numActualPoints * sizeof(int16_t) * 2U;

            pWindowingIn         = pInterferenceOut;
            break;
        default :
            break;
        }

        if (  inArgs->enableWindowing == 0 )
        {
            /* if windowing is disabled but DC offset is enable make all windowing coefficients as 1 */
            for ( i = 0; i < numActualPoints ; i++)
            {
                winCoefficientsBuf[i] = 1U;
            }
            windowingScaleFactor = 0;
        }
        else
        {
            /* Otherwise copy user provided buffer for windowcoefficients */
            memcpy(winCoefficientsBuf, inBufs->bufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF]->bufPlanes[0].buf,
                   sizeof(int16_t) * numActualPoints);
            windowingScaleFactor = inArgs->windowingScaleFactor;;
        }

        if (  inArgs->enableDcOffset == 0 )
        {
            /* if user disable DC offset initialize dc offset to be zero */
            memset (pDcOffsetBuf, 0 , inArgs->bufDescription.numVertPoints * sizeof(int32_t) * inArgs->bufDescription.numAntennas);
        }

        if ( configMask & DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION)
        {
            vcop_sign_extension_cn(
                    (uint16_t *)pInput,
                    pSignExtOutput,
                    inArgs->bufDescription.numHorzPoints[0],
                    inArgs->bufDescription.numVertPoints * inArgs->bufDescription.numAntennas,
                    signExtOutPitch,
                    inArgs->numValidBits
            );
            /* As sign extension is enabled hence windowing is not required untill unless user requests for  it */
            isWindowingRequired = 0;
        }

        if ( configMask & DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT)
        {
            vcop_interference_zero_out_cn(
                    pInterferenceIn,
                    pInterferenceOut,
                    inArgs->interferenceZeroOutThreshold,
                    inArgs->bufDescription.numHorzPoints[0],
                    inArgs->bufDescription.numVertPoints * inArgs->bufDescription.numAntennas,
                    interferenceOutPitch
            );

            isWindowingRequired  = 0;
        }

        if ( configMask & DCOFFSET_WINDOWING_ENABLE_DCOFFSET)
        {
            vcop_dcoffset_cn(
                    pWindowingIn,
                    pDcOffsetBuf,
                    inArgs->bufDescription.numHorzPoints[0],
                    inArgs->bufDescription.numVertPoints * inArgs->bufDescription.numAntennas);
        }

        /* this reserved entry is to remove the constraint the input to each stage of FFT is bound to 15 bits */
        /* User can switch to this mode if they want to utilize full 16 bit of data range. But this may result */
        /* in functionally incorrect results */
        if (inArgs->reserved == 0x5A716)
        {
            saturationLimit = 32768;
            maxNumBits = 16U;
        }
        else
        {
            saturationLimit = 16384;
            maxNumBits = 15U;
        }

        /* Windowing kernel does both substraction of dcOffset and windowing and hence if either of dcOffset or windowing is
    enabled we should call this function */
        if ( ( configMask & DCOFFSET_WINDOWING_ENABLE_WINDOWING) || isWindowingRequired)
        {
            if ( createParams->fftDirection == FFT_TI_DIRECTION_VERTICAL)
            {
                vcop_windowing_with_transpose_cn(
                        pWindowingIn,
                        winCoefficientsBuf,
                        pWindowingOutputBuf,
                        inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas,
                        inArgs->bufDescription.numVertPoints ,
                        windowingScaleFactor,
                        saturationLimit,
                        winOutputPitch);
            }
            else
            {
                vcop_windowing_cn(
                        pWindowingIn,
                        winCoefficientsBuf,
                        pDcOffsetBuf,
                        pWindowingOutputBuf,
                        inArgs->bufDescription.numHorzPoints[0],
                        inArgs->bufDescription.numVertPoints * inArgs->bufDescription.numAntennas,
                        windowingScaleFactor,
                        saturationLimit,
                        winOutputPitch);
            }
        }

        if ( pDcOffsetBuf)
        {
            free(pDcOffsetBuf);
            pDcOffsetBuf = NULL;
        }

        if ( pInterferenceOutBuf)
        {
            free(pInterferenceOutBuf);
            pInterferenceOutBuf = NULL;
        }

        if ( winCoefficientsBuf)
        {
            free(winCoefficientsBuf);
            winCoefficientsBuf = NULL;
        }

        fftOutputBuf = (int16_t *) malloc(MAX_NUM_POINTS * inArgs->bufDescription.numVertPoints *  sizeof(int16_t) *
                                          inArgs->bufDescription.numAntennas * 2 );

        dopplerCorrectionBuf = (int16_t *) malloc(numPointFFTdirection * sizeof(int16_t) * 2);

        pTwiddleFactorBuf = generateTwiddleFactor_ref(numPointFFTdirection , 0, &twiddleFactorBufSize);

        if ( inArgs->enableOverFlowDetection )
        {
            uint32_t numTempPoints;
            uint32_t numStages = 0;
            uint32_t bitGrowthLastStage;
            uint32_t bitGrowth;

            numTempPoints = numPointFFTdirection;

            while (numTempPoints != 0 )
            {
                numTempPoints = numTempPoints >> 2;
                numStages++;
                /* If last stage is radix 2 and its vertical direction FFT then we can use full 16 bit of data */
                if ( (numTempPoints == 2U) && ( createParams->fftDirection == FFT_TI_DIRECTION_VERTICAL ))
                {
                    bitGrowthLastStage = 1U;
                }
                else
                {
                    bitGrowthLastStage = 2U;
                }
                if ( numTempPoints == 1U)
                {
                    break;
                }
            }
            overFlowMask = 0x1FU;
            numBits = inArgs->inDataRange;
            stageWithoutOverflow = 0;
            bitGrowth = 2U;

            /* In case intermediate results are in 32-bits, the overflow detection and scales only applies to the last stage */
            if (inArgs->enable32bitsIntermResults== 1)
            {
                for ( i = 0; i < numStages; i++)
                {
                    scaleFactorsIn[i] = 0;
                }
                scaleFactorsIn[numStages-1]= outArgsTarget->scaleFactors[numStages-1];

                overFlowMask= (1<<(numStages-1));
            }
            else
            {
                for ( i = 0; i < numStages; i++)
                {
                    if ( i == (numStages -1U) )
                    {
                        bitGrowth = bitGrowthLastStage;
                    }
                    /* each stage there is bit growth of 2 bits except last stage where it could be by 1 */
                    if ( (numBits + bitGrowth) <= maxNumBits)
                    {
                        numBits += bitGrowth;
                        stageWithoutOverflow++;
                    }
                    else
                    {
                        break;
                    }
                }

                if ( stageWithoutOverflow == (numStages - 1U))
                {
                    stageWithoutOverflow++;
                }

                for ( i = 0; i <stageWithoutOverflow; i++)
                {
                    temp = ( 0x1U << i );
                    overFlowMask = (overFlowMask ^ temp);
                }
                for ( i = 0; i < FFT_TI_MAX_NUM_STAGES; i++)
                {
                    scaleFactorsIn[i] = outArgsTarget->scaleFactors[i];
                }
            }
        }
        else
        {
            overFlowMask = 0;
            for ( i = 0; i < FFT_TI_MAX_NUM_STAGES; i++)
            {
                scaleFactorsIn[i] = inArgs->scaleFactors[i];
            }
        }

        if ( createParams->fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
        {
            uint32_t chunkInnerIdx = 0;

            if ( inArgs->numPointsZeroPadding != 0 )
            {
                for (j = 0; j < inArgs->bufDescription.numVertPoints * inArgs->bufDescription.numAntennas; j++)
                {
                    for ( i = 0; i < inArgs->numPointsZeroPadding; i++)
                    {
                        (pWindowingOutputBuf + numActualPoints * 2)[2* (i + j * (winOutputPitch/ sizeof(uint32_t)))] = 0;
                        (pWindowingOutputBuf + numActualPoints * 2)[2* (i + j * (winOutputPitch/ sizeof(uint32_t))) + 1] = 0;
                    }
                }
            }


            for ( i = 0 ;i < inArgs->bufDescription.numVertPoints * inArgs->bufDescription.numAntennas; i++)
            {

                if (inArgs->enable32bitsIntermResults) {
                    vcop_fft_npt_32inter_mixed_radix_cn(pWindowingOutputBuf + i * numPointFFTdirection * 2,
                                                        pTwiddleFactorBuf,
                                                        scratchBufRef,
                                                        fftOutputBuf + i * numPointFFTdirection * 2,
                                                        scaleFactorsIn,
                                                        minMaxBuf,
                                                        numPointFFTdirection,
                                                        0,
                                                        saturationLimit,
                                                        overFlowMask);
                }
                else {
                    vcop_fft_npt_mixed_radix_cn(pWindowingOutputBuf + i * numPointFFTdirection * 2,
                                                pTwiddleFactorBuf,
                                                fftOutputBuf + i * numPointFFTdirection * 2,
                                                scaleFactorsIn,
                                                minMaxBuf,
                                                numPointFFTdirection,
                                                0,
                                                saturationLimit,
                                                overFlowMask
                    );
                }
            }


            fftPitchRefOutput = (numPointFFTdirection * inArgs->bufDescription.numAntennas * 2 * sizeof(int16_t) );

            /* rearrange final output to match target output format */
            numPointsOffset =0;

            for ( chunkInnerIdx = 0; chunkInnerIdx < outputBufDescriptor->numChunks; chunkInnerIdx++)
            {
                pitchInWords = (outputBufDescriptor->pitch[chunkInnerIdx]/ sizeof(int32_t));
                for ( antennaIdx = 0; antennaIdx < outputBufDescriptor->numAntennas; antennaIdx++)
                {

                    chunkBasePtr =(int16_t *)((int8_t *)pOutput + ((chunkInnerIdx * (outputBufDescriptor->pitch[chunkInnerIdx] *
                            outputBufDescriptor->numVertPoints)) +
                            (antennaIdx * outputBufDescriptor->numHorzPoints[chunkInnerIdx] * sizeof(int16_t) * 2)));/* Multiplication by 2 for real and imaginary data */

                    fftOutputBasePtr = ( fftOutputBuf + ((numPointsOffset * 2) +
                            (antennaIdx * numPointFFTdirection * 2 ) ));

                    for ( j = 0; j < outputBufDescriptor->numVertPoints; j++)
                    {
                        for ( i = 0; i < outputBufDescriptor->numHorzPoints[chunkInnerIdx]; i++)
                        {
                            chunkBasePtr[2 * ( j * pitchInWords + i )] =
                                    fftOutputBasePtr[2 * ( j * ( fftPitchRefOutput/sizeof(int32_t)) + i )];
                            chunkBasePtr[2 * ( j * pitchInWords + i ) + 1] =
                                    fftOutputBasePtr[2 * ( j * ( fftPitchRefOutput/sizeof(int32_t))+ i ) + 1];
                        }
                    }

                }
                /* Move the the offset for the next chunk */
                numPointsOffset += outputBufDescriptor->numHorzPoints[chunkInnerIdx];
            }

        }
        else
        {
            if ( inArgs->numPointsZeroPadding != 0 )
            {
                for (j = 0; j < inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas; j++)
                {
                    for ( i = 0; i < inArgs->numPointsZeroPadding; i++)
                    {
                        (pWindowingOutputBuf + numActualPoints * 2)[2* (i + j * (winOutputPitch/ sizeof(uint32_t)))] = 0;
                        (pWindowingOutputBuf + numActualPoints * 2)[2* (i + j * (winOutputPitch/ sizeof(uint32_t))) + 1] = 0;
                    }
                }
            }


            for ( i = 0 ;i < inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas; i++)
            {
                if (inArgs->enable32bitsIntermResults) {
                    vcop_fft_npt_32inter_mixed_radix_cn(pWindowingOutputBuf + i * numPointFFTdirection * 2,
                                                        pTwiddleFactorBuf,
                                                        scratchBufRef,
                                                        fftOutputBuf + i * numPointFFTdirection * 2,
                                                        scaleFactorsIn,
                                                        minMaxBuf,
                                                        numPointFFTdirection,
                                                        0,
                                                        saturationLimit,
                                                        overFlowMask);
                }
                else {
                    vcop_fft_npt_mixed_radix_cn(pWindowingOutputBuf + i * numPointFFTdirection * 2,
                                                pTwiddleFactorBuf,
                                                fftOutputBuf + i * numPointFFTdirection * 2,
                                                scaleFactorsIn,
                                                minMaxBuf,
                                                numPointFFTdirection,
                                                0,
                                                saturationLimit,
                                                overFlowMask
                    );
                }
            }

            if ( inArgs->enableDopplerCorrection == 1 )
            {
                memcpy(dopplerCorrectionBuf,
                       inBufs->bufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF]->bufPlanes[0].buf,
                       numPointFFTdirection * sizeof(int16_t) * 2);
            }
            else
            {
                /* if doppler correction is disabled and transpose is enable then set the coefficients to 1 */
                for ( i= 0; i < numPointFFTdirection ; i++)
                {
                    dopplerCorrectionBuf[2 * i]     = 1;
                    dopplerCorrectionBuf[2 * i + 1] = 0;
                }
            }

            for ( i = 0; i < inArgs->bufDescription.numAntennas; i++)
            {
                if ( inArgs->enableDopplerCorrection == 1 )
                {
                    memcpy(dopplerCorrectionBuf,
                           (uint8_t*)inBufs->bufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF]->bufPlanes[0].buf +
                           i * numPointFFTdirection * sizeof(int16_t) * 2,
                           numPointFFTdirection * sizeof(int16_t) * 2);
                }
                vcop_fft_doppler_correction_cn(fftOutputBuf + i * numPointFFTdirection * inArgs->bufDescription.numHorzPoints[chunkIdx] * 2,
                                               pOutput + i * inArgs->bufDescription.numHorzPoints[chunkIdx] * 2 ,
                                               dopplerCorrectionBuf,
                                               numPointFFTdirection,
                                               inArgs->bufDescription.numHorzPoints[chunkIdx],
                                               inArgs->dopplerCorrectionScaleFactor,
                                               inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas * sizeof(int16_t) * 2,
                                               saturationLimit);
            }

            memcpy(fftOutputBuf, pOutput, inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas *
                   sizeof(int16_t) * 2 * numPointFFTdirection);
            numVertPointCurrChunk = ((inArgs->bufDescription.numHorzPoints[chunkIdx] * numPointFFTdirection) /
                    outputBufDescriptor->numHorzPoints[0]);
            /* rearrange final output to match target output format */

            for ( antennaIdx = 0; antennaIdx < outputBufDescriptor->numAntennas; antennaIdx++)
            {

                chunkBasePtr =(int16_t *)((int8_t *) pOutput +  antennaIdx * outputBufDescriptor->offsetBwAntennas[0]);
                fftOutputBasePtr = (fftOutputBuf + antennaIdx * (inArgs->bufDescription.offsetBwAntennas[chunkIdx] / sizeof(int16_t)));

                for ( j = 0; j < (numVertPointCurrChunk/ numPointFFTdirection); j++)
                {
                    memcpy2D(chunkBasePtr + ( j * ( numPointFFTdirection * outputBufDescriptor->pitch[0] / sizeof(int16_t))),
                             fftOutputBasePtr + (j * outputBufDescriptor->numHorzPoints[0] * 2),
                             outputBufDescriptor->numHorzPoints[0] * sizeof(int16_t) * 2,
                             numPointFFTdirection,
                             outputBufDescriptor->pitch[0],
                             inArgs->bufDescription.pitch[chunkIdx]);
                }
            }
        }

        if ( inArgs->enableOverFlowDetection )
        {
            uint32_t  numStages;
            uint32_t  maxValue = 0x80000000;
            uint32_t numBits = 15U;
            uint32_t numTempPoints;
            uint16_t scaleFactor = 0;
            int32_t maxNBitValue;
            int32_t minNBitValue;
            numStages = 0;

            numTempPoints = numPointFFTdirection;

            while (numTempPoints != 0 )
            {
                numTempPoints = numTempPoints >> 2;
                numStages++;
                if ( numTempPoints == 1U)
                {
                    break;
                }
            }

            if (inArgs->reserved == 0x5A716)
            {
                numBits = 16;
            }
            maxNBitValue = (1<< (numBits- 1)) - 1;
            minNBitValue = -(1<< (numBits- 1));

            for ( i= 0; i < numStages; i++)
            {
                if ( overFlowMask & ( 0x1 << i))
                {
                    if ( (minMaxBuf[2*i] == minNBitValue) || (minMaxBuf[2*i + 1] == minNBitValue) )
                    {
                        maxValue = maxNBitValue;
                    }
                    else
                    {
                        maxValue = MAX(abs(minMaxBuf[2*i]) , abs(minMaxBuf[2*i + 1]) ) ;
                    }
                    scaleFactor = 0;
                    while(  (maxValue >> scaleFactor) > maxNBitValue )
                    {
                        scaleFactor++;
                    }
                    outArgs->scaleFactors[i]     = scaleFactor;
                }
                else
                {
                    outArgs->scaleFactors[i]     = 0;
                }
            }


        }

        if ( pTwiddleFactorBuf )
        {
            free(pTwiddleFactorBuf);
            pTwiddleFactorBuf = NULL;
        }
        if ( pWindowingOutputBuf)
        {
            free(pWindowingOutputBuf);
            pWindowingOutputBuf = NULL;
        }

        if (dopplerCorrectionBuf)
        {
            free(dopplerCorrectionBuf);
            dopplerCorrectionBuf = NULL;
        }

        if (scratchBufRef)
        {
            free(scratchBufRef);
            scratchBufRef= NULL;
        }

        if ( fftOutputBuf)
        {
            free(fftOutputBuf);
            fftOutputBuf = NULL;
        }
    }



}
void fillDefaultConfig(sFFT_Config* params)
{
    strcpy((char *)params->testCaseName, "FFT");
    strcpy((char *)params->inputData, "");
    strcpy((char *)params->outputData, "");
    strcpy((char *)params->desc, "");
    params->performanceTestcase = 1;

    params->numLines  = 128;
    params->numPoints = 512;
    params->outputContainerFormat= 0;
    params->enableDcoffset = 1;
    params->enableInterferenceZeroOut = 0;
    params->enableWindowing = 0;
    params->enable32bitsIntermResults= 0;
    params->dopplerCorrectionScaleFactor = 0;
    params->windowingScaleFactor = 0;

}


int32_t fftTest(sFFT_Config* params)
{
#if (ENABLE_PROFILE)
    uint64_t     profile_tsc, profile_sctm;
#endif
    int16_t     *inputData = NULL;
    int16_t     *outputData = NULL;
    int16_t     *refOutputData = NULL;
    int16_t     *winCoeffcients = NULL;
    int16_t     *dopplerCorrectionBuf = NULL;
    int32_t      i, j, numMemRec, status, fail = 0;
    uint32_t     outputElmtSize;
    TI_FILE     *fp;
    IALG_MemRec *memRec;
    char        *statusStr = NULL;

    /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
    IM_Fxns *    handle;

    /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
    FFT_TI_CreateParams   createParams;

    FFT_TI_InArgs  inArgs;
    FFT_TI_OutArgs outArgs;
    FFT_TI_OutArgs outArgsRef;

    IVISION_InBufs        inBufs;
    IVISION_OutBufs       outBufs;

    IVISION_BufDesc    inBufDesc[FFT_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *inBufDescList[FFT_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    outBufDesc[FFT_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *outBufDescList[FFT_TI_BUFDESC_OUT_TOTAL];

    int16_t * chunkBasePtrTarget;
    int16_t * chunkBasePtrRef;
    int32_t * chunkBasePtrTarget32;
    int32_t * chunkBasePtrRef32;
    uint32_t chunkIdx;
    uint32_t antennaIdx;
    uint32_t totalInputBufferSize;
    uint32_t totalOutputBufferSize;
    uint32_t numOtherPoints;
    uint32_t numFFTPoints;
    uint32_t numStages;
    uint32_t overflowDetected;

    outArgs.iVisionOutArgs.size = sizeof(FFT_TI_OutArgs);

    inArgs.iVisionInArgs.size   = sizeof(FFT_TI_InArgs);
    inArgs.iVisionInArgs.subFrameInfo = 0;

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t *pDmem;
    TIMemHandle memHdl_DMEM;

    pDmem = (uint8_t *)&DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;
    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if (ENABLE_PROFILE)
    profiler_init();
#endif

    /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs  = FFT_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs = FFT_TI_BUFDESC_OUT_TOTAL;

    for(i = 0 ; i < FFT_TI_BUFDESC_IN_TOTAL ;i++)
    {
        inBufDescList[i]  = &inBufDesc[i];
    }

    for(i = 0 ; i < FFT_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        outBufDescList[i] = &outBufDesc[i];
    }

    /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
    createParams.fftDirection = params->fftDirection;
    createParams.visionParams.algParams.size = sizeof(FFT_TI_CreateParams);
    createParams.visionParams.cacheWriteBack = NULL;
    createParams.inputContainerFormat= FFT_TI_CONTAINER_FORMAT_16BIT;
    createParams.outputContainerFormat= params->outputContainerFormat;

#if (ENABLE_PROFILE)
    profiler_initStack(profiler_getSP());
    profiler_start();
#endif

    /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
    numMemRec = FFT_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));

    status = FFT_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK) {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
    }

#if ENABLE_TRACES
    printf("FFT Applet Create Done\n");
#endif

    /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec, numMemRec);
    if(status != IALG_EOK) {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
    }

    /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
    status = FFT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                                             memRec,
                                             NULL,
                                             (IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
    profiler_end_print(0);
    /*  profile_create_tsc = gTest_TI_profileTsc;  */
#endif

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK) {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
    }

#if ENABLE_TRACES
    printf("FFT Applet Init Done\n");
#endif


    /*-----------------------------------------------------------------
  Set buffer descriptors
  -----------------------------------------------------------------*/
    /*-----------------------------------------------------------------
  Input buffer
  -----------------------------------------------------------------*/

    if ( createParams.fftDirection == FFT_TI_DIRECTION_HORIZONTAL)
    {
        numFFTPoints = params->numPoints;
        numOtherPoints = params->numLines;
    }
    else
    {
        numFFTPoints = params->numLines;
        numOtherPoints = params->numPoints;
    }

    if ( params->irregularityFrequency != 0 )
    {
        totalInputBufferSize = params->numChunks * ( params->irregularityFrequency * params->offsetBwAntenna + params->offsetBwAntenna1 ) *
                params->numLines * ( params->numAntennas / (params->irregularityFrequency + 1) );
    }
    else
    {
        if ( createParams.fftDirection == FFT_TI_DIRECTION_HORIZONTAL)
        {
            totalInputBufferSize   = params->numChunks * params->offsetBwAntenna * numOtherPoints * params->numAntennas;
        }
        else
        {
            totalInputBufferSize   = params->numChunks * params->offsetBwAntenna * numFFTPoints * params->numAntennas;
        }
    }



    inBufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER].bufPlanes[0].buf = TestApp_AlignedMalloc(totalInputBufferSize, 128);

    if ( params->enableWindowing)
    {
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].numPlanes = 1;
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].frameROI.width =
                numFFTPoints * sizeof(uint16_t);
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].frameROI.height = 1;
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].width  =
                numFFTPoints * sizeof(uint16_t);
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].height =
                inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].frameROI.height;
        inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].buf =
                TestApp_AlignedMalloc(inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].width *
                                      inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].bufPlanes[0].height, 128);
    }
    if ( params->enableDopplerCorrection)
    {
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].numPlanes = 1;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].frameROI.width =
                (numFFTPoints + params->numPointsZeroPadding) *
                params->numAntennas * sizeof(uint16_t) * 2;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].frameROI.height = 1;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].width  =
                (numFFTPoints + params->numPointsZeroPadding) *
                params->numAntennas * sizeof(uint16_t) * 2;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].height =
                inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].frameROI.height;
        inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].buf =
                TestApp_AlignedMalloc(inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].width *
                                      inBufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF].bufPlanes[0].height, 128);
    }

    inputData  = (int16_t *) inBufs.bufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufPlanes[0].buf;
    if ( params->enableWindowing )
    {
        winCoeffcients = (int16_t *)inBufs.bufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF]->bufPlanes[0].buf;
    }

    if ( params->enableDopplerCorrection)
    {
        dopplerCorrectionBuf = (int16_t *) inBufs.bufDesc[FFT_TI_BUFDESC_IN_DOPPLER_CORRECTION_BUF]->bufPlanes[0].buf;
    }



    /*-----------------------------------------------------------------
        Open Input File. If non existant, fill input with data.
        -----------------------------------------------------------------*/
    fp = FOPEN((char *)params->inputData, "rb");
    if(fp == NULL)
    {
        srand(params->randSeed);
#if 0
        pitchInHalfWords = (params->pitch/sizeof(int16_t));
        for(chunkIdx = 0; chunkIdx < params->numChunks; chunkIdx++)
        {
            chunkBasePtr = inputData + (pitchInHalfWords * params->numAntennas *
                    params->numLines * chunkIdx);
            for(j = 0; j < params->numLines; j++)
            {
                for(antennaIdx = 0; antennaIdx < params->numAntennas; antennaIdx++)
                {
                    for(i = 0; i < params->numPoints; i++)
                    {
#if FIXED_PATTERN
                        chunkBasePtr[(j * (pitchInHalfWords * params->numAntennas)) +
                                     (antennaIdx * pitchInHalfWords) +
                                     (i * 2)] = 8* i+j*14;
                        chunkBasePtr[(j * (pitchInHalfWords * params->numAntennas)) +
                                     (antennaIdx * pitchInHalfWords) +
                                     (i * 2) + 1] = 4*i - j*12;

#else
                        chunkBasePtr[(j * (pitchInHalfWords * params->numAntennas)) +
                                     (antennaIdx * pitchInHalfWords) +
                                     (i * 2)] = rand();
                        chunkBasePtr[(j * (pitchInHalfWords * params->numAntennas)) +
                                     (antennaIdx * pitchInHalfWords) +
                                     (i * 2) + 1] = rand();
#endif
                    }
                }
            }
        }
#else
        for ( i = 0; i< totalInputBufferSize / ( 2 *sizeof(int16_t)) ; i++)
        {
#if FIXED_PATTERN
            inputData[2*i] = i * 234 + i* 12 - (i %13) *1234;
            inputData[2*i + 1] = (i %25) * 765 + i* 3 - (i %25) * 124;
#else
#if SMALL_INPUT
            inputData[2*i]     = rand() % (1 << 5);
            inputData[2*i + 1] = rand() % (1 << 5);
#else
            inputData[2*i]     = rand() % (1 << params->inDataRange);
            inputData[2*i + 1] = rand() % (1 << params->inDataRange);
#endif
#endif
        }
#endif
    } else
    {
        FREAD(inputData, 1, totalInputBufferSize, fp);
        FCLOSE(fp);
    }

    if ( params->enableWindowing )
    {
        fp = FOPEN((char *)params->winCoefficients, "rb");
        if(fp == NULL)
        {
            srand(params->randSeed);
            for(j = 0; j < numFFTPoints; j++)
            {
                winCoeffcients[j] = rand();
            }
        } else
        {
            FREAD(winCoeffcients, 1, numFFTPoints * sizeof(uint16_t), fp);
            FCLOSE(fp);
        }
    }

    if ( params->enableDopplerCorrection)
    {
        fp = FOPEN((char *)params->dopplerCorrectionCoefficients, "rb");
        if(fp == NULL)
        {
            srand(params->randSeed);
            for(j = 0; j < (numFFTPoints + params->numPointsZeroPadding) * params->numAntennas; j++)
            {
                dopplerCorrectionBuf[2 * j] = rand();
                dopplerCorrectionBuf[2 * j + 1] = rand();
            }
        } else
        {
            FREAD(dopplerCorrectionBuf, 1, (numFFTPoints + params->numPointsZeroPadding)* params->numAntennas * 2 * sizeof(uint16_t), fp);
            FCLOSE(fp);
        }
    }

    if (params->outputContainerFormat== FFT_TI_CONTAINER_FORMAT_16BIT)
    {
        outputElmtSize= 4;
    }
    else if (params->outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT){
        outputElmtSize= 8;
    }

    if ( params->fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
    {
        inArgs.enableDcOffset               = params->enableDcoffset;
        inArgs.enableDopplerCorrection      = 0;
        inArgs.enableInterferenceZeroOut    = params->enableInterferenceZeroOut;
        inArgs.enableWindowing              = params->enableWindowing;
        inArgs.numValidBits                 = params->numValidBits;
        inArgs.interferenceZeroOutThreshold = params->interferenceThreshold;
        inArgs.windowingScaleFactor         = params->windowingScaleFactor;
        inArgs.dopplerCorrectionScaleFactor = params->dopplerCorrectionScaleFactor;
        inArgs.numPointsZeroPadding         = params->numPointsZeroPadding;
        inArgs.bufDescription.irregularityFrequency = params->irregularityFrequency;

        /* Describe the range FFT input buffer */
        inArgs.bufDescription.numChunks           = 1;
        inArgs.bufDescription.numHorzPoints[0]    = params->numPoints;
        inArgs.bufDescription.numVertPoints       = params->numLines;
        inArgs.bufDescription.numAntennas         = params->numAntennas;
        if ( params->irregularityFrequency == 0)
        {
            inArgs.bufDescription.pitch[0] = params->offsetBwAntenna * params->numAntennas;
        }
        else
        {
            inArgs.bufDescription.pitch[0] = ( params->irregularityFrequency * params->offsetBwAntenna + params->offsetBwAntenna1) *
                    ( params->numAntennas/ (params->irregularityFrequency + 1));

        }
        inArgs.bufDescription.offsetBwAntennas[0] = params->offsetBwAntenna;
        inArgs.bufDescription.offsetBwAntennas1[0] = params->offsetBwAntenna1;
        for ( i = 0; i < FFT_TI_MAX_NUM_STAGES; i++)
        {
            inArgs.scaleFactors[i]                 = params->scaleFactors[i];
        }
    }
    else if ( params->fftDirection == FFT_TI_DIRECTION_VERTICAL)
    {
        inArgs.enableDcOffset               = 0;
        inArgs.enableDopplerCorrection      = params->enableDopplerCorrection;
        inArgs.enableInterferenceZeroOut    = 0;
        inArgs.enableWindowing              = params->enableWindowing;
        inArgs.numValidBits                 = 16;
        inArgs.interferenceZeroOutThreshold = 0;
        inArgs.windowingScaleFactor         = params->windowingScaleFactor;
        inArgs.dopplerCorrectionScaleFactor = params->dopplerCorrectionScaleFactor;
        inArgs.numPointsZeroPadding         = params->numPointsZeroPadding;
        inArgs.bufDescription.irregularityFrequency = params->irregularityFrequency;

        /* Describe the range FFT input buffer */
        inArgs.bufDescription.numChunks           = params->numChunks;
        for ( i = 0 ; i < inArgs.bufDescription.numChunks; i++)
        {
            inArgs.bufDescription.numHorzPoints[i]    = params->numPoints;
            inArgs.bufDescription.numVertPoints       = params->numLines;
            inArgs.bufDescription.numAntennas         = params->numAntennas;
            inArgs.bufDescription.pitch[i]            = params->offsetBwAntenna * params->numAntennas;
            inArgs.bufDescription.offsetBwAntennas[i] = params->offsetBwAntenna;
        }

        for ( i = 0; i < FFT_TI_MAX_NUM_STAGES; i++)
        {
            inArgs.scaleFactors[i]                 = params->scaleFactors[i];
        }
    }


    inArgs.enable32bitsIntermResults= params->enable32bitsIntermResults;
    inArgs.enableOverFlowDetection = params->enableOverFlowDetection;
    inArgs.inDataRange             = params->inDataRange;

    if ( createParams.fftDirection ==  FFT_TI_DIRECTION_VERTICAL)
    {
        uint32_t outputPitch;
        /* Call the optional control call to get the parameters for output bufdescriptor */
        status = handle->ivision->algControl((IVISION_Handle)handle,
                                             FFT_TI_CONTROL_GET_OUTPUT_BUFDESCRIPTOR,
                                             (const IALG_Params *)&inArgs,
                                             (IALG_Params *)&outArgs.bufDescription);

        outBufDesc[FFT_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].width = params->dopplerOutputPitch;
        /*Set the output buffer descriptor pitch based on the control call */
        outputPitch = outArgs.bufDescription.pitch[0];
        if ( params->dopplerOutputPitch != 0 )
        {
            if ( params->dopplerOutputPitch >= outArgs.bufDescription.pitch[0])
            {
                outBufDesc[FFT_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].width = params->dopplerOutputPitch;
                outputPitch = params->dopplerOutputPitch;
            }
            else
            {
                fail = 1;
                PRINTF(" Pitch is less than minimum supported \n");
                goto Exit;
            }
        }
        else
        {
            outBufDesc[FFT_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].width = 0;
        }
        totalOutputBufferSize = outputPitch * outArgs.bufDescription.numVertPoints;

    }
    else
    {
        totalOutputBufferSize  = params->numChunks * (numFFTPoints + params->numPointsZeroPadding) * numOtherPoints * params->numAntennas * outputElmtSize;
        outBufDesc[FFT_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].width = 0;
    }
    /*-----------------------------------------------------------------
  Allocate Reference Buffers
  -----------------------------------------------------------------*/
    refOutputData = (int16_t *)malloc(totalOutputBufferSize);

    /*-----------------------------------------------------------------
  Output buffer
  -----------------------------------------------------------------*/
    outBufDesc[FFT_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].buf = TestApp_AlignedMalloc(totalOutputBufferSize, 128);

    outputData = (int16_t *)outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf;

    /*-----------------------------------------------------------------
        Fill Structuring Element buffer.
        -----------------------------------------------------------------*/

    /*-----------------------------------------------------------------
        Process.
        -----------------------------------------------------------------*/
#if ENABLE_TRACES
    printf("Processing start \n");
#endif
#if (ENABLE_PROFILE)
    profiler_start();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
                                         &inBufs,
                                         &outBufs,
                                         (IVISION_InArgs *)&inArgs,
                                         (IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
    profiler_end_print(1);

    profile_tsc  = gTest_TI_profileTsc;
    profile_sctm = gTest_TI_profileSctm[0];
#endif

    if(status != IALG_EOK) {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Processing End\n");
#endif

    /*-----------------------------------------------------------------
        Dump output image.
        -----------------------------------------------------------------*/
    fp = FOPEN((char *)params->outputData, "wb");

    if(fp != NULL)
    {
        FWRITE(outputData, 1,totalOutputBufferSize, fp);
        FCLOSE(fp);
    }


#if COMPARE_REFERENCE
    /*---------------------------------------------------------------------*/
    /*  Call the natural C implementation for  fft funcs.  */
    /*---------------------------------------------------------------------*/
    /* release input buffer used for target to free up some space */

    //inBufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER].bufPlanes[0].buf = inputDataRef;

    if (params->outputContainerFormat== FFT_TI_CONTAINER_FORMAT_32BIT) {
        fft32o_cn(&inBufs,
               &createParams,
               &inArgs,
               &outArgsRef,
               &outArgs,/*This is used to find if the target scaling factors are correct or not */
               (int32_t*)refOutputData,
               &outArgs.bufDescription); /* Reusing utArgs.bufDescription which is calculated inside
             the applet to avoid copying some code inside the applet */
        }
    else {
        fft_cn(&inBufs,
               &createParams,
               &inArgs,
               &outArgsRef,
               &outArgs,/*This is used to find if the target scaling factors are correct or not */
               refOutputData,
               &outArgs.bufDescription); /* Reusing utArgs.bufDescription which is calculated inside
             the applet to avoid copying some code inside the applet */
        }

    numStages = (log((double)(numFFTPoints + params->numPointsZeroPadding)) / log((double)4.0) ) + 0.5;

    overflowDetected = 0;

    if ( inArgs.enableOverFlowDetection == 1 )
    {
        for ( i = 0 ; i< numStages; i++)
        {
            if ( outArgs.scaleFactors[i] != 0 )
            {
                overflowDetected = 1;
                break;
            }
        }
    }

    fail = 0;

    printf("Overflow Detected %d \n", overflowDetected);
    if ( overflowDetected == 0 )
    {
        if (params->outputContainerFormat== FFT_TI_CONTAINER_FORMAT_16BIT)
        {
            for ( chunkIdx = 0; chunkIdx < outArgs.bufDescription.numChunks; chunkIdx++)
            {
                for ( antennaIdx = 0; antennaIdx < outArgs.bufDescription.numAntennas; antennaIdx++)
                {
                    chunkBasePtrTarget = (int16_t *)((int8_t *)outputData + ((chunkIdx * (outArgs.bufDescription.pitch[chunkIdx] *
                            outArgs.bufDescription.numVertPoints)) +
                            (antennaIdx * outArgs.bufDescription.numHorzPoints[chunkIdx] * sizeof(int16_t) * 2)));
                    chunkBasePtrRef    = (int16_t *)((int8_t *)refOutputData + ((chunkIdx * (outArgs.bufDescription.pitch[chunkIdx] *
                            outArgs.bufDescription.numVertPoints)) +
                            (antennaIdx * outArgs.bufDescription.numHorzPoints[chunkIdx] * sizeof(int16_t) * 2)));

                    for ( j = 0; j < outArgs.bufDescription.numVertPoints;j++)
                    {
                        for(i = 0; i < outArgs.bufDescription.numHorzPoints[chunkIdx];i++)
                        {

                            if ( (chunkBasePtrTarget[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/sizeof(int32_t)))] !=
                                    chunkBasePtrRef[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/sizeof(int32_t)))]) ||
                                    (chunkBasePtrTarget[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/sizeof(int32_t))) + 1] !=
                                            chunkBasePtrRef[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/sizeof(int32_t)))+ 1]))
                            {
                                fail = 1;
                                printf("FFT is not matching for Antenna %d at chunk %d line %d elem %d, offset %d bytes\n",antennaIdx, chunkIdx,  j, i, (chunkIdx*outArgs.bufDescription.numAntennas*outArgs.bufDescription.numVertPoints*outArgs.bufDescription.numHorzPoints[0] + antennaIdx * outArgs.bufDescription.numHorzPoints[chunkIdx] + j*outArgs.bufDescription.numHorzPoints[0] + i)*4);
                                goto Exit;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for ( chunkIdx = 0; chunkIdx < outArgs.bufDescription.numChunks; chunkIdx++)
            {
                for ( antennaIdx = 0; antennaIdx < outArgs.bufDescription.numAntennas; antennaIdx++)
                {
                    chunkBasePtrTarget32 = (int32_t *)((int8_t *)outputData + ((chunkIdx * (outArgs.bufDescription.pitch[chunkIdx] *
                            outArgs.bufDescription.numVertPoints)) +
                            (antennaIdx * outArgs.bufDescription.numHorzPoints[chunkIdx] * sizeof(int32_t) * 2)));
                    chunkBasePtrRef32    = (int32_t *)((int8_t *)refOutputData + ((chunkIdx * (outArgs.bufDescription.pitch[chunkIdx] *
                            outArgs.bufDescription.numVertPoints)) +
                            (antennaIdx * outArgs.bufDescription.numHorzPoints[chunkIdx] * sizeof(int32_t) * 2)));

                    for ( j = 0; j < outArgs.bufDescription.numVertPoints;j++)
                    {
                        for(i = 0; i < outArgs.bufDescription.numHorzPoints[chunkIdx];i++)
                        {

                            if ( (chunkBasePtrTarget32[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/(2*sizeof(int32_t))))] !=
                                    chunkBasePtrRef32[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/(2*sizeof(int32_t))))]) ||
                                    (chunkBasePtrTarget32[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/(2*sizeof(int32_t)))) + 1] !=
                                            chunkBasePtrRef32[2 *(i + j * (outArgs.bufDescription.pitch[chunkIdx]/(2*sizeof(int32_t))))+ 1]))
                            {
                                fail = 1;
                                printf("FFT is not matching for Antenna %d at chunk %d line %d elem %d, offset %d bytes\n",antennaIdx, chunkIdx,  j, i, (chunkIdx*outArgs.bufDescription.numAntennas*outArgs.bufDescription.numVertPoints*outArgs.bufDescription.numHorzPoints[0] + antennaIdx * outArgs.bufDescription.numHorzPoints[chunkIdx] + j*outArgs.bufDescription.numHorzPoints[0] + i)*8);
                                goto Exit;
                            }
                        }
                    }
                }
            }
        }
    }
    if ( overflowDetected == 1 )
    {
        for ( i = 0; i < numStages; i++)
        {
            if ( outArgs.scaleFactors[i] != outArgsRef.scaleFactors[i] )
            {
                fail |= 1;
                printf(" Scale factors are not matching for stage %d \n", i+1);
                goto Exit;
            }
        }
    }

    Exit:

#endif


    statusStr = fail ? "FAILED" : "PASSED";

    profiler_printStatus(fail);

#if (ENABLE_PROFILE)
    printf("\n%-30s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s\n", \
           "Algorithm", "Status", "Width", "Height", "NumAnetnnas", "VCOPCycPerFr", "MegaCycPerFr", \
           "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
#if (VCOP_HOST_EMULATION)
    profile_sctm = 1;
    profile_tsc = 1;
#endif
#if 1
    printf("%-30s %10s %10d %10d %10d %15lld %15.2f %20.2f %10.2f %16.2f  , overhead=%d%%\n",
           "FFT",
           statusStr,
           params->numPoints,
           params->numLines,
           params->numAntennas,
           profile_tsc,
           profile_tsc/1000000.0,
           30*(profile_tsc/1000000.0),
           profile_tsc/((float)params->numPoints * params->numLines * params->numAntennas * params->numChunks),
           profile_tsc/500000.0,
           ((profile_tsc - profile_sctm)*100)/profile_sctm);
#endif
#endif

    fflush(stdout);

    EXIT_LOOP:

    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);

    if(status != IALG_EOK) {
        PRINT_ERROR_MSG();
    }

    /* Here Free memory for all the mem records */
    status = TestApp_FreeMemRecords(memRec, numMemRec);
    if(status != IALG_EOK) {
        PRINT_ERROR_MSG();
    }

    if ( inputData != NULL ) {
        TestApp_AlignedFree(inputData);
    }

    if ( memRec != NULL ) {
        free(memRec);
    }

    if (outputData != NULL) {
        TestApp_AlignedFree(outputData);
    }
    if ( refOutputData != NULL ) {
        free(refOutputData);
    }
    if ( winCoeffcients != NULL ) {
        TestApp_AlignedFree(winCoeffcients);
    }


#if !(VCOP_HOST_EMULATION)
    profiler_getStackDepth();
#endif

    return status;
}


int main(int argc, char *argv[])
{
    TI_FILE *fp;
    char     configFile[FILE_NAME_SIZE] = {0};
    char     configLine[MAX_CONFIG_LINE_SIZE];
    char     configParam[MAX_PARAM_STRING_SIZE];
    int8_t  *LinePtr;
    int32_t  lineNum = -1, config_cmd, status = 0;

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
        strcpy(configFile,CONFIG_LIST_FILE_NAME);
    }

    fp = FOPEN((const char *)configFile , "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
        return(status);
    }

    report_printAppletInfo((int8_t *)"FFT_TI_VISION");

    while ( 1 )
    {
        memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
        status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = (int8_t *)configLine;
        if ((status == EOF) || (status == 0))
        {
            break;
        }
        status = 0;
        lineNum++;
        sscanf((const char *)LinePtr, "%d",&config_cmd);
        sscanf((const char *)LinePtr, "%s",configParam);

        if(config_cmd == 0)
        {
            printf("End of config list found !\n");
            break;
        }
        else if(config_cmd == 2)
        {
            continue;
        }
        else if(config_cmd == 1)
        {
            LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
            status  = sscanf((const char *)LinePtr, "%s",configFile);

            printf("\n Processing config file %s !\n", configFile);

            fillDefaultConfig(&gConfig_fft);

            status = readparamfile(configFile, &gsTokenMap_fft[0]);
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            profiler_testCaseInfo((int8_t *)gConfig_fft.testCaseName, (int8_t *)gConfig_fft.desc,
                                  gConfig_fft.performanceTestcase);
            printparams(&gsTokenMap_fft[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_fft),
                        sizeof(sFFT_Config));

            /* Validate the applet */
            status = fftTest(&gConfig_fft);
            if(status == -1)
            {
                return status;
            }
        }
        else
        {
            printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
        }

    }

    FCLOSE(fp);

#if VCOP_HOST_EMULATION
    printf("Press any key to continue ...\n");
    scanf("%c", configFile);
#endif

    return status;
}

