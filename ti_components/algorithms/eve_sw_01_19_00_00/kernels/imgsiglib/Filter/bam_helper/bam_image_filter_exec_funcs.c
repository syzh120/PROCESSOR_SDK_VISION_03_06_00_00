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
 * @file:       bam_image_filter_exec_funcs.c
 *
 * @brief:     This file contains all kernel Exce functions for Bayer to RGB coversion
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
#include "vcop_filter_kernel.h" //makerules should take care of include path

/* Function Prototypes */
static BAM_Status BAM_Image_filter_initFrame(void *kernelContext);
static BAM_Status BAM_Image_filter_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_filter_initFrame
 * @brief     Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_filter_initFrame(void *kernelContext)
{
    BAM_Image_filter_Context *context = (BAM_Image_filter_Context *)kernelContext;
/*This is temporary fix for build. This BAM helper doesnt support host emulation */    
#if !VCOP_HOST_EMULATION
    if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == CHAR_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_uchar_char_char_init((unsigned char*)context->pInBlock[0],
                (char*)context->pInternalBlock[COEFFS_IDX],
                (char*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_uchar_char_short_init((unsigned char*)context->pInBlock[0],
                (char*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_ushort_short_short_init((unsigned short*)context->pInBlock[0],
                (short*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == SHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_short_short_short_init((short*)context->pInBlock[0],
                (short*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == USHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_ushort_ushort_short_init((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == INT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_ushort_short_int_init((unsigned short*)context->pInBlock[0],
                (short*)context->pInternalBlock[COEFFS_IDX],
                (int*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else
    {
    }
#endif
    return 0;
}

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
static BAM_Status BAM_Image_filter_computeFrame(void *kernelContext)
{
    BAM_Image_filter_Context *context = (BAM_Image_filter_Context *) kernelContext;
/*This is temporary fix for build. This BAM helper doesnt support host emulation */       
#if !VCOP_HOST_EMULATION
    if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == CHAR_TYPE)
    )
    {
        vcop_filter_uchar_char_char_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_uchar_char_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_ushort_short_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == SHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_short_short_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == USHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_ushort_ushort_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == INT_TYPE)
    )
    {
        vcop_filter_ushort_short_int_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
    }
#endif    
    return 0;
}


BAM_KernelExecFuncDef gBAM_TI_filterExecFunc =
{
        NULL,
        &BAM_Image_filter_initFrame,
        &BAM_Image_filter_computeFrame,
        NULL,
        NULL,
        NULL
};

