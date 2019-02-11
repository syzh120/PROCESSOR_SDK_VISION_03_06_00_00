/* ======================================================================= */
/* DSP_mat_mul_d.c -- Perform Matrix Multiplication                        */
/*                    Driver code implementation                           */
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

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <c6x.h>

#include "DSP_mat_mul_cn.h"
#include "DSP_mat_mul.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;

#define FORMULA_SIZE          8
#define FORMULA_DEVIDE        8
#define CYCLE_FORMULA_R1_PT1  12
#define CYCLE_FORMULA_R1_PT2  8
#define CYCLE_FORMULA_R2_PT1  12
#define CYCLE_FORMULA_R2_PT2  8
#define CYCLE_FORMULA_C2_PT1  12
#define CYCLE_FORMULA_C2_PT2  8
/* inverse of [12*12*12 12*12 12*12 12*12 12 12 12 1] */
/*            [12*12* 8 12*12 12* 8 12* 8 12 12  8 1] */
/*            [12* 8*12 12* 8 12*12  8*12 12  8 12 1] */
/*            [ 8*12*12  8*12  8*12 12*12  8 12 12 1] */
/*            [12* 8* 8 12* 8 12* 8  8* 8 12  8  8 1] */
/*            [ 8*12* 8  8*12  8* 8 12* 8  8 12  8 1] */
/*            [ 8* 8*12  8* 8  8*12  8*12  8  8 12 1] */
/*            [ 8* 8* 8  8* 8  8* 8  8* 8  8  8  8 1] */
float form_inv[FORMULA_SIZE][FORMULA_SIZE] = 
{{ 0.0156,   -0.0156,   -0.0156,   -0.0156,    0.0156,    0.0156,    0.0156,   -0.0156},
 {-0.1250,    0.1875,    0.1250,    0.1250,   -0.1875,   -0.1875,   -0.1250,    0.1875},
 {-0.1250,    0.1250,    0.1875,    0.1250,   -0.1875,   -0.1250,   -0.1875,    0.1875},
 {-0.1250,    0.1250,    0.1250,    0.1875,   -0.1250,   -0.1875,   -0.1875,    0.1875},
 { 1.0000,   -1.5000,   -1.5000,   -1.0000,    2.2500,    1.5000,    1.5000,   -2.2500},
 { 1.0000,   -1.5000,   -1.0000,   -1.5000,    1.5000,    2.2500,    1.5000,   -2.2500},
 { 1.0000,   -1.0000,   -1.5000,   -1.5000,    1.5000,    1.5000,    2.2500,   -2.2500},
 {-8.0000,   12.0000,   12.0000,   12.0000,  -18.0000,  -18.0000,  -18.0000,   27.0000}
};
float form_temp  [FORMULA_SIZE];
int   form_cycle [FORMULA_SIZE];
int   form_result[FORMULA_SIZE];

/* ======================================================================== */
/*  Kernel-specific alignments                                              */
/* ======================================================================== */
#pragma DATA_ALIGN(x, 8);
#pragma DATA_ALIGN(y, 8);
#pragma DATA_ALIGN(r_c, 8);
#pragma DATA_ALIGN(r_i, 8);

/* ======================================================================== */
/*  Parameters of fixed dataset.                                            */
/* ======================================================================== */
#define R1   (12)
#define C1R2 (12)
#define   C2 (16)
#define R1C1 (144)
#define R1C2 (192)
#define R2C2 (192)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
const short x[R1C1] =
{
     0x453E, -0x321D,  0x2DBB,  0x77C7, -0x57B9, -0x4ADD,  0x10B7, -0x113F,
    -0x1A92,  0x7CA7,  0x4A14,  0x719D,  0x3E61,  0x1858, -0x0D4C,  0x3D94,
    -0x32B8, -0x14B2,  0x1B6A,  0x7A1D,  0x0D5B,  0x1D2C,  0x55D8, -0x5459,
     0x5030, -0x5CBD,  0x0180,  0x059B,  0x4D97,  0x49E3,  0x68A4, -0x3629,
    -0x7AA5, -0x582E,  0x1D05,  0x3A65, -0x4734,  0x3D6B, -0x6CE3,  0x4A99,
     0x1D54, -0x50B4,  0x62F5, -0x75A7, -0x6AFA,  0x5D26,  0x3C1A, -0x793D,
    -0x6493,  0x4282, -0x0020,  0x1BE0,  0x1A7F,  0x621B, -0x1C86, -0x254E,
    -0x12FB, -0x4E5B,  0x3409,  0x223E,  0x3856, -0x4179, -0x60C9, -0x102C,
     0x5EB6, -0x097B,  0x7A6E,  0x1450, -0x41CD, -0x133A,  0x0358, -0x2677,
    -0x0BA0,  0x6732,  0x19A5, -0x4961, -0x1E47, -0x6657,  0x57C6,  0x1E70,
     0x1F12,  0x59F9,  0x13A4,  0x16D9,  0x26E6, -0x4FE0,  0x39FA, -0x6AF4,
    -0x2829, -0x673F,  0x7460,  0x57A6, -0x5BB4,  0x424C, -0x6068,  0x2CC9,
     0x0F61, -0x4030, -0x00AD,  0x6AE1, -0x4FD3,  0x56ED,  0x2FDA, -0x759C,
    -0x726F,  0x78E3,  0x42DF, -0x63D3, -0x1F88, -0x71D0,  0x07E8, -0x6D4A,
     0x21E5, -0x6C4D, -0x0072,  0x0EEE,  0x749D, -0x4622, -0x2AF7, -0x3A2B,
     0x70E2,  0xDD6F,  0x43FB,  0x9C71,  0x8C6F,  0x0CF5,  0x5D09,  0x8FFC,
     0x88CD,  0xF1FE,  0x27CF,  0xFBC7,  0xF178,  0xB465,  0x4A93,  0x296F,
     0x2FCF,  0x1C8A,  0x85B0,  0x2953,  0x3804,  0x63D3,  0x7398,  0x840E,
};

const short y[R2C2] =
{
     0x126C,  0x3DE7, -0x754D,  0x360C, -0x2589, -0x2234, -0x2DAF, -0x7E1F,
     0x022A, -0x4C8A, -0x34A6,  0x2A23, -0x5A1A,  0x4B95, -0x0317,  0x7430,
    -0x7091, -0x0CC1, -0x0A3E, -0x7AFE,  0x645A, -0x50BD,  0x0909,  0x6090,
     0x34AE, -0x56B3, -0x3AA9,  0x438B,  0x1C64,  0x62BE, -0x5E6A,  0x7A07,
     0x0D08,  0x6089, -0x5D4D,  0x0B27,  0x4A2C,  0x79F5,  0x5A86,  0x4061,
    -0x4411, -0x6674,  0x19FC,  0x7F77, -0x4EBE,  0x0E21, -0x5D11,  0x72BE,
     0x2232,  0x4040,  0x3DA5, -0x1736,  0x10DD, -0x192A, -0x768A,  0x770A,
     0x1261, -0x788B, -0x2778,  0x4989, -0x4999,  0x7905,  0x6F1E,  0x184B,
    -0x3C6D,  0x1543, -0x6F94, -0x3588, -0x0D80,  0x57D4, -0x728A, -0x5E27,
     0x4092, -0x59A4, -0x2322, -0x762C,  0x684B, -0x0AA5,  0x5F2B,  0x5F6B,
    -0x5CA5, -0x01CC, -0x1F8D, -0x35A1,  0x432A, -0x35C6, -0x0E0F, -0x7FEF,
     0x3D0B,  0x3D0B,  0x2B67, -0x7BC7,  0x48D5, -0x1FE3,  0x0ADA,  0x4F02,
    -0x69DF, -0x6226,  0x4E99,  0x52AC, -0x322F, -0x4CF2,  0x34FE, -0x26B0,
     0x512C, -0x7CE4,  0x59F0, -0x4137, -0x7CBE, -0x7F4B, -0x5471, -0x1A85,
    -0x0F38, -0x0883,  0x3513, -0x0813,  0x322B, -0x1C8F,  0x2643,  0x59E8,
     0x7410,  0x7F60, -0x1D73, -0x27DB,  0x48FD, -0x1AAB, -0x7DD7, -0x0BD5,
    -0x1CA4,  0x524B, -0x71B5,  0x5C6E,  0x4C92,  0x6100,  0x4ED3,  0x7244,
    -0x5594, -0x12C8, -0x6F88,  0x6EDB,  0x3284, -0x36A5,  0x33E6,  0x05AC,
    -0x1E10,  0x13B5,  0x49C1,  0x1399, -0x721F,  0x5033,  0x430D,  0x3B48,
     0x6B6D,  0x18FB, -0x2711, -0x0233, -0x5DBB,  0x6FB3,  0x2341,  0x3640,
    -0x027C, -0x5C31, -0x4715,  0x795B,  0x5C52, -0x3241,  0x1380,  0x50AE,
    -0x0365, -0x42AD,  0x3917, -0x4178,  0x2082, -0x7CCF, -0x222D,  0x1931,
     0x46E0,  0x4CAF, -0x1DED, -0x6482,  0x7B64, -0x340E, -0x623A, -0x4B9A,
    -0x2D4B, -0x1563, -0x5F28, -0x7754, -0x44D3, -0x030A,  0x6E31, -0x67CF,
};

short r_c[R1C2];
short r_i[R1C2];

// Right shift the result by qs bits
int qs =  0x00000001;

/* ======================================================================== */
/*  Generate pointers to point to matrices                                  */
/* ======================================================================== */
const short *const ptr_x = x;
const short *const ptr_y = y;
short *const ptr_r_c = r_c;
short *const ptr_r_i = r_i;

/* ======================================================================== */
/*  Prototypes for timing functions.                                        */
/* ======================================================================== */
clock_t time_c(int r1, int c1r2, int c2);
clock_t time_i(int r1, int c1r2, int c2);

/* ======================================================================== */
/*  MAIN -- Top level driver for the test.                                  */
/* ======================================================================== */
int main()
{   
    clock_t t_overhead, t_start, t_stop;
    clock_t t_c, t_i;
    int i, j, r1 = R1, c1r2 = C1R2, c2 = C2, fail = 0;
    int form_error = 0;

    /* -------------------------------------------------------------------- */
    /* Initialize timer for clock */
    TSCL= 0,TSCH=0;
    /*  Compute the overhead of calling _itoll(TSCH, TSCL) twice to get timing info.   */
    /* -------------------------------------------------------------------- */
    t_start    = _itoll(TSCH, TSCL);
    t_stop     = _itoll(TSCH, TSCL);
    t_overhead = t_stop - t_start;

    for(r1 = 8, i = 1; r1 <= R1; r1 += 2) {
        for(c1r2 = 8; c1r2 <= C1R2; c1r2 += 2) {
            for(c2 = 4; c2 <= C2; i++, c2 += 4) {
                /* -------------------------------------------------------- */
                /*  Force uninitialized arrays to fixed values.             */
                /* -------------------------------------------------------- */
                memset(r_c, 0xA5, sizeof(r_c));
                memset(r_i, 0xA5, sizeof(r_i));

                /* -------------------------------------------------------- */
                /*  Call the individual timing routines, rhead.             */
                /*  and subtract off overhead.                              */
                /* -------------------------------------------------------- */
                t_c = time_c(r1, c1r2, c2) - t_overhead;
                t_i = time_i(r1, c1r2, c2) - t_overhead;

                /* -------------------------------------------------------- */
                /*  Print timing results.                                   */
                /* -------------------------------------------------------- */
                printf("DSP_mat_mul\tIter#: %d\t", i);

                /* -------------------------------------------------------- */
                /*  Check the results arrays, and report any failures.      */
                /* -------------------------------------------------------- */
                if (memcmp(r_i, r_c, sizeof(r_c))) {
                    fail++;
                    printf("Result Failure (r_i)");
                }
                else
                    printf("Result Succesful (r_i)");

                printf("\tR1 = %d\tC1R2 = %d\tC2 = %d\tnatC: %d\tintC: %d\n", r1, c1r2, c2, t_c, t_i);

                if (c2 == CYCLE_FORMULA_C2_PT1 && c1r2 == CYCLE_FORMULA_R2_PT1 && r1 == CYCLE_FORMULA_R1_PT1)
                    form_cycle[0] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT1 && c1r2 == CYCLE_FORMULA_R2_PT2 && r1 == CYCLE_FORMULA_R1_PT1)
                    form_cycle[1] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT2 && c1r2 == CYCLE_FORMULA_R2_PT1 && r1 == CYCLE_FORMULA_R1_PT1)
                    form_cycle[2] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT1 && c1r2 == CYCLE_FORMULA_R2_PT1 && r1 == CYCLE_FORMULA_R1_PT2)
                    form_cycle[3] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT2 && c1r2 == CYCLE_FORMULA_R2_PT2 && r1 == CYCLE_FORMULA_R1_PT1)
                    form_cycle[4] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT1 && c1r2 == CYCLE_FORMULA_R2_PT2 && r1 == CYCLE_FORMULA_R1_PT2)
                    form_cycle[5] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT2 && c1r2 == CYCLE_FORMULA_R2_PT1 && r1 == CYCLE_FORMULA_R1_PT2)
                    form_cycle[6] = t_i;
                if (c2 == CYCLE_FORMULA_C2_PT2 && c1r2 == CYCLE_FORMULA_R2_PT2 && r1 == CYCLE_FORMULA_R1_PT2)
                    form_cycle[7] = t_i;
           }
        }
    }

    /* Provide memory information */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
    printf("Memory:  %d bytes\n", &kernel_size);
#endif

    /* Provide profiling information */
    for (i = 0; i < FORMULA_SIZE; i++) {
        form_temp[i] = 0;
        for (j = 0; j < FORMULA_SIZE; j++) {
            form_temp[i] += form_inv[i][j] * form_cycle[j];
        }
        if (i != (FORMULA_SIZE-1)) {
            form_result[i] = (int) (form_temp[i] * FORMULA_DEVIDE + 0.5);
            if ((form_result[i] - form_temp[i] * FORMULA_DEVIDE) >  0.1 ||
                (form_result[i] - form_temp[i] * FORMULA_DEVIDE) < -0.1) {
                form_error = 1;
            }
        }
        else {
            form_result[i] = (int) (form_temp[i] + 0.5);
        }
    }

    if (!form_error) {
      printf("Cycles:  ");
      if (form_result[0])
        printf("%d/%d*r1*c2*c1 + ", form_result[0], FORMULA_DEVIDE);
      if (form_result[1])
        printf("%d/%d*r1*c2 + ", form_result[1], FORMULA_DEVIDE);
      if (form_result[2])
        printf("%d/%d*r1*c1 + ", form_result[2], FORMULA_DEVIDE);
      if (form_result[3])
        printf("%d/%d*c2*c1 + ", form_result[3], FORMULA_DEVIDE);
      if (form_result[4])
        printf("%d/%d*r1 + ", form_result[4], FORMULA_DEVIDE);
      if (form_result[5])
        printf("%d/%d*c2 + ", form_result[5], FORMULA_DEVIDE);
      if (form_result[6])
        printf("%d/%d*c1 + ", form_result[6], FORMULA_DEVIDE);
      if (form_result[7])
        printf("%d\n", form_result[7]);
    }
    else
      printf("Cycles Formula Not Available\n");

    return (fail);
}

/* ======================================================================== */
/*  TIME_C   -- Measure elapsed time for natural C version.                 */
/* ======================================================================== */
clock_t time_c(int r1, int c1r2, int c2)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_mat_mul_cn(ptr_x, r1, c1r2, ptr_y, c2, ptr_r_c, qs);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  TIME_I   -- Measure elapsed time for intrinsic C version.               */
/* ======================================================================== */
clock_t time_i(int r1, int c1r2, int c2)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_mat_mul(ptr_x, r1, c1r2, ptr_y, c2, ptr_r_i, qs);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_mat_mul_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

