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

/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.                                                  */
/*                      All Rights Reserved                                                                                      */
/*==========================================================================*/


#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_fast9_score_config.h"
#include "../inc/vcop_fast9score_c.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_fast9_score_kernel.k"    // kernel source
#else
  #include "vcop_fast9_score_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define NUM_FEATURES     (32)
#define THR              (1)
#define PITCH            (64)
#define NUM_ITER         (1)
#define COMPARE_REFERENCE (1)

#pragma DATA_ALIGN(in_temp, 32);
#pragma DATA_SECTION (in_temp, "Adata");
unsigned char in_temp[NUM_FEATURES*VCOP_SIMD_WIDTH*VCOP_SIMD_WIDTH] = {0x0};

#pragma DATA_ALIGN(pTemp_buf, 32);
#pragma DATA_SECTION (pTemp_buf, "Bdata");
unsigned char pTemp_buf[NUM_FEATURES*VCOP_SIMD_WIDTH*9] = {0x0};

#pragma DATA_ALIGN(pTemp, 32);
#pragma DATA_SECTION (pTemp, "Cdata");
unsigned char pTemp[NUM_FEATURES*VCOP_SIMD_WIDTH*8] = {0x0};

#pragma DATA_ALIGN(Offset_Out, 32);
#pragma DATA_SECTION (Offset_Out, "Adata");
unsigned char Offset_Out[NUM_FEATURES*4*25] = {0x0};

#pragma DATA_ALIGN(lut_index_sad, 32);
#pragma DATA_SECTION (lut_index_sad, "Bdata");
unsigned char lut_index_sad[136] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
    27, 27, 27, 27, 27, 27, 27, 27
};

#pragma DATA_ALIGN(lut_index_thresh, 32);
#pragma DATA_SECTION (lut_index_thresh, "Bdata");
unsigned char lut_index_thresh[200] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    27, 27, 27, 27, 27, 27, 27, 27
};

#pragma DATA_ALIGN(Score_b, 32);
#pragma DATA_SECTION(Score_b, "Adata");
unsigned short Score_b[NUM_FEATURES] = {0x0};

#pragma DATA_ALIGN(Score_d, 32);
#pragma DATA_SECTION(Score_d, "Bdata");
unsigned short Score_d[NUM_FEATURES] = {0x0};

#pragma DATA_ALIGN(BScore, 32);
#pragma DATA_SECTION(BScore, "Adata");
unsigned char BScore[NUM_FEATURES*16] = {0x0};

#pragma DATA_ALIGN(DScore, 32);
#pragma DATA_SECTION(DScore, "Bdata");
unsigned char DScore[NUM_FEATURES*16] = {0x0};

#pragma DATA_ALIGN(Score, 32);
#pragma DATA_SECTION(Score, "Cdata");
unsigned short Score[NUM_FEATURES] = {0x0};

#pragma DATA_SECTION(sad_scores, "EXTDMEM");
unsigned short sad_scores[NUM_FEATURES] = {0x0};

#pragma DATA_SECTION(Ref_Out, "Eoutdata");
unsigned short Ref_Out[NUM_FEATURES] = {0x0};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sfast9_score_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->Thr            = THR;
    params->num_features   = NUM_FEATURES;
    params->pitch          = PITCH;
    params->numIter        = NUM_ITER;
    params->writeOutput    = 0;
    params->seedForRND     = 0;
    params->scoreMethod    = 1;
}

int writeOutputFile(unsigned short * output, sfast9_score_Config * params, char * filename)
{
    FILE * fp;
    int i;
    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(i=0;i<params->num_features;i++)
    {
           fprintf(fp, "%d ", output[i]);
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
            in_temp[i*stride + j] = (rand() & 0xFF);
#ifdef __DEBUG
            printf("%4d, ",  in_temp[i*stride + j]);
#endif
        }
#ifdef __DEBUG
          printf("\n");
#endif
      }
}

void test_fast9_score_c_reference()
{
    int k;

    char refFile[MAX_FILE_NAME_SIZE] = "../testvecs/reference/ref_out.txt";
    char inFile[MAX_FILE_NAME_SIZE] = "../testvecs/input/input_image.txt";

    memset(in_temp, 0, sizeof(in_temp));

    readInputFile(in_temp, 1, PITCH, NUM_FEATURES, PITCH, inFile, 0);

    // sad based score
    fast9_sad_score(&in_temp[0],
                    NUM_FEATURES,
                    &lut_index_sad[0],
                    THR,
                    &sad_scores[0]);

    readInputFile(Ref_Out, 1, NUM_FEATURES, 1, NUM_FEATURES, refFile, 2);

    for(k=0;k<NUM_FEATURES;k++)
    {
        if(sad_scores[k] != Ref_Out[k])
        {
            printf("sad score: %d, Reference score: %d \n", sad_scores[k], Ref_Out[k]);
        }
    }

}

void test_fast9_original_reference()
{
    int k;

    char inFile[MAX_FILE_NAME_SIZE] = "../testvecs/input/input_image1.txt";

    char thr = 30;

    memset(in_temp, 0, sizeof(in_temp));

    readInputFile(in_temp, 1, PITCH, NUM_FEATURES, PITCH, inFile, 0);

    // original fast9 score
    fast9_thresh_score(&in_temp[0],
                    NUM_FEATURES,
                    &lut_index_thresh[0],
                    thr,
                    &sad_scores[0]);

    for(k=0;k<NUM_FEATURES;k++)
    {
        printf("sad score: %d \n", sad_scores[k]);
    }

}

int test_fast9_score_vcop(sfast9_score_Config * params)
{
    unsigned int k;
    unsigned int iter;

    int fail = 0;

    profiler_init();

    printf("\nFast9 Score:\n");

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern genereation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU8(in_temp, params->num_features, params->pitch);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(in_temp, 1, PITCH, NUM_FEATURES, PITCH, params->inFileName, 0);
    }

    printf("Block size = %dx%d \n", params->pitch, params->num_features);

    for(iter = 0; iter < params->numIter; iter++)
    {
#if !(VCOP_HOST_EMULATION)
        if (params->scoreMethod)
        {
            profiler_start();

            // Call the Fast9_score_Sad kernel
            vcop_fast9_score_kernel
            (
                (unsigned int*)in_temp,
                (unsigned int*)pTemp_buf,
                (unsigned int*)pTemp,
                pTemp,
                params->num_features,
                params->Thr,
                lut_index_sad,
                Offset_Out,
                Score_b,
                Score_d,
                Score,
                (unsigned int *)__pblock_vcop_fast9_score_kernel);

            profiler_end();
        }    
        else
        {
            profiler_start();

            vcop_fast9_thresh_score
            (
                (unsigned int*)in_temp,
                (unsigned int*)pTemp_buf,
                (unsigned int*)pTemp,
                pTemp,
                params->num_features,
                params->Thr,
                lut_index_thresh,
                Offset_Out,
                BScore,
                DScore,
                Score_b,
                Score_d,
                Score,
                (unsigned int *)__pblock_vcop_fast9_thresh_score);

            profiler_end();    
        }    
#else
        if (params->scoreMethod)
        {
            vcop_fast9_score_kernel
            (
                (unsigned int*)in_temp,
                (unsigned int*)pTemp_buf,
                (unsigned int*)pTemp,
                pTemp,
                params->num_features,
                params->Thr,
                lut_index_sad,
                Offset_Out,
                Score_b,
                Score_d,
                Score,
                (unsigned int*)Score);
        }
        else
        {
            vcop_fast9_thresh_score
            (
                (unsigned int*)in_temp,
                (unsigned int*)pTemp_buf,
                (unsigned int*)pTemp,
                pTemp,
                params->num_features,
                params->Thr,
                lut_index_thresh,
                Offset_Out,
                BScore,
                DScore,
                Score_b,
                Score_d,
                Score,
                (unsigned int*)Score);
        }
        
#endif

#ifdef COMPARE_REFERENCE
    if (params->scoreMethod)
        // sad based score
        fast9_sad_score(&in_temp[0],
                        params->num_features,
                        &lut_index_sad[0],
                        params->Thr,
                        &sad_scores[0]);

    else
        fast9_thresh_score(&in_temp[0],
                        params->num_features,
                        &lut_index_thresh[0],
                        params->Thr,
                        &sad_scores[0]);


        for(k=0;k<params->num_features;k++)
            {
                if(sad_scores[k] != Score[k])
                {
                    printf("sad score: %d, Vcop score: %d \n", sad_scores[k], Score[k]);
                    fail++;
                }
            }
            printf(fail ? "FAIL\n" : "PASS\n");
    }
#endif

    profiler_deinit();

    if(params->writeOutput)
    {
        writeOutputFile(Score, params, params->outFileName);
    }

    return 0;

}


int main()
{
    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    sfast9_score_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    params = (sfast9_score_Config *)(&gConfig_fast9_score);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_fast9_score_vcop(params);
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
            status = readparamfile(configFileName, &gsTokenMap_fast9_score[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_fast9_score_vcop(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);


    return 0;
}


/*--------------------------------------------------------------------------*/
/* End of file: vcop_fast9_score_tb.c                                        */
/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

