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
/* NAME : vcop_rgb_to_yuv                                          */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*                                                                 */
/* The function rgb_to_yuv, converts rgb to interleaved yuv.       */
/* by applying coefficients weighting red, blue and green,         */
/* to luma. Similarly we aplly a weighted product of red,          */
/* blue and green to U and V.                                      */
/*                                                                 */
/* A possible set of coefficients, to use is suggnsted at:         */
/* http://msdn.microsoft.com/en-us/library/ms893078.aspx           */
/*                                                                 */
/* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16          */
/* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128          */
/* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128          */
/*                                                                 */
/* The values from this equation, will have to be clamped          */
/* between 0..255.                                                 */
/*                                                                 */
/* This benchmark is intended to highlight the value of predicated */
/* stores to memory.                                               */
/*                                                                 */
/* API:                                                            */
/* void rgb_to_yuv                                                 */
/* (                                                               */
/*     unsigned char    iPtrR[],                                   */
/*     unsigned char    iPtrG[],                                   */
/*     unsigned char    iPtrB[],                                   */
/*     unsigned short   width,                                     */
/*     short            coefs[],                                   */
/*     unsigned char    iPtrOut[]                                  */
/* )                                                               */
/*                                                                 */
/* The function "rgb_to_yuv" accepts red, green and blue pixels    */
/* in arrays "iPtrR", "iPtrG" and "iPtrB" into an interleaved      */
/* array of YUYV pixels stored in "iPtrOut" by applying a 3x3      */
/* array of coefficients to convert from RGB to YUV space.         */
/*                                                                 */
/*  Version : 0.0 (Base Version)                                   */
/*  Version : 0.1 (Oct 8 2012) Modified, :Gajanan Ambi              */
/*=================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMBSZ_INPUT    (sizeof (*iPtrR))
#define ELEMBSZ_OUTPUT    (sizeof (*iPtrOut))
#define VECTOR_I_SZ  (VCOP_SIMD_WIDTH * ELEMBSZ_INPUT)
#define VECTOR_O_SZ  (2 * VCOP_SIMD_WIDTH * ELEMBSZ_OUTPUT)

void rgb_to_yuv_UYVY
(
__vptr_uint16     iPtrR,
__vptr_uint16     iPtrG,
__vptr_uint16     iPtrB,
unsigned short   blk_w,
unsigned short   blk_h,
unsigned short   in_stride,
short            coefs_r,
short            coefs_g,
short            coefs_b,
__vptr_int16     rgb2yuv_coefs,
unsigned int     roundingFactor,
unsigned short   shift_val,
__vptr_uint8     iPtrOut
)
{
  __vector  Vry0,    Vgy0,    Vby0;
  __vector  Vru_rv0, Vgu_gv0, Vbu_bv0;
  __vector  Vy0,     Vuv0,    Vred;
  __vector  Vgrn,    Vblu;

  Vry0  =  coefs_r;
  Vgy0  =  coefs_g;
  Vby0  =  coefs_b;

  __agen Addr_c  = 0;

  Vru_rv0     = (rgb2yuv_coefs +  6)[Addr_c].circ2();
  Vgu_gv0     = (rgb2yuv_coefs + 10)[Addr_c].circ2();
  Vbu_bv0     = (rgb2yuv_coefs + 14)[Addr_c].circ2();

  for(int I0 = 0; I0 < blk_h; I0++)
  {

    for(int I1 =0; I1 < (blk_w/VCOP_SIMD_WIDTH); I1++)
    {
      __agen Addr_in = (I1 * VECTOR_I_SZ) + (I0 * in_stride * ELEMBSZ_INPUT);
      __agen Addr_out = (I1 * VECTOR_O_SZ) + (I0 * blk_w * 2 * ELEMBSZ_OUTPUT);

      Vuv0   = roundingFactor;
      Vy0    = 0x80U;

      Vred   =  (iPtrR)[Addr_in].npt();
      Vgrn   =  (iPtrG)[Addr_in].npt();
      Vblu   =  (iPtrB)[Addr_in].npt();

      Vy0   +=  (Vry0     *  Vred);
      Vuv0  +=  (Vru_rv0  *  Vred);

      Vy0   +=  (Vgy0     *  Vgrn);
      Vuv0  +=  (Vgu_gv0  *  Vgrn);

      Vy0   +=  (Vby0     *  Vblu);
      Vuv0  +=  (Vbu_bv0  *  Vblu);

      (iPtrOut)[Addr_out].interleave() = (Vuv0, Vy0).truncate(shift_val).saturate(0,255);
    }
  }
}


void rgb_to_yuv_YUYV
(
__vptr_uint16     iPtrR,
__vptr_uint16     iPtrG,
__vptr_uint16     iPtrB,
unsigned short   blk_w,
unsigned short   blk_h,
unsigned short   in_stride,
short            coefs_r,
short            coefs_g,
short            coefs_b,
__vptr_int16     coefs,
unsigned int     roundingFactor,
unsigned short   shift_val,
__vptr_uint8     iPtrOut
)
{
  __vector  Vry0,    Vgy0,    Vby0;
  __vector  Vru_rv0, Vgu_gv0, Vbu_bv0;
  __vector  Vy0,     Vuv0,    Vred;
  __vector  Vgrn,    Vblu;

  Vry0  =  coefs_r;
  Vgy0  =  coefs_g;
  Vby0  =  coefs_b;

  __agen Addr_c  = 0;

  Vru_rv0     = (coefs +  6)[Addr_c].circ2();
  Vgu_gv0     = (coefs + 10)[Addr_c].circ2();
  Vbu_bv0     = (coefs + 14)[Addr_c].circ2();

  for(int I0 = 0; I0 < blk_h; I0++)
  {

    for(int I1 =0; I1 < (blk_w/VCOP_SIMD_WIDTH); I1++)
    {
      __agen Addr_in = (I1 * VECTOR_I_SZ) + (I0 * in_stride * ELEMBSZ_INPUT);
      __agen Addr_out = (I1 * VECTOR_O_SZ) + (I0 * blk_w * 2 * ELEMBSZ_OUTPUT);

      Vuv0   = roundingFactor;
      Vy0    = 0x80U;

      Vred   =  (iPtrR)[Addr_in].npt();
      Vgrn   =  (iPtrG)[Addr_in].npt();
      Vblu   =  (iPtrB)[Addr_in].npt();

      Vy0   +=  (Vry0     *  Vred);
      Vuv0  +=  (Vru_rv0  *  Vred);

      Vy0   +=  (Vgy0     *  Vgrn);
      Vuv0  +=  (Vgu_gv0  *  Vgrn);

      Vy0   +=  (Vby0     *  Vblu);
      Vuv0  +=  (Vbu_bv0  *  Vblu);

      (iPtrOut)[Addr_out].interleave() = (Vy0 ,Vuv0).truncate(shift_val).saturate(0,255);
    }
  }
}
/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv_kernel.k                          */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

