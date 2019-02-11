/*
 
Copyright (c) [2015] – [2017] Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI ("TI Devices").  No hardware patent is licensed hereunder.
 
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

/** @file clr_tb.c
*
*  @brief  This file contains test code for Circular light Recognition algorithm
*
*
*  @date   June 2014
*
*  Description
*    This file contains test code to validate the frame level algorithm TI CLR
*    
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include <conio.h>


#include "xdais_types.h"
#include "clr_config.h"
#include "iclr_ti.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"

#define ENABLE_TRACES 1
#define RANDOM_INPUT  0

#define DISABLE_FILE_IO 0

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#define ENABLE_TRACES 1
#endif


#define L2CFG()  (*(volatile uint32_t *)0x01840000)
#define L1PCFG() (*(volatile uint32_t *)0x01840020)
#define L1DCFG() (*(volatile uint32_t *)0x01840040)

#define MAX_IMG_BUF_SIZE ((1920*1088*1))

#pragma DATA_SECTION (IMG_BUF2, ".fileio_data");
uint8_t IMG_BUF2[MAX_IMG_BUF_SIZE];

#pragma DATA_SECTION (IMG_BUF1, ".fileio_data");
uint8_t IMG_BUF1[MAX_IMG_BUF_SIZE];

#pragma DATA_SECTION (IMG_BUF3, ".fileio_data");
uint8_t IMG_BUF3[MAX_IMG_BUF_SIZE];

#pragma DATA_SECTION (trace_buf_y, ".fileio_data");
uint8_t trace_buf_y[MAX_IMG_BUF_SIZE];

#pragma DATA_SECTION (trace_buf_u, ".fileio_data");
uint8_t trace_buf_u[MAX_IMG_BUF_SIZE/4];

#pragma DATA_SECTION (trace_buf_v, ".fileio_data");
uint8_t trace_buf_v[MAX_IMG_BUF_SIZE/4];

#define HOST_MALLOC_PACKET_SIZE (128)
#define HOST_MALLOC_TOT_PACKET  (100)

#pragma DATA_SECTION (SCRATCH_NON_CACHED, ".hostdata");
uint8_t SCRATCH_NON_CACHED[HOST_MALLOC_TOT_PACKET][HOST_MALLOC_PACKET_SIZE];

#pragma DATA_SECTION (SCRATCH_NON_CACHED, ".hostdata");
uint8_t SCRATCH_PACKET_VALIDITY[HOST_MALLOC_TOT_PACKET];

#pragma DATA_SECTION (OUT_BUF1, ".fileio_data");
uint8_t OUT_BUF1[TI_CLR_OUT_BUFDESC_LIST_SIZE];

#pragma DATA_SECTION (OUT_BUF2, ".fileio_data");
uint8_t OUT_BUF2[4*10000];

#if (!HOST_EMULATION)
#define ENABLE_PROFILE 1
volatile long long clr_profile_data[10];
#endif

#define RGB88_GREEN ((0 << 16) | (255 << 8) | (0))
#define RGB88_YELLOW ((255 << 16) | (255 << 8) | (0))
#define RGB88_RED ((255 << 16) | (0 << 8) | (0))
#define RGB88_BLUE ((0 << 16) | (0 << 8) | (255))
#define RGB88_RB ((255 << 16) | (0 << 8) | (255))

int32_t clrTest(sCLR_Config * testcaseParams);

int32_t currStartX = 0;
int32_t currStartY = 0;

int32_t currRoiWidth  = 0;
int32_t currRoiHeight = 0;

int32_t currWidth  = 0;
int32_t currHeight = 0;

#if (!HOST_EMULATION)
void _TSC_enable();
long long _TSC_read();

static void SetMAR()
{


  uint32_t i ;
  /* MAR Reg  Add         Cache able Region
  * MAR 144 (0x01848240h) 9000 0000h - 90FF FFFFh
  * MAR 160 (0x01848280)  A000 0000h - A0FF FFFFh
  */
  uint32_t* MAR = (uint32_t*)0x01848000 ;

  for(i = 144 ;i <= 160 ; i++)
  {
    MAR[i] = 0x1;
  }

  for(i = 128 ;i <= 133 ; i++)
  {
    MAR[i] = 0x1;
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
  L2CFG()  = 2;

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
  L1DCFG() = 3;

  SetMAR() ;
}

#endif

#define ALIGN_T0_32(x) (((x+31)/32)*32)


#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (16*1024)

#define L2SRAMMEM_SIZE (192*1024)

#define DDRNONCACHE_SIZE (16384*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];
TIMemObject memObj_DMEM;


#pragma DATA_SECTION (L2MEM_SCRATCH, ".l2memSect");
uint8_t L2MEM_SCRATCH[L2SRAMMEM_SIZE];
TIMemObject memObj_L2MEM;

//#pragma DATA_SECTION (DDRMEM_NONCACHE, ".ddrnoncacheSect");
//uint8_t DDRMEM_NONCACHE[DDRNONCACHE_SIZE];
//TIMemObject memObj_DDRMEMNC;
#include "ti_draw_utils.h"

#if (HOST_EMULATION)
#define ENABLE_TRACE_IMAGE_DUMP (1)
#else
#define ENABLE_TRACE_IMAGE_DUMP (1)
#endif



#if ENABLE_TRACE_IMAGE_DUMP
uint8_t * tiR;
uint8_t * tiG;
uint8_t * tiB;
uint8_t currColor;
void tb_clr_alloc_traceBuffers(uint32_t imgWidth,uint32_t imgHeight)
{
  tiR = (uint8_t *)malloc(imgWidth*imgHeight);
  tiG = (uint8_t *)malloc(imgWidth*imgHeight);
  tiB = (uint8_t *)malloc(imgWidth*imgHeight);
  currColor = 0;

  if((tiR == NULL) || (tiG == NULL) || (tiB == NULL))
  {
    printf(" Error !!! : Could not allocate memory for trace buffer\n");
  }
}

void tb_clr_free_traceBuffers(void)
{
  if((tiR == NULL) || (tiG == NULL) || (tiB == NULL))
  {
    printf(" Error !!! : Could not free memory for trace buffer\n");
  }
  free(tiR);
  free(tiG);
  free(tiB);
}
void tb_clr_trace_set_color(uint32_t colorIdx)
{
    currColor = colorIdx;
    return;
}

void tb_clr_trace_image(uint32_t * edgeListXy, float * gMag, uint32_t numEdgePoints, uint32_t tileX, uint32_t tileY)
{
  uint32_t i,x,y,size = currWidth * currHeight;
  uint8_t * ptr = tiR;
  if(currColor == 0)
  {
    if((tileX == 0) && (tileY == 0))
    {
      memset(tiR,0,size);
      memset(tiG,0,size);
      memset(tiB,0,size);
    }
    ptr = tiR;
  }
  else
  {
    ptr = tiG;
  }

  for (i = 0; i < numEdgePoints; i++)
  {
      y = ((uint16_t  *)edgeListXy)[2*i]   + currStartY + tileY;
      x = ((uint16_t  *)edgeListXy)[2*i+1] + currStartX + tileX;
      if(gMag == NULL)
      {
        ptr[y*currWidth + x] = 255;
      }
      else
      {
        ptr[y*currWidth + x] = (unsigned char)(gMag[i]);
      }
  }

}


void tb_clr_dump_traceBuffers(const char * fileName, uint16_t width,  uint16_t height)
{
  static int8_t firstFrame = 1;
  TI_FILE * fp_out;
  uint32_t size = width * height;
  uint8_t *y, *u, *v;
  int16_t xmin;
  int16_t ymin;
  int16_t xmax;
  int16_t ymax;

  y = (uint8_t *)trace_buf_y;
  u = (uint8_t *)trace_buf_u;
  v = (uint8_t *)trace_buf_v;

  if(firstFrame)
  {
    fp_out = FOPEN((char *)fileName,"wb+");
    firstFrame = 0;
  }
  else
  {
    fp_out = FOPEN((char *)fileName,"ab");
  }
  if(fp_out == NULL)
  {
    printf("Error Opening trace file\n");
  }

  xmin = currStartX;
  ymin = currStartY;
  xmax = currStartX + currRoiWidth-1;
  ymax = currStartY + currRoiHeight-1;

  xmin = xmin & (~1); 
  ymin = ymin & (~1); 
  xmax = xmax & (~1); 
  ymax = ymax & (~1); 

  if( (xmin >= 0) && (xmin < width) && (xmax >= 0) && (xmax < width) && (ymin >= 0) && (ymin < height) && (ymax >= 0) && (ymax < height))
  {
      APP_drawBoxRGB(tiR,tiG,tiB, RGB88_RED,width,xmin,ymin,xmax,ymax);
  }
  else
  {
    printf("ROI Box is going beyond Image resolution\n");
  }


  APP_convertRGB888toYUV420p(tiR,tiG,tiB,y,u,v,width,height); 

  FWRITE(y,1,size,fp_out);
  FWRITE(u,1,size/4,fp_out);
  FWRITE(v,1,size/4,fp_out);
  FCLOSE(fp_out);

}
#endif






int32_t APP_drawCircles(  const char * inFileName,  const char * OutFileName,  TI_CLR_OutArgs *outArgs, IVISION_OutBufs * outBufs, uint16_t frameIdx, uint16_t width,  uint16_t height, TI_CLR_InArgs* inArgs )
{
#if (ENABLE_TRACE_IMAGE_DUMP)
  TI_FILE * fp_out;
  TI_FILE * fp_in;

  uint32_t size = width * height;

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

  uint32_t bbColor;

  int32_t j;
  static int8_t firstFrame = 1;
  uint16_t row,col;
  uint16_t centerX,centerY,radiusValue;

  if(firstFrame)
  {
    fp_out = FOPEN((char *)OutFileName,"wb+");
    firstFrame = 0;
  }
  else
  {
    fp_out = FOPEN((char *)OutFileName,"ab");
  }
  if(fp_out == NULL)
  {
    return (-1);
  }

  y = (uint8_t *)trace_buf_y;
  u = (uint8_t *)trace_buf_u;
  v = (uint8_t *)trace_buf_v;

  r = (uint8_t *)malloc(size);
  g = (uint8_t *)malloc(size);
  b = (uint8_t *)malloc(size);

  if((y == NULL) || (u == NULL) || (v == NULL) || (r == NULL) || (g == NULL) || (b == NULL))
  {
    return (-1);
  }
  fp_in = FOPEN((char *)inFileName,"rb");
  if(fp_in == NULL)
  {
    return (-1);
  }

  FSEEK(fp_in, ((frameIdx * size*3)/2), SEEK_SET);

  FREAD(y,1,size,fp_in);
  FREAD(u,1,size/2,fp_in);
  FCLOSE(fp_in);
  
  
  APP_convertYUV420sptoRGB888(y,u,r,g,b,width,height);
  
  xmin = currStartX;
  ymin = currStartY;
  xmax = currStartX + currRoiWidth-1;
  ymax = currStartY + currRoiHeight-1;

  xmin = xmin & (~1); 
  ymin = ymin & (~1); 
  xmax = xmax & (~1); 
  ymax = ymax & (~1); 

#if 0
  if( (xmin >= 0) && (xmin < width) && (xmax >= 0) && (xmax < width) && (ymin >= 0) && (ymin < height) && (ymax >= 0) && (ymax < height))
  {
      APP_drawBoxRGB(r,g,b, RGB88_RED,width,xmin,ymin,xmax,ymax);
  }
  else
  {
    printf("ROI Box is going beyond Image resolution\n");
  }
#endif

    TI_CLR_output * lights   = (TI_CLR_output *)outBufs->bufDesc[0]->bufPlanes[0].buf;


    for(j = 0; j < lights->numObjects; j++)
    {    
        if(lights->objDesc[j].objType == TI_CLR_OBJ_RED_TRAFFIC_LIGHT)
        {
          bbColor = RGB88_RED ;
        }
        else
        {
          bbColor = RGB88_GREEN ;
        }
          row=lights->objDesc[j].yPos;
          col=lights->objDesc[j].xPos;
  
         if((col > 5) && (col < width-lights->objDesc[j].objWidth-5) &&
            (row > 5) && (row < (height-lights->objDesc[j].objHeight-5)))
         {
          xmin = col;
          ymin = row;
          xmax = col + lights->objDesc[j].objWidth;
          ymax = row + lights->objDesc[j].objHeight;

          xmin = xmin & (~1); 
          ymin = ymin & (~1); 
          xmax = xmax & (~1); 
          ymax = ymax & (~1); 

          if( (xmin >= 0) && (xmin < width) && (xmax >= 0) && (xmax < width) && (ymin >= 0) && (ymin < height) && (ymax >= 0) && (ymax < height))
          {
            if(inArgs->groupingWindowSize > 48)
            {
              APP_drawBoxRGB(r,g,b, bbColor,width,xmin,ymin,xmax,ymax);
              APP_drawBoxRGB(r,g,b, bbColor,width,xmin-1,ymin-1,xmax+1,ymax+1);
            }
            else
            {
              centerX     = xmin+lights->objDesc[j].objWidth/2;
              centerY     = ymin+lights->objDesc[j].objWidth/2;
              radiusValue = lights->objDesc[j].objWidth/2;
              APP_drawCircle(r,g,b, bbColor,width,centerX,centerY,radiusValue+1);
              APP_drawCircle(r,g,b, bbColor,width,centerX,centerY,radiusValue+2);
              APP_drawCircle(r,g,b, bbColor,width,centerX,centerY,radiusValue+3);
              APP_drawCircle(r,g,b, bbColor,width,centerX,centerY,radiusValue+4);
              APP_drawCircle(r,g,b, bbColor,width,centerX,centerY,radiusValue+5);
            }
          }
          else
          {
            printf("Obj Box is goinf beyond Image resolution\n");
          }
         }
    }

  APP_convertRGB888toYUV420p(r,g,b,y,u,v,width,height); 

  FWRITE(y,1,size,fp_out);
  FWRITE(u,1,size/4,fp_out);
  FWRITE(v,1,size/4,fp_out);


  free(r);
  free(g);
  free(b);

  FCLOSE(fp_out);
#endif

  return 0;
}



int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM  = &memObj_DMEM;
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
      printf("  Could NOT ALLOCATE THE memory requested \n");
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

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs, sCLR_Config * params)
{
  //TIMemHandle memHdl_EXTMEM = &memObj_DDRMEMNC; 
  
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->numPlanes                       = 2;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.x = params[0].startX;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.y = params[0].startY;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width              = params[0].actualImgWidth;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height             = params[0].actualImgHeight;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width     = params[0].roiWidth;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height    = params[0].roiHeight;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].planeType          = 0; // Luma Y
  /* Allocate the buffer in DDR which is non-cacheable */
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf = IMG_BUF1;
  
  if((inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERRORE_MSG();
  }

  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].frameROI.topLeft.x = params[0].startX;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].frameROI.topLeft.y = params[0].startY/2;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].width              = params[0].actualImgWidth;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].height             = params[0].actualImgHeight/2;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].frameROI.width     = params[0].roiWidth;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].frameROI.height    = params[0].roiHeight/2;
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].planeType          = 0; // Luma Y
  /* Allocate the buffer in DDR which is non-cacheable */
  inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].buf = IMG_BUF3;
  
  if((inBufs->bufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[1].buf == NULL))
  {
    PRINT_ERRORE_MSG();
  }

  outBufs->bufDesc[0]->numPlanes                       = 1;
  outBufs->bufDesc[0]->bufPlanes[0].buf                = OUT_BUF1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x = 0;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y = 0;
  outBufs->bufDesc[0]->bufPlanes[0].width              = TI_CLR_OUT_BUFDESC_LIST_SIZE;
  outBufs->bufDesc[0]->bufPlanes[0].height             = 1;


  return IALG_EOK;
}

int32_t TestApp_ReadInBufs(IVISION_InBufs * inBufs,int32_t currFrameNum, char * fileName, uint8_t bufIndex)
{
  int32_t size = inBufs->bufDesc[bufIndex]->bufPlanes[0].width * inBufs->bufDesc[bufIndex]->bufPlanes[0].height; 
  
  TI_FILE * fp;
  fp = FOPEN(fileName, "rb");
  if(fp == NULL)
  {
  printf("Error Opening Input file\n");
   goto Exit;
  }

  FSEEK(fp, currFrameNum*size*1.5, SEEK_SET);
  FREAD(inBufs->bufDesc[bufIndex]->bufPlanes[0].buf,1,size,fp);
  FREAD(inBufs->bufDesc[bufIndex]->bufPlanes[1].buf,1,size/2,fp);

  FCLOSE(fp);

Exit:
    return (0);
}
void sortOutput(TI_CLR_output * lights, uint16_t imPitch);
void sortOutput(TI_CLR_output * lights, uint16_t imPitch)
{
  TI_CLR_objectDescriptor templights;
  uint32_t i,j,lightPos1,lightPos2;
  for(i =0 ;i < lights->numObjects-1; i++)
  {
    for(j = i+1; j < lights->numObjects; j++)
    {
      if(lights->objDesc[i].objType == lights->objDesc[j].objType)
      {
        lightPos1 = lights->objDesc[i].yPos*imPitch + lights->objDesc[i].xPos;
        lightPos2 = lights->objDesc[j].yPos*imPitch + lights->objDesc[j].xPos;
        if(lightPos2 < lightPos1)
        {
          templights = lights->objDesc[i];
          lights->objDesc[i]  = lights->objDesc[j];
          lights->objDesc[j]  = templights;
        }
      }
    }
  }
}
TI_CLR_OutArgs    outArgs;

int32_t clrTest(sCLR_Config * testcaseParams)
{
  int32_t numMemRec;
  uint32_t i, j;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t testcase;
  FILE *fpOut ;
  char *name;
  char *file;
  uint8_t numLights;
  uint16_t row,col;
  
  /*-----------------------------------------------------------------
   Pointer to algorithm instance
   -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
   Algorithm parameters memory in stack
   -----------------------------------------------------------------*/
  TI_CLR_CreateParams   createParams;
  TI_CLR_InArgs      inArgs;
  IVISION_InBufs    inBufs;
  
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[TI_CLR_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[TI_CLR_BUFDESC_IN_TOTAL];

  IVISION_OutBufs   outBufs;
  
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/

  IVISION_BufDesc   outBufDesc[1];
  IVISION_BufDesc   *outBufDescList[1];

#if ENABLE_TRACES
  long long  t0, t1;
#endif

#if (!HOST_EMULATION)
  _TSC_enable();
#endif

  outArgs.iVisionOutArgs.size = sizeof(TI_CLR_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(TI_CLR_InArgs);
  
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
//  TIMemHandle memHdl_EXTMEM;
  
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

//  pExtmem = (uint8_t *)&DDRMEM_NONCACHE;
//  memHdl_EXTMEM = &memObj_DDRMEMNC;
//  TI_CreateMemoryHandle(memHdl_EXTMEM, pExtmem, DDRNONCACHE_SIZE);

  for ( testcase = 0 ; testcase < clr_numTestCases; testcase++ )
  {
    /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;

    inBufs.numBufs   = TI_CLR_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = TI_CLR_BUFDESC_OUT_TOTAL;

    inBufDescList[TI_CLR_BUFDESC_IN_IMAGEBUFFER] = &inBufDesc[TI_CLR_BUFDESC_IN_IMAGEBUFFER];
    
    outBufs.bufDesc = outBufDescList;
    outBufs.numBufs = 1;
    outBufDescList[0] = &outBufDesc[0];

#if ENABLE_TRACE_IMAGE_DUMP
  tb_clr_alloc_traceBuffers(testcaseParams[testcase].maxImageWidth,testcaseParams[testcase].maxImageHeight);
#endif

    /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    createParams.maxImageWidth      = testcaseParams[testcase].maxImageWidth;
    createParams.maxImageHeight     = testcaseParams[testcase].maxImageHeight;
    createParams.maxNumRadius       = testcaseParams[testcase].maxNumRadius ;
    createParams.maxRadius          = TI_CLR_MAX_RADIUS ;
    createParams.maxNumColors       = TI_CLR_MAX_NUM_COLOR_LIGHTS ;
    createParams.minScalingFactor   = TI_CLR_HS_NO_SCALING ;
    createParams.trackingMethod     = testcaseParams[testcase].trackingMethod ;

    createParams.maxRadius = 0;
    for (i =0 ; i < testcaseParams[testcase].numRadius; i++)
    {
      if(testcaseParams[testcase].radius[i] > createParams.maxRadius)
      {
        createParams.maxRadius = testcaseParams[testcase].radius[i];
      }
    }

#if (!HOST_EMULATION)
    //createParams.edma3RmLldHandle   = edma3RmLldHandle;
    createParams.edma3RmLldHandle   = NULL;    
#else
    createParams.edma3RmLldHandle   = NULL;
#endif

    /*-----------------------------------------------------------------
      Query alogorithm memory requirement using standard IALG interface
      -----------------------------------------------------------------*/
    numMemRec = TI_CLR_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = TI_CLR_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);
    
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
    
#if ENABLE_TRACES
    printf("Circular Light Recognition algorithm Create Done\n");
#endif
    /*-----------------------------------------------------------------
      Allocate memory for all the mem records
      Application has to implement the below function
      Refer the example implementation below in this file
      -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
  //printf("numMemRec %d\n",numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }


    /*-----------------------------------------------------------------
      Intialize the algorithm instance with the alocated memory
      and user create parameters
      -----------------------------------------------------------------*/
    status = TI_CLR_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
            memRec,NULL,(IALG_Params *)(&createParams));

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Circular Light Recognition algorithm Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(TI_CLR_InArgs);
    
    inArgs.numColors          = 2;
    inArgs.numRadius          = testcaseParams[testcase].numRadius ;
    inArgs.groupingWindowSize = testcaseParams[testcase].groupingWindowSize ;
    inArgs.morphologyMethod   = testcaseParams[testcase].morphologyMethod ;
    inArgs.lightSelection     = testcaseParams[testcase].lightSelection ;
    inArgs.reserved           = testcaseParams[testcase].useCacheForList ;
    
    inArgs.houghSpaceVotingMethod = TI_CLR_HSV_GRAD_MAGNITUDE;
    for (i =0 ; i < inArgs.numRadius; i++)
    {
      inArgs.radius[i]             = testcaseParams[testcase].radius[i] ;
      inArgs.circleDetectionThr[i] = testcaseParams[testcase].circleDetectionThr[i];
      inArgs.scalingFactor[i]      = testcaseParams[testcase].scalingFactor[i];
    }

    for (i =0 ; i < TI_CLR_MAX_NUM_COLOR_LIGHTS; i++)
    {
      inArgs.lightBrightnessThr[i] = testcaseParams[testcase].lightBrightnessThr[i];
      inArgs.lightColor[i]         = testcaseParams[testcase].lightColor[i];
      inArgs.lightThr1[i]          = testcaseParams[testcase].lightThr1[i];
      inArgs.lightThr2[i]          = testcaseParams[testcase].lightThr2[i];
      inArgs.falseFilterThr[i]     = testcaseParams[testcase].falseFilterThr[i];
    }

    
    TestApp_AllocIOBuffers(&inBufs,&outBufs,&testcaseParams[testcase]);

    name = (char *)malloc(256);
    file = (char *)malloc(256);
    fpOut = fopen((char *)testcaseParams[testcase].outFileName,"w");
    if(fpOut == NULL)
    {
      printf("Unable to open output file\n");
      goto EXIT_LOOP;
    }
    currStartX = testcaseParams[testcase].startX;
    currStartY = testcaseParams[testcase].startY;
    currRoiWidth  = testcaseParams[testcase].roiWidth;
    currRoiHeight = testcaseParams[testcase].roiHeight;
    currWidth  = testcaseParams[testcase].actualImgWidth;
    currHeight = testcaseParams[testcase].actualImgHeight;

    for(frameIdx = testcaseParams[testcase].startFrame; frameIdx < (testcaseParams[testcase].startFrame + testcaseParams[testcase].maxFrames);frameIdx++)
    {
#if ENABLE_TRACES
      printf("Processing started for frame %6d ",frameIdx);
#endif
    TestApp_ReadInBufs(&inBufs,frameIdx,(char *)testcaseParams[testcase].inFileNameYUV, TI_CLR_BUFDESC_IN_IMAGEBUFFER);

#if (!HOST_EMULATION)
#if ENABLE_TRACES
      t0 = _TSC_read();
#endif
#endif
      status = handle->ivision->algProcess((IVISION_Handle)handle,
        &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if (!HOST_EMULATION)
#if ENABLE_PROFILE
      t1 = _TSC_read();
      clr_profile_data[9] = t1-t0;

      for(i =0 ;i < 6; i++)
      {
        if(clr_profile_data[i] < 0)
        {
          clr_profile_data[i] += 0x7FFFFFFF;
        }
      }
      //printf("\n");
      //printf("Cycle Consumed in thresholding is   %4dK\n", clr_profile_data[0]/1000);
      //printf("Cycle Consumed in Dilation          %4dK\n", clr_profile_data[1]/1000);
      //printf("Cycle Consumed in Center Comp       %4dK\n", clr_profile_data[2]/1000);
      //printf("Cycle Consumed in Voting            %4dK\n", clr_profile_data[3]/1000);
      //printf("Cycle Consumed in FAlse Filter      %4dK\n", clr_profile_data[4]/1000);
      //printf("Cycle Consumed in DMA               %4dK\n", clr_profile_data[5]/1000);
      //printf("Cycle Consumed in List              %4dK\n", clr_profile_data[6]/1000);
      //printf("Cycle Consumed in grad              %4dK\n", clr_profile_data[7]/1000);
      //printf("Cycle Consumed in center            %4dK\n", clr_profile_data[8]/1000);
      //printf("Cycles per frame                    %4dK\n", clr_profile_data[9]/1000);

      printf("| Cycles per frame                    | %6dK |", clr_profile_data[9]/1000);


#endif
#endif
     
      if(status != IALG_EOK)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
      printf("Number of edge Points in this Frame | %6d |", (outArgs.numSegPixels[0] + outArgs.numSegPixels[1]));
#if ENABLE_TRACES
      printf("Completed for frame %6d \n",frameIdx);
#endif
 
      fprintf(fpOut,"%8d :: ",frameIdx);
      {
        TI_CLR_output * lights   = (TI_CLR_output *)outBufs.bufDesc[0]->bufPlanes[0].buf;
        numLights = lights->numObjects;
        if(numLights > 1)
        {
          sortOutput(lights,testcaseParams[testcase].actualImgWidth);
        }
        for(j=0;j<numLights;j++)
        {

          row = lights->objDesc[j].yPos = lights->objDesc[j].yPos   + testcaseParams[testcase].startY;
          col = lights->objDesc[j].xPos = lights->objDesc[j].xPos   + testcaseParams[testcase].startX;

          if((row > 2) && (row < testcaseParams[testcase].actualImgHeight-lights->objDesc[j].objHeight-2 ) && (col > 2) && (col < testcaseParams[testcase].actualImgWidth-lights->objDesc[j].objWidth-2))
          {
            if(lights->objDesc[j].objType == TI_CLR_OBJ_RED_TRAFFIC_LIGHT)
            {
              fprintf(fpOut,"R, ");
            }
            else
            {
              fprintf(fpOut,"G, ");
            }
            fprintf(fpOut,"%3d, %3d, ",lights->objDesc[j].objWidth, lights->objDesc[j].objHeight);
            if(lights->objDesc[j].objScore == ((1 << 16)-1))
            {
              fprintf(fpOut,"%8.1f, ", 0);
            }
            else
            {
              fprintf(fpOut,"%8.1f, ",(lights->objDesc[j].objScore/(lights->objDesc[j].objWidth/2)));
            }

            fprintf(fpOut,"%4d, ",row);
            fprintf(fpOut,"%4d, | ",col);
          }
        }

      }
      fprintf(fpOut,"\n");
 
      APP_drawCircles((char *)testcaseParams[testcase].inFileNameYUV, (char *)testcaseParams[testcase].outFileNameYUV, (TI_CLR_OutArgs *)&outArgs, &outBufs, frameIdx,testcaseParams[testcase].actualImgWidth,testcaseParams[testcase].actualImgHeight,(TI_CLR_InArgs*)&inArgs);
#if ENABLE_TRACE_IMAGE_DUMP
      tb_clr_dump_traceBuffers((char *)testcaseParams[testcase].traceNameYUV,testcaseParams[testcase].actualImgWidth,testcaseParams[testcase].actualImgHeight);
#endif


    }

#if ENABLE_TRACE_IMAGE_DUMP
    tb_clr_free_traceBuffers();
#endif
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
  char configFile[CLR_FILE_NAME_SIZE]={0};

#if (!HOST_EMULATION)
  InitCache(); // Deepak
#endif
  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/clr.cfg");
  }

  status = readparamfile(configFile, &gsTokenMap_CLR[0]) ;

  if(status == -1)
  {
#if ENABLE_TRACES
    printf("Parser Failed");
#endif
    return -1 ;
  }
  
#ifdef USE_HOST_FILE_IO
  ti_fileio_init();
#endif

  /* Validate the algorithm */
  status = clrTest(gConfig_CLR);

#if ENABLE_TRACES
printf("end of Clr_tb\n");
#endif

//getch();
#if (!HOST_EMULATION)
  CacheWbInv();
#endif

  return status;
}

void host_file_io_ti_init(){
  int32_t i;
  /* making all packets as available
  */
  for(i = 0; i < HOST_MALLOC_TOT_PACKET; i++){
    SCRATCH_PACKET_VALIDITY[i] = 0x0;
  }
}

void* host_file_io_ti_malloc(int32_t size){

  int32_t  contSize   = 0;
  int32_t  numPackets = 0;
  int32_t  baseIndx   = 0;
  void*    baseAddr;
  int32_t i;

  baseAddr   = &SCRATCH_NON_CACHED[baseIndx][0];

  for(i = 0; i < HOST_MALLOC_TOT_PACKET; i++){

    if(SCRATCH_PACKET_VALIDITY[i] == 0x0){

      contSize += HOST_MALLOC_PACKET_SIZE;
      numPackets++;
    }else{

      contSize   = 0;
      numPackets = 0;
      baseIndx   = i + 1;
      baseAddr   = &SCRATCH_NON_CACHED[baseIndx][0];
    }

    if(contSize >= size)
      break;

  }

  if(i == HOST_MALLOC_TOT_PACKET){
  	#if ENABLE_TRACES
    printf("\n Could not allocate memory for host file i/o \n");
	#endif
    return(0x0);
  }


  for(i = baseIndx; i < baseIndx + numPackets; i++)
    SCRATCH_PACKET_VALIDITY[i] = 1;

  /* Indication for freeing up the packets. At the time of freeing
  * total number of packets to be freed to be known.
  */
  SCRATCH_PACKET_VALIDITY[baseIndx] = numPackets;

  return(baseAddr);
}

void host_file_io_ti_free(void* ptr){

  int32_t numPackets;
  int32_t baseIndx;
  int32_t i;

  for(i = 0; i < HOST_MALLOC_TOT_PACKET; i++){
    if(ptr == &SCRATCH_NON_CACHED[i][0])
      break;
  }

  baseIndx = i;

  if( i >= HOST_MALLOC_TOT_PACKET)
    {
  #if ENABLE_TRACES
    printf("\n Error");
  #endif
  	}
  numPackets = SCRATCH_PACKET_VALIDITY[baseIndx];

  for(i = baseIndx; i < baseIndx + numPackets; i++){
    SCRATCH_PACKET_VALIDITY[i] = 0x0;
  }

  if( i >= HOST_MALLOC_TOT_PACKET)
    {
  #if ENABLE_TRACES
    printf("\n Error");
  #endif
  	}
}


