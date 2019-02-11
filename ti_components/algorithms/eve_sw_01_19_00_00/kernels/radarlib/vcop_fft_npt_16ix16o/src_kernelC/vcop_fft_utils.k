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

/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_zero_padding_kernel
 *
 *  @desc     This kernel adds zeros to each FFT line
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                 pitch :
 *                          Pitch in bytes for the input data
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  numPointsZeroPadding :
 *                           Number of points to do zero padding
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  inputData
 *                          This kernel updates the input buffer by adding zeros towards the end of the
 *                           input buffer
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                None
 *
 *  @constraints Following constraints
 *                  numPointsZeroPadding should be multiple of VCOP_SIMD_WIDTH
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_fft_zero_padding_kernel
(
  __vptr_uint32   inputData,
  unsigned short numActualPoints,
  unsigned short numOfLines,
  unsigned short numPointsZeroPadding,
  unsigned short pitch
)
{
  __vector VK0;

  VK0 = 0;

  for (int I2 = 0; I2 < numOfLines; I2++)
  {
    for ( int I1 = 0; I1 < numPointsZeroPadding / VCOP_SIMD_WIDTH; I1++)
    {
      __agen outAddr;

      outAddr = I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) +
                I2 * pitch;

      (inputData + numActualPoints * sizeof(*inputData))[outAddr] = VK0;
    }
  }
}


