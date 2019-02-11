/*
*
* Copyright (c) {YEAR} Texas Instruments Incorporated
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
/* NAME       : vision_vcop_bilateralFilter_kernel                            */
/* DESCRIPTION: Kernel code for bilateral filter                              */
/* AUTHOR     : Gajanan Ambi (gajanan.ambi@ti.com)                            */
/* VERSION    : 0.0 (August 2012) : Base version.                             */
/*----------------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define NUM_TBLS 8
#define NUM_PTS_TLU 1

#define ELEMSZ                   sizeof(*input_ptr)
#define FILTER_WINDOW_SIZE      (5)  /* 5 x 5*/
#define SIZE_OF_INT             (4)  /*unsigned int*/
#define SIZE_OF_SHORT           (2)  /*unsigned short*/
#define VCOP_2SIMD_WIDTH        (2*VCOP_SIMD_WIDTH)

void vcop_img_bilateralFilter
(
  __vptr_uint8 input_ptr,
  __vptr_uint8 output_ptr,
  __vptr_uint8 diff_ptr,
  __vptr_uint16 G_pq_ptr,
  __vptr_uint32 W_p_ptr,
  __vptr_uint32 BF_p_ptr,
  __vptr_uint16 LUT_RANGE_8TBL,
  __vptr_uint16 LUT_SPACE_TBL,
  int blk_width,
  int blk_height,
  int blk_stride,
  int horz_pad_size,
  int vert_pad_size,
  unsigned int Qpoint_tbl,
  unsigned int Qpoint_div,
  unsigned char pixel_format
)
{
  /*--------------------------------------------------------------------------*/
  /* Compute loop to find out difference                                      */
  /*--------------------------------------------------------------------------*/
  for(int i = 0; i < blk_height; i++)
  {
    for(int j = 0; j <(blk_width/VCOP_2SIMD_WIDTH); j++)
    {
      __agen Addr_ctrl;
      __vector VI_p_1,VI_p_2; /* Center pixel*/

      Addr_ctrl      = (i*blk_stride) + (j*VCOP_2SIMD_WIDTH);
      /*----------------------------------------------------------------------*/
      /* Center pixel fetch                                                   */
      /*----------------------------------------------------------------------*/
      (VI_p_1,VI_p_2)  = (input_ptr + (vert_pad_size*blk_stride) + horz_pad_size)[Addr_ctrl].deinterleave();

      for(int s = 0; s < 5; s++)
      {
        for(int t = 0; t < 5; t++)
        {
          __agen Addr_nbr_pixel;
          __agen Addr_diff_out;
          __vector VI_q_1, VI_q_2; /*nbre pixel*/
          __vector Vdiff_1, Vdiff_2;
          Vdiff_1 = 0;
          Vdiff_2 = 0;

          Addr_nbr_pixel = (s*blk_stride) + (t*pixel_format) + (i*blk_stride) + (j*VCOP_2SIMD_WIDTH);
          Addr_diff_out  = (s*blk_width*blk_height*FILTER_WINDOW_SIZE) + (t*blk_width*blk_height) + (i*blk_width) + (j * VCOP_2SIMD_WIDTH);


          (VI_q_1,VI_q_2) = input_ptr[Addr_nbr_pixel].deinterleave();

          Vdiff_1 += abs(VI_p_1 - VI_q_1);
          Vdiff_2 += abs(VI_p_2 - VI_q_2);

          diff_ptr[Addr_diff_out].interleave() = (Vdiff_1,Vdiff_2);
        }
      }
    }
  }
  /*--------------------------------------------------------------------------*/
  /* Lookup Loop to find out LUT values for each diff                         */
  /*--------------------------------------------------------------------------*/
  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

  for(int i = 0; i<(FILTER_WINDOW_SIZE*FILTER_WINDOW_SIZE); i++)
  {
    for(int j = 0; j<((blk_height*blk_width)/VCOP_SIMD_WIDTH); j++)
    {
      __agen table_index = 0;
      __agen diff_offset;
      __agen Gpq_offset;
      __vector Vdiff_val;
      __vector VG_pq;

      diff_offset  = (i*blk_height*blk_width) + (j*VCOP_SIMD_WIDTH);
      Gpq_offset   = (i*blk_height*blk_width*SIZE_OF_SHORT) + (j*VCOP_SIMD_WIDTH*SIZE_OF_SHORT);

      Vdiff_val    = diff_ptr[diff_offset];

      VG_pq        = LUT_RANGE_8TBL[table_index].lookup(Vdiff_val);

      G_pq_ptr[Gpq_offset] = VG_pq;
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Compute Loop                                                             */
  /*--------------------------------------------------------------------------*/
  for(int m = 0; m<blk_height; m++)
  {
    for(int n = 0; n<(blk_width/VCOP_2SIMD_WIDTH); n++)
    {
      __agen Addr_output;
      __vector VW_p_1,VW_p_2;
      __vector VBF_p_1,VBF_p_2;

      Addr_output = (m*blk_width*SIZE_OF_INT) + (n*SIZE_OF_INT*VCOP_2SIMD_WIDTH);

      VW_p_1  = 0;
      VBF_p_1 = 0;
      VW_p_2  = 0;
      VBF_p_2 = 0;

      for(int p = 0; p<FILTER_WINDOW_SIZE; p++)
      {
        for(int q = 0; q<FILTER_WINDOW_SIZE; q++)
        {
          __agen Gpq_offset;
          __agen Add_lut_s;
          __agen Addr_nbr_pixel_1, Addr_nbr_pixel_2;
          __vector Vlut_s;
          __vector VI_q_1, VI_q_2; //*nbre pixel */

          __vector Vlut_r_1,Vlut_r_2;
          __vector VG_pq_1,VG_pq_2;

          Gpq_offset = (m*blk_width*SIZE_OF_SHORT) + (n * VCOP_2SIMD_WIDTH*SIZE_OF_SHORT) + (p *5*blk_height*blk_width*SIZE_OF_SHORT) + (q *blk_height*blk_width*SIZE_OF_SHORT);

          Add_lut_s = (p*FILTER_WINDOW_SIZE*SIZE_OF_SHORT) + (q*SIZE_OF_SHORT);
          Addr_nbr_pixel_1 = (m * blk_stride) + (n *VCOP_2SIMD_WIDTH) + (p * blk_stride) + (q*pixel_format);
          Addr_nbr_pixel_2 = (m * blk_stride) + (n *VCOP_2SIMD_WIDTH) + (p * blk_stride) + (q*pixel_format);

          Vlut_s    = LUT_SPACE_TBL[Add_lut_s].onept();

          VI_q_1    = input_ptr[Addr_nbr_pixel_1];
          VI_q_2    = (input_ptr + VCOP_SIMD_WIDTH)[Addr_nbr_pixel_2];

          Vlut_r_1  = G_pq_ptr[Gpq_offset];
          Vlut_r_2  = (G_pq_ptr + (VCOP_SIMD_WIDTH*SIZE_OF_SHORT))[Gpq_offset];

          VG_pq_1   = (Vlut_s * Vlut_r_1).truncate(8);
          VG_pq_2   = (Vlut_s * Vlut_r_2).truncate(8);

          VW_p_1   += VG_pq_1;
          VW_p_2   += VG_pq_2;

          VBF_p_1  += (VI_q_1 * VG_pq_1);
          VBF_p_2  += (VI_q_2 * VG_pq_2);
        }
      }

      W_p_ptr[Addr_output]                                     = VW_p_1;
      (W_p_ptr + (VCOP_SIMD_WIDTH*SIZE_OF_INT))[Addr_output]   = VW_p_2;
      BF_p_ptr[Addr_output]                                    = VBF_p_1;
      (BF_p_ptr + (VCOP_SIMD_WIDTH*SIZE_OF_INT))[Addr_output]  = VBF_p_2;
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Compute Loop for division                                                */
  /*--------------------------------------------------------------------------*/
  __vector Vin1;
  __vector Vin2;
  __vector VbinX,VbinY;
  __vector Vdelta, Vfrac, Vexp;
  __vector Vfrac_p1,Vexp_adj,Vfmask;
  __vector Vm28, V2_to_28,VQm28;
  __vector Vout;
  __vector Vshift;

  Vshift = Qpoint_div - Qpoint_tbl;

  /*--------------------------------------------------------------------------*/
  /* Shift value used to get the fractional part of the binlog which is       */
  /* located in (bits 0 - 27)                                                 */
  /*--------------------------------------------------------------------------*/
  Vm28 = -28;

  /*--------------------------------------------------------------------------*/
  /* Output Q-factor alignment, VQm28 = 0 means scaling by 2^28               */
  /*--------------------------------------------------------------------------*/
  VQm28 = Qpoint_tbl - 28;

  /*--------------------------------------------------------------------------*/
  /* (1 << 28), constant used to place the LMBD back onto the fractional      */
  /* portion of the binlog after division                                     */
  /*--------------------------------------------------------------------------*/
  V2_to_28 = 268435456;

  /*--------------------------------------------------------------------------*/
  /* Used to get the fractional part of binlog (bits 0 - 27)                  */
  /*--------------------------------------------------------------------------*/
  Vfmask = 0x0FFFFFFF;

  for(int i = 0; i<blk_height; i++)
  {
    for(int j = 0; j<(blk_width/VCOP_SIMD_WIDTH); j++)
    {
      __agen Addr_output;
      __agen Addr_input;

      Addr_output = (i * blk_width) + (j * VCOP_SIMD_WIDTH);
      Addr_input  = (i * blk_width * SIZE_OF_INT) + (j * VCOP_SIMD_WIDTH * SIZE_OF_INT);

      Vin1 = BF_p_ptr[Addr_input];
      Vin2 = W_p_ptr[Addr_input];

      Vin1 = Vin1 << Vshift;
      Vin2 = Vin2 << Vshift;

      VbinX = binlog(Vin1);
      VbinY = binlog(Vin2);

      /*----------------------------------------------------------------------*/
      /* Perform division via subtraction of logarithms                       */
      /*----------------------------------------------------------------------*/
      Vdelta = VbinX - VbinY;

      /*----------------------------------------------------------------------*/
      /* Perform an inverse binlog through a series of bitwise operations     */
      /* Align quotient to the user-defined Qformat                           */
      /* ---------------------------------------------------------------------*/

      /*----------------------------------------------------------------------*/
      /* (Vdelta & 0x0FFFFFFF) extract fractional portion of quotient         */
      /*----------------------------------------------------------------------*/
      Vfrac = Vdelta & Vfmask;

      /*----------------------------------------------------------------------*/
      /* Obtain integer part of quotient by right-Vshifting 28 bits           */
      /*----------------------------------------------------------------------*/
      Vexp = Vdelta << Vm28;

      /*----------------------------------------------------------------------*/
      /* Vfrac OR (1 << 28): "add 1, the LMBD"                                */
      /*----------------------------------------------------------------------*/
      Vfrac_p1 = Vfrac | V2_to_28;

      /*----------------------------------------------------------------------*/
      /* Adjust the exponent to the user-selected Qformat                     */
      /*----------------------------------------------------------------------*/
      Vexp_adj = Vexp + VQm28;

      /*----------------------------------------------------------------------*/
      /* Align quotient to user-defined Qformat                               */
      /*----------------------------------------------------------------------*/
      Vout = Vfrac_p1 << Vexp_adj;

      //output_ptr[Addr_output] = Vout.round(Qpoint_tbl).saturate(0, 255);
      output_ptr[Addr_output] = Vout.round(Qpoint_tbl);

    }
  }
}
