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
 *  @file       bam_bin_image_to_list_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating binary image to
 *              (X, Y) co-ordinate list creation into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_bin_image_to_list_int.h"
#include "vcop_bin_image_to_list_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Bin_image_to_list_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Bin_image_to_list_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2U * vcop_bin_image_to_list_param_count();
#else
    internalBlock[PARAMS_IDX].size = 16U;
#endif
    internalBlock[STARTXY_IDX].size = 4U;
    internalBlock[STARTXY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[STARTXY_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[XSEQ_IDX].size = 4U * 8U *((BIN_IMAGE_TO_LIST_MAX_BLK_WIDTH+7U)/8U);
    internalBlock[XSEQ_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[XSEQ_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_XY_IDX].size = 4U * BIN_IMAGE_TO_LIST_MAX_PIXELS;
    outBlock[OUT_XY_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_SIZE_IDX].size = 4U * 8U;
    outBlock[OUT_SIZE_IDX].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_binImageToListKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Bin_image_to_list_Context),
    sizeof(BAM_Bin_image_to_list_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_BIN_IMAGE_TO_LIST_NUM_IN_BLOCKS,                          /* 1 */
    BAM_BIN_IMAGE_TO_LIST_NUM_OUT_BLOCKS,                         /* 2 */
    BAM_BIN_IMAGE_TO_LIST_NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_binImageToListHelperFunc =
{ &BAM_Bin_image_to_list_getMemRecFunc, NULL};
