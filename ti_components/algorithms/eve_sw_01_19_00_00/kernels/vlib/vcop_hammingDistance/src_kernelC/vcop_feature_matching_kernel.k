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

/*--------------------------------------------------------------------------*/
/* NAME: vcop_feature_matching_kernel.k                                     */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing hamming distance between two      */
/* input byte array string pointers each having "ysize" number of byte      */
/* array elements each having a size of "xsize" and pitch of "xpitch" in    */
/* bytes Hamming distance indicates the total number of bit locations       */
/* wherein the two input strings differ.                                    */
/*                                                                          */
/* Hamming distance kernel accepts two input byte array string pointers of  */
/* type unsigned char in "pString1", "pString2" of length "ysize * xpitch"  */
/* in bytes. The kernel writes the result in an unsigned int output pointer */
/* "pHammingDistance"                                                       */
/*                                                                          */
/* The following functions are supported:                                   */
/*  1. vcop_featureMatching_32 - Used for computing hamming distance        */
/*     when "xsize" is 32 bytes                                             */
/*                                                                          */
/*  2. vcop_featureMatching_lt_32 - Used for computing hamming              */
/*     distance when "xsize" is less than 32 bytes                          */
/*                                                                          */
/*  3. vcop_featureMatching_gt_32 - Used for computing hamming distance     */
/*     when the "xsize" is greater than 32 bytes                            */
/*                                                                          */
/*  Computes the hamming distance between two input byte array              */
/*  string pointers. Each byte array pointer is represented                 */
/*  as depicted below                                                       */
/*  Supports the following two modes                                        */
/*    1. mode = 0 :Many-to-16                                               */
/*       pHammingDistance[i] = HammingDistance(bytearr1[i],                 */
/*                                             bytearr2[0:15]);             */
/*    2. mode = 1 :One-to-One                                               */
/*       pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[i]);   */
/*    where i = 0,1,2, ...ySize-1                                           */
/*                                                                          */
/*              xpitch                             xpitch                   */
/*    <----------------------->          <----------------------->          */
/*         xsize                              xsize                         */
/*    <---------->                       <---------->                       */
/*    |-----------------------|          |-----------------------|          */
/*    |bytearr1[0]            |          |bytearr2[0]            |          */
/*    |-----------------------|          |-----------------------|          */
/*    |bytearr1[1]            |          |bytearr2[1]            |          */
/*    |-----------------------|          |-----------------------|          */
/*    |                       |          |                       |          */
/*    |                       |          |                       |          */
/*    |-----------------------|          |-----------------------|          */
/*    |bytearr1[ysize-1]      |          |bytearr2[ysize-1]      |          */
/*    |-----------------------|          |-----------------------|          */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Input strings are of 8-bit                                          */
/*   2. "xsize" & "xpitch" is specified in bytes                            */
/*   3. Maximum value of "ysize*xpitch" is 4096 bytes                       */
/*                                                                          */
/*   @version 1.0 (Sept 2014) : Base version.                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ              sizeof(*pString1)
#define ELEMSZBYTE          sizeof(*pStringByte1)
#define VECTORSZ            (2 * VCOP_SIMD_WIDTH*ELEMSZ)
#define VECTORSZBYTE        (2 * VCOP_SIMD_WIDTH*ELEMSZBYTE)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)
#define VCOP_4SIMD_WIDTH    (4 * VCOP_SIMD_WIDTH)
#define VCOP_8SIMD_WIDTH    (8 * VCOP_SIMD_WIDTH)

#define LOOP1_CNT ((2-mode)*(2-mode)*(2-mode)*(2-mode))
#define SCATTER_OFST_NP1 (4*9)
#define SCATTER_OFST_17_WORDS (4*17)

#define MAX_16BIT (65535)

/**************************************************************************/
/* Kernels for Hamming distance based Feature Matching applet             */
/**************************************************************************/
/*                                                                        */
/*  vcop_featureMatching_32 - Used for computing Hamming distances when   */
/*  "xsize" is 32 bytes. Index of string1 is packed in the lower 16 bits  */
/*  and Hamming distance is packed in the upper 16 bits of each 32 bit    */
/*  output element. The string 1 indices starts from 'startIdx'.          */
/*  In mode 0, string 2 should have 16 byte array elements where as in    */
/*  mode 1, it should have same number of byte array elements as string 1 */
/*  (i.e. 'ysize' elements).                                              */
/*                                                                        */
/**************************************************************************/
void vcop_featureMatching_32
(
  __vptr_uint32  pString1,          // input 1 data pointer
  __vptr_uint32  pString2,          // input 2 data pointer
  __vptr_uint8   pScratch,          // scratch pointer
  __vptr_uint16  pHammingDistance,  // output data pointer
  unsigned int   ysize,             // number of byte array elements in input string 1
  unsigned int   mode,              // mode 0: All in Str1 to 16 in Str2; mode 1: one to one
  unsigned int   xpitch,            // pitch of each input string byte array element
  short          startIdx
)
{
  for(int I2 = 0; I2 < (ysize+1)/2; I2++)
  {
    __agen Addr1;
    __vector Vin11, Vin12;

    Addr1 = I2*2*xpitch;

    Vin11 = pString1[Addr1];
    Vin12 = (pString1 + xpitch)[Addr1];

    for(int I1 = 0; I1 < LOOP1_CNT; I1++)
    {
      __agen Addr2, AddrOut;
      __vector Vout1, Vout2, Vin21, Vin22;
      __vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;

      Addr2 = I1*xpitch + I2*2*xpitch*mode;
      AddrOut = I1*2*sizeof(*pScratch) + I2*SCATTER_OFST_NP1*VCOP_SIMD_WIDTH;

      // Load even elements/descriptors from both strings
      Vin21 = pString2[Addr2];

      // Load odd elements/descriptors from both strings
      Vin22 = (pString2 + xpitch*mode)[Addr2];

      // Takes 1 cycle using two functional units in parallel
      Vxor1 = Vin11 ^ Vin21;
      Vxor2 = Vin12 ^ Vin22;

      // Takes 1 cycles using two functional units in parallel
      Vout1 = count_bits(Vxor1);
      Vout2 = count_bits(Vxor2);

      pScratch[AddrOut].offset_np1() = Vout1.saturate(0x0, 0x0, 0xFF, 0xFF);
      (pScratch + sizeof(*pScratch))[AddrOut].offset_np1() = Vout2.saturate(0x0, 0x0, 0xFF, 0xFF);
    }
  }

  //Sum the counts within the scratch buffer vector to get the final
  //hamming distance output
  for(int I1 = 0; I1 < 2; I1++)
  {
    for(int I2 = 0; I2 < (ysize+1)/2; I2++)
    {
      __agen AddrOut;
      __vector Vout1, Vout2;

      AddrOut = I1*VCOP_SIMD_WIDTH*4 + I2*2*4*VCOP_2SIMD_WIDTH;

      Vout1 = 0;
      Vout2 = 0;

      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH; I3++)
      {
        __agen AddrIn;
        __vector Vin1, Vin2;

        AddrIn = I1*VCOP_2SIMD_WIDTH*sizeof(*pScratch) + I2*SCATTER_OFST_NP1*VCOP_SIMD_WIDTH + I3*SCATTER_OFST_NP1;

        (Vin1, Vin2) = pScratch[AddrIn].deinterleave();

        Vout1 += Vin1;
        Vout2 += Vin2;
      }

      (pHammingDistance + 2)[AddrOut].skip() = Vout1.saturate(0x0, 0x0, 0xFFFF, 0xFFFF);
      (pHammingDistance + VCOP_2SIMD_WIDTH*4 + 2)[AddrOut].skip() = Vout2.saturate(0x0, 0x0, 0xFFFF, 0xFFFF);
    }
  }

  __vector Vidx1;

  Vidx1 = startIdx - 1;

  for(int I1 = 0; I1 < ysize; I1++)
  {
    __agen AddrOut;
    __vector VK1;

    AddrOut = I1*4*VCOP_2SIMD_WIDTH;

    VK1 = 1;

    Vidx1 += VK1;

    pHammingDistance[AddrOut].skip() = Vidx1;
    (pHammingDistance + 4*VCOP_SIMD_WIDTH)[AddrOut].skip() = Vidx1;
  }
}

/**************************************************************************/
/*  vcop_featureMatching_lt_32 - Used for computing hamming distances     */
/*  when the element or descriptor size ("xsize") is less than 32         */
/*  bytes. In the output buffer pHammingDistance, Index of string1 is     */
/*  packed in the lower 16 bits and Hamming distance is packed in the     */
/*  upper 16 bits of each 32 bit output element. The string 1 indices     */
/*  starts from 'startIdx'. In mode 0, string 2 should have 16 byte       */
/*  array elements where as in mode 1, it should have same number of      */
/*  byte array elements as string 1 (i.e. 'ysize' elements).              */
/**************************************************************************/
void vcop_featureMatching_lt_32
(
  __vptr_uint32  pString1,          // input 1 data pointer
  __vptr_uint32  pString2,          // input 2 data pointer
  __vptr_uint32  pDescriptorMask,   // Mask to indicate valid bits within a descriptor
  __vptr_uint8   pScratch,          // scratch pointer
  __vptr_uint16  pHammingDistance,  // output data pointer
  unsigned int   ysize,             // number of byte array elements in input string 1
  unsigned int   mode,              // mode 0: many to 16; mode 1: one to one
  unsigned int   xpitch,            // pitch of each input string byte array element
  short          startIdx
)
{
  __agen Addr0;
  __vector Vmask;

  Addr0 = 0;

  Vmask = pDescriptorMask[Addr0];

  //Compute the hamming distance vector outputs
  for(int I2 = 0; I2 < (ysize+1)/2; I2++)
  {
    __agen Addr1;
    __vector Vin11, Vin12;

    Addr1 = I2*2*xpitch;

    Vin11 = (pString1)[Addr1];
    Vin12 = (pString1 + xpitch)[Addr1];

    for(int I1 = 0; I1 < LOOP1_CNT; I1++)
    {
      __agen Addr2, AddrOut;
      __vector Vin21, Vin22, Vxor1, Vxor2;
      __vector Vtemp1, Vtemp2, Vout1, Vout2;

      Addr2 = I1*xpitch + I2*2*xpitch*mode;
      AddrOut = I1*2*sizeof(*pScratch) + I2*SCATTER_OFST_NP1*VCOP_SIMD_WIDTH;

      Vin21 = (pString2)[Addr2];
      Vin22 = (pString2 + xpitch*mode)[Addr2];

      // Takes 1 cycle using two functional units in parallel
      Vxor1 = Vin11 ^ Vin21;
      Vxor2 = Vin12 ^ Vin22;

      Vtemp1 = Vxor1 & Vmask;
      Vtemp2 = Vxor2 & Vmask;

      // Takes 1 cycles using two functional units in parallel
      Vout1 = count_bits(Vtemp1);
      Vout2 = count_bits(Vtemp2);

      pScratch[AddrOut].offset_np1() = Vout1.saturate(0x0, MAX_16BIT);
      (pScratch + sizeof(*pScratch))[AddrOut].offset_np1() = Vout2.saturate(0x0, MAX_16BIT);
    }
  }

  //Sum the counts within the scratch buffer vector to get the final
  //hamming distance output
  for(int I1 = 0; I1 < 2; I1++)
  {
    for(int I2 = 0; I2 < (ysize+1)/2; I2++)
    {
      __agen AddrOut;
      __vector Vout1, Vout2;

      AddrOut = I1*VCOP_SIMD_WIDTH*4 + I2*2*4*VCOP_2SIMD_WIDTH;

      Vout1 = 0;
      Vout2 = 0;

      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH; I3++)
      {
        __agen AddrIn;
        __vector Vin1, Vin2;

        AddrIn = I1*VCOP_2SIMD_WIDTH*sizeof(*pScratch) + I2*SCATTER_OFST_NP1*VCOP_SIMD_WIDTH + I3*SCATTER_OFST_NP1;

        (Vin1, Vin2) = pScratch[AddrIn].deinterleave();

        Vout1 += Vin1;
        Vout2 += Vin2;
      }

      (pHammingDistance + 2)[AddrOut].skip() = Vout1.saturate(0x0, MAX_16BIT);
      (pHammingDistance + VCOP_2SIMD_WIDTH*4 + 2)[AddrOut].skip() = Vout2.saturate(0x0, MAX_16BIT);
    }
  }

  __vector Vidx1;

  Vidx1 = startIdx - 1;

  for(int I1 = 0; I1 < ysize; I1++)
  {
    __agen AddrOut;
    __vector VK1;

    AddrOut = I1*4*VCOP_2SIMD_WIDTH;

    VK1 = 1;

    Vidx1 += VK1;

    pHammingDistance[AddrOut].skip() = Vidx1;
    (pHammingDistance + 4*VCOP_SIMD_WIDTH)[AddrOut].skip() = Vidx1;
  }
}


/**************************************************************************/
/*  vcop_featureMatching_gt_32 - Used for computing hamming distances     */
/*  when the element or descriptor size ("xsize") is greater than 32      */
/*  bytes. In the output buffer pHammingDistance, Index of string1 is     */
/*  packed in the lower 16 bits and Hamming distance is packed in the     */
/*  upper 16 bits of each 32 bit output element. The string 1 indices     */
/*  starts from 'startIdx'. In mode 0, string 2 should have 16 byte       */
/*  array elements where as in mode 1, it should have same number of      */
/*  byte array elements as string 1 (i.e. 'ysize' elements).              */
/**************************************************************************/
void vcop_featureMatching_gt_32
(
  __vptr_uint32  pString1,          // input 1 data pointer
  __vptr_uint32  pString2,          // input 2 data pointer
  __vptr_uint32  pDescriptorMask,   // Mask to indicate valid bits within a descriptor
  __vptr_uint16  pScratch,          // scratch pointer
  __vptr_uint16  pScatterOffsets,   // Vector of 8 offsets for parallel scatter stores (0:7)*68
  __vptr_uint16  pHammingDistance,  // output data pointer
  unsigned int   xsize,             // size of input string element in bytes
  unsigned int   ysize,             // number of byte array elements in input string 1
  unsigned int   mode,              // mode 0: many to 16; mode 1: one to one
  unsigned int   xpitch,            // pitch of each input string byte array element
  short          startIdx
)
{
  __agen Addr0;
  __vector Voffs;

  Addr0 = 0;

  Voffs = pScatterOffsets[Addr0];

  for(int I2 = 0; I2 < (ysize+1)/2; I2++)
  {
    for(int I1 = 0; I1 < LOOP1_CNT; I1++)
    {
      __vector Vout1, Vout2;
      __agen AddrOut;

      AddrOut = I1*2*sizeof(*pScratch) + I2*SCATTER_OFST_17_WORDS*VCOP_SIMD_WIDTH;

      Vout1 = 0;
      Vout2 = 0;

      //Compute the hamming distance vector outputs for the bytes up to
      //the next nearest multiple of VCOP_4SIMD_WIDTH for 'xsize' parameter
      for (int I3 = 0; I3 < (xsize + VCOP_4SIMD_WIDTH - 1)/VCOP_4SIMD_WIDTH; I3++)
      {
        __agen Addr1, Addr2, AddrMask;
        __vector Vin11, Vin12, Vin21, Vin22;
        __vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;
        __vector Vmask, Vtemp1, Vtemp2;

        Addr1 = I2*2*xpitch + I3*VCOP_4SIMD_WIDTH;
        Addr2 = I1*xpitch + I2*2*xpitch*mode + I3*VCOP_4SIMD_WIDTH;
        AddrMask = I3*VCOP_4SIMD_WIDTH;

        Vin11 = (pString1)[Addr1];
        Vin21 = (pString2)[Addr2];

        Vin12 = (pString1 + xpitch)[Addr1];
        Vin22 = (pString2 + xpitch*mode)[Addr2];

        Vmask = pDescriptorMask[AddrMask];

        // Takes 1 cycle using two functional units in parallel
        Vxor1 = Vin11 ^ Vin21;
        Vxor2 = Vin12 ^ Vin22;

        Vtemp1 = Vxor1 & Vmask;
        Vtemp2 = Vxor2 & Vmask;

        // Takes 1 cycles using two functional units in parallel
        Vbitcnt1 = count_bits(Vtemp1);
        Vbitcnt2 = count_bits(Vtemp2);

        Vout1 += Vbitcnt1;
        Vout2 += Vbitcnt2;
      }
      pScratch[AddrOut].p_scatter(Voffs) = Vout1.saturate(0x0, MAX_16BIT);
      (pScratch + sizeof(*pScratch))[AddrOut].p_scatter(Voffs) = Vout2.saturate(0x0, MAX_16BIT);
    }
  }

  //Sum the counts within the scratch buffer vector to get the final
  //hamming distance output
  for(int I1 = 0; I1 < 2; I1++)
  {
    for(int I2 = 0; I2 < (ysize+1)/2; I2++)
    {
      __agen AddrOut;
      __vector Vout1, Vout2;

      AddrOut = I1*VCOP_SIMD_WIDTH*4 + I2*2*4*VCOP_2SIMD_WIDTH;

      Vout1 = 0;
      Vout2 = 0;

      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH; I3++)
      {
        __agen AddrIn;
        __vector Vin1, Vin2;

        AddrIn = I1*VCOP_2SIMD_WIDTH*sizeof(*pScratch) + I2*SCATTER_OFST_17_WORDS*VCOP_SIMD_WIDTH + I3*SCATTER_OFST_17_WORDS;

        (Vin1, Vin2) = pScratch[AddrIn].deinterleave();

        Vout1 += Vin1;
        Vout2 += Vin2;
      }

      (pHammingDistance + 2)[AddrOut].skip() = Vout1.saturate(0x0, MAX_16BIT);
      (pHammingDistance + VCOP_2SIMD_WIDTH*4 + 2)[AddrOut].skip() = Vout2.saturate(0x0, MAX_16BIT);
    }
  }

  __vector Vidx1;

  Vidx1 = startIdx - 1;

  for(int I1 = 0; I1 < ysize; I1++)
  {
    __agen AddrOut;
    __vector VK1;

    AddrOut = I1*4*VCOP_2SIMD_WIDTH;

    VK1 = 1;

    Vidx1 += VK1;

    pHammingDistance[AddrOut].skip() = Vidx1;
    (pHammingDistance + 4*VCOP_SIMD_WIDTH)[AddrOut].skip() = Vidx1;
  }
}


void vcop_featureMatch_initialize
(
  __vptr_uint32 pMinDist0,
  __vptr_uint32 pMinDist1,
  unsigned int  m
)
{
  for(int I1 = 0; I1 < (m + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I1++) {
    __agen AddrOut;
    __vector VK;

    AddrOut = I1*4*VCOP_SIMD_WIDTH;

    VK = 0xFFFFFFFF;

    pMinDist0[AddrOut] = VK;
    pMinDist1[AddrOut] = VK;
  }
}


void vcop_findTwoBestMatches
(
  __vptr_uint32 pHammingDistance,   // n * 16
  __vptr_uint32 pMinDist0,          // 1 * 16
  __vptr_uint32 pMinDist1,          // 1 * 16
  unsigned char stride,
  unsigned int  n
)
{
  for(int I0 = 0; I0 < 1; I0++) {
    __agen Addr0;
    __vector Vmin00, Vmin01, Vmin10, Vmin11;

    Addr0 = I0;

    Vmin00 = pMinDist0[Addr0];
    Vmin01 = (pMinDist0 + VCOP_SIMD_WIDTH*4)[Addr0];

    Vmin10 = pMinDist1[Addr0];
    Vmin11 = (pMinDist1 + VCOP_SIMD_WIDTH*4)[Addr0];

    for(int I1 = 0; I1 < n; I1++) {
      __agen AddrIn;
      __vector Vin0, Vin1;

      AddrIn = I1*4*stride;

      Vin0 = pHammingDistance[AddrIn];
      Vin1 = (pHammingDistance + VCOP_SIMD_WIDTH*4)[AddrIn];

      (Vmin00, Vin0).minmax();
      (Vmin01, Vin1).minmax();

      (Vmin10, Vin0).minmax();
      (Vmin11, Vin1).minmax();
    }

    pMinDist0[Addr0] = Vmin00;
    (pMinDist0 + VCOP_SIMD_WIDTH*4)[Addr0] = Vmin01;

    pMinDist1[Addr0] = Vmin10;
    (pMinDist1 + VCOP_SIMD_WIDTH*4)[Addr0] = Vmin11;
  }
}


void vcop_pickConfidentMatches
(
  __vptr_uint16  pMinDist0,          // m (hamDist, Idx) pairs for the minima
  __vptr_uint16  pMinDist1,          // m (hamDist, Idx) pairs for second minima
  __vptr_uint16  pMatchIndex,
  unsigned int   m,
  unsigned short minDistanceThres,
  unsigned short matchConfidence
)
{
  for(int I1 = 0; I1 < (m + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I1++) {
    __agen AddrIn, AddrOut;
    __vector VminDist0, VminDist1, Vidx, Vout;
    __vector Vthresh, Vmc;
    __vector Vflag, Vflag1, Vflag2, Vlim;

    AddrIn = I1*VCOP_SIMD_WIDTH*4;
    AddrOut = I1*VCOP_SIMD_WIDTH*2;

    (Vidx, VminDist0) = pMinDist0[AddrIn].deinterleave();
    VminDist1 = (pMinDist1 + 2)[AddrIn].ds2();

    Vthresh = minDistanceThres;
    Vmc = 32768 - matchConfidence;
    Vout = 0xFFFF;

    Vflag1 = Vthresh >= VminDist0;
    Vlim = (Vmc*VminDist1).truncate(15);

    Vflag2 = Vlim >= VminDist0;

    Vflag = Vflag1 & Vflag2;

    Vout = select(Vflag, Vidx, Vout);

    pMatchIndex[AddrOut] = Vout;
  }
}


/* vcop_featureMatch_32_pblk_update - For updating address of pString2 */
/* parameter entry in the param block of the vcop_featureMatching_32   */
/* kernel and pMinDist0 and pMinDist1 of the vcop_findTwoBestMatches   */
/* kernel.                                                             */
void vcop_featureMatch_32_pblk_update
(
  __vptr_uint32  pFeatureMatchParamBlk,
  __vptr_uint32  pBestMatchesParamBlk,
  unsigned short str2ByteIncr,
  unsigned short minDistIncr
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vstr2, Vincr, Vstr2_new;
    __vector VminDist0, VminDist1, VminDistIncr;
    __vector VminDist0_, VminDist1_;
    __vector VK32;

    Addr0 = I1;

    Vincr = str2ByteIncr;
    VminDistIncr = minDistIncr;

    VK32 = 32;

    Vstr2 = (pFeatureMatchParamBlk + 12)[Addr0].onept();
    VminDist0 = (pBestMatchesParamBlk + 28)[Addr0].onept();
    VminDist1 = (pBestMatchesParamBlk + 8)[Addr0].onept();

    Vstr2_new = Vstr2 + Vincr;

    VminDist0 += VminDistIncr;
    VminDist1 += VminDistIncr;

    VminDist0_ = VminDist0 + VK32;
    VminDist1_ = VminDist1 + VK32;

    (pFeatureMatchParamBlk + 12)[Addr0].onept() = Vstr2_new;
    (pFeatureMatchParamBlk + 16)[Addr0].onept() = Vstr2_new;

    (pBestMatchesParamBlk + 28)[Addr0].onept() = VminDist0;
    (pBestMatchesParamBlk + 32)[Addr0].onept() = VminDist0_;
    (pBestMatchesParamBlk + 8)[Addr0].onept()  = VminDist1;
    (pBestMatchesParamBlk + 12)[Addr0].onept() = VminDist1_;
  }
}


/* vcop_featureMatch_32_pblk_reset - For resetting address of pString2 */
/* parameter entry in the param block of the vcop_featureMatching_32   */
/* kernel and pMinDist0 and pMinDist1 of the vcop_findTwoBestMatches   */
/* kernel. The startIdx for vcop_featureMatching_32 is incremented.    */
void vcop_featureMatch_32_pblk_reset
(
  __vptr_int32   pFeatureMatchParamBlk,
  __vptr_uint32  pBestMatchesParamBlk,
  unsigned short startIdxIncr,
  unsigned int   maxStartIdx,
  unsigned int   str2Addr,
  unsigned int   minDist0Addr,
  unsigned int   minDist1Addr
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vidx, Vincr, Vidx_new;
    __vector Vstr2, VminDist0, VminDist1;
    __vector VminDist0_, VminDist1_, VK32;

    Addr0 = I1;

    Vincr = startIdxIncr;
    Vstr2 = str2Addr;
    VminDist0 = minDist0Addr;
    VminDist1 = minDist1Addr;
    VK32 = 32;

    Vidx = (pFeatureMatchParamBlk + 116)[Addr0].onept();

    Vidx_new = Vidx + Vincr;

    VminDist0_ = VminDist0 + VK32;
    VminDist1_ = VminDist1 + VK32;

    (pFeatureMatchParamBlk + 12)[Addr0].onept() = Vstr2;
    (pFeatureMatchParamBlk + 16)[Addr0].onept() = Vstr2;
    (pFeatureMatchParamBlk + 116)[Addr0].onept() = Vidx_new.saturate(0, 0, maxStartIdx, -1);

    (pBestMatchesParamBlk + 28)[Addr0].onept() = VminDist0;
    (pBestMatchesParamBlk + 32)[Addr0].onept() = VminDist0_;
    (pBestMatchesParamBlk + 8)[Addr0].onept()  = VminDist1;
    (pBestMatchesParamBlk + 12)[Addr0].onept() = VminDist1_;
  }
}


/* vcop_featureMatch_lt_32_pblk_update - For updating address of pString2 */
/* parameter entry in the param block of the vcop_featureMatching_lt_32   */
/* kernel and pMinDist0 and pMinDist1 of the vcop_findTwoBestMatches      */
/* kernel.                                                                */
void vcop_featureMatch_lt_32_pblk_update
(
  __vptr_uint32  pFeatureMatchParamBlk,
  __vptr_uint32  pBestMatchesParamBlk,
  unsigned short str2ByteIncr,
  unsigned short minDistIncr
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vstr2, Vincr, Vstr2_new;
    __vector VminDist0, VminDist1, VminDistIncr;
    __vector VminDist0_, VminDist1_;
    __vector VK32;

    Addr0 = I1;

    Vincr = str2ByteIncr;
    VminDistIncr = minDistIncr;

    VK32 = 32;

    Vstr2 = (pFeatureMatchParamBlk + 16)[Addr0].onept();
    VminDist0 = (pBestMatchesParamBlk + 28)[Addr0].onept();
    VminDist1 = (pBestMatchesParamBlk + 8)[Addr0].onept();

    Vstr2_new = Vstr2 + Vincr;

    VminDist0 += VminDistIncr;
    VminDist1 += VminDistIncr;

    VminDist0_ = VminDist0 + VK32;
    VminDist1_ = VminDist1 + VK32;

    (pFeatureMatchParamBlk + 16)[Addr0].onept() = Vstr2_new;
    (pFeatureMatchParamBlk + 20)[Addr0].onept() = Vstr2_new;

    (pBestMatchesParamBlk + 28)[Addr0].onept() = VminDist0;
    (pBestMatchesParamBlk + 32)[Addr0].onept() = VminDist0_;
    (pBestMatchesParamBlk + 8)[Addr0].onept()  = VminDist1;
    (pBestMatchesParamBlk + 12)[Addr0].onept() = VminDist1_;
  }
}


/* vcop_featureMatch_lt_32_pblk_reset - For resetting address of pString2 */
/* parameter entry in the param block of the vcop_featureMatching_lt_32   */
/* kernel and pMinDist0 and pMinDist1 of the vcop_findTwoBestMatches      */
/* kernel. The startIdx for vcop_featureMatching_32 is incremented.       */
void vcop_featureMatch_lt_32_pblk_reset
(
  __vptr_int32   pFeatureMatchParamBlk,
  __vptr_uint32  pBestMatchesParamBlk,
  unsigned short startIdxIncr,
  unsigned int   maxStartIdx,
  unsigned int   str2Addr,
  unsigned int   minDist0Addr,
  unsigned int   minDist1Addr
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vidx, Vincr, Vidx_new;
    __vector Vstr2, VminDist0, VminDist1;
    __vector VminDist0_, VminDist1_, VK32;

    Addr0 = I1;

    Vincr = startIdxIncr;
    Vstr2 = str2Addr;
    VminDist0 = minDist0Addr;
    VminDist1 = minDist1Addr;
    VK32 = 32;

    Vidx = (pFeatureMatchParamBlk + 108)[Addr0].onept();

    Vidx_new = Vidx + Vincr;

    VminDist0_ = VminDist0 + VK32;
    VminDist1_ = VminDist1 + VK32;

    (pFeatureMatchParamBlk + 16)[Addr0].onept() = Vstr2;
    (pFeatureMatchParamBlk + 20)[Addr0].onept() = Vstr2;
    (pFeatureMatchParamBlk + 108)[Addr0].onept() = Vidx_new.saturate(0, 0, maxStartIdx, -1);

    (pBestMatchesParamBlk + 28)[Addr0].onept() = VminDist0;
    (pBestMatchesParamBlk + 32)[Addr0].onept() = VminDist0_;
    (pBestMatchesParamBlk + 8)[Addr0].onept()  = VminDist1;
    (pBestMatchesParamBlk + 12)[Addr0].onept() = VminDist1_;
  }
}


/* vcop_featureMatch_gt_32_pblk_update - For updating address of pString2 */
/* parameter entry in the param block of the vcop_featureMatching_gt_32   */
/* kernel and pMinDist0 and pMinDist1 of the vcop_findTwoBestMatches      */
/* kernel.                                                                */
void vcop_featureMatch_gt_32_pblk_update
(
  __vptr_uint32  pFeatureMatchParamBlk,
  __vptr_uint32  pBestMatchesParamBlk,
  unsigned short str2ByteIncr,
  unsigned short minDistIncr
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vstr2, Vincr, Vstr2_new;
    __vector VminDist0, VminDist1, VminDistIncr;
    __vector VminDist0_, VminDist1_;
    __vector VK32;

    Addr0 = I1;

    Vincr = str2ByteIncr;
    VminDistIncr = minDistIncr;

    VK32 = 32;

    Vstr2 = (pFeatureMatchParamBlk + 16)[Addr0].onept();
    VminDist0 = (pBestMatchesParamBlk + 28)[Addr0].onept();
    VminDist1 = (pBestMatchesParamBlk + 8)[Addr0].onept();

    Vstr2_new = Vstr2 + Vincr;

    VminDist0 += VminDistIncr;
    VminDist1 += VminDistIncr;

    VminDist0_ = VminDist0 + VK32;
    VminDist1_ = VminDist1 + VK32;

    (pFeatureMatchParamBlk + 16)[Addr0].onept() = Vstr2_new;
    (pFeatureMatchParamBlk + 24)[Addr0].onept() = Vstr2_new;

    (pBestMatchesParamBlk + 28)[Addr0].onept() = VminDist0;
    (pBestMatchesParamBlk + 32)[Addr0].onept() = VminDist0_;
    (pBestMatchesParamBlk + 8)[Addr0].onept()  = VminDist1;
    (pBestMatchesParamBlk + 12)[Addr0].onept() = VminDist1_;
  }
}


/* vcop_featureMatch_gt_32_pblk_reset - For resetting address of pString2 */
/* parameter entry in the param block of the vcop_featureMatching_gt_32   */
/* kernel and pMinDist0 and pMinDist1 of the vcop_findTwoBestMatches      */
/* kernel. The startIdx for vcop_featureMatching_32 is incremented.       */
void vcop_featureMatch_gt_32_pblk_reset
(
  __vptr_int32   pFeatureMatchParamBlk,
  __vptr_uint32  pBestMatchesParamBlk,
  unsigned short startIdxIncr,
  unsigned int   maxStartIdx,
  unsigned int   str2Addr,
  unsigned int   minDist0Addr,
  unsigned int   minDist1Addr
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vidx, Vincr, Vidx_new;
    __vector Vstr2, VminDist0, VminDist1;
    __vector VminDist0_, VminDist1_, VK32;

    Addr0 = I1;

    Vincr = startIdxIncr;
    Vstr2 = str2Addr;
    VminDist0 = minDist0Addr;
    VminDist1 = minDist1Addr;
    VK32 = 32;

    Vidx = (pFeatureMatchParamBlk + 120)[Addr0].onept();

    Vidx_new = Vidx + Vincr;

    VminDist0_ = VminDist0 + VK32;
    VminDist1_ = VminDist1 + VK32;

    (pFeatureMatchParamBlk + 16)[Addr0].onept() = Vstr2;
    (pFeatureMatchParamBlk + 24)[Addr0].onept() = Vstr2;
    (pFeatureMatchParamBlk + 120)[Addr0].onept() = Vidx_new.saturate(0, 0, maxStartIdx, -1);

    (pBestMatchesParamBlk + 28)[Addr0].onept() = VminDist0;
    (pBestMatchesParamBlk + 32)[Addr0].onept() = VminDist0_;
    (pBestMatchesParamBlk + 8)[Addr0].onept()  = VminDist1;
    (pBestMatchesParamBlk + 12)[Addr0].onept() = VminDist1_;
  }
}


/* vcop_twoBestMatches_update_n - For updating the parameter 'n'      */
/* specifying the number of valid input hamming distances in the      */
/* kernel vcop_findTwoBestMatches's param block.                      */
void vcop_twoBestMatches_update_n
(
  __vptr_int16   pBestMatchesParamBlk,
  unsigned short n_new
)
{
  for(int I1 = 0; I1 < 1; I1++) {
    __agen Addr0;
    __vector Vn;

    Addr0 = I1;

    Vn = n_new;

    (pBestMatchesParamBlk + 6)[Addr0].onept() = Vn;
  }
}
