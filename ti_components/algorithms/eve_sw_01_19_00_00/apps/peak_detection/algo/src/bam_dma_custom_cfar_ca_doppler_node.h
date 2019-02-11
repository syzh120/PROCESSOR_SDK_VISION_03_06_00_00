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
 *  bam_dma_custom_cfar_ca_doppler_node.h
 *
 * @brief
 *
 * @version 0.1 (Apr 2017) : First version of custom dma node for custom node for CFAR CA Doppler graph
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2016 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_CUSTOM_CFAR_DOPPLER_CA_NODE_H_
#define BAM_DMA_CUSTOM_CFAR_DOPPLER_CA_NODE_H_

#include "bam_types.h"
#include "edma_utils_context_size.h"
#include "edma_utils_scatterGather.h"
#include "xdais_types.h"

typedef struct
{
  uint16_t   maxNumPoints;
  uint16_t   maxNumLines;
  uint16_t   maxExtraBufferRequired;
}BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_initArgs;

typedef struct
{
  const uint16_t   (*energyPtrExtMem)[];
  const uint16_t   (*rangeDopplerCoordinateBuf)[];
  uint16_t   dopplerDim;
  uint16_t   numDetections;
  uint16_t   numDetectionsPerBlock;
}BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ctrlArgs;

typedef enum
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY1_PORT,
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_ENERGY2_PORT,
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_NUM_OUTPUT_BLOCKS
} eBAM_DMA_CUSTOM_CFAR_CA_DOPPLER_READ_OUTPUT_PORTS;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomCfarCaDopplerNodeReadKernelExecFunc;


typedef struct
{
  uint8_t  *ptrToRangeDopplerBuf;
  uint8_t  *ptrToEnergyBuf;
  uint8_t  *ptrToNumDetectionBuf;
}BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ctrlArgs;

typedef enum
{
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_RANGE_DOPPLER_PORT,
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_ENERGY_PORT,
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_NUM_DETECTION_PORT,
  BAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_NUM_OUTPUT_BLOCKS
} eBAM_DMA_CUSTOM_CFAR_CA_DOPPLER_WRITE_INPUT_PORTS;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomCfarCaDopplerNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_CFAR_DOPPLER_CA_NODE_H_ */

