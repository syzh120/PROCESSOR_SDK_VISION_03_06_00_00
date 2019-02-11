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

/*--------------------------------------------------------------------------*/
/* NAME: vcop_multiblock_bilinear_interp_intlv_7x7_s16_kernel.k             */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing bilinear interpolated gradient    */
/* pixels of multiple input blocks corresponding to diferent feature or key */
/* point                                                                    */
/*                                                                          */
/* Multi Block Bilinear Interpolation Kernel accepts a 16-bit input gradient*/
/* image with Gradient along X and Y directions being stored in interleaved */
/* format with stride equal to "input1Stride", pre-computed bilinear weights*/
/* for each key point or input block and compute 16bit bilinear interpolated*/
/* pixels of Gradient along X and Y directions for each output block        */
/* corresponding to each key point of dimension,(blkWidth) x (blkHeight).   */
/* blkOffset denotes the inter block offset which implies distance between  */
/* first pixel of Blk(n) and Blk(n-1). 7x7 neighboorhood window is being    */
/* used here, due to SIMD alignment 8x7 is recommended as blkWidth x        */
/* blkHeight                                                                */
/*                                                                          */
/* pIntlvGradXY_A - 16 bit interleaved gradient input pixel data:           */
/*                                                                          */
/* NOTE: blkOffset = input1Stride * Inp_Blk_Height pixels                   */
/*                          input1Stride pixels                             */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (Inp_Blk_Height)|     Inp Blk(0)        |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |     Inp Blk(1)        |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |Inp Blk(numKeyPoints-1)|                           */
/*                      |_______________________|                           */
/*                                                                          */
/* pGradXBilinearInterpImg_B - 16-bit bilinear interpolated pixels          */
/* corresponding to odd pixels of interleaved input pixel data              */
/* pGradYBilinearInterpImg_C - 16-bit bilinear interpolated pixels          */
/* corresponding to even pixels of interleaved input pixel data             */
/*                                                                          */
/*                        (outputStride) pixels                             */
/*                      <----------------------->                           */
/*                      <---blkWidth--->                                    */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (blkHeight)     |    Out Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |    Out Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |Out Blk(numKeyPoints-1)|                           */
/*                      |_______________________|                           */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Input image is of signed 16 bit such as gradient along X or Y       */
/*   2. pGradXBilinearInterpImg_B & pGradYBilinearInterpImg_C allocation    */
/*      should be at least the following:                                   */
/*      -> numKeyPoints * (outputStride)*(blkHeight)                        */
/*   3. input2Stride >= numKeyPoints                                        */
/*   4. blkOffset/input1Stride >= blkHeight+1                               */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. blkWidth is multiple of 8                                           */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_multiblock_bilinear_interp_intlv_7x7_s16:                         */
/*   - ~ (4/8)*(blkWidth)* numKeyPoints * (blkHeight)                       */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*pIntlvGradXY_A)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define ELEMSZWT        sizeof(*pInpWts_X)

void vcop_multiblock_bilinear_interp_intlv_7x7_s16
(
    __vptr_int16       pIntlvGradXY_A,
    __vptr_uint16      pInpWts_X,
    __vptr_int16       pGradXBilinearInterpImg_B,
    __vptr_int16       pGradYBilinearInterpImg_C,
    unsigned short     input1Stride,
    unsigned short     input2Stride,
    unsigned short     outputStride,
    unsigned short     blkWidth,
    unsigned short     blkHeight,
    unsigned short     blkOffset,
    unsigned short     shiftValue,
    unsigned short     numKeyPoints
)
{
    __vector Vwt0, Vwt1, Vwt2, Vwt3;                              //Bilinear weights needed for bilinear interpolation
    __vector Vpix00_Odd, Vpix01_Odd, Vpix10_Odd, Vpix11_Odd;      //Odd 2x2 neigbhorhood pixels required for bilinear interpolation
    __vector Vpix00_Even, Vpix01_Even, Vpix10_Even, Vpix11_Even;  //Even 2x2 neigbhorhood pixels required for bilinear interpolation
    __vector VgradX, VgradY;                                      //Output vectors to hold Gradient X and Gradient Y interpolated outputs
    __agen AddrWt,AddrPix, AddrOut;                               //Address generators for inputs and output

    for (int I1 = 0; I1 < numKeyPoints; I1++)
    {
        AddrWt = I1*ELEMSZWT;

        //Load the precomputed bilinear weights for the given input block
        //corresponding to given key point
        Vwt0 = pInpWts_X[AddrWt].onept();
        Vwt1 = (pInpWts_X + 1*input2Stride*ELEMSZWT)[AddrWt].onept();
        Vwt2 = (pInpWts_X + 2*input2Stride*ELEMSZWT)[AddrWt].onept();
        Vwt3 = (pInpWts_X + 3*input2Stride*ELEMSZWT)[AddrWt].onept();

        for (int I2 = 0; I2 < blkHeight; I2++)
        {
           for (int I3 = 0; I3 < (blkWidth+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
           {
               AddrPix = I1*blkOffset*ELEMSZ + I2*input1Stride*ELEMSZ + I3*2*VECTORSZ;
               AddrOut = I1*outputStride*blkHeight*ELEMSZ + I2*outputStride*ELEMSZ + I3*VECTORSZ;

               //Load the 2x2 neighborhood pixels for computing bilinear interpolated output
               (Vpix00_Odd, Vpix00_Even)  = (pIntlvGradXY_A)                          [AddrPix].deinterleave();
               (Vpix01_Odd, Vpix01_Even)  = (pIntlvGradXY_A + 2*ELEMSZ)               [AddrPix].deinterleave();
               (Vpix10_Odd, Vpix10_Even)  = (pIntlvGradXY_A + input1Stride*ELEMSZ)    [AddrPix].deinterleave();
               (Vpix11_Odd, Vpix11_Even)  = (pIntlvGradXY_A + (input1Stride+2)*ELEMSZ)[AddrPix].deinterleave();

               //Compute partial products of first row & first column pixel with corresponding weights
               VgradX   = Vwt3 * Vpix00_Odd;
               VgradY   = Vwt3 * Vpix00_Even;

               //Compute partial products of first row & second column pixel with corresponding weights
               VgradX  += Vwt2 * Vpix01_Odd;
               VgradY  += Vwt2 * Vpix01_Even;

               //Compute partial products of second row & first column pixel with corresponding weights
               VgradX  += Vwt1 * Vpix10_Odd;
               VgradY  += Vwt1 * Vpix10_Even;

               //Compute partial products of second row & second column pixel with corresponding weights
               VgradX  += Vwt0 * Vpix11_Odd;
               VgradY  += Vwt0 * Vpix11_Even;

               //Compute the final blinear interpolated pixel output, need to truncate it during store
               //to normalize it to 8-bit data
               pGradXBilinearInterpImg_B[AddrOut].npt()   = VgradX.truncate(shiftValue);
               pGradYBilinearInterpImg_C[AddrOut].npt()   = VgradY.truncate(shiftValue);
          }
       }
   }
}
