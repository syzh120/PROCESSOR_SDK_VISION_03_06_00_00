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
 *  @file       bam_peak_detection_cfar_ca_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating CFAR CA kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_peak_detection_cfar_ca_int.h"
#include "vcop_peak_detection_kernel.h" /* compiler should take care of include path */

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

static BAM_Status BAM_PeakDetectionCfarCa_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_PeakDetectionCfarCa_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_PeakDetectionCfarCa_Args *args = (const BAM_PeakDetectionCfarCa_Args *) kernelArgs;
    uint32_t pBlockSize = 4U;/* Initialize to some non-zero value so that host emulation doesnt fail */
    uint32_t transposeBufSize;
    uint32_t cellSumBufSize;
#if !VCOP_HOST_EMULATION
    pBlockSize = vcop_peak_detection_cell_sum_param_count();
    pBlockSize += vcop_peak_detection_CFARCA_thresholding_param_count();
    if (args->rangeDopplerOrder == 0 )
    {
      pBlockSize += vcop_peak_detection_transpose_param_count();
    }
#endif
    if (args->rangeDopplerOrder == 0 )
    {
      transposeBufSize = ((args->maxNumHorzPoint/ 2U) + 1U) * args->maxNumVertPoint * sizeof(uint32_t);
    }
    else
    {
      transposeBufSize = 0;
    }

    cellSumBufSize = args->maxNumHorzPoint *
                      sizeof(uint16_t) *
                      (args->maxNumVertPoint +
                       (2U * (args->maxNoiseLen +
                       args->maxGaurdLen)));


    internalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * pBlockSize;
    internalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX].size = MAX(cellSumBufSize, transposeBufSize);
    internalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_ONE_LINE_IDX].size = args->maxNumHorzPoint *
                                                                       sizeof(uint32_t) * 2U;
    internalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_ONE_LINE_IDX].space = VCOP_IBUFLA;
    internalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_ONE_LINE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[PEAK_DETECTION_CFAR_CA_BINARY_MASK_IDX].size = args->maxNumHorzPoint*
                                                                 args->maxNumVertPoint *
                                                                 sizeof(uint8_t);
    internalBlock[PEAK_DETECTION_CFAR_CA_BINARY_MASK_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_CFAR_CA_BINARY_MASK_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /* Multiplication by 2 to handle splitting of input buffer in 2 different buffers */
    internalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_DOPPLER_INDEX_IDX].size = 128U * 2U * sizeof(uint32_t);
    internalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_DOPPLER_INDEX_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_DOPPLER_INDEX_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX].size = sizeof(uint32_t);
    internalBlock[PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX].size = sizeof(uint16_t)* VCOP_SIMD_WIDTH;
    internalBlock[PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    /* Assuming max 25 % of points gets detected. Subtraction by 32 to take care of BAM not being able to allocate */
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_RANGE_DOPPLER_PORT].size = ((args->maxNumHorzPoint *
                                                                          args->maxNumVertPoint
                                                                          * sizeof(uint16_t) * 2U)/4U)-32U;
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_RANGE_DOPPLER_PORT].space = VCOP_IBUFHA;
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_RANGE_DOPPLER_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    /* Assuming max 25 % of points gets detected */
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_ENERGY_PORT].size = ((args->maxNumHorzPoint *
                                                                    args->maxNumVertPoint *
                                                                    sizeof(uint16_t)) / 4U);
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_ENERGY_PORT].space = VCOP_IBUFLA;
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_ENERGY_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    outBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_DETECTIONS_PORT].size = VCOP_SIMD_WIDTH * sizeof(uint16_t) * 2U;
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_DETECTIONS_PORT].space = VCOP_IBUFLA;
    outBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_DETECTIONS_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_peakDetectionCfarCaKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_PeakDetectionCfarCa_Context),
    sizeof(BAM_PeakDetectionCfarCa_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_PEAK_DETECTION_CFAR_CA_NUM_INPUT_BLOCKS,
    BAM_PEAK_DETECTION_CFAR_CA_NUM_OUTPUT_BLOCKS,
    PEAK_DETECTION_CFAR_CA_INTERNAL_NUM_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_peakDetectionCfarCaHelperFunc =
{
  &BAM_PeakDetectionCfarCa_getMemRecFunc,
  NULL
};

