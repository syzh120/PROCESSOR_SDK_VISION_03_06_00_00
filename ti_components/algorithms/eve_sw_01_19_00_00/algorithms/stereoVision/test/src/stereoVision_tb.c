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


/** @file stereoVision_tb.c
 *
 *  @brief  This file contains test code for stereoVision algorithm
 *
 *
 *  @date   21 Aug 2014
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
#include <math.h>
#include <vcop.h>


#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"
#include "iDisparity_ti.h"
#include "iCensus_ti.h"
#include "../vlib/vcop_census_8bits/inc/vcop_census_8bits_cn.h"
#include "../vlib/vcop_census_16bits/inc/vcop_census_16bits_cn.h"
#include "../vlib/vcop_disparity_hammingDistance_row/inc/vcop_disparity_hammingDistance_row_cn.h"
#include "../vlib/vcop_disparity_sad8_row/inc/vcop_disparity_sad8_row_cn.h"
#include "../vlib/vcop_disparity_sad16_row/inc/vcop_disparity_sad16_row_cn.h"
#include "stereoVision_config.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"

#include "stereoVision_testfuncs.h"
#include "ti_file_io.h"
#include "ti_image_file_io.h"
#include "rectify.h"

/*#define _CENSUS_FILE*/
/* #define YUV_OUTPUT */

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

#define ABS(x) (((x)<0) ? (-x) : (x))

#define MIN(a,b) ((a)<(b)?(a):(b))

#define SLICE_HEIGHT 10

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (14*1024)

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

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '   ')||(LinePtr[0] == ','))
    {
        LinePtr++;
    }
    return(LinePtr);
}

int test_stereoVision(sstereoVision_Config * gConfig_stereoVision, int testNum)
{
    int i=0, result = 0;
    char *statusStr = NULL;
    unsigned int tcntr0, tcntr1, overflow, profile_sctm;
    uint32_t sizeDispOutput, sizeDisparityInput;
    uint16_t *natC_allCostOutput, *natC_allCostRLOutput;
    uint16_t numCensusOrientations, numBytesPerCensus;
    CENSUS_TI_ControlInParams census_ctlInParams;
    CENSUS_TI_ControlOutParams census_ctlOutParams;
    DISPARITY_TI_ControlInParams disparity_ctlInParams;
    DISPARITY_TI_ControlOutParams disparity_ctlOutParams;
    DISPARITY_TI_ControlInParams lrCheckDisparity_ctlInParams;
    DISPARITY_TI_ControlOutParams lrCheckDisparity_ctlOutParams;
    uint16_t left_n_rows, right_n_rows, left_n_cols, right_n_cols;
    uint16_t left_bytesPerPixel, right_bytesPerPixel, left_maxBitPerPixel, right_maxBitPerPixel;
    int32_t n_maxValue;
    uint8_t *dispImage_red, *dispImage_grn, *dispImage_blu;

    char filepath[256];
    char filepath2[256];
    char *algoString;
    char censusString[]="Census";
    char sadString[]="SAD   ";
    char *dirStr;
    uint32_t t;
    float avgError;
    uint8_t maxDiff= 0;

    uint32_t idx;
    uint8_t *census_inputLeft, *census_inputRight, *remap_inputLeft, *remap_inputRight;
    uint8_t **inputLeft, **inputRight;
    uint8_t *gtImage=  NULL;
    uint8_t *diffImage= NULL;
    uint8_t *disparity_inputLeft, *disparity_inputRight;
    uint8_t *disparity_inputLeft8bits, *disparity_inputRight8bits;
    uint8_t *refDisparity_inputLeft, *refDisparity_inputRight;
    uint8_t *dispOutput, *lrCheckDispOutput, *dispRefOutput;
    uint16_t *minCostOutput, *lrCheckMinCostOutput, *minCostRefOutput, *prevAdjCostOutput, *nextAdjCostOutput,*prevAdjCostRefOutput, *nextAdjCostRefOutput;
    uint16_t totalDisparityRange;

    int fail = 0;

    unsigned int t0, t1, overhead, profile_tsc, profile_create_tsc;

    int32_t census_numMemRec= 0;
    IALG_MemRec *census_memRec= NULL;
    int32_t disparity_numMemRec= 0;
    IALG_MemRec *disparity_memRec= NULL;
    int32_t lrCheckDisparity_numMemRec= 0;
    IALG_MemRec *lrCheckDisparity_memRec= NULL;
    int32_t status;
    IALG_Cmd cmd;

    /*-----------------------------------------------------------------
             Pointer to algorithm instance
             -----------------------------------------------------------------*/
    IM_Fxns *disparity_handle= NULL, *lrCheckDisparity_handle= NULL, *census_handle= NULL;

    /*-----------------------------------------------------------------
             Algorithm parameters memory in stack
             -----------------------------------------------------------------*/
    CENSUS_TI_CreateParams  census_createParams;
    DISPARITY_TI_CreateParams  disparity_createParams;
    DISPARITY_TI_CreateParams  lrCheckDisparity_createParams; /* Extra disparity map produced for the purpose of Left-Right check */ 

    IVISION_InArgs    disparity_inArgs;
    IVISION_InBufs    disparity_inBufs;
    IVISION_InArgs    lrCheckDisparity_inArgs;
    IVISION_InBufs    lrCheckDisparity_inBufs;
    IVISION_InArgs    census_inArgs;
    IVISION_InBufs    census_inBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   census_inBufDesc[CENSUS_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *census_inBufDescList[CENSUS_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   disparity_inBufDesc[DISPARITY_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *disparity_inBufDescList[DISPARITY_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   lrCheckDisparity_inBufDesc[DISPARITY_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *lrCheckDisparity_inBufDescList[DISPARITY_TI_BUFDESC_IN_TOTAL];

    CENSUS_TI_outArgs                census_outArgs;
    IVISION_OutBufs                  census_outBufs;
    DISPARITY_TI_outArgs     disparity_outArgs;
    IVISION_OutBufs                  disparity_outBufs;
    DISPARITY_TI_outArgs             lrCheckDisparity_outArgs;
    IVISION_OutBufs                  lrCheckDisparity_outBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   census_outBufDesc[CENSUS_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *census_outBufDescList[CENSUS_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   disparity_outBufDesc[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *disparity_outBufDescList[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   lrCheckDisparity_outBufDesc[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *lrCheckDisparity_outBufDescList[DISPARITY_TI_BUFDESC_OUT_TOTAL];

    disparity_outArgs.iVisionOutArgs.size = sizeof(DISPARITY_TI_outArgs);
    lrCheckDisparity_outArgs.iVisionOutArgs.size = sizeof(DISPARITY_TI_outArgs);
    census_outArgs.iVisionOutArgs.size = sizeof(CENSUS_TI_outArgs);

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t *pDmem;
    TIMemHandle memHdl_DMEM;

    pDmem = (uint8_t *)&DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;
    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

    _tsc_start();
    t0 = _tsc_gettime();
    overhead = _tsc_gettime() - t0;

    /*------------------------------------------------------------*/
    /* This function actually sets Enable bit in the CT CNTL      */
    /* register of SCTM. Parameter CTM is defined in              */
    /* baseaddress.h, and is used by cred macros to compute       */
    /* baseaddress of CTM.                                        */
    /*------------------------------------------------------------*/
    EVE_SCTM_Enable(CTM);

    /*------------------------------------------------------------*/
    /* Configure Counter 0, to measure "vcop_busy" which is a     */
    /* duration signal, and enable the counter.                   */
    /*------------------------------------------------------------*/
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);

    /*-----------------------------------------------------------------
          Set buffer descriptor pointers array base for disparity
    -----------------------------------------------------------------*/
    census_inBufs.bufDesc  = census_inBufDescList;
    census_outBufs.bufDesc = census_outBufDescList;

    census_inBufs.numBufs   = CENSUS_BUFDESC_IN_TOTAL;
    census_outBufs.numBufs  = CENSUS_BUFDESC_OUT_TOTAL;

    for(i = 0 ; i < CENSUS_BUFDESC_IN_TOTAL ;i++)
    {
        census_inBufDescList[i]     = &census_inBufDesc[i];
    }

    for(i = 0 ; i < CENSUS_BUFDESC_OUT_TOTAL ;i++)
    {
        census_outBufDescList[i]     = &census_outBufDesc[i];
    }

    /*-----------------------------------------------------------------
          Set buffer descriptor pointers array base for disparity
    -----------------------------------------------------------------*/
    disparity_inBufs.bufDesc  = disparity_inBufDescList;
    disparity_outBufs.bufDesc = disparity_outBufDescList;

    disparity_inBufs.numBufs   = DISPARITY_TI_BUFDESC_IN_TOTAL;
    disparity_outBufs.numBufs  = DISPARITY_TI_BUFDESC_OUT_TOTAL;

    lrCheckDisparity_inBufs.bufDesc  = lrCheckDisparity_inBufDescList;
    lrCheckDisparity_outBufs.bufDesc = lrCheckDisparity_outBufDescList;

    lrCheckDisparity_inBufs.numBufs   = DISPARITY_TI_BUFDESC_IN_TOTAL;
    lrCheckDisparity_outBufs.numBufs  = DISPARITY_TI_BUFDESC_OUT_TOTAL;

    for(i = 0 ; i < DISPARITY_TI_BUFDESC_IN_TOTAL ;i++)
    {
        disparity_inBufDescList[i]     = &disparity_inBufDesc[i];
    }

    for(i = 0 ; i < DISPARITY_TI_BUFDESC_IN_TOTAL ;i++)
    {
        lrCheckDisparity_inBufDescList[i]     = &lrCheckDisparity_inBufDesc[i];
    }

    for(i = 0 ; i < DISPARITY_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        disparity_outBufDescList[i]     = &disparity_outBufDesc[i];
    }

    for(i = 0 ; i < DISPARITY_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        lrCheckDisparity_outBufDescList[i]     = &lrCheckDisparity_outBufDesc[i];
    }


    /* In order to derive stack requirements, call profiler_initStack() which will write DEADBEEF from current stack pointer up to the top */
    profiler_initStack(profiler_getSP());

    for (t=0;t<stereoVision_numTestCases;t++) {

        if (strcmp((const char *)gConfig_stereoVision[t].stereoMode,"CENSUS")==0) {
            algoString= censusString;
        }
        else { /* In case the algo is SAD, zero out some variables in order to avoid any side effect */
            algoString= sadString;
            gConfig_stereoVision[t].censusWinWidth= 1;
            gConfig_stereoVision[t].censusWinHeight= 1;
            census_createParams.winWidth= 1;
            census_createParams.winHeight= 1;
        }

        /* Load image files */
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision[t].inImageLeft);

        if (gConfig_stereoVision[t].enableRectify== 1) {
            inputLeft= &remap_inputLeft;
        }
        else {
            inputLeft= &census_inputLeft;
            remap_inputLeft= NULL;
        }

        status= readFilePGM((const int8_t*)filepath,
                inputLeft,
                &left_n_rows,
                &left_n_cols,
                &left_bytesPerPixel,
                &left_maxBitPerPixel,
                &n_maxValue);
        /* We realloc the buffer after rounding up the number of cols and rows by 16 pixels and by census filter width, in order to make sure we don't access any unallocated area of memory
         * during census transform since the requirement of the algorithm is to have the ROI width being multiple of 16 and also have extra border pixels.
         */
        if (gConfig_stereoVision[t].enableRectify== 1) {
            census_inputLeft= (uint8_t*)malloc((((left_n_cols + gConfig_stereoVision[t].censusWinWidth -1 + 15)>>4)<<4)*left_n_rows*(left_bytesPerPixel + gConfig_stereoVision[t].censusWinHeight-1));
        }else {
            *inputLeft= (uint8_t*)realloc(*inputLeft, (((left_n_cols + gConfig_stereoVision[t].censusWinWidth -1 + 15)>>4)<<4)*left_n_rows*(left_bytesPerPixel + gConfig_stereoVision[t].censusWinHeight-1));
            assert(*inputLeft != NULL);
        }

        if (status!=IALG_EOK) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        totalDisparityRange= gConfig_stereoVision[t].numDisparities - 1 + ABS(gConfig_stereoVision[t].disparityOffset);
        gConfig_stereoVision[t].srcImagePitch= left_n_cols;
        gConfig_stereoVision[t].inputBitDepth= left_maxBitPerPixel;

        /* If gConfig_stereoVision[t].imageWidth was not already set in the config file */
        if (gConfig_stereoVision[t].imageWidth== 0) {
            if (algoString== censusString) {
                gConfig_stereoVision[t].imageWidth= left_n_cols - (gConfig_stereoVision[t].censusWinWidth - 1) - (gConfig_stereoVision[t].disparityWinWidth - 1) - (totalDisparityRange);
            }
            else {
                gConfig_stereoVision[t].imageWidth= left_n_cols - (gConfig_stereoVision[t].disparityWinWidth - 1) - (totalDisparityRange);
            }
            /* round up to neareast multiple of 16. Normally should round down but for test purpose,we don't mind processing extra pixels even if the disparities are out of range */
            gConfig_stereoVision[t].imageWidth= ((gConfig_stereoVision[t].imageWidth+15)>>4)<<4;
        }

        /* If gConfig_stereoVision[t].imageHeight was not already set in the config file */
        if (gConfig_stereoVision[t].imageHeight== 0) {
            if (algoString== censusString) {
                gConfig_stereoVision[t].imageHeight= left_n_rows - (gConfig_stereoVision[t].censusWinHeight - 1) - (gConfig_stereoVision[t].disparityWinHeight - 1);
            }
            else {
                gConfig_stereoVision[t].imageHeight= left_n_rows - (gConfig_stereoVision[t].disparityWinHeight - 1);
            }
        }

        if (gConfig_stereoVision[t].dstImagePitch== 0) {
            gConfig_stereoVision[t].dstImagePitch=  gConfig_stereoVision[t].imageWidth;
        }

        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision[t].inImageRight);

        if (gConfig_stereoVision[t].enableRectify== 1) {
            inputRight= &remap_inputRight;
        }
        else {
            inputRight= &census_inputRight;
            remap_inputRight= NULL;
        }

        status= readFilePGM((const int8_t*)filepath,
                inputRight,
                &right_n_rows,
                &right_n_cols,
                &right_bytesPerPixel,
                &right_maxBitPerPixel,
                &n_maxValue);

        if (status!=IALG_EOK) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        if (left_n_rows != right_n_rows || left_n_cols != right_n_cols ||  left_bytesPerPixel != right_bytesPerPixel || left_maxBitPerPixel != right_maxBitPerPixel) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        /* We realloc the buffer after rounding up the number of cols by 16 pixels, in order to make sure we don't access any unallocated area of memory
         * during census transform since the requirement of the algorithm is to have the ROI width being multiple of 16
         */
        if (gConfig_stereoVision[t].enableRectify== 1) {
            census_inputRight= (uint8_t*)malloc((((left_n_cols + gConfig_stereoVision[t].censusWinWidth -1 + 15)>>4)<<4)*left_n_rows*(left_bytesPerPixel + gConfig_stereoVision[t].censusWinHeight-1));
        }else {
            *inputRight= (uint8_t*)realloc(*inputRight, (((left_n_cols + gConfig_stereoVision[t].censusWinWidth -1 + 15)>>4)<<4)*(left_n_rows)*(right_bytesPerPixel + gConfig_stereoVision[t].censusWinHeight-1));
            assert(*inputRight != NULL);
        }

        /* If ground truth was provided, let's load it */
        if (gConfig_stereoVision[t].gtImage[0]!=0) {
            sprintf(filepath, "../testvecs/%s", gConfig_stereoVision[t].gtImage);

            status= readFilePGM((const int8_t*)filepath,
                    &gtImage,
                    &left_n_rows,
                    &left_n_cols,
                    &left_bytesPerPixel,
                    &left_maxBitPerPixel,
                    &n_maxValue);

            if (status!=IALG_EOK) {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }
        }
        else {
            gtImage= NULL;
        }

        /* Allocate buffers
         * */
        numCensusOrientations= _CENSUS_WIN_SIZE(gConfig_stereoVision[t].censusWinWidth, gConfig_stereoVision[t].censusWinHeight, gConfig_stereoVision[t].censusWinHorzStep, gConfig_stereoVision[t].censusWinVertStep);
        numBytesPerCensus= (numCensusOrientations + 7) >> 3;
        census_createParams.imgFrameWidth = gConfig_stereoVision[t].imageWidth + gConfig_stereoVision[t].disparityWinWidth - 1 + totalDisparityRange;
        /* Make it multiple of 16 */
        census_createParams.imgFrameWidth = ((census_createParams.imgFrameWidth + 15) >> 4) << 4;
        census_createParams.imgFrameHeight = gConfig_stereoVision[t].imageHeight + gConfig_stereoVision[t].disparityWinHeight - 1;
        /* Make it multiple of 16 */
        census_createParams.imgFrameHeight = ((census_createParams.imgFrameHeight + 15) >> 4) << 4;
        sizeDisparityInput = numBytesPerCensus*(census_createParams.imgFrameWidth + ABS(gConfig_stereoVision[t].offset_x))*(census_createParams.imgFrameHeight+ABS(gConfig_stereoVision[t].offset_y));

        disparity_inputLeft= (uint8_t*)malloc(sizeDisparityInput);
        assert(disparity_inputLeft != NULL);

        disparity_inputRight= (uint8_t*)malloc(sizeDisparityInput);
        assert(disparity_inputRight != NULL);

        if (algoString== censusString) {/* in case census transform, allocate the buffers below to convert census codeword to 8-bits intensity in order to save to pgm file*/
            disparity_inputLeft8bits= (uint8_t*)malloc(sizeDisparityInput/numBytesPerCensus);
            assert(disparity_inputLeft8bits != NULL);

            disparity_inputRight8bits= (uint8_t*)malloc(sizeDisparityInput/numBytesPerCensus);
            assert(disparity_inputRight8bits != NULL);
        }

        /*If pattern is 1, then we enable validation with reference C code and we need to allocate buffers for reference c code */
        if (gConfig_stereoVision[t].pattern== 1) {
            refDisparity_inputLeft= (uint8_t*)malloc(sizeDisparityInput);
            assert(refDisparity_inputLeft != NULL);

            refDisparity_inputRight= (uint8_t*)malloc(sizeDisparityInput);
            assert(refDisparity_inputRight != NULL);
        }
        else {
            refDisparity_inputLeft= NULL;
            refDisparity_inputRight= NULL;
        }

        /* Allocate output and reference output buffer
         * Note that gConfig_disparityHamDist[t].dstImagePitch is expressed in term of bytes
         * */
        sizeDispOutput= gConfig_stereoVision[t].dstImagePitch*gConfig_stereoVision[t].imageHeight;

        dispOutput= (uint8_t*)malloc(sizeDispOutput);
        assert(dispOutput != NULL);

        lrCheckDispOutput= (uint8_t*)malloc(sizeDispOutput/2); /* For left right check, we are going to produce a disparity map for an input image that has been verticalluy downsampled */
        assert(lrCheckDispOutput != NULL);

        if (gConfig_stereoVision[t].gtImage[0]!=0) {
            diffImage= (uint8_t*)malloc(sizeDispOutput);
            assert(diffImage != NULL);
        }
        else {
            diffImage= NULL;
        }

        dispImage_red= (uint8_t*)malloc(sizeDispOutput);
        assert(dispImage_red != NULL);

        dispImage_grn= (uint8_t*)malloc(sizeDispOutput);
        assert(dispImage_grn != NULL);

        dispImage_blu= (uint8_t*)malloc(sizeDispOutput);
        assert(dispImage_blu != NULL);

        /*If pattern is 1, then we enable validation with reference C code and we need to allocate buffers for reference c code */
        if (gConfig_stereoVision[t].pattern== 1) {
            dispRefOutput= (uint8_t*)malloc(sizeDispOutput);
            assert(dispRefOutput != NULL);

            minCostRefOutput= (uint16_t*)malloc(sizeDispOutput*2);
            assert(minCostRefOutput != NULL);

        }
        else {
            dispRefOutput= NULL;
            minCostRefOutput= NULL;
        }

        minCostOutput= (uint16_t*)malloc(sizeDispOutput*2);
        assert(minCostOutput != NULL);

        lrCheckMinCostOutput= (uint16_t*)malloc(sizeDispOutput);
        assert(lrCheckMinCostOutput != NULL);

        prevAdjCostOutput= (uint16_t*)malloc(sizeDispOutput*2);
        assert(prevAdjCostOutput != NULL);

        nextAdjCostOutput= (uint16_t*)malloc(sizeDispOutput*2);
        assert(nextAdjCostOutput != NULL);

        prevAdjCostRefOutput= (uint16_t*)malloc(sizeDispOutput*2);
        assert(prevAdjCostRefOutput != NULL);

        nextAdjCostRefOutput= (uint16_t*)malloc(sizeDispOutput*2);
        assert(nextAdjCostRefOutput != NULL);

        natC_allCostOutput= (uint16_t*)malloc(2*gConfig_stereoVision[t].imageWidth*(gConfig_stereoVision[t].numDisparities/gConfig_stereoVision[t].disparityStep));
        assert(natC_allCostOutput != NULL);

        natC_allCostRLOutput= (uint16_t*)malloc(2*(gConfig_stereoVision[t].imageWidth + gConfig_stereoVision[t].numDisparities - 1)*(gConfig_stereoVision[t].numDisparities/gConfig_stereoVision[t].disparityStep));
        assert(natC_allCostRLOutput != NULL);

        /* Zero out both output and reference output arrays */
        memset(disparity_inputLeft, 0, sizeDisparityInput);
        memset(disparity_inputRight, 0, sizeDisparityInput);
        memset(dispOutput, 0, sizeDispOutput);
        memset(minCostOutput, 0, 2*sizeDispOutput);
        memset(lrCheckMinCostOutput, 0, sizeDispOutput);
        memset(prevAdjCostOutput, 0, 2*sizeDispOutput);
        memset(nextAdjCostOutput, 0, 2*sizeDispOutput);

        /*If pattern is 1, then we enable validation with reference C code and we need to reset some buffers */
        if (gConfig_stereoVision[t].pattern== 1) {
            memset(refDisparity_inputLeft, 0, sizeDisparityInput);
            memset(refDisparity_inputRight, 0, sizeDisparityInput);
            memset(dispRefOutput, 0, sizeDispOutput);
            memset(minCostRefOutput, 0, 2 * sizeDispOutput);
            memset(prevAdjCostRefOutput, 0, 2*sizeDispOutput);
            memset(nextAdjCostRefOutput, 0, 2*sizeDispOutput);
        }

        if (gConfig_stereoVision[t].enableRectify== 1) {
            status= rectify(&gConfig_stereoVision[t], remap_inputLeft, remap_inputRight, census_inputLeft, census_inputRight);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }
        }

        if (algoString== censusString) {

            /*-----------------------------------------------------------------
                                    Set census algorithm parameters
        -----------------------------------------------------------------*/
            census_createParams.visionParams.algParams.size   = sizeof(CENSUS_TI_CreateParams);
            census_createParams.visionParams.cacheWriteBack   = NULL;
            census_createParams.imgFrameWidth                 = gConfig_stereoVision[t].imageWidth + gConfig_stereoVision[t].disparityWinWidth - 1 + totalDisparityRange;
            /* Make it multiple of 16 */
            census_createParams.imgFrameWidth                 = ((census_createParams.imgFrameWidth + 15)>>4)<<4;
            census_createParams.imgFrameHeight                = gConfig_stereoVision[t].imageHeight + gConfig_stereoVision[t].disparityWinHeight - 1;
            /* Make it multiple of 16 */
            census_createParams.imgFrameHeight                 = ((census_createParams.imgFrameHeight + 15)>>4)<<4;
            census_createParams.inputBitDepth                 = gConfig_stereoVision[t].inputBitDepth;
            census_createParams.winWidth                      = gConfig_stereoVision[t].censusWinWidth;
            census_createParams.winHeight                     = gConfig_stereoVision[t].censusWinHeight;
            census_createParams.winHorzStep                   = gConfig_stereoVision[t].censusWinHorzStep;
            census_createParams.winVertStep                   = gConfig_stereoVision[t].censusWinVertStep;

            /*---------------------------------------------------
          Query algorithm memory requirement using standard IALG interface
        -----------------------------------------------------------------*/
            census_numMemRec = CENSUS_TI_VISION_FXNS.ialg.algNumAlloc();
            census_memRec    = (IALG_MemRec *)malloc(census_numMemRec*sizeof(IALG_MemRec));

            status = CENSUS_TI_VISION_FXNS.ialg.algAlloc(
                    (IALG_Params *)(&census_createParams), NULL, census_memRec);

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /*-----------------------------------------------------------------
                         Allocate memory for all the mem records
                         Application has to implement the below function
                         Refer the example implementation below in this file
        -----------------------------------------------------------------*/
            status = TestApp_AllocMemRecords(census_memRec,census_numMemRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /* Start measuring execution time for creation process */

            t0 = _tsc_gettime();

            /*-----------------------------------------------------------------
                         Intialize the algorithm instance with the allocated memory
                         and user create parameters
        -----------------------------------------------------------------*/
            status = CENSUS_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&census_handle),
                    census_memRec,NULL,(IALG_Params *)(&census_createParams));

            /* Set the end point of the timing measurement for the creation process */
            t1 = _tsc_gettime();
            profile_create_tsc = (t1 - t0 - overhead);

            if(status != IALG_EOK)
            {
                census_handle = NULL;
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            census_handle = (IM_Fxns *) census_memRec[0].base;

            /* Use control API to query the optimum output block width and height found by algInit() */

            census_ctlInParams.algParams.size= sizeof(CENSUS_TI_ControlInParams);
            census_ctlOutParams.algParams.size= sizeof(CENSUS_TI_ControlOutParams);

            cmd= CENSUS_GET_OUTPUT_BLOCK_DIM;
            status = census_handle->ivision->algControl((IVISION_Handle)census_handle, cmd, (const IALG_Params *)&census_ctlInParams, (IALG_Params *)&census_ctlOutParams);

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /*-----------------------------------------------------------------
                            Set disparity algorithm parameters
        -----------------------------------------------------------------*/
            disparity_createParams.visionParams.algParams.size   = sizeof(DISPARITY_TI_CreateParams);
            disparity_createParams.visionParams.cacheWriteBack   = NULL;
            disparity_createParams.imgFrameWidth                 = gConfig_stereoVision[t].imageWidth;
            disparity_createParams.imgFrameHeight                = gConfig_stereoVision[t].imageHeight;
            disparity_createParams.inputBitDepth                 = 8*numBytesPerCensus;
            disparity_createParams.winWidth                      = gConfig_stereoVision[t].disparityWinWidth;
            disparity_createParams.winHeight                     = gConfig_stereoVision[t].disparityWinHeight;
            disparity_createParams.numDisparities                = gConfig_stereoVision[t].numDisparities;
            disparity_createParams.disparityStep                 = gConfig_stereoVision[t].disparityStep;
            disparity_createParams.costMethod                    = DISPARITY_TI_HAM_DIST;
            disparity_createParams.outputCostType                = DISPARITY_TI_MIN_ADJACENT_COSTS;
            disparity_createParams.searchDir                     = (DISPARITY_TI_SearchDir)gConfig_stereoVision[t].searchDir;

            /*---------------------------------------------------
                           Query disparity algorithm memory requirement using standard IALG interface
                  -----------------------------------------------------------------*/
            disparity_numMemRec = DISPARITY_TI_VISION_FXNS.ialg.algNumAlloc();
            disparity_memRec    = (IALG_MemRec *)malloc(disparity_numMemRec*sizeof(IALG_MemRec));

            status = DISPARITY_TI_VISION_FXNS.ialg.algAlloc(
                    (IALG_Params *)(&disparity_createParams), NULL, disparity_memRec);

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /*-----------------------------------------------------------------
                 Allocate memory for all the mem records
                 Application has to implement the below function
                 Refer the example implementation below in this file
-----------------------------------------------------------------*/
            status = TestApp_AllocMemRecords(disparity_memRec, disparity_numMemRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /* Start measuring execution time for creation process */

            t0 = _tsc_gettime();

            /*-----------------------------------------------------------------
                 Intialize the algorithm instance with the allocated memory
                 and user create parameters
                -----------------------------------------------------------------*/
            status = DISPARITY_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&disparity_handle),
                    disparity_memRec,NULL,(IALG_Params *)(&disparity_createParams));

            if(status != IALG_EOK)
            {
                disparity_handle= NULL;
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /* Set the end point of the timing measurement for the creation process */
            t1 = _tsc_gettime();
            profile_create_tsc += (t1 - t0 - overhead);

            disparity_handle = (IM_Fxns *) disparity_memRec[0].base;

            /* Use control API to query the optimum output block width and height found by algInit() */

            disparity_ctlInParams.algParams.size= sizeof(DISPARITY_TI_ControlInParams);
            disparity_ctlOutParams.algParams.size= sizeof(DISPARITY_TI_ControlOutParams);

            cmd= DISPARITY_TI_GET_OUTPUT_BLOCK_DIM;
            status = disparity_handle->ivision->algControl((IVISION_Handle)disparity_handle, cmd, (const IALG_Params *)&disparity_ctlInParams, (IALG_Params *)&disparity_ctlOutParams);

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /*-----------------------------------------------------------------
                             Set disparity algorithm parameters for LR check instantation of disparity applet
             -----------------------------------------------------------------*/
            lrCheckDisparity_createParams.visionParams.algParams.size   = sizeof(DISPARITY_TI_CreateParams);
            lrCheckDisparity_createParams.visionParams.cacheWriteBack   = NULL;
            lrCheckDisparity_createParams.imgFrameWidth                 = gConfig_stereoVision[t].imageWidth;
            lrCheckDisparity_createParams.imgFrameHeight                = gConfig_stereoVision[t].imageHeight/2;
            lrCheckDisparity_createParams.inputBitDepth                 = 8*numBytesPerCensus;
            lrCheckDisparity_createParams.winWidth                      = gConfig_stereoVision[t].disparityWinWidth;
            lrCheckDisparity_createParams.winHeight                     = gConfig_stereoVision[t].disparityWinHeight/2 + 1;
            lrCheckDisparity_createParams.numDisparities                = gConfig_stereoVision[t].numDisparities;
            lrCheckDisparity_createParams.disparityStep                 = gConfig_stereoVision[t].disparityStep*2;
            lrCheckDisparity_createParams.costMethod                    = DISPARITY_TI_HAM_DIST;
            lrCheckDisparity_createParams.outputCostType                = DISPARITY_TI_NOCOST;
            /* If main image stereo's direction is left to right then we choose the opposite direction to generate the frame that will be used for LR check */
            if (gConfig_stereoVision[t].searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                lrCheckDisparity_createParams.searchDir                 = DISPARITY_TI_RIGHT_TO_LEFT;
            }
            else {
                lrCheckDisparity_createParams.searchDir                 = DISPARITY_TI_LEFT_TO_RIGHT;
            }

            /*---------------------------------------------------
                            Query disparity algorithm memory requirement using standard IALG interface
                   -----------------------------------------------------------------*/
            lrCheckDisparity_numMemRec = DISPARITY_TI_VISION_FXNS.ialg.algNumAlloc();
            lrCheckDisparity_memRec    = (IALG_MemRec *)malloc(lrCheckDisparity_numMemRec*sizeof(IALG_MemRec));

            status = DISPARITY_TI_VISION_FXNS.ialg.algAlloc(
                    (IALG_Params *)(&lrCheckDisparity_createParams), NULL, lrCheckDisparity_memRec);

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /*-----------------------------------------------------------------
                  Allocate memory for all the mem records
                  Application has to implement the below function
                  Refer the example implementation below in this file
 -----------------------------------------------------------------*/
            status = TestApp_AllocMemRecords(lrCheckDisparity_memRec, lrCheckDisparity_numMemRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /* Start measuring execution time for creation process */

            t0 = _tsc_gettime();

            /*-----------------------------------------------------------------
                  Intialize the algorithm instance with the allocated memory
                  and user create parameters
                 -----------------------------------------------------------------*/
            status = DISPARITY_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&lrCheckDisparity_handle),
                    lrCheckDisparity_memRec,NULL,(IALG_Params *)(&lrCheckDisparity_createParams));

            if(status != IALG_EOK)
            {
                lrCheckDisparity_handle= NULL;
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /* Set the end point of the timing measurement for the creation process */
            t1 = _tsc_gettime();
            profile_create_tsc += (t1 - t0 - overhead);

            lrCheckDisparity_handle = (IM_Fxns *) lrCheckDisparity_memRec[0].base;

            /* Use control API to query the optimum output block width and height found by algInit() */

            lrCheckDisparity_ctlInParams.algParams.size= sizeof(DISPARITY_TI_ControlInParams);
            lrCheckDisparity_ctlOutParams.algParams.size= sizeof(DISPARITY_TI_ControlOutParams);

            cmd= DISPARITY_TI_GET_OUTPUT_BLOCK_DIM;
            status = lrCheckDisparity_handle->ivision->algControl((IVISION_Handle)lrCheckDisparity_handle, cmd, (const IALG_Params *)&lrCheckDisparity_ctlInParams, (IALG_Params *)&lrCheckDisparity_ctlOutParams);

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }


            census_inArgs.subFrameInfo = 0;
            census_inArgs.size                  = sizeof(IVISION_InArgs);

            idx = CENSUS_BUFDESC_IN;
            census_inBufs.bufDesc[idx]->numPlanes                          = 1;
            census_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (census_createParams.winWidth - 1)/2;
            census_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (census_createParams.winHeight - 1)/2;

            census_inBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].srcImagePitch;
            census_inBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight + census_createParams.winHeight - 1 + gConfig_stereoVision[t].disparityWinHeight - 1;
            census_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = census_createParams.imgFrameWidth;
            census_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = census_createParams.imgFrameHeight;
            census_inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )census_inputLeft;

            if(census_inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            idx= CENSUS_BUFDESC_OUT;
            census_outBufs.bufDesc[idx]->numPlanes                          = 1;
            census_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
            census_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
            census_outBufs.bufDesc[idx]->bufPlanes[0].width                 = census_createParams.imgFrameWidth;
            census_outBufs.bufDesc[idx]->bufPlanes[0].height                = census_createParams.imgFrameHeight;
            census_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = census_createParams.imgFrameWidth;
            census_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = census_createParams.imgFrameHeight;
            census_outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )disparity_inputLeft;

            tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
            t0 = _tsc_gettime();
#ifndef _CENSUS_FILE
            /* Census transform of left image */
            status = census_handle->ivision->algProcess((IVISION_Handle)census_handle, &census_inBufs,&census_outBufs,&census_inArgs,(IVISION_OutArgs *)&census_outArgs);
#else
            {
                TI_FILE *fid;
                fid = FOPEN("censusLeft.bin", "rb");
                if (fid == NULL)
                    fprintf(stderr, "Error opening file for census\n");
                for(i=0;i< gConfig_stereoVision[t].imageHeight; i++) {
                    FREAD((uint8_t*)census_outBufs.bufDesc[idx]->bufPlanes[0].buf + i*numBytesPerCensus*census_createParams.imgFrameWidth, 1, numBytesPerCensus*gConfig_stereoVision[t].imageWidth, fid);
                }
                FCLOSE(fid);
            }
#endif
            t1 = _tsc_gettime();
            profile_tsc = (t1 - t0 - overhead);
            tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
            overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
            if(overflow) {
                TEST_PRINTF("Counter overflow!!!\n");
            }
            profile_sctm= ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            idx = CENSUS_BUFDESC_IN;
            census_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (census_createParams.winWidth - 1)/2;
            census_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (census_createParams.winHeight - 1)/2;
            census_inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )census_inputRight;
            idx= CENSUS_BUFDESC_OUT;
            census_outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )disparity_inputRight;

            /* For the right frame, in case direction is left-to-right and gConfig_stereoVision[t].offset_x is negative, it means we want to produce disparity values for regions
             * that may be invalid and out of the frame boundary. On PC, access to memory outside of the heap generate segmentation fault type of error.
             * To avoid these errors, we adjust the destination pointer such as it falls within the heap.
             */
            if (disparity_createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT && gConfig_stereoVision[t].offset_x <= 0 && gConfig_stereoVision[t].offset_y <= 0) {
                census_outBufs.bufDesc[idx]->bufPlanes[0].buf= (uint8_t * )census_outBufs.bufDesc[idx]->bufPlanes[0].buf - numBytesPerCensus*(gConfig_stereoVision[t].offset_x + gConfig_stereoVision[t].offset_y*census_createParams.imgFrameWidth);
            }

            tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
            t0 = _tsc_gettime();
#ifndef _CENSUS_FILE
            /* Census transform of right image */
            status = census_handle->ivision->algProcess((IVISION_Handle)census_handle, &census_inBufs,&census_outBufs,&census_inArgs,(IVISION_OutArgs *)&census_outArgs);
#else
            {
                TI_FILE *fid;

                fid = FOPEN("censusRight.bin", "rb");
                if (fid == NULL)
                    fprintf(stderr, "Error opening file for census\n");
                for(i=0;i< gConfig_stereoVision[t].imageHeight; i++) {
                    FREAD((uint8_t*)census_outBufs.bufDesc[idx]->bufPlanes[0].buf + i*numBytesPerCensus*census_createParams.imgFrameWidth, 1, numBytesPerCensus*gConfig_stereoVision[t].imageWidth, fid);
                }
                FCLOSE(fid);
            }
#endif
            t1 = _tsc_gettime();
            profile_tsc+= (t1 - t0 - overhead);
            tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
            overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
            if(overflow) {
                TEST_PRINTF("Counter overflow!!!\n");
            }
            profile_sctm+= ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            /* Set the runtime arguments for the main disparity function */ 
            disparity_inArgs.subFrameInfo = 0;
            disparity_inArgs.size = sizeof(IVISION_InArgs);

            idx = DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE;
            disparity_inBufs.bufDesc[idx]->numPlanes                          = 1;

            if (disparity_createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = disparity_createParams.numDisparities - 1 + (disparity_createParams.winWidth - 1)/2 + gConfig_stereoVision[t].offset_x ;
            }
            else {
                disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (disparity_createParams.winWidth - 1)/2;
            }

            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (disparity_createParams.winHeight - 1)/2 + gConfig_stereoVision[t].offset_y ;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].width                 = census_createParams.imgFrameWidth;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].height                = census_createParams.imgFrameHeight;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )disparity_inputLeft ;

            if(disparity_inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            idx= DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE;
            disparity_inBufs.bufDesc[idx]->numPlanes                          = 1;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (disparity_createParams.winWidth - 1)/2 - gConfig_stereoVision[t].disparityOffset;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (disparity_createParams.winHeight - 1)/2;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].width                 = census_createParams.imgFrameWidth;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].height                = census_createParams.imgFrameHeight;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight;
            disparity_inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )disparity_inputRight ;

            if(disparity_inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }

            idx = DISPARITY_TI_BUFDESC_DISPARITY_OUT;
            disparity_outBufs.bufDesc[idx]->numPlanes                          = 1;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].buf                   = (uint8_t * )dispOutput;

            idx = DISPARITY_TI_BUFDESC_COST_OUT;
            disparity_outBufs.bufDesc[idx]->numPlanes                          = 1;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].buf                   = (uint8_t * )minCostOutput;

            idx = DISPARITY_TI_BUFDESC_PREV_ADJ_COST_OUT;
            disparity_outBufs.bufDesc[idx]->numPlanes                          = 1;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )prevAdjCostOutput;

            idx = DISPARITY_TI_BUFDESC_NEXT_ADJ_COST_OUT;
            disparity_outBufs.bufDesc[idx]->numPlanes                          = 1;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight;
            disparity_outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )nextAdjCostOutput;

            /* In case left-right check is enabled, we need to process another version of the disparity map but this time using opposite
             * search direction and also on a smaller scale image.
             */
            if (gConfig_stereoVision[t].lrCheck== 1) {

                /* Set the runtime arguments for disparity function whose output will be used for LR check */ 
                lrCheckDisparity_inArgs.subFrameInfo = 0;
                lrCheckDisparity_inArgs.size = sizeof(IVISION_InArgs);

                idx = DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE;
                lrCheckDisparity_inBufs.bufDesc[idx]->numPlanes                          = 1;

                if (lrCheckDisparity_createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                    lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = lrCheckDisparity_createParams.numDisparities - 1 + (lrCheckDisparity_createParams.winWidth - 1)/2 + gConfig_stereoVision[t].offset_x ;
                }
                else {
                    lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (lrCheckDisparity_createParams.winWidth - 1)/2;
                }

                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (lrCheckDisparity_createParams.winHeight - 1)/2 + gConfig_stereoVision[t].offset_y ;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].width                 = 2*census_createParams.imgFrameWidth;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].height                = census_createParams.imgFrameHeight/2;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight/2;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )disparity_inputLeft ;

                if(lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx= DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE;
                lrCheckDisparity_inBufs.bufDesc[idx]->numPlanes                          = 1;
                if (lrCheckDisparity_createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                    lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (lrCheckDisparity_createParams.winWidth - 1)/2 - gConfig_stereoVision[t].disparityOffset;
                }
                else {
                    lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (lrCheckDisparity_createParams.winWidth - 1)/2 - gConfig_stereoVision[t].disparityOffset - gConfig_stereoVision[t].offset_x;
                }
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (lrCheckDisparity_createParams.winHeight - 1)/2;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].width                 = 2*census_createParams.imgFrameWidth;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].height                = census_createParams.imgFrameHeight/2;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight/2;
                lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )disparity_inputRight ;

                if(lrCheckDisparity_inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx = DISPARITY_TI_BUFDESC_DISPARITY_OUT;
                lrCheckDisparity_outBufs.bufDesc[idx]->numPlanes                          = 1;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].imageWidth;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight/2;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight/2;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].buf                   = (uint8_t * )lrCheckDispOutput;

                idx = DISPARITY_TI_BUFDESC_COST_OUT;
                lrCheckDisparity_outBufs.bufDesc[idx]->numPlanes                          = 1;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_stereoVision[t].imageWidth;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_stereoVision[t].imageHeight/2;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_stereoVision[t].imageWidth;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_stereoVision[t].imageHeight/2;
                lrCheckDisparity_outBufs.bufDesc[idx]->bufPlanes[0].buf                   = (uint8_t * )lrCheckMinCostOutput;

            }

            tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
            t0 = _tsc_gettime();

            /* Disparity calculation  */
            status = disparity_handle->ivision->algProcess((IVISION_Handle)disparity_handle,
                    &disparity_inBufs,&disparity_outBufs,&disparity_inArgs,(IVISION_OutArgs *)&disparity_outArgs);

            /* In case left-right check is enabled, we need to process another version of the disparity map but this time using opposite
             * search direction and also on a smaller scale image.
             */
            if (gConfig_stereoVision[t].lrCheck== 1) {
                /* Disparity calculation  */
                status = lrCheckDisparity_handle->ivision->algProcess((IVISION_Handle)lrCheckDisparity_handle,
                        &lrCheckDisparity_inBufs,&lrCheckDisparity_outBufs,&lrCheckDisparity_inArgs,(IVISION_OutArgs *)&lrCheckDisparity_outArgs);
            }

            t1 = _tsc_gettime();
            profile_tsc+= (t1 - t0 - overhead);
            tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
            overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
            if(overflow) {
                TEST_PRINTF("Counter overflow!!!\n");
            }
            profile_sctm+= ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));

            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
                goto EXIT_LOOP;
            }


            if (gConfig_stereoVision[t].pattern== 1) {
                fail= validateCensus(
                        census_inputLeft,
                        census_inputRight,
                        disparity_inputLeft,
                        disparity_inputRight - numBytesPerCensus*(gConfig_stereoVision[t].offset_x + gConfig_stereoVision[t].offset_y*census_createParams.imgFrameWidth),
                        refDisparity_inputLeft,
                        refDisparity_inputRight - numBytesPerCensus*(gConfig_stereoVision[t].offset_x + gConfig_stereoVision[t].offset_y*census_createParams.imgFrameWidth),
                        &census_createParams,
                        gConfig_stereoVision[t].srcImagePitch,
                        census_createParams.imgFrameWidth*numBytesPerCensus,
                        left_n_rows,
                        numBytesPerCensus);

                fail|= validateHamDistDisparity(
                        disparity_inputLeft + numBytesPerCensus*(gConfig_stereoVision[t].offset_x + gConfig_stereoVision[t].offset_y*census_createParams.imgFrameWidth),
                        disparity_inputRight - numBytesPerCensus*gConfig_stereoVision[t].disparityOffset,
                        dispOutput,
                        dispRefOutput,
                        minCostOutput,
                        minCostRefOutput,
                        prevAdjCostOutput,
                        nextAdjCostOutput,
                        prevAdjCostRefOutput,
                        nextAdjCostRefOutput,
                        natC_allCostOutput,
                        natC_allCostRLOutput,
                        &census_createParams,
                        &disparity_createParams,
                        gConfig_stereoVision[t].imageWidth,
                        gConfig_stereoVision[t].imageHeight,
                        gConfig_stereoVision[t].dstImagePitch
                );

                statusStr = fail? "FAILED" : "PASSED";
            }
            else {
                statusStr= " N/A  ";
            }

            fflush(stdout);

            result &= fail;

        }
        else {

            statusStr= " N/A  ";

            /* The SAD based stereovision is in natural C code, there is no EVE equivalent implementation available for now
             * It is provided here as a conveninency so one can generate an output from SAD based stereovision to compare with census transform method
             * */
            disparity_createParams.winWidth                      = gConfig_stereoVision[t].disparityWinWidth;
            disparity_createParams.winHeight                     = gConfig_stereoVision[t].disparityWinHeight;
            disparity_createParams.numDisparities                = gConfig_stereoVision[t].numDisparities;
            disparity_createParams.disparityStep                 = gConfig_stereoVision[t].disparityStep;

            computeSADdisparity8bits(
                    census_inputLeft,
                    census_inputRight,
                    dispOutput,
                    minCostOutput,
                    natC_allCostOutput,
                    &disparity_createParams,
                    gConfig_stereoVision[t].imageWidth,
                    gConfig_stereoVision[t].imageHeight,
                    left_n_cols,
                    gConfig_stereoVision[t].dstImagePitch
            );
        }

        if (gConfig_stereoVision[t].gtImage[0]!=0) {
            avgError= computeErrorsGroundTruth(
                    dispOutput,
                    gtImage,
                    diffImage,
                    gConfig_stereoVision[t].imageWidth,
                    gConfig_stereoVision[t].imageHeight,
                    left_n_cols,
                    left_n_rows,
                    disparity_createParams.winWidth -1 + census_createParams.winWidth -1,
                    disparity_createParams.winHeight -1 + census_createParams.winHeight -1,
                    disparity_createParams.numDisparities,
                    gConfig_stereoVision[t].gtScale,
                    &maxDiff);
        }
        else {
            avgError= 0.0;
            maxDiff= 0;
        }

        if (disparity_createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
            dirStr= "LR";
        }
        else {
            dirStr= "RL";
        }

        TEST_PRINTF("%d) %s %dx%d step:(%d,%d), cost %dx%d numDisp:%3d step:%d dir:%s %5s %8.2f %10d %10d %10d %10.2f %20.2f %16.2f       Create graph is %2.2f Mcycles per frame but it is a one-time startup call, output block is %d x %d\n",
                testNum, algoString, census_createParams.winWidth, census_createParams.winHeight, census_createParams.winHorzStep, census_createParams.winVertStep,
                disparity_createParams.winWidth, disparity_createParams.winHeight,
                disparity_createParams.numDisparities, disparity_createParams.disparityStep, dirStr, statusStr, avgError, maxDiff, gConfig_stereoVision[t].imageWidth, gConfig_stereoVision[t].imageHeight,
                (profile_tsc*2.0)/(gConfig_stereoVision[t].imageWidth * gConfig_stereoVision[t].imageHeight),
                (profile_sctm*2.0)/(gConfig_stereoVision[t].imageWidth * gConfig_stereoVision[t].imageHeight),(2.0*profile_tsc)/500000.0, (profile_create_tsc*2.0)/1000000.0, disparity_ctlOutParams.outputBlockWidth, disparity_ctlOutParams.outputBlockHeight);

        fflush(stdout);

        if (gConfig_stereoVision[t].enableRectify== 1) {
            i = strlen((const char *)gConfig_stereoVision[t].outImage);
            memcpy(filepath2, gConfig_stereoVision[t].outImage, i - 4);
            filepath2[i - 4] = 0;

            sprintf(filepath, "../testvecs/%s_left_rectified.pgm", filepath2, gConfig_stereoVision[t].outImage);
            writeFile_PGM((const int8_t *)filepath,
                    census_inputLeft,
                    gConfig_stereoVision[t].remapHeight,
                    gConfig_stereoVision[t].remapWidth,
                    NULL,
                    255);

            sprintf(filepath, "../testvecs/%s_right_rectified.pgm", filepath2, gConfig_stereoVision[t].outImage);
            writeFile_PGM((const int8_t *)filepath,
                    census_inputRight,
                    gConfig_stereoVision[t].remapHeight,
                    gConfig_stereoVision[t].remapWidth,
                    NULL,
                    255);
        }

        if (algoString== censusString){
            /* Write output pgmfile */
            convertCensus32bitsTo8bits((uint32_t*)disparity_inputLeft, disparity_inputLeft8bits, census_createParams.imgFrameWidth*census_createParams.imgFrameHeight);
            convertCensus32bitsTo8bits((uint32_t*)disparity_inputRight, disparity_inputRight8bits, census_createParams.imgFrameWidth*census_createParams.imgFrameHeight);

            i = strlen((const char *)gConfig_stereoVision[t].outImage);
            memcpy(filepath2, gConfig_stereoVision[t].outImage, i - 4);
            filepath2[i - 4] = 0;

            sprintf(filepath, "../testvecs/%s_left_census.pgm", filepath2, gConfig_stereoVision[t].outImage);
            writeFile_PGM((const int8_t *)filepath,
                    disparity_inputLeft8bits,
                    census_createParams.imgFrameHeight,
                    census_createParams.imgFrameWidth,
                    NULL,
                    255);

            sprintf(filepath, "../testvecs/%s_right_census.pgm", filepath2, gConfig_stereoVision[t].outImage);
            writeFile_PGM((const int8_t *)filepath,
                    disparity_inputRight8bits,
                    census_createParams.imgFrameHeight,
                    census_createParams.imgFrameWidth,
                    NULL,
                    255);
        }
#ifdef YUV_OUTPUT
#if 0
        convertDisparityFalseColorYUV444(
                dispImage_red,
                dispImage_grn,
                dispImage_blu,
                dispOutput,
                minCostOutput,
                gConfig_stereoVision[t].dstImagePitch,
                gConfig_stereoVision[t].imageHeight,
                disparity_createParams.numDisparities,
                gConfig_stereoVision[t].maxMinCostRatio);
#else
        convertDisparityFalseColorYUV420SP(
                dispImage_red,
                dispImage_grn,
                dispOutput,
                minCostOutput,
                gConfig_stereoVision[t].dstImagePitch,
                gConfig_stereoVision[t].imageHeight,
                disparity_createParams.numDisparities,
                gConfig_stereoVision[t].maxMinCostRatio);
#endif
        /* Write output pgmfile for disparity */
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision[t].outImage);

        writeFile_PGM((const int8_t *)filepath,
                dispOutput,
                gConfig_stereoVision[t].imageHeight,
                gConfig_stereoVision[t].dstImagePitch,
                NULL,
                255);

        /* Write output pgmfile */
        sprintf(filepath, "../testvecs/%s.pgm", gConfig_stereoVision[t].outImage);

        // changes the .pgm extension to .yuv
        i = strlen(filepath);
        filepath[i-3] = 'y';
        filepath[i-2] = 'u';
        filepath[i-1] = 'v';

        /* Write output yuv */
#if 0
        writeFile_YUV444((const int8_t *)filepath,
                dispImage_red,
                dispImage_grn,
                dispImage_blu,
                gConfig_stereoVision[t].imageHeight,
                gConfig_stereoVision[t].dstImagePitch,
                NULL,
                255);
#else
        writeFile_YUV420SP((const int8_t *)filepath,
                dispImage_red,
                dispImage_grn,
                gConfig_stereoVision[t].imageHeight,
                gConfig_stereoVision[t].dstImagePitch,
                NULL,
                255);
#endif
#else
        convertDisparityFalseColor(
                dispImage_red,
                dispImage_grn,
                dispImage_blu,
                dispOutput,
                minCostOutput,
                gConfig_stereoVision[t].dstImagePitch,
                gConfig_stereoVision[t].imageHeight,
                disparity_createParams.numDisparities,
                gConfig_stereoVision[t].maxMinCostRatio);

        /* Write output pgmfile */
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision[t].outImage);

        writeFile_PGM((const int8_t *)filepath,
                dispOutput,
                gConfig_stereoVision[t].imageHeight,
                gConfig_stereoVision[t].dstImagePitch,
                NULL,
                255);

        // changes the .pgm extension to .ppm
        i = strlen(filepath);
        filepath[i-2] = 112; //"p";

        /* Write output ppmfile */
        writeFile_PPM((const int8_t *)filepath,
                dispImage_red,
                dispImage_grn,
                dispImage_blu,
                gConfig_stereoVision[t].imageHeight,
                gConfig_stereoVision[t].dstImagePitch,
                NULL,
                255);

        if (gConfig_stereoVision[t].lrCheck== 1) {
            convertDisparityFalseColor(
                    dispImage_red,
                    dispImage_grn,
                    dispImage_blu,
                    lrCheckDispOutput,
                    lrCheckMinCostOutput,
                    gConfig_stereoVision[t].dstImagePitch,
                    gConfig_stereoVision[t].imageHeight/2,
                    disparity_createParams.numDisparities,
                    gConfig_stereoVision[t].maxMinCostRatio);

            /* Write output pgmfile */
            sprintf(filepath, "../testvecs/%s.pgm", gConfig_stereoVision[t].outImage);

            // Replace '.pgm' with '__lr' or '__rl' in the filename
            i = strlen(filepath);
            if (lrCheckDisparity_createParams.searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
                filepath[i-8] = '_'; 
                filepath[i-7] = '_'; 
                filepath[i-6] = 'l'; 
                filepath[i-5] = 'r'; 
            }
            else {
                filepath[i-8] = '_'; 
                filepath[i-7] = '_'; 
                filepath[i-6] = 'r'; 
                filepath[i-5] = 'l'; 
            }

            writeFile_PGM((const int8_t *)filepath,
                    lrCheckDispOutput,
                    gConfig_stereoVision[t].imageHeight/2,
                    gConfig_stereoVision[t].dstImagePitch,
                    NULL,
                    255);

            // changes the .pgm extension to .ppm
            i = strlen(filepath);
            filepath[i-2] = 112; //"p";

            /* Write output ppmfile */
            writeFile_PPM((const int8_t *)filepath,
                    dispImage_red,
                    dispImage_grn,
                    dispImage_blu,
                    gConfig_stereoVision[t].imageHeight/2,
                    gConfig_stereoVision[t].dstImagePitch,
                    NULL,
                    255);
        }

        /* Write output cost pgmfile */
        sprintf(filepath, "../testvecs/%s.bin", gConfig_stereoVision[t].outImage);

        // Replace '.pgm' with 'Cost' in the filename
        i = strlen(filepath);
        filepath[i-8] = 'C'; 
        filepath[i-7] = 'o'; 
        filepath[i-6] = 's'; 
        filepath[i-5] = 't'; 

        /* Write output adjacent cost and minimum costs */
        {
            TI_FILE *fid;
            fid = FOPEN(filepath, "wb");
            if (fid == NULL)
                fprintf(stderr, "Error opening file for cost\n");
            for(i=0;i< gConfig_stereoVision[t].imageHeight; i++) {
                FWRITE((uint8_t*)prevAdjCostOutput + i*2*gConfig_stereoVision[t].imageWidth, 1, 2*gConfig_stereoVision[t].imageWidth, fid);
            }

            for(i=0;i< gConfig_stereoVision[t].imageHeight; i++) {
                FWRITE((uint8_t*)minCostOutput + i*2*gConfig_stereoVision[t].imageWidth, 1, 2*gConfig_stereoVision[t].imageWidth, fid);
            }

            for(i=0;i< gConfig_stereoVision[t].imageHeight; i++) {
                FWRITE((uint8_t*)nextAdjCostOutput + i*2*gConfig_stereoVision[t].imageWidth, 1, 2*gConfig_stereoVision[t].imageWidth, fid);
            }
            FCLOSE(fid);
        }

#endif
        /* Write diff image if ground truth was available */

        if (gConfig_stereoVision[t].gtImage[0]!=0) {

            i = strlen((const char *)gConfig_stereoVision[t].outImage);
            memcpy(filepath2, gConfig_stereoVision[t].outImage, i - 4);
            filepath2[i - 4] = 0;

            sprintf(filepath, "../testvecs/%s_diff_gt.pgm", filepath2);
            writeFile_PGM((const int8_t *)filepath,
                    diffImage,
                    gConfig_stereoVision[t].imageHeight,
                    gConfig_stereoVision[t].dstImagePitch,
                    NULL,
                    255);
        }


        EXIT_LOOP:

        if (algoString== censusString){
            /* Free these things only if the algorithm  was census algorithm. The SAD version is all pure natural C so doesn't conform with iVision and doesn't need all these book-keeping*/
            if (census_handle != NULL) {
                status = census_handle->ivision->ialg.algFree((IALG_Handle)(census_handle), census_memRec);
                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                }
            }

            /* Here Free memory for all the mem records */
            status = TestApp_FreeMemRecords(census_memRec,census_numMemRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
            }

            if ( census_memRec != NULL )
            {
                free(census_memRec);
            }

            if (disparity_handle != NULL) {
                status = disparity_handle->ivision->ialg.algFree((IALG_Handle)(disparity_handle), disparity_memRec);
                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                }
            }

            /* Here Free memory for all the mem records */
            status = TestApp_FreeMemRecords(disparity_memRec,disparity_numMemRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
            }

            if ( disparity_memRec != NULL )
            {
                free(disparity_memRec);
            }

            if (lrCheckDisparity_handle != NULL) {
                status = lrCheckDisparity_handle->ivision->ialg.algFree((IALG_Handle)(lrCheckDisparity_handle), lrCheckDisparity_memRec);
                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                }
            }

            /* Here Free memory for all the mem records */
            status = TestApp_FreeMemRecords(lrCheckDisparity_memRec, lrCheckDisparity_numMemRec);
            if(status != IALG_EOK)
            {
                PRINT_ERRORE_MSG();
            }

            if ( lrCheckDisparity_memRec != NULL )
            {
                free(lrCheckDisparity_memRec);
            }

        }

        if (dispOutput != NULL)
        {
            free(dispOutput);
        }

        if (lrCheckDispOutput != NULL)
        {
            free(lrCheckDispOutput);
        }

        if (dispImage_red != NULL)
        {
            free(dispImage_red);
        }

        if (dispImage_grn != NULL)
        {
            free(dispImage_grn);
        }

        if (dispImage_blu != NULL)
        {
            free(dispImage_blu);
        }

        if (minCostOutput != NULL)
        {
            free(minCostOutput);
        }

        if (prevAdjCostOutput != NULL)
        {
            free(prevAdjCostOutput);
        }

        if (nextAdjCostOutput != NULL)
        {
            free(nextAdjCostOutput);
        }

        if (census_inputLeft != NULL)
        {
            free(census_inputLeft);
        }

        if (census_inputRight != NULL)
        {
            free(census_inputRight);
        }

        if (remap_inputLeft != NULL)
        {
            free(remap_inputLeft);
        }

        if (remap_inputRight != NULL)
        {
            free(remap_inputRight);
        }

        if (gtImage != NULL)
        {
            free(gtImage);
        }

        if (diffImage != NULL)
        {
            free(diffImage);
        }

        if (disparity_inputLeft != NULL)
        {
            free(disparity_inputLeft);
        }

        if (disparity_inputRight != NULL)
        {
            free(disparity_inputRight);
        }

        if (algoString== censusString) {
            if (disparity_inputLeft8bits != NULL)
            {
                free(disparity_inputLeft8bits);
            }

            if (disparity_inputRight8bits != NULL)
            {
                free(disparity_inputRight8bits);
            }
        }

        if (refDisparity_inputLeft != NULL)
        {
            free(refDisparity_inputLeft);
        }

        if (refDisparity_inputRight != NULL)
        {
            free(refDisparity_inputRight);
        }

        if(dispRefOutput != NULL)
        {
            free(dispRefOutput);
        }

        if (minCostRefOutput != NULL)
        {
            free(minCostRefOutput);
        }

        if (prevAdjCostRefOutput != NULL)
        {
            free(prevAdjCostRefOutput);
        }

        if (nextAdjCostRefOutput != NULL)
        {
            free(nextAdjCostRefOutput);
        }

        if(natC_allCostOutput != NULL)
        {
            free(natC_allCostOutput);
        }

        if(natC_allCostRLOutput != NULL)
        {
            free(natC_allCostRLOutput);
        }
    }

    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);

    return result;
}

int main(int argc, char *argv[])
{
    int status = 0;
    uint32_t stackDepth;
    char configFile[FILE_NAME_SIZE]={0};
    char configLine[MAX_CONFIG_LINE_SIZE];
    char configParam[MAX_PARAM_STRING_SIZE];
    int8_t         *LinePtr;
    TI_FILE * fp;
    int32_t         lineNum = -1;
    int32_t         config_cmd;

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

    TEST_PRINTF("\n%-58s %10s %10s %10s %10s %10s %10s %10s %16s    %s\n", \
            "Disparity Algorithm", "Status", "Avg Err", "Max Err", "Width", "Height",  \
            "Total CycPerPix", "VCOP busy CycPerPix","TimePerFr(MSec)", "Comments");

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

            memset(gConfig_stereoVision, 0, sizeof(gConfig_stereoVision));

            status = readparamfile(configFile, &gsTokenMap_stereoVision[0]);
            if(status == -1)
            {
                TEST_PRINTF("Parser Failed");
                return -1 ;
            }

            /* Validate the applet */
            status = test_stereoVision(gConfig_stereoVision, lineNum);
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

#if !(VCOP_HOST_EMULATION)
    /* Get the stack usage */
    stackDepth= profiler_getStackDepth();

    TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s %20s    %s", \
            "Module", "Far data (DDR)", "Stack DMEM", "Near data DMEM", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s", "Disparity calculation", &_algo_fardata_size, 0, &_algo_neardata_size,  &_algo_text_size, 1.0, 0.328, 1.328, "");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s", "BAM fw", &_bam_fardata_size, stackDepth, &_bam_neardata_size,  &_bam_text_size, 0.0, 0.0, 0.0, "");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s", "Starterware", &_starterware_fardata_size, 0, &_starterware_neardata_size,  &_starterware_text_size, 0.0, 0.0, 0.0, "");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s\n", "rtsarp32_v200.lib", &_rts_fardata_size, 0, &_rts_neardata_size,  &_rts_text_size, 0.0, 0.0, 0.0, "");
#endif
    FCLOSE(fp);

    return status;
}
