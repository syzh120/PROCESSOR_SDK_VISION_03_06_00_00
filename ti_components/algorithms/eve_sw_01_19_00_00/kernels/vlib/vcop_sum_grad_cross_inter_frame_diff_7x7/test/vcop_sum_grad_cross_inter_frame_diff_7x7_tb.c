/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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
#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_sum_grad_cross_inter_frame_diff_7x7_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct 
{
  char gradXName[MAX_FILE_NAME_SIZE];
  char gradYName[MAX_FILE_NAME_SIZE];
  char currImName[MAX_FILE_NAME_SIZE];
  char prevImName[MAX_FILE_NAME_SIZE];
  char outFileName[MAX_FILE_NAME_SIZE];
  int  numKeyPoints;
  int  writeOutput;
  int seedForRND;
  char inputSrc[MAX_PARAM_STRING_SIZE];
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];

} config_params;

config_params gParams ;


sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] = 
{
  {(char* )"inputSrc",                  &(gParams.inputSrc)                   , STRING, SINGLE},                    
  {(char* )"gradXName",                 &(gParams.gradXName)                  , STRING, SINGLE},                    
  {(char* )"gradYName",                 &(gParams.gradYName)                  , STRING, SINGLE},                    
  {(char* )"currImName",                &(gParams.currImName)                 , STRING, SINGLE},                    
  {(char* )"prevImName",                &(gParams.prevImName)                 , STRING, SINGLE},                    
  {(char* )"outFileName",               &(gParams.outFileName)                , STRING, SINGLE},                    
  {(char* )"numKeyPoints",              &gParams.numKeyPoints                 , INT_32, SINGLE},                    
  {(char* )"writeOutput",               &gParams.writeOutput                  , INT_32, SINGLE},                    
  {(char* )"seedForRND",                &gParams.seedForRND                   , INT_32, SINGLE},                    
} ;

#define COMPARE_REFERENCE
#define NUM_ITER (1)


#define BLK_WIDTH  (7)
#define BLK_HEIGHT (7)
#define BLK_STRIDE (8)

#define MAX_NUM_POINTS (32)

#define SCATCH_SIZE ((MAX_NUM_POINTS/VCOP_SIMD_WIDTH)*8*9)


#pragma DATA_SECTION(gradX, "Adata");
static signed short gradX[BLK_STRIDE*BLK_HEIGHT*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(gradY, "Bdata");
static signed short gradY[BLK_STRIDE*BLK_HEIGHT*MAX_NUM_POINTS] = {0}; 

#pragma DATA_SECTION(im1, "Adata");
static unsigned char im1[BLK_STRIDE*BLK_HEIGHT*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(im2, "Bdata");
static unsigned char im2[BLK_STRIDE*BLK_HEIGHT*MAX_NUM_POINTS] = {0}; 

#pragma DATA_SECTION(outIxIt, "Adata");
static signed int outIxIt[SCATCH_SIZE] = {0};
#pragma DATA_SECTION(outIyIt, "Bdata");
static signed int outIyIt[SCATCH_SIZE] = {0};

#pragma DATA_SECTION(refIxIt, "EXTDMEM");
static signed int refIxIt[MAX_NUM_POINTS] = {0};
#pragma DATA_SECTION(refIyIt, "EXTDMEM");
static signed int refIyIt[MAX_NUM_POINTS] = {0};

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_sum_grad_cross_inter_frame_diff_7x7_kernel.k"
#else
#include "vcop_sum_grad_cross_inter_frame_diff_7x7_kernel.h"
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
  params->numKeyPoints = 8;
  params->seedForRND   = 0;
}
static int writeOutputToTxtFile(unsigned short n, int * ptr1, int * ptr2, char * fileName)
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
      fprintf(fp,"%12d %12d\n",ptr1[i],ptr2[i]);
  }
  fclose(fp);
  return(0);
}

static int readInputFromTxtFile(void *p, unsigned short n, unsigned short w, unsigned short h, unsigned short stride,char * fileName, int dataType)
{
  int i, j, k;
  FILE * fp;
  char * LinePtr;
  int status;
  int value;
  char inputLine[MAX_INPUT_LINE_SIZE];
  char inputValue[MAX_INPUT_VALUE_SIZE];

  fp = fopen(fileName, "r");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(k = 0; k < n; k++) 
  {
    for(i = 0; i < h; i++) 
    {
      memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
      status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
      if ((status == EOF) || (status == 0))
      {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return(-1);
      }
      LinePtr = inputLine;
      for(j = 0; j < w; j++) 
      {
        sscanf(LinePtr, "%d",&value);
        sscanf(LinePtr, "%s",inputValue);
        if(dataType == 5)
        {
          int * ptr = (int * )p;
          ptr[k*stride*h + i*stride+j] = value;
        }
        else if(dataType == 4)
        {
          unsigned int * ptr = (unsigned int * )p;
          ptr[k*stride*h + i*stride+j] = value;
        }
        else if(dataType == 3)
        {
          short * ptr = (short * )p;
          ptr[k*stride*h + i*stride+j] = value;
        }
        else if(dataType == 2)
        {
          unsigned short * ptr = (unsigned short * )p;
          ptr[k*stride*h + i*stride+j] = value;
        }
        else if(dataType == 1)
        {
          char * ptr = (char * )p;
          ptr[k*stride*h + i*stride+j] = value;
        }
        else if(dataType ==0)
        {
          unsigned char * ptr = (unsigned char * )p;
          ptr[k*stride*h + i*stride+j] = value;
        }
        LinePtr = moveToNextElement(inputValue,LinePtr);
      }
    }
  }
  fclose(fp);
  return(0);
}

static void CreateRandPatternU8(unsigned char *p, unsigned short n, unsigned short w, unsigned short h, unsigned short stride)
{
    int i, j, k;

#ifdef __DEBUG
    printf("Input Block:\n");
#endif
    for(k = 0; k < n; k++) 
    {
      for(i = 0; i < h; i++) 
      {
          for(j = 0; j < w; j++) 
          {
              p[k*stride*h + i*stride+j] = (rand() & 0xFF);
#ifdef __DEBUG
              printf("%4d, ",  p[k*stride*h + i*stride+j]);
#endif
        }
#ifdef __DEBUG
          printf("\n");
#endif
      }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}

static void CreateRandPatternS9(signed short *p, unsigned short n, unsigned short w, unsigned short h, unsigned short stride)
{
    int i, j, k;

#ifdef __DEBUG
    printf("Input Block:\n");
#endif
    for(k = 0; k < n; k++) 
    {
      for(i = 0; i < h; i++) 
      {
          for(j = 0; j < w; j++) 
          {
              p[k*stride*h + i*stride+j] = (rand() % 255) * (rand()&1 ? -1:1);
#ifdef __DEBUG
              printf("%4d, ",  p[k*stride*h + i*stride+j]);
#endif
        }
#ifdef __DEBUG
          printf("\n");
#endif
      }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}


int test_bench(config_params * params)
{
    int fail,i;
    profiler_init();
    fail = 0;
    
        if(strcmp(params->inputSrc, "RND_PTRN")==0)
        {
          printf("Pattern Generation Seed = %d\n", params->seedForRND);
          srand(params->seedForRND);
          CreateRandPatternS9(gradX, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE);        
          CreateRandPatternS9(gradY, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE);
          CreateRandPatternU8(im1, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE);
          CreateRandPatternU8(im2, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE);
          
        }
        else if(strcmp(params->inputSrc, "TXT_FILE")==0)
        {
           readInputFromTxtFile(gradX, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE,params->gradXName,3);        
           readInputFromTxtFile(gradY, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE,params->gradYName,3);        
           readInputFromTxtFile(im1, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE,params->currImName,0);        
           readInputFromTxtFile(im2, params->numKeyPoints, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE,params->prevImName,0);        
        }
       
        profiler_start();
 
        vcop_sum_grad_cross_inter_frame_diff_7x7(gradX,gradY,im1,im2,BLK_STRIDE,BLK_STRIDE, params->numKeyPoints,outIxIt,outIyIt,outIxIt,outIyIt);
                           
        profiler_end();
    
#ifdef COMPARE_REFERENCE
        vcop_sum_grad_cross_inter_frame_diff_7x7_cn(gradX,gradY,im1,im2,BLK_STRIDE,BLK_STRIDE,params->numKeyPoints,refIxIt,refIyIt);

        fail = memcmp(refIxIt,outIxIt,params->numKeyPoints*4);
        fail |= memcmp(refIyIt,outIyIt,params->numKeyPoints*4);
        printf(fail ? "FAIL\n\n" : "PASS\n\n");

    if(fail != 0) 
    {
        for(i = 0; i < params->numKeyPoints; i++) 
        {
           printf("At %3d - IxIt = %9d:%9d, IyIt = %9d:%9d \n",i,outIxIt[i],refIxIt[i],outIyIt[i],refIyIt[i]);
        }
    }

#endif

    profiler_deinit();

    if(params->writeOutput)
    {
      writeOutputToTxtFile(params->numKeyPoints, refIxIt, refIyIt,params->outFileName);        
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
      test_bench(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);

}
