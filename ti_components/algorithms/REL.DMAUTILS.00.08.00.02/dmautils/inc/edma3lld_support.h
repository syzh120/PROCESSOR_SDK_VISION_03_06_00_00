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

/** ===========================================================================
* @file   edma3lld_support.h
*
* @path   $(STARTERWAREPATH)/inc
*
* @desc   This header defines functions to integrate EDMA3LLD with Starterware
*
* =====================================================================
*
* Use of this software is controlled by the terms and conditions found
* ===========================================================================*/

#ifndef EDMA3LLD_SUPPORT_H_
#define EDMA3LLD_SUPPORT_H_

#include "stdint.h"
#include "edma_baseaddr.h"
#include "dma_resource.h"

#ifdef USE_EDMA3LLD
#include "edma3_rm.h"
#else
typedef void *EDMA3_RM_Handle;
#endif


/* ==================================================
 *  @func   EDMA3LLD_SUPPORT_requestResources
 *
 *  @desc   This functions useses EDMA3 LLD library for requesting EDMA resources.
 *
 *  @modif    This function modifies edmaResources structure
 *
 *  @inputs   This function takes following Inputs
 *              edma3RmHandle:
 *                  Handle to EDMA3LLD resource manager
 *              edmaCc :
 *                  Pointer to the address space of EDMA module.
 *
 *              edmaResources :
 *                  Pointer to the resource structure defined in dma_resource.h.
 *                  User is expected to populate following fields of this
 *                  structure as an input and resourceAllocator will  populate
 *                  the remaining fields.
 *                      Input :
 *                          numChannels,
 *
 *                          dmaAttr[for Each channel requested],
 *
 *                          numParam[for Each channel requested], a value of
 *                          -1 means use default value which is 1
 *
 *                          queNo[for Each channel requested], - a value of
 *                          -1 means use default value.
 *
 *                      Output :
 *                          logicalChannelNo[for Each channel requested],
 *
 *                          tccVal[for Each channel requested],
 *
 *                          baseParam[for Each channel requested]
 *
 *  @outputs  edmaResources:
 *                      Contains the resources allocated for all the channels
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA3LLD_SUPPORT_requestResources(
                              EDMA3_RM_Handle    edma3RmHandle,
                              CSL_EdmaccRegsOvly edmaCc,
                              DMA_resourceStruct * edmaResources);


/* ==================================================
 *  @func   EDMA3LLD_SUPPORT_releaseResources
 *
 *  @desc   This functions useses EDMA3 LLD library for releasing requested EDMA resources.
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   This function takes following Inputs
 *              edma3RmHandle:
 *                  Handle to EDMA3LLD resource manager
 *              edmaCc :
 *                  Pointer to the address space of EDMA module.
 *
 *              edmaResources :
 *                  Pointer to the resource structure allocated using
 *                  DMA_resourceAllocator_allocateResources API
 *                          baseParam[for Each channel requested]
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA3LLD_SUPPORT_releaseResources(
                              EDMA3_RM_Handle    edma3RmHandle,
                              CSL_EdmaccRegsOvly edmaCc,
                              DMA_resourceStruct * edmaResources);

#endif /* EDMA3LLD_SUPPORT_H_ */