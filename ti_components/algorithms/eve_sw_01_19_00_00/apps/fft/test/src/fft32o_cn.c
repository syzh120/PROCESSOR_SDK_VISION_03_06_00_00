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
#include "vcop_fft_npt_16ix32o_cn.h"

#include "vcop_dcoffset_windowing_cn.h"

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

#define MAX_NUM_POINTS (1024)

typedef enum{
    DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION         = (uint32_t)1U << 0U,
    DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT = (uint32_t)1U << 1U,
    DCOFFSET_WINDOWING_ENABLE_DCOFFSET              = (uint32_t)1U << 2U,
    DCOFFSET_WINDOWING_ENABLE_WINDOWING             = (uint32_t)1U << 3U,
    DCOFFSET_WINDOWING_ENABLE_ALL                   = 0xFFFFU
}eBAM_DCOFFSET_WINDOWING_CONFIG;

static void memcpy2D(
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

void fft32o_cn(IVISION_InBufs * inBufs,
            FFT_TI_CreateParams * createParams,
            FFT_TI_InArgs        * inArgs,
            FFT_TI_OutArgs       * outArgs,
            FFT_TI_OutArgs       * outArgsTarget,
            int32_t *outputDataPtr,
            FFT_TI_BufferDescriptor * outputBufDescriptor)
{
    int16_t * pInput;
    int32_t * pOutput;
    int16_t * pTwiddleFactorBuf = NULL;
    int16_t * pWindowingOutputBuf = NULL;
    int16_t * pInterferenceOutBuf = NULL;
    int16_t * pDcOffsetBuf = NULL;
    int16_t * winCoefficientsBuf = NULL;
    int32_t * fftOutputBuf = NULL;
    int32_t * minMaxBuf = NULL;
    int32_t * scratchBufRef = NULL;
    int32_t * refOutputScratch32 = NULL;
    int16_t * dopplerCorrectionBuf;
    uint32_t i;
    uint32_t twiddleFactorBufSize;
    uint32_t isWindowingRequired = 1;
    uint32_t chunkIdx, j, antennaIdx;
    int32_t * chunkBasePtr;
    int32_t * fftOutputBasePtr;
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
        refOutputScratch32 = (int32_t *)malloc(MAX_NUM_POINTS * sizeof(uint32_t) * 2);
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
            pOutput = (int32_t *)((uint8_t *)pOutput +
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

        if ( createParams->fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
        {
            fftOutputBuf = (int32_t *) malloc(numPointFFTdirection * inArgs->bufDescription.numVertPoints *  sizeof(int32_t) *
                                              inArgs->bufDescription.numAntennas * 2 );
        }
        else
        {
            fftOutputBuf = (int32_t *) malloc(inArgs->bufDescription.numHorzPoints[0] * numPointFFTdirection *  sizeof(int32_t) *
                                              inArgs->bufDescription.numAntennas * 2 );
        }

        dopplerCorrectionBuf = (int16_t *) malloc(numPointFFTdirection * sizeof(int32_t) * 2);

        pTwiddleFactorBuf = generateTwiddleFactor_ref2(numPointFFTdirection , 0, &twiddleFactorBufSize);

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

                vcop_fft_npt_32o_mixed_radix_cn(pWindowingOutputBuf + i * numPointFFTdirection * 2,
                                            pTwiddleFactorBuf,
                                            scratchBufRef,
                                            refOutputScratch32,
                                            fftOutputBuf + i * numPointFFTdirection * 2,
                                            scaleFactorsIn,
                                            minMaxBuf,
                                            numPointFFTdirection,
                                            0,
                                            saturationLimit,
                                            overFlowMask);
            }


            fftPitchRefOutput = (numPointFFTdirection * inArgs->bufDescription.numAntennas * 2 * sizeof(int32_t) );

            /* rearrange final output to match target output format */
            numPointsOffset =0;

            for ( chunkInnerIdx = 0; chunkInnerIdx < outputBufDescriptor->numChunks; chunkInnerIdx++)
            {
                pitchInWords = (outputBufDescriptor->pitch[chunkInnerIdx]/(2*sizeof(int32_t)));
                for ( antennaIdx = 0; antennaIdx < outputBufDescriptor->numAntennas; antennaIdx++)
                {

                    chunkBasePtr =(int32_t *)((int8_t *)pOutput + ((chunkInnerIdx * (outputBufDescriptor->pitch[chunkInnerIdx] *
                            outputBufDescriptor->numVertPoints)) +
                            (antennaIdx * outputBufDescriptor->numHorzPoints[chunkInnerIdx] * sizeof(int32_t) * 2)));/* Multiplication by 2 for real and imaginary data */

                    fftOutputBasePtr = ( fftOutputBuf + ((numPointsOffset * 2) +
                            (antennaIdx * numPointFFTdirection * 2 ) ));

                    for ( j = 0; j < outputBufDescriptor->numVertPoints; j++)
                    {
                        for ( i = 0; i < outputBufDescriptor->numHorzPoints[chunkInnerIdx]; i++)
                        {
                            chunkBasePtr[2 * ( j * pitchInWords + i )] =
                                    fftOutputBasePtr[2 * ( j * ( fftPitchRefOutput/(2*sizeof(int32_t))) + i )];
                            chunkBasePtr[2 * ( j * pitchInWords + i ) + 1] =
                                    fftOutputBasePtr[2 * ( j * ( fftPitchRefOutput/(2*sizeof(int32_t)))+ i ) + 1];
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
                vcop_fft_npt_32o_mixed_radix_cn(pWindowingOutputBuf + i * numPointFFTdirection * 2,
                                pTwiddleFactorBuf,
                                scratchBufRef,
                                refOutputScratch32,
                                fftOutputBuf + i * numPointFFTdirection * 2,
                                scaleFactorsIn,
                                minMaxBuf,
                                numPointFFTdirection,
                                0,
                                saturationLimit,
                                overFlowMask);
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
                vcop_fft_doppler_correction_32ix32o_cn(fftOutputBuf + i * numPointFFTdirection * inArgs->bufDescription.numHorzPoints[chunkIdx] * 2,
                                               pOutput + i * inArgs->bufDescription.numHorzPoints[chunkIdx] * 2 ,
                                               dopplerCorrectionBuf,
                                               numPointFFTdirection,
                                               inArgs->bufDescription.numHorzPoints[chunkIdx],
                                               inArgs->dopplerCorrectionScaleFactor,
                                               inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas * sizeof(int32_t) * 2,
                                               saturationLimit);
            }

            memcpy(fftOutputBuf, pOutput, inArgs->bufDescription.numHorzPoints[chunkIdx] * inArgs->bufDescription.numAntennas *
                   sizeof(int32_t) * 2 * numPointFFTdirection);
            numVertPointCurrChunk = ((inArgs->bufDescription.numHorzPoints[chunkIdx] * numPointFFTdirection) /
                    outputBufDescriptor->numHorzPoints[0]);
            /* rearrange final output to match target output format */

            for ( antennaIdx = 0; antennaIdx < outputBufDescriptor->numAntennas; antennaIdx++)
            {

                chunkBasePtr =(int32_t *)((int8_t *) pOutput +  antennaIdx * outputBufDescriptor->offsetBwAntennas[0]);
                fftOutputBasePtr = (fftOutputBuf + antennaIdx * (inArgs->bufDescription.offsetBwAntennas[chunkIdx] / (sizeof(int16_t))));

                for ( j = 0; j < (numVertPointCurrChunk/ numPointFFTdirection); j++)
                {
                    memcpy2D(chunkBasePtr + ( j * ( numPointFFTdirection * outputBufDescriptor->pitch[0] / (sizeof(int32_t)))),
                             fftOutputBasePtr + (j * outputBufDescriptor->numHorzPoints[0] * 2),
                             outputBufDescriptor->numHorzPoints[0] * sizeof(int32_t) * 2,
                             numPointFFTdirection,
                             outputBufDescriptor->pitch[0],
                             2*inArgs->bufDescription.pitch[chunkIdx]);
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

            i = numStages - 1;
            for ( i= 0; i < numStages; i++)
            {
            outArgs->scaleFactors[i]     = 0;
            }

            i= numStages - 1;
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

        if (refOutputScratch32) {
            free(refOutputScratch32);
            refOutputScratch32= NULL;
        }

        if ( fftOutputBuf)
        {
            free(fftOutputBuf);
            fftOutputBuf = NULL;
        }

    }

}

