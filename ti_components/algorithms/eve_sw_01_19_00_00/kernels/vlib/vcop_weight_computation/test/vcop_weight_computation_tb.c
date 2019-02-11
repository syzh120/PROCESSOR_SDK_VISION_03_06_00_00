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

/*                                                                          */
/*  NAME                                                                    */
/*      vcop_weight_computation_tb.c                                        */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel for weight computation      */
/*  function with C reference output                                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_weight_computation' function with a random input or file      */
/*      file based inputs                                                   */
/*                                                                          */
/*  This test bench then compares the results with the C reference output   */
/*  and prints a pass/fail message.                                         */
/*                                                                          */
/*  To build the executable type:                                           */
/*  gmake                                                                   */
/*                                                                          */
/*  @author Venkat R Peddigari (a0393744@ti.com)                            */
/*                                                                          */
/*  @version 1.0 (November 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"
#include "eve_profile.h"
#include "vcop_weight_computation_config.h"
#include "vcop_weight_computation_cn.h"

#if VCOP_HOST_EMULATION
#include "vcop_host.h"
#include "../src_kernelC/vcop_weight_computation_kernel.k"
#else
#include "vcop_weight_computation_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

//#define __DEBUG
#define COMPARE_REFERENCE
#define NUM_ITER (1)

#define NUM_KEYPOINTS     (8)
#define QFORMATMAXFACTOR  (15)             //Q4 format => 4 fractional bits; (2^4) - 1 = 15, For Q3 format, (2^3) - 1 = 7
#define OUT_STRIDE        (NUM_KEYPOINTS)  //Should be greater than or equal to (4*NUM_KEYPOINTS)
#define NUM_OUTPUTS       (4)              //Factor of 4 is used since we have 4 output weight vectors namely w0, w1, w2, w3

#pragma DATA_SECTION(XYLIST, "Adata");
static unsigned short XYLIST[2*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(WEIGHT_OUT, "Cdata");
static unsigned short WEIGHT_OUT[NUM_OUTPUTS*OUT_STRIDE] = {0x00};

#pragma DATA_SECTION(REF_WEIGHT_OUT, "Eoutdata");
static unsigned short REF_WEIGHT_OUT[NUM_OUTPUTS*OUT_STRIDE] = {0x00};

#pragma DATA_SECTION(C_REF_TRUTH_OUT, "Eoutdata");
static unsigned char C_REF_TRUTH_OUT[NUM_OUTPUTS*OUT_STRIDE] = {
              0,   28,  154,  66,  140,  132,   36,   84,
              0,  182,   11,  99,   70,   33,  144,  126,
            180,    2,   56,  24,   10,   48,    9,    6,
             45,   13,    4,  36,    5,   12,   36,    9};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sweight_computation_Config * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->numKeyPoints     = NUM_KEYPOINTS;
  params->qFormatMaxFactor = QFORMATMAXFACTOR;
  params->outputStride     = OUT_STRIDE;
  params->numIter          = NUM_ITER;
  params->writeOutput      = 0;
  params->seedForRND       = 0;
}

int writeOutputFile(unsigned short * output, sweight_computation_Config * params)
{
    FILE * fp;
    int i,j;
    fp = fopen(params->outFileName, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(j = 0; j < NUM_OUTPUTS; j++)
    {
        for(i = 0; i < params->numKeyPoints; i++)
        {
            if(i < (params->numKeyPoints-1))
            {
                fprintf(fp, "%d   ", output[j*params->outputStride+i]);
            }
            else
            {
                fprintf(fp, "%d\n", output[j*params->outputStride+i]);
            }
        }
    }
    fclose(fp);

    return (0);
}

int readInputFile(void * input, unsigned short n, char * filename, int dataType)
{
    int j;
    FILE * fp;
    char * LinePtr;
    int status;
    int value;
    char inputLine[MAX_INPUT_LINE_SIZE];
    char inputValue[MAX_INPUT_VALUE_SIZE];

    fp = fopen(filename, "r");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return(-1);
    }
    LinePtr = inputLine;
    for(j = 0; j < n; j++)
    {
        sscanf(LinePtr, "%d",&value);
        sscanf(LinePtr, "%s",inputValue);
        if(dataType == 5)
        {
          int * ptr = (int * )input;
          ptr[j] = value;
        }
        else if(dataType == 4)
        {
          unsigned int * ptr = (unsigned int * )input;
          ptr[j] = value;
        }
        else if(dataType == 3)
        {
          short * ptr = (short * )input;
          ptr[j] = value;
        }
        else if(dataType == 2)
        {
          unsigned short * ptr = (unsigned short * )input;
          ptr[j] = value;
        }
        else if(dataType == 1)
        {
          char * ptr = (char * )input;
          ptr[j] = value;
        }
        else if(dataType ==0)
        {
          unsigned char * ptr = (unsigned char * )input;
          ptr[j] = value;
        }
        LinePtr = moveToNextElement(inputValue,LinePtr);
    }

  fclose(fp);
  return(0);
}

static void CreateRandPatternU16(unsigned short *xylist, unsigned short n)
{
    int j;

#ifdef __DEBUG
    printf("(X Y) Coordinate Lists in Q-Format:\n");
#endif

    for(j = 0; j < n; j++)
    {
        xylist[j] = (rand() & 0xFFF);
#ifdef __DEBUG
        printf("%4d ",  xylist[j]);
#endif
    }
#ifdef __DEBUG
        printf("\n");
#endif
}

void test_weight_computation_c_reference(sweight_computation_Config * params)
{
    int i, j, fail;

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU16(XYLIST, 2*params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFile(XYLIST, 2*params->numKeyPoints, params->inFileName, 2);
    }

#ifdef __DEBUG
    for(j = 0; j < 2*params->numKeyPoints; j++)
    {
        printf("%4d ",  XYLIST[j]);
    }
    printf("\n");
#endif
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_weight_computation_cn(XYLIST, REF_WEIGHT_OUT, params->numKeyPoints, params->qFormatMaxFactor, 0, params->outputStride);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
#ifdef __DEBUG
    printf("\n");
#endif
    for(j = 0; j < NUM_OUTPUTS; j++)
    {
        for(i = 0; i < params->numKeyPoints; i++)
        {
            if(C_REF_TRUTH_OUT[j*params->outputStride+i] != REF_WEIGHT_OUT[j*params->outputStride+i])
            {
                fail = 1;
                printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_WEIGHT_OUT[j*params->outputStride+i], C_REF_TRUTH_OUT[j*params->outputStride+i], (j*OUT_STRIDE+i));
                break;
            }
#ifdef __DEBUG
            printf("%3d ",REF_WEIGHT_OUT[j*params->outputStride+i]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
    printf(fail ? "FAIL\n":"PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(REF_WEIGHT_OUT, params);
    }
}

int test_weight_computation_vcop(sweight_computation_Config * params)
{
    int i, j, iter, fail = 0, status = 0;

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU16(XYLIST, 2*params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFile(XYLIST, 2*params->numKeyPoints, params->inFileName, 2);
    }

    printf("Number of KeyPoints = %d, Output Stride = %d\n", params->numKeyPoints, params->outputStride);

#ifdef __DEBUG
    for(j = 0; j < 2*params->numKeyPoints; j++)
    {
        printf("%4d ",  XYLIST[j]);
    }
    printf("\n");
#endif

#if VCOP_HOST_EMULATION
#else
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_weight_computation_init(XYLIST, WEIGHT_OUT, params->numKeyPoints, params->qFormatMaxFactor, 0, params->outputStride, __pblock_vcop_weight_computation);
#endif

    for (iter = 0; iter <  params->numIter; iter++)
    {
        printf("Iteration %d:\n", iter);
#ifdef COMPARE_REFERENCE
        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
        vcop_weight_computation_cn(XYLIST, REF_WEIGHT_OUT, params->numKeyPoints, params->qFormatMaxFactor, 0, params->outputStride);
#endif
        profiler_start();
#if VCOP_HOST_EMULATION
    vcop_weight_computation(XYLIST, WEIGHT_OUT, params->numKeyPoints, params->qFormatMaxFactor, 0 ,params->outputStride);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_weight_computation_vloops(__pblock_vcop_weight_computation);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
#endif
        profiler_end();

#ifdef COMPARE_REFERENCE
        fail = 0;
#ifdef __DEBUG
        printf("\n");
#endif
        for(j = 0; j < NUM_OUTPUTS; j++)
        {
            for(i = 0; i < params->numKeyPoints; i++)
            {
                if(WEIGHT_OUT[j*params->outputStride+i] != REF_WEIGHT_OUT[j*params->outputStride+i])
                {
                    fail = 1;
                    printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_WEIGHT_OUT[j*params->outputStride+i], WEIGHT_OUT[j*params->outputStride+i], (j*OUT_STRIDE+i));
                    break;
                }
#ifdef __DEBUG
                printf("%3d ",WEIGHT_OUT[j*params->outputStride+i]);
#endif
            }
#ifdef __DEBUG
        printf("\n");
#endif
        }

        printf(fail ? "FAIL\n\n" : "PASS\n\n");
        status |= fail;
#endif
    }
    profiler_deinit();

    printf(status ? "test_weight_computation: FAIL\n":"test_weight_computation: PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(WEIGHT_OUT, params);
    }

    return status;
}

int main()
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  sweight_computation_Config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  printf("Validate Weight Computation VCOP Kernel Output\n");
  params = (sweight_computation_Config *)(&gConfig_weight_computation);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_weight_computation_vcop(params);
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
      status = readparamfile(configFileName, &gsTokenMap_weight_computation[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_weight_computation_vcop(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);
}
