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

/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif
/* ------------------------------------------------------------------------- */
/*  Register mappings for manual register allocations.                       */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* #defines for typecasting unsigned short as unsigned short.                */
/* ------------------------------------------------------------------------- */

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#if (!VCOP_HOST_EMULATION)
#define ENABLE_MANUAL_REGISTER_ALLOCATION (0)
#else
#define ENABLE_MANUAL_REGISTER_ALLOCATION (0)
#endif

#if (ENABLE_MANUAL_REGISTER_ALLOCATION)
    /* Manual Register Allocation for optimal performance */
    #define VScatterOffset  V0
    #define VCond V1
    #define VMin V2
    #define VMax V4

    #define VInterim1 V3
    #define VInterim2 V5
    #define VInterim3 V6
    #define VInterim4 V7



    #define VX0 V8
    #define VY0 V9
    #define VX1 V10
    #define VY1 V11
    #define VX2 V12
    #define VY2 V13
    #define VX3 V14
    #define VY3 V15

    #define VX0_plus_X2 V8
    #define VX0_minus_X2 V12

    #define VX1_plus_X3 V10
    #define VX1_minus_X3 V14

    #define VY0_plus_Y2 V9
    #define VY0_minus_Y2 V13

    #define VY1_plus_Y3 V11
    #define VY1_minus_Y3 V15

    #define VOutX0 V8
    #define VOutY0 V9
    #define VOutX1 V12
    #define VOutY1 V14
    #define VOutX2 V10
    #define VOutY2 V11
    #define VOutX3 V15
    #define VOutY3 V13
#endif


#define MAX_OUTPUT_VALUE (16383)
#define MIN_OUTPUT_VALUE (-16384)

#define VCOP_FFT_512_NPOINTS (512U)
#define VCOP_FFT_512_STAGE1_NUMBF_PER_GRP (128)
#define VCOP_FFT_512_STAGE1_NUMPT_PER_GRP (VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE1_NUM_GRPS      (1)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

#define pStage1OutX pOutput
#define pStage1OutY (pOutput + VCOP_FFT_512_NPOINTS * sizeof(*pOutput))

void vcop_fft_512_32inter_stage_1
(
    __vptr_int16  pInput,
    __vptr_int32  pScratchWBUF,
    __vptr_uint16  pScratchWBUF16_lo,
    __vptr_int16  pScratchWBUF16_hi,
    __vptr_int32  pScratchH,
    __vptr_uint16  pScratchH16_lo,
    __vptr_int16  pScratchH16_hi,
    __vptr_int32  pOutput,
    __vptr_int16  pTwiddleFactor,
    unsigned short    pitch,
    unsigned short    numOfLines)
{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
  __vector VScatterOffset;
  __vector VInterim1, VInterim2, VInterim3, VInterim4;

  __vector VX0, VY0, VX1, VY1;
  __vector VX2, VY2, VX3, VY3;

  __vector VX0_plus_X2;
  __vector VX1_plus_X3;
  __vector VY0_plus_Y2;
  __vector VY1_plus_Y3;
  __vector VX0_minus_X2;
  __vector VX1_minus_X3;
  __vector VY0_minus_Y2;
  __vector VY1_minus_Y3;

  __vector VOutX0, VOutY0, VOutX1, VOutY1;
  __vector VOutX2, VOutY2, VOutX3, VOutY3;
#endif

  __agen addr0;
  addr0 = 0;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE1_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE1_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        __agen  Addr_in = lineIdx * pitch +
                I3 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pInput) * 2 * VCOP_SIMD_WIDTH;

        __agen  Addr_out = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2 +
                I3 * sizeof(*pOutput) * 1 * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pOutput) * 1 * VCOP_SIMD_WIDTH;

        __agen  Addr_outWBUF = lineIdx * pitch +
                            I3 * sizeof(*pScratchWBUF) * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                            I4 * sizeof(*pScratchWBUF) * VCOP_SIMD_WIDTH;

        __agen  Addr_outH = lineIdx * sizeof(*pScratchH) * VCOP_FFT_512_NPOINTS +
                            I3 * sizeof(*pScratchH) * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                            I4 * sizeof(*pScratchH) * VCOP_SIMD_WIDTH;

        /*-----------------------------------------------------------*/
        /*  Read the complex input and de-interleave into real and   */
        /*  imaginary parts. Note we will be working on "VCOP_SIMD_WIDTH"  */
        /*  radix-4 butterflies or 8 radix-4 butterflies  in parallel. */
        /*  Leg0 = x0 + j y0                                                                   */
        /*  Leg1 = x1 + j y1                                                                   */
        /*  Leg2 = x2 + j y2                                                                   */
        /*  Leg3 = x3 + j y3                                                                   */
        /* outLeg0 = (x0 + x2) + (x1 + x3)   + j ( (y0 + y2) + ( y1 + y3))      */
        /* outLeg1 = (x0 - x2) + (y1 - y3)   + j ( (y0 - y2) - ( x1 - x3))      */
        /* outLeg2 = (x0 + x2) - (x1 + x3)   + j ( (y0 + y2) - ( y1 + y3))     */
        /* outLeg3 = (x0 - x2) - (y1 - y3)   + j ( (y0 - y2) + ( x1 - x3))      */
        /*  Convention here is to denote the four input legs of the              */
        /*  butterfly as input 0, 1, 2, 3                            */
        /*-----------------------------------------------------------*/

        (VX0, VY0) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 0 )[Addr_in].deinterleave();
        (VX1, VY1) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 1 )[Addr_in].deinterleave();
        (VX2, VY2) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 2 )[Addr_in].deinterleave();
        (VX3, VY3) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 3 )[Addr_in].deinterleave();

        (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
        (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
        (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
        (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


        (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
        (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
        (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
        (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

        (pStage1OutX + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 1 * 0 )[Addr_out].npt() = VOutX0.saturate();
        (pStage1OutY + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 1 * 0 )[Addr_out].npt() = VOutY0.saturate();

        (pScratchWBUF + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 1 )[Addr_outWBUF].npt() = VOutX1.saturate();
        (pScratchH + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 1 )[Addr_outH].npt() = VOutY1.saturate();

        (pScratchWBUF + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 2 )[Addr_outWBUF].npt() = VOutX2.saturate();
        (pScratchH + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 2 )[Addr_outH].npt() = VOutY2.saturate();

        (pScratchWBUF + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 3 )[Addr_outWBUF].npt() = VOutX3.saturate();
        (pScratchH + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 3 )[Addr_outH].npt() = VOutY3.saturate();
      }
    }
  }

  __vector VInX, VInY, VInX_lo, VInY_lo, VInX_hi, VInY_hi, VK15;
  __vector VCos, VSin;
  __vector VOutX, VOutY;

  VK15= 15;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE1_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE1_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        for (int twIdx = 0; twIdx < 3; twIdx++)
        {
          __agen  Addr_inWBUF = lineIdx * pitch +
                I3 * sizeof(*pScratchWBUF) * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pScratchWBUF) * VCOP_SIMD_WIDTH +
                twIdx * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF);

          __agen  Addr_inH = lineIdx * sizeof(*pScratchH) * VCOP_FFT_512_NPOINTS +
                I3 * sizeof(*pScratchH) * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pScratchH) * VCOP_SIMD_WIDTH +
                twIdx * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH);


          __agen  Addr_out = lineIdx * sizeof(*pOutput) * VCOP_FFT_512_NPOINTS * 2 +
                            I3 * sizeof(*pOutput) * 1 * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                            I4 * sizeof(*pOutput) * 1 * VCOP_SIMD_WIDTH +
                            twIdx * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 1;

          __agen  Addr_tw = I4 * 3 * sizeof(*pTwiddleFactor) * 2 *  VCOP_SIMD_WIDTH +
                            twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;

          /* here we will multiple the previous output with twiddle factor which is written as   */
          /* cos(theta) - j sin(theta)                                                                            */
          /* if input is x + j y then output is                                                                   */
          /* (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs)                                                */

          (VSin, VCos) =  (pTwiddleFactor + VCOP_SIMD_WIDTH * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();

          VInX_lo= (pScratchWBUF16_lo + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 1 )[Addr_inWBUF].ds2();
          VInX_hi= (pScratchWBUF16_hi + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 1 )[Addr_inWBUF].ds2();
          VInY_lo= (pScratchH16_lo + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 1)[Addr_inH].ds2();
          VInY_hi= (pScratchH16_hi + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 1)[Addr_inH].ds2();

          VOutX = (VInX_lo * VCos);
          VOutY = (VInY_lo * VCos);

          VOutX += (VInY_lo * VSin);
          VOutY -= (VInX_lo * VSin);

          VOutX = round(VOutX, VK15);
          VOutY = round(VOutY, VK15);

          VOutX+= (VInX_hi * VCos)<<1;
          VOutY+= (VInY_hi * VCos)<<1;

          VOutX+= (VInY_hi * VSin)<<1;
          VOutY-= (VInX_hi * VSin)<<1;

          (pStage1OutX + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 1 * 1 )[Addr_out].npt() = VOutX;
          (pStage1OutY + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 1 * 1 )[Addr_out].npt() = VOutY;

        }
      }
    }
  }
}

#define VCOP_FFT_512_STAGE2_NUMBF_PER_GRP (32)
#define VCOP_FFT_512_STAGE2_NUMPT_PER_GRP (VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * VCOP_FFT_512_STAGE2_NUM_GRPS)
#define VCOP_FFT_512_STAGE2_NUM_GRPS      (4)

#define pStage2InX pInput
#define pStage2InY (pInput + VCOP_FFT_512_NPOINTS * sizeof(*pInput))
#define pStage2OutX pOutput
#define pStage2OutY (pOutput + VCOP_FFT_512_NPOINTS * sizeof(*pOutput))

void vcop_fft_512_32inter_stage_2
(
    __vptr_int32  pInput,
    __vptr_int32  pScratch1,
    __vptr_uint16 pScratch1_16_lo,
    __vptr_int16  pScratch1_16_hi,
    __vptr_int32  pScratch2,
    __vptr_uint16 pScratch2_16_lo,
    __vptr_int16  pScratch2_16_hi,
    __vptr_int32  pOutput,
    __vptr_int16  pTwiddleFactor,
    unsigned short    pitch,
    unsigned short    numOfLines)
{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
  __vector VX0, VY0, VX1, VY1;
  __vector VX2, VY2, VX3, VY3;

  __vector VX0_plus_X2;
  __vector VX1_plus_X3;
  __vector VY0_plus_Y2;
  __vector VY1_plus_Y3;
  __vector VX0_minus_X2;
  __vector VX1_minus_X3;
  __vector VY0_minus_Y2;
  __vector VY1_minus_Y3;

  __vector VOutX0, VOutY0, VOutX1, VOutY1;
  __vector VOutX2, VOutY2, VOutX3, VOutY3;
#endif

  __agen addr0;
  addr0 = 0;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE2_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE2_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        __agen  Addr_in = lineIdx * pitch +
                I3 * sizeof(*pInput) * 1 * VCOP_FFT_512_STAGE2_NUMPT_PER_GRP  +
                I4 * sizeof(*pInput) * 1 * VCOP_SIMD_WIDTH;

        __agen  Addr_out = lineIdx * sizeof(*pScratch1) * VCOP_FFT_512_NPOINTS +
                            I3 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE2_NUMPT_PER_GRP  +
                            I4 * sizeof(*pScratch1) * VCOP_SIMD_WIDTH;


        /*-----------------------------------------------------------*/
        /*  Read the complex input and de-interleave into real and   */
        /*  imaginary parts. Note we will be working on "VCOP_SIMD_WIDTH"  */
        /*  radix-4 butterflies or 8 radix-4 butterflies  in parallel. */
        /*  Leg0 = x0 + j y0                                                                   */
        /*  Leg1 = x1 + j y1                                                                   */
        /*  Leg2 = x2 + j y2                                                                   */
        /*  Leg3 = x3 + j y3                                                                   */
        /* outLeg0 = (x0 + x2) + (x1 + x3)   + j ( (y0 + y2) + ( y1 + y3))      */
        /* outLeg1 = (x0 - x2) + (y1 - y3)   + j ( (y0 - y2) - ( x1 - x3))      */
        /* outLeg2 = (x0 + x2) - (x1 + x3)   + j ( (y0 + y2) - ( y1 + y3))     */
        /* outLeg3 = (x0 - x2) - (y1 - y3)   + j ( (y0 - y2) + ( x1 - x3))      */
        /*  Convention here is to denote the four input legs of the              */
        /*  butterfly as input 0, 1, 2, 3                            */
        /*-----------------------------------------------------------*/

        VX0= (pStage2InX + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
        VY0= (pStage2InY + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
        VX1= (pStage2InX + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
        VY1= (pStage2InY + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
        VX2= (pStage2InX + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
        VY2= (pStage2InY + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
        VX3= (pStage2InX + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 3 )[Addr_in].npt();
        VY3= (pStage2InY + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 3 )[Addr_in].npt();

        (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
        (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
        (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
        (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


        (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
        (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
        (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
        (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

        (pScratch1 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 0 )[Addr_out].npt() = VOutX0.saturate();
        (pScratch2 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 0 )[Addr_out].npt() = VOutY0.saturate();

        (pScratch1 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 1 )[Addr_out].npt() = VOutX1.saturate();
        (pScratch2 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 1 )[Addr_out].npt() = VOutY1.saturate();

        (pScratch1 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 2 )[Addr_out].npt() = VOutX2.saturate();
        (pScratch2 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 2 )[Addr_out].npt() = VOutY2.saturate();

        (pScratch1 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 3 )[Addr_out].npt() = VOutX3.saturate();
        (pScratch2 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 3 )[Addr_out].npt() = VOutY3.saturate();
      }
    }
  }

  __vector VInX, VInY, VInX_lo, VInY_lo, VInX_hi, VInY_hi, VK15;
  __vector VCos, VSin;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE2_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE2_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        __agen  Addr_in = lineIdx * sizeof(*pScratch1) * VCOP_FFT_512_NPOINTS +
              I3 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4  +
              I4 * sizeof(*pScratch1) * VCOP_SIMD_WIDTH;

        __agen  Addr_out = lineIdx * sizeof(*pOutput) * VCOP_FFT_512_NPOINTS * 2 +
                          I3 * sizeof(*pOutput) * 1 * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4  +
                          I4 * sizeof(*pOutput) * 1 * VCOP_SIMD_WIDTH;

        /* here we will multiple the previous output with twiddle factor which is written as   */
        /* cos(theta) - j sin(theta)                                                                            */
        /* if input is x + j y then output is                                                                   */
        /* (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs)                                                */

        VInX = (pScratch1 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 0 )[Addr_in].npt();
        VInY = (pScratch2 + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 0)[Addr_in].npt();

        //(pOutput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 0 )[Addr_out].interleave() = (VInX, VInY);
        (pStage2OutX + sizeof(*pOutput) * 1 * 4 * 0)[Addr_out].npt() = VInX;
        (pStage2OutY + sizeof(*pOutput) * 1 * 4 * 0)[Addr_out].npt() = VInY;
      }
    }
  }

  VK15= 15;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE2_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE2_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        for (int twIdx = 0; twIdx < 3; twIdx++)
        {
          __agen  Addr_in = lineIdx * sizeof(*pScratch1) * VCOP_FFT_512_NPOINTS +
                I3 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pScratch1) * VCOP_SIMD_WIDTH +
                twIdx * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1);

          __agen  Addr_out = lineIdx * sizeof(*pOutput) * VCOP_FFT_512_NPOINTS * 2 +
                            I3 * sizeof(*pOutput) * 1 * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4  +
                            I4 * sizeof(*pOutput) * 1 * VCOP_SIMD_WIDTH +
                            twIdx * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 1;

          __agen  Addr_tw = I4 * 3 * sizeof(*pTwiddleFactor) * 2 *  VCOP_SIMD_WIDTH +
                            twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;

          /* here we will multiple the previous output with twiddle factor which is written as   */
          /* cos(theta) - j sin(theta)                                                                            */
          /* if input is x + j y then output is                                                                   */
          /* (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs)                                                */

          (VSin, VCos) =  (pTwiddleFactor + VCOP_SIMD_WIDTH * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();

          VInX_lo= (pScratch1_16_lo + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 1)[Addr_in].ds2();
          VInX_hi= (pScratch1_16_hi + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 1)[Addr_in].ds2();
          VInY_lo= (pScratch2_16_lo + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 1)[Addr_in].ds2();
          VInY_hi= (pScratch2_16_hi + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 1)[Addr_in].ds2();

          VOutX = (VInX_lo * VCos);
          VOutY = (VInY_lo * VCos);

          VOutX += (VInY_lo * VSin);
          VOutY -= (VInX_lo * VSin);

          VOutX = round(VOutX, VK15);
          VOutY = round(VOutY, VK15);

          VOutX+= (VInX_hi * VCos)<<1;
          VOutY+= (VInY_hi * VCos)<<1;

          VOutX+= (VInY_hi * VSin)<<1;
          VOutY-= (VInX_hi * VSin)<<1;

          (pStage2OutX + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 1 * 1)[Addr_out].npt() = VOutX;
          (pStage2OutY + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 1 * 1)[Addr_out].npt() = VOutY;

        }
      }
    }
  }

}

/*---------------------------------------------------------------------------*/
/* In stage 3, operations are similar to previous stages of 1..2. Even       */
/* though repeat loop can be leveraged for this stage as shown in ver1       */
/* and ver2, we break out, so that we can make the task of digit reversal    */
/* for free by purposefully writing results within a vector word further     */
/* apart, by using transpisition, as we will need to work on them in         */
/* later iterations.                                                         */
/*---------------------------------------------------------------------------*/

#define VCOP_FFT_512_STAGE3_NUMBF_PER_GRP (8)
#define VCOP_FFT_512_STAGE3_NUMPT_PER_GRP (VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE3_NUM_GRPS      (16)
#define VCOP_FFT_512_TRANSPOSE_STRIDE     ( 65 * sizeof(*pOutput))
#define pStage3InX pInput
#define pStage3InY (pInput + VCOP_FFT_512_NPOINTS*sizeof(*pInput))
#define pStage3OutX pOutput
#define pStage3OutY (pOutput + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * VCOP_FFT_512_TRANSPOSE_STRIDE)

void vcop_fft_512_32inter_stage_3
(

    __vptr_int32      pInput,
    __vptr_int32  pScratch1,
    __vptr_uint16 pScratch1_16_lo,
    __vptr_int16  pScratch1_16_hi,
    __vptr_int32  pScratch2,
    __vptr_uint16 pScratch2_16_lo,
    __vptr_int16  pScratch2_16_hi,
    __vptr_int32      pOutput,
    __vptr_int16      pTwiddleFactor,
    __vptr_uint16     pScatterOffset,
    unsigned short pitch,
    unsigned short numOfLines
)
{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
    __vector VScatterOffset;
    __vector VX0, VY0, VX1, VY1;
    __vector VX2, VY2, VX3, VY3;

    __vector VX0_plus_X2;
    __vector VX1_plus_X3;
    __vector VY0_plus_Y2;
    __vector VY1_plus_Y3;
    __vector VX0_minus_X2;
    __vector VX1_minus_X3;
    __vector VY0_minus_Y2;
    __vector VY1_minus_Y3;

    __vector VOutX0, VOutY0, VOutX1, VOutY1;
    __vector VOutX2, VOutY2, VOutX3, VOutY3;
#endif

   __agen addr0;
   addr0 = 0;

   for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
   {
       for (int I3 = 0; I3 < 4; I3++)/* Process in two loops each of 4 groups */
       {
           for (int I4 = 0; I4 < 4; I4++)/* start with  Group 0,1,2,3,*/
           {
             __agen  Addr_in = lineIdx * pitch +
                               I3 * 4 * sizeof(*pInput) * 1 * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP +
                               I4 * 1 * sizeof(*pInput) * 1 * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP;

             __agen  Addr_out = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1) +
                               I3 * 4 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP +
                               I4 * 1 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP;

              /*-----------------------------------------------------------*/
              /*  Read the complex input and de-interleave into real and   */
              /*  imaginary parts. Note we will be working on "VCOP_SIMD_WIDTH"  */
              /*  radix-4 butterflies or 8 radix-4 butterflies  in parallel. */
              /*  Leg0 = x0 + j y0                                                                   */
              /*  Leg1 = x1 + j y1                                                                   */
              /*  Leg2 = x2 + j y2                                                                   */
              /*  Leg3 = x3 + j y3                                                                   */
              /* outLeg0 = (x0 + x2) + (x1 + x3)   + j ( (y0 + y2) + ( y1 + y3))      */
              /* outLeg1 = (x0 - x2) + (y1 - y3)   + j ( (y0 - y2) - ( x1 - x3))      */
              /* outLeg2 = (x0 + x2) - (x1 + x3)   + j ( (y0 + y2) - ( y1 + y3))     */
              /* outLeg3 = (x0 - x2) - (y1 - y3)   + j ( (y0 - y2) + ( x1 - x3))      */
              /*  Convention here is to denote the four input legs of the              */
              /*  butterfly as input 0, 1, 2, 3                            */
              /*-----------------------------------------------------------*/

              VX0= (pStage3InX + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
              VY0= (pStage3InY + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
              VX1= (pStage3InX + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
              VY1= (pStage3InY + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
              VX2= (pStage3InX + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
              VY2= (pStage3InY + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
              VX3= (pStage3InX + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 3 )[Addr_in].npt();
              VY3= (pStage3InY + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 1 * 3 )[Addr_in].npt();

              (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
              (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
              (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
              (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7

              (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
              (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
              (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
              (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

              (pScratch1 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1) * 0 )[Addr_out].npt() = VOutX0.saturate();
              (pScratch2 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2) * 0 )[Addr_out].npt() = VOutY0.saturate();

              (pScratch1 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1) * 1 )[Addr_out].npt() = VOutX1.saturate();
              (pScratch2 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2) * 1 )[Addr_out].npt() = VOutY1.saturate();

              (pScratch1 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1) * 2 )[Addr_out].npt() = VOutX2.saturate();
              (pScratch2 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2) * 2 )[Addr_out].npt() = VOutY2.saturate();

              (pScratch1 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1) * 3 )[Addr_out].npt() = VOutX3.saturate();
              (pScratch2 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2) * 3 )[Addr_out].npt() = VOutY3.saturate();
           }
       }
   }

   __vector VInX, VInY, VInX_lo, VInY_lo, VInX_hi, VInY_hi, VK15;
   __vector VCos, VSin;
   __vector VOutX, VOutY;

   VScatterOffset = pScatterOffset[addr0].npt();

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < 4; I3++)/* Process in two loops each of 4 groups */
    {
       for (int I4 = 0; I4 < 4; I4++)/* start with  Group 0,1,2,3,*/
       {
         __agen  Addr_in = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1) +
                           I3 * 4 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP +
                           I4 * 1 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP;

         __agen  Addr_ou = lineIdx * VCOP_FFT_512_TRANSPOSE_STRIDE * VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * 2 +
                           I3 * 1 * sizeof(*pOutput) * 1  +
                           I4 * 4 * sizeof(*pOutput) * 1;

          /* here we will multiple the previous output with twiddle factor which is written as   */
          /* cos(theta) - j sin(theta)                                                                            */
          /* if input is x + j y then output is                                                                   */
          /* (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs)                                                */

         VInX =  (pScratch1 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2) * 0)[Addr_in].npt();
         VInY =  (pScratch2 + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2) * 0)[Addr_in].npt();

         pStage3OutX[Addr_ou].p_scatter(VScatterOffset) = VInX;
         pStage3OutY[Addr_ou].p_scatter(VScatterOffset) = VInY;
      }
     }
   }

  VK15= 15;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < 4; I3++)/* Process in two loops each of 4 groups */
    {
       for (int I4 = 0; I4 < 4; I4++)/* start with  Group 0,1,2,3,*/
       {
         for (int twIdx = 0; twIdx < 3; twIdx++)
         {
           __agen  Addr_in = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1) +
                             I3 * 4 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP +
                             I4 * 1 * sizeof(*pScratch1) * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP +
                             twIdx * VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1);

           __agen  Addr_ou = lineIdx * VCOP_FFT_512_TRANSPOSE_STRIDE * VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * 2 +
                             I3 * 1 * sizeof(*pOutput) * 1  +
                             I4 * 4 * sizeof(*pOutput) * 1 +
                             twIdx * VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 1;

           __agen  Addr_tw = twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;

            /* here we will multiple the previous output with twiddle factor which is written as   */
            /* cos(theta) - j sin(theta)                                                                            */
            /* if input is x + j y then output is                                                                   */
            /* (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs)                                                */


           (VSin, VCos) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();

          VInX_lo= (pScratch1_16_lo + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1))[Addr_in].ds2();
          VInX_hi= (pScratch1_16_hi + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch1))[Addr_in].ds2();
          VInY_lo= (pScratch2_16_lo + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2))[Addr_in].ds2();
          VInY_hi= (pScratch2_16_hi + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pScratch2))[Addr_in].ds2();

          VOutX = (VInX_lo * VCos);
          VOutY = (VInY_lo * VCos);

          VOutX += (VInY_lo * VSin);
          VOutY -= (VInX_lo * VSin);

          VOutX = round(VOutX, VK15);
          VOutY = round(VOutY, VK15);

          VOutX+= (VInX_hi * VCos)<<1;
          VOutY+= (VInY_hi * VCos)<<1;

          VOutX+= (VInY_hi * VSin)<<1;
          VOutY-= (VInX_hi * VSin)<<1;

          (pStage3OutX + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 1 )[Addr_ou].p_scatter(VScatterOffset) = VOutX;
          (pStage3OutY + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 1 )[Addr_ou].p_scatter(VScatterOffset) = VOutY;

          }
      }
     }
   }
}


/*---------------------------------------------------------------------------*/
/* In stage 4, operations are similar to previous stages of 1..2. Even       */
/*---------------------------------------------------------------------------*/

#define VCOP_FFT_512_STAGE4_NUMBF_PER_GRP (2)
#define VCOP_FFT_512_STAGE4_NUMPT_PER_GRP (VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE4_NUM_GRPS      (64)
#define VCOP_FFT_512_STAGE4_OUTPUT_STRIDE (VCOP_FFT_512_STAGE4_NUM_GRPS * sizeof(*pOutput))

#define pStage4InX pInput
#define pStage4InY (pInput + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * VCOP_FFT_512_TRANSPOSE_STRIDE)
#define pStage4OutX pOutput
#define pStage4OutY (pOutput + VCOP_FFT_512_NPOINTS * sizeof(*pOutput))

void vcop_fft_512_32inter_stage_4
(
  __vptr_int32  pInput,
  __vptr_int32  pScratch1,
  __vptr_uint16 pScratch1_16_lo,
  __vptr_int16  pScratch1_16_hi,
  __vptr_int32  pScratch2,
  __vptr_uint16 pScratch2_16_lo,
  __vptr_int16  pScratch2_16_hi,
  __vptr_int32      pOutput,
  __vptr_int16      pTwiddleFactor,
  unsigned short    numOfLines
)

{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
  __vector VX0, VY0, VX1, VY1;
  __vector VX2, VY2, VX3, VY3;

  __vector VX0_plus_X2;
  __vector VX1_plus_X3;
  __vector VY0_plus_Y2;
  __vector VY1_plus_Y3;
  __vector VX0_minus_X2;
  __vector VX1_minus_X3;
  __vector VY0_minus_Y2;
  __vector VY1_minus_Y3;

  __vector VOutX0, VOutY0, VOutX1, VOutY1;
  __vector VOutX2, VOutY2, VOutX3, VOutY3;
#endif

  __agen addr0;
  addr0 = 0;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I2 = 0; I2 < VCOP_FFT_512_STAGE4_NUM_GRPS/ VCOP_SIMD_WIDTH; I2++)
    {
      for (int I3 = 0; I3 < VCOP_FFT_512_STAGE4_NUMBF_PER_GRP; I3++)
      {
        __agen  Addr_in = lineIdx * VCOP_FFT_512_TRANSPOSE_STRIDE * VCOP_FFT_512_STAGE4_NUMPT_PER_GRP * 2 +
                          I2 * VCOP_SIMD_WIDTH * sizeof(*pInput) * 1 +
                          I3 * VCOP_FFT_512_TRANSPOSE_STRIDE;

        __agen  Addr_out = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1)+
                          I2 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                          I3 * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE;

        /*-----------------------------------------------------------*/
        /*  Read the complex input and de-interleave into real and   */
        /*  imaginary parts. Note we will be working on "VCOP_SIMD_WIDTH"  */
        /*  radix-4 butterflies or 8 radix-4 butterflies  in parallel. */
        /*  Leg0 = x0 + j y0                                                                   */
        /*  Leg1 = x1 + j y1                                                                   */
        /*  Leg2 = x2 + j y2                                                                   */
        /*  Leg3 = x3 + j y3                                                                   */
        /* outLeg0 = (x0 + x2) + (x1 + x3)   + j ( (y0 + y2) + ( y1 + y3))      */
        /* outLeg1 = (x0 - x2) + (y1 - y3)   + j ( (y0 - y2) - ( x1 - x3))      */
        /* outLeg2 = (x0 + x2) - (x1 + x3)   + j ( (y0 + y2) - ( y1 + y3))     */
        /* outLeg3 = (x0 - x2) - (y1 - y3)   + j ( (y0 - y2) + ( x1 - x3))      */
        /*  Convention here is to denote the four input legs of the              */
        /*  butterfly as input 0, 1, 2, 3                            */
        /*-----------------------------------------------------------*/
        VX0=  (pStage4InX + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 0 )[Addr_in].npt();
        VY0=  (pStage4InY + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 0 )[Addr_in].npt();
        VX1=  (pStage4InX + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 1 )[Addr_in].npt();
        VY1=  (pStage4InY + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 1 )[Addr_in].npt();
        VX2=  (pStage4InX + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 2 )[Addr_in].npt();
        VY2=  (pStage4InY + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 2 )[Addr_in].npt();
        VX3=  (pStage4InX + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 3 )[Addr_in].npt();
        VY3=  (pStage4InY + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                    VCOP_FFT_512_TRANSPOSE_STRIDE * 3 )[Addr_in].npt();

        (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
        (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
        (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
        (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


        (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
        (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
        (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
        (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

       (pScratch1 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                         VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 0 )[Addr_out].npt() = VOutX0.saturate();
       (pScratch2 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 0 )[Addr_out].npt() = VOutY0.saturate();

       (pScratch1 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 1)[Addr_out].npt() = VOutX1.saturate();
       (pScratch2 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 1)[Addr_out].npt() = VOutY1.saturate();

       (pScratch1 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 2)[Addr_out].npt() = VOutX2.saturate();
       (pScratch2 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 2 )[Addr_out].npt() = VOutY2.saturate();

       (pScratch1 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 3)[Addr_out].npt() = VOutX3.saturate();
       (pScratch2 + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                       VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 3)[Addr_out].npt() = VOutY3.saturate();

      }
    }
  }

  __vector VInX, VInY, VInX_lo, VInY_lo, VInX_hi, VInY_hi, VK15;
  __vector VCos, VSin;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE4_NUM_GRPS/ VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE4_NUMBF_PER_GRP; I4++)
      {
       __agen  Addr_in = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1) +
                         I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                         I4 * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE;

       __agen  Addr_ou = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2+
                         I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 1 +
                         I4 * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE;

        VInX =  (pScratch1 +  VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                               VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 0)[Addr_in].npt();
        VInY =  (pScratch2 +  VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
                               VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 0)[Addr_in].npt();

        (pStage4OutX + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
        VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 1 * 0 )[Addr_ou].npt() = VInX;
        (pStage4OutY + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE *
        VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 1 * 0 )[Addr_ou].npt() = VInY;
      }
    }
  }

  VK15= 15;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_512_STAGE4_NUM_GRPS/ VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_512_STAGE4_NUMBF_PER_GRP; I4++)
      {
        for (int twIdx = 0; twIdx < 3; twIdx++)
        {
         __agen  Addr_in = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1) +
                           I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                           I4 * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE +
                           twIdx * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP;

         __agen  Addr_ou = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2+
                           I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) +
                           I4 * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE +
                           twIdx * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP;

         __agen  Addr_tw = I4 * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH * 3 +
                           twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;

          (VSin, VCos) =  (pTwiddleFactor)[Addr_tw].deinterleave();

          VInX_lo= (pScratch1_16_lo + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP)[Addr_in].ds2();
          VInX_hi= (pScratch1_16_hi + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP)[Addr_in].ds2();
          VInY_lo= (pScratch2_16_lo + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP)[Addr_in].ds2();
          VInY_hi= (pScratch2_16_hi + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP)[Addr_in].ds2();

          VOutX = (VInX_lo * VCos);
          VOutY = (VInY_lo * VCos);

          VOutX += (VInY_lo * VSin);
          VOutY -= (VInX_lo * VSin);

          VOutX = round(VOutX, VK15);
          VOutY = round(VOutY, VK15);

          VOutX+= (VInX_hi * VCos)<<1;
          VOutY+= (VInY_hi * VCos)<<1;

          VOutX+= (VInY_hi * VSin)<<1;
          VOutY-= (VInX_hi * VSin)<<1;

          (pStage4OutX + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 1 )[Addr_ou].npt() = VOutX;
          (pStage4OutY + VCOP_FFT_512_STAGE4_OUTPUT_STRIDE * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 1 )[Addr_ou].npt() = VOutY;

        }
      }
    }
  }

}



#define VCOP_FFT_512_STAGE5_NUMBF_PER_GRP (1)
#define VCOP_FFT_512_STAGE5_NUMPT_PER_GRP (VCOP_FFT_512_STAGE5_NUMBF_PER_GRP * 2)
#define VCOP_FFT_512_STAGE5_NUM_GRPS      (64 * 4)
#define VCOP_FFT_512_STAGE5_STRIDE        (2*VCOP_FFT_512_STAGE4_OUTPUT_STRIDE)
#define pStage5InX pInput
#define pStage5InY (pInput + VCOP_FFT_512_NPOINTS * sizeof(*pInput))

void vcop_fft_512_16ix16o_32inter_radix2_stage_5_overflow
(
    __vptr_int32      pInput,
    __vptr_int32      pScratch1,
    __vptr_int32      pScratch2,
    __vptr_int16      pOutput,
    __vptr_uint8  pScaleFactor,
    unsigned char numValidBits,
    unsigned short numOfLines
)
{
  __vector Vx0, Vx1, Vy0, Vy1;
  __vector Vx0_plus_x1, Vx0_minus_x1;
  __vector Vy0_plus_y1, Vy0_minus_y1;
  __vector VTemp1, VTemp2, VTemp3, VTemp4;
  __vector VMin, VMax;

  __agen addr0;

  addr0 = 0;
  VMin = 0x7FFFFFFFFF;
  VMax = 0x8000000000;


  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < (VCOP_FFT_512_STAGE5_NUM_GRPS/ 4)/VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < 4; I4++)
      {

        __agen  addr_in = I4 * VCOP_FFT_512_STAGE5_STRIDE * VCOP_FFT_512_STAGE5_NUMPT_PER_GRP +
                          I3 *  VCOP_SIMD_WIDTH * 1 * sizeof(*pInput) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pInput) * 2;

        __agen  addr_out = I4 * VCOP_FFT_512_STAGE5_STRIDE +
                          I3 *  VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1);

        Vx0=  (pStage5InX + VCOP_FFT_512_STAGE5_STRIDE * 1 * 0 )[addr_in].npt();
        Vy0=  (pStage5InY + VCOP_FFT_512_STAGE5_STRIDE * 1 * 0 )[addr_in].npt();
        Vx1=  (pStage5InX + VCOP_FFT_512_STAGE5_STRIDE * 1 * 1 )[addr_in].npt();
        Vy1=  (pStage5InY + VCOP_FFT_512_STAGE5_STRIDE * 1 * 1 )[addr_in].npt();

        (Vx0_plus_x1,  Vx0_minus_x1)   = (Vx0, Vx1).addsub();
        (Vy0_plus_y1,  Vy0_minus_y1)   = (Vy0, Vy1).addsub();

        VTemp1 = min(Vx0_plus_x1, Vy0_plus_y1);
        VTemp2 = min(Vx0_minus_x1,  Vy0_minus_y1);

        VTemp3 = max(Vx0_plus_x1, Vy0_plus_y1);
        VTemp4 = max(Vx0_minus_x1,  Vy0_minus_y1);

        VTemp1 = min(VTemp1, VTemp2);
        VTemp3 = max(VTemp3, VTemp4);

        VMin = min(VMin,VTemp1);
        VMax = max(VMax,VTemp3);

        (pScratch1 + VCOP_FFT_512_STAGE5_STRIDE *  0)[addr_out].npt() = Vx0_plus_x1;
        (pScratch2 + VCOP_FFT_512_STAGE5_STRIDE *  0)[addr_out].npt() = Vy0_plus_y1;

        (pScratch1 + VCOP_FFT_512_STAGE5_STRIDE *  4)[addr_out].npt() = Vx0_minus_x1;
        (pScratch2 + VCOP_FFT_512_STAGE5_STRIDE *  4)[addr_out].npt() = Vy0_minus_y1;

      }
    }
  }

  for ( int I1 = 0; I1 < 1;I1++)
  {
    __vector VK0,VK1;
    __vector VMask;
    __vector VNeg1,VNeg2;
    __vector VPos1,VPos2;
    __vector VLmbd1,VLmbd2;
    __vector VLmbdFinal1,VLmbdFinal2;
    __vector VKMinus1;

    VK0 = 0;
    VK1 = 1;
    VKMinus1 = -1;

    VMask = VMin < VK0;
    VNeg1 = VKMinus1;
    VNeg1 = select(VMask,VMin, VNeg1);
    VMask = VMax < VK0;
    VNeg2 = VKMinus1;
    VNeg2 = select(VMask,VMax, VNeg2);

    VLmbd1 = leading_bit(VNeg1, VK0);
    VLmbd2 = leading_bit(VNeg2, VK0);

    VLmbdFinal1 = max(VLmbd1,VLmbd2);

    VMask = VMin >= VK0;
    VPos1 = VK0;
    VPos1 = select(VMask,VMin, VPos1);
    VMask = VMax >= VK0;
    VPos2 = VK0;
    VPos2 = select(VMask,VMax, VPos2);

    VLmbd1 = leading_bit(VPos1, VK1);
    VLmbd2 = leading_bit(VPos2, VK1);

    VLmbdFinal2 = max(VLmbd1,VLmbd2);

    VLmbdFinal1 = max(VLmbdFinal1,VLmbdFinal2);

    pInput[addr0].npt() = VLmbdFinal1.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  __vector VScaleIn;
  __vector VScale;
  __vector VTemp;

  VTemp = 0;
  VScaleIn = pScaleFactor[addr0].onept();

  for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
  {
    __vector VLmbd;
    __vector VNumValidBits;

    __agen addrIn = I1 * sizeof(*pInput);

    VNumValidBits = numValidBits - 2;

    VLmbd = pInput[addrIn].onept();
    VTemp = max(VLmbd,VTemp);
    VScale = VTemp - VNumValidBits;
    VScale = max(VScaleIn,VScale);

    pScaleFactor[addr0].onept() = VScale.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }


  __vector VInX,VInY;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
   for ( int I3 = 0; I3 < VCOP_FFT_512_NPOINTS/VCOP_SIMD_WIDTH; I3++)
   {
     __agen Addr_in = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                      lineIdx * (VCOP_FFT_512_NPOINTS) * sizeof(*pScratch1);

     __agen Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 +
                      lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2;

     VInX = (pScratch1)[Addr_in].npt();
     VInY = (pScratch2)[Addr_in].npt();

     VOutX = round(VInX, VScale);
     VOutY = round(VInY, VScale);

     pOutput[Addr_out].interleave() = (VOutX, VOutY);
   }
  }
}

void vcop_fft_512_16ix16o_32inter_radix2_stage_5
(
    __vptr_int32      pInput,
    __vptr_int32      pScratch1,
    __vptr_int32      pScratch2,
    __vptr_int16      pOutput,
    unsigned short numOfLines,
    unsigned short scale,
    unsigned short    saturationLimit
)
{
  __vector Vx0, Vx1, Vy0, Vy1;
  __vector Vx0_plus_x1, Vx0_minus_x1;
  __vector Vy0_plus_y1, Vy0_minus_y1;

  __agen addr0;

  addr0 = 0;


  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < (VCOP_FFT_512_STAGE5_NUM_GRPS/ 4)/VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < 4; I4++)
      {

        __agen  addr_in = I4 * VCOP_FFT_512_STAGE5_STRIDE * VCOP_FFT_512_STAGE5_NUMPT_PER_GRP +
                          I3 *  VCOP_SIMD_WIDTH * 1 * sizeof(*pInput) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pInput) * 2;

        __agen  addr_out = I4 * VCOP_FFT_512_STAGE5_STRIDE +
                          I3 *  VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pScratch1);


        Vx0=  (pStage5InX + VCOP_FFT_512_STAGE5_STRIDE * 1 * 0 )[addr_in].npt();
        Vy0=  (pStage5InY + VCOP_FFT_512_STAGE5_STRIDE * 1 * 0 )[addr_in].npt();
        Vx1=  (pStage5InX + VCOP_FFT_512_STAGE5_STRIDE * 1 * 1 )[addr_in].npt();
        Vy1=  (pStage5InY + VCOP_FFT_512_STAGE5_STRIDE * 1 * 1 )[addr_in].npt();

        (Vx0_plus_x1,  Vx0_minus_x1)   = (Vx0, Vx1).addsub();
        (Vy0_plus_y1,  Vy0_minus_y1)   = (Vy0, Vy1).addsub();

        (pScratch1 + VCOP_FFT_512_STAGE5_STRIDE *  0)[addr_out].npt() = Vx0_plus_x1;
        (pScratch2 + VCOP_FFT_512_STAGE5_STRIDE *  0)[addr_out].npt() = Vy0_plus_y1;

        (pScratch1 + VCOP_FFT_512_STAGE5_STRIDE *  4)[addr_out].npt() = Vx0_minus_x1;
        (pScratch2 + VCOP_FFT_512_STAGE5_STRIDE *  4)[addr_out].npt() = Vy0_minus_y1;

      }
    }
  }

  __vector VInX,VInY;
  __vector VOutX, VOutY;


  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
   for ( int I3 = 0; I3 < VCOP_FFT_512_NPOINTS/VCOP_SIMD_WIDTH; I3++)
   {
     __agen Addr_in = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                      lineIdx * (VCOP_FFT_512_NPOINTS) * sizeof(*pScratch1);

     __agen Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 +
                      lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2;

     VInX = (pScratch1)[Addr_in].npt();
     VInY = (pScratch2)[Addr_in].npt();

     VOutX= VInX;
     VOutY= VInY;

     pOutput[Addr_out].interleave() = (VOutX, VOutY).round(scale).saturate(-saturationLimit, (saturationLimit - 1));
   }
  }
}


/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft_512_16ix16o_32inter_kernel_overflow.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */





