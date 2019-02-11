/* ======================================================================== */
/* DSPF_dp_fftDPxDP_d.c -- Complex Forward FFT with Mixed Radix             */
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

#include "DSPF_dp_fftDPxDP.h"
#include "DSPF_dp_fftDPxDP_cn.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;
#define CYCLE_FORMULA_NX_PT1  128
#define CYCLE_FORMULA_NX_PT2  256
#define FORMULA_SIZE          2
int     form_cycle [FORMULA_SIZE];

void tw_gen (double *w, int n);

/* ======================================================================== */
/*  Kernel-specific alignments                                              */
/* ======================================================================== */
#pragma DATA_ALIGN(x_i, 8);
#pragma DATA_ALIGN(x_cn, 8);

#pragma DATA_ALIGN(w, 8);
#pragma DATA_ALIGN(y_i, 8);
#pragma DATA_ALIGN(y_cn, 8);

/* ======================================================================== */
/*  Parameters of fixed dataset.                                            */
/* ======================================================================== */
#define MAXN (256)
#define M    (2*MAXN)
#define PAD  (16)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */

double x_i[M + 2 * PAD];
double x_cn[M + 2 * PAD];

double w[M + 2 * PAD];

double y_i[M + 2 * PAD];
double y_cn[M + 2 * PAD];

/* ======================================================================== */
/*  Generate pointers to skip beyond array padding                          */
/* ======================================================================== */
double *const ptr_x_i  = x_i  + PAD;
double *const ptr_x_cn = x_cn + PAD;

double *const ptr_w = w + PAD;

double *const ptr_y_i  = y_i  + PAD;
double *const ptr_y_cn = y_cn + PAD;

/* ======================================================================== */
/*  MAIN -- Top level driver for the test.                                  */
/* ======================================================================== */

int main ()
{
    int i, j, rad, N, k;
    clock_t t_start, t_stop, t_overhead, t_opt, t_cn;
    float pct_diff, max_pct_diff = 0;

    for (N = 8, k = 1; N <= MAXN; N = N * 2, k++)
    {

        memset (x_i,  0x55, sizeof (x_i));
        memset (x_cn, 0x55, sizeof (x_cn));

        /* ---------------------------------------------------------------- */
        /* Initialize input vector temporarily.                             */
        /* ---------------------------------------------------------------- */
        for (i = 0; i < N; i++)
        {
            x_cn[PAD + 2 * i]     = sin (2 * 3.1415 *  50 * i / (double) N);
            x_cn[PAD + 2 * i + 1] = sin (2 * 3.1415 * 100 * i / (double) N);
            x_i[PAD + 2 * i]      = x_cn[PAD + 2 * i];
            x_i[PAD + 2 * i + 1]  = x_cn[PAD + 2 * i + 1];
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

        if (j % 2 == 0)
            rad = 4;
        else
            rad = 2;

        tw_gen (ptr_w, N);

        printf("DSPF_dp_fftDPxDP\tIter#: %d\t", k);
        t_start = _itoll(TSCH, TSCL);
        DSPF_dp_fftDPxDP_cn (N, &ptr_x_cn[0], &ptr_w[0], ptr_y_cn, rad, 0, N);
        t_stop = _itoll(TSCH, TSCL);
        t_cn = (t_stop - t_start) - t_overhead;

        t_start = _itoll(TSCH, TSCL);
        DSPF_dp_fftDPxDP (N, &ptr_x_i[0], &ptr_w[0], ptr_y_i, rad, 0, N);
        t_stop = _itoll(TSCH, TSCL);
        t_opt = (t_stop - t_start) - t_overhead;

        /* ---------------------------------------------------------------- */
        /* compute percent difference and track max difference              */  
        /* ---------------------------------------------------------------- */
        for(i=0; i<N; i++) {
          pct_diff = (ptr_y_cn[i] - ptr_y_i[i]) / ptr_y_cn[i] * 100.0;
          if (pct_diff < 0) pct_diff *= -1;
          if (pct_diff > max_pct_diff) max_pct_diff = pct_diff;
        }
        if (max_pct_diff > 0.001)
            printf("Result Failure  max_pct_diff = %f", max_pct_diff);
        else
            printf("Result Successful ");

        printf("\tN = %d\tradix = %d\tnatC: %d\toptC: %d\n", N, rad, t_cn, t_opt);

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
void tw_gen (double *w, int n)
{
    int i, j, k;
    const double PI = 3.141592654;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {
            w[k]     = cos (2 * PI * i / n);
            w[k + 1] = sin (2 * PI * i / n);
            w[k + 2] = cos (4 * PI * i / n);
            w[k + 3] = sin (4 * PI * i / n);
            w[k + 4] = cos (6 * PI * i / n);
            w[k + 5] = sin (6 * PI * i / n);
            k += 6;
        }
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_fftSPxSP_d.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
