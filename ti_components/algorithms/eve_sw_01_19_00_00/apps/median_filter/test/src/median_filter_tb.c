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
*  @file:      median_filter_test.c
*
*  @brief:     Example file that shows the usage of median filter applet
*
*  @version:   0.2 (July 2014) : Added support for 3x3 dense median filtering.
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

#include "imedian_filter_ti.h"
#include "median_filter_config.h"
#include "median_filter_cn.h"

#define ENABLE_TRACES 0
#define ENABLE_PROFILE (1U)

#define PRINT_ERROR_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)
#define MAX_CONFIG_LINE_SIZE     (300U)
#define MAX_FILE_NAME_SIZE       (200U)
#define MAX_PARAM_STRING_SIZE    (30U)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

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
void fillDefaultConfig(sMedianFilter_Config* params)
{
  strcpy(params->inImg, "");
  strcpy(params->outImg, "");

  params->imageWidth  = 640;
  params->imageHeight = 480;
  params->imagePitch  = 640;

  params->blockWidth   = 121;
  params->blockHeight  = 71;
  params->stepSizeHorz = 35;
  params->stepSizeVert = 35;

  params->randSeed    = 0;
  params->numIter     = 1;
}


int32_t medianFilterTest(sMedianFilter_Config* params)
{
#if (ENABLE_PROFILE)
  uint64_t profile_tsc, profile_create_tsc, profile_sctm;
#endif
  uint32_t seed;
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i, j; //k;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t fail = 0;

  uint8_t *input = NULL, *output = NULL, *refOutput = NULL;
  int16_t *pBlkHist;
  uint32_t sizeInput, sizeOutput;
  int16_t imgOutWidth, imgOutHeight;
  uint32_t numBytes;

  char  filepath[256];
  TI_FILE *fid;

#if (ENABLE_PROFILE)
  char *statusStr = NULL;
#endif

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  MEDIAN_FILTER_TI_CreateParams   createParams;

  IVISION_InArgs inArgs;
  IVISION_InBufs inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc inImgBufDesc;
  IVISION_BufDesc *inBufDescList[MEDIAN_FILTER_TI_BUFDESC_IN_TOTAL];

  IVISION_OutArgs outArgs;
  IVISION_OutBufs outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc outImgBufDesc;
  IVISION_BufDesc *outBufDescList[MEDIAN_FILTER_TI_BUFDESC_OUT_TOTAL];

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

  inBufs.numBufs  = 1;
  outBufs.numBufs = 1;

  inBufDescList[0]  = &inImgBufDesc;
  outBufDescList[0] = &outImgBufDesc;

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size = sizeof(MEDIAN_FILTER_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;
  createParams.imageWidth   = params->imageWidth;
  createParams.imageHeight  = params->imageHeight;
  createParams.blockWidth   = params->blockWidth;
  createParams.blockHeight  = params->blockHeight;
  createParams.stepSizeHorz = params->stepSizeHorz;
  createParams.stepSizeVert = params->stepSizeVert;

#if (ENABLE_PROFILE)
  profiler_initStack(profiler_getSP());
  profiler_start();
#endif

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = MEDIAN_FILTER_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = MEDIAN_FILTER_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Median Filter Applet Create Done\n");
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
  status = MEDIAN_FILTER_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
  /* Set the end point of the timing measurement for the creation process */
  profiler_end_print(0);
  profile_create_tsc = gTest_TI_profileTsc;
#endif

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Median Filter Applet Init Done\n");
#endif

  status = handle->ivision->algControl((IVISION_Handle)handle,TI_MEDIAN_FILTER_CONTROL_GET_BUF_SIZE,
    (IALG_Params *)(&createParams),(IALG_Params *)(&createParams));
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  inArgs.subFrameInfo = 0;
  inArgs.size         = sizeof(IVISION_InArgs);

  /* Image buffer input to the Median filter */
  sizeInput = params->imagePitch * createParams.minInputBufHeight + createParams.extraInputMem;
  inImgBufDesc.numPlanes = 1;
  inImgBufDesc.bufPlanes[0].frameROI.topLeft.x = 0;
  inImgBufDesc.bufPlanes[0].frameROI.topLeft.y = 0;
  inImgBufDesc.bufPlanes[0].width = params->imagePitch;
  inImgBufDesc.bufPlanes[0].height = createParams.minInputBufHeight;
  inImgBufDesc.bufPlanes[0].frameROI.width = params->imageWidth;
  inImgBufDesc.bufPlanes[0].frameROI.height = params->imageHeight;

  input = (uint8_t *)malloc(sizeInput);
  inImgBufDesc.bufPlanes[0].buf = input;

  if(inImgBufDesc.bufPlanes[0].buf == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /* Buffer for Median Filter output */
  imgOutWidth = 1 + (createParams.imageWidth-createParams.blockWidth)/createParams.stepSizeHorz;
  imgOutHeight = 1 + (createParams.imageHeight-createParams.blockHeight)/createParams.stepSizeVert;

  sizeOutput = createParams.minOutputBufStride*createParams.minOutputBufHeight;
  outImgBufDesc.numPlanes = 1;
  outImgBufDesc.bufPlanes[0].frameROI.topLeft.x = 0;
  outImgBufDesc.bufPlanes[0].frameROI.topLeft.y = 0;
  outImgBufDesc.bufPlanes[0].width = createParams.minOutputBufStride;
  outImgBufDesc.bufPlanes[0].height = createParams.minOutputBufHeight;
  outImgBufDesc.bufPlanes[0].frameROI.width = imgOutWidth;
  outImgBufDesc.bufPlanes[0].frameROI.height = imgOutHeight;

  output = (uint8_t *)malloc(sizeOutput);
  if(output == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
  outImgBufDesc.bufPlanes[0].buf = output;

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

  memset(output, 0, sizeOutput);

  vcop_minit();
  wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 27*1024);
  memset(wbufToZero, 0xcd, 27*1024);
  vcop_free(wbufToZero);

#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif
#if (ENABLE_PROFILE)
  profiler_start();
#endif

  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs, &outBufs, &inArgs, &outArgs);

#if (ENABLE_PROFILE)
  profiler_end_print(1);

  profile_tsc = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];
#endif

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
    output = (uint8_t *)outImgBufDesc.bufPlanes[0].buf;
    numBytes = FWRITE(output, 1, sizeOutput, fid);
    assert(numBytes == sizeOutput);
    FCLOSE(fid);
  }

  refOutput = (uint8_t *)malloc(sizeOutput);
  if(refOutput == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  pBlkHist = (int16_t *)malloc(sizeof(uint16_t)*8*256);
  if(pBlkHist == NULL) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  medianFilter_cn(&createParams, params->imagePitch, input, refOutput, pBlkHist);

  fail = 0;
  for(i = 0; i < imgOutHeight; i++) {
    for(j = 0; j < imgOutWidth; j++) {
      if(refOutput[i*imgOutWidth + j] != output[i*createParams.minOutputBufStride + j]) {
        TEST_PRINTF("Median Filter Output (%d, %d): Expected = %d, Output = %d\n",
          i, j, refOutput[i*imgOutWidth + j], output[i*createParams.minOutputBufStride + j]);
        fail = 1;
      }
    }
  }

  profiler_printStatus(fail);

#if (ENABLE_PROFILE)
  TEST_PRINTF("\n%-15s %10s %15s %15s %15s %20s %16s %17s %16s    %s\n", \
    "Algorithm", "Status", "imageWidth", "imageHeight", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

  statusStr = fail ? "FAILED" : "PASSED";

  TEST_PRINTF("%-15s %10s %15d %15d %15.2f %20.2f %16.2f %17.2f %16.2f\
    Create graph is %2.2f MegaCycPerFr (one-time)\n",\
    "MEDIAN FILTER", statusStr, params->imageWidth, params->imageHeight,\
    (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
    (profile_tsc)/((float)params->imageWidth*params->imageHeight),\
    (profile_sctm)/((float)params->imageWidth*params->imageHeight),\
    (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);
#endif

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

  if ( memRec != NULL ) {
    free(memRec);
  }
  if ( input != NULL ) {
    free(input);
  }
  if (output != NULL) {
    free(output);
  }
  if(pBlkHist != NULL) {
    free(pBlkHist);
  }
  if (refOutput != NULL) {
    free(refOutput);
  }

#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}


int main(int argc, char *argv[])
{
  TI_FILE *fp;
  char configFile[FILE_NAME_SIZE]={0};
  char     configLine[MAX_CONFIG_LINE_SIZE];
  char     configParam[MAX_PARAM_STRING_SIZE];
  int8_t  *LinePtr;
  int32_t  lineNum = -1, config_cmd, status = 0;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile, CONFIG_LIST_FILE_NAME);
  }
  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }
  report_printAppletInfo((int8_t *)"MEDIAN_FILTER_TI_VISION");

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
  fillDefaultConfig(&gConfig_median_filter);
  status = readparamfile(configFile, &gsTokenMap_median_filter[0]) ;
  if(status == -1)
  {
    TEST_PRINTF("Parser Failed");
    return -1 ;
  }

  profiler_testCaseInfo((int8_t *)gConfig_median_filter.testCaseName, (int8_t *)gConfig_median_filter.desc,
                        gConfig_median_filter.performanceTestcase);
  printparams(&gsTokenMap_median_filter[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_median_filter),
                        sizeof(sMedianFilter_Config));

  /* Validate the applet */
  status = medianFilterTest(&gConfig_median_filter);
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
#if VCOP_HOST_EMULATION
  printf("Press any key to continue ...\n");
  scanf("%c", configFile);
#endif

  return status;
}
