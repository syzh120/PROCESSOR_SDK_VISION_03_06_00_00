/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  DSPLIB  DSP Signal Processing Library                                  */
/*                                                                         */
/*  This library contains proprietary intellectual property of Texas       */
/*  Instruments, Inc.  The library and its source code are protected by    */
/*  various copyrights, and portions may also be protected by patents or   */
/*  other legal protections.                                               */
/*                                                                         */
/*  This software is licensed for use with Texas Instruments TMS320        */
/*  family DSPs.  This license was provided to you prior to installing     */
/*  the software.  You may review this license by consulting the file      */
/*  TI_license.PDF which accompanies the files in this library.            */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/* DSP_q15tofl.c -- Float to Q15 conversion                                */
/*                  Optimized C Implementation (w/ Intrinsics)             */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_q15tofl (                                                  */
/*         const short *restrict q15, // Input Q15 array                   */
/*         float *restrict flt,       // Output float array                */
/*         short nx                   // Number of elements                */
/*     );                                                                  */
/*                                                                         */
/*     x[nx]  ---  Pointer to Q15 input vector of size nx                  */
/*     r[nx]  ---  Pointer to floating-point output data vector            */
/*                 of size nx containing the floating-point equivalent     */
/*                 of vector input                                         */
/*     nx     ---  length of input and output data vectors                 */
/*                                                                         */
/*  Description                                                            */
/*     Converts the Q15 stored in vector input to IEEE floating point      */
/*     numbers stored in vector output.                                    */
/*                                                                         */
/*     void q15tofl (short *q15, float *flt, int nx)                       */
/*     {                                                                   */
/*      int i;                                                             */
/*                                                                         */
/*      for (i=0;i<nx;i++)                                                 */
/*           flt[i]=(float)q15[i]/0x8000;                                  */
/*     }                                                                   */
/*                                                                         */
/*     The above C code is a general implementation without                */
/*     restrictions.  The assembly code may have some restrictions, as     */
/*     noted below.                                                        */
/*                                                                         */
/*  Assumptions                                                            */
/*     Arrays q15 and flt do not overlap                                   */
/*     nx >= 4;   nx % 4 == 0;                                             */
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

#pragma CODE_SECTION(DSP_q15tofl, ".text:optimized");

#include "DSP_q15tofl.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSP_q15tofl (
    const short *restrict q15,  /* Input Q15 array      */
    float *restrict flt,        /* Output float array   */
    int   nx                    /* Number of elements   */
)
{
    int       i;
    long long input, ones;
    float     temp;
    __float2_t scale;
    __x128_t  in_int;

    /* to expand short into int with dmpy2 */
    ones  = _itoll(0x00010001, 0x00010001);

    /* scaling factor for Q15 */
    temp  = 1./32768;
    scale = _ftof2(temp, temp);

    #pragma MUST_ITERATE(1,,1)
    for (i = 0; i < nx; i += 4) {
        input  = _amem8((void*)&q15[i]);
        in_int = _dmpy2(input, ones);
        _amem8_f2((void*)&flt[i+0]) = _dmpysp(_dintsp(_lo128(in_int)), scale);
        _amem8_f2((void*)&flt[i+2]) = _dmpysp(_dintsp(_hi128(in_int)), scale);
    }
}
#else
void DSP_q15tofl (
    const short *restrict q15,  /* Input Q15 array      */
    float *restrict flt,        /* Output float array   */
    int   nx                    /* Number of elements   */
)
{
    int       i;
    long long input, ones;
    float     temp;
    __float2_t scale;
    __x128_t  in_int;

    /* to expand short into int with dmpy2 */
    ones  = _itoll(0x00010001, 0x00010001);

    /* scaling factor for Q15 */
    temp  = 1./32768;
    scale = _ftof2(temp, temp);

    #pragma MUST_ITERATE(1,,1)
    for (i = 0; i < nx; i += 4) {
        input  = _amem8((void*)&q15[i]);
        in_int = _dmpy2(input, ones);
        _amem8_f2((void*)&flt[i+0]) = _dmpysp(_dintsp(_hi128(in_int)), scale);
        _amem8_f2((void*)&flt[i+2]) = _dmpysp(_dintsp(_lo128(in_int)), scale);
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSP_q15tofl.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

