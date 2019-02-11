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
/*  @file : vcop_dcoffset_windowing_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for binary masking kernel.                   */
/*                                                                          */
/*  @version 0.1 (July 2016) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_DCOFFSET_WINDOWING_CN_H_
#define VCOP_DCOFFSET_WINDOWING_CN_H_

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_interference_zero_out_cn
 *
 *  @desc     This function is to zeroout the interference by setting value which are higher
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
 *                 outputPitch :
 *                          Number of  bytes to jump from one line to next line in the output buffer
 *
 *  @scratch   This kernel needs  following scratch buffers
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
void vcop_interference_zero_out_cn
(
  int16_t        *inputData,
  int16_t        *outputData,
  int16_t        interferenceThreshold,
  unsigned short numPoints,
  unsigned short numOfLines,
  unsigned short outputPitch
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_dcoffset_cn
 *
 *  @desc     This function finds the average of each line and also thresholds the input and set it to zero
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
 *
 *  @scratch   This kernel needs  following scratch buffers
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
void vcop_dcoffset_cn
(
  int16_t        *inputData,
  int16_t        *dcOffsetBuf,
  unsigned short numPoints,
  unsigned short numOfLines
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_windowing_cn
 *
 *  @desc     This function applyies a scaling factor to each entery of input data for both real and imagignary parts
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  winCoefficients :
 *                          Buffer which holds the window coefficients to apply
 *                           Size of this buffer should be numPoints * sizeof(int16_t)
 *                  dcOffset :
 *                          Buffer to the DC offsets for each line
 *                  numPoints :
 *                          Number of points
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                 scaleFactor :
 *                           Scaling to be applied at output
 *                 saturationLimit :
 *                           Limit the output to certain range. Output will be limited with -saturationLimit to
 *                           (saturationLimit - 1)
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
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_windowing_cn
(
  int16_t        *inputData,
  int16_t        *winCoefficients,
  int16_t        *dcOffset,
  int16_t        *outputData,
  unsigned short numPoints,
  unsigned short numOfLines,
  uint16_t       scaleFactor,
  uint16_t       saturationLimit,
  uint16_t       outputPitch
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_windowing_with_transpose_cn
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
 *                          Buffer which holds the window coefficients to apply
 *                           Size of this buffer should be numPoints * sizeof(int16_t)
 *                  numOfLines :
 *                          Number of lines to work with in single kernel
 *                  numPoints :
 *                          Number of points
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
 *                          Size of this buffer should be
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
void vcop_windowing_with_transpose_cn
(
  int16_t        *inputData,
  int16_t        *winCoefficients,
  int16_t        *outputData,
  unsigned short numPoints,
  unsigned short numOfLines,
  uint16_t       scaleFactor,
  uint16_t       saturationLimit,
  uint16_t       winOutputPitch
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func    vcop_sign_extension_cn
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
void vcop_sign_extension_cn
(
  uint16_t  *inputData,
  int16_t   *outputData,
  unsigned short numPoints,
  unsigned short numOfLines,
  unsigned short outputPitch,
  unsigned short inBits
);

#endif /* VCOP_DCOFFSET_WINDOWING_CN_H_ */

