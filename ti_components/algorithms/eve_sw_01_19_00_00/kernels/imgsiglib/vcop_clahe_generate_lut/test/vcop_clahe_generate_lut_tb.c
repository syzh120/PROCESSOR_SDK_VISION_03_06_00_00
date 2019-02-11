/*
*
* Copyright (c) 2015-2017 Texas Instruments Incorporated
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
#include <stdint.h>
#include <math.h>
#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_clahe_generate_lut_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct
{
  char dataInFile[MAX_FILE_NAME_SIZE];
  char lutFile[MAX_FILE_NAME_SIZE];
  char dataOutFile[MAX_FILE_NAME_SIZE];
  int  width;
  int  height;
  int  clipValue;
  int  lutScale;
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
  {(char* )"dataInFile",                &(gParams.dataInFile)                 , STRING, SINGLE},
  {(char* )"lutFile",                   &(gParams.lutFile)                    , STRING, SINGLE},
  {(char* )"width",                     &gParams.width                        , INT_32, SINGLE},
  {(char* )"height",                    &gParams.height                       , INT_32, SINGLE},
  {(char* )"clipValue",                 &gParams.clipValue                        , INT_32, SINGLE},
  {(char* )"lutScale",                  &gParams.lutScale                       , INT_32, SINGLE},
  {(char* )"writeOutput",               &gParams.writeOutput                  , INT_32, SINGLE},
  {(char* )"seedForRND",                &gParams.seedForRND                   , INT_32, SINGLE},
  {(char *)"testCaseName",              &gParams.testCaseName                 , STRING, SINGLE},
} ;

#define COMPARE_REFERENCE

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_clahe_generate_lut_kernel.k"
#else
#include "vcop_clahe_generate_lut_kernel.h"
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
  params->width        = 32;
  params->height       = 32;
  params->clipValue    = ((params->width*params->height)*2)/256;
  params->lutScale     = ((256 - 1)*(0xFFFFU)) / (params->width*params->height);


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

static int readInputFromTxtFile(unsigned char * grad, unsigned short n, char * fileName)
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

static void CreateRandPatternU8(unsigned char *ptr, unsigned short n)
{
  int i;
  short val;
  for(i = 0; i < n; i++)
  {
    val = rand() & 0xFF;
    ptr[i] =  val;
  }
}


int test_bench(config_params * params)
{
  unsigned char * dataInPtr  ;
  unsigned char * lutPtrRef  ;
  unsigned char * lutPtr  ;
  unsigned int * histPtr  ;
  unsigned int * hist8WayPtr  ;
  unsigned int * histTempPtr  ;
  unsigned int * wbuf_scratch  ;
  unsigned short * wbuf_dist    ;
  unsigned short * wbuf_res     ;
  unsigned short * wbuf_enble  ;
  uint16_t txf,tyf,histSize;

  int fail,i;
  profiler_init();
  fail = 0;
  histSize = 256;

#if VCOP_HOST_EMULATION
  dataInPtr        = (unsigned char *)malloc(params->width *params->height);
  lutPtr           = (unsigned char *)malloc(256);
  histPtr          = (unsigned int *)malloc(256*4);
  hist8WayPtr      = (unsigned int *)malloc(256*4*8);
  histTempPtr      = (unsigned int *)malloc(8*sizeof(uint32_t)*((256/8)*9));
  wbuf_scratch     = (unsigned int *)malloc(4*8);
  wbuf_dist        = (unsigned short *)malloc(4);
  wbuf_res         = (unsigned short *)malloc(4);
  wbuf_enble       = (unsigned short *)malloc(4);
#else
  dataInPtr        = (unsigned char *)vcop_malloc(VCOP_IBUFLA,params->width *params->height);
  lutPtr           = (unsigned char *)vcop_malloc(VCOP_IBUFLA,256);
  histPtr          = (unsigned int  *)vcop_malloc(VCOP_IBUFLA,256*4);
  hist8WayPtr      = (unsigned int  *)vcop_malloc(VCOP_WMEM,256*4*8);
  histTempPtr      = (unsigned int  *)vcop_malloc(VCOP_IBUFHA,8*sizeof(uint32_t)*((256/8)*9));
  wbuf_scratch     = (unsigned int  *)vcop_malloc(VCOP_WMEM,4*8);
  wbuf_dist        = (unsigned short  *)vcop_malloc(VCOP_WMEM,4);
  wbuf_res         = (unsigned short  *)vcop_malloc(VCOP_WMEM,4);
  wbuf_enble       = (unsigned short  *)vcop_malloc(VCOP_WMEM,4);
#endif
  lutPtrRef           = (unsigned char *)malloc(256);

  if(strcmp(params->inputSrc, "RND_PTRN")==0)
  {
    printf("Pattern Generation Seed = %d\n", params->seedForRND);
    srand(params->seedForRND);
    CreateRandPatternU8(dataInPtr, params->width*params->height);
  }
  else if(strcmp(params->inputSrc, "TXT_FILE")==0)
  {
    readInputFromTxtFile(dataInPtr, params->width*params->height, params->dataInFile);
  }

#ifdef COMPARE_REFERENCE
  memset(histPtr,0, 4*histSize);
  vcop_clahe_histogram_cn(dataInPtr,params->width, params->height,params->width,histPtr);
  vcop_clahe_clip_hist_cn(histPtr,wbuf_scratch,wbuf_res, wbuf_dist, wbuf_enble,histSize,params->clipValue);
  wbuf_res[0] += 1;
  vcop_clahe_generate_lut_cn(histPtr,lutPtrRef,params->lutScale,histSize,wbuf_dist[0], wbuf_res[0], wbuf_enble[0]);
#endif
  profiler_start();

  vcop_clahe_memset((uint32_t*)hist8WayPtr, 0, 4*256*8);
  vcop_clahe_histogram_8c_word(dataInPtr,params->width, params->height,params->width,hist8WayPtr);
  vcop_clahe_histogram_8c_word_sum(hist8WayPtr,histTempPtr,histPtr);
  vcop_clahe_clip_hist(histPtr,wbuf_scratch, wbuf_res, wbuf_dist, wbuf_enble, histSize, params->clipValue);
  wbuf_res[0] += 1;
  vcop_clahe_generate_lut(histPtr, lutPtr, params->lutScale, histSize, wbuf_dist[0], wbuf_res[0], wbuf_enble[0]);

  profiler_end_print(1);
  profiler_performanceParam(params->width * params->height);

#ifdef COMPARE_REFERENCE

  fail = memcmp(lutPtr,lutPtrRef,histSize);
  profiler_printStatus(fail);

  if(fail != 0)
  {
    for(i = 0; i < histSize; i++)
    {
      printf("At %3d = %9d:%9d",i,lutPtrRef[i], lutPtr[i]);
      if(lutPtrRef[i] != lutPtr[i])
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
    writeOutputToTxtFile(histSize,lutPtr,params->lutFile);
  }

 #if VCOP_HOST_EMULATION
  free(dataInPtr     );   
  free(lutPtr        );   
  free(histPtr       );   
  free(hist8WayPtr   );   
  free(histTempPtr   );   
  free(wbuf_dist     );   
  free(wbuf_scratch  );   
  free(wbuf_res      );   
  free(wbuf_enble    );   
#else
  vcop_free(dataInPtr    );  
  vcop_free(lutPtr       );  
  vcop_free(histPtr      );  
  vcop_free(hist8WayPtr  );  
  vcop_free(histTempPtr  );  
  vcop_free(wbuf_dist    );  
  vcop_free(wbuf_scratch );  
  vcop_free(wbuf_res     );  
  vcop_free(wbuf_enble   );  
#endif  
  free(lutPtrRef    );   

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
  CF_profile_init(2, "vcop_clahe_generate_lut");

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
      CF_formula_add_test(params->width*params->height, NULL, NULL,  NULL, 0, NULL , 1);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  CF_profile_setMode(2, 1);
  CF_profile_cycle_report(CF_PROFILE_FORMULA_RANGE,"N = Number of Pixels;");

  fclose(fp);
  return (0);

}
