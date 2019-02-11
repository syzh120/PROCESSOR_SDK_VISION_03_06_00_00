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
 *  bam_dma_custom_cfar_ca_doppler_node.c
 *
 * @brief
 *
 * @version 0.1 (Aug 2017) : First version of custom dma node for CFAR CA Doppler graph
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
#include "edma_utils_autoincrement.h"
#include "edma_utils_scatterGather.h"
#include "bam_dma_custom_cfar_ca_doppler_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "ipeak_detection_ti.h"
#include "bam_dma_autoincrement_node.h"

#define BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IMG_BUF_A_B_OFFSET (0x20000U)
#define BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IMG_BUF_L_H_OFFSET (0x4000U)


#define BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES (32U)
#define BAM_DMA_CUSTOM_CFAR_CA_MAX_RANGE_DIMENSION (1024U)
#define BAM_DMA_CUSTOM_CFAR_CA_MAX_DOPPLER_DIMENSION (512U)

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN(x,y)         (((x) + (y) - 1U)/(y))*(y)
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


typedef struct
{
  const uint8_t  *srcPtr[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES + 1U];
}BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_SCATTERIN_MEM;

typedef struct
{
  uint8_t  *srcPtr[2];
  uint8_t  *dstPtr[2];
  uint16_t  stride[2];
  uint16_t  blkWidth[2];
}BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_SCATTEROUT_MEM;

/*
  @param *inSrcPtr             Pointer to store the external memory location of the input image

  @param *inXYPtr              Pointer to store the memory location of XY list in DDR

  @param *blockPtrList[32]     Pointer to store the memory location of the 32 features

  @param *dstPtr               Pointer in internal memory where the transferred blocks are stored

  @param *inXYPtr_dmem         Pointer pointing to XY list in DMEM

*/

typedef struct
{
  uint8_t   inAutoIncrement1DDmaContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
  uint8_t   inScatterGatherDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t   outScatterGatherDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t   *intMemEnergyPtr1;
  uint8_t   *intMemEnergyPtr2;
  uint8_t   *intMemCurrRangeIndexBuf;
  uint16_t  *pListSize;
  uint8_t   *dstStartPtr[2];
  uint16_t  numTotalBlk;
  int16_t   blkIdxOut;
  uint8_t   pingPongFlagIn;
  uint8_t   pingPongFlagOut;
  uint8_t   exitConditionDetected;
  uint8_t   finalExitCondition;
  int8_t    getFinalListSize;
  uint32_t  *pIntNumDetections[2];
  uint16_t   detectionIdx;
  uint8_t   rangeIndexBuf[BAM_DMA_CUSTOM_CFAR_CA_MAX_RANGE_DIMENSION];
  uint16_t  zeroBuf[BAM_DMA_CUSTOM_CFAR_CA_MAX_DOPPLER_DIMENSION];
  uint32_t  indexBufShared[2][BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES * 2U];
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_SCATTERIN_MEM scatterInMem;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_SCATTEROUT_MEM scatterOutMem;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs  dmaArgs;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ctrlArgs  dmaCtrlArgs;
  EDMA_UTILS_scattherGather_transferProperties updateParamsIn;
  EDMA_UTILS_scattherGather_transferProperties updateParamsOut;
}BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context;



/* Source node is a scatter gather node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_updateDDRptr(
                  void * edmaContext,  void * params);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_wait(void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_trigger(void * edmaContext);


/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_updateOutDDRptr(void * edmaContext,  void * params);


static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_trigger(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_wait(
                void * edmaContext);


/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* Rule : Pointer parameter is not used to modify the addressed object but is not declared as pointer to const */
/* Falsely detected by klocwork   */
static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[2],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
/*RESET_MISRA("16.7")  -> Reset rule 16.7 for  MISRA.PPARAM.NEEDS.CONST*/
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  /* CHECK_MISRA("-11.5")  -> Disable rule 11.5  */
  /* Rule : Cast operation removes const or volatile modifier from a pointer or reference */
  /* Falsely detected by klocwork   */
  const BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs * dmaArgs = (const BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs *)edmaArgs;
  /*RESET_MISRA("11.5")  -> Reset rule 11.5 for MISRA.CAST.CONST */

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal == NULL ) || (numRecOutputDataBlock == NULL))
  {
    PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_getMemRecFunc ERROR : Argument pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    *numRecOutputDataBlock = BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NUM_OUTPUT_BLOCKS;
    *numRecInternal = 0;

    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    /* Allocate the maximum list size that can be processed */
    /* allocate extra BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES * 4 * 2 bytes to store the current range index. This buffer
    will be used to imbed range index into the detected doppler index */
    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT].size = ( (dmaArgs->maxNumPoints *
                                                                 dmaArgs->maxNumLines *
                                                                 sizeof(uint16_t))/2U) + dmaArgs->maxExtraBufferRequired  +
                                                                 (2U * BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES * sizeof(uint32_t));
    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT].alignment  = 32U;

    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT].space = BAM_MEMSPACE_IBUFHA;
    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    /* Allocate the maximum list size that can be processed */
    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT].size = ( (dmaArgs->maxNumPoints *
                                                                 dmaArgs->maxNumLines *
                                                                 sizeof(uint16_t))/2U );
    memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT].alignment  = 32U;

  }

  return errCode;
}

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* Rule : Pointer parameter is not used to modify the addressed object but is not declared as pointer to const */
/* Falsely detected by klocwork   */
static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
/*RESET_MISRA("16.7")  -> Reset rule 16.7 for  MISRA.PPARAM.NEEDS.CONST*/
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *context = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;

  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  /* CHECK_MISRA("-11.5")  -> Disable rule 11.5  */
  /* Rule : Cast operation removes const or volatile modifier from a pointer or reference */
  /* Falsely detected by klocwork   */
  const BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs * dmaArgs = (const BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs *)edmaArgs;
  /*RESET_MISRA("11.5")  -> Reset rule 11.5 for MISRA.CAST.CONST */

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  }

  context->dmaArgs = *dmaArgs;

  if( memRecOutputDataBlock )
  {
    if(memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    if(memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    context->intMemEnergyPtr1 = (uint8_t *) memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT]->base;
    context->intMemEnergyPtr2 = (uint8_t *) memRecOutputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT]->base;
    context->intMemCurrRangeIndexBuf =  (uint8_t *)(*(uint8_t (*)[])(void *)context->intMemEnergyPtr1 +
                                        (( (dmaArgs->maxNumPoints *
                                             dmaArgs->maxNumLines *
                                             sizeof(uint16_t))/2U) + dmaArgs->maxExtraBufferRequired));

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

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_updateDDRptr(
                  void * edmaContext,  void * params)
{

  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ctrlArgs * ctrlArgs =
              (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ctrlArgs *)params;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *context =
              (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;

  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_updateDDRptr ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  context->dmaCtrlArgs = *ctrlArgs;

EXIT:
    return errCode;

}

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *dmaContext = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint8_t  *dstPtr[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES + 1U];
  uint16_t  srcStride[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES + 1U];
  uint16_t  dstStride[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES  + 1U];
  uint16_t  blkWidth[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES + 1U];
  uint16_t  blkHeight[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_MAX_NUMLINES + 1U];
  uint16_t i;
  uint16_t rangeIdx;
  uint16_t detectionBlockIdx;

  if (edmaContext == NULL)  {
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_frameInitChannel ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }
  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  memset(dmaContext->rangeIndexBuf, 0 , BAM_DMA_CUSTOM_CFAR_CA_MAX_RANGE_DIMENSION);
  memset(dmaContext->zeroBuf      , 0 , BAM_DMA_CUSTOM_CFAR_CA_MAX_DOPPLER_DIMENSION * sizeof(uint16_t));
  dmaContext->detectionIdx = 0;
  dmaContext->pingPongFlagIn = 0;
  dmaContext->exitConditionDetected = 0;
  dmaContext->getFinalListSize =0;

  dmaContext->updateParamsIn.updateMask   = (EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W |
                                              EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE);
  dmaContext->updateParamsIn.dmaQueNo     = 0;
  /* CHECK_MISRA("-11.5")  -> Disable rule 11.5  */
  /* Rule : Cast operation removes const or volatile modifier from a pointer or reference */
  /* Fixing this will  involve changing ivision interface and as this interface is already widely in use we have decided to
  waive this issue for such incidences   */
  dmaContext->updateParamsIn.srcPtr       = (uint8_t **)dmaContext->scatterInMem.srcPtr;
  /*RESET_MISRA("11.5")  -> Reset rule 11.5 for MISRA.CAST.CONST */
  dmaContext->updateParamsIn.dstPtr       = dstPtr;
  dmaContext->updateParamsIn.srcPtrStride = srcStride;
  dmaContext->updateParamsIn.dstPtrStride = dstStride;
  dmaContext->updateParamsIn.blkWidth     = blkWidth;
  dmaContext->updateParamsIn.blkHeight    = blkHeight;

  /* We have to split each line in doppler dimension in half. Half of the buffer needs to be transferred in L buffer and other half in H buffer.
  To do this we visualize each input line of doppler dimension as a 2 D buffer of width = dopplerDim / 2 and height = 2. Now if we consider
  desitnation stride to be 16KB (gap between L and H) buffer then we automatically get the other of line in H buffer */
  for ( i = 0; i < dmaContext->dmaCtrlArgs.numDetectionsPerBlock; i++)
  {
    dstPtr[i]       = *(uint8_t (*)[])(void *)dmaContext->intMemEnergyPtr1 + (i * (dmaContext->dmaCtrlArgs.dopplerDim / (uint16_t)2U) * (uint16_t)sizeof(uint16_t));
    srcStride[i] = (dmaContext->dmaCtrlArgs.dopplerDim/ (uint16_t)2U) * (uint16_t)sizeof(uint16_t);
    dstStride[i] = BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IMG_BUF_L_H_OFFSET;
    blkWidth[i]     = (dmaContext->dmaCtrlArgs.dopplerDim / (uint16_t)2U) * (uint16_t)sizeof(uint16_t);
    blkHeight[i]    = 2U;
  }

  detectionBlockIdx = 0;
  for ( i = 0; i < dmaContext->dmaCtrlArgs.numDetections; i++)
  {
    rangeIdx = (*dmaContext->dmaCtrlArgs.rangeDopplerCoordinateBuf)[(2U * i) + 1U];
    dmaContext->detectionIdx++;
    /* Check if this range has already been used */
    if ( dmaContext->rangeIndexBuf[rangeIdx] == 0 )
    {
      dmaContext->scatterInMem.srcPtr[detectionBlockIdx] = (const uint8_t *)(const void *)( &(*dmaContext->dmaCtrlArgs.energyPtrExtMem)[rangeIdx * dmaContext->dmaCtrlArgs.dopplerDim]);
      dmaContext->rangeIndexBuf[rangeIdx] = 1U;
      dmaContext->indexBufShared[dmaContext->pingPongFlagIn][detectionBlockIdx] = (uint32_t)((uint32_t)rangeIdx << (uint32_t)16U);
      dmaContext->indexBufShared[dmaContext->pingPongFlagIn][detectionBlockIdx +
        (dmaContext->dmaCtrlArgs.numDetectionsPerBlock)] = ( (uint32_t)((uint32_t)rangeIdx << (uint32_t)16U) + (uint32_t)((uint32_t)dmaContext->dmaCtrlArgs.dopplerDim/2U));
      detectionBlockIdx++;
      if (detectionBlockIdx == dmaContext->dmaCtrlArgs.numDetectionsPerBlock)
      {
        break;
      }
    }
  }

  if ( i == dmaContext->dmaCtrlArgs.numDetections)
  {
    dmaContext->exitConditionDetected = 1U;
    dmaContext->getFinalListSize = 0;
  }
  else
  {
#if VCOP_HOST_EMULATION
    dmaContext->getFinalListSize = (int8_t)-1;
#else
    dmaContext->getFinalListSize = (int8_t)-2;
#endif
  }

  if ( (detectionBlockIdx % dmaContext->dmaCtrlArgs.numDetectionsPerBlock) != 0 )
  {
    for ( i = 0; i < (dmaContext->dmaCtrlArgs.numDetectionsPerBlock - (detectionBlockIdx % dmaContext->dmaCtrlArgs.numDetectionsPerBlock)); i++)
    {
      dmaContext->scatterInMem.srcPtr[detectionBlockIdx + i] = (uint8_t *)dmaContext->zeroBuf;
    }
  }

  dstPtr[dmaContext->dmaCtrlArgs.numDetectionsPerBlock]       = dmaContext->intMemCurrRangeIndexBuf;
  srcStride[dmaContext->dmaCtrlArgs.numDetectionsPerBlock] = 0;
  dstStride[dmaContext->dmaCtrlArgs.numDetectionsPerBlock] = 0;
  blkWidth[dmaContext->dmaCtrlArgs.numDetectionsPerBlock]     = (uint16_t)2U * dmaContext->dmaCtrlArgs.numDetectionsPerBlock * (uint16_t)sizeof(uint32_t);
  blkHeight[dmaContext->dmaCtrlArgs.numDetectionsPerBlock]    = 1U;
  dmaContext->scatterInMem.srcPtr[dmaContext->dmaCtrlArgs.numDetectionsPerBlock]       = (uint8_t *)(void *)dmaContext->indexBufShared[dmaContext->pingPongFlagIn];

  /* Setup Index buffer transfer by DMA */

  status = EDMA_UTILS_scattherGather_init(dmaContext->inScatterGatherDmaContext , &(dmaContext->updateParamsIn), dmaContext->dmaCtrlArgs.numDetectionsPerBlock + 1U);

  if (status == 0 )
  {
     status = EDMA_UTILS_scattherGather_configure(dmaContext->inScatterGatherDmaContext);
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }

EXIT:

  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *dmaContext = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;


  /* Trigger the transfer */
  EDMA_UTILS_scattherGather_updateSrcNtrigger(dmaContext->inScatterGatherDmaContext, dmaContext->updateParamsIn.srcPtr);

  dmaContext->pingPongFlagIn ^= 1U;

  return errCode;
}



static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_wait(void * edmaContext)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *dmaContext = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint32_t i;
  uint16_t rangeIdx;
  uint16_t detectionBlockIdx = 0;
  uint16_t currDetectionIdx  = dmaContext->detectionIdx;

  for ( i = currDetectionIdx; i < dmaContext->dmaCtrlArgs.numDetections ; i++)
  {
    rangeIdx = (*dmaContext->dmaCtrlArgs.rangeDopplerCoordinateBuf)[(2U * i) + 1U];
    dmaContext->detectionIdx++;
    /* Check if this range has already been used */
    if ( dmaContext->rangeIndexBuf[rangeIdx] == 0 )
    {
      dmaContext->scatterInMem.srcPtr[detectionBlockIdx] = (const uint8_t *)(const void *)(&(*dmaContext->dmaCtrlArgs.energyPtrExtMem)[rangeIdx * dmaContext->dmaCtrlArgs.dopplerDim]);
      dmaContext->rangeIndexBuf[rangeIdx] = 1U;
      dmaContext->indexBufShared[dmaContext->pingPongFlagIn][detectionBlockIdx] = (uint32_t)rangeIdx << 16U;
      dmaContext->indexBufShared[dmaContext->pingPongFlagIn][detectionBlockIdx +
        (dmaContext->dmaCtrlArgs.numDetectionsPerBlock)] = ((uint32_t)rangeIdx << 16U) + (uint32_t)((uint32_t)dmaContext->dmaCtrlArgs.dopplerDim/2U);

      detectionBlockIdx++;
      if (detectionBlockIdx == dmaContext->dmaCtrlArgs.numDetectionsPerBlock)
      {
        break;
      }
    }
  }
  if ( i == dmaContext->dmaCtrlArgs.numDetections)
  {
    dmaContext->exitConditionDetected++;
  }

  if ( ((detectionBlockIdx % dmaContext->dmaCtrlArgs.numDetectionsPerBlock) != 0) || (detectionBlockIdx == 0) )
  {
    if ( dmaContext->finalExitCondition == 0)
    {
      for ( i = detectionBlockIdx; i < dmaContext->dmaCtrlArgs.numDetectionsPerBlock; i++)
      {
        dmaContext->scatterInMem.srcPtr[i] = (uint8_t*)dmaContext->zeroBuf;
      }
    }
  }

  dmaContext->scatterInMem.srcPtr[dmaContext->dmaCtrlArgs.numDetectionsPerBlock] = (uint8_t *)(void *)dmaContext->indexBufShared[dmaContext->pingPongFlagIn];

  EDMA_UTILS_scattherGather_wait(dmaContext->inScatterGatherDmaContext);

  return errCode;
}


/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_getMemRecFunc(
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
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *dmaContext = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (dmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
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
      if(memRecInputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_RANGE_DOPPLER_PORT]->base == NULL)
      {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto EXIT;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
      }

      if(memRecInputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ENERGY_PORT]->base == NULL)
      {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto EXIT;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
      }

      if(memRecInputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_NUM_DETECTION_PORT]->base == NULL)
      {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
          /* GOTO is used at error check to jump to end of function, to exit.   */
          goto EXIT;
          /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
      }

      dmaContext->scatterOutMem.srcPtr[0] = (uint8_t *)memRecInputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_RANGE_DOPPLER_PORT]->base;
      dmaContext->scatterOutMem.srcPtr[1] = (uint8_t *)memRecInputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ENERGY_PORT]->base;

      dmaContext->pIntNumDetections[0] = (uint32_t *)memRecInputDataBlock[BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_NUM_DETECTION_PORT]->base;
#if (!VCOP_HOST_EMULATION)
      dmaContext->pIntNumDetections[1] = *(uint32_t (*)[])(void *)dmaContext->pIntNumDetections[0] + (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IMG_BUF_A_B_OFFSET / sizeof(uint32_t));
#else
      dmaContext->pIntNumDetections[1] = dmaContext->pIntNumDetections[0];
#endif
    }
    EXIT:

  return errCode;

}

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *dmaContext = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint16_t  blkHeight[2];

  if (edmaContext == NULL)  {
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_frameInitChannel ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  }

  dmaContext->pingPongFlagOut = 0;
  *(dmaContext->pIntNumDetections[0]) = 0;
  dmaContext->pingPongFlagOut^= 1U;
  dmaContext->finalExitCondition = 0U;

  dmaContext->scatterOutMem.stride[0] = 0;
  dmaContext->scatterOutMem.stride[1] = 0;
  dmaContext->scatterOutMem.blkWidth[0] = 1U;/* Actual width will be decided during before trigger*/
  dmaContext->scatterOutMem.blkWidth[1] = 1U;/* Actual width will be decided during before trigger*/
  blkHeight[0] = 1U;
  blkHeight[1] = 1U;
  dmaContext->blkIdxOut = -1;

  dmaContext->updateParamsOut.updateMask   = (EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W |
                                        EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE);
  dmaContext->updateParamsOut.dmaQueNo     = 1U;
  dmaContext->updateParamsOut.srcPtr       = dmaContext->scatterOutMem.srcPtr;
  dmaContext->updateParamsOut.dstPtr       = dmaContext->scatterOutMem.dstPtr;
  dmaContext->updateParamsOut.srcPtrStride = dmaContext->scatterOutMem.stride;
  dmaContext->updateParamsOut.dstPtrStride = dmaContext->scatterOutMem.stride;
  dmaContext->updateParamsOut.blkWidth     = dmaContext->scatterOutMem.blkWidth;
  dmaContext->updateParamsOut.blkHeight    = blkHeight;

  status = EDMA_UTILS_scattherGather_init(dmaContext->outScatterGatherDmaContext , &(dmaContext->updateParamsOut), 2U);

  if (status == 0 )
  {
     status = EDMA_UTILS_scattherGather_configure(dmaContext->outScatterGatherDmaContext);
  }

  if ( dmaContext->exitConditionDetected)
  {
    dmaContext->finalExitCondition = 1U;
  }
  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
EXIT:
  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_updateOutDDRptr(void * edmaContext,  void * params)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *context = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ctrlArgs * ctrlArgs =
                            (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ctrlArgs *)params;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_updateOutDDRptr ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      context->scatterOutMem.dstPtr[0] = ctrlArgs->ptrToRangeDopplerBuf;
      context->scatterOutMem.dstPtr[1] = ctrlArgs->ptrToEnergyBuf;

      context->dstStartPtr[0] = ctrlArgs->ptrToRangeDopplerBuf;
      context->dstStartPtr[1] = ctrlArgs->ptrToEnergyBuf;

      context->pListSize = (uint16_t *)(void *)ctrlArgs->ptrToNumDetectionBuf;

  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_trigger(void * edmaContext)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *context = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint16_t   numDetections;

  if ( context->blkIdxOut != -1 )
  {
    numDetections = (uint16_t)(*context->pIntNumDetections[context->pingPongFlagOut]);
    /* Update the amount of transfer to be done based on the list size returned by the kernel */
    context->scatterOutMem.blkWidth[0]     = (uint16_t)(numDetections << 2);/* 4 * numDetections */
    context->scatterOutMem.blkWidth[1]     = (uint16_t)(numDetections << 1);/* 2 * numDetections */

    /* Trigger the transfer */
    EDMA_UTILS_scattherGather_updateNtrigger(context->outScatterGatherDmaContext, &(context->updateParamsOut));
  }

  context->pingPongFlagOut ^= 1U;

  /* Indicate BAM to pipe down on encountering penultimate block */
  /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
  /*  MISRA.BOOL.INVAR.TRUE :   The condition is always true  */
   /* Status will never be 0 because we are passing all the correct parameters to the function above and hence all the error conditions inside the function
  will never occur.*/
  if (context->finalExitCondition)
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
  /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */

  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_wait(void * edmaContext)
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *context = (BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  if(context->exitConditionDetected)
  {
    context->getFinalListSize++;
    if ( context->exitConditionDetected == 2U)
    {
      context->finalExitCondition = 1U;
    }
  }

  if ( context->blkIdxOut != -1 )
  {
    /* Update the destination pointer in DDR */
    context->scatterOutMem.dstPtr[0] = *(uint8_t (*)[])(void *)context->scatterOutMem.dstPtr[0] + context->scatterOutMem.blkWidth[0];
    context->scatterOutMem.dstPtr[1] = *(uint8_t (*)[])(void *)context->scatterOutMem.dstPtr[1] + context->scatterOutMem.blkWidth[1];

    EDMA_UTILS_scattherGather_wait(context->outScatterGatherDmaContext);

  }

  /* ------------------------------------------------------------- */
  /* Update block position                                         */
  /* ------------------------------------------------------------- */
  context->blkIdxOut++;
  if(context->getFinalListSize == 2U)
  {

      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* Rule :  Cast converts pointer to integral type    */
      /*  To calculate pointer difference, we need to convert them   */
      /* Return the list size */
      *context->pListSize = (uint16_t)(((uintptr_t )context->scatterOutMem.dstPtr[0] - (uintptr_t )context->dstStartPtr[0])/sizeof(uint32_t ));
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT  */

      /* Restore back to initial state at end of pipeline */
      context->blkIdxOut = -1;
      context->getFinalListSize = 0;

      context->scatterOutMem.dstPtr[0] = context->dstStartPtr[0];
      context->scatterOutMem.dstPtr[1] = context->dstStartPtr[1];
  }

  return errCode;
}


BAM_KernelInfo gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NODE_context),
  0,
  BAM_EVE_ARP32,                      /*coreType*/
  BAM_NODE_SOURCE,                    /*nodeType*/
  0,                                  /*numInputDataBlocks */
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NUM_OUTPUT_BLOCKS,                                  /*numOutputDataBlocks */
  0                                   /*numRecInternal */
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernelHelperFunc =
{
   &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
   &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_setMemRecFunc/* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernelExecFunc =
{
  NULL,
   &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_frameInitChannel,
   &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_trigger,
   &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_wait,
   &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_IN_updateDDRptr,
   NULL
};



/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernel =
{
  0,                                    /*kernelId*/
  0,
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_NUM_OUTPUT_BLOCKS,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_frameInitChannel,
  &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_trigger,
  &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_wait,
  &BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_OUT_updateOutDDRptr,
  NULL
};


