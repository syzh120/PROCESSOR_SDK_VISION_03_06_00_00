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


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_fft_npt_16ix32o_config.h"
#include "vcop_fft_npt_16ix32o_wrapper.h"
#include "../../vcop_fft_npt_16ix16o/inc/vcop_fft_npt_16ix16o_gen_twiddleFactor.h"

#include "vcop_fft_npt_16ix32o_cn.h"

#if _DUMP
FILE *natcDumpFid;
#endif

#if (!VCOP_HOST_EMULATION)
#include "../inc/vcop_fft_doppler_correction_kernel.h"
#else
#include "../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_doppler_correction_kernel.k"
#endif

#define FIXED_PATTERN 0

#define SPLIT_VLOOPS_INIT 0

#if VCOP_HOST_EMULATION
#define SPLIT_VLOOPS_INIT 0
#endif
/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of SOFT ISP functions      */
/* ------------------------------------------------------------------------ */
#include "vcop_fft_npt_16ix32o_cn.h"

//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define TRANSPOSE_STRIDE          ((VCOP_SIMD_WIDTH + 1 ) * 4 )

#if (VCOP_HOST_EMULATION)
#define FFT_TEST_malloc(heap, size)   malloc(size)
#define FFT_TEST_free(ptr)            free(ptr)
#else
#define FFT_TEST_malloc(heap, size)   (vcop_malloc((heap), (size)))
#define FFT_TEST_free(ptr)            (vcop_free(ptr))
#endif


#define MIN(a,b) ((a) < (b) ? (a) : (b)) ;
#define MAX(a, b) ((a) > (b) ? (a) : (b));

void createRndPattern(uint8_t * image,
                      uint32_t width,
                      uint32_t height,
                      uint32_t pitch

)
{
    int32_t i, j;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            image[i * pitch + j] = rand() % (255);
        }
    }
}

void fillDefaultConfig(sFFT_np_16ix16tx32o_Config * params)
{
    strcpy(params->inputData, "");
    strcpy(params->outputData, "");
    params->numPoints = 512;
    params->numLines  = 1;
    params->scaleFactor[0] = 0;
    params->scaleFactor[1] = 0;
    params->scaleFactor[2] = 0;
    params->scaleFactor[3] = 0;
    params->scaleFactor[4] = 0;
    params->randSeed    = 0;

}

int32_t fftTest(sFFT_np_16ix16tx32o_Config * testcaseParams)
{
    int32_t fail, status = 0;
    uint32_t seed;
    FILE *fp_in = NULL;
    int32_t i,j;
    int16_t * twiddleFactorBuf = NULL;
    int16_t * twiddleFactorBufExt = NULL;
    //int16_t * pDopplerCorrectionBuf = NULL;
    int32_t * refOutputData32 = NULL;
    int32_t * refOutputScratch32 = NULL;

    int16_t * pInputDataWbuf = NULL;
    int16_t * pScratchIBufL  = NULL;
    int16_t * pScratchIBufH  = NULL;
    uint8_t * pScaleFactorOut = NULL;

    int16_t * inputDataRef = NULL;
    int32_t * scratchBufRef= NULL;
    char    testcaseName[100];
    uint16_t * pScatterOffset;


    uint16_t numOfLines;
    uint16_t inputDataOffst16 = 0;
    uint32_t sizeofTwiddleFactorBuf = 0;
    uint32_t transposeStride;
    uint32_t  overflowMask = 0;
    int32_t * pMinMaxRef = NULL;
    uint16_t saturationLimit;
    uint32_t isOverflowDetected = 0;

#if SPLIT_VLOOPS_INIT
    uint16_t * pBlockMemoryFFT = NULL;
    uint16_t * pBlockDopplerCorrection;
    uint16_t * pBlockPitchRemoval;

    uint32_t maxParamBlockSize;
#endif
    if ( testcaseParams->numLines < VCOP_SIMD_WIDTH)
    {
        transposeStride        = ( (VCOP_SIMD_WIDTH) + 1 ) * sizeof(uint32_t);
    }
    else
    {
        transposeStride        = (((testcaseParams->numLines % 2)?testcaseParams->numLines :
                testcaseParams->numLines + 1)) *   sizeof(uint32_t);
    }

    if ( testcaseParams->enableOverflowDetection == 1 )
    {
        overflowMask = (uint32_t)VCOP_FFT_NPT_16ix32o_STAGE_ALL_OVERFLOW;
    }
    else
    {
        overflowMask = 0;
    }
    profiler_init();
    vcop_minit();
    numOfLines = testcaseParams->numLines;

#if VCOP_HOST_EMULATION
    /* allocating full 16KB to store intermediateresults */
    pScratchIBufL   = (int16_t *)FFT_TEST_malloc(VCOP_IBUFLA, 16384);
    /* allocating full 16KB to store intermediateresults */
    pScratchIBufH  = (int16_t *)FFT_TEST_malloc(VCOP_IBUFHA,16384);
#else
    /* VCOP_malloc cannot allocate full 16kb of data and hence using hard coded values */
    pScratchIBufL = (int16_t *) ibufla;
    pScratchIBufH   = (int16_t *) ibufha;
#endif

#if SPLIT_VLOOPS_INIT
#if !VCOP_HOST_EMULATION
    maxParamBlockSize = vcop_fft_512_16i_32o_param_count();
    maxParamBlockSize = MAX(maxParamBlockSize,
                            vcop_fft_128_16i_32o_param_count());
    maxParamBlockSize = MAX(maxParamBlockSize,
                            vcop_fft_256_16i_32o_param_count());
    maxParamBlockSize = MAX(maxParamBlockSize,
                            vcop_fft_64_16i_32o_param_count());
#endif
    pBlockMemoryFFT = (uint16_t *)FFT_TEST_malloc(VCOP_WMEM,(maxParamBlockSize * sizeof(uint16_t)));
    pBlockDopplerCorrection = (uint16_t *)FFT_TEST_malloc(VCOP_WMEM,(vcop_fft_doppler_correction_kernel_param_count()* sizeof(uint16_t)));
    pBlockPitchRemoval = (uint16_t *)FFT_TEST_malloc(VCOP_WMEM,(vcop_fft_doppler_pitch_removal_param_count()* sizeof(uint16_t)));
#endif
    /* Multiplication by 2 because for 64 point FFT we need to store 16 indexes in memory */
    pScatterOffset    = (uint16_t *)FFT_TEST_malloc(VCOP_WMEM,(2 * VCOP_SIMD_WIDTH * sizeof(uint16_t)));
    /* Allocate worst case buffer. For storing 1024 point transpose we will need 64 rows( corresponding to 16 butterflies within a group)
  in stage 3 ( all corresponding to same group ). Each row would be storing 16 groups which means 16 * 4 bytes. As we are using pScatter
  we will take next odd word which would be 68 bytes. So for a single line memory requried would be 64 * 68 bytes. For 1024 case we can process
  maximum of 4 lines hence total memory would be 64 * 68 * 4 bytes. */
    /* For 512 point transpose we need 512 * 9 * 4 bytes of memory which is greater than the above quantity and hence allocate for the
  worst case */
    pInputDataWbuf        = (int16_t *)FFT_TEST_malloc(VCOP_WMEM,512 * 9 * 4);

    /* We actually need only 5 + 8 meomry */
    pScaleFactorOut =(uint8_t *)FFT_TEST_malloc(VCOP_WMEM,VCOP_SIMD_WIDTH * 2 * sizeof(uint8_t));
    //if ( testcaseParams->enableDopplerCorrection == 1 )
    //{
    //    pDopplerCorrectionBuf = (int16_t *)FFT_TEST_malloc(VCOP_WMEM,(testcaseParams->numPoints * sizeof(uint16_t)* 2));
    //}

    refOutputData32 = (int32_t *)malloc((testcaseParams->numPoints) * numOfLines * sizeof(uint32_t) * 2);
    refOutputScratch32 = (int32_t *)malloc((testcaseParams->numPoints) * sizeof(uint32_t) * 2);
    inputDataRef   = (int16_t *)malloc((testcaseParams->numPoints)* numOfLines * sizeof(uint32_t) * 2);
    scratchBufRef   = (int32_t *)malloc((testcaseParams->numPoints) * sizeof(uint32_t) * 2);
    pMinMaxRef     = (int32_t *)malloc(5 * sizeof(int32_t) * 2);


    memset (pScaleFactorOut, 0, VCOP_SIMD_WIDTH * 2 * sizeof(uint8_t));
    fail = 0;

    for ( i = 0; i < 5; i++)
    {
        *(pMinMaxRef + 2 * i) = 0x7FFFFFFF;
        *(pMinMaxRef + 2 * i +1) = 0x80000000;
    }

    if(strcmp(testcaseParams->inputData, ""))
    {
        printf("File Test\n");
        fp_in = fopen((const char *)testcaseParams->inputData, "rb");

        if(fp_in == NULL) {
            printf("Failed to open input file: %s.\n", testcaseParams->inputData);
            return -1;
        }
        fread(pInputDataWbuf, testcaseParams->numPoints * testcaseParams->numLines , sizeof(uint32_t), fp_in);
        fclose(fp_in);
        /* Create a duplicate copy of input data for reference because during processing we will overwrite the input buffer */
        memcpy(inputDataRef, pInputDataWbuf, testcaseParams->numPoints * numOfLines * sizeof(int16_t) * 2);
    }
    else
    {
        /* Generate input data */
        seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
        srand(seed);
        printf("Random pattern test: Seed = %d\n", seed);

        for ( j = 0; j < numOfLines; j++ )
        {
            inputDataOffst16 = (j)*testcaseParams->numPoints*2;

            for ( i = 0; i < testcaseParams->numPoints; i++ )
            {
#if FIXED_PATTERN
                pInputDataWbuf[inputDataOffst16+2*i] = i % 64;//sin((100+20*j)*2*PI*i/512)*(64.0 + (j*2));  //sin(100*2*PI*i/512)*64.0 + sin(350*2*PI*i/512)*64.0;
                pInputDataWbuf[inputDataOffst16+2*i+1] = 0;//sin((100+20*j)*2*PI*i/512)*(16.0 + (j*2));//in[2*i +1];
#else
                pInputDataWbuf[inputDataOffst16+2*i] =  rand()% ( 1<< 8);
                pInputDataWbuf[inputDataOffst16+2*i+1] = rand()% ( 1<< 8);
#endif
                inputDataRef[inputDataOffst16+2*i] = pInputDataWbuf[inputDataOffst16+2*i];
                inputDataRef[inputDataOffst16+2*i+1] = pInputDataWbuf[inputDataOffst16+2*i+1];

            }
        }


    }
#if 0
    if ( testcaseParams->enableDopplerCorrection == 1 )
    {
        if(strcmp(testcaseParams->dopplerCorrectionBuf, ""))
        {
            printf("File Test\n");
            fp_in = fopen((const char *)testcaseParams->dopplerCorrectionBuf, "rb");

            if(fp_in == NULL) {
                printf("Failed to open input file: %s.\n", testcaseParams->dopplerCorrectionBuf);
                return -1;
            }
            fread(pDopplerCorrectionBuf, testcaseParams->numPoints , sizeof(uint32_t), fp_in);
            fclose(fp_in);
        }
        else
        {
            /* Generate input data */
            seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
            srand(seed);
            printf("Random pattern test: Seed = %d\n", seed);


            for ( i = 0; i < testcaseParams->numPoints; i++ )
            {
#if FIXED_PATTERN
                pDopplerCorrectionBuf[2*i] = i % 64;//sin((100+20*j)*2*PI*i/512)*(64.0 + (j*2));  //sin(100*2*PI*i/512)*64.0 + sin(350*2*PI*i/512)*64.0;
                pDopplerCorrectionBuf[2*i+1] = 0;//sin((100+20*j)*2*PI*i/512)*(16.0 + (j*2));//in[2*i +1];
#else
                pDopplerCorrectionBuf[2*i] =  rand()%512;
                pDopplerCorrectionBuf[2*i+1] = rand()%512;
#endif

            }
        }
    }
#endif
    strcpy(testcaseName, "FFT");
    strcat(testcaseName," FFT kernel");

    profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
    printparams(&gsTokenMap_FFT_np_16ix16tx32o[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sFFT_np_16ix16tx32o_Config)) ;

    saturationLimit = 32768;

    if ( testcaseParams->numPoints == 512 )
    {
#if SPLIT_VLOOPS_INIT
        sVCOP_FFT_512_pBlock_t pBlock;
        sVCOP_FFT_512_pBlock_t * pBlockWBUF = (sVCOP_FFT_512_pBlock_t *)pBlockMemoryFFT ;
#endif
        uint8_t enableInPlaceCompute = 1;
#if 0
        if (testcaseParams->enableDopplerCorrection == 1)
        {
            enableInPlaceCompute = 0;
        }
#endif
        sizeofTwiddleFactorBuf = getSizeTwiddleFactor_512();
        twiddleFactorBuf  = (int16_t *)FFT_TEST_malloc(VCOP_WMEM,sizeofTwiddleFactorBuf);
        generateTwiddleFactor_512(twiddleFactorBuf);


        profiler_start();
#if !SPLIT_VLOOPS_INIT
        vcop_fft_512_16i_32o(pInputDataWbuf,
                             pScratchIBufL,
                             pScratchIBufH,
                             twiddleFactorBuf,
                             pScatterOffset,
                             pScaleFactorOut,
                             15,
                             testcaseParams->numPoints * sizeof(int16_t) * 2,
                             testcaseParams->scaleFactor,
                             testcaseParams->numLines,
                             enableInPlaceCompute,
                             overflowMask,
                             saturationLimit);
#else
        vcop_fft_512_16i_32o_init(pInputDataWbuf,
                                  pScratchIBufL,
                                  pScratchIBufH,
                                  twiddleFactorBuf,
                                  pScatterOffset,
                                  pScaleFactorOut,
                                  15,
                                  testcaseParams->numPoints * sizeof(int16_t) * 2,
                                  testcaseParams->scaleFactor,
                                  testcaseParams->numLines,
                                  enableInPlaceCompute,
                                  overflowMask,
                                  saturationLimit,
                                  pBlockMemoryFFT);

        pBlock.pblock_stage_1 = pBlockWBUF->pblock_stage_1;
        pBlock.pblock_stage_2 = pBlockWBUF->pblock_stage_2;
        pBlock.pblock_stage_3 = pBlockWBUF->pblock_stage_3;
        pBlock.pblock_stage_4 = pBlockWBUF->pblock_stage_4;
        pBlock.pblock_stage_5 = pBlockWBUF->pblock_stage_5;
        for ( i = 0; i < 5U; i++)
        {
            pBlock.execFunc[i] = pBlockWBUF->execFunc[i];
        }

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);
        vcop_fft_512_16i_32o_vloops((uint16_t *)&pBlock);
        _vcop_vloop_done();
        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

#endif

        profiler_end_print(1);
    }
    else if ( testcaseParams->numPoints == 128 )
    {
#if SPLIT_VLOOPS_INIT
        sVCOP_FFT_128_pBlock_t pBlock;
        sVCOP_FFT_128_pBlock_t * pBlockWBUF = (sVCOP_FFT_128_pBlock_t *)pBlockMemoryFFT ;
#endif
        sizeofTwiddleFactorBuf = getSizeTwiddleFactor_128();
        twiddleFactorBuf  = (int16_t *)FFT_TEST_malloc(VCOP_WMEM,sizeofTwiddleFactorBuf);
        generateTwiddleFactor_128(twiddleFactorBuf);

        profiler_start();

#if !SPLIT_VLOOPS_INIT
        vcop_fft_128_16i_32o(pInputDataWbuf,
                             pScratchIBufL,
                             pScratchIBufH,
                             twiddleFactorBuf,
                             pScatterOffset,
                             pScaleFactorOut,
                             15,
                             testcaseParams->numPoints * sizeof(int16_t) * 2,
                             testcaseParams->scaleFactor,
                             testcaseParams->numLines,
                             1,
                             overflowMask,
                             saturationLimit);
#else
        vcop_fft_128_16i_32o_init(pInputDataWbuf,
                                  pScratchIBufL,
                                  pScratchIBufH,
                                  twiddleFactorBuf,
                                  pScatterOffset,
                                  pScaleFactorOut,
                                  15,
                                  testcaseParams->numPoints * sizeof(int16_t) * 2,
                                  testcaseParams->scaleFactor,
                                  testcaseParams->numLines,
                                  1,
                                  overflowMask,
                                  saturationLimit,
                                  pBlockMemoryFFT);

        pBlock.pblock_stage_1 = pBlockWBUF->pblock_stage_1;
        pBlock.pblock_stage_2 = pBlockWBUF->pblock_stage_2;
        pBlock.pblock_stage_3 = pBlockWBUF->pblock_stage_3;
        pBlock.pblock_stage_4 = pBlockWBUF->pblock_stage_4;
        for ( i = 0; i < 4; i++)
        {
            pBlock.execFunc[i] = pBlockWBUF->execFunc[i];
        }
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);
        vcop_fft_128_16i_32o_vloops((uint16_t *)&pBlock);
        _vcop_vloop_done();
        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

#endif

        profiler_end_print(1);
    }
    else if ( testcaseParams->numPoints == 256 )
    {
#if SPLIT_VLOOPS_INIT
        sVCOP_FFT_256_pBlock_t pBlock;
        sVCOP_FFT_256_pBlock_t * pBlockWBUF = (sVCOP_FFT_256_pBlock_t *)pBlockMemoryFFT ;
#endif
        sizeofTwiddleFactorBuf = getSizeTwiddleFactor_256();
        twiddleFactorBuf  = (int16_t *)FFT_TEST_malloc(VCOP_WMEM,sizeofTwiddleFactorBuf);
        generateTwiddleFactor_256(twiddleFactorBuf);

        profiler_start();
#if !SPLIT_VLOOPS_INIT
        vcop_fft_256_16i_32o(pInputDataWbuf,
                             pScratchIBufL,
                             pScratchIBufH,
                             twiddleFactorBuf,
                             pScatterOffset,
                             pScaleFactorOut,
                             15,
                             testcaseParams->numPoints * sizeof(int16_t) * 2,
                             testcaseParams->scaleFactor,
                             testcaseParams->numLines,
                             1,
                             overflowMask,
                             saturationLimit);
#else
        vcop_fft_256_16i_32o_init(pInputDataWbuf,
                                  pScratchIBufL,
                                  pScratchIBufH,
                                  twiddleFactorBuf,
                                  pScatterOffset,
                                  pScaleFactorOut,
                                  15,
                                  testcaseParams->numPoints * sizeof(int16_t) * 2,
                                  testcaseParams->scaleFactor,
                                  testcaseParams->numLines,
                                  1,
                                  overflowMask,
                                  saturationLimit,
                                  pBlockMemoryFFT);
        pBlock.pblock_stage_1 = pBlockWBUF->pblock_stage_1;
        pBlock.pblock_stage_2 = pBlockWBUF->pblock_stage_2;
        pBlock.pblock_stage_3 = pBlockWBUF->pblock_stage_3;
        pBlock.pblock_stage_4 = pBlockWBUF->pblock_stage_4;

        for ( i = 0; i < 4U; i++)
        {
            pBlock.execFunc[i] = pBlockWBUF->execFunc[i];
        }

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);
        vcop_fft_256_16i_32o_vloops((uint16_t *)&pBlock);
        _vcop_vloop_done();
        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

#endif
        profiler_end_print(1);
    }

    else if ( testcaseParams->numPoints == 64 )
    {
#if SPLIT_VLOOPS_INIT
        sVCOP_FFT_64_pBlock_t pBlock;
        sVCOP_FFT_64_pBlock_t * pBlockWBUF = (sVCOP_FFT_64_pBlock_t *)pBlockMemoryFFT ;
#endif
        sizeofTwiddleFactorBuf = getSizeTwiddleFactor_64();
        twiddleFactorBuf  = (int16_t *)FFT_TEST_malloc(VCOP_WMEM,sizeofTwiddleFactorBuf);
        generateTwiddleFactor_64(twiddleFactorBuf);


        profiler_start();

#if !SPLIT_VLOOPS_INIT
        vcop_fft_64_16i_32o(pInputDataWbuf,
                            pScratchIBufL,
                            pScratchIBufH,
                            twiddleFactorBuf,
                            pScatterOffset,
                            pScaleFactorOut,
                            15,
                            testcaseParams->numPoints * sizeof(int16_t) * 2,
                            testcaseParams->scaleFactor,
                            testcaseParams->numLines,
                            1,
                            overflowMask,
                            saturationLimit);
#else
        vcop_fft_64_16i_32o_init(pInputDataWbuf,
                                 pScratchIBufL,
                                 pScratchIBufH,
                                 twiddleFactorBuf,
                                 pScatterOffset,
                                 pScaleFactorOut,
                                 15,
                                 testcaseParams->numPoints * sizeof(int16_t) * 2,
                                 testcaseParams->scaleFactor,
                                 testcaseParams->numLines,
                                 1,
                                 overflowMask,
                                 saturationLimit,
                                 pBlockMemoryFFT);
        pBlock.pblock_stage_1 = pBlockWBUF->pblock_stage_1;
        pBlock.pblock_stage_2 = pBlockWBUF->pblock_stage_2;
        pBlock.pblock_stage_3 = pBlockWBUF->pblock_stage_3;

        for ( i = 0; i < 3U; i++)
        {
            pBlock.execFunc[i] = pBlockWBUF->execFunc[i];
        }

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);
        vcop_fft_64_16i_32o_vloops((uint16_t *)&pBlock);
        _vcop_vloop_done();
        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

#endif

        profiler_end_print(1);
    }


    /* Reference Code starts here */

    {
        int16_t * twiddleFactorRef = NULL;
        uint32_t sizeofTfBuf;
        uint16_t scaleFactorArray[5];
        isOverflowDetected = 0;

        if ( testcaseParams->enableOverflowDetection == 1)
        {
            for ( i = 0; i < 5; i++)
            {
                scaleFactorArray[i] = pScaleFactorOut[i];
                if ( pScaleFactorOut[i] != 0 )
                {
                    isOverflowDetected = 1;
                }
            }
        }
        else
        {
            for ( i = 0; i < 5; i++)
            {
                scaleFactorArray[i] = testcaseParams->scaleFactor[i];
            }
        }
        twiddleFactorRef = generateTwiddleFactor_ref2(testcaseParams->numPoints, 0, &sizeofTfBuf);


        for( j = 0; j < testcaseParams->numLines; j ++)
        {
#if _DUMP
            {
                char filename[256];

                sprintf(filename, "refCdump/test_%dx%d_ovf%d_line_%d.txt", testcaseParams->numLines, testcaseParams->numPoints, testcaseParams->enableOverflowDetection, j);
                natcDumpFid= fopen(filename, "wt");
                if (natcDumpFid== NULL) {
                    printf("Error opening file %s\n", filename);
                }
            }
#endif
            vcop_fft_npt_32o_mixed_radix_cn(inputDataRef+ j * testcaseParams->numPoints * 2,
                                        twiddleFactorRef,
                                        scratchBufRef,
                                        refOutputScratch32,
                                        refOutputData32 + j * testcaseParams->numPoints * 2,
                                        scaleFactorArray,
                                        pMinMaxRef,
                                        testcaseParams->numPoints,
                                        0,
                                        saturationLimit,
                                        overflowMask);
#if _DUMP
            if (natcDumpFid!= NULL) {
                fclose(natcDumpFid);
            }
#endif
        }
        if (twiddleFactorRef != NULL)
        {
            free(twiddleFactorRef);
            twiddleFactorRef = NULL;
        }

    }

    fail = 0;

    printf("isOverflowDetected %d \n", isOverflowDetected);

    {
        int32_t * pInputDataWbuf32= (int32_t*)pInputDataWbuf;

        if (1)//( testcaseParams->enableDopplerCorrection == 0)
        {

            for ( j = 0; j < testcaseParams->numLines; j ++)
            {
                for (i = 0; i < testcaseParams->numPoints; i++)
                {
                    if ( ( pInputDataWbuf32[(j * testcaseParams->numPoints + i) * 2] != refOutputData32[2*(j * testcaseParams->numPoints + i)] ) ||
                            ( pInputDataWbuf32[2*(j * testcaseParams->numPoints + i) + 1] != refOutputData32[2*(j * testcaseParams->numPoints + i) + 1] ) )
                    {
                        fail = 1;
                        printf("FFT is not matching at line %d point %d ref %d target %d \n", j, i, refOutputData32[2*(j * testcaseParams->numPoints + i)],pInputDataWbuf32[2*(j * testcaseParams->numPoints + i)] );
                        printf("FFT is not matching at line %d point %d ref %d target %d \n", j, i, refOutputData32[2*(j * testcaseParams->numPoints + i) + 1],pInputDataWbuf32[2*(j * testcaseParams->numPoints + i) + 1] );
                        goto EXIT;
                    }

                }
            }
        }
        else
        {
            /* For num points equal to 512 we have already removed the holes between lines */
            if ( testcaseParams->numPoints == 512)
            {
                transposeStride = testcaseParams->numLines * sizeof(int32_t);
            }
            for ( j = 0; j < testcaseParams->numPoints; j ++)
            {
                for (i = 0; i < testcaseParams->numLines; i++)
                {
                    if ( ( pInputDataWbuf32[(j * (transposeStride/ sizeof(int32_t))+ i) * 2] != refOutputData32[2*(j * testcaseParams->numLines + i)] ) ||
                            ( pInputDataWbuf32[2*(j * (transposeStride/ sizeof(int32_t)) + i) + 1] != refOutputData32[2*(j * testcaseParams->numLines + i) + 1] ) )
                    {
                        fail = 1;
                        printf("FFT is not matching at line %d point %d ref %d target %d \n", j, i, refOutputData32[2*(j * testcaseParams->numLines + i)],pInputDataWbuf32[(j * (transposeStride/ sizeof(int32_t))+ i) * 2] );
                        printf("FFT is not matching at line %d point %d ref %d target %d \n", j, i, refOutputData32[2*(j * testcaseParams->numLines + i) + 1],pInputDataWbuf32[2*(j * (transposeStride/ sizeof(int32_t)) + i) + 1] );
                        goto EXIT;
                    }

                }
            }
        }
    }
    if ( isOverflowDetected == 1 )
    {
        uint32_t  numStages = (log((double)testcaseParams->numPoints) / log((double)4) ) + 0.5;
        int32_t maxNBitValue;
        int32_t minNBitValue;
        uint32_t numBits = 15U;
        uint32_t scaleFactor;

        maxNBitValue = (1<< (numBits- 1)) - 1;
        minNBitValue = -(1<< (numBits- 1));

        i= numStages - 1;

        {
            uint32_t finalMax;
            if ( (pMinMaxRef[2*i] == minNBitValue) || (pMinMaxRef[2*i + 1] == minNBitValue) )
            {
                finalMax = maxNBitValue;
            }
            else
            {
                finalMax = MAX(abs(pMinMaxRef[2*i]) , abs(pMinMaxRef[2*i + 1]) ) ;
            }
            scaleFactor = 0;
            while(  (finalMax >> scaleFactor) > maxNBitValue )
            {
                scaleFactor++;
            }

            if ( scaleFactor != pScaleFactorOut[i] )
            {
                fail = 1;
                printf("Overflow detection not working at stage %d \n",i + 1);
                printf("Overflow detection : FAILED\n");
                goto EXIT;
            }
        }

        printf("Overflow detection : PASSED\n");
        goto EXIT;
    }


    EXIT:

    profiler_printStatus(fail);

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;

    if ( pInputDataWbuf)
    {
        FFT_TEST_free(pInputDataWbuf);
    }

    if(pScratchIBufL)
    {
        FFT_TEST_free(pScratchIBufL);
    }

    if(pScratchIBufH)
    {
        FFT_TEST_free(pScratchIBufH);
    }

    if(twiddleFactorBuf)
    {
        FFT_TEST_free(twiddleFactorBuf);
    }

#if SPLIT_VLOOPS_INIT
    if(pBlockMemoryFFT)
    {
        FFT_TEST_free(pBlockMemoryFFT);
    }
    //if(pBlockDopplerCorrection)
    //{
    //    FFT_TEST_free(pBlockDopplerCorrection);
    //}
    if(pBlockPitchRemoval)
    {
        FFT_TEST_free(pBlockPitchRemoval);
    }


#endif
    if ( twiddleFactorBufExt)
    {
        free(twiddleFactorBufExt);
    }

    if(refOutputData32)
    {
        free(refOutputData32);
    }

    if(refOutputScratch32)
    {
        free(refOutputScratch32);
    }

    profiler_deinit();

    printf(status ? "\nFAIL\n" : "\nPASS\n");

    return (status);
}

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '  '))
    {
        LinePtr++;
    }
    return(LinePtr);
}

int32_t main(int32_t argc, char *argv[])
{
    int status = 0;
    char configFile[FILE_NAME_SIZE]={0};
    char configLine[MAX_CONFIG_LINE_SIZE];
    char configParam[MAX_PARAM_STRING_SIZE];
    int8_t *LinePtr;
    FILE *fp;
    int32_t lineNum = -1, config_cmd;

    if (argc > 1) {
        strcpy(configFile, argv[1]) ;
    }
    else {
        strcpy(configFile, "../testvecs/config/config_list.txt");
    }

    fp = fopen((const char *)configFile , "r");
    if(fp== NULL) {
        printf("Could not open config list file : %s \n", configFile);
        return(status);
    }

    CF_profile_init(3, "FFT 16bit input and 32 bit output");

    while(1) {
        memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
        status = (int)fgets(configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = (int8_t *)configLine;
        if ((status == EOF) || (status == 0)) {
            break;
        }

        status = 0;
        lineNum++;
        sscanf((const char *)LinePtr, "%d",&config_cmd);
        sscanf((const char *)LinePtr, "%s",configParam);

        if(config_cmd == 0) {
            printf("End of config list found !\n");
            break;
        }
        else if(config_cmd == 2) {
            continue;
        }
        else if(config_cmd == 1) {
            LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
            status  = sscanf((const char *)LinePtr, "%s",configFile);
            printf("\nProcessing config file %s !\n", configFile);
            status = readparamfile(configFile, &gsTokenMap_FFT_np_16ix16tx32o[0]);
            if(status == -1) {
                printf("Parser Failed");
                return -1 ;
            }

            /* Validate the kernel */
            status = fftTest(&gConfig_FFT_np_16ix16tx32o);

            if(status == -1) {
                return status;
            }
        }
        else {
            printf("Unsupported config list command parameter at line num : %4d !\n", lineNum);
        }
    }

    fclose(fp);

    return status;
}


