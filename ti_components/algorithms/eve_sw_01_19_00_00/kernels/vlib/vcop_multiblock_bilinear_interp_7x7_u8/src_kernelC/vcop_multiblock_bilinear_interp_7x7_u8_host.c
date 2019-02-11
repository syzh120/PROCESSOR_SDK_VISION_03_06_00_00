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
/*     @file : vcop_multiblock_bilinear_interp_7x7_u8_host.c                */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Multi Block Bilinear            */
/*     Interpolation for Unsigned Char data type pixels                     */
/*           vcop_multiblock_bilinear_interp_7x7_u8_init - Copies arguments */
/*             to parameter block memory                                    */
/*           vcop_multiblock_bilinear_interp_7x7_u8_vloops - Invokes the    */
/*             API namely vcop_multiblock_bilinear_interp_7x7_u8 defined in */
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
void vcop_multiblock_bilinear_interp_7x7_u8
(
    __vptr_uint8    pIn_A,
    __vptr_uint16    pInpWts_B,
    __vptr_uint8    pOutBilinearInterpImg_C,
    unsigned short  input1Stride,
    unsigned short  input2Stride,
    unsigned short  outputStride,
    unsigned short  blkWidth,
    unsigned short  blkHeight,
    unsigned short  blkOffset,
    unsigned short  shiftValue,
    unsigned short  numKeyPoints 
);

typedef struct _vcop_multiblock_bilinear_interp_7x7_u8_args
{
    unsigned short     input1Stride;
    unsigned short     input2Stride;
    unsigned short     outputStride;
    unsigned short     blkWidth;
    unsigned short     blkHeight;
    unsigned short     blkOffset;
    unsigned short     shiftValue;
    unsigned short     numKeyPoints;
} VCOP_Multiblock_Bilinear_Interp_7x7_U8_Args;


typedef struct _vcop_multiblock_bilinear_interp_7x7_u8_context
{
    void *pInBlock[2];
    void *pOutBlock[1];
    VCOP_Multiblock_Bilinear_Interp_7x7_U8_Args kernelArgs;
} VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context;

unsigned short __pblock_vcop_multiblock_bilinear_interp_7x7_u8[sizeof(VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context)/sizeof(unsigned short)];

unsigned int vcop_multiblock_bilinear_interp_7x7_u8_init(
    __vptr_uint8    pIn_A,
    __vptr_uint16    pInpWts_B,
    __vptr_uint8    pOutBilinearInterpImg_C,
    unsigned short  input1Stride,
    unsigned short  input2Stride,
    unsigned short  outputStride,
    unsigned short  blkWidth,
    unsigned short  blkHeight,
    unsigned short  blkOffset,
    unsigned short  shiftValue,
    unsigned short  numKeyPoints,
    unsigned short  pblock[])
{
    int retVal = 0;

    VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context *multiblockBilinearInterp7x7U8 = (VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context *)pblock;

    multiblockBilinearInterp7x7U8->pInBlock[0]             = pIn_A.addr;
    multiblockBilinearInterp7x7U8->pInBlock[1]             = pInpWts_B.addr;
    multiblockBilinearInterp7x7U8->pOutBlock[0]            = pOutBilinearInterpImg_C.addr;
    multiblockBilinearInterp7x7U8->kernelArgs.input1Stride = input1Stride;
    multiblockBilinearInterp7x7U8->kernelArgs.input2Stride = input2Stride;
    multiblockBilinearInterp7x7U8->kernelArgs.outputStride = outputStride;
    multiblockBilinearInterp7x7U8->kernelArgs.blkWidth     = blkWidth;
    multiblockBilinearInterp7x7U8->kernelArgs.blkHeight    = blkHeight;
    multiblockBilinearInterp7x7U8->kernelArgs.blkOffset    = blkOffset;
    multiblockBilinearInterp7x7U8->kernelArgs.shiftValue   = shiftValue;
    multiblockBilinearInterp7x7U8->kernelArgs.numKeyPoints = numKeyPoints;

    return retVal;
}


void vcop_multiblock_bilinear_interp_7x7_u8_vloops(unsigned short pblock[])
{
    VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context *multiblockBilinearInterp7x7U8 = (VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context *)pblock;

    vcop_multiblock_bilinear_interp_7x7_u8(multiblockBilinearInterp7x7U8->pInBlock[0], multiblockBilinearInterp7x7U8->pInBlock[1], multiblockBilinearInterp7x7U8->pOutBlock[0],
                                multiblockBilinearInterp7x7U8->kernelArgs.input1Stride, multiblockBilinearInterp7x7U8->kernelArgs.input2Stride,
                                multiblockBilinearInterp7x7U8->kernelArgs.outputStride, multiblockBilinearInterp7x7U8->kernelArgs.blkWidth,
                                multiblockBilinearInterp7x7U8->kernelArgs.blkHeight, multiblockBilinearInterp7x7U8->kernelArgs.blkOffset,
                                multiblockBilinearInterp7x7U8->kernelArgs.shiftValue, multiblockBilinearInterp7x7U8->kernelArgs.numKeyPoints);
}


unsigned int vcop_multiblock_bilinear_interp_7x7_u8_param_count(void)
{
    return (sizeof(VCOP_Multiblock_Bilinear_Interp_7x7_U8_Context));
}

#endif
