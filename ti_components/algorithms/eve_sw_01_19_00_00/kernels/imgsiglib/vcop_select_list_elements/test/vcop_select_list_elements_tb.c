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
#include "vcop_select_list_elements_config.h"


#include "vcop_select_list_elements_cn.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_select_list_elements_kernel.k"
#else
#include "../inc/vcop_select_list_elements_kernel.h"
#endif

//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)

#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define CEIL(x,y) ((( x + y - 1) / y) * y)


static void CreatePattern(uint32_t * p, uint16_t listSize)
{
  int32_t i;

  for (i = 0; i < listSize; i++)
  {
#ifdef FIXEDPATTERN
    p[i] = (i);

#else
    p[i] = rand();
#endif
  }


}

void fillDefaultConfig(sSelect_list_elements_Config * params)
{
  strcpy(params->inputList, "");
  strcpy(params->outputList, "");

  params->listSize          = 1024;
  params->selectionMaskSize = 16;
  params->randSeed      = 0;
  params->numIter       = 1;
}

int32_t selectListElementsTest(sSelect_list_elements_Config * testcaseParams)
{
  int32_t fail, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;
  int32_t i,iter;
  uint32_t * inputListPtr  = NULL;
  uint32_t * outputListPtr = NULL;
  uint8_t  * selectionMaskPtr = NULL;
  uint32_t * outputListPtrRef = NULL;

  uint16_t * outputListSize = NULL;
  uint32_t outputListSizeRef;

  char    testcaseName[100];

  profiler_init();
  vcop_minit();

#if VCOP_HOST_EMULATION
  inputListPtr   = (uint32_t *)malloc((testcaseParams->listSize) * sizeof(uint32_t));
  outputListPtr  = (uint32_t *)malloc((testcaseParams->listSize) * sizeof(uint32_t));
  selectionMaskPtr  = (uint8_t *)malloc((testcaseParams->selectionMaskSize) * sizeof(uint8_t));
  outputListSize    = (uint16_t *)malloc( VCOP_SIMD_WIDTH * sizeof(uint16_t));

#else
  inputListPtr   = (uint32_t *)vcop_malloc(VCOP_IBUFLA,((testcaseParams->listSize) * sizeof(uint32_t)));
  outputListPtr  = (uint32_t *)vcop_malloc(VCOP_IBUFHA,((testcaseParams->listSize) * sizeof(uint32_t)));
  selectionMaskPtr  = (uint8_t *)vcop_malloc(VCOP_WMEM,((testcaseParams->selectionMaskSize) * sizeof(uint8_t)));
  outputListSize    = (uint16_t *)vcop_malloc(VCOP_IBUFHA, VCOP_SIMD_WIDTH * sizeof(uint16_t));

#endif

  outputListPtrRef  = (uint32_t *)malloc((testcaseParams->listSize) * sizeof(uint32_t));

  for(iter = 0; iter < testcaseParams->numIter; iter++)
  {
    printf("Iteration %d\n", iter);
    fail = 0;

    if(strcmp(testcaseParams->inputList , "")) {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->inputList, "rb");

      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", testcaseParams->inputList);
        return -1;
      }

      fread(inputListPtr, testcaseParams->listSize , sizeof(uint32_t), fp_in);
      fclose(fp_in);
    }
    else {
      /* Generate input data */
      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      CreatePattern(inputListPtr,
                    testcaseParams->listSize);

    }

    for ( i = 0; i < testcaseParams->selectionMaskSize; i++)
    {
      selectionMaskPtr[i] = rand() % 2;
    }

    strcpy(testcaseName, (char *)testcaseParams->testCaseName);
    strcat(testcaseName," Binary Masking");

    profiler_testCaseInfo((int8_t *)testcaseName,(int8_t *)" ",0);
    printparams(&gsTokenMap_select_list_elements[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(testcaseParams),sizeof(sSelect_list_elements_Config)) ;

    profiler_start();

    vcop_select_list_elements(inputListPtr,
                        outputListPtr,
                        selectionMaskPtr,
                        outputListSize,
                        testcaseParams->listSize,
                        testcaseParams->selectionMaskSize);

    profiler_end_print(1);

    vcop_select_list_elements_cn(inputListPtr,
                        outputListPtrRef,
                        selectionMaskPtr,
                        &outputListSizeRef,
                        testcaseParams->listSize,
                        testcaseParams->selectionMaskSize);


    fail = 0;

    if ( outputListSizeRef == *outputListSize)
    {
      fail = memcmp(outputListPtrRef, outputListPtr, outputListSizeRef);
    }
    else
    {
      fail = 1;
    }

    profiler_printStatus(fail);

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;
  }

#if !(VCOP_HOST_EMULATION)
  vcop_free(inputListPtr);
  vcop_free(outputListPtr);
  vcop_free(selectionMaskPtr);
  vcop_free(outputListSize);
#else
  if ( inputListPtr)
  {
    free(inputListPtr);
  }

  if(outputListPtr)
  {
    free(outputListPtr);
  }

  if(selectionMaskPtr)
  {
    free(selectionMaskPtr);
  }

  if(outputListSize)
  {
    free(outputListSize);
  }


#endif

  if(outputListPtrRef)
  {
    free(outputListPtrRef);
  }

  profiler_deinit();

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}


char* moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ',')) {
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

  CF_profile_init(3, "vcop_select_list_elements");

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
      status = readparamfile(configFile, &gsTokenMap_select_list_elements[0]);
      if(status == -1) {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel */
      status = selectListElementsTest(&gConfig_select_list_elements);

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

