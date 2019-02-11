/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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
 *  @file       bam_select_list_elements_int.h
 *
 *  @brief      This header defines internal structures for integrating select list elements
 *              kernel into BAM.
 */
#ifndef BAM_SELECT_LIST_ELEMENTS_INT_H_
#define BAM_SELECT_LIST_ELEMENTS_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_select_list_elements.h"

typedef enum
{
  SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX = 0,
  SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX,
  SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX,
  SELECT_LIST_ELEMENTS_INTERNAL_NUM_BLOCK
} eBAM_SELECT_LIST_ELEMENTS_INTERNAL_BLOCKS;


typedef struct bam_select_list_elements_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_SELECT_LIST_ELEMENTS_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_SELECT_LIST_ELEMENTS_NUM_OUTPUT_BLOCKS];
    BAM_Select_list_elements_Args     kernelArgs;
    BAM_Select_list_elements_ctrlArgs ctrlArgs;
    uint16_t                          blkIdx;
    uint16_t                          numBlks;
    uint16_t                          numElemsInLaskBlk;
} BAM_Select_list_elements_Context;

#endif /* BAM_SELECT_LIST_ELEMENTS_INT_H_ */

