/*
*
* Copyright (c) {YEAR} Texas Instruments Incorporated
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
/* NAME: eve_fir2D_Y                                              */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*                                                                 */
/*                                                                 */
/* void vcop_yuv420_fir2d_separable_y                              */
/* (                                                               */
/*     __vptr_uint8        data_ptr,                               */
/*     __vptr_int16        inter_ptr,                              */
/*     __vptr_int8         coefh_ptr,                              */
/*     __vptr_int8         coefv_ptr,                              */
/*     unsigned short      blkw,                                   */
/*     unsigned short      lofst,                                  */
/*     unsigned short      blkh,                                   */
/*     unsigned short      num_coef,                               */
/*     __vptr_uint8        output_ptr,                             */
/*    unsigned short       rnd_bits                                */
/* );                                                              */
/*                                                                 */
/* The function "eve_fir2D_Y" accepts input data in an array      */
/* of unsigned char in "data_ptr", of width "blk_w" and height     */
/* "blk_h" with each line having a line pitch of "line_ofst"       */
/* elements, a filter coefficient array in "coef_ptr" of width     */
/* "coef_w" and a height of "coef_h" unsigned char 8-bit coeffs,   */
/* filtering the input and writing the result in an output array   */
/* output_ptr of width "blk_w" elements per line, where each line  */
/* has a line pitch of "line_ofst" and "blk_h" such lines.         */
/*                                                                 */
/* The interleave form of this kernel, would require "blk_w"       */
/* to be a multiple of 16, so that we can compute 16 output        */
/* coefficients in parallel.                                       */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2012-2016.                       */
/*=================================================================*/

#if (VCOP_HOST_EMULATION)
#include "vcop.h"
#endif

#define VCOP_2SIMD_WIDTH  (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ            sizeof(*data_ptr)
#define LINESZ            (lofst * ELEMSZ)

#define VECTORSZ          (VCOP_2SIMD_WIDTH * ELEMSZ)

#define COEF_ELEMSZ       sizeof(*coefh_ptr)
#define COEF_LINESZ       (num_coef * COEF_ELEMSZ)

#define INTER_ELEMSZ      sizeof(*inter_ptr)

#define OUTPUT_ELEMSZ     sizeof(*output_ptr)
#define OUTPUT_LINESZ     (blkw * OUTPUT_ELEMSZ)
#define OUTPUT_VECTORSZ   (VCOP_2SIMD_WIDTH * OUTPUT_ELEMSZ)

void vcop_yuv420_fir2d_separable_y
(
    __vptr_uint8        data_ptr,     // input data pointer
    __vptr_int16        inter_ptr,    // intermediate data pointer
    __vptr_int8         coefh_ptr,    // horizontal coef data pointer
    __vptr_int8         coefv_ptr,    // vertical coef data pointer
    unsigned short      blkw,         // width of input block, in elements
    unsigned short      lofst,        // offset between input lines, in elems
    unsigned short      blkh,         // height of input block
    unsigned short      num_coef,     // width of coef block, in elements
    __vptr_uint8        output_ptr,   // output data pointer
   unsigned short       rnd_bits      // bit position for rounding
)
{
    /*-------------------------------------------------------------------*/
    /* This is the first loop where we implement 1-D horizontal filtering*/
    /* by applying [1 2 1] to the image data.                            */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /* Note 2 extra lines need to be processed, to make sure the         */
    /* intermediate data has last 2 lines needed for next VLOOP.         */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < blkh + num_coef - 1; I1++)
    {
        __vector Vout1, Vout2;

        for ( int I2 = 0; I2 < blkw/VCOP_2SIMD_WIDTH; I2++)
        {
         __agen A2;
         __vector Vin1, Vin2;

         Vout1 =  0;
         Vout2 =  0;

            for (int I3 = 0; I3 < num_coef; I3++)
            {
               __agen A0, A1;
               __vector Vcoef;

               A0  = I1 * lofst * ELEMSZ + I2 * VCOP_2SIMD_WIDTH * ELEMSZ + I3 * ELEMSZ;

               (Vin1, Vin2) = data_ptr[A0].deinterleave();

               A1    = I3 * COEF_ELEMSZ;
               Vcoef = coefh_ptr[A1].onept();

               Vout1 += Vin1 * Vcoef;
               Vout2 += Vin2 * Vcoef;

#ifdef __PRINT_RES__
               printf("\n");
               printf("Addr = %d,\n", I1 * lofst * ELEMSZ + I2 * VECTORSZ + I3 * ELEMSZ);
               Vin1.printx();
               Vin2.printx();
               Vcoef.printx();
#endif
            }

#ifdef __PRINT_RES__
         printf("------\n");
         Vout1.printx();
         Vout2.printx();
         printf("------\n");
#endif

         A2 = (I1 * blkw * INTER_ELEMSZ) + (I2 * VCOP_2SIMD_WIDTH * INTER_ELEMSZ);

         inter_ptr[A2].interleave() = (Vout1, Vout2);
      }
    }

    /*-------------------------------------------------------------------*/
    /* This is the second loop where we implement 1-D vertical filtering */
    /* by applying [1 2 1]' to the intermediate data.                    */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT_RES__
    printf("*********\n");
#endif

    for (int I1 = 0; I1 < blkh; I1++)
    {
        for ( int I2 = 0; I2 < blkw/VCOP_2SIMD_WIDTH; I2++)
        {
         __agen A2;
         __vector Vcoef;
         __vector Vout1, Vout2;

         Vout1 =  0;
         Vout2 =  0;

            for (int I3 = 0; I3 < num_coef; I3++)
            {
               __agen A0, A1;
               __vector Vin1, Vin2;

               A0  = I1 * blkw * INTER_ELEMSZ + I2 * VCOP_2SIMD_WIDTH * INTER_ELEMSZ + I3 * blkw * INTER_ELEMSZ;

               (Vin1, Vin2) = inter_ptr[A0].deinterleave();

               A1    = I3 * COEF_ELEMSZ;
               Vcoef = coefv_ptr[A1].onept();

               Vout1 += Vin1 * Vcoef;
               Vout2 += Vin2 * Vcoef;

#ifdef __PRINT_RES__
               printf("\n");
               printf("Addr** = %d,\n", I2 * VCOP_2SIMD_WIDTH * INTER_ELEMSZ + I3 * blkw * INTER_ELEMSZ);
               Vin1.printx();
               Vin2.printx();
               Vcoef.printx();
#endif
            }

#ifdef __PRINT_RES__
         printf("------\n");
         Vout1.printx();
         Vout2.printx();
         printf("------\n");
#endif

         A2 = I1 * (blkw) * OUTPUT_ELEMSZ + (I2 * VCOP_2SIMD_WIDTH * OUTPUT_ELEMSZ);

         output_ptr[A2].interleave() = (Vout1, Vout2).round(rnd_bits).saturate(0,255);
      }
   }
}



/*-------------------------------------------------------------------*/
/* UV data filtered here.                                            */
/* YUV 4:2:0 format assumed. Results are stored in interleaved       */
/* format.                                                           */
/*-------------------------------------------------------------------*/
#define ELEMSZ_UV         sizeof(*UVdata_ptr)
#define VECTORSZ_UV       (VCOP_2SIMD_WIDTH * ELEMSZ_UV)
#define OUT_UV_ELEMSZ     sizeof(*UVout_ptr)

void vcop_yuv420_fir2d_separable_uv
(
    __vptr_uint8        UVdata_ptr,   // input data pointer
    __vptr_int16        inter_ptr,    // intermediate data pointer
    __vptr_int8         coefh_ptr,    // horizontal coef data pointer
    __vptr_int8         coefv_ptr,    // vertical coef data pointer
    unsigned short      blkw,         // width of input block, in elements
    unsigned short      lofst,        // offset between input lines, in elems
    unsigned short      blkh,         // height of input block
    unsigned short      num_coef,     // width of coef block, in elements
    __vptr_uint8        UVout_ptr,    // output data pointer
   unsigned short       rnd_bits      // bit position for rounding
)
{
    /*-------------------------------------------------------------------*/
    /* This is the first loop where we implement 1-D horizontal filtering*/
    /* by applying [1 2 1] to the image data.                            */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /* Note 2 extra lines need to be processed, to make sure the         */
    /* intermediate data has last 2 lines needed for next VLOOP.         */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < blkh + num_coef - 1; I1++)
    {
        __vector Vout1, Vout2;

        for ( int I2 = 0; I2 < blkw/VCOP_2SIMD_WIDTH; I2++)
        {
         __agen A2;
         __vector Vin1, Vin2;

         Vout1 =  0;
         Vout2 =  0;

            for (int I3 = 0; I3 < num_coef; I3++)
            {
               __agen A0, A1;
               __vector Vcoef;

               /*----------------------------------------------------*/
               /* Skip by 2 in the horizontal direction to get to    */
               /* next U pixel --> I3 * 2 * ELEMSZ                   */
               /*----------------------------------------------------*/

               A0  = I1 * lofst * ELEMSZ_UV + I2 * VCOP_2SIMD_WIDTH * ELEMSZ_UV + I3 * 2 * ELEMSZ_UV;

               (Vin1, Vin2) = UVdata_ptr[A0].deinterleave();

               A1    = I3 * COEF_ELEMSZ;
               Vcoef = coefh_ptr[A1].onept();

               Vout1 += Vin1 * Vcoef;
               Vout2 += Vin2 * Vcoef;

#ifdef __PRINT_RES__
               printf("\n");
               printf("Addr = %d,\n", I1 * lofst * ELEMSZ_UV + I2 * VECTORSZ + I3 * ELEMSZ_UV);
               Vin1.printx();
               Vin2.printx();
               Vcoef.printx();
#endif
            }

#ifdef __PRINT_RES__
         printf("------\n");
         Vout1.printx();
         Vout2.printx();
         printf("------\n");
#endif

         A2 = (I1 * blkw * INTER_ELEMSZ) + (I2 * VCOP_2SIMD_WIDTH * INTER_ELEMSZ);

         inter_ptr[A2].interleave() = (Vout1, Vout2);
      }
    }

    /*-------------------------------------------------------------------*/
    /* This is the second loop where we implement 1-D vertical filtering */
    /* by applying [1 2 1]' to the intermediate data.                    */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT_RES__
    printf("*********\n");
#endif

    for (int I1 = 0; I1 < blkh; I1++)
    {
        for ( int I2 = 0; I2 < blkw/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen A2;
            __vector Vcoef;
            __vector Vout1, Vout2;

            Vout1 =  0;
            Vout2 =  0;

            for (int I3 = 0; I3 < num_coef; I3++)
            {
               __agen A0, A1;
               __vector Vin1, Vin2;

               A0  = I1 * blkw * INTER_ELEMSZ + I2 * VCOP_2SIMD_WIDTH * INTER_ELEMSZ + I3 * blkw * INTER_ELEMSZ;

               (Vin1, Vin2) = inter_ptr[A0].deinterleave();

               A1    = I3 * COEF_ELEMSZ;
               Vcoef = coefv_ptr[A1].onept();

               Vout1 += Vin1 * Vcoef;
               Vout2 += Vin2 * Vcoef;

#ifdef __PRINT_RES__
               printf("\n");
               printf("Addr** = %d,\n", I2 * VCOP_2SIMD_WIDTH * INTER_ELEMSZ + I3 * blkw * INTER_ELEMSZ);
               Vin1.printx();
               Vin2.printx();
               Vcoef.printx();
#endif
            }

#ifdef __PRINT_RES__
         printf("------\n");
         Vout1.printx();
         Vout2.printx();
         printf("------\n");
#endif

         A2 = I1 * (blkw) * OUT_UV_ELEMSZ + (I2 * VCOP_2SIMD_WIDTH * OUT_UV_ELEMSZ);

         UVout_ptr[A2].interleave() = (Vout1, Vout2).round(rnd_bits).saturate(0,255);
      }
   }
}


/*
{
   __vector   VinU,  VinV;
   __vector   Vcoef;
   __vector   VoutU, VoutV;

   for (int I1 = 0; I1 < blkh; I1++)
   {
      for (int I2 = 0; I2 < (blkw/VCOP_2SIMD_WIDTH); I2++)
      {
         __agen A2;

         VoutU =  0;
         VoutV =  0;

         for (int I3 = 0; I3 < coefh; I3++)
         {
            for (int I4 = 0; I4 < coefw; I4++)
            {
               __agen A0, A1;
*/
               /*----------------------------------------------------*/
               /* Skip by 2 in the horizontal direction to get to    */
               /* next U pixel.                                      */
               /*----------------------------------------------------*/
/*
               A0  = I1 * lofst * ELEMSZ_UV + I2 * VECTORSZ_UV +
                     I3 * lofst * ELEMSZ_UV + I4 * 2 * ELEMSZ_UV;

               (VinU, VinV) = UVdata_ptr[A0].deinterleave();

               A1    = I3 * COEF_LINESZ + I4 * COEF_ELEMSZ;
               Vcoef = coef_ptr[A1].onept();

               VoutU += VinU * Vcoef;
               VoutV += VinV * Vcoef;
            }
         }

         A2 = I1 * (blkw) * OUT_UV_ELEMSZ + (I2 * VCOP_2SIMD_WIDTH * OUT_UV_ELEMSZ);

         UVout_ptr[A2].interleave() = (VoutU, VoutV).round(rnd_bits).saturate(0,255);
      }
   }
}
*/

/*-----------------------------------------------------------------*/
/* End of file: vcop_fir_2D_unschar_intlv_kernel.k                 */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                       */
/*=================================================================*/
