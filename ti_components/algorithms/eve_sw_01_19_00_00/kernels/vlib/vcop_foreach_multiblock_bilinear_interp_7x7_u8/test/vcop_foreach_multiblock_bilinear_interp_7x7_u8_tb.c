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
/*      vcop_foreach_multiblock_bilinear_interp_7x7_u8_tb.c                 */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel for computing bilinear      */
/*  interpolation of image pixels wherein the output block is not centered  */
/*  around the intput block with corresponding C reference output           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_foreach_multiblock_bilinear_interp_7x7_u8' function with      */
/*      a random input or file based inputs                                 */
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

//#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"
#include "eve_profile.h"
#include "vcop_foreach_multiblock_bilinear_interp_7x7_u8_config.h"
#include "vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn.h"

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel.k"
#else
#include "vcop_host.h"
#include "vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

//#define __DEBUG
#define COMPARE_REFERENCE
#define NUM_ITER (1)

#define NUM_KEYPOINTS     (8)
#define NUM_OUTPUTS       (4)              //Factor of 4 is used since we have 4 output weight vectors namely w0, w1, w2, w3
#define INP_BLOCK_HEIGHT  (31)
#define INP_BLOCK_WIDTH   (31)
#define IMG_STRIDE        (INP_BLOCK_WIDTH)

#define OUT_STRIDE (8)
#define OUT_WIDTH  (8)
#define OUT_HEIGHT (7)

#pragma DATA_SECTION(IMAGE, "Adata");
static unsigned char IMAGE[IMG_STRIDE*INP_BLOCK_HEIGHT*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(BASE_ADDR_IN, "Bdata");
static unsigned char *BASE_ADDR_IN[NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(WEIGHTS_INP, "Cdata");
static unsigned short WEIGHTS_INP[NUM_OUTPUTS*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(BILINEAR_INTERP_OUT, "Cdata");
static unsigned char  BILINEAR_INTERP_OUT[OUT_HEIGHT*OUT_STRIDE*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(REF_BILINEAR_INTERP_OUT, "Eoutdata");
static unsigned char  REF_BILINEAR_INTERP_OUT[OUT_HEIGHT*OUT_STRIDE*NUM_KEYPOINTS] = {0x00};

#pragma DATA_SECTION(C_REF_TRUTH_OUT, "Eoutdata");
static unsigned char  C_REF_TRUTH_OUT[OUT_HEIGHT*OUT_STRIDE*NUM_KEYPOINTS] = {0x00};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sforeach_multiblock_bilinear_interp_7x7_u8_Config * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->input1Stride     = IMG_STRIDE;
  params->input2Stride     = NUM_KEYPOINTS;
  params->outputStride     = OUT_STRIDE;
  params->outBlkWidth      = OUT_WIDTH;
  params->outBlkHeight     = OUT_HEIGHT;
  params->numKeyPoints     = NUM_KEYPOINTS;
  params->numIter          = NUM_ITER;
  params->writeOutput      = 0;
  params->seedForRND       = 0;
}

int writeOutputFile(unsigned char * output, sforeach_multiblock_bilinear_interp_7x7_u8_Config * params)
{
    FILE * fp;
    int i,j,k;
    fp = fopen(params->outFileName, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(k = 0; k < params->numKeyPoints; k++)
    {
        for(j = 0; j < (params->outBlkHeight); j++)
        {
            for(i = 0; i < (params->outBlkWidth); i++)
            {
                if(i < ((params->outBlkWidth)-1))
                {
                    fprintf(fp, "%d   ", output[k*params->outputStride*(params->outBlkHeight)+j*params->outputStride+i]);
                }
                else
                {
                    fprintf(fp, "%d\n", output[k*params->outputStride*(params->outBlkHeight)+j*params->outputStride+i]);
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

static void CreateRandPatternU8(unsigned char *input, unsigned short n, unsigned short w, unsigned short h, unsigned short stride)
{
    int i, j, k;

#ifdef __DEBUG
    printf("Input Image & Weight Input For Bilinear Interpolation 7x7 U8 Kernel:\n");
#endif

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < h; i++)
        {
            for(j = 0; j < w; j++)
            {
                input[k*stride*h+i*stride+j] = (rand() & 0xFF);
#ifdef __DEBUG
                printf("%4d ",  input[k*stride*h+i*stride+j]);
#endif
            }
#ifdef __DEBUG
            printf("\n");
#endif
        }
    }
}

static void CreateRandPatternU32(unsigned char *addrlist[], unsigned short n)
{
    int j;

#ifdef __DEBUG
    printf("Base address list:\n");
#endif

    for(j = 0; j < n; j++)
    {
        addrlist[j] = (unsigned char*)((((rand() & 0xFFFF) << 16) | (rand() & 0xFFFF)));
#ifdef __DEBUG
        printf("%4d ",  addrlist[j]);
#endif
    }
    printf("\n");
}

static void CreateRandPatternWtU16(unsigned short *input, unsigned short w, unsigned short h, unsigned short stride)
{
    int i, j;
    unsigned char dx, dy, w0, w1, w2, w3;

#ifdef __DEBUG
    printf("IWeight Input For Bilinear Interpolation 7x7 U8 Kernel:\n");
#endif

    for(j = 0; j < w; j++)
    {
        dx = (rand() & 0xF);
        dy = (rand() & 0xF);

        w0 = dx * dy;
        w1 = (15 - dx) * dy;
        w2 = dx * (15 - dy);
        w3 = (15 - dx) * (15 - dy);
        input[j] =  w0;
        input[stride + j] = w1;
        input[2*stride + j] = w2;
        input[3*stride + j] = w3;
    }

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j++)
        {
#ifdef __DEBUG
            printf("%4d ",  input[i*stride+j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}

void test_foreach_multiblock_bilinear_interp_7x7_u8_c_reference(sforeach_multiblock_bilinear_interp_7x7_u8_Config * params)
{
    int i, j, k, index, fail;
    char imageFile[] = "../testvecs/input/input_image.txt";
    char refFile[] = "../testvecs/reference/image_pix_bilinear_interp_output.txt";

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU8(IMAGE, params->numKeyPoints, INP_BLOCK_WIDTH, INP_BLOCK_HEIGHT, params->input1Stride);
      CreateRandPatternWtU16(WEIGHTS_INP, params->numKeyPoints, NUM_OUTPUTS, params->input2Stride);
      CreateRandPatternU32(BASE_ADDR_IN, params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFile(IMAGE, params->numKeyPoints, INP_BLOCK_WIDTH, INP_BLOCK_HEIGHT, params->input1Stride, imageFile, 0);
       readInputFile(BASE_ADDR_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName1, 4);
       readInputFile(WEIGHTS_INP, 1, params->numKeyPoints, NUM_OUTPUTS, params->input2Stride, params->inFileName2, 2);
       readInputFile(C_REF_TRUTH_OUT, params->numKeyPoints, params->outBlkWidth, params->outBlkHeight, params->outputStride, refFile, 0);

        for(j = 0; j < params->numKeyPoints; j++)
        {
            BASE_ADDR_IN[j] = (unsigned char*)((unsigned int)BASE_ADDR_IN[j] + (unsigned int)&IMAGE[0]);
        }
    #ifdef __DEBUG
        printf("IMAGE INPUT FROM FILE %d %d:\n", &IMAGE, IMAGE);
    #endif

        for(k = 0; k < params->numKeyPoints; k++)
        {
            for(i = 0; i < INP_BLOCK_HEIGHT; i++)
            {
                for(j = 0; j < INP_BLOCK_WIDTH; j++)
                {
    #ifdef __DEBUG
                    printf("%4d ",  IMAGE[k*params->input1Stride*INP_BLOCK_HEIGHT+i*params->input1Stride+j]);
    #endif
                }
    #ifdef __DEBUG
                printf("\n");
    #endif
            }
        }

    #ifdef __DEBUG
        for(j = 0; j < params->numKeyPoints; j++)
        {
            printf("%4d \n", BASE_ADDR_IN[j]);
        }
    #endif

        for(i = 0; i < NUM_OUTPUTS; i++)
        {
            for(j = 0; j < params->numKeyPoints; j++)
            {
    #ifdef __DEBUG
                printf("%4d ",  WEIGHTS_INP[i*params->input2Stride+j]);
    #endif
            }
    #ifdef __DEBUG
            printf("\n");
    #endif
        }
    }

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn(BASE_ADDR_IN, WEIGHTS_INP, REF_BILINEAR_INTERP_OUT, params->input1Stride, params->input2Stride, params->outputStride,
            params->outBlkWidth, params->outBlkHeight, 8 ,params->numKeyPoints);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
#ifdef __DEBUG
    printf("\n");
#endif
    for(k = 0; k < params->numKeyPoints; k++)
    {
        for(j = 0; j < (params->outBlkHeight); j++)
        {
            for(i = 0; i < (params->outBlkWidth); i++)
            {
                index = k*params->outputStride*(params->outBlkHeight)+j*params->outputStride+i;
                if(C_REF_TRUTH_OUT[index] != REF_BILINEAR_INTERP_OUT[index])
                {
                    fail = 1;
                    //printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_BILINEAR_INTERP_OUT[index], C_REF_TRUTH_OUT[index], index);
                    //break;
                }
#ifdef __DEBUG
                printf("%3d ",REF_BILINEAR_INTERP_OUT[index]);
#endif
            }
#ifdef __DEBUG
        printf("\n");
#endif
        }
    }
    printf(fail ? "FAIL\n":"PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(REF_BILINEAR_INTERP_OUT, params);
    }
}

void test_foreach_multiblock_bilinear_interp_7x7_u8_vcop(sforeach_multiblock_bilinear_interp_7x7_u8_Config * params)
{
    int i, j, k, index, iter, fail = 0, status = 0;
    char imageFile[] = "../testvecs/input/input_image.txt";
    unsigned char *OUT_ADDR_LIST[NUM_KEYPOINTS];
    unsigned short *WGT_ADDR_LIST[NUM_KEYPOINTS];

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU8(IMAGE, params->numKeyPoints, INP_BLOCK_WIDTH, INP_BLOCK_HEIGHT, params->input1Stride);
      CreateRandPatternWtU16(WEIGHTS_INP, params->numKeyPoints, NUM_OUTPUTS, params->input2Stride);
      CreateRandPatternU32(BASE_ADDR_IN, params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       readInputFile(IMAGE, params->numKeyPoints, INP_BLOCK_WIDTH, INP_BLOCK_HEIGHT, params->input1Stride, imageFile, 0);
       readInputFile(BASE_ADDR_IN, 1, params->numKeyPoints, 1, params->numKeyPoints, params->inFileName1, 4);
       readInputFile(WEIGHTS_INP, 1, params->numKeyPoints, NUM_OUTPUTS, params->input2Stride, params->inFileName2, 2);

        for(j = 0; j < params->numKeyPoints; j++)
        {
            BASE_ADDR_IN[j] = (unsigned char*)((unsigned int)BASE_ADDR_IN[j] + (unsigned int)&IMAGE[0]);
        }
    #ifdef __DEBUG
        printf("IMAGE INPUT FROM FILE %d %d:\n", &IMAGE, IMAGE);
    #endif

        for(k = 0; k < params->numKeyPoints; k++)
        {
            for(i = 0; i < INP_BLOCK_HEIGHT; i++)
            {
                for(j = 0; j < INP_BLOCK_WIDTH; j++)
                {
    #ifdef __DEBUG
                    printf("%4d ",  IMAGE[k*params->input1Stride*INP_BLOCK_HEIGHT+i*params->input1Stride+j]);
    #endif
                }
    #ifdef __DEBUG
                printf("\n");
    #endif
            }
        }

    #ifdef __DEBUG
        for(j = 0; j < params->numKeyPoints; j++)
        {
            printf("%4d \n", BASE_ADDR_IN[j]);
        }
    #endif

        for(i = 0; i < NUM_OUTPUTS; i++)
        {
            for(j = 0; j < params->numKeyPoints; j++)
            {
    #ifdef __DEBUG
                printf("%4d ",  WEIGHTS_INP[i*params->input2Stride+j]);
    #endif
            }
    #ifdef __DEBUG
            printf("\n");
    #endif
        }
    }

    printf("Output Block size = %dx%d \n", params->outBlkWidth, (params->outBlkHeight * params->numKeyPoints));

    for(j = 0; j < params->numKeyPoints; j++)
    {
        OUT_ADDR_LIST[j] = (unsigned char*)(((unsigned int)BILINEAR_INTERP_OUT) + j*params->outputStride*params->outBlkHeight);
        WGT_ADDR_LIST[j] = (unsigned short*)(((unsigned int)WEIGHTS_INP) + j*2);
    }
   
#if VCOP_HOST_EMULATION
#else   
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(BASE_ADDR_IN, WGT_ADDR_LIST, OUT_ADDR_LIST, params->input1Stride, params->input2Stride, params->outputStride,
            params->outBlkWidth, params->outBlkHeight, 8, params->numKeyPoints, __pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8);
#endif
    for (iter = 0; iter <  params->numIter; iter++)
    {
        printf("Iteration %d:\n", iter);
#ifdef COMPARE_REFERENCE
        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
        vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn(BASE_ADDR_IN, WEIGHTS_INP, REF_BILINEAR_INTERP_OUT, params->input1Stride, params->input2Stride, params->outputStride,
                params->outBlkWidth, params->outBlkHeight, 8, params->numKeyPoints);

#endif
        profiler_start();
#if VCOP_HOST_EMULATION
    vcop_foreach_multiblock_bilinear_interp_7x7_u8(BASE_ADDR_IN, WGT_ADDR_LIST, OUT_ADDR_LIST, params->input1Stride, params->input2Stride, params->outputStride,
            params->outBlkWidth, params->outBlkHeight, 8, params->numKeyPoints);

#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(__pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8);
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
        for(k = 0; k < params->numKeyPoints; k++)
        {
            for(j = 0; j < (params->outBlkHeight); j++)
            {
                for(i = 0; i < (params->outBlkWidth); i++)
                {
                    index = k*params->outputStride*(params->outBlkHeight)+j*params->outputStride+i;
                    if(BILINEAR_INTERP_OUT[index] != REF_BILINEAR_INTERP_OUT[index])
                    {
                        fail = 1;
                        printf("C Reference Output = %d, VCOP Output = %d, i = %d\n",REF_BILINEAR_INTERP_OUT[index], BILINEAR_INTERP_OUT[index], index);
                        break;
                    }
    #ifdef __DEBUG
                    printf("%3d ",BILINEAR_INTERP_OUT[index]);
    #endif
                }
    #ifdef __DEBUG
            printf("\n");
    #endif
            }
        }
        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
#endif
    }

    profiler_deinit();

    printf(status ? "test_foreach_multiblock_bilinear_interp_7x7_u8: FAIL\n":"test_foreach_multiblock_bilinear_interp_7x7_u8: PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(BILINEAR_INTERP_OUT, params);
    }
}

int main()
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  sforeach_multiblock_bilinear_interp_7x7_u8_Config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  printf("Validate Bilinear Interpolation Kernel Using for each loop VCOP Kernel\n");
  params = (sforeach_multiblock_bilinear_interp_7x7_u8_Config *)(&gConfig_foreach_multiblock_bilinear_interp_7x7_u8);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_foreach_multiblock_bilinear_interp_7x7_u8_vcop(params);
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
      status = readparamfile(configFileName, &gsTokenMap_foreach_multiblock_bilinear_interp_7x7_u8[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_foreach_multiblock_bilinear_interp_7x7_u8_vcop(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);
}
