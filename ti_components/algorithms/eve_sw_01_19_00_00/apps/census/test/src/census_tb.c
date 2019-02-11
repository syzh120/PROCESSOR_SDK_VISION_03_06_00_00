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


/** @file census_test.c
 *
 *  @brief  This file contains test code for census transform applet
 *
 *
 *  @date   24 July 2014
 *
 *  Description
 *    This file contains test code to validate the frame level applet for
 *    census transform. It also checks the output against c reference
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
#include "iCensus_ti.h"
#include "../vlib/vcop_census_8bits/inc/vcop_census_8bits_cn.h"
#include "../vlib/vcop_census_16bits/inc/vcop_census_16bits_cn.h"
#include "census_config.h"
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

int test_census(scensus_Config * gConfig_census, int testNum)
{
    int i=0, j=0, result = 0;
    uint16_t idx;
#ifdef SCAN_DIM
    initialWidth= 0;
#endif
    char *statusStr = NULL;
    unsigned int profile_sctm;
    uint8_t *wbufToZero;
    uint32_t sizeOutput, sizeInput, numBytes;

    char filepath[256];
    TI_FILE *fid;
    uint32_t t;

    uint8_t *input;
    uint8_t *output;
    uint8_t *refOutput;

    int fail = 0;

    unsigned int profile_tsc, profile_create_tsc;
    uint16_t numCensusOrientations, numBytesPerCensus, sizeInputElmt;
    CENSUS_TI_ControlInParams ctlInParams;
    CENSUS_TI_ControlOutParams ctlOutParams;

    int32_t numMemRec;
    IALG_MemRec *memRec;
    int32_t status;
    IALG_Cmd cmd;

    /*-----------------------------------------------------------------
             Pointer to algorithm instance
             -----------------------------------------------------------------*/
    IM_Fxns *     handle= NULL;

    /*-----------------------------------------------------------------
             Algorithm parameters memory in stack
             -----------------------------------------------------------------*/
    CENSUS_TI_CreateParams  createParams;


    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc[CENSUS_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *inBufDescList[CENSUS_BUFDESC_IN_TOTAL];

    CENSUS_TI_outArgs   outArgs;
    IVISION_OutBufs     outBufs;
    /*-----------------------------------------------------------------
             For test purpose it is allocated in stack. Application may get
             this descriptors from its buffer manager
             -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc[CENSUS_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *outBufDescList[CENSUS_BUFDESC_OUT_TOTAL];

    outArgs.iVisionOutArgs.size = sizeof(CENSUS_TI_outArgs);

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

    inBufs.numBufs   = CENSUS_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = CENSUS_BUFDESC_OUT_TOTAL;

    for(i = 0 ; i < CENSUS_BUFDESC_IN_TOTAL ;i++)
    {
        inBufDescList[i]     = &inBufDesc[i];
    }

    for(i = 0 ; i < CENSUS_BUFDESC_OUT_TOTAL ;i++)
    {
        outBufDescList[i]     = &outBufDesc[i];
    }
    profiler_init();
    /* In order to derive stack requirements, call profiler_initStack() which will write DEADBEEF from current stack pointer up to the top */
    profiler_initStack(profiler_getSP());

    for (t=0;t<census_numTestCases;t++) {

        /* Enable SCAN_DIM if you want to vary the width and height of the image for each test case
         * This enable wide coverage of the image dimensions to be tested
         *  */
#ifdef SCAN_DIM
        initialWidth= gConfig_census[t].srcImageWidth;
        while (gConfig_census[t].srcImageHeight >= 64) {
            while (gConfig_census[t].srcImageWidth >= 64) {
#endif

                /* Allocate input buffer based on srcImagePitch and srcImageHeight values.
                 * It is assumed that the pitch value srcImagePitch passed to the testbench already includes (winWidth - 1) extra pixels.
                 * However srcImageHeight represents the ROi's height and is not supposed to include the border pixels and thus the testbench must add these.
                 * */

                sizeInputElmt= (uint32_t)(gConfig_census[t].inputBitDepth + 7) >>3U;
                sizeInput= sizeInputElmt*gConfig_census[t].srcImagePitch*(gConfig_census[t].srcImageHeight + gConfig_census[t].winHeight - 1);

                input= (uint8_t*)malloc(sizeInput);
                assert(input != NULL);

                /* Allocate output and reference output buffer
                 * */

                numCensusOrientations= _CENSUS_WIN_SIZE(gConfig_census[t].winWidth, gConfig_census[t].winHeight, gConfig_census[t].winHorzStep, gConfig_census[t].winVertStep);
                numBytesPerCensus= (numCensusOrientations + 7) >> 3;
                sizeOutput= numBytesPerCensus*gConfig_census[t].dstImagePitch*gConfig_census[t].srcImageHeight;

                output= (uint8_t*)malloc(sizeOutput);
                assert(output != NULL);

                refOutput= (uint8_t*)malloc(sizeOutput);
                assert(refOutput != NULL);

                if (gConfig_census[t].pattern== 1) {
                    /* Generate random input data */
                    srand(1);
                    if (gConfig_census[t].inputBitDepth <= 8) {
                        for(i=0; i<sizeInput; i++)
                        {
                            input[i] = rand() % 256;
                        }
                    }else {
                        for(i=0; i<sizeInput/2; i++)
                        {
                            *((uint16_t*)input + i) = rand() % 65535;
                        }
                    }
                }
                else {
                    sprintf(filepath, "../testvecs/%s", gConfig_census[t].inImage);
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

                profiler_start();
                /***********************************************************************************************************************************/

                /*-----------------------------------------------------------------
                            Set algorithm parameters
                            -----------------------------------------------------------------*/
                createParams.visionParams.algParams.size   = sizeof(CENSUS_TI_CreateParams);
                createParams.visionParams.cacheWriteBack   = NULL;
                createParams.imgFrameWidth                 = gConfig_census[t].srcImageWidth;
                createParams.imgFrameHeight                = gConfig_census[t].srcImageHeight;
                createParams.inputBitDepth                 = gConfig_census[t].inputBitDepth;
                createParams.winWidth                      = gConfig_census[t].winWidth;
                createParams.winHeight                     = gConfig_census[t].winHeight;
                createParams.winHorzStep                   = gConfig_census[t].winHorzStep;
                createParams.winVertStep                   = gConfig_census[t].winVertStep;

                /*---------------------------------------------------
                           Query alogorithm memory requirement using standard IALG interface
                           -----------------------------------------------------------------*/
                numMemRec = CENSUS_TI_VISION_FXNS.ialg.algNumAlloc();
                memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

                status = CENSUS_TI_VISION_FXNS.ialg.algAlloc(
                        (IALG_Params *)(&createParams), NULL, memRec);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

#if ENABLE_TRACES
                TEST_PRINTF("Census transform Applet Create Done\n");
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
                status = CENSUS_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
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
                TEST_PRINTF("Census transform applet Init Done\n");
#endif

                /* Use control API to query the optimum output block width and height found by algInit() */

                ctlInParams.algParams.size= sizeof(CENSUS_TI_ControlInParams);
                ctlOutParams.algParams.size= sizeof(CENSUS_TI_ControlOutParams);

                cmd= CENSUS_GET_OUTPUT_BLOCK_DIM;
                status = handle->ivision->algControl((IVISION_Handle)handle, cmd, (const IALG_Params *)&ctlInParams, (IALG_Params *)&ctlOutParams);

                if(status != IALG_EOK)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                inArgs.subFrameInfo = 0;
                inArgs.size                  = sizeof(IVISION_InArgs);

                idx = CENSUS_BUFDESC_IN;
                inBufs.bufDesc[idx]->numPlanes                          = 1;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = (createParams.winWidth - 1)/2;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = (createParams.winHeight - 1)/2;

                /* Not that EDMA may access pixels outside of the specified image area due to some internal implementation constraints.
                 * the area actually accessed from the topLeft corner will be given by outArgs.activeImgWidth and outArgs.activeImgHeight
                 * It is the application responsibiliy to ensure that inBufDesc.bufPlanes[0].width and inBufDesc.bufPlanes[0].height
                 * are larger enough to enclose the area of dimensions activeImgWidth x activeImgHeight whose top left corner is located
                 * at (frameROI.topLeft.x, frameROI.topLeft.y) .
                 * */
                inBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_census[t].srcImagePitch;
                inBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_census[t].srcImageHeight + (createParams.winHeight - 1)/2;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_census[t].srcImageWidth;
                inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_census[t].srcImageHeight;
                inBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )input ;

                if(inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL)
                {
                    PRINT_ERRORE_MSG();
                    goto EXIT_LOOP;
                }

                idx= CENSUS_BUFDESC_OUT;
                outBufs.bufDesc[idx]->numPlanes                          = 1;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
                outBufs.bufDesc[idx]->bufPlanes[0].width                 = gConfig_census[t].dstImagePitch;
                outBufs.bufDesc[idx]->bufPlanes[0].height                = gConfig_census[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = gConfig_census[t].srcImageWidth;
                outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = gConfig_census[t].srcImageHeight;
                outBufs.bufDesc[idx]->bufPlanes[0].buf = (uint8_t * )output;

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
                memset(output, 0, sizeof(output));
                vcop_minit();
                wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
                memset(wbufToZero, 0, 31*1024);
                vcop_free(wbufToZero);

                /* Prepare to call EVELIB_census_execute() a second time. This time we are going to measure its performance.*/
                profiler_start();
                status = handle->ivision->algProcess((IVISION_Handle)handle,
                        &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);
                profiler_end_print(1);

                profile_tsc = gTest_TI_profileTsc;
                profile_sctm = gTest_TI_profileSctm[0];

                /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                /*  Call the natural C implementation for census transfrom which results will be used to validate EVE's output                                         */
                /*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
                if (gConfig_census[t].inputBitDepth <= 8) {
                    vcop_census_8bits_cn(
                            input,
                            refOutput,
                            createParams.winWidth,
                            createParams.winHeight,
                            createParams.winHorzStep,
                            createParams.winVertStep,
                            gConfig_census[t].srcImageWidth,
                            gConfig_census[t].srcImageHeight,
                            gConfig_census[t].srcImagePitch,
                            gConfig_census[t].dstImagePitch*numBytesPerCensus
                    );
                }
                else {
                    vcop_census_16bits_cn(
                            (uint16_t*)input,
                            refOutput,
                            createParams.winWidth,
                            createParams.winHeight,
                            createParams.winHorzStep,
                            createParams.winVertStep,
                            gConfig_census[t].srcImageWidth,
                            gConfig_census[t].srcImageHeight,
                            gConfig_census[t].srcImagePitch,
                            gConfig_census[t].dstImagePitch*numBytesPerCensus
                    );
                }

                fail = 0;

                for(i=0; i<gConfig_census[t].srcImageHeight; i++)
                {
                    for(j=0; j<gConfig_census[t].srcImageWidth * numBytesPerCensus; j++)
                    {
                        if(output[i*gConfig_census[t].dstImagePitch*numBytesPerCensus+j] != refOutput[i*gConfig_census[t].dstImagePitch*numBytesPerCensus+j])
                        {
                            fail = 1;
                            TEST_PRINTF("level:0, row:%d, col:%d, out:%u, EOut:%u \n", i, j, output[i*gConfig_census[t].dstImagePitch*numBytesPerCensus+j], refOutput[i*gConfig_census[t].dstImagePitch*numBytesPerCensus+j]);
                            break;
                        }
                    }
                }

                statusStr = fail? "FAILED" : "PASSED";
                fflush(stdout);

                result= (int32_t)((uint32_t)result & (uint32_t)fail);

                TEST_PRINTF("%d) Census %2d bits %dx%d hStep:%d vStep:%d  %5s %10d %10d %15.2f %20.2f %10.2f %20.2f %16.2f       Create graph is %2.2f Mcycles per frame but it is a one-time startup call, census length: %d bytes, output block is %d x %d\n", testNum, createParams.inputBitDepth, createParams.winWidth, createParams.winHeight,
                        createParams.winHorzStep, createParams.winVertStep, statusStr, gConfig_census[t].srcImageWidth, gConfig_census[t].srcImageHeight,
                        (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0), (profile_tsc*1.0)/(gConfig_census[t].srcImageWidth * gConfig_census[t].srcImageHeight),
                        (profile_sctm*1.0)/(gConfig_census[t].srcImageWidth * gConfig_census[t].srcImageHeight),(profile_tsc/500000.0), (profile_create_tsc*1.0)/1000000.0, outArgs.numBytesPerCensus, ctlOutParams.outputBlockWidth, ctlOutParams.outputBlockHeight);

                fflush(stdout);

                profiler_printStatus(fail ? -1 : 0);

                if (gConfig_census[t].pattern== 0) {
                    /* Write output file */
                    sprintf(filepath, "../testvecs/%s", gConfig_census[t].outImage);
                    fid= FOPEN(filepath,"wb");
                    if (fid==NULL) {
                        printf("Error, unable to open file %s \n", filepath);
                        goto EXIT_LOOP;
                    }
                    numBytes= FWRITE(output, 1, gConfig_census[t].dstImagePitch*gConfig_census[t].srcImageHeight*numBytesPerCensus, fid);
                    FCLOSE(fid);
                }

                EXIT_LOOP:
                if (handle!=NULL) {
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

                if(refOutput != NULL)
                {
                    free(refOutput);
                }
 /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
                profiler_getStackDepth();
#endif

#ifdef SCAN_DIM
                gConfig_census[t].srcImageWidth -= 16;
            }
            gConfig_census[t].srcImageWidth= initialWidth;
            gConfig_census[t].srcImageHeight -= 2;
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

    report_printAppletInfo((int8_t *)"CENSUS_TI_VISION");

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

        status = readparamfile(configFile, &gsTokenMap_census[0]);
        if(status == -1)
        {
          TEST_PRINTF("Parser Failed");
          return -1 ;
        }

        profiler_testCaseInfo((int8_t *)gConfig_census[0].testCaseName, (int8_t *)gConfig_census[0].desc,
                gConfig_census[0].performanceTestcase);
        printparams(&gsTokenMap_census[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_census),
                sizeof(scensus_Config));

        /* Validate the applet */
        status = test_census(gConfig_census, lineNum);
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
