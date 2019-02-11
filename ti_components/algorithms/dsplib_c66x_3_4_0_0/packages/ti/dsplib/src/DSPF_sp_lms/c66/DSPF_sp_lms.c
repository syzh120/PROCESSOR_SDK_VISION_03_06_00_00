/* ======================================================================= */
/* DSPF_sp_lms.c -- LMS Adaptive Filter                                    */
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

#pragma CODE_SECTION(DSPF_sp_lms, ".text:optimized");

#include "DSPF_sp_lms.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
float DSPF_sp_lms(const float *x, float *restrict h, const float *y_i,
    float *restrict y_o, const float ar, float error, const int nh, const int nx)
{
    int    i,j;
    float  sum, xm1=0, ae;
    __float2_t x0xm1, x1x0, x2x1, x3x2, h1h0, h3h2, ae_ae, sum10, sum32;
    
    _nassert((int)h % 8 == 0);
    _nassert(nh % 4 == 0);
    _nassert(nh > 0);
    _nassert(nx > 0);
        
    #pragma MUST_ITERATE(1,,)
    for (i = 0; i < nx; i++)
    {
        sum10 = 0;
        sum32 = 0;
        ae    = ar * error;
        ae_ae = _ftof2(ae, ae);
        
        #pragma MUST_ITERATE(1,,)
        for (j = 0; j < nh; j+=4)         
        {
            x1x0  = _mem8_f2((void*)&x[i+j]);
            x3x2  = _mem8_f2((void*)&x[i+j+2]);
            h1h0  = _amem8_f2((void*)&h[j]);
            h3h2  = _amem8_f2((void*)&h[j+2]);
            x0xm1 = _ftof2(_lof2(x1x0), xm1);
            x2x1  = _ftof2(_lof2(x3x2), _hif2(x1x0));
            
            h1h0  = _daddsp(h1h0, _dmpysp(ae_ae, x0xm1));
            h3h2  = _daddsp(h3h2, _dmpysp(ae_ae, x2x1));
            sum10 = _daddsp(sum10, _dmpysp(h1h0, x1x0));
            sum32 = _daddsp(sum32, _dmpysp(h3h2, x3x2));
            
            xm1   = _hif2(x3x2);
            _amem8_f2((void*)&h[j])   = h1h0;
            _amem8_f2((void*)&h[j+2]) = h3h2;
        }                      
        sum10  = _daddsp(sum10, sum32);                 
        sum    = _hif2(sum10)+_lof2(sum10);
        y_o[i] = sum;
        error  = y_i[i] - sum; 
        xm1    = x[i];                             
   }
   return error;
}
#else
float DSPF_sp_lms(const float *x, float *restrict h, const float *y_i,
    float *restrict y_o, const float ar, float error, const int nh, const int nx)
{
    int    i,j;
    float  sum, xm1=0, ae;
    __float2_t xm1x0, x0x1, x1x2, x2x3, h0h1, h2h3, ae_ae, sum01, sum23;
    
    _nassert((int)h % 8 == 0);
    _nassert(nh % 4 == 0);
    _nassert(nh > 0);
    _nassert(nx > 0);
        
    #pragma MUST_ITERATE(1,,)
    for (i = 0; i < nx; i++)
    {
        sum01 = 0;
        sum23 = 0;
        ae    = ar * error;
        ae_ae = _ftof2(ae, ae);
        
        #pragma MUST_ITERATE(1,,)
        for (j = 0; j < nh; j+=4)         
        {
            x0x1  = _mem8_f2((void*)&x[i+j]);
            x2x3  = _mem8_f2((void*)&x[i+j+2]);
            h0h1  = _amem8_f2((void*)&h[j]);
            h2h3  = _amem8_f2((void*)&h[j+2]);
            xm1x0 = _ftof2(xm1, _hif2(x0x1));
            x1x2  = _ftof2(_lof2(x0x1), _hif2(x2x3));
            
            h0h1  = _daddsp(h0h1, _dmpysp(ae_ae, xm1x0));
            h2h3  = _daddsp(h2h3, _dmpysp(ae_ae, x1x2));
            sum01 = _daddsp(sum01, _dmpysp(h0h1, x0x1));
            sum23 = _daddsp(sum23, _dmpysp(h2h3, x2x3));
            
            xm1   = _lof2(x2x3);
            _amem8_f2((void*)&h[j])   = h0h1;
            _amem8_f2((void*)&h[j+2]) = h2h3;
        }                      
        sum01  = _daddsp(sum01, sum23);                 
        sum    = _hif2(sum01)+_lof2(sum01);
        y_o[i] = sum;
        error  = y_i[i] - sum; 
        xm1    = x[i];                             
   }
   return error;
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_lms.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

