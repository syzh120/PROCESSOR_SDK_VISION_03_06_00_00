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
/*     @file : vcop_median_filter_mxn_u8_host.c                             */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the underlying kernels.                               */
/*                                                                          */
/*     Host emulation wrapper functions for median filter:                  */
/*     1. vcop_update_block_histogram_8c                                    */
/*           vcop_update_block_histogram_8c_init - Copies arguments to      */
/*             global variables                                             */
/*           vcop_update_block_histogram_8c_vloops - Invokes the API namely */
/*             vcop_update_block_histogram_8c defined in kernel file by     */
/*             passing the arguments from global variables backup           */
/*     2. vcop_select_kth_smallest_from_hist                                */
/*           vcop_select_kth_smallest_from_hist_init - Copies arguments to  */
/*             global variables                                             */
/*           vcop_select_kth_smallest_from_hist_vloops - Invokes the API    */
/*             namely vcop_select_kth_smallest_from_hist defined in kernel  */
/*             file by passing the arguments from global variables backup.  */
/*                                                                          */
/*  @author Anoop K P(a-kp@ti.com)                                          */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_MEDIAN_FILTER_HOST
#define _VCOP_MEDIAN_FILTER_HOST  1

#include "vcop_host.h"

#if VCOP_HOST_EMULATION

unsigned int vcop_update_block_histogram_8c_init(
    unsigned char  *inp_data_A,
    unsigned char  *last_strip_A,
    short          *histo_B,
    char           *wgt_ones_C,
    char           *wgt_delta_C,
    short          *scratch_histo_C,
    short          *blk_histo_B,
    unsigned int    blk_wdth,
    unsigned int    blk_hght,
    unsigned int    blk_stride,
    unsigned short   *pblock);

void vcop_update_block_histogram_8c_vloops(
   unsigned short  *pblock);
   
unsigned int vcop_update_block_histogram_8c_param_count(void);

unsigned int vcop_select_kth_smallest_from_hist_init(
    short          *blk_histo_B,
    short          *coarse_hist_scratch_A,
    short          *hist_scratch_C,
    unsigned char  *optr_A,
    unsigned short  k,
    unsigned short *pblock);

void vcop_select_kth_smallest_from_hist_vloops(
   unsigned short   *pblock);

unsigned int vcop_select_kth_smallest_from_hist_param_count(void);

#endif

#endif

