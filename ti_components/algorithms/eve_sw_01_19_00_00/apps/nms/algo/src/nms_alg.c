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
 *  @file       nms_alg.c
 *
 *  @brief       This file defines the XDAIS/iVISION functions for nms  applet
 *  @version     0.0 (Aug 2014) : Base version.
 */

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "nms_alg_int.h"
#include "edma_utils_memcpy.h"
#include "evestarterware.h"


/**
 * IVISION interface of the algorithm
 */
const IVISION_Fxns NMS_TI_VISION_FXNS =
{
        {
                &NMS_TI_activate, /* module ID */
                &NMS_TI_activate,    /* activate */
                &NMS_TI_alloc,       /* algAlloc */
                NULL,                          /* control (not suported) */
                &NMS_TI_deactivate,  /* deactivate */
                &NMS_TI_free,        /* free */
                &NMS_TI_init,        /* init */
                NULL,                          /* moved (not suported) */
                &NMS_TI_numAlloc     /* algNumAlloc  */
        },
        &NMS_TI_process,
        &NMS_TI_control
};


/**
 * IRES interface of the algorithm
 */
const IRES_Fxns NMS_TI_IRES = {
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
int32_t NMS_TI_numAlloc(void)
{
    return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t NMS_TI_alloc(const IALG_Params *params,
        IALG_Fxns **parentFxns,
        IALG_MemRec memRec[])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqFilter2D;
    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    NMS_TI_getGraphMemReq(&graphMemReqFilter2D);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when NMS_TI_deactivate */
    /*  is called. Likewise when NMS_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(NMS_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(NMS_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. NMS_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. NMS_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. NMS_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. NMS_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. NMS_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[NMS_GRAPH_OBJ_MEMREC].size  = graphMemReqFilter2D.graphObjSize;
    memRec[NMS_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[NMS_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[NMS_GRAPH_OBJ_MEMREC].alignment      = 4;

    /*
    NMS_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[NMS_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqFilter2D.graphObjSize;
    memRec[NMS_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[NMS_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[NMS_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

    memRec[NMS_GRAPH_SCRATCH_MEMREC].size  = graphMemReqFilter2D.graphScratchSize;
    memRec[NMS_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[NMS_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[NMS_GRAPH_SCRATCH_MEMREC].alignment  = 4;

    memRec[NMS_GRAPH_CONTEXT_MEMREC].size  = graphMemReqFilter2D.graphcontextSize;
    memRec[NMS_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[NMS_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[NMS_GRAPH_CONTEXT_MEMREC].alignment  = 4;

    memRec[NMS_GRAPH_ARGS_MEMREC].size  = graphMemReqFilter2D.graphArgsSize;
    memRec[NMS_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[NMS_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[NMS_GRAPH_ARGS_MEMREC].alignment     = 4;

    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t NMS_TI_init(IALG_Handle handle,
        const IALG_MemRec memRec[],
        IALG_Handle parent,
        const IALG_Params * params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;

    NMS_TI_graphCreateParams    nmsCreateParams;

    NMS_TI_Handle algHandle =
            (NMS_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

    algHandle->nmsGraphMem.graphObj      = memRec[NMS_GRAPH_OBJ_MEMREC].base;
    algHandle->nmsGraphMem.graphScratch  = memRec[NMS_GRAPH_SCRATCH_MEMREC].base;
    algHandle->nmsGraphMem.graphcontext  = memRec[NMS_GRAPH_CONTEXT_MEMREC].base;
    algHandle->nmsGraphMem.graphArgs     = memRec[NMS_GRAPH_ARGS_MEMREC].base;



    nmsCreateParams.inmsCreateParams = (const NMS_TI_CreateParams*)(const void *)params;
    algHandle->createParams = *(nmsCreateParams.inmsCreateParams);

    bamStatus = NMS_TI_graphCreate(&(algHandle->nmsGraphMem),&nmsCreateParams);

    if ( bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    algHandle->numMemRecs  = NUM_MEMRECS;
    memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
    algHandle->ivision = &NMS_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;

    Exit:
    return (status);
}

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */


/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t NMS_TI_control(IVISION_Handle handle,
        IALG_Cmd cmd,
        const IALG_Params *inParams,
        IALG_Params *outParams)
{
  NMS_TI_Handle algHandle = (NMS_TI_Handle)(void *)(handle);
  const NMS_TI_ControlInArgs * ctrlInArgs = (const NMS_TI_ControlInArgs*)(const void *) inParams;
  NMS_TI_ControlOutArgs * ctrlOutArgs= ( NMS_TI_ControlOutArgs*)(void *) outParams;

  int32_t status = IALG_EOK;

  uint16_t k = 1U;
  uint16_t inImageWidth;
  uint16_t inImageHeight;
  uint16_t effImageWidth;
  uint16_t effImageHeight;
  uint16_t inBlockSize;
  uint16_t outBlockSize;
  uint16_t minBlockHeight;
  uint16_t maxBlockHeight;
  uint16_t  windowWidth;
  uint16_t  windowHeight;
  uint16_t  blockWidth;
  uint16_t  blockHeight;
  uint8_t   elemSize;
  uint16_t  maxInBlockSize;
  uint16_t  maxOutBlockSize;

  IVISION_BufDesc    *(*inBufDesc)[NMS_TI_BUFDESC_IN_TOTAL];

  inBufDesc  = (IVISION_BufDesc *(*)[NMS_TI_BUFDESC_IN_TOTAL])(void *)ctrlInArgs->imageBuf->bufDesc;

  elemSize = algHandle->createParams.inputByteDepth;
  windowWidth  = ctrlInArgs->windowWidth;
  windowHeight = ctrlInArgs->windowHeight;

  inImageWidth  = (uint16_t)(*inBufDesc)[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width / (uint16_t)elemSize;
  inImageHeight = (uint16_t)(*inBufDesc)[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height;

  effImageWidth  = inImageWidth - (windowWidth - 1U);
  effImageHeight = inImageHeight - (windowHeight - 1U);

  if ( (effImageWidth % 8U) != 0 )
  {
    status = NMS_TI_ERRORTYPE_WIDTH_NON_MULTIPLE_OF_8;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if ( effImageWidth > BIN_IMAGE_TO_LIST_MAX_BLK_WIDTH)
  {
    status = NMS_TI_ERRORTYPE_IMAGE_DIMENSION_UNSUPPORTED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }


  minBlockHeight = 16U;


  maxInBlockSize  =  (uint16_t)BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE * (uint16_t)elemSize;
  maxOutBlockSize =  (uint16_t)BIN_IMAGE_TO_LIST_MAX_PIXELS * sizeof(uint32_t);


  maxBlockHeight = ( maxOutBlockSize * (windowWidth * windowHeight) ) /(  effImageWidth * sizeof(uint32_t)  );

  k = 1U;

  while (1)
  {
    blockWidth = effImageWidth / k;
    blockWidth = CEIL( blockWidth , 8U);
    blockHeight = minBlockHeight;

    inBlockSize = (CEIL(blockWidth + (windowWidth - 1U) , 16U))* (blockHeight + (windowHeight - 1U))* elemSize;

    if ( inBlockSize < maxInBlockSize)
    {
      break;
    }
    k += 1U;

  }

  ctrlOutArgs->effectiveImageWidth = k * blockWidth;
  k= 1U;

  blockHeight = effImageHeight;

  while (blockHeight >= minBlockHeight)
  {
    blockHeight = effImageHeight / k;

    if ( (effImageHeight % k) == 0 )
    {
      inBlockSize = (CEIL(blockWidth + (windowWidth - 1U) , 16U))* (blockHeight + (windowHeight - 1U))* elemSize;
      outBlockSize = (effImageWidth * blockHeight * sizeof (uint32_t)) / (windowWidth * windowHeight) ;
      if ( ( inBlockSize < maxInBlockSize ) && ( outBlockSize < maxOutBlockSize ) && ( blockHeight < maxBlockHeight ) && ( (blockHeight % 2U) == 0))
      {
        break;
      }
    }
    k += 1U;

  }

  if ( blockHeight < minBlockHeight )
  {
    status = NMS_TI_ERRORTYPE_IMAGE_DIMENSION_UNSUPPORTED;
  }
  else
  {
    ctrlOutArgs->effectiveImageHeight = k * blockHeight;

    algHandle->blockWidth  = blockWidth;
    algHandle->blockHeight = blockHeight;
  }

Exit:
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
int32_t NMS_TI_process(IVISION_Handle handle,
        IVISION_InBufs *inBufs,
        IVISION_OutBufs *outBufs,
        IVISION_InArgs *inArgs,
        IVISION_OutArgs *outArgs)
{
/* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    NMS_TI_Handle algHandle = (NMS_TI_Handle)(void *)(handle);
    NMS_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    NMS_TI_OutArgs         *nmsOutArgs;
    NMS_TI_InArgs          *nmsInArgs;
    uint16_t                inImageWidth;

    IVISION_BufDesc    *(*inBufDesc)[NMS_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[NMS_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[NMS_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[NMS_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    if ( inBufs->numBufs < 1 )
    {
        status = IVISION_ERRORTYPE_NUM_INBUF_LESS;

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    if (inArgs->size != sizeof(NMS_TI_InArgs))
    {
      status = IALG_EFAIL;

      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if (outArgs->size != sizeof(NMS_TI_OutArgs))
    {
      status = IALG_EFAIL;

      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    nmsOutArgs = (NMS_TI_OutArgs *)(void *)outArgs;
    nmsInArgs  = (NMS_TI_InArgs *)(void *)inArgs;

    inImageWidth =  (*inBufDesc)[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width / algHandle->createParams.inputByteDepth;

    if ( ((  (inImageWidth - (uint16_t)nmsInArgs->windowWidth) + (uint16_t)1 )% 8U ) != 0 )
    {
      status = NMS_TI_ERRORTYPE_WIDTH_NON_MULTIPLE_OF_8;

      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

    }

    if (( (inImageWidth - (uint16_t)nmsInArgs->windowWidth) + (uint16_t)1) > BIN_IMAGE_TO_LIST_MAX_BLK_WIDTH)
    {
      status = NMS_TI_ERRORTYPE_IMAGE_DIMENSION_UNSUPPORTED;

      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    NMS_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (NMS_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->nmsGraphMem.graphObj      =
            intAlgHandle->memRec[NMS_GRAPH_OBJ_INT_MEMREC].base;

    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);

    bamStatus = NMS_TI_dmaControl(&(intAlgHandle->nmsGraphMem),
                                   nmsInArgs->windowWidth,
                                   nmsInArgs->windowHeight,
                                   intAlgHandle->createParams.inputByteDepth,
                                   intAlgHandle->blockWidth,
                                   intAlgHandle->blockHeight,
                                   (*inBufDesc)[NMS_TI_BUFDESC_IN_IMAGEBUFFER],
                                   (*outBufDesc)[NMS_TI_BUFDESC_OUT_LIST_XY],
                                   (uint8_t *)(void *)&nmsOutArgs->numListPoints
                                   );

    if (bamStatus != BAM_S_SUCCESS) {
        status = IALG_EFAIL;
        PRINTF("NMS_TI_dmaControl() returned error\n");

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    bamStatus = NMS_TI_kernelControl(&(intAlgHandle->nmsGraphMem),
                                      nmsInArgs,
                                      (*inBufDesc)[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width ,
                                      intAlgHandle->createParams.inputByteDepth,
                                      intAlgHandle->blockWidth,
                                      intAlgHandle->blockHeight);


    if (bamStatus != BAM_S_SUCCESS) {
        status = IALG_EFAIL;
        PRINTF("NMS_TI_kernelControl() returned error\n");

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    bamStatus = NMS_TI_execute(&(intAlgHandle->nmsGraphMem), &bamInArgs,&bamOutArgs);


    if (bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        PRINTF("NMS_TI_execute() returned error\n");

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

    }

    Exit:
    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[NMS_TI_BUFDESC_IN_IMAGEBUFFER] =
            (*inBufDesc)[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId ;

    outArgs->inFreeBufIDs[NMS_TI_BUFDESC_IN_TOTAL] = 0 ;

    outArgs->outFreeBufIDs[NMS_TI_BUFDESC_OUT_LIST_XY] =
            (*outBufDesc)[NMS_TI_BUFDESC_OUT_LIST_XY]->bufferId ;

    outArgs->outFreeBufIDs[NMS_TI_BUFDESC_OUT_TOTAL] = 0 ;

    (*outBufDesc)[NMS_TI_BUFDESC_OUT_LIST_XY]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  NMS_TI_activate(IALG_Handle handle)
{
    NMS_TI_Handle algHandle = (NMS_TI_Handle)(void *)(handle);
    int32_t i;

    /*----------------------------------------------------------------*/
    /* Do Activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_NOT_ACTIVE)
    {
        for(i= 1; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == NMS_GRAPH_OBJ_INT_MEMREC))
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
void  NMS_TI_deactivate(IALG_Handle handle)
{
    NMS_TI_Handle algHandle = (NMS_TI_Handle)(void *)(handle);
    int32_t i;
    /*----------------------------------------------------------------*/
    /* Do De-activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_ACTIVE)
    {
        for(i= 1; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == NMS_GRAPH_OBJ_INT_MEMREC))
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
int32_t NMS_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
    int32_t status            = IALG_EOK;
    NMS_TI_Handle algHandle = (NMS_TI_Handle)(void *)(handle);

    memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    return status;
}
