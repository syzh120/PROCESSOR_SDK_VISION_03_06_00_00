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


/** @file harris_best_feature_to_front_tb.c
*
*  @brief  This file contains test code for Harris score based Best Feature
*          to front applet
*
*
*  @date   Dec 2013
*
*  Description
*    This file contains test code to validate the frame level applet for
*    obtaining best feature to front based on harris scores. It checks the
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
#include "harris_best_feature_to_front_config.h"
#include "xdais_types.h"
#include "iharris_best_feature_to_front_ti.h"

#include "harris_bftf.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"
#include "configparser.h"


#define ENABLE_TRACES 0
#define ENABLE_PROFILE (1U)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERROR_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (16*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;

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


void fillDefaultConfig(sHarrisBestFeatureToFront_Config * params)
{
  strcpy(params->inImage[0], "");
  strcpy(params->inXyList[0], "");

  params->srcImageWidth[0]  = 400;
  params->srcImageHeight[0] = 400;
  params->srcImagePitch[0]  = 400;

  params->xyListInDmem = 0;
  params->numPoints[0] = 1024;

  params->numLevels = 1;
  params->maxNumFeaturesIn = 2048;
  params->bestNFeaturesOut = 500;
  params->sensitivityParam = 1310;

  strcpy(params->outXyList, "");
  strcpy(params->outLevelIds, "");

  params->fileBased   = 0;
  params->randSeed    = 0;
}


int32_t harrisBestFeatureToFrontTest(sHarrisBestFeatureToFront_Config * params)
{
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i, j, n;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t fail = 0;
  uint8_t *input[MAX_NUM_LEVELS] = {NULL, NULL, NULL};
  uint32_t *inXYList[MAX_NUM_LEVELS] = {NULL, NULL, NULL};
  uint32_t *outXYList = NULL, *refOutXYList = NULL;
  uint8_t  *outLevelList = NULL, *refOutLevelList = NULL;
  uint32_t seed;
#if (ENABLE_PROFILE)
  uint64_t profile_tsc, profile_create_tsc, profile_sctm;
#endif
  uint32_t sizeOutXY, sizeOutLevel;
  uint32_t sizeInput[MAX_NUM_LEVELS];
  uint32_t sizeInXY[MAX_NUM_LEVELS];
  uint32_t numBytes, totalNumPoints;

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
  HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams   createParams;

  IVISION_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inImgBufDesc, inXyListBufDesc;
  IVISION_BufDesc   *inBufDescList[2];

  IVISION_OutArgs   outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outXyListBufDesc, outLevelListBufDesc;
  IVISION_BufDesc   *outBufDescList[2];

  outArgs.size = sizeof(IVISION_OutArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;


  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if (ENABLE_PROFILE)
  profiler_init();
#endif

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs  = 2;
  outBufs.numBufs = 2;

  inBufDescList[0]     = &inImgBufDesc;
  inBufDescList[1]     = &inXyListBufDesc;
  outBufDescList[0]    = &outXyListBufDesc;
  outBufDescList[1]    = &outLevelListBufDesc;

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size = sizeof(HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;
  createParams.maxNumFeaturesIn            = params->maxNumFeaturesIn;
  createParams.bestNFeaturesOut            = params->bestNFeaturesOut;
  createParams.sensitivityParam            = params->sensitivityParam;
  createParams.xyListInDmem                = params->xyListInDmem;

#if (ENABLE_PROFILE)
  profiler_initStack(profiler_getSP());
  profiler_start();
#endif

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Harris Best Feature to Front Applet Create Done\n");
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
  status = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
  /* Set the end point of the timing measurement for the creation process */
  profiler_end_print(0);
  profile_create_tsc = gTest_TI_profileTsc;
#endif
  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Harris Best Feature to Front Applet Init Done\n");
#endif


  inArgs.subFrameInfo = 0;
  inArgs.size                  = sizeof(IVISION_InArgs);

  inImgBufDesc.numPlanes       = params->numLevels;
  inXyListBufDesc.numPlanes    = params->numLevels;

  for(i = 0; i < params->numLevels; i++) {

    /* Image buffer for each pyramidal level */
    inImgBufDesc.bufPlanes[i].frameROI.topLeft.x    = 0;
    inImgBufDesc.bufPlanes[i].frameROI.topLeft.y    = 0;
    inImgBufDesc.bufPlanes[i].width                 = params->srcImagePitch[i];
    inImgBufDesc.bufPlanes[i].height                = params->srcImageHeight[i];
    inImgBufDesc.bufPlanes[i].frameROI.width        = params->srcImageWidth[i];
    inImgBufDesc.bufPlanes[i].frameROI.height       = inImgBufDesc.bufPlanes[i].height;

    sizeInput[i] = inImgBufDesc.bufPlanes[i].width * inImgBufDesc.bufPlanes[i].height;
    input[i]  = (uint8_t *)malloc(sizeInput[i]);
    inImgBufDesc.bufPlanes[i].buf = (uint8_t *)input[i];

    if(inImgBufDesc.bufPlanes[i].buf == NULL)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    sizeInXY[i] = 4*params->numPoints[i];
    /* Input buffer holding list of XY co-ordinates of feature points at each level */
    inXyListBufDesc.bufPlanes[i].frameROI.topLeft.x    = 0;
    inXyListBufDesc.bufPlanes[i].frameROI.topLeft.y    = 0;
    inXyListBufDesc.bufPlanes[i].width                 = sizeInXY[i];
    inXyListBufDesc.bufPlanes[i].height                = 1;
    inXyListBufDesc.bufPlanes[i].frameROI.width        = inXyListBufDesc.bufPlanes[i].width ;
    inXyListBufDesc.bufPlanes[i].frameROI.height       = inXyListBufDesc.bufPlanes[i].height;

    inXYList[i]  = (uint32_t *)malloc(sizeInXY[i]);
    inXyListBufDesc.bufPlanes[i].buf = (uint32_t *)inXYList[i];

    if(inXyListBufDesc.bufPlanes[i].buf == NULL)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
  }

  totalNumPoints = 0;
  for(n = 0; n < params->numLevels; n++) {
    totalNumPoints += params->numPoints[n];
  }

  sizeOutXY = (params->bestNFeaturesOut < totalNumPoints) ? (4*params->bestNFeaturesOut) : (4*totalNumPoints);
  outXyListBufDesc.numPlanes                          = 1;
  outXyListBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  outXyListBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
  outXyListBufDesc.bufPlanes[0].width                 = sizeOutXY;
  outXyListBufDesc.bufPlanes[0].height                = 1;
  outXyListBufDesc.bufPlanes[0].frameROI.width        = outXyListBufDesc.bufPlanes[0].width;
  outXyListBufDesc.bufPlanes[0].frameROI.height       = outXyListBufDesc.bufPlanes[0].height;

  outXYList = (uint32_t *)malloc(sizeOutXY);
  outXyListBufDesc.bufPlanes[0].buf = (uint8_t *)outXYList;

  if(outXyListBufDesc.bufPlanes[0].buf == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  sizeOutLevel = (params->bestNFeaturesOut < totalNumPoints) ? params->bestNFeaturesOut : totalNumPoints;
  outLevelListBufDesc.numPlanes                       = 1;
  outLevelListBufDesc.bufPlanes[0].frameROI.topLeft.x = 0;
  outLevelListBufDesc.bufPlanes[0].frameROI.topLeft.y = 0;
  outLevelListBufDesc.bufPlanes[0].width              = sizeOutLevel;
  outLevelListBufDesc.bufPlanes[0].height             = 1;
  outLevelListBufDesc.bufPlanes[0].frameROI.width     = outLevelListBufDesc.bufPlanes[0].width;
  outLevelListBufDesc.bufPlanes[0].frameROI.height    = outLevelListBufDesc.bufPlanes[0].height;

  outLevelList = (uint8_t *)malloc(sizeOutLevel);
  outLevelListBufDesc.bufPlanes[0].buf = (uint8_t *)outLevelList;

  if(outLevelListBufDesc.bufPlanes[0].buf == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  if(params->fileBased == 1)
  {
    for(i = 0; i < params->numLevels; i++) {
      sprintf(filepath, "../testvecs/input/%s", params->inImage[i]);
      fid = FOPEN(filepath,"rb");
      if(fid == NULL) {
        PRINT_ERROR_MSG();
        TEST_PRINTF("\nError, unable to open file %s \n", filepath);
        goto EXIT_LOOP;
      }
      input[i] = (uint8_t *)inImgBufDesc.bufPlanes[i].buf;
      numBytes= FREAD(input[i], 1, sizeInput[i], fid);
      assert(numBytes== sizeInput[i]);
      FCLOSE(fid);
    }
  }
  else
  {

    seed = (params->randSeed == 0) ? _tsc_gettime() : params->randSeed;
    srand(seed);
    TEST_PRINTF("Pattern Generation Seed = %d\n", seed);

    /* Create Random input data */
    for(n = 0; n < params->numLevels; n++) {

      /* Image Pyramid */
      for(i = 0 ; i < params->srcImageHeight[n]; i++) {
        for(j = 0; j < params->srcImageWidth[n]; j++) {
          input[n][j + (i*params->srcImagePitch[n])] = rand() % 256;
        }
      }

      /* Input XY List */
      for(i = 0; i < params->numPoints[n]; i++) {
        inXYList[n][i] = (((4 + rand() % (params->srcImageWidth[n] - 5)) << 16) & 0xFFFF0000) +
                         ((4 + rand() % (params->srcImageHeight[n] - 5)) & 0x0000FFFF);
      }
    }
  }

  memset(outXYList, 0, sizeOutXY);
  memset(outLevelList, 0, sizeOutLevel);
  vcop_minit();
  wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
  memset(wbufToZero, 0xcd, 31*1024);
  vcop_free(wbufToZero);

#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif
#if (ENABLE_PROFILE)
  profiler_start();
#endif

  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
  profiler_end_print(1);
  profile_tsc = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];
#endif

  if(status != IALG_EOK)
  {
    PRINT_ERROR_MSG();
    if(status == IHARRIS_BEST_FEATURE_TO_FRONT_ERRORTYPE_MAXNUMFEATURES_EXCEEDED) {
      TEST_PRINTF("\nbestNFeaturesOut = %d, totalNumFeatures = %d, maxNumFeaturesIn=%d\n",
        params->bestNFeaturesOut, totalNumPoints, params->maxNumFeaturesIn);
    }
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Processing End\n");
#endif

  if (params->fileBased == 1)
  {
    /* Write output XY List */
    sprintf(filepath, "../testvecs/output/%s", params->outXyList);
    fid= FOPEN(filepath,"wb");
    if ( fid == NULL)
    {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    outXYList = (uint32_t *)outXyListBufDesc.bufPlanes[0].buf;
    numBytes = FWRITE(outXYList, 1, 4*params->bestNFeaturesOut, fid);
    assert(numBytes == 4*params->bestNFeaturesOut);
    FCLOSE(fid);

    /* Write output Level List */
    sprintf(filepath, "../testvecs/output/%s", params->outLevelIds);
    fid= FOPEN(filepath,"wb");
    if ( fid == NULL)
    {
      PRINT_ERROR_MSG();
      TEST_PRINTF("\nError, unable to open file %s \n", filepath);
      goto EXIT_LOOP;
    }
    outLevelList = (uint8_t *)outLevelListBufDesc.bufPlanes[0].buf;
    numBytes = FWRITE(outLevelList, 1, params->bestNFeaturesOut, fid);
    assert(numBytes == params->bestNFeaturesOut);
    FCLOSE(fid);
  }

  refOutXYList = (uint32_t *)malloc(sizeOutXY);
  if(refOutXYList == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  refOutLevelList = (uint8_t *)malloc(sizeOutLevel);
  if(refOutLevelList == NULL)
  {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  for(i = 0; i < params->numLevels; i++) {
    sizeInXY[i] = params->numPoints[i];
  }

  HarrisScoreBestFeatureToFront(&input[0], &inXYList[0],
    sizeInXY, params->srcImageWidth[0],
    params->srcImageHeight[0],
    params->srcImagePitch[0],
    params->sensitivityParam,
    refOutXYList, refOutLevelList,
    params->numLevels,
    params->bestNFeaturesOut);

  fail = 0 ;
  fail = memcmp(refOutXYList, outXYList, 4*params->bestNFeaturesOut);
  fail |= memcmp(refOutLevelList, outLevelList, params->bestNFeaturesOut);

  if(fail) {
    for(i = 0; i < sizeOutLevel; i++) {
      if(refOutXYList[i] != outXYList[i]) {

        TEST_PRINTF("XY List (%d): Expected = (%3d, %3d), Output = (%3d, %3d)\n",
          i, ((uint16_t *)refOutXYList)[2*i], ((uint16_t *)refOutXYList)[2*i + 1],
          ((uint16_t *)outXYList)[2*i], ((uint16_t *)outXYList)[2*i + 1]);
      }

      if(refOutLevelList[i] != outLevelList[i]) {
        TEST_PRINTF("Level (%d): Expected = %d, Output = %d\n", i, refOutLevelList[i], outLevelList[i]);
      }
    }
  }

  statusStr = fail ? "FAILED" : "PASSED";

  profiler_printStatus(fail);

#if (ENABLE_PROFILE)

  TEST_PRINTF("\n%-15s %10s %10s %10s %10s %15s %20s %16s %17s %16s    %s\n", \
    "Algorithm", "Status", "NumPoints", "bestN", "numLevels", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

  TEST_PRINTF("%-15s %10s %10d %10d %10d %15.2f %20.2f %16.2f %17.2f %16.2f\
    Create graph is %2.2f MegaCycPerFr (one-time)\n",\
    "Harris BFTF",statusStr, totalNumPoints, params->bestNFeaturesOut, params->numLevels,\
    (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
    (profile_tsc*1.0)/totalNumPoints, (profile_sctm*1.0)/totalNumPoints,\
    (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);
#endif
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

  if ( memRec != NULL )
  {
    free(memRec);
  }
  for(i = 0; i < MAX_NUM_LEVELS; i++) {
    if ( input[i] != NULL )
    {
      free(input[i]);
    }
  }
  if (outXYList != NULL)
  {
    free(outXYList);
  }
  if (refOutXYList != NULL)
  {
    free(refOutXYList);
  }
  if (outLevelList != NULL)
  {
    free(outLevelList);
  }
  if (refOutLevelList != NULL)
  {
    free(refOutLevelList);
  }

  return status;
}

char * moveToNextElement(char *in, char *LinePtr)
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
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t *LinePtr;
  TI_FILE * fp;
  int32_t lineNum = -1;
  int32_t config_cmd;


  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  report_printAppletInfo((int8_t *)"HARRIS_BFTF_TI_VISION");

  fp = FOPEN((const char *)configFile, "r");
  if (fp == NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

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
      TEST_PRINTF("\n Processing config file %s !\n", configFile);
      fillDefaultConfig(&gConfig_harrisBestFeatureToFront[0]);
      status = readparamfile(configFile, &gsTokenMap_harrisBestFeatureToFront[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_harrisBestFeatureToFront[0].testCaseName, (int8_t *)gConfig_harrisBestFeatureToFront[0].desc,
                            gConfig_harrisBestFeatureToFront[0].performanceTestcase);
      printparams(&gsTokenMap_harrisBestFeatureToFront[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_harrisBestFeatureToFront),
                            sizeof(sHarrisBestFeatureToFront_Config));

      /* Validate the applet */
      status = harrisBestFeatureToFrontTest(gConfig_harrisBestFeatureToFront);
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

#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}



