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
 *  @file       bin_image_to_list_alg.c
 *
 *  @brief       This file defines the XDAIS/iVISION functions for bin_image_to_list  applet
 *  @version     0.0 (Aug 2015) : Base version.
 */

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "bin_image_to_list_alg_int.h"
#include "edma_utils_memcpy.h"
#include "evestarterware.h"
#include "bin_image_to_list_with_masking_graph_int.h"
#include "bin_image_to_list_select_list_elems_graph_int.h"


#define BIN_IMAGE_TO_LIST_SELECTION_CHUNK_SIZE (2048U)
/**
 * IVISION interface of the algorithm
 */
const IVISION_Fxns BIN_IMAGE_TO_LIST_TI_VISION_FXNS =
{
        {
                &BIN_IMAGE_TO_LIST_TI_activate, /* module ID */
                &BIN_IMAGE_TO_LIST_TI_activate,    /* activate */
                &BIN_IMAGE_TO_LIST_TI_alloc,       /* algAlloc */
                NULL,                          /* control (not suported) */
                &BIN_IMAGE_TO_LIST_TI_deactivate,  /* deactivate */
                &BIN_IMAGE_TO_LIST_TI_free,        /* free */
                &BIN_IMAGE_TO_LIST_TI_init,        /* init */
                NULL,                          /* moved (not suported) */
                &BIN_IMAGE_TO_LIST_TI_numAlloc     /* algNumAlloc  */
        },
        &BIN_IMAGE_TO_LIST_TI_process,
        &BIN_IMAGE_TO_LIST_TI_control
};


/**
 * IRES interface of the algorithm
 */
const IRES_Fxns BIN_IMAGE_TO_LIST_TI_IRES = {
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
int32_t BIN_IMAGE_TO_LIST_TI_numAlloc(void)
{
    return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_TI_alloc(const IALG_Params *params,
        IALG_Fxns **parentFxns,
        IALG_MemRec memRec[NUM_MEMRECS])
{
    int32_t status = IALG_EOK;
    BAM_GraphMemReq graphMemReqBinImgToList;
    BAM_GraphMemReq graphMemReqSelListElem;
    const BIN_IMAGE_TO_LIST_TI_CreateParams * createParams = (const BIN_IMAGE_TO_LIST_TI_CreateParams *) (const void *)params;
    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    BIN_IMAGE_TO_LIST_WITH_MASKING_TI_getGraphMemReq(&graphMemReqBinImgToList);

    /*-----------------------------------------------------------------------------*/
    /*  For memory record ALG_HANDLE_INT_MEMREC and FAST9_GRAPH_OBJ_INT_MEMREC,          */
    /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
    /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
    /*  This persistent record will be used to backup the following scratch        */
    /*  memory record during context saving when BIN_IMAGE_TO_LIST_TI_deactivate */
    /*  is called. Likewise when BIN_IMAGE_TO_LIST_TI_activate it called,        */
    /*  the content of the persistent memory record is copied back to the          */
    /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
    /*-----------------------------------------------------------------------------*/
    memRec[ALG_HANDLE_MEMREC].size          = sizeof(BIN_IMAGE_TO_LIST_TI_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 4;

    memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(BIN_IMAGE_TO_LIST_TI_Obj);
    memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
    memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. BIN_IMAGE_TO_LIST_WITH_MASKING_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. BIN_IMAGE_TO_LIST_WITH_MASKING_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. BIN_IMAGE_TO_LIST_WITH_MASKING_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC].size  = graphMemReqBinImgToList.graphObjSize;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC].alignment      = 4;

    /*
    BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC].size  = graphMemReqBinImgToList.graphObjSize;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_MEMREC].size  = graphMemReqBinImgToList.graphScratchSize;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_MEMREC].alignment  = 4;

    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_MEMREC].size  = graphMemReqBinImgToList.graphcontextSize;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_MEMREC].alignment  = 4;

    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_ARGS_MEMREC].size  = graphMemReqBinImgToList.graphArgsSize;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_ARGS_MEMREC].alignment     = 4;


    /*---------------------------------------------------------*/
    /* Request BAM public function about memories assosiated   */
    /* to graph creation                                       */
    /*---------------------------------------------------------*/
    BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_getGraphMemReq(&graphMemReqSelListElem);

    /* Mem records for select list elements graph */
    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC].size  = graphMemReqSelListElem.graphObjSize;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC].attrs = IALG_PERSIST;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC].alignment      = 4U;

    /*
    BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
     */
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC].size  = graphMemReqSelListElem.graphObjSize;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC].space =(IALG_MemSpace) IALG_DARAM0;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC].alignment  = 4U;

    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC].size  = graphMemReqSelListElem.graphScratchSize;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC].alignment  = 4U;

    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC].size  = graphMemReqSelListElem.graphcontextSize;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC].alignment  = 4U;

    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC].size  = graphMemReqSelListElem.graphArgsSize;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC].alignment     = 4U;

    if ( createParams->enableListSuppression == 1U )
    {
      /* Request worst case memory for intermediate buffer */
      memRec[BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC].size  = createParams->maxImageWidth *
            createParams->maxImageHeight * sizeof(uint32_t);
    }
    else
    {
      /* Just populate some small value for the cases when list Suprresion is disabled */
      memRec[BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC].size  = 4U;
    }
    memRec[BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC].space =(IALG_MemSpace) IALG_EXTERNAL;
    memRec[BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC].attrs = IALG_SCRATCH;
    memRec[BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC].alignment     = 4U;
    return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_TI_init(IALG_Handle handle,
        const IALG_MemRec memRec[NUM_MEMRECS],
        IALG_Handle parent,
        const IALG_Params * params)
{
    int32_t status = IALG_EOK;
    int32_t bamStatus;

    BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreateParams    createParams;

    BIN_IMAGE_TO_LIST_TI_Handle algHandle =
            (BIN_IMAGE_TO_LIST_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

    algHandle->binImgToListWithMaskingGraphMem.graphObj      = memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC].base;
    algHandle->binImgToListWithMaskingGraphMem.graphScratch  = memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_MEMREC].base;
    algHandle->binImgToListWithMaskingGraphMem.graphcontext  = memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_MEMREC].base;
    algHandle->binImgToListWithMaskingGraphMem.graphArgs     = memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_ARGS_MEMREC].base;

    algHandle->binImgToListSelListElemGraphMem.graphObj      = memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC].base;
    algHandle->binImgToListSelListElemGraphMem.graphScratch  = memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC].base;
    algHandle->binImgToListSelListElemGraphMem.graphcontext  = memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC].base;
    algHandle->binImgToListSelListElemGraphMem.graphArgs     = memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC].base;

    createParams.icreateParams = (const BIN_IMAGE_TO_LIST_TI_CreateParams*)(const void*)params;
    algHandle->createParams = *(createParams.icreateParams);

    bamStatus = BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate(&(algHandle->binImgToListWithMaskingGraphMem),&createParams);

    if ( bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

    }

    if ( createParams.icreateParams->enableListSuppression == 1U )
    {
      bamStatus = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate(&(algHandle->binImgToListSelListElemGraphMem),NULL);

      if ( bamStatus != BAM_S_SUCCESS)
      {
          status = IALG_EFAIL;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

      }
    }

    algHandle->numMemRecs  = NUM_MEMRECS;
    memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
    algHandle->ivision = &BIN_IMAGE_TO_LIST_TI_VISION_FXNS;

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = ALG_NOT_ACTIVE;

    Exit:
    return (status);
}

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define BIN_IMAGE_TO_LIST_TI_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y) )
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

int32_t BIN_IMAGE_TO_LIST_TI_control(IVISION_Handle handle,
        IALG_Cmd cmd,
        const IALG_Params *inParams,
        IALG_Params *outParams)
{
  int32_t status = IALG_EOK;

  return status;
}




/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
static int32_t BIN_IMAGE_TO_LIST_TI_getComputeDimensions(uint16_t imageWidth,
                                                                       uint16_t imageHeight,
                                                                       uint16_t *computeWidth,
                                                                       uint16_t *computeHeight);

static int32_t BIN_IMAGE_TO_LIST_TI_getComputeDimensions(uint16_t imageWidth,
                                                                       uint16_t imageHeight,
                                                                       uint16_t *computeWidth,
                                                                       uint16_t *computeHeight)
{
  int32_t status = IALG_EOK;
  uint16_t maxBlockHeight;
  uint16_t maxBlockSize;
  uint16_t blockSize;
  uint16_t blockHeight;
  uint16_t blockWidth;

  maxBlockHeight = (uint16_t) BIN_IMAGE_TO_LIST_MAX_PIXELS / imageWidth;
  maxBlockSize   = BIN_IMAGE_TO_LIST_MAX_PIXELS;

  blockWidth  = imageWidth;

  for ( blockHeight = maxBlockHeight; blockHeight > 0; blockHeight--)
  {
    blockSize =  blockWidth * blockHeight;
    if ( blockSize < maxBlockSize )
    {
      if ( (imageHeight % blockHeight) == 0)
      {
        break;
      }
    }
  }

  *computeWidth  = blockWidth;
  *computeHeight = blockHeight;

  return status;
}

static uint32_t leftmostbit(uint32_t n);

static uint32_t leftmostbit(uint32_t n)
{
    uint32_t j, a = 0;
    uint32_t temp ;
    uint32_t compareBit = ( n > 0 ) ? 0 : 1U;

    for (j = 1U; j < 32U; j++)
    {
      n = n<<1U;
      temp = (n >> 31U) & 0x1U;
      if (temp != compareBit )
      {
        break;
      }
    }
    a = 32U - j;
    return a;
}

static int32_t BIN_IMAGE_TO_LIST_TI_generateSelectionMask(uint8_t selectionMaskSize,
        uint8_t selectionMaskPtr[BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_SELECTION_MASK_SIZE],
        uint16_t numBitsToSet);

static int32_t BIN_IMAGE_TO_LIST_TI_generateSelectionMask(uint8_t selectionMaskSize,
        uint8_t selectionMaskPtr[BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_SELECTION_MASK_SIZE],
        uint16_t numBitsToSet)
{
  uint32_t i;

  uint32_t firstPassValidBits;
  uint32_t stepsizeFirstPass;
  uint32_t remainingElements;
  uint32_t bucket;
  uint32_t stepsizeSecondPass;
  memset ( selectionMaskPtr, 0, (uint32_t)selectionMaskSize );

  if ( numBitsToSet != 0 )
  {
    bucket = leftmostbit((uint32_t)numBitsToSet);


    firstPassValidBits = (uint32_t)1U << (bucket - 1U);
    stepsizeFirstPass  = BIN_IMAGE_TO_LIST_TI_CEIL(selectionMaskSize,firstPassValidBits) / firstPassValidBits;


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
      selectionMaskPtr[(i * stepsizeSecondPass)  + (stepsizeFirstPass / 2U)] = 1U;
    }
  }

  return 0;
}






/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* MISRA.PPARAM.NEEDS.CONST:   Pointer parameter is not used to modify the addressed object but is not declared as a pointer to const*/
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const. Fixing this will
    involve changing ivision interface and as this interface is already widely in use we have decided to waive this issue for such incidences */
int32_t BIN_IMAGE_TO_LIST_TI_process(IVISION_Handle handle,
        IVISION_InBufs *inBufs,
        IVISION_OutBufs *outBufs,
        IVISION_InArgs *inArgs,
        IVISION_OutArgs *outArgs)
{
/* RESET_MISRA("16.7")  -> Reset rule 16.7     */

    BIN_IMAGE_TO_LIST_TI_Handle algHandle = (BIN_IMAGE_TO_LIST_TI_Handle)(void *)(handle);
    BIN_IMAGE_TO_LIST_TI_Handle intAlgHandle;
    int32_t status            = IALG_EOK;
    int32_t bamStatus;
    IBAMALG_InArgs          bamInArgs;
    IBAMALG_OutArgs         bamOutArgs;
    BIN_IMAGE_TO_LIST_TI_OutArgs         *binToListOutArgs;
    BIN_IMAGE_TO_LIST_TI_InArgs          *binToListInArgs;
    uint8_t * inputDataPtr;
    uint8_t * inputMaskPtr;
    uint8_t * outputListPtr;
    uint16_t  computeWidth;
    uint16_t  computeHeight;
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint16_t  inImagePitch;
    uint16_t  inMaskPitch;
    uint16_t  listChunkSize;
    uint32_t  numListPointsDetected = 0;
    uint32_t  numListPointsSelected = 0;
    uint32_t  numExtraPointsDetected = 0;
    uint8_t * binToListOutputBuf;
    uint32_t  numDeltaPoints;
    uint32_t i;
    uint32_t isSuppresionRequired;

    IVISION_BufDesc    *(*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc    *(*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL];


    inBufDesc  = (IVISION_BufDesc *(*)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
    outBufDesc = (IVISION_BufDesc *(*)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;


    if ( inBufs->numBufs < 1 )
    {
        status = IVISION_ERRORTYPE_NUM_INBUF_LESS;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    if (inArgs->size != sizeof(BIN_IMAGE_TO_LIST_TI_InArgs))
    {
      status = IALG_EFAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if (outArgs->size != sizeof(BIN_IMAGE_TO_LIST_TI_OutArgs))
    {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      status = IALG_EFAIL;
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }


    binToListOutArgs = (BIN_IMAGE_TO_LIST_TI_OutArgs *)(void *)outArgs;
    binToListInArgs  = (BIN_IMAGE_TO_LIST_TI_InArgs *)(void *)inArgs;

    /*-----------------------------------------------------------------------*/
    /* Activate the algorithm to make sure that now onwards internal memory  */
    /* handle can be utilized                                                */
    /*-----------------------------------------------------------------------*/
    BIN_IMAGE_TO_LIST_TI_activate((IALG_Handle)(void *)handle);

    intAlgHandle                      = (BIN_IMAGE_TO_LIST_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
    intAlgHandle->binImgToListWithMaskingGraphMem.graphObj      =
            intAlgHandle->memRec[BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC].base;
    intAlgHandle->binImgToListSelListElemGraphMem.graphObj =
            intAlgHandle->memRec[BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC].base;

    bamInArgs.size        = sizeof(IBAMALG_InArgs);
    bamInArgs.sliceIndex  = 0;

    bamOutArgs.size       = sizeof(IBAMALG_OutArgs);

    inputDataPtr = *(uint8_t (*)[])(*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].buf +
                              (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].frameROI.topLeft.x +
                              ((*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].frameROI.topLeft.y *
                              (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].width );

    inputMaskPtr = *(uint8_t (*)[])(*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].buf +
                              (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].frameROI.topLeft.x +
                              ((*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].frameROI.topLeft.y *
                              (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].width );


    outputListPtr = *(uint8_t (*)[])(*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]->bufPlanes[0].buf +
                              (*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]->bufPlanes[0].frameROI.topLeft.x +
                              ((*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]->bufPlanes[0].frameROI.topLeft.y *
                              (*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]->bufPlanes[0].width );

    if ( intAlgHandle->createParams.enableListSuppression == 1 )
    {
      binToListOutputBuf = (uint8_t *)(void *)intAlgHandle->memRec[BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC].base;
    }
    else
    {
      binToListOutputBuf = outputListPtr;
    }
    imageWidth  = (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].frameROI.width;
    imageHeight = (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].frameROI.height;

    if ( binToListInArgs->outputListQFormat > BIN_IMAGE_TO_LIST_TI_MAX_QFORMAT )
    {
      status = BIN_IMAGE_TO_LIST_TI_ERRORTYPE_QFORMAT_NOT_FEASIBLE;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    inImagePitch = (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].width;
    inMaskPitch  = (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufPlanes[0].width;

    if ( (imageWidth % 8U) != 0 )
    {
      status = BIN_IMAGE_TO_LIST_TI_ERRORTYPE_WIDTH_NON_MULTIPLE_OF_8;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    if ( intAlgHandle->createParams.enableMasking )
    {
      if ( (imageWidth / 8U) != (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufPlanes[0].frameROI.width )
      {
        status = BIN_IMAGE_TO_LIST_TI_ERRORTYPE_IMAGE_DIMENSION_MISMATCH;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
    }

    BIN_IMAGE_TO_LIST_TI_getComputeDimensions(
                                imageWidth,
                                imageHeight,
                                &computeWidth,
                                &computeHeight);

    bamStatus = BIN_IMAGE_TO_LIST_WITH_MASKING_TI_dmaControl(&(intAlgHandle->binImgToListWithMaskingGraphMem),
                                   inputDataPtr,
                                   inputMaskPtr,
                                   binToListOutputBuf,
                                   (uint8_t *)(void *)&numListPointsDetected,
                                   imageWidth,
                                   imageHeight,
                                   inImagePitch,
                                   inMaskPitch,
                                   computeWidth,
                                   computeHeight,
                                   intAlgHandle->createParams.enableMasking);

    if (bamStatus != BAM_S_SUCCESS) {
        status = IALG_EFAIL;
        PRINTF("BIN_IMAGE_TO_LIST_WITH_MASKING_TI_dmaControl() returned error\n");
       /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
       /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    bamStatus = BIN_IMAGE_TO_LIST_WITH_MASKING_TI_kernelControl(&(intAlgHandle->binImgToListWithMaskingGraphMem),
                                    computeWidth,
                                    computeHeight,
                                    binToListInArgs->startX,
                                    binToListInArgs->startY,
                                    binToListInArgs->outputListQFormat,
                                    binToListInArgs->outputListOrder,
                                    intAlgHandle->createParams.enableMasking);


    if (bamStatus != BAM_S_SUCCESS) {
        status = IALG_EFAIL;
        PRINTF("BIN_IMAGE_TO_LIST_WITH_MASKING_TI_kernelControl() returned error\n");
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    bamStatus = BIN_IMAGE_TO_LIST_WITH_MASKING_TI_execute(&(intAlgHandle->binImgToListWithMaskingGraphMem), &bamInArgs,&bamOutArgs);


    if (bamStatus != BAM_S_SUCCESS)
    {
        status = IALG_EFAIL;
        PRINTF("BIN_IMAGE_TO_LIST_WITH_MASKING_TI_execute() returned error\n");
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    numListPointsSelected = numListPointsDetected;


    /* Check if suppresion is actually required */
    if ( intAlgHandle->createParams.enableListSuppression == 1U)
    {
      isSuppresionRequired = 1U;
      /* If suppression method is based on max value and actual number of points detected
      is already less than max value then suppresion is not required. Just do memcopy */
      if ( binToListInArgs->listSuppressionMethod == BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE )
      {
        isSuppresionRequired = ( numListPointsDetected < binToListInArgs->suppressionValue )? 0 : 1U;
      }
    }
    else
    {
      isSuppresionRequired = 0;
    }

    if ( ( isSuppresionRequired == 1U )&& ( numListPointsDetected != 0 ) )
    {
      uint8_t selectionMaskArray[BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_SELECTION_MASK_SIZE];
      /* numBitsToSet here tells us how many bits should be 1 in the mask */
      uint8_t numBitsToSet;
      uint8_t selectionMaskSize = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_SELECTION_MASK_SIZE;

      numListPointsSelected = 0;
      listChunkSize = BIN_IMAGE_TO_LIST_SELECTION_CHUNK_SIZE;

      if ( binToListInArgs->listSuppressionMethod == BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE )
      {
        numBitsToSet = (uint8_t)(( (uint32_t)selectionMaskSize * binToListInArgs->suppressionValue ) /
                        numListPointsDetected);
      }
      else if ( binToListInArgs->listSuppressionMethod == BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_PERCENTAGE)
      {
        if ( binToListInArgs->suppressionValue > 100 )
        {
          status = IALG_EFAIL;
          PRINTF("BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }

        numBitsToSet = (uint8_t)(((uint32_t)selectionMaskSize * binToListInArgs->suppressionValue) / 100U );
      }
      else
      {
        status = IALG_EFAIL;
        PRINTF("BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl() returned error\n");
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }


      BIN_IMAGE_TO_LIST_TI_generateSelectionMask(selectionMaskSize,
                                                 selectionMaskArray,
                                                 (uint16_t)numBitsToSet);

      numDeltaPoints = numListPointsDetected - ((numListPointsDetected/ selectionMaskSize) * selectionMaskSize);
      numExtraPointsDetected = 0;

      if ( numDeltaPoints != 0 )
      {
        for ( i = 0; i < (selectionMaskSize - numDeltaPoints) ; i++)
        {
          if ( selectionMaskArray[i + numDeltaPoints] == 1U )
          {
            numExtraPointsDetected++;
          }
        }
      }



      bamStatus = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl(&(intAlgHandle->binImgToListSelListElemGraphMem),
                                   binToListOutputBuf,
                                   outputListPtr,
                                   (uint8_t *)(void *)&numListPointsSelected,
                                   numListPointsDetected,
                                   listChunkSize);

      if (bamStatus != BAM_S_SUCCESS) {
          status = IALG_EFAIL;
          PRINTF("BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl() returned error\n");
         /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
         /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      bamStatus = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_kernelControl(&(intAlgHandle->binImgToListSelListElemGraphMem),
                                      numListPointsDetected,
                                      listChunkSize,
                                      selectionMaskSize,
                                      selectionMaskArray);


      if (bamStatus != BAM_S_SUCCESS) {
          status = IALG_EFAIL;
          PRINTF("BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_kernelControl() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }
      bamStatus = BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_execute(&(intAlgHandle->binImgToListSelListElemGraphMem), &bamInArgs,&bamOutArgs);


      if (bamStatus != BAM_S_SUCCESS)
      {
          status = IALG_EFAIL;
          PRINTF("BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_execute() returned error\n");
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto Exit;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
      }

      numListPointsSelected = numListPointsSelected - numExtraPointsDetected;
    }
    else
    {
      if ( intAlgHandle->createParams.enableListSuppression == 1U )
      {
        uint32_t totalBytesToTransfer = numListPointsDetected * sizeof(uint32_t);
        uint32_t numChunks   = totalBytesToTransfer / 32767U;

        if ( numChunks > 0 )
        {
          EDMA_UTILS_memcpy2D(outputListPtr,
                              binToListOutputBuf,
                              (uint16_t)32767,
                              (uint16_t)numChunks,
                              32767,
                              32767);
        }

        if ( totalBytesToTransfer != ( numChunks * 32767U ) )
        {
          uint32_t remainingDataToTransfer = totalBytesToTransfer - ( numChunks * 32767U );
          uint32_t ptrOffset = ( numChunks * 32767U );

          /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
          /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
          /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
              rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
          EDMA_UTILS_memcpy2D(outputListPtr + ptrOffset,
                    binToListOutputBuf + ptrOffset,
                    (uint16_t)remainingDataToTransfer,
                    (uint16_t)1U,
                    0,
                    0);
          /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
        }
      }
    }

    binToListOutArgs->numListPoints = numListPointsSelected;

Exit:

    /*----------------------------------*/
    /* Free the input and output buffer */
    /*----------------------------------*/
    outArgs->inFreeBufIDs[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER] =
            (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER]->bufferId ;

    outArgs->inFreeBufIDs[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER] =
            (*inBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER]->bufferId ;

    outArgs->inFreeBufIDs[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL] = 0 ;

    outArgs->outFreeBufIDs[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST] =
            (*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]->bufferId ;

    outArgs->outFreeBufIDs[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL] = 0 ;

    (*outBufDesc)[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

    return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  BIN_IMAGE_TO_LIST_TI_activate(IALG_Handle handle)
{
    BIN_IMAGE_TO_LIST_TI_Handle algHandle = (BIN_IMAGE_TO_LIST_TI_Handle)(void *)(handle);
    uint8_t i;

    /*----------------------------------------------------------------*/
    /* Do Activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_NOT_ACTIVE)
    {
        for(i= 1U; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC) ||
                  (i == BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC))
            {

                EDMA_UTILS_memcpy2D(algHandle->memRec[i].base,
                        algHandle->memRec[i-1U].base,
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
void  BIN_IMAGE_TO_LIST_TI_deactivate(IALG_Handle handle)
{
    BIN_IMAGE_TO_LIST_TI_Handle algHandle = (BIN_IMAGE_TO_LIST_TI_Handle)(void *)(handle);
    uint8_t i;
    /*----------------------------------------------------------------*/
    /* Do De-activation only if it is deactivated or just after creation */
    /*----------------------------------------------------------------*/
    if(algHandle->algState == ALG_ACTIVE)
    {
        for(i= 1U; i < algHandle->numMemRecs; i++)
        {
            if((i == ALG_HANDLE_INT_MEMREC) ||(i == BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC) ||
                  (i == BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC))
            {
                EDMA_UTILS_memcpy2D(algHandle->memRec[i-1U].base,
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
int32_t BIN_IMAGE_TO_LIST_TI_free(IALG_Handle handle, IALG_MemRec *memRec)
{
    int32_t status            = IALG_EOK;
    BIN_IMAGE_TO_LIST_TI_Handle algHandle = (BIN_IMAGE_TO_LIST_TI_Handle)(void *)(handle);

    memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

    return status;
}
