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
/* NAME: vcop_contrast_stretching_kernel.k                                                        */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* VERSION:                                                                   */
/*            0.1 (May 2014) : Base version.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2014.                                  */
/*============================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH  (2*VCOP_SIMD_WIDTH)
#define NUM_COPIES (8)
#define ELEM_SZ_HISTOGRAM   (sizeof(*inputImage))
#define VECTOR_SZ_HISTOGRAM (ELEM_SZ_HISTOGRAM * NUM_COPIES)
#define ROW_SZ_HISTOGRAM    (inPitch * ELEM_SZ_HISTOGRAM)
#define MAX_PIXEL_VAL  (255)

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

void vcop_memset
(
    __vptr_uint32  inPtr,
    unsigned char  value,
    unsigned short size
)
{
  __vector valPtr;
  for ( int i = 0 ; i < ALIGN_2SIMD(size)/(4*VCOP_SIMD_WIDTH) ;i++)
  {
    __agen addr1;

    addr1 = i * VCOP_SIMD_WIDTH * sizeof(*inPtr);
    valPtr = value;

    inPtr[addr1] = valPtr;
  }

}

void vcop_histogram_8c_word
(
    __vptr_uint8  inputImage,
    unsigned short blkWidth,
    unsigned short blkHeight,
    unsigned short inPitch,
    __vptr_uint32 histogram8Copy
)
{
  __vector Vindex, Vweight, Vdata;
  __vector Vout;

  _HISTOGRAM(NUM_COPIES);

  /*--------------------------------------------------------------*/
  /* Initialize the weight of the histogram to 1.                 */
  /*--------------------------------------------------------------*/

  Vweight = 1;

  for (int i3 = 0; i3 < blkHeight; i3++)
  {
    for (int i4 = 0; i4 < blkWidth/NUM_COPIES; i4++)
    {
       __agen hist_agen = 0;
       __agen ind_agen  = i3 * ROW_SZ_HISTOGRAM + i4 * VECTOR_SZ_HISTOGRAM;

       Vindex  = inputImage[ind_agen];

       Vdata   = histogram8Copy[hist_agen].hist_update
                 (
                    Vindex.truncate(0).saturate(0, (MAX_PIXEL_VAL)),
                    Vweight
                 );
    }
  }
}

#define ELEM_SZ_CONTRAST_STRETCHING    (sizeof(*inputImage))
#define VECTOR_SZ_CONTRAST_STRETCHING (VCOP_2SIMD_WIDTH * ELEM_SZ_CONTRAST_STRETCHING)
#define RIGHT_SHIFT_BY_8 (-8)


void vcop_contrast_stretching
(
  __vptr_uint8  inputImage,
  __vptr_uint8 outputImage,
  unsigned short blkWidth,
  unsigned short blkHeight,
  unsigned short inPitch,
  unsigned short outPitch,
  unsigned char  minVal,
  unsigned short scaleFactorQ16
)
{
  __vector VremappedValueQ16_1;
  __vector VremappedValueQ16_2;
  __vector VinterimVal1;
  __vector VinterimVal2;
  __vector VpixVal1, VpixVal2;
  __vector VnegShift;
  __vector VscaleFactorQ16;
  __vector VminVal;
  __vector VrightShift8;
  __vector VmaxPixVal;

  for (int i3 = 0; i3 < blkHeight; i3++)
  {
    for (int i4 = 0; i4 < ALIGN_2SIMD(blkWidth) / VCOP_2SIMD_WIDTH; i4++)
    {
      __agen inAddr;
      __agen outAddr;
      VscaleFactorQ16  = scaleFactorQ16;
      VminVal         = minVal;
      VrightShift8    = RIGHT_SHIFT_BY_8;
      VmaxPixVal      = MAX_PIXEL_VAL;
      inAddr  = i3 * inPitch * ELEM_SZ_CONTRAST_STRETCHING  +
                i4 * VECTOR_SZ_CONTRAST_STRETCHING;
      outAddr = i3 * outPitch * ELEM_SZ_CONTRAST_STRETCHING +
                i4 * VECTOR_SZ_CONTRAST_STRETCHING;

      (VpixVal1, VpixVal2) = inputImage[inAddr].deinterleave();

      VpixVal1 -= VminVal;
      VpixVal2 -= VminVal;

      VinterimVal1 =  VpixVal1 * VmaxPixVal;
      VinterimVal2 =  VpixVal2 * VmaxPixVal;

      /* remappedValQ16 =  pixDiff * scaleFactorQ16 * MAX_PIXEL_VAL*/
      VremappedValueQ16_1 = (VinterimVal1 * VscaleFactorQ16);
      VremappedValueQ16_2 = (VinterimVal2 * VscaleFactorQ16);


      outputImage[outAddr].interleave() = (VremappedValueQ16_1,
                                      VremappedValueQ16_2).round(16).saturate(0,MAX_PIXEL_VAL);

    }
  }

}


#define TRANSPOSE_STRIDE        ( 9 * sizeof(*histogram8Copy))
#define TRANSPOSE_LOOP1_STRIDE  (TRANSPOSE_STRIDE* VCOP_SIMD_WIDTH)
#define HIST_ELEMSZ             (sizeof(*histogram8Copy))


#define HIST_8COPY_PITCH (VCOP_SIMD_WIDTH * HIST_ELEMSZ)
#define HIST_8COPY_JUMP   (HIST_8COPY_PITCH * VCOP_SIMD_WIDTH)

void vcop_histogram_8c_word_sum
(
    __vptr_uint32  histogram8Copy,
    __vptr_uint32  transposeBuff,
    __vptr_uint32  histogram
)
{
  __vector bankData;

  for (int i3 = 0; i3 < 32; i3++)
  {
    for (int i4 = 0; i4 < VCOP_SIMD_WIDTH ; i4++)
    {
      __agen inAddr;
      __agen outAddr;
      inAddr = i3 * (HIST_8COPY_JUMP) + i4 * (HIST_8COPY_PITCH);
      outAddr = i4* (HIST_ELEMSZ) + i3 * TRANSPOSE_LOOP1_STRIDE;

      bankData = histogram8Copy[inAddr];

      transposeBuff[outAddr].offset_np1() = bankData;
    }
  }

  __vector sum;
  __vector inData;

  for (int i3 = 0; i3 < 32; i3++)
  {
    __agen outAddr;
    sum = 0;
    outAddr = i3 * VCOP_SIMD_WIDTH * HIST_ELEMSZ;

    for (int i4 = 0; i4 < VCOP_SIMD_WIDTH ; i4++)
    {
      __agen inAddr;

      inAddr = i4 * (TRANSPOSE_STRIDE) + i3 * (TRANSPOSE_STRIDE * VCOP_SIMD_WIDTH) ;

      inData = transposeBuff[inAddr];
      sum += inData;
    }
    histogram[outAddr] = sum;
  }

}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_contrast_stretching_kernel.k                                        */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2014.                                  */
/*============================================================================*/

