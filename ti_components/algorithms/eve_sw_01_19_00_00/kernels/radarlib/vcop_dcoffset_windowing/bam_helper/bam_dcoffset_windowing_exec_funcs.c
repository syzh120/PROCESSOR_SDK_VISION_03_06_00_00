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
 *  @file       bam_dcoffset_windowing_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating DC offset, windowing kernels
 *                into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>


#include "bam_dcoffset_windowing_int.h"
#include "bam_dcoffset_windowing.h"
#include "vcop_dcoffset_windowing_kernel.h" /* compiler should take care of include path */

#include "edma_utils_memcpy.h"



/***********************************************************************************************/
/*                        Below are the helper  functions related to DC offset windowing and interference zero out kernels              */
/***********************************************************************************************/
static BAM_Status Bam_DcoffsetWindowing_initFrame(void *kernelContext);
static BAM_Status Bam_DcoffsetWindowing_computeFrame(void *kernelContext);

static BAM_Status Bam_DcoffsetWindowing_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_DcoffsetWindowing_initFrame(void *kernelContext)
{
  BAM_DcoffsetWindowing_Context *context = (BAM_DcoffsetWindowing_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;
  uint16_t (*pScatterIndex)[VCOP_SIMD_WIDTH];
  uint16_t (*pTransposeScatterIndex)[VCOP_SIMD_WIDTH];
  uint32_t i;
  uint32_t numKernels = 0;
  uint16_t tempPoints;
  uint32_t isWindowingRequired = 1U;
  uint32_t numWindowingPoints;
  uint16_t windowingScaleFactor = 0;

  context->configMask = 0;

  context->numAlignedPoints= ALIGN_SIMD(context->kernelCtrlArgs.numPoints);
  context->inputPitch      = context->kernelCtrlArgs.numPoints * 2U * sizeof(int16_t);

  if ( context->kernelCtrlArgs.enableSignExtension)
  {
    context->configMask = BAM_DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION;
  }
  if ( context->kernelCtrlArgs.enableInterferenceZeroOut)
  {
    context->configMask |= BAM_DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT;
  }
  if ( context->kernelCtrlArgs.enableDcoffset)
  {
    context->configMask |= BAM_DCOFFSET_WINDOWING_ENABLE_DCOFFSET;
    context->configMask |= BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING;
  }
  if ( context->kernelCtrlArgs.enableWindowing)
  {
    context->configMask |= BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING;
  }

  /* If nothing is enabled then we will do windowing to do the copy */
  if ( context->configMask == 0)
  {
    context->configMask = BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING;
  }
/* Following are the possible configuration
configMask   Windowing    DC Offset    InterferenceZeroOut   SignExtension
0                0                        0                0                        0
1                0                        0                0                        1
2                0                        0                1                        0
3                0                        0                1                        1
4                0                        1                0                        0
5                0                        1                0                        1
6                0                        1                1                        0
7                0                        1                1                        1
8                1                        0                0                        0
9                1                        0                0                        1
10                1                        0                1                        0
11                1                        0                1                        1
12                1                        1                0                        0
13                1                        1                0                        1
14                1                        1                1                        0
15                1                        1                1                        1

 Here 4,5,6,7 config is same as 12,13,14,15 as whenever DC offset is enabled
 windowing is automatically enabled
*/
  switch (context->configMask)
  {
    case 0 :
       context->configMask |= BAM_DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT;
       context->pInterferenceIn      = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
       context->pInterferenceOut     = (int16_t*) context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT];
       context->interferenceInPitch  = context->inputPitch;
       context->interferenceOutPitch = context->kernelCtrlArgs.winOutputPitch;
       break;
    case 1 :
      context->pSignExtOutput  = (int16_t*) context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT];
      context->signExtInPitch  = context->inputPitch;
      context->signExtOutPitch = context->kernelCtrlArgs.winOutputPitch;
      break;
    case 2:
      context->pInterferenceIn      = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->pInterferenceOut     = (int16_t*) context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT];
      context->interferenceInPitch  = context->inputPitch;
      context->interferenceOutPitch = context->kernelCtrlArgs.winOutputPitch;
      break;
    case 3:
      context->pSignExtOutput  = (int16_t*) context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->signExtInPitch  = context->inputPitch;
      context->signExtOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->pInterferenceIn      = context->pSignExtOutput;
      context->pInterferenceOut     = (int16_t*) context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT];
      context->interferenceInPitch  =  context->signExtOutPitch;
      context->interferenceOutPitch = context->kernelCtrlArgs.winOutputPitch;
      break;
    case 8:
      context->pWindowingIn         = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->winInputPitch      = context->inputPitch;
      break;
    case 9 :
      context->pSignExtOutput  = (int16_t*) context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->signExtInPitch  = context->inputPitch;
      context->signExtOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->pWindowingIn         = context->pSignExtOutput;
      context->winInputPitch      = context->signExtOutPitch;
      break;
    case 10 :
      context->pInterferenceIn      = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->pInterferenceOut     = (int16_t*)context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->interferenceInPitch  = context->inputPitch;
      context->interferenceOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->pWindowingIn         = context->pInterferenceOut;
      context->winInputPitch      = context->interferenceOutPitch;
      break;
    case 11 :
      context->pSignExtOutput  = (int16_t*) context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->signExtInPitch  = context->inputPitch;
      context->signExtOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->pInterferenceIn      = context->pSignExtOutput;
      context->pInterferenceOut     = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->interferenceInPitch  =  context->signExtOutPitch;
      context->interferenceOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->pWindowingIn         = context->pInterferenceOut;
      context->winInputPitch        = context->interferenceOutPitch;
      break;
    case 12 :
      context->pWindowingIn         = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->dcOffsetInPitch      = context->inputPitch;
      context->winInputPitch        = context->inputPitch;
      break;
    case 13:
      context->pSignExtOutput  = (int16_t*) context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->signExtInPitch  = context->inputPitch;
      context->signExtOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->dcOffsetInPitch = context->signExtOutPitch;

      context->pWindowingIn         = context->pSignExtOutput;
      context->winInputPitch        = context->signExtOutPitch;

      break;
    case 14:
      context->pInterferenceIn      = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->pInterferenceOut     = (int16_t*) context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->interferenceInPitch  = context->inputPitch;
      context->interferenceOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->dcOffsetInPitch      = context->interferenceOutPitch;

      context->pWindowingIn         = context->pInterferenceOut;
      context->winInputPitch        = context->interferenceOutPitch;
      break;
    case 15:
      context->pSignExtOutput  = (int16_t*) context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX];
      context->signExtInPitch  = context->inputPitch;
      context->signExtOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->pInterferenceIn      = context->pSignExtOutput;
      context->pInterferenceOut     = (int16_t*)context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT];
      context->interferenceInPitch  =  context->signExtOutPitch;
      context->interferenceOutPitch = context->numAlignedPoints * sizeof(int16_t) * 2U;

      context->dcOffsetInPitch      = context->interferenceOutPitch;

      context->pWindowingIn         = context->pInterferenceOut;
      context->winInputPitch        = context->interferenceOutPitch;

      break;
    default :
      status = BAM_E_FAIL;
      break;
  }

  if ( status == BAM_E_FAIL)
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }
  context->numKernels = 0;
  pScatterIndex = (uint16_t (*)[VCOP_SIMD_WIDTH])context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX];
  pTransposeScatterIndex  = (uint16_t (*)[VCOP_SIMD_WIDTH])context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX];

  context->shift = 0;
  tempPoints = context->numAlignedPoints;

  while (tempPoints != 0)
  {
    tempPoints = tempPoints / 2U;
    context->shift++;
  }
  context->shift = context->shift - 1U;

  if ( context->kernelCtrlArgs.numLines < VCOP_SIMD_WIDTH)
  {
    context->interimTransposeStride = ( (2U * VCOP_SIMD_WIDTH) + 1U ) * sizeof(uint32_t);
  }
  else
  {
    context->interimTransposeStride = ((context->kernelCtrlArgs.numLines * 2U) + 1U) *   sizeof(uint32_t);
  }

  for ( i = 0 ; i < VCOP_SIMD_WIDTH; i++)
  {
    (*pScatterIndex)[i] = (uint16_t)context->interimTransposeStride * (uint16_t)i;
    (*pTransposeScatterIndex)[i] = (uint16_t)context->kernelCtrlArgs.winOutputPitch * (uint16_t)i;
  }

  numWindowingPoints = context->numAlignedPoints;
  /* When tranpose in enable it indicates that windowing coefficients have to be applied in vertical direction */
  if ( context->kernelInitArgs.enableTranspose == 1U )
  {
    numWindowingPoints = context->kernelCtrlArgs.numLines;
  }

  if (  context->kernelCtrlArgs.enableWindowing == 0 )
  {
    int16_t (*windowingCoeff)[BAM_DCOFFSET_WINDOWING_MAX_NUM_POINTS] = (int16_t (*)[BAM_DCOFFSET_WINDOWING_MAX_NUM_POINTS])context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX];
    /* if windowing is disabled but DC offset is enable make all windowing coefficients as 1 */
    for ( i = 0; i < numWindowingPoints ; i++)
    {
      (*windowingCoeff)[i] = (int16_t)1;
    }
    windowingScaleFactor = 0;
  }
  else
  {
    /* Otherwise copy user provided buffer for windowcoefficients */
    EDMA_UTILS_memcpy2D(context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX],
          context->kernelCtrlArgs.windowingCoefficients,
          (uint16_t)sizeof(int16_t) * (uint16_t)numWindowingPoints,
          1U, 0, 0);
    windowingScaleFactor = context->kernelCtrlArgs.scaleFactor;
  }

  if (  (context->kernelCtrlArgs.enableDcoffset == 0 ) && (context->kernelInitArgs.enableTranspose == 0))
  {
    /* if user disable DC offset initialize dc offset to be zero */
    memset (context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX], 0 , context->kernelCtrlArgs.numLines * sizeof(int32_t));
  }


#if (!VCOP_HOST_EMULATION)
  context->pBlockInterferenceZeroOut = (uint16_t *)context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_PARAMS_IDX];
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->pBlockDcOffset  = context->pBlockInterferenceZeroOut + vcop_interference_zero_out_kernel_param_count();
  context->pBlockSignExtension = context->pBlockDcOffset + vcop_dcoffset_kernel_param_count();
  context->pBlockWindowing = context->pBlockSignExtension + vcop_sign_extension_kernel_param_count();

  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  if ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION)
  {
    vcop_sign_extension_kernel_init(context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT],
                               context->pSignExtOutput,
                               context->numAlignedPoints,
                               context->kernelCtrlArgs.numLines,
                               context->signExtInPitch,
                               context->signExtOutPitch,
                               context->kernelCtrlArgs.numInBits,
                               context->pBlockSignExtension
                               );

    /* Store the function pointer and corresponding pBlock to be called later */
     context->execFunc[numKernels] = &vcop_sign_extension_kernel_vloops;
     context->kernelContext[numKernels] = (BAM_DcoffsetWindowing_KernelContextType)context->pBlockSignExtension;
     numKernels++;

     /* As sign extension is enabled hence windowing is not required untill unless user requests for  it */
    isWindowingRequired = 0;
  }
  if ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT)
  {
    vcop_interference_zero_out_kernel_init(
      context->pInterferenceIn,/*IBUFLA*/
      context->pInterferenceOut,/*IBUFHA*/
      context->kernelCtrlArgs.interferenceThreshold,
      context->numAlignedPoints,
      context->kernelCtrlArgs.numLines,
      context->interferenceInPitch,
      context->interferenceOutPitch,
      context->pBlockInterferenceZeroOut );

    /* Store the function pointer and corresponding pBlock to be called later */
    context->execFunc[numKernels] = &vcop_interference_zero_out_kernel_vloops;
    context->kernelContext[numKernels] = (BAM_DcoffsetWindowing_KernelContextType)context->pBlockInterferenceZeroOut;
    numKernels++;

    /* As interference zero out is enabled hence windowing is not required untill unless user requests for  it */
    isWindowingRequired = 0;

  }

  if ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_DCOFFSET)
  {
    vcop_dcoffset_kernel_init(
        context->pWindowingIn,
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_SCRATCH_IDX],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX],
        context->dcOffsetInPitch,
        context->interimTransposeStride,
        context->numAlignedPoints,
        context->kernelCtrlArgs.numLines,
        context->shift,
        context->pBlockDcOffset);
    /* Store the function pointer and corresponding pBlock to be called later */
    context->execFunc[numKernels] = &vcop_dcoffset_kernel_vloops;
    context->kernelContext[numKernels] = (BAM_DcoffsetWindowing_KernelContextType)context->pBlockDcOffset;
    numKernels++;
  }


  /* Windowing kernel does both substraction of dcOffset and windowing and hence if either of dcOffset or windowing is
  enabled we should call this function */
  if ( ( (context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING) ==
          BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING) || (isWindowingRequired == 1U))
  {
    if ( context->kernelInitArgs.enableTranspose)
    {
      vcop_windowing_with_transpose_kernel_init(
        context->pWindowingIn,
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX],
        context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX],
        context->winInputPitch,
        context->kernelCtrlArgs.winOutputPitch,
        context->numAlignedPoints,
        context->kernelCtrlArgs.numLines,
        windowingScaleFactor,
        context->kernelCtrlArgs.saturationLimit,
        context->pBlockWindowing);
       /* Store the function pointer and corresponding pBlock to be called later */
      context->execFunc[numKernels] = &vcop_windowing_with_transpose_kernel_vloops;
    }
    else
    {
      vcop_windowing_kernel_init(
        context->pWindowingIn,
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX],
        context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT],
        context->numAlignedPoints,
        context->kernelCtrlArgs.numLines,
        windowingScaleFactor,
        context->kernelCtrlArgs.saturationLimit,
        context->winInputPitch,
        context->kernelCtrlArgs.winOutputPitch,
        context->pBlockWindowing);
       /* Store the function pointer and corresponding pBlock to be called later */
      context->execFunc[numKernels] = &vcop_windowing_kernel_vloops;
    }
    context->kernelContext[numKernels] = (BAM_DcoffsetWindowing_KernelContextType)context->pBlockWindowing;
    numKernels++;
  }
  context->numKernels = numKernels;
#endif
EXIT:
    return status;
}


static BAM_Status Bam_DcoffsetWindowing_computeFrame(void *kernelContext)
{
  BAM_DcoffsetWindowing_Context *context = (BAM_DcoffsetWindowing_Context *)kernelContext;
  uint32_t kernelIdx;

#if (VCOP_HOST_EMULATION)
  uint32_t isWindowingRequired = 1;
  int16_t windowingScaleFactor;

  if ( context->kernelCtrlArgs.enableWindowing == 0 )
  {
    windowingScaleFactor = 0;
  }
  else
  {
    windowingScaleFactor = context->kernelCtrlArgs.scaleFactor;
  }

  if ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION)
  {
    vcop_sign_extension_kernel(
      context->pInBlock[BAM_DCOFFSET_WINDOWING_INPUT_PORT],
      context->pSignExtOutput,
      context->numAlignedPoints,
      context->kernelCtrlArgs.numLines,
      context->signExtInPitch,
      context->signExtOutPitch,
      context->kernelCtrlArgs.numInBits);

     /* As sign extension is enabled hence windowing is not required untill unless user requests for  it */
    isWindowingRequired = 0;
  }

  if ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT)
  {
    vcop_interference_zero_out_kernel(
      context->pInterferenceIn,
      context->pInterferenceOut,
      context->kernelCtrlArgs.interferenceThreshold,
      context->numAlignedPoints,
      context->kernelCtrlArgs.numLines,
      context->interferenceInPitch,
      context->interferenceOutPitch);

    /* As interference zero out is enabled hence windowing is not required untill unless user requests for  it */
    isWindowingRequired = 0;
  }

  if ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_DCOFFSET)
  {
    vcop_dcoffset_kernel(
        context->pWindowingIn,
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_SCRATCH_IDX],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX],
        context->dcOffsetInPitch,
        context->interimTransposeStride,
        context->numAlignedPoints,
        context->kernelCtrlArgs.numLines,
        context->shift);
  }


  /* Windowing kernel does both substraction of dcOffset and windowing and hence if either of dcOffset or windowing is
  enabled we should call this function */
  if ( ( context->configMask & BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING) || (isWindowingRequired == 1U))
  {
    if ( context->kernelInitArgs.enableTranspose)
    {
      vcop_windowing_with_transpose_kernel(
        context->pWindowingIn,
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX],
        context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX],
        context->winInputPitch,
        context->kernelCtrlArgs.winOutputPitch,
        context->numAlignedPoints,
        context->kernelCtrlArgs.numLines,
        windowingScaleFactor,
        context->kernelCtrlArgs.saturationLimit);
    }
    else
    {
      vcop_windowing_kernel(
        context->pWindowingIn,
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX],
        context->pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX],
        context->pOutBlock[BAM_DCOFFSET_WINDOWING_OUTPUT_PORT],
        context->numAlignedPoints,
        context->kernelCtrlArgs.numLines,
        windowingScaleFactor,
        context->kernelCtrlArgs.saturationLimit,
        context->winInputPitch,
        context->kernelCtrlArgs.winOutputPitch);
    }
  }
#else
    for (kernelIdx = 0 ; kernelIdx < context->numKernels; kernelIdx++)
    {
      context->execFunc[kernelIdx](context->kernelContext[kernelIdx]);
    }
#endif

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_DcoffsetWindowing_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_DcoffsetWindowing_Context *context = (BAM_DcoffsetWindowing_Context *) kernelContext;

  BAM_DcoffsetWindowing_CtrlArgs * ctrlArgs = (BAM_DcoffsetWindowing_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}


BAM_KernelExecFuncDef gBAM_TI_dcoffsetWindowingExecFunc =
{
  NULL,
  &Bam_DcoffsetWindowing_initFrame,
  &Bam_DcoffsetWindowing_computeFrame,
  NULL,
  &Bam_DcoffsetWindowing_control,
  NULL
};


