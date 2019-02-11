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
/* NAME: vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel.k            */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing bilinear interpolated image pixels*/
/* of multiple input blocks corresponding to diferent feature or key point  */
/*                                                                          */
/* Multi Block Bilinear Interpolation Kernel using repeat loop accepts a    */
/* list of pointers denoting the start pixel of the 7x7 neighborhood window */
/* within each input block corresponding to each key point, each input block*/ 
/* consists of 8-bit input pixels with stride equal to "input1Stride". It   */
/* also takes pre-computed bilinear weights for each key point or input     */
/* block and outputs 8-bit bilinear interpolated pixels for each output     */
/* block corresponding to each key point of dimension,(outBlkWidth) x       */
/* (outBlkHeight).                                                          */
/* 7x7 neighboorhood window is being used here, due to SIMD alignment 8x7 is*/
/* recommended as outBlkWidth x outBlkHeight                                */
/*                                                                          */
/*  *pIn_A[] - List of pointers to processing block within each input block */
/*                             input1Stride                                 */
/*          <------------------------------------------------------->       */
/*           __________________________________________________________     */
/*          |                                                          |    */
/*          |          outBlkWidth                                     |    */
/*          | pIn_A[n]_____________                                    |    */
/*          |        |             |       Blk(n)                      |    */
/*          |        |             |                                   |    */
/*          |        |             | outBlkHeight                      |    */
/*          |        |_____________|                                   |    */
/*          |                                                          |    */
/*          |                                                          |    */
/*          |                                                          |    */
/*          |                                                          |    */
/*          |__________________________________________________________|    */
/*                                                                          */
/*pOutBilinearInterpImg_C - 8-bit bilinear interpolated image pixels output */
/*                                                                          */
/*                            (outBlkWidth) bytes                           */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (outBlkHeight)  |        Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |        Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |  Blk(numKeyPoints-1)  |                           */
/*                      |_______________________|                           */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Input image is of 8-bit                                             */
/*   2. pOutBilinearInterpImg_C allocation should be at least the following:*/
/*      -> numKeyPoints * (outputStride)*(outBlkHeight)                     */
/*   3. input2Stride >= numKeyPoints                                        */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. (outBlkWidth) is multiple of 8                                      */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_foreach_multiblock_bilinear_interp_7x7_u8:                        */
/*   - ~ (4/8)*(outBlkWidth)* numKeyPoints * (outBlkHeight)                 */
/*    + Overhead of repeat loop for each key point                          */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define WGT_ELEMSZ          (2)
#define ELEMSZ              (1)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define MAX_KEY_POINTS  (16)

void vcop_foreach_multiblock_bilinear_interp_7x7_u8
(
    __vptr_uint8_arr    pIn_A,                
    __vptr_uint16_arr   pInpWts_B,              
    __vptr_uint8_arr    pOutBilinearInterpImg_C,
    unsigned short      input1Stride,         
    unsigned short      input2Stride,         
    unsigned short      outputStride,         
    unsigned short      outBlkWidth,          
    unsigned short      outBlkHeight,         
    unsigned short      shiftValue,
    unsigned short      numKeyPoints
)
{
    __vector Vwt0, Vwt1, Vwt2, Vwt3;          //Bilinear weights needed for bilinear interpolation
    __vector Vpix00, Vpix01, Vpix10, Vpix11;  //2x2 neigbhorhood pixels required for bilinear interpolation
    __vector Vout;                            //Output vectors to hold intermediate outputs
    __agen AddrWt,AddrPix, AddrOut;           //Address generators for inputs and output

#define ROW1 pIn_A[I0]

    foreach(I0, numKeyPoints, MAX_KEY_POINTS)
    {
        AddrWt = 0;

        //Load the precomputed bilinear weights for the given input block
        //corresponding to given key point
        Vwt0 = pInpWts_B[I0][AddrWt].onept();
        Vwt1 = (pInpWts_B[I0] + 1*input2Stride*WGT_ELEMSZ)[AddrWt].onept();
        Vwt2 = (pInpWts_B[I0] + 2*input2Stride*WGT_ELEMSZ)[AddrWt].onept();
        Vwt3 = (pInpWts_B[I0] + 3*input2Stride*WGT_ELEMSZ)[AddrWt].onept();

        for (int I2 = 0; I2 < outBlkHeight; I2++)
        {
           for (int I3 = 0; I3 < (outBlkWidth+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
           {
               AddrPix = I2*input1Stride*ELEMSZ + I3*VECTORSZ;
               AddrOut = I2*outputStride*ELEMSZ + I3*VECTORSZ;

               //Load the 2x2 neighborhood pixels for computing bilinear interpolated output
               Vpix00 = (ROW1)                          [AddrPix].npt();
               Vpix01 = (ROW1 + ELEMSZ)                 [AddrPix].npt();
               Vpix10 = (ROW1 + input1Stride*ELEMSZ)    [AddrPix].npt();
               Vpix11 = (ROW1 + (input1Stride+1)*ELEMSZ)[AddrPix].npt();

               //Compute partial products of first column pixels with corresponding weights
               Vout  = Vwt3 * Vpix00;
               Vout += Vwt1 * Vpix10;

               //Compute partial products of second column pixels with corresponding weights
               Vout += Vwt2 * Vpix01;
               Vout += Vwt0 * Vpix11;

               pOutBilinearInterpImg_C[I0][AddrOut].npt()   = Vout.truncate(shiftValue);
          }
       }
   }
}
