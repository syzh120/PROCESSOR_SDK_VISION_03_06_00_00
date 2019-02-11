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
 *  bam_dma_custom_beam_forming_node.h
 *
 * @brief
 *
 * @version 0.1 (Dec 2016) : First version of custom dma node for custom node for Beam Forming Applet
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2016 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_CUSTOM_BEAM_FORMING_NODE_H_
#define BAM_DMA_CUSTOM_BEAM_FORMING_NODE_H_

#include "bam_types.h"
#include "edma_utils_context_size.h"
#include "edma_utils_scatterGather.h"
#include "xdais_types.h"

typedef struct
{
  uint16_t   maxNumDetectionPerBlock;
  uint16_t   maxNumTotalDetection;
  uint16_t   maxNumAntennas;
  uint16_t   maxNumAngles;
}BAM_DMA_CUSTOM_BEAM_FORMING_READ_initArgs;

typedef struct
{
  /* This pointer is shared between kernel node and DMA node and is used to
  decide whether to execute copy kernel or not */
  uint32_t  *enableSMcopyShared;
  uint8_t   *ptrToSteeringMatrix;
  uint8_t   *ptrToAntennaData;
  /* This buffer will store the sorted list of of angle and detection buffer and is expected
  to be present in DMEM for better performance */
  uint16_t   *ptrToAngleDetectionBuf;
  uint16_t   numDetections;
  uint16_t   numDetectionsPerBlock;
  uint16_t   numAntennas;
  uint16_t   numAngles;
}BAM_DMA_CUSTOM_BEAM_FORMING_READ_ctrlArgs;

typedef enum
{
  BAM_DMA_CUSTOM_BEAM_FORMING_ANTENNA_DATA_PORT = 0,
  BAM_DMA_CUSTOM_BEAM_FORMING_STEERING_MATRIX_PORT,
  /* This port is to share information between dma node and kernel node */
  BAM_DMA_CUSTOM_BEAM_FORMING_INFO_PORT,
  BAM_DMA_CUSTOM_BEAM_FORMING_NUM_OUTPUT_BLOCKS
} eBAM_DMA_CUSTOM_BEAM_FORMING_READ_OUTPUT_PORTS;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomBeamFormingNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomBeamFormingNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomBeamFormingNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomBeamFormingNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomBeamFormingNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomBeamFormingNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_BEAM_FORMING_NODE_H_ */

