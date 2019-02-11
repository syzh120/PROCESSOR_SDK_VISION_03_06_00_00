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
 *  @file       bam_beam_forming_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating DC offset, windowing kernels
 *                into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>
#include <string.h>

#include "bam_beam_forming_int.h"
#include "bam_beam_forming.h"
#include "vcop_beam_forming_kernel.h" /* compiler should take care of include path */

#include "edma_utils_memcpy.h"

#define BAM_BEAM_FORMING_IMG_BUF_A_B_OFFSET (0x20000U)

/***********************************************************************************************/
/*                        Below are the helper  functions related to DC offset windowing and interference zero out kernels              */
/***********************************************************************************************/
static inline uint8_t * Bam_BeamForming_addOffset(uint8_t ptr[], uint32_t offset);

static inline uint8_t * Bam_BeamForming_addOffset(uint8_t ptr[], uint32_t offset)
{
  return &ptr[offset];
}

static BAM_Status Bam_BeamForming_initFrame(void *kernelContext);
static BAM_Status Bam_BeamForming_computeFrame(void *kernelContext);

static BAM_Status Bam_BeamForming_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_BeamForming_initFrame(void *kernelContext)
{
  BAM_BeamForming_Context *context = (BAM_BeamForming_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;
  uint32_t i;

  uint16_t (*pScatterIndex)[VCOP_SIMD_WIDTH] = NULL;
  uint32_t pBlockSize = 0;

  pScatterIndex = (uint16_t (*)[VCOP_SIMD_WIDTH])context->pInternalBlock[BEAM_FORMING_INTERNAL_PSCATTER_IDX];

  /* For first call we always have to copy steering matrix from IBUF to WBUF */
  context->enableSMCopy = 1U;
  context->pingPongFlag = 0;


  context->pMatMulOutput = context->pInBlock[BAM_BEAM_FORMING_ANTENNA_DATA_PORT];/* IBUFLA */
  context->pEnergy       = context->pInBlock[BAM_BEAM_FORMING_STEERING_MATRIX_PORT];/* IBUFHA */
  context->pTransposeOut = context->pInBlock[BAM_BEAM_FORMING_STEERING_MATRIX_PORT];/* IBUFHA */
  context->pBeamFormingInfo[0] = (BAM_BeamForming_Info *)context->pInBlock[BAM_BEAM_FORMING_INFO_PORT];
#if VCOP_HOST_EMULATION
  context->pBeamFormingInfo[1] = context->pBeamFormingInfo[0];
  context->currDetectionIdx    = 0;
#else
  /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
  /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
  /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
  context->pBeamFormingInfo[1] = (BAM_BeamForming_Info *)(void *)((uint8_t *)(void *)context->pBeamFormingInfo[0] +
                           BAM_BEAM_FORMING_IMG_BUF_A_B_OFFSET );
  /* RESET_MISRA("17.4")  -> Reset rule 17.4     */
#endif

  if (( context->kernelCtrlArgs.numAngles % 2U) != 0 )
  {
    uint8_t *steeringMatrixEnd =  Bam_BeamForming_addOffset((uint8_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_STEERING_MATRIX_IDX],
      context->kernelCtrlArgs.numAngles * context->kernelCtrlArgs.numAntennas * sizeof(int16_t) * 2U);

    memset(steeringMatrixEnd, 0, context->kernelCtrlArgs.numAntennas * sizeof(int32_t));
  }
  context->transposePitch = (((context->kernelCtrlArgs.numDetections % 2U) ? context->kernelCtrlArgs.numDetections:
                        context->kernelCtrlArgs.numDetections + 1U)) * sizeof(uint32_t);

  for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
  {
    (*pScatterIndex)[i] = (uint16_t)i * context->transposePitch;
  }

#if (!VCOP_HOST_EMULATION)
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->pBlockBeamForming      = (uint16_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_PARAMS_IDX];
  context->pBlockEnergyCal        = context->pBlockBeamForming + vcop_beam_forming_kernel_param_count();
  context->pBlockAngleAssociation = context->pBlockEnergyCal + vcop_beam_energy_calculation_kernel_param_count();
  context->pBlockSteeringMatCopy  = context->pBlockAngleAssociation + vcop_beam_angle_association_kernel_param_count();
  context->pBlockTranspose        = context->pBlockSteeringMatCopy + vcop_beam_forming_copy_steering_matrix_kernel_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  pBlockSize += vcop_beam_forming_copy_steering_matrix_kernel_init(
       context->pInBlock[BAM_BEAM_FORMING_STEERING_MATRIX_PORT],/*IBUFHA*/
       context->pInternalBlock[BEAM_FORMING_INTERNAL_STEERING_MATRIX_IDX],/*WBUF*/
       context->kernelCtrlArgs.numAngles,
       context->kernelCtrlArgs.numAntennas,
       context->pBlockSteeringMatCopy);

  pBlockSize += vcop_beam_forming_transpose_antenna_data_kernel_init(
       context->pInBlock[BAM_BEAM_FORMING_ANTENNA_DATA_PORT],/*IBUFLA*/
       context->pTransposeOut,/*IBUFHA*/
       context->pInternalBlock[BEAM_FORMING_INTERNAL_PSCATTER_IDX],
       context->transposePitch,
       context->kernelCtrlArgs.numDetections,
       context->kernelCtrlArgs.numAntennas,
       context->pBlockTranspose);


  pBlockSize = vcop_beam_forming_kernel_init(
      context->pTransposeOut,
      context->pMatMulOutput,
      context->pInternalBlock[BEAM_FORMING_INTERNAL_STEERING_MATRIX_IDX],
      context->transposePitch,
      context->kernelCtrlArgs.numDetections,
      context->kernelCtrlArgs.numAntennas,
      context->kernelCtrlArgs.numAngles,
      context->kernelCtrlArgs.beamFormingScaling,
      context->pBlockBeamForming);

  pBlockSize += vcop_beam_energy_calculation_kernel_init(
       context->pMatMulOutput,
       context->pEnergy,
       context->kernelCtrlArgs.numDetections,
       ALIGN(context->kernelCtrlArgs.numAngles, 2U),
       context->pBlockEnergyCal);

  pBlockSize += vcop_beam_angle_association_kernel_init(
       context->pEnergy,
       context->pInternalBlock[BEAM_FORMING_INTERNAL_OUT_ANGLE_IDX],
       context->pInternalBlock[BEAM_FORMING_INTERNAL_OUT_ENERGY_IDX],
       (uint16_t *)(void *)context->pBeamFormingInfo[0],
       (uint32_t *)(void *)context->pBlockAngleAssociation,/* This is pass for pblock update */
       context->pBeamFormingInfo[0]->baseAngleOffset,/* this field will get updated because of param block update within the kernel */
       context->kernelCtrlArgs.numDetections,
       context->kernelCtrlArgs.numAngles,
       context->kernelCtrlArgs.energyScaling,
       context->pBlockAngleAssociation);

#endif
  context->pingPongFlag ^= 1U;

  return status;
}


static BAM_Status Bam_BeamForming_computeFrame(void *kernelContext)
{
    BAM_BeamForming_Context *context = (BAM_BeamForming_Context *)kernelContext;


#if (VCOP_HOST_EMULATION)
    /* This condition is different for host emulation as in host emulation we are always working on the
    data which is currently transferred using DMa whereas in target there is a delay of one call */
    if ( (*context->kernelCtrlArgs.enableSMcopyShared) )
    {
      vcop_beam_forming_copy_steering_matrix_kernel(
           context->pInBlock[BAM_BEAM_FORMING_STEERING_MATRIX_PORT],/*IBUFHA*/
           context->pInternalBlock[BEAM_FORMING_INTERNAL_STEERING_MATRIX_IDX],/*WBUF*/
           context->kernelCtrlArgs.numAngles,
           context->kernelCtrlArgs.numAntennas);
    }

    vcop_beam_forming_transpose_antenna_data_kernel(
         context->pInBlock[BAM_BEAM_FORMING_ANTENNA_DATA_PORT],/*IBUFLA*/
         context->pTransposeOut,/*IBUFHA*/
         context->pInternalBlock[BEAM_FORMING_INTERNAL_PSCATTER_IDX],
         context->transposePitch,
         context->kernelCtrlArgs.numDetections,
         context->kernelCtrlArgs.numAntennas);


    vcop_beam_forming_kernel(
        context->pTransposeOut,
        context->pMatMulOutput,
        context->pInternalBlock[BEAM_FORMING_INTERNAL_STEERING_MATRIX_IDX],
        context->transposePitch,
        context->kernelCtrlArgs.numDetections,
        context->kernelCtrlArgs.numAntennas,
        context->kernelCtrlArgs.numAngles,
        context->kernelCtrlArgs.beamFormingScaling);

    vcop_beam_energy_calculation_kernel(
         context->pMatMulOutput,
         context->pEnergy,
         context->kernelCtrlArgs.numDetections,
         ALIGN(context->kernelCtrlArgs.numAngles, 2U));


    vcop_beam_angle_association_kernel(
         context->pEnergy,
         (uint8_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_OUT_ANGLE_IDX] +
          context->currDetectionIdx * sizeof(uint16_t),
         (uint8_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_OUT_ENERGY_IDX] +
         context->currDetectionIdx * sizeof(uint16_t),
         NULL,/* For host emulation this field is not used */
         NULL,/* For host emulation this field is not used */
         context->pBeamFormingInfo[context->pingPongFlag]->baseAngleOffset,
         context->kernelCtrlArgs.numDetections,
         context->kernelCtrlArgs.numAngles,
         context->kernelCtrlArgs.energyScaling);

    context->currDetectionIdx += context->pBeamFormingInfo[context->pingPongFlag]->numValidDetection;

#else
  if ( context->enableSMCopy )
  {
    vcop_beam_forming_copy_steering_matrix_kernel_vloops(context->pBlockSteeringMatCopy);
  }
  vcop_beam_forming_transpose_antenna_data_kernel_vloops(context->pBlockTranspose);
  vcop_beam_forming_kernel_vloops(context->pBlockBeamForming);
  vcop_beam_energy_calculation_kernel_vloops(context->pBlockEnergyCal);
  vcop_beam_angle_association_kernel_vloops(context->pBlockAngleAssociation);
#endif

  if ( (*context->kernelCtrlArgs.enableSMcopyShared) == 1U)
  {
    context->enableSMCopy = 1U;
  }
  else
  {
    context->enableSMCopy = 0U;
  }

  context->pingPongFlag ^= 1U;

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_BeamForming_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_BeamForming_Context *context = (BAM_BeamForming_Context *) kernelContext;

  BAM_BeamForming_CtrlArgs * args = (BAM_BeamForming_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  if ( args->cmdId == BAM_BEAM_FORMING_CTRL_CMD_ID_SET_PARAMS)
  {
    BAM_BeamForming_InCtrlArgs * inCtrlArgs = (BAM_BeamForming_InCtrlArgs *)args->ctrlArgs;
    context->kernelCtrlArgs = *inCtrlArgs;
  }
  else if ( args->cmdId == BAM_BEAM_FORMING_CTRL_CMD_ID_GET_WBUF_PTR)
  {
    BAM_BeamForming_OutCtrlArgs * outCtrlArgs = (BAM_BeamForming_OutCtrlArgs *)args->ctrlArgs;
    outCtrlArgs->WBUFptrToAngleBuf          = (uint16_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_OUT_ANGLE_IDX];
    outCtrlArgs->WBUFptrToEnergyBuf         = (uint16_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_OUT_ENERGY_IDX];
    /* This pointer is to re-use to memory allocated for param block for other kernels outside the graph */
    outCtrlArgs->WBUFpBlockPtr              = (uint16_t *)context->pInternalBlock[BEAM_FORMING_INTERNAL_PARAMS_IDX];
  }
  else
  {
    status = BAM_E_FAIL;
  }

  return status;
}


BAM_KernelExecFuncDef gBAM_TI_beamFormingExecFunc =
{
  NULL,
  &Bam_BeamForming_initFrame,
  &Bam_BeamForming_computeFrame,
  NULL,
  &Bam_BeamForming_control,
  NULL
};


