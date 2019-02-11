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


/** @file pyramid_lk_sof_tb.c
*
*  @brief  This file contains test code for pyramid lk based sof demo code
*
*
*  @date   Dec 2013
*
*  Description
*    This file contains test code to validate the frame level pyramid lk sof demo.
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>

#include "xdais_types.h"

#include "evestarterware.h"
#include "alg_osal.h"
#include "pyramid_lk_sof_config.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "configparser.h"
#include "pyramid_lk_sof_tb.h"
#include "ti_draw_utils.h"
#include "ti_file_io.h"


#include "isof_ti.h"

#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)

#define absDiff(x,y) ( x > y ? x-y : y-x )

#if (VCOP_HOST_EMULATION)
#define ENABLE_FLOW_VISUVALIZATION (1)
#define ENABLE_SCORE_CALCULATION (1)
#define ENABLE_FILE_READ (1)
#else
#define ENABLE_FLOW_VISUVALIZATION (1)
#define ENABLE_SCORE_CALCULATION (0)
#define ENABLE_FILE_READ (1)
#endif

#define ENABLE_REFERENCE_MATCHING 1
#define ENABLE_TRACK_DUMP         0
#define ENABLE_TEXT_TRACK_DUMP 0

#define ENABLE_PROCESS_LEVEL_TRACE (0)


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)

#define DMEM_SIZE (24*1024 + 512)

#define RGB88_GREEN ((0 << 16) | (255 << 8) | (0))
#define RGB88_YELLOW ((255 << 16) | (255 << 8) | (0))

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
  int i;
  params->maxNumKeyPoints = 0;
  params->numLevels    = 4;
  params->numLevelsPerCall = PYRAMID_LK_TRACKER_TI_MAXLEVELS_PER_CALL;
  params->imWidth      = 640;
  params->imHeight     = 320;
  params->keyPointDetectMethod = SOF_HARRIS_KEY_POINTS; //SOF_EXTERNAL_KEY_POINTS = 0,  SOF_HARRIS_KEY_POINTS   = 1,  SOF_FAST9_KEY_POINTS   = 2
  params->fast9Threshold    = 100;
  params->trackErrThr        = 1000;
  params->trackMinFlowQ4     = (2 << 4);
  params->trackNmsWinSize    = 1;
  params->inPutType         = 1;

  strcpy(params->outVideoSeqFile,"NA");
  for(i = 0; i < PYRAMID_LK_TRACKER_TI_MAXLEVELS; i++)
  {
    params->searchRange[i] = PYRAMID_LK_TRACKER_TI_MAX_SEARCH_RANGE;
    params->minErrValue[i] = 0;
    params->maxItersLK[i]  = PYRAMID_LK_TRACKER_TI_MAXITERATION;
  }
  strcpy((char*)params->testCaseName, " ");
  strcpy((char*)params->testCaseDesc, " ");
}

void SOF_CreateFixedMotion(unsigned char *prevBuf, unsigned char *curBuf, unsigned short srcBufferPitch, unsigned short srcImageWidth,unsigned short srcImageHeight,  short u,  short v )
{
#ifdef CREATE_FIXED_MOTION
  int i, j, newPosX, newPosY ;

  for(j=0; j<srcImageHeight; j++)
  {
    for(i=0; i<srcImageWidth; i++)
    {
      newPosX  = i+u ;
      newPosY  = j+v ;

      newPosX = CLIP(newPosX, 0, srcImageWidth-1)  ;
      newPosY = CLIP(newPosY, 0, srcImageHeight-1) ;

      *(curBuf + (newPosY)*srcBufferPitch + newPosX) = *(prevBuf + j*srcBufferPitch + i) ;
    }

  }
#endif
}

int SOFDemo_ComputeStats(char *fileRef, char *fileCur, char *fileStats)
{
#if ENABLE_SCORE_CALCULATION
  FILE *fpCur, *fpStats;
  int ret ;
  int totalPts = 0;
  int points3 = 0 ;
  int points2 = 0 ;
  int points1 = 0 ;
  float accuracy3;
  float accuracy2;
  float accuracy1;
  int lineNum = 0;
  sSOFFlow (*flowGT) [MAX_WIDTH];

  static int summayFile = 0;
  FILE *summaryFile;
  char * sumFileName = "accuracySummary.csv";

  int x, y ;
  float u, v ;
  unsigned int error= 0;
  int totalPoints = 0 ;

#ifndef CREATE_FIXED_MOTION
  FILE *fpRef;
  fpRef = fopen(fileRef, "r");
  if(fpRef == NULL)
  {
    TEST_PRINTF("Not able to open Ref flow vector file - %s\n",fileRef );
    return -1 ;
  }
#endif
  if(summayFile)
  {
    summaryFile = fopen(sumFileName, "w+");
    if(summaryFile == NULL)
    {
      TEST_PRINTF("Not able to open Summary  file \n");
      return -1 ;
    }
    fclose(summaryFile);
    summayFile = 0;
  }

  fpCur = fopen(fileCur, "r");
  if(fpCur == NULL)
  {
    TEST_PRINTF("Not able to open Cur flow vector file - %s\n",fileCur );
    return -1 ;
  }

  fpStats = fopen(fileStats, "w");
  if(fpStats == NULL)
  {
    TEST_PRINTF("Not able to open Out stats file - %s\n",fileStats );
    return -1 ;
  }

  /*---------------------------------------------------------------*/
  /* Main aim of this memory zeroing is to Set the valid flag = 0  */
  /*---------------------------------------------------------------*/
  flowGT   = (sSOFFlow (*)[MAX_WIDTH])malloc(MAX_HEIGHT*MAX_WIDTH* sizeof(sSOFFlow));
  memset(flowGT, 0, sizeof(sSOFFlow)*MAX_HEIGHT*MAX_WIDTH);
  if(flowGT == NULL)
  {
    TEST_PRINTF("Not able to Allocate memory for flowGT - %s\n" );
    return -1 ;
  }
#ifndef CREATE_FIXED_MOTION
  while (!feof(fpRef))
  {
    ret = fscanf(fpRef,"%d,%d,%f,%f\n",&x,&y,&u,&v);
    if (ret != -1)
    {
      if(x <0 || x> (MAX_WIDTH-1) || y <0 || y> (MAX_HEIGHT-1))
      {
        TEST_PRINTF("Ref flow vector file - %s is not Valid\n",fileRef );
        break;
      }
      flowGT[y][x].u = u ;
      flowGT[y][x].v = v ;
      flowGT[y][x].valid = 1 ;
    }
  }
#endif

  fprintf(fpStats, "XPos,YPos,u[calculated],v[calculated],u[GT],v[GT], Disatnce\n");
  while (!feof(fpCur))
  {
    ret = fscanf(fpCur,"%d,%d,%f,%f,%d",&x,&y,&u,&v,&error);
    if (ret != -1)
    {
      lineNum++;
      if(x <0 || x> (MAX_WIDTH-1) || y <0 || y> (MAX_HEIGHT-1))
      {
        TEST_PRINTF("Invalid flow vector %4d, %4d @ %4d\n",x, y,lineNum );
        continue;
      }
#ifdef CREATE_FIXED_MOTION
      flowGT[y][x].valid = 1 ;
      flowGT[y][x].u = MOTION_u ;
      flowGT[y][x].v = MOTION_v ;
#endif
      if(flowGT[y][x].valid == 1 )
      {
        double distance;
        distance =
          sqrt((flowGT[y][x].u - u)*(flowGT[y][x].u - u) + (flowGT[y][x].v - v)*(flowGT[y][x].v - v));
        fprintf(fpStats, "%d,%d,%f,%f,%f,%f,%f\n",x,y,u,v,flowGT[y][x].u, flowGT[y][x].v,distance);
        if(distance <= 3)
        {
          points3++;
        }
        if(distance <= 2)
        {
          points2++;
        }
        if(distance <= 1)
        {
          points1++;
        }
        totalPts++;
      }
    }
  }
  if(totalPts !=0)
  {
    accuracy3 = ((float)points3/totalPts)*100;
    accuracy2 = ((float)points2/totalPts)*100;
    accuracy1 = ((float)points1/totalPts)*100;
  }
  else
  {
    accuracy3 = 0;
    accuracy2 = 0;
    accuracy1 = 0;
  }
  summaryFile = fopen(sumFileName, "a+");
  if(summaryFile == NULL)
  {
    TEST_PRINTF("Not able to open Summary  file \n");
    return -1 ;
  }
  fprintf(summaryFile,"%s,%f,%f,%f,%d\n",fileCur,accuracy3,accuracy2,accuracy1,totalPts);
  TEST_PRINTF("%s,%f,%f,%f,%d\n",fileCur,accuracy3,accuracy2,accuracy1,totalPts);
  fclose(summaryFile);

  fclose(fpRef);
  fclose(fpCur);
  fclose(fpStats);
  free(flowGT );
#endif
  return 0 ;
}

int readintputImage(config_params * params, uint8_t * imgPtr1, uint32_t frameIdx )
{
#if ENABLE_FILE_READ
  TI_FILE *fp1;
  int32_t readSize1;
  uint32_t sizeInput;
  sizeInput   = params->imWidth*params->imHeight;

  if(params->inPutType == 1)
  {
    if(frameIdx == 0)
    {
      fp1 = FOPEN(params->prevFrameFile, "rb");
    }
    else
    {
      fp1 = FOPEN(params->currFrameFile, "rb");
    }
    if(fp1== NULL)
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }
    readSize1 = FREAD(imgPtr1,1,sizeInput,fp1);
    if(readSize1 != sizeInput)
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }

    FCLOSE(fp1);
  }
  else
  {
    fp1 = FOPEN(params->inVideoSeqFile, "rb");
    if(fp1== NULL)
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }
    FSEEK(fp1, (frameIdx*sizeInput*3)/2, SEEK_SET);
    readSize1 = FREAD(imgPtr1,1,sizeInput,fp1);
    if(readSize1 != sizeInput)
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }

    FCLOSE(fp1);
  }
#endif
  return (0);
}


static int compareOutputYUV(char * outfileName, char * reffileName, uint32_t frameIdx, uint32_t frameSize)
{
  TI_FILE * out_fp;
  TI_FILE * ref_fp;
  uint8_t * outPtr;
  uint8_t * refPtr;
  uint32_t readSize1;
  uint32_t readSize2;
  int32_t fail;

  out_fp = FOPEN((char *)outfileName,"rb");
  ref_fp = FOPEN((char *)reffileName,"rb");
  if((out_fp==NULL)||(ref_fp==NULL))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  FSEEK(out_fp, (frameIdx*frameSize), SEEK_SET);
  FSEEK(ref_fp, (frameIdx*frameSize), SEEK_SET);
  outPtr = (uint8_t *)malloc(frameSize);
  refPtr = (uint8_t *)malloc(frameSize);
  if((outPtr==NULL)||(refPtr==NULL))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  readSize1 = FREAD(outPtr,1,frameSize,out_fp);
  readSize2 = FREAD(refPtr,1,frameSize,ref_fp);
  if((readSize1 != frameSize) || (readSize2 != frameSize))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  fail = memcmp(outPtr,refPtr,frameSize);
  FCLOSE(out_fp);
  FCLOSE(ref_fp);
  return(fail);

}

static int writeOutputToTxtFile(strackInfo * trackInfo, uint16_t maxNumKeyPoints, uint16_t startX,uint16_t startY, char * fileName)
{
  int i;
  float vX, vY;
  uint16_t x1,y1,x2,y2;
  FILE * fp;
  uint16_t errMeasure = 0;
  fp = fopen(fileName, "w+");

  if(fp== NULL)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  for(i = 0; i < maxNumKeyPoints; i ++)
  {
    if(trackInfo[i].age > 0)
    {
    x1 = trackInfo[i].x[0];
    y1 = trackInfo[i].y[0];
    x2 = trackInfo[i].x[1];
    y2 = trackInfo[i].y[1];


    vX = x2   - x1 ;
    vY = y2   - y1;
    vX = vX/16;
    vY = vY/16;
    fprintf(fp,"%d,%d,%f,%f,%d\n",x1/16 + startX,y1/16 + startY,vX,vY,errMeasure);
    }
  }
  fclose(fp);
  return(0);
}

#if ENABLE_TRACK_DUMP
static void writeTrackInfoToCsvFile(strackInfo * trackInfo, uint16_t maxNumKeyPoints,uint32_t frameIdx, char* outMetaDataDir)
{
  char trackInfoFile[200];
  TI_FILE * fp_track;

#if ENABLE_TEXT_TRACK_DUMP
  int i,curTrackSize, curIndx, k, j;

  sprintf(trackInfoFile,"%s\\inTrackInfo_%d.txt",outMetaDataDir,frameIdx);
  fp_track = FOPEN(trackInfoFile,"w");
  if(fp_track == NULL)
    exit(0);

  FPRINTF(fp_track,"TrackId, TrackSize,Pt 15,Pt 14 ,Pt 13,Pt 12,Pt 11,Pt 10,Pt 9,Pt 8,Pt 7,Pt 6,Pt 5,Pt 4,Pt 3,Pt 2,Pt 1,Pt 0\n");

  for(i = 0; i < maxNumKeyPoints; i ++)
  {
    curTrackSize = (trackInfo[i].age < 16) ? (trackInfo[i].age + 1) : 16;
    curIndx      = (16 + trackInfo[i].age - curTrackSize + 1)% 16;

    FPRINTF(fp_track,"%5d,%5d,",i,((trackInfo[i].age + 1) > 1) ? (trackInfo[i].age + 1) : 0 );

    k = curIndx;

    if(trackInfo[i].age == 0) curTrackSize = 0;

    for(j=0;j<curTrackSize;j++){
      FPRINTF(fp_track,"(%10.5f %10.5f),",trackInfo[i].x[k]/16.0,trackInfo[i].y[k]/16.0);
      k++;
      if(k == MAX_NUM_FRAMES_TO_TRACK)
        k =0;
    }
    FPRINTF(fp_track,"\n");

  }
#else
    sprintf(trackInfoFile,"%s\\inTrackInfo_%d.bin",outMetaDataDir,frameIdx);
    fp_track = FOPEN(trackInfoFile,"wb");
    if(fp_track == NULL)
      exit(0);
   FWRITE(trackInfo,1,maxNumKeyPoints*sizeof(strackInfo),fp_track);
#endif
  FCLOSE(fp_track);
}
#endif


int32_t APP_drawFlow(  uint8_t * currFrame,  const char * OutFileName,  strackInfo * trackInfo, uint16_t maxNumKeyPoints,    uint16_t width,  uint16_t height, uint16_t startX,uint16_t startY, uint8_t firstFrame )
{
  TI_FILE * fp;

  uint32_t size = width * height;
  int32_t idx;
  int32_t minPt;
  int32_t maxPt;

  uint16_t vx;
  uint16_t vy;

  uint8_t * y;
  uint8_t * u;
  uint8_t * v;

  uint8_t * r;
  uint8_t * g;
  uint8_t * b;

  int16_t xmin;
  int16_t ymin;
  int16_t xmax;
  int16_t ymax;

  uint16_t numLines;

  uint32_t bbColor;
  uint32_t flowColor;

  int32_t i,j;

  if(firstFrame)
  {
    fp = FOPEN((char *)OutFileName,"wb+");
  }
  else
  {
    fp = FOPEN((char *)OutFileName,"ab");
  }
  if(fp == NULL)
  {
    return (-1);
  }

  y = (uint8_t *)malloc(size);
  u = (uint8_t *)malloc(size/4);
  v = (uint8_t *)malloc(size/4);

  r = (uint8_t *)malloc(size);
  g = (uint8_t *)malloc(size);
  b = (uint8_t *)malloc(size);

  if((y == NULL) || (u == NULL) || (v == NULL) || (r == NULL) || (g == NULL) || (b == NULL))
  {
    return (-1);
  }

  memcpy(y,currFrame,size);
  memset(u,128,size/4);
  memset(v,128,size/4);

  APP_convertYUV420ptoRGB888(y,u,v,r,g,b,width,height);

  for(i = 0; i < maxNumKeyPoints; i ++)
  {
    if(trackInfo[i].age > 0)
    {

        idx = trackInfo[i].age % MAX_NUM_FRAMES_TO_TRACK;
        vx = trackInfo[i].x[idx]/16 + startX;
        vy = trackInfo[i].y[idx]/16 + startY;

        vx = vx & (~1);
        vy = vy & (~1);

        xmin = vx-2;
        ymin = vy-2;
        xmax = vx+2;
        ymax = vy+2;

        bbColor   = RGB88_GREEN;
        flowColor = RGB88_YELLOW;

        if( (xmin >= 0) && (xmin < width) && (xmax >= 0) && (xmax < width) && (ymin >= 0) && (ymin < height) && (ymax >= 0) && (ymax < height))
        {
          APP_drawBoxRGB(r,g,b, bbColor,width,xmin,ymin,xmax,ymax);

          numLines = (trackInfo[i].age + 1) > MAX_NUM_FRAMES_TO_TRACK ? MAX_NUM_FRAMES_TO_TRACK : (trackInfo[i].age+1);
          numLines = numLines-1;

          for(j = 0; j < numLines; j++)
          {
            minPt = (idx-j    + MAX_NUM_FRAMES_TO_TRACK) % MAX_NUM_FRAMES_TO_TRACK;
            maxPt = (idx-j - 1 + MAX_NUM_FRAMES_TO_TRACK) % MAX_NUM_FRAMES_TO_TRACK;
            xmin = trackInfo[i].x[minPt]/16 + startX;
            ymin = trackInfo[i].y[minPt]/16 + startY;

            xmin = xmin & (~1);
            ymin = ymin & (~1);

            xmax = trackInfo[i].x[maxPt]/16 + startX;
            ymax = trackInfo[i].y[maxPt]/16 + startY;

            xmax = xmax & (~1);
            ymax = ymax & (~1);
            if( (xmin >= 0) && (xmin < width) && (xmax >= 0) && (xmax < width) && (ymin >= 0) && (ymin < height) && (ymax >= 0) && (ymax < height))
            {
              APP_drawLineRGB(r,g,b,flowColor,width,xmin,ymin,xmax,ymax);
            }
          }

        }
    }
  }

  APP_convertRGB888toYUV420p(r,g,b,y,u,v,width,height);

  FWRITE(y,1,size,fp);
  FWRITE(u,1,size/4,fp);
  FWRITE(v,1,size/4,fp);


  free(y);
  free(u);
  free(v);

  free(r);
  free(g);
  free(b);

  FCLOSE(fp);

  return 0;
}
int SOFDemo_ReadCornerPoints(uint16_t *pListXY, char * fileName, uint16_t startX,uint16_t startY)
{
  FILE *fp = fopen(fileName,"r");
  int x,y;
  int numPoints =0 ;
  if(fp == NULL)
  {
    TEST_PRINTF(" Unable to open corner file %s for reading\n",fileName);
  }
  while(!feof(fp))
  {
    fscanf(fp, "%d, %d\n",&x, &y);
    if((x > startX) && (y > startY))
    {
      x -= startX;
      y -= startY;

      *pListXY = x << 4 ;
      pListXY++ ;
      *pListXY = y << 4 ;
      pListXY++ ;
      numPoints++;
    }
  }
  fclose(fp);
  return numPoints;
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

int32_t createAlgHandle(IM_Fxns ** handle, const IVISION_Fxns * ivisionFxns, IALG_Params * params)
{
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  /*---------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = ivisionFxns->ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status    = ivisionFxns->ialg.algAlloc(params, NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    return -1;
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
    return -1;
  }
  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the allocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = ivisionFxns->ialg.algInit((IALG_Handle)(handle), memRec,NULL, params);

  *handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    return -1;
  }
  free(memRec);
  return (IALG_EOK);

}

int32_t sofhandleCreate(IM_Fxns ** handle, config_params * params)
{
  int32_t i;
  int32_t status;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  SOF_TI_CreateParams  createParams;
  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(SOF_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL   ;
  createParams.imWidth                       = params->imWidth    ;
  createParams.imHeight                      = params->imHeight   ;
  createParams.roiWidth                      = params->roiWidth   ;
  createParams.roiHeight                     = params->roiHeight  ;
  createParams.startX                        = params->startX     ;
  createParams.startY                        = params->startY     ;
  createParams.numLevels                     = params->numLevels  ;
  createParams.keyPointDetectMethod          = params->keyPointDetectMethod;
  createParams.maxNumKeyPoints               = params->maxNumKeyPoints;
  createParams.maxPrevTrackPoints            = params->maxPrevTrackPoints;
  createParams.fast9Threshold                = params->fast9Threshold;
  createParams.scoreMethod                   = FAST9_BFTF_TI_THRESH_METHOD;
  createParams.harrisScaling                 = params->harrisScaling  ;
  createParams.nmsThreshold                  = params->nmsThreshold   ;
  createParams.keyPointDetectInterval        = params->keyPointDetectInterval;

  createParams.harrisScoreMethod             = params->harrisScoreMethod;
  createParams.harrisWindowSize              = params->harrisWindowSize;
  createParams.suppressionMethod             = params->suppressionMethod;
  createParams.trackOffsetMethod             = params->trackOffsetMethod;

  for(i = 0; i < createParams.numLevels; i++)
  {
    createParams.maxItersLK[i]                    = params->maxItersLK[i]  ;
    createParams.minErrValue[i]                   = params->minErrValue[i]  ;
    createParams.searchRange[i]                   = params->searchRange[i]  ;
  }
  status = createAlgHandle(handle,&SOF_TI_VISION_FXNS,(IALG_Params *)(&createParams));

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    return -1;
  }
  return status;
}

int32_t sofProcess(IM_Fxns * handle, uint8_t * currImage, uint16_t * inKeyPoints, uint16_t * outKeyPoints, uint16_t * errEstPtr, uint16_t * trackInfo, uint16_t * numKeyPoints, uint8_t staticFrame)
{
  int32_t status;
  SOF_TI_InArgs                           sofInArgs;
  SOF_TI_OutArgs                          sofOutArgs;
  IVISION_InBufs                          sofInBufs;
  IVISION_OutBufs                         sofOutBufs;

  IVISION_BufDesc   inImageBufDesc[2];
  IVISION_BufDesc   keyPointsBufDesc[3];


  IVISION_BufDesc   *inBufDescList[2];
  IVISION_BufDesc   *outBufDescList[3];

  sofInArgs.iVisionInArgs.subFrameInfo    = 0;
  sofInArgs.iVisionInArgs.size            = sizeof(PYRAMID_LK_TRACKER_TI_InArgs);
  sofOutArgs.iVisionOutArgs.size          = sizeof(SOF_TI_OutArgs);

  sofInBufs.bufDesc  = inBufDescList;
  sofOutBufs.bufDesc = outBufDescList;

  sofInBufs.numBufs   = 2;
  sofOutBufs.numBufs  = 3;

  inBufDescList[0]         = &inImageBufDesc[0];
  inBufDescList[1]         = &inImageBufDesc[1];
  outBufDescList[0]        = &keyPointsBufDesc[0];
  outBufDescList[1]        = &keyPointsBufDesc[1];
  outBufDescList[2]        = &keyPointsBufDesc[2];

  keyPointsBufDesc[0].bufPlanes[0].buf                   = (uint8_t * ) outKeyPoints ;
  keyPointsBufDesc[1].bufPlanes[0].buf                   = (uint8_t * ) errEstPtr;
  keyPointsBufDesc[2].bufPlanes[0].buf                   = (uint8_t * ) trackInfo;
  inImageBufDesc[0].bufPlanes[0].buf                     = (uint8_t * ) (currImage);
  inImageBufDesc[1].bufPlanes[0].buf                     = (uint8_t * ) (inKeyPoints);

  handle->ivision->ialg.algActivate((IALG_Handle)handle);

  sofInArgs.numCorners      = *numKeyPoints;
  sofInArgs.reservered0     = gParams.numLevelsPerCall;
  sofInArgs.trackErrThr     = gParams.trackErrThr    ;
  sofInArgs.trackMinFlowQ4  = gParams.trackMinFlowQ4 ;
  sofInArgs.trackNmsWinSize = gParams.trackNmsWinSize;
  sofInArgs.staticFrame     = staticFrame;

  status = handle->ivision->algProcess((IVISION_Handle)handle,
      &sofInBufs,&sofOutBufs,(IVISION_InArgs*)&sofInArgs,(IVISION_OutArgs *)&sofOutArgs);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      return status;
    }
  handle->ivision->ialg.algDeactivate((IALG_Handle)handle);

  *numKeyPoints = sofOutArgs.numCorners;

  return status;
}
extern uint32_t filteKeyPointsCycles;

int32_t pyramidLkSofTest(config_params * params)
{
  int32_t status;
  uint16_t frameIdx;

  strackInfo * trackInfo;
  uint8_t firstFrame;
  IM_Fxns  * sofAlgHandle;
  uint8_t *imagePtr[2];
  uint16_t * inKeyPoints;
  uint16_t * outKeyPoints;
  uint16_t * errEstPtr;
  uint16_t numKeyPoints;
  uint32_t t0, t1;
  uint8_t  staticFrame;
  int32_t fail = 0;
  uint16_t startX;
  uint16_t startY;
  /* Range checks on configuration parameters */
  if(((params->roiWidth + params->startX) > params->imWidth) || ((params->roiHeight + params->startY) > params->imHeight))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  if(((params->roiWidth <  64) || (params->roiHeight < 32) || (params->roiHeight & 1) || (params->roiWidth &  0xF)) && (params->numLevels > 1))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  if((params->numLevelsPerCall > PYRAMID_LK_TRACKER_TI_MAXLEVELS_PER_CALL) || (params->numLevelsPerCall < 0))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  /* Allocating memory for input and output buffer
  Image buffers and the key point in and out put buffer
  */
  imagePtr[0] = (uint8_t * )malloc(params->imWidth*params->imHeight);
  imagePtr[1] = (uint8_t * )malloc(params->imWidth*params->imHeight);

  if((imagePtr[0]== NULL) || (imagePtr[1]== NULL))
  {
    PRINT_ERRORE_MSG();
    return -1;
  }

  if((params->inPutType == 1) && (params->keyPointDetectMethod == SOF_EXTERNAL_KEY_POINTS))
  {
    inKeyPoints    = (uint16_t *)malloc(params->maxNumKeyPoints*sizeof(uint16_t)*2);
    if((inKeyPoints== NULL))
    {
      PRINT_ERRORE_MSG();
      return (-1);
    }
  }

 outKeyPoints   = (uint16_t *)malloc(params->maxNumKeyPoints*sizeof(uint16_t)*4);
 errEstPtr      = (uint16_t *)malloc(params->maxNumKeyPoints*sizeof(uint16_t));
 trackInfo      = (strackInfo *)malloc(params->maxNumKeyPoints*sizeof(strackInfo));

 memset(trackInfo,0,params->maxNumKeyPoints*sizeof(strackInfo));

  if((outKeyPoints== NULL) || (trackInfo== NULL) || (errEstPtr== NULL))
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  /*
  Creating ivsion algorithm instance of all the required applets
  */
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();


  status = sofhandleCreate(&sofAlgHandle, params);
  if(status)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }
  profiler_end_print(0);

  if ( params->trackOffsetMethod == SOF_TRACK_OFFSET_METHOD_IMAGE_ORIGIN )
  {
    startX = 0;
    startY = 0;
  }
  else if ( params->trackOffsetMethod == SOF_TRACK_OFFSET_METHOD_ROI_ORIGIN)
  {
    startX = params->startX;
    startY = params->startY;
  }
  else
  {
    startX = params->startX;
    startY = params->startY;
  }
  if(params->inPutType == 1)
  {
    params->startFrame = 0;
    params->numFrames  = 2;
  }
  firstFrame = 1;
  _tsc_start();
  for(frameIdx = params->startFrame; frameIdx < (params->numFrames + params->startFrame); frameIdx++)
  {

    printf("processing Frame Num : %d\n",frameIdx);
    /*
    Reading input images from the corresponding files
    */
    readintputImage(params, imagePtr[0],frameIdx);

    if((params->inPutType == 1) && (params->keyPointDetectMethod == SOF_EXTERNAL_KEY_POINTS) && (frameIdx == 1))
    {
      numKeyPoints = SOFDemo_ReadCornerPoints(inKeyPoints,params->keyPointFile,params->startX,params->startY);
    }

    staticFrame = 0;

      profiler_start();
      status = sofProcess(sofAlgHandle,imagePtr[0], inKeyPoints, outKeyPoints, errEstPtr, (uint16_t *)trackInfo,&numKeyPoints, staticFrame);
      profiler_end_print(1);

#if (!VCOP_HOST_EMULATION)
      printf("%-30s %15.2f \n","PYRAMID_LK_TRACKER_PROCESS", (2*(t1-t0)/1000000.0));
#endif

#if ENABLE_TRACK_DUMP
    writeTrackInfoToCsvFile(trackInfo, params->maxNumKeyPoints, frameIdx,params->outMetaDataDir);
#endif

#if ENABLE_FLOW_VISUVALIZATION
    if(strcmp(params->outVideoSeqFile,"NA"))
    {
      APP_drawFlow(imagePtr[0],params->outVideoSeqFile,trackInfo, params->maxNumKeyPoints, params->imWidth, params->imHeight,startX,startY, firstFrame);
#if ENABLE_REFERENCE_MATCHING
      fail = compareOutputYUV(params->outVideoSeqFile,params->refFileName, frameIdx, (params->imWidth * params->imHeight * 1.5));
#endif
      if(fail)
        break;

    }
#endif

    /*
      Computing accuracy statistic for the given ground truth file
    */
    if(params->inPutType == 1)
    {
      /*
        Writing out the SOF key points, flow vector and error measures to the text file
      */
      if(frameIdx == 1)
      {
        writeOutputToTxtFile(trackInfo,params->maxNumKeyPoints,startX,startY, params->outFileName);
        SOFDemo_ComputeStats(params->gtFileName,params->outFileName,params->statsFileName);
      }
    }

    firstFrame = 0;
  }

  profiler_printStatus(fail);

  /*
    Deleting all the created ivsion algorithm applets
  */
  status = deleteAlgHandle(sofAlgHandle);
  if(status)
  {
    PRINT_ERRORE_MSG();
    return (-1);
  }

  fflush(stdout);

  TEST_PRINTF("Free all the IO buffers \n");
  if((params->inPutType == 1) && (params->keyPointDetectMethod == SOF_EXTERNAL_KEY_POINTS))
  {
     free(inKeyPoints);
  }
  free(trackInfo   );
  free(errEstPtr   );
  free(outKeyPoints);
  free(imagePtr[0]);
  free(imagePtr[1]);
  TEST_PRINTF("Exiting the test with status : %d \n",status);
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif
  return status;
}

int main(int argc, char *argv[])
{
  int32_t         status = 0;
  FILE           *fp;
  int8_t         *LinePtr;
  int32_t         lineNum = -1;
  config_params  *params;
  int32_t         config_cmd;
  int8_t          configFileName[MAX_FILE_NAME_SIZE];

  report_printAppletInfo((int8_t *)"SOF_TI_VISION");
  params = (config_params *)(&gParams);

  if (argc > 1)
  {
    strcpy((char *)configFileName, argv[1]) ;
  }
  else
  {
    strcpy((char *)configFileName,CONFIG_LIST_FILE_NAME);
  }

  fp = fopen((const char *)configFileName , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s , Runing in defult mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    /* Validate the applet */
    status = pyramidLkSofTest(params);

    return(status);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
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
      status = readparamfile((char *)configFileName, gsTokenMap_sof) ;
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }
      printConfigParams(params);

      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)params->testCaseDesc,params->performanceTestcase);
      printparams(gsTokenMap_sof,(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)params,sizeof(config_params)) ;

      /* Validate the applet */
      status = pyramidLkSofTest(params);
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
  fclose(fp);

  return status;
}
