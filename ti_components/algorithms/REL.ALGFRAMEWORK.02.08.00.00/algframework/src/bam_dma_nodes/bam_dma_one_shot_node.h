/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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
 *  bam_dma_one_shot_node.h
 *
 * @brief
 *  This file interfaces with the BAM dma node that triggers EDMA only one time
 *  when a specific triggerBlockId is reached.
 *  So to trigger at the beginning of the frame, set it to 0 and at the end, set it to the
 *  N-1 when N is the total number of blocks in the frame.
 *
 * @version 0.1 (Dec 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 */

#ifndef BAM_DMA_ONESHOT_NODE_H_
#define BAM_DMA_ONESHOT_NODE_H_

#include "bam_types.h"
#include "edma_utils_autoincrement.h"
#include "edma_bam_interface.h"

typedef struct {
    uint16_t    blkWidth;
    uint16_t    blkHeight;
    uint8_t     *extMemPtr;
    uint8_t     *interMemPtr;
    uint16_t    extMemPtrStride;
    uint16_t    interMemPtrStride;
} BAM_DMA_OneShot_transferProperties;

/**
*  @brief      DMA argument structure used to initialize the EDMA parameters
*/
typedef struct
{
    uint8_t    transferType;
    uint8_t    numInTransfers;
    uint8_t    numOutTransfers;
    int32_t    triggerBlockId;
    uint32_t   numTotalBlocksInFrame;  /* required because if it is a sink node because the scheduler needs to know when to stop */
    BAM_DMA_OneShot_transferProperties transferProp[NUM_MAX_TRANSFER_AUTOINCREMENT];
} BAM_DMA_OneShot_Args;

/**
*  @brief      Control structure used to pass new pointer and new stride in external memory after graph creation, before each execution.
*/
typedef struct
{
    uint8_t numTransfers;
    uint8_t *extMemPtr[NUM_MAX_TRANSFER_AUTOINCREMENT];
    uint16_t extMemPtrStride[NUM_MAX_TRANSFER_AUTOINCREMENT];
} BAM_DMA_OneShot_CtlArgs;

/**
*  @brief      DMA Read kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaOneShotReadKernel;

/**
*  @brief      DMA Read kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaReadOneShotKernelHelperFunc;

/**
*  @brief      DMA Read kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaReadOneShotKernelExecFunc;

/**
*  @brief      DMA Write kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaOneShotWriteKernel;

/**
*  @brief      DMA Write kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaWriteOneShotKernelHelperFunc;

/**
*  @brief      DMA Write kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaWriteOneShotKernelExecFunc;

#endif /* BAM_DMA_ONESHOT_NODE_H_ */

