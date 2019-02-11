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
/*     @file : vcop_foreach_multiblock_bilinear_interp_7x7_u8_host.c        */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Multi Block Bilinear            */
/*     Interpolation for Unsigned Char data type pixels using foreach loop  */
/*           vcop_foreach_multiblock_bilinear_interp_7x7_u8_init - Copies   */
/*             arguments to parameter block memory                          */
/*           vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops - Invokes*/
/*             the API namely vcop_foreach_multiblock_bilinear_interp_7x7_u8*/
/*             defined in kernel file by passing the arguments from         */
/*             parameter block memory                                       */
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

#include "vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn.h"

#if VCOP_HOST_EMULATION

void vcop_foreach_multiblock_bilinear_interp_7x7_u8
(
    __vptr_uint8_arr    pIn_A,
    __vptr_uint16_arr    pInpWts_B,
    __vptr_uint8_arr    pOutBilinearInterpImg_C,
    unsigned short      input1Stride,
    unsigned short      input2Stride,
    unsigned short      outputStride,
    unsigned short      outBlkWidth,
    unsigned short      outBlkHeight,
    unsigned short      shiftValue,
    unsigned short      numKeyPoints
);
typedef struct _vcop_foreach_multiblock_bilinear_interp_7x7_u8_args
{
    unsigned short     input1Stride;
    unsigned short     input2Stride;
    unsigned short     outputStride;
    unsigned short     outBlkWidth;
    unsigned short     outBlkHeight;
    unsigned short     numKeyPoints;
    unsigned short      shiftValue;
} VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Args;

typedef struct _vcop_foreach_multiblock_bilinear_interp_7x7_u8_context
{
    void *pInBlock[32];
    void *pInWgts[32];
    void *pOutBlock[32];
    VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Args kernelArgs;
} VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context;

unsigned short __pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8[416 + sizeof(VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context)/sizeof(unsigned short)];
unsigned short __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[1];

unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(
    __vptr_uint8_arr    pIn_A,
    __vptr_uint16_arr    pInpWts_B,
    __vptr_uint8_arr    pOutBilinearInterpImg_C,
    unsigned short      input1Stride,
    unsigned short      input2Stride,
    unsigned short      outputStride,
    unsigned short      outBlkWidth,
    unsigned short      outBlkHeight,
    unsigned short      shiftValue,
    unsigned short      numKeyPoints,
    unsigned short      pblock[])
{
    int retVal = 0;
    int I0;
    int __offset = 0;
    unsigned int * ptr = (unsigned int *)pblock;
    VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context *context = (VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context *) (pblock + 416);

    if(numKeyPoints > 32)
    {
      return -1;
    }
    __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = numKeyPoints - 1;

    for(int i =0; i < numKeyPoints; i++)
    {
      context->pInBlock[i]             = pIn_A[i].addr;
      context->pInWgts[i]              = pInpWts_B[i].addr;
      context->pOutBlock[i]            = pOutBilinearInterpImg_C[i].addr;
    }

    context->kernelArgs.input1Stride = input1Stride;
    context->kernelArgs.input2Stride = input2Stride;
    context->kernelArgs.outputStride = outputStride;
    context->kernelArgs.outBlkWidth  = outBlkWidth;
    context->kernelArgs.outBlkHeight = outBlkHeight;
    context->kernelArgs.shiftValue   = shiftValue;
    context->kernelArgs.numKeyPoints = numKeyPoints;

    for(int i =0; i < context->kernelArgs.numKeyPoints; i++)
    {
      ptr[(12-2)/2 + i* (26/2)] = (unsigned int)pIn_A[i].addr;
      ptr[(20-2)/2 + i* (26/2)] = (unsigned int)pOutBilinearInterpImg_C[i].addr;
    }

    return retVal;
}


void vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(unsigned short pblock[])
{
    unsigned int * ptr = (unsigned int *)pblock;
    VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context *context = (VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context *) (pblock + 416);

    context->kernelArgs.numKeyPoints = __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] + 1;

    for(int i =0; i < context->kernelArgs.numKeyPoints; i++)
    {
      context->pInBlock[i]             = (void *)ptr[(12-2)/2 + i* (26/2)];
      context->pOutBlock[i]            = (void *)ptr[(20-2)/2 + i* (26/2)];
    }

#if 1 /*#ifdef NATC*/

    vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn(
            (unsigned char **)context->pInBlock,
            (unsigned short *)context->pInWgts[0],
            (unsigned char **)context->pOutBlock,
            context->kernelArgs.input1Stride,
            context->kernelArgs.input2Stride,
            context->kernelArgs.outputStride,
            context->kernelArgs.outBlkWidth,
            context->kernelArgs.outBlkHeight,
            context->kernelArgs.shiftValue,
            context->kernelArgs.numKeyPoints);
#else
    vcop_foreach_multiblock_bilinear_interp_7x7_u8(
            context->pInBlock,
            context->pInWgts,
            context->pOutBlock,
            context->kernelArgs.input1Stride,
            context->kernelArgs.input2Stride,
            context->kernelArgs.outputStride,
            context->kernelArgs.outBlkWidth,
            context->kernelArgs.outBlkHeight,
            context->kernelArgs.shiftValue,
            context->kernelArgs.numKeyPoints);
#endif
}


unsigned int vcop_foreach_multiblock_bilinear_interp_7x7_u8_param_count(void)
{
    return (416 + sizeof(VCOP_Foreach_Multiblock_Bilinear_Interp_7x7_U8_Context));
}

#endif
