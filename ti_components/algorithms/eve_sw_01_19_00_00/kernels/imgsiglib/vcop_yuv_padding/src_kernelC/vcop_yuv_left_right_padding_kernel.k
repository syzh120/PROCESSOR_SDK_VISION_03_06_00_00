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

/*                                                                          */
/*    @file : vcop_yuv_left_right_padding_kernel.k                          */
/*                                                                          */
/*    @brief : Kernel for left and right padding                            */
/*                                                                          */
/*    @version : 1.0 (Mar 2014) : Base version.                             */
/*                                                                          */
/*==========================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

void vcop_yuv_left_right_padding_u8
(
    __vptr_uint8   in_left_A,
    __vptr_uint8   in_right_B,
    __vptr_uint8   out_left_A,
    __vptr_uint8   out_right_B,
    unsigned short width,
    unsigned short height,
    unsigned short out_stride
)
{
  __vector vin_left;
  __vector vin_right;
  __agen Addr_in, Addr_out;
  for(int I1 = 0; I1 < height; I1++)
  {
    Addr_in = I1;
    vin_left  = in_left_A[Addr_in].onept();
    vin_right = in_right_B[Addr_in].onept();
    for(int I2 = 0; I2 < (width + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I2++)
    {
      Addr_out = I1*out_stride + I2*VCOP_SIMD_WIDTH;
      out_left_A[Addr_out]  = vin_left;
      out_right_B[Addr_out] = vin_right;
    }
  }

}


void vcop_yuv_left_right_padding_u16
(
    __vptr_uint16   in_left_A,
    __vptr_uint16   in_right_B,
    __vptr_uint16   out_left_A,
    __vptr_uint16   out_right_B,
    unsigned short width,
    unsigned short height,
    unsigned short out_stride
)
{
  __vector vin_left;
  __vector vin_right;
  __agen Addr_in, Addr_out;
  for(int I1 = 0; I1 < height; I1++)
  {
    Addr_in = I1*2;
    vin_left  = in_left_A[Addr_in].onept();
    vin_right = in_right_B[Addr_in].onept();
    for(int I2 = 0; I2 < (width + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I2++)
    {
      Addr_out = I1*out_stride*2 + I2*VCOP_SIMD_WIDTH*2;
      out_left_A[Addr_out]  = vin_left;
      out_right_B[Addr_out] = vin_right;
    }
  }

}
