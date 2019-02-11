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
/*     @file : vcop_fft_npt_16ix16o_wrapper.c                                 */
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
#include "vcop_fft_npt_16ix16o_wrapper.h"

#if (!VCOP_HOST_EMULATION)
#include "vcop_fft_1024_16ix16o_kernel.h"
#include "vcop_fft_1024_16ix16o_kernel_overflow.h"
#include "vcop_fft_512_16ix16o_kernel.h"
#include "vcop_fft_512_16ix16o_kernel_overflow.h"
#include "vcop_fft_256_16ix16o_kernel.h"
#include "vcop_fft_256_16ix16o_kernel_overflow.h"
#include "vcop_fft_128_16ix16o_kernel.h"
#include "vcop_fft_128_16ix16o_kernel_overflow.h"
#include "vcop_fft_64_16ix16o_kernel.h"
#include "vcop_fft_64_16ix16o_kernel_overflow.h"
#else
#include "vcop_fft_1024_16ix16o_kernel.k"
#include "vcop_fft_1024_16ix16o_kernel_overflow.k"
#include "vcop_fft_512_16ix16o_kernel.k"
#include "vcop_fft_512_16ix16o_kernel_overflow.k"
#include "vcop_fft_256_16ix16o_kernel.k"
#include "vcop_fft_256_16ix16o_kernel_overflow.k"
#include "vcop_fft_128_16ix16o_kernel.k"
#include "vcop_fft_128_16ix16o_kernel_overflow.k"
#include "vcop_fft_64_16ix16o_kernel.k"
#include "vcop_fft_64_16ix16o_kernel_overflow.k"
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
void dumpIntoFile(int16_t *pScratchIBufL, int32_t stageNo, int32_t numOfGrp, int32_t numBFperGrp, int32_t currentRadix, int32_t numOfLines, int32_t numPoints, int32_t overflowMask, int32_t transposeStride) {

          int32_t j, groupIdx, bfIdx, twIdx;
          FILE *fid;
          int16_t *basePtrGrp;
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
                            basePtrGrp    = pScratchIBufL + j*numOfGrp*numBFperGrp * currentRadix * 2 + groupIdx * numBFperGrp * currentRadix * 2;
                            for ( bfIdx = 0 ; bfIdx < 2*4*numBFperGrp; bfIdx++) {
                                fprintf(fid, "%06d ", *(basePtrGrp + bfIdx));
                                }
                          }
                          else {
                            if (numPoints== 64) {
                                basePtrGrp    = pScratchIBufL + (j/2)*2*transposeStride*numBFperGrp + groupIdx * 2 + (j%2)*4*2;
                                }
                            else if (numPoints== 1024 || numPoints== 512) {
                                basePtrGrp    = pScratchIBufL + j*2*transposeStride*numBFperGrp + (groupIdx%4)*2*4 + (groupIdx/4) * 2;
                                }
                            else {
                                basePtrGrp    = pScratchIBufL + j*2*transposeStride*numBFperGrp + groupIdx * 2;
                                }
                            for (twIdx= 0; twIdx < currentRadix; twIdx++) {
                                for ( bfIdx = 0 ; bfIdx < numBFperGrp; bfIdx++) {
                                    fprintf(fid, "%06d ", *(basePtrGrp + twIdx*numOfGrp*2 + bfIdx*transposeStride*2));
                                    fprintf(fid, "%06d ", *(basePtrGrp + twIdx*numOfGrp*2 + bfIdx*transposeStride*2 + 1));
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

uint32_t vcop_fft_1024_16i_16o_param_count(void)
{
  uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
  uint32_t pBlockCount1;
  uint32_t pBlockCount2;
#if (!VCOP_HOST_EMULATION)
  pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_1024_pBlock_t)), 4U) +
               vcop_fft_1024_16ix16o_stage_1_param_count() +
               vcop_fft_1024_16ix16o_stage_2_param_count() +
               vcop_fft_1024_16ix16o_stage_3_param_count() +
               vcop_fft_1024_16ix16o_stage_4_param_count() +
               vcop_fft_1024_16ix16o_stage_5_param_count();

  pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_1024_pBlock_t)), 4U) +
                vcop_fft_1024_16ix16o_stage_1_overflow_param_count() +
                vcop_fft_1024_16ix16o_stage_2_overflow_param_count() +
                vcop_fft_1024_16ix16o_stage_3_overflow_param_count() +
                vcop_fft_1024_16ix16o_stage_4_overflow_param_count() +
                vcop_fft_1024_16ix16o_stage_5_overflow_param_count();
  pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif


  return pBlockCount;

}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_1024_16i_16o_init(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  uint32_t N = 1024U;
  uint16_t scatterOffsetArray[]={0 ,
                            65 * 4 * 1,
                            65 * 4 * 2,
                            65 * 4 * 3,
                            65 * 4 * 4,
                            65 * 4 * 5,
                            65 * 4 * 6,
                            65 * 4 * 7};
  int16_t * pStage5In;
  int16_t * pStage5Out;
  uint32_t execFuncCount = 0;


  sVCOP_FFT_1024_pBlock_t * pBlock1024 = (sVCOP_FFT_1024_pBlock_t *) (void *)pblock;

  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  pBlock1024->pblock_stage_1 = (uint16_t *)pBlock1024 + (ALIGN(sizeof(sVCOP_FFT_1024_pBlock_t), 4U)/ sizeof(uint16_t));
  pBlock1024->pblock_stage_2   = (uint16_t *)pBlock1024->pblock_stage_1 + vcop_fft_1024_16ix16o_stage_1_overflow_param_count();
  pBlock1024->pblock_stage_3   = (uint16_t *)pBlock1024->pblock_stage_2 + vcop_fft_1024_16ix16o_stage_2_overflow_param_count();
  pBlock1024->pblock_stage_4   = (uint16_t *)pBlock1024->pblock_stage_3 + vcop_fft_1024_16ix16o_stage_3_overflow_param_count();
  pBlock1024->pblock_stage_5   = (uint16_t *)pBlock1024->pblock_stage_4 + vcop_fft_1024_16ix16o_stage_4_overflow_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  tfStageBasePtr = &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_1024_16ix16o_stage_1_overflow_init
     (
       pInputDataWBuf,
       (int32_t*)(void *)pScratchIBufL,
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pScaleFactorOut,
       numValidBits,
       pitch,
       numOfLines,
       scaleFactorArray[0],
       saturationLimit,
       pBlock1024->pblock_stage_1
     );
    pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_1_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_1024_16ix16o_stage_1_init
     (
       pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pitch,
       numOfLines,
       scaleFactorArray[0],
       saturationLimit,
       pBlock1024->pblock_stage_1
     );
    pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_1_vloops;
    execFuncCount++;
  }

  tfStageBasePtr = &twiddleFactorBuf[(N/4U )* 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
      vcop_fft_1024_16ix16o_stage_2_overflow_init
     (
       pScratchIBufL,
       (int32_t*)(void *)pScratchIBufL,
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       &pScaleFactorOut[1],
       numValidBits,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[1],
       saturationLimit,
       pBlock1024->pblock_stage_2
     );

    pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_2_overflow_vloops;
    execFuncCount++;
  }
  else
  {
     vcop_fft_1024_16ix16o_stage_2_init
     (
       pScratchIBufL,
       pScratchIBufL,
       tfStageBasePtr,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[1],
       saturationLimit,
       pBlock1024->pblock_stage_2
     );

     pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_2_vloops;
     execFuncCount++;
  }
   tfStageBasePtr = &twiddleFactorBuf[((N/4U) + (N/16U)  )* 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)
  {
    vcop_fft_1024_16ix16o_stage_3_overflow_init
    (
      pScratchIBufL,
      (int32_t*)(void *)pScratchIBufL,
      (int32_t*)(void *)pScratchIBufH,
      (int32_t*)(void *)pInputDataWBuf,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      &pScaleFactorOut[2],
      numValidBits,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[2],
      saturationLimit,
      pBlock1024->pblock_stage_3
    );

    pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_3_overflow_vloops;
    execFuncCount++;
  }
  else
  {
     vcop_fft_1024_16ix16o_stage_3_init
     (
       pScratchIBufL,
       pInputDataWBuf,
       tfStageBasePtr,
       pScatterOffset,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[2],
       saturationLimit,
       pBlock1024->pblock_stage_3
     );

     pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_3_vloops;
     execFuncCount++;
  }

    if ( enableInPlaceCompute == 1U )
   {
      pStage5Out = pInputDataWBuf;
   }
   else
   {
     pStage5Out = pScratchIBufH;
   }
   tfStageBasePtr = &twiddleFactorBuf[((N/4U) + (N/16U) + (N/64U) )* 3U * 2U];

  /* If stage 5 is in overflow mode then we force stage 4 also to be in overflow mode */
  if (((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW) != 0) ||
    ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW) != 0) )
  {
     vcop_fft_1024_16ix16o_stage_4_overflow_init(
       pInputDataWBuf,/*Leg 0 */
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pScratchIBufL,
       pInputDataWBuf,
       tfStageBasePtr,
       &pScaleFactorOut[3],
       numValidBits,
       numOfLines,
       scaleFactorArray[3],
       saturationLimit,
       pBlock1024->pblock_stage_4
     );
     pStage5In = pInputDataWBuf;

     pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_4_overflow_vloops;
     execFuncCount++;
  }
  else
  {
     vcop_fft_1024_16ix16o_stage_4_init(
       pInputDataWBuf,/*Leg 0 */
       pScratchIBufL,
       tfStageBasePtr,
       numOfLines,
       scaleFactorArray[3],
       saturationLimit,
       pBlock1024->pblock_stage_4
     );
     pStage5In = pScratchIBufL;

     pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_4_vloops;
     execFuncCount++;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW)
  {
    vcop_fft_1024_16ix16o_stage_5_overflow_init
    (
     pStage5In,
     (int32_t*)(void *)pScratchIBufL,
     (int32_t*)(void *)pScratchIBufH,
     pStage5Out,
     &pScaleFactorOut[4],
     numValidBits,
     numOfLines,
     scaleFactorArray[4],
     saturationLimit,
     pBlock1024->pblock_stage_5
    );

    pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_5_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_1024_16ix16o_stage_5_init(
     pStage5In,
     pStage5Out,
     numOfLines,
     scaleFactorArray[4],
     saturationLimit,
     pBlock1024->pblock_stage_5
    );

    pBlock1024->execFunc[execFuncCount] = &vcop_fft_1024_16ix16o_stage_5_vloops;
    execFuncCount++;
  }

  return (uint32_t)0;
}


void vcop_fft_1024_16i_16o_vloops(uint16_t pblock[])
{
  sVCOP_FFT_1024_pBlock_t * pBlock1024 = (sVCOP_FFT_1024_pBlock_t *) pblock;

  pBlock1024->execFunc[0](pBlock1024->pblock_stage_1);
  pBlock1024->execFunc[1](pBlock1024->pblock_stage_2);
  pBlock1024->execFunc[2](pBlock1024->pblock_stage_3);
  pBlock1024->execFunc[3](pBlock1024->pblock_stage_4);
  pBlock1024->execFunc[4](pBlock1024->pblock_stage_5);

}
#endif

void vcop_fft_1024_16i_16o(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  uint32_t N = 1024U;
  uint16_t scatterOffsetArray[]={0 ,
                            65 * 4 * 1,
                            65 * 4 * 2,
                            65 * 4 * 3,
                            65 * 4 * 4,
                            65 * 4 * 5,
                            65 * 4 * 6,
                            65 * 4 * 7};
  int16_t * pStage5Out;

  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  tfStageBasePtr = (int16_t *)&twiddleFactorBuf[0];

#if INDIVIDUAL_PROFILING
  profiler_start();
#endif

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_1024_16ix16o_stage_1_overflow
     (
       pInputDataWBuf,
       (int32_t*)(void *)pScratchIBufL,
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pScaleFactorOut,
       numValidBits,
       pitch,
       numOfLines,
       scaleFactorArray[0],
       saturationLimit
     );
  }
  else
  {
    vcop_fft_1024_16ix16o_stage_1
     (
       pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pitch,
       numOfLines,
       scaleFactorArray[0],
       saturationLimit
     );
  }

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
    profiler_start();
#endif

#if _DUMP
  {
  int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

  numOfGrp    = 1;
  currentRadix= 4;
  numPoints= 1024;

  numBFperGrp = numPoints / currentRadix;

  dumpIntoFile(pScratchIBufL, 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0); 
  }
#endif

  tfStageBasePtr = &twiddleFactorBuf[(N/4U )* 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
      vcop_fft_1024_16ix16o_stage_2_overflow
     (
       pScratchIBufL,
       (int32_t*)(void *)pScratchIBufL,
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       &pScaleFactorOut[1],
       numValidBits,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[1],
       saturationLimit
     );
  }
  else
  {
     vcop_fft_1024_16ix16o_stage_2
     (
       pScratchIBufL,
       pScratchIBufL,
       tfStageBasePtr,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[1],
       saturationLimit
     );
  }
#if INDIVIDUAL_PROFILING
  profiler_end_print(1);
  profiler_start();
#endif

#if _DUMP
  {
  int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

  currentRadix= 4;
  numPoints= 1024;

  numBFperGrp = numPoints / (4*currentRadix);
  numOfGrp= currentRadix;

  dumpIntoFile(pScratchIBufL, 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0); 
  }
#endif

  tfStageBasePtr = &twiddleFactorBuf[((N/4U) + (N/16U)  )* 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)
  {
    vcop_fft_1024_16ix16o_stage_3_overflow
    (
      pScratchIBufL,
      (int32_t*)(void *)pScratchIBufL,
      (int32_t*)(void *)pScratchIBufH,
      (int32_t*)(void *)pInputDataWBuf,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      &pScaleFactorOut[2],
      numValidBits,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[2],
      saturationLimit
    );
  }
  else
  {
     vcop_fft_1024_16ix16o_stage_3
     (
       pScratchIBufL,
       pInputDataWBuf,
       tfStageBasePtr,
       pScatterOffset,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[2],
       saturationLimit
     );
  }
#if INDIVIDUAL_PROFILING
  profiler_end_print(1);
  profiler_start();
#endif

#if _DUMP
    {
    int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;

    currentRadix= 4;
    numPoints= 1024;

    numBFperGrp = numPoints / (4*4*currentRadix);
    numOfGrp= 4*currentRadix;

    dumpIntoFile(pInputDataWBuf, 3, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 65); 
    }
#endif

   if ( enableInPlaceCompute == 1U )
   {
      pStage5Out = pInputDataWBuf;
   }
   else
   {
     pStage5Out = pScratchIBufH;
   }


  tfStageBasePtr = &twiddleFactorBuf[((N/4U) + (N/16U) + (N/64U) )* 3U * 2U];

  /* If stage 5 is in overflow mode then we force stage 4 also to be in overflow mode */
  if (( (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW) != 0) ||
    ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW) != 0 ) )
  {
     vcop_fft_1024_16ix16o_stage_4_overflow(
       pInputDataWBuf,/*Leg 0 */
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pScratchIBufL,
       pInputDataWBuf,
       tfStageBasePtr,
       &pScaleFactorOut[3],
       numValidBits,
       numOfLines,
       scaleFactorArray[3],
       saturationLimit
     );
  }
  else
  {
     vcop_fft_1024_16ix16o_stage_4(
       pInputDataWBuf,/*Leg 0 */
       pScratchIBufL,
       tfStageBasePtr,
       numOfLines,
       scaleFactorArray[3],
       saturationLimit
     );
  }
#if INDIVIDUAL_PROFILING
  profiler_end_print(1);
  profiler_start();
#endif

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW)
  {
    vcop_fft_1024_16ix16o_stage_5_overflow(
     pInputDataWBuf,
     (int32_t*)(void *)pScratchIBufL,
     (int32_t*)(void *)pScratchIBufH,
     pStage5Out,
     &pScaleFactorOut[4],
     numValidBits,
     numOfLines,
     scaleFactorArray[4],
     saturationLimit
    );
  }
  else
  {
    vcop_fft_1024_16ix16o_stage_5(
     pScratchIBufL,
     pStage5Out,
     numOfLines,
     scaleFactorArray[4],
     saturationLimit
    );
  }
#if INDIVIDUAL_PROFILING
  profiler_end_print(1);
#endif



}



uint32_t vcop_fft_512_16i_16o_param_count(void)
{
  uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
  uint32_t pBlockCount1;
  uint32_t pBlockCount2;
#if (!VCOP_HOST_EMULATION)
    pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_512_pBlock_t)), 4U) +
                 vcop_fft_512_16ix16o_stage_1_param_count() +
                 vcop_fft_512_16ix16o_stage_2_param_count() +
                 vcop_fft_512_16ix16o_stage_3_param_count() +
                 vcop_fft_512_16ix16o_stage_4_param_count() +
                 vcop_fft_512_16ix16o_radix2_stage_5_param_count();

    pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_512_pBlock_t)), 4U) +
                  vcop_fft_512_16ix16o_stage_1_overflow_param_count() +
                  vcop_fft_512_16ix16o_stage_2_overflow_param_count() +
                  vcop_fft_512_16ix16o_stage_3_overflow_param_count() +
                  vcop_fft_512_16ix16o_stage_4_overflow_param_count() +
                  vcop_fft_512_16ix16o_radix2_stage_5_overflow_param_count();
    pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif

  return pBlockCount;
}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_512_16i_16o_init(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage5Out;
  uint32_t execFuncCount = 0;


  sVCOP_FFT_512_pBlock_t * pBlock512 = (sVCOP_FFT_512_pBlock_t *)(void *) pblock;

  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  pBlock512->pblock_stage_1 = (uint16_t *)pBlock512 + (ALIGN(sizeof(sVCOP_FFT_512_pBlock_t), 4U)/ sizeof(uint16_t));
  pBlock512->pblock_stage_2   = (uint16_t *)pBlock512->pblock_stage_1 + vcop_fft_512_16ix16o_stage_1_overflow_param_count();
  pBlock512->pblock_stage_3   = (uint16_t *)pBlock512->pblock_stage_2 + vcop_fft_512_16ix16o_stage_2_overflow_param_count();
  pBlock512->pblock_stage_4   = (uint16_t *)pBlock512->pblock_stage_3 + vcop_fft_512_16ix16o_stage_3_overflow_param_count();
  pBlock512->pblock_stage_5   = (uint16_t *)pBlock512->pblock_stage_4 + vcop_fft_512_16ix16o_stage_4_overflow_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_512_16ix16o_stage_1_overflow_init(
          pInputDataWBuf,
          (int32_t*)(void *)pInputDataWBuf,
          (int32_t*)(void *)pScratchIBufH,
          pScratchIBufL,
          &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )],
          pScaleFactorOut,
          numValidBits,
          pitch,
          numOfLines,
          scaleFactorArray[0],
          saturationLimit,
          pBlock512->pblock_stage_1
        );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_1_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_512_16ix16o_stage_1_init(
          pInputDataWBuf,
          pScratchIBufL,
          &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )],
          pitch,
          numOfLines,
          scaleFactorArray[0],
          saturationLimit,
          pBlock512->pblock_stage_1
        );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_1_vloops;
    execFuncCount++;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
    vcop_fft_512_16ix16o_stage_2_overflow_init(
      pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      (int32_t *)(void *)pInputDataWBuf,
      pScratchIBufL,
      (int16_t *)&twiddleFactorBuf[(N/4U) * 3U * 2U],
      &pScaleFactorOut[1],
      numValidBits,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit,
      pBlock512->pblock_stage_2
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_2_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_512_16ix16o_stage_2_init(
      pScratchIBufL,
      pScratchIBufL,
      (int16_t *)&twiddleFactorBuf[(N/4U) * 3U * 2U],
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit,
      pBlock512->pblock_stage_2
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_2_vloops;
    execFuncCount++;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)
  {
    vcop_fft_512_16ix16o_stage_3_overflow_init
    (
           pScratchIBufL,
          (int32_t *)(void *)pScratchIBufL,
          (int32_t *)(void *)pScratchIBufH,
          pInputDataWBuf,
          &twiddleFactorBuf[ ((N/4U) + (N/16U)) * 3U * 2U],
          pScatterOffset,
          &pScaleFactorOut[2],
          numValidBits,
          (uint16_t)(N * sizeof(int16_t) * 2U),
          numOfLines,
          scaleFactorArray[2]/* Scale*/,
          saturationLimit,
          pBlock512->pblock_stage_3
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_3_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_512_16ix16o_stage_3_init
    (
          pScratchIBufL,
          pInputDataWBuf,
          &twiddleFactorBuf[ ((N/4U) + (N/16U)) * 3U * 2U],
          pScatterOffset,
          (uint16_t)(N * sizeof(int16_t) * 2U),
          numOfLines,
          scaleFactorArray[2],
          saturationLimit,
          pBlock512->pblock_stage_3
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_3_vloops;
    execFuncCount++;
  }

  if ( enableInPlaceCompute == 1U )
  {
    pStage5Out = pInputDataWBuf;
  }
  else
  {
    pStage5Out = pScratchIBufH;
  }

  /* If stage 5 is in overflow mode then we force stage 4 also to be in overflow mode */
  if ( ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW) != 0) ||
      ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW)!= 0) )
  {
     vcop_fft_512_16ix16o_stage_4_overflow_init
    (
          pInputDataWBuf,
          (int32_t *)(void *)pScratchIBufL,
          (int32_t *)(void *)pScratchIBufH,
          pInputDataWBuf,
          &twiddleFactorBuf[ ((N/4U) + (N/16U) + ((N/64U) * 4U)) * 3U * 2U],
          &pScaleFactorOut[3],
          numValidBits,
          numOfLines,
          scaleFactorArray[3]/* Scale*/,
          saturationLimit,
          pBlock512->pblock_stage_4
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_4_overflow_vloops;
    execFuncCount++;
  }
  else
  {

    vcop_fft_512_16ix16o_stage_4_init
    (
          pInputDataWBuf,
          pScratchIBufL,
          &twiddleFactorBuf[ ((N/4U) + (N/16U) + ((N/64U) * 4U)) * 3U * 2U],
          numOfLines,
          scaleFactorArray[3],
          saturationLimit,
          pBlock512->pblock_stage_4
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_stage_4_vloops;
    execFuncCount++;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW)
  {
    vcop_fft_512_16ix16o_radix2_stage_5_overflow_init(
        pInputDataWBuf,
        (int32_t *)(void *)pScratchIBufL,
        (int32_t *)(void *)pScratchIBufH,
        pStage5Out,
        &pScaleFactorOut[4],
        numValidBits,
        numOfLines,
        scaleFactorArray[4],
        saturationLimit,
      pBlock512->pblock_stage_5
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_radix2_stage_5_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_512_16ix16o_radix2_stage_5_init(
      pScratchIBufL,
      pStage5Out,
      numOfLines,
      scaleFactorArray[4],
      saturationLimit,
      pBlock512->pblock_stage_5
    );
    pBlock512->execFunc[execFuncCount] = &vcop_fft_512_16ix16o_radix2_stage_5_vloops;
    execFuncCount++;
  }
  return (uint32_t)0;
}


void vcop_fft_512_16i_16o_vloops(uint16_t pblock[])
{
  sVCOP_FFT_512_pBlock_t * pBlock512 = (sVCOP_FFT_512_pBlock_t *) pblock;

  pBlock512->execFunc[0](pBlock512->pblock_stage_1);
  pBlock512->execFunc[1](pBlock512->pblock_stage_2);
  pBlock512->execFunc[2](pBlock512->pblock_stage_3);
  pBlock512->execFunc[3](pBlock512->pblock_stage_4);
  pBlock512->execFunc[4](pBlock512->pblock_stage_5);

}
#endif

void vcop_fft_512_16i_16o(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage5Out;

  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

#if INDIVIDUAL_PROFILING
      profiler_start();
#endif

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_512_16ix16o_stage_1_overflow(
          pInputDataWBuf,
          (int32_t*)(void *)pInputDataWBuf,
          (int32_t*)(void *)pScratchIBufH,
          pScratchIBufL,
          &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )],
          pScaleFactorOut,
          numValidBits,
          pitch,
          numOfLines,
          scaleFactorArray[0],
          saturationLimit
        );
  }
  else
  {
    vcop_fft_512_16ix16o_stage_1(
          pInputDataWBuf,
          pScratchIBufL,
          &twiddleFactorBuf[2U * (VCOP_SIMD_WIDTH * 0 )],
          pitch,
          numOfLines,
          scaleFactorArray[0],
          saturationLimit
        );
  }
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

  dumpIntoFile(pScratchIBufL, 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0); 
  }
#endif

#if INDIVIDUAL_PROFILING
      profiler_start();
#endif

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
    vcop_fft_512_16ix16o_stage_2_overflow(
      pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      (int32_t *)(void *)pInputDataWBuf,
      pScratchIBufL,
      (int16_t *)&twiddleFactorBuf[(N/4U) * 3U * 2U],
      &pScaleFactorOut[1],
      numValidBits,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit
    );
  }
  else
  {
    vcop_fft_512_16ix16o_stage_2(
      pScratchIBufL,
      pScratchIBufL,
      (int16_t *)&twiddleFactorBuf[(N/4U) * 3U * 2U],
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit
    );
  }

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

  dumpIntoFile(pScratchIBufL, 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0); 
  }
#endif


#if INDIVIDUAL_PROFILING
    profiler_start();
#endif

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)
  {
    vcop_fft_512_16ix16o_stage_3_overflow
    (
          pScratchIBufL,
          (int32_t *)(void *)pScratchIBufL,
          (int32_t *)(void *)pScratchIBufH,
          pInputDataWBuf,
          &twiddleFactorBuf[ ((N/4U) + (N/16U)) * 3U * 2U],
          pScatterOffset,
          &pScaleFactorOut[2],
          numValidBits,
          (uint16_t)(N * sizeof(int16_t) * 2U),
          numOfLines,
          scaleFactorArray[2]/* Scale*/,
          saturationLimit
    );
  }
  else
  {
    vcop_fft_512_16ix16o_stage_3
    (
          pScratchIBufL,
          pInputDataWBuf,
          &twiddleFactorBuf[ ((N/4U) + (N/16U)) * 3U * 2U],
          pScatterOffset,
          (uint16_t)(N * sizeof(int16_t) * 2U),
          numOfLines,
          scaleFactorArray[2]/* Scale*/,
          saturationLimit
    );
  }

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

    dumpIntoFile(pInputDataWBuf, 3, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 65); 
    }
#endif

  if ( enableInPlaceCompute == 1U )
  {
    pStage5Out = pInputDataWBuf;
  }
  else
  {
    pStage5Out = pScratchIBufH;
  }

#if INDIVIDUAL_PROFILING
  profiler_start();
#endif
   /* If stage 5 is in overflow mode then we force stage 4 also to be in overflow mode */
  if (((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW)!= 0 ) ||
      ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW) != 0 ))
  {
     vcop_fft_512_16ix16o_stage_4_overflow
    (
          pInputDataWBuf,
          (int32_t *)(void *)pScratchIBufL,
          (int32_t *)(void *)pScratchIBufH,
          pInputDataWBuf,
          &twiddleFactorBuf[ ((N/4U) + (N/16U) + ((N/64U) * 4U)) * 3U * 2U],
          &pScaleFactorOut[3],
          numValidBits,
          numOfLines,
          scaleFactorArray[3]/* Scale*/,
          saturationLimit
    );
  }
  else
  {

    vcop_fft_512_16ix16o_stage_4
    (
          pInputDataWBuf,
          pScratchIBufL,
          &twiddleFactorBuf[ ((N/4U) + (N/16U) + ((N/64U) * 4U)) * 3U * 2U],
          numOfLines,
          scaleFactorArray[3]/* Scale*/,
          saturationLimit
    );
  }

#if INDIVIDUAL_PROFILING
    profiler_end_print(1);
#endif

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif
    if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE5_OVERFLOW)
    {
      vcop_fft_512_16ix16o_radix2_stage_5_overflow(
        pInputDataWBuf,
        (int32_t *)(void *)pScratchIBufL,
        (int32_t *)(void *)pScratchIBufH,
        pStage5Out,
        &pScaleFactorOut[4],
        numValidBits,
        numOfLines,
        scaleFactorArray[4],
        saturationLimit
      );
    }
    else
    {
      vcop_fft_512_16ix16o_radix2_stage_5(
        pScratchIBufL,
        pStage5Out,
        numOfLines,
        scaleFactorArray[4],
        saturationLimit
      );
    }
#if INDIVIDUAL_PROFILING
        profiler_end_print(1);
#endif

}


uint32_t vcop_fft_128_16i_16o_param_count(void)
{
  uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
  uint32_t pBlockCount1;
  uint32_t pBlockCount2;
#if (!VCOP_HOST_EMULATION)
  pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_128_pBlock_t)), 4U) +
               vcop_fft_128_16ix16o_stage_1_param_count() +
               vcop_fft_128_16ix16o_stage_2_param_count() +
               vcop_fft_128_16ix16o_stage_3_param_count() +
               vcop_fft_128_16ix16o_radix2_stage_4_param_count();

  pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_128_pBlock_t)), 4U) +
                vcop_fft_128_16ix16o_stage_1_overflow_param_count() +
                vcop_fft_128_16ix16o_stage_2_overflow_param_count() +
                vcop_fft_128_16ix16o_stage_3_overflow_param_count() +
                vcop_fft_128_16ix16o_radix2_stage_4_overflow_param_count();

  pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif

  return pBlockCount;

}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_128_16i_16o_init(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage4Out;
  uint32_t  execFuncCount = 0;
  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  tfStageBasePtr = &twiddleFactorBuf[0];
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  pBlock128->pblock_stage_1   = (uint16_t *)pBlock128 + (ALIGN(sizeof(sVCOP_FFT_128_pBlock_t), 4U)/ sizeof(uint16_t));

  /* Overflow detection param counts are always higher hence use the worst case number */
  pBlock128->pblock_stage_2   = (uint16_t *)pBlock128->pblock_stage_1 + vcop_fft_128_16ix16o_stage_1_overflow_param_count();
  pBlock128->pblock_stage_3   = (uint16_t *)pBlock128->pblock_stage_2 + vcop_fft_128_16ix16o_stage_2_overflow_param_count();
  pBlock128->pblock_stage_4   = (uint16_t *)pBlock128->pblock_stage_3 + vcop_fft_128_16ix16o_stage_3_overflow_param_count();

  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_128_16ix16o_stage_1_overflow_init
       (
         pInputDataWBuf,
        (int32_t *)(void *)pInputDataWBuf,
        (int32_t *)(void *)pScratchIBufH,
        pScratchIBufL,
        tfStageBasePtr,
        pScaleFactorOut,
        numValidBits,
        pitch,
        numOfLines,
        scaleFactorArray[0],
        saturationLimit,
         pBlock128->pblock_stage_1
       );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_stage_1_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_128_16ix16o_stage_1_init
       (
         pInputDataWBuf,
         pScratchIBufL,
         tfStageBasePtr,
         pitch,
         numOfLines,
         scaleFactorArray[0],
         saturationLimit,
         pBlock128->pblock_stage_1
       );

    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_stage_1_vloops;
    execFuncCount++;
  }

   tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
     vcop_fft_128_16ix16o_stage_2_overflow_init
     (
       pScratchIBufL,
       (int32_t *)(void *)pScratchIBufL,
       (int32_t *)(void *)pScratchIBufH,
       pInputDataWBuf,
       tfStageBasePtr,
       pScatterOffset,
       &pScaleFactorOut[1],
       numValidBits,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[1],
       saturationLimit,
       pBlock128->pblock_stage_2
     );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_stage_2_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_128_16ix16o_stage_2_init
    (
      pScratchIBufL,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit,
      pBlock128->pblock_stage_2
    );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_stage_2_vloops;
    execFuncCount++;
  }

   tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (4U * (N/16U))) * 3U * 2U];

  if ( enableInPlaceCompute == 1U )
  {
    pStage4Out = pInputDataWBuf;
  }
  else
  {
    pStage4Out = pScratchIBufH;
  }

  if (((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW) != 0) ||
    ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW) != 0))
  {
     vcop_fft_128_16ix16o_stage_3_overflow_init(
      pInputDataWBuf,/*Leg 0 */
       (int32_t *)(void *)pScratchIBufL,
       (int32_t *)(void *)pScratchIBufH,
      pInputDataWBuf,
      tfStageBasePtr,
      &pScaleFactorOut[2],
      numValidBits,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit,
      pBlock128->pblock_stage_3
      );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_stage_3_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_128_16ix16o_stage_3_init(
      pInputDataWBuf,/*Leg 0 */
      pScratchIBufL,
      tfStageBasePtr,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit,
      pBlock128->pblock_stage_3
      );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_stage_3_vloops;
    execFuncCount++;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW)
  {
    vcop_fft_128_16ix16o_radix2_stage_4_overflow_init(
      pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pStage4Out,
      &pScaleFactorOut[3],
      numValidBits,
      numOfLines,
      scaleFactorArray[3],
      saturationLimit,
      pBlock128->pblock_stage_4
    );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_radix2_stage_4_overflow_vloops;
    execFuncCount++;
  }
  else
  {
     vcop_fft_128_16ix16o_radix2_stage_4_init(
       pScratchIBufL,
       pStage4Out,
       numOfLines,
       scaleFactorArray[3],
       saturationLimit,
       pBlock128->pblock_stage_4
     );
    pBlock128->execFunc[execFuncCount] = &vcop_fft_128_16ix16o_radix2_stage_4_vloops;
    execFuncCount++;
  }
   return (uint32_t)0;
}


void vcop_fft_128_16i_16o_vloops(uint16_t pblock[])
{
  sVCOP_FFT_128_pBlock_t * pBlock128 = (sVCOP_FFT_128_pBlock_t *) pblock;

  pBlock128->execFunc[0](pBlock128->pblock_stage_1);
  pBlock128->execFunc[1](pBlock128->pblock_stage_2);
  pBlock128->execFunc[2](pBlock128->pblock_stage_3);
  pBlock128->execFunc[3](pBlock128->pblock_stage_4);

}
#endif

void vcop_fft_128_16i_16o(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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

  int16_t * pStage4Out;
  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  tfStageBasePtr = &twiddleFactorBuf[0];

  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_128_16ix16o_stage_1_overflow
    (
      pInputDataWBuf,
      (int32_t *)(void *)pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufH,
      pScratchIBufL,
      tfStageBasePtr,
      pScaleFactorOut,
      numValidBits,
      pitch,
      numOfLines,
      scaleFactorArray[0],
      saturationLimit
    );
  }
  else
  {
    vcop_fft_128_16ix16o_stage_1
       (
         pInputDataWBuf,
         pScratchIBufL,
         tfStageBasePtr,
         pitch,
         numOfLines,
         scaleFactorArray[0],
         saturationLimit
       );
  }

#if _DUMP
       {
       int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;
   
       numOfGrp    = 1;
       currentRadix= 4;
       numPoints= 128;
   
       numBFperGrp = numPoints / currentRadix;
   
       dumpIntoFile(pScratchIBufL, 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0); 
       }
#endif

   tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
     vcop_fft_128_16ix16o_stage_2_overflow
     (
       pScratchIBufL,
       (int32_t *)(void *)pScratchIBufL,
       (int32_t *)(void *)pScratchIBufH,
       pInputDataWBuf,
       tfStageBasePtr,
       pScatterOffset,
       &pScaleFactorOut[1],
       numValidBits,
       (uint16_t)(N * sizeof(int16_t) * 2U),
       numOfLines,
       scaleFactorArray[1],
       saturationLimit
     );
  }
  else
  {
    vcop_fft_128_16ix16o_stage_2
    (
      pScratchIBufL,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit
    );
  }

#if _DUMP
       {
       int32_t numBFperGrp, numOfGrp,  currentRadix, numPoints;
   
       currentRadix= 4;
       numPoints= 128;
   
       numBFperGrp = numPoints / (4*currentRadix);
       numOfGrp= currentRadix;
   
       dumpIntoFile(pInputDataWBuf, 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 17); 
       }
#endif

   tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (4U * (N/16U))) * 3U * 2U];

  if ( enableInPlaceCompute == 1U )
  {
    pStage4Out = pInputDataWBuf;
  }
  else
  {
    pStage4Out = pScratchIBufH;
  }

  if (((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW) != 0 ) ||
    ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW) != 0))
  {
     vcop_fft_128_16ix16o_stage_3_overflow(
      pInputDataWBuf,/*Leg 0 */
       (int32_t *)(void *)pScratchIBufL,
       (int32_t *)(void *)pScratchIBufH,
      pInputDataWBuf,
      tfStageBasePtr,
      &pScaleFactorOut[2],
      numValidBits,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit
      );

  }
  else
  {
    vcop_fft_128_16ix16o_stage_3(
      pInputDataWBuf,/*Leg 0 */
      pScratchIBufL,
      tfStageBasePtr,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit
      );
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW)
  {
    vcop_fft_128_16ix16o_radix2_stage_4_overflow(
      pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pStage4Out,
      &pScaleFactorOut[3],
      numValidBits,
      numOfLines,
      scaleFactorArray[3],
      saturationLimit
    );
  }
  else
  {
     vcop_fft_128_16ix16o_radix2_stage_4(
       pScratchIBufL,
       pStage4Out,
       numOfLines,
       scaleFactorArray[3],
      saturationLimit
     );
  }

}


uint32_t vcop_fft_256_16i_16o_param_count(void)
{
  uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
  uint32_t pBlockCount1;
  uint32_t pBlockCount2;
#if (!VCOP_HOST_EMULATION)
  pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_256_pBlock_t)), 4U) +
               vcop_fft_256_16ix16o_stage_1_param_count() +
               vcop_fft_256_16ix16o_stage_2_param_count() +
               vcop_fft_256_16ix16o_stage_3_param_count() +
               vcop_fft_256_16ix16o_stage_4_param_count();

  pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_256_pBlock_t)), 4U) +
                vcop_fft_256_16ix16o_stage_1_overflow_param_count() +
                vcop_fft_256_16ix16o_stage_2_overflow_param_count() +
                vcop_fft_256_16ix16o_stage_3_overflow_param_count() +
                vcop_fft_256_16ix16o_stage_4_overflow_param_count();

  pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif

  return pBlockCount;
}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_256_16i_16o_init(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage4Out;
  uint32_t  execFuncCount = 0;

  sVCOP_FFT_256_pBlock_t * pBlock256 = (sVCOP_FFT_256_pBlock_t *)(void *) pblock;

  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  tfStageBasePtr = &twiddleFactorBuf[0];

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual kernel which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  pBlock256->pblock_stage_1   = (uint16_t *)pBlock256 + (ALIGN(sizeof(sVCOP_FFT_256_pBlock_t), 4U)/ sizeof(uint16_t));
  pBlock256->pblock_stage_2   = (uint16_t *)pBlock256->pblock_stage_1 + vcop_fft_256_16ix16o_stage_1_overflow_param_count();
  pBlock256->pblock_stage_3   = (uint16_t *)pBlock256->pblock_stage_2 + vcop_fft_256_16ix16o_stage_2_overflow_param_count();
  pBlock256->pblock_stage_4   = (uint16_t *)pBlock256->pblock_stage_3 + vcop_fft_256_16ix16o_stage_3_overflow_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_256_16ix16o_stage_1_overflow_init
    (
      pInputDataWBuf,
      (int32_t *)(void *)pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufH,
      pScratchIBufL,
      tfStageBasePtr,
      pScaleFactorOut,
      numValidBits,
      pitch,
      numOfLines,
      scaleFactorArray[0],
      saturationLimit,
      pBlock256->pblock_stage_1
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_1_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_256_16ix16o_stage_1_init
    (
      pInputDataWBuf,
      pScratchIBufL,
      tfStageBasePtr,
      pitch,
      numOfLines,
      scaleFactorArray[0],
      saturationLimit,
      pBlock256->pblock_stage_1
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_1_vloops;
    execFuncCount++;
  }

   tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
     vcop_fft_256_16ix16o_stage_2_overflow_init
    (
      pScratchIBufL,
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      &pScaleFactorOut[1],
      numValidBits,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit,
      pBlock256->pblock_stage_2
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_2_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_256_16ix16o_stage_2_init
    (
      pScratchIBufL,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit,
      pBlock256->pblock_stage_2
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_2_vloops;
    execFuncCount++;
  }

   tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (2U * (N/16U))) * 3U * 2U];
   if ( enableInPlaceCompute == 1U )
  {
    pStage4Out = pInputDataWBuf;
  }
  else
  {
    pStage4Out = pScratchIBufH;
  }

  if (((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)!= 0) ||
    ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW) != 0))
  {
    vcop_fft_256_16ix16o_stage_3_overflow_init(
      pInputDataWBuf,/*Leg 0 */
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pInputDataWBuf,
      tfStageBasePtr,
      &pScaleFactorOut[2],
      numValidBits,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit,
      pBlock256->pblock_stage_3
    );

    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_3_overflow_vloops;
    execFuncCount++;

  }
  else
  {
    vcop_fft_256_16ix16o_stage_3_init(
      pInputDataWBuf,/*Leg 0 */
      pScratchIBufL,
      tfStageBasePtr,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit,
      pBlock256->pblock_stage_3
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_3_vloops;
    execFuncCount++;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW)
  {
    vcop_fft_256_16ix16o_stage_4_overflow_init(
      pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pStage4Out,
      &pScaleFactorOut[3],
      numValidBits,
      numOfLines,
      scaleFactorArray[3],
      saturationLimit,
      pBlock256->pblock_stage_4
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_4_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_256_16ix16o_stage_4_init(
      pScratchIBufL,
      pStage4Out,
      numOfLines,
      scaleFactorArray[3],
      saturationLimit,
      pBlock256->pblock_stage_4
    );
    pBlock256->execFunc[execFuncCount] = &vcop_fft_256_16ix16o_stage_4_vloops;
    execFuncCount++;
  }

  return (uint32_t)0;
}


void vcop_fft_256_16i_16o_vloops(uint16_t pblock[])
{
  sVCOP_FFT_256_pBlock_t * pBlock256 = (sVCOP_FFT_256_pBlock_t *) pblock;


  pBlock256->execFunc[0](pBlock256->pblock_stage_1);
  pBlock256->execFunc[1](pBlock256->pblock_stage_2);
  pBlock256->execFunc[2](pBlock256->pblock_stage_3);
  pBlock256->execFunc[3](pBlock256->pblock_stage_4);

}
#endif

void vcop_fft_256_16i_16o(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage4Out;
  memcpy(pScatterOffset, scatterOffsetArray, sizeof(scatterOffsetArray));

  tfStageBasePtr = &twiddleFactorBuf[0];

#if INDIVIDUAL_PROFILING
      profiler_start();
#endif
  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_256_16ix16o_stage_1_overflow
    (
      pInputDataWBuf,
      (int32_t *)(void *)pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufH,
      pScratchIBufL,
      tfStageBasePtr,
      pScaleFactorOut,
      numValidBits,
      pitch,
      numOfLines,
      scaleFactorArray[0],
      saturationLimit
    );
  }
  else
  {
    vcop_fft_256_16ix16o_stage_1
    (
      pInputDataWBuf,
      pScratchIBufL,
      tfStageBasePtr,
      pitch,
      numOfLines,
      scaleFactorArray[0],
      saturationLimit
    );
  }
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

    dumpIntoFile(pScratchIBufL, 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 0); 
    }
#endif


  tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];

#if INDIVIDUAL_PROFILING
      profiler_start();
#endif
  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
     vcop_fft_256_16ix16o_stage_2_overflow
    (
      pScratchIBufL,
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      &pScaleFactorOut[1],
      numValidBits,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit
    );
  }
  else
  {
    vcop_fft_256_16ix16o_stage_2
    (
      pScratchIBufL,
      pInputDataWBuf,
      tfStageBasePtr,
      pScatterOffset,
      (uint16_t)(N * sizeof(int16_t) * 2U),
      numOfLines,
      scaleFactorArray[1],
      saturationLimit
    );
  }
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

    dumpIntoFile(pInputDataWBuf, 2, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 17); 
    }
#endif

  tfStageBasePtr = &twiddleFactorBuf[ ((N/4U) + (2U * (N/16U))) * 3U * 2U];

  if ( enableInPlaceCompute == 1U )
  {
    pStage4Out = pInputDataWBuf;
  }
  else
  {
    pStage4Out = pScratchIBufH;
  }

#if INDIVIDUAL_PROFILING
  profiler_start();
#endif
  if (((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)!= 0 ) ||
      ((overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW)!= 0))
  {
    vcop_fft_256_16ix16o_stage_3_overflow(
      pInputDataWBuf,/*Leg 0 */
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pInputDataWBuf,
      tfStageBasePtr,
      &pScaleFactorOut[2],
      numValidBits,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit
    );
  }
  else
  {
    vcop_fft_256_16ix16o_stage_3(
      pInputDataWBuf,/*Leg 0 */
      pScratchIBufL,
      tfStageBasePtr,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit
    );
  }
#if INDIVIDUAL_PROFILING
        profiler_end_print(1);
#endif

#if INDIVIDUAL_PROFILING
      profiler_start();
#endif
  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE4_OVERFLOW)
  {
    vcop_fft_256_16ix16o_stage_4_overflow(
      pInputDataWBuf,
      (int32_t *)(void *)pScratchIBufL,
      (int32_t *)(void *)pScratchIBufH,
      pStage4Out,
      &pScaleFactorOut[3],
      numValidBits,
      numOfLines,
      scaleFactorArray[3],
      saturationLimit
    );
  }
  else
  {
    vcop_fft_256_16ix16o_stage_4(
      pScratchIBufL,
      pStage4Out,
      numOfLines,
      scaleFactorArray[3],
      saturationLimit
    );
  }
#if INDIVIDUAL_PROFILING
      profiler_end_print(1);
#endif


}



uint32_t vcop_fft_64_16i_16o_param_count(void)
{
  uint32_t pBlockCount=4U;/* Setting some non-zero value so that Host EMulation will not break */
  uint32_t pBlockCount1;
    uint32_t pBlockCount2;

#if (!VCOP_HOST_EMULATION)
    pBlockCount1 = ALIGN((sizeof(sVCOP_FFT_64_pBlock_t)), 4U) +
                 vcop_fft_64_16ix16o_stage_1_param_count() +
                 vcop_fft_64_16ix16o_stage_2_param_count() +
                 vcop_fft_64_16ix16o_stage_3_param_count();

    pBlockCount2 = ALIGN((sizeof(sVCOP_FFT_64_pBlock_t)), 4U) +
                  vcop_fft_64_16ix16o_stage_1_overflow_param_count() +
                  vcop_fft_64_16ix16o_stage_2_overflow_param_count() +
                  vcop_fft_64_16ix16o_stage_3_overflow_param_count();

    pBlockCount = MAX(pBlockCount1,pBlockCount2);
#endif

  return pBlockCount;

}

#if (!VCOP_HOST_EMULATION)
uint32_t vcop_fft_64_16i_16o_init(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage2In;
  int32_t * pStage2Scratch1;
  int32_t * pStage2Scratch2;
  int16_t * pStage2InterimBuf;
  int16_t * pStage2Out;
  int16_t * pStage3Out;
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
  pBlock64->pblock_stage_2   = (uint16_t *)pBlock64->pblock_stage_1 + vcop_fft_64_16ix16o_stage_1_overflow_param_count();
  pBlock64->pblock_stage_3   = (uint16_t *)pBlock64->pblock_stage_2 + vcop_fft_64_16ix16o_stage_2_overflow_param_count();

  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_64_16ix16o_stage_1_overflow_init
    (
       pInputDataWBuf,
       (int32_t*)(void *)pScratchIBufH,
       (int32_t*)(void *)pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pScatterOffset,
       pScaleFactorOut,
       numValidBits,
       pitch,
       numOfLines,
       saturationLimit,
       pBlock64->pblock_stage_1
     );

    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix16o_stage_1_overflow_vloops;
    execFuncCount++;
  }
  else
  {

    vcop_fft_64_16ix16o_stage_1_init
    (
       pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pScatterOffset,
       pitch,
       numOfLines,
       scaleFactorArray[0],
       saturationLimit,
       pBlock64->pblock_stage_1
     );
    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix16o_stage_1_vloops;
    execFuncCount++;
  }

  tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];
  if ( enableInPlaceCompute == 1U )
  {
    pStage2In  = pScratchIBufL;
    pStage2Out = pScratchIBufH;
    pStage2InterimBuf = pScratchIBufH;
    pStage2Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage2Scratch2 = (int32_t*)(void *)pInputDataWBuf;
    pStage3Out = pInputDataWBuf;
    pStage3Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage3Scratch2 = (int32_t*)(void *)pScratchIBufH;
    pStage3InterimBuf = pInputDataWBuf;

  }
  else
  {
    pStage2In  = pScratchIBufL;
    pStage2Out = pInputDataWBuf;
    pStage2InterimBuf = pInputDataWBuf;
    pStage2Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage2Scratch2 = (int32_t*)(void *)pScratchIBufH;
    pStage3Out = pScratchIBufH;
    pStage3Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage3Scratch2 = (int32_t*)(void *)pInputDataWBuf;
    pStage3InterimBuf = pScratchIBufH;
  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
    vcop_fft_64_16ix16o_stage_2_overflow_init
    (
      pStage2In,
      pStage2Scratch1,
      pStage2Scratch2,
      pStage2Out,
      tfStageBasePtr,
      &pScatterOffset[8],
      &pScaleFactorOut[1],
      pStage2InterimBuf,
      numValidBits,
      numOfLines,
      saturationLimit,
     pBlock64->pblock_stage_2
    );
    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix16o_stage_2_overflow_vloops;
    execFuncCount++;
  }
  else
  {
    vcop_fft_64_16ix16o_stage_2_init
    (
      pStage2In,
      pStage2Out,
      tfStageBasePtr,
      &pScatterOffset[8],
      numOfLines,
      scaleFactorArray[1],
      saturationLimit,
      pBlock64->pblock_stage_2
    );
    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix16o_stage_2_vloops;
    execFuncCount++;

  }

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)
  {
    vcop_fft_64_16ix16o_stage_3_overflow_init(
      pStage2Out,
      pStage3Scratch1,
      pStage3Scratch2,
      pStage3Out,
      &pScaleFactorOut[2],
      pStage3InterimBuf,
      numValidBits,
      numOfLines,
      saturationLimit,
      pBlock64->pblock_stage_3
    );
    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix16o_stage_3_overflow_vloops;
    execFuncCount++;

  }
  else
  {
    vcop_fft_64_16ix16o_stage_3_init(
      pStage2Out,
      pStage3Out,
      numOfLines,
      scaleFactorArray[2],
      saturationLimit,
      pBlock64->pblock_stage_3
    );
    pBlock64->execFunc[execFuncCount] = &vcop_fft_64_16ix16o_stage_3_vloops;
    execFuncCount++;

  }

  return (uint32_t)0;
}


void vcop_fft_64_16i_16o_vloops(uint16_t pblock[])
{
  sVCOP_FFT_64_pBlock_t * pBlock64 = (sVCOP_FFT_64_pBlock_t *) pblock;

  pBlock64->execFunc[0](pBlock64->pblock_stage_1);
  pBlock64->execFunc[1](pBlock64->pblock_stage_2);
  pBlock64->execFunc[2](pBlock64->pblock_stage_3);

}
#endif

void vcop_fft_64_16i_16o(
    int16_t      *pInputDataWBuf,
    int16_t      *pScratchIBufL,
    int16_t      *pScratchIBufH,
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
  int16_t * pStage2In;
  int32_t * pStage2Scratch1;
  int32_t * pStage2Scratch2;
  int16_t * pStage2InterimBuf;
  int16_t * pStage2Out;
  int16_t * pStage3Out;
  int32_t * pStage3Scratch1;
  int32_t * pStage3Scratch2;
  int16_t * pStage3InterimBuf;

  memcpy(pScatterOffset, scatterOffsetArray1, sizeof(scatterOffsetArray1));
  memcpy(&pScatterOffset[8], scatterOffsetArray2, sizeof(scatterOffsetArray2));

  tfStageBasePtr = &twiddleFactorBuf[0];

#if INDIVIDUAL_PROFILING
    profiler_start();
#endif
  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE1_OVERFLOW)
  {
    vcop_fft_64_16ix16o_stage_1_overflow(pInputDataWBuf,
                                         (int32_t*)(void *)pScratchIBufH,
                                         (int32_t*)(void *)pInputDataWBuf,
                                         pScratchIBufL,
                                         tfStageBasePtr,
                                         pScatterOffset,
                                         pScaleFactorOut,
                                         numValidBits,
                                         pitch,
                                         numOfLines,
                                         saturationLimit);
  }
  else
  {

    vcop_fft_64_16ix16o_stage_1
    (
       pInputDataWBuf,
       pScratchIBufL,
       tfStageBasePtr,
       pScatterOffset,
       pitch,
       numOfLines,
       scaleFactorArray[0],
       saturationLimit
     );
  }

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
  
      dumpIntoFile(pScratchIBufL, 1, numOfGrp, numBFperGrp, currentRadix, numOfLines, numPoints, overflowMask, 9); 
      }
#endif

  tfStageBasePtr = &twiddleFactorBuf[(N/4U) * 3U * 2U];


  if ( enableInPlaceCompute == 1U )
  {
    pStage2In  = pScratchIBufL;
    pStage2Out = pScratchIBufH;
    pStage2InterimBuf = pScratchIBufH;
    pStage2Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage2Scratch2 = (int32_t*)(void *)pInputDataWBuf;
    pStage3Out = pInputDataWBuf;
    pStage3Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage3Scratch2 = (int32_t*)(void *)pScratchIBufH;
    pStage3InterimBuf = pInputDataWBuf;

  }
  else
  {
    pStage2In  = pScratchIBufL;
    pStage2Out = pInputDataWBuf;
    pStage2InterimBuf = pInputDataWBuf;
    pStage2Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage2Scratch2 = (int32_t*)(void *)pScratchIBufH;
    pStage3Out = pScratchIBufH;
    pStage3Scratch1 = (int32_t*)(void *)pScratchIBufL;
    pStage3Scratch2 = (int32_t*)(void *)pInputDataWBuf;
    pStage3InterimBuf = pScratchIBufH;
  }

#if INDIVIDUAL_PROFILING
  profiler_start();
#endif
  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE2_OVERFLOW)
  {
    vcop_fft_64_16ix16o_stage_2_overflow
    (
      pStage2In,
      pStage2Scratch1,
      pStage2Scratch2,
      pStage2Out,
      tfStageBasePtr,
      &pScatterOffset[8],
      &pScaleFactorOut[1],
      pStage2InterimBuf,
      numValidBits,
      numOfLines,
       saturationLimit
    );
  }
  else
  {
    vcop_fft_64_16ix16o_stage_2
    (
      pStage2In,
      pStage2Out,
      tfStageBasePtr,
      &pScatterOffset[8],
      numOfLines,
      scaleFactorArray[1],
      saturationLimit
    );
  }
#if INDIVIDUAL_PROFILING
  profiler_end_print(1);
#endif

#if INDIVIDUAL_PROFILING
  profiler_start();
#endif

  if (overflowMask & VCOP_FFT_NPT_16ix16o_STAGE3_OVERFLOW)
  {
    vcop_fft_64_16ix16o_stage_3_overflow(
      pStage2Out,
      pStage3Scratch1,
      pStage3Scratch2,
      pStage3Out,
      &pScaleFactorOut[2],
      pStage3InterimBuf,
      numValidBits,
      numOfLines,
      saturationLimit
    );
  }
  else
  {
    vcop_fft_64_16ix16o_stage_3(
      pStage2Out,
      pStage3Out,
      numOfLines,
      scaleFactorArray[2],
       saturationLimit
    );
  }
#if INDIVIDUAL_PROFILING
  profiler_end_print(1);
#endif


}

