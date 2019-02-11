/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if 0
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
void vcop_vec_gradients_xy_and_magnitude
(
    __vptr_uint8   pIn,
    __vptr_int16   pGradX,
    __vptr_int16   pGradY,
    __vptr_int16   pMag,
    unsigned short width,
    unsigned short height
)
{
    __vector VinT1,VinT2;               //Top pixel
    __vector VinL1,VinL2;               //Left pixel
    __vector VinR1,VinR2;               //Right pixel
    __vector VinB1,VinB2;               //Bottom pixel
    __vector VgX_1,VgX_2;               //Gx
    __vector VgY_1,VgY_2;               //Gy
    __vector Vabs_gX_1,Vabs_gX_2;       //abs of Gx
    __vector Vabs_gY_1,Vabs_gY_2;       //abs of Gy
    __vector Vmag1,Vmag2, Z;               //Mag

    Z = 0;

    for (int I1 = 0; I1 < (width*height+2*VCOP_SIMD_WIDTH-1)/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr1,Addr2;

        Addr1 = I1*VECTORSZ*2;
        Addr2 = I1*VECTORSZ*4;

        (VinT1,VinT2) = (pIn+1)        [Addr1].deinterleave();
        (VinL1,VinL2) = (pIn+width)    [Addr1].deinterleave();
        (VinR1,VinR2) = (pIn+width+2)  [Addr1].deinterleave();
        (VinB1,VinB2) = (pIn+2*width+1)[Addr1].deinterleave();

        VgX_1 = VinR1 - VinL1;
        VgY_1 = VinB1 - VinT1;

        VgX_2 = VinR2 - VinL2;
        VgY_2 = VinB2 - VinT2;

        Vmag1 = abs(VgX_1);
        Vmag2 = abs(VgX_2);

        Vmag1 += abs(VgY_1 - Z);
        Vmag2 += abs(VgY_2 - Z);

        pGradX[Addr2].interleave() = (VgX_1,VgX_2);
        pGradY[Addr2].interleave() = (VgY_1,VgY_2);
        pMag[Addr2].interleave()   = (Vmag1,Vmag2);
    }
}
#else
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define ALIGN_SIZE(x,y) ((x + (y-1)) & (~(y-1)))

void vcop_vec_gradients_xy_magnitudeu8
(
    __vptr_uint8   pIn,
    __vptr_int16   pGradX,
    __vptr_int16   pGradY,
    __vptr_uint8   pMag,
    unsigned short pitch,
    unsigned short width,
    unsigned short height
)
{
    __vector VinT1,VinT2;               //Top pixel
    __vector VinL1,VinL2;               //Left pixel
    __vector VinR1,VinR2;               //Right pixel
    __vector VinB1,VinB2;               //Bottom pixel
    __vector VgX_1,VgX_2;               //Gx
    __vector VgY_1,VgY_2;               //Gy
    __vector Vabs_gX_1,Vabs_gX_2;       //abs of Gx
    __vector Vabs_gY_1,Vabs_gY_2;       //abs of Gy
    __vector Vmag1,Vmag2, Z;               //Mag
    __agen Addr1,Addr2,Addr3;
    Z = 0;
    for (int I1 = 0; I1 < height; I1++)
    {
       for (int I2 = 0; I2 < ALIGN_SIZE(width,(2*VCOP_SIMD_WIDTH))/(2*VCOP_SIMD_WIDTH); I2++)
       {

        Addr1 = I1*pitch*ELEMSZ + I2*VECTORSZ*2;
        Addr2 = I1*width*ELEMSZ*2 + I2*VECTORSZ*2*2;
        Addr3 = I1*width*ELEMSZ + I2*VECTORSZ*2;

        (VinT1,VinT2) = (pIn+1)        [Addr1].deinterleave();
        (VinL1,VinL2) = (pIn+pitch)    [Addr1].deinterleave();
        (VinR1,VinR2) = (pIn+pitch+2)  [Addr1].deinterleave();
        (VinB1,VinB2) = (pIn+2*pitch+1)[Addr1].deinterleave();

        VgX_1 = VinR1 - VinL1;
        VgY_1 = VinB1 - VinT1;

        VgX_2 = VinR2 - VinL2;
        VgY_2 = VinB2 - VinT2;

        Vmag1 = abs(VgX_1);
        Vmag2 = abs(VgX_2);

        Vmag1 += abs(VgY_1-Z);
        Vmag2 += abs(VgY_2-Z);


        pGradX[Addr2].interleave()    = (VgX_1,VgX_2);
        pGradY[Addr2].interleave()    = (VgY_1,VgY_2);
        //pMag[Addr3].interleave()      = (Vmag1,Vmag2).round(1);
        pMag[Addr3].interleave()      = (Vmag1,Vmag2).saturate(0,255);
      }
   }
}

void vcop_vec_gradients_xy_and_magnitude
(
    __vptr_uint8   pIn,
    __vptr_int16   pGradX,
    __vptr_int16   pGradY,
    __vptr_int16   pMag,
    unsigned short pitch,
    unsigned short width,
    unsigned short height
)
{
    __vector VinT1,VinT2;               //Top pixel
    __vector VinL1,VinL2;               //Left pixel
    __vector VinR1,VinR2;               //Right pixel
    __vector VinB1,VinB2;               //Bottom pixel
    __vector VgX_1,VgX_2;               //Gx
    __vector VgY_1,VgY_2;               //Gy
    __vector Vabs_gX_1,Vabs_gX_2;       //abs of Gx
    __vector Vabs_gY_1,Vabs_gY_2;       //abs of Gy
    __vector Vmag1,Vmag2, Z;               //Mag
    __agen Addr1,Addr2,Addr3;
    Z = 0;
    for (int I1 = 0; I1 < height; I1++)
    {
       for (int I2 = 0; I2 < ALIGN_SIZE(width,(2*VCOP_SIMD_WIDTH))/(2*VCOP_SIMD_WIDTH); I2++)
       {

        Addr1 = I1*pitch*ELEMSZ + I2*VECTORSZ*2;
        Addr2 = I1*width*ELEMSZ*2 + I2*VECTORSZ*2*2;
        Addr3 = I1*width*ELEMSZ*2 + I2*VECTORSZ*2*2;

        (VinT1,VinT2) = (pIn+1)        [Addr1].deinterleave();
        (VinL1,VinL2) = (pIn+pitch)    [Addr1].deinterleave();
        (VinR1,VinR2) = (pIn+pitch+2)  [Addr1].deinterleave();
        (VinB1,VinB2) = (pIn+2*pitch+1)[Addr1].deinterleave();

        VgX_1 = VinR1 - VinL1;
        VgY_1 = VinB1 - VinT1;

        VgX_2 = VinR2 - VinL2;
        VgY_2 = VinB2 - VinT2;

        Vmag1 = abs(VgX_1);
        Vmag2 = abs(VgX_2);

        Vmag1 += abs(VgY_1-Z);
        Vmag2 += abs(VgY_2-Z);


        pGradX[Addr2].interleave()    = (VgX_1,VgX_2);
        pGradY[Addr2].interleave()    = (VgY_1,VgY_2);
        pMag[Addr3].interleave()      = (Vmag1,Vmag2);

      }
   }
}

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))


#define   VCOP_2SIMD_WIDTH   (2 * VCOP_SIMD_WIDTH)
#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define ELEMSZ_INT          sizeof(*gradXY)
#define ELEMSZ_SHORT          sizeof(*gradX)
#define ELEMSZ_CHAR           sizeof(*log4aPtr)
/* ---------------------------------------------------------- */
/* Use "2*VCOP_SIMD_WIDTH" because we operate per 16 elements */
/* ---------------------------------------------------------- */

#define VCOP_2SIMD_WIDTH      (2 * VCOP_SIMD_WIDTH)
#define VECTORSZ_SHORT        (VCOP_2SIMD_WIDTH*ELEMSZ_SHORT)
#define VECTORSZ_CHAR         (VCOP_2SIMD_WIDTH*ELEMSZ_CHAR)
#define SEQ_VECTORSZ          (VCOP_SIMD_WIDTH*sizeof(*xSequence_C))


/* ==================================================
 *  @kernel     vcop_gradients_xy_list
 *
 *  @desc     This kernel calculates the gradient from the input image and edge data
 *                and outputs a list of points where edgeMap is one and gradients at those
 *                points in packed format
 *
 *  @inputs   This kernel takes following Inputs
 *                  pIn :
 *                          Pointer the the input gray scale buffer ( 8bit data)
 *                          Size of this buffer should be width * height
 *                  pUpperLeftXY :
 *                          This is pointer to the buffer which contains the upper left corner coordinates
 *                           Size of this array should be  sizeof(uint32_t)
 *                  pEdgeMap :
 *                          Pointer to the binary image containing 1 at locations where edges are present.
 *                          Size of this buffer should be width * height
 *                  xSequence_C :
 *                          Pointer to pre-calculated sequence from 0 to width -1 left shifted by 16
 *                          Size of this buffer should width * sizeof(uint32_t)
 *                  width :
 *                          Width of the input buffer
 *                  height :
 *                          Height of the input buffer
 *                  pitchInData :
 *                          Pitch of the input buffer
 *                  pitchEdgeMap :
 *                          Pitch of the edgeMap buffer. The (0,0) pixel of this buffer should correspond to
 *                          (1,1) pixel in image buffer
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  pGradXY :
 *                          Pointer to the buffer output gradient buffer containing gradient in both X and Y direction in packed format
 *                          for all the pixels for which edgeMap = 1. Output is stored like ( gx<<16) | gy
 *                          Size of this buffer should be (width * height * sizeof(int32_t))
 *                  pEdgeListXY :
 *                          Pointer to the buffer which will contain the x and y coordinates stored in packed format in
 *                          a 32 bit container. ( x<<16) | y.
 *                          Size of this buffer should be width * height * sizeof(uint32_t))
 *                  pListSize :
 *                          Pointer to the buffer which will contain the size of the list of edges.
 *                          Size of this buffer should be sizeof(uint16_t) * 8
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          pIn                  -> A Copy
 *                          pUpperLeftXY   -> A Copy
 *                          pEdgeMap        -> B Copy
 *                          xSequence_C   -> C Copy
 *                          pGradXY          -> B Copy
 *                          pEdgeListXY      -> C Copy
 *                          pListSize           -> A Copy
 *
 *  @constraints Following constraints
 *                          NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_gradients_xy_list
(
    __vptr_uint8   pIn,
    __vptr_uint32  pUpperLeftXY,
    __vptr_uint8   pEdgeMap,
    __vptr_uint32  xSequence_C,
    __vptr_int32   pGradXY,
    __vptr_uint32  pEdgeListXY,
    __vptr_uint16  pListSize,
    unsigned short width,
    unsigned short height,
    unsigned short pitchInData,
    unsigned short pitchEdgeMap
)
{
    __vector VinT;               //Top pixel
    __vector VinL;               //Left pixel
    __vector VinR;               //Right pixel
    __vector VinB;               //Bottom pixel
    __vector VgX;               //Gx
    __vector VgY;               //Gy
    __vector Vedge;
    __vector VnumEntries;
    __vector K16;
    __vector VgXY;       //abs of Gx
    __vector VedgeXY;
    __vector VxSeq;
    __vector upperLeftXY;
    __agen Addr0, Addr1,Addr2,Addr3;

    VnumEntries = 0;
    Addr0 = 0;
    K16 = 16;

    upperLeftXY = pUpperLeftXY[Addr0].onept();
    for ( int I0 = 0; I0 < 1; I0++)
    {
      for (int I1 = 0; I1 < height; I1++)
      {
        for (int I2 = 0; I2 < ALIGN_SIMD(width)/ VCOP_SIMD_WIDTH; I2++)
        {

          Addr1 = I1 * pitchInData * sizeof(*pIn) + I2 * VCOP_SIMD_WIDTH * sizeof(*pIn);
          Addr2 = I1 * pitchEdgeMap * sizeof(*pEdgeMap) + I2 * VCOP_SIMD_WIDTH * sizeof(*pEdgeMap);
          Addr3 = I2 * VCOP_SIMD_WIDTH * sizeof(*xSequence_C);

          VinT = (pIn+1)        [Addr1].npt();
          VinL = (pIn+pitchInData)    [Addr1].npt();
          VinR = (pIn+pitchInData+2)  [Addr1].npt();
          VinB = (pIn+2*pitchInData+1)[Addr1].npt();
          Vedge = pEdgeMap[Addr2].npt();
          VxSeq = xSequence_C[Addr3].npt();

          /* Initialize y to the current row counter 'i' */
          VedgeXY = I1;

          VgX = VinR - VinL;
          VgY = VinB - VinT;

          VnumEntries += Vedge;
          VgXY = VgX << K16;

          VedgeXY += VxSeq + upperLeftXY;
          VgXY += VgY;

          pGradXY[collate(Vedge)]    = VgXY;
          pEdgeListXY[collate(Vedge)] = VedgeXY;

        }
      }
      pListSize[Addr0] = VnumEntries;
    }

    for(int i = 0; i < 1; i++)
    {
      for(int j = 0; j < 7; j++)
      {
        __vector sz;

        Addr1 = j * sizeof(*pListSize);

        sz = (pListSize + sizeof(*pListSize))[Addr1].onept();

        VnumEntries += sz;
      }
      pListSize[Addr0].onept() = VnumEntries;
    }
}

/* ==================================================
 *  @kernel     vcop_gradients_xy_mag_lut_index_calulcation
 *
 *  @desc     This kernel calculates the index to be used for lookup in reciprocal square root table.
 *                It also outputs (int)log4(a)
 *
 *  @inputs   This kernel takes following Inputs
 *                  gradXY :
 *                          Pointer to the gradient buffer containing gradient in both X and Y direction in packed format
 *                          for all the pixels for which edgeMap = 1. Gradients are stored as ( gx<<16) | gy
 *                          Size of this buffer should be (width * height * sizeof(int32_t))
 *                  width :
 *                          Width of the input buffer
 *                  height :
 *                          Height of the input buffer
 *                  pitch :
 *                          Pitch of the input buffer
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  lutIdxPtr :
 *                          This is pointer to the buffer which will contain the index of the reciprocal sqaure root table
 *                           Size of this array should be width * height * sizeof(int16_t)
 *                  log4aPtr :
 *                          This is pointer to the buffer which will contain the value of (int)log4(a). This will be used to
 *                          calculate the square root
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                    This loop is compute bound so buffer placement is not relevant
 *
 *  @constraints Following constraints
 *                          NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_gradients_xy_mag_lut_index_calulcation
(
  __vptr_int16  gradXY,
  __vptr_uint16 lutIdxPtr,
  __vptr_int8   log4aPtr,
  unsigned short width,
  unsigned short height,
  unsigned short pitch
)
{
   __vector VgX0,  VgX1;
   __vector VgY0,  VgY1;
   __vector VgM0,  VgM1;
   __vector Vz0,   Vz1;
   __vector Vw0,   Vw1;
   __vector VMthr, Vk256;
   __vector Vlut_shift_0, Vlut_shift_1;
   __vector Vk0, Vk1, Vkn1, Vk2;
   __vector Vzlog4_0, Vzlog4_1;
   __vector Vrnd_val_0, Vrnd_val_1;
   __vector Vlut_idx_0, Vlut_idx_1;


   /* -------------------------------------------------------------- */
   /* Initialize constants                                           */
   /* -------------------------------------------------------------- */

   Vk1       = 1;
   Vkn1      = -1;


    for (int I1 = 0; I1 < height; I1++)
    {
      for (int I2 = 0; I2 < ALIGN_2SIMD(width)/ VCOP_2SIMD_WIDTH; I2++)
      {
        __agen Addr_SHORT_IN, Addr_SHORT_OUT, Addr_CHAR;


         Vlut_shift_0 = 8;
         Vk256 = 256;
         Vk2       = 2;
         Vk0 = 0;

         Addr_SHORT_IN  = I1 * pitch * sizeof(*gradXY) * 2   + I2 * VCOP_2SIMD_WIDTH * sizeof(*gradXY) * 2;
         Addr_CHAR   = I1 * pitch * sizeof(*log4aPtr) + I2 * VCOP_2SIMD_WIDTH * sizeof(*log4aPtr);
         Addr_SHORT_OUT  = I1 * pitch * sizeof(*lutIdxPtr)   + I2 * VCOP_2SIMD_WIDTH * sizeof(*lutIdxPtr);


         /* ---------------------------------------------------------- */
         /* Load horizontal and vertical gradients                     */
         /* ---------------------------------------------------------- */

         (VgX0,VgY0)   = gradXY[Addr_SHORT_IN].deinterleave();
         (VgX1,VgY1)   = (gradXY + VCOP_2SIMD_WIDTH * sizeof(*gradXY))[Addr_SHORT_IN].deinterleave();

         /* ----------------------------------------------------------- */
         /* Make copy of initialized constant for second op slot        */
         /* ----------------------------------------------------------- */

         Vlut_shift_1 = Vlut_shift_0 + Vk0;


         /* ----------------------------------------------------------- */
         /* Compute gX*gX and gY*gY                                     */
         /* ----------------------------------------------------------- */

         Vz0 = VgX0*VgX0;
         Vz1 = VgX1*VgX1;

         Vz0 += VgY0*VgY0;
         Vz1 += VgY1*VgY1;


         /* ----------------------------------------------------------- */
         /* Compute lmbd(z)                                             */
         /* ----------------------------------------------------------- */

         Vzlog4_0 = leading_bit(Vz0, Vk1);
         Vzlog4_1 = leading_bit(Vz1, Vk1);


         /* ----------------------------------------------------------- */
         /* Compute int(log4(z)) = lmbd(z) >> 1                         */
         /* ----------------------------------------------------------- */

         Vzlog4_0 = Vzlog4_0 << Vkn1;
         Vzlog4_1 = Vzlog4_1 << Vkn1;


         /* ----------------------------------------------------------- */
         /* Compute Qpoint - 2*int(log4(z))                             */
         /* ----------------------------------------------------------- */

         Vlut_shift_0 -= Vk2*Vzlog4_0;
         Vlut_shift_1 -= Vk2*Vzlog4_1;


         /* ----------------------------------------------------------- */
         /* Compute round value used when right-shifting to get LUT     */
         /* index                                                       */
         /* ----------------------------------------------------------- */

         Vrnd_val_0 = Vk0 - Vlut_shift_0;
         Vrnd_val_1 = Vk0 - Vlut_shift_1;

         Vrnd_val_0 = Vrnd_val_0 - Vk1;
         Vrnd_val_1 = Vrnd_val_1 - Vk1;

         Vrnd_val_0 = Vk1 << Vrnd_val_0;
         Vrnd_val_1 = Vk1 << Vrnd_val_1;

         Vrnd_val_0 = Vz0 + Vrnd_val_0;
         Vrnd_val_1 = Vz1 + Vrnd_val_1;


         /* ----------------------------------------------------------- */
         /* LUT index = (z >> lut_shift) - 256                          */
         /* ----------------------------------------------------------- */

         Vlut_idx_0 = Vrnd_val_0 << Vlut_shift_0;
         Vlut_idx_1 = Vrnd_val_1 << Vlut_shift_1;

         Vlut_idx_0 = Vlut_idx_0 - Vk256;
         Vlut_idx_1 = Vlut_idx_1 - Vk256;


         /* ----------------------------------------------------------- */
         /* If magnitude is zero, give a predefined constant LUT idx,   */
         /* since 1/sqrt(0) is undefined, pixels having this magnitude  */
         /* will not be used in later stages of the app                 */
         /* ----------------------------------------------------------- */

         Vk256 = Vk256 - Vk1;

         Vz0 = Vz0 == Vk0;
         Vz1 = Vz1 == Vk0;

         Vlut_idx_0 = select(Vz0, Vk256, Vlut_idx_0);
         Vlut_idx_1 = select(Vz1, Vk256, Vlut_idx_1);

         lutIdxPtr[Addr_SHORT_OUT] = Vlut_idx_0.saturate(0,767);
         (lutIdxPtr + VCOP_SIMD_WIDTH * sizeof(*lutIdxPtr))[Addr_SHORT_OUT] = Vlut_idx_1.saturate(0,767);

         log4aPtr[Addr_CHAR] = Vzlog4_0;
         (log4aPtr + VCOP_SIMD_WIDTH * sizeof(*log4aPtr))[Addr_CHAR] = Vzlog4_1;
      }
    }
}

#define NUM_TBLS    (8)
#define NUM_PTS_TLU (1)

/* ==================================================
 *  @kernel     vcop_reciprocal_sqrt_lookup
 *
 *  @desc     This kernel does 8 way  lookup in reciprocal square root table.
 *
 *  @inputs   This kernel takes following Inputs
 *                  lutIdxPtr :
 *                          This is pointer to the buffer which will contain the index of the reciprocal sqaure root table
 *                           Size of this array should be width * height * sizeof(int16_t)
 *                  reciSqrtLut :
 *                          This is pointer to the 8 way lookup table.
 *                          Size of this should be  768 * 8
 *                  listSize :
 *                          Size of the list for which lookup is required
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  reciSqrtLutOutput :
 *                          This is pointer to the buffer which will contain the value after the lookup from the given table
 *                           Size of this array should be width * height * sizeof(uint8_t)

 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                  lutIdxPtr
      -> A Copy
 *                  reciSqrtLut     -> C Copy
 *                  reciSqrtLutOutput -> B Copy
 *
 *  @constraints Following constraints
 *                          NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_reciprocal_sqrt_lookup(
                __vptr_uint16 lutIdxPtr,
                __vptr_uint8   reciSqrtLut,
                __vptr_uint8   reciSqrtLutOutput,
                unsigned short listSize)
{

    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

    for (int i4 = 0; i4 < ALIGN_SIMD(listSize)/ NUM_TBLS; i4++)
    {
        __vector Vindex, Vtabledata;

        __agen Addr_CHAR;
        __agen Addr_SHORT;
        __agen Addr_TABLE = 0;

        Addr_SHORT  = i4 * sizeof(*lutIdxPtr) * NUM_TBLS;
        Addr_CHAR   = i4 * sizeof(*reciSqrtLutOutput) * NUM_TBLS;

        Vindex     = lutIdxPtr[Addr_SHORT];
        Vtabledata = reciSqrtLut[Addr_TABLE].lookup(Vindex);
        reciSqrtLutOutput[Addr_CHAR].table_npt() = Vtabledata;
    }
}


/* ==================================================
 *  @kernel     vcop_gradients_xy_unit_vecs
 *
 *  @desc     This kernel calculates the normalized gradients
 *
 *  @inputs   This kernel takes following Inputs
 *                  gradXY :
 *                          Pointer to the gradient buffer containing gradient in both X and Y direction in packed format
 *                          for all the pixels for which edgeMap = 1. Gradients are stored as ( gx<<16) | gy
 *                          Size of this buffer should be (width * height * sizeof(int32_t))
 *                  log4aPtr :
 *                          This is pointer to the buffer which  contain the value of (int)log4(a). This will be used to
 *                          calculate the square root
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *                  reciSqrtLutOutput :
 *                          This is pointer to the buffer which  contain the value after the lookup from the given table
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *                  listSize :
 *                          Size of the list for which lookup is required
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  unitXYptr :
 *                          This is pointer to the buffer which will contain the normalized gradients in X and Y direction
 *                          in packed format as (Ux<<16) | Uy;
 *                           Size of this array should be width * height * sizeof(u32nt8_t)

 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                  gradXY
      -> C Copy
 *                  log4aPtr     -> A Copy
 *                  reciprocalLutOutput -> B Copy
 *                  unitXYptr -> C Copy
 *
 *  @constraints Following constraints
 *                          NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_gradients_xy_unit_vecs
(
  __vptr_int16  gradXY,
  __vptr_int8   log4aPtr,
  __vptr_uint8  reciprocalLutOutput,
  __vptr_int16  unitXYptr,
   unsigned short listSize
)
{
   __vector VgX0,        VgX1;
   __vector VgY0,        VgY1;
   __vector V_UnitX0,    V_UnitX1;
   __vector V_UnitY0,    V_UnitY1;
   __vector Vrec_zqm0,   Vrec_zqm1;
   __vector Vtrig_shf0,  Vtrig_shf1;
   __vector Vk0;
   __vector Vzlog4_0,    Vzlog4_1;

   Vk0 = 0;


    for (int I2 = 0; I2 < ALIGN_2SIMD(listSize)/ VCOP_2SIMD_WIDTH; I2++)
    {
      __agen Addr_SHORT, Addr_CHAR, Addr_out;

      Addr_SHORT  =  I2 * VCOP_2SIMD_WIDTH * sizeof(*gradXY) * 2;
      Addr_CHAR   =  I2 * VCOP_2SIMD_WIDTH * sizeof(*log4aPtr);
      Addr_out    =  I2 * VCOP_2SIMD_WIDTH * sizeof(*unitXYptr)* 2;

      (VgX0,VgY0)            = gradXY[Addr_SHORT].deinterleave();
      (VgX1,VgY1)            = (gradXY + VCOP_2SIMD_WIDTH * sizeof(*gradXY))[Addr_SHORT].deinterleave();


      Vzlog4_0 = log4aPtr[Addr_CHAR];
      Vzlog4_1 = (log4aPtr + VCOP_SIMD_WIDTH * sizeof(*log4aPtr))[Addr_CHAR];

      Vrec_zqm0 = reciprocalLutOutput[Addr_CHAR];
      Vrec_zqm1 = (reciprocalLutOutput + VCOP_SIMD_WIDTH * sizeof(*reciprocalLutOutput))[Addr_CHAR];

      /* ----------------------------------------------------------------- */
      /* trig_shf is the shift amount needed to complete the reciprocal    */
      /* square root computation                                           */
      /* ----------------------------------------------------------------- */

      Vtrig_shf0 = Vk0 - Vzlog4_0;
      Vtrig_shf1 = Vk0 - Vzlog4_1;

      /* ----------------------------------------------------------------- */
      /* Compute the product of the vector component and reciprocal TLU    */
      /* output                                                            */
      /* ----------------------------------------------------------------- */

      V_UnitX0 = VgX0*Vrec_zqm0;
      V_UnitX1 = VgX1*Vrec_zqm1;

      V_UnitY0 = VgY0*Vrec_zqm0;
      V_UnitY1 = VgY1*Vrec_zqm1;

      /* ----------------------------------------------------------------- */
      /* Perform the shift by zlog4 to complete the reciprocal square root */
      /* computation                                                       */
      /* ----------------------------------------------------------------- */

      V_UnitX0 = V_UnitX0 << Vtrig_shf0;
      V_UnitX1 = V_UnitX1 << Vtrig_shf1;

      V_UnitY0 = V_UnitY0 << Vtrig_shf0;
      V_UnitY1 = V_UnitY1 << Vtrig_shf1;

      unitXYptr[Addr_out].interleave() = (V_UnitX0, V_UnitY0);
      (unitXYptr + VCOP_2SIMD_WIDTH * sizeof(*unitXYptr))[Addr_out].interleave() = (V_UnitX1, V_UnitY1);
    }

}

#define GRADIENTS_MAGNITUDE_LUT_INDEX_CALCULATION_PREG_5 (6)
#define RECIPROCAL_SQRT_LOOKUP_PREG_5                    (6)
#define RADIENTS_XY_UNIT_VECS_PREG_5                     (6)


void vcop_gradients_xy_update_param_block
(
  __vptr_uint16  pBlockGradientsXyMagLutIndexCalulcation,
  __vptr_uint16  pBlockReciprocalSqrtLookup,
  __vptr_uint16  pBlockGradientsXyUnitVecs,
  __vptr_uint16  pListSize,
  __vptr_uint16  pListSizeWbuf
)
{
  __vector Vk15;
  __vector Vk7;
  __vector Vk0;
  __vector Vk1;
  __vector VkMinus4;
  __vector VkMinus3;
  __vector VkMinus1;
  __vector VlistSizeAlignSIMD;
  __vector VlistSizeAlign2SIMD;
  __vector VlistSize;
  __vector VMask;
  __agen   addr0 = 0;

  Vk15 = 15;
  Vk7 = 7;
  Vk0 = 0;
  Vk1 = 1;
  VkMinus4 = -4;
  VkMinus3 = -3;
  VkMinus1 = -1;

  VlistSize   = pListSize[addr0].onept();

  for ( int i = 0 ; i < 1; i++ )
  {

    VlistSizeAlignSIMD = VlistSize + Vk0;
    VMask = VlistSizeAlignSIMD == Vk0;
    /* If List size is zero then make it one so that kernels doesnt have problem */
    /* But DMA will still use a value of zero so should not h ave any impact */
    VlistSizeAlignSIMD = select(VMask, Vk1, VlistSizeAlignSIMD);

    VlistSizeAlign2SIMD  = VlistSizeAlignSIMD + Vk0;

    VlistSizeAlign2SIMD += Vk15;
    VlistSizeAlign2SIMD  = VlistSizeAlign2SIMD << VkMinus4;
    VlistSizeAlign2SIMD += VkMinus1;

    VlistSizeAlignSIMD += Vk7;
    VlistSizeAlignSIMD = VlistSizeAlignSIMD << VkMinus3;
    VlistSizeAlignSIMD += VkMinus1;



    (pBlockGradientsXyMagLutIndexCalulcation + GRADIENTS_MAGNITUDE_LUT_INDEX_CALCULATION_PREG_5 )[addr0].onept()  = VlistSizeAlign2SIMD;

    (pBlockReciprocalSqrtLookup + RECIPROCAL_SQRT_LOOKUP_PREG_5 )[addr0].onept()  = VlistSizeAlignSIMD;
    (pBlockGradientsXyUnitVecs + RADIENTS_XY_UNIT_VECS_PREG_5 )[addr0].onept()  = VlistSizeAlign2SIMD;
    /* Copy the listSize to WBUF from IBUF as this will be reused for every trigger and hence should not be in IBUF */
    pListSizeWbuf[addr0].onept()  = VlistSize;

  }
}

#endif
/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_kernel.k              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


