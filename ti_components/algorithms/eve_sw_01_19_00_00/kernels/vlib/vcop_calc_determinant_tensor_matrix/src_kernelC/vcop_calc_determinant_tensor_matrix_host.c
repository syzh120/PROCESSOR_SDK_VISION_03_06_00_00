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
/*     @file : vcop_calc_determinant_tensor_matrix_host.c              */
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

#if VCOP_HOST_EMULATION
void vcop_calc_determinant_tensor_matrix(
  __vptr_uint16 Ix2L_a, 
  __vptr_uint16 Iy2L_b,
  __vptr_uint16 IxyL_c,
  __vptr_int16  Ix2H_a, 
  __vptr_int16  Iy2H_b,
  __vptr_int16  IxyH_c,
  __vptr_uint16 d_nrsb_a,
  __vptr_int32  d_norm_b,
  unsigned short n);

typedef struct _vcop_calc_determinant_tensor_matrix_args
{
    unsigned short numBlocks;
} vcop_calc_determinant_tensor_matrix_Args;


typedef struct _vcop_calc_determinant_tensor_matrix_context
{
   void *pInBlock[6];
   void *pOutBlock[2];
    vcop_calc_determinant_tensor_matrix_Args kernelArgs;
} vcop_calc_determinant_tensor_matrix_Context;

unsigned short __pblock_vcop_calc_determinant_tensor_matrix[sizeof(vcop_calc_determinant_tensor_matrix_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_calc_determinant_tensor_matrix_init(
  __vptr_uint16 Ix2L_a, 
  __vptr_uint16 Iy2L_b,
  __vptr_uint16 IxyL_c,
  __vptr_int16  Ix2H_a, 
  __vptr_int16  Iy2H_b,
  __vptr_int16  IxyH_c,
  __vptr_uint16 d_nrsb_a,
  __vptr_int32  d_norm_b,
   unsigned short n,
   unsigned short pblock[])
{
    int retVal = 0;

    vcop_calc_determinant_tensor_matrix_Context *Context = (vcop_calc_determinant_tensor_matrix_Context *)pblock;

    Context->pInBlock[0]            = Ix2L_a.addr;
    Context->pInBlock[1]            = Iy2L_b.addr;
    Context->pInBlock[2]            = IxyL_c.addr;
    Context->pInBlock[3]            = Ix2H_a.addr;
    Context->pInBlock[4]            = Iy2H_b.addr;
    Context->pInBlock[5]            = IxyH_c.addr;
    Context->pOutBlock[0]           = d_nrsb_a.addr;
    Context->pOutBlock[1]           = d_norm_b.addr;
    Context->kernelArgs.numBlocks   = n;
    
    return retVal;
}


void vcop_calc_determinant_tensor_matrix_vloops(unsigned short pblock[])
{
    vcop_calc_determinant_tensor_matrix_Context *Context = (vcop_calc_determinant_tensor_matrix_Context *)pblock;

    vcop_calc_determinant_tensor_matrix(
      Context->pInBlock[0],        
      Context->pInBlock[1],         
      Context->pInBlock[2],         
      Context->pInBlock[3],         
      Context->pInBlock[4],         
      Context->pInBlock[5],         
      Context->pOutBlock[0],        
      Context->pOutBlock[1],        
      Context->kernelArgs.numBlocks
      );

}

unsigned int vcop_calc_determinant_tensor_matrix_param_count(void)
{
    return (sizeof(vcop_calc_determinant_tensor_matrix_Context));
}

#endif
