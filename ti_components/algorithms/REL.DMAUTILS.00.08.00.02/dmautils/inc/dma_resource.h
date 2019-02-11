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
* @file   dma_resource.h
*
* @path   $(STARTERWAREPATH)/inc
*
* @desc   This  File contains the structure which dma_func API's expect from
*         the resource managere
*
* =====================================================================
*
* Use of this software is controlled by the terms and conditions found
* ===========================================================================*/

#ifndef DMA_RESOURCE_H
#define DMA_RESOURCE_H

#include "edmacc_config.h"

/** ====================================================
 *  @name   DMA_chanAttr
 *
 *  @desc   Describes the attribute of a DMA channel ie whether its
 *                a EDMA channel or QDMA channel
 *
 *  @field  DMA_CHAN_ATTR_EDMA
 *             EDMA channel Attribute
 *
 *  @field  DMA_CHAN_ATTR_QDMA
 *             QDMA channel Attribute
 *  ====================================================
 */
typedef enum chan_attr
{
    DMA_CHAN_ATTR_EDMA,
    DMA_CHAN_ATTR_QDMA
} DMA_chanAttr;


/** ========================================================
 *  @name   DMA_ResourceStruct
 *
 *  @desc   This structure is common between EDMA and QDMA channels and is used
 *          to hold the resources allocated by the resource manager and is
 *          expected to be used by dma_funcs API's
 *
 *  @field  numChannels
 *              Number of channels for which resources have been allocated. This
 *              is an input to the request allocator
 *
 *  @field  dmaAttr[]
 *              DMA attribute for all numChannels (whether its EDMA transfer
 *              or QDMA transfer). Refer to enum DMA_chanAttr defined in
 *              this header  for valid values. This is an input to resource
 *              allocator
 *
 *  @field  numParam[]
 *              This stores the number of param set corresponding to a given
 *              channel number for all requested numChannels channels. This is
 *              an input to resource allocator
 *
 *  @field queNo[]
 *              This stores the que number corresponding to a given channel
 *              number for requested channel. This field is used to configure
 *              DMAQNUM (for EDMA channels) or QDMAQNUM (for QDMA channels).
 *              This is an input from resource allocator. It is to be noted that
 *              only last bit of this field is considered for configuring the
 *              Que. This is because we have only two ques.
 *
 * @field trigWordIndex[]
 *              The index of the param entry writing at which will trigger
 *              QDMA channel. This field is only valid for QDMA channels
 *              and is ignored for EDMA channels. Index can take value from
 *              0-7.
 *
 *  @field  logicalChannelNo[]
 *              This is logical channel number/event number allocated for
 *              channels requested. EDMA has only two physical channels but
 *              can support total 16 logical channels. In case of QDMA channel
 *              this field tells the actual QDMA channel number. In case of
 *              EDMA this field indicates the event that needs to be set in
 *              the event enable register. This field will be used to configure
 *              DCHMAP ( for EDMA channels) or QCHMAP (for QDMA chanenls).
 *              This is an output from resource allocator.
 *
 *  @field tccVal[]
 *              This stores the transfer completion code corresponding to
 *              a given channel number for channels requested. This field is
 *              configured using OPT[12:17] field of param set. This is an
 *              output from resource allocator.
 *
 *
 *  @field baseParam[]
 *              This stores the base param set corresponding to a given
 *              channel number for requested channel. Resource allocator
 *              should make sure to leave a space on numParam parameter sets
 *              after this base address for a particular channel.This is an
 *              output from resource allocator.
 *
 *  ===============================================================
 */
typedef struct dma_resourceStruct
{
    uint8_t            numChannels;
    uint8_t            dmaAttr[NUM_MAX_CHANNELS];
    uint8_t            numParam[NUM_MAX_CHANNELS];
    uint8_t            queNo[NUM_MAX_CHANNELS];
    uint8_t            trigWordIndex[NUM_QDMA_CHANNELS];
    uint8_t            logicalChannelNo[NUM_MAX_CHANNELS];
    uint8_t            tccVal[NUM_MAX_CHANNELS];
    volatile uint32_t   *baseParam[NUM_MAX_CHANNELS];
}DMA_resourceStruct;

#endif /* DMA_RESOURCE_H */

/*!
*! Revision History
*! ================
*! 16-Oct-2013   Anshu: Initial Draft
*/

