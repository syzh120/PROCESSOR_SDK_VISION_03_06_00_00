/*
*
* Copyright (c) 2014-2017 Texas Instruments Incorporated
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
#include <string.h>
#include <math.h>
#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_orientation_binning_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct
{
  char gradXFile[MAX_FILE_NAME_SIZE];
  char gradYFile[MAX_FILE_NAME_SIZE];
  char outFileName[MAX_FILE_NAME_SIZE];
  int  numBins;
  int  width;
  int  height;
  int  writeOutput;
  int  seedForRND;
  char inputSrc[MAX_PARAM_STRING_SIZE];
  char testCaseName[MAX_FILE_NAME_SIZE];
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];

} config_params;

config_params gParams ;


sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                  &(gParams.inputSrc)                   , STRING, SINGLE},
  {(char* )"gradXFile",                 &(gParams.gradXFile)                  , STRING, SINGLE},
  {(char* )"gradYFile",                 &(gParams.gradYFile)                  , STRING, SINGLE},
  {(char* )"outFileName",               &(gParams.outFileName)                , STRING, SINGLE},
  {(char* )"numBins",                   &gParams.numBins                        , INT_32, SINGLE},
  {(char* )"width",                     &gParams.width                        , INT_32, SINGLE},
  {(char* )"height",                    &gParams.height                       , INT_32, SINGLE},
  {(char* )"writeOutput",               &gParams.writeOutput                  , INT_32, SINGLE},
  {(char* )"seedForRND",                &gParams.seedForRND                   , INT_32, SINGLE},
  {(char *)"testCaseName",              &gParams.testCaseName                 , STRING, SINGLE},
} ;

#define COMPARE_REFERENCE

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_orientation_binning_kernel.k"
#else
#include "vcop_orientation_binning_kernel.h"
#endif

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}
void fillDefaultConfig(config_params * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->writeOutput  = 0;
  params->numBins      = 6;
  params->width        = 32;
  params->height       = 32;
  params->seedForRND   = 0xABDC1234;
  strcpy(params->testCaseName, " ");
}
static int writeOutputToTxtFile(unsigned short n, unsigned char * ptr1, char * fileName)
{
  int i;
  FILE * fp;
  fp = fopen(fileName, "w+");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(i = 0; i < n; i++)
  {
    fprintf(fp,"%d\n",ptr1[i]);
  }
  fclose(fp);
  return(0);
}

static int readInputFromTxtFile(short * grad, unsigned short n, char * fileName)
{
  int k;
  FILE * fp;
  int status;
  int value;
  char inputLine[MAX_INPUT_LINE_SIZE];

  fp = fopen(fileName, "r");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(k = 0; k < n; k++)
  {
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    sscanf(inputLine, "%d",&value);
    grad[k] = value;
  }
  fclose(fp);
  return(0);
}

static void CreateRandPatternS9(short *grad, unsigned short n)
{
  int i;
  short val;
  for(i = 0; i < n; i++)
  {
    val = rand() & 0xFF;
    grad[i] = (rand()&1) ? val : -val;
  }
}

#define TB_PI       3.14159265358979323846

int test_bench(config_params * params)
{
  short * gradX  ;
  short * gradY  ;
  unsigned char * absBradX  ;
  unsigned char * absBradY  ;
  short * wSinTab;
  short * wCosTab;
  unsigned char  * outBin;
  unsigned char  * refOut;
  float startAngle = (TB_PI/(params->numBins*2));

  int fail,i;
  profiler_init();
  fail = 0;

#if VCOP_HOST_EMULATION
  absBradX   = (unsigned char *)malloc(params->width *params->height);
  absBradY   = (unsigned char *)malloc(params->width *params->height);
  gradY      = (short *)malloc(params->width *params->height*2);
  gradX      = (short *)malloc(params->width *params->height*2);
  gradY      = (short *)malloc(params->width *params->height*2);
  wSinTab    = (short *)malloc(params->numBins*4);
  wCosTab    = (short *)malloc(params->numBins*4);
  outBin     = (unsigned char *)malloc(params->width *params->height);
#else
  absBradX   = (unsigned char *)vcop_malloc(VCOP_IBUFLA,params->width *params->height);
  absBradY   = (unsigned char *)vcop_malloc(VCOP_IBUFHA,params->width *params->height);
  gradX      = (signed short *)vcop_malloc(VCOP_IBUFLA,params->width *params->height*2);
  gradY      = (signed short *)vcop_malloc(VCOP_IBUFHA,params->width *params->height*2);
  wSinTab    = (signed short *)vcop_malloc(VCOP_WMEM,  params->numBins*4);
  wCosTab    = (signed short *)vcop_malloc(VCOP_WMEM,  params->numBins*4);
  outBin     = (unsigned char *)vcop_malloc(VCOP_WMEM,  params->width *params->height);
#endif
  refOut     = (unsigned char *)malloc(params->width *params->height);

  if(strcmp(params->inputSrc, "RND_PTRN")==0)
  {
    printf("Pattern Generation Seed = %d\n", params->seedForRND);
    srand(params->seedForRND);
    CreateRandPatternS9(gradX, params->width*params->height);
    CreateRandPatternS9(gradY, params->width*params->height);

  }
  else if(strcmp(params->inputSrc, "TXT_FILE")==0)
  {
    readInputFromTxtFile(gradX, params->width*params->height, params->gradXFile);
    readInputFromTxtFile(gradY, params->width*params->height, params->gradYFile);
  }

  for(i = 0; i < params->numBins; i++)
  {
    wSinTab[i] = sin((i*(TB_PI/(params->numBins))) + startAngle) * (1 << 14);
    wCosTab[i] = cos((i*(TB_PI/(params->numBins))) + startAngle) * (1 << 14);
  }

#ifdef COMPARE_REFERENCE
  vcop_orientation_binning_cn(gradX, gradY, refOut, wSinTab, wCosTab, params->numBins, params->width, params->height, params->width);
#endif
  profiler_start();

  if(params->numBins & 1)
  {
    vcop_orientation_binning(gradX, gradY, outBin, wSinTab, wCosTab, params->numBins, params->width, params->height, params->width);
  }
  else
  {
    vcop_orientation_binning_even(gradX, gradY, absBradX, absBradY, outBin, wSinTab, wCosTab, params->numBins, params->width, params->height, params->width);
  }

  profiler_end_print(1);
  profiler_performanceParam(params->width * params->height);

#ifdef COMPARE_REFERENCE

  fail = memcmp(outBin,refOut,params->height*params->width);
  profiler_printStatus(fail);

  if(fail != 0)
  {
    for(i = 0; i < params->height*params->width; i++)
    {
      printf("At %3d - Bin = %9d:%9d %9d:%9d",i,outBin[i], refOut[i], gradX[i], gradY[i]);
      if(outBin[i] != refOut[i])
      {
        printf("*******\n");
      }
      else
      {
        printf("\n");
      }
    }
  }

#endif

  profiler_deinit();

  if(params->writeOutput)
  {
    writeOutputToTxtFile(params->height*params->width,outBin,params->outFileName);
  }

  return (0);
}

int main()
{


  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  config_params * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  params = (config_params *)(&gParams);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Runing in defult mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_bench(params);
    return(0);
  }
  CF_profile_init(3, "vcop_orientation_binning");

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf(LinePtr, "%d",&config_cmd);
    sscanf(LinePtr, "%s",params->configParam);
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
      LinePtr = moveToNextElement(params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile(configFileName, &gsTokenMap_sof[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)" ",0);
      printparams(&gsTokenMap_sof[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(params),sizeof(config_params)) ;
      test_bench(params);
      CF_formula_add_test((params->width * params->height), params->numBins, NULL,  NULL, 0, NULL , 1);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  CF_profile_setMode(3, 1);
  CF_profile_cycle_report(CF_PROFILE_FORMULA_RANGE,"N = num pixels; M = numBins");

  fclose(fp);
  return (0);

}
