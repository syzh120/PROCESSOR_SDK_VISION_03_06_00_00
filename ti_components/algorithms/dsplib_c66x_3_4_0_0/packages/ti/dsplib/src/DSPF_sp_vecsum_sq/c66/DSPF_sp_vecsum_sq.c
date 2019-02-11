/* ======================================================================= */
/* DSPF_sp_vecsum_sq.c -- Vector Sum of Squares                            */
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

#pragma CODE_SECTION(DSPF_sp_vecsum_sq, ".text:optimized");

#include "DSPF_sp_vecsum_sq.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

float DSPF_sp_vecsum_sq(const float *restrict x, const int nx)
{
    int    i, n = nx/16*16;
    float  sum;
    __float2_t x_01, x_23, x_45, x_67;
    __float2_t x_89, x_ab, x_cd, x_ef;
  
    __float2_t sum1 = 0, sum2 = 0;
    __float2_t sum3 = 0, sum4 = 0;
    __float2_t sum5 = 0, sum6 = 0;
    __float2_t sum7 = 0, sum8 = 0;

    _nassert((int)x % 8 == 0);
    
    /* this loop processes 16 samples in paralell */
    for(i = 0; i < n; i += 16)
    {
      x_01 = _amem8_f2((void*)(x+i));
      x_23 = _amem8_f2((void*)(x+i+2));
      x_45 = _amem8_f2((void*)(x+i+4));
      x_67 = _amem8_f2((void*)(x+i+6));
      x_89 = _amem8_f2((void*)(x+i+8));
      x_ab = _amem8_f2((void*)(x+i+10));
      x_cd = _amem8_f2((void*)(x+i+12));
      x_ef = _amem8_f2((void*)(x+i+14));
    
      sum1 = _daddsp(_dmpysp(x_01, x_01), sum1);
      sum2 = _daddsp(_dmpysp(x_23, x_23), sum2);
      sum3 = _daddsp(_dmpysp(x_45, x_45), sum3);
      sum4 = _daddsp(_dmpysp(x_67, x_67), sum4);
      sum5 = _daddsp(_dmpysp(x_89, x_89), sum5);
      sum6 = _daddsp(_dmpysp(x_ab, x_ab), sum6);
      sum7 = _daddsp(_dmpysp(x_cd, x_cd), sum7);
      sum8 = _daddsp(_dmpysp(x_ef, x_ef), sum8);
    }
    
    sum1 = _daddsp(sum1, sum2);
    sum3 = _daddsp(sum3, sum4);
    sum5 = _daddsp(sum5, sum6);
    sum7 = _daddsp(sum7, sum8);
    sum1 = _daddsp(sum1, sum3);
    sum5 = _daddsp(sum5, sum7);
    sum1 = _daddsp(sum1, sum5);

    /* this loop processes the left-over */
    sum  = _hif2(sum1) + _lof2(sum1);
    for(i = n; i < nx; i++ )
        sum += x[i] * x[i];

    return sum;     
}


/* ======================================================================= */
/*  End of file:  DSPF_sp_vecsum_sq.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

