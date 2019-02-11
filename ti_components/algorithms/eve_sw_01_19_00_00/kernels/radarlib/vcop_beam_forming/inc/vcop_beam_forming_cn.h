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
/*  @file : vcop_beam_forming_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Beam forming kernels.                   */
/*                                                                          */
/*  @version 0.1 (Dec 2016) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_BEAM_FORMING_CN_H_
#define VCOP_BEAM_FORMING_CN_H_

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_beam_forming_cn
 *
 *  @desc     This function does the beam forming which is esstentially a matrix multiplication
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
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_forming_cn
(
  int16_t   *inputData,
  int16_t   *outputData,
  int16_t   *steeringMatrix,
  uint16_t  pitch,
  uint16_t  numDetections,
  uint16_t  numAntennas,
  uint16_t  numAngles,
  uint16_t  scale
);
/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_beam_energy_calculation_cn
 *
 *  @desc     This function does computes the energy after beam forming
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
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_energy_calculation_cn
(
  int16_t   *inputData,
  uint32_t  *outputEnergy,
  uint16_t  numDetections,
  uint16_t  numAngles
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_beam_angle_association_cn
 *
 *  @desc     This function associates an angle to each detection by finding max energy among all the angles
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
 *                  energyScalingFactor:
 *                           Scale factor to apply (rounding) before storing the 32 bit enery in 16 bit container
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  angleBuf
 *                          Pointer to the output buffer containing angle and detection id in interleaved manner
 *                          Size of this buffer should be ( (numDetections * 2 * size(uint16_t))
 *                  energyBuf
 *                          Pointer to the output buffer containing energy for each detection
 *                          Size of this buffer should be ( (numDetections * size(uint16_t))
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_beam_angle_association_cn
(
  uint32_t   *inputEnergy,
  uint16_t  *angleBuf,
  uint16_t  *energyBuf,
  uint16_t  baseAngleOffset,
  uint16_t  numDetections,
  uint16_t  numAngles,
  uint16_t  energyScalingFactor
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_range_doppler_energy_angle_mapping_cn
 *
 *  @desc     This func updates the new angle and energy to the corresponding range and
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
 *  @inputs   This func takes following Inputs
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
void vcop_range_doppler_energy_angle_mapping_cn
(
  uint32_t  *coordinateBufEnergy,
  uint16_t  *angleDetectionMapping,
  uint16_t  *angleBuf,
  uint16_t  *energyBuf,
  unsigned short  coordinateBufPitch,
  unsigned short  numDetections
);

#endif /* VCOP_BEAM_FORMING_CN_H_ */

