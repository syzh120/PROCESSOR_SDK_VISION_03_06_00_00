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


/** @file evelib_blockSort_u32_test.c
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
#include "iBlockSort_u32_ti.h"
#include "../vlib/blockSortU32/inc/vcop_sort_cn.h"
#include "blockSort_u32_config.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

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

int test_blockSort_u32(void)
{
    uint32_t i=0, j=0;
    int32_t result = 0;
#ifdef SCAN_DIM
    int notEven= 0, initialWidth= 0;
#endif
    char *statusStr = NULL;

    uint8_t *wbufToZero;
    uint32_t stackDepth;
    uint32_t sizeOutput, sizeInput, numBytes;
    char filepath[256];
    TI_FILE *fid;
    uint32_t t;
    int testnum;
    uint32_t tileSize;
    uint16_t num_horz_tiles, num_vert_tiles, X, Y, x, y;
    uint32_t count;

    uint32_t *input, *tempBlock;
    uint32_t *output;
    uint32_t *refOutput;
    int32_t *natcScratch1, *natcScratch2;
    uint32_t value;

    int fail = 0;

    unsigned int profile_tsc, profile_sctm, profile_create_tsc;

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
    BLOCK_SORT_U32_TI_CreateParams  createParams;

    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    /*-----------------------------------------------------------------
                 For test purpose it is allocated in stack. Application may get
                 this descriptors from its buffer manager
                 -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc;
    IVISION_BufDesc   *inBufDescList[1];

    BLOCK_SORT_U32_TI_outArgs   outArgs;
    IVISION_OutBufs                  outBufs;
    /*-----------------------------------------------------------------
                 For test purpose it is allocated in stack. Application may get
                 this descriptors from its buffer manager
     -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc;
    IVISION_BufDesc   *outBufDescList[1];

    outArgs.iVisionOutArgs.size = sizeof(BLOCK_SORT_U32_TI_outArgs);

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint8_t *pDmem;
    TIMemHandle memHdl_DMEM;

    pDmem = (uint8_t *)&DMEM_SCRATCH;
    memHdl_DMEM = &memObj_DMEM;
    TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

    testnum= 0;

    /* 'natcScratch1', 'natcScratch2' and 'tempBlock'will point to buffers required by the natural C code used for validation purposes.
     * the final application won't need these.
     */
    natcScratch1= (int32_t*)malloc(4*1000);
    assert(natcScratch1 !=NULL);

    natcScratch2= (int32_t*)malloc(4*1000);
    assert(natcScratch2 !=NULL);

    tempBlock= (uint32_t*)malloc(4*BLOCKSORTU32_MAX_ELEMTS);

    for (t=0;t<blockSort_u32_numTestCases;t++) {

        profiler_testCaseInfo((int8_t *)gConfig_blockSort_u32[t].testCaseName, (int8_t *)gConfig_blockSort_u32[t].desc,
                              (uint8_t )gConfig_blockSort_u32[t].performanceTestcase);
        printparams(&gsTokenMap_blockSort_u32[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_blockSort_u32[t]),
                              sizeof(sblockSort_u32_Config));

        profiler_init();

        /* In order to derive stack requirements, call profiler_initStack() which will write DEADBEEF from current stack pointer up to the top */
        profiler_initStack(profiler_getSP());

        /* Allocate input frame buffer */
        sizeInput= gConfig_blockSort_u32[t].srcImagePitch*gConfig_blockSort_u32[t].srcImageHeight;
        input= (uint32_t*)malloc(sizeInput);
        assert(input != NULL);

        /* Allocate output frame buffer */
        sizeOutput= gConfig_blockSort_u32[t].dstImagePitch*gConfig_blockSort_u32[t].srcImageHeight;
        output= (uint32_t*)malloc(sizeOutput);
        assert(output != NULL);

        /* Allocate reference output frame buffer to store natural C function's output */
        refOutput= (uint32_t*)malloc(sizeOutput);
        assert(refOutput != NULL);

        if (gConfig_blockSort_u32[t].pattern== 1) {
            /* Generate random input data */
            srand(1);
            for(i=0; i<sizeInput/4; i++) /*/4 is because size was in bytes where as i will iterates over uitn32_t */
            {
                input[i] = abs(rand());
            }
        }
        else {
            sprintf(filepath, "../testvecs/%s", gConfig_blockSort_u32[t].inImage);
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
        createParams.visionParams.algParams.size   = sizeof(BLOCK_SORT_U32_TI_CreateParams);
        createParams.visionParams.cacheWriteBack   = NULL;
        createParams.imgFrameWidth                 = gConfig_blockSort_u32[t].srcImageWidth;
        createParams.imgFrameHeight                = gConfig_blockSort_u32[t].srcImageHeight;
        createParams.blockWidth                    = gConfig_blockSort_u32[t].blockWidth;
        createParams.blockHeight                   = gConfig_blockSort_u32[t].blockHeight;

        /* The members below are used in single block processing when createParams.blockWidth= createParams.imgFrameWidth
         * and createParams.blockHeight= createParams.imgFrameHeight
         * to specify where the application has written the input data in VCOP internal memory
         * and where the output data should be written to.
         */
#if !(VCOP_HOST_EMULATION)
        createParams.singleBlockSrcAddr= (uint32_t*)vcop_malloc(VCOP_IBUFLA, 2048*4);
        createParams.singleBlockDstAddr= (uint32_t*)vcop_malloc(VCOP_IBUFHA, 2048*4);

        /* Free the memory as we used vcop_malloc() to just obtain the pointer value */
        vcop_free(createParams.singleBlockSrcAddr);
        vcop_free(createParams.singleBlockDstAddr);
#else
        createParams.singleBlockSrcAddr= (uint32_t*)malloc(2048*4);
        createParams.singleBlockDstAddr= (uint32_t*)malloc(2048*4);
#endif
        /*---------------------------------------------------
        Query alogorithm memory requirement using standard IALG interface
        ----------------------------------------------------------------*/
        profiler_start();

        numMemRec = BLOCK_SORT_U32_TI_VISION_FXNS.ialg.algNumAlloc();
        memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

        status = BLOCK_SORT_U32_TI_VISION_FXNS.ialg.algAlloc(
                (IALG_Params *)(&createParams), NULL, memRec);

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

#if ENABLE_TRACES
        TEST_PRINTF("Block Sort Applet Create Done\n");
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
        status = BLOCK_SORT_U32_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
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
        TEST_PRINTF("Block Sort Init Done\n");
#endif

        inArgs.subFrameInfo = 0;
        inArgs.size                  = sizeof(IVISION_InArgs);

        inBufDesc.numPlanes                          = 1;
        inBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        inBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;

        /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
         * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
         * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
         * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
         * at (frameROI.topLeft.x, frameROI.topLeft.y) .
         * */
        inBufDesc.bufPlanes[0].width                 = gConfig_blockSort_u32[t].srcImagePitch;
        inBufDesc.bufPlanes[0].height                = gConfig_blockSort_u32[t].srcImageHeight;
        inBufDesc.bufPlanes[0].frameROI.width        = gConfig_blockSort_u32[t].srcImageWidth<<2; /* convert to bytes */
        inBufDesc.bufPlanes[0].frameROI.height       = gConfig_blockSort_u32[t].srcImageHeight;
        inBufDesc.bufPlanes[0].buf = (uint8_t * )input ;

        if(inBufDesc.bufPlanes[0].buf == NULL)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }


        outBufDesc.numPlanes                          = 1;

        outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
        outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
        outBufDesc.bufPlanes[0].width                 = gConfig_blockSort_u32[t].dstImagePitch;
        outBufDesc.bufPlanes[0].height                = gConfig_blockSort_u32[t].srcImageHeight;
        outBufDesc.bufPlanes[0].frameROI.width        = gConfig_blockSort_u32[t].srcImageWidth<<2; /* convert to bytes */
        outBufDesc.bufPlanes[0].frameROI.height       = gConfig_blockSort_u32[t].srcImageHeight;
        outBufDesc.bufPlanes[0].buf = (uint32_t * )output;


        /* Testing single block processing
         * The testbench detects here whether the frame is only made of a single processing block to sort
         * If yes then, we store the data directly into image buffer and we update params.src and params.dst accordingly.
         * The function EVELIB_blockSort_u32_execute() will automatically detect that a single block needs to be processed
         * and will bypass the usage of EDMA because it will see that  params.src== params.srcImBuf and params.src== params.srcImBuf
         */
        if (createParams.imgFrameWidth== createParams.blockWidth && createParams.imgFrameHeight== createParams.blockHeight) {
            for(i=0;i<createParams.blockHeight; i++) {
                for(j=0;j<createParams.blockWidth; j++) {
                    createParams.singleBlockSrcAddr[i*createParams.blockWidth + j]= input[i*gConfig_blockSort_u32[t].srcImagePitch/4 + j];
                }
            }
            inBufDesc.bufPlanes[0].buf= createParams.singleBlockSrcAddr;
            outBufDesc.bufPlanes[0].buf= createParams.singleBlockDstAddr;
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
        memset(outBufDesc.bufPlanes[0].buf, 0, sizeof(output));
        vcop_minit();
        wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
        memset(wbufToZero, 0, 31*1024);
        vcop_free(wbufToZero);

        /* Second call to EVELIB_blockSort_u32_execute()*/

        /* Testing single block processing
         * The testbench detects here whether the frame is only made of a single processing block to sort
         * If yes then, we store the data directly into image buffer and we update params.src and params.dst accordingly.
         * The function EVELIB_blockSort_u32_execute() will automatically detect that a single block needs to be processed
         * and will bypass the usage of EDMA because it will see that  params.src== params.srcImBuf and params.src== params.srcImBuf
         */
        if (createParams.imgFrameWidth== createParams.blockWidth && createParams.imgFrameHeight== createParams.blockHeight) {
            for(i=0;i<createParams.blockHeight; i++) {
                for(j=0;j<createParams.blockWidth; j++) {
                    createParams.singleBlockSrcAddr[i*createParams.blockWidth + j]= input[i*gConfig_blockSort_u32[t].srcImagePitch/4 + j];
                }
            }
            inBufDesc.bufPlanes[0].buf= createParams.singleBlockSrcAddr;
            outBufDesc.bufPlanes[0].buf= createParams.singleBlockDstAddr;
        }

        /* Prepare to call EVELIB_blockSort_u32_execute() a second time. This time we are going to measure its performance.*/
        profiler_start();
        status = handle->ivision->algProcess((IVISION_Handle)handle,
                &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);
        profiler_end_print(1);

        profile_tsc = gTest_TI_profileTsc;
        profile_sctm = gTest_TI_profileSctm[0];

        if (createParams.imgFrameWidth== createParams.blockWidth && createParams.imgFrameHeight== createParams.blockHeight) {
            for(i=0;i<createParams.blockHeight; i++) {
                for(j=0;j<createParams.blockWidth; j++) {
                    output[i*gConfig_blockSort_u32[t].dstImagePitch/4 + j]= createParams.singleBlockDstAddr[i*createParams.blockWidth + j];
                }
            }
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
        /*  Call the natural C implementation for sorting which results will be used to validate EVELIB_blockSort_u32_execute()'s output            */
        /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
        num_horz_tiles= createParams.imgFrameWidth/createParams.blockWidth;
        num_vert_tiles= createParams.imgFrameHeight/createParams.blockHeight;

        tileSize= createParams.blockWidth*createParams.blockHeight;

        for (Y=0;Y<num_vert_tiles;Y++)
            for(X=0;X<num_horz_tiles; X++) {
                count= 0;
                for (y=0; y<createParams.blockHeight; y++) {
                    for(x=0;x<createParams.blockWidth;x++) {
                        value= input[Y*createParams.blockHeight*gConfig_blockSort_u32[t].srcImagePitch/4 + X*createParams.blockWidth + y*gConfig_blockSort_u32[t].srcImagePitch/4 + x];
                        tempBlock[count]= value;
                        count++;
                    }
                }

                vcop_sort_cn(tileSize, tempBlock, natcScratch1, natcScratch2);

                count= 0;
                for (y=0; y<createParams.blockHeight; y++) {
                    for(x=0;x<createParams.blockWidth;x++) {
                        refOutput[Y*createParams.blockHeight*gConfig_blockSort_u32[t].dstImagePitch/4 + X*createParams.blockWidth + y*gConfig_blockSort_u32[t].dstImagePitch/4 + x]= tempBlock[count];
                        count++;
                    }
                }
            }


        /* Perform the output validation */
        fail = 0;

        for(i=0; i<createParams.imgFrameHeight; i++)
        {
            for(j=0; j<createParams.imgFrameWidth; j++)
            {
                if(output[i*gConfig_blockSort_u32[t].dstImagePitch/4+j] != refOutput[i*gConfig_blockSort_u32[t].dstImagePitch/4+j])
                {
                    fail = 1;
                    //TEST_PRINTF("row:%d, col:%d, out:%u, EOut:%u \n", i, j, output[i*params.dstImagePitch/4+j], refOutput[i*params.dstImagePitch/4+j]);
                }
            }
        }

        profiler_printStatus(fail);

        statusStr = fail? "FAILED" : "PASSED";
        fflush(stdout);

        result = (int32_t)((uint32_t)result & (uint32_t)fail);

        TEST_PRINTF("\n%-30s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
                "Algorithm", "Status", "Width", "Height", "MegaCycPerFr", \
                "MegaCycPerSec(30Fr)", "Total CycPerPix", "VCOP busy CycPerPix","TimePerFr(MSec)", "Comments");

        TEST_PRINTF("%2d) Block Sort %5d points    %10s %10d %10d %15.2f %20.2f %10.2f %20.2f %16.2f       Create graph is an additional %2.2f Mcycles per frame but it is a one-time startup call\n", testnum++, createParams.blockWidth*createParams.blockHeight,
                statusStr, gConfig_blockSort_u32[t].srcImageWidth, gConfig_blockSort_u32[t].srcImageHeight,
                (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0), (profile_tsc)/(gConfig_blockSort_u32[t].srcImageWidth * gConfig_blockSort_u32[t].srcImageHeight),
                (profile_sctm)/(gConfig_blockSort_u32[t].srcImageWidth * gConfig_blockSort_u32[t].srcImageHeight),(profile_tsc/500000.0), (profile_create_tsc)/1000000.0);

        fflush(stdout);

        if (gConfig_blockSort_u32[t].pattern== 0) {
            /* Write output files */
            sprintf(filepath, "../testvecs/%s", gConfig_blockSort_u32[t].outImage);
            fid= FOPEN(filepath,"wb");
            if (fid==NULL) {
                printf("Error, unable to open file %s \n", filepath);
                goto EXIT_LOOP;
            }
            numBytes= FWRITE(outBufDesc.bufPlanes[0].buf, 1, gConfig_blockSort_u32[t].dstImagePitch*createParams.imgFrameHeight, fid);
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

#if !(VCOP_HOST_EMULATION)
        /* Get the stack usage */
        profiler_getStackDepth();
#endif

#if (VCOP_HOST_EMULATION)
        /* Free the memory as we used malloc() to just obtain the pointer values */
        free(createParams.singleBlockSrcAddr);
        free(createParams.singleBlockDstAddr);
#endif
    }

#if !(VCOP_HOST_EMULATION)
    TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s %20s    %s", \
            "Module", "Far data (DDR)", "Stack DMEM", "Near data DMEM", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s", "Block sort algo", &_algo_fardata_size, 0, &_algo_neardata_size,  &_algo_text_size, 1.0, 0.328, 1.328, "");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s", "BAM fw", &_bam_fardata_size, stackDepth, &_bam_neardata_size,  &_bam_text_size, 0.0, 0.0, 0.0, "");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s", "Starterware", &_starterware_fardata_size, 0, &_starterware_neardata_size,  &_starterware_text_size, 0.0, 0.0, 0.0, "");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20d %20.1f %20.1f %20.1f    %s\n", "rtsarp32_v200.lib", &_rts_fardata_size, 0, &_rts_neardata_size,  &_rts_text_size, 0.0, 0.0, 0.0, "");
#endif

    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);

    free(natcScratch1);
    free(natcScratch2);
    free(tempBlock);

    return result;
}

int main(int argc, char *argv[])
{
    int status = 0;
    char configFile[FILE_NAME_SIZE]={0};

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
        strcpy(configFile,"../testvecs/config/blockSort_u32.cfg");
    }

    report_printAppletInfo((int8_t *)"BLOCKSORT_U32_TI_VISION");

    /* Erase gConfig_blockSort_u32 to make sure it doesn't have any settings from previous run */
    memset(gConfig_blockSort_u32, 0, sizeof(gConfig_blockSort_u32));
    status = readparamfile(configFile, &gsTokenMap_blockSort_u32[0]) ;
    if(status == -1)
    {
        printf("Parser Failed");
        return -1 ;
    }

    /* Validate the applet */
    status = test_blockSort_u32();

    return status;
}

