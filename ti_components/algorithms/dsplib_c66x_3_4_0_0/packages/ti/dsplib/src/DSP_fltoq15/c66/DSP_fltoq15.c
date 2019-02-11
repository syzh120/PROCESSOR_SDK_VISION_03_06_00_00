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
/* DSP_fltoq15.c -- Float to Q15 conversion                                */
/*                  Optimized C Implementation (w/ Intrinsics)             */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fltoq15 (                                                  */
/*         const float *restrict flt, // Input float array                 */
/*         short *restrict q15,       // Output Q15 array                  */
/*         short nx                   // Number of elements                */
/*     );                                                                  */
/*                                                                         */
/*     Convert the IEEE floating point numbers stored in vector x[] into   */
/*     Q.15 format numbers stored in vector r[]. Results are truncated     */
/*     towards zero. Values that exceed the size limit will be saturated   */
/*     to 0x7fff if value is positive and 0x8000 if value is negative.     */
/*     All values too small to be correctly represented will be truncated  */
/*     to 0.                                                               */
/*                                                                         */
/*     The 16-bit Q.15 format is defined as follows:                       */
/*                                                                         */
/*         1 11111                                                         */
/*         5 432109876543210                                               */
/*         S.XXXXXXXXXXXXXXX                                               */
/*                                                                         */
/*         range: 1.000000000000000 = -1.0               <-> -32768        */
/*                0.111111111111111 =  0.999969482421875 <->  32767        */
/*                                                                         */
/*     IEEE floating point format is defined as follows:                   */
/*                                                                         */
/*         31 | 30....23 | 22.....0                                        */
/*         S  | EXPONENT | MANTISSA                                        */
/*                                                                         */
/*     The value is obtained as: (-1)^S * 1.MANTISSA * 2^(EXPONENT-127)    */
/*                                                                         */
/*  Assumptions                                                            */
/*     Arrays flt and q15 do not overlap                                   */
/*     nx >= 2    nx % 2 == 0                                              */
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

#pragma CODE_SECTION(DSP_fltoq15, ".text:optimized");

#include "DSP_fltoq15.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSP_fltoq15 (
    const float *restrict flt,  /* Input float array    */
    short *restrict q15,        /* Output Q15 array     */
    int   nx                    /* Number of elements   */
)
{
    int       i;
    long long output1, output2, round1, round2;
    __float2_t input1, input2, scale;

    /* scaling factor for Q31 int */
    scale  = _ftof2(2147483648., 2147483648.);
    /* rounding factor */
    round1 = _itoll(0x8000, 0x8000);
    round2 = _itoll(0x8000, 0x8000);

    #pragma MUST_ITERATE(1,,1)
    for (i = 0; i < nx; i += 4) {
        input1  = _dmpysp(scale, _amem8_f2((void*)&flt[i+0]));
        input2  = _dmpysp(scale, _amem8_f2((void*)&flt[i+2]));
        output1 = _dsadd(round1, _dspint(input1));
        output2 = _dsadd(round2, _dspint(input2));
        _amem8((void*)&q15[i]) = _itoll(_packh2(_hill(output2), _loll(output2)),
                                        _packh2(_hill(output1), _loll(output1)));
    }
}
#else
void DSP_fltoq15 (
    const float *restrict flt,  /* Input float array    */
    short *restrict q15,        /* Output Q15 array     */
    int   nx                    /* Number of elements   */
)
{
    int       i;
    long long output1, output2, round1, round2;
    __float2_t input1, input2, scale;

    /* scaling factor for Q31 int */
    scale  = _ftof2(2147483648., 2147483648.);
    /* rounding factor */
    round1 = _itoll(0x8000, 0x8000);
    round2 = _itoll(0x8000, 0x8000);

    #pragma MUST_ITERATE(1,,1)
    for (i = 0; i < nx; i += 4) {
        input1  = _dmpysp(scale, _amem8_f2((void*)&flt[i+0]));
        input2  = _dmpysp(scale, _amem8_f2((void*)&flt[i+2]));
        output1 = _dsadd(round1, _dspint(input1));
        output2 = _dsadd(round2, _dspint(input2));
        _amem8((void*)&q15[i]) = _itoll(_packh2(_hill(output1), _loll(output1)),
                                        _packh2(_hill(output2), _loll(output2)));
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSP_fltoq15.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

