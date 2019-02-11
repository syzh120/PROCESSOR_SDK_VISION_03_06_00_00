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

/*      Copyright (C) 2009-2016 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ALIGN_SIMD(a)     (((a) + VCOP_SIMD_WIDTH-1U) & ~(VCOP_SIMD_WIDTH-1U))

#define MAX_OUTPUT_VALUE (32767)
#define MIN_OUTPUT_VALUE (-32768)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_beam_forming_copy_steering_matrix_kernel
 *
 *  @desc     This kernel copies the steering matrix from one buffer to other
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension numAngles x numAntennas.
 *                          Size of this buffer should be numAngles * numAntennas * sizeof(int16_t) * 2
 *                  numAngles :
 *                          Number of angles to be determined. This should come from the resolution user wants
 *                  numAntennas :
 *                          Total number of antennnas
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be ( (numAngles * numAngles) * size(int16_t) * 2)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                         inputData, outputData should be in different memory
 *
 *  @constraints Following constraints
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_forming_copy_steering_matrix_kernel
(
  __vptr_uint32   inputData,
  __vptr_uint32   outputData,
  unsigned short  numAngles,
  unsigned short  numAntennas
)
{

  for ( int i = 0; i < ALIGN_SIMD(numAngles * numAntennas)/ VCOP_SIMD_WIDTH; i++)
  {
    __vector Vin;
    __agen inOutAddr;

    inOutAddr = i * VCOP_SIMD_WIDTH * sizeof(*inputData);

    Vin = inputData[inOutAddr];
    outputData[inOutAddr] = Vin;
  }

}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_beam_forming_transpose_antenna_data_kernel
 *
 *  @desc     This kernel tranpose the antenna data
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension  numAntennas x numDetections.
 *                          Size of this buffer should be numDetections * numAntennas * sizeof(int16_t) * 2
 *                  numDetections :
 *                          Number of angles to be determined. This should come from the resolution user wants
 *                  numAntennas :
 *                          Total number of antennnas
 *                  outputPitch :
 *                           Pitch at which transposed output will be stored
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be ( (numDetections * numAntennas) * size(int16_t) * 2)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                         inputData, outputData should be in different memory
 *
 *  @constraints Following constraints
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_forming_transpose_antenna_data_kernel
(
  __vptr_uint32   inputData,
  __vptr_uint32   outputData,
  __vptr_uint16   pScatterIndex,
  unsigned short  outputPitch,
  unsigned short  numDetections,
  unsigned short  numAntennas
)
{
  __agen addr0;
  __vector VIndex;

  addr0 = 0;
  VIndex = pScatterIndex[addr0];

  for ( int detectionIdx = 0; detectionIdx < numDetections; detectionIdx++)
  {
    for ( int antennaIdx = 0; antennaIdx < ALIGN_SIMD(numAntennas)/VCOP_SIMD_WIDTH; antennaIdx++)
    {
      __vector Vin;
      __agen inAddr;
      __agen outAddr;

      inAddr = antennaIdx * VCOP_SIMD_WIDTH * sizeof(*inputData) +
               detectionIdx * numAntennas * sizeof(*inputData);

      outAddr = antennaIdx * outputPitch * VCOP_SIMD_WIDTH +
                detectionIdx * sizeof(*outputData);

      Vin = inputData[inAddr];
      outputData[outAddr].p_scatter(VIndex) = Vin;
    }
  }
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_beam_forming_kernel
 *
 *  @desc     This kernel does the beam forming which is esstentially a matrix multiplication
 *                of input data ( numDetections x numAntennas) with steering matrix ( numAntennas x numAngles)
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension numDetections x numAntennas, here
 *                          detections are in horizontal direction and anetnna data is in vertical direction.
 *                          Size of this buffer should be numDetections * numAntennas * sizeof(int16_t) * 2
 *                steeringMatrix :
 *                          Steering matrix for all the antenna. Dimension of this buffer is numAntennas x numAngles,
 *                          here antenna data is in horizontal direction and angle data is in vertical direction.
 *                          Size of this buffer should be numAntennas * numAngles * sizeof(int16_t) * 2
 *                 pitch :
 *                         Pitch in bytes to access next line inputData
 *                  numDetections :
 *                          Number of detections whose angle needs to be determined
 *                  numAntennas :
 *                          Total number of antennnas
 *                  numAngles :
 *                          Number of angles to be determined. This should come from the resolution user wants
 *                  scale : Scale factor to be applied after complex multiplication
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          Size of this buffer should be ( (numDetections * numAngles) * size(int16_t) * 2)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                         inputData, outputData, steeringMatrix should all lie in different memory
 *
 *  @constraints Following constraints
 *                  Pitch, inputData and outputData should be word aligned
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_forming_kernel
(
  __vptr_int16    inputData,
  __vptr_int16    outputData,
  __vptr_int16    steeringMatrix,
  unsigned short  pitch,
  unsigned short  numDetections,
  unsigned short  numAntennas,
  unsigned short  numAngles,
  unsigned short  scale
)
{
  __vector VInDataReal;
  __vector VInDataImg;

  __vector VSmDataReal;
  __vector VSmDataImg;

  __vector VOutDataReal;
  __vector VOutDataImg;

  __agen inAddr;
  __agen smAddr;
  __agen outAddr;

  for ( int detectionIdx = 0; detectionIdx < ALIGN_SIMD(numDetections)/ VCOP_SIMD_WIDTH; detectionIdx++)
  {
    for ( int angleIdx = 0; angleIdx < numAngles; angleIdx++)
    {
      VOutDataReal = 0;
      VOutDataImg  = 0;

      outAddr = angleIdx * sizeof(*outputData) * 2 * numDetections +
                detectionIdx * sizeof(*outputData) * 2 * VCOP_SIMD_WIDTH;

      for ( int antennaIdx = 0; antennaIdx < numAntennas; antennaIdx++)
      {
        inAddr = antennaIdx * pitch +
                 detectionIdx * sizeof(*inputData) * 2 * VCOP_SIMD_WIDTH;

        smAddr = antennaIdx * sizeof(*steeringMatrix) * 2 +
                 angleIdx * sizeof(*steeringMatrix) * 2 * numAntennas;

        (VInDataReal, VInDataImg) = inputData[inAddr].deinterleave();

        VSmDataReal = steeringMatrix[smAddr].onept();
        VSmDataImg  = (steeringMatrix + sizeof(*steeringMatrix))[smAddr].onept();

        VOutDataReal += (VInDataReal * VSmDataReal);
        VOutDataImg  += (VInDataReal * VSmDataImg);

        VOutDataReal -= (VInDataImg * VSmDataImg);
        VOutDataImg  += (VInDataImg * VSmDataReal);
      }
      outputData[outAddr].interleave() = (VOutDataReal, VOutDataImg).round(scale).saturate(MIN_OUTPUT_VALUE,MAX_OUTPUT_VALUE);
    }
  }
}


#define MIN_ENERGY_VALUE (0)
#define MAX_ENERGY_VALUE (65536)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_beam_energy_calculation_kernel
 *
 *  @desc     This kernel does computes the energy after beam forming
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension numDetections x numAntennas, here
 *                          detections are in horizontal direction and anetnna data is in vertical direction.
 *                          Size of this buffer should be numDetections * numAntennas * sizeof(int16_t) * 2
 *                  numDetections :
 *                          Number of detections whose angle needs to be determined
 *                  numAngles :
 *                          Number of angles to be determined. This should come from the resolution user wants
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputEnergy
 *                          Pointer to the output buffer containing energy of the input data.
 *                          Size of this buffer should be ( (numDetections * numAngles) * size(uint32_t))
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputData and outputData should be in two different buffers for best performance
 *
 *  @constraints Following constraints
 *                  numAngles should be even number
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_energy_calculation_kernel
(
  __vptr_int16    inputData,
  __vptr_uint32   outputEnergy,
  unsigned short  numDetections,
  unsigned short  numAngles
)
{
  __vector VInDataReal1;
  __vector VInDataImg1;

  __vector VInDataReal2;
  __vector VInDataImg2;

  __vector VOutEnergy1;
  __vector VOutEnergy2;


  __agen inAddr;
  __agen outAddr;

  for ( int angleIdx = 0; angleIdx < numAngles / 2; angleIdx++)
  {
    for ( int detectionIdx = 0; detectionIdx < ALIGN_SIMD(numDetections)/ VCOP_SIMD_WIDTH; detectionIdx++)
    {
      inAddr = detectionIdx * sizeof(*inputData) * 2 * VCOP_SIMD_WIDTH +
               angleIdx * sizeof(*inputData) * 2 * numDetections * 2;

      outAddr = detectionIdx * sizeof(*outputEnergy) * VCOP_SIMD_WIDTH +
               angleIdx * sizeof(*outputEnergy) *  numDetections * 2;

      (VInDataReal1, VInDataImg1) = inputData[inAddr].deinterleave();
      (VInDataReal2, VInDataImg2) = (inputData + numDetections * 2 * sizeof(*inputData)) [inAddr].deinterleave();

      VOutEnergy1 = VInDataReal1 * VInDataReal1;
      VOutEnergy2 = VInDataReal2 * VInDataReal2;

      VOutEnergy1 += VInDataImg1 * VInDataImg1;
      VOutEnergy2 += VInDataImg2 * VInDataImg2;

      outputEnergy[outAddr].npt() = VOutEnergy1;
      (outputEnergy + numDetections * sizeof(*outputEnergy))[outAddr].npt() = VOutEnergy2;
    }
  }
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_beam_angle_association_kernel
 *
 *  @desc     This kernel associates an angle to each detection by finding max energy among all the angles
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy :
 *                          Pointer to the input buffer containing energy of the input data.
 *                          Size of this buffer should be ( (numDetections * numAngles) * size(uint32_t))
 *                  baseAngleOffset :
 *                          Offset that need to be added for each angle
 *                  numDetections :
 *                          Number of detections whose angle needs to be determined
 *                  numAngles :
 *                          Number of angles to be determined. This should come from the resolution user wants
 *                  ptrToValidDetectionCount :
 *                          This field tells how many detections are actually valid in current iteration
 *                  ptrToParamBlock :
 *                          Pointer to the param block for this kernel. this will be used to update certain
 *                          enteries in param block
 *                  energyScalingFactor:
 *                           Scale factor to apply (rounding) before storing the 32 bit enery in 16 bit container
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  angleDetectionBuf
 *                          Pointer to the output buffer containing angle and detection id in interleaved manner
 *                          Size of this buffer should be ( (numDetections * 2 * size(uint16_t))
 *                  energyBuf
 *                          Pointer to the output buffer containing energy for each detection
 *                          Size of this buffer should be ( (numDetections * size(uint16_t))
 *
 *  @remarks  This kernel invovles param block update and hence it is very important to
 *                 note that if you make any changes to this kernel you should make sure
 *                 that the corresponding param block offsets are updated accordingly
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
#define PBLOCK_OFFSET_ANGLE_BUF (16U)
#define PBLOCK_OFFSET_ENERGY_BUF (20U)
#define PBLOCK_OFFSET_BASE_ANGLE_OFFSET (36U)


void vcop_beam_angle_association_kernel
(
  __vptr_uint32   inputEnergy,
  __vptr_uint16   angleBuf,
  __vptr_uint16   energyBuf,
  __vptr_uint16   ptrToInfoBuffer,
  __vptr_uint32   ptrToParamBlock,
  unsigned short  baseAngleOffset,
  unsigned short  numDetections,
  unsigned short  numAngles,
  unsigned short  energyScalingFactor
)
{
  __vector VInputEnergy;
  __vector VMaxEnergy;
  __vector VMaxAngleIdx;
  __vector VDetectionIdx;
  __vector VFinalDetectionIdx;
  __vector VMaxEnergyFlag;
  __vector VAngleIdx;
  __vector VBaseAngleOffset;
  __vector VBaseDetectionOffset;
  __vector VK8;
  __agen inAddr;
  __agen angleAddr;
  __agen energyAddr;


  for ( int detectionIdx = 0; detectionIdx < ALIGN_SIMD(numDetections)/ VCOP_SIMD_WIDTH; detectionIdx++)
  {
    VMaxEnergy = 0;
    VMaxAngleIdx = baseAngleOffset;
    angleAddr    = detectionIdx * VCOP_SIMD_WIDTH * sizeof(*angleBuf);
    energyAddr = detectionIdx * VCOP_SIMD_WIDTH * sizeof(*energyBuf);

    for ( int angleIdx = 0; angleIdx < numAngles; angleIdx++)
    {
      inAddr = detectionIdx * sizeof(*inputEnergy) * VCOP_SIMD_WIDTH +
      angleIdx * sizeof(*inputEnergy) * numDetections;

      VAngleIdx = angleIdx;

      VBaseAngleOffset = baseAngleOffset;

      VInputEnergy = inputEnergy[inAddr].npt();

      (VMaxEnergy, VMaxEnergyFlag) = maxf(VInputEnergy, VMaxEnergy);

      VAngleIdx     = VAngleIdx + VBaseAngleOffset;
      VMaxAngleIdx = select(VMaxEnergyFlag, VAngleIdx, VMaxAngleIdx);
    }
    angleBuf[angleAddr]       = VMaxAngleIdx;
    energyBuf[energyAddr]      = VMaxEnergy.round(energyScalingFactor).saturate();
  }

#if !VCOP_HOST_EMULATION

  __vector VAngleBufAddr;
  __vector VDetectionBufAddr;
  __vector VEnergyBufAddr;
  __vector VAngleOffset;
  __vector VEnergyOffset;
  __vector VBaseDetectionOffsetUpdate;
  __vector VBaseAngleOffsetUpdate;
  __vector VNumValidDetections;
  __vector VBaseAngleOffsetValue;
  __vector VK2;
  __vector VK1;
  __agen addr0;

  addr0 = 0;
  VK2 = 2;
  VK1 = 1U;

  VAngleBufAddr = (ptrToParamBlock + PBLOCK_OFFSET_ANGLE_BUF)[addr0].onept();
  VEnergyBufAddr         = (ptrToParamBlock + PBLOCK_OFFSET_ENERGY_BUF)[addr0].onept();
  VBaseAngleOffsetUpdate       = (ptrToParamBlock + PBLOCK_OFFSET_BASE_ANGLE_OFFSET)[addr0].onept();
  VNumValidDetections = ptrToInfoBuffer[addr0].onept();
  VBaseAngleOffsetValue = (ptrToInfoBuffer + sizeof(*ptrToInfoBuffer))[addr0].onept();
  /* This loop will update destination pointers after each call of this kernel.
  Number of valid detections will  be populated by DMA node */
  for ( int i = 0; i < 1; i++)
  {
    VAngleOffset = ( VNumValidDetections << VK1);/* Each entry is 2 bytes*/
    VEnergyOffset         = ( VNumValidDetections << VK1);/* Each entry is 2 bytes*/

    VAngleBufAddr = VAngleBufAddr + VAngleOffset;
    VEnergyBufAddr         = VEnergyBufAddr + VEnergyOffset;

    VBaseAngleOffsetUpdate        = VBaseAngleOffsetValue;

    (ptrToParamBlock + PBLOCK_OFFSET_ANGLE_BUF)[addr0].onept() = VAngleBufAddr ;
    (ptrToParamBlock + PBLOCK_OFFSET_ENERGY_BUF)[addr0].onept() = VEnergyBufAddr;
    (ptrToParamBlock + PBLOCK_OFFSET_BASE_ANGLE_OFFSET)[addr0].onept() = VBaseAngleOffsetUpdate;
  }
#endif
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_range_doppler_energy_angle_mapping_kernel
 *
 *  @desc     This kernel updates the new angle and energy to the corresponding range and
 *                 doppler coordinates in coordinate buffer. It is important to note that range
 *                 and doppler dimension are expected to be present by default.
 *                 Coordinate buffer is expected to be as follows :
 *                  typedef struct
 *                  {
 *                     uint16_t       velocity;
 *                     uint16_t       range;
 *                     uint16_t       energy;
 *                     uint16_t       angleBin;
  *                  } BEAM_FORMING_TI_Coordinates;
 *
 *  @inputs   This kernel takes following Inputs
 *                  angleDetectionMapping :
 *                          Pointer to angle detection buffer which holds the mapping of a particular angle with
 *                          correspondind detection number
 *                           Size of this buffer should be ( numDetections * sizeof(uint16_t) * 2)
 *                  angleBuf :
 *                          Pointer to angle buffer which holds the angle at each detection
 *                           Size of this buffer should be ( numDetections * sizeof(uint16_t))
 *                  energyBuf :
 *                          Pointer to energy buffer which holds the max energy of all angles at each detection
 *                           Size of this buffer should be ( numDetections * sizeof(uint16_t))
 *                  numDetections :
 *                          Number of detections whose angle needs to be determined
 *                  coordinateBufPitch :
 *                          Pitch in bytes to reach to the next detection coordinates from the first detection
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  coordinateBufEnergy :
 *                          Pointer to coordinate buffer energy field as described in above description.
 *                          Size of this buffer should be ( numDetections * sizeof(BEAM_FORMING_TI_Coordinates))
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 coordinateBuf IBUFLA
 *                 angleDetectionBuf WBUF
 *                 energyBuf WBUF
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_range_doppler_energy_angle_mapping_kernel
(
  __vptr_uint32  coordinateBufEnergy,
 __vptr_uint16   angleDetectionMapping,
 __vptr_uint16   angleBuf,
 __vptr_uint16   energyBuf,
 unsigned short  coordinateBufPitch,
 unsigned short  numDetections
)
{
  __vector VAngle;
  __vector VMapping;
  __vector VMappingOffset;
  __vector VEnergy;
  __vector VAngleEnergy;
  __vector VPitch;
  __vector VK16;

  __agen angleDetMapAddr;
  __agen energyAddr;
  __agen angleAddr;
  __agen outAddr;

  VPitch = coordinateBufPitch;
  VK16 = 16U;


  for ( int detectionIdx = 0; detectionIdx < ALIGN_SIMD(numDetections)/ VCOP_SIMD_WIDTH; detectionIdx++)
  {
    angleDetMapAddr = detectionIdx * sizeof(*angleDetectionMapping) * 2 * VCOP_SIMD_WIDTH;
    energyAddr   = detectionIdx * sizeof(*energyBuf) * VCOP_SIMD_WIDTH;
    angleAddr    = detectionIdx * sizeof(*angleBuf) * VCOP_SIMD_WIDTH;

    outAddr = 0;
    VAngle            = angleBuf[angleAddr];
    VEnergy           = energyBuf[energyAddr];
    VMapping          = angleDetectionMapping[angleDetMapAddr].ds2();
    /* Energy is 3rd entry in coordinate buf and angle is 4th entry */
    VAngle = VAngle << VK16;

    VAngle += VEnergy;

    VMappingOffset =  VMapping * VPitch;

    (coordinateBufEnergy)[outAddr]. s_scatter(VMappingOffset) = VAngle;
  }
}

