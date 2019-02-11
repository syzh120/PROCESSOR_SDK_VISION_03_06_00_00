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
 *  @kernel     vcop_fft_doppler_correction_kernel
 *
 *  @desc     This kernel does dopller correction by doing a point to point
 *                complex multiplication of input data with doppler correction coefficients.
 *                Output of this kernel is stored as transpose
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  dopplerCorrectionBuf :
 *                          Buffer which holds the doppler correction complex coefficients to apply
 *                           Size of this buffer should be numPoints * sizeof(int16_t) * 2
 *                  pScatterIndex :
 *                           Pointer to the index to be used for pScatter. This should be such that
 *                           all 8 lanes of a vector goes to different memory bank.
 *                 transposePitch :
 *                          Pitch in bytes for the pitch to be used for transpose
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  scaleFactor :
 *                          Scale factor to be applied after complex multiplication
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputData and outputData should be placed in two different buffer for optimal performance
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_fft_doppler_correction_kernel
(
  __vptr_int16   inputData,
  __vptr_int16   outputData,
  __vptr_int16   dopplerCorrectionBuf,
  __vptr_uint16   pScatterIndex,
  unsigned short transposePitch,
  unsigned short numPoints,
  unsigned short numOfLines,
  unsigned short scaleFactor,
  unsigned short saturationLimit

)
{
  __vector VInputDataR;
  __vector VInputDataI;
  __vector VDopplerR;
  __vector VDopplerI;
  __vector VOutReal;
  __vector VOutImg;
  __vector VScatterOffset;
  __agen addr0 = 0;

  VScatterOffset = pScatterIndex[addr0].npt();

  for (int I2 = 0; I2 < numOfLines; I2++)
  {
    for ( int I1 = 0; I1 < numPoints / VCOP_SIMD_WIDTH; I1++)
    {
      __agen inAddr;
      __agen outAddr;
      __agen dopplerAddr;

      inAddr  = (I2 *  numPoints * sizeof(*inputData) * 2) +
                (I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2);

      outAddr = I1 * VCOP_SIMD_WIDTH * transposePitch +
                I2 * sizeof(*inputData) * 2;

      dopplerAddr = (I1 * VCOP_SIMD_WIDTH * sizeof(*dopplerCorrectionBuf) * 2);

      (VInputDataR, VInputDataI) = inputData[inAddr].deinterleave();
      (VDopplerR, VDopplerI)     = dopplerCorrectionBuf[dopplerAddr].deinterleave();

      VOutReal  = VInputDataR * VDopplerR;
      VOutReal -= (VInputDataI * VDopplerI);

      VOutImg  = VInputDataR * VDopplerI;
      VOutImg += (VInputDataI * VDopplerR);

      outputData[outAddr].p_scatter(VScatterOffset) = VOutReal.round(scaleFactor).saturate(-saturationLimit, (saturationLimit - 1));
      (outputData + sizeof(*outputData))[outAddr].p_scatter(VScatterOffset) = VOutImg.round(scaleFactor).saturate(-saturationLimit, (saturationLimit - 1));

    }
  }

}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_fft_doppler_pitch_removal
 *
 *  @desc     This kernel does a copy of the bufffer in such a way so as to remove the gaps between
 *                2 lines
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                 inputPitch :
 *                          Pitch in bytes for the input data
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputData and outputData should be placed in two different buffer for optimal performance
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_fft_doppler_pitch_removal
(
  __vptr_int16   inputData,
  __vptr_int16   outputData,
  unsigned short inputPitch,
  unsigned short outputPitch,
  unsigned short numPoints,
  unsigned short numOfLines

)
{
  __vector VInputDataR;
  __vector VInputDataI;


  for (int I2 = 0; I2 < numPoints; I2++)
  {
    for ( int I1 = 0; I1 < numOfLines / VCOP_SIMD_WIDTH; I1++)
    {
      __agen inAddr;
      __agen outAddr;

      inAddr  = (I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2) +
                (I2 *  inputPitch);

      outAddr = I1 * VCOP_SIMD_WIDTH * sizeof(*outputData) * 2 +
                I2 * outputPitch;

      (VInputDataR, VInputDataI) = inputData[inAddr].deinterleave();

      outputData[outAddr].interleave() = (VInputDataR, VInputDataI);
    }
  }

}


