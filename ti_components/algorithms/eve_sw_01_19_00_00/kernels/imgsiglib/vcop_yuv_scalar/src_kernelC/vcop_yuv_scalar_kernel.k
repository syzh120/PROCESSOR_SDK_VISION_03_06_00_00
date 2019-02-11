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
/*     NAME                                                                 */
/*     vcop_yuv_scalar_kernel.k                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This file contains the VCOP kernels for                          */
/*         YUV scalar                                                       */
/*                                                                          */
/*==========================================================================*/
#define NUM_TBLS (1)
#define NUM_PTS_TLU (8)

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ZERO_DUMMY (0)
#define NUM_PIXELS_PER_LOOKUP (32)
#define VCOP_2SIMD_WIDTH      (VCOP_SIMD_WIDTH * 2)

void yuv_scalar_pixels_look_up_kernel
  (
  __vptr_uint32 src,      
  __vptr_uint16 index,  
  __vptr_uint32 outBuf,    
  short int numTaps,    
  short int src_w,    
  short int dst_h    
  )
{

    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
    for ( int i = 0; i < numTaps*dst_h ; i++ )
    {
      for ( int  j = 0 ; j < (src_w+(NUM_PIXELS_PER_LOOKUP-1))/NUM_PIXELS_PER_LOOKUP ; ++j)
      {
        __agen Addr_index ,Addr_out ;
        __agen Addr_table = 0;
        __vector Vindex,Vdata;
        Addr_index  = i*sizeof(*index);
        Addr_out    = i*src_w + j*NUM_PIXELS_PER_LOOKUP;
        Addr_table  = i*ZERO_DUMMY + j*NUM_PIXELS_PER_LOOKUP;

        Vindex                         = index[Addr_index].onept();
        Vdata                          = src[Addr_table].lookup(Vindex);
        outBuf[Addr_out].table_npt()   = Vdata;
      }
    }

}

#define DAT_SIZE (sizeof(*inPtr))
#define CO_EFF_SIZE (sizeof(*fracPtr))

void yuv_scalar_interpolation_kernel( 
          __vptr_uint8 inPtr,          
          __vptr_uint8 fracPtr,          
          __vptr_uint8 temp1Ptr,          
          __vptr_uint8 temp2Ptr,          
          __vptr_uint16 offsetPtr,          
          short int tempBufPitch,    
          short int fracBits,    
          short int numTaps,
          short int src_w,    
          short int src_pitch,    
          short int dst_h
        )
{
  __agen Addr_dstOut, Addr_offset, Addr_p, Addr_f;
  __vector Voffset,Vsum1,Vsum2,Vin1,Vin2,Vin3,Vin4,Vinf;

  Addr_offset = 0;
  Voffset = offsetPtr[Addr_offset];
  
  for (int I1=0; I1<dst_h; I1++)
  {

    for (int I2=0; I2< ((src_w + (VCOP_2SIMD_WIDTH-1))/VCOP_2SIMD_WIDTH); I2++)
    {
      Addr_dstOut = I1 *DAT_SIZE + I2*tempBufPitch*VCOP_SIMD_WIDTH*DAT_SIZE;
      Vsum1=0;
      Vsum2=0;

      for (int I3=0; I3<numTaps; I3++)
      {
        Addr_p =I3*DAT_SIZE*src_pitch*dst_h + I1*DAT_SIZE*src_pitch + I2*DAT_SIZE*VCOP_2SIMD_WIDTH;
        Addr_f =I3*CO_EFF_SIZE*dst_h + I1*CO_EFF_SIZE;

        (Vin1,Vin2) = inPtr[Addr_p].deinterleave();
         Vinf       = fracPtr[Addr_f].onept();
        Vsum1 += Vinf*Vin1;
        Vsum2 += Vinf*Vin2;
      }
      temp1Ptr[Addr_dstOut].p_scatter(Voffset) = Vsum1.round(fracBits).saturate(0,255);
      temp2Ptr[Addr_dstOut].p_scatter(Voffset) = Vsum2.round(fracBits).saturate(0,255);
    }
  }
}

void yuv_scalar_luma_copy_kernel( 
          __vptr_uint32 outPtr,          
          __vptr_uint32 temp1Ptr,          
          __vptr_uint32 temp2Ptr,          
          short int tempBufPitch,    
          short int src_w,    
          short int dst_h
        )
{
    __agen Addr1;
    __agen Addr2;
  __vector Vin1,Vin2;

  for(int I1=0;I1< (src_w+1)/2;I1++)
  {
    for(int I2=0;I2< ((dst_h + (32-1))/32);I2++) 
    {
    Addr1= I2*32 + I1*tempBufPitch;
    Addr2= I2*32 + I1*dst_h*2;
    Vin1=temp1Ptr[Addr1];
    Vin2=temp2Ptr[Addr1];
     outPtr[Addr2]=Vin1;
    (outPtr+dst_h)[Addr2]=Vin2;
    }
  }
}


void yuv_scalar_chroma_copy_kernel( 
          __vptr_uint8 outPtr,          
          __vptr_uint8 temp1Ptr,          
          __vptr_uint8 temp2Ptr,          
          short int tempBufPitch,    
          short int src_w,    
          short int dst_h
        )
{
    __agen Addr1;
    __agen Addr2;
  __vector Vin1,Vin2,Vin3,Vin4;

  __vector Vzero;
  Vzero = 0;
  for(int I1=0;I1< (src_w+1)/2;I1++)
  {
    for(int I2=0;I2< (dst_h + (VCOP_SIMD_WIDTH-1))/VCOP_SIMD_WIDTH;I2++) 
    {
    Addr1= I2*VCOP_SIMD_WIDTH + I1*tempBufPitch;
    Addr2= I2*VCOP_SIMD_WIDTH*2 + I1*dst_h*2;
    Vin1=temp1Ptr[Addr1];
    Vin2=temp2Ptr[Addr1];
    Vin3 = Vin1 + Vzero;
    Vin4 = Vin2 + Vzero;
     outPtr[Addr2].interleave()= (Vin3,Vin4);
    }
  }
}
























