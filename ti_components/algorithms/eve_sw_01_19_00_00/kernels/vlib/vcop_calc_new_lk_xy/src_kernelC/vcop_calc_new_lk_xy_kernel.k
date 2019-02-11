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
/* NAME: vcop_calc_new_lk_xy_kernel.k                                         */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*         This is vcop implemenation for the vcop_calc_new_lk_xy_cn  kernel  */
/*   This routine accepts tesnsor matrix and the IxIt/IyIT matrix to          */
/*   calculate the new x and y co-oridinates                                  */
/* AUTHOR:                                                                    */
/*             Kumar Desappan(kumar.desappan@ti.com)                          */
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

#define ELMT_SIZE_1  (4)
#define ELMT_SIZE_2  (2)

#define VCOP_LK_PATCH_WIDTH          (7) // 7x7
#define Q_FORMAT_FOR_ERR_VALUE       (10)

void vcop_calc_new_lk_xy
(
    __vptr_uint16 IxItL_a,         
    __vptr_uint16 IyItL_b,        
    __vptr_int16 IxItH_a,         
    __vptr_int16 IyItH_b,        
    __vptr_int16 Ix2_a,        
    __vptr_int16 Iy2_b,        
    __vptr_int16 Ixy_c,        
    __vptr_int16 X_c,
    __vptr_int16 Y_c,
    __vptr_int16 localXY_b,
    __vptr_int16 frameXY_b,
    __vptr_uint16 numValidPoints,
    __vptr_uint8  currValidPoints,        
    __vptr_uint32 pBaseAddrList ,
    __vptr_uint32 pValidAddrList,
    __vptr_uint32 pOutAddrList     ,
    __vptr_uint32 pValidOutAddrList,
    __vptr_int32  vx,
    __vptr_int32  vy,
    unsigned short  qFormatePel,
    unsigned short  minErrValue,
    unsigned char   searchRange,
    unsigned short n
)
{
  /*-----------------------------------------------------------------
  Compiler could not allocate the regusters automaticaly for this loop.
  Manged the registers manually
  ------------------------------------------------------------------*/
  __vector Vec0;
  __vector Vec1;
  __vector Vec2;
  __vector Vec3;
  __vector Vec4;
  __vector Vec5;
  __vector Vec6;
  __vector Vec7;
  __vector Vec8;
  __vector Vec9;
  __vector Vec10;
  __vector Vec11;
  __vector Vec12;
  __vector Vec13;
  __vector Vec14;
  __vector Vec15;
 
  Vec13 = 32;
  Vec15 = 0xFFFFFFFF;
    
  
   /*----------------------------------------------------------------
   vx = ((IxIt_a[k] * Iy2[2*k]) >> Iy2[2*k+1]) - ((IyIt[k] * Ixy[2*k]) >> Ixy[2*k+1]);
   vy = ((IyIt[k] * Ix2[2*k]) >> Ix2[2*k+1]) - ((IxIt[k] * Ixy[2*k]) >> Ixy[2*k+1]);

   A = ((IxIt[k] * Iy2[2*k]) >> Iy2[2*k+1])
   B = ((IyIt[k] * Ixy[2*k]) >> Ixy[2*k+1])
   C = ((IyIt[k] * Ix2[2*k]) >> Ix2[2*k+1])
   D = ((IxIt[k] * Ixy[2*k]) >> Ixy[2*k+1])

   vx = A - B;
   vy = C - D;

   The above computation requires more than 40 VCOP instructions 
   and we can not fit it in one loop. In the first Vsloop we are 
   going to compute  A, B and D So we don't need to load Ix2.
   Since the A and B are availabe we can compure Vx and store it in 
   scratch buffer. The next loop will compute C and to calculate Vy
  -----------------------------------------------------------------*/

  for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
  {        
    __agen Addr1;
    __agen Addr2;
    Addr1 = I1*ELMT_SIZE_1*VCOP_SIMD_WIDTH;
    Addr2 = I1*ELMT_SIZE_2*VCOP_SIMD_WIDTH;

    Vec0           = (IxItL_a )[Addr1].ds2(); 
    Vec2           = (IyItL_b )[Addr1].ds2();  
    Vec8           = (IxItH_a )[Addr1].ds2(); 
    Vec14          = (IyItH_b )[Addr1].ds2();  
    (Vec4,Vec5)    = (Iy2_b  )[Addr1].deinterleave(); //(Iy2Frac Iy2Exp)
    (Vec6,Vec7)    = (Ixy_c  )[Addr1].deinterleave(); //(IxyFrac IxyExp)
    (Vec10,Vec11)  = (Ix2_a  )[Addr1].deinterleave(); //(Ix2Frac Ix2Exp)
    //Vec12          = offsets[Addr2];

    // One load available for expand flag
   
    //((IxIt[k] * Iy2[2*k]) >> Iy2[2*k+1]) -- > A 
    Vec1 = Vec8*Vec4; // IxItH * Iy2Frac;
    Vec3 = Vec0*Vec4; // IxItL * Iy2Frac;
    (Vec9, Vec4) = jus16(Vec1);
    Vec3 += Vec9;             // Add Low
    Vec1  = Vec4 + hi(Vec3);   // Add High
    Vec3 = Vec3 & Vec15;       // AND with MASK
    Vec3 = Vec3 << Vec5;     // Lo >> Exp
    Vec5 += Vec13;             // 32 - Iy2Exp;
    Vec3 |= Vec1 << Vec5;     // Hi << (32 - Exp) // A

    //((IyIt[k] * Ix2[2*k]) >> Ix2[2*k+1])-- > C
    Vec1 = Vec14*Vec10; // IyItH * Ix2Frac;
    Vec5 = Vec2*Vec10;  // IytItL * Ix2Frac;
    (Vec9, Vec10) = jus16(Vec1);
    Vec5 += Vec9;             // Add Low
    Vec1  = Vec10 + hi(Vec5);   // Add High
    Vec5 = Vec5 & Vec15;       // AND with MASK
    Vec5 = Vec5 << Vec11;     // Lo >> Exp
    Vec11 += Vec13;             // 32 - Iy2Exp;
    Vec5 |= Vec1 << Vec11;     // Hi << (32 - Exp) // C



    //((IyIt[k] * Ixy[2*k]) >> Ixy[2*k+1])-- > B
    Vec1 = Vec14*Vec6; // IyItH * IxyFrac;
    Vec10 = Vec2*Vec6; // IytItL * IxyFrac;
    (Vec9, Vec4) = jus16(Vec1);
    Vec10 += Vec9;             // Add Low
    Vec1  = Vec4 + hi(Vec10);   // Add High
    Vec10 = Vec10 & Vec15;       // AND with MASK
    Vec10    = Vec10 << Vec7;     // Lo >> Exp
    Vec2   = Vec7 + Vec13;             // 32 - Iy2Exp;
    Vec10   |= Vec1 << Vec2;     // Hi << (32 - Exp) // B

    Vec11 = Vec3 - Vec10; // A-B Vx

    //((IxIt[k] * Ixy[2*k]) >> Ixy[2*k+1])-- > D
    Vec1 = Vec8*Vec6; // IxItH * IxyFrac;
    Vec3 = Vec0*Vec6; // IxtItL * IxyFrac;
    (Vec9, Vec4) = jus16(Vec1);
    Vec3 += Vec9;             // Add Low
    Vec1  = Vec4 + hi(Vec3);   // Add High
    Vec3 = Vec3 & Vec15;       // AND with MASK
    Vec3   = Vec3 << Vec7;     // Lo >> Exp
    Vec3   |= Vec1 << Vec2;     // Hi << (32 - Exp)
    Vec10 = Vec5 - Vec3; // C-D Vy


    //(vx)[Addr1].s_scatter(Vec12)=Vec11 ;
    //(vy)[Addr1].s_scatter(Vec12)=Vec10 ;  
   // offsets[Addr2] = Vec13;
    (vx)[Addr1] = Vec11 ;
    (vy)[Addr1] = Vec10 ;  

  }
  Vec1  =   ((VCOP_LK_PATCH_WIDTH/2+1) << qFormatePel);
  Vec3  =   (((searchRange*2) + VCOP_LK_PATCH_WIDTH- VCOP_LK_PATCH_WIDTH/2 -2) << qFormatePel);
  Vec9  = 0;
  Vec15 = 0;
  Vec13 = minErrValue >> (Q_FORMAT_FOR_ERR_VALUE - qFormatePel);
#if 1
  for (int I2 = 0; I2 < 1 ; I2++)
  {        
    __agen Addr0;
    Addr0 = 0;
    for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
    {        
      __agen Addr1;
      __agen Addr2;
      __agen Addr3;

      Addr1 = I1*ELMT_SIZE_1*VCOP_SIMD_WIDTH;
      Addr2 = I1*ELMT_SIZE_2*VCOP_SIMD_WIDTH;
      Addr3 = I1*VCOP_SIMD_WIDTH;
    
      Vec14        = (vx)[Addr1];    // Vx
      Vec2         = (vy)[Addr1];    // Vy
      (Vec4,Vec5)  = (localXY_b  )[Addr1].deinterleave(); //(frame X Y)
      (Vec6,Vec7)  = (frameXY_b  )[Addr1].deinterleave(); //(frame X Y)
      Vec0         = currValidPoints[Addr3];
      Vec8         = pBaseAddrList[Addr1];
      Vec10        = pOutAddrList[Addr1];

      Vec2  = Vec0 * Vec2;
      Vec14 = Vec0 * Vec14;

      Vec11  = (Vec4 < Vec1);
      Vec12  = (Vec5 < Vec1);
      Vec12  = Vec11 | Vec12;

      Vec11  = (Vec4 >= Vec3);
      Vec0  = (Vec5 >= Vec3);


      Vec11   = Vec11 | Vec0;
      Vec12  = Vec11 | Vec12;

      Vec14   = select(Vec12, Vec9, Vec14); //select 0 or Vx
      Vec2   = select(Vec12, Vec9, Vec2); //select 0 or Vy
#if 1
      Vec0 = Vec9 - Vec1;

      Vec11  = (Vec2 <= Vec0);
      Vec2   = select(Vec11, Vec0, Vec2); //select 0 or Vx
 
      Vec11  = (Vec2 >= Vec1);
      Vec2   = select(Vec11, Vec1, Vec2); //select 0 or Vx

      Vec11  = (Vec14 <= Vec0);
      Vec14   = select(Vec11, Vec0, Vec14); //select 0 or Vx
 
      Vec11  = (Vec14 >= Vec1);
      Vec14   = select(Vec11, Vec1, Vec14); //select 0 or Vx
#endif

      Vec4  = Vec4 +  Vec14;  //Vy
      Vec5  = Vec5 +  Vec2;  //Vy
 
      Vec6  = Vec6 +  Vec14;  //Vy
      Vec7  = Vec7 +  Vec2;  //Vy

      Vec14 =  abs(Vec14);
      Vec2  =  abs(Vec2);

      Vec12 = Vec14 > Vec13;  // Early EXIT condition
      Vec11 = Vec2  > Vec13;  // Early EXIT condition
      Vec0  = Vec12 | Vec11; // Valid key Points

      Vec12 = transpose_bits(Vec0);
      Vec12 = count_bits(Vec12);
      Vec15 += Vec12;

      (X_c  )[collate(Vec0)]            = Vec4;
      (Y_c  )[collate(Vec0)]            = Vec5;
      pValidAddrList[collate(Vec0)]     = Vec8;
      pValidOutAddrList[collate(Vec0)]  = Vec10;      
      (frameXY_b  )[Addr1].interleave() = (Vec6,Vec7);
      (localXY_b  )[Addr1].interleave() = (Vec4,Vec5);
      currValidPoints[Addr3]            = Vec0;
    }
    numValidPoints[Addr0].onept()       = Vec15;
  }       
#else
  for (int I2 = 0; I2 < 1 ; I2++)
  {        
    __agen Addr0;
    Addr0 = 0;
    for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
    {        
      __agen Addr1;
      __agen Addr2;
      __agen Addr3;

      Addr1 = I1*ELMT_SIZE_1*VCOP_SIMD_WIDTH;
      Addr2 = I1*ELMT_SIZE_2*VCOP_SIMD_WIDTH;
      Addr3 = I1*VCOP_SIMD_WIDTH;
    
      Vec14        = (vx)[Addr1];    // Vx
      Vec2         = (vy)[Addr1];    // Vy
      (Vec4,Vec5)  = (localXY_b  )[Addr1].deinterleave(); //(frame X Y)
      (Vec6,Vec7)  = (frameXY_b  )[Addr1].deinterleave(); //(frame X Y)
      Vec0         = currValidPoints[Addr3];

      Vec2  = Vec0 * Vec2;
      Vec14 = Vec0 * Vec14;

      Vec11  = (Vec4 < Vec1);
      Vec12  = (Vec5 < Vec1);
      Vec1  = (Vec4 >= Vec3);
      Vec0  = (Vec5 >= Vec3);


      Vec12  = Vec11 | Vec12;
      Vec1   = Vec1 | Vec0;
      Vec12  = Vec1 | Vec12;

      Vec14   = select(Vec12, Vec9, Vec14); //select 0 or Vx
      Vec2   = select(Vec12, Vec9, Vec2); //select 0 or Vy

      Vec4  = Vec4 +  Vec14;  //Vy
      Vec5  = Vec5 +  Vec2;  //Vy
 
      Vec6  = Vec6 +  Vec14;  //Vy
      Vec7  = Vec7 +  Vec2;  //Vy

      Vec14 =  abs(Vec14);
      Vec2  =  abs(Vec2);

      Vec12 = Vec14 > Vec13;  // Early EXIT condition
      Vec11 = Vec2  > Vec13;  // Early EXIT condition
      Vec0  = Vec12 | Vec11; // Valid key Points

      Vec12 = transpose_bits(Vec0);
      Vec12 = count_bits(Vec12);
      Vec15 += Vec12;

      (X_c  )[collate(Vec0)]            = Vec4;
      (Y_c  )[Addr2]                    = Vec5;
      (frameXY_b  )[Addr1].interleave() = (Vec6,Vec7);
      (localXY_b  )[Addr1].interleave() = (Vec4,Vec5);
      currValidPoints[Addr3]            = Vec0;
    }
    numValidPoints[Addr0].onept()       = Vec15;
  }                                     
  for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
  {        
    __agen Addr2;
    __agen Addr3;

    Addr2 = I1*ELMT_SIZE_2*VCOP_SIMD_WIDTH;
    Addr3 = I1*VCOP_SIMD_WIDTH;
    
    Vec0         = currValidPoints[Addr3];
    Vec2        = Y_c[Addr2];
    (Y_c  )[collate(Vec0)]            = Vec2;
  }
  for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
  {        
    __agen Addr1;
    __agen Addr3;

    Addr1 = I1*ELMT_SIZE_1*VCOP_SIMD_WIDTH;
    Addr3 = I1*VCOP_SIMD_WIDTH;
    
    Vec0         = currValidPoints[Addr3];
    Vec2         = pBaseAddrList[Addr1];
    (pValidAddrList  )[collate(Vec0)]            = Vec2;
  }
  for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
  {        
    __agen Addr1;
    __agen Addr3;

    Addr1 = I1*ELMT_SIZE_1*VCOP_SIMD_WIDTH;
    Addr3 = I1*VCOP_SIMD_WIDTH;
    
    Vec0         = currValidPoints[Addr3];
    Vec2        = pOutAddrList[Addr1];
    (pValidOutAddrList  )[collate(Vec0)]            = Vec2;
  }
#endif
} 



/*----------------------------------------------------------------------------*/
/* End of file:vcop_calc_new_lk_xy_kernel.k                                   */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
