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

/*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vcop.h"
#include <math.h>
#include "eve_profile.h"
#include "vcop_ncc_config.h"
#include "vcop_ncc_tb_utils.h"
#include "../inc/vcop_ncc.h"
#include "../inc/vcop_ncc_cn.h"
#include "init_slidingSum_params.h"

extern uint8_t input[];
extern uint8_t template[];
extern float output[];

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_ncc_kernel.k"    // kernel source
#else
#include "vcop_ncc_kernel.h"
#endif

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define VCOP_SIMD_WIDTH4 (4*VCOP_SIMD_WIDTH)

#define ALIGN_8(a)   (((a) + 7) & ~(7))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_32(a)   (((a) + (32)-1) & ~(32-1))

#define NUM_ITER    (1)
#define COMPARE_REFERENCE (1)

#pragma DATA_SECTION (INPUT_IMG, "DDR_MEM");
uint8_t INPUT_IMG[MAX_INPUT_IMG_STRIDE*MAX_INPUT_IMG_HEIGHT2];

#pragma DATA_SECTION (TEMPLATE_IMG, "DDR_MEM");
int16_t TEMPLATE_IMG[ALIGN_SIMD2(MAX_TEMPLATE_BLK_WIDTH)*MAX_TEMPLATE_BLK_HEIGHT];

#pragma DATA_SECTION (SCRATCH, "DDR_MEM");
int32_t SCRATCH[MAX_INPUT_IMG_STRIDE*MAX_INPUT_IMG_HEIGHT2];

#pragma DATA_SECTION (SUM, "DDR_MEM");
int32_t SUM[MAX_INPUT_IMG_STRIDE*MAX_INPUT_IMG_HEIGHT2];

#pragma DATA_SECTION (OUTPUT_NUM_CC, "DDR_MEM");
int32_t OUTPUT_NUM_CC[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (NATC_OUTPUT_NUM_CC, "DDR_MEM");
int32_t NATC_OUTPUT_NUM_CC[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (REF_OUTPUT_NUM_CC, "DDR_MEM");
int32_t REF_OUTPUT_NUM_CC[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (OUTPUT_DENOM_VAR, "DDR_MEM");
uint32_t OUTPUT_DENOM_VAR[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (NATC_OUTPUT_DENOM_VAR, "DDR_MEM");
uint32_t NATC_OUTPUT_DENOM_VAR[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (REF_OUTPUT_DENOM_VAR, "DDR_MEM");
uint32_t REF_OUTPUT_DENOM_VAR[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (OUTPUT_NCC, "DDR_MEM");
float OUTPUT_NCC[MAX_NUM_HORZ_BLOCKS*MAX_COMP_BLK_WIDTH*MAX_NUM_VERT_BLOCKS*MAX_COMP_BLK_HEIGHT];

#pragma DATA_SECTION (IBUFL_LAYOUT, "Adata");
IBUFL_MemLayout IBUFL_LAYOUT;

#pragma DATA_SECTION (IBUFH_LAYOUT, "Bdata");
IBUFH_MemLayout IBUFH_LAYOUT;

#pragma DATA_SECTION (WBUF_LAYOUT, "Cdata");
WBUF_MemLayout WBUF_LAYOUT;

void nccInFrame(NccFunc nccFunc, uint8_t *pFrame, int16_t *pTemplate, int32_t *pOutput_num_cc, uint32_t *pOutput_denom_var, sncc_Config * params);

void wrapper_for_vcop_ncc(
        uint8_t     orgImg[],           /*original input image data pointer */
        int32_t     orgImgWidth,        /*original input image width*/
        int32_t     orgImgHeight,       /*original input image height*/
        int32_t     orgImgPitch,        /*original input image pitch*/
        int16_t     tempImg[],          /*template image pointer*/
        int32_t     tempImgWidth,       /*template image width*/
        int32_t     tempImgHeight,      /*template image height*/
        int32_t     tempImgPitch,       /*template image pitch*/
        uint8_t     sizeQshift,         /*number of fractional bits used to compute the inverse of the size of the template*/
        uint8_t     qShift,             /*number of fractional bits */
        uint8_t     xDirJump,           /*Jump in x direction while searching*/
        uint8_t     yDirJump,           /*Jump in y direction while searching*/
        int32_t     outNumCC[],         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        uint32_t    outDenomVar[],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        int32_t     outPitch,           /*Out Score buffer pitch*/
        int32_t     scratch[],
        int32_t     scratchStride,
        uint32_t    sum[],
        int32_t     sumStride);

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
    {
        LinePtr++;
    }
    return(LinePtr);
}

void fillDefaultConfig(sncc_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");\
    params->qShift= 8;
    params->sizeQshift= 8;
    params->computeBlkWidth     = MAX_COMP_BLK_WIDTH;
    params->computeBlkHeight    = MAX_COMP_BLK_HEIGHT;
    params->templateBlkWidth= MAX_TEMPLATE_BLK_WIDTH;
    params->templateBlkHeight= MAX_TEMPLATE_BLK_HEIGHT;
    params->inputImgWidth= MAX_INPUT_IMG_WIDTH;
    params->inputImgHeight= MAX_INPUT_IMG_HEIGHT;
    params->inputImgStride= MAX_INPUT_IMG_STRIDE;
    params->numIter        = NUM_ITER;
    params->writeOutput = 0;
    params->seedForRND    = 0;
}


int writeOutputFile(float *outputNCC, uint32_t size, char * filename)
{
    FILE * fp;

    fp = fopen(filename, "wb");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    fwrite(outputNCC, sizeof(float), size, fp);

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
            p[i*stride + j] = rand();
#ifdef __DEBUG
            printf("%4d, ",  p[i*stride + j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}

void copyInputImg(uint8_t *dst, uint8_t *src, uint32_t width, uint32_t height, uint32_t stride, uint32_t height2) {
    int32_t w, h;
    memset(dst, 0, stride*height2);
    for (h= 0; h < height; h++) {
        for (w= 0; w < width; w++) {
            dst[w + h*stride]= src[w + h*width];
        }
    }
}

uint32_t copyTemplate(int16_t *dst, uint8_t *src, uint32_t width, uint32_t height, uint32_t stride, uint8_t sizeQshift, uint8_t qShift) {

    int32_t tAver, sum= 0;
    uint32_t tVar, w, h;
    int32_t t_p;
    uint16_t qValDiffHalf, qShiftDiff, qValHalf;

    qShiftDiff= sizeQshift - qShift;
    qValDiffHalf= 1<<(qShiftDiff -1 );
    qValHalf= 1<<(qShift - 1);

    memset(dst, 0, stride * height);

    for (h= 0; h < height; h++) {
        for (w= 0; w < width; w++) {
            sum += src[w + h*width];
        }
    }

    tAver= ((sum<<sizeQshift) + (width*height)/2)/(width*height);
    tVar= 0;

    for (h= 0; h < height; h++) {
        for (w= 0; w < width; w++) {
            t_p= (src[w + h*width]<<qShift) - ((tAver + qValDiffHalf)>>qShiftDiff);
            dst[w + h*stride]= t_p;
            tVar+= ((unsigned int)t_p*t_p + qValHalf) >> qShift;
        }
    }

    return tVar;
}

float shiftFloat(float a, uint8_t qShift) {

    float result;
    float qVal= (float)(1<<qShift);
    float qHalfVal= (float)(1<<(qShift-1));

    result= (a + qHalfVal)/qVal;

    return result;
}

int test_ncc_vcop(sncc_Config * params)
{
    unsigned int iter;
    int i, j;
    int ret=0;
    int roiBlkWidth, roiBlkHeight, numHorzBlocks, numVertBlocks;
    uint32_t templateVar;
    float maxErr, err;
    int32_t maxErr_i= 0, maxi= 0;
    float max= 0.0;
    uint32_t size;
    uint32_t outStride;

    roiBlkWidth= params->computeBlkWidth + params->templateBlkWidth - 1;
    roiBlkHeight= params->computeBlkHeight + params->templateBlkHeight - 1;

    assert(MAX_INPUT_BLK_WIDTH*MAX_INPUT_BLK_HEIGHT >= (roiBlkWidth*roiBlkHeight));
    assert(MAX_INPUT_IMG_STRIDE*MAX_INPUT_IMG_HEIGHT >= (params->inputImgStride*params->inputImgHeight));
    assert(MAX_TEMPLATE_BLK_WIDTH*MAX_TEMPLATE_BLK_HEIGHT >= (params->templateBlkWidth*params->templateBlkHeight));

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern genereation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU8(INPUT_IMG, params->inputImgHeight, params->inputImgStride);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(INPUT_IMG, 4, params->inputImgStride, params->inputImgHeight, params->inputImgStride, params->inFileName, 0);
        readInputFile(TEMPLATE_IMG, 4, params->templateBlkWidth, params->templateBlkHeight, params->templateBlkWidth, params->templateFileName, 0);
    }
    else if (strcmp(params->inputSrc, "STATIC") == 0)
    {
        copyInputImg(INPUT_IMG, input, params->inputImgWidth, params->inputImgHeight, params->inputImgStride, params->inputImgHeight + params->templateBlkHeight - 1);
        templateVar= copyTemplate(TEMPLATE_IMG, template, params->templateBlkWidth, params->templateBlkHeight, params->templateBlkWidth, params->sizeQshift, params->qShift);
    }

    printf("Compute block size = %dx%d  template size= %dx%d Number of fractional bits used for computation: %d\n", params->computeBlkWidth, params->computeBlkHeight, params->templateBlkWidth, params->templateBlkHeight, params->qShift);

    numHorzBlocks=  (params->inputImgWidth + params->computeBlkWidth - 1 ) / params->computeBlkWidth;
    numVertBlocks=  (params->inputImgHeight + params->computeBlkHeight - 1 ) / params->computeBlkHeight;

    printf("Original frame dimensions: %d x %d pixels, Effective processing frame dimensions: %d x %d pixels\n", params->inputImgWidth , params->inputImgHeight, numHorzBlocks * params->computeBlkWidth, numVertBlocks * params->computeBlkHeight);
    for(iter = 0; iter < params->numIter; iter++)
    {

        profiler_start();

        nccInFrame((NccFunc)wrapper_for_vcop_ncc, INPUT_IMG, TEMPLATE_IMG, OUTPUT_NUM_CC, OUTPUT_DENOM_VAR, params);
        //nccInFrame((NccFunc)vcop_ncc_opt_cn, INPUT_IMG, TEMPLATE_IMG, OUTPUT_NUM_CC, OUTPUT_DENOM_VAR, params);

        profiler_end();

#ifdef COMPARE_REFERENCE
#if 1
        vcop_ncc_cn(
                INPUT_IMG,           /*original input image data pointer */
                params->inputImgWidth + params->templateBlkWidth - 1,        /*original input image width*/
                params->inputImgHeight + params->templateBlkHeight - 1,       /*original input image height*/
                params->inputImgStride,        /*original input image pitch*/
                TEMPLATE_IMG,          /*template image pointer*/
                params->templateBlkWidth,       /*template image width*/
                params->templateBlkHeight,      /*template image height*/
                params->templateBlkWidth,       /*template image pitch*/
                params->sizeQshift,
                params->qShift,
                params->xDirJump,           /*Jump in x direction while searching*/
                params->yDirJump,           /*Jump in y direction while searching*/
                NATC_OUTPUT_NUM_CC,         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                NATC_OUTPUT_DENOM_VAR,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                params->inputImgWidth,           /*Out Score buffer pitch*/
                NULL,
                0,
                NULL,
                0
        );
#else
        vcop_ncc_opt_cn(
                INPUT_IMG,           /*original input image data pointer */
                params->inputImgWidth + params->templateBlkWidth - 1,        /*original input image width*/
                params->inputImgHeight + params->templateBlkHeight - 1,       /*original input image height*/
                params->inputImgStride,        /*original input image pitch*/
                TEMPLATE_IMG,          /*template image pointer*/
                params->templateBlkWidth,       /*template image width*/
                params->templateBlkHeight,      /*template image height*/
                params->templateBlkWidth,       /*template image pitch*/
                params->sizeQshift,
                params->qShift,
                params->xDirJump,           /*Jump in x direction while searching*/
                params->yDirJump,           /*Jump in y direction while searching*/
                NATC_OUTPUT_NUM_CC,         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                NATC_OUTPUT_DENOM_VAR,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                params->inputImgWidth,           /*Out Score buffer pitch*/
                SCRATCH,
                0,
                SUM,
                0
        );
#endif
#if 1

        printf("Performance estimates: %2.1f cycles/pixel\n", params->cyclesPerPixel);

        ret= 0;
        outStride= numHorzBlocks*params->computeBlkWidth;
        for (j= 0; j < params->inputImgHeight; j++ ) {
            for( i = 0; i < params->inputImgWidth; i++ ) {
                if(NATC_OUTPUT_NUM_CC[i + j*params->inputImgWidth] != OUTPUT_NUM_CC[i + j*outStride]){
                    ret = 1;
                    printf("Error !!! Mismatch with natural C output_num_cc (X=%d, Y=%d)= %d, eve output (X=%d, Y=%d)= %d\n", i, j, NATC_OUTPUT_NUM_CC[i + j*params->inputImgWidth], i, j, OUTPUT_NUM_CC[i + j*outStride]);
                    break;
                }
                if(NATC_OUTPUT_DENOM_VAR[i + j*params->inputImgWidth] != OUTPUT_DENOM_VAR[i + j*outStride]){
                    ret = 1;
                    printf("Error !!! Mismatch with natural C output_denom_var_cc (X=%d, Y=%d)= %d, eve output_denom_var_cc (X=%d, Y=%d)= %d\n", i, j, NATC_OUTPUT_DENOM_VAR[i + j*params->inputImgWidth], i, j, OUTPUT_DENOM_VAR[i + j*outStride]);
                    break;
                }
            }
        }

        if(ret !=0)
        {
            printf("Natural C & EVE DIDN'T MATCH !!!!!!!!!!\n");
        }
        else
        {
            printf("Natural C & EVE MATCHED\n");
        }
#endif

        size= params->inputImgWidth*params->inputImgHeight;
        max= 0.0;
        maxi= 0;

        /* Convert to floating point and implement the true formula of normalized cross-correlation */
        for (j= 0; j < params->inputImgHeight; j++ ) {
            for( i = 0; i < params->inputImgWidth; i++ ) {
                if (OUTPUT_DENOM_VAR[i] != 0) {
                    //OUTPUT_NCC[i + j*params->inputImgWidth]= (float)OUTPUT_NUM_CC[i + j*outStride]/sqrt(shiftFloat((float)OUTPUT_DENOM_VAR[i + j*outStride] * templateVar, params->qShift));
                    OUTPUT_NCC[i + j*params->inputImgWidth]= (float)OUTPUT_NUM_CC[i + j*outStride]/sqrt((float)OUTPUT_DENOM_VAR[i + j*outStride] * templateVar);
                }
                else {
                    OUTPUT_NCC[i + j*params->inputImgWidth]= 0.0;
                }
                if (OUTPUT_NCC[i + j*params->inputImgWidth] > max) {
                    max= OUTPUT_NCC[i + j*params->inputImgWidth];
                    maxi= i;
                }
            }
        }


        /* compare with reference output */
        maxErr= 0.0;
        maxErr_i= 0;
        for (i=0;i<size;i++) {
            err= fabs(OUTPUT_NCC[i] - output[i])/fabs(output[i]);
            if (maxErr < err) {
                maxErr= err;
                maxErr_i= i;
            }
        }

        if (maxErr > 0.01) {
            ret= 1;
        }

        if(ret !=0)
        {
            printf("Reference output and EVE DIDN'T MATCH !!!!!!!!!! with max error of %f percent reached at i= %d, (x=%d, y=%d)\n\n", 100.0*maxErr, maxErr_i, maxErr_i - ((maxErr_i/params->inputImgWidth)*params->inputImgWidth), maxErr_i/params->inputImgWidth);
        }
        else
        {
            printf("Reference output and EVE MATCHED with max error of %3.2f percent\n\n", 100.0*maxErr);
        }

        printf("Maximum value reached at (x=%d, y=%d)\n", maxi - ((maxi/params->inputImgWidth)*params->inputImgWidth), maxi/params->inputImgWidth);

#endif
    }

    profiler_deinit();

    if(params->writeOutput)
    {
        printf("Writing output file, please be patient ...\n");
        writeOutputFile(OUTPUT_NCC, size, params->outFileName);
        printf("Writing output file, done.\n");
    }

    return 0;
}

int main()
{
    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    sncc_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    printf("\nncc test\n\n");

    params = (sncc_Config *)(&gConfig_ncc);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_ncc_vcop(params);
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
            status = readparamfile(configFileName, &gsTokenMap_ncc[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_ncc_vcop(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);
    exit(0);

}

void nccInFrame(NccFunc nccFunc, uint8_t *pFrame, int16_t *pTemplate, int32_t *pOutput_num_cc, uint32_t *pOutput_denom_var, sncc_Config * params) {

    int32_t h, w;
    uint16_t scratchStride, sumStride, sizeOfScratch, sizeOfSum;
    int32_t errorCode= 0;

    uint16_t roiBlkWidth, roiBlkHeight,numHorzBlocks, numVertBlocks;

    roiBlkWidth= params->computeBlkWidth + params->templateBlkWidth - 1;
    roiBlkHeight= params->computeBlkHeight + params->templateBlkHeight - 1;

    numHorzBlocks=  (params->inputImgWidth + params->computeBlkWidth - 1 ) / params->computeBlkWidth;
    numVertBlocks=  (params->inputImgHeight + params->computeBlkHeight - 1 ) / params->computeBlkHeight;

    errorCode= init_slidingSum_params
            (
                    params->templateBlkWidth,       /*template image width*/
                    params->templateBlkHeight,      /*template image height*/
                    params->computeBlkWidth,
                    params->computeBlkHeight,
                    WBUF_LAYOUT.PSCATT_OFFSETS, /* Point to an array of 8 bytes */
                    sizeof(WBUF_LAYOUT.PSCATT_OFFSETS), /* Should be 32 */
                    &scratchStride,
                    &sizeOfScratch,
                    &sumStride,
                    &sizeOfSum);

    assert(errorCode==0);
    assert(sizeof(WBUF_LAYOUT.SCRATCH_BLK) >= sizeOfScratch);
    assert(sizeof(IBUFH_LAYOUT.SUM_BLK) >= sizeOfSum);

    /* Copy the template to the wbuf */
    copyHalfWordsToImBuf(WBUF_LAYOUT.TEMPLATE_BLK, pTemplate, params->templateBlkWidth, params->templateBlkHeight, params->templateBlkWidth, params->templateBlkWidth);

    for (h=0; h < numVertBlocks*params->computeBlkHeight; h+= params->computeBlkHeight) {
        for (w=0; w < numHorzBlocks*params->computeBlkWidth; w+= params->computeBlkWidth) {

            /* copy a block of the image from ext memory to image buffer */
            copyBytesToImBuf(IBUFL_LAYOUT.INPUT_BLK, pFrame + w + h*params->inputImgStride, roiBlkWidth, roiBlkHeight, roiBlkWidth, params->inputImgStride);

            nccFunc(
                    IBUFL_LAYOUT.INPUT_BLK,           /*original input image data pointer */
                    roiBlkWidth,        /*original input image width*/
                    roiBlkHeight,       /*original input image height*/
                    roiBlkWidth,        /*original input image pitch*/
                    WBUF_LAYOUT.TEMPLATE_BLK,          /*template image pointer*/
                    params->templateBlkWidth,       /*template image width*/
                    params->templateBlkHeight,      /*template image height*/
                    params->templateBlkWidth,       /*template image pitch*/
                    params->sizeQshift,
                    params->qShift,
                    params->xDirJump,           /*Jump in x direction while searching*/
                    params->yDirJump,           /*Jump in y direction while searching*/
                    IBUFH_LAYOUT.OUT_NUM_CC_BLK,         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                    IBUFH_LAYOUT.OUT_DENOM_VAR_BLK,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                    params->computeBlkWidth,           /*Out Score buffer pitch*/
                    WBUF_LAYOUT.SCRATCH_BLK,
                    scratchStride,
                    IBUFH_LAYOUT.SUM_BLK,
                    sumStride
            );

            /* Save the output block from image buffer to ext memory */
            copyWordsToExt((uint32_t*)IBUFH_LAYOUT.OUT_NUM_CC_BLK , (uint32_t*)pOutput_num_cc + w + h*numHorzBlocks*params->computeBlkWidth, params->computeBlkWidth, params->computeBlkHeight, params->computeBlkWidth, numHorzBlocks*params->computeBlkWidth);
            copyWordsToExt(IBUFH_LAYOUT.OUT_DENOM_VAR_BLK, pOutput_denom_var + w + h*numHorzBlocks*params->computeBlkWidth, params->computeBlkWidth, params->computeBlkHeight, params->computeBlkWidth, numHorzBlocks*params->computeBlkWidth);

        } /* w loop */
    } /* h loop */

}

void wrapper_for_vcop_ncc(
        uint8_t     orgImg[],           /*original input image data pointer */
        int32_t     orgImgWidth,        /*original input image width*/
        int32_t     orgImgHeight,       /*original input image height*/
        int32_t     orgImgPitch,        /*original input image pitch*/
        int16_t     tempImg[],          /*template image pointer*/
        int32_t     tempImgWidth,       /*template image width*/
        int32_t     tempImgHeight,      /*template image height*/
        int32_t     tempImgPitch,       /*template image pitch*/
        uint8_t     sizeQshift,         /*number of fractional bits used to compute the inverse of the size of the template*/
        uint8_t     qShift,             /*number of fractional bits */
        uint8_t     xDirJump,           /*Jump in x direction while searching*/
        uint8_t     yDirJump,           /*Jump in y direction while searching*/
        int32_t     outNumCC[],         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        uint32_t    outDenomVar[],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        int32_t     outPitch,           /*Out Score buffer pitch*/
        int32_t     scratch[],
        int32_t     scratchStride,
        uint32_t    sum[],
        int32_t     sumStride
){

    vcop_slidingSum(
            &orgImg[0],
            orgImgPitch,        /*original input image pitch*/
            tempImgWidth,       /*template image width*/
            tempImgHeight,      /*template image height*/
            orgImgWidth - tempImgWidth + 1,
            orgImgHeight - tempImgHeight + 1,
            &scratch[0],
            scratchStride,
            &sum[0],
            sumStride,
            WBUF_LAYOUT.PSCATT_OFFSETS, /* Point to an array of 16 bytes. Call init_ncc_params() to initialize content pointed by pOffset*/
            IBUFL_LAYOUT.SCRATCH_LINE);


    if (qShift== 0) {
        vcop_ncc_qShift0(
                &orgImg[0],
                orgImgWidth,
                orgImgHeight,
                orgImgPitch,        /*original input image pitch*/
                &tempImg[0],           /*template image pointer*/
                tempImgWidth,       /*template image width*/
                tempImgHeight,      /*template image height*/
                tempImgPitch,       /*template image pitch*/
                &sum[0],
                (uint16_t*)&sum[0],
                (uint16_t*)&sum[0] + 1,
                sumStride,
                sizeQshift,
                qShift,
                &outNumCC[0],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                &outDenomVar[0],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                outPitch           /*Out Score buffer pitch*/
        );
    }
    else if (qShift== 8) {
        vcop_ncc_qShift8(
                &orgImg[0],
                orgImgWidth,
                orgImgHeight,
                orgImgPitch,        /*original input image pitch*/
                &tempImg[0],           /*template image pointer*/
                tempImgWidth,       /*template image width*/
                tempImgHeight,      /*template image height*/
                tempImgPitch,       /*template image pitch*/
                &sum[0],
                (uint16_t*)&sum[0],
                (uint16_t*)&sum[0] + 1,
                sumStride,
                sizeQshift,
                qShift,
                &outNumCC[0],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                &outDenomVar[0],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                outPitch           /*Out Score buffer pitch*/
        );
    }
    else {

        vcop_ncc(
                &orgImg[0],
                orgImgWidth,
                orgImgHeight,
                orgImgPitch,        /*original input image pitch*/
                &tempImg[0],           /*template image pointer*/
                tempImgWidth,       /*template image width*/
                tempImgHeight,      /*template image height*/
                tempImgPitch,       /*template image pitch*/
                &sum[0],
                (uint16_t*)&sum[0],
                (uint16_t*)&sum[0] + 1,
                sumStride,
                sizeQshift,
                qShift,
                &outNumCC[0],          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                &outDenomVar[0],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                outPitch           /*Out Score buffer pitch*/
        );
    }
}
/*--------------------------------------------------------------------------*/
/* End of file: vcop_ncc_tb.c                                        */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

