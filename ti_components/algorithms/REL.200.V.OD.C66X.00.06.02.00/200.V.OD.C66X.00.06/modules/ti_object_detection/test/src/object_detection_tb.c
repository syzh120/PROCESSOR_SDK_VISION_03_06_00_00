/*
* module name       :TI Object Detection
*
* module descripton :Detection of pedestrians, traffic signs and vehicles using TI’s C66x DSP
*
*/
/*

Copyright (c) [2014] – [2017] Texas Instruments Incorporated

All rights reserved not granted herein.
   
Limited License.

Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.

Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution

Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:

*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.

*       any redistribution and use are licensed by TI for use only with TI Devices.

*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.

If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:

*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.

*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.

Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.

DISCLAIMER.

THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/** @file object_detection_tb.c
*
*  @brief  This is a test bench file for object detection module.
*          This test interface is common for PD and TSR.
*
*  @date   July 2014
*
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "xdais_types.h"
#include "object_detection_config.h"
#include "iobjdet_ti.h"

#include "ti_mem_manager.h"
#include "ti_file_io.h"
#include "cache.h"

#define DISABLE_FILE_IO    (0)
#define IO_PERSISTENT_DATA (0)
#define DISPLAY_HEADER     (0)
#define DUMP_OD_STATS      (0)

#if (HOST_EMULATION)
#define DISABLE_FILE_IO    (0)
#endif

#if (!HOST_EMULATION)

void _TSC_enable();
long long _TSC_read();

#define L1D_SRAM_ADDR (0x00F00000)

void SetMAR()
{

  uint32_t i ;

  uint32_t* MAR = (uint32_t*)0x01848000 ; //MAR_128

  for(i = 128 ;i <= 133 ; i++) // 0x80000000 - 0x85FFFFFF only cached! prev value 160
  {
    MAR[i] = 0x1;
  }
  
  for(i = 144 ;i <= 159 ; i++) //0x90000000 - 0x9FFFFFFF cached
  {
    MAR[i] = 0x1;
  }
  return ;
}

void InitCache()
{
  /*-------------------------------------------------------------------------*/
  /* 4-> full 256 KB as cache, 3-> 128KB, 2 -> 64KB, 1-> 32KB                */
  /* IMPORTANT :: Currently 0 KB of L2 is assumed to be SRAM, hence in final */
  /* application any amount L2 can be configured as SRAM, but DMVAL will not */
  /* use that. Only thing here important is that if in application full L2 is*/
  /* configured as cache then standalone and final application performance   */
  /* numbers will match. otherwise no functionality issue.                    */
  /*-------------------------------------------------------------------------*/
  *L2CFG  = 2;

  /*-------------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                                 */
  /* Nothing in L1P is assumed as SRAM, so no dependency from final applicati*/
  /* -on configuration. Only thing if full L1P is configured as cache then   */
  /* standalone and application performance numbers will match.              */
  /*-------------------------------------------------------------------------*/
  *L1PCFG = 4;

 /*--------------------------------------------------------------------------*/
  /* 1 -> 4 KB, 2-> 8KB, 3 ->16 KB, 4 -> 32KB as cache                       */
  /* Currently 4KB as cache has been allocated for L1D, Rest 28 KB is configu*/
  /* red as SRAM. Any change in cache configuration should be done in conjuca*/
  /* of linker command file modification in test applciation                 */
  /* IMPORTANT :: Here 28 KB of L1 D is assumed as SRAM hence there is depend*/
  /* -dency from final applcaition configuration of L1D. If atleast 28 KB of */
  /* L1D is not configured as SRAM in final application then that will be a  */
  /* functional issue.                                                       */
  /*-------------------------------------------------------------------------*/
  *L1DCFG = 4;

  SetMAR() ;
}

#endif //!HOST_EMULATION

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Feature Plane classification applet
 *
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_ROI_MEMREC,
  ALG_TRACKER_MEMREC,
  ALG_INT_EDMA_MEMREC,
  ALG_INT_SCRATCH_MEMREC,
  ALG_EXT_SCRATCH_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @struct  TI_OD_Obj
 *  @brief   This structure is the main handle of OD algorithm
 *
 *  @param ivision           : All public function pointers
 *  @param algState          : State of algorithm to indicate
 *  @param numMemRecs        : Number of memory records
 *  @param memRec            : Array of memory records
 *  @param edma3RmLldHandle  : Pointer to EDMA3 LLD resource manager
 *  @param maxImageWidth     : Maximum width of input image
 *  @param maxImageHeight    : Maximum height of input image
 *  @param maxScales         : Maximum scales of input image
*/
typedef struct
{
  IVISION_Fxns      *ivision;
  uint8_t           algState;
  uint32_t          numMemRecs;
  IALG_MemRec       memRec[NUM_MEMRECS];
  void             *edma3RmLldHandle;
  uint16_t          maxImageWidth;
  uint16_t          maxImageHeight;
  uint16_t          maxScales;
  int32_t           firstTimeFlag;
  int32_t           frameNum;

} TI_OD_Obj;

#define PRINT_ERROR_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define MAX_FEATURE_PLANE_SIZE (8 * 1024 * 1024)
#define MAX_ADABOOST_WEIGHT_SIZE_PD  (40 * 1024)
#define MAX_ADABOOST_WEIGHT_SIZE_TSR (25 * 1024)
#define MAX_ADABOOST_WEIGHT_SIZE_VD  (25 * 1024)

#define DMEM_SIZE (224 * 1024)

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
    if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else if(memRec[i].space == IALG_DARAM0) {
       //L1D SRAM space, curretly alg requires 24kb SRAM and 8kb cache.
#if (!HOST_EMULATION)
      memRec[i].base = (void *)L1D_SRAM_ADDR;
#else
      memRec[i].base = (void *)malloc( memRec[i].size);
#endif
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

int32_t TestApp_storePersistent(IALG_MemRec * memRec,int32_t numMemRec)
{
  char fileName[] = "C:\\Work\\C66\\ODFlow\\data\\od_memtab_";
  FILE *fp;
  int32_t i;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].attrs == IALG_PERSIST)
    {
       char newName[512];
       char buffer[16];

       strcpy(newName, fileName);
       sprintf(buffer, "%d", i);
       strcat(newName, buffer);
       strcat(newName, ".bin");

       fp = fopen(newName, "wb");

       if(fp == NULL)
       {
          printf("Unable to store persistent data!\n");
          return IALG_EFAIL;
       }

       fwrite((void *)memRec[i].base,1, memRec[i].size,fp);

       fclose(fp);
    }
  }
  return IALG_EOK;
}

int32_t TestApp_restorePersistent(IALG_MemRec * memRec,int32_t numMemRec)
{
  char fileName[] = "C:\\Work\\C66\\ODFlow\\data\\od_memtab_";
  FILE *fp;
  int32_t i;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].attrs == IALG_PERSIST)
    {
       char newName[512];
       char buffer[16];

       strcpy(newName, fileName);
       sprintf(buffer, "%d", i);
       strcat(newName, buffer);
       strcat(newName, ".bin");

       fp = fopen(newName, "rb");

       if(fp == NULL)
       {
          printf("Unable to restore persistent file!\n");
          return IALG_EFAIL;
       }

       if(i == 0)
       {
           TI_OD_Obj sObj;
           TI_OD_Obj *pObj;

           fread((void *)&sObj,1, memRec[i].size,fp);

           pObj = (TI_OD_Obj *)memRec[i].base;

           pObj->firstTimeFlag = sObj.firstTimeFlag;
           pObj->frameNum       = sObj.frameNum;

       }
       else
       {
           fread((void *)memRec[i].base,1, memRec[i].size,fp);
       }

       fclose(fp);
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
    if(memRec[i].space == IALG_EXTERNAL) {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

#pragma DATA_SECTION(featData,".featDat");
uint8_t featData[MAX_FEATURE_PLANE_SIZE];

#pragma DATA_SECTION(extWeightsPD,".extWeightsPD");
uint8_t extWeightsPD[MAX_ADABOOST_WEIGHT_SIZE_PD];

#pragma DATA_SECTION(extWeightsTSR,".extWeightsTSR");
uint8_t extWeightsTSR[MAX_ADABOOST_WEIGHT_SIZE_TSR];

#pragma DATA_SECTION(extWeightsVD,".extWeightsVD");
uint8_t extWeightsVD[MAX_ADABOOST_WEIGHT_SIZE_VD];

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs)
{
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->numPlanes                          = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].width                 = MAX_FEATURE_PLANE_SIZE;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].width;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].planeType             = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf                   = &featData[0];

  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->numPlanes                          = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].width                 = MAX_ADABOOST_WEIGHT_SIZE_PD;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].width;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].planeType             = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].buf                   = &extWeightsPD[0];

  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->numPlanes                          = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].width                 = MAX_ADABOOST_WEIGHT_SIZE_TSR;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].width;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].planeType             = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].buf                   = &extWeightsTSR[0];

  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->numPlanes                          = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].width                 = MAX_ADABOOST_WEIGHT_SIZE_VD;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].width;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].planeType             = 0;
  inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].buf                   = &extWeightsVD[0];

  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->numPlanes                          = 1;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].width                 = TI_OD_OUT_BUFDESC_LIST_SIZE + 16;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].height                = 1;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.width        = TI_OD_OUT_BUFDESC_LIST_SIZE + 16;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.height       = 1;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].planeType             = 0;

  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->numPlanes                          = 1;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].width                 = TI_OD_OUT_BUFDESC_LIST_SIZE + 16;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].height                = 1;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.width        = TI_OD_OUT_BUFDESC_LIST_SIZE + 16;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.height       = 1;
  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].planeType             = 0;

  outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].buf = malloc(outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].width * outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].height);
  if((outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }
  memset(outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].buf ,0,outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].width * outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].height);

  outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].buf = malloc(outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].width * outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].height);
  if((outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }
  memset(outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].buf ,0,outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].width * outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].height);

  return IALG_EOK;
}

int32_t TestApp_readInput(IVISION_InBufs * inBufs,int32_t currFrameNum, char * fileName)
{
  TI_OBJECT_FEATURES_outputMetaData *metaData;
  int32_t metaDataSize;
  int32_t size;

#ifdef USE_HOST_FILE_IO
  HOSTFILE * fp;
#else
  FILE * fp;
#endif

  fp = FOPEN(fileName, "rb");

  if(fp == NULL)
  {
      printf("Unable to open Input file!\n");
      return (-1);
  }
  metaDataSize = sizeof(TI_OBJECT_FEATURES_outputMetaData);
  FREAD(inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf, 1, metaDataSize, fp);
  metaData = (TI_OBJECT_FEATURES_outputMetaData *)inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf;
  size = metaData->featBufSize;

  FSEEK(fp, (currFrameNum * size), SEEK_SET);

#if (!DISABLE_FILE_IO)

#ifdef USE_HOST_FILE_IO
{
    int32_t nChunks, reminder, ctr;
    int32_t ONE_MEGA_BYTE = 0x100000;

    nChunks  = size / ONE_MEGA_BYTE;
    reminder = size % ONE_MEGA_BYTE;

    for(ctr = 0; ctr < nChunks; ctr++)
       FREAD((void *)((uint32_t)inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf + (ctr * ONE_MEGA_BYTE)),1,ONE_MEGA_BYTE,fp);

    if(reminder)
       FREAD((void *)((uint32_t)inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf + (ctr * ONE_MEGA_BYTE)),1,reminder,fp);
}
#else

  FREAD((void *)((uint32_t)inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf),1,size,fp);

#endif
  metaData = (TI_OBJECT_FEATURES_outputMetaData *)inBufs->bufDesc[TI_OD_IN_BUFDESC_FEATURE_PLANES]->bufPlanes[0].buf;
#if DISPLAY_HEADER
  printf("size        : %d \n", metaData->size);
  printf("featBufSize : %d \n", metaData->featBufSize);
  printf("numScales   : %d \n", metaData->numScales);
  printf("numPlanes   : %d \n", metaData->numPlanes);
  printf("featFormat  : %d \n", metaData->featFormat);
#endif

#endif

  FCLOSE(fp);

  return (0);
}

int32_t TestApp_readWeights(IVISION_InBufs * inBufs, uint8_t objType, char * fileName)
{
  int32_t size;
  uint8_t *pDst;
  FILE * fp;

  fp = fopen(fileName, "rb");

  if(fp == NULL)
  {
      printf("Unable to open Input file!\n");
      return (-1);
  }

  if(objType == TI_OD_PEDESTRIAN)
  {
	  size = MAX_ADABOOST_WEIGHT_SIZE_PD;
	  pDst = (uint8_t *) inBufs->bufDesc[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]->bufPlanes[0].buf;
  }
  else if(objType == TI_OD_TRAFFIC_SIGN)
  {
	  size = MAX_ADABOOST_WEIGHT_SIZE_TSR;
	  pDst = (uint8_t *) inBufs->bufDesc[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]->bufPlanes[0].buf;
  }
  else if(objType == TI_OD_VEHICLE)
  {
	  size = MAX_ADABOOST_WEIGHT_SIZE_VD;
	  pDst = (uint8_t *) inBufs->bufDesc[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]->bufPlanes[0].buf;
  }

#if (!DISABLE_FILE_IO)
  fread((void *)pDst,1,size,fp);
#endif

  fclose(fp);

  return (0);
}

int32_t TestApp_writeOutput(IVISION_OutBufs * outBufs, char * detListFileName, char * objListFileName)
{
  int32_t size;

  FILE * fp1, *fp2;

#if IO_PERSISTENT_DATA
  fp1 = fopen(detListFileName, "wb");
  fp2 = fopen(objListFileName, "wb");
#else
  fp1 = fopen(detListFileName, "ab");
  fp2 = fopen(objListFileName, "ab");
#endif

  if(fp1 == NULL)
  {
      printf("Unable to open Output file! %s\n", detListFileName);
      return (-1);
  }

  if(fp2 == NULL)
  {
      printf("Unable to open Output file! %s\n", objListFileName);
      return (-1);
  }

  size = sizeof(TI_OD_outputList);

  fwrite((void *)((uint32_t)outBufs->bufDesc[TI_OD_OUT_BUFDESC_DETECTION_LIST]->bufPlanes[0].buf),1,size,fp1);

  fwrite((void *)((uint32_t)outBufs->bufDesc[TI_OD_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].buf),1,size,fp2);

  fclose(fp1);

  fclose(fp2);

  return (0);
}

int32_t objectDetectionTest(sObjectDetection_Config * testcaseParams)
{
  int32_t numMemRec;
  int32_t j;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t testcase;
  uint8_t  levelCnt=0;
  FILE *fpOut ;

#if (!HOST_EMULATION)
  long long  t0, t1;
  _TSC_enable();
#endif

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  TI_OD_CreateParams   createParams;

  TI_OD_InArgs      inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   pdWgtBufDesc;
  IVISION_BufDesc   tsrWgtBufDesc;
  IVISION_BufDesc   vdWgtBufDesc;
  IVISION_BufDesc   *inBufDescList[TI_OD_IN_BUFDESC_TOTAL];

  TI_OD_OutArgs     outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDescObjects;
  IVISION_BufDesc   outBufDescDetections;
  IVISION_BufDesc   *outBufDescList[TI_OD_OUT_BUFDESC_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(TI_OD_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(TI_OD_InArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  TI_OD_objectDescriptor *pObjDesc;
  TI_OD_outputList *pOutputList;
  uint32_t frameIdx;

  objectDetection_numTestCases  = 1;

  for (testcase = 0 ; testcase < objectDetection_numTestCases; testcase++)
  {

    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = TI_OD_IN_BUFDESC_TOTAL;
    outBufs.numBufs  = TI_OD_OUT_BUFDESC_TOTAL;

    inBufDescList[TI_OD_IN_BUFDESC_FEATURE_PLANES]        = &inBufDesc;
    inBufDescList[TI_OD_IN_BUFDESC_PD_ADABOOST_WEIGHTS]   = &pdWgtBufDesc;
    inBufDescList[TI_OD_IN_BUFDESC_TSR_ADABOOST_WEIGHTS]  = &tsrWgtBufDesc;
    inBufDescList[TI_OD_IN_BUFDESC_VD_ADABOOST_WEIGHTS]   = &vdWgtBufDesc;

    outBufDescList[TI_OD_OUT_BUFDESC_OBJECT_LIST]     = &outBufDescObjects;
    outBufDescList[TI_OD_OUT_BUFDESC_DETECTION_LIST]  = &outBufDescDetections;

    createParams.maxImageWidth  = testcaseParams[testcase].maxImageWidth;
    createParams.maxImageHeight = testcaseParams[testcase].maxImageHeight;
    createParams.maxScales      = testcaseParams[testcase].maxScales;
    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    createParams.edma3RmLldHandle   = NULL;

    /*-----------------------------------------------------------------
    Create DMEM Handle
    -----------------------------------------------------------------*/
    TI_CreateMemoryHandle(&memObj_DMEM, DMEM_SCRATCH, DMEM_SIZE);

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = TI_OD_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = TI_OD_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
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
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = TI_OD_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));


    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

#if IO_PERSISTENT_DATA
    TestApp_restorePersistent(memRec,numMemRec);
#endif

    inArgs.iVisionInArgs.subFrameInfo       = 0;
    inArgs.iVisionInArgs.size               = sizeof(TI_OD_InArgs);

    inBufDesc.numPlanes                     = 1;
    pdWgtBufDesc.numPlanes                  = 1;
    tsrWgtBufDesc.numPlanes                 = 1;
    vdWgtBufDesc.numPlanes                  = 1;

    outBufDescObjects.numPlanes             = 1;
    outBufDescDetections.numPlanes          = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs);

    fpOut = fopen((char *)testcaseParams[testcase].logFileName,"w+");
    if(fpOut == NULL)
    {
      printf("Unable to open output file\n");
      goto EXIT_LOOP;
    }

    inArgs.detectionMode                    = testcaseParams[testcase].detectionMode;
    inArgs.roiPreset                        = testcaseParams[testcase].roiPreset;
    inArgs.refreshInterval                  = testcaseParams[testcase].refreshInterval;

    inArgs.pdConfig.enablePD                = testcaseParams[testcase].pdConfig.enablePD;
    inArgs.pdConfig.detectorTypePD          = testcaseParams[testcase].pdConfig.detectorTypePD;
    inArgs.pdConfig.trackingMethodPD        = testcaseParams[testcase].pdConfig.trackingMethodPD;
    inArgs.pdConfig.useExtWeightsPD         = testcaseParams[testcase].pdConfig.useExtWeightsPD;
    inArgs.pdConfig.softCascadeThPD         = testcaseParams[testcase].pdConfig.softCascadeThPD;
    inArgs.pdConfig.strongCascadeThPD       = testcaseParams[testcase].pdConfig.strongCascadeThPD;

    inArgs.tsrConfig.enableTSR              = testcaseParams[testcase].tsrConfig.enableTSR;
    inArgs.tsrConfig.detectorTypeTSR        = testcaseParams[testcase].tsrConfig.detectorTypeTSR;
    inArgs.tsrConfig.trackingMethodTSR      = testcaseParams[testcase].tsrConfig.trackingMethodTSR;
    inArgs.tsrConfig.recognitionMethodTSR   = testcaseParams[testcase].tsrConfig.recognitionMethodTSR;
    inArgs.tsrConfig.useExtWeightsTSR       = testcaseParams[testcase].tsrConfig.useExtWeightsTSR;
    inArgs.tsrConfig.softCascadeThTSR       = testcaseParams[testcase].tsrConfig.softCascadeThTSR;
    inArgs.tsrConfig.strongCascadeThTSR     = testcaseParams[testcase].tsrConfig.strongCascadeThTSR;

    inArgs.vdConfig.enableVD                = testcaseParams[testcase].vdConfig.enableVD;
    inArgs.vdConfig.detectorTypeVD          = testcaseParams[testcase].vdConfig.detectorTypeVD;
    inArgs.vdConfig.trackingMethodVD        = testcaseParams[testcase].vdConfig.trackingMethodVD;
    inArgs.vdConfig.useExtWeightsVD         = testcaseParams[testcase].vdConfig.useExtWeightsVD;
    inArgs.vdConfig.softCascadeThVD         = testcaseParams[testcase].vdConfig.softCascadeThVD;
    inArgs.vdConfig.strongCascadeThVD       = testcaseParams[testcase].vdConfig.strongCascadeThVD;

    //Set reserved params to 0 for normal operation
    inArgs.reserved0  = 0;
    inArgs.reserved1  = 0;
    inArgs.reserved2  = 0;
    inArgs.reserved3  = 0;

    printf("Running Object Detection...\n");

    if(inArgs.pdConfig.enablePD && inArgs.pdConfig.useExtWeightsPD)
        TestApp_readWeights(&inBufs, TI_OD_PEDESTRIAN, (char *)testcaseParams[testcase].pdWeightsFileName);

    if(inArgs.tsrConfig.enableTSR && inArgs.tsrConfig.useExtWeightsTSR)
        TestApp_readWeights(&inBufs, TI_OD_TRAFFIC_SIGN, (char *)testcaseParams[testcase].tsrWeightsFileName);

    if(inArgs.vdConfig.enableVD && inArgs.vdConfig.useExtWeightsVD)
        TestApp_readWeights(&inBufs, TI_OD_VEHICLE, (char *)testcaseParams[testcase].vdWeightsFileName);

    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {

      TI_OD_Obj *objPtr = (TI_OD_Obj *)memRec[0].base;
      printf("Frame %d : ",objPtr->frameNum);
      fprintf(fpOut,"Frame %d detections \n", objPtr->frameNum);

      TestApp_readInput(&inBufs,frameIdx, (char *)testcaseParams[testcase].inFileName);

#if (!HOST_EMULATION)
      t0 = _TSC_read();
#endif
      status = handle->ivision->algProcess((IVISION_Handle)handle,
                                            &inBufs,
                                            &outBufs,
                                           (IVISION_InArgs  *)&inArgs,
                                           (IVISION_OutArgs *)&outArgs);
#if (!HOST_EMULATION)
      t1 = _TSC_read();
      printf(" Cycles - %8d ", t1-t0);
#endif

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

#if (DUMP_OD_STATS)

      printf(" %8d, %8d,", outArgs.cellSumCycles, outArgs.cellSumPoints);

      if(inArgs.pdConfig.enablePD)
      {
          printf(" %8d, %8d, %8d, %8d, %8d, %8d, %8d,", outArgs.pdStats.detectorCycles, outArgs.pdStats.groupingCycles, outArgs.pdStats.trackingCycles, outArgs.pdStats.numDetected, outArgs.pdStats.numGrouped, outArgs.pdStats.numTracked, outArgs.pdStats.reserved0);
      }

      if(inArgs.tsrConfig.enableTSR)
      {
          printf(" %8d, %8d, %8d, %8d, %8d, %8d, %8d,", outArgs.tsrStats.detectorCycles, outArgs.tsrStats.groupingCycles, outArgs.tsrStats.trackingCycles, outArgs.tsrStats.numDetected, outArgs.tsrStats.numGrouped, outArgs.tsrStats.numTracked, outArgs.tsrStats.reserved0);
      }

      if(inArgs.vdConfig.enableVD)
      {
          printf(" %8d, %8d, %8d, %8d, %8d, %8d, %8d,", outArgs.vdStats.detectorCycles, outArgs.vdStats.groupingCycles, outArgs.vdStats.trackingCycles, outArgs.vdStats.numDetected, outArgs.vdStats.numGrouped, outArgs.vdStats.numTracked, outArgs.vdStats.reserved0);
      }
#endif
      printf("\n");
#if IO_PERSISTENT_DATA
      status = TestApp_storePersistent(memRec,numMemRec);
      if(status != IALG_EOK)
      {
         PRINT_ERROR_MSG();
         goto EXIT_LOOP;
      }
#endif

      status = TI_OD_Report_Error(outArgs.errorCode);

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      TestApp_writeOutput(&outBufs, (char *)testcaseParams[testcase].detListFileName, (char *)testcaseParams[testcase].objListFileName);

      pOutputList  = (TI_OD_outputList *)outBufs.bufDesc[0]->bufPlanes[0].buf;
      pObjDesc     = &pOutputList->objDesc[0];

      for(j = 0; j < pOutputList->numObjects; j++)
      {
        if(pObjDesc->objType == TI_OD_PEDESTRIAN)
        {
            fprintf(fpOut,"PD at %4d,%4d,%4d,%4d with ",pObjDesc->xPos, pObjDesc->yPos, pObjDesc->objWidth, pObjDesc->objHeight);
            fprintf(fpOut,"Score =       %4f  Curr scale :       %4f",pObjDesc->objScore, pObjDesc->objScale);
        }

        if(pObjDesc->objType == TI_OD_TRAFFIC_SIGN)
        {
            fprintf(fpOut,"TSR at %4d,%4d,%4d,%4d with ",pObjDesc->xPos, pObjDesc->yPos, pObjDesc->objWidth, pObjDesc->objHeight);
            fprintf(fpOut,"Score =       %4f  Curr scale :       %4f",pObjDesc->objScore, pObjDesc->objScale);
        }

        if(pObjDesc->objType == TI_OD_VEHICLE)
        {
            fprintf(fpOut,"VD at %4d,%4d,%4d,%4d with ",pObjDesc->xPos, pObjDesc->yPos, pObjDesc->objWidth, pObjDesc->objHeight);
            fprintf(fpOut,"Score =       %4f  Curr scale :       %4f",pObjDesc->objScore, pObjDesc->objScale);
        }

        fprintf(fpOut,"\n");
        pObjDesc++;
      }

    }
    fprintf(fpOut,"\n");
    printf("Processing complete!\n");
EXIT_LOOP:
    if(fpOut)
    {
        fflush(fpOut);
        fclose(fpOut);
    }

#if (!IO_PERSISTENT_DATA)
    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
    }
#endif

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

    for ( levelCnt = 0 ; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      if ( inBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        //free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < pdWgtBufDesc.numPlanes ; levelCnt++)
    {
      if ( pdWgtBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        //free(pdWgtBufDesc.bufPlanes[levelCnt].buf);
      }
    }

     for ( levelCnt = 0 ; levelCnt < tsrWgtBufDesc.numPlanes ; levelCnt++)
    {
      if ( tsrWgtBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        //free(tsrWgtBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < vdWgtBufDesc.numPlanes ; levelCnt++)
    {
      if ( vdWgtBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        //free(vdWgtBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDescObjects.numPlanes ; levelCnt++)
    {
      if ( outBufDescObjects.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDescObjects.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDescDetections.numPlanes ; levelCnt++)
    {
      if ( outBufDescDetections.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDescDetections.bufPlanes[levelCnt].buf);
      }
    }

  }
  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[FILE_NAME_SIZE]={0};

#if (!HOST_EMULATION)
  InitCache();
#endif

#ifdef USE_HOST_FILE_IO
    ti_fileio_init();
#endif

#if (!HOST_EMULATION)
  _TSC_enable();
#endif

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
#if IO_PERSISTENT_DATA
    strcpy(configFile,"C:\\Work\\C66\\ODFlow\\od\\object_detection.cfg");
#else
    strcpy(configFile,"../testvecs/config/object_detection.cfg");
#endif
  }
  
  status = readparamfile(configFile, &gsTokenMap_objectDetection[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }
  
  /* Validate the applet */
  status = objectDetectionTest(gConfig_objectDetection);

  return status;
}



