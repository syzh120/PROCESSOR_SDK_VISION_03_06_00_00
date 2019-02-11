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
/* NAME: vcop_sad_error_measure_lk_kernel.k                                 */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                   This file contains the VCOP implementation of the      */
/*     function for computing SAD (Sum of Absolute Differences) based error */
/*     measure for each key point. It will also incorporate boundary check  */
/*     compute and initializes error to 0xFFFF for out of bound key points  */
/*     The following figure illustrates the input data arrangement of the   */
/*     bilinear interpolated patch windows for both previous and current    */
/*     frames across each key point.                                        */
/*                                                                          */
/*                           (inputStride) bytes                            */
/*                            (blkWidth) bytes                              */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (blkHeight)     |        Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |        Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |  Blk(numKeyPoints-1)  |                           */
/*                      |_______________________|                           */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. X,Y coordinates are of 16 bit (Q12.4) and are in interleaved fashion*/
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_sad_error_measure_lk:                                             */
/*   - ~ 1/16 * 64 (instead of 49)  = 4 cycle per point + 25/8 overhead     */
/*                                  = 7.x cycles per point                  */
/*                                                                          */
/* version 1.0 (January 2014) : Base version.                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pPrevBiLinImg_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pOutErrorMeasure_C)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define TRANSPOSE_STRIDE    (36)
#define VCOP_LK_PATCH_WIDTH (7)

void vcop_sad_error_measure_lk
(
   __vptr_uint8      pPrevBiLinImg_A,
   __vptr_uint8      pCurrBiLinImg_B,
   __vptr_uint16     pNewXYList_X,
   __vptr_uint16     pOutErrorMeasure_C,
   unsigned short    inputStride,
   unsigned short    frmWidth,
   unsigned short    frmHeight,
   unsigned short    blkWidth,
   unsigned short    blkHeight,
   unsigned short    numKeyPoints,
   unsigned short    shiftValue,
   __vptr_uint16     scratch_a,
   unsigned short    sadThreshold,
   __vptr_uint16     numInvalidPointsWbuf,/* Pointer in work buffer to store number of invalid points as per sad threshold ie. points whose sad is greater than sad threshold */
   __vptr_uint16     numInvalidPointsIbuf/* Pointer in image buffer to store number of invalid points as per sad threshold ie. points whose sad is greater than sad threshold */
)
{
  __agen   inAddr1;       //Address generator for the previous frame pixel
  __agen   inAddr2;       //Address generator for the current frame pixel
  __agen   outAddr;       //Address generator for the SAD based error measure output
  __agen   addr0;
  __vector VnumInvalidPts;


  for (int I0 = 0; I0 < (numKeyPoints + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
    for (int I1 = 0; I1 < VCOP_SIMD_WIDTH/2; I1++)
    {
      __vector VimC, VimP, VimC1, VimP1;    //Vector registers to hold the current and previous frame interpolated pixels
      __vector VsumAbsDiff, VsumAbsDiff1;   //Vector register for accumulating absolute difference of current and previous frame pixels

      outAddr = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH + (2*I1)*OUT_ELEMSZ;

      VsumAbsDiff  = 0;
      VsumAbsDiff1 = 0;
      for (int I2 = 0; I2 < blkHeight; I2++)
      {
        inAddr1 = I0*VCOP_SIMD_WIDTH*blkHeight*inputStride*INP_ELEMSZ + (2*I1)*inputStride*blkHeight*INP_ELEMSZ + I2*inputStride*INP_ELEMSZ;
        inAddr2 = I0*VCOP_SIMD_WIDTH*blkHeight*inputStride*INP_ELEMSZ + (2*I1)*inputStride*blkHeight*INP_ELEMSZ + I2*inputStride*INP_ELEMSZ;

        VimP  = pPrevBiLinImg_A[inAddr1];
        VimC  = pCurrBiLinImg_B[inAddr2];

        VimP1 = (pPrevBiLinImg_A + inputStride*blkHeight*INP_ELEMSZ)[inAddr1];
        VimC1 = (pCurrBiLinImg_B + inputStride*blkHeight*INP_ELEMSZ)[inAddr2];

        VsumAbsDiff  += abs(VimC - VimP);
        VsumAbsDiff1 += abs(VimC1 - VimP1);
      }
      //Storing the intermediate sum of absolute differences to scratch in transpose mode to enable SIMD for next loop
      scratch_a[outAddr].offset_np1()                   = VsumAbsDiff;
      (scratch_a + OUT_ELEMSZ)[outAddr].offset_np1()    = VsumAbsDiff1;
    }
  }

  //Accumulate the intermediate SAD's within the vector for each key point
  for (int I0 = 0; I0 < (numKeyPoints + 2*VCOP_SIMD_WIDTH-1)/(2*VCOP_SIMD_WIDTH); I0++)
  {
      __vector Vodd, Veven;
      __vector VsumAbsDiff, VsumAbsDiff1;   //Vector register for accumulating absolute difference of current and previous frame pixels

      outAddr  = I0*OUT_ELEMSZ*2*VCOP_SIMD_WIDTH;
      VsumAbsDiff  = 0;
      VsumAbsDiff1 = 0;
      for (int I2 = 0; I2 < blkHeight; I2++)
      {
        inAddr1  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I2*TRANSPOSE_STRIDE;
        (Vodd, Veven) = scratch_a[inAddr1].deinterleave();
        VsumAbsDiff  += Vodd;
        VsumAbsDiff1 += Veven;
      }
      pOutErrorMeasure_C[outAddr].interleave() = (VsumAbsDiff, VsumAbsDiff1);
  }


  addr0 = 0;

  /* Load the previous valid points from the internal memory */
  VnumInvalidPts = numInvalidPointsWbuf[addr0];

  //Check the boundary conditions and set the flag if it is out of bounds
  //Use select instruction to either store the computed SAD or the default 0xFFFF

  for (int I0 = 0; I0 < (numKeyPoints + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
      __vector Vlimit1, Vlimit2, Vlimit3; //Upper and lower limits for checking the out of bound conditions along X and Y directions
      __vector Vflag, Vflag1, Vflag2;     //Flags for indicating if the out of bound is true or false for each key point
      __vector Vshift;                    //Number of fractional bits in X,Y coordinates to be truncated
      __vector Vmaxerror;                 //Vector registers for constants used in out of bound condition checks
      __vector Verror;                    //Vector register for the SAD based error measure output
      __vector Vxint, Vyint;              //Vector registers to hold the integer pixel locations of key points being tracked
      __vector VsadThreshold;
      __vector VsadFlag;

      VsadThreshold = sadThreshold;



      Vlimit1 = (VCOP_LK_PATCH_WIDTH/2+1);
      Vlimit2 = (frmWidth - VCOP_LK_PATCH_WIDTH/2-2);
      Vlimit3 = (frmHeight - VCOP_LK_PATCH_WIDTH/2-2);
      Vshift  = -shiftValue;
      Vmaxerror = 0xFFFF;

      outAddr  = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH;
      inAddr1  = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH;
      inAddr2  = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH*2;



      Verror = pOutErrorMeasure_C[inAddr1];
      (Vxint, Vyint) = pNewXYList_X[inAddr2].deinterleave();

      /* Check if error is above sad threshold */
      VsadFlag = Verror > VsadThreshold;

      //Compute the integer locations by truncating fractional bits
      Vxint = Vxint << Vshift;
      Vyint = Vyint << Vshift;

      //Check the boundary conditions along X direction
      Vflag1  = Vxint <  Vlimit1;
      Vflag2  = Vxint >= Vlimit2;

      Vflag   = Vflag1 | Vflag2;

      //Compute the boundary conditions along Y direction
      Vflag1  = Vyint <  Vlimit1;
      Vflag2  = Vyint >= Vlimit3;

      Vflag |= Vflag1 | Vflag2;

      VsadFlag  |= Vflag;
      VnumInvalidPts += VsadFlag;

      //Select MAX ERROR if Out of Bound flag is set
      Verror = select(Vflag, Vmaxerror, Verror);

      /* Copy the number of points below SAD treshold in both image and work buffer */
      numInvalidPointsWbuf[addr0] = VnumInvalidPts;
      numInvalidPointsIbuf[addr0] = VnumInvalidPts;
      pOutErrorMeasure_C[outAddr] = Verror;
  }
}

