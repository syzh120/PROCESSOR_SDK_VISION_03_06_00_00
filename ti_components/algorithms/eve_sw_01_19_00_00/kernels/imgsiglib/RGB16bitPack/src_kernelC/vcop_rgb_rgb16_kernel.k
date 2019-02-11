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
/* NAME : vcop_rgb_rgb16 : Test bench data                         */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb_rgb16" accepts un-packed data in         */
/* the form of packed 16-bit "r", "g" and "b" with 5-bits each,    */
/* resulting in RGB555 or RGB565 data.                             */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb_rgb555                                            */
/* (                                                               */
/*     __vptr_uint32  rgb,                                         */
/*     __vptr_int8    rgbmask,                                     */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  rgb555                                       */
/*  );                                                             */
/*                                                                 */
/* void vcop_rgb_rgb565                                            */
/* (                                                               */
/*     __vptr_uint32  rgb,                                         */
/*     __vptr_int8    rgbmask,                                     */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  rgb565                                       */
/*  );                                                             */
/*                                                                 */
/* The function "vcop_rgb_rgb16" accepts unpacked "r", "g"         */
/* and "b" data, for "npixels" pixels, and writes packed 16-bit    */
/* RGB555 or RGB565 data.                                          */
/*                                                                 */
/* PERFORMANCE                                                     */
/* 4/8 cyc/pix                                                     */
/*                                                                 */
/*=================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN           (sizeof( *rgb ))
#define VECTORSZ_IN         ((VCOP_SIMD_WIDTH - 2) * ELEMSZ_IN)

#define ELEMSZ_OUT555       sizeof( *rgb555 )
#define VECTORSZ_OUT555     (VCOP_SIMD_WIDTH * ELEMSZ_OUT555)

#define ELEMSZ_OUT565       sizeof( *rgb565 )
#define VECTORSZ_OUT565     (VCOP_SIMD_WIDTH * ELEMSZ_OUT565)

#define K0                  0
#define K1                  1
#define K2                  2
#define K3                  3
#define K4                  4
#define K5                  5
#define K6                  6
#define K7                  7
#define K8                  8

/* * * * * * * * * * * * * * * * * * * * */

void vcop_rgb_rgb555
(
    __vptr_uint32  rgb,
    __vptr_int8    rgbmask,
    unsigned int   npixels,
    __vptr_uint16  rgb555
)
{
    __vector Vr, Vg, Vb, Vtmp, Vrgb;
    __vector Vrs, Vgs, Vbs;
    __vector VRm, VGm, VBm;
    __vector S5, S10;
    __vector mask5;

    S5    =    5;
    S10   =   10;
    mask5 = 0x1F;

   /*------------------------------------------------------------*/
   /* We use an outer loop to load various masks to extract      */
   /* bytes.                                                     */
   /*------------------------------------------------------------*/

   for (int I0 = 0; I0 < 1; I0++)
   {
       __agen Addr_m = I0;

       VRm  =  (rgbmask +  0)[Addr_m];
       VGm  =  (rgbmask +  8)[Addr_m];
       VBm  =  (rgbmask + 16)[Addr_m];

       /*---------------------------------------------------------*/
       /* We work on VCOP_SIMD_WIDTH elements at a time, load     */
       /* the values, using custom load so that each way has      */
       /* one pixel of "R", "G" or "B".                           */
       /*---------------------------------------------------------*/

       for (int I1 = 0; I1 < (npixels/VCOP_SIMD_WIDTH); I1++)
       {
            __agen Addr_in;
            __agen Addr_out;

            Addr_in  = I1 * VECTORSZ_IN;
            Addr_out = I1 * VECTORSZ_OUT555;

            Vr  =  rgb[Addr_in].dist(K0, K0, K1, K2, K3, K3, K4, K5);
            Vg  =  rgb[Addr_in].dist(K0, K1, K1, K2, K3, K4, K4, K5);
            Vb  =  rgb[Addr_in].dist(K0, K1, K2, K2, K3, K4, K5, K5);

            /*---------------------------------------------------*/
            /* The shift amounts to be applied are as follows:   */
            /*                                                   */
            /* R:  0 24  16  8  0 24  16   8                     */
            /* G:  8  0  24 16  8  0  24  16                     */
            /* B: 16  8   0 24 16  8   0  24                     */
            /*---------------------------------------------------*/

            Vrs  =  (Vr << VRm);
            Vgs  =  (Vg << VGm);    // 1

            Vbs  =  (Vb << VBm);

            /*---------------------------------------------------*/
            /* RGB555 pattern and corresponding masks:           */
            /* 0 b b b | b b g g | g g g r | r r r r             */
            /*---------------------------------------------------*/

            Vrgb  =  (Vrs & mask5); // 2

            Vgs   =  (Vgs & mask5);
            Vrgb |=  (Vgs << S5);   // 3

            Vbs   =  (Vbs & mask5);
            Vrgb |=  (Vbs << S10);  // 4

            rgb555[Addr_out].npt() = Vrgb;

        }
    }
}



void vcop_rgb_rgb565
(
   __vptr_uint32  rgb,
    __vptr_int8   rgbmask,
    unsigned int  npixels,
   __vptr_uint16  rgb565
)
{
    __vector Vr, Vg, Vb, Vtmp, Vrgb;
    __vector Vrs, Vgs, Vbs;
    __vector VRm, VGm, VBm;
    __vector S5, S11;
    __vector mask5, mask6;

    S5    =  5;
    S11   = 11;
    mask5 = 0x1F;
    mask6 = 0x3F;

   /*-------------------------------------------------------------*/
   /* We use an outer loop to load various masks to extract       */
   /* bytes.                                                      */
   /*-------------------------------------------------------------*/

   for (int I0 = 0; I0 < 1; I0++)
   {
       __agen Addr_m = I0;

       VRm  =  (rgbmask +  0)[Addr_m];
       VGm  =  (rgbmask +  8)[Addr_m];
       VBm  =  (rgbmask + 16)[Addr_m];

       /*---------------------------------------------------------*/
       /* We work on VCOP_SIMD_WIDTH elements at a time, load     */
       /* the values, using custom load so that each way has      */
       /* one pixel of "R", "G" or "B".                           */
       /*---------------------------------------------------------*/

       for (int I1 = 0; I1 < (npixels/VCOP_SIMD_WIDTH); I1++)
       {
            __agen Addr_in;
            __agen Addr_out;

            Addr_in  = I1 * VECTORSZ_IN;
            Addr_out = I1 * VECTORSZ_OUT565;

            Vr  =  rgb[Addr_in].dist(K0, K0, K1, K2, K3, K3, K4, K5);
            Vg  =  rgb[Addr_in].dist(K0, K1, K1, K2, K3, K4, K4, K5);
            Vb  =  rgb[Addr_in].dist(K0, K1, K2, K2, K3, K4, K5, K5);

            /*---------------------------------------------------*/
            /* The shift amounts to be applied are as follows:   */
            /*                                                   */
            /* R:  0 24  16  8  0 24  16   8                     */
            /* G:  8  0  24 16  8  0  24  16                     */
            /* B: 16  8   0 24 16  8   0  24                     */
            /*---------------------------------------------------*/

            Vrs  =  (Vr << VRm);
            Vgs  =  (Vg << VGm);    // 1

            Vbs  =  (Vb << VBm);

            /*---------------------------------------------------*/
            /* RGB565 pattern and corresponding masks:           */
            /* b b b b | b g g g | g g g r | r r r r             */
            /*---------------------------------------------------*/

            Vrgb  =  (Vrs & mask5); // 2

            Vgs   =  (Vgs & mask6);
            Vrgb |=  (Vgs << S5);   // 3

            Vbs   =  (Vbs & mask5);
            Vrgb |=  (Vbs << S11);  // 4

            rgb565[Addr_out].npt() = Vrgb;

        }
    }
}


/* * * * * * * * * * * * * * * * * * * * */
