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
/* DSP_fir_r8_h24.c -- FIR 24 Coefficient Filter (Radix 8)                 */
/*                          Optimized C Implementation (w/ Intrinsics)     */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fir_r8_h24 (                                               */
/*         const short *restrict x,                                        */
/*         const short *restrict h,                                        */
/*         short *restrict r,                                              */
/*         int nr,                                                         */
/*     )                                                                   */
/*                                                                         */
/*  Description                                                            */
/*     Computes a real FIR filter (direct-form) using 24 coefficients      */
/*     stored in vector h.  The real data input is stored in vector x.     */
/*     The filter output result is stored in vector r.  Input data and     */
/*     filter taps are 16-bit, with intermediate values kept at 32-bit     */
/*     precision.  Filter taps are expected in Q15 format.                 */
/*                                                                         */
/*  Assumptions                                                            */
/*     Arrays x, h, and r do not overlap                                   */
/*     nr >= 4; nr % 4 == 0                                                */
/*     nh == 24                                                            */
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

#pragma CODE_SECTION(DSP_fir_r8_h24, ".text:optimized");

#include "DSP_fir_r8_h24.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSP_fir_r8_h24 (
    const short *restrict x,    /* Input array [nr+24-1 elements] (A4)*/
    const short *restrict h,    /* Coeff array [24 elements]      (B4)*/
    short       *restrict r,    /* Output array [nr elements]     (A6)*/
    int nr                      /* Number of output samples       (A8)*/
)
{
    /* 24 Coefficient FIR Radix 8 implementation */
    int j;
    long long h_3210, h_7654, h_BA98, h_FEDC, h_JIHG, h_NMLK;
    long long x_3210, x_7654, x_BA98;
    long long x_9876, x_5432, x_4321, x_6543, x_8765, x_A987;
    long long ddot_0, ddot_1, ddot_2, ddot_3;
    long long sum_20, sum_31;
    __x128_t h_7654_3210, h_FEDC_BA98, h_NMLK_JIHG;
    __x128_t x_7654_3210, x_8765_4321, x_9876_5432, x_A987_6543;

    /* Preload the twenty four filter array coefficients using aligned
     * double word wide loads and form three 128-bit quad register pairs */
    h_NMLK = _amem8_const(&h[20]);
    h_JIHG = _amem8_const(&h[16]);
    h_FEDC = _amem8_const(&h[12]);
    h_BA98 = _amem8_const(&h[8]);
    h_7654 = _amem8_const(&h[4]);
    h_3210 = _amem8_const(&h[0]);
    h_NMLK_JIHG = _llto128(h_NMLK,h_JIHG);
    h_FEDC_BA98 = _llto128(h_FEDC,h_BA98);
    h_7654_3210 = _llto128(h_7654,h_3210);

    /* Four results will be computed per loop iteration */
    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    for (j = 0; j < nr; j += 4)
    {
        /* Compute first third of each result using coefficients 0 - 7 (8 used)
         * and data array inputs 0 - 11 (12 total - 11 used) */

        /* Load the first eleven elements of the data array using aligned
         * double word wide loads */
        x_BA98 = _amem8_const(&x[j+8]);
        x_7654 = _amem8_const(&x[j+4]);
        x_3210 = _amem8_const(&x[j]);

        /* Form the first third of result 2's filter taps */
        x_9876 = _dmv(_loll(x_BA98),_hill(x_7654));
        x_5432 = _dmv(_loll(x_7654),_hill(x_3210));

        /* Form the first third of result 1's filter taps */
        x_4321 = _mem8_const(&x[j+1]);
        x_8765 = _dpacklh2(x_9876,x_7654);
        /* Form the first third of result 3's filter taps */
        x_6543 = _dpacklh2(x_7654,x_5432);
        x_A987 = _dpacklh2(x_BA98,x_9876);

        /* Create four 128-bit quad register pairs holding all the result
         * filter tap first thirds */
        x_7654_3210 = _llto128(x_7654,x_3210);
        x_8765_4321 = _llto128(x_8765,x_4321);
        x_9876_5432 = _llto128(x_9876,x_5432);
        x_A987_6543 = _llto128(x_A987,x_6543);

        /* Compute first third of result 0 double dot product
         * x7h7 + x6h6 + x5h5 + x4h4 ; x3h3 + x2h2 + x1h1 + x0h0 */
        ddot_0 = _ddotp4h(x_7654_3210, h_7654_3210); 
        /* Compute first third of result 1 double dot product
         * x8h7 + x7h6 + x6h5 + x5h4 ; x4h3 + x3h2 + x2h1 + x1h0 */
        ddot_1 = _ddotp4h(x_8765_4321, h_7654_3210);  
        /* Compute first third of result 2 double dot product
         * x9h7 + x8h6 + x7h5 + x6h4 ; x5h3 + x4h2 + x3h1 + x2h0 */
        ddot_2 = _ddotp4h(x_9876_5432, h_7654_3210);  
        /* Compute first third of result 3 double dot product
         * xAh7 + x9h6 + x8h5 + x7h4 ; x6h3 + x5h2 + x4h1 + x3h0 */
        ddot_3 = _ddotp4h(x_A987_6543, h_7654_3210);    

        /* Compute second third of each result using coefficients 8 - 15 (8 used)
         * and data array inputs 8 - 20 (12 total - 11 used) */

        /* Load the second eleven elements of the data array using aligned
         * double word wide loads */
        x_3210 = x_BA98;
        x_BA98 = _amem8_const(&x[j+16]);
        x_7654 = _amem8_const(&x[j+12]);

        /* Form the second third of result 2's filter taps */
        x_9876 = _dmv(_loll(x_BA98),_hill(x_7654));
        x_5432 = _dmv(_loll(x_7654),_hill(x_3210));

        /* Form the second third of result 1's filter taps */
        x_4321 = _dpacklh2(x_5432,x_3210);
        x_8765 = _dpacklh2(x_9876,x_7654);
        /* Form the second third of result 3's filter taps */
        x_6543 = _dpacklh2(x_7654,x_5432);
        x_A987 = _mem8_const(&x[j+15]);

        /* Create four 128-bit quad register pairs holding all the result
         * filter tap second thirds */
        x_7654_3210 = _llto128(x_7654,x_3210);
        x_8765_4321 = _llto128(x_8765,x_4321);
        x_9876_5432 = _llto128(x_9876,x_5432);
        x_A987_6543 = _llto128(x_A987,x_6543);

        /* Compute second third of result 0 double dot product and add to
         * the first third.
         * xFhF + xEhE + xDhD + xChC ; xBhB + xAhA + x9h9 + x8h8 */
        ddot_0 = _dsadd(ddot_0, _ddotp4h(x_7654_3210, h_FEDC_BA98)); 
        /* Compute second third of result 1 double dot product and add to
         * the first third.
         * x10hF + xFhE + xEhD + xDhC ; xChB + xBhA + xAh9 + x9h8 */
        ddot_1 = _dsadd(ddot_1, _ddotp4h(x_8765_4321, h_FEDC_BA98));  
        /* Compute second third of result 2 double dot product and add to
         * the first third.
         * x11hF + x10hE + xFhD + xEhC ; xDhB + xChA + xBh9 + xAh8 */
        ddot_2 = _dsadd(ddot_2, _ddotp4h(x_9876_5432, h_FEDC_BA98));  
        /* Compute second third of result 3 double dot product and add to
         * the first third.
         * x12hF + x11hE + x10hD + xFhC ; xEhB + xDhA + xCh9 + xBh8 */
        ddot_3 = _dsadd(ddot_3, _ddotp4h(x_A987_6543, h_FEDC_BA98));  

        /* Compute last third of each result using coefficients 16 - 23 (8 used)
         * and data array inputs 16 - 28 (12 total - 11 used) */

        /* Load the third eleven elements of the data array using aligned
         * double word wide loads */
        x_3210 = x_BA98;
        x_BA98 = _amem8_const(&x[j+24]);
        x_7654 = _amem8_const(&x[j+20]);

        /* Form the last third of result 2's filter taps */
        x_9876 = _dmv(_loll(x_BA98),_hill(x_7654));
        x_5432 = _dmv(_loll(x_7654),_hill(x_3210));

        /* Form the last third of result 1's filter taps */
        x_4321 = _dpacklh2(x_5432,x_3210);
        x_8765 = _dpacklh2(x_9876,x_7654);
        /* Form the last third of result 3's filter taps */
        x_6543 = _mem8_const(&x[j+19]);
        x_A987 = _dpacklh2(x_BA98,x_9876);

        /* Create four 128-bit quad register pairs holding all the result
         * filter tap third halves */
        x_7654_3210 = _llto128(x_7654,x_3210);
        x_8765_4321 = _llto128(x_8765,x_4321);
        x_9876_5432 = _llto128(x_9876,x_5432);
        x_A987_6543 = _llto128(x_A987,x_6543);

        /* Compute last third of result 0 double dot product and add to
         * the first and second thirds.
         * x17hN + x16hM + x15hL + x14hK ; x13hJ + x12hI + x11hH + x10hG */
        ddot_0 = _dsadd(ddot_0, _ddotp4h(x_7654_3210, h_NMLK_JIHG)); 
        /* Compute last third of result 1 double dot product and add to
         * the first and second thirds.
         * x18hN + x17hM + x16hL + x15hK ; x14hJ + x13hI + x12hH + x11hG */
        ddot_1 = _dsadd(ddot_1, _ddotp4h(x_8765_4321, h_NMLK_JIHG));  
        /* Compute last third of result 2 double dot product and add to
         * the first and second thirds.
         * x19hN + x18hM + x17hL + x16hK ; x15hJ + x14hI + x13hH + x12hG */
        ddot_2 = _dsadd(ddot_2, _ddotp4h(x_9876_5432, h_NMLK_JIHG));  
        /* Compute last third of result 3 double dot product and add to
         * the first and second thirds.
         * x1AhN + x19hM + x18hL + x17hK ; x16hJ + x15hI + x14hH + x13hG */
        ddot_3 = _dsadd(ddot_3, _ddotp4h(x_A987_6543, h_NMLK_JIHG));  

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
void DSP_fir_r8_h24 (
    const short *restrict x,    /* Input array [nr+24-1 elements] */
    const short *restrict h,    /* Coeff array [24 elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nr                      /* Number of output samples       */
)
{
    /* 24 Coefficient FIR Radix 8 implementation */
    int j;
    long long h_0123, h_4567, h_89AB, h_CDEF, h_GHIJ, h_KLMN;
    long long x_0123, x_4567, x_89AB;
    long long x_6789, x_2345, x_1234, x_3456, x_5678, x_789A;
    long long ddot_0, ddot_1, ddot_2, ddot_3;
    long long sum_02, sum_13;

    __x128_t h_0123_4567, h_89AB_CDEF, h_GHIJ_KLMN;
    __x128_t x_0123_4567, x_1234_5678, x_2345_6789, x_3456_789A;

    /* Preload the twenty four filter array coefficients using aligned 
     * double word wide loads and form three 128-bit quad register pairs */
    h_KLMN = _amem8_const(&h[20]);
    h_GHIJ = _amem8_const(&h[16]);
    h_CDEF = _amem8_const(&h[12]);
    h_89AB = _amem8_const(&h[8]);
    h_4567 = _amem8_const(&h[4]);
    h_0123 = _amem8_const(&h[0]);
    h_GHIJ_KLMN = _llto128(h_GHIJ,h_KLMN);
    h_89AB_CDEF = _llto128(h_89AB,h_CDEF);
    h_0123_4567 = _llto128(h_0123,h_4567);

    /* Four results will be computed per loop iteration */
    _nassert(nr % 4 == 0);
    _nassert(nr >= 4);
    for (j = 0; j < nr; j += 4)
    {
        /* Compute first third of each result using coefficients 0 - 7 (8 used)
         * and data array inputs 0 - 11 (12 total - 11 used) */

        /* Load the first eleven elements of the data array using aligned
         * double word wide loads */
        x_89AB = _amem8_const(&x[j+8]);
        x_4567 = _amem8_const(&x[j+4]);
        x_0123 = _amem8_const(&x[j]);

        /* Form the first third of result 2's filter taps */
        x_6789 = _dmv(_loll(x_4567),_hill(x_89AB));
        x_2345 = _dmv(_loll(x_0123),_hill(x_4567));

        /* Form the first third of result 1's filter taps */
        x_1234 = _mem8_const(&x[j+1]);
        x_5678 = _dpacklh2(x_4567,x_6789);
        /* Form the first third of result 3's filter taps */
        x_3456 = _dpacklh2(x_2345,x_4567);
        x_789A = _dpacklh2(x_6789,x_89AB);

        /* Create four 128-bit quad register pairs holding all the result
         * filter tap first halves */
        x_0123_4567 = _llto128(x_0123,x_4567);
        x_1234_5678 = _llto128(x_1234,x_5678);
        x_2345_6789 = _llto128(x_2345,x_6789);
        x_3456_789A = _llto128(x_3456,x_789A);

        /* Compute first third of result 0 double dot product
         * x0h0 + x1h1 + x2h2 + x3h3 ; x4h4 + x5h5 + x6h6 + x7h7 */
        ddot_0 = _ddotp4h(x_0123_4567, h_0123_4567); 
        /* Compute first third of result 1 double dot product
         * x1h0 + x2h1 + x3h2 + x4h3 ; x5h4 + x6h5 + x7h6 + x8h7 */
        ddot_1 = _ddotp4h(x_1234_5678, h_0123_4567);  
        /* Compute first third of result 2 double dot product
         * x2h0 + x3h1 + x4h2 + x5h3 ; x6h4 + x7h5 + x8h6 + x9h7 */
        ddot_2 = _ddotp4h(x_2345_6789, h_0123_4567);  
        /* Compute first third of result 3 double dot product
         * x3h0 + x4h1 + x5h2 + x6h3 ; x7h4 + x8h5 + x9h6 + xAh7 */
        ddot_3 = _ddotp4h(x_3456_789A, h_0123_4567);    

        /* Compute second third of each result using coefficients 8 - 15 (8 used)
         * and data array inputs 8 - 20 (12 total - 11 used) */

        /* Load the second eleven elements of the data array using aligned
         * double word wide loads */
        x_0123 = x_89AB;
        x_89AB = _amem8_const(&x[j+16]);
        x_4567 = _amem8_const(&x[j+12]);

        /* Form the second third of result 2's filter taps */
        x_6789 = _dmv(_loll(x_4567),_hill(x_89AB));
        x_2345 = _dmv(_loll(x_0123),_hill(x_4567));

        /* Form the second third of result 1's filter taps */
        x_1234 = _mem8_const(&x[j+9]);
        x_5678 = _mem8_const(&x[j+13]);
        /* Form the second third of result 3's filter taps */
        x_3456 = _dpacklh2(x_2345,x_4567);
        x_789A = _dpacklh2(x_6789,x_89AB);

        /* Create four 128-bit quad register pairs holding all the result
         * filter tap second halves */
        x_0123_4567 = _llto128(x_0123,x_4567);
        x_1234_5678 = _llto128(x_1234,x_5678);
        x_2345_6789 = _llto128(x_2345,x_6789);
        x_3456_789A = _llto128(x_3456,x_789A);

        /* Compute second third of result 0 double dot product and add to
         * the first third.
         * x8h8 + x9h9 + xAhA + xBhB ; xChC + xDhD + xEhE + xFhF */
        ddot_0 = _dsadd(ddot_0, _ddotp4h(x_0123_4567, h_89AB_CDEF)); 
        /* Compute second third of result 1 double dot product and add to
         * the first third.
         * x9h8 + xAh9 + xBhA + xChB ; xDhC + xEhD + xFhE + x10hF */
        ddot_1 = _dsadd(ddot_1, _ddotp4h(x_1234_5678, h_89AB_CDEF));  
        /* Compute second third of result 2 double dot product and add to
         * the first third.
         * xAh8 + xBh9 + xChA + xDhB ; xEhC + xFhD + x10hE + x11hF */
        ddot_2 = _dsadd(ddot_2, _ddotp4h(x_2345_6789, h_89AB_CDEF));  
        /* Compute second third of result 3 double dot product and add to
         * the first third.
         * xBh8 + xCh9 + xDhA + xEhB ; xFhC + x10hD + x11hE + x12hF */
        ddot_3 = _dsadd(ddot_3, _ddotp4h(x_3456_789A, h_89AB_CDEF));  

        /* Compute last third of each result using coefficients 16 - 23 (8 used)
         * and data array inputs 16 - 28 (12 total - 11 used) */

        /* Load the third eleven elements of the data array using aligned
         * double word wide loads */
        x_0123 = x_89AB;
        x_89AB = _amem8_const(&x[j+24]);
        x_4567 = _amem8_const(&x[j+20]);

        /* Form the last third of result 2's filter taps */
        x_6789 = _dmv(_loll(x_4567),_hill(x_89AB));
        x_2345 = _dmv(_loll(x_0123),_hill(x_4567));

        /* Form the last third of result 1's filter taps */
        x_1234 = _dpacklh2(x_0123,x_2345);
        x_5678 = _dpacklh2(x_4567,x_6789);
        /* Form the last third of result 3's filter taps */
        x_3456 = _dpacklh2(x_2345,x_4567);
        x_789A = _dpacklh2(x_6789,x_89AB);

        /* Create four 128-bit quad register pairs holding all the result
         * filter tap third halves */
        x_0123_4567 = _llto128(x_0123,x_4567);
        x_1234_5678 = _llto128(x_1234,x_5678);
        x_2345_6789 = _llto128(x_2345,x_6789);
        x_3456_789A = _llto128(x_3456,x_789A);

        /* Compute last third of result 0 double dot product and add to
         * the first and second thirds.
         * x10hG + x11hH + x12hI + x13hJ ; x14hK + x15hL+ x16hM + x17hN */
        ddot_0 = _dsadd(ddot_0, _ddotp4h(x_0123_4567, h_GHIJ_KLMN)); 
        /* Compute last third of result 1 double dot product and add to
         * the first and second thirds.
         * x11hG + x12hH + x13hI + x14hJ ; x15hK + x16hL+ x17hM + x18hN */
        ddot_1 = _dsadd(ddot_1, _ddotp4h(x_1234_5678, h_GHIJ_KLMN));  
        /* Compute last third of result 2 double dot product and add to
         * the first and second thirds.
         * x12hG + x13hH + x14hI + x15hJ ; x16hK + x17hL+ x18hM + 19hN */
        ddot_2 = _dsadd(ddot_2, _ddotp4h(x_2345_6789, h_GHIJ_KLMN));  
        /* Compute last third of result 3 double dot product and add to
         * the first and second thirds.
         * x13hG + x14hH + x15hI + x16hJ ; x17hK + x18hL+ x19hM + x1AhN */
        ddot_3 = _dsadd(ddot_3, _ddotp4h(x_3456_789A, h_GHIJ_KLMN)); 

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
/*  End of file:  DSP_fir_r8_h24.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
