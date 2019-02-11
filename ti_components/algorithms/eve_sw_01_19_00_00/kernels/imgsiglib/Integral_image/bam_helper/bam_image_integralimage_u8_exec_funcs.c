/*
*
* Copyright (c) 2011-2017 Texas Instruments Incorporated
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
 * @file bam_image_integralImage_u8_exec_funcs.c
 *
 * @brief This file contains all kernel Exce functions for Bayer to RGB coversion
 *
 * @author Kumar Desappan(kumar.desappan@ti.com)
 *
 * @version 0.0 (Jul 2013) : Base version.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_image_integralimage_u8_helper_funcs.h"
#include "eve_integral_image_kernel.h"

BAM_Status BAM_Image_integralImage_u8_initFrame
(
        void *kernelContext
);

BAM_Status BAM_Image_integralImage_u8_computeFrame
(
        void *kernelContext
);

/**
 *******************************************************************************
 * @fn        BAM_Image_integralImage_u8_initFrame
 * @brief    Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
BAM_Status BAM_Image_integralImage_u8_initFrame
(
        void *kernelContext
)
{
    BAM_Image_integralImage_u8_Context *context = (BAM_Image_integralImage_u8_Context *)kernelContext;

#if (!VCOP_HOST_EMULATION)
    eve_integral_image_reset_accv_init(
            context->pInternalBlock[SCRATCH_VER_ACC_IDX],
            context->kernelArgs.blk_height,
            context->pInternalBlock[PARAMS_RESET_ACCV_IDX]);

    eve_integral_image_u8_int_int_init(context->kernelArgs.blk_width, /*16*/
            context->kernelArgs.blk_height,/*160,*/
            context->kernelArgs.input_stride, /*16,*/
            context->pInBlock[IN_HOR_ACC_IDX],               /* context->pIn_ACC_H,  */
            context->pInternalBlock[SCRATCH_VER_ACC_IDX],    /* context->pIn_ACC_V,  */
            context->pInBlock[IN_IMG_IDX],                   /* context->pIn_IN,     */
            context->pInternalBlock[SCRATCH_B0_IDX],         /* context->pIn_B0,     */
            context->pInternalBlock[SCRATCH_B1_IDX],         /* context->pIn_B1,     */
            context->pInternalBlock[SCRATCH_C0_IDX],         /* context->pIn_C0,     */
            context->pInternalBlock[SCRATCH_C1_IDX],         /* context->pIn_C1,     */
            context->pOutBlock[OUT_INTG_IMG_IDX],            /* context->pOut_OUT,   */
            context->pOutBlock[OUT_HOR_ACC_IDX],             /* context->pOut_ACC_H , */
            context->pInternalBlock[PARAMS_IDX]              /* context->pBlock      */
    );
#endif

    context->currHorBlkIdx = 0;

    return 0;
}


/**
 *******************************************************************************
 * @fn       BAM_Image_integralImage_u8_computeFrame
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
BAM_Status BAM_Image_integralImage_u8_computeFrame
(
        void *kernelContext
)
{
    BAM_Image_integralImage_u8_Context *context = (BAM_Image_integralImage_u8_Context *)kernelContext;

    if(context->currHorBlkIdx == 0)
    {
#if (VCOP_HOST_EMULATION)
        eve_integral_image_reset_accv(
                context->pInternalBlock[SCRATCH_VER_ACC_IDX],
                context->kernelArgs.blk_height);
#else
        eve_integral_image_reset_accv_vloops(context->pInternalBlock[PARAMS_RESET_ACCV_IDX]);
#endif
    }
    
    
#if (VCOP_HOST_EMULATION)
    eve_integral_image_u8_int_int(context->kernelArgs.blk_width, /*16*/
            context->kernelArgs.blk_height,/*160,*/
            context->kernelArgs.input_stride, /*16,*/
            context->pInBlock[IN_HOR_ACC_IDX],               /*context->pIn_ACC_H,*/  
            context->pInternalBlock[SCRATCH_VER_ACC_IDX],    /*context->pIn_ACC_V,*/  
            context->pInBlock[IN_IMG_IDX],                   /*context->pIn_IN,*/     
            context->pInternalBlock[SCRATCH_B0_IDX],         /*context->pIn_B0,*/     
            context->pInternalBlock[SCRATCH_B1_IDX],         /*context->pIn_B1,*/     
            context->pInternalBlock[SCRATCH_C0_IDX],         /*context->pIn_C0,*/     
            context->pInternalBlock[SCRATCH_C1_IDX],         /*context->pIn_C1,*/     
            context->pOutBlock[OUT_INTG_IMG_IDX],            /*context->pOut_OUT,*/   
            context->pOutBlock[OUT_HOR_ACC_IDX]              /*context->pOut_ACC_H ,*/
    );
#else
    eve_integral_image_u8_int_int_vloops(context->pInternalBlock[PARAMS_IDX]);
#endif
    context->currHorBlkIdx++;
    if(context->currHorBlkIdx == context->kernelArgs.num_hor_blocks)
    {
        context->currHorBlkIdx = 0;
    }


    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_integralImage_u8KernelExecFunc =
{
        &BAM_Image_integralImage_u8_initFrame,    /* kernelInitInstance   */
        NULL,                                      /* kernelInitFrame      */
        &BAM_Image_integralImage_u8_computeFrame, /* kernelCompute        */
        NULL,                                      /* kernelWait           */
        NULL,                                      /* kernelCtl            */
        NULL                                       /* Custom               */
};

