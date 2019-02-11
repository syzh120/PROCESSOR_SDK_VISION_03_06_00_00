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
*  @file       eve_edma_bam_interface.h
*
*  @brief      This header defines all constants and functions
*              shared by implementations of the EDMA BAM interface.
*/

#ifndef EDMA_BAM_INTERFACE_H
#define EDMA_BAM_INTERFACE_H

#include "bam_kernel_interface.h"
#include "edma_user_interface.h"

/**
*  @brief      Error codes returned by various BAM EDMA APIs.
*
*  @remarks
*/
typedef enum edma_err
{
    DMANODE_EDMA_ERR_SUCCESS,               /**< Error code showing Success */
    DMANODE_EDMA_ERR_FAILED,                /**< Error code returned for Failiures due to unknown reason */
    DMANODE_EDMA_ERR_NULL_CONTEXT,          /**< Error code returned if a NULL context structure pointer is found*/
    DMANODE_EDMA_ERR_NULL_ARGS,             /**< Error code returned if a NULL ARGS structure pointer is found*/
    DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS,/**< Error code returned if ARGS structure contains more than allowed number of channels */
    DMANODE_EDMA_ERR_CROSSED_MAX_CHANNELS,  /**< Error code returned if all avialable EDMA channels are occupied */
    DMANODE_EDMA_ERR_NULL_DDR_PTR,          /**< Error code returned if a NULL DDR buffer pointer is found */
    DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR,   /**< Error code returned if a NULL internal buffer pointer is found */
    DMANODE_EDMA_ERR_NULL_STRIDE,           /**< Error code returned if a NULL DDR stride is found */
    DMANODE_EDMA_ERR_INVALID_IMAGE_DIM,     /**< Error code returned if wrong image dimensions are found */
    DMANODE_EDMA_ERR_INVALID_BLOCK_DIM,     /**< Error code returned if wrong block dimensions are found */
    DMANODE_EDMA_ERR_UNKNOWN_TRANSFER_TYPE, /**< Error code returned if nature of transfer (1D_1D, 1D_2D, etc) could not be resolved */
    DMANODE_EDMA_ERR_LAST_BLOCK             /**< Error code returned if last output block is encountered */
} DMANODE_EdmaErr;

/**
*  @brief      DMA Read kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaAutoIncrementReadKernel;

/**
*  @brief      DMA Read kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaReadAutoIncrementKernelHelperFunc;

/**
*  @brief      DMA Read kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaReadAutoIncrementKernelExecFunc;

/**
*  @brief      DMA Write kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaAutoIncrementWriteKernel;

/**
*  @brief      DMA Write kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc;

/**
*  @brief      DMA Write kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaWriteAutoIncrementKernelExecFunc;


#endif

