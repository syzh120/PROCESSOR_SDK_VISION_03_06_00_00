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
*  @file       pyramid_lk_tracker_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for pyramid_lk_tracker applet
*  @version     0.0 (Dec 2013) : Base version.
*/

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "pyramid_lk_tracker_alg_int.h"
#include "edma_utils_memcpy.h"
#include "ti_file_io.h"

#define DEBUG (0)

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define PYRAMID_LK_TRACKER_TI_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns PYRAMID_LK_TRACKER_TI_VISION_FXNS =
{
  {
      &PYRAMID_LK_TRACKER_TI_activate, /* module ID */
      &PYRAMID_LK_TRACKER_TI_activate,           /* activate */
      &PYRAMID_LK_TRACKER_TI_alloc,              /* algAlloc */
      NULL,                                     /* control (not suported) */
      &PYRAMID_LK_TRACKER_TI_deactivate,         /* deactivate */
      &PYRAMID_LK_TRACKER_TI_free,               /* free */
      &PYRAMID_LK_TRACKER_TI_init,               /* init */
      NULL,                                     /* moved (not suported) */
      &PYRAMID_LK_TRACKER_TI_numAlloc            /* algNumAlloc  */
  },
  &PYRAMID_LK_TRACKER_TI_process,
  &PYRAMID_LK_TRACKER_TI_control
};

/**
* IRES interface of the algorithm
*/
const IRES_Fxns PYRAMID_LK_TRACKER_TI_IRES = {
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
XDAS_Int32 PYRAMID_LK_TRACKER_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
XDAS_Int32 PYRAMID_LK_TRACKER_TI_alloc(const IALG_Params *params,
                                                    IALG_Fxns **parentFxns,
                                                    IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;

  BAM_GraphMemReq graphMemReqLkTracker;

  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  LK_TRACKER_TI_getGraphMemReq(&graphMemReqLkTracker);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and LK_TRACKER_GRAPH_OBJ_INT_MEMREC,          */
  /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
  /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
  /*  This persistent record will be used to backup the following scratch        */
  /*  memory record during context saving when PYRAMID_LK_TRACKER_TI_deactivate */
  /*  is called. Likewise when PYRAMID_LK_TRACKER_TI_activate it called,        */
  /*  the content of the persistent memory record is copied back to the          */
  /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size          = sizeof(PYRAMID_LK_TRACKER_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment     = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(PYRAMID_LK_TRACKER_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

  /*-------------------------------------------------------------------------           */
  /* Below 5 memory records are used to store data related to the BAM graph:            */
  /* 1. LK_TRACKER_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
  /* 2. LK_TRACKER_GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
  /* GRAPH OBJECT has 2 instances - internal and external memory - it is to             */
  /* speed up the processing - Main processing will work on internal memory             */
  /* instance and before any one else needing internal memory, deacitavte               */
  /* has to be performed by caller to make sure the data is backed up to ext            */
  /* memory                                                                             */
  /*                                                                                    */
  /* 3. LK_TRACKER_GRAPH_SCRATCH_MEMREC -                                               */
  /*  It is used as scratch memory during graph create time                             */
  /*  Scratch mem is currently placed in external memory.                               */
  /*  For faster graph creation time, you can place it in internal memory               */
  /*                                                                                    */
  /* 4. LK_TRACKER_GRAPH_CONTEXT_MEMREC                                                 */
  /*  It is used to backup into external memory the graph's                             */
  /*  nodes internal memory records that are persistent.                                */
  /*                                                                                    */
  /* 5. LK_TRACKER_GRAPH_ARGS_MEMREC  -                                                 */
  /*   It is used keep kernels arguments during graph create time                       */
  /*-------------------------------------------------------------------------           */
  memRec[LK_TRACKER_GRAPH_OBJ_MEMREC].size           = graphMemReqLkTracker.graphObjSize;
  memRec[LK_TRACKER_GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[LK_TRACKER_GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
  memRec[LK_TRACKER_GRAPH_OBJ_MEMREC].alignment      = 4;

  /*
    LK_TRACKER_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
  */
  memRec[LK_TRACKER_GRAPH_OBJ_INT_MEMREC].size       = graphMemReqLkTracker.graphObjSize;
  memRec[LK_TRACKER_GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[LK_TRACKER_GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
  memRec[LK_TRACKER_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

  memRec[LK_TRACKER_GRAPH_SCRATCH_MEMREC].size       =  graphMemReqLkTracker.graphScratchSize;
  memRec[LK_TRACKER_GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[LK_TRACKER_GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[LK_TRACKER_GRAPH_SCRATCH_MEMREC].alignment  = 4;

  memRec[LK_TRACKER_GRAPH_CONTEXT_MEMREC].size       =  graphMemReqLkTracker.graphcontextSize;
  memRec[LK_TRACKER_GRAPH_CONTEXT_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[LK_TRACKER_GRAPH_CONTEXT_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[LK_TRACKER_GRAPH_CONTEXT_MEMREC].alignment  = 4;

  memRec[LK_TRACKER_GRAPH_ARGS_MEMREC].size          =  graphMemReqLkTracker.graphArgsSize;
  memRec[LK_TRACKER_GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[LK_TRACKER_GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[LK_TRACKER_GRAPH_ARGS_MEMREC].alignment     = 4;

  /*-------------------------------------------------------------------------*/
  /* Below should contain Applet specific memory request.                    */
  /*-------------------------------------------------------------------------*/
  memRec[LK_TRACKER_PREVXYLIST_MEMREC].size          =  NUM_POINTS_IN_DMEM*NUM_POINT_BUFFS_IN_DMEM*sizeof(uint32_t);
  memRec[LK_TRACKER_PREVXYLIST_MEMREC].space         =  (IALG_MemSpace) IALG_DARAM0;
  memRec[LK_TRACKER_PREVXYLIST_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[LK_TRACKER_PREVXYLIST_MEMREC].alignment     =  4;

  memRec[LK_TRACKER_CURRXYLIST_MEMREC].size          =  NUM_POINTS_IN_DMEM*NUM_POINT_BUFFS_IN_DMEM*sizeof(uint32_t);
  memRec[LK_TRACKER_CURRXYLIST_MEMREC].space         =  (IALG_MemSpace) IALG_DARAM0;
  memRec[LK_TRACKER_CURRXYLIST_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[LK_TRACKER_CURRXYLIST_MEMREC].alignment     =  4;

  memRec[LK_TRACKER_DMACTRL_MEMREC].size          =  sizeof(EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args);
  memRec[LK_TRACKER_DMACTRL_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[LK_TRACKER_DMACTRL_MEMREC].attrs         =  IALG_PERSIST;
  memRec[LK_TRACKER_DMACTRL_MEMREC].alignment     =  4;

  memRec[LK_TRACKER_DMACTRL_INT_MEMREC].size          =  sizeof(EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args);
  memRec[LK_TRACKER_DMACTRL_INT_MEMREC].space         =  (IALG_MemSpace) IALG_DARAM0;
  memRec[LK_TRACKER_DMACTRL_INT_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[LK_TRACKER_DMACTRL_INT_MEMREC].alignment     =  4;

  memRec[LK_TRACKER_KERNELSCTRL_MEMREC].size          =  4;
  memRec[LK_TRACKER_KERNELSCTRL_MEMREC].space         =  (IALG_MemSpace) IALG_DARAM0;
  memRec[LK_TRACKER_KERNELSCTRL_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[LK_TRACKER_KERNELSCTRL_MEMREC].alignment     =  4;

  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
XDAS_Int32 PYRAMID_LK_TRACKER_TI_init(IALG_Handle handle,
                                                   const IALG_MemRec memRec[],
                                                   IALG_Handle parent,
                                                   const IALG_Params * params)
{
  int32_t status = IALG_EOK;
  int32_t i;
  int32_t exitLoop = 0;

  const PYRAMID_LK_TRACKER_TI_CreateParams * createParams =
    (const PYRAMID_LK_TRACKER_TI_CreateParams*)(const void*)params;

  LK_TRACKER_TI_graphArgs *graphArgs;


  PYRAMID_LK_TRACKER_TI_Handle algHandle =
        (PYRAMID_LK_TRACKER_TI_Handle)(void*)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->lkTrackerGraphMem.graphObj      = memRec[LK_TRACKER_GRAPH_OBJ_MEMREC].base;
  algHandle->lkTrackerGraphMem.graphScratch  = memRec[LK_TRACKER_GRAPH_SCRATCH_MEMREC].base;
  algHandle->lkTrackerGraphMem.graphcontext  = memRec[LK_TRACKER_GRAPH_CONTEXT_MEMREC].base;
  algHandle->lkTrackerGraphMem.graphArgs     = memRec[LK_TRACKER_GRAPH_ARGS_MEMREC].base;

  graphArgs = (LK_TRACKER_TI_graphArgs*)algHandle->lkTrackerGraphMem.graphArgs;

  graphArgs->prevXYList      =  (uint16_t *)(void*)memRec[LK_TRACKER_PREVXYLIST_MEMREC].base;
  graphArgs->currXYList      =  (uint16_t *)(void*)memRec[LK_TRACKER_CURRXYLIST_MEMREC].base;
  graphArgs->dmaCtrlArgs     =  (uint32_t *)(void*)memRec[LK_TRACKER_DMACTRL_INT_MEMREC].base;
  graphArgs->kernelCtrlArgs  =  (uint32_t *)(void*)memRec[LK_TRACKER_KERNELSCTRL_MEMREC].base;

  status = LK_TRACKER_TI_graphCreate(&(algHandle->lkTrackerGraphMem),createParams);

  if (status != IALG_EOK)
  {
    PRINTF("PYRAMID_LK_TRACKER_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = &PYRAMID_LK_TRACKER_TI_VISION_FXNS;

  algHandle->numMemRecs   = NUM_MEMRECS;
  algHandle->numLevels    = createParams->numLevels;
  algHandle->imWidth      = createParams->imWidth  ;
  algHandle->imHeight     = createParams->imHeight ;
  algHandle->numKeyPoints = createParams->numKeyPoints ;
  for(i =0 ; ((i < algHandle->numLevels) && (exitLoop==0)); i++)
  {
    if((createParams->maxItersLK[i] > (uint16_t)PYRAMID_LK_TRACKER_TI_MAXITERATION) || (createParams->maxItersLK[i] < 1U))
    {
      status = IPYRAMID_LK_TRACKER_ERRORTYPE_MAXITERATION_EXCEEDED;
      exitLoop = 1;
    }
    if((createParams->searchRange[i] > (uint16_t)PYRAMID_LK_TRACKER_TI_MAX_SEARCH_RANGE) || (createParams->searchRange[i] < 1U))
    {
      status = IPYRAMID_LK_TRACKER_ERRORTYPE_SEARCH_RANGE_EXCEEDED;
      exitLoop = 1;
    }
    algHandle->maxItersLK[i]    = createParams->maxItersLK[i] ;
    algHandle->minErrValue[i]   = createParams->minErrValue[i] ;
    algHandle->searchRange[i]   = createParams->searchRange[i] ;
  }

  if(exitLoop != 1)
  {
    if((createParams->numLevels > PYRAMID_LK_TRACKER_TI_MAXLEVELS) || (createParams->numLevels < 1))
    {
      status = IPYRAMID_LK_TRACKER_ERRORTYPE_MAXLEVELS_EXCEEDED;
    }
    else
    {
    EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[LK_TRACKER_DMACTRL_INT_MEMREC-1].base,
                        (const void *)algHandle->memRec[LK_TRACKER_DMACTRL_INT_MEMREC].base,
                        (uint16_t)    algHandle->memRec[LK_TRACKER_DMACTRL_INT_MEMREC].size,
                        (uint16_t)1,
                        (int16_t) 0,
                        (int16_t) 0);
    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;
    }
  }

Exit:
  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
XDAS_Int32 PYRAMID_LK_TRACKER_TI_control(IVISION_Handle handle,
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
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type IVISION_Fxns : algProcess in order to be ASSIGNED IVISION_Fxns */
XDAS_Int32 PYRAMID_LK_TRACKER_TI_process(IVISION_Handle handle,
                                       IVISION_InBufs *inBufs,
                                       IVISION_OutBufs *outBufs,
                                       IVISION_InArgs *inArgs,
                                       IVISION_OutArgs *outArgs)
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
{
  PYRAMID_LK_TRACKER_TI_Handle algHandle = (PYRAMID_LK_TRACKER_TI_Handle)(void*)(handle);
  PYRAMID_LK_TRACKER_TI_Handle intAlgHandle;
  int32_t status            = IALG_EOK;
  int32_t j;
  uint32_t i;
  uint8_t numKeyPointsPerCall;

  IBAMALG_InArgs          bamInArgs;
  IBAMALG_OutArgs         bamOutArgs;

  uint16_t currBlkWidth;
  uint16_t currBlkHeight;

  BAM_Weight_Computation_Ctrl_Args *kernelCtrlArgs;
  PYRAMID_LK_TRACKER_TI_InArgs    *lkInArgs;
  PYRAMID_LK_TRACKER_TI_OutArgs   *lkOutArgs;

  EDMA_UTILS_pyramidlktracker_dma_ctrl_args bam_ctrl_args;
  uint8_t maxSearchRange;
  uint8_t searchWidth   ;
  uint8_t searchHeight  ;
  uint16_t searchMax     ;

  IVISION_BufDesc      *(*inBufDesc)[PYRAMID_LK_TRACKER_TI_EST_KEY_POINTS_BUF_IDX+1];
  IVISION_BufDesc      *(*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX+1];

  inBufDesc = (IVISION_BufDesc *(*)[PYRAMID_LK_TRACKER_TI_EST_KEY_POINTS_BUF_IDX+1])(void*)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX+1])(void*)outBufs->bufDesc;



  lkInArgs = (PYRAMID_LK_TRACKER_TI_InArgs    *)(void*)inArgs;
  lkOutArgs = (PYRAMID_LK_TRACKER_TI_OutArgs    *)(void*)outArgs;

  if ( inBufs->numBufs < 4 )
  {
    status = IPYRAMID_LK_TRACKER_ERRORTYPE_INSUFFICIENT_BUFFERS;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  if ( lkInArgs->numKeyPoints < 1 )
  {
    status = IPYRAMID_LK_TRACKER_ERRORTYPE_NO_KEY_POINTS;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if((lkInArgs->numLevels > PYRAMID_LK_TRACKER_TI_MAXLEVELS_PER_CALL)   || (lkInArgs->numLevels < 1))
  {
    status = IPYRAMID_LK_TRACKER_ERRORTYPE_NUMLEVELS_PER_CALL_EXCEEDED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if(lkInArgs->startLevel >= algHandle->numLevels)
  {
    status = IPYRAMID_LK_TRACKER_ERRORTYPE_START_LEVEL_EXCEEDED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if(lkInArgs->startLevel < (lkInArgs->numLevels-1))
  {
    status = IPYRAMID_LK_TRACKER_ERRORTYPE_INVALID_START_LEVEL_OR_NUMLEVELS;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  PYRAMID_LK_TRACKER_TI_activate((IALG_Handle)(void*)handle);

  intAlgHandle                              = (PYRAMID_LK_TRACKER_TI_Handle)(void*)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->lkTrackerGraphMem.graphObj      = intAlgHandle->memRec[LK_TRACKER_GRAPH_OBJ_INT_MEMREC].base;


  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;
  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);
  kernelCtrlArgs = (BAM_Weight_Computation_Ctrl_Args*)(void*)intAlgHandle->memRec[LK_TRACKER_KERNELSCTRL_MEMREC].base;

  bam_ctrl_args.cornerListInXY      = (uint8_t *)(void*)(*inBufDesc)[PYRAMID_LK_TRACKER_TI_IN_KEY_POINTS_BUF_IDX]->bufPlanes[0].buf;
  bam_ctrl_args.cornerListOutXY     = (uint8_t *)(void*)(*inBufDesc)[PYRAMID_LK_TRACKER_TI_EST_KEY_POINTS_BUF_IDX]->bufPlanes[0].buf;
  bam_ctrl_args.cornerListErrMeasure= (uint8_t *)(void*)(*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX]->bufPlanes[0].buf;

  maxSearchRange = LK_TRACKER_TI_FindMaxSearchRange(algHandle->searchRange, algHandle->numLevels);
  searchWidth    = maxSearchRange;
  searchHeight   = maxSearchRange;

  currBlkWidth  = ((searchWidth + (uint16_t)((uint16_t)VCOP_LK_PATCH_WIDTH/2U))*2U) + 1U;
  currBlkWidth  = (uint16_t)((currBlkWidth + (uint16_t)1U) & (uint16_t)(~(uint16_t)1U));
  currBlkHeight = ((searchHeight + (uint16_t)((uint16_t)VCOP_LK_PATCH_WIDTH/2U))*2U) + 1U;

  numKeyPointsPerCall = LK_TRACKER_TI_FindNumKeyPointsPerCall(currBlkWidth,currBlkHeight);

  bam_ctrl_args.numKeyPoints         = ((lkInArgs->numKeyPoints + (numKeyPointsPerCall-1U))/numKeyPointsPerCall)*numKeyPointsPerCall;
  bam_ctrl_args.numValidKeyPoints    = lkInArgs->numKeyPoints;

  bam_ctrl_args.sinkNodeParams.updateParams[0].extMemPtr =
    (uint8_t *)(void*)(*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_KEY_POINTS_BUF_IDX]->bufPlanes[0].buf;
  bam_ctrl_args.sinkNodeParams.updateParams[1].extMemPtr =
    (uint8_t *)(void*)(*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX]->bufPlanes[0].buf;

  i =  ((uint32_t)lkInArgs->numLevels-1U);
  for(j=0; j < lkInArgs->numLevels; j++)
  {

    bam_ctrl_args.srcNodeParams.updateParams[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX].extMemPtr =
      (uint8_t *)(void*)(*inBufDesc)[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX]->bufPlanes[i].buf;
    bam_ctrl_args.srcNodeParams.updateParams[PYRAMID_LK_TRACKER_TI_PREV_IMAGE_BUF_IDX].extMemPtr =
      (uint8_t *)(void*)(*inBufDesc)[PYRAMID_LK_TRACKER_TI_PREV_IMAGE_BUF_IDX]->bufPlanes[i].buf;

    bam_ctrl_args.srcNodeParams.updateParams[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX].extMemPtrStride =
      (*inBufDesc)[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX]->bufPlanes[i].width;
    bam_ctrl_args.srcNodeParams.updateParams[PYRAMID_LK_TRACKER_TI_PREV_IMAGE_BUF_IDX].extMemPtrStride =
      (*inBufDesc)[PYRAMID_LK_TRACKER_TI_PREV_IMAGE_BUF_IDX]->bufPlanes[i].width;

    bam_ctrl_args.imPitch              = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX]->bufPlanes[i].width;
    bam_ctrl_args.imWidth              = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX]->bufPlanes[i].frameROI.width;
    bam_ctrl_args.imHeight             = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX]->bufPlanes[i].frameROI.height;
    bam_ctrl_args.maxItersLK           = intAlgHandle->maxItersLK[i];
    bam_ctrl_args.minErrValue          = intAlgHandle->minErrValue[i];
    bam_ctrl_args.searchRange          = intAlgHandle->searchRange[i];
    searchMax = (bam_ctrl_args.imWidth < bam_ctrl_args.imHeight ? bam_ctrl_args.imWidth : bam_ctrl_args.imHeight);
    if(searchMax < VCOP_LK_MIN_IM_SIZE)
    {
      status = IPYRAMID_LK_TRACKER_ERRORTYPE_INSUFFICIENT_IM_SIZE;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if(currBlkWidth > searchMax)
    {
      bam_ctrl_args.searchRange = (uint16_t)((searchMax - (uint16_t)VCOP_LK_PATCH_WIDTH)/2U);
    }

    bam_ctrl_args.currLevel            = lkInArgs->startLevel - j;
    bam_ctrl_args.numValidKeyPoints    = lkInArgs->numKeyPoints;
    bam_ctrl_args.SADthreshold         = lkInArgs->SADthreshold;

    LK_TRACKER_TI_bamControl(&(intAlgHandle->lkTrackerGraphMem),&bam_ctrl_args);

    kernelCtrlArgs->currLevel         = lkInArgs->startLevel - j;
    /*-----------------------------------------------------------------------*/
    /* Call execute function                                                 */
    /*-----------------------------------------------------------------------*/

    status =  LK_TRACKER_TI_execute(&(intAlgHandle->lkTrackerGraphMem), &bamInArgs, &bamOutArgs);

    bam_ctrl_args.cornerListOutXY     = (uint8_t *)(void*)(*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_KEY_POINTS_BUF_IDX]->bufPlanes[0].buf;
    bam_ctrl_args.cornerListErrMeasure= (uint8_t *)(void*)(*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX]->bufPlanes[0].buf;

#if DEBUG
    {
      char FileName[200];
      char temp[20];
      TI_FILE * fp;
      int key;
      int currWidth  ;
      int currHeight ;
      char *numbers[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

      unsigned short * cornerListInXY = (unsigned short *)bam_ctrl_args.cornerListInXY;
      unsigned short * cornerListOutXY = (unsigned short *)bam_ctrl_args.cornerListOutXY;
      unsigned short * cornerListErrMeasure = (unsigned short *)bam_ctrl_args.cornerListErrMeasure;
      strcpy(FileName,"KeyPoints_out_Level_");
      strcat(FileName,numbers[kernelCtrlArgs->currLevel]);
      strcat(FileName,".txt");
      fp = FOPEN(FileName,"w+");
      for(key = 0; key < bam_ctrl_args.numKeyPoints ; key++)
      {
         FPRINTF(fp, "%8d, %8d, %8d, %8d, %8d\n",cornerListInXY[2*key], cornerListInXY[2*key+1], cornerListOutXY[2*key], cornerListOutXY[2*key+1], cornerListErrMeasure[key]);
      }
      FCLOSE(fp);

    }
#endif
    i--;
  }


  lkOutArgs->numValidPoints = lkInArgs->numKeyPoints - bam_ctrl_args.numInvalidPoints;




Exit:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[0]    = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_CURR_IMAGE_BUF_IDX]->bufferId ;
  outArgs->inFreeBufIDs[1]    = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_PREV_IMAGE_BUF_IDX]->bufferId ;
  outArgs->inFreeBufIDs[2]    = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_IN_KEY_POINTS_BUF_IDX]->bufferId ;
  outArgs->inFreeBufIDs[3]    = (*inBufDesc)[PYRAMID_LK_TRACKER_TI_EST_KEY_POINTS_BUF_IDX]->bufferId ;
  outArgs->inFreeBufIDs[4]    = 0 ;
  outArgs->outFreeBufIDs[0]   = (*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_KEY_POINTS_BUF_IDX]->bufferId ;
  outArgs->outFreeBufIDs[1]   = (*outBufDesc)[PYRAMID_LK_TRACKER_TI_OUT_ERR_MEASURE_BUF_IDX]->bufferId ;
  outArgs->outFreeBufIDs[2]   = 0 ;
  (*outBufDesc)[0]->bufPlanes[0].accessMask = IVISION_ACCESSMODE_HWA;
  (*outBufDesc)[1]->bufPlanes[0].accessMask = IVISION_ACCESSMODE_HWA;
  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
XDAS_Void  PYRAMID_LK_TRACKER_TI_activate(IALG_Handle handle)
{
  PYRAMID_LK_TRACKER_TI_Handle algHandle = (PYRAMID_LK_TRACKER_TI_Handle)(void*)(handle);
  int32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == LK_TRACKER_GRAPH_OBJ_INT_MEMREC) || (i == LK_TRACKER_DMACTRL_INT_MEMREC))
      {
        EDMA_UTILS_memcpy2D((void *)        algHandle->memRec[i].base,
                            (const void  *) algHandle->memRec[i-1].base,
                            (uint16_t)      algHandle->memRec[i].size,
                            (uint16_t)      1,
                            (int16_t)       0,
                            (int16_t)       0);
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
XDAS_Void  PYRAMID_LK_TRACKER_TI_deactivate(IALG_Handle handle)
{
  PYRAMID_LK_TRACKER_TI_Handle algHandle = (PYRAMID_LK_TRACKER_TI_Handle)(void*)(handle);
  int32_t i;
  for(i= 1; i < algHandle->numMemRecs; i++)
  {
    if((i == ALG_HANDLE_INT_MEMREC) ||(i == LK_TRACKER_GRAPH_OBJ_INT_MEMREC) || (i == LK_TRACKER_DMACTRL_INT_MEMREC))
    {
        EDMA_UTILS_memcpy2D((void *)       algHandle->memRec[i-1].base,
                            (const void  *)algHandle->memRec[i].base,
                            (uint16_t)     algHandle->memRec[i].size,
                            (uint16_t)     1,
                            (int16_t)      0,
                            (int16_t)      0);
    }
  }
  algHandle->algState = ALG_NOT_ACTIVE;
  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
XDAS_Int32 PYRAMID_LK_TRACKER_TI_free(IALG_Handle handle, IALG_MemRec *memRec)
{
  int32_t status            = IALG_EOK;
  PYRAMID_LK_TRACKER_TI_Handle algHandle = (PYRAMID_LK_TRACKER_TI_Handle)(void*)(handle);

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}
