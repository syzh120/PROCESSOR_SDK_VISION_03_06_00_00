/* ======================================================================= */
/* DSPF_sp_autocor.c -- Autocorrelation                                    */
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

#pragma CODE_SECTION(DSPF_sp_autocor, ".text:optimized");

#include "DSPF_sp_autocor.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_autocor(float *restrict r, float *restrict x, const int nx, const int nr)
{
    int    i, k;
    __float2_t x_k_10, x_k_32;
    __float2_t x_k_i_01, x_k_i_12, x_k_i_23, x_k_i_34, x_k_i_45, x_k_i_56;
    __float2_t sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;
     
    _nassert(nx % 4 == 0);
    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    _nassert((int)x % 8 == 0);

    #pragma MUST_ITERATE(1, ,1);
    for (i = 0; i < nr; i+=4)
    {
        /* Initialise the accumulators */
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;                                                              
        sum4 = 0;
        sum5 = 0;
        sum6 = 0;
        sum7 = 0;                                                              
        sum8 = 0;
    
        #pragma MUST_ITERATE(1, ,1);
        for (k = nr; k < nx+nr; k += 4) {    
            /* load x[k] and x[k+2] */
            x_k_10   = _amem8_f2((void*)(x+k));
            x_k_32   = _amem8_f2((void*)(x+k+2));
           
            /* load x[k-i+2] and x[k-i+3] */
            x_k_i_01 = _amem8_f2((void*)(x+k-i+2));
           
            /* load x[k-i] and x[k-i+1] */
            x_k_i_23 = _amem8_f2((void*)(x+k-i));

            /* pack x[k-i+1] and x[k-i+2] */
            x_k_i_12 = _ftof2(_lof2(x_k_i_01), _hif2(x_k_i_23));
           
            /* load x[k-i-2] and x[k-i-1] */
            x_k_i_45 = _amem8_f2((void*)(x+k-i-2));

            /* pack x[k-i-1] and x[k-i] */
            x_k_i_34 = _ftof2(_lof2(x_k_i_23), _hif2(x_k_i_45));
           
            /* load x[k-i-3] and x[k-i-2] */
            x_k_i_56 = _mem8_f2((void*)(x+k-i-3));
                      
            sum1 = _daddsp(_dmpysp(x_k_32, x_k_i_01), sum1);
            sum2 = _daddsp(_dmpysp(x_k_32, x_k_i_12), sum2);
            sum3 = _daddsp(_dmpysp(x_k_32, x_k_i_23), sum3);
            sum4 = _daddsp(_dmpysp(x_k_32, x_k_i_34), sum4);
            sum5 = _daddsp(_dmpysp(x_k_10, x_k_i_23), sum5);
            sum6 = _daddsp(_dmpysp(x_k_10, x_k_i_34), sum6);
            sum7 = _daddsp(_dmpysp(x_k_10, x_k_i_45), sum7);
            sum8 = _daddsp(_dmpysp(x_k_10, x_k_i_56), sum8);
        }
        sum1 = _daddsp(sum1, sum5);
        sum2 = _daddsp(sum2, sum6);
        sum3 = _daddsp(sum3, sum7);
        sum4 = _daddsp(sum4, sum8);

        /* Store the result */
        _amem8_f2((void*)&r[i])   = _ftof2(_hif2(sum2)+_lof2(sum2), _hif2(sum1)+_lof2(sum1));
        _amem8_f2((void*)&r[i+2]) = _ftof2(_hif2(sum4)+_lof2(sum4), _hif2(sum3)+_lof2(sum3));
    }
}
#else
void DSPF_sp_autocor(float *restrict r, float *restrict x, const int nx, const int nr)
{
    int    i, k;
    __float2_t x_k_01, x_k_23;
    __float2_t x_k_i_10, x_k_i_21, x_k_i_32, x_k_i_43, x_k_i_54, x_k_i_65;
    __float2_t sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;
     
    _nassert(nx % 4 == 0);
    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    _nassert((int)x % 8 == 0);

    #pragma MUST_ITERATE(1, ,1);
    for (i = 0; i < nr; i+=4)
    {
        /* Initialise the accumulators */
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;                                                              
        sum4 = 0;
        sum5 = 0;
        sum6 = 0;
        sum7 = 0;                                                              
        sum8 = 0;
    
        #pragma MUST_ITERATE(1, ,1);
        for (k = nr; k < nx+nr; k += 4) {    
            /* load x[k] and x[k+2] */
            x_k_01   = _amem8_f2((void*)(x+k));
            x_k_23   = _amem8_f2((void*)(x+k+2));
           
            /* load x[k-i+2] and x[k-i+3] */
            x_k_i_10 = _amem8_f2((void*)(x+k-i+2));
           
            /* load x[k-i] and x[k-i+1] */
            x_k_i_32 = _amem8_f2((void*)(x+k-i));

            /* pack x[k-i+1] and x[k-i+2] */
            x_k_i_21 = _ftof2(_lof2(x_k_i_32), _hif2(x_k_i_10));
           
            /* load x[k-i-2] and x[k-i-1] */
            x_k_i_54 = _amem8_f2((void*)(x+k-i-2));

            /* pack x[k-i-1] and x[k-i] */
            x_k_i_43 = _ftof2(_lof2(x_k_i_54), _hif2(x_k_i_32));
           
            /* load x[k-i-3] and x[k-i-2] */
            x_k_i_65 = _mem8_f2((void*)(x+k-i-3));
                      
            sum1 = _daddsp(_dmpysp(x_k_23, x_k_i_10), sum1);
            sum2 = _daddsp(_dmpysp(x_k_23, x_k_i_21), sum2);
            sum3 = _daddsp(_dmpysp(x_k_23, x_k_i_32), sum3);
            sum4 = _daddsp(_dmpysp(x_k_23, x_k_i_43), sum4);
            sum5 = _daddsp(_dmpysp(x_k_01, x_k_i_32), sum5);
            sum6 = _daddsp(_dmpysp(x_k_01, x_k_i_43), sum6);
            sum7 = _daddsp(_dmpysp(x_k_01, x_k_i_54), sum7);
            sum8 = _daddsp(_dmpysp(x_k_01, x_k_i_65), sum8);
        }
        sum1 = _daddsp(sum1, sum5);
        sum2 = _daddsp(sum2, sum6);
        sum3 = _daddsp(sum3, sum7);
        sum4 = _daddsp(sum4, sum8);

        /* Store the result */
        _amem8_f2((void*)&r[i])   = _ftof2(_hif2(sum1)+_lof2(sum1), _hif2(sum2)+_lof2(sum2));
        _amem8_f2((void*)&r[i+2]) = _ftof2(_hif2(sum3)+_lof2(sum3), _hif2(sum4)+_lof2(sum4));
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_autocor.c                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

