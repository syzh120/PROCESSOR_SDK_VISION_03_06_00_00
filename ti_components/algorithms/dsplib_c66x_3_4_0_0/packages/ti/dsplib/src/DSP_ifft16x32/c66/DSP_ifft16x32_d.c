/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_ifft16x32_d.c -- Driver file for DSP_ifft16x32                 */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'DSP_ifft16x32'*/
/*      kernel.  The function prototype appears below.  The driver itself  */
/*      is invoked as a standard C program, and results are reported on    */
/*      stdout.                                                            */
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

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <c6x.h>

#include "DSP_ifft16x32_cn.h"
#include "DSP_ifft16x32.h"
#include "gen_twiddle_ifft16x32.h"

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
#define N (2048)
#define PAD (16)

/* ======================================================================== */
/*  Number of input arguments:                                              */
/* ======================================================================== */
#define NUM_INPUTS (1)
#define NUM_X_INITIALIZERS 544                         /* for N=256, PAD=16 */
extern int gen_twiddle_ifft16x32(short *w, int n);

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
int x[NUM_INPUTS][NUM_X_INITIALIZERS] =
{
/* Input Number: 0 */
{
    -0x4AF2AA,  0x08C3C6, -0x045937,  0x0A3C7B,
     0x253DB9, -0x3422FD, -0x227A08, -0x0B91F8,
    -0x1E9758, -0x55FD39, -0x185DF8, -0x204FEF,
     0x3FD069,  0x5A4759,  0x7221D8,  0x3A4FD7,
     0x300711,  0x04DA22,  0x549CDF, -0x6A0A35,
    -0x255F0E,  0x6DBBD5, -0x00CC4A,  0x365622,
    -0x0F3E19, -0x7586E6, -0x484647,  0x46182B,
     0x560CEF, -0x0893EF,  0x3E8536,  0x2E84B5,
    -0x7A8771, -0x320AAA, -0x6C9A58, -0x6E90CA,
     0x327D7A,  0x683AE3,  0x272E76,  0x6EED14,
    -0x3AD7E5, -0x7A1A98,  0x2773D0, -0x13C054,
     0x059352,  0x516682,  0x3ED409,  0x3F8168,
    -0x66CCE9, -0x29CB84,  0x607A06,  0x3FA0A3,
    -0x3E6AAC,  0x4C8BD5,  0x22283B,  0x1C0BA3,
    -0x231066, -0x28C9A6,  0x0675AF, -0x4559B6,
     0x311D22,  0x20D00E,  0x5EA494,  0x3080EE,
     0x7B7795,  0x5C0698,  0x2A9DE4, -0x123714,
    -0x45F5DB,  0x2E6287,  0x798A94,  0x04814E,
    -0x2F4994, -0x04EEE7, -0x267230,  0x1C8140,
     0x57A8A9,  0x152AD8,  0x4124BB, -0x7FDF6E,
     0x48B8BA,  0x55F6BF,  0x099D53, -0x24C409,
    -0x23DA9B, -0x673FCF,  0x5F3EC5,  0x18E874,
     0x3D3771, -0x646892, -0x368118, -0x1C8989,
     0x713B16, -0x385A0E,  0x23E92E,  0x4E250F,
     0x166822,  0x56713C, -0x51E044,  0x2628EE,
     0x561F83,  0x67B888, -0x6A880F,  0x5F657B,
    -0x54F270,  0x7032F1, -0x7A3CE9,  0x2E6C9F,
    -0x204E5D, -0x66157B, -0x3C4875,  0x4344BF,
    -0x23407E,  0x798DBC,  0x4367FC, -0x529EA0,
    -0x4C17EF, -0x42C50D,  0x51773B, -0x219008,
     0x777ED3,  0x2F562F,  0x305A0A,  0x57526B,
     0x4E81BD, -0x5E1C09,  0x494187,  0x79ECBD,
     0x5581C8,  0x46D175,  0x5A209B, -0x05DE99,
    -0x41111D, -0x1D265B,  0x2959F8,  0x7D9ED5,
    -0x46BF63,  0x6E50D0,  0x438B27, -0x2B1B54,
    -0x5D7CD0, -0x6A80E8,  0x33FB1D,  0x640D13,
    -0x1039AF, -0x63FFB2, -0x30DF19,  0x2BD6D2,
     0x6BE741,  0x2E96CE, -0x04272F, -0x0B937C,
     0x2D40C3, -0x71F73E,  0x78B1B0,  0x25757A,
    -0x2342B5, -0x5581BC,  0x38DAAF, -0x482026,
    -0x4F3801, -0x6724FE, -0x49C7DF, -0x2413AD,
    -0x3C66F3, -0x0C5C3C, -0x2CE718, -0x4FFEEC,
     0x1C71C5, -0x5C30A4, -0x4A000E, -0x49489C,
     0x032705, -0x78C774,  0x33212F,  0x52AB67,
     0x1C9F6C,  0x7EF250,  0x3EF4A5,  0x048E99,
    -0x385F1D,  0x612E1F, -0x2D92F6, -0x450696,
     0x418BE6,  0x5B218D, -0x13B19C, -0x317C74,
     0x0C742F,  0x2266E2,  0x072647,  0x249276,
     0x201715, -0x609EDD, -0x6698E8, -0x0F8C77,
     0x59394A,  0x732AF2,  0x1A22CB, -0x5DD2A1,
    -0x4C24A1, -0x1A8E00,  0x0CDED6,  0x71A1DA,
    -0x3D256D, -0x4E1ABF, -0x71E179,  0x14584C,
    -0x089087,  0x44A2AD, -0x150C81,  0x19A555,
     0x2606DB, -0x2CE918, -0x4BBC45,  0x637CEE,
    -0x31FC81, -0x2310BD, -0x1CDB66,  0x4B8E1E,
    -0x5122E2, -0x717836,  0x79DE7F, -0x11D91E,
     0x182242, -0x6BAF5D,  0x260E7A,  0x1749B5,
    -0x73249A, -0x3D3B97,  0x76657E,  0x4F8E59,
     0x19CADA,  0x2C52F1,  0x088CA3, -0x68B8C4,
    -0x02F0F6,  0x1DD1FC,  0x3FACF9,  0x455A0A,
     0x15B276,  0x7BEE51, -0x01EF9C, -0x7C99FF,
    -0x7A7EE9,  0x0421CE, -0x1093F9, -0x0A5AAE,
     0x2FDE6E, -0x036125, -0x3CB845,  0x08114B,
     0x6EE304, -0x46342D, -0x0001EB,  0x5D489F,
    -0x74936A, -0x6B4C2C, -0x340C89, -0x1D50A1,
    -0x767E5A, -0x3B007E,  0x4B56AB,  0x0B5C1E,
    -0x575F35, -0x6813D4, -0x0BF166, -0x4FC036,
     0x306B58, -0x683D11,  0x6C486F,  0x1505A1,
     0x0535C8,  0x114E32,  0x7124F7, -0x72B714,
     0x7EEA79,  0x7CDC25,  0x3E005F,  0x5074C8,
    -0x0116C8,  0x4F3594, -0x020FE4, -0x170641,
    -0x2AD7EC, -0x4CEA40, -0x4A3BAA, -0x34CF96,
    -0x17B2FD, -0x5D4F70,  0x484162, -0x666E1F,
    -0x66E12E, -0x1E563F, -0x150F33,  0x7E9B3E,
     0x76D3E1,  0x6A1571, -0x57ED9C,  0x3907DF,
     0x32C92F, -0x4C0453,  0x6B36DE,  0x48B8C8,
     0x561B2F,  0x5CD54D,  0x06EB8B, -0x441242,
     0x4992EC, -0x396D1C, -0x37E479,  0x26337E,
     0x0D83FB,  0x0997F5,  0x107E02,  0x4299BD,
     0x4AFEBA, -0x2DB7C5,  0x68B61F, -0x585ACC,
     0x1BF258, -0x5A75C9, -0x597936,  0x37896D,
     0x209D30,  0x09C8D1, -0x6E51D5, -0x5AE33F,
     0x58EDED,  0x0FFD4D, -0x7519DF, -0x5CF313,
     0x3838FC, -0x38C4CC, -0x4385B4,  0x3BDFEC,
    -0x6D2334,  0x1735A5,  0x4F0620, -0x3CDA8B,
    -0x45C3AB,  0x7548A8,  0x23DA8C, -0x008767,
     0x70A079,  0x0885CC, -0x758D5C, -0x1D4AD9,
     0x1171A5, -0x50BE2D, -0x6F6421,  0x78F826,
    -0x71A2B8,  0x6BA0AF,  0x3EB663,  0x70DC10,
    -0x5B2377, -0x505E78,  0x6C94DC, -0x2C85DB,
    -0x22731F,  0x133311, -0x717FA5,  0x56A679,
    -0x2A0611, -0x0E4018,  0x0FE0C8, -0x230ECD,
     0x42421D,  0x61BB46, -0x54049A, -0x6D1398,
     0x442098,  0x1DC1B9,  0x5062D0,  0x382730,
     0x77C910, -0x3465D1,  0x047222,  0x0C7A6B,
     0x4C3BC4,  0x2BD900,  0x51818F, -0x27F85C,
     0x28645E, -0x599297, -0x4AD9E7, -0x558355,
    -0x3C53E2, -0x334925, -0x6CDA34, -0x4FDE9F,
     0x5462C8,  0x2CA2D3,  0x34760F, -0x50E5DA,
    -0x077B0F,  0x143D93,  0x40F67B, -0x4D8C88,
    -0x1491FD, -0x40AEBD,  0x4533BA,  0x4B6843,
    -0x0A1563,  0x5B7D03, -0x4024FC,  0x046E59,
    -0x52E53F,  0x7A5076,  0x264993,  0x758498,
    -0x0731BE,  0x6AE624, -0x7F4743,  0x763B41,
     0x4DAE0C, -0x1077A6, -0x026B02,  0x0305F5,
     0x3DD4B4, -0x1F3C12,  0x0D6CAD,  0x3843E4,
    -0x37C82C,  0x308F76, -0x75FA57,  0x0098A8,
    -0x0F7A4F, -0x281594,  0x590F94, -0x290AB0,
     0x10D4B8,  0x1D7BB3,  0x17FB2E,  0x43ED0C,
     0x79BA44, -0x2F4AE3,  0x4D7122,  0x6BC91B,
    -0x21BAD9, -0x1E05B7, -0x5C1A08,  0x4ADA50,
    -0x0DAF75, -0x27C47D, -0x632980,  0x188DD1,
    -0x214360, -0x3E5902,  0x561F5B,  0x4BC280,
    -0x14F16D, -0x133DF9, -0x3107F6, -0x3F1B6D,
     0x03E54F,  0x209E9F,  0x2B0F00, -0x71C130,
     0x67DA98, -0x5889F7, -0x70BBA8, -0x06ECFB,
     0x303ADE, -0x37A347, -0x187981,  0x09FC1F,
     0x1C2673,  0x23633E,  0x44547B,  0x49FF79,
     0x118F7F,  0x6FC98F,  0x3E5A40,  0x2DEECC,
    -0x0C65B8,  0x23A64A, -0x2D4B7D, -0x6681A7,
     0x39DE43,  0x7F955B,  0x4D4AA5,  0x09AAB4,
    -0x38F788,  0x7BE796, -0x4A24CC, -0x122E36,
    -0x75A357,  0x1ECEBD,  0x40185E, -0x67EB7F,
     0x6398D2, -0x49F193,  0x486E14,  0x5F7699,
    -0x354190,  0x77B27C,  0x48E817,  0x5C412F,
    -0x3DCAF4, -0x02C6B2,  0x5BB8AB,  0x51256A,
    -0x762F57,  0x3BCB7D, -0x3921B0,  0x369FDD,
    -0x6FC59A,  0x40F18F, -0x019002, -0x18E3EA,
     0x3C3C04,  0x7044FC, -0x43007F,  0x7B5ECE,
    -0x199858, -0x655ACC, -0x6E53AF, -0x415BA4,
    -0x5E6094,  0x737905,  0x7D4A7D,  0x4E10B7,
     0x4A074A, -0x03A501,  0x142F2C, -0x1C2C38,
     0x58D0C8,  0x42D72D, -0x64E2EA,  0x349446,
    -0x0D9B10,  0x11A6D3, -0x492761,  0x0A9ADC,
    -0x3689E4,  0x01EA8B,  0x15CDF4, -0x10C414,
     0x3E730D,  0x69E44F, -0x599546,  0x07057D
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
        gen_twiddle_ifft16x32(&w[0][PAD], j);

        /* -------------------------------------------------------------------- */
        /*  Copy vector to all inputs.                                          */
        /* -------------------------------------------------------------------- */
		memset(x_cn, 0, sizeof(x_cn));
		memset(x_i,  0, sizeof(x_i));
        memcpy(x_cn, x, sizeof(x));
        memcpy(x_i,  x, sizeof(x));
        memcpy(y_i, y_cn, sizeof(y_i));

        /* -------------------------------------------------------------------- */
        /*  Check the results arrays, and report any failures.                  */
        /* -------------------------------------------------------------------- */
        for(i = 0; i < NUM_INPUTS; i++) {
            t_cn += time_cn(i, j) - t_overhead;
            t_i += time_i(i, j) - t_overhead;
        }

        printf("DSP_ifft16x32\tIter#: %d\t", k);

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
    DSP_ifft16x32_cn(&w[cur_input][PAD], n, &x_cn[cur_input][PAD], &y_cn[cur_input][PAD]);
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
    DSP_ifft16x32(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_ifft16x32_d.c                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

