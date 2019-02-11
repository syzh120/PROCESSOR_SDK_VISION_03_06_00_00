/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_to_yuv   : Test bench.                          */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*                                                                 */
/* The function rgb_to_yuv, converts rgb to interleaved yuv.       */
/* by applying coefficients weighting red, blue and green,         */
/* to luma. Similarly we aplly a weighted product of red,          */
/* blue and green to U and V.                                      */
/*                                                                 */
/* A possible set of coefficients, to use is suggnsted at:         */
/* http://msdn.microsoft.com/en-us/library/ms893078.aspx           */
/*                                                                 */
/* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16          */
/* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128          */
/* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128          */
/*                                                                 */
/* The values from this equation, will have to be clamped          */
/* between 0..255.                                                 */
/*                                                                 */
/* This benchmark is intended to highlight the value of predicated */
/* stores to memory.                                               */
/*                                                                 */
/* API:                                                            */
/* void rgb_to_yuv                                                 */
/* (                                                               */
/*     unsigned char    iPtrR[],                                   */
/*     unsigned char    iPtrG[],                                   */
/*     unsigned char    iPtrB[],                                   */
/*     unsigned short   width,                                     */
/*     short            coefs[],                                   */
/*     unsigned char    iPtrOut[]                                  */
/* )                                                               */
/*                                                                 */
/* The function "rgb_to_yuv" accepts red, green and blue pixels    */
/* in arrays "iPtrR", "iPtrG" and "iPtrB" into an interleaved      */
/* array of YUYV pixels stored in "iPtrOut" by applying a 3x3      */
/* array of coefficients to convert from RGB to YUV space.         */
/*                                                                 */
/*=================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_profile.h"

#include "vcop.h"

#define true    1
#define false   0


#if VCOP_HOST_EMULATION
  #include "vcop_rgb_to_yuv_kernel.k"    // kernel source
#else
  void rgb_to_yuv
  (
      __vptr_uint8     iPtrR,
      __vptr_uint8     iPtrG,
      __vptr_uint8     iPtrB,
      unsigned short   width,
      short            coefs_r,
      short            coefs_g,
      short            coefs_b,
      __vptr_int16     coefs,
      __vptr_uint8     iPtrOut
  );
#endif

#define IN_SIZE 32
#define OUT_SIZE 64

#pragma DATA_SECTION (R, "Adata")
unsigned char R[IN_SIZE] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF8, 0xF7,
    0xCF, 0xCC, 0xCD, 0xCA, 0xCE, 0xC4, 0xC3, 0xC2
};

#pragma DATA_SECTION (G, "Adata")
unsigned char G[IN_SIZE] =
{
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x88, 0x87,
    0x9F, 0x9C, 0x9D, 0x9A, 0x9E, 0x94, 0x93, 0x92
};

#pragma DATA_SECTION (B, "Adata")
unsigned char B[IN_SIZE] =
{
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC8, 0xC7,
    0xDF, 0xDC, 0xDD, 0xDA, 0xDE, 0xD4, 0xD3, 0xD2
};

#pragma DATA_SECTION (YUV, "Bdata")
unsigned char YUV[OUT_SIZE] = {0};

#pragma DATA_SECTION (EOut, "EOutdata");
unsigned char EOut[OUT_SIZE] =
{
   0xAD,  0x4A,  0x4B,  0x4A,  0xAD, 0x4B,  0x4B,  0x4C,
   0xAD,  0x4D,  0x4B,  0x4E,  0xAD, 0x4F,  0x4B,  0x50,
   0xAA,  0x47,  0x52,  0x48,  0xAA, 0x49,  0x52,  0x49,
   0xAA,  0x4A,  0x52,  0x4B,  0xAA, 0x4C,  0x52,  0x4D,
   0x8B,  0x9E,  0xAD,  0x9D,  0x8B, 0x9C,  0xAD,  0x9B,
   0x8B,  0x9B,  0xAD,  0x9A,  0x8B, 0x98,  0xAD,  0x97,
   0x95,  0x9B,  0x91,  0x99,  0x95, 0x9A,  0x91,  0x97,
   0x95,  0x9A,  0x91,  0x92,  0x95, 0x91,  0x91,  0x90
};

unsigned short width = 32;

/* Re-arranged to take advantage of vector core features */

#pragma DATA_SECTION (coefs, "Bdata")
short coefs[9] =
{
     66, 129,  25,    /* ry0   gy0  by0 */
    -38,  112, -74,   /* ru0   rv0  gu0 */
    -94, 112,  -18    /* gv0   bu0  bv0 */
};

void print_output();

#define W_OUTPUT (8)
#define H_OUTPUT (8)

int main()
{
#ifdef REPORT
    int ok;
    FILE* fpReport = fopen("../../../report.csv","a+");
    #ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;

    EVE_SCTM_Enable(CTM);
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);

    sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    #endif
#endif
    rgb_to_yuv
    (
        R,
        G,
        B,
        width,
        coefs[0],
        coefs[1],
        coefs[2],
        coefs,
        YUV
    );
#ifdef REPORT
    #ifdef SCTM
    sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
    assert(overflow!=1);

    exec_diff = sctm_t2 - sctm_t1;
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
    #endif

    fprintf(fpReport,"vcop_rgb_to_yuv,");
    fprintf(fpReport,"%d,",IN_SIZE);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",IN_SIZE);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"1,");
#endif


#ifdef CONSOLE
    print_output();
#endif

    if (memcmp (YUV, EOut, sizeof(YUV))){
#ifdef CONSOLE
        printf ("Fail \n");
#endif
    }
    else {
#ifdef REPORT
        ok = 1;
#endif
#ifdef CONSOLE
        printf ("Pass \n");
#endif
    }

#ifdef REPORT
    if(ok) {
        fprintf(fpReport,"PASS,");
    }
    else {
        fprintf(fpReport,"FAIL,");
    }
    #ifdef SCTM
        fprintf(fpReport,"%d\n",exec_diff);
    #endif
    if(fpReport){
        fclose(fpReport);
    }
#endif

    return 0;
}

void print_output()
{
   int i, j;
   for (i = 0; i < H_OUTPUT; ++i)
   {
      for (j = 0; j < W_OUTPUT; ++j)
         printf("%x ", YUV[i * W_OUTPUT + j]);
      printf("\n");
   }
}

/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv.c                                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/


