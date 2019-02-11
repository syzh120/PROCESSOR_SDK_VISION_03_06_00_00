/* ======================================================================= */
/* DSPF_sp_erand_d.c -- sp_erand driver code  implementation               */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  */
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

/* ======================================================================== */
/*  Includes                                                                */
/* ======================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <c6x.h>

/* Interface header files for the natural C and optimized C code */
#include "DSPF_sp_erand_cn.h"
#include "DSPF_sp_erand.h"

/* ======================================================================== */
/*  DEFINES                                                                 */
/* ======================================================================== */
#define SEED                  (1776)
#define MAX_ARRAY_SIZE        (256)

/* This #define is used to generate a large set of random numbers and save
 * them to a file for further analysis. Comment it out if it is not desired
 */
//#define OUTPUT_FILE

#ifdef OUTPUT_FILE
#define LARGE_SAMPLE_SIZE     (1048576) /* 2^20 */
#endif

#define FORMULA_SIZE          (2)
#define FORMULA_DIVIDE        (1)
#define CYCLE_FORMULA_NX_PT1  (64)
#define CYCLE_FORMULA_NX_PT2  (128)

#define CLOCK64() (_itoll(TSCH, TSCL))

#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#define data_size _data_size
#endif

/* ======================================================================== */
/*  TYPEDEFS                                                                */
/* ======================================================================== */
typedef unsigned long long clock_t64;

/* ======================================================================== */
/*  Gloabl Variables and Vectors                                            */
/* ======================================================================== */
extern int kernel_size;
extern int data_size;

float r_cn[MAX_ARRAY_SIZE];
float  r_i[MAX_ARRAY_SIZE];

float  form_temp  [FORMULA_SIZE];
clock_t64  form_cycle [FORMULA_SIZE];

/* inverse of [ 64 1] */
/*            [128 1] */
float form_inv[FORMULA_SIZE][FORMULA_SIZE] =
{{-0.0156,  0.0156},
 { 2.0000, -1.0000}
};


/* ======================================================================== */
/*  MAIN -- Top level driver for the test.                                  */
/* ======================================================================== */
int main(void)
{
  clock_t64 t_start, t_stop, overhead, t_cn, t_i;
  int i,j,arraySize, fail = 0;
  unsigned int state_cn[7], state_i[7];
  double diff_max, diff_temp;

#ifdef OUTPUT_FILE
  FILE *pFile;
  float x_cn_large[LARGE_SAMPLE_SIZE];
  float  x_i_large[LARGE_SAMPLE_SIZE];
#endif


  TSCL = 0; /**enable cycle counter */

  /* calculate overhead of calling _itoll() */
  t_start = CLOCK64();
  t_stop = CLOCK64();
  overhead = t_stop - t_start;

  /* Initialize State Variables */
  DSP_urand32_init_cn(SEED, NULL, state_cn);
  DSP_urand32_init(SEED, NULL, state_i);

  for (i = 1, arraySize = 8; arraySize <= MAX_ARRAY_SIZE; arraySize *= 2, i++)
  {

    /* =================================================================== */
    /* Time The Function Calls                                             */
    /* =================================================================== */
    TSCL = 0;
    t_start = CLOCK64();
    DSPF_sp_erand_cn(arraySize, r_cn, state_cn);
    t_stop = CLOCK64();
    t_cn = t_stop - t_start - overhead;

    TSCL = 0;
    t_start = CLOCK64();
    DSPF_sp_erand(arraySize, r_i, state_i);
    t_stop = CLOCK64();
    t_i = t_stop - t_start - overhead;

    /* =================================================================== */
    /* Print timing results                                                */
    /* =================================================================== */
    printf("DSPF_sp_erand\tIter#: %d\t", i);

    /* =================================================================== */
    /* Check the results arrays, and report any failures                   */
    /* =================================================================== */

    diff_max = 0;
    for(j = 0; j < arraySize; ++j)
    {
      diff_temp = r_cn[j] - r_i[j];
      if(diff_temp < 0.0)
        diff_temp = -diff_temp;
      if(diff_temp >= diff_max)
        diff_max = diff_temp;
    }


    if (diff_max > 1.0)
    {
      fail++;
      printf("Result Failure (r_i)");
    }
    else
    {
      printf("Result Successful (r_i)");
    }

    printf("\tSIZE = %d\tnatC: %lld\toptC: %lld\n", arraySize, t_cn, t_i);
    if (arraySize == CYCLE_FORMULA_NX_PT1)
      form_cycle[0] = t_i;
    if (arraySize == CYCLE_FORMULA_NX_PT2)
      form_cycle[1] = t_i;
  }

  /* Provide memory information */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  /* Provide profiling information */
  printf("Cycles:  %llu (N=128) %llu (N=256)\n", form_cycle[0], form_cycle[1]);

#ifdef OUTPUT_FILE
  /* Generate large sample size for third party statistical analysis */

  DSPF_sp_erand_cn(LARGE_SAMPLE_SIZE, x_cn_large, state_cn);

  TSCL = 0; /**reset cycle counter */

  t_start = CLOCK64();
  DSPF_sp_erand(LARGE_SAMPLE_SIZE, x_i_large, state_i);
  t_stop = CLOCK64();
   printf("Time For %d Samples: %f", LARGE_SAMPLE_SIZE, ((double)t_stop - (double)t_start - (double)overhead)/(double)LARGE_SAMPLE_SIZE);

  /* Print data to a binary file for further analysis */

  pFile = fopen("results.bin_cn", "wb");
  fwrite(x_cn_large, sizeof(x_cn_large[0]), sizeof(x_cn_large) / sizeof(x_cn_large[0]), pFile);

  pFile = fopen("results.bin_i", "wb");
  fwrite(x_i_large, sizeof(x_i_large[0]), sizeof(x_i_large) / sizeof(x_i_large[0]), pFile);
#endif

  printf("\n\n-----------------------------------------------------\n\n");

  return fail;
}

/* ======================================================================== */
/*  End of file:  DSPF_sp_erand_d.c                                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

