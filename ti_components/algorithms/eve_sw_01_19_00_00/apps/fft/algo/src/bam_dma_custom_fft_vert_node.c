/*
*
* Copyright (c) 2016-2017 Texas Instruments Incorporated
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
 *  bam_dma_custom_fft_vert_node.c
 *
 * @brief
 *
 * @version 0.1 (Sept 2016) : First version of custom dma node for custom node for FFT in vertical direction
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2016 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/
#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_scatterGather.h"
#include "bam_dma_custom_fft_vert_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "bam_fft_npt_16ix32o.h"

#define BAM_DMA_CUSTOM_FFT_VERT_MAX_PITCH_SUPPORTED (32768U)

/*
  @param *inSrcPtr             Pointer to store the external memory location of the input image

  @param *inXYPtr              Pointer to store the memory location of XY list in DDR

  @param *blockPtrList[32]     Pointer to store the memory location of the 32 features

  @param *dstPtr               Pointer in internal memory where the transferred blocks are stored

  @param *inXYPtr_dmem         Pointer pointing to XY list in DMEM

*/

typedef struct
{
  /* Auto increment context should be the first entry as later we can directly use this
  context in EDMA_UTILS_autoIncrement1D_triggerInChannel calls */
  uint8_t   scatterGatherDmaContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  int16_t   blockIdx;
  int16_t   blockIdxHorz;
  int16_t   blockIdxVert;
  uint32_t  horzOffset;
  uint32_t  vertOffset;
  uint16_t  numHorzBlk;
  uint16_t  numVertBlk;
  uint16_t  numTotalBlk;
  uint8_t   *intMemPtr;
  uint8_t   *extMemBasePtr;
  uint8_t   *extDstPtr[1];
  uint8_t   *dstPtrStride[1];
  EDMA_UTILS_scattherGather_transferProperties updateParams;
  BAM_DMA_CUSTOM_FFT_VERT_WRITE_ctrlArgs ctrlArgs;
}BAM_DMA_CUSTOM_FFT_VERT_NODE_context;

/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_updateOutDDRptr(void * edmaContext,  void * params);




/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_getMemRecFunc(
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
      PRINTF("BAM_DMA_CUSTOM_FFT_VERT_OUT_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_FFT_VERT_NODE_context *dmaContext = (BAM_DMA_CUSTOM_FFT_VERT_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (dmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_FFT_VERT_OUT_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
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
          dmaContext->intMemPtr = (uint8_t *)memRecInputDataBlock[0]->base;
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

static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_FFT_VERT_NODE_context *dmaContext = (BAM_DMA_CUSTOM_FFT_VERT_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_scattherGather_transferProperties initArgs;
  uint8_t  *srcPtr[1];
  uint8_t  *dstPtr[1];
  uint16_t  srcStride[1];
  uint16_t  dstStride[1];
  uint16_t  blkWidth[1];
  uint16_t  blkHeight[1];
  uint16_t elmtSize;

  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_FFT_VERT_OUT_frameInitChannel: Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
       goto Exit;
       /* RESET_MISRA("14.4")  -> Reset rule 14.4  */

  }

  elmtSize= (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits);

  dmaContext->blockIdx    = -1;
  dmaContext->blockIdxHorz = 0;
  dmaContext->blockIdxVert = 0;
  dmaContext->horzOffset = dmaContext->ctrlArgs.numHorzPointsPerBlock * elmtSize;
  dmaContext->vertOffset = dmaContext->ctrlArgs.numVertPointsPerBlock * dmaContext->ctrlArgs.pitch;

  dmaContext->extDstPtr[0]  = dmaContext->ctrlArgs.ptrToOutputBuf;
  dmaContext->extMemBasePtr = dmaContext->ctrlArgs.ptrToOutputBuf;

  dmaContext->numHorzBlk = dmaContext->ctrlArgs.numAntennas;
  dmaContext->numVertBlk = ( dmaContext->ctrlArgs.numTotalVertPoints / dmaContext->ctrlArgs.numVertPointsPerBlock);
  dmaContext->numTotalBlk  = dmaContext->numHorzBlk * dmaContext->numVertBlk;

  /* Assign initargs pointers to the memory*/
  initArgs.blkWidth     = blkWidth;
  initArgs.blkHeight    = blkHeight;
  initArgs.srcPtr       = srcPtr;
  initArgs.dstPtr       = dstPtr;
  initArgs.srcPtrStride = srcStride;
  initArgs.dstPtrStride = dstStride;

  *(initArgs.blkWidth)     = dmaContext->ctrlArgs.numHorzPointsPerBlock * elmtSize;
  *(initArgs.blkHeight)    = dmaContext->ctrlArgs.numVertPointsPerBlock;
  *(initArgs.srcPtr)       = dmaContext->intMemPtr;
  *(initArgs.dstPtr)       = dmaContext->extDstPtr[0];

  if (dmaContext->ctrlArgs.isOutput32bits== 1) {
    *(initArgs.srcPtrStride) = (uint16_t)(dmaContext->ctrlArgs.numHorzPointsPerBlock) * elmtSize;
  }
  else {
    if (dmaContext->ctrlArgs.numVertPointsPerBlock == 512U)
    {
    *(initArgs.srcPtrStride) = (uint16_t)(dmaContext->ctrlArgs.numHorzPointsPerBlock) * elmtSize;
    }
    else /* Add 1 because for transpose we need one extra column in numVertPointsPerBlock is not 512 pts*/
    {
    *(initArgs.srcPtrStride) = (uint16_t)(dmaContext->ctrlArgs.numHorzPointsPerBlock + 1U) *elmtSize;
    }
  }
  *(initArgs.dstPtrStride) = dmaContext->ctrlArgs.pitch;
  initArgs.dmaQueNo     = 1U;

  status = EDMA_UTILS_scattherGather_init(dmaContext->scatterGatherDmaContext, &initArgs, 1U);

  if (status == 0 )
  {
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /*currently the function is hardcoded to return a value. Code is currently unreachable */
    /*but as the implementation of the function changes, it will not be unreachable*/
     status = EDMA_UTILS_scattherGather_configure(dmaContext->scatterGatherDmaContext);
    /* RESET_MISRA("14.1")  -> Reset rule 14.1  */
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
Exit:
  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_updateOutDDRptr(void * edmaContext,  void * params)
{
  BAM_DMA_CUSTOM_FFT_VERT_NODE_context *context = (BAM_DMA_CUSTOM_FFT_VERT_NODE_context *)edmaContext;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (context == NULL)
  {
      PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
     BAM_DMA_CUSTOM_FFT_VERT_WRITE_ctrlArgs * ctrlArgs =
                              (BAM_DMA_CUSTOM_FFT_VERT_WRITE_ctrlArgs *)params;

      context->ctrlArgs = *ctrlArgs;
  }

  return errCode;
}


BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_triggerOutChannel(void * edmaContext);

BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_triggerOutChannel(void * edmaContext)
{
    BAM_DMA_CUSTOM_FFT_VERT_NODE_context *context = (BAM_DMA_CUSTOM_FFT_VERT_NODE_context *)edmaContext;
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;
    int32_t         status = 0;

    if(context->blockIdx >= 0)
    {
        status = EDMA_UTILS_scattherGather_updateDstNtrigger(context->scatterGatherDmaContext, context->extDstPtr);
    }

    /* Indicate BAM to pipe down on encountering penultimate block */
    /* CHECK_MISRA("-13.7")  -> Disable rule 13.7  */
    /*  MISRA.BOOL.INVAR.TRUE : The condition is always true  */
    /* status will never be nonzero because we are exiting */
    /* in case of failures by having checks for various contitions above */
    if ((status != 0) || ((context->blockIdx + 1) >= (context->numTotalBlk - 1)))
    {
    /*RESET_MISRA("13.7")  -> Reset rule 13.7 for  MISRA.BOOL.INVAR.TRUE */
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;
}

BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_waitOutChannel(void * edmaContext);

BAM_Status BAM_DMA_CUSTOM_FFT_VERT_OUT_waitOutChannel(void * edmaContext)
{
    BAM_DMA_CUSTOM_FFT_VERT_NODE_context *context = (BAM_DMA_CUSTOM_FFT_VERT_NODE_context *)edmaContext;
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    if(context->blockIdx >= 0)
    {
        uint32_t addrOffset;
        context->blockIdxVert++;
        if ( context->blockIdxVert == context->numVertBlk)
        {
          context->blockIdxVert = 0;
          context->blockIdxHorz++;

        }
        addrOffset = (context->blockIdxHorz * context->horzOffset) +
                     (context->blockIdxVert * context->vertOffset);


        /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
        /* Pointer arithmetic is needed here to update the output pointer */
        /* The harmful side effect of voilating this rule (accessing outside valid memory) */
        /* shall be checked by another code checker like Klocwork */

        /* Update the destination pointer in DDR */
        context->extDstPtr[0] = context->extMemBasePtr + addrOffset;
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */
        context->blockIdx++;

        EDMA_UTILS_scattherGather_wait(context->scatterGatherDmaContext);
    }
    else
    {
      context->blockIdx++;
    }

    return errCode;
}

/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomFftVertNodeWriteKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_FFT_VERT_NODE_context),
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1U,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomFftVertNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_FFT_VERT_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_FFT_VERT_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomFftVertNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_FFT_VERT_OUT_frameInitChannel,
  &BAM_DMA_CUSTOM_FFT_VERT_OUT_triggerOutChannel,
  &BAM_DMA_CUSTOM_FFT_VERT_OUT_waitOutChannel,
  &BAM_DMA_CUSTOM_FFT_VERT_OUT_updateOutDDRptr,
  NULL
};


