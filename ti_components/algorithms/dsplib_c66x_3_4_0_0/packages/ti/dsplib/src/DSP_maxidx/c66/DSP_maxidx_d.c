/* ======================================================================== */
/* DSP_maxidx_c.h -- Maximum Vector Value                                   */
/*                   Driver Code Implementation                             */
/*                                                                          */
/* Rev 0.0.1                                                                */
/*                                                                          */
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

#include "DSP_maxidx_cn.h"
#include "DSP_maxidx.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;

#define FORMULA_SIZE          2
#define FORMULA_DEVIDE        16
#define CYCLE_FORMULA_NX_PT1  128
#define CYCLE_FORMULA_NX_PT2  192
/* inverse of [128 1] */
/*            [192 1] */
float form_inv[FORMULA_SIZE][FORMULA_SIZE] = 
{{-0.0156,    0.0156},
 { 3.0000,   -2.0000}
};
float form_temp  [FORMULA_SIZE];
int   form_cycle [FORMULA_SIZE];
int   form_result[FORMULA_SIZE];

/* kernel specific input arrays */
#pragma DATA_ALIGN(Input, 8);
/* implementation specific output arrays */
#pragma DATA_ALIGN(Max_c, 8);
#pragma DATA_ALIGN(Max_i, 8);

#define N       (256)
#define nInputs (N)
#define PAD     (8)

short Input[N] =
{
  0x429e, 0x4aab, 0x2444, 0x0589, 0x0bbd, 0xfc91, 0xb1a7, 0xbae7,
  0xcb1c, 0xf4a0, 0xe041, 0xa21e, 0x0e65, 0x4db2, 0xeff4, 0x05cf,
  0xed66, 0x3e8a, 0xe11c, 0x1292, 0xe176, 0x0529, 0xe129, 0xe628,
  0x19f5, 0x038b, 0x34f2, 0x2b68, 0x34e1, 0x118a, 0xcf36, 0x2d18,
  0x0c28, 0x346f, 0x0cc0, 0xb5f4, 0xcdfa, 0x307a, 0xd0df, 0x96d2,
  0xc3b8, 0x11f7, 0xd42c, 0xbe45, 0x0154, 0x2fae, 0xc9cc, 0x5ae8,
  0x0c9b, 0xe65d, 0x2135, 0x1877, 0xef80, 0x5e91, 0xf4b0, 0xb56c,
  0x0121, 0x3be5, 0x0bdc, 0x2a7c, 0xfa5e, 0xdbcd, 0xb379, 0xb1f0,
  0x1035, 0x166b, 0x0175, 0x4545, 0x38ce, 0xed13, 0x7fad, 0xda9f,
  0x2062, 0x004a, 0x1226, 0xbb35, 0xb1ef, 0xdaaa, 0xfe8b, 0xbabd,
  0x9ebb, 0xe52b, 0x096e, 0xfc4e, 0xfa24, 0xce40, 0xe887, 0xe5ee,
  0xf511, 0x1f03, 0x21c4, 0xc635, 0x412a, 0x41c2, 0xe4dc, 0xd6fd,
  0xd448, 0xe2cf, 0x0cbe, 0xee51, 0xff33, 0xe038, 0xa22a, 0x4f86,
  0xdaac, 0x098a, 0xf195, 0xd26a, 0xd377, 0xbf09, 0x1f2e, 0x926c,
  0x232e, 0x539c, 0x3fae, 0x1c5d, 0xf8b3, 0xde14, 0xf1cb, 0x0037,
  0x1551, 0xe461, 0x0a4c, 0x33fe, 0x201f, 0x1ec0, 0x1422, 0x26e8,
  0x1FAE, 0x1489, 0x1EC9, 0x6F5E, 0x5BE8, 0x024A, 0x75B7, 0x2217,
  0x2EB6, 0x4D81, 0x0757, 0x254F, 0x7FCC, 0x6A05, 0x65AE, 0x5AC9,
  0x5D3B, 0x4219, 0x47E8, 0x4A2C, 0x03AD, 0x6576, 0x00D7, 0x7AA6,
  0x0016, 0x2FEE, 0x55CB, 0x1E2C, 0x32AC, 0x2494, 0x4F3C, 0x6FFF,
  0x0826, 0x4087, 0x4C0A, 0x2E16, 0x4CEB, 0x6DE1, 0x03EC, 0x0BC2,
  0x484A, 0x2E04, 0x7E82, 0x4FAD, 0x55DF, 0x6293, 0x5530, 0x4875,
  0x5E20, 0x7DB6, 0x516A, 0x47EE, 0x4EC0, 0x3429, 0x2649, 0x3754,
  0x3F41, 0x00AD, 0x37BA, 0x5271, 0x3CFA, 0x1F8B, 0x2494, 0x371C,
  0x51F4, 0x1E9F, 0x0CCB, 0x59E3, 0x180D, 0x38F2, 0x2132, 0x2B94,
  0x17D1, 0x31A9, 0x275A, 0x2993, 0x417D, 0x49B1, 0x750B, 0x123F,
  0x3CCC, 0x18E2, 0x61E9, 0x5E28, 0x1D06, 0x68BA, 0x1647, 0x6698,
  0x18EE, 0x50D8, 0x4231, 0x2468, 0x4A2F, 0x4FED, 0x7584, 0x6DC2,
  0x3008, 0x23BA, 0x5366, 0x2ADE, 0x379A, 0x751F, 0x3367, 0x4DE8,
  0x4A1C, 0x42C4, 0x3A38, 0x34B1, 0x031A, 0x161B, 0x3F68, 0x244D,
  0x75F3, 0x7695, 0x7439, 0x797D, 0x3AD0, 0x18E2, 0x0248, 0x2D0D,
  0x5974, 0x31D6, 0x0D25, 0x3A8C, 0x2907, 0x343B, 0x6A7F, 0x24C1,
};

/* results, padded with guard to show array overflow */
int Max_c;
int Max_i;

clock_t time_c(int n);
clock_t time_i(int n);

/****************************************************************************/
/* TOP LEVEL DRIVER FOR THE TEST.                                           */
/****************************************************************************/
int main()
{
    clock_t t_overhead, t_start, t_stop, t_c, t_i;
    int i, j, n, fail = 0;
    int form_error = 0;

   /*************************************************************************/
   /* COMPUTE THE OVERHEAD OF CALLING CLOCK TWICE TO GET TIMING INFO.       */
   /*************************************************************************/
    /* Initialize timer for clock */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    t_stop = _itoll(TSCH, TSCL);
    t_overhead = t_stop - t_start;

    for(n = 128, i = 1; n <= N; i++, n += 16) {
        /********************************************************************/
        /* CALL THE INDIVIDIUAL TIMING ROUTINES.                            */
        /********************************************************************/
        t_c = time_c(n) - t_overhead;
        t_i = time_i(n) - t_overhead;

        /********************************************************************/
        /* PRINT TIMING RESULTS                                             */
        /********************************************************************/ 
        printf("DSP_maxidx\tIter#: %d\t", i);

        /********************************************************************/
        /* CHECK THE RESULTS ARRAY.                                         */
        /********************************************************************/
        if (Max_i != Max_c) {
            fail++;
            printf("Result Failure (max_i)");
        }
        else
            printf("Result Successful (max_i)");

        printf("\tN = %d\tnatC: %d\tintC: %d\n", n, t_c, t_i);

        if (n == CYCLE_FORMULA_NX_PT1)
          form_cycle[0] = t_i;
        if (n == CYCLE_FORMULA_NX_PT2)
          form_cycle[1] = t_i;
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

    if (!form_error)
        if (FORMULA_DEVIDE == 1) {
            printf("Cycles:  %d*Nx + %d \n", form_result[0], form_result[1]);
        }
        else {
            printf("Cycles:  %d/%d*Nx + %d \n", form_result[0], FORMULA_DEVIDE, form_result[1]);
        }
    else
        printf("Cycles Formula Not Available\n");

    return (fail);
}

/****************************************************************************/
/* COMPUTE THE ELAPSED TIME OF THE COMPILED NATURAL C ROUTINE               */
/****************************************************************************/
clock_t time_c(int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    Max_c = DSP_maxidx_cn(Input, n);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/****************************************************************************/
/* COMPUTE THE ELAPSED TIME OF THE COMPILED INTRINSIC C ROUTINE             */
/****************************************************************************/
clock_t time_i(int n)
{
    clock_t t_start, t_stop;

    t_start = _itoll(TSCH, TSCL);
    Max_i = DSP_maxidx(Input, n);
    t_stop = _itoll(TSCH, TSCL);
    return t_stop - t_start;
}

/****************************************************************************/
/*                  END OF DRIVER FILE                                      */
/****************************************************************************/

