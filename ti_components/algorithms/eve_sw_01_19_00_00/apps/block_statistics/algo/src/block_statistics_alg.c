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


/*==========================================================================*/
/**
*  @file:      block_statistics_alg.c
*
*  @brief:     This file defines the XDAIS/iVISION functions for block
*              statistics operation
*
*  @version:   0.2 (Aug 2014) : Base version.
*/
/*==========================================================================*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "block_statistics_alg_int.h"
#include "edma_utils_memcpy.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns BLOCK_STATISTICS_TI_VISION_FXNS =
{
  {
      &BLOCK_STATS_TI_activate, /* module ID */
      &BLOCK_STATS_TI_activate,           /* activate */
      &BLOCK_STATS_TI_alloc,              /* algAlloc */
      NULL,                              /* control (not suported) */
      &BLOCK_STATS_TI_deactivate,         /* deactivate */
      &BLOCK_STATS_TI_free,               /* free */
      &BLOCK_STATS_TI_init,               /* init */
      NULL,                              /* moved (not suported) */
      &BLOCK_STATS_TI_numAlloc            /* algNumAlloc  */
  },
  &BLOCK_STATS_TI_process,
  &BLOCK_STATS_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns BLOCK_STATS_TI_IRES = {
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
int32_t BLOCK_STATS_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}


/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t BLOCK_STATS_TI_alloc(const IALG_Params *params,
                      IALG_Fxns **parentFxns,
                      IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;
  BAM_GraphMemReq graphMemReq;

  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  BLOCK_STATS_TI_getGraphMemReq(&graphMemReq);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and GRAPH_OBJ_INT_MEMREC, which    */
  /*  are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded by a       */
  /*  persistent memory record in IALG_EXTERNAL of same size. This persistent    */
  /*  record will be used to backup the following scratch memory record during   */
  /*  context saving when BLOCK_STATS_TI_deactivate is called. Likewise when     */
  /*  BLOCK_STATS_TI_activate is called, the content of the persistent memory    */
  /*  record is copied back to the scratch memory record in BAM_MEMSPACE_DMEM    */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size      = sizeof(BLOCK_STATS_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space     = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs     = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(BLOCK_STATS_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

  /*-------------------------------------------------------------------------*/
  /* Below 5 memory records are used to store data related to the BAM graph: */
  /* 1. GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
  /* 2. GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
  /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
  /* speed up the processing - Main processing will work on internal memory  */
  /* instance and before any one else needing internal memory, deacitavte    */
  /* has to be performed by caller to make sure the data is backed up to ext */
  /* memory                                                                  */
  /*                                                                         */
  /* 3. GRAPH_SCRATCH_MEMREC -                                               */
  /*  It is used as scratch memory during graph create time                  */
  /*  Scratch mem is currently placed in external memory.                    */
  /*  For faster graph creation time, you can place it in internal memory    */
  /*                                                                         */
  /* 4. GRAPH_CONTEXT_MEMREC                                                 */
  /*  It is used to backup into external memory the graph's                  */
  /*  nodes internal memory records that are persistent.                     */
  /*                                                                         */
  /* 5. GRAPH_ARGS_MEMREC  -                                                 */
  /*   It is used keep kernels arguments during graph create time            */
  /*-------------------------------------------------------------------------*/

  memRec[GRAPH_OBJ_MEMREC].size           = graphMemReq.graphObjSize;
  memRec[GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
  memRec[GRAPH_OBJ_MEMREC].alignment      = 4;

  /*
    GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is
    called.
  */
  memRec[GRAPH_OBJ_INT_MEMREC].size       = graphMemReq.graphObjSize;
  memRec[GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
  memRec[GRAPH_OBJ_INT_MEMREC].alignment  = 4;

  memRec[GRAPH_SCRATCH_MEMREC].size       = graphMemReq.graphScratchSize;
  memRec[GRAPH_SCRATCH_MEMREC].space      = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[GRAPH_SCRATCH_MEMREC].attrs      = IALG_SCRATCH;
  memRec[GRAPH_SCRATCH_MEMREC].alignment  = 4;

  memRec[GRAPH_CONTEXT_MEMREC].size       = graphMemReq.graphcontextSize;
  memRec[GRAPH_CONTEXT_MEMREC].space      = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[GRAPH_CONTEXT_MEMREC].attrs      = IALG_SCRATCH;
  memRec[GRAPH_CONTEXT_MEMREC].alignment  = 4;

  memRec[GRAPH_ARGS_MEMREC].size          = graphMemReq.graphArgsSize;
  memRec[GRAPH_ARGS_MEMREC].space         = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[GRAPH_ARGS_MEMREC].attrs         = IALG_SCRATCH;
  memRec[GRAPH_ARGS_MEMREC].alignment     = 4;

  return (status);
}


/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t BLOCK_STATS_TI_init(IALG_Handle handle,
                     const IALG_MemRec  memRec[],
                     IALG_Handle parent,
                     const IALG_Params *params)
{
  int32_t status = IALG_EOK;
  int32_t bamStatus = BAM_S_SUCCESS;
  const BLOCK_STATISTICS_TI_CreateParams *createParams = (const BLOCK_STATISTICS_TI_CreateParams*)(const void *)params;
  BLOCK_STATS_TI_graphCreateParams blockStatsGraphCreateParams;

  BLOCK_STATS_TI_Handle algHandle = (BLOCK_STATS_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->graphMem.graphObj      = memRec[GRAPH_OBJ_MEMREC].base;
  algHandle->graphMem.graphScratch  = memRec[GRAPH_SCRATCH_MEMREC].base;
  algHandle->graphMem.graphcontext  = memRec[GRAPH_CONTEXT_MEMREC].base;
  algHandle->graphMem.graphArgs     = memRec[GRAPH_ARGS_MEMREC].base;

  blockStatsGraphCreateParams.imageWidth        = createParams->imageWidth;
  blockStatsGraphCreateParams.imageHeight       = createParams->imageHeight;
  blockStatsGraphCreateParams.statBlockWidth    = createParams->statBlockWidth;
  blockStatsGraphCreateParams.statBlockHeight   = createParams->statBlockHeight;

  bamStatus = BLOCK_STATS_TI_graphCreate(&(algHandle->graphMem),
                            &blockStatsGraphCreateParams);

  if(bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("BLOCK_STATS_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = &BLOCK_STATISTICS_TI_VISION_FXNS;

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
int32_t BLOCK_STATS_TI_control(IVISION_Handle handle,
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
int32_t BLOCK_STATS_TI_process(IVISION_Handle handle,
                        IVISION_InBufs  *inBufs,
                        IVISION_OutBufs *outBufs,
                        IVISION_InArgs  *inArgs,
                        IVISION_OutArgs *outArgs)
{
/* RESET_MISRA("16.7")  -> Reset rule 16.7     */
  int32_t status = IALG_EOK;
  int32_t bamStatus;

  BLOCK_STATS_TI_Handle algHandle = (BLOCK_STATS_TI_Handle)(void *)(handle);
  BLOCK_STATS_TI_Handle intAlgHandle;

  IVISION_BufDesc    *(*inBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    *(*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL];
  IBAMALG_InArgs      bamInArgs;
  IBAMALG_OutArgs     bamOutArgs;

  inBufDesc  = (IVISION_BufDesc *(*)[BLOCK_STATISTICS_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  BLOCK_STATS_TI_activate((IALG_Handle)(void *)handle);

  intAlgHandle = (BLOCK_STATS_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->graphMem.graphObj = intAlgHandle->memRec[GRAPH_OBJ_INT_MEMREC].base;

  /*-----------------------------------------------------------------------------*/
  /* BAM specific In Args and OutArgs Assignment                                 */
  /*-----------------------------------------------------------------------------*/
  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;

  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

  status = BLOCK_STATS_TI_dmaControl(&(intAlgHandle->graphMem),
               (*inBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER],
               (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN],
               (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX],
               (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN],
               (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE]);
  if (status != IALG_EOK) {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT_PROCESS;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /*-----------------------------------------------------------------------*/
  /* Call execute function  - it will invoke median filter compute         */
  /*-----------------------------------------------------------------------*/
  bamStatus = BLOCK_STATS_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);
  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("BLOCK_STATS_TI_execute() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT_PROCESS;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

EXIT_PROCESS:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER]
      = (*inBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId;
  outArgs->inFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_IN_TOTAL] = 0;

  outArgs->outFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN]
      = (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN]->bufferId;
  (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN]->bufPlanes[0].accessMask
      = IVISION_ACCESSMODE_HWA;

  outArgs->outFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX]
      = (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX]->bufferId;
  (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX]->bufPlanes[0].accessMask
      = IVISION_ACCESSMODE_HWA;

  outArgs->outFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN]
      = (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN]->bufferId;
  (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN]->bufPlanes[0].accessMask
      = IVISION_ACCESSMODE_HWA;

  outArgs->outFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE]
      = (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE]->bufferId;
  (*outBufDesc)[BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE]->bufPlanes[0].accessMask
      = IVISION_ACCESSMODE_HWA;

  outArgs->outFreeBufIDs[BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL]   = 0;

  return status;
}


/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  BLOCK_STATS_TI_activate(IALG_Handle handle)
{
  BLOCK_STATS_TI_Handle algHandle = (BLOCK_STATS_TI_Handle)(void *)(handle);
  int32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == GRAPH_OBJ_INT_MEMREC))
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
void  BLOCK_STATS_TI_deactivate(IALG_Handle handle)
{
  BLOCK_STATS_TI_Handle algHandle = (BLOCK_STATS_TI_Handle)(void *)(handle);
  int32_t i;
  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) || (i == GRAPH_OBJ_INT_MEMREC))
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
int32_t BLOCK_STATS_TI_free(IALG_Handle handle, IALG_MemRec *memRec)
{
  int32_t status           = IALG_EOK;
  BLOCK_STATS_TI_Handle algHandle = (BLOCK_STATS_TI_Handle)(void *)(handle);

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}
