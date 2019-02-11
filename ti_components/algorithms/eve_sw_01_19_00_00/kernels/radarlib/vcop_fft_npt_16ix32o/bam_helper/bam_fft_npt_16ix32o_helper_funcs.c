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
 *  @file       bam_fft_npt_16ix16o_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating FFT kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_fft_npt_16ix32o_int.h"
#include "vcop_fft_npt_16ix32o_wrapper.h" /* compiler should take care of include path */
#include "vcop_fft_npt_16ix16o_gen_twiddleFactor.h"

#define FFT_NPT_16IX32O_MAX_NUM_DOPPLER_POINTS (512U)

static BAM_Status BAM_Fftnpt16ix32o_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_Fftnpt16ix32o_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_Fftnpt16ix32o_Args *args = (const BAM_Fftnpt16ix32o_Args *) kernelArgs;
    uint32_t maxParamBlockSize = 4U;/* Initialize to some non-zero value so that host emulation doesnt fail */
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t maxTwiddleFactorBufSize;

#if !VCOP_HOST_EMULATION
    maxParamBlockSize = vcop_fft_512_16i_32o_param_count();
    maxParamBlockSize = BAM_FFT_NPT_16I_32O_MAX(maxParamBlockSize,
      vcop_fft_128_16i_32o_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_32O_MAX(maxParamBlockSize,
      vcop_fft_256_16i_32o_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_32O_MAX(maxParamBlockSize,
      vcop_fft_64_16i_32o_param_count());
    maxParamBlockSize += vcop_copy_fft_32ix32o_kernel_param_count();
    maxParamBlockSize += vcop_fft_doppler_correction_32ix32o_kernel_param_count();
    maxParamBlockSize += vcop_fft_doppler_pitch_removal_32ix32o_param_count();
    maxParamBlockSize += vcop_fft_zero_padding_kernel_param_count();
#endif
    maxTwiddleFactorBufSize = getSizeTwiddleFactor_512();
    maxTwiddleFactorBufSize = BAM_FFT_NPT_16I_32O_MAX(maxTwiddleFactorBufSize,getSizeTwiddleFactor_128());
    maxTwiddleFactorBufSize = BAM_FFT_NPT_16I_32O_MAX(maxTwiddleFactorBufSize,getSizeTwiddleFactor_256());
    maxTwiddleFactorBufSize = BAM_FFT_NPT_16I_32O_MAX(maxTwiddleFactorBufSize,getSizeTwiddleFactor_64());

    internalBlock[FFT_NPT_16IX32O_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * maxParamBlockSize;

    /* Allocate worst case buffer. For storing 1024 point transpose we will need 64 rows( corresponding to 16 butterflies within a group)
     in stage 3 ( all corresponding to same group ). Each row would be storing 16 groups which means 16 * 4 bytes. As we are using pScatter
     we will take next odd word which would be 68 bytes. So for a single line memory requried would be 64 * 68 bytes. For 1024 case we can process
     maximum of 4 lines hence total memory would be 64 * 68 * 4 bytes. */
     /* For 512 point transpose we need 512 * 9 * 4 bytes of memory which is greater than the above quantity and hence allocate for the
  worst case */
    internalBlock[FFT_NPT_16IX32O_INTERNAL_IBUFL_SCRATCH_BUF_IDX].size  = FFT_NPT_16IX32O_MAX_IBUF_SIZE;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_IBUFL_SCRATCH_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_IBUFL_SCRATCH_BUF_IDX].space          = BAM_MEMSPACE_IBUFLA;

    internalBlock[FFT_NPT_16IX32O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX].size  = maxTwiddleFactorBufSize;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX].space          = BAM_MEMSPACE_WBUF;

    if ( args->enableTranspose == 1 )
    {
      internalBlock[FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX].size  = (FFT_NPT_16IX32O_MAX_NUM_DOPPLER_POINTS * sizeof(int16_t) * 2U);
      internalBlock[FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
      internalBlock[FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX].space          = BAM_MEMSPACE_WBUF;
    }
    else
    {
      internalBlock[FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX].size  = 4;
      internalBlock[FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
      internalBlock[FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX].space          = BAM_MEMSPACE_WBUF;
    }

    /* Multiply by 2 as for 64 pooint FFT we need 2 sets of pScatter Index */
    internalBlock[FFT_NPT_16IX32O_INTERNAL_PSCATTER_IDX].size  = VCOP_SIMD_WIDTH * sizeof(uint16_t) * 2U;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_PSCATTER_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_PSCATTER_IDX].space          = BAM_MEMSPACE_WBUF;

    internalBlock[FFT_NPT_16IX32O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX].size  = VCOP_SIMD_WIDTH * sizeof(uint16_t);
    internalBlock[FFT_NPT_16IX32O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX].space          = BAM_MEMSPACE_WBUF;

    internalBlock[FFT_NPT_16IX32O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX].size  = VCOP_SIMD_WIDTH * 2U * sizeof(uint8_t);
    internalBlock[FFT_NPT_16IX32O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[FFT_NPT_16IX32O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX].space          = BAM_MEMSPACE_WBUF;

    outBlock[BAM_FFT_NPT_16IX32O_OUTPUT_PORT].size = FFT_NPT_16IX32O_MAX_IBUF_SIZE;
    outBlock[BAM_FFT_NPT_16IX32O_OUTPUT_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_FFT_NPT_16IX32O_OUTPUT_PORT].space = BAM_MEMSPACE_IBUFHA;

    return status;
}

/* For Compute index BAM node */
BAM_KernelInfo gBAM_TI_Fftnpt16ix32oKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Fftnpt16ix32o_Context),
    sizeof(BAM_Fftnpt16ix32o_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_FFT_NPT_16IX32O_NUM_INPUT_BLOCKS,
    BAM_FFT_NPT_16IX32O_NUM_OUTPUT_BLOCKS,
    FFT_NPT_16IX32O_INTERNAL_NUM_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_Fftnpt16ix32oHelperFunc =
{ &BAM_Fftnpt16ix32o_getMemRecFunc,
  NULL};

