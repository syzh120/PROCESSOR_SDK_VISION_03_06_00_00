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


/** @file evelib_harrisCornerDetection32_test.c
 *
 *  @brief  This file contains test code for harris corner detection
 *
 *
 *  @date   28 Nov 2013
 *
 *  Description
 *    This file contains test code to validate the frame level applet of harris corner detection
 *    It also checks the output against c reference
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
#include "iHarrisCornerDetection32_ti.h"
#include "../vlib/vcop_vec_gradients_xy_and_magnitude/inc/vcop_vec_gradients_xy_and_magnitude_c.h"
#include "../vlib/vcop_harrisScore_32_7x7/inc/vcop_harrisScore_32_7x7_cn.h"
#include "../vlib/vcop_nonMaxSuppress_mxn_S32/inc/vcop_nonMaxSuppress_mxn_32s_c.h"
#include "../vlib/vcop_generateList/inc/vcop_generateList_c.h"
#include "evelib_harrisCornerDetection32_config.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

/* Raster scan checking of the list of coordinate points will produce false negative (errors when there isn't actually any) in case the actual number of
 * detected corners exceed the maximum of corners allowable, which is set by EVELIB_HARRISCORNER_MAX_NUM_CORNERS.
 * So it is better to leave it disabled. The default mode of checking the list of coordinates will work fine.
 */
/* #define _RASTER_SCAN_CHECKING */


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

/***** Start of declarations of function prototypes for the natural C code used to generate the reference output *****/
void allocateNatCBuffers(
        int16_t **refGradX, int16_t **refGradY,
        int16_t **refGradMag, int32_t **refHarrisScore,
        uint8_t **refOutput,
        uint16_t **refOutXY,
        uint32_t dstImagePitch, uint16_t maxNumCorners,
        uint16_t testIndex,
        uint8_t  blockSize,
        uint8_t  totalBorderRequired);

void harrisCornerDetectionNatc(
        uint8_t *input,
        int16_t *refGradX, int16_t *refGradY,
        int16_t *refGradMag, int32_t *refHarrisScore,
        uint8_t *refOutput,
        uint16_t *refOutXY,
        uint16_t maxNumCorners,
        uint16_t testIndex,
        uint8_t  outputFormat,
        uint8_t  harrisWindowSize,
        uint8_t  nmsWindowSize,
        uint8_t  harrisScoreMethod);

void generateListfromBlockNatc(uint32_t imageWidth,
                                    uint32_t imageHeight,
                                    uint16_t outputBlockWidth,
                                    uint16_t outputBlockHeight,
                                    uint16_t maxNumCorners,
                                    uint8_t* refOutput,
                                    uint16_t *refOutXY,
                                    uint16_t *refNumCornersDetected,
                                    uint32_t srcPitch,
                                    uint8_t qShift,
                                    uint8_t totalBorder);

void freeNatCBuffers(int16_t *refGradX, int16_t *refGradY, int16_t *refGradMag, int32_t *refHarrisScore, uint8_t* refOutput, uint16_t *refOutXY);

/***** End of declarations of function prototypes for the natural C code used to generate the reference output *****/
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

int test_harrisCornerDetection32(void)
{
    uint32_t i=0;
    int32_t result = 0;
#ifdef SCAN_DIM
    int notEven= 0, initialWidth= 0;
#endif

    uint8_t *vcopBufToZero;
    uint32_t sizeOutput, sizeInput, numBytes;
    char filepath[256];
    TI_FILE *fid;
    uint32_t t;
    int16_t *refGradX, *refGradY, *refGradMag;
    int32_t *refHarrisScore;
    uint16_t refNumCornersDetected;
    uint32_t dstImagePitch;
    uint16_t maxNumCorners;
    HARRIS_CORNER_DETECTION_32_TI_ControlInParams ctlInParams;
    HARRIS_CORNER_DETECTION_32_TI_ControlOutParams ctlOutParams;
    IALG_Cmd cmd;

    uint8_t *input;
    uint8_t *output;
    uint16_t *outXY, *refOutXY;

    uint8_t *refOutput;
    int fail = 0;

    int32_t numMemRec;
    IALG_MemRec *memRec;
    int32_t status;

    /*-----------------------------------------------------------------
          Pointer to algorithm instance
          -----------------------------------------------------------------*/
    IM_Fxns *     handle= NULL;

    /*-----------------------------------------------------------------
          Algorithm parameters memory in stack
          -----------------------------------------------------------------*/
    HARRIS_CORNER_DETECTION_32_TI_CreateParams  createParams;

    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    /*-----------------------------------------------------------------
          For test purpose it is allocated in stack. Application may get
          this descriptors from its buffer manager
          -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc;
    IVISION_BufDesc   *inBufDescList[1];

    HARRIS_CORNER_DETECTION_32_TI_outArgs   outArgs;
    IVISION_OutBufs                  outBufs;
    /*-----------------------------------------------------------------
          For test purpose it is allocated in stack. Application may get
          this descriptors from its buffer manager
          -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc;
    IVISION_BufDesc   *outBufDescList[1];

    outArgs.iVisionOutArgs.size = sizeof(HARRIS_CORNER_DETECTION_32_TI_outArgs);

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t *pDmem;
    TIMemHandle memHdl_DMEM;

    uint8_t totalBorderRequired;
    uint8_t gradientBorder;
    uint8_t harrisBorder;
    uint8_t nmsBorder;
    uint8_t nmsWindowSize;
    uint8_t harrisWindowSize;

    pDmem = (uint8_t *)&DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;
    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);


    /* In order to derive stack requirements, call profiler_initStack() which will write DEADBEEF from current stack pointer up to the top */
    profiler_initStack(profiler_getSP());

    t=0;

        /*-----------------------------------------------------------------
        Set algorithm parameters
        -----------------------------------------------------------------*/
    createParams.visionParams.algParams.size   = sizeof(HARRIS_CORNER_DETECTION_32_TI_CreateParams);
    createParams.visionParams.cacheWriteBack   = NULL;
    createParams.imgFrameWidth                 = gConfig_harrisCornerDetection32[t].srcImageWidth;
    createParams.imgFrameHeight                = gConfig_harrisCornerDetection32[t].srcImageHeight;
    createParams.maxNumCorners                 = HARRIS_CORNER_DETECTION_MAX_NUM_CORNERS;
    createParams.harrisScoreScalingFactor      =gConfig_harrisCornerDetection32[t].harrisScaling;
    createParams.nmsThresh                     =gConfig_harrisCornerDetection32[t].nmsThresh;
    createParams.qShift                        =gConfig_harrisCornerDetection32[t].qShift;
    createParams.outputFormat                  = gConfig_harrisCornerDetection32[t].outputFormat;
    createParams.harrisScoreMethod             = gConfig_harrisCornerDetection32[t].harrisScoreMethod;
    createParams.harrisWindowSize              = gConfig_harrisCornerDetection32[t].harrisWindowSize;
    createParams.suppressionMethod             = gConfig_harrisCornerDetection32[t].suppressionMethod;

    switch (createParams.harrisWindowSize)
    {
      case HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_7x7:
            harrisWindowSize = 7;
            break;
      case HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_5x5:
            harrisWindowSize = 5;
            break;
      case HARRIS_CORNER_DETECTION_32_TI_HARRIS_WINDOW_3x3:
            harrisWindowSize = 3;
            break;
      default:
            harrisWindowSize = 7;
    }

    switch (createParams.suppressionMethod)
    {
      case HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS3x3:
            nmsWindowSize = 3;
            break;
      case HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS5x5:
            nmsWindowSize = 7;
            break;
      case HARRIS_CORNER_DETECTION_32_TI_SUPPRESSION_METHOD_NMS7x7:
            nmsWindowSize = 7;
            break;
      default:
            nmsWindowSize = 7;
    }

    gradientBorder = GRAD_FILTER_SZ - 1U;

    harrisBorder  = harrisWindowSize - 1;

    nmsBorder      = nmsWindowSize - 1;

    totalBorderRequired = gradientBorder + harrisBorder + nmsBorder;



        /* Allocate input frame buffer */
        sizeInput= gConfig_harrisCornerDetection32[t].srcImagePitch*(gConfig_harrisCornerDetection32[t].srcImageHeight + totalBorderRequired);
        input= (uint8_t*)malloc(sizeInput);
        assert(input != NULL);

        dstImagePitch= gConfig_harrisCornerDetection32[t].dstImagePitch;
        maxNumCorners= HARRIS_CORNER_DETECTION_MAX_NUM_CORNERS;

#ifdef _ONLY_GRAD_OUTPUT
        dstImagePitch*= sizeof(int16_t);
#elif  defined(_ONLY_HARRIS_OUTPUT)
        dstImagePitch*= sizeof(int32_t);
#endif
        sizeOutput= dstImagePitch*gConfig_harrisCornerDetection32[t].srcImageHeight;
        output= (uint8_t*)malloc(sizeOutput);
        assert(output != NULL);

        /* Allocate output frame buffer to store natural C function's X coordinates output */
        outXY= (uint16_t*)malloc(2*maxNumCorners*sizeof(uint16_t)); /* +1 because we append the number of detected corners as the first element of the list */
        assert(outXY != NULL);
        memset(outXY, 0, 2*maxNumCorners*sizeof(uint16_t));

        /* Allocate buffers used by natural C code, only necessary for validation against natural-C code */
        allocateNatCBuffers(&refGradX,
                            &refGradY,
                            &refGradMag,
                            &refHarrisScore,
                            &refOutput,
                            &refOutXY,
                            dstImagePitch,
                            maxNumCorners,
                            t,
                            harrisWindowSize,
                            totalBorderRequired);

        if (gConfig_harrisCornerDetection32[t].pattern== 1) {
            /* Generate random input data */
            srand(1);
            for(i=0; i<sizeInput; i++) /*/4 is because size was in bytes where as i will iterates over uitn32_t */
            {
                input[i] = (uint32_t)abs(rand()) & 0xFFU;
            }
        }
        else {
            sprintf(filepath, "../testvecs/%s", gConfig_harrisCornerDetection32[t].inImage);
            fid= FOPEN(filepath,"rb");
            if (fid==NULL) {
                printf("Error, unable to open file %s \n", filepath);
                goto EXIT_LOOP;
            }

            numBytes= FREAD(input, 1, gConfig_harrisCornerDetection32[t].srcImagePitch*gConfig_harrisCornerDetection32[t].srcImageHeight, fid);
            assert(numBytes== gConfig_harrisCornerDetection32[t].srcImagePitch*gConfig_harrisCornerDetection32[t].srcImageHeight);
            FCLOSE(fid);
        }
        /* Zero out both output and reference output arrays */
        memset(output, 0, sizeOutput);
        memset(refOutput, 0, sizeOutput);
        profiler_init();
        profiler_initStack(profiler_getSP());
        profiler_start();

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


        /*---------------------------------------------------
           Query alogorithm memory requirement using standard IALG interface
           -----------------------------------------------------------------*/
        numMemRec = HARRIS_CORNER_DETECTION_32_TI_VISION_FXNS.ialg.algNumAlloc();
        memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

        status = HARRIS_CORNER_DETECTION_32_TI_VISION_FXNS.ialg.algAlloc(
                (IALG_Params *)(&createParams), NULL, memRec);

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

#if ENABLE_TRACES
        TEST_PRINTF("Harris Corner Detection Applet Create Done\n");
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
        status = HARRIS_CORNER_DETECTION_32_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                memRec,NULL,(IALG_Params *)(&createParams));

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        handle = (IM_Fxns *) memRec[0].base;

        profiler_end_print(0);
#if ENABLE_TRACES
        TEST_PRINTF("Harris Corner 32-bits detection Applet Init Done\n");
#endif


        inArgs.subFrameInfo = 0;
        inArgs.size                  = sizeof(IVISION_InArgs);

        inBufDesc.numPlanes                          = 1;
        /* ROI is shifted such that border pixels that extend out of the ROI are "captured" during filtering */
        inBufDesc.bufPlanes[0].frameROI.topLeft.x    = totalBorderRequired/2;
        inBufDesc.bufPlanes[0].frameROI.topLeft.y    = totalBorderRequired/2;

        /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
         * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
         * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
         * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
         * at (frameROI.topLeft.x, frameROI.topLeft.y) .
         * */
        inBufDesc.bufPlanes[0].width                 = gConfig_harrisCornerDetection32[t].srcImagePitch;
        inBufDesc.bufPlanes[0].height                = gConfig_harrisCornerDetection32[t].srcImageHeight + totalBorderRequired;
        inBufDesc.bufPlanes[0].frameROI.width        = gConfig_harrisCornerDetection32[t].srcImageWidth;
        inBufDesc.bufPlanes[0].frameROI.height       = gConfig_harrisCornerDetection32[t].srcImageHeight;

        inBufDesc.bufPlanes[0].buf = (uint8_t * )input ;

        if(inBufDesc.bufPlanes[0].buf == NULL)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

#if defined(_ONLY_GRAD_OUTPUT) || defined(_ONLY_HARRIS_OUTPUT) || defined(_ONLY_NMS_OUTPUT)

        outBufDesc.numPlanes                          = 1;

        outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
#ifdef _ONLY_NMS_OUTPUT
        outBufDesc.bufPlanes[0].width                 = gConfig_harrisCornerDetection32[t].dstImagePitch;
#elif defined(_ONLY_HARRIS_OUTPUT)
        outBufDesc.bufPlanes[0].width                 = gConfig_harrisCornerDetection32[t].dstImagePitch*sizeof(uint32_t);
#else
        outBufDesc.bufPlanes[0].width                 = gConfig_harrisCornerDetection32[t].dstImagePitch*sizeof(uint16_t);
#endif
        outBufDesc.bufPlanes[0].height                = gConfig_harrisCornerDetection32[t].srcImageHeight;
        outBufDesc.bufPlanes[0].frameROI.width        = gConfig_harrisCornerDetection32[t].srcImageWidth*sizeof(uint16_t);
        outBufDesc.bufPlanes[0].frameROI.height       = gConfig_harrisCornerDetection32[t].srcImageHeight;
        outBufDesc.bufPlanes[0].buf = (uint8_t *)output;

        if(outBufDesc.bufPlanes[0].buf == NULL)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

#else

        outBufDesc.numPlanes                          = 1;

        outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
        if ( createParams.outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST)
        {
          outBufDesc.bufPlanes[0].width                 = 2*createParams.maxNumCorners*sizeof(uint16_t);
          outBufDesc.bufPlanes[0].height                = 1;
          outBufDesc.bufPlanes[0].frameROI.width        = 2*createParams.maxNumCorners*sizeof(uint16_t);
          outBufDesc.bufPlanes[0].frameROI.height       = 1;
          outBufDesc.bufPlanes[0].buf = (uint16_t * )outXY;
        }
        else
        {
          outBufDesc.bufPlanes[0].width                 = gConfig_harrisCornerDetection32[t].dstImagePitch;
          outBufDesc.bufPlanes[0].height                = 1;
          outBufDesc.bufPlanes[0].frameROI.width        = gConfig_harrisCornerDetection32[t].srcImageWidth / 8;
          outBufDesc.bufPlanes[0].frameROI.height       = gConfig_harrisCornerDetection32[t].srcImageHeight;
          outBufDesc.bufPlanes[0].buf = (uint16_t * )output;
        }

        if(outBufDesc.bufPlanes[0].buf == NULL)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
#endif

        /* Use control API to change the NMS threshold */

        /* For testing purpose, first we get the current NMS threshold value */
        ctlInParams.algParams.size= sizeof(HARRIS_CORNER_DETECTION_32_TI_ControlInParams);
        ctlOutParams.algParams.size= sizeof(HARRIS_CORNER_DETECTION_32_TI_ControlOutParams);

        cmd= HARRIS_CORNER_DETECTION_GET_THRESHOLD;
        status = handle->ivision->algControl((IVISION_Handle)handle, cmd, (const IALG_Params *)&ctlInParams, (IALG_Params *)&ctlOutParams);

        /* For testing, we then set the new NMS threshold value to half of the current value */
        cmd= HARRIS_CORNER_DETECTION_SET_THRESHOLD;
        ctlInParams.nmsThreshold= ctlOutParams.nmsThreshold/2;
        status = handle->ivision->algControl((IVISION_Handle)handle, cmd, (const IALG_Params *)&ctlInParams, (IALG_Params *)&ctlOutParams);

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

#if ENABLE_TRACES
        TEST_PRINTF("Processing Start\n");
#endif
        profiler_start();
        /* After the call, the result of the process function should be wrong since we messed with the threshold value earlier but it was for testing purpose */
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


        /* Erase output and vcop bufs after first call to test repeatabiity
         * */
        memset(output, 0, sizeOutput);
        memset(outXY, 0, 2*maxNumCorners*sizeof(uint16_t));

#if !(VCOP_HOST_EMULATION)
        /* * wmem contains param registers and constant so erasing it will test the context saving and restore capability of the function
         */
        vcop_minit();
        vcopBufToZero= (uint8_t *)vcop_malloc(VCOP_WMEM, 31*1024);
        assert(vcopBufToZero!=NULL);
        memset(vcopBufToZero, 0, 31*1024);
        vcop_free(vcopBufToZero);

        /* * It is good to erase all image buffers as well. Especially in this case, the function only outputs once the content of the image buffer
         * at the end of the frame. So if we don't erase the image buffer, the correct output still exists in the memory and will be written out
         * even though we erased the wmem.
         */
        vcop_minit();
        vcopBufToZero= (uint8_t *)vcop_malloc(VCOP_IBUFLA, 15*1024);
        assert(((uint32_t)vcopBufToZero & 0xFFFFFF00)!=NULL);
        memset(vcopBufToZero, 0, 15*1024);
        vcop_free(vcopBufToZero);

        vcop_minit();
        vcopBufToZero= (uint8_t*)vcop_malloc(VCOP_IBUFHA, 8*1024);
        assert(((uint32_t)vcopBufToZero & 0xFFFFFF00)!=NULL);
        memset(vcopBufToZero, 0, 15*1024);
        vcop_free(vcopBufToZero);

        vcop_minit();
        vcopBufToZero= (uint8_t*)vcop_malloc(VCOP_IBUFLB, 15*1024);
        assert(((uint32_t)vcopBufToZero & 0xFFFFFF00)!=NULL);
        memset(vcopBufToZero, 0, 15*1024);
        vcop_free(vcopBufToZero);

        vcop_minit();
        vcopBufToZero= (uint8_t*)vcop_malloc(VCOP_IBUFHB, 8*1024);
        assert(((uint32_t)vcopBufToZero & 0xFFFFFF00)!=NULL);
        memset(vcopBufToZero, 0, 15*1024);
        vcop_free(vcopBufToZero);
#endif
#if ENABLE_TRACES
        TEST_PRINTF("Processing start again \n");
#endif

        /* Since we messed with the NMS threshold value before the first process call, it was for testing purpose
         * we now restore it to its original correct value  */
        cmd= HARRIS_CORNER_DETECTION_SET_THRESHOLD;
        ctlInParams.nmsThreshold= gConfig_harrisCornerDetection32[t].nmsThresh;
        status = handle->ivision->algControl((IVISION_Handle)handle, cmd, (const IALG_Params *)&ctlInParams, (IALG_Params *)&ctlOutParams);

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        status = handle->ivision->algProcess((IVISION_Handle)handle,
                &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
#if ENABLE_TRACES
        TEST_PRINTF("Processing End\n");
#endif

        /* Call reference natural C to generate reference output, first call the function that generates NMS output */
        harrisCornerDetectionNatc(input,
                                  refGradX,
                                  refGradY,
                                  refGradMag,
                                  refHarrisScore,
                                  refOutput,
                                  refOutXY,
                                  maxNumCorners,
                                  t,
                                  createParams.outputFormat,
                                  harrisWindowSize,
                                  nmsWindowSize,
                                  createParams.harrisScoreMethod);

        /* Call second function that does the block to list generation in case we don't debug the gradident, or harris or nms output */
        if ( createParams.outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST )
        {
#if !defined(_ONLY_GRAD_OUTPUT) && !defined(_ONLY_HARRIS_OUTPUT) && !defined(_ONLY_NMS_OUTPUT)
        generateListfromBlockNatc(gConfig_harrisCornerDetection32[t].srcImageWidth,
                                  gConfig_harrisCornerDetection32[t].srcImageHeight,
                                  outArgs.outputBlockWidth,
                                  outArgs.outputBlockHeight,
                                  maxNumCorners,
                                  refOutput,
                                  refOutXY,
                                  &refNumCornersDetected,
                                  gConfig_harrisCornerDetection32[t].srcImageWidth,
                                  gConfig_harrisCornerDetection32[t].qShift,
                                  totalBorderRequired);
#endif
        }
        /* Perform the output validation */
        fail = 0;
#if defined(_ONLY_GRAD_OUTPUT) || defined(_ONLY_HARRIS_OUTPUT) || defined (_ONLY_NMS_OUTPUT)
        {
            int32_t j;
            for(i=0; i<gConfig_harrisCornerDetection32[t].srcImageHeight; i++)
            {
                for(j=0; j<gConfig_harrisCornerDetection32[t].srcImageWidth; j++)
                {
#ifdef _ONLY_GRAD_OUTPUT
                    if(*((int16_t*)output + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j) != *((int16_t*)refOutput + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j))
#elif defined(_ONLY_HARRIS_OUTPUT)
                        if(*((int32_t*)output + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j) != *((int32_t*)refOutput + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j))
#else
                            if(output[i*gConfig_harrisCornerDetection32[t].dstImagePitch+j] != refOutput[i*gConfig_harrisCornerDetection32[t].dstImagePitch+j])
#endif
                            {
                                fail = 1;
#ifdef _ONLY_GRAD_OUTPUT
                                TEST_PRINTF("row:%d, col:%d, out:%d, EOut:%d \n", i, j, *((int16_t*)output + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j), *((int16_t*)refOutput + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j));
#elif defined(_ONLY_HARRIS_OUTPUT)
                                TEST_PRINTF("row:%d, col:%d, out:%u, EOut:%u \n", i, j, *((int32_t*)output + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j), *((int32_t*)refOutput + i*gConfig_harrisCornerDetection32[t].dstImagePitch +j));
#else
                                TEST_PRINTF("row:%d, col:%d, out:%u, EOut:%u \n", i, j, output[i*gConfig_harrisCornerDetection32[t].dstImagePitch+j], refOutput[i*gConfig_harrisCornerDetection32[t].dstImagePitch+j]);
#endif
                            }
                }
            }
        }
#else
        if ( createParams.outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST )
        {

          if (outArgs.numCorners != refNumCornersDetected) {
              TEST_PRINTF("Number of corners detected mismatch, out:%d, Eout: %d !\n", outArgs.numCorners, refNumCornersDetected);
              fail= 1;
          }

          else {
#ifdef _RASTER_SCAN_CHECKING
              uint16_t checksum=0, refChecksum=0;

              for(i=0; i<2*outArgs.numCorners; i++) {
                  checksum= checksum ^ outXY[i];
                  refChecksum= refChecksum ^ refOutXY[i];
              }

              if (checksum != refChecksum)
              {
                  TEST_PRINTF("X,Y coordinates mismatch\n");
                  fail= 1;
              }
#else
              for(i=0; i<2*outArgs.numCorners; i++) {
                  if (outXY[i] != refOutXY[i]) {
                      TEST_PRINTF("X or Y coordinates mismatch at %d, out:%u, Eout:%u \n", i, outXY[i], refOutXY[i]);
                      fail= 1;
                  }
              }
#endif
          }
        }
        else
        {
          int i, j;

          uint8_t * targetPtr = (uint8_t *) outBufDesc.bufPlanes[0].buf;
          uint8_t * refPtr = (uint8_t *) refOutput;

          for(i=0; i<gConfig_harrisCornerDetection32[t].srcImageHeight; i++)
          {
              for(j=0; j < gConfig_harrisCornerDetection32[t].srcImageWidth/ 8; j++)
              {

                if ( targetPtr[ j + i * gConfig_harrisCornerDetection32[t].dstImagePitch ] != refPtr[j + i * gConfig_harrisCornerDetection32[t].dstImagePitch])
                {
                  TEST_PRINTF("output mismatch at , %d, %d \n", j, i);
                  fail= 1;
                }

              }
          }

        }

#endif
        fflush(stdout);
        profiler_printStatus(fail);

        result= (int32_t)((uint32_t)result & (uint32_t)fail);

        fflush(stdout);

        if (gConfig_harrisCornerDetection32[t].pattern== 0) {
            /* Write output files */
            sprintf(filepath, "../testvecs/%s", gConfig_harrisCornerDetection32[t].outImage);
            fid= FOPEN(filepath,"wb");
            if (fid==NULL) {
                printf("Error, unable to open file %s \n", filepath);
                goto EXIT_LOOP;
            }
#if defined(_ONLY_GRAD_OUTPUT) || defined(_ONLY_HARRIS_OUTPUT) || defined (_ONLY_NMS_OUTPUT)
#ifdef _ONLY_NMS_OUTPUT
#define SIZE_OUTELMT 1
#else
#define SIZE_OUTELMT 2
#endif
            numBytes= FWRITE(output, 1, SIZE_OUTELMT*gConfig_harrisCornerDetection32[t].dstImagePitch*gConfig_harrisCornerDetection32[t].srcImageHeight, fid);
#else
            for (i = 0; i < outArgs.numCorners; i++) {
                FPRINTF(fid, "%4.d\t%4.d\n", outXY[2 * i], outXY[2 * i + 1]);
            }
#endif
            FCLOSE(fid);
        }


        EXIT_LOOP:

        freeNatCBuffers(refGradX, refGradY, refGradMag, refHarrisScore, refOutput, refOutXY);

        if (handle!= NULL) {
            status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
            }
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

        if(outXY != NULL)
        {
            free(outXY);
        }
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

  report_printAppletInfo((int8_t *)"HARRIS_CORNER_DETECTION_32_TI_VISION");

  if (argc > 1)
  {
      strcpy(configFile, argv[1]) ;
  }
  else
  {
      strcpy(configFile,"../testvecs/config/config_list.txt");
  }

  fp = FOPEN((char *)configFile , "r");

  while(1)
  {
    memset(gConfig_harrisCornerDetection32, 0, sizeof(gConfig_harrisCornerDetection32));
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
      status = readparamfile((char *)configFile, &gsTokenMap_harrisCornerDetection32[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_harrisCornerDetection32[0].testCaseName,(int8_t *)gConfig_harrisCornerDetection32[0].testCaseDesc,gConfig_harrisCornerDetection32[0].performanceTestcase);
      printparams(&gsTokenMap_harrisCornerDetection32[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(&gConfig_harrisCornerDetection32[0]),sizeof(sharrisCornerDetection32_Config)) ;


      /* Validate the applet */
      status = test_harrisCornerDetection32();
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



void allocateNatCBuffers(
        int16_t **refGradX, int16_t **refGradY,
        int16_t **refGradMag, int32_t **refHarrisScore,
        uint8_t **refOutput,
        uint16_t **refOutXY,
        uint32_t dstImagePitch, uint16_t maxNumCorners,
        uint16_t testIndex,
        uint8_t  blockSize,
        uint8_t  totalBorderRequired) {

    uint32_t imageWidthFinal, imageHeightFinal, imageWidth, imageHeight, dstPitch, sizeGrad, sizeHarris;
    uint32_t sizeOutput= dstImagePitch*gConfig_harrisCornerDetection32[testIndex].srcImageHeight;

#ifdef  _ONLY_HARRIS_OUTPUT
    /* Allocate reference output frame buffer to store natural C function's NMS output */
    *refOutput= (uint8_t*)malloc(sizeOutput*sizeof(uint32_t));
    assert(*refOutput != NULL);
#else
    /* Allocate reference output frame buffer to store natural C function's NMS output */
    *refOutput= (uint8_t*)malloc(sizeOutput*sizeof(uint8_t));
    assert(*refOutput != NULL);
#endif
    /* Allocate reference output frame buffer to store natural C function's X,Y coordinates output */
    *refOutXY= (uint16_t*)malloc(2*maxNumCorners*sizeof(uint16_t));
    assert(*refOutXY != NULL);

    /* Call reference C code first */
    imageWidthFinal= gConfig_harrisCornerDetection32[testIndex].srcImageWidth;
    imageHeightFinal= gConfig_harrisCornerDetection32[testIndex].srcImageHeight;

    imageWidth= imageWidthFinal + totalBorderRequired;
    imageHeight= imageHeightFinal + totalBorderRequired;
    dstPitch= imageWidth - (GRAD_FILTER_SZ-1);

    sizeGrad= sizeof(int16_t)*imageWidth*(imageHeight-2);
#ifdef  _ONLY_GRAD_OUTPUT
    *refGradX= (int16_t*)(*refOutput);
#else
    *refGradX= (int16_t*)malloc(sizeGrad);
    assert(*refGradX!=NULL);
    memset(*refGradX, 0, sizeGrad);
#endif
    *refGradY= (int16_t*)malloc(sizeGrad);
    assert(*refGradY!=NULL);
    memset(*refGradY, 0, sizeGrad);

    *refGradMag= (int16_t*)malloc(sizeGrad);
    assert(*refGradMag!=NULL);
    memset(*refGradMag, 0, sizeGrad);

#ifndef _ONLY_GRAD_OUTPUT
    imageWidth= imageWidth - (GRAD_FILTER_SZ-1);
    imageHeight= imageHeight - (GRAD_FILTER_SZ-1);
    dstPitch= imageWidth - (blockSize - 1);

    sizeHarris= sizeof(int32_t)*dstPitch*(imageHeight - (blockSize - 1));
    /* Allocate output frame buffer */
#ifdef  _ONLY_HARRIS_OUTPUT
    *refHarrisScore= (int32_t*)(*refOutput);
#else
    *refHarrisScore= (int32_t*)malloc(sizeHarris);
    assert(*refHarrisScore!=NULL);
    memset(*refHarrisScore, 0, sizeHarris);
#endif


#endif
}

void harrisCornerDetectionNatc(
        uint8_t *input,
        int16_t *refGradX, int16_t *refGradY,
        int16_t *refGradMag, int32_t *refHarrisScore,
        uint8_t *refOutput,
        uint16_t *refOutXY,
        uint16_t maxNumCorners,
        uint16_t testIndex,
        uint8_t  outputFormat,
        uint8_t  harrisWindowSize,
        uint8_t  nmsWindowSize,
        uint8_t  harrisScoreMethod) {

    uint32_t imageWidthFinal, imageHeightFinal, imageWidth, imageHeight, dstPitch, srcPitch, sizeHarris;

    imageWidthFinal= gConfig_harrisCornerDetection32[testIndex].srcImageWidth;
    imageHeightFinal= gConfig_harrisCornerDetection32[testIndex].srcImageHeight;

    uint8_t totalBorderRequired;
    uint8_t gradientBorder;
    uint8_t harrisBorder;
    uint8_t nmsBorder;

    gradientBorder = GRAD_FILTER_SZ - 1U;

    harrisBorder   = harrisWindowSize - 1 ;

    nmsBorder      = nmsWindowSize - 1;

    totalBorderRequired = gradientBorder + harrisBorder + nmsBorder;

    imageWidth= imageWidthFinal   + totalBorderRequired;
    imageHeight= imageHeightFinal + totalBorderRequired;
    dstPitch= imageWidth - gradientBorder;

    vcop_vec_gradients_xy_and_magnitude_cn2(input,
                                            refGradX,
                                            refGradY,
                                            refGradMag,
                                            imageWidth - gradientBorder,
                                            imageHeight - gradientBorder,
                                            gConfig_harrisCornerDetection32[testIndex].srcImagePitch,
                                            dstPitch);

#ifndef _ONLY_GRAD_OUTPUT
    srcPitch= dstPitch;
    imageWidth= imageWidth   - gradientBorder;
    imageHeight= imageHeight - gradientBorder;
    dstPitch= imageWidth - harrisBorder;

    sizeHarris= sizeof(int32_t)*dstPitch*(imageHeight - harrisBorder);
    /* Allocate output frame buffer */
#ifdef  _ONLY_HARRIS_OUTPUT
    refHarrisScore= (int32_t*)refOutput;
#endif
    memset(refHarrisScore, 0, sizeHarris);

    if ( harrisScoreMethod == HARRIS_CORNER_DETECTION_32_TI_HARRIS_SCORE_METHOD_A )
    {
      vcop_harrisScore_32_7x7_cn
      (
              refGradX,
              refGradY,
              imageWidth,
              imageHeight,
              srcPitch,
              dstPitch,
              harrisWindowSize,
              (int32_t*)refHarrisScore,
              gConfig_harrisCornerDetection32[testIndex].harrisScaling);
    }
    else
    {
      vcop_harrisScore_32_methodB_cn
      (
              refGradX,
              refGradY,
              imageWidth,
              imageHeight,
              srcPitch,
              dstPitch,
              harrisWindowSize,
              (uint32_t *)refHarrisScore);
    }

#ifndef _ONLY_HARRIS_OUTPUT
    srcPitch= dstPitch;
    imageWidth= imageWidth   - harrisBorder;
    imageHeight= imageHeight - harrisBorder;
    dstPitch= gConfig_harrisCornerDetection32[testIndex].dstImagePitch;

    /* For debugging find the maximum value, in order to set the nmsThresh  */
    /*
    {
        maxi= 0;
        for(i=0;i<imageHeight;i++)
            for(j=0;j<imageWidth;j++) {
                if (refHarrisScore[i*srcPitch + j] > maxi)
                    maxi= refHarrisScore[i*srcPitch + j];
            }
    }
     */
    if ( outputFormat == HARRIS_CORNER_DETECTION_32_TI_OUTPUT_FORMAT_LIST )
    {
      vcop_nonMaxSuppress_mxn_32s_cn((int32_t *)refHarrisScore,
                                                refOutput,
                                                imageWidth,
                                                imageHeight,
                                                srcPitch,
                                                dstPitch,
                                                nmsWindowSize,
                                                nmsWindowSize,
                                                gConfig_harrisCornerDetection32[testIndex].nmsThresh);
    }
    else
    {
      vcop_nonMaxSuppress_mxn_32s_bitPack_cn((int32_t *)refHarrisScore,
                                                refOutput,
                                                imageWidth,
                                                imageHeight,
                                                srcPitch,
                                                dstPitch,
                                                nmsWindowSize,
                                                nmsWindowSize,
                                                gConfig_harrisCornerDetection32[testIndex].nmsThresh);
    }

#endif
#endif
}

void freeNatCBuffers(int16_t *refGradX, int16_t *refGradY, int16_t *refGradMag, int32_t *refHarrisScore, uint8_t* refOutput, uint16_t *refOutXY){

#ifndef _ONLY_GRAD_OUTPUT
    free(refHarrisScore);
#endif
    free(refGradX);
    free(refGradY);
    free(refGradMag);

#if !defined(_ONLY_HARRIS_OUTPUT) && !defined(_ONLY_GRAD_OUTPUT)
    free(refOutput);
#endif
    free(refOutXY);
}


void generateListfromBlockNatc(uint32_t imageWidth,
                                    uint32_t imageHeight,
                                    uint16_t outputBlockWidth,
                                    uint16_t outputBlockHeight,
                                    uint16_t maxNumCorners,
                                    uint8_t* refOutput,
                                    uint16_t *refOutXY,
                                    uint16_t *refNumCornersDetected,
                                    uint32_t srcPitch,
                                    uint8_t qShift,
                                    uint8_t totalBorder) {

    uint32_t i,j;
    uint16_t blockX, blockY;

    uint16_t numHorzBlocks;
    uint16_t numVertBlocks;
    uint16_t numFeatures;

    numHorzBlocks= imageWidth/outputBlockWidth;
    numVertBlocks= imageHeight/outputBlockHeight;

    *refNumCornersDetected= 0;
    blockX= 0;
    blockY= 0;

    numFeatures= 0;

#ifdef _RASTER_SCAN_CHECKING

    refNumCornersDetected= 0;
    blockX= 0;
    blockY= 0;

    vcop_generateList_intlv_cn
    (
            refOutput,
            &blockX, /* pointer to X coordinate of the current block processed */
            &blockY, /* pointer to Y coordinate of the current block processed */
            1,   /* number of horizontal blocks in the frame */
            1,   /* number of vertical blocks in the frame */
            refOutXY,
            refNumCornersDetected,
            refNumCornersDetected,
            maxNumCorners,
            imageWidth,
            imageHeight,
            srcPitch,
            qShift,
            totalBorder/2,
            totalBorder/2
    );


#else

    for (i=0;i<numVertBlocks;i++){
        for (j=0;j<numHorzBlocks;j++) {
            numFeatures+= vcop_generateList_intlv_cn
                    (
                            refOutput + (i*outputBlockHeight*srcPitch + j*outputBlockWidth),
                            &blockX, /* pointer to X coordinate of the current block processed */
                            &blockY, /* pointer to Y coordinate of the current block processed */
                            numHorzBlocks,   /* number of horizontal blocks in the frame */
                            numVertBlocks,   /* number of vertical blocks in the frame */
                            refOutXY + 2*numFeatures,
                            refNumCornersDetected,
                            refNumCornersDetected,
                            maxNumCorners,
                            outputBlockWidth,
                            outputBlockHeight,
                            srcPitch,
                            qShift,
                            totalBorder/2,
                            totalBorder/2
                    );
        }
    }
#endif

}

