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
* @file bam_orientation_binning_exec_funcs.c
*
* @brief
*
* @author Anshu Jain(anshu.jain@ti.com)
*
* @version 0.0 (Aug 2013) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>
#include <math.h>

#include "bam_orientation_binning_helper_funcs.h"
#include "vcop_orientation_binning_kernel.h"

typedef float   float32_t;
typedef double  double64_t;


#define TB_PI       ((double64_t)3.14159265358979323846)
#define MAX_NUM_BINS (32)
BAM_Status BAM_orientation_binning_initInstance
(
    void *kernelContext
);
BAM_Status BAM_orientation_binning_initFrame
(
    void *kernelContext
);
BAM_Status BAM_orientation_binning_computeFrame
(
    void *kernelContext
);
/**
*******************************************************************************
* @fn        BAM_orientation_binning_initInstance
* @brief    Function for Sequnce level Initialization
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/

BAM_Status BAM_orientation_binning_initInstance
(
    void *kernelContext
)
{
    BAM_orientation_binning_Context *context = (BAM_orientation_binning_Context*)kernelContext;
    int16_t (*sinTabPtr)[MAX_NUM_BINS];
    int16_t (*cosTabPtr)[MAX_NUM_BINS];
    int16_t i;
    uint32_t totalNumBins = (context->kernelArgs.numBins*2U);
    double64_t startAngle = (double64_t)(TB_PI/(double64_t)totalNumBins);
    double64_t value;
    double64_t sinValue;
    double64_t cosValue;
    sinTabPtr = (int16_t (*)[MAX_NUM_BINS])(void *)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX];
    cosTabPtr = (int16_t (*)[MAX_NUM_BINS])(void *)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX];




  for(i = 0; i < context->kernelArgs.numBins; i++)
  {
    value = (double64_t)sin(((double64_t)i*(TB_PI/((double64_t)context->kernelArgs.numBins))) + startAngle);
    sinValue = (double64_t)((double64_t)value * (double64_t)((uint32_t)1 << 15));
    (*sinTabPtr)[i] = (int16_t)sinValue;
    value = (double64_t)cos(((double64_t)i*(TB_PI/((double64_t)context->kernelArgs.numBins))) + startAngle);
    cosValue = (double64_t)((double64_t)value * (double64_t)((uint32_t)1 << 15));
    (*cosTabPtr)[i] = (int16_t)cosValue;
  }
  return 0;
}


/**
*******************************************************************************
* @fn        BAM_orientation_binning_initFrame
* @brief    Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/

BAM_Status BAM_orientation_binning_initFrame
(
    void *kernelContext
)
{
    BAM_orientation_binning_Context *context = (BAM_orientation_binning_Context*)kernelContext;
#if (!VCOP_HOST_EMULATION)
    if(context->kernelArgs.numBins & 1U)
    {
      vcop_orientation_binning_init(
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADX_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADY_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (uint8_t*)context->pOutBlock[ORIENTATION_BINNING_OUT_BIN_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            context->kernelArgs.numBins,
                            context->kernelArgs.blockW,
                            context->kernelArgs.blockH,
                            context->kernelArgs.pitch,
                            (uint16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX]
                           );
      context->kernelCustom = &vcop_orientation_binning_vloops;
    }
    else
    {
      vcop_orientation_binning_even_init(
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADX_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADY_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (uint8_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_ABS_GRADX_IDX],
                            (uint8_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_ABS_GRADY_IDX],
                            (uint8_t*)context->pOutBlock[ORIENTATION_BINNING_OUT_BIN_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            context->kernelArgs.numBins,
                            context->kernelArgs.blockW,
                            context->kernelArgs.blockH,
                            context->kernelArgs.pitch,
                            (uint16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX]
                           );

      context->kernelCustom = &vcop_orientation_binning_even_vloops;
    }
#endif

    return 0;
}


/**
*******************************************************************************
* @fn       BAM_bop_compute_features_computeFrame
* @brief    Function to call Vloop
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_orientation_binning_computeFrame
(
    void *kernelContext
)
{
    BAM_orientation_binning_Context *context = (BAM_orientation_binning_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_orientation_binning(
            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADX_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADY_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pOutBlock[ORIENTATION_BINNING_OUT_BIN_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.numBins,
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.pitch
           );
#else
      context->kernelCustom(context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX]);
#endif

 return 0;
}

BAM_KernelExecFuncDef gBAM_TI_orientation_binningExecFunc =
{
    &BAM_orientation_binning_initInstance,    /* kernelInitInstance   */
    &BAM_orientation_binning_initFrame,                                      /* kernelInitFrame      */
    &BAM_orientation_binning_computeFrame, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    NULL                                       /* Custom               */
};


