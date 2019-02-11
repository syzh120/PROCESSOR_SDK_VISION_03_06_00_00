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


/** @file fast9_corner_detect_tb.c
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
#include "fast9_corner_detect_config.h"
#include "xdais_types.h"
#include "ifast9_corner_detect_ti.h"


#include "vcop_fast9_cn.h"

#include "vcop_bin_image_to_list_cn.h"
#include "fast9_corner_detect_config.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

#define ENABLE_TRACES 0
#define ENABLE_PROFILE (1U)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")


#define FAST9_CORNER_DETECT_APPLET_BORDER_X 3
#define FAST9_CORNER_DETECT_APPLET_BORDER_Y 3

/*-------------------------------------------------------------------------*/
/* Keep the compute Block width multiple of 8 and don't aloow go below 64  */
/* Keep the compute Block height multiple of 8 and don't aloow go below 32 */
/*-------------------------------------------------------------------------*/
#define FAST9_CORNER_DETECT_APPLET_BLK_WIDTH_MAX  (96 + 2*FAST9_CORNER_DETECT_APPLET_BORDER_X)
#define FAST9_CORNER_DETECT_APPLET_BLK_HEIGHT_MAX (32 + 2*FAST9_CORNER_DETECT_APPLET_BORDER_Y)
#define FAST9_CORNER_DETECT_APPLET_BLK_WIDTH_MIN  (64 + 2*FAST9_CORNER_DETECT_APPLET_BORDER_X)
#define FAST9_CORNER_DETECT_APPLET_BLK_HEIGHT_MIN (16 + 2*FAST9_CORNER_DETECT_APPLET_BORDER_Y)


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define RBRIEF_APPLET_BORDER_X  24
#define RBRIEF_APPLET_BORDER_Y  24
#define DMEM_SIZE (10*1024)

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


/* Find best block width satisfying EDMA and Kernel requirements */
static void bestDimBlkW(uint16_t imgW, uint16_t eImgW, uint16_t k, uint16_t* eBlkWout)
{
  int32_t bwToSatisfyDmaCeil;
  int32_t bwToSatisfyDmaClip;
  uint16_t eBlkW;

  bwToSatisfyDmaCeil = ((eImgW + (k-1))/k);/* Edma Utiltiy requirement */
  bwToSatisfyDmaClip = eImgW / k;/* Edma Utiltiy requirement */

  eBlkW = ((bwToSatisfyDmaCeil + 7)/8) * 8;/* Kernel Requirement : eBlkW should be divisable by 8*/
  if( eBlkW * k <= (imgW - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X))
  {
    goto EXIT;

  }
  eBlkW = ((bwToSatisfyDmaCeil) / 8) * 8;/* Kernel Requirement : eBlkW should be divisable by 8*/

  if( eBlkW * k <= (imgW - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X))
  {
    goto EXIT;
  }

  eBlkW = ((bwToSatisfyDmaClip + 7)/8) * 8;/* Kernel Requirement : eBlkW should be divisable by 8*/
  if( eBlkW * k <= (imgW - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X))
  {
    goto EXIT;

  }
  eBlkW = ((bwToSatisfyDmaClip) / 8) * 8;/* Kernel Requirement : eBlkW should be divisable by 8*/

  if( eBlkW * k <= (imgW - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X))
  {
    goto EXIT;
  }

EXIT:

  *eBlkWout = eBlkW;

  return;

}

/* Find best block height satisfying EDMA requirement */
static void bestDimBlkH(uint16_t imgH, uint16_t eImgH, uint16_t k, uint16_t* eBlkHout)
{
  uint16_t eBlkH;

  eBlkH = ((eImgH + (k-1))/k);/* Edma Utiltiy requirement */

  if( eBlkH * k <= (imgH - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_Y))
  {
    goto EXIT;

  }
  eBlkH = eImgH / k ;/* Edma Utiltiy requirement */
  if( eBlkH * k <= (imgH - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_Y))
  {
    goto EXIT;
  }

EXIT:

  *eBlkHout = eBlkH;

  return;

}


/*------------------------------------------------------------------------------------------*/
/* This function tries to get the active width and height which satisfies below 2 condtiions*/
/* 1. DMA Requirement: activeImagewidth- 6 should be multiple of  blockwidth - 6            */
/* 2. Kernel Requirement: Compute Width to be multiple of 8                                 */
/* block width = compute width + 6                                                          */
/* In order to satisfy this the function starts with max blck width and height and if the   */
/* active width becomes too smaller then reduces the max block width                        */
/*-----------------------------------------------------------------------------------------**/
static void FAST9_CORNER_DETECT_TI_findOptimizeBlockDim(uint16_t imgW,
                                                        uint16_t imgH,
                                                        uint16_t excludeBorderX,
                                                        uint16_t excludeBorderY,
                                                        uint16_t *blockW,
                                                        uint16_t *blockH,
                                                        uint16_t *activeImgWidth,
                                                        uint16_t *activeImgHeight)
{
  int32_t blkW, blkH;
  int32_t maxEffblockWidth, maxEffblockHeight;
  uint16_t eBlkW, eBlkH;
  int32_t eImgW, eImgH;
  int32_t k;
  int32_t effectiveBorderX;
  int32_t effectiveBorderY;
  int32_t delta;
  int32_t mindelta = 100000;
  int32_t eImgWOpt,eImgHOpt;
  int32_t blkWOpt,blkHOpt;

  /* If exclude border X is less than FAST9_CORNER_DETECT_APPLET_BORDER_X then border needed
  will still be FAST9_CORNER_DETECT_APPLET_BORDER_X because that is mandatory border needed by
  FAST9 corner detect algorithm */
  if ( excludeBorderX < FAST9_CORNER_DETECT_APPLET_BORDER_X )
  {
    effectiveBorderX = FAST9_CORNER_DETECT_APPLET_BORDER_X;
  }
  else
  {
    effectiveBorderX = excludeBorderX;
  }

  if ( excludeBorderY < FAST9_CORNER_DETECT_APPLET_BORDER_Y )
  {
    effectiveBorderY = FAST9_CORNER_DETECT_APPLET_BORDER_Y;
  }
  else
  {
    effectiveBorderY = excludeBorderY;
  }

  maxEffblockWidth  = FAST9_CORNER_DETECT_APPLET_BLK_WIDTH_MAX  - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X;
  maxEffblockHeight = FAST9_CORNER_DETECT_APPLET_BLK_HEIGHT_MAX - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_Y;


  eImgW = imgW - 2 * effectiveBorderX;
  eImgH = imgH - 2 * effectiveBorderY;
  /*First find optimal Block Width */
  do
  {
    k = 1;
    /* Find effectiveBlock Width based on current maxEffblockWidth */
    while(1)
    {
      /* Find the best block width which is not going beyond input image Width */
      bestDimBlkW(imgW,eImgW, k ,&eBlkW );
      /* Check if above block width fits into internal memory, if not then try with another factor
      k++ in next iteration */
      if (  eBlkW <= maxEffblockWidth)
      {
        eImgW = eBlkW*k;
        break;
      }
      k++;
    }

    delta = (imgW - 2 * effectiveBorderX) - eImgW;

    /* Keep storing the effective block width found for which delta is minimum, which
    basically indicates that actual image width is closer to effective image width*/
    if ( delta < mindelta )
    {
      eImgWOpt = eBlkW*k;
      blkWOpt  = eBlkW  + 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X;
      mindelta = delta;
    }

    /* reduce maxEffblockWidth by one so as to re-iterate again if delta is greater than zero
    to see if some other k satisfy all the above requriements and still having small delta */
    maxEffblockWidth -= 1 ;
    /* If maxEffblockWidth is smaller than the minimum block width by kernel then break so as to
    pick the effective block width corresponding to the iteration where delta is minimum */
    if( maxEffblockWidth < FAST9_CORNER_DETECT_APPLET_BLK_WIDTH_MIN - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X)
    {
      break ;
    }
  } while (delta > 0 );
  eImgW = eImgWOpt;
  blkW  = blkWOpt;

  /* Now find optimal block height */
  k = 1;
  mindelta = 100000;

  /* Find effectiveBlock height based on current maxEffblockheight*/
  do
  {
    while(1)
    {
      /* Find the best block width which is not going beyond input image Width */
      bestDimBlkH(imgH, eImgH, k, &eBlkH);

      /* Check if above block height fits into internal memory, if not then try with another factor
      k++ in next iteration */
      if (  eBlkH <= maxEffblockHeight)
      {
        eImgH = eBlkH*k;
        break;
      }
      k++;
    }
    delta = (imgH - 2 * effectiveBorderY) - eImgH;

    /* Keep storing the effective block width found for which delta is minimum, which
    basically indicates that actual image width is closer to effective image width*/
    if ( delta < mindelta )
    {
      eImgHOpt = eBlkH*k;
      blkHOpt  = eBlkH  + 2 * FAST9_CORNER_DETECT_APPLET_BORDER_Y;
      mindelta = delta;
    }

    /* reduce maxEffblockHeight by one so as to re-iterate again if delta is greater than zero
    to see if some other k satisfy all the above requriements and still having small delta */
    maxEffblockHeight -= 1 ;
    /* If maxEffblockHeight is smaller than the minimum block height by kernel then break so as to
    pick the effective block height corresponding to the iteration where delta is minimum */
    if( maxEffblockHeight < FAST9_CORNER_DETECT_APPLET_BLK_HEIGHT_MIN - 2 * FAST9_CORNER_DETECT_APPLET_BORDER_Y)
    {
      break ;
    }

  }while(delta > 0);

  eImgH = eImgHOpt;
  blkH  = blkHOpt;

  *blockW = blkW;
  *blockH = blkH;
  *activeImgWidth  = eImgW + 2 * FAST9_CORNER_DETECT_APPLET_BORDER_X;
  *activeImgHeight = eImgH + 2 * FAST9_CORNER_DETECT_APPLET_BORDER_Y;

}


int32_t FAST9CornerDetection_cn(
  uint8_t  *src,
  uint16_t  srcImageWidth,
  uint16_t  srcImageHeight,
  uint16_t  srcBufferPitch,
  uint16_t  excludeBorderX,
  uint16_t  excludeBorderY,
  uint32_t *cornerListXY,
  uint8_t   fast9Th
  )
{
  uint8_t *binImageBuffer, *input ;
  uint32_t list_size = 0, binImageWidth, binImageHeight, binImagePitch ;
  uint16_t dx, dy, dx_binImg, dy_binImg ;
  uint32_t upperLeftXY ;
  uint16_t blockWidth, blockHeight ;
  uint16_t activeImageWidth, activeImageHeight ;
  int16_t  extra_pixels_in_border ;

  FAST9_CORNER_DETECT_TI_findOptimizeBlockDim(srcImageWidth,
                                              srcImageHeight,
                                              excludeBorderX,
                                              excludeBorderY,
                                              &blockWidth,
                                              &blockHeight,
                                              &activeImageWidth,
                                              &activeImageHeight);
  binImageWidth  = activeImageWidth - 6 ;
  binImageHeight = activeImageHeight - 6 ;
  binImagePitch  = binImageWidth ;

  binImageBuffer = (uint8_t *)malloc(binImageWidth*binImageHeight) ;
  if(binImageBuffer == NULL)
  {
    TEST_PRINTF("NatC:: Unable to alocate intermediate buffer\n") ;
    return -1 ;
  }

  dx = (srcImageWidth - activeImageWidth)/2 ;
  dy = (srcImageHeight- activeImageHeight)/2 ;

  input =   src + dy*srcBufferPitch + dx ;
  vcop_fast9_cn(
    input,               // input 1 data pointer (top-left)
    binImageBuffer,
    fast9Th,
    srcBufferPitch,      // pitch, should be atleast compute_width + 6
    activeImageWidth,    // compute width
    activeImageHeight    // compute height
    );

  /* Ensure that the corner list contains points only within the excluded borders specified */
  dx_binImg = 0;
  dy_binImg = 0;

  extra_pixels_in_border = (excludeBorderX - (dx + 3)) ;
  if(extra_pixels_in_border > 0) {
      dx_binImg = ((extra_pixels_in_border + 7)/8)*8 ;
      binImageWidth -= 2*dx_binImg ;
  }

  extra_pixels_in_border = (excludeBorderY - (dy + 3)) ;
  if(extra_pixels_in_border > 0) {
      dy_binImg = extra_pixels_in_border ;
      binImageHeight -= 2*dy_binImg ;
  }

  upperLeftXY = ((dx + dx_binImg + 3) << 16) | ((dy + dy_binImg + 3)) ;

  vcop_bin_image_to_list_cn(
    binImageBuffer + (dy_binImg*binImagePitch + dx_binImg)/8,
    &upperLeftXY,
    cornerListXY,
    &list_size,
    binImageWidth,
    binImageHeight,      // compute height
    binImagePitch,        // pitch, should be atleast compute_width + 6
    0,
    1
    );
  free(binImageBuffer) ;
  return list_size ;

}


int32_t fast9CornerDetectTest(sFast9CornerDetect_Config * testcaseParams)
{
  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i,j;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t fail = 0;
  uint8_t *output;
  uint8_t *refOutput[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t numCornersRef ;
#if (ENABLE_PROFILE)
    uint64_t profile_tsc, profile_create_tsc, profile_sctm;
#endif
  uint32_t sizeOutput;
  uint32_t sizeInput;
  uint32_t numBytes;
  uint32_t testcase;
  uint8_t  levelCnt=0;
  char  filepath[256];
  TI_FILE *fid;
  char  *statusStr = NULL;
  uint8_t * inputPtr;
  float totalActivePixels;
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  FAST9_CORNER_DETECT_TI_CreateParams   createParams;

  FAST9_CORNER_DETECT_TI_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[FAST9_CORNER_DETECT_TI_BUFDESC_IN_TOTAL];

  FAST9_CORNER_DETECT_TI_OutArgs   outArgs;
  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(FAST9_CORNER_DETECT_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(FAST9_CORNER_DETECT_TI_InArgs);
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

  for ( testcase = 0 ; testcase < fast9CornerDetect_numTestCases; testcase++ )
  {


    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = FAST9_CORNER_DETECT_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = FAST9_CORNER_DETECT_TI_BUFDESC_OUT_TOTAL;

    inBufDescList[FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER]     = &inBufDesc;
    outBufDescList[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER]    = &outBufDesc;
    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    createParams.numLevels                        = testcaseParams[testcase].numLevels;
    createParams.excludeBorderX                   = RBRIEF_APPLET_BORDER_X;
    createParams.excludeBorderY                   = RBRIEF_APPLET_BORDER_Y;

    for ( levelCnt = 0 ; levelCnt < testcaseParams[testcase].numLevels ; levelCnt++)
    {
      createParams.visionParams.algParams.size      = sizeof(FAST9_CORNER_DETECT_TI_CreateParams);
      createParams.visionParams.cacheWriteBack      = NULL;
      createParams.imgFrameWidth[levelCnt]          = testcaseParams[testcase].srcImageWidth[levelCnt];
      createParams.imgFrameHeight[levelCnt]         = testcaseParams[testcase].srcImageHeight[levelCnt];
    }

#if (ENABLE_PROFILE)
    profiler_initStack(profiler_getSP());
    profiler_start();
#endif
    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("FAST9 corner detect Applet Create Done\n");
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
    status = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
    /* Set the end point of the timing measurement for the creation process */
    profiler_end_print(0);
    profile_create_tsc = gTest_TI_profileTsc;
#endif
    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("FAST9 corner detect Applet Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size                  = sizeof(FAST9_CORNER_DETECT_TI_InArgs);

    inBufDesc.numPlanes                          = testcaseParams[testcase].numLevels;
    outBufDesc.numPlanes                          = testcaseParams[testcase].numLevels;

    for ( levelCnt = 0; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      inBufDesc.bufPlanes[levelCnt].frameROI.topLeft.x    = testcaseParams[testcase].frameStartX[levelCnt];
      inBufDesc.bufPlanes[levelCnt].frameROI.topLeft.y    = testcaseParams[testcase].frameStartY[levelCnt];
      inBufDesc.bufPlanes[levelCnt].width                 = testcaseParams[testcase].srcImagePitch[levelCnt];
      inBufDesc.bufPlanes[levelCnt].height                = testcaseParams[testcase].srcImageHeight[levelCnt];
      inBufDesc.bufPlanes[levelCnt].frameROI.width        = testcaseParams[testcase].srcImageWidth[levelCnt];
      inBufDesc.bufPlanes[levelCnt].frameROI.height       = testcaseParams[testcase].srcImageHeight[levelCnt];
      inBufDesc.bufPlanes[levelCnt].buf = (uint8_t *)malloc(inBufDesc.bufPlanes[levelCnt].width *
                                                      inBufDesc.bufPlanes[levelCnt].height);
      if(inBufDesc.bufPlanes[levelCnt].buf == NULL)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }

      if ( testcaseParams[testcase].fileBased == 1 )
      {
        sprintf(filepath, "../testvecs/input/%s", testcaseParams[testcase].inImage[levelCnt]);

        fid = FOPEN(filepath,"rb");
        if (fid == NULL) {
          PRINT_ERRORE_MSG();
          TEST_PRINTF("Error, unable to open file %s \n", filepath);
          goto EXIT_LOOP;
        }
        inputPtr = (uint8_t * )inBufDesc.bufPlanes[levelCnt].buf;
        sizeInput = inBufDesc.bufPlanes[levelCnt].frameROI.width *
                      inBufDesc.bufPlanes[levelCnt].frameROI.height;

        numBytes = FREAD(inputPtr, 1, sizeInput, fid);
        assert(numBytes== sizeInput);
        FCLOSE(fid);
      }
      else
      {
        srand(1);
        inputPtr = (uint8_t * )inBufDesc.bufPlanes[levelCnt].buf;
        /* Create Random input data */
        for ( i = 0 ; i < testcaseParams[testcase].srcImageHeight[levelCnt]; i++)
        {
          for ( j = 0; j < testcaseParams[testcase].srcImageWidth[levelCnt]; j++)
          {
            inputPtr[j + (i*testcaseParams[testcase].srcImagePitch[levelCnt])] = rand() % 256;
          }
        }
      }
      inArgs.fast9Threshold[levelCnt] = testcaseParams[testcase].fast9Threshold[levelCnt];
    }

    inArgs.levelMask = (uint8_t)FAST9_CORNER_DETECT_TI_LEVEL_ALL;

    for ( levelCnt = 0; levelCnt < outBufDesc.numPlanes ; levelCnt++)
    {
      sizeOutput = 4 * testcaseParams[testcase].srcImageWidth[levelCnt] *
                          testcaseParams[testcase].srcImageHeight[levelCnt];

      outBufDesc.bufPlanes[levelCnt].frameROI.topLeft.x    = 0;
      outBufDesc.bufPlanes[levelCnt].frameROI.topLeft.y    = 0;
      outBufDesc.bufPlanes[levelCnt].width                 = sizeOutput;
      outBufDesc.bufPlanes[levelCnt].height                = 1;
      outBufDesc.bufPlanes[levelCnt].frameROI.width        = outBufDesc.bufPlanes[levelCnt].width;
      outBufDesc.bufPlanes[levelCnt].frameROI.height       = outBufDesc.bufPlanes[levelCnt].height;

      output = (uint8_t * )malloc(sizeOutput);
      outBufDesc.bufPlanes[levelCnt].buf = (uint8_t * )output;

      if(outBufDesc.bufPlanes[levelCnt].buf == NULL)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
    }


    vcop_minit();
    wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
    memset(wbufToZero, 0xcd, 31*1024);
    vcop_free(wbufToZero);

#if ENABLE_TRACES
    TEST_PRINTF("Processing start \n");
#endif
#if (ENABLE_PROFILE)
    profiler_start();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
    profiler_end_print(1);
    profile_tsc = gTest_TI_profileTsc;
    profile_sctm = gTest_TI_profileSctm[0];
#endif

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Processing End\n");
#endif

    if (testcaseParams[testcase].fileBased == 1)
    {
      for ( levelCnt = 0; levelCnt < outBufDesc.numPlanes ; levelCnt++)
      {
        /* Write output files */
        sprintf(filepath, "../testvecs/output/%s", testcaseParams[testcase].outImage[levelCnt]);
        fid= FOPEN(filepath,"wb");
        if ( fid == NULL)
        {
          TEST_PRINTF("Error, unable to open file %s \n", filepath);
          goto EXIT_LOOP;
        }
        output = (uint8_t * )outBufDesc.bufPlanes[levelCnt].buf;
        numBytes = FWRITE(output, 1,outArgs.numCorners[levelCnt]*4, fid);
        assert(numBytes == outArgs.numCorners[levelCnt]*4);
        FCLOSE(fid);
      }
    }

    for ( levelCnt = 0 ; levelCnt < testcaseParams[testcase].numLevels ; levelCnt++)
    {
      sizeOutput = outBufDesc.bufPlanes[levelCnt].width * outBufDesc.bufPlanes[levelCnt].height;
      refOutput[levelCnt] =  (uint8_t * )malloc(sizeOutput);
      if(refOutput == NULL)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
      numCornersRef =  FAST9CornerDetection_cn(
        (uint8_t *)inBufDesc.bufPlanes[levelCnt].buf,
        testcaseParams[testcase].srcImageWidth[levelCnt],
        testcaseParams[testcase].srcImageHeight[levelCnt],
        testcaseParams[testcase].srcImagePitch[levelCnt],
        createParams.excludeBorderX,
        createParams.excludeBorderY,
        (uint32_t *)refOutput[levelCnt],
        testcaseParams[testcase].fast9Threshold[levelCnt]
        );

      fail = 0 ;
      if(numCornersRef != outArgs.numCorners[levelCnt])
      {
        fail = 1;
        TEST_PRINTF("Failed at level %d \n", levelCnt);
      }
      else
      {
        fail =  memcmp(refOutput[levelCnt], outBufDesc.bufPlanes[levelCnt].buf, 4*outArgs.numCorners[levelCnt]);
      }

      if(!fail) {

        uint16_t x, y;

        for(i = 0; i < outArgs.numCorners[levelCnt]; i++) {
          x = ((uint16_t *)outBufDesc.bufPlanes[levelCnt].buf)[2*i];
          y = ((uint16_t *)outBufDesc.bufPlanes[levelCnt].buf)[2*i+1];
          if( (x < createParams.excludeBorderX) || (x > (testcaseParams[testcase].srcImageWidth[levelCnt]- createParams.excludeBorderX)) ||
              (y < createParams.excludeBorderY) || (y > (testcaseParams[testcase].srcImageHeight[levelCnt]- createParams.excludeBorderY))) {
            fail = 1;
            TEST_PRINTF("Corner %d - (%d, %d) outside the specified border.\n", i, x, y);
            break;
          }
        }
      }

      statusStr = fail?"FAILED":"PASSED";
      if ( fail )
      {
        TEST_PRINTF("Failed at level %d \n", levelCnt);
        break;
      }
    }
    profiler_printStatus(fail);

    totalActivePixels  = 0;

    for ( levelCnt = 0 ; levelCnt < testcaseParams[testcase].numLevels ; levelCnt++)
    {
      totalActivePixels  += outArgs.activeImgWidth[levelCnt] * outArgs.activeImgHeight[levelCnt];
    }
#if (ENABLE_PROFILE)
    TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
      "Algorithm", "Status", "BaseWidth", "BaseHeight","NumLevels", "MegaCycPerFr", \
      "MegaCycPerSec(30Fr)", "TotalCycPerPix", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

    TEST_PRINTF("%-20s %10s %10d %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
        Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
        "FAST9",statusStr, outArgs.activeImgWidth[0], outArgs.activeImgHeight[0],\
        testcaseParams[testcase].numLevels, (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
        (profile_tsc)/totalActivePixels,\
        (profile_sctm)/totalActivePixels,\
        (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);
#endif
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
    for ( levelCnt = 0 ; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      if ( inBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDesc.numPlanes ; levelCnt++)
    {
      if ( outBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDesc.numPlanes ; levelCnt++)
    {
      if ( refOutput[levelCnt] != NULL )
      {
        free(refOutput[levelCnt]);
      }
    }

  }

#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
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

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  report_printAppletInfo((int8_t *)"FAST9_CORNER_DETECT_TI_VISION");

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

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
      status = readparamfile(configFile, &gsTokenMap_fast9CornerDetect[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_fast9CornerDetect[0].testCaseName, (int8_t *)gConfig_fast9CornerDetect[0].desc,
                            gConfig_fast9CornerDetect[0].performanceTestcase);
      printparams(&gsTokenMap_fast9CornerDetect[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_fast9CornerDetect),
                            sizeof(sFast9CornerDetect_Config));

      /* Validate the applet */
      status = fast9CornerDetectTest(gConfig_fast9CornerDetect);
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


#if !(VCOP_HOST_EMULATION)
    profiler_getStackDepth();
#endif

  return status;


}



