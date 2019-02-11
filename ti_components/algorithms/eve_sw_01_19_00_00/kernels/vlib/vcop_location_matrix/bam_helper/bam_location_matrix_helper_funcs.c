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
* @file bam_location_matrix_helper_funcs.c
*
* @brief    This file contains all kernel helper functions for location_matrix
*           kernel
*
*
* @version 0.0 (Jan 2014) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_location_matrix_helper_funcs.h"
#include "vcop_location_matrix_kernel.h"
BAM_Status BAM_location_matrix_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);
/**
*******************************************************************************
* @fn        BAM_location_matrix_getMemRecFunc
* @brief
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  memRecInternal :
* @inputs -  memRecOutputDataBlock :
* @inputs -  numRecInternal :
* @inputs -  numRecOutputDataBlock :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_location_matrix_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{
    const BAM_location_matrix_Args *args = (const BAM_location_matrix_Args *)kernelArgs;
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t numBins = (uint32_t)(args->numBins);
    numBins++;
    numBins = (numBins >> 1U) << 1U;

    if(args->gradientMagSize <= 2)
    {

#if (!VCOP_HOST_EMULATION)
    if(args->gradientMagSize == 1)
    {
      memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*
                                  vcop_vec_L_matrix_u8_Mag_param_count();
    }
    else
    {
      memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*
                                  vcop_vec_L_matrix_u16_Mag_param_count();
    }
#else
    /* This field could be any non-zero number for host emulation, its not really used for host emualtion */
    memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].size = 4;
#endif
    memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;


    memRecInternal[LOCATION_MATRIX_INTERNAL_BIN_IDX].size = numBins;
    memRecInternal[LOCATION_MATRIX_INTERNAL_BIN_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[LOCATION_MATRIX_INTERNAL_BIN_IDX].space = BAM_MEMSPACE_WBUF;


    /*--------------------------------------------------------------------------*/
    /* Output pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX].size = (args->gradientMagSize * args->blockW * args->blockH * numBins) / (2U) ;
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX].space = BAM_MEMSPACE_IBUFLA;

    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX].size = (args->gradientMagSize * args->blockW * args->blockH * numBins) / (2U);
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX].space = BAM_MEMSPACE_IBUFHA;
    }
    return status;
}

BAM_KernelInfo gBAM_TI_location_matrixKernel =
{
    0,  /*kernelId */
    sizeof(BAM_location_matrix_Context),/*kernelContextSize*/
    sizeof(BAM_location_matrix_Args),
    BAM_EVE, /* Core Type */
    BAM_NODE_COMPUTE, /*nodeType */
    LOCATION_MATRIX_NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    LOCATION_MATRIX_NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    LOCATION_MATRIX_NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_location_matrixHelperFunc =
{
    &BAM_location_matrix_getMemRecFunc,
    NULL
};

