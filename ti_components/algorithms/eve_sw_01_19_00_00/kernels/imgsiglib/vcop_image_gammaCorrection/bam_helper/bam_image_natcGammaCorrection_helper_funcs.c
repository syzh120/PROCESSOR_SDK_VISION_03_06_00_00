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
* @file bam_image_gammaCorrection_helper_funcs.c
*
* @brief This file contains all kernel helper functions for Gamma Correction
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include <vcop.h>
#include "algframework.h"
#include "bam_image_gammaCorrection_helper_funcs.h"
#include "vcop_gamma_correction_kernel.h"


/* Function Prototypes */
static BAM_Status BAM_Image_natcGammaCorrection_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
);


/**
*******************************************************************************
* @fn        BAM_Image_rgb2srgb_GetMemRecFunc
* @brief    Function to allocate memory for RGB to sRGB conversion .
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  internalBlock :
* @inputs -  outBlock :
* @inputs -  numInternalBlocks :
* @inputs -  numOutBlocks :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
static BAM_Status BAM_Image_natcGammaCorrection_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
)
{
    ISP_BAM_Image_gammaCorrection_Args *args = (ISP_BAM_Image_gammaCorrection_Args *)kernelArgs;

    internalBlock[PARAMS_IDX].size = 2;
    internalBlock[PARAMS_IDX].space= BAM_MEMSPACE_DMEM;

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for R component                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_R_IDX].size = (args->blk_width* args->blk_height *sizeof(short));

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for G component                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_G_IDX].size = (args->blk_width* args->blk_height *sizeof(short));

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for B component                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_B_IDX].size = (args->blk_width* args->blk_height *sizeof(short));

    /*--------------------------------------------------------------------------*/
    /* Temp oputput pointer for R component                                     */
    /*--------------------------------------------------------------------------*/
    internalBlock[TEMP_R_IDX].size = (args->blk_width* args->blk_height *sizeof(short));
    internalBlock[TEMP_R_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /*--------------------------------------------------------------------------*/
    /* Temp oputput pointer for G component                                     */
    /*--------------------------------------------------------------------------*/
    internalBlock[TEMP_G_IDX].size = (args->blk_width* args->blk_height *sizeof(short));
    internalBlock[TEMP_G_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /*--------------------------------------------------------------------------*/
    /* Temp oputput pointer for G component                                     */
    /*--------------------------------------------------------------------------*/
    internalBlock[TEMP_B_IDX].size = (args->blk_width* args->blk_height *sizeof(short));
    internalBlock[TEMP_B_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /*--------------------------------------------------------------------------*/
    /* LUT pointer                                                              */
    /*--------------------------------------------------------------------------*/
    /*1024 - size of LUT table and 4 is table replication number             */
    internalBlock[LUT_IDX].size = 1024*4*sizeof(short); /* TODO : Need to use this pointer for LUT*/

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_natcGammaCorrectionKernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_gammaCorrection_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_gammaCorrection_Args),
    BAM_EVE_ARP32, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,                  /* 3 */
    NUM_OUT_BLOCKS,                 /* 3 */
    NUM_INTERNAL_BLOCKS             /* 5 */
};


BAM_KernelHelperFuncDef gBAM_TI_natcGammaCorrectionHelperFunc =
{
    &BAM_Image_natcGammaCorrection_getMemRecFunc,
    NULL
};

