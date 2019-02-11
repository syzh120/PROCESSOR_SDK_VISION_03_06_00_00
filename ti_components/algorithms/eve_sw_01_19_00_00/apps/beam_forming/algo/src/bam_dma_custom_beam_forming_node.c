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
 *  bam_dma_custom_beam_forming_node.c
 *
 * @brief
 *
 * @version 0.1 (Sept 2016) : First version of custom dma node for custom node for Beam Forming
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

#include "bam_dma_custom_beam_forming_node.h"
#include "bam_beam_forming.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "ibeam_forming_ti.h"
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7 */
/* Function-like macro definition */
/* Deviation is allowed because this is a simple operation best implemented through a macro */
#define BAM_DMA_CUSTOM_BEAM_FORMING_MAX(a,b) (((a)>(b)) ? (a) : (b))
/*RESET_MISRA("19.7")  -> Reset rule 19.7 */

#define BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK (16U)
#define BAM_DMA_CUSTOM_BEAM_FORMING_IMG_BUF_A_B_OFFSET      (0x20000U)


typedef struct
{
  uint16_t detectionId;
  uint16_t binAngle;
}BAM_DMA_CUSTOM_BEAM_FORMING_angleDetection;

typedef struct
{
  uint8_t   dmaContextAntennaData[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t   dmaContextSteeringMatrix[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
  uint8_t  *antennaDataIntPtr;
  uint8_t  *steeringMatIntPtr;
  uint8_t   enableSMcopy;
  uint8_t   exitCondition;
  uint32_t  exitConditionCount;
  uint8_t   avoidFinalWait;
  uint8_t   pingPongFlag;
  uint8_t   groupChangeDetected;
  uint16_t  currGroupId;
  uint16_t  lastGroupId;
  uint16_t  currGroupDetectionCount;
  uint16_t  lastValidDetectionCount;
  uint16_t  steeringMatrixSize;
  uint8_t   *steeringMatrixExtPtr[1];
  BAM_DMA_CUSTOM_BEAM_FORMING_angleDetection (*ptrToAngleDetectionBuf)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS];
  BAM_BeamForming_Info  *infoPtr[2];
  BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs initArgs;
  BAM_DMA_CUSTOM_BEAM_FORMING_READ_ctrlArgs ctrlArgs;
  /* This is the memory to store the set of pointers corresponding to a particular angle in the input
  antenna data buffer */
  uint8_t   *srcPtrAntennaData[BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK];
}BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context;

/* Sink node is a 1D autoincrement node. Following are its helper and exec functions */
static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_getMemRecFunc(
                  const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                  uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_frameInitChannel(
                void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_updateOutDDRptr(void * edmaContext,  void * params);

BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_waitInChannel(void * edmaContext);
BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_triggerInChannel(void * edmaContext);


static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_getMemRecFunc(
                    const void *edmaArgs,
                    BAM_MemRec *memRecInternal,
                    BAM_MemRec *memRecOutputDataBlock,
                    uint8_t *numRecInternal,
                    uint8_t *numRecOutputDataBlock);



static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs);


static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_frameInitChannel(
                void * edmaContext);



BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_triggerInChannel(void * edmaContext);



BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_waitInChannel(void * edmaContext);





/**************************************************************************************************/
/*                              Source Node Helper and Exec Functions                               */
/**************************************************************************************************/
static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_getMemRecFunc(
                    const void *edmaArgs,
                    BAM_MemRec memRecInternal[],
                    BAM_MemRec memRecOutputDataBlock[],
                    uint8_t *numRecInternal,
                    uint8_t *numRecOutputDataBlock)
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  const BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs * initArgs = (const BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs *)edmaArgs;

  uint32_t steeringMatrixSize;
  uint32_t antennaDataSize;
  uint32_t antennaDataTransposeSize;
  uint32_t matrixMulSize;
  uint32_t interimEnergySize;
  uint16_t transposePitch;
  uint32_t max1;

  /* Choose strides such that with this as a pitch each memory location falls into different memory bank */
  /* For this we can choose any odd number greater than or equal to 9 words */
  transposePitch = (((initArgs->maxNumDetectionPerBlock % 2U) ? initArgs->maxNumDetectionPerBlock :
                            initArgs->maxNumDetectionPerBlock + 1U)) * sizeof(uint32_t);

  steeringMatrixSize = initArgs->maxNumAngles * initArgs->maxNumAntennas * sizeof(int16_t) * 2U;
  antennaDataSize    = initArgs->maxNumDetectionPerBlock * initArgs->maxNumAntennas * sizeof(int16_t) * 2U;
  antennaDataTransposeSize    = ALIGN_SIMD(initArgs->maxNumAntennas) * transposePitch;
  matrixMulSize      = initArgs->maxNumAngles * initArgs->maxNumDetectionPerBlock * sizeof(int16_t) * 2U;
  interimEnergySize  = initArgs->maxNumAngles * initArgs->maxNumDetectionPerBlock * sizeof(uint32_t);

  /* Not checking memRecInternal pointer since it is not used in this function */
  if ( (numRecInternal== NULL ) || ( numRecOutputDataBlock == NULL) )
  {
      PRINTF("BAM_DMA_CUSTOM_BEAM_FORMING_IN_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    /* Kernel Node will re-use this buffer to store the output of matrix multiplication and hence allocate the worst case memory */
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_ANTENNA_DATA_PORT].size = BAM_DMA_CUSTOM_BEAM_FORMING_MAX(antennaDataSize , matrixMulSize);
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_ANTENNA_DATA_PORT].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_ANTENNA_DATA_PORT].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;

    /* Kernel Node will re-use this buffer to store the transpose and hence allocate the worst case memory */
    max1 = BAM_DMA_CUSTOM_BEAM_FORMING_MAX(antennaDataTransposeSize,steeringMatrixSize);
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_STEERING_MATRIX_PORT].size =  BAM_DMA_CUSTOM_BEAM_FORMING_MAX(max1,interimEnergySize);
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_STEERING_MATRIX_PORT].space = BAM_MEMSPACE_IBUFHA;
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_STEERING_MATRIX_PORT].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;

    /*This port will only contain information on whether to do SM copy or not. Based on this kernel will enable/disable copy kernel */
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_INFO_PORT].size = sizeof(BAM_BeamForming_Info);
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_INFO_PORT].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_INFO_PORT].attrs.memAttrs= BAM_MEMATTRS_CONST;

    *numRecOutputDataBlock = 3U;
    *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  const BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs * dmaArgs = (const BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs *)edmaArgs;


  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_BEAM_FORMING_IN_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  context->initArgs = *dmaArgs;

  if( memRecOutputDataBlock )
  {

    if(memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_ANTENNA_DATA_PORT]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    context->antennaDataIntPtr= (uint8_t *) memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_ANTENNA_DATA_PORT]->base;


    if(memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_STEERING_MATRIX_PORT]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    context->steeringMatIntPtr = (uint8_t *) memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_STEERING_MATRIX_PORT]->base;

    if(memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_INFO_PORT]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    context->infoPtr[0] = (BAM_BeamForming_Info  *) memRecOutputDataBlock[BAM_DMA_CUSTOM_BEAM_FORMING_INFO_PORT]->base;
#if VCOP_HOST_EMULATION
    context->infoPtr[1] = context->infoPtr[0];
#else
    /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
    /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
    /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
    context->infoPtr[1] = (BAM_BeamForming_Info *)(void *)((uint8_t *)(void *)context->infoPtr[0] +
                           BAM_DMA_CUSTOM_BEAM_FORMING_IMG_BUF_A_B_OFFSET );
    /* RESET_MISRA("17.4")  -> Reset rule 17.4     */

#endif

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

static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_frameInitChannel(
                void * edmaContext)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  EDMA_UTILS_scattherGather_transferProperties initParams;
  uint8_t * dstPtrList[BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK];
  uint16_t  blockWidth[BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK];
  uint16_t  blockHeight[BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK];
  uint16_t  srcPtrStride[BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK];
  uint16_t  dstPtrStride[BAM_DMA_CUSTOM_BEAM_FORMING_MAX_DETECTION_PER_BLOCK];
  uint32_t i;
  uint32_t detectionId;

  uint32_t validDetectionCount = 0;

  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_BEAM_FORMING_IN_frameInitChannel: Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
  EDMA_UTILS_globalReset();

  /* Initialize DMA context parameters */
  context->ptrToAngleDetectionBuf = (BAM_DMA_CUSTOM_BEAM_FORMING_angleDetection (*)[BEAM_FORMING_TI_MAX_NUM_DETECTIONS])(void*) context->ctrlArgs.ptrToAngleDetectionBuf;
  /* First time we always need to copy */
  (*context->ctrlArgs.enableSMcopyShared) = 1U;
  context->enableSMcopy = 1U;
  context->groupChangeDetected = 0U;
  context->currGroupDetectionCount = 0U;
  context->exitCondition = 0;
  context->pingPongFlag = 0;
  context->steeringMatrixSize = context->ctrlArgs.numAngles * context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U;
  context->avoidFinalWait = 0;

  context->currGroupId = 0;
  context->exitConditionCount = ALIGN_SIMD(context->ctrlArgs.numDetections);


#if VCOP_HOST_EMULATION
    context->exitConditionCount = context->ctrlArgs.numDetections - 1U;
#endif

  initParams.blkWidth     = blockWidth;
  initParams.blkHeight    = blockHeight;
  initParams.srcPtr       = context->srcPtrAntennaData;
  initParams.srcPtrStride = srcPtrStride;
  initParams.dstPtr       = dstPtrList;
  initParams.dstPtrStride = dstPtrStride;


  initParams.dmaQueNo = 0;
  /* These parameters wont change throughout the process */
  for ( i = 0; i < context->ctrlArgs.numDetectionsPerBlock; i++)
  {
    blockWidth[i]      = (uint16_t)context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U;
    blockHeight[i]     = 1U;
    srcPtrStride[i]  = 1U;
    dstPtrStride[i]  = 1U;
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from based on user given parameters and hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork static analyis     */
    dstPtrList[i]        = context->antennaDataIntPtr + (blockWidth[i] * i);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
  }


  for ( i = 0 ; i < context->ctrlArgs.numDetectionsPerBlock; i++)
  {
    detectionId = context->currGroupDetectionCount + i;
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from based on user given parameters and hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork    */
    context->srcPtrAntennaData[i]  = context->ctrlArgs.ptrToAntennaData +
                                (detectionId * context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U);

    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    validDetectionCount++;
  }

  /* Increment the base count of detection */
  context->currGroupDetectionCount += validDetectionCount;
  context->lastValidDetectionCount = validDetectionCount;
  context->lastGroupId             = context->currGroupId;
  /* This information is shared between kernel node and dma node */
  /* In this function call we are writing to ping buffer (A) and after buffer switch this buffer should be visible to kernel node */
  context->infoPtr[context->pingPongFlag]->numValidDetection = context->lastValidDetectionCount;
  context->infoPtr[context->pingPongFlag]->baseAngleOffset   = context->currGroupId * context->ctrlArgs.numAngles;

  if ( context->currGroupDetectionCount > context->exitConditionCount )
  {
    context->exitCondition = 1U;
  }

  /* First configure Antenna Data Transfer */
  status = EDMA_UTILS_scattherGather_init(context->dmaContextAntennaData, &initParams,context->ctrlArgs.numDetectionsPerBlock);

  /* Now confiure steering matrix EDMA transfer */
  if ( status == 0)
  {
    /* Use separate memory to hold src pointer for SM as only this will change and dst address
    will not change */
    initParams.srcPtr = context->steeringMatrixExtPtr;

    blockWidth[0] = (uint16_t)context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U;
    blockHeight[0] = context->ctrlArgs.numAngles;
    context->steeringMatrixExtPtr[0] = context->ctrlArgs.ptrToSteeringMatrix;
    srcPtrStride[0] = (uint16_t)context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U;
    dstPtrList[0] = context->steeringMatIntPtr;
    dstPtrStride[0] = (uint16_t)context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U;
    initParams.dmaQueNo = 1U;

    /* Initialize steering matrix to point to the one corresponding to first angle in the list */
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from based on user given parameters and hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork    */
    context->steeringMatrixExtPtr[0] = context->ctrlArgs.ptrToSteeringMatrix +
                                     (context->steeringMatrixSize * context->currGroupId);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    status = EDMA_UTILS_scattherGather_init(context->dmaContextSteeringMatrix, &initParams,1U);
  }

  if ( status != 0 )
  {
      errCode = DMANODE_EDMA_ERR_FAILED;
  }
Exit:
  return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_updateOutDDRptr(void * edmaContext,  void * params)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  if (context == NULL)
  {
      PRINTF("BIN_IMG2LIST_BAM_DMA ERROR : Context Structure pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }

  if ( errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
    BAM_DMA_CUSTOM_BEAM_FORMING_READ_ctrlArgs * ctrlArgs =
                              (BAM_DMA_CUSTOM_BEAM_FORMING_READ_ctrlArgs *)params;

      context->ctrlArgs = *ctrlArgs;
  }

  return errCode;
}


BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_triggerInChannel(void * edmaContext)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;

#if !VCOP_HOST_EMULATION
  if ( context->exitCondition == 0)
#endif
  {
    if ( context->enableSMcopy )
    {
      EDMA_UTILS_scattherGather_updateSrcNtrigger(context->dmaContextSteeringMatrix,context->steeringMatrixExtPtr);
    }
    EDMA_UTILS_scattherGather_updateSrcNtrigger(context->dmaContextAntennaData,context->srcPtrAntennaData);
  }
  return 0;
}


BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_IN_waitInChannel(void * edmaContext)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;
  uint32_t i,detectionId;
  uint32_t validDetectionCount = 0;
  uint32_t currExitCondition = context->exitCondition;
  uint32_t isSMcopyEnabled = context->enableSMcopy;



  for (i = 0; i < context->ctrlArgs.numDetectionsPerBlock; i++)
  {
    detectionId = context->currGroupDetectionCount + i;
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from based on user given parameters and hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    context->srcPtrAntennaData[i]  = context->ctrlArgs.ptrToAntennaData +
                                (detectionId * context->ctrlArgs.numAntennas * sizeof(int16_t) * 2U);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    validDetectionCount++;
  }
  context->enableSMcopy = 0;
  /* Write to the IBUF to share that kernel needs to disable copy SM */
  (*context->ctrlArgs.enableSMcopyShared) =  0U;

  /* This information is shared between kernel node and dma node */
  /* In this function call we are writing to ping buffer (A) and after buffer switch this buffer should be visible to kernel node */
#if VCOP_HOST_EMULATION
  context->infoPtr[context->pingPongFlag]->numValidDetection = validDetectionCount;
#else
  context->infoPtr[context->pingPongFlag]->numValidDetection = context->lastValidDetectionCount;
#endif
  context->infoPtr[context->pingPongFlag]->baseAngleOffset   = context->currGroupId * context->ctrlArgs.numAngles;

  /* Kernel is in delay of one block for processing compared to DMA and hence we always update last valid detection instead
  of current valid detection */
  context->lastValidDetectionCount = validDetectionCount;
  context->lastGroupId = context->currGroupId;

  context->currGroupDetectionCount += validDetectionCount;

  if ( context->exitCondition == 1)
  {
    context->avoidFinalWait = 1;
  }

  if ( context->currGroupDetectionCount > context->exitConditionCount)
  {
    context->exitCondition = 1U;
  }

  /* Toggle ping pong buffer flag */
  context->pingPongFlag ^= 1U;

  if ( currExitCondition == 0)
  {
    if (isSMcopyEnabled)
    {
      EDMA_UTILS_scattherGather_wait(context->dmaContextSteeringMatrix);
    }
  }

#if !VCOP_HOST_EMULATION
  if ( context->avoidFinalWait == 0)
#endif
  {
    EDMA_UTILS_scattherGather_wait(context->dmaContextAntennaData);
  }

  return 0;
}


/**************************************************************************************************/
/*                              Sink Node Helper and Exec Functions                               */
/**************************************************************************************************/

static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_getMemRecFunc(
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
      PRINTF("BAM_DMA_CUSTOM_BEAM_FORMING_OUT_getMemRecFunc ERROR : Argument pointer is NULL\n");
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
  }

  if(errCode == DMANODE_EDMA_ERR_SUCCESS)
  {
      *numRecOutputDataBlock = 0;
      *numRecInternal = 0;
  }

  return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_setMemRecFunc(
                  const BAM_MemRec *memRecInternal[],
                  const BAM_MemRec *memRecInputDataBlock[],
                  const BAM_MemRec *memRecOutputDataBlock[],
                  uint8_t numRecInternal,
                  uint8_t numRecInputDataBlock,
                  uint8_t numRecOutputDataBlock,
                  void *edmaContext,
                  const void *edmaArgs)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;


  if (context == NULL)
  {
      PRINTF("BAM_DMA_CUSTOM_BEAM_FORMING_OUT_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
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

static BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_frameInitChannel(
                void * edmaContext)
{
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

  return errCode;
}


BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_triggerInChannel(void * edmaContext)
{
  BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *context = (BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context *)edmaContext;

  return context->exitCondition;
}


BAM_Status BAM_DMA_CUSTOM_BEAM_FORMING_OUT_waitInChannel(void * edmaContext)
{

  return DMANODE_EDMA_ERR_SUCCESS;
}


/* Source Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomBeamFormingNodeReadKernel =
{
  0,                                    /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_BEAM_FORMING_NODE_context),
  0,
  BAM_EVE_ARP32,      /*coreType*/
  BAM_NODE_SOURCE,      /*nodeType*/
  0U,                  /*numInputDataBlocks */
  3U,                  /*numOutputDataBlocks */
  0                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomBeamFormingNodeReadKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_BEAM_FORMING_IN_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_BEAM_FORMING_IN_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomBeamFormingNodeReadKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_BEAM_FORMING_IN_frameInitChannel,
  &BAM_DMA_CUSTOM_BEAM_FORMING_IN_triggerInChannel,
  &BAM_DMA_CUSTOM_BEAM_FORMING_IN_waitInChannel,
  &BAM_DMA_CUSTOM_BEAM_FORMING_IN_updateOutDDRptr,
  NULL
};

/* Source Node kernel Info, helper, and exec functions */
BAM_KernelInfo gBAM_TI_dmaCustomBeamFormingNodeWriteKernel =
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


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomBeamFormingNodeWriteKernelHelperFunc =
{
     &BAM_DMA_CUSTOM_BEAM_FORMING_OUT_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_CUSTOM_BEAM_FORMING_OUT_setMemRecFunc /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomBeamFormingNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_BEAM_FORMING_OUT_frameInitChannel,
  &BAM_DMA_CUSTOM_BEAM_FORMING_OUT_triggerInChannel,
  &BAM_DMA_CUSTOM_BEAM_FORMING_OUT_waitInChannel,
  NULL,
  NULL
};


