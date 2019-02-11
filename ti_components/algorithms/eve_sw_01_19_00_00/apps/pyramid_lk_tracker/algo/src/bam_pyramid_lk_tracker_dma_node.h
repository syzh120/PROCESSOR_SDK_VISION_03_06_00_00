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
 *  bam_pyramid_lk_tracker_dma_node.h
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of dma node for pyramid lk tracker
 *
 *****************************************************************************
 */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_PYRAMID_LK_TRACKER_DMA_NODE_H_
#define BAM_PYRAMID_LK_TRACKER_DMA_NODE_H_

#include "bam_types.h"
#include "edma_bam_interface.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"

/*Limited by the number of param entries available for EDMA programming*/
#define VCOP_LK_MAX_NUM_KEY_PER_CALL     (16)
#define NUM_MAX_SCATTER_GATHER_TRANSFERS      (VCOP_LK_MAX_NUM_KEY_PER_CALL*2)
#define VCOP_LK_PATCH_WIDTH          (7) /* 7x7*/

typedef struct
{
  uint8_t *  currBaseAddr;
  uint8_t *  prevBaseAddr;
  uint16_t  imPitch;
  uint16_t  imWidth;
  uint16_t  imHeight;
  uint16_t  numKeyPoints;
  uint16_t  numValidKeyPoints;
  uint8_t   currLevel;
  uint8_t   maxItersLK;
  uint16_t  minErrValue;
  uint8_t   searchRange;
  uint8_t*  srcAddrList[2][2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint8_t *  prevXYAddr[2];
  uint8_t *  cornerListInXY;
  uint8_t *  cornerListOutXY;
  uint8_t *  cornerListErrMeasure;
}EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args;

typedef struct
{
    uint8_t     *extMemPtr;
    uint16_t    extMemPtrStride;
}EDMA_UTILS_pyramidlktracker_transfer_updatePrams;
typedef struct
{
    EDMA_UTILS_pyramidlktracker_transfer_updatePrams updateParams[2];
}EDMA_UTILS_pyramidlktracker_tranfer_params;

typedef struct
{
  uint16_t  imPitch;
  uint16_t  imWidth;
  uint16_t  imHeight;
  uint16_t  numKeyPoints;
  uint16_t  numValidKeyPoints;
  uint8_t   currLevel;
  uint8_t   maxItersLK;
  uint16_t  minErrValue;
  uint8_t   searchRange;
  uint8_t * cornerListInXY;
  uint8_t * cornerListOutXY;
  uint8_t * cornerListErrMeasure;
  EDMA_UTILS_pyramidlktracker_tranfer_params srcNodeParams;
  EDMA_UTILS_pyramidlktracker_tranfer_params sinkNodeParams;
  uint16_t  numInvalidPoints;
  uint16_t  SADthreshold;
}EDMA_UTILS_pyramidlktracker_dma_ctrl_args;

typedef struct
{
    uint8_t   autoIncrContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    uint8_t   scatterGatherContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];

    uint8_t   numKeyPointsProcessedPerCall;
    uint16_t  totalKeyPointsCompute;
    uint8_t   numScatterGatherTransfers;
    uint16_t  prevFrmblkWidth;
    uint16_t  prevFrmblkHeight;
    uint16_t  prevFrmsrcPtrStride;
    uint16_t  prevFrmdstPtrStride;
    uint16_t  currFrmblkWidth;
    uint16_t  currFrmblkHeight;
    uint16_t  currFrmsrcPtrStride;
    uint16_t  currFrmdstPtrStride;

    uint16_t  blkIdxIn;
    uint16_t  numTotalBlks;

    uint8_t   pingPongFlag;
    uint8_t *  outDataInterMemPtr[2];

    uint8_t  *prevFrmInterMemPtr[1];
    uint8_t  *currFrmInterMemPtr[1];
    uint8_t  *iterativeLoopLAMemPtr[1];
    uint8_t  *iterativeLoopHAMemPtr[1];
    EDMA_UTILS_scattherGather_transferProperties    inBlksScatterGatherTransferContext;
    EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs;
    uint16_t    *numInvalidPointsPtrExt;
    uint16_t    *numInvalidPointsPtrInt[2];
    uint16_t    *ouputErrEstimateInt[2];
    uint8_t     lastTrigger;
    uint16_t    SADthreshold;
}EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT;

typedef struct
{
    uint8_t     numKeyPointsProcessedPerCall;
    uint16_t    totalKeyPointsCompute;
    uint8_t     numScatterGatherTransfers;
    uint16_t    prevFrmblkWidth;
    uint16_t    prevFrmblkHeight;
    uint16_t    prevFrmsrcPtrStride;
    uint16_t    prevFrmdstPtrStride;
    uint16_t    currFrmblkWidth;
    uint16_t    currFrmblkHeight;
    uint16_t    currFrmsrcPtrStride;
    uint16_t    currFrmdstPtrStride;
    EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs;
}EDMA_UTILS_pyramidlktracker_dmaReadInitParam;

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaReadGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaReadSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_frameInitInChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_frameInitOutChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_dmaReadUpdateDDRptr(void * edmaContext,  void * params);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteUpdateDDRptr(void * edmaContext,  void * params);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_triggerInChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_waitInChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_triggerOutChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_waitOutChannel(void * edmaContext);

/**
*  @brief      DMA Read kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaPyramidLKTrackerReadKernel;

/**
*  @brief      DMA Read kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaReadPyramidLKTrackerKernelHelperFunc;

/**
*  @brief      DMA Read kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaReadPyramidLKTrackerKernelExecFunc;

/**
*  @brief      DMA Write kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaPyramidLKTrackerWriteKernel;

/**
*  @brief      DMA Write kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaWritePyramidLKTrackerKernelHelperFunc;

/**
*  @brief      DMA Write kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaWritePyramidLKTrackerKernelExecFunc;

#endif /* BAM_PYRAMID_LK_TRACKER_DMA_NODE_H_ */
