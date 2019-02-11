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
/* NAME : vcop_rgb16_rgb                                           */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit data in     */
/* the form of 5-5-5-bits or 5-6-5 bits "r", "g" and "b", and      */
/* writes out seperate 8-bit "r", 8-bit "g" and "b". The reason    */
/* for having this function, is to allow the vector core to work   */
/* in it's natural format of looking at similar data together,     */
/* rather than diverse data.                                       */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb16_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb16[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b".                    */
/*                                                                 */
/* PERFORMANCE                                                     */
/* 3/16 cyc/pix for R,G and B planes                               */
/*                                                                 */
/*=================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define VCOP_2SIMD_WIDTH     (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN            sizeof( *rgb16 )
#define VECTORSZ_IN          (VCOP_2SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_RGB           sizeof( *r )
#define VECTORSZ_RGB         (VCOP_2SIMD_WIDTH * ELEMSZ_RGB)


/* * * * * * * * * * * * * * * * * * * * */


void vcop_rgb555_rgb
(
   __vptr_uint16   rgb16,
    unsigned int   npixels,
    __vptr_uint8   r,
    __vptr_uint8   g,
    __vptr_uint8   b
)
{
    __vector Vin1, Vin2;
    __vector Vr1, Vg1, Vb1;
    __vector Vr2, Vg2, Vb2;
    __vector V1F, V3E0, V7C00;

    /*-------------------------------------------------------------------*/
    /* RGB555 pattern and corresponding masks:                           */
    /* 0 b b b | b b g g | g g g b | b b b b                             */
    /*-------------------------------------------------------------------*/

    V1F   = 0x1F;
    V3E0  = 0x3E0;
    V7C00 = 0x7C00;

    for (int I1 = 0; I1 < npixels/VCOP_2SIMD_WIDTH; I1++)
    {
        __agen inAddr, outAddr;

         inAddr  =  I1 * VCOP_2SIMD_WIDTH * ELEMSZ_IN;
        outAddr  =  I1 * VCOP_2SIMD_WIDTH * ELEMSZ_RGB;

        (Vin1, Vin2) = rgb16[inAddr].deinterleave();

        Vr1 = (Vin1 & V1F);
        Vg1 = (Vin1 & V3E0);
        Vb1 = (Vin1 & V7C00);

        Vr2 = (Vin2 & V1F);
        Vg2 = (Vin2 & V3E0);
        Vb2 = (Vin2 & V7C00);

        r[outAddr].interleave() = (Vr1, Vr2);
        g[outAddr].interleave() = (Vg1, Vg2).round(5);
        b[outAddr].interleave() = (Vb1, Vb2).round(10);

    }
}



void vcop_rgb565_rgb
(
   __vptr_uint16   rgb16,
    unsigned int   npixels,
    __vptr_uint8   r,
    __vptr_uint8   g,
    __vptr_uint8   b
)
{
    __vector Vin1, Vin2;
    __vector Vr1, Vg1, Vb1;
    __vector Vr2, Vg2, Vb2;
    __vector V1F, V7E0, VF800;

    /*-------------------------------------------------------------------*/
    /* RGB565 pattern and corresponding masks:                           */
    /* b b b b | b g g g | g g g b | b b b b                             */
    /*-------------------------------------------------------------------*/

    V1F   = 0x1F;
    V7E0  = 0x7E0;
    VF800 = 0xF800;

    for (int I1 = 0; I1 < npixels/VCOP_2SIMD_WIDTH; I1++)
    {
        __agen inAddr, outAddr;

         inAddr  =  I1 * VCOP_2SIMD_WIDTH * ELEMSZ_IN;
        outAddr  =  I1 * VCOP_2SIMD_WIDTH * ELEMSZ_RGB;

        (Vin1, Vin2) = rgb16[inAddr].deinterleave();

        Vr1 = (Vin1 & V1F);
        Vg1 = (Vin1 & V7E0);
        Vb1 = (Vin1 & VF800);

        Vr2 = (Vin2 & V1F);
        Vg2 = (Vin2 & V7E0);
        Vb2 = (Vin2 & VF800);

        r[outAddr].interleave() = (Vr1, Vr2);
        g[outAddr].interleave() = (Vg1, Vg2).round(5);
        b[outAddr].interleave() = (Vb1, Vb2).round(11);

    }
}

/* * * * * * * * * * * * * * * * * * * * */
