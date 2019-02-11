/* ======================================================================= */
/* DSPF_sp_convol.c -- Convolution                                         */
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

#pragma CODE_SECTION(DSPF_sp_convol, ".text:optimized");

#include "DSPF_sp_convol.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_convol(const float *x, const float *h,
    float *restrict y, const short nh, const short ny)
{
    int    i, j;
    float *x_ptr, *h_ptr;
    __float2_t sum1, sum2, sum3, sum4;
    __float2_t h_10, h_01, h_32, h_23, x_10, x_21, x_32, x_43;

    _nassert(nh % 4 == 0);
    _nassert(nh > 4);
    _nassert(ny % 2 == 0);
    _nassert(ny > 2);
    _nassert((int)x % 8 == 0);
    _nassert((int)h % 8 == 0);
    _nassert((int)y % 8 == 0);

    h_ptr = (float*)h + nh - 2;
    #pragma MUST_ITERATE(1,,)
    for (i = 0 ; i < ny ; i += 2)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        x_ptr = (float*)&x[i];

        #pragma MUST_ITERATE(1,,)
        for (j = 0 ; j < nh ; j += 4)
        {  
            h_10 = _amem8_f2((void*)(h_ptr - j));
            h_32 = _amem8_f2((void*)(h_ptr - j - 2));
            x_10 = _amem8_f2((void*)(x_ptr + j));
            x_32 = _amem8_f2((void*)(x_ptr + j + 2));
            x_43 =  _mem8_f2((void*)(x_ptr + j + 3));

            h_01 = _ftof2(_lof2(h_10), _hif2(h_10));
            h_23 = _ftof2(_lof2(h_32), _hif2(h_32));
            x_21 = _ftof2(_lof2(x_32), _hif2(x_10));

            sum1 = _daddsp(sum1, _dmpysp(h_01, x_10));
            sum2 = _daddsp(sum2, _dmpysp(h_01, x_21));
            sum3 = _daddsp(sum3, _dmpysp(h_23, x_32));
            sum4 = _daddsp(sum4, _dmpysp(h_23, x_43));
        }
        sum1 = _daddsp(sum1, sum3);
        sum2 = _daddsp(sum2, sum4);
        _amem8_f2((void*)&y[i]) = _ftof2(_hif2(sum2)+_lof2(sum2), _hif2(sum1)+_lof2(sum1));
    }
}
#else
void DSPF_sp_convol(const float *x, const float *h,
    float *restrict y, const short nh, const short ny)
{
    int    i, j;
    float *x_ptr, *h_ptr;
    __float2_t sum1, sum2, sum3, sum4;
    __float2_t h_10, h_01, h_32, h_23, x_01, x_12, x_23, x_34;

    _nassert(nh % 4 == 0);
    _nassert(nh > 4);
    _nassert(ny % 2 == 0);
    _nassert(ny > 2);
    _nassert((int)x % 8 == 0);
    _nassert((int)h % 8 == 0);
    _nassert((int)y % 8 == 0);

    h_ptr = (float*)h + nh - 2;
    #pragma MUST_ITERATE(1,,)
    for (i = 0 ; i < ny ; i += 2)
    {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        x_ptr = (float*)&x[i];

        #pragma MUST_ITERATE(1,,)
        for (j = 0 ; j < nh ; j += 4)
        {  
            h_01 = _amem8_f2((void*)(h_ptr - j));
            h_23 = _amem8_f2((void*)(h_ptr - j - 2));
            x_01 = _amem8_f2((void*)(x_ptr + j));
            x_23 = _amem8_f2((void*)(x_ptr + j + 2));
            x_34 =  _mem8_f2((void*)(x_ptr + j + 3));

            h_10 = _ftof2(_lof2(h_01), _hif2(h_01));
            h_32 = _ftof2(_lof2(h_23), _hif2(h_23));
            x_12 = _ftof2(_lof2(x_01), _hif2(x_23));

            sum1 = _daddsp(sum1, _dmpysp(h_10, x_01));
            sum2 = _daddsp(sum2, _dmpysp(h_10, x_12));
            sum3 = _daddsp(sum3, _dmpysp(h_32, x_23));
            sum4 = _daddsp(sum4, _dmpysp(h_32, x_34));
        }
        sum1 = _daddsp(sum1, sum3);
        sum2 = _daddsp(sum2, sum4);
        _amem8_f2((void*)&y[i]) = _ftof2(_hif2(sum1)+_lof2(sum1), _hif2(sum2)+_lof2(sum2));
    }
}
#endif

/* ======================================================================= */
/*  End of file:  DSPF_sp_convol.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

