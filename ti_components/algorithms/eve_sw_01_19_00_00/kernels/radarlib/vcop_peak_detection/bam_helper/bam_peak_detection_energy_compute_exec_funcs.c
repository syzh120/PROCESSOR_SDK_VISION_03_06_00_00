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
 *  @file       bam_peak_detection_energy_compute_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating DC offset, windowing kernels
 *                into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_peak_detection_energy_compute_int.h"
#include "bam_peak_detection_energy_compute.h"
#include "vcop_peak_detection_kernel.h" /* compiler should take care of include path */

#include "edma_utils_memcpy.h"

#define BAM_PEAK_DETECTION_ENERGY_COMPUTE_IMG_BUF_A_B_OFFSET (0x20000U)


/***********************************************************************************************/
/*                        Below are the helper  functions related to DC offset windowing and interference zero out kernels              */
/***********************************************************************************************/
static BAM_Status Bam_PeakDetectionEnergyCompute_initFrame(void *kernelContext);
static BAM_Status Bam_PeakDetectionEnergyCompute_computeFrame(void *kernelContext);

static BAM_Status Bam_PeakDetectionEnergyCompute_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_PeakDetectionEnergyCompute_initFrame(void *kernelContext)
{
  BAM_PeakDetectionEnergyCompute_Context *context = (BAM_PeakDetectionEnergyCompute_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;
  uint32_t i;
  uint32_t numWordsRequired;
  uint32_t numLUTPoints;
  uint32_t *lutTableBasePtr;
  uint16_t (*pScatterIndex)[VCOP_SIMD_WIDTH] = NULL;
  uint32_t pBlockSize = 0;

  numLUTPoints = ((uint32_t)1U<<(context->kernelCtrlArgs.alphaQFormat));

  pScatterIndex = (uint16_t (*)[VCOP_SIMD_WIDTH])context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PSCATTER_IDX];

  numWordsRequired = context->kernelCtrlArgs.nuwRows/2U;
  if ( numWordsRequired < 9U )
  {
    numWordsRequired = 9U;
  }

  context->transposePitch  = (( (numWordsRequired % 2U)== 0 ) ? (numWordsRequired + 1U) : numWordsRequired);

  context->transposePitch  = context->transposePitch   * sizeof(uint32_t);

  for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
  {
    (*pScatterIndex)[i] = (uint16_t)i * context->transposePitch;
  }

  for ( i = 0; i < (context->kernelCtrlArgs.numHorzPtPerAntenna / VCOP_SIMD_WIDTH);i++)
  {
    context->inputDataArr[i]   = (int16_t *)context->pInBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_ANTENNA_DATA_PORT] + (i * ((uint32_t)VCOP_SIMD_WIDTH) * 2U);
    context->outputDataArr[i]  = (int16_t *)context->pOutBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT] + (i * ((uint32_t)VCOP_SIMD_WIDTH) * 2U);
  }

  if ( context->kernelCtrlArgs.enableTxDecoding )
  {
      context->pEnergyCompIn  = context->pOutBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT];/* IBUFHA*/
      EDMA_UTILS_memcpy2D(context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_TX_DECODING_COEFF_IDX],
                          context->kernelCtrlArgs.txDecodingPtr,
                          context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numTx * sizeof(int16_t),
                          1U,
                          0,
                          0);
  }
  else
  {
      context->pEnergyCompIn = context->pInBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_ANTENNA_DATA_PORT]/*IBUFLA*/;
  }

  lutTableBasePtr = (uint32_t*)context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX];

  EDMA_UTILS_memcpy2D((uint8_t*)context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX] +
                            ((numLUTPoints / 2U ) * BAM_PEAK_DETECTION_ENERGY_COMPUTE_NUM_TABLES * sizeof(uint32_t)),
                            context->kernelCtrlArgs.lutTablePtr,
                            (uint16_t)((numLUTPoints / 2U ) * BAM_PEAK_DETECTION_ENERGY_COMPUTE_NUM_TABLES * sizeof(uint32_t)),
                            1U,
                            0,
                            0);

  /* Set the zero'th index of LUT table to zero to handle the case when energy is zero. Zero'th index will correspond to the
  first row of LUT table. Hence set first full row of LUT table to zero*/
  for ( i = 0; i < BAM_PEAK_DETECTION_ENERGY_COMPUTE_NUM_TABLES; i++)
  {
    lutTableBasePtr[i] = 0;
  }


  context->pEnergyCompOut = context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_ENERGY32_IDX];/*WBUF*/


#if (!VCOP_HOST_EMULATION)
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->pBlockTxDecoding = (uint16_t *)context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PARAMS_IDX];
  context->pBlockEnergyCal= context->pBlockTxDecoding + vcop_tx_decoding_kernel_param_count();
  context->pBlockBinLog= context->pBlockEnergyCal + vcop_peak_detection_energy_across_antenna_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  pBlockSize += vcop_tx_decoding_kernel_init(
       context->inputDataArr,
       context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_TX_DECODING_COEFF_IDX],
       context->outputDataArr,
       context->kernelCtrlArgs.numTx,
       context->kernelCtrlArgs.numRx,
       context->kernelCtrlArgs.nuwRows,
       context->kernelCtrlArgs.numHorzPtPerAntenna,
       context->kernelCtrlArgs.offsetBwTx,
       context->kernelCtrlArgs.offsetBwRx,
       context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numRx * context->kernelCtrlArgs.numHorzPtPerAntenna * 2U * sizeof(int16_t),
       context->pBlockTxDecoding);

  pBlockSize += vcop_peak_detection_energy_across_antenna_init(
       context->pEnergyCompIn,
       context->pEnergyCompOut,
       context->kernelCtrlArgs.nuwRows,
       context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numRx,
       context->kernelCtrlArgs.numHorzPtPerAntenna,
       context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numRx * context->kernelCtrlArgs.numHorzPtPerAntenna * 2U * sizeof(int16_t),
       context->pBlockEnergyCal);


  pBlockSize = vcop_peak_detection_binlog_energy_scaling_init(
      context->pEnergyCompOut,
      context->pOutBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT],/* Re-use output buffer to store index */
      context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LMBD_IDX],
      context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX],
      context->pInBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_ANTENNA_DATA_PORT],/*Re-use input buffer in IBUFLA to store the LUT VALUE */
      context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PSCATTER_IDX],
      context->pOutBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT],
      context->transposePitch,
      context->kernelCtrlArgs.lutQFormat,
      context->kernelCtrlArgs.alphaQFormat,
      context->kernelCtrlArgs.nuwRows,
      context->kernelCtrlArgs.numHorzPtPerAntenna,
      context->pBlockBinLog);

#endif

  return status;
}


static BAM_Status Bam_PeakDetectionEnergyCompute_computeFrame(void *kernelContext)
{
    BAM_PeakDetectionEnergyCompute_Context *context = (BAM_PeakDetectionEnergyCompute_Context *)kernelContext;


#if (VCOP_HOST_EMULATION)
    if ( (context->kernelCtrlArgs.enableTxDecoding) )
    {
        vcop_tx_decoding_kernel(
           context->inputDataArr,
           context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_TX_DECODING_COEFF_IDX],
           context->outputDataArr,
           context->kernelCtrlArgs.numTx,
           context->kernelCtrlArgs.numRx,
           context->kernelCtrlArgs.nuwRows,
           context->kernelCtrlArgs.numHorzPtPerAntenna,
           context->kernelCtrlArgs.offsetBwTx,
           context->kernelCtrlArgs.offsetBwRx,
           context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numRx * context->kernelCtrlArgs.numHorzPtPerAntenna * 2 * sizeof(int16_t));
    }

    vcop_peak_detection_energy_across_antenna(
           context->pEnergyCompIn,
           context->pEnergyCompOut,
           context->kernelCtrlArgs.nuwRows,
           context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numRx,
           context->kernelCtrlArgs.numHorzPtPerAntenna,
           context->kernelCtrlArgs.numTx * context->kernelCtrlArgs.numRx * context->kernelCtrlArgs.numHorzPtPerAntenna * 2 * sizeof(int16_t));


    vcop_peak_detection_binlog_energy_scaling(
          context->pEnergyCompOut,
          context->pOutBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT],/* Re-use output buffer to store index */
          context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LMBD_IDX],
          context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_LUTTABLE_IDX],
          context->pInBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_ANTENNA_DATA_PORT],/*Re-use input buffer in IBUFLA to store the LUT VALUE */
          context->pInternalBlock[PEAK_DETECTION_ENERGY_COMPUTE_INTERNAL_PSCATTER_IDX],
          context->pOutBlock[BAM_PEAK_DETECTION_ENERGY_COMPUTE_OUTPUT_PORT],
          context->transposePitch,
          context->kernelCtrlArgs.lutQFormat,
          context->kernelCtrlArgs.alphaQFormat,
          context->kernelCtrlArgs.nuwRows,
          context->kernelCtrlArgs.numHorzPtPerAntenna);


#else
  if ( (context->kernelCtrlArgs.enableTxDecoding) )
  {
    vcop_tx_decoding_kernel_vloops(context->pBlockTxDecoding);
  }
  vcop_peak_detection_energy_across_antenna_vloops(context->pBlockEnergyCal);
  vcop_peak_detection_binlog_energy_scaling_vloops(context->pBlockBinLog);
#endif

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_PeakDetectionEnergyCompute_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_PeakDetectionEnergyCompute_Context *context = (BAM_PeakDetectionEnergyCompute_Context *) kernelContext;

  BAM_PeakDetectionEnergyCompute_ctrlArgs * args = (BAM_PeakDetectionEnergyCompute_ctrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *args;

  return status;
}


BAM_KernelExecFuncDef gBAM_TI_peakDetectionEnergyComputeExecFunc =
{
  NULL,
  &Bam_PeakDetectionEnergyCompute_initFrame,
  &Bam_PeakDetectionEnergyCompute_computeFrame,
  NULL,
  &Bam_PeakDetectionEnergyCompute_control,
  NULL
};


