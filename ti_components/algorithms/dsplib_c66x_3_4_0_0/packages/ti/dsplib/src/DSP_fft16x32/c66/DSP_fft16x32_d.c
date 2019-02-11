/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fft16x32_d.c -- Driver file for DSP_fft16x32                   */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'DSP_fft16x32' */
/*      kernel.  The function prototype appears below.  The driver itself  */
/*      is invoked as a standard C program, and results are reported on    */
/*      stdout.                                                            */
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

#include "DSP_fft16x32_cn.h"
#include "DSP_fft16x32.h"
#include "gen_twiddle_fft16x32.h"

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
#define NUM_INPUTS (1)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
int x[NUM_INPUTS][2*N + 2*PAD] = 
{
/* Input Number: 0 */

{
    -0x56E4B1, -0x030C65, -0x336D71,  0x52420A,
     0x0840E7, -0x64D54D,  0x5D8FA6, -0x1DCE5D,
    -0x59DB96, -0x2DEB28,  0x393FA5, -0x38C502,
     0x4B8A5E, -0x6BD6C1,  0x488687, -0x3AB9DF,

    -0x750239,  0x7568E8,  0x162B88, -0x0CF711,
     0x597696, -0x27EC27,  0x01EDB9,  0x4AAEC4,
     0x6EEFFB, -0x7E934F,  0x63ABA1, -0x24363D,
    -0x21AC0B,  0x08EB3F,  0x4B3C65,  0x22F93D,
    -0x7EB44C, -0x4A7A84,  0x2E5A08,  0x09E1DD,
    -0x5E88AF,  0x3F606D,  0x29392B,  0x04CCF2,
     0x647B42, -0x0E6682,  0x4139E5, -0x215B97,
    -0x798BD2, -0x487E45,  0x2A3A20, -0x5D5D0F,
    -0x33B088, -0x791E79,  0x13100D,  0x2E3BD8,
    -0x3681D5, -0x4A47CF, -0x0762E9, -0x1927F4,
     0x5E8EAB, -0x4AFC00, -0x08F815,  0x13C8BF,
    -0x7DE04E, -0x5203DA,  0x2B8D14,  0x62F250,
    -0x2E3FEB,  0x7E6523, -0x747868,  0x08D0CC,
     0x5F24E6, -0x55B6E9,  0x52FB20,  0x0D1FA6,
     0x4C4156, -0x5D3989,  0x665A43,  0x3CDD1B,
    -0x59351F, -0x0AAA42,  0x48DF3D,  0x37FFBF,
     0x068B52, -0x13EC80,  0x0907D1,  0x2F6ABB,
     0x772B13, -0x017692, -0x3F4B57, -0x3D50C5,
     0x23C73C, -0x47823B,  0x0D6EBD, -0x7DFB86,
     0x45F202,  0x7F35AB,  0x163B60, -0x66F9ED,
    -0x276518, -0x443000, -0x6C53C5,  0x17B2E7,
    -0x65BCC8, -0x18F9F9,  0x5B74E5,  0x652543,
    -0x3BCCA6,  0x090799, -0x0CCB6E,  0x5F9BA6,
     0x15ED6A,  0x03BE31, -0x5522CA, -0x76CB46,
    -0x6A6461,  0x5D2866, -0x52CD35, -0x07100C,
    -0x562B05, -0x20D8A3, -0x4E0BEA,  0x537270,
    -0x1BBE2B, -0x5EAB65, -0x6CDB7B, -0x7EF694,
     0x1DA69C, -0x0CB031, -0x790E73,  0x7871E8,
     0x53CB80, -0x4CE1FC,  0x40BC1E, -0x4B28EA,
    -0x363BB3, -0x790742, -0x4E385A, -0x335B39,
    -0x0EDEDD,  0x6F2586, -0x4001ED, -0x467E50,
    -0x678D82,  0x595268,  0x7F6274,  0x3323C0,
    -0x294301, -0x0A162C, -0x7E6463, -0x3EAFCC,
     0x46438C, -0x74108F, -0x6FDDAC, -0x1F5038,
     0x013836,  0x2DDE62, -0x776C68, -0x232F5A,
    -0x20348E, -0x3A028D, -0x5A6298, -0x39058D,
     0x7C1C15, -0x693A53, -0x25EC5F,  0x113B15,
    -0x7F734E, -0x66471F, -0x4D61A1,  0x5331A1,
    -0x4B105B,  0x4544A0,  0x2C9175, -0x4DE10E,
     0x52228C,  0x332219,  0x295E71,  0x67B96D,
     0x218078,  0x33B864, -0x2BD462, -0x08C279,
    -0x2F4A8D,  0x39FAC3, -0x6FF759, -0x77C0B1,
     0x1D78C8, -0x42B1B8, -0x09B9C0, -0x29422F,
     0x3EA3B2, -0x0A0F9A,  0x497353,  0x5DF884,
     0x0A29B9,  0x7558FC, -0x0692B3,  0x15867E,
     0x70726E, -0x43E1BF, -0x5ADC23,  0x642AC1,
    -0x53680D,  0x1EE517,  0x2C6CDC, -0x5813BE,
    -0x3B0337, -0x694199,  0x3487B4, -0x160EEC,
    -0x333290, -0x02693D, -0x3D4C2F,  0x3E964D,
     0x65DE55,  0x241D18,  0x5174A2,  0x3D480C,
     0x14678C,  0x59B3B8, -0x0A104C,  0x27A22B,
    -0x38D82E, -0x372BA5, -0x0A16C0,  0x2D492B,
     0x32615F,  0x48847F,  0x7DECDE,  0x5F0BBE,
     0x67430D,  0x0C3ED0, -0x3CF745, -0x434477,
     0x342640, -0x4C1A21,  0x3EB4D4, -0x15AC75,
    -0x33CFDE,  0x4930D5,  0x5A56D4,  0x15D3B8,
     0x2ADEA4, -0x62E165,  0x35E7E7,  0x6B6442,
    -0x3A1B21, -0x711629, -0x1EC5D6, -0x37C401,
     0x00FB25, -0x530790, -0x579DE5, -0x044470,
    -0x18FE81, -0x35AE14, -0x254355,  0x3D5CAB,
    -0x59F527, -0x11EDB9, -0x67E8BF,  0x40CC18,
     0x51C196,  0x2E67AD,  0x2F8162,  0x6DDDCF,
     0x67BEE0, -0x1B824F,  0x6C2E5C, -0x3B5931,
    -0x5CD9B7, -0x2601AA, -0x7EF687, -0x248EE2,
    -0x73BFC5, -0x3A765D, -0x1B9FB9, -0x72208B,
     0x4763B4, -0x4152EF, -0x46CF92, -0x3927E5,
     0x3BC0D3,  0x08E46A,  0x449A8B, -0x0A4B98,
    -0x176B58, -0x35F364, -0x2A135E, -0x58D781,
    -0x69C428,  0x29EBE9, -0x372673, -0x408A56,
     0x36A18F,  0x4B251C, -0x05B8F0, -0x1EAC18,
     0x1A9342, -0x4ABDEE,  0x5046E2,  0x702629,
    -0x1C8953, -0x65D4C4, -0x405DAA, -0x3F1547,
     0x3FD8B2, -0x765469,  0x5299FE, -0x1997B2,
    -0x1A9580,  0x00737B, -0x3DCD0E, -0x54D7B3,
     0x57D579,  0x631BEF,  0x06B30A,  0x2DA1BB,
    -0x0F0D82, -0x22572C,  0x72BCC1, -0x65CAA7,
    -0x531D13, -0x5EEF74, -0x2981F4, -0x65A09B,
     0x3D8C01,  0x114188,  0x2297C9, -0x2B5167,
    -0x1E0E08,  0x4D274A,  0x100D43,  0x22FDC9,
    -0x7E0F84, -0x5CC7BA,  0x55E831, -0x1F9548,
    -0x702413,  0x64F63A, -0x2D0B30, -0x136F76,
     0x327CE4, -0x5BFE87,  0x501E84, -0x427E86,
     0x29EF95,  0x591D8C,  0x3BF08C,  0x2E0527,
     0x04E46C,  0x5FC0E4, -0x1649C7,  0x5E9322,
     0x14C187, -0x1C5F2F, -0x2443C9,  0x438F14,
    -0x57DF90, -0x49417D, -0x6CCB96,  0x5A4B22,
     0x0D36AE, -0x028592,  0x5E35CB, -0x00BA06,
    -0x31695C, -0x2EE068, -0x4D9B21, -0x15D600,
    -0x3B29D8,  0x35775A, -0x7D49D5,  0x4C1140,
     0x609289,  0x02DA0B,  0x26D847,  0x1B887A,
    -0x40A8B7,  0x2C4717,  0x3FB7F5, -0x043021,
     0x04E923, -0x110FFA,  0x1FA5C1,  0x4BE0FB,
     0x746CF6,  0x61D6EA,  0x3CA9B4, -0x2048A6,
    -0x26111F, -0x0F2139,  0x266296, -0x26ACC3,
    -0x532BC7,  0x38E453,  0x7C1836,  0x250217,
     0x7CA1D0, -0x38A743,  0x716741,  0x226B2D,
     0x24A703,  0x42D5C7,  0x4D082D, -0x172C20,
     0x3F1713,  0x753DE2,  0x7349A8, -0x48D5DC,
     0x66E850, -0x3E3054,  0x769118,  0x0B58AC,
    -0x51D071,  0x70CC57, -0x586459, -0x2DB8C1,
    -0x10B295,  0x730B8D, -0x543FA3,  0x4D34AE,
     0x4E7ED8,  0x001E33, -0x5F1337,  0x10BA12,
    -0x75AE7E, -0x689365,  0x37B3AD, -0x59DA66,
    -0x688690, -0x132758,  0x5E024B,  0x658194,
    -0x0F7B82,  0x35595B, -0x120758, -0x2715D5,
     0x3BEC25,  0x5E2453, -0x2AA499,  0x59A43D,
    -0x56EBF5, -0x5B3353,  0x572FB6,  0x4A68F3,
    -0x5F6127,  0x0FE7DE, -0x3E123C,  0x787E78,
     0x29A2EE,  0x56B1F7,  0x29E135,  0x1E1163,
    -0x5FB6A5, -0x57C92E, -0x48DFBC,  0x10444B,
     0x304998, -0x288954, -0x155B33, -0x7674F0,
    -0x763E55,  0x6D0EB2,  0x6E0D00,  0x22C63F,
     0x6AF2F3,  0x1DE2F8, -0x1887E8,  0x68963E,
     0x5E6563,  0x244758,  0x54018F, -0x618377,
     0x4FE075,  0x072EC5,  0x636283,  0x1B32AD,
     0x51CF6C,  0x3BCF89,  0x5B3580, -0x27378E,
     0x3E7D70,  0x2C59EC,  0x025072, -0x66FC61,
    -0x764116,  0x311DD1,  0x09D01D,  0x417C03,
    -0x1D9456, -0x21404B,  0x7E339A, -0x3602E2,
     0x1B4A6E,  0x3CE79E, -0x3ADB90,  0x5CA4F0,
    -0x312FDE,  0x6FEF85, -0x6EA257,  0x19448C,
     0x4E4B70,  0x311A94,  0x682E80, -0x087842,
     0x5BE52B, -0x403D18,  0x28231E,  0x54556A,
     0x180FF5, -0x57EFD3,  0x0F4FD6, -0x5E0CDA,
    -0x343942, -0x025046, -0x2F4985, -0x4591A1,
    -0x21BE78,  0x6A0489,  0x25533B,  0x61BECD,
    -0x5984FF, -0x4D9B56,  0x674892,  0x593180,
     0x711D63,  0x12CC93, -0x4B5845, -0x4F70DD,

     0x574E23,  0x069BF1,  0x0A6237, -0x5D741F,
     0x51DCEC, -0x0933AD, -0x08251B, -0x521A75,
     0x115269,  0x48314B,  0x438B18,  0x41DD54,
     0x29615C,  0x512F84,  0x255F4D, -0x68A434
},

};

int x_cn[NUM_INPUTS][2*N + 2*PAD];
int x_i[NUM_INPUTS][2*N + 2*PAD];

int y_cn[NUM_INPUTS][2*N + 2*PAD];
int y_i[NUM_INPUTS][2*N + 2*PAD];

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
    int i, j, k, n, m, radix, fail;
    int p, q, diff, diff_max;

    /* -------------------------------------------------------------------- */
    /* Initialize timer for clock */
    TSCL= 0,TSCH=0;
    /*  Compute the overhead of calling _itoll(TSCH, TSCL) twice to get timing info.   */
    /* -------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    t_stop = _itoll(TSCH, TSCL);
    t_overhead = t_stop - t_start;

    for (j = 16, k = 1, fail = 0; j <= N; k++, j *= 2) {
        t_cn = 0;
        t_i = 0;

        for (n = 31, m = 1; (j & (1 << n)) == 0; n--, m++)
            ;
        radix = m & 1 ? 2 : 4;

        /* -------------------------------------------------------------------- */
        /*  Generate twiddle factors for fft of size 'j'                        */
        /* -------------------------------------------------------------------- */
        gen_twiddle_fft16x32(&w[0][PAD], j);

        /* -------------------------------------------------------------------- */
        /*  Copy vector to all inputs.                                          */
        /* -------------------------------------------------------------------- */
        memcpy(x_cn, x, sizeof(x));
        memcpy(x_i, x, sizeof(x));
        memcpy(y_i, y_cn, sizeof(y_i));

        /* -------------------------------------------------------------------- */
        /*  Check the results arrays, and report any failures.                  */
        /* -------------------------------------------------------------------- */
        for(i = 0; i < NUM_INPUTS; i++) {
            t_cn += time_cn(i, j) - t_overhead;
            t_i += time_i(i, j) - t_overhead;
        }

        printf("DSP_fft16x32\tIter#: %d\t", k);

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
 
        if (diff_max > 1) {
            fail++;
            printf("Result Failure ");
        }
        else
            printf("Result Successful ");
     
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
    DSP_fft16x32_cn(&w[cur_input][PAD], n, &x_cn[cur_input][PAD], &y_cn[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  TIME_I  -- Measure elapsed time for intrinsic C version.                */
/* ======================================================================== */
clock_t time_i(int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_fft16x32(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_fft16x32_d.c                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

