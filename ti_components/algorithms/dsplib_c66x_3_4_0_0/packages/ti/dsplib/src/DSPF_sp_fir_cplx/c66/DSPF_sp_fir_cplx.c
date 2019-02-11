/* ======================================================================= */
/* DSPF_sp_fir_cplx.c -- Complex FIR Filter                                */
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

#pragma CODE_SECTION(DSPF_sp_fir_cplx, ".text:optimized");

#include "DSPF_sp_fir_cplx.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_fir_cplx(const float * x, const float * h,
                      float * restrict r, int nh, int nr)
{
    int    i, j;
    __float2_t h1_re_im, h2_re_im, x1_re_im, x2_re_im, x3_re_im, x4_re_im, x5_re_im;
    __float2_t sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;

    _nassert((int) nr % 4 == 0);
    _nassert((int) nr >= 4);
    _nassert((int) nh % 2 == 0);
    _nassert((int) nh >= 2);
    _nassert((int) x % 8 == 0);
    _nassert((int) r % 8 == 0);
    _nassert((int) h % 8 == 0);

    for (i = 0; i < 2*nr; i += 8) {
        /* calculate 4 output in parallel */
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        sum5 = 0;
        sum6 = 0;
        sum7 = 0;
        sum8 = 0;
        for (j = 0; j < 2*nh; j += 4) {
            
            h1_re_im = _amem8_f2_const(&h[j]);
            h2_re_im = _amem8_f2_const(&h[j+2]);

            x1_re_im = _amem8_f2_const(&x[i-j]);
            x2_re_im = _amem8_f2_const(&x[i-j+2]);
            x3_re_im = _amem8_f2_const(&x[i-j+4]);
            x4_re_im = _amem8_f2_const(&x[i-j+6]);
            x5_re_im = _amem8_f2_const(&x[i-j-2]);

            sum1     = _daddsp(sum1, _complex_mpysp(h1_re_im, x1_re_im));
            sum2     = _daddsp(sum2, _complex_mpysp(h1_re_im, x2_re_im));
            sum3     = _daddsp(sum3, _complex_mpysp(h1_re_im, x3_re_im));
            sum4     = _daddsp(sum4, _complex_mpysp(h1_re_im, x4_re_im));
            sum5     = _daddsp(sum5, _complex_mpysp(h2_re_im, x5_re_im));
            sum6     = _daddsp(sum6, _complex_mpysp(h2_re_im, x1_re_im));
            sum7     = _daddsp(sum7, _complex_mpysp(h2_re_im, x2_re_im));
            sum8     = _daddsp(sum8, _complex_mpysp(h2_re_im, x3_re_im));
        }
        sum1 = _daddsp(sum1, sum5);
        sum2 = _daddsp(sum2, sum6);
        sum3 = _daddsp(sum3, sum7);
        sum4 = _daddsp(sum4, sum8);

        _amem8_f2(&r[i])   = _ftof2(_lof2(sum1), -_hif2(sum1));
        _amem8_f2(&r[i+2]) = _ftof2(_lof2(sum2), -_hif2(sum2));
        _amem8_f2(&r[i+4]) = _ftof2(_lof2(sum3), -_hif2(sum3));
        _amem8_f2(&r[i+6]) = _ftof2(_lof2(sum4), -_hif2(sum4));
    }
}
#else
void DSPF_sp_fir_cplx(const float * x, const float * h,
                      float * restrict r, int nh, int nr)
{
    int    i, j;
    __float2_t h1_im_re, h2_im_re, x1_im_re, x2_im_re, x3_im_re, x4_im_re, x5_im_re;
    __float2_t sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;

    _nassert((int) nr % 4 == 0);
    _nassert((int) nr >= 4);
    _nassert((int) nh % 2 == 0);
    _nassert((int) nh >= 2);
    _nassert((int) x % 8 == 0);
    _nassert((int) r % 8 == 0);
    _nassert((int) h % 8 == 0);

    for (i = 0; i < 2*nr; i += 8) {
        /* calculate 4 output in parallel */
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        sum5 = 0;
        sum6 = 0;
        sum7 = 0;
        sum8 = 0;
        for (j = 0; j < 2*nh; j += 4) {
            
            h1_im_re = _amem8_f2_const(&h[j]);
            h2_im_re = _amem8_f2_const(&h[j+2]);

            x1_im_re = _amem8_f2_const(&x[i-j]);
            x2_im_re = _amem8_f2_const(&x[i-j+2]);
            x3_im_re = _amem8_f2_const(&x[i-j+4]);
            x4_im_re = _amem8_f2_const(&x[i-j+6]);
            x5_im_re = _amem8_f2_const(&x[i-j-2]);

            sum1     = _daddsp(sum1, _complex_mpysp(h1_im_re, x1_im_re));
            sum2     = _daddsp(sum2, _complex_mpysp(h1_im_re, x2_im_re));
            sum3     = _daddsp(sum3, _complex_mpysp(h1_im_re, x3_im_re));
            sum4     = _daddsp(sum4, _complex_mpysp(h1_im_re, x4_im_re));
            sum5     = _daddsp(sum5, _complex_mpysp(h2_im_re, x5_im_re));
            sum6     = _daddsp(sum6, _complex_mpysp(h2_im_re, x1_im_re));
            sum7     = _daddsp(sum7, _complex_mpysp(h2_im_re, x2_im_re));
            sum8     = _daddsp(sum8, _complex_mpysp(h2_im_re, x3_im_re));
        }
        sum1 = _daddsp(sum1, sum5);
        sum2 = _daddsp(sum2, sum6);
        sum3 = _daddsp(sum3, sum7);
        sum4 = _daddsp(sum4, sum8);

        _amem8_f2(&r[i])   = sum1;
        _amem8_f2(&r[i+2]) = sum2;
        _amem8_f2(&r[i+4]) = sum3;
        _amem8_f2(&r[i+6]) = sum4;
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_fir_cplx.c                                       */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
