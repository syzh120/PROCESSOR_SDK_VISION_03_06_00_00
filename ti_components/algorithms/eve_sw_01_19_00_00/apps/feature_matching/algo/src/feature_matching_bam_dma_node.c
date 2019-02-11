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

/*
 *****************************************************************************
 *
 * BAM DMA node for feature matching applet
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *****************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  feature_matching_bam_dma_node.c
 *
 * @brief
 *
 * @version 0.1 (Aug 2014) : First version of custom dma node for feature
 *                           matching graph
 *
 *****************************************************************************
 */

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/
#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"
#include "feature_matching_bam_dma_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"

typedef struct
{
  uint8_t  autoincr1dIn1PingOutContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
  uint8_t  autoincr1dIn1PongContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
  uint8_t  scatterDmaIn2Context[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint32_t inIterIdx;
  uint32_t outIterIdx;
  uint16_t numIters;
  uint16_t loopCount1;
  uint16_t loopCount2;
  uint8_t *in2IntMemAddr;
  uint8_t *in2ExtMemAddr;
  uint8_t *scatterSrcPtr[1];
  BAM_DMA_NODE_FEAT_MATCH_args dmaArgs;
}BAM_DMA_NODE_FEAT_MATCH_context;

static BAM_Status BAM_DMA_IN_FEAT_MATCH_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[],
        BAM_MemRec memRecOutputDataBlock[], uint8_t *numRecInternal,
        uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_IN_FEAT_MATCH_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[],
        BAM_MemRec memRecOutputDataBlock[], uint8_t *numRecInternal,
        uint8_t *numRecOutputDataBlock)
{
  const BAM_DMA_NODE_FEAT_MATCH_args *initArgs = (const BAM_DMA_NODE_FEAT_MATCH_args *)edmaArgs;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */

  /* Not checking memRecInternal pointer since it is not used in this function */
  if((initArgs == NULL) || (numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
  {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    goto EXIT;
  }

  if(memRecOutputDataBlock == NULL)
  {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    goto EXIT;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  /* Request memory in image buffer for holding the output block for DMA node */
  memRecOutputDataBlock[0].space = BAM_MEMSPACE_IBUFHA;
  memRecOutputDataBlock[0].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
  memRecOutputDataBlock[0].size = 16*((initArgs->numDescPerIter1 + 15)/16)*initArgs->descriptorLength;
  memRecOutputDataBlock[0].alignment = 32;

  memRecOutputDataBlock[1].space = BAM_MEMSPACE_IBUFLA;
  memRecOutputDataBlock[1].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
  memRecOutputDataBlock[1].size = 2*((initArgs->numDescPerIter2 + 1)/2)*initArgs->descriptorLength;
  memRecOutputDataBlock[1].alignment = 32;

  *numRecOutputDataBlock = 2U;
  *numRecInternal = 0;

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[],
        BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[],
        BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if((numRecInternal == NULL)|| (numRecOutputDataBlock == NULL))
    {
      PRINTF("BAM_DMA_OUT_FEAT_MATCH_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
    }

    return errCode;
}

static BAM_Status BAM_DMA_IN_FEAT_MATCH_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_IN_FEAT_MATCH_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
  BAM_DMA_NODE_FEAT_MATCH_context *context     = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  const BAM_DMA_NODE_FEAT_MATCH_args *initArgs = (const BAM_DMA_NODE_FEAT_MATCH_args*)edmaArgs;
  EDMA_UTILS_autoIncrement1D_initParam initAutoIncrParams;
  int32_t status = 0;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */

  if(context == NULL) {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    goto EXIT;
  }

  context->dmaArgs = *initArgs;

  if(memRecOutputDataBlock != NULL) {
    if((memRecOutputDataBlock[0]->base == NULL) && (memRecOutputDataBlock[1]->base == NULL)) {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      goto EXIT;
    }

    /* Reset globalStateStruct for the first time for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();

    /* Set internal memory pointer */
    initAutoIncrParams.transferType = EDMA_UTILS_TRANSFER_IN;
    initAutoIncrParams.numInTransfers = 1;
    initAutoIncrParams.numOutTransfers = 0;

    initAutoIncrParams.transferProp[0].intMemIncrement = 0;
    initAutoIncrParams.transferProp[0].extMemPtr = NULL;
    initAutoIncrParams.transferProp[0].dmaQueNo = 0;

    initAutoIncrParams.transferProp[0].totalLength = initArgs->numDescPerIter1*initArgs->descriptorLength;
    initAutoIncrParams.transferProp[0].numBytes = initArgs->numDescPerIter1*initArgs->descriptorLength;
    initAutoIncrParams.transferProp[0].extMemIncrement = initArgs->numDescPerIter1*initArgs->descriptorLength;
    initAutoIncrParams.transferProp[0].interMemPtr = (uint8_t *)memRecOutputDataBlock[0]->base;
    initAutoIncrParams.transferProp[0].numCircBuf = 1;

    status = EDMA_UTILS_autoIncrement1D_init(context->autoincr1dIn1PingOutContext, &initAutoIncrParams);

   /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
   /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
   /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /* The returned status may or may not be zero. The below if() condition is a valid condition.   */

    if(status != 0) {
      errCode = DMANODE_EDMA_ERR_FAILED;
      goto EXIT;
    }

    status = EDMA_UTILS_autoIncrement1D_init(context->autoincr1dIn1PongContext, &initAutoIncrParams);
    if(status != 0) {
      errCode = DMANODE_EDMA_ERR_FAILED;
      goto EXIT;
    }
    /* RESET_MISRA("14.1")  -> Reset rule 14.1     */
    /* RESET_MISRA("13.7")  -> Reset rule 13.7     */

    context->in2IntMemAddr = (uint8_t *)memRecOutputDataBlock[1]->base;
  }
  else {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock,
        void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock,
        void *edmaContext, const void *edmaArgs)
{
  BAM_DMA_NODE_FEAT_MATCH_context *context     = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  const BAM_DMA_NODE_FEAT_MATCH_args *initArgs = (const BAM_DMA_NODE_FEAT_MATCH_args*)edmaArgs;
  EDMA_UTILS_autoIncrement1D_initParam initAutoIncrParams;
  int32_t status = 0;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if( memRecInputDataBlock != NULL ) {
    if(memRecInputDataBlock[0]->base == NULL) {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      goto EXIT;
    }

    initAutoIncrParams.transferType = EDMA_UTILS_TRANSFER_OUT;
    initAutoIncrParams.numInTransfers = 0;
    initAutoIncrParams.numOutTransfers = 1;

    initAutoIncrParams.transferProp[0].totalLength = initArgs->numDescPerIter1*sizeof(uint16_t);
    initAutoIncrParams.transferProp[0].numBytes = initArgs->numDescPerIter1*sizeof(uint16_t);
    initAutoIncrParams.transferProp[0].extMemIncrement = initArgs->numDescPerIter1*sizeof(uint16_t);
    initAutoIncrParams.transferProp[0].intMemIncrement = 0;
    initAutoIncrParams.transferProp[0].extMemPtr = NULL;
    initAutoIncrParams.transferProp[0].interMemPtr = (uint8_t *)memRecInputDataBlock[0]->base;
    initAutoIncrParams.transferProp[0].numCircBuf = 1;
    initAutoIncrParams.transferProp[0].dmaQueNo = 0;

    status = EDMA_UTILS_autoIncrement1D_init(context->autoincr1dIn1PingOutContext, &initAutoIncrParams);
    if(status != 0) {
      errCode = DMANODE_EDMA_ERR_FAILED;
      goto EXIT;
    }
  }
  else {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_IN_FEAT_MATCH_frameInitChannel(
                       void * edmaContext);

static BAM_Status BAM_DMA_IN_FEAT_MATCH_frameInitChannel(
                       void * edmaContext)
{
  int32_t status = 0;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  EDMA_UTILS_scattherGather_transferProperties scatterGatherParams;
  uint8_t *dstPtr[1];
  uint16_t blockW[1];
  uint16_t blockH[1];
  uint16_t srcPtrStride[1];
  uint16_t dstPtrStride[1];

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if(context == NULL) {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_frameInitChannel ERROR :\
                        Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    goto EXIT;
  }

  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  status = EDMA_UTILS_autoIncrement1D_configure(context->autoincr1dIn1PingOutContext, EDMA_UTILS_TRANSFER_IN);
  if( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }

  status = EDMA_UTILS_autoIncrement1D_configure(context->autoincr1dIn1PongContext, EDMA_UTILS_TRANSFER_IN);
  if( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }

  context->scatterSrcPtr[0] = context->in2ExtMemAddr;
  dstPtr[0]       = context->in2IntMemAddr;
  blockW[0]       = context->dmaArgs.numDescPerIter2*context->dmaArgs.descriptorLength;
  blockH[0]       = 1U;
  srcPtrStride[0] = blockW[0];
  dstPtrStride[0] = blockW[0];

  scatterGatherParams.srcPtr       = context->scatterSrcPtr;
  scatterGatherParams.dstPtr       = dstPtr;
  scatterGatherParams.blkWidth     = blockW;
  scatterGatherParams.blkHeight    = blockH;
  scatterGatherParams.srcPtrStride = srcPtrStride;
  scatterGatherParams.dstPtrStride = dstPtrStride;

  scatterGatherParams.dmaQueNo     = 1U;

  status = EDMA_UTILS_scattherGather_init(context->scatterDmaIn2Context, &scatterGatherParams, 1U);

  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
  /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
  /* The returned status may or may not be zero. The below if() condition is a valid condition.   */

  if ( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.1")  -> Reset rule 14.1     */
  /* RESET_MISRA("13.7")  -> Reset rule 13.7     */

  status = EDMA_UTILS_scattherGather_configure(context->scatterDmaIn2Context);
  if ( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  context->inIterIdx = 0;

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_frameInitChannel(
                       void * edmaContext);

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_frameInitChannel(
                       void * edmaContext)
{
  int32_t status = 0;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if(context == NULL) {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_frameInitChannel ERROR :\
                        Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    goto EXIT;
  }

  status = EDMA_UTILS_autoIncrement1D_configure(context->autoincr1dIn1PingOutContext, EDMA_UTILS_TRANSFER_OUT);
  if( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  context->outIterIdx = 0;

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_IN_FEAT_MATCH_updateDDRptr(
                  void * edmaContext,  void * params);

static BAM_Status BAM_DMA_IN_FEAT_MATCH_updateDDRptr(
                  void * edmaContext,  void * params)
{
  BAM_DMA_NODE_FEAT_MATCH_updateParams *featMatchUpdateParams= (BAM_DMA_NODE_FEAT_MATCH_updateParams*)params;
  EDMA_UTILS_autoIncrement1D_updateParams updateParams;
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  uint32_t totalNumDesc1, totalNumDesc2, descBlockSize;
  int32_t status = 0;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if(context == NULL) {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_updateDDRptr ERROR :\
                      Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    goto EXIT;
  }

  if(featMatchUpdateParams == NULL) {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_updateDDRptr ERROR : updateParams NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    goto EXIT;
  }

  totalNumDesc1 = featMatchUpdateParams->totalNumBytesIn1/context->dmaArgs.descriptorLength;
  totalNumDesc2 = featMatchUpdateParams->totalNumBytesIn2/context->dmaArgs.descriptorLength;

  /* Update the number of descriptors to be processed per iteration */
  context->dmaArgs.numDescPerIter1 = featMatchUpdateParams->numDesc1PerIter;
  context->dmaArgs.numDescPerIter2 = featMatchUpdateParams->numDesc2PerIter;

  context->loopCount1 = ((totalNumDesc1 + context->dmaArgs.numDescPerIter1) - (1U))/
                         context->dmaArgs.numDescPerIter1;

  context->loopCount2 = ((totalNumDesc2 + context->dmaArgs.numDescPerIter2) - (1U))/
                         context->dmaArgs.numDescPerIter2;

  context->numIters = context->loopCount1*context->loopCount2;

  updateParams.transferType = EDMA_UTILS_TRANSFER_IN;
  updateParams.updateMask = EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TOTALLENGTH |
                            EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_NUMBYTES |
                            EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMINCREMENT |
                            EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMPTR;
  descBlockSize = context->dmaArgs.numDescPerIter1*context->dmaArgs.descriptorLength;
  updateParams.updateParams[0].totalLength = context->loopCount1*descBlockSize;
  updateParams.updateParams[0].numBytes = descBlockSize;
  updateParams.updateParams[0].extMemIncrement = descBlockSize;
  updateParams.updateParams[0].extMemPtr  = featMatchUpdateParams->extMemPtrIn1;

  status = EDMA_UTILS_autoIncrement1D_update(context->autoincr1dIn1PingOutContext, &updateParams);

  /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
  /* The returned status may or may not be zero. The below if() condition is a valid condition.   */

  if( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.1")  -> Reset rule 14.1     */

  status = EDMA_UTILS_autoIncrement1D_update(context->autoincr1dIn1PongContext, &updateParams);

  /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
  /* The returned status may or may not be zero. The below if() condition is a valid condition.   */

  if( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.1")  -> Reset rule 14.1     */

  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  context->in2ExtMemAddr = featMatchUpdateParams->extMemPtrIn2;

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_updateDDRptr(
                  void * edmaContext,  void * params);

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_updateDDRptr(
                  void * edmaContext,  void * params)
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  int32_t status = 0;
  const BAM_DMA_NODE_FEAT_MATCH_updateParams *featMatchUpdateParams = (const BAM_DMA_NODE_FEAT_MATCH_updateParams*)params;
  EDMA_UTILS_autoIncrement1D_updateParams updateParams;
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  uint32_t outBlockSize;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if(edmaContext == NULL) {
    PRINTF("BAM_DMA_OUT_FEAT_MATCH_updateDDRptr ERROR :\
                      Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    goto EXIT;
  }

  if(featMatchUpdateParams == NULL) {
    PRINTF("BAM_DMA_IN_FEAT_MATCH_updateDDRptr ERROR : updateParams NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    goto EXIT;
  }

  updateParams.transferType = EDMA_UTILS_TRANSFER_OUT;
  updateParams.updateMask = EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_TOTALLENGTH |
                            EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_NUMBYTES |
                            EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMINCREMENT |
                            EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMPTR;
  outBlockSize = context->dmaArgs.numDescPerIter1*sizeof(uint16_t);
  updateParams.updateParams[0].totalLength = context->loopCount1*outBlockSize;
  updateParams.updateParams[0].numBytes = outBlockSize;
  updateParams.updateParams[0].extMemIncrement = outBlockSize;
  updateParams.updateParams[0].extMemPtr = featMatchUpdateParams->extMemPtrOut;
  status = EDMA_UTILS_autoIncrement1D_update(context->autoincr1dIn1PingOutContext, &updateParams);

  /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
  /* The returned status may or may not be zero. The below if() condition is a valid condition.   */

  if( status != 0 ) {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.1")  -> Reset rule 14.1     */

  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_IN_FEAT_MATCH_trigger(void * edmaContext);

static BAM_Status BAM_DMA_IN_FEAT_MATCH_trigger(void * edmaContext)
{
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  uint16_t i;
  int32_t status = 0;

  if(context->inIterIdx < context->numIters) {

    i = context->inIterIdx % context->loopCount2;

    if(i == 0) {
      EDMA_UTILS_autoIncrement1D_triggerInChannel(context->autoincr1dIn1PingOutContext);
    }

    if(i == 1U) {
      EDMA_UTILS_autoIncrement1D_triggerInChannel(context->autoincr1dIn1PongContext);
    }

    EDMA_UTILS_scattherGather_updateSrcNtrigger(context->scatterDmaIn2Context, context->scatterSrcPtr);
  }

  return (DMANODE_EdmaErr)status;
}

static BAM_Status BAM_DMA_IN_FEAT_MATCH_wait(void * edmaContext);

static BAM_Status BAM_DMA_IN_FEAT_MATCH_wait(void * edmaContext)
{
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  uint16_t i;
  int32_t status = 0;

  if(context->inIterIdx < context->numIters) {

    i = context->inIterIdx % context->loopCount2;

    if(i < (context->loopCount2 - (uint16_t)1)) {
      context->scatterSrcPtr[0] = (uint8_t *)(*((uint8_t (*)[])(void *)context->scatterSrcPtr[0]) +
                                  (context->dmaArgs.numDescPerIter2*context->dmaArgs.descriptorLength));
    }
    else {
      context->scatterSrcPtr[0] = context->in2ExtMemAddr;
    }

    if(i == 0) {
      EDMA_UTILS_autoIncrement1D_waitInChannel(context->autoincr1dIn1PingOutContext);
    }

    if(i == 1U) {
      EDMA_UTILS_autoIncrement1D_waitInChannel(context->autoincr1dIn1PongContext);
    }

    EDMA_UTILS_scattherGather_wait(context->scatterDmaIn2Context);
  }

  context->inIterIdx++;

  return (DMANODE_EdmaErr)status;
}

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_trigger(void * edmaContext);

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_trigger(void * edmaContext)
{
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  int32_t status = 0;

  /* Indicate BAM to pipe down on encountering penultimate block */
  if(context->outIterIdx == (context->numIters - 1)) {
    status = 1;
  }

  if((context->outIterIdx % context->loopCount2) == 0) {
    EDMA_UTILS_autoIncrement1D_triggerOutChannel(context->autoincr1dIn1PingOutContext);
 }

  return (DMANODE_EdmaErr)status;
}

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_wait(void * edmaContext);

static BAM_Status BAM_DMA_OUT_FEAT_MATCH_wait(void * edmaContext)
{
  BAM_DMA_NODE_FEAT_MATCH_context *context = (BAM_DMA_NODE_FEAT_MATCH_context *)edmaContext;
  int32_t status = 0;

  if((context->outIterIdx % context->loopCount2) == 0) {
    EDMA_UTILS_autoIncrement1D_waitOutChannel(context->autoincr1dIn1PingOutContext);
  }

  context->outIterIdx++;

  return (DMANODE_EdmaErr)status;
}


BAM_KernelInfo gBAM_TI_featMatchDmaNodeReadKernel =
{
    0,                  /*kernelId*/
    sizeof(BAM_DMA_NODE_FEAT_MATCH_context),
    sizeof(BAM_DMA_NODE_FEAT_MATCH_args),
    BAM_EVE_ARP32,      /*coreType*/
    BAM_NODE_SOURCE,    /*nodeType*/
    0,                  /*numInputDataBlocks */
    2,                  /*numOutputDataBlocks */
    0                   /*numRecInternal */
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_featMatchDmaNodeReadKernelHelperFunc =
{
    &BAM_DMA_IN_FEAT_MATCH_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    &BAM_DMA_IN_FEAT_MATCH_setMemRecFunc/* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_featMatchDmaNodeReadKernelExecFunc =
{
    NULL,
    &BAM_DMA_IN_FEAT_MATCH_frameInitChannel,
    &BAM_DMA_IN_FEAT_MATCH_trigger,
    &BAM_DMA_IN_FEAT_MATCH_wait,
    &BAM_DMA_IN_FEAT_MATCH_updateDDRptr,
    NULL
};



/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_featMatchDmaNodeWriteKernel =
{
  0,                  /*kernelId*/
  0,
  sizeof(BAM_DMA_NODE_FEAT_MATCH_args),
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_featMatchDmaNodeWriteKernelHelperFunc =
{
  &BAM_DMA_OUT_FEAT_MATCH_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
  &BAM_DMA_OUT_FEAT_MATCH_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_featMatchDmaNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_OUT_FEAT_MATCH_frameInitChannel,
  &BAM_DMA_OUT_FEAT_MATCH_trigger,
  &BAM_DMA_OUT_FEAT_MATCH_wait,
  &BAM_DMA_OUT_FEAT_MATCH_updateDDRptr,
  NULL
};

