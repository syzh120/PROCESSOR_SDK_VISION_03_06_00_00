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
/* ------------------------------------------------------------------------- */
/*  Register mappings for manual register allocations.                       */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* #defines for typecasting unsigned short as unsigned short.                */
/* ------------------------------------------------------------------------- */

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif
#define MAX_OUTPUT_VALUE (16383)
#define MIN_OUTPUT_VALUE (-16384)

#define VCOP_FFT_512_NPOINTS (512U)
#define VCOP_FFT_512_STAGE1_NUMBF_PER_GRP (128)
#define VCOP_FFT_512_STAGE1_NUMPT_PER_GRP (VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE1_NUM_GRPS      (1)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

void vcop_fft_512_16ix16o_stage_1
(
    __vptr_int16  pInput,
    __vptr_int16  pOutput,
    __vptr_int16  pTwiddleFactor,
    unsigned short    pitch,
    unsigned short    numOfLines,
    unsigned short    scale,
    unsigned short    saturationLimit)
{
    /*----------------------------------------------------------------------*/
    /* The first 3 stages of the FFT do the same processing, with the       */
    /* spacing adjusted between the four legs of the FFT, initially         */
    /* starting off with N/4, N/16, N/64 which for a 1024 pt FFT is         */
    /* 256, 64, and 16. We see the 3-loop structure of the FFT, where       */
    /* we have an outer loop with passes which is 3 out of 5 passes,        */
    /* 1, 4, 16 groups. In the first pass, there is no re-use of twiddle    */
    /* factors, next group we re-use the same twiddle factor 4 times,       */
    /* in the third stage we re-use the same twiddle factors 16-times.      */
    /*----------------------------------------------------------------------*/

    __vector VS1_76543210, VC1_76543210,VS2_76543210, VC2_76543210;
    __vector VS3_76543210, VC3_76543210;
    __vector VX0_76543210, VY0_76543210, VX1_76543210, VY1_76543210;
    __vector VX2_76543210, VY2_76543210, VX3_76543210, VY3_76543210;
    __vector Vxh0_76543210,  Vxl0_76543210, Vxh1_76543210,  Vxl1_76543210;
    __vector Vxh20_76543210, Vxl20_76543210, Vxh21_76543210, Vxl21_76543210;
    __vector V_x0r, Vxt2, Vxt1,  Vxt3;
    __vector V_y0i, Vyt2, Vyt3,  Vyt1;
    __vector V_x2r, V_y2i, V_x1r, V_y1i, V_x3r, V_y3i;

    for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
    {
      for (int I3 = 0; I3 < VCOP_FFT_512_STAGE1_NUM_GRPS; I3++)
      {
        for (int I4 = 0; I4 < VCOP_FFT_512_STAGE1_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
        {
          /*-----------------------------------------------------------*/
          /* Set up an address generation, two seperate ones, one for  */
          /* input, and one for twiddle factors.                       */
          /*-----------------------------------------------------------*/

          __agen  Addr_in = lineIdx * pitch +
                  I3 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pInput) * 2 * VCOP_SIMD_WIDTH;

          __agen  Addr_out = lineIdx * sizeof(*pInput) * VCOP_FFT_512_NPOINTS * 2 +
                              I3 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * 4  +
                              I4 * sizeof(*pInput) * 2 * VCOP_SIMD_WIDTH;


          __agen  Addr_tw = I4 * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH  * 3;


          /*-----------------------------------------------------------*/
          /*  Read the complex input and de-interleave into real and   */
          /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
          /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
          /*  in parallel.                                             */
          /*                                                           */
          /*  x_0    = x;       x_1 = x[1];                         */
          /*  x_2    = x[2];       x_3 = x[3];                         */
          /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
          /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
          /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
          /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
          /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
          /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
          /*                                                           */
          /*  Convention here is to denote the four input legs of the  */
          /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
          /*  CS1, CS2 and CS3.                                        */
          /*-----------------------------------------------------------*/

          (VS1_76543210, VC1_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();
          (VS2_76543210, VC2_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 1)[Addr_tw].deinterleave();
          (VS3_76543210, VC3_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 2)[Addr_tw].deinterleave();


          (VX0_76543210, VY0_76543210) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 0 )[Addr_in].deinterleave();
          (VX1_76543210, VY1_76543210) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 1 )[Addr_in].deinterleave();
          (VX2_76543210, VY2_76543210) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 2 )[Addr_in].deinterleave();
          (VX3_76543210, VY3_76543210) =  (pInput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 3 )[Addr_in].deinterleave();

          /*------------------------------------------------------------*/
          /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
          /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
          /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
          /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
          /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
          /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
          /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
          /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
          /*                                                            */
          /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */
          /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
          /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
          /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
          /* -----------------------------------------------------------*/

          (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
          (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();

          (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
          (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

          /*------------------------------------------------------------*/
          /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
          /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
          /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
          /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
          /*                                                            */
          /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
          /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
          /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
          /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
          /*------------------------------------------------------------*/

          (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
          (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
          (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
          (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

          /*------------------------------------------------------------*/
          /* Perform twiddle factor multiplies of three terms,top       */
          /* term does not have any multiplies. Note the twiddle        */
          /* factors for a normal FFT are C + j (-S). Since the         */
          /* factors that are stored are C + j S, this is               */
          /* corrected for in the multiplies.                           */
          /*                                                            */
          /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
          /*                                                            */
          /* x0r = xt0;                                                 */
          /* y0i = yt0;                                                 */
          /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
          /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
          /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
          /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
          /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
          /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
          /*------------------------------------------------------------*/

          V_x2r  = (Vxt2 * VC2_76543210);
          V_y2i  = (Vyt2 * VC2_76543210);
          V_x2r += (Vyt2 * VS2_76543210);
          V_y2i -= (Vxt2 * VS2_76543210);

          V_x1r  = (Vxt1 * VC1_76543210);
          V_y1i  = (Vyt1 * VC1_76543210);
          V_x3r  = (Vxt3 * VC3_76543210);
          V_y3i  = (Vyt3 * VC3_76543210);

          V_x3r += (Vyt3 * VS3_76543210);
          V_y3i -= (Vxt3 * VS3_76543210);

          V_x1r += (Vyt1 * VS1_76543210);
          V_y1i -= (Vxt1 * VS1_76543210);

          /* -----------------------------------------------------------*/
          /*  Store the final results back to the input array.          */
          /*                                                            */
          /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
          /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
          /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
          /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
          /* -----------------------------------------------------------*/

          (pOutput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 0 )[Addr_out].interleave() = (V_x0r, V_y0i).round(scale).saturate(-saturationLimit, (saturationLimit - 1));
          (pOutput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 1 )[Addr_out].interleave() = (V_x1r, V_y1i).round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
          (pOutput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 2 )[Addr_out].interleave() = (V_x2r, V_y2i).round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
          (pOutput + VCOP_FFT_512_STAGE1_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 3 )[Addr_out].interleave() = (V_x3r, V_y3i).round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
        }
      }
    }
}

#define VCOP_FFT_512_STAGE2_NUMBF_PER_GRP (32)
#define VCOP_FFT_512_STAGE2_NUMPT_PER_GRP (VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE2_NUM_GRPS      (4)

void vcop_fft_512_16ix16o_stage_2
(
    __vptr_int16  pInput,
    __vptr_int16  pOutput,
    __vptr_int16  pTwiddleFactor,
    unsigned short    pitch,
    unsigned short    numOfLines,
    unsigned short    scale,
    unsigned short    saturationLimit)
{
    /*----------------------------------------------------------------------*/
    /* The first 3 stages of the FFT do the same processing, with the       */
    /* spacing adjusted between the four legs of the FFT, initially         */
    /* starting off with N/4, N/16, N/64 which for a 1024 pt FFT is         */
    /* 256, 64, and 16. We see the 3-loop structure of the FFT, where       */
    /* we have an outer loop with passes which is 3 out of 5 passes,        */
    /* 1, 4, 16 groups. In the first pass, there is no re-use of twiddle    */
    /* factors, next group we re-use the same twiddle factor 4 times,       */
    /* in the third stage we re-use the same twiddle factors 16-times.      */
    /*----------------------------------------------------------------------*/

    __vector VS1_76543210, VC1_76543210,VS2_76543210, VC2_76543210;
    __vector VS3_76543210, VC3_76543210;
    __vector VX0_76543210, VY0_76543210, VX1_76543210, VY1_76543210;
    __vector VX2_76543210, VY2_76543210, VX3_76543210, VY3_76543210;
    __vector Vxh0_76543210,  Vxl0_76543210, Vxh1_76543210,  Vxl1_76543210;
    __vector Vxh20_76543210, Vxl20_76543210, Vxh21_76543210, Vxl21_76543210;
    __vector V_x0r, Vxt2, Vxt1,  Vxt3;
    __vector V_y0i, Vyt2, Vyt3,  Vyt1;
    __vector V_x2r, V_y2i, V_x1r, V_y1i, V_x3r, V_y3i;

    for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
    {
      for (int I3 = 0; I3 < VCOP_FFT_512_STAGE2_NUM_GRPS; I3++)
      {
        for (int I4 = 0; I4 < VCOP_FFT_512_STAGE2_NUMBF_PER_GRP/VCOP_SIMD_WIDTH; I4++)
        {
          /*-----------------------------------------------------------*/
          /* Set up an address generation, two seperate ones, one for  */
          /* input, and one for twiddle factors.                       */
          /*-----------------------------------------------------------*/

          __agen  Addr_in = lineIdx * pitch +
                  I3 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4  +
                  I4 * sizeof(*pInput) * 2 * VCOP_SIMD_WIDTH;

          __agen  Addr_out = lineIdx * sizeof(*pInput) * VCOP_FFT_512_NPOINTS * 2 +
                              I3 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * 4  +
                              I4 * sizeof(*pInput) * 2 * VCOP_SIMD_WIDTH;


          __agen  Addr_tw = I4 * sizeof(*pTwiddleFactor) * 2 * VCOP_SIMD_WIDTH  * 3;


          /*-----------------------------------------------------------*/
          /*  Read the complex input and de-interleave into real and   */
          /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
          /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
          /*  in parallel.                                             */
          /*                                                           */
          /*  x_0    = x;       x_1 = x[1];                         */
          /*  x_2    = x[2];       x_3 = x[3];                         */
          /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
          /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
          /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
          /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
          /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
          /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
          /*                                                           */
          /*  Convention here is to denote the four input legs of the  */
          /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
          /*  CS1, CS2 and CS3.                                        */
          /*-----------------------------------------------------------*/

          (VS1_76543210, VC1_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0)[Addr_tw].deinterleave();
          (VS2_76543210, VC2_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 1)[Addr_tw].deinterleave();
          (VS3_76543210, VC3_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 2)[Addr_tw].deinterleave();


          (VX0_76543210, VY0_76543210) =  (pInput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 0 )[Addr_in].deinterleave();
          (VX1_76543210, VY1_76543210) =  (pInput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 1 )[Addr_in].deinterleave();
          (VX2_76543210, VY2_76543210) =  (pInput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 2 )[Addr_in].deinterleave();
          (VX3_76543210, VY3_76543210) =  (pInput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 3 )[Addr_in].deinterleave();

          /*------------------------------------------------------------*/
          /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
          /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
          /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
          /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
          /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
          /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
          /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
          /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
          /*                                                            */
          /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */
          /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
          /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
          /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
          /* -----------------------------------------------------------*/

          (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
          (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();

          (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
          (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

          /*------------------------------------------------------------*/
          /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
          /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
          /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
          /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
          /*                                                            */
          /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
          /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
          /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
          /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
          /*------------------------------------------------------------*/

          (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
          (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
          (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
          (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

          /*------------------------------------------------------------*/
          /* Perform twiddle factor multiplies of three terms,top       */
          /* term does not have any multiplies. Note the twiddle        */
          /* factors for a normal FFT are C + j (-S). Since the         */
          /* factors that are stored are C + j S, this is               */
          /* corrected for in the multiplies.                           */
          /*                                                            */
          /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
          /*                                                            */
          /* x0r = xt0;                                                 */
          /* y0i = yt0;                                                 */
          /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
          /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
          /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
          /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
          /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
          /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
          /*------------------------------------------------------------*/

          V_x2r  = (Vxt2 * VC2_76543210);
          V_y2i  = (Vyt2 * VC2_76543210);
          V_x2r += (Vyt2 * VS2_76543210);
          V_y2i -= (Vxt2 * VS2_76543210);

          V_x1r  = (Vxt1 * VC1_76543210);
          V_y1i  = (Vyt1 * VC1_76543210);
          V_x3r  = (Vxt3 * VC3_76543210);
          V_y3i  = (Vyt3 * VC3_76543210);

          V_x3r += (Vyt3 * VS3_76543210);
          V_y3i -= (Vxt3 * VS3_76543210);

          V_x1r += (Vyt1 * VS1_76543210);
          V_y1i -= (Vxt1 * VS1_76543210);

          /* -----------------------------------------------------------*/
          /*  Store the final results back to the input array.          */
          /*                                                            */
          /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
          /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
          /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
          /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
          /* -----------------------------------------------------------*/

          (pOutput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 0 )[Addr_out].interleave() = (V_x0r, V_y0i).round(scale).saturate(-saturationLimit, (saturationLimit - 1));
          (pOutput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 1 )[Addr_out].interleave() = (V_x1r, V_y1i).round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
          (pOutput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 2 )[Addr_out].interleave() = (V_x2r, V_y2i).round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
          (pOutput + VCOP_FFT_512_STAGE2_NUMBF_PER_GRP * sizeof(*pOutput) * 2 * 3 )[Addr_out].interleave() = (V_x3r, V_y3i).round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
        }
      }
    }
}


/*---------------------------------------------------------------------------*/
/* In stage 3, operations are similar to previous stages of 1..2. Even       */
/* though repeat loop can be leveraged for this stage as shown in ver1       */
/* and ver2, we break out, so that we can make the task of digit reversal    */
/* for free by purposefully writing results within a vector word further     */
/* apart, by using transpisition, as we will need to work on them in         */
/* later iterations.                                                         */
/*---------------------------------------------------------------------------*/

#define VCOP_FFT_512_STAGE3_NUMBF_PER_GRP (8)
#define VCOP_FFT_512_STAGE3_NUMPT_PER_GRP (VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE3_NUM_GRPS      (16)
#define VCOP_FFT_512_TRANSPOSE_STRIDE     ( 65 * sizeof(*pOutput) * 2)

void vcop_fft_512_16ix16o_stage_3
(

    __vptr_int16      pInput,
    __vptr_int16      pOutput,
    __vptr_int16      pTwiddleFactor,
    __vptr_uint16     pScatterOffset,
    unsigned short pitch,
    unsigned short numOfLines,
    unsigned short scale,
    unsigned short saturationLimit
)
{
  __vector VS1_76543210, VC1_76543210,VS2_76543210, VC2_76543210;
  __vector VS3_76543210, VC3_76543210;
  __vector VX0_76543210, VY0_76543210, VX1_76543210, VY1_76543210;
  __vector VX2_76543210, VY2_76543210, VX3_76543210, VY3_76543210;
  __vector Vxh0_76543210,  Vxl0_76543210, Vxh1_76543210,  Vxl1_76543210;
  __vector Vxh20_76543210, Vxl20_76543210, Vxh21_76543210, Vxl21_76543210;
  __vector V_x0r, Vxt2, Vxt1,  Vxt3;
  __vector V_y0i, Vyt2, Vyt3,  Vyt1;
  __vector V_x2r, V_y2i, V_x1r, V_y1i, V_x3r, V_y3i;
  __vector VScatterOffset;
  __agen addr0 = 0;

   VScatterOffset = pScatterOffset[addr0].npt();

   for (int lineIdx = 0; lineIdx  < numOfLines; lineIdx++)
   {
       for (int I3 = 0; I3 < 4; I3++)
       {
           for (int I4 = 0; I4 < 4; I4++)/* Group 0,1,2,3,*/
           {
             __agen  Addr_in = lineIdx * pitch +
                               I3 * 4 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP +
                               I4 * 1 * sizeof(*pInput) * 2 * VCOP_FFT_512_STAGE3_NUMPT_PER_GRP;

             __agen  Addr_ou = lineIdx * VCOP_FFT_512_TRANSPOSE_STRIDE * VCOP_FFT_512_STAGE3_NUMBF_PER_GRP +
                               I3 * 1 * sizeof(*pOutput) * 2 +
                               I4 * 4 * sizeof(*pOutput) * 2;

                 /* Duplicate twiddle factors are required because otherwise register allocation will fail */
             __agen Addr_tw = I4 * sizeof(*pTwiddleFactor) * 2 * 3 * VCOP_SIMD_WIDTH;


               /*-----------------------------------------------------------*/
               /*  Read the complex input and de-interleave into real and   */
               /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
               /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
               /*  in parallel.                                             */
               /*                                                           */
               /*  x_0    = x[0];       x_1 = x[1];                         */
               /*  x_2    = x[2];       x_3 = x[3];                         */
               /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
               /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
               /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
               /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
               /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
               /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
               /*                                                           */
               /*  Convention here is to denote the four input legs of the  */
               /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
               /*  CS1, CS2 and CS3.                                        */
               /*-----------------------------------------------------------*/

               (VS1_76543210, VC1_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0 )[Addr_tw].deinterleave();
               (VS2_76543210, VC2_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 1 )[Addr_tw].deinterleave();
               (VS3_76543210, VC3_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 2 )[Addr_tw].deinterleave();

               (VX0_76543210, VY0_76543210) =  (pInput + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 0)[Addr_in].deinterleave();
               (VX1_76543210, VY1_76543210) =  (pInput + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 1)[Addr_in].deinterleave();
               (VX2_76543210, VY2_76543210) =  (pInput + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 2)[Addr_in].deinterleave();
               (VX3_76543210, VY3_76543210) =  (pInput + VCOP_FFT_512_STAGE3_NUMBF_PER_GRP * sizeof(*pInput) * 2 * 3)[Addr_in].deinterleave();

               /*------------------------------------------------------------*/
               /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
               /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
               /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
               /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
               /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
               /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
               /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
               /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
               /*                                                            */
               /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */
               /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
               /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
               /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
               /* -----------------------------------------------------------*/

               (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
               (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();

               (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
               (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

               /*------------------------------------------------------------*/
               /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
               /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
               /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
               /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
               /*                                                            */
               /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
               /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
               /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
               /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
               /*------------------------------------------------------------*/

               (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
               (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
               (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
               (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

               /*------------------------------------------------------------*/
               /* Perform twiddle factor multiplies of three terms,top       */
               /* term does not have any multiplies. Note the twiddle        */
               /* factors for a normal FFT are C + j (-S). Since the         */
               /* factors that are stored are C + j S, this is               */
               /* corrected for in the multiplies.                           */
               /*                                                            */
               /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
               /*                                                            */
               /* x0r = xt0;                                                 */
               /* y0i = yt0;                                                 */
               /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
               /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
               /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
               /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
               /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
               /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
               /*------------------------------------------------------------*/

               V_x2r  = (Vxt2 * VC2_76543210);
               V_y2i  = (Vyt2 * VC2_76543210);
               V_x2r += (Vyt2 * VS2_76543210);
               V_y2i -= (Vxt2 * VS2_76543210);

               V_x1r  = (Vxt1 * VC1_76543210);
               V_y1i  = (Vyt1 * VC1_76543210);
               V_x3r  = (Vxt3 * VC3_76543210);
               V_y3i  = (Vyt3 * VC3_76543210);

               V_x1r += (Vyt1 * VS1_76543210);
               V_y1i -= (Vxt1 * VS1_76543210);
               V_x3r += (Vyt3 * VS3_76543210);
               V_y3i -= (Vxt3 * VS3_76543210);

               /* -----------------------------------------------------------*/
               /*  Store the final results back to output with transpoition. */
               /*                                                            */
               /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
               /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
               /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
               /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
               /* -----------------------------------------------------------*/

               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 0)[Addr_ou].p_scatter(VScatterOffset) = V_x0r.round(scale).saturate(-saturationLimit, (saturationLimit - 1));
               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 1)[Addr_ou].p_scatter(VScatterOffset) = V_x1r.round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 2)[Addr_ou].p_scatter(VScatterOffset) = V_x2r.round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 3)[Addr_ou].p_scatter(VScatterOffset) = V_x3r.round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));

               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 0 + sizeof(*pOutput))[Addr_ou].p_scatter(VScatterOffset) = V_y0i.round(scale).saturate(-saturationLimit, (saturationLimit - 1));
               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 1 + sizeof(*pOutput))[Addr_ou].p_scatter(VScatterOffset) = V_y1i.round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 2 + sizeof(*pOutput))[Addr_ou].p_scatter(VScatterOffset) = V_y2i.round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));
               (pOutput + VCOP_FFT_512_STAGE3_NUM_GRPS * sizeof(*pOutput) * 2 * 3 + sizeof(*pOutput))[Addr_ou].p_scatter(VScatterOffset) = V_y3i.round(scale + 15).saturate(-saturationLimit, (saturationLimit - 1));

           }
       }
   }
}

/*---------------------------------------------------------------------------*/
/* In stage 4, operations are similar to previous stages of 1..2. Even       */
/*---------------------------------------------------------------------------*/

#define VCOP_FFT_512_STAGE4_NUMBF_PER_GRP (2)
#define VCOP_FFT_512_STAGE4_NUMPT_PER_GRP (VCOP_FFT_512_STAGE4_NUMBF_PER_GRP * 4)
#define VCOP_FFT_512_STAGE4_NUM_GRPS      (64)
#define VCOP_FFT_512_STAGE4_OUTPUT_STRIDE (VCOP_FFT_512_STAGE4_NUM_GRPS * sizeof(*pOutput) * 2)

void vcop_fft_512_16ix16o_stage_4
(

    __vptr_int16      pInput,
    __vptr_int16      pOutput,
    __vptr_int16      pTwiddleFactor,
    unsigned short numOfLines,
    unsigned short scale,
    unsigned short saturationLimit
)

{
  __vector VS1_76543210, VC1_76543210,VS2_76543210, VC2_76543210;
  __vector VS3_76543210, VC3_76543210;
  __vector VX0_76543210, VY0_76543210, VX1_76543210, VY1_76543210;
  __vector VX2_76543210, VY2_76543210, VX3_76543210, VY3_76543210;
  __vector Vxh0_76543210,  Vxl0_76543210, Vxh1_76543210,  Vxl1_76543210;
  __vector Vxh20_76543210, Vxl20_76543210, Vxh21_76543210, Vxl21_76543210;
  __vector V_x0r, Vxt2, Vxt1,  Vxt3;
  __vector V_y0i, Vyt2, Vyt3,  Vyt1;
  __vector V_x2r, V_y2i, V_x1r, V_y1i, V_x3r, V_y3i;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I2 = 0; I2 < VCOP_FFT_512_STAGE4_NUM_GRPS/ VCOP_SIMD_WIDTH; I2++)
    {
      for (int I3 = 0; I3 < VCOP_FFT_512_STAGE4_NUMBF_PER_GRP; I3++)
      {

        __agen  Addr_in = lineIdx * VCOP_FFT_512_TRANSPOSE_STRIDE * VCOP_FFT_512_STAGE4_NUMPT_PER_GRP +
                                  I2 * VCOP_SIMD_WIDTH * sizeof(*pInput) * 2 +
                                  I3 * VCOP_FFT_512_TRANSPOSE_STRIDE;

        __agen  Addr_out = lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2+
                          I2 * VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 +
                          I3 * VCOP_FFT_512_STAGE4_OUTPUT_STRIDE;

        __agen  Addr_tw = I3 * 3 * sizeof(*pTwiddleFactor) * 2 *  VCOP_SIMD_WIDTH;
#if 0
        __agen  Addr_out = I4 * 1 * (2 * VCOP_SIMD_WIDTH * 4) +
                  I3 *  2 * (2 * VCOP_SIMD_WIDTH * 4) +
                  I2 * VCOP_SIMD_WIDTH * 2 * sizeof(*pOutput) +
                  lineIdx * 16 * 4 * 32;
#endif
        /*-----------------------------------------------------------*/
        /*  Read the complex input and de-interleave into real and   */
        /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
        /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
        /*  in parallel.                                             */
        /*                                                           */
        /*  x_0    = x[0];       x_1 = x[1];                         */
        /*  x_2    = x[2];       x_3 = x[3];                         */
        /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
        /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
        /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
        /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
        /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
        /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
        /*                                                           */
        /*  Convention here is to denote the four input legs of the  */
        /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
        /*  CS1, CS2 and CS3.                                        */
        /*-----------------------------------------------------------*/

        (VS1_76543210, VC1_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 0 )[Addr_tw].deinterleave();
        (VS2_76543210, VC2_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 1 )[Addr_tw].deinterleave();
        (VS3_76543210, VC3_76543210) =  (pTwiddleFactor + 8 * sizeof(*pTwiddleFactor) * 2 * 2 )[Addr_tw].deinterleave();

        (VX0_76543210, VY0_76543210) =  (pInput + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                                      VCOP_FFT_512_TRANSPOSE_STRIDE * 0 )[Addr_in].deinterleave();
        (VX1_76543210, VY1_76543210) =  (pInput + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                                      VCOP_FFT_512_TRANSPOSE_STRIDE * 1 )[Addr_in].deinterleave();
        (VX2_76543210, VY2_76543210) =  (pInput + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                                      VCOP_FFT_512_TRANSPOSE_STRIDE * 2 )[Addr_in].deinterleave();
        (VX3_76543210, VY3_76543210) =  (pInput + VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
                                      VCOP_FFT_512_TRANSPOSE_STRIDE * 3 )[Addr_in].deinterleave();

        /*------------------------------------------------------------*/
        /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
        /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
        /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
        /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
        /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
        /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
        /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
        /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
        /*                                                            */
        /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */
        /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
        /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
        /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
        /* -----------------------------------------------------------*/

        (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
        (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();

        (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
        (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

        /*------------------------------------------------------------*/
        /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
        /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
        /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
        /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
        /*                                                            */
        /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
        /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
        /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
        /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
        /*------------------------------------------------------------*/

        (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
        (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
        (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
        (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

        /*------------------------------------------------------------*/
        /* Perform twiddle factor multiplies of three terms,top       */
        /* term does not have any multiplies. Note the twiddle        */
        /* factors for a normal FFT are C + j (-S). Since the         */
        /* factors that are stored are C + j S, this is               */
        /* corrected for in the multiplies.                           */
        /*                                                            */
        /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
        /*                                                            */
        /* x0r = xt0;                                                 */
        /* y0i = yt0;                                                 */
        /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
        /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
        /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
        /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
        /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
        /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
        /*------------------------------------------------------------*/

        V_x2r  = (Vxt2 * VC2_76543210);
        V_y2i  = (Vyt2 * VC2_76543210);
        V_x2r += (Vyt2 * VS2_76543210);
        V_y2i -= (Vxt2 * VS2_76543210);

        V_x1r  = (Vxt1 * VC1_76543210);
        V_y1i  = (Vyt1 * VC1_76543210);
        V_x3r  = (Vxt3 * VC3_76543210);
        V_y3i  = (Vyt3 * VC3_76543210);

        V_x1r += (Vyt1 * VS1_76543210);
        V_y1i -= (Vxt1 * VS1_76543210);
        V_x3r += (Vyt3 * VS3_76543210);
        V_y3i -= (Vxt3 * VS3_76543210);

        /* -----------------------------------------------------------*/
        /*  Store the final results back to output with transpoition. */
        /*                                                            */
        /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
        /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
        /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
        /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
        /* -----------------------------------------------------------*/

        (pOutput + 8 * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
            VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 * 0 )[Addr_out].interleave() = (V_x0r, V_y0i).round(scale).saturate(-saturationLimit, (saturationLimit - 1));
        (pOutput + 8 * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
            VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 * 1 )[Addr_out].interleave() = (V_x1r, V_y1i).round(15 + scale).saturate(-saturationLimit, (saturationLimit - 1));
        (pOutput + 8 * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
            VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 * 2 )[Addr_out].interleave() = (V_x2r, V_y2i).round(15 + scale).saturate(-saturationLimit, (saturationLimit - 1));
        (pOutput + 8 * VCOP_FFT_512_STAGE4_NUMBF_PER_GRP *
            VCOP_SIMD_WIDTH * sizeof(*pOutput) * 2 * 3 )[Addr_out].interleave() = (V_x3r, V_y3i).round(15 + scale).saturate(-saturationLimit, (saturationLimit - 1));
      }
    }
  }
}

#define VCOP_FFT_512_STAGE5_NUMBF_PER_GRP (1)
#define VCOP_FFT_512_STAGE5_NUMPT_PER_GRP (VCOP_FFT_512_STAGE5_NUMBF_PER_GRP * 2)
#define VCOP_FFT_512_STAGE5_NUM_GRPS      (64 * 4)
#define VCOP_FFT_512_STAGE5_STRIDE        (VCOP_FFT_512_STAGE4_OUTPUT_STRIDE)

void vcop_fft_512_16ix16o_radix2_stage_5
(

    __vptr_int16      pInput,
    __vptr_int16      pOutput,
    unsigned short numOfLines,
    unsigned short scale,
    unsigned short    saturationLimit
)
{
  __vector Vx0, Vx1, Vy0, Vy1;
  __vector Vx0_plus_x1, Vx0_minus_x1;
  __vector Vy0_plus_y1, Vy0_minus_y1;

  for (int lineIdx = 0; lineIdx < numOfLines; lineIdx++)
  {
    for (int I3 = 0; I3 < (VCOP_FFT_512_STAGE5_NUM_GRPS/ 4)/VCOP_SIMD_WIDTH; I3++) /* There are total 2 such sets */
    {
      for (int I4 = 0; I4 < 4; I4++) /* There are 16 groups per column */
      {

        __agen  addr_in = I4 * VCOP_FFT_512_STAGE5_STRIDE * VCOP_FFT_512_STAGE5_NUMPT_PER_GRP +
                          I3 *  VCOP_SIMD_WIDTH * 2 * sizeof(*pInput) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pInput) * 2;

        __agen  addr_out = I4 * VCOP_FFT_512_STAGE5_STRIDE +
                          I3 *  VCOP_SIMD_WIDTH * 2 * sizeof(*pOutput) +
                          lineIdx * VCOP_FFT_512_NPOINTS * sizeof(*pOutput) * 2;

      (Vx0, Vy0) =  (pInput + VCOP_FFT_512_STAGE5_STRIDE * 0)[addr_in].deinterleave();
      (Vx1, Vy1) =  (pInput + VCOP_FFT_512_STAGE5_STRIDE * 1)[addr_in].deinterleave();

      (Vx0_plus_x1,  Vx0_minus_x1)   = (Vx0, Vx1).addsub();
      (Vy0_plus_y1,  Vy0_minus_y1)   = (Vy0, Vy1).addsub();


      (pOutput + VCOP_FFT_512_STAGE5_STRIDE *  0)[addr_out].interleave() = (Vx0_plus_x1, Vy0_plus_y1).round(scale).saturate(-saturationLimit, (saturationLimit - 1));
      (pOutput + VCOP_FFT_512_STAGE5_STRIDE *  4)[addr_out].interleave() = (Vx0_minus_x1,  Vy0_minus_y1).round(scale).saturate(-saturationLimit, (saturationLimit - 1));
      }
    }
  }
}
/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft-1024_16x16t_kernel.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */





