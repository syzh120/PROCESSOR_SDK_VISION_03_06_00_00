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
*  @file       remap_merge_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for Remap Merge Applet
*  @version     0.0 (Jan 2014) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "remap_merge_alg_int.h"
#include "edma_utils_memcpy.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns REMAP_MERGE_TI_VISION_FXNS =
{
    {
        &REMAP_MERGE_TI_activate,  /* module ID */
        &REMAP_MERGE_TI_activate,              /* activate */
        &REMAP_MERGE_TI_alloc,                 /* algAlloc */
        NULL,                                 /* control (not suported) */
        &REMAP_MERGE_TI_deactivate,            /* deactivate */
        &REMAP_MERGE_TI_free,                  /* free */
        &REMAP_MERGE_TI_init,                  /* init */
        NULL,                                 /* moved (not suported) */
        &REMAP_MERGE_TI_numAlloc               /* algNumAlloc  */
    },
    &REMAP_MERGE_TI_process,
    &REMAP_MERGE_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns REMAP_MERGE_TI_IRES = {
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
int32_t REMAP_MERGE_TI_numAlloc(void)
{
    return NUM_REMAP_MERGE_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t REMAP_MERGE_TI_alloc(const IALG_Params *params,
                                        IALG_Fxns **parentFxns,
                                        IALG_MemRec       memRec[])
{
    int32_t status = IALG_EOK;

    BAM_GraphMemReq graphMemReqRemap;

    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    REMAP_MERGE_TI_getGraphMemReq(&graphMemReqRemap);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and REMAP_MERGE_GRAPH_OBJ_INT_MEMREC,      */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded                                      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.                                                   */
    /*  This persistent record will be used to backup the following scratch                                                       */
    /*  memory record during context saving when REMAP_MERGE_TI_deactivate                                         */
    /*  is called. Likewise when REMAP_MERGE_TI_activate it called,                                                              */
    /*  the content of the persistent memory record is copied back to the                                                     */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                                                            */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(REMAP_MERGE_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(REMAP_MERGE_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph:                                 */
    /* 1. REMAP_MERGE_GRAPH_OBJ_MEMREC        - To hold graph object in external memory           */
    /* 2. REMAP_MERGE_GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory      */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to                                     */
    /* speed up the processing - Main processing will work on internal memory                                     */
    /* instance and before any one else needing internal memory, deactivate                                         */
    /* has to be performed by caller to make sure the data is backed up to ext                                     */
    /* memory                                                                                                                                    */
    /*                                                                                                                                                  */
    /* 3. REMAP_MERGE_GRAPH_SCRATCH_MEMREC -                                                                       */
    /*  It is used as scratch memory during graph create time                                                               */
    /*  Scratch mem is currently placed in external memory.                                                                 */
    /*  For faster graph creation time, you can place it in internal memory                                             */
    /*                                                                                                                                                  */
    /* 4. REMAP_MERGE_GRAPH_CONTEXT_MEMREC                                                                           */
    /*  It is used to backup into external memory the graph's                                                                */
    /*  nodes internal memory records that are persistent.                                                                    */
    /*                                                                                                                                                  */
    /* 5. REMAP_MERGE_GRAPH_ARGS_MEMREC  -                                                                             */
    /*   It is used keep kernels arguments during graph create time                                                        */
    /*-------------------------------------------------------------------------*/

    memRec[REMAP_MERGE_GRAPH_OBJ_MEMREC].size           = graphMemReqRemap.graphObjSize;
    memRec[REMAP_MERGE_GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
    memRec[REMAP_MERGE_GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
    memRec[REMAP_MERGE_GRAPH_OBJ_MEMREC].alignment      = 4;

    /*
       REMAP_MERGE_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
       restored from external memory to faster internal memory when activate is called.
       */
    memRec[REMAP_MERGE_GRAPH_OBJ_INT_MEMREC].size       = graphMemReqRemap.graphObjSize;
    memRec[REMAP_MERGE_GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
    memRec[REMAP_MERGE_GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
    memRec[REMAP_MERGE_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

    memRec[REMAP_MERGE_GRAPH_SCRATCH_MEMREC].size       =  graphMemReqRemap.graphScratchSize;
    memRec[REMAP_MERGE_GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[REMAP_MERGE_GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
    memRec[REMAP_MERGE_GRAPH_SCRATCH_MEMREC].alignment  = 4;

    if(graphMemReqRemap.graphcontextSize)
    {
        /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
        /* The if() condition will currently never fail hence code is unreachable but  */
        /* as the implementation of the function changes, it will not be unreachable.   */
#ifdef DEBUG
        PRINTF("REMAP_MERGE_TI_alloc(): graphMemReqRemap.graphcontextSize is not zero. Set memRec for this memory.");
#endif
        status = IALG_EFAIL;
        /* RESET_MISRA("14.1")  -> Reset rule 14.1     */
    }

    memRec[REMAP_MERGE_GRAPH_ARGS_MEMREC].size          =  graphMemReqRemap.graphArgsSize;
    memRec[REMAP_MERGE_GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[REMAP_MERGE_GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
    memRec[REMAP_MERGE_GRAPH_ARGS_MEMREC].alignment     = 4;

    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t REMAP_MERGE_TI_init(IALG_Handle        handle,
                                      const IALG_MemRec  memRec[],
                                      IALG_Handle        parent,
                                      const IALG_Params *params)
{
    REMAP_MERGE_TI_Handle algHandle = (REMAP_MERGE_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;
    const REMAP_MERGE_TI_CreateParams *createParams = (const REMAP_MERGE_TI_CreateParams *)(const void *)params;
    REMAP_MERGE_TI_graphCreateParams graphCreateParams;
    int32_t status = IALG_EOK;
    int32_t bamStatus = BAM_S_SUCCESS;

    algHandle->ivision     = &REMAP_MERGE_TI_VISION_FXNS;
    algHandle->numMemRecs  = NUM_REMAP_MERGE_MEMRECS;
    memcpy(algHandle->memRec, memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    /*-----------------------------------------------------------------------*/
    /* Initialize the algorithm Handle. These values are needed for future iAlg calls                              */
    /*-----------------------------------------------------------------------*/
    algHandle->srcFormat   = createParams->remapParams.maps.srcFormat;
    algHandle->enableMerge = createParams->enableMerge;
    algHandle->dstFormat   = createParams->dstFormat;
    if(createParams->remapParams.maps.maxInputBlockSize != 0)
    {
        algHandle->enableTileApproach = 0;
        if(createParams->remapParams.maps.maxNumPixelsinTile != 0)
        {
#ifdef DEBUG
            PRINTF("Both maxInputBlockSize and maxNumPixelsinTile can't be positive value.");
#endif
            status = IALG_EFAIL;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        }
    }
    else
    {
        algHandle->enableTileApproach = 1;
    }
    /*-----------------------------------------------------------------------*/
    /* Initialize the Graph Create Params                                                                                          */
    /*-----------------------------------------------------------------------*/
    graphCreateParams.remapParams = createParams->remapParams;
    graphCreateParams.enableMerge = createParams->enableMerge;
    graphCreateParams.dstFormat   = createParams->dstFormat;

    /*-----------------------------------------------------------------------*/
    /* Call BAM Graph creation function with passing all the memories        */
    /*-----------------------------------------------------------------------*/
    algHandle->remapMergeGraphMem.graphObj      = memRec[REMAP_MERGE_GRAPH_OBJ_MEMREC].base;
    algHandle->remapMergeGraphMem.graphScratch  = memRec[REMAP_MERGE_GRAPH_SCRATCH_MEMREC].base;
    algHandle->remapMergeGraphMem.graphcontext  = NULL;
    algHandle->remapMergeGraphMem.graphArgs     = memRec[REMAP_MERGE_GRAPH_ARGS_MEMREC].base;

    bamStatus = REMAP_MERGE_TI_graphCreate(&(algHandle->remapMergeGraphMem),
                                        &graphCreateParams);

    if (bamStatus != BAM_S_SUCCESS)
    {
#ifdef DEBUG
      PRINTF("REMAP_MERGE_TI_graphCreate() returned error!!!");
#endif
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

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
int32_t REMAP_MERGE_TI_control(IVISION_Handle     handle,
                                           IALG_Cmd           cmd,
                                           const IALG_Params *inParams,
                                           IALG_Params       *outParams)
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
int32_t REMAP_MERGE_TI_process(IVISION_Handle   handle,
                                            IVISION_InBufs  *inBufs,
                                            IVISION_OutBufs *outBufs,
                                            IVISION_InArgs  *inArgs,
                                            IVISION_OutArgs *outArgs)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
    REMAP_MERGE_TI_Handle algHandle = (REMAP_MERGE_TI_Handle)(void *)handle;
    REMAP_MERGE_TI_Handle intAlgHandle;
    IBAMALG_InArgs        bamInArgs;
    IBAMALG_OutArgs       bamOutArgs;
    IVISION_BufDesc    *(*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_TOTAL];
    int32_t               status = IALG_EOK;
    int32_t               bamStatus = BAM_S_SUCCESS;
    uint8_t               sinkNodeId = 2U;

    inBufDesc  = (IVISION_BufDesc *(*)[REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[REMAP_MERGE_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if ( (inBufs->numBufs != 2) && (inBufs->numBufs != 4) )
    {
      status = IVISION_ERRORTYPE_NUM_INBUF_EXCEEDED;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    REMAP_MERGE_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle     = (REMAP_MERGE_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->remapMergeGraphMem.graphObj = intAlgHandle->memRec[REMAP_MERGE_GRAPH_OBJ_INT_MEMREC].base;

    /*-----------------------------------------------------------------------------*/
    /* BAM specific InArgs and OutArgs Assignment                                 */
    /*-----------------------------------------------------------------------------*/
    bamInArgs.size                  = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex            = 0;

    bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

    /* In case of Bounding Box Approach, Remap, Format Convert and Merge are all
            separate Nodes in the BAM Graph, whereas in Tile Approach, BAM is exposed to
            only one super Kernel named Remap and Merge. */
    if(intAlgHandle->enableTileApproach == 0)
    {
        if (intAlgHandle->srcFormat != intAlgHandle->dstFormat)
        {
           sinkNodeId++;
        }
        if(intAlgHandle->enableMerge == 1)
        {
           sinkNodeId++;
        }
    }
    bamStatus = REMAP_MERGE_TI_graphDmaControl(&(intAlgHandle->remapMergeGraphMem),
                                     inBufs, outBufs, sinkNodeId);
    /*-----------------------------------------------------------------------*/
    /* Call execute function                                                 */
    /*-----------------------------------------------------------------------*/
    if ( bamStatus == BAM_S_SUCCESS )
    {
      bamStatus =  REMAP_MERGE_TI_execute(&(intAlgHandle->remapMergeGraphMem),
                                        &bamInArgs, &bamOutArgs);
    }
    if ( bamStatus != BAM_S_SUCCESS )
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

Exit:
    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/

    outArgs->inFreeBufIDs[REMAP_MERGE_TI_BUFDESC_IN_IMAGEBUFFER] = (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId;
    outArgs->inFreeBufIDs[REMAP_MERGE_TI_BUFDESC_IN_LUTBUFFER]   = (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_LUTBUFFER]->bufferId;
    outArgs->inFreeBufIDs[REMAP_MERGE_TI_BUFDESC_IN_REMAP_TOTAL] = 0 ;

    if(algHandle->enableMerge == 1)
    {
      outArgs->inFreeBufIDs[REMAP_MERGE_TI_BUFDESC_IN_MERGEBUFFER] = (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_MERGEBUFFER]->bufferId;
      outArgs->inFreeBufIDs[REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER] = (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER]->bufferId;
      outArgs->inFreeBufIDs[REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL] = 0 ;
    }

    outArgs->outFreeBufIDs[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER] = (*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufferId ;
    outArgs->outFreeBufIDs[REMAP_MERGE_TI_BUFDESC_OUT_TOTAL]       = 0 ;

    (*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufPlanes[0].accessMask = IVISION_ACCESSMODE_HWA;
    (*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufPlanes[1].accessMask = IVISION_ACCESSMODE_HWA;

    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  REMAP_MERGE_TI_activate(IALG_Handle handle)
{
  REMAP_MERGE_TI_Handle algHandle = (REMAP_MERGE_TI_Handle)(void *)handle;
  uint32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i = 1U; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) || (i == REMAP_MERGE_GRAPH_OBJ_INT_MEMREC))
      {

        EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[i].base,
                            (const void *)algHandle->memRec[i - 1U].base,
                            (uint16_t)    algHandle->memRec[i].size,
                            (uint16_t)1,
                            (int16_t) 0,
                            (int16_t) 0);
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
void  REMAP_MERGE_TI_deactivate(IALG_Handle handle)
{
  REMAP_MERGE_TI_Handle algHandle = (REMAP_MERGE_TI_Handle)(void *)handle;
  uint32_t i;

  for(i = 1U; i < algHandle->numMemRecs; i++)
  {
    if((i == ALG_HANDLE_INT_MEMREC) || (i == REMAP_MERGE_GRAPH_OBJ_INT_MEMREC))
    {
        EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[i - 1U].base,
                            (const void *)algHandle->memRec[i].base,
                            (uint16_t)    algHandle->memRec[i].size,
                            (uint16_t)1,
                            (int16_t) 0,
                            (int16_t) 0);
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
int32_t REMAP_MERGE_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  REMAP_MERGE_TI_Handle algHandle = (REMAP_MERGE_TI_Handle)(void *)handle;
  int32_t status            = IALG_EOK;

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}
