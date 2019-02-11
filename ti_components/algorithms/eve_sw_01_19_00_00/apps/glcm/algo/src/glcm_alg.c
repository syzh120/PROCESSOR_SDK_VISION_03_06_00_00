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
*  @file       glcm_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for Gray-level
*               co-occurrence matrix applet
*
*  @version     0.1 (Jan 2014) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "glcm_alg_int.h"
#include "edma_utils_memcpy.h"
#include "vcop_glcm_kernel.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns GLCM_TI_VISION_FXNS =
{
  {
      &GLCM_TI_activate, /* module ID */
      &GLCM_TI_activate,           /* activate */
      &GLCM_TI_alloc,              /* algAlloc */
      NULL,                          /* control (not suported) */
      &GLCM_TI_deactivate,         /* deactivate */
      &GLCM_TI_free,               /* free */
      &GLCM_TI_init,               /* init */
      NULL,                          /* moved (not suported) */
      &GLCM_TI_numAlloc            /* algNumAlloc  */
  },
  &GLCM_TI_process,
  &GLCM_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns GLCM_TI_IRES = {
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
* Maximum number of gray-levels (numLevels) that can be supported for GLCM analysis
* assuming 24kB of WBUF is available for storing the output buffer
*/
extern uint8_t GLCM_TI_maxGLCMLevels_8c[BAM_GLCM_MAX_NUM_DIRECTIONS];

/**
* Other exposed functions
*/
int32_t GLCM_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}


/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t GLCM_TI_alloc(const IALG_Params *params,
                      IALG_Fxns **parentFxns,
                      IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;
  BAM_GraphMemReq graphMemReq;

  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  GLCM_TI_getGraphMemReq(&graphMemReq);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and GRAPH_OBJ_INT_MEMREC, which    */
  /*  are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded by a       */
  /*  persistent memory record in IALG_EXTERNAL of same size. This persistent    */
  /*  record will be used to backup the following scratch memory record during   */
  /*  context saving when GLCM_TI_deactivate is called.  */
  /*  Likewise when GLCM_TI_activate is called, the      */
  /*  content of the persistent memory record is copied back to the scratch      */
  /*  memory record in BAM_MEMSPACE_DMEM                                         */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size      = sizeof(GLCM_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space     = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs     = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(GLCM_TI_Obj);
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
int32_t GLCM_TI_init(IALG_Handle handle,
                     const IALG_MemRec memRec[],
                     IALG_Handle parent,
                     const IALG_Params *params)
{
  int32_t status = IALG_EOK;
  int32_t bamStatus;
  const GLCM_TI_CreateParams *createParams = (const GLCM_TI_CreateParams*)(const void *)params;
  GLCM_TI_graphCreateParams glcmGraphCreateParams;

  GLCM_TI_Handle algHandle = (GLCM_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->graphMem.graphObj      = memRec[GRAPH_OBJ_MEMREC].base;
  algHandle->graphMem.graphScratch  = memRec[GRAPH_SCRATCH_MEMREC].base;
  algHandle->graphMem.graphcontext  = memRec[GRAPH_CONTEXT_MEMREC].base;
  algHandle->graphMem.graphArgs     = memRec[GRAPH_ARGS_MEMREC].base;

  if((createParams->numDirections > GLCM_MAX_NUM_DIRECTIONS) || (createParams->numDirections < 1)) {
    status = IGLCM_ERRORTYPE_MAXNUMDIRECTIONS_EXCEEDED;
    PRINTF("Ensure numDirections <= %d.\n", GLCM_MAX_NUM_DIRECTIONS);
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  if((2U*createParams->numDirections*createParams->numLevels*createParams->numLevels) > GLCM_TI_MAXMEMORY) {
    status = IGLCM_ERRORTYPE_INSUFFICIENT_MEMORY;
    PRINTF("Insufficient internal memory. Try to reduce numDirections or numLevels.\n");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  glcmGraphCreateParams.imageWidth = createParams->imageWidth;
  glcmGraphCreateParams.imageHeight = createParams->imageHeight;
  glcmGraphCreateParams.numLevels = createParams->numLevels;
  glcmGraphCreateParams.loPixelVal = createParams->loPixelVal;
  glcmGraphCreateParams.hiPixelVal = createParams->hiPixelVal;
  glcmGraphCreateParams.numDirections = createParams->numDirections;
  glcmGraphCreateParams.rowOffset = (int8_t (*)[])(void *)createParams->rowOffset;
  glcmGraphCreateParams.colOffset = (int8_t (*)[])(void *)createParams->colOffset;

  bamStatus = GLCM_TI_graphCreate(&(algHandle->graphMem),
                            &glcmGraphCreateParams);

  if(bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("GLCM_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  algHandle->scatterOffset = 4*((2*(((((glcmGraphCreateParams.numLevels*glcmGraphCreateParams.numLevels) + 1)/2) + 1)/4)) + 1);
  algHandle->numLevels = glcmGraphCreateParams.numLevels;
  algHandle->numDirections = glcmGraphCreateParams.numDirections;
  algHandle->outBufSize = 2*glcmGraphCreateParams.numDirections*glcmGraphCreateParams.numLevels*glcmGraphCreateParams.numLevels;
  algHandle->numChannels = (glcmGraphCreateParams.numLevels > GLCM_TI_maxGLCMLevels_8c[glcmGraphCreateParams.numDirections - 1]) ? 1 : 8;

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = &GLCM_TI_VISION_FXNS;

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
int32_t GLCM_TI_control(IVISION_Handle handle,
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
int32_t GLCM_TI_process(IVISION_Handle handle,
                        IVISION_InBufs  *inBufs,
                        IVISION_OutBufs *outBufs,
                        IVISION_InArgs  *inArgs,
                        IVISION_OutArgs *outArgs)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
  int32_t status = IALG_EOK;
  uint32_t n;
  void     *intGlcmBufAddr = NULL;
  uint16_t *glcm_8c_arr[GLCM_MAX_NUM_DIRECTIONS],
           *out_glcm_arr[GLCM_MAX_NUM_DIRECTIONS],
           *scratch_arr[GLCM_MAX_NUM_DIRECTIONS];
  uint16_t *scratch;
  uint16_t (*scatter_offsets)[8U];
  int32_t bamStatus;

  GLCM_TI_Handle algHandle = (GLCM_TI_Handle)(void *)(handle);
  GLCM_TI_Handle intAlgHandle;

  IVISION_BufDesc    *(*inBufDesc)[GLCM_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    *(*outBufDesc)[GLCM_TI_BUFDESC_OUT_TOTAL];
  IBAMALG_InArgs          bamInArgs;
  IBAMALG_OutArgs         bamOutArgs;

  inBufDesc  = (IVISION_BufDesc *(*)[GLCM_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[GLCM_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  GLCM_TI_activate((IALG_Handle)(void *)handle);

  intAlgHandle = (GLCM_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->graphMem.graphObj = intAlgHandle->memRec[GRAPH_OBJ_INT_MEMREC].base;

  /*-----------------------------------------------------------------------------*/
  /* BAM specific In Args and OutArgs Assignment                                 */
  /*-----------------------------------------------------------------------------*/
  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;

  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);
  status= GLCM_TI_dmaControl(&(intAlgHandle->graphMem), (*inBufDesc)[GLCM_TI_BUFDESC_IN_IMAGEBUFFER], (uint32_t *)(void *)&intGlcmBufAddr);

  if (status!= IALG_EOK) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT_PROCESS;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /*-----------------------------------------------------------------------*/
  /* Call execute function  - it will do GLCM compute                      */
  /*-----------------------------------------------------------------------*/
  bamStatus = GLCM_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);
  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("GLCM_TI_execute() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT_PROCESS;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /* Accumulate the output GLCM if 8 channel histogram was used during compute */
  if(algHandle->numChannels == 8U) {
#if !(VCOP_HOST_EMULATION)
    scratch = (uint16_t *)0x40050000;
    scatter_offsets = (uint16_t (*)[8U])0x40054000;
#else
    scratch = (uint16_t *)malloc(algHandle->numDirections*algHandle->scatterOffset*8);
    scatter_offsets = (uint16_t (*)[8U])malloc(8*sizeof(uint16_t));
#endif
    for(n = 0; n < 8U; n++) {
        (*scatter_offsets)[n] = (uint16_t)n*algHandle->scatterOffset;
    }
    for(n = 0; n < algHandle->numDirections; n++) {
        glcm_8c_arr[n]  = (uint16_t *)(*((uint8_t (*)[])intGlcmBufAddr) + (n*8U*((uint32_t)algHandle->numLevels)*
                                                             ((uint32_t)algHandle->numLevels)*(sizeof(uint16_t))));
        out_glcm_arr[n] = (uint16_t *)(*((uint8_t (*)[])intGlcmBufAddr) + (n*((uint32_t)algHandle->numLevels)*
                                                             ((uint32_t)algHandle->numLevels)*(sizeof(uint16_t))));
        scratch_arr[n]  = (uint16_t *)(*((uint8_t (*)[])(void *)scratch) + (n*8U*((uint32_t)algHandle->scatterOffset)));
    }

    vcop_accumulate_8c_glcm(glcm_8c_arr, out_glcm_arr, scratch_arr, *scatter_offsets, algHandle->numLevels,
                            algHandle->numDirections, algHandle->scatterOffset);
  }

  /* Copy GLCM output from internal memory to output buffer in external memory */
  EDMA_UTILS_memcpy2D(
    (*outBufDesc)[GLCM_TI_BUFDESC_OUT_GLCM]->bufPlanes[0].buf,
    intGlcmBufAddr,
    algHandle->outBufSize,
    1U, 0, 0);

EXIT_PROCESS:

  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[GLCM_TI_BUFDESC_IN_IMAGEBUFFER]
      = (*inBufDesc)[GLCM_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId;
  outArgs->inFreeBufIDs[GLCM_TI_BUFDESC_IN_TOTAL] = 0;

  outArgs->outFreeBufIDs[GLCM_TI_BUFDESC_OUT_GLCM]
      = (*outBufDesc)[GLCM_TI_BUFDESC_OUT_GLCM]->bufferId;
  outArgs->outFreeBufIDs[GLCM_TI_BUFDESC_OUT_TOTAL]   = 0;

  (*outBufDesc)[GLCM_TI_BUFDESC_OUT_GLCM]->bufPlanes[0].accessMask
      = IVISION_ACCESSMODE_HWA;

  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  GLCM_TI_activate(IALG_Handle handle)
{
  GLCM_TI_Handle algHandle = (GLCM_TI_Handle)(void *)(handle);
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
void  GLCM_TI_deactivate(IALG_Handle handle)
{
  GLCM_TI_Handle algHandle = (GLCM_TI_Handle)(void *)(handle);
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
int32_t GLCM_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  int32_t status           = IALG_EOK;
  GLCM_TI_Handle algHandle = (GLCM_TI_Handle)(void *)(handle);

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}

