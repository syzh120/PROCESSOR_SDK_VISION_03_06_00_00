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


/** @file feature_plane_comp_tb.c
*
*  @brief  This file contains test code for FAST9 corner detect applet
*
*
*  @date   Dec 2013
*
*  Description
*    This file contains test code to validate the frame level applet fast9 corner detect.
*    It also checks the output against c reference outputs and profiles the performance
*    and computes the system overheads.
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
#include "feature_plane_comp_config.h"
#include "iti_pd_feature_plane_computation_ti.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"
#include "iyuv_padding_ti.h"
#include "vcop_yuv_scalar_cn.h"
#include "iyuv_scalar_ti.h"
#include "ifilter_2d_ti.h"
#include "edma_utils_memcpy.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

#define DISABLE_FILE_IO 0
#define ENABLE_TRACES 1
#define ENABLE_COMPARE 1
#define ALIGN_T0_32(x) (((x+31)/32)*32)
#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)

#define Q_FORMATE_SCALE_RATIO                   (12)
#define FEATURE_PLANE_COMP_Q_SHIFT              (4)


extern uint32_t PD_FEATURE_TI_LumaSCTM[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];
extern uint32_t PD_FEATURE_TI_chromaSCTM[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];
extern uint32_t PD_FEATURE_TI_slidingSumSCTM[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];


uint8_t *lumaImageScales[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES]  ;
uint8_t *chromaImageScales[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];
uint16_t ImageScalesPitchs[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (20*1024 )

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];


TIMemObject memObj_DMEM;
IVISION_BufDesc   inBufDesc[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];

static uint16_t scaleRatiosQ12[MAX_SCALE_STEPS] = {0};

#define FILTER_COEF_WIDTH   3
#define FILTER_COEF_HEIGHT  3
uint8_t filterCoeff[FILTER_COEF_WIDTH * FILTER_COEF_HEIGHT]=
{
  1, 2, 1,
  1, 2, 1,
  0, 0, 0,
};


void TestApp_FillInBuffDesc(scalePrams_t *scaleParams, uint8_t * lumaPtr, uint16_t lumaPitch, uint8_t * ChromaPtr, uint16_t ChromaPitch, uint8_t numScales, uint8_t scaleSteps)
{
  uint8_t i;
  for(i = 0; i < numScales; i++)
  {
    inBufDesc[i].numPlanes                          = 2;
    inBufDesc[i].bufPlanes[0].buf                   = lumaImageScales[i];
    inBufDesc[i].bufPlanes[0].width                 = ImageScalesPitchs[i];
    inBufDesc[i].bufPlanes[0].height                = scaleParams[i].height;
    inBufDesc[i].bufPlanes[0].frameROI.width        = scaleParams[i].width;
    inBufDesc[i].bufPlanes[0].frameROI.height       = scaleParams[i].height;
    inBufDesc[i].bufPlanes[0].planeType             = 0; //Luma Y
    inBufDesc[i].bufPlanes[1].buf                   = chromaImageScales[i];
    inBufDesc[i].bufPlanes[1].width                 = ImageScalesPitchs[i];
    inBufDesc[i].bufPlanes[1].height                = scaleParams[i].height/2;
    inBufDesc[i].bufPlanes[1].frameROI.width        = scaleParams[i].width;
    inBufDesc[i].bufPlanes[1].frameROI.height       = scaleParams[i].height/2;
    inBufDesc[i].bufPlanes[1].planeType             = 1; //Chroma UV

    if(i%scaleSteps)
    {
      inBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = 0;
      inBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = 0;
      inBufDesc[i].bufPlanes[1].frameROI.topLeft.x    = 0;
      inBufDesc[i].bufPlanes[1].frameROI.topLeft.y    = 0;
    }
    else
    {
      inBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = scaleParams[i].x;
      inBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = scaleParams[i].y;
      inBufDesc[i].bufPlanes[1].frameROI.topLeft.x    = scaleParams[i].x;
      inBufDesc[i].bufPlanes[1].frameROI.topLeft.y    = scaleParams[i].y/2;
    }

  }
  inBufDesc[0].bufPlanes[0].buf                   = lumaPtr;
  inBufDesc[0].bufPlanes[0].width                 = lumaPitch;
  inBufDesc[0].bufPlanes[1].buf                   = ChromaPtr;
  inBufDesc[0].bufPlanes[1].width                 = ChromaPitch;

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

void printProfileData(uint16_t numScales )
{
  int32_t scaleIdx;
#if (!VCOP_HOST_EMULATION)
  for(scaleIdx = 0; scaleIdx < numScales; scaleIdx++)
  {
    printf(" Luma : Chroma : 2x2 Sum = %12d, %12d, %12d\n", PD_FEATURE_TI_LumaSCTM[scaleIdx], PD_FEATURE_TI_chromaSCTM[scaleIdx], PD_FEATURE_TI_slidingSumSCTM[scaleIdx]);
  }
#endif
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

int32_t TestApp_AllocIOBuffers(uint8_t ** lumaImage,uint8_t ** chromaImage, IVISION_OutBufs * outBufs, int32_t width, int32_t height,PD_FEATURE_PLANE_COMPUTATION_CreateParams * params)
{

  *lumaImage   = (uint8_t *)malloc(ALIGN_T0_32(width + 2) * ALIGN_T0_32(height + 128));
  *chromaImage = (uint8_t *)malloc(ALIGN_T0_32(width + 2) * ALIGN_T0_32(height/2 + 128));

  if((*lumaImage == NULL) || (*chromaImage == NULL))
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }

  outBufs->bufDesc[0]->numPlanes                          = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].width                 = params->outPutBufSize;
  outBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = outBufs->bufDesc[0]->bufPlanes[0].width;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 1;
  outBufs->bufDesc[0]->bufPlanes[0].planeType             = 0; //Luma Y


  outBufs->bufDesc[0]->bufPlanes[0].buf = malloc(ALIGN_T0_32(outBufs->bufDesc[0]->bufPlanes[0].width) *
    (2*outBufs->bufDesc[0]->bufPlanes[0].height));
  if((outBufs->bufDesc[0]->bufPlanes[0].buf == NULL))
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  memset(outBufs->bufDesc[0]->bufPlanes[0].buf ,0,ALIGN_T0_32(outBufs->bufDesc[0]->bufPlanes[0].width) *
    (2*outBufs->bufDesc[0]->bufPlanes[0].height));

  printf("Heap required for Ouput buffer : %d\n",params->outPutBufSize);


  return IALG_EOK;
}

int32_t TestApp_ReadInBufs(uint8_t * lumaImage,uint8_t * chromaImage,int32_t currFrameNum, char * fileName, uint16_t imWidth, uint16_t imHeight)
{
#if (!DISABLE_FILE_IO)
  TI_FILE * fp;
  int32_t lumaSize    = imWidth*imHeight;
  int32_t ChromaSize  = (imWidth*imHeight)/2;
  int32_t FrameSize = (lumaSize + ChromaSize);

  fp = FOPEN(fileName, "rb");
  FSEEK(fp, currFrameNum*FrameSize, SEEK_SET);
  FREAD(lumaImage,  1,lumaSize,fp);
  FREAD(chromaImage,1,ChromaSize,fp);
  FCLOSE(fp);

#endif
  return (0);
}

int32_t TestApp_WriteOutBufs(IVISION_OutBufs * outBufs, char * fileName, uint32_t size)
{
#if (!DISABLE_FILE_IO)
#if (!ENABLE_COMPARE)

  TI_FILE * fp;
  static int firtsWrite = 1;
  int32_t retVal;
  if(firtsWrite)
  {
    fp = FOPEN(fileName, "wb+");
    FCLOSE(fp);
    firtsWrite = 0;
  }
  fp = FOPEN(fileName, "ab+");
  retVal = FWRITE(outBufs->bufDesc[0]->bufPlanes[0].buf,1,size,fp);
  if(retVal != size)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  FCLOSE(fp);
#endif
#endif
  return (0);
}

int32_t TestApp_compareOutBufs(IVISION_OutBufs * outBufs, int32_t currFrameNum, char * fileName)
{
#if ENABLE_COMPARE
  TI_FILE * fp;
  int16_t * refData;
  int32_t scaleIdx,planeIdx,LineIdx,PelIdx;
  uint8_t * outPtr  = (uint8_t * )outBufs->bufDesc[0]->bufPlanes[0].buf;
  uint16_t * outLinePtr;
  uint16_t refRows;
  uint16_t refCols;
  uint16_t validRows;
  uint16_t validCols;
  static int refFrameSize = 0;
  int32_t retVal = 0;

  refData      = (int16_t*)malloc(1024*8*sizeof(int16_t));

  PD_FEATURE_PLANE_COMPUTATION_outputMetaData * outMetaData = (PD_FEATURE_PLANE_COMPUTATION_outputMetaData*)outPtr;

  fp = FOPEN(fileName, "rb");
  FSEEK(fp, currFrameNum*refFrameSize, SEEK_SET);
  refFrameSize = 0;
  for(scaleIdx = 0; scaleIdx < outMetaData->numScales; scaleIdx++)
  {
    refRows   = (outMetaData->scaleInfo[scaleIdx].imRows-2)/gConfig_featurePlaneComp->sreachStep;
    refCols   = (outMetaData->scaleInfo[scaleIdx].imCols-2)/gConfig_featurePlaneComp->sreachStep;
    if(gConfig_featurePlaneComp->sreachStep == 2)
    {
      validRows = ((outMetaData->scaleInfo[scaleIdx].imRows- 2 - gConfig_featurePlaneComp->cellSize)/gConfig_featurePlaneComp->sreachStep);
      validCols = ((outMetaData->scaleInfo[scaleIdx].imCols- 2 - gConfig_featurePlaneComp->cellSize)/gConfig_featurePlaneComp->sreachStep);
    }
    else
    {
      validRows = ((outMetaData->scaleInfo[scaleIdx].imRows- 2 - gConfig_featurePlaneComp->cellSize)/gConfig_featurePlaneComp->sreachStep)+1;
      validCols = ((outMetaData->scaleInfo[scaleIdx].imCols- 2 - gConfig_featurePlaneComp->cellSize)/gConfig_featurePlaneComp->sreachStep)+1;
    }
    for(planeIdx = 0; planeIdx < outMetaData->numPlanes; planeIdx++)
    {
      for(LineIdx = 0; LineIdx < validRows; LineIdx++)
      {
        FREAD(refData,2,refCols,fp);
        outLinePtr = (uint16_t *)(outPtr + outMetaData->scaleInfo[scaleIdx].scaleOffset + outMetaData->scaleInfo[scaleIdx].planeOffset*planeIdx + LineIdx*outMetaData->scaleInfo[scaleIdx].featPitch*sizeof(uint16_t));
        if(outMetaData->outFormat == 1)
        {
          for(PelIdx = 0; PelIdx < (validCols/2); PelIdx++)
          {
            if((refData[2*PelIdx] != outLinePtr[PelIdx]) || (refData[2*PelIdx+1] != outLinePtr[PelIdx + outMetaData->scaleInfo[scaleIdx].featPitch/2]))
            {
              printf("Output not matching at Scale Num %d, Plane Num %d , Line %d , Pel %d \n", scaleIdx,planeIdx,LineIdx,PelIdx);
              retVal |= -1;
            }
          }
        }
        else
        {
          for(PelIdx = 0; PelIdx < validCols; PelIdx++)
          {
            if((refData[PelIdx] != outLinePtr[PelIdx]))
            {
              printf("Output not matching at Scale Num %d, Plane Num %d , Line %d , Pel %d \n", scaleIdx,planeIdx,LineIdx,PelIdx);
              retVal |= -1;
            }
          }
        }
      }
      for(;LineIdx < refRows; LineIdx++)
      {
        FREAD(refData,2,refCols,fp);
      }
    }
    refFrameSize += outMetaData->numPlanes*refRows*refCols*sizeof(uint16_t);
  }
  FCLOSE(fp);
  free(refData);

  return (retVal);
#else
  return 0;
#endif
}
void calculateScaleResolutions(scalePrams_t *scaleParams, uint16_t width, uint16_t height, uint8_t numScales, uint8_t scaleSteps, uint16_t * scaleRatiosQ12, uint8_t sreachStep)
{
  uint8_t i;

  scaleParams[0].orgWidth  = width;
  scaleParams[0].orgHeight = height;

  for(i = 1; i < numScales; i++)
  {
    scaleParams[i].orgWidth  = ((scaleParams[((i-1)/scaleSteps)*scaleSteps].orgWidth *(1 << Q_FORMATE_SCALE_RATIO))/ scaleRatiosQ12[i%scaleSteps])&(~1);
    scaleParams[i].orgHeight = ((scaleParams[((i-1)/scaleSteps)*scaleSteps].orgHeight*(1 << Q_FORMATE_SCALE_RATIO))/ scaleRatiosQ12[i%scaleSteps])&(~1);
  }

}

void calculateScaleParams(scalePrams_t *scaleParams, uint8_t numScales, uint8_t scaleSteps,  uint16_t * scaleRatiosQ12, uint16_t RoiCenterX,  uint16_t RoiCenterY, uint16_t RoiWidth, uint16_t RoiHeight, uint8_t sreachStep)
{
  uint8_t i;

  for( i = 0; i < numScales; i++)
  {
      int32_t xNum  = ((RoiCenterX >> (i/scaleSteps)) * (1 << Q_FORMATE_SCALE_RATIO));
      int32_t yNum  = ((RoiCenterY >> (i/scaleSteps)) * (1 << Q_FORMATE_SCALE_RATIO));
      int32_t xDen  = (scaleRatiosQ12[i%scaleSteps]);
      uint32_t imWidth  = scaleParams[i].orgWidth ;
      uint32_t imHidth  = scaleParams[i].orgHeight;
      if(i%scaleSteps)
      {
        xNum = (xNum/xDen);
        yNum = (yNum/xDen);
      }
      else
      {
        xNum = (xNum/(1 << Q_FORMATE_SCALE_RATIO));
        yNum = (yNum/(1 << Q_FORMATE_SCALE_RATIO));
      }

      if(RoiWidth >= imWidth)
      {
        scaleParams[i].x = 0;
        scaleParams[i].width = imWidth;
      }
      else
      {
        scaleParams[i].width = RoiWidth;
        scaleParams[i].x = (xNum-scaleParams[i].width/2) < 0 ? 0 : (xNum-scaleParams[i].width/2);
        scaleParams[i].x = (scaleParams[i].x + RoiWidth) > imWidth ? imWidth - scaleParams[i].width : scaleParams[i].x;
      }

      if(RoiHeight >= imHidth)
      {
        scaleParams[i].y = 0;
        scaleParams[i].height = imHidth;
      }
      else
      {
        scaleParams[i].height = RoiHeight;
        scaleParams[i].y =(yNum-scaleParams[i].height/2) < 0 ? 0 :(yNum-scaleParams[i].height/2) ;
        scaleParams[i].y = (scaleParams[i].y + RoiHeight) > imHidth ? imHidth - scaleParams[i].height : scaleParams[i].y;
      }

      scaleParams[i].x      = (scaleParams[i].x / sreachStep)*sreachStep;
      scaleParams[i].y      = (scaleParams[i].y / sreachStep)*sreachStep;
      scaleParams[i].width  = (scaleParams[i].width / sreachStep)*sreachStep;
      scaleParams[i].height = (scaleParams[i].height / sreachStep)*sreachStep;
  }

  printf("Calculctaed scale Params: \n");
  for(i = 0; i < numScales; i++)
  {
    printf("%d %d %d %d %d ",i,scaleParams[i].x,scaleParams[i].y,scaleParams[i].width,scaleParams[i].height);
  }

}


int32_t TestApp_AllocScalesBuffers(scalePrams_t *scaleParams, uint16_t inBufWidth,uint16_t inBufHeight, uint8_t numScales, uint8_t scaleSteps)
{
  uint8_t i;
  uint16_t width, height;
  uint32_t totalScalesMemSize = 0;
  uint32_t totalNumPixels     = scaleParams[0].width*scaleParams[0].height;

  for(i = 1; i < numScales; i++)
  {
    if(i%scaleSteps)
    {
      width  = scaleParams[i].width;
      height = scaleParams[i].height;
    }
    else
    {
      width  = inBufWidth  >> (i/scaleSteps);
      height = inBufHeight >> (i/scaleSteps);
    }
    width  = ALIGN_SIZE(width,384);
    height = ALIGN_SIZE(height,64);

    lumaImageScales[i]   = (uint8_t*) malloc(width*(height+128));
    chromaImageScales[i] = (uint8_t*) malloc(width*(height+128)/2);
    ImageScalesPitchs[i] = width;

    totalScalesMemSize += (width*height) + (width*height/2);
    totalNumPixels     += scaleParams[i].width*scaleParams[i].height;
    if((lumaImageScales[i] == NULL) || (chromaImageScales[i] == NULL))
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }
  }
  printf("Total heap required for Pyramid scales : %d\n",totalScalesMemSize);
  printf("Total number of input pixel  Processed : %d\n",totalNumPixels);
  return (0);
}

int32_t TestApp_freeScalesBuffers(uint8_t numScales)
{
  uint8_t i;
  for(i = 1; i < numScales; i++)
  {
    free(lumaImageScales[i]  );
    free(chromaImageScales[i]);
  }
  return (0);
}

int32_t deleteAlgHandle(IM_Fxns * handle)
{
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  numMemRec = handle->ivision->ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));
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
  free(memRec);
  return status;
}

int32_t createFilter2d(IM_Fxns ** handle, uint8_t enableFilter, uint8_t enableContrastStretching)
{
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  FILTER_2D_CreateParams   createParams;

  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;


  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);


  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/

  createParams.filterCoefWidth          = FILTER_COEF_WIDTH;
  createParams.filterCoefHeight         = FILTER_COEF_HEIGHT;
  createParams.separableFilter          = 1;

  createParams.enableFilter             = enableFilter; //gConfig_featurePlaneComp[0].enableFilter;
  createParams.enableContrastStretching = enableContrastStretching; //gConfig_featurePlaneComp[0].enableContrastStretching;
  createParams.minPercentileThreshold   = 1;
  createParams.maxPercentileThreshold   = 99;
  createParams.minVal                   = 0;
  createParams.maxVal                   = 255;
  createParams.filterCoef               = filterCoeff;
  createParams.imageFormat              = FILTER_2D_TI_IMAGE_FORMAT_YUV420;
  /*-----------------------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = FILTER_2D_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = FILTER_2D_TI_VISION_FXNS.ialg.algAlloc(
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
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = FILTER_2D_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  *handle = (IM_Fxns *) memRec[0].base;

EXIT_LOOP:
  return status;
}

int32_t processFilter2d(IM_Fxns * handle, uint8_t * lumaIn, uint8_t * chromaIn, uint8_t * lumaOut, uint8_t * chromaOut, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outPitch,uint8_t externalParam)
{
  int32_t status;

  FILTER_2D_InArgs inArgs;
  IVISION_InBufs    inBufs;

  static uint8_t minVal = 0;
  static uint8_t maxVal = 255;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[FILTER_2D_TI_BUFDESC_IN_TOTAL];

  FILTER_2D_OutArgs   outArgs;
  IVISION_OutBufs     outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[FILTER_2D_TI_BUFDESC_OUT_TOTAL];

  uint8_t idx;

  outArgs.iVisionOutArgs.size = sizeof(FILTER_2D_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(FILTER_2D_InArgs);

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = FILTER_2D_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs  = FILTER_2D_TI_BUFDESC_OUT_TOTAL;

  inBufDescList[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]                = &inBufDesc;
  outBufDescList[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]    = &outBufDesc;


  idx = FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER;
  inBufs.bufDesc[idx]->numPlanes                          = 2;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].width                 = inPitch;
  inBufs.bufDesc[idx]->bufPlanes[0].height                = inHeight;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = inWidth;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = inHeight;
  inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0; //Luma Y

  inBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.x    = 0;
  inBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.y    = 0;
  inBufs.bufDesc[idx]->bufPlanes[1].width                 = inPitch;
  inBufs.bufDesc[idx]->bufPlanes[1].height                = inHeight/2;
  inBufs.bufDesc[idx]->bufPlanes[1].frameROI.width        = inWidth;
  inBufs.bufDesc[idx]->bufPlanes[1].frameROI.height       = inHeight/2;
  inBufs.bufDesc[idx]->bufPlanes[1].planeType             = 1; //C

  inBufs.bufDesc[idx]->bufPlanes[0].buf = lumaIn;
  inBufs.bufDesc[idx]->bufPlanes[1].buf = chromaIn;


  idx = FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER;
  outBufs.bufDesc[idx]->numPlanes                          = 2;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].width                 = outPitch;
  outBufs.bufDesc[idx]->bufPlanes[0].height                = inHeight;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = inWidth;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = inHeight;
  outBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0; //Luma Y

  outBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.x    = 0;
  outBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.y    = 0;
  outBufs.bufDesc[idx]->bufPlanes[1].width                 = outPitch;
  outBufs.bufDesc[idx]->bufPlanes[1].height                = inHeight/2;
  outBufs.bufDesc[idx]->bufPlanes[1].frameROI.width        = inWidth;
  outBufs.bufDesc[idx]->bufPlanes[1].frameROI.height       = inHeight/2;
  outBufs.bufDesc[idx]->bufPlanes[1].planeType             = 1; //Chroma UV

  outBufs.bufDesc[idx]->bufPlanes[0].buf = lumaOut;
  outBufs.bufDesc[idx]->bufPlanes[1].buf = chromaOut;


  inArgs.iVisionInArgs.subFrameInfo          = 0;
  inArgs.iVisionInArgs.size                  = sizeof(FILTER_2D_InArgs);
  inArgs.minVal                              = minVal;
  inArgs.maxVal                              = maxVal;
  inBufDesc.numPlanes                        = 2;
  outBufDesc.numPlanes                       = 2;

  if(externalParam)
  {
    TI_FILE * fp = FOPEN("contrast_stretch_params.txt", "r");
    if( fp != NULL)
    {
      FSCANF(fp,"%d %d",&minVal,&maxVal);
      FCLOSE(fp);
    }
  }

  handle->ivision->ialg.algActivate((IALG_Handle)handle);

  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

  handle->ivision->ialg.algDeactivate((IALG_Handle)handle);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
  minVal = outArgs.minVal;
  maxVal = outArgs.maxVal;

  if(externalParam)
  {
    TI_FILE * fp = FOPEN("contrast_stretch_params.txt", "w+");
    if( fp != NULL)
    {
      FPRINTF(fp,"%d %d",minVal,maxVal);
      FCLOSE(fp);
    }
  }
EXIT_LOOP :
  return status;
}

int processYUVScalar(IM_Fxns * handle, uint8_t * lumaIn, uint8_t * chromaIn, uint8_t * lumaOut, uint8_t * chromaOut, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch,uint16_t outStartX, uint16_t outStartY)
{
  int32_t status;

  YUV_SCALAR_TI_InArgs             inArgs;
  YUV_SCALAR_TI_outArgs            outArgs;
  IVISION_OutBufs                  outBufs;
  IVISION_InBufs                   inBufs;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *inBufDescList[1];

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[1];

  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = 1;
  outBufs.numBufs  = 1;

  inBufDescList[0]     = &inBufDesc;
  outBufDescList[0]    = &outBufDesc;


  inArgs.iVisionInArgs.size         = sizeof(YUV_SCALAR_TI_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;

  inBufDesc.numPlanes                          = 2;
  inBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;

  inBufDesc.bufPlanes[0].width                 = inPitch;
  inBufDesc.bufPlanes[0].height                = inHeight;
  inBufDesc.bufPlanes[0].frameROI.width        = inWidth;
  inBufDesc.bufPlanes[0].frameROI.height       = inHeight;

  inBufDesc.bufPlanes[0].buf = (uint8_t * )lumaIn ;

  inBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
  inBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;

  inBufDesc.bufPlanes[1].width                 = inPitch ;
  inBufDesc.bufPlanes[1].height                = inHeight/2;
  inBufDesc.bufPlanes[1].frameROI.width        = inWidth;
  inBufDesc.bufPlanes[1].frameROI.height       = inHeight/2;

  inBufDesc.bufPlanes[1].buf = (uint8_t * )chromaIn ;


  outBufDesc.numPlanes                          = 2;
  outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;

  outBufDesc.bufPlanes[0].width                 = outPitch ;
  outBufDesc.bufPlanes[0].height                = outHeight;
  outBufDesc.bufPlanes[0].frameROI.width        = outWidth ;
  outBufDesc.bufPlanes[0].frameROI.height       = outHeight;

  outBufDesc.bufPlanes[0].buf = (uint8_t * )lumaOut ;

  outBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
  outBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;

  outBufDesc.bufPlanes[1].width                 = outPitch ;
  outBufDesc.bufPlanes[1].height                = outHeight/2;
  outBufDesc.bufPlanes[1].frameROI.width        = outWidth ;
  outBufDesc.bufPlanes[1].frameROI.height       = outHeight/2;

  outBufDesc.bufPlanes[1].buf = (uint8_t * )chromaOut ;

  outArgs.iVisionOutArgs.size = sizeof(YUV_SCALAR_TI_outArgs);

  handle->ivision->ialg.algActivate((IALG_Handle)handle);

  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

  handle->ivision->ialg.algDeactivate((IALG_Handle)handle);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }
  return status;
}

int createYUVScalar(IM_Fxns ** handle, uint16_t maxOutWidth,  uint16_t maxOutHeight, uint16_t scaleRatioQ12, uint16_t outStartX, uint16_t outStartY)
{
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  YUV_SCALAR_TI_CreateParams  createParams;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(YUV_SCALAR_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.maxWidth                      = maxOutWidth    ;
  createParams.maxHeight                     = maxOutHeight   ;
  createParams.scaleRatioQ12                 = scaleRatioQ12 ;
  createParams.scalingMethod                 = 0 ;
  createParams.fracQFmt                      = 4;
  createParams.outStartX                     = outStartX;
  createParams.outStartY                     = outStartY;

  numMemRec = YUV_SCALAR_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = YUV_SCALAR_TI_VISION_FXNS.ialg.algAlloc(
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
  status = YUV_SCALAR_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  *handle = (IM_Fxns *) memRec[0].base;
  //profiler_end_print(0);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }
EXIT_LOOP:
  return(status);
}

void generateScales(IM_Fxns ** handles, uint8_t * lumaImage, uint8_t * chromaImage, uint16_t Width, uint16_t Height, uint16_t Pitch, scalePrams_t *scaleParams, uint8_t numScales, uint8_t scaleSteps, uint16_t srQShift, uint16_t fpQShift)
{
  uint16_t outWidth;
  uint16_t outHeight;
  uint16_t scaleRatioQ12;
  uint16_t i;

  uint16_t inWidth;
  uint16_t inHeight;
  uint16_t inPitch;

  uint8_t * lumaPtr;
  uint8_t * chromaPtr;

  IM_Fxns * handle;
  uint16_t outStartX, outStartY;
  uint16_t inStartX,  inStartY;

  for(i = 1; i < numScales; i++)
  {

    if(i <= scaleSteps)
    {
      inPitch   = Pitch;
      lumaPtr   = lumaImage;
      chromaPtr = chromaImage;
    }
    else
    {
      inPitch   = ImageScalesPitchs[((i-1)/scaleSteps)*scaleSteps];
      lumaPtr   = lumaImageScales[((i-1)/scaleSteps)*scaleSteps];
      chromaPtr = chromaImageScales[((i-1)/scaleSteps)*scaleSteps];
    }
    handle         = handles[i];
    scaleRatioQ12  = scaleRatiosQ12[i%scaleSteps];

    inWidth   = Width  >> ((i-1)/scaleSteps);
    inHeight  = Height >> ((i-1)/scaleSteps);

    if(i%scaleSteps == 0)
    {
      outWidth  =  Width  >> (i/scaleSteps);
      outHeight =  Height >> (i/scaleSteps);
      outStartX =  0;
      outStartY =  0;
    }
    else
    {
      outWidth   =  scaleParams[i].width;
      outHeight  =  scaleParams[i].height;
      outStartX  =  scaleParams[i].x;
      outStartY  =  scaleParams[i].y;
      inStartX   = ((outStartX * scaleRatioQ12) / (1 << (srQShift))) ;
      inStartY   = ((outStartY * scaleRatioQ12) / (1 << (srQShift))) ;
      lumaPtr   += inStartY*inPitch     + inStartX;
      inStartX   = (((outStartX/2) * scaleRatioQ12) / (1 << (srQShift))) ;
      inStartY   = (((outStartY/2) * scaleRatioQ12) / (1 << (srQShift))) ;
      chromaPtr += inStartY*inPitch + inStartX*2;

    }
#if (VCOP_HOST_EMULATION)
    TEST_PRINTF("Generating scales %d \n",i);
#endif

#if 1
    processYUVScalar(handle, lumaPtr, chromaPtr, lumaImageScales[i], chromaImageScales[i], inWidth, inHeight, inPitch, outWidth, outHeight, ImageScalesPitchs[i],outStartX,outStartY);
#else
    vcop_resize_cn_y_s(lumaPtr, lumaImageScales[i], inWidth, inHeight, inPitch, outWidth, outHeight, ImageScalesPitchs[i], scaleRatioQ12, srQShift, fpQShift);
    vcop_resize_cn_uv_s(chromaPtr, chromaImageScales[i], inWidth, inHeight, inPitch, outWidth, outHeight, ImageScalesPitchs[i], scaleRatioQ12, srQShift, fpQShift);
#endif

  }
}

int createTiOdFeatureCompute(IM_Fxns ** handle, PD_FEATURE_PLANE_COMPUTATION_CreateParams   *createParams, sFeaturePlaneComp_Config * testcaseParams)
{
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;
  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  createParams->imgFrameWidth          = testcaseParams[0].srcImageWidth  ;
  createParams->imgFrameHeight         = testcaseParams[0].srcImageHeight ;
  createParams->cellSize               = testcaseParams[0].cellSize          ;
  createParams->blockSize              = testcaseParams[0].blockSize         ;
  createParams->blockOverlap           = testcaseParams[0].blockOverlap      ;
  createParams->sreachStep             = testcaseParams[0].sreachStep        ;
  createParams->numBins                = testcaseParams[0].numBins           ;
  createParams->gradientMethod         = testcaseParams[0].gradientMethod    ;
  createParams->enableCellSum          = testcaseParams[0].enableCellSum     ;
  createParams->outFormat              = testcaseParams[0].outFormat         ;
  createParams->additionalPlaneFLag    = (testcaseParams[0].enableGardMagPlane ) |
    (testcaseParams[0].enableYPlane   << 1) |
    (testcaseParams[0].enableUVPlane  << 2);

  createParams->leftPadPels            = 0;
  createParams->topPadPels             = 0;

  /*-----------------------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = PD_FEATURE_PLANE_COMPUTATION_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = PD_FEATURE_PLANE_COMPUTATION_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(createParams), NULL, memRec);

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
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = PD_FEATURE_PLANE_COMPUTATION_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(handle),
    memRec,NULL,(IALG_Params *)(createParams));


  *handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }

  status = (*handle)->ivision->algControl((IVISION_Handle)(*handle),TI_PD_CONTROL_GET_OUTPUT_BUF_SIZE,
    (IALG_Params *)(createParams),(IALG_Params *)(createParams));
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
EXIT_LOOP:
  return status;
}

int32_t featurePlaneCompTest(sFeaturePlaneComp_Config * testcaseParams)
{
  int32_t i,status;
  uint32_t frameIdx;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     tiPdHandle;
  IM_Fxns *     filter2dHandle;
  IM_Fxns *     yuvScalarHandle[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];

  PD_FEATURE_PLANE_COMPUTATION_CreateParams   createParams;

  PD_FEATURE_PLANE_COMPUTATION_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *inBufDescList[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES];

  PD_FEATURE_PLANE_COMPUTATION_OutArgs   outArgs;
  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_TOTAL];
  uint8_t * lumaImage;
  uint8_t * chromaImage;
  uint8_t * orgLumaImage;
  uint8_t * orgChromaImage;

  outArgs.iVisionOutArgs.size = sizeof(PD_FEATURE_PLANE_COMPUTATION_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(PD_FEATURE_PLANE_COMPUTATION_InArgs);

  uint16_t inBufWidth ;
  uint16_t inBufHeight;

  profiler_init();
  profiler_initStack(profiler_getSP());

  for ( i = 0 ; i < FEATURE_PLANE_COMP_MAX_TOTAL_SCALES; i++ )
  {
    inBufDescList[i]                = &(inBufDesc[i]);
  }
  outBufDescList[PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_FEATURE_PLANES_BUFFER]    = &outBufDesc;

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = PD_FEATURE_PLANE_COMPUTATION_BUFDESC_IN_TOTAL;
  outBufs.numBufs  = PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_TOTAL;


  inBufWidth  = testcaseParams[0].srcImageWidth  ;
  inBufHeight = testcaseParams[0].srcImageHeight ;


  for ( i = 1 ; i < testcaseParams[0].scaleSteps; i++ )
  {
    scaleRatiosQ12[i]                = testcaseParams[0].scaleRatioQ12[i-1];
  }
  scaleRatiosQ12[0]                = testcaseParams[0].scaleRatioQ12[testcaseParams[0].scaleSteps-1];

  inArgs.numScales = testcaseParams[0].numScales;


  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.iVisionInArgs.size                  = sizeof(PD_FEATURE_PLANE_COMPUTATION_InArgs);

  outBufDesc.numPlanes                         = 1;


  createParams.maxNumScales           = testcaseParams[0].numScales         ;

  for(i = 0; i < createParams.maxNumScales; i++)
  {
    createParams.scaleParams[i].x      = testcaseParams[0].scaleParams[i*5 + 1];
    createParams.scaleParams[i].y      = testcaseParams[0].scaleParams[i*5 + 2];
    createParams.scaleParams[i].width  = testcaseParams[0].scaleParams[i*5 + 3];
    createParams.scaleParams[i].height = testcaseParams[0].scaleParams[i*5 + 4];
  }

  calculateScaleResolutions(createParams.scaleParams,inBufWidth, inBufHeight, createParams.maxNumScales, testcaseParams[0].scaleSteps,scaleRatiosQ12,testcaseParams[0].sreachStep);


  if(testcaseParams[0].RoiSelectionMethod == 0)
  {
    calculateScaleParams(createParams.scaleParams, createParams.maxNumScales, testcaseParams[0].scaleSteps,scaleRatiosQ12, testcaseParams[0].RoiCenterX,testcaseParams[0].RoiCenterY,testcaseParams[0].RoiWidth,testcaseParams[0].RoiHeight,testcaseParams[0].sreachStep);
  }

  TEST_PRINTF("Creating  tiPdHandles \n");
  profiler_start();
  createTiOdFeatureCompute(&tiPdHandle, &createParams,testcaseParams);

  TestApp_AllocIOBuffers(&lumaImage,&chromaImage,&outBufs, inBufWidth,inBufHeight,&createParams);

  TestApp_AllocScalesBuffers(createParams.scaleParams,inBufWidth,inBufHeight,testcaseParams[0].numScales, testcaseParams[0].scaleSteps);

  TestApp_FillInBuffDesc(createParams.scaleParams, lumaImage, inBufWidth,chromaImage, inBufWidth, testcaseParams[0].numScales, testcaseParams[0].scaleSteps);

  createFilter2d(&filter2dHandle,gConfig_featurePlaneComp[0].enableFilter,gConfig_featurePlaneComp[0].enableContrastStretching);

  for(i = 1; i < testcaseParams[0].numScales; i++)
  {
    createYUVScalar(&yuvScalarHandle[i], (inBufWidth+192), (inBufHeight + 64), scaleRatiosQ12[i % testcaseParams[0].scaleSteps],createParams.scaleParams[i].x,createParams.scaleParams[i].y);
  }
  profiler_end_print(0);

  if(gConfig_featurePlaneComp[0].enableFilter  || gConfig_featurePlaneComp[0].enableContrastStretching)
  {
    orgLumaImage   = (uint8_t*)malloc(inBufWidth * inBufHeight);
    orgChromaImage = (uint8_t*)malloc(inBufWidth * inBufHeight/2);
  }
  else
  {
    orgLumaImage   = lumaImage;
    orgChromaImage = chromaImage;
  }

  for(frameIdx = testcaseParams[0].startFrame; frameIdx < (testcaseParams[0].startFrame + testcaseParams[0].numFrames);frameIdx++)
  {
    TestApp_ReadInBufs(orgLumaImage , orgChromaImage , frameIdx,(char *)testcaseParams[0].inImage,inBufWidth,inBufHeight);

    TEST_PRINTF("Processing started for frame %d \n",frameIdx);

    profiler_start();
    if(gConfig_featurePlaneComp[0].enableFilter  || gConfig_featurePlaneComp[0].enableContrastStretching)
    {
      processFilter2d(filter2dHandle,orgLumaImage,orgChromaImage, lumaImage,chromaImage,inBufWidth,inBufHeight,inBufWidth,inBufWidth,testcaseParams[0].extFilterParam);
    }

    generateScales(yuvScalarHandle, lumaImage,   chromaImage, inBufWidth,   inBufHeight,   inBufWidth, createParams.scaleParams, testcaseParams[0].numScales, testcaseParams[0].scaleSteps, Q_FORMATE_SCALE_RATIO, FEATURE_PLANE_COMP_Q_SHIFT);

    TEST_PRINTF("Processing started for HOG \n");


    tiPdHandle->ivision->ialg.algActivate((IALG_Handle)tiPdHandle);
    status = tiPdHandle->ivision->algProcess((IVISION_Handle)tiPdHandle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
    tiPdHandle->ivision->ialg.algDeactivate((IALG_Handle)tiPdHandle);

    profiler_end_print(1);
    printProfileData(testcaseParams[0].numScales);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
    TEST_PRINTF("Processing Completed for frame %d \n",frameIdx);

    TestApp_WriteOutBufs(&outBufs,(char *)testcaseParams[0].outImage,createParams.outPutBufSize);

    status = TestApp_compareOutBufs(&outBufs,frameIdx, (char *)testcaseParams[0].refImage);

    if(status != 0)
    {
      profiler_printStatus(status);
      goto EXIT_LOOP;
    }

    TEST_PRINTF("Test Completed for frame %d \n",frameIdx);
  }
  profiler_printStatus(0);

  fflush(stdout);

EXIT_LOOP:
  deleteAlgHandle(tiPdHandle);

  for(i = 1; i < testcaseParams[0].numScales; i++)
  {

   deleteAlgHandle(yuvScalarHandle[i]);
  }

  deleteAlgHandle(filter2dHandle);
  TestApp_freeScalesBuffers(testcaseParams[0].numScales);

  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
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
  report_printAppletInfo((int8_t *)"PD_FEATURE_PLANE_COMPUTATION");

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
    printf("Could not open config list file : %s , Runing in default mode \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  while(1)
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
      break;
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
      printf("Processing config file %s !\n", configFile);
      status = readparamfile(configFile, &gsTokenMap_featurePlaneComp[0]);
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      if (argc > 2)
      {
        gConfig_featurePlaneComp[0].startFrame = atoi(argv[2]);
      }

      profiler_testCaseInfo((int8_t *)gConfig_featurePlaneComp->testCaseName,(int8_t *)gConfig_featurePlaneComp->testCaseDesc,gConfig_featurePlaneComp->performanceTestcase);
      printparams(&gsTokenMap_featurePlaneComp[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)gConfig_featurePlaneComp,sizeof(sFeaturePlaneComp_Config)) ;

      /* Validate the applet */
      status = featurePlaneCompTest(gConfig_featurePlaneComp);
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



