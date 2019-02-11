/* ======================================================================== */
/* DSPF_sp_fftSPxSP_r2c_d.c -- Real to Complex FFT with Mixed Radix         */
/*                Driver code; tests kernel and reports result in stdout    */
/*                                                                          */
/* Rev 0.0.3                                                                */
/*                                                                          */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/   */ 
/*                                                                          */
/*                                                                          */
/*  Redistribution and use in source and binary forms, with or without      */
/*  modification, are permitted provided that the following conditions      */
/*  are met:                                                                */
/*                                                                          */
/*    Redistributions of source code must retain the above copyright        */
/*    notice, this list of conditions and the following disclaimer.         */
/*                                                                          */
/*    Redistributions in binary form must reproduce the above copyright     */
/*    notice, this list of conditions and the following disclaimer in the   */
/*    documentation and/or other materials provided with the                */
/*    distribution.                                                         */
/*                                                                          */
/*    Neither the name of Texas Instruments Incorporated nor the names of   */
/*    its contributors may be used to endorse or promote products derived   */
/*    from this software without specific prior written permission.         */
/*                                                                          */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/* ======================================================================== */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <c6x.h>

#include "DSPF_sp_fftSPxSP_r2c.h"
#include "DSPF_sp_fftSPxSP_r2c_cn.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif
extern char kernel_size;

#define CYCLE_FORMULA_NX_PT1  128
#define CYCLE_FORMULA_NX_PT2  256
#define FORMULA_SIZE          2
int     form_cycle [FORMULA_SIZE];

void tw_gen    (float *w, int n);
void tw_gen_cn (float *w, int n);

/* ======================================================================== */
/*  Kernel-specific alignments                                              */
/* ======================================================================== */
#pragma DATA_ALIGN(x_i,  8);
#pragma DATA_ALIGN(x_cn, 8);

#pragma DATA_ALIGN(w_i,  8);
#pragma DATA_ALIGN(w_cn, 8);

#pragma DATA_ALIGN(y_i,  8);
#pragma DATA_ALIGN(y_cn, 8);
#pragma DATA_ALIGN(brev, 8);

/* ======================================================================== */
/*  Parameters of fixed dataset.                                            */
/* ======================================================================== */
#define MAXN (1024)
#define M    (2*MAXN)
#define PAD  (16)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */

float x_i [M + 2 * PAD];
float x_cn[M + 2 * PAD];

float w_i [M + 2 * PAD];
float w_cn[M + 2 * PAD];

float y_i [M + 2 * PAD];
float y_cn[M + 2 * PAD];

/* ======================================================================== */
/*  Generate pointers to skip beyond array padding                          */
/* ======================================================================== */
float *const ptr_x_i  = x_i  + PAD;
float *const ptr_x_cn = x_cn + PAD;

float *const ptr_w_i  = w_i  + PAD;
float *const ptr_w_cn = w_cn + PAD;

float *const ptr_y_i  = y_i  + PAD;
float *const ptr_y_cn = y_cn + PAD;

unsigned char brev[64] = {
    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
};

/* ======================================================================== */
/*  MAIN -- Top level driver for the test.                                  */
/* ======================================================================== */

int main ()
{
    int i, j, rad_cn, rad_i, N, k;
    clock_t t_start, t_stop, t_overhead, t_opt, t_cn;
    float diff, max_diff;

    for (N = 32, k = 1; N <= MAXN; N = N * 2, k++)
    {

        memset (x_i,  0x55, sizeof (x_i) );
        memset (x_cn, 0x55, sizeof (x_cn));

        /* ---------------------------------------------------------------- */
        /* Initialize input vector temporarily.                             */
        /* ---------------------------------------------------------------- */
        for (i = 0; i < N; i++)
        {
            x_cn[PAD + 2*i]     = sin (2 * 3.1415 * 50 * i / (double) N);
            x_cn[PAD + 2*i + 1] = 0;
            x_i [PAD + i]       = x_cn[PAD + 2*i];
        }

        /* ---------------------------------------------------------------- */
        /* Force uninitialized arrays to fixed values.                      */
        /* ---------------------------------------------------------------- */
        memset (y_i,  0xA5, sizeof (y_i) );
        memset (y_cn, 0xA5, sizeof (y_cn));

        /* ---------------------------------------------------------------- */
        /* Initialize timer for clock */
        TSCL= 0,TSCH=0;
        /* Compute the overhead of calling _itoll(TSCH, TSCL) twice to get timing info */
        /* ---------------------------------------------------------------- */
        t_start = _itoll(TSCH, TSCL);
        t_stop = _itoll(TSCH, TSCL);
        t_overhead = t_stop - t_start;

        /* ---------------------------------------------------------------- */
        /* Generate twiddle factors.                                        */
        /* ---------------------------------------------------------------- */
        j = 0;
        for (i = 0; i <= 31; i++)
            if ((N & (1 << i)) == 0)
                j++;
            else
                break;

        if (j % 2 == 0) {
            rad_cn = 4;
            rad_i  = 2;
        }
        else {
            rad_cn = 2;
            rad_i  = 4;
        }

        tw_gen    (ptr_w_i,  N);
        tw_gen_cn (ptr_w_cn, N);

        printf("DSPF_sp_fftSPxSP\tIter#: %d\t", k);
        t_start = _itoll(TSCH, TSCL);
        DSPF_sp_fftSPxSP_r2c_cn (N, &ptr_x_cn[0], &ptr_w_cn[0], ptr_y_cn, brev, rad_cn, 0, N);
        t_stop = _itoll(TSCH, TSCL);
        t_cn   = (t_stop - t_start) - t_overhead;

        t_start = _itoll(TSCH, TSCL);
        DSPF_sp_fftSPxSP_r2c (N, &ptr_x_i[0], &ptr_w_i[0], ptr_y_i, brev, rad_i, 0, N);
        t_stop = _itoll(TSCH, TSCL);
        t_opt  = (t_stop - t_start) - t_overhead;

        /* ---------------------------------------------------------------- */
        /* compute percent difference and track max difference              */  
        /* ---------------------------------------------------------------- */
        diff = 0; max_diff = 0;
        for(i=0; i<N; i++) {
          diff = ptr_y_cn[i] - ptr_y_i[i];
          if (diff < 0) diff *= -1;
          if (diff > max_diff) 
            max_diff = diff;
        }

        if (max_diff > 0.01)
            printf("Intrinsic Failure  max_diff = %f", max_diff);
        else
            printf("Intrinsic Successful ");

        printf("\tN = %d\tnatC: %d\toptC: %d\n", N, t_cn, t_opt);

        if (N == CYCLE_FORMULA_NX_PT1)
          form_cycle[0] = t_opt;
        if (N == CYCLE_FORMULA_NX_PT2)
          form_cycle[1] = t_opt;
    }

    /* Provide memory information */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
    printf("Memory:  %d bytes\n", &kernel_size);
#endif

    /* Provide profiling information */
    printf("Cycles:  %d (N=128) %d (N=256)\n", form_cycle[0], form_cycle[1]);
}

/* Function for generating Specialized sequence of twiddle factors */
void tw_gen_cn (float *w, int n)
{
    int i, j, k;
    const double PI = 3.141592654;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {
#ifdef _LITTLE_ENDIAN
            w[k]     = (float) sin (2 * PI * i / n);
            w[k + 1] = (float) cos (2 * PI * i / n);
            w[k + 2] = (float) sin (4 * PI * i / n);
            w[k + 3] = (float) cos (4 * PI * i / n);
            w[k + 4] = (float) sin (6 * PI * i / n);
            w[k + 5] = (float) cos (6 * PI * i / n);
#else
            w[k]     = (float)  cos (2 * PI * i / n);
            w[k + 1] = (float) -sin (2 * PI * i / n);
            w[k + 2] = (float)  cos (4 * PI * i / n);
            w[k + 3] = (float) -sin (4 * PI * i / n);
            w[k + 4] = (float)  cos (6 * PI * i / n);
            w[k + 5] = (float) -sin (6 * PI * i / n);
#endif
            k += 6;
        }
    }
}

void tw_gen (float *w, int n)
{
    int i, j, k;
    const double PI = 3.141592654;

    for (i = 1, k = 0; i < n >> 2; i++) {
#ifdef _LITTLE_ENDIAN
        w[k    ] = sin (2 * PI * i / n);
        w[k + 1] = cos (2 * PI * i / n);
#else
        w[k    ] =  cos (2 * PI * i / n);
        w[k + 1] = -sin (2 * PI * i / n);
#endif
        k += 2;
    }

    for (j = 1; j <= n >> 3; j = j << 2) {
        for (i = 0; i < n >> 3; i += j) {
#ifdef _LITTLE_ENDIAN
            w[k]     = (float) sin ( 4 * PI * i / n);
            w[k + 1] = (float) cos ( 4 * PI * i / n);
            w[k + 2] = (float) sin ( 8 * PI * i / n);
            w[k + 3] = (float) cos ( 8 * PI * i / n);
            w[k + 4] = (float) sin (12 * PI * i / n);
            w[k + 5] = (float) cos (12 * PI * i / n);
#else
            w[k]     = (float)  cos ( 4 * PI * i / n);
            w[k + 1] = (float) -sin ( 4 * PI * i / n);
            w[k + 2] = (float)  cos ( 8 * PI * i / n);
            w[k + 3] = (float) -sin ( 8 * PI * i / n);
            w[k + 4] = (float)  cos (12 * PI * i / n);
            w[k + 5] = (float) -sin (12 * PI * i / n);
#endif
            k += 6;
        }
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_fftSPxSP_r2c_d.c                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
