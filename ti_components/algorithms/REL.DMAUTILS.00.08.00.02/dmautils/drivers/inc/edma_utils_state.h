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
* @file   dma_utils_state.h
*
* @path   $(STARTERWAREPATH)/drivers/inc
*
* @desc   This header is an internal header and is used to store the state
*         of edmaResources of all the EDMA usecases.
*
* =====================================================================
*
* Use of this software is controlled by the terms and conditions found
* ===========================================================================*/

#ifndef DMA_UTILS_STATE_H
#define DMA_UTILS_STATE_H

/*#pragma CHECK_MISRA ("none")*/
#include "stdint.h"
/*#pragma RESET_MISRA ("required")*/

#include "edmacc_config.h"
#include "dma_resource.h"

/** ========================================================
 *  @name   DMA_utilsStateStruct
 *
 *  @desc   This structure maintains the state of dma resources allocated for
 *          EDMA utility usecases
 *
 *  @field logicalChanNo[]
 *              This stores the event corresponding to a given channel number for
 *              all channels
 *
 *  @field tccVal[]
 *              This stores the transfer completion code corresponding to a given
 *              channel number for all channels
 *
 *  @field baseParam
 *              This stores the base parameter(end of linked parameter)
 *              corresponding to a given channel number for all channels
 *
 *  ===============================================================
 */

typedef struct dma_utilsStateStruct
{
    int8_t              logicalChanNo[NUM_MAX_CHANNELS];
    int8_t              tccVal[NUM_MAX_CHANNELS];
    volatile uint32_t     *baseParam[NUM_MAX_CHANNELS];
} DMA_utilsStateStruct;

/* ==================================================
 *  @func   DMA_utils_resetStateStruct
 *
 *  @desc   This function reset the state structure for all the
 *          EDMA utility usecases
 *
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_utils_resetStateStruct(void);


/* ==================================================
 *  @func   DMA_utils_updateStateStruct
 *
 *  @desc   This functions updates the state structure for Utilities
 *          based on the resources allocated by using resource Allocator
  *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaResources :
 *                  Pointer to the resource structure defined in dma_resource.h.
 *                  User is expected to populate following fields of this
 *                  structure as an input and resourceAllocator will  populate
 *                  the remaining fields.
 *  @outputs
 *              startIndex :
 *                  The index at which edmaResources are stored in utilsStateStruct
 *                  Usecase should be using this index to fetch the data
 *                  corresponding to it.
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_utils_updateStateStruct(const DMA_resourceStruct * edmaResources , uint8_t * startIndex);

/* ==================================================
 *  @func   DMA_utils_freeStateStruct
 *
 *  @desc   This functions frees the state structure for Utilities
 *          based on the startIndex and numEnteries
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   This function takes following Inputs
 *              startIndex :
 *                  The index at which edmaResources are stored in utilsStateStruct
 *
 *              numEnteries :
 *                  Number of enteries that needs to be freed from utilsStateStruct
 *                  starting from startIndex
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void DMA_utils_freeStateStruct(uint8_t startIndex , uint8_t numEnteries);


#endif /*DMA_UTILS_STATE_H*/
/*!
*! Revision History
*! ================
*! 16-Oct-2013   Anshu: Initial Draft
*/
