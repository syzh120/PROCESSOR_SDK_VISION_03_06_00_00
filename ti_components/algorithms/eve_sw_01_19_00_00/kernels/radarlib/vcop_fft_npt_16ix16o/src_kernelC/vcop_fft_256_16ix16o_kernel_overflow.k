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

#define VCOP_FFT_256_NPOINTS   (256)
#define VCOP_FFT_256_STAGE1_NUMBF_PER_GRP (64)
#define VCOP_FFT_256_STAGE1_NUM_GRPS      (1)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

#define MAX_OUTPUT_VALUE (16383)
#define MIN_OUTPUT_VALUE (-16384)


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_256_16ix16o_stage_1
 *
 *  @desc     This kernel computes stage 1 of 256 point FFT
 *
 *  @inputs   This kernel takes following Inputs
 *                  pInput :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_cn.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_256()
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  scale :
 *                          Scale factor to be applied after complex multiplication
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutput
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pTwiddleFactor : WBUF
 *                 pInput            :IBUFLA/IBUFHA
 *                 pOutput          :IBUFLA/IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_256_16ix16o_stage_1_overflow
(
    __vptr_int16  pInput,
    __vptr_int32  pScratchWBUF,
    __vptr_int32  pScratchH,
    __vptr_int16  pOutput,
    __vptr_int16  pTwiddleFactor,
    __vptr_uint8  pScaleFactor,
    unsigned char numValidBits,
    unsigned short    pitch,
    unsigned short    numOfLines,
    unsigned short    scale,
    unsigned short    saturationLimit)
{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
    __vector VScatterOffset;
    __vector VCond;
    __vector VMin, VMax;
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
    VCond = 1;
    addr0 = 0;
    VMin = 0x7FFFFFFFFF;
    VMax = 0x8000000000;

    for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
    {
      for (int I3 = 0; I3 < VCOP_FFT_256_STAGE1_NUM_GRPS; I3++)
      {
        for (int I4 = 0; I4 < VCOP_FFT_256_STAGE1_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
        {
          /*-----------------------------------------------------------*/
          /* Set up an address generation, two seperate ones, one for  */
          /* input, and one for twiddle factors.                       */
          /*-----------------------------------------------------------*/

          __agen  Addr_in = lineIdx * pitch +
                  I3 * sizeof(*pInput) * 2 * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pInput) * 2 * VCOP_SIMD_WIDTH;

          __agen  Addr_outWBUF = lineIdx * pitch +
                  I3 * sizeof(*pScratchWBUF) * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pScratchWBUF) * VCOP_SIMD_WIDTH;

          __agen  Addr_outH = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratchH) +
                  I3 * sizeof(*pScratchH) * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
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

          (VX0, VY0) =  (pInput + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 0 )[Addr_in].deinterleave();
          (VX1, VY1) =  (pInput + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 1 )[Addr_in].deinterleave();
          (VX2, VY2) =  (pInput + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 2 )[Addr_in].deinterleave();
          (VX3, VY3) =  (pInput + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 3 )[Addr_in].deinterleave();

          (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
          (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
          (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
          (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


          (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
          (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
          (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
          (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6


          VInterim1 =  min(VOutX0,VOutX2);
          VInterim2 =  max(VOutX0,VOutX2);

          VInterim3 =  min(VOutX1,VOutX3);
          VInterim4 =  max(VOutX1,VOutX3);

          VInterim1 = min(VInterim1, VInterim3);
          VInterim2 = max(VInterim2, VInterim4);

          VInterim3 =  min(VOutY0,VOutY2);
          VInterim4 =  max(VOutY0,VOutY2);

          VInterim1 = min(VInterim1,VInterim3);
          VInterim2 = max(VInterim2,VInterim4);

          VInterim3 =  min(VOutY3,VOutY1);
          VInterim4 =  max(VOutY3,VOutY1);

          VInterim1 = min(VInterim1,VInterim3);
          VInterim2 = max(VInterim2,VInterim4);

          VMin = min(VMin,VInterim1);
          VMax = max(VMax,VInterim2);

          (pScratchWBUF + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 0 )[Addr_outWBUF].npt() = VOutX0.saturate();
          (pScratchH + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 0 )[Addr_outH].npt() = VOutY0.saturate();

          (pScratchWBUF + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 1 )[Addr_outWBUF].npt() = VOutX1.saturate();
          (pScratchH + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 1 )[Addr_outH].npt() = VOutY1.saturate();

          (pScratchWBUF + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 2 )[Addr_outWBUF].npt() = VOutX2.saturate();
          (pScratchH + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 2 )[Addr_outH].npt() = VOutY2.saturate();

          (pScratchWBUF + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 3 )[Addr_outWBUF].npt() = VOutX3.saturate();
          (pScratchH + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 3 )[Addr_outH].npt() = VOutY3.saturate();
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

    pOutput[addr0].npt() = VLmbdFinal1.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  __vector VScaleIn;
  __vector VScaleMinus;
  __vector VTemp;

  VTemp = 0;
  VScaleIn = pScaleFactor[addr0].onept();

  for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
  {
    __vector VLmbd;
    __vector VNumValidBits;
    __vector VKMinus1;
    __vector VScale;


    __agen addrIn = I1 * sizeof(*pOutput);

    VKMinus1 = -1;
    VNumValidBits = numValidBits - 2;

    VLmbd = pOutput[addrIn].onept();
    VTemp = max(VLmbd,VTemp);
    VScale = VTemp - VNumValidBits;
    VScale = max(VScaleIn,VScale);
    VScaleMinus = VScale * VKMinus1;

    pScaleFactor[addr0].onept() = VScale.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  __vector VInX, VInY;
  __vector VCos, VSin;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_256_STAGE1_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_256_STAGE1_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        /*-----------------------------------------------------------*/
        /* Set up an address generation, two seperate ones, one for  */
        /* input, and one for twiddle factors.                       */
        /*-----------------------------------------------------------*/

        __agen  Addr_inWBUF = lineIdx * pitch +
                I3 * sizeof(*pScratchWBUF) * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pScratchWBUF) * VCOP_SIMD_WIDTH;

        __agen  Addr_inH = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratchH) +
                I3 * sizeof(*pScratchH) * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pScratchH) * VCOP_SIMD_WIDTH;

        __agen  Addr_out = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pOutput) * 2 +
                I3 * sizeof(*pOutput) * 2 * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                I4 * sizeof(*pOutput) * 2 * VCOP_SIMD_WIDTH;

        /* here we will multiple the previous output with twiddle factor which is written as
        cos(theta) - j sin(theta)
        if input is x + j y then output is
        (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs) */

        VInX = (pScratchWBUF + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 0 )[Addr_inWBUF].npt();
        VInY = (pScratchH + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 0)[Addr_inH].npt();

        VOutX = VInX << VScaleMinus;
        VOutY = VInY << VScaleMinus;

        (pOutput + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 0 )[Addr_out].interleave() = (VOutX, VOutY);
      }
    }
  }

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_256_STAGE1_NUM_GRPS; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_256_STAGE1_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
      {
        for (int twIdx = 0; twIdx < 3; twIdx++)
        {
          /*-----------------------------------------------------------*/
          /* Set up an address generation, two seperate ones, one for  */
          /* input, and one for twiddle factors.                       */
          /*-----------------------------------------------------------*/

          __agen  Addr_inWBUF = lineIdx * pitch  +
                  I3 * sizeof(*pScratchWBUF) * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pScratchWBUF) * VCOP_SIMD_WIDTH +
                  twIdx * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF);

          __agen  Addr_inH = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratchH) +
                  I3 * sizeof(*pScratchH) * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pScratchH) * VCOP_SIMD_WIDTH +
                  twIdx * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH);

          __agen  Addr_out = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pOutput) * 2 +
                  I3 * sizeof(*pOutput) * 2 * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pOutput) * 2 * VCOP_SIMD_WIDTH +
                  twIdx * VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2;

          __agen  Addr_tw = I4 * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH * 3 +
                            twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;


          /* here we will multiple the previous output with twiddle factor which is written as
          cos(theta) - j sin(theta)
          if input is x + j y then output is
          (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs) */

          (VSin, VCos) =  (pTwiddleFactor + VCOP_SIMD_WIDTH * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();

          VInX = (pScratchWBUF + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchWBUF) * 1 )[Addr_inWBUF].npt();
          VInY = (pScratchH + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pScratchH) * 1)[Addr_inH].npt();

          VInX = VInX << VScaleMinus;
          VInY = VInY << VScaleMinus;

          VOutX = (VInX * VCos);
          VOutY = (VInY * VCos);

          VOutX += (VInY * VSin);
          VOutY -= (VInX * VSin);

          (pOutput + VCOP_FFT_256_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 1 )[Addr_out].interleave() = (VOutX, VOutY).round(15);
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

#define VCOP_FFT_256_STAGE2_NUMBF_PER_GRP (16)
#define VCOP_FFT_256_STAGE2_NUMPT_PER_GRP (VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * 4)
#define VCOP_FFT_256_STAGE2_NUM_GRPS      (4)
#define VCOP_FFT_256_TRANSPOSE_STRIDE     ( 17 * sizeof(*pOutput) * 2)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_256_16ix16o_stage_2
 *
 *  @desc     This kernel computes stage 2 of 256 point FFT. The output at this stage
 *                is re-arranged in such a way that we dont need to do bit-reversal in last stage
 *                to get the output in correct order. To achieve this it utilizes the fact that
 *                each stage each group of butterflies is independent of each other and hence
 *                 can be moved in such a way so as to get output in correct order
 *
 *  @inputs   This kernel takes following Inputs
 *                  pInput :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_cn.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_256()
 *                 pScatterOffset :
 *                          Buffer which stores 8 indexes to be used for doing transpose. Please refer the testbench
 *                           to check how this is calculated
 *                  pitch :
 *                         Offset in terms of number of bytes to move from one line to the next line
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  scale :
 *                          Scale factor to be applied after complex multiplication
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutput
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pTwiddleFactor : WBUF
 *                 pInput            :IBUFLA
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_fft_256_16ix16o_stage_2_overflow
(

    __vptr_int16      pInput,
    __vptr_int32  pScratch1,
    __vptr_int32  pScratch2,
    __vptr_int16      pOutput,
    __vptr_int16      pTwiddleFactor,
    __vptr_uint16     pScatterOffset,
    __vptr_uint8  pScaleFactor,
    unsigned char numValidBits,
    unsigned short pitch,
    unsigned short numOfLines,
    unsigned short scale,
    unsigned short    saturationLimit
)
{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
    __vector VScatterOffset;
    __vector VCond;
    __vector VMin, VMax;
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



   VCond = 1;
   __agen addr0;
   addr0 = 0;


   VScatterOffset = pScatterOffset[addr0].npt();
   VMin = 0x7FFFFFFFFF;
   VMax = 0x8000000000;

   for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
   {
       for (int I3 = 0; I3 < VCOP_FFT_256_STAGE2_NUM_GRPS; I3++)
       {
         for (int I2 = 0; I2 < (VCOP_FFT_256_STAGE2_NUMBF_PER_GRP/ VCOP_SIMD_WIDTH); I2++)
         {
           __agen  Addr_in = lineIdx * pitch +
                             I3 * VCOP_FFT_256_STAGE2_NUMPT_PER_GRP  * sizeof(*pInput) * 2 +
                             I2 * VCOP_SIMD_WIDTH * sizeof(*pInput) * 2;

           __agen  Addr_out = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratch1) +
                              I3 * VCOP_FFT_256_STAGE2_NUMPT_PER_GRP  * sizeof(*pScratch1) +
                              I2 * VCOP_SIMD_WIDTH * sizeof(*pScratch1);

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

        (VX0, VY0) =  (pInput + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 0 )[Addr_in].deinterleave();
        (VX1, VY1) =  (pInput + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 1 )[Addr_in].deinterleave();
        (VX2, VY2) =  (pInput + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 2 )[Addr_in].deinterleave();
        (VX3, VY3) =  (pInput + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 3 )[Addr_in].deinterleave();

        (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
        (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
        (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
        (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


        (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
        (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
        (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
        (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

        VInterim1 =  min(VOutX0,VOutX2);
        VInterim2 =  max(VOutX0,VOutX2);

        VInterim3 =  min(VOutX1,VOutX3);
        VInterim4 =  max(VOutX1,VOutX3);

        VInterim1 = min(VInterim1, VInterim3);
        VInterim2 = max(VInterim2, VInterim4);

        VInterim3 =  min(VOutY0,VOutY2);
        VInterim4 =  max(VOutY0,VOutY2);

        VInterim1 = min(VInterim1,VInterim3);
        VInterim2 = max(VInterim2,VInterim4);

        VInterim3 =  min(VOutY3,VOutY1);
        VInterim4 =  max(VOutY3,VOutY1);

        VInterim1 = min(VInterim1,VInterim3);
        VInterim2 = max(VInterim2,VInterim4);

        VMin = min(VMin,VInterim1);
        VMax = max(VMax,VInterim2);

        (pScratch1 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 0 )[Addr_out].npt() = VOutX0.saturate();
        (pScratch2 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 0 )[Addr_out].npt() = VOutY0.saturate();

        (pScratch1 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 1 )[Addr_out].npt() = VOutX1.saturate();
        (pScratch2 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 1 )[Addr_out].npt() = VOutY1.saturate();

        (pScratch1 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 2 )[Addr_out].npt() = VOutX2.saturate();
        (pScratch2 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 2 )[Addr_out].npt() = VOutY2.saturate();

        (pScratch1 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 3 )[Addr_out].npt() = VOutX3.saturate();
        (pScratch2 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 3 )[Addr_out].npt() = VOutY3.saturate();
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

    pOutput[addr0].npt() = VLmbdFinal1.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  __vector VScaleIn;
  __vector VScaleMinus;
  __vector VTemp;

  VTemp = 0;
  VScaleIn = pScaleFactor[addr0].onept();

  for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
  {
    __vector VLmbd;
    __vector VNumValidBits;
    __vector VKMinus1;
    __vector VScale;


    __agen addrIn = I1 * sizeof(*pOutput);

    VKMinus1 = -1;
    VNumValidBits = numValidBits - 2;

    VLmbd = pOutput[addrIn].onept();
    VTemp = max(VLmbd,VTemp);
    VScale = VTemp - VNumValidBits;
    VScale = max(VScaleIn,VScale);
    VScaleMinus = VScale * VKMinus1;

    pScaleFactor[addr0].onept() = VScale.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  __vector VInX, VInY;
  __vector VCos, VSin;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I4 = 0; I4 < VCOP_FFT_256_STAGE2_NUM_GRPS; I4++)
    {
      for (int I3 = 0; I3 < (VCOP_FFT_256_STAGE2_NUMBF_PER_GRP/ VCOP_SIMD_WIDTH); I3++)
      {
        /*-----------------------------------------------------------*/
        /* Set up an address generation, two seperate ones, one for  */
        /* input, and one for twiddle factors.                       */
        /*-----------------------------------------------------------*/
        __agen  Addr_in = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratch1) +
                          I4 * VCOP_FFT_256_STAGE2_NUMPT_PER_GRP * sizeof(*pScratch1) +
                          I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1);

        __agen  Addr_out = lineIdx * VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * VCOP_FFT_256_TRANSPOSE_STRIDE +
                          I4 * 1 * sizeof(*pOutput) * 2 +
                          I3 * VCOP_FFT_256_TRANSPOSE_STRIDE * VCOP_SIMD_WIDTH ;

        /* here we will multiple the previous output with twiddle factor which is written as
        cos(theta) - j sin(theta)
        if input is x + j y then output is
        (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs) */

        VInX =  (pScratch1 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1) * 0 )[Addr_in].npt();
        VInY =  (pScratch2 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2) * 0)[Addr_in].npt();

        VOutX = VInX << VScaleMinus;
        VOutY = VInY << VScaleMinus;

        (pOutput + sizeof(*pOutput) * 2 * 4 * 0)[Addr_out].p_scatter(VScatterOffset) = VOutX;
        (pOutput + sizeof(*pOutput) * 2 * 4 * 0 + sizeof(*pOutput))[Addr_out].p_scatter(VScatterOffset) = VOutY;
      }
    }
  }


  for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
  {
    for (int I4 = 0; I4 < VCOP_FFT_256_STAGE2_NUM_GRPS; I4++)
    {
      for (int I3 = 0; I3 < (VCOP_FFT_256_STAGE2_NUMBF_PER_GRP/ VCOP_SIMD_WIDTH); I3++)
      {
        for (int twIdx = 0; twIdx < 3; twIdx++)
        {
          /*-----------------------------------------------------------*/
          /* Set up an address generation, two seperate ones, one for  */
          /* input, and one for twiddle factors.                       */
          /*-----------------------------------------------------------*/
          __agen  Addr_in = lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratch1) +
                            I4 * VCOP_FFT_256_STAGE2_NUMPT_PER_GRP * sizeof(*pScratch1) +
                            I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                            twIdx * VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch1);

          __agen  Addr_out = lineIdx * VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * VCOP_FFT_256_TRANSPOSE_STRIDE +
                            I4 * 1 * sizeof(*pOutput) * 2 +
                            I3 * VCOP_FFT_256_TRANSPOSE_STRIDE * VCOP_SIMD_WIDTH +
                            twIdx * sizeof(*pOutput) * 2 * 4 ;

          __agen  Addr_tw = I3 * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH * 3 +
                            twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;


          /* here we will multiple the previous output with twiddle factor which is written as
          cos(theta) - j sin(theta)
          if input is x + j y then output is
          (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs) */

          (VSin, VCos) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();
          VInX =  (pScratch1 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2))[Addr_in].npt();
          VInY =  (pScratch2 + VCOP_FFT_256_STAGE2_NUMBF_PER_GRP * sizeof(*pScratch2))[Addr_in].npt();

          VInX = VInX << VScaleMinus;
          VInY = VInY << VScaleMinus;

          VOutX = (VInX * VCos);
          VOutY = (VInY * VCos);

          VOutX += (VInY * VSin);
          VOutY -= (VInX * VSin);

          (pOutput + sizeof(*pOutput) * 2 * 4 * 1)[Addr_out].p_scatter(VScatterOffset) = VOutX.round(15);
          (pOutput + sizeof(*pOutput) * 2 * 4 * 1 + sizeof(*pOutput))[Addr_out].p_scatter(VScatterOffset) = VOutY.round(15);
         }
      }
    }
  }
}


/*---------------------------------------------------------------------------*/
/* In stage 4, operations are similar to previous stages of 1..2. Even       */
/*---------------------------------------------------------------------------*/


#define VCOP_FFT_256_STAGE3_NUMBF_PER_GRP (4)
#define VCOP_FFT_256_STAGE3_NUMPT_PER_GRP (VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 4)
#define VCOP_FFT_256_STAGE3_NUM_GRPS      (16)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_256_16ix16o_stage_3
 *
 *  @desc     This kernel computes stage 3 of 256 point FFT. This stage computation is
 *                 same as stage 1.
 *
 *  @inputs   This kernel takes following Inputs
 *                  pInput :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  pTwiddleFactor :
 *                          Buffer which holds twidlde factor for this kernel implementaion. The order
 *                          in which these are generated can be seen from vcop_fft_npt_16ix16o_cn.c file
 *                           Size of this buffer should be getSizeTwiddleFactor_256()
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  scale :
 *                          Scale factor to be applied after complex multiplication
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutput
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pTwiddleFactor : WBUF
 *                 pInput            :IBUFLA
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_256_16ix16o_stage_3_overflow
(
  __vptr_int16      pInput,
  __vptr_int32  pScratch1,
  __vptr_int32  pScratch2,
  __vptr_int16      pOutput,
  __vptr_int16      pTwiddleFactor,
  __vptr_uint8  pScaleFactor,
  unsigned char numValidBits,
  unsigned short numOfLines,
  unsigned short scale,
  unsigned short    saturationLimit
)

{
#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
    __vector VScatterOffset;
    __vector VCond;
    __vector VMin, VMax;
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
  VCond = 1;
  addr0 = 0;

  VMin = 0x7FFFFFFFFF;
  VMax = 0x8000000000;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_256_STAGE3_NUM_GRPS/ VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_256_STAGE3_NUMBF_PER_GRP; I4++)
      {

        __agen  Addr_in = I4 * VCOP_FFT_256_TRANSPOSE_STRIDE +
                          I3 * VCOP_SIMD_WIDTH * sizeof(*pInput) * 2 +
                          lineIdx * VCOP_FFT_256_TRANSPOSE_STRIDE * VCOP_FFT_256_STAGE3_NUMPT_PER_GRP;


        __agen  Addr_out = I4 * (VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1)) +
                           I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                           lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratch1);

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

      (VX0, VY0) =  (pInput + VCOP_FFT_256_STAGE3_NUMBF_PER_GRP *
                    VCOP_FFT_256_TRANSPOSE_STRIDE * 0 )[Addr_in].deinterleave();
      (VX1, VY1) =  (pInput + VCOP_FFT_256_STAGE3_NUMBF_PER_GRP *
                    VCOP_FFT_256_TRANSPOSE_STRIDE * 1 )[Addr_in].deinterleave();
      (VX2, VY2) =  (pInput + VCOP_FFT_256_STAGE3_NUMBF_PER_GRP *
                    VCOP_FFT_256_TRANSPOSE_STRIDE * 2 )[Addr_in].deinterleave();
      (VX3, VY3) =  (pInput + VCOP_FFT_256_STAGE3_NUMBF_PER_GRP *
                    VCOP_FFT_256_TRANSPOSE_STRIDE * 3 )[Addr_in].deinterleave();

      (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
      (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
      (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
      (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


      (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
      (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
      (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
      (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

      VInterim1 =  min(VOutX0,VOutX2);
      VInterim2 =  max(VOutX0,VOutX2);

      VInterim3 =  min(VOutX1,VOutX3);
      VInterim4 =  max(VOutX1,VOutX3);

      VInterim1 = min(VInterim1, VInterim3);
      VInterim2 = max(VInterim2, VInterim4);

      VInterim3 =  min(VOutY0,VOutY2);
      VInterim4 =  max(VOutY0,VOutY2);

      VInterim1 = min(VInterim1,VInterim3);
      VInterim2 = max(VInterim2,VInterim4);

      VInterim3 =  min(VOutY3,VOutY1);
      VInterim4 =  max(VOutY3,VOutY1);

      VInterim1 = min(VInterim1,VInterim3);
      VInterim2 = max(VInterim2,VInterim4);

      VMin = min(VMin,VInterim1);
      VMax = max(VMax,VInterim2);

      (pScratch1 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) * 1 *
                        VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 0 )[Addr_out].npt() = VOutX0.saturate();
      (pScratch2 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch2) * 0 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 0 )[Addr_out].npt() = VOutY0.saturate();

      (pScratch1 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) * 1 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 1)[Addr_out].npt() = VOutX1.saturate();
      (pScratch2 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch2) * 1 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 1)[Addr_out].npt() = VOutY1.saturate();

      (pScratch1 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) * 1 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 2)[Addr_out].npt() = VOutX2.saturate();
      (pScratch2 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch2) * 1 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 2 )[Addr_out].npt() = VOutY2.saturate();

      (pScratch1 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) * 1 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 3)[Addr_out].npt() = VOutX3.saturate();
      (pScratch2 + VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch2)  * 1 *
                      VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 3)[Addr_out].npt() = VOutY3.saturate();

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
  __vector VScaleMinus;
  __vector VTemp;

  VTemp = 0;
  VScaleIn = pScaleFactor[addr0].onept();

  for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
  {
    __vector VLmbd;
    __vector VNumValidBits;
    __vector VKMinus1;
    __vector VScale;


    __agen addrIn = I1 * sizeof(*pInput);

    VKMinus1 = -1;
    VNumValidBits = numValidBits - 2;

    VLmbd = pInput[addrIn].onept();
    VTemp = max(VLmbd,VTemp);
    VScale = VTemp - VNumValidBits;
    VScale = max(VScaleIn,VScale);
    VScaleMinus = VScale * VKMinus1;

    pScaleFactor[addr0].onept() = VScale.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }


  __vector VInX, VInY;
  __vector VCos, VSin;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_256_STAGE3_NUM_GRPS/ VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_256_STAGE3_NUMBF_PER_GRP; I4++)
      {
        /*-----------------------------------------------------------*/
        /* Set up an address generation, two seperate ones, one for  */
        /* input, and one for twiddle factors.                       */
        /*-----------------------------------------------------------*/
        __agen  Addr_in = I4 * (VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1)) +
                          I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                          lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratch1);

        __agen  Addr_ou = I4 * (VCOP_FFT_256_STAGE3_NUM_GRPS * 2 * sizeof(*pOutput)) +
                          I3 * VCOP_SIMD_WIDTH * 2 * sizeof(*pOutput) +
                          lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pOutput) * 2;

        /* here we will multiple the previous output with twiddle factor which is written as
        cos(theta) - j sin(theta)
        if input is x + j y then output is
        (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs) */

        VInX =  (pScratch1 +  VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) *
                                         VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 0)[Addr_in].npt();
        VInY =  (pScratch2 +  VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) *
                               VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 0)[Addr_in].npt();

        VOutX = VInX << VScaleMinus;
        VOutY = VInY << VScaleMinus;

        (pOutput + VCOP_FFT_256_STAGE3_NUMBF_PER_GRP *
        VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 0 )[Addr_ou].interleave() = (VOutX, VOutY);

      }
    }
  }

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_256_STAGE3_NUM_GRPS/ VCOP_SIMD_WIDTH; I3++)
    {
      for (int I4 = 0; I4 < VCOP_FFT_256_STAGE3_NUMBF_PER_GRP; I4++)
      {
        for (int twIdx = 0; twIdx < 3; twIdx++)
        {
          /*-----------------------------------------------------------*/
          /* Set up an address generation, two seperate ones, one for  */
          /* input, and one for twiddle factors.                       */
          /*-----------------------------------------------------------*/
          __agen  Addr_in = twIdx * (VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1)) * VCOP_FFT_256_STAGE3_NUMBF_PER_GRP +
                            I4 * (VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1)) +
                            I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                            lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pScratch1);

          __agen  Addr_ou = twIdx * (VCOP_FFT_256_STAGE3_NUM_GRPS * 2 * sizeof(*pOutput)) * VCOP_FFT_256_STAGE3_NUMBF_PER_GRP +
                            I4 * (VCOP_FFT_256_STAGE3_NUM_GRPS * 2 * sizeof(*pOutput)) +
                            I3 * VCOP_SIMD_WIDTH * 2 * sizeof(*pOutput) +
                            lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pOutput) * 2;

          __agen  Addr_tw = I4 * 3 * sizeof(*pTwiddleFactor) * 2 *  VCOP_SIMD_WIDTH +
                            twIdx * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH;


          /* here we will multiple the previous output with twiddle factor which is written as
          cos(theta) - j sin(theta)
          if input is x + j y then output is
          (x + j y) ( c - j s) = (x.c + y.s) + j (y.c - xs) */

          (VSin, VCos) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();

          VInX =  (pScratch1 +  VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) *
                                           VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 1)[Addr_in].npt();
          VInY =  (pScratch2 +  VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pScratch1) *
                                 VCOP_FFT_256_STAGE3_NUMBF_PER_GRP * 1)[Addr_in].npt();

          VInX = VInX << VScaleMinus;
          VInY = VInY << VScaleMinus;

          VOutX = (VInX * VCos);
          VOutY = (VInY * VCos);

          VOutX += (VInY * VSin);
          VOutY -= (VInX * VSin);

          (pOutput + VCOP_FFT_256_STAGE3_NUMBF_PER_GRP *
          VCOP_FFT_256_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 )[Addr_ou].interleave() = (VOutX, VOutY).round(15);


         }
      }
    }
  }
}

#define VCOP_FFT_256_STAGE4_NUMBF_PER_GRP (1)
#define VCOP_FFT_256_STAGE4_NUMPT_PER_GRP (VCOP_FFT_256_STAGE4_NUMBF_PER_GRP * 4)
#define VCOP_FFT_256_STAGE4_NUM_GRPS      (64)
/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_256_16ix16o_stage_4
 *
 *  @desc     This kernel computes stage 4 of 256 point FFT. At this stage
 *                  no twiddle factors are required as all of them are 1.
 *
 *  @inputs   This kernel takes following Inputs
 *                  pInput :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  scale :
 *                          Scale factor to be applied after complex multiplication
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutput
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 pInput            :IBUFLA/WBUF
 *                 pOutput          :IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_256_16ix16o_stage_4_overflow
(

    __vptr_int16      pInput,
    __vptr_int32  pScratch1,
    __vptr_int32  pScratch2,
    __vptr_int16      pOutput,
    __vptr_uint8  pScaleFactor,
    unsigned char numValidBits,
    unsigned short numOfLines,
    unsigned short scale,
    unsigned short    saturationLimit
)
{

#if (!ENABLE_MANUAL_REGISTER_ALLOCATION)
    __vector VScatterOffset;
    __vector VCond;
    __vector VMin, VMax;
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
  VCond = 1;
  addr0 = 0;

  VMin = 0x7FFFFFFFFF;
  VMax = 0x8000000000;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < 2; I3++)
    {
      for (int I4 = 0; I4 < 4; I4++)
      {
        __agen  Addr_in = I4 * (4 * VCOP_2SIMD_WIDTH * 2 * sizeof(*pInput)) +
                  I3 * VCOP_SIMD_WIDTH * 2 * sizeof(*pInput) +
                  lineIdx * (VCOP_2SIMD_WIDTH * 2 * sizeof(*pInput)) * 16;


        __agen  Addr_out = I4 * (VCOP_2SIMD_WIDTH * sizeof(*pScratch1)) +
                  I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                  lineIdx * (VCOP_2SIMD_WIDTH* sizeof(*pScratch1)) * 16;

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

        (VX0, VY0) =  (pInput + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
                      VCOP_2SIMD_WIDTH * sizeof(*pInput) * 2 * 0 )[Addr_in].deinterleave();
        (VX1, VY1) =  (pInput + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
                      VCOP_2SIMD_WIDTH * sizeof(*pInput) * 2 * 1 )[Addr_in].deinterleave();
        (VX2, VY2) =  (pInput + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
                      VCOP_2SIMD_WIDTH * sizeof(*pInput) * 2 * 2 )[Addr_in].deinterleave();
        (VX3, VY3) =  (pInput + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
                      VCOP_2SIMD_WIDTH * sizeof(*pInput) * 2 * 3 )[Addr_in].deinterleave();

        (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
        (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
        (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
        (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


        (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
        (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
        (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
        (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6

        VInterim1 =  min(VOutX0,VOutX2);
        VInterim2 =  max(VOutX0,VOutX2);

        VInterim3 =  min(VOutX1,VOutX3);
        VInterim4 =  max(VOutX1,VOutX3);

        VInterim1 = min(VInterim1, VInterim3);
        VInterim2 = max(VInterim2, VInterim4);

        VInterim3 =  min(VOutY0,VOutY2);
        VInterim4 =  max(VOutY0,VOutY2);

        VInterim1 = min(VInterim1,VInterim3);
        VInterim2 = max(VInterim2,VInterim4);

        VInterim3 =  min(VOutY3,VOutY1);
        VInterim4 =  max(VOutY3,VOutY1);

        VInterim1 = min(VInterim1,VInterim3);
        VInterim2 = max(VInterim2,VInterim4);

        VMin = min(VMin,VInterim1);
        VMax = max(VMax,VInterim2);

        (pScratch1 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch1) * 0 )[Addr_out].npt() = VOutX0;
        (pScratch2 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch2) *  0 )[Addr_out].npt() = VOutY0;

        (pScratch1 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch1) * 1 )[Addr_out].npt() = VOutX1;
        (pScratch2 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch2) * 1 )[Addr_out].npt() = VOutY1;

        (pScratch1 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch1) * 2 )[Addr_out].npt() = VOutX2;
        (pScratch2 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch2) * 2 )[Addr_out].npt() = VOutY2;

        (pScratch1 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch1) * 3 )[Addr_out].npt() = VOutX3;
        (pScratch2 + VCOP_FFT_256_STAGE4_NUMBF_PER_GRP *
              4 * VCOP_2SIMD_WIDTH * sizeof(*pScratch2) * 3 )[Addr_out].npt() = VOutY3;

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
  __vector VScaleMinus;
  __vector VTemp;

  VTemp = 0;
  VScaleIn = pScaleFactor[addr0].onept();


  for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
  {
    __vector VLmbd;
    __vector VNumValidBits;
    __vector VKMinus1;
    __vector VScale;


    __agen addrIn = I1 * sizeof(*pInput);

    VKMinus1 = -1;
    VNumValidBits = numValidBits - 2;

    VLmbd = pInput[addrIn].onept();
    VTemp = max(VLmbd,VTemp);
    VScale = VTemp - VNumValidBits;
    VScale = max(VScaleIn,VScale);
    VScaleMinus = VScale * VKMinus1;

    pScaleFactor[addr0].onept() = VScale.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }


  __vector VInX,VInY;
  __vector VOutX, VOutY;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
   for ( int I3 = 0; I3 < VCOP_FFT_256_NPOINTS/VCOP_SIMD_WIDTH; I3++)
   {
     __agen Addr_in = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                      lineIdx * (VCOP_FFT_256_NPOINTS) * sizeof(*pScratch1);

     __agen Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 +
                      lineIdx * VCOP_FFT_256_NPOINTS * sizeof(*pOutput) * 2;

     VInX = (pScratch1)[Addr_in].npt();
     VInY = (pScratch2)[Addr_in].npt();

     VOutX = VInX << VScaleMinus;
     VOutY = VInY << VScaleMinus;

     pOutput[Addr_out].interleave() = (VOutX, VOutY);
   }
  }
}


/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft_256_16ix16o_kernel_overflow.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */



