/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_ifft16x16_imre -- Driver file for ifft16x16                    */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'ifft16x16     */
/*      _imre' kernel.  The function prototype appears below.  The driver  */
/*      itself is invoked as a standard C program, and results are         */
/*      reported on stdout.                                                */
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

#include "DSP_ifft16x16_imre_cn.h"
#include "DSP_ifft16x16_imre.h"
#include "gen_twiddle_ifft16x16_imre.h"

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
     0x4DF4,  0x69AD,  0x2C4F, -0x1CA9,  0x7883,  0x73E9, -0x4491, -0x34C9,
     0x262A,  0x2EE7,  0x76A5, -0x3FDA, -0x654B, -0x72A5,  0x48C4,  0x0D2C,

    -0x0A7C,  0x364E, -0x2CAE,  0x64F2, -0x35CA, -0x5123, -0x6665,  0x6867,
     0x7D3C, -0x160C,  0x2BDE, -0x1F52, -0x1F38, -0x3F79, -0x24E0,  0x14CC,
    -0x6866, -0x332C,  0x751A, -0x396D, -0x35C8,  0x261C,  0x7ACF,  0x5254,
    -0x7303, -0x7498,  0x653D,  0x7FCA, -0x6974,  0x65C2,  0x6EB2,  0x5FD1,
    -0x45D7,  0x3C7E,  0x5B42, -0x17B0, -0x5693,  0x0AF6, -0x3423, -0x550C,
     0x70DB, -0x11AF, -0x6C79,  0x261D,  0x43DB, -0x2E3B, -0x6ED1,  0x5196,
     0x0D90,  0x66DD, -0x6D56, -0x4577,  0x3C16,  0x0F40, -0x48B2, -0x2CC6,
     0x6199,  0x2F75, -0x2556, -0x2009,  0x04D1,  0x5732, -0x7C19,  0x09D7,
     0x4C64, -0x2165, -0x2ABE,  0x1CB3, -0x1E63,  0x5F18,  0x0F2C,  0x5FDD,
    -0x63F0, -0x68EA,  0x0489,  0x1D21,  0x7197,  0x2D58,  0x2091,  0x477B,
     0x2D36, -0x26BA,  0x72D0, -0x36E4,  0x6859,  0x78B4,  0x33CB, -0x0ADD,
     0x49FB, -0x7F44,  0x60BF, -0x615F, -0x73D9,  0x5603, -0x36F3,  0x5456,
     0x475D,  0x1111,  0x35B7,  0x42B4, -0x05A5,  0x1B24, -0x0475,  0x3AA4,
     0x66C0,  0x3EFD, -0x5096,  0x5D86, -0x5EE9, -0x76C7,  0x4632, -0x1708,
    -0x0A42, -0x5159,  0x4FC1, -0x4F26,  0x0431,  0x311A, -0x6257, -0x47E9,
    -0x54CB,  0x0744,  0x0BF3,  0x6FAC,  0x3562,  0x1B0C, -0x4A70,  0x186F,
     0x4793,  0x30E7,  0x3DE7, -0x2DE6,  0x1AB2, -0x4F4A, -0x6901, -0x3BEA,
     0x7367, -0x2265, -0x2F2E, -0x0C7A, -0x18D5, -0x1DA5,  0x6B3F,  0x3914,
    -0x1FCF,  0x53B6, -0x4EE9, -0x1E01, -0x1C3E, -0x73B5, -0x6E30,  0x6DE9,
    -0x5997,  0x7372, -0x7FA2, -0x071A,  0x618A,  0x229E, -0x1B5F, -0x37AF,
    -0x1A2A, -0x043F,  0x7CFD,  0x7AD6,  0x021F, -0x6AD8,  0x5191,  0x5B4C,
    -0x5EEC,  0x1665, -0x4D72,  0x63C5,  0x3554,  0x76AE, -0x5AD3,  0x5565,
    -0x1B96,  0x1B45,  0x70CE, -0x7B8C, -0x07DB,  0x645F, -0x6752, -0x41C8,
     0x1BD3, -0x67FA, -0x0E3E, -0x27F5, -0x2E21, -0x4F77,  0x2536,  0x6935,
    -0x47B3, -0x6623,  0x4E0B,  0x1B05,  0x1296,  0x458F,  0x0E52,  0x31AB,
     0x0F69,  0x31A8, -0x5373, -0x5CAB,  0x5ACC, -0x33E1, -0x494D,  0x6D0B,
     0x761A,  0x3D42, -0x53B6,  0x76CD,  0x5065,  0x18A9,  0x2A31, -0x5890,
    -0x5B42,  0x6F1F,  0x1B7F, -0x5F3F, -0x5D2F, -0x32EA,  0x7008, -0x6A9C,
     0x5272, -0x6BE7, -0x22FD, -0x310D,  0x487D,  0x42BC,  0x1952,  0x4FE6,
     0x169F,  0x198F,  0x24E7,  0x22B3,  0x037E, -0x516A,  0x11CC, -0x394D,
    -0x773C, -0x2749, -0x27AF,  0x494A,  0x1685, -0x7347, -0x5630,  0x7DC9,
    -0x6374,  0x1834,  0x499E, -0x2663,  0x4F07,  0x450C, -0x126C,  0x7E2F,
     0x4414, -0x2413,  0x20BE, -0x20EA,  0x3EAF,  0x133E,  0x2DA9, -0x6D05,
     0x4F80,  0x6023, -0x742D, -0x4038, -0x48F5,  0x2CF8, -0x2D47, -0x446A,
    -0x763D, -0x1135, -0x50F4,  0x45D7, -0x6B86,  0x295B,  0x6883, -0x18B8,
     0x17B4, -0x28E4,  0x55CB, -0x01E3, -0x4EA5, -0x5451, -0x0EE2, -0x1709,
     0x1B56, -0x3A93, -0x2407, -0x2EEF,  0x2A7C,  0x435E,  0x7273, -0x51CD,
    -0x7094,  0x3D47,  0x62AF, -0x2A15, -0x203A, -0x63D9, -0x3B03, -0x4286,
     0x6642,  0x66BF,  0x3E0B,  0x660F,  0x302C, -0x2169, -0x5B39, -0x1D44,
    -0x1442,  0x1408, -0x5AAC, -0x7D51, -0x0325,  0x57BE, -0x0356,  0x2E27,
     0x63AF,  0x0C49, -0x60AB,  0x5AB2, -0x1D59,  0x6523,  0x7CCE,  0x2A27,
    -0x18A8, -0x7545,  0x34FE,  0x2EDD, -0x4048, -0x6800,  0x6161,  0x50B0,
    -0x78BD,  0x0FF4, -0x24BF,  0x5F36,  0x6D7A,  0x1EB2, -0x7662, -0x3D3D,
    -0x57B6,  0x5F86,  0x2C2E, -0x3256, -0x3B35,  0x6774, -0x40FB,  0x4037,
    -0x5B17, -0x302F, -0x34AA,  0x68F6, -0x2797,  0x0E50,  0x4EDE,  0x63B8,
    -0x5734, -0x35E6, -0x639A,  0x0DCE,  0x779F,  0x005D, -0x320F,  0x0F16,
    -0x2A65, -0x651C,  0x2D04, -0x69C3, -0x14CA, -0x1CD3,  0x2F8D,  0x2DC6,
    -0x62F6,  0x6A80,  0x6AF2,  0x3A52, -0x075F, -0x4277,  0x15BC, -0x5B56,
     0x6426, -0x6B15, -0x749A,  0x1C04,  0x1A6C, -0x249C,  0x57CA, -0x73EB,
     0x5FE5,  0x23DE,  0x40B0,  0x2957,  0x06EB, -0x06ED, -0x2500, -0x55EA,
    -0x4C0C, -0x60D9,  0x2511,  0x29C2,  0x6826, -0x543C, -0x6162,  0x22FA,
    -0x2B3C,  0x0F3E,  0x6EDB,  0x1CDA, -0x1AF7,  0x0031,  0x0723,  0x7411,
     0x25D7,  0x441F, -0x282D, -0x31D0,  0x55D3,  0x6B99,  0x74C0, -0x5245,
    -0x2AAC,  0x605B, -0x2A33, -0x5180,  0x48C2, -0x120B,  0x0C21, -0x1958,
     0x02CC, -0x6490,  0x0386, -0x17F0, -0x3FFC,  0x7A71, -0x369F, -0x0CA1,
     0x1754,  0x4C62, -0x2D35, -0x45A3,  0x36E1, -0x62E4, -0x32AF,  0x5F09,
     0x66C7,  0x318E,  0x77CF,  0x09F9, -0x2CD0,  0x66E6, -0x0F10, -0x5C90,
     0x125D, -0x0C3F,  0x1ECD,  0x3FBB, -0x0A03, -0x732F, -0x73D2, -0x62B4,
     0x2276, -0x0E70,  0x55E9,  0x5C1C, -0x1581, -0x2898, -0x701A,  0x46C5,
    -0x1458,  0x45EA, -0x41BA,  0x4FE4, -0x0DC1, -0x3989, -0x35DF, -0x54C6,
    -0x58F0,  0x0DF5, -0x0292, -0x6FF3,  0x7B8E,  0x7601, -0x7E73,  0x2049,
     0x5ADA, -0x0FE2, -0x1816, -0x0D17, -0x5AD5, -0x358E,  0x3645, -0x3FEC,
    -0x11E9, -0x188E, -0x0BE0, -0x3F77, -0x03C6, -0x2CE3, -0x403A,  0x1BC5,
    -0x6C3B,  0x4333, -0x1789,  0x0F67,  0x7E6A,  0x74EC, -0x6FCD,  0x315A,

     0x6023, -0x0B50, -0x3453,  0x5943, -0x2F98,  0x4D57,  0x4BD2, -0x535A,
     0x2F39,  0x155C,  0x0F7D,  0x5354, -0x3572, -0x1D61, -0x6D38,  0x5299
},

};

short x_c[NUM_INPUTS][2*N + 2*PAD];
short x_i[NUM_INPUTS][2*N + 2*PAD];

short y_c[NUM_INPUTS][2*N + 2*PAD];
short y_i[NUM_INPUTS][2*N + 2*PAD];
short y_sa[NUM_INPUTS][2*N + 2*PAD];

short w[NUM_INPUTS][2*N + 2*PAD];

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

    for (j = 16, k = 1; j <= N; k++, fail = 0, j *= 2) {
        t_c = 0;
        t_i = 0;

        for (n = 31, m = 1; (j & (1 << n)) == 0; n--, m++)
            ;
        radix = m & 1 ? 2 : 4;

        /* -------------------------------------------------------------------- */
        /* Generate twiddle factors                                             */
        /* -------------------------------------------------------------------- */
        gen_twiddle_ifft16x16_imre(&w[0][PAD], j);

        /* -------------------------------------------------------------------- */
        /*  Copy vector to all inputs.                                          */
        /* -------------------------------------------------------------------- */
        memcpy(x_c, x, sizeof(x_c));
        memcpy(x_i, x, sizeof(x_i));
        memcpy(y_i, y_c, sizeof(y_i));

        /* -------------------------------------------------------------------- */
        /*  Check the results arrays, and report any failures.                  */
        /* -------------------------------------------------------------------- */
        for(i = 0; i < NUM_INPUTS; i++) {
            t_c += time_c(i, j) - t_overhead;
            t_i += time_i(i, j) - t_overhead;
        }

        printf("DSP_ifft16x16_imre\tIter#: %d\t", k);

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
 
        if (diff_max > 15) {
            fail++;
            printf("Result Failure (y_i) ");
        }
        else
            printf("Result Successful (y_i) ");

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
clock_t time_c(int cur_input, int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    DSP_ifft16x16_imre_cn(&w[cur_input][PAD], n, &x_c[cur_input][PAD], &y_c[cur_input][PAD]);
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
    DSP_ifft16x16_imre(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_ifft16x16_imre_d.c                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

