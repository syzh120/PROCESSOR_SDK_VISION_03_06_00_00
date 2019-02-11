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
/*  @file : vcop_sobel_xy_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Sobel xy computation for circles.                   */
/*                                                                          */
/*  @version 0.1 (Dec 2014) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_SOBEL_XY_CN_H_
#define VCOP_SOBEL_XY_CN_H_


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_sobelXY_3x3_separable_uchar_cn
 *
 *  @desc     Implementation of sobel X and Y operator together
 *                 which is [1 2 1] x [1 0 -1]'
 *
 *  @inputs   This func takes following Inputs
 *                  inData :
 *                          Input data pointer
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  roundShift :
 *                          Rounding that needs to be applied to the output
 *
 *  @scratch   This function needs  following scratch buffers
 *                  interimDataX :
 *                          This is dummy pointer just to keep interface of ref and kernel same. Its not really required
 *                          by reference C
 *                  interimDataY :
 *                          This is dummy pointer just to keep interface of ref and kernel same. Its not really required
 *                          by reference C
 *
 *  @outputs   This function produce following outputs
 *                  outDataX
 *                          Pointer to the output for X component
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *                  outDataY
 *                          Pointer to the output for Y component
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXY_3x3_separable_uchar_cn
(
  uint8_t  *inData,
  int16_t  *interimDataX,
  int16_t  *interimDataY,
  int8_t   *outDataX,
  int8_t   *outDataY,
  uint16_t  computeWidth,
  uint16_t  computeHeight,
  uint16_t  inputPitch,
  uint16_t  outputPitch,
  uint8_t   roundShift
);


/* ==================================================
 *  @func     vcop_sobelXy_3x3_L1_thresholding_cn
 *
 *  @desc     This function uses L1 norm and thesholding
 *
 *
 *  @inputs   This function takes following Inputs
 *                  gradX :
 *                          Gradient X
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  gradY :
 *                          Gradient Y
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  threshold :
 *                          Threshold to be used for thresholding magnitude
 *
 *  @scratch   This function needs  following scratch buffers
 *                          None
 *
 *  @outputs   This function produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl containing 255 at places where edges are present and 0 otherwise
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_sobelXy_3x3_L1_thresholding_cn
(
   int8_t   *gradX,
   int8_t   *gradY,
   uint8_t  *outData,
   uint16_t  computeWidth,
   uint16_t  computeHeight,
   uint16_t  inputPitch,
   uint16_t  outputPitch,
   uint16_t  threshold
);

/* ==================================================
 *  @func  vcop_sobelXy_3x3_L1_thresholding_binPack_cn
 *
 *  @desc     This function uses L1 norm and thesholding and gives a binary image output
 *                whose bits indicate edge if it is 1 and non-edge if it is zero. While loading
 *                a data in byte lower most bit will correspond to the first pixel.
 *
 *
 *  @inputs   This function takes following Inputs
 *                  gradX :
 *                          Gradient X
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  gradY :
 *                          Gradient Y
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  threshold :
 *                          Threshold to be used for thresholding magnitude
 *
 *  @outputs   This function produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl containing 1 and places where edges are present and 0 otherwise
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t) /8
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXy_3x3_L1_thresholding_binPack_cn
(
   int8_t   *gradX,
   int8_t   *gradY,
   uint8_t  *outData,
   uint16_t  computeWidth,
   uint16_t  computeHeight,
   uint16_t  inputPitch,
   uint16_t  outputPitch,
   uint16_t  threshold
);


#endif /* VCOP_SOBEL_XY_CN_H_ */

