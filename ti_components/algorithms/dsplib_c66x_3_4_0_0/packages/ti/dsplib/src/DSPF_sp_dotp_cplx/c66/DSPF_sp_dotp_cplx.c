/* ======================================================================= */
/* DSPF_sp_dotp_cplx.c -- Complex Dot Product                              */
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

#pragma CODE_SECTION(DSPF_sp_dotp_cplx, ".text:optimized");

#include "DSPF_sp_dotp_cplx.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_dotp_cplx(const float * x, const float * y, int nx,
                       float * restrict re, float * restrict im)
{
    int i;
    __float2_t x0_im_re, y0_im_re, result0 = 0;
    __float2_t x1_im_re, y1_im_re, result1 = 0;
    __float2_t x2_im_re, y2_im_re, result2 = 0;
    __float2_t x3_im_re, y3_im_re, result3 = 0;
    __float2_t result;

    _nassert(nx % 4 == 0);
    _nassert(nx > 0);
    _nassert((int)x % 8 == 0);
    _nassert((int)y % 8 == 0);
    
    for(i = 0; i < 2 * nx; i += 8)
    {        
        /* load 4 sets of input data */
        x0_im_re = _amem8_f2((void*)&x[i]);
        y0_im_re = _amem8_f2((void*)&y[i]);

        x1_im_re = _amem8_f2((void*)&x[i+2]);
        y1_im_re = _amem8_f2((void*)&y[i+2]);

        x2_im_re = _amem8_f2((void*)&x[i+4]);
        y2_im_re = _amem8_f2((void*)&y[i+4]);

        x3_im_re = _amem8_f2((void*)&x[i+6]);
        y3_im_re = _amem8_f2((void*)&y[i+6]);

        /* calculate 4 running sums */
        result0 = _daddsp(_complex_mpysp(x0_im_re, y0_im_re), result0);
        result1 = _daddsp(_complex_mpysp(x1_im_re, y1_im_re), result1);
        result2 = _daddsp(_complex_mpysp(x2_im_re, y2_im_re), result2);
        result3 = _daddsp(_complex_mpysp(x3_im_re, y3_im_re), result3);
    }

    result = _daddsp(_daddsp(result0,result1),_daddsp(result2,result3));
    *re = -_hif2(result);
    *im =  _lof2(result);
}
#else
void DSPF_sp_dotp_cplx(const float * x, const float * y, int nx,
                       float * restrict re, float * restrict im)
{
    int i;
    __float2_t x0_re_im, y0_re_im, result0 = 0;
    __float2_t x1_re_im, y1_re_im, result1 = 0;
    __float2_t x2_re_im, y2_re_im, result2 = 0;
    __float2_t x3_re_im, y3_re_im, result3 = 0;
    __float2_t result;

    _nassert(nx % 4 == 0);
    _nassert(nx > 0);
    _nassert((int)x % 8 == 0);
    _nassert((int)y % 8 == 0);
    
    for(i = 0; i < 2 * nx; i += 8)
    {        
        /* load 4 sets of input data */
        x0_re_im = _amem8_f2((void*)&x[i]);
        y0_re_im = _amem8_f2((void*)&y[i]);

        x1_re_im = _amem8_f2((void*)&x[i+2]);
        y1_re_im = _amem8_f2((void*)&y[i+2]);

        x2_re_im = _amem8_f2((void*)&x[i+4]);
        y2_re_im = _amem8_f2((void*)&y[i+4]);

        x3_re_im = _amem8_f2((void*)&x[i+6]);
        y3_re_im = _amem8_f2((void*)&y[i+6]);

        /* calculate 4 running sums */
        result0 = _daddsp(_complex_mpysp(x0_re_im, y0_re_im), result0);
        result1 = _daddsp(_complex_mpysp(x1_re_im, y1_re_im), result1);
        result2 = _daddsp(_complex_mpysp(x2_re_im, y2_re_im), result2);
        result3 = _daddsp(_complex_mpysp(x3_re_im, y3_re_im), result3);
    }

    result = _daddsp(_daddsp(result0,result1),_daddsp(result2,result3));
    *re = _hif2(result);
    *im = _lof2(result);
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_dotp_cplx.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

