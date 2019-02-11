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
/*     @file : vcop_fft_npt_16ix16o_cn.h                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the reference functions   */
/*     for the different FFT sizes                                      */
/*                                                                          */
/*                                         */
/*                                                                          */
/*     @version 1.0 (August 2016) : Base version.                         */
/*                                                                          */

#ifndef VCOP_FFT512_16X16_C_H_
#define VCOP_FFT512_16X16_C_H_ 1

#if _DUMP
#include "stdio.h"
extern FILE *natcDumpFid;
#endif

/*
 * Declaration of LUT tables used during FFT output re-ordering
 */
extern uint16_t gInputOuputOrderIndex512pt[512];
extern uint16_t gInputOuputOrderIndex128pt[128];

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_ref
 *
 *  @desc     This function generates twiddle factor to be used for the reference FFT implementation of n
 *                point
 *
 *  @inputs   This kernel takes following Inputs
 *                numPoints :
 *                          Number of point of FFT for which twiddle factor needs to be generated. Note that
 *                          numPoints can only be power of 2's. By default twiddle factors are generated for
 *                          radix4 and mixed radix implementation.
 *
 *                forceRadix2Tf
 *                          Generate twiddle factor for radix 2 implementation.
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                sizeOfTwiddleFactorBuf
 *                          This will contain the size of twiddle factor buffer required in bytes
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    Pointer to the buffer containing twiddleFactor generated for 128 point FFT for
 *                target implementation which is stored with sine and cosine interleaved.
 *
 *  =======================================================
 */
int16_t * generateTwiddleFactor_ref(uint16_t numPoints, uint8_t forceRadix2Tf, uint32_t * sizeOfTwiddleFactorBuf);


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_npt_mixed_radix_cn
 *
 *  @desc     This function implements reference for n point FFT using mixed radix ( raidx4 and radix2)
 *
 *
 *  @inputs   This kernel takes following Inputs
 *                input : Pointer to input bufer
 *                twiddleFactorBuf : Pointer to twiddle factor buffer
 *                scaleFactorArray : Array of scaling factor which needs to be applied at each stage
 *                numPoints :
 *                forceRadix2 : Force radix 2 implementation
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                output
 *                          Pointer to the output of FFT implementation
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return
 *                  None
 *
 *  =======================================================
 */
void vcop_fft_npt_mixed_radix_cn(int16_t * input,
                         int16_t * twiddleFactorBuf,
                         int16_t * output,
                         uint16_t * scaleFactorArray,
                         int32_t  * minMax,
                         uint16_t numPoints,
                         uint8_t forceRadix2,
                         uint16_t saturationLimit,
                         uint32_t overFlowMask);


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_fft_doppler_correction_cn
 *
 *  @desc     This function implements reference C code for dopller correction by doing a point to point
 *                complex multiplication of input data with doppler correction coefficients
 *                Output of this function is stored as transpose
 *
 *  @inputs   This function takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved.
 *                          Size of this buffer should be numPoints * numOfLines * sizeof(int16_t) * 2
 *                  dopplerCorrectionBuf :
 *                          Buffer which holds the doppler correction complex coefficients to apply
 *                           Size of this buffer should be numPoints * sizeof(int16_t) * 2
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
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_fft_doppler_correction_cn
( int16_t * inputData,
  int16_t * outputData,
  int16_t * dopplerCorrectionBuf,
  unsigned short numPoints,
  unsigned short numOfLines,
  unsigned short scaleFactor,
  unsigned int   outputPitch,
  unsigned short saturationLimit
);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     digitReversalCustom
 *
 *  @desc     This function implements reference C code for re-ordering the output of the FFT using a lookup table
 *
 *  @inputs   This function takes following Inputs
 *                  input :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. The pointer is of type int32_t* because each element is represented by a pair of (real, imaginary)
 *                          Size of this buffer should be numPoints * sizeof(int16_t) * 2
 *                  numPoints :
 *                          Number of points
 *                  inputOutputMapping :
 *                          Table lookup used for the re-ordering
 *
 *
 *  @outputs   This kernel produce following outputs
 *                  output
 *                          Pointer to the output buffer containing the output of this kernel which is
 *                          stored with real and imaginary part interleaved .
 *                          The pointer is of type int32_t* because each element is represented by a pair of (real, imaginary)
 *                          Size of this buffer should be is same as input buffer size which is
 *                          numPoints  * sizeof(int16_t) * 2
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
void digitReversalCustom(int32_t * input, int32_t *output, uint16_t numPoints, uint16_t * inputOutputMapping);

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     isPowerOfFour
 *
 *  @desc     This function is a support function that returns 1 if the input is a power of 4, 0 otherwise
 *
 *  @inputs   This function takes following Inputs
 *                  x : input integer that will be inspected by the function to determine whether it is a power of 4.
 *
 *  @outputs   NONE
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    1 if x power of 4
 *             0 if x not power of 4
 *  =======================================================
 */
uint8_t isPowerOfFour(unsigned int x);

#endif


/* ======================================================================== */
/*  End of file:  vcop_fft_32x16t_c.h                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2001 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

