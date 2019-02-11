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
/* NAME: vcop_weight_computation_kernel.k                                   */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing bilinear weights that is required */
/* during bilinear interpolation of a given image or gradient image         */
/*                                                                          */
/* Weight computation kernel accepts the (X,Y) coordinate pair list for each*/
/* key point and outputs four 8-bit weights for each key point that would be*/
/* applied over 2x2 neighborhood pixels during bilinear interpolation       */
/* The dimension of output is (numKeyPoints x 4)                            */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. X, Y coordinates are of 16 bit and are in interleaved fashion       */
/*   2. pOutWts_B allocation should be at least the following:              */
/*      -> (outputStride x 4) wherein outputStride >= numKeyPoints          */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_weight_computation:                                               */
/*   - ~ (5/8)(numKeyPoints)                                                */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pXYList_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pOutWts_B)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)

void vcop_weight_computation
(
    __vptr_uint16  pXYList_A,
    __vptr_uint16   pOutWts_B,
    unsigned short numKeyPoints,
    unsigned short qFormatMaxFactor,
    unsigned short truncateBits,
    unsigned short outputStride
)
{
    __vector Vwt0, Vwt1, Vwt2, Vwt3;     //Bilinear weights that would be applied on 2x2 neighborhood pixels during bilinear interpolation
    __vector Vx, Vy;                     //Denotes the X & Y coordinates in Q format as specified by qFormatMaxFactor
    __vector VxFrac, VyFrac;             //Fractional part of the X & Y coordinates in Q format specified by qFormatMaxFactor
    __vector VQFt_xFrac, VQFt_yFrac;     //Delta between the Max Q format value and the fractional part of the X & Y coordinates respectively
    __vector VqFormat;                   //Denotes the maximum value allowed for the given Q format
                                         //Example: Q4 format => (2^4 - 1) = 15 is maximum value
    __agen AddrIn, AddrOut;              //Address generators for input and output buffers

    VqFormat = qFormatMaxFactor;

    for (int I1 = 0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I1++)
    {
       AddrIn  = 2*I1*INP_VECTORSZ;
       AddrOut = I1*OUT_VECTORSZ;
       //Deinterleaving loading of the (X,Y) coordinate pair list
       (Vx, Vy) =  pXYList_A[AddrIn].deinterleave();

       //Get the fractional part from (X,Y) which is in Q format
       VxFrac = Vx & VqFormat;
       VyFrac = Vy & VqFormat;

       //Compute the difference between the maximum and the fractional parts of X & Y for given Q format
       VQFt_xFrac = VqFormat - VxFrac;
       VQFt_yFrac = VqFormat - VyFrac;

       //Compute the weights for the 2x2 neighboorhood pixels which are used during bilinear interpolation
       Vwt0  = VxFrac * VyFrac;
       Vwt1  = VQFt_xFrac * VyFrac;

       Vwt2  = VxFrac * VQFt_yFrac;
       Vwt3  = VQFt_xFrac * VQFt_yFrac;

        //Store the bilinear weights for each key point
         pOutWts_B[AddrOut]                              = Vwt0.truncate(truncateBits);
        (pOutWts_B +   outputStride*OUT_ELEMSZ)[AddrOut] = Vwt1.truncate(truncateBits);
        (pOutWts_B + 2*outputStride*OUT_ELEMSZ)[AddrOut] = Vwt2.truncate(truncateBits);
        (pOutWts_B + 3*outputStride*OUT_ELEMSZ)[AddrOut] = Vwt3.truncate(truncateBits);
   }
}
