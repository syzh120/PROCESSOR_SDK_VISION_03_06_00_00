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

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define NUM_TBLS 4
#define NUM_PTS_TLU 1

#define ELEMBSZ    (sizeof (*iPtrR_in))
#define VECTORBSZ  (VCOP_SIMD_WIDTH * ELEMBSZ)
#define VECTOROSZ  (2 * VCOP_SIMD_WIDTH * ELEMBSZ)

void gamma_correction
(
__vptr_uint16    iPtrR_in,
__vptr_uint16    iPtrG_in,
__vptr_uint16    iPtrB_in,
__vptr_uint16    iPtrR_out,
__vptr_uint16    iPtrG_out,
__vptr_uint16    iPtrB_out,
unsigned short   blk_w,
unsigned short   blk_h,
unsigned short   input_stride,
unsigned short   output_stride,
__vptr_uint16    tempPtrR,
__vptr_uint16    tempPtrG,
__vptr_uint16    tempPtrB,
__vptr_uint16    LUT
)
{
  /*--------------------------------------------------------------------------*/
  /*Compute Loop for 12-bit to 10-bit conversion                              */
  /*--------------------------------------------------------------------------*/
  __vector Vred,Vgreen,Vblue;
  for(int I0 = 0; I0 < blk_h; I0++)
  {
    for(int I1 = 0; I0 < (blk_w/VCOP_SIMD_WIDTH); I0++)
    {
      __agen Addr;

      Addr = (I0 * input_stride  * ELEMBSZ) + (I1 * VCOP_SIMD_WIDTH * ELEMBSZ);

      Vred   = iPtrR_in[Addr];
      Vgreen = iPtrG_in[Addr];
      Vblue  = iPtrB_in[Addr];

      tempPtrR[Addr] = Vred.truncate(2);
      tempPtrG[Addr] = Vgreen.truncate(2);
      tempPtrB[Addr] = Vblue.truncate(2);
    }
  }

  /*--------------------------------------------------------------------------*/
  /*Look Up Loop for R component                                              */
  /*--------------------------------------------------------------------------*/
  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

  for(int I2 = 0; I2< blk_h; I2++)
  {
    for(int I3 = 0; I3<(blk_w/NUM_TBLS); I3++)
    {
      __agen tblR_index = 0;
      __agen AddrR_in;
      __agen AddrR_out;

      __vector Vr;
      __vector Vtbl_Rval;

      AddrR_in  = (I2*input_stride * ELEMBSZ) + (I3 * NUM_TBLS * ELEMBSZ);
      AddrR_out = (I2*input_stride * ELEMBSZ) + (I3 * NUM_TBLS * ELEMBSZ);

      Vr = tempPtrR[AddrR_in];

      Vtbl_Rval = LUT[tblR_index].lookup(Vr);

      tempPtrR[AddrR_out] = Vtbl_Rval;
    }
  }

  /*--------------------------------------------------------------------------*/
  /*Look Up Loop for G component                                              */
  /*--------------------------------------------------------------------------*/
  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
  for(int I2 = 0; I2< blk_h; I2++)
  {
    for(int I3 = 0; I3<(blk_w/NUM_TBLS); I3++)
    {
      __agen tblG_index = 0;
      __agen AddrG_in;
      __agen AddrG_out;

      __vector Vg;
      __vector Vtbl_Gval;

      AddrG_in  = (I2*input_stride*ELEMBSZ) + (I3 *NUM_TBLS*ELEMBSZ);
      AddrG_out = (I2*input_stride*ELEMBSZ) + (I3 *NUM_TBLS*ELEMBSZ);

      Vg = tempPtrG[AddrG_in];

      Vtbl_Gval = LUT[tblG_index].lookup(Vg);

      tempPtrG[AddrG_out] = Vtbl_Gval;
    }
  }

  /*--------------------------------------------------------------------------*/
  /*Look Up Loop for G component                                              */
  /*--------------------------------------------------------------------------*/
  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

  for(int I2 = 0; I2< blk_h; I2++)
  {
    for(int I3 = 0; I3<(blk_w/NUM_TBLS); I3++)
    {
      __agen tblB_index = 0;
      __agen AddrB_in;
      __agen AddrB_out;

      __vector Vb;
      __vector Vtbl_Bval;

      AddrB_in  = (I2*input_stride*ELEMBSZ) + (I3 *NUM_TBLS*ELEMBSZ);
      AddrB_out = (I2*input_stride*ELEMBSZ) + (I3 *NUM_TBLS*ELEMBSZ);

      Vb = tempPtrB[AddrB_in];

      Vtbl_Bval = LUT[tblB_index].lookup(Vb);

      tempPtrB[AddrB_out] = Vtbl_Bval;
    }
  }

  /*--------------------------------------------------------------------------*/
  /*Compute Loop for 10-bit to 12-bit conversion                              */
  /*--------------------------------------------------------------------------*/
  __vector Vshift;
  Vshift = 2;
  for(int I4 = 0; I4 < blk_h; I4++)
  {
    for(int I5 = 0; I5 < (blk_w/VCOP_SIMD_WIDTH); I5++)
    {
      __agen Addr;

      Addr = (I4 * output_stride * ELEMBSZ) + (I5 * VCOP_SIMD_WIDTH * ELEMBSZ);

      Vred   = tempPtrR[Addr];
      Vgreen = tempPtrG[Addr];
      Vblue  = tempPtrB[Addr];

      Vred   = Vred << Vshift;
      Vgreen = Vgreen << Vshift;
      Vblue  = Vblue << Vshift;

      iPtrR_out[Addr] = Vred;
      iPtrG_out[Addr] = Vgreen;
      iPtrB_out[Addr] = Vblue;
    }
  }
}

