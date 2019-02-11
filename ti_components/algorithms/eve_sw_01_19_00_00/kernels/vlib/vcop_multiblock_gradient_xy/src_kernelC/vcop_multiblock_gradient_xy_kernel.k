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
/* NAME: vcop_multiblock_gradient_xy_kernel.k                               */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing gradients along X and Y directions*/
/* of multiple input blocks corresponding to diferent feature or key point  */
/*                                                                          */
/* Multi Block Gradient Kernel accepts an 8-bit input image with stride     */
/* equal to "inputStride" and outputs 16-bit gradients along X and          */
/* Y directions in interleaved format for 'numBlocks' wherein each block is */
/* of dimension,(blkWidth) x (blkHeight). blkOffset denotes the inter block */
/* offset which implies distance between first pixel of Blk(n) and Blk(n-1) */
/*                                                                          */
/*  pIn_A - Input Image Data:                                               */
/*                             inputStride                                  */
/*          <------------------------------------------------------->       */
/*           _______________________________________________________        */
/*          |      |      |      |                    | Blk(        |       */
/*          |Blk(0)|Blk(1)|Blk(2)| ...................|numBlocks -1)|       */
/*          |______|______|______|____________________|_____________|       */
/*          <------>                                                        */
/*          blkOffset                                                       */
/*                                                                          */
/*pIntlvGradXY_B - Interleaved Gradient XY (GradX, GradY are 16 bit outputs)*/
/*                                                                          */
/*                        (blkWidth)*2*2bytes                               */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |GradX0GradY0 .....     |                           */
/*      (blkHeight)     |        Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |        Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |  Blk(numBlocks-1)     |                           */
/*                      |_______________________|                           */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Input image is of 8-bit                                             */
/*   2. pIntlvGradXY_B allocation should be at least the following:         */
/*      -> numBlocks * 4 * (blkWidth)*(blkHeight)                           */
/*           + numBlocks * 4 * (8 - ((blkWidth)%8)) bytes                   */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. (blkWidth) is multiple of 8                                         */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_multiblock_gradient_xy:                                           */
/*   - ~ (6/3)*(1/8)(blkWidth)* numBlocks * (blkHeight)                     */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*pIn_A)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_multiblock_gradient_xy
(
    __vptr_uint8   pIn_A,
    __vptr_int16   pIntlvGradXY_B,
    unsigned short inputStride,
    unsigned short blkWidth,
    unsigned short blkHeight,
    unsigned short blkOffset,
    unsigned short numBlocks
)
{
    __vector VinT;               //Top pixel
    __vector VinL;               //Left pixel
    __vector VinR;               //Right pixel
    __vector VinB;               //Bottom pixel
    __vector VgX;                //GradX
    __vector VgY;                //GradY
    __agen Addr1,Addr2;

    for (int I1 = 0; I1 < blkHeight; I1++)
    {
        for (int I2 = 0; I2 < numBlocks; I2++)
        {
           for (int I3 = 0; I3 < (blkWidth+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
           {

               Addr1 = I1*inputStride*ELEMSZ + I2*blkOffset*ELEMSZ + I3*VECTORSZ;
               Addr2 = I1*(blkWidth)*4 + I2*((blkHeight)*(blkWidth) + ((blkWidth+7)/8)*8-blkWidth)*4 + I3*VECTORSZ*4;

               VinT = (pIn_A+1)              [Addr1];
               VinL = (pIn_A+inputStride)    [Addr1];
               VinR = (pIn_A+inputStride+2)  [Addr1];
               VinB = (pIn_A+2*inputStride+1)[Addr1];

               VgX = VinR - VinL;
               VgY = VinB - VinT;

               pIntlvGradXY_B[Addr2].interleave()   = (VgX,VgY);
          }
       }
   }
}
