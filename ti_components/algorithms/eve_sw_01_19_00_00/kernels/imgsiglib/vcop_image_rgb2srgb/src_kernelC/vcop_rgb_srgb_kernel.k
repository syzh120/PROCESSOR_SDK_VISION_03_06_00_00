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

#define ELEMBSZ    (sizeof (*iPtrR))
#define VECTORSZ  (VCOP_SIMD_WIDTH * ELEMBSZ)

void rgb_to_srgb
(
__vptr_uint16   iPtrR,
__vptr_uint16   iPtrG,
__vptr_uint16   iPtrB,
__vptr_uint16   oPtrR,
__vptr_uint16   oPtrG,
__vptr_uint16   oPtrB,
unsigned short  blk_w,
unsigned short  blk_h,
unsigned short  input_stride,
unsigned short  output_stride,
__vptr_int16    rgb2srgb_coefs
)
{
  __vector  Vred,Vgrn, Vblu;
  __vector  Vcoef0,Vcoef1,Vcoef2,Vcoef3,Vcoef4,Vcoef5,Vcoef6,Vcoef7,Vcoef8;
  __vector VsRed,VsGreen,VsBlue;

  Vcoef0 = *(rgb2srgb_coefs);
  Vcoef1 = *(rgb2srgb_coefs+1);
  Vcoef2 = *(rgb2srgb_coefs+2);
  Vcoef3 = *(rgb2srgb_coefs+3);
  Vcoef4 = *(rgb2srgb_coefs+4);
  Vcoef5 = *(rgb2srgb_coefs+5);
  Vcoef6 = *(rgb2srgb_coefs+6);
  Vcoef7 = *(rgb2srgb_coefs+7);
  Vcoef8 = *(rgb2srgb_coefs+8);

  for(int I0 = 0; I0 < blk_h; I0++)
  {
    for(int I1 =0; I1 < (blk_w/VCOP_SIMD_WIDTH); I1++)
    {
      __agen Addr_in  = (I0 * input_stride * ELEMBSZ) + (I1 * VECTORSZ);
      __agen Addr_out = (I0 * output_stride * ELEMBSZ) + (I1 * VECTORSZ);

      Vred   =  (iPtrR)[Addr_in].npt();
      Vgrn   =  (iPtrG)[Addr_in].npt();
      Vblu   =  (iPtrB)[Addr_in].npt();

      VsRed   = 0x80;
      VsGreen = 0x80;
      VsBlue  = 0x80;

      VsRed  +=  (Vcoef0  *  Vred);
      VsRed  +=  (Vcoef1  *  Vgrn);
      VsRed  +=  (Vcoef2  *  Vblu);

      VsGreen  +=  (Vcoef3  *  Vred);
      VsGreen  +=  (Vcoef4  *  Vgrn);
      VsGreen  +=  (Vcoef5  *  Vblu);

      VsBlue  +=  (Vcoef6  *  Vred);
      VsBlue  +=  (Vcoef7  *  Vgrn);
      VsBlue  +=  (Vcoef8  *  Vblu);

      (oPtrR)[Addr_out] = VsRed.truncate(8).saturate(0,4095);
      (oPtrG)[Addr_out] = VsGreen.truncate(8).saturate(0,4095);
      (oPtrB)[Addr_out] = VsBlue.truncate(8).saturate(0,4095);
    }
  }
}

/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv_kernel.k                          */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

