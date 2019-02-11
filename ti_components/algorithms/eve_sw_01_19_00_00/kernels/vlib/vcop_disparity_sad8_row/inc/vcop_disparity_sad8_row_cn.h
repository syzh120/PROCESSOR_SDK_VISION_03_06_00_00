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


/**
 *******************************************************************************
 *  @func          vcop_disparity_sad8_row_cn
 *  @brief         The function vcop_disparity_sad8_row_cn takes two input image rows,          
 * left and right and compute the disparity and kinimum SAD cost for every pixel 
 * Use this function for the very first row of the image                        
 * Subsequent row should use vcop_disparity_sad8_row_iterative_cn() in the same file .
 *
 *
 *  @param [in]    left : Pointer to row from left image 
 *  @param [in]    right : Pointer to row from right image
 *  @param [in]    leftStride : Stride of the left row, need to be greater or equal to width + winWidth-1
 *  @param [in]    rightStride : Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 
 *  @param [in]    winWidth : width of the support window used for SAD calculation
 *  @param [in]    winHeight : height of the support window used for SAD calculation
 *  @param [in]    disparityOutput: pointer to disparity found for every pixels. Size is (numDisparities/disparityStep) bytes
 *  @param [in]    minCostOutput: pointer to minimum cost corresponding to the disparity found for every pixel. Size is 2*(numDisparities/disparityStep) bytes 
 *  @param [in]    allCostOutput: size must be equal 2*(numDisparities/disparityStep )*width bytes
 *  @param [in]    width: Must be multiple of 32, number of pixels in the row for which disparities are produced 
 *  @param [in]    numDisparities: Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep
 *  @param [in]    disparityStep: Disparity step, for faster computation
 *  @return        None
 *******************************************************************************
 */

#ifndef _VCOP_DISPARITY_SAD_8_CN_H_
#define _VCOP_DISPARITY_SAD_8_CN_H_

#include <stdint.h>

void vcop_disparity_sad8_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_sad8_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_sad8_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

#endif
