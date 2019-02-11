/*
*
* Copyright (c) 1997-2017 Texas Instruments Incorporated
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


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "vcop.h"
#include "../inc/vcop_fft_npt_16ix16o_cn.h"
#include "../inc/vcop_fft_npt_16ix16o_gen_twiddleFactor.h"

#define PI 3.14159265358979323846

typedef double double64_t;

static int16_t d2s(double64_t d);

static int16_t d2s(double64_t d)
{
  int16_t outVal;

  outVal = (int16_t)d;

  if (d >=  32767.0)
  {
    outVal = 32767;
  }
  if (d <= -32768.0)
  {
    outVal = (int16_t)-32768;
  }
  return outVal;
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_1024
 *
 *  @desc     This function returns the size twiddle factor buffer in bytes to be used
  *                for target implementaion of 1024 point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    size of twiddle factor bufer
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_1024(void)
{
  uint32_t numPoints = 1024U;
  uint32_t sizeOfTwiddleFactor;
  sizeOfTwiddleFactor = ((numPoints/4U)+(numPoints/16U)+(numPoints/64U) + (8U * (numPoints/256U))) * 3U * 2U * 2U ;
  return sizeOfTwiddleFactor;
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_1024
 *
 *  @desc     This function generates twiddle factor to be used for target implementaion of 1024
 *                point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  twiddleFactorBuf
 *                        Generated twiddle factor
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
void generateTwiddleFactor_1024(int16_t  twiddleFactorBuf[])
{
  double64_t scale;
  uint32_t i,j;
  double64_t temp;
  double64_t cosTheta;
  double64_t sinTheta;
  uint32_t numPoints = 1024U;
  uint32_t sizeOfTwiddleFactor;
  uint32_t tfBaseOffset;
  scale = 32767.0;

  sizeOfTwiddleFactor = ((numPoints/4U)+(numPoints/16U)+(numPoints/64U) + (8U * (numPoints/256U))) * 3U * 2U * 2U ;
  /* Stage 1 */
  memset(twiddleFactorBuf,0,sizeOfTwiddleFactor);

  /* Each butterly needs 3 Twiddle factor (TF) and as we are going to work with 8BF per iteration hence store 8 twiddle factor for different  2nd leg of
  BF consecutively 8 TF for 3rd leg and then 8TF for 4th leg
  TF = cos(2*pi *k / N) + j sin(2*pi*k/N)*/
  tfBaseOffset = 0;
  for ( i = 0 ; i < (numPoints/4U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (double64_t)((2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints);
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* Stage 2 */
  /* Stage 2 twiddle factor are also arranged in same manner as stage 1 */
  tfBaseOffset = ((numPoints/4U) * 3U * 2U);
  for ( i = 0 ; i < (numPoints/16U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (4.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (4.0 * 2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (4.0 * 3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U * j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U * j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* Stage 3 */
  tfBaseOffset = (((numPoints/4U) + (numPoints/16U)) * 3U * 2U);
  for ( i = 0 ; i < (numPoints/64U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (16.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (16.0 * 2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (16.0 * 3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }


    /* Stage 4 */
    tfBaseOffset = (((numPoints/4U) +
                                          (numPoints/16U) +
                                          (numPoints/64U)) * 3U * 2U);

    /* From stage 4 onwards instead of working with 8BF within a single group we start working on 8BF from 8 differnt groups. Thats
    the reason we have to duplicate the twiddle factor for each leg 8 times as across groups twiddle factor are always the same */
    for ( j = 0; j < (numPoints/256U); j++)
    {
        for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
        {
          temp = (64.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
          cosTheta = cos(temp) * scale;
          sinTheta = sin(temp) * scale;
          twiddleFactorBuf[tfBaseOffset + (2U*(j* 3U * VCOP_SIMD_WIDTH)) + (2U*i)]     = d2s(sinTheta);
          twiddleFactorBuf[tfBaseOffset + (2U*(j* 3U * VCOP_SIMD_WIDTH)) + (2U*i) + 1U] = d2s(cosTheta);

          temp = (64.0 * 2.0 *  2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
          cosTheta = cos(temp) * scale;
          sinTheta = sin(temp) * scale;
          twiddleFactorBuf[tfBaseOffset + (2U*(j* 3U * VCOP_SIMD_WIDTH)) + (VCOP_SIMD_WIDTH * 2U) + (2U* i)]     = d2s(sinTheta);
          twiddleFactorBuf[tfBaseOffset + (2U*(j* 3U * VCOP_SIMD_WIDTH)) + 1U + (VCOP_SIMD_WIDTH * 2U) + (2U* i)] = d2s(cosTheta);

          temp = (64.0 * 3.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
          cosTheta = cos(temp) * scale;
          sinTheta = sin(temp) * scale;
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) +  (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)]    = d2s(sinTheta);
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)] = d2s(cosTheta);
        }
    }

}


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_512
 *
 *  @desc     This function returns the size twiddle factor buffer in bytes to be used
  *                for target implementaion of 512 point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    size of twiddle factor bufer
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_512(void)
{
  uint32_t numPoints = 512U;
  uint32_t sizeOfTwiddleFactor;
  sizeOfTwiddleFactor = ((numPoints/4U)+(numPoints/16U)+((numPoints/64U)*4U) + (8U * (numPoints/256U))) * 3U * 2U * 2U ;
  return sizeOfTwiddleFactor;
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_512
 *
 *  @desc     This function generates twiddle factor to be used for target implementaion of 512
 *                point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  twiddleFactorBuf
 *                        Generated twiddle factor
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
void generateTwiddleFactor_512(int16_t  twiddleFactorBuf[])
{
  double64_t scale;
  uint32_t i,j;
  double64_t temp;
  double64_t cosTheta;
  double64_t sinTheta;
  uint32_t numPoints = 512U;
  uint32_t sizeOfTwiddleFactor;
  uint32_t tfBaseOffset;

  scale = 32767.0;

  sizeOfTwiddleFactor = ((numPoints/4U)+(numPoints/16U)+((numPoints/64U)*4U) + (8U * (numPoints/256U))) * 3U * 2U * 2U ;
  /* Stage 1 */
  memset(twiddleFactorBuf,0,sizeOfTwiddleFactor);

  /* Each butterly needs 3 Twiddle factor (TF) and as we are going to work with 8BF per iteration hence store 8 twiddle factor for different  2nd leg of
  BF consecutively 8 TF for 3rd leg and then 8TF for 4th leg
  TF = cos(2*pi *k / N) + j sin(2*pi*k/N)*/
  tfBaseOffset = 0;
  for ( i = 0 ; i < (numPoints/4U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* Stage 2 */
  /* Stage 2 twiddle factor are also arranged in same manner as stage 1 */
  tfBaseOffset = ((numPoints/4U) * 3U * 2U);

  for ( i = 0 ; i < (numPoints/16U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (4.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (4.0 * 2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (4.0 * 3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* Stage 3 */
  /* Stage 3 twiddle factor are also arranged in same manner as stage 1 */
  tfBaseOffset = (((numPoints/4U) + (numPoints/16U)) * 3U * 2U);

    for ( j = 0; j < 8U ;j++)
    {

    temp = (16.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (16.0 * 2.0 *  2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (16.0 * 3.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);

    }

    /* we are duplicating the twiddle factor 4 times to avoid register allocation failure error */
    for ( i = 1U ; i < 4U; i++)
    {
        memcpy(&twiddleFactorBuf[tfBaseOffset + (i*(VCOP_SIMD_WIDTH * 2U)*3U)],
               &twiddleFactorBuf[tfBaseOffset],
               (VCOP_SIMD_WIDTH * 2U*2U)*3U);
    }

    /* Stage 4 */
    tfBaseOffset = (((numPoints/4U) +
                      (numPoints/16U) +
                      ((numPoints/64U)* 4U)) * 3U * 2U);

    /* From stage 4 onwards instead of working with 8BF within a single group we start working on 8BF from 8 differnt groups. Thats
    the reason we have to duplicate the twiddle factor for each leg 8 times as across groups twiddle factor are always the same */
    for ( j = 0; j < (numPoints/256U); j++)
    {
        for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
        {
          temp = (64.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
          cosTheta = cos(temp) * scale;
          sinTheta = sin(temp) * scale;
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i)]     = d2s(sinTheta);
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i) + 1U] = d2s(cosTheta);

          temp = (64.0 * 2.0 *  2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
          cosTheta = cos(temp) * scale;
          sinTheta = sin(temp) * scale;
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (VCOP_SIMD_WIDTH * 2U) + (2U* i)]     = d2s(sinTheta);
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (VCOP_SIMD_WIDTH * 2U) + (2U* i)] = d2s(cosTheta);

          temp = (64.0 * 3.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
          cosTheta = cos(temp) * scale;
          sinTheta = sin(temp) * scale;
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) +  (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)]    = d2s(sinTheta);
          twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)] = d2s(cosTheta);
        }
    }

}


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_128
 *
 *  @desc     This function returns the size twiddle factor buffer in bytes to be used
  *                for target implementaion of 128 point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    size of twiddle factor bufer
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_128(void)
{
  uint32_t numPoints = 128U;
  uint32_t sizeOfTwiddleFactor;
  sizeOfTwiddleFactor = ((numPoints/4U)+ (4U * (numPoints/16U))+((numPoints/64U)* 8U)) * 3U * 2U * 2U ;
  return sizeOfTwiddleFactor;
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_128
 *
 *  @desc     This function generates twiddle factor to be used for target implementaion of 128
 *                point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  twiddleFactorBuf
 *                        Generated twiddle factor
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
void generateTwiddleFactor_128(int16_t twiddleFactorBuf[])
{
  double64_t scale;
  uint32_t i,j;
  double64_t temp;
  double64_t cosTheta;
  double64_t sinTheta;
  scale = 32767.0;
  uint32_t numPoints = 128U;
  uint32_t sizeOfTwiddleFactor;
  uint32_t tfBaseOffset;

  sizeOfTwiddleFactor = ((numPoints/4U)+ (4U * (numPoints/16U))+((numPoints/64U)* 8U)) * 3U * 2U * 2U ;

  /* Stage 1 */
  memset(twiddleFactorBuf,0,sizeOfTwiddleFactor);

  /* Each butterly needs 3 Twiddle factor (TF) and as we are going to work with 8BF per iteration hence store 8 twiddle factor for different  2nd leg of
    BF consecutively 8 TF for 3rd leg and then 8TF for 4th leg
    TF = cos(2*pi *k / N) + j sin(2*pi*k/N)*/
  tfBaseOffset = 0;
  for ( i = 0 ; i < (numPoints/4U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));

  }

  /* Stage 2 */
  /* Stage 2 TF are stored same as stage 1 */
  tfBaseOffset = ((numPoints/4U) * 3U * 2U);

  i = 0;
  for ( j = 0; j < 8U; j++)
  {
    temp = (4.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
    cosTheta = cos(temp) * scale;
    sinTheta = sin(temp) * scale;
    twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
    twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

    temp = (4.0 * 2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
    cosTheta = cos(temp) * scale;
    sinTheta = sin(temp) * scale;
    twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
    twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

    temp = (4.0 * 3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
    cosTheta = cos(temp) * scale;
    sinTheta = sin(temp) * scale;
    twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
    twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
  }
  tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));

  /* This is required because register allocation is failing if we move twiddle factor read outside the inner most loop */
  for ( i = 0 ; i < 3U; i++)
  {
      memcpy(&twiddleFactorBuf[tfBaseOffset + (i*(VCOP_SIMD_WIDTH * 2U)*3U)],
             &twiddleFactorBuf[tfBaseOffset + ((i - 1U)*(VCOP_SIMD_WIDTH * 2U)*3U)],
             (VCOP_SIMD_WIDTH * 2U*2U)*3U);
  }

  /* Stage 3 */
  tfBaseOffset = (((numPoints/4U) + (4U * (numPoints/16U))) * 3U * 2U);

  /* From stage 3 onwards instead of working with 8BF within a single group we start working on 8BF from 8 differnt groups. Thats
     the reason we have to duplicate the twiddle factor for each leg 8 times as across groups twiddle factor are always the same */
  for ( j = 0; j < (numPoints/64U); j++)
  {
      for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
      {
        temp = (16.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i)]     = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i) + 1U] = d2s(cosTheta);

        temp = (16.0 * 2.0 *  2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (VCOP_SIMD_WIDTH * 2U) + (2U* i)]     = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (VCOP_SIMD_WIDTH * 2U) + (2U* i)] = d2s(cosTheta);

        temp = (16.0 * 3.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) +  (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)]    = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)] = d2s(cosTheta);
      }
  }
}


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_256
 *
 *  @desc     This function returns the size twiddle factor buffer in bytes to be used
  *                for target implementaion of 256 point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    size of twiddle factor bufer
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_256(void)
{
  uint32_t numPoints = 256U;
  uint32_t sizeOfTwiddleFactor;
  sizeOfTwiddleFactor = ((numPoints/4U)+ (2U * (numPoints/16U))+((numPoints/64U)* 8U)) * 3U * 2U * 2U ;
  return sizeOfTwiddleFactor;
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_256
 *
 *  @desc     This function generates twiddle factor to be used for target implementaion of 256
 *                point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  twiddleFactorBuf
 *                        Generated twiddle factor
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
void generateTwiddleFactor_256(int16_t twiddleFactorBuf[])
{
  double64_t scale;
  uint32_t i,j;
  double64_t temp;
  double64_t cosTheta;
  double64_t sinTheta;
  scale = 32767.0;
  uint32_t numPoints = 256U;
  uint32_t sizeOfTwiddleFactor;
  uint32_t tfBaseOffset;

  sizeOfTwiddleFactor = ((numPoints/4U)+ (2U * (numPoints/16U))+((numPoints/64U)* 8U)) * 3U * 2U * 2U ;

  /* Stage 1 */
  memset(twiddleFactorBuf,0,sizeOfTwiddleFactor);

  /* Each butterly needs 3 Twiddle factor (TF) and as we are going to work with 8BF per iteration hence store 8 twiddle factor for different  2nd leg of
    BF consecutively 8 TF for 3rd leg and then 8TF for 4th leg
    TF = cos(2*pi *k / N) + j sin(2*pi*k/N)*/
  tfBaseOffset = 0;
  for ( i = 0 ; i < (numPoints/4U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* Stage 2 */
  /* Stage 2 TF are stored same as stage 1 */
  tfBaseOffset = (numPoints/4U) * 3U * 2U;
  for ( i = 0 ; i < (numPoints/16U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (4.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (4.0 * 2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (4.0 * 3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* This is required because register allocation is failing if we move twiddle factor read outside the inner most loop */
  i = 0;
  memcpy(&twiddleFactorBuf[tfBaseOffset + (i*(VCOP_SIMD_WIDTH * 2U)*3U)],
         &twiddleFactorBuf[tfBaseOffset + ((i - 1U)*(VCOP_SIMD_WIDTH * 2U)*3U)],
         (VCOP_SIMD_WIDTH * 2U*2U)*3U);

  /* Stage 3 */
  tfBaseOffset = (((numPoints/4U) + (2U * (numPoints/16U))) * 3U * 2U);

  /* From stage 3 onwards instead of working with 8BF within a single group we start working on 8BF from 8 differnt groups. Thats
     the reason we have to duplicate the twiddle factor for each leg 8 times as across groups twiddle factor are always the same */
  for ( j = 0; j < (numPoints/64U); j++)
  {
      for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
      {
        temp = (16.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i)]     = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i) + 1U] = d2s(cosTheta);

        temp = (16.0 * 2.0 *  2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (VCOP_SIMD_WIDTH * 2U) + (2U* i)]     = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (VCOP_SIMD_WIDTH * 2U) + (2U* i)] = d2s(cosTheta);

        temp = (16.0 * 3.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) +  (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)]    = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)] = d2s(cosTheta);
      }
  }
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     getSizeTwiddleFactor_64
 *
 *  @desc     This function returns the size twiddle factor buffer in bytes to be used
  *                for target implementaion of 64 point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    size of twiddle factor bufer
 *
 *  =======================================================
 */
uint32_t getSizeTwiddleFactor_64(void)
{
  uint32_t numPoints = 64U;
  uint32_t sizeOfTwiddleFactor;
  sizeOfTwiddleFactor = ((numPoints/4U) + (8U * (numPoints/16U))) * 3U * 2U * 2U ;
  return sizeOfTwiddleFactor;
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     generateTwiddleFactor_64
 *
 *  @desc     This function generates twiddle factor to be used for target implementaion of 64
 *                point FFT
 *
 *  @inputs   This function takes following Inputs
 *                 NONE
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  twiddleFactorBuf
 *                        Generated twiddle factor
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
void generateTwiddleFactor_64(int16_t twiddleFactorBuf[])
{
  double64_t scale;
  uint32_t i,j;
  double64_t temp;
  double64_t cosTheta;
  double64_t sinTheta;
  scale = 32767.0;
  uint32_t numPoints = 64U;
  uint32_t sizeOfTwiddleFactor;
  uint32_t tfBaseOffset;

  sizeOfTwiddleFactor = ((numPoints/4U) + (8U * (numPoints/16U))) * 3U * 2U * 2U ;

  /* Stage 1 */
  memset(twiddleFactorBuf,0,sizeOfTwiddleFactor);

  /* Each butterly needs 3 Twiddle factor (TF) and as we are going to work with 8BF per iteration hence store 8 twiddle factor for different  2nd leg of
    BF consecutively 8 TF for 3rd leg and then 8TF for 4th leg
    TF = cos(2*pi *k / N) + j sin(2*pi*k/N)*/
  tfBaseOffset = 0;
  for ( i = 0 ; i < (numPoints/4U); i+=8U)
  {
    for ( j = 0; j < 8U; j++)
    {
      temp = (2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) ]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U] = d2s(cosTheta);

      temp = (2.0 *  2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) + (VCOP_SIMD_WIDTH * 2U)]     = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (VCOP_SIMD_WIDTH * 2U)] = d2s(cosTheta);

      temp = (3.0 * 2.0 * PI * ((double64_t)i +(double64_t)j))/ (double64_t)numPoints;
      cosTheta = cos(temp) * scale;
      sinTheta = sin(temp) * scale;
      twiddleFactorBuf[tfBaseOffset + (2U*j) +  (2U * (VCOP_SIMD_WIDTH * 2U))]    = d2s(sinTheta);
      twiddleFactorBuf[tfBaseOffset + (2U*j) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U))] = d2s(cosTheta);
    }
    tfBaseOffset += (3U * (VCOP_SIMD_WIDTH * 2U));
  }

  /* Stage 2 */
  /* From stage 3 onwards instead of working with 8BF within a single group we start working on 8BF from 8 differnt groups. Thats
     the reason we have to duplicate the twiddle factor for each leg 8 times as across groups twiddle factor are always the same */
  tfBaseOffset = (numPoints/4U) * 3U * 2U;
  for ( j = 0; j < (numPoints/16U); j++)
  {
      for ( i = 0; i < VCOP_SIMD_WIDTH; i++)
      {
        temp = (4.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i)]     = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (2U*i) + 1U] = d2s(cosTheta);

        temp = (4.0 * 2.0 *  2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + (VCOP_SIMD_WIDTH * 2U) + (2U* i)]     = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (VCOP_SIMD_WIDTH * 2U) + (2U* i)] = d2s(cosTheta);

        temp = (4.0 * 3.0 * 2.0 * PI * (double64_t)j)/ (double64_t)numPoints;
        cosTheta = cos(temp) * scale;
        sinTheta = sin(temp) * scale;
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) +  (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)]    = d2s(sinTheta);
        twiddleFactorBuf[tfBaseOffset + ((2U*(j* 3U * VCOP_SIMD_WIDTH))) + 1U + (2U * (VCOP_SIMD_WIDTH * 2U)) + (2U* i)] = d2s(cosTheta);
      }
  }
}

/*==========================================================================*/
/*      Copyright (C) 1997-2000 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
