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
 *  @file       bam_fft_npt_16ix16o_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating FFT kernels
 *                into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_fft_npt_16ix16o_int.h"
#include "bam_fft_npt_16ix16o.h"
#include "vcop_fft_npt_16ix16o_cn.h"
#include "vcop_fft_npt_16ix16o_32inter_cn.h"
#include "edma_utils_memcpy.h"
#include "vcop_fft_npt_16ix16o_gen_twiddleFactor.h"

/***********************************************************************************************/
/*                        Below are the helper  functions related to DC offset windowing and interference zero out kernels              */
/***********************************************************************************************/
static BAM_Status Bam_Fftnpt16ix16o_initFrame(void *kernelContext);
static BAM_Status Bam_Fftnpt16ix16o_computeFrame(void *kernelContext);

static BAM_Status Bam_Fftnpt16ix16o_control(void *kernelContext,
                                            void * kernelCtlArg);

static void Bam_Fftnpt16ix16o_copyDopplerCorrectionCoefficients(uint16_t *kernelContext);
static void Bam_Fftnpt16ix16o_copyDopplerCorrectionCoefficients(uint16_t *kernelContext)
{
    BAM_Fftnpt16ix16o_Context *context = (BAM_Fftnpt16ix16o_Context *)(void *) kernelContext;
    uint8_t (*dopplerCorrectionBuf)[] = (uint8_t (*)[])(void *)context->kernelCtrlArgs.dopplerCorrectionBuf;
    if ( (context->blockCount % context->kernelCtrlArgs.numBlocksPerAntenna) == 0)
    {
#if !VCOP_HOST_EMULATION
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
        /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   MEM_BUF_SWITCH is a memory mapped register*/
        volatile uint32_t * bufSwitchCtrl = (uint32_t *)(void*)(MEM_BUF_SWITCH);
        /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
#else
        uint32_t tempVar = 0;
        volatile uint32_t * bufSwitchCtrl = (uint32_t *)(void*)&tempVar;
#endif
        uint32_t origMemSwitchState;
        uint32_t modiMemSwitchState;

        origMemSwitchState = *bufSwitchCtrl;
        modiMemSwitchState = (uint32_t)((uint32_t)(origMemSwitchState & 0x0000FFFFU) | (uint32_t)((uint32_t)WBUF_SYST << 16U));
        /* Wait for previous kernel to finish */
        _vcop_vloop_done();

        /* Take the ownership of work buffer */
        *bufSwitchCtrl = modiMemSwitchState;
        /* Do memcpy of doppler correction Buf */
        EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX],
                            (*dopplerCorrectionBuf) + (context->antennaCount *
                                    context->kernelCtrlArgs.numPoints * sizeof(int16_t) * 2U),
                                    (uint16_t)context->kernelCtrlArgs.numPoints * sizeof(int16_t) * 2U,1U,0,0);

        context->antennaCount++;
        /* Swith back to the original state of buffers */
        *bufSwitchCtrl = origMemSwitchState;
    }
}


static BAM_Status Bam_Fftnpt16ix16o_initFrame(void *kernelContext)
{
    BAM_Fftnpt16ix16o_Context *context = (BAM_Fftnpt16ix16o_Context *) kernelContext;
    BAM_Status status = BAM_S_SUCCESS;
    uint8_t inPlaceFFT;
    uint32_t maxParamBlockSize;
    uint16_t (*pScatterOffset)[VCOP_SIMD_WIDTH];
    uint32_t i;
    int16_t (*dopplerCorrectionBufInt)[BAM_FFT_NPT_16IX16O_MAX_NUM_POINTS];
    uint32_t kernelIdx = 0;

    inPlaceFFT = 0U;
    context->blockCount = 0;
    context->antennaCount = 0;

    if (context->kernelCtrlArgs.enableOverflowDetection == 0 )
    {
        context->overFlowMask = 0;
        for (i =0; i < BAM_FFT_NPT_16IX16O_MAX_NUM_STAGES; i++)
        {
            context->scaleFactorsIn[i] = context->kernelCtrlArgs.scaleFactors[i];
        }
    }
    else
    {
        uint8_t (*scaleFactorOut)[BAM_FFT_NPT_16IX16O_MAX_NUM_STAGES] =  (uint8_t (*)[BAM_FFT_NPT_16IX16O_MAX_NUM_STAGES])context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX];
        context->overFlowMask = context->kernelCtrlArgs.overflowMask;

        for ( i = 0; i < BAM_FFT_NPT_16IX16O_MAX_NUM_STAGES; i++)
        {
            (*scaleFactorOut)[i] = 0;
            if ( context->overFlowMask & (uint32_t)((uint32_t)1U << i))
            {
                context->scaleFactorsIn[i] = context->kernelCtrlArgs.scaleFactors[i];
            }
            else
            {
                context->scaleFactorsIn[i] = 0;
            }
        }

    }

    if ( context->kernelInitArgs.enableTranspose == 1U )
    {
        inPlaceFFT = 1U;
        if (  context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512 )
        {
            inPlaceFFT = 0;
        }

        if ( context->kernelCtrlArgs.enableDopplerCorrection == 1U)
        {
            context->execFunc[kernelIdx] = &Bam_Fftnpt16ix16o_copyDopplerCorrectionCoefficients;
            context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)context;
            kernelIdx++;
        }
    }
    maxParamBlockSize = vcop_fft_512_16i_16o_param_count();
    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_128_16i_16o_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_256_16i_16o_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_64_16i_16o_param_count());

    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_512_16i_16o_32inter_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_128_16i_16o_32inter_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_256_16i_16o_32inter_param_count());
    maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                vcop_fft_64_16i_16o_32inter_param_count());

    if ( (context->kernelInitArgs.enableTranspose == 0) && (context->kernelCtrlArgs.enable32bitsIntermResults== 0))
    {
        maxParamBlockSize = BAM_FFT_NPT_16I_16O_MAX(maxParamBlockSize,
                                                    vcop_fft_1024_16i_16o_param_count());
    }

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
#if !VCOP_HOST_EMULATION
    context->pBlockDopplerCorrection = (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX] +
            maxParamBlockSize;
    context->pBlockDopplerPitchRemoval = (uint16_t *)context->pBlockDopplerCorrection +
            vcop_fft_doppler_correction_kernel_param_count();
    context->pBlockZeroPadding         =  (uint16_t *)context->pBlockDopplerPitchRemoval +
            vcop_fft_doppler_pitch_removal_param_count();
#endif

#if !VCOP_HOST_EMULATION
    if ( context->kernelCtrlArgs.numPointsZeroPadding != 0)
    {
        vcop_fft_zero_padding_kernel_init((uint32_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                                          context->kernelCtrlArgs.numActualPoints,
                                          context->kernelCtrlArgs.numLines,
                                          context->kernelCtrlArgs.numPointsZeroPadding,
                                          context->kernelCtrlArgs.pitch,
                                          context->pBlockZeroPadding);
        context->execFunc[kernelIdx] = &vcop_fft_zero_padding_kernel_vloops;
        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)context->pBlockZeroPadding;
        kernelIdx++;
    }
#endif
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    if ( context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_1024 )
    {
        sVCOP_FFT_1024_pBlock_t              * pBlock1024 = (sVCOP_FFT_1024_pBlock_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX];
        EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                            context->kernelCtrlArgs.twiddleFactorBuf,
                            (uint16_t)getSizeTwiddleFactor_1024(),1U,0,0);

#if (!VCOP_HOST_EMULATION)
        vcop_fft_1024_16i_16o_init(
                context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                context->kernelCtrlArgs.numValidBits,
                context->kernelCtrlArgs.pitch,
                context->scaleFactorsIn,
                context->kernelCtrlArgs.numLines,
                inPlaceFFT,
                context->overFlowMask,
                context->kernelCtrlArgs.saturationLimit,
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

        /* Copy the param block pointers for each individual kernels */
        context->pBlock1024.pblock_stage_1 = pBlock1024->pblock_stage_1;
        context->pBlock1024.pblock_stage_2 = pBlock1024->pblock_stage_2;
        context->pBlock1024.pblock_stage_3 = pBlock1024->pblock_stage_3;
        context->pBlock1024.pblock_stage_4 = pBlock1024->pblock_stage_4;
        context->pBlock1024.pblock_stage_5 = pBlock1024->pblock_stage_5;
        for ( i = 0; i < 5U; i++)
        {
            context->pBlock1024.execFunc[i] = pBlock1024->execFunc[i];
        }

        context->execFunc[kernelIdx] = &vcop_fft_1024_16i_16o_vloops;
        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)&context->pBlock1024;
#endif
    }
    else if ( context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512 )
    {
        sVCOP_FFT_512_pBlock_t              * pBlock512 = (sVCOP_FFT_512_pBlock_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX];
        EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                            context->kernelCtrlArgs.twiddleFactorBuf,
                            (uint16_t)getSizeTwiddleFactor_512(),1U,0,0);

#if (!VCOP_HOST_EMULATION)
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_512_16i_16o_32inter_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_512_16i_16o_32inter_vloops;
        }
        else {
            vcop_fft_512_16i_16o_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_512_16i_16o_vloops;
        }

        /* Copy the param block pointers for each individual kernels */
        context->pBlock512.pblock_stage_1   = pBlock512->pblock_stage_1;
        context->pBlock512.pblock_stage_2   = pBlock512->pblock_stage_2;
        context->pBlock512.pblock_stage_3   = pBlock512->pblock_stage_3;
        context->pBlock512.pblock_stage_4   = pBlock512->pblock_stage_4;
        context->pBlock512.pblock_stage_5   = pBlock512->pblock_stage_5;
        for ( i = 0; i < 5U; i++)
        {
            context->pBlock512.execFunc[i] = pBlock512->execFunc[i];
        }

        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)&context->pBlock512;
#endif
    }
    else if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_128)
    {
        sVCOP_FFT_128_pBlock_t              * pBlock128 = (sVCOP_FFT_128_pBlock_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX];
        EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                            context->kernelCtrlArgs.twiddleFactorBuf,
                            (uint16_t)getSizeTwiddleFactor_128(),1U,0,0);

#if (!VCOP_HOST_EMULATION)
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_128_16i_16o_32inter_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_128_16i_16o_32inter_vloops;
        }
        else {
            vcop_fft_128_16i_16o_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_128_16i_16o_vloops;
        }

        /* Copy the param block pointers for each individual kernels */
        context->pBlock128.pblock_stage_1 = pBlock128->pblock_stage_1;
        context->pBlock128.pblock_stage_2 = pBlock128->pblock_stage_2;
        context->pBlock128.pblock_stage_3 = pBlock128->pblock_stage_3;
        context->pBlock128.pblock_stage_4 = pBlock128->pblock_stage_4;
        for ( i = 0; i < 4U; i++)
        {
            context->pBlock128.execFunc[i] = pBlock128->execFunc[i];
        }

        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)&context->pBlock128;

#endif
    }
    else if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_256)
    {
        sVCOP_FFT_256_pBlock_t              * pBlock256 = (sVCOP_FFT_256_pBlock_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX];
        EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                            context->kernelCtrlArgs.twiddleFactorBuf,
                            (uint16_t)getSizeTwiddleFactor_256(),1U,0,0);

#if (!VCOP_HOST_EMULATION)
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_256_16i_16o_32inter_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_256_16i_16o_32inter_vloops;
        }
        else {
            vcop_fft_256_16i_16o_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_256_16i_16o_vloops;
        }

        /* Copy the param block pointers for each individual kernels */
        context->pBlock256.pblock_stage_1 = pBlock256->pblock_stage_1;
        context->pBlock256.pblock_stage_2 = pBlock256->pblock_stage_2;
        context->pBlock256.pblock_stage_3 = pBlock256->pblock_stage_3;
        context->pBlock256.pblock_stage_4 = pBlock256->pblock_stage_4;
        for ( i = 0; i < 4U; i++)
        {
            context->pBlock256.execFunc[i] = pBlock256->execFunc[i];
        }

        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)&context->pBlock256;

#endif
    }
    else if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_64)
    {
        sVCOP_FFT_64_pBlock_t              * pBlock64 = (sVCOP_FFT_64_pBlock_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX];
        EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                            context->kernelCtrlArgs.twiddleFactorBuf,
                            (uint16_t)getSizeTwiddleFactor_64(),1U,0,0);

#if (!VCOP_HOST_EMULATION)
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_64_16i_16o_32inter_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_64_16i_16o_32inter_vloops;
        }
        else {
            vcop_fft_64_16i_16o_init(
                    context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit,
                    context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PARAMS_IDX]);

            context->execFunc[kernelIdx] = &vcop_fft_64_16i_16o_vloops;
        }

        /* Copy the param block pointers for each individual kernels */
        context->pBlock64.pblock_stage_1 = pBlock64->pblock_stage_1;
        context->pBlock64.pblock_stage_2 = pBlock64->pblock_stage_2;
        context->pBlock64.pblock_stage_3 = pBlock64->pblock_stage_3;
        for ( i = 0; i < 3U; i++)
        {
            context->pBlock64.execFunc[i] = pBlock64->execFunc[i];
        }
        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)(void *)&context->pBlock64;

#endif
    }
    else
    {
        status = BAM_E_FAIL;
    }
    kernelIdx++;

    if ( context->kernelInitArgs.enableTranspose == 1 )
    {
        int16_t * pDopplerInput;
        int16_t * pDopplerOutput;

        dopplerCorrectionBufInt = (int16_t (*)[BAM_FFT_NPT_16IX16O_MAX_NUM_POINTS])context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX];

        pDopplerInput  = (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT];/*WBUF*/
        pDopplerOutput = (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT];/*IBUFH*/

        /* for 512 point FFT transpose IBUF is not enough tp hold the transpose buf and hence we use WBUF to store the transpose
    and call another kernel to do a copy from WBUF to IBUF which removes the pitch */
        if ( context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512)
        {
            pDopplerInput  = (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT];/*IBUFH*/
            pDopplerOutput = (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT];/*WBUF*/
        }

        /* Copy doppler correction coefficients into internal memory */
        if ( context->kernelCtrlArgs.enableDopplerCorrection == 1)
        {
            EDMA_UTILS_memcpy2D((int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX],
                                context->kernelCtrlArgs.dopplerCorrectionBuf,
                                (uint16_t)context->kernelCtrlArgs.numPoints * sizeof(int16_t) * 2U,1U,0,0);
        }
        else
        {
            /* if doppler correction is disabled and transpose is enable then set the coefficients to 1 */
            for ( i= 0; i < context->kernelCtrlArgs.numPoints ; i++)
            {
                (*dopplerCorrectionBufInt)[2U * i]     = (int16_t)1;
                (*dopplerCorrectionBufInt)[(2U * i) + 1U] = 0;
            }
        }

        pScatterOffset = (uint16_t (*)[VCOP_SIMD_WIDTH])context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX];
        if ( context->kernelCtrlArgs.numLines < VCOP_SIMD_WIDTH)
        {
            context->dopplerCorrectionPitch        = ( (VCOP_SIMD_WIDTH) + 1U ) * sizeof(uint32_t);
        }
        else
        {
            context->dopplerCorrectionPitch        = (((context->kernelCtrlArgs.numLines % 2U)?context->kernelCtrlArgs.numLines:
                    context->kernelCtrlArgs.numLines + 1U)) *   sizeof(uint32_t);
        }

        for ( i = 0 ; i < VCOP_SIMD_WIDTH; i++)
        {
            (*pScatterOffset)[i] = (uint16_t)context->dopplerCorrectionPitch * (uint16_t)i;
        }
#if !VCOP_HOST_EMULATION
        vcop_fft_doppler_correction_kernel_init(
                pDopplerInput,
                pDopplerOutput,
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX],
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX],
                context->dopplerCorrectionPitch,
                context->kernelCtrlArgs.numPoints,
                context->kernelCtrlArgs.numLines,
                context->kernelCtrlArgs.dopplerCorrectionScaling,
                context->kernelCtrlArgs.saturationLimit,
                context->pBlockDopplerCorrection
        );
        context->execFunc[kernelIdx] = &vcop_fft_doppler_correction_kernel_vloops;
        context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)context->pBlockDopplerCorrection;
        kernelIdx++;

        if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512)
        {
            vcop_fft_doppler_pitch_removal_init(
                    pDopplerOutput,
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    context->dopplerCorrectionPitch,
                    context->kernelCtrlArgs.numLines*2u*sizeof(int16_t),
                    context->kernelCtrlArgs.numPoints,
                    (uint16_t)ALIGN_SIMD(context->kernelCtrlArgs.numLines),
                    context->pBlockDopplerPitchRemoval
            );

            context->execFunc[kernelIdx] = &vcop_fft_doppler_pitch_removal_vloops;
            context->kernelContext[kernelIdx] = (BAM_Fftnpt16ix16o_KernelContextType)context->pBlockDopplerPitchRemoval;
            kernelIdx++;
        }
#endif
    }

    context->numKernels = kernelIdx;

    return status;
}


static BAM_Status Bam_Fftnpt16ix16o_computeFrame(void *kernelContext)
{
    BAM_Fftnpt16ix16o_Context *context = (BAM_Fftnpt16ix16o_Context *)kernelContext;
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t i;


#if (VCOP_HOST_EMULATION)
    uint8_t inPlaceFFT;

    inPlaceFFT = 0;

    if ( context->kernelInitArgs.enableTranspose == 1 )
    {
        inPlaceFFT = 1;
        if (  context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512 )
        {
            inPlaceFFT = 0;
        }
    }

    if ( context->kernelCtrlArgs.numPointsZeroPadding != 0)
    {
        vcop_fft_zero_padding_kernel((uint32_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                                     context->kernelCtrlArgs.numActualPoints,
                                     context->kernelCtrlArgs.numLines,
                                     context->kernelCtrlArgs.numPointsZeroPadding,
                                     context->kernelCtrlArgs.pitch);
    }

    if ( context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_1024 )
    {
        vcop_fft_1024_16i_16o(
                (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                context->kernelCtrlArgs.numValidBits,
                context->kernelCtrlArgs.pitch,
                context->scaleFactorsIn,
                context->kernelCtrlArgs.numLines,
                inPlaceFFT,
                context->overFlowMask,
                context->kernelCtrlArgs.saturationLimit);
    }
    else if ( context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512 )
    {
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_512_16i_16o_32inter(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
        else {
            vcop_fft_512_16i_16o(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
    }
    else if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_128)
    {
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_128_16i_16o_32inter(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
        else {
            vcop_fft_128_16i_16o(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
    }
    else if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_256)
    {
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_256_16i_16o_32inter(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
        else {
            vcop_fft_256_16i_16o(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
    }
    else if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_64)
    {
        if (context->kernelCtrlArgs.enable32bitsIntermResults== 1) {
            vcop_fft_64_16i_16o_32inter(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
        else {
            vcop_fft_64_16i_16o(
                    (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_IBUFL_SCRATCH_BUF_IDX],
                    (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],
                    (int16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_TWIDDLE_FACTOR_BUF_IDX],
                    (uint16_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_IDX],
                    (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX],
                    context->kernelCtrlArgs.numValidBits,
                    context->kernelCtrlArgs.pitch,
                    context->scaleFactorsIn,
                    context->kernelCtrlArgs.numLines,
                    inPlaceFFT,
                    context->overFlowMask,
                    context->kernelCtrlArgs.saturationLimit);
        }
    }
    else
    {
        status = BAM_E_FAIL;
    }

    if ( context->kernelInitArgs.enableTranspose == 1 )
    {
        int16_t * pDopplerInput;
        int16_t * pDopplerOutput;

        pDopplerInput  = (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT];/*WBUF*/
        pDopplerOutput = (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT];/*IBUFH*/

        /* for 512 point FFT transpose IBUF is not enough tp hold the transpose buf and hence we use WBUF to store the transpose
    and call another kernel to do a copy from WBUF to IBUF which removes the pitch */
        if ( context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512)
        {
            pDopplerInput  = (int16_t *)context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT];/*IBUFH*/
            pDopplerOutput = (int16_t *)context->pInBlock[BAM_FFT_NPT_16IX16O_INPUT_PORT];/*WBUF*/
        }

        if ( context->kernelCtrlArgs.enableDopplerCorrection == 1)
        {
            Bam_Fftnpt16ix16o_copyDopplerCorrectionCoefficients((uint16_t *)context);
        }

        vcop_fft_doppler_correction_kernel(
                pDopplerInput,
                pDopplerOutput,
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_DOPPLER_CORRECTION_BUF_IDX],
                context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_PSCATTER_DOPPLER_CORRECTION_IDX],
                context->dopplerCorrectionPitch,
                context->kernelCtrlArgs.numPoints,
                context->kernelCtrlArgs.numLines,
                context->kernelCtrlArgs.dopplerCorrectionScaling,
                context->kernelCtrlArgs.saturationLimit
        );

        if (context->kernelCtrlArgs.numPoints == BAM_FFT_NPT_16IX16O_NUM_POINTS_512)
        {
            vcop_fft_doppler_pitch_removal(
                    pDopplerOutput,/*WBUF*/
                    context->pOutBlock[BAM_FFT_NPT_16IX16O_OUTPUT_PORT],/*IBUFH*/
                    context->dopplerCorrectionPitch,
                    context->kernelCtrlArgs.numLines*2*sizeof(int16_t),
                    context->kernelCtrlArgs.numPoints,
                    ALIGN_SIMD(context->kernelCtrlArgs.numLines));
        }

    }

#else
    for ( i = 0; i < context->numKernels; i++)
    {
        (context->execFunc[i])(context->kernelContext[i]);
    }
#endif
    context->blockCount++;

    return status;
}


static BAM_Status Bam_Fftnpt16ix16o_control(void *kernelContext,
                                            void * kernelCtlArg)
{
    BAM_Fftnpt16ix16o_Context *context = (BAM_Fftnpt16ix16o_Context *) kernelContext;

    BAM_Fftnpt16ix16o_CtrlArgs * args = (BAM_Fftnpt16ix16o_CtrlArgs * )kernelCtlArg;
    BAM_Status status = BAM_S_SUCCESS;

    if ( args->cmdId == BAM_FFT_NPT_16IX16O_CTRL_CMD_ID_SET_PARAMS)
    {
        BAM_Fftnpt16ix16o_InCtrlArgs * inCtrlArgs = (BAM_Fftnpt16ix16o_InCtrlArgs *)args->ctrlArgs;
        context->kernelCtrlArgs = *inCtrlArgs;
    }
    else if ( args->cmdId == BAM_FFT_NPT_16IX16O_CTRL_CMD_ID_GET_WBUF_PTR)
    {
        BAM_Fftnpt16ix16o_OutCtrlArgs * outCtrlArgs = (BAM_Fftnpt16ix16o_OutCtrlArgs *)args->ctrlArgs;
        outCtrlArgs->WBUFPtrScaleFactorOut = (uint8_t *)context->pInternalBlock[FFT_NPT_16IX16O_INTERNAL_SCALEFACTOR_OUT_BUF_IDX];
    }
    else
    {
        status = BAM_E_FAIL;
    }


    return status;
}


BAM_KernelExecFuncDef gBAM_TI_Fftnpt16ix16oExecFunc =
{
 NULL,
 &Bam_Fftnpt16ix16o_initFrame,
 &Bam_Fftnpt16ix16o_computeFrame,
 NULL,
 &Bam_Fftnpt16ix16o_control,
 NULL
};


