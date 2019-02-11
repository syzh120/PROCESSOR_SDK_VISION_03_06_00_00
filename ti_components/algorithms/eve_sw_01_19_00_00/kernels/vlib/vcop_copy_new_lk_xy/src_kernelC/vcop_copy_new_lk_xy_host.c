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
/*     @file : vcop_copy_new_lk_xy_host.c                                   */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Weight Computation:             */
/*           vcop_copy_new_lk_xy_init - Copies arguments to                 */
/*             parameter block memory                                       */
/*           vcop_copy_new_lk_xy_vloops - Invokes the API namely            */
/*             vcop_copy_new_lk_xy defined in kernel file by                */
/*             passing the arguments from parameter block memory            */
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

#include "vcop_copy_new_lk_xy_cn.h"

#if VCOP_HOST_EMULATION
void vcop_copy_new_lk_xy
(
    __vptr_int16   pInput_A,
    __vptr_int16   pOutput_B,
    __vptr_uint8  currValidPoints,        
		__vptr_uint32 pBaseAddrList ,
		__vptr_uint32 pValidAddrList,
		__vptr_uint32 pOutAddrList     ,
		__vptr_uint32 pValidOutAddrList,
    __vptr_int16   pLocalX,
    __vptr_int16   pLocalY,
    __vptr_int16   pLocalXY,
    unsigned short  numKeyPoints
);

typedef struct _vcop_copy_new_lk_xy_args
{
    unsigned short numKeyPoints;
} VCOP_COPY_NEW_LK_XY_Args;


typedef struct _vcop_copy_new_lk_xy_context
{
    void *pInBlock[4];
    void *pOutBlock[6];
    VCOP_COPY_NEW_LK_XY_Args kernelArgs;
} VCOP_COPY_NEW_LK_XY_Context;

unsigned short __pblock_vcop_copy_new_lk_xy[sizeof(VCOP_COPY_NEW_LK_XY_Context)/sizeof(unsigned short)];

unsigned int vcop_copy_new_lk_xy_init(
    __vptr_int16   pInput_A,
    __vptr_int16   pOutput_B,
    __vptr_uint8  currValidPoints,        
		__vptr_uint32 pBaseAddrList ,
		__vptr_uint32 pValidAddrList,
		__vptr_uint32 pOutAddrList     ,
		__vptr_uint32 pValidOutAddrList,
    __vptr_int16   pLocalX,
    __vptr_int16   pLocalY,
    __vptr_int16   pLocalXY,
    unsigned short  numKeyPoints,
    unsigned short  pblock[])
{
    int retVal = 0;

    VCOP_COPY_NEW_LK_XY_Context *copyNewLKXYHostContext = (VCOP_COPY_NEW_LK_XY_Context *)pblock;

    copyNewLKXYHostContext->pInBlock[0]                 = pInput_A.addr;
    copyNewLKXYHostContext->pInBlock[1]                 = pBaseAddrList.addr;
    copyNewLKXYHostContext->pInBlock[2]                 = pOutAddrList.addr;
    copyNewLKXYHostContext->pInBlock[3]                 = pLocalXY.addr;
    copyNewLKXYHostContext->pOutBlock[0]                = pOutput_B.addr;
    copyNewLKXYHostContext->pOutBlock[1]                = currValidPoints.addr;
    copyNewLKXYHostContext->pOutBlock[2]                = pValidAddrList.addr;
    copyNewLKXYHostContext->pOutBlock[3]                = pValidOutAddrList.addr;
    copyNewLKXYHostContext->pOutBlock[4]                = pLocalX.addr;
    copyNewLKXYHostContext->pOutBlock[5]                = pLocalY.addr;
    copyNewLKXYHostContext->kernelArgs.numKeyPoints     = numKeyPoints;
    
    return retVal;
}


void vcop_copy_new_lk_xy_vloops(unsigned short pblock[])
{
    VCOP_COPY_NEW_LK_XY_Context *copyNewLKXYHostContext = (VCOP_COPY_NEW_LK_XY_Context *)pblock;

#ifdef NATC
    vcop_copy_new_lk_xy_cn((short *)copyNewLKXYHostContext->pInBlock[0],
                        (short *)copyNewLKXYHostContext->pOutBlock[0],
                        (unsigned char *)copyNewLKXYHostContext->pOutBlock[1],
                        (unsigned int *)copyNewLKXYHostContext->pInBlock[1],
                        (unsigned int *)copyNewLKXYHostContext->pOutBlock[2],
                        (unsigned int *)copyNewLKXYHostContext->pInBlock[2],
                        (unsigned int *)copyNewLKXYHostContext->pOutBlock[3],
                        (short *)copyNewLKXYHostContext->pOutBlock[4],
                        (short *)copyNewLKXYHostContext->pOutBlock[5],
                        (short *)copyNewLKXYHostContext->pInBlock[3],
                        copyNewLKXYHostContext->kernelArgs.numKeyPoints);

#else
    vcop_copy_new_lk_xy(copyNewLKXYHostContext->pInBlock[0],
                        copyNewLKXYHostContext->pOutBlock[0],
                        copyNewLKXYHostContext->pOutBlock[1],
                        copyNewLKXYHostContext->pInBlock[1],
                        copyNewLKXYHostContext->pOutBlock[2],
                        copyNewLKXYHostContext->pInBlock[2],
                        copyNewLKXYHostContext->pOutBlock[3],
                        copyNewLKXYHostContext->pOutBlock[4],
                        copyNewLKXYHostContext->pOutBlock[5],
                        copyNewLKXYHostContext->pInBlock[3],
                        copyNewLKXYHostContext->kernelArgs.numKeyPoints);
#endif
}

unsigned int vcop_copy_new_lk_xy_param_count(void)
{
    return (sizeof(VCOP_COPY_NEW_LK_XY_Context));
}

#endif
