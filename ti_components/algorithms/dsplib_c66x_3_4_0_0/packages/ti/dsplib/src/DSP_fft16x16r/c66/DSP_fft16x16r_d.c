/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fft16x16r -- Driver file for fft16x16r                         */
/*                                                                         */
/*  USAGE                                                                  */
/*    This code contains a driver program for testing the 'DSP_fft16x16r'  */
/*    kernel.  The function prototype appears below.  The driver itself    */
/*    is invoked as a standard C program, and results are reported on      */
/*    stdout. The driver will use a fixed test vector.                     */
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

#include "DSP_fft16x16r_cn.h"
#include "DSP_fft16x16r.h"
#include "gen_twiddle_fft16x16r.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;
#define CYCLE_FORMULA_NX_PT1  128
#define CYCLE_FORMULA_NX_PT2  256
#define FORMULA_SIZE          2
int     form_cycle [FORMULA_SIZE];

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
#define NUM_INPUTS  (1)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
short x[NUM_INPUTS][2*N + 2*PAD] =
{
/* Input Number: 0 */

{
    -0x1460, -0x0BA5,  0x0BA3, -0x67DE,  0x20CE,  0x6ED0, -0x60B1,  0x1A10,
    -0x6D6C, -0x5D87,  0x5022,  0x2A31,  0x2457, -0x6AF5,  0x162D, -0x2DA9,

     0x467E, -0x1605,  0x7C61,  0x1296, -0x176D,  0x5FB4,  0x2A11, -0x3397,
     0x2C4C, -0x3E38,  0x619E,  0x4D14,  0x5FF1, -0x505C,  0x0CB9, -0x0536,
    -0x4A57, -0x2CBA, -0x2F2C, -0x53F1,  0x4C1F, -0x098C, -0x62D9,  0x24E5,
    -0x0BEF, -0x7F10,  0x4CDE,  0x2E2E,  0x3D3A, -0x27CA, -0x421C, -0x1B27,
     0x441F,  0x2B2F, -0x072F, -0x69BA, -0x2FC3,  0x176E, -0x2387, -0x2587,
     0x2518, -0x4394, -0x3A64,  0x407C,  0x2DAC, -0x4CBD, -0x38CE,  0x2796,
     0x59BD,  0x696B, -0x1F1C,  0x3DAE, -0x3578,  0x5CF9, -0x46E8,  0x1F84,
     0x4656, -0x3E23,  0x6628, -0x5BE7,  0x6675,  0x0FA4, -0x54CD,  0x45E3,
    -0x6AFC, -0x12C8,  0x4D18,  0x303D,  0x4B31,  0x0323, -0x20FB,  0x7E9E,
     0x114C,  0x3AD0, -0x66C9,  0x1107, -0x33C3, -0x30AE, -0x4AB5, -0x70C5,
    -0x391C, -0x1ED9, -0x3644,  0x0933,  0x04CC, -0x2E7F, -0x4A06, -0x35A8,
     0x5EC8,  0x108A, -0x7A57, -0x3F09, -0x2710, -0x2CD3, -0x1C85,  0x117A,
    -0x3A80,  0x2BE2, -0x72D0,  0x59E4,  0x310F, -0x060D,  0x4B2F,  0x020A,
     0x06B4,  0x59CD, -0x12B3,  0x4E10, -0x7E7A, -0x1F39, -0x2FD9,  0x78A4,
     0x67F9,  0x4AF4,  0x65A8, -0x7983,  0x7FA3,  0x096C,  0x3E27,  0x3B98,
    -0x3023,  0x3CA0,  0x1FAF, -0x5446,  0x25C9, -0x7BD8, -0x681F, -0x0450,
     0x5F37,  0x4792, -0x6508, -0x3F31, -0x0A19, -0x2F45, -0x5C8C, -0x79C6,
     0x54B5, -0x23E7, -0x2524, -0x049F,  0x701F,  0x0697, -0x40D4,  0x404A,
     0x26AC, -0x689B, -0x25A7, -0x22EA, -0x2347,  0x4253, -0x1180, -0x25BB,
    -0x16DE,  0x3D23,  0x362D, -0x7BBF,  0x4250,  0x4665,  0x244C,  0x49A3,
    -0x16DE,  0x084E,  0x2134,  0x49C1, -0x57C1,  0x6513, -0x26AA, -0x020A,
    -0x75BC,  0x2D47, -0x73F6, -0x6ED3, -0x66AF, -0x554F, -0x26FA,  0x5931,
     0x6980, -0x5CD2, -0x621A, -0x14C8, -0x2251,  0x3A0E,  0x4E68,  0x6831,
    -0x45C7,  0x2C74,  0x5BB9,  0x5F57,  0x7B0B,  0x0233,  0x166B, -0x2682,
    -0x1670, -0x654D, -0x6274,  0x0DA7, -0x06ED, -0x62AE,  0x4D5B,  0x3254,
     0x74EC,  0x57C5,  0x371F, -0x00EA, -0x25E2,  0x7601,  0x1EA2,  0x48E9,
     0x12CD,  0x2D1B,  0x70C8,  0x44C5,  0x5E18,  0x37B0, -0x2B38, -0x070A,
     0x0DD7,  0x4B4F, -0x5472,  0x45B2,  0x7FB2,  0x685C,  0x26AE,  0x1C76,
    -0x1FDD, -0x6F02,  0x568B,  0x5A9C,  0x34D0,  0x5F87, -0x36F3, -0x3B4B,
     0x1DCD,  0x0FDF,  0x2188, -0x56D7, -0x11C8,  0x5E71,  0x3E36, -0x5371,
    -0x7B41, -0x27EA,  0x62DC,  0x334F,  0x587E,  0x0488, -0x1EF3, -0x0B04,
     0x68C4, -0x0133, -0x3176,  0x34F7,  0x5535, -0x13D9,  0x394B,  0x19D0,
     0x4FD1, -0x20F9,  0x63A1, -0x4A1B,  0x415A, -0x677F, -0x7804,  0x27C8,
    -0x3667, -0x5345, -0x662B,  0x66DF,  0x6D07, -0x671C, -0x6AC9,  0x35CC,
    -0x65A9,  0x2E26, -0x309B, -0x4BEF, -0x1AA3, -0x0DDD, -0x39DA,  0x1C76,
     0x13DD, -0x2F9C, -0x01CE,  0x1FB4,  0x66B4, -0x39AA,  0x633D,  0x6CD9,
    -0x4F1B, -0x1BBD, -0x59DD, -0x2A0A, -0x59F8,  0x3BCA,  0x2EB9, -0x5B79,
    -0x0167,  0x2C5D, -0x0143, -0x79E2, -0x3258, -0x60C5,  0x2E63, -0x552B,
    -0x4D96, -0x6093,  0x600A,  0x7BF4,  0x3828, -0x2AB8, -0x4076, -0x7C9A,
     0x0E16,  0x72E5, -0x0053, -0x0F9A,  0x7687, -0x08D7, -0x1BC0,  0x46EE,
     0x7FFC,  0x61C1, -0x2FB7, -0x5593, -0x775C,  0x40A8, -0x2E23,  0x5A37,
     0x7BA8,  0x31A5, -0x44E7, -0x33C7,  0x60EB,  0x3554, -0x4046, -0x1795,
    -0x5D60,  0x7D2A,  0x0DD4, -0x0D72, -0x5BBE,  0x08FB, -0x07CF, -0x6D68,
     0x1A74, -0x4782,  0x23C6, -0x7A8C, -0x5AC9,  0x405A,  0x2AD7,  0x6F76,
     0x320C,  0x7B2F,  0x5C30,  0x5616, -0x5A91, -0x5AE4, -0x0EFE,  0x3E6C,
     0x4137,  0x034E,  0x49E8,  0x70EC,  0x5755,  0x6108, -0x5380, -0x2023,
    -0x3E8A,  0x02B8,  0x1834,  0x351F, -0x68F9,  0x6B7C, -0x7768,  0x09A4,
    -0x4CF0, -0x6148,  0x49EE, -0x4ECD,  0x7284,  0x2D23, -0x2FB6,  0x42E4,
     0x3E5A, -0x412A, -0x6827,  0x32E7,  0x5E1C,  0x6CE7,  0x7DC9,  0x1905,
    -0x76B7, -0x7010,  0x2E4A,  0x2162, -0x41E2,  0x6E2D,  0x083D, -0x69FC,
    -0x1EC1,  0x4C8E,  0x14FC,  0x1995, -0x603D,  0x634A,  0x73C2, -0x0410,
     0x151B,  0x427B, -0x22C8,  0x3CE3, -0x46A0,  0x0B35, -0x625F, -0x4E48,
     0x1383,  0x1C9C, -0x67D6, -0x33FC, -0x532C, -0x637E, -0x2E2C, -0x77D4,
    -0x3288,  0x6900, -0x037A,  0x0233, -0x7FCC, -0x126B, -0x6E41,  0x2A46,
     0x5320,  0x5F3F, -0x209C,  0x268A,  0x66B9, -0x24E4, -0x53CB, -0x2E53,
     0x35D5, -0x15F7, -0x25A2, -0x1B4F, -0x4B0C, -0x123F, -0x7752,  0x4280,
     0x2176, -0x14FF,  0x43EC, -0x1842,  0x2833,  0x4324, -0x4B34,  0x0159,
    -0x3B10, -0x3931,  0x5608, -0x54A0,  0x6538, -0x4AF2, -0x4CE9, -0x346B,
    -0x1AEE,  0x247B, -0x5BF8, -0x66BD, -0x4EDF,  0x41E8,  0x13FA,  0x4AD7,
    -0x3569,  0x0000, -0x3845,  0x5DB6, -0x0666, -0x528B, -0x4BFE,  0x10D3,
    -0x2B89, -0x19DD,  0x4CCD,  0x7B90,  0x0849,  0x72C2,  0x5C5E, -0x34B0,
     0x5F73, -0x7B77, -0x18A2,  0x295A,  0x127F, -0x1E9F, -0x7766, -0x408F,
    -0x1F1C,  0x6A0F, -0x2219,  0x66B4,  0x6723, -0x7421,  0x73A1,  0x7A3A,
     0x45CC,  0x135C, -0x48AE,  0x4EF7,  0x7AE2, -0x1689,  0x6FF6, -0x32A9,

    -0x6AE1,  0x2FBD,  0x325F, -0x49DE,  0x1F9C,  0x420A,  0x6E3A,  0x0620,
    -0x2FAB,  0x2638,  0x6B3B,  0x01FC,  0x0915, -0x2DA9, -0x2A1E,  0x62E5
},

};

short x_cn[NUM_INPUTS][2*N + 2*PAD];
short x_i [NUM_INPUTS][2*N + 2*PAD];

short y_cn[NUM_INPUTS][2*N + 2*PAD];
short y_i [NUM_INPUTS][2*N + 2*PAD];

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

    for (j = 16, k = 1, fail = 0; j <= N; k++, j *= 2) {
        t_cn = 0;
        t_i = 0;

        for (n = 31, m = 1; (j & (1 << n)) == 0; n--, m++)
            ;
        radix = m & 1 ? 2 : 4;

        /* -------------------------------------------------------------------- */
        /*  Generate twiddle factors for fft of size 'j'                        */
        /* -------------------------------------------------------------------- */
        gen_twiddle_fft16x16r(&w[0][PAD], j);

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
            t_cn += time_cn(i, j) - t_overhead;
            t_i += time_i(i, j) - t_overhead;
        }

        printf("DSP_fft16x16_r\tIter#: %d\t", k);

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
    int i, j, radix;
    clock_t t_start, t_stop;

    for (i = 31, j = 1; (n & (1 << i)) == 0; i--, j++)
        ;
    radix = j & 1 ? 2 : 4;

    t_start = _itoll(TSCH, TSCL);
    DSP_fft16x16r_cn(n, &x_cn[cur_input][PAD], &w[cur_input][PAD], &y_cn[cur_input][PAD], radix, 0, n);
    t_stop  = _itoll(TSCH, TSCL);
    return (t_stop - t_start);
}

/* ======================================================================== */
/*  TIME_I   -- Measure elapsed time for intrinsic C version.               */
/* ======================================================================== */
clock_t time_i(int cur_input, int n)
{   
    int i, j, radix;
    clock_t t_start, t_stop;

    for (i = 31, j = 1; (n & (1 << i)) == 0; i--, j++)
        ;
    radix = j & 1 ? 2 : 4;

    t_start = _itoll(TSCH, TSCL);
    DSP_fft16x16r(n, &x_i[cur_input][PAD], &w[cur_input][PAD], &y_i[cur_input][PAD], radix, 0, n);
    t_stop  = _itoll(TSCH, TSCL);
    return (t_stop - t_start);
}

/* ======================================================================== */
/*  End of file:  DSP_fft16x16r_d.c                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

