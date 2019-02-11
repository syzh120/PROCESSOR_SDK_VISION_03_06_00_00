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


/*----------------------------------------------------------------------------*/
/* NAME : vcop_white_balance_kernel                                       */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*  Version : 0.0 (Base Version) :Gajanan Ambi                                */
/*============================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define VCOP_2SIMD_WIDTH   (VCOP_SIMD_WIDTH * 2)

#define ELEMSZ           sizeof(*CFA_short_in)
#define VECTORSZ_1SIMD  (ELEMSZ * VCOP_SIMD_WIDTH)
#define VECTORSZ_2SIMD  (ELEMSZ * VCOP_2SIMD_WIDTH)
#define NUM_OF_LINES_PROCESSED 2

void vcop_white_balance_BGGR
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VB0, VG0) = CFA_short_in[Addr_in].deinterleave();
      (VG1, VR0) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VB0_wb = (VB0 * VGAIN_FACT_B);
      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);
      VR0_wb = (VR0 * VGAIN_FACT_R);

      CFA_short_out[Addr_out].interleave() = (VB0_wb,VG0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VG1_wb,VR0_wb).round(shift_val);
    }
  }
}


void vcop_white_balance_GBRG
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VG0 , VB0) = CFA_short_in[Addr_in].deinterleave();
      (VR0 , VG1) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VB0_wb = (VB0 * VGAIN_FACT_B);
      VR0_wb = (VR0 * VGAIN_FACT_R);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);

      CFA_short_out[Addr_out].interleave() = (VG0_wb,VB0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VR0_wb,VG1_wb).round(shift_val);
    }
  }
}


void vcop_white_balance_GRBG
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VG0 , VR0 ) = CFA_short_in[Addr_in].deinterleave();
      (VB0 , VG1) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VR0_wb = (VR0 * VGAIN_FACT_R);
      VB0_wb = (VB0 * VGAIN_FACT_B);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);

      CFA_short_out[Addr_out].interleave() = (VG0_wb,VR0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VB0_wb,VG1_wb).round(shift_val);
    }
  }
}


void vcop_white_balance_RGGB
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VR0, VG0) = CFA_short_in[Addr_in].deinterleave();
      (VG1, VB0) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VR0_wb = (VR0 * VGAIN_FACT_R);
      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);
      VB0_wb = (VB0 * VGAIN_FACT_B);

      CFA_short_out[Addr_out].interleave() = (VR0_wb,VG0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VG1_wb,VB0_wb).round(shift_val);
    }
  }
}

