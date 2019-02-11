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
 *  bam_dma_custom_nms_node.c
 *
 * @brief
 *
 * @version 0.1 (Aug 2014) : First version of custom dma node for nms applet
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
#include "edma_utils_autoincrement.h"
#include "edma_utils_scatterGather.h"
#include "bam_dma_custom_bin_to_list_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "ibin_image_to_list_ti.h"
#include "bam_dma_autoincrement_node.h"

#define BAM_DMA_CUSTOM_BIN_TO_LIST_IMG_BUF_A_B_OFFSET (0x20000U)

/*
  @param *inSrcPtr             Pointer to store the external memory location of the input image

  @param *inXYPtr              Pointer to store the memory location of XY list in DDR

  @param *blockPtrList[32]     Pointer to store the memory location of the 32 features

  @param *dstPtr               Pointer in internal memory where the transferred blocks are stored

  @param *inXYPtr_dmem         Pointer pointing to XY list in DMEM

*/

typedef struct
{
  uint8_t   inAutoIncrementDmaContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
  uint8_t   outScatterGatherDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t   *extMemXyListPtr;
  uint8_t   *extMemListSizePtr;
  uint8_t   *intMemXyListPtr;
  uint8_t   *intMemListSizePtr;
  uint32_t  *pListSize;
  uint8_t  *srcPtr[1];
  uint8_t  *dstPtr[1];
  uint16_t  stride[1];
  uint16_t  blkWidth[1];
  uint8_t   *dstStartPtr[1];
  uint16_t  numHorzBlock;
  uint16_t  numVertBlock;
  uint16_t  numTotalBlk;
  int16_t   blkIdxOut;
  uint8_t   pingPongFlag;
  uint32_t  *pIntListSize[2];
  BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args  dmaArgs;
  EDMA_UTILS_scattherGather_transferProperties updateParams;
}BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context;



/* Source node is a scatter gather node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_IN_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_IN_updateDDRptr(
                  void * edmaContext,  void * params);


/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_updateOutDDRptr(void * edmaContext,  void * params);


static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_trigger(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_wait(
                void * edmaContext);


/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* Rule : Pointer parameter is not used to modify the addressed object but is not declared as pointer to const */
/* Falsely detected by klocwork   */
static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_IN_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[2],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
/*RESET_MISRA("16.7")  -> Reset rule 16.7 for  MISRA.PPARAM.NEEDS.CONST*/
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  /* CHECK_MISRA("-11.5")  -> Disable rule 11.5  */
  /* Rule : Cast operation removes const or volatile modifier from a pointer or reference */
  /* Falsely detected by klocwork   */
  const BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args * dmaArgs = (const BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args *)edmaArgs;
  /*RESET_MISRA("11.5")  -> Reset rule 11.5 for MISRA.CAST.CONST */

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal == NULL ) || (numRecOutputDataBlock == NULL))
  {
    PRINTF("BAM_DMA_CUSTOM_BIN_TO_LIST_IN_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    *numRecOutputDataBlock = 1U;
    *numRecInternal = 0;
    memRecOutputDataBlock[0].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    /* Allocate the maximum list size that can be processed */
    memRecOutputDataBlock[0].size =  ( dmaArgs->maxBlkWidth * dmaArgs->maxBlkHeight ) / 8U;
    memRecOutputDataBlock[0].alignment  = 32U;

    if ( dmaArgs->enableMasking == 1U )
    {
      *numRecOutputDataBlock = 2U;

      memRecOutputDataBlock[1].space = BAM_MEMSPACE_IBUFHA;
      memRecOutputDataBlock[1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
      /* Allocate the maximum list size that can be processed */
      memRecOutputDataBlock[1].size =  dmaArgs->maxBlkWidth * dmaArgs->maxBlkHeight;
      memRecOutputDataBlock[1].alignment  = 32U;
    }

  }

  return errCode;
}

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* Rule : Pointer parameter is not used to modify the addressed object but is not declared as pointer to const */
/* Falsely detected by klocwork   */
static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_IN_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
/*RESET_MISRA("16.7")  -> Reset rule 16.7 for  MISRA.PPARAM.NEEDS.CONST*/
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *context = (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;

  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_autoIncrement_initParam initParams;
  /* CHECK_MISRA("-11.5")  -> Disable rule 11.5  */
  /* Rule : Cast operation removes const or volatile modifier from a pointer or reference */
  /* Falsely detected by klocwork   */
  const BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args * dmaArgs = (const BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args *)edmaArgs;
  /*RESET_MISRA("11.5")  -> Reset rule 11.5 for MISRA.CAST.CONST */

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_BIN_TO_LIST_IN_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  }

  context->dmaArgs = *dmaArgs;

  if( memRecOutputDataBlock )
  {

    initParams.numInTransfers = 1U;
    initParams.transferType   = EDMA_UTILS_TRANSFER_IN;

    if(memRecOutputDataBlock[0]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    initParams.transferProp[0].interMemPtr = (uint8_t *) memRecOutputDataBlock[0]->base;

    if (dmaArgs->enableMasking == 1U )
    {
      /* There are two transfers one is binary packed data and other is byte masked data */
      initParams.numInTransfers = 2U;
      if (memRecOutputDataBlock[1]->base == NULL)
      {
        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
      }
      initParams.transferProp[1].interMemPtr = (uint8_t *) memRecOutputDataBlock[1]->base;
    }

    EDMA_UTILS_autoIncrement_init(context->inAutoIncrementDmaContext,&initParams);
  }
  else
  {
    errCode = DMANODE_EDMA_ERR_FAILED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_IN_updateDDRptr(
                  void * edmaContext,  void * params)
{

  BAM_DMA_CUSTOM_BIN_TO_LIST_READ_ctrlArgs * ctrlArgs =
              (BAM_DMA_CUSTOM_BIN_TO_LIST_READ_ctrlArgs *)params;
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *context =
              (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;
  EDMA_UTILS_autoIncrement_updateParams updateParams;
  int32_t                 status;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_BIN_TO_LIST_IN_updateDDRptr ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

   if ( (ctrlArgs->inTransferProp[0].blkWidth * ctrlArgs->inTransferProp[0].blkHeight) > (context->dmaArgs.maxBlkWidth * context->dmaArgs.maxBlkHeight))
  {
    PRINTF("BAM_DMA_CUSTOM_BIN_TO_LIST_IN_updateDDRptr ERROR : Invalid Block Dimensions NULL\n");
    errCode = DMANODE_EDMA_ERR_INVALID_BLOCK_DIM;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  context->numHorzBlock = (( ctrlArgs->inTransferProp[0].roiWidth - ctrlArgs->inTransferProp[0].blkWidth ) /
                             ctrlArgs->inTransferProp[0].extBlkIncrementX ) + 1U;
  context->numVertBlock = (( ctrlArgs->inTransferProp[0].roiHeight - ctrlArgs->inTransferProp[0].blkHeight) /
                             ctrlArgs->inTransferProp[0].extBlkIncrementY) + 1U;


  context->numTotalBlk = context->numHorzBlock * context->numVertBlock;


  updateParams.transferType = EDMA_UTILS_TRANSFER_IN;
  updateParams.updateMask   = (uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ALL &
                                (uint32_t)(~(uint32_t)EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTERMEMPTR);

  updateParams.updateParams[0] = ctrlArgs->inTransferProp[0];

  if (context->dmaArgs.enableMasking == 1U )
  {
    updateParams.updateParams[1] = ctrlArgs->inTransferProp[1];
  }

  status = EDMA_UTILS_autoIncrement_update(context->inAutoIncrementDmaContext,&updateParams);

  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
  /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
  /*  UNREACH.GEN :   Unreachable code  */
  /* Status will never be 0 because we are passing all the correct parameters to the function and hence all the error conditions inside the function
  will never occur.*/
  if ( status != 0 )
  {
    errCode = DMANODE_EDMA_ERR_FAILED;
  }
  /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
  /*RESET_MISRA("14.1")  -> Reset rule 14.1 for  UNREACH.GEN */

 EXIT:
    return errCode;

}




/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_getMemRecFunc(
                    const void *edmaArgs,
                    BAM_MemRec *memRecInternal,
                    BAM_MemRec *memRecOutputDataBlock,
                    uint8_t *numRecInternal,
                    uint8_t *numRecOutputDataBlock)
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal== NULL ) || ( numRecOutputDataBlock == NULL) )
  {
      PRINTF("BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *dmaContext = (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (dmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  if( memRecInputDataBlock )
  {
      /* ------------------------------------------------------------- */
      /* Set internal memory pointers                                  */
      /* ------------------------------------------------------------- */
      if(memRecInputDataBlock[0]->base == NULL)
      {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto EXIT;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
      }
      else
      {
          dmaContext->srcPtr[0] = (uint8_t *)memRecInputDataBlock[0]->base;
          dmaContext->pIntListSize[0] = (uint32_t *)memRecInputDataBlock[1]->base;
#if (!VCOP_HOST_EMULATION)
          dmaContext->pIntListSize[1] = *(uint32_t (*)[])(void *)dmaContext->pIntListSize[0] + (BAM_DMA_CUSTOM_BIN_TO_LIST_IMG_BUF_A_B_OFFSET / sizeof(uint32_t));
#else
          dmaContext->pIntListSize[1] = dmaContext->pIntListSize[0];
#endif
      }
    }
    else
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }
EXIT:

  return errCode;

}

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *dmaContext = (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint16_t  blkHeight[1];

  if (edmaContext == NULL)  {
      PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if (errCode == DMANODE_EDMA_ERR_SUCCESS )
  {
      dmaContext->pingPongFlag = 0;
      *(dmaContext->pIntListSize[0]) = 0;
      dmaContext->pingPongFlag^= 1U;

      dmaContext->stride[0] = 0;
      dmaContext->blkWidth[0] = 1U;
      blkHeight[0] = 1U;
      dmaContext->blkIdxOut = -1;

      dmaContext->updateParams.updateMask   = (EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W |
                                            EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE);
      dmaContext->updateParams.dmaQueNo     = 1U;
      dmaContext->updateParams.srcPtr       = dmaContext->srcPtr;
      dmaContext->updateParams.dstPtr       = dmaContext->dstPtr;
      dmaContext->updateParams.srcPtrStride = dmaContext->stride;
      dmaContext->updateParams.dstPtrStride = dmaContext->stride;
      dmaContext->updateParams.blkWidth     = dmaContext->blkWidth;
      dmaContext->updateParams.blkHeight    = blkHeight;

      status = EDMA_UTILS_scattherGather_init(dmaContext->outScatterGatherDmaContext , &(dmaContext->updateParams), 1U);
  }

  if (status == 0 )
  {
     status = EDMA_UTILS_scattherGather_configure(dmaContext->outScatterGatherDmaContext);
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }

  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_updateOutDDRptr(void * edmaContext,  void * params)
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *context = (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;
  BAM_DMA_CUSTOM_BIN_TO_LIST_WRITE_ctrlArgs * ctrlArgs =
                            (BAM_DMA_CUSTOM_BIN_TO_LIST_WRITE_ctrlArgs *)params;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL)
  {
      PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
  {

      context->dstPtr[0] = ctrlArgs->ptrToXyListBuf;
      context->dstStartPtr[0] = ctrlArgs->ptrToXyListBuf;
      context->pListSize = (uint32_t *)(void *)ctrlArgs->ptrToListSizeBuf;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *context = (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  int32_t         status = 0;

  if((( context->blkIdxOut + 1U ) % context->numHorzBlock) == 0)
  {
      if ( context->blkIdxOut != -1 )
      {
        /* Update the amount of transfer to be done based on the list size returned by the kernel */
        context->blkWidth[0]     = (uint16_t)4U * ((uint16_t)(*context->pIntListSize[context->pingPongFlag]));

        /* Trigger the transfer */
        status = EDMA_UTILS_scattherGather_updateNtrigger(context->outScatterGatherDmaContext, &(context->updateParams));
      }
  }

  context->pingPongFlag ^= 1U;

  /* Indicate BAM to pipe down on encountering penultimate block */
  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
   /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
  will never occur.*/
  if ((status != 0) || ((context->blkIdxOut + 1U) >= (context->numTotalBlk - 1U)))
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
  /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */

  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_wait(void * edmaContext)
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *context = (BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  if( ( (context->blkIdxOut + 1U ) % context->numHorzBlock) == 0)
  {
      if ( context->blkIdxOut != -1 )
      {
        EDMA_UTILS_scattherGather_wait(context->outScatterGatherDmaContext);

        /* Update the destination pointer in DDR */
        context->dstPtr[0] = *(uint8_t (*)[])(void *)context->dstPtr[0] + context->blkWidth[0];
      }
  }

  /* ------------------------------------------------------------- */
  /* Update block position                                         */
  /* ------------------------------------------------------------- */
  context->blkIdxOut++;
  if(context->blkIdxOut >= context->numTotalBlk)
  {

      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* Rule :  Cast converts pointer to integral type    */
      /*  To calculate pointer difference, we need to convert them   */
      /* Return the list size */
      *context->pListSize = ((uintptr_t )context->dstPtr[0] - (uintptr_t )context->dstStartPtr[0])/sizeof(uint32_t );
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT  */

      /* Restore back to initial state at end of pipeline */
      context->blkIdxOut = -1;

      context->dstPtr[0] = context->dstStartPtr[0];
  }

  return errCode;
}


BAM_KernelInfo gBAM_TI_dmaCustomBinToListNodeReadKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_context),
  0,
  BAM_EVE_ARP32,                      /*coreType*/
  BAM_NODE_SOURCE,                    /*nodeType*/
  0,                                  /*numInputDataBlocks */
  2U,                                  /*numOutputDataBlocks */
  0                                   /*numRecInternal */
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_dmaCustomBinToListNodeReadKernelHelperFunc =
{
   &BAM_DMA_CUSTOM_BIN_TO_LIST_IN_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
   &BAM_DMA_CUSTOM_BIN_TO_LIST_IN_setMemRecFunc/* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaCustomBinToListNodeReadKernelExecFunc =
{
  NULL,
   &BAM_DMA_AUTOINCREMENT_frameInitInChannel,
   &EDMA_UTILS_autoIncrement_triggerInChannel,
   &EDMA_UTILS_autoIncrement_waitInChannel,
   &BAM_DMA_CUSTOM_BIN_TO_LIST_IN_updateDDRptr,
   NULL
};



/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomBinToListNodeWriteKernel =
{
  0,                                    /*kernelId*/
  0,
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  2U,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomBinToListNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomBinToListNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_frameInitChannel,
  &BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_trigger,
  &BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_wait,
  &BAM_DMA_CUSTOM_BIN_TO_LIST_OUT_updateOutDDRptr,
  NULL
};


