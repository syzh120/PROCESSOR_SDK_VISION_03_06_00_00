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
/* DSP_fir_r8_h8.c -- FIR 8 Coefficient Filter (Radix 8)                   */
/*                    Optimized C Implementation (w/ Intrinsics)           */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fir_r8_h8 (                                                */
/*         const short *restrict x,                                        */
/*         const short *restrict h,                                        */
/*         short *restrict r,                                              */
/*         int nr,                                                         */
/*     )                                                                   */
/*                                                                         */
/*  Description                                                            */
/*     Computes a real FIR filter (direct-form) using 8 coefficients       */
/*     stored in vector h.  The real data input is stored in vector x.     */
/*     The filter output result is stored in vector r.  Input data and     */
/*     filter taps are 16-bit, with intermediate values kept at 32-bit     */
/*     precision.  Filter taps are expected in Q15 format.                 */
/*                                                                         */
/*  Assumptions                                                            */
/*     Arrays x, h, and r do not overlap                                   */
/*     nr >= 4; nr % 4 == 0                                                */
/*     nh == 8                                                             */
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

#pragma CODE_SECTION(DSP_fir_r8_h8, ".text:optimized");

#include "DSP_fir_r8_h8.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSP_fir_r8_h8 (
    const short *restrict x,    /* Input array [nr+8-1 elements] */
    const short *restrict h,    /* Coeff array [8 elements]      */
    short       *restrict r,    /* Output array [nr elements]    */
    int nr                      /* Number of output samples      */
)
{
    /* 8 Coefficient FIR Radix 8 implementation */
    int j;

    long long h_7654, h_3210;
    long long x_3210, x_7654, x_BA98;
    long long x_9876, x_5432, x_4321, x_6543, x_8765, x_A987;
    long long ddot_0, ddot_1, ddot_2, ddot_3;
    long long sum_20, sum_31;
    __x128_t h_7654_3210, x_7654_3210, x_8765_4321, x_9876_5432, x_A987_6543;

    /* Preload the eight filter array coefficients using aligned double word
     * wide loads and form a 128-bit quad register pair */
    h_7654 = _amem8_const(&h[4]);
    h_3210 = _amem8_const(&h[0]);
    h_7654_3210 = _llto128(h_7654,h_3210);

    /* Four results will be computed per loop iteration */
    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    for (j = 0; j < nr; j += 4)
    {
        /* Load the first eleven elements of the data array using aligned
         * double word wide loads */
        x_BA98 = _amem8_const(&x[j+8]);
        x_7654 = _amem8_const(&x[j+4]);
        x_3210 = _amem8_const(&x[j]);

        /* Form result 2's filter taps */
        x_9876 = _itoll(_loll(x_BA98),_hill(x_7654));
        x_5432 = _itoll(_loll(x_7654),_hill(x_3210));

        /* Form result 1's filter taps.  Perform loads to 
         * balance .L and .S unit usage with .D unit */
        x_4321 = _mem8_const(&x[j+1]);
        x_8765 = _mem8_const(&x[j+5]);
        /* Form result 3's filter taps */
        x_6543 = _dpacklh2(x_7654,x_5432);
        x_A987 = _dpacklh2(x_BA98,x_9876);

        /* Create four 128-bit quad register pairs holding all the result
         * filter taps */
        x_7654_3210 = _llto128(x_7654,x_3210);
        x_8765_4321 = _llto128(x_8765,x_4321);
        x_9876_5432 = _llto128(x_9876,x_5432);
        x_A987_6543 = _llto128(x_A987,x_6543);

        /* Compute result 0 double dot product
         * x7h7 + x6h6 + x5h5 + x4h4 ; x3h3 + x2h2 + x1h1 + x0h0 */
        ddot_0 = _ddotp4h(x_7654_3210, h_7654_3210); 
        /* Compute result 1 double dot product
         * x8h7 + x7h6 + x6h5 + x5h4 ; x4h3 + x3h2 + x2h1 + x1h0 */
        ddot_1 = _ddotp4h(x_8765_4321, h_7654_3210);  
        /* Compute result 2 double dot product
         * x9h7 + x8h6 + x7h5 + x6h4 ; x5h3 + x4h2 + x3h1 + x2h0 */
        ddot_2 = _ddotp4h(x_9876_5432, h_7654_3210);  
        /* Compute result 3 double dot product
         * xAh7 + x9h6 + x8h5 + x7h4 ; x6h3 + x5h2 + x4h1 + x3h0 */
        ddot_3 = _ddotp4h(x_A987_6543, h_7654_3210);  

        /* Sum the high and low portions of each ddot_X register pair to
         * form each results complete sum.  Then shift down 15 to convert
         * to Q15 format. */
        sum_20 = _itoll(_hill(ddot_2)+_loll(ddot_2), _hill(ddot_0)+_loll(ddot_0));
        sum_20 = _dshr(sum_20, 15);
        sum_31 = _itoll(_hill(ddot_3)+_loll(ddot_3), _hill(ddot_1)+_loll(ddot_1));
        sum_31 = _dshr(sum_31, 15);

        /* Store out four output samples at a time using STDW */
        _amem8(&r[j]) = _dpackl2(sum_31, sum_20);
    }
}

/*-----------------------------------------------------------*/
/*  Big Endian version                                       */
/*-----------------------------------------------------------*/
#else
void DSP_fir_r8_h8 (
    const short *restrict x,    /* Input array [nr+8-1 elements] */
    const short *restrict h,    /* Coeff array [8 elements]     */
    short       *restrict r,    /* Output array [nr elements]    */
    int nr                      /* Number of output samples      */
)
{
    /* 8 Coefficient FIR Radix 8 implementation */
    int j;

    long long h_4567, h_0123;
    long long x_0123, x_4567, x_89AB;
    long long x_6789, x_2345, x_1234, x_3456, x_5678, x_789A;
    long long ddot_0, ddot_1, ddot_2, ddot_3;
    long long sum_02, sum_13;
    
    __x128_t h_0123_4567, x_0123_4567, x_1234_5678, x_2345_6789, x_3456_789A;
    
    /* Preload the eight filter array coefficients using aligned double word
     * wide loads and form a 128-bit quad register pair */
    h_4567 = _amem8_const(&h[4]);
    h_0123 = _amem8_const(&h[0]);
    h_0123_4567 = _llto128(h_0123,h_4567);
    
    /* Four results will be computed per loop iteration */
    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    for (j = 0; j < nr; j += 4)
    {
        /* Load the first eleven elements of the data array using aligned
         * double word wide loads */
        x_89AB = _amem8_const(&x[j+8]);
        x_4567 = _amem8_const(&x[j+4]);
        x_0123 = _amem8_const(&x[j]);
    
        /* Form result 2's filter taps */
        x_6789 = _itoll(_loll(x_4567),_hill(x_89AB));
        x_2345 = _itoll(_loll(x_0123),_hill(x_4567));
    
        /* Form result 1's filter taps.  Perform loads to 
         * balance .L and .S unit usage with .D unit */
        x_1234 = _dpacklh2(x_0123,x_2345);
        x_5678 = _dpacklh2(x_4567,x_6789);
        /* Form result 3's filter taps */
        x_3456 = _mem8_const(&x[j+3]);
        x_789A = _mem8_const(&x[j+7]);
    
        /* Create four 128-bit quad register pairs holding all the result
         * filter taps */
        x_0123_4567 = _llto128(x_0123,x_4567);
        x_1234_5678 = _llto128(x_1234,x_5678);
        x_2345_6789 = _llto128(x_2345,x_6789);
        x_3456_789A = _llto128(x_3456,x_789A);
    
        /* Compute result 0 double dot product
         * x0h0 + x1h1 + x2h2 + x3h3 ; x4h4 + x5h5 + x6h6 + x7h7 */
        ddot_0 = _ddotp4h(x_0123_4567, h_0123_4567); 
        /* Compute result 1 double dot product
         * x1h0 + x2h1 + x3h2 + x4h3 ; x5h4 + x6h5 + x7h6 + x8h7 */
        ddot_1 = _ddotp4h(x_1234_5678, h_0123_4567);  
        /* Compute result 2 double dot product
         * x2h0 + x3h1 + x4h2 + x5h3 ; x6h4 + x7h5 + x8h6 + x9h7 */
        ddot_2 = _ddotp4h(x_2345_6789, h_0123_4567);  
        /* Compute result 3 double dot product
         * x3h0 + x4h1 + x5h2 + x6h3 ; x7h4 + x8h5 + x9h6 + xAh7 */
        ddot_3 = _ddotp4h(x_3456_789A, h_0123_4567);  

        /* Sum the high and low portions of each ddot_X register pair to
         * form each results complete sum.  Then shift down 15 to convert
         * to Q15 format. */
        sum_02 = _itoll(_hill(ddot_0)+_loll(ddot_0), _hill(ddot_2)+_loll(ddot_2));
        sum_02 = _dshr(sum_02, 15);
        sum_13 = _itoll(_hill(ddot_1)+_loll(ddot_1), _hill(ddot_3)+_loll(ddot_3));
        sum_13 = _dshr(sum_13, 15);

        /* Store out four output samples at a time using STDW */
        _amem8(&r[j]) = _dpackl2(sum_02, sum_13);
    }
}
#endif

/* ======================================================================= */
/*  End of file:  DSP_fir_r8_h8.c                                          */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
