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
#include <assert.h>

#include <math.h>

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_peak_detection_config.h"


/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Peak Detection kernel   */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_peak_detection_cn.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_peak_detection_kernel.k"
#else
#include "../inc/vcop_peak_detection_kernel.h"
#endif

#define FIXED_PATTERN (0)
//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)

#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define CEIL(x,y) ((( x + y - 1) / y) * y)

#define NUM_TABLES (8)


#if (VCOP_HOST_EMULATION)
#define PEAK_DETECTION_TEST_malloc(heap, size)   malloc(size)
#define PEAK_DETECTION_TEST_free(ptr)            free(ptr)
#else
#define PEAK_DETECTION_TEST_malloc(heap, size)   (vcop_malloc((heap), (size)))
#define PEAK_DETECTION_TEST_free(ptr)            (vcop_free(ptr))
#endif

typedef double double64_t;

static int16_t d2s(double64_t d);

static int16_t d2s(double64_t d)
{
  int16_t outVal;

  outVal = (int16_t)d;

  if (d >=  32767.0)
  {
    outVal = 32767;
  }
  if (d <= -32768.0)
  {
    outVal = (int16_t)-32768;
  }
  return outVal;
}


void fillDefaultConfig(sPeak_detection_Config * params)
{
  strcpy(params->inputData, "");
  strcpy(params->outData, "");

  params->numTx = 3;
  params->numTx = 4;
  params->numHorzPtPerAntenna = 8;
  params->offsetBwTx = 8 * 4 * sizeof(uint32_t);
  params->offsetBwRx = sizeof(uint32_t);
  params->alphaQFormat = 6;
  params->lutQFormat   = 8;
  params->noiseLen     = 4;
  params->gaurdLen     = 2;
  params->const1       = 1;
  params->const2       = 2;
  params->dopplerIdxOffset = 0;
  params->testType =1;
  params->performanceTestcase  = 1;
  params->randSeed      = 0;
}


int32_t energyComputationTest(sPeak_detection_Config * testcaseParams)
{
  int32_t fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;

  int32_t i, j;
  int16_t * inputData = NULL;
  int16_t * outputData = NULL;
  int16_t * inputDataRef = NULL;
  int16_t * outputDataRef = NULL;
  uint32_t * outputEnergy32 = NULL;
  uint32_t * outputEnergy32Ref = NULL;
  int16_t * txDecodingCoeffBuf = NULL;
  uint16_t * indexBuf = NULL;
  uint8_t * lmbdBuf = NULL;
  uint16_t * lutValueBuf = NULL;
  uint16_t * lutTableBuf = NULL;
  uint16_t * outputEnergy16 = NULL;
  uint16_t * scatterIndex = NULL;
  uint16_t * outputEnergy16Ref;
  uint32_t numLUTPoints;

  char    testcaseName[100];
  int16_t * inputDataArr[4];
  int16_t * outputDataArr[4];
  uint32_t numWordsRequired;
  uint16_t outputPitch;

  profiler_init();
  vcop_minit();
  inputData   = (int16_t *) PEAK_DETECTION_TEST_malloc(VCOP_IBUFLA, testcaseParams->pitch *
                                                                    testcaseParams->numRows);
  inputDataRef = (int16_t *)malloc(testcaseParams->pitch * testcaseParams->numRows);
  if ( inputData == NULL )
  {
    printf("Failed to allocate memory \n");
    return -1;
  }

  outputData   = (int16_t *) PEAK_DETECTION_TEST_malloc(VCOP_IBUFHA,testcaseParams->pitch *
                                                                    testcaseParams->numRows
                                                                    );

  outputDataRef = (int16_t *)malloc(testcaseParams->pitch * testcaseParams->numRows);


  txDecodingCoeffBuf = (int16_t*)PEAK_DETECTION_TEST_malloc(VCOP_WMEM,( sizeof(int16_t) * (testcaseParams->numTx) * (testcaseParams->numTx)));

  scatterIndex = (uint16_t*)PEAK_DETECTION_TEST_malloc(VCOP_WMEM, VCOP_SIMD_WIDTH * sizeof(uint16_t));

  fail = 0;

  if(strcmp(testcaseParams->inputData, ""))
  {
    printf("File Test\n");
    fp_in = fopen((const char *)testcaseParams->inputData, "rb");

    if(fp_in == NULL) {
      printf("Failed to open input file: %s.\n", testcaseParams->inputData);
      return -1;
    }

    fread(inputData, testcaseParams->pitch* testcaseParams->numRows, 1, fp_in);
    fclose(fp_in);
  }
  else
  {
    /* Generate input data */
    seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
    srand(seed);
    printf("Random pattern test: Seed = %d\n", seed);
    for ( j = 0; j < testcaseParams->numRows;j++)
    {
      for ( i = 0; i < testcaseParams->numTx * testcaseParams->numRx * testcaseParams->numHorzPtPerAntenna;i++)
      {
#if FIXED_PATTERN
        inputData[2* (i + j * testcaseParams->pitch / sizeof(int32_t))] = i;
        inputData[2*(i + j * testcaseParams->pitch / sizeof(int32_t)) + 1] = i+5;
#else
        /* Limit input to smaller range to avoid overflow */
        inputData[2* (i + j * testcaseParams->pitch / sizeof(int32_t))] = rand()%256;
        inputData[2*(i + j * testcaseParams->pitch / sizeof(int32_t)) + 1] = rand()%256;
#endif
      }
    }
  }
  memcpy(inputDataRef, inputData, testcaseParams->pitch* testcaseParams->numRows);

  for ( i = 0 ; i < testcaseParams->numTx * testcaseParams->numTx; i++)
  {
    txDecodingCoeffBuf[i] = d2s((( (rand() % 2 == 0 ) ? +1 : -1) * 32767));
  }
  strcpy(testcaseName, (char *)testcaseParams->testCaseName);
  strcat(testcaseName," Peak Detection KERNELS");

  profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
  printparams(&gsTokenMap_Peak_detection[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sPeak_detection_Config)) ;

  for ( i = 0; i < testcaseParams->numHorzPtPerAntenna / VCOP_SIMD_WIDTH;i++)
  {
    inputDataArr[i]   = inputData + (i * (VCOP_SIMD_WIDTH) * 2);
    outputDataArr[i]  = outputData + (i * (VCOP_SIMD_WIDTH) * 2);
  }

  profiler_start();

  vcop_tx_decoding_kernel(inputDataArr,
                          txDecodingCoeffBuf,
                          outputDataArr,
                          testcaseParams->numTx,
                          testcaseParams->numRx,
                          testcaseParams->numRows,
                          testcaseParams->numHorzPtPerAntenna,
                          testcaseParams->offsetBwTx,
                          testcaseParams->offsetBwRx,
                          testcaseParams->pitch);


  profiler_end_print(1);

  vcop_tx_decoding_cn(inputData,
                      txDecodingCoeffBuf,
                      outputDataRef,
                      testcaseParams->numTx,
                      testcaseParams->numRx,
                      testcaseParams->numRows,
                      testcaseParams->numHorzPtPerAntenna,
                      testcaseParams->offsetBwTx,
                      testcaseParams->offsetBwRx,
                      testcaseParams->pitch);


  fail = 0;


  fail = memcmp(outputData, outputDataRef, testcaseParams->numTx * testcaseParams->numRx * sizeof(int32_t) * testcaseParams->numRows);
  if ( fail != 0 )
  {
    for ( i = 0; i < testcaseParams->numRows; i++)
    {
      for ( j = 0; j < testcaseParams->numTx * testcaseParams->numRx; j++)
      {
        if ( ( outputData[2 *(j + i * (testcaseParams->numTx * testcaseParams->numRx))] != outputDataRef[2 *(j + i * (testcaseParams->numTx * testcaseParams->numRx))] ) ||
             ( outputData[2 *(j + i * (testcaseParams->numTx * testcaseParams->numRx)) + 1] != outputDataRef[2 *(j + i * (testcaseParams->numTx * testcaseParams->numRx)) + 1] ))
        {
          printf("Output of vcop_tx_decoding_kernel is not matching at row %d, for antenna %d \n",i , j );
          fail = 1;
          break;
        }
      }
      if ( fail == 1)
      {
        break;
      }
    }
    printf("vcop_tx_decoding_kernel is not working : FAIL  \n");
  }
  else
  {
    printf("vcop_tx_decoding_kernel is working : PASSED \n");
  }


  /* Release input data buffer as it is not needed now */
  if ( inputData != NULL )
  {
    PEAK_DETECTION_TEST_free(inputData);
    inputData = NULL;
  }

  /* Output of previous kernel becomes input to next kernel */
  inputData = outputData;

  outputEnergy32 = (uint32_t *)PEAK_DETECTION_TEST_malloc(VCOP_IBUFLA,testcaseParams->numHorzPtPerAntenna * sizeof(uint32_t) * testcaseParams->numRows);
  outputEnergy32Ref = (uint32_t *)malloc(testcaseParams->numHorzPtPerAntenna * sizeof(uint32_t) * testcaseParams->numRows);

  profiler_start();
  vcop_peak_detection_energy_across_antenna(inputData,
                                            outputEnergy32,
                                            testcaseParams->numRows,
                                            testcaseParams->numTx * testcaseParams->numRx,
                                            testcaseParams->numHorzPtPerAntenna,
                                            testcaseParams->pitch);
  profiler_end_print(1);

  vcop_peak_detection_energy_across_antenna_cn(inputData,
                                            outputEnergy32Ref,
                                            testcaseParams->numRows,
                                            testcaseParams->numTx * testcaseParams->numRx,
                                            testcaseParams->numHorzPtPerAntenna,
                                            testcaseParams->pitch);

  for ( i = 0; i < testcaseParams->numRows; i++)
  {
    for ( j = 0; j < testcaseParams->numHorzPtPerAntenna; j++)
    {
      if ( ( outputEnergy32[(j + i * testcaseParams->numHorzPtPerAntenna)] != outputEnergy32Ref[(j + i * testcaseParams->numHorzPtPerAntenna)] ) )
      {
        printf("Output of vcop_peak_detection_energy_across_antenna is not matching at row %d, for point %d \n",i , j );
        fail = 1;
        break;
      }
    }
    if ( fail == 1 )
    {
      break;
    }
  }

  if ( fail != 0)
  {
    printf("vcop_peak_detection_energy_across_antenna is not working : FAIL \n");
  }
  else
  {
    printf("vcop_peak_detection_energy_across_antenna is working : PASSED \n");
  }



  if ( inputData != NULL)
  {
    PEAK_DETECTION_TEST_free(inputData);
    inputData = NULL;
  }

  numLUTPoints = (1<<(testcaseParams->alphaQFormat));
  numWordsRequired = testcaseParams->numRows /2;
  if ( numWordsRequired < 9 )
  {
    numWordsRequired = 9;
  }

  outputPitch  = ( (numWordsRequired % 2 == 0 ) ? numWordsRequired + 1 : numWordsRequired);

  outputPitch  = outputPitch   * sizeof(uint32_t);

  indexBuf = (uint16_t *)PEAK_DETECTION_TEST_malloc(VCOP_IBUFLA, testcaseParams->numHorzPtPerAntenna * outputPitch);
  lmbdBuf  = (uint8_t  *)PEAK_DETECTION_TEST_malloc(VCOP_WMEM, testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint8_t));
  lutValueBuf = (uint16_t *)PEAK_DETECTION_TEST_malloc(VCOP_IBUFHA, testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint16_t));
  lutTableBuf = (uint16_t *)PEAK_DETECTION_TEST_malloc(VCOP_WMEM, 2 *  NUM_TABLES * (numLUTPoints /2 )* sizeof(uint32_t));/* Multiplication by 2 because we
  will be storing LUT table starting from index of 64 for alphaQFormat = 6. This way we can avoid substraction by one during compute and save cycles */

  outputEnergy16Ref = (uint16_t *)malloc(testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint16_t));

  /* Re-use Index buf as final output */
  outputEnergy16 = indexBuf;
  /* Generate LUT Table */
  {

    uint16_t * lutTableBasePtr = &lutTableBuf[(numLUTPoints/2) * 2 * NUM_TABLES];

    for ( i = 0; i < ( 1<<testcaseParams->alphaQFormat) ; i+=2)
    {
      double one_plus_aplha;

      one_plus_aplha = (double)(i + ( 1<<(testcaseParams->alphaQFormat))) /(double)( 1<<(testcaseParams->alphaQFormat))    ;
      lutTableBasePtr[8 * i] =  ((double)log(one_plus_aplha) / (double)log(2) ) *
                                                ( 1 << testcaseParams->lutQFormat);

      one_plus_aplha = (double)(i + 1 + ( 1<<(testcaseParams->alphaQFormat))) /(double)( 1<<(testcaseParams->alphaQFormat))    ;

      lutTableBasePtr[8 * i + 1] =  ((double)log(one_plus_aplha) / (double)log(2) ) *
                                                ( 1 << testcaseParams->lutQFormat);
      for ( j = 1; j < 8;j++)
      {
        lutTableBasePtr[8* i + 2*j ] = lutTableBasePtr[8 * i];
        lutTableBasePtr[8 * i + 2*j + 1] = lutTableBasePtr[8 * i + 1];
      }
    }
  }

  /* Set the zero'th index of LUT table to zero to handle the case when energy is zero */
  for ( i = 0; i < NUM_TABLES; i++)
  {
    lutTableBuf[2*i] = 0;
  }


  for ( i = 0; i < 8;i++)
  {
    scatterIndex[i] = i * outputPitch;
  }


  profiler_start();
  vcop_peak_detection_binlog_energy_scaling(outputEnergy32,
                                            indexBuf,
                                            lmbdBuf,
                                            lutTableBuf,
                                            lutValueBuf,
                                            scatterIndex,
                                            outputEnergy16,
                                            outputPitch,
                                            testcaseParams->lutQFormat,
                                            testcaseParams->alphaQFormat,
                                            testcaseParams->numRows,
                                            testcaseParams->numHorzPtPerAntenna);
  profiler_end();
  vcop_peak_detection_binlog_energy_scaling_cn(outputEnergy32,
                                               lutTableBuf,
                                               outputEnergy16Ref,
                                               testcaseParams->lutQFormat,
                                               testcaseParams->alphaQFormat,
                                               testcaseParams->numRows,
                                               testcaseParams->numHorzPtPerAntenna);


  for ( j = 0; j < testcaseParams->numHorzPtPerAntenna; j++)
  {
    for ( i = 0; i < testcaseParams->numRows; i++)
    {
      if ( ( outputEnergy16[(i + j * outputPitch/sizeof(uint16_t))] != outputEnergy16Ref[(i + j * testcaseParams->numRows)] ) )
      {
        printf("Output of vcop_peak_detection_binlog_energy_scaling is not matching at row %d, for point %d \n",i , j );
        fail = 1;
        break;
      }
    }
    if ( fail == 1 )
    {
      break;
    }
  }

  if ( fail != 0)
  {
    printf("vcop_peak_detection_binlog_energy_scaling is not working : FAIL \n");
  }
  else
  {
    printf("vcop_peak_detection_binlog_energy_scaling is working : PASSED \n");
  }

  if ( indexBuf)
  {
    PEAK_DETECTION_TEST_free(indexBuf);
  }
  if ( lmbdBuf)
  {
    PEAK_DETECTION_TEST_free(lmbdBuf);
  }
  if ( lutValueBuf)
  {
    PEAK_DETECTION_TEST_free(lutValueBuf);
  }


  if ( txDecodingCoeffBuf)
  {
    PEAK_DETECTION_TEST_free(txDecodingCoeffBuf);
  }

  if ( inputDataRef)
  {
    free(inputDataRef);
  }

  if ( outputDataRef)
  {
    free(outputDataRef);
  }

  if ( outputEnergy32Ref)
  {
    free(outputEnergy32Ref);
  }

  profiler_deinit();

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}

int32_t CFARCATest(sPeak_detection_Config * testcaseParams)
{
  int32_t fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;

  int32_t i, j;
  uint16_t * inputEnergy1 = NULL;
  uint16_t * inputEnergy2 = NULL;
  uint16_t * inputEnergyRef = NULL;
  uint16_t * cellSum = NULL;
  uint32_t * cellSumOneLine = NULL;
  uint8_t  * binaryMask = NULL;
  uint32_t * idxBuf= NULL;
  uint16_t * cellSumRef = NULL;
  uint16_t * outEnergyBuf = NULL;
  uint16_t * outRangeDopplerBuf = NULL;
  uint16_t * outEnergyBufRef = NULL;
  uint16_t * outRangeDopplerBufRef = NULL;
  uint16_t * numDetections;
  uint32_t *currDopplerIdxBuf = NULL;
  uint16_t * horzIdxOffset;
  char    testcaseName[100];
  uint16_t numDetectionsRef;

  uint16_t numActualHorzPoints;
  uint16_t numActualVertPoints;
  uint16_t numHorzPoint;
  uint16_t numVertPoint;
  uint16_t shiftAmount;
  uint16_t cellSumPitchActual;
  uint16_t cellSumPitch;
  uint16_t inputDataPitchActual;
  uint16_t inputDataPitch;
  uint16_t vertCoordinateShift;

  profiler_init();
  vcop_minit();
  inputEnergy1   = (uint16_t *) PEAK_DETECTION_TEST_malloc(VCOP_IBUFLA, testcaseParams->pitch *
                                                                    ((testcaseParams->numRows / 2) + testcaseParams->noiseLen));
  assert( inputEnergy1 != NULL );

  inputEnergy2   = (uint16_t *) PEAK_DETECTION_TEST_malloc(VCOP_IBUFHA, testcaseParams->pitch *
                                                                    ((testcaseParams->numRows / 2) + testcaseParams->noiseLen));
  assert( inputEnergy2 != NULL );

  cellSum   = (uint16_t *) PEAK_DETECTION_TEST_malloc(VCOP_WMEM,testcaseParams->numHorzPtPerAntenna * sizeof(uint16_t) *
                                                                    (testcaseParams->numRows + 2* (testcaseParams->noiseLen + testcaseParams->gaurdLen)));
  assert( cellSum != NULL );

  cellSumOneLine = (uint32_t *) PEAK_DETECTION_TEST_malloc(VCOP_IBUFHA,testcaseParams->numHorzPtPerAntenna * sizeof(uint32_t) * 2);
  assert( cellSumOneLine != NULL );

  binaryMask = (uint8_t *) PEAK_DETECTION_TEST_malloc(VCOP_WMEM,testcaseParams->numHorzPtPerAntenna *
                                                                    testcaseParams->numRows *
                                                                    sizeof(uint8_t));
  assert(binaryMask != NULL);

  outRangeDopplerBuf = (uint16_t *)PEAK_DETECTION_TEST_malloc(VCOP_IBUFLA,(testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint16_t) * 2/4));
  assert(outRangeDopplerBuf != NULL);
  outEnergyBuf = (uint16_t *)PEAK_DETECTION_TEST_malloc(VCOP_IBUFHA,(testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint16_t))/4);
  assert(outEnergyBuf != NULL);
  numDetections = (uint16_t *)PEAK_DETECTION_TEST_malloc(VCOP_WMEM,VCOP_SIMD_WIDTH * 2 * sizeof(uint16_t));
  assert(numDetections != NULL);
  idxBuf = (uint32_t *)PEAK_DETECTION_TEST_malloc(VCOP_WMEM,2 * testcaseParams->numHorzPtPerAntenna * sizeof(uint32_t));
  assert(idxBuf != NULL);
  currDopplerIdxBuf= (uint32_t *)PEAK_DETECTION_TEST_malloc(VCOP_WMEM,sizeof(uint32_t));
  assert(currDopplerIdxBuf != NULL);
  horzIdxOffset = (uint16_t *) PEAK_DETECTION_TEST_malloc(VCOP_WMEM,testcaseParams->numHorzPtPerAntenna *sizeof(uint16_t));
  assert(horzIdxOffset != NULL);

  inputEnergyRef = (uint16_t *)malloc((testcaseParams->numRows +  testcaseParams->noiseLen)* testcaseParams->pitch);

  cellSumRef = (uint16_t *)malloc(testcaseParams->numHorzPtPerAntenna * sizeof(uint16_t) * (testcaseParams->numRows + 2* (testcaseParams->noiseLen + testcaseParams->gaurdLen)));
  outRangeDopplerBufRef = (uint16_t *)malloc(testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint16_t) * 2);
  outEnergyBufRef = (uint16_t *)malloc(testcaseParams->numHorzPtPerAntenna * testcaseParams->numRows * sizeof(uint16_t));


  memset(horzIdxOffset, 0 , (testcaseParams->numHorzPtPerAntenna * sizeof(uint16_t)));

  fail = 0;

  if(strcmp(testcaseParams->inputEnergy, ""))
  {
    printf("File Test\n");
    fp_in = fopen((const char *)testcaseParams->inputEnergy, "rb");

    if(fp_in == NULL) {
      printf("Failed to open input file: %s.\n", testcaseParams->inputEnergy);
      return -1;
    }

    fread(inputEnergyRef, testcaseParams->pitch* testcaseParams->numRows, 1, fp_in);
    fclose(fp_in);
  }
  else
  {
    /* Generate input data */
    seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
    srand(seed);
    printf("Random pattern test: Seed = %d\n", seed);
    for ( j = 0; j < testcaseParams->numRows;j++)
    {
      for ( i = 0; i < testcaseParams->numHorzPtPerAntenna;i++)
      {
#if FIXED_PATTERN
        inputEnergyRef[(i + j * testcaseParams->pitch / sizeof(uint16_t))] = i;

#else
        /* Limit input to smaller range to avoid overflow */
        inputEnergyRef[(i + j * testcaseParams->pitch / sizeof(uint16_t))] = rand()%256;
#endif

      }
    }
  }

  memcpy(inputEnergy1, inputEnergyRef, (testcaseParams->pitch *
                        ((testcaseParams->numRows / 2) + testcaseParams->noiseLen)));

  memcpy(inputEnergy2, inputEnergyRef + (testcaseParams->numRows / 2) * testcaseParams->pitch/(sizeof(uint16_t)), (testcaseParams->pitch *
                        ((testcaseParams->numRows / 2) + testcaseParams->noiseLen)));

  strcpy(testcaseName, (char *)testcaseParams->testCaseName);
  strcat(testcaseName," Peak Detection KERNELS");

  profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
  printparams(&gsTokenMap_Peak_detection[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sPeak_detection_Config)) ;

  /* Extra factor of 2 to avoid dividing when we sum left and right noise floor */
  shiftAmount = testcaseParams->const2 + 1;


  profiler_start();

  vcop_peak_detection_cell_sum(inputEnergy1,
                      inputEnergy2,
                      cellSum,
                      cellSumOneLine,
                      testcaseParams->noiseLen,
                      testcaseParams->gaurdLen,
                      testcaseParams->numHorzPtPerAntenna,//numHorzPoints
                      testcaseParams->numRows,//numVertPoint
                      testcaseParams->pitch,
                      testcaseParams->numHorzPtPerAntenna * sizeof(uint16_t),
                      shiftAmount);

  profiler_end_print(1);


  vcop_peak_detection_cell_sum_cn(inputEnergyRef,
                      cellSumRef,
                      testcaseParams->noiseLen,
                      testcaseParams->gaurdLen,
                      testcaseParams->numHorzPtPerAntenna,//numHorzPoints
                      testcaseParams->numRows,//numVertPoint
                      testcaseParams->pitch,
                      testcaseParams->numHorzPtPerAntenna * sizeof(uint16_t),
                      shiftAmount);//shift

  for ( i = 0; i < testcaseParams->numRows + (2 * (testcaseParams->noiseLen + testcaseParams->gaurdLen)) - testcaseParams->noiseLen + 1; i++)
  {
    for ( j = 0; j < testcaseParams->numHorzPtPerAntenna; j++)
    {
      if ( ( cellSum[(j + i * testcaseParams->numHorzPtPerAntenna)] != cellSumRef[(j + i * testcaseParams->numHorzPtPerAntenna)] ))
      {
        fail = 1;
        printf("Output of vcop_peak_detection_cell_sum is not matching at row %d, for antenna %d \n",i , j );
        break;
      }
    }
    if ( fail != 0)
    {
      break;
    }
  }
  if( fail != 0 )
  {
    printf("vcop_peak_detection_cell_sum is not working : FAIL  \n");
  }
  else
  {
    printf("vcop_peak_detection_cell_sum is working : PASSED \n");
  }

  vertCoordinateShift = testcaseParams->vertCoordinateShift;

  for ( j = 0; j < 2; j++)
  {
    for ( i = 0; i < testcaseParams->numHorzPtPerAntenna; i++)
    {
      idxBuf[i + j * testcaseParams->numHorzPtPerAntenna] = (i<<(16-vertCoordinateShift) ) + (j * (testcaseParams->numRows/2)<< vertCoordinateShift);

    }
  }
  currDopplerIdxBuf[0] = testcaseParams->dopplerIdxOffset;

  numActualHorzPoints = testcaseParams->numHorzPtPerAntenna;
  numActualVertPoints = testcaseParams->numRows;
  cellSumPitchActual  = testcaseParams->numHorzPtPerAntenna * sizeof(uint16_t);
  inputDataPitchActual = testcaseParams->pitch;

  if ( testcaseParams->numHorzPtPerAntenna == 8 )
  {
    numHorzPoint = numActualHorzPoints * 2;
    numVertPoint = numActualVertPoints/ 2;
    cellSumPitch = 2 * cellSumPitchActual;
    inputDataPitch = 2 * testcaseParams->pitch;
  }
  else
  {
    numHorzPoint = numActualHorzPoints;
    numVertPoint = numActualVertPoints;
    cellSumPitch = cellSumPitchActual;
    inputDataPitch = testcaseParams->pitch;
  }

  profiler_start();

  vcop_peak_detection_CFARCA_thresholding(inputEnergy1,
                                          cellSum,
                                          binaryMask,
                                          (uint32_t*)outRangeDopplerBuf,
                                          outEnergyBuf,
                                          idxBuf,
                                          currDopplerIdxBuf,
                                          numDetections,
                                          (uint32_t)inputEnergy2 - (uint32_t)inputEnergy1,
                                          testcaseParams->noiseLen,
                                          testcaseParams->gaurdLen,
                                          numActualHorzPoints,//numHorzPoints
                                          numHorzPoint,
                                          numActualVertPoints,
                                          numVertPoint,
                                          cellSumPitchActual,
                                          cellSumPitch,
                                          inputDataPitchActual,
                                          inputDataPitch,
                                          vertCoordinateShift,
                                          numActualHorzPoints,
                                          testcaseParams->const1);
  profiler_end_print(1);

  vcop_peak_detection_CFARCA_thresholding_cn(inputEnergyRef,
                                             cellSumRef,
                                             outRangeDopplerBufRef,
                                             outEnergyBufRef,
                                             &numDetectionsRef,
                                             horzIdxOffset,
                                             testcaseParams->dopplerIdxOffset,
                                             testcaseParams->noiseLen,
                                             testcaseParams->gaurdLen,
                                             testcaseParams->numHorzPtPerAntenna,//numHorzPoints
                                             testcaseParams->numRows,//numVertPoint
                                             testcaseParams->pitch,
                                             cellSumPitchActual,
                                             testcaseParams->const1,
                                             vertCoordinateShift);


  fail = 0;

  if ( numDetectionsRef != *numDetections)
  {
    fail = 1;
    printf("numDetections of vcop_peak_detection_CFARCA_thresholding is not matching\n" );

  }
  if ( fail == 0 )
  {
    for ( j = 0; j < numDetectionsRef; j++)
    {
      if ( ( outRangeDopplerBuf[2 *(j)] != outRangeDopplerBufRef[2 *(j)] ) ||
           ( outRangeDopplerBuf[2 *(j) + 1] != outRangeDopplerBufRef[2 *(j) + 1] ))
      {
        printf("range doppler of vcop_peak_detection_CFARCA_thresholding is not matching at detection %d \n",j );
        fail = 1;
        break;
      }
      if (outEnergyBuf[(j)] != outEnergyBufRef[(j)])
      {
        printf("energy of vcop_peak_detection_CFARCA_thresholding is not matching at detection  %d\n",j );
        fail = 1;
        break;
      }
    }
  }

  if ( fail != 0 )
  {
    printf("vcop_peak_detection_CFARCA_thresholding is not working : FAIL  \n");
  }
  else
  {
    printf("vcop_peak_detection_CFARCA_thresholding is working : PASSED \n");
  }


  if ( inputEnergy1 != NULL)
  {
    PEAK_DETECTION_TEST_free(inputEnergy1);
    inputEnergy1= NULL;
  }
  if ( inputEnergy2 != NULL)
  {
    PEAK_DETECTION_TEST_free(inputEnergy2);
    inputEnergy2= NULL;
  }

  if ( cellSum)
  {
    PEAK_DETECTION_TEST_free(cellSum);
  }

  if ( cellSumOneLine)
  {
    PEAK_DETECTION_TEST_free(cellSumOneLine);
  }

  if ( cellSumRef)
  {
    free(cellSumRef);
  }

  if ( inputEnergyRef != NULL)
  {
    PEAK_DETECTION_TEST_free(inputEnergyRef);
    inputEnergyRef= NULL;
  }

  profiler_deinit();

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}

char* moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '  ')||(LinePtr[0] == ',')) {
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

  CF_profile_init(3, "Peak_detection");

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
      status = readparamfile(configFile, &gsTokenMap_Peak_detection[0]);
      if(status == -1) {
        printf("Parser Failed");
        return -1 ;
      }

     /* Validate the kernel */
     if ( gConfig_Peak_detection.testType == 0 )
     {
       status = energyComputationTest(&gConfig_Peak_detection);
     }
     else
     {
       status = CFARCATest(&gConfig_Peak_detection);
     }


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

