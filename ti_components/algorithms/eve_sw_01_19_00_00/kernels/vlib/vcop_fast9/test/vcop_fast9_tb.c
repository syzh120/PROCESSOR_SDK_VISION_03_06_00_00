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

/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_fast9_config.h"
#include "../inc/vcop_fast9_cn.h"


#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_fast9_kernel.k"    // kernel source
#else
  #include "vcop_fast9_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define BLK_WIDTH      (70)  //3 (left border) + 3 (right border) + Compute width
#define BLK_HEIGHT     (14)  // 3 (top border) + 3 (bottom border) + Compute height
#define COMP_WIDTH     (BLK_WIDTH-6)  // multiple of 8
#define COMP_HEIGHT    (BLK_HEIGHT-6)
#define THR            (32)  // Threshold for detecting key points
#define NUM_ITER    (1)
#define COMPARE_REFERENCE (1)

#pragma DATA_SECTION (IMAGE, "Adata");
unsigned char IMAGE[BLK_WIDTH*BLK_HEIGHT] ;

#pragma DATA_SECTION (output0, "Bdata");
unsigned char output0[2*COMP_WIDTH*COMP_HEIGHT] ;

#pragma DATA_SECTION (output1, "Cdata");
unsigned char output1[2*COMP_WIDTH*COMP_HEIGHT] ;

#pragma DATA_SECTION (indexG, "Cdata");
unsigned short indexG[2*COMP_WIDTH*COMP_HEIGHT] ;

#pragma DATA_SECTION (Out, "Adata");
unsigned char Out[COMP_WIDTH*COMP_HEIGHT/8] ;


#pragma DATA_SECTION(Ref_Out, "Eoutdata");
unsigned int Ref_Out[COMP_WIDTH*COMP_HEIGHT/8] = {0x0};

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '\t'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sfast9_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->Thr         = THR;
    params->pitch        = BLK_WIDTH;
    params->blkHeight    = BLK_HEIGHT;
    params->comp_width     = COMP_WIDTH;
    params->comp_height    = COMP_HEIGHT;
    params->numIter        = NUM_ITER;
    params->writeOutput = 0;
    params->seedForRND    = 0;
}


int writeOutputFile(unsigned char * output, sfast9_Config * params, char * filename)
{
    FILE * fp;
    int i,k;
    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(i=0;i<params->comp_height;i++)
    {
        for(k=0;k<params->comp_width/8;k++)
        {
           fprintf(fp, "%d ", *output);
           output++;
        }
        fprintf(fp, "\n");
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

void test_fast9_c_reference()
{
    int outSize, ret=0;
    unsigned char natC_out[COMP_WIDTH*COMP_HEIGHT/8];

    char refFile[MAX_FILE_NAME_SIZE] = "../testvecs/reference/ref_out.txt";
    char inFile[MAX_FILE_NAME_SIZE] = "../testvecs/input/input_image.txt";

    outSize = 8*14 ;

    readInputFile(IMAGE, 1, 70, 14, 70, inFile, 0);

    vcop_fast9_cn(&IMAGE[0],
            natC_out,
            THR,
            70,
            64,
            8);

    readInputFile(Ref_Out, 1, 8, 8, 8, refFile, 0);

    ret = memcmp(Ref_Out,natC_out, outSize);
    if(ret !=0)
    {
      printf("Natural C implementation FAILED\n");
    }
    else
    {
      printf("Natural C implementation PASSED\n");
    }
    return ;
}


int test_fast9_vcop(sfast9_Config * params)
{
    unsigned int iter;
    unsigned char natC_out[COMP_WIDTH*COMP_HEIGHT/8];
    int outSize, ret=0;

    profiler_init();

    printf("\nvcop_fast9:\n");

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern genereation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU8(IMAGE, params->blkHeight, params->pitch);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(IMAGE, 1, params->pitch, params->comp_height+6, params->pitch, params->inFileName, 0);
    }

    printf("Block size = %dx%d \n", params->pitch, params->blkHeight);

    for(iter = 0; iter < params->numIter; iter++)
    {
        outSize = params->comp_width * params->comp_height/8 ;
        profiler_start();

        vcop_fast9
        (
                &IMAGE[0],
                output0,     //8 bit scratch
                output1,     //8 bit scratch
                indexG,      //16 bit scratch
                Out,         //8 bit output
                params->Thr,           // thereshold
                params->pitch,       //block width
                params->comp_width+6,  //in_w
                params->comp_height+6  //in_h
        );

        profiler_end();

#ifdef COMPARE_REFERENCE

        vcop_fast9_cn(&IMAGE[0],
                natC_out,
                params->Thr,    // thereshold
                params->pitch,  //block width
                params->pitch,  //in_w
                params->comp_height+6  //in_h
                );


        ret = memcmp(Out,natC_out, outSize);

         if(ret !=0)
         {
           printf("Natural C & Kernel DIDN'T MATCH\n");
         }
         else
         {
             printf("Natural C & Kernel MATCHED\n");
         }
#endif

    }

    profiler_deinit();

    if(params->writeOutput)
    {
        writeOutputFile(Out, params, params->outFileName);
    }

    return 0;
}

int main()
{
    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    sfast9_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    params = (sfast9_Config *)(&gConfig_fast9);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_fast9_vcop(params);
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
            status = readparamfile(configFileName, &gsTokenMap_fast9[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_fast9_vcop(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);
    return (0);

}


/*--------------------------------------------------------------------------*/
/* End of file: vcop_fast9_tb.c                                        */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

