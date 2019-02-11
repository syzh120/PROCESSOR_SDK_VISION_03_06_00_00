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


/** @file templateMatching_test.c
 *
 *  @brief  This file contains test code for template matching applet
 *
 *
 *  @date   24 July 2016
 *
 *  Description
 *    This file contains test code to validate the frame level applet for
 *    templateMatching transform. It also checks the output against c reference
 *    outputs and profiles the performance and computes the system
 *    overheads.
 */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>


#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"
#include "iTemplateMatching_ti.h"
#include "../vlib/vcop_ncc/inc/vcop_ncc_cn.h"
#include "templateMatching_config.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

//#define SCAN_DIM
#if !(VCOP_HOST_EMULATION)
extern uint32_t  _bam_text_size;
extern uint32_t  _bam_neardata_size;
extern uint32_t  _bam_fardata_size;
extern uint32_t  _algo_fardata_size;
extern uint32_t  _algo_neardata_size;
extern uint32_t  _algo_text_size;
extern uint32_t  _starterware_fardata_size;
extern uint32_t  _starterware_neardata_size;
extern uint32_t  _starterware_text_size;
extern uint32_t  _rts_fardata_size;
extern uint32_t  _rts_neardata_size;
extern uint32_t  _rts_text_size;

extern uint32_t  _text_size;
#endif

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (8*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;

TIMemObject memObj_DMEM;

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
    int32_t i;
    TIMemHandle memHdl_DMEM = &memObj_DMEM;
    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].space == IALG_DARAM0) {
            memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
        }
        else {
            memRec[i].base = (Void *) malloc( memRec[i].size);
        }
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
    }
    return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
    int32_t i;
    TIMemHandle memHdl_DMEM = &memObj_DMEM;

    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
        if(memRec[i].space == IALG_DARAM0) {
            TI_ResetMemoryHandle(memHdl_DMEM);
        }else {
            free(memRec[i].base);
        }
    }
    return IALG_EOK;
}

typedef struct IM_Fxns
{
    IVISION_Fxns * ivision;

} IM_Fxns;

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '   ')||(LinePtr[0] == ','))
    {
        LinePtr++;
    }
    return(LinePtr);
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

uint8_t log2(uint32_t val) {

    uint32_t origval;
    uint8_t i= 0;

    origval= val;

    val= val >> 1;

    while (val!=0) {
        val>>=1;
        i++;
    }

    if (origval & ((1<<i) - 1)) { /* round up the result */
        i= i + 1;
    }
    return i;
}

/* Calculate the mean and subtract it from every pixel */
uint32_t normalizeTemplate(
        int16_t *dst, /* Destination pointer to the 16-bits template output in Q format */
        uint8_t *src, /* Source pointer to the 8-bits template image */
        uint32_t width, /* width of the template in number of pixels */
        uint32_t height, /* height of the template in number of rows */
        uint32_t stride, /* stride of the template in number of pixels */
        uint8_t sizeQshift, /* Number of fractional bits used to represent 1/(templateWidth*templateHeight) */
        uint8_t qShift) /* Number of fractional bits used to represent the output */
    {

    int32_t tAver, sum= 0;
    uint32_t tVar, w, h;
    int32_t t_p;
    uint16_t qValDiffHalf, qShiftDiff, qValHalf;

    qShiftDiff= sizeQshift - qShift;
    qValDiffHalf= 1<<(qShiftDiff -1 );
    qValHalf= 1<<(qShift - 1);

    memset(dst, 0, stride * height);

    /* Add all the pixel values together */
    for (h= 0; h < height; h++) {
        for (w= 0; w < width; w++) {
            sum += src[w + h*width];
        }
    }

    /* Caculate the mean by dividing the sum of all the pixels by the number of pixels in the template, result has 'sizeQshift' fractional bits */
    tAver= ((sum<<sizeQshift) + (width*height)/2)/(width*height);
    tVar= 0;

    for (h= 0; h < height; h++) {
        for (w= 0; w < width; w++) {
            /* Subtract the mean from every pixel values. Convert to Q format by left shifting the input template valye by qShift and
             * right shifting the mean by qShiftDiff
             */
            t_p= (src[w + h*width]<<qShift) - ((tAver + qValDiffHalf)>>qShiftDiff);
            dst[w + h*stride]= t_p;
            /* Calculate the pseudo variance of the template, which represents the constant value K used in the normalized cross-correlation
             * Result is in Q format
             * */
            tVar+= ((unsigned int)t_p*t_p + qValHalf) >> qShift;
        }
    }

    return tVar; /* Return the pseudo-variance */
}


int test_templateMatching(stemplateMatching_Config * gConfig_templateMatching, int testNum)
{
    int i=0, j=0, result = 0;
    uint16_t idx;
#ifdef SCAN_DIM
    initialWidth= 0;
#endif
    char *statusStr = NULL;
    unsigned int profile_sctm;
    uint8_t *wbufToZero;
    uint32_t sizeInputElmt, sizeOutput, sizeInput, numBytes, sizeTemplate;
    uint8_t sizeQshift;

    char filepath[256];
    TI_FILE *fid;
    uint32_t t;

    uint8_t *input, *tempInput, *templateImg;
    int16_t *normTemplate;
    int32_t *outputNumCC, *refOutputNumCC;
    uint32_t *outputDenomVar, *refOutputDenomVar;

    int fail = 0;

    unsigned int profile_tsc, profile_create_tsc;
    TEMPLATE_MATCHING_TI_ControlInParams ctlInParams;
    TEMPLATE_MATCHING_TI_ControlOutParams ctlOutParams;

    int32_t numMemRec;
    IALG_MemRec *memRec;
    int32_t status;
    IALG_Cmd cmd;

    /*-----------------------------------------------------------------
             Pointer to algorithm instance
             -----------------------------------------------------------------*/
    IM_Fxns *     handle;

    /*-----------------------------------------------------------------
             Algorithm parameters memory in stack
             -----------------------------------------------------------------*/
    TEMPLATE_MATCHING_TI_CreateParams  createParams;


    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc[TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *inBufDescList[TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL];

    TEMPLATE_MATCHING_TI_outArgs   outArgs;
    IVISION_OutBufs     outBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc[TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *outBufDescList[TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL];

    outArgs.iVisionOutArgs.size = sizeof(TEMPLATE_MATCHING_TI_outArgs);

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t *pDmem;
    TIMemHandle memHdl_DMEM;

    pDmem = (uint8_t *)&DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;
    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

    /*-----------------------------------------------------------------
          Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL;

    for(i = 0 ; i < TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL ;i++)
    {
        inBufDescList[i]     = &inBufDesc[i];
    }

    for(i = 0 ; i < TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        outBufDescList[i]     = &outBufDesc[i];
    }
    profiler_init();
    /* In order to derive stack requirements, call profiler_initStack() which will write DEADBEEF from current stack pointer up to the top */
    profiler_initStack(profiler_getSP());

    for (t=0;t<templateMatching_numTestCases;t++) {

        /* Enable SCAN_DIM if you want to vary the width and height of the image for each test case
         * This enable wide coverage of the image dimensions to be tested
         *  */
#ifdef SCAN_DIM
        initialWidth= gConfig_templateMatching[t].srcImageWidth;
        while (gConfig_templateMatching[t].srcImageHeight >= 64) {
            while (gConfig_templateMatching[t].srcImageWidth >= 64) {
#endif

                /* Allocate input buffer based on srcImagePitch and srcImageHeight values.
                 * It is assumed that the pitch value srcImagePitch passed to the testbench already includes (templateWidth - 1) extra pixels.
                 * However srcImageHeight represents the ROi's height and is not supposed to include the border pixels and thus the testbench must add these.
                 * */

                sizeInputElmt= 1;
                sizeInput= sizeInputElmt*gConfig_templateMatching[t].srcImagePitch*(gConfig_templateMatching[t].srcImageHeight + gConfig_templateMatching[t].templateHeight - 1);
                sizeTemplate= gConfig_templateMatching[t].templateWidth * gConfig_templateMatching[t].templateHeight;

                tempInput= (uint8_t*)malloc(gConfig_templateMatching[t].srcImageWidth*gConfig_templateMatching[t].srcImageHeight);
                assert(tempInput != NULL);

                input= (uint8_t*)malloc(sizeInput);
                assert(input != NULL);

                templateImg= (uint8_t*)malloc(sizeTemplate);
                assert(templateImg != NULL);

                normTemplate= (int16_t*)malloc(2*sizeTemplate);
                assert(normTemplate != NULL);

                /* Allocate output and reference output buffer
                 * */

                sizeOutput= 4*gConfig_templateMatching[t].dstImagePitch*gConfig_templateMatching[t].srcImageHeight;

                outputNumCC= (int32_t*)malloc(sizeOutput);
                assert(outputNumCC != NULL);

                refOutputNumCC= (int32_t*)malloc(sizeOutput);
                assert(refOutputNumCC != NULL);

                outputDenomVar= (uint32_t*)malloc(sizeOutput);
                assert(outputDenomVar != NULL);

                refOutputDenomVar= (uint32_t*)malloc(sizeOutput);
                assert(refOutputDenomVar != NULL);

                if (gConfig_templateMatching[t].pattern== 1) {
                    /* Generate random input data */
                    srand(1);

                    for(i=0; i<sizeInput; i++)
                    {
                        input[i] = rand() % 256;
                    }

                    for(i=0; i<sizeTemplate; i++)
                    {
                        templateImg[i] = rand() % 256;
                    }

                }
                else {
                    sprintf(filepath, "../testvecs/%s", gConfig_templateMatching[t].inImage);
                    fid= FOPEN(filepath,"rb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }

                    numBytes= FREAD(tempInput, 1, gConfig_templateMatching[t].srcImageWidth*gConfig_templateMatching[t].srcImageHeight, fid);
                    assert(numBytes== gConfig_templateMatching[t].srcImageWidth*gConfig_templateMatching[t].srcImageHeight );
                    FCLOSE(fid);

                    sprintf(filepath, "../testvecs/%s", gConfig_templateMatching[t].inTemplateImage);
                    fid= FOPEN(filepath,"rb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }

                    numBytes= FREAD(templateImg, 1, sizeTemplate, fid);
                    assert(numBytes== sizeTemplate);
                    FCLOSE(fid);
                }

                sizeQshift= log2(gConfig_templateMatching[t].templateWidth*gConfig_templateMatching[t].templateHeight);
                copyInputImg(input, tempInput, gConfig_templateMatching[t].srcImageWidth, gConfig_templateMatching[t].srcImageHeight, gConfig_templateMatching[t].srcImagePitch, gConfig_templateMatching[t].srcImageHeight + gConfig_templateMatching[t].templateHeight - 1);
                normalizeTemplate(normTemplate, templateImg, gConfig_templateMatching[t].templateWidth, gConfig_templateMatching[t].templateHeight, gConfig_templateMatching[t].templateWidth, sizeQshift, gConfig_templateMatching[t].qShift);
                /* Zero out both output and reference output arrays */
                memset(outputNumCC, 0, sizeOutput);
                memset(refOutputNumCC, 0, sizeOutput);
                memset(outputDenomVar, 0, sizeOutput);
                memset(refOutputDenomVar, 0, sizeOutput);

                profiler_start();
                /***********************************************************************************************************************************/

                /*-----------------------------------------------------------------
                            Set algorithm parameters
                            -----------------------------------------------------------------*/
                createParams.visionParams.algParams.size   = sizeof(TEMPLATE_MATCHING_TI_CreateParams);
                createParams.visionParams.cacheWriteBack   = NULL;
                createParams.imgFrameWidth                 = gConfig_templateMatching[t].srcImageWidth;
                createParams.imgFrameHeight                = gConfig_templateMatching[t].srcImageHeight;
                createParams.templateWidth                 = gConfig_templateMatching[t].templateWidth;
                createParams.templateHeight                = gConfig_templateMatching[t].templateHeight;
                createParams.xDirJump                      = 1;
                createParams.xDirJump                      = 1;
                createParams.method                        = TEMPLATE_MATCHING_TI_NCC;
                createParams.qShift                        = gConfig_templateMatching[t].qShift;

                /*---------------------------------------------------
                           Query alogorithm memory requirement using standard IALG interface
                           -----------------------------------------------------------------*/
                numMemRec = TEMPLATE_MATCHING_TI_VISION_FXNS.ialg.algNumAlloc();
                memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

                status = TEMPLATE_MATCHING_TI_VISION_FXNS.ialg.algAlloc(
                        (IALG_Params *)(&createParams), NULL, memRec);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

#if ENABLE_TRACES
                TEST_PRINTF("Template matching Applet Create Done\n");
#endif

                /*-----------------------------------------------------------------
                 Allocate memory for all the mem records
                 Application has to implement the below function
                 Refer the example implementation below in this file
                -----------------------------------------------------------------*/
                status = TestApp_AllocMemRecords(memRec,numMemRec);
                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                /* Start measuring execution time for creation process */
                /*-----------------------------------------------------------------
                 Intialize the algorithm instance with the allocated memory
                 and user create parameters
                -----------------------------------------------------------------*/
                status = TEMPLATE_MATCHING_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                        memRec,NULL,(IALG_Params *)(&createParams));

                profiler_end_print(0);
                profile_create_tsc = gTest_TI_profileTsc;

                handle = (IM_Fxns *) memRec[0].base;

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }
#if ENABLE_TRACES
                TEST_PRINTF("Template matching applet Init Done\n");
#endif

                /* Use control API to query the optimum output block width and height found by algInit() */

                ctlInParams.algParams.size= sizeof(TEMPLATE_MATCHING_TI_ControlInParams);
                ctlOutParams.algParams.size= sizeof(TEMPLATE_MATCHING_TI_ControlOutParams);

                cmd= TEMPLATE_MATCHING_TI_GET_OUTPUT_BLOCK_DIM;
                status = handle->ivision->algControl((IVISION_Handle)handle, cmd, (const IALG_Params *)&ctlInParams, (IALG_Params *)&ctlOutParams);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                inArgs.subFrameInfo = 0;
                inArgs.size                  = sizeof(IVISION_InArgs);

                idx = TEMPLATE_MATCHING_TI_BUFDESC_IN;
                inBufs.bufDesc[idx]->numPlanes                          = 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;

                /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
                 * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
                 * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
                 * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
                 * at (frameROI.topLeft.x, frameROI.topLeft.y) .
                 * */
                inBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_templateMatching[t].srcImagePitch;
                inBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_templateMatching[t].srcImageHeight + createParams.templateHeight - 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_templateMatching[t].srcImageWidth;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_templateMatching[t].srcImageHeight;
                inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )input ;

                if(inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx = TEMPLATE_MATCHING_TI_BUFDESC_IN_TEMPLATE;
                inBufs.bufDesc[idx]->numPlanes                          = 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;

                inBufs.bufDesc[idx]->bufPlanes[0].width                 = createParams.templateWidth;
                inBufs.bufDesc[idx]->bufPlanes[0].height                = createParams.templateHeight;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = createParams.templateWidth;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = createParams.templateHeight;
                inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )normTemplate ;

                if(inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx= TEMPLATE_MATCHING_TI_BUFDESC_OUT;
                outBufs.bufDesc[idx]->numPlanes                          = 2;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_templateMatching[t].dstImagePitch;
                outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_templateMatching[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_templateMatching[t].srcImageWidth;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_templateMatching[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )outputNumCC;

                outBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.x    = 0;
                outBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.y    = 0;
                outBufs.bufDesc[idx]->bufPlanes[1].width                 = gConfig_templateMatching[t].dstImagePitch;
                outBufs.bufDesc[idx]->bufPlanes[1].height                = gConfig_templateMatching[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[1].frameROI.width        = gConfig_templateMatching[t].srcImageWidth;
                outBufs.bufDesc[idx]->bufPlanes[1].frameROI.height       = gConfig_templateMatching[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[1].buf = (uint8_t * )outputDenomVar;

#if ENABLE_TRACES
                TEST_PRINTF("Processing Start\n");
#endif
                status = handle->ivision->algProcess((IVISION_Handle)handle,
                        &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }


#if ENABLE_TRACES

                TEST_PRINTF("Processing End\n");

                TEST_PRINTF("Clearing WBUF\n");
#endif


                /* Erase output and wmem after first call to test repeatabiity
                 * wmem contains param registers and constant so erasing it will test the context saving and restore capability of the function
                 * */
                memset(outputNumCC, 0, sizeof(outputNumCC));
                memset(outputDenomVar, 0, sizeof(outputDenomVar));
                vcop_minit();
                wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
                memset(wbufToZero, 0, 31*1024);
                vcop_free(wbufToZero);

                /* Prepare to call EVELIB_templateMatching_execute() a second time. This time we are going to measure its performance.*/
                profiler_start();
                status = handle->ivision->algProcess((IVISION_Handle)handle,
                        &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);
                profiler_end_print(1);

                profile_tsc = gTest_TI_profileTsc;
                profile_sctm = gTest_TI_profileSctm[0];

                /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                /*  Call the natural C implementation for templateMatching transfrom which results will be used to validate EVE's output                                         */
                /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

                vcop_ncc_cn(
                        input,           /*original input image data pointer */
                        gConfig_templateMatching[t].srcImageWidth + createParams.templateWidth - 1,        /*original input image width*/
                        gConfig_templateMatching[t].srcImageHeight + createParams.templateHeight - 1,       /*original input image height*/
                        gConfig_templateMatching[t].srcImagePitch,        /*original input image pitch*/
                        normTemplate,          /*templateImg image pointer*/
                        createParams.templateWidth,       /*template image width*/
                        createParams.templateHeight,      /*template image height*/
                        createParams.templateWidth,       /*template image pitch*/
                        sizeQshift,
                        gConfig_templateMatching[t].qShift,
                        0,           /*Jump in x direction while searching*/
                        0,           /*Jump in y direction while searching*/
                        refOutputNumCC,         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
                        refOutputDenomVar,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
                        gConfig_templateMatching[t].srcImageWidth,           /*Out Score buffer pitch*/
                        NULL,
                        0,
                        NULL,
                        0
                );

                fail = 0;

                for(i=0; i<gConfig_templateMatching[t].srcImageHeight; i++)
                {
                    for(j=0; j<gConfig_templateMatching[t].srcImageWidth; j++)
                    {
                        if(outputNumCC[i*gConfig_templateMatching[t].dstImagePitch+j] != refOutputNumCC[i*gConfig_templateMatching[t].dstImagePitch+j])
                        {
                            fail = 1;
                            TEST_PRINTF("Num CC, row:%d, col:%d, out:%u, EOut:%u \n", i, j, outputNumCC[i*gConfig_templateMatching[t].dstImagePitch+j], refOutputNumCC[i*gConfig_templateMatching[t].dstImagePitch+j]);
                            break;
                        }
                    }
                }

                for(i=0; i<gConfig_templateMatching[t].srcImageHeight; i++)
                {
                    for(j=0; j<gConfig_templateMatching[t].srcImageWidth; j++)
                    {
                        if(outputDenomVar[i*gConfig_templateMatching[t].dstImagePitch+j] != refOutputDenomVar[i*gConfig_templateMatching[t].dstImagePitch+j])
                        {
                            fail = 1;
                            TEST_PRINTF("Denom Var, row:%d, col:%d, out:%u, EOut:%u \n", i, j, outputDenomVar[i*gConfig_templateMatching[t].dstImagePitch+j], refOutputDenomVar[i*gConfig_templateMatching[t].dstImagePitch+j]);
                            break;
                        }
                    }
                }

                statusStr = fail? "FAILED" : "PASSED";
                fflush(stdout);

                result= (int32_t)((uint32_t)result & (uint32_t)fail);

                TEST_PRINTF("%d) Template dimension %dx%d qShift:%d %5s %10d %10d %15.2f %20.2f %10.2f %20.2f %16.2f       Create graph is %2.2f Mcycles per frame but it is a one-time startup call, output block is %d x %d\n", testNum, createParams.templateWidth, createParams.templateHeight,
                        gConfig_templateMatching[t].qShift, statusStr, gConfig_templateMatching[t].srcImageWidth, gConfig_templateMatching[t].srcImageHeight,
                        (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0), (profile_tsc*1.0)/(gConfig_templateMatching[t].srcImageWidth * gConfig_templateMatching[t].srcImageHeight),
                        (profile_sctm*1.0)/(gConfig_templateMatching[t].srcImageWidth * gConfig_templateMatching[t].srcImageHeight),(profile_tsc/500000.0), (profile_create_tsc*1.0)/1000000.0, ctlOutParams.outputBlockWidth, ctlOutParams.outputBlockHeight);

                fflush(stdout);

                profiler_printStatus(fail ? -1 : 0);

                if (gConfig_templateMatching[t].pattern== 0) {
                    /* Write output file */
                    sprintf(filepath, "../testvecs/%s", gConfig_templateMatching[t].outNumCC);
                    fid= FOPEN(filepath,"wb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }
                    numBytes= FWRITE(outputNumCC, 1, gConfig_templateMatching[t].dstImagePitch*gConfig_templateMatching[t].srcImageHeight*4, fid);
                    FCLOSE(fid);

                    sprintf(filepath, "../testvecs/%s", gConfig_templateMatching[t].outDenomVar);
                    fid= FOPEN(filepath,"wb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }
                    numBytes= FWRITE(outputDenomVar, 1, gConfig_templateMatching[t].dstImagePitch*gConfig_templateMatching[t].srcImageHeight*4, fid);
                    FCLOSE(fid);
                }

                EXIT_LOOP:
                status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                }
                /* Here Free memory for all the mem records */
                status = TestApp_FreeMemRecords(memRec,numMemRec);
                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                }

                if ( memRec != NULL )
                {
                    free(memRec);
                }

                if ( outputNumCC != NULL)
                {
                    free(outputNumCC);
                }

                if ( outputDenomVar!= NULL)
                {
                    free(outputDenomVar);
                }

                if (input != NULL)
                {
                    free(input);
                }

                if (tempInput != NULL)
                {
                    free(tempInput);
                }

                if (templateImg != NULL)
                {
                    free(templateImg);
                }

                if (normTemplate != NULL)
                {
                    free(normTemplate);
                }

                if(refOutputNumCC != NULL)
                {
                    free(refOutputNumCC);
                }

                if(refOutputDenomVar != NULL)
                {
                    free(refOutputDenomVar);
                }
                 /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
                profiler_getStackDepth();
#endif

#ifdef SCAN_DIM
                gConfig_templateMatching[t].srcImageWidth -= 16;
            }
            gConfig_templateMatching[t].srcImageWidth= initialWidth;
            gConfig_templateMatching[t].srcImageHeight -= 2;
        }
#endif
    }

    return result;
}

int main(int argc, char *argv[])
{
    int status = 0;
    char configFile[FILE_NAME_SIZE]={0};
    char configLine[MAX_CONFIG_LINE_SIZE];
    char configParam[MAX_PARAM_STRING_SIZE];
    int8_t         *LinePtr;
    TI_FILE * fp;
    int32_t         lineNum = -1;
    int32_t         config_cmd;

    report_printAppletInfo((int8_t *)"TEMPLATE_MATCHING_TI_VISION");

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
        strcpy(configFile,CONFIG_LIST_FILE_NAME);
    }

    fp = FOPEN((const char *)configFile , "r");
    if(fp== NULL)
    {
        TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
        return(status);
    }

    TEST_PRINTF("\n%-34s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
            "Algorithm", "Status", "Width", "Height", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "Total CycPerPix", "VCOP busy CycPerPix","TimePerFr(MSec)", "Comments");

    while ( 1 )
    {
        memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
        status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = (int8_t *)configLine;
        if ((status == EOF) || (status == 0))
        {
            break;
        }
        status = 0;
        lineNum++;
        sscanf((const char *)LinePtr, "%d",&config_cmd);
        sscanf((const char *)LinePtr, "%s",configParam);

        if(config_cmd == 0)
        {
            break;
        }
        else if(config_cmd == 2)
        {
            continue;
        }
        else if(config_cmd == 1)
        {
            LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
            status  = sscanf((const char *)LinePtr, "%s",configFile);

            status = readparamfile(configFile, &gsTokenMap_templateMatching[0]);
            if(status == -1)
            {
                TEST_PRINTF("Parser Failed");
                return -1 ;
            }

            profiler_testCaseInfo((int8_t *)gConfig_templateMatching[0].testCaseName, (int8_t *)gConfig_templateMatching[0].desc,
                    gConfig_templateMatching[0].performanceTestcase);
            printparams(&gsTokenMap_templateMatching[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_templateMatching),
                    sizeof(stemplateMatching_Config));

            /* Validate the applet */
            status = test_templateMatching(gConfig_templateMatching, lineNum);
            if(status == -1)
            {
                return status;
            }
        }
        else
        {
            TEST_PRINTF(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
        }

    }

    FCLOSE(fp);

    return status;
}
