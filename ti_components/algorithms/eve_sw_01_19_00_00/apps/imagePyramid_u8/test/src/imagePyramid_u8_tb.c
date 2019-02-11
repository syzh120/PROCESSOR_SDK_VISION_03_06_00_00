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


/** @file evelib_imagePyramid_test.c
 *
 *  @brief  This file contains test code for image pyramid applet
 *
 *
 *  @date   28 Nov 2013
 *
 *  Description
 *    This file contains test code to validate the frame level applet for
 *    up to 5 levels image pyramid. It also checks the output against c reference
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
#include "iImagePyramid_u8_ti.h"
#include "../imgsiglib/BlockAverage2x2/inc/vcop_blockAverage2x2_cn.h"
#include "../imgsiglib/vcop_gauss5x5PyramidKernel_8/inc/vcop_gauss5x5PyramidKernel_8_cn.h"
#include "imagePyramid_u8_config.h"
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

#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (8*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

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

int test_imagePyramid_u8(void)
{
    int l=0, i=0, j=0, result = 0;
#ifdef SCAN_DIM
    int notEven= 0, initialWidth= 0;
#endif
    uint8_t *curRefOutput;
    uint8_t *wbufToZero;
    uint32_t sizeOutput, sizeRefOutput, sizeInput, numBytes;
    uint32_t refRoiWidth[IMGPYRAMID_MAX_NUM_LEVELS];
    uint32_t refRoiHeight[IMGPYRAMID_MAX_NUM_LEVELS];
    uint32_t refOutputPitch[IMGPYRAMID_MAX_NUM_LEVELS];
    uint32_t refOutputHeight[IMGPYRAMID_MAX_NUM_LEVELS];
    uint32_t extraBorders;
    uint32_t offsetX, offsetY;

    char filepath[256];
    TI_FILE *fid;
    uint32_t t;

    uint8_t *input;
    uint8_t *output;
    uint8_t *tempRefBuf;
    uint8_t *refOutput;
    int fail = 0;


    int32_t numMemRec;
    IALG_MemRec *memRec;
    int32_t status;

    /*-----------------------------------------------------------------
             Pointer to algorithm instance
             -----------------------------------------------------------------*/
    IM_Fxns *     handle;

    /*-----------------------------------------------------------------
             Algorithm parameters memory in stack
             -----------------------------------------------------------------*/
    IMAGE_PYRAMID_U8_TI_CreateParams  createParams;

    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc;
    IVISION_BufDesc   *inBufDescList[1];

    IMAGE_PYRAMID_U8_TI_outArgs   outArgs;
    IVISION_OutBufs                  outBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc;
    IVISION_BufDesc   *outBufDescList[1];

    outArgs.iVisionOutArgs.size = sizeof(IMAGE_PYRAMID_U8_TI_outArgs);

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t *pDmem;
    TIMemHandle memHdl_DMEM;

    pDmem = (uint8_t *)&DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;
    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);


  profiler_init();
  profiler_initStack(profiler_getSP());


    t=0;

        /* Enable SCAN_DIM if you want to vary the width and height of the image for each test case
         * This enable wide coverage of the image dimensions to be tested
         *  */
#ifdef SCAN_DIM
        initialWidth= gConfig_imagePyramid_u8[t].srcImageWidth;
        while (gConfig_imagePyramid_u8[t].srcImageHeight >= 64) {
            while (gConfig_imagePyramid_u8[t].srcImageWidth >= 64) {
#endif

                /* Allocate input buffer
                 * In case filtering type is 2x2 averaging, the dimension allocated is the one specified by srcImagePitch x srcImageHeight.
                 * In case filtering type is pyramid, the dimension allocated is larger as border pixels must be accounted for due to 5x5 gaussian filtering.
                 * For each filtering level, a border of 4 pixels must be added to both horizontal and vertical dimensions. Due to 2x scaling, 4 pixels at level n=1,2,..
                 * would correspond to 4*(2^n-1) pixels from the original iamge.. It is assumed that whatever
                 * pitch value srcImagePitch is passed to the testbench already 'includes' the extra 4 pixels per level. However srcImageHeight
                 * represents the ROi's height and is not supposed to include the border pixels and thus the testbench must add these.
                 * */
                if (gConfig_imagePyramid_u8[t].filterType== 0) {
                    sizeInput= gConfig_imagePyramid_u8[t].srcImagePitch*gConfig_imagePyramid_u8[t].srcImageHeight;
                }
                else if (gConfig_imagePyramid_u8[t].filterType== 1) {
                    /* calculate extra borders which is made of 4 pixels per level, which are scaled back to the original image */
                    extraBorders= 0;
                    for (i=0;i<gConfig_imagePyramid_u8[t].numLevels;i++){
                        extraBorders+= (1U<<(uint32_t)i)*4U;
                    }
                    sizeInput= gConfig_imagePyramid_u8[t].srcImagePitch*(gConfig_imagePyramid_u8[t].srcImageHeight + extraBorders);
                }
                input= (uint8_t*)malloc(sizeInput);
                assert(input != NULL);

                /* Allocate output and reference output buffer */
                sizeOutput= 0;
                for(i=0;i<gConfig_imagePyramid_u8[t].numLevels;i++) {
                    sizeOutput += gConfig_imagePyramid_u8[t].dstImagePitch[i]*(gConfig_imagePyramid_u8[t].srcImageHeight>>(i+1));
                }

                /* Reference output is handled differently depending on the filter type
                 * For filterType==0, 2x2 averaging, sizeRefOutput= sizeOutput
                 * For filterType==1, 5x5 gaussian, different handling required
                 * */
                if (gConfig_imagePyramid_u8[t].filterType== 0) {
                    sizeRefOutput= sizeOutput;
                }
                else if (gConfig_imagePyramid_u8[t].filterType== 1) {

                    tempRefBuf= (uint8_t*)malloc(sizeInput);
                    assert(tempRefBuf != NULL);

                    /* Due to border handling, the reference output frames dimensions must have border pixels
                     * for each level
                     */
                    refRoiWidth[0]= (gConfig_imagePyramid_u8[t].srcImageWidth + extraBorders - 4);
                    refRoiHeight[0]= (gConfig_imagePyramid_u8[t].srcImageHeight + extraBorders - 4);
                    refOutputPitch[0]= (gConfig_imagePyramid_u8[t].srcImageWidth + extraBorders - 4)/2;
                    refOutputHeight[0]= (gConfig_imagePyramid_u8[t].srcImageHeight + extraBorders - 4)/2;

                    sizeRefOutput= refOutputPitch[0]*refOutputHeight[0];

                    for (l=1;l<gConfig_imagePyramid_u8[t].numLevels; l++) {
                        refRoiWidth[l]= refRoiWidth[l-1]/2 - 4;
                        refRoiHeight[l]= refRoiHeight[l-1]/2 - 4;
                        refOutputPitch[l]= (refOutputPitch[l-1] - 4)/2;
                        refOutputHeight[l]= (refOutputHeight[l-1] - 4)/2;
                        sizeRefOutput += refOutputPitch[l]*refOutputHeight[l];
                    }
                }

                output= (uint8_t*)malloc(sizeOutput);
                assert(output != NULL);

                refOutput= (uint8_t*)malloc(sizeRefOutput);
                assert(refOutput != NULL);

                if (gConfig_imagePyramid_u8[t].pattern== 1) {
                    /* Generate random input data */
                    srand(1);
                    for(i=0; i<sizeInput; i++)
                    {
                        input[i] = rand() % 256;
                    }
                }
                else {
                    sprintf(filepath, "../testvecs/%s", gConfig_imagePyramid_u8[t].inImage);
                    fid= FOPEN(filepath,"rb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }

                    numBytes= FREAD(input, 1, sizeInput, fid);
                    assert(numBytes== sizeInput);
                    FCLOSE(fid);
                }
                /* Zero out both output and reference output arrays */
                memset(output, 0, sizeOutput);
                memset(refOutput, 0, sizeOutput);

                /***********************************************************************************************************************************/

                /*-----------------------------------------------------------------
                            Set buffer descriptor pointers array base
                            -----------------------------------------------------------------*/
                inBufs.bufDesc  = inBufDescList;
                outBufs.bufDesc = outBufDescList;

                inBufs.numBufs   = 1;
                outBufs.numBufs  = 1;

                inBufDescList[0]     = &inBufDesc;
                outBufDescList[0]    = &outBufDesc;

                /*-----------------------------------------------------------------
                            Set algorithm parameters
                            -----------------------------------------------------------------*/
                createParams.visionParams.algParams.size   = sizeof(IMAGE_PYRAMID_U8_TI_CreateParams);
                createParams.visionParams.cacheWriteBack   = NULL;
                createParams.imgFrameWidth                 = gConfig_imagePyramid_u8[t].srcImageWidth;
                createParams.imgFrameHeight                = gConfig_imagePyramid_u8[t].srcImageHeight;
                createParams.numLevels                 = gConfig_imagePyramid_u8[t].numLevels;

                if (gConfig_imagePyramid_u8[t].filterType== 0) {
                    createParams.filterType= IMAGE_PYRAMID_U8_TI_2x2_AVERAGE;
                }
                else if (gConfig_imagePyramid_u8[t].filterType== 1) {
                    createParams.filterType= IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN;
                }
                else {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }
                /*---------------------------------------------------
                           Query alogorithm memory requirement using standard IALG interface
                           -----------------------------------------------------------------*/
               profiler_start();
               numMemRec = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algNumAlloc();
                memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

                status = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algAlloc(
                        (IALG_Params *)(&createParams), NULL, memRec);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

#if ENABLE_TRACES
                TEST_PRINTF("Image Pyramid Applet Create Done\n");
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


                /*-----------------------------------------------------------------
                                    Intialize the algorithm instance with the allocated memory
                                    and user create parameters
                                    -----------------------------------------------------------------*/
                status = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                        memRec,NULL,(IALG_Params *)(&createParams));


                handle = (IM_Fxns *) memRec[0].base;

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }
                profiler_end_print(0);

#if ENABLE_TRACES
                TEST_PRINTF("Image pyramid Init Done\n");
#endif


                inArgs.subFrameInfo = 0;
                inArgs.size                  = sizeof(IVISION_InArgs);

                inBufDesc.numPlanes                          = 1;

                if (createParams.filterType== IMAGE_PYRAMID_U8_TI_2x2_AVERAGE){
                    inBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
                    inBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
                } /* For the Gaussian filtering case, ROI is shifted such that border pixels that extend out of the ROI are "captured" during filtering */
                else if (createParams.filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN){
                    inBufDesc.bufPlanes[0].frameROI.topLeft.x    = extraBorders/2;
                    inBufDesc.bufPlanes[0].frameROI.topLeft.y    = extraBorders/2;
                }

                /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
                 * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
                 * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
                 * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
                 * at (frameROI.topLeft.x, frameROI.topLeft.y) .
                 * */
                inBufDesc.bufPlanes[0].width                 = gConfig_imagePyramid_u8[t].srcImagePitch;
                inBufDesc.bufPlanes[0].height                = gConfig_imagePyramid_u8[t].srcImageHeight;
                if (createParams.filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN){
                    inBufDesc.bufPlanes[0].height+= createParams.numLevels*4;
                }
                inBufDesc.bufPlanes[0].frameROI.width        = gConfig_imagePyramid_u8[t].srcImageWidth;
                inBufDesc.bufPlanes[0].frameROI.height       = gConfig_imagePyramid_u8[t].srcImageHeight;

                inBufDesc.bufPlanes[0].buf = (uint8_t * )input ;

                if(inBufDesc.bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                outBufDesc.numPlanes                          = createParams.numLevels;

                outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
                outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
                outBufDesc.bufPlanes[0].width                 = gConfig_imagePyramid_u8[t].dstImagePitch[0];
                outBufDesc.bufPlanes[0].height                = gConfig_imagePyramid_u8[t].srcImageHeight>>1;
                outBufDesc.bufPlanes[0].frameROI.width        = gConfig_imagePyramid_u8[t].srcImageWidth>>1;
                outBufDesc.bufPlanes[0].frameROI.height       = gConfig_imagePyramid_u8[t].srcImageHeight>>1;
                outBufDesc.bufPlanes[0].buf = (uint16_t * )output;

                /* Initialize destination pointers for subsequent levels */
                for(l=1;l<createParams.numLevels; l++) {
                    outBufDesc.bufPlanes[l].frameROI.topLeft.x    = 0;
                    outBufDesc.bufPlanes[l].frameROI.topLeft.y    = 0;
                    outBufDesc.bufPlanes[l].buf= (uint8_t*)outBufDesc.bufPlanes[l-1].buf + outBufDesc.bufPlanes[l-1].width*outBufDesc.bufPlanes[l-1].height;
                    outBufDesc.bufPlanes[l].width= gConfig_imagePyramid_u8[t].dstImagePitch[l];
                    outBufDesc.bufPlanes[l].height= outBufDesc.bufPlanes[l-1].height>>1;
                    outBufDesc.bufPlanes[l].frameROI.width        = outBufDesc.bufPlanes[l-1].frameROI.width>>1;
                    outBufDesc.bufPlanes[l].frameROI.height       = outBufDesc.bufPlanes[l-1].frameROI.height>>1;
                }

#if ENABLE_TRACES
                TEST_PRINTF("Processing Start\n");
#endif
                profiler_start();
                status = handle->ivision->algProcess((IVISION_Handle)handle,
                        &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

                profiler_end_print(1);
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
                memset(output, 0, sizeof(output));
                vcop_minit();
                wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
                memset(wbufToZero, 0, 31*1024);
                vcop_free(wbufToZero);

                status = handle->ivision->algProcess((IVISION_Handle)handle,
                        &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

                /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                /*  Call the natural C implementation for block average2x2 which results will be used to validate EVELIB_imagePyramid_u8_execute()'s output            */
                /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                if (createParams.filterType== IMAGE_PYRAMID_U8_TI_2x2_AVERAGE) {
                    vcop_blockAverage2x2_uchar_cn(
                            input,
                            refOutput,
                            inBufDesc.bufPlanes[0].width,
                            outBufDesc.bufPlanes[0].width,
                            inBufDesc.bufPlanes[0].frameROI.width,
                            inBufDesc.bufPlanes[0].frameROI.height);

                    curRefOutput= refOutput;

                    for(l=1;l<createParams.numLevels; l++) {
                        vcop_blockAverage2x2_uchar_cn(
                                curRefOutput,
                                curRefOutput + outBufDesc.bufPlanes[l-1].width*(inBufDesc.bufPlanes[0].frameROI.height>>l),
                                outBufDesc.bufPlanes[l-1].width,
                                outBufDesc.bufPlanes[l].width,
                                inBufDesc.bufPlanes[0].frameROI.width>>l,
                                inBufDesc.bufPlanes[0].frameROI.height>>l);

                        curRefOutput= curRefOutput + outBufDesc.bufPlanes[l-1].width*(inBufDesc.bufPlanes[0].frameROI.height>>l);
                    }
                }else if (createParams.filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN) {

                    vcop_gauss5x5PyramidKernel_8_horiz_c(
                            input,     /* pIn */
                            tempRefBuf, /* pB */
                            refRoiWidth[0], /* width */
                            refRoiHeight[0] + 4,    /* height */
                            inBufDesc.bufPlanes[0].width,                              /* inPitch */
                            refRoiWidth[0] /* outPitch */
                    );

                    vcop_gauss5x5PyramidKernel_8_vert_c(
                            tempRefBuf,
                            refOutput,
                            refRoiWidth[0], /* width */
                            refRoiHeight[0],    /* height */
                            refRoiWidth[0], /* in Pitch */
                            refOutputPitch[0] /* out pitch */
                    );

                    curRefOutput= refOutput;

                    for(l=1;l<createParams.numLevels; l++) {

                        vcop_gauss5x5PyramidKernel_8_horiz_c(
                                curRefOutput, /* pIn */
                                tempRefBuf, /* pB */
                                refRoiWidth[l], /* width */
                                refRoiHeight[l] + 4, /* height */
                                refOutputPitch[l-1],/* in pitch */
                                refRoiWidth[l]/* out pitch */
                        );

                        vcop_gauss5x5PyramidKernel_8_vert_c(
                                tempRefBuf, /*pB */
                                curRefOutput + refOutputPitch[l-1]*refOutputHeight[l-1],
                                refRoiWidth[l], /* width */
                                refRoiHeight[l],  /* height */
                                refRoiWidth[l], /* in pitch */
                                refOutputPitch[l] /* out pitch */
                        );

                        curRefOutput= curRefOutput + refOutputPitch[l-1]*refOutputHeight[l-1];
                    }
                }

                fail = 0;

                if (createParams.filterType== IMAGE_PYRAMID_U8_TI_2x2_AVERAGE) {
                    for(i=0; i<inBufDesc.bufPlanes[0].frameROI.height/2; i++)
                    {
                        for(j=0; j<inBufDesc.bufPlanes[0].frameROI.width/2; j++)
                        {
                            if(output[i*outBufDesc.bufPlanes[0].width+j] != refOutput[i*outBufDesc.bufPlanes[0].width+j])
                            {
                                fail = 1;
                                TEST_PRINTF("level:0, row:%d, col:%d, out:%u, EOut:%u \n", i, j, output[i*outBufDesc.bufPlanes[0].width+j], refOutput[i*outBufDesc.bufPlanes[0].width+j]);
                                break;
                            }
                        }
                    }

                    curRefOutput= refOutput + outBufDesc.bufPlanes[0].width*(inBufDesc.bufPlanes[0].frameROI.height>>1);

                    for(l=1;l<createParams.numLevels; l++) {

                        for(i=0; i<inBufDesc.bufPlanes[0].frameROI.height>>(l+1); i++)
                        {
                            for(j=0; j<inBufDesc.bufPlanes[0].frameROI.width>>(l+1); j++)
                            {
                                if(*((uint8_t*)outBufDesc.bufPlanes[l].buf + i*outBufDesc.bufPlanes[l].width+j) != curRefOutput[i*outBufDesc.bufPlanes[l].width+j])
                                {
                                    fail = 1;
                                    TEST_PRINTF("level:%d, row:%d, col:%d, out:%u, EOut:%u \n", l, i, j, *((uint8_t*)outBufDesc.bufPlanes[l].buf + i*outBufDesc.bufPlanes[l].width+j), curRefOutput[i*outBufDesc.bufPlanes[l].width+j]);
                                    break;
                                }
                            }
                        }

                        curRefOutput= curRefOutput + outBufDesc.bufPlanes[l].width*(inBufDesc.bufPlanes[0].frameROI.height>>(l+1));

                    }
                }
                else if (createParams.filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN) {

                    offsetX= (refOutputPitch[0] - inBufDesc.bufPlanes[0].frameROI.width/2)/2;
                    offsetY= (refOutputHeight[0] - inBufDesc.bufPlanes[0].frameROI.height/2)/2;

                    for(i=0; i<inBufDesc.bufPlanes[0].frameROI.height/2; i++)
                    {
                        for(j=0; j<inBufDesc.bufPlanes[0].frameROI.width/2; j++)
                        {
                            if(output[i*outBufDesc.bufPlanes[0].width+j] != refOutput[(i + offsetY)*refOutputPitch[0]+j+offsetX])
                            {
                                fail = 1;
                                TEST_PRINTF("level:0, row:%d, col:%d, out:%u, EOut:%u \n", i, j, output[i*outBufDesc.bufPlanes[0].width+j], refOutput[(i + offsetY)*refOutputPitch[0]+j+offsetX]);
                                break;
                            }
                        }
                    }

                    curRefOutput= refOutput + refOutputPitch[0]*refOutputHeight[0];

                    for(l=1;l<createParams.numLevels; l++) {

                        offsetX= (refOutputPitch[l] - (inBufDesc.bufPlanes[0].frameROI.width>>(l+1)))/2;
                        offsetY= (refOutputHeight[l] - (inBufDesc.bufPlanes[0].frameROI.height>>(l+1)))/2;

                        for(i=0; i<inBufDesc.bufPlanes[0].frameROI.height>>(l+1); i++)
                        {
                            for(j=0; j<inBufDesc.bufPlanes[0].frameROI.width>>(l+1); j++)
                            {
                                if(*((uint8_t*)outBufDesc.bufPlanes[l].buf + i*outBufDesc.bufPlanes[l].width+j) != curRefOutput[(i + offsetY)*refOutputPitch[l]+j+offsetX])
                                {
                                    fail = 1;
                                    TEST_PRINTF("level:%d, row:%d, col:%d, out:%u, EOut:%u \n", l, i, j, *((uint8_t*)outBufDesc.bufPlanes[l].buf + i*outBufDesc.bufPlanes[l].width+j), curRefOutput[(i + offsetY)*refOutputPitch[0]+j+offsetX]);
                                    break;
                                }
                            }
                        }

                        curRefOutput= curRefOutput + refOutputPitch[l]*refOutputHeight[l];
                    }

                }

                fflush(stdout);
                profiler_printStatus(fail);

                result= (int32_t)((uint32_t)result & (uint32_t)fail);

                fflush(stdout);

                if (gConfig_imagePyramid_u8[t].pattern== 0) {
                    /* Write output files */
                    for(l=0;l<createParams.numLevels; l++) {
                        sprintf(filepath, "../testvecs/%s", gConfig_imagePyramid_u8[t].outImage[l]);
                        fid= FOPEN(filepath,"wb");
                        if (fid==NULL) {
                            printf("Error, unable to open file %s \n", filepath);
                            goto EXIT_LOOP;
                        }

                        numBytes= FWRITE(outBufDesc.bufPlanes[l].buf, 1, outBufDesc.bufPlanes[l].width*(inBufDesc.bufPlanes[0].frameROI.height>>(l+1)), fid);
                        FCLOSE(fid);
                    }
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

                if ( output != NULL)
                {
                    free(output);
                }

                if (input != NULL)
                {
                    free(input);
                }

                if(refOutput != NULL)
                {
                    free(refOutput);
                }

                if (createParams.filterType== IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN) {

                    if(tempRefBuf != NULL)
                    {
                        free(tempRefBuf);
                    }
                }

#ifdef SCAN_DIM
                gConfig_imagePyramid_u8[t].srcImageWidth -= 16;
                notEven= 0;
                for (i= 0; i< createParams.numLevels;i ++) {
                    if (((gConfig_imagePyramid_u8[t].srcImageWidth >> i) & 1)) {
                        notEven= 1;
                        break;
                    }
                }

                while (notEven) {
                    gConfig_imagePyramid_u8[t].srcImageWidth -= 16;

                    notEven= 0;
                    for (i= 0; i< createParams.numLevels;i ++) {
                        if (((gConfig_imagePyramid_u8[t].srcImageWidth >> i) & 1)) {
                            notEven= 1;
                            break;
                        }
                    }
                }

            }

            gConfig_imagePyramid_u8[t].srcImageWidth= initialWidth;

            gConfig_imagePyramid_u8[t].srcImageHeight -= 2;
            notEven= 0;
            for (i= 0; i< createParams.numLevels;i ++) {
                if (((gConfig_imagePyramid_u8[t].srcImageHeight >> i) & 1)) {
                    notEven= 1;
                    break;
                }
            }

            while (notEven) {
                gConfig_imagePyramid_u8[t].srcImageHeight -= 2;

                notEven= 0;
                for (i= 0; i< createParams.numLevels;i ++) {
                    if (((gConfig_imagePyramid_u8[t].srcImageHeight >> i) & 1)) {
                        notEven= 1;
                        break;
                    }
                }
            }
        }
#endif
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();

#endif
    return result;
}

static char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int main(int argc, char *argv[])
{
  int32_t         status = 0;
  TI_FILE        *fp;
  int8_t         *LinePtr;
  int32_t         lineNum = -1;
  int32_t         config_cmd;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[FILE_NAME_SIZE]={0};
  char configParam[FILE_NAME_SIZE]={0};
 
  report_printAppletInfo((int8_t *)"IMAGE_PYRAMID_U8_TI_VISION");

  if (argc > 1)
  {
      strcpy(configFile, argv[1]) ;
  }
  else
  {
      strcpy(configFile,"../testvecs/config/imagePyramid_u8.cfg");
  }

  fp = FOPEN((char *)configFile , "r");

  while(1)
  {
    memset(configLine, 0, FILE_NAME_SIZE);
    status = (int)FGETS(configLine,FILE_NAME_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
      break;
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);
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
      LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFile);
      printf("Processing config file %s !\n", configFile);
      status = readparamfile((char *)configFile, &gsTokenMap_imagePyramid_u8[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      
      profiler_testCaseInfo((int8_t *)gConfig_imagePyramid_u8[0].testCaseName,(int8_t *)gConfig_imagePyramid_u8[0].testCaseDesc,gConfig_imagePyramid_u8[0].performanceTestcase);
      printparams(&gsTokenMap_imagePyramid_u8[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(&gConfig_imagePyramid_u8[0]),sizeof(simagePyramid_u8_Config)) ;


      /* Validate the applet */
      status = test_imagePyramid_u8();
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  FCLOSE(fp);


  return status;
}
