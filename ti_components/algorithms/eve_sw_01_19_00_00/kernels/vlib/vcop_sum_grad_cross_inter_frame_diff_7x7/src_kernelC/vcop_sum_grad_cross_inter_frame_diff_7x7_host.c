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
/*     @file : vcop_sum_grad_cross_inter_frame_diff_7x7_host.c              */
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

#include "vcop_sum_grad_cross_inter_frame_diff_7x7_cn.h"

#if VCOP_HOST_EMULATION
void vcop_sum_grad_cross_inter_frame_diff_7x7(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b);

typedef struct _vcop_sum_grad_cross_inter_frame_diff_7x7_args
{
   unsigned short  gradStride;
   unsigned short  imStride;
    unsigned short numBlocks;
} vcop_sum_grad_cross_inter_frame_diff_7x7_Args;


typedef struct _vcop_sum_grad_cross_inter_frame_diff_7x7_context
{
   void *pInBlock[4];
   void *pInternalBlock[2];
   void *pOutBlock[2];
    vcop_sum_grad_cross_inter_frame_diff_7x7_Args kernelArgs;
} vcop_sum_grad_cross_inter_frame_diff_7x7_Context;

unsigned short __pblock_vcop_sum_grad_cross_inter_frame_diff_7x7[sizeof(vcop_sum_grad_cross_inter_frame_diff_7x7_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   unsigned short pblock[])
{
    int retVal = 0;

    vcop_sum_grad_cross_inter_frame_diff_7x7_Context *Context = (vcop_sum_grad_cross_inter_frame_diff_7x7_Context *)pblock;

    Context->pInBlock[0]            = gradX_a.addr;
    Context->pInBlock[1]            = gradY_b.addr;
    Context->pInBlock[2]            = im1_a.addr;
    Context->pInBlock[3]            = im2_b.addr;
    Context->pOutBlock[0]           = IxIt_a.addr;
    Context->pOutBlock[1]           = IyIt_b.addr;
    Context->pInternalBlock[0]      = scartch_a.addr;
    Context->pInternalBlock[1]      = scartch_b.addr;
    Context->kernelArgs.gradStride  = gradStride;
    Context->kernelArgs.imStride    = imStride;
    Context->kernelArgs.numBlocks   = n;
    
    return retVal;
}


void vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(unsigned short pblock[])
{
    vcop_sum_grad_cross_inter_frame_diff_7x7_Context *Context = (vcop_sum_grad_cross_inter_frame_diff_7x7_Context *)pblock;

#ifdef NATC
    vcop_sum_grad_cross_inter_frame_diff_7x7_cn(
      (short *)Context->pInBlock[0],
      (short *)Context->pInBlock[1],
      (unsigned char *)Context->pInBlock[2],
      (unsigned char *)Context->pInBlock[3],
      Context->kernelArgs.gradStride,
      Context->kernelArgs.imStride,
      Context->kernelArgs.numBlocks,
      (int *)Context->pOutBlock[0],
      (int *)Context->pOutBlock[1]
    );
#else
    vcop_sum_grad_cross_inter_frame_diff_7x7(
      Context->pInBlock[0],          
      Context->pInBlock[1],         
      Context->pInBlock[2],          
      Context->pInBlock[3],          
      Context->kernelArgs.gradStride,
      Context->kernelArgs.imStride,  
      Context->kernelArgs.numBlocks, 
      Context->pOutBlock[0],         
      Context->pOutBlock[1],         
      Context->pInternalBlock[0],
      Context->pInternalBlock[1]    
    );
#endif

}

unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_param_count(void)
{
    return (sizeof(vcop_sum_grad_cross_inter_frame_diff_7x7_Context));
}

#endif
