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
 *  @file       bam_fft_npt_16ix32o_int.h
 *
 *  @brief      This header defines internal structures for FFT kernels.
 */

#ifndef BAM_FFT_INT_H_
#define BAM_FFT_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_fft_npt_16ix32o.h"
#include "vcop_fft_npt_16ix32o_wrapper.h" /* compiler should take care of include path */
#include "vcop_fft_doppler_correction_32ix32o_kernel.h" /* compiler should take care of include path */
#include "vcop_fft_utils.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define BAM_FFT_NPT_16I_32O_MAX(A, B) (((A) > (B)) ? (A) : (B))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

typedef enum
{
  FFT_NPT_16IX32O_INTERNAL_PARAMS_IDX = 0,
  FFT_NPT_16IX32O_INTERNAL_PSCATTER_IDX,
  FFT_NPT_16IX32O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX,
  FFT_NPT_16IX32O_INTERNAL_IBUFL_SCRATCH_BUF_IDX,
  FFT_NPT_16IX32O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX,
  FFT_NPT_16IX32O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX,
  FFT_NPT_16IX32O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX,
  FFT_NPT_16IX32O_INTERNAL_NUM_BLOCKS
} eBAM_FFT_NPT_16IX32O_INTERNAL_BLOCKS;

typedef void (*BAM_Fftnpt16ix32o_KernelFuncType)(uint16_t pblock[]);
typedef uint16_t *BAM_Fftnpt16ix32o_KernelContextType;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[FFT_NPT_16IX32O_INTERNAL_NUM_BLOCKS];
    void *pInBlock[BAM_FFT_NPT_16IX32O_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_FFT_NPT_16IX32O_NUM_OUTPUT_BLOCKS];
    BAM_Fftnpt16ix32o_Args     kernelInitArgs;
    BAM_Fftnpt16ix32o_InCtrlArgs kernelCtrlArgs;
    uint8_t                        numKernels;
    uint16_t                            dopplerCorrectionPitch;
    BAM_Fftnpt16ix32o_KernelFuncType    execFunc[BAM_FFT_NPT_16IX32O_MAX_NUM_STAGES+1u];
    BAM_Fftnpt16ix32o_KernelContextType kernelContext[BAM_FFT_NPT_16IX32O_MAX_NUM_STAGES+1u];
    sVCOP_FFT_1024_pBlock_t             pBlock1024;
    sVCOP_FFT_512_pBlock_t              pBlock512;
    sVCOP_FFT_256_pBlock_t              pBlock256;
    sVCOP_FFT_128_pBlock_t              pBlock128;
    sVCOP_FFT_64_pBlock_t               pBlock64;
    uint16_t                           *pBlockCopy;
    uint16_t                           *pBlockDopplerCorrection;
    uint16_t                           *pBlockDopplerPitchRemoval;
    uint16_t                           *pBlockZeroPadding;
    uint16_t                            blockCount;
    uint16_t                            antennaCount;
    uint16_t                            scaleFactorsIn[BAM_FFT_NPT_16IX32O_MAX_NUM_STAGES];
    uint32_t                            overFlowMask;
} BAM_Fftnpt16ix32o_Context;

#endif /* BAM_FFT_INT_H_*/

