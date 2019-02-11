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
/*  @file : vcop_peak_detection_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Peak Detection kernels.                   */
/*                                                                          */
/*  @version 0.1 (Apr 2017) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_PEAK_DETECTION_CN_H_
#define VCOP_PEAK_DETECTION_CN_H_

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_tx_decoding_kernel
 *
 *  @desc     This function does tx decoding by multiplying data received by all the receivers
 *                 by a matrix of dimens tx X tx. This kernel has a foreach loop and each iteration
 *                works on 8 points at a time
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This data is an array of pointers. for kth for each iteration
 *                          the pointer in this array buffer should point to k * VCOP_SIMD_WIDTH
 *                          Size of this buffer should be numTx * numRx * numHorzPtPerAntenna * sizeof(int16_t) * 2 * numRows
 *
 *                  txDecodingCoeff :
 *                          Pointer storing the coefficient of tx decoding.
 *                          Size of this buffer should be numTx * numTx
 *
 *                  numTx :
 *                          Number of transmitters in the sytem
 *                  numRx :
 *                          Number of receivers in the sytem
 *                  numRows :
 *                          Number of rows to work with
 *                  numHorzPtPerAntenna :
 *                          Number of horizontal points in the input buffer per antenna
 *                  offsetBwTx :
 *                          Offset in bytes between two transmitter data
 *                  offsetBwRx :
 *                          Offset in bytes between two receiver data
 *                  pitch :
 *                          Offset in bytes to jump from one line to next line
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  None
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Output buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This data is an array of pointers. for kth for each iteration
 *                          the pointer in this array buffer should point to k * VCOP_SIMD_WIDTH
 *                          Size of this buffer should be numTx * numRx * numHorzPtPerAntenna * sizeof(int16_t) * 2 * numRows
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_tx_decoding_cn
(
  int16_t  *inputData,
  int16_t  *txDecodingCoeff,
  int16_t  *outputData,
  uint16_t numTx,
  uint16_t numRx,
  uint16_t numRows,
  uint16_t numHorzPtPerAntenna,
  uint16_t offsetBwTx,
  uint16_t offsetBwRx,
  uint16_t pitch
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_peak_detection_energy_across_antenna_cn
 *
 *  @desc     This function computes the energy at each point and sum the energy
 *                across all antenna for the same point
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension  numAntennas x numDetections.
 *                          Size of this buffer should be numHorzPtPerAntenna *numRows * numAntennas * sizeof(int16_t) * 2
 *                  numRows :
 *                          Number of rows in the input block
 *                  numAntennas :
 *                          Total number of antennnas in the system
 *                  numHorzPtPerAntenna :
 *                          Number of horizontal points in the input buffer per antenna
 *                  pitch :
 *                          Offset in bytes to jump from one line to next line in input buffer
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output energy of this kernel which is
 *                          stored in uint32_t container.
 *                          Size of this buffer should be ( (numRows * numHorzPtPerAntenna) * size(uint32_t) )
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
void vcop_peak_detection_energy_across_antenna_cn(
  int16_t  *inputData,
  uint32_t *outputData,
  uint16_t numRows,
  uint16_t numAntennas,
  uint16_t numHorzPtPerAntenna,
  uint16_t pitch
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_peak_detection_binlog_energy_scaling_cn
 *
 *  @desc     This function computes computes the log2 of energy (32 bit) and store the output in 16 bit
 *                container. Following is the explanation of this kernel
 *                Binary Log can be computed as follows (log used here is log in base 2
 *                Any number X can be written as 2^m ( 1 + aplha) where 0<= alpha < 1
 *                log X = m + log ( 1 + aplha)
 *                If n is preccision for alpha, i.e. we  have 2^n enteries in lookup table to store log(1+aplha)
 *                log X =~ m + log (  1 + (floor(2^n * alpha)) / 2^n)
 *                Index for LUT is in Qn format  alpha = (X * 2^n/ 2^m ) - 2^n
 *                Which can also be written as X>> (m -n) - 2^n
 *                Here we can avoid substraction by 2^n if we store index as 1+alpha
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension  numAntennas x numDetections.
 *                          Size of this buffer should be numHorzPtPerAntenna *numRows * numAntennas * sizeof(int16_t) * 2
 *                  lutTable :
 *                          LUT table to store the LUT of log (  1 + (floor(2^n * alpha)) / 2^n). LUT values are stored in Q format
 *                           which is given by lutQFormat parameter. The index of LUT will be given by 1+alpha.
 *                           Size of this buffer should be 2 * ( 1<< alphaQFormat). Multiplication by 2 because we are allocating
 *                          double the size of LUT so that we can avoid substraction by 2^n
 *                  lutQFormat :
 *                          Q Format to be used to store the LUT table
 *                  alphaQFormat :
 *                          Q Format to be used finding the index corresponding to LUT table
 *                  numRows :
 *                          Number of rows in the input block
 *                  numHorzPtPerAntenna :
 *                          Number of horizontal points in the input buffer per antenna
 *
 *  @scratch   This kernel needs  following scratch buffers
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output energy of this kernel which is
 *                          stored in uint32_t container.
 *                          Size of this buffer should be ( (numRows * numHorzPtPerAntenna) * size(uint32_t) )
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                numHorzPtPerAntenna should be multiple of VCOP_SIMD_WIDTH
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_binlog_energy_scaling_cn
(
  uint32_t   *inputEnergy,
  uint16_t   *lutTable,
  uint16_t   *outputEnergy,
  uint8_t    lutQFormat,
  uint8_t    alphaQFormat,
  uint16_t   numRows,
  uint16_t   numHorzPtPerAntenna
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_peak_detection_cell_sum_cn
 *
 *  @desc     This kernel computes computes the cell sum using the energy buffer
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy :
 *                          Input buffer containing data 16 bit energy of
 *                          Size of this buffer should be numHorzPoint *numVertPoint  * sizeof(uint16_t)
 *                  noiseLen :
 *                          Noise length to be used to calculate the nosie floor
 *                  gaurdLen :
 *                          gaurd length to be used to to skip gaurd cells
 *                  numHorzPoint :
 *                          Number of horizontal points in the input block
 *                  numVertPoint :
 *                          Number of rows in the input block
 *                  inputDataPitch :
 *                          Offset in bytes to jump from one line to other line in input buffer
 *                  cellSumPitch :
 *                          Offset in bytes to jump from one line to other line in cell sum buffer
 *                  shift :
 *                         Shift to be applied to the output
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  cellSum
 *                          Pointer to the output buffer containing the cell sum of this kernel which is
 *                          stored in uint16_t container.
 *                          Size of this buffer should be ( ((numVertPoint + 2 * (noiseLen + gaurdLen)) *
 *                          numHorzPtPerAntenna) * size(uint16_t) )
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                numHorzPoint should be multiple of VCOP_SIMD_WIDTH
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_cell_sum_cn
(
  uint16_t   *inputEnergy,
  uint16_t   *cellSum,
  uint16_t   noiseLen,
  uint16_t   gaurdLen,
  uint16_t   numHorzPoint,
  uint16_t   numVertPoint,
  uint16_t   inputDataPitch,
  uint16_t   cellSumPitch,
  uint16_t   shift
);


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_peak_detection_CFARCA_thresholding_cn
 *
 *  @desc     This function does CFAR CA detector and store the output coordinates
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy :
 *                          Input energy buffer containing 16 bit energy
 *                          Size of this buffer should be numHorzPoint *numVertPoint  * sizeof(uint16_t)
 *                  cellSum :
 *                          Buffer which stores the cell sum computed byt the previous kernel
 *                         Size of this buffer should be ( ((numVertPoint + 2 * (noiseLen + gaurdLen)) *
 *                          numHorzPtPerAntenna) * size(uint16_t) )
 *                  numDetections :
 *                         Buffer to store the number of detections
 *                         Size of this buffer should be ( VCOP_SIMD_WIDTH * 2 * size(uint16_t) )
 *                  dopplerIdxOffset :
 *                          Offset to be added to the doppler index
 *                  noiseLen :
 *                          Noise length to be used to calculate the nosie floor
 *                  gaurdLen :
 *                          gaurd length to be used to to skip gaurd cells
 *                  numHorzPoint :
 *                          Number of actual horizontal points in the input block
 *                  numVertPoint :
 *                          Number of actual vertical in the input block.
 *                  inputDataPitch :
 *                          Offset in bytes to jump from one line to other line in input buffer
 *                  cellSumPitch :
 *                          Offset in bytes to jump from one line to other line in cell sum buffer
 *                  threshold :
 *                         Threshold to be used for CFAR CA DB.
 *                          Original equation of CFAR CA detector is CUT > T * NF, where T can be written as C1/ 2^C2
 *                          Same equation in log domain becomes
 *                          log(CUT)> log(T) + log(NF)
 *                          =  log(CUT) -  log(NF)> log(C1) - C2
 *                          So threshold here is log(C1) - C2.
 *                          Q format for threshold should be same as lutQFormat used during energy computation
 *                  vertCoordinateShift : A value of 16 indicates that horz corrdinate is stored in upper 16 bit and
 *                           vert coordinate is stored in lower 16 bit. A value of 0 indicates that horz coordinate is stored
 *                            in lower 16 bit and vertical coordinate is stored in upper 16 bits
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  binaryMask
 *                          Buffer to store the binary mask
 *                          Size of this buffer should be numHorzPoint * numVertPoint
 *
 *  @outputs   This kernel produce following outputs
 *                  outRangeDopplerBuf
 *                          Pointer to the output buffer storing the range and doppler coordinate  for each detection
 *                  outEnergyBuf
 *                          Pointer to the output buffer storing the energy for each detection
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputEnergy : IBUFLA and IBUFHA
 *                 cellSum : WMEM
 *                 binaryMask : WMEM
 *                 outRangeDopplerBuf : IBUFLA
 *                 outEnergyBuf: IBUFHA
 *                 dopplerIdxOffsetBuf : WMEM
 *                  numDetections : IBUFHA
 *  @constraints Following constraints
 *                numHorzPoint should be multiple of VCOP_SIMD_WIDTH ( an power of 2.
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_CFARCA_thresholding_cn
(
  uint16_t   *inputEnergy,
  uint16_t   *cellSum,
  uint16_t   *outRangeDopplerBuf,
  uint16_t   *outEnergyBuf,
  uint16_t   *numDetections,
  uint16_t   *horzIdxOffset,
  uint16_t   dopplerIdxOffset,
  uint16_t   noiseLen,
  uint16_t   gaurdLen,
  uint16_t   numHorzPoint,
  uint16_t   numVertPoint,
  uint16_t   inputDataPitch,
  uint16_t   cellSumPitch,
  int16_t    threshold,
  uint16_t   vertCoordinateShift
);


#endif /* VCOP_PEAK_DETECTION_CN_H_ */

