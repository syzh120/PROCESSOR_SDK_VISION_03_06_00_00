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


#define VCOP_FFT_512_NPOINTS (512U)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

#define pStage1OutX pOutput
#define pStage1OutY (pOutput + VCOP_FFT_512_NPOINTS * sizeof(*pOutput))

#define VCOP_FFT_512_STAGE4_NUM_GRPS      (64)
#define VCOP_FFT_512_STAGE4_OUTPUT_STRIDE (VCOP_FFT_512_STAGE4_NUM_GRPS * sizeof(*pOutput))

#define VCOP_FFT_512_STAGE5_NUMBF_PER_GRP (1)
#define VCOP_FFT_512_STAGE5_NUMPT_PER_GRP (VCOP_FFT_512_STAGE5_NUMBF_PER_GRP * 2)
#define VCOP_FFT_512_STAGE5_NUM_GRPS      (64 * 4)
#define VCOP_FFT_512_STAGE5_STRIDE        (VCOP_FFT_512_STAGE4_OUTPUT_STRIDE)
#define pStage5InX pInput
#define pStage5InY (pInput + VCOP_FFT_512_NPOINTS * sizeof(*pInput))

void vcop_fft_512_16ix32o_radix2_stage_5_overflow
(
    __vptr_int32      pInput,
    __vptr_int32      pScratch1,
    __vptr_int32      pScratch2,
    __vptr_int32      pOutput,
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
                          I3 *  VCOP_SIMD_WIDTH * sizeof(*pOutput) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput);

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
  VScaleIn = 0;

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

     VOutX = VInX;
     VOutY = VInY;

     (VOutX, VOutY).interleave();

     pOutput[Addr_out].npt() = VOutX;
     (pOutput + VCOP_SIMD_WIDTH*sizeof(*pOutput))[Addr_out].npt() = VOutY;
   }
  }
}

void vcop_fft_512_16ix32o_radix2_stage_5
(
    __vptr_int32      pInput,
    __vptr_int32      pScratch1,
    __vptr_int32      pScratch2,
    __vptr_int32      pOutput,
    unsigned short numOfLines
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
                          I3 *  VCOP_SIMD_WIDTH * sizeof(*pOutput) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput);


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

     VOutX = VInX;
     VOutY = VInY;

     (VOutX, VOutY).interleave();

     pOutput[Addr_out].npt() = VOutX;
     (pOutput + VCOP_SIMD_WIDTH*sizeof(*pOutput))[Addr_out].npt() = VOutY;
   }
  }
}


/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft_512_16ix32o_kernel_overflow.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */





