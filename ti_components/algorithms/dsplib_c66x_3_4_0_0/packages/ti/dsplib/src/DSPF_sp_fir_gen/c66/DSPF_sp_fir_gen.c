/* ======================================================================= */
/* DSPF_sp_fir_gen.c -- FIR Filter                                         */
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

#pragma CODE_SECTION(DSPF_sp_fir_gen, ".text:optimized");

#include "DSPF_sp_fir_gen.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_fir_gen(const float * restrict x,
    const float * restrict h,
    float * restrict r,
    int nh,
    int nr)
{
    int i, j;
    __float2_t x_10, x_32, x_43, x_54, x_65, h_10, h_32;
    __float2_t sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;

    _nassert(nh >= 4);
    _nassert(nh % 4 == 0);
    _nassert(nr >= 4);
    _nassert(nr % 4 == 0);
    _nassert((int) x % 8 == 0);
    _nassert((int) r % 8 == 0);
    _nassert((int) h % 8 == 0);

    for(j = 0; j < nr; j+=4)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        sum5 = 0;
        sum6 = 0;
        sum7 = 0;
        sum8 = 0;

        /* note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] } */
        for(i = 0; i < nh; i+=4) {
            h_10 = _amem8_f2_const(&h[i]);
            h_32 = _amem8_f2_const(&h[i+2]);

            x_10 = _amem8_f2_const(&x[i+j]);
            x_32 = _amem8_f2_const(&x[i+j+2]);
            x_54 = _amem8_f2_const(&x[i+j+4]);
            x_65 = _mem8_f2_const(&x[i+j+5]);
            x_43 = _ftof2(_lof2(x_54), _hif2(x_32));

            sum1 = _daddsp(sum1, _dmpysp(x_10, h_10));
            sum2 = _daddsp(sum2, _dmpysp(_ftof2(_lof2(x_32), _hif2(x_10)), h_10));
            sum3 = _daddsp(sum3, _dmpysp(x_32, h_10));
            sum4 = _daddsp(sum4, _dmpysp(x_43, h_10));
            sum5 = _daddsp(sum5, _dmpysp(x_32, h_32));
            sum6 = _daddsp(sum6, _dmpysp(x_43, h_32));
            sum7 = _daddsp(sum7, _dmpysp(x_54, h_32));
            sum8 = _daddsp(sum8, _dmpysp(x_65, h_32));

        }
        sum1 = _daddsp(sum1, sum5);
        sum2 = _daddsp(sum2, sum6);
        sum3 = _daddsp(sum3, sum7);
        sum4 = _daddsp(sum4, sum8);

        _amem8_f2(&r[j])   = _ftof2(_hif2(sum2)+_lof2(sum2), _hif2(sum1)+_lof2(sum1));
        _amem8_f2(&r[j+2]) = _ftof2(_hif2(sum4)+_lof2(sum4), _hif2(sum3)+_lof2(sum3));
    }
}
#else
void DSPF_sp_fir_gen(const float * restrict x,
    const float * restrict h,
    float * restrict r,
    int nh,
    int nr)
{
    int i, j;
    __float2_t x_01, x_23, x_34, x_45, x_56, h_01, h_23;
    __float2_t sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;

    _nassert(nh >= 4);
    _nassert(nh % 4 == 0);
    _nassert(nr >= 4);
    _nassert(nr % 4 == 0);
    _nassert((int) x % 8 == 0);
    _nassert((int) r % 8 == 0);
    _nassert((int) h % 8 == 0);

    for(j = 0; j < nr; j+=4)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        sum5 = 0;
        sum6 = 0;
        sum7 = 0;
        sum8 = 0;

        /* note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] } */
        for(i = 0; i < nh; i+=4) {
            h_01 = _amem8_f2_const(&h[i]);
            h_23 = _amem8_f2_const(&h[i+2]);

            x_01 = _amem8_f2_const(&x[i+j]);
            x_23 = _amem8_f2_const(&x[i+j+2]);
            x_45 = _amem8_f2_const(&x[i+j+4]);
            x_56 = _mem8_f2_const(&x[i+j+5]);
            x_34 = _ftof2(_lof2(x_23), _hif2(x_45));

            sum1 = _daddsp(sum1, _dmpysp(x_01, h_01));
            sum2 = _daddsp(sum2, _dmpysp(_ftof2(_lof2(x_01), _hif2(x_23)), h_01));
            sum3 = _daddsp(sum3, _dmpysp(x_23, h_01));
            sum4 = _daddsp(sum4, _dmpysp(x_34, h_01));
            sum5 = _daddsp(sum5, _dmpysp(x_23, h_23));
            sum6 = _daddsp(sum6, _dmpysp(x_34, h_23));
            sum7 = _daddsp(sum7, _dmpysp(x_45, h_23));
            sum8 = _daddsp(sum8, _dmpysp(x_56, h_23));
        }
        sum1 = _daddsp(sum1, sum5);
        sum2 = _daddsp(sum2, sum6);
        sum3 = _daddsp(sum3, sum7);
        sum4 = _daddsp(sum4, sum8);

        _amem8_f2(&r[j])   = _ftof2(_hif2(sum1)+_lof2(sum1), _hif2(sum2)+_lof2(sum2));
        _amem8_f2(&r[j+2]) = _ftof2(_hif2(sum3)+_lof2(sum3), _hif2(sum4)+_lof2(sum4));
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_fir_gen.c                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


