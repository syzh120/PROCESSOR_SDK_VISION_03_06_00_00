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
 * @file isp_bam_image_bayer2rgb_Exec_Funcs.c
 *
 * @brief This file contains all kernel Exce functions for Bayer to RGB coversion
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 * @version 0.0 (November 2012) : Base version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "vcop_BayerCFA_interpolate_kernel.h"
#include "bam_image_bayer2rgb_helper_funcs.h"

/* Function Prototypes */
static BAM_Status BAM_Image_bayer2rgb_initFrame(void *kernelContext);
static BAM_Status BAM_Image_bayer2rgb_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_bayer2rgb_initFrame
 * @brief    Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_bayer2rgb_initFrame(void *kernelContext)
{
    BAM_Image_bayer2rgb_Context *context = (BAM_Image_bayer2rgb_Context *) kernelContext;

    if(context->kernelArgs.bayerFormat == BGGR)
    {
        vcop_BayerCFA_interpolate_short_BGGR_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == GBRG)
    {
        vcop_BayerCFA_interpolate_short_GBRG_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == GRBG)
    {
        vcop_BayerCFA_interpolate_short_GRBG_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == RGGB)
    {
        vcop_BayerCFA_interpolate_short_RGGB_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else
    {
    }

    return 0;
}

/**
 *******************************************************************************
 * @fn        BAM_Image_bayer2rgb_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_bayer2rgb_computeFrame(void *kernelContext)
{
    BAM_Image_bayer2rgb_Context *context = (BAM_Image_bayer2rgb_Context *) kernelContext;

    if(context->kernelArgs.bayerFormat == BGGR)
    {
        vcop_BayerCFA_interpolate_short_BGGR_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == GBRG)
    {
        vcop_BayerCFA_interpolate_short_GBRG_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == GRBG)
    {
        vcop_BayerCFA_interpolate_short_GRBG_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == RGGB)
    {
        vcop_BayerCFA_interpolate_short_RGGB_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
    }

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_bayer2rgbExecFunc =
{
        NULL,
        &BAM_Image_bayer2rgb_initFrame,
        &BAM_Image_bayer2rgb_computeFrame,
        NULL,
        NULL,
        NULL
};

