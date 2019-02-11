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
 * @file bam_raw2rgb16_Exec_Funcs.c
 *
 * @brief This file contains all kernel Exce functions for Raw to RGB coversion
 * @version 0.0 (November 2012) : Base version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "vcop_raw2rgb_i16u_o16u_kernel.h"
#include "bam_raw2rgb16_int.h"

/* Function Prototypes */
static BAM_Status BAM_raw2rgb16_initFrame(void *kernelContext);

static BAM_Status BAM_raw2rgb16_computeFrame(void *kernelContext);

static BAM_Status BAM_raw2rgb16_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_raw2rgb16_control(void *kernelContext, void *kernelCtlArg) {

    BAM_Status status = 0;

    return status;
}

/**
 *******************************************************************************
 * @fn        BAM_raw2rgb_initFrame
 * @brief    Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_raw2rgb16_initFrame(void *kernelContext)
{
    BAM_Raw2rgb16_Context *context = (BAM_Raw2rgb16_Context *) kernelContext;
    uint16_t *pColor1Block;
    uint16_t *pColor2Block;
    uint8_t isGBRGorGRBG;

    if ((context->kernelArgs.bayer_pattern== 0) || (context->kernelArgs.bayer_pattern== 1)) {
        isGBRGorGRBG= (uint8_t)1U; /* gbrg or grbg */
        }
    else {
        isGBRGorGRBG= (uint8_t)0U; /* bggr or rggb */
        }

    if ((context->kernelArgs.bayer_pattern== 3) || (context->kernelArgs.bayer_pattern== 0)) {/* rggb or gbrg */
        pColor1Block= (uint16_t *)context->pOutBlock[OUT_R_IDX];
        pColor2Block=  (uint16_t *)context->pOutBlock[OUT_B_IDX];
        }
    else {
        pColor1Block= (uint16_t *)context->pOutBlock[OUT_B_IDX];
        pColor2Block=  (uint16_t *)context->pOutBlock[OUT_R_IDX];
        }

#if (!VCOP_HOST_EMULATION)
    if (isGBRGorGRBG== 0) {
         vcop_raw2rgb_CGGC_i16u_o16u_init((uint16_t *)context->pInBlock[IN_IDX],
                    pColor1Block,
                    (uint16_t *)context->pOutBlock[OUT_G_IDX],
                    pColor2Block,
                    (uint16_t *)context->pInternalBlock[SCRATCH_IDX],
                    context->kernelArgs.blk_width,
                    context->kernelArgs.blk_height,
                    context->kernelArgs.input_stride,
                    context->kernelArgs.outputG_stride,
                    context->kernelArgs.outputRB_stride,
                    (uint16_t *)context->pInternalBlock[PARAMS_IDX]
         );
        }
    else {
        vcop_raw2rgb_GCCG_i16u_o16u_init((uint16_t *)context->pInBlock[IN_IDX],
                   pColor1Block,
                   (uint16_t *)context->pOutBlock[OUT_G_IDX],
                   pColor2Block,
                   (uint16_t *)context->pInternalBlock[SCRATCH_IDX],
                   context->kernelArgs.blk_width,
                   context->kernelArgs.blk_height,
                   context->kernelArgs.input_stride,
                   context->kernelArgs.outputG_stride,
                   context->kernelArgs.outputRB_stride,
                   (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
        }
#endif
    return 0;
}

/**
 *******************************************************************************
 * @fn        BAM_raw2rgb_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_raw2rgb16_computeFrame(void *kernelContext)
{
    BAM_Raw2rgb16_Context *context = (BAM_Raw2rgb16_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t *pColor1Block;
    uint16_t *pColor2Block;

    uint8_t isGBRGorGRBG;

    if ((context->kernelArgs.bayer_pattern== 0) || (context->kernelArgs.bayer_pattern== 1)) {
        isGBRGorGRBG= (uint8_t)1U; /* gbrg or grbg */
        }
    else {
        isGBRGorGRBG= (uint8_t)0U; /* bggr or rggb */
        }

    if ((context->kernelArgs.bayer_pattern== 3) || (context->kernelArgs.bayer_pattern== 0)) {/* rggb or gbrg */
        pColor1Block= (uint16_t *)context->pOutBlock[OUT_R_IDX];
        pColor2Block=  (uint16_t *)context->pOutBlock[OUT_B_IDX];
        }
    else {
        pColor1Block= (uint16_t *)context->pOutBlock[OUT_B_IDX];
        pColor2Block=  (uint16_t *)context->pOutBlock[OUT_R_IDX];
        }

    if (!isGBRGorGRBG) {
        vcop_raw2rgb_CGGC_i16u_o16u((uint16_t *)context->pInBlock[IN_IDX],
                    pColor1Block,
                    (uint16_t *)context->pOutBlock[OUT_G_IDX],
                    pColor2Block,
                    (uint16_t *)context->pInternalBlock[SCRATCH_IDX],
                    context->kernelArgs.blk_width,
                    context->kernelArgs.blk_height,
                    context->kernelArgs.input_stride,
                    context->kernelArgs.outputG_stride,
                    context->kernelArgs.outputRB_stride
        );
    }
    else {
        vcop_raw2rgb_GCCG_i16u_o16u((uint16_t *)context->pInBlock[IN_IDX],
                    pColor1Block,
                    (uint16_t *)context->pOutBlock[OUT_G_IDX],
                    pColor2Block,
                    (uint16_t *)context->pInternalBlock[SCRATCH_IDX],
                    context->kernelArgs.blk_width,
                    context->kernelArgs.blk_height,
                    context->kernelArgs.input_stride,
                    context->kernelArgs.outputG_stride,
                    context->kernelArgs.outputRB_stride
        );
    }

    return status;
}

#else
static BAM_Status BAM_raw2rgb16_computeFrame(void *kernelContext)
{
    BAM_Raw2rgb16_Context *context = (BAM_Raw2rgb16_Context *) kernelContext;
    BAM_Status status = 0;

    if ((context->kernelArgs.bayer_pattern== 0) || (context->kernelArgs.bayer_pattern== 1)) {
        vcop_raw2rgb_GCCG_i16u_o16u_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]); /* gbrg or grbg */
        }
    else {
        vcop_raw2rgb_CGGC_i16u_o16u_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]); /* bggr or rggb */
        }

    return status;

}
#endif

BAM_KernelExecFuncDef gBAM_TI_raw2rgb16ExecFunc =
{
        NULL,
        &BAM_raw2rgb16_initFrame,
        &BAM_raw2rgb16_computeFrame,
        NULL,
        &BAM_raw2rgb16_control,
        NULL
};

