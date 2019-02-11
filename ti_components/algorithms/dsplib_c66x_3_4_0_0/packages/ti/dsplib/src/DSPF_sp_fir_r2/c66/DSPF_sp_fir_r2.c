/* ======================================================================= */
/* DSPF_sp_fir_r2_opt.c -- FIR Filter                                      */
/*                 Optimized C Implementation with Intrinsics              */
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

#pragma CODE_SECTION(DSPF_sp_fir_r2, ".text:optimized");

#include "DSPF_sp_fir_r2.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_fir_r2(const float * x, const float * h,
                    float *restrict r, const int nh, const int nr)
{
    int i, j;
    __float2_t x_10, x_21, h_10;
    __float2_t sum1, sum2;

    _nassert((int)x % 8 == 0);
    _nassert((int)h % 8 == 0);
    _nassert((int)r % 8 == 0);
    _nassert(nh >= 4);
    _nassert(nh % 2 == 0);
    _nassert(nr >= 2);
    _nassert(nr % 2 == 0);

    for(j = 0; j < nr; j+=2)
    {
        sum1 = 0;
        sum2 = 0;

        /* note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] } */
        #pragma MUST_ITERATE(2,,)
        for(i = 0; i < nh; i+=2) {
            h_10 = _amem8_f2_const(&h[i]);

            x_10 = _amem8_f2_const(&x[i+j]);
            x_21 = _ftof2(x[i+j+2], _hif2(x_10));

            sum1 = _daddsp(sum1, _dmpysp(x_10, h_10));
            sum2 = _daddsp(sum2, _dmpysp(x_21, h_10));
        }
        _amem8_f2(&r[j]) = _ftof2(_hif2(sum2)+_lof2(sum2), _hif2(sum1)+_lof2(sum1));
    }
}
#else
void DSPF_sp_fir_r2(const float * x, const float * h,
                    float *restrict r, const int nh, const int nr)
{
    int i, j;
    __float2_t x_01, x_12, h_01;
    __float2_t sum1, sum2;

    _nassert((int)x % 8 == 0);
    _nassert((int)h % 8 == 0);
    _nassert((int)r % 8 == 0);
    _nassert(nh >= 4);
    _nassert(nh % 2 == 0);
    _nassert(nr >= 2);
    _nassert(nr % 2 == 0);

    for(j = 0; j < nr; j+=2)
    {
        sum1 = 0;
        sum2 = 0;

        /* note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] } */
        #pragma MUST_ITERATE(2,,)
        for(i = 0; i < nh; i+=2) {
            h_01 = _amem8_f2_const(&h[i]);

            x_01 = _amem8_f2_const(&x[i+j]);
            x_12 = _ftof2(_lof2(x_01), x[i+j+2]);

            sum1 = _daddsp(sum1, _dmpysp(x_01, h_01));
            sum2 = _daddsp(sum2, _dmpysp(x_12, h_01));
        }
        _amem8_f2(&r[j]) = _ftof2(_hif2(sum1)+_lof2(sum1), _hif2(sum2)+_lof2(sum2));
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_fir_r2_opt.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

