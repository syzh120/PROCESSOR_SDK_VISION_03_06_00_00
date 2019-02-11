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
/*      vcop_calc_inverse_structure_tensor_2x2_tb.c                         */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel to compute inverse of       */
/*  structure tensor with C reference output                                */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_calc_inverse_structure_tensor_2x2' function with a random     */
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
#include "vcop_calc_inverse_structure_tensor_2x2_config.h"
#include "vcop_calc_inverse_structure_tensor_2x2_cn.h"

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_calc_inverse_structure_tensor_2x2_kernel.k"
#else
#include "vcop_host.h"
#include "vcop_calc_inverse_structure_tensor_2x2_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

//#define __DEBUG
#define COMPARE_REFERENCE
#define NUM_ITER (1)
#define NUM_KEYPOINTS     (8)
#define NUM_TENSORARR_ELEMENTS (3)
#define INPUT_STRIDE   (8)
#define OUTPUT_STRIDE  (16)

#pragma DATA_SECTION(TensorArrInp, "Adata");
static signed int TensorArrInp[NUM_TENSORARR_ELEMENTS*INPUT_STRIDE] = {0};

#pragma DATA_SECTION(D_norm, "Bdata");
static unsigned int D_norm[NUM_KEYPOINTS] = {0};

#pragma DATA_SECTION(D_nrsb, "Cdata");
static unsigned short D_nrsb[NUM_KEYPOINTS] = {0};

#pragma DATA_SECTION(scratch_norm, "Cdata");
static signed int scratch_norm[NUM_TENSORARR_ELEMENTS*INPUT_STRIDE] = {0};

#pragma DATA_SECTION(scratch_dividend, "Cdata");
static unsigned int scratch_dividend[NUM_TENSORARR_ELEMENTS*INPUT_STRIDE] = {0};

#pragma DATA_SECTION(InverseArr_OUT, "Adata");
static signed short InverseArr_OUT[NUM_TENSORARR_ELEMENTS*OUTPUT_STRIDE] = {0};

#pragma DATA_SECTION(REF_InverseArr_OUT, "Eoutdata");
static signed short REF_InverseArr_OUT[NUM_TENSORARR_ELEMENTS*OUTPUT_STRIDE] = {0};

#pragma DATA_SECTION(C_REF_TRUTH_InverseArr_OUT, "Eoutdata");
static signed short C_REF_TRUTH_InverseArr_OUT[NUM_TENSORARR_ELEMENTS*OUTPUT_STRIDE] = {0};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(scalc_inverse_structure_tensor_2x2_Config * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->inputStride      = INPUT_STRIDE;
  params->outputStride     = OUTPUT_STRIDE;
  params->numKeyPoints     = NUM_KEYPOINTS;
  params->numIter          = NUM_ITER;
  params->writeOutput      = 0;
  params->seedForRND       = 0;
}

int writeOutputFile(short * output, scalc_inverse_structure_tensor_2x2_Config * params)
{
    FILE * fp;
    int i,j;
    fp = fopen(params->outFileName, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(j = 0; j < NUM_TENSORARR_ELEMENTS; j++)
    {
        for(i = 0; i < params->numKeyPoints; i++)
        {
            if(i < (params->numKeyPoints-1))
            {
                fprintf(fp, "%d  %d  ", output[j*params->outputStride+2*i], output[j*params->outputStride+2*i+1]);
            }
            else
            {
                fprintf(fp, "%d  %d\n", output[j*params->outputStride+2*i], output[j*params->outputStride+2*i+1]);
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

static int readDeterminantInputFromTxtFile(unsigned int *d_norm, unsigned short *d_nrsb, unsigned short n, char * filename)
{
  int k;
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
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    LinePtr = inputLine;
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    d_nrsb[k] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    d_norm[k] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
  }
  fclose(fp);
  return(0);
}

static void CreateRandPatternS32(int *tensorArr, unsigned short n)
{
    int i,j;
#ifdef __DEBUG
    printf("Structure Tensor Elements Per Key Point SumIx2 ; SumIy2; SumIxIy:\n");
#endif

    for(i = 0; i < NUM_TENSORARR_ELEMENTS; i++)
    {
        for(j = 0; j < n; j++)
        {
            tensorArr[i*INPUT_STRIDE+j] = (rand() << (rand()%4)) | rand();
#ifdef __DEBUG
            printf("%12d ",  tensorArr[i*INPUT_STRIDE+j]);
#endif
        }
        printf("\n");
    }
}

static void CreateRandPatternDeterminant(unsigned int *d_norm, unsigned short *d_nrsb, unsigned short n)
{
    int j;

#ifdef __DEBUG
    printf("Determinant in normalized form, d_nrsb ; d_norm:\n");
#endif

    for(j = 0; j < n; j++)
    {
        d_nrsb[j] = (rand() & 0xFF);
        d_norm[j]  = ((rand() << (rand()%4)) | rand());
#ifdef __DEBUG
        printf("%12d %12d\n",  d_nrsb[j], d_norm[j]);
#endif
    }
}

void test_calc_inverse_structure_tensor_2x2_c_reference(scalc_inverse_structure_tensor_2x2_Config * params)
{
    int i, j, fail;
    char refFile[] = "..\\testvecs\\reference\\fracExp_sumIx2byD_sumIy2byD_sumIxybyD.txt";

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternS32(TensorArrInp, params->numKeyPoints);
      CreateRandPatternDeterminant(D_norm, D_nrsb, params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
      readDeterminantInputFromTxtFile(D_norm, D_nrsb, params->numKeyPoints, params->inFileName1);
      readInputFile(TensorArrInp, 1, params->numKeyPoints, NUM_TENSORARR_ELEMENTS, params->inputStride, params->inFileName2, 5);
      readInputFile(C_REF_TRUTH_InverseArr_OUT, 1, (2*params->numKeyPoints), NUM_TENSORARR_ELEMENTS, params->outputStride, refFile, 3);

#ifdef __DEBUG
        printf("Structure Tensor Elements Per Key Point SumIx2 ; SumIy2; SumIxIy:\n");
#endif

        for(i = 0; i < NUM_TENSORARR_ELEMENTS; i++)
        {
            for(j = 0; j < params->numKeyPoints; j++)
            {
#ifdef __DEBUG
                printf("%12d ",  TensorArrInp[i*params->inputStride+j]);
#endif
            }
            printf("\n");
        }

#ifdef __DEBUG
        printf("Determinant in normalized form, D_nrsb ; D_norm:\n");
#endif

        for(j = 0; j < params->numKeyPoints; j++)
        {
#ifdef __DEBUG
            printf("%12d %12d\n",  D_nrsb[j], D_norm[j]);
#endif
        }
    }

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_calc_inverse_structure_tensor_2x2_cn(TensorArrInp, D_nrsb, D_norm, REF_InverseArr_OUT, params->inputStride, params->outputStride, 4, params->numKeyPoints);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
#ifdef __DEBUG
    printf("\n");
#endif
    for(i = 0; i < NUM_TENSORARR_ELEMENTS; i++)
    {
        for(j = 0; j < 2*params->numKeyPoints; j++)
        {
            if(C_REF_TRUTH_InverseArr_OUT[i*params->outputStride+j] != REF_InverseArr_OUT[i*params->outputStride+j])
            {
                fail = 1;
                //printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_InverseArr_OUT[i*params->outputStride+j], C_REF_TRUTH_InverseArr_OUT[i*params->outputStride+j], (i*params->outputStride+j));
                //break;
            }
#ifdef __DEBUG
            printf("%12d ",REF_InverseArr_OUT[i*params->outputStride+j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }

    printf(fail ? "FAIL\n":"PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(REF_InverseArr_OUT, params);
    }
}

void test_calc_inverse_structure_tensor_2x2_vcop(scalc_inverse_structure_tensor_2x2_Config * params)
{
    int i, j, iter, fail = 0, status = 0;

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternS32(TensorArrInp, params->numKeyPoints);
      CreateRandPatternDeterminant(D_norm, D_nrsb, params->numKeyPoints);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
      readDeterminantInputFromTxtFile(D_norm, D_nrsb, params->numKeyPoints, params->inFileName1);
      readInputFile(TensorArrInp, 1, params->numKeyPoints, NUM_TENSORARR_ELEMENTS, params->inputStride, params->inFileName2, 5);

#ifdef __DEBUG
        printf("Structure Tensor Elements Per Key Point SumIx2 ; SumIy2; SumIxIy:\n");
#endif

        for(i = 0; i < NUM_TENSORARR_ELEMENTS; i++)
        {
            for(j = 0; j < params->numKeyPoints; j++)
            {
#ifdef __DEBUG
                printf("%12d ",  TensorArrInp[i*params->inputStride+j]);
#endif
            }
            printf("\n");
        }

#ifdef __DEBUG
        printf("Determinant in normalized form, D_nrsb ; D_norm:\n");
#endif

        for(j = 0; j < params->numKeyPoints; j++)
        {
#ifdef __DEBUG
            printf("%12d %12d\n",  D_nrsb[j], D_norm[j]);
#endif
        }
    }

    printf("Number of KeyPoints = %d\n", params->numKeyPoints);

#if VCOP_HOST_EMULATION
#else
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_calc_inverse_structure_tensor_2x2_init(TensorArrInp, D_nrsb, D_norm, InverseArr_OUT, scratch_norm, scratch_dividend, params->inputStride, params->outputStride, 4, params->numKeyPoints, __pblock_vcop_calc_inverse_structure_tensor_2x2);
#endif
    for (iter = 0; iter <  params->numIter; iter++)
    {
        printf("Iteration %d:\n", iter);
#ifdef COMPARE_REFERENCE
        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to be tested                    */
        /*---------------------------------------------------------------------*/
        vcop_calc_inverse_structure_tensor_2x2_cn(TensorArrInp, D_nrsb, D_norm, REF_InverseArr_OUT, params->inputStride, params->outputStride, 4, params->numKeyPoints);
#endif
        profiler_start();
#if VCOP_HOST_EMULATION
        vcop_calc_inverse_structure_tensor_2x2(TensorArrInp, D_nrsb, D_norm, InverseArr_OUT, scratch_norm, scratch_dividend, params->inputStride, params->outputStride, 4, params->numKeyPoints);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_calc_inverse_structure_tensor_2x2_vloops(__pblock_vcop_calc_inverse_structure_tensor_2x2);
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
        for(i = 0; i < NUM_TENSORARR_ELEMENTS; i++)
        {
            for(j = 0; j < 2*params->numKeyPoints; j++)
            {
                if(InverseArr_OUT[i*params->outputStride+j] != REF_InverseArr_OUT[i*params->outputStride+j])
                {
                    fail = 1;
                    //printf("C Reference Output = %d, VCOP Output = %d, i = %d\n",REF_InverseArr_OUT[i*params->outputStride+j], InverseArr_OUT[i*params->outputStride+j], (i*params->outputStride+j));
                    //break;
                }
#ifdef __DEBUG
                printf("%12d ",InverseArr_OUT[i*params->outputStride+j]);
#endif
            }
#ifdef __DEBUG
            printf("\n");
#endif
        }

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
#endif
    }
    profiler_deinit();

    printf(status ? "test_calc_inverse_structure_tensor_2x2: FAIL\n":"test_calc_inverse_structure_tensor_2x2: PASS\n");

    if(params->writeOutput)
    {
      writeOutputFile(InverseArr_OUT, params);
    }
}

int main()
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  scalc_inverse_structure_tensor_2x2_Config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  printf("Validate Inverse of Structure Tensor 2x2 with VCOP Kernel\n");
  params = (scalc_inverse_structure_tensor_2x2_Config *)(&gConfig_calc_inverse_structure_tensor_2x2);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_calc_inverse_structure_tensor_2x2_vcop(params);
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
      status = readparamfile(configFileName, &gsTokenMap_calc_inverse_structure_tensor_2x2[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_calc_inverse_structure_tensor_2x2_vcop(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);
}
