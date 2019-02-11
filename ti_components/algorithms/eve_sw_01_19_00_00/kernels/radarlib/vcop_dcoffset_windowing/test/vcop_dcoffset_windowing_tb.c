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

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_dcoffset_windowing_config.h"


/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Sobel Xy kernel   */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_dcoffset_windowing_cn.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_dcoffset_windowing_kernel.k"
#else
#include "../inc/vcop_dcoffset_windowing_kernel.h"
#endif

#define FIXED_PATTERN (0)
//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)

#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define CEIL(x,y) ((( x + y - 1) / y) * y)

#define TRANSPOSE_STRIDE ( (VCOP_SIMD_WIDTH + 1 ) * 4 )

#if (VCOP_HOST_EMULATION)
#define DCOFFSET_WINDOWING_TEST_malloc(heap, size)   malloc(size)
#define DCOFFSET_WINDOWING_TEST_free(ptr)            free(ptr)
#else
#define DCOFFSET_WINDOWING_TEST_malloc(heap, size)   (vcop_malloc((heap), (size)))
#define DCOFFSET_WINDOWING_TEST_free(ptr)            (vcop_free(ptr))
#endif


void fillDefaultConfig(sDcoffset_windowing_Config * params)
{
  strcpy(params->inputData, "");
  strcpy(params->outData, "");

  params->numPoints = 1024;
  params->numLines = 8;
  params->interferenceThreshold = 12345;
  params->scaleFactor = 15;
  params->performanceTestcase  = 1;
  params->randSeed      = 0;
}

int32_t dcOffsetWindowingTest(sDcoffset_windowing_Config * testcaseParams)
{
  int32_t fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;
  FILE *fp_out = NULL;
  int32_t i, j;
  int16_t * inputData = NULL;
  int16_t * outputData = NULL;
  int16_t * inputDataRef = NULL;
  int16_t * outputDataRef = NULL;
  int32_t * scratchBuf = NULL;
  uint16_t * pScatterIndex = NULL;
  int16_t * winCoeffBuf = NULL;
  int16_t * dcOffsetBuf = NULL;
  int16_t * dcOffsetBufRef = NULL;
  char    testcaseName[100];
  uint16_t shift;
  uint16_t interimTransposeStride;
  uint16_t transposeStride;
  profiler_init();
  vcop_minit();

  if ( testcaseParams->numLines < VCOP_SIMD_WIDTH)
  {
    interimTransposeStride = ( (2* VCOP_SIMD_WIDTH) + 1 ) * sizeof(uint32_t);
    transposeStride        = ( (VCOP_SIMD_WIDTH) + 1 ) * sizeof(uint32_t);
  }
  else
  {
    interimTransposeStride = ((testcaseParams->numLines * 2) + 1) *   sizeof(uint32_t);
    transposeStride        = (((testcaseParams->numLines % 2)?testcaseParams->numLines :
                              testcaseParams->numLines + 1)) *   sizeof(uint32_t);
  }


  inputData   = (int16_t *) DCOFFSET_WINDOWING_TEST_malloc(VCOP_IBUFLA,(testcaseParams->numPoints)* testcaseParams->numLines * sizeof(int32_t));
  if ( inputData == NULL )
  {
    printf("Failed to allocate memory \n");
  }
  outputData   = (int16_t *) DCOFFSET_WINDOWING_TEST_malloc(VCOP_IBUFHA,(testcaseParams->numPoints)* transposeStride);
  scratchBuf    = (int32_t *)DCOFFSET_WINDOWING_TEST_malloc(VCOP_WMEM,( VCOP_SIMD_WIDTH * interimTransposeStride));
  dcOffsetBuf   = (int16_t *)DCOFFSET_WINDOWING_TEST_malloc(VCOP_WMEM,(sizeof(int32_t)) * testcaseParams->numLines );
  pScatterIndex = (uint16_t *)DCOFFSET_WINDOWING_TEST_malloc(VCOP_WMEM,(VCOP_SIMD_WIDTH * sizeof(int16_t)));
  winCoeffBuf   =  (int16_t *)DCOFFSET_WINDOWING_TEST_malloc(VCOP_WMEM,(testcaseParams->numPoints)* sizeof(int16_t));

  dcOffsetBufRef = (int16_t *)malloc((testcaseParams->numLines * sizeof(int32_t)));
  inputDataRef = (int16_t *)malloc((testcaseParams->numPoints *testcaseParams->numLines * sizeof(int32_t)));
  outputDataRef = (int16_t *)malloc((testcaseParams->numPoints *testcaseParams->numLines * sizeof(int32_t)));

  fail = 0;
  if(strcmp(testcaseParams->winCoeffData, ""))
  {
    printf("File Test\n");
    fp_in = fopen((const char *)testcaseParams->winCoeffData, "rb");

    if(fp_in == NULL) {
      printf("Failed to open input file: %s.\n", testcaseParams->winCoeffData);
      return -1;
    }

    fread(winCoeffBuf, testcaseParams->numPoints , sizeof(int16_t), fp_in);
    fclose(fp_in);
  }
  else
  {
    /* Generate input data */
    seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
    srand(seed+3);
    printf("Random pattern test: Seed = %d\n", seed + 3);
    for ( i = 0; i < testcaseParams->numPoints;i++)
    {
#if FIXED_PATTERN
      winCoeffBuf[i] = i;
#else
      winCoeffBuf[i] = rand();
#endif
    }
  }

  if(strcmp(testcaseParams->inputData, ""))
  {
    printf("File Test\n");
    fp_in = fopen((const char *)testcaseParams->inputData, "rb");

    if(fp_in == NULL) {
      printf("Failed to open input file: %s.\n", testcaseParams->inputData);
      return -1;
    }

    fread(inputData, testcaseParams->numPoints * testcaseParams->numLines , sizeof(uint32_t), fp_in);
    fclose(fp_in);
  }
  else
  {
    /* Generate input data */
    seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
    srand(seed);
    printf("Random pattern test: Seed = %d\n", seed);
    for ( i = 0; i < testcaseParams->numPoints * testcaseParams->numLines ;i++)
    {
#if FIXED_PATTERN
      inputData[2*i] = i;
      inputData[2*i + 1] = i+5;
#else
      inputData[2*i] = rand() % (1 << testcaseParams->numInBits);
      inputData[2*i + 1] = rand() % (1 << testcaseParams->numInBits);
#endif
    }
  }
  memcpy(inputDataRef, inputData, testcaseParams->numPoints * testcaseParams->numLines * sizeof(uint32_t));

  strcpy(testcaseName, (char *)testcaseParams->testCaseName);
  strcat(testcaseName," DC OFFSET WINDOWiNG");

  profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
  printparams(&gsTokenMap_Dcoffset_windowing[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sDcoffset_windowing_Config)) ;

  shift = log((double)testcaseParams->numPoints)/ log (2.0);

  fail = 0;

  profiler_start();
  vcop_sign_extension_kernel((uint16_t*)inputData,
                     outputData,
                     testcaseParams->numPoints,
                     testcaseParams->numLines,
                     testcaseParams->numPoints * sizeof(int16_t) * 2U,
                     (testcaseParams->numInBits)
                     );
  profiler_end_print(1);

  vcop_sign_extension_cn((uint16_t *)inputDataRef,
                     outputDataRef,
                     testcaseParams->numPoints,
                     testcaseParams->numLines,
                     testcaseParams->numPoints * sizeof(int16_t) * 2U,
                     (testcaseParams->numInBits)
                     );

  for ( j = 0; j <testcaseParams->numLines ;j++)
  {
    for ( i = 0; i < testcaseParams->numPoints; i++)
    {
      if ( (outputData[2 * (i + j * testcaseParams->numPoints)] != outputDataRef[2 * (i + j * testcaseParams->numPoints)]) ||
            (outputData[2 * (i + j * testcaseParams->numPoints) + 1] != outputDataRef[2 * (i + j * testcaseParams->numPoints) + 1]))
      {
        fail = 1;
        break;
      }
    }
    if ( fail == 1)
    {
      break;
    }
  }
  if ( fail != 0 )
   {
     printf("vcop_sign_extension_kernel is not working at %d %d : FAIL\n", i , j);
   }

  profiler_start();

  vcop_interference_zero_out_kernel(inputData,
                     outputData,
                     testcaseParams->interferenceThreshold,
                     testcaseParams->numPoints,
                     testcaseParams->numLines,
                     testcaseParams->numPoints * sizeof(int16_t) * 2U
                     );

  profiler_end_print(1);

  vcop_interference_zero_out_cn(inputDataRef,
                   inputDataRef,
                   testcaseParams->interferenceThreshold,
                   testcaseParams->numPoints,
                   testcaseParams->numLines,
                   testcaseParams->numPoints * sizeof(int16_t) * 2U
                   );


  fail |= memcmp(outputData, inputDataRef, testcaseParams->numLines * testcaseParams->numPoints * sizeof(int32_t));
  if ( fail != 0 )
  {
    printf("vcop_interference_zero_out_kernel is not working : FAIL\n");
  }

  for ( i = 0 ; i < 8 ; i++)
  {
    pScatterIndex[i] = interimTransposeStride * i;
  }


  profiler_start();

  vcop_dcoffset_kernel(outputData,
                      scratchBuf,
                      pScatterIndex,
                      dcOffsetBuf,
                      interimTransposeStride,
                      testcaseParams->numPoints,
                      testcaseParams->numLines,
                      shift
                      );

  profiler_end_print(1);

  vcop_dcoffset_cn(inputDataRef,
                    dcOffsetBufRef,
                    testcaseParams->numPoints,
                    testcaseParams->numLines
                    );


  for ( i = 0; i < testcaseParams->numLines ; i++)
  {
    if ( (dcOffsetBuf[2 * i] != dcOffsetBufRef[2 * i]) || (dcOffsetBuf[2 * i + 1] != dcOffsetBufRef[2 * i + 1]))
    {
      fail |= 1;
      printf("DC Offset Output Not matching for line %d : FAIL \n", i);
      break;
    }
  }

  memcpy ( inputData, outputData, sizeof(int16_t) * 2 * testcaseParams->numPoints * testcaseParams->numLines);

  profiler_start();

  vcop_windowing_kernel(inputData,/*Input Ptr */
                     winCoeffBuf,
                     dcOffsetBuf,
                     outputData,/*Output Ptr */
                     testcaseParams->numPoints,
                     testcaseParams->numLines,
                     testcaseParams->scaleFactor,
                     32768,
                     testcaseParams->numPoints * sizeof(int16_t) * 2
                     );

  profiler_end_print(1);

  vcop_windowing_cn(inputDataRef,/*Input Ptr */
                    winCoeffBuf,
                    dcOffsetBuf,
                   outputDataRef,/* Output Ptr */
                   testcaseParams->numPoints,
                   testcaseParams->numLines,
                   testcaseParams->scaleFactor,
                   32768,
                   testcaseParams->numPoints * sizeof(int16_t) * 2
                   );


  for ( i = 0; i < testcaseParams->numLines * testcaseParams->numPoints; i++)
  {
    if ( (outputDataRef[2 * i] != outputData[2 * i]) || (outputDataRef[2 * i + 1] != outputData[2 * i + 1]))
    {
      fail |= 1;
      printf("windowing output in not matching at line %d point %d : FAIL \n",
            i % testcaseParams->numPoints,
            i - (i / testcaseParams->numPoints)* testcaseParams->numPoints);
      break;
    }
  }

  for ( i = 0 ; i < 8 ; i++)
  {
    pScatterIndex[i] = transposeStride * i;
  }

  profiler_start();
  vcop_windowing_with_transpose_kernel(inputData,/*Input Ptr */
                     winCoeffBuf,
                     outputData,/*Output Ptr */
                     pScatterIndex,
                     transposeStride,
                     testcaseParams->numPoints,
                     testcaseParams->numLines,
                     testcaseParams->scaleFactor,
                     32768
                     );

  profiler_end_print(1);

  vcop_windowing_with_transpose_cn(inputDataRef,/*Input Ptr */
                    winCoeffBuf,
                   outputDataRef,/* Output Ptr */
                   testcaseParams->numPoints,
                   testcaseParams->numLines,
                   testcaseParams->scaleFactor,
                   32768,
                   testcaseParams->numLines * sizeof(int16_t) * 2U
                   );

  for ( j = 0; j < testcaseParams->numLines; j++)
  {
    for ( i = 0; i < testcaseParams->numPoints; i++)
    {
      if ( (outputDataRef[2 * (i * testcaseParams->numLines + j )] != outputData[2 * (j + i * transposeStride/sizeof(int32_t))]) ||
        (outputDataRef[2 * (j + i * testcaseParams->numLines ) + 1] != outputData[2 * (j + i * transposeStride/sizeof(int32_t)) + 1]))
      {
        fail |= 1;
        printf("windowing output in not matching at line %d point %d : FAIL\n",
              i % testcaseParams->numPoints,
              i - (i / testcaseParams->numPoints)* testcaseParams->numPoints);
        break;
      }
    }
  }

  printf(fail ? "FAIL\n":"PASS\n");
  status |= fail;

  profiler_printStatus(fail);

  if(strcmp(testcaseParams->outData, "")) {
    fp_out = fopen((const char *)testcaseParams->outData, "rb");

    if(fp_out == NULL) {
      printf("Failed to open input file: %s.\n", testcaseParams->outData);
      return -1;
    }

    fwrite(inputData, testcaseParams->numLines, sizeof(uint32_t), fp_in);
    fclose(fp_out);
  }



  if ( inputData)
  {
    DCOFFSET_WINDOWING_TEST_free(inputData);
  }
  if ( outputData)
  {
    DCOFFSET_WINDOWING_TEST_free(outputData);
  }
  if ( scratchBuf)
  {
    DCOFFSET_WINDOWING_TEST_free(scratchBuf);
  }
  if ( dcOffsetBuf)
  {
    DCOFFSET_WINDOWING_TEST_free(dcOffsetBuf);
  }
  if ( winCoeffBuf)
  {
    DCOFFSET_WINDOWING_TEST_free(winCoeffBuf);
  }
  if ( pScatterIndex)
  {
    DCOFFSET_WINDOWING_TEST_free(pScatterIndex);
  }

  if ( dcOffsetBufRef)
  {
    free(dcOffsetBufRef);
  }

  if ( inputDataRef)
  {
    free(inputDataRef);
  }

  if ( outputDataRef)
  {
    free(outputDataRef);
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

  CF_profile_init(3, "Dcoffset_windowing");

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
      status = readparamfile(configFile, &gsTokenMap_Dcoffset_windowing[0]);
      if(status == -1) {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel */
      status = dcOffsetWindowingTest(&gConfig_Dcoffset_windowing);

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

