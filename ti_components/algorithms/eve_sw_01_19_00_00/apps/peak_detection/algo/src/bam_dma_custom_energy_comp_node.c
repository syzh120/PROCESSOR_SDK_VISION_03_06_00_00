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
 *  bam_dma_custom_energy_comp_node.c
 *
 * @brief
 *
 * @version 0.1 (Apr 2017) : First version of custom dma node for custom node for Energy computation graph
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

#include "bam_dma_custom_energy_comp_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_autoincrement_1d.h"

#include "ipeak_detection_ti.h"

typedef struct
{
  uint8_t   autoIncrementContext1D[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
  uint8_t   autoIncrementContext2D[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
  uint8_t  *antennaDataIntPtr;
  uint8_t  *outputEnergyIntPtr;
  BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs initArgs;
  BAM_DMA_CUSTOM_ENERGY_COMP_ctrlArgs ctrlArgs;
}BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context;

/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_updateOutDDRptr(void * edmaContext,  void * params);

BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_waitInChannel(void * edmaContext);
BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_triggerInChannel(void * edmaContext);


static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_getMemRecFunc(
                    const void *edmaArgs,
                    BAM_MemRec *memRecInternal,
                    BAM_MemRec *memRecOutputDataBlock,
                    uint8_t *numRecInternal,
                    uint8_t *numRecOutputDataBlock);



static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_frameInitChannel(
                void * edmaContext);



BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_triggerInChannel(void * edmaContext);



BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_waitInChannel(void * edmaContext);





/**************************************************************************************************/
/*                              Source Node Helper and Exec Functions                               */
/**************************************************************************************************/
static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_getMemRecFunc(
                    const void *edmaArgs,
                    BAM_MemRec memRecInternal[],
                    BAM_MemRec memRecOutputDataBlock[],
                    uint8_t *numRecInternal,
                    uint8_t *numRecOutputDataBlock)
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  const BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs * initArgs = (const BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs *)edmaArgs;

  /* Choose strides such that with this as a pitch each memory location falls into different memory bank */
  /* For this we can choose any odd number greater than or equal to 9 words */

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal== NULL ) || ( numRecOutputDataBlock == NULL) )
  {
      PRINTF("BAM_DMA_CUSTOM_ENERGY_COMP_IN_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    /* Kernel Node will re-use this buffer to store the output of matrix multiplication and hence allocate the worst case memory */
    memRecOutputDataBlock[BAM_DMA_CUSTOM_ENERGY_COMP_ANTENNA_DATA_PORT].size = initArgs->maxNumPoints *
                                                                               initArgs->maxNumRowsPerBlock * sizeof(int16_t) * 2;

    memRecOutputDataBlock[BAM_DMA_CUSTOM_ENERGY_COMP_ANTENNA_DATA_PORT].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[BAM_DMA_CUSTOM_ENERGY_COMP_ANTENNA_DATA_PORT].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;

    *numRecOutputDataBlock = 1U;
    *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  const BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs * dmaArgs = (const BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs *)edmaArgs;


  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_ENERGY_COMP_IN_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  context->initArgs = *dmaArgs;

  if( memRecOutputDataBlock )
  {

    if(memRecOutputDataBlock[BAM_DMA_CUSTOM_ENERGY_COMP_ANTENNA_DATA_PORT]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    context->antennaDataIntPtr= (uint8_t *) memRecOutputDataBlock[BAM_DMA_CUSTOM_ENERGY_COMP_ANTENNA_DATA_PORT]->base;


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

static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_autoIncrement1D_initParam initParams;

  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_ENERGY_COMP_IN_frameInitChannel: Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  initParams.numInTransfers   = 1;
  initParams.numOutTransfers  = 0;
  initParams.transferType = EDMA_UTILS_TRANSFER_IN;

  initParams.transferProp[0].totalLength = context->ctrlArgs.numAntennas * context->ctrlArgs.numHorzPointPerAnetnna *
                                           context->ctrlArgs.numRows * sizeof(int16_t) * 2;
  initParams.transferProp[0].numBytes    = context->ctrlArgs.numAntennas * context->ctrlArgs.numHorzPointPerAnetnna *
                                           context->ctrlArgs.numRowsPerBlock * sizeof(int16_t) * 2;
  initParams.transferProp[0].numCircBuf  = 1;
  initParams.transferProp[0].extMemPtr   = context->ctrlArgs.ptrToAntennaData;
  initParams.transferProp[0].interMemPtr = context->antennaDataIntPtr;
  initParams.transferProp[0].extMemIncrement = initParams.transferProp[0].numBytes;
  initParams.transferProp[0].intMemIncrement = 0;
  initParams.transferProp[0].dmaQueNo = 0;

  status = EDMA_UTILS_autoIncrement1D_init(context->autoIncrementContext1D,&initParams);

  if ( status == 0 )
  {
    status = EDMA_UTILS_autoIncrement1D_configure(context->autoIncrementContext1D, EDMA_UTILS_TRANSFER_IN);
  }
  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
Exit:
  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_IN_updateOutDDRptr(void * edmaContext,  void * params)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (context == NULL)
  {
      PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    BAM_DMA_CUSTOM_ENERGY_COMP_ctrlArgs * ctrlArgs =
                              (BAM_DMA_CUSTOM_ENERGY_COMP_ctrlArgs *)params;
    context->ctrlArgs = *ctrlArgs;
  }

  return errCode;
}


/**************************************************************************************************/
/*                              Sink Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_getMemRecFunc(
                    const void *edmaArgs,
                    BAM_MemRec *memRecInternal,
                    BAM_MemRec *memRecOutputDataBlock,
                    uint8_t *numRecInternal,
                    uint8_t *numRecOutputDataBlock)
{

  BAM_Status  errCode = DMANODE_EDMA_ERR_SUCCESS;

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal == NULL) || (numRecOutputDataBlock == NULL ))
  {
      PRINTF("BAM_DMA_CUSTOM_ENERGY_COMP_OUT_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;


  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_ENERGY_COMP_OUT_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  if( memRecInputDataBlock )
  {

    if(memRecInputDataBlock[BAM_SINK_NODE_PORT1]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }
    context->outputEnergyIntPtr = (uint8_t *)memRecInputDataBlock[BAM_SINK_NODE_PORT1]->base;
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

static BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_frameInitChannel(
                void * edmaContext)
{
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_autoIncrement_initParam initParams;
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  int32_t                 status = 0;
  uint16_t                transposePitch;
  uint16_t                numWordsRequired;

  numWordsRequired = context->ctrlArgs.numRowsPerBlock/(uint16_t)2U;
  if ( numWordsRequired < 9U )
  {
    numWordsRequired = 9U;
  }

  transposePitch = ( ((numWordsRequired % 2U) == 0 ) ? (numWordsRequired + 1U) : numWordsRequired);
  transposePitch = transposePitch * sizeof(uint32_t);

  initParams.numInTransfers   = 0;
  initParams.numOutTransfers  = 1U;
  initParams.transferType     = EDMA_UTILS_TRANSFER_INOUT;
  initParams.transferProp[0].roiWidth         = context->ctrlArgs.dopplerDim * sizeof(uint16_t);
  initParams.transferProp[0].roiHeight        = context->ctrlArgs.rangeDim;
  initParams.transferProp[0].blkWidth         = context->ctrlArgs.numRowsPerBlock * sizeof(uint16_t);
  initParams.transferProp[0].blkHeight        = context->ctrlArgs.numHorzPointPerAnetnna;
  initParams.transferProp[0].extBlkIncrementX = initParams.transferProp[0].blkWidth;
  initParams.transferProp[0].extBlkIncrementY = initParams.transferProp[0].blkHeight;
  initParams.transferProp[0].intBlkIncrementX = 0;
  initParams.transferProp[0].intBlkIncrementY = 0;
  initParams.transferProp[0].roiOffset        = 0;
  initParams.transferProp[0].blkOffset        = 0;
  initParams.transferProp[0].extMemPtr        = context->ctrlArgs.ptrToEnergyBuf;
  initParams.transferProp[0].interMemPtr      = context->outputEnergyIntPtr;
  initParams.transferProp[0].extMemPtrStride  = initParams.transferProp[0].roiWidth;
  initParams.transferProp[0].interMemPtrStride = transposePitch;
  initParams.transferProp[0].dmaQueNo = 1U;

  status = EDMA_UTILS_autoIncrement_init(context->autoIncrementContext2D,&initParams);

  if ( status == 0 )
  {
    status = EDMA_UTILS_autoIncrement_configure(context->autoIncrementContext2D, EDMA_UTILS_TRANSFER_INOUT);
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }

  return errCode;
}

BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_triggerChannel(void * edmaContext);

BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_triggerChannel(void * edmaContext)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  int32_t status;

  status = EDMA_UTILS_autoIncrement_triggerOutChannel(context->autoIncrementContext2D);

  return status;
}

BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_waitChannel(void * edmaContext);

BAM_Status BAM_DMA_CUSTOM_ENERGY_COMP_OUT_waitChannel(void * edmaContext)
{
  BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *context = (BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context *)edmaContext;
  int32_t status;

  status = EDMA_UTILS_autoIncrement_waitOutChannel(context->autoIncrementContext2D);

  return status;
}



/* Source Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomEnergyCompNodeReadKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_ENERGY_COMP_NODE_context),
  sizeof(BAM_DMA_CUSTOM_ENERGY_COMP_READ_initArgs),
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SOURCE,      /*nodeType*/
  0U,                  /*numInputDataBlocks */
  3U,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomEnergyCompNodeReadKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_ENERGY_COMP_IN_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_ENERGY_COMP_IN_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomEnergyCompNodeReadKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_ENERGY_COMP_IN_frameInitChannel,
  &EDMA_UTILS_autoIncrement1D_triggerInChannel,
  &EDMA_UTILS_autoIncrement1D_waitInChannel,
  &BAM_DMA_CUSTOM_ENERGY_COMP_IN_updateOutDDRptr,
  NULL
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomEnergyCompNodeWriteKernel =
{
  0,                                    /*kernelId*/
  0,
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SINK,      /*nodeType*/
  1U,                  /*numInputDataBlocks */
  0U,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomEnergyCompNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_ENERGY_COMP_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_ENERGY_COMP_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomEnergyCompNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_ENERGY_COMP_OUT_frameInitChannel,
  &BAM_DMA_CUSTOM_ENERGY_COMP_OUT_triggerChannel,
  &BAM_DMA_CUSTOM_ENERGY_COMP_OUT_waitChannel,
  NULL,
  NULL
};


