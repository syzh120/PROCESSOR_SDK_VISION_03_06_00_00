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
/* NAME: vcop_sum_grad_cross_inter_frame_diff_7x7_kernel                     */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*     This kernel implements sum of Ix*It ans Iy*It                          */
/*     computation on EVE                                                     */
/* AUTHOR:                                                                    */
/*             Kumar Desappan(kumar.desappan@ti.com)                         */
/*                                                                            */
/* VERSION:                                                                   */
/*            1.0 (Nov 2013) : Base version.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define TRANSPOSE_STRIDE (36)
#define BLK_WIDTH        (7)
#define BLK_HEIGHT       (7)
#define IN_GRAD_SZ       (2)
#define IN_IMG_SZ        (1)
#define OUT_ELEM_SZ      (4)


void vcop_sum_grad_cross_inter_frame_diff_7x7
  (
  __vptr_int16           gradX_a,         
  __vptr_int16           gradY_b,         
  __vptr_uint8          im1_a,         
  __vptr_uint8        im2_b,         
    unsigned short       gradStride,            
    unsigned short       imStride,            
    unsigned short       n,              
  __vptr_int32           IxIt_a,         
  __vptr_int32           IyIt_b,         
  __vptr_int32           scartch_a,         
  __vptr_int32           scartch_b         
  )
{
  __vector VgradX, VgradY, VimC, VimP, VDiff;
  __vector VsumIxIt, VsumIyIt;
  __vector VIxIt, VIyIt;
  __agen inAddr1;
  __agen inAddr2;
  __agen outAddr;

  for (int I0 = 0; I0 < (n + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
    for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
    {
      outAddr  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I1*OUT_ELEM_SZ;
      VsumIxIt = 0;
      VsumIyIt = 0;
      for (int I2 = 0; I2 < BLK_HEIGHT; I2++)
      {
        inAddr1  = I0*VCOP_SIMD_WIDTH*BLK_HEIGHT*gradStride*IN_GRAD_SZ + I1*gradStride*BLK_HEIGHT*IN_GRAD_SZ + I2*gradStride*IN_GRAD_SZ;
        inAddr2  = I0*VCOP_SIMD_WIDTH*BLK_HEIGHT*imStride*IN_IMG_SZ + I1*imStride*BLK_HEIGHT*IN_IMG_SZ + I2*imStride*IN_IMG_SZ;
        VgradX = gradX_a[inAddr1];
        VgradY = gradY_b[inAddr1];
        VimC   = im1_a[inAddr2]; 
        VimP   = im2_b[inAddr2]; 

        VDiff = VimC - VimP;

        VsumIxIt += VgradX*VDiff;
        VsumIyIt += VgradY*VDiff;

      }
      scartch_a[outAddr].offset_np1()     = VsumIxIt;
      scartch_b[outAddr].offset_np1()     = VsumIyIt;
    }
  }

  for (int I0 = 0; I0 < (n + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
      outAddr  = I0*OUT_ELEM_SZ*VCOP_SIMD_WIDTH;
      VsumIxIt = 0;
      VsumIyIt = 0;
      for (int I2 = 0; I2 < BLK_WIDTH; I2++)
      {
        inAddr1  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I2*TRANSPOSE_STRIDE;
        VIxIt = scartch_a[inAddr1];
        VIyIt = scartch_b[inAddr1];
        VsumIxIt += VIxIt;
        VsumIyIt += VIyIt;
     }
      IxIt_a[outAddr] = VsumIxIt;
      IyIt_b[outAddr] = VsumIyIt;
  }
}


/*----------------------------------------------------------------------------*/
/* End of file:vcop_sum_grad_cross_inter_frame_diff_7x7_kernel.k              */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
