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
/*     @file : vcop_sad_error_measure_lk_cn.h                               */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing SAD (Sum of Absolute Differences) based error */
/*     measure for each key point. It will also incorporate boundary check  */
/*     compute and initializes error to 0xFFFF for out of bound key points  */
/*     The following figure illustrates the input data arrangement of the   */
/*     bilinear interpolated patch windows for both previous and current    */
/*     frames across each key point.                                        */
/*                                                                          */
/*                           (inputStride) bytes                            */
/*                            (blkWidth) bytes                              */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (blkHeight)     |        Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |        Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |  Blk(numKeyPoints-1)  |                           */
/*                      |_______________________|                           */
/*                                                                          */
/*     @version 1.0 (January 2014) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

#include <stdint.h>

#ifndef _VCOP_SAD_ERROR_MEASURE_LK_CN
#define _VCOP_SAD_ERROR_MEASURE_LK_CN  1
/*!

  @fn     vcop_sad_error_measure_lk_cn

  @brief  This is the c-reference for the vcop_sad_error_measure_lk_cn
          kernel. This routine accepts tracked (X, Y) coordinates lists
          of length 'numKeyPoints', bilinear interpolated patch windows
          around the initial and tracked key point locations for both
          previous and current frame respectively. blkOffset denotes the
          inter block offset which implies distance between first pixel
          of Blk(n) and Blk(n-1) as illustrated in figure above. 7x7
          neighboorhood window is being used here, due to SIMD alignment
          8x7 is recommended as blkWidth x blkHeight. It computes the SAD
          based error measure of LK at every key point. For out of bound
          points, it will initialize the error to 0xFFFF

  @param  pPrevBiLinImg_A    : Pointer to previous frame bilinear interpolated patch windows
  @param  pCurrBiLinImg_B    : Pointer to current frame bilinear interpolated patch windows
  @param  pNewLocalXYList_X  : Pointer to local XY coordinates locations corresponding to the tracked locations
  @param  pOutErrorMeasure_C : Pointer to SAD based error measure for each key point being tracked
  @param  inputStride       : Stride of the previous or current frame bilinear interpolated patch windows, pPrevBiLinImg_A or pCurrBiLinImg_B
  @param  frmWidth           : Width of the previous or current frame in bytes
  @param  frmHeight          : Height of the previous or current frame in bytes
  @param  blkWidth           : Width of the input block around each key point
  @param  blkHeight          : Height of the input block around each key point
  @param  numKeyPoints       : Number of key points
  @param  shiftValue         : Number of fractional bits

*/
void vcop_sad_error_measure_lk_cn
(
   uint8_t     *pPrevBiLinImg_A,
   uint8_t     *pCurrBiLinImg_B,
   uint16_t    *pNewXYList_X,
   uint16_t    *pOutErrorMeasure_C,
   uint16_t     inputStride,
   uint16_t     frmWidth,
   uint16_t     frmHeight,
   uint16_t     blkWidth,
   uint16_t     blkHeight,
   uint16_t     numKeyPoints,
   uint16_t     shiftValue,
   uint16_t     sadThreshold,
   uint16_t    *numValidPoints
);
#endif /* _VCOP_SAD_ERROR_MEASURE_LK_CN */
