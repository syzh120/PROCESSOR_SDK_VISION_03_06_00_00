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


/**
*  @file       fast9_corner_detect_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for FAST9 corner detect applet
*  @version     0.0 (Dec 2013) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "fast9_corner_detect_alg_int.h"
#include "edma_utils_memcpy.h"

/* Function prototypes */
static void FAST9_CORNER_DETECT_TI_findOptimizeBlockDim(uint16_t imgW,
                                                        uint16_t imgH,
                                                        uint16_t excludeBorderX,
                                                        uint16_t excludeBorderY,
                                                        uint16_t *blockW,
                                                        uint16_t *blockH,
                                                        uint16_t *activeImgWidth,
                                                        uint16_t *activeImgHeight);
static void bestDimBlkW(uint16_t imgW, uint16_t eImgW, uint16_t k, uint16_t* eBlkWout);
static void bestDimBlkH(uint16_t imgH, uint16_t eImgH, uint16_t k, uint16_t* eBlkHout);

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns FAST9_CORNER_DETECT_TI_VISION_FXNS =
{
  {
      &FAST9_CORNER_DETECT_TI_activate, /* module ID */
      &FAST9_CORNER_DETECT_TI_activate,    /* activate */
      &FAST9_CORNER_DETECT_TI_alloc,       /* algAlloc */
      NULL,                          /* control (not suported) */
      &FAST9_CORNER_DETECT_TI_deactivate,  /* deactivate */
      &FAST9_CORNER_DETECT_TI_free,        /* free */
      &FAST9_CORNER_DETECT_TI_init,        /* init */
      NULL,                          /* moved (not suported) */
      &FAST9_CORNER_DETECT_TI_numAlloc     /* algNumAlloc  */
  },
  &FAST9_CORNER_DETECT_TI_process,
  &FAST9_CORNER_DETECT_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns FAST9_CORNER_DETECT_TI_IRES = {
  NULL,
  NULL,                                     /*getResourceDescriptors, */
  NULL,                                     /*numResourceDescriptors */
  NULL,                                     /*initResources,  */
  NULL,                                     /*reinitResources, */
  NULL,                                     /*deinitResources, */
  NULL,                                     /*activateResource,*/
  NULL,                                     /*activateAllResources, */
  NULL,                                     /*deactivateResource,   */
  NULL                                      /*deactivateAllResources */
};

/**
* Other exposed functions
*/
int32_t FAST9_CORNER_DETECT_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}

/* Find best block width satisfying EDMA and Kernel requirements */
static void bestDimBlkW(uint16_t imgW, uint16_t eImgW, uint16_t k, uint16_t* eBlkWout)
{
  int32_t bwToSatisfyDmaCeil;
  int32_t bwToSatisfyDmaClip;
  uint16_t eBlkW;

  bwToSatisfyDmaCeil = (((int32_t)eImgW + ((int32_t)k-1))/(int32_t)k);/* Edma Utiltiy requirement */
  bwToSatisfyDmaClip = (int32_t)eImgW / (int32_t)k;/* Edma Utiltiy requirement */

  eBlkW = (((uint16_t)bwToSatisfyDmaCeil + 7U)/8U) * 8U;/* Kernel Requirement : eBlkW should be divisable by 8*/
  if( (eBlkW * k) <= (imgW - (2U * FAST9_TI_BORDER_X)))
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  eBlkW = (((uint16_t)bwToSatisfyDmaCeil) / 8U) * 8U;/* Kernel Requirement : eBlkW should be divisable by 8*/

  if( (eBlkW * k) <= (imgW - (2U * FAST9_TI_BORDER_X)))
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  eBlkW = (((uint16_t)bwToSatisfyDmaClip + 7U)/8U) * 8U;/* Kernel Requirement : eBlkW should be divisable by 8*/
  if( (eBlkW * k) <= (imgW - (2U * FAST9_TI_BORDER_X)))
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  eBlkW = (((uint16_t)bwToSatisfyDmaClip) / 8U) * 8U;/* Kernel Requirement : eBlkW should be divisable by 8*/

  if( (eBlkW * k) <= (imgW - (2U * FAST9_TI_BORDER_X)))
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

EXIT:

  *eBlkWout = eBlkW;

  return;

}

/* Find best block height satisfying EDMA requirement */
static void bestDimBlkH(uint16_t imgH, uint16_t eImgH, uint16_t k, uint16_t* eBlkHout)
{
  uint16_t eBlkH;

  eBlkH = (eImgH + (k-1U)) / k;/* Edma Utiltiy requirement */

  if( (eBlkH * k) <= (imgH - (2U * FAST9_TI_BORDER_Y)))
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  eBlkH = eImgH / k ;/* Edma Utiltiy requirement */
  if( (eBlkH * k) <= (imgH - (2U * FAST9_TI_BORDER_Y)))
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
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
  uint16_t blkW, blkH;
  uint16_t maxEffblockWidth, maxEffblockHeight;
  uint16_t eBlkW, eBlkH;
  uint16_t eImgW, eImgH;
  uint16_t k;
  uint16_t effectiveBorderX;
  uint16_t effectiveBorderY;
  int32_t delta;
  int32_t mindelta = 100000;
  uint16_t eImgWOpt,eImgHOpt;
  uint16_t blkWOpt,blkHOpt;

  /* If exclude border X is less than FAST9_TI_BORDER_X then border needed
  will still be FAST9_TI_BORDER_X because that is mandatory border needed by
  FAST9 corner detect algorithm */
  if ( excludeBorderX < FAST9_TI_BORDER_X )
  {
    effectiveBorderX = FAST9_TI_BORDER_X;
  }
  else
  {
    effectiveBorderX = excludeBorderX;
  }

  if ( excludeBorderY < FAST9_TI_BORDER_Y )
  {
    effectiveBorderY = FAST9_TI_BORDER_Y;
  }
  else
  {
    effectiveBorderY = excludeBorderY;
  }

  maxEffblockWidth  = FAST9_TI_BLK_WIDTH_MAX  - (2U * FAST9_TI_BORDER_X);
  maxEffblockHeight = FAST9_TI_BLK_HEIGHT_MAX - (2U * FAST9_TI_BORDER_Y);


  eImgW = imgW - (2U * effectiveBorderX);
  eImgH = imgH - (2U * effectiveBorderY);
  /*First find optimal Block Width */
  do
  {
    k = 1U;
    /* Find effectiveBlock Width based on current maxEffblockWidth */
    while(1)
    {
      /* Find the best block width which is not going beyond input image Width */
      bestDimBlkW(imgW, eImgW, k , &eBlkW );
      /* Check if above block width fits into internal memory, if not then try with another factor
      k++ in next iteration */
      if (  eBlkW <= maxEffblockWidth)
      {
        eImgW = eBlkW*k;
        break;
      }
      k++;
    }

    delta = (((int32_t)imgW) - (2 * ((int32_t)effectiveBorderX))) - ((int32_t)eImgW);

    /* Keep storing the effective block width found for which delta is minimum, which
    basically indicates that actual image width is closer to effective image width*/
    if ( delta < mindelta )
    {
      eImgWOpt = eBlkW*k;
      blkWOpt  = eBlkW  + (2U * FAST9_TI_BORDER_X);
      mindelta = delta;
    }

    /* reduce maxEffblockWidth by one so as to re-iterate again if delta is greater than zero
    to see if some other k satisfy all the above requriements and still having small delta */
    maxEffblockWidth -= 1U ;
    /* If maxEffblockWidth is smaller than the minimum block width by kernel then break so as to
    pick the effective block width corresponding to the iteration where delta is minimum */
    if( maxEffblockWidth < (FAST9_TI_BLK_WIDTH_MIN - (2U * FAST9_TI_BORDER_X)) )
    {
      break ;
    }
  } while (delta > 0 );
  eImgW = eImgWOpt;
  blkW  = blkWOpt;

  /* Now find optimal block height */
  k = 1U;
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
    delta = (((int32_t)imgH) - (2 * ((int32_t)effectiveBorderY))) - ((int32_t)eImgH);

    /* Keep storing the effective block width found for which delta is minimum, which
    basically indicates that actual image width is closer to effective image width*/
    if ( delta < mindelta )
    {
      eImgHOpt = eBlkH*k;
      blkHOpt  = eBlkH  + (2U * FAST9_TI_BORDER_Y);
      mindelta = delta;
    }

    /* reduce maxEffblockHeight by one so as to re-iterate again if delta is greater than zero
    to see if some other k satisfy all the above requriements and still having small delta */
    maxEffblockHeight -= 1U ;
    /* If maxEffblockHeight is smaller than the minimum block height by kernel then break so as to
    pick the effective block height corresponding to the iteration where delta is minimum */
    if( maxEffblockHeight < (FAST9_TI_BLK_HEIGHT_MIN - (2U * FAST9_TI_BORDER_Y)))
    {
      break ;
    }

  }while(delta > 0);

  eImgH = eImgHOpt;
  blkH  = blkHOpt;

  *blockW = blkW;
  *blockH = blkH;
  *activeImgWidth  = eImgW + (2U * FAST9_TI_BORDER_X);
  *activeImgHeight = eImgH + (2U * FAST9_TI_BORDER_Y);
}


/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_alloc(const IALG_Params *params,
                                                  IALG_Fxns **parentFxns,
                                                  IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;

  BAM_GraphMemReq graphMemReqFast9;
  BAM_GraphMemReq graphMemReqBintoList;
  const FAST9_CORNER_DETECT_TI_CreateParams * createParams =
    (const FAST9_CORNER_DETECT_TI_CreateParams*)(const void *)params;

  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  FAST9_CORNER_DETECT_TI_getGraphMemReq(&graphMemReqFast9);
  BIN_IMAGE_TO_LIST_TI_getGraphMemReq(&graphMemReqBintoList);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
  /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
  /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
  /*  This persistent record will be used to backup the following scratch        */
  /*  memory record during context saving when FAST9_CORNER_DETECT_TI_deactivate */
  /*  is called. Likewise when FAST9_CORNER_DETECT_TI_activate it called,        */
  /*  the content of the persistent memory record is copied back to the          */
  /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size          = sizeof(FAST9_CORNER_DETECT_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment     = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(FAST9_CORNER_DETECT_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. FAST9_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. FAST9_GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. FAST9_GRAPH_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. FAST9_GRAPH_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. FAST9_GRAPH_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

  memRec[FAST9_GRAPH_OBJ_MEMREC].size           = graphMemReqFast9.graphObjSize;
  memRec[FAST9_GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[FAST9_GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
  memRec[FAST9_GRAPH_OBJ_MEMREC].alignment      = 4;

  /*
    FAST9_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
  */
  memRec[FAST9_GRAPH_OBJ_INT_MEMREC].size       = graphMemReqFast9.graphObjSize;
  memRec[FAST9_GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[FAST9_GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
  memRec[FAST9_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

  memRec[FAST9_GRAPH_SCRATCH_MEMREC].size       =  graphMemReqFast9.graphScratchSize;
  memRec[FAST9_GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[FAST9_GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[FAST9_GRAPH_SCRATCH_MEMREC].alignment  = 4;

  memRec[FAST9_GRAPH_CONTEXT_MEMREC].size       =  graphMemReqFast9.graphcontextSize;
  memRec[FAST9_GRAPH_CONTEXT_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[FAST9_GRAPH_CONTEXT_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[FAST9_GRAPH_CONTEXT_MEMREC].alignment  = 4;

  memRec[FAST9_GRAPH_ARGS_MEMREC].size          =  graphMemReqFast9.graphArgsSize;
  memRec[FAST9_GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[FAST9_GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[FAST9_GRAPH_ARGS_MEMREC].alignment     = 4;

  memRec[BIN2LIST_GRAPH_OBJ_MEMREC].size        = graphMemReqBintoList.graphObjSize;
  memRec[BIN2LIST_GRAPH_OBJ_MEMREC].space       = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[BIN2LIST_GRAPH_OBJ_MEMREC].attrs       = IALG_PERSIST;
  memRec[BIN2LIST_GRAPH_OBJ_MEMREC].alignment   = 4;

  /*
    BIN2IMG_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
  */
  memRec[BIN2LIST_GRAPH_OBJ_INT_MEMREC].size        = graphMemReqBintoList.graphObjSize;
  memRec[BIN2LIST_GRAPH_OBJ_INT_MEMREC].space       = (IALG_MemSpace) IALG_DARAM0;
  memRec[BIN2LIST_GRAPH_OBJ_INT_MEMREC].attrs       = IALG_SCRATCH;
  memRec[BIN2LIST_GRAPH_OBJ_INT_MEMREC].alignment   = 4;

  memRec[BIN2LIST_GRAPH_SCRATCH_MEMREC].size        = graphMemReqBintoList.graphScratchSize;
  memRec[BIN2LIST_GRAPH_SCRATCH_MEMREC].space       = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[BIN2LIST_GRAPH_SCRATCH_MEMREC].attrs       = IALG_SCRATCH;
  memRec[BIN2LIST_GRAPH_SCRATCH_MEMREC].alignment   = 4;

  memRec[BIN2LIST_GRAPH_CONTEXT_MEMREC].size        = graphMemReqBintoList.graphcontextSize;
  memRec[BIN2LIST_GRAPH_CONTEXT_MEMREC].space       = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[BIN2LIST_GRAPH_CONTEXT_MEMREC].attrs       = IALG_SCRATCH;
  memRec[BIN2LIST_GRAPH_CONTEXT_MEMREC].alignment   = 4;

  memRec[BIN2LIST_GRAPH_ARGS_MEMREC].size           = graphMemReqBintoList.graphArgsSize;
  memRec[BIN2LIST_GRAPH_ARGS_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[BIN2LIST_GRAPH_ARGS_MEMREC].attrs          = IALG_SCRATCH;
  memRec[BIN2LIST_GRAPH_ARGS_MEMREC].alignment      = 4;

  /*-------------------------------------------------------------------------*/
  /* Below should contain Applet specific memory request.                    */
  /*-------------------------------------------------------------------------*/
  /* this is under the assumption that zero'th is the max */
  memRec[BIN_IMG_SCRATCH_MEMREC].size       = ((createParams->imgFrameWidth[0] +7U)/8U)*
                                               createParams->imgFrameHeight[0];
  memRec[BIN_IMG_SCRATCH_MEMREC].space      = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[BIN_IMG_SCRATCH_MEMREC].attrs      = IALG_SCRATCH;
  memRec[BIN_IMG_SCRATCH_MEMREC].alignment  =  4;

  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_init(IALG_Handle handle,
                                                   const IALG_MemRec memRec[],
                                                   IALG_Handle parent,
                                                   const IALG_Params * params)
{
  int32_t status = IALG_EOK;
  int32_t bamStatus;
  uint16_t levelCnt;
  uint16_t blkWidthFinal  = 0;
  uint16_t blkHeightFinal = 0;
  uint16_t imgWidth;
  uint16_t imgHeight;
  int16_t extra_pixels_in_border;

  const FAST9_CORNER_DETECT_TI_CreateParams * createParams =
    (const FAST9_CORNER_DETECT_TI_CreateParams*)(const void *)params;

  FAST9_CORNER_DETECT_TI_graphArgs fast9GraphCreateParams;
  BIN_IMAGE_TO_LIST_TI_graphArgs    bin2ListGraphCreateParams;

  FAST9_CORNER_DETECT_TI_Handle algHandle =
        (FAST9_CORNER_DETECT_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->fast9GraphMem.graphObj      = memRec[FAST9_GRAPH_OBJ_MEMREC].base;
  algHandle->fast9GraphMem.graphScratch  = memRec[FAST9_GRAPH_SCRATCH_MEMREC].base;
  algHandle->fast9GraphMem.graphcontext  = memRec[FAST9_GRAPH_CONTEXT_MEMREC].base;
  algHandle->fast9GraphMem.graphArgs     = memRec[FAST9_GRAPH_ARGS_MEMREC].base;

  algHandle->numLevels  = createParams->numLevels;

  for (levelCnt = 0 ; levelCnt < createParams->numLevels; levelCnt++)
  {
    FAST9_CORNER_DETECT_TI_findOptimizeBlockDim(createParams->imgFrameWidth[levelCnt],
                                                createParams->imgFrameHeight[levelCnt],
                                                createParams->excludeBorderX,
                                                createParams->excludeBorderY,
                                                &algHandle->blockWidth[levelCnt],
                                                &algHandle->blockHeight[levelCnt],
                                                &algHandle->activeImageWidth[levelCnt],
                                                &algHandle->activeImageHeight[levelCnt]);


    algHandle->dx[levelCnt] = (createParams->imgFrameWidth[levelCnt] -
                                         algHandle->activeImageWidth[levelCnt])/2U ;
    algHandle->dy[levelCnt] = (createParams->imgFrameHeight[levelCnt] -
                                          algHandle->activeImageHeight[levelCnt])/2U ;

    imgWidth  = algHandle->activeImageWidth[levelCnt] - ((uint16_t)FAST9_TI_BORDER_X * 2U);
    imgHeight = algHandle->activeImageHeight[levelCnt] - ((uint16_t)FAST9_TI_BORDER_Y * 2U);

    algHandle->dx_binImg[levelCnt] = 0U;
    algHandle->dy_binImg[levelCnt] = 0U;

    /* Ensure that the applet returns corners only within the excluded borders specified */
    extra_pixels_in_border = ((int16_t)createParams->excludeBorderX - ((int16_t)algHandle->dx[levelCnt] + (int16_t)FAST9_TI_BORDER_X));
    if(extra_pixels_in_border > 0) {
        algHandle->dx_binImg[levelCnt] = (((uint16_t)extra_pixels_in_border + 7U)/8U)*8U;
        imgWidth -= (uint16_t)2 * algHandle->dx_binImg[levelCnt];
    }

    extra_pixels_in_border = ((int16_t)createParams->excludeBorderY - ((int16_t)algHandle->dy[levelCnt] + (int16_t)FAST9_TI_BORDER_Y));
    if(extra_pixels_in_border > 0) {
        algHandle->dy_binImg[levelCnt] = (uint16_t)extra_pixels_in_border;
        imgHeight -= (uint16_t)2 * algHandle->dy_binImg[levelCnt];
    }

    /* To ensure list is generated in raster order, processing block width is always set to image width */
    blkWidthFinal = imgWidth;

    /* Find optimal block height to efficiently utilize the internal memory */
    if((imgWidth * imgHeight) <= BIN_IMAGE_TO_LIST_MAX_PIXELS) {
        blkHeightFinal = imgHeight;
    }
    else
    {
        blkHeightFinal = (uint16_t)BIN_IMAGE_TO_LIST_MAX_PIXELS / imgWidth;
        while((imgHeight % blkHeightFinal) != 0) {
            blkHeightFinal--;
        }
    }
    algHandle->activeBinImgWidth[levelCnt]        = imgWidth + (FAST9_TI_BORDER_X * 2U);
    algHandle->activeBinImgHeight[levelCnt]       = imgHeight + (FAST9_TI_BORDER_Y * 2U);
    algHandle->blockWidthBinImgToList[levelCnt]   = blkWidthFinal;
    algHandle->blockHeightBinImgToList[levelCnt]  = blkHeightFinal;
  }

  bamStatus = FAST9_CORNER_DETECT_TI_graphCreate(&(algHandle->fast9GraphMem),&fast9GraphCreateParams);

  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("FAST9_CORNER_DETECT_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*-----------------------------------------------------------------------*/
  /* Call Binary Image to List BAM Graph creation function                 */
  /*-----------------------------------------------------------------------*/
  algHandle->binToListGraphMem.graphObj      = memRec[BIN2LIST_GRAPH_OBJ_MEMREC].base;
  algHandle->binToListGraphMem.graphScratch  = memRec[BIN2LIST_GRAPH_SCRATCH_MEMREC].base;
  algHandle->binToListGraphMem.graphcontext  = memRec[BIN2LIST_GRAPH_CONTEXT_MEMREC].base;
  algHandle->binToListGraphMem.graphArgs     = memRec[BIN2LIST_GRAPH_ARGS_MEMREC].base;

  bamStatus = BIN_IMAGE_TO_LIST_TI_graphCreate(&(algHandle->binToListGraphMem),&bin2ListGraphCreateParams);

  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("BIN_IMAGE_TO_LIST_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = &FAST9_CORNER_DETECT_TI_VISION_FXNS;

  /*-----------------------------------------------------------------------*/
  /* State to indicate that internal context of algorithm is not active    */
  /*-----------------------------------------------------------------------*/
  algHandle->algState = ALG_NOT_ACTIVE;

Exit:
  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_control(IVISION_Handle handle,
                                       IALG_Cmd cmd,
                                       const IALG_Params *inParams,
                                       IALG_Params *outParams)
{
  int32_t status = IALG_EOK;

  return (status);
}

/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* MISRA.PPARAM.NEEDS.CONST:   Pointer parameter is not used to modify the addressed object but is not declared as a pointer to const*/
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const. Fixing this will
    involve changing ivision interface and as this interface is already widely in use we have decided to waive this issue for such incidences */

int32_t FAST9_CORNER_DETECT_TI_process(IVISION_Handle handle,
                                       IVISION_InBufs *inBufs,
                                       IVISION_OutBufs *outBufs,
                                       IVISION_InArgs *inArgs,
                                       IVISION_OutArgs *outArgs)
{
  /* RESET_MISRA("16.7")  -> Reset rule 16.7     */
  /* CHECK_MISRA("-11.4")  -> Disable rule 11.4  */
  /* handle is a extended structure from the base IALG_Handle structure.   */
  FAST9_CORNER_DETECT_TI_Handle algHandle = (FAST9_CORNER_DETECT_TI_Handle)(handle);
  /* RESET_MISRA("11.4")  -> Reset rule 11.4     */

  FAST9_CORNER_DETECT_TI_Handle intAlgHandle;
  int32_t status            = IALG_EOK;
  int32_t bamStatus;
  uint32_t numCorners ;

  IBAMALG_InArgs          bamInArgs;
  IBAMALG_OutArgs         bamOutArgs;
  IBAMALG_OutArgs         outScratchArgs;
  IBAMALG_InArgs          inScratchArgs;

  IVISION_BufDesc         interMediateBufDesc;
  uint8_t                 levelCnt;

  FAST9_CORNER_DETECT_TI_OutArgs * fast9OutArgs;
  FAST9_CORNER_DETECT_TI_InArgs  * fast9InArgs;
  BAM_Fast9_ctrlArgs                 fast9KernelCtrlArgs;
  BAM_Bin_image_to_list_ctrlArgs     binImg2ListCtrlArgs;
  FAST9_CORNER_DETECT_TI_dmaCtrlArgs fast9DmaCtrlArgs;
  BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs   binImg2ListDmaCtrlArgs;
  IVISION_BufDesc  *(*inBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc  *(*outBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_TOTAL];

  inBufDesc = (IVISION_BufDesc *(*)[FAST9_CORNER_DETECT_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  if ( inBufs->numBufs < 1U )
  {
    status = IVISION_ERRORTYPE_NUM_INBUF_LESS;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if ( inArgs->size != sizeof(FAST9_CORNER_DETECT_TI_InArgs))
  {
    status = IALG_EFAIL;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  fast9InArgs = (FAST9_CORNER_DETECT_TI_InArgs *)inArgs;

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  FAST9_CORNER_DETECT_TI_activate((IALG_Handle)handle);

  intAlgHandle                      = (FAST9_CORNER_DETECT_TI_Handle)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->fast9GraphMem.graphObj      = intAlgHandle->memRec[FAST9_GRAPH_OBJ_INT_MEMREC].base;
  intAlgHandle->binToListGraphMem.graphObj = intAlgHandle->memRec[BIN2LIST_GRAPH_OBJ_INT_MEMREC].base;

  /*-----------------------------------------------------------------------------*/
  /* BAM specific In Args and OutArgs Assignment                                 */
  /* There are 2 graphs combined in this applet:                                 */
  /* 1. FAST9_CORNER_DETECT: Takes bamInBufs and produces in fast9OutBuf         */
  /* 2. BIN_IMAGE_TO_LIST: It takes the output of previous graph (binToListInBuf)*/
  /* and prooduces in outBufDesc[0]                                              */
  /* outBufDesc[1] is used by BIN_IMAGE_TO_LIST graph to produce the number of   */
  /* corners - as of now BAM communicate through buffer descriptor only in its   */
  /* graph nodes - so this is the only way.                                      */
  /*-----------------------------------------------------------------------------*/
  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;

  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

  inScratchArgs.size                  = sizeof(IBAMALG_InArgs);
  inScratchArgs.sliceIndex            = 0;

  outScratchArgs.size                 = sizeof(IBAMALG_OutArgs);

  for ( levelCnt = 0 ; levelCnt < intAlgHandle->numLevels; levelCnt++)
  {
    if ( fast9InArgs->levelMask & (uint8_t)(1U << levelCnt ))
    {
      /* Update fast9 kernel properties before execute */
      fast9KernelCtrlArgs.in_w      = intAlgHandle->blockWidth[levelCnt];
      fast9KernelCtrlArgs.in_h      = intAlgHandle->blockHeight[levelCnt];
      fast9KernelCtrlArgs.pitch     = intAlgHandle->blockWidth[levelCnt];

      fast9KernelCtrlArgs.threshold = fast9InArgs->fast9Threshold[levelCnt];

      bamStatus = FAST9_CORNER_DETECT_TI_graphControl(&(intAlgHandle->fast9GraphMem),
                                          &fast9KernelCtrlArgs);

      fast9DmaCtrlArgs.activeImageWidth  = intAlgHandle->activeImageWidth[levelCnt];
      fast9DmaCtrlArgs.activeImageHeight = intAlgHandle->activeImageHeight[levelCnt];
      fast9DmaCtrlArgs.blkWidth          = intAlgHandle->blockWidth[levelCnt];
      fast9DmaCtrlArgs.blkHeight         = intAlgHandle->blockHeight[levelCnt];
      fast9DmaCtrlArgs.dx                = intAlgHandle->dx[levelCnt];
      fast9DmaCtrlArgs.dy                = intAlgHandle->dy[levelCnt];
      fast9DmaCtrlArgs.level             = levelCnt;

      interMediateBufDesc.bufPlanes[0].buf =
                                intAlgHandle->memRec[BIN_IMG_SCRATCH_MEMREC].base;
      interMediateBufDesc.bufPlanes[0].frameROI.topLeft.x  = 0;
      interMediateBufDesc.bufPlanes[0].frameROI.topLeft.y  = 0;
      interMediateBufDesc.bufPlanes[0].frameROI.width  =
                            (intAlgHandle->activeImageWidth[levelCnt] -
                            (2U*FAST9_TI_BORDER_X))/8U;
      interMediateBufDesc.bufPlanes[0].frameROI.height =
                             intAlgHandle->activeImageHeight[levelCnt] -
                             (2U*FAST9_TI_BORDER_Y);
      interMediateBufDesc.bufPlanes[0].width =
                             interMediateBufDesc.bufPlanes[0].frameROI.width;
      if (bamStatus == BAM_S_SUCCESS )
      {
        bamStatus = FAST9_CORNER_DETECT_TI_graphDmaControl(
                                  &(intAlgHandle->fast9GraphMem),
                                  (*inBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER],
                                  &interMediateBufDesc,
                                  &fast9DmaCtrlArgs);
      }
      /*-----------------------------------------------------------------------*/
      /* Call execute function                                                 */
      /*-----------------------------------------------------------------------*/
      if (bamStatus == BAM_S_SUCCESS )
      {

        bamStatus =  FAST9_CORNER_DETECT_TI_execute(&(intAlgHandle->fast9GraphMem),
                              &inScratchArgs,
                              &outScratchArgs);
      }

      if ( bamStatus == BAM_S_SUCCESS )
      {
        binImg2ListDmaCtrlArgs.imgWidth  =
            intAlgHandle->activeBinImgWidth[levelCnt] - (2U * FAST9_TI_BORDER_X);
        binImg2ListDmaCtrlArgs.imgHeight =
            intAlgHandle->activeBinImgHeight[levelCnt] - (2U * FAST9_TI_BORDER_X);
        binImg2ListDmaCtrlArgs.imgPitch  =
            intAlgHandle->activeImageWidth[levelCnt] - (2U * FAST9_TI_BORDER_X);

        /* To ensure list is generated in raster order, processing block width is always set to image width */
        binImg2ListDmaCtrlArgs.blkWidth   =
            intAlgHandle->blockWidthBinImgToList[levelCnt];
        binImg2ListDmaCtrlArgs.blkHeight  =
            intAlgHandle->blockHeightBinImgToList[levelCnt];

        binImg2ListDmaCtrlArgs.dx = intAlgHandle->dx_binImg[levelCnt];

        binImg2ListDmaCtrlArgs.dy = intAlgHandle->dy_binImg[levelCnt];
        binImg2ListDmaCtrlArgs.level  = levelCnt;
        binImg2ListDmaCtrlArgs.pListSize = &numCorners;


        bamStatus = BIN_IMAGE_TO_LIST_TI_graphDmaControl(
                                  &(intAlgHandle->binToListGraphMem),
                                  &interMediateBufDesc,
                                  (*outBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER],
                                  &binImg2ListDmaCtrlArgs);


        /*--------------------------------------------------------------------------*/
        /*Params Update for Binary image to list kernel                             */
        /*--------------------------------------------------------------------------*/
        binImg2ListCtrlArgs.frameStartX     =
          (*inBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[levelCnt].frameROI.topLeft.x +
                                              FAST9_TI_BORDER_X +
                                              intAlgHandle->dx[levelCnt] +
                                              intAlgHandle->dx_binImg[levelCnt];

        binImg2ListCtrlArgs.frameStartY     =
          (*inBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[levelCnt].frameROI.topLeft.y +
                                              FAST9_TI_BORDER_Y +
                                              intAlgHandle->dy[levelCnt] +
                                              intAlgHandle->dy_binImg[levelCnt];

        binImg2ListCtrlArgs.blkWidth        = intAlgHandle->blockWidthBinImgToList[levelCnt];
        binImg2ListCtrlArgs.blkHeight       = intAlgHandle->blockHeightBinImgToList[levelCnt];
        binImg2ListCtrlArgs.blkStride       = (uint16_t)(8U*(((uint32_t)intAlgHandle->blockWidthBinImgToList[levelCnt]+7U)/8U));
        binImg2ListCtrlArgs.outputQformat   = 0;
        binImg2ListCtrlArgs.xyOrder         = BAM_BIN_IMAGE_TO_LIST_XY;

        if (bamStatus == BAM_S_SUCCESS )
        {
          bamStatus = BIN_IMAGE_TO_LIST_TI_graphControl(&(intAlgHandle->binToListGraphMem),
                                            &binImg2ListCtrlArgs);
        }

        if (bamStatus == BAM_S_SUCCESS )
        {
          /* Temporary workaround to force BAM_process() to skip executing the DMA control functions */

          bamStatus =  BIN_IMAGE_TO_LIST_TI_execute(&(intAlgHandle->binToListGraphMem),
                                                    &bamInArgs,
                                                    &bamOutArgs);
        }
      }

      if (bamStatus != BAM_S_SUCCESS)
      {
        status = IALG_EFAIL;
        PRINTF("RBRIEF_TI_execute() returned error!!!");
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      /*-----------------------------------------------------------------------*/
      /* iVISION doesn't allow multiple control output, so last utput will be  */
      /* available to user                                                     */
      /*-----------------------------------------------------------------------*/
      if (outArgs->size == sizeof (FAST9_CORNER_DETECT_TI_OutArgs))
      {
        fast9OutArgs = (FAST9_CORNER_DETECT_TI_OutArgs *)outArgs;
        fast9OutArgs->activeImgWidth[levelCnt]    = intAlgHandle->activeBinImgWidth[levelCnt];
        fast9OutArgs->activeImgHeight[levelCnt]   = intAlgHandle->activeBinImgHeight[levelCnt];
        fast9OutArgs->numCorners[levelCnt]        = (uint16_t)numCorners;
      }
    }
  }

Exit:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER] =
              (*inBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId ;

  outArgs->inFreeBufIDs[FAST9_CORNER_DETECT_TI_BUFDESC_IN_TOTAL] = 0 ;

  outArgs->outFreeBufIDs[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER] =
              (*outBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER]->bufferId ;

  outArgs->outFreeBufIDs[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_TOTAL] = 0 ;

  (*outBufDesc)[FAST9_CORNER_DETECT_TI_BUFDESC_OUT_LISTBUFFER]->bufPlanes[0].accessMask =
              IVISION_ACCESSMODE_HWA;

  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  FAST9_CORNER_DETECT_TI_activate(IALG_Handle handle)
{
  /* CHECK_MISRA("-11.4")  -> Disable rule 11.4  */
  /* handle is a extended structure from the base IALG_Handle structure.   */
  FAST9_CORNER_DETECT_TI_Handle algHandle = (FAST9_CORNER_DETECT_TI_Handle)(handle);
  /* RESET_MISRA("11.4")  -> Reset rule 11.4     */
  int32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == FAST9_GRAPH_OBJ_INT_MEMREC) || (i == BIN2LIST_GRAPH_OBJ_INT_MEMREC))
      {

        EDMA_UTILS_memcpy2D(algHandle->memRec[i].base,
                            algHandle->memRec[i-1].base,
                            algHandle->memRec[i].size,
                            1U,
                            0,
                            0);
      }

    }
    algHandle->algState = ALG_ACTIVE;
  }

  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do de-activation of algorithm. All scratch memory*/
/* are stoed to external memory in this                                     */
/* Refer algDeActivate function for details in ialg.h file                  */
/*--------------------------------------------------------------------------*/
void  FAST9_CORNER_DETECT_TI_deactivate(IALG_Handle handle)
{
  /* CHECK_MISRA("-11.4")  -> Disable rule 11.4  */
  /* handle is a extended structure from the base IALG_Handle structure.   */
  FAST9_CORNER_DETECT_TI_Handle algHandle = (FAST9_CORNER_DETECT_TI_Handle)(handle);
  /* RESET_MISRA("11.4")  -> Reset rule 11.4     */
  int32_t i;
  /*----------------------------------------------------------------*/
  /* Do De-activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == FAST9_GRAPH_OBJ_INT_MEMREC) || (i == BIN2LIST_GRAPH_OBJ_INT_MEMREC))
      {
          EDMA_UTILS_memcpy2D(algHandle->memRec[i-1].base,
                              algHandle->memRec[i].base,
                              algHandle->memRec[i].size,
                              1U,
                              0,
                              0);
      }

    }
    algHandle->algState = ALG_NOT_ACTIVE;
  }
  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_free(IALG_Handle handle, IALG_MemRec *memRec)
{
  int32_t status            = IALG_EOK;
  /* CHECK_MISRA("-11.4")  -> Disable rule 11.4  */
  /* handle is a extended structure from the base IALG_Handle structure.   */
  FAST9_CORNER_DETECT_TI_Handle algHandle = (FAST9_CORNER_DETECT_TI_Handle)(handle);
  /* RESET_MISRA("11.4")  -> Reset rule 11.4     */

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}
