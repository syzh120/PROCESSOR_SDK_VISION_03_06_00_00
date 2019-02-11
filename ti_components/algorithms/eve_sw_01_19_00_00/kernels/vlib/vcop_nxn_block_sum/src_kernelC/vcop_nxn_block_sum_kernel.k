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

#if (VCOP_HOST_EMULATION)
#include "vcop.h"
#endif

#define IN_ELEMSZ_U8           (1)
#define IN_ELEMSZ_U16          (2)
#define IN_VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

#define OUT_ELEMSZ          sizeof(*outPtr2)
#define VECTORSZ_OUT        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)

#define WORD_SIZE (4)
#define NP1_LINE_OSSFET          ((VCOP_SIMD_WIDTH+1)*WORD_SIZE)
#define NP1_BLK_OSSFET           (NP1_LINE_OSSFET*VCOP_SIMD_WIDTH)


//#define ALIGN_SIZE(x,y) ((x + (y-1)) & (~(y-1)))
#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y) 
#define OFFSET_TO_STEP2           ((ALIGN_SIZE(width,VCOP_SIMD_WIDTH)/(VCOP_SIMD_WIDTH))*((ALIGN_SIZE(height,(VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n))*NP1_BLK_OSSFET))

void vcop_nxn_sum_interleaved
(
  __vptr_uint8     inPtr1,
  __vptr_uint16    outPtr1,
  __vptr_uint16    outPtr2,
  __vptr_uint32    tempPtr1,
  __vptr_uint32    tempPtr2,
  unsigned short   n,
  unsigned short   width,
  unsigned short   height,
  unsigned short   pitch,
  signed short     shiftValue
)
{
  __vector vin1        ;
  __vector vin2        ;
  __vector vin3        ;
  __vector vin4        ;
  __vector vsum1       ;
  __vector vsum2       ;

  __vector vshift       ;

  __agen Addr1;
  __agen Addr2;
  __agen Addr3;

  vshift = shiftValue;

  for(int I1 = 0; I1 < (height/VCOP_SIMD_WIDTH)/n; I1++)
  {
    for(int I2 = 0; I2 < (width)/(VCOP_SIMD_WIDTH); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*pitch*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH*n+ I2*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH*2 + I3*pitch*IN_ELEMSZ_U8*n + I4*pitch*IN_ELEMSZ_U8;
         (vin3,vin4)       = inPtr1[Addr1].deinterleave();
          vsum1      += vin3;
          vsum2      += vin4;
        }
        tempPtr1[Addr2].offset_np1() = vsum1;
        tempPtr2[Addr2].offset_np1() = vsum2;
      }
    }
  }

  for(int I1 = 0; I1 < (height/n)/(VCOP_SIMD_WIDTH); I1++)
  {
    for(int I2 = 0; I2 < (width/VCOP_SIMD_WIDTH)/n; I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*((width/VCOP_SIMD_WIDTH)/n)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_LINE_OSSFET*VCOP_SIMD_WIDTH*n+ I3*NP1_LINE_OSSFET*n + I4*NP1_LINE_OSSFET;
          vin1       = tempPtr1[Addr1];
          vin2       = tempPtr2[Addr1];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        (tempPtr1 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum1;
        (tempPtr2 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum2;
      }
    }
  }
  for(int I1 = 0; I1 < ((height / VCOP_SIMD_WIDTH) /n); I1++)
  {
    for(int I2 = 0; I2 < ((width/n)/VCOP_SIMD_WIDTH); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr1      = I1*OUT_ELEMSZ*(width/n)*VCOP_SIMD_WIDTH + I2*VCOP_SIMD_WIDTH*OUT_ELEMSZ + I3*OUT_ELEMSZ*(width/n);
        Addr2      = I1*((width/n)/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*NP1_LINE_OSSFET;
        vin1       = (tempPtr1 + OFFSET_TO_STEP2)[Addr2];
        vin2       = (tempPtr2 + OFFSET_TO_STEP2)[Addr2];
        vin1 = vin1 << vshift;
        vin2 = vin2 << vshift;
        (outPtr1 )[Addr1] = vin1;
        (outPtr2 )[Addr1] = vin2;
      }
    }
  }
}


void vcop_nxn_sum_u8
(
  __vptr_uint8     inPtr1,
  __vptr_uint8     inPtr2,
  __vptr_uint16    outPtr1,
  __vptr_uint16    outPtr2,
  __vptr_uint32    tempPtr1,
  __vptr_uint32    tempPtr2,
  unsigned short   n,
  unsigned short   width,
  unsigned short   height,
  unsigned short   pitch1,
  unsigned short   pitch2
)
{
  __vector vin1        ;
  __vector vin2        ;
  __vector vsum1       ;
  __vector vsum2       ;

  __agen Addr1;
  __agen Addr2;
  __agen Addr3;

#if 1
  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 <  ALIGN_SIZE(width,VCOP_SIMD_WIDTH)/VCOP_SIMD_WIDTH; I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*pitch1*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH*n+ I2*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH + I3*pitch1*IN_ELEMSZ_U8*n + I4*pitch1*IN_ELEMSZ_U8;
          Addr3      = I1*pitch2*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH*n+ I2*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH + I3*pitch2*IN_ELEMSZ_U8*n + I4*pitch2*IN_ELEMSZ_U8;
          vin1       = inPtr1[Addr1];
          vin2       = inPtr2[Addr3];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        tempPtr1[Addr2].offset_np1() = vsum1;
        tempPtr2[Addr2].offset_np1() = vsum2;
      }
    }
  }

  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 < ALIGN_SIZE(width, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*((width/VCOP_SIMD_WIDTH)/n)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_LINE_OSSFET*VCOP_SIMD_WIDTH*n+ I3*NP1_LINE_OSSFET*n + I4*NP1_LINE_OSSFET;
          vin1       = tempPtr1[Addr1];
          vin2       = tempPtr2[Addr1];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        (tempPtr1 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum1;
        (tempPtr2 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum2;
      }
    }
  }
#endif

  for(int I1 = 0; I1 <  ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 <  ALIGN_SIZE(width, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr1      = I1*OUT_ELEMSZ*(width/n)*VCOP_SIMD_WIDTH + I2*VCOP_SIMD_WIDTH*OUT_ELEMSZ + I3*OUT_ELEMSZ*(width/n);
        Addr2      = I1*((width/n)/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*NP1_LINE_OSSFET;
        vin1       = (tempPtr1 + OFFSET_TO_STEP2)[Addr2];
        vin2       = (tempPtr2 + OFFSET_TO_STEP2)[Addr2];
        (outPtr1 )[Addr1] = vin1;
        (outPtr2 )[Addr1] = vin2;
      }
    }
  }
}


void vcop_nxn_sum_u16
(
  __vptr_uint16     inPtr1,
  __vptr_uint16     inPtr2,
  __vptr_uint16    outPtr1,
  __vptr_uint16    outPtr2,
  __vptr_uint32    tempPtr1,
  __vptr_uint32    tempPtr2,
  unsigned short   n,
  unsigned short   width,
  unsigned short   height,
  unsigned short   pitch1,
  unsigned short   pitch2
)
{
  __vector vin1        ;
  __vector vin2        ;
  __vector vsum1       ;
  __vector vsum2       ;

  __agen Addr1;
  __agen Addr2;
  __agen Addr3;

  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 < ALIGN_SIZE(width,VCOP_SIMD_WIDTH)/(VCOP_SIMD_WIDTH); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*pitch1*IN_ELEMSZ_U16*VCOP_SIMD_WIDTH*n+ I2*IN_ELEMSZ_U16*VCOP_SIMD_WIDTH + I3*pitch1*IN_ELEMSZ_U16*n + I4*pitch1*IN_ELEMSZ_U16;
          Addr3      = I1*pitch2*IN_ELEMSZ_U16*VCOP_SIMD_WIDTH*n+ I2*IN_ELEMSZ_U16*VCOP_SIMD_WIDTH + I3*pitch2*IN_ELEMSZ_U16*n + I4*pitch2*IN_ELEMSZ_U16;
          vin1       = inPtr1[Addr1];
          vin2       = inPtr2[Addr3];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        tempPtr1[Addr2].offset_np1() = vsum1;
        tempPtr2[Addr2].offset_np1() = vsum2;
      }
    }
  }

  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 <  ALIGN_SIZE(width, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*((width/VCOP_SIMD_WIDTH)/n)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_LINE_OSSFET*VCOP_SIMD_WIDTH*n+ I3*NP1_LINE_OSSFET*n + I4*NP1_LINE_OSSFET;
          vin1       = tempPtr1[Addr1];
          vin2       = tempPtr2[Addr1];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        (tempPtr1 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum1;
        (tempPtr2 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum2;
      }
    }
  }
  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 < ALIGN_SIZE(width, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr1      = I1*OUT_ELEMSZ*(width/n)*VCOP_SIMD_WIDTH + I2*VCOP_SIMD_WIDTH*OUT_ELEMSZ + I3*OUT_ELEMSZ*(width/n);
        Addr2      = I1*((width/n)/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*NP1_LINE_OSSFET;
        vin1       = (tempPtr1 + OFFSET_TO_STEP2)[Addr2];
        vin2       = (tempPtr2 + OFFSET_TO_STEP2)[Addr2];
        (outPtr1 )[Addr1] = vin1;
        (outPtr2 )[Addr1] = vin2;
      }
    }
  }
}

void vcop_nxn_sum_u8_u16
(
  __vptr_uint8     inPtr1,
  __vptr_uint16    inPtr2,
  __vptr_uint16    outPtr1,
  __vptr_uint16    outPtr2,
  __vptr_uint32    tempPtr1,
  __vptr_uint32    tempPtr2,
  unsigned short   n,
  unsigned short   width,
  unsigned short   height,
  unsigned short   pitch1,
  unsigned short   pitch2
)
{
  __vector vin1        ;
  __vector vin2        ;
  __vector vsum1       ;
  __vector vsum2       ;

  __agen Addr1;
  __agen Addr2;
  __agen Addr3;

  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 < ALIGN_SIZE(width,VCOP_SIMD_WIDTH)/(VCOP_SIMD_WIDTH); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*pitch1*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH*n  + I2*IN_ELEMSZ_U8*VCOP_SIMD_WIDTH  + I3*pitch1*IN_ELEMSZ_U8*n  + I4*pitch1*IN_ELEMSZ_U8;
          Addr3      = I1*pitch2*IN_ELEMSZ_U16*VCOP_SIMD_WIDTH*n + I2*IN_ELEMSZ_U16*VCOP_SIMD_WIDTH + I3*pitch2*IN_ELEMSZ_U16*n + I4*pitch2*IN_ELEMSZ_U16;
          vin1       = inPtr1[Addr1];
          vin2       = inPtr2[Addr3];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        tempPtr1[Addr2].offset_np1() = vsum1;
        tempPtr2[Addr2].offset_np1() = vsum2;
      }
    }
  }

  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 <  ALIGN_SIZE(width, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr2      = I1*((width/VCOP_SIMD_WIDTH)/n)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*WORD_SIZE;
        vsum1 = 0;
        vsum2 = 0;
        for(int I4 = 0; I4 < n;  I4++)
        {
          Addr1      = I1*(width/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_LINE_OSSFET*VCOP_SIMD_WIDTH*n+ I3*NP1_LINE_OSSFET*n + I4*NP1_LINE_OSSFET;
          vin1       = tempPtr1[Addr1];
          vin2       = tempPtr2[Addr1];
          vsum1      += vin1;
          vsum2      += vin2;
        }
        (tempPtr1 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum1;
        (tempPtr2 + OFFSET_TO_STEP2)[Addr2].offset_np1() = vsum2;
      }
    }
  }
  for(int I1 = 0; I1 < ALIGN_SIZE(height, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I1++)
  {
    for(int I2 = 0; I2 < ALIGN_SIZE(width, (VCOP_SIMD_WIDTH*n))/(VCOP_SIMD_WIDTH*n); I2++)
    {
      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH;  I3++)
      {
        Addr1      = I1*OUT_ELEMSZ*(width/n)*VCOP_SIMD_WIDTH + I2*VCOP_SIMD_WIDTH*OUT_ELEMSZ + I3*OUT_ELEMSZ*(width/n);
        Addr2      = I1*((width/n)/VCOP_SIMD_WIDTH)*NP1_BLK_OSSFET + I2*NP1_BLK_OSSFET + I3*NP1_LINE_OSSFET;
        vin1       = (tempPtr1 + OFFSET_TO_STEP2)[Addr2];
        vin2       = (tempPtr2 + OFFSET_TO_STEP2)[Addr2];
        (outPtr1 )[Addr1] = vin1;
        (outPtr2 )[Addr1] = vin2;
      }
    }
  }
}

