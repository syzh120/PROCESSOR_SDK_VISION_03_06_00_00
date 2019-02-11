/* ======================================================================= */
/* DSP_urand16_d.c -- urand16 driver code  implementation                  */
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
#include <c6x.h>

/* Interface header files for the natural C and optimized C code */
#include "DSP_urand16_cn.h"
#include "DSP_urand16.h"

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

unsigned short x_cn[MAX_ARRAY_SIZE];
unsigned short  x_i[MAX_ARRAY_SIZE];

float  form_temp  [FORMULA_SIZE];
clock_t64  form_cycle [FORMULA_SIZE];
int  form_result[FORMULA_SIZE];

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
  unsigned short seed_cn = SEED, seed_i = SEED;
  int i,j,arraySize, fail = 0;
  int form_error = 0;

#ifdef OUTPUT_FILE
  unsigned short x_cn_large[LARGE_SAMPLE_SIZE];
  unsigned short x_i_large[LARGE_SAMPLE_SIZE];
#endif

  TSCL = 0; /**enable cycle counter */

  /* calculate overhead of calling _itoll() */
  t_start = CLOCK64();
  t_stop = CLOCK64();
  overhead = t_stop - t_start;

  for (i = 1, arraySize = 8; arraySize <= MAX_ARRAY_SIZE; arraySize *= 2, i++)
  {

    /* =================================================================== */
    /* Time The Function Calls                                             */
    /* =================================================================== */
    TSCL = 0;
    t_start = CLOCK64();
    DSP_urand16_cn(&seed_cn, arraySize, x_cn);
    t_stop = CLOCK64();
    t_cn = t_stop - t_start - overhead;

    TSCL = 0;
    t_start = CLOCK64();
    DSP_urand16(&seed_i, arraySize, x_i);
    t_stop = CLOCK64();
    t_i = t_stop - t_start - overhead;

    /* =================================================================== */
    /* Print timing results                                                */
    /* =================================================================== */
    printf("DSP_urand16\tIter#: %d\t", i);

    /* =================================================================== */
    /* Check the results arrays, and report any failures                   */
    /* =================================================================== */
    if (memcmp(x_cn, x_i, arraySize))
    {
      fail++;
      printf("Result Failure (x_i)");
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
  for (i = 0; i < FORMULA_SIZE; i++)
  {
    form_temp[i] = 0;
    for (j = 0; j < FORMULA_SIZE; j++)
    {
      form_temp[i] += form_inv[i][j] * form_cycle[j];
    }


    if (i != (FORMULA_SIZE - 1))
    {
      form_result[i] = (int) (form_temp[i] * FORMULA_DIVIDE + 0.5);

      if ((form_result[i] - form_temp[i] * FORMULA_DIVIDE)> 0.1 ||
      (form_result[i] - form_temp[i] * FORMULA_DIVIDE) < -0.1)
      {
          form_error = 1;
      }
    }

    else
    {
      form_result[i] = (int) (form_temp[i] + 0.5);
    }
  }

  if (!form_error)
  {
    if(FORMULA_DIVIDE == 1)
      printf("Cycles:  %d*Nx + %d \n", form_result[0], form_result[1]);
    else
      printf("Cycles:  %d/%d*Nx + %d \n", form_result[0], FORMULA_DIVIDE, form_result[1]);
  }
  else
    printf("Cycles Formula Not Available\n");

#ifdef OUTPUT_FILE
  /* Generate large sample size for third party statistical analysis */

  DSP_urand16_cn(&seed_cn, LARGE_SAMPLE_SIZE, x_cn);


  TSCL = 0;
  t_start = CLOCK64();
  DSP_urand16(&seed_i, LARGE_SAMPLE_SIZE, x_i);
  t_stop = CLOCK64();

  printf("Average Speed for %lld Samples: %f", LARGE_SAMPLE_SIZE, ((double)t_stop-t_start-overhead)/LARGE_SAMPLE_SIZE);


  /* Print data to a binary file for further analysis */
  FILE* pFile_cn;
  pFile_cn = fopen("results.bin_cn", "wb");
  fwrite(x_cn_large, sizeof(x_cn_large[0]), sizeof(x_cn_large) / sizeof(x_cn_large[0]), pFile_cn);

  FILE* pFile_i;
  pFile_i = fopen("results.bin_i", "wb");
  fwrite(x_i_large, sizeof(x_i_large[0]), sizeof(x_i_large) / sizeof(x_i_large[0]), pFile_i);
#endif

  printf("\n\n-----------------------------------------------------\n\n");


  return fail;
}

/* ======================================================================== */
/*  End of file:  DSP_urand16_d.c                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

