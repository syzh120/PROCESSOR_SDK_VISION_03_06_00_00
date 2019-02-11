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
/*      vcop_sad_error_measure_lk_tb.c                                      */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel for SAD based error measure */
/*  of LK function with C reference output                                  */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_sad_error_measure_lk' function with a random input or         */
/*      file based inputs                                                   */
/*                                                                          */
/*  This test bench then compares the results with the C reference output   */
/*  and prints a pass/fail message.                                         */
/*                                                                          */
/*  To build the executable type:                                           */
/*  gmake                                                                   */
/*                                                                          */
/*  @version 1.0 (January 2014) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"
#include "eve_profile.h"
#include "vcop_sad_error_measure_lk_config.h"
#include "vcop_sad_error_measure_lk_cn.h"

#if VCOP_HOST_EMULATION
#include "vcop_host.h"
#include "../src_kernelC/vcop_sad_error_measure_lk_kernel.k"
#else
#include "vcop_sad_error_measure_lk_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

//#define __DEBUG
#define COMPARE_REFERENCE
#define NUM_ITER (1)

#define NUM_KEYPOINTS     (8)
#define INPUT_STRIDE      (8)
#define IMAGE_WIDTH       (640)
#define IMAGE_HEIGHT      (480)
#define BLOCK_WIDTH       (7)
#define BLOCK_HEIGHT      (7)
#define NUMFRACBITS       (4)              //Q4 format => 4 fractional bits;

#define MAX_NUM_POINTS (32)

#define SCRATCH_SIZE ((MAX_NUM_POINTS/VCOP_SIMD_WIDTH)*8*9*2)

#pragma DATA_SECTION(PREVBILINIMG, "Adata");
static unsigned char PREVBILINIMG[MAX_NUM_POINTS*INPUT_STRIDE*BLOCK_HEIGHT] = {0x00};

#pragma DATA_SECTION(CURRBILINIMG, "Bdata");
static unsigned char CURRBILINIMG[MAX_NUM_POINTS*INPUT_STRIDE*BLOCK_HEIGHT] = {0x00};

#pragma DATA_SECTION(NEWXYLIST, "Cdata");
static unsigned short NEWXYLIST[2*MAX_NUM_POINTS] = {0x00};

#pragma DATA_SECTION(SAD_ERROR_MEASURE_OUT, "Adata");
static unsigned short SAD_ERROR_MEASURE_OUT[MAX_NUM_POINTS] = {0x00};

#pragma DATA_SECTION(scratch_a, "Cdata");
static uint16_t scratch_a[SCRATCH_SIZE] = {0};

#pragma DATA_SECTION(numInvalidPointsWbuf, "Cdata");
static uint16_t numInvalidPointsWbuf[VCOP_SIMD_WIDTH] = {0};

#pragma DATA_SECTION(numInvalidPointsIbuf, "Adata");
static uint16_t numInvalidPointsIbuf[VCOP_SIMD_WIDTH] = {0};

#pragma DATA_SECTION(REF_SAD_ERROR_MEASURE_OUT, "Eoutdata");
static uint16_t REF_SAD_ERROR_MEASURE_OUT[MAX_NUM_POINTS] = {0x00};

#pragma DATA_SECTION(C_REF_TRUTH_OUT, "Eoutdata");
static uint16_t C_REF_TRUTH_OUT[MAX_NUM_POINTS] = {0x00};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(ssad_error_measure_lk_Config * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->inputStride      = INPUT_STRIDE  ;
  params->frmWidth         = IMAGE_WIDTH   ;
  params->frmHeight        = IMAGE_HEIGHT  ;
  params->blkWidth         = BLOCK_WIDTH   ;
  params->blkHeight        = BLOCK_HEIGHT  ;
  params->numKeyPoints     = NUM_KEYPOINTS ;
  params->shiftValue       = NUMFRACBITS   ;
  params->numIter          = NUM_ITER      ;
  params->writeOutput      = 0             ;
  params->seedForRND       = 0             ;
}

int writeOutputFile(unsigned short * output, ssad_error_measure_lk_Config * params)
{
    FILE * fp;
    int i;
    fp = fopen(params->outFileName, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(i = 0; i < params->numKeyPoints; i++)
    {
        if(i < (params->numKeyPoints-1))
        {
            fprintf(fp, "%d   ", output[i]);
        }
        else
        {
            fprintf(fp, "%d\n", output[i]);
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

static void CreateRandPatternU16(unsigned short *xylist, unsigned short n)
{
    int j;

#ifdef __DEBUG
    printf("(X Y) Coordinate Lists in Q-Format:\n");
#endif

    for(j = 0; j < n; j++)
    {
        xylist[j] = (rand() & 0xFFFF);
#ifdef __DEBUG
        printf("%4d ",  xylist[j]);
#endif
    }
#ifdef __DEBUG
        printf("\n");
#endif
}

void test_sad_error_measure_lk_c_reference(ssad_error_measure_lk_Config * params)
{
    int i, fail;
    char refFile[] = "../testvecs/reference/err_measure_lk_output.txt";
#ifdef __DEBUG
    int j, k;
#endif
    uint16_t numInvalidKeyPointsRef = 0;

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU8(PREVBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride);
      CreateRandPatternU8(CURRBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride);
      CreateRandPatternU16(NEWXYLIST, 2*params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFromTxtFile(PREVBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride, params->inFileName1,0);
       readInputFromTxtFile(CURRBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride, params->inFileName2,0);
       readInputFile(NEWXYLIST, 2*params->numKeyPoints, params->inFileName3, 2);
       readInputFile(C_REF_TRUTH_OUT, params->numKeyPoints, refFile, 2);
    }

#ifdef __DEBUG
    //Print the (X,Y) coordinate list denoted in Q4 format
    for(j = 0; j < 2*params->numKeyPoints; j++)
    {
        printf("%4d ",  NEWXYLIST[j]);
    }
    printf("\n");

    //Print the previous frame bilinear interpolated patch window pixels for every key point
    for(k = 0; k < params->numKeyPoints; k++)
    {
        for(j = 0; j < params->blkHeight; j++)
        {
            for(i = 0; i < params->blkWidth; i++)
            {
                printf("%4d ",  PREVBILINIMG[k*params->inputStride*params->blkHeight+j*params->inputStride+i]);
            }
            printf("\n");
        }
    }

    //Print the current frame bilinear interpolated patch window pixels for every key point
    for(k = 0; k < params->numKeyPoints; k++)
    {
        for(j = 0; j < params->blkHeight; j++)
        {
            for(i = 0; i < params->blkWidth; i++)
            {
                printf("%4d ",  CURRBILINIMG[k*params->inputStride*params->blkHeight+j*params->inputStride+i]);
            }
            printf("\n");
        }
    }
#endif

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_sad_error_measure_lk_cn(PREVBILINIMG, CURRBILINIMG, NEWXYLIST, REF_SAD_ERROR_MEASURE_OUT,
                                 params->inputStride, params->frmWidth,
                                 params->frmHeight, params->blkWidth, params->blkHeight,
                                 params->numKeyPoints, params->shiftValue, 0 , &numInvalidKeyPointsRef );

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
#ifdef __DEBUG
    printf("\n");
#endif

    for(i = 0; i < params->numKeyPoints; i++)
    {
        if(C_REF_TRUTH_OUT[i] != REF_SAD_ERROR_MEASURE_OUT[i])
        {
            fail = 1;
            printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_SAD_ERROR_MEASURE_OUT[i], C_REF_TRUTH_OUT[i], (i));
            break;
        }
#ifdef __DEBUG
        printf("%3d ",REF_SAD_ERROR_MEASURE_OUT[i]);
#endif
    }

    printf(fail ? "FAIL\n":"PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(REF_SAD_ERROR_MEASURE_OUT, params);
    }
}

int test_sad_error_measure_lk_vcop(ssad_error_measure_lk_Config * params)
{
    int i, iter, fail = 0, status = 0;
#ifdef __DEBUG
    int j, k;
#endif
    uint16_t numInvalidKeyPointsRef = 0;

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU8(PREVBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride);
      CreateRandPatternU8(CURRBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride);
      CreateRandPatternU16(NEWXYLIST, 2*params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFromTxtFile(PREVBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride, params->inFileName1,0);
       readInputFromTxtFile(CURRBILINIMG, params->numKeyPoints, params->blkWidth, params->blkHeight, params->inputStride, params->inFileName2,0);
       readInputFile(NEWXYLIST, 2*params->numKeyPoints, params->inFileName3, 2);
    }

    printf("Number of KeyPoints = %d\n", params->numKeyPoints);

#ifdef __DEBUG
    //Print the (X,Y) coordinate list denoted in Q4 format
    for(j = 0; j < 2*params->numKeyPoints; j++)
    {
        printf("%4d ",  NEWXYLIST[j]);
    }
    printf("\n");

    //Print the previous frame bilinear interpolated patch window pixels for every key point
    for(k = 0; k < params->numKeyPoints; k++)
    {
        for(j = 0; j < params->blkHeight; j++)
        {
            for(i = 0; i < params->blkWidth; i++)
            {
                printf("%4d ",  PREVBILINIMG[k*params->inputStride*params->blkHeight+j*params->inputStride+i]);
            }
            printf("\n");
        }
    }

    //Print the current frame bilinear interpolated patch window pixels for every key point
    for(k = 0; k < params->numKeyPoints; k++)
    {
        for(j = 0; j < params->blkHeight; j++)
        {
            for(i = 0; i < params->blkWidth; i++)
            {
                printf("%4d ",  CURRBILINIMG[k*params->inputStride*params->blkHeight+j*params->inputStride+i]);
            }
            printf("\n");
        }
    }
#endif

#if VCOP_HOST_EMULATION
#else
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_sad_error_measure_lk_init(PREVBILINIMG,
                                   CURRBILINIMG,
                                   NEWXYLIST,
                                   SAD_ERROR_MEASURE_OUT,
                                   params->inputStride,
                                   params->frmWidth,
                                   params->frmHeight,
                                   params->blkWidth,
                                   params->blkHeight,
                                   params->numKeyPoints,
                                   params->shiftValue,
                                   scratch_a,
                                   0xFFFF,
                                   numInvalidPointsWbuf,
                                   numInvalidPointsIbuf,
                                   __pblock_vcop_sad_error_measure_lk);
#endif

    for (iter = 0; iter <  params->numIter; iter++)
    {

        memset(numInvalidPointsWbuf, 0 , VCOP_SIMD_WIDTH * sizeof(uint16_t));
        memset(numInvalidPointsIbuf, 0 , VCOP_SIMD_WIDTH * sizeof(uint16_t));
        numInvalidKeyPointsRef = 0;

        printf("Iteration %d:\n", iter);
#ifdef COMPARE_REFERENCE
        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
    vcop_sad_error_measure_lk_cn(PREVBILINIMG, CURRBILINIMG, NEWXYLIST, REF_SAD_ERROR_MEASURE_OUT,
                                 params->inputStride, params->frmWidth,
                                 params->frmHeight, params->blkWidth, params->blkHeight,
                                 params->numKeyPoints, params->shiftValue,0xFFFF, &numInvalidKeyPointsRef );
#endif
        profiler_start();

#if VCOP_HOST_EMULATION

    vcop_sad_error_measure_lk(PREVBILINIMG, CURRBILINIMG, NEWXYLIST, SAD_ERROR_MEASURE_OUT,
                                   params->inputStride, params->frmWidth,
                                   params->frmHeight, params->blkWidth, params->blkHeight,
                                   params->numKeyPoints, params->shiftValue, scratch_a,0xFFFF,
                                   numInvalidPointsWbuf,
                                   numInvalidPointsIbuf);

#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_sad_error_measure_lk_vloops(__pblock_vcop_sad_error_measure_lk);
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

        for(i = 0; i < params->numKeyPoints; i++)
        {
            if(SAD_ERROR_MEASURE_OUT[i] != REF_SAD_ERROR_MEASURE_OUT[i])
            {
                fail = 1;
                printf("C Reference Output = %d, VCOP Output = %d, i = %d\n",REF_SAD_ERROR_MEASURE_OUT[i], SAD_ERROR_MEASURE_OUT[i], (i));
                break;
            }
        }
#ifdef __DEBUG
            printf("%3d ",SAD_ERROR_MEASURE_OUT[i]);
#endif


      if ( fail == 0 )
      {
        for ( i = 1 ; i < VCOP_SIMD_WIDTH; i++ )
        {
          numInvalidPointsWbuf[0] += numInvalidPointsWbuf[i];
        }

        if ( numInvalidKeyPointsRef != numInvalidPointsWbuf[0] )
        {
          fail = 1;

        }
      }

        printf(fail ? "FAIL\n\n" : "PASS\n\n");
        status |= fail;
#endif
    }
    profiler_deinit();

    printf(status ? "test_sad_error_measure_lk: FAIL\n":"test_sad_error_measure_lk: PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(SAD_ERROR_MEASURE_OUT, params);
    }

    return status;
}

int main()
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  ssad_error_measure_lk_Config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  printf("Validate SAD Based Error Measure for LK VCOP Kernel Output\n");
  params = (ssad_error_measure_lk_Config *)(&gConfig_sad_error_measure_lk);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_sad_error_measure_lk_vcop(params);
    //test_sad_error_measure_lk_c_reference(params);
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
      status = readparamfile(configFileName, &gsTokenMap_sad_error_measure_lk[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_sad_error_measure_lk_vcop(params);
      //test_sad_error_measure_lk_c_reference(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);
}
