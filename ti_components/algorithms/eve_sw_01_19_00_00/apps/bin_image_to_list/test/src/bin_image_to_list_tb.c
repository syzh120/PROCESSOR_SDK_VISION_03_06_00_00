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


/** @file bin_image_to_list_tb.c
*
*  @brief  This file contains test code for BIN_IMAGE_TO_LIST applet
*
*
*  @date   April 2015
*
*  Description
*    This file contains test code to validate the frame level applet BIN_IMAGE_TO_LIST.
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
#include "bin_image_to_list_config.h"
#include "xdais_types.h"
#include "ibin_image_to_list_ti.h"
#include "ti_file_io.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "vcop_binary_masking_cn.h"
#include "vcop_bin_image_to_list_cn.h"
#include "vcop_select_list_elements_cn.h"


#define ENABLE_OUTPUT_DUMP 0
#define ENABLE_TRACES 0
#define ENABLE_PROFILE (1U)
#define ALIGN_T0_32(x) (((x+31)/32)*32)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (16*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;


TIMemObject memObj_DMEM;

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define SELECTION_MASK_SIZE (128)

static int leftmostbit(uint32_t n)
{
    int j, a = 0;
    long long temp ;
    int compareBit = ( n > 0 ) ? 0 : 1;

    for (j = 1; j < 32; j++)
    {
      n = n<<1U;
      temp = (n >> 31U) & 0x1U;
      if (temp != compareBit )
      {
        break;
      }
    }
    a = 32 - j;
    return a;
}
#define CEIL(x,y) ((( x + y - 1) / y) * y)

static int32_t TestApp_generateSelectionMask(uint8_t selectionMaskSize,
        uint8_t *selectionMaskPtr,
        uint16_t numBitsToSet)
{
  uint8_t i;

  uint32_t firstPassValidBits;
  uint32_t stepsizeFirstPass;
  uint32_t remainingElements;
  uint8_t bucket;
  uint32_t stepsizeSecondPass;
  memset ( selectionMaskPtr, 0, selectionMaskSize );

  if ( numBitsToSet != 0 )
  {
    bucket = leftmostbit(numBitsToSet);


    firstPassValidBits = 1U << (bucket - 1U);
    stepsizeFirstPass  = CEIL(selectionMaskSize,firstPassValidBits) / firstPassValidBits;


    for ( i = 0; i < selectionMaskSize; i+= stepsizeFirstPass)
    {
      selectionMaskPtr[i] = 1U;
    }

    remainingElements = numBitsToSet - firstPassValidBits;

    if ( remainingElements != 0 )
    {
      stepsizeSecondPass = ((firstPassValidBits / remainingElements) * stepsizeFirstPass );
    }

    for ( i = 0; i < remainingElements; i++ )
    {
      selectionMaskPtr[i * stepsizeSecondPass  + (stepsizeFirstPass / 2U)] = 1U;
    }
  }

  return 0;
}



int32_t TestApp_BinImageToListReference
(
    BIN_IMAGE_TO_LIST_TI_CreateParams   * createParams,
    BIN_IMAGE_TO_LIST_TI_InArgs         * inArgs,
    IVISION_InBufs *inBufs,
    uint32_t       *outputListXy,
    uint32_t       *numListElems
)
{
  int32_t status = 0;
  uint8_t * binPackBuffer = NULL;
  uint8_t * interimBuf    = NULL;

  uint8_t   *inImgBuf;
  uint8_t   *byteMaskBuf;
  uint16_t  inImgWidth;
  uint16_t  inImgHeight;

  uint32_t  upperLeftXy = 0;
  uint8_t   xyOrder;
  uint16_t  inputImagePitch;
  uint16_t  inputMaskPitch;
  uint8_t   outputListQFormat;
  uint8_t   *binToListInputBuffer;
  uint32_t   *binToListOutputBuffer = NULL;
  uint32_t  numListPointsDetected = 0;
  uint32_t  numListPointsSelected = 0;
  uint8_t isSuppresionRequired;

  inImgBuf    = (uint8_t *) inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].buf;
  byteMaskBuf = (uint8_t *) inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].buf;

  inImgWidth  = inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].frameROI.width ;
  inImgHeight = inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].frameROI.height;

  inputImagePitch = inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].width;
  inputMaskPitch  = inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].width;


  binPackBuffer = (uint8_t *) malloc (inputMaskPitch * inImgHeight);
  if ( binPackBuffer == NULL)
  {
    status = -1;
    PRINT_ERRORE_MSG();
    goto EXIT;
  }

  if ( createParams->enableListSuppression == 1)
  {
    interimBuf = (uint8_t *) malloc (createParams->maxImageWidth *
                        createParams->maxImageHeight * sizeof(uint32_t));
    if ( interimBuf == NULL)
    {
      status = -1;
      PRINT_ERRORE_MSG();
      goto EXIT;
    }
  }


  if ( inArgs->outputListOrder == BIN_IMAGE_TO_LIST_TI_ORDER_XY)
  {
    upperLeftXy = (inArgs->startX) << (16 + inArgs->outputListQFormat)+ (inArgs->startY << inArgs->outputListQFormat);
    xyOrder = 1;
    outputListQFormat= inArgs->outputListQFormat;
  }
  else
  {
    upperLeftXy = (inArgs->startY) << (16 + inArgs->outputListQFormat)+ (inArgs->startX << inArgs->outputListQFormat);
    xyOrder = 0;
    outputListQFormat = (16 + inArgs->outputListQFormat);
  }

  binToListInputBuffer = inImgBuf;

  if ( createParams->enableMasking == 1 )
  {
    vcop_binary_masking_cn(byteMaskBuf,
                          inImgBuf,
                          binPackBuffer,
                          inImgWidth,
                          inImgHeight,
                          inputMaskPitch,
                          inputImagePitch,
                          inputImagePitch);

    binToListInputBuffer = binPackBuffer;
  }

  if ( createParams->enableListSuppression == 1 )
  {
    binToListOutputBuffer = (uint32_t *)interimBuf;
  }
  else
  {
    binToListOutputBuffer = outputListXy;
  }


  vcop_bin_image_to_list_cn(binToListInputBuffer,
                        &upperLeftXy,
                        binToListOutputBuffer,
                        &numListPointsDetected,
                        inImgWidth,
                        inImgHeight,
                        inputImagePitch * 8,
                        outputListQFormat,
                        xyOrder
                        );

  numListPointsSelected = numListPointsDetected;

  /* Check if suppresion is actually required */
  if ( createParams->enableListSuppression == 1U)
  {
    isSuppresionRequired = 1U;
    /* If suppression method is based on max value and actual number of points detected
    is already less than max value then suppresion is not required. Just do memcopy */
    if ( inArgs->listSuppressionMethod == BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE )
    {
      isSuppresionRequired = ( numListPointsDetected < inArgs->suppressionValue )? 0 : 1U;
    }
  }
  else
  {
    isSuppresionRequired = 0;
  }

  if (isSuppresionRequired && ( numListPointsDetected != 0 ) )
  {
    uint8_t selectionMaskArray[SELECTION_MASK_SIZE];

    numListPointsSelected = 0;
    /* numBitsToSet here tells us how many bits should be 1 in the selection mask */
    uint8_t numBitsToSet;

    if ( inArgs->listSuppressionMethod == BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE )
    {
      numBitsToSet = ( SELECTION_MASK_SIZE * inArgs->suppressionValue ) /
                      numListPointsDetected;
    }
    else if ( inArgs->listSuppressionMethod == BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_PERCENTAGE)
    {
      if ( inArgs->suppressionValue > 100 )
      {
        status = -1;
        goto EXIT;
      }

      numBitsToSet = ( SELECTION_MASK_SIZE * inArgs->suppressionValue ) / 100;
    }
    else
    {
      status = -1;
      goto EXIT;
    }

    /* Make detected points to be multiple of SELECTION_MASK_SIZE by ceiling */


    TestApp_generateSelectionMask(SELECTION_MASK_SIZE,selectionMaskArray, numBitsToSet);

    vcop_select_list_elements_cn(
      binToListOutputBuffer,
      outputListXy,
      selectionMaskArray,
      &numListPointsSelected,
      numListPointsDetected,
      SELECTION_MASK_SIZE);
  }
  else
  {
    if ( createParams->enableListSuppression == 1U )
    {
      memcpy(outputListXy,binToListOutputBuffer,numListPointsSelected * sizeof(uint32_t));
    }
  }
  *numListElems = numListPointsSelected;

EXIT:
  if (binPackBuffer)
  {
    free(binPackBuffer);
  }

  if (interimBuf)
  {
    free(interimBuf);
  }
  return status;
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

int32_t TestApp_AllocateBufs(IVISION_InBufs * inBufs,
                             IVISION_InBufs * outBufs)
{
  uint32_t i, j;
  int32_t status = 0;
  if ( inBufs != NULL)
  {
    for ( i  = 0 ; i < inBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
      {
        inBufs->bufDesc[i]->bufPlanes[j].buf = malloc(inBufs->bufDesc[i]->bufPlanes[j].width *
                                                           inBufs->bufDesc[i]->bufPlanes[j].height);
        if ( inBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
        {
          TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
          return -1;
        }
      }
    }
  }

  if ( outBufs != NULL )
  {
    for ( i  = 0 ; i < outBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
      {
        outBufs->bufDesc[i]->bufPlanes[j].buf = malloc(outBufs->bufDesc[i]->bufPlanes[j].width *
                                                       outBufs->bufDesc[i]->bufPlanes[j].height);
        if ( outBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
        {
          TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
          return -1;
        }
      }
    }
  }

  return status;
}


int32_t TestApp_FreeBufs(IVISION_InBufs * inBufs,
                                 IVISION_InBufs * outBufs)
{
  uint32_t i, j;
  int32_t status = 0;
  if ( inBufs != NULL )
  {
    for ( i  = 0 ; i < inBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
      {
        if (inBufs->bufDesc[i]->bufPlanes[j].buf != NULL)
        {
          free(inBufs->bufDesc[i]->bufPlanes[j].buf);
          inBufs->bufDesc[i]->bufPlanes[j].buf = NULL;
        }
      }
    }
  }
  if ( outBufs != NULL )
  {

    for ( i  = 0 ; i < outBufs->numBufs ; i++)
    {
      for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
      {
        if (outBufs->bufDesc[i]->bufPlanes[j].buf != NULL)
        {
          free(outBufs->bufDesc[i]->bufPlanes[j].buf);
          outBufs->bufDesc[i]->bufPlanes[j].buf = NULL;
        }
      }
    }
  }
  return status;
}

int32_t binImageToListTest(sBinImageToList_Config * testcaseParams)
{
#if ENABLE_PROFILE
  uint64_t     profile_tsc, profile_sctm;
  char  *statusStr = NULL;
#endif
  uint32_t i, j, idx, frameNum;

  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t seed;

  int32_t fail;
  TI_FILE *fp_in = NULL;
#if ENABLE_OUTPUT_DUMP
  TI_FILE * fp_out = NULL;
#endif

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  BIN_IMAGE_TO_LIST_TI_CreateParams   createParams;

  BIN_IMAGE_TO_LIST_TI_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL];

  BIN_IMAGE_TO_LIST_TI_OutArgs   outArgs;
  IVISION_OutBufs     outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL];

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  uint32_t *outputListXyRef = NULL;
  uint32_t numListElemRef;

  /* This is just to remove warning coming from linker command file */
    vcop_minit();

  outArgs.iVisionOutArgs.size = sizeof(BIN_IMAGE_TO_LIST_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(BIN_IMAGE_TO_LIST_TI_InArgs);

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if ENABLE_PROFILE
  profiler_init();
#endif

  /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs  = BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]     = &inBufDesc[i];
  }

  for(i = 0 ; i < BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
  /*-----------------------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/

  createParams.inputDataFormat        = testcaseParams->inputDataFormat;
  createParams.inputMaskFormat        = testcaseParams->inputMaskFormat;
  createParams.enableMasking          = testcaseParams->enableMasking;
  createParams.enableListSuppression  = testcaseParams->enableListSuppression;
  createParams.maxImageWidth          = 1920;
  createParams.maxImageHeight         = 1080;

  inArgs.startX = 0;
  inArgs.startY = 0;
  inArgs.outputListOrder        = testcaseParams->outputListOrder;
  inArgs.outputListQFormat      = testcaseParams->outputListQFormat;
  inArgs.listSuppressionMethod  = testcaseParams->listSuppressionMethod;
  inArgs.suppressionValue       = testcaseParams->suppressionValue;

  numMemRec = BIN_IMAGE_TO_LIST_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = BIN_IMAGE_TO_LIST_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("BIN_IMAGE_TO_LIST Applet Create Done\n");
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

#if ENABLE_PROFILE
    profiler_initStack(profiler_getSP());
    profiler_start();
#endif


  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = BIN_IMAGE_TO_LIST_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

#if ENABLE_PROFILE
      profiler_end_print(0);
/*      profile_create_tsc = gTest_TI_profileTsc;*/
#endif

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("BIN_IMAGE_TO_LIST  Applet Init Done\n");
#endif


  idx = BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER;
  inBufs.bufDesc[idx]->numPlanes                          = 1;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams->inputImagePitch;
  /* Worst case padding buffer requirement for this applet is 4096 so add extra lines required for padding*/
  inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams->imgHeight + 7;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams->imgWidth / 8;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams->imgHeight;
  inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;


  idx = BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER;
  inBufs.bufDesc[idx]->numPlanes                          = 1;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams->inputMaskPitch;
  /* Worst case padding buffer requirement for this applet is 4096 so add extra lines required for padding*/
  inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams->imgHeight + 7;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams->imgWidth;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams->imgHeight;
  inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;


  idx = BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST;
  outBufs.bufDesc[idx]->numPlanes                          = 1;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams->imgWidth * testcaseParams->imgHeight *
                                                              sizeof(uint32_t);
                                                              ;
  outBufs.bufDesc[idx]->bufPlanes[0].height                = 1;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = outBufs.bufDesc[idx]->bufPlanes[0].width;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = 1;
  outBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

  status = TestApp_AllocateBufs(&inBufs, &outBufs);
   if(status != IALG_EOK)
   {
     PRINT_ERRORE_MSG();
     goto EXIT_LOOP;
   }

  outputListXyRef = (uint32_t *) malloc (outBufs.bufDesc[idx]->bufPlanes[0].width * outBufs.bufDesc[idx]->bufPlanes[0].height);

  if ( outputListXyRef == NULL)
   {
     PRINT_ERRORE_MSG();
     goto EXIT_LOOP;
   }


  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.iVisionInArgs.size                  = sizeof(BIN_IMAGE_TO_LIST_TI_InArgs);

  for ( frameNum = 0 ; frameNum < testcaseParams->numFrames ; frameNum++ )
  {

    if ( strcmp((const char *)testcaseParams->inputImage, ""))
    {
      uint32_t frameSize;
      fp_in = FOPEN((const char *)testcaseParams->inputImage, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams->inputImage);
          return -1;
      }
      frameSize = inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].width *
              inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].height;

      FSEEK(fp_in, frameNum * frameSize, SEEK_SET);
      FREAD(inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].buf,
                    frameSize, 1, fp_in);

      FCLOSE(fp_in);
    }
    else
    {
      uint8_t  * ptr  = (uint8_t *) inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].buf;

      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);

      for ( j = 0; j < testcaseParams->imgHeight; j++ )
      {
        for ( i = 0 ; i < testcaseParams->imgWidth / 8; i++)
        {
          ptr[i + (j * testcaseParams->inputImagePitch)] = rand();
        }
      }
    }

    if ( strcmp((const char *)testcaseParams->inputMask, ""))
    {
      uint32_t frameSize;
      fp_in = FOPEN((const char *)testcaseParams->inputMask, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams->inputMask);
          return -1;
      }
      frameSize = inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].width *
              inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].height;

      FSEEK(fp_in, frameNum * frameSize, SEEK_SET);
      FREAD(inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].buf,
                    frameSize, 1, fp_in);

      FCLOSE(fp_in);
    }
    else
    {
      uint8_t  * ptr  = (uint8_t *) inBufs.bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].buf;

      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);

      for ( j = 0; j < testcaseParams->imgHeight; j++ )
      {
        for ( i = 0 ; i < testcaseParams->imgWidth; i++)
        {
          ptr[i + (j * testcaseParams->inputMaskPitch)] = rand() % 2;
        }
      }
    }

#if ENABLE_TRACES
    TEST_PRINTF("Processing started for frame %d \n",0);
#endif

#if ENABLE_PROFILE
        profiler_start();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if ENABLE_PROFILE
    profiler_end_print(1);

    profile_tsc  = gTest_TI_profileTsc;
    profile_sctm = gTest_TI_profileSctm[0];

#endif

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
  }
#if ENABLE_TRACES
    TEST_PRINTF("Processing Completed for frame %d \n",0);
#endif


    TestApp_BinImageToListReference(
      &createParams,
      &inArgs,
      &inBufs,
      outputListXyRef,
      &numListElemRef
    );

    fail = 0;

    if ( numListElemRef == outArgs.numListPoints )
    {
      fail = memcmp(outputListXyRef, outBufs.bufDesc[0]->bufPlanes[0].buf,numListElemRef * sizeof(uint32_t) );

      if ( fail != 0 )
      {
        for ( i = 0 ; i < numListElemRef; i++)
        {
          if ( outputListXyRef[i] != ((uint32_t *)outBufs.bufDesc[0]->bufPlanes[0].buf)[i])
          {
            TEST_PRINTF("Output mismatches at location %d \n", i);
          }
        }
      }

    }
    else
    {
      fail = -1;
    }

    fflush(stdout);

#if ENABLE_PROFILE
    statusStr = fail ? "FAILED":"PASSED";

#if (VCOP_HOST_EMULATION)
    profile_sctm = 1;
    profile_tsc = 1;
#endif

    TEST_PRINTF("\n%-15s %10s %15s %15s %15s %20s %16s %17s %16s    %s\n", \
        "Algorithm", "Status", "imageWidth", "imageHeight", "MegaCycPerFr", \
        "MegaCycPerSec(30Fr)", "TotalCycPerPoint", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

    TEST_PRINTF("%-15s %10s %15d %15d %15.2f %20.2f %16.2f %17.2f %16.2f\
      None\n",\
      "Bin Image To List",
      statusStr,
      testcaseParams->imgWidth,
      testcaseParams->imgHeight,
      (profile_tsc/1000000.0),
      30*(profile_tsc/1000000.0),
      (profile_tsc)/(float)(testcaseParams->imgWidth * testcaseParams->imgHeight),
      (profile_sctm)/(float)(testcaseParams->imgWidth * testcaseParams->imgHeight),
      (profile_tsc/500000.0));

     profiler_printStatus(fail);

#endif


#if ENABLE_OUTPUT_DUMP
    if(strcmp((const char *)testcaseParams->outputListXY, ""))
    {
      fp_out = FOPEN((const char*)testcaseParams->outputListXY, "wb+");


      if(fp_out != NULL)
      {

        FWRITE(outBufs.bufDesc[0]->bufPlanes[0].buf , outArgs.numListPoints * sizeof(uint32_t),
                          1, fp_out);

        FCLOSE(fp_out);
      }
      else
      {
        TEST_PRINTF("Failed to open Output file.\n");
      }
    }
#endif
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

    if ( outputListXyRef)
    {
      free(outputListXyRef);
      outputListXyRef = NULL;
    }

    TestApp_FreeBufs(&inBufs, &outBufs);

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

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  report_printAppletInfo((int8_t *)"BIN_IMAGE_TO_LIST_TI_VISION");

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
      status = readparamfile(configFile, &gsTokenMap_binImageToList[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_binImageToList[0].testCaseName, (int8_t *)gConfig_binImageToList[0].desc,
                                  gConfig_binImageToList[0].performanceTestcase);
      printparams(&gsTokenMap_binImageToList[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_binImageToList),
                            sizeof(sBinImageToList_Config));

      /* Validate the applet */
      status = binImageToListTest(gConfig_binImageToList);
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

  return status;
}



