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
 *  @func          init_disparity_hammingDistance_row_params
 *  @brief         This function initializes and checks the validity of some of the parameters passed to vcop_disparity_hammingDistance_row()
 *
 *  @param [out]   pOffset : Pointer to offset array that will be used by p-scatter and is filled by init_disparity_sad8_row_params()
 *  @param [in]    sizeOffsetArray : sizeOffsetArray should be set to 32 bytes, this parameter is checked by init_disparity_sad8_row_params() prior to filling pOffset 
 *  @param [out]   collateMask : Pointer to single byte that will be filled by  init_disparity_sad8_row_params
 *  @param [out]   scratchBufferSize : size of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferSize
 *  @param [out]   scratchBufferStride :  stride of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferStride
 *  @param [out]   allCostOutputStride: value allCostOutputStride that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputStride 
 *  @param [out]   allCostOutputBufferSize: size of allCostOutputBuffer that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputBufferSize 
 *  @param [in]    width: Number of pixels in the row for which disparities are calculated
 *  @param [in]    numDisparities: number of disparities
 *  @param [in]    disparityStep: disparity step
 *  @return        None
 *******************************************************************************
 */
#ifndef _INIT_DISPARITY_HAMMING_H_
#define _INIT_DISPARITY_HAMMING_H_

#include <stdint.h>

#define SIZE_COST (2U) /* disparity cost is 2 bytes */

int32_t init_disparity_hammingDistance_row_params
(
        uint16_t *pOffset,  /* Pointer to offset array that will be used by p-scatter and is filled by init_disparity_sad8_row_params() */
        uint8_t sizeOffsetArray, /* sizeOffsetArray should be set to 32 bytes, this parameter is checked by init_disparity_sad8_row_params() prior to filling pOffset */
        uint8_t *collateMask, /* Pointer to single byte that will be filled by  init_disparity_sad8_row_params */
        uint16_t *scratchBufferSize, /* size of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferSize */
        uint16_t *scratchBufferStride, /* stride of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferStride */
        uint16_t *allCostOutputStride, /* value allCostOutputStride that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputStride */
        uint16_t *allCostOutputBufferSize, /* size of allCostOutputBuffer that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputBufferSize */
        uint16_t width, /* Number of pixels in the row for which disparities are calculated */
        uint8_t numDisparities, /* number of disparities */
        uint8_t disparityStep /* disparity step */
);

#endif
