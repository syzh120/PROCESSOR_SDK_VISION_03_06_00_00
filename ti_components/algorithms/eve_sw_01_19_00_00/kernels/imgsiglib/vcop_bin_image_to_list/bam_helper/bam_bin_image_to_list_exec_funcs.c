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
 *  @file       bam_bin_image_to_list_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating binary image to
 *              (X, Y) co-ordinate list creation function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_bin_image_to_list_int.h"
#include "vcop_bin_image_to_list_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Bin_image_to_list_initFrame(void *kernelContext);

static BAM_Status Bam_Bin_image_to_list_initFrame(void *kernelContext)
{
    BAM_Bin_image_to_list_Context *context = (BAM_Bin_image_to_list_Context *) kernelContext;
    uint32_t i, XYincr;
    uint32_t (*xseq)[];
    uint32_t (*pStartIdx)[];

    xseq = (uint32_t (*)[])context->pInternalBlock[XSEQ_IDX];
    pStartIdx = (uint32_t (*)[])context->pInternalBlock[STARTXY_IDX];

    if ( context->kernelArgs.xyOrder == BAM_BIN_IMAGE_TO_LIST_XY )
    {
      context->outputQformat = context->kernelArgs.outputQformat;
      for(i = 0; i < context->kernelArgs.blkWidth; i++) {
          (*xseq)[i] = i<<(16U + context->kernelArgs.outputQformat);
      }

      XYincr = ((uint32_t)context->kernelArgs.frameStartX << (16U + context->kernelArgs.outputQformat)) +
                    ((uint32_t)context->kernelArgs.frameStartY << context->kernelArgs.outputQformat) ;
    }
    else
    {
      /* To put Y in upper bytes add a shift of 16 */
      context->outputQformat = context->kernelArgs.outputQformat + 16U;

      /* To put X in lower bytes do not shift X */
      for(i = 0; i < context->kernelArgs.blkWidth; i++) {
          (*xseq)[i] = i<<(context->kernelArgs.outputQformat);
      }
      XYincr = ((uint32_t)context->kernelArgs.frameStartY << (16U + context->kernelArgs.outputQformat)) +
                    ((uint32_t)context->kernelArgs.frameStartX << context->kernelArgs.outputQformat) ;
    }
    (*pStartIdx)[0] = XYincr;

#if (!VCOP_HOST_EMULATION)
      vcop_bin_image_to_list_init((uint8_t*)context->pInBlock[IN_IMG_IDX],
                                 (uint32_t*)context->pInternalBlock[STARTXY_IDX],
                                 (uint32_t*)context->pOutBlock[OUT_XY_IDX],
                                 (uint32_t*)context->pOutBlock[OUT_SIZE_IDX],
                                 context->kernelArgs.blkWidth,
                                 context->kernelArgs.blkHeight,
                                 context->kernelArgs.blkStride,
                                 context->outputQformat,
                                 (uint32_t*)context->pInternalBlock[XSEQ_IDX],
                                 (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif

    return 0;
}

#if VCOP_HOST_EMULATION
static BAM_Status Bam_Bin_image_to_list_computeFrame(void *kernelContext)
{
    BAM_Bin_image_to_list_Context *context = (BAM_Bin_image_to_list_Context *) kernelContext;

    vcop_bin_image_to_list((uint8_t*)context->pInBlock[IN_IMG_IDX],
                               (uint32_t*)context->pInternalBlock[STARTXY_IDX],
                               (uint32_t*)context->pOutBlock[OUT_XY_IDX],
                               (uint32_t*)context->pOutBlock[OUT_SIZE_IDX],
                               context->kernelArgs.blkWidth,
                               context->kernelArgs.blkHeight,
                               context->kernelArgs.blkStride,
                               context->outputQformat,
                               (uint32_t*)context->pInternalBlock[XSEQ_IDX]);
    return 0;

}
#endif


static BAM_Status Bam_Bin_image_to_list_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status Bam_Bin_image_to_list_control(void *kernelContext, void *kernelCtlArg){

    BAM_Bin_image_to_list_Context *context = (BAM_Bin_image_to_list_Context *) kernelContext;
    BAM_Bin_image_to_list_ctrlArgs *ctlArg= (BAM_Bin_image_to_list_ctrlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.frameStartX   = ctlArg->frameStartX;
    context->kernelArgs.frameStartY   = ctlArg->frameStartY;
    context->kernelArgs.blkWidth      = ctlArg->blkWidth;
    context->kernelArgs.blkHeight     = ctlArg->blkHeight;
    context->kernelArgs.blkStride     = ctlArg->blkStride;
    context->kernelArgs.outputQformat = ctlArg->outputQformat;
    context->kernelArgs.xyOrder       = ctlArg->xyOrder;

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_binImageToListExecFunc =
#if VCOP_HOST_EMULATION
{
    NULL,
    &Bam_Bin_image_to_list_initFrame,
    &Bam_Bin_image_to_list_computeFrame,
    NULL,
    &Bam_Bin_image_to_list_control,
    NULL
};
#else
{
  NULL,
  &Bam_Bin_image_to_list_initFrame,
  NULL,
  NULL,
  &Bam_Bin_image_to_list_control,
  &vcop_bin_image_to_list_vloops };
#endif

