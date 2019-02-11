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
 *  bam_dma_custom_fft_horz_node.c
 *
 * @brief
 *
 * @version 0.1 (Sept 2016) : First version of custom dma node for custom node for FFT in horziontal direction
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
#include "edma_utils_autoincrement.h"
#include "bam_dma_custom_fft_horz_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"

#define BAM_DMA_CUSTOM_FFT_HORZ_MAX_PITCH_SUPPORTED (32768U)

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
  uint8_t   autoIncrementDmaContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
  uint8_t  *intMemPtr;
  BAM_DMA_CUSTOM_FFT_HORZ_WRITE_ctrlArgs ctrlArgs;
}BAM_DMA_CUSTOM_FFT_HORZ_NODE_context;

/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_updateOutDDRptr(void * edmaContext,  void * params);




/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_getMemRecFunc(
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
      PRINTF("BAM_DMA_CUSTOM_FFT_HORZ_OUT_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_FFT_HORZ_NODE_context *dmaContext = (BAM_DMA_CUSTOM_FFT_HORZ_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (dmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_FFT_HORZ_OUT_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
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

static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_FFT_HORZ_NODE_context *dmaContext = (BAM_DMA_CUSTOM_FFT_HORZ_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_autoIncrement_initParam initArgs;
  uint32_t chunkIdx;
  uint32_t numTotalPoints;
  uint32_t numPointOffset;
  if (edmaContext == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_FFT_HORZ_OUT_frameInitChannel: Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if (errCode == DMANODE_EDMA_ERR_SUCCESS )
  {
      initArgs.numInTransfers = 0;
      initArgs.numOutTransfers = dmaContext->ctrlArgs.fftBufDescription->numChunks;
      initArgs.transferType = EDMA_UTILS_TRANSFER_INOUT;
      numTotalPoints = 0;

      for ( chunkIdx = 0; chunkIdx < initArgs.numOutTransfers; chunkIdx++)
      {
        numTotalPoints += dmaContext->ctrlArgs.fftBufDescription->numHorzPoints[chunkIdx];
      }

      numPointOffset = 0;

      for ( chunkIdx = 0; chunkIdx < initArgs.numOutTransfers; chunkIdx++)
      {
        initArgs.transferProp[chunkIdx].roiWidth           = dmaContext->ctrlArgs.numHorzBlock *
                              dmaContext->ctrlArgs.fftBufDescription->numHorzPoints[chunkIdx] * (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits);
        initArgs.transferProp[chunkIdx].roiHeight          = dmaContext->ctrlArgs.numVertBlock * dmaContext->ctrlArgs.numLinesPerBlock;
        initArgs.transferProp[chunkIdx].blkWidth           = dmaContext->ctrlArgs.fftBufDescription->numHorzPoints[chunkIdx] * (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits);
        initArgs.transferProp[chunkIdx].blkHeight          = dmaContext->ctrlArgs.numLinesPerBlock;
        initArgs.transferProp[chunkIdx].extBlkIncrementX   = dmaContext->ctrlArgs.fftBufDescription->numHorzPoints[chunkIdx] * (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits);
        initArgs.transferProp[chunkIdx].extBlkIncrementY   = dmaContext->ctrlArgs.numLinesPerBlock;
        initArgs.transferProp[chunkIdx].intBlkIncrementX   = 0;
        initArgs.transferProp[chunkIdx].intBlkIncrementY   = 0;
        initArgs.transferProp[chunkIdx].roiOffset          = 0;
        initArgs.transferProp[chunkIdx].blkOffset          = 0;
        if ( chunkIdx == 0)
        {
          initArgs.transferProp[chunkIdx].extMemPtr          = dmaContext->ctrlArgs.ptrToOutputBuf;
        }
        else
        {
          /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
          /* MISRA.PTR.ARITH:  Pointer is used in arithmetic or array index expression  */
          /*  Pointer arithmetic is required for performance like auto increment in loop. The harmful side effect of voilating this
            rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
                  initArgs.transferProp[chunkIdx].extMemPtr          = dmaContext->ctrlArgs.ptrToOutputBuf +
                       (chunkIdx * dmaContext->ctrlArgs.fftBufDescription->pitch[chunkIdx - 1U] *
                       dmaContext->ctrlArgs.fftBufDescription->numVertPoints);

        }
        initArgs.transferProp[chunkIdx].interMemPtr        = dmaContext->intMemPtr + (numPointOffset * (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits));
        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

        initArgs.transferProp[chunkIdx].extMemPtrStride    = dmaContext->ctrlArgs.numHorzBlock *
                              dmaContext->ctrlArgs.fftBufDescription->numHorzPoints[chunkIdx] * (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits);
        initArgs.transferProp[chunkIdx].interMemPtrStride  = numTotalPoints * (sizeof(int32_t)<<dmaContext->ctrlArgs.isOutput32bits);
        initArgs.transferProp[chunkIdx].dmaQueNo           = 1U;

        numPointOffset+= dmaContext->ctrlArgs.fftBufDescription->numHorzPoints[chunkIdx];
      }
      status = EDMA_UTILS_autoIncrement_init(dmaContext->autoIncrementDmaContext, &initArgs);

  }
  if ( status == 0 )
  {
    status = EDMA_UTILS_autoIncrement_configure(dmaContext->autoIncrementDmaContext, EDMA_UTILS_TRANSFER_INOUT);
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }

  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_FFT_HORZ_OUT_updateOutDDRptr(void * edmaContext,  void * params)
{
  BAM_DMA_CUSTOM_FFT_HORZ_NODE_context *context = (BAM_DMA_CUSTOM_FFT_HORZ_NODE_context *)edmaContext;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (context == NULL)
  {
      PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    BAM_DMA_CUSTOM_FFT_HORZ_WRITE_ctrlArgs * ctrlArgs =
                              (BAM_DMA_CUSTOM_FFT_HORZ_WRITE_ctrlArgs *)params;

      context->ctrlArgs = *ctrlArgs;
  }

  return errCode;
}


/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomFftHorzNodeWriteKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_FFT_HORZ_NODE_context),
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1U,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomFftHorzNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_FFT_HORZ_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_FFT_HORZ_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomFftHorzNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_FFT_HORZ_OUT_frameInitChannel,
  &EDMA_UTILS_autoIncrement_triggerOutChannel,
  &EDMA_UTILS_autoIncrement_waitOutChannel,
  &BAM_DMA_CUSTOM_FFT_HORZ_OUT_updateOutDDRptr,
  NULL
};


