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


#define   VCOP_2SIMD_WIDTH   (2 * VCOP_SIMD_WIDTH)
#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define MAX_VAL (32767)
#define TRANSPOSE_STRIDE ( (VCOP_SIMD_WIDTH + 1 ) * 4 )


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_interference_zero_out_kernel
 *
 *  @desc     This kernel is to zero out the interference by setting value which are higher
 *                than a particular value to zero
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  interferenceThreshold :
 *                          Interference threshold to be used
 *                  numPoints :
 *                          Number of points whose dc offset calculation is required.
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  inputPitch :
 *                          Number of  bytes to jump from one line to next line in the input buffer
 *                  outputPitch :
 *                          Number of  bytes to jump from one line to next line in the output buffer
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
void vcop_interference_zero_out_kernel
(
  __vptr_int16   inputData,
  __vptr_int16   outputData,
  unsigned short interferenceThreshold,
  unsigned short numPoints,
  unsigned short numOfLines,
  unsigned short inputPitch,
  unsigned short outputPitch

)
{
  __vector VInputDataR;
  __vector VInputDataI;

  for (int I2 = 0; I2 < numOfLines; I2++)
  {
    for ( int I1 = 0; I1 < numPoints / VCOP_SIMD_WIDTH; I1++)
    {
      __agen inAddr;
      __agen outAddr;

      inAddr  = (I2 *  inputPitch) +
                (I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2);

      outAddr  = (I2 *  outputPitch) +
                (I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2);

      (VInputDataR, VInputDataI) = inputData[inAddr].deinterleave();

      outputData[outAddr].interleave()= (VInputDataR, VInputDataI).saturate(-(interferenceThreshold - 1),0, interferenceThreshold, 0);
    }
  }

}


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_dcoffset_kernel
 *
 *  @desc     This kernel finds the average of each line and also thresholds the input and set it to zero
 *                based on user given threshold. Final output is real and imaginary avaerage for each line
 *               in interleave format.
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  numPoints :
 *                          Number of points whose dc offset calculation is required.
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  inputPitch :
 *                          Number of  bytes to jump from one line to next line in the input buffer
 *                  shift :
 *                          Amount of shift that needs to be applied in final output
 *                  pScatterIndex :
 *                           Pointer to the 8 indexes to be used for pScatter. Each entry of this should be such that
 *                           all 8 lanes of a vector goes to different memory bank. Size of this buffer
 *                           should be VCOP_SIMD_WIDTH * sizeof(int16_t)
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  scratchBuf
 *                          Pointer to the scratch buffer .
 *                          Size of this buffer should be transposeStride * sizeof(int32Pt) * VCOP_SIMD_WIDTH
 *
 *  @outputs   This kernel produce following outputs
 *                  dcOffsetBuf
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved . Total number of elements would
 *                          be equal to number of lines
 *                          Size of this buffer should be ( (numOfLines) * size(int16_t) * 2)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_dcoffset_kernel
(
   __vptr_int16   inputData,
   __vptr_int32   scratchBuf,
   __vptr_uint16  pScatterIndex,
   __vptr_int16   dcOffsetBuf,
   unsigned short inputPitch,
   unsigned short transposeStride,
   unsigned short numPoints,
   unsigned short numOfLines,
   unsigned short shift
)
{
  __vector VInputDataR;
  __vector VInputDataI;
  __vector VsumReal;
  __vector VsumImg;
  __vector Vindex;
  __agen addr0;
  __agen outAddr;

  addr0 = 0;

  Vindex = pScatterIndex[addr0].npt();

  /* Loop 1 will sum a set 8 elements with the next set of 8 elements and so on.
  Output is stored as transpose to enable vertical some in SIMD friendly way*/

  for (int I2 = 0; I2 < numOfLines; I2++)
  {
    VsumReal = 0;
    VsumImg = 0;
    for ( int I1 = 0; I1 < numPoints / VCOP_SIMD_WIDTH; I1++)
    {
      __agen inAddr;

      inAddr  = (I2 *  inputPitch) +
                (I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2);
      outAddr = (I2  * sizeof(*scratchBuf) );

      (VInputDataR, VInputDataI) = inputData[inAddr].deinterleave();

      VsumReal  += VInputDataR;
      VsumImg   += VInputDataI;
    }
    scratchBuf[outAddr].p_scatter(Vindex) = VsumReal;
    (scratchBuf + (numOfLines) * sizeof(*scratchBuf))[outAddr].p_scatter(Vindex) = VsumImg;
  }


  __vector Vtemp1, Vtemp2;
  /* Loop 2: This is to sum the transposed elements and it should run for numOfLines times */

  for (int i = 0; i < ALIGN_SIMD(numOfLines) / VCOP_SIMD_WIDTH; i++)
  {
    VsumReal = 0;
    VsumImg = 0;

    __agen addrOut = i * VCOP_2SIMD_WIDTH * sizeof(*dcOffsetBuf);

    for ( int j = 0; j < VCOP_SIMD_WIDTH; j++)
    {
      __agen addrIn  = j * transposeStride + i * VCOP_SIMD_WIDTH * sizeof(*scratchBuf);
      Vtemp1 = scratchBuf[addrIn].npt();
      Vtemp2 = (scratchBuf + (numOfLines  ) * sizeof(*scratchBuf) )[addrIn].npt();

      VsumReal += Vtemp1;
      VsumImg  += Vtemp2;

    }
    dcOffsetBuf[addrOut].interleave() = (VsumReal,VsumImg).truncate(shift);
  }

}


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel    vcop_windowing_kernel
 *
 *  @desc     This function applyies a scaling factor to each entery of input data for both real and imagignary parts
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  winCoefficients :
 *                          Buffer which holds the scalar window coefficients to apply
 *                           Size of this buffer should be numPoints * sizeof(int16_t)
 *                  dcOffsetBuf :
 *                          Buffer to the DC offsets for each line
 *                  numPoints :
 *                          Number of points whose windowing is required.
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                 scaleFactor :
 *                           Scaling to be applied at output
 *                 saturationLimit :
 *                           Limit the output to certain range. Output will be limited with -saturationLimit to
 *                           (saturationLimit - 1)
 *                 inputPitch :
 *                          Number of  bytes to jump from one line to next line in the input buffer
 *                 outputPitch :
 *                          Number of  bytes to jump from one line to next line in the output buffer
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel
 *                          Size of this buffer should be
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          inputdata,  winCoefficients , outputData one of these three buffer should be
 *                          iin different memory
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_windowing_kernel
(
  __vptr_int16         inputData,
  __vptr_int16         winCoefficients,
  __vptr_int16         dcOffsetBuf,
  __vptr_int16         outputData,
  unsigned short       numPoints,
  unsigned short       numOfLines,
  unsigned short       scaleFactor,
  unsigned short       saturationLimit,
  unsigned short       inputPitch,
  unsigned short       outputPitch
)
{
  __vector VInputDataR;
  __vector VInputDataI;
  __vector VDcOffsetReal;
  __vector VDcOffsetImg;
  __vector VWinCoeff;

  for (int j = 0; j < numOfLines; j++)
  {
    __agen addrDcOffset;
    addrDcOffset = j * sizeof(*dcOffsetBuf) * 2;

    VDcOffsetReal = dcOffsetBuf[addrDcOffset].onept();
    VDcOffsetImg  = (dcOffsetBuf + sizeof(*dcOffsetBuf))[addrDcOffset].onept();

    for ( int i = 0; i < numPoints / VCOP_SIMD_WIDTH; i++)
    {
      __agen inAddr = ( i * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2 ) +
                    ( j * inputPitch);

      __agen outAddr = ( i * VCOP_SIMD_WIDTH * sizeof(*outputData) * 2 ) +
                    ( j * outputPitch );

      __agen coeffAddr = ( i * VCOP_SIMD_WIDTH * sizeof(*winCoefficients));

      (VInputDataR, VInputDataI)    = inputData[inAddr].deinterleave();
      VWinCoeff                     = winCoefficients[coeffAddr].npt();

      VInputDataR = VInputDataR - VDcOffsetReal;
      VInputDataI = VInputDataI - VDcOffsetImg;

      VInputDataR  = VInputDataR * VWinCoeff;
      VInputDataI  = VInputDataI * VWinCoeff;

      outputData[outAddr].interleave()= (VInputDataR, VInputDataI).round(scaleFactor).saturate(-saturationLimit, (saturationLimit - 1));
    }
  }

}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel    vcop_windowing_with_transpose_kernel
 *
 *  @desc     This function applyies a scaling factor to each entery of input data for both real and imagignary parts and
 *                stores the output in tranpose order
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  winCoefficients :
 *                          Buffer which holds the scalar window coefficients to apply
 *                           Size of this buffer should be numPoints * sizeof(int16_t)
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  pScatterIndex :
 *                           Pointer to the 8 indexes to be used for pScatter. Each entry of this should be such that
 *                           all 8 lanes of a vector goes to different memory bank. Size of this buffer
 *                           should be VCOP_SIMD_WIDTH * sizeof(int16_t)
 *                 inputPitch :
 *                          Number of  bytes to jump from one line to next line in the input buffer
 *                 transposePitch :
 *                          Pitch in bytes for the pitch to be used for transpose
 *                 scaleFactor :
 *                           Scaling to be applied at output
 *                 saturationLimit :
 *                           Limit the output to certain range. Output will be limited with -saturationLimit to
 *                           (saturationLimit - 1)
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel
 *                          Size of this buffer should be (transposePitch * numPoints)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_windowing_with_transpose_kernel
(
  __vptr_int16         inputData,
  __vptr_int16         winCoefficients,
  __vptr_int16         outputData,
  __vptr_uint16        pScatterIndex,
  unsigned short       inputPitch,
  unsigned short       transposePitch,
  unsigned short       numPoints,
  unsigned short       numOfLines,
  unsigned short       scaleFactor,
  unsigned short       saturationLimit
)
{
  __vector VInputDataR;
  __vector VInputDataI;
  __vector VDcOffsetReal;
  __vector VDcOffsetImg;
  __vector VWinCoeff;
  __vector VIndex;
  __agen addr0;

  addr0 = 0;
  VIndex = pScatterIndex[addr0].npt();


  for (int j = 0; j < numOfLines; j++)
  {
    __agen coeffAddr = ( j * sizeof(*winCoefficients));
    VWinCoeff                     = winCoefficients[coeffAddr].onept();

    for ( int i = 0; i < numPoints / VCOP_SIMD_WIDTH; i++)
    {
      __agen inAddr = ( i * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2 ) +
                    ( j * inputPitch );

      __agen outAddr = ( i * VCOP_SIMD_WIDTH * transposePitch) +
                    ( j * sizeof(*outputData) * 2 );



      (VInputDataR, VInputDataI)    = inputData[inAddr].deinterleave();

      VInputDataR  = VInputDataR * VWinCoeff;
      VInputDataI  = VInputDataI * VWinCoeff;

      outputData[outAddr].p_scatter(VIndex)= VInputDataR.round(scaleFactor).saturate(-saturationLimit, (saturationLimit - 1));
      (outputData + sizeof(*outputData))[outAddr].p_scatter(VIndex)= VInputDataI.round(scaleFactor).saturate(-saturationLimit, (saturationLimit - 1));
    }
  }

}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel    vcop_sign_extension_kernel
 *
 *  @desc     This function extends the sign of input data from n bits to 16 bits. where n < 16
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                 inputPitch :
 *                          Number of  bytes to jump from one line to next line in the input buffer
 *                 outputPitch :
 *                           Number of bytes to jump from one line to next line in output buffer
 *                 inBits :
 *                           Number of bits valid bits in input data which is stored in 16b it container
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sign_extension_kernel
(
  __vptr_uint16  inputData,
  __vptr_int16   outputData,
  unsigned short numPoints,
  unsigned short numOfLines,
  unsigned short inputPitch,
  unsigned short outputPitch,
  unsigned short inBits
)
{
  __vector VInReal, VInImg;
  __vector VShift;

  VShift = (40 - inBits);

  for (int I2 = 0; I2 < numOfLines; I2++)
  {
    for ( int I1 = 0; I1 < numPoints / VCOP_SIMD_WIDTH; I1++)
    {
      __agen inAddr;
      __agen outAddr;

      inAddr = I1 * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2 +
                I2 * inputPitch;

      outAddr = I1 * VCOP_SIMD_WIDTH * sizeof(*outputData) * 2 +
                I2 * outputPitch;

      (VInReal, VInImg) = inputData[inAddr].deinterleave();

       VInReal = VInReal << VShift;
       VInImg  = VInImg  << VShift;

       outputData[outAddr].interleave() = (VInReal,VInImg).truncate((40 - inBits));

    }
  }
}

