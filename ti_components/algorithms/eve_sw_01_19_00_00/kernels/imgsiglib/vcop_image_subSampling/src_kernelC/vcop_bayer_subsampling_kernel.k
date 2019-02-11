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
/* NAME : vcop_bayer_subsampling_kernel                                       */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*  Version : 0.0 (Base Version) :Gajanan Ambi                                */
/*============================================================================*/
/* Texas Instruments Incorporated 2009-2012.                                  */
/*----------------------------------------------------------------------------*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMBSZ    (sizeof (*CFA_short))

void bayer_subSampling
(
  __vptr_uint16 CFA_short,      /*Input block pointer*/
  __vptr_uint16 subSample_out,  /*Output block pointer*/
  unsigned int  blk_w,          /*Input block width*/
  unsigned int  blk_h,          /*Input block height*/
  unsigned int  input_stride,
  unsigned int  output_stride,
  unsigned int  subSample_X,    /*Horizontal sampling value*/
  unsigned int  subSample_Y,    /*Vertical sampling  value*/
  unsigned int  NumOfSample     /*Number of samples to be taken*/
)
{
  __vector pixel1,pixel2;
  for(int I0 = 0; I0 < (blk_h/subSample_Y); I0++)
  {
    for(int I1 = 0; I1 < (blk_w/subSample_X); I1++)
    {
      __agen Addr_in,Addr_out;
      Addr_in  = (I0*input_stride*subSample_Y*ELEMBSZ) + (I1*subSample_X*ELEMBSZ);
      Addr_out = (I0*output_stride*ELEMBSZ*2) + (I1*NumOfSample*2*ELEMBSZ);

      pixel1 = CFA_short[Addr_in];
      pixel2 = (CFA_short + (input_stride*ELEMBSZ))[Addr_in];

      subSample_out[Addr_out] = pixel1;
      (subSample_out + (output_stride*ELEMBSZ))[Addr_out] = pixel2;
    }
  }
}


