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


/** @file soft_isp_tb.c
*
*  @brief  This file contains test code for software Image Signal Processor
*          (soft ISP) applet
*
*  @date   April 2014
*
*  Description
*    This file contains test code to validate the frame level applet for
*    performing software Image Signal Processor (ISP). It checks the
*    output against c reference outputs and profiles the performance and
*    computes the system overheads.
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
#include "soft_isp_config.h"
#include "xdais_types.h"
#include "isoft_isp_ti.h"
#include "soft_isp_ref_cn.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

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

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
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


void fillDefaultConfig(sSoftIsp_Config * params)
{
  strcpy(params->inImg, "");
  strcpy(params->gbceToneCurve, "testvecs/input/gbceToneCurve.bin");
  strcpy(params->outImg, "");

  params->imageWidth  = 1284;
  params->imageHeight = 724;
  params->imagePitch  = 1284;

  params->rPosition      = 1;
  params->sensorBitDepth = 12;
  params->maxPixValue    = 3712;

  params->enableDecompand = 0;
  params->pout1           = 2048;
  params->pout2           = 2944;
  params->slope1          = 16;
  params->slope2          = 16;

  params->blackClamp[0]   = 0;
  params->cBalanceGain[0] = 1;

  params->blackClamp[1]   = 0;
  params->cBalanceGain[1] = 1;

  params->blackClamp[2]   = 0;
  params->cBalanceGain[2] = 1;

  params->blackClamp[3]   = 0;
  params->cBalanceGain[3] = 1;

  params->cBalanceShift = 0;

  params->enableExtractR = 0;

  params->enableStats     = 0;
  params->statBlkWidth    = 80;
  params->statBlkHeight   = 45;
  params->saturationLimit = 3500;

  params->gbceMethod  = 0;

  params->randSeed    = 0;
  params->numIter     = 1;


  params->performanceTestcase = 1;
  strcpy((char*)params->testCaseName, " ");
  strcpy((char*)params->testCaseDesc, " ");
}


int32_t softIspTest(sSoftIsp_Config * params)
{
  uint32_t profile_tsc, profile_sctm, profile_create_tsc;
  uint32_t seed;
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i, j; //k;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t fail = 0;

  uint16_t *input = NULL;
  uint8_t *pGbceToneCurve_1c = NULL, *pGbceToneCurve_4c = NULL;
  uint8_t *output = NULL, *refOutput = NULL;
  uint8_t *outputR = NULL, *refOutputR = NULL;
  uint8_t *statsOut = NULL, *refStatsOut = NULL;
  uint32_t sizeInput, sizeOutput, sizeStatsBuf;

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
  SOFT_ISP_TI_CreateParams   createParams;

  SOFT_ISP_TI_InArgs inArgs;
  IVISION_InBufs     inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inImgBufDesc;
  IVISION_BufDesc   *inBufDescList[SOFT_ISP_TI_BUFDESC_IN_TOTAL];

  SOFT_ISP_TI_OutArgs outArgs;
  IVISION_OutBufs     outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[SOFT_ISP_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(SOFT_ISP_TI_OutArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;


  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);


  TEST_PRINTF("\n%-15s %10s %15s %15s %15s %20s %16s %17s %16s    %s\n", \
    "Algorithm", "Status", "imageWidth", "imageHeight", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs  = 1;
  outBufs.numBufs = 1;

  inBufDescList[0]     = &inImgBufDesc;
  outBufDescList[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE] = &outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE];
  outBufDescList[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF] = &outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF];
  outBufDescList[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE] = &outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE];

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size = sizeof(SOFT_ISP_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;
  createParams.imageWidth             = params->imageWidth;
  createParams.imageHeight            = params->imageHeight;
  createParams.enableExtractR         = params->enableExtractR;
  createParams.enableStats            = params->enableStats;
  createParams.statBlkWidth           = params->statBlkWidth;
  createParams.statBlkHeight          = params->statBlkHeight;

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Start\n");
#endif
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();

  numMemRec = SOFT_ISP_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = SOFT_ISP_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Software ISP Applet Create Done\n");
#endif

  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = SOFT_ISP_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  profiler_end_print(0);
  profile_create_tsc = gTest_TI_profileTsc;

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Software ISP Applet Init Done\n");
#endif

  status = handle->ivision->algControl((IVISION_Handle)handle,TI_SOFT_ISP_CONTROL_GET_BUF_SIZE,
    (IALG_Params *)(&createParams),(IALG_Params *)(&createParams));
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.iVisionInArgs.size         = sizeof(SOFT_ISP_TI_InArgs);

  /* Image buffer input to the ISP */
  sizeInput = sizeof(uint16_t)*params->imagePitch * createParams.minInputBufHeight + createParams.extraInputMem;
  inImgBufDesc.numPlanes       = 1;
  inImgBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  inImgBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
  inImgBufDesc.bufPlanes[0].width   = params->imagePitch;
  inImgBufDesc.bufPlanes[0].height  = createParams.minInputBufHeight;
  inImgBufDesc.bufPlanes[0].frameROI.width        = params->imageWidth;
  inImgBufDesc.bufPlanes[0].frameROI.height       = params->imageHeight;

  input = (uint16_t *)malloc(sizeInput);
  inImgBufDesc.bufPlanes[SOFT_ISP_TI_BUFDESC_IN_RCCC_IMAGE].buf = (uint8_t *)input;

  if(inImgBufDesc.bufPlanes[SOFT_ISP_TI_BUFDESC_IN_RCCC_IMAGE].buf == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /* Buffer for Software ISP output */
  sizeOutput = createParams.minOutputBufStride*createParams.minOutputBufHeight;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].numPlanes      = 1;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].frameROI.topLeft.x = 0;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].frameROI.topLeft.y = 0;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].width    = createParams.minOutputBufStride;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].height   = createParams.minOutputBufHeight;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].frameROI.width     = params->imageWidth - 4;
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].frameROI.height    = params->imageHeight - 4;

  output = (uint8_t *)malloc(sizeOutput);
  if(output == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].buf = output;

  /* Buffer for Statistics Collection */
  if(params->enableStats == 1) {
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].numPlanes = 1;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].width   = createParams.statBufStride;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].height  = createParams.statBufHeight;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].frameROI.width     = createParams.statBlkWidth;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].frameROI.height    = createParams.statBufHeight;

    sizeStatsBuf = createParams.statBufStride * createParams.statBufHeight;
    statsOut = (uint8_t*)malloc(sizeStatsBuf);
    if(statsOut == NULL)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF].bufPlanes[0].buf = statsOut;
  }

  /* Buffer for R pixel output */
  if(params->enableExtractR == 1) {
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].numPlanes = 1;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].frameROI.topLeft.x = 0;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].frameROI.topLeft.y = 0;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].width   = createParams.minOutputBufStride/2;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].height  = createParams.minOutputBufHeight/2;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].frameROI.width     = (params->imageWidth - 4)/2;
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].frameROI.height    = (params->imageHeight - 4)/2;

    outputR = (uint8_t *)malloc(sizeOutput/4);
    if(outputR == NULL)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
    outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE].bufPlanes[0].buf = outputR;
  }

  if(strcmp(params->inImg, ""))
  {
    sprintf(filepath, "../testvecs/input/%s", params->inImg);
    fid = FOPEN(filepath,"rb");
    if(fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    input = (uint16_t *)inImgBufDesc.bufPlanes[0].buf;

    memset(input, 0, sizeInput);

    for(i = 0; i < params->imageHeight; i++) {
      numBytes = FREAD(input + i*params->imagePitch, 2, params->imageWidth, fid);
      assert(numBytes == params->imageWidth);
    }
    FCLOSE(fid);
  }
  else
  {
    seed = (params->randSeed == 0) ? _tsc_gettime() : params->randSeed;
    srand(seed);
    TEST_PRINTF("Pattern Generation Seed = %d\n", seed);

    /* Create Random input data in Image Buffer */
    for(i = 0 ; i < params->imageHeight; i++) {
      for(j = 0; j < params->imageWidth; j++) {
        input[i*params->imagePitch + j] =  rand() % (params->maxPixValue + 1);
      }
    }
  }

  if(strcmp(params->gbceToneCurve, ""))
  {
    sprintf(filepath, "../testvecs/input/%s", params->gbceToneCurve);
    fid = FOPEN(filepath,"rb");
    if(fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    pGbceToneCurve_1c = (uint8_t *)malloc(4096);
    numBytes = FREAD(pGbceToneCurve_1c, 1, 4096, fid);
    assert(numBytes == 4096);

    FCLOSE(fid);
    TEST_PRINTF("Custom GBCE curve\n");
  }
  else
  {
    /* Use default linear GBCE table */
    pGbceToneCurve_1c = (uint8_t *)malloc(4096);
    for(i = 0 ; i < 4096; i++) {
      pGbceToneCurve_1c[i] =  i >> 4;
    }
    TEST_PRINTF("Linear GBCE curve\n");
  }

  /* Replicate to 4 Table LUT format */
  pGbceToneCurve_4c = (uint8_t *)malloc(4*4096);
  for(i = 0; i < 4096; i++) {
    pGbceToneCurve_4c[32*(i/8) + (i%8)]      = pGbceToneCurve_1c[i];
    pGbceToneCurve_4c[32*(i/8) + (i%8) + 8]  = pGbceToneCurve_1c[i];
    pGbceToneCurve_4c[32*(i/8) + (i%8) + 16] = pGbceToneCurve_1c[i];
    pGbceToneCurve_4c[32*(i/8) + (i%8) + 24] = pGbceToneCurve_1c[i];
  }

  memset(output, 0, sizeOutput);

  vcop_minit();
  wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 27*1024);
  memset(wbufToZero, 0xcd, 27*1024);
  vcop_free(wbufToZero);

  inArgs.updateToneCurve = 1;
  inArgs.pGbceToneCurve = pGbceToneCurve_4c;

  inArgs.sensorBitDepth         = params->sensorBitDepth;
  inArgs.rPosition              = params->rPosition;
  inArgs.enableDecompand        = params->enableDecompand;
  inArgs.pout1                  = params->pout1;
  inArgs.pout2                  = params->pout2;
  inArgs.slope1                 = params->slope1;
  inArgs.slope2                 = params->slope2;
  for(i = 0; i < 4; i++) {
    inArgs.blackClamp[i]        = params->blackClamp[i];
    inArgs.cBalanceGain[i]      = params->cBalanceGain[i];
  }
  inArgs.cBalanceShift          = params->cBalanceShift;
  inArgs.enableExtractR         = params->enableExtractR;
  inArgs.gbceMethod             = params->gbceMethod;
  inArgs.enableStats            = params->enableStats;
  inArgs.saturationLimit        = params->saturationLimit;

#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif

  profiler_start();
  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
  profiler_end_print(1);

  profile_tsc = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];

  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Processing End\n");
#endif

  if (strcmp(params->outImg, ""))
  {
    /* Write output image */
    sprintf(filepath, "../testvecs/output/%s", params->outImg);
    fid= FOPEN(filepath,"wb");
    if ( fid == NULL)
    {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }

    output = (uint8_t *)outImgBufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE].bufPlanes[0].buf;
    for(i = 0; i < params->imageHeight - 4; i++) {
      numBytes = FWRITE(output + i*createParams.minOutputBufStride, 1, params->imageWidth - 4, fid);
      assert(numBytes == (params->imageWidth - 4));
    }
    FCLOSE(fid);
  }

  refOutput = (uint8_t *)malloc(sizeOutput);
  if(refOutput == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  if(params->enableExtractR == 1) {
    refOutputR = (uint8_t *)malloc(sizeOutput/4);
    if(refOutputR == NULL)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
  }
  else {
    refOutputR = NULL;
  }

  if(params->enableStats == 1) {
    refStatsOut = (uint8_t *)malloc(sizeStatsBuf);
    if(refStatsOut == NULL)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
  }

  soft_isp_ref_cn(input, refOutput, refOutputR, refStatsOut, params->imageWidth,
    params->imageHeight, params->imagePitch, params->rPosition, params->sensorBitDepth,
    params->enableDecompand, params->pout1, params->pout2, params->slope1,
    params->slope2, params->blackClamp, params->cBalanceGain, params->cBalanceShift,
    params->enableExtractR, params->enableStats, params->statBlkWidth,
    params->statBlkHeight, params->saturationLimit, params->gbceMethod, pGbceToneCurve_4c);

  fail = 0 ;

  for(i = 0; i < params->imageHeight - 4; i++) {
    for(j = 0; j < params->imageWidth - 4; j++) {
      if(refOutput[i*(params->imageWidth - 4) + j] != output[i*createParams.minOutputBufStride + j]) {
        TEST_PRINTF("SOFT ISP C Output (%d, %d): Expected = %d, Output = %d\n",
          i, j, refOutput[i*(params->imageWidth - 4) + j],
          output[i*createParams.minOutputBufStride + j]);
        fail = 1;
      }
    }
  }
  /* Compare R output with reference */
  if(params->enableExtractR == 1) {
    for(i = 0; i < (params->imageHeight - 4)/2; i++) {
      for(j = 0; j < (params->imageWidth - 4)/2; j++) {
        if(refOutputR[i*(params->imageWidth - 4)/2 + j] != outputR[i*createParams.minOutputBufStride/2 + j]) {
          TEST_PRINTF("SOFT ISP R Output (%d, %d): Expected = %d, Output = %d\n",
            i, j, refOutput[i*(params->imageWidth - 4)/2 + j],
            output[i*createParams.minOutputBufStride/2 + j]);
          fail = 1;
        }
      }
    }
  }
#if 0
  /* Compare Statistics output with reference */
  if(params->enableStats == 1) {
    for(i = 0; i < createParams.statBufHeight; i++) {
      for(j = 0; j < createParams.statBufWidth/34; j++) {
        for(k = 0; k < 8; k++) {
          if((uint32_t *)(refStatsOut + i*createParams.statBufStride + j*34)[k] !=
             (uint32_t *)(statsOut + i*createParams.statBufStride + j*34)[k]) {
            TEST_PRINTF("SOFT ISP Sum Statistics (%d, %d, %d): Expected = %d, Output = %d\n", i, j, k,
              (uint32_t *)(refStatsOut + i*createParams.statBufStride + j*34)[k],
              (uint32_t *)(statsOut + i*createParams.statBufStride + j*34)[k]);
            fail = 1;
          }
        }
        if((uint16_t *)(refStatsOut + i*createParams.statBufStride + j*34 + 32)[0] !=
           (uint16_t *)(statsOut + i*createParams.statBufStride + j*34 + 32)[0]) {
          TEST_PRINTF("SOFT ISP Count Statistics (%d, %d): Expected = %d, Output = %d\n", i, j,
            (uint16_t *)(refStatsOut + i*createParams.statBufStride + j*34 + 32)[0],
            (uint16_t *)(statsOut + i*createParams.statBufStride + j*34 + 32)[0]);

          fail = 1;
        }
      }
    }
  }
#endif

  profiler_printStatus(fail);

  statusStr = fail ? "FAILED" : "PASSED";

  TEST_PRINTF("%-15s %10s %15d %15d %15.2f %20.2f %16.2f %17.2f %16.2f\
    Create graph is %2.2f MegaCycPerFr (one-time)\n",\
    "SOFT ISP", statusStr, params->imageWidth, params->imageHeight,\
    (2*profile_tsc/1000000.0), 30*(2*profile_tsc/1000000.0),\
    (profile_tsc*2.0)/(params->imageWidth*params->imageHeight),\
    (profile_sctm*2.0)/(params->imageWidth*params->imageHeight),\
    (2*profile_tsc/500000.0), (profile_create_tsc*2.0)/1000000.0);

  fflush(stdout);

EXIT_LOOP:
  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
  }
  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
  }

  if(memRec != NULL)
  {
    free(memRec);
  }
  if(input != NULL)
  {
    free(input);
  }
  if(output != NULL)
  {
    free(output);
  }
  if(outputR != NULL)
  {
    free(outputR);
  }
  if(refOutput != NULL)
  {
    free(refOutput);
  }
  if(statsOut != NULL)
  {
    free(statsOut);
  }
  if(refStatsOut != NULL)
  {
    free(refStatsOut);
  }
  if(refOutputR != NULL)
  {
    free(refOutputR);
  }
  if(pGbceToneCurve_1c != NULL)
  {
    free(pGbceToneCurve_1c);
  }
  if(pGbceToneCurve_4c != NULL)
  {
    free(pGbceToneCurve_4c);
  }

  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}


int main(int argc, char *argv[])
{
  int32_t status = 0;
  TI_FILE *fp;
  int8_t *LinePtr;
  int32_t lineNum = -1;
  int32_t config_cmd;
  int8_t configFileName[FILE_NAME_SIZE];
  sSoftIsp_Config *params;

  report_printAppletInfo((int8_t *)"SOFT_ISP_TI_VISION");

  params = (sSoftIsp_Config *)(&gConfig_soft_isp);

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
    status = softIspTest(params);

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
      status = readparamfile((char *)configFileName, gsTokenMap_soft_isp) ;
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed\n");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)params->testCaseName,
        (int8_t *)params->testCaseDesc, params->performanceTestcase);
      printparams(gsTokenMap_soft_isp, (int32_t)MAX_ITEMS_TO_PARSE,
        (uint32_t)params, sizeof(sSoftIsp_Config));

      /* Validate the applet */
      status = softIspTest(params);
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

