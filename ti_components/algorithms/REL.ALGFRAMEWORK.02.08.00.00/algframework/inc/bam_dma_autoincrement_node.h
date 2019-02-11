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





#ifndef _BAM_DMA_AUTOINCREMENT_NODE_H_
#define _BAM_DMA_AUTOINCREMENT_NODE_H_

#include "bam_types.h"
#include "edma_bam_interface.h"

/**
 *  @brief   Helper function that BAM will call at graph creation to query about the DMA node's memory requirements
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_getMemRecFunc(const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

/**
 *  @brief   Helper function that BAM will call at graph creation to set the DMA node's memory requirements
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

/**
 *  @brief   Initialization function that BAM will call at execution time at the beginning of each frame
 *  for input channel.
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_frameInitInChannel(void * edmaContext);

/**
 *  @brief   Initialization function that BAM will call at execution time at the beginning of each frame
 *  for output channels
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_frameInitOutChannel(void * edmaContext);

/**
 *  @brief   Input channel initialization function that BAM will call at execution time, the very first time the DMA node is used.
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_updateDDRptrInChannel(void * edmaContext,
          void *params);

/**
 *  @brief   Output channel initialization function that BAM will call at execution time, the very first time the DMA node is used.
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_updateDDRptrOutChannel(void * edmaContext,
          void *params);



#endif /* _BAM_DMA_AUTOINCREMENT_NODE_H_ */

