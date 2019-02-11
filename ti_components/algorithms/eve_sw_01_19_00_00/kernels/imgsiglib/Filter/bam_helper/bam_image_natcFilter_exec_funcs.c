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
 ********************************************************************************
 * @file:       bam_image_natcFilter_exec_funcs.c
 *
 * @brief:     This file contains all kernel Exce functions for the natural C version of the filter kernek
 *
 * @author:  Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version:  0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_image_filter_helper_funcs.h"
#include "../inc/vcop_filter_cn.h"

/* Function Prototypes */
static BAM_Status BAM_Image_natcFilter_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn:        BAM_Image_filter_Compute
 * @brief      Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_natcFilter_computeFrame(void *kernelContext)
{
    BAM_Image_filter_Context *context = (BAM_Image_filter_Context *)kernelContext;

    if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == CHAR_TYPE)
    )
    {
        filter_uchar_cn((unsigned char*)context->pInBlock[0],
                (char*)context->kernelArgs.filter_coefs,
                (unsigned char*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                0,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_uchar_cn((unsigned char*)context->pInBlock[0],
                (char*)context->kernelArgs.filter_coefs,
                (unsigned char*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == SHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == USHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == INT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else
    {
    }

    return 0;
}


BAM_KernelExecFuncDef gBAM_TI_natcFilterExecFunc =
{
        NULL,
        NULL,
        &BAM_Image_natcFilter_computeFrame,
        NULL,
        NULL,
        NULL
};

