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
/* DSP_fir_r4.c -- FIR Filter (Radix 4)                                    */
/*                 Optimized C Implementation (w/ Intrinsics)              */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fir_r4 (                                                   */
/*         const short *restrict x,                                        */
/*         const short *restrict h,                                        */
/*         short *restrict r,                                              */
/*         int nh,                                                         */
/*         int nr,                                                         */
/*     )                                                                   */
/*                                                                         */
/*  Description                                                            */
/*     Computes a real FIR filter (direct-form) using coefficients         */
/*     stored in vector h.  The real data input is stored in vector x.     */
/*     The filter output result is stored in vector r.  Input data and     */
/*     filter taps are 16-bit, with intermediate values kept at 32-bit     */
/*     precision.  Filter taps are expected in Q15 format.                 */
/*                                                                         */
/*  Assumptions                                                            */
/*     Arrays x, h, and r do not overlap                                   */
/*     nr >= 4; nr % 4 == 0                                                */
/*     nh >= 4; nh % 4 == 0                                                */
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

#pragma CODE_SECTION(DSP_fir_r4, ".text:optimized");

#include "DSP_fir_r4.h"

#ifdef _LITTLE_ENDIAN
void DSP_fir_r4 (
    const short *restrict x,    /* Input array [nr+nh-1 elements] */
    const short *restrict h,    /* Coeff array [nh elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nh,                     /* Number of coefficients         */
    int nr                      /* Number of output samples       */
)
{
    int i, j;
    int r_32, r_10;
    int ddot_3, ddot_2, ddot_1, ddot_0;
    int sum_0, sum_1, sum_2, sum_3;

    long long x_3210, x_4321, x_5432, x_6543, x_7654;
    long long h_3210;

    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    _nassert(nh % 4 == 0);
    _nassert(nh >= 4);
    for (j = 0; j < nr; j += 4) {
        sum_0 = 0;
        sum_1 = 0;
        sum_2 = 0;
        sum_3 = 0;

        /* Loop through the number of coefficients, 4 at a time 
         * summing all dot products together to form 4 results.
         * Tell compiler this loop will iterate at least once. */
        #pragma MUST_ITERATE(1,,1)
        for (i = 0; i < nh; i += 4) 
        {
           /* Load the four elements of the coefficient array using aligned
            * double word wide load */
            h_3210 = _amem8_const(&h[i]);

            /* Load the seven elements of the data array using aligned
             * double word wide loads */
            x_3210 = _amem8_const(&x[i + j]);
            x_7654 = _amem8_const(&x[i + j + 4]);

            /* Form result 2's filter taps */
            x_5432 = _dmv(_loll(x_7654),_hill(x_3210));

            /* Form result 1's filter taps */          
            x_4321 = _dpacklh2(x_5432,x_3210);

            /* Load result 3's filter taps */          
            x_6543 = _mem8_const(&x[i + j + 3]);

            /* Compute result 3 dot product x6h3 + x5h2 + x4h1 + x3h0 */
            ddot_3 = _dotp4h(x_6543, h_3210);
            /* Compute result 2 dot product x5h3 + x4h2 + x3h1 + x2h0 */
            ddot_2 = _dotp4h(x_5432, h_3210);
            /* Compute result 1 dot product x4h3 + x3h2 + x2h1 + x1h0 */
            ddot_1 = _dotp4h(x_4321, h_3210);
            /* Compute result 0 dot product x3h3 + x2h2 + x1h1 + x0h0 */
            ddot_0 = _dotp4h(x_3210, h_3210);

            /* Sum each ddot_X register to form each results complete sum */
            sum_3 += ddot_3; /* Add x6h3 + x5h2 + x4h1 + x3h0 */
            sum_2 += ddot_2; /* Add x5h3 + x4h2 + x3h1 + x2h0 */
            sum_1 += ddot_1; /* Add x4h3 + x3h2 + x2h1 + x1h0 */
            sum_0 += ddot_0; /* Add x3h3 + x2h2 + x1h1 + x0h0 */
        }

        /* Shift accumulators up 1 into upper halfword, for Q15 math and  
         * pack results together so that four output samples may be stored 
         * as a double word minimizing the number of memory operations. */
        r_10 = _packh2(sum_1 << 1, sum_0 << 1);
        r_32 = _packh2(sum_3 << 1, sum_2 << 1);

        /* Store out four output samples at a time using STDW */
        _amem8(&r[j]) = _itoll(r_32, r_10);
    }
}

/*-----------------------------------------------------------*/
/*  Big Endian version                                       */
/*-----------------------------------------------------------*/
#else
void DSP_fir_r4 (
    const short *restrict x,    /* Input array [nr+nh-1 elements] */
    const short *restrict h,    /* Coeff array [nh elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nh,                     /* Number of coefficients         */
    int nr                      /* Number of output samples       */
)
{

    int i, j;
    int r_01, r_23;
    int ddot_3, ddot_2, ddot_1, ddot_0;
    int sum_0, sum_1, sum_2, sum_3;

    long long x_0123, x_1234, x_2345, x_3456, x_4567;
    long long h_0123;

    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    for (j = 0; j < nr; j += 4) {
        sum_0 = 0;
        sum_1 = 0;
        sum_2 = 0;
        sum_3 = 0;

        /* Loop through the number of coefficients, 4 at a time 
         * summing all dot products together to form 4 results.
         * Tell compiler this loop will iterate at least once. */
        #pragma MUST_ITERATE(1,,1)
        for (i = 0; i < nh; i += 4) {
            /* Load the four elements of the coefficient array using aligned
             * double word wide load */
            h_0123 = _amem8_const(&h[i]);
            
            /* Load the seven elements of the data array using aligned
             * double word wide loads */
            x_0123 = _amem8_const(&x[i + j]);
            x_4567 = _amem8_const(&x[i + j + 4]);

            /* Form result 2's filter taps */
            x_2345 = _dmv(_loll(x_0123),_hill(x_4567));

            /* Form result 1's filter taps */          
            x_1234 = _dpacklh2(x_0123, x_2345);

            /* Load result 3's filter taps */          
            x_3456 = _mem8_const(&x[i + j + 3]);

            /* Compute result 3 dot product x3h0 + x4h1 + x5h2 + x6h3 */
            ddot_3 = _dotp4h(x_3456, h_0123);
            /* Compute result 2 dot product x2h0 + x3h1 + x4h2 + x5h3 */
            ddot_2 = _dotp4h(x_2345, h_0123);
            /* Compute result 1 dot product x1h0 + x2h1 + x3h2 + x4h3 */
            ddot_1 = _dotp4h(x_1234, h_0123);
            /* Compute result 0 dot product x0h0 + x1h1 + x2h2 + x3h3 */
            ddot_0 = _dotp4h(x_0123, h_0123);

            /* Sum each ddot_X register to form each results complete sum */
            sum_3 += ddot_3; /* Add x3h0 + x4h1 + x5h2 + x6h3 */
            sum_2 += ddot_2; /* Add x2h0 + x3h1 + x4h2 + x5h3 */
            sum_1 += ddot_1; /* Add x1h0 + x2h1 + x3h2 + x4h3 */
            sum_0 += ddot_0; /* Add x0h0 + x1h1 + x2h2 + x3h3 */
        }

        /* Shift accumulators up 1 into upper halfword, for Q15 math and  
         * pack results together so that four output samples may be stored 
         * as a double word minimizing the number of memory operations. */
        r_01 = _packh2(sum_0 << 1, sum_1 << 1);
        r_23 = _packh2(sum_2 << 1, sum_3 << 1);

        /* Store out four output samples at a time using STDW */
        _amem8(&r[j]) = _itoll(r_01, r_23);
    }
}
#endif

/* ======================================================================= */
/*  End of file:  DSP_fir_gen.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

