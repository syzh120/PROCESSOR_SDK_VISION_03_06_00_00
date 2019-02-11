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


/** @file   remap_merge_tb.c
*
*  @brief   This file contains test code for the Remap and Merge Applet
*
*
*  @date   Jan, 2014
*
*  Description
*    This file contains test code to validate the frame level applet Remap and Merge.
*    It also checks the output against c reference outputs and profiles the performance
*    and computes the system overheads.
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
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"
#include "GlobalTypes.h"
#include "baseaddress/vayu/eve/baseaddress.h"
#include "pcache.h"
#include "sctm.h"
#include "bam_common.h"

#include "xdais_types.h"
#include "iremap_merge_ti.h"

#include "remap_test_print.h"
#include "convert_map.h"
#include "remap_common.h"
#include "remap_merge_config.h"
#include "remap_merge_natc.h"

#if (VCOP_HOST_EMULATION)
extern unsigned int smallMap_int[2*640*80];
#ifdef FILE_TEST
extern unsigned int bigMap_int[2*640*480];
#endif
#else
extern far const unsigned int smallMap_int[2*640*80];
#ifdef FILE_TEST
extern far const unsigned int bigMap_int[2*640*480];
#endif
#endif

#define ENABLE_TRACES  (0u)
#define ENABLE_PROFILE (1u)

#define OUTPUT_DUMP    (1u)
#define NATC_COMPARE   (1u)
//#define NATC_DUMP      (1u)


/* Global pointers used by the test application */
char *SRC;
char *SRC_UV;
char *DST;
char *DST_UV;
char *REF_DST;
char *REF_DST_UV;
char *SRC_BLK_MAP;
char *MERGE_FRAME;
char *MERGE_FRAME_UV;
char *ALPHA;

#define REMAP_MERGE_DMEM_SIZE     (7680u)    /* (GRAPH_OBJ_SIZE + GRAPH_SCRATCH_SIZE) */

#define MAX_CONFIG_LINE_SIZE     (300u)
#define MAX_FILE_NAME_SIZE       (200u)
#define MAX_PARAM_STRING_SIZE    (30u)
#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")


/* This will be used for allocation of memory in DMEM*/
#pragma DATA_SECTION (REMAP_MERGE_DMEM_SCRATCH, ".dmemSect");
uint8_t REMAP_MERGE_DMEM_SCRATCH[REMAP_MERGE_DMEM_SIZE];

TIMemObject memObj_DMEM;


#define PRINT_ERRORE_MSG() TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)


extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;


char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}


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

  TI_ResetMemoryHandle(memHdl_DMEM);

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space != IALG_DARAM0) {
        free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;



int remapMergeTest(sRemapMerge_Config *testcaseParams)
{
    /* Parameter structures required to interface with the lib */
    RemapParms     *params;
    RemapStat       stat;
    char            desc[512];
    uint16_t        blockWidth, blockHeight, tileWidth, tileHeight;
    uint8_t         enableTileApproach, numTestcase, testcase, referenceAvailable;
    uint32_t        srcStride, roiWidth, roiHeight, dstStride, srcHeight;
    uint32_t        sizeDstRoi, sizeSrcRoi;
    uint32_t        alphaValue;
    int32_t         blockMap_LEN, numMemRec;
    int32_t         i, j, errorFlag;
    IALG_MemRec    *memRec;
    int32_t         status;
    TI_FILE           *fp;
    eRemapMerge_Approach remapApproach;

#if (ENABLE_PROFILE)
    uint64_t        convertMapTimerDiff, setupTimerDiff, execTimerDiff, execVcopTimerDiff, tsc_start, tsc_end;
    uint32_t        execGraphCycles;
    BAM_Statistics  bamStat;
#endif

    /*-----------------------------------------------------------------
       Pointer to algorithm instance
       -----------------------------------------------------------------*/
    IM_Fxns          *handle;

    /*-----------------------------------------------------------------
        Algorithm parameters memory in stack
       -----------------------------------------------------------------*/
    REMAP_MERGE_TI_CreateParams   createParams;

    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    IVISION_OutArgs   outArgs;
    IVISION_OutBufs   outBufs;
    /*-----------------------------------------------------------------
        For test purpose it is allocated in stack. Application may get
        this descriptors from its buffer manager
        -----------------------------------------------------------------*/
    IVISION_BufDesc   inputBlkBufDesc, lutBlkBufDesc, alphaBlkBufDesc, mergeBlkBufDesc;
    IVISION_BufDesc  *inBufDescList[4];
    IVISION_BufDesc   outputBlkBufDesc;
    IVISION_BufDesc  *outBufDescList[1];

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t          *pDmem;
    TIMemHandle       memHdl_DMEM;


    pDmem       = (uint8_t *)REMAP_MERGE_DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;

    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, REMAP_MERGE_DMEM_SIZE);

    params                              = &createParams.remapParams;
    remapApproach                       = (eRemapMerge_Approach)testcaseParams->remapApproach;

    /* Enable Tile Approach. */
    if(remapApproach == remapMergeTileApproach)
    {
        enableTileApproach = 1;
        numTestcase        = 1;
    }
    /* Enable Bounding Box Approach. */
    else if(remapApproach == remapMergeBBApproach)
    {
        enableTileApproach = 0;
        numTestcase        = 1;
    }
    /* First enable Tile Approach, then Bounding Box Approach. */
    else if(remapApproach == remapMergeTileAndBBApproach)
    {
        enableTileApproach = 1;
        numTestcase        = 2;
    } else
    {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
    }

    /*--------------------------------------------------------------------------*/
    /*Fill create time parameters.                                      */
    /*--------------------------------------------------------------------------*/
    params->maps.isSrcMapFloat          = testcaseParams->isSrcMapFloat;
    params->maps.srcFormat              = testcaseParams->srcFormat;
    params->maps.qShift                 = testcaseParams->mapQshift;
    params->interpolationLuma           = testcaseParams->interpolationLuma;
    params->interpolationChroma         = testcaseParams->interpolationChroma;
    params->rightShift                  = testcaseParams->rightShift;
    params->sat_high                    = testcaseParams->sat_high;
    params->sat_high_set                = testcaseParams->sat_high_set;
    params->sat_low                     = testcaseParams->sat_low;
    params->sat_low_set                 = testcaseParams->sat_low_set;
    createParams.dstFormat              = testcaseParams->dstFormat;
    createParams.enableMerge            = testcaseParams->enableMerge;
    srcStride                           = testcaseParams->srcStride;
    srcHeight                           = testcaseParams->srcHeight;
    dstStride                           = testcaseParams->dstStride;
    roiWidth                            = testcaseParams->roiWidth;
    roiHeight                           = testcaseParams->roiHeight;
    tileWidth                           = testcaseParams->tileWidth;
    tileHeight                          = testcaseParams->tileHeight;

    if(testcaseParams->coordMapList == remapMergeBigMap_int)
    {
#ifdef FILE_TEST
        params->maps.srcMap = bigMap_int;
#endif
    } else if(testcaseParams->coordMapList == remapMergeSmallMap_int)
    {
        params->maps.srcMap = smallMap_int;
    } else
    {
        TEST_PRINTF("Please add to the list of srcMaps\n");
        goto EXIT_LOOP;
    }

    params->maps.srcImageDim.width      = srcStride;
    params->maps.srcImageDim.height     = srcHeight;
    params->maps.mapDim.width           = roiWidth;
    params->maps.mapDim.height          = roiHeight;
    params->maps.inputTileDim.width     = tileWidth;
    params->maps.inputTileDim.height    = tileHeight;

    /*-----------------------------------------------------------------
          Allocate the memory needed for the buffers in external Memory (DDR)
          -----------------------------------------------------------------*/
    if(createParams.enableMerge == 0)
    {
        if ((SRC = (char*)malloc(2*srcStride*srcHeight + 2*2*dstStride*roiHeight))==NULL)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
    } else
    {
        if ((SRC = (char*)malloc(2*srcStride*srcHeight + (2+1+2+2)*dstStride*roiHeight))==NULL)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
    }

    /*-----------------------------------------------------------------
          Partition the allocated memory for the buffers in external Memory (DDR)
          -----------------------------------------------------------------*/
    DST        = SRC + 2*srcStride*srcHeight;
    REF_DST    = DST + 2*dstStride*roiHeight;

    /* For YUV420 Semi-planar define SRC_UV, DST_UV and REF_DST_UV */
    SRC_UV     = SRC     + srcStride*srcHeight;
    DST_UV     = DST     + dstStride*roiHeight;
    REF_DST_UV = REF_DST + dstStride*roiHeight;

    if(createParams.enableMerge == 1)
    {
        MERGE_FRAME     = REF_DST_UV     + dstStride*roiHeight;
        MERGE_FRAME_UV  = MERGE_FRAME    + dstStride*roiHeight;
        ALPHA           = MERGE_FRAME_UV + dstStride*roiHeight;
    }

    if (createParams.dstFormat == YUV_420SP)
    {
        sizeDstRoi = (3*dstStride*roiHeight)/2;
    } else
    {
        sizeDstRoi = dstStride*roiHeight*sizeofFormat(createParams.dstFormat);
    }

    if (params->maps.srcFormat == YUV_420SP)
    {
        sizeSrcRoi = (3*srcStride*srcHeight)/2;
    } else
    {
        sizeSrcRoi = srcStride*srcHeight*sizeofFormat(params->maps.srcFormat);
    }

    /*-----------------------------------------------------------------
          Open Input File. If non existant, fill input with data.
          -----------------------------------------------------------------*/
    fp = FOPEN((char *)testcaseParams->inImage, "rb");
    if(fp == NULL)
    {
        /*-----------------------------------------------------------------
              Fill input with data
              -----------------------------------------------------------------*/
        for (i = 0; i < 2*srcHeight; i++)
        {
            for (j = 0; j < srcStride; j++)
            {
                *((uint8_t*)SRC + i*srcStride + j) = j%srcStride;
            }
        }
    } else
    {
        FREAD(SRC, 1, sizeSrcRoi, fp);
        FCLOSE(fp);
    }

    /*-----------------------------------------------------------------
          Zero out dest buffer
          -----------------------------------------------------------------*/
    for (i = 0; i < 2*dstStride*roiHeight; i++)
    {
        *(DST + i) = 0;
    }

    /*-----------------------------------------------------------------
          Fill Merge and Alpha frame
          -----------------------------------------------------------------*/
    if(createParams.enableMerge == 1)
    {
        alphaValue = 0x10;
        for (i = 0; i < dstStride*roiHeight; i++)
        {
            *(ALPHA + i) = alphaValue;
        }

        for (i = 0; i < 2*dstStride*roiHeight; i++)
        {
            *(MERGE_FRAME + i) = 0xFF;
        }
    }

    /*-----------------------------------------------------------------
                  If numTestcase = 1, run either or Tile or BB Approach only.
            Else if numTestcase = 2, run Tile first, then BB Approach.
        -----------------------------------------------------------------*/
    for(testcase = 0; testcase < numTestcase; testcase++)
    {
        profiler_testCaseInfo((int8_t *)testcaseParams->testCaseName, (int8_t *)testcaseParams->desc,
                              testcaseParams->performanceTestcase);
        printparams(&gsTokenMap_remapMerge[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_remapMerge),
                              sizeof(sRemapMerge_Config));

        profiler_init();

        /* In second iteration, enable Bounding Box Approach. */
        if(testcase == 1)
        {
            enableTileApproach = 0;
        }

        if(enableTileApproach == 0)
        {
            blockWidth                          = testcaseParams->blockWidthBB;
            blockHeight                         = testcaseParams->blockHeightBB;
            params->maps.outputBlockDim.width   = blockWidth;
            params->maps.outputBlockDim.height  = blockHeight;
            blockMap_LEN = convertMap_bbApproach_getMemorysizeBlockMap(&params->maps);
        } else
        {
            blockWidth                          = testcaseParams->blockWidthTile;
            blockHeight                         = testcaseParams->blockHeightTile;
            params->maps.outputBlockDim.width   = blockWidth;
            params->maps.outputBlockDim.height  = blockHeight;
            blockMap_LEN = convertMap_tileApproach_getMemorysizeBlockMap(&params->maps);
        }

        if ( (blockMap_LEN == -1) || (SRC_BLK_MAP = (char*)malloc(blockMap_LEN)) == NULL){
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        stat.collectStatFlag= 0;

#if (ENABLE_PROFILE)
        tsc_start = _tsc_gettime();
#endif
        if(enableTileApproach)
        {
            status =  convertMap_tileApproach(&params->maps, &stat, SRC_BLK_MAP, createParams.enableMerge);
        } else
        {
            status =  convertMap_bbApproach(&params->maps, &stat, SRC_BLK_MAP);
        }

#if (ENABLE_PROFILE)
        tsc_end = _tsc_gettime();
        convertMapTimerDiff = (tsc_end - tsc_start) << 1;
#endif

        if (status == -1) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

#if (ENABLE_PROFILE)
        profiler_initStack(profiler_getSP());
        profiler_start();
#endif

        /*-----------------------------------------------------------------
              Query alogorithm memory requirement using standard IALG interface
              -----------------------------------------------------------------*/
        numMemRec = REMAP_MERGE_TI_VISION_FXNS.ialg.algNumAlloc();
        memRec    = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));

        status    = REMAP_MERGE_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams),
                                                              NULL, memRec);
        if(status != IALG_EOK)
        {
          PRINT_ERRORE_MSG();
          goto EXIT_LOOP;
        }

#if (ENABLE_TRACES)
        TEST_PRINTF("Remap and Merge Applet Create Done\n");
#endif
        /*-----------------------------------------------------------------
              Allocate memory for all the mem records
              Application has to implement the below function
              Refer the example implementation below in this file
              -----------------------------------------------------------------*/
        status = TestApp_AllocMemRecords(memRec, numMemRec);
        if(status != IALG_EOK)
        {
          PRINT_ERRORE_MSG();
          goto EXIT_LOOP;
        }

        /*-----------------------------------------------------------------
              Intialize the algorithm instance with the alocated memory
              and user create parameters
              -----------------------------------------------------------------*/
        status = REMAP_MERGE_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                                            memRec, NULL, (IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
        profiler_end_print(0);
        setupTimerDiff = gTest_TI_profileTsc;
#endif

        handle = (IM_Fxns *)memRec[0].base;

        if(status != IALG_EOK)
        {
          PRINT_ERRORE_MSG();
          goto EXIT_LOOP;
        }
#if (ENABLE_TRACES)
        TEST_PRINTF("Remap and Merge Applet Init Done\n");
#endif

        /*-----------------------------------------------------------------
              Set buffer descriptor pointers array base
              -----------------------------------------------------------------*/
        inArgs.subFrameInfo = 0;
        inArgs.size         = sizeof(IVISION_InArgs);
        outArgs.size        = sizeof(IVISION_OutArgs);

        inBufs.bufDesc      = inBufDescList;
        outBufs.bufDesc     = outBufDescList;

        inBufs.numBufs      = 2;
        outBufs.numBufs     = 1;

        inBufDescList[0]    = &inputBlkBufDesc;
        inBufDescList[1]    = &lutBlkBufDesc;
        inBufDescList[2]    = &mergeBlkBufDesc;
        inBufDescList[3]    = &alphaBlkBufDesc;
        outBufDescList[0]   = &outputBlkBufDesc;

        inputBlkBufDesc.numPlanes                          = 1;
        inputBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)SRC;
        inputBlkBufDesc.bufPlanes[0].width                 = srcStride;
        inputBlkBufDesc.bufPlanes[0].height                = srcHeight;
        inputBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        inputBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
        inputBlkBufDesc.bufPlanes[0].frameROI.width        = srcStride;
        inputBlkBufDesc.bufPlanes[0].frameROI.height       = srcHeight;

        if (params->maps.srcFormat == YUV_420SP)
        {
            inputBlkBufDesc.numPlanes                          = 2;
            inputBlkBufDesc.bufPlanes[1].buf                   = (uint8_t *)SRC_UV;
            inputBlkBufDesc.bufPlanes[1].width                 = srcStride;
            inputBlkBufDesc.bufPlanes[1].height                = srcHeight;
            inputBlkBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
            inputBlkBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;
            inputBlkBufDesc.bufPlanes[1].frameROI.width        = srcStride;
            inputBlkBufDesc.bufPlanes[1].frameROI.height       = srcHeight >> 1;
        }

        lutBlkBufDesc.numPlanes                          = 1;
        lutBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)params->maps.blockMap;
        lutBlkBufDesc.bufPlanes[0].width                 = blockMap_LEN;
        lutBlkBufDesc.bufPlanes[0].height                = 1;
        lutBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        lutBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
        lutBlkBufDesc.bufPlanes[0].frameROI.width        = blockMap_LEN;
        lutBlkBufDesc.bufPlanes[0].frameROI.height       = 1;

        if(createParams.enableMerge == 1)
        {
            inBufs.numBufs      = 4;

            mergeBlkBufDesc.numPlanes                          = 1;
            mergeBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)MERGE_FRAME;
            mergeBlkBufDesc.bufPlanes[0].width                 = dstStride;
            mergeBlkBufDesc.bufPlanes[0].height                = roiHeight;
            mergeBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
            mergeBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
            mergeBlkBufDesc.bufPlanes[0].frameROI.width        = roiWidth;
            mergeBlkBufDesc.bufPlanes[0].frameROI.height       = roiHeight;

            if (createParams.dstFormat == YUV_420SP)
            {
                mergeBlkBufDesc.numPlanes                          = 2;
                mergeBlkBufDesc.bufPlanes[1].buf                   = (uint8_t *)MERGE_FRAME_UV;
                mergeBlkBufDesc.bufPlanes[1].width                 = dstStride;
                mergeBlkBufDesc.bufPlanes[1].height                = roiHeight;
                mergeBlkBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
                mergeBlkBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;
                mergeBlkBufDesc.bufPlanes[1].frameROI.width        = roiWidth;
                mergeBlkBufDesc.bufPlanes[1].frameROI.height       = roiHeight >> 1;
            }

            alphaBlkBufDesc.numPlanes                          = 1;
            alphaBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)ALPHA;
            alphaBlkBufDesc.bufPlanes[0].width                 = dstStride;
            alphaBlkBufDesc.bufPlanes[0].height                = roiHeight;
            alphaBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
            alphaBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
            alphaBlkBufDesc.bufPlanes[0].frameROI.width        = roiWidth;
            alphaBlkBufDesc.bufPlanes[0].frameROI.height       = roiHeight;

        }


        outputBlkBufDesc.numPlanes                          = 1;
        outputBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)DST;
        outputBlkBufDesc.bufPlanes[0].width                 = dstStride;
        outputBlkBufDesc.bufPlanes[0].height                = roiHeight;
        outputBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        outputBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
        outputBlkBufDesc.bufPlanes[0].frameROI.width        = roiWidth;
        outputBlkBufDesc.bufPlanes[0].frameROI.height       = roiHeight;

        if (createParams.dstFormat == YUV_420SP)
        {
            outputBlkBufDesc.numPlanes                          = 2;
            outputBlkBufDesc.bufPlanes[1].buf                   = (uint8_t *)DST_UV;
            outputBlkBufDesc.bufPlanes[1].width                 = dstStride;
            outputBlkBufDesc.bufPlanes[1].height                = roiHeight;
            outputBlkBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
            outputBlkBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;
            outputBlkBufDesc.bufPlanes[1].frameROI.width        = roiWidth;
            outputBlkBufDesc.bufPlanes[1].frameROI.height       = roiHeight >> 1;
        }

#if (ENABLE_TRACES)
        TEST_PRINTF("Processing start \n");
#endif

#if (!VCOP_HOST_EMULATION)
        /* Prefill the cache for better performance */
        EVE_PROGCACHE_Prefetch(EVE_CONTROL, (const uint32_t *)EVE_SCTM_CounterRead, (uint32_t)32768);
#endif

#if (ENABLE_PROFILE)
        profiler_start();
#endif

        /*-----------------------------------------------------------------
              Initiate frame processing
              -----------------------------------------------------------------*/
        status = handle->ivision->algProcess((IVISION_Handle)handle,
                                              &inBufs, &outBufs, &inArgs, &outArgs);

#if (ENABLE_PROFILE)
        profiler_end_print(1);
        execTimerDiff     = gTest_TI_profileTsc;
        execVcopTimerDiff = gTest_TI_profileSctm[0];

        BAM_getStats(NULL, &bamStat);
        execGraphCycles   = bamStat.kernelsExec.lastCycles; //*2; /* Convert to vcop cycles */
#endif

        if(status != IALG_EOK)
        {
          PRINT_ERRORE_MSG();
          goto EXIT_LOOP;
        }
#if (ENABLE_TRACES)
        TEST_PRINTF("Processing End\n");
#endif

#if (ENABLE_PROFILE)
        if(enableTileApproach)
            sprintf(desc, "TILE APPROACH :");
        else
            sprintf(desc, "BB APPROACH :");
#endif

        /* Pass case. */
        errorFlag = 0;

        /*-----------------------------------------------------------------
              First Iteration
              -----------------------------------------------------------------*/
        if(testcase == 0)
        {
#ifdef OUTPUT_DUMP
            fp = FOPEN((char *)testcaseParams->outImage, "wb");

            if(fp == NULL)
            {
                TEST_PRINTF("Unable to open out file");
            } else
            {
                FWRITE(DST, 1, sizeDstRoi, fp);
                FCLOSE(fp);
            }
#endif

            /*-----------------------------------------------------------------
                     Compare the output of the Natural C Remap with the H/W output. It is possible when
                     only Remap is enabled and not Format Convert and Alpha blending. In other cases, check if
                     reference is already available. In both cases, load the reference in REF_DST
                     -----------------------------------------------------------------*/
#ifdef NATC_COMPARE
            if(createParams.enableMerge == 0 && (params->maps.srcFormat == createParams.dstFormat))
            {
                remapNatc((uint8_t*)SRC, (uint8_t*)SRC_UV, (uint8_t*)REF_DST, (uint8_t*)REF_DST_UV, params);
                referenceAvailable = 1;
                sprintf(desc, "%s Bit-matched to generated Natc.", desc);
#ifdef NATC_DUMP
                fp = FOPEN((char *)testcaseParams->refImage, "wb");

                if(fp == NULL)
                {
                    TEST_PRINTF("Unable to open ref file");
                } else
                {
                    FWRITE(REF_DST, 1, sizeDstRoi, fp);
                    FCLOSE(fp);
                }
#endif
            } else
            {
                /* Check if the ref is already available */
                fp = FOPEN((char *)testcaseParams->refImage, "rb");

                if(fp == NULL)
                {
                    errorFlag = 2;
                    referenceAvailable = 0;
                } else
                {

                    FREAD(REF_DST, 1, sizeDstRoi, fp);
                    FCLOSE(fp);
                    referenceAvailable = 1;
                    sprintf(desc, "%s Bit-matched to stored Natc.", desc);
                }

            }
#endif
        }
#ifdef NATC_COMPARE
        /*-----------------------------------------------------------------
              Second Iteration: It is always BB Approach.
              If reference loaded in REF_DST, bit-match with that, else bit-match with Tile output.
              -----------------------------------------------------------------*/
        else if(testcase == 1)
        {
            /* if reference is not available. */
            if(referenceAvailable == 0)
            {
                /*-----------------------------------------------------------------
                              Compare the output of the BB Approach with that of the dumped Tile Approach
                              -----------------------------------------------------------------*/
                fp = FOPEN((char *)testcaseParams->outImage, "rb");

                if(fp == NULL)
                {
                    TEST_PRINTF("Unable to open Tile Remap output");
                    errorFlag = 2;
                }
                if(fp != NULL)
                {
                    FREAD(REF_DST, 1, sizeDstRoi, fp);
                    FCLOSE(fp);
                    sprintf(desc, "%s Bit-matched to Tile output.", desc);
                }
            } else
            {
                sprintf(desc, "%s Bit-matched to stored/generated NATC.", desc);
            }
        }

        /* Bit-match. */
        if(errorFlag != 2)
        {
            for (i = 0; i < sizeDstRoi; i++){
                if (*(DST + i) != *(REF_DST + i)){
                    TEST_PRINTF("Mismatch component #0, offset %d\n", i);
                    errorFlag = 1;
                    break;
                }
            }
        }
#endif

#ifdef OUTPUT_DUMP
        /* If in iteration 2, BB Approach is not bit-matching, dump the output. */
        if(testcase == 1 && errorFlag == 1)
        {
            sprintf((char *)testcaseParams->outImage, "%s_BB", (char *)testcaseParams->outImage);
            fp = FOPEN((char *)testcaseParams->outImage, "wb");

            if(fp == NULL)
            {
                TEST_PRINTF("Unable to open out file");
            } else
            {
                FWRITE(DST, 1, sizeDstRoi, fp);
                FCLOSE(fp);
            }
        }
#endif
#if (ENABLE_PROFILE)
        profiler_printStatus(errorFlag);

        testPrintHeader("Remap and Merge");
        sprintf(desc, "%s %s, Exec time of convertMap(): %6.2f M3 cycles/point", desc, testcaseParams->desc,
               (float)convertMapTimerDiff/(roiWidth*roiHeight));
        if (stat.collectStatFlag) {
            sprintf(desc, "%s, Width min ratio: %3.2f, max ratio: %3.2f, aver ratio: %3.2f - Height min ratio: %3.2f, max ratio: %3.2f, aver ratio: %3.2f",
                    testcaseParams->desc, stat.minWidthRatio, stat.maxWidthRatio, stat.averWidthRatio, stat.minHeightRatio, stat.maxHeightRatio, stat.averHeightRatio);
        }
        testPrintResults(errorFlag, setupTimerDiff, execGraphCycles, execTimerDiff, execVcopTimerDiff,
                         desc, roiWidth*roiHeight);
#endif

        fflush(stdout);

EXIT_LOOP:

        /*-----------------------------------------------------------------
              Call algFree
              -----------------------------------------------------------------*/
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
        if ( SRC_BLK_MAP != NULL )
        {
          free(SRC_BLK_MAP);
        }

#if (ENABLE_PROFILE)
        profiler_getStackDepth();
#endif
    }

    if ( SRC != NULL )
    {
      free(SRC);
    }


    return 0;
}

int main(int argc, char *argv[])
{
  int  status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t   *LinePtr;
  TI_FILE     *fp;
  int32_t  lineNum = -1;
  int32_t  config_cmd;

  report_printAppletInfo((int8_t *)"REMAP_MERGE_TI_VISION");

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s , Runing in default mode \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  while(1)
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
      break;
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);
    if(config_cmd == 0)
    {
      TEST_PRINTF("End of config list found !\n");
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

      status = readparamfile(configFile, &gsTokenMap_remapMerge[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      /* Validate the applet */
      status = remapMergeTest(gConfig_remapMerge);
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

#if (ENABLE_PROFILE)
  testPrintFooter("Remap and Merge");
#endif

  return status;
}


