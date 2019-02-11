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


/** @file pyramid_lk_tracker_tb.c
*
*  @brief  This file contains test code for pyramid_lk_tracker applet
*
*
*  @date   Dec 2013
*
*  Description
*    This file contains test code to validate the frame level applet of pyramid lk tracker.
*    It also profiles the performance and computes the system overheads.
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
#include "pyramid_lk_tracker_config.h"
#include "xdais_types.h"
#include "ipyramid_lk_tracker_ti.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "configparser.h"
#include "ti_file_io.h"

#define ENABLE_TRACES (0)
#define ENABLE_FILE_READ (1)

#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define VCOP_LK_NUM_KEY_PER_CALL     (16)
#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)

#define DMEM_SIZE (12*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
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
void fillDefaultConfig(config_params * params)
{
  uint16_t i;
  params->numKeyPoints = 0;
  params->numLevels    = 4;
  params->imWidth      = 640;
  params->imHeight     = 320;
  params->performanceTestcase = 1;

  for(i = 0; i < PYRAMID_LK_TRACKER_TI_MAXLEVELS; i++)
  {
    params->searchRange[i] = PYRAMID_LK_TRACKER_TI_MAX_SEARCH_RANGE;
    params->minErrValue[i] = 0;
    params->maxItersLK[i]  = PYRAMID_LK_TRACKER_TI_MAXITERATION;
  }
  strcpy((char*)params->testCaseName, " ");
  strcpy((char*)params->testCaseDesc, " ");
}

static int readInputFromTxtFile(unsigned short *XY, unsigned short n, char * fileName)
{
  int k;
  TI_FILE * fp;
  char * LinePtr;
  int status;
  int value;
  char inputLine[MAX_INPUT_LINE_SIZE];
  char inputValue[MAX_INPUT_VALUE_SIZE];

  fp = FOPEN(fileName, "r");
  if(fp== NULL)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  for(k = 0; k < n; k++)
  {
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)FGETS(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      PRINT_ERRORE_MSG();
      return(-1);
    }
    LinePtr = inputLine;
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    XY[2*k] = value;
    LinePtr = moveToNextElement(inputValue,LinePtr);
    sscanf(LinePtr, "%d",&value);
    sscanf(LinePtr, "%s",inputValue);
    XY[2*k+1] = value;
  }
  FCLOSE(fp);
  return(0);
}

static int writeOutputToFile(unsigned short *XY, unsigned short *errMeasure, unsigned short n, char * fileName)
{
  int retVal;
  TI_FILE * fp;
  fp = FOPEN(fileName, "wb+");
  if(fp== NULL)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  retVal = FWRITE(XY,1,n*4,fp);
  if(retVal != n*4)
  {
    PRINT_ERRORE_MSG();
  }
  retVal = FWRITE(errMeasure,1,n*2,fp);
  if(retVal != n*2)
  {
    PRINT_ERRORE_MSG();
  }
  FCLOSE(fp);
  return(0);
}


static int CompareOutputWithFile(unsigned short *XY, unsigned short *errMeasure, unsigned short n, char * fileName)
{
  int retVal;
  TI_FILE * fp;

  uint8_t *refData;

  refData = (uint8_t *)malloc(n*4);

  fp = FOPEN(fileName, "rb");
  if(fp== NULL)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  retVal = FREAD(refData,1,n*4,fp);
  if(retVal != n*4)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  retVal = memcmp(refData,XY,n*4);
  if(retVal)
  {
    PRINT_ERRORE_MSG();
    return (-1);
 }

  retVal = FREAD(refData,1,n*2,fp);
  if(retVal != n*2)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  retVal = memcmp(refData,errMeasure,n*2);
  if(retVal)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  FCLOSE(fp);
  return(0);
}
int32_t pyramidLkTrackerTest(config_params * params)
{
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i,j;
  IALG_MemRec *memRec;
  int32_t status;

  uint32_t sizeOutput[3];
  uint16_t pitchOutput[3];
  uint32_t sizeInput;
  uint32_t numKeyPoints = ((params->numKeyPoints + (VCOP_LK_NUM_KEY_PER_CALL-1))/VCOP_LK_NUM_KEY_PER_CALL)*VCOP_LK_NUM_KEY_PER_CALL;

  TI_FILE *fp;
  uint16_t *xyPoints;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  PYRAMID_LK_TRACKER_TI_CreateParams   createParams;

  PYRAMID_LK_TRACKER_TI_InArgs    lkInArgs;
  PYRAMID_LK_TRACKER_TI_OutArgs   lkOutArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[4];
  IVISION_BufDesc   *inBufDescList[4];

  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc[3];
  IVISION_BufDesc   *outBufDescList[3];

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

  inBufs.numBufs   = 4;
  outBufs.numBufs  = 2;

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/

  createParams.visionParams.algParams.size   = sizeof(PYRAMID_LK_TRACKER_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.numKeyPoints                  = numKeyPoints        ;
  createParams.numLevels                     = params->numLevels   ;
  createParams.imWidth                       = params->imWidth     ;
  createParams.imHeight                      = params->imHeight    ;

  for(i = 0; i < PYRAMID_LK_TRACKER_TI_MAXLEVELS; i++)
  {
    createParams.maxItersLK[i]                   = params->maxItersLK[i];
    createParams.minErrValue[i]                  = params->minErrValue[i];
    createParams.searchRange[i]                  = params->searchRange[i];
  }
  /*-----------------------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Start\n");
#endif
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();

  numMemRec = PYRAMID_LK_TRACKER_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = PYRAMID_LK_TRACKER_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

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
  status = PYRAMID_LK_TRACKER_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));


  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
  profiler_end_print(0);

#if ENABLE_TRACES
  TEST_PRINTF("PYRAMID_LK_TRACKER corner detect Applet Init Done\n");
#endif

  lkInArgs.iVisionInArgs.subFrameInfo    = 0;
  lkInArgs.iVisionInArgs.size            = sizeof(PYRAMID_LK_TRACKER_TI_InArgs);
  lkInArgs.numKeyPoints                  = params->numKeyPoints;
  lkInArgs.startLevel                    = params->numLevels-1;
  lkInArgs.numLevels                     = params->numLevels;
  lkInArgs.SADthreshold                  = params->SADthreshold;

  lkOutArgs.iVisionOutArgs.size = sizeof (PYRAMID_LK_TRACKER_TI_OutArgs);

 /*-----------------------------------------------------------------
  Initialize the input buffer descriptors for the current and previous frames
  -----------------------------------------------------------------*/

  for(i = 0; i < 2; i++)
  {
    inBufDescList[i]         = &inBufDesc[i];
    inBufDesc[i].numPlanes   = params->numLevels ;
    for(j = 0; j < params->numLevels; j++)
    {
      inBufDesc[i].bufPlanes[j].frameROI.topLeft.x    = 0;
      inBufDesc[i].bufPlanes[j].frameROI.topLeft.y    = 0;
      inBufDesc[i].bufPlanes[j].width                 = params->imWidth  >> j;
      inBufDesc[i].bufPlanes[j].height                = params->imHeight >> j;
      inBufDesc[i].bufPlanes[j].frameROI.width        = inBufDesc[i].bufPlanes[j].width ;
      inBufDesc[i].bufPlanes[j].frameROI.height       = inBufDesc[i].bufPlanes[j].height;

      sizeInput = inBufDesc[i].bufPlanes[j].width * inBufDesc[i].bufPlanes[j].height;
      inBufDesc[i].bufPlanes[j].buf = (uint8_t * )malloc(sizeInput); ;

      if(inBufDesc[i].bufPlanes[j].buf == NULL)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
    }
  }
 /*-----------------------------------------------------------------
  Initialize the input buffer descriptors for the input and output corner list coordinates
  -----------------------------------------------------------------*/
  for(i = 2; i < 4; i++)
  {
    inBufDescList[i]                                = &inBufDesc[i];
    inBufDesc[i].numPlanes                          = 1;
    inBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = 0;
    inBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = 0;
    inBufDesc[i].bufPlanes[0].width                 = numKeyPoints*sizeof(uint16_t)*2;
    inBufDesc[i].bufPlanes[0].height                = 1;
    inBufDesc[i].bufPlanes[0].frameROI.width        = inBufDesc[i].bufPlanes[0].width ;
    inBufDesc[i].bufPlanes[0].frameROI.height       = inBufDesc[i].bufPlanes[0].height;

    sizeInput = inBufDesc[i].bufPlanes[0].width * inBufDesc[i].bufPlanes[0].height;
    inBufDesc[i].bufPlanes[0].buf = (uint8_t * )malloc(sizeInput);

    if(inBufDesc[i].bufPlanes[0].buf == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
  }

  /*-----------------------------------------------------------------
   Initialize the output buffer descriptors for the output corners list coordinates
   -----------------------------------------------------------------*/

  sizeOutput[0] = 4*numKeyPoints;
  pitchOutput[0] = 4*VCOP_LK_NUM_KEY_PER_CALL;
  sizeOutput[1] = 2*numKeyPoints;
  pitchOutput[1] = 2*VCOP_LK_NUM_KEY_PER_CALL;

  for(i = 0; i < 2; i++)
  {
    outBufDescList[i]    = &outBufDesc[i];
    outBufDesc[i].numPlanes                          = 1;
    outBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = 0;
    outBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = 0;
    outBufDesc[i].bufPlanes[0].width                 = pitchOutput[i];
    outBufDesc[i].bufPlanes[0].height                = 1;
    outBufDesc[i].bufPlanes[0].frameROI.width        = outBufDesc[i].bufPlanes[0].width;
    outBufDesc[i].bufPlanes[0].frameROI.height       = outBufDesc[i].bufPlanes[0].height;
    outBufDesc[i].bufPlanes[0].buf =  (uint8_t * )malloc(sizeOutput[i]);

    if(outBufDesc[i].bufPlanes[0].buf == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
  }
#if ENABLE_FILE_READ
  for(i = 0; i < 2; i++)
  {
    if(i == 0)
    {
      fp = FOPEN(params->currFrameFile, "rb");
    }
    else
    {
      fp = FOPEN(params->prevFrameFile, "rb");
    }
    if(fp== NULL)
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }
    for(j = 0; j < params->numLevels; j++)
    {
      sizeInput = inBufDesc[i].bufPlanes[j].width * inBufDesc[i].bufPlanes[j].height;
      status = FREAD(inBufDesc[i].bufPlanes[j].buf,1,sizeInput,fp);
      if(status != sizeInput)
      {
        printf("Could not read the requested amount for data\n");
      }

    }
    FCLOSE(fp);
  }
#endif
  readInputFromTxtFile((unsigned short *)(inBufDesc[2].bufPlanes[0].buf),params->numKeyPoints,params->inKeyPointsFile);
  xyPoints = (uint16_t*)(inBufDesc[2].bufPlanes[0].buf);
  if(numKeyPoints > params->numKeyPoints)
  {
    for(i = params->numKeyPoints; i < numKeyPoints; i++)
    {
      xyPoints[2*i]   = xyPoints[2*i-2];
      xyPoints[2*i+1] = xyPoints[2*i-1];
    }
  }
  memcpy(inBufDesc[3].bufPlanes[0].buf,inBufDesc[2].bufPlanes[0].buf,4*numKeyPoints);
  memset(outBufDesc[1].bufPlanes[0].buf,0,2*numKeyPoints);
  vcop_minit();
  wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
  memset(wbufToZero, 0xcd, 31*1024);
  vcop_free(wbufToZero);

#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif

  profiler_start();
  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs,&outBufs,(IVISION_InArgs*)&lkInArgs,(IVISION_OutArgs *)&lkOutArgs);
  profiler_end_print(1);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Processing End\n");
#endif

  writeOutputToFile((unsigned short *)outBufDesc[0].bufPlanes[0].buf,(unsigned short *)outBufDesc[1].bufPlanes[0].buf,params->numKeyPoints,params->outKeyPointsFile);
  status = CompareOutputWithFile((unsigned short *)outBufDesc[0].bufPlanes[0].buf,(unsigned short *)outBufDesc[1].bufPlanes[0].buf,params->numKeyPoints,params->refKeyPointsFile);


  profiler_printStatus(status);


  fflush(stdout);
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

  for(i = 0; i < 2; i++)
  {
    for(j = 0; j < gParams.numLevels ; j++)
    {
      free(inBufDesc[i].bufPlanes[j].buf);
    }
  }
  for(i = 2; i < 4; i++)
  {
    free(inBufDesc[i].bufPlanes[0].buf);
  }

  for(j = 0; j < 2; j++)
  {
    free(outBufDesc[j].bufPlanes[0].buf);
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
  config_params  *params;
  int32_t         config_cmd;
  int8_t          configFileName[MAX_FILE_NAME_SIZE];

  report_printAppletInfo((int8_t *)"PYRAMID_LK_TRACKER_TI_VISION");

  params = (config_params *)(&gParams);

  if (argc > 1)
  {
    strcpy((char *)configFileName, argv[1]) ;
  }
  else
  {
    strcpy((char *)configFileName,CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((char *)configFileName , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Runing in default mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    /* Validate the applet */
    status = pyramidLkTrackerTest(params);
    return(status);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)FGETS(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",params->configParam);
    if(config_cmd == 0)
    {
      printf("End of config list found !\n");
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
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile((char *)configFileName, gsTokenMap_sof) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)params->testCaseDesc,params->performanceTestcase);
      printparams(gsTokenMap_sof,(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)params,sizeof(config_params)) ;

      /* Validate the applet */
      status = pyramidLkTrackerTest(params);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  FCLOSE(fp);


  return status;
}



