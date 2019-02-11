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
 *  @file       bam_vcop_clahe_process_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating clahe interpolate
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_vcop_clahe_process_int.h"
#include "vcop_clahe_process_kernel.h"

static BAM_Status BAM_claheInterpolate_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks);


static BAM_Status BAM_claheInterpolate_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks)
{

#if (!VCOP_HOST_EMULATION)
  const BAM_clahe_interpolate_Args * args = kernelArgs;
  internalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_0].size = 2U *
                               clahe_make_8way_look_up_kernel_param_count();
  internalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1].size = 2U * 4U *
                               clahe_look_up_and_interpolate_kernel_param_count();
#else
  const BAM_clahe_interpolate_Args * args = (const BAM_clahe_interpolate_Args *)kernelArgs;
  /* This field could be any non-zero number for host emulation */
  internalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_0].size = 4;
  internalBlock[CLAHE_INTERP_INTERNAL_PARAMS_IDX_1].size = 4;
#endif

  internalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX].size                    = 4*8*256*sizeof(uint8_t);
  internalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX].attrs.memAttrs          = BAM_MEMATTRS_SCRATCH;
  internalBlock[CLAHE_INTERP_INTERNAL_8_WAY_LUT_IDX].space                   = BAM_MEMSPACE_WBUF;

  internalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES].size                   = 4*args->outBlockPitch*args->blockHeight*sizeof(uint8_t);
  internalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES].attrs.memAttrs         = BAM_MEMATTRS_SCRATCH;
  internalBlock[CLAHE_INTERP_INTERNAL_TEMP_LU_VALUES].space                  = BAM_MEMSPACE_IBUFHA;

  internalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0].size                    = args->blockWidth*sizeof(uint16_t)*2;
  internalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0].attrs.memAttrs          = BAM_MEMATTRS_PERSIST;
  internalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_0].space                   = BAM_MEMSPACE_WBUF;
                                                                             
  internalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1].size                    = args->blockWidth*sizeof(uint16_t)*2;
  internalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1].attrs.memAttrs          = BAM_MEMATTRS_PERSIST;
  internalBlock[CLAHE_INTERP_INTERNAL_HOR_WGT_TAB_1].space                   = BAM_MEMSPACE_WBUF;
                                                                             
  internalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0].size                    = args->blockHeight*sizeof(uint16_t)*2;
  internalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0].attrs.memAttrs          = BAM_MEMATTRS_PERSIST;
  internalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_0].space                   = BAM_MEMSPACE_WBUF;
                                                                             
  internalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1].size                    = args->blockHeight*sizeof(uint16_t)*2;
  internalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1].attrs.memAttrs          = BAM_MEMATTRS_PERSIST;
  internalBlock[CLAHE_INTERP_INTERNAL_VER_WGT_TAB_1].space                   = BAM_MEMSPACE_WBUF;

  outBlock[CLAHE_INTERP_OUT_IDX].size                                        = args->outBlockPitch*args->blockHeight*sizeof(uint8_t);
  outBlock[CLAHE_INTERP_OUT_IDX].attrs.memAttrs                              = BAM_MEMATTRS_SCRATCH;
  outBlock[CLAHE_INTERP_OUT_IDX].space                                       = BAM_MEMSPACE_IBUFLA;


  return BAM_S_SUCCESS;
}




BAM_KernelInfo gBAM_TI_claheInterpolateKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_claheInterpolate_Context),
    sizeof(BAM_clahe_interpolate_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_claheInterpolateHelperFunc =
{ &BAM_claheInterpolate_getMemRecFunc, NULL};




