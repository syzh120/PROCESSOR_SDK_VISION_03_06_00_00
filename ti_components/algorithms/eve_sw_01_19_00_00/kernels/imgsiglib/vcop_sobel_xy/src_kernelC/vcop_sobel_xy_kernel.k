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


#define   VCOP_2SIMD_WIDTH   (2 * VCOP_SIMD_WIDTH)
#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define ELEMSZ_IN       sizeof(*inData)
#define VECTORSZ_IN     (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT      sizeof(*outData)
#define VECTORSZ_OUT    ((VCOP_SIMD_WIDTH) * ELEMSZ_OUT)

#define ELEMSZ_INTER    sizeof(*interimData)

#define SAT_LO          (-128)
#define SAT_HI          (127)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_sobelXY_3x3_separable_uchar
 *
 *  @desc     Separable implementation of sobel X and Y operator together
 *                 which is [1 2 1] x [1 0 -1]'
 *
 *  @inputs   This kernel takes following Inputs
 *                  inData :
 *                          Input data pointer
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  roundShift :
 *                          Rounding that needs to be applied to the output
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  interimDataX :
 *                          This is pointer  to an intermediate scratch buffer to store intermediate X data
 *                          Size of this buffer should be (blockHeight * ALIGN_2SIMD(computeWidth) * size(int16_t)
 *                  interimDataY :
 *                          This is pointer  to an intermediate scratch buffer to store intermediate  Y data
 *                          Size of this buffer should be (blockHeight * ALIGN_2SIMD(computeWidth) * size(int16_t)
 *
 *  @outputs   This kernel produce following outputs
 *                  outDataX
 *                          Pointer to the output for X component
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *                  outDataY
 *                          Pointer to the output for Y component
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          inData -> ACOPY
 *                          interimDataX-> B COPY
 *                          interimDataY-> C COPY
 *                          outDataX-> ACOPY
 *                          outDataX-> ACOPY
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXY_3x3_separable_uchar
(
     __vptr_uint8  inData,
     __vptr_int16  interimDataX,
     __vptr_int16  interimDataY,
     __vptr_int8   outDataX,
     __vptr_int8   outDataY,
     unsigned short computeWidth,
     unsigned short computeHeight,
     unsigned short inputPitch,
     unsigned short outputPitch,
     unsigned short roundShift
)
{
    __vector Vin, Vin0_plus2, Vin1_plus2;
    __vector Vin0, Vin1, Vin2, Vin3, Vin4, Vin5, VinY0 , VinY1;
    __vector VinterimY1, VinterimY2;
    __vector VinterimX1, VinterimX2;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we implement 1-D horizontal filtering for both X and Y */
    /*-------------------------------------------------------------------*/
    for (int I1 = 0; I1 < computeHeight + 2; I1++)
    {
        for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen outAddr;
            __agen inAddr;

            inAddr = (I1 * inputPitch * sizeof(*inData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*inData));
            outAddr = (I1 * computeWidth * sizeof(*interimDataX)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*interimDataX));

            /* Read Elements 1 3 5 7 9..  and 2 4 6 8 10..*/
            (Vin0, Vin1)  =   inData[inAddr].deinterleave();
            /* Read Elements 3 5 7 9 11..  and 4 6 8 10 12..*/
            (Vin2, Vin3)   =   (inData + (2 * sizeof(*inData)))[inAddr].deinterleave();

            /* For X gradient apply [1 0 -1] */
            VinterimX1 = Vin0 - Vin2;
            VinterimX2 = Vin1 - Vin3;

           /* For Y gradient apply [1 2 1], so we want Vin0 + 2 * Vin1 + Vin2 and Vin1 + 2 * Vin2 + Vin3*/
           VinterimY1 = Vin0 + Vin1;
           VinterimY2 = Vin1 + Vin2;

           VinterimY1 += Vin1 + Vin2;
           VinterimY2 += Vin2 + Vin3;

           interimDataX[outAddr].interleave() = (VinterimX1, VinterimX2);
           interimDataY[outAddr].interleave() = (VinterimY1, VinterimY2);
        }
    }

    /*-------------------------------------------------------------------*/
    /* This is the second loop where we implement 1-D vertical filtering for both X and Y */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < computeHeight; I1++)
    {

        /*---------------------------------------------------------------*/
        /* As we do deinterleaved loads, we can load 2 * VCOP_SIMD_WIDTH */
        /* amount of data at a time.                                     */
        /*---------------------------------------------------------------*/

        for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen Addr0;
            __agen Addr1;

            Addr0 = (I1 * computeWidth *  sizeof(*interimDataX)) + (I2 * VCOP_2SIMD_WIDTH *  sizeof(*interimDataX));
            Addr1 = (I1 * outputPitch * sizeof(*outDataX)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*outDataX));

            /* Read Intermediate X and Y Data */
            (Vin0, Vin1) = interimDataX[Addr0].deinterleave();
            (Vin2, Vin3) = (interimDataX + (computeWidth * sizeof(*interimDataX)))[Addr0].deinterleave();
            (Vin4, Vin5) = (interimDataX + (2 * computeWidth * sizeof(*interimDataX)))[Addr0].deinterleave();

            (VinY0, VinY1)  =   interimDataY[Addr0].deinterleave();
            (Vin0_plus2, Vin1_plus2)   =   (interimDataY + (2 * computeWidth * sizeof(*interimDataY)))[Addr0].deinterleave();

            /* For X apply [1 2 1]' operator */
            VinterimX1 = Vin0 + Vin2;
            VinterimX2 = Vin1 + Vin3;

            VinterimX1 += Vin2 + Vin4;
            VinterimX2 += Vin3 + Vin5;

            /* For X apply [1 0 -1]' operator */
            VinterimY1 = VinY0 - Vin0_plus2;
            VinterimY2 = VinY1 - Vin1_plus2;

            outDataX[Addr1].interleave() = (VinterimX1, VinterimX2).round(roundShift).saturate( SAT_LO, SAT_HI );
            outDataY[Addr1].interleave() = (VinterimY1, VinterimY2).round(roundShift).saturate( SAT_LO, SAT_HI );
        }
    }
}

/*-----------------------------------------------------------------------*/
/* This is the separable version of the sobel X function.                */
/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_sobelX_3x3_separable_uchar
 *
 *  @desc     Separable implementation of sobel X operator
 *                 which is [1 0 -1] x[1 2 1]'
 *
 *  @inputs   This kernel takes following Inputs
 *                  inData :
 *                          Input data pointer
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  roundShift :
 *                          Rounding that needs to be applied to the output
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  interimData :
 *                          This is pointer  to an intermediate scratch buffer to store intermediate data
 *                          Size of this buffer should be (blockHeight * ALIGN_2SIMD(computeWidth) * size(int16_t)
 *
 *  @outputs   This kernel produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          inData -> VCOP_IBUFLA
 *                          interimData -> VCOP_WMEM
 *                          outData -> VCOP_IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelX_3x3_separable_uchar
(
     __vptr_uint8  inData,
     __vptr_int16  interimData,
     __vptr_int8   outData,
     unsigned short computeWidth,
     unsigned short computeHeight,
     unsigned short inputPitch,
     unsigned short outputPitch,
     unsigned short roundShift
)
{
    __vector Vin, Vin0_plus2, Vin1_plus2, Vout0, Vout1;
    __vector Vin0, Vin1, Vin2, Vin3, Vin4, Vin5;
    __vector Vsum0, Vsum1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we implement 1-D horizontal filtering*/
    /* by applying [1 0 -1] to the image data.                           */
    /* Cycles: 2/16                                                      */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < computeHeight + 2; I1++)
    {
        for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen outAddr;
            __agen inAddr;

            inAddr = (I1 * inputPitch * sizeof(*inData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*inData));
            outAddr = (I1 * computeWidth * sizeof(*interimData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*interimData));

            (Vin0, Vin1)  =   inData[inAddr].deinterleave();
            (Vin0_plus2, Vin1_plus2)   =   (inData + (2 * sizeof(*inData)))[inAddr].deinterleave();

            Vsum0 = Vin0 - Vin0_plus2;
            Vsum1 = Vin1 - Vin1_plus2;

           interimData[outAddr].interleave() = (Vsum0, Vsum1);
        }
    }

    /*-------------------------------------------------------------------*/
    /* This is the second loop where we implement 1-D vertical filtering */
    /* by applying [1 2 1]' to the intermediate data.                    */
    /* Cycles: 3/16 cyc/pix (Memory access bound)                        */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < computeHeight; I1++)
    {

        /*---------------------------------------------------------------*/
        /* As we do deinterleaved loads, we can load 2 * VCOP_SIMD_WIDTH */
        /* amount of data at a time.                                     */
        /*---------------------------------------------------------------*/

        for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen Addr0;
            __agen Addr1;

            Addr0 = (I1 * computeWidth *  sizeof(*interimData)) + (I2 * VCOP_2SIMD_WIDTH *  sizeof(*interimData));
            Addr1 = (I1 * outputPitch * sizeof(*outData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*outData));

            (Vin0, Vin1) = interimData[Addr0].deinterleave();
            (Vin2, Vin3) = (interimData + (computeWidth * sizeof(*interimData)))[Addr0].deinterleave();
            (Vin4, Vin5) = (interimData + (2 * computeWidth * sizeof(*interimData)))[Addr0].deinterleave();

            Vout0 = Vin0 + Vin2;
            Vout1 = Vin1 + Vin3;

            Vout0 += Vin2 + Vin4;
            Vout1 += Vin3 + Vin5;

            outData[Addr1].interleave() = (Vout0, Vout1).round(roundShift).saturate( SAT_LO, SAT_HI );
        }
    }
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_sobelY_3x3_separable_uchar
 *
 *  @desc     Separable implementation of sobel Y operator
 *                 which is [1 2 1] x [1 0 -1]'
 *
 *  @inputs   This kernel takes following Inputs
 *                  inData :
 *                          Input data pointer
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  roundShift :
 *                          Rounding that needs to be applied to the output
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  interimData :
 *                          This is pointer  to an intermediate scratch buffer to store intermediate data
 *                          Size of this buffer should be (blockHeight * ALIGN_2SIMD(computeWidth) * size(int16_t)
 *
 *  @outputs   This kernel produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          inData -> VCOP_IBUFLA
 *                          interimData -> VCOP_WMEM
 *                          outData -> VCOP_IBUFHA
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelY_3x3_separable_uchar
(
     __vptr_uint8  inData,
     __vptr_int16  interimData,
     __vptr_int8   outData,
     unsigned short computeWidth,
     unsigned short computeHeight,
     unsigned short inputPitch,
     unsigned short outputPitch,
     unsigned short roundShift
)
{
    __vector Vin0, Vin1, Vin2, Vin3, Vin4, Vin5;
    __vector Vinterim1, Vinterim2;
    __vector Vin0_plus2, Vin1_plus2;
    __vector Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we implement 1-D horizontal filtering */
    /* by applying [1 2 1] to the input data.                    */
    /*-------------------------------------------------------------------*/
    for (int I1 = 0; I1 < computeHeight + 2; I1++)
    {
        /*---------------------------------------------------------------*/
        /* As we do deinterleaved loads, we can load 2 * VCOP_SIMD_WIDTH */
        /* amount of data at a time.                                     */
        /*---------------------------------------------------------------*/

        for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen Addr0;
            __agen Addr1;

            Addr0 = (I1 * inputPitch *  sizeof(*inData)) + (I2 * VCOP_2SIMD_WIDTH *  sizeof(*inData));
            Addr1 = (I1 * computeWidth * sizeof(*interimData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*interimData));

            /* Read Elements 1 3 5 7 9..  and 2 4 6 8 10..*/
            (Vin0, Vin1) = inData[Addr0].deinterleave();
            /* Read Elements 3 5 7 9 11..  and 4 6 8 10 12..*/
            (Vin2, Vin3) = (inData + (2 *sizeof(*inData)))[Addr0].deinterleave();

            /* We want Vin0 + 2 * Vin1 + Vin2 and Vin1 + 2 * Vin2 + Vin3*/
            Vinterim1 = Vin0 + Vin1;
            Vinterim2 = Vin1 + Vin2;

            Vinterim1 += Vin1 + Vin2;
            Vinterim2 += Vin2 + Vin3;

            interimData[Addr1].interleave() = (Vinterim1, Vinterim2);
        }
    }

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we implement 1-D Vertical filtering*/
    /* by applying [1 0 -1]' to the image data.                           */
    /* Cycles: 2/16                                                      */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < computeHeight; I1++)
    {
        for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen outAddr;
            __agen inAddr;

            inAddr = (I1 * computeWidth * sizeof(*interimData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*interimData));
            outAddr = (I1 * outputPitch * sizeof(*outData)) + (I2 * VCOP_2SIMD_WIDTH * sizeof(*outData));

            (Vin0, Vin1)  =   interimData[inAddr].deinterleave();
            (Vin0_plus2, Vin1_plus2)   =   (interimData + (2 * computeWidth * sizeof(*interimData)))[inAddr].deinterleave();

            Vout0 = Vin0 - Vin0_plus2;
            Vout1 = Vin1 - Vin1_plus2;

           outData[outAddr].interleave() = (Vout0, Vout1).round(roundShift).saturate( SAT_LO, SAT_HI );
        }
    }


}

/* ==================================================
 *  @kernel     vcop_sobelXy_3x3_L1_thresholding
 *
 *  @desc     This kernel uses L1 norm and thesholding
 *
 *
 *  @inputs   This kernel takes following Inputs
 *                  gradX :
 *                          Gradient X
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  gradY :
 *                          Gradient Y
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  threshold :
 *                          Threshold to be used for thresholding magnitude
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl containing 255 at places where edges are present and 0 otherwise
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   This is compute bound kernel so buffer placement doesnt affect the performance
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXy_3x3_L1_thresholding
(
   __vptr_int8   gradX,
   __vptr_int8   gradY,
   __vptr_uint8  outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short  threshold
)
{
  __vector VgradX1, VgradX2;
  __vector VgradY1, VgradY2;
  __vector Vmag1, Vmag2;
  __vector Vout1, Vout2;
  __vector VK0;
  __vector Vthreshold;

   VK0 = 0;
   Vthreshold = threshold;

  /*-------------------------------------------------------------------*/
  /* This is the 2-D version of the code. Here the 3x3 kernel is       */
  /* applied to the input data.                                        */
  /*-------------------------------------------------------------------*/

  for ( int I1 = 0; I1 < computeHeight; I1++ )
  {
      for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
      {
         __agen Addr_in;
         __agen Addr_out;

         /* ----------------------------------------------------------- */
         /* Input and Output Address Increments                         */
         /* ----------------------------------------------------------- */

         Addr_in   =  I2 * VCOP_2SIMD_WIDTH * sizeof(*gradX) + I1 * inputPitch * sizeof(*gradX);
         Addr_out  =  I2 * VCOP_2SIMD_WIDTH * sizeof(*outData) + I1 * outputPitch * sizeof(*outData);

         (VgradX1, VgradX2) = gradX[Addr_in].deinterleave();
         (VgradY1, VgradY2) = gradY[Addr_in].deinterleave();

          Vmag1 = abs(VgradX1);
          Vmag2 = abs(VgradX2);

          Vmag1 += abs ( VgradY1 - VK0);
          Vmag2 += abs ( VgradY2 - VK0);

          Vout1 = Vmag1 > Vthreshold;
          Vout2 = Vmag2 > Vthreshold;

          outData[Addr_out].interleave() = (Vout1,Vout2).saturate(0, 0, 1, 255);

     }
  }

}


/* Compiler register allocation is not giving optimal performance. for this code
There is a difference of 1/16 cycles per pixel */

/* ==================================================
 *  @kernel     vcop_sobelXy_3x3_L1_thresholding_binPack
 *
 *  @desc     This kernel uses L1 norm and thesholding and gives a binary image output
 *                whose bits indicate edge if it is 1 and non-edge if it is zero. While loading
 *                a data in byte lower most bit will correspond to the first pixel.
 *
 *
 *  @inputs   This kernel takes following Inputs
 *                  gradX :
 *                          Gradient X
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  gradY :
 *                          Gradient Y
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  threshold :
 *                          Threshold to be used for thresholding magnitude
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl containing 1 and places where edges are present and 0 otherwise
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t) /8
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   gradX, gradY and outData should not be in same memory
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXy_3x3_L1_thresholding_binPack
(
   __vptr_int8   gradX,
   __vptr_int8   gradY,
   __vptr_uint8  outData,
   unsigned short computeWidth,
   unsigned short computeHeight,
   unsigned short inputPitch,
   unsigned short outputPitch,
   unsigned short  threshold
)
{
  __vector VgX1, VgX2,VgY1, VgY2,VTest1, VTest2,Vo1, Vo2,VK0,Vthreshold;

   VK0 = 0;
   Vthreshold = threshold;

  /*-------------------------------------------------------------------*/
  /* This is the 2-D version of the code. Here the 3x3 kernel is       */
  /* applied to the input data.                                        */
  /*-------------------------------------------------------------------*/

  for ( int I1 = 0; I1 < computeHeight; I1++ )
  {
      for ( int I2 = 0; I2 < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; I2++)
      {
         __agen Addr_in;
         __agen Addr_out;

         /* ----------------------------------------------------------- */
         /* Input and Output Address Increments                         */
         /* ----------------------------------------------------------- */

         Addr_in   =  I2 * VCOP_2SIMD_WIDTH * sizeof(*gradX) + I1 * inputPitch * sizeof(*gradX);
         Addr_out  =  I2 * 2 * sizeof(*outData) + I1 * outputPitch * sizeof(*outData);

         VgX1 = gradX[Addr_in].npt();
         VgX2 = (gradX + VCOP_SIMD_WIDTH)[Addr_in].npt();

         VgY1 = gradY[Addr_in].npt();
         VgY2 = (gradY + VCOP_SIMD_WIDTH)[Addr_in].npt();

         VTest1 = abs(VgX1);
         VTest2 = abs(VgX2);

         VTest1 += abs ( VgY1 - VK0);
         VTest2 += abs ( VgY2 - VK0);

         Vo1 = pack(VTest1 >= Vthreshold);
         Vo2 = pack(VTest2 >= Vthreshold);

         outData[Addr_out].onept() = Vo1;
         (outData + 1)[Addr_out].onept() = Vo2;

     }
  }

}

