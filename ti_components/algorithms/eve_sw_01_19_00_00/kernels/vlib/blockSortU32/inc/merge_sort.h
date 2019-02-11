/*
*
* Copyright (c) {YEAR} Texas Instruments Incorporated
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

#ifndef _MERGE_SORT_H

#define _MERGE_SORT_H

#include <stdint.h>

#define MAX_PARAMS        1150U
#define MAX_FUNC_CALLS    32U

typedef void (*FUNC_PTR)(uint16_t* pblock);

typedef struct {
    FUNC_PTR funcs_exec[MAX_FUNC_CALLS]; /**< List the vloops that EVELIB_algoDMAAutoIncrProcess() will need to call */
    uint16_t *ptr_params[MAX_FUNC_CALLS]; /**< List the pointers to the param registers passed as arguments to the vloops */
    int32_t  (*my_out_offset_ptr)[];  /**< Internal usage */
    uint16_t *my_pblock_ptr; /**< Running pointer of the param blocks */
    int32_t  (*backup_my_out_offset_ptr)[];  /**< Pointer to where the output offsets are backed up in external memory as we don't want to generate them directly in WMEM */
    uint16_t *backup_my_pblock_ptr; /**< Running pointer of where the param blocks are backed up in external memory as we don't want to generate them directly in WMEM */
    uint32_t num_funcs_exec; /**< Number of vloops functions registered in funcs_exec */
} SortContext;

/* All the functions below are used internally by the implementation of EVELIB_sort() */
int32_t mergeSort_init(void *bufa, void *bufb, void *output, int32_t n, SortContext *c);

int32_t lmbd(int32_t x);

void vcop_sort8_simd8(int32_t niter, int32_t out_transpose, int32_t *in, int32_t *out, SortContext *c);

void swap_ptr(int32_t **x, int32_t **y);

int32_t  transp_idx(int32_t x, int32_t w1, int32_t w2);

int32_t bitonic_merge_multi_step
(
   int32_t     n,
   int32_t     comp_dist,
   int32_t     nsteps,
   int32_t     input_mode,
   int32_t     itransp,
   int32_t     otransp,
   int32_t     *input,
   int32_t     *output,
   SortContext *c
);

void vcop_psort2_1step
(
       int32_t niter1,
       int32_t niter2,
       int32_t niter3,
       int32_t in1_base,
       int32_t in2_base,
       int32_t in1ptr_w1,
       int32_t in1ptr_w2,
       int32_t in1ptr_w3,
       int32_t in2ptr_w1,
       int32_t in2ptr_w2,
       int32_t in2ptr_w3,
       int32_t out_base,
       int32_t outptr_ofst, /* point spread in a vector */
       int32_t out_base_step,
       int32_t outptr_w1,
       int32_t outptr_w2,
       int32_t outptr_w3,
       int32_t in_pad,  /* 0: array not padded, N: stride = N+1 */
       int32_t out_pad,
       int32_t reverse_pts,
       int32_t *input,
       int32_t *output,
       SortContext *c
       );

void vcop_psort2_2steps(
       int32_t niter1,
       int32_t niter2,
       int32_t niter3,
       int32_t in_base,
       int32_t in_base_step,
       int32_t in1ptr_w1,
       int32_t in1ptr_w2,
       int32_t in1ptr_w3,
       int32_t in2_base,
       int32_t in2ptr_w1,
       int32_t in2ptr_w2,
       int32_t in2ptr_w3,
       int32_t out_base,
       int32_t outptr_ofst,
       int32_t out_base_step,
       int32_t outptr_w1,
       int32_t outptr_w2,
       int32_t outptr_w3,
       int32_t in_pad,  /* 0: array not padded, N: stride = N+1 */
       int32_t out_pad,
       int32_t reverse_ptr,
       int32_t reverse_pts,
       int32_t *input,
       int32_t *output,
       SortContext *c);

void vcop_psort2_3steps(
       int32_t niter1,
       int32_t niter2,
       int32_t niter3,
       int32_t in_base,
       int32_t in_base_step,
       int32_t in1ptr_w1,
       int32_t in1ptr_w2,
       int32_t in1ptr_w3,
       int32_t in2_base,
       int32_t in2ptr_w1,
       int32_t in2ptr_w2,
       int32_t in2ptr_w3,
       int32_t out_base,
       int32_t outptr_ofst,
       int32_t out_base_step,
       int32_t outptr_w1,
       int32_t outptr_w2,
       int32_t outptr_w3,
       int32_t in_pad,  /* 0: array not padded, N: stride = N+1 */
       int32_t out_pad,
       int32_t reverse_ptr,
       int32_t reverse_pts,
       int32_t *input,
       int32_t *output,
       SortContext *c);

#endif
