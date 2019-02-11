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
 *  @file       bam_image_rgb2yuv_exec_funcs.c
 *
 *  @brief      This file defines functions for integrating rgb2yuv kernels into BAM
 */

/**
 ********************************************************************************
 * @file isp_bam_image_rgb2yuv_Exec_Funcs.c
 *
 * @brief This file contains all kernel Exce functions for Bayer to RGB coversion
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 ********************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_image_rgb2yuv_helper_funcs.h"
#include "vcop_rgb_to_yuv_kernel.h" /* makerules should take care of include path */
#include "edma_utils_memcpy.h"


/* Function Prototypes */
static BAM_Status BAM_Image_rgb2yuv_initFrame(void *kernelContext);
static BAM_Status BAM_Image_rgb2yuv_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2yuv_initFrame
 * @brief    Function called during graph's instance initialization
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_rgb2yuv_initFrame(void *kernelContext)
{

    BAM_Image_rgb2yuv_Context *context = (BAM_Image_rgb2yuv_Context *) kernelContext;
    int16_t *coef= (int16_t*)(context->pInternalBlock[COEFS_IDX]);

    /* Sometimes memcpy is faster if number of bytes to transfer is small */
#if 0
    memcpy(context->pInternalBlock[COEFS_IDX], context->kernelArgs.rgb2yuv_coefs, sizeof(short)*25);
#else
    EDMA_UTILS_memcpy2D(context->pInternalBlock[COEFS_IDX], context->kernelArgs.rgb2yuv_coefs, sizeof(short)*25,
        1,0,0);
#endif



    if(context->kernelArgs.outputFormat == RGB2YUV_OUTPUT_UYVY)
    {
        rgb_to_yuv_UYVY_init((uint16_t *)context->pInBlock[IN_R_IDX],
                (uint16_t *)context->pInBlock[IN_G_IDX],
                (uint16_t *)context->pInBlock[IN_B_IDX],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.input_stride,
                coef[0],
                coef[1],
                coef[2],
                (int16_t *)coef,
                context->kernelArgs.roundingFactor,
                context->kernelArgs.shift_val,
                (uint8_t *)context->pOutBlock[OUT_YUV_IDX],
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else
    {
        rgb_to_yuv_YUYV_init((uint16_t *)context->pInBlock[IN_R_IDX],
                (uint16_t *)context->pInBlock[IN_G_IDX],
                (uint16_t *)context->pInBlock[IN_B_IDX],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.input_stride,
                coef[0],
                coef[1],
                coef[2],
                (int16_t *)coef,
                context->kernelArgs.roundingFactor,
                context->kernelArgs.shift_val,
                (uint8_t *)context->pOutBlock[OUT_YUV_IDX],
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );

    }

    return 0;
}

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2yuv_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_rgb2yuv_computeFrame(void *kernelContext)
{
    BAM_Image_rgb2yuv_Context *context = (BAM_Image_rgb2yuv_Context *) kernelContext;

    if(context->kernelArgs.outputFormat == RGB2YUV_OUTPUT_UYVY)
    {
        rgb_to_yuv_UYVY_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
        rgb_to_yuv_YUYV_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_rgb2yuvExecFunc =
{
        NULL,
        &BAM_Image_rgb2yuv_initFrame,
        &BAM_Image_rgb2yuv_computeFrame,
        NULL,
        NULL,
        NULL
};

