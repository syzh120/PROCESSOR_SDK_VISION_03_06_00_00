/*
*
* Copyright (c) 2011-2017 Texas Instruments Incorporated
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
* @file bam_image_integraiImage_u8_helper_funcs.c
*
* @brief This file contains all kernel helper functions for Gamma Correction
*
* @author Kumar Desappan(kumar.desappan@ti.com)
*
* @version 0.0 (Jul 2013) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_image_integralimage_u8_helper_funcs.h"
#include "eve_integral_image_kernel.h"

BAM_Status BAM_Image_integralImage_u8_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);

/**
*******************************************************************************
* @fn        BAM_Image_integralImage_u8_getMemRecFunc
* @brief    Function to allocate memory for RGB to sRGB conversion .
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  memRecInternal :
* @inputs -  memRecOutputDataBlock :
* @inputs -  numRecInternal :
* @inputs -  numRecOutputDataBlock :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_Image_integralImage_u8_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{

#if (!VCOP_HOST_EMULATION)
    const BAM_Image_integralImage_u8_Args *args = kernelArgs;
    memRecInternal[PARAMS_IDX].size = 2u*eve_integral_image_u8_int_int_param_count();
    memRecInternal[PARAMS_RESET_ACCV_IDX].size = 2u*eve_integral_image_reset_accv_param_count();
#else
    const BAM_Image_integralImage_u8_Args *args = (const BAM_Image_integralImage_u8_Args *)kernelArgs;
    memRecInternal[PARAMS_IDX].size = 16;
    memRecInternal[PARAMS_RESET_ACCV_IDX].size = 16;
#endif

    memRecInternal[SCRATCH_VER_ACC_IDX].size =  sizeof(int32_t)*  args->blk_height;
    
    memRecInternal[SCRATCH_B0_IDX].size = sizeof(int32_t)*  (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_B0_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_B0_IDX].space = BAM_MEMSPACE_WBUF;
    
    memRecInternal[SCRATCH_B1_IDX].size = sizeof(int32_t)*  (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_B1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_B1_IDX].space = BAM_MEMSPACE_WBUF;
    
    memRecInternal[SCRATCH_C0_IDX].size = sizeof(int32_t)*  (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_C0_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_C0_IDX].space = BAM_MEMSPACE_ANY_VCOPBUF;
    
    memRecInternal[SCRATCH_C1_IDX].size = sizeof(int32_t)* (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_C1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_C1_IDX].space = BAM_MEMSPACE_ANY_VCOPBUF;
    
    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[OUT_INTG_IMG_IDX].size = sizeof(int32_t) * ( args->blk_width * args->blk_height );
    memRecOutputDataBlock[OUT_INTG_IMG_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[OUT_INTG_IMG_IDX].space = BAM_MEMSPACE_IBUFHA;

    memRecOutputDataBlock[OUT_HOR_ACC_IDX].size = sizeof(int32_t) * args->blk_width;
    memRecOutputDataBlock[OUT_HOR_ACC_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[OUT_HOR_ACC_IDX].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_integralImage_u8Kernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_integralImage_u8_Context),/*kernelContextSize*/
    sizeof(BAM_Image_integralImage_u8_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_integralImage_u8HelperFunc =
{
    &BAM_Image_integralImage_u8_getMemRecFunc,
    NULL
};

