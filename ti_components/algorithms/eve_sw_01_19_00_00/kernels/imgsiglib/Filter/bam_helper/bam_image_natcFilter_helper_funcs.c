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
 ********************************************************************************
 * @file:      bam_image_filter_helper_funcs.c
 *
 * @brief:   This file defines functions for integrating filter kernels into BAM
 *
 * @author: Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_image_filter_helper_funcs.h"
#include "bam_image_natcFilter.h" /*makerules should take care of include path*/
#include "vcop_filter_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_Image_natcFilter_getMemRecFunc
(
  const void *kernelArgs,
  BAM_MemRec *internalBlock,
  BAM_MemRec *outBlock,
  uint8_t    *numInternalBlocks,
  uint8_t    *numOutBlocks
);

/**
 *******************************************************************************
 * @fn        BAM_Image_filter_GetMemRecFunc
 * @brief     Function to allocate memory for filter .
 *
 * @inputs -  kernelArgs :
 * @inputs -  kernelContext :
 * @inputs -  internalBlock :
 * @inputs -  outBlock :
 * @inputs -  numInternalBlocks :
 * @inputs -  numOutBlocks :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_natcFilter_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t    *numInternalBlocks,
    uint8_t    *numOutBlocks
)
{
    BAM_Image_filter_Args *args = (BAM_Image_filter_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2;
    
    internalBlock[COEFFS_IDX].size = args->coeff_blk_width*args->coeff_blk_height;

    if (args->coeff_type== USHORT_TYPE || args->coeff_type== SHORT_TYPE) {
        internalBlock[COEFFS_IDX].size *= 2; 
    }
    else if (args->coeff_type== INT_TYPE) {
        internalBlock[COEFFS_IDX].size *= 4; 
    }
    else {
        ;
    }

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[0].size = ((args->compute_blk_width) * (args->compute_blk_height));

    return 0;
}


BAM_KernelInfo gBAM_TI_natcFilterKernel =
{
  0, /*kernelId */
  sizeof(BAM_Image_filter_Context),/*kernelContextSize*/
  sizeof(BAM_Image_filter_Args),
  BAM_EVE_ARP32, /*coreType */
  BAM_NODE_COMPUTE, /*nodeType */
  NUM_IN_BLOCKS,      /*1*/
  NUM_OUT_BLOCKS,      /*1 */
  NUM_INTERNAL_BLOCKS       /*2 */
};

BAM_KernelHelperFuncDef gBAM_TI_natcFilterHelperFunc =
{
  &BAM_Image_natcFilter_getMemRecFunc,
  NULL,/*(BAM_KernelSetMemRecFunc)&BAM_Image_filter_setMemRecFunc*/
};

