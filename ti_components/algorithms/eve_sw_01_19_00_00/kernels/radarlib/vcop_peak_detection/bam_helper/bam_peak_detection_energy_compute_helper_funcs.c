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
 *  @file       bam_beam_forming_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Beam Forming kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_peak_detection_energy_compute_int.h"
#include "vcop_peak_detection_kernel.h" /* compiler should take care of include path */



static BAM_Status BAM_PeakDetectionEnergyCompute_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_PeakDetectionEnergyCompute_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_PeakDetectionEnergyCompute_Args *args = (const BAM_PeakDetectionEnergyCompute_Args *) kernelArgs;
    uint32_t pBlockSize = 4U;/* Initialize to some non-zero value so that host emulation doesnt fail */
    uint32_t numLUTPoints;
    uint32_t numWordsRequired;
    uint16_t outputPitch;

    numWordsRequired = args->maxNumRows/2U;
    if ( numWordsRequired < 9U )
    {
      numWordsRequired = 9U;
    }

    outputPitch  = ( ((numWordsRequired % 2U) == 0 ) ? (numWordsRequired + 1U) : numWordsRequired);

    outputPitch  = outputPitch   * sizeof(uint32_t);

#if !VCOP_HOST_EMULATION
    pBlockSize = vcop_tx_decoding_kernel_param_count();
    pBlockSize += vcop_peak_detection_energy_across_antenna_param_count();
    pBlockSize += vcop_peak_detection_binlog_energy_scaling_param_count();
#endif
    numLUTPoints = ((uint32_t)1U<<(uint32_t)(args->alphaQFormat));

    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * pBlockSize;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_TX_DECODING_COEFF_IDX].size = args->maxNumTx * args->maxNumTx * sizeof(int16_t);
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_TX_DECODING_COEFF_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_TX_DECODING_COEFF_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PSCATTER_IDX].size = VCOP_SIMD_WIDTH * sizeof(uint16_t);
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PSCATTER_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PSCATTER_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX].size = 2U *  BAM_PEAK_DETECTION_ENERGY_COMPUTE_NUM_TABLES *
                                                                            (numLUTPoints /2U)* sizeof(uint32_t);
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LMBD_IDX].size = args->maxNumHorzPtPerAntenna * args->maxNumRows* sizeof(uint8_t);
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LMBD_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LMBD_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_ENERGY32_IDX].size = args->maxNumHorzPtPerAntenna * args->maxNumRows* sizeof(uint32_t);
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_ENERGY32_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_ENERGY32_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;


    /* This buffer is also used to store Index for LUT in  bin log scaling kernel */
    outBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT].size = outputPitch *  args->maxNumHorzPtPerAntenna;
    outBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT].space = VCOP_IBUFHA;
    outBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    return BAM_S_SUCCESS;
}

/* For Compute Hough Space index BAM node */
BAM_KernelInfo gBAM_TI_peakDetectionEnergyComputeKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_PeakDetectionEnergyCompute_Context),
    sizeof(BAM_PeakDetectionEnergyCompute_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_PEAK_DETECTION_ENERGY_COMPUTE_NUM_INPUT_BLOCKS,
    BAM_PEAK_DETECTION_ENERGY_COMPUTE_NUM_OUTPUT_BLOCKS,
    PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_NUM_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_peakDetectionEnergyComputeHelperFunc =
{ &BAM_PeakDetectionEnergyCompute_getMemRecFunc,
  NULL};

