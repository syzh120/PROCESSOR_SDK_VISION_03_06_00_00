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

/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_census_16bits_config.h"
#include "../inc/vcop_census_16bits_cn.h"
#include "../inc/init_census_16bits_params.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_census_16bits_kernel.k"    // kernel source
#else
#include "vcop_census_16bits_kernel.h"
#endif

// #define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define VCOP_SIMD_WIDTH4 (4*VCOP_SIMD_WIDTH)

#define ALIGN_8(a)   (((a) + 7) & ~(7))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_32(a)   (((a) + (32)-1) & ~(32-1))

/*Define MAXIMUM values */
#define MAX_WIN_WIDTH      (9)
#define MAX_WIN_HEIGHT     (9)
#define MAX_COMP_WIDTH     (32)  // multiple of 8
#define MAX_COMP_HEIGHT    (32)
#define MAX_BLK_WIDTH      (MAX_COMP_WIDTH+MAX_WIN_WIDTH-1)  //3 (left border) + 3 (right border) + Compute width
#define MAX_BLK_HEIGHT     (MAX_COMP_HEIGHT+MAX_WIN_HEIGHT-1)  // 3 (top border) + 3 (bottom border) + Compute height
#define MAX_IN_STRIDE      MAX_BLK_WIDTH 
#define MAX_OUT_STRIDE     (8*MAX_COMP_WIDTH)

#define NUM_ITER    (1)
#define COMPARE_REFERENCE (1)

#pragma DATA_SECTION (natC_out, "DST_MEM");
unsigned char natC_out[MAX_OUT_STRIDE*MAX_COMP_HEIGHT];

#pragma DATA_SECTION (IMAGE, "Adata");
unsigned short IMAGE[MAX_BLK_WIDTH*MAX_BLK_HEIGHT] ;

#pragma DATA_SECTION (ScratchBitmask, "Bdata");
unsigned char ScratchBitmask[((2*MAX_WIN_WIDTH*MAX_WIN_HEIGHT + 16)*((MAX_COMP_WIDTH+15)/16)*MAX_COMP_HEIGHT)] ; // (2*winWidth*winHeight + 16)*((computeWidth+15)/16)*computeHeight

#pragma DATA_SECTION (Offset, "Cdata");
uint16_t Offset[16];

#pragma DATA_SECTION (codeWordMask, "Cdata");
unsigned char codeWordMask[16];

#pragma DATA_SECTION (rowMask, "Cdata");
unsigned char rowMask[(MAX_COMP_HEIGHT+7)/8];

#pragma DATA_SECTION (Scratch, "Cdata");
#pragma DATA_ALIGN (Scratch, 32)
unsigned char Scratch[MAX_COMP_WIDTH*(ALIGN_32(MAX_COMP_HEIGHT)+4)*(MAX_WIN_WIDTH*MAX_WIN_HEIGHT+7)/8]; // inStride * (computeHeight + winHeight -1 ) + 15 bytes 

#pragma DATA_SECTION (Out, "Adata");
unsigned char Out[MAX_OUT_STRIDE*MAX_COMP_HEIGHT] ;

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
    {
        LinePtr++;
    }
    return(LinePtr);
}

void fillDefaultConfig(scensus_16bits_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->inStride        = MAX_BLK_WIDTH;
    params->computeWidth     = MAX_COMP_WIDTH;
    params->computeHeight    = MAX_COMP_HEIGHT;
    params->outStride= MAX_COMP_WIDTH;
    params->numIter        = NUM_ITER;
    params->writeOutput = 0;
    params->seedForRND    = 0;
}


int writeOutputFile(unsigned char * output, scensus_16bits_Config * params, char * filename)
{
    FILE * fp;
    int i,k, h;
    unsigned int j;
    uint8_t numBytesPerCensus;
    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    numBytesPerCensus=(_CENSUS_WIN_SIZE(params->winWidth, params->winHeight, params->winHorzStep, params->winVertStep) + 7) / 8;

    for(i=0;i<params->computeHeight;i++)
    {
        for(k=0;k<params->outStride;k+= numBytesPerCensus)
        {
            for (h=0;h<numBytesPerCensus; h++) {
                for (j=0;j<8;j++) {
                    fprintf(fp, "%d,", ((*output & (1<<j)) == (1<<j)));
                }
                output++;
            }
            fprintf(fp, " ");
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

static void CreateRandPatternU16(unsigned short *p, unsigned short h, unsigned short stride)
{
    int i, j;

#ifdef __DEBUG
    printf("Input Block:\n");
#endif

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < stride; j++)
        {
            IMAGE[i*stride + j] = (rand() & 0x00FF);
#ifdef __DEBUG
            printf("%4d, ",  IMAGE[i*stride + j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}

int test_census_16bits_vcop(scensus_16bits_Config * params)
{
    unsigned int iter;

    uint8_t numBytesPerCensus;
    uint16_t scratchStride;
    int outSize, ret=0, status;

    numBytesPerCensus= (_CENSUS_WIN_SIZE(params->winWidth, params->winHeight, params->winHorzStep, params->winVertStep) + 7) / 8;

    assert(params->outStride >= numBytesPerCensus*params->computeWidth);
    assert(MAX_IN_STRIDE*MAX_BLK_HEIGHT >= params->inStride*(params->computeHeight + params->winHeight - 1));
    assert(MAX_OUT_STRIDE*MAX_COMP_HEIGHT >= (params->outStride*params->computeHeight));

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern genereation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU16(IMAGE, params->computeHeight + params->winHeight - 1, params->inStride);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(IMAGE, 1, params->inStride, params->computeHeight + params->winHeight - 1, params->inStride, params->inFileName, 2);
    }

    status= init_census_16bits_params (
            params->winWidth, /* windWidth * winHeight msut be > 8 */
            params->winHeight,
            params->winHorzStep,
            params->winVertStep,
            params->computeWidth,
            params->computeHeight,
            params->outStride, /* in bytes, must multiple of 4 but not multiple of 32 bytes*/
            Offset, /* Point to an array of 8 bytes. Call init_census_16bits_params() to initialize content pointed by pOffset*/
            sizeof(Offset), /* Should be 8 */
            codeWordMask, /* Point to an array of (winWidth*winHeight+7)/8 bytes. Call init_census_16bits_params() to initialize content pointed by pCodeWordMask */
            sizeof(codeWordMask), /* Should be (winWidth*winHeight+7)/8 */
            rowMask,/* Point to an array of (computeHeight+7)/8 bytes. Call init_census_16bits_params() to initialize content pointed by pRowMask */
            sizeof(rowMask),
            &scratchStride);

    if (status < 0 ) {
        if (status== -1) {
            printf("Error: outStride is not >= numBytesPerCensus*computeWidth\n");
        }
        else if (status==-2) {
            printf ("Error: outStride is not multiple of 4\n");
        }
        else if (status== -3) {
            printf ("Error: outStride is multiple of 32, which must be avoided\n");
        }
        else if (status== -4) {
            printf ("Error: size of offset array not greater than 32\n");
        }
        else if (status== -5) {
            printf ("Error: size of codeWordMask array not greater than numBytesPerCensus\n");
        }
        else if (status== -6) {
            printf ("Error: size of rowMask array not greater than (computeHeight+7)/8\n");
        }
        else if (status== -7) {
            printf ("Error: bank conflict in computed offset (this error should not happen)\n");
        }
        exit(-1);
    }

    printf("Compute block size = %dx%d, winHorzStep= %d, winVertStep= %d\n", params->computeWidth, params->computeHeight, params->winHorzStep, params->winVertStep);

    for(iter = 0; iter < params->numIter; iter++)
    {
        outSize = params->outStride * params->computeHeight;
        memset(ScratchBitmask, 0, sizeof(ScratchBitmask));
        memset(Scratch, 0, sizeof(Scratch));
        memset(natC_out, 0, sizeof(natC_out));
        memset(Out, 0, sizeof(Out));

        profiler_start();

        vcop_census_16bits
        (
                &IMAGE[0],
                Out,         //8 bit output
                ScratchBitmask,
                (uint16_t*)Scratch,
                (uint8_t*)Scratch,
                Offset,
                codeWordMask,
                rowMask,
                params->winWidth, 
                params->winHeight,
                params->winHorzStep,
                params->winVertStep,
                params->computeWidth,
                params->computeHeight,
                params->inStride,
                params->outStride,
                scratchStride
        );

        profiler_end();

#ifdef COMPARE_REFERENCE

        vcop_census_16bits_cn(
                &IMAGE[0],
                (uint8_t*)natC_out,
                params->winWidth, 
                params->winHeight,
                params->winHorzStep,
                params->winVertStep,
                params->computeWidth,
                params->computeHeight,
                params->inStride,
                params->outStride
        );

        ret = memcmp(Out,natC_out, outSize);

        if(ret !=0)
        {
            printf("Natural C & Kernel DIDN'T MATCH !!!!!!!!!!\n\n");
            exit(0);
        }
        else
        {
            printf("Natural C & Kernel MATCHED\n\n");
        }
#endif

    }

    profiler_deinit();

    if(params->writeOutput)
    {
        //writeOutputFile(Out, params, params->outFileName);
        writeOutputFile((uint8_t*)natC_out, params, params->outFileName);
    }

    return 0;
}

int main()
{
    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    scensus_16bits_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    printf("\nvcop_census_16bits test\n\n");

    params = (scensus_16bits_Config *)(&gConfig_census_16bits);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_census_16bits_vcop(params);
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
            status = readparamfile(configFileName, &gsTokenMap_census_16bits[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_census_16bits_vcop(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);
    exit(0);

}


/*--------------------------------------------------------------------------*/
/* End of file: vcop_census_16bits_tb.c                                        */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

