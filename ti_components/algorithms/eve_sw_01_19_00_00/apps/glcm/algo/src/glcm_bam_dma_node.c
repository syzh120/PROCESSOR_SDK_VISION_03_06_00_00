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
 *******************************************************************************
 *
 * BAM DMA node for Gray-level Co-occurrence matrix applet
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  glcm_bam_dma_node.c
 *
 * @brief
 *
 * @version 0.1 (Jan 2014) : First version of custom dma node for glcm graph
 *
 *****************************************************************************
 */

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/
#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "glcm_bam_dma_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"

typedef struct
{
    uint8_t   autoincrementContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    uint16_t *intOutGlcmPtr;
    uint32_t *outGlcmAddr;
    uint16_t  numBlocks;
    uint16_t  numBlocksOrig;
}BAM_DMA_NODE_GLCM_context;

/* Following are the helper and exec functions of Source Node */
static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_frameInitChannel(
                       void * edmaContext);

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_updateDDRptr(
                  void * edmaContext,  void * params);


/* Sink node is a dummy node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_getMemRecFunc(
                  const void *edmaArgs,
                  BAM_MemRec memRecInternal[],
                  BAM_MemRec memRecOutputDataBlock[],
                  uint8_t *numRecInternal,
                  uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs);

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_updateDDRptr(
                  void * edmaContext,
                  void * params);

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_trigger(
                void *edmaContext);

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_wait(
                void *edmaContext);


/**************************************************************************************************/
/*                              SOURCE Node Helper and Exec Functions                             */
/**************************************************************************************************/

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    const EDMA_UTILS_autoIncrement_initParam *initParams = (const EDMA_UTILS_autoIncrement_initParam *)edmaArgs;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    /* Not checking memRecInternal pointer since it is not used in this function */
    if((initParams == NULL) || (numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
    {
      PRINTF("BAM_DMA_IN_CUSTOM_GLCM_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
      goto EXIT;
    }

    if(memRecOutputDataBlock == NULL)
    {
        PRINTF("BAM_DMA_IN_CUSTOM_GLCM_getMemRecFunc ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }

    if((initParams->transferProp[0].roiWidth <= 0U) ||
       (initParams->transferProp[0].roiHeight <= 0U))
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Image Dimensions!!\n");
        errCode = DMANODE_EDMA_ERR_INVALID_IMAGE_DIM;
        goto EXIT;
    }

    if((initParams->transferProp[0].blkWidth <= 0U) ||
       (initParams->transferProp[0].blkHeight <= 0U))
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Image Dimentions!!\n");
        errCode = DMANODE_EDMA_ERR_INVALID_BLOCK_DIM;
        goto EXIT;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    /* Request memory in image buffer for holding the output block for DMA node */
    memRecOutputDataBlock[0].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[0].size = initParams->transferProp[0].blkWidth*initParams->transferProp[0].blkHeight;
    memRecOutputDataBlock[0].alignment = 32;

    *numRecOutputDataBlock = 1U;
    *numRecInternal = 0;

EXIT:
    return errCode;
}

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
    BAM_DMA_NODE_GLCM_context *context = (BAM_DMA_NODE_GLCM_context *)edmaContext;
    EDMA_UTILS_autoIncrement_initParam *initParams= (EDMA_UTILS_autoIncrement_initParam*)edmaArgs;
    int32_t status = 0;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    if(context == NULL)
    {
        PRINTF("BAM_DMA_IN_CUSTOM_GLCM_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }

    if(memRecOutputDataBlock != NULL)
    {
      if(memRecOutputDataBlock[0]->base == NULL)
      {
        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
        goto EXIT;
      }

      /* Set internal memory pointer */
      initParams->transferProp[0].interMemPtr = (uint8_t *)memRecOutputDataBlock[0]->base;
    }
    else
    {
      errCode = DMANODE_EDMA_ERR_FAILED;
      goto EXIT;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */


    status = EDMA_UTILS_autoIncrement_init(context->autoincrementContext, initParams);

    context->numBlocks = (((initParams->transferProp[0].roiWidth  - initParams->transferProp[0].blkWidth )/initParams->transferProp[0].extBlkIncrementX) + 1)*
                         (((initParams->transferProp[0].roiHeight - initParams->transferProp[0].blkHeight)/initParams->transferProp[0].extBlkIncrementY) + 1);
    context->numBlocksOrig = context->numBlocks;

    if(status != 0)
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

EXIT:
    return errCode;
}

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_frameInitChannel(
                       void * edmaContext)
{
  int32_t status = 0;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_NODE_GLCM_context *context = (BAM_DMA_NODE_GLCM_context *)edmaContext;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if (context == NULL)
  {
    PRINTF("BAM_DMA_IN_CUSTOM_GLCM_frameInitChannel ERROR :\
                        Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    goto EXIT;
  }

  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  status = EDMA_UTILS_autoIncrement_configure(context->autoincrementContext, EDMA_UTILS_TRANSFER_IN);
  if ( status != 0 )
  {
    errCode = DMANODE_EDMA_ERR_FAILED;
    goto EXIT;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

EXIT:
    return errCode;
}

static BAM_Status BAM_DMA_IN_CUSTOM_GLCM_updateDDRptr(
                  void * edmaContext,  void * params)
{
    EDMA_UTILS_autoIncrement_updateParams *updateParams= (EDMA_UTILS_autoIncrement_updateParams*)params;
    BAM_DMA_NODE_GLCM_context *context = (BAM_DMA_NODE_GLCM_context *)edmaContext;
    int32_t                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    if (context == NULL)
    {
        PRINTF("BAM_DMA_IN_CUSTOM_GLCM_updateDDRptr ERROR :\
                          Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }

    if (updateParams == NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : updateParams NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    updateParams->transferType = EDMA_UTILS_TRANSFER_IN;
    status = EDMA_UTILS_autoIncrement_update(context->autoincrementContext, updateParams);

    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /* The returned status may or may not be zero. The below if() condition is a valid condition.   */

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }
    /* RESET_MISRA("14.1")  -> Reset rule 14.1     */

EXIT:
    return errCode;
}


/**************************************************************************************************/
/*                              SINK Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if((numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
    {
      PRINTF("BAM_DMA_OUT_GLCM_DUMMY_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
    }

    return errCode;
}

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
    BAM_DMA_NODE_GLCM_context *context = (BAM_DMA_NODE_GLCM_context *)edmaContext;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    if( memRecInputDataBlock )
    {
        if(memRecInputDataBlock[0]->base == NULL)
        {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          goto EXIT;
        }

        context->intOutGlcmPtr = (uint16_t *)memRecInputDataBlock[0]->base;
    }
    else
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
        goto EXIT;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

EXIT:
    return errCode;
}

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_updateDDRptr(
                  void * edmaContext,  void * params)
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_autoIncrement_updateParams *updateParams= (EDMA_UTILS_autoIncrement_updateParams*)params;
  BAM_DMA_NODE_GLCM_context *context = (BAM_DMA_NODE_GLCM_context *)edmaContext;

  if (edmaContext == NULL)
  {
    PRINTF("BAM_DMA_OUT_GLCM_DUMMY_updateDDRptr ERROR :\
                      Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  context->outGlcmAddr = (uint32_t*)(void *)updateParams->updateParams[0].extMemPtr;

 EXIT:
    return errCode;

}


static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_trigger(void * edmaContext)
{
  BAM_DMA_NODE_GLCM_context *context = (BAM_DMA_NODE_GLCM_context *)edmaContext;
  int32_t status = 0;

  /* Indicate BAM to pipe down on encountering penultimate block */
  if(context->numBlocks <= 1)
  {
    *context->outGlcmAddr = *((uint32_t *)(void *)context->intOutGlcmPtr);
    status = 1;
    context->numBlocks = context->numBlocksOrig;
  }
  else {
    context->numBlocks--;
  }

  return (DMANODE_EdmaErr)status;
}

static BAM_Status BAM_DMA_OUT_GLCM_DUMMY_wait(void * edmaContext)
{
  int32_t status = 0;

  return (BAM_Status)status;
}


BAM_KernelInfo gBAM_TI_glcmDmaNodeReadKernel =
{
    0,                  /*kernelId*/
    sizeof(BAM_DMA_NODE_GLCM_context),
    sizeof(EDMA_UTILS_autoIncrement_initParam),
    BAM_EVE_ARP32,      /*coreType*/
    BAM_NODE_SOURCE,    /*nodeType*/
    0,                  /*numInputDataBlocks */
    1,                  /*numOutputDataBlocks */
    0                   /*numRecInternal */
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_glcmDmaNodeReadKernelHelperFunc =
{
    &BAM_DMA_IN_CUSTOM_GLCM_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
    &BAM_DMA_IN_CUSTOM_GLCM_setMemRecFunc/* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_glcmDmaNodeReadKernelExecFunc =
{
    NULL,
    &BAM_DMA_IN_CUSTOM_GLCM_frameInitChannel,
    &EDMA_UTILS_autoIncrement_triggerInChannel,
    &EDMA_UTILS_autoIncrement_waitInChannel,
    &BAM_DMA_IN_CUSTOM_GLCM_updateDDRptr,
    NULL
};



/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_glcmDmaNodeWriteKernel =
{
  0,                  /*kernelId*/
  0,
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1,                  /*numInputDataBlocks */
  0,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_glcmDmaNodeWriteKernelHelperFunc =
{
  &BAM_DMA_OUT_GLCM_DUMMY_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
  &BAM_DMA_OUT_GLCM_DUMMY_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_glcmDmaNodeWriteKernelExecFunc =
{
  NULL,
  NULL,
  &BAM_DMA_OUT_GLCM_DUMMY_trigger,
  &BAM_DMA_OUT_GLCM_DUMMY_wait,
  &BAM_DMA_OUT_GLCM_DUMMY_updateDDRptr,
  NULL
};

