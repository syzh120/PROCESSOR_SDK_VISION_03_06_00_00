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


/*==========================================================================*/
/**
*  @file:      block_statistics_tb.c
*
*  @brief:     Example file that shows the usage of block statistics applet
*
*  @version:   0.2 (Aug 2013) : Added iVision Interface.
*/
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "evestarterware.h"
#include "alg_osal.h"
#include "xdais_types.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"

#include "ti_file_io.h"
#include "iblock_statistics_ti.h"
#include "block_statistics_config.h"
#include "block_statistics_cn.h"

#define ENABLE_TRACES 0

#define PRINT_ERROR_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (16*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
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

int32_t TestApp_FreeMemRecords(IALG_MemRec *memRec, int32_t numMemRec)
{
  int32_t i;
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


char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}


void fillDefaultConfig(sBlockStatistics_Config* params)
{
  strcpy(params->inImg, "");
  strcpy(params->outImg, "");

  params->imageWidth  = 640;
  params->imageHeight = 480;
  params->imagePitch  = 640;

  params->statBlockWidth   = 8;
  params->statBlockHeight  = 8;

  params->randSeed    = 0;
  params->numIter     = 1;

  params->performanceTestcase = 1;
  strcpy((char*)params->testCaseName, " ");
  strcpy((char*)params->testCaseDesc, " ");
}

/**
*******************************************************************************
* @fn       blockStat_compare
* @brief    Function to compare the output with reference
*
* @inputs -  output    : Output from platform
*
* @inputs -  refOutput : Reference output
*
* @return   none
* @param Comments:
*******************************************************************************
*/
uint32_t blockStat_compare(
    BLOCK_STATISTICS_TI_CreateParams *createParams,
    uint8_t *minOutput,
    uint8_t *maxOutput,
    uint16_t *meanOutput,
    uint32_t *varOutput,
    uint8_t *refMinOutput,
    uint8_t *refMaxOutput,
    uint16_t *refMeanOutput,
    uint32_t *refVarOutput)
{
  unsigned int i, num_pix;
  unsigned int pix, RefPix, result = 0;

  num_pix = (createParams->imageWidth/createParams->statBlockWidth) *
            (createParams->imageHeight/createParams->statBlockHeight);

  for(i = 0; i<num_pix; i++) {
    pix     = *minOutput++;
    RefPix  = *refMinOutput++;

    if(pix != RefPix) {
      result |= 1;
    }

    pix     = *maxOutput++;
    RefPix  = *refMaxOutput++;

    if(pix != RefPix) {
      result |= 2;
    }

    pix     = *meanOutput++;
    RefPix  = *refMeanOutput++;

    if(pix != RefPix) {
      result |= 4;
    }

    pix     = *varOutput++;
    RefPix  = *refVarOutput++;

    if(pix != RefPix) {
      result |= 8;
    }

    if(result != 0) {
        TEST_PRINTF("Mismatch at (%d, %d).\n",
                    i/(createParams->imageWidth/createParams->statBlockWidth),
                    i%(createParams->imageWidth/createParams->statBlockWidth));
        break;
    }
  }

  return result;
}


int32_t blockStatisticsTest(sBlockStatistics_Config* params)
{
  uint32_t profile_tsc, profile_sctm, profile_create_tsc;
  uint32_t seed;
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i, j; //k;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t fail = 0;

  uint8_t *input = NULL, *outMinImg = NULL, *outMaxImg = NULL,
          *refOutMin = NULL, *refOutMax = NULL;
  uint16_t *outMeanImg = NULL, *refOutMean = NULL;
  uint32_t *outVarImg = NULL, *refOutVar = NULL;
  uint32_t sizeInput, sizeOutput;
  int16_t imgOutWidth, imgOutHeight;
  uint32_t numBytes;

  char  filepath[256];
  TI_FILE *fid;
  char *statusStr = NULL;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  BLOCK_STATISTICS_TI_CreateParams   createParams;

  IVISION_InArgs inArgs;
  IVISION_InBufs inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc inImgBufDesc;
  IVISION_BufDesc *inBufDescList[BLOCK_STATISTICS_TI_BUFDESC_IN_TOTAL];

  IVISION_OutArgs outArgs;
  IVISION_OutBufs outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc *outBufDescList[BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL];

  outArgs.size = sizeof(IVISION_OutArgs);
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

  inBufs.numBufs  = 1;
  outBufs.numBufs = 1;

  inBufDescList[BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER]  = &inImgBufDesc;
  outBufDescList[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN] = &outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN];
  outBufDescList[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX] = &outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX];
  outBufDescList[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN] = &outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN];
  outBufDescList[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE] = &outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE];

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size = sizeof(BLOCK_STATISTICS_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;
  createParams.imageWidth       = params->imageWidth;
  createParams.imageHeight      = params->imageHeight;
  createParams.statBlockWidth   = params->statBlockWidth;
  createParams.statBlockHeight  = params->statBlockHeight;

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Start\n");
#endif
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();

  numMemRec = BLOCK_STATISTICS_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = BLOCK_STATISTICS_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Block Statistics Applet Create Done\n");
#endif

  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec,numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = BLOCK_STATISTICS_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  profiler_end_print(0);
  profile_create_tsc = gTest_TI_profileTsc;

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Block Statistics Applet Init Done\n");
#endif

  inArgs.subFrameInfo = 0;
  inArgs.size         = sizeof(IVISION_InArgs);

  /* Image buffer input for Block Statistics computation */
  sizeInput = params->imagePitch * params->imageHeight;
  inImgBufDesc.numPlanes = 1;
  inImgBufDesc.bufPlanes[0].frameROI.topLeft.x = 0;
  inImgBufDesc.bufPlanes[0].frameROI.topLeft.y = 0;
  inImgBufDesc.bufPlanes[0].width = params->imagePitch;
  inImgBufDesc.bufPlanes[0].height = params->imageHeight;
  inImgBufDesc.bufPlanes[0].frameROI.width = params->imageWidth;
  inImgBufDesc.bufPlanes[0].frameROI.height = params->imageHeight;

  input = (uint8_t *)malloc(sizeInput);
  inImgBufDesc.bufPlanes[0].buf = input;

  if(inImgBufDesc.bufPlanes[0].buf == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /* Buffer for Block Statistics outputs */
  imgOutWidth = createParams.imageWidth/createParams.statBlockWidth;
  imgOutHeight = createParams.imageHeight/createParams.statBlockHeight;

  sizeOutput = imgOutWidth*imgOutHeight;

 /* Block Minimum */
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].numPlanes = 1;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].frameROI.topLeft.x = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].frameROI.topLeft.y = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].width = imgOutWidth;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].height = imgOutHeight;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].frameROI.width = imgOutWidth;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].frameROI.height = imgOutHeight;

  outMinImg = (uint8_t *)malloc(sizeOutput*sizeof(uint8_t));
  if(outMinImg == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN].bufPlanes[0].buf = outMinImg;

  /* Block Maximum */
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].numPlanes = 1;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].frameROI.topLeft.x = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].frameROI.topLeft.y = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].width = imgOutWidth;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].height = imgOutHeight;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].frameROI.width = imgOutWidth;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].frameROI.height = imgOutHeight;

  outMaxImg = (uint8_t *)malloc(sizeOutput*sizeof(uint8_t));
  if(outMaxImg == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX].bufPlanes[0].buf = outMaxImg;

  /* Block Mean */
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].numPlanes = 1;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].frameROI.topLeft.x = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].frameROI.topLeft.y = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].width = imgOutWidth*sizeof(uint16_t);
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].height = imgOutHeight;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].frameROI.width = imgOutWidth*sizeof(uint16_t);
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].frameROI.height = imgOutHeight;

  outMeanImg = (uint16_t *)malloc(sizeOutput*sizeof(uint16_t));
  if(outMeanImg == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN].bufPlanes[0].buf = (uint8_t*)outMeanImg;

  /* Block Variance */
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].numPlanes = 1;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].frameROI.topLeft.x = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].frameROI.topLeft.y = 0;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].width = imgOutWidth*sizeof(uint32_t);
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].height = imgOutHeight;
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].frameROI.width = imgOutWidth*sizeof(uint32_t);
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].frameROI.height = imgOutHeight;

  outVarImg = (uint32_t *)malloc(sizeOutput*sizeof(uint32_t));
  if(outVarImg == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  outImgBufDesc[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE].bufPlanes[0].buf = (uint8_t*)outVarImg;

  if(strcmp(params->inImg, "")) {
    sprintf(filepath, "../testvecs/input/%s", params->inImg);
    fid = FOPEN(filepath,"rb");
    if(fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    input = (uint8_t *)inImgBufDesc.bufPlanes[0].buf;
    numBytes = FREAD(input, 1, sizeInput, fid);
    assert(numBytes == sizeInput);
    FCLOSE(fid);
  }
  else {
    seed = (params->randSeed == 0) ? _tsc_gettime() : params->randSeed;
    srand(seed);
    TEST_PRINTF("Pattern Generation Seed = %d\n", seed);

    /* Create Random input data in Image Buffer */
    for(i = 0 ; i < params->imageHeight; i++) {
      for(j = 0; j < params->imageWidth; j++) {
        input[i*params->imagePitch + j] =  rand() % 0x100;
      }
    }
  }

  memset(outMinImg, 0, sizeOutput*sizeof(uint8_t));
  memset(outMaxImg, 0, sizeOutput*sizeof(uint8_t));
  memset(outMeanImg, 0, sizeOutput*sizeof(uint16_t));
  memset(outVarImg, 0, sizeOutput*sizeof(uint32_t));

  vcop_minit();
  wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 27*1024);
  memset(wbufToZero, 0xcd, 27*1024);
  vcop_free(wbufToZero);

#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif

  profiler_start();
  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs, &outBufs, &inArgs, &outArgs);
  profiler_end_print(1);

  profile_tsc = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Processing End\n");
#endif


  if(strcmp(params->outImg, "")) {
    /* Write output image */
    sprintf(filepath, "../testvecs/output/%s", params->outImg);
    fid= FOPEN(filepath,"wb");
    if(fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }

    numBytes = FWRITE(outMinImg, 1, sizeOutput, fid);
    assert(numBytes == sizeOutput);

    numBytes = FWRITE(outMaxImg, 1, sizeOutput, fid);
    assert(numBytes == sizeOutput);

    numBytes = FWRITE((uint8_t *)outMeanImg, 2, sizeOutput, fid);
    assert(numBytes == sizeOutput);

    numBytes = FWRITE((uint8_t *)outVarImg, 4, sizeOutput, fid);
    assert(numBytes == sizeOutput);

    FCLOSE(fid);
  }

  /* Allocate reference output buffers */
  refOutMin = (uint8_t *)malloc(sizeOutput*sizeof(uint8_t));
  refOutMax = (uint8_t *)malloc(sizeOutput*sizeof(uint8_t));
  refOutMean = (uint16_t *)malloc(sizeOutput*sizeof(uint16_t));
  refOutVar = (uint32_t *)malloc(sizeOutput*sizeof(uint32_t));
  if((refOutMin == NULL) || (refOutMax == NULL) ||
     (refOutMean == NULL) || (refOutVar == NULL)) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  blockStat_cn(&createParams,
               params->imagePitch,
               input,
               refOutMin,
               refOutMax,
               refOutMean,
               refOutVar);

  fail = blockStat_compare(&createParams,
                  outMinImg,
                  outMaxImg,
                  outMeanImg,
                  outVarImg,
                  refOutMin,
                  refOutMax,
                  refOutMean,
                  refOutVar);

  TEST_PRINTF("\nVCOP cycles consumed for process per frame = %d\n",2*profile_tsc);

  profiler_printStatus(fail);

  statusStr = fail ? "FAILED" : "PASSED";

  TEST_PRINTF("\n%-15s %10s %15s %15s %15s %20s %16s %17s %16s    %s\n", \
    "Algorithm", "Status", "imageWidth", "imageHeight", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

  TEST_PRINTF("%-15s %10s %15d %15d %15.2f %20.2f %16.2f %17.2f %16.2f\
    Create graph is %2.2f MegaCycPerFr (one-time)\n",\
    "BLOCK STATISTICS", statusStr, params->imageWidth, params->imageHeight,\
    (2*profile_tsc/1000000.0), 30*(2*profile_tsc/1000000.0),\
    (profile_tsc*2.0)/(params->imageWidth*params->imageHeight),\
    (profile_sctm*2.0)/(params->imageWidth*params->imageHeight),\
    (2*profile_tsc/500000.0), (profile_create_tsc*2.0)/1000000.0);

  fflush(stdout);

EXIT_LOOP:
  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }
  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec,numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  if(memRec != NULL) {
    free(memRec);
  }
  if(input != NULL) {
    free(input);
  }
  if(outMinImg != NULL) {
    free(outMinImg);
  }
  if(refOutMin != NULL) {
    free(refOutMin);
  }
  if(outMaxImg != NULL) {
    free(outMaxImg);
  }
  if(refOutMax != NULL) {
    free(refOutMax);
  }
  if(outMeanImg != NULL) {
    free(outMeanImg);
  }
  if(refOutMean != NULL) {
    free(refOutMean);
  }
    if(outVarImg != NULL) {
    free(outVarImg);
  }
  if(refOutVar != NULL) {
    free(refOutVar);
  }

  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}


int main(int argc, char *argv[])
{
  int32_t         status = 0;
  TI_FILE         *fp;
  int8_t         *LinePtr;
  int32_t         lineNum = -1;
  int32_t         config_cmd;
  int8_t          configFileName[FILE_NAME_SIZE];
  sBlockStatistics_Config *params;

  report_printAppletInfo((int8_t *)"BLOCK_STATISTICS_TI_VISION");

  params = (sBlockStatistics_Config *)(&gConfig_block_statistics);

  if (argc > 1)
  {
    strcpy((char *)configFileName, argv[1]) ;
  }
  else
  {
    strcpy((char *)configFileName, CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((char *)configFileName , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s , Runing in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    /* Validate the applet */
    status = blockStatisticsTest(params);

    return(status);
  }

  while(1)
  {
    memset(params->configLine, 0, CONFIG_LINE_SIZE);
    status = (int)FGETS(params->configLine, CONFIG_LINE_SIZE, fp);
    LinePtr = (int8_t *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",params->configParam);
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
      LinePtr = (int8_t *)moveToNextElement(params->configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFileName);
      TEST_PRINTF("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile((char *)configFileName, gsTokenMap_block_statistics) ;
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed\n");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)params->testCaseName,
        (int8_t *)params->testCaseDesc, params->performanceTestcase);
      printparams(gsTokenMap_block_statistics, (int32_t)MAX_ITEMS_TO_PARSE,
        (uint32_t)params, sizeof(sBlockStatistics_Config)) ;

      /* Validate the applet */
      status = blockStatisticsTest(params);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      TEST_PRINTF("Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  FCLOSE(fp);

#if VCOP_HOST_EMULATION
    TEST_PRINTF("Press any key to continue ...\n");
    scanf("%c", configFileName);
#endif

  return status;
}

