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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_disparity_sad16_row_config.h"
#include "../inc/vcop_disparity_sad16_row_cn.h"
#include "../inc/init_disparity_sad16_row_params.h"

//#define _ONLY_NATC

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_disparity_sad16_row_kernel.k"    // kernel source
#else
#include "vcop_disparity_sad16_row_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define VCOP_SIMD_WIDTH4 (4*VCOP_SIMD_WIDTH)

#define ALIGN_8(a)   (((a) + 7) & ~(7))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))

/*Define MAXIMUM values */
#define MAX_WIN_WIDTH      (15)
#define MAX_WIN_HEIGHT     (15)
#define EVE_MAX_NUM_DISPARITIES (64)
#define EVE_MAX_WIDTH       (64)
#define MAX_NUM_DISPARITIES (64)
#define MAX_NUM_DISPARITIES_OUT (32)
#define MAX_WIDTH          (64)
#define MAX_NUM_ROWS       (2)
#define MAX_LEFT_STRIDE    (MAX_WIDTH + MAX_WIN_WIDTH - 1)
#define MAX_RIGHT_STRIDE   (MAX_WIDTH + MAX_NUM_DISPARITIES - 1 + MAX_WIN_WIDTH - 1)

#define NUM_ITER    (1)
#define COMPARE_REFERENCE (1)

#pragma DATA_SECTION (natC_dispOut, "DST_MEM");
unsigned char natC_dispOut[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_minCostOutput, "DST_MEM");
unsigned int natC_minCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_allCostOutput, "DST_MEM");
unsigned int natC_allCostOutput[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH];
#pragma DATA_SECTION (allCostOutput, "DST_MEM");
unsigned int allCostOutput[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH];

#pragma DATA_SECTION (IMAGE_LEFT, "Adata");
unsigned short IMAGE_LEFT[(MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_LEFT_STRIDE] ;
#pragma DATA_SECTION (IMAGE_RIGHT, "Bdata");
unsigned short IMAGE_RIGHT[(MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_RIGHT_STRIDE] ;

#pragma DATA_SECTION (dispOut, "Adata");
unsigned char dispOut[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (minCostOutput, "Adata");
unsigned int minCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (partialAllCostOutput, "Cdata");
#pragma DATA_ALIGN (partialAllCostOutput, 32);
unsigned int partialAllCostOutput[MAX_NUM_DISPARITIES_OUT*(MAX_WIDTH+4)];

#pragma DATA_SECTION (offset, "Cdata");
uint16_t offset[16];

#pragma DATA_SECTION (collateMask, "Cdata");
uint8_t collateMask[1];

#pragma DATA_SECTION (scratch0, "Bdata");
#pragma DATA_ALIGN (scratch0, 32);
int32_t scratch0[((MAX_NUM_DISPARITIES_OUT+8+1)*EVE_MAX_WIDTH)];

/* scratch1 is not used in 16-bits version, only in 8-bits version so lines below are commented out */
/*
#pragma DATA_SECTION (scratch1, "Cdata");
#pragma DATA_ALIGN (scratch1, 32);
int32_t scratch1[(MAX_NUM_DISPARITIES_OUT*EVE_MAX_WIDTH)/2];
 */

#pragma DATA_SECTION (scratch1, "Adata");
int32_t scratch1[(MAX_NUM_DISPARITIES_OUT+8+1)*MAX_WIDTH];

#pragma DATA_SECTION (carryOver, "Cdata");
uint32_t carryOver[MAX_NUM_DISPARITIES_OUT];

uint32_t carryOverBackup[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT];

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
    {
        LinePtr++;
    }
    return(LinePtr);
}

void fillDefaultConfig(sdisparity_sad16_row_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->leftStride = MAX_LEFT_STRIDE;
    params->rightStride = MAX_RIGHT_STRIDE;
    params->width = MAX_WIDTH;
    params->numRows = MAX_NUM_ROWS;
    params->winWidth= MAX_WIN_WIDTH;
    params->winHeight= MAX_WIN_HEIGHT;
    params->numDisparities= MAX_NUM_DISPARITIES;
    params->disparityStep= 1;
    params->numIter        = NUM_ITER;
    params->writeOutput = 0;
    params->seedForRND    = 0;
}


int writeOutputFile(unsigned char *dispOut, unsigned int *minCostOutput, unsigned int *allCostOutput, sdisparity_sad16_row_Config * params, char * filename)
{
    FILE * fp;
    unsigned int i, j, k, actualNumDisparities;

    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for (k=0; k < params->numRows; k++) {

        for(i=0;i<params->width;i++)
        {

            fprintf(fp, "%3d,", dispOut[k*params->width + i]);
        }

        fprintf(fp, "\n\n");

        for(i=0;i<params->width;i++)
        {

            fprintf(fp, "%3d,", minCostOutput[k*params->width + i]);
        }

        fprintf(fp, "\n\n");

        actualNumDisparities= params->numDisparities/params->disparityStep;

        for(i=0;i<actualNumDisparities;i++)
        {
            for (j=0;j<params->width;j++) {
                fprintf(fp, "%3d,", allCostOutput[k*params->width*actualNumDisparities + i*params->width + j]);
            }
            fprintf(fp, "\n");
        }

        fprintf(fp, "\n ------------------------------------------------------------------------------------------ \n");
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
            p[i*stride + j] = (rand() & 0x00FF);
#ifdef __DEBUG
            printf("%4d, ",  IMAGE[i*stride + j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}

int test_disparity_sad16_row_vcop(sdisparity_sad16_row_Config * params)
{
    unsigned int iter, r, d, i, segm;
    uint16_t segmWidth;
    uint16_t scratchBufferSize, scratchBufferStride, partialAllCostOutputStride, partialAllCostOutputSize;

    int ret=0, status;

    assert((MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_LEFT_STRIDE >= params->leftStride*(params->numRows + params->winHeight - 1));
    assert((MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_RIGHT_STRIDE >= params->rightStride*(params->numRows + params->winHeight - 1));
    assert(MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH >= (params->width*params->numRows*(params->numDisparities/params->disparityStep)));

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern genereation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU16(IMAGE_LEFT, params->numRows + params->winHeight - 1, params->leftStride);
        CreateRandPatternU16(IMAGE_RIGHT, params->numRows + params->winHeight - 1, params->rightStride);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(IMAGE_LEFT, 1, params->leftStride, params->numRows + params->winHeight - 1, params->leftStride, params->inLeftFileName, 2);
        readInputFile(IMAGE_RIGHT, 1, params->rightStride, params->numRows + params->winHeight - 1, params->rightStride, params->inRightFileName, 2);
    }

    segmWidth= params->width/params->numRowSegments;

    printf("Num disparities: %d, Compute row width = %d, num rows= %d, num segm per row= %d\n", params->numDisparities/params->disparityStep, segmWidth, params->numRows, params->numRowSegments);

    status= init_disparity_sad16_row_params
            (
                    offset,
                    sizeof(offset),
                    collateMask,
                    &scratchBufferSize,
                    &scratchBufferStride,
                    &partialAllCostOutputStride,
                    &partialAllCostOutputSize,
                    segmWidth,
                    params->numDisparities,
                    params->disparityStep
            );

    if (status < 0 ) {
        if (status== -1) {
            printf ("Error: width not greater than 32\n");
        }
        else if (status== -2) {
            printf ("Error: width not multiple of 16\n");
        }
        else if (status== -4) {
            printf ("Error: size of offset array not greater than 32\n");
        }
        else if (status== -7) {
            printf ("Error: bank conflict in computed offset (this error should not happen)\n");
        }
        else if (status== -8) {
            printf ("Error: bank conflict in computed offset (this error should not happen)\n");
        }
        exit(-1);
    }

    assert(scratchBufferSize <= sizeof(scratch0));
    assert(partialAllCostOutputSize <= sizeof(partialAllCostOutput));

    for(iter = 0; iter < params->numIter; iter++)
    {
        memset(natC_dispOut, 0, sizeof(natC_dispOut));
        memset(dispOut, 0, sizeof(dispOut));
        memset(natC_minCostOutput, 0, sizeof(natC_minCostOutput));
        memset(minCostOutput, 0, sizeof(minCostOutput));
        memset(allCostOutput, 0, sizeof(allCostOutput));
        memset(natC_allCostOutput, 0, sizeof(natC_allCostOutput));
        memset(partialAllCostOutput, 0, sizeof(partialAllCostOutput));
        memset(scratch0, 0, sizeof(scratch0));
        //memset(scratch1, 0, sizeof(scratch1));
        memset(carryOver, 0, sizeof(carryOver));

        for (segm=0; segm < params->numRowSegments; segm++) {
            r= 0;
#ifdef _ONLY_NATC        
            vcop_disparity_sad16_first_row_cn
            (
                    IMAGE_LEFT + r*params->leftStride + segm*segmWidth,
                    IMAGE_RIGHT + r*params->rightStride + segm*segmWidth,
                    params->leftStride,
                    params->rightStride,
                    params->winWidth,
                    params->winHeight,
                    dispOut + r*params->width + segm*segmWidth,
                    minCostOutput + r*params->width + segm*segmWidth,
                    allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width + segm*segmWidth,
                    segmWidth,
                    params->width,
                    params->numDisparities,
                    params->disparityStep
            );
#else                
            if (segm==0) {
                vcop_disparity_sad16_first_row_firstCall
                (
                        IMAGE_LEFT + r*params->leftStride + segm*segmWidth,
                        IMAGE_RIGHT + r*params->rightStride + segm*segmWidth,
                        params->leftStride,
                        params->rightStride,
                        params->winWidth,
                        params->winHeight,
                        dispOut + r*params->width + segm*segmWidth,
                        minCostOutput + r*params->width + segm*segmWidth,
                        partialAllCostOutput,
                        partialAllCostOutputStride,
                        segmWidth,
                        params->numDisparities,
                        params->disparityStep,
                        collateMask,
                        offset,
                        scratch0,
                        carryOver,
                        scratchBufferStride
                );
            }
            else {
                /* Restore carryOver */
                for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                    carryOver[d]= carryOverBackup[r*(params->numDisparities/params->disparityStep) + d];
                }

                vcop_disparity_sad16_first_row
                (
                        IMAGE_LEFT + r*params->leftStride + segm*segmWidth,
                        IMAGE_RIGHT + r*params->rightStride + segm*segmWidth,
                        params->leftStride,
                        params->rightStride,
                        params->winWidth,
                        params->winHeight,
                        dispOut + r*params->width + segm*segmWidth,
                        minCostOutput + r*params->width + segm*segmWidth,
                        partialAllCostOutput,
                        partialAllCostOutputStride,
                        segmWidth,
                        params->numDisparities,
                        params->disparityStep,
                        collateMask,
                        offset,
                        scratch0,
                        carryOver,
                        scratchBufferStride
                );
            }

            /* Save carryOver */
            for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                carryOverBackup[r*(params->numDisparities/params->disparityStep) + d]= carryOver[d];
            }

            /* For testing purpose, copy from partialAllCostOutput (used in VCOP version only) to allCostOutput */
            for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                for(i=0;i<segmWidth;i++) {
                    allCostOutput[d*params->width + segm*segmWidth +i]= partialAllCostOutput[d*(partialAllCostOutputStride/4)+i];
                }
            }
#endif
            if (params->numRowSegments== 1)
                profiler_start();

            for (r=1;r<params->numRows;r++) {

#ifdef _ONLY_NATC

                vcop_disparity_sad16_nth_row_cn
                (
                        IMAGE_LEFT + r*params->leftStride + segm*segmWidth,
                        IMAGE_RIGHT + r*params->rightStride + segm*segmWidth,
                        params->leftStride,
                        params->rightStride,
                        params->winWidth,
                        params->winHeight,
                        dispOut + r*params->width + segm*segmWidth,
                        minCostOutput + r*params->width + segm*segmWidth,
                        allCostOutput + (r-1)*(params->numDisparities/params->disparityStep)*params->width + segm*segmWidth,
                        allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width + segm*segmWidth,
                        segmWidth,
                        params->width,
                        params->numDisparities,
                        params->disparityStep
                );
#else

                if (params->numRowSegments!= 1)
                    profiler_start();

                if (segm== 0) {
                    vcop_disparity_sad16_nth_row_firstCall
                    (
                            IMAGE_LEFT + r*params->leftStride,
                            IMAGE_RIGHT + r*params->rightStride,
                            params->leftStride,
                            params->rightStride,
                            params->winWidth,
                            params->winHeight,
                            dispOut + r*params->width,
                            minCostOutput + r*params->width,
                            partialAllCostOutput,
                            partialAllCostOutputStride,
                            segmWidth,
                            params->numDisparities,
                            params->disparityStep,
                            collateMask,
                            offset,
                            scratch0,
                            scratch1,
                            carryOver,
                            scratchBufferStride
                    );
                }
                else {
                    /* Restore carryOver */
                    for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                        carryOver[d]= carryOverBackup[r*(params->numDisparities/params->disparityStep) + d];
                    }

                    vcop_disparity_sad16_nth_row
                    (
                            IMAGE_LEFT + r*params->leftStride + segm*segmWidth,
                            IMAGE_RIGHT + r*params->rightStride + segm*segmWidth,
                            params->leftStride,
                            params->rightStride,
                            params->winWidth,
                            params->winHeight,
                            dispOut + r*params->width + segm*segmWidth,
                            minCostOutput + r*params->width + segm*segmWidth,
                            partialAllCostOutput,
                            partialAllCostOutputStride,
                            segmWidth,
                            params->numDisparities,
                            params->disparityStep,
                            collateMask,
                            offset,
                            scratch0,
                            scratch1,
                            carryOver,
                            scratchBufferStride
                    );
                }
                if (params->numRowSegments!= 1)
                    profiler_end();

                /* Save carryOver */
                for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                    carryOverBackup[r*(params->numDisparities/params->disparityStep) + d]= carryOver[d];
                }

                /* For testing purpose, copy from partialAllCostOutput (used in VCOP version only) to allCostOutput */
                for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                    for(i=0;i<segmWidth;i++) {
                        allCostOutput[(r*(params->numDisparities/params->disparityStep) + d)*params->width + segm*segmWidth + i]= partialAllCostOutput[d*(partialAllCostOutputStride/4)+i];
                    }
                }
#endif
            }

        }
        if (params->numRowSegments== 1)
            profiler_end();

#ifdef COMPARE_REFERENCE

        for (r=0;r<params->numRows;r++) {
            vcop_disparity_sad16_row_ref_cn
            (
                    IMAGE_LEFT + r*params->leftStride,
                    IMAGE_RIGHT + r*params->rightStride,
                    params->leftStride,
                    params->rightStride,
                    params->winWidth,
                    params->winHeight,
                    natC_dispOut + r*params->width,
                    natC_minCostOutput + r*params->width,
                    natC_allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width,
                    params->width,
                    params->numDisparities,
                    params->disparityStep
            );
        }

        ret = memcmp(dispOut, natC_dispOut, sizeof(dispOut));
        ret |= memcmp(minCostOutput, natC_minCostOutput, sizeof(minCostOutput));
        ret |= memcmp(allCostOutput, natC_allCostOutput, sizeof(allCostOutput));

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
        writeOutputFile(natC_dispOut, natC_minCostOutput, natC_allCostOutput, params, params->outFileName);
    }

    return 0;
}

int main()
{
    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    sdisparity_sad16_row_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    printf("\nvcop_disparity_sad16_row test\n\n");

    params = (sdisparity_sad16_row_Config *)(&gConfig_disparity_sad16_row);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_disparity_sad16_row_vcop(params);
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
            status = readparamfile(configFileName, &gsTokenMap_disparity_sad16_row[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_disparity_sad16_row_vcop(params);
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
/* End of file: vcop_census_8bits_tb.c                                        */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

