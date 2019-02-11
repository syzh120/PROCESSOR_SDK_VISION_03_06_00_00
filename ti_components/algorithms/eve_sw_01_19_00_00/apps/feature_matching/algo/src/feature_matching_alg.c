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
*  @file        feature_matching_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for Feature
*               matching applet
*
*  @version     0.1 (Aug 2014) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "feature_matching_alg_int.h"
#include "edma_utils_memcpy.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns FEATURE_MATCHING_TI_VISION_FXNS =
{
  {
      &FEATURE_MATCHING_TI_activate, /* module ID */
      &FEATURE_MATCHING_TI_activate,           /* activate */
      &FEATURE_MATCHING_TI_alloc,              /* algAlloc */
      NULL,                                   /* control (not suported) */
      &FEATURE_MATCHING_TI_deactivate,         /* deactivate */
      &FEATURE_MATCHING_TI_free,               /* free */
      &FEATURE_MATCHING_TI_init,               /* init */
      NULL,                                   /* moved (not suported) */
      &FEATURE_MATCHING_TI_numAlloc            /* algNumAlloc  */
  },
  &FEATURE_MATCHING_TI_process,
  &FEATURE_MATCHING_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns FEATURE_MATCHING_TI_IRES = {
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
int32_t FEATURE_MATCHING_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}


/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t FEATURE_MATCHING_TI_alloc(const IALG_Params *params,
                      IALG_Fxns **parentFxns,
                      IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;
  BAM_GraphMemReq graphMemReq;

  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  FEATURE_MATCHING_TI_getGraphMemReq(&graphMemReq);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and GRAPH_OBJ_INT_MEMREC, which    */
  /*  are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded by a       */
  /*  persistent memory record in IALG_EXTERNAL of same size. This persistent    */
  /*  record will be used to backup the following scratch memory record during   */
  /*  context saving when FEATURE_MATCHING_TI_deactivate is called.  */
  /*  Likewise when FEATURE_MATCHING_TI_activate is called, the      */
  /*  content of the persistent memory record is copied back to the scratch      */
  /*  memory record in BAM_MEMSPACE_DMEM                                         */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size      = sizeof(FEATURE_MATCHING_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space     = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs     = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(FEATURE_MATCHING_TI_Obj);
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
int32_t FEATURE_MATCHING_TI_init(IALG_Handle handle,
                     const IALG_MemRec memRec[],
                     IALG_Handle parent,
                     const IALG_Params *params)
{
  int32_t status = IALG_EOK;
  int32_t bamStatus;
  const FEATURE_MATCHING_TI_CreateParams *createParams = (const FEATURE_MATCHING_TI_CreateParams*)(const void *)params;
  FEATURE_MATCHING_TI_graphCreateParams featureMatchingGraphCreateParams;

  FEATURE_MATCHING_TI_Handle algHandle = (FEATURE_MATCHING_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->graphMem.graphObj      = memRec[GRAPH_OBJ_MEMREC].base;
  algHandle->graphMem.graphScratch  = memRec[GRAPH_SCRATCH_MEMREC].base;
  algHandle->graphMem.graphcontext  = memRec[GRAPH_CONTEXT_MEMREC].base;
  algHandle->graphMem.graphArgs     = memRec[GRAPH_ARGS_MEMREC].base;

  if(createParams->descriptorLength > FEATURE_MATCHING_TI_MAX_DESCRIPTOR_LENGTH) {
    status = FEATURE_MATCHING_TI_ERRORTYPE_MAX_DESCRIPTOR_LEN_EXCEEDED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  featureMatchingGraphCreateParams.descriptorLength = createParams->descriptorLength;

  bamStatus = FEATURE_MATCHING_TI_graphCreate(&(algHandle->graphMem),
                            &featureMatchingGraphCreateParams);
  if(bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("FEATURE_MATCHING_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = &FEATURE_MATCHING_TI_VISION_FXNS;

  algHandle->descriptorLength = createParams->descriptorLength;

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
int32_t FEATURE_MATCHING_TI_control(IVISION_Handle handle,
                        IALG_Cmd cmd,
                        const IALG_Params *inParams,
                        IALG_Params *outParams)
{
  int32_t status = IALG_EOK;
  FEATURE_MATCHING_TI_Handle algHandle = (FEATURE_MATCHING_TI_Handle)(void *)(handle);
  FEATURE_MATCHING_TI_CtrlParams *params = (FEATURE_MATCHING_TI_CtrlParams*)(void *)outParams;
  uint16_t minNumDesc1PerIter, minNumDesc2PerIter;
  uint16_t numSegments1, numDesc1PerIter, numSegments2, numDesc2PerIter;

  if(cmd == FEATURE_MATCHING_TI_CONTROL_GET_BUF_SIZE)
  {

    if(algHandle->descriptorLength <= 32) {
      minNumDesc1PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MIN_NUM_FEAT;
      minNumDesc2PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MIN_NUM_FEAT;
      numDesc1PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT1;
      numDesc2PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT2;
    }
    else {
      minNumDesc1PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MIN_NUM_FEAT,
                               16U*((16384U/(2U+algHandle->descriptorLength))/16U));
      minNumDesc2PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MIN_NUM_FEAT,
                               2U*((16384U/(64U+algHandle->descriptorLength))/2U));
      numDesc1PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT1,
                           16U*((16384U/(2U+algHandle->descriptorLength))/16U));
      numDesc2PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT2,
                           2U*((16384U/(64U+algHandle->descriptorLength))/2U));
    }

    numSegments1 = ((params->numDescriptors1 + numDesc1PerIter) - (1U))/numDesc1PerIter;
    while(numSegments1 <= (params->numDescriptors1/minNumDesc1PerIter)) {
      if((params->numDescriptors1 % numSegments1) == 0) {
        break;
      }
      numSegments1++;
    }
    numDesc1PerIter = MAX((((params->numDescriptors1 + numSegments1) - (1U))/numSegments1),
      minNumDesc1PerIter);

    numSegments2 = ((params->numDescriptors2 + numDesc2PerIter) - (1U))/numDesc2PerIter;
    while(numSegments2 <= (params->numDescriptors2/minNumDesc2PerIter)) {
      if((params->numDescriptors2 % numSegments2) == 0) {
        break;
      }
      numSegments2++;
    }
    numDesc2PerIter = MAX((((params->numDescriptors2 + numSegments2) - (1U))/numSegments2),
      minNumDesc2PerIter);

    params->in1BufSize = algHandle->descriptorLength*(((params->numDescriptors1 +
      numDesc1PerIter) - (1U))/numDesc1PerIter)*numDesc1PerIter;

    params->in2BufSize = algHandle->descriptorLength*(((params->numDescriptors2 +
      numDesc2PerIter) - (1U))/numDesc2PerIter)*numDesc2PerIter;

    params->outBufSize = sizeof(uint16_t)*(((params->numDescriptors1 +
      numDesc1PerIter) - (1U))/numDesc1PerIter)*numDesc1PerIter;
  }

  return (status);
}


/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type IVISION_Fxns : algProcess in order to be ASSIGNED IVISION_Fxns */
int32_t FEATURE_MATCHING_TI_process(IVISION_Handle handle,
                        IVISION_InBufs  *inBufs,
                        IVISION_OutBufs *outBufs,
                        IVISION_InArgs  *inArgs,
                        IVISION_OutArgs *outArgs)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
  int32_t status = IALG_EOK;
  int32_t bamStatus;

  FEATURE_MATCHING_TI_Handle algHandle = (FEATURE_MATCHING_TI_Handle)(void *)(handle);
  FEATURE_MATCHING_TI_Handle intAlgHandle;

  FEATURE_MATCHING_TI_InArgs *featureMatchingInArgs = (FEATURE_MATCHING_TI_InArgs*)(void *)inArgs;
  FEATURE_MATCHING_TI_graphCtrlArgs featureMatchingCtrlArgs;

  IVISION_BufDesc    *(*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    *(*outBufDesc)[FEATURE_MATCHING_TI_BUFDESC_OUT_TOTAL];
  IBAMALG_InArgs          bamInArgs;
  IBAMALG_OutArgs         bamOutArgs;

  uint16_t numDesc1PerIter, numDesc2PerIter, minNumDesc1PerIter, minNumDesc2PerIter;
  uint16_t numSegments1, numSegments2;

  inBufDesc  = (IVISION_BufDesc *(*)[FEATURE_MATCHING_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[FEATURE_MATCHING_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  FEATURE_MATCHING_TI_activate((IALG_Handle)(void *)handle);

  intAlgHandle = (FEATURE_MATCHING_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->graphMem.graphObj = intAlgHandle->memRec[GRAPH_OBJ_INT_MEMREC].base;

  /*-----------------------------------------------------------------------------*/
  /* BAM specific In Args and OutArgs Assignment                                 */
  /*-----------------------------------------------------------------------------*/
  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;

  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

  if(intAlgHandle->descriptorLength <= 32) {
    minNumDesc1PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MIN_NUM_FEAT;
    minNumDesc2PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MIN_NUM_FEAT;
    numDesc1PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT1;
    numDesc2PerIter = FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT2;
  }
  else {
    minNumDesc1PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MIN_NUM_FEAT,
                            16U*((16384U/(2U+algHandle->descriptorLength))/16U));
    minNumDesc2PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MIN_NUM_FEAT,
                            2U*((16384U/(64U+algHandle->descriptorLength))/2U));
    numDesc1PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT1,
                         16U*((16384U/(2U+algHandle->descriptorLength))/16U));
    numDesc2PerIter = MIN(FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT2,
                         2U*((16384U/(64U+algHandle->descriptorLength))/2U));
  }

  featureMatchingCtrlArgs.numDescriptors1 =
    (*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1]->bufPlanes[0].frameROI.width/
    intAlgHandle->descriptorLength;

  featureMatchingCtrlArgs.numDescriptors2 =
    (*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2]->bufPlanes[0].frameROI.width/
    intAlgHandle->descriptorLength;

  numSegments1 = ((featureMatchingCtrlArgs.numDescriptors1 + numDesc1PerIter) - (1U))/numDesc1PerIter;
  while(numSegments1 <= (featureMatchingCtrlArgs.numDescriptors1/minNumDesc1PerIter)) {
    if((featureMatchingCtrlArgs.numDescriptors1 % numSegments1) == 0) {
      break;
    }
    numSegments1++;
  }
  featureMatchingCtrlArgs.numDesc1PerIter = MAX((((featureMatchingCtrlArgs.numDescriptors1 +
    numSegments1) - (1U))/numSegments1), minNumDesc1PerIter);

  numSegments2 = ((featureMatchingCtrlArgs.numDescriptors2 + numDesc2PerIter) - (1U))/numDesc2PerIter;
  while(numSegments2 <= (featureMatchingCtrlArgs.numDescriptors2/minNumDesc2PerIter)) {
    if((featureMatchingCtrlArgs.numDescriptors2 % numSegments2) == 0) {
      break;
    }
    numSegments2++;
  }
  featureMatchingCtrlArgs.numDesc2PerIter = MAX((((featureMatchingCtrlArgs.numDescriptors2 +
    numSegments2) - (1U)))/numSegments2, minNumDesc2PerIter);

  featureMatchingCtrlArgs.minDistanceThres = featureMatchingInArgs->minDistanceThres;
  featureMatchingCtrlArgs.matchConfidence  = featureMatchingInArgs->matchConfidence;

  status = FEATURE_MATCHING_TI_graphControl(&(intAlgHandle->graphMem),
               &featureMatchingCtrlArgs);
  if (status != IALG_EOK) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT_PROCESS;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  status = FEATURE_MATCHING_TI_dmaControl(&(intAlgHandle->graphMem),
            (*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1],
            (*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2],
            (*outBufDesc)[FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE],
            featureMatchingCtrlArgs.numDesc1PerIter,
            featureMatchingCtrlArgs.numDesc2PerIter);

  if (status!= IALG_EOK) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT_PROCESS;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /*-----------------------------------------------------------------------*/
  /* Call execute function  - it will do FEATURE_MATCHING compute          */
  /*-----------------------------------------------------------------------*/
  bamStatus = FEATURE_MATCHING_TI_execute(&(intAlgHandle->graphMem),
                &bamInArgs, &bamOutArgs);
  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("FEATURE_MATCHING_TI_execute() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT_PROCESS;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

EXIT_PROCESS:

  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1]
      = (*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE1]->bufferId;
  outArgs->inFreeBufIDs[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2]
      = (*inBufDesc)[FEATURE_MATCHING_TI_BUFDESC_IN_FEATURE2]->bufferId;
  outArgs->inFreeBufIDs[FEATURE_MATCHING_TI_BUFDESC_IN_TOTAL] = 0;

  outArgs->outFreeBufIDs[FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE]
      = (*outBufDesc)[FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE]->bufferId;
  outArgs->outFreeBufIDs[FEATURE_MATCHING_TI_BUFDESC_OUT_TOTAL]   = 0;

  (*outBufDesc)[FEATURE_MATCHING_TI_BUFDESC_OUT_CORRESPONDENCE]->bufPlanes[0].accessMask
      = IVISION_ACCESSMODE_HWA;

  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  FEATURE_MATCHING_TI_activate(IALG_Handle handle)
{
  FEATURE_MATCHING_TI_Handle algHandle = (FEATURE_MATCHING_TI_Handle)(void *)(handle);
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
void  FEATURE_MATCHING_TI_deactivate(IALG_Handle handle)
{
  FEATURE_MATCHING_TI_Handle algHandle = (FEATURE_MATCHING_TI_Handle)(void *)(handle);
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
int32_t FEATURE_MATCHING_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  int32_t status           = IALG_EOK;
  FEATURE_MATCHING_TI_Handle algHandle = (FEATURE_MATCHING_TI_Handle)(void *)(handle);

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}

