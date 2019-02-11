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

#define VCOP_FFT_64_NPOINTS   (64)
#define VCOP_FFT_64_NUM_LINES_PER_ITERATION (2)

#define VCOP_FFT_64_TRANSPOSE_STRIDE ((VCOP_SIMD_WIDTH + 1) * 4)

#define VCOP_FFT_64_STAGE3_NUMBF_PER_GRP (1)
#define VCOP_FFT_64_STAGE3_NUMPT_PER_GRP (VCOP_FFT_64_STAGE2_NUMBF_PER_GRP * 4)
#define VCOP_FFT_64_STAGE3_NUM_GRPS      (16)
#define pStage3InX pInput
#define pStage3InY (pInput + numOfLines * (VCOP_FFT_64_NPOINTS + 4) * sizeof(*pInput))
/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_64_16ix32o_stage_3
 *
 *  @desc     This kernel computes stage 3 of 64 point FFT. At this stage
 *                  no twiddle factors are required as all of them are 1.
 *
 *  @inputs   This kernel takes following Inputs
 *                  pInput :
 *                          Input buffer containing data 32 bit signed data with real and imaginary part
 *                          separated in different planes.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int32_t) * 2
 *                  numPoints :
 *                          Number of points
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutput
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int32_t) * 2
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
 void vcop_fft_64_16ix32o_stage_3_overflow
(

    __vptr_int32      pInput,
    __vptr_int32      pScratch1,
    __vptr_int32      pScratch2,
    __vptr_int32      pOutput,
    __vptr_uint8      pScaleFactor,
    __vptr_int16      pInterimBuf,
    unsigned char     numValidBits,
    unsigned short numOfLines
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

  __vector VInX, VInY;
  __vector VCos, VSin;
  __vector VOutX, VOutY;
#endif

  VCond = 1;
  __agen addr0;
  addr0 = 0;

  VMin = 0x7FFFFFFFFF;
  VMax = 0x8000000000;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_64_STAGE3_NUM_GRPS / VCOP_SIMD_WIDTH; I3++)
    {
      __agen  Addr_in = I3 * VCOP_SIMD_WIDTH * 1 * sizeof(*pInput) +
                lineIdx * ((VCOP_FFT_64_NPOINTS + 4) * sizeof(*pInput));


      __agen  Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                lineIdx * (VCOP_FFT_64_NPOINTS + 4) * sizeof(*pScratch1);

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

      VX0=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
      VY0=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
      VX1=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
      VY1=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
      VX2=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
      VY2=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
      VX3=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 3 )[Addr_in].npt();
      VY3=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 3 )[Addr_in].npt();

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

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 0 )[Addr_out].npt() = VOutX0;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 0 )[Addr_out].npt() = VOutY0;

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 1 )[Addr_out].npt() = VOutX1;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 1 )[Addr_out].npt() = VOutY1;

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 2 )[Addr_out].npt() = VOutX2;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 2 )[Addr_out].npt() = VOutY2;

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 3 )[Addr_out].npt() = VOutX3;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 3 )[Addr_out].npt() = VOutY3;

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

    pInterimBuf[addr0].npt() = VLmbdFinal1.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  __vector VScaleIn;
  __vector VScale;
  __vector VScaleMinus;
  __vector VTemp;

  VTemp = 0;
  VScaleIn = 0;

  for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
  {
    __vector VLmbd;
    __vector VNumValidBits;

    __agen addrIn = I1 * sizeof(*pInterimBuf);

    VNumValidBits = numValidBits - 2;

    VLmbd = pInterimBuf[addrIn].onept();
    VTemp = max(VLmbd,VTemp);
    VScale = VTemp - VNumValidBits;
    VScale = max(VScaleIn,VScale);

    pScaleFactor[addr0].onept() = VScale.saturate(0,0,40,40);/* Saturate to make negative values to zero */
  }

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for ( int I3 = 0; I3 < VCOP_FFT_64_NPOINTS/VCOP_SIMD_WIDTH; I3++)
    {
      __agen Addr_in = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                       lineIdx * (VCOP_FFT_64_NPOINTS + 4) * sizeof(*pScratch1);

      __agen Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 +
                       lineIdx * VCOP_FFT_64_NPOINTS * sizeof(*pOutput) * 2;

      VInX = (pScratch1)[Addr_in].npt();
      VInY = (pScratch2)[Addr_in].npt();

      VOutX = VInX;
      VOutY = VInY;

      (VOutX, VOutY).interleave();

      pOutput[Addr_out].npt() = VOutX;
      (pOutput + VCOP_SIMD_WIDTH*sizeof(*pOutput))[Addr_out].npt() = VOutY;
    }
  }
}

void vcop_fft_64_16ix32o_stage_3
(

    __vptr_int32      pInput,
    __vptr_int32      pScratch1,
    __vptr_int32      pScratch2,
    __vptr_int32      pOutput,
    unsigned short numOfLines
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

  __vector VInX, VInY;
  __vector VCos, VSin;
  __vector VOutX, VOutY;
#endif

  __agen addr0;
  addr0 = 0;


  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < VCOP_FFT_64_STAGE3_NUM_GRPS / VCOP_SIMD_WIDTH; I3++)
    {
      __agen  Addr_in = I3 * VCOP_SIMD_WIDTH * 1 * sizeof(*pInput) +
                lineIdx * ((VCOP_FFT_64_NPOINTS + 4) * sizeof(*pInput));


      __agen  Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                lineIdx * (VCOP_FFT_64_NPOINTS + 4) * sizeof(*pScratch1);

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

      VX0=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
      VY0=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 0 )[Addr_in].npt();
      VX1=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
      VY1=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 1 )[Addr_in].npt();
      VX2=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
      VY2=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 2 )[Addr_in].npt();
      VX3=  (pStage3InX + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 3 )[Addr_in].npt();
      VY3=  (pStage3InY + VCOP_FFT_64_STAGE3_NUM_GRPS *
                                  sizeof(*pInput) * 1 * 3 )[Addr_in].npt();

      (VX0_plus_X2,VX0_minus_X2) = (VX0,VX2).addsub();//v0 and v4
      (VX1_plus_X3,VX1_minus_X3) = (VX1,VX3).addsub();//v2 and V6
      (VY0_plus_Y2,VY0_minus_Y2) = (VY0,VY2).addsub();//V1 and V5
      (VY1_plus_Y3,VY1_minus_Y3) = (VY1,VY3).addsub();//V3 and V7


      (VOutX0,VOutX2) = (VX0_plus_X2,VX1_plus_X3).addsub();//V0 and V2
      (VOutX1,VOutX3) = (VX0_minus_X2,VY1_minus_Y3).addsub();//V4 and V7
      (VOutY0,VOutY2) = (VY0_plus_Y2,VY1_plus_Y3).addsub();// V1 and V3
      (VOutY3,VOutY1) = (VY0_minus_Y2,VX1_minus_X3).addsub();//V5,V6


      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 0 )[Addr_out].npt() = VOutX0;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 0 )[Addr_out].npt() = VOutY0;

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 1 )[Addr_out].npt() = VOutX1;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 1 )[Addr_out].npt() = VOutY1;

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 2 )[Addr_out].npt() = VOutX2;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 2 )[Addr_out].npt() = VOutY2;

      (pScratch1 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch1) * 1 * 3 )[Addr_out].npt() = VOutX3;
      (pScratch2 + VCOP_FFT_64_STAGE3_NUM_GRPS *
                          sizeof(*pScratch2) * 1 * 3 )[Addr_out].npt() = VOutY3;

    }
  }

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for ( int I3 = 0; I3 < VCOP_FFT_64_NPOINTS/VCOP_SIMD_WIDTH; I3++)
    {
      __agen Addr_in = I3 * VCOP_SIMD_WIDTH * sizeof(*pScratch1) +
                       lineIdx * (VCOP_FFT_64_NPOINTS + 4) * sizeof(*pScratch1);

      __agen Addr_out = I3 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 +
                       lineIdx * VCOP_FFT_64_NPOINTS * sizeof(*pOutput) * 2;

      VInX = (pScratch1)[Addr_in].npt();
      VInY = (pScratch2)[Addr_in].npt();

      VOutX = VInX;
      VOutY = VInY;

      (VOutX, VOutY).interleave();

      pOutput[Addr_out].npt() = VOutX;
      (pOutput + VCOP_SIMD_WIDTH*sizeof(*pOutput))[Addr_out].npt() = VOutY;
    }
  }
}


/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft-64_16x16t_kernel.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */



