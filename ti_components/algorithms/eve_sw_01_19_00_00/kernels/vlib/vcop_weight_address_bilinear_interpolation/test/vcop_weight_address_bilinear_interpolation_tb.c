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
/*      vcop_weight_address_bilinear_interpolation_tb.c                     */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel for weight and address      */
/*  computation needed for bilinear interpolation with C reference output   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_weight_address_bilinear_interpolation' function with a random */
/*      input or file based inputs                                          */
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
#include "vcop_weight_address_bilinear_interpolation_config.h"
#include "vcop_weight_address_bilinear_interpolation_cn.h"

#if VCOP_HOST_EMULATION
#include "vcop_host.h"
#include "../src_kernelC/vcop_weight_address_bilinear_interpolation_kernel.k"
#else
#include "vcop_weight_address_bilinear_interpolation_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

//#define __DEBUG
#define COMPARE_REFERENCE
#define NUM_ITER (1)

#define NUM_KEYPOINTS     (8)
#define QFORMATMAXFACTOR  (15)             //Q4 format => 4 fractional bits; (2^QSHIFT) - 1 = 15, For Q3 format, (2^3) - 1 = 7
#define QSHIFT            (4)              //Denotes the number of fractional bits, n in the given Qn Format used for X or Y coordinates
#define OUT_STRIDE        (NUM_KEYPOINTS)  //Should be greater than or equal to (4*NUM_KEYPOINTS)
#define NUM_OUTPUTS       (4)              //Factor of 4 is used since we have 4 output weight vectors namely w0, w1, w2, w3
#define BLK_STRIDE        (31)
#define CURR_FRM_INTERP_KERNEL_PARAM_BLK_SIZE  (256)  //Specified in bytes
#define PARAM_BLK_SIZE_IN_WORDS (CURR_FRM_INTERP_KERNEL_PARAM_BLK_SIZE>>2)

#pragma DATA_SECTION(XYLIST, "Adata");
static unsigned short XYLIST[2*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(XLIST, "Adata");
static unsigned short XLIST[NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(YLIST, "Adata");
static unsigned short YLIST[NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(BASE_ADDR_IN, "Bdata");
static unsigned int BASE_ADDR_IN[NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(PARAM_BLK_OFST_VEC_IN, "Cdata");
static unsigned short PARAM_BLK_OFST_VEC_IN[NUM_KEYPOINTS] = {0x00};  //Specifies offset in bytes, 
 
#pragma DATA_SECTION(FINAL_ADDR_IN, "Bdata");
static unsigned int FINAL_ADDR_IN[NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(WEIGHT_OUT, "Cdata");
static unsigned short WEIGHT_OUT[NUM_OUTPUTS*OUT_STRIDE] = {0x00};

#pragma DATA_SECTION(BASE_ADDR_OUT, "Cdata");
static unsigned int BASE_ADDR_OUT[PARAM_BLK_SIZE_IN_WORDS*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(REF_WEIGHT_OUT, "Eoutdata");
static unsigned short REF_WEIGHT_OUT[NUM_OUTPUTS*OUT_STRIDE] = {0x00};

#pragma DATA_SECTION(REF_BASE_ADDR_OUT, "Eoutdata");
static unsigned int REF_BASE_ADDR_OUT[PARAM_BLK_SIZE_IN_WORDS*NUM_KEYPOINTS] = {0x00};


#pragma DATA_SECTION(C_REF_TRUTH_WEIGHT_OUT, "Eoutdata");
static unsigned short C_REF_TRUTH_WEIGHT_OUT[NUM_OUTPUTS*OUT_STRIDE] = {0x00};

#pragma DATA_SECTION(C_REF_TRUTH_BASE_ADDR_OUT, "Eoutdata");
static unsigned int C_REF_TRUTH_BASE_ADDR_OUT[PARAM_BLK_SIZE_IN_WORDS*NUM_KEYPOINTS] = {0x00};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sweight_address_bilinear_interpolation_Config * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->numKeyPoints     = NUM_KEYPOINTS;
  params->qFormatMaxFactor = QFORMATMAXFACTOR;
  params->qShift           = QSHIFT;
  params->blkStride        = BLK_STRIDE;
  params->outputStride     = OUT_STRIDE;
  params->numIter          = NUM_ITER;
  params->writeOutput      = 0;
  params->seedForRND       = 0;
}

int writeOutputFile(void * output, unsigned short w, unsigned short h, unsigned short stride, char * filename, int dataType)
{
    FILE * fp;
    int i,j;
    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            if(i < (w-1))
            {
                if(dataType == 5)
                {
                  int * ptr = (int * )output;
                  fprintf(fp, "%d   ", ptr[j*stride+i]);
                }
                else if(dataType == 4)
                {
                  unsigned int * ptr = (unsigned int * )output;
                  fprintf(fp, "%d   ", ptr[j*stride+i]);
                }
                else if(dataType == 3)
                {
                  short * ptr = (short * )output;
                  fprintf(fp, "%d   ", ptr[j*stride+i]);
                }
                else if(dataType == 2)
                {
                  unsigned short * ptr = (unsigned short * )output;
                  fprintf(fp, "%d   ", ptr[j*stride+i]);
                }
                else if(dataType == 1)
                {
                  char * ptr = (char * )output;
                  fprintf(fp, "%d   ", ptr[j*stride+i]);
                }
                else if(dataType ==0)
                {
                  unsigned char * ptr = (unsigned char * )output;
                  fprintf(fp, "%d   ", ptr[j*stride+i]);
                }
            }
            else
            {
                if(dataType == 5)
                {
                  int * ptr = (int * )output;
                  fprintf(fp, "%d\n", ptr[j*stride+i]);
                }
                else if(dataType == 4)
                {
                  unsigned int * ptr = (unsigned int * )output;
                  fprintf(fp, "%d\n", ptr[j*stride+i]);
                }
                else if(dataType == 3)
                {
                  short * ptr = (short * )output;
                  fprintf(fp, "%d\n", ptr[j*stride+i]);
                }
                else if(dataType == 2)
                {
                  unsigned short * ptr = (unsigned short * )output;
                  fprintf(fp, "%d\n", ptr[j*stride+i]);
                }
                else if(dataType == 1)
                {
                  char * ptr = (char * )output;
                  fprintf(fp, "%d\n", ptr[j*stride+i]);
                }
                else if(dataType ==0)
                {
                  unsigned char * ptr = (unsigned char * )output;
                  fprintf(fp, "%d\n", ptr[j*stride+i]);
                }

            }
        }
    }
    fclose(fp);

    return (0);
}

int readInputFile(void * input, unsigned short n, unsigned short w, unsigned short h, unsigned short stride, char * filename, int dataType)
{
    int i, j, k;
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
                  int * ptr = (int * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 4)
                {
                  unsigned int * ptr = (unsigned int * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 3)
                {
                  short * ptr = (short * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 2)
                {
                  unsigned short * ptr = (unsigned short * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 1)
                {
                  char * ptr = (char * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType ==0)
                {
                  unsigned char * ptr = (unsigned char * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                LinePtr = moveToNextElement(inputValue,LinePtr);
            }
        }
    }
  fclose(fp);
  return(0);
}

static void CreatePatternU16(unsigned short *paramBlkOffset, unsigned short n, unsigned short paramBlkSize)
{
    int j;

#ifdef __DEBUG
    printf("Param Bock Offset Vector:\n");
#endif

    for(j = 0; j < n; j++)
    {
        paramBlkOffset[j] = j*paramBlkSize;
#ifdef __DEBUG
        printf("%4d ",  paramBlkOffset[j]);
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
        xylist[j] = (rand() & 0xFFF);
#ifdef __DEBUG
        printf("%4d ",  xylist[j]);
#endif
    }
}

static void CreateRandPatternU32(unsigned int *addrlist, unsigned short n)
{
    int j;

#ifdef __DEBUG
    printf("Base address list:\n");
#endif

    for(j = 0; j < n; j++)
    {
        addrlist[j] = ((rand() & 0xFFFF) << 16) | (rand() & 0xFFFF);
#ifdef __DEBUG
        printf("%4d ",  addrlist[j]);
#endif
    }
    printf("\n");
}

void test_weight_address_bilinear_interpolation_c_reference(sweight_address_bilinear_interpolation_Config * params)
{
    int i, j, fail;
    char refFile1[] = "../testvecs/reference/base_address_output.txt";
    char refFile2[] = "../testvecs/reference/weight_output.txt";

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU16(XYLIST, 2*params->numKeyPoints);
      CreateRandPatternU32(BASE_ADDR_IN, params->numKeyPoints);
      CreateRandPatternU32(FINAL_ADDR_IN, params->numKeyPoints);
      CreatePatternU16(PARAM_BLK_OFST_VEC_IN, CURR_FRM_INTERP_KERNEL_PARAM_BLK_SIZE, params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFile(XYLIST, 1, 2*params->numKeyPoints, 1, 2*params->numKeyPoints, params->inFileName1, 2);
       readInputFile(BASE_ADDR_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName2, 4);
       readInputFile(FINAL_ADDR_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName2, 4);
       readInputFile(PARAM_BLK_OFST_VEC_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName3, 2);
       readInputFile(C_REF_TRUTH_BASE_ADDR_OUT, 1, params->numKeyPoints, 1, params->numKeyPoints, refFile1, 4);
       readInputFile(C_REF_TRUTH_WEIGHT_OUT, 1, params->numKeyPoints, NUM_OUTPUTS, params->numKeyPoints, refFile2, 2);
    }
    for(j = 0; j < params->numKeyPoints; j++)
    {
        XLIST[j] = XYLIST[2*j];
        YLIST[j] = XYLIST[2*j+1];
    }

#ifdef __DEBUG
    for(j = 0; j < 2*params->numKeyPoints; j++)
    {
        printf("%4d ",  XLIST[j]);
        printf("%4d ",  YLIST[j]);
    }

    for(j = 0; j < params->numKeyPoints; j++)
    {
        printf("%4d \n", BASE_ADDR_IN[j]);
    }

    for(j = 0; j < params->numKeyPoints; j++)
    {
        printf("%4d \n", PARAM_BLK_OFST_VEC_IN[j]);
    }
#endif
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_weight_address_bilinear_interpolation_cn(XLIST,YLIST, BASE_ADDR_IN, FINAL_ADDR_IN, REF_WEIGHT_OUT, REF_BASE_ADDR_OUT, PARAM_BLK_OFST_VEC_IN, params->numKeyPoints, params->qFormatMaxFactor, 0 ,params->qShift, params->blkStride, params->outputStride);

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
            if(C_REF_TRUTH_WEIGHT_OUT[j*params->outputStride+i] != REF_WEIGHT_OUT[j*params->outputStride+i])
            {
                fail = 1;
                printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_WEIGHT_OUT[j*params->outputStride+i], C_REF_TRUTH_WEIGHT_OUT[j*params->outputStride+i], (j*OUT_STRIDE+i));
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

#ifdef __DEBUG
    printf("\n");
#endif

    for(i = 0; i < PARAM_BLK_SIZE_IN_WORDS*params->numKeyPoints; i++)
    {
        if(C_REF_TRUTH_BASE_ADDR_OUT[i] != REF_BASE_ADDR_OUT[i])
        {
            fail = 1;
            printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_BASE_ADDR_OUT[i], C_REF_TRUTH_BASE_ADDR_OUT[i], i);
            break;
        }
#ifdef __DEBUG
        printf("%3d ",REF_BASE_ADDR_OUT[i]);
#endif
    }
#ifdef __DEBUG
        printf("\n");
#endif
    printf(fail ? "FAIL\n":"PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(REF_WEIGHT_OUT, params->numKeyPoints, NUM_OUTPUTS, params->numKeyPoints, params->outFileName1, 2);
      writeOutputFile(REF_BASE_ADDR_OUT, PARAM_BLK_SIZE_IN_WORDS*params->numKeyPoints, 1, PARAM_BLK_SIZE_IN_WORDS*params->numKeyPoints, params->outFileName2, 4);
    }
}

int test_weight_address_bilinear_interpolation_vcop(sweight_address_bilinear_interpolation_Config * params)
{
    int i, j, iter, fail = 0, status = 0;

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU16(XYLIST,2*params->numKeyPoints);
      CreateRandPatternU32(BASE_ADDR_IN, params->numKeyPoints);
      CreateRandPatternU32(FINAL_ADDR_IN, params->numKeyPoints);
      CreatePatternU16(PARAM_BLK_OFST_VEC_IN, CURR_FRM_INTERP_KERNEL_PARAM_BLK_SIZE, params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFile(XYLIST, 1, 2*params->numKeyPoints, 1, 2*params->numKeyPoints, params->inFileName1, 2);
       readInputFile(BASE_ADDR_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName2, 4);
       readInputFile(FINAL_ADDR_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName2, 4);
       readInputFile(PARAM_BLK_OFST_VEC_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName3, 2);
    }
    for(j = 0; j < params->numKeyPoints; j++)
    {
        XLIST[j] = XYLIST[2*j];
        YLIST[j] = XYLIST[2*j+1];
    }
    printf("Number of KeyPoints = %d, Block Stride = %d\n", params->numKeyPoints, params->blkStride);

#ifdef __DEBUG
    for(j = 0; j < 2*params->numKeyPoints; j++)
    {
        printf("%4d ",  XLIST[j]);
        printf("%4d ",  YLIST[j]);
    }

    for(j = 0; j < params->numKeyPoints; j++)
    {
        printf("%4d \n", BASE_ADDR_IN[j]);
    }

    for(j = 0; j < params->numKeyPoints; j++)
    {
        printf("%4d \n", PARAM_BLK_OFST_VEC_IN[j]);
    }
#endif

#if VCOP_HOST_EMULATION
#else
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_weight_address_bilinear_interpolation_init(XLIST,YLIST, BASE_ADDR_IN, FINAL_ADDR_IN, WEIGHT_OUT, BASE_ADDR_OUT, PARAM_BLK_OFST_VEC_IN, params->numKeyPoints, params->qFormatMaxFactor, 0, params->qShift, params->blkStride, params->outputStride, __pblock_vcop_weight_address_bilinear_interpolation);
#endif

    for (iter = 0; iter <  params->numIter; iter++)
    {
        printf("Iteration %d:\n", iter);
#ifdef COMPARE_REFERENCE
        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
        vcop_weight_address_bilinear_interpolation_cn(XLIST,YLIST, BASE_ADDR_IN, FINAL_ADDR_IN, REF_WEIGHT_OUT, REF_BASE_ADDR_OUT, PARAM_BLK_OFST_VEC_IN, params->numKeyPoints, params->qFormatMaxFactor, 0, params->qShift, params->blkStride, params->outputStride);

#endif
        profiler_start();
#if VCOP_HOST_EMULATION
    vcop_weight_address_bilinear_interpolation(XLIST,YLIST, BASE_ADDR_IN, FINAL_ADDR_IN, WEIGHT_OUT, BASE_ADDR_OUT, PARAM_BLK_OFST_VEC_IN, params->numKeyPoints, params->qFormatMaxFactor, 0, params->qShift, params->blkStride, params->outputStride);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_weight_address_bilinear_interpolation_vloops(__pblock_vcop_weight_address_bilinear_interpolation);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
#endif
        profiler_end();

#ifdef COMPARE_REFERENCE

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
                if(WEIGHT_OUT[j*params->outputStride+i] != REF_WEIGHT_OUT[j*params->outputStride+i])
                {
                    fail = 1;
                    printf("C Reference Output = %d, VCOP Output = %d, i = %d\n",REF_WEIGHT_OUT[j*params->outputStride+i], WEIGHT_OUT[j*params->outputStride+i], (j*OUT_STRIDE+i));
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

    #ifdef __DEBUG
        printf("\n");
    #endif

        for(i = 0; i < PARAM_BLK_SIZE_IN_WORDS*params->numKeyPoints; i++)
        {
            if(BASE_ADDR_OUT[i] != REF_BASE_ADDR_OUT[i])
            {
                fail = 1;
                printf("C Reference Output = %d, VCOP Output = %d, i = %d\n",REF_BASE_ADDR_OUT[i], BASE_ADDR_OUT[i], i);
                break;
            }
    #ifdef __DEBUG
            printf("%3d ",BASE_ADDR_OUT[i]);
    #endif
        }
    #ifdef __DEBUG
            printf("\n");
    #endif
        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
#endif
    }
    profiler_deinit();

    printf(status ? "test_weight_address_bilinear_interpolation: FAIL\n":"test_weight_address_bilinear_interpolation: PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(WEIGHT_OUT, params->numKeyPoints, NUM_OUTPUTS, params->numKeyPoints, params->outFileName1, 2);
      writeOutputFile(BASE_ADDR_OUT, PARAM_BLK_SIZE_IN_WORDS*params->numKeyPoints, 1, PARAM_BLK_SIZE_IN_WORDS*params->numKeyPoints, params->outFileName2, 4);
    }

    return status;
}

int main()
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  sweight_address_bilinear_interpolation_Config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  printf("Validate Weight & Address Parameters Update Needed for Bilinear Interpolation of VCOP Kernel\n");
  params = (sweight_address_bilinear_interpolation_Config *)(&gConfig_weight_address_bilinear_interpolation);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_weight_address_bilinear_interpolation_vcop(params);
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
      status = readparamfile(configFileName, &gsTokenMap_weight_address_bilinear_interpolation[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_weight_address_bilinear_interpolation_vcop(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);
}
