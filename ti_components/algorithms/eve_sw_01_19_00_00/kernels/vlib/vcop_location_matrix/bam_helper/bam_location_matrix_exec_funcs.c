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
* @file bam_location_matrix_exec_funcs.c
*
* @brief
*
* @version 0.0 (Jan 2014) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_location_matrix_helper_funcs.h"
#include "vcop_location_matrix_kernel.h"
#define MAX_NUM_BINS (32)
BAM_Status BAM_location_matrix_computeFrame
(
    void *kernelContext
);
BAM_Status BAM_location_matrix_initFrame
(
    void *kernelContext
);
/**
*******************************************************************************
* @fn        BAM_location_matrix_initFrame
* @brief    Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_location_matrix_initFrame
(
    void *kernelContext
)
{
    BAM_location_matrix_Context *context = (BAM_location_matrix_Context*)kernelContext;
    uint8_t (*binIdx)[MAX_NUM_BINS] = (uint8_t (*)[MAX_NUM_BINS])(void*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX];
    uint8_t i;
    uint8_t numBinsBy2 = (uint8_t)((context->kernelArgs.numBins+(uint8_t)1)/(uint8_t)2);
    if(context->kernelArgs.gradientMagSize <= 2)
    {

    for(i =0; i < numBinsBy2; i++)
    {
      (*binIdx)[i*2U]   = i;
      (*binIdx)[(i*2U)+1U] = numBinsBy2 + i;
    }

#if (!VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMagSize == 1)
    {
      vcop_vec_L_matrix_u8_Mag_init(
              (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              context->kernelArgs.blockW,
              context->kernelArgs.blockH,
              context->kernelArgs.numBins,
              (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX],
              context->pInternalBlock[LOCATION_MATRIX_INTERNAL_PARAMS_IDX]
             );
      context->kernelCustom = &vcop_vec_L_matrix_u8_Mag_vloops;
    }
    else
    {
      vcop_vec_L_matrix_u16_Mag_init(
              (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              context->kernelArgs.blockW,
              context->kernelArgs.blockH,
              context->kernelArgs.numBins,
              (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX],
              context->pInternalBlock[LOCATION_MATRIX_INTERNAL_PARAMS_IDX]
             );
      context->kernelCustom = &vcop_vec_L_matrix_u16_Mag_vloops;
    }
#endif
    }
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
BAM_Status BAM_location_matrix_computeFrame
(
    void *kernelContext
)
{
    BAM_location_matrix_Context *context = (BAM_location_matrix_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMagSize == 1)
    {
     vcop_vec_L_matrix_u8_Mag(
            (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.numBins,
            (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX]);
     }
     else
     {
     vcop_vec_L_matrix_u16_Mag(
            (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.numBins,
            (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX]);
     }
#else
    context->kernelCustom(context->pInternalBlock[LOCATION_MATRIX_INTERNAL_PARAMS_IDX]);
#endif

    return 0;
}


BAM_KernelExecFuncDef gBAM_TI_location_matrixExecFunc =
{
    NULL,    /* kernelInitInstance   */
    &BAM_location_matrix_initFrame,                                      /* kernelInitFrame      */
    &BAM_location_matrix_computeFrame, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    NULL                                       /* Custom               */
};

