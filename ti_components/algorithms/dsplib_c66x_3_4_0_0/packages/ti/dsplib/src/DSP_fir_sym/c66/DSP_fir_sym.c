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
/* DSP_fir_sym.c -- Symmetric FIR Filter                                   */
/*                  Optimized C Implementation (w/ Intrinsics)             */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fir_sym (                                                  */
/*         const short *restrict x,                                        */
/*         const short *restrict h,                                        */
/*         short *restrict r,                                              */
/*         int nh,                                                         */
/*         int nr,                                                         */
/*         int s,                                                          */
/*     )                                                                   */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*     This function applies a symmetric filter to the input samples.      */
/*     The filter tap array h[] provides 'nh + 1' total filter taps.       */
/*     The filter tap at h[nh] forms the center point of the filter.       */
/*     The taps at h[nh - 1] through h[0] form a symmetric filter          */
/*     about this central tap.  The effective filter length is thus        */
/*     2*nh + 1 taps.                                                      */
/*                                                                         */
/*     The filter is performed on 16-bit data with 16-bit coefficients,    */
/*     accumulating intermediate results to 40-bit precision.  The         */
/*     accumulator is rounded and truncated according to the value         */
/*     provided in 's'.  This allows a variety of Q-points to be used.     */
/*                                                                         */
/*     Note that samples are added together before multiplication, and     */
/*     so overflow *may* result for large-scale values, despite the        */
/*     40-bit accumulation.                                                */
/*                                                                         */
/*  ASSUMPTIONS                                                            */
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

#pragma CODE_SECTION(DSP_fir_sym, ".text:optimized");

#include "DSP_fir_sym.h"

#ifdef _LITTLE_ENDIAN
void DSP_fir_sym (
    const short *restrict x,    /* Input samples                   */
    const short *restrict h,    /* Filter taps                     */
    short       *restrict r,    /* Output samples                  */
    int nh,                     /* Number of symmetric filter taps */
    int nr,                     /* Number of output samples        */
    int s                       /* Final output shift              */
)
{
    int i, j, round;
    int h_00, h_10;
    int xf_76, xf_54, xf_32, xf_10, xf_12, xf_56, xf_70;

    int y_0, y_1, y_2, y_3;

    long long h_3210;
    long long x_3210, x_4321, x_5432, x_6543, x_7654;
    long long xf_3210, xf_7654;
    long long sum_0, sum_1, sum_2, sum_3;
    long long y_20, y_31;
    long long prod_f10, prod_f32;

    round = 1 << (s - 1);

    /* Preload center coefficent */
    h_10 = _amem4_const(&h[nh]);
    h_00 = _pack2(h_10, h_10);

    /* Inform the compiler that the number of filter taps is greater
     * than 0, and a multiple of four. In addition inform the compiler 
     * that the number of output samples is greater than zero and
     * a multiple of 4. */
    _nassert((nh > 0) && (nh % 4 == 0));
    _nassert((nr > 0) && (nr % 4 == 0));
    for (j = 0; j < nr; j += 4) {
        /* Initialize the four accumulators to the round value before 
         * the start of the FIR computation. */
        y_0 = round;
        y_1 = round;
        y_2 = round;
        y_3 = round;

        /* The inner loop processes eight filter taps in parallel for
         * four output samples. */
        for (i = 0; i < nh; i += 4) {
            /* Load eight input data samples from both ends as filter 
             * coefficients are being shared. */
            x_3210 = _amem8_const(&x[j + i]);
            x_7654 = _amem8_const(&x[j + i + 4]);

            xf_3210 = _amem8_const(&x[2*nh + j - i]);
            xf_7654 = _amem8_const(&x[2*nh + j - i - 4]);

            /* Load four filter taps */
            h_3210 = _amem8_const(&h[i]);

            /* Extract low and high halves at end of filter to reverse order
             * of inputs for summation with inputs from the beginning end */
            xf_10 = _loll(xf_3210);
            xf_32 = _hill(xf_3210);
            xf_54 = _loll(xf_7654);
            xf_76 = _hill(xf_7654);

            xf_12 = _packhl2(xf_10, xf_32);
            xf_56 = _packhl2(xf_54, xf_76);
            xf_70 = _packhl2(xf_76, xf_10);
            
            /* Load output 1 inputs to balance load unit and logical
             * operation units */ 
            x_4321 = _mem8_const(&x[i+j+1]);
            /* Form output 2 inputs */
            x_5432 = _dmv(_loll(x_7654),_hill(x_3210));
            /* Load output 3 inputs to balance load unit and logical
             * operation units */ 
            x_6543 = _mem8_const(&x[i+j+3]);
             
            /* Since filter coefficients are going to be re-used,  
             * the multiplies are saved by performing add's using   
             * the dadd instruction. */
             
            /* Create sum for output 0: x_3210 + xf_5670 */
            sum_0 = _dadd2(x_3210,_dmv(xf_56,xf_70));
            /* Create sum for output 1: x_4321 + xf_6701 */
            sum_1 = _dadd2(x_4321,_dmv(_rotl(xf_76,16),_rotl(xf_10,16)));
            /* Create sum for output 2: x_5432 + xf_7012 */
            sum_2 = _dadd2(x_5432,_dmv(xf_70,xf_12));
            /* Create sum for output 3: x_6543 + xf_0123 */
            sum_3 = _dadd2(x_6543,_dmv(_rotl(xf_10,16),_rotl(xf_32,16)));            

            /* The partial products are multiplied and accumulated 
             * using dotp4h instructions.                          
             * The four partial accumulated sums for each output    
             * sample are then accumulated with the main accumulator
             * y_0..y_3 */
            y_0 += _dotp4h(sum_0, h_3210);
            y_1 += _dotp4h(sum_1, h_3210);
            y_2 += _dotp4h(sum_2, h_3210);
            y_3 += _dotp4h(sum_3, h_3210);
        }

        /* Perform four multiplies required for the four output sam-  
         * ples with this coefficient. Extract individual results   
         * using _loll and _hill. Add these last results to the accumu-  
         * mulator. */           
        prod_f10 = _mpy2ll(_loll(x_7654), h_00);
        prod_f32 = _mpy2ll(_hill(x_7654), h_00);
        
        /* Form y_20, y_31 to allow for double shift and store */
        y_20 = _dmv(y_2,y_0);
        y_31 = _dmv(y_3,y_1);
        y_20 = _dsadd(y_20,_dmv(_loll(prod_f32),_loll(prod_f10)));
        y_31 = _dsadd(y_31,_dmv(_hill(prod_f32),_hill(prod_f10)));

        /* Perform 's' bit shifts and pack the resulting quantities.
         * The pack instruction accepts 32 bit quantities, and hence  
         * the shifted quantities are cast as int's. The packed   
         * quantities are stored out as a double word. */
        y_20 = _dshr(y_20, s);
        y_31 = _dshr(y_31, s);

        /* Store four output samples at a time using STDW */
        _amem8(&r[j]) = _dpackl2(y_31, y_20);
    }
}

/*-----------------------------------------------------------*/
/*  Big Endian version                                       */
/*-----------------------------------------------------------*/
#else
void DSP_fir_sym (
    const short *restrict x,    /* Input samples                   */
    const short *restrict h,    /* Filter taps                     */
    short       *restrict r,    /* Output samples                  */
    int nh,                     /* Number of symmetric filter taps */
    int nr,                     /* Number of output samples        */
    int s                       /* Final output shift              */
)
{
    int i, j, round;
    int h_00, h_01;
    int xf_67, xf_45, xf_23, xf_01, xf_21, xf_65, xf_07;

    int y_0, y_1, y_2, y_3;

    long long h_0123;
    long long x_0123, x_1234, x_2345, x_3456, x_4567;
    long long xf_0123, xf_4567;
    long long sum_0, sum_1, sum_2, sum_3;
    long long y_02, y_13;
    long long prod_f01, prod_f23;

    round = 1 << (s - 1);

    /* Preload center coefficent */
    h_01 = _amem4_const(&h[nh]);
    h_00 = _packh2(h_01, h_01);

    /* Inform the compiler that the number of filter taps is greater
     * than 0, and a multiple of four. In addition inform the compiler 
     * that the number of output samples is greater than zero and
     * a multiple of 4. */
    _nassert((nh > 0) && (nh % 4 == 0));
    _nassert((nr > 0) && (nr % 4 == 0));
    for (j = 0; j < nr; j += 4) {
        /* Initialize the four accumulators to the round value before 
         * the start of the FIR computation. */
        y_0 = round;
        y_1 = round;
        y_2 = round;
        y_3 = round;

        /* The inner loop processes eight filter taps in parallel for
         * four output samples. */
        for (i = 0; i < nh; i += 4) {
            /* Load eight input data samples from both ends as filter 
             * coefficients are being shared. */
            x_0123 = _amem8_const(&x[j + i]);
            x_4567 = _amem8_const(&x[j + i + 4]);

            xf_0123 = _amem8_const(&x[2*nh + j - i]);
            xf_4567 = _amem8_const(&x[2*nh + j - i - 4]);

            /* Load four filter taps */
            h_0123 = _amem8_const(&h[i]);

            /* Extract low and high halves at end of filter to reverse order
             * of inputs for summation with inputs from the beginning end */
            xf_01 = _hill(xf_0123);
            xf_23 = _loll(xf_0123);
            xf_45 = _hill(xf_4567);
            xf_67 = _loll(xf_4567);

            xf_21 = _packhl2(xf_23, xf_01);
            xf_65 = _packhl2(xf_67, xf_45);
            xf_07 = _packhl2(xf_01, xf_67);
            
            /* Load output 1 inputs to balance load unit and logical
             * operation units */ 
            x_1234 = _mem8_const(&x[i+j+1]);
            /* Form output 2 inputs */
            x_2345 = _dmv(_loll(x_0123),_hill(x_4567));
            /* Load output 3 inputs to balance load unit and logical
             * operation units */ 
            x_3456 = _mem8_const(&x[i+j+3]);
             
            /* Since filter coefficients are going to be re-used,  
             * the multiplies are saved by performing add's using   
             * the dadd instruction. */
             
            /* Create sum for output 0: x_0123 + xf_0765 */
            sum_0 = _dadd2(x_0123,_dmv(xf_07,xf_65));
            /* Create sum for output 1: x_1234 + xf_1076 */
            sum_1 = _dadd2(x_1234,_dmv(_rotl(xf_01,16),_rotl(xf_67,16)));
            /* Create sum for output 2: x_2345 + xf_2107 */
            sum_2 = _dadd2(x_2345,_dmv(xf_21,xf_07));
            /* Create sum for output 3: x_3456 + xf_3210 */
            sum_3 = _dadd2(x_3456,_dmv(_rotl(xf_23,16),_rotl(xf_01,16)));            

            /* The partial products are multiplied and accumulated 
             * using dotp4h instructions.                          
             * The four partial accumulated sums for each output    
             * sample are then accumulated with the main accumulator
             * y_0..y_3 */
            y_0 += _dotp4h(sum_0, h_0123);
            y_1 += _dotp4h(sum_1, h_0123);
            y_2 += _dotp4h(sum_2, h_0123);
            y_3 += _dotp4h(sum_3, h_0123);
        }

        /* Perform four multiplies required for the four output sam-  
         * ples with this coefficient. Extract individual results   
         * using _loll and _hill. Add these last results to the accumu-  
         * mulator. */           
        prod_f01 = _mpy2ll(_hill(x_4567), h_00);
        prod_f23 = _mpy2ll(_loll(x_4567), h_00);
        
        /* Form y_02, y_13 to allow for double shift and store */
        y_02 = _dmv(y_0,y_2);
        y_13 = _dmv(y_1,y_3);
        y_02 = _dsadd(y_02,_dmv(_hill(prod_f01),_hill(prod_f23)));
        y_13 = _dsadd(y_13,_dmv(_loll(prod_f01),_loll(prod_f23)));

        /* Perform 's' bit shifts and pack the resulting quantities.
         * The pack instruction accepts 32 bit quantities, and hence  
         * the shifted quantities are cast as int's. The packed   
         * quantities are stored out as a double word. */
        y_02 = _dshr(y_02, s);
        y_13 = _dshr(y_13, s);

        /* Store four output samples at a time using STDW */
        _amem8(&r[j]) = _dpackl2(y_02, y_13);
    }
}
#endif

/* ======================================================================= */
/*  End of file:  DSP_fir_sym.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

