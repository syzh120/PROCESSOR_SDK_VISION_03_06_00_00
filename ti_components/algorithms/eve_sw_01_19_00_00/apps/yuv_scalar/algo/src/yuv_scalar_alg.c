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
 *  @file       yuv_scalar_alg.c
 *
 *  @brief       This file defines the XDAIS/iVISION functions for yuv padding applet
 *  @version     0.0 (Dec 2013) : Base version.
 */

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "edma_utils_memcpy.h"
#include "yuv_scalar_alg_int.h"

#define ENABLE_DYNAMIC_ROI (0)

/**
 * IVISION interface of the algorithm
 */
const IVISION_Fxns YUV_SCALAR_TI_VISION_FXNS =
{
        {
                &YUV_SCALAR_TI_activate, /* module ID */
                &YUV_SCALAR_TI_activate,    /* activate */
                &YUV_SCALAR_TI_alloc,       /* algAlloc */
                NULL,                          /* control (not suported) */
                &YUV_SCALAR_TI_deactivate,  /* deactivate */
                &YUV_SCALAR_TI_free,        /* free */
                &YUV_SCALAR_TI_init,        /* init */
                NULL,                          /* moved (not suported) */
                &YUV_SCALAR_TI_numAlloc     /* algNumAlloc  */
        },
        &YUV_SCALAR_TI_process,
        &YUV_SCALAR_TI_control
};


/**
 * IRES interface of the algorithm
 */
const IRES_Fxns YUV_SCALAR_TI_IRES = {
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
XDAS_Int32 YUV_SCALAR_TI_numAlloc(void)
{
    return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
XDAS_Int32 YUV_SCALAR_TI_alloc(const IALG_Params *params,
        IALG_Fxns **parentFxns,
        IALG_MemRec memRec[])
{
    int32_t status = IALG_EOK;

    const YUV_SCALAR_TI_CreateParams * createParams =
            (const YUV_SCALAR_TI_CreateParams*)(const void*)params;

    BAM_GraphMemReq graphMemReq;
    uint16_t  outWidth      = (uint16_t)ALIGN_SIZE(createParams->maxWidth,384U);
    uint16_t  outHeight     = (uint16_t)ALIGN_SIZE(createParams->maxHeight,64U);

    /*---------------------------------------------------------*/
    /* Request BAM public function about memories associated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    YUV_SCALAR_TI_getGraphMemReq(&graphMemReq);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when YUV_SCALAR_TI_deactivate */
    /*  is called. Likewise when YUV_SCALAR_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(YUV_SCALAR_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(YUV_SCALAR_TI_Obj);
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
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[GRAPH_OBJ_INT_MEMREC].size       = graphMemReq.graphObjSize;
    memRec[GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
    memRec[GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
    memRec[GRAPH_OBJ_INT_MEMREC].alignment  = 4;

    memRec[GRAPH_SCRATCH_MEMREC].size       =  graphMemReq.graphScratchSize;
    memRec[GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
    memRec[GRAPH_SCRATCH_MEMREC].alignment  = 4;

    memRec[GRAPH_CONTEXT_MEMREC].size       =  graphMemReq.graphcontextSize;
    memRec[GRAPH_CONTEXT_MEMREC].space      =  (IALG_MemSpace) IALG_DARAM0;
    memRec[GRAPH_CONTEXT_MEMREC].attrs      =  IALG_SCRATCH;
    memRec[GRAPH_CONTEXT_MEMREC].alignment  = 4;

    memRec[GRAPH_ARGS_MEMREC].size          =  graphMemReq.graphArgsSize;
    memRec[GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_DARAM0;
    memRec[GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
    memRec[GRAPH_ARGS_MEMREC].alignment     = 4;

    memRec[X_INDEX_MEMREC].size             =  outWidth * 2U * sizeof(uint16_t);
    memRec[X_INDEX_MEMREC].space            =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[X_INDEX_MEMREC].attrs            =  IALG_SCRATCH;
    memRec[X_INDEX_MEMREC].alignment        = 4;

    memRec[X_FRAC_MEMREC].size              =  outWidth * 2U * sizeof(uint8_t);
    memRec[X_FRAC_MEMREC].space             =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[X_FRAC_MEMREC].attrs             =  IALG_SCRATCH;
    memRec[X_FRAC_MEMREC].alignment         = 4;

    memRec[Y_INDEX_MEMREC].size             =  outHeight * 2U * sizeof(uint16_t);
    memRec[Y_INDEX_MEMREC].space            =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[Y_INDEX_MEMREC].attrs            =  IALG_SCRATCH;
    memRec[Y_INDEX_MEMREC].alignment        = 4;

    memRec[Y_FRAC_MEMREC].size              =  outHeight * sizeof(uint16_t);
    memRec[Y_FRAC_MEMREC].space             =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[Y_FRAC_MEMREC].attrs             =  IALG_SCRATCH;
    memRec[Y_FRAC_MEMREC].alignment         = 4;

    memRec[X_CHROMA_INDEX_MEMREC].size      =  (outWidth/2U) * 2U * sizeof(uint16_t);
    memRec[X_CHROMA_INDEX_MEMREC].space     =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[X_CHROMA_INDEX_MEMREC].attrs     =  IALG_SCRATCH;
    memRec[X_CHROMA_INDEX_MEMREC].alignment =  4;

    memRec[X_CHROMA_FRAC_MEMREC].size       =  (outWidth/2U) * 2U * sizeof(uint8_t);
    memRec[X_CHROMA_FRAC_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[X_CHROMA_FRAC_MEMREC].attrs      =  IALG_SCRATCH;
    memRec[X_CHROMA_FRAC_MEMREC].alignment  =  4;

    memRec[Y_CHROMA_INDEX_MEMREC].size             =  outHeight * 2U * sizeof(uint16_t);
    memRec[Y_CHROMA_INDEX_MEMREC].space            =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[Y_CHROMA_INDEX_MEMREC].attrs            =  IALG_SCRATCH;
    memRec[Y_CHROMA_INDEX_MEMREC].alignment        = 4;

    memRec[Y_CHROMA_FRAC_MEMREC].size              =  outHeight * sizeof(uint16_t);
    memRec[Y_CHROMA_FRAC_MEMREC].space             =  (IALG_MemSpace) IALG_EXTERNAL;
    memRec[Y_CHROMA_FRAC_MEMREC].attrs             =  IALG_SCRATCH;
    memRec[Y_CHROMA_FRAC_MEMREC].alignment         = 4;


    return (status);
}


static void getIndexAndFracParts(uint16_t indexPtr[], uint8_t fracPtr[], uint16_t startOffset, uint16_t inSize, uint16_t outSize, uint16_t inblkSize, uint16_t outblkSize, uint16_t scaleRatioQ12, uint16_t fpQShift)
{

  uint16_t y, srcY, srcY1;
  uint16_t srQShift = Q_FORMATE_SCALE_RATIO;
  uint16_t yFracB;
  uint16_t yFracT;
  uint16_t startY0 = 0;
  uint16_t LUT_DATA_SIZE = 4U;
  /*uint16_t offset = (uint16_t)((startOffset * scaleRatioQ12) / (1U << (srQShift))) ;*/
  uint16_t offset = (uint16_t)((startOffset * scaleRatioQ12) >> (srQShift)) ;

  for(y = 0; y < outSize; y++)
  {
    /*srcY = ((uint16_t)((y+startOffset) * scaleRatioQ12) / (uint32_t)(1U << (srQShift-fpQShift)));*/
    srcY = (uint16_t)(((y+startOffset) * scaleRatioQ12) >> (srQShift-fpQShift));
    yFracB = srcY - (uint16_t)((uint16_t)(srcY >> fpQShift) << fpQShift);
    yFracT = (uint16_t)((uint16_t)1U << fpQShift);
    yFracT-= yFracB;
    srcY   = (srcY >> fpQShift);
    srcY1  = srcY+1U;
    srcY   = srcY  >= inSize ? inSize-1U : srcY;
    srcY1  = srcY1 >= inSize ? inSize-1U : srcY1;

    srcY  -= offset;
    srcY1 -= offset;

    if((y % outblkSize) == 0)
    {
      indexPtr[y]           =  0;
      startY0               = srcY;
      indexPtr[outSize+y]   =  srcY1-startY0;
    }
    else
    {
      indexPtr[y]              = srcY  - startY0 ;
      indexPtr[outSize + y]    = srcY1 - startY0;
    }
    fracPtr[y]               = (uint8_t)yFracT;
    fracPtr[outSize + y]     = (uint8_t)yFracB;
  }
  for(y = 0; y < outSize; y++)
  {
      indexPtr[y]           =  (indexPtr[y]*inblkSize)/LUT_DATA_SIZE;
      indexPtr[outSize+y]   =  (indexPtr[outSize+y]*inblkSize)/LUT_DATA_SIZE;
  }
}


/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
XDAS_Int32 YUV_SCALAR_TI_init(IALG_Handle handle,
        const IALG_MemRec memRec[],
        IALG_Handle parent,
        const IALG_Params * params)
{
    int32_t status = IALG_EOK;

    const YUV_SCALAR_TI_CreateParams * createParams =
            (const YUV_SCALAR_TI_CreateParams*)(const void*)params;

    YUV_SCALAR_TI_graphCreateParams graphCreateParams;
    uint16_t blockIncr = 32U;
    uint16_t inBlockWidthOrg ;
    uint16_t  inBlockWidth    ;
                             ;
    uint16_t  outWidth       ;
    uint16_t  outHeight      ;
    YUV_SCALAR_TI_graphArgs * graphArgs;


    YUV_SCALAR_TI_Handle algHandle =
            (YUV_SCALAR_TI_Handle)(void*)memRec[ALG_HANDLE_MEMREC].base;

    /*-----------------------------------------------------------------------*/
    /* Call BAM Graph creation function with passing all the memories        */
    /*-----------------------------------------------------------------------*/
    algHandle->graphMem.graphObj      = memRec[GRAPH_OBJ_MEMREC].base;
    algHandle->graphMem.graphScratch  = memRec[GRAPH_SCRATCH_MEMREC].base;
    algHandle->graphMem.graphcontext  = memRec[GRAPH_CONTEXT_MEMREC].base;
    algHandle->graphMem.graphArgs     = memRec[GRAPH_ARGS_MEMREC].base;

    graphCreateParams.appCreateParams  = createParams;
    graphCreateParams.inputDataType = 0;

    algHandle->createParams = *createParams;

    status = YUV_SCALAR_TI_graphCreate(&(algHandle->graphMem),&graphCreateParams);

    if (status != IALG_EOK)
    {
        PRINTF("YUV_SCALAR_TI_graphCreate() returned error!!!");
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    algHandle->numMemRecs  = NUM_MEMRECS;
    memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
    algHandle->ivision = &YUV_SCALAR_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;

  graphArgs = (YUV_SCALAR_TI_graphArgs *)algHandle->graphMem.graphArgs;
  inBlockWidthOrg = (((uint16_t)graphArgs->blockWidth  * (uint16_t)createParams->scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 4U;
  inBlockWidth    = ALIGN_SIZE((uint16_t)inBlockWidthOrg,(uint16_t)blockIncr);

  outWidth       = ALIGN_SIZE((uint16_t)createParams->maxWidth, (uint16_t)graphArgs->blockWidth );
  outHeight      = ALIGN_SIZE((uint16_t)createParams->maxHeight,(uint16_t)graphArgs->blockHeight);

  getIndexAndFracParts((uint16_t *)(void*)algHandle->memRec[X_INDEX_MEMREC].base,(uint8_t  *)(void*)algHandle->memRec[X_FRAC_MEMREC ].base, createParams->outStartX, (uint16_t)0xFFFF , outWidth,    graphArgs->blockHeight,   graphArgs->blockWidth,  createParams->scaleRatioQ12, createParams->fracQFmt);
  getIndexAndFracParts((uint16_t *)(void*)algHandle->memRec[Y_INDEX_MEMREC].base,(uint8_t  *)(void*)algHandle->memRec[Y_FRAC_MEMREC ].base, createParams->outStartY, (uint16_t)0xFFFF , outHeight,   inBlockWidth,   graphArgs->blockHeight,  createParams->scaleRatioQ12, createParams->fracQFmt);
  getIndexAndFracParts((uint16_t *)(void*)algHandle->memRec[Y_CHROMA_INDEX_MEMREC].base,(uint8_t  *)(void*)algHandle->memRec[Y_CHROMA_FRAC_MEMREC ].base, createParams->outStartY/2U, (uint16_t)0xFFFF , outHeight,   inBlockWidth,   graphArgs->blockHeight,  createParams->scaleRatioQ12, createParams->fracQFmt);
  getIndexAndFracParts((uint16_t *)(void*)algHandle->memRec[X_CHROMA_INDEX_MEMREC].base,(uint8_t  *)(void*)algHandle->memRec[X_CHROMA_FRAC_MEMREC ].base, createParams->outStartX/2U, (uint16_t)0xFFFF , outWidth/2U,   (graphArgs->blockHeight*2U),   (graphArgs->blockWidth/2U),  createParams->scaleRatioQ12, createParams->fracQFmt);

  algHandle->blockWidth  = graphArgs->blockWidth ;
  algHandle->blockHeight = graphArgs->blockHeight;

  Exit:
    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
XDAS_Int32 YUV_SCALAR_TI_control(IVISION_Handle handle,
        IALG_Cmd cmd,
        const IALG_Params *inParams,
        IALG_Params *outParams)
{
    int32_t status = IALG_EOK;
    YUV_SCALAR_TI_ControlOutParams *controlOutParams= (YUV_SCALAR_TI_ControlOutParams *)(void*)outParams;
    YUV_SCALAR_TI_Handle algHandle = (YUV_SCALAR_TI_Handle)(void*)(handle);

    if (cmd== YUV_SCALAR_TI_GET_OUTPUT_BLOCK_DIM) {
        controlOutParams->outputBlockWidth= algHandle->blockWidth;
        controlOutParams->outputBlockHeight= algHandle->blockHeight;
    }
    else {
        status= IALG_EFAIL;
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
XDAS_Int32 YUV_SCALAR_TI_process(IVISION_Handle Handle,
        IVISION_InBufs *inBufs,
        IVISION_OutBufs *outBufs,
        IVISION_InArgs *inArgs,
        IVISION_OutArgs *outArgs)
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
{
    YUV_SCALAR_TI_Handle algHandle = (YUV_SCALAR_TI_Handle)(void*)(Handle);
    YUV_SCALAR_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;

    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;

    IVISION_BufDesc      *(*inBufDesc)[1];
    IVISION_BufDesc      *(*outBufDesc)[1];


    inBufDesc = (IVISION_BufDesc *(*)[1])(void*)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[1])(void*)outBufs->bufDesc;


    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    YUV_SCALAR_TI_activate((IALG_Handle)(void*)Handle);

    intAlgHandle                      = (YUV_SCALAR_TI_Handle)(void*)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->graphMem.graphObj      = intAlgHandle->memRec[GRAPH_OBJ_INT_MEMREC].base;

    /*-----------------------------------------------------------------------*/
    /* BAM specific In Args and OutArgs Assignment                           */
    /*-----------------------------------------------------------------------*/
    bamInArgs.size                  = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex            = 0;

    bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);

#if ENABLE_DYNAMIC_ROI
    if(intAlgHandle->createParams.enableDynamicROI == 1)
    {
      uint16_t blockIncr = 32;
      uint16_t inBlockWidthOrg = ((intAlgHandle->blockWidth  * intAlgHandle->createParams.scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 4;
      int16_t  inBlockWidth    = ALIGN_SIZE(inBlockWidthOrg,blockIncr);
      uint16_t  outWidth       = ALIGN_SIZE(intAlgHandle->createParams.maxWidth, intAlgHandle->blockWidth );
      uint16_t  outHeight      = ALIGN_SIZE(intAlgHandle->createParams.maxHeight,intAlgHandle->blockHeight);

      getIndexAndFracParts((uint16_t *)intAlgHandle->memRec[X_INDEX_MEMREC].base,(uint8_t  *)intAlgHandle->memRec[X_FRAC_MEMREC ].base, intAlgHandle->createParams.outStartX,  0xFFFF , outWidth,    intAlgHandle->blockHeight,   intAlgHandle->blockWidth,  intAlgHandle->createParams.scaleRatioQ12, intAlgHandle->createParams.fracQFmt);
      getIndexAndFracParts((uint16_t *)intAlgHandle->memRec[Y_INDEX_MEMREC].base,(uint8_t  *)intAlgHandle->memRec[Y_FRAC_MEMREC ].base, intAlgHandle->createParams.outStartY, 0xFFFF , outHeight,   inBlockWidth,   intAlgHandle->blockHeight,  intAlgHandle->createParams.scaleRatioQ12, intAlgHandle->createParams.fracQFmt);
      getIndexAndFracParts((uint16_t *)intAlgHandle->memRec[Y_CHROMA_INDEX_MEMREC].base,(uint8_t  *)intAlgHandle->memRec[Y_CHROMA_FRAC_MEMREC ].base, intAlgHandle->createParams.outStartY/2, 0xFFFF , outHeight,   inBlockWidth,   intAlgHandle->blockHeight,  intAlgHandle->createParams.scaleRatioQ12, intAlgHandle->createParams.fracQFmt);
      getIndexAndFracParts((uint16_t *)intAlgHandle->memRec[X_CHROMA_INDEX_MEMREC].base,(uint8_t  *)intAlgHandle->memRec[X_CHROMA_FRAC_MEMREC ].base, intAlgHandle->createParams.outStartX/2, 0xFFFF , outWidth/2,   (intAlgHandle->blockHeight*2),   (intAlgHandle->blockWidth/2),  intAlgHandle->createParams.scaleRatioQ12, intAlgHandle->createParams.fracQFmt);
    }
#endif

    BAM_activateGraph(intAlgHandle->graphMem.graphObj);
    {
      BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_ctrl_args srcDMACtrlArgs;
      const IVISION_BufPlanes (*ivisionBufPlane)[]= (const IVISION_BufPlanes (*)[])(void*)&((*inBufDesc)[0]->bufPlanes[0]);
      YUV_SCALAR_TI_graphArgs * graphArgs = (YUV_SCALAR_TI_graphArgs *)intAlgHandle->graphMem.graphArgs;

      graphArgs->blockWidth     = intAlgHandle->blockWidth ;
      graphArgs->blockHeight    = intAlgHandle->blockHeight;


      /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
      /* Pointer is used in arithmetic or array index expression */
      /* Deviation allowed since, this same address needs to be accessed with an offset  */
      srcDMACtrlArgs.imBaseAddr = (uint8_t*)((uint8_t*)(*ivisionBufPlane)[0].buf + (((*ivisionBufPlane)[0].frameROI.topLeft.y) * (*ivisionBufPlane)[0].width) +  ((*ivisionBufPlane)[0].frameROI.topLeft.x));
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/


      srcDMACtrlArgs.imPitch    = (*ivisionBufPlane)[0].width;
      srcDMACtrlArgs.imWidth    = (*ivisionBufPlane)[0].frameROI.width;
      srcDMACtrlArgs.imHeight   = (*ivisionBufPlane)[0].frameROI.height;

      ivisionBufPlane= (const IVISION_BufPlanes (*)[])(void*)&((*outBufDesc)[0]->bufPlanes[0]);

      srcDMACtrlArgs.outWidth  = ALIGN_SIZE((*ivisionBufPlane)[0].frameROI.width,graphArgs->blockWidth);
      srcDMACtrlArgs.outHeight = ALIGN_SIZE((*ivisionBufPlane)[0].frameROI.height,graphArgs->blockHeight);

      srcDMACtrlArgs.xInfoPitch  = ALIGN_SIZE(intAlgHandle->createParams.maxWidth,graphArgs->blockWidth);
      srcDMACtrlArgs.yInfoPitch  = ALIGN_SIZE(intAlgHandle->createParams.maxHeight,graphArgs->blockHeight);


      srcDMACtrlArgs.scaleRatioQ12 = intAlgHandle->createParams.scaleRatioQ12;

      srcDMACtrlArgs.xIdxBaseAddr  = (uint16_t *)(void*)intAlgHandle->memRec[X_INDEX_MEMREC].base;
      srcDMACtrlArgs.xfracBaseAddr = (uint8_t  *)(void*)intAlgHandle->memRec[X_FRAC_MEMREC ].base;
      srcDMACtrlArgs.yIdxBaseAddr  = (uint16_t *)(void*)intAlgHandle->memRec[Y_INDEX_MEMREC].base;
      srcDMACtrlArgs.yfracBaseAddr = (uint8_t  *)(void*)intAlgHandle->memRec[Y_FRAC_MEMREC ].base;
      srcDMACtrlArgs.inputDataType = 0;
      srcDMACtrlArgs.outStartX     = intAlgHandle->createParams.outStartX;
      srcDMACtrlArgs.outStartY     = intAlgHandle->createParams.outStartY;

      YUV_SCALAR_TI_kernelControl(&(intAlgHandle->graphMem),0,intAlgHandle->createParams.scaleRatioQ12);
      status= YUV_SCALAR_TI_dmaControl(&(intAlgHandle->graphMem), &srcDMACtrlArgs, &((*outBufDesc)[0]->bufPlanes[0]));
      if (status!= IALG_EOK)
      {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      /*-----------------------------------------------------------------------*/
      /* Call execute function                                                 */
      /*-----------------------------------------------------------------------*/
      status =  YUV_SCALAR_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);

      if(((*inBufDesc)[0]->numPlanes == 2) && ((*outBufDesc)[0]->numPlanes == 2))
      {

        ivisionBufPlane= (const IVISION_BufPlanes (*)[])(void*)&((*inBufDesc)[0]->bufPlanes[1]);
        /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
        /* Pointer is used in arithmetic or array index expression */
        /* Deviation allowed since, this same address needs to be accessed with an offset  */
        srcDMACtrlArgs.imBaseAddr    = ((uint8_t*)(*ivisionBufPlane)[0].buf + (((*ivisionBufPlane)[0].frameROI.topLeft.y) * (*ivisionBufPlane)[0].width) +  ((*ivisionBufPlane)[0].frameROI.topLeft.x));
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
        srcDMACtrlArgs.imPitch       = (*ivisionBufPlane)[0].width;
        srcDMACtrlArgs.imWidth       = (*ivisionBufPlane)[0].frameROI.width;
        srcDMACtrlArgs.imHeight      = (*ivisionBufPlane)[0].frameROI.height;

        ivisionBufPlane= (const IVISION_BufPlanes (*)[])(void*)&((*outBufDesc)[0]->bufPlanes[1]);

        srcDMACtrlArgs.outWidth      = ALIGN_SIZE((*ivisionBufPlane)[0].frameROI.width,graphArgs->blockWidth);
        srcDMACtrlArgs.outHeight     = ALIGN_SIZE((*ivisionBufPlane)[0].frameROI.height,graphArgs->blockHeight);
        srcDMACtrlArgs.xInfoPitch    = (ALIGN_SIZE(intAlgHandle->createParams.maxWidth,graphArgs->blockWidth))/2U;
        srcDMACtrlArgs.yInfoPitch    = ALIGN_SIZE(intAlgHandle->createParams.maxHeight,graphArgs->blockHeight);

        srcDMACtrlArgs.xIdxBaseAddr  = (uint16_t *)(void*)intAlgHandle->memRec[X_CHROMA_INDEX_MEMREC].base;
        srcDMACtrlArgs.xfracBaseAddr = (uint8_t  *)(void*)intAlgHandle->memRec[X_CHROMA_FRAC_MEMREC ].base;
        srcDMACtrlArgs.yIdxBaseAddr  = (uint16_t *)(void*)intAlgHandle->memRec[Y_CHROMA_INDEX_MEMREC].base;
        srcDMACtrlArgs.yfracBaseAddr = (uint8_t  *)(void*)intAlgHandle->memRec[Y_CHROMA_FRAC_MEMREC ].base;
        srcDMACtrlArgs.inputDataType = 1;
        srcDMACtrlArgs.outStartX     = intAlgHandle->createParams.outStartX/2;
        srcDMACtrlArgs.outStartY     = intAlgHandle->createParams.outStartY/2;

        YUV_SCALAR_TI_kernelControl(&(intAlgHandle->graphMem),1U,intAlgHandle->createParams.scaleRatioQ12);
        status= YUV_SCALAR_TI_dmaControl(&(intAlgHandle->graphMem), &srcDMACtrlArgs, &((*outBufDesc)[0]->bufPlanes[1]));
        if (status!= IALG_EOK)
        {
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
      }

      /*-----------------------------------------------------------------------*/
      /* Call execute function                                                 */
      /*-----------------------------------------------------------------------*/
      status =  YUV_SCALAR_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);


    }




Exit:
    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
XDAS_Void  YUV_SCALAR_TI_activate(IALG_Handle handle)
{
    YUV_SCALAR_TI_Handle algHandle = (YUV_SCALAR_TI_Handle)(void*)(handle);
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
                EDMA_UTILS_memcpy2D((void *)       algHandle->memRec[i].base,
                                    (const void  *)algHandle->memRec[i-1].base,
                                    (uint16_t)     algHandle->memRec[i].size,
                                    (uint16_t)     1,
                                    (int16_t)      0,
                                    (int16_t)      0);
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
XDAS_Void  YUV_SCALAR_TI_deactivate(IALG_Handle handle)
{
    YUV_SCALAR_TI_Handle algHandle = (YUV_SCALAR_TI_Handle)(void*)(handle);
    int32_t i;
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
        if((i == ALG_HANDLE_INT_MEMREC) ||(i == GRAPH_OBJ_INT_MEMREC) )
        {
            /* Need to replace with EDMA */
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
XDAS_Int32 YUV_SCALAR_TI_free(IALG_Handle handle, IALG_MemRec *memRec)
{
    int32_t status            = IALG_EOK;
    YUV_SCALAR_TI_Handle algHandle = (YUV_SCALAR_TI_Handle)(void*)(handle);

    memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    return status;
}
