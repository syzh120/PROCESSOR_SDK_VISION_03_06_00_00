/*
* module name       :TI Lane Detection 
*
* module descripton :Lane Detection and departure warning using TI’s C66x DSP
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

/** @file ld_tb.c
*
*  @brief  This file contains test code for lane detection algorithm
*
*
*  @date   June 2014
*
*  Description
*    This file contains test code to validate the frame level algorithm TI LD
*
*  @date -- December 2015
*
*  Descritpion
*    File modified to output different visualization of lanes
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "xdais_types.h"

#include "ld_config.h"
#include "ild_ti.h"
#include "ti_mem_manager.h"
//#if (!HOST_EMULATION)
//#include "edma3_lld_helper.h"
//#endif
#include "ti_draw_utils.h"
#include "ti_file_io.h"

#define ENABLE_TRACES 0
#define RANDOM_INPUT  0

#define DISABLE_FILE_IO 0

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#define ENABLE_TRACES 1
#endif
#define RGB88_GREEN ((0 << 16) | (255 << 8) | (0))
#define RGB88_RED ((255 << 16) | (0 << 8) | (0))



#if (!HOST_EMULATION)
void _TSC_enable();
long long _TSC_read();

#define L2CFG()  (*(volatile uint32_t *)0x01840000)
#define L1PCFG() (*(volatile uint32_t *)0x01840020)
#define L1DCFG() (*(volatile uint32_t *)0x01840040)

static void SetMAR()
{

  uint32_t i ;

  uint32_t* MAR = (uint32_t*)0x01848200 ; //MAR_128

  /* DDR from 0x80000000 to 9F000000 made cacheable */
  /* From 9F000000 to A0000000 is non-cacheable region. */
  /*  This non-cacheable region is used to hold input and output buffers */
  for(i = 128 ;i <= 158 ; i++)
  {
    *MAR = 0x1;
     MAR++ ;
  }
  return ;
}

static void CacheWbInv()
{
  uint32_t* L1DWBINV = (uint32_t *)0x01845044;
  uint32_t* L2WBINV = (uint32_t *)0x01845004;
  
  /* Write back invalidate cache */
  *L1DWBINV = 1;
  *L2WBINV = 1; 
}

static void InitCache()
{
  /*-------------------------------------------------------------------------*/
  /* 4-> full 256 KB as cache, 3-> 128KB, 2 -> 64KB, 1-> 32KB                */
  /* IMPORTANT :: Currently 0 KB of L2 is assumed to be SRAM, hence in final */
  /* application any amount L2 can be configured as SRAM, but DMVAL will not */
  /* use that. Only thing here important is that if in application full L2 is*/
  /* configured as cache then standalone and final application performance   */
  /* numbers will match. otherwise no functionality issue.                    */
  /*-------------------------------------------------------------------------*/
  L2CFG()  = 4;

  /*-------------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                                 */
  /* Nothing in L1P is assumed as SRAM, so no dependency from final applicati*/
  /* -on configuration. Only thing if full L1P is configured as cache then   */
  /* standalone and application performance numbers will match.              */
  /*-------------------------------------------------------------------------*/
  L1PCFG() = 4;

 /*-------------------------------------------------------------------------*/
  /* 1 -> 4 KB, 2-> 8KB, 3 ->16 KB, 4 -> 32KB as cache                       */
  /* Currently 4KB as cache has been allocated for L1D, Rest 28 KB is configu*/
  /* red as SRAM. Any change in cache configuration should be done in conjuca*/
  /* of linker command file modification in test applciation                 */
  /* IMPORTANT :: Here 28 KB of L1 D is assumed as SRAM hence there is depend*/
  /* -dency from final applcaition configuration of L1D. If atleast 28 KB of */
  /* L1D is not configured as SRAM in final application then that will be a  */
  /* functional issue.                                                       */
  /*-------------------------------------------------------------------------*/
  L1DCFG() = 2;

  SetMAR() ;
}

#endif

#define ALIGN_T0_32(x) (((x+31)/32)*32)


#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (23*1024)

#define L2SRAMMEM_SIZE (128*1024)

#define DDRNONCACHE_SIZE (16384*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];
TIMemObject memObj_DMEM;


#pragma DATA_SECTION (L2MEM_SCRATCH, ".l2memSect");
uint8_t L2MEM_SCRATCH[L2SRAMMEM_SIZE];
TIMemObject memObj_L2MEM;

#pragma DATA_SECTION (DDRMEM_NONCACHE, ".ddrnoncacheSect");
uint8_t DDRMEM_NONCACHE[DDRNONCACHE_SIZE];
TIMemObject memObj_DDRMEMNC;

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  TIMemHandle memHdl_L2MEM = &memObj_L2MEM;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_L2MEM, memRec[i].size, memRec[i].alignment);
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
    if(memRec[i].space == IALG_EXTERNAL){
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs, sLD_Config * params)
{
  TIMemHandle memHdl_EXTMEM = &memObj_DDRMEMNC; 
  uint32_t size;
  
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->numPlanes                       = 1;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.x = params[0].startX;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.y = params[0].startY;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width              = params[0].actualImgWidth;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height             = params[0].actualImgHeight;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width     = params[0].roiWidth;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height    = params[0].roiHeight;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].planeType          = 0; // Luma Y
  size = (inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width)*(inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height);
  /* Allocate the buffer in DDR which is non-cacheable */
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf = TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);
  if((inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERRORE_MSG();
  }

  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->numPlanes                        = 1;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.topLeft.x  = 0;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.topLeft.y  = 0;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].width               = LD_TI_MAXLANEPOINTS * sizeof(uint32_t);
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].height              = 1;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.width      = LD_TI_MAXLANEPOINTS * sizeof(uint32_t);
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.height     = 1;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].planeType           = 0;
  size = (outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].width)*(outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].height);
  /* Allocate the buffer in DDR which is non-cacheable */
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf = TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);
  if((outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERRORE_MSG();
  }
  memset(outBufs->bufDesc[0]->bufPlanes[0].buf ,0,outBufs->bufDesc[0]->bufPlanes[0].width * outBufs->bufDesc[0]->bufPlanes[0].height);

  return IALG_EOK;
}

int32_t TestApp_ReadInBufs(IVISION_InBufs * inBufs,int32_t currFrameNum, char * fileName)
{
  int32_t size = inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width * inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height;

#if (!RANDOM_INPUT)
  FILE * fp;
  fp = fopen(fileName, "rb");
  if(fp == NULL)
  {
    goto Exit;
  }

  fseek(fp, currFrameNum*size, SEEK_SET);
  fread(inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf,1,size,fp);
  fclose(fp);
#else
  int32_t i;
  uint8_t * ptr = (uint8_t *)(inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf);
  for(i = 0; i < size; i++)
  {
    ptr[i] = (i & 0xFF);
  }
#endif

  Exit:
    return (0);
}

int32_t TestApp_WriteOutBufs(IVISION_OutBufs * outBufs, uint16_t width, uint16_t height, char * fileName)
{
  FILE * fp;
  static int firtsWrite = 1;
  int32_t size;
  int32_t retVal;
  if(firtsWrite)
  {
    fp = fopen(fileName, "wb");
    fclose(fp);
    firtsWrite = 0;
  }
  fp = fopen(fileName, "ab");
  if(fp == NULL)
  {
    goto Exit;
  }
  size= width * height;

  retVal = fwrite(outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf,1,size,fp);

  if(retVal != size)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  fclose(fp);
  Exit:
    return (0);
}

int32_t solveLineEqForX(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t y)
{
  float inv_slope = (float) ((int32_t)(x2-x1))/((int32_t)(y2-y1));

  return (int32_t) ((float)((int32_t)(y-y1))*inv_slope + x1);
}

int32_t drawLaneRegion(uint8_t *pOutIm, LD_TI_output * pLanePoints, uint16_t numLeftLanePoints, uint16_t numRightLanePoints , sLD_Config * params, uint32_t testcase, 
                          uint32_t *pLaneMaxWidth, uint32_t *pLaneMinWidth, uint8_t infoFlag, char * fileName)
{
  uint32_t maxXL, maxYL, maxXR, maxYR;
  uint32_t minXL, minXR, minYL, minYR;
  uint32_t leftTopX, leftTopY, leftBottomX, leftBottomY;
  uint32_t rightTopX, rightTopY, rightBottomX, rightBottomY;
  uint32_t i;
  LD_TI_output *pPoint;
  uint16_t startY, roiHeight;
  uint16_t roiWidth, width, height;
  int32_t trapX[4], trapY[4];
  int32_t y, x_l, x_r;
  uint8_t * yPlane;
  uint8_t * uPlane;
  uint8_t * vPlane;
  uint8_t * rPlane, r;
  uint8_t * gPlane, g;
  uint8_t * bPlane, b;
  uint32_t size;
  uint32_t laneColor;
  uint32_t offset;
  FILE * fp;
  static int firtsWrite = 1;

  if(firtsWrite)
  {
    fp = fopen(fileName, "wb");
    fclose(fp);
    firtsWrite = 0;
  }
  fp = fopen(fileName, "ab");
  if(fp == NULL)
  {
    return -1;
  }

  maxXL = 0;
  minXL = 0xffff;
  maxYL = 0;
  minYL = 0xffff;

  width = params[testcase].actualImgWidth;
  height = params[testcase].actualImgHeight;
  size = width * height;

  yPlane = (uint8_t *)malloc(size);
  uPlane = (uint8_t *)malloc(size/4);
  vPlane = (uint8_t *)malloc(size/4);
  rPlane = (uint8_t *)malloc(size);
  bPlane = (uint8_t *)malloc(size);
  gPlane = (uint8_t *)malloc(size);

  if((yPlane == NULL) || (uPlane == NULL) || (vPlane == NULL) || (rPlane == NULL) || (gPlane == NULL) || (bPlane == NULL))
  {
    return (-1);
  }

  memcpy(yPlane, pOutIm, size);
  memset(uPlane, 128, size/4);
  memset(vPlane, 128, size/4);

  APP_convertYUV420ptoRGB888(yPlane,uPlane,vPlane,rPlane,gPlane,bPlane,width,height);
  laneColor = RGB88_GREEN;
  r = (laneColor >> 16) & 0xff;
  g = (laneColor >> 8 ) & 0xff;
  b = (laneColor      ) & 0xff;

  if (numLeftLanePoints + numRightLanePoints < 1) 
  {
    APP_convertRGB888toYUV420p(rPlane,gPlane,bPlane,yPlane,uPlane,vPlane,width,height);

    fwrite(yPlane, 1, size, fp);
    fwrite(uPlane, 1, size/4, fp);
    fwrite(vPlane, 1, size/4, fp);
    goto EXIT;
  }

  if ((infoFlag == LD_TI_RIGHT_LANE_CROSS) || (infoFlag == LD_TI_LEFT_LANE_CROSS))
  {
    APP_convertRGB888toYUV420p(rPlane,gPlane,bPlane,yPlane,uPlane,vPlane,width,height);

    fwrite(yPlane, 1, size, fp);
    fwrite(uPlane, 1, size/4, fp);
    fwrite(vPlane, 1, size/4, fp);
    goto EXIT;
  }

  // find min and max for X, Y of left and right lane
  for(i = 0; i < numLeftLanePoints; i++)
  {
    pPoint = &pLanePoints[i];

    if(pPoint->x < minXL)
    {
      minXL = pPoint->x;
    }

    if(pPoint->x > maxXL)
    {
      maxXL = pPoint->x;
    }

    if(pPoint->y < minYL)
    {
      minYL = pPoint->y;
    }

    if(pPoint->y > maxYL)
    {
      maxYL = pPoint->y;
    }
  }

  leftTopX = maxXL;
  leftTopY = minYL;
  leftBottomX = minXL;
  leftBottomY = maxYL;

  maxXR = 0;
  minXR = 0xffff;
  maxYR = 0;
  minYR = 0xffff;

  for(i = numLeftLanePoints; i < (numLeftLanePoints + numRightLanePoints); i++)
  {
    pPoint = &pLanePoints[i];

    if(pPoint->x < minXR)
    {
      minXR = pPoint->x;
    }

    if(pPoint->x > maxXR)
    {
      maxXR = pPoint->x;
    }

    if(pPoint->y < minYR)
    {
      minYR = pPoint->y;
    }

    if(pPoint->y > maxYR)
    {
      maxYR = pPoint->y;
    }
  }

  rightTopX = minXR;
  rightTopY = minYR;
  rightBottomX = maxXR;
  rightBottomY = maxYR;

  startY = params[testcase].startY;
  roiHeight = params[testcase].roiHeight;
  roiWidth = params[testcase].roiWidth;


  trapY[0] = startY;
  trapY[1] = trapY[0];

  // check if (startY + roiHeight < imgHeight)
  if((startY + roiHeight) >= height)
  {
    trapY[2] = height - 10;
    trapY[3] = trapY[2];
  }
  else
  {
    trapY[2] = startY + roiHeight;
    trapY[3] = trapY[2];
  }

  trapX[0] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[0]);
  trapX[1] = solveLineEqForX(rightTopX, rightTopY, rightBottomX, rightBottomY, trapY[1]);
  trapX[2] = solveLineEqForX(rightTopX, rightTopY, rightBottomX, rightBottomY, trapY[2]);
  trapX[3] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[3]);

  if(numRightLanePoints > 1)
  {
    // If there are no left lane points, find topXL and botXL = roiWidth, and topYL = topYR, botYL = botYR
    if(((leftTopX == leftBottomX) && (leftTopY == leftBottomY)) || (numLeftLanePoints == 0))
    {
      if ((*pLaneMaxWidth != 0) && (*pLaneMinWidth != 0)){
        leftTopX = trapX[1] - *pLaneMinWidth;
        leftTopY = trapY[1];
        leftBottomX = trapX[2] - *pLaneMaxWidth;
        leftBottomY = trapY[2];
        trapX[0] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[0]);
        trapX[3] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[3]);
      } else {
        leftTopX = trapX[2] - roiWidth/2; // used BottomX because need to be trapezoid
        leftBottomX = trapX[1] - roiWidth/2; // used TopX because need to be trapezoid
        leftTopY = trapY[1];
        leftBottomY = trapY[2];
        trapX[0] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[0]);
        trapX[3] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[3]);
      }
    }
  }
  else
  {
    rightTopX = rightBottomX;
    rightTopY = rightBottomY;
  }

  if(numLeftLanePoints > 1)
  {
    // If there are no right lane points, find topXR and botXR from roiWidth, and topYR = topYL, botYR = botYL
    if(((rightTopX == rightBottomX) && (rightTopY == rightBottomY)) || (numRightLanePoints == 0))
    {
      if ((*pLaneMaxWidth != 0) && (*pLaneMinWidth != 0)){
        rightTopX = trapX[0] + *pLaneMinWidth;
        rightTopY = trapY[0];
        rightBottomX = trapX[3] + *pLaneMaxWidth;
        rightBottomY = trapY[3];
        trapX[1] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[1]);
        trapX[2] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[2]);
      } else {
        rightTopX = trapX[3] + roiWidth/2; // used BottomX because need to be trapezoid
        rightBottomX = trapX[0] + roiWidth/2; // used TopX because need to be trapezoid
        rightTopY = trapY[0];
        rightBottomY = trapY[3];
        trapX[1] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[1]);
        trapX[2] = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[2]);
      }
    }
  }
  else
  {
    APP_convertRGB888toYUV420p(rPlane,gPlane,bPlane,yPlane,uPlane,vPlane,width,height);

    fwrite(yPlane, 1, size, fp);
    fwrite(uPlane, 1, size/4, fp);
    fwrite(vPlane, 1, size/4, fp);
    goto EXIT;
  }
  y = trapY[0];
  x_l = trapX[0];
  x_r = trapX[1];

  // Update the laneMaxWidth the first time
  if (*pLaneMinWidth == 0)
  {
    *pLaneMinWidth = trapX[1] - trapX[0];
  }

  if (*pLaneMaxWidth == 0)
  {
    *pLaneMaxWidth = trapX[2] - trapX[3];
  }

  while(1)
  {
    for(i = x_l; i < x_r; i++)
    {
      offset = (y * width) + i;
      rPlane[offset] = r;
      gPlane[offset] = g;
      bPlane[offset] = b;
    }
    y += 10;
    x_l = solveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, y);
    if((x_l < 0) || (x_l > width))
    {
      break;
    }
    x_r = solveLineEqForX(rightTopX, rightTopY, rightBottomX, rightBottomY, y);
    if((x_r < 0) || (x_r > width))
    {
      break;
    }

    if(y > trapY[3])
    {
      break;
    }
  }

  APP_convertRGB888toYUV420p(rPlane,gPlane,bPlane,yPlane,uPlane,vPlane,width,height);

  fwrite(yPlane, 1, size, fp);
  fwrite(uPlane, 1, size/4, fp);
  fwrite(vPlane, 1, size/4, fp);

EXIT:
  fclose(fp);
  free(yPlane);
  free(uPlane);
  free(vPlane);

  free(rPlane);
  free(gPlane);
  free(bPlane);

  return (0);
}

int32_t markLanePoints(uint8_t *pOutIm, LD_TI_output * pLanePoints, uint16_t numLeftLanePoints, uint16_t numRightLanePoints , uint8_t infoFlag,
            sLD_Config * params, uint32_t testcase, char * fileName)
{
  uint32_t j;
  uint8_t * yPlane;
  uint8_t * uPlane;
  uint8_t * vPlane;
  uint8_t * rPlane, r;
  uint8_t * gPlane, g;
  uint8_t * bPlane, b;
  uint32_t size;
  uint32_t laneColor;
  uint32_t offset;
  uint16_t width, height;
  FILE * fp;
  uint16_t x, y;
  LD_TI_output *pPoint;
  static int firstWrite = 1;

  if(firstWrite)
  {
    fp = fopen(fileName, "wb");
    fclose(fp);
    firstWrite = 0;
  }
  fp = fopen(fileName, "ab");
  if(fp == NULL)
  {
    return (-1);
  }

  width = params[testcase].actualImgWidth;
  height = params[testcase].actualImgHeight;
  size = width * height;

  yPlane = (uint8_t *)malloc(size);
  uPlane = (uint8_t *)malloc(size/4);
  vPlane = (uint8_t *)malloc(size/4);
  rPlane = (uint8_t *)malloc(size);
  bPlane = (uint8_t *)malloc(size);
  gPlane = (uint8_t *)malloc(size);

  if((yPlane == NULL) || (uPlane == NULL) || (vPlane == NULL) || (rPlane == NULL) || (gPlane == NULL) || (bPlane == NULL))
  {
    return (-1);
  }

  memcpy(yPlane, pOutIm, size);
  memset(uPlane, 128, size/4);
  memset(vPlane, 128, size/4);

  APP_convertYUV420ptoRGB888(yPlane,uPlane,vPlane,rPlane,gPlane,bPlane,width,height);

  if (numLeftLanePoints + numRightLanePoints < 1)
  {
    APP_convertRGB888toYUV420p(rPlane,gPlane,bPlane,yPlane,uPlane,vPlane,width,height);

    fwrite(yPlane, 1, size, fp);
    fwrite(uPlane, 1, size/4, fp);
    fwrite(vPlane, 1, size/4, fp);
    goto EXIT;
  }

  if((infoFlag == LD_TI_RIGHT_LANE_CROSS) || (infoFlag == LD_TI_LEFT_LANE_CROSS))
  {
    laneColor = RGB88_RED;
    r = (laneColor >> 16) & 0xff;
    g = (laneColor >> 8 ) & 0xff;
    b = (laneColor      ) & 0xff;
  }
  else
  {
    laneColor = RGB88_GREEN;
    r = (laneColor >> 16) & 0xff;
    g = (laneColor >> 8 ) & 0xff;
    b = (laneColor      ) & 0xff;
  }

  for(j = 0; j < (numLeftLanePoints + numRightLanePoints); j++)
  {
    pPoint = &pLanePoints[j];
    x = pPoint->x;
    y = pPoint->y;
    offset = (y * width) + x;
    rPlane[offset] = r;
    gPlane[offset] = g;
    bPlane[offset] = b;
    offset = (y * width) + (x - 1);
    rPlane[offset] = r;
    gPlane[offset] = g;
    bPlane[offset] = b;
    offset = (y * width) + (x + 1);
    rPlane[offset] = r;
    gPlane[offset] = g;
    bPlane[offset] = b;
    offset = (y * width) + (x - 2);
    rPlane[offset] = r;
    gPlane[offset] = g;
    bPlane[offset] = b;
    offset = (y * width) + (x + 2);
    rPlane[offset] = r;
    gPlane[offset] = g;
    bPlane[offset] = b;

  }

  APP_convertRGB888toYUV420p(rPlane,gPlane,bPlane,yPlane,uPlane,vPlane,width,height);

  fwrite(yPlane, 1, size, fp);
  fwrite(uPlane, 1, size/4, fp);
  fwrite(vPlane, 1, size/4, fp);

EXIT:
  fclose(fp);
  free(yPlane);
  free(uPlane);
  free(vPlane);

  free(rPlane);
  free(gPlane);
  free(bPlane);

  return (0);
}

int32_t ldTest(sLD_Config * testcaseParams)
{
  int32_t numMemRec;
  uint32_t j;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t testcase;
  FILE *fpOut ;
  char *outFile;
  char *inFile;
  char *name;
  char *file;
  long long  t0, t1;
#if (!HOST_EMULATION)
  _TSC_enable();
#endif
  /*-----------------------------------------------------------------
   Pointer to algorithm instance
   -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
   Algorithm parameters memory in stack
   -----------------------------------------------------------------*/
  LD_TI_CreateParams   createParams;
  LD_TI_InArgs      inArgs;
  IVISION_InBufs    inBufs;
  
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[LD_BUFDESC_IN_TOTAL];

  LD_TI_OutArgs     outArgs;
  IVISION_OutBufs   outBufs;
  
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[LD_BUFDESC_OUT_TOTAL];

#if ENABLE_TRACES
  IVISION_BufDesc   outImBufDesc;
  IVISION_BufDesc   *outImBufDescList[1];
  IVISION_InBufs    outImBufs;
  uint8_t *laneOutIm;
  uint32_t laneMaxWidth = 0;
  uint32_t laneMinWidth = 0;
#endif

  outArgs.iVisionOutArgs.size = sizeof(LD_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(LD_TI_InArgs);
  
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L1DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L2MEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pL2mem;
  TIMemHandle memHdl_L2MEM;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for DDR NON CACHE MEM                     */
  /*--------------------------------------------------------------------------*/
  uint8_t *pExtmem;
  TIMemHandle memHdl_EXTMEM;

  LD_TI_output *outputLanes;
  uint32_t     *outNumLanePoints;
  uint32_t frameIdx;


#if (!HOST_EMULATION)
  //EDMA3_RM_Result edma3Error;
  //EDMA3_RM_Handle edma3RmLldHandle;
  /* Create a resource manager Handle */
  //edma3RmLldHandle = EDMA3_LLD_HELPER_init(0, NULL, NULL, &edma3Error);
#endif

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  pL2mem = (uint8_t *)&L2MEM_SCRATCH;
  memHdl_L2MEM = &memObj_L2MEM;
  TI_CreateMemoryHandle(memHdl_L2MEM, pL2mem, L2SRAMMEM_SIZE);

  pExtmem = (uint8_t *)&DDRMEM_NONCACHE;
  memHdl_EXTMEM = &memObj_DDRMEMNC;
  TI_CreateMemoryHandle(memHdl_EXTMEM, pExtmem, DDRNONCACHE_SIZE);

  for ( testcase = 0 ; testcase < ld_numTestCases; testcase++ )
  {
    /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = LD_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = LD_BUFDESC_OUT_TOTAL;

    inBufDescList[LD_BUFDESC_IN_IMAGEBUFFER] = &inBufDesc;
    outBufDescList[LD_BUFDESC_OUT_XY_LIST]   = &outBufDesc;

#if ENABLE_TRACES
    outImBufs.bufDesc = outImBufDescList;
    outImBufs.numBufs = 1;
    outImBufDescList[0] = &outImBufDesc;
#endif

    /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    createParams.maxImageWidth      = testcaseParams[testcase].maxImageWidth;
    createParams.maxImageHeight     = testcaseParams[testcase].maxImageHeight;
    createParams.maxRho             = testcaseParams[testcase].maxRho;
    createParams.maxTheta           = LD_TI_MAXNUMTHETA;
#if (!HOST_EMULATION)
    //createParams.edma3RmLldHandle   = edma3RmLldHandle;
	createParams.edma3RmLldHandle   = NULL;
#else
    createParams.edma3RmLldHandle   = NULL;
#endif

    /*-----------------------------------------------------------------
      Query alogorithm memory requirement using standard IALG interface
      -----------------------------------------------------------------*/
    numMemRec = LD_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = LD_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Lane Detection algorithm Create Done\n");
#endif
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
    status = LD_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
            memRec,NULL,(IALG_Params *)(&createParams));

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Lane detection algorithm Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(LD_TI_InArgs);
    inArgs.cannyHighThresh            = testcaseParams[testcase].cannyHiThresh ;
    inArgs.cannyLowThresh             = testcaseParams[testcase].cannyLoThresh ;
    inArgs.houghNmsThresh             = testcaseParams[testcase].houghNmsThresh ;
    inArgs.startThetaLeft             = testcaseParams[testcase].startThetaLeft ;
    inArgs.endThetaLeft               = testcaseParams[testcase].endThetaLeft ;
    inArgs.startThetaRight            = testcaseParams[testcase].startThetaRight ;
    inArgs.endThetaRight              = testcaseParams[testcase].endThetaRight ;
    inArgs.thetaStepSize              = testcaseParams[testcase].thetaStepSize ;
    inArgs.resetLDAlg                 = 0;
    if(testcaseParams[testcase].trackMethod == 1)
    {
      inArgs.trackingMethod             = LD_TI_TRACK_KF;
    }
    else
    {
      inArgs.trackingMethod             = LD_TI_TRACK_DISABLE;
    }
    inArgs.numHoughMaximasDet         = testcaseParams[testcase].numHoughMaximasDet;
    inArgs.numHoughMaximasTrack       = testcaseParams[testcase].numHoughMaximasTrack;
    if(testcaseParams[testcase].enableWarning == 1)
    {
      inArgs.warningMethod              = LD_TI_WARNING_ENABLE;
    }
    else
    {
      inArgs.warningMethod              = LD_TI_WARNING_DISABLE;
    }
    inArgs.departThetaLeftMin         = testcaseParams[testcase].departThetaLeftMin;
    inArgs.departThetaLeftMax         = testcaseParams[testcase].departThetaLeftMax;
    inArgs.departRhoLeftMin           = testcaseParams[testcase].departRhoLeftMin;
    inArgs.departRhoLeftMax           = testcaseParams[testcase].departRhoLeftMax;
    inArgs.departThetaRightMin        = testcaseParams[testcase].departThetaRightMin;
    inArgs.departThetaRightMax        = testcaseParams[testcase].departThetaRightMax;
    inArgs.departRhoRightMin          = testcaseParams[testcase].departRhoRightMin;
    inArgs.departRhoRightMax          = testcaseParams[testcase].departRhoRightMax;
    inBufDesc.numPlanes               = 1;
    outBufDesc.numPlanes              = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs,&testcaseParams[testcase]);

#if ENABLE_TRACES
    outImBufDesc.bufPlanes[0].frameROI.topLeft.x = testcaseParams[testcase].startX;
    outImBufDesc.bufPlanes[0].frameROI.topLeft.y = testcaseParams[testcase].startY;
    outImBufDesc.bufPlanes[0].width              = testcaseParams[testcase].actualImgWidth;
    outImBufDesc.bufPlanes[0].height             = testcaseParams[testcase].actualImgHeight;
    outImBufDesc.bufPlanes[0].frameROI.width     = testcaseParams[testcase].roiWidth;
    outImBufDesc.bufPlanes[0].frameROI.height    = testcaseParams[testcase].roiHeight;
    outImBufDesc.bufPlanes[0].planeType          = 0; // Luma Y

    outImBufDesc.bufPlanes[0].buf = 
      malloc(outImBufDesc.bufPlanes[0].width * outImBufDesc.bufPlanes[0].height);
    if((outImBufDesc.bufPlanes[0].buf == NULL))
    {
      PRINT_ERRORE_MSG();
    }
    laneOutIm = (uint8_t *)outImBufDesc.bufPlanes[0].buf;
#endif
    name = (char *)malloc(256);
    file = (char *)malloc(256);

    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {
      sprintf(name, "%d.csv", frameIdx);
      strcpy(file, (char *)testcaseParams[testcase].outFileName);
      outFile = strcat((char *)file, name);      
      fpOut = fopen((char *)outFile,"w");
      if(fpOut == NULL)
      {
        printf("Unable to open output file\n");
        goto EXIT_LOOP;
      }
#if ENABLE_TRACES
      printf("Processing started for frame %d \n",frameIdx);
#endif
      sprintf(name, "%d.y", frameIdx);
      strcpy(file, (char *)testcaseParams[testcase].inFileName);
      inFile = strcat((char *)file, name);
      TestApp_ReadInBufs(&inBufs,0,inFile);

#if ENABLE_TRACES
      TestApp_ReadInBufs(&outImBufs,0,inFile);
#endif
#if (!HOST_EMULATION)
      /* Write back Invalidate cache */
      CacheWbInv();
      t0 = _TSC_read();
#endif
      status = handle->ivision->algProcess((IVISION_Handle)handle,
        &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
#if (!HOST_EMULATION)
      t1 = _TSC_read();
      printf(" Cycles per frame %ld \n", t1-t0);
      /* Write back Invalidate cache */
      CacheWbInv();
#endif
      printf(" Number of Left lane points detected = %d\n", outArgs.numLeftLanePoints);
      printf(" Number of Right lane points detected = %d\n", outArgs.numRightLanePoints);

      if(status != IALG_EOK)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
#if ENABLE_TRACES
      printf("Processing Completed for frame %d \n",frameIdx);
#endif
      outNumLanePoints = ( uint32_t * )outBufs.bufDesc[0]->bufPlanes[0].buf;
      outputLanes = ( LD_TI_output * )(outNumLanePoints);

      for(j = 0; j < (outArgs.numLeftLanePoints + outArgs.numRightLanePoints); j++)
      {
        fprintf(fpOut,"%4d,%4d \n",outputLanes[j].x,outputLanes[j].y);
      }
      if(fpOut)
      {
        fclose(fpOut);
      }
#if ENABLE_TRACES
      sprintf(name, "../testvecs/output/ImgOut%d.y", frameIdx);
      if(testcaseParams[testcase].visType == 0)
      {
        status = markLanePoints(laneOutIm, outputLanes, outArgs.numLeftLanePoints, outArgs.numRightLanePoints, outArgs.infoFlag, testcaseParams, testcase, name);
      }
      else
      {
        status = drawLaneRegion(laneOutIm, outputLanes, outArgs.numLeftLanePoints, outArgs.numRightLanePoints, testcaseParams, testcase, &laneMaxWidth, &laneMinWidth, outArgs.infoFlag, name);
      }
      if(status != 0)
      {
        printf("Draw lane failed!");
        goto EXIT_LOOP;
      }
#endif

    }

EXIT_LOOP:
    if(name != NULL)
    {
      free(name);
    }
    if(file != NULL)
    {
      free(file);
    }    
    if(fpOut)
    {
      fclose(fpOut);
    }
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

#if ENABLE_TRACES
    free(outImBufDesc.bufPlanes[0].buf);
#endif

  }
#if (!HOST_EMULATION)
  /* Delete resouce manager Handle */
  //EDMA3_LLD_HELPER_deinit(0, edma3RmLldHandle);
#endif

  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[LD_FILE_NAME_SIZE]={0};
#if (!HOST_EMULATION)
  InitCache();
#endif
  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/ld.cfg");
  }

  status = readparamfile(configFile, &gsTokenMap_LD[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  /* Validate the algorithm */
  status = ldTest(gConfig_LD);

  return status;
}



