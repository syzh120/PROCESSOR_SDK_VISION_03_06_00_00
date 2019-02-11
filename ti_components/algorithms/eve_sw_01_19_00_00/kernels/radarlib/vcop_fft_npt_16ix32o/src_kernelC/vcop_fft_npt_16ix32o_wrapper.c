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

/*                                                                          */
/*     @file : vcop_fft_npt_16ix32o_wrapper.c                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the wrapper functions   */
/*     for the different FFT sizes                                      */
/*                                                                          */
/*     Wrappers for the following FFTs are provided:    */
/*                                         */
/*                                                                          */
/*     @version 1.0 (August 2016) : Base version.                         */
/*                                                                          */
/*==========================================================================*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "vcop.h"
#include "vcop_fft_npt_16ix32o_wrapper.h"

#if (!VCOP_HOST_EMULATION)
#include "vcop_fft_512_16ix32o_kernel.h"
#include "vcop_fft_256_16ix32o_kernel.h"
#include "vcop_fft_128_16ix32o_kernel.h"
#include "vcop_fft_64_16ix32o_kernel.h"
#include "vcop_fft_512_16ix16o_32inter_kernel.h"
#include "vcop_fft_256_16ix16o_32inter_kernel.h"
#include "vcop_fft_128_16ix16o_32inter_kernel.h"
#include "vcop_fft_64_16ix16o_32inter_kernel.h"

#else
#include "vcop_fft_512_16ix32o_kernel.k"
#include "vcop_fft_256_16ix32o_kernel.k"
#include "vcop_fft_128_16ix32o_kernel.k"
#include "vcop_fft_64_16ix32o_kernel.k"

/* Only when we build for the testbench, we include the *.k files that correspond to the 32-bits intermediary ressults because we use some of the kernels
    Otherwise when building the applet, we exclude them and include the *.h files instead in order to avoid linker errors of symbols already defined.
*/
#if _FOR_FFT_O32_TEST_BENCH
#include "../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_512_16ix16o_32inter_kernel.k"
#include "../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_256_16ix16o_32inter_kernel.k"
#include "../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_128_16ix16o_32inter_kernel.k"
#include "../../vcop_fft_npt_16ix16o/src_kernelC/vcop_fft_64_16ix16o_32inter_kernel.k"

#else

#include "vcop_fft_512_16ix16o_32inter_kernel.h"
#include "vcop_fft_256_16ix16o_32inter_kernel.h"
#include "vcop_fft_128_16ix16o_32inter_kernel.h"
#include "vcop_fft_64_16ix16o_32inter_kernel.h"

#endif

#endif

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN(x,y)         ((((x) + (y) - 1U)/(y))*(y))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


#define INDIVIDUAL_PROFILING (0)

#if (INDIVIDUAL_PROFILING)
#include "eve_profile.h"
#endif

#if _DUMP
#include <stdio.h>
void dumpIntoFile_32inter(int32_t *pScratchIBufL, int32_t stageNo, int32_t numOfGrp, int32_t numBFperGrp, int32_t currentRadix, int32_t numOfLines, int32_t numPoints, int32_t overflowMask, int32_t transposeStride) {

    int32_t j, groupIdx, bfIdx, twIdx;
    FILE *fid;
    int32_t *basePtrGrp;
    char filename[256];

    for (j=0; j < numOfLines; j++) {
        sprintf(filename, "kernelCdump/test_%dx%d_ovf%d_line_%d.txt", numOfLines, numPoints, (overflowMask!=0), j);

        if (stageNo== 1) {
            fid= fopen(filename, "wt");
        }
        else {
            fid= fopen(filename, "at");
        }

        if (fid== NULL) {
            printf("Error opening file %s\n", filename);
        }
        else {
            fprintf(fid, "stage %d\n", stageNo);
            fprintf(fid, "--------\n");
            for ( groupIdx = 0 ; groupIdx < numOfGrp; groupIdx++) {
                if (transposeStride== 0) {
                    basePtrGrp    = pScratchIBufL + j*numOfGrp*numBFperGrp * currentRadix * 2 + groupIdx * numBFperGrp * currentRadix * 1;
                    for ( bfIdx = 0 ; bfIdx < 1*4*numBFperGrp; bfIdx++) {
                        fprintf(fid, "%06d ", *(basePtrGrp + bfIdx));
                        fprintf(fid, "%06d ", *(basePtrGrp + numPoints + bfIdx));
                    }
                }
                else {
                    if (numPoints== 64) {
                        basePtrGrp    = pScratchIBufL + (j/2)*transposeStride*numBFperGrp*2 + groupIdx * 1 + (j%2)*4*1;
                    }
                    else if (numPoints== 1024 || numPoints== 512) {
                        basePtrGrp    = pScratchIBufL + j*transposeStride*numBFperGrp*2 + (groupIdx%4)*1*4 + (groupIdx/4) * 1;
                    }
                    else {
                        basePtrGrp    = pScratchIBufL + j*transposeStride*numBFperGrp*2 + groupIdx * 1;
                    }
                    for (twIdx= 0; twIdx < currentRadix; twIdx++) {
                        for ( bfIdx = 0 ; bfIdx < numBFperGrp; bfIdx++) {
                            fprintf(fid, "%06d ", *(basePtrGrp + twIdx*numOfGrp*1 + bfIdx*transposeStride));
                            fprintf(fid, "%06d ", *(basePtrGrp + numBFperGrp*transposeStride + twIdx*numOfGrp*1 + bfIdx*transposeStride));
                        }
                    }
                }
                fprintf(fid, "\n");
            }
            fclose(fid);
        }
    }
}

#endif


uint32_t vcop_fft_512_16i_32o_param_count(void)
{
    uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
    uint32_t pBlockCount1;
    uint32_t pBlockCount2;
#if (!VCOP_HOST_EMULATION)
    pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_512_pBlock_t)), 4U) +
            vcop_fft_512_32inter_stage_1_param_count() +
            vcop_fft_512_32inter_stage_2_param_count() +
            vcop_fft_512_32inter_stage_3_param_count() +
            vcop_fft_512_32inter_stage_4_param_count() +
            vcop_fft_512_16ix32o_radix2_stage_5_param_count();

    pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_512_pBlock_t)), 4U) +
            vcop_fft_512_32inter_stage_1_param_count() +
            vcop_fft_512_32inter_stage_2_param_count() +
            vcop_fft_512_32inter_stage_3_param_count() +
            vcop_fft_512_32inter_stage_4_param_count() +
            vcop_fft_512_16ix32o_radix2_stage_5_overflow_param_count();
    pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif

return pBlockCount;
}


#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_512_16i_32o_init(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     *pScatterOffset,
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t      overflowMask,
        uint16_t      saturationLimit,
        uint16_t     *pblock)
{
    uint16_t scatterOffsetArray[]={0 ,
                                   65 * 4 * 1,
                                   65 * 4 * 2,
                                   65 * 4 * 3,
                                   65 * 4 * 4,
                                   65 * 4 * 5,
                                   65 * 4 * 6,
                                   65 * 4 * 7};

    uint32_t N = 512U;
    int32_t * pStage5Out;
    uint32_t execFuncCount = 0;


    sVCOP_FFT_512_pBlock_t * pBlock512 = (sVCOP_FFT_512_pBlock_t *)(void *) pblock;

    memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    pBlock512->pblock_stage_1 = (uint16_t *)pBlock512 + (ALIGN(sizeof(sVCOP_FFT_512_pBlock_t), 4U)/ sizeof(uint16_t));
    pBlock512->pblock_stage_2   = (uint16_t *)pBlock512->pblock_stage_1 + vcop_fft_512_32inter_stage_1_param_count();
    pBlock512->pblock_stage_3   = (uint16_t *)pBlock512->pblock_stage_2 + vcop_fft_512_32inter_stage_2_param_count();
    pBlock512->pblock_stage_4   = (uint16_t *)pBlock512->pblock_stage_3 + vcop_fft_512_32inter_stage_3_param_count();
    pBlock512->pblock_stage_5   = (uint16_t *)pBlock512->pblock_stage_4 + vcop_fft_512_32inter_stage_4_param_count();
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    vcop_fft_512_32inter_stage_1_init(
            &pInputDataWBuf[0],
            (int32_t*)(void*)&pInputDataWBuf[0],
            (uint16_t*)(void *)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void *)&pScratchIBufH[0],
            &pScratchIBufH[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )],
            pitch,
            numOfLines,
            pBlock512->pblock_stage_1
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_32inter_stage_1_vloops;
    execFuncCount++;

    vcop_fft_512_32inter_stage_2_init(
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)pScratchIBufH,
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t *)(void *)&pInputDataWBuf[0],
            (uint16_t *)(void *)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            (int16_t *)&twiddleFactorBuf[(N/4U) * 3U * 2U],
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines,
            pBlock512->pblock_stage_2
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_32inter_stage_2_vloops;
    execFuncCount++;

    vcop_fft_512_32inter_stage_3_init
    (
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)pScratchIBufH,
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            &twiddleFactorBuf[ ((N/4U) + (N/16U)) * 3U * 2U],
            pScatterOffset,
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines,
            pBlock512->pblock_stage_3
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_32inter_stage_3_vloops;
    execFuncCount++;

    if ( enableInPlaceCompute == 1U )
    {
        pStage5Out = (int32_t*)(void*)&pInputDataWBuf[0];
    }
    else
    {
        pStage5Out = (int32_t*)(void*)&pScratchIBufH[0];
    }

    vcop_fft_512_32inter_stage_4_init
    (
            (int32_t*)(void*)&pInputDataWBuf[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)pScratchIBufH,
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            &twiddleFactorBuf[ ((N/4U) + (N/16U) + ((N/64U) * 4U)) * 3U * 2U],
            numOfLines,
            pBlock512->pblock_stage_4
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_32inter_stage_4_vloops;
    execFuncCount++;

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE5_OVERFLOW)
    {
        vcop_fft_512_16ix32o_radix2_stage_5_overflow_init(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t *)(void *)&pScratchIBufL[0],
                (int32_t *)(void *)&pScratchIBufH[0],
                pStage5Out,
                &pScaleFactorOut[4],
                numValidBits,
                numOfLines,
                pBlock512->pblock_stage_5
        );
        pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix32o_radix2_stage_5_overflow_vloops;
        execFuncCount++;
    }
    else
    {
        vcop_fft_512_16ix32o_radix2_stage_5_init(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t *)(void *)&pScratchIBufL[0],
                (int32_t *)(void *)&pScratchIBufH[0],
                pStage5Out,
                numOfLines,
                pBlock512->pblock_stage_5
        );
        pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix32o_radix2_stage_5_vloops;
        execFuncCount++;
    }

    return (uint32_t)0;
}


void vcop_fft_512_16i_32o_vloops(uint16_t pblock[])
{
    sVCOP_FFT_512_pBlock_t * pBlock512 = (sVCOP_FFT_512_pBlock_t *) pblock;

    pBlock512->execFunc[0](pBlock512->pblock_stage_1);
    pBlock512->execFunc[1](pBlock512->pblock_stage_2);
    pBlock512->execFunc[2](pBlock512->pblock_stage_3);
    pBlock512->execFunc[3](pBlock512->pblock_stage_4);
    pBlock512->execFunc[4](pBlock512->pblock_stage_5);

}
#endif

void vcop_fft_512_16i_32o(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     *pScatterOffset,
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t      overflowMask,
        uint16_t      saturationLimit)
{
    uint16_t scatterOffsetArray[]={0 ,
                                   65 * 4 * 1,
                                   65 * 4 * 2,
                                   65 * 4 * 3,
                                   65 * 4 * 4,
                                   65 * 4 * 5,
                                   65 * 4 * 6,
                                   65 * 4 * 7};


    uint32_t N = 512U;
    int32_t * pStage5Out;

    memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_512_32inter_stage_1(
            &pInputDataWBuf[0],
            (int32_t*)(void *)&pInputDataWBuf[0],
            (uint16_t*)(void *)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void *)&pScratchIBufH[0],
            (int16_t*)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )],
            pitch,
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        numOfGrp    = 1;
        currentRadix= 4;
        numPoints= 512;

        numBFperGrp = numPoints / currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pScratchIBufL[0], 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0);
    }
#endif

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_512_32inter_stage_2(
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t *)(void *)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t *)(void *)&pInputDataWBuf[0],
            (uint16_t *)(void *)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            (int16_t *)&twiddleFactorBuf[(N/4U) * 3U * 2U],
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        currentRadix= 4;
        numPoints= 512;

        numBFperGrp = numPoints / (4*currentRadix);
        numOfGrp= currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pScratchIBufL[0], 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0);
    }
#endif


#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_512_32inter_stage_3
    (
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t *)(void *)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            &twiddleFactorBuf[ ((N/4U) + (N/16U)) * 3U * 2U],
            pScatterOffset,
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        currentRadix= 4;
        numPoints= 512;

        numBFperGrp = numPoints / (4*4*currentRadix);
        numOfGrp= 4*currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pInputDataWBuf[0], 3, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 65);
    }
#endif

    if ( enableInPlaceCompute == 1U )
    {
        pStage5Out = (int32_t*)(void*)&pInputDataWBuf[0];
    }
    else
    {
        pStage5Out = (int32_t*)(void*)&pScratchIBufH[0];
    }

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif
    vcop_fft_512_32inter_stage_4
    (
            (int32_t*)(void*)&pInputDataWBuf[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t*)(void*)&pScratchIBufL[0],
            (int16_t*)(void*)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void*)&pScratchIBufH[0],
            (int16_t*)(void*)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            &twiddleFactorBuf[ ((N/4U) + (N/16U) + ((N/64U) * 4U)) * 3U * 2U],
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE5_OVERFLOW)
    {
        vcop_fft_512_16ix32o_radix2_stage_5_overflow(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t*)(void*)&pScratchIBufL[0],
                (int32_t*)(void*)&pScratchIBufH[0],
                pStage5Out,
                &pScaleFactorOut[4],
                numValidBits,
                numOfLines
        );
    }
    else
    {
        vcop_fft_512_16ix32o_radix2_stage_5(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t*)(void*)&pScratchIBufL[0],
                (int32_t*)(void*)&pScratchIBufH[0],
                pStage5Out,
                numOfLines
        );
    }

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

}


uint32_t vcop_fft_128_16i_32o_param_count(void)
{
    uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
    uint32_t pBlockCount1;
    uint32_t pBlockCount2;

#if (!VCOP_HOST_EMULATION)
    pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_128_pBlock_t)), 4U) +
            vcop_fft_128_32inter_stage_1_param_count() +
            vcop_fft_128_32inter_stage_2_param_count() +
            vcop_fft_128_32inter_stage_3_param_count() +
            vcop_fft_128_16ix32o_radix2_stage_4_overflow_param_count();

    pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_128_pBlock_t)), 4U) +
            vcop_fft_128_32inter_stage_1_param_count() +
            vcop_fft_128_32inter_stage_2_param_count() +
            vcop_fft_128_32inter_stage_3_param_count() +
            vcop_fft_128_16ix32o_radix2_stage_4_param_count();

    pBlockCount = MAX(pBlockCount1,pBlockCount2);

#endif

    return pBlockCount;

}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_128_16i_32o_init(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     *pScatterOffset,
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t      overflowMask,
        uint16_t     saturationLimit,
        uint16_t     *pblock)
{
    int16_t * tfStageBasePtr = NULL;
    uint32_t N = 128U;
    uint16_t scatterOffsetArray[]={0 ,
                                   17 * 4 * 1,
                                   17 * 4 * 2,
                                   17 * 4 * 3,
                                   17 * 4 * 4,
                                   17 * 4 * 5,
                                   17 * 4 * 6,
                                   17 * 4 * 7};

    sVCOP_FFT_128_pBlock_t * pBlock128 = (sVCOP_FFT_128_pBlock_t *) (void *)pblock;
    int32_t * pStage4Out;
    uint32_t  execFuncCount = 0;
    memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

    tfStageBasePtr = &twiddleFactorBuf[0];
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    pBlock128->pblock_stage_1   = (uint16_t *)pBlock128 + (ALIGN(sizeof(sVCOP_FFT_128_pBlock_t), 4U)/ sizeof(uint16_t));

    /* Overflow detection param counts are always higher hence use the worst case number */
    pBlock128->pblock_stage_2   = (uint16_t *)pBlock128->pblock_stage_1 + vcop_fft_128_32inter_stage_1_param_count();
    pBlock128->pblock_stage_3   = (uint16_t *)pBlock128->pblock_stage_2 + vcop_fft_128_32inter_stage_2_param_count();
    pBlock128->pblock_stage_4   = (uint16_t *)pBlock128->pblock_stage_3 + vcop_fft_128_32inter_stage_3_param_count();

    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    vcop_fft_128_32inter_stage_1_init
    (
            &pInputDataWBuf[0],
            (int32_t *)(void *)&pInputDataWBuf[0],
            (uint16_t *)(void *)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            tfStageBasePtr,
            pitch,
            numOfLines,
            pBlock128->pblock_stage_1
    );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_32inter_stage_1_vloops;
    execFuncCount++;

    tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

    vcop_fft_128_32inter_stage_2_init
    (
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            tfStageBasePtr,
            pScatterOffset,
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines,
            pBlock128->pblock_stage_2
    );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_32inter_stage_2_vloops;
    execFuncCount++;

    tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (4U * (N/16U))) * 3U * 2U];

    if ( enableInPlaceCompute == 1U )
    {
        pStage4Out = (int32_t*)(void*)&pInputDataWBuf[0];
    }
    else
    {
        pStage4Out = (int32_t*)(void*)&pScratchIBufH[0];
    }

    vcop_fft_128_32inter_stage_3_init(
            (int32_t*)(void*)&pInputDataWBuf[0],/*Leg 0 */
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            tfStageBasePtr,
            numOfLines,
            pBlock128->pblock_stage_3
    );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_32inter_stage_3_vloops;
    execFuncCount++;

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE4_OVERFLOW)
    {
        vcop_fft_128_16ix32o_radix2_stage_4_overflow_init(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t *)(void *)&pScratchIBufL[0],
                (int32_t *)(void *)&pScratchIBufH[0],
                pStage4Out,
                &pScaleFactorOut[3],
                numValidBits,
                numOfLines,
                pBlock128->pblock_stage_4
        );
        pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix32o_radix2_stage_4_overflow_vloops;
        execFuncCount++;
    }
    else {
        vcop_fft_128_16ix32o_radix2_stage_4_init(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t *)(void *)&pScratchIBufL[0],
                (int32_t *)(void *)&pScratchIBufH[0],
                pStage4Out,
                numOfLines,
                pBlock128->pblock_stage_4
        );
        pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix32o_radix2_stage_4_vloops;
        execFuncCount++;
    }

    return (uint32_t)0;
}


void vcop_fft_128_16i_32o_vloops(uint16_t pblock[])
{
    sVCOP_FFT_128_pBlock_t * pBlock128 = (sVCOP_FFT_128_pBlock_t *) pblock;

    pBlock128->execFunc[0](pBlock128->pblock_stage_1);
    pBlock128->execFunc[1](pBlock128->pblock_stage_2);
    pBlock128->execFunc[2](pBlock128->pblock_stage_3);
    pBlock128->execFunc[3](pBlock128->pblock_stage_4);

}
#endif

void vcop_fft_128_16i_32o(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     *pScatterOffset,
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t      overflowMask,
        uint16_t     saturationLimit)
{
    int16_t * tfStageBasePtr = NULL;
    uint32_t N = 128U;
    uint16_t scatterOffsetArray[]={0 ,
                                   17 * 4 * 1,
                                   17 * 4 * 2,
                                   17 * 4 * 3,
                                   17 * 4 * 4,
                                   17 * 4 * 5,
                                   17 * 4 * 6,
                                   17 * 4 * 7};

    int32_t * pStage4Out;
    memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

    tfStageBasePtr = &twiddleFactorBuf[0];

    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    vcop_fft_128_32inter_stage_1
    (
            &pInputDataWBuf[0],
            (int32_t *)(void *)&pInputDataWBuf[0],
            (uint16_t *)(void *)&pInputDataWBuf[0],
            (int16_t *)(void *)&pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            tfStageBasePtr,
            pitch,
            numOfLines
    );

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        numOfGrp    = 1;
        currentRadix= 4;
        numPoints= 128;

        numBFperGrp = numPoints / currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pScratchIBufL[0], 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0);
    }
#endif

    tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

    vcop_fft_128_32inter_stage_2
    (
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            tfStageBasePtr,
            pScatterOffset,
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines
    );

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        currentRadix= 4;
        numPoints= 128;

        numBFperGrp = numPoints / (4*currentRadix);
        numOfGrp= currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pInputDataWBuf[0], 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 17);
    }
#endif

    tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (4U * (N/16U))) * 3U * 2U];

    if ( enableInPlaceCompute == 1U )
    {
        pStage4Out = (int32_t*)(void*)&pInputDataWBuf[0];
    }
    else
    {
        pStage4Out = (int32_t*)(void*)&pScratchIBufH[0];
    }

    vcop_fft_128_32inter_stage_3(
            (int32_t*)(void*)&pInputDataWBuf[0],/*Leg 0 */
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t *)(void *)&pScratchIBufL[0],
            (int16_t *)(void *)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pInputDataWBuf[0],
            tfStageBasePtr,
            numOfLines
    );

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE4_OVERFLOW)
    {
        vcop_fft_128_16ix32o_radix2_stage_4_overflow(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t *)(void *)&pScratchIBufL[0],
                (int32_t *)(void *)&pScratchIBufH[0],
                pStage4Out,
                &pScaleFactorOut[3],
                numValidBits,
                numOfLines
        );
    }
    else {
        vcop_fft_128_16ix32o_radix2_stage_4(
                (int32_t*)(void*)&pInputDataWBuf[0],
                (int32_t *)(void *)&pScratchIBufL[0],
                (int32_t *)(void *)&pScratchIBufH[0],
                pStage4Out,
                numOfLines
        );
    }

}


uint32_t vcop_fft_256_16i_32o_param_count(void)
{
    uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
    uint32_t pBlockCount1;
    uint32_t pBlockCount2;

#if (!VCOP_HOST_EMULATION)
    pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_256_pBlock_t)), 4U) +
            vcop_fft_256_32inter_stage_1_param_count() +
            vcop_fft_256_32inter_stage_2_param_count() +
            vcop_fft_256_32inter_stage_3_param_count() +
            vcop_fft_256_16ix32o_stage_4_overflow_param_count();
    pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_256_pBlock_t)), 4U) +
            vcop_fft_256_32inter_stage_1_param_count() +
            vcop_fft_256_32inter_stage_2_param_count() +
            vcop_fft_256_32inter_stage_3_param_count() +
            vcop_fft_256_16ix32o_stage_4_param_count();

    pBlockCount = MAX(pBlockCount1,pBlockCount2);

#endif

    return pBlockCount;
}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_256_16i_32o_init(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     *pScatterOffset,
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t      overflowMask,
        uint16_t     saturationLimit,
        uint16_t     *pblock)
{
    int16_t * tfStageBasePtr = NULL;
    uint32_t N = 256U;

    uint16_t scatterOffsetArray[]={0 ,
                                   17 * 4 * 1,
                                   17 * 4 * 2,
                                   17 * 4 * 3,
                                   17 * 4 * 4,
                                   17 * 4 * 5,
                                   17 * 4 * 6,
                                   17 * 4 * 7};

    int32_t * pStage4Out;
    uint32_t  execFuncCount = 0;

    sVCOP_FFT_256_pBlock_t * pBlock256 = (sVCOP_FFT_256_pBlock_t *)(void *) pblock;

    memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

    tfStageBasePtr = &twiddleFactorBuf[0];

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    pBlock256->pblock_stage_1   = (uint16_t *)pBlock256 + (ALIGN(sizeof(sVCOP_FFT_256_pBlock_t), 4U)/ sizeof(uint16_t));
    pBlock256->pblock_stage_2   = (uint16_t *)pBlock256->pblock_stage_1 + vcop_fft_256_32inter_stage_1_param_count();
    pBlock256->pblock_stage_3   = (uint16_t *)pBlock256->pblock_stage_2 + vcop_fft_256_32inter_stage_2_param_count();
    pBlock256->pblock_stage_4   = (uint16_t *)pBlock256->pblock_stage_3 + vcop_fft_256_32inter_stage_3_param_count();
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    vcop_fft_256_32inter_stage_1_init
    (
            &pInputDataWBuf[0],
            (int32_t *)(void *)&pInputDataWBuf[0],
            (uint16_t*)(void*)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            tfStageBasePtr,
            pitch,
            numOfLines,
            pBlock256->pblock_stage_1
    );

    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_32inter_stage_1_vloops;
    execFuncCount++;

    tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

    vcop_fft_256_32inter_stage_2_init
    (
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t*)(void*)&pScratchIBufL[0],
            (int16_t*)(void*)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void*)&pScratchIBufH[0],
            (int16_t*)(void*)&pScratchIBufH[1],
            (int32_t *)(void *)pInputDataWBuf,
            tfStageBasePtr,
            pScatterOffset,
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines,
            pBlock256->pblock_stage_2
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_32inter_stage_2_vloops;
    execFuncCount++;

    tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (2U * (N/16U))) * 3U * 2U];
    if ( enableInPlaceCompute == 1U )
    {
        pStage4Out = (int32_t*)(void*)&pInputDataWBuf[0];
    }
    else
    {
        pStage4Out = (int32_t *)(void *)pScratchIBufH;
    }
    vcop_fft_256_32inter_stage_3_init(
            (int32_t *)(void *)&pInputDataWBuf[0],/*Leg 0 */
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t*)(void*)&pScratchIBufL[0],
            (int16_t*)(void*)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void*)pScratchIBufH,
            (int16_t*)(void*)&pScratchIBufH[1],
            (int32_t *)(void *)&pInputDataWBuf[0],
            tfStageBasePtr,
            numOfLines,
            pBlock256->pblock_stage_3
    );

    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_32inter_stage_3_vloops;
    execFuncCount++;

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE4_OVERFLOW)
    {
        vcop_fft_256_16ix32o_stage_4_overflow_init(
                (int32_t *)(void *)&pInputDataWBuf[0],
                (int32_t*)(void*)&pScratchIBufL[0],
                (int32_t*)(void*)&pScratchIBufH[0],
                pStage4Out,
                &pScaleFactorOut[3],
                numValidBits,
                numOfLines,
                pBlock256->pblock_stage_4
        );
        pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix32o_stage_4_overflow_vloops;
        execFuncCount++;
    }
    else {
        vcop_fft_256_16ix32o_stage_4_init(
                (int32_t *)(void *)&pInputDataWBuf[0],
                (int32_t*)(void*)&pScratchIBufL[0],
                (int32_t*)(void*)&pScratchIBufH[0],
                pStage4Out,
                numOfLines,
                pBlock256->pblock_stage_4
        );
        pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix32o_stage_4_vloops;
        execFuncCount++;
    }

    return (uint32_t)0;
}


void vcop_fft_256_16i_32o_vloops(uint16_t pblock[])
{
    sVCOP_FFT_256_pBlock_t * pBlock256 = (sVCOP_FFT_256_pBlock_t *) pblock;


    pBlock256->execFunc[0](pBlock256->pblock_stage_1);
    pBlock256->execFunc[1](pBlock256->pblock_stage_2);
    pBlock256->execFunc[2](pBlock256->pblock_stage_3);
    pBlock256->execFunc[3](pBlock256->pblock_stage_4);

}
#endif

void vcop_fft_256_16i_32o(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     *pScatterOffset,
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t     overflowMask,
        uint16_t     saturationLimit)
{
    int16_t * tfStageBasePtr = NULL;

    uint16_t scatterOffsetArray[]={0 ,
                                   17 * 4 * 1,
                                   17 * 4 * 2,
                                   17 * 4 * 3,
                                   17 * 4 * 4,
                                   17 * 4 * 5,
                                   17 * 4 * 6,
                                   17 * 4 * 7};


    uint32_t N = 256U;
    int32_t * pStage4Out;
    memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

    tfStageBasePtr = &twiddleFactorBuf[0];

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_256_32inter_stage_1
    (
            &pInputDataWBuf[0],
            (int32_t *)(void *)&pInputDataWBuf[0],
            (uint16_t*)(void*)&pInputDataWBuf[0],
            &pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t *)(void *)&pScratchIBufH[0],
            (int16_t *)(void *)&pScratchIBufH[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            tfStageBasePtr,
            pitch,
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        numOfGrp    = 1;
        currentRadix= 4;
        numPoints= 256;

        numBFperGrp = numPoints / currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pScratchIBufL[0], 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0);
    }
#endif


    tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_256_32inter_stage_2
    (
            (int32_t*)(void*)&pScratchIBufL[0],
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t*)(void*)&pScratchIBufL[0],
            (int16_t*)(void*)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void*)&pScratchIBufH[0],
            (int16_t*)(void*)&pScratchIBufH[1],
            (int32_t *)(void *)&pInputDataWBuf[0],
            tfStageBasePtr,
            pScatterOffset,
            (uint16_t)(N * sizeof(int32_t) * 2U),
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        currentRadix= 4;
        numPoints= 256;

        numBFperGrp = numPoints / (4*currentRadix);
        numOfGrp= currentRadix;

        dumpIntoFile_32inter((int32_t *)(void *)&pInputDataWBuf[0], 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 17);
    }
#endif

    tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (2U * (N/16U))) * 3U * 2U];

    if ( enableInPlaceCompute == 1U )
    {
        pStage4Out = (int32_t*)(void*)&pInputDataWBuf[0];
    }
    else
    {
        pStage4Out = (int32_t *)(void *)pScratchIBufH;
    }

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif
    vcop_fft_256_32inter_stage_3(
            (int32_t *)(void *)&pInputDataWBuf[0],/*Leg 0 */
            (int32_t*)(void*)&pScratchIBufL[0],
            (uint16_t*)(void*)&pScratchIBufL[0],
            (int16_t*)(void*)&pScratchIBufL[1],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void*)&pScratchIBufH[0],
            (int16_t*)(void*)&pScratchIBufH[1],
            (int32_t *)(void *)&pInputDataWBuf[0],
            tfStageBasePtr,
            numOfLines
    );
#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE4_OVERFLOW)
    {
        vcop_fft_256_16ix32o_stage_4_overflow(
                (int32_t *)(void *)&pInputDataWBuf[0],
                (int32_t*)(void*)&pScratchIBufL[0],
                (int32_t*)(void*)&pScratchIBufH[0],
                pStage4Out,
                &pScaleFactorOut[3],
                numValidBits,
                numOfLines
        );
    }
    else
    {
        vcop_fft_256_16ix32o_stage_4(
                (int32_t *)(void *)&pInputDataWBuf[0],
                (int32_t*)(void*)&pScratchIBufL[0],
                (int32_t*)(void*)&pScratchIBufH[0],
                pStage4Out,
                numOfLines
        );
    }

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif


}


uint32_t vcop_fft_64_16i_32o_param_count(void)
{
    uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
    uint32_t pBlockCount1;
    uint32_t pBlockCount2;

#if (!VCOP_HOST_EMULATION)
    pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_64_pBlock_t)), 4U) +
            vcop_fft_64_32inter_stage_1_param_count() +
            vcop_fft_64_32inter_stage_2_param_count() +
            vcop_fft_64_16ix32o_stage_3_overflow_param_count();

    pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_64_pBlock_t)), 4U) +
            vcop_fft_64_32inter_stage_1_param_count() +
            vcop_fft_64_32inter_stage_2_param_count() +
            vcop_fft_64_16ix32o_stage_3_param_count();

    pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif

    return pBlockCount;

}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_64_16i_32o_init(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     pScatterOffset[],
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t      overflowMask,
        uint16_t      saturationLimit,
        uint16_t     *pblock)
{
    int16_t * tfStageBasePtr = NULL;
    uint16_t scatterOffsetArray1[]={0 ,
                                    9 * 4 * 1,
                                    9 * 4 * 2,
                                    9 * 4 * 3,
                                    9 * 4 * 4,
                                    9 * 4 * 5,
                                    9 * 4 * 6,
                                    9 * 4 * 7};

    uint16_t scatterOffsetArray2[]={0 ,
                                    1 * 4 * 1,
                                    1 * 4 * 2,
                                    1 * 4 * 3,
                                    1 * 4 * 68,
                                    1 * 4 * 69,
                                    1 * 4 * 70,
                                    1 * 4 * 71};
    uint32_t N = 64U;
    int32_t * pStage2In;
    uint16_t * pStage2Scratch1;
    int16_t * pStage2Scratch1_plusOne;
    uint16_t * pStage2Scratch2;
    int16_t * pStage2Scratch2_plusOne;
    int32_t * pStage2Out;
    int32_t * pStage3Out;
    int32_t * pStage3Scratch1;
    int32_t * pStage3Scratch2;
    int16_t * pStage3InterimBuf;
    uint32_t  execFuncCount = 0;

    sVCOP_FFT_64_pBlock_t * pBlock64 = (sVCOP_FFT_64_pBlock_t *)(void *) pblock;

    memcpy(pScatterOffset, scatterOffsetArray1, sizeof(scatterOffsetArray1));
    memcpy(&pScatterOffset[8], scatterOffsetArray2, sizeof(scatterOffsetArray2));

    tfStageBasePtr = &twiddleFactorBuf[0];

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    pBlock64->pblock_stage_1   = (uint16_t *)(void *)pBlock64 + (ALIGN(sizeof(sVCOP_FFT_64_pBlock_t), 4U)/ sizeof(uint16_t));
    pBlock64->pblock_stage_2   = (uint16_t *)pBlock64->pblock_stage_1 + vcop_fft_64_32inter_stage_1_param_count();
    pBlock64->pblock_stage_3   = (uint16_t *)pBlock64->pblock_stage_2 + vcop_fft_64_32inter_stage_2_param_count();

    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    vcop_fft_64_32inter_stage_1_init
    (
            &pInputDataWBuf[0],
            (int32_t*)(void*)&pScratchIBufH[0],
            (uint16_t*)(void *)&pScratchIBufH[0],
            (int16_t*)(void *)&pScratchIBufH[1],
            (int32_t*)(void *)&pInputDataWBuf[0],
            (uint16_t*)(void *)&pInputDataWBuf[0],
            (int16_t*)(void *)&pInputDataWBuf[1],
            (int32_t*)(void*)&pScratchIBufL[0],
            tfStageBasePtr,
            pScatterOffset,
            pitch,
            numOfLines,
            pBlock64->pblock_stage_1
    );

    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_32inter_stage_1_vloops;
    execFuncCount++;

    tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];
    if ( enableInPlaceCompute == 1U )
    {
        pStage2In  = (int32_t*)(void*)&pScratchIBufL[0];
        pStage2Out = (int32_t*)(void*)&pScratchIBufH[0];
        pStage2Scratch1 = (uint16_t*)(void*)&pScratchIBufL[0];
        pStage2Scratch1_plusOne = (int16_t*)(void*)&pScratchIBufL[1];
        pStage2Scratch2 = (uint16_t*)(void *)&pInputDataWBuf[0];
        pStage2Scratch2_plusOne = (int16_t*)(void *)&pInputDataWBuf[1];
        pStage3Out = (int32_t*)(void*)&pInputDataWBuf[0];
        pStage3InterimBuf = &pInputDataWBuf[0];
        pStage3Scratch1 = (int32_t*)(void*)&pScratchIBufL[0];
        pStage3Scratch2 = (int32_t*)(void*)&pScratchIBufH[0];

    }
    else
    {
        pStage2In  = (int32_t*)(void*)&pScratchIBufL[0];
        pStage2Out = (int32_t*)(void *)&pInputDataWBuf[0];
        pStage2Scratch1 = (uint16_t*)(void *)&pScratchIBufL[0];
        pStage2Scratch1_plusOne = (int16_t*)(void *)&pScratchIBufL[1];
        pStage2Scratch2 = (uint16_t*)(void *)&pScratchIBufH[0];
        pStage2Scratch2_plusOne = (int16_t*)(void *)&pScratchIBufH[1];
        pStage3Out = (int32_t*)(void *)&pScratchIBufH[0];
        pStage3Scratch1 = (int32_t*)(void *)&pScratchIBufL[0];
        pStage3Scratch2 = (int32_t*)(void *)&pInputDataWBuf[0];
        pStage3InterimBuf = (int16_t*)(void *)&pScratchIBufH[0];
    }

    vcop_fft_64_32inter_stage_2_init
    (
            pStage2In,
            (int32_t*)(void*)pStage2Scratch1,
            pStage2Scratch1,
            pStage2Scratch1_plusOne,
            (int32_t*)(void*)pStage2Scratch2,
            pStage2Scratch2,
            pStage2Scratch2_plusOne,
            pStage2Out,
            tfStageBasePtr,
            &pScatterOffset[8],
            numOfLines,
            pBlock64->pblock_stage_2
    );
    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_32inter_stage_2_vloops;
    execFuncCount++;

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE3_OVERFLOW)
    {
        vcop_fft_64_16ix32o_stage_3_overflow_init(
                pStage2Out,
                pStage3Scratch1,
                pStage3Scratch2,
                pStage3Out,
                &pScaleFactorOut[2],
                pStage3InterimBuf,
                numValidBits,
                numOfLines,
                pBlock64->pblock_stage_3
        );
        pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix32o_stage_3_overflow_vloops;
        execFuncCount++;
    }
    else {
        vcop_fft_64_16ix32o_stage_3_init(
                pStage2Out,
                pStage3Scratch1,
                pStage3Scratch2,
                pStage3Out,
                numOfLines,
                pBlock64->pblock_stage_3
        );
        pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix32o_stage_3_vloops;
        execFuncCount++;
    }

    return (uint32_t)0;
}


void vcop_fft_64_16i_32o_vloops(uint16_t pblock[])
{
    sVCOP_FFT_64_pBlock_t * pBlock64 = (sVCOP_FFT_64_pBlock_t *) pblock;

    pBlock64->execFunc[0](pBlock64->pblock_stage_1);
    pBlock64->execFunc[1](pBlock64->pblock_stage_2);
    pBlock64->execFunc[2](pBlock64->pblock_stage_3);

}
#endif

void vcop_fft_64_16i_32o(
        int16_t      pInputDataWBuf[],
        int16_t      pScratchIBufL[],
        int16_t      pScratchIBufH[],
        int16_t      twiddleFactorBuf[],
        uint16_t     pScatterOffset[],
        uint8_t      pScaleFactorOut[],
        uint8_t      numValidBits,
        uint16_t     pitch,
        uint16_t     scaleFactorArray[],
        uint16_t     numOfLines,
        uint8_t      enableInPlaceCompute,
        uint32_t     overflowMask,
        uint16_t     saturationLimit)
{
    int16_t * tfStageBasePtr = NULL;
    uint16_t scatterOffsetArray1[]={0 ,
                                    9 * 4 * 1,
                                    9 * 4 * 2,
                                    9 * 4 * 3,
                                    9 * 4 * 4,
                                    9 * 4 * 5,
                                    9 * 4 * 6,
                                    9 * 4 * 7};

    uint16_t scatterOffsetArray2[]={0 ,
                                    1 * 4 * 1,
                                    1 * 4 * 2,
                                    1 * 4 * 3,
                                    1 * 4 * 68,
                                    1 * 4 * 69,
                                    1 * 4 * 70,
                                    1 * 4 * 71};
    uint32_t N = 64U;
    int32_t * pStage2In;
    int16_t * pStage2Scratch1;
    int16_t * pStage2Scratch2;
    int16_t * pStage2Scratch1_plusOne;
    int16_t * pStage2Scratch2_plusOne;
    int32_t * pStage2Out;
    int32_t * pStage3Out;
    int32_t * pStage3Scratch1;
    int32_t * pStage3Scratch2;
    int16_t * pStage3InterimBuf;

    memcpy(pScatterOffset, scatterOffsetArray1, sizeof(scatterOffsetArray1));
    memcpy(&pScatterOffset[8], scatterOffsetArray2, sizeof(scatterOffsetArray2));

    tfStageBasePtr = &twiddleFactorBuf[0];

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_64_32inter_stage_1(&pInputDataWBuf[0],
                                (int32_t*)(void*)&pScratchIBufH[0],
                                (uint16_t*)(void *)&pScratchIBufH[0],
                                (int16_t*)(void *)&pScratchIBufH[1],
                                (int32_t*)(void *)&pInputDataWBuf[0],
                                (uint16_t*)(void *)&pInputDataWBuf[0],
                                (int16_t*)(void *)&pInputDataWBuf[1],
                                (int32_t*)(void*)&pScratchIBufL[0],
                                tfStageBasePtr,
                                pScatterOffset,
                                pitch,
                                numOfLines);


#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if _DUMP
    {
        int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

        numOfGrp    = 1;
        currentRadix= 4;
        numPoints= 64;

        numBFperGrp = numPoints / currentRadix;

        dumpIntoFile_32inter((int32_t*)(void*)&pScratchIBufL[0], 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 9);
    }
#endif

    tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];


    if ( enableInPlaceCompute == 1U )
    {
        pStage2In  = (int32_t*)(void*)&pScratchIBufL[0];
        pStage2Out = (int32_t*)(void*)&pScratchIBufH[0];
        pStage2Scratch1 = &pScratchIBufL[0];
        pStage2Scratch1_plusOne = &pScratchIBufL[1];
        pStage2Scratch2 = &pInputDataWBuf[0];
        pStage2Scratch2_plusOne = &pInputDataWBuf[1];
        pStage3Out = (int32_t*)(void*)&pInputDataWBuf[0];
        pStage3Scratch1 = (int32_t*)(void*)&pScratchIBufL[0];
        pStage3Scratch2 = (int32_t*)(void*)&pScratchIBufH[0];
        pStage3InterimBuf = (int16_t*)(void*)&pInputDataWBuf[0];

    }
    else
    {
        pStage2In  = (int32_t*)(void*)&pScratchIBufL[0];
        pStage2Out = (int32_t*)(void*)&pInputDataWBuf[0];
        pStage2Scratch1 = &pScratchIBufL[0];
        pStage2Scratch1_plusOne= &pScratchIBufL[1];
        pStage2Scratch2 = &pScratchIBufH[0];
        pStage2Scratch2_plusOne = &pScratchIBufH[1];
        pStage3Out = (int32_t*)(void*)&pScratchIBufH[0];
        pStage3Scratch1 = (int32_t*)(void*)&pScratchIBufL[0];
        pStage3Scratch2 = (int32_t*)(void*)&pInputDataWBuf[0];
        pStage3InterimBuf = (int16_t*)(void*)&pScratchIBufH[0];
    }

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    vcop_fft_64_32inter_stage_2
    (
            pStage2In,
            (int32_t*)(void*)pStage2Scratch1,
            (uint16_t*)(void*)pStage2Scratch1,
            (int16_t*)(void*)pStage2Scratch1_plusOne,
            (int32_t*)(void*)pStage2Scratch2,
            (uint16_t*)(void*)pStage2Scratch2,
            (int16_t*)(void*)pStage2Scratch2_plusOne,
            pStage2Out,
            tfStageBasePtr,
            &pScatterOffset[8],
            numOfLines
    );

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

    if (overflowMask & VCOP_FFT_NPT_16ix32o_STAGE3_OVERFLOW)
    {
        vcop_fft_64_16ix32o_stage_3_overflow(
                pStage2Out,
                pStage3Scratch1,
                pStage3Scratch2,
                pStage3Out,
                &pScaleFactorOut[2],
                pStage3InterimBuf,
                numValidBits,
                numOfLines
        );
    }
    else {
        vcop_fft_64_16ix32o_stage_3(
                pStage2Out,
                pStage3Scratch1,
                pStage3Scratch2,
                pStage3Out,
                numOfLines
        );
    }

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif


}

