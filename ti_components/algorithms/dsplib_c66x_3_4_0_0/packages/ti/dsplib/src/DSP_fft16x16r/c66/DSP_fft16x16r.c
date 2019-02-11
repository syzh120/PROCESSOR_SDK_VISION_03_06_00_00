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
/*      DSP_fft16x16r -- fft16x16r                                         */
/*                                                                         */
/*  USAGE                                                                  */
/*                                                                         */
/*      void DSP_fft16x16r (                                               */
/*          int n,                                                         */
/*          short * ptr_x,                                                 */
/*          const short * ptr_w,                                           */
/*          short * ptr_y,                                                 */
/*          int radix,                                                     */
/*          int offset,                                                    */
/*          int n_max                                                      */
/*      );                                                                 */
/*                                                                         */
/*      N      = length of fft in complex samples, power of 2 <=16384      */
/*      ptr_x  = pointer to complex data input                             */
/*      ptr_w  = pointer to complex twiddle factor (see below)             */
/*      radix  = smallest fft butterfly used in computation for decomposi  */
/*      offset = index in complex samples of sub-fft from start of main f  */
/*      n_max  = size of main fft in complex samples                       */
/*                                                                         */
/*      (See the C compiler reference guide.)                              */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      The benchmark performs a mixed radix forwards fft using            */
/*      a special sequence of coefficients generated in the following      */
/*      way:                                                               */
/*                                                                         */
/*    int gen_twiddle_fft16x16r(short *w, int n)                           */
/*                                                                         */
/*    int i, j, k;                                                         */
/*    double M = 32767.5;                                                  */
/*                                                                         */
/*    for (j = 1, k = 0; j < n >> 2; j = j << 2)                           */
/*    {                                                                    */
/*        for (i = 0; i < n >> 2; i += j << 1)                             */
/*        {                                                                */
/*                                                                         */
/*          w[k +  3] = d2s(M * cos(2.0 * PI * (i + j) / n));              */
/*          w[k +  2] = d2s(M * sin(2.0 * PI * (i + j) / n));              */
/*          w[k +  1] = d2s(M * cos(2.0 * PI * (i    ) / n));              */
/*          w[k +  0] = d2s(M * sin(2.0 * PI * (i    ) / n));              */
/*                                                                         */
/*          k += 12;                                                       */
/*                                                                         */
/*        }                                                                */
/*    }                                                                    */
/*      This redundent set of twiddle factors is size 2*N short samples.   */
/*      As pointed out later dividing these twiddle factors by 2 will give */
/*      an effective divide by 4 at each stage to guarentee no overflow.   */
/*      The function is accurate to about 68dB of signal to noise ratio    */
/*      to the DFT function below:                                         */
/*                                                                         */
/*       void dft(int n, short x[], short y[])                             */
/*       {                                                                 */
/*          int k,i, index;                                                */
/*          const double PI = 3.14159654;                                  */
/*          short * p_x;                                                   */
/*          double arg, fx_0, fx_1, fy_0, fy_1, co, si;                    */
/*                                                                         */
/*          for(k = 0; k<n; k++)                                           */
/*          {                                                              */
/*            p_x = x;                                                     */
/*            fy_0 = 0;                                                    */
/*            fy_1 = 0;                                                    */
/*            for(i=0; i<n; i++)                                           */
/*            {                                                            */
/*              fx_0 = (double)p_x[0];                                     */
/*              fx_1 = (double)p_x[1];                                     */
/*              p_x += 2;                                                  */
/*              index = (i*k) % n;                                         */
/*              arg = 2*PI*index/n;                                        */
/*              co = cos(arg);                                             */
/*              si = -sin(arg);                                            */
/*              fy_0 += ((fx_0 * co) - (fx_1 * si));                       */
/*              fy_1 += ((fx_1 * co) + (fx_0 * si));                       */
/*            }                                                            */
/*            y[2*k] = (short)2*fy_0/sqrt(N);                              */
/*            y[2*k+1] = (short)2*fy_1/sqrt(N);                            */
/*          }                                                              */
/*       }                                                                 */
/*      Scaling takes place at each stage except the last one.             */
/*      This is a divide by 2 to prevent overflow. All shifts are rounded  */
/*      reduce truncation noise power by 3dB.                              */
/*      The function takes the table and input data and calculates the fft */
/*      producing the frequency domain data in the Y array.                */
/*      As the fft allows every input point to effect every output point i */
/*      a cache based system such as the c64xx, this causes cache thrashin */
/*      This is mitigated by allowing the main fft of size N to be divided */
/*      into several steps, allowing as much data reuse as possible.       */
/*                                                                         */
/*      For example the following function:                                */
/*                                                                         */
/*      fft16x16r  (1024, &x_asm[0], &w[0], y_asm, 4, 0, 1024);            */
/*                                                                         */
/*      is equvalent to:                                                   */
/*                                                                         */
/*      fft16x16r  (1024,&x_asm[2*0],  &w[0]    ,y_asm,256,  0,1024);      */
/*      fft16x16r  (256, &x_asm[2*0],  &w[2*768],y_asm,4,    0,1024);      */
/*      fft16x16r  (256, &x_asm[2*256],&w[2*768],y_asm,4,  256,1024);      */
/*      fft16x16r  (256, &x_asm[2*512],&w[2*768],y_asm,4,  512,1024);      */
/*      fft16x16r  (256, &x_asm[2*768],&w[2*768],y_asm,4,  768,1024);      */
/*                                                                         */
/*      Notice how the 1st fft function is called on the entire 1K data se */
/*      it covers the 1st pass of the fft until the butterfly size is 256. */
/*      The following 4 ffts do 256 pt ffts 25% of the size. These continu */
/*      down to the end when the buttefly is of size 4. The use an index t */
/*      the main twiddle factor array of 0.75*2*N. This is because the     */
/*      twiddle factor array is composed of successively decimated version */
/*      of the main array.                                                 */
/*                                                                         */
/*      N not equal to a power of 4 can be used, i.e. 512. In this case to */
/*      decompose the fft the following would be needed :                  */
/*                                                                         */
/*      fft16x16r   (512, &x_asm[0],&w[0],y_asm,2,  0,512);                */
/*                                                                         */
/*      is equvalent to:                                                   */
/*                                                                         */
/*      fft16x16r   (512, &x_asm[0],    &w[0],    y_asm,128,  0,512);      */
/*      fft16x16r   (128, &x_asm[2*0],  &w[2*384],y_asm,2,    0,512);      */
/*      fft16x16r   (128, &x_asm[2*128],&w[2*384],y_asm,2,  128,512);      */
/*      fft16x16r   (128, &x_asm[2*256],&w[2*384],y_asm,2,  256,512);      */
/*      fft16x16r   (128, &x_asm[2*384],&w[2*384],y_asm,2,  384,512);      */
/*                                                                         */
/*      The twiddle factor array is composed of log4(N) sets of twiddle    */
/*      factors, (3/4)*N, (3/16)*N, (3/64)*N, etc.  The index into this    */
/*      array for each stage of the fft is calculated by summing these     */
/*      indices up appropriately.                                          */
/*      For multiple ffts they can share the same table by calling the sma */
/*      ffts from further down in the twiddle factor array. In the same wa */
/*      as the decomposition works for more data reuse.                    */
/*                                                                         */
/*      Thus, the above decomposition can be summarized for a general N ,  */
/*      radix "rad" as follows:                                            */
/*                                                                         */
/*  fft16x16r(N,  &x_cn[0],         &w[0],         y_cn, N/4, 0,     N     */
/*  fft16x16r(N/4,&x_cn[0],         &w[2*(3*N/4)], y_cn, rad, 0,     N     */
/*  fft16x16r(N/4,&x_cn[2*(N/4)],   &w[2*(3*N/4)], y_cn, rad, N/4,   N     */
/*  fft16x16r(N/4,&x_cn[2*(N/2)],   &w[2*(3*N/4)], y_cn, rad, N/2,   N     */
/*  fft16x16r(N/4,&x_cn[2*(3*N/4)], &w[2*3*N/4)],  y_cn, rad, 3*N/4, N     */
/*                                                                         */
/*      As discussed previously, N can be either a power of 4 or 2.  If  N */
/*      N is a power  of 4, rad = 4, and if N is a power of 2, and not  a  */
/*      power of 4, then rad = 2. "rad" is used to control how many stages */
/*      of decomposition are performed. It is also used to dtermine whethe */
/*      a radix4 or radix2 decomposition should be performed at the last   */
/*      stage. Hence when "rad" is set to "N/4" the first stage of the     */
/*      transform alone is performed and the code exits. To complete the   */
/*      FFT four other calls are required to perform N/4 size FFT's. In    */
/*      fact the ordering of these 4 FFT's amonst themselves does not      */
/*      matter and hence from a cahe perspective it helps to go through    */
/*      the remaining 4 FFT's in exactly the opposite order to the first.  */
/*                                                                         */
/*      This is illustrated as follows:                                    */
/*                                                                         */
/*  fft16x16r(N,  &x_cn[0],         &w[0],         y_cn, N/4, 0,     N     */
/*  fft16x16r(N/4,&x_cn[2*(3*N/4)], &w[2*3*N/4)],  y_cn, rad, 3*N/4, N     */
/*  fft16x16r(N/4,&x_cn[2*(N/2)],   &w[2*(3*N/4)], y_cn, rad, N/2,   N     */
/*  fft16x16r(N/4,&x_cn[2*(N/4)],   &w[2*(3*N/4)], y_cn, rad, N/4,   N     */
/*  fft16x16r(N/4,&x_cn[0],         &w[2*(3*N/4)], y_cn, rad, 0,     N     */
/*                                                                         */
/*      In addition this function can be used to minimize call overhead, b */
/*      completing the FFT with one function call invocation as shown belo */
/*                                                                         */
/*      fft16x16r(N, &x_cn[0], &w[0], y_cn, rad, 0, N)                     */
/*                                                                         */
/*   ASSUMPTIONS:                                                          */
/*      n must be a power of 2 and n >= 8  n <= 16384 points.              */
/*      Complex time data x and twiddle facotrs w are aligned on double    */
/*      word boundares. Real values are stored in even word positions and  */
/*      imaginary values in odd positions.                                 */
/*                                                                         */
/*      All data is in short precision integer fixed point form. The       */
/*      complex frequency data will be returned in linear order.           */
/*                                                                         */
/*   TECHNIQUES                                                            */
/*      A special sequence of coeffs. used as generated above              */
/*      produces the fft. This collapses the inner 2 loops in the          */
/*      taditional Burrus and Parks implementation Fortran Code.           */
/*                                                                         */
/*      The revised FFT uses a redundant sequence of twiddle factors to    */
/*      allow a linear access through the data. This linear access enables */
/*      data and instruction level parallelism.                            */
/*      The data produced by the fft16x16r fft is in normal form, the      */
/*      whole data array is written into a new output buffer.              */
/*                                                                         */
/*      The fft16x16r butterfly is bit reversed, i.e. the inner 2 points o */
/*      the butterfly are crossed over, this has the effect of making the  */
/*      data come out in bit reversed rather than in radix 4 digit reverse */
/*      order. This simplifies the last pass of the loop. It is performed  */
/*      using the _bitr instruction on C64x architecture.                  */
/*                                                                         */
/*   NOTES                                                                 */
/*      For more aggressive overflow control the shift in the DC term can  */
/*      adjusted to 2 and the twiddle factors shifted right by 1. This giv */
/*      a divide by 4 at each stage. For better accuracy the data can be p */
/*      asserted left by so many bits so that as it builds in magnitude th */
/*      divide by 2 prevents too much growth. An optimal point for example */
/*      with an 8192pt fft with input data precision of 8 bits is to asert */
/*      the input 4 bits left to make it 12 bits. This gives an SNR of 68d */
/*      at the output. By trying combinations the optimal can be found.    */
/*      If scaling isnot required it is possible to replace the MPY by SMP */
/*      this will give a shift left by 1 so a shift right by 16 gives a    */
/*      total 15 bit shift right. The DC term must be adjusted to give a   */
/*      zero shift.                                                        */
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

#pragma CODE_SECTION(DSP_fft16x16r, ".text:optimized");

#include "DSP_fft16x16r.h"

static inline void radix_2(short *restrict ptr_x, short *restrict ptr_y, int n, int offset, int n_max);
static inline void radix_4(short *restrict ptr_x, short *restrict ptr_y, int n, int offset, int n_max);

#ifdef _LITTLE_ENDIAN
void DSP_fft16x16r (
    int n,
    short * restrict ptr_x,
    const short * restrict ptr_w,
    short * restrict ptr_y,
    int radix,
    int offset,
    int n_max
)
{
    short * restrict x, * restrict x1, * restrict x2;
    const short * restrict tw;
    long long *restrict Twiddles;

    long long x_3210, x_7654, xl2_3210, xl2_7654, xl1_3210, xl1_7654, xh2_3210, xh2_7654;
    long long co11si11_co10si10, co13si13_co12si12, co13si13_co12si12_tmp;
    long long co1si1_1_co1si1_0, co2si2_1_co2si2_0, co3si3_1_co3si3_0;
    long long xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0;
    long long xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0;
    long long x_3o_x_2o_x_1o_x_0o, yt2_1_xt1_1_yt2_0_xt1_0, yt0_1_xt0_1_yt0_0_xt0_0, yt1_1_xt2_1_yt1_0_xt2_0;
    long long x_7o_x_6o_x_5o_x_4o, yt2_3_xt1_3_yt2_2_xt1_2, yt0_3_xt0_3_yt0_2_xt0_2, yt1_3_xt2_3_yt1_2_xt2_2;  

    int j, i, l1, l2, h2, fft_jmp, tw_jmp;
    int predj, tw_offset, stride, loop_limit, last_r4;

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
    stride = n;
    tw_offset = 0;
    fft_jmp = 6 * stride;
    tw_jmp  = 2 * stride;

    /*----------------------------------------------------------------------*/
    /* When radix == 2, last radix 4 stage needs to be treated differently  */
    /*----------------------------------------------------------------------*/
    loop_limit = radix;
    last_r4    = 0;
    if (radix == 2) {
      loop_limit = 8;
      last_r4    = 1;
    }

    _nassert(stride > 4);
    #pragma MUST_ITERATE(1,,1);

    while (stride > loop_limit) {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "tw" is pointing to the correct location within the */
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
        tw = ptr_w + tw_offset;
        Twiddles = (void*)tw;
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
        /* fft_jmp amount. In addition the following code is unrolled to  */
        /* perform "4" radix4 butterflies in parallel.                    */
        /*----------------------------------------------------------------*/
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        _nassert(n >= 16);
        #pragma MUST_ITERATE(1,,1);
        for (i = 0; i < n; i += 16) {

            /*-----------------------------------------------------------*/
            /* Read in complex input for the butterflies.                */
            /*-----------------------------------------------------------*/
            x_3210   = _amem8(&x[0]);
            x_7654   = _amem8(&x[4]);
            xl1_3210 = _amem8(&x[l1]);
            xl1_7654 = _amem8(&x[l1+4]);
            xl2_3210 = _amem8(&x[l2]);
            xl2_7654 = _amem8(&x[l2+4]);
            xh2_3210 = _amem8(&x[h2]);
            xh2_7654 = _amem8(&x[h2+4]);

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x2 = (short *)_mvd((int)x);

            /*-----------------------------------------------------------*/
            /* Read in complex input for twiddle factors.                */
            /*-----------------------------------------------------------*/
            co11si11_co10si10 = *Twiddles++;
            co13si13_co12si12_tmp = *Twiddles++;
            co13si13_co12si12 = _dmvd(_hill(co13si13_co12si12_tmp), _loll(co13si13_co12si12_tmp));

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 24, to reflect the fact that 24 half words */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 8. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            j += 24;
            x += 8;

            predj = (fft_jmp - j);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;
            if (!predj) Twiddles= (void*)tw;

            /*-----------------------------------------------------------*/
            /* First 2-Radix4's                                          */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_h2_0 - x_l2_0;    xl21_0 = x_h2_1 - x_l2_1;  */
            /*   xl20_1 = x_h2_2 - x_l2_2;    xl21_1 = x_h2_3 - x_l2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh1_1_xh0_1_xh1_0_xh0_0     = _davg2(xl1_3210, x_3210);
            xh21_1_xh20_1_xh21_0_xh20_0 = _davg2(xl2_3210, xh2_3210);
            xl1_1_xl0_1_xl1_0_xl0_0     = _dshr2(_dssub2(x_3210, xl1_3210), 1);
            xl20_1_xl21_1_xl20_0_xl21_0 = _dshr2(_dcrot270(_dssub2(xl2_3210, xh2_3210)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_1 = xl0_1 + xl21_1;      yt2_1 = xl1_1 + xl20_1;    */
            /*   xt1_0 = xl0_0 + xl21_0;      yt2_0 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_0 = xh0_0 - xh20_0;      xt0_1 = xh0_1 - xh20_1;    */
            /*   yt0_0 = xh1_0 - xh21_0;      yt0_1 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_0 = xl0_0 - xl21_0;      xt2_1 = xl0_1 - xl21_1;    */
            /*   yt1_0 = xl1_0 - xl20_0;      yt1_1 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_3o_x_2o_x_1o_x_0o     = _dsadd2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt2_1_xt1_1_yt2_0_xt1_0 = _dsadd2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);
            yt0_1_xt0_1_yt0_0_xt0_0 = _dssub2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt1_1_xt2_1_yt1_0_xt2_0 = _dssub2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);

            /*-----------------------------------------------------------*/
            /* Second 2-Radix4's                                         */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_h2_0 - x_l2_0;    xl21_0 = x_h2_1 - x_l2_1;  */
            /*   xl20_1 = x_h2_2 - x_l2_2;    xl21_1 = x_h2_3 - x_l2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh1_1_xh0_1_xh1_0_xh0_0     = _davg2(xl1_7654, x_7654);
            xh21_1_xh20_1_xh21_0_xh20_0 = _davg2(xl2_7654, xh2_7654);
            xl1_1_xl0_1_xl1_0_xl0_0     = _dshr2(_dssub2(x_7654, xl1_7654), 1);
            xl20_1_xl21_1_xl20_0_xl21_0 = _dshr2(_dcrot270(_dssub2(xl2_7654, xh2_7654)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_3 = xl0_1 + xl21_1;      yt2_3 = xl1_1 + xl20_1;    */
            /*   xt1_2 = xl0_0 + xl21_0;      yt2_2 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_2 = xh0_0 - xh20_0;      xt0_3 = xh0_1 - xh20_1;    */
            /*   yt0_2 = xh1_0 - xh21_0;      yt0_3 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_2 = xl0_0 - xl21_0;      xt2_3 = xl0_1 - xl21_1;    */
            /*   yt1_2 = xl1_0 - xl20_0;      yt1_3 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_7o_x_6o_x_5o_x_4o     = _dsadd2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt2_3_xt1_3_yt2_2_xt1_2 = _dsadd2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);
            yt0_3_xt0_3_yt0_2_xt0_2 = _dssub2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt1_3_xt2_3_yt1_2_xt2_2 = _dssub2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);
   
            /*-----------------------------------------------------------*/
            /* Compute and apply twiddle factor for first 2-Radix4's     */
            /*-----------------------------------------------------------*/
            co2si2_1_co2si2_0 = _dcmpyr1(co11si11_co10si10, co11si11_co10si10);
            co3si3_1_co3si3_0 = _dcmpyr1(co11si11_co10si10, co2si2_1_co2si2_0);
            _amem8(&x2[0])    = x_3o_x_2o_x_1o_x_0o;
            _amem8(&x2[l1])   = _dcmpyr1(yt2_1_xt1_1_yt2_0_xt1_0, co11si11_co10si10);
            _amem8(&x2[h2])   = _dcmpyr1(yt0_1_xt0_1_yt0_0_xt0_0, co2si2_1_co2si2_0);
            _amem8(&x2[l2])   = _dcmpyr1(yt1_1_xt2_1_yt1_0_xt2_0, co3si3_1_co3si3_0);
   
            /*-----------------------------------------------------------*/
            /* Compute and apply twiddle factor for second 2-Radix4's    */
            /*-----------------------------------------------------------*/
            co2si2_1_co2si2_0 = _dcmpyr1(co13si13_co12si12, co13si13_co12si12);
            co3si3_1_co3si3_0 = _dcmpyr1(co13si13_co12si12, co2si2_1_co2si2_0);
            _amem8(&x2[4])    = x_7o_x_6o_x_5o_x_4o;
            _amem8(&x2[l1+4]) = _dcmpyr1(yt2_3_xt1_3_yt2_2_xt1_2, co13si13_co12si12);
            _amem8(&x2[h2+4]) = _dcmpyr1(yt0_3_xt0_3_yt0_2_xt0_2, co2si2_1_co2si2_0);
            _amem8(&x2[l2+4]) = _dcmpyr1(yt1_3_xt2_3_yt1_2_xt2_2, co3si3_1_co3si3_0);

        }
    }

    if (last_r4) {

        /*---------------------------------------------------------------*/
        /*  Last stage of Radix4's is handled here because               */
        /*  it has different pointer offsets                             */
        /*---------------------------------------------------------------*/
        x1 = ptr_x;
        tw = ptr_w + tw_offset;
        Twiddles = (void*)tw;

        /*---------------------------------------------------------------*/
        /* Load and compute twiddle factors                              */
        /*---------------------------------------------------------------*/
        co1si1_1_co1si1_0 = *Twiddles;
        co2si2_1_co2si2_0 = _dcmpyr1(co1si1_1_co1si1_0, co1si1_1_co1si1_0);
        co3si3_1_co3si3_0 = _dcmpyr1(co1si1_1_co1si1_0, co2si2_1_co2si2_0);

        _nassert(n >= 16);
        #pragma MUST_ITERATE(1,,1);
        for (i = 0; i < n; i += 16) {

            /*-----------------------------------------------------------*/
            /* Read in complex input for the butterflies.                */
            /*-----------------------------------------------------------*/
            x_3210   = _amem8(&x1[0]);
            xl1_3210 = _amem8(&x1[8]);
            xl2_3210 = _amem8(&x1[12]);
            xh2_3210 = _amem8(&x1[4]);
            x_7654   = _amem8(&x1[16]);
            xl1_7654 = _amem8(&x1[24]);
            xl2_7654 = _amem8(&x1[28]);
            xh2_7654 = _amem8(&x1[20]);

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x2 = (short *)_mvd((int)x1);

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 12, to reflect the fact that 12 half words */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            x1 += 32;

            /*-----------------------------------------------------------*/
            /* First 2-Radix4's                                          */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_l2_0 - x_h2_0;    xl21_0 = x_l2_1 - x_h2_1;  */
            /*   xl20_1 = x_l2_2 - x_h2_2;    xl21_1 = x_l2_3 - x_h2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh1_1_xh0_1_xh1_0_xh0_0     = _davg2(xl1_3210, x_3210);
            xh21_1_xh20_1_xh21_0_xh20_0 = _davg2(xl2_3210, xh2_3210);
            xl1_1_xl0_1_xl1_0_xl0_0     = _dshr2(_dssub2(x_3210, xl1_3210), 1);
            xl20_1_xl21_1_xl20_0_xl21_0 = _dshr2(_dcrot270(_dssub2(xl2_3210, xh2_3210)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_3 = xl0_1 + xl21_1;      yt2_3 = xl1_1 + xl20_1;    */
            /*   xt1_2 = xl0_0 + xl21_0;      yt2_2 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_2 = xh0_0 - xh20_0;      xt0_3 = xh0_1 - xh20_1;    */
            /*   yt0_2 = xh1_0 - xh21_0;      yt0_3 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_2 = xl0_0 - xl21_0;      xt2_3 = xl0_1 - xl21_1;    */
            /*   yt1_2 = xl1_0 - xl20_0;      yt1_3 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_3o_x_2o_x_1o_x_0o     = _dsadd2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt2_1_xt1_1_yt2_0_xt1_0 = _dsadd2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);
            yt0_1_xt0_1_yt0_0_xt0_0 = _dssub2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt1_1_xt2_1_yt1_0_xt2_0 = _dssub2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);

            /*-----------------------------------------------------------*/
            /* Second 2-Radix4's                                         */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_l2_0 - x_h2_0;    xl21_0 = x_l2_1 - x_h2_1;  */
            /*   xl20_1 = x_l2_2 - x_h2_2;    xl21_1 = x_l2_3 - x_h2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh1_1_xh0_1_xh1_0_xh0_0     = _davg2(xl1_7654, x_7654);
            xh21_1_xh20_1_xh21_0_xh20_0 = _davg2(xl2_7654, xh2_7654);
            xl1_1_xl0_1_xl1_0_xl0_0     = _dshr2(_dssub2(x_7654, xl1_7654), 1);
            xl20_1_xl21_1_xl20_0_xl21_0 = _dshr2(_dcrot270(_dssub2(xl2_7654, xh2_7654)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_3 = xl0_1 + xl21_1;      yt2_3 = xl1_1 + xl20_1;    */
            /*   xt1_2 = xl0_0 + xl21_0;      yt2_2 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_2 = xh0_0 - xh20_0;      xt0_3 = xh0_1 - xh20_1;    */
            /*   yt0_2 = xh1_0 - xh21_0;      yt0_3 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_2 = xl0_0 - xl21_0;      xt2_3 = xl0_1 - xl21_1;    */
            /*   yt1_2 = xl1_0 - xl20_0;      yt1_3 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_7o_x_6o_x_5o_x_4o     = _dsadd2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt2_3_xt1_3_yt2_2_xt1_2 = _dsadd2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);
            yt0_3_xt0_3_yt0_2_xt0_2 = _dssub2(xh1_1_xh0_1_xh1_0_xh0_0, xh21_1_xh20_1_xh21_0_xh20_0);
            yt1_3_xt2_3_yt1_2_xt2_2 = _dssub2(xl1_1_xl0_1_xl1_0_xl0_0, xl20_1_xl21_1_xl20_0_xl21_0);
   
            /*-----------------------------------------------------------*/
            /* apply twiddle factor for first 2-Radix4's                 */
            /*-----------------------------------------------------------*/
            _amem8(&x2[0])  = x_3o_x_2o_x_1o_x_0o;
            _amem8(&x2[4])  = _dcmpyr1(yt0_1_xt0_1_yt0_0_xt0_0, co2si2_1_co2si2_0);
            _amem8(&x2[8])  = _dcmpyr1(yt2_1_xt1_1_yt2_0_xt1_0, co1si1_1_co1si1_0);
            _amem8(&x2[12]) = _dcmpyr1(yt1_1_xt2_1_yt1_0_xt2_0, co3si3_1_co3si3_0);

            /*-----------------------------------------------------------*/
            /* apply twiddle factor for second 2-Radix4's                */
            /*-----------------------------------------------------------*/
            _amem8(&x2[16]) = x_7o_x_6o_x_5o_x_4o;
            _amem8(&x2[20]) = _dcmpyr1(yt0_3_xt0_3_yt0_2_xt0_2, co2si2_1_co2si2_0);
            _amem8(&x2[24]) = _dcmpyr1(yt2_3_xt1_3_yt2_2_xt1_2, co1si1_1_co1si1_0);
            _amem8(&x2[28]) = _dcmpyr1(yt1_3_xt2_3_yt1_2_xt2_2, co3si3_1_co3si3_0);
        }
    }

    if (radix == 2)
        radix_2(ptr_x, ptr_y, n, offset, n_max);
    if (radix == 4)
        radix_4(ptr_x, ptr_y, n, offset, n_max);

    return;
}


void radix_2(
    short * restrict ptr_x,
    short * restrict ptr_y,
    int n,
    int offset,
    int n_max
)
{
    short * restrict ptr_x0;
    short * restrict y0, * restrict y1, * restrict y2, * restrict y3;

    int i, j, k, l0;
    long long x_32_x_10, x_76_x_54;
    long long yt1yt0_yt5yt4, yt3yt2_yt7yt6;

    /*-----------------------------------------------------------------*/
    /* Use index at offset/4 for bit reversal. Set up input , output   */
    /* pointers to store away the result. The last stage perfoms 1     */
    /* radix4 butterfly or 4 radix2 burtterflies per iteration.        */
    /*-----------------------------------------------------------------*/
    j = offset >> 2;
    ptr_x0 = ptr_x;

    y0 = ptr_y;
    y1 = y0 + (n_max >> 1);
    y2 = y1 + (n_max >> 1);
    y3 = y2 + (n_max >> 1);

    l0 = _norm(n_max) + 3;

    _nassert((int)(n) % 4  == 0);
    _nassert((int)(ptr_x0) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    _nassert((int)(y1) % 8 == 0);
    _nassert((int)(y2) % 8 == 0);
    _nassert((int)(y3) % 8 == 0);
    _nassert(n >= 16);
    #pragma MUST_ITERATE(2,,2);
    #pragma UNROLL(2);
    for (i = 0; i < n; i += 4) {
        /*--------------------------------------------------------*/
        /* The following macro performs bit reversal of index "j" */
        /* of size "l0" bits into index "k". This forms the index */
        /* with respect to pointers y0, y1, y2, y3 into which  4  */
        /* consecutive inputs map into.                           */
        /*--------------------------------------------------------*/
        k = _bitr(j) >> l0;
        j += 1;

        x_32_x_10 = _amem8(&ptr_x0[2*i]);
        x_76_x_54 = _amem8(&ptr_x0[2*i + 4]);
 
        /*--------------------------------------------------------*/
        /* Perform nest step of radix4 for lower leg. This will   */
        /* result in the correct results radix4 or radix2         */
        /*  yt2  = x_4 + x_6;       yt3  = x_5 + x_7;             */
        /*  yt6  = x_4 - x_6;       yt7  = x_5 - x_7;             */
        /*--------------------------------------------------------*/
        yt3yt2_yt7yt6 = _addsub2(_loll(x_76_x_54), _hill(x_76_x_54));

        /*---------------------------------------------------------*/
        /* Perform radix4 decomposition as a series of radix2 DIF  */
        /* compositions. This yields yt1:yt0 and yt5:yt4           */
        /*  yt0  = x_2 + x_0;       yt1  = x_3 + x_1;              */
        /*  yt4  = x_2 - x_0;       yt5  = x_3 - x_1;              */
        /*---------------------------------------------------------*/
        yt1yt0_yt5yt4 = _addsub2(_loll(x_32_x_10), _hill(x_32_x_10));

        /*---------------------------------------------------------*/
        /* Store out the results of the radix4 butterfly as 4 o/p  */
        /* or the result of 2 radix2 butterflies. These results    */
        /* are stored out using store words _amem4 intrinsic.      */
        /*---------------------------------------------------------*/
        _amem4(&y0[k]) = _hill(yt1yt0_yt5yt4);
        _amem4(&y1[k]) = _hill(yt3yt2_yt7yt6);
        _amem4(&y2[k]) = _loll(yt1yt0_yt5yt4);
        _amem4(&y3[k]) = _loll(yt3yt2_yt7yt6);
    }
}


void radix_4(
    short * restrict ptr_x,
    short * restrict ptr_y,
    int n,
    int offset,
    int n_max
)
{
    short * restrict ptr_x0;
    short * restrict y0, * restrict y1, * restrict y2, * restrict y3;

    int i, j, k, l0;
    long long x_32_x_10, x_76_x_54;
    long long x_h1_1_x_h0_1_x_h1_0_x_h0_0, x_l1_1_x_l0_1_x_l1_0_x_l0_0;
    long long yt1yt0_yt5yt4, yt3yt2_yt7yt6;

    /*-----------------------------------------------------------------*/
    /* Use index at offset/4 for bit reversal. Set up input , output   */
    /* pointers to store away the result. The last stage perfoms 1     */
    /* radix4 butterfly or 4 radix2 burtterflies per iteration.        */
    /*-----------------------------------------------------------------*/
    j = offset >> 2;
    ptr_x0 = ptr_x;

    y0 = ptr_y;
    y1 = y0 + (n_max >> 1);
    y2 = y1 + (n_max >> 1);
    y3 = y2 + (n_max >> 1);

    l0 = _norm(n_max) + 3;

    _nassert((int)(n) % 4  == 0);
    _nassert((int)(ptr_x0) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    _nassert((int)(y1) % 8 == 0);
    _nassert((int)(y2) % 8 == 0);
    _nassert((int)(y3) % 8 == 0);
    _nassert(n >= 16);
    #pragma MUST_ITERATE(2,,2);
    #pragma UNROLL(2);
    for (i = 0; i < n; i += 4) {
        /*--------------------------------------------------------*/
        /* The following macro performs bit reversal of index "j" */
        /* of size "l0" bits into index "k". This forms the index */
        /* with respect to pointers y0, y1, y2, y3 into which  4  */
        /* consecutive inputs map into.                           */
        /*--------------------------------------------------------*/
        k = _bitr(j) >> l0;
        j += 1;

        x_32_x_10 = _amem8(&ptr_x0[2*i]);
        x_76_x_54 = _amem8(&ptr_x0[2*i + 4]);

        /*--------------------------------------------------------*/
        /* Read in the input data, from the first eight locations.*/
        /* These results are transformed as radix 4               */
        /*  xl0_0  = x_0 - x_4; xl1_0  = x_1 - x_5;               */
        /*  xl0_1  = x_2 - x_6; xl1_1  = x_3 - x_7;               */
        /*  xh0_0  = x_0 + x_4; xh1_0  = x_1 + x_5;               */
        /*  xh0_1  = x_2 + x_6; xh1_1  = x_3 + x_7;               */
        /*--------------------------------------------------------*/
        x_h1_1_x_h0_1_x_h1_0_x_h0_0 = _dsadd2(x_32_x_10, x_76_x_54);
        x_l1_1_x_l0_1_x_l1_0_x_l0_0 = _dssub2(x_32_x_10, x_76_x_54);

        /*--------------------------------------------------------*/
        /* Perform nest step of radix4 for lower leg. This will   */
        /* result in the correct results radix4 or radix2         */
        /*  yt2  = xl0_0 + xl1_1; yt7  = xl1_0 + xl0_1;           */
        /*  yt6  = xl0_0 - xl1_1; yt3  = xl1_0 - xl0_1;           */
        /*--------------------------------------------------------*/
        yt3yt2_yt7yt6 = _addsub2(_loll(x_l1_1_x_l0_1_x_l1_0_x_l0_0),
                         _crot90(_hill(x_l1_1_x_l0_1_x_l1_0_x_l0_0)));

        /*---------------------------------------------------------*/
        /* Perform radix4 decomposition as a series of radix2 DIF  */
        /* compositions. This yields yt1:yt0 and yt5:yt4           */
        /*  yt0  = xh0_0 + xh0_1; yt1  = xh1_0 + xh1_1;            */
        /*  yt4  = xh0_0 - xh0_1; yt5  = xh1_0 - xh1_1;            */
        /*---------------------------------------------------------*/
        yt1yt0_yt5yt4 = _addsub2(_loll(x_h1_1_x_h0_1_x_h1_0_x_h0_0),
                                 _hill(x_h1_1_x_h0_1_x_h1_0_x_h0_0));

        /*---------------------------------------------------------*/
        /* Store out the results of the radix4 butterfly as 4 o/p  */
        /* or the result of 2 radix2 butterflies. These results    */
        /* are stored out using store words _amem4 intrinsic.      */
        /*---------------------------------------------------------*/
        _amem4(&y0[k]) = _hill(yt1yt0_yt5yt4);
        _amem4(&y1[k]) = _hill(yt3yt2_yt7yt6);
        _amem4(&y2[k]) = _loll(yt1yt0_yt5yt4);
        _amem4(&y3[k]) = _loll(yt3yt2_yt7yt6);
    }
}
#else
void DSP_fft16x16r (
    int n,
    short * restrict ptr_x,
    const short * restrict ptr_w,
    short * restrict ptr_y,
    int radix,
    int offset,
    int n_max
)
{
    short * restrict x, * restrict x1, * restrict x2;
    const short * restrict tw;
    long long *restrict Twiddles;

    long long x_0123, x_4567, xl2_0123, xl2_4567, xl1_0123, xl1_4567, xh2_0123, xh2_4567;
    long long co10si10_co11si11, co12si12_co13si13, co12si12_co13si13_tmp;
    long long co1si1_0_co1si1_1, co2si2_0_co2si2_1, co3si3_0_co3si3_1;
    long long xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1;
    long long xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1;
    long long x_0o_x_1o_x_2o_x_3o, xt1_0_yt2_0_xt1_1_yt2_1, xt0_0_yt0_0_xt0_1_yt0_1, xt2_0_yt1_0_xt2_1_yt1_1;
    long long x_4o_x_5o_x_6o_x_7o, xt1_2_yt2_2_xt1_3_yt2_3, xt0_2_yt0_2_xt0_3_yt0_3, xt2_2_yt1_2_xt2_3_yt1_3;  

    int j, i, l1, l2, h2, fft_jmp, tw_jmp;
    int predj, tw_offset, stride, loop_limit, last_r4;

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
    stride = n;
    tw_offset = 0;
    fft_jmp = 6 * stride;
    tw_jmp  = 2 * stride;

    /*----------------------------------------------------------------------*/
    /* When radix == 2, last radix 4 stage needs to be treated differently  */
    /*----------------------------------------------------------------------*/
    loop_limit = radix;
    last_r4    = 0;
    if (radix == 2) {
      loop_limit = 8;
      last_r4    = 1;
    }

    _nassert(stride > 4);
    #pragma MUST_ITERATE(1,,1);

    while (stride > loop_limit) {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "tw" is pointing to the correct location within the */
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
        tw = ptr_w + tw_offset;
        Twiddles = (void*)tw;
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
        /* fft_jmp amount. In addition the following code is unrolled to  */
        /* perform "4" radix4 butterflies in parallel.                    */
        /*----------------------------------------------------------------*/
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        _nassert(n >= 16);
        #pragma MUST_ITERATE(1,,1);
        for (i = 0; i < n; i += 16) {

            /*-----------------------------------------------------------*/
            /* Read in complex input for the butterflies.                */
            /*-----------------------------------------------------------*/
            x_0123   = _amem8(&x[0]);
            x_4567   = _amem8(&x[4]);
            xl1_0123 = _amem8(&x[l1]);
            xl1_4567 = _amem8(&x[l1+4]);
            xl2_0123 = _amem8(&x[l2]);
            xl2_4567 = _amem8(&x[l2+4]);
            xh2_0123 = _amem8(&x[h2]);
            xh2_4567 = _amem8(&x[h2+4]);

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x2 = (short *)_mvd((int)x);

            /*-----------------------------------------------------------*/
            /* Read in complex input for twiddle factors.                */
            /*-----------------------------------------------------------*/
            co10si10_co11si11 = *Twiddles++;
            co12si12_co13si13_tmp = *Twiddles++;
            co12si12_co13si13 = _dmvd(_hill(co12si12_co13si13_tmp), _loll(co12si12_co13si13_tmp));

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 24, to reflect the fact that 24 half words */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 8. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            j += 24;
            x += 8;

            predj = (fft_jmp - j);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;
            if (!predj) Twiddles= (void*)tw;

            /*-----------------------------------------------------------*/
            /* First 2-Radix4's                                          */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_h2_0 - x_l2_0;    xl21_0 = x_h2_1 - x_l2_1;  */
            /*   xl20_1 = x_h2_2 - x_l2_2;    xl21_1 = x_h2_3 - x_l2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh0_0_xh1_0_xh0_1_xh1_1     = _davg2(xl1_0123, x_0123);
            xh20_0_xh21_0_xh20_1_xh21_1 = _davg2(xl2_0123, xh2_0123);
            xl0_0_xl1_0_xl0_1_xl1_1     = _dshr2(_dssub2(x_0123, xl1_0123), 1);
            xl21_0_xl20_0_xl21_1_xl20_1 = _dshr2(_dcrot90(_dssub2(xl2_0123, xh2_0123)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_1 = xl0_1 + xl21_1;      yt2_1 = xl1_1 + xl20_1;    */
            /*   xt1_0 = xl0_0 + xl21_0;      yt2_0 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_0 = xh0_0 - xh20_0;      xt0_1 = xh0_1 - xh20_1;    */
            /*   yt0_0 = xh1_0 - xh21_0;      yt0_1 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_0 = xl0_0 - xl21_0;      xt2_1 = xl0_1 - xl21_1;    */
            /*   yt1_0 = xl1_0 - xl20_0;      yt1_1 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_0o_x_1o_x_2o_x_3o     = _dsadd2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt1_0_yt2_0_xt1_1_yt2_1 = _dsadd2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);
            xt0_0_yt0_0_xt0_1_yt0_1 = _dssub2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt2_0_yt1_0_xt2_1_yt1_1 = _dssub2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);

            /*-----------------------------------------------------------*/
            /* Second 2-Radix4's                                         */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_h2_0 - x_l2_0;    xl21_0 = x_h2_1 - x_l2_1;  */
            /*   xl20_1 = x_h2_2 - x_l2_2;    xl21_1 = x_h2_3 - x_l2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh0_0_xh1_0_xh0_1_xh1_1     = _davg2(xl1_4567, x_4567);
            xh20_0_xh21_0_xh20_1_xh21_1 = _davg2(xl2_4567, xh2_4567);
            xl0_0_xl1_0_xl0_1_xl1_1     = _dshr2(_dssub2(x_4567, xl1_4567), 1);
            xl21_0_xl20_0_xl21_1_xl20_1 = _dshr2(_dcrot90(_dssub2(xl2_4567, xh2_4567)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_3 = xl0_1 + xl21_1;      yt2_3 = xl1_1 + xl20_1;    */
            /*   xt1_2 = xl0_0 + xl21_0;      yt2_2 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_2 = xh0_0 - xh20_0;      xt0_3 = xh0_1 - xh20_1;    */
            /*   yt0_2 = xh1_0 - xh21_0;      yt0_3 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_2 = xl0_0 - xl21_0;      xt2_3 = xl0_1 - xl21_1;    */
            /*   yt1_2 = xl1_0 - xl20_0;      yt1_3 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_4o_x_5o_x_6o_x_7o     = _dsadd2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt1_2_yt2_2_xt1_3_yt2_3 = _dsadd2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);
            xt0_2_yt0_2_xt0_3_yt0_3 = _dssub2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt2_2_yt1_2_xt2_3_yt1_3 = _dssub2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);
   
            /*-----------------------------------------------------------*/
            /* Compute and apply twiddle factor for first 2-Radix4's     */
            /*-----------------------------------------------------------*/
            co2si2_0_co2si2_1 = _dcmpyr1(co10si10_co11si11, co10si10_co11si11);
            co3si3_0_co3si3_1 = _dcmpyr1(co10si10_co11si11, co2si2_0_co2si2_1);
            _amem8(&x2[0])    = x_0o_x_1o_x_2o_x_3o;
            _amem8(&x2[l1])   = _dcmpyr1(xt1_0_yt2_0_xt1_1_yt2_1, co10si10_co11si11);
            _amem8(&x2[h2])   = _dcmpyr1(xt0_0_yt0_0_xt0_1_yt0_1, co2si2_0_co2si2_1);
            _amem8(&x2[l2])   = _dcmpyr1(xt2_0_yt1_0_xt2_1_yt1_1, co3si3_0_co3si3_1);
   
            /*-----------------------------------------------------------*/
            /* Compute and apply twiddle factor for second 2-Radix4's    */
            /*-----------------------------------------------------------*/
            co2si2_0_co2si2_1 = _dcmpyr1(co12si12_co13si13, co12si12_co13si13);
            co3si3_0_co3si3_1 = _dcmpyr1(co12si12_co13si13, co2si2_0_co2si2_1);
            _amem8(&x2[4])    = x_4o_x_5o_x_6o_x_7o;
            _amem8(&x2[l1+4]) = _dcmpyr1(xt1_2_yt2_2_xt1_3_yt2_3, co12si12_co13si13);
            _amem8(&x2[h2+4]) = _dcmpyr1(xt0_2_yt0_2_xt0_3_yt0_3, co2si2_0_co2si2_1);
            _amem8(&x2[l2+4]) = _dcmpyr1(xt2_2_yt1_2_xt2_3_yt1_3, co3si3_0_co3si3_1);

        }
    }

    if (last_r4) {

        /*---------------------------------------------------------------*/
        /*  Last stage of Radix4's is handled here because               */
        /*  it has different pointer offsets                             */
        /*---------------------------------------------------------------*/
        x1 = ptr_x;
        tw = ptr_w + tw_offset;
        Twiddles = (void*)tw;

        /*---------------------------------------------------------------*/
        /* Load and compute twiddle factors                              */
        /*---------------------------------------------------------------*/
        co1si1_0_co1si1_1 = *Twiddles;
        co2si2_0_co2si2_1 = _dcmpyr1(co1si1_0_co1si1_1, co1si1_0_co1si1_1);
        co3si3_0_co3si3_1 = _dcmpyr1(co1si1_0_co1si1_1, co2si2_0_co2si2_1);

        _nassert(n >= 16);
        #pragma MUST_ITERATE(1,,1);
        for (i = 0; i < n; i += 16) {

            /*-----------------------------------------------------------*/
            /* Read in complex input for the butterflies.                */
            /*-----------------------------------------------------------*/
            x_0123   = _amem8(&x1[0]);
            xl1_0123 = _amem8(&x1[8]);
            xl2_0123 = _amem8(&x1[12]);
            xh2_0123 = _amem8(&x1[4]);
            x_4567   = _amem8(&x1[16]);
            xl1_4567 = _amem8(&x1[24]);
            xl2_4567 = _amem8(&x1[28]);
            xh2_4567 = _amem8(&x1[20]);

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x2 = (short *)_mvd((int)x1);

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 12, to reflect the fact that 12 half words */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            x1 += 32;

            /*-----------------------------------------------------------*/
            /* First 2-Radix4's                                          */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_l2_0 - x_h2_0;    xl21_0 = x_l2_1 - x_h2_1;  */
            /*   xl20_1 = x_l2_2 - x_h2_2;    xl21_1 = x_l2_3 - x_h2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh0_0_xh1_0_xh0_1_xh1_1     = _davg2(xl1_0123, x_0123);
            xh20_0_xh21_0_xh20_1_xh21_1 = _davg2(xl2_0123, xh2_0123);
            xl0_0_xl1_0_xl0_1_xl1_1     = _dshr2(_dssub2(x_0123, xl1_0123), 1);
            xl21_0_xl20_0_xl21_1_xl20_1 = _dshr2(_dcrot90(_dssub2(xl2_0123, xh2_0123)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_3 = xl0_1 + xl21_1;      yt2_3 = xl1_1 + xl20_1;    */
            /*   xt1_2 = xl0_0 + xl21_0;      yt2_2 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_2 = xh0_0 - xh20_0;      xt0_3 = xh0_1 - xh20_1;    */
            /*   yt0_2 = xh1_0 - xh21_0;      yt0_3 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_2 = xl0_0 - xl21_0;      xt2_3 = xl0_1 - xl21_1;    */
            /*   yt1_2 = xl1_0 - xl20_0;      yt1_3 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_0o_x_1o_x_2o_x_3o     = _dsadd2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt1_0_yt2_0_xt1_1_yt2_1 = _dsadd2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);
            xt0_0_yt0_0_xt0_1_yt0_1 = _dssub2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt2_0_yt1_0_xt2_1_yt1_1 = _dssub2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);

            /*-----------------------------------------------------------*/
            /* Second 2-Radix4's                                         */
            /*                                                           */
            /*   xh0_0 = x_0 + x_l1_0;        xh1_0 = x_1 + x_l1_1;      */
            /*   xh0_1 = x_2 + x_l1_2;        xh1_1 = x_3 + x_l1_3;      */
            /*                                                           */
            /*   xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;  */
            /*   xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;  */
            /*                                                           */
            /*   xl0_0 = x_0 - x_l1_0;        xl1_0 = x_1 - x_l1_1;      */
            /*   xl0_1 = x_2 - x_l1_2;        xl1_1 = x_3 - x_l1_3;      */
            /*                                                           */
            /*   xl20_0 = x_l2_0 - x_h2_0;    xl21_0 = x_l2_1 - x_h2_1;  */
            /*   xl20_1 = x_l2_2 - x_h2_2;    xl21_1 = x_l2_3 - x_h2_3;  */
            /*                                                           */
            /*-----------------------------------------------------------*/

            xh0_0_xh1_0_xh0_1_xh1_1     = _davg2(xl1_4567, x_4567);
            xh20_0_xh21_0_xh20_1_xh21_1 = _davg2(xl2_4567, xh2_4567);
            xl0_0_xl1_0_xl0_1_xl1_1     = _dshr2(_dssub2(x_4567, xl1_4567), 1);
            xl21_0_xl20_0_xl21_1_xl20_1 = _dshr2(_dcrot90(_dssub2(xl2_4567, xh2_4567)), 1);

            /*-----------------------------------------------------------*/
            /*   x0[0] = xh0_0 + xh20_0;      x0[2] = xh0_1 + xh20_1;    */
            /*   x0[1] = xh1_0 + xh21_0;      x0[3] = xh1_1 + xh21_1;    */
            /*                                                           */
            /*   xt1_3 = xl0_1 + xl21_1;      yt2_3 = xl1_1 + xl20_1;    */
            /*   xt1_2 = xl0_0 + xl21_0;      yt2_2 = xl1_0 + xl20_0;    */
            /*                                                           */
            /*   xt0_2 = xh0_0 - xh20_0;      xt0_3 = xh0_1 - xh20_1;    */
            /*   yt0_2 = xh1_0 - xh21_0;      yt0_3 = xh1_1 - xh21_1;    */
            /*                                                           */
            /*   xt2_2 = xl0_0 - xl21_0;      xt2_3 = xl0_1 - xl21_1;    */
            /*   yt1_2 = xl1_0 - xl20_0;      yt1_3 = xl1_1 - xl20_1;    */
            /*-----------------------------------------------------------*/

            x_4o_x_5o_x_6o_x_7o     = _dsadd2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt1_2_yt2_2_xt1_3_yt2_3 = _dsadd2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);
            xt0_2_yt0_2_xt0_3_yt0_3 = _dssub2(xh0_0_xh1_0_xh0_1_xh1_1, xh20_0_xh21_0_xh20_1_xh21_1);
            xt2_2_yt1_2_xt2_3_yt1_3 = _dssub2(xl0_0_xl1_0_xl0_1_xl1_1, xl21_0_xl20_0_xl21_1_xl20_1);
   
            /*-----------------------------------------------------------*/
            /* apply twiddle factor for first 2-Radix4's                 */
            /*-----------------------------------------------------------*/
            _amem8(&x2[0])  = x_0o_x_1o_x_2o_x_3o;
            _amem8(&x2[4])  = _dcmpyr1(xt0_0_yt0_0_xt0_1_yt0_1, co2si2_0_co2si2_1);
            _amem8(&x2[8])  = _dcmpyr1(xt1_0_yt2_0_xt1_1_yt2_1, co1si1_0_co1si1_1);
            _amem8(&x2[12]) = _dcmpyr1(xt2_0_yt1_0_xt2_1_yt1_1, co3si3_0_co3si3_1);

            /*-----------------------------------------------------------*/
            /* apply twiddle factor for second 2-Radix4's                */
            /*-----------------------------------------------------------*/
            _amem8(&x2[16]) = x_4o_x_5o_x_6o_x_7o;
            _amem8(&x2[20]) = _dcmpyr1(xt0_2_yt0_2_xt0_3_yt0_3, co2si2_0_co2si2_1);
            _amem8(&x2[24]) = _dcmpyr1(xt1_2_yt2_2_xt1_3_yt2_3, co1si1_0_co1si1_1);
            _amem8(&x2[28]) = _dcmpyr1(xt2_2_yt1_2_xt2_3_yt1_3, co3si3_0_co3si3_1);
        }
    }

    if (radix == 2)
        radix_2(ptr_x, ptr_y, n, offset, n_max);
    if (radix == 4)
        radix_4(ptr_x, ptr_y, n, offset, n_max);

    return;
}


void radix_2(
    short * restrict ptr_x,
    short * restrict ptr_y,
    int n,
    int offset,
    int n_max
)
{
    short * restrict ptr_x0;
    short * restrict y0, * restrict y1, * restrict y2, * restrict y3;

    int i, j, k, l0;
    long long x_01_x_23, x_45_x_67;
    long long yt0yt1_yt4yt5, yt2yt3_yt6yt7;

    /*-----------------------------------------------------------------*/
    /* Use index at offset/4 for bit reversal. Set up input , output   */
    /* pointers to store away the result. The last stage perfoms 1     */
    /* radix4 butterfly or 4 radix2 burtterflies per iteration.        */
    /*-----------------------------------------------------------------*/
    j = offset >> 2;
    ptr_x0 = ptr_x;

    y0 = ptr_y;
    y1 = y0 + (n_max >> 1);
    y2 = y1 + (n_max >> 1);
    y3 = y2 + (n_max >> 1);

    l0 = _norm(n_max) + 3;

    _nassert((int)(n) % 4  == 0);
    _nassert((int)(ptr_x0) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    _nassert((int)(y1) % 8 == 0);
    _nassert((int)(y2) % 8 == 0);
    _nassert((int)(y3) % 8 == 0);
    _nassert(n >= 16);
    #pragma MUST_ITERATE(2,,2);
    #pragma UNROLL(2);
    for (i = 0; i < n; i += 4) {
        /*--------------------------------------------------------*/
        /* The following macro performs bit reversal of index "j" */
        /* of size "l0" bits into index "k". This forms the index */
        /* with respect to pointers y0, y1, y2, y3 into which  4  */
        /* consecutive inputs map into.                           */
        /*--------------------------------------------------------*/
        k = _bitr(j) >> l0;
        j += 1;

        x_01_x_23 = _amem8(&ptr_x0[2*i]);
        x_45_x_67 = _amem8(&ptr_x0[2*i + 4]);
 
        /*--------------------------------------------------------*/
        /* Perform nest step of radix4 for lower leg. This will   */
        /* result in the correct results radix4 or radix2         */
        /*  yt2  = x_4 + x_6;       yt3  = x_5 + x_7;             */
        /*  yt6  = x_4 - x_6;       yt7  = x_5 - x_7;             */
        /*--------------------------------------------------------*/
        yt2yt3_yt6yt7 = _addsub2(_hill(x_45_x_67), _loll(x_45_x_67));

        /*---------------------------------------------------------*/
        /* Perform radix4 decomposition as a series of radix2 DIF  */
        /* compositions. This yields yt1:yt0 and yt5:yt4           */
        /*  yt0  = x_2 + x_0;       yt1  = x_3 + x_1;              */
        /*  yt4  = x_2 - x_0;       yt5  = x_3 - x_1;              */
        /*---------------------------------------------------------*/
        yt0yt1_yt4yt5 = _addsub2(_hill(x_01_x_23), _loll(x_01_x_23));

        /*---------------------------------------------------------*/
        /* Store out the results of the radix4 butterfly as 4 o/p  */
        /* or the result of 2 radix2 butterflies. These results    */
        /* are stored out using store words _amem4 intrinsic.      */
        /*---------------------------------------------------------*/
        _amem4(&y0[k]) = _hill(yt0yt1_yt4yt5);
        _amem4(&y1[k]) = _hill(yt2yt3_yt6yt7);
        _amem4(&y2[k]) = _loll(yt0yt1_yt4yt5);
        _amem4(&y3[k]) = _loll(yt2yt3_yt6yt7);
    }
}


void radix_4(
    short * restrict ptr_x,
    short * restrict ptr_y,
    int n,
    int offset,
    int n_max
)
{
    short * restrict ptr_x0;
    short * restrict y0, * restrict y1, * restrict y2, * restrict y3;

    int i, j, k, l0;
    long long x_01_x_23, x_45_x_67;
    long long x_h0_0_x_h1_0_x_h0_1_x_h1_1, x_l0_0_x_l1_0_x_l0_1_x_l1_1;
    long long yt0yt1_yt4yt5, yt2yt3_yt6yt7;

    /*-----------------------------------------------------------------*/
    /* Use index at offset/4 for bit reversal. Set up input , output   */
    /* pointers to store away the result. The last stage perfoms 1     */
    /* radix4 butterfly or 4 radix2 burtterflies per iteration.        */
    /*-----------------------------------------------------------------*/
    j = offset >> 2;
    ptr_x0 = ptr_x;

    y0 = ptr_y;
    y1 = y0 + (n_max >> 1);
    y2 = y1 + (n_max >> 1);
    y3 = y2 + (n_max >> 1);

    l0 = _norm(n_max) + 3;

    _nassert((int)(n) % 4  == 0);
    _nassert((int)(ptr_x0) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    _nassert((int)(y1) % 8 == 0);
    _nassert((int)(y2) % 8 == 0);
    _nassert((int)(y3) % 8 == 0);
    _nassert(n >= 16);
    #pragma MUST_ITERATE(2,,2);
    #pragma UNROLL(2);
    for (i = 0; i < n; i += 4) {
        /*--------------------------------------------------------*/
        /* The following macro performs bit reversal of index "j" */
        /* of size "l0" bits into index "k". This forms the index */
        /* with respect to pointers y0, y1, y2, y3 into which  4  */
        /* consecutive inputs map into.                           */
        /*--------------------------------------------------------*/
        k = _bitr(j) >> l0;
        j += 1;

        x_01_x_23 = _amem8(&ptr_x0[2*i]);
        x_45_x_67 = _amem8(&ptr_x0[2*i + 4]);

        /*--------------------------------------------------------*/
        /* Read in the input data, from the first eight locations.*/
        /* These results are transformed as radix 4               */
        /*  xl0_0  = x_0 - x_4; xl1_0  = x_1 - x_5;               */
        /*  xl0_1  = x_2 - x_6; xl1_1  = x_3 - x_7;               */
        /*  xh0_0  = x_0 + x_4; xh1_0  = x_1 + x_5;               */
        /*  xh0_1  = x_2 + x_6; xh1_1  = x_3 + x_7;               */
        /*--------------------------------------------------------*/
        x_h0_0_x_h1_0_x_h0_1_x_h1_1 = _dsadd2(x_01_x_23, x_45_x_67);
        x_l0_0_x_l1_0_x_l0_1_x_l1_1 = _dssub2(x_01_x_23, x_45_x_67);

        /*--------------------------------------------------------*/
        /* Perform nest step of radix4 for lower leg. This will   */
        /* result in the correct results radix4 or radix2         */
        /*  yt2  = xl0_0 + xl1_1; yt7  = xl1_0 + xl0_1;           */
        /*  yt6  = xl0_0 - xl1_1; yt3  = xl1_0 - xl0_1;           */
        /*--------------------------------------------------------*/
        yt2yt3_yt6yt7 = _addsub2(_hill(x_l0_0_x_l1_0_x_l0_1_x_l1_1),
                         _crot270(_loll(x_l0_0_x_l1_0_x_l0_1_x_l1_1)));

        /*---------------------------------------------------------*/
        /* Perform radix4 decomposition as a series of radix2 DIF  */
        /* compositions. This yields yt1:yt0 and yt5:yt4           */
        /*  yt0  = xh0_0 + xh0_1; yt1  = xh1_0 + xh1_1;            */
        /*  yt4  = xh0_0 - xh0_1; yt5  = xh1_0 - xh1_1;            */
        /*---------------------------------------------------------*/
        yt0yt1_yt4yt5 = _addsub2(_hill(x_h0_0_x_h1_0_x_h0_1_x_h1_1),
                                 _loll(x_h0_0_x_h1_0_x_h0_1_x_h1_1));

        /*---------------------------------------------------------*/
        /* Store out the results of the radix4 butterfly as 4 o/p  */
        /* or the result of 2 radix2 butterflies. These results    */
        /* are stored out using store words _amem4 intrinsic.      */
        /*---------------------------------------------------------*/
        _amem4(&y0[k]) = _hill(yt0yt1_yt4yt5);
        _amem4(&y1[k]) = _hill(yt2yt3_yt6yt7);
        _amem4(&y2[k]) = _loll(yt0yt1_yt4yt5);
        _amem4(&y3[k]) = _loll(yt2yt3_yt6yt7);
    }
}
#endif
/* ======================================================================== */
/*  End of file: DSP_fft16x16r.c                                            */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

