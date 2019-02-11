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
 *  @file       bam_dcoffset_windowing_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating DC offset, windowing kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_dcoffset_windowing_int.h"
#include "vcop_dcoffset_windowing_kernel.h" /* compiler should take care of include path */

static BAM_Status BAM_DcoffsetWindowing_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_DcoffsetWindowing_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_DcoffsetWindowing_Args *args = (const BAM_DcoffsetWindowing_Args *) kernelArgs;
    uint32_t pBlockSize = 4U;/* Initialize to some non-zero value so that host emulation doesnt fail */
    uint16_t interimTransposeStride;


#if !VCOP_HOST_EMULATION
    pBlockSize = vcop_interference_zero_out_kernel_param_count();

    pBlockSize += vcop_dcoffset_kernel_param_count();

    pBlockSize += vcop_sign_extension_kernel_param_count();

    if ( args->enableTranspose)
    {
      pBlockSize += vcop_windowing_with_transpose_kernel_param_count();
    }
    else
    {
      pBlockSize += vcop_windowing_kernel_param_count();
    }
#endif
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * pBlockSize;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;

    /* Choose strides such that with this as a pitch each memory location falls into different memory bank */
    /* For this we can choose any odd number greater than 9 words */
    interimTransposeStride = ((BAM_DCOFFSET_WINDOWING_MAX_NUM_LINES * 2U) + 1U) *   sizeof(uint32_t);


    internalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX].size  = BAM_DCOFFSET_WINDOWING_MAX_NUM_POINTS * sizeof(int16_t);
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX].space          = BAM_MEMSPACE_WBUF;

    internalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX].size  = BAM_DCOFFSET_WINDOWING_MAX_NUM_LINES * sizeof(int16_t) * 2U;/* Multiple by 2 for real and imaginary part */
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX].space          = BAM_MEMSPACE_WBUF;

    internalBlock[DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX].size  = VCOP_SIMD_WIDTH * sizeof(uint16_t);/* Multiple by 2 for real and imaginary part */
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX].space          = BAM_MEMSPACE_WBUF;

    internalBlock[DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX].size  = VCOP_SIMD_WIDTH * sizeof(uint16_t);/* Multiple by 2 for real and imaginary part */
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX].space          = BAM_MEMSPACE_WBUF;

    internalBlock[DCOFFSET_WINDOWING_INTERNAL_SCRATCH_IDX].size  = ( VCOP_SIMD_WIDTH * interimTransposeStride);
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_SCRATCH_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_SCRATCH_IDX].space          = BAM_MEMSPACE_WBUF;

    /* Allocate maximum HA buffer as output to interference zero out can at max be same as IBUFLA size which is 16K */
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX].size  = 16384U;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX].space          = BAM_MEMSPACE_IBUFHA;

    /* Allocate maximum possible block size for output so as to take care of all FFT dimension. This will occur when we are doing transpose for
    512 point FFT, as transpose of 512x8 block will need memory of (512/8)*9*4*8 so allocate this memory to handle worst case allocation*/
    outBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT].size =   512 * 9 * 4;
    outBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT].space = BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}

/* For Compute Hough Space index BAM node */
BAM_KernelInfo gBAM_TI_dcoffsetWindowingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_DcoffsetWindowing_Context),
    sizeof(BAM_DcoffsetWindowing_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_DCOFFSET_WINDOWING_NUM_INPUT_BLOCKS,
    BAM_DCOFFSET_WINDOWING_NUM_OUTPUT_BLOCKS,
    DCOFFSET_WINDOWING_INTERNAL_NUM_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_dcoffsetWindowingHelperFunc =
{ &BAM_DcoffsetWindowing_getMemRecFunc,
  NULL};

