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


/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb24_rgb : Test bench data                         */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit data in     */
/* the form of 8-bit "r", "g" and "b", and writes out seperate     */
/* 8-bit "r", 8-bit "g" and "b". The reason for having this        */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb24_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb24[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b". Since we are       */
/* packing 24-bit pixels in 32-bit memory, the actual size of      */
/* the input buffer "rgb24" is (3 * npixels) >> 2 and each of      */
/* the output buffers "r", "g" and "b" are of size "npixels".      */
/*                                                                 */
/*=================================================================*/
/*-----------------------------------------------------------------*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define K0                  0
#define K1                  1
#define K2                  2
#define K3                  3
#define K4                  4
#define K5                  5
#define K6                  6
#define K7                  7

/*----------------------------------------------------------------*/
/* Increment by 6 words for every 8 words we read. Therefore we   */
/* deduct 2, from IN_VECTORSZ. We write out 8 elements, at a      */
/* time.                                                          */
/*----------------------------------------------------------------*/

#define IN_ELEMSZ           sizeof(*rgb24)
#define IN_VECTORSZ         (IN_ELEMSZ * (VCOP_SIMD_WIDTH - 2))

#define OUT_ELEMSZ          sizeof(*r)
#define OUT_VECTORSZ        (OUT_ELEMSZ * VCOP_SIMD_WIDTH)

void vcop_rgb24_rgb
(
    __vptr_uint32  rgb24,
    __vptr_int8    rgbmask,
    unsigned int   npixels,
    __vptr_uint8   r,
    __vptr_uint8   g,
    __vptr_uint8   b
)
{
   __vector  Vr,    Vg;
   __vector  Vb;
   __vector  Vrm,   Vgm;
   __vector  Vbm,   Vrs;
   __vector  Vgs,   Vbs;


   /*------------------------------------------------------------*/
   /* We use an outer loop to load various masks to extract      */
   /* bytes.                                                     */
   /*------------------------------------------------------------*/

   __agen Addr_m = 0;

   Vrm = (rgbmask +  0)[Addr_m];
   Vgm = (rgbmask +  8)[Addr_m];
   Vbm = (rgbmask + 16)[Addr_m];

   for (int I0 = 0; I0 < 1; I0++)
   {
       /*--------------------------------------------------------*/
       /* We work on VCOP_SIMD_WIDTH elements at a time, load    */
       /* the values, using custom load so that each way has     */
       /* one pixel of "r", "g" or "b".                          */
       /*--------------------------------------------------------*/

       for (int I1 = 0; I1 < (npixels/VCOP_SIMD_WIDTH); I1++)
       {
            __agen Addr_in;
            __agen Addr_out;

            Addr_in  = I1 * IN_VECTORSZ;
            Addr_out = I1 * OUT_VECTORSZ;

            Vr       = rgb24[Addr_in].dist(K0, K0, K1, K2, K3, K3, K4, K5);
            Vg       = rgb24[Addr_in].dist(K0, K1, K1, K2, K3, K4, K4, K5);
            Vb       = rgb24[Addr_in].dist(K0, K1, K2, K2, K3, K4, K5, K5);

            /*---------------------------------------------------*/
            /* The shift amounts to be applied are as follows:   */
            /*                                                   */
            /* R:  0 24 16  8   0 24  16   8                     */
            /* G:  8 0  24 16   8  0  16  24                     */
            /* B: 16 8   0 24  16  8   0  24                     */
            /*---------------------------------------------------*/

            Vrs      = (Vr << Vrm);
            Vgs      = (Vg << Vgm);
            Vbs      = (Vb << Vbm);

            r[Addr_out]  = Vrs;
            g[Addr_out]  = Vgs;
            b[Addr_out]  = Vbs;
        }
    }
}


/*------------------------------------------------------------------*/
/*  End of file: vcop_mpy_32x32_to_64_kernel.k                      */
/* -----------------------------------------------------------------*/
/*             Copyright (c) 2012 Texas Instruments, Incorporated.  */
/*                            All Rights Reserved.                  */
/* =================================================================*/



