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


/** @file feature_matching_tb.c
*
*  @brief  This file contains test code for Feature Matching applet
*
*  @date   Aug 2014
*
*  Description
*    This file contains test code to validate the frame level applet for
*    feature matching. It checks the output against c reference outputs and
*    profiles the performance and computes the system overheads.
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
#include "feature_matching_config.h"
#include "xdais_types.h"

#include "ti_file_io.h"
#include "ifeature_matching_ti.h"
#include "feature_matching_cn.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"

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


void fillDefaultConfig(sFeatureMatching_Config * params)
{

  strcpy(params->inFeatureList1, "");
  strcpy(params->inFeatureList2, "");
  strcpy(params->outCorrespondence, "");

  params->numDescriptors1  = 64;
  params->numDescriptors2  = 64;
  params->descriptorLength = 32;
  params->minDistanceThres = 50;
  params->matchConfidence  = 3277;

  params->randSeed1 = 0;
  params->randSeed2 = 0;

  params->performanceTestcase = 1;
  strcpy((char*)params->testCaseName, " ");
  strcpy((char*)params->testCaseDesc, " ");
}


int32_t featureMatchingTest(sFeatureMatching_Config * params)
{
  uint64_t profile_tsc, profile_sctm, profile_create_tsc;
  uint32_t  seed;
  uint8_t *wbufToZero;
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t i, status, fail = 0;

  uint8_t *inFeature1 = NULL, *inFeature2 = NULL;
  uint16_t *outCorrespondence = NULL, *refOutCorrespondence = NULL;
  uint32_t sizeInput1, sizeInput2;
  uint32_t sizeOutput;

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
  FEATURE_MATCHING_TI_CreateParams   createParams;
  FEATURE_MATCHING_TI_CtrlParams  ctrlParams;

  FEATURE_MATCHING_TI_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[FEATURE_MATCHING_TI_BUFDESC_IN_TOTAL];

  FEATURE_MATCHING_TI_OutArgs outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[FEATURE_MATCHING_TI_BUFDESC_OUT_TOTAL];

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

  inBufs.numBufs  = 2;
  outBufs.numBufs = 1;

  inBufDescList[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1] =
                        &inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1];
  inBufDescList[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2] =
                        &inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2];
  outBufDescList[FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE] = &outBufDesc;

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size = sizeof(FEATURE_MATCHING_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;
  createParams.descriptorLength  =  params->descriptorLength;

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Start\n");
#endif
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();

  numMemRec = FEATURE_MATCHING_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = FEATURE_MATCHING_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

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
  status = FEATURE_MATCHING_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  profiler_end_print(0);
  profile_create_tsc = gTest_TI_profileTsc;

#if ENABLE_TRACES
  TEST_PRINTF("Feature Matching Applet Init Done\n");
#endif

  ctrlParams.numDescriptors1 = params->numDescriptors1;
  ctrlParams.numDescriptors2 = params->numDescriptors2;

  status = handle->ivision->algControl((IVISION_Handle)handle,
    FEATURE_MATCHING_TI_CONTROL_GET_BUF_SIZE,
    (IALG_Params *)(&ctrlParams),(IALG_Params *)(&ctrlParams));
  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.iVisionInArgs.size         = sizeof(FEATURE_MATCHING_TI_InArgs);

  /* Buffer for first feature descriptor list */
  sizeInput1 = params->descriptorLength * params->numDescriptors1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].numPlanes = 1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].width              = sizeInput1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].height             = 1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].frameROI.width     = sizeInput1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].frameROI.height    = 1;

  inFeature1 = (uint8_t *)malloc(ctrlParams.in1BufSize);
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].buf = (uint8_t *)inFeature1;

  if(inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1].bufPlanes[0].buf == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /* Buffer for first feature descriptor list */
  sizeInput2 = params->descriptorLength * params->numDescriptors2;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].numPlanes = 1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].width              = sizeInput2;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].height             = 1;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].frameROI.width     = sizeInput2;
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].frameROI.height    = 1;

  inFeature2 = (uint8_t *)malloc(ctrlParams.in2BufSize);
  inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].buf = (uint8_t *)inFeature2;

  if(inBufDesc[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2].bufPlanes[0].buf == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  outArgs.iVisionOutArgs.size = sizeof(FEATURE_MATCHING_TI_OutArgs);

  /* Buffer for output Feature Matching matrix */
  sizeOutput = sizeof(uint16_t)*params->numDescriptors1;
  outBufDesc.numPlanes                          = 1;
  outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufDesc.bufPlanes[0].width                 = sizeOutput;
  outBufDesc.bufPlanes[0].height                = 1;
  outBufDesc.bufPlanes[0].frameROI.width        = sizeOutput;
  outBufDesc.bufPlanes[0].frameROI.height       = 1;

  outCorrespondence = (uint16_t *)malloc(ctrlParams.outBufSize);
  outBufDesc.bufPlanes[0].buf = (uint8_t *)outCorrespondence;

  if(outBufDesc.bufPlanes[0].buf == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /* Fill feature descriptor list 1 buffer */
  if(strcmp(params->inFeatureList1, "")) {
    sprintf(filepath, "../testvecs/input/%s", params->inFeatureList1);
    fid = FOPEN(filepath,"rb");
    if(fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    numBytes = FREAD(inFeature1, 1, sizeInput1, fid);
    assert(numBytes == sizeInput1);
    FCLOSE(fid);
  }
  else {
    seed = (params->randSeed1 == 0) ? _tsc_gettime() : params->randSeed1;
    srand(seed);
    if(params->randSeed1 == 0) {
      TEST_PRINTF("Pattern Generation Seed = %d\n", seed);
    }

    /* Create Random inFeature1 data in Buffer */
    for(i = 0; i < sizeInput1; i++) {
      inFeature1[i] = rand() & 0xFF;
    }
  }

  /* Fill feature descriptor list 2 buffer */
  if(strcmp(params->inFeatureList2, "")) {
    sprintf(filepath, "../testvecs/input/%s", params->inFeatureList2);
    fid = FOPEN(filepath,"rb");
    if(fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    numBytes = FREAD(inFeature2, 1, sizeInput2, fid);
    assert(numBytes == sizeInput2);
    FCLOSE(fid);
  }
  else {
    seed = (params->randSeed2 == 0) ? _tsc_gettime() : params->randSeed2;
    srand(seed);
    if(params->randSeed2 == 0) {
      TEST_PRINTF("Pattern Generation Seed = %d\n", seed);
    }

    /* Create Random inFeature2 data in Buffer */
    for(i = 0; i < sizeInput2; i++) {
      inFeature2[i] = rand() & 0xFF;
    }
  }

  // Intialize output buffer with zeros
  memset(outCorrespondence, 0, sizeOutput);

  vcop_minit();
  wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 27*1024);
  memset(wbufToZero, 0xcd, 27*1024);
  vcop_free(wbufToZero);

#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif

  inArgs.minDistanceThres = params->minDistanceThres;
  inArgs.matchConfidence  = params->matchConfidence;

  profiler_start();
  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs, &outBufs, (IVISION_InArgs *)&inArgs, (IVISION_OutArgs *)&outArgs);
  profiler_end_print(1);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Processing End\n");
#endif

  if (strcmp(params->outCorrespondence, "")) {
    /* Write output Feature Matching */
    sprintf(filepath, "../testvecs/output/%s", params->outCorrespondence);
    fid= FOPEN(filepath,"wb");
    if ( fid == NULL) {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    numBytes = FWRITE(outCorrespondence, 1, sizeOutput, fid);
    assert(numBytes == sizeOutput);
    FCLOSE(fid);
  }

  refOutCorrespondence = (uint16_t *)malloc(sizeOutput);
  if(refOutCorrespondence == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  feature_matching_cn(inFeature1, inFeature2, refOutCorrespondence,
                      params->numDescriptors1, params->numDescriptors2,
                      params->descriptorLength, params->minDistanceThres,
                      params->matchConfidence);

  fail = 0 ;
  fail = memcmp(refOutCorrespondence, outCorrespondence, sizeOutput);

  if(fail) {
    for(i = 0; i < sizeOutput/2; i++) {
      if(refOutCorrespondence[i] != outCorrespondence[i]) {
        TEST_PRINTF("Feature Matching (%d): Expected = %d, Output = %d\n",
          i, refOutCorrespondence[i], outCorrespondence[i]);
      }
    }
  }

  profiler_printStatus(fail);

  statusStr = fail ? "FAILED" : "PASSED";
  profile_tsc = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];

  TEST_PRINTF("\n%-15s %10s %20s %20s %15s %20s %16s %17s %16s    %s\n", \
    "Algorithm", "Status", "numDescriptors1", "numDescriptors2", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix", \
    "TimePerFr(MSec)", "Comments");

  TEST_PRINTF("%-15s %10s %20d %20d %15.2f %20.2f %16.2f %17.2f %16.2f\
    Create graph is %2.2f MegaCycPerFr (one-time)\n",\
    "Feature Matching", statusStr, params->numDescriptors1, params->numDescriptors2,\
    (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
    (profile_tsc*1.0)/(params->numDescriptors1*params->numDescriptors2),\
    (profile_sctm*1.0)/(params->numDescriptors1*params->numDescriptors2),\
    profile_tsc/500000.0, profile_create_tsc/1000000.0);

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
  if(inFeature1 != NULL) {
    free(inFeature1);
  }
  if(inFeature2 != NULL) {
    free(inFeature2);
  }
  if(outCorrespondence != NULL) {
    free(outCorrespondence);
  }
  if(refOutCorrespondence != NULL) {
    free(refOutCorrespondence);
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
  sFeatureMatching_Config *params;

  report_printAppletInfo((int8_t *)"FEATURE_MATCHING_TI_VISION");

  params = (sFeatureMatching_Config *)(&gConfig_feature_matching);

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
    printf("Could not open config list file : %s , Runing in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    /* Validate the applet */
    status = featureMatchingTest(params);
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
      status = readparamfile((char *)configFileName, gsTokenMap_feature_matching) ;
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed\n");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)params->testCaseName,
        (int8_t *)params->testCaseDesc, params->performanceTestcase);
      printparams(gsTokenMap_feature_matching, (int32_t)MAX_ITEMS_TO_PARSE,
        (uint32_t)params, sizeof(sFeatureMatching_Config)) ;

      /* Validate the applet */
      status = featureMatchingTest(params);
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

