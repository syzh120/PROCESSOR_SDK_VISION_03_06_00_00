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
 *  @file       bam_remap_int.h
 *
 *  @brief      This header defines internal structures for remap kernel
 *              into BAM.
 */
#ifndef BAM_REMAP_INT_H_
#define BAM_REMAP_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_remap.h"

#define REMAP_NUM_IN_BLOCKS       (2U)
#define REMAP_NUM_OUT_BLOCKS      (1U)
#define REMAP_NUM_INTERNAL_BLOCKS (REMAP_DEINTERLEAVED_CHROMA_U_V_PTR_IDX + 1U)                   /* 6 */

/* Input Blocks Pointer Indexes */
#define REMAP_INPUT_IMAGE_BLOCK_PTR_IDX     (0U)
#define REMAP_LUT_PTR_IDX                   (1U)


/* Output Blocks Pointer Indexes */
#define REMAP_OUT_LUMA_IDX                  (0U)


/* Internal Blocks Pointer Indexes */
#define REMAP_INTERPOLATION_BUF0_PTR_IDX    (0U)                                                  /* 0 */
#define REMAP_INTERPOLATION_BUF1_PTR_IDX    (REMAP_INTERPOLATION_BUF0_PTR_IDX + 1U)               /* 1 */
#define REMAP_MAX_INTERPOLATION_BUF_PTR_IDX (REMAP_INTERPOLATION_BUF1_PTR_IDX)                   /* 1 */

#define REMAP_PBLOCK_PTR_IDX                (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 1U)            /* 2 */
#define REMAP_CHROMA_TLU_INDEX_PTR_IDX      (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 2U)            /* 3 */

/* For YUV 420 SP and YUV 422 ILE and IBE */
#define REMAP_SCATTERED_DEST_OFFSET_VALUES_PTR_IDX (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 3U)     /* 4 */

/* For YUV 422 ILE and IBE */
#define REMAP_DEINTERLEAVED_CHROMA_U_V_PTR_IDX     (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 4U)     /* 5 */


typedef VcopRemapContext VCOP_Remap_Context;

typedef struct bam_remap_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[REMAP_NUM_INTERNAL_BLOCKS];
    void *pInBlock[REMAP_NUM_IN_BLOCKS];
    void *pOutBlock[REMAP_NUM_OUT_BLOCKS];
    BAM_Remap_Args kernelArgs;
    VCOP_Remap_Context vcopContext;
    int32_t (*vloopFunc)(VCOP_Remap_Context *vcopContext);
} BAM_Remap_Context;

#endif /* BAM_REMAP_INT_H_*/
