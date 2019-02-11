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
/*     @file : vcop_weight_address_bilinear_interpolation_host.c            */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Weight & Address Compute needed */
/*     for bilinear interpolation:                                          */
/*           vcop_weight_address_bilinear_interpolation_init - Copies       */
/*             arguments to parameter block memory                          */
/*           vcop_weight_address_bilinear_interpolation_vloops - Invokes the*/
/*             API namely vcop_weight_address_bilinear_interpolation defined*/
/*             in kernel file by passing the arguments from parameter block */
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

#include "vcop_weight_address_bilinear_interpolation_cn.h"

#if VCOP_HOST_EMULATION
void vcop_weight_address_bilinear_interpolation
(
    __vptr_uint16   pXList_A,
    __vptr_uint16   pYList_A,
    __vptr_uint32   pBaseAddrList_B,
    __vptr_uint32   pOutAddrList_B,
    __vptr_uint16    pOutWts_C,
    __vptr_uint32   pOutBaseAddress_C,
    __vptr_uint16   pParamBlkOffsetVec_C,
    unsigned short  numKeyPoints,
    unsigned short  qFormatMaxFactor,
    unsigned short  truncateBits,
    unsigned short  qShift,
    unsigned short  blkStride,
    unsigned short  outputStride
);

typedef struct _vcop_weight_address_bilinear_interpolation_args
{
    unsigned short     numKeyPoints;
    unsigned short     qFormatMaxFactor;
    unsigned short     truncateBits;
    unsigned short     qShift;
    unsigned short     blkStride;
    unsigned short     outputStride;
} VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Args;

typedef struct _vcop_weight_address_bilinear_interpolation_context
{
    void *pInBlock[5];
    void *pOutBlock[2];
    VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Args kernelArgs;
} VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context;

unsigned short __pblock_vcop_weight_address_bilinear_interpolation[sizeof(VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context)/sizeof(unsigned short )];

unsigned int vcop_weight_address_bilinear_interpolation_init(
    __vptr_uint16   pXList_A,
    __vptr_uint16   pYList_A,
    __vptr_uint32   pBaseAddrList_B,
    __vptr_uint32   pOutAddrList_B,
    __vptr_uint16    pOutWts_C,
    __vptr_uint32   pOutBaseAddress_C,
    __vptr_uint16   pParamBlkOffsetVec_C,
    unsigned short  numKeyPoints,
    unsigned short  qFormatMaxFactor,
    unsigned short  truncateBits,
    unsigned short  qShift,
    unsigned short  blkStride,
    unsigned short  outputStride,
    unsigned short  pblock[])
{
    int retVal = 0;

    VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context *weightAddressBilinearInterpolationHostContext = (VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context *)pblock;

    weightAddressBilinearInterpolationHostContext->pInBlock[0]                 = pXList_A.addr;
    weightAddressBilinearInterpolationHostContext->pInBlock[1]                 = pYList_A.addr;
    weightAddressBilinearInterpolationHostContext->pInBlock[2]                 = pBaseAddrList_B.addr;
    weightAddressBilinearInterpolationHostContext->pInBlock[3]                 = pOutAddrList_B.addr;
    weightAddressBilinearInterpolationHostContext->pInBlock[4]                 = pParamBlkOffsetVec_C.addr;
    weightAddressBilinearInterpolationHostContext->pOutBlock[0]                = pOutWts_C.addr;
    weightAddressBilinearInterpolationHostContext->pOutBlock[1]                = pOutBaseAddress_C.addr;
    weightAddressBilinearInterpolationHostContext->kernelArgs.numKeyPoints     = numKeyPoints;
    weightAddressBilinearInterpolationHostContext->kernelArgs.qFormatMaxFactor = qFormatMaxFactor;
    weightAddressBilinearInterpolationHostContext->kernelArgs.truncateBits     = truncateBits;
    weightAddressBilinearInterpolationHostContext->kernelArgs.qShift           = qShift;
    weightAddressBilinearInterpolationHostContext->kernelArgs.blkStride        = blkStride;
    weightAddressBilinearInterpolationHostContext->kernelArgs.outputStride     = outputStride;

    return retVal;
}


void vcop_weight_address_bilinear_interpolation_vloops(unsigned short pblock[])
{
    VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context *weightAddressBilinearInterpolationHostContext = (VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context *)pblock;

#ifdef NATC

    vcop_weight_address_bilinear_interpolation_cn((unsigned short *)weightAddressBilinearInterpolationHostContext->pInBlock[0], (unsigned short *)weightAddressBilinearInterpolationHostContext->pInBlock[1],
                                (unsigned int *)weightAddressBilinearInterpolationHostContext->pInBlock[2],
                                (unsigned int *)weightAddressBilinearInterpolationHostContext->pInBlock[3],
                                (unsigned short *)weightAddressBilinearInterpolationHostContext->pOutBlock[0], (unsigned int *)weightAddressBilinearInterpolationHostContext->pOutBlock[1],
                                (unsigned short *)weightAddressBilinearInterpolationHostContext->pInBlock[4],
                                weightAddressBilinearInterpolationHostContext->kernelArgs.numKeyPoints,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.qFormatMaxFactor,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.truncateBits,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.qShift,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.blkStride,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.outputStride);
#else
    vcop_weight_address_bilinear_interpolation(weightAddressBilinearInterpolationHostContext->pInBlock[0], weightAddressBilinearInterpolationHostContext->pInBlock[1],
                                weightAddressBilinearInterpolationHostContext->pInBlock[2],
                                weightAddressBilinearInterpolationHostContext->pInBlock[3],
                                weightAddressBilinearInterpolationHostContext->pOutBlock[0], weightAddressBilinearInterpolationHostContext->pOutBlock[1],
                                weightAddressBilinearInterpolationHostContext->pInBlock[4],
                                weightAddressBilinearInterpolationHostContext->kernelArgs.numKeyPoints,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.qFormatMaxFactor,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.truncateBits,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.qShift,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.blkStride,
                                weightAddressBilinearInterpolationHostContext->kernelArgs.outputStride);
#endif
}


unsigned int vcop_weight_address_bilinear_interpolation_param_count(void)
{
    return (sizeof(VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_Context));
}

#endif
