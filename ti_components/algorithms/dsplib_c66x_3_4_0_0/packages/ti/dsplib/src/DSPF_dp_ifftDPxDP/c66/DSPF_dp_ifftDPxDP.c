/* ======================================================================= */
/* DSPF_dp_ifftDPxDP.c -- Inverse FFT with Mixed Radix                     */
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

#pragma CODE_SECTION(DSPF_dp_ifftDPxDP, ".text:optimized");

#include "DSPF_dp_ifftDPxDP.h"

void DSPF_dp_ifftDPxDP (int N, double *restrict ptr_x, double *restrict ptr_w, 
                        double *restrict ptr_y, int n_min, int offset, int n_max)
{
    int i, j, k, l1, l2, h2, predj, l0, radix;
    int tw_offset, stride, fft_jmp;

    double x0, x1, x2, x3, x4, x5, x6, x7;
    double xt0, yt0, xt1, yt1, xt2, yt2, yt3;
    double yt4, yt5, yt6, yt7;
    double si1, si2, si3, co1, co2, co3;
    double xh0, xh1, xh20, xh21, xl0, xl1, xl20, xl21;
    double x_0, x_1, x_l1, x_l1p1, x_h2, x_h2p1, x_l2, x_l2p1;
    double xl0_0, xl1_0, xl0_1, xl1_1;
    double xh0_0, xh1_0, xh0_1, xh1_1;
    double *restrict x, *restrict w;
    double *restrict y0, *restrict y1, *restrict y2, *restrict y3;
    double *restrict ptr_x0, *restrict ptr_x2;
    double scale;

    radix     = n_min;
    stride    = N;    /* n is the number of complex samples */
    tw_offset = 0;

    _nassert(stride > 4);
    while (stride > radix) {

        fft_jmp = stride + (stride >> 1);
        j  = 0;
        h2 = stride >> 1;
        l1 = stride;
        l2 = stride + (stride >> 1);
        x  = ptr_x;
        w  = ptr_w + tw_offset;

        _nassert((int)(w) % 8 == 0);
        _nassert((int)(x) % 8 == 0);
        _nassert(N >= 8);
 
        for (i = 0; i < N; i += 4) {

            co1 = w[j];
            si1 = w[j + 1];
            co2 = w[j + 2];
            si2 = w[j + 3];
            co3 = w[j + 4];
            si3 = w[j + 5];

            x_0    = x[0];
            x_1    = x[1];
            x_h2   = x[h2];
            x_h2p1 = x[h2 + 1];
            x_l1   = x[l1];
            x_l1p1 = x[l1 + 1];
            x_l2   = x[l2];
            x_l2p1 = x[l2 + 1];

            xh0  = x_0 + x_l1;
            xh1  = x_1 + x_l1p1;
            xl0  = x_0 - x_l1;
            xl1  = x_1 - x_l1p1;

            xh20 = x_h2   + x_l2;
            xh21 = x_h2p1 + x_l2p1;
            xl20 = x_h2   - x_l2;
            xl21 = x_h2p1 - x_l2p1;

            ptr_x2    = (double*)_mvd((int)x);
            ptr_x2[0] = xh0 + xh20;
            ptr_x2[1] = xh1 + xh21;

            x += 2;
            j += 6;
            predj = (j - fft_jmp);
            if (!predj) {
                x += fft_jmp;
                j = 0;
            }

            xt0 = xh0 - xh20;                                
            yt0 = xh1 - xh21;                                
            xt1 = xl0 - xl21;                                 
            yt2 = xl1 - xl20;                                
            xt2 = xl0 + xl21;                                 
            yt1 = xl1 + xl20;                                

            ptr_x2[l1    ] = xt1 * co1 - yt1 * si1;               
            ptr_x2[l1 + 1] = yt1 * co1 + xt1 * si1;            
            ptr_x2[h2    ] = xt0 * co2 - yt0 * si2;                 
            ptr_x2[h2 + 1] = yt0 * co2 + xt0 * si2;             
            ptr_x2[l2    ] = xt2 * co3 - yt2 * si3;                 
            ptr_x2[l2 + 1] = yt2 * co3 + xt2 * si3;            
        }
        tw_offset += fft_jmp;
        stride = stride >> 2;
    } /* end while */

    j = offset >> 2;

    ptr_x0 = ptr_x;
    l0     = _norm(n_max) + 3;
    scale  = (double)_rcpsp((float)n_max);
    y0     = ptr_y;
    y2     = ptr_y + n_max;
    y1     = y0 + (n_max >> 1);
    y3     = y2 + (n_max >> 1);
    
    if (radix == 4) {
        for (i = 0; i < N; i += 4) {
            /* reversal computation */
            k = _bitr(j) >> l0;
            j++;                                            

            x0 = ptr_x0[0];
            x1 = ptr_x0[1];
            x2 = ptr_x0[2];
            x3 = ptr_x0[3];
            x4 = ptr_x0[4];
            x5 = ptr_x0[5];
            x6 = ptr_x0[6];
            x7 = ptr_x0[7];
            ptr_x0 += 8;

            xh0_0 = x0 + x4;
            xh1_0 = x1 + x5;
            xh0_1 = x2 + x6;
            xh1_1 = x3 + x7;

            yt0 = xh0_0 + xh0_1;
            yt1 = xh1_0 + xh1_1;
            yt4 = xh0_0 - xh0_1;
            yt5 = xh1_0 - xh1_1;

            xl0_0 = x0 - x4;
            xl1_0 = x1 - x5;
            xl0_1 = x2 - x6;
            xl1_1 = x7 - x3;                                

            yt2 = xl0_0 + xl1_1;
            yt3 = xl1_0 + xl0_1;                            
            yt6 = xl0_0 - xl1_1;
            yt7 = xl1_0 - xl0_1;                             

            y0[k    ] = yt0 * scale;
            y0[k + 1] = yt1 * scale;
            y1[k    ] = yt2 * scale;
            y1[k + 1] = yt3 * scale;
            y2[k    ] = yt4 * scale;
            y2[k + 1] = yt5 * scale;
            y3[k    ] = yt6 * scale;
            y3[k + 1] = yt7 * scale;
        }
    }
    else if (radix == 2) {
        for (i = 0; i < N; i += 4) {
            /* reversal computation */
            k = _bitr(j) >> l0;
            j++;                                           

            xh0_0 = ptr_x0[0];
            xh1_0 = ptr_x0[1];
            xh0_1 = ptr_x0[2];
            xh1_1 = ptr_x0[3];
            xl0_0 = ptr_x0[4];
            xl1_0 = ptr_x0[5];
            xl1_1 = ptr_x0[6];
            xl0_1 = ptr_x0[7];
            ptr_x0 += 8;
                
            yt0 = xh0_0 + xh0_1;
            yt1 = xh1_0 + xh1_1;
            yt4 = xh0_0 - xh0_1;
            yt5 = xh1_0 - xh1_1;

            yt2 = xl0_0 + xl1_1;
            yt3 = xl1_0 + xl0_1;                            
            yt6 = xl0_0 - xl1_1;
            yt7 = xl1_0 - xl0_1;                             

            y0[k    ] = yt0 * scale;
            y0[k + 1] = yt1 * scale;
            y1[k    ] = yt2 * scale;
            y1[k + 1] = yt3 * scale;
            y2[k    ] = yt4 * scale;
            y2[k + 1] = yt5 * scale;
            y3[k    ] = yt6 * scale;
            y3[k + 1] = yt7 * scale;
        }
    }
}
/* ======================================================================= */
/*  End of file:  DSPF_dp_ifftDPxDP.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
