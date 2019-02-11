/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fft32x32s_d.c -- Driver file for DSP_fft32x32s                 */
/*                                                                         */
/*  USAGE                                                                  */
/*      This code contains a driver program for testing the 'DSP_fft32x32s'*/
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

#include "DSP_fft32x32s_cn.h"
#include "DSP_fft32x32s.h"
#include "gen_twiddle_fft32x32s.h"

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
#define NUM_INPUTS (1)

/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */

int x[NUM_INPUTS][2*N + 2*PAD] =
{
/* Input Number: 0 */

{
     0x7730673F,  0x40F75764, -0x203AC8A0, -0x41972FA3,
    -0x2DB04F7B,  0x45222AA3, -0x1F31237F, -0x1992913F,
     0x3261DFAD, -0x4937FF6E,  0x74E4C539,  0x229C9F2E,
     0x75FC706A, -0x0E0D8C8F, -0x3E3CBB62, -0x3589CDFB,

    -0x697ADCDC,  0x4544B919, -0x1CE53FC7, -0x27A257BA,
     0x43E77DBE,  0x23B4D948,  0x179C426E,  0x7A37CA7E,
     0x3A1A0BB3, -0x56BCB69E, -0x16CDE69F,  0x4461F66D,
    -0x19E60113,  0x19427D12, -0x1A37FC14, -0x7AA77435,
    -0x3653760F, -0x467C1EA7,  0x51426B18,  0x4AA611BD,
     0x23A193CE, -0x74DB3F7B,  0x6A092CA6,  0x7D96816F,
     0x63DC3555,  0x7642998D, -0x5C3B9BE9, -0x53E5B9AA,
    -0x24357CE4,  0x50445F5F,  0x71AAD7C7, -0x0B79A15E,
     0x39B624CC,  0x4B13288E,  0x12F85E8C, -0x6882CDB2,
     0x4681322F,  0x4AE3C9ED, -0x1DFA24A3, -0x515F649E,
     0x6C37F394, -0x660B236D, -0x5080B87B, -0x7A757523,
     0x7A09CFF1, -0x742C473A, -0x6DC2BA1F,  0x1C7EE9C3,
     0x32221E53,  0x7CA4D353, -0x2CC23F65,  0x4C6022D5,
     0x20E74318, -0x4618F135,  0x4C3C1F01,  0x1169D67C,
     0x2E0B8D6E, -0x2FC388D5, -0x2C8C822C,  0x7A223C4C,
     0x7E126A9F, -0x434F1494,  0x29F371A9, -0x44E44942,
     0x13A667A4, -0x7FFECA84, -0x11DE1930, -0x161BF473,
    -0x50A28380, -0x6090F7DE,  0x19D77D47, -0x27372FC4,
    -0x7BABDB1B,  0x037E7649,  0x79A1FC31, -0x64347EB6,
     0x232CC4A6, -0x44B3B3CB, -0x4B5FB7A7,  0x3063C384,
     0x31F2DD69,  0x2BD7DA1E,  0x5289753F, -0x3487AAF2,
     0x625C8D2B,  0x1BCEADB9,  0x4948562F,  0x4A223088,
     0x38EBDD09,  0x2A61B128, -0x703ADC29,  0x4AAB4FE7,
     0x077457D0,  0x299043CF,  0x3046AAF8,  0x644AA770,
    -0x3D808C27, -0x27854F67,  0x6BF88F8D,  0x112CCE5D,
     0x031245B1, -0x71C95DDC,  0x54120F0A, -0x54CF3351,
    -0x1AA9FB02,  0x3C9CF34C,  0x771CDF19,  0x1EF096A0,
     0x199ED140,  0x5EA477B4,  0x07DB8F67, -0x4D7E3FB5,
    -0x3CAFA539,  0x50B42C9F,  0x0A5AF7FA, -0x7A812D0C,
    -0x60CF437F,  0x7F785CC8,  0x0F8F3C89,  0x26C8CE76,
    -0x1A73C6FA,  0x0EBA2594, -0x13D1299B, -0x31699A98,
     0x7CC53D79,  0x4FBAF637, -0x09EED199, -0x33C9ACA8,
    -0x1E41D45A, -0x4E798CC9,  0x4CC53D67, -0x79E48F3E,
     0x69AA78F0, -0x762AB419, -0x66443A41, -0x4E5A1ADF,
     0x34BA9686,  0x41E57439, -0x176874AF,  0x1A3118B1,
     0x712D2962,  0x71D05D8B, -0x0AE1D662, -0x581D42A7,
     0x62410B90,  0x58F284CF, -0x7CB61CA1, -0x125268C4,
    -0x547865C3,  0x3AC002A6,  0x3BFA0F2A, -0x07D09C8D,
     0x5912D711,  0x29AB7AD9, -0x71347660, -0x504C848C,
     0x3F0FCF54, -0x547F0137,  0x1C84B3A5,  0x610D949A,
     0x0A35D553, -0x3638A1C5,  0x1EB3851F, -0x095EC59F,
    -0x5C5C0066,  0x06A75E15,  0x59DF23BD,  0x46416CC1,
     0x508D8070, -0x4B359B7E,  0x14E0884B,  0x1335F237,
     0x1B5D3D1C,  0x33C00BFB, -0x6D2447F4,  0x2A19D1F6,
     0x06A44273, -0x699DD93F, -0x6DA9FA61,  0x2AEF7AC2,
     0x777A7034,  0x25BDAD39,  0x55F5DAE7,  0x69F41BF0,
     0x70B709A7,  0x51F51CB4, -0x58A66677, -0x75425AE9,
     0x118E7E08, -0x7F4F43E0,  0x6E950363,  0x2B09FBE1,
    -0x2CF4EDC9,  0x467D5620,  0x40D2AC97,  0x43DFCE89,
     0x11EFC33B, -0x7D3F24F0,  0x778AFE9C, -0x6197577C,
     0x56740300, -0x24638D90,  0x55E84CD8,  0x000BA2D1,
    -0x169A4014,  0x2A5F753A, -0x5C3595C0,  0x6D47486F,
     0x242733AE,  0x42F2DC9A,  0x5CE0588A,  0x19D62985,
     0x121608E9, -0x603D6C63, -0x2A8E86A8,  0x768596A4,
    -0x3737BDEE,  0x7FB5413B, -0x0BC32800, -0x0FA5F23B,
     0x10B67A2A, -0x286A0AB2, -0x19020BB4, -0x3B8E30A2,
    -0x31461847, -0x4B7AB507, -0x26E95C34, -0x7AE3DAD3,
    -0x4F095275,  0x7FF26DEE,  0x3DCF7930, -0x3E3229DC,
    -0x5E5BFD39, -0x5C7B68DB,  0x0EC44025,  0x4D314004,
    -0x7BCD6142,  0x20977674, -0x671800BA, -0x4BE559E6,
    -0x52B010F1,  0x79ACF898,  0x4FB0078E,  0x4CA429AD,
    -0x59A45675, -0x739FEEDC,  0x1DE297D0,  0x731AF08D,
    -0x4658EB97, -0x2D9B1D2A, -0x3D857D3D,  0x6A1FF755,
    -0x49D34BC0,  0x7DF5D9D9, -0x53C493F3,  0x5C9810C9,
    -0x73F14BB5,  0x0257306D, -0x1DA8F222,  0x08D191E8,
     0x1993A372, -0x7D359C84,  0x68C6048B, -0x7291D3DD,
    -0x3614FF5C, -0x6274ED6C, -0x4D534641, -0x216F86C3,
     0x77630AEF,  0x264DCFCC, -0x708E3B57,  0x5BCAA450,
     0x107669F0,  0x3FB7530F,  0x2AEE6DB7,  0x0C45D687,
     0x7E3E1BF9,  0x5562A957, -0x7FBE52A0,  0x07B6B9F0,
     0x59C93193, -0x72273BB7, -0x173FB994,  0x738CBC06,
    -0x23362545,  0x0415FEC0,  0x138F614F, -0x46218AA1,
    -0x64D2C490, -0x7AF8FC44,  0x1D533B06,  0x4FA0B7FA,
    -0x7BEB71F9,  0x1993B53E,  0x1F896300, -0x4B6A2938,
    -0x5C58E33C,  0x00946A8C, -0x3FFF036E,  0x098093CC,
     0x294D7248, -0x6E9DD5A5,  0x52EE9670, -0x2FE3C88D,
     0x39C77139,  0x7A554C67, -0x08D4EE50,  0x54526286,
    -0x01555B40, -0x152FF70E,  0x3C0C04D9,  0x2F2AF956,
     0x7DB96944,  0x1A4271A9, -0x32A1BE89,  0x7F0BCE7F,
    -0x4861A405, -0x3A4DA089, -0x62FE2746,  0x35AE6CE4,
    -0x79726447, -0x06B83646,  0x1EA92F9E,  0x1158984A,
    -0x38C1AB74, -0x2BABFE93, -0x08C75AE3, -0x402607E1,
     0x42CD17A4, -0x57A09453, -0x3ABFC219, -0x633E9514,
    -0x21077C00, -0x044DE7D1,  0x5B24E323, -0x649B7717,
    -0x6BBA499C, -0x061932DF,  0x0E58ACC2, -0x28EF26BA,
    -0x5483F4E5, -0x4210FF14,  0x7C43B5CA,  0x3F133090,
    -0x49EB5500,  0x08313965,  0x6446FF3B, -0x0A094B37,
    -0x26139AB0, -0x23F69C19, -0x06A41A0D, -0x3E7FE55E,
    -0x2A06AA3E,  0x7C648CD2,  0x41DF981F,  0x3AF58965,
     0x5149D974,  0x49CE8FF9, -0x0E09D54F,  0x0A1DADFE,
    -0x0B1AAFF3,  0x14882C70,  0x5A13A264, -0x287C8C47,
    -0x49DCD344,  0x45191050, -0x30DE5A38,  0x557DF620,
     0x05C4C874,  0x6EE443D4,  0x14CD27D3, -0x048EE37C,
     0x248694F4, -0x37BF7591,  0x596EA67F, -0x2025AB4B,
     0x518D0718,  0x0A8E3540,  0x2E127AEF,  0x30910E56,
     0x332AE4F5,  0x2DD1D372,  0x042CABA0, -0x1E27A496,
     0x0E92473B, -0x6BB9A1FA, -0x4CA129E2, -0x1261C783,
     0x34DF025F,  0x15814A88,  0x7EEBA1C6, -0x366FF803,
     0x460DC618,  0x6D880825,  0x28433C10,  0x7360B839,
    -0x4FC3676E, -0x6D948E49, -0x7FC9971E, -0x512BE475,
    -0x0D11E901,  0x70E7A42B, -0x03B96897, -0x20EC1BD7,
     0x288E03E3, -0x767F3723, -0x256A6FFD,  0x0BB4D222,
     0x5AEAAAAC, -0x075EBAAC,  0x39FE1FA8, -0x7CF26C01,
     0x11058417,  0x5E3EE3EE, -0x3838A29D, -0x4FB93B6D,
    -0x4C365024,  0x2B7359ED,  0x6D75F750, -0x7E585693,
     0x1C23B41E, -0x2657378A,  0x7B440AA8,  0x03AD107D,
     0x04F4172B,  0x7EB3A2F1, -0x1D40F1B1, -0x63A123A9,
    -0x5694CBFD,  0x4E7C8257, -0x1106BA8E,  0x6C5DC6A4,
     0x3C41EC26,  0x7DA36EE9,  0x06E243A8,  0x523FC040,
    -0x6EB063D4,  0x04A801CD, -0x0EB808E0,  0x15A2917B,
    -0x66F71C58, -0x2CF3EFEE,  0x1FEBC759,  0x36871102,
     0x1F5BB1CF, -0x23FED257,  0x79433DDC, -0x20986107,
     0x45692B70, -0x6EF1604B,  0x3653B887, -0x7D6FC74C,
     0x51A8D2AB,  0x3A3A44D6,  0x3130B1DE, -0x6AC3385B,
     0x33E07FFB, -0x48C51932,  0x4A9A09E2, -0x0C0DE61D,
     0x5889AA00,  0x28197119,  0x4741E7F8,  0x689CFDEB,
     0x41107899, -0x09175B18, -0x41DA5EB0, -0x2214E503,
     0x587723C5, -0x3D125AF4,  0x7F97315E, -0x588C1357,
    -0x6A2AE137, -0x4331FAC1,  0x085EBAD3, -0x7CF792FD,
     0x62409625, -0x24B94D9C,  0x7D7C9BAB, -0x4E1B1201,
     0x408DB7CE,  0x7BD35622, -0x5FEE784B, -0x4EFA6787,
    -0x4487C2CC, -0x1B155D8F,  0x57E53330,  0x31512761,
     0x19AADB8B,  0x2E2A058F,  0x2F0B0FEB, -0x7005C069,
     0x5524E4E7,  0x140C52D9,  0x662E8673, -0x6C5F0219,
    -0x227E3869,  0x22A2D416, -0x0007AB3D, -0x4444D048,
    -0x6D5627B1, -0x2F3EB462,  0x531B6201, -0x433F4824,
    -0x6DAB1967, -0x02BDA606, -0x547F4D3A, -0x61795CF4,
     0x41FC1C0E,  0x50B6DA5B,  0x6411D86D,  0x0172698F,

     0x20A5AEDC,  0x021FAF8E,  0x0DA880E8,  0x07E0D386,
    -0x21F026F0, -0x78D5943A,  0x139A7DA1,  0x5F4C1D64,
     0x37C1A72D, -0x5F938725,  0x6D6DEFE8, -0x023D48F2,
     0x137D0C87,  0x4D1E226E, -0x2DDE15A1, -0x0FFBC2DC
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
        gen_twiddle_fft32x32s(&w[0][PAD], j, 2147483647.5);

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

        printf("DSP_fft32x32s\tIter#: %d\t", k);

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
 
        if (diff_max > 12) {
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
    DSP_fft32x32s_cn(&w[cur_input][PAD], n, &x_cn[cur_input][PAD], &y_cn[cur_input][PAD]);
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
    DSP_fft32x32s(&w[cur_input][PAD], n, &x_i[cur_input][PAD], &y_i[cur_input][PAD]);
    t_stop  = _itoll(TSCH, TSCL);
    return  t_stop - t_start;
}

/* ======================================================================== */
/*  End of file:  DSP_fft32x32s_d.c                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

