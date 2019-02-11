/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"

#undef uint16
#undef int16
#undef int32

typedef unsigned short uint16;

#if VCOP_HOST_EMULATION
  #include "vcop_fft_64_16x16t_kernel.k"    // kernel source
#else
  void vcop_fft_64_16x16t_stage_1
  (
    __vptr_int16_arr  Pxi0,
    __vptr_int16_arr  Pxi1,
    __vptr_int16_arr  Pxi2,
    __vptr_int16_arr  Pxi3,
    __vptr_int16_arr  PCS1,
    __vptr_int16_arr  PCS2,
    __vptr_int16_arr  PCS3,
    uint16            bfys_per_grp[],
    uint16            grps[],
    uint16            passes,
    uint16            pinc3[],
    uint16            pinc4[],
    uint16            ptnc3[],
    uint16            ptnc4[]
  );

  void vcop_fft_64_16x16t_stage2
  (

    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    __vptr_int16      PCS1,
    __vptr_int16      PCS2,
    __vptr_int16      PCS3,
    uint16            bfys_per_grp,
    uint16            grps,
    uint16            pinc3,
    uint16            pinc4,
    uint16            ptnc3,
    uint16            ptnc4
  );

  void vcop_fft_64_16x16t_stage3
  (
    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    uint16            bfys_per_grp,
    uint16            grps,
    uint16            pinc3,
    uint16            pinc4
  );

  void vcop_fft_digit_rev_64
  (
    __vptr_int32      Px,
    __vptr_uint16     digit_rev,
    __vptr_int32      Py
  );


#endif


#define uint16  unsigned short 
#define int16   short 
#define int32   int
#define true    1
#define false   0

/* ------------------------------------------------------------------------- */
/*  Input test data, limited to 10-bit input range to deal with signal growth*/
/*  in FFT, a 64 point FFT has 3 stages, hence can grow by as much as        */
/*  6-bits to fit in the 16-bit range.                                       */
/* ------------------------------------------------------------------------- */

#define N (64)

#pragma DATA_SECTION (in, "Adata");
short in[128] =
  {
  	0x03F9, 0x00B3, 0x028E, 0x02A4, 0x0391, 0x03FC, 0x0346, 0x01BE,
  	0x02D2, 0x0110, 0x0269, 0x0331, 0x0331, 0x003B, 0x0229, 0x012B,
  	0x01E3, 0x01B6, 0x021B, 0x02BC, 0x0297, 0x02DC, 0x033E, 0x01B9,
  	0x0064, 0x021E, 0x028D, 0x02CC, 0x0106, 0x0037, 0x0047, 0x006E,
  	0x0063, 0x03B2, 0x000D, 0x00D8, 0x0103, 0x02EB, 0x024B, 0x0076,
  	0x023F, 0x0303, 0x006A, 0x003D, 0x0109, 0x0038, 0x0225, 0x03FF,
  	0x018D, 0x02A4, 0x018B, 0x02EC, 0x0216, 0x01E5, 0x0045, 0x023B,
  	0x0193, 0x023D, 0x0209, 0x03FA, 0x029C, 0x001B, 0x002E, 0x0232,
  	0x0270, 0x01AA, 0x0160, 0x032E, 0x0200, 0x0138, 0x0236, 0x023D,
  	0x0302, 0x02B9, 0x0132, 0x03F6, 0x029E, 0x013D, 0x0089, 0x001C,
  	0x02FD, 0x030F, 0x0284, 0x0332, 0x01B4, 0x00E0, 0x0126, 0x00B0,
  	0x022B, 0x02D4, 0x0130, 0x0297, 0x0132, 0x023B, 0x0171, 0x0342,
  	0x03E6, 0x0222, 0x0261, 0x011D, 0x0021, 0x009B, 0x001F, 0x031A,
  	0x03F0, 0x02DA, 0x02D9, 0x0192, 0x0339, 0x0392, 0x018D, 0x0309,
  	0x012C, 0x03C0, 0x033E, 0x0105, 0x0029, 0x0295, 0x01D9, 0x00A0,
  	0x03A2, 0x038A, 0x03A9, 0x004C, 0x0333, 0x003F, 0x02B7, 0x03F6,
  };

/* ------------------------------------------------------------------------- */
/*  Twiddle factor array organized as SC, or sinecosine pairs, and as        */
/*  e^j*2*pi*n*k/N eventhough it is an FFT (like an IFFT) with the negative  */
/*  sign comprehended by software.                                           */
/* ------------------------------------------------------------------------- */


#pragma DATA_SECTION (SC_vector, "Bdata");
short SC_vector[200] =
{
		0x0000, 0x7FFF, 0x0C8B, 0x7F61, 0x18F8, 0x7D89, 0x2527, 0x7A7C,
		0x30FB, 0x7640, 0x3C56, 0x70E1, 0x471C, 0x6A6C, 0x5133, 0x62F1,
		0x0000, 0x7FFF, 0x18F8, 0x7D89, 0x30FB, 0x7640, 0x471C, 0x6A6C,
		0x5A81, 0x5A81, 0x6A6C, 0x471C, 0x7640, 0x30FB, 0x7D89, 0x18F8,
		0x0000, 0x7FFF, 0x2527, 0x7A7C, 0x471C, 0x6A6C, 0x62F1, 0x5133,
		0x7640, 0x30FB, 0x7F61, 0x0C8B, 0x7D89, 0xE708, 0x70E1, 0xC3AA,
		0x5A81, 0x5A81, 0x62F1, 0x5133, 0x6A6C, 0x471C, 0x70E1, 0x3C56,
		0x7640, 0x30FB, 0x7A7C, 0x2527, 0x7D89, 0x18F8, 0x7F61, 0x0C8B,
		0x7FFF, 0x0000, 0x7D89, 0xE708, 0x7640, 0xCF05, 0x6A6C, 0xB8E4,
		0x5A81, 0xA57F, 0x471C, 0x9594, 0x30FB, 0x89C0, 0x18F8, 0x8277,
		0x5A81, 0xA57F, 0x3C56, 0x8F1F, 0x18F8, 0x8277, 0xF375, 0x809F,
		0xCF05, 0x89C0, 0xAECD, 0x9D0F, 0x9594, 0xB8E4, 0x8584, 0xDAD9,
		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};


/* ------------------------------------------------------------------------- */
/*  Region for output.                                                       */
/* ------------------------------------------------------------------------- */

#pragma DATA_SECTION (out, "Cdata");
short out[128] = {0};


/* ------------------------------------------------------------------------- */
/*  N/4 linear digit reversal table. For example, normal index 1, is         */
/*  placed in digit reversed index of 16 .                                   */
/* ------------------------------------------------------------------------- */

#pragma DATA_SECTION (digit_rev, "Bdata");
unsigned short digit_rev[16] =
{
		0,  16,  32,  48,  4,  20,  36,  52,
		 8,  24,  40,  56,  12,  28,  44,  60,
};

int16 EOut[128] =  {
		0x7EE3, 0x83F2, 0x0BEA, 0x05CC, 0x0CEF, 0xFC96, 0x0714, 0xF73E,
		0xFFED, 0xF80A, 0x07CB, 0x0997, 0x1234, 0x04DD, 0x03DD, 0x0BA1,
		0x0024, 0x04E2, 0xFCCF, 0xFF9A, 0xF81D, 0xFA11, 0x0635, 0xFCC0,
		0xFE21, 0xFED7, 0x06C9, 0x02D6, 0xFF4E, 0x05F9, 0xF17B, 0xF27A,
		0x0C0A, 0x0813, 0x0037, 0xFF5F, 0x00D7, 0xF128, 0xFBB2, 0x081C,
		0x02C8, 0xFF69, 0xF6B6, 0xF8C6, 0xF6F5, 0x039E, 0xF605, 0xF8A3,
		0xF3F4, 0xF504, 0x0160, 0x0097, 0x0292, 0xF310, 0xFD54, 0xFA55,
		0x03C1, 0x0269, 0x12E9, 0x07D4, 0x0BF4, 0xF549, 0xF8C8, 0x0185,
		0x0BEF, 0xFD7C, 0xF738, 0x0DC4, 0xFED5, 0xF160, 0xF1D6, 0xFEF4,
		0x05AD, 0xF3A8, 0x0889, 0xF3C7, 0xFE4A, 0x0251, 0x06A3, 0x0A57,
		0x0EA6, 0x02C4, 0x0081, 0xF07E, 0x0C05, 0xF6D7, 0xFE07, 0xF424,
		0x110F, 0x0355, 0x0AE9, 0xFDCA, 0xFE50, 0xEC13, 0x0EF9, 0xEDF6,
		0x016C, 0x1563, 0xFE17, 0x062D, 0xF3A1, 0x0F5E, 0x0198, 0xF822,
		0xFFB2, 0xF809, 0x0332, 0x12FC, 0xF8CD, 0xFBF4, 0xF4C7, 0xEFB5,
		0xF752, 0xFF42, 0x0254, 0x0D45, 0xFD0C, 0x009C, 0x0278, 0xFFEF,
		0xFDBB, 0x0083, 0x0029, 0x0004, 0x1416, 0x0767, 0x16C4, 0xF683,
};

/* ------------------------------------------------------------------------- */
/*  Repeat loop is leveraged for 1 pass, last 2 stages are done using        */
/*  vloop, total of 3 stages.                                                */
/* ------------------------------------------------------------------------- */

uint16 passes_rpt   = 1;
uint16 passes_vloop = 2;
uint16 passes       = 3;

/* ------------------------------------------------------------------------- */
/*  Spacing of the legs of the butterfly, as follows:                        */
/*                                                                           */
/*  Stage 1: 16 points N/4  apart.                                           */
/*  Stage 2:  4  points apart, loaded as 8 points apart, re-arranged.        */
/*  Stage 3:  1  point  apart, loaded as 8 points apart, re-arranged.        */
/*---------------------------------------------------------------------------*/

short *pxi0[3] = {&in[2*0],   &in[2*0],  &in[2*0]};
short *pxi1[3] = {&in[2*16],  &in[2*8],  &in[2*8]};
short *pxi2[3] = {&in[2*32],  &in[2*16], &in[2*16]};
short *pxi3[3] = {&in[2*48],  &in[2*24], &in[2*24]};

/*---------------------------------------------------------------------------*/
/*  Twiddle factors, are stored as 3 inputs per butterfly sequentially.      */
/*                                                                           */
/*  First stage: 0,     8,  16  3 twiddle factors per bfly, 16 bfys(N/4)     */
/*  Secd  stage: 16, 24, 32  3 twiddle factors per bfly, 4  bfys(N/16)       */
/*   2 (SC) * 3 (TWF per BFLY) * (16+ 2*(4 bfys * 2)) + 8 PAD = 200          */
/*  In the second stage the bfys are twice replicated for parallel processing*/
/*---------------------------------------------------------------------------*/

short *cs1[3]  = {&SC_vector[2*0],  &SC_vector[2*3*16],         0x0};
short *cs2[3]  = {&SC_vector[2*8],  &SC_vector[2*3*16 + 2*8],   0x0};
short *cs3[3]  = {&SC_vector[2*16], &SC_vector[2*3*16 + 2*16],  0x0};

/*---------------------------------------------------------------------------*/
/* In the Parameters for 1st stage, we perform 1 set of 16 4-point          */
/* FFT's. Since the vector core has two operation slots, each of             */
/* which works on eight data points, we work on 8 radix-4 bflies             */
/* in parallel. Therefore we only need one level of loop, which              */
/* will iterate 16/8 = 2 times, so loop counter is set up to be            */
/* 2 times.                                                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* In the first stage of the radix-4 FFT, we point the data at inp.          */
/* offsets of 0, N/4, N/2 and 3 N/4 which for N = 64 maps to                 */
/* 0, 64, 128, 192 in byte offsets, as each offset is 4 bytes                */
/* corresponding to 2 bytes real, 2 bytes imaginary. After we                */
/* calculate the radix-4 butterfly we write the output at the                */
/* same locations. Since we load 8 complex inputs from each of               */
/* the legs of the butterfly, input increment is 32 bytes. We                */
/* maintain twiddle factors in sets of 8, for the three inputs,              */
/* (2*pi*n*k)/N, (4*pi*n*k/N) and (6*pi*N*k)/N, so we jump by 96             */
/* bytes. Since we only have one level of loop, outer level loop             */
/* increments are set to 0. The shift by 15 as twiddle factors               */
/* are in Q15 is done by the store out. This is also why twiddle             */
/* factors for the three legs are set to be 8 complex values                 */
/* apart at 0, 32 and 64.                                                    */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* Parameters for 2nd stage  4 sets of 4 4-point FFT's.                      */
/* Note SIMD width is 8, but now we have only 4 radix-4 FFt's, so            */
/* we do two sets, replicating the twiddle factor. Therefore inner           */
/* loop iterates twice, outer loop iterates 1 time to accomplish             */
/* 16 radix-4 butterflies. We can only load 8 points apart, so               */
/* we set the 4 legs of the butterfly to point to offsets 0, 8,              */
/* 16 and 32, which correspond to byte offsets of 0, 32, 64 and              */
/* 128. We offset twiddle by the amount of 3*(16). The                       */
/* data pointer increments by 128 for inner loop iteration,                  */
/* as we load consecutive           										 */
/* points. Once again round out by 15 is done through the store              */
/* unit. Although in this iteration we need data at offsets 0,               */
/* 4, 8 and 12 we will have to prepare this in register file.                */
/*---------------------------------------------------------------------------*/    

/*---------------------------------------------------------------------------*/    
/* Parameters for 3rd stage   4 sets of 4 4-point FFT's. Note                */
/* SIMD width is 8, but now we have only 4 radix-4 FFt's, so do              */
/* two sets in parallel, we do not need twiddle factor. Here we              */
/* merely load, re-arrange data as required and do radix-4                   */
/* butterflies without any multiply. So, we only have inner loop             */
/* where we increment by 128. So both twiddle factor increments are 0.       */                                                
/*---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/    
/* In this implementation, we do a seperate digit reversal stage.           */
/* We have a table of 16 entries to do this. So inner loop                  */
/* iterates 2 times = 16/8, and outer loop reuses this                      */
/* table 4 times. For every iteration of the inner loop, we                 */
/* jump by one radix 4, ie 0, 32, 64, and so on, which in a byte            */
/* index is 0, 128, 256 and so on. We then rewind by -128*31 and            */
/* jump to the next leg of the butterfly by adding 32. For the              */
/* digit reversal table, we jump by 8 entries, being hw 16 bytes            */
/* rewinding by -16 x 31, to achieve re-use.                                */
/*                                                                          */
/* This is coded as an explicit loop, so these pointer increments are       */
/* not carried as part of the array.                                        */
/*--------------------------------------------------------------------------*/ 
 
uint16 bfys_per_grp[3] = {2, 2,   2};//These are inner loop iterations
uint16 grps[3]         = {1, 1,   1};//outer loop iterations
uint16 pinc3[3]        = {0, 256,   0};//Increment for the index of the input array for outer loop 
uint16 ptnc3[3]        = {0, 0, 0};//For twiddle factors outer loop increments. Zero because twiddle factors are reused
uint16 pinc4[3]        = {32, 128,  128};//Increments within a group between different inner loop iterations for input.
uint16 ptnc4[3]        = {96, 96,   0};//pointer increments for twiddle factors. 96 Bytes always


/*--------------------------------------------------------------------------*/ 
/*  Top level FFT function, which leverages repeat loops for first stage    */
/*  It uses a regular loop for 2nd and 3rd stage, with pointer increments   */
/*  passed as arguments. It then does a seperate digit reversal loop.       */
/*  This is a good example, where RISC core queues up back to back loops    */
/*  for execution on the vector core.                                       */
/*--------------------------------------------------------------------------*/ 

void vcop_fft_64_16x16t_cn (short in[128], short SC[200], unsigned short digit_rev[16], short out[128])
{

	vcop_fft_64_16x16t_stage_1
    (
        pxi0, 
        pxi1, 
        pxi2, 
        pxi3, 
        cs1, 
        cs2, 
        cs3, 
        bfys_per_grp,
        grps,
        passes_rpt,
        pinc3,
        pinc4,
        ptnc3,
        ptnc4
     );

    vcop_fft_64_16x16t_stage2
    (
        pxi0[1],
        pxi1[1],
        pxi2[1],
        pxi3[1],
        cs1[1],
        cs2[1],
        cs3[1],
        bfys_per_grp[1],
        grps[1],
        pinc3[1],
        pinc4[1],
        ptnc3[1],
        ptnc4[1]
     );

    vcop_fft_64_16x16t_stage3
    (
        pxi0[2],
        pxi1[2],
        pxi2[2],
        pxi3[2],
        bfys_per_grp[2],
        grps[2],
        pinc3[2],
        pinc4[2]
     );

     vcop_fft_digit_rev_64
     (
         (int *) (&in[0]),   
         digit_rev,
         (int *) (&out[0])
     );
}

/*-------------------------------------------------------------------------- */
/*  Call FFT function, where input data is in "in", twiddle factor array     */
/*  is in "SC_vector", digit reversal array is in "digit_rev" and            */
/*  output array is in "out".                                                */
/*-------------------------------------------------------------------------- */

int main()
{
    /*-----------------------------------------------------------------------*/
    /*  Call FFT routine here.                                               */
    /*-----------------------------------------------------------------------*/

    vcop_fft_64_16x16t_cn(in, SC_vector, digit_rev, out);

    /*-----------------------------------------------------------------------*/
    /*  Compare output "out" with expected output after digit reversal.      */
    /*-----------------------------------------------------------------------*/
    if (memcmp (out, EOut, sizeof (EOut)))
        printf ("Fail \n");
        else
        printf ("Pass \n");

}

/*-------------------------------------------------------------------------- */
/* End of file: vcop_fft_1024_16x16t_tb.c                                    */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */

