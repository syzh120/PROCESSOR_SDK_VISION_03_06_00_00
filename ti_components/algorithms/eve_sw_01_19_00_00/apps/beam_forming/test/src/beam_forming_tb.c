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
*  @file:      beam_forming_tb.c
*
*  @brief:     This file contains test code for Beam Forming applet
*
*
*  @date:      March 2016
*
*  @description:
*    This file contains test code to validate the frame level applet for
*    Beam Forming. It also checks the output against c reference
*    outputs and profiles the performance and computes the system
*    overheads.
**/
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "xdais_types.h"

#include "evestarterware.h"
#include "alg_osal.h"
#include "eve_profile.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"

#include "beam_forming_config.h"
#include "ibeam_forming_ti.h"
#include "vcop_beam_forming_cn.h"


#define ENABLE_TRACES     (0U)
#define ENABLE_PROFILE    (1U)
#define COMPARE_REFERENCE (1U)


#define MAX_CONFIG_LINE_SIZE     (300U)
#define MAX_FILE_NAME_SIZE       (200U)
#define MAX_PARAM_STRING_SIZE    (30U)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERROR_MSG() printf("Error at line: %5d in file: %22s of function: %s\n",__LINE__,__FILE__,__FUNCTION__)
#define ALIGN(x,y)        (((x + y - 1)/y)*y)

#define FIXED_PATTERN 0

#define DMEM_SIZE (16*1024U)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;


TIMemObject memObj_DMEM;

void* TestApp_AlignedMalloc(size_t required_bytes, size_t alignment)
{
    void* p1; // original block
    void** p2; // aligned block
    int offset = alignment - 1 + sizeof(void*);
    if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
    {
       return NULL;
    }
    p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void TestApp_AlignedFree(void *p)
{
    free(((void**)p)[-1]);
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

void memcpy2D(
    void        *dstPtr,
    const void  *srcPtr,
    uint16_t     width,
    uint16_t     height,
    int32_t      dstStride,
    int32_t      srcStride
)
{
  uint32_t rowCnt;

  for (rowCnt = 0 ; rowCnt < height; rowCnt++)
  {
      memcpy ((uint8_t *)dstPtr + rowCnt * dstStride, (uint8_t *)srcPtr + rowCnt * srcStride, width);
  }

  return;
}

void beam_forming_angle_association(int16_t *antennaData,
                                             int16_t  *steeringMatrix,
                                             uint16_t *pOutputAngleBuf,
                                             uint16_t *pOutputMaxEnergyBuf,
                                             uint16_t  numDetections,
                                             uint16_t  numAntennas,
                                             uint16_t  numAngles,
                                             uint16_t  beamFormingScaling,
                                             uint16_t  energyScaling,
                                             uint16_t  currAngleIdx)
{
  uint32_t antennaIdx;
  uint32_t detectionIdx;
  uint32_t * pTransposeAntennaData32  = NULL;
  uint32_t * pAntennaData32  = NULL;
  int16_t  * pMatMulOutput = NULL;
  uint32_t * pOutputEnergy =NULL;
  uint32_t baseAngleOffset;

  baseAngleOffset = currAngleIdx * numAngles;

  pAntennaData32 = (uint32_t *)antennaData;

  pTransposeAntennaData32 = (uint32_t *) malloc( numDetections * numAntennas * sizeof(uint32_t));

  pMatMulOutput = (int16_t *)malloc( numDetections * numAngles * sizeof(uint32_t));

  pOutputEnergy = (uint32_t *) malloc(numDetections * numAngles * sizeof(uint32_t ));

  for ( detectionIdx = 0 ; detectionIdx < numDetections; detectionIdx++)
   {
     for ( antennaIdx = 0 ; antennaIdx < numAntennas; antennaIdx++)
     {
       pTransposeAntennaData32[detectionIdx + antennaIdx * numDetections ] =
          pAntennaData32[antennaIdx + detectionIdx * numAntennas];
     }
   }

   vcop_beam_forming_cn(
     (int16_t *)pTransposeAntennaData32,
     pMatMulOutput,
     steeringMatrix,
     numDetections * sizeof(int16_t) * 2,
     numDetections,
     numAntennas,
     numAngles,
     beamFormingScaling);


   vcop_beam_energy_calculation_cn(
     pMatMulOutput,
     pOutputEnergy,
     numDetections,
     numAngles);

 vcop_beam_angle_association_cn(
   pOutputEnergy,
   (uint16_t *)pOutputAngleBuf,
   pOutputMaxEnergyBuf,
   baseAngleOffset,
   numDetections,
   numAngles,
   energyScaling);

 if ( pTransposeAntennaData32)
 {
   free(pTransposeAntennaData32);
   pTransposeAntennaData32 = NULL;
 }

 if ( pMatMulOutput )
 {
   free(pMatMulOutput);
   pMatMulOutput = NULL;
 }
 if ( pOutputEnergy)
 {
   free(pOutputEnergy);
   pOutputEnergy = NULL;
 }




}

void beam_forming_cn(IVISION_InBufs * inBufs,
             BEAM_FORMING_TI_CreateParams * createParams,
             BEAM_FORMING_TI_InArgs        * inArgs,
             BEAM_FORMING_TI_Coordinates * outputCorrdinates)
{

  BEAM_FORMING_TI_Coordinates * pCoordinateBuf  = NULL;
  uint32_t * pAntennaData    = NULL;
  uint32_t * pAntennaDataInterim    = NULL;
  int16_t * pSteeringMatrix = NULL;
  int16_t * currSteeringMatrix = NULL;
  uint16_t * pAngleBuf = NULL;
  uint16_t * pMaxEnergyBuf = NULL;
  uint16_t * pSortedAnetnnaDetectionIdBuf = NULL;


  uint32_t detectionIdx;
  uint32_t numDetectionPerGroup;
  uint32_t currBinIdx;
  uint32_t i;

  uint32_t baseDetectionIdx;

  int32_t * blockSortScratch1 = NULL;
  int32_t * blockSortScratch2 = NULL;


  blockSortScratch1= (int32_t*)malloc(4*1024);
  assert(blockSortScratch1 !=NULL);

  blockSortScratch2= (int32_t*)malloc(4*1024);
  assert(blockSortScratch2 !=NULL);


  pAntennaDataInterim = (uint32_t *)malloc( createParams->maxNumDetection* inArgs->numAntennas * sizeof(uint32_t));

  pAngleBuf = (uint16_t *) malloc(createParams->maxNumDetection * sizeof(uint16_t ));
  pMaxEnergyBuf = (uint16_t *) malloc(createParams->maxNumDetection * sizeof(uint16_t ));

  pSortedAnetnnaDetectionIdBuf = (uint16_t *) malloc(createParams->maxNumDetection * sizeof(uint32_t ));

  pAntennaData = (uint32_t *)inBufs->bufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF]->bufPlanes[0].buf;
  pSteeringMatrix = (int16_t *)inBufs->bufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF]->bufPlanes[0].buf;
  pCoordinateBuf = (BEAM_FORMING_TI_Coordinates *)inBufs->bufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF]->bufPlanes[0].buf;



  currBinIdx = 0;
  memset(pSortedAnetnnaDetectionIdBuf, 0, sizeof(uint32_t) * inArgs->numDetections);

  for ( i = 0; i < inArgs->numDetections; i++)
  {
    pSortedAnetnnaDetectionIdBuf[2 * i] = i;
  }

  numDetectionPerGroup = 0;
  baseDetectionIdx = 0;


  for ( detectionIdx = 0 ; detectionIdx < inArgs->numDetections; detectionIdx++)
  {
    if ( currBinIdx == pSortedAnetnnaDetectionIdBuf[2 * detectionIdx + 1] )
    {
      memcpy(pAntennaDataInterim + numDetectionPerGroup * inArgs->numAntennas,
             pAntennaData + detectionIdx * inArgs->numAntennas,
             inArgs->numAntennas * sizeof(uint32_t));


      numDetectionPerGroup++;

      continue;
    }

    currSteeringMatrix = pSteeringMatrix + currBinIdx *
                    2 * inArgs->numAngles * inArgs->numAntennas;

    beam_forming_angle_association((int16_t*)pAntennaDataInterim,
                                  currSteeringMatrix,
                                  pAngleBuf + baseDetectionIdx,
                                  pMaxEnergyBuf + baseDetectionIdx,
                                  numDetectionPerGroup,
                                  inArgs->numAntennas,
                                  inArgs->numAngles,
                                  inArgs->beamFormingScaling,
                                  inArgs->energyScaling,
                                  currBinIdx);



    baseDetectionIdx += numDetectionPerGroup;
    currBinIdx = pSortedAnetnnaDetectionIdBuf[2 * detectionIdx + 1];
    numDetectionPerGroup = 0;
    detectionIdx = detectionIdx - 1;

  }

  currSteeringMatrix = pSteeringMatrix + currBinIdx *
                      2 * inArgs->numAngles * inArgs->numAntennas;

  beam_forming_angle_association((int16_t*)pAntennaDataInterim,
                                  currSteeringMatrix,
                                  pAngleBuf + baseDetectionIdx,
                                  pMaxEnergyBuf + baseDetectionIdx,
                                  numDetectionPerGroup,
                                  inArgs->numAntennas,
                                  inArgs->numAngles,
                                  inArgs->beamFormingScaling,
                                  inArgs->energyScaling,
                                  currBinIdx);


  if ( createParams->coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_1)
  {
    memcpy(outputCorrdinates, pCoordinateBuf, sizeof(BEAM_FORMING_TI_Coordinates) * inArgs->numDetections);
  }
  else if ( createParams->coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_2)
  {
    memcpy2D(outputCorrdinates,
             pCoordinateBuf,
             sizeof(uint32_t),
             inArgs->numDetections,
             sizeof(BEAM_FORMING_TI_Coordinates),
             sizeof(uint32_t));
  }

  vcop_range_doppler_energy_angle_mapping_cn((uint32_t *)&outputCorrdinates->energy,
                                             pSortedAnetnnaDetectionIdBuf,
                                             pAngleBuf,
                                             pMaxEnergyBuf,
                                             sizeof(BEAM_FORMING_TI_Coordinates),
                                             inArgs->numDetections);
  if ( pAntennaDataInterim)
  {
    free(pAntennaDataInterim);
    pAntennaDataInterim = NULL;
  }

  if (pAngleBuf)
  {
    free(pAngleBuf);
    pAngleBuf = NULL;
  }

  if ( pMaxEnergyBuf)
  {
    free(pMaxEnergyBuf);
    pMaxEnergyBuf = NULL;
  }

  if ( pSortedAnetnnaDetectionIdBuf)
  {
    free(pSortedAnetnnaDetectionIdBuf);
    pSortedAnetnnaDetectionIdBuf = NULL;
  }

  if (blockSortScratch1)
  {
    free(blockSortScratch1);
    blockSortScratch1 = NULL;
  }

  if (blockSortScratch2)
  {
    free(blockSortScratch2);
    blockSortScratch2 = NULL;
  }



}
void fillDefaultConfig(sBEAM_FORMING_Config* params)
{
  strcpy((char *)params->testCaseName, "Beam Forming");
  strcpy((char *)params->antennaData, "");
  strcpy((char *)params->steeringMatrix, "");
  strcpy((char *)params->coordinateBuf, "");
  strcpy((char *)params->desc, "");
  params->performanceTestcase = 1;

  params->numAngles = 324;
  params->numAntennas   = 12;
  params->numDetections = 1024;
  params->maxNumDetections = 1024;
  params->beamFormingScaling = 15;
  params->energyScaling  = 15;

}


int32_t beamFormingTest(sBEAM_FORMING_Config* params)
{
#if (ENABLE_PROFILE)
  uint64_t     profile_tsc, profile_sctm;
#endif
  int16_t     *antennaData = NULL;
  int16_t     *steeringMatrix = NULL;
  BEAM_FORMING_TI_Coordinates     *coordinateBuf = NULL;
  BEAM_FORMING_TI_Coordinates     *refOutputCoordinates = NULL;
  BEAM_FORMING_TI_Coordinates     *targetOutputCoordinates = NULL;

  int32_t      i, j, k, numMemRec, status, fail = 0;
  TI_FILE     *fp;
  IALG_MemRec *memRec;
  char        *statusStr = NULL;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *    handle;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  BEAM_FORMING_TI_CreateParams   createParams;

  BEAM_FORMING_TI_InArgs  inArgs;
  BEAM_FORMING_TI_OutArgs outArgs;

  IVISION_InBufs        inBufs;
  IVISION_OutBufs       outBufs;

  IVISION_BufDesc    inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[BEAM_FORMING_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    outBufDesc[BEAM_FORMING_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[BEAM_FORMING_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(BEAM_FORMING_TI_OutArgs);

  inArgs.iVisionInArgs.size   = sizeof(BEAM_FORMING_TI_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;

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

  inBufs.numBufs  = BEAM_FORMING_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs = BEAM_FORMING_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < BEAM_FORMING_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]  = &inBufDesc[i];
  }

  for(i = 0 ; i < BEAM_FORMING_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i] = &outBufDesc[i];
  }

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.maxNumAngle     = params->numAngles;
  createParams.maxNumAntenna   = params->numAntennas;
  createParams.maxNumDetection = params->maxNumDetections;
  createParams.coordinateBufFormat = params->coordinateBufFormat;


  createParams.visionParams.algParams.size = sizeof(BEAM_FORMING_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;

#if (ENABLE_PROFILE)
  profiler_initStack(profiler_getSP());
  profiler_start();
#endif

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = BEAM_FORMING_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));

  status = BEAM_FORMING_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  printf("Beam Forming Applet Create Done\n");
#endif

  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec, numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = BEAM_FORMING_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                                                   memRec,
                                                   NULL,
                                                   (IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
  profiler_end_print(0);
/*  profile_create_tsc = gTest_TI_profileTsc;  */
#endif

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  printf("Beam Forming Applet Init Done\n");
#endif


  /*-----------------------------------------------------------------
  Set buffer descriptors
  -----------------------------------------------------------------*/
  /*-----------------------------------------------------------------
  Input buffer
  -----------------------------------------------------------------*/

  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].numPlanes = 1;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.width =
            params->numAntennas * params->maxNumDetections * sizeof(int16_t) * 2U;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.height = 1;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].width  =
            inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.width;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].height =
            inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].frameROI.height;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].buf =
       TestApp_AlignedMalloc(inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].width *
              inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].height, 128);

  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].numPlanes = 1;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].frameROI.width =
            params->maxNumDetections * sizeof(BEAM_FORMING_TI_Coordinates);
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].frameROI.height = 1;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].width  =
            inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].frameROI.width;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].height =
            inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].frameROI.height;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].buf =
       TestApp_AlignedMalloc(inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].width *
              inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].height, 128);

  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].numPlanes = 1;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].frameROI.width =
            params->numAntennas * params->numAngles * sizeof(int16_t) * 2U;

  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].frameROI.height = 1;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].width  =
            inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].frameROI.width;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].height =
            inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].frameROI.height;
  inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].buf =
       TestApp_AlignedMalloc(inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].width *
              inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].height, 128);

  /*-----------------------------------------------------------------
  Output buffer
  -----------------------------------------------------------------*/
  outBufDesc[BEAM_FORMING_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].buf = TestApp_AlignedMalloc(sizeof(BEAM_FORMING_TI_Coordinates) *
                                          params->maxNumDetections,
                                          128);


  /*-----------------------------------------------------------------
  Allocate Reference Buffers
  -----------------------------------------------------------------*/
  refOutputCoordinates = (BEAM_FORMING_TI_Coordinates *)malloc(sizeof(BEAM_FORMING_TI_Coordinates) * params->maxNumDetections);

  antennaData    = ( int16_t *)inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF].bufPlanes[0].buf;
  steeringMatrix = ( int16_t *)inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF].bufPlanes[0].buf;
  coordinateBuf  = ( BEAM_FORMING_TI_Coordinates *)inBufDesc[BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF].bufPlanes[0].buf;
  targetOutputCoordinates = ( BEAM_FORMING_TI_Coordinates *)outBufDesc[BEAM_FORMING_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].buf;

  memset (targetOutputCoordinates, 0, (sizeof(BEAM_FORMING_TI_Coordinates) * params->maxNumDetections));
  memset (refOutputCoordinates, 0xF, (sizeof(BEAM_FORMING_TI_Coordinates) * params->maxNumDetections));
  /*-----------------------------------------------------------------
        Open Input File. If non existant, fill input with data.
        -----------------------------------------------------------------*/
  fp = FOPEN((char *)params->antennaData, "rb");
  if(fp == NULL)
  {
    srand(params->randSeed);

    for(j = 0; j < params->numDetections; j++)
    {
      for(i = 0; i < params->numAntennas; i++)
      {
#if FIXED_PATTERN
        antennaData[(j * (2 * params->numAntennas)) +
                  (i * 2)] = i + j * 12;//rand();
        antennaData[(j * (2 * params->numAntennas)) +
                  (i * 2) + 1] = i - j * 15;//rand();
#else
        antennaData[(j * (2 * params->numAntennas)) +
                  (i * 2)] = rand();
        antennaData[(j * (2 * params->numAntennas)) +
                  (i * 2) + 1] = rand();
#endif

      }
    }
  } else
  {
      FREAD(antennaData, params->numAntennas* params->numDetections * sizeof(int16_t) * 2, 1, fp);
      FCLOSE(fp);
  }

  fp = FOPEN((char *)params->steeringMatrix, "rb");
  if(fp == NULL)
  {
    srand(params->randSeed);

    for(k = 0; k < 1; k++)
    {
      for(j = 0; j < params->numAngles; j++)
      {
        for(i = 0; i < params->numAntennas; i++)
        {
#if FIXED_PATTERN
          steeringMatrix[ (k * 2 * params->numAngles * params->numAntennas ) + (j * (2 * params->numAntennas)) +
                    (i * 2)] = i + j * 12+k*43;//rand();
          steeringMatrix[ (k * 2 * params->numAngles * params->numAntennas ) +(j * (2 * params->numAntennas)) +
                    (i * 2) + 1] = i*4  + j * 12 - k*3;//rand();
#else
          steeringMatrix[ (k * 2 * params->numAngles * params->numAntennas ) + (j * (2 * params->numAntennas)) +
                    (i * 2)] = rand();
          steeringMatrix[ (k * 2 * params->numAngles * params->numAntennas ) +(j * (2 * params->numAntennas)) +
                    (i * 2) + 1] = rand();
#endif

        }
      }
    }
  } else
  {
      FREAD(steeringMatrix, params->numAntennas* params->numAngles* sizeof(int16_t) * 2, 1, fp);
      FCLOSE(fp);
  }

  fp = FOPEN((char *)params->coordinateBuf, "rb");
  if(fp == NULL)
  {
    srand(params->randSeed);
    if (params->coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_1)
    {
      for(j = 0; j < params->numDetections; j++)
      {
#if FIXED_PATTERN
        coordinateBuf[j].range            = j * 1;//rand();
        coordinateBuf[j].velocity         = j * 3;//rand();
        coordinateBuf[j].angleBin         = (i+3*j) % params->numAngles;
        coordinateBuf[j].energy           = 12*i + 7 *j;
#else
        coordinateBuf[j].range            = rand();
        coordinateBuf[j].velocity         = rand();
        coordinateBuf[j].angleBin         = rand() % params->numAngles;
        coordinateBuf[j].energy           = rand();
#endif
      }
    }
    else if (params->coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_2)
    {
      uint16_t * coordinateBufFormat2 = (uint16_t*)coordinateBuf;
      for(j = 0; j < params->numDetections; j++)
      {
        coordinateBufFormat2[2*j] = rand();
        coordinateBufFormat2[2*j +1] = rand();
      }
    }
  } else
  {
    if (params->coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_1)
    {
      FREAD(coordinateBuf, params->numDetections * sizeof(BEAM_FORMING_TI_Coordinates), 1, fp);
      FCLOSE(fp);
    }
    else if (params->coordinateBufFormat == BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_2)
    {
      FREAD(coordinateBuf, params->numDetections * sizeof(uint32_t), 1, fp);
      FCLOSE(fp);
    }
  }


    inArgs.numAngles          = params->numAngles;
    inArgs.numAntennas        = params->numAntennas;
    inArgs.numDetections      = params->numDetections;
    inArgs.beamFormingScaling = params->beamFormingScaling;
    inArgs.energyScaling      = params->energyScaling;


  /*-----------------------------------------------------------------
        Fill Structuring Element buffer.
        -----------------------------------------------------------------*/

  /*-----------------------------------------------------------------
        Process.
        -----------------------------------------------------------------*/
#if ENABLE_TRACES
  printf("Processing start \n");
#endif
#if (ENABLE_PROFILE)
  profiler_start();
#endif

  status = handle->ivision->algProcess((IVISION_Handle)handle,
                                        &inBufs,
                                        &outBufs,
                                       (IVISION_InArgs *)&inArgs,
                                       (IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
  profiler_end_print(1);

  profile_tsc  = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];
#endif

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  printf("Processing End\n");
#endif


#if COMPARE_REFERENCE
  /*---------------------------------------------------------------------*/
  /*  Call the natural C implementation for  Beam Forming funcs.  */
  /*---------------------------------------------------------------------*/

  beam_forming_cn(&inBufs,
         &createParams,
         &inArgs,
         refOutputCoordinates); /* Reusing utArgs.bufDescription which is calculated inside
         the applet to avoid copying some code inside the applet */


  fail = 0;
  fail = memcmp(targetOutputCoordinates, refOutputCoordinates, sizeof(*refOutputCoordinates) * params->numDetections);

  for ( i = 0; i < params->numDetections; i++)
  {
    if ( ( targetOutputCoordinates[i].range!= refOutputCoordinates[i].range) ||
          ( targetOutputCoordinates[i].velocity!= refOutputCoordinates[i].velocity) ||
          ( targetOutputCoordinates[i].angleBin != refOutputCoordinates[i].angleBin) ||
          ( targetOutputCoordinates[i].energy!= refOutputCoordinates[i].energy))
    {
      fail = 1;
      printf(" Output of target is not matching to reference at detection %d \n", i);
      printf("Target Range    %d , Reference range    %d \n",targetOutputCoordinates[i].range, refOutputCoordinates[i].range);
      printf("Target velocity %d , Reference velocity %d \n",targetOutputCoordinates[i].velocity, refOutputCoordinates[i].velocity);
      printf("Target angleBin %d , Reference angleBin %d \n",targetOutputCoordinates[i].angleBin, refOutputCoordinates[i].angleBin);
      printf("Target energy   %d , Reference energy   %d \n",targetOutputCoordinates[i].energy, refOutputCoordinates[i].energy);
    }

  }

#endif


  statusStr = fail ? "FAILED" : "PASSED";

  profiler_printStatus(fail);

#if (ENABLE_PROFILE)
  printf("\n%-30s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s\n", \
          "Algorithm", "Status", "numDetection", "numAngles", "NumAnetnnas", "VCOPCycPerFr", "MegaCycPerFr", \
          "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
#if (VCOP_HOST_EMULATION)
  profile_sctm = 1;
  profile_tsc = 1;
#endif
{
  uint32_t * numDetectionPerGrp = NULL;
  uint32_t   totalNumDetection = 0;

  totalNumDetection = params->numDetections;



  printf("%-30s %10s %10d %10d %10d %15lld %15.2f %20.2f %10.2f %16.2f numActual points %d, overhead=%d%%\n",
      "Beam Forming",
      statusStr,
      params->numDetections,
      params->numAngles,
      params->numAntennas,
      profile_tsc,
      profile_tsc/1000000.0,
      30*(profile_tsc/1000000.0),
      profile_tsc/((float)params->numDetections* params->numAngles * params->numAntennas),
      profile_tsc/500000.0,
      totalNumDetection,
      ((profile_tsc - profile_sctm)*100)/profile_sctm);

  if (numDetectionPerGrp)
  {
    free(numDetectionPerGrp);
  }
}
#endif

  fflush(stdout);

EXIT_LOOP:

  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec, numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  if ( antennaData != NULL ) {
    TestApp_AlignedFree(antennaData);
  }

  if ( memRec != NULL ) {
    free(memRec);
  }

  if (steeringMatrix != NULL) {
    TestApp_AlignedFree(steeringMatrix);
  }

  if ( coordinateBuf != NULL ) {
    TestApp_AlignedFree(coordinateBuf);
  }

  if ( targetOutputCoordinates != NULL ) {
    TestApp_AlignedFree(targetOutputCoordinates);
  }

  if ( refOutputCoordinates != NULL ) {
    free(refOutputCoordinates);
  }


#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}


int main(int argc, char *argv[])
{
  TI_FILE *fp;
  char     configFile[FILE_NAME_SIZE] = {0};
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
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  report_printAppletInfo((int8_t *)"BEAM_FORMING_TI_VISION");

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
      printf("End of config list found !\n");
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

      printf("\n Processing config file %s !\n", configFile);

      fillDefaultConfig(&gConfig_beam_forming);

      status = readparamfile(configFile, &gsTokenMap_beam_forming[0]);
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_beam_forming.testCaseName, (int8_t *)gConfig_beam_forming.desc,
                            gConfig_beam_forming.performanceTestcase);
      printparams(&gsTokenMap_beam_forming[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_beam_forming),
                            sizeof(sBEAM_FORMING_Config));

      /* Validate the applet */
      status = beamFormingTest(&gConfig_beam_forming);
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

#if VCOP_HOST_EMULATION
    printf("Press any key to continue ...\n");
    scanf("%c", configFile);
#endif

  return status;
}

