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

#ifndef MERGE_SORT_KERNEL_HARD_H
#define MERGE_SORT_KERNEL_HARD_H  1

#include <vcop.h>
#include <stdint.h>
void my_vcop_sort8_simd8_64_custom
(
   int32_t             niter,
   int32_t             out_tr,
   __vptr_uint32    in,
   __vptr_uint32    out,
   uint16_t  *pblock
);

void my_vcop_sort8_simd8_XX_custom
(
   int32_t              niter,
   int32_t              out_tr,
   __vptr_uint32     in,
   __vptr_uint32     out,
   uint16_t   *pblock
);

void my_vcop_psort2_1step_reverse_kernel_custom
(
   int32_t              niter1,
   int32_t              niter2,
   int32_t              niter3,
   int32_t              ibase_0,
   int32_t              ibase_1,
   int32_t              in1ptr_w1,
   int32_t              in1ptr_w2,
   int32_t              in1ptr_w3,
   int32_t              in2ptr_w1,
   int32_t              in2ptr_w2,
   int32_t              in2ptr_w3,
   int32_t              obase_0,
   int32_t              obase_1,
   int32_t              outptr_w1,
   int32_t              outptr_w2,
   int32_t              outptr_w3,
   __vptr_uint32     input,
   __vptr_uint32     output,
   __vptr_int32     out_ofst,
   uint16_t   *pblock
);

void my_vcop_psort2_1step_kernel_custom
(
   int32_t              niter1,
   int32_t              niter2,
   int32_t              niter3,
   int32_t              ibase_0,
   int32_t              ibase_1,
   int32_t              in1ptr_w1,
   int32_t              in1ptr_w2,
   int32_t              in1ptr_w3,
   int32_t              in2ptr_w1,
   int32_t              in2ptr_w2,
   int32_t              in2ptr_w3,
   int32_t              obase_0,
   int32_t              obase_1,
   int32_t              outptr_w1,
   int32_t              outptr_w2,
   int32_t              outptr_w3,
   __vptr_uint32     input,
   __vptr_uint32     output,
   __vptr_int32     out_ofst,
   uint16_t   *pblock
);

void my_vcop_psort2_2steps_reverse_kernel_custom
(
   int32_t               niter1,
   int32_t               niter2,
   int32_t               niter3,
   int32_t               ibase_0,
   int32_t               ibase_1,
   int32_t               ibase_2,
   int32_t               ibase_3,
   int32_t               in1ptr_w1,
   int32_t               in1ptr_w2,
   int32_t               in1ptr_w3,
   int32_t               in2ptr_w1,
   int32_t               in2ptr_w2,
   int32_t               in2ptr_w3,
   int32_t               obase_0,
   int32_t               obase_1,
   int32_t               obase_2,
   int32_t               obase_3,
   int32_t               outptr_w1,
   int32_t               outptr_w2,
   int32_t               outptr_w3,
   __vptr_uint32      input,
   __vptr_uint32      output,
   __vptr_int32      out_ofst,
   uint16_t    *pblock
);

void my_vcop_psort2_2steps_kernel_custom
(
   int32_t               niter1,
   int32_t               niter2,
   int32_t               niter3,
   int32_t               ibase_0,
   int32_t               ibase_1,
   int32_t               ibase_2,
   int32_t               ibase_3,
   int32_t               in1ptr_w1,
   int32_t               in1ptr_w2,
   int32_t               in1ptr_w3,
   int32_t               in2ptr_w1,
   int32_t               in2ptr_w2,
   int32_t               in2ptr_w3,
   int32_t               obase_0,
   int32_t               obase_1,
   int32_t               obase_2,
   int32_t               obase_3,
   int32_t               outptr_w1,
   int32_t               outptr_w2,
   int32_t               outptr_w3,
   __vptr_uint32      input,
   __vptr_uint32      output,
   __vptr_int32      out_ofst,
   uint16_t    *pblock
);


void my_vcop_psort2_3steps_reverse_kernel_custom
(
   int32_t               niter1,
   int32_t               niter2,
   int32_t               niter3,
   int32_t               ibase_0,
   int32_t               ibase_1,
   int32_t               ibase_2,
   int32_t               ibase_3,
   int32_t               ibase_4,
   int32_t               ibase_5,
   int32_t               ibase_6,
   int32_t               ibase_7,
   int32_t               in1ptr_w1,
   int32_t               in1ptr_w2,
   int32_t               in1ptr_w3,
   int32_t               in2ptr_w1,
   int32_t               in2ptr_w2,
   int32_t               in2ptr_w3,
   int32_t               obase_0,
   int32_t               obase_1,
   int32_t               obase_2,
   int32_t               obase_3,
   int32_t               obase_4,
   int32_t               obase_5,
   int32_t               obase_6,
   int32_t               obase_7,
   int32_t               outptr_w1,
   int32_t               outptr_w2,
   int32_t               outptr_w3,
   __vptr_uint32      input,
   __vptr_uint32      output,
   __vptr_int32      out_ofst,
   uint16_t    *pblock
);

void my_vcop_psort2_3steps_kernel_custom
(
   int32_t                niter1,
   int32_t                niter2,
   int32_t                niter3,
   int32_t                ibase_0,
   int32_t                ibase_1,
   int32_t                ibase_2,
   int32_t                ibase_3,
   int32_t                ibase_4,
   int32_t                ibase_5,
   int32_t                ibase_6,
   int32_t                ibase_7,
   int32_t                in1ptr_w1,
   int32_t                in1ptr_w2,
   int32_t                in1ptr_w3,
   int32_t                in2ptr_w1,
   int32_t                in2ptr_w2,
   int32_t                in2ptr_w3,
   int32_t                obase_0,
   int32_t                obase_1,
   int32_t                obase_2,
   int32_t                obase_3,
   int32_t                obase_4,
   int32_t                obase_5,
   int32_t                obase_6,
   int32_t                obase_7,
   int32_t                outptr_w1,
   int32_t                outptr_w2,
   int32_t                outptr_w3,
   __vptr_uint32       input,
   __vptr_uint32       output,
   __vptr_int32       out_ofst,
   uint16_t     *pblock
);

void my_vcop_remove_ex_col_custom
(
   __vptr_uint32       input,
   __vptr_uint32       output,
   int32_t                nitems,
   uint16_t     *pblock
);
#endif










