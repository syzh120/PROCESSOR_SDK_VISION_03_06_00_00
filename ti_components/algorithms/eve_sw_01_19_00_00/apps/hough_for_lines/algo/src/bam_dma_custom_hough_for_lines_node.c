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
 *  bam_dma_custom_hough_for_lines_node.c
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
#include <string.h>


#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"
#include "bam_dma_custom_hough_for_lines_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "bam_hough_for_lines.h"

/*
  @param *inSrcPtr             Pointer to store the external memory location of the input image

  @param *inXYPtr              Pointer to store the memory location of XY list in DDR

  @param *blockPtrList[32]     Pointer to store the memory location of the 32 features

  @param *dstPtr               Pointer in internal memory where the transferred blocks are stored

  @param *inXYPtr_dmem         Pointer pointing to XY list in DMEM

*/

typedef struct
{
  uint8_t   listBlockTransferDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t   rhoThetaArrayTransferDmaContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
  uint8_t  * listBlockPtr;
  uint8_t  * votedRhoPerTheta;
  uint16_t    currThetaIdx;
  uint16_t   numThetaCnt;
  uint16_t   listDelta;
  uint16_t   votedRhoIndex;
  uint16_t   *pingPongVotedRhoPerTheta[2];
  uint8_t     pingPongFlag;
  EDMA_UTILS_scattherGather_transferProperties scatterGatherParams;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs  dmaArgs;
  uint8_t * srcPtrMemory[1];
}BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context;



/* Source node is a scatter gather node. Following are its helper and exec functions */
static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_updateDDRptr(
                  void * edmaContext,  void * params);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_frameInitChannel(
                  void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_trigger(
                  void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_wait(
                  void * edmaContext);


/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_getMemRecFunc(const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_frameInitChannel(
                void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_trigger(
                void * edmaContext);

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_wait(
                void * edmaContext);


static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
  {
    PRINTF("BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    memRecOutputDataBlock[0].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    /* Allocate the maximum list size that can be processed */
    memRecOutputDataBlock[0].size =  HOUGH_FOR_LINES_MAX_LIST_SIZE * sizeof(uint16_t) * 2U;
    memRecOutputDataBlock[0].alignment  = 32U;

    memRecOutputDataBlock[1].space = BAM_MEMSPACE_IBUFHA;
    memRecOutputDataBlock[1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[1].size = HOUGH_FOR_LINES_RHO_MAX_LENGTH * sizeof(uint16_t);
    memRecOutputDataBlock[1].alignment  = 32U;

    *numRecOutputDataBlock = 2U;
    *numRecInternal = 0;

  }

    return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;

  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

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

    context->listBlockPtr  = (uint8_t *)memRecOutputDataBlock[0]->base;

    if(memRecOutputDataBlock[1]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    context->votedRhoPerTheta  = (uint8_t *)memRecOutputDataBlock[1]->base;
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

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_updateDDRptr(
                  void * edmaContext,  void * params)
{

  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs * ctrlArgs =
              (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs *)params;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context =
              (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;

  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_updateDDRptr ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  context->dmaArgs = *ctrlArgs;

 EXIT:
    return errCode;

}

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_frameInitChannel(
                       void * edmaContext)
{
  int32_t                 status = 0;
  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;
  EDMA_UTILS_autoIncrement1D_initParam  votedRhoArrayInitParams;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs * dmaArgs;
  uint8_t *dstPtrMemory[1];
  uint16_t blkWidthMemory;
  uint16_t blkHeightMemory;
  uint16_t dstPtrStrideMemory;
  uint16_t srcPtrStrideMemory;

  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_frameInitInChannel ERROR :\
                          Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  dmaArgs = &context->dmaArgs;

  context->currThetaIdx   = 0;
  context->pingPongVotedRhoPerTheta[0] = (uint16_t *)(void *)context->votedRhoPerTheta;
  /* As we are using ping pong buffering, hence we have to do the same for B buffer also */
  /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
  /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
  /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
  context->pingPongVotedRhoPerTheta[1] = (uint16_t *)(void *)(context->votedRhoPerTheta  +
                                              HOUGH_FOR_LINES_IMG_BUF_A_B_OFFSET);
  /* RESET_MISRA("17.4")  -> Reset rule 17.4     */



  /* First dma out trigger is dummy */
  context->pingPongFlag = 1U;
  context->listDelta = ( dmaArgs->listSize % 16U);
  if ( context->listDelta != 0 )
  {
    uint32_t * ptrA;
    uint32_t * ptrB;

    context->listDelta = 16U - ( dmaArgs->listSize % 16U);

    /* Make the list which is non aligned of 16 to be zero */
    ptrA  = ( *((uint32_t (*)[HOUGH_FOR_LINES_MAX_LIST_SIZE])(void *)context->listBlockPtr) + (dmaArgs->listSize));

    /* As we are using ping pong buffering, hence we have to do the same for B buffer also */
    /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
    /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
    /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
    ptrB = ptrA + (HOUGH_FOR_LINES_IMG_BUF_A_B_OFFSET / 4U );
    /* RESET_MISRA("17.4")  -> Reset rule 17.4     */


#ifdef HOST_EMULATION
    ptrB = ptrA;
#endif

    memset(ptrA, 0, context->listDelta * sizeof(uint32_t));
    memset(ptrB, 0, context->listDelta * sizeof(uint32_t));

    context->votedRhoIndex = (context->dmaArgs.rhoMaxLength + 1U) / 2U;
  }

  /* updateMask field is a don't care for init call but we are configuring it for update call later */
  context->scatterGatherParams.dmaQueNo     = 0;
  context->scatterGatherParams.srcPtr       = context->srcPtrMemory;
  context->scatterGatherParams.dstPtr       = dstPtrMemory;
  context->scatterGatherParams.blkWidth     = &blkWidthMemory;
  context->scatterGatherParams.blkHeight    = &blkHeightMemory;
  context->scatterGatherParams.srcPtrStride = &srcPtrStrideMemory;
  context->scatterGatherParams.dstPtrStride = &dstPtrStrideMemory;
  context->scatterGatherParams.dmaQueNo        = 0;

  context->srcPtrMemory[0] = dmaArgs->ptrToList;
  dstPtrMemory[0]       = context->listBlockPtr;
  blkWidthMemory        = dmaArgs->listSize * sizeof(uint16_t) * (uint16_t)2;
  blkHeightMemory       = 1U;
  srcPtrStrideMemory    = 0;
  dstPtrStrideMemory    = 0;

  status = EDMA_UTILS_scattherGather_init(context->listBlockTransferDmaContext,
                                          &context->scatterGatherParams,
                                          1U);
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

  status = EDMA_UTILS_scattherGather_configure(context->listBlockTransferDmaContext);

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

  context->numThetaCnt =  (dmaArgs->thetaEnd - dmaArgs->thetaStart) / dmaArgs->thetaStepSize ;


  votedRhoArrayInitParams.numInTransfers  = 1U;
  votedRhoArrayInitParams.transferType    = EDMA_UTILS_TRANSFER_IN;

  votedRhoArrayInitParams.transferProp[0].totalLength = context->numThetaCnt *
                                                        dmaArgs->rhoMaxLength *
                                                        sizeof(uint16_t);

  votedRhoArrayInitParams.transferProp[0].numBytes    = dmaArgs->rhoMaxLength *
                                                        sizeof(uint16_t);
  votedRhoArrayInitParams.transferProp[0].extMemIncrement = dmaArgs->rhoMaxLength *
                                                        sizeof(uint16_t);
  votedRhoArrayInitParams.transferProp[0].extMemPtr    = dmaArgs->ptrToVotedRhoThetaSpace;
  votedRhoArrayInitParams.transferProp[0].interMemPtr  = context->votedRhoPerTheta;
  votedRhoArrayInitParams.transferProp[0].intMemIncrement  = 0;
  votedRhoArrayInitParams.transferProp[0].numCircBuf       = 1U;
  votedRhoArrayInitParams.transferProp[0].dmaQueNo         = 0;

  status = EDMA_UTILS_autoIncrement1D_init(context->rhoThetaArrayTransferDmaContext ,
                                  &votedRhoArrayInitParams);

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

  status = EDMA_UTILS_autoIncrement1D_configure(context->rhoThetaArrayTransferDmaContext ,
                EDMA_UTILS_TRANSFER_IN);

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




static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  if ( context->currThetaIdx < 2U )
  {
    EDMA_UTILS_scattherGather_updateSrcNtrigger(
                              context->listBlockTransferDmaContext,context->srcPtrMemory);
  }

  EDMA_UTILS_autoIncrement1D_triggerInChannel(context->rhoThetaArrayTransferDmaContext);

  return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_wait(
                      void * edmaContext)
{
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;


  if ( context->currThetaIdx < 2U )
  {
    EDMA_UTILS_scattherGather_wait(context->listBlockTransferDmaContext);
  }

  EDMA_UTILS_autoIncrement1D_waitInChannel(context->rhoThetaArrayTransferDmaContext);

  return errCode;
}

/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_getMemRecFunc(const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ((numRecInternal == NULL ) || (numRecOutputDataBlock == NULL) )
  {
    PRINTF("BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    *numRecOutputDataBlock = 0;
    *numRecInternal = 0;
  }

  return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{

  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;


  return errCode;
}

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_frameInitChannel(
                void * edmaContext)
{
  int32_t                 status = 0;
  BAM_Status          errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;
  EDMA_UTILS_autoIncrement1D_initParam  votedRhoArrayInitParams;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs * dmaArgs;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  dmaArgs = &context->dmaArgs;
  votedRhoArrayInitParams.numOutTransfers = 1;
  votedRhoArrayInitParams.transferType    = EDMA_UTILS_TRANSFER_OUT;

  votedRhoArrayInitParams.transferProp[0].totalLength = context->numThetaCnt *
                                                        dmaArgs->rhoMaxLength *
                                                        sizeof(uint16_t);

  votedRhoArrayInitParams.transferProp[0].numBytes    = dmaArgs->rhoMaxLength *
                                                        sizeof(uint16_t);
  votedRhoArrayInitParams.transferProp[0].extMemIncrement = dmaArgs->rhoMaxLength *
                                                        sizeof(uint16_t);
  votedRhoArrayInitParams.transferProp[0].extMemPtr    = dmaArgs->ptrToVotedRhoThetaSpace;
  votedRhoArrayInitParams.transferProp[0].interMemPtr  = context->votedRhoPerTheta;
  votedRhoArrayInitParams.transferProp[0].intMemIncrement  = 0;
  votedRhoArrayInitParams.transferProp[0].numCircBuf       = 1U;
  votedRhoArrayInitParams.transferProp[0].dmaQueNo         = 1U;

  status = EDMA_UTILS_autoIncrement1D_init(context->rhoThetaArrayTransferDmaContext ,
                                  &votedRhoArrayInitParams);


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

  status = EDMA_UTILS_autoIncrement1D_configure(context->rhoThetaArrayTransferDmaContext ,
                EDMA_UTILS_TRANSFER_OUT);

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


static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;
  int32_t status = 0;

  if ( context->listDelta != 0)
  {
    if ( context->currThetaIdx != 0 )
    {
      uint16_t (*votedRhoPtr)[HOUGH_FOR_LINES_RHO_MAX_LENGTH];
      votedRhoPtr = (uint16_t (*)[HOUGH_FOR_LINES_RHO_MAX_LENGTH])(void *) context->pingPongVotedRhoPerTheta[context->pingPongFlag];
      (*votedRhoPtr)[context->votedRhoIndex] =
        (*votedRhoPtr)[context->votedRhoIndex] - context->listDelta;
    }
  }
  status = EDMA_UTILS_autoIncrement1D_triggerOutChannel(context->rhoThetaArrayTransferDmaContext);

  context->pingPongFlag ^= 1U;
#ifdef HOST_EMULATION
  context->pingPongFlag = 0;
#endif
  return (BAM_Status )status;
}

static BAM_Status  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_wait(void * edmaContext)
{
  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *context = (BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context *)edmaContext;

  context->currThetaIdx++;

  EDMA_UTILS_autoIncrement1D_waitOutChannel(context->rhoThetaArrayTransferDmaContext);

  return errCode;
}


BAM_KernelInfo gBAM_TI_dmaCustomHoughForLinesNodeReadKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_context),
  0,
  BAM_EVE_ARP32,                      /*coreType*/
  BAM_NODE_SOURCE,                    /*nodeType*/
  0,                                  /*numInputDataBlocks */
  2,                                  /*numOutputDataBlocks */
  0                                   /*numRecInternal */
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_dmaCustomHoughForLinesNodeReadKernelHelperFunc =
{
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_setMemRecFunc/* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaCustomHoughForLinesNodeReadKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_frameInitChannel,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_trigger,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_wait,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_IN_updateDDRptr,
  NULL
};



/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomHoughForLinesNodeWriteKernel =
{
  0,                                    /*kernelId*/
  0,
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomHoughForLinesNodeWriteKernelHelperFunc =
{
    &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomHoughForLinesNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_frameInitChannel,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_trigger,
  &BAM_DMA_CUSTOM_HOUGH_FOR_LINES_OUT_wait,
  NULL,
  NULL
};


