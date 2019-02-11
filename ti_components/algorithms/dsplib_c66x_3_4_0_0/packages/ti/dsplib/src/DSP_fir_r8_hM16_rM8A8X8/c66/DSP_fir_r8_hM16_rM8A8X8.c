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
/* DSP_fir_r8_hM16_rM8A8X8.c -- FIR Filter (Radix 8)                       */
/*                              Intrinsic C Implementation                 */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fir_r8_hM16_rM8A8X8 (                                      */
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
/*     nr >= 8; nr % 8 == 0                                                */
/*     nh >= 8; nh % 8 == 0                                               */
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

#pragma CODE_SECTION(DSP_fir_r8_hM16_rM8A8X8, ".text:optimized");

#include "DSP_fir_r8_hM16_rM8A8X8.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSP_fir_r8_hM16_rM8A8X8 (
    const short *restrict x,    /* Input array [nr+nh-1 elements] */
    const short *restrict h,    /* Coeff array [nh elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nh,                     /* Number of coefficients         */
    int nr                      /* Number of output samples       */
)
{
    int i, j;
    long long h_3210, h_7654;
    long long x_3210, x_4321, x_5432, x_6543, x_7654, x_8765, x_9876;
    long long x_A987, x_BA98, x_CBA9, x_DCBA, x_EDCB, x_FEDC;
    long long ddot_0, ddot_1, ddot_2, ddot_3, ddot_4, ddot_5, ddot_6, ddot_7;
    long long sum_0, sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7;
    long long sum_20, sum_31, sum_75, sum_64;

    __x128_t h_7654_3210;
    __x128_t x_7654_3210, x_9876_5432, x_8765_4321, x_A987_6543;
    __x128_t x_BA98_7654, x_CBA9_8765, x_DCBA_9876, x_EDCB_A987;

    /* Four results will be computed per loop iteration */
    _nassert(nh % 8 == 0);
    _nassert(nh >= 8);
    _nassert(nr % 8 == 0);
    _nassert(nr >= 8);
    for (j = 0; j < nr; j += 8) {
        /* Initialize the 8 result accumulators to zero */
        sum_0 = 0;
        sum_1 = 0;
        sum_2 = 0; 
        sum_3 = 0;
        sum_4 = 0;
        sum_5 = 0;
        sum_6 = 0;
        sum_7 = 0;

        /* Loop through the number of coefficients, 8 at a time 
         * summing all dot products together to form 8 results */
        for (i = 0; i < nh; i += 8)
        {
            /* Load the eleven elements of the data array using aligned
             * double word wide loads */
            x_FEDC = _amem8_const(&x[i + j + 12]);
            x_BA98 = _amem8_const(&x[i + j + 8]);
            x_7654 = _amem8_const(&x[i + j + 4]);
            x_3210 = _amem8_const(&x[i + j]);

            /* Load the eight elements of the coefficient array using aligned
             * double word wide loads */
            h_7654 = _amem8_const(&h[i + 4]);
            h_3210 = _amem8_const(&h[i]);

            /* Form the coefficient 128-bit quad register pair */
            h_7654_3210 = _llto128(h_7654,h_3210);

            /* Form filter taps */
            x_DCBA = _dmv(_loll(x_FEDC),_hill(x_BA98));
            x_9876 = _dmv(_loll(x_BA98),_hill(x_7654));
            x_5432 = _dmv(_loll(x_7654),_hill(x_3210));

            x_4321 = _mem8_const(&x[i+j+1]);
            x_6543 = _dpacklh2(x_7654,x_5432);
            x_8765 = _dpacklh2(x_9876,x_7654);
            x_A987 = _mem8_const(&x[i+j+7]);
            x_CBA9 = _dpacklh2(x_DCBA,x_BA98);
            x_EDCB = _mem8_const(&x[i+j+11]);

            /* Create 128-bit quad register pairs */
            x_7654_3210 = _llto128(x_7654,x_3210);
            x_8765_4321 = _llto128(x_8765,x_4321);
            x_9876_5432 = _llto128(x_9876,x_5432);
            x_A987_6543 = _llto128(x_A987,x_6543); 
            x_BA98_7654 = _llto128(x_BA98,x_7654); 
            x_CBA9_8765 = _llto128(x_CBA9,x_8765); 
            x_DCBA_9876 = _llto128(x_DCBA,x_9876); 
            x_EDCB_A987 = _llto128(x_EDCB,x_A987); 

            /* Compute result 0 double dot product */
            ddot_0 = _ddotp4h(h_7654_3210,x_7654_3210);
            /* Compute result 1 double dot product */
            ddot_1 = _ddotp4h(h_7654_3210,x_8765_4321);
            /* Compute result 2 double dot product */
            ddot_2 = _ddotp4h(h_7654_3210,x_9876_5432);
            /* Compute result 3 double dot product */
            ddot_3 = _ddotp4h(h_7654_3210,x_A987_6543);
            /* Compute result 4 double dot product */
            ddot_4 = _ddotp4h(h_7654_3210,x_BA98_7654);
            /* Compute result 5 double dot product */
            ddot_5 = _ddotp4h(h_7654_3210,x_CBA9_8765);
            /* Compute result 6 double dot product */
            ddot_6 = _ddotp4h(h_7654_3210,x_DCBA_9876);
            /* Compute result 7 double dot product */
            ddot_7 = _ddotp4h(h_7654_3210,x_EDCB_A987);

            /* Sum 8 results */
            sum_0 = _dsadd(sum_0, ddot_0);
            sum_1 = _dsadd(sum_1, ddot_1);      
            sum_2 = _dsadd(sum_2, ddot_2);
            sum_3 = _dsadd(sum_3, ddot_3);
            sum_4 = _dsadd(sum_4, ddot_4);
            sum_5 = _dsadd(sum_5, ddot_5);      
            sum_6 = _dsadd(sum_6, ddot_6);
            sum_7 = _dsadd(sum_7, ddot_7);
        }
        
        /* Sum the high and low portions of each ddot_X register pair to
         * form each results complete sum.  Then shift down 15 to convert
         * to Q15 format. */
        sum_20 = _itoll(_hill(sum_2)+_loll(sum_2), _hill(sum_0)+_loll(sum_0));
        sum_20 = _dshr(sum_20, 15);
        sum_31 = _itoll(_hill(sum_3)+_loll(sum_3), _hill(sum_1)+_loll(sum_1));
        sum_31 = _dshr(sum_31, 15);
        sum_64 = _itoll(_hill(sum_6)+_loll(sum_6), _hill(sum_4)+_loll(sum_4));
        sum_64 = _dshr(sum_64, 15);
        sum_75 = _itoll(_hill(sum_7)+_loll(sum_7), _hill(sum_5)+_loll(sum_5));
        sum_75 = _dshr(sum_75, 15);

        /* Store out 8 output samples at a time using STDW */
        _amem8(&r[j])   = _dpackl2(sum_31, sum_20);
        _amem8(&r[j+4]) = _dpackl2(sum_75, sum_64);
    }
}

/*-----------------------------------------------------------*/
/*  Big Endian version                                       */
/*-----------------------------------------------------------*/
#else
void DSP_fir_r8_hM16_rM8A8X8 (
    const short *restrict x,    /* Input array [nr+nh-1 elements] */
    const short *restrict h,    /* Coeff array [nh elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nh,                     /* Number of coefficients         */
    int nr                      /* Number of output samples       */
)
{
    int i, j;
    long long h_0123, h_4567;
    long long x_0123, x_1234, x_2345, x_3456, x_4567, x_5678, x_6789;
    long long x_789A, x_89AB, x_9ABC, x_ABCD, x_BCDE, x_CDEF;
    long long ddot_0, ddot_1, ddot_2, ddot_3, ddot_4, ddot_5, ddot_6, ddot_7;
    long long sum_0, sum_1, sum_2, sum_3, sum_4, sum_5, sum_6, sum_7;
    long long sum_02, sum_13, sum_57, sum_46;

    __x128_t h_0123_4567;
    __x128_t x_0123_4567, x_2345_6789, x_1234_5678, x_3456_789A;
    __x128_t x_4567_89AB, x_5678_9ABC, x_6789_ABCD, x_789A_BCDE;

    /* Four results will be computed per loop iteration */
    _nassert(nh % 8 == 0);
    _nassert(nh >= 8);
    _nassert(nr % 8 == 0);
    _nassert(nr >= 8);
    for (j = 0; j < nr; j += 8) {
        /* Initialize the 8 result accumulators to zero */
        sum_0 = 0;
        sum_1 = 0;
        sum_2 = 0; 
        sum_3 = 0;
        sum_4 = 0;
        sum_5 = 0;
        sum_6 = 0;
        sum_7 = 0;

        /* Loop through the number of coefficients, 8 at a time 
         * summing all dot products together to form 8 results */
        for (i = 0; i < nh; i += 8)
        {
            /* Load the eleven elements of the data array using aligned
             * double word wide loads */
            x_CDEF = _amem8_const(&x[i + j + 12]);
            x_89AB = _amem8_const(&x[i + j + 8]);
            x_4567 = _amem8_const(&x[i + j + 4]);
            x_0123 = _amem8_const(&x[i + j]);

            /* Load the eight elements of the coefficient array using aligned
             * double word wide loads */
            h_4567 = _amem8_const(&h[i + 4]);
            h_0123 = _amem8_const(&h[i]);

            /* Form the coefficient 128-bit quad register pair */
            h_0123_4567 = _llto128(h_0123,h_4567);

            /* Form filter taps */
            x_ABCD = _dmv(_loll(x_89AB),_hill(x_CDEF));
            x_6789 = _dmv(_loll(x_4567),_hill(x_89AB));
            x_2345 = _dmv(_loll(x_0123),_hill(x_4567));

            x_1234 = _dpacklh2(x_0123,x_2345);
            x_3456 = _dpacklh2(x_2345,x_4567);
            x_5678 = _mem8_const(&x[i+j+5]);
            x_789A = _mem8_const(&x[i+j+7]);
            x_9ABC = _dpacklh2(x_89AB,x_ABCD);
            x_BCDE = _mem8_const(&x[i+j+11]);

            /* Create 128-bit quad register pairs */
            x_0123_4567 = _llto128(x_0123,x_4567);
            x_1234_5678 = _llto128(x_1234,x_5678);
            x_2345_6789 = _llto128(x_2345,x_6789);
            x_3456_789A = _llto128(x_3456,x_789A); 
            x_4567_89AB = _llto128(x_4567,x_89AB); 
            x_5678_9ABC = _llto128(x_5678,x_9ABC); 
            x_6789_ABCD = _llto128(x_6789,x_ABCD); 
            x_789A_BCDE = _llto128(x_789A,x_BCDE); 

            /* Compute result 0 double dot product */
            ddot_0 = _ddotp4h(h_0123_4567,x_0123_4567);
            /* Compute result 1 double dot product */
            ddot_1 = _ddotp4h(h_0123_4567,x_1234_5678);
            /* Compute result 2 double dot product */
            ddot_2 = _ddotp4h(h_0123_4567,x_2345_6789);
            /* Compute result 3 double dot product */
            ddot_3 = _ddotp4h(h_0123_4567,x_3456_789A);
            /* Compute result 4 double dot product */
            ddot_4 = _ddotp4h(h_0123_4567,x_4567_89AB);
            /* Compute result 5 double dot product */
            ddot_5 = _ddotp4h(h_0123_4567,x_5678_9ABC);
            /* Compute result 6 double dot product */
            ddot_6 = _ddotp4h(h_0123_4567,x_6789_ABCD);
            /* Compute result 7 double dot product */
            ddot_7 = _ddotp4h(h_0123_4567,x_789A_BCDE);

            /* Sum 8 results */
            sum_0 = _dsadd(sum_0, ddot_0);
            sum_1 = _dsadd(sum_1, ddot_1);      
            sum_2 = _dsadd(sum_2, ddot_2);
            sum_3 = _dsadd(sum_3, ddot_3);
            sum_4 = _dsadd(sum_4, ddot_4);
            sum_5 = _dsadd(sum_5, ddot_5);      
            sum_6 = _dsadd(sum_6, ddot_6);
            sum_7 = _dsadd(sum_7, ddot_7);
        }
        
        /* Sum the high and low portions of each ddot_X register pair to
         * form each results complete sum.  Then shift down 15 to convert
         * to Q15 format. */
        sum_02 = _itoll(_hill(sum_0)+_loll(sum_0), _hill(sum_2)+_loll(sum_2));
        sum_02 = _dshr(sum_02, 15);
        sum_13 = _itoll(_hill(sum_1)+_loll(sum_1), _hill(sum_3)+_loll(sum_3));
        sum_13 = _dshr(sum_13, 15);
        sum_46 = _itoll(_hill(sum_4)+_loll(sum_4), _hill(sum_6)+_loll(sum_6));
        sum_46 = _dshr(sum_46, 15);
        sum_57 = _itoll(_hill(sum_5)+_loll(sum_5), _hill(sum_7)+_loll(sum_7));
        sum_57 = _dshr(sum_57, 15);

        /* Store out 8 output samples at a time using STDW */
        _amem8(&r[j])   = _dpackl2(sum_02, sum_13);
        _amem8(&r[j+4]) = _dpackl2(sum_46, sum_57);
    }
}
#endif

/* ======================================================================= */
/*  End of file: DSP_fir_r8_hM16_rM8A8X8.c                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

