/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fft16x16_imre -- Driver file for fft16x16_imre                 */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'DSP_fft16x16  */
/*      _imre' kernel.  The function prototype appears below.  The driver  */
/*      itself is invoked as a standard C program, and results are         */
/*      reported on stdout. The driver will use a fixed test vector.       */
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

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <c6x.h>

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;
#define CYCLE_FORMULA_NX_PT1  128
#define CYCLE_FORMULA_NX_PT2  256
#define FORMULA_SIZE          2
int     form_cycle [FORMULA_SIZE];

#include "DSP_fft16x16_imre_cn.h"
#include "DSP_fft16x16_imre.h"
#include "gen_twiddle_fft16x16_imre.h"

/* ======================================================================== */
/*  Kernel-specific alignments                                              */
/* ======================================================================== */
#pragma DATA_ALIGN(w, 8);

#pragma DATA_ALIGN(x, 8);
#pragma DATA_ALIGN(x_cn, 8);
#pragma DATA_ALIGN(x_i, 8);

#pragma DATA_ALIGN(y_cn, 8);
#pragma DATA_ALIGN(y_i, 8);

/* ======================================================================== */
/*  Parameters of fixed dataset.                                            */
/* ======================================================================== */
#define N   (256)
#define PAD (16)

/* ======================================================================== */
/*  Number of input arguments:                                              */
/* ======================================================================== */
#define NUM_INPUTS (1)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
short x[NUM_INPUTS][2*N + 2*PAD] =
{
/* Input Number: 0 */

{
    -0x4FB8,  0x7BF0,  0x0D47,  0x0D11,  0x305B,  0x73FB,  0x0585, -0x4FE2,
     0x7879, -0x55C9,  0x5739, -0x7AFF, -0x03DB, -0x5B14, -0x1F55,  0x2D1C,

    -0x6D09,  0x1B3D, -0x49A6,  0x2BEE, -0x00BB,  0x27DC,  0x4D08,  0x74BC,
     0x59B7, -0x3134, -0x5615, -0x5B7E, -0x59CB,  0x7D99,  0x107F,  0x559B,
     0x3EB8, -0x1F69, -0x3E8B,  0x1BB0,  0x7A7B, -0x5C61,  0x2F46, -0x5698,
     0x2110, -0x6A30,  0x48E7, -0x6BA9,  0x1FD3, -0x4B34,  0x381E,  0x44AE,
    -0x05C2, -0x6403,  0x37F5, -0x7ED3, -0x6B61, -0x2AAB, -0x272D,  0x2FD7,
    -0x514D, -0x68EF,  0x62B3, -0x5F1E, -0x5069,  0x5DFF, -0x5905,  0x1E71,
     0x34A7, -0x1540, -0x1988,  0x0A87, -0x1E4C,  0x3692,  0x34F6,  0x29BB,
    -0x09DF, -0x4BEB, -0x2204, -0x6DCC,  0x315F, -0x746D,  0x5C28, -0x3E9E,
     0x6B49,  0x234A,  0x48B0,  0x56F1,  0x7FE2, -0x54C9, -0x2C85, -0x1573,
    -0x060C, -0x0C22,  0x4164, -0x6429,  0x0012,  0x349A, -0x0BE6, -0x51DD,
     0x1475,  0x3BE8,  0x6B21, -0x1E86, -0x00BF,  0x7637, -0x2A8D, -0x27AF,
    -0x6258,  0x6EB3, -0x60B9,  0x3B8F, -0x2395,  0x1C9C, -0x708E, -0x13B3,
    -0x7BBE, -0x5570, -0x2312, -0x152D,  0x4AA2,  0x1662, -0x2CFF,  0x5960,
    -0x5E9F,  0x39EB,  0x7883,  0x2C2C, -0x2E40, -0x459F, -0x493A, -0x09D4,
    -0x27AB,  0x5BA8, -0x735D,  0x5C18, -0x74AD,  0x332B, -0x3DDF, -0x4ACF,
     0x7BB5,  0x4BB2, -0x5AC0,  0x444A,  0x24CB,  0x21BC,  0x4569, -0x606E,
    -0x2059, -0x742C, -0x4908, -0x4968,  0x18EA, -0x798D, -0x2094,  0x041E,
     0x4873,  0x65D1,  0x42B8,  0x621C,  0x3571, -0x16B6,  0x542F, -0x046B,
    -0x02B1, -0x474A, -0x3066, -0x0F63,  0x580D, -0x3FB5, -0x6918,  0x132E,
    -0x5093, -0x0489, -0x6CFF,  0x5334,  0x6D89,  0x1745,  0x1C3D,  0x4A5E,
     0x164A, -0x7944,  0x65F8,  0x6733, -0x53C7,  0x73C3,  0x6AC6,  0x4ADF,
    -0x31C5,  0x1A00, -0x142F, -0x41B5,  0x1FA8,  0x0243, -0x1B38, -0x250F,
     0x783F, -0x591C,  0x0B03, -0x3D0F,  0x5888, -0x0753, -0x23CC, -0x6618,
     0x1B09,  0x51C1, -0x66B7,  0x0608,  0x77E3,  0x4005, -0x1D1C, -0x0C12,
    -0x40B1, -0x3F7A,  0x44FE, -0x203F,  0x6780,  0x5A67,  0x531D,  0x5C09,
     0x515B, -0x6337, -0x3543,  0x38C9,  0x5D9C, -0x76C6,  0x2948, -0x3E9F,
    -0x402B,  0x5C1E,  0x643F, -0x4D58, -0x672E,  0x3AA4,  0x08F6,  0x45CB,
     0x58D6,  0x48AF,  0x767A, -0x1094,  0x6049, -0x5AB8, -0x6FE8,  0x3687,
     0x6C33, -0x3AF0,  0x7EFE,  0x368E,  0x4427, -0x44CE, -0x167D,  0x444E,
     0x2B0A, -0x25AA,  0x4492,  0x3E15, -0x63C6,  0x4B16, -0x6A55, -0x086C,
    -0x3C6A, -0x0790,  0x4816,  0x5003,  0x45E9,  0x68C1, -0x7E5E,  0x6C0E,
    -0x3EC9, -0x0247,  0x759D, -0x690A, -0x5C9D,  0x13D3,  0x4D56,  0x437C,
    -0x503D, -0x7B30,  0x09D1, -0x47F2, -0x21F7,  0x1DB0, -0x1BF0, -0x2054,
    -0x0AEB,  0x65AF, -0x3577, -0x4EE8,  0x6522,  0x56BD,  0x4531, -0x2840,
    -0x0B26,  0x7C00,  0x77B0, -0x1B11, -0x583B, -0x1230, -0x6ACE, -0x4C4A,
     0x6C9F, -0x494B,  0x6F5D,  0x7724,  0x170A,  0x1CEA,  0x6EE1, -0x21D2,
     0x1522,  0x54DC, -0x56CD, -0x161A,  0x6D75,  0x0D2D,  0x6EDF, -0x2092,
    -0x7D26,  0x72B7, -0x21FF, -0x17D8,  0x1EA8,  0x0010,  0x045E, -0x2E53,
     0x3ECE, -0x2FEF, -0x0662,  0x6B03,  0x234E, -0x4728, -0x7ADD,  0x1A94,
     0x2D9A, -0x252B, -0x35F7,  0x0462, -0x0CB3,  0x1A4D,  0x75BE,  0x6306,
     0x2AC7, -0x121B, -0x0F3B,  0x7FE5, -0x3AD1,  0x1BAE,  0x1B0E, -0x32D6,
    -0x19B1, -0x22D2,  0x0A7A, -0x4DF9,  0x0DD5, -0x1B13,  0x4BFB,  0x6AAC,
     0x0B73, -0x3DFF,  0x29D2, -0x687A,  0x3F63,  0x3B1F,  0x7C76, -0x0CBD,
    -0x6B39, -0x0559,  0x7A95, -0x59F6, -0x3691,  0x2836,  0x11B9, -0x3D82,
     0x747D,  0x7038,  0x3C0C,  0x6705,  0x586E, -0x2109, -0x123E,  0x06C4,
     0x70FB,  0x29B1, -0x1564,  0x4EE4,  0x5265, -0x1DD3,  0x3E13,  0x3C9A,
     0x419F,  0x044C, -0x565D, -0x3096, -0x662C,  0x7125, -0x6E4F, -0x1AD2,
    -0x0F2A, -0x38EB, -0x0065, -0x48A2, -0x771A,  0x2A5E,  0x1D60, -0x7FE7,
     0x7B65,  0x63BD, -0x458E, -0x3C91,  0x35DF, -0x0D7B,  0x5423, -0x4297,
    -0x5205,  0x7BB7,  0x2330,  0x7558, -0x1435,  0x1EA6, -0x4E07, -0x081E,
     0x45FC,  0x2E8A,  0x6ECD,  0x304B, -0x0F97, -0x285A, -0x3222, -0x1177,
     0x4D8F,  0x1D65,  0x6755, -0x746F,  0x7E5F, -0x3908, -0x5CFA, -0x4898,
    -0x3F0E, -0x5005,  0x6244, -0x168A,  0x08A3, -0x086C,  0x2C5C, -0x076A,
     0x6701, -0x606A,  0x6B25,  0x536C, -0x4BD5,  0x022A,  0x2441,  0x627A,
    -0x08F9, -0x4293, -0x4891, -0x748C,  0x1EDC,  0x719D,  0x218B,  0x6056,
     0x72CE, -0x08C5,  0x4CA6,  0x68BF,  0x55B8,  0x6BB6, -0x253E,  0x1707,
    -0x3B14, -0x5BEC, -0x054C,  0x679A,  0x1C4D, -0x6AE5, -0x3F62, -0x68EE,
    -0x59B0,  0x057E, -0x7B72, -0x756E,  0x675F,  0x3F88, -0x3A3B,  0x55E6,
    -0x47EE,  0x12C6,  0x100E,  0x68DA,  0x1DDB, -0x37C2,  0x6ECB, -0x1C9E,
    -0x197F,  0x7B94, -0x28EF, -0x750F,  0x1506,  0x49C3,  0x2670, -0x1A61,
     0x046F, -0x083B,  0x17D8, -0x0178,  0x57E6,  0x75CF, -0x38E3,  0x4AF1,
    -0x523D, -0x3A83,  0x3CA3,  0x30AA, -0x660C, -0x3776,  0x6CA2, -0x3ECD,
     0x6245,  0x7582,  0x5492,  0x0322,  0x010A, -0x1504, -0x7CCB,  0x7448,
    -0x1254, -0x0E32, -0x413F,  0x241D,  0x2291,  0x58C8,  0x18B1, -0x041B,

    -0x0414, -0x3D97,  0x18AA, -0x5AE8,  0x3DEC,  0x491E,  0x6513, -0x666C,
    -0x0138, -0x6785,  0x6EBE, -0x2C01, -0x41D2, -0x2609, -0x5BC6, -0x5502
},

};

short x_cn[NUM_INPUTS][2*N + 2*PAD];
short x_i[NUM_INPUTS][2*N + 2*PAD];

short y_cn[NUM_INPUTS][2*N + 2*PAD];
short y_i[NUM_INPUTS][2*N + 2*PAD];

short w[NUM_INPUTS][2*N + 2*PAD];

/* ======================================================================== */
/*  Prototypes for timing functions.                                        */
/* ======================================================================== */
clock_t time_cn(int cur_input, int n);
clock_t time_i(int cur_input, int n);

/* ======================================================================== */
/*  MAIN -- Top level driver for the test.                                  */
/* ======================================================================== */
int main()
{
    clock_t t_overhead, t_start, t_stop;
    clock_t t_cn, t_i;
    int i, j, k, m, n, radix, fail, p, q;
    short diff, diff_max;

    /* -------------------------------------------------------------------- */
    /* Initialize timer for clock */
    TSCL= 0,TSCH=0;
    /*  Compute the overhead of calling _itoll(TSCH, TSCL) twice to get timing info.   */
    /* -------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    t_stop = _itoll(TSCH, TSCL);
    t_overhead = t_stop - t_start;

    for (j = 0; j < NUM_INPUTS; j++) {
        for (i = 0; i < 2*N + 2*PAD; i++)
            x[j][i] = x[j][i] >> 4;
    }

    for(j = 16, k = 1, fail = 0; j <= N; k++, j *= 2) {
        for (n = 31, m = 1; (j & (1 << n)) == 0; n--, m++)
            ;
        radix = m & 1 ? 2 : 4;

        /* -------------------------------------------------------------------- */
        /*  Generate twiddle factors for fft of size 'j'                        */
        /* -------------------------------------------------------------------- */
        gen_twiddle_fft16x16_imre(&w[0][PAD], j);

        /* -------------------------------------------------------------------- */
        /*  Copy vector to all inputs.                                          */
        /* -------------------------------------------------------------------- */
        memcpy(x_cn, x, sizeof(x_cn));
        memcpy(x_i, x, sizeof(x_i));
        memcpy(y_i, y_cn, sizeof(y_i));

        /* -------------------------------------------------------------------- */
        /*  Check the results arrays, and report any failures.                  */
        /* -------------------------------------------------------------------- */
        for(i = 0; i < NUM_INPUTS; i++) {
            t_cn = time_cn(i, j) - t_overhead;
            t_i = time_i(i, j) - t_overhead;
        }

        printf("DSP_fft16x16_imre\tIter#: %d\t", k);

        diff_max = 0;
        for (p = 0; p < NUM_INPUTS; p++) {
            for (q = 0; q < 2*N + 2*PAD; q++) {
                diff = y_cn[p][q] - y_i[p][q];
                if (diff < 0)
                    diff = -diff;
                if (diff > diff_max)
                    diff_max = diff;
            } 
        }
 
        if (diff_max > 15) {
            fail++;
            printf("Result Failure (y_i) ");
        }
        else
            printf("Result Successful (y_i) ");

        printf("\tRadix = %d\tN = %d\tnatC: %d\tintC: %d\n", radix, j, t_cn, t_i);

        if (j == CYCLE_FORMULA_NX_PT1)
          form_cycle[0] = t_i;
        if (j == CYCLE_FORMULA_NX_PT2)
          form_cycle[1] = t_i;
    }

    /* Provide memory information */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
    printf("Memory:  %d bytes\n", &kernel_size);
#endif

    /* Provide profiling information */
    printf("Cycles:  %d (N=128) %d (N=256)\n", form_cycle[0], form_cycle[1]);

    return (fail);
}

/* ======================================================================== */
/*  TIME_CN  -- Measure elapsed time for natural C version.                 */
/* ======================================================================== */
clock_t time_cn(int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_fft16x16_imre_cn(&w[cur_input][PAD], n, &x_cn[cur_input][PAD], &y_cn[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  TIME_I   -- Measure elapsed time for intrinsic C version.               */
/* ======================================================================== */
clock_t time_i(int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_fft16x16_imre(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_fft16x16_imre_d.c                                     */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

