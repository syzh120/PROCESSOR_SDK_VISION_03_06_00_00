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


/** @file yuv_scalar_tb.c
*
*  @brief  This file contains test code for YUV padding
*
*
*  @date   Mar 2014
*
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

#include "xdais_types.h"
#include "iclahe_ti.h"
#include "clahe_config.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"
#include "edma_utils_memcpy.h"



#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define ENABLE_FILE_IO (1)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

#define Q_FORMATE_SCALE_RATIO                   (12)
#define Q_FORMATE_FRAC_WEIGHT                   (4)

#define EVE_CLAHE_FIXED_Q (1) 

#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)


#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (19*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;

#if VCOP_HOST_EMULATION
#define CALHE_USE_KERNEL_C (0)
void clahe_make_8way_look_up_kernel
  (
  __vptr_uint32 inLuts,      
  __vptr_uint32 outLuts,  
  unsigned short histSize 
  );
void clahe_look_up_and_interpolate_kernel
  (
  __vptr_uint8 inBuf,      
  __vptr_uint8 inLut,      
  __vptr_uint16 xWgtBuf,  
  __vptr_uint16 yWgtBuf,  
  __vptr_uint8 tempBuf,  
  __vptr_uint8 outBuf,  
  unsigned short inWidth,
  unsigned short inHeight, 
  unsigned short inPitch,
  unsigned short tablePitch,
  unsigned short numTab
  );
void vcop_clahe_memset
  (
  __vptr_uint32  inPtr,
  unsigned char  value,
  unsigned short size
  );
void vcop_clahe_histogram_8c_word
  (
  __vptr_uint8  inputImage,
  unsigned short blkWidth,
  unsigned short blkHeight,
  unsigned short inPitch,
  __vptr_uint32 histogram8Copy
  );
void vcop_clahe_histogram_8c_word_sum
  (
  __vptr_uint32  histogram8Copy,
  __vptr_uint32  transposeBuff,
  __vptr_uint32  histogram
  );

void vcop_clahe_clip_hist
  (
  __vptr_uint32  histogram,
  __vptr_uint32  scratch,
  __vptr_uint16  residual,
  __vptr_uint16  clipDist,
  __vptr_uint16  enableResidual,
  unsigned short histSize,
  unsigned short clipValue
  );
void vcop_clahe_generate_lut
  (
  __vptr_uint32  histogram,
  __vptr_uint8   lut,
  unsigned short  scaleValue,
  unsigned short  histSize,
  unsigned short  clipDist,
  unsigned short  residual,
  unsigned short  ebaleResidual
  );

#endif

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
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
  TIMemHandle memHdl_DMEM = &memObj_DMEM;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space == IALG_DARAM0) {
      TI_ResetMemoryHandle(memHdl_DMEM);
    }else {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int test_clahe_ivision( uint8_t * inDataPtr, uint8_t * inLutPtr, uint8_t * outDataPtr, uint8_t * outLutPtr, uint8_t * refDataPtr)
{
  int i=0,j,x,y,failed=0;

  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status,maxdiff,mindiff,diff;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  CLAHE_TI_CreateParams  createParams;

  CLAHE_TI_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[2];
  IVISION_BufDesc   outBufDesc[2];
  IVISION_BufDesc   *inBufDescList[2];

  CLAHE_TI_outArgs            outArgs;
  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[2];
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(CLAHE_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.maxWidth                      = gParams.imWidth    ;
  createParams.maxHeight                     = gParams.imHeight   ;
  createParams.tileWidth                     = gParams.tileWidth;
  createParams.tileHeight                    = gParams.tileHeight;


  numMemRec = CLAHE_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = CLAHE_TI_VISION_FXNS.ialg.algAlloc(
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
  status = CLAHE_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  handle = (IM_Fxns *) memRec[0].base;
  profiler_end_print(0);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Done\n");
#endif



  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = 2;
  outBufs.numBufs  = 2;

  inBufDescList[0]     = &inBufDesc[0];
  outBufDescList[0]    = &outBufDesc[0];

  inBufDesc[0].numPlanes                          = 1;
  inBufDesc[0].bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufDesc[0].bufPlanes[0].frameROI.topLeft.y    = 0;

  inBufDesc[0].bufPlanes[0].width                 = gParams.imWidth;
  inBufDesc[0].bufPlanes[0].height                = gParams.imHeight;
  inBufDesc[0].bufPlanes[0].frameROI.width        = gParams.imWidth;
  inBufDesc[0].bufPlanes[0].frameROI.height       = gParams.imHeight;

  inBufDesc[0].bufPlanes[0].buf = (uint8_t * )inDataPtr ;


  outBufDesc[0].numPlanes                          = 1;
  outBufDesc[0].bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufDesc[0].bufPlanes[0].frameROI.topLeft.y    = 0;

  outBufDesc[0].bufPlanes[0].width                 = gParams.imWidth;
  outBufDesc[0].bufPlanes[0].height                = gParams.imHeight;
  outBufDesc[0].bufPlanes[0].frameROI.width        = gParams.imWidth;
  outBufDesc[0].bufPlanes[0].frameROI.height       = gParams.imHeight;

  outBufDesc[0].bufPlanes[0].buf = (uint8_t * )outDataPtr ;

  inBufDescList[1]     = &inBufDesc[1];
  outBufDescList[1]    = &outBufDesc[1];

  inBufDesc[1].numPlanes                          = 1;           
  inBufDesc[1].bufPlanes[0].buf = (uint8_t * )inLutPtr ;


  outBufDesc[1].numPlanes                          = 1;           
  outBufDesc[1].bufPlanes[0].buf = (uint8_t * )outLutPtr ;


  outArgs.iVisionOutArgs.size       = sizeof(CLAHE_TI_outArgs);

  inArgs.iVisionInArgs.size         = sizeof(CLAHE_TI_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.clipLimit = gParams.clipLimit;



  profiler_start();
  status = handle->ivision->algProcess((IVISION_Handle)handle,
    &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
  profiler_end_print(1);

  failed = 0;


  for(y = 0; y < gParams.imHeight; y++)
  {
    for(x = 0; x < gParams.imWidth; x++)
    {
      if(outDataPtr[y*gParams.imWidth+x] != refDataPtr[y*gParams.imWidth+x])
      {

        failed |= 1;
        break;
      }
    }
    if(failed)
    {
      break;
    }
  } 
  if(failed != 0)
  {
    printf("EVE CLAHE falied \n");
  }
  else
  {
    printf("EVE CLAHE Passed \n");
  }


  for(x = 0; x < (256*(gParams.imWidth*gParams.imHeight)/(gParams.tileWidth*gParams.tileHeight)); x++)
  {
    if(inLutPtr[x] != outLutPtr[x])
    {

      failed |= 2;
      break;
    }
  }
  if((failed&2) != 0)
  {
    printf("EVE LUT falied \n");
  }
  else
  {
    printf("EVE LUT Passed \n");
  }
  if(failed)
  {
    maxdiff = 0;
    mindiff = 0;
    for(i = 0; i < gParams.imHeight; i++)
    {
      for(j = 0; j < gParams.imWidth; j++)
      {
        diff = (int32_t)outDataPtr[i*gParams.imWidth + j] - (int32_t)refDataPtr[i*gParams.imWidth + j];
        if(diff > maxdiff)
        {
          maxdiff = diff;
        }
        if(diff < mindiff)
        {
          mindiff = diff;
        }
      }
    }

    printf("Min and Max diff in EVE Version: %5d %5d  \n",mindiff,maxdiff);
  }

  profiler_printStatus(failed);
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


  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif
EXIT_LOOP:
  return failed;
}
#if (VCOP_HOST_EMULATION)

void clahe_look_up_and_interpolate_kernel_cn
  (
  uint8_t  * inBuf,      
  uint8_t  * inLut,      
  uint16_t * xWgtBuf,  
  uint16_t * yWgtBuf,  
  uint8_t  * tempBuf,  
  uint8_t  * outBuf,  
  unsigned short inWidth,
  unsigned short inHeight, 
  unsigned short inPitch,
  unsigned short tablePitch,
  unsigned short numTab
  );
void vcop_clahe_generate_lut_cn
(
    uint32_t *  histogram,
    uint8_t *   lut,
    unsigned short  scaleValue,
    unsigned short  histSize,
    unsigned short  clipDist,
    unsigned short  residual,
    unsigned short  ebaleResidual
);
void vcop_clahe_clip_hist_cn
(
    uint32_t *  histogram,
    uint32_t *  scratch,
    uint16_t *  residual,
    uint16_t *  clipDist,
    uint16_t *  enableResidual,
    unsigned short histSize,
    unsigned short clipValue
);
void vcop_clahe_histogram_cn
(
    uint8_t  *  inputImage,
    unsigned short blkWidth,
    unsigned short blkHeight,
    unsigned short inPitch,
    uint32_t  * histogram
);

int test_clahe_natc( uint8_t * inDataPtr, uint8_t * inLutPtr, uint8_t * outDataPtr, uint8_t * outLutPtr, uint16_t imWidth, uint16_t imHeight, uint16_t imPitch, uint16_t tileWidth, uint16_t tileHeight, uint16_t clipLimit)
{
  int32_t i,j,k,l,m,n,tx1,tx2,ty1,ty2,maxdiff,mindiff,diff;

  uint16_t txf0,tyf0,txf1,tyf1,out0,out1;
  uint32_t scratch[8];
  uint16_t VclipDist;
  uint16_t VclipResidual;
  uint16_t ebaleResidual;

  uint16_t * xWgtPtr;
  uint16_t * yWgtPtr;
  uint16_t * xWgtPtr0;
  uint16_t * yWgtPtr0;
  uint16_t * xWgtPtr1;
  uint16_t * yWgtPtr1;
  uint8_t * tileInMem;
  uint8_t * tiletempMem;
  uint8_t * tileOutMem;
  uint8_t * lutPtr0;
  uint8_t * lutPtr1;
  uint8_t * lutPtr2;
  uint16_t txf,tyf;
  uint32_t sum,out;
  uint32_t * histPtr2;
  uint32_t * histPtr1;
  uint32_t * histPtrTemp;
  uint32_t subTileOffset;

  uint32_t tileX, tileY, subTileX, subTileY, tileXIdx, tileYIdx, subTileXIdx, subTileYIdx,clipped,redistBatch,residual;
  uint32_t subTileWidth,subTileHeigt;
  uint32_t histSize, clipValue;
  uint16_t lutScale;

  subTileWidth = tileWidth >> 1;
  subTileHeigt = tileHeight >> 1;
  histSize = 256;  
  clipValue   = ((tileWidth*tileHeight)*clipLimit)/histSize;
  lutScale = ((histSize - 1)*(0xFFFFU)) / (tileWidth*tileHeight);


  xWgtPtr0    =  (uint16_t *)malloc(subTileWidth*sizeof(uint16_t)*2);
  yWgtPtr0    =  (uint16_t *)malloc(subTileHeigt*sizeof(uint16_t)*2);
  xWgtPtr1    =  (uint16_t *)malloc(subTileWidth*sizeof(uint16_t)*2);
  yWgtPtr1    =  (uint16_t *)malloc(subTileHeigt*sizeof(uint16_t)*2);
  histPtr1    =  (uint32_t *)malloc(8*sizeof(uint32_t)*histSize);
  histPtr2    =  (uint32_t *)malloc(sizeof(uint32_t)*histSize);
  histPtrTemp =  (uint32_t *)malloc(8*sizeof(uint32_t)*((histSize/8)*9));
  lutPtr0     =  (uint8_t *)malloc(4*256*sizeof(uint8_t));
  lutPtr1     =  (uint8_t *)malloc(4*8*256*sizeof(uint8_t));
  lutPtr2     =  (uint8_t *)malloc(256*sizeof(uint8_t));
  tileInMem   =  (uint8_t *)malloc(subTileWidth*subTileHeigt*sizeof(uint8_t));
  tileOutMem  =  (uint8_t *)malloc(subTileWidth*subTileHeigt*sizeof(uint8_t));
  tiletempMem =  (uint8_t *)malloc(4*subTileWidth*subTileHeigt*sizeof(uint8_t));

  if( (xWgtPtr0 == NULL)  || (yWgtPtr0 == NULL)  || (xWgtPtr1 == NULL)  || (yWgtPtr1 == NULL) 
    || (histPtr1 == NULL) || (histPtrTemp == NULL) || (histPtr2 == NULL)
    || (tileInMem == NULL) || (tileOutMem == NULL) || (tiletempMem == NULL)
    || (lutPtr0 == NULL) || (lutPtr1 == NULL) || (lutPtr2 == NULL))
  {
    return -1;
  }


  for(i = 0; i < subTileWidth; i++)
  {
    txf = (i + subTileWidth);
    txf = (txf * 0xFFFFU)  / tileWidth;
    xWgtPtr0[2*i] = (0xFFFFU - txf);
    xWgtPtr0[2*i+1] = txf;

    txf = (i);
    txf = (txf * 0xFFFFU) / tileWidth;
    xWgtPtr1[2*i] = (0xFFFFU - txf);
    xWgtPtr1[2*i+1] = txf;

  }
  for(i = 0; i < subTileHeigt; i++)
  {
    tyf = (i + subTileHeigt);
    tyf = (tyf * 0xFFFFU) / tileHeight;
    yWgtPtr0[2*i] = (0xFFFFU - tyf);
    yWgtPtr0[2*i+1] = tyf;

    tyf = (i);
    tyf = (tyf * 0xFFFFU) / tileHeight;
    yWgtPtr1[2*i] = (0xFFFFU - tyf);
    yWgtPtr1[2*i+1] = tyf;
  }


  tileX = imWidth/tileWidth;
  tileY = imHeight/tileHeight;

  for(i = 0; i < tileY; i++)
  {
    for(j = 0; j < tileX; j++)
    {

      for(k = 0; k < 4; k++)
      {

        if(k == 3)
        {
          tx2 = j+1;
          ty2 = i+1;
          xWgtPtr = xWgtPtr1;
          yWgtPtr = yWgtPtr1;
          subTileOffset = subTileHeigt * imPitch + subTileWidth;

        }
        else if(k == 2)
        {
          tx2 = j;
          ty2 = i+1;
          xWgtPtr = xWgtPtr0;
          yWgtPtr = yWgtPtr1;
          subTileOffset = subTileHeigt * imPitch;
        }
        else if(k == 1)
        {
          tx2 = j+1;
          ty2 = i;
          xWgtPtr = xWgtPtr1;
          yWgtPtr = yWgtPtr0;
          subTileOffset =  subTileWidth;
        }
        else
        {
          tx2 = j;
          ty2 = i;
          xWgtPtr = xWgtPtr0;
          yWgtPtr = yWgtPtr0;
          subTileOffset = 0;
        }

        tx1 = tx2 - 1;
        ty1 = ty2 - 1;

        tx1 = tx1 < 0 ? 0 : tx1;
        tx2 = tx2 > (tileX-1) ? (tileX-1) : tx2;

        ty1 = ty1 < 0 ? 0 : ty1;
        ty2 = ty2 > (tileY-1) ? (tileY-1) : ty2;


        EDMA_UTILS_memcpy2D((void *)lutPtr0,  (const void  *)(inLutPtr + (ty1*tileX + tx1)*histSize), histSize, 1,  0,  0);
        EDMA_UTILS_memcpy2D((void *)(lutPtr0 +  1*histSize),  (const void  *)(inLutPtr + (ty1*tileX + tx2)*histSize), histSize, 1,  0,  0);
        EDMA_UTILS_memcpy2D((void *)(lutPtr0 +  2*histSize),  (const void  *)(inLutPtr + (ty2*tileX + tx1)*histSize), histSize, 1,  0,  0);
        EDMA_UTILS_memcpy2D((void *)(lutPtr0 +  3*histSize),  (const void  *)(inLutPtr + (ty2*tileX + tx2)*histSize), histSize, 1,  0,  0);
        EDMA_UTILS_memcpy2D((void *)tileInMem, 
          (const void  *)((uint8_t *)inDataPtr + (i*tileHeight) * imPitch + j*tileWidth + subTileOffset), 
          (uint16_t)     subTileWidth, 
          (uint16_t)     subTileHeigt, 
          (int16_t)      subTileWidth, 
          (int16_t)      imPitch);




#if CALHE_USE_KERNEL_C
        clahe_make_8way_look_up_kernel((uint32_t*)lutPtr0, (uint32_t*)lutPtr1, histSize);
        clahe_look_up_and_interpolate_kernel(tileInMem,lutPtr1,xWgtPtr,yWgtPtr,tiletempMem,tileOutMem,subTileWidth,subTileHeigt,subTileWidth,histSize*8,4);
        if(k == 0)
        {
          vcop_clahe_memset(histPtr1,0, 4*histSize*8);
        }
        vcop_clahe_histogram_8c_word(tileInMem,subTileWidth,subTileHeigt,subTileWidth,histPtr1);

        if(k == 3)
        {
          vcop_clahe_histogram_8c_word_sum(histPtr1,histPtrTemp,histPtr2);
          vcop_clahe_clip_hist(histPtr2,scratch,&VclipResidual,&VclipDist,&ebaleResidual,histSize,clipValue);
          VclipResidual++;
          vcop_clahe_generate_lut(histPtr2,lutPtr2,lutScale,histSize,VclipDist,VclipResidual,ebaleResidual);
        }
#else
        clahe_look_up_and_interpolate_kernel_cn(tileInMem,lutPtr0,xWgtPtr,yWgtPtr,tiletempMem,tileOutMem,subTileWidth,subTileHeigt,subTileWidth,histSize,4);
        if(k == 0)
        {
          memset(histPtr2,0, 4*histSize);
        }
        vcop_clahe_histogram_cn(tileInMem,subTileWidth,subTileHeigt,subTileWidth,histPtr2);

        if(k == 3)
        {
          vcop_clahe_clip_hist_cn(histPtr2,scratch,&VclipResidual,&VclipDist,&ebaleResidual,histSize,clipValue);
          VclipResidual++;
          vcop_clahe_generate_lut_cn(histPtr2,lutPtr2,lutScale,histSize,VclipDist,VclipResidual,ebaleResidual);
        }
#endif

        EDMA_UTILS_memcpy2D((void *)((uint8_t *)outDataPtr + (i*tileHeight) * imPitch + j*tileWidth + subTileOffset), 
          (const void  *)(tileOutMem), 
          (uint16_t)     subTileWidth, 
          (uint16_t)     subTileHeigt, 
          (int16_t)      imPitch, 
          (int16_t)      subTileWidth);

        if(k == 3)
        {
          EDMA_UTILS_memcpy2D((void *)(outLutPtr + (i*tileX + j)*histSize),  (const void  *)(lutPtr2), histSize, 1,  0,  0);
        }

      }

    }
  }

  free(xWgtPtr0   );
  free(yWgtPtr0   );
  free(xWgtPtr1   );
  free(yWgtPtr1   );
  free(histPtr1   );
  free(histPtr2   );
  free(histPtrTemp);
  free(lutPtr0    );
  free(lutPtr1    );
  free(lutPtr2    );
  free(tileInMem  );
  free(tileOutMem );
  free(tiletempMem);

}
#endif

int test_clahe_ref_fp(void)
{
  FILE * fp;

  uint8_t * inPtr;
  uint8_t * outEVEPtr;
  uint8_t * outNatcPtr;
  uint8_t * refPtr;
  uint8_t * lutPtrExt0;
  uint8_t * lutPtrEVE;
  uint8_t * lutPtrNtac;
  uint32_t * histPtr;

  uint8_t * tileLut;
  uint8_t * srcPtr;

  int32_t i,j,k,l;
  uint32_t tileX, tileY, clipped,redistBatch,residual;

  uint32_t histSize, clipValue;

#if VCOP_HOST_EMULATION
  int32_t maxdiff,mindiff,diff,failed,x,y;
#endif

#if EVE_CLAHE_FIXED_Q
  uint16_t lutScale;
  uint32_t sum;
#else
  float lutScale, sum;
#endif

  printf("Image Width : %d\n" ,(char *)gParams.imWidth);
  printf("Image Height: %d\n" ,(char *)gParams.imHeight);
  printf("Tile Width  : %d\n" ,(char *)gParams.tileWidth);
  printf("Tile Height : %d\n" ,(char *)gParams.tileHeight);
  printf("Clip Limit  : %d\n" ,(char *)gParams.clipLimit);
  printf("In Image    : %s\n" ,(char *)gParams.inImage);
  printf("Out Image   : %s\n" ,(char *)gParams.outImage);

  fp = fopen((char *)gParams.inImage, "rb");
  if(fp == NULL)
  {
    PRINT_ERRORE_MSG() ;
    return -1;
  }
  inPtr        = (uint8_t *)malloc(gParams.imWidth*gParams.imHeight);
  refPtr       = (uint8_t *)malloc(gParams.imWidth*gParams.imHeight);
  outNatcPtr   = (uint8_t *)malloc(gParams.imWidth*gParams.imHeight);
  outEVEPtr    = (uint8_t *)malloc(gParams.imWidth*gParams.imHeight);

  if((inPtr == NULL)  || (refPtr == NULL)  || (outNatcPtr == NULL) || (outEVEPtr == NULL))
  {
    PRINT_ERRORE_MSG() ;
    return -1;
  }


  fread(inPtr,1,gParams.imWidth*gParams.imHeight,fp);
  fclose(fp);

  tileX = gParams.imWidth/gParams.tileWidth;
  tileY = gParams.imHeight/gParams.tileHeight;
  histSize = 256;

  lutPtrExt0 = (uint8_t *)malloc(tileX*tileY*histSize);
  lutPtrNtac = (uint8_t *)malloc(tileX*tileY*histSize);
  lutPtrEVE  = (uint8_t *)malloc(tileX*tileY*histSize);
  clipValue   = ((gParams.tileWidth*gParams.tileHeight)*gParams.clipLimit)/histSize;
#if EVE_CLAHE_FIXED_Q
  lutScale = ((histSize - 1)*(0xFFFFU)) / (gParams.tileWidth*gParams.tileHeight);
#else
  lutScale = (float(histSize - 1)) / (gParams.tileWidth*gParams.tileHeight);
#endif
#if 1
  histPtr = (uint32_t *)malloc(sizeof(uint32_t)*histSize);
  if((histPtr == NULL))
  {
    PRINT_ERRORE_MSG() ;
    return -1;
  }
  for(i = 0; i < tileY; i++)
  {
    for(j = 0; j < tileX; j++)
    {
      memset(histPtr,0,sizeof(uint32_t)*histSize);

      srcPtr = inPtr + i*gParams.tileHeight*gParams.imWidth + j*gParams.tileWidth;

      for(k = 0; k < gParams.tileHeight; k++)
      {
        for(l = 0; l < gParams.tileWidth; l++)
        {
          histPtr[srcPtr[k*gParams.imWidth+l]]++;
        }
      }
      clipped = 0;
      for(k = 0; k < histSize; k++)
      {
        if(histPtr[k] > clipValue)
        {
          clipped += histPtr[k] - clipValue;
          histPtr[k]  = clipValue;
        }
      }

      redistBatch = clipped / histSize;

      for(k = 0; k < histSize; k++)
      {
        histPtr[k] += redistBatch;
      }
      residual = clipped - redistBatch * histSize;
      for(k = 0; k < residual; k++)
      {
        histPtr[k]++;
      }

      tileLut = lutPtrExt0 + (i*tileX + j)*histSize;
      sum = 0;
      for (k = 0; k < histSize; ++k)
      {
        sum += histPtr[k];
#if EVE_CLAHE_FIXED_Q
        tileLut[k] = (sum * lutScale + (1 << 15)) >> 16; 
#else
        tileLut[k] = ((uint32_t)(sum * lutScale + 0.5)) > 255 ? 255 : (uint8_t)(sum * lutScale + 0.5);
#endif
      }

    }
  }
  free(histPtr );
#else
  for(j = 0; j < tileY*tileX; j++)
  {
      tileLut = lutPtrExt0 + j*histSize;
      for (k = 0; k < histSize; ++k)
      {
        tileLut[k] = k;
      }

    }
#endif
  
  fp = fopen((char *)gParams.refImage, "rb");
  if(fp == NULL)
  {
    PRINT_ERRORE_MSG() ;
    return -1;
  }
  fread(refPtr,1,gParams.imWidth*gParams.imHeight,fp);
  fclose(fp);


 test_clahe_ivision(inPtr, lutPtrExt0, outEVEPtr, lutPtrEVE, refPtr);
  
#if VCOP_HOST_EMULATION
  failed = test_clahe_natc(inPtr, lutPtrExt0, outNatcPtr, lutPtrNtac, gParams.imWidth, gParams.imHeight, gParams.imWidth,gParams.tileWidth,gParams.tileHeight,gParams.clipLimit);
  
  for(y = 0; y < gParams.imHeight; y++)
  {
    for(x = 0; x < gParams.imWidth; x++)
    {
      if(outNatcPtr[y*gParams.imWidth+x] != refPtr[y*gParams.imWidth+x])
      {

        failed |= 1;
        break;
      }
    }
    if(failed)
    {
      break;
    }
  } 
  if(failed != 0)
  {
    printf("NATC CLAHE falied \n");
  }
  else
  {
    printf("NATC CLAHE Passed \n");
  }


  for(x = 0; x < (256*(gParams.imWidth*gParams.imHeight)/(gParams.tileWidth*gParams.tileHeight)); x++)
  {
    if(lutPtrExt0[x] != lutPtrNtac[x])
    {

      failed |= 2;
      break;
    }
  }
  if((failed&2) != 0)
  {
    printf("NATC LUT falied \n");
  }
  else
  {
    printf("NATC LUT Passed \n");
  }
  if(failed)
  {
    maxdiff = 0;
    mindiff = 0;
    for(i = 0; i < gParams.imHeight; i++)
    {
      for(j = 0; j < gParams.imWidth; j++)
      {
        diff = (int32_t)outNatcPtr[i*gParams.imWidth + j] - (int32_t)refPtr[i*gParams.imWidth + j];
        if(diff > maxdiff)
        {
          maxdiff = diff;
        }
        if(diff < mindiff)
        {
          mindiff = diff;
        }
      }
    }

    printf("Min and Max diff in NATC Version: %5d %5d  \n",mindiff,maxdiff);
  }

#endif


  fp = fopen((char *)gParams.outImage, "wb+");
  if(fp == NULL)
  {
    PRINT_ERRORE_MSG() ;
    return -1;
  }
  fwrite(outEVEPtr,1,gParams.imWidth*gParams.imHeight,fp);
  fclose(fp);

  free(inPtr);
  free(refPtr);
  free(lutPtrExt0 );
  free(lutPtrNtac );
  free(outNatcPtr );
  free(outEVEPtr );
  free(lutPtrEVE );
  
  return 0;
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
  report_printAppletInfo((int8_t *)"CLAHE_TI_VISION");

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s  \n",CONFIG_LIST_FILE_NAME);
    return(0);
  }

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
      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)params->testCaseDesc,params->performanceTestcase);
      printparams(&gsTokenMap_yuv_scalar[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(&gParams),sizeof(yuv_scalar_config)) ;

      /* Validate the applet */
      status = test_clahe_ref_fp();

    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }

  fclose(fp);
  return (0);
}
