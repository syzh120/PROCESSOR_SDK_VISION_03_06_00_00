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

/*                                                                          */
/*     @file : vcop_calc_inverse_structure_tensor_2x2_host.c                */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Weight Computation:             */
/*           vcop_calc_inverse_structure_tensor_2x2_init - Copies arguments */
/*             to parameter block memory                                    */
/*           vcop_calc_inverse_structure_tensor_2x2_vloops - Invokes the    */
/*             API namely vcop_calc_inverse_structure_tensor_2x2 defined in */
/*             kernel file by passing the arguments from parameter block    */
/*             memory                                                       */
/*                                                                          */
/*  @author Venkat R Peddigari (a0393744@ti.com)                            */
/*                                                                          */
/*  @version 1.0 (November 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#if VCOP_HOST_EMULATION
void vcop_calc_inverse_structure_tensor_2x2
(
    __vptr_int32      pTensorArrInp_A,
    __vptr_uint16     pD_nrsb_B,
    __vptr_uint32     pD_norm_C,
    __vptr_int16      pInverseArrOut_A,
    __vptr_int32      pScratchNorm_C,
    __vptr_uint32     pScratchDividend_C,
    unsigned short    inputStride,
    unsigned short    outputStride,
    unsigned short    numFracBits,
    unsigned short    numKeyPoints
);

typedef struct _vcop_calc_inverse_structure_tensor_2x2_args
{
    unsigned short    inputStride;
    unsigned short    outputStride;
    unsigned short    numKeyPoints;
    unsigned short    numFracBits;
} VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Args;


typedef struct _vcop_calc_inverse_structure_tensor_2x2_context
{
    void *pInBlock[3];
    void *pOutBlock[1];
    void *pInternalBlock[2];
    VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Args kernelArgs;
} VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context;

unsigned short __pblock_vcop_calc_inverse_structure_tensor_2x2[sizeof(VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context)/sizeof(unsigned short)];

unsigned int vcop_calc_inverse_structure_tensor_2x2_init(
    __vptr_int32      pTensorArrInp_A,
    __vptr_uint16     pD_nrsb_B,
    __vptr_uint32     pD_norm_C,
    __vptr_int16      pInverseArrOut_A,
    __vptr_int32      pScratchNorm_C,
    __vptr_uint32     pScratchDividend_C,
    unsigned short    inputStride,
    unsigned short    outputStride,
    unsigned short    numFracBits,
    unsigned short    numKeyPoints,
    unsigned short  pblock[])
{
    int retVal = 0;

    VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context *calcInverseStructureTensor2x2HostContext = (VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context *)pblock;

    calcInverseStructureTensor2x2HostContext->pInBlock[0]                 = pTensorArrInp_A.addr;
    calcInverseStructureTensor2x2HostContext->pInBlock[1]                 = pD_nrsb_B.addr;
    calcInverseStructureTensor2x2HostContext->pInBlock[2]                 = pD_norm_C.addr;
    calcInverseStructureTensor2x2HostContext->pOutBlock[0]                = pInverseArrOut_A.addr;
    calcInverseStructureTensor2x2HostContext->pInternalBlock[0]           = pScratchNorm_C.addr;
    calcInverseStructureTensor2x2HostContext->pInternalBlock[1]           = pScratchDividend_C.addr;
    calcInverseStructureTensor2x2HostContext->kernelArgs.inputStride      = inputStride;
    calcInverseStructureTensor2x2HostContext->kernelArgs.outputStride     = outputStride;
    calcInverseStructureTensor2x2HostContext->kernelArgs.numFracBits      = numFracBits;
    calcInverseStructureTensor2x2HostContext->kernelArgs.numKeyPoints     = numKeyPoints;

    return retVal;
}


void vcop_calc_inverse_structure_tensor_2x2_vloops(unsigned short pblock[])
{
    VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context *calcInverseStructureTensor2x2HostContext = (VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context *)pblock;

    vcop_calc_inverse_structure_tensor_2x2(calcInverseStructureTensor2x2HostContext->pInBlock[0], calcInverseStructureTensor2x2HostContext->pInBlock[1],
                                calcInverseStructureTensor2x2HostContext->pInBlock[2], calcInverseStructureTensor2x2HostContext->pOutBlock[0],
                                calcInverseStructureTensor2x2HostContext->pInternalBlock[0], calcInverseStructureTensor2x2HostContext->pInternalBlock[1],
                                calcInverseStructureTensor2x2HostContext->kernelArgs.inputStride, calcInverseStructureTensor2x2HostContext->kernelArgs.outputStride,
                                calcInverseStructureTensor2x2HostContext->kernelArgs.numFracBits, calcInverseStructureTensor2x2HostContext->kernelArgs.numKeyPoints);
}


unsigned int vcop_calc_inverse_structure_tensor_2x2_param_count(void)
{
    return (sizeof(VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_Context));
}

#endif
