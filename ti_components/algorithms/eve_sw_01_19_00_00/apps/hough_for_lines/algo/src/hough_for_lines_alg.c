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
*  @file       hough_for_lines_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for hough for lines applet
*  @version     0.0 (Dec 2013) : Base version.
*/

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "hough_for_lines_alg_int.h"
#include "edma_utils_memcpy.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns HOUGH_FOR_LINES_TI_VISION_FXNS =
{
  {
      &HOUGH_FOR_LINES_TI_activate, /* module ID */
      &HOUGH_FOR_LINES_TI_activate,    /* activate */
      &HOUGH_FOR_LINES_TI_alloc,       /* algAlloc */
      NULL,                          /* control (not suported) */
      &HOUGH_FOR_LINES_TI_deactivate,  /* deactivate */
      &HOUGH_FOR_LINES_TI_free,        /* free */
      &HOUGH_FOR_LINES_TI_init,        /* init */
      NULL,                          /* moved (not suported) */
      &HOUGH_FOR_LINES_TI_numAlloc     /* algNumAlloc  */
  },
  &HOUGH_FOR_LINES_TI_process,
  &HOUGH_FOR_LINES_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns HOUGH_FOR_LINES_TI_IRES = {
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
int32_t HOUGH_FOR_LINES_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t HOUGH_FOR_LINES_TI_alloc(const IALG_Params *params,
                                                    IALG_Fxns **parentFxns,
                                                    IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;

  BAM_GraphMemReq graphMem;
  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  HOUGH_FOR_LINES_TI_getGraphMemReq(&graphMem);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC,          */
  /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
  /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
  /*  This persistent record will be used to backup the following scratch        */
  /*  memory record during context saving when HOUGH_FOR_LINES_TI_deactivate */
  /*  is called. Likewise when HOUGH_FOR_LINES_TI_activate it called,        */
  /*  the content of the persistent memory record is copied back to the          */
  /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size          = sizeof(HOUGH_FOR_LINES_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment     = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(HOUGH_FOR_LINES_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC].size           = graphMem.graphObjSize;
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC].alignment      = 4;

  /*
    HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
  */
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC].size       = graphMem.graphObjSize;
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
  memRec[HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

  memRec[HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC].size       =  graphMem.graphScratchSize;
  memRec[HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC].alignment  = 4;

  memRec[HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC].size       =  graphMem.graphcontextSize;
  memRec[HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC].alignment  = 4;

  memRec[HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC].size          =  graphMem.graphArgsSize;
  memRec[HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC].alignment     = 4;

  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t HOUGH_FOR_LINES_TI_init(IALG_Handle handle,
                            const IALG_MemRec memRec[],
                            IALG_Handle parent,
                            const IALG_Params * params)
{
  int32_t status = IALG_EOK;
  int32_t bamStatus;

  HOUGH_FOR_LINES_TI_Handle algHandle =
        (HOUGH_FOR_LINES_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->graphMem.graphObj      = memRec[HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC].base;
  algHandle->graphMem.graphScratch  = memRec[HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC].base;
  algHandle->graphMem.graphcontext  = memRec[HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC].base;
  algHandle->graphMem.graphArgs     = memRec[HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC].base;

  bamStatus = HOUGH_FOR_LINES_TI_graphCreate(&(algHandle->graphMem),NULL);

  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("HOUGH_FOR_LINES_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = &HOUGH_FOR_LINES_TI_VISION_FXNS;

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
int32_t HOUGH_FOR_LINES_TI_control(IVISION_Handle handle,
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
int32_t HOUGH_FOR_LINES_TI_process(IVISION_Handle handle,
                                       IVISION_InBufs *inBufs,
                                       IVISION_OutBufs *outBufs,
                                       IVISION_InArgs *inArgs,
                                       IVISION_OutArgs *outArgs)
{
/* RESET_MISRA("16.7")  -> Reset rule 16.7     */

  HOUGH_FOR_LINES_TI_Handle algHandle = (HOUGH_FOR_LINES_TI_Handle)(void *)(handle);
  HOUGH_FOR_LINES_TI_Handle intAlgHandle;
  int32_t status            = IALG_EOK;
  int32_t bamStatus = BAM_S_SUCCESS;
  uint8_t * ptrToList;
  uint32_t (*currPtrToList)[HOUGH_FOR_LINES_MAX_LIST_SIZE];
  uint8_t * ptrToVotedRhoThetaSpace;
  IBAMALG_InArgs          bamInArgs;
  IBAMALG_OutArgs         bamOutArgs;
  uint16_t                lastBlockSize = 0;
  uint16_t                numListBlocks;
  uint8_t                 listCount;
  HOUGH_FOR_LINES_InArgs  *houghLineInArgs;

  IVISION_BufDesc    *(*inBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    *(*outBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL];


  inBufDesc  = (IVISION_BufDesc *(*)[HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  if ( inBufs->numBufs != 1 )
  {
    status = IVISION_ERRORTYPE_NUM_INBUF_EXCEEDED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if ( inArgs->size != sizeof(HOUGH_FOR_LINES_InArgs))
  {
    status = IALG_EFAIL;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  houghLineInArgs = (HOUGH_FOR_LINES_InArgs *)(void *)inArgs;

  if (houghLineInArgs->rhoMaxLength > HOUGH_FOR_LINES_TI_MAXRHOLENGTH )
  {
    status = IHOUGH_FOR_LINES_ERRORTYPE_MAXRHOLENGTH_EXCEEDED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if ( (houghLineInArgs->thetaStart > 360U) || (houghLineInArgs->thetaEnd > 360U))
  {
    status = IHOUGH_FOR_LINES_ERRORTYPE_THETA_BEYOND_RANGE;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if ( houghLineInArgs->thetaStart > houghLineInArgs->thetaEnd )
  {
   status = IHOUGH_FOR_LINES_ERRORTYPE_INVALID_THETA_START_END;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
   goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/

  HOUGH_FOR_LINES_TI_activate((IALG_Handle)(void *)handle);

  intAlgHandle                      = (HOUGH_FOR_LINES_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->graphMem.graphObj   = intAlgHandle->memRec[HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC].base;

  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;

  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

  ptrToList = (uint8_t *)(*inBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST]->bufPlanes[0].buf;
  ptrToVotedRhoThetaSpace = (uint8_t *)(*outBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE]->bufPlanes[0].buf;

  numListBlocks = houghLineInArgs->listSize / (uint16_t)HOUGH_FOR_LINES_MAX_LIST_SIZE;

  lastBlockSize = houghLineInArgs->listSize % (uint16_t)HOUGH_FOR_LINES_MAX_LIST_SIZE;

  currPtrToList = (uint32_t (*)[HOUGH_FOR_LINES_MAX_LIST_SIZE])(void *)ptrToList;

  for ( listCount = 0 ; listCount < numListBlocks; listCount++)
  {

    bamStatus = HOUGH_FOR_LINES_TI_graphDmaControl(&(intAlgHandle->graphMem),
                                        houghLineInArgs,
                                        (uint8_t *) (void *) &(*currPtrToList)[0],
                                        ptrToVotedRhoThetaSpace,
                                        HOUGH_FOR_LINES_MAX_LIST_SIZE);

    currPtrToList = (uint32_t (*)[HOUGH_FOR_LINES_MAX_LIST_SIZE])(void *) &((*currPtrToList)[HOUGH_FOR_LINES_MAX_LIST_SIZE]);

    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus =HOUGH_FOR_LINES_TI_graphKernelControl(&(intAlgHandle->graphMem),
                                              houghLineInArgs,
                                              HOUGH_FOR_LINES_MAX_LIST_SIZE);
    }

    /*-----------------------------------------------------------------------*/
    /* Call execute function                                                 */
    /*-----------------------------------------------------------------------*/
    if (bamStatus == BAM_S_SUCCESS)
    {
      bamStatus =  HOUGH_FOR_LINES_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);
    }

    if (bamStatus != BAM_S_SUCCESS)
    {
      status = IALG_EFAIL;
      PRINTF("HOUGH_FOR_LINES_TI_process() returned error!!!");
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
  }

  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
  /* bamStatus will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
    will never occur.*/
  if ( (lastBlockSize != 0) && (bamStatus == BAM_S_SUCCESS) )
  {
  /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
      bamStatus = HOUGH_FOR_LINES_TI_graphDmaControl(&(intAlgHandle->graphMem),
                                        houghLineInArgs,
                                        (uint8_t *) (void *) &(*currPtrToList)[0],
                                        ptrToVotedRhoThetaSpace,
                                        lastBlockSize);
      if (bamStatus == BAM_S_SUCCESS)
      {
        bamStatus =HOUGH_FOR_LINES_TI_graphKernelControl(&(intAlgHandle->graphMem),
                                                houghLineInArgs,
                                                (uint16_t)ALIGN_2SIMD((uint32_t)lastBlockSize));
      }

      if (bamStatus == BAM_S_SUCCESS)
      {
        bamStatus =  HOUGH_FOR_LINES_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);
      }

      if (bamStatus != BAM_S_SUCCESS)
      {
        status = IALG_EFAIL;
        PRINTF("HOUGH_FOR_LINES_TI_process() returned error!!!");
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
  }
Exit:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST] =
            (*inBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST]->bufferId ;
  outArgs->inFreeBufIDs[HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL]    = 0 ;

  outArgs->outFreeBufIDs[HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE]   =
            (*outBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE]->bufferId ;
  outArgs->outFreeBufIDs[HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL]   = 0 ;

  (*outBufDesc)[HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  HOUGH_FOR_LINES_TI_activate(IALG_Handle handle)
{
  HOUGH_FOR_LINES_TI_Handle algHandle = (HOUGH_FOR_LINES_TI_Handle)(void *)(handle);
  int32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC))
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
void  HOUGH_FOR_LINES_TI_deactivate(IALG_Handle handle)
{
  HOUGH_FOR_LINES_TI_Handle algHandle = (HOUGH_FOR_LINES_TI_Handle)(void *)(handle);
  int32_t i;
  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC))
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
int32_t HOUGH_FOR_LINES_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  int32_t status            = IALG_EOK;
  HOUGH_FOR_LINES_TI_Handle algHandle = (HOUGH_FOR_LINES_TI_Handle)(void *)(handle);

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}

