/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fft32x32_d -- Driver file for fft32x32                         */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'DSP_fft32x32' */
/*      kernel.  The function prototype appears below.  The driver itself  */
/*      is invoked as a standard C program, and results are reported on    */
/*      stdout. The driver will use a fixed test vector.                   */
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

#include "DSP_fft32x32_cn.h"
#include "DSP_fft32x32.h"
#include "gen_twiddle_fft32x32.h"

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
int x[NUM_INPUTS][2*N + 2*PAD] =
{
/* Input Number: 0 */

{
     0x61DEED,  0x4AC29E, -0x528F5F,  0x690868,
    -0x026C32,  0x54F60D, -0x07E3E2, -0x703E12,
     0x4324F5,  0x63DEBE,  0x2867F5, -0x0A8DB1,
    -0x09EF49,  0x06C94C,  0x5E2C28,  0x3C1A33,

     0x261855, -0x0FED61, -0x195389, -0x26F759,
    -0x390F73,  0x1FD21A,  0x599EF8, -0x5E7D57,
     0x0AC9CB,  0x75A347, -0x2FA449,  0x01B17F,
     0x0348D8,  0x26D95A, -0x6B4D22,  0x555022,
     0x075129, -0x673FD0, -0x24270B, -0x1F669C,
     0x5C3A9C,  0x1E5731, -0x03075F, -0x080ECC,
    -0x591F12,  0x2214AF, -0x451380, -0x3F235C,
    -0x63E37B,  0x2B231E,  0x068B7F,  0x23A90C,
    -0x7CEEF3,  0x4BA3C2, -0x33DAAA,  0x5A69DF,
    -0x1613A9,  0x786E52,  0x459472, -0x576153,
     0x2B7109,  0x3ED8F9,  0x4C7609, -0x4CD232,
     0x40FCA3,  0x62F74D,  0x3804A9,  0x031946,
     0x3F5140, -0x1E1C4A, -0x40F123,  0x2B7247,
     0x39DFB8, -0x247C4D,  0x579452,  0x1112EB,
    -0x332B81, -0x21B45D, -0x5A7FDA, -0x23726F,
     0x029CD5,  0x169064,  0x650498,  0x0BF372,
    -0x0DC232, -0x183A8E,  0x6619F1,  0x2CC0DF,
    -0x5CE96C,  0x684EDF, -0x036520, -0x44615A,
    -0x428378,  0x4148CF, -0x7B7B1C, -0x59A1D7,
     0x76BEA1,  0x75D6CE,  0x60DB51, -0x0C4B59,
     0x48FFA7, -0x779462,  0x08A455,  0x113826,
    -0x117F52, -0x6A6316, -0x73706D,  0x451E9A,
     0x1DBC5E, -0x451091,  0x32B6BB, -0x37C25C,
    -0x6D0D65,  0x7A2A0A, -0x7EFF34, -0x04336D,
    -0x2E7A23,  0x78A33C,  0x68AB41,  0x506403,
     0x3CC4EE,  0x1A148B, -0x288F18,  0x4CC3B5,
    -0x1C6E96, -0x6A919B,  0x67CBB0,  0x32D009,
    -0x639679, -0x2AD126, -0x761EE9, -0x299F55,
    -0x1FB24B, -0x295123, -0x4F7070,  0x0E39E7,
    -0x0EF57A, -0x26FDAB,  0x0A0E8B,  0x52DC3D,
    -0x41969E,  0x00C9B1,  0x37C381, -0x0A727D,
     0x10B387, -0x2E779E, -0x72557C, -0x71E8B2,
     0x7C27DF,  0x1A05BB,  0x55E1E8,  0x00DCFD,
    -0x643EED, -0x3DE334, -0x652281, -0x5A640B,
     0x02EA76, -0x095F65, -0x0B4D37,  0x267D81,
    -0x7971BB,  0x3DB256, -0x24F835,  0x71E2EF,
     0x41039A, -0x07DC11,  0x0128E5,  0x567149,
    -0x289B34, -0x41B064,  0x2CB83C,  0x4AE048,
    -0x704183,  0x20FBD1,  0x1A8328, -0x33F416,
    -0x6057F0,  0x57BC22, -0x180BC8, -0x0A3CC1,
     0x4BB4D9,  0x4D4E8D,  0x7BA93C, -0x582527,
     0x4049A8, -0x697F46,  0x79ABE8, -0x1D018D,
    -0x46A8EF, -0x39EF64,  0x34C673, -0x3C37C7,
    -0x1791F2, -0x51EBF0,  0x2D7ECD, -0x5E6EB4,
     0x21BD6E,  0x015CD7, -0x6FD21B, -0x2E771D,
     0x506588, -0x23A573,  0x3CBA71, -0x69775A,
     0x30B6C2, -0x51F704, -0x368B2E, -0x56CB52,
    -0x3D309D,  0x0F536C,  0x1C9370, -0x0A364A,
    -0x6AECD0, -0x0981A5, -0x082FBE, -0x17C308,
     0x4D115A, -0x2DEBE9,  0x13A8BA, -0x07ECCB,
    -0x19C6C4,  0x0BCDD8,  0x3FB8E9, -0x3D7B90,
     0x4E0353,  0x6DFFB8,  0x01BF0E,  0x544DCB,
    -0x4914DD, -0x15F9DF,  0x40C047,  0x1BD220,
     0x2BD945,  0x52371C,  0x70C3C4, -0x0CFD47,
    -0x04A299,  0x63CD24, -0x3A46F6, -0x1F9147,
     0x535871, -0x3CA738, -0x18FF3A, -0x16CE45,
    -0x52815D,  0x6131D0, -0x4CF356, -0x64F4EE,
     0x7D3FD0, -0x4895B2,  0x77A7D5, -0x51B4C5,
    -0x5C7667,  0x73C308,  0x3A5E50,  0x4EEEFB,
     0x26F7C4,  0x041CEC, -0x7779F2, -0x6E7D4D,
    -0x4E2C77, -0x701323,  0x4167F9, -0x78AEB8,
     0x53830A, -0x3BC996, -0x12F65F,  0x75445A,
     0x0BD6BA,  0x1D8207,  0x1719D1, -0x48F2F2,
    -0x6F5412, -0x01ADDD,  0x2E7BDD, -0x3DF2F2,
    -0x1B7BAB,  0x3D9FA4,  0x65F5D7, -0x327FC7,
     0x2B6EB2, -0x722E93,  0x1D7F6C, -0x5D9A87,
     0x48D36B,  0x4EB92A,  0x57B0BF,  0x0BAE4C,
    -0x4654AE,  0x44102E, -0x5F2E29,  0x73297B,
     0x428B52, -0x4C0B5C,  0x100D14,  0x1BB074,
    -0x2DE8A0,  0x5CE3B5, -0x3CBAC0, -0x7CEC24,
     0x36552F, -0x1D42D8,  0x5A0095,  0x6B51C7,
     0x0F6243,  0x1545D1,  0x06046B,  0x057E25,
    -0x79F839, -0x5F616C, -0x6EF823, -0x3F042C,
     0x4FADA8, -0x61ADD3, -0x10F5FE,  0x466ADB,
     0x6A3692, -0x6DAD79, -0x2A33C4,  0x0FDC66,
     0x2E3429,  0x427DE7, -0x2B1AF7,  0x29CAD9,
     0x140211, -0x00DE69,  0x7900E0, -0x69B766,
    -0x33C1B5, -0x37F992, -0x0E4B55, -0x24FFFB,
     0x102455, -0x268F31, -0x4C81CD,  0x2F6515,
    -0x38B45B,  0x1DAE92, -0x4E9DC8, -0x3351CF,
    -0x1FC126,  0x049D60, -0x765B86, -0x14F15E,
     0x7C8056,  0x3EB3EC,  0x402864, -0x1C4DB9,
    -0x249970, -0x23F057,  0x01F4B9, -0x170618,
    -0x76A546,  0x59FF66,  0x5D4BCE, -0x068B4A,
     0x53F834,  0x00925D, -0x6C0C29,  0x691F81,
    -0x7A68AE,  0x3CA322,  0x6217B9, -0x6F98EA,
    -0x165C22,  0x53EA0D, -0x2AB90A,  0x296341,
     0x0968FB, -0x097475, -0x63E0EC, -0x372AED,
     0x38B5CC,  0x49AAD8,  0x6B0F1E, -0x048D48,
    -0x19209D, -0x3E874E, -0x2B414A, -0x69206A,
    -0x53537D,  0x6D4B66,  0x358F1C, -0x680BFE,
    -0x556650,  0x2830E5,  0x1FCFE5,  0x3EC530,
    -0x5CFBF4,  0x278125, -0x3B0161, -0x451831,
     0x5FB378,  0x71FB8E, -0x0F4BEB,  0x0A72C3,
    -0x2FBC6A, -0x3E2C42,  0x01B299,  0x774DA9,
    -0x790D09,  0x415344,  0x668BE3,  0x3D3868,
    -0x29B4C1, -0x4B9134,  0x2374EB, -0x2DEF7B,
     0x5A3672, -0x7B20D7, -0x254E9C,  0x51E09A,
     0x28E427,  0x2C3FDC, -0x26D9C8, -0x6BD87E,
     0x5124F7, -0x6A587D, -0x517C68,  0x67E9A2,
     0x2B8EC3, -0x32B859, -0x4163F1,  0x68FCF8,
    -0x29E6BA, -0x59746D,  0x615531,  0x05153D,
    -0x6E7394, -0x41CC81,  0x05BC49,  0x2A17C5,
     0x4A5302,  0x66F9B1, -0x284766,  0x072785,
    -0x04CBD2, -0x0FD0EB,  0x6ADFAD, -0x790333,
     0x476529, -0x181C58, -0x110FD2, -0x220EE1,
    -0x257F21, -0x5CFF91,  0x6068CD, -0x34A637,
     0x1ADFBD, -0x360ABC,  0x4ABBBE, -0x056965,
    -0x752A94,  0x2E581C, -0x7F53D2,  0x026A50,
    -0x7ABD44, -0x62F2C8,  0x674956, -0x6BEDD7,
    -0x4CE792,  0x076DB6,  0x3C079D,  0x499B22,
    -0x3FD4B6, -0x6E11D1, -0x1A82C7, -0x6A0189,
    -0x170609,  0x0CCF94, -0x38BD1D,  0x6575AB,
    -0x4B3ED5,  0x513B29,  0x1A6A20, -0x2A661D,
    -0x757B5C,  0x037EC5,  0x4C2990, -0x62412E,
     0x7C656C,  0x34A917, -0x1FEE3B, -0x6EF11F,
    -0x1F150F,  0x6D424C,  0x587330, -0x2E1A01,
     0x269F5C, -0x5E8A54, -0x5B9D66,  0x1FF69F,
     0x7D96C8, -0x7EC06A, -0x72275E, -0x2F5B99,
    -0x4EB149, -0x4AE085, -0x4A882F, -0x13D904,
    -0x258AAA,  0x7CCB33, -0x728C48, -0x10176C,
     0x4A1318,  0x2D5C51, -0x29EC66, -0x515260,
     0x3B8913,  0x2487D5,  0x2C5F1F, -0x1D0AD3,
    -0x30FD51, -0x74B22E,  0x0A63A2, -0x24DF8F,
    -0x374AE1, -0x6E4C7E, -0x1F6684, -0x2E2DFF,
    -0x716ED4,  0x7EF645, -0x5A0820,  0x631D38,
    -0x0D3537,  0x33C50F,  0x6F17CC, -0x4D18B1,
     0x3FC3F4, -0x750A41, -0x67FA7D, -0x58EB70,

     0x0BD967,  0x1B3EE0, -0x22D3F5, -0x2212B0,
     0x4B9794, -0x138A95,  0x07E644, -0x52B3FD,
     0x30BE69,  0x7FC4D5, -0x63D9F4, -0x19F6FE,
     0x46BA6D, -0x3796D0,  0x11D2E0, -0x62D880
},

};

int x_cn[NUM_INPUTS][2*N + 2*PAD];
int x_i[NUM_INPUTS][2*N + 2*PAD];

int y_cn[NUM_INPUTS][2*N + 2*PAD];
int y_i[NUM_INPUTS][2*N + 2*PAD];

int w[NUM_INPUTS][2*N + 2*PAD];

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
    int i, j, k, m, n, radix, fail;
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
        /* Generate twiddle factors                                             */
        /* -------------------------------------------------------------------- */
        gen_twiddle_fft32x32(&w[0][PAD], j, 2147483647.5);

        /* -------------------------------------------------------------------- */
        /*  Copy vector to all inputs.                                          */
        /* -------------------------------------------------------------------- */
        memcpy(x_cn, x, sizeof(x_cn));
        memcpy(x_i, x, sizeof(x_i));

        /* -------------------------------------------------------------------- */
        /*  Force uninitialized arrays to fixed values.                         */
        /* -------------------------------------------------------------------- */
        memset(y_cn, 0xA5, sizeof(y_cn));
        memset(y_i, 0xA5, sizeof(y_i));

        printf("DSP_fft32x32\tIter#: %d\t", k);

        /* -------------------------------------------------------------------- */
        /*  Check the results arrays, and report any failures.                  */
        /* -------------------------------------------------------------------- */
        for(i = 0; i < NUM_INPUTS; i++) {
            t_cn += time_cn(i, j) - t_overhead;
            t_i += time_i(i, j) - t_overhead;
        }

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
 
        if (diff_max > 8) {
            fail++;
            printf("Result Failure ");
        }
        else
            printf("Result Successful ");

        printf("\tRadix=%d\tN=%d\tnatC: %d\tintC: %d\n", radix, j, t_cn, t_i);

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
    DSP_fft32x32_cn(&w[cur_input][PAD], n, &x_cn[cur_input][PAD], &y_cn[cur_input][PAD]);
    t_stop  = _itoll(TSCH, TSCL);
    return  t_stop - t_start;
}

/* ======================================================================== */
/*  TIME_I   -- Measure elapsed time for intrinsic C version.               */
/* ======================================================================== */
clock_t time_i(int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_fft32x32(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop  = _itoll(TSCH, TSCL);
    return  t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_fft32x32_d.c                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

