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
/*      vcop_multiblock_gradient_xy_tb.c                                    */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel for multi block gradient    */
/*  compute function with C reference output                                */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_multiblock_gradient_xy' function with a random input strings  */
/*      of varying lengths.                                                 */
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
#include "vcop_multiblock_gradient_xy_config.h"
#include "vcop_multiblock_gradient_xy_cn.h"

#if VCOP_HOST_EMULATION
#include "vcop_host.h"
#include "../src_kernelC/vcop_multiblock_gradient_xy_kernel.k"
#else
#include "vcop_multiblock_gradient_xy_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

//#define __DEBUG
#define COMPARE_REFERENCE
#define NUM_ITER (1)

#define NUM_BLOCKS   (8)
#define BLOCK_HEIGHT (8)
#define BLOCK_WIDTH  (8)
#define BLOCK_OFFSET (10)
#define IMG_STRIDE (NUM_BLOCKS * BLOCK_OFFSET)
#define IMG_HEIGHT (BLOCK_HEIGHT+2)    //Image height should be at least (BLOCK_HEIGHT+2)

#define OUT_WIDTH  (BLOCK_WIDTH)
#define OUT_HEIGHT (NUM_BLOCKS * (BLOCK_HEIGHT))

#pragma DATA_SECTION(IMAGE, "Adata");
static unsigned char IMAGE[IMG_STRIDE*IMG_HEIGHT] = {0x00};

#pragma DATA_SECTION(INTLVGRADXY_OUT, "Bdata");
static short INTLVGRADXY_OUT[2*OUT_HEIGHT*OUT_WIDTH+2*NUM_BLOCKS*7] = {0x00};

#pragma DATA_SECTION(REF_INTLVGRADXY_OUT, "Eoutdata");
static short REF_INTLVGRADXY_OUT[2*OUT_HEIGHT*OUT_WIDTH+2*NUM_BLOCKS*7] = {0x00};

#pragma DATA_SECTION(C_REF_TRUTH_OUT, "Eoutdata");
static short C_REF_TRUTH_OUT[2*OUT_HEIGHT*OUT_WIDTH+2*NUM_BLOCKS*7] = {0x00};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(smultiblock_gradient_xy_Config * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->inputStride  = IMG_STRIDE;
  params->blkWidth     = BLOCK_WIDTH;
  params->blkHeight    = BLOCK_HEIGHT;
  params->blkOffset    = BLOCK_OFFSET;
  params->numBlocks    = NUM_BLOCKS;
  params->numIter      = NUM_ITER;
  params->writeOutput  = 0;
  params->seedForRND   = 0;
}

int TestKernel_WriteOutput(short * output, smultiblock_gradient_xy_Config * params)
{
    FILE * fp;
    int i,j,k;
    fp = fopen(params->outFileName, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(j = 0; j < params->numBlocks; j++)
    {
        k = j*((params->blkHeight)*(params->blkWidth)+((params->blkWidth+7)/8)*8-params->blkWidth)*2;
        for(i = 0; i < (2*(params->blkHeight)*(params->blkWidth)); i++)
        {
            if(i<((2*(params->blkHeight)*(params->blkWidth))-1))
            {
                fprintf(fp, "%d ", output[k+i]);
            }
            else
            {
                fprintf(fp, "%d\n", output[k+i]);
            }
        }
    }
    fclose(fp);

    return (0);
}

int TestKernel_ReadInput(void * input, smultiblock_gradient_xy_Config * params, int dataType)
{
    int i, j;
    FILE * fp;
    char * LinePtr;
    int status;
    int value;
    char inputLine[MAX_INPUT_LINE_SIZE];
    char inputValue[MAX_INPUT_VALUE_SIZE];

    fp = fopen(params->inFileName, "r");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }
    for(i = 0; i < IMG_HEIGHT; i++)
    {
        memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
        status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
        if ((status == EOF) || (status == 0))
        {
            printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
            return(-1);
        }
        LinePtr = inputLine;
        for(j = 0; j < params->inputStride; j++)
        {
            sscanf(LinePtr, "%d",&value);
            sscanf(LinePtr, "%s",inputValue);
            if(dataType == 5)
            {
              int * ptr = (int * )input;
              ptr[i*params->inputStride+j] = value;
            }
            else if(dataType == 4)
            {
              unsigned int * ptr = (unsigned int * )input;
              ptr[i*params->inputStride+j] = value;
            }
            else if(dataType == 3)
            {
              short * ptr = (short * )input;
              ptr[i*params->inputStride+j] = value;
            }
            else if(dataType == 2)
            {
              unsigned short * ptr = (unsigned short * )input;
              ptr[i*params->inputStride+j] = value;
            }
            else if(dataType == 1)
            {
              char * ptr = (char * )input;
              ptr[i*params->inputStride+j] = value;
            }
            else if(dataType ==0)
            {
              unsigned char * ptr = (unsigned char * )input;
              ptr[i*params->inputStride+j] = value;
            }
            LinePtr = moveToNextElement(inputValue,LinePtr);
        }
    }

  fclose(fp);
  return(0);

}

void test_multiblock_gradient_xy_c_reference()
{
    int i, j, k, fail;

    memset(IMAGE, 0, sizeof(IMAGE));

    for(i = 0; i < IMG_HEIGHT; i++)
    {
        for(j = 0; j < IMG_STRIDE; j++)
        {
            IMAGE[i*IMG_STRIDE + j] = i;
        }
    }

    /* Initialize C Reference Truth */
    for(j = 0; j < NUM_BLOCKS; j++)
    {
        k = j*((BLOCK_HEIGHT)*(BLOCK_WIDTH)+((BLOCK_WIDTH+7)/8)*8-BLOCK_WIDTH)*2;
        for(i = 1; i < (2*(BLOCK_HEIGHT)*(BLOCK_WIDTH)); i=i+2)
        {
            C_REF_TRUTH_OUT[k+i] = 0x0002;
        }
    }

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_multiblock_gradient_xy_cn(IMAGE, REF_INTLVGRADXY_OUT, IMG_STRIDE, BLOCK_WIDTH,
                    BLOCK_HEIGHT, BLOCK_OFFSET, NUM_BLOCKS);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
    for(j = 0; j < NUM_BLOCKS; j++)
    {
        k = j*((BLOCK_HEIGHT)*(BLOCK_WIDTH)+((BLOCK_WIDTH+7)/8)*8-BLOCK_WIDTH)*2;
        for(i = 0; i < (2*(BLOCK_HEIGHT)*(BLOCK_WIDTH)); i++)
        {
            if(C_REF_TRUTH_OUT[k+i] != REF_INTLVGRADXY_OUT[k+i])
            {
                fail = 1;
                printf("C Reference Output = %d, C Reference TRUTH = %d, i = %d\n",REF_INTLVGRADXY_OUT[k+i], C_REF_TRUTH_OUT[k+i], (k+i));
                break;
            }
        }
    }
    printf(fail ? "FAIL\n":"PASS\n");
}

static void CreateRandPatternU8(unsigned char *p, unsigned short h, unsigned short stride)
{
    int i, j;

#ifdef __DEBUG
    printf("Input Block:\n");
#endif

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < stride; j++)
        {
            IMAGE[i*stride + j] = (rand() & 0xFF);
#ifdef __DEBUG
            printf("%4d, ",  IMAGE[i*stride + j]);
#endif
        }
#ifdef __DEBUG
          printf("\n");
#endif
      }
}

int test_multiblock_gradient_xy_vcop(smultiblock_gradient_xy_Config * params)
{
    int i, j, k, iter, fail = 0, status = 0;

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN")==0)
    {
      printf("Pattern Generation Seed = %d\n", params->seedForRND);
      srand(params->seedForRND);
      CreateRandPatternU8(IMAGE, IMG_HEIGHT, params->inputStride);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE")==0)
    {
       TestKernel_ReadInput(IMAGE, params, 0);
    }

    printf("Block size = %dx%d \n", params->blkWidth, (params->blkHeight * params->numBlocks));
#if VCOP_HOST_EMULATION
#else
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_multiblock_gradient_xy_init(IMAGE, INTLVGRADXY_OUT, params->inputStride, params->blkWidth, params->blkHeight, params->blkOffset, params->numBlocks, __pblock_vcop_multiblock_gradient_xy);
#endif
    for (iter = 0; iter <  params->numIter; iter++)
    {
        printf("Iteration %d:\n", iter);
#ifdef COMPARE_REFERENCE
        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
        vcop_multiblock_gradient_xy_cn(IMAGE, REF_INTLVGRADXY_OUT, params->inputStride, params->blkWidth, params->blkHeight, params->blkOffset, params->numBlocks);
#endif
        profiler_start();
#if VCOP_HOST_EMULATION
        vcop_multiblock_gradient_xy(IMAGE, INTLVGRADXY_OUT, params->inputStride, params->blkWidth, params->blkHeight, params->blkOffset, params->numBlocks);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_multiblock_gradient_xy_vloops(__pblock_vcop_multiblock_gradient_xy);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
#endif
        profiler_end();

#ifdef COMPARE_REFERENCE
        fail = 0;
        for(j = 0; j < params->numBlocks; j++)
        {
            k = j*((params->blkHeight)*(params->blkWidth)+((params->blkWidth+7)/8)*8-params->blkWidth)*2;
            for(i = 0; i < (2*(params->blkHeight)*(params->blkWidth)); i++)
            {
                if(INTLVGRADXY_OUT[k+i] != REF_INTLVGRADXY_OUT[k+i])
                {
                    fail = 1;
                    printf("C Reference Output = %d, VCOP Computed Output = %d, i = %d\n",REF_INTLVGRADXY_OUT[k+i], INTLVGRADXY_OUT[k+i], (k+i));
                    break;
                }
            }
        }

#ifdef __DEBUG
        printf("\nVCOP Output:\n");
        for(j = 0; j < params->numBlocks; j++)
        {
            k = j*((params->blkHeight)*(params->blkWidth)+((params->blkWidth+7)/8)*8-params->blkWidth)*2;
            for(i = 0; i < (2*(params->blkHeight)*(params->blkWidth)); i++)
            {
                printf("%3d ",INTLVGRADXY_OUT[k+i]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nReference Output:\n");
        for(j = 0; j < params->numBlocks; j++)
        {
            k = j*((params->blkHeight)*(params->blkWidth)+((params->blkWidth+7)/8)*8-params->blkWidth)*2;
            for(i = 0; i < (2*(params->blkHeight)*(params->blkWidth)); i++)
            {
                printf("%3d ",REF_INTLVGRADXY_OUT[k+i]);
            }
            printf("\n");
        }
        printf("\n");
#endif
        printf(fail ? "FAIL\n\n" : "PASS\n\n");
        status |= fail;
#endif
    }
    profiler_deinit();

    printf(status ? "test_multiblock_gradient_xy: FAIL\n":"test_multiblock_gradient_xy: PASS\n");

    if(params->writeOutput)
    {
      TestKernel_WriteOutput(INTLVGRADXY_OUT, params);
    }

    return (0);
}

int main()
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  smultiblock_gradient_xy_Config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  printf("Validate Multi Block Gradient XY VCOP Kernel\n");
  test_multiblock_gradient_xy_c_reference();

  params = (smultiblock_gradient_xy_Config *)(&gConfig_multiblock_gradient);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_multiblock_gradient_xy_vcop(params);
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
      status = readparamfile(configFileName, &gsTokenMap_multiblock_gradient[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      test_multiblock_gradient_xy_vcop(params);
    }
    else
    {
      printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
    }
  }
  fclose(fp);
  return (0);
}
