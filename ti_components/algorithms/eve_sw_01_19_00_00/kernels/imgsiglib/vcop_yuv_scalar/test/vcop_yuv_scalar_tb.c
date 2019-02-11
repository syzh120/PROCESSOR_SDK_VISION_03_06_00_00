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


/** @file vcop_yuv_scalar_tb.c
*
*  @brief  This file contains test code for YUV scaling
*
*
*/
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>


#include "vcop_yuv_scalar_config.h"
#include "eve_profile.h"
#include "ti_file_io.h"
#include "vcop_yuv_scalar_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_yuv_scalar_kernel.k"
#else
#include "vcop_yuv_scalar_kernel.h"
#endif

#define Q_FORMATE_SCALE_RATIO                   (12)
#define Q_FORMATE_FRAC_WEIGHT                   (4)

#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '  '))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int32_t TestApp_ReadInBufs(uint8_t * ptr,uint8_t * ptrC, int32_t currFrameNum, char * fileName)
{
  int32_t lumaSize   = gParams.imWidth * gParams.imHeight ;
  int32_t ChromaSize = lumaSize/2;

  if(strcmp((const char *)gParams.inputSrc, "RND_PTRN")==0)
  {
    int32_t i;
    srand(gParams.seedForRND);
    for(i = 0; i < lumaSize; i++)
    {
      ptr[i] = rand() & 0XFF;
    }
    for(i = 0; i < ChromaSize; i++)
    {
      ptrC[i] = rand() & 0XFF;
    }
  }
  else if(strcmp((const char *)gParams.inputSrc, "BIN_PTRN")==0)
  {
    TI_FILE * fp;
    fp = fopen(fileName, "rb");
    fseek(fp, currFrameNum*(lumaSize+ChromaSize), SEEK_SET);
    fread(ptr, 1,lumaSize,fp);
    fread(ptrC,1,ChromaSize,fp);
    fclose(fp);
 }
  return (0);
}


int32_t TestApp_WrtiteOutBufs(uint8_t * ptr, uint8_t * ptrC, char * fileName)
{
  TI_FILE * fp;
  static int firtsWrite = 1;
  int32_t size = gParams.outWidth * gParams.outHeight;
  int32_t retVal;
  if(firtsWrite)
  {
    fp = fopen(fileName, "wb+");
    fclose(fp);
    firtsWrite = 0;
  }
  fp = fopen(fileName, "ab+");
  retVal = fwrite(ptr,1,size,fp);
  if(retVal != size)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  retVal = fwrite(ptrC,1,size/2,fp);
  if(retVal != size/2)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  fclose(fp);
  return (0);
}


void getIndexAndFracParts(uint16_t * indexPtr, uint8_t * fracPtr, uint16_t inSize, uint16_t outSize, uint16_t inblkSize, uint16_t outblkSize, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift)
{

  uint16_t y, srcY, srcY1;
  uint16_t yFracB;
  uint16_t yFracT;
  uint16_t startY0;
  uint16_t LUT_DATA_SIZE = 4;

  for(y = 0; y < outSize; y++)
  {
    srcY = ((y * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    yFracB = srcY - ((srcY >> fpQShift) << fpQShift);
    yFracT = (1 << fpQShift) - yFracB;
    srcY   = (srcY >> fpQShift);
    srcY1  = srcY+1;
    srcY   = srcY  >= inSize ? inSize-1 : srcY;
    srcY1  = srcY1 >= inSize ? inSize-1 : srcY1;

    if((y % outblkSize) == 0)
    {
      indexPtr[y]           =  0;      
      startY0               = srcY;
      indexPtr[outSize+y]   =  srcY1-startY0;
    }
    else
    {
      indexPtr[y]              = srcY  - startY0 ;
      indexPtr[outSize + y]    = srcY1 - startY0;
    }
    fracPtr[y]               = yFracT;
    fracPtr[outSize + y]     = yFracB;
  }
  for(y = 0; y < outSize; y++)
  {
      indexPtr[y]           =  (indexPtr[y]*inblkSize)/LUT_DATA_SIZE;      
      indexPtr[outSize+y]   =  (indexPtr[outSize+y]*inblkSize)/LUT_DATA_SIZE; 
  }
}



void memCopy2D
(
unsigned char * dstAddr,
unsigned char * srcAddr,
unsigned short width,
unsigned short height,
short dstLineOffset,
short srcLineOffset
)
{
  int i;
  for(i=0;i<height;i++)
    memcpy(dstAddr + i*dstLineOffset, srcAddr + i*srcLineOffset, width);
}

int test_yuv_scalar(void)
{
  int i=0,x,y,result = 0,failed=0;

  uint8_t blkX;
  uint8_t blkY;

  uint8_t *inLuma   ;
  uint8_t *inChroma ;
  uint8_t *outLuma  ;
  uint8_t *outChroma;
  uint8_t *refLuma  ;
  uint8_t *refChroma;
  uint8_t maxDiffLuma   = 0;
  uint8_t maxDiffChroma = 0;
  uint8_t *eveLuma  ;
  uint8_t *eveChroma;

  uint8_t *inBlkPtr;
  uint8_t *outBlkPtr;
  uint8_t *interBlkPtr;
  uint16_t *horIndexPtr;
  uint16_t *verIndexPtr;
  uint8_t *horFracPtr;
  uint8_t *verFracPtr;
  uint8_t *lutOutPtr;
  uint16_t *horIndexPtrChroma;
  uint8_t  *horFracPtrChroma;

  uint8_t *interOutPtr1 ;
  uint8_t *interOutPtr2 ;
  uint8_t *interBlkPtr1 ;
  uint8_t *outBlkPtr1   ;


  uint8_t *yFracPtr ;
  uint8_t *xFracPtr ;
  uint16_t *xIndexPtr;
  uint16_t *yIndexPtr;
  uint32_t InternalmemReq;

  uint16_t srcY, srcX;
  
  uint16_t blockIncr   = 32;
  uint16_t blockWidth  = 128;
  uint16_t blockHeight = 32;

  uint16_t transposeBlkWidth1 = ALIGN_SIZE(blockHeight,4);
  uint16_t transposeBlkWidth2 = ALIGN_SIZE(blockWidth,4);
  uint16_t transposeBlkWidth3 = ALIGN_SIZE((blockWidth/2),4);

  int32_t inLumaSize    = 2 * gParams.imWidth * gParams.imHeight ;
  int32_t inChromaSize  = inLumaSize/2;
  int32_t outLumaSize   = gParams.outWidth * gParams.outHeight ;
  int32_t outChromaSize = outLumaSize/2;

  uint16_t eveOutWidth    = ALIGN_SIZE(gParams.outWidth,blockWidth);
  uint16_t eveOutHeight   = ALIGN_SIZE(gParams.outHeight,blockHeight);
  uint16_t eveOutHeight1  = ALIGN_SIZE((gParams.outHeight/2),blockHeight);

  uint32_t eveLumaSize   = eveOutWidth*eveOutHeight;
  uint32_t eveChromaSize = eveOutWidth*eveOutHeight1;

  uint16_t inBlockWidthOrg  = ((blockWidth  * gParams.scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 4;
  uint16_t inBlockHeight    = ((blockHeight * gParams.scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 4;


  int16_t  inBlockWidth  = ALIGN_SIZE(inBlockWidthOrg,blockIncr); 
  uint16_t srQShift = Q_FORMATE_SCALE_RATIO;
  uint16_t fpQShift = Q_FORMATE_FRAC_WEIGHT;
  uint16_t *offsetBuf1;
  uint16_t *offsetBuf2;
  uint16_t *offsetBuf3;
  uint16_t LUT_DATA_SIZE = 4;

  if(transposeBlkWidth1 % 8 == 0)
  {
    transposeBlkWidth1 += 4;
  }
  if(transposeBlkWidth2 % 8 == 0)
  {
    transposeBlkWidth2 += 4;
  }  
  if(transposeBlkWidth3 % 8 == 0)
  {
    transposeBlkWidth3 += 4;
  }
  InternalmemReq = inBlockWidth*inBlockHeight;
  InternalmemReq += 2*inBlockWidth*blockHeight;
  InternalmemReq += transposeBlkWidth1*((inBlockWidth+1)/2);
  InternalmemReq += transposeBlkWidth1*((inBlockWidth+1)/2);
  InternalmemReq += inBlockWidth*blockHeight;
  InternalmemReq += blockWidth*blockHeight;
  InternalmemReq += 2*blockHeight;
  InternalmemReq += 2*blockWidth;
  InternalmemReq += 4*blockWidth;
  InternalmemReq += 4*blockHeight;

  inLuma            = (uint8_t *)malloc(inLumaSize);
  inChroma          = (uint8_t *)malloc(inChromaSize);
  outLuma           = (uint8_t *)malloc(outLumaSize);
  outChroma         = (uint8_t *)malloc(outChromaSize);
  refLuma           = (uint8_t *)malloc(outLumaSize);
  refChroma         = (uint8_t *)malloc(outChromaSize);
  eveLuma           = (uint8_t *)malloc(eveLumaSize);
  eveChroma         = (uint8_t *)malloc(eveChromaSize);
  outBlkPtr         = (uint8_t *)malloc(blockWidth*blockHeight);
  interBlkPtr       = (uint8_t *)malloc(inBlockWidth*blockHeight);
  horIndexPtr       = (uint16_t *)malloc(4*eveOutWidth);
  verIndexPtr       = (uint16_t *)malloc(4*eveOutHeight);
  horFracPtr        = (uint8_t *)malloc(2*eveOutWidth);
  verFracPtr        = (uint8_t *)malloc(2*eveOutHeight);
  horIndexPtrChroma = (uint16_t *)malloc(2*eveOutWidth);
  horFracPtrChroma  = (uint8_t *)malloc(eveOutWidth);



#if VCOP_HOST_EMULATION
  inBlkPtr          = (uint8_t  *)malloc(inBlockWidth*inBlockHeight);
  lutOutPtr         = (uint8_t  *)malloc(2*inBlockWidth*blockHeight);
  interOutPtr1      = (uint8_t  *)malloc(transposeBlkWidth1*((inBlockWidth+1)/2));
  interOutPtr2      = (uint8_t  *)malloc(transposeBlkWidth1*((inBlockWidth+1)/2));
  interBlkPtr1      = (uint8_t  *)malloc(inBlockWidth*blockHeight);
  outBlkPtr1        = (uint8_t  *)malloc(blockWidth*blockHeight);
  yFracPtr          = (uint8_t  *)malloc(2*blockHeight);
  xFracPtr          = (uint8_t  *)malloc(2*blockWidth);
  xIndexPtr         = (uint16_t *)malloc(4*blockWidth);
  yIndexPtr         = (uint16_t *)malloc(4*blockHeight);
  offsetBuf1        = (uint16_t *)malloc(8*2);
  offsetBuf2        = (uint16_t *)malloc(8*2);
  offsetBuf3        = (uint16_t *)malloc(8*2); 

#else
  inBlkPtr          = (uint8_t  *)vcop_malloc(VCOP_IBUFLA,inBlockWidth*inBlockHeight);
  lutOutPtr         = (uint8_t  *)vcop_malloc(VCOP_WMEM,2*inBlockWidth*blockHeight);
  interOutPtr1      = (uint8_t  *)vcop_malloc(VCOP_IBUFHA,transposeBlkWidth1*((inBlockWidth+1)/2));
  interOutPtr2      = (uint8_t  *)vcop_malloc(VCOP_IBUFHA,transposeBlkWidth1*((inBlockWidth+1)/2));
  interBlkPtr1      = (uint8_t  *)vcop_malloc(VCOP_IBUFLA,inBlockWidth*blockHeight);
  outBlkPtr1        = (uint8_t  *)vcop_malloc(VCOP_IBUFLA,blockWidth*blockHeight);
  yFracPtr          = (uint8_t  *)vcop_malloc(VCOP_IBUFLA,2*blockHeight);
  xFracPtr          = (uint8_t  *)vcop_malloc(VCOP_IBUFLA,2*blockWidth);
  xIndexPtr         = (uint16_t *)vcop_malloc(VCOP_IBUFHA,4*blockWidth);
  yIndexPtr         = (uint16_t *)vcop_malloc(VCOP_IBUFHA,4*blockHeight);
  offsetBuf1        = (uint16_t *)vcop_malloc(VCOP_WMEM,8*2);
  offsetBuf2        = (uint16_t *)vcop_malloc(VCOP_WMEM,8*2);
  offsetBuf3        = (uint16_t *)vcop_malloc(VCOP_WMEM,8*2);
#endif

  if((eveLuma == NULL) || (eveChroma == NULL) || (inLuma == NULL) || (inChroma == NULL) || (outLuma == NULL) || (outChroma == NULL) || (refLuma == NULL) || (refChroma == NULL))
  {
    printf("Error in allocating memory \n");
    return(-1);
  }

  if((inBlkPtr == NULL) || (outBlkPtr == NULL) || (interBlkPtr == NULL) || (horIndexPtr == NULL) ||(interBlkPtr1 == NULL)  || (outBlkPtr1 == NULL)  || (yFracPtr == NULL) ||  (xFracPtr == NULL) || (xIndexPtr == NULL)  || (yIndexPtr == NULL) ||
    (verIndexPtr == NULL) || (horFracPtr == NULL) || (verFracPtr == NULL) ||  (lutOutPtr == NULL) || (interOutPtr1 == NULL) || (interOutPtr2 == NULL))
  {
    printf("Error in allocating memory \n");
    return(-1);
  }
  if((offsetBuf1 == NULL)||(offsetBuf2 == NULL)||(offsetBuf3 == NULL))
  {
    printf("Error in allocating memory \n");
    return(-1);
  }
  for(i = 0; i < 8; i++)
  {
    offsetBuf1[i] = i*transposeBlkWidth1;
    offsetBuf2[i] = i*transposeBlkWidth2;
    offsetBuf3[i] = i*transposeBlkWidth3;
  }

  /* Genarting all the look up tabl;es required for resizsing in the init time */
  getIndexAndFracParts(horIndexPtr,horFracPtr,gParams.imWidth,eveOutWidth,   blockHeight,   blockWidth,  gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
  getIndexAndFracParts(verIndexPtr,verFracPtr,gParams.imHeight,eveOutHeight, inBlockWidth, blockHeight,  gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
  getIndexAndFracParts(horIndexPtrChroma,horFracPtrChroma,(gParams.imWidth/2),(eveOutWidth/2),   blockHeight*2,   (blockWidth/2),  gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);

  profiler_init();
  profiler_initStack(profiler_getSP());

  for(i = gParams.startFrame; i < gParams.numFrames; i++)
  {
    TestApp_ReadInBufs(inLuma, inChroma, i, (char *)gParams.inImage);
    

   /* Naturl C - version of Luma and chroma resize with out any bit truncation on intermediate data*/
    vcop_resize_cn_y( inLuma,   outLuma, gParams.imWidth, gParams.imHeight, gParams.imWidth, gParams.outWidth, gParams.outHeight, gParams.outWidth, gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
    vcop_resize_cn_uv(inChroma, outChroma, gParams.imWidth, gParams.imHeight, gParams.imWidth, gParams.outWidth, gParams.outHeight, gParams.outWidth, gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
   /* Naturl C - version of Luma and chroma resize with 8 bit intermediate data*/
    vcop_resize_cn_y_s( inLuma,   refLuma, gParams.imWidth, gParams.imHeight, gParams.imWidth, gParams.outWidth, gParams.outHeight, gParams.outWidth, gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
    vcop_resize_cn_uv_s(inChroma, refChroma, gParams.imWidth, gParams.imHeight, gParams.imWidth, gParams.outWidth, gParams.outHeight, gParams.outWidth, gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);

    profiler_start();

    for(y = 0; y < eveOutHeight; y+=blockHeight)
    {
      for(x = 0; x < eveOutWidth; x+=blockWidth)
      {
        srcY = ((y * gParams.scaleRatioQ12) / (1 << (srQShift)));
        srcX = ((x * gParams.scaleRatioQ12) / (1 << (srQShift)));

        memCopy2D(inBlkPtr,inLuma+srcY*gParams.imWidth+srcX,inBlockWidthOrg,inBlockHeight,inBlockWidth,gParams.imWidth);

        memCopy2D(xFracPtr,horFracPtr+x,blockWidth,1,blockWidth,blockWidth);
        memCopy2D(xFracPtr+blockWidth,horFracPtr+eveOutWidth+x,blockWidth,1,blockWidth,blockWidth);
        memCopy2D(yFracPtr,verFracPtr+y,blockHeight,1,blockHeight,blockHeight);
        memCopy2D(yFracPtr+blockHeight,verFracPtr+eveOutHeight+y,blockHeight,1,blockHeight,blockHeight);

        memCopy2D((uint8_t *)(xIndexPtr),(uint8_t *)(horIndexPtr+x),2*blockWidth,1,blockWidth,blockWidth);
        memCopy2D((uint8_t *)(xIndexPtr+blockWidth),(uint8_t *)(horIndexPtr+eveOutWidth+x),2*blockWidth,1,blockWidth,blockWidth);
        memCopy2D((uint8_t *)(yIndexPtr),(uint8_t *)(verIndexPtr+y),2*blockHeight,1,blockHeight,blockHeight);
        memCopy2D((uint8_t *)(yIndexPtr+blockHeight),(uint8_t *)(verIndexPtr+eveOutHeight+y),2*blockHeight,1,blockHeight,blockHeight);

        /* Natural C - version of kernel to match the intermediate output*/
        vcop_scaler_luma_vertical_cn(inBlkPtr,interBlkPtr,yIndexPtr,yFracPtr,inBlockWidth,blockHeight,LUT_DATA_SIZE,fpQShift);
        vcop_scaler_luma_Horizontal_cn(interBlkPtr,outBlkPtr,xIndexPtr,xFracPtr,inBlockWidth,blockWidth,blockHeight,LUT_DATA_SIZE,fpQShift);

        /* VCOP - version of kernel for vertical re-sise*/
        yuv_scalar_pixels_look_up_kernel((uint32_t*)inBlkPtr, (uint16_t*)yIndexPtr, (uint32_t*)lutOutPtr, 2, inBlockWidth, blockHeight);
        yuv_scalar_interpolation_kernel(lutOutPtr,yFracPtr, interOutPtr1, interOutPtr2, offsetBuf1, transposeBlkWidth1, fpQShift, 2, inBlockWidthOrg, inBlockWidth, blockHeight);
        yuv_scalar_luma_copy_kernel((uint32_t*)interBlkPtr1, (uint32_t*)interOutPtr1, (uint32_t*)interOutPtr2, transposeBlkWidth1, inBlockWidthOrg, blockHeight);

        failed = 0;
        for(blkY = 0; blkY < inBlockWidthOrg; blkY++)
        {
          for(blkX = 0; blkX < blockHeight; blkX++)
          {
            if(interBlkPtr1[blkY*blockHeight+blkX] != interBlkPtr[blkX*inBlockWidth+blkY])
            {
              failed |= 1;
            }
          }
        }
        if(failed != 0)
        {
          printf("Luma VCOP version falied during Vertical resize at (y,x): %4d ,%4d\n",y,x);
        }
        /* VCOP - version of kernel for horizontal re-sise*/
        yuv_scalar_pixels_look_up_kernel((uint32_t*)interBlkPtr1, (uint16_t*)xIndexPtr, (uint32_t*)lutOutPtr, 2, blockHeight, blockWidth);
        yuv_scalar_interpolation_kernel(lutOutPtr,xFracPtr, interOutPtr1, interOutPtr2, offsetBuf2,  transposeBlkWidth2, fpQShift, 2, blockHeight, blockHeight, blockWidth);
        yuv_scalar_luma_copy_kernel((uint32_t*)outBlkPtr1, (uint32_t*)interOutPtr1, (uint32_t*)interOutPtr2, transposeBlkWidth2, blockHeight, blockWidth);

        failed = 0;
        for(blkY = 0; blkY < blockHeight; blkY++)
        {
          for(blkX = 0; blkX < blockWidth; blkX++)
          {
            if(outBlkPtr1[blkY*blockWidth+blkX] != outBlkPtr[blkY*blockWidth+blkX])
            {
              failed |= 1;
            }
          }
        } 
        if(failed != 0)
        {
          printf("Luma VCOP version falied during Horizontal resize at (y,x): %4d ,%4d\n",y,x);
        }
        memCopy2D(eveLuma+y*eveOutWidth+x,outBlkPtr1, blockWidth,blockHeight,eveOutWidth,blockWidth);
      }
    }

    for(y = 0; y < eveOutHeight/2; y+=blockHeight)
    {
      for(x = 0; x < eveOutWidth/2; x+=(blockWidth/2))
      {
        srcY = ((y * gParams.scaleRatioQ12) / (1 << (srQShift)));
        srcX = ((x * gParams.scaleRatioQ12) / (1 << (srQShift)));

        memCopy2D(inBlkPtr,inChroma+srcY*gParams.imWidth+srcX*2,inBlockWidthOrg,inBlockHeight,inBlockWidth,gParams.imWidth);

        memCopy2D(xFracPtr,horFracPtrChroma+x,blockWidth,1,blockWidth,blockWidth);
        memCopy2D(xFracPtr+(blockWidth/2),horFracPtrChroma+eveOutWidth/2+x,blockWidth,1,blockWidth,blockWidth);
        memCopy2D(yFracPtr,verFracPtr+y,blockHeight,1,blockHeight,blockHeight);
        memCopy2D(yFracPtr+blockHeight,verFracPtr+eveOutHeight+y,blockHeight,1,blockHeight,blockHeight);

        memCopy2D((uint8_t *)(xIndexPtr),(uint8_t *)(horIndexPtrChroma+x),2*blockWidth,1,blockWidth,blockWidth);
        memCopy2D((uint8_t *)(xIndexPtr+(blockWidth/2)),(uint8_t *)(horIndexPtrChroma+eveOutWidth/2+x),2*blockWidth,1,blockWidth,blockWidth);
        memCopy2D((uint8_t *)(yIndexPtr),(uint8_t *)(verIndexPtr+y),2*blockHeight,1,blockHeight,blockHeight);
        memCopy2D((uint8_t *)(yIndexPtr+blockHeight),(uint8_t *)(verIndexPtr+eveOutHeight+y),2*blockHeight,1,blockHeight,blockHeight);

        /* Natural C - version of kernel to match the intermediate output*/
        vcop_scaler_chroma_vertical_cn(inBlkPtr,interBlkPtr,yIndexPtr,yFracPtr,inBlockWidth,blockHeight,LUT_DATA_SIZE,fpQShift);
        vcop_scaler_chroma_Horizontal_cn(interBlkPtr,outBlkPtr,xIndexPtr,xFracPtr,inBlockWidth,blockWidth,blockHeight,LUT_DATA_SIZE,fpQShift);
 
        /* VCOP - version of kernel for vertical re-sise*/
        yuv_scalar_pixels_look_up_kernel((uint32_t*)inBlkPtr, (uint16_t*)yIndexPtr, (uint32_t*)lutOutPtr, 2, inBlockWidth, blockHeight);
        yuv_scalar_interpolation_kernel(lutOutPtr,yFracPtr, interOutPtr1, interOutPtr2, offsetBuf1, transposeBlkWidth1, fpQShift, 2, inBlockWidthOrg, inBlockWidth, blockHeight);
        yuv_scalar_chroma_copy_kernel(interBlkPtr1, interOutPtr1, interOutPtr2, transposeBlkWidth1, inBlockWidthOrg, blockHeight);

        failed = 0;
        for(blkY = 0; blkY < (inBlockWidthOrg/2); blkY++)
        {
          for(blkX = 0; blkX < blockHeight; blkX++)
          {
            if(interBlkPtr1[blkY*blockHeight*2 + 2*blkX] != interBlkPtr[blkX*inBlockWidth+2*blkY])
            {
              failed |= 1;
            }
            if(interBlkPtr1[blkY*blockHeight*2 + 2*blkX+1] != interBlkPtr[blkX*inBlockWidth+2*blkY+1])
            {
              failed |= 1;
            }          
          }
        }
        if(failed != 0)
        {
          printf("Chroma VCOP version falied during Vertical resize at (y,x): %4d ,%4d\n",y,x);
        }
        /* VCOP - version of kernel for horizontal re-sise*/
        yuv_scalar_pixels_look_up_kernel((uint32_t*)interBlkPtr1, (uint16_t*)xIndexPtr, (uint32_t*)lutOutPtr, 2, blockHeight*2, (blockWidth/2));
        yuv_scalar_interpolation_kernel(lutOutPtr,xFracPtr, interOutPtr1, interOutPtr2, offsetBuf3,  transposeBlkWidth3, fpQShift, 2, blockHeight*2, blockHeight*2, (blockWidth/2));
        yuv_scalar_chroma_copy_kernel(outBlkPtr1, interOutPtr1, interOutPtr2, transposeBlkWidth3, blockHeight*2, (blockWidth/2));

        failed = 0;
        for(blkY = 0; blkY < blockHeight; blkY++)
        {
          for(blkX = 0; blkX < blockWidth; blkX++)
          {
            if(outBlkPtr1[blkY*blockWidth+blkX] != outBlkPtr[blkY*blockWidth+blkX])
            {
              failed |= 1;
            }
          }
        } 
        if(failed != 0)
        {
          printf("Chroma VCOP version falied during Horizontal resize at (y,x): %4d ,%4d\n",y,x);
        }
        memCopy2D(eveChroma+y*eveOutWidth+2*x,outBlkPtr1, blockWidth,blockHeight,eveOutWidth,blockWidth);
      }
    }
    profiler_end_print(1);
    profiler_performanceParam(gParams.outWidth*gParams.outHeight);


    /* Comparing the vcop version result with the generic resizer to find the
    maximum diffrence caused due to bit-truncation of intermediate data*/

    for(y = 0; y < gParams.outHeight; y++)
    {
      for(x = 0; x < gParams.outWidth; x++)
      {
        if(outLuma[y*gParams.outWidth+x] != refLuma[y*gParams.outWidth+x])
        {
          if(maxDiffLuma < abs(outLuma[y*gParams.outWidth+x] - refLuma[y*gParams.outWidth+x]))
          {
            maxDiffLuma = abs(outLuma[y*gParams.outWidth+x] - refLuma[y*gParams.outWidth+x]);
          }
          failed |= 1;
        }
      }
    }   
    for(y = 0; y < gParams.outHeight/2; y++)
    {
      for(x = 0; x < gParams.outWidth; x++)
      {
        if(outChroma[y*gParams.outWidth+x] != refChroma[y*gParams.outWidth+x])
        {
          if(maxDiffChroma < abs(outChroma[y*gParams.outWidth+x] - refChroma[y*gParams.outWidth+x]))
          {
            maxDiffChroma = abs(outChroma[y*gParams.outWidth+x] - refChroma[y*gParams.outWidth+x]);
          }
          failed |= 1;
        }
      }
    }

    if(failed != 0)
    {
      printf("Printf Max Diff : %4d %4d \n",maxDiffLuma,maxDiffChroma);
    }

    failed = 0;

    /* Comparing the vcop version result with the natrural C version */
   for(y = 0; y < gParams.outHeight; y++)
    {
      for(x = 0; x < gParams.outWidth; x++)
      {
        if(eveLuma[y*eveOutWidth+x] != refLuma[y*gParams.outWidth+x])
        {

          failed |= 1;
        }
      }
    } 
    for(y = 0; y < gParams.outHeight/2; y++)
    {
      for(x = 0; x < gParams.outWidth; x++)
      {
        if(eveChroma[y*eveOutWidth+x] != refChroma[y*gParams.outWidth+x])
        {

          failed |= 1;
        }
      }
    }    
    if(failed != 0)
    {
      printf("Block based re-size falied \n");
    }
    else
    {
      printf("Block based re-size Passed \n");
    }
    if(gParams.writeOutput)
    {
      TestApp_WrtiteOutBufs(outLuma,outChroma,(char *)gParams.outImage);
    }
  }

  profiler_printStatus(failed);


  free(inLuma            );
  free(inChroma          );
  free(outLuma           );
  free(outChroma         );
  free(refLuma           );
  free(refChroma         );
  free(eveLuma           );
  free(eveChroma         );
  free(outBlkPtr         );
  free(interBlkPtr       );
  free(horIndexPtr       );
  free(verIndexPtr       );
  free(horFracPtr        );
  free(verFracPtr        );
  free(horIndexPtrChroma );
  free(horFracPtrChroma  );
#if VCOP_HOST_EMULATION
  free(inBlkPtr         ); 
  free(lutOutPtr        ); 
  free(interOutPtr1     ); 
  free(interOutPtr2     ); 
  free(interBlkPtr1     ); 
  free(outBlkPtr1       ); 
  free(yFracPtr         ); 
  free(xFracPtr         ); 
  free(xIndexPtr        ); 
  free(yIndexPtr        ); 
  free(offsetBuf1       ); 
  free(offsetBuf2       ); 
  free(offsetBuf3       ); 

#else
  vcop_free(inBlkPtr     ); 
  vcop_free(lutOutPtr    ); 
  vcop_free(interOutPtr1 ); 
  vcop_free(interOutPtr2 ); 
  vcop_free(interBlkPtr1 ); 
  vcop_free(outBlkPtr1   ); 
  vcop_free(yFracPtr     ); 
  vcop_free(xFracPtr     ); 
  vcop_free(xIndexPtr    ); 
  vcop_free(yIndexPtr    ); 
  vcop_free(offsetBuf1   ); 
  vcop_free(offsetBuf2   ); 
  vcop_free(offsetBuf3   ); 
#endif

  return result;
}

int main(int argc, char *argv[])
{
   FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  yuv_scalar_config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  params = (yuv_scalar_config *)(&gParams);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s  \n",CONFIG_LIST_FILE_NAME);
    return(0);
  }

  CF_profile_init(2, "VCOP_YUV_SCALAR");

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets((char *)params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (char *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf(LinePtr, "%d",&config_cmd);
    sscanf(LinePtr, "%s",params->configParam);
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
      LinePtr = moveToNextElement((char *)params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      status = readparamfile(configFileName, &gsTokenMap_yuv_scalar[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)" ",0);
      printparams(&gsTokenMap_yuv_scalar[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(&gParams),sizeof(yuv_scalar_config)) ;

      /* Validate the applet */
      status = test_yuv_scalar();

      CF_formula_add_test(params->outWidth*params->outHeight, NULL, NULL,  NULL, 0, NULL , 1);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  CF_profile_setMode(2, 1);
  CF_profile_cycle_report(CF_PROFILE_FORMULA_RANGE,"N = Num Out Pixels");

  fclose(fp);
  return (0);
}
