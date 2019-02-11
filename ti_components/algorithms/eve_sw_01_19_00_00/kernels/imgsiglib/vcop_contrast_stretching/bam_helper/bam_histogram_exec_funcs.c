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
 *  @file       bam_histogram_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_histogram_int.h"
#include "bam_histogram.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Histogram_initFrame(void *kernelContext);
static BAM_Status Bam_Histogram_computeFrame(void *kernelContext);
static BAM_Status Bam_Histogram_control(void *kernelContext,
                                                        void * kernelCtlArg);

static BAM_Status Bam_Histogram_initFrame(void *kernelContext)
{
  BAM_Histogram_Context *context = (BAM_Histogram_Context *) kernelContext;

  context->blockCnt = 0;

  vcop_memset((uint32_t *)context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX],
              0,
              HISTOGRAM_NUM_BINS * sizeof(uint32_t) * HISTOGRAM_NUM_COPIES);

#if (!VCOP_HOST_EMULATION)
  vcop_histogram_8c_word_init(
    context->pInBlock[BAM_HISTOGRAM_INPUT_BLOCK_PORT],
    context->kernelArgs.blkWidth,
    context->kernelArgs.blkHeight,
    context->kernelArgs.inPitch,
    context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX],
    context->pInternalBlock[HISTOGRAM_INTERNAL_PARAMS_IDX]
  );
#endif

    return 0;
}

static BAM_Status Bam_Histogram_computeFrame(void *kernelContext)
{
    BAM_Histogram_Context *context = (BAM_Histogram_Context *) kernelContext;

  if ( context->blockCnt < context->totalBlockCnt)
  {
#if (!VCOP_HOST_EMULATION)
    vcop_histogram_8c_word_vloops(context->pInternalBlock[HISTOGRAM_INTERNAL_PARAMS_IDX]);
#else
    vcop_histogram_8c_word(
      context->pInBlock[BAM_HISTOGRAM_INPUT_BLOCK_PORT],
      context->kernelArgs.blkWidth,
      context->kernelArgs.blkHeight,
      context->kernelArgs.inPitch,
      context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX]
    );
#endif
  }

  context->blockCnt++;
  return 0;
}

static BAM_Status Bam_Histogram_control(void *kernelContext,
                                                        void * kernelCtlArg)
{

  BAM_Histogram_Context *context = (BAM_Histogram_Context *) kernelContext;

  BAM_Histogram_CtrlArgs * args = (BAM_Histogram_CtrlArgs *)kernelCtlArg;

  if ( args->cmdId == BAM_HISTOGRAM_CTRL_CMDID_GET_HISTOGRAM8COPY_WBUF )
  {
    args->ctrlArgs = context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX];
  }

  if ( args->cmdId == BAM_HISTOGRAM_CTRL_CMDID_SET_IMAGE_HEIGHT )
  {
    BAM_Histogram_ImageDim_CtrlArgs * imageDims = ( BAM_Histogram_ImageDim_CtrlArgs *)
                                                            args->ctrlArgs;
    uint16_t numHorzBlock;
    uint16_t numVertBlock;
    numHorzBlock = imageDims->imageWidth/ context->kernelArgs.blkWidth;
    numVertBlock = imageDims->imageHeight/ context->kernelArgs.blkHeight;
    context->totalBlockCnt = numHorzBlock * numVertBlock;
  }

  return 0;
}


BAM_KernelExecFuncDef gBAM_TI_histogramExecFunc =
{
  NULL,
  &Bam_Histogram_initFrame,
  &Bam_Histogram_computeFrame,
  NULL,
  &Bam_Histogram_control,
  NULL
};

