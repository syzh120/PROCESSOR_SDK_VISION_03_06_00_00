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
 *  @file       bam_peak_detection_cfar_ca_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating CFAR CA kernels
 *                into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>
#include "math.h"

#include "bam_peak_detection_cfar_ca_int.h"
#include "bam_peak_detection_cfar_ca.h"
#include "vcop_peak_detection_kernel.h" /* compiler should take care of include path */

#include "edma_utils_memcpy.h"

#define BAM_PEAK_DETECTION_CFAR_CA_IMG_BUF_A_B_OFFSET (0x20000U)
#define BAM_PEAK_DETECTION_CFAR_CA_MAX_NUM_HORZ_PT    (128U)

typedef double float64_t;

/***********************************************************************************************/
/*                        Below are the helper  functions related to DC offset windowing and interference zero out kernels              */
/***********************************************************************************************/
static BAM_Status Bam_PeakDetectionCfarCa_initFrame(void *kernelContext);
static BAM_Status Bam_PeakDetectionCfarCa_computeFrame(void *kernelContext);

static BAM_Status Bam_PeakDetectionCfarCa_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_PeakDetectionCfarCa_initFrame(void *kernelContext)
{
  BAM_PeakDetectionCfarCa_Context *context = (BAM_PeakDetectionCfarCa_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;
  uint32_t i, j;
  uint32_t pBlockSize = 0;
  uint32_t (*idxBuf)[BAM_PEAK_DETECTION_CFAR_CA_MAX_NUM_HORZ_PT];
  uint16_t (*scatterIndex)[VCOP_SIMD_WIDTH];
  uint32_t Log2Const;
  uint32_t numKernels = 0;
  uint32_t scaleFactor  = (uint32_t)((uint32_t)1U << (uint32_t)context->kernelInitArgs.log2QFormat);
  float64_t tempFloat;
  /* Threshold to be used for CFAR CA DB.
 *     Original equation of CFAR CA detector is CUT > T * ANF, where T can be written as C1/ 2^C2
 *     Same equation in log domain becomes
 *     log(CUT)> log(T) + log(NF)
 *     =  log(CUT) -  log(NF)> log(C1) - C2
 *     So threshold here is log(C1) - C2.
 *     Q format for threshold should be same as lutQFormat used during energy computation*/
  tempFloat = ((log((float64_t)context->kernelCtrlArgs.const1) / log((float64_t)2.0)) *
                  (float64_t)scaleFactor);
  Log2Const =  (uint32_t)tempFloat;
  context->cfarCaThreshold = Log2Const - (context->kernelCtrlArgs.const2 * ((uint32_t)1U <<context->kernelInitArgs.log2QFormat));

  tempFloat = (log((float64_t)context->kernelCtrlArgs.noiseLen)/log((float64_t)2.0));
  context->shiftAmount = (uint16_t)tempFloat;

  context->shiftAmount = context->shiftAmount +(uint16_t) 1U;

  if ( context->kernelCtrlArgs.numHorzPoint == 8U )
  {
    context->numHorzPoint = context->kernelCtrlArgs.numHorzPoint * 2;
    context->numVertPoint = context->kernelCtrlArgs.numVertPoint/ 2;
    context->cellSumPitch = 2 * context->kernelCtrlArgs.numHorzPoint * sizeof(uint16_t);
    context->inputDataPitch = 2 * context->kernelCtrlArgs.inputDataPitch;
  }
  else
  {
    context->numHorzPoint = context->kernelCtrlArgs.numHorzPoint;
    context->numVertPoint = context->kernelCtrlArgs.numVertPoint;
    context->cellSumPitch = context->numHorzPoint * sizeof(uint16_t);
    context->inputDataPitch = context->kernelCtrlArgs.inputDataPitch;
  }

  idxBuf = (uint32_t (*)[BAM_PEAK_DETECTION_CFAR_CA_MAX_NUM_HORZ_PT]) context->pInternalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_DOPPLER_INDEX_IDX];

  if ( context->kernelInitArgs.rangeDopplerOrder )
  {
    context->vertCoordinateShift = 16U;
    context->horzIdxUpdateOffset = context->kernelCtrlArgs.numHorzPoint;
    for ( j = 0; j < 2U; j++)
    {
      for ( i = 0; i < context->kernelCtrlArgs.numHorzPoint; i++)
      {
        (*idxBuf)[i + (j * context->kernelCtrlArgs.numHorzPoint)] = (i<<(16U - context->vertCoordinateShift) ) +
                             ((j * (context->kernelCtrlArgs.numVertPoint/2U))<< context->vertCoordinateShift);
      }
    }
    context->idxBuf = (uint8_t *)context->pInternalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_DOPPLER_INDEX_IDX];
  }
  else
  {
    context->vertCoordinateShift = 0;
    context->horzIdxUpdateOffset = 0;
    for ( j = 0; j < 2U; j++)
    {
      for ( i = 0; i < context->kernelCtrlArgs.numHorzPoint; i++)
      {
        (*idxBuf)[i + (j * context->kernelCtrlArgs.numHorzPoint)] = 0;
      }
    }

    context->idxBuf = *(uint8_t (*)[])context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT] +
      context->kernelInitArgs.maxExtraInputBufRequired +
      ((context->kernelInitArgs.maxNumHorzPoint *
        context->kernelInitArgs.maxNumVertPoint *
        sizeof(uint16_t) )/ 2U);
  }

  context->transposePitch = ((context->kernelCtrlArgs.numHorzPoint / 2U) + 1U) * sizeof(uint32_t);
  *((uint32_t *)context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX]) = 0;

  scatterIndex = (uint16_t (*)[VCOP_SIMD_WIDTH]) context->pInternalBlock[PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX];

  for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
  {
    (*scatterIndex)[i] = (uint16_t)i * context->transposePitch;
  }



  if ( (uint32_t)context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT] >
        (uint32_t)context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT] )
  {
    context->offsetBwInBufs = (uint32_t)context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT] -
                              (uint32_t)context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT];
  }
  else
  {
    context->offsetBwInBufs = (uint32_t)context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT] -
                              (uint32_t)context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT];
  }


#if (!VCOP_HOST_EMULATION)
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->pBlockCellSum  = (uint16_t *)context->pInternalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_PARAMS_IDX];
  context->pBlockCfarCa   = context->pBlockCellSum + vcop_peak_detection_cell_sum_param_count();
  if ( context->kernelInitArgs.rangeDopplerOrder == 0 )
  {
    context->pBlockTranspose = context->pBlockCfarCa + vcop_peak_detection_CFARCA_thresholding_param_count();
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    pBlockSize += vcop_peak_detection_transpose_init(
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT],
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX],
       context->kernelCtrlArgs.numVertPoint,
       context->kernelCtrlArgs.numHorzPoint,
       context->transposePitch,
       context->kernelCtrlArgs.noiseLen,
       context->pBlockTranspose);

     /* Store the function pointer and corresponding pBlock to be called later */
     context->execFunc[numKernels] = &vcop_peak_detection_transpose_vloops;
     context->kernelContext[numKernels] = (BAM_PeakDetectionCfarCa_KernelContextType)context->pBlockTranspose;
     numKernels++;
  }


  pBlockSize += vcop_peak_detection_cell_sum_init(
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT],
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_ONE_LINE_IDX],
       context->kernelCtrlArgs.noiseLen,
       context->kernelCtrlArgs.gaurdLen,
       context->kernelCtrlArgs.numHorzPoint,
       context->kernelCtrlArgs.numVertPoint,
       context->kernelCtrlArgs.inputDataPitch,
       context->kernelCtrlArgs.numHorzPoint * sizeof(uint16_t),
       context->shiftAmount,/*Shift*/
       context->pBlockCellSum);

  /* Store the function pointer and corresponding pBlock to be called later */
  context->execFunc[numKernels] = &vcop_peak_detection_cell_sum_vloops;
  context->kernelContext[numKernels] = (BAM_PeakDetectionCfarCa_KernelContextType)context->pBlockCellSum;
  numKernels++;

  pBlockSize += vcop_peak_detection_CFARCA_thresholding_init(
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_BINARY_MASK_IDX],
       context->pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_RANGE_DOPPLER_PORT],
       context->pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_ENERGY_PORT],
       (uint32_t*)(void *)context->idxBuf,
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX],
       context->pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_DETECTIONS_PORT],
       context->offsetBwInBufs,
       context->kernelCtrlArgs.noiseLen,
       context->kernelCtrlArgs.gaurdLen,
       context->kernelCtrlArgs.numHorzPoint,
       context->numHorzPoint,
       context->kernelCtrlArgs.numVertPoint,
       context->numVertPoint,
       context->kernelCtrlArgs.numHorzPoint * sizeof(uint16_t),
       context->cellSumPitch,
       context->kernelCtrlArgs.inputDataPitch,
       context->inputDataPitch,
       context->vertCoordinateShift,
       context->horzIdxUpdateOffset,
       context->cfarCaThreshold,
       context->pBlockCfarCa);

  /* Store the function pointer and corresponding pBlock to be called later */
  context->execFunc[numKernels] = &vcop_peak_detection_CFARCA_thresholding_vloops;
  context->kernelContext[numKernels] = (BAM_PeakDetectionCfarCa_KernelContextType)context->pBlockCfarCa;
  numKernels++;

  context->numKernels = numKernels;
#endif

  return status;
}


static BAM_Status Bam_PeakDetectionCfarCa_computeFrame(void *kernelContext)
{
    BAM_PeakDetectionCfarCa_Context *context = (BAM_PeakDetectionCfarCa_Context *)kernelContext;
    uint32_t kernelIdx;

#if (VCOP_HOST_EMULATION)
    if ( context->kernelInitArgs.rangeDopplerOrder == 0 )
    {

      vcop_peak_detection_transpose(
         context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT],
         context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT],
         context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX],
         context->pInternalBlock[PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX],
        context->kernelCtrlArgs.numVertPoint,
        context->kernelCtrlArgs.numHorzPoint,
         context->transposePitch,
         context->kernelCtrlArgs.noiseLen);
    }

    vcop_peak_detection_cell_sum(
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT],
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY2_PORT],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_ONE_LINE_IDX],
       context->kernelCtrlArgs.noiseLen,
       context->kernelCtrlArgs.gaurdLen,
       context->kernelCtrlArgs.numHorzPoint,
       context->kernelCtrlArgs.numVertPoint,
       context->kernelCtrlArgs.inputDataPitch,
       context->kernelCtrlArgs.numHorzPoint * sizeof(uint16_t),
       context->shiftAmount);/*Shift*/

    vcop_peak_detection_CFARCA_thresholding(
       context->pInBlock[BAM_PEAK_DETECTION_CFAR_CA_INPUT_ENERGY1_PORT],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX],
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_BINARY_MASK_IDX],
       context->pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_RANGE_DOPPLER_PORT],
       context->pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_OUTPUT_ENERGY_PORT],
       context->idxBuf,
       context->pInternalBlock[PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX],
       context->pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_DETECTIONS_PORT],
       context->offsetBwInBufs,
       context->kernelCtrlArgs.noiseLen,
       context->kernelCtrlArgs.gaurdLen,
       context->kernelCtrlArgs.numHorzPoint,
       context->numHorzPoint,
       context->kernelCtrlArgs.numVertPoint,
       context->numVertPoint,
       context->kernelCtrlArgs.numHorzPoint * sizeof(uint16_t),
       context->cellSumPitch,
       context->kernelCtrlArgs.inputDataPitch,
       context->inputDataPitch,
       context->vertCoordinateShift,
       context->horzIdxUpdateOffset,
       context->cfarCaThreshold);

#else
    for (kernelIdx = 0 ; kernelIdx < context->numKernels; kernelIdx++)
    {
      context->execFunc[kernelIdx](context->kernelContext[kernelIdx]);
    }
#endif

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_PeakDetectionCfarCa_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_PeakDetectionCfarCa_Context *context = (BAM_PeakDetectionCfarCa_Context *) kernelContext;

  BAM_PeakDetectionCfarCa_ctrlArgs * args = (BAM_PeakDetectionCfarCa_ctrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *args;

  return status;
}


BAM_KernelExecFuncDef gBAM_TI_peakDetectionCfarCaExecFunc =
{
  NULL,
  &Bam_PeakDetectionCfarCa_initFrame,
  &Bam_PeakDetectionCfarCa_computeFrame,
  NULL,
  &Bam_PeakDetectionCfarCa_control,
  NULL
};


