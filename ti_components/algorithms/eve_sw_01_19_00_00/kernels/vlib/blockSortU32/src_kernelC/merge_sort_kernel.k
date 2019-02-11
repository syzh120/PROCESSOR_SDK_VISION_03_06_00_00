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

/*-------------------------------------------------------------------------*/
/* NAME: merge_sort_kernel.k : Sort any 2^N size array on VCOP.            */
/*                                                                         */
/* AUTHOR: J.Sankaran                                                      */
/*                                                                         */
/* REVISON HISTORY:                                                        */
/* 04/16/13.........Wrote initial version of code............J.Sankaran    */
/*                                                                         */
/* DESCRIPTION:                                                            */
/* The file "merge_sort_kernel.k" contains various functions that          */
/* form part of the sort library. These helper functions are written       */
/* in kernel-C and have the following intent:                              */
/*                                                                         */
/* The function has the following prototype:                               */
/*                                                                         */
/* 1. void vcop_sort8_simd8_64                                             */
/*    (                                                                    */
/*        int           niter,                                             */
/*        int           out_tr,                                            */
/*        __vptr_uint32  in,                                                */
/*        __vptr_uint32  out                                                */
/*    )                                                                    */
/*                                                                         */
/*    Specialized function to call when N the number of points to sort     */
/*    is 64. It implements one 8x8 block sort and transposes the data      */
/*    immediately. Specifically "niter" will always be 1, and "out_tr"     */
/*    will be 1, requesting a tranpose be performed on the output          */
/*    immediately. These extra redundant arguments, are there because      */
/*    C code implementation is generic. No error checking is performed     */
/*    on these arguments.                                                  */
/*                                                                         */
/*  2. void vcop_sort8_simd8_XX                                            */
/*     (                                                                   */
/*         int           niter,                                            */
/*         int           out_tr,                                           */
/*         __vptr_uint32  in,                                               */
/*         __vptr_uint32  out                                               */
/*     )                                                                   */
/*                                                                         */
/*     Generic block sort for "niter" 8x8 blocks at starting address       */
/*     "in" sorted within the column and written to output. It is          */
/*     assumed that "out_tr" request to transpose output is always         */
/*     "0" and we do not transpose the data.                               */
/*                                                                         */
/*                                                                         */
/*  3. void vcop_psort2_1step_reverse_kernel                               */
/*     (                                                                   */
/*        int           niter1,                                            */
/*        int           niter2,                                            */
/*        int           niter3,                                            */
/*        int           ibase_0,                                           */
/*        int           ibase_1,                                           */
/*        int           in1ptr_w1,                                         */
/*        int           in1ptr_w2,                                         */
/*        int           in1ptr_w3,                                         */
/*        int           in2ptr_w1,                                         */
/*        int           in2ptr_w2,                                         */
/*        int           in2ptr_w3,                                         */
/*        int           obase_0,                                           */
/*        int           obase_1,                                           */
/*        int           outptr_w1,                                         */
/*        int           outptr_w2,                                         */
/*        int           outptr_w3,                                         */
/*        __vptr_uint32  input,                                             */
/*        __vptr_uint32  output,                                            */
/*        __vptr_int32  out_ofst                                           */
/*     )                                                                   */
/*                                                                         */
/*     This function implements a 1-step sort, possibly iterating a        */
/*     maximum of 3 loop levels as specified by "niter1", "niter2"         */
/*     and "niter3", reading inputs from a base offset address as          */
/*     "ibase_0", "ibase_1". Input pointer adjustments at each loop        */
/*     level are "in1ptr_w1", "in1ptr_w2", "in1ptr_w3" for the first       */
/*     input, "in2ptr_w1", "in2ptr_w2", "in2ptr_w3" for the second         */
/*     input at each of the loop levels. The two outputs are written       */
/*     into address "output" at base offsets "obase0" and "obase1"         */
/*     incrementing the asoociated pointer by "outptr_w1", "outptr_w2"     */
/*     and "outptr_w3". The output may be transposed and written in        */
/*     at locations "out_ofst". The "reverse" at the end of the            */
/*     function is indicating data for the second input is read in         */
/*     the opposite order.                                                 */
/*                                                                         */
/*                                                                         */
/*   4. void vcop_psort2_1step_kernel                                      */
/*      (                                                                  */
/*         int           niter1,                                           */
/*         int           niter2,                                           */
/*         int           niter3,                                           */
/*         int           ibase_0,                                          */
/*         int           ibase_1,                                          */
/*         int           in1ptr_w1,                                        */
/*         int           in1ptr_w2,                                        */
/*         int           in1ptr_w3,                                        */
/*         int           in2ptr_w1,                                        */
/*         int           in2ptr_w2,                                        */
/*         int           in2ptr_w3,                                        */
/*         int           obase_0,                                          */
/*         int           obase_1,                                          */
/*         int           outptr_w1,                                        */
/*         int           outptr_w2,                                        */
/*         int           outptr_w3,                                        */
/*         __vptr_uint32  input,                                            */
/*         __vptr_uint32  output,                                           */
/*         __vptr_int32  out_ofst                                          */
/*      )                                                                  */
/*                                                                         */
/*      This is the same function that implements a 1-step sort, with      */
/*      the key difference being, that the second input is read in a       */
/*      normal order.                                                      */
/*                                                                         */
/*    5. void vcop_psort2_2steps_reverse_kernel                            */
/*       (                                                                 */
/*           int           niter1,                                         */
/*           int           niter2,                                         */
/*           int           niter3,                                         */
/*           int           ibase_0,                                        */
/*           int           ibase_1,                                        */
/*           int           ibase_2,                                        */
/*           int           ibase_3,                                        */
/*           int           in1ptr_w1,                                      */
/*           int           in1ptr_w2,                                      */
/*           int           in1ptr_w3,                                      */
/*           int           in2ptr_w1,                                      */
/*           int           in2ptr_w2,                                      */
/*           int           in2ptr_w3,                                      */
/*           int           obase_0,                                        */
/*           int           obase_1,                                        */
/*           int           obase_2,                                        */
/*           int           obase_3,                                        */
/*           int           outptr_w1,                                      */
/*           int           outptr_w2,                                      */
/*           int           outptr_w3,                                      */
/*           __vptr_uint32  input,                                          */
/*           __vptr_uint32  output,                                         */
/*           __vptr_int32  out_ofst                                        */
/*        )                                                                */
/*                                                                         */
/*        This function implements a 2-step sort, with the second step     */
/*        being half the jump of the first step. The remaining arguments   */
/*        are the same. The reverse indicates, that the second input       */
/*        is read in reverse.                                              */
/*                                                                         */
/*     6.  void vcop_psort2_2steps_kernel                                  */
/*         (                                                               */
/*            int           niter1,                                        */
/*            int           niter2,                                        */
/*            int           niter3,                                        */
/*            int           ibase_0,                                       */
/*            int           ibase_1,                                       */
/*            int           ibase_2,                                       */
/*            int           ibase_3,                                       */
/*            int           in1ptr_w1,                                     */
/*            int           in1ptr_w2,                                     */
/*            int           in1ptr_w3,                                     */
/*            int           in2ptr_w1,                                     */
/*            int           in2ptr_w2,                                     */
/*            int           in2ptr_w3,                                     */
/*            int           obase_0,                                       */
/*            int           obase_1,                                       */
/*            int           obase_2,                                       */
/*            int           obase_3,                                       */
/*            int           outptr_w1,                                     */
/*            int           outptr_w2,                                     */
/*            int           outptr_w3,                                     */
/*            __vptr_uint32  input,                                         */
/*            __vptr_uint32  output,                                        */
/*            __vptr_int32  out_ofst                                       */
/*         )                                                               */
/*                                                                         */
/*        This function implements a 2-step sort, with the second input    */
/*        being read normally.                                             */
/*                                                                         */
/*                                                                         */
/*        7. void vcop_psort2_3steps_reverse_kernel                        */
/*           (                                                             */
/*              int           niter1,                                      */
/*              int           niter2,                                      */
/*              int           niter3,                                      */
/*              int           ibase_0,                                     */
/*              int           ibase_1,                                     */
/*              int           ibase_2,                                     */
/*              int           ibase_3,                                     */
/*              int           ibase_4,                                     */
/*              int           ibase_5,                                     */
/*              int           ibase_6,                                     */
/*              int           ibase_7,                                     */
/*              int           in1ptr_w1,                                   */
/*              int           in1ptr_w2,                                   */
/*              int           in1ptr_w3,                                   */
/*              int           in2ptr_w1,                                   */
/*              int           in2ptr_w2,                                   */
/*              int           in2ptr_w3,                                   */
/*              int           obase_0,                                     */
/*              int           obase_1,                                     */
/*              int           obase_2,                                     */
/*              int           obase_3,                                     */
/*              int           obase_4,                                     */
/*              int           obase_5,                                     */
/*              int           obase_6,                                     */
/*              int           obase_7,                                     */
/*              int           outptr_w1,                                   */
/*              int           outptr_w2,                                   */
/*              int           outptr_w3,                                   */
/*              __vptr_uint32  input,                                       */
/*              __vptr_uint32  output,                                      */
/*              __vptr_int32  out_ofst                                     */
/*           )                                                             */
/*                                                                         */
/*           This is the 3-step function, with each stage being half       */
/*           the distance in each step to implement distances 4, 2         */
/*           and 1. Half the inputs, are read in the reverse direction     */
/*           for the bottom inputs.                                        */
/*                                                                         */
/*                                                                         */
/*      8. void vcop_psort2_3steps_kernel                                  */
/*         (                                                               */
/*            int           niter1,                                        */
/*            int           niter2,                                        */
/*            int           niter3,                                        */
/*            int           ibase_0,                                       */
/*            int           ibase_1,                                       */
/*            int           ibase_2,                                       */
/*            int           ibase_3,                                       */
/*            int           ibase_4,                                       */
/*            int           ibase_5,                                       */
/*            int           ibase_6,                                       */
/*            int           ibase_7,                                       */
/*            int           in1ptr_w1,                                     */
/*            int           in1ptr_w2,                                     */
/*            int           in1ptr_w3,                                     */
/*            int           in2ptr_w1,                                     */
/*            int           in2ptr_w2,                                     */
/*            int           in2ptr_w3,                                     */
/*            int           obase_0,                                       */
/*            int           obase_1,                                       */
/*            int           obase_2,                                       */
/*            int           obase_3,                                       */
/*            int           obase_4,                                       */
/*            int           obase_5,                                       */
/*            int           obase_6,                                       */
/*            int           obase_7,                                       */
/*            int           outptr_w1,                                     */
/*            int           outptr_w2,                                     */
/*            int           outptr_w3,                                     */
/*            __vptr_uint32  input,                                         */
/*            __vptr_uint32  output,                                        */
/*            __vptr_int32  out_ofst                                       */
/*         )                                                               */
/*                                                                         */
/*         This is the 3-step function, with each stage being half         */
/*         the distance in each step to implement the distances 4, 2,      */
/*         and 1. The inputs are all read in the same order.               */
/*                                                                         */
/*                                                                         */
/*       9. void vcop_remove_ex_col                                        */
/*          (                                                              */
/*              __vptr_uint32   input,                                      */
/*              __vptr_uint32   output,                                     */
/*              int            nitems                                      */
/*          )                                                              */
/*                                                                         */
/*         This function removes the extra column in the input after       */
/*         every 8 words, where the 9th word is junk. This is the last     */
/*         function, that gets called.                                     */
/*                                                                         */
/* ASSUMPTIONS:                                                            */
/*                                                                         */
/* This function assumes that the input and output arrays are always       */
/* 32-bit arrays. When needing to sort 8-bit and 16-bit data values,       */
/* we need to promote to 32-bit, do the sorting and then convert back.     */
/* This converting back, can be done by vcop_remove_ex_col, and saturate   */
/* back to the limits.                                                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                               */
/*=========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define IN_ELEMSZ       sizeof(*in)
#define OU_ELEMSZ       sizeof(*out)
#define VECTOR_SZ       (VCOP_SIMD_WIDTH *       IN_ELEMSZ)
#define OVECTOR_SZ      ((VCOP_SIMD_WIDTH + 1) * OU_ELEMSZ)

#define IR0    (0 * VECTOR_SZ)
#define IR1    (1 * VECTOR_SZ)
#define IR2    (2 * VECTOR_SZ)
#define IR3    (3 * VECTOR_SZ)
#define IR4    (4 * VECTOR_SZ)
#define IR5    (5 * VECTOR_SZ)
#define IR6    (6 * VECTOR_SZ)
#define IR7    (7 * VECTOR_SZ)


#define OR0    (0 * VECTOR_SZ)
#define OR1    (1 * VECTOR_SZ)
#define OR2    (2 * VECTOR_SZ)
#define OR3    (3 * VECTOR_SZ)
#define OR4    (4 * VECTOR_SZ)
#define OR5    (5 * VECTOR_SZ)
#define OR6    (6 * VECTOR_SZ)
#define OR7    (7 * VECTOR_SZ)

#define OTR0    (0)
#define OTR1    (4)
#define OTR2    (8)
#define OTR3    (12)
#define OTR4    (16)
#define OTR5    (20)
#define OTR6    (24)
#define OTR7    (28)


void vcop_sort8_simd8_64
(
    int           niter,
    int           out_tr,
    __vptr_uint32  in,
    __vptr_uint32  out
)
{
     __vector   Vin0;
     __vector   Vin1;
     __vector   Vin2;
     __vector   Vin3;
     __vector   Vin4;
     __vector   Vin5;
     __vector   Vin6;
     __vector   Vin7;


     for (int I1 = 0; I1 < 1; I1++)
     {
         __agen   Addr  = I1*0;

         Vin0 = (in + IR0)[Addr];
         Vin1 = (in + IR1)[Addr];
         Vin2 = (in + IR2)[Addr];
         Vin3 = (in + IR3)[Addr];
         Vin4 = (in + IR4)[Addr];
         Vin5 = (in + IR5)[Addr];
         Vin6 = (in + IR6)[Addr];
         Vin7 = (in + IR7)[Addr];

         (Vin0, Vin1).minmax();
         (Vin2, Vin3).minmax();
         (Vin0, Vin2).minmax();
         (Vin1, Vin3).minmax();
         (Vin1, Vin2).minmax();

         (Vin4, Vin5).minmax();
         (Vin6, Vin7).minmax();
         (Vin4, Vin6).minmax();
         (Vin5, Vin7).minmax();
         (Vin5, Vin6).minmax();

         (Vin0, Vin4).minmax();
         (Vin2, Vin6).minmax();
         (Vin2, Vin4).minmax();
         (Vin1, Vin5).minmax();
         (Vin3, Vin7).minmax();
         (Vin3, Vin5).minmax();

         (Vin1, Vin2).minmax();
         (Vin3, Vin4).minmax();
         (Vin5, Vin6).minmax();

         (out + OTR0)[Addr].offset_np1() = Vin0;
         (out + OTR1)[Addr].offset_np1() = Vin1;
         (out + OTR2)[Addr].offset_np1() = Vin2;
         (out + OTR3)[Addr].offset_np1() = Vin3;
         (out + OTR4)[Addr].offset_np1() = Vin4;
         (out + OTR5)[Addr].offset_np1() = Vin5;
         (out + OTR6)[Addr].offset_np1() = Vin6;
         (out + OTR7)[Addr].offset_np1() = Vin7;
     }
}


void vcop_sort8_simd8_XX
(
    int           niter,
    int           out_tr,
    __vptr_uint32  in,
    __vptr_uint32  out
)
{
     __vector   Vin0;
     __vector   Vin1;
     __vector   Vin2;
     __vector   Vin3;
     __vector   Vin4;
     __vector   Vin5;
     __vector   Vin6;
     __vector   Vin7;


     for (int I1 = 0; I1 < niter; I1++)
     {
         __agen   Addr  = VCOP_SIMD_WIDTH * VCOP_SIMD_WIDTH * IN_ELEMSZ * I1;

         Vin0 = (in + IR0)[Addr];
         Vin1 = (in + IR1)[Addr];
         Vin2 = (in + IR2)[Addr];
         Vin3 = (in + IR3)[Addr];
         Vin4 = (in + IR4)[Addr];
         Vin5 = (in + IR5)[Addr];
         Vin6 = (in + IR6)[Addr];
         Vin7 = (in + IR7)[Addr];

         (Vin0, Vin1).minmax();
         (Vin2, Vin3).minmax();
         (Vin0, Vin2).minmax();
         (Vin1, Vin3).minmax();
         (Vin1, Vin2).minmax();

         (Vin4, Vin5).minmax();
         (Vin6, Vin7).minmax();
         (Vin4, Vin6).minmax();
         (Vin5, Vin7).minmax();
         (Vin5, Vin6).minmax();

         (Vin0, Vin4).minmax();
         (Vin2, Vin6).minmax();
         (Vin2, Vin4).minmax();
         (Vin1, Vin5).minmax();
         (Vin3, Vin7).minmax();
         (Vin3, Vin5).minmax();

         (Vin1, Vin2).minmax();
         (Vin3, Vin4).minmax();
         (Vin5, Vin6).minmax();

         (out + OR0)[Addr] = Vin0;
         (out + OR1)[Addr] = Vin1;
         (out + OR2)[Addr] = Vin2;
         (out + OR3)[Addr] = Vin3;
         (out + OR4)[Addr] = Vin4;
         (out + OR5)[Addr] = Vin5;
         (out + OR6)[Addr] = Vin6;
         (out + OR7)[Addr] = Vin7;
     }
}


#define K0      0
#define K1      1
#define K2      2
#define K3      3
#define K4      4
#define K5      5
#define K6      6
#define K7      7

void vcop_psort2_1step_reverse_kernel
(
   int           niter1,
   int           niter2,
   int           niter3,
   int           ibase_0,
   int           ibase_1,
   int           in1ptr_w1,
   int           in1ptr_w2,
   int           in1ptr_w3,
   int           in2ptr_w1,
   int           in2ptr_w2,
   int           in2ptr_w3,
   int           obase_0,
   int           obase_1,
   int           outptr_w1,
   int           outptr_w2,
   int           outptr_w3,
   __vptr_uint32  input,
   __vptr_uint32  output,
   __vptr_int32  out_ofst
)
{
   __vector  Vin0;
   __vector  Vin1;
   __vector  Vin2;
   __vector  Vin3;
   __vector  Vin4;
   __vector  Vin5;
   __vector  Vin6;
   __vector  Vin7;
   __vector  Vin0_c;
   __vector  Vin0_d;
   __vector  Vindex1;
   __vector  Vindex2;


    for (int I1=0; I1 < niter1; I1++)
    {
        for (int I2=0; I2 < niter2; I2++)
        {
            for (int I3=0; I3 < niter3; I3++)
            {
                __agen Addr_in1 = I1 * in1ptr_w1 + I2 * in1ptr_w2 + I3 * in1ptr_w3;
                __agen Addr_in2 = I1 * in2ptr_w1 + I2 * in2ptr_w2 + I3 * in2ptr_w3;
                __agen Addr_ou1 = I1 * outptr_w1 + I2 * outptr_w2 + I3 * outptr_w3;
                __agen Addr_in  = I1 * 0         + I2 * 0         + I3 * 0;

                Vindex2  = out_ofst[Addr_in].npt();

                Vin0_c = (input + ibase_0)[Addr_in1].npt();
                Vin1   = (input + ibase_1)[Addr_in2].dist (K7, K6, K5, K4, K3, K2, K1, K0);

                (Vin0_c, Vin1).minmax();
                Vin0         =  Vindex2;

                (output + obase_0)[Addr_ou1].p_scatter(Vin0)  =   Vin0_c;
                (output + obase_1)[Addr_ou1].p_scatter(Vin0)  =   Vin1;
            }
        }
    }

}

void vcop_psort2_1step_kernel
(
   int           niter1,
   int           niter2,
   int           niter3,
   int           ibase_0,
   int           ibase_1,
   int           in1ptr_w1,
   int           in1ptr_w2,
   int           in1ptr_w3,
   int           in2ptr_w1,
   int           in2ptr_w2,
   int           in2ptr_w3,
   int           obase_0,
   int           obase_1,
   int           outptr_w1,
   int           outptr_w2,
   int           outptr_w3,
   __vptr_uint32  input,
   __vptr_uint32  output,
   __vptr_int32  out_ofst
)
{
   __vector  Vin0;
   __vector  Vin1;
   __vector  Vin2;
   __vector  Vin3;
   __vector  Vin4;
   __vector  Vin5;
   __vector  Vin6;
   __vector  Vin7;
   __vector  Vin0_c;
   __vector  Vin0_d;
   __vector  Vindex1;
   __vector  Vindex2;


    for (int I1=0; I1 < niter1; I1++)
    {
        for (int I2=0; I2 < niter2; I2++)
        {
            for (int I3=0; I3 < niter3; I3++)
            {
                __agen Addr_in1 = I1 * in1ptr_w1 + I2 * in1ptr_w2 + I3 * in1ptr_w3;
                __agen Addr_in2 = I1 * in2ptr_w1 + I2 * in2ptr_w2 + I3 * in2ptr_w3;
                __agen Addr_ou1 = I1 * outptr_w1 + I2 * outptr_w2 + I3 * outptr_w3;
                __agen Addr_in  = I1 * 0         + I2 * 0         + I3 * 0;

                Vindex2  = out_ofst[Addr_in].npt();

                Vin0_c = (input + ibase_0)[Addr_in1].npt();
                Vin1   = (input + ibase_1)[Addr_in2].npt();

                (Vin0_c, Vin1).minmax();
                Vin0         =  Vindex2;

                (output + obase_0)[Addr_ou1].p_scatter(Vin0) =   Vin0_c;
                (output + obase_1)[Addr_ou1].p_scatter(Vin0) =   Vin1;
            }
        }
    }
}


void vcop_psort2_2steps_reverse_kernel
(
   int           niter1,
   int           niter2,
   int           niter3,
   int           ibase_0,
   int           ibase_1,
   int           ibase_2,
   int           ibase_3,
   int           in1ptr_w1,
   int           in1ptr_w2,
   int           in1ptr_w3,
   int           in2ptr_w1,
   int           in2ptr_w2,
   int           in2ptr_w3,
   int           obase_0,
   int           obase_1,
   int           obase_2,
   int           obase_3,
   int           outptr_w1,
   int           outptr_w2,
   int           outptr_w3,
   __vptr_uint32  input,
   __vptr_uint32  output,
   __vptr_int32  out_ofst
)
{
__vector  Vin0;
__vector  Vin1;
__vector  Vin2;
__vector  Vin3;
__vector  Vin4;
__vector  Vin5;
__vector  Vin6;
__vector  Vin7;
__vector  Vin0_c;
__vector  Vin0_d;
__vector  Vindex1;
__vector  Vindex2;


    for (int I1 = 0; I1 < niter1; I1++)
    {
        for (int I2 = 0; I2 < niter2; I2++)
        {
            for (int I3 = 0; I3 < niter3; I3++)
            {
                __agen Addr_in1 = I1 * in1ptr_w1 + I2 * in1ptr_w2 + I3 * in1ptr_w3;
                __agen Addr_in2 = I1 * in2ptr_w1 + I2 * in2ptr_w2 + I3 * in2ptr_w3;
                __agen Addr_ou1 = I1 * outptr_w1 + I2 * outptr_w2 + I3 * outptr_w3;
                __agen Addr_in  = I1* 0          + I2 * 0         + I3 * 0;

                Vin0    = (input + ibase_0)[Addr_in1].npt();
                Vin1    = (input + ibase_1)[Addr_in1].npt();
                Vin2    = (input + ibase_2)[Addr_in1].dist(K7, K6, K5, K4, K3, K2, K1, K0);
                Vin3    = (input + ibase_3)[Addr_in1].dist(K7, K6, K5, K4, K3, K2, K1, K0);
                Vindex2 = out_ofst[Addr_in].npt();

                (Vin0, Vin2).minmax();
                (Vin1, Vin3).minmax();
                (Vin0, Vin1).minmax();
                (Vin2, Vin3).minmax();

                Vin0_d  =  Vin0;    // Snap shot sorted V0
                Vin0    =  Vindex2; // Scatter index has to be in V0.

                (output + obase_0)[Addr_ou1].p_scatter(Vin0) = Vin0_d;
                (output + obase_1)[Addr_ou1].p_scatter(Vin0) = Vin1;
                (output + obase_2)[Addr_ou1].p_scatter(Vin0) = Vin2;
                (output + obase_3)[Addr_ou1].p_scatter(Vin0) = Vin3;
            }
        }
    }
}

void vcop_psort2_2steps_kernel
(
   int           niter1,
   int           niter2,
   int           niter3,
   int           ibase_0,
   int           ibase_1,
   int           ibase_2,
   int           ibase_3,
   int           in1ptr_w1,
   int           in1ptr_w2,
   int           in1ptr_w3,
   int           in2ptr_w1,
   int           in2ptr_w2,
   int           in2ptr_w3,
   int           obase_0,
   int           obase_1,
   int           obase_2,
   int           obase_3,
   int           outptr_w1,
   int           outptr_w2,
   int           outptr_w3,
   __vptr_uint32  input,
   __vptr_uint32  output,
   __vptr_int32  out_ofst
)
{
    __vector  Vin0;
    __vector  Vin1;
    __vector  Vin2;
    __vector  Vin3;
    __vector  Vin4;
    __vector  Vin5;
    __vector  Vin6;
    __vector  Vin7;
    __vector  Vin0_c;
    __vector  Vin0_d;
    __vector  Vindex1;
    __vector  Vindex2;

    for (int I1 = 0; I1 < niter1; I1++)
    {
        for (int I2 = 0; I2 < niter2; I2++)
        {
            for (int I3 = 0; I3 < niter3; I3++)
            {
                __agen Addr_in1 = I1 * in1ptr_w1 + I2 * in1ptr_w2 + I3 * in1ptr_w3;
                __agen Addr_in2 = I1 * in2ptr_w1 + I2 * in2ptr_w2 + I3 * in2ptr_w3;
                __agen Addr_ou1 = I1 * outptr_w1 + I2 * outptr_w2 + I3 * outptr_w3;
                __agen Addr_in  = I1* 0          + I2 * 0         + I3 * 0;

                Vin0    = (input + ibase_0)[Addr_in1].npt();
                Vin1    = (input + ibase_1)[Addr_in1].npt();
                Vin2    = (input + ibase_2)[Addr_in1].npt();
                Vin3    = (input + ibase_3)[Addr_in1].npt();
                Vindex2 = out_ofst[Addr_in].npt();

                (Vin0, Vin2).minmax();
                (Vin1, Vin3).minmax();
                (Vin0, Vin1).minmax();
                (Vin2, Vin3).minmax();

                Vin0_d  =  Vin0;    // Snap shot sorted V0
                Vin0    =  Vindex2; // Scatter index has to be in V0.

                (output + obase_0)[Addr_ou1].p_scatter(Vin0) = Vin0_d;
                (output + obase_1)[Addr_ou1].p_scatter(Vin0) = Vin1;
                (output + obase_2)[Addr_ou1].p_scatter(Vin0) = Vin2;
                (output + obase_3)[Addr_ou1].p_scatter(Vin0) = Vin3;
            }
        }
    }
}



void vcop_psort2_3steps_reverse_kernel
(
   int           niter1,
   int           niter2,
   int           niter3,
   int           ibase_0,
   int           ibase_1,
   int           ibase_2,
   int           ibase_3,
   int           ibase_4,
   int           ibase_5,
   int           ibase_6,
   int           ibase_7,
   int           in1ptr_w1,
   int           in1ptr_w2,
   int           in1ptr_w3,
   int           in2ptr_w1,
   int           in2ptr_w2,
   int           in2ptr_w3,
   int           obase_0,
   int           obase_1,
   int           obase_2,
   int           obase_3,
   int           obase_4,
   int           obase_5,
   int           obase_6,
   int           obase_7,
   int           outptr_w1,
   int           outptr_w2,
   int           outptr_w3,
   __vptr_uint32  input,
   __vptr_uint32  output,
   __vptr_int32  out_ofst
)
{
    __vector  Vin0;
    __vector  Vin1;
    __vector  Vin2;
    __vector  Vin3;
    __vector  Vin4;
    __vector  Vin5;
    __vector  Vin6;
    __vector  Vin7;
    __vector  Vin0_c;
    __vector  Vin0_d;
    __vector  Vindex1;
    __vector  Vindex2;

    /*--------------------------------------------------------------------*/
    /* We can only do 8 loads in the innermost loop. Read the offset      */
    /* register in Vindex1, and this requires a 9th load is required      */
    /* which we pre-load and forward the result of this load.             */
    /*--------------------------------------------------------------------*/

    for (int I1 = 0; I1 < 1;  I1++)
    {
        __agen   Addr_in = I1* 0;

        Vindex1 = out_ofst[Addr_in].npt();
        Vindex2 = Vindex1;
    }


    for (int I1 = 0; I1 < niter1; I1++)
    {
        for (int I2 = 0; I2 < niter2; I2++)
        {
            for (int I3 = 0; I3 < niter3; I3++)
            {
                __agen Addr_in1 = I1 * in1ptr_w1 + I2 * in1ptr_w2 + I3 * in1ptr_w3;
                __agen Addr_in2 = I1 * in2ptr_w1 + I2 * in2ptr_w2 + I3 * in2ptr_w3;
                __agen Addr_ou1 = I1 * outptr_w1 + I2 * outptr_w2 + I3 * outptr_w3;

                Vin0 = (input + ibase_0)[Addr_in1].npt();
                Vin1 = (input + ibase_1)[Addr_in1].npt();
                Vin2 = (input + ibase_2)[Addr_in1].npt();
                Vin3 = (input + ibase_3)[Addr_in1].npt();

                Vin4 = (input + ibase_4)[Addr_in2].dist(K7, K6, K5, K4, K3, K2, K1, K0);
                Vin5 = (input + ibase_5)[Addr_in2].dist(K7, K6, K5, K4, K3, K2, K1, K0);
                Vin6 = (input + ibase_6)[Addr_in2].dist(K7, K6, K5, K4, K3, K2, K1, K0);
                Vin7 = (input + ibase_7)[Addr_in2].dist(K7, K6, K5, K4, K3, K2, K1, K0);

                /*--------------------------------------------------------*/
                /*  Use the vector registers and sort 4, 2 and 1 away     */
                /*  without going back to memory.                         */
                /*--------------------------------------------------------*/

                (Vin0, Vin4).minmax();
                (Vin1, Vin5).minmax();
                (Vin2, Vin6).minmax();
                (Vin3, Vin7).minmax();

                (Vin0, Vin2).minmax();
                (Vin1, Vin3).minmax();
                (Vin4, Vin6).minmax();
                (Vin5, Vin7).minmax();

                (Vin0, Vin1).minmax();
                (Vin2, Vin3).minmax();
                (Vin4, Vin5).minmax();
                (Vin6, Vin7).minmax();

                Vin0_d  =  Vin0;    // Snap shot sorted V0
                Vin0    =  Vindex2; // Scatter index has to be in V0.

                (output + obase_0)[Addr_ou1].p_scatter(Vin0) = Vin0_d;
                (output + obase_1)[Addr_ou1].p_scatter(Vin0) = Vin1;
                (output + obase_2)[Addr_ou1].p_scatter(Vin0) = Vin2;
                (output + obase_3)[Addr_ou1].p_scatter(Vin0) = Vin3;
                (output + obase_4)[Addr_ou1].p_scatter(Vin0) = Vin4;
                (output + obase_5)[Addr_ou1].p_scatter(Vin0) = Vin5;
                (output + obase_6)[Addr_ou1].p_scatter(Vin0) = Vin6;
                (output + obase_7)[Addr_ou1].p_scatter(Vin0) = Vin7;
            }
        }
    }
}

void vcop_psort2_3steps_kernel
(
   int           niter1,
   int           niter2,
   int           niter3,
   int           ibase_0,
   int           ibase_1,
   int           ibase_2,
   int           ibase_3,
   int           ibase_4,
   int           ibase_5,
   int           ibase_6,
   int           ibase_7,
   int           in1ptr_w1,
   int           in1ptr_w2,
   int           in1ptr_w3,
   int           in2ptr_w1,
   int           in2ptr_w2,
   int           in2ptr_w3,
   int           obase_0,
   int           obase_1,
   int           obase_2,
   int           obase_3,
   int           obase_4,
   int           obase_5,
   int           obase_6,
   int           obase_7,
   int           outptr_w1,
   int           outptr_w2,
   int           outptr_w3,
   __vptr_uint32  input,
   __vptr_uint32  output,
   __vptr_int32  out_ofst
)
{
__vector  Vin0;
__vector  Vin1;
__vector  Vin2;
__vector  Vin3;
__vector  Vin4;
__vector  Vin5;
__vector  Vin6;
__vector  Vin7;
__vector  Vin0_c;
__vector  Vin0_d;
__vector  Vindex1;
__vector  Vindex2;

    for (int I1 = 0; I1 < 1;  I1++)
    {
        __agen   Addr_in = I1* 0;

        Vindex1 = out_ofst[Addr_in].npt();
        Vindex2 = Vindex1;
    }

    for (int I1 = 0; I1 < niter1; I1++)
    {
        for (int I2 = 0; I2 < niter2; I2++)
        {
            for (int I3 = 0; I3 < niter3; I3++)
            {
                __agen Addr_in1 = I1 * in1ptr_w1 + I2 * in1ptr_w2 + I3 * in1ptr_w3;
                __agen Addr_in2 = I1 * in2ptr_w1 + I2 * in2ptr_w2 + I3 * in2ptr_w3;
                __agen Addr_ou1 = I1 * outptr_w1 + I2 * outptr_w2 + I3 * outptr_w3;

                Vin0 = (input + ibase_0)[Addr_in1].npt();
                Vin1 = (input + ibase_1)[Addr_in1].npt();
                Vin2 = (input + ibase_2)[Addr_in1].npt();
                Vin3 = (input + ibase_3)[Addr_in1].npt();

                Vin4 = (input + ibase_4)[Addr_in2].npt();
                Vin5 = (input + ibase_5)[Addr_in2].npt();
                Vin6 = (input + ibase_6)[Addr_in2].npt();
                Vin7 = (input + ibase_7)[Addr_in2].npt();

                (Vin0, Vin4).minmax();
                (Vin1, Vin5).minmax();
                (Vin2, Vin6).minmax();
                (Vin3, Vin7).minmax();

                (Vin0, Vin2).minmax();
                (Vin1, Vin3).minmax();
                (Vin4, Vin6).minmax();
                (Vin5, Vin7).minmax();

                (Vin0, Vin1).minmax();
                (Vin2, Vin3).minmax();
                (Vin4, Vin5).minmax();
                (Vin6, Vin7).minmax();

                Vin0_d  =  Vin0;      // Snap shot sorted V0, for store
                Vin0    =  Vindex2;   // Scatter index has to be in V0.

                (output + obase_0)[Addr_ou1].p_scatter(Vin0) = Vin0_d;
                (output + obase_1)[Addr_ou1].p_scatter(Vin0) = Vin1;
                (output + obase_2)[Addr_ou1].p_scatter(Vin0) = Vin2;
                (output + obase_3)[Addr_ou1].p_scatter(Vin0) = Vin3;
                (output + obase_4)[Addr_ou1].p_scatter(Vin0) = Vin4;
                (output + obase_5)[Addr_ou1].p_scatter(Vin0) = Vin5;
                (output + obase_6)[Addr_ou1].p_scatter(Vin0) = Vin6;
                (output + obase_7)[Addr_ou1].p_scatter(Vin0) = Vin7;
            }
        }
    }
}


#define IN_VECTOR_SZ  ((VCOP_SIMD_WIDTH + 1) * sizeof(*output))
#define OU_VECTOR_SZ  (VCOP_SIMD_WIDTH *       sizeof(*input))
#define OU_ELEM_SZ    (sizeof (*output))
#define IN_ELEM_SZ    (sizeof (*input))

void vcop_remove_ex_col
(
    __vptr_uint32   input,
    __vptr_uint32   output,
    int            nitems
)
{
    __vector   Vinp_data;

    for (int I3 = 0; I3 < 8; I3++)
    {
        for (int I4 = 0; I4 < nitems/64; I4++)
        {
            __agen  Addr_i  = I4 * OU_VECTOR_SZ + I3 * ((nitems/8) + 1) * IN_ELEM_SZ;
            __agen  Addr_o  = I4 * OU_VECTOR_SZ + I3 * (nitems/8)       * OU_ELEM_SZ;

            Vinp_data             =  input[Addr_i].npt();
            output[Addr_o].npt()  =  Vinp_data;
        }
    }
}

/*----------------------------------------------------------------------------*/
/* End of file: merge_sort_kernel.k                                           */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/













