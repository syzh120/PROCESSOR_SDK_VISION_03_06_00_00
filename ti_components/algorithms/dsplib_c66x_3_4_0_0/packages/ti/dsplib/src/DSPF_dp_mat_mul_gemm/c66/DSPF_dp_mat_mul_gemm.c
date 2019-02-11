/* ======================================================================= */
/* DSPF_dp_mat_mul_gemm.c -- Matrix Multiply “y = a*x1*x2+y"               */
/*              Optimized C Implementation (w/ Intrinsics)                 */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#pragma CODE_SECTION(DSPF_dp_mat_mul_gemm, ".text:optimized");

#include "DSPF_dp_mat_mul_gemm.h"

void DSPF_dp_mat_mul_gemm(double *x1, double const a, const int r1, const int c1,
    double *x2, const int c2, double *restrict y)
{
    int    i, j, k, xoff1, xoff2;
    double sum0, sum1, sum2, sum3;
    double x00, x01, y00, y01, y10, y11, x10, x11;
    double *ptr_x, *ptr_y, *restrict y1, *restrict y2;

    _nassert(r1 > 0);
    _nassert(c1 > 0);
    _nassert(c2 > 0);
    _nassert((int)x1 % 8 == 0);
    _nassert((int)x2 % 8 == 0);
    _nassert((int)y  % 8 == 0);
    _nassert(c1 % 2 == 0 );
    _nassert(r1 % 2 == 0 );
    _nassert(c2 % 2 == 0 );

    #pragma MUST_ITERATE(1,,)
    for (j = 0; j < c2; j+=2) {
      xoff2 = j * c1;
      y1 = &y[(j + 0) * r1];
      y2 = &y[(j + 1) * r1];

      #pragma MUST_ITERATE(1,,)
      for (i = 0; i < r1; i+=2) {                         
        xoff1 = i * c1;                            
        sum0  = 0;
        sum1  = 0;
        sum2  = 0;
        sum3  = 0;
        ptr_x = &x1[xoff1];
        ptr_y = &x2[xoff2];

        #pragma MUST_ITERATE(1,,)
        for (k = 0; k < c1; k+=2,ptr_x+=2,ptr_y+=2) {
          x00 = ptr_x[0];
          x01 = ptr_x[1];
          x10 = ptr_x[c1];
          x11 = ptr_x[c1 + 1];
          y00 = ptr_y[0];
          y01 = ptr_y[c1];
          y10 = ptr_y[1];
          y11 = ptr_y[c1 + 1];

          sum0 += x00 * y00 + x01 * y10;
          sum1 += x00 * y01 + x01 * y11;
          sum2 += x10 * y00 + x11 * y10;
          sum3 += x10 * y01 + x11 * y11;
        }
        y1[(i + 0)] += a*sum0;
        y2[(i + 0)] += a*sum1;
        y1[(i + 1)] += a*sum2;
        y2[(i + 1)] += a*sum3;        
      }
    }                        
}

/* ======================================================================= */
/*  End of file:  DSPF_dp_mat_mul_gemm.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */



