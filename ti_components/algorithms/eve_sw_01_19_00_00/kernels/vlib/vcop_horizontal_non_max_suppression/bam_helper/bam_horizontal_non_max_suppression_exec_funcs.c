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
 *  @file       bam_horizontal_non_max_suppression_exec_funcs.c
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (May 2014) : Updated as per control node requirements
 *  @brief      This file defines interfaces for integrating block statistics
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_horizontal_non_max_suppression_int.h"
#include "bam_horizontal_non_max_suppression.h"
#include "vcop_horizontal_non_max_suppression_kernel.h" /* compiler should take care of include path */
#include "edma_utils_memcpy.h"

/* Function Prototypes */
static BAM_Status Bam_Horizontal_Non_Max_Suppression_initFrame(void *kernelContext);

static BAM_Status Bam_Horizontal_Non_Max_Suppression_initFrame(void *kernelContext)
{
    BAM_Horizontal_Non_Max_Suppression_Context *context = (BAM_Horizontal_Non_Max_Suppression_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t maxCorners;

    EDMA_UTILS_memcpy2D(context->pInternalBlock[ID_IDX],
                        (const void *)ID_EXT_IDX,
                        (uint16_t)sizeof(ID_EXT_IDX),
                        1U,
                        0,
                        0);

#if (!VCOP_HOST_EMULATION)
    maxCorners = context->kernelArgs.max_corners <= context->kernelArgs.num_corners_in ? (context->kernelArgs.num_corners_in + 8) : context->kernelArgs.max_corners;
    vcop_horizontal_non_max_suppression_init((uint32_t *)context->pInBlock[IN_XY_IDX],
                                              context->kernelArgs.num_corners_in,
                                              maxCorners,
                                             (uint16_t *)context->pInBlock[IN_SCORE_IDX],
                                             (uint32_t *)context->pOutBlock[OUT_XY_IDX],
                                             (uint16_t *)context->pOutBlock[OUT_SCORE_IDX],
                                             (uint8_t *)context->pInternalBlock[ID_IDX],
                                             context->pInternalBlock[PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Horizontal_Non_Max_Suppression_compute(void *kernelContext);

static BAM_Status Bam_Horizontal_Non_Max_Suppression_compute(void *kernelContext)
{
    BAM_Horizontal_Non_Max_Suppression_Context *context = (BAM_Horizontal_Non_Max_Suppression_Context *) kernelContext;
    BAM_Status status = 0;

    uint32_t maxCorners;
    maxCorners = context->kernelArgs.max_corners <= context->kernelArgs.num_corners_in ? (context->kernelArgs.num_corners_in + 8) : context->kernelArgs.max_corners;
    vcop_horizontal_non_max_suppression((unsigned int*)context->pInBlock[IN_XY_IDX],
                                         context->kernelArgs.num_corners_in,
                                         maxCorners,
                                         (unsigned short*)context->pInBlock[IN_SCORE_IDX],
                                         (unsigned int*)context->pOutBlock[OUT_XY_IDX],
                                         (unsigned short*)context->pOutBlock[OUT_SCORE_IDX],
                                         (unsigned char*)context->pInternalBlock[ID_IDX]);

    return status;
}
#endif

static BAM_Status Bam_Horizontal_Non_Max_Suppression_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status Bam_Horizontal_Non_Max_Suppression_control(void *kernelContext, void *kernelCtlArg)
{
    BAM_Horizontal_Non_Max_Suppression_Context *context = (BAM_Horizontal_Non_Max_Suppression_Context *) kernelContext;
    BAM_Horizontal_Non_Max_Suppression_ctrlArgs *ctlArg = (BAM_Horizontal_Non_Max_Suppression_ctrlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.num_corners_in = ctlArg->num_corners_in;

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_horizontalnonmaxsuppressionExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL, &Bam_Horizontal_Non_Max_Suppression_initFrame, NULL, NULL, &Bam_Horizontal_Non_Max_Suppression_control, &vcop_horizontal_non_max_suppression_vloops };
#else
    { NULL, &Bam_Horizontal_Non_Max_Suppression_initFrame, &Bam_Horizontal_Non_Max_Suppression_compute, NULL, &Bam_Horizontal_Non_Max_Suppression_control, NULL };
#endif
