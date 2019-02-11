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
#include "vcop_beam_forming_config.h"


/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Beam Forming kernel   */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_beam_forming_cn.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_beam_forming_kernel.k"
#else
#include "../inc/vcop_beam_forming_kernel.h"
#endif

#define FIXED_PATTERN (0)
//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)

#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define CEIL(x,y) ((( x + y - 1) / y) * y)

#define MAX_NUM_DETECTIONS (2048)


#if (VCOP_HOST_EMULATION)
#define BEAM_FORMING_TEST_malloc(heap, size)   malloc(size)
#define BEAM_FORMING_TEST_free(ptr)            free(ptr)
#else
#define BEAM_FORMING_TEST_malloc(heap, size)   (vcop_malloc((heap), (size)))
#define BEAM_FORMING_TEST_free(ptr)            (vcop_free(ptr))
#endif


void fillDefaultConfig(sBeam_forming_Config * params)
{
  strcpy(params->inputData, "");
  strcpy(params->outData, "");
  strcpy(params->steeringMatrix, "");

  params->numDetections = 8;
  params->numAntennas   = 12;
  params->numAngles     = 324;
  params->performanceTestcase  = 1;
  params->randSeed      = 0;
}

int32_t beamFormingTest(sBeam_forming_Config * testcaseParams)
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
  int16_t * steeringMatrixBuf = NULL;
  uint32_t * outputEnergyRef = NULL;
  uint32_t * outputEnergy= NULL;
  uint16_t * angleBuf = NULL;
  uint16_t * maxEnergyBuf = NULL;
  uint16_t * angleBufRef = NULL;
  uint16_t * maxEnergyBufRef = NULL;
  uint16_t * detectionIdPtr = NULL;
  char    testcaseName[100];
  uint16_t shift;

  profiler_init();
  vcop_minit();

  /* Allocate worst case input and output buffers so that we can re-use buffers for different kernels*/
  /* Correct amount to allocate is ((testcaseParams->numDetections)* testcaseParams->numAntennas * sizeof(int32_t)) */
  inputData   = (int16_t *) BEAM_FORMING_TEST_malloc(VCOP_IBUFLA, 16300U);
  inputDataRef = (int16_t *)malloc(16300U);
  if ( inputData == NULL )
  {
    printf("Failed to allocate memory \n");
  }
  /* Correct amount to allocate is (testcaseParams->numDetections) * (testcaseParams->numAngles)* sizeof(int32_t)) */
  outputData   = (int16_t *) BEAM_FORMING_TEST_malloc(VCOP_IBUFHA,16300U);
  outputDataRef = (int16_t *)malloc(16300U);

  steeringMatrixBuf    = (int16_t  *)BEAM_FORMING_TEST_malloc(VCOP_WMEM,( (testcaseParams->numAngles) * (testcaseParams->numAntennas) * sizeof(int32_t)));
  angleBuf = (uint16_t  *)BEAM_FORMING_TEST_malloc(VCOP_WMEM,( (testcaseParams->numDetections) * sizeof(uint16_t)));
  maxEnergyBuf         = (uint16_t  *)BEAM_FORMING_TEST_malloc(VCOP_WMEM,( (testcaseParams->numDetections) * sizeof(uint16_t)));
  detectionIdPtr   = (uint16_t  *)BEAM_FORMING_TEST_malloc(VCOP_WMEM,( MAX_NUM_DETECTIONS * sizeof(uint16_t)));

  angleBufRef = (uint16_t *)malloc(( (testcaseParams->numDetections) * sizeof(uint16_t)));
  maxEnergyBufRef         = (uint16_t *)malloc(( (testcaseParams->numDetections) * sizeof(uint32_t)));


  fail = 0;
  if(strcmp(testcaseParams->steeringMatrix, ""))
  {
    printf("File Test\n");
    fp_in = fopen((const char *)testcaseParams->steeringMatrix, "rb");

    if(fp_in == NULL) {
      printf("Failed to open input file: %s.\n", testcaseParams->steeringMatrix);
      return -1;
    }

    fread(steeringMatrixBuf, ( (testcaseParams->numAngles) * (testcaseParams->numAntennas) * sizeof(int32_t)), 1, fp_in);
    fclose(fp_in);
  }
  else
  {
    /* Generate input data */
    seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
    srand(seed+3);
    printf("Random pattern test: Seed = %d\n", seed + 3);
    for ( i = 0; i < testcaseParams->numAngles;i++)
    {
      for ( j = 0; j < testcaseParams->numAntennas;j++)
      {
#if FIXED_PATTERN
      steeringMatrixBuf[2 * (j + i * testcaseParams->numAntennas)] = i;
      steeringMatrixBuf[2 * (j + i * testcaseParams->numAntennas) + 1] = j;
#else
      steeringMatrixBuf[2 * (j + i * testcaseParams->numAntennas)] = rand() % 8192;
      steeringMatrixBuf[2 * (j + i * testcaseParams->numAntennas) + 1] = rand() % 8192;
#endif
      }
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

    fread(inputData, testcaseParams->numDetections * testcaseParams->numAntennas, sizeof(uint32_t), fp_in);
    fclose(fp_in);
  }
  else
  {
    /* Generate input data */
    seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
    srand(seed);
    printf("Random pattern test: Seed = %d\n", seed);
    for ( i = 0; i < testcaseParams->numDetections * testcaseParams->numAntennas ;i++)
    {
#if FIXED_PATTERN
      inputData[2*i] = i;
      inputData[2*i + 1] = i+5;
#else
      /* Limit input to smaller range to avoid overflow */
      inputData[2*i] = rand() % 8192;
      inputData[2*i + 1] = rand() % 8192;
#endif
    }
  }
  memcpy(inputDataRef, inputData, testcaseParams->numDetections * testcaseParams->numAntennas * sizeof(uint32_t));

  strcpy(testcaseName, (char *)testcaseParams->testCaseName);
  strcat(testcaseName," BEAM FORMING KERNELS");

  profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
  printparams(&gsTokenMap_Beam_forming[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sBeam_forming_Config)) ;

  shift = 15;
  profiler_start();

  vcop_beam_forming_kernel(inputData,
                           outputData,
                           steeringMatrixBuf,
                           testcaseParams->pitch,
                           testcaseParams->numDetections,
                           testcaseParams->numAntennas,
                           testcaseParams->numAngles,
                           shift);


  profiler_end_print(1);

  vcop_beam_forming_cn(inputDataRef,
                   outputDataRef,
                   steeringMatrixBuf,
                   testcaseParams->pitch,
                   testcaseParams->numDetections,
                   testcaseParams->numAntennas,
                   testcaseParams->numAngles,
                   shift
                   );

  fail = 0;


  fail = memcmp(outputData, outputDataRef, testcaseParams->numDetections * testcaseParams->numAngles * sizeof(int32_t));
  if ( fail != 0 )
  {
    for ( i = 0; i < testcaseParams->numAngles; i++)
    {
      for ( j = 0; j < testcaseParams->numDetections; j++)
      {
        if ( ( outputData[2 *(j + i * testcaseParams->numDetections)] != outputDataRef[2 *(j + i * testcaseParams->numDetections)] ) ||
             ( outputData[2 *(j + i * testcaseParams->numDetections) + 1] != outputDataRef[2 *(j + i * testcaseParams->numDetections) + 1] ))
        {
          printf("Output of vcop_beam_forming_kernel is not matching at detection %d, for angle %d \n",j , i );
        }
      }
    }
    printf("vcop_beam_forming_kernel is not working \n");
  }
  else
  {
    printf("vcop_beam_forming_kernel is working : PASSED \n");
  }

  /* Re-use already allocated buffer */
  outputEnergy = (uint32_t*)inputData;
  outputEnergyRef = (uint32_t *)inputDataRef;

  shift = 24;

  profiler_start();

  vcop_beam_energy_calculation_kernel(outputData,
                          outputEnergy,
                          testcaseParams->numDetections,
                          testcaseParams->numAngles);


  profiler_end_print(1);

  vcop_beam_energy_calculation_cn(outputDataRef,
                  outputEnergyRef,
                  testcaseParams->numDetections,
                  testcaseParams->numAngles
                  );

  fail |= memcmp(outputEnergy, outputEnergyRef, testcaseParams->numDetections * testcaseParams->numAngles * sizeof(int16_t));
  if ( fail != 0 )
  {
    for ( i = 0; i < testcaseParams->numAngles; i++)
    {
      for ( j = 0; j < testcaseParams->numDetections; j++)
      {
        if ( ( outputEnergy[(j + i * testcaseParams->numDetections)] != outputEnergyRef[(j + i * testcaseParams->numDetections)] ) ||
             ( outputEnergy[(j + i * testcaseParams->numDetections) + 1] != outputEnergyRef[(j + i * testcaseParams->numDetections) + 1] ))
        {
          printf("Output of vcop_beam_energy_calculation_kernel is not matching at detection %d, for angle %d \n",j , i );
        }
      }
    }
    printf("vcop_beam_energy_calculation_kernel is not working \n");
  }
  else
  {
    printf("vcop_beam_energy_calculation_kernel is working : PASSED \n");
  }


  for ( i = 0; i < MAX_NUM_DETECTIONS; i++)
  {
    detectionIdPtr[i] = i;
  }
  profiler_start();

  vcop_beam_angle_association_kernel(outputEnergy,
                          angleBuf,
                          maxEnergyBuf,
                          NULL,
#if !VCOP_HOST_EMULATION
                          (uint32_t *)__pblock_vcop_beam_angle_association_kernel,
#else
                          0,
#endif
                          0,
                          testcaseParams->numDetections,
                          testcaseParams->numAngles,
                          shift/*eneryScaling*/);


  profiler_end_print(1);

  vcop_beam_angle_association_cn(outputEnergyRef,
                          angleBufRef,
                          maxEnergyBufRef,
                          0,
                          testcaseParams->numDetections,
                          testcaseParams->numAngles,
                          shift/*eneryScaling*/);

  fail |= memcmp(angleBufRef, angleBuf, testcaseParams->numDetections * sizeof(int16_t));
  fail |= memcmp(maxEnergyBufRef, maxEnergyBuf, testcaseParams->numDetections * sizeof(int16_t));

  if ( fail != 0 )
  {
     for ( j = 0; j < testcaseParams->numDetections; j++)
     {
       if ( ( angleBufRef[(j)] != angleBuf[(j)] ) ||
            ( maxEnergyBufRef[(j)] != maxEnergyBuf[(j)] ))
       {
         printf("Output of vcop_beam_energy_calculation_kernel is not matching at detection %d\n",j);
       }
     }

 }
 else
 {
   printf("vcop_beam_angle_association_kernel is working : PASSED \n");
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

    fwrite(inputData, testcaseParams->numAngles * testcaseParams->numDetections, sizeof(uint32_t), fp_in);
    fclose(fp_out);
  }



  if ( inputData)
  {
    BEAM_FORMING_TEST_free(inputData);
  }
  if ( outputData)
  {
    BEAM_FORMING_TEST_free(outputData);
  }
  if ( steeringMatrixBuf)
  {
    BEAM_FORMING_TEST_free(steeringMatrixBuf);
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

  CF_profile_init(3, "Beam_forming");

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
      status = readparamfile(configFile, &gsTokenMap_Beam_forming[0]);
      if(status == -1) {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel */
      status = beamFormingTest(&gConfig_Beam_forming);

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

