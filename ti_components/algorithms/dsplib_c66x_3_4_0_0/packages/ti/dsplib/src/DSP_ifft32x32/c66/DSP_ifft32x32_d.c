/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_ifft32x32 -- Driver file for DSP_ifft32x32                     */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'ifft32x32'    */
/*      kernel.  The function prototype appears below.  The driver itself  */
/*      is invoked as a standard C program, and results are reported on    */
/*      stdout.                                                            */
/*                                                                         */
/*      Building this with the "COMM_FLOW" and "RAND_DATA" macros set      */
/*      will build a driver which generates and tests with random data     */
/*      sets.  Otherwise, the driver will use a fixed test vector.         */
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

#include "DSP_ifft32x32_cn.h"
#include "DSP_ifft32x32.h"
#include "gen_twiddle_ifft32x32.h"

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
#pragma DATA_ALIGN(x_c, 8);
#pragma DATA_ALIGN(x_i, 8);

#pragma DATA_ALIGN(y_c, 8);
#pragma DATA_ALIGN(y_i, 8);

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
#define N   (256)
#define PAD (16)

/* ======================================================================== */
/*  Number of input arguements:            .                                */
/* ======================================================================== */
#define NUM_INPUTS (1)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
int x[NUM_INPUTS][2*N + 2*PAD] =
{
/* Input Number: 0 */

{
    -0x56BBF3, -0x33FFB3,  0x35C4A1,  0x0E60EF,
    -0x2BC60C,  0x2CC37D, -0x4C548E, -0x75D3BE,
     0x55BC2D, -0x128FFC, -0x447F1F,  0x0E274E,
     0x48CD25, -0x205E45, -0x67D2A6,  0x4D2953,

    -0x483222, -0x6AE991,  0x5E24A8,  0x6B798B,
     0x2F2E67, -0x6F8DF7,  0x106B90, -0x6D8B32,
     0x1C0531, -0x2C07CC, -0x2F329A,  0x1E7DCF,
     0x68F49C,  0x53C4E5, -0x6E57BF, -0x035860,
    -0x1BFFA6, -0x28F7A0, -0x2E1ECE, -0x5D5D41,
    -0x113EDE, -0x4B32F0, -0x2F89F4,  0x346F74,
    -0x1C8BD4, -0x0A4D17, -0x23D2CA,  0x4B46C4,
    -0x2B9004,  0x612A9F,  0x0EF10A, -0x20AC66,
    -0x018609, -0x12439F,  0x1C4049, -0x226466,
    -0x7582B6,  0x0FCB62, -0x57BAF1, -0x2845D9,
     0x0E2197,  0x7555F4, -0x6AF226,  0x66CE0E,
     0x59BFF8, -0x5ACB8F, -0x1A9BDC, -0x5DCE97,
    -0x03C13A, -0x029360, -0x6836FE,  0x516C18,
     0x214CB0, -0x6015F9,  0x090B50,  0x28F18A,
     0x2076A6, -0x46B358,  0x6A05F3, -0x3EF3ED,
     0x5BA907, -0x46D25D, -0x5F0566, -0x545A82,
    -0x1C7361, -0x1A94A9,  0x421294,  0x26324E,
     0x583EF3, -0x2B0FA6,  0x0E793E,  0x007325,
    -0x630B9D,  0x5083F2,  0x6A9D62,  0x1673DB,
    -0x410382,  0x1D0D71,  0x621040,  0x023DBE,
    -0x4E63B9,  0x21EBF9, -0x4A746F,  0x62E18C,
     0x4854AC,  0x76BB3B,  0x5F8A1F,  0x4E2D87,
    -0x0B002A, -0x22D568,  0x2D196D,  0x6EAF47,
    -0x37A342,  0x1B452D, -0x2DCF20,  0x3777AC,
     0x436E99, -0x4D32A0,  0x043DFF, -0x35EA78,
     0x624590, -0x73FDC6,  0x1C4944, -0x019E93,
     0x6BA336, -0x0381B7, -0x41BF16,  0x08782D,
     0x0F065D, -0x4D7999,  0x03D856,  0x4C8989,
     0x408EB1,  0x0A5EE4, -0x586373, -0x2D2E7C,
     0x5949A0,  0x4720AE, -0x3D67D9, -0x1C9416,
     0x02600B,  0x2B94D7,  0x7D2164,  0x445288,
     0x5E9C4F,  0x7E8812,  0x5741C6, -0x62D579,
    -0x0322F2, -0x0FD66A,  0x6448AF, -0x7FB387,
     0x0CDE4A, -0x17220B,  0x16FB95, -0x636F6C,
     0x5EEA58, -0x4AE3A7,  0x0EDE49, -0x76A867,
    -0x5F13F5, -0x602C4B,  0x7029B8, -0x39A519,
     0x635ABA,  0x68BA5A,  0x34D8D1,  0x55B73C,
     0x689196, -0x57CC7A,  0x0C5DE0,  0x7CBEA4,
    -0x520341, -0x6CD0B2,  0x3D7509,  0x2C0212,
    -0x3D4B4F, -0x5F7777,  0x0F9C47, -0x71D3D8,
    -0x1B1582, -0x619BE7,  0x319F78,  0x3607AA,
     0x58C64B, -0x5FE5D9, -0x502608,  0x765A28,
    -0x6BE753,  0x5C10CC, -0x197AB7,  0x5AF442,
    -0x5C8EC7,  0x6425A8,  0x00B746, -0x3378D4,
     0x521EF5, -0x33EF20,  0x747A6B,  0x52BBCC,
    -0x597CE7, -0x4DB3F0,  0x07849A,  0x000522,
     0x134F81,  0x27FBA6, -0x21E903,  0x02BC39,
    -0x0BDF6D,  0x055231,  0x057769,  0x50F85E,
    -0x2D0233,  0x22FD0E,  0x0791DE,  0x0EA500,
    -0x17CE42,  0x700F11,  0x07317C,  0x0064B4,
     0x6C0EB6,  0x78E894, -0x239A61, -0x4A5F12,
     0x270DD5, -0x39598B, -0x488591, -0x328F1C,
    -0x3E352A, -0x507181, -0x37DA69, -0x194DDD,
     0x626C2F,  0x04FDC0,  0x6B3E6F, -0x5214B9,
     0x10E406,  0x235657,  0x5FA64C, -0x679997,
     0x519364, -0x0B8EEB,  0x74CC44, -0x41EB4A,
    -0x6531C2,  0x4810A6,  0x505314,  0x5FB1B3,
    -0x093B38,  0x19CD9D, -0x54A877, -0x7E5E4D,
    -0x7FB968,  0x3610E7, -0x692C0C,  0x4519EE,
     0x18EC14, -0x2E7ECB,  0x44AD31,  0x5002D4,
    -0x1DDE52,  0x6F80C7, -0x1F1F43, -0x1BE3FD,
     0x068D63, -0x3EE7C8, -0x24BFB5,  0x17EA69,
     0x3C5D20, -0x1B0766,  0x4A6C77, -0x492BDD,
    -0x6A0DA8,  0x7BED9E, -0x3CA602,  0x49156A,
     0x0C6D73,  0x3E5614,  0x43FDFD, -0x491FAC,
     0x5E9C92,  0x61235A, -0x686032,  0x184E9A,
    -0x5835ED,  0x67CF46, -0x3AB723,  0x2D8833,
     0x40EE63, -0x2B2515,  0x06D11A, -0x104A08,
     0x64BCAC,  0x4D4BD5, -0x44EB87, -0x2DDAF7,
     0x1C1BBB, -0x6B58C9, -0x173C1A,  0x24445D,
    -0x0F8F3F, -0x11078D, -0x46AA94,  0x1AC601,
    -0x28A7A5,  0x6C48A6, -0x785F34, -0x0B668B,
    -0x0AC292, -0x64DD6A, -0x1A73D6, -0x29E938,
    -0x68B8BB,  0x169A81,  0x31674C, -0x480927,
    -0x07C578, -0x7EB788,  0x2963DE,  0x058443,
     0x45A771,  0x65D380,  0x08A849,  0x5A9080,
     0x730AE5,  0x737247, -0x5C6E6E, -0x125759,
     0x4A40BD, -0x540B57,  0x1083C8,  0x130C69,
     0x3DE6F5, -0x143855,  0x51EF85,  0x74E8B5,
    -0x72ECE4,  0x5F8169, -0x7F180D,  0x5C4B82,
     0x21F48C,  0x58676E,  0x05DFDA, -0x4A9DB0,
    -0x4935FB,  0x0879F0,  0x4E0D55,  0x2770CF,
    -0x3C340A, -0x5E8378, -0x701990, -0x27F1C5,
    -0x539ED2,  0x5E88C5,  0x013D69,  0x5724D7,
    -0x45B6B8, -0x136CBA,  0x308902,  0x282829,
     0x521970, -0x467D5E, -0x3F3BB3,  0x771C4D,
    -0x09600E, -0x55CC2C,  0x476F92,  0x6DD207,
    -0x7658F7, -0x4DEA74, -0x60C739, -0x4F1B08,
     0x599E90, -0x294E16,  0x44BE00, -0x7D017E,
     0x6D9BF8,  0x0DC22D,  0x32F589,  0x04DED9,
    -0x66BB01, -0x78B834, -0x2E490D,  0x2995CB,
    -0x29E83D, -0x20EB8D,  0x59DBB6, -0x3F7061,
     0x5F91A1, -0x539481,  0x4794F0,  0x2AD7B1,
     0x16B959, -0x07EDA5,  0x504998,  0x362040,
    -0x5772FD,  0x1D6646,  0x5AADCB, -0x5EF728,
    -0x0436B2, -0x7805E8, -0x009C55, -0x49D80D,
     0x609A98, -0x25D6A6,  0x0CD039, -0x63ABB6,
     0x0AA743,  0x013565, -0x747828, -0x3E4FB4,
     0x4604DE, -0x659F1F, -0x2A2246, -0x0F0CBC,
     0x007C9F,  0x4D8C25,  0x2013FB, -0x7A8452,
     0x06CBA1, -0x742ED7,  0x1AACB4,  0x4F9337,
    -0x6BD984,  0x26A133,  0x055EA3, -0x707511,
    -0x60496A,  0x5EE822, -0x26D922, -0x5E03E5,
     0x7166D7, -0x3A5A7F, -0x1505ED, -0x3719BB,
    -0x0462DE, -0x716BE7, -0x685C2A, -0x630912,
     0x7A4F09, -0x39B491,  0x762F7D, -0x595F93,
    -0x2A068B, -0x1AA157, -0x6F74F7, -0x678F7D,
     0x47F56E,  0x520266,  0x18BB92, -0x54E1ED,
    -0x2E4B29,  0x44B7FF,  0x2A33D3, -0x561874,
    -0x1AA5A4, -0x78964A,  0x14D133,  0x149E7E,
    -0x1CCAC6, -0x5366B1, -0x61051D, -0x0AF41F,
    -0x2B62AD,  0x1907A0, -0x29AA81, -0x2A0384,
    -0x1552F6, -0x7DA97A, -0x14552E,  0x4EA408,
     0x47676F,  0x413EC2,  0x7D5D09, -0x2F4881,
    -0x7355C2,  0x1AB050,  0x051210,  0x03BE04,
    -0x5A64E5, -0x21795D, -0x52139B,  0x4D3C15,
     0x5EE0AC,  0x7B2F49,  0x43EB03, -0x00F7A9,
     0x4444FB, -0x1C2070, -0x620C21, -0x539673,
     0x3B3A9A,  0x69BB79,  0x11EE61,  0x1A7D4D,
     0x6DC127, -0x097447,  0x688F81,  0x6352D6,
    -0x17D673, -0x5594F4, -0x24C526, -0x4CB371,
    -0x67C869,  0x5D0084, -0x6779A8,  0x3248B9,
    -0x0ECFA9, -0x725CB7,  0x40EAF1, -0x760127,
    -0x11C331,  0x26212D, -0x04FB14, -0x66DBCB,
    -0x364B8F, -0x499A2E, -0x7F02D7, -0x3227EA,
     0x04C7DD, -0x774A66, -0x5062F8, -0x6B3AD4,
     0x2A0885,  0x1EE718,  0x296D54, -0x7F7760,
    -0x20A37E, -0x6DE48E,  0x7089BA, -0x7422AE,

    -0x4D3FB9,  0x606F17,  0x0A8D4B,  0x0305C8,
     0x317EA0,  0x0D4180,  0x2A2295, -0x6E0BB4,
    -0x3AC786,  0x3C624A,  0x60AEBC, -0x0A4558,
    -0x29A40B, -0x5C24BB, -0x365BD1, -0x294FDD
},

};

int x_c[NUM_INPUTS][2*N + 2*PAD];
int x_i[NUM_INPUTS][2*N + 2*PAD];

int y_c[NUM_INPUTS][2*N + 2*PAD];
int y_i[NUM_INPUTS][2*N + 2*PAD];

int w[NUM_INPUTS][2*N + 2*PAD];

/* ======================================================================== */
/*  Prototypes for timing functions.                                        */
/* ======================================================================== */
clock_t time_c(int cur_input, int n);
clock_t time_i(int cur_input, int n);

/* ======================================================================== */
/*  MAIN -- Top level driver for the test.                                  */
/* ======================================================================== */
int main()
{   
    clock_t t_overhead, t_start, t_stop;
    clock_t t_c, t_i;
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
        for (n = 31, m = 1; (j & (1 << n)) == 0; n--, m++)
            ;
        radix = m & 1 ? 2 : 4;

        /* -------------------------------------------------------------------- */
        /* Generate twiddle factors                                             */
        /* -------------------------------------------------------------------- */
        gen_twiddle_ifft32x32(&w[0][PAD], j, 2147483647.5);

        /* -------------------------------------------------------------------- */
        /*  Copy vector to all inputs.                                          */
        /* -------------------------------------------------------------------- */
        memcpy(x_c, x, sizeof(x_c));
        memcpy(x_i, x, sizeof(x_i));

        /* -------------------------------------------------------------------- */
        /*  Force uninitialized arrays to fixed values.                         */
        /* -------------------------------------------------------------------- */
        memset(y_c, 0xA5, sizeof(y_c));
        memset(y_i, 0xA5, sizeof(y_i));

        /* -------------------------------------------------------------------- */
        /*  Check the results arrays, and report any failures.                  */
        /* -------------------------------------------------------------------- */
        for(i = 0; i < NUM_INPUTS; i++) {
            t_c = time_c(i, j) - t_overhead;
            t_i = time_i(i, j) - t_overhead;
        }

        printf("DSP_ifft32x32\tIter#: %d\t", k);

        diff_max = 0;
        for (p = 0; p < NUM_INPUTS; p++) {
            for (q = 0; q < 2*N + 2*PAD; q++) {
                diff = y_c[p][q] - y_i[p][q];
                if (diff < 0)
                    diff = -diff;
                if (diff > diff_max)
                    diff_max = diff;
            } 
        }
 
        if (diff_max > 8) {
            fail++;
            printf("Result Failure ");
        }
        else
            printf("Result Successful ");

        printf("\tRadix = %d\tN = %d\tnatC: %d\tintC: %d\n", radix, j, t_c, t_i);

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
/*  TIME_C   -- Measure elapsed time for natural C version.                 */
/* ======================================================================== */
clock_t time_c (int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_ifft32x32_cn(&w[cur_input][PAD], n, &x_c[cur_input][PAD], &y_c[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  TIME_I   -- Measure elapsed time for optimized C (with intrinsics)      */
/*              version.                                                    */
/* ======================================================================== */
clock_t time_i(int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_ifft32x32(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_ifft32x32_d.c                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

