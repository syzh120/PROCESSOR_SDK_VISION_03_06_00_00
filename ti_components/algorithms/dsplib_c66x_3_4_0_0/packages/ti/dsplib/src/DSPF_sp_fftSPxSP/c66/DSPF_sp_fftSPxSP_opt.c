/* ======================================================================= */
/* DSPF_sp_fftSPxSP_opt.c -- Forward FFT with Mixed Radix                  */
/*                 Intrinsic C Implementation                              */
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

#pragma CODE_SECTION(DSPF_sp_fftSPxSP_opt, ".text:Intrinsic");

#include "DSPF_sp_fftSPxSP_opt.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_fftSPxSP_opt (int N, float *ptr_x, float *ptr_w, float *ptr_y,
                       unsigned char *brev, int n_min, int offset, int n_max)
{

    int i, j, k, l1, l2, h2, predj, tw_offset, stride, fft_jmp, radix;

    float yt2, yt3, yt6, yt7;
    float xt1_0, yt2_0, xt1_1, yt2_1, xt2_0, yt1_0, xt2_1, yt1_1;
    float * restrict x, * restrict x2, * restrict w;
    float * restrict y0, * restrict y1, * restrict y2, * restrict y3;

    __float2_t xh21_0_xh20_0, xh21_1_xh20_1, xh1_0_xh0_0, xh1_1_xh0_1;
    __float2_t xl21_0_xl20_0, xl21_1_xl20_1, xl1_0_xl0_0, xl1_1_xl0_1;
    __float2_t yt0_0_xt0_0,   yt0_1_xt0_1,   yt1_0_xt1_0;
    __float2_t yt1_1_xt1_1,   yt2_0_xt2_0,   yt2_1_xt2_1;
    __float2_t x_1o_x_0o,     xl1_1o_xl1_0o, x_3o_x_2o,     xl1_3o_xl1_2o;
    __float2_t xh2_1o_xh2_0o, xl2_1o_xl2_0o, xh2_3o_xh2_2o, xl2_3o_xl2_2o;
    __float2_t x_l1_10, x_l1_32, x_l2_10, x_l2_32, x_h2_10, x_h2_32;
    __float2_t co10_si10, co20_si20, co30_si30, co11_si11, co21_si21, co31_si31;
    __float2_t x_10, x_32, x_54, x_76, yt_10, yt_32, yt_54, yt_76;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 6*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/ 
    radix     = n_min;
    stride    = N;
    tw_offset = 0;
    fft_jmp   = 6 * stride;

    _nassert(stride > 4);
    while (stride > radix)
    {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 6 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          6 N/4               1               */
        /*  2                          6 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/  
        j =  0;
        fft_jmp >>= 2;

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
        w = ptr_w + tw_offset;
        tw_offset += fft_jmp;

        /*-----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies,  */
        /* within a given stage. Recall that there are logN to base 4      */
        /* stages. Certain butterflies share the twiddle factors. These    */
        /* are grouped together. On the very first stage there are no      */
        /* butterflies that share the twiddle factor, all N/4 butter-      */
        /* flies have different factors. On the next stage two sets of     */
        /* N/8 butterflies share the same twiddle factor. Hence after      */
        /* half the butterflies are performed, j the index into the        */
        /* factor array resets to 0, and the twiddle factors are reused.   */
        /* When this happens, the data pointer 'x' is incremented by the   */
        /* fft_jmp amount.                                                 */
        /*-----------------------------------------------------------------*/
        _nassert((int)(w) % 8 == 0);
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        _nassert(N >= 8);

        for (i = 0; i < (N >> 3); i++) {

            /*-------------------------------------------------------------*/
            /*  Read the first six twiddle factor values. This loop        */
            /*  computes two radix 4 butterflies at a time.                */
            /* si10 = w[0] co10 = w[1]  si20 = w[2]  co20 = w[3]           */
            /* si30 = w[4] co30 = w[5]  si11 = w[6]  co11 = w[7]           */
            /* si21 = w[8] co21 = w[9]  si31 = w[a]  co31 = w[b]           */
            /*-------------------------------------------------------------*/
            co10_si10 = _amem8_f2_const(&w[j]);
            co20_si20 = _amem8_f2_const(&w[j+2]);
            co30_si30 = _amem8_f2_const(&w[j+4]);

            co11_si11 = _amem8_f2_const(&w[j+6]);
            co21_si21 = _amem8_f2_const(&w[j+8]);
            co31_si31 = _amem8_f2_const(&w[j+10]);

            /*-------------------------------------------------------------*/
            /* Read in the data elements for the eight inputs of two       */
            /* radix4 butterflies.                                         */
            /*  x[0]       x[1]       x[2]       x[3]                      */
            /*  x[h2+0]    x[h2+1]    x[h2+2]    x[h2+3]                   */
            /*  x[l1+0]    x[l1+1]    x[l1+2]    x[l1+3]                   */
            /*  x[l2+0]    x[l2+1]    x[l2+2]    x[l2+3]                   */
            /*-------------------------------------------------------------*/
            x_10    = _amem8_f2(&x[0]);
            x_32    = _amem8_f2(&x[2]);
            x_l1_10 = _amem8_f2(&x[l1]);
            x_l1_32 = _amem8_f2(&x[l1 + 2]);
            x_l2_10 = _amem8_f2(&x[l2]);
            x_l2_32 = _amem8_f2(&x[l2 + 2]);
            x_h2_10 = _amem8_f2(&x[h2]);
            x_h2_32 = _amem8_f2(&x[h2 + 2]);

            /*-------------------------------------------------------------*/
            /* xh0_0 = x[0] + x[l1];    xh1_0 = x[1] + x[l1+1]             */
            /* xh0_1 = x[2] + x[l1+2];  xh1_1 = x[3] + x[l1+3]             */
            /* xl0_0 = x[0] - x[l1];    xl1_0 = x[1] - x[l1+1]             */
            /* xl0_1 = x[2] - x[l1+2];  xl1_1 = x[3] - x[l1+3]             */
            /*-------------------------------------------------------------*/
            xh1_0_xh0_0 = _daddsp(x_10, x_l1_10);
            xl1_0_xl0_0 = _dsubsp(x_10, x_l1_10);
            xh1_1_xh0_1 = _daddsp(x_32, x_l1_32);
            xl1_1_xl0_1 = _dsubsp(x_32, x_l1_32);

            /*-------------------------------------------------------------*/
            /* xh20_0 = x[h2  ] + x[l2  ]; xh21_0 = x[h2+1] + x[l2+1]      */
            /* xh20_1 = x[h2+2] + x[l2+2]; xh21_1 = x[h2+3] + x[l2+3]      */
            /* xl20_0 = x[h2  ] - x[l2  ]; xl21_0 = x[h2+1] - x[l2+1]      */
            /* xl20_1 = x[h2+2] - x[l2+2]; xl21_1 = x[h2+3] - x[l2+3]      */
            /*-------------------------------------------------------------*/
            xh21_0_xh20_0 = _daddsp(x_h2_10, x_l2_10);
            xl21_0_xl20_0 = _dsubsp(x_h2_10, x_l2_10);
            xh21_1_xh20_1 = _daddsp(x_h2_32, x_l2_32);
            xl21_1_xl20_1 = _dsubsp(x_h2_32, x_l2_32);

            /*-------------------------------------------------------------*/
            /*    x_0o  = xh0_0 + xh20_0;    x_1o  = xh1_0 + xh21_0;       */
            /*    x_2o  = xh0_1 + xh20_1;    x_3o  = xh1_1 + xh21_1;       */
            /*    xt0_0 = xh0_0 - xh20_0;    yt0_0 = xh1_0 - xh21_0;       */
            /*    xt0_1 = xh0_1 - xh20_1;    yt0_1 = xh1_1 - xh21_1;       */
            /*-------------------------------------------------------------*/
            x_1o_x_0o = _daddsp(xh1_0_xh0_0, xh21_0_xh20_0);
            x_3o_x_2o = _daddsp(xh1_1_xh0_1, xh21_1_xh20_1);

            yt0_0_xt0_0 = _dsubsp(xh1_0_xh0_0, xh21_0_xh20_0);
            yt0_1_xt0_1 = _dsubsp(xh1_1_xh0_1, xh21_1_xh20_1);

            /*-------------------------------------------------------------*/
            /*    xt1_0 = xl0_0 + xl21_0;    yt2_0 = xl1_0 + xl20_0;       */
            /*    xt1_1 = xl0_1 + xl21_1;    yt2_1 = xl1_1 + xl20_1;       */
            /*    xt2_0 = xl0_0 - xl21_0;    yt1_0 = xl1_0 - xl20_0;       */
            /*    xt2_1 = xl0_1 - xl21_1;    yt1_1 = xl1_1 - xl20_1;       */
            /*-------------------------------------------------------------*/
            xt1_0 = _lof2(xl1_0_xl0_0) + _hif2(xl21_0_xl20_0);
            yt2_0 = _hif2(xl1_0_xl0_0) + _lof2(xl21_0_xl20_0);
            xt1_1 = _lof2(xl1_1_xl0_1) + _hif2(xl21_1_xl20_1);
            yt2_1 = _hif2(xl1_1_xl0_1) + _lof2(xl21_1_xl20_1);
            xt2_0 = _lof2(xl1_0_xl0_0) - _hif2(xl21_0_xl20_0);
            yt1_0 = _hif2(xl1_0_xl0_0) - _lof2(xl21_0_xl20_0);
            xt2_1 = _lof2(xl1_1_xl0_1) - _hif2(xl21_1_xl20_1);
            yt1_1 = _hif2(xl1_1_xl0_1) - _lof2(xl21_1_xl20_1);

            yt1_0_xt1_0 = _ftof2(yt1_0, xt1_0);
            yt1_1_xt1_1 = _ftof2(yt1_1, xt1_1);
            yt2_0_xt2_0 = _ftof2(yt2_0, xt2_0);
            yt2_1_xt2_1 = _ftof2(yt2_1, xt2_1);

            /*-------------------------------------------------------------*/
            /*   x2[h2  ] = (si10 * yt1_0 + co10 * xt1_0)                  */
            /*   x2[h2+1] = (co10 * yt1_0 - si10 * xt1_0)                  */
            /*   x2[h2+2] = (si11 * yt1_1 + co11 * xt1_1)                  */
            /*   x2[h2+3] = (co11 * yt1_1 - si11 * xt1_1)                  */
            /*-------------------------------------------------------------*/
            xl1_1o_xl1_0o = _complex_mpysp(co10_si10, yt1_0_xt1_0);
            xl1_3o_xl1_2o = _complex_mpysp(co11_si11, yt1_1_xt1_1);

            /*-------------------------------------------------------------*/
            /*   x2[l1  ] = (si20 * yt0_0 + co20 * xt0_0)                  */
            /*   x2[l1+1] = (co20 * yt0_0 - si20 * xt0_0)                  */
            /*   x2[l1+2] = (si21 * yt0_1 + co21 * xt0_1)                  */
            /*   x2[l1+3] = (co21 * yt0_1 - si21 * xt0_1)                  */
            /*-------------------------------------------------------------*/
            xh2_1o_xh2_0o = _complex_mpysp(co20_si20, yt0_0_xt0_0);
            xh2_3o_xh2_2o = _complex_mpysp(co21_si21, yt0_1_xt0_1);

            /*-------------------------------------------------------------*/
            /*   x2[l2  ] = (si30 * yt2_0 + co30 * xt2_0)                  */
            /*   x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0)                  */
            /*   x2[l2+2] = (si31 * yt2_1 + co31 * xt2_1)                  */
            /*   x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1)                  */
            /*-------------------------------------------------------------*/
            xl2_1o_xl2_0o = _complex_mpysp(co30_si30, yt2_0_xt2_0);
            xl2_3o_xl2_2o = _complex_mpysp(co31_si31, yt2_1_xt2_1);

            /*-------------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"          */
            /*-------------------------------------------------------------*/
            x2 = (float*)_mvd((int)x);

            /*-------------------------------------------------------------*/
            /*  Store eight outputs - four legs of each butterfly          */
            /*-------------------------------------------------------------*/
            _amem8_f2(&x2[0])    = x_1o_x_0o;
            _amem8_f2(&x2[2])    = x_3o_x_2o;

            _amem8_f2(&x2[l1])   = xl1_1o_xl1_0o;
            _amem8_f2(&x2[l1+2]) = xl1_3o_xl1_2o;

            _amem8_f2(&x2[h2])   = xh2_1o_xh2_0o;
            _amem8_f2(&x2[h2+2]) = xh2_3o_xh2_2o;

            _amem8_f2(&x2[l2])   = xl2_1o_xl2_0o;
            _amem8_f2(&x2[l2+2]) = xl2_3o_xl2_2o;

            /*-------------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is        */
            /* incremented by 12, to reflect the fact that 6 words are     */
            /* consumed in every iteration. The input data pointer         */
            /* increments by 4. Note that within a stage, the stride does  */
            /* not change and hence the offsets for the other three legs,  */
            /* 0, h2, l1, l2.                                              */
            /*-------------------------------------------------------------*/
            j += 12;
            x += 4;
            predj = (j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;
        }
        stride >>= 2;
    }

    j = offset >> 2;
    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix4 pass or a  */
    /* radix2 pass. Two pointers are used to access the input data.    */
    /* The input data is read "N/4" complex samples apart or "N/2"     */
    /* words apart using pointers "x0" and "x2". This produces out-    */
    /* puts that are 0, N/8, N/2, 3N/8 for radix 2.                    */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + n_max;
    x2 = ptr_x;
    y1 = y0 + (n_max >> 1);
    y3 = y2 + (n_max >> 1);
    l1 = _norm(n_max) + 4;

    if (radix == 4) {
        for (i = 0; i < N; i += 4) {
            /* reversal computation */
            k = _bitr(j) >> l1;
            j++;

            /*-------------------------------------------------------------*/
            /* Read in the input data. These are transformed as a radix 4. */
            /*-------------------------------------------------------------*/
            x_10 = _amem8_f2(&x2[0]);
            x_32 = _amem8_f2(&x2[2]);
            x_54 = _amem8_f2(&x2[4]);
            x_76 = _amem8_f2(&x2[6]);
            x2 += 8;
 
            /*-------------------------------------------------------------*/
            /* Perform radix4 style decomposition.                         */
            /*-------------------------------------------------------------*/
            xh1_0_xh0_0 = _daddsp(x_10, x_54);
            xh1_1_xh0_1 = _daddsp(x_32, x_76);
            xl1_0_xl0_0 = _dsubsp(x_10, x_54);
            xl1_1_xl0_1 = _dsubsp(x_32, x_76);

            yt_10 = _daddsp(xh1_0_xh0_0, xh1_1_xh0_1);
            yt_54 = _dsubsp(xh1_0_xh0_0, xh1_1_xh0_1);

            yt3 = _hif2(xl1_0_xl0_0) - _lof2(xl1_1_xl0_1);
            yt2 = _lof2(xl1_0_xl0_0) + _hif2(xl1_1_xl0_1);
            yt7 = _hif2(xl1_0_xl0_0) + _lof2(xl1_1_xl0_1);
            yt6 = _lof2(xl1_0_xl0_0) - _hif2(xl1_1_xl0_1);

            /*-------------------------------------------------------------*/
            /* Points that are read from succesive locations map to y      */
            /* y[N/8], y[N/2], y[5N/8] in a radix2 scheme.                 */
            /*-------------------------------------------------------------*/
            _amem8_f2(&y0[k*2]) = yt_10;
            _amem8_f2(&y1[k*2]) = _ftof2(yt3, yt2);
            _amem8_f2(&y2[k*2]) = yt_54;
            _amem8_f2(&y3[k*2]) = _ftof2(yt7, yt6);
        }
    }
    if (radix == 2) {
        for (i = 0; i < N; i += 4) {
            /* reversal computation */
            k = _bitr(j) >> l1;
            j++;

            /*-------------------------------------------------------------*/
            /* Read in the input data. These are transformed as a radix 2. */
            /*-------------------------------------------------------------*/
            x_10 = _amem8_f2(&x2[0]);
            x_32 = _amem8_f2(&x2[2]);
            x_54 = _amem8_f2(&x2[4]);
            x_76 = _amem8_f2(&x2[6]);
            x2 += 8;
 
            /*-------------------------------------------------------------*/
            /* Perform radix2 style decomposition.                         */
            /*-------------------------------------------------------------*/
            yt_10 = _daddsp(x_10, x_32);
            yt_32 = _daddsp(x_54, x_76);
            yt_54 = _dsubsp(x_10, x_32);
            yt_76 = _dsubsp(x_54, x_76);

            /*-------------------------------------------------------------*/
            /* Points that are read from succesive locations map to y      */
            /* y[N/8], y[N/2], y[5N/8] in a radix2 scheme.                 */
            /*-------------------------------------------------------------*/
            _amem8_f2(&y0[k*2]) = yt_10;
            _amem8_f2(&y1[k*2]) = yt_32;
            _amem8_f2(&y2[k*2]) = yt_54;
            _amem8_f2(&y3[k*2]) = yt_76;
        }
    }
}
#else
void DSPF_sp_fftSPxSP_opt (int N, float *ptr_x, float *ptr_w, float *ptr_y,
                       unsigned char *brev, int n_min, int offset, int n_max)
{

    int i, j, k, l1, l2, h2, predj, tw_offset, stride, fft_jmp, radix;

    float yt2, yt3, yt6, yt7;
    float xt1_0, yt2_0, xt1_1, yt2_1, xt2_0, yt1_0, xt2_1, yt1_1;
    float * restrict x, * restrict x2, * restrict w;
    float * restrict y0, * restrict y1, * restrict y2, * restrict y3;

    __float2_t xh20_0_xh21_0, xh20_1_xh21_1, xh0_0_xh1_0, xh0_1_xh1_1;
    __float2_t xl20_0_xl21_0, xl20_1_xl21_1, xl0_0_xl1_0, xl0_1_xl1_1;
    __float2_t xt0_0_yt0_0,   xt0_1_yt0_1,   xt1_0_yt1_0;
    __float2_t xt1_1_yt1_1,   xt2_0_yt2_0,   xt2_1_yt2_1;
    __float2_t x_0o_x_1o,     xl1_0o_xl1_1o, x_2o_x_3o,     xl1_2o_xl1_3o;
    __float2_t xh2_0o_xh2_1o, xl2_0o_xl2_1o, xh2_2o_xh2_3o, xl2_2o_xl2_3o;
    __float2_t x_l1_01, x_l1_23, x_l2_01, x_l2_23, x_h2_01, x_h2_23;
    __float2_t co10_si10, co20_si20, co30_si30, co11_si11, co21_si21, co31_si31;
    __float2_t x_01, x_23, x_45, x_67, yt_01, yt_23, yt_45, yt_67;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 6*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/ 
    radix     = n_min;
    stride    = N;
    tw_offset = 0;
    fft_jmp   = 6 * stride;

    _nassert(stride > 4);
    while (stride > radix)
    {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 6 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          6 N/4               1               */
        /*  2                          6 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/  
        j =  0;
        fft_jmp >>= 2;

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
        w = ptr_w + tw_offset;
        tw_offset += fft_jmp;

        /*-----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies,  */
        /* within a given stage. Recall that there are logN to base 4      */
        /* stages. Certain butterflies share the twiddle factors. These    */
        /* are grouped together. On the very first stage there are no      */
        /* butterflies that share the twiddle factor, all N/4 butter-      */
        /* flies have different factors. On the next stage two sets of     */
        /* N/8 butterflies share the same twiddle factor. Hence after      */
        /* half the butterflies are performed, j the index into the        */
        /* factor array resets to 0, and the twiddle factors are reused.   */
        /* When this happens, the data pointer 'x' is incremented by the   */
        /* fft_jmp amount.                                                 */
        /*-----------------------------------------------------------------*/
        _nassert((int)(w) % 8 == 0);
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        _nassert(N >= 8);

        for (i = 0; i < (N >> 3); i++) {

            /*-------------------------------------------------------------*/
            /*  Read the first six twiddle factor values. This loop        */
            /*  computes two radix 4 butterflies at a time.                */
            /* si10 = -w[0] co10 = w[1]   si20 = -w[2] co20 = w[3]         */
            /* si30 = -w[4] co30 = w[5]   si11 = -w[6] co11 = w[7]         */
            /* si21 = -w[8] co21 = w[9]   si31 = -w[a] co31 = w[b]         */
            /*-------------------------------------------------------------*/
            co10_si10 = _amem8_f2_const(&w[j]);
            co20_si20 = _amem8_f2_const(&w[j+2]);
            co30_si30 = _amem8_f2_const(&w[j+4]);

            co11_si11 = _amem8_f2_const(&w[j+6]);
            co21_si21 = _amem8_f2_const(&w[j+8]);
            co31_si31 = _amem8_f2_const(&w[j+10]);

            /*-------------------------------------------------------------*/
            /* Read in the data elements for the eight inputs of two       */
            /* radix4 butterflies.                                         */
            /*  x[0]       x[1]       x[2]       x[3]                      */
            /*  x[h2+0]    x[h2+1]    x[h2+2]    x[h2+3]                   */
            /*  x[l1+0]    x[l1+1]    x[l1+2]    x[l1+3]                   */
            /*  x[l2+0]    x[l2+1]    x[l2+2]    x[l2+3]                   */
            /*-------------------------------------------------------------*/
            x_01    = _amem8_f2(&x[0]);
            x_23    = _amem8_f2(&x[2]);
            x_l1_01 = _amem8_f2(&x[l1]);
            x_l1_23 = _amem8_f2(&x[l1 + 2]);
            x_l2_01 = _amem8_f2(&x[l2]);
            x_l2_23 = _amem8_f2(&x[l2 + 2]);
            x_h2_01 = _amem8_f2(&x[h2]);
            x_h2_23 = _amem8_f2(&x[h2 + 2]);

            /*-------------------------------------------------------------*/
            /* xh0_0 = x[0] + x[l1];    xh1_0 = x[1] + x[l1+1]             */
            /* xh0_1 = x[2] + x[l1+2];  xh1_1 = x[3] + x[l1+3]             */
            /* xl0_0 = x[0] - x[l1];    xl1_0 = x[1] - x[l1+1]             */
            /* xl0_1 = x[2] - x[l1+2];  xl1_1 = x[3] - x[l1+3]             */
            /*-------------------------------------------------------------*/
            xh0_0_xh1_0 = _daddsp(x_01, x_l1_01);
            xl0_0_xl1_0 = _dsubsp(x_01, x_l1_01);
            xh0_1_xh1_1 = _daddsp(x_23, x_l1_23);
            xl0_1_xl1_1 = _dsubsp(x_23, x_l1_23);

            /*-------------------------------------------------------------*/
            /* xh20_0 = x[h2  ] + x[l2  ]; xh21_0 = x[h2+1] + x[l2+1]      */
            /* xh20_1 = x[h2+2] + x[l2+2]; xh21_1 = x[h2+3] + x[l2+3]      */
            /* xl20_0 = x[h2  ] - x[l2  ]; xl21_0 = x[h2+1] - x[l2+1]      */
            /* xl20_1 = x[h2+2] - x[l2+2]; xl21_1 = x[h2+3] - x[l2+3]      */
            /*-------------------------------------------------------------*/
            xh20_0_xh21_0 = _daddsp(x_h2_01, x_l2_01);
            xl20_0_xl21_0 = _dsubsp(x_h2_01, x_l2_01);
            xh20_1_xh21_1 = _daddsp(x_h2_23, x_l2_23);
            xl20_1_xl21_1 = _dsubsp(x_h2_23, x_l2_23);

            /*-------------------------------------------------------------*/
            /*    x_0o  = xh0_0 + xh20_0;    x_1o  = xh1_0 + xh21_0;       */
            /*    x_2o  = xh0_1 + xh20_1;    x_3o  = xh1_1 + xh21_1;       */
            /*    xt0_0 = xh0_0 - xh20_0;    yt0_0 = xh1_0 - xh21_0;       */
            /*    xt0_1 = xh0_1 - xh20_1;    yt0_1 = xh1_1 - xh21_1;       */
            /*-------------------------------------------------------------*/
            x_0o_x_1o = _daddsp(xh0_0_xh1_0, xh20_0_xh21_0);
            x_2o_x_3o = _daddsp(xh0_1_xh1_1, xh20_1_xh21_1);

            xt0_0_yt0_0 = _dsubsp(xh0_0_xh1_0, xh20_0_xh21_0);
            xt0_1_yt0_1 = _dsubsp(xh0_1_xh1_1, xh20_1_xh21_1);

            /*-------------------------------------------------------------*/
            /*    xt1_0 = xl0_0 + xl21_0;    yt2_0 = xl1_0 + xl20_0;       */
            /*    xt1_1 = xl0_1 + xl21_1;    yt2_1 = xl1_1 + xl20_1;       */
            /*    xt2_0 = xl0_0 - xl21_0;    yt1_0 = xl1_0 - xl20_0;       */
            /*    xt2_1 = xl0_1 - xl21_1;    yt1_1 = xl1_1 - xl20_1;       */
            /*-------------------------------------------------------------*/
            yt1_0 = _lof2(xl0_0_xl1_0) - _hif2(xl20_0_xl21_0);
            xt2_0 = _hif2(xl0_0_xl1_0) - _lof2(xl20_0_xl21_0);
            yt1_1 = _lof2(xl0_1_xl1_1) - _hif2(xl20_1_xl21_1);
            xt2_1 = _hif2(xl0_1_xl1_1) - _lof2(xl20_1_xl21_1);
            yt2_0 = _lof2(xl0_0_xl1_0) + _hif2(xl20_0_xl21_0);
            xt1_0 = _hif2(xl0_0_xl1_0) + _lof2(xl20_0_xl21_0);
            yt2_1 = _lof2(xl0_1_xl1_1) + _hif2(xl20_1_xl21_1);
            xt1_1 = _hif2(xl0_1_xl1_1) + _lof2(xl20_1_xl21_1);

            xt1_0_yt1_0 = _ftof2(xt1_0, yt1_0);
            xt1_1_yt1_1 = _ftof2(xt1_1, yt1_1);
            xt2_0_yt2_0 = _ftof2(xt2_0, yt2_0);
            xt2_1_yt2_1 = _ftof2(xt2_1, yt2_1);

            /*-------------------------------------------------------------*/
            /*   x2[h2  ] = (si10 * yt1_0 + co10 * xt1_0)                  */
            /*   x2[h2+1] = (co10 * yt1_0 - si10 * xt1_0)                  */
            /*   x2[h2+2] = (si11 * yt1_1 + co11 * xt1_1)                  */
            /*   x2[h2+3] = (co11 * yt1_1 - si11 * xt1_1)                  */
            /*-------------------------------------------------------------*/
            xl1_0o_xl1_1o = _complex_mpysp(co10_si10, xt1_0_yt1_0);
            xl1_2o_xl1_3o = _complex_mpysp(co11_si11, xt1_1_yt1_1);

            /*-------------------------------------------------------------*/
            /*   x2[l1  ] = (si20 * yt0_0 + co20 * xt0_0)                  */
            /*   x2[l1+1] = (co20 * yt0_0 - si20 * xt0_0)                  */
            /*   x2[l1+2] = (si21 * yt0_1 + co21 * xt0_1)                  */
            /*   x2[l1+3] = (co21 * yt0_1 - si21 * xt0_1)                  */
            /*-------------------------------------------------------------*/
            xh2_0o_xh2_1o = _complex_mpysp(co20_si20, xt0_0_yt0_0);
            xh2_2o_xh2_3o = _complex_mpysp(co21_si21, xt0_1_yt0_1);

            /*-------------------------------------------------------------*/
            /*   x2[l2  ] = (si30 * yt2_0 + co30 * xt2_0)                  */
            /*   x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0)                  */
            /*   x2[l2+2] = (si31 * yt2_1 + co31 * xt2_1)                  */
            /*   x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1)                  */
            /*-------------------------------------------------------------*/
            xl2_0o_xl2_1o = _complex_mpysp(co30_si30, xt2_0_yt2_0);
            xl2_2o_xl2_3o = _complex_mpysp(co31_si31, xt2_1_yt2_1);

            /*-------------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"          */
            /*-------------------------------------------------------------*/
            x2 = (float*)_mvd((int)x);

            /*-------------------------------------------------------------*/
            /*  Store eight outputs - four legs of each butterfly          */
            /*-------------------------------------------------------------*/
            _amem8_f2(&x2[0])    = x_0o_x_1o;
            _amem8_f2(&x2[2])    = x_2o_x_3o;

            _amem8_f2(&x2[l1])   = xl1_0o_xl1_1o;
            _amem8_f2(&x2[l1+2]) = xl1_2o_xl1_3o;

            _amem8_f2(&x2[h2])   = xh2_0o_xh2_1o;
            _amem8_f2(&x2[h2+2]) = xh2_2o_xh2_3o;

            _amem8_f2(&x2[l2])   = xl2_0o_xl2_1o;
            _amem8_f2(&x2[l2+2]) = xl2_2o_xl2_3o;

            /*-------------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is        */
            /* incremented by 12, to reflect the fact that 6 words are     */
            /* consumed in every iteration. The input data pointer         */
            /* increments by 4. Note that within a stage, the stride does  */
            /* not change and hence the offsets for the other three legs,  */
            /* 0, h2, l1, l2.                                              */
            /*-------------------------------------------------------------*/
            j += 12;
            x += 4;
            predj = (j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;
        }
        stride >>= 2;
    }

    j = offset >> 2;
    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix4 pass or a  */
    /* radix2 pass. Two pointers are used to access the input data.    */
    /* The input data is read "N/4" complex samples apart or "N/2"     */
    /* words apart using pointers "x0" and "x2". This produces out-    */
    /* puts that are 0, N/8, N/2, 3N/8 for radix 2.                    */
    /*-----------------------------------------------------------------*/
    y0 = ptr_y;
    y2 = ptr_y + n_max;
    x2 = ptr_x;
    y1 = y0 + (n_max >> 1);
    y3 = y2 + (n_max >> 1);
    l1 = _norm(n_max) + 4;

    if (radix == 4) {
        for (i = 0; i < N; i += 4) {
            /* reversal computation */
            k = _bitr(j) >> l1;
            j++;

            /*-------------------------------------------------------------*/
            /* Read in the input data. These are transformed as a radix 4. */
            /*-------------------------------------------------------------*/
            x_01 = _amem8_f2(&x2[0]);
            x_23 = _amem8_f2(&x2[2]);
            x_45 = _amem8_f2(&x2[4]);
            x_67 = _amem8_f2(&x2[6]);
            x2 += 8;
 
            /*-------------------------------------------------------------*/
            /* Perform radix4 style decomposition.                         */
            /*-------------------------------------------------------------*/
            xh0_0_xh1_0 = _daddsp(x_01, x_45);
            xh0_1_xh1_1 = _daddsp(x_23, x_67);
            xl0_0_xl1_0 = _dsubsp(x_01, x_45);
            xl0_1_xl1_1 = _dsubsp(x_23, x_67);

            yt_01 = _daddsp(xh0_0_xh1_0, xh0_1_xh1_1);
            yt_45 = _dsubsp(xh0_0_xh1_0, xh0_1_xh1_1);

            yt3 = _lof2(xl0_0_xl1_0) - _hif2(xl0_1_xl1_1);
            yt2 = _hif2(xl0_0_xl1_0) + _lof2(xl0_1_xl1_1);
            yt7 = _lof2(xl0_0_xl1_0) + _hif2(xl0_1_xl1_1);
            yt6 = _hif2(xl0_0_xl1_0) - _lof2(xl0_1_xl1_1);

            /*-------------------------------------------------------------*/
            /* Points that are read from succesive locations map to y      */
            /* y[N/8], y[N/2], y[5N/8] in a radix2 scheme.                 */
            /*-------------------------------------------------------------*/
            _amem8_f2(&y0[k*2]) = yt_01;
            _amem8_f2(&y1[k*2]) = _ftof2(yt2, yt3);
            _amem8_f2(&y2[k*2]) = yt_45;
            _amem8_f2(&y3[k*2]) = _ftof2(yt6, yt7);
        }
    }
    if (radix == 2) {
        for (i = 0; i < N; i += 4) {
            /* reversal computation */
            k = _bitr(j) >> l1;
            j++;

            /*-------------------------------------------------------------*/
            /* Read in the input data. These are transformed as a radix 2. */
            /*-------------------------------------------------------------*/
            x_01 = _amem8_f2(&x2[0]);
            x_23 = _amem8_f2(&x2[2]);
            x_45 = _amem8_f2(&x2[4]);
            x_67 = _amem8_f2(&x2[6]);
            x2 += 8;
 
            /*-------------------------------------------------------------*/
            /* Perform radix2 style decomposition.                         */
            /*-------------------------------------------------------------*/
            yt_01 = _daddsp(x_01, x_23);
            yt_23 = _daddsp(x_45, x_67);
            yt_45 = _dsubsp(x_01, x_23);
            yt_67 = _dsubsp(x_45, x_67);

            /*-------------------------------------------------------------*/
            /* Points that are read from succesive locations map to y      */
            /* y[N/8], y[N/2], y[5N/8] in a radix2 scheme.                 */
            /*-------------------------------------------------------------*/
            _amem8_f2(&y0[k*2]) = yt_01;
            _amem8_f2(&y1[k*2]) = yt_23;
            _amem8_f2(&y2[k*2]) = yt_45;
            _amem8_f2(&y3[k*2]) = yt_67;
        }
    }
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_fftSPxSP_opt.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
