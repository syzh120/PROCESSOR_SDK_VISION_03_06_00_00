/* ======================================================================= */
/* DSPF_sp_vecrecip.c -- Vector Reciprocal                                 */
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

#pragma CODE_SECTION(DSPF_sp_vecrecip, ".text:optimized");

#include "DSPF_sp_vecrecip.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

void DSPF_sp_vecrecip(const float * x, float *restrict y, const int nx)
{
    int i;
    __float2_t x1x0_temp, x1x0, y1y0, z1z0, r1r0;

    _nassert((int)x % 8 == 0);
    _nassert((int)y % 8 == 0);
    _nassert(nx % 4 == 0);
    _nassert(nx > 0);
    
    #pragma MUST_ITERATE(2,,2)
    #pragma UNROLL(2)
    for(i = 0; i < nx; i += 2)
    {                
        x1x0 = _amem8_f2((void *)&x[i]);
        
        /* seed for Newton-Raphson method */
        y1y0 = _ftof2(_rcpsp(_hif2(x1x0)), _rcpsp(_lof2(x1x0)));

        x1x0_temp = x1x0;

        /* perform one iteration of the Newton-Raphson method */
        z1z0 = _dsubsp(_daddsp(y1y0, y1y0), _dmpysp(_dmpysp(y1y0, y1y0), x1x0_temp));
        
        /* perform second iteration of the Newton-Raphson method */
        r1r0 = _dsubsp(_daddsp(z1z0, z1z0), _dmpysp(_dmpysp(z1z0, z1z0), x1x0_temp));
              
        /* store final reciprocal */
        _amem8_f2((void *)&y[i]) = r1r0;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_vecrecip.c                                       */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

