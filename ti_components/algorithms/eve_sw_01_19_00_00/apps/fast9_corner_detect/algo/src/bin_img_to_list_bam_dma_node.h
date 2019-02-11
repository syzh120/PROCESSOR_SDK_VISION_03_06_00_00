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
 *  bin_img_to_list_bam_dma_node.h
 *
 * @brief
 *
 * @author: Anoop K P (a-kp@ti.com)
 * @version 0.1 (Dec 2013) : First version of eve edma utils function
 *
 *****************************************************************************
*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BIN_IMG_TO_LIST_BAM_DMA_NODE_H_
#define BIN_IMG_TO_LIST_BAM_DMA_NODE_H_

#include "bam_types.h"
#include "edma_bam_interface.h"

typedef struct
{
  uint8_t * dstPtr;
  uint32_t * pListSize;
} BAM_DMA_CUSTOM_BINIMG2LIST_WRITENODE_ctrlArgs;

/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_binImg2ListReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaReadBinImg2ListHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaReadBinImg2ListExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_binImg2ListWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaWriteBinImg2ListHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaWriteBinImg2ListExecFunc;


#endif /* _BIN_IMG_TO_LIST_BAM_DMA_NODE_H_ */

