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
 *  @file       bam_multiblock_bilinear_interp_intlv_7x7_s16_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 signed 16-bit gradient
 *              pixel data which includes gradient along X and Y directions in
 *              interleaved format into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_multiblock_bilinear_interp_intlv_7x7_s16_int.h"
#include "bam_multiblock_bilinear_interp_intlv_7x7_s16.h"
#include "vcop_multiblock_bilinear_interp_intlv_7x7_s16_kernel.h" /* compiler should take care of include path */
#include "vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_initFrame(void *kernelContext);
static BAM_Status Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_initFrame(void *kernelContext)
{
    BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *context = (BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *) kernelContext;
    BAM_Status status = 0;
    int32_t shiftValue = 2*(VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);

    /* Return error if assumptions in kernel are not satisfied*/
    if(((context->kernelArgs.input1Stride) < 1) || ((context->kernelArgs.outputStride) < 1) ||
        ((context->kernelArgs.blkWidth) < 1) || ((context->kernelArgs.blkHeight) < 1) ||
        ((context->kernelArgs.numKeyPoints) < 1) || ((context->kernelArgs.input2Stride) < 1) ||
        ((context->kernelArgs.blkOffset/context->kernelArgs.input1Stride) < (context->kernelArgs.blkHeight))) {
        status = 1;
    }
    if(shiftValue > 16)
    {
      shiftValue = 16;
    }
    if(status == 0) {
        vcop_multiblock_bilinear_interp_intlv_7x7_s16_init((int16_t*)context->pInBlock[IN_IDX1],
                               (uint16_t*)context->pInBlock[IN_IDX2],
                               (int16_t*)context->pOutBlock[OUT_IDX1],
                               (int16_t*)context->pOutBlock[OUT_IDX2],
                               context->kernelArgs.input1Stride,
                               context->kernelArgs.input2Stride,
                               context->kernelArgs.outputStride,
                               context->kernelArgs.blkWidth,
                               context->kernelArgs.blkHeight,
                               context->kernelArgs.blkOffset,
                               (uint16_t)shiftValue,
                               context->kernelArgs.numKeyPoints,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_computeFrame(void *kernelContext);

static BAM_Status Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_computeFrame(void *kernelContext)
{
    BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *context = (BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *) kernelContext;
    BAM_Status status = 0;
    int shiftValue = 2*(VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);
    if(shiftValue > 16)
    {
      shiftValue = 16;
    }
    vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn((int16_t*)context->pInBlock[IN_IDX1],
                           (uint16_t*)context->pInBlock[IN_IDX2],
                           (int16_t*)context->pOutBlock[OUT_IDX1],
                           (int16_t*)context->pOutBlock[OUT_IDX2],
                           context->kernelArgs.input1Stride,
                           context->kernelArgs.input2Stride,
                           context->kernelArgs.outputStride,
                           context->kernelArgs.blkWidth,
                           context->kernelArgs.blkHeight,
                           context->kernelArgs.blkOffset,
                           shiftValue,
                           context->kernelArgs.numKeyPoints);

    return status;
}
#endif

static BAM_Status Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *context = (BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *) kernelContext;
  BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Ctrl_Args *args  = (BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Ctrl_Args *) ctlArg;
  context->kernelArgs.ctrlPtr = *args;
  return status;
}

BAM_KernelExecFuncDef gBAM_TI_multiblockBilinearInterpIntlv7x7S16ExecFunc =
#ifdef NATC
    { NULL, &Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_initFrame, &Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_computeFrame, NULL, &Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_control, NULL };
#else
    { NULL, &Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_initFrame, NULL, NULL, &Bam_Multiblock_Bilinear_Interp_Intlv_7x7_S16_control, &vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops };
#endif
