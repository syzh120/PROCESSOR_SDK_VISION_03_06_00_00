/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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
 *****************************************************************************
 * @file
 *  bam_dma_custom_rbrief_node.c
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of custom dma node for rbrief applet
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"
#include "bam_dma_custom_rbrief_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"

/* 5 rows at the top are needed by rbrief kernel */
#define RBRIEF_NUM_ZERO_ROWS            (5U)
#define RBRIEF_INTERNAL_XY_LIST_PTR     (0)
#define RBRIEF_INTERNAL_LEVEL_PTR       (1U)
#define RBRIEF_HALF_PATCH_SIZE          (23U)

/*
  @param *inSrcPtr             Pointer to store the external memory location of the input image

  @param *inXYPtr              Pointer to store the memory location of XY list in DDR

  @param *blockPtrList[32]     Pointer to store the memory location of the 32 features

  @param *dstPtr               Pointer in internal memory where the transferred blocks are stored

  @param *inXYPtr_dmem         Pointer pointing to XY list in DMEM

*/

typedef struct
{
  uint8_t   scatterDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t   autoIncrement1dDmaContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
  uint8_t   *extImgPtr[RBRIEF_TI_MAXLEVELS];
  uint16_t  imgStride[RBRIEF_TI_MAXLEVELS];

  uint8_t   *intImgPtr;
  uint32_t  (*intXyPtr)[RBRIEF_TI_MAXNUMFEATURES];
  uint8_t   (*intLevelPtr)[RBRIEF_TI_MAXNUMFEATURES];
  uint8_t   *autoIncrement1DinputPtr;
  uint16_t  totalFeatures;
  uint16_t  numBlocks;
  uint8_t   *scatterGatherInputPtrList[NUM_FEATURES];
  uint16_t   scatterGatherInputStride[NUM_FEATURES];
  EDMA_UTILS_scattherGather_transferProperties scatterGatherParams;
  BAM_DMA_CUSTOM_RBRIEF_NODE_args dmaArgs;
}BAM_DMA_CUSTOM_RBRIEF_NODE_context;

/* Source node is a scatter gather node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr(
                  void * edmaContext,  void * params);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_frameInitChannel(
                  void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_trigger(
                  void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_wait(
                  void * edmaContext);


/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_updateDDRptr(
                  void * edmaContext,  void * params);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_frameInitChannel(
                void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_trigger(
                void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_wait(
                void * edmaContext);


static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
  const BAM_DMA_CUSTOM_RBRIEF_NODE_args *initArgs = (const BAM_DMA_CUSTOM_RBRIEF_NODE_args*)edmaArgs;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (initArgs == NULL) || (numRecInternal == NULL) || ( numRecOutputDataBlock == NULL ))
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  if ( NUM_FEATURES != initArgs->numFeatures)
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc ERROR : Invalid argument is passed NULL\n");
    errCode = DMANODE_EDMA_ERR_FAILED;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    /* Request memory in image buffer for holding the output block for DMA node  */
    memRecOutputDataBlock[0].space = BAM_MEMSPACE_ANY_VCOPBUF;
    memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[0].size = (initArgs->numFeatures)*(initArgs->blockWidth)*
                                    (initArgs->blockHeight + RBRIEF_NUM_ZERO_ROWS);
    memRecOutputDataBlock[0].alignment  = 32U;

    *numRecOutputDataBlock = 1U;
    *numRecInternal = 0;

  }

Exit:
    return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  const BAM_DMA_CUSTOM_RBRIEF_NODE_args *initArgs = (const BAM_DMA_CUSTOM_RBRIEF_NODE_args*)edmaArgs;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL )
  {
      PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  context->dmaArgs = *initArgs;

  if( memRecOutputDataBlock )
  {
    if(memRecOutputDataBlock[0]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    context->intImgPtr = (uint8_t *)memRecOutputDataBlock[0]->base;
  }
  else
  {
    errCode = DMANODE_EDMA_ERR_FAILED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

EXIT:
  return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr(
                  void * edmaContext,  void * params)
{

  BAM_DMA_CUSTOM_RBRIEF_READ_ctrlArgs * ctrlArgs = (BAM_DMA_CUSTOM_RBRIEF_READ_ctrlArgs *)params;
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint32_t levelCnt;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  for ( levelCnt = 0; levelCnt < ctrlArgs->inBufDesc->numPlanes; levelCnt++)
  {
    context->extImgPtr[levelCnt] =
        (uint8_t *)ctrlArgs->inBufDesc->bufPlanes[levelCnt].buf;

    context->imgStride[levelCnt] =
        ctrlArgs->inBufDesc->bufPlanes[levelCnt].width;

    if ( context->extImgPtr[levelCnt] == NULL )
    {
      PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr ERROR : NULL DDR PTR\n");
      errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
  }

  context->intXyPtr =
          (uint32_t (*)[RBRIEF_TI_MAXNUMFEATURES])(void *)ctrlArgs->xyListBufDesc->bufPlanes[0].buf;


  if ( (*context->intXyPtr) == NULL )
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr ERROR : NULL XY list DDR PTR\n");
    errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  context->intLevelPtr =
          (uint8_t (*)[RBRIEF_TI_MAXNUMFEATURES])(void *)ctrlArgs->levelListBufDesc->bufPlanes[0].buf;

  if ( (*context->intLevelPtr) == NULL )
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr ERROR : NULL level List DDR PTR\n");
    errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  context->totalFeatures  = ctrlArgs->levelListBufDesc->bufPlanes[0].width;

  context->numBlocks = ((context->totalFeatures  + (context->dmaArgs.numFeatures - 1 ))/context->dmaArgs.numFeatures);

 EXIT:
    return errCode;

}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_frameInitChannel(
                       void * edmaContext)
{
  int32_t                 status = 0;
  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;

  uint16_t x, y;
  uint32_t offset;
  uint16_t (*xy)[2];
  uint8_t *dstPtrList[NUM_FEATURES];
  uint16_t blockW[NUM_FEATURES];
  uint16_t blockH[NUM_FEATURES];
  uint16_t dstPtrStride[NUM_FEATURES];
  uint32_t featureCnt;
  uint8_t levelId;

  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_frameInitInChannel ERROR :\
                          Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  for(featureCnt = 0; featureCnt < context->dmaArgs.numFeatures; featureCnt++)
  {
    xy = (uint16_t (*)[2])(void *)( &((*context->intXyPtr)[featureCnt]));
    x = (*xy)[1];
    y = (*xy)[0];
    levelId = (*context->intLevelPtr)[featureCnt];

    offset = (((uint32_t)y - RBRIEF_HALF_PATCH_SIZE) * ( context->imgStride[levelId])) + ( (uint32_t)x - RBRIEF_HALF_PATCH_SIZE);

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    context->scatterGatherInputPtrList[featureCnt] = (uint8_t *)(context->extImgPtr[levelId] + offset);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    /* For destination pointers( internal memory ), leave RBRIEF_NUM_ZERO_ROWS as kernel will be
      using these rows for its computation */

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated based on user given input hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    dstPtrList[featureCnt]   = (context->intImgPtr) + (featureCnt * context->dmaArgs.blockWidth) +
                                ( RBRIEF_NUM_ZERO_ROWS * context->dmaArgs.numFeatures *
                                context->dmaArgs.blockWidth );
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    blockW[featureCnt]       = context->dmaArgs.blockWidth;
    blockH[featureCnt]       = context->dmaArgs.blockHeight;
    dstPtrStride[featureCnt] = context->dmaArgs.blockWidth;
    context->scatterGatherInputStride[featureCnt] = context->imgStride[levelId];
  }

  /* updateMask field is a don't care for init call but we are configuring it for update call later */
  context->scatterGatherParams.updateMask = EDMA_UTILS_SCATTERGATHER_UPDATE_SRCPTR_STRIDE;
  context->scatterGatherParams.srcPtr     = context->scatterGatherInputPtrList;
  context->scatterGatherParams.dstPtr     = dstPtrList;
  context->scatterGatherParams.blkWidth     = blockW;
  context->scatterGatherParams.blkHeight    = blockH;
  context->scatterGatherParams.srcPtrStride = context->scatterGatherInputStride;
  context->scatterGatherParams.dstPtrStride = dstPtrStride;
  context->scatterGatherParams.dmaQueNo   = 0;

  status = EDMA_UTILS_scattherGather_init(context->scatterDmaContext, &context->scatterGatherParams,
          context->dmaArgs.numFeatures);

    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
    /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
    will never occur.*/
    if ( status != 0 )
    {
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
      errCode = DMANODE_EDMA_ERR_FAILED;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*  UNREACH.GEN :   Unreachable code  */
    /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
    will never occur.*/
    status = EDMA_UTILS_scattherGather_configure(context->scatterDmaContext);
    /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */


    if ( status != 0 )
    {
      errCode = DMANODE_EDMA_ERR_FAILED;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

EXIT:
    return errCode;
}




static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Trigger the transfer */
  if(context->numBlocks > 0)
  {
    EDMA_UTILS_scattherGather_updateNtrigger(context->scatterDmaContext,
                                        &context->scatterGatherParams);
  }
  return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_wait(
                      void * edmaContext)
{
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint16_t x, y;
  uint32_t offset;
  uint16_t (*xy)[2];
  uint32_t featureCnt;
  uint8_t levelId;

  if(context->numBlocks > 0)
  {
    /* Increment the xylist and level ptr list to go the next set of feature */
    context->intXyPtr     = (uint32_t (*)[RBRIEF_TI_MAXNUMFEATURES])(void *) (&(*context->intXyPtr)[context->dmaArgs.numFeatures]);
    context->intLevelPtr  = (uint8_t (*)[RBRIEF_TI_MAXNUMFEATURES])(void *) (&(*context->intLevelPtr)[context->dmaArgs.numFeatures]);

    /* Prepare scatter gather transfer params for next trigger */
    for(featureCnt = 0; featureCnt < context->dmaArgs.numFeatures; featureCnt++)
    {
      xy = (uint16_t (*)[2])(void *)( &((*context->intXyPtr)[featureCnt]));
      x = (*xy)[1];
      y = (*xy)[0];
      levelId = (*context->intLevelPtr)[featureCnt];

      offset = (((uint32_t)y - RBRIEF_HALF_PATCH_SIZE) * ( context->imgStride[levelId])) +
                ((uint32_t) x - RBRIEF_HALF_PATCH_SIZE);


      /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
      /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
      /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
          rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
      context->scatterGatherInputPtrList[featureCnt]  = (uint8_t *)(context->extImgPtr[levelId] + offset);
      /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

      context->scatterGatherInputStride[featureCnt]   = context->imgStride[levelId];
    }

    EDMA_UTILS_scattherGather_wait(context->scatterDmaContext);
  }
  context->numBlocks--;

  return errCode;
}

/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
  const BAM_DMA_CUSTOM_RBRIEF_NODE_args *initArgs = (const BAM_DMA_CUSTOM_RBRIEF_NODE_args*)edmaArgs;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (initArgs == NULL ) ||  (numRecInternal == NULL) || (numRecOutputDataBlock == NULL) )
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  if ( NUM_FEATURES != initArgs->numFeatures)
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc ERROR : Invalid argument is passed NULL\n");
    errCode = DMANODE_EDMA_ERR_FAILED;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    *numRecOutputDataBlock = 0;
    *numRecInternal = 0;
  }
Exit:

    return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  if ( memRecInputDataBlock )
  {
    if ( memRecInputDataBlock[0]->base != NULL )
    {
      context->autoIncrement1DinputPtr = (uint8_t *)memRecInputDataBlock[0]->base;
    }
    else
    {
      PRINTF("BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_setMemRecFunc ERROR : Allocated internal mem pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
    }
  }
  else
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_setMemRecFunc ERROR : memRecInputDataBlock is NULL\n");
    errCode = DMANODE_EDMA_ERR_FAILED;
  }

  return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_updateDDRptr(
                  void * edmaContext,  void * params)
{
  IVISION_OutBufs * outBufs = (IVISION_OutBufs *)params;
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  EDMA_UTILS_autoIncrement1D_initParam  initParams;
  uint16_t                numBlocks;
  int32_t                 status = 0;
  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint8_t * extMemPtr;

  IVISION_BufDesc    *(*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_TOTAL];

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }


  if (params == NULL)
  {
      PRINTF("BAM_DMA_AUTOINCREMENT ERROR : updateParams NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

   outBufDesc = (IVISION_BufDesc *(*)[RBRIEF_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

   /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
   /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
   /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
       rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
   extMemPtr = (uint8_t *)(*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]->bufPlanes[0].buf +
                 ((*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]->bufPlanes[0].frameROI.topLeft.y *
     (*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]->bufPlanes[0].width) +
     (*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]->bufPlanes[0].frameROI.topLeft.x;
   /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */


  if ( extMemPtr == NULL )
  {
    PRINTF("BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_updateDDRptr ERROR : ext mem ptr NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  numBlocks = (((uint16_t)context->totalFeatures + ( context->dmaArgs.numFeatures - (uint16_t)1U ) )/context->dmaArgs.numFeatures );
  initParams.numInTransfers   = 0;
  initParams.numOutTransfers  = 1;
  initParams.transferType                     = EDMA_UTILS_TRANSFER_INOUT;
  initParams.transferProp[0].totalLength      = numBlocks * RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE;
  initParams.transferProp[0].numBytes         = RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE;
  initParams.transferProp[0].numCircBuf       = 1;
  initParams.transferProp[0].dmaQueNo         = 0;
  initParams.transferProp[0].extMemPtr        = extMemPtr;
  initParams.transferProp[0].extMemIncrement  = RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE;
  initParams.transferProp[0].interMemPtr      =  (uint8_t *)context->autoIncrement1DinputPtr;
  initParams.transferProp[0].intMemIncrement  = 0;
  initParams.transferProp[0].dmaQueNo         = 1;

  status = EDMA_UTILS_autoIncrement1D_init(context->autoIncrement1dDmaContext,&initParams);

  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
  /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
  will never occur.*/
  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
  /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
EXIT:
  return errCode;

}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_frameInitChannel(
                void * edmaContext)
{
  int32_t                 status = 0;
  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if (errCode == DMANODE_EDMA_ERR_SUCCESS )
  {
     status = EDMA_UTILS_autoIncrement1D_configure(context->autoIncrement1dDmaContext, EDMA_UTILS_TRANSFER_INOUT);
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }

  return errCode;

}


static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;
  int32_t status = 0;

  status = EDMA_UTILS_autoIncrement1D_triggerOutChannel(context->autoIncrement1dDmaContext);

  return (BAM_Status )status;
}

static BAM_Status  BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_wait(void * edmaContext)
{
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_RBRIEF_NODE_context *context = (BAM_DMA_CUSTOM_RBRIEF_NODE_context *)edmaContext;

  EDMA_UTILS_autoIncrement1D_waitOutChannel(context->autoIncrement1dDmaContext);

  return errCode;
}


BAM_KernelInfo gBAM_TI_dmaCustomRbriefNodeReadKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_RBRIEF_NODE_context),
  sizeof(BAM_DMA_CUSTOM_RBRIEF_NODE_args),
  BAM_EVE_ARP32,                      /*coreType*/
  BAM_NODE_SOURCE,                    /*nodeType*/
  0,                                  /*numInputDataBlocks */
  1,                                  /*numOutputDataBlocks */
  2                                   /*numRecInternal */
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_dmaCustomRbriefNodeReadKernelHelperFunc =
{
   &BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
   &BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_setMemRecFunc/* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaCustomRbriefNodeReadKernelExecFunc =
{
  NULL,
   &BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_frameInitChannel,
   &BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_trigger,
   &BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_wait,
   &BAM_DMA_CUSTOM_RBRIEF_SCATTERGATHER_updateDDRptr,
   NULL
};



/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomRbriefNodeWriteKernel =
{
  0,                                    /*kernelId*/
  0,
  sizeof(BAM_DMA_CUSTOM_RBRIEF_NODE_args),
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  1                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomRbriefNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomRbriefNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_frameInitChannel,
   &BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_trigger,
   &BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_wait,
   &BAM_DMA_CUSTOM_RBRIEF_AUTOINCREMENT_1D_updateDDRptr,
   NULL
};


