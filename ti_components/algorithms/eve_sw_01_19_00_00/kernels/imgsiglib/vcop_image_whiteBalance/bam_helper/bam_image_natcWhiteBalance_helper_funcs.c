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
* @file bam_image_whiteBalance_helper_funcs.c
*
* @brief This file contains all kernel helper functions for white balance adjustments
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_image_whiteBalance_helper_funcs.h"
#include "vcop_white_balance_kernel.h"


/* Function Prototypes */
static BAM_Status BAM_Image_natcWhiteBalance_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
);

/**
*******************************************************************************
* @fn        BAM_Image_whiteBalance_getMemRecFunc
* @brief
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
static BAM_Status BAM_Image_natcWhiteBalance_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,           /* generally unused in case of processing node */
    uint8_t      *numOutBlocks     /* generally unused in case of processing node */
)
{
    ISP_BAM_Image_whiteBalance_Args *args = (ISP_BAM_Image_whiteBalance_Args *)kernelArgs;

    /* Actually doesn't really need an internal block */
    internalBlock[PARAMS_IDX].size = 2;
    internalBlock[PARAMS_IDX].space= BAM_MEMSPACE_DMEM;

    /*--------------------------------------------------------------------------------------------------*/
    /* Oputput pointer for Bayer data                                                                   */
    /* Here 16 is added for output block width because, actual input block width is                     */
	/* input_blk + horizotal padding size.(Minimum input block width is 16)            */
	/* This padding requires to add this 16(VCOP_2SIMD_WIDTH) for output line, and is independent of input block width  */

	/* 2 is added to block height because vertical padding is required for next module (Bayer2RGB)           */
	/* And is independent of input block height                                                         */
    /*--------------------------------------------------------------------------------------------------*/
    outBlock[0].size = ((args->blk_width +16)* (args->blk_height +2) * sizeof(short));

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_natcWhiteBalanceKernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_whiteBalance_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_whiteBalance_Args),
    BAM_EVE_ARP32, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    NUM_INTERNAL_BLOCKS       /*numInternalBlocks */
};

BAM_KernelHelperFuncDef gBAM_TI_natcWhiteBalanceHelperFunc =
{
    &BAM_Image_natcWhiteBalance_getMemRecFunc,
    NULL,/*(BAM_KernelSetMemRecFunc)&BAM_Image_whiteBalance_setMemRecFunc*/
};

