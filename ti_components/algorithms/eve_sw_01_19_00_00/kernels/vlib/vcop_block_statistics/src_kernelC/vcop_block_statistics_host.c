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
/*     @file : vcop_block_statistics_host.c                                 */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for block statistics:               */
/*           vcop_block_statistics_init - Copies arguments to global        */
/*             variables                                                    */
/*           vcop_block_statistics_vloops - Invokes the API namely          */
/*             vcop_block_statistics defined in kernel file by passing the  */
/*             arguments from global variables backup                       */
/*                                                                          */
/*  @author Anoop K P(a-kp@ti.com)                                          */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#if VCOP_HOST_EMULATION
#include "vcop_block_statistics_kernel.k"

static unsigned char     *gim_A;
static unsigned short     gblockStride;
static unsigned short     gblockWidth;
static unsigned short     gblockHeight;
static unsigned short     gstatBlockWidth;
static unsigned short     gstatBlockHeight;
static unsigned char     *gscratch_C;
static unsigned short    *gscratchSum_A;
static unsigned int      *gscratchSumSq_B;
static unsigned int      *gscratchSumSq_C;
static unsigned short    *gscratchSumSq_C_lo;
static unsigned short    *gscratchSumSq_C_hi;
static unsigned char     *gmin_B;
static unsigned char     *gmax_B;
static unsigned short    *gmean_B;
static unsigned int      *gvariance_A;

unsigned int vcop_block_statistics_init(
    unsigned char   *im_A,
    unsigned short   blockStride,
    unsigned short   blockWidth,
    unsigned short   blockHeight,
    unsigned short   statBlockWidth,
    unsigned short   statBlockHeight,
    unsigned char   *scratch_C,
    unsigned short  *scratchSum_A,
    unsigned int    *scratchSumSq_B,
    unsigned int    *scratchSumSq_C,
    unsigned short  *scratchSumSq_C_lo,
    unsigned short  *scratchSumSq_C_hi,
    unsigned char   *min_B,
    unsigned char   *max_B,
    unsigned short  *mean_B,
    unsigned int    *variance_A,
   unsigned short   *pblock)
{
   int retVal = 0;

    gim_A = im_A;
    gblockStride = blockStride;
    gblockWidth = blockWidth;
    gblockHeight = blockHeight;
    gstatBlockWidth = statBlockWidth;
    gstatBlockHeight = statBlockHeight;
    gscratch_C = scratch_C;
    gscratchSum_A = scratchSum_A;
    gscratchSumSq_B = scratchSumSq_B;
    gscratchSumSq_C = scratchSumSq_C;
    gscratchSumSq_C_lo = scratchSumSq_C_lo;
    gscratchSumSq_C_hi = scratchSumSq_C_hi;
    gmin_B = min_B;
    gmax_B = max_B;
    gmean_B = mean_B;
    gvariance_A = variance_A;

   return retVal;
}

void vcop_block_statistics_vloops(
   unsigned short   *pblock)
{
   vcop_block_statistics(gim_A, gblockStride, gblockWidth, gblockHeight,
                         gstatBlockWidth, gstatBlockHeight, gscratch_C,
                         gscratchSum_A, gscratchSumSq_B, gscratchSumSq_C,
                         gscratchSumSq_C_lo, gscratchSumSq_C_hi, gmin_B,
                         gmax_B, gmean_B, gvariance_A);
}

#endif
