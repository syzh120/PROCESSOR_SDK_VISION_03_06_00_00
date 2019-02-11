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
/*     @file : vcop_calc_new_lk_xy_host.c                                   */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*  @author Kumar Desappan (a0393754@ti.com)                                */
/*                                                                          */
/*  @version 1.0 (November 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#include "vcop_calc_new_lk_xy_cn.h"

#if VCOP_HOST_EMULATION
void vcop_calc_new_lk_xy(
    __vptr_uint16 IxItL_a,
    __vptr_uint16 IyItL_b,
    __vptr_int16 IxItH_a,
    __vptr_int16 IyItH_b,
    __vptr_int16 Ix2_a,
    __vptr_int16 Iy2_b,
    __vptr_int16 Ixy_c,
    __vptr_int16 X_c,
    __vptr_int16 Y_c,
    __vptr_int16 localXY_b,
    __vptr_int16 frameXY_b,
    __vptr_uint16 numValidPoints,
    __vptr_uint8  currValidPoints,
    __vptr_uint32 pBaseAddrList ,
    __vptr_uint32 pValidAddrList,
    __vptr_uint32 pOutAddrList     ,
    __vptr_uint32 pValidOutAddrList,
    __vptr_int32  vx,
    __vptr_int32  vy,
    unsigned short  qFormatePel,
    unsigned short  minErrValue,
    unsigned char   searchRange,
    unsigned short n);

typedef struct _vcop_calc_new_lk_xy_args
{
    unsigned short  numBlocks;
    unsigned short  qFormatePel;
    short  minErrValue;
    unsigned char   searchRange;
} vcop_calc_new_lk_xy_Args;


typedef struct _vcop_calc_new_lk_xy_context
{
   void *pInBlock[17];
   void *pInternalBlock[2];
    vcop_calc_new_lk_xy_Args kernelArgs;
} vcop_calc_new_lk_xy_Context;

unsigned short __pblock_vcop_calc_new_lk_xy[sizeof(vcop_calc_new_lk_xy_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_calc_new_lk_xy_init(
    __vptr_uint16 IxItL_a,
    __vptr_uint16 IyItL_b,
    __vptr_int16  IxItH_a,
    __vptr_int16  IyItH_b,
    __vptr_int16  Ix2_a,
    __vptr_int16  Iy2_b,
    __vptr_int16  Ixy_c,
    __vptr_int16  X_c,
    __vptr_int16  Y_c,
    __vptr_int16  localXY_b,
    __vptr_int16  frameXY_b,
    __vptr_uint16 numValidPoints,
    __vptr_uint8  currValidPoints,
    __vptr_uint32 pBaseAddrList ,
    __vptr_uint32 pValidAddrList,
    __vptr_uint32 pOutAddrList     ,
    __vptr_uint32 pValidOutAddrList,
    __vptr_int32  vx,
    __vptr_int32  vy,
    unsigned short  qFormatePel,
    unsigned short  minErrValue,
    unsigned char   searchRange,
    unsigned short n,
   unsigned short pblock[])
{
    int retVal = 0;

    vcop_calc_new_lk_xy_Context *Context = (vcop_calc_new_lk_xy_Context *)pblock;

    Context->pInBlock[0]            = IxItL_a.addr;
    Context->pInBlock[1]            = IyItL_b.addr;
    Context->pInBlock[2]            = IxItH_a.addr;
    Context->pInBlock[3]            = IyItH_b.addr;
    Context->pInBlock[4]            = Ix2_a.addr;
    Context->pInBlock[5]            = Iy2_b.addr;
    Context->pInBlock[6]            = Ixy_c.addr;
    Context->pInBlock[7]            = X_c.addr;
    Context->pInBlock[8]            = Y_c.addr;
    Context->pInBlock[9]            = localXY_b.addr;
    Context->pInBlock[10]           = frameXY_b.addr;
    Context->pInBlock[11]           = numValidPoints.addr;
    Context->pInBlock[12]           = currValidPoints.addr;
    Context->pInBlock[13]           = pBaseAddrList.addr;
    Context->pInBlock[14]           = pValidAddrList.addr;
    Context->pInBlock[15]           = pOutAddrList.addr;
    Context->pInBlock[16]           = pValidOutAddrList.addr;
    Context->pInternalBlock[0]      = vx.addr;
    Context->pInternalBlock[1]      = vy.addr;
    Context->kernelArgs.qFormatePel = qFormatePel;
    Context->kernelArgs.minErrValue = minErrValue;
    Context->kernelArgs.numBlocks   = n;
    Context->kernelArgs.searchRange   = searchRange;

    return retVal;
}


void vcop_calc_new_lk_xy_vloops(unsigned short pblock[])
{
    vcop_calc_new_lk_xy_Context *Context = (vcop_calc_new_lk_xy_Context *)pblock;

#ifdef NATC

    vcop_calc_new_lk_xy_cn(
      (int *)Context->pInBlock[0],
      (int *)Context->pInBlock[1],
      (short *)Context->pInBlock[4],
      (short *)Context->pInBlock[5],
      (short *)Context->pInBlock[6],
      (unsigned short *)Context->pInBlock[7],
      (unsigned short *)Context->pInBlock[8],
      (unsigned short *)Context->pInBlock[9],
      (unsigned short *)Context->pInBlock[10],
      (unsigned short *)Context->pInBlock[11],
      (unsigned char *)Context->pInBlock[12],
      (unsigned int*)Context->pInBlock[13],
      (unsigned int*)Context->pInBlock[14],
      (unsigned int*)Context->pInBlock[15],
      (unsigned int*)Context->pInBlock[16],
      Context->kernelArgs.qFormatePel,
      Context->kernelArgs.minErrValue,
      Context->kernelArgs.searchRange,
      Context->kernelArgs.numBlocks
      );
#else
    vcop_calc_new_lk_xy(
      Context->pInBlock[0],
      Context->pInBlock[1],
      Context->pInBlock[2],
      Context->pInBlock[3],
      Context->pInBlock[4],
      Context->pInBlock[5],
      Context->pInBlock[6],
      Context->pInBlock[7],
      Context->pInBlock[8],
      Context->pInBlock[9],
      Context->pInBlock[10],
      Context->pInBlock[11],
      Context->pInBlock[12],
      Context->pInBlock[13],
      Context->pInBlock[14],
      Context->pInBlock[15],
      Context->pInBlock[16],
      Context->pInternalBlock[0],
      Context->pInternalBlock[1],
      Context->kernelArgs.qFormatePel,
      Context->kernelArgs.minErrValue,
      Context->kernelArgs.searchRange,
      Context->kernelArgs.numBlocks
      );
#endif
}

unsigned int vcop_calc_new_lk_xy_param_count(void)
{
    return (sizeof(vcop_calc_new_lk_xy_Context));
}

#endif
