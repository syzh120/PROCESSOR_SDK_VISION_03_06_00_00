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
/*  NAME                                                                   */
/*      DSP_fft16x32 -- Radix-4 FFT with digit reversal                    */
/*                                                                         */
/*                                                                         */
/*  USAGE                                                                  */
/*                                                                         */
/*      This routine is C-callable and can be called as:                   */
/*                                                                         */
/*      void DSP_fft16x32                                                  */
/*      (                                                                  */
/*          short * w,                                                     */
/*          int nx,                                                        */
/*          int * x,                                                       */
/*          int * y                                                        */
/*      )                                                                  */
/*                                                                         */
/*      w[2*nx]:    Pointer to vector of Q.15 FFT coefficients of size     */
/*                  2*nx elements.                                         */
/*                                                                         */
/*      nx:         Number of complex elements in vector x.                */
/*                                                                         */
/*      x[2*nx]:    Pointer to input vector of size 2*nx elements.         */
/*                                                                         */
/*      y[2*nx]:    Pointer to output vector of size 2*nx elements.        */
/*                                                                         */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*                                                                         */
/*      This code performs a Radix-4 FFT with digit reversal.  The code    */
/*      uses a special ordering of twiddle factors and memory accesses     */
/*      to improve performance in the presence of cache.  It operates      */
/*      largely in-place, but the final digit-reversed output is written   */
/*      out-of-place.                                                      */
/*                                                                         */
/*      This code requires a special sequence of twiddle factors stored    */
/*      in Q1.15 fixed-point format.  The following C code illustrates     */
/*      one way to generate the desired twiddle-factor array:              */
/*                                                                         */
/*      #include <math.h>                                                  */
/*                                                                         */
/*                                                                         */
/*      short d2s(double d)                                                */
/*      {                                                                  */
/*         d = floor(0.5 + d);  // Explicit rounding to integer //         */
/*         if (d >=  32767.0) return  32767;                               */
/*         if (d <= -32768.0) return -32768;                               */
/*         return (short)d;                                                */
/*      }                                                                  */
/*                                                                         */
/*       void gen_twiddle_fft_c(short *w, int n)                           */
/*      {                                                                  */
/*         double M = 32767.5;                                             */
/*         const double PI = 3.141592654;                                  */
/*         int i, j, k;                                                    */
/*                                                                         */
/*         for (j = 1, k = 0; j < n >> 2; j = j << 2)                      */
/*         {                                                               */
/*            for (i = 0; i < n >> 2; i += j << 1)                         */
/*            {                                                            */
/*                                                                         */
/*              w[k +  3] = d2s(M * cos(2.0 * PI * (i + j) / n));          */
/*              w[k +  2] = d2s(M * sin(2.0 * PI * (i + j) / n));          */
/*              w[k +  1] = d2s(M * cos(2.0 * PI * (i    ) / n));          */
/*              w[k +  0] = d2s(M * sin(2.0 * PI * (i    ) / n));          */
/*                                                                         */
/*              k += 4;                                                    */
/*            }                                                            */
/*           }                                                             */
/*      }                                                                  */
/*                                                                         */
/*                                                                         */
/*  TECHNIQUES                                                             */
/*                                                                         */
/*      The following C code represents an implementation of the Cooley    */
/*      Tukey radix 4 DIF FFT. It accepts the inputs in normal order and   */
/*      produces the outputs in digit reversed order. The natural C code   */
/*      shown in this file on the other hand, accepts the inputs in nor-   */
/*      mal order and produces the outputs in normal order.                */
/*                                                                         */
/*  ASSUMPTIONS                                                            */
/*                                                                         */
/*      The size of the FFT, n, must be a power of 4 and greater than      */
/*      or equal to 16 and less than 32768.                                */
/*                                                                         */
/*      The arrays 'x[]', 'y[]', and 'w[]' all must be aligned on a        */
/*      double-word boundary for the "optimized" implementations.          */
/*                                                                         */
/*      The input and output data are complex, with the real/imaginary     */
/*      components stored in adjacent locations in the array.  The real    */
/*      components are stored at even array indices, and the imaginary     */
/*      components are stored at odd array indices.                        */
/*                                                                         */
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

#pragma CODE_SECTION(DSP_fft16x32, ".text:optimized");

#include "DSP_fft16x32.h"

static inline void radix_2(int *restrict ptr_x, int *restrict ptr_y, int npoints);
static inline void radix_4(int *restrict ptr_x, int *restrict ptr_y, int npoints);

#ifdef _LITTLE_ENDIAN
void DSP_fft16x32 (
    const short * restrict ptr_w,
    int npoints,
    int * restrict ptr_x,
    int * restrict ptr_y
)
{
    const short * restrict w;
    int * restrict x, * restrict x2;
    int i, j, l1, l2, h2, predj, tw_offset, stride, fft_jmp, tw_jmp, radix;
    int xt1_0, yt2_0, xt1_1, yt2_1, xt2_0, yt1_0, xt2_1, yt1_1;

    long long xh21_0_xh20_0, xh21_1_xh20_1, xh1_0_xh0_0, xh1_1_xh0_1; 
    long long xl21_0_xl20_0, xl21_1_xl20_1, xl1_0_xl0_0, xl1_1_xl0_1; 
    long long yt0_0_xt0_0,   yt0_1_xt0_1,   yt1_0_xt1_0;
    long long yt1_1_xt1_1,   yt2_0_xt2_0,   yt2_1_xt2_1; 
    long long x_1o_x_0o,     xl1_1o_xl1_0o, x_3o_x_2o,     xl1_3o_xl1_2o; 
    long long xh2_1o_xh2_0o, xl2_1o_xl2_0o, xh2_3o_xh2_2o, xl2_3o_xl2_2o;  
 
    long long x_10, x_32, x_l1_10, x_l1_32, x_l2_10, x_l2_32, x_h2_10,x_h2_32;
    long long co11si11_co10si10;
    long long co10_si10, co20_si20, co30_si30, co11_si11, co21_si21, co31_si31;

    /*---------------------------------------------------------------------*/
    /* Determine the magnitude od the number of points to be transformed.  */
    /* Check whether we can use a radix4 decomposition or a mixed radix    */
    /* transformation, by determining modulo 2.                            */
    /*---------------------------------------------------------------------*/
    radix = _norm(npoints) & 1 ? 2 : 4;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 2*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/ 
    stride = npoints;
    tw_offset = 0;
    fft_jmp = 6 * stride;
    tw_jmp  = 2 * stride;

    _nassert(stride > 4);
    #pragma MUST_ITERATE(1,,1);
    while (stride > 4) {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 2 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          2 N/4               1               */
        /*  2                          2 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/  
        j =  0;
        fft_jmp >>= 2;
        tw_jmp  >>= 2;

        /*-----------------------------------------------------------------*/
        /* Set up offsets to access "N/4", "N/2", "3N/4" complex point or  */
        /* "N/2", "N", "3N/2" half word                                    */
        /*-----------------------------------------------------------------*/ 
        h2 = stride >> 1;
        l1 = stride;
        l2 = stride + (stride >> 1);

        /*-----------------------------------------------------------------*/
        /*  Reset "x" to point to the start of the input data array.       */
        /* "tw_offset" starts off at 0, and increments by "6 * stride"     */
        /*  The stride quarters with every iteration of the outer loop     */
        /*-----------------------------------------------------------------*/
        x = ptr_x;
        w = (short *)ptr_w + tw_offset;
        tw_offset += tw_jmp;

        stride >>= 2;

        /*----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies, */
        /* within a given stage. Recall that there are logN to base 4     */
        /* stages. Certain butterflies share the twiddle factors. These   */
        /* are grouped together. On the very first stage there are no     */
        /* butterflies that share the twiddle factor, all N/4 butter-     */
        /* flies have different factors. On the next stage two sets of    */
        /* N/8 butterflies share the same twiddle factor. Hence after     */
        /* half the butterflies are performed, j the index into the       */
        /* factor array resets to 0, and the twiddle factors are reused.  */
        /* When this happens, the data pointer 'x' is incremented by the  */
        /* fft_jmp amount.                                                */
        /*----------------------------------------------------------------*/
        _nassert((int)(w) % 8 == 0);
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        _nassert(npoints >= 16);
        #pragma MUST_ITERATE(2,,2);
        for (i = 0; i < (npoints >> 3); i++) {
            /*------------------------------------------------------------*/
            /*  Read the first four twiddle factor values. This loop      */
            /*  computes two radix 4 butterflies at a time.               */
            /* si10 = w[0] co10 = w[1]  si11 = w[2]  co11 = w[3]          */
            /*------------------------------------------------------------*/
            co11si11_co10si10 = _amem8_const(&w[j]);
            co10_si10 = _dshl(_unpkh2(_loll(co11si11_co10si10)),16);
            co11_si11 = _dshl(_unpkh2(_hill(co11si11_co10si10)),16);
            co20_si20 = _cmpy32r1(co10_si10, co10_si10);
            co30_si30 = _cmpy32r1(co20_si20, co10_si10);
            co21_si21 = _cmpy32r1(co11_si11, co11_si11);
            co31_si31 = _cmpy32r1(co21_si21, co11_si11);

            /*-------------------------------------------------------------*/
            /* Read in the data elements for the eight inputs of two       */
            /* radix4 butterflies.                                         */
            /*  x[0]       x[1]       x[2]       x[3]                      */
            /*  x[h2+0]    x[h2+1]    x[h2+2]    x[h2+3]                   */
            /*  x[l1+0]    x[l1+1]    x[l1+2]    x[l1+3]                   */
            /*  x[l2+0]    x[l2+1]    x[l2+2]    x[l2+3]                   */
            /*-------------------------------------------------------------*/
            x_10    = _amem8(&x[0]);
            x_32    = _amem8(&x[2]);
            x_l1_10 = _amem8(&x[l1]);
            x_l1_32 = _amem8(&x[l1 + 2]);
            x_l2_10 = _amem8(&x[l2]);
            x_l2_32 = _amem8(&x[l2 + 2]);
            x_h2_10 = _amem8(&x[h2]);
            x_h2_32 = _amem8(&x[h2 + 2]);

            /*-------------------------------------------------------------*/
            /* xh0_0 = x[0] + x[l1];    xh1_0 = x[1] + x[l1+1]             */
            /* xh0_1 = x[2] + x[l1+2];  xh1_1 = x[3] + x[l1+3]             */
            /* xl0_0 = x[0] - x[l1];    xl1_0 = x[1] - x[l1+1]             */
            /* xl0_1 = x[2] - x[l1+2];  xl1_1 = x[3] - x[l1+3]             */
            /*-------------------------------------------------------------*/
            xh1_0_xh0_0 = _dadd(x_10, x_l1_10);
            xl1_0_xl0_0 = _dsub(x_10, x_l1_10);
            xh1_1_xh0_1 = _dadd(x_32, x_l1_32);
            xl1_1_xl0_1 = _dsub(x_32, x_l1_32);

            /*------------------------------------------------------------*/
            /* xh20_0 = x[h2  ] + x[l2  ]; xh21_0 = x[h2+1] + x[l2+1]     */
            /* xh20_1 = x[h2+2] + x[l2+2]; xh21_1 = x[h2+3] + x[l2+3]     */
            /* xl20_0 = x[h2  ] - x[l2  ]; xl21_0 = x[h2+1] - x[l2+1]     */
            /* xl20_1 = x[h2+2] - x[l2+2]; xl21_1 = x[h2+3] - x[l2+3]     */
            /*------------------------------------------------------------*/
            xh21_0_xh20_0 = _dadd(x_h2_10, x_l2_10);
            xl21_0_xl20_0 = _dsub(x_h2_10, x_l2_10);
            xh21_1_xh20_1 = _dadd(x_h2_32, x_l2_32);
            xl21_1_xl20_1 = _dsub(x_h2_32, x_l2_32);

            /*-------------------------------------------------------------*/
            /*    x_0o  = xh0_0 + xh20_0;    x_1o  = xh1_0 + xh21_0;       */
            /*    x_2o  = xh0_1 + xh20_1;    x_3o  = xh1_1 + xh21_1;       */
            /*    xt0_0 = xh0_0 - xh20_0;    yt0_0 = xh1_0 - xh21_0;       */
            /*    xt0_1 = xh0_1 - xh20_1;    yt0_1 = xh1_1 - xh21_1;       */
            /*-------------------------------------------------------------*/
            x_1o_x_0o = _dadd(xh1_0_xh0_0, xh21_0_xh20_0);
            x_3o_x_2o = _dadd(xh1_1_xh0_1, xh21_1_xh20_1);

            yt0_0_xt0_0 = _dsub(xh1_0_xh0_0, xh21_0_xh20_0);
            yt0_1_xt0_1 = _dsub(xh1_1_xh0_1, xh21_1_xh20_1);

            /*-------------------------------------------------------------*/
            /*    xt1_0 = xl0_0 + xl21_0;    yt2_0 = xl1_0 + xl20_0;       */
            /*    xt1_1 = xl0_1 + xl21_1;    yt2_1 = xl1_1 + xl20_1;       */
            /*    xt2_0 = xl0_0 - xl21_0;    yt1_0 = xl1_0 - xl20_0;       */
            /*    xt2_1 = xl0_1 - xl21_1;    yt1_1 = xl1_1 - xl20_1;       */
            /*-------------------------------------------------------------*/
            xt1_0 = _loll(xl1_0_xl0_0) + _hill(xl21_0_xl20_0);
            yt2_0 = _hill(xl1_0_xl0_0) + _loll(xl21_0_xl20_0);
            xt1_1 = _loll(xl1_1_xl0_1) + _hill(xl21_1_xl20_1);
            yt2_1 = _hill(xl1_1_xl0_1) + _loll(xl21_1_xl20_1);

            xt2_0 = _loll(xl1_0_xl0_0) - _hill(xl21_0_xl20_0);
            yt1_0 = _hill(xl1_0_xl0_0) - _loll(xl21_0_xl20_0);
            xt2_1 = _loll(xl1_1_xl0_1) - _hill(xl21_1_xl20_1);
            yt1_1 = _hill(xl1_1_xl0_1) - _loll(xl21_1_xl20_1);

            yt1_0_xt1_0 = _itoll(yt1_0, xt1_0);
            yt1_1_xt1_1 = _itoll(yt1_1, xt1_1);

            yt2_0_xt2_0 = _itoll(yt2_0, xt2_0);
            yt2_1_xt2_1 = _itoll(yt2_1, xt2_1);

            /*-------------------------------------------------------------*/
            /*   x2[h2  ] = (si10 * yt1_0 + co10 * xt1_0) >> 15            */
            /*   x2[h2+1] = (co10 * yt1_0 - si10 * xt1_0) >> 15            */
            /*   x2[h2+2] = (si11 * yt1_1 + co11 * xt1_1) >> 15            */
            /*   x2[h2+3] = (co11 * yt1_1 - si11 * xt1_1) >> 15            */
            /*-------------------------------------------------------------*/
            xh2_1o_xh2_0o = _cmpy32r1(co10_si10, yt1_0_xt1_0);
            xh2_3o_xh2_2o = _cmpy32r1(co11_si11, yt1_1_xt1_1);

            /*-------------------------------------------------------------*/
            /*   x2[l1  ] = (si20 * yt0_0 + co20 * xt0_0) >> 15            */
            /*   x2[l1+1] = (co20 * yt0_0 - si20 * xt0_0) >> 15            */
            /*   x2[l1+2] = (si21 * yt0_1 + co21 * xt0_1) >> 15            */
            /*   x2[l1+3] = (co21 * yt0_1 - si21 * xt0_1) >> 15            */
            /*-------------------------------------------------------------*/
            xl1_1o_xl1_0o = _cmpy32r1(co20_si20, yt0_0_xt0_0);
            xl1_3o_xl1_2o = _cmpy32r1(co21_si21, yt0_1_xt0_1);

            /*-------------------------------------------------------------*/
            /*   x2[l2  ] = (si30 * yt2_0 + co30 * xt2_0) >> 15            */
            /*   x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0) >> 15            */
            /*   x2[l2+2] = (si31 * yt2_1 + co31 * xt2_1) >> 15            */
            /*   x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1) >> 15            */
            /*-------------------------------------------------------------*/
            xl2_1o_xl2_0o = _cmpy32r1(co30_si30, yt2_0_xt2_0);
            xl2_3o_xl2_2o = _cmpy32r1(co31_si31, yt2_1_xt2_1);

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x2 = x;

            /*-------------------------------------------------------------*/
            /*  Store eight outputs - four legs of each butterfly          */
            /*-------------------------------------------------------------*/
            _amem8(&x2[0])    = x_1o_x_0o;
            _amem8(&x2[2])    = x_3o_x_2o;

            _amem8(&x2[h2])   = xh2_1o_xh2_0o;
            _amem8(&x2[h2+2]) = xh2_3o_xh2_2o;

            _amem8(&x2[l1])   = xl1_1o_xl1_0o;
            _amem8(&x2[l1+2]) = xl1_3o_xl1_2o;

            _amem8(&x2[l2])   = xl2_1o_xl2_0o;
            _amem8(&x2[l2+2]) = xl2_3o_xl2_2o;

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 4, to reflect the fact that 2 words        */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            j += 4;
            x += 4;
            predj = (3*j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;
        }
    }

    if (radix == 2)
        radix_2(ptr_x, ptr_y, npoints);
    else
        radix_4(ptr_x, ptr_y, npoints);

}

void radix_2 (
    int * restrict ptr_x,
    int * restrict ptr_y,
    int npoints
)
{
    int * restrict x0, * restrict x2;
    int * restrict y0, * restrict y1, * restrict y2, * restrict y3;
    int * restrict yb0, * restrict yb1, * restrict yb2, * restrict yb3;
    int n0, j, i, h2, l1;
    long long n01_n00, n11_n10, n21_n20, n31_n30;
    long long n03_n02, n13_n12, n23_n22, n33_n32;

    long long x10, x32, x54, x76, x98, xBA, xDC, xFE;

    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix4 pass or a  */
    /* radix2 pass. Two pointers are used to access the input data.    */
    /* The input data is read "N/4" complex samples apart or "N/2"     */
    /* words apart using pointers "x0" and "x2". This produces out-    */
    /* puts that are 0, N/8, N/2, 3N/8 for radix 2.                    */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + (int)npoints;
    x0 = ptr_x;
    x2 = ptr_x + (int)(npoints >> 1);

    /*----------------------------------------------------------------*/
    /* The pointers are set at the following locations which are half */
    /* the offsets of a radix4 FFT.                                   */
    /*----------------------------------------------------------------*/
    y1 = y0 + (int)(npoints >> 2);
    y3 = y2 + (int)(npoints >> 2);
    l1 = _norm(npoints) + 1;
    n0 = npoints >> 1;

    yb0 = y0 + 2;
    yb1 = y1 + 2;
    yb2 = y2 + 2;
    yb3 = y3 + 2;

    /*--------------------------------------------------------------------*/
    /* The following code reads data identically for either a radix 4     */
    /* or a radix 2 style decomposition. It writes out at different       */
    /* locations though. It checks if either half the points, or a        */
    /* quarter of the complex points have been exhausted to jump to       */
    /* pervent double reversal.                                           */
    /*--------------------------------------------------------------------*/
    j = 0;

    _nassert((int)(npoints) % 4  == 0);
    _nassert((int)(ptr_x) % 8 == 0);
    _nassert((int)(ptr_y) % 8 == 0);
    _nassert((int)(x0) % 8 == 0);
    _nassert((int)(x2) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    #pragma MUST_ITERATE(2,,2);
    for (i = 0; i < npoints; i += 8) {
        /*----------------------------------------------------------------*/
        /* Digit reverse the index starting from 0. The increment to "j"  */
        /* is either by 4, or 8.                                          */
        /*----------------------------------------------------------------*/
        h2 = _deal(j);
        h2 = _bitr(h2);
        h2 = _rotl(h2, 16);
        h2 = _shfl(h2);
        h2 >>= l1;

        /*----------------------------------------------------------------*/
        /* Read in the input data. These are transformed as a radix 2.    */
        /*----------------------------------------------------------------*/
        x10 = _amem8(&x0[0]);
        x32 = _amem8(&x0[2]);
        x54 = _amem8(&x0[4]);
        x76 = _amem8(&x0[6]);
        x0 += 8;

        x98 = _amem8(&x2[0]);
        xBA = _amem8(&x2[2]);
        xDC = _amem8(&x2[4]);
        xFE = _amem8(&x2[6]);
        x2 += 8;

        /*-------------------------------------------------------------*/
        /* Perform radix2 style decomposition.                         */
        /*-------------------------------------------------------------*/
        n01_n00 = _dadd(x10, x32);
        n21_n20 = _dsub(x10, x32);
        n11_n10 = _dadd(x54, x76);
        n31_n30 = _dsub(x54, x76);

        n03_n02 = _dadd(x98, xBA);
        n23_n22 = _dsub(x98, xBA);
        n13_n12 = _dadd(xDC, xFE);
        n33_n32 = _dsub(xDC, xFE);

        /*-----------------------------------------------------------------*/
        /* Points that are read from succesive locations map to y, y[N/8]  */
        /* y[N/2],y[5N/8] in a radix2 scheme.                              */
        /*-----------------------------------------------------------------*/
        _amem8(&y0[2*h2])  = n01_n00;
        _amem8(&y1[2*h2])  = n11_n10;
        _amem8(&y2[2*h2])  = n21_n20;
        _amem8(&y3[2*h2])  = n31_n30;

        _amem8(&yb0[2*h2]) = n03_n02;
        _amem8(&yb1[2*h2]) = n13_n12;
        _amem8(&yb2[2*h2]) = n23_n22;
        _amem8(&yb3[2*h2]) = n33_n32;

        j += 8;
        if (j == n0) {
            j  += n0;
            x0 += (int)npoints >> 1;
            x2 += (int)npoints >> 1;
        }
    }
}

void radix_4 (
    int * restrict ptr_x,
    int * restrict ptr_y,
    int npoints
)
{
    int * restrict x0, * restrict x2;
    int * restrict y0, * restrict y1, * restrict y2, * restrict y3;
    int * restrict yb0, * restrict yb1, * restrict yb2, * restrict yb3;
    int n0, j, i, h2, l1;
    int n11, n10, n31, n30;

    long long x10, x32, x54, x76, x98, xba, xdc, xfe;
    long long xh1_0_xh0_0, xh1_1_xh0_1, xl1_0_xl0_0, xl1_1_xl0_1;
    long long n01_n00, n21_n20;
                              
    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix2 pass. Two  */
    /* pointers are used to access the input data. The input data is   */
    /* read "N/4" complex samples apart or "N/2" words apart using     */
    /* pointers "x0" and "x2". This produces outputs that are 0, N/4,  */
    /* N/2, 3N/4 for a radix4 FFT.                                     */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + (int)npoints;
    x0 = ptr_x;
    x2 = ptr_x + (int)(npoints >> 1);

    /*----------------------------------------------------------------*/
    /* The pointers are set at the following locations                */
    /*----------------------------------------------------------------*/
    y1 = y0 + (int)(npoints >> 1);
    y3 = y2 + (int)(npoints >> 1);
    l1 = _norm(npoints) + 2;
    n0 = npoints >> 2;

    yb0 = y0 + 2;
    yb1 = y1 + 2;
    yb2 = y2 + 2;
    yb3 = y3 + 2;
   
    /*--------------------------------------------------------------------*/
    /* The following code reads data identically for either a radix 4     */
    /* or a radix 2 style decomposition. It writes out at different       */
    /* locations though. It checks if either half the points, or a        */
    /* quarter of the complex points have been exhausted to jump to       */
    /* pervent double reversal.                                           */
    /*--------------------------------------------------------------------*/
    j = 0;
    
    _nassert((int)(npoints) % 4  == 0);
    _nassert((int)(x0) % 8 == 0);
    _nassert((int)(x2) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    _nassert(npoints >= 16);
    #pragma MUST_ITERATE(2,,2);
    for (i = 0; i < npoints; i += 8) {
        /*----------------------------------------------------------------*/
        /* Digit reverse the index starting from 0. The increment to "j"  */
        /* is either by 4, or 8.                                          */
        /*----------------------------------------------------------------*/
        h2 = _deal(j);
        h2 = _bitr(h2);
        h2 = _rotl(h2, 16);
        h2 = _shfl(h2);
        h2 >>= l1;

        /*----------------------------------------------------------------*/
        /* Read in the input data, from the first eight locations. These  */
        /* are transformed as a radix4.                                   */
        /*----------------------------------------------------------------*/
        x10 = _amem8(&x0[0]);
        x32 = _amem8(&x0[2]);
        x54 = _amem8(&x0[4]);
        x76 = _amem8(&x0[6]);
        x0 += 8;

        xh1_0_xh0_0 = _dadd(x10, x54);
        xh1_1_xh0_1 = _dadd(x32, x76);
        xl1_0_xl0_0 = _dsub(x10, x54);
        xl1_1_xl0_1 = _dsub(x32, x76);

        n01_n00 = _dadd(xh1_0_xh0_0, xh1_1_xh0_1);
        n21_n20 = _dsub(xh1_0_xh0_0, xh1_1_xh0_1);
        n11 = _hill(xl1_0_xl0_0) - _loll(xl1_1_xl0_1);
        n10 = _loll(xl1_0_xl0_0) + _hill(xl1_1_xl0_1);
        n31 = _hill(xl1_0_xl0_0) + _loll(xl1_1_xl0_1);
        n30 = _loll(xl1_0_xl0_0) - _hill(xl1_1_xl0_1);

        _amem8(&y0[2*h2]) = n01_n00;
        _amem8(&y1[2*h2]) = _itoll(n11, n10);
        _amem8(&y2[2*h2]) = n21_n20;
        _amem8(&y3[2*h2]) = _itoll(n31, n30);

        /*----------------------------------------------------------------*/
        /* Read in the next eight inputs and perform radix4 decomposition */
        /*----------------------------------------------------------------*/
        x98 = _amem8(&x2[0]);
        xba = _amem8(&x2[2]);
        xdc = _amem8(&x2[4]);
        xfe = _amem8(&x2[6]);
        x2 += 8;

        xh1_0_xh0_0 = _dadd(x98, xdc);
        xh1_1_xh0_1 = _dadd(xba, xfe);
        xl1_0_xl0_0 = _dsub(x98, xdc);
        xl1_1_xl0_1 = _dsub(xba, xfe);

        n01_n00 = _dadd(xh1_0_xh0_0, xh1_1_xh0_1);
        n21_n20 = _dsub(xh1_0_xh0_0, xh1_1_xh0_1);
        n11 = _hill(xl1_0_xl0_0) - _loll(xl1_1_xl0_1);
        n10 = _loll(xl1_0_xl0_0) + _hill(xl1_1_xl0_1);
        n31 = _hill(xl1_0_xl0_0) + _loll(xl1_1_xl0_1);
        n30 = _loll(xl1_0_xl0_0) - _hill(xl1_1_xl0_1);

        /*-----------------------------------------------------------------*/
        /* Points that are read from succesive locations map to y, y[N/4]  */
        /* y[N/2], y[3N/4] in a radix4 scheme.                             */
        /*-----------------------------------------------------------------*/
        _amem8(&yb0[2*h2]) = n01_n00;
        _amem8(&yb1[2*h2]) = _itoll(n11, n10);
        _amem8(&yb2[2*h2]) = n21_n20;
        _amem8(&yb3[2*h2]) = _itoll(n31, n30);

        j += 4;
        if (j == n0) {
            j += n0;
            x0 += (int)npoints >> 1;
            x2 += (int)npoints >> 1;
        }
    }
}
#else
void DSP_fft16x32 (
    const short * restrict ptr_w,
    int npoints,
    int * restrict ptr_x,
    int * restrict ptr_y
)
{
    const short * restrict w;
    int * restrict x, * restrict x2;
    int i, j, l1, l2, h2, predj, tw_offset, stride, fft_jmp, tw_jmp, radix;
    int xt1_0, yt2_0, xt1_1, yt2_1, xt2_0, yt1_0, xt2_1, yt1_1;

    long long xh20_0_xh21_0, xh20_1_xh21_1, xh0_0_xh1_0, xh0_1_xh1_1; 
    long long xl20_0_xl21_0, xl20_1_xl21_1, xl0_0_xl1_0, xl0_1_xl1_1; 
    long long xt0_0_yt0_0,   xt0_1_yt0_1,   xt1_0_yt1_0;
    long long xt1_1_yt1_1,   xt2_0_yt2_0,   xt2_1_yt2_1; 
    long long x_0o_x_1o,     xl1_0o_xl1_1o, x_2o_x_3o,     xl1_2o_xl1_3o; 
    long long xh2_0o_xh2_1o, xl2_0o_xl2_1o, xh2_2o_xh2_3o, xl2_2o_xl2_3o;  
 
    long long x_01, x_23, x_l1_01, x_l1_23, x_l2_01, x_l2_23, x_h2_01,x_h2_23;
    long long co10si10_co11si11;
    long long co10_si10, co20_si20, co30_si30, co11_si11, co21_si21, co31_si31;

    /*---------------------------------------------------------------------*/
    /* Determine the magnitude od the number of points to be transformed.  */
    /* Check whether we can use a radix4 decomposition or a mixed radix    */
    /* transformation, by determining modulo 2.                            */
    /*---------------------------------------------------------------------*/
    radix = _norm(npoints) & 1 ? 2 : 4;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 2*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/ 
    stride = npoints;
    tw_offset = 0;
    fft_jmp = 6 * stride;
    tw_jmp  = 2 * stride;

    _nassert(stride > 4);
    #pragma MUST_ITERATE(1,,1);
    while (stride > 4) {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 2 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          2 N/4               1               */
        /*  2                          2 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/  
        j =  0;
        fft_jmp >>= 2;
        tw_jmp  >>= 2;

        /*-----------------------------------------------------------------*/
        /* Set up offsets to access "N/4", "N/2", "3N/4" complex point or  */
        /* "N/2", "N", "3N/2" half word                                    */
        /*-----------------------------------------------------------------*/ 
        h2 = stride >> 1;
        l1 = stride;
        l2 = stride + (stride >> 1);

        /*-----------------------------------------------------------------*/
        /*  Reset "x" to point to the start of the input data array.       */
        /* "tw_offset" starts off at 0, and increments by "6 * stride"     */
        /*  The stride quarters with every iteration of the outer loop     */
        /*-----------------------------------------------------------------*/
        x = ptr_x;
        w = (short *)ptr_w + tw_offset;
        tw_offset += tw_jmp;

        stride >>= 2;

        /*----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies, */
        /* within a given stage. Recall that there are logN to base 4     */
        /* stages. Certain butterflies share the twiddle factors. These   */
        /* are grouped together. On the very first stage there are no     */
        /* butterflies that share the twiddle factor, all N/4 butter-     */
        /* flies have different factors. On the next stage two sets of    */
        /* N/8 butterflies share the same twiddle factor. Hence after     */
        /* half the butterflies are performed, j the index into the       */
        /* factor array resets to 0, and the twiddle factors are reused.  */
        /* When this happens, the data pointer 'x' is incremented by the  */
        /* fft_jmp amount.                                                */
        /*----------------------------------------------------------------*/
        _nassert((int)(w) % 8 == 0);
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        _nassert(npoints >= 16);
        #pragma MUST_ITERATE(2,,2);
        for (i = 0; i < (npoints >> 3); i++) {
            /*------------------------------------------------------------*/
            /*  Read the first four twiddle factor values. This loop      */
            /*  computes two radix 4 butterflies at a time.               */
            /* si10 = w[0] co10 = w[1]  si11 = w[2]  co11 = w[3]          */
            /*------------------------------------------------------------*/
            co10si10_co11si11 = _amem8_const(&w[j]);
            co10_si10 = _dshl(_unpkh2(_hill(co10si10_co11si11)),16);
            co11_si11 = _dshl(_unpkh2(_loll(co10si10_co11si11)),16);
            co20_si20 = _cmpy32r1(co10_si10, co10_si10);
            co30_si30 = _cmpy32r1(co20_si20, co10_si10);
            co21_si21 = _cmpy32r1(co11_si11, co11_si11);
            co31_si31 = _cmpy32r1(co21_si21, co11_si11);

            /*-------------------------------------------------------------*/
            /* Read in the data elements for the eight inputs of two       */
            /* radix4 butterflies.                                         */
            /*  x[0]       x[1]       x[2]       x[3]                      */
            /*  x[h2+0]    x[h2+1]    x[h2+2]    x[h2+3]                   */
            /*  x[l1+0]    x[l1+1]    x[l1+2]    x[l1+3]                   */
            /*  x[l2+0]    x[l2+1]    x[l2+2]    x[l2+3]                   */
            /*-------------------------------------------------------------*/
            x_01    = _amem8(&x[0]);
            x_23    = _amem8(&x[2]);
            x_l1_01 = _amem8(&x[l1]);
            x_l1_23 = _amem8(&x[l1 + 2]);
            x_l2_01 = _amem8(&x[l2]);
            x_l2_23 = _amem8(&x[l2 + 2]);
            x_h2_01 = _amem8(&x[h2]);
            x_h2_23 = _amem8(&x[h2 + 2]);

            /*-------------------------------------------------------------*/
            /* xh0_0 = x[0] + x[l1];    xh1_0 = x[1] + x[l1+1]             */
            /* xh0_1 = x[2] + x[l1+2];  xh1_1 = x[3] + x[l1+3]             */
            /* xl0_0 = x[0] - x[l1];    xl1_0 = x[1] - x[l1+1]             */
            /* xl0_1 = x[2] - x[l1+2];  xl1_1 = x[3] - x[l1+3]             */
            /*-------------------------------------------------------------*/
            xh0_0_xh1_0 = _dadd(x_01, x_l1_01);
            xl0_0_xl1_0 = _dsub(x_01, x_l1_01);
            xh0_1_xh1_1 = _dadd(x_23, x_l1_23);
            xl0_1_xl1_1 = _dsub(x_23, x_l1_23);

            /*------------------------------------------------------------*/
            /* xh20_0 = x[h2  ] + x[l2  ]; xh21_0 = x[h2+1] + x[l2+1]     */
            /* xh20_1 = x[h2+2] + x[l2+2]; xh21_1 = x[h2+3] + x[l2+3]     */
            /* xl20_0 = x[h2  ] - x[l2  ]; xl21_0 = x[h2+1] - x[l2+1]     */
            /* xl20_1 = x[h2+2] - x[l2+2]; xl21_1 = x[h2+3] - x[l2+3]     */
            /*------------------------------------------------------------*/
            xh20_0_xh21_0 = _dadd(x_h2_01, x_l2_01);
            xl20_0_xl21_0 = _dsub(x_h2_01, x_l2_01);
            xh20_1_xh21_1 = _dadd(x_h2_23, x_l2_23);
            xl20_1_xl21_1 = _dsub(x_h2_23, x_l2_23);

            /*-------------------------------------------------------------*/
            /*    x_0o  = xh0_0 + xh20_0;    x_1o  = xh1_0 + xh21_0;       */
            /*    x_2o  = xh0_1 + xh20_1;    x_3o  = xh1_1 + xh21_1;       */
            /*    xt0_0 = xh0_0 - xh20_0;    yt0_0 = xh1_0 - xh21_0;       */
            /*    xt0_1 = xh0_1 - xh20_1;    yt0_1 = xh1_1 - xh21_1;       */
            /*-------------------------------------------------------------*/
            x_0o_x_1o = _dadd(xh0_0_xh1_0, xh20_0_xh21_0);
            x_2o_x_3o = _dadd(xh0_1_xh1_1, xh20_1_xh21_1);

            xt0_0_yt0_0 = _dsub(xh0_0_xh1_0, xh20_0_xh21_0);
            xt0_1_yt0_1 = _dsub(xh0_1_xh1_1, xh20_1_xh21_1);

            /*-------------------------------------------------------------*/
            /*    xt1_0 = xl0_0 + xl21_0;    yt2_0 = xl1_0 + xl20_0;       */
            /*    xt1_1 = xl0_1 + xl21_1;    yt2_1 = xl1_1 + xl20_1;       */
            /*    xt2_0 = xl0_0 - xl21_0;    yt1_0 = xl1_0 - xl20_0;       */
            /*    xt2_1 = xl0_1 - xl21_1;    yt1_1 = xl1_1 - xl20_1;       */
            /*-------------------------------------------------------------*/
            xt1_0 = _hill(xl0_0_xl1_0) + _loll(xl20_0_xl21_0);
            yt2_0 = _loll(xl0_0_xl1_0) + _hill(xl20_0_xl21_0);
            xt1_1 = _hill(xl0_1_xl1_1) + _loll(xl20_1_xl21_1);
            yt2_1 = _loll(xl0_1_xl1_1) + _hill(xl20_1_xl21_1);

            xt2_0 = _hill(xl0_0_xl1_0) - _loll(xl20_0_xl21_0);
            yt1_0 = _loll(xl0_0_xl1_0) - _hill(xl20_0_xl21_0);
            xt2_1 = _hill(xl0_1_xl1_1) - _loll(xl20_1_xl21_1);
            yt1_1 = _loll(xl0_1_xl1_1) - _hill(xl20_1_xl21_1);

            xt1_0_yt1_0 = _itoll(xt1_0, yt1_0);
            xt1_1_yt1_1 = _itoll(xt1_1, yt1_1);

            xt2_0_yt2_0 = _itoll(xt2_0, yt2_0);
            xt2_1_yt2_1 = _itoll(xt2_1, yt2_1);

            /*-------------------------------------------------------------*/
            /*   x2[h2  ] = (si10 * yt1_0 + co10 * xt1_0) >> 15            */
            /*   x2[h2+1] = (co10 * yt1_0 - si10 * xt1_0) >> 15            */
            /*   x2[h2+2] = (si11 * yt1_1 + co11 * xt1_1) >> 15            */
            /*   x2[h2+3] = (co11 * yt1_1 - si11 * xt1_1) >> 15            */
            /*-------------------------------------------------------------*/
            xh2_0o_xh2_1o = _cmpy32r1(co10_si10, xt1_0_yt1_0);
            xh2_2o_xh2_3o = _cmpy32r1(co11_si11, xt1_1_yt1_1);

            /*-------------------------------------------------------------*/
            /*   x2[l1  ] = (si20 * yt0_0 + co20 * xt0_0) >> 15            */
            /*   x2[l1+1] = (co20 * yt0_0 - si20 * xt0_0) >> 15            */
            /*   x2[l1+2] = (si21 * yt0_1 + co21 * xt0_1) >> 15            */
            /*   x2[l1+3] = (co21 * yt0_1 - si21 * xt0_1) >> 15            */
            /*-------------------------------------------------------------*/
            xl1_0o_xl1_1o = _cmpy32r1(co20_si20, xt0_0_yt0_0);
            xl1_2o_xl1_3o = _cmpy32r1(co21_si21, xt0_1_yt0_1);

            /*-------------------------------------------------------------*/
            /*   x2[l2  ] = (si30 * yt2_0 + co30 * xt2_0) >> 15            */
            /*   x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0) >> 15            */
            /*   x2[l2+2] = (si31 * yt2_1 + co31 * xt2_1) >> 15            */
            /*   x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1) >> 15            */
            /*-------------------------------------------------------------*/
            xl2_0o_xl2_1o = _cmpy32r1(co30_si30, xt2_0_yt2_0);
            xl2_2o_xl2_3o = _cmpy32r1(co31_si31, xt2_1_yt2_1);

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x2 = x;

            /*-------------------------------------------------------------*/
            /*  Store eight outputs - four legs of each butterfly          */
            /*-------------------------------------------------------------*/
            _amem8(&x2[0])    = x_0o_x_1o;
            _amem8(&x2[2])    = x_2o_x_3o;

            _amem8(&x2[h2])   = xh2_0o_xh2_1o;
            _amem8(&x2[h2+2]) = xh2_2o_xh2_3o;

            _amem8(&x2[l1])   = xl1_0o_xl1_1o;
            _amem8(&x2[l1+2]) = xl1_2o_xl1_3o;

            _amem8(&x2[l2])   = xl2_0o_xl2_1o;
            _amem8(&x2[l2+2]) = xl2_2o_xl2_3o;

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 4, to reflect the fact that 2 words        */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            j += 4;
            x += 4;
            predj = (3*j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;
        }
    }

    if (radix == 2)
        radix_2(ptr_x, ptr_y, npoints);
    else
        radix_4(ptr_x, ptr_y, npoints);

}

void radix_2 (
    int * restrict ptr_x,
    int * restrict ptr_y,
    int npoints
)
{
    int * restrict x0, * restrict x2;
    int * restrict y0, * restrict y1, * restrict y2, * restrict y3;
    int * restrict yb0, * restrict yb1, * restrict yb2, * restrict yb3;
    int n0, j, i, h2, l1;
    long long n00_n01, n10_n11, n20_n21, n30_n31;
    long long n02_n03, n12_n13, n22_n23, n32_n33;

    long long x01, x23, x45, x67, x89, xAB, xCD, xEF;

    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix4 pass or a  */
    /* radix2 pass. Two pointers are used to access the input data.    */
    /* The input data is read "N/4" complex samples apart or "N/2"     */
    /* words apart using pointers "x0" and "x2". This produces out-    */
    /* puts that are 0, N/8, N/2, 3N/8 for radix 2.                    */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + (int)npoints;
    x0 = ptr_x;
    x2 = ptr_x + (int)(npoints >> 1);

    /*----------------------------------------------------------------*/
    /* The pointers are set at the following locations which are half */
    /* the offsets of a radix4 FFT.                                   */
    /*----------------------------------------------------------------*/
    y1 = y0 + (int)(npoints >> 2);
    y3 = y2 + (int)(npoints >> 2);
    l1 = _norm(npoints) + 1;
    n0 = npoints >> 1;

    yb0 = y0 + 2;
    yb1 = y1 + 2;
    yb2 = y2 + 2;
    yb3 = y3 + 2;

    /*--------------------------------------------------------------------*/
    /* The following code reads data identically for either a radix 4     */
    /* or a radix 2 style decomposition. It writes out at different       */
    /* locations though. It checks if either half the points, or a        */
    /* quarter of the complex points have been exhausted to jump to       */
    /* pervent double reversal.                                           */
    /*--------------------------------------------------------------------*/
    j = 0;

    _nassert((int)(npoints) % 4  == 0);
    _nassert((int)(ptr_x) % 8 == 0);
    _nassert((int)(ptr_y) % 8 == 0);
    _nassert((int)(x0) % 8 == 0);
    _nassert((int)(x2) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    #pragma MUST_ITERATE(2,,2);
    for (i = 0; i < npoints; i += 8) {
        /*----------------------------------------------------------------*/
        /* Digit reverse the index starting from 0. The increment to "j"  */
        /* is either by 4, or 8.                                          */
        /*----------------------------------------------------------------*/
        h2 = _deal(j);
        h2 = _bitr(h2);
        h2 = _rotl(h2, 16);
        h2 = _shfl(h2);
        h2 >>= l1;

        /*----------------------------------------------------------------*/
        /* Read in the input data. These are transformed as a radix 2.    */
        /*----------------------------------------------------------------*/
        x01 = _amem8(&x0[0]);
        x23 = _amem8(&x0[2]);
        x45 = _amem8(&x0[4]);
        x67 = _amem8(&x0[6]);
        x0 += 8;

        x89 = _amem8(&x2[0]);
        xAB = _amem8(&x2[2]);
        xCD = _amem8(&x2[4]);
        xEF = _amem8(&x2[6]);
        x2 += 8;

        /*-------------------------------------------------------------*/
        /* Perform radix2 style decomposition.                         */
        /*-------------------------------------------------------------*/
        n00_n01 = _dadd(x01, x23);
        n20_n21 = _dsub(x01, x23);
        n10_n11 = _dadd(x45, x67);
        n30_n31 = _dsub(x45, x67);

        n02_n03 = _dadd(x89, xAB);
        n22_n23 = _dsub(x89, xAB);
        n12_n13 = _dadd(xCD, xEF);
        n32_n33 = _dsub(xCD, xEF);

        /*-----------------------------------------------------------------*/
        /* Points that are read from succesive locations map to y, y[N/8]  */
        /* y[N/2],y[5N/8] in a radix2 scheme.                              */
        /*-----------------------------------------------------------------*/
        _amem8(&y0[2*h2])  = n00_n01;
        _amem8(&y1[2*h2])  = n10_n11;
        _amem8(&y2[2*h2])  = n20_n21;
        _amem8(&y3[2*h2])  = n30_n31;

        _amem8(&yb0[2*h2]) = n02_n03;
        _amem8(&yb1[2*h2]) = n12_n13;
        _amem8(&yb2[2*h2]) = n22_n23;
        _amem8(&yb3[2*h2]) = n32_n33;

        j += 8;
        if (j == n0) {
            j  += n0;
            x0 += (int)npoints >> 1;
            x2 += (int)npoints >> 1;
        }
    }
}

void radix_4 (
    int * restrict ptr_x,
    int * restrict ptr_y,
    int npoints
)
{
    int * restrict x0, * restrict x2;
    int * restrict y0, * restrict y1, * restrict y2, * restrict y3;
    int * restrict yb0, * restrict yb1, * restrict yb2, * restrict yb3;
    int n0, j, i, h2, l1;
    int n11, n10, n31, n30;

    long long x01, x23, x45, x67, x89, xab, xcd, xef;
    long long xh0_0_xh1_0, xh0_1_xh1_1, xl0_0_xl1_0, xl0_1_xl1_1;
    long long n00_n01, n20_n21;
                              
    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix2 pass. Two  */
    /* pointers are used to access the input data. The input data is   */
    /* read "N/4" complex samples apart or "N/2" words apart using     */
    /* pointers "x0" and "x2". This produces outputs that are 0, N/4,  */
    /* N/2, 3N/4 for a radix4 FFT.                                     */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + (int)npoints;
    x0 = ptr_x;
    x2 = ptr_x + (int)(npoints >> 1);

    /*----------------------------------------------------------------*/
    /* The pointers are set at the following locations                */
    /*----------------------------------------------------------------*/
    y1 = y0 + (int)(npoints >> 1);
    y3 = y2 + (int)(npoints >> 1);
    l1 = _norm(npoints) + 2;
    n0 = npoints >> 2;

    yb0 = y0 + 2;
    yb1 = y1 + 2;
    yb2 = y2 + 2;
    yb3 = y3 + 2;
   
    /*--------------------------------------------------------------------*/
    /* The following code reads data identically for either a radix 4     */
    /* or a radix 2 style decomposition. It writes out at different       */
    /* locations though. It checks if either half the points, or a        */
    /* quarter of the complex points have been exhausted to jump to       */
    /* pervent double reversal.                                           */
    /*--------------------------------------------------------------------*/
    j = 0;
    
    _nassert((int)(npoints) % 4  == 0);
    _nassert((int)(x0) % 8 == 0);
    _nassert((int)(x2) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    _nassert(npoints >= 16);
    #pragma MUST_ITERATE(2,,2);
    for (i = 0; i < npoints; i += 8) {
        /*----------------------------------------------------------------*/
        /* Digit reverse the index starting from 0. The increment to "j"  */
        /* is either by 4, or 8.                                          */
        /*----------------------------------------------------------------*/
        h2 = _deal(j);
        h2 = _bitr(h2);
        h2 = _rotl(h2, 16);
        h2 = _shfl(h2);
        h2 >>= l1;

        /*----------------------------------------------------------------*/
        /* Read in the input data, from the first eight locations. These  */
        /* are transformed as a radix4.                                   */
        /*----------------------------------------------------------------*/
        x01 = _amem8(&x0[0]);
        x23 = _amem8(&x0[2]);
        x45 = _amem8(&x0[4]);
        x67 = _amem8(&x0[6]);
        x0 += 8;

        xh0_0_xh1_0 = _dadd(x01, x45);
        xh0_1_xh1_1 = _dadd(x23, x67);
        xl0_0_xl1_0 = _dsub(x01, x45);
        xl0_1_xl1_1 = _dsub(x23, x67);

        n00_n01 = _dadd(xh0_0_xh1_0, xh0_1_xh1_1);
        n20_n21 = _dsub(xh0_0_xh1_0, xh0_1_xh1_1);
        n11 = _loll(xl0_0_xl1_0) - _hill(xl0_1_xl1_1);
        n10 = _hill(xl0_0_xl1_0) + _loll(xl0_1_xl1_1);
        n31 = _loll(xl0_0_xl1_0) + _hill(xl0_1_xl1_1);
        n30 = _hill(xl0_0_xl1_0) - _loll(xl0_1_xl1_1);

        _amem8(&y0[2*h2]) = n00_n01;
        _amem8(&y1[2*h2]) = _itoll(n10, n11);
        _amem8(&y2[2*h2]) = n20_n21;
        _amem8(&y3[2*h2]) = _itoll(n30, n31);

        /*----------------------------------------------------------------*/
        /* Read in the next eight inputs and perform radix4 decomposition */
        /*----------------------------------------------------------------*/
        x89 = _amem8(&x2[0]);
        xab = _amem8(&x2[2]);
        xcd = _amem8(&x2[4]);
        xef = _amem8(&x2[6]);
        x2 += 8;

        xh0_0_xh1_0 = _dadd(x89, xcd);
        xh0_1_xh1_1 = _dadd(xab, xef);
        xl0_0_xl1_0 = _dsub(x89, xcd);
        xl0_1_xl1_1 = _dsub(xab, xef);

        n00_n01 = _dadd(xh0_0_xh1_0, xh0_1_xh1_1);
        n20_n21 = _dsub(xh0_0_xh1_0, xh0_1_xh1_1);
        n11 = _loll(xl0_0_xl1_0) - _hill(xl0_1_xl1_1);
        n10 = _hill(xl0_0_xl1_0) + _loll(xl0_1_xl1_1);
        n31 = _loll(xl0_0_xl1_0) + _hill(xl0_1_xl1_1);
        n30 = _hill(xl0_0_xl1_0) - _loll(xl0_1_xl1_1);

        /*-----------------------------------------------------------------*/
        /* Points that are read from succesive locations map to y, y[N/4]  */
        /* y[N/2], y[3N/4] in a radix4 scheme.                             */
        /*-----------------------------------------------------------------*/
        _amem8(&yb0[2*h2]) = n00_n01;
        _amem8(&yb1[2*h2]) = _itoll(n10, n11);
        _amem8(&yb2[2*h2]) = n20_n21;
        _amem8(&yb3[2*h2]) = _itoll(n30, n31);

        j += 4;
        if (j == n0) {
            j += n0;
            x0 += (int)npoints >> 1;
            x2 += (int)npoints >> 1;
        }
    }
}
#endif
/* ======================================================================== */
/*  End of file: DSP_fft16x32.c                                             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

