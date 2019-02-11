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


/** @file stereoVision_testfuncs.c
 *
 *  @brief  This file contains test code for stereoVision algorithm
 *
 *
 *  @date   21 Aug 2014
 *
 *  Description
 *    This file contains test code to validate the frame level applet for
 *    hamming-based disparity calculation. It also checks the output against c reference
 *    outputs and profiles the performance and computes the system
 *    overheads.
 */

#ifndef _STEREO_VISION_FUNCS_H_
#define _STEREO_VISION_FUNCS_H_

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vcop.h>

#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"
#include "iDisparity_ti.h"
#include "iCensus_ti.h"
#include "../vlib/vcop_census_8bits/inc/vcop_census_8bits_cn.h"
#include "../vlib/vcop_census_16bits/inc/vcop_census_16bits_cn.h"
#include "../vlib/vcop_disparity_hammingDistance_row/inc/vcop_disparity_hammingDistance_row_cn.h"
#include "../vlib/vcop_disparity_sad8_row/inc/vcop_disparity_sad8_row_cn.h"
#include "../vlib/vcop_disparity_sad16_row/inc/vcop_disparity_sad16_row_cn.h"

#include "ti_image_file_io.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

void convertCensus32bitsTo8bits(
        uint32_t *disparity_input, 
        uint8_t *disparity_input8bits, 
        uint32_t size);

int32_t validateCensus(
        uint8_t *census_inputLeft, 
        uint8_t *census_inputRight,
        uint8_t *disparity_inputLeft,
        uint8_t *disparity_inputRight,
        uint8_t *refDisparity_inputLeft,
        uint8_t *refDisparity_inputRight,
        CENSUS_TI_CreateParams *census_createParams,
        uint16_t srcImagePitch,
        uint16_t dstImagePitch,
        uint16_t left_n_rows,
        uint8_t numBytesPerCensus
);

int32_t validateHamDistDisparity(
        uint8_t *disparity_inputLeft,
        uint8_t *disparity_inputRight,
        uint8_t *dispOutput,
        uint8_t *dispRefOutput,
        uint16_t *minCostOutput,
        uint16_t *minCostRefOutput,
        uint16_t *prevAdjCostOutput,
        uint16_t *nextAdjCostOutput,
        uint16_t *prevAdjCostRefOutput,
        uint16_t *nextAdjCostRefOutput,
        uint16_t *natC_allCostOutput,
        uint16_t *natC_allCostRLOutput,
        CENSUS_TI_CreateParams *census_createParams,
        DISPARITY_TI_CreateParams *disparity_createParams,
        uint16_t imageWidth,
        uint16_t imageHeight,
        uint16_t dstImagePitch
);

void convertDisparityFalseColor(
        uint8_t *image_red, 
        uint8_t *image_grn, 
        uint8_t *image_blu, 
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height, 
        uint8_t numDisparities,
        float maxMinCostRatio);

void convertDisparityFalseColorYUV444(
        uint8_t *image_y,
        uint8_t *image_u,
        uint8_t *image_v,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio);

void convertDisparityFalseColorYUV420SP(
        uint8_t *image_y,
        uint8_t *image_uv,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio);

float computeErrorsGroundTruth(
        uint8_t *dispOut,
        uint8_t *gtImage,
        uint8_t *diffImage,
        uint16_t dispWidth,
        uint16_t dispHeight,
        uint16_t gtWidth,
        uint16_t gtHeight,
        uint8_t filterWidth,
        uint8_t filterHeight,
        uint8_t numDisparities,
        uint8_t gtScale,
        uint8_t *maxDiffPtr
);

int32_t computeSADdisparity8bits(
        uint8_t *disparity_inputLeft, 
        uint8_t *disparity_inputRight,
        uint8_t *dispOutput,
        uint16_t *minCostOutput,
        uint16_t *natC_allCostOutput,
        DISPARITY_TI_CreateParams *disparity_createParams,
        uint16_t imageWidth,
        uint16_t imageHeight,
        uint16_t srcImagePitch,
        uint16_t dstImagePitch
);


void vcop_disparity_hammingDistance_row_ref_cn
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
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
); 

void vcop_disparity_hammingDistance_first_row_cn
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
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
);

void vcop_disparity_hammingDistance_nth_row_cn
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
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
);

#endif


