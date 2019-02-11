/* ======================================================================= */
/* DSPF_sp_iirlat_opt.c -- Lattice IIR Filter                              */
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

#pragma CODE_SECTION(DSPF_sp_iirlat, ".text:optimized");

#include "DSPF_sp_iirlat.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_iirlat(const float *x, int nx, const float *restrict k, 
                    int nk, float *restrict b, float *restrict y)
{
    int    i, j;
    float  yt, yt1, yt2, yt3, temp;
    __float2_t bibim1, bim2bim3, kikim1, kim2kim3;
    __float2_t temp_1_2, temp_3_4, temp_sum;
    
    _nassert(nx > 0);
    _nassert(nk >= 4);
    _nassert(nk % 4 == 0);
    _nassert((int)k % 8 == 0);
    _nassert((int)b % 8 == 0);
           
    #pragma MUST_ITERATE(1,,)
    for (j = 0; j < nx; j++)
    {
        /* starting value of yt */
        yt = x[j];

        #pragma MUST_ITERATE(1,,)
        for (i = nk - 1; i >= 3; i-=4)
        {
            /* load b[i-1] and b[i] */
            bibim1   = _amem8_f2((void*)(b + i - 1));
            
            /* load b[i-2] and b[i-3] */
            bim2bim3 = _amem8_f2((void*)(b + i - 3));
            
            /* load k[i], k[i-1] */
            kikim1   = _amem8_f2((void*)(k + i - 1));
            
            /* load k[i-2], k[i-3] */
            kim2kim3 = _amem8_f2((void*)(k + i - 3));
            
            temp_1_2 = _dmpysp(bibim1, kikim1);
            temp_3_4 = _dmpysp(bim2bim3, kim2kim3);
            temp_sum = _daddsp(temp_1_2, temp_3_4);
            temp     = _hif2(temp_sum) + _lof2(temp_sum);
                                          
            /* update delays and find output for this input */
            yt1 = yt  - _hif2(temp_1_2);
            yt2 = yt1 - _lof2(temp_1_2);
            _mem8_f2((void*)&b[i]) = _daddsp(bibim1, _dmpysp(_ftof2(yt1, yt2), kikim1));

            /* yt = yt - (b[i]*k[i] + b[i-1]*k[i-1] + b[i-2]*k[i-2] + b[i-3]*k[i-3]) */
            yt3 = yt2 - _hif2(temp_3_4);
            yt  = yt  - temp;
            _mem8_f2((void*)&b[i-2]) = _daddsp(bim2bim3, _dmpysp(_ftof2(yt3, yt), kim2kim3));
        }
        
        /* update first delay */
        b[0] = yt;
        /* store output */
        y[j] = yt;       
    }
}       
#else
void DSPF_sp_iirlat(const float *x, int nx, const float *restrict k, 
                    int nk, float *restrict b, float *restrict y)
{
    int    i, j;
    float  yt, yt1, yt2, yt3, temp;
    __float2_t bim1bi, bim3bim2, kim1ki, kim3kim2;
    __float2_t temp_1_2, temp_3_4, temp_sum;
    
    _nassert(nx > 0);
    _nassert(nk >= 4);
    _nassert(nk % 4 == 0);
    _nassert((int)k % 8 == 0);
    _nassert((int)b % 8 == 0);
           
    #pragma MUST_ITERATE(1,,)
    for (j = 0; j < nx; j++)
    {
        /* starting value of yt */
        yt = x[j];

        #pragma MUST_ITERATE(1,,)
        for (i = nk - 1; i >= 3; i-=4)
        {
            /* load b[i-1] and b[i] */
            bim1bi   = _amem8_f2((void*)(b + i - 1));
            
            /* load b[i-2] and b[i-3] */
            bim3bim2 = _amem8_f2((void*)(b + i - 3));
            
            /* load k[i], k[i-1] */
            kim1ki   = _amem8_f2((void*)(k + i - 1));
            
            /* load k[i-2], k[i-3] */
            kim3kim2 = _amem8_f2((void*)(k + i - 3));
            
            temp_1_2 = _dmpysp(bim1bi, kim1ki);
            temp_3_4 = _dmpysp(bim3bim2, kim3kim2);
            temp_sum = _daddsp(temp_1_2, temp_3_4);
            temp     = _hif2(temp_sum) + _lof2(temp_sum);
                                          
            /* update delays and find output for this input */
            yt1 = yt  - _lof2(temp_1_2);
            yt2 = yt1 - _hif2(temp_1_2);
            _mem8_f2((void*)&b[i]) = _daddsp(bim1bi, _dmpysp(_ftof2(yt2, yt1), kim1ki));
            
            /* yt = yt - (b[i]*k[i] + b[i-1]*k[i-1] + b[i-2]*k[i-2] + b[i-3]*k[i-3]) */
            yt3 = yt2 - _lof2(temp_3_4);
            yt  = yt  - temp;
            _mem8_f2((void*)&b[i-2]) = _daddsp(bim3bim2, _dmpysp(_ftof2(yt, yt3), kim3kim2));
        }
        
        /* update first delay */
        b[0] = yt;
        /* store output */
        y[j] = yt;       
    }
}       
#endif                                                       
/* ======================================================================= */
/*  End of file:  DSPF_sp_iirlat.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

