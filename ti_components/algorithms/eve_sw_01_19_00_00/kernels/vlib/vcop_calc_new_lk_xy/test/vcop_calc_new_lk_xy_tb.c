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
#include "vcop_calc_new_lk_xy_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct 
{
  char ifDiffFileName[MAX_FILE_NAME_SIZE];
  char fracExpFileName[MAX_FILE_NAME_SIZE];
  char XYCoOrdFileName[MAX_FILE_NAME_SIZE];
  char outFileName[MAX_FILE_NAME_SIZE];
  int  numKeyPoints;
  int  writeOutput;
  int  seedForRND;
  char inputSrc[MAX_PARAM_STRING_SIZE];
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];

} config_params;

config_params gParams ;


sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] = 
{
  {(char* )"inputSrc",                  &(gParams.inputSrc)                   , STRING, SINGLE},                    
  {(char* )"ifDiffFileName",            &(gParams.ifDiffFileName)              , STRING, SINGLE},                    
  {(char* )"fracExpFileName",            &(gParams.fracExpFileName)              , STRING, SINGLE},                    
  {(char* )"XYCoOrdFileName",            &(gParams.XYCoOrdFileName)              , STRING, SINGLE},                    
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

#pragma DATA_SECTION(FrameXY, "Bdata");
static signed short FrameXY[2*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(X, "Cdata");
static signed short X[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(Y, "Cdata");
static signed short Y[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(XY, "Cdata");
static signed short XY[2*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(Ix2, "Adata");
static signed short Ix2[2*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(Iy2, "Bdata");
static signed short Iy2[2*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(Ixy, "Cdata");
static signed short Ixy[2*MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(IxIt, "Adata");
static signed int IxIt[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(IyIt, "Bdata");
static signed int IyIt[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(temp1, "Adata");
static signed int temp1[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(temp2, "Cdata");
static signed int temp2[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(numValidPoints, "Bdata");
static unsigned short numValidPoints[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(currValidPoints, "Bdata");
static unsigned char currValidPoints[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(pBaseAddrList, "Bdata");
static unsigned int pBaseAddrList[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(pValidInAddrList, "Bdata");
static unsigned int pValidInAddrList[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(pFinalOutAddress, "Bdata");
static unsigned int pFinalOutAddress[MAX_NUM_POINTS] = {0}; 
#pragma DATA_SECTION(pValidOutAddrList, "Bdata");
static unsigned int pValidOutAddrList[MAX_NUM_POINTS] = {0}; 
  
static signed short bakFrameXY[2*MAX_NUM_POINTS] = {0}; 
static signed short bakXY[2*MAX_NUM_POINTS]      = {0}; 

static signed short refFrameXY[2*MAX_NUM_POINTS] = {0}; 
static signed short refXY[2*MAX_NUM_POINTS]      = {0}; 


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_calc_new_lk_xy_kernel.k"
#else
#include "vcop_calc_new_lk_xy_kernel.h"
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
  params->seedForRND   = 0xABDC1234;
}
static int writeOutputToTxtFile(unsigned short n, short * ptr1, short * ptr2, char * fileName)
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

#if 0
static int WriteFracExpToFile(short *Ix2, short *Iy2, short *Ixy, unsigned short n, char * fileName)
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
    fprintf(fp,"%12d %12d %12d %12d %12d %12d \n",Ix2[2*i],Ix2[2*i+1],Iy2[2*i],Iy2[2*i+1],Ixy[2*i],Ixy[2*i+1]);
  }
  fclose(fp);
  return(0);
}
static int WriteXyCoOrdinatesToFile(short *XY, short *frameXY, unsigned short n, char * fileName)
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
    fprintf(fp,"%12d %12d %12d %12d\n",XY[2*i],XY[2*i+1],frameXY[2*i],frameXY[2*i+1]);
  }
  fclose(fp);
  return(0);
}
#endif

static int readIfDiffFromTxtFile(int *IxIt, int *IyIt, unsigned short n, char * fileName)
{
  int k;
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
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    inputValue[0] ='\0';
    LinePtr = inputLine;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    IxIt[k] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    IyIt[k] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
  }
  fclose(fp);
  return(0);
}
static int readFracExpFromTxtFile(short *Ix2, short *Iy2, short *Ixy, unsigned short n, char * fileName)
{
  int i;
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
  for(i = 0; i < n; i++) 
  {
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    LinePtr = inputLine;
    inputValue[0] ='\0';
    LinePtr = inputLine;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    Ix2[2*i] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    Ix2[2*i+1] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    Iy2[2*i] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    Iy2[2*i+1] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    Ixy[2*i] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    Ixy[2*i+1] = value;
  }
  fclose(fp);
  return(0);
}
static int readXyCoOrdinatesFromTxtFile(short *XY, short *frameXY, unsigned short n, char * fileName)
{
  int i;
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
  for(i = 0; i < n; i++) 
  {
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    LinePtr = inputLine;
    inputValue[0] ='\0';
    LinePtr = inputLine;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    XY[2*i] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    XY[2*i+1] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    frameXY[2*i] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    frameXY[2*i+1] = value;
  }
  fclose(fp);
  return(0);
}
static void CreateRandPatternS32(int *IxIt, int *IyIt, unsigned short n)
{
  int i;

  for(i = 0; i < n; i++) 
  {
    IxIt[i] = (rand() << (rand()%8)) | rand();
    IyIt[i] = (rand() << (rand()%8)) | rand();
  }
}
static void CreateRandPatternU16(short *XY, short *frameXY, unsigned short n)
{
  int i;

  for(i = 0; i < n; i++) 
  {
    XY[2*i]        = rand() % 64;
    XY[2*i+1]      = rand() % 64;
    frameXY[2*i]   = rand();
    frameXY[2*i+1] = rand();
  }
}

static void CreateRandPatternFracExp(short *Ix2, short *Iy2, short *Ixy, unsigned short n)
{
  int i;

  for(i = 0; i < n; i++) 
  {
    Ix2[2*i]   = rand();
    Ix2[2*i+1] = (rand()%32);
    Iy2[2*i]   = rand();
    Iy2[2*i+1] = (rand()%32);
    Ixy[2*i]   = rand();
    Ixy[2*i+1] = (rand()%32);
  }
}


int test_bench(config_params * params)
{
  int fail,i;
  profiler_init();
  fail = 0;
  unsigned short  *IxItL_a;
  unsigned short  *IyItL_b;
  short  *IxItH_a;
  short  *IyItH_b;

  IxItL_a = (unsigned short *)(IxIt);
  IyItL_b = (unsigned short *)(IyIt);
  IxItH_a = (short *)(((unsigned int)IxIt) + 2);
  IyItH_b = (short *)(((unsigned int)IyIt) + 2);


  /*
  char * fracExpFileName = "D:\\work\\vision\\kumar_local\\Kernel_Template_v2\\kernels\\vlib\\vcop_calc_new_lk_xy\\test\\testvecs\\input\\fracExp.txt";
  char * XYCoOrdFileName = "D:\\work\\vision\\kumar_local\\Kernel_Template_v2\\kernels\\vlib\\vcop_calc_new_lk_xy\\test\\testvecs\\input\\XYPoints.txt";
  */
  if(strcmp(params->inputSrc, "RND_PTRN")==0)
  {
    printf("Pattern Generation Seed = %d\n", params->seedForRND);
    srand(params->seedForRND);
    CreateRandPatternS32(IxIt, IyIt,params->numKeyPoints);        
    CreateRandPatternFracExp(Ix2, Iy2, Ixy, params->numKeyPoints);        
    CreateRandPatternU16(XY, FrameXY,params->numKeyPoints);        
    /*
    WriteFracExpToFile(Ix2, Iy2, Ixy, params->numKeyPoints,fracExpFileName);        
    WriteXyCoOrdinatesToFile(XY, FrameXY,params->numKeyPoints,XYCoOrdFileName);        
    */
  }
  else if(strcmp(params->inputSrc, "TXT_FILE")==0)
  {
    readIfDiffFromTxtFile(IxIt, IyIt, params->numKeyPoints, params->ifDiffFileName);   
    readFracExpFromTxtFile(Ix2, Iy2, Ixy, params->numKeyPoints,params->fracExpFileName); 
    readXyCoOrdinatesFromTxtFile(XY, FrameXY,params->numKeyPoints,params->XYCoOrdFileName); 
  }
#ifdef COMPARE_REFERENCE
  memcpy(bakFrameXY, FrameXY,params->numKeyPoints*4);
  memcpy(bakXY, XY,params->numKeyPoints*4);
  for(i = 0; i < params->numKeyPoints; i++) 
  {
    X[i]   = bakXY[2*i];
    Y[i]   = bakXY[2*i+1];
  }

  vcop_calc_new_lk_xy_cn(IxIt,IyIt,Ix2, Iy2, Ixy, (unsigned short*)X, (unsigned short*)Y, (unsigned short*)FrameXY, numValidPoints, currValidPoints, 4, 0, 12, params->numKeyPoints);
  memcpy(refFrameXY, FrameXY,params->numKeyPoints*4);
  for(i = 0; i < params->numKeyPoints; i++) 
  {
    refXY[2*i]   = X[i];
    refXY[2*i+1] = Y[i];
  }
  memcpy(FrameXY,bakFrameXY, params->numKeyPoints*4);
  memcpy(XY,bakXY, params->numKeyPoints*4);
  for(i = 0; i < params->numKeyPoints; i++) 
  {
    X[i]   = bakXY[2*i];
    Y[i]   = bakXY[2*i+1];
  }
#endif
  profiler_start();

  vcop_calc_new_lk_xy(IxItL_a,IyItL_b,IxItH_a,IyItH_b,Ix2, Iy2, Ixy, X, Y, XY, FrameXY, numValidPoints, currValidPoints, pBaseAddrList, pValidInAddrList ,pFinalOutAddress,pValidOutAddrList,temp1, temp2, 4, 0, 12, params->numKeyPoints);

  profiler_end();

#ifdef COMPARE_REFERENCE

  fail = memcmp(refXY,XY,params->numKeyPoints*2);
  fail |= memcmp(refFrameXY,FrameXY,params->numKeyPoints*2);
  printf(fail ? "FAIL\n\n" : "PASS\n\n");

  if(fail != 0) 
  {
    for(i = 0; i < params->numKeyPoints; i++) 
    {
      printf("At %3d - X = %9d:%9d, Y = %16d:%16d ",i,XY[2*i],refXY[2*i],XY[2*i+1],refXY[2*i+1]);
      if(XY[2*i]!=refXY[2*i] || XY[2*i+1]!=refXY[2*i+1])
      {
        printf("*******\n");
      }
      else
      {
        printf("\n");
      }
    }
    for(i = 0; i < params->numKeyPoints; i++) 
    {
      printf("At %3d - X = %9d:%9d, Y = %16d:%16d ",i,FrameXY[2*i],refFrameXY[2*i],FrameXY[2*i+1],refFrameXY[2*i+1]);
      if(FrameXY[2*i]!=refFrameXY[2*i] || FrameXY[2*i+1]!=refFrameXY[2*i+1])
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
    writeOutputToTxtFile(params->numKeyPoints, XY, FrameXY,params->outFileName);        
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
