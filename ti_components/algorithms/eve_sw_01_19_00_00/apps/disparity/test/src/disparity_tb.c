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


/** @file disparity_tb.c
 *
 *  @brief  This file contains test code for disparity calculation applet
 *
 *
 *  @date   24 July 2014
 *
 *  Description
 *    This file contains test code to validate the frame level applet for
 *    hamming-based disparity calculation. It also checks the output against c reference
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
#include "iDisparity_ti.h"
#include "../vlib/vcop_disparity_hammingDistance_row/inc/vcop_disparity_hammingDistance_row_cn.h"
#include "disparity_config.h"
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

#define MIN(a,b) ((a)<(b)?(a):(b))

#define SLICE_HEIGHT 10

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

void vcop_disparity_hammingDistance_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
) {
    if (searchDir== 0) { /* left right */
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_row_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_row_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
    } else {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_row_right_left_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            /* Right-left not implemented for 64 bits hamming distance */
        }
    }
}

void vcop_disparity_hammingDistance_row_right_left_ref_cn(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen
) {
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_row_right_left_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_row_right_left_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }

}

void vcop_disparity_hammingDistance_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
){
    if (searchDir== 0) {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
    }
    else {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_RL_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            /* Right-left not implemented for 64 bits hamming distance */
        }
    }
}

void vcop_disparity_hammingDistance_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
){
    if (searchDir== 0) {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
    }
    else {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_RL_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            /* Right-left not implemented for 64 bits hamming distance */
        }
    }
}


int test_disparity(sdisparity_Config * gConfig_disparity, int testNum)
{
    int i=0, j=0, r= 0, result = 0;
#ifdef SCAN_DIM
    initialWidth= 0;
#endif
    char *statusStr = NULL;
    unsigned int profile_sctm;
    uint8_t *wbufToZero;
    uint32_t sizeDispOutput, sizeDispRLOutput, sizeInputLeft, sizeInputRight, numBytes;
    uint16_t *natC_allCostOutput, *natC_allCostRLOutput;
    DISPARITY_TI_ControlInParams ctlInParams;
    DISPARITY_TI_ControlOutParams ctlOutParams;

    char filepath[256];
    char *dirStr;
    TI_FILE *fid;
    uint32_t t;

    uint8_t inputByteLen;
    uint32_t idx;
    uint8_t *inputLeft, *inputRight;
    uint8_t *dispOutput, *dispRLOutput, *dispRefOutput, *dispRefRLOutput;
    uint16_t *minCostOutput, *minCostRefOutput,*minCostRefRLOutput;
    uint16_t *prevAdjCostOutput, *nextAdjCostOutput, *prevAdjCostRefOutput, *nextAdjCostRefOutput;
    uint16_t *prevAdjCostRefOutputTemp, *nextAdjCostRefOutputTemp;
    uint16_t extraOffset;

    int fail = 0;

    unsigned int profile_tsc, profile_create_tsc;

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
    DISPARITY_TI_CreateParams  createParams;

    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
    -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc[DISPARITY_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *inBufDescList[DISPARITY_TI_BUFDESC_IN_TOTAL];

    DISPARITY_TI_outArgs     outArgs;
    IVISION_OutBufs                  outBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
    -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *outBufDescList[DISPARITY_TI_BUFDESC_OUT_TOTAL];

    outArgs.iVisionOutArgs.size = sizeof(DISPARITY_TI_outArgs);

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

    inBufs.numBufs   = DISPARITY_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = DISPARITY_TI_BUFDESC_OUT_TOTAL;

    for(i = 0 ; i < DISPARITY_TI_BUFDESC_IN_TOTAL ;i++)
    {
        inBufDescList[i]     = &inBufDesc[i];
    }

    for(i = 0 ; i < DISPARITY_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        outBufDescList[i]     = &outBufDesc[i];
    }

    profiler_init();
    /* In order to derive stack requirements, call profiler_initStack() which will write DEADBEEF from current stack pointer up to the top */
    profiler_initStack(profiler_getSP());

    for (t=0;t<disparity_numTestCases;t++) {
#if 0 //#if !(VCOP_HOST_EMULATION)
        /*On target, if the filename contains "host" then we skip the execution of this test case in order to avoid long execution time */
        if (strstr((const char*)gConfig_disparity[t].inImageLeft,"host")!=NULL) {
            continue;
        }
#endif
        /* Enable SCAN_DIM if you want to vary the width and height of the image for each test case
         * This enable wide coverage of the image dimensions to be tested
         *  */
#ifdef SCAN_DIM
        initialWidth= gConfig_disparity[t].srcImageWidth;
        while (gConfig_disparity[t].srcImageHeight >= 64) {
            while (gConfig_disparity[t].srcImageWidth >= 64) {
#endif

                /* The below lines will have to be removed */

                /* Allocate input buffer based on srcImagePitchL and srcImageHeight values.
                 * It is assumed that the pitch value srcImagePitchL passed to the testbench already includes (winWidth - 1) extra pixels.
                 * However srcImageHeight represents the ROi's height and is not supposed to include the border pixels and thus the testbench must add these.
                 * Note that gConfig_disparity[t].srcImagePitchL is expressed in term of bytes whereas gConfig_disparity[t].srcImageWidth is epxressed in term of pixels
                 * */
                inputByteLen= gConfig_disparity[t].inputBitDepth>>3;

                sizeInputLeft= inputByteLen*(gConfig_disparity[t].srcImagePitchL)*(gConfig_disparity[t].srcImageHeight + gConfig_disparity[t].winHeight - 1);
                sizeInputRight= inputByteLen*(gConfig_disparity[t].srcImagePitchR)*(gConfig_disparity[t].srcImageHeight + gConfig_disparity[t].winHeight - 1);

                inputLeft= (uint8_t*)malloc(sizeInputLeft);
                assert(inputLeft != NULL);

                inputRight= (uint8_t*)malloc(sizeInputRight);
                assert(inputRight != NULL);

                /* Allocate output and reference output buffer
                 * Note that gConfig_disparity[t].dstImagePitch is expressed in term of bytes
                 * */
                sizeDispOutput= gConfig_disparity[t].dstImagePitch*gConfig_disparity[t].srcImageHeight;

                /* For computation purpose, size of disparity map generated by right-to-left disparity computation is wider
                 * This is due to the nature of the optimizations implemented to derive right-to-left disparities from left-to-right disparities */
                sizeDispRLOutput= (gConfig_disparity[t].dstImagePitch + gConfig_disparity[t].numDisparities - 1)*gConfig_disparity[t].srcImageHeight;

                dispOutput= (uint8_t*)malloc(sizeDispOutput);
                assert(dispOutput != NULL);

                dispRLOutput= (uint8_t*)malloc(sizeDispRLOutput);
                assert(dispRLOutput != NULL);

                dispRefOutput= (uint8_t*)malloc(sizeDispOutput);
                assert(dispRefOutput != NULL);

                dispRefRLOutput= (uint8_t*)malloc(sizeDispRLOutput);
                assert(dispRefRLOutput != NULL);

                minCostOutput= (uint16_t*)malloc(sizeDispOutput*2);
                assert(minCostOutput != NULL);

                minCostRefOutput= (uint16_t*)malloc(sizeDispOutput*2);
                assert(minCostRefOutput != NULL);

                minCostRefRLOutput= (uint16_t*)malloc(2*(gConfig_disparity[t].srcImageWidth + gConfig_disparity[t].numDisparities - 1)*(gConfig_disparity[t].numDisparities/gConfig_disparity[t].disparityStep));
                assert(minCostRefRLOutput != NULL);

                natC_allCostOutput= (uint16_t*)malloc(2*gConfig_disparity[t].srcImageWidth*(gConfig_disparity[t].numDisparities/gConfig_disparity[t].disparityStep));
                assert(natC_allCostOutput != NULL);

                natC_allCostRLOutput= (uint16_t*)malloc(2*(gConfig_disparity[t].srcImageWidth + gConfig_disparity[t].numDisparities - 1)*(gConfig_disparity[t].numDisparities/gConfig_disparity[t].disparityStep));
                assert(natC_allCostRLOutput != NULL);

                if (gConfig_disparity[t].outputCostType== DISPARITY_TI_MIN_ADJACENT_COSTS) {
                    prevAdjCostOutput= (uint16_t*)malloc(sizeDispOutput*2);
                    assert(prevAdjCostOutput != NULL);
                    nextAdjCostOutput= (uint16_t*)malloc(sizeDispOutput*2);
                    assert(nextAdjCostOutput != NULL);
                    prevAdjCostRefOutput= (uint16_t*)malloc(sizeDispOutput*2);
                    assert(prevAdjCostRefOutput != NULL);
                    nextAdjCostRefOutput= (uint16_t*)malloc(sizeDispOutput*2);
                    assert(nextAdjCostRefOutput != NULL);
                }

                if (gConfig_disparity[t].pattern== 1) {
                    /* Generate random input data */
                    srand(1);
                    for(i=0; i<sizeInputLeft; i++)
                    {
                        inputLeft[i] = rand() % 256;
                    }
#if 1
                    for(i=0; i<sizeInputRight; i++)
                    {
                        inputRight[i] = rand() % 256;
                    }
#else
                    memset(inputRight, 0, sizeInputRight);
                    /* Generate right image by extracting slices of the left image and pasting them to the right image by a shifted amount. The shift amount
                     * increases by 1 from one slice to the next one, until it reaches numDisparities and then rolls back */
                    d= 0;
                    for(i=0;i<gConfig_disparity[t].srcImageHeight + gConfig_disparity[t].winHeight - 1;i+= SLICE_HEIGHT) {
                        /* Copy left to right, destination position in right image is shifted by the amount d*inputByteLen */
                        numLinesInSlice = MIN(SLICE_HEIGHT, gConfig_disparity[t].srcImageHeight + gConfig_disparity[t].winHeight - 1 - i);
                        for (j = 0; j<numLinesInSlice; j++) {
                            memcpy(&inputRight[((i + j)*gConfig_disparity[t].srcImagePitchR + d)*inputByteLen], &inputLeft[(i + j)*gConfig_disparity[t].srcImagePitchL*inputByteLen], inputByteLen * (gConfig_disparity[t].srcImagePitchL - d));
                            /* Zero out the first d*inputByteLen bytes of the row */
                            //memset(&inputRight[(i + j)*gConfig_disparity[t].srcImagePitch*inputByteLen], 0,  d*inputByteLen);
                        }
                        d++;
                        if (d > gConfig_disparity[t].numDisparities)
                            d= 0;
                    }
#endif
                }
                else {
                    sprintf(filepath, "../testvecs/%s", gConfig_disparity[t].inImageLeft);
                    fid= FOPEN(filepath,"rb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }

                    numBytes= FREAD(inputLeft, 1, sizeInputLeft, fid);
                    assert(numBytes== sizeInputLeft);
                    FCLOSE(fid);

                    sprintf(filepath, "../testvecs/%s", gConfig_disparity[t].inImageRight);
                    fid= FOPEN(filepath,"rb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }

                    numBytes= FREAD(inputRight, 1, sizeInputRight, fid);
                    assert(numBytes== sizeInputRight);
                    FCLOSE(fid);
                }

                /* Zero out both output and reference output arrays */
                memset(dispOutput, 0, sizeDispOutput);
                memset(dispRefOutput, 0, sizeDispOutput);
                memset(minCostOutput, 0, 2*sizeDispOutput);
                memset(minCostRefOutput, 0, 2*sizeDispOutput);

                if (gConfig_disparity[t].outputCostType== DISPARITY_TI_MIN_ADJACENT_COSTS) {
                    memset(prevAdjCostOutput, 0, 2*sizeDispOutput);
                    memset(nextAdjCostOutput, 0, 2*sizeDispOutput);
                    memset(prevAdjCostRefOutput, 0, 2*sizeDispOutput);
                    memset(nextAdjCostRefOutput, 0, 2*sizeDispOutput);
                }

                profiler_start();
                /*-----------------------------------------------------------------
                            Set algorithm parameters
                  -----------------------------------------------------------------*/
                createParams.visionParams.algParams.size   = sizeof(DISPARITY_TI_CreateParams);
                createParams.visionParams.cacheWriteBack   = NULL;
                createParams.imgFrameWidth                 = gConfig_disparity[t].srcImageWidth;
                createParams.imgFrameHeight                = gConfig_disparity[t].srcImageHeight;
                createParams.inputBitDepth               = gConfig_disparity[t].inputBitDepth;
                createParams.winWidth                      = gConfig_disparity[t].winWidth;
                createParams.winHeight                     = gConfig_disparity[t].winHeight;
                createParams.numDisparities                = gConfig_disparity[t].numDisparities;
                createParams.disparityStep                 = gConfig_disparity[t].disparityStep;
                createParams.costMethod                    = DISPARITY_TI_HAM_DIST;
                createParams.searchDir                     = (DISPARITY_TI_SearchDir)gConfig_disparity[t].searchDir;
                createParams.outputCostType                = (DISPARITY_TI_SearchDir)gConfig_disparity[t].outputCostType;

                /*---------------------------------------------------
                           Query alogorithm memory requirement using standard IALG interface
                  -----------------------------------------------------------------*/
                numMemRec = DISPARITY_TI_VISION_FXNS.ialg.algNumAlloc();
                memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

                status = DISPARITY_TI_VISION_FXNS.ialg.algAlloc(
                        (IALG_Params *)(&createParams), NULL, memRec);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

#if ENABLE_TRACES
                TEST_PRINTF("Hamming-based disparity calculation Applet Creation Done\n");
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
                status = DISPARITY_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                        memRec,NULL,(IALG_Params *)(&createParams));

                profiler_end_print(0);
                profile_create_tsc = gTest_TI_profileTsc;

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                handle = (IM_Fxns *) memRec[0].base;

#if ENABLE_TRACES
                TEST_PRINTF("Disparity calc applet Init Done\n");
#endif
                /* Use control API to query the optimum output block width and height found by algInit() */

                ctlInParams.algParams.size= sizeof(DISPARITY_TI_ControlInParams);
                ctlOutParams.algParams.size= sizeof(DISPARITY_TI_ControlOutParams);

                cmd= DISPARITY_TI_GET_OUTPUT_BLOCK_DIM;
                status = handle->ivision->algControl((IVISION_Handle)handle, cmd, (const IALG_Params *)&ctlInParams, (IALG_Params *)&ctlOutParams);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                inArgs.subFrameInfo = 0;
                inArgs.size                  = sizeof(IVISION_InArgs);

                idx = DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE;

                inBufs.bufDesc[idx]->numPlanes                          = 1;

                if (createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = createParams.numDisparities - 1 + (createParams.winWidth - 1)/2;
                }
                else {
                    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (createParams.winWidth - 1)/2;
                }

                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (createParams.winHeight - 1)/2;
                /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
                 * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
                 * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
                 * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
                 * at (frameROI.topLeft.x, frameROI.topLeft.y) .
                 * */
                inBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_disparity[t].srcImagePitchL;
                inBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_disparity[t].srcImageHeight + createParams.winHeight - 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_disparity[t].srcImageWidth;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_disparity[t].srcImageHeight;
                inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )inputLeft ;

                if(inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx= DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE;
                inBufs.bufDesc[idx]->numPlanes                          = 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (createParams.winWidth - 1)/2;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (createParams.winHeight - 1)/2;
                /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
                 * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
                 * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
                 * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
                 * at (frameROI.topLeft.x, frameROI.topLeft.y) .
                 * */
                inBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_disparity[t].srcImagePitchR;
                inBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_disparity[t].srcImageHeight + createParams.winHeight - 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_disparity[t].srcImageWidth;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_disparity[t].srcImageHeight;
                inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )inputRight ;

                if(inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx = DISPARITY_TI_BUFDESC_DISPARITY_OUT;
                outBufs.bufDesc[idx]->numPlanes                          = 1;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_disparity[t].dstImagePitch;
                outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_disparity[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_disparity[t].srcImageWidth;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_disparity[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )dispOutput;

                idx = DISPARITY_TI_BUFDESC_COST_OUT;
                outBufs.bufDesc[idx]->numPlanes                          = 1;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_disparity[t].dstImagePitch;
                outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_disparity[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_disparity[t].srcImageWidth;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_disparity[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )minCostOutput;

                if (gConfig_disparity[t].outputCostType== DISPARITY_TI_MIN_ADJACENT_COSTS) {
                    idx = DISPARITY_TI_BUFDESC_PREV_ADJ_COST_OUT;
                    outBufs.bufDesc[idx]->numPlanes                          = 1;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                    outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_disparity[t].dstImagePitch;
                    outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_disparity[t].srcImageHeight;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_disparity[t].srcImageWidth;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_disparity[t].srcImageHeight;
                    outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )prevAdjCostOutput;

                    idx = DISPARITY_TI_BUFDESC_NEXT_ADJ_COST_OUT;
                    outBufs.bufDesc[idx]->numPlanes                          = 1;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                    outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_disparity[t].dstImagePitch;
                    outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_disparity[t].srcImageHeight;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_disparity[t].srcImageWidth;
                    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_disparity[t].srcImageHeight;
                    outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )nextAdjCostOutput;
                }

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
                memset(dispOutput, 0, sizeDispOutput);
                memset(minCostOutput, 0, 2*sizeDispOutput);

                vcop_minit();
                wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
                memset(wbufToZero, 0, 31*1024);
                vcop_free(wbufToZero);

                profiler_start();
                status = handle->ivision->algProcess((IVISION_Handle)handle,
                        &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);
                profiler_end_print(1);

                profile_tsc = gTest_TI_profileTsc;;
                profile_sctm = gTest_TI_profileSctm[0];

                if (createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                    prevAdjCostRefOutputTemp= prevAdjCostRefOutput;
                    nextAdjCostRefOutputTemp= nextAdjCostRefOutput;
                    extraOffset= createParams.numDisparities - 1;
                }
                else {
                    prevAdjCostRefOutputTemp= nextAdjCostRefOutput;
                    nextAdjCostRefOutputTemp= prevAdjCostRefOutput;
                    extraOffset= 0;
                }

                if (disparity_skipValidation== 0) {

                    /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                    /*  Call the natural C implementation for disparity calculation which results will be used to validate EVE's output                                     */
                    /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                    for (r=0; r< gConfig_disparity[t].srcImageHeight; r++) {
#if 0 /* Below is a very slow version of the natural C code so we disable it and instead use a faster version. Re-enable if you suspect faster version has a bug */
                        vcop_disparity_hammingDistance_row_ref_cn
                        (
                                inputLeft + (extraOffset + r*gConfig_disparity[t].srcImagePitchL)*inputByteLen,
                                inputRight + (r*gConfig_disparity[t].srcImagePitchR)*inputByteLen,
                                inBufDesc.bufPlanes[0].width*inputByteLen,
                                inBufDesc.bufPlanes[1].width*inputByteLen,
                                createParams.winWidth,
                                createParams.winHeight,
                                dispRefOutput + r*gConfig_disparity[t].dstImagePitch,
                                minCostRefOutput + r*gConfig_disparity[t].dstImagePitch,
                                natC_allCostOutput,
                                gConfig_disparity[t].srcImageWidth,
                                createParams.numDisparities,
                                createParams.disparityStep,
                                inputByteLen,
                                createParams.searchDir
                        );
#else
                        if (r==0) {
                            vcop_disparity_hammingDistance_first_row_cn(
                                    inputLeft + extraOffset*inputByteLen,
                                    inputRight,
                                    gConfig_disparity[t].srcImagePitchL*inputByteLen,
                                    gConfig_disparity[t].srcImagePitchR*inputByteLen,
                                    createParams.winWidth,
                                    createParams.winHeight,
                                    dispRefOutput,
                                    minCostRefOutput,
                                    natC_allCostOutput,
                                    gConfig_disparity[t].srcImageWidth,
                                    gConfig_disparity[t].srcImageWidth,
                                    createParams.numDisparities,
                                    createParams.disparityStep,
                                    inputByteLen,
                                    createParams.searchDir
                            );
                        }
                        else {
                            vcop_disparity_hammingDistance_nth_row_cn(
                                    inputLeft + (extraOffset + r*gConfig_disparity[t].srcImagePitchL)*inputByteLen,
                                    inputRight + (r*gConfig_disparity[t].srcImagePitchR)*inputByteLen,
                                    gConfig_disparity[t].srcImagePitchL*inputByteLen,
                                    gConfig_disparity[t].srcImagePitchR*inputByteLen,
                                    createParams.winWidth,
                                    createParams.winHeight,
                                    dispRefOutput + r*gConfig_disparity[t].dstImagePitch,
                                    minCostRefOutput + r*gConfig_disparity[t].dstImagePitch,
                                    natC_allCostOutput,
                                    natC_allCostOutput,
                                    gConfig_disparity[t].srcImageWidth,
                                    gConfig_disparity[t].srcImageWidth,
                                    createParams.numDisparities,
                                    createParams.disparityStep,
                                    inputByteLen,
                                    createParams.searchDir
                            );
                        }
#endif
                        if (gConfig_disparity[t].outputCostType== DISPARITY_TI_MIN_ADJACENT_COSTS) {
                            vcop_disparity_genPrevAndNextMinCost_cn(
                                    dispRefOutput + r*gConfig_disparity[t].dstImagePitch,
                                    natC_allCostOutput,
                                    prevAdjCostRefOutputTemp + r*gConfig_disparity[t].dstImagePitch,
                                    nextAdjCostRefOutputTemp + r*gConfig_disparity[t].dstImagePitch,
                                    gConfig_disparity[t].srcImageWidth,
                                    createParams.numDisparities,
                                    createParams.disparityStep
                            );
                        }

                        if (createParams.searchDir== DISPARITY_TI_BOTH_DIR) { /* If right-to-Left disparity calculation was also enabled, invoke the corresponding reference C code */
#if 0
                            vcop_disparity_hammingDistance_row_right_left_ref_cn
                            (
                                    inputLeft + (createParams.numDisparities - 1 + r*gConfig_disparity[t].srcImagePitchL)*inputByteLen,
                                    inputRight + (createParams.numDisparities - 1 + r*gConfig_disparity[t].srcImagePitchR)*inputByteLen,
                                    gConfig_disparity[t].srcImagePitchL*inputByteLen,
                                    gConfig_disparity[t].srcImagePitchR*inputByteLen,
                                    createParams.winWidth,
                                    createParams.winHeight,
                                    dispRefRLOutput + r*gConfig_disparity[t].dstImagePitch,//natC_RLdispOut + r*params->width,
                                    minCostRefRLOutput,//natC_RLminCostOutput + r*params->width,
                                    natC_allCostRLOutput,//natC_RLallCostOutput + r*(params->numDisparities/params->disparityStep)*params->width,
                                    gConfig_disparity[t].srcImageWidth,
                                    createParams.numDisparities,
                                    createParams.disparityStep,
                                    inputByteLen,
                                    createParams.searchDir
                            );
#else
                            memset(minCostRefRLOutput, 0xFF, 2*(gConfig_disparity[t].dstImagePitch + createParams.numDisparities - 1));

                            vcop_disparity_hammingDistance_row_right_left_cn
                            (
                                    natC_allCostOutput ,
                                    dispRefRLOutput + r*(gConfig_disparity[t].dstImagePitch + createParams.numDisparities - 1),
                                    minCostRefRLOutput,
                                    dispRefRLOutput + r*(gConfig_disparity[t].dstImagePitch + createParams.numDisparities - 1),
                                    minCostRefRLOutput,
                                    natC_allCostRLOutput,
                                    NULL,
                                    NULL,
                                    2*gConfig_disparity[t].srcImageWidth,
                                    2*(gConfig_disparity[t].srcImageWidth + createParams.numDisparities - 1),
                                    gConfig_disparity[t].srcImageWidth,
                                    createParams.numDisparities,
                                    createParams.disparityStep
                            );

                            /* Shift the line to the left border by disparity_createParams->numDisparities - 1 pixels as these pixels are garbage and not meaningful */
                            memcpy(dispRefRLOutput + r*gConfig_disparity[t].dstImagePitch, dispRefRLOutput + createParams.numDisparities - 1 + r*(gConfig_disparity[t].dstImagePitch + createParams.numDisparities - 1), gConfig_disparity[t].srcImageWidth);
#endif
                        }
                    }

                    fail = 0;

                    for(i=0; i<gConfig_disparity[t].srcImageHeight; i++)
                    {
                        for(j=0; j<gConfig_disparity[t].srcImageWidth; j++)
                        {
                            if(dispOutput[i*gConfig_disparity[t].dstImagePitch+j] != dispRefOutput[i*gConfig_disparity[t].dstImagePitch+j])
                            {
                                fail = 1;
                                TEST_PRINTF("Disparity error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, dispOutput[i*gConfig_disparity[t].dstImagePitch+j], dispRefOutput[i*gConfig_disparity[t].dstImagePitch+j]);
                                break;
                            }
                        }
                    }

                    for(i=0; i<gConfig_disparity[t].srcImageHeight; i++)
                    {
                        for(j=0; j<gConfig_disparity[t].srcImageWidth; j++)
                        {
                            if(minCostOutput[i*gConfig_disparity[t].dstImagePitch+j] != minCostRefOutput[i*gConfig_disparity[t].dstImagePitch+j])
                            {
                                fail = 1;
                                TEST_PRINTF("Min-cost error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, minCostOutput[i*gConfig_disparity[t].dstImagePitch+j], minCostRefOutput[i*gConfig_disparity[t].dstImagePitch+j]);
                                break;
                            }
                        }
                    }

                    if (gConfig_disparity[t].outputCostType== DISPARITY_TI_MIN_ADJACENT_COSTS) {
                        for(i=0; i<gConfig_disparity[t].srcImageHeight; i++)
                        {
                            for(j=0; j<gConfig_disparity[t].srcImageWidth; j++)
                            {
                                if(prevAdjCostOutput[i*gConfig_disparity[t].dstImagePitch+j] != prevAdjCostRefOutput[i*gConfig_disparity[t].dstImagePitch+j])
                                {
                                    fail = 1;
                                    TEST_PRINTF("prevAdjCost error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, prevAdjCostOutput[i*gConfig_disparity[t].dstImagePitch+j], prevAdjCostRefOutput[i*gConfig_disparity[t].dstImagePitch+j]);
                                    break;
                                }
                            }
                        }

                        for(i=0; i<gConfig_disparity[t].srcImageHeight; i++)
                        {
                            for(j=0; j<gConfig_disparity[t].srcImageWidth; j++)
                            {
                                if(nextAdjCostOutput[i*gConfig_disparity[t].dstImagePitch+j] != nextAdjCostRefOutput[i*gConfig_disparity[t].dstImagePitch+j])
                                {
                                    fail = 1;
                                    TEST_PRINTF("nextAdjCost error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, nextAdjCostOutput[i*gConfig_disparity[t].dstImagePitch+j], nextAdjCostRefOutput[i*gConfig_disparity[t].dstImagePitch+j]);
                                    break;
                                }
                            }
                        }
                    }

#if 1
                    if (createParams.searchDir== DISPARITY_TI_BOTH_DIR) {
                        for(i=0; i<gConfig_disparity[t].srcImageHeight; i++)
                        {
                            for(j=0; j<gConfig_disparity[t].srcImageWidth; j++)
                            {
                                if(dispRLOutput[i*gConfig_disparity[t].dstImagePitch+j] != dispRefRLOutput[i*gConfig_disparity[t].dstImagePitch+j])
                                {
                                    fail = 1;
                                    TEST_PRINTF("Disparity error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, dispRLOutput[i*gConfig_disparity[t].dstImagePitch+j], dispRefRLOutput[i*gConfig_disparity[t].dstImagePitch+j]);
                                    break;
                                }
                            }
                        }
                    }
#endif
                    statusStr = fail? "FAILED" : "PASSED";
                }
                else {
                    statusStr = "  N/A  ";
                }

                fflush(stdout);

                result= (int32_t)((uint32_t)result & (uint32_t)fail);

                if (createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                    dirStr= "LR";
                }
                else {
                    dirStr= "RL";
                }

                TEST_PRINTF("%d) Codeword length %d bytes %dx%d numDisp:%3d dispStep:%d cosTyp:%d searchDir:%s  %5s %10d %10d %15.2f %20.2f %10.2f %20.2f %16.2f       Create graph is %2.2f Mcycles per frame but it is a one-time startup call, output block is %d x %d\n",
                        testNum, inputByteLen, createParams.winWidth, createParams.winHeight,
                        createParams.numDisparities, createParams.disparityStep, createParams.outputCostType, dirStr, statusStr, gConfig_disparity[t].srcImageWidth, gConfig_disparity[t].srcImageHeight,
                        (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0), (profile_tsc*1.0)/(gConfig_disparity[t].srcImageWidth * gConfig_disparity[t].srcImageHeight),
                        (profile_sctm*1.0)/(gConfig_disparity[t].srcImageWidth * gConfig_disparity[t].srcImageHeight),(profile_tsc/500000.0), (profile_create_tsc*1.0)/1000000.0, ctlOutParams.outputBlockWidth, ctlOutParams.outputBlockHeight);

                fflush(stdout);

                if (gConfig_disparity[t].pattern== 0) {
                    /* Write output file */
                    sprintf(filepath, "../testvecs/%s", gConfig_disparity[t].outImage);
                    fid= FOPEN(filepath,"wb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }
                    numBytes= FWRITE(dispOutput, 1, gConfig_disparity[t].dstImagePitch*gConfig_disparity[t].srcImageHeight, fid);
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

                if (dispOutput != NULL)
                {
                    free(dispOutput);
                }

                if (dispRLOutput != NULL)
                {
                    free(dispRLOutput);
                }

                if (minCostOutput != NULL)
                {
                    free(minCostOutput);
                }

                if (inputLeft != NULL)
                {
                    free(inputLeft);
                }

                if (inputRight != NULL)
                {
                    free(inputRight);
                }

                if(dispRefOutput != NULL)
                {
                    free(dispRefOutput);
                }

                if(dispRefRLOutput != NULL)
                {
                    free(dispRefRLOutput);
                }

                if (minCostRefOutput != NULL)
                {
                    free(minCostRefOutput);
                }

                if (minCostRefRLOutput != NULL)
                {
                    free(minCostRefRLOutput);
                }

                if(natC_allCostOutput != NULL)
                {
                    free(natC_allCostOutput);
                }

                if(natC_allCostRLOutput != NULL)
                {
                    free(natC_allCostRLOutput);
                }

                if (gConfig_disparity[t].outputCostType== DISPARITY_TI_MIN_ADJACENT_COSTS) {

                    if(prevAdjCostOutput != NULL)
                    {
                        free(prevAdjCostOutput);
                    }

                    if(nextAdjCostOutput != NULL)
                    {
                        free(nextAdjCostOutput);
                    }

                    if(prevAdjCostRefOutput != NULL)
                    {
                        free(prevAdjCostRefOutput);
                    }

                    if(nextAdjCostRefOutput != NULL)
                    {
                        free(nextAdjCostRefOutput);
                    }

                }
                 /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
                profiler_getStackDepth();
#endif
#ifdef SCAN_DIM
                gConfig_disparity[t].srcImageWidth -= 16;
            }
            gConfig_disparity[t].srcImageWidth= initialWidth;
            gConfig_disparity[t].srcImageHeight -= 2;
        }
#endif
    }

    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);

    return result;
}

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '   ')||(LinePtr[0] == ','))
    {
        LinePtr++;
    }
    return(LinePtr);
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

    report_printAppletInfo((int8_t *)"DISPARITY_TI_VISION");

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

    TEST_PRINTF("\n%-74s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
            "Disparity Algorithm", "Status", "Width", "Height", "MegaCycPerFr", \
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

            status = readparamfile(configFile, &gsTokenMap_disparity[0]);
            if(status == -1)
            {
                TEST_PRINTF("Parser Failed");
                return -1 ;
            }

            profiler_testCaseInfo((int8_t *)gConfig_disparity[0].testCaseName, (int8_t *)gConfig_disparity[0].desc,
                    gConfig_disparity[0].performanceTestcase);
            printparams(&gsTokenMap_disparity[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_disparity),
                    sizeof(sdisparity_Config));

            /* Validate the applet */
            status = test_disparity(gConfig_disparity, lineNum);
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

