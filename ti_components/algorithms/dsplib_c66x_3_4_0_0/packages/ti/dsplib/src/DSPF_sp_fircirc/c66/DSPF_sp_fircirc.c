/* ======================================================================= */
/* DSPF_sp_fircirc.c -- Circular FIR Filter                                */
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

#pragma CODE_SECTION(DSPF_sp_fircirc, ".text:optimized");

#include "DSPF_sp_fircirc.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_fircirc(const float *x, float *h, float *restrict y, 
                     int index, int csize, int nh, int ny)
{
    int    i, j;
    /* Circular Buffer block size = ((2^(csize + 1)) / 4) floating point numbers */
    int    mod = (1 << (csize - 1)) - 1; 
    float  *x_ptr = (float*)&x[index];
    __float2_t x_10, x_21, x_32, x_43, x_54, h_10;
    __float2_t sum1, sum2, sum3, sum4;

    _nassert(nh >= 2);
    _nassert(nh % 2 == 0);
    _nassert(ny >= 4);
    _nassert(ny % 4 == 0);
    _nassert((int) x % 8 == 0);
    _nassert((int) y % 8 == 0);
    _nassert((int) h % 8 == 0);

    #pragma MUST_ITERATE(1,,)
    for(j = 0; j < ny; j+=4)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;

        x_10 = _amem8_f2_const(&x_ptr[(i) & (mod)]);
        x_32 = _amem8_f2_const(&x_ptr[(i+2) & (mod)]);
        x_21 = _ftof2(_lof2(x_32), _hif2(x_10));

        /* note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] } */
        #pragma MUST_ITERATE(1,,)
        for(i = 0; i < nh; i+=2) {
            h_10 = _amem8_f2_const(&h[i]);
            x_54 = _amem8_f2_const(&x_ptr[(i+4) & (mod)]);
            x_43 = _ftof2(_lof2(x_54), _hif2(x_32));

            sum1 = _daddsp(sum1, _dmpysp(x_10, h_10));
            sum2 = _daddsp(sum2, _dmpysp(x_21, h_10));
            sum3 = _daddsp(sum3, _dmpysp(x_32, h_10));
            sum4 = _daddsp(sum4, _dmpysp(x_43, h_10));

            x_10 = x_32;
            x_21 = x_43;
            x_32 = x_54;
        }
        _amem8_f2(&y[j])   = _ftof2(_hif2(sum2)+_lof2(sum2), _hif2(sum1)+_lof2(sum1));
        _amem8_f2(&y[j+2]) = _ftof2(_hif2(sum4)+_lof2(sum4), _hif2(sum3)+_lof2(sum3));
    }
}
#else
void DSPF_sp_fircirc(const float *x, float *h, float *restrict y, 
                     int index, int csize, int nh, int ny)
{
    int    i, j;
    /* Circular Buffer block size = ((2^(csize + 1)) / 4) floating point numbers */
    int    mod = (1 << (csize - 1)) - 1; 
    float  *x_ptr = (float*)&x[index];
    __float2_t x_01, x_12, x_23, x_34, x_45, h_01;
    __float2_t sum1, sum2, sum3, sum4;

    _nassert(nh >= 2);
    _nassert(nh % 2 == 0);
    _nassert(ny >= 4);
    _nassert(ny % 4 == 0);
    _nassert((int) x % 8 == 0);
    _nassert((int) y % 8 == 0);
    _nassert((int) h % 8 == 0);

    #pragma MUST_ITERATE(1,,)
    for(j = 0; j < ny; j+=4)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;

        x_01 = _amem8_f2_const(&x_ptr[(i) & (mod)]);
        x_23 = _amem8_f2_const(&x_ptr[(i+2) & (mod)]);
        x_12 = _ftof2(_lof2(x_01), _hif2(x_23));

        /* note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] } */
        #pragma MUST_ITERATE(1,,)
        for(i = 0; i < nh; i+=2) {
            h_01 = _amem8_f2_const(&h[i]);
            x_45 = _amem8_f2_const(&x_ptr[(i+4) & (mod)]);
            x_34 = _ftof2(_lof2(x_23), _hif2(x_45));

            sum1 = _daddsp(sum1, _dmpysp(x_01, h_01));
            sum2 = _daddsp(sum2, _dmpysp(x_12, h_01));
            sum3 = _daddsp(sum3, _dmpysp(x_23, h_01));
            sum4 = _daddsp(sum4, _dmpysp(x_34, h_01));

            x_01 = x_23;
            x_12 = x_34;
            x_23 = x_45;
        }
        _amem8_f2(&y[j])   = _ftof2(_hif2(sum1)+_lof2(sum1), _hif2(sum2)+_lof2(sum2));
        _amem8_f2(&y[j+2]) = _ftof2(_hif2(sum3)+_lof2(sum3), _hif2(sum4)+_lof2(sum4));
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_fircirc.c                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

