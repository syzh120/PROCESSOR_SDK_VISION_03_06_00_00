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
 *  @brief  This file contains some support functiosn for the test code for stereoVision algorithm
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
#include "stereoVision_testfuncs.h"

#include "ti_image_file_io.h"
#include "eve_profile.h"

#define MIN(a,b) ((a)<(b)?(a):(b))


/* The below table is used by convertDisparityFalseColor for producing a disparity colormap */
const uint8_t falseColorLUT_RGB[3][257] = {
        {0,33,28,24,21,18,14,10,6,3,1,2,2,2,3,2,3,2,2,2,2,3,3,3,2,2,2,3,3,2,3,1,3,3,2,2,3,2,3,3,2,2,3,2,2,3,3,3,3,2,2,4,2,3,3,2,3,3,2,2,3,3,3,2,2,3,2,2,3,1,3,2,3,2,3,3,3,2,2,2,2,3,2,3,2,3,3,3,3,2,2,2,3,2,3,2,4,2,1,3,2,2,2,3,3,3,2,2,2,1,8,13,20,26,31,38,44,50,56,63,67,74,81,86,93,99,104,110,117,123,129,136,140,147,155,159,166,172,177,183,191,196,202,209,214,219,225,231,238,244,249,255,254,255,255,255,255,255,255,255,255,254,255,255,254,255,255,255,255,255,255,255,255,254,255,255,255,255,255,255,255,255,255,255,255,255,255,254,255,255,255,255,255,255,255,255,255,255,255,254,255,255,254,255,255,255,255,255,255,255,254,254,255,254,255,255,255,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,255,255,255,254,255,255,255,254,255,254,255,255,255,255,255,254,255,255,255,255,255,255,254,255},
        {0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,6,12,19,25,32,37,43,51,57,63,70,76,82,89,95,101,109,115,120,127,133,140,146,152,158,165,172,178,184,190,196,204,209,216,222,229,236,241,247,254,254,254,255,254,254,255,254,254,255,254,255,254,254,254,254,253,254,253,254,254,253,255,253,253,254,254,254,254,254,254,254,253,254,253,254,254,253,254,254,254,254,253,254,253,254,254,253,254,254,254,253,254,254,254,254,253,254,253,254,255,254,254,254,254,254,254,255,254,255,254,254,255,254,254,254,255,254,255,255,255,255,255,252,249,247,244,241,239,237,234,231,230,227,225,222,219,217,215,211,209,207,205,201,200,198,195,192,189,187,184,181,179,177,174,171,169,168,164,162,160,157,154,152,150,147,144,142,139,138,135,132,130,126,124,122,120,116,114,112,109,107,105,100,97,94,90,87,83,81,76,73,70,67,63,59,57,52,49,45,43,39,35,31,29,25,21,18,15,11,7,4,1,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1},
        {0,96,101,104,108,113,116,120,125,129,135,142,148,153,160,166,174,179,185,192,198,205,211,217,224,230,235,242,248,255,255,255,255,255,254,255,255,255,255,255,254,253,255,255,255,254,255,255,255,255,255,255,255,254,254,255,255,255,255,254,254,255,255,255,255,255,255,255,255,255,249,242,236,231,224,217,210,205,199,192,186,179,173,169,162,155,149,144,138,130,123,117,112,105,99,91,87,80,73,67,60,54,48,41,35,28,23,17,9,2,5,4,4,3,3,4,3,3,2,3,4,4,4,4,4,3,3,2,3,3,2,5,4,4,4,3,4,3,3,2,3,3,4,4,4,4,3,3,4,3,3,2,2,3,4,5,2,3,4,5,2,3,4,3,3,4,4,3,3,4,3,3,3,4,3,4,3,4,3,3,4,2,3,3,4,3,4,3,2,3,4,3,2,3,4,4,3,3,4,2,3,4,3,2,3,4,2,2,3,4,2,3,2,2,3,3,2,2,3,2,2,3,3,2,2,3,3,2,2,3,3,2,2,3,2,2,2,3,2,2,2,3,9,16,23,27,34,40,48,53,59,66,73,77,85,89,96}
};

const uint8_t falseColorLUT_YUV[3][257] = {
        {16,34,33,32,32,31,30,30,29,29,29,30,31,31,32,32,33,34,34,35,35,36,37,38,38,39,39,40,41,41,44,47,51,54,57,60,63,67,70,73,76,79,83,86,89,92,96,99,102,105,108,112,115,118,121,124,128,131,134,137,140,144,147,150,153,157,160,162,166,169,169,168,168,167,166,166,165,164,164,163,163,162,161,161,160,159,159,158,158,157,156,156,155,154,154,153,153,152,151,151,150,149,149,148,148,147,146,146,145,144,146,147,149,150,152,154,155,157,158,160,161,163,165,166,168,169,171,171,174,176,177,179,180,182,184,185,187,188,190,191,193,195,196,198,199,201,202,204,206,207,208,210,208,207,206,205,203,202,201,199,198,197,196,195,193,192,191,190,188,187,186,185,183,182,181,180,178,177,176,174,173,171,171,169,168,167,166,164,163,162,161,159,158,157,156,154,153,151,151,149,148,147,145,144,143,142,140,139,138,136,135,134,132,130,129,127,125,123,122,120,118,117,115,113,111,110,108,106,104,103,101,99,97,96,94,92,90,89,87,85,83,82,82,83,84,84,85,85,86,87,87,88,89,89,90,90,91},
        {128,164,167,170,172,174,176,179,181,184,187,190,192,194,197,200,203,205,208,211,214,217,220,222,226,228,230,233,236,239,237,236,233,232,229,228,226,224,222,221,218,216,215,213,212,209,207,206,204,202,200,198,197,194,193,191,189,187,186,183,182,180,178,176,175,172,170,169,167,165,162,160,156,155,151,148,145,143,140,138,135,132,129,127,124,121,119,117,114,110,108,104,103,100,97,93,91,88,85,83,80,77,74,71,69,65,64,61,57,54,55,54,52,51,50,50,49,48,46,46,46,44,43,43,42,41,40,38,38,36,35,36,35,34,32,31,30,29,28,27,27,26,25,24,24,23,22,20,20,19,18,16,17,19,20,21,21,22,23,24,23,24,25,26,27,28,28,29,30,31,31,31,33,33,33,35,35,37,37,38,39,39,40,40,42,42,43,44,43,45,46,46,46,47,49,50,50,51,51,52,53,54,55,55,56,57,57,57,58,60,60,61,62,63,64,65,65,67,68,69,69,71,72,72,73,74,76,76,78,79,80,80,82,83,83,85,86,87,87,89,90,91,94,97,100,102,104,107,111,113,116,118,122,123,127,129,132},
        {128,135,132,131,129,127,125,123,121,120,118,118,118,118,117,117,116,115,115,115,114,114,114,113,112,112,112,112,111,110,109,105,104,102,99,97,95,92,90,88,85,82,81,78,75,74,71,68,67,64,61,60,57,55,53,50,47,45,43,40,39,36,34,31,29,26,23,22,20,16,18,18,18,19,19,20,20,20,20,21,21,23,23,23,23,25,25,25,26,26,27,26,28,28,28,28,30,29,29,31,31,31,31,33,33,33,34,34,34,34,37,40,43,46,47,50,53,56,58,61,64,66,69,71,75,78,79,83,85,87,91,93,95,98,102,104,106,109,111,114,118,119,122,125,128,130,133,135,138,141,143,145,146,148,148,149,151,151,152,153,154,154,156,156,157,159,159,160,162,162,163,164,165,165,166,167,169,170,170,172,173,173,174,175,176,177,177,178,180,180,181,183,183,184,185,186,187,188,188,189,191,191,192,194,194,195,197,197,198,199,199,200,203,203,205,206,207,208,209,211,212,213,215,216,218,218,220,221,223,223,225,226,227,229,230,232,232,234,235,237,237,239,238,238,237,238,237,237,235,235,235,234,234,234,233,232,232}
};

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
) {
    if (searchDir== 0) { /* left right */
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_row_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_row_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
    }
    else {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_row_right_left_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_row_ref_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    numDisparities,
                    disparityStep
            );
        }
    }
}

void vcop_disparity_hammingDistance_row_right_left_ref_cn(
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
        uint8_t codeWordLen
) {
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_row_right_left_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_row_right_left_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }

}

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
){
    if (searchDir== 0) {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
    }
    else {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_RL_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_first_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
    }
}

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
){
    if (searchDir== 0) {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
    }
    else {
        if (codeWordLen== 4) {
            vcop_disparity_hammingDistance32_RL_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
        else if (codeWordLen== 8) {
            vcop_disparity_hammingDistance64_nth_row_cn
            (
                    left,
                    right,
                    leftStride,
                    rightStride,
                    winWidth,
                    winHeight,
                    disparityOutput,
                    minCostOutput,
                    prevAllCostOutput,
                    allCostOutput,
                    width,
                    allCostOutputStride,
                    numDisparities,
                    disparityStep
            );
        }
    }
}
#if 0
void rgb2yuv(){//(const uint8_t falseColorLUT_RGB[3][257], uint8_t falseColorLUT_YUV[3][257]){

    int32_t i;
    float r,g,b;
    int16_t y,u,v;
    for (i=0;i<257;i++) {
        r= (float)falseColorLUT_RGB[0][i];
        g= (float)falseColorLUT_RGB[1][i];
        b= (float)falseColorLUT_RGB[2][i];

        y= (uint16_t)((0.257 * r) + (0.504 * g) + (0.098 * b) + 16);
        if (y > 255) {
            y= 255;
        }
        else if (y<0){
            y=0;
        }

        u= (uint16_t)(-(0.148 * r) - (0.291 * g) + (0.439 * b) + 128);
        if (v > 255) {
            v= 255;
        }
        else if (v<0){
            v=0;
        }

        v= (uint16_t)( (0.439 * r) - (0.368 * g) - (0.071 * b) + 128);
        if (u > 255) {
            u= 255;
        }
        else if (u<0){
            u=0;
        }

        falseColorLUT_YUV[0][i]= y;
        falseColorLUT_YUV[1][i]= u;
        falseColorLUT_YUV[2][i]= v;
    }

    for (i=0;i<257;i++) {
        printf("%d,", falseColorLUT_YUV[0][i]);
    }
    printf("\n");
    for (i=0;i<257;i++) {
        printf("%d,", falseColorLUT_YUV[1][i]);
    }
    printf("\n");
    for (i=0;i<257;i++) {
        printf("%d,", falseColorLUT_YUV[2][i]);
    }
    printf("\n");

}
#endif

void convertDisparityFalseColor(
        uint8_t *image_red,
        uint8_t *image_grn,
        uint8_t *image_blu,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio) {

    int32_t x, y, value, idx=0;
    uint16_t maxCost= 0;

    /* First, search for the maxCost */

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (costOutput[idx] > maxCost) {
                maxCost = costOutput[idx];
            }
            idx++;
        }
    }

    maxCost= (uint16_t)(maxMinCostRatio*(float)maxCost);

    idx= 0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
#if 1
            if (costOutput[idx] <= maxCost)
                value = (dispOutput[idx] * (int32_t)255)/numDisparities;
            else
                value= 0;
#else
            value= (y*(int32_t)255)/height;
#endif
            image_red[idx] = (uint8_t) (falseColorLUT_RGB[0][value]);
            image_grn[idx] = (uint8_t) (falseColorLUT_RGB[1][value]);
            image_blu[idx] = (uint8_t) (falseColorLUT_RGB[2][value]);
            idx++;
        }
    }
}

void convertDisparityFalseColorYUV444(
        uint8_t *image_y,
        uint8_t *image_u,
        uint8_t *image_v,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio) {

    int32_t x, y, value, idx=0;
    uint16_t maxCost= 0;

    /* First, search for the maxCost */

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (costOutput[idx] > maxCost) {
                maxCost = costOutput[idx];
            }
            idx++;
        }
    }

    maxCost= (uint16_t)(maxMinCostRatio*(float)maxCost);

    idx= 0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (costOutput[idx] <= maxCost)
                value = (dispOutput[idx] * (int32_t)255)/numDisparities;
            else
                value= 0;

            image_y[idx] = (uint8_t) (falseColorLUT_YUV[0][value]);
            image_u[idx] = (uint8_t) (falseColorLUT_YUV[1][value]);
            image_v[idx] = (uint8_t) (falseColorLUT_YUV[2][value]);
            idx++;
        }
    }
}

void convertDisparityFalseColorYUV420SP(
        uint8_t *image_y,
        uint8_t *image_uv,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio) {

    int32_t x, y, value, idx=0;
    uint16_t maxCost= 0;

    /* First, search for the maxCost */

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (costOutput[idx] > maxCost) {
                maxCost = costOutput[idx];
            }
            idx++;
        }
    }

    maxCost= (uint16_t)(maxMinCostRatio*(float)maxCost);

    idx= 0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {

            if (costOutput[idx] <= maxCost)
                value = (dispOutput[idx] * (int32_t)255)/numDisparities;
            else
                value= 0;

            image_y[y*width + x] = (uint8_t) (falseColorLUT_YUV[0][value]);
            image_uv[(y>>1)*width + ((x>>1)<<1)] = (uint8_t)(falseColorLUT_YUV[1][value]);
            image_uv[(y>>1)*width + ((x>>1)<<1) + 1] = (uint8_t)(falseColorLUT_YUV[2][value]);
            idx++;
        }
    }
}

void convertCensus32bitsTo8bits(
        uint32_t *disparity_input,
        uint8_t *disparity_input8bits,
        uint32_t size) {
    uint32_t i;
    uint8_t bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7;

    for(i=0;i<size;i++){
#if 1
        bit0= ((disparity_input[i] & 0x0000000F)!=0 );
        bit1= ((disparity_input[i] & 0x000000F0)!=0 );
        bit2= ((disparity_input[i] & 0x00000F00)!=0 );
        bit3= ((disparity_input[i] & 0x0000F000)!=0 );
        bit4= ((disparity_input[i] & 0x000F0000)!=0 );
        bit5= ((disparity_input[i] & 0x00F00000)!=0 );
        bit6= ((disparity_input[i] & 0x0F000000)!=0 );
        bit7= ((disparity_input[i] & 0xF0000000)!=0 );
        disparity_input8bits[i]= bit0 | (bit1<<1) | (bit2<<2) |(bit3<<3) | (bit4<<4) | (bit5<<5) | (bit6<<6) | (bit7<<7);
#else
        disparity_input8bits[i]= disparity_input[i];
#endif
    }
}

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
        uint16_t n_rows,
        uint8_t numBytesPerCensus
){

    int32_t i,j, fail=0;

    if (census_createParams->inputBitDepth <= 8) {
        vcop_census_8bits_cn(
                census_inputLeft,
                refDisparity_inputLeft,
                census_createParams->winWidth,
                census_createParams->winHeight,
                census_createParams->winHorzStep,
                census_createParams->winVertStep,
                census_createParams->imgFrameWidth,
                census_createParams->imgFrameHeight,
                srcImagePitch,
                dstImagePitch
        );
        vcop_census_8bits_cn(
                census_inputRight,
                refDisparity_inputRight,
                census_createParams->winWidth,
                census_createParams->winHeight,
                census_createParams->winHorzStep,
                census_createParams->winVertStep,
                census_createParams->imgFrameWidth,
                census_createParams->imgFrameHeight,
                srcImagePitch,
                dstImagePitch
        );
    }
    else {
        vcop_census_16bits_cn(
                (uint16_t*)census_inputLeft,
                refDisparity_inputLeft,
                census_createParams->winWidth,
                census_createParams->winHeight,
                census_createParams->winHorzStep,
                census_createParams->winVertStep,
                census_createParams->imgFrameWidth,
                census_createParams->imgFrameHeight,
                srcImagePitch,
                dstImagePitch
        );
        vcop_census_16bits_cn(
                (uint16_t*)census_inputRight,
                refDisparity_inputRight,
                census_createParams->winWidth,
                census_createParams->winHeight,
                census_createParams->winHorzStep,
                census_createParams->winVertStep,
                census_createParams->imgFrameWidth,
                census_createParams->imgFrameHeight,
                srcImagePitch,
                dstImagePitch
        );
    }

    fail = 0;

    for (i = 0; i<MIN(census_createParams->imgFrameHeight, n_rows - (census_createParams->winHeight - 1)); i++)
    {
        for(j=0; j<census_createParams->imgFrameWidth * numBytesPerCensus; j++)
        {
            if(disparity_inputLeft[i*census_createParams->imgFrameWidth*numBytesPerCensus+j] != refDisparity_inputLeft[i*census_createParams->imgFrameWidth*numBytesPerCensus+j])
            {
                fail = 1;
                TEST_PRINTF("Census left error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, disparity_inputLeft[i*census_createParams->imgFrameWidth*numBytesPerCensus+j], refDisparity_inputLeft[i*census_createParams->imgFrameWidth*numBytesPerCensus+j]);
                break;
            }
        }
    }

    for (i = 0; i<MIN(census_createParams->imgFrameHeight, n_rows - (census_createParams->winHeight - 1)); i++)
    {
        for(j=0; j<census_createParams->imgFrameWidth * numBytesPerCensus; j++)
        {
            if(disparity_inputRight[i*census_createParams->imgFrameWidth*numBytesPerCensus+j] != refDisparity_inputRight[i*census_createParams->imgFrameWidth*numBytesPerCensus+j])
            {
                fail = 1;
                TEST_PRINTF("Census right error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, disparity_inputRight[i*census_createParams->imgFrameWidth*numBytesPerCensus+j], refDisparity_inputRight[i*census_createParams->imgFrameWidth*numBytesPerCensus+j]);
                break;
            }
        }
    }

    return fail;
}


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
){

    int32_t i,j,r,fail=0;
    uint16_t extraOffset;
    uint16_t *prevAdjCostRefOutputTemp= prevAdjCostRefOutput;
    uint16_t *nextAdjCostRefOutputTemp= nextAdjCostRefOutput;

    uint8_t inputByteLen= disparity_createParams->inputBitDepth>>3;

    if (disparity_createParams->searchDir== DISPARITY_TI_LEFT_TO_RIGHT) {
        prevAdjCostRefOutputTemp= prevAdjCostRefOutput;
        nextAdjCostRefOutputTemp= nextAdjCostRefOutput;
        extraOffset= disparity_createParams->numDisparities - 1;
    }
    else {
        prevAdjCostRefOutputTemp= nextAdjCostRefOutput;
        nextAdjCostRefOutputTemp= prevAdjCostRefOutput;
        extraOffset= 0;
    }

    for (r=0; r< imageHeight; r++) {
#if 0 /* Below is a very slow version of the natural C code so we disable it and instead use a faster version. Re-enable if you suspect faster version has a bug */
        vcop_disparity_hammingDistance_row_ref_cn
        (
                disparity_inputLeft + (extraOffset + r*census_createParams->imgFrameWidth)*inputByteLen,
                disparity_inputRight + (r*census_createParams->imgFrameWidth)*inputByteLen,
                census_createParams->imgFrameWidth*inputByteLen,
                census_createParams->imgFrameWidth*inputByteLen,
                disparity_createParams->winWidth,
                disparity_createParams->winHeight,
                dispRefOutput + r*dstImagePitch,
                minCostRefOutput + r*dstImagePitch,
                natC_allCostOutput,
                imageWidth,
                disparity_createParams->numDisparities,
                disparity_createParams->disparityStep,
                inputByteLen,
                disparity_createParams->searchDir
        );
#else
        if (r==0) {
            vcop_disparity_hammingDistance_first_row_cn(
                    disparity_inputLeft + extraOffset*inputByteLen,
                    disparity_inputRight,
                    census_createParams->imgFrameWidth*inputByteLen,
                    census_createParams->imgFrameWidth*inputByteLen,
                    disparity_createParams->winWidth,
                    disparity_createParams->winHeight,
                    dispRefOutput,
                    minCostRefOutput,
                    natC_allCostOutput,
                    imageWidth,
                    imageWidth,
                    disparity_createParams->numDisparities,
                    disparity_createParams->disparityStep,
                    inputByteLen,
                    disparity_createParams->searchDir
            );
        }
        else {
            vcop_disparity_hammingDistance_nth_row_cn(
                    disparity_inputLeft + (extraOffset + r*census_createParams->imgFrameWidth)*inputByteLen,
                    disparity_inputRight + (r*census_createParams->imgFrameWidth)*inputByteLen,
                    census_createParams->imgFrameWidth*inputByteLen,
                    census_createParams->imgFrameWidth*inputByteLen,
                    disparity_createParams->winWidth,
                    disparity_createParams->winHeight,
                    dispRefOutput + r*dstImagePitch,
                    minCostRefOutput + r*dstImagePitch,
                    natC_allCostOutput,
                    natC_allCostOutput,
                    imageWidth,
                    imageWidth,
                    disparity_createParams->numDisparities,
                    disparity_createParams->disparityStep,
                    inputByteLen,
                    disparity_createParams->searchDir
            );
        }
#endif

        vcop_disparity_genPrevAndNextMinCost_cn(
                dispRefOutput + r*dstImagePitch,
                natC_allCostOutput,
                prevAdjCostRefOutputTemp + r*dstImagePitch,
                nextAdjCostRefOutputTemp + r*dstImagePitch,
                imageWidth,
                disparity_createParams->numDisparities,
                disparity_createParams->disparityStep
        );
    }

    for(i=0; i<imageHeight; i++)
    {
        for(j=0; j<imageWidth; j++)
        {
            if(dispOutput[i*dstImagePitch+j] != dispRefOutput[i*dstImagePitch+j])
            {
                fail = 1;
                TEST_PRINTF("Disparity error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, dispOutput[i*dstImagePitch+j], dispRefOutput[i*dstImagePitch+j]);
                break;
            }
        }
    }

    for(i=0; i<imageHeight; i++)
    {
        for(j=0; j<imageWidth; j++)
        {
            if(minCostOutput[i*dstImagePitch+j] != minCostRefOutput[i*dstImagePitch+j])
            {
                fail = 1;
                TEST_PRINTF("Min-cost error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, minCostOutput[i*dstImagePitch+j], minCostRefOutput[i*dstImagePitch+j]);
                break;
            }
        }
    }

    for(i=0; i<imageHeight; i++)
    {
        for(j=0; j<imageWidth; j++)
        {
            if(prevAdjCostOutput[i*dstImagePitch+j] != prevAdjCostRefOutput[i*dstImagePitch+j])
            {
                fail = 1;
                TEST_PRINTF("Previous adjacent cost error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, prevAdjCostOutput[i*dstImagePitch+j], prevAdjCostRefOutput[i*dstImagePitch+j]);
                break;
            }
        }
    }

    for(i=0; i<imageHeight; i++)
    {
        for(j=0; j<imageWidth; j++)
        {
            if(nextAdjCostOutput[i*dstImagePitch+j] != nextAdjCostRefOutput[i*dstImagePitch+j])
            {
                fail = 1;
                TEST_PRINTF("Next adjacent cost error, row:%d, col:%d, out:%u, EOut:%u \n", i, j, nextAdjCostOutput[i*dstImagePitch+j], nextAdjCostRefOutput[i*dstImagePitch+j]);
                break;
            }
        }
    }

    return fail;
}

#define ABS(x) ((x) > 0 ? (x) : -(x) )

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
) {
    float totalErr=0.0;
    uint16_t diff;
    int16_t offset_x, offset_y, x, y;
    uint8_t maxDiff= 0;

    offset_x= filterWidth/2 + numDisparities - 1;
    offset_y= filterHeight/2;

    for(y=0; y<dispHeight; y++) {
        for(x=0; x<dispWidth; x++) {
            diff= ABS(gtScale*dispOut[x + y*dispWidth] - gtImage[x + offset_x + (y + offset_y)*gtWidth]);
            if (diff > maxDiff)
                maxDiff= diff;
            diffImage[x + y*dispWidth]= diff;
            totalErr+= (float)diff*diff;
        }
    }

    totalErr= sqrtf(totalErr/((float)dispWidth*dispHeight));
    *maxDiffPtr= maxDiff;

    return totalErr;
}

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
){

    int32_t r;

    for (r=0; r< imageHeight; r++) {
#if 0 /* Below is a very slow version of the natural C code so we disable it and instead use a faster version. Re-enable if you suspect faster version has a bug */
        vcop_disparity_sad8_row_ref_cn
        (
                disparity_inputLeft + (r*srcImagePitch) + (disparity_createParams->numDisparities - 1),
                disparity_inputRight + (r*srcImagePitch),
                srcImagePitch,
                srcImagePitch,
                disparity_createParams->winWidth,
                disparity_createParams->winHeight,
                dispRefOutput + r*dstImagePitch,
                minCostRefOutput + r*dstImagePitch,
                natC_allCostOimageWidth           imageWidth,
                disparity_createParams->numDisparities,
                disparity_createParams->disparityStep
        );
#else
        if (r==0) {
            vcop_disparity_sad8_first_row_cn(
                    disparity_inputLeft + (disparity_createParams->numDisparities - 1),
                    disparity_inputRight,
                    srcImagePitch,
                    srcImagePitch,
                    disparity_createParams->winWidth,
                    disparity_createParams->winHeight,
                    dispOutput,
                    minCostOutput,
                    natC_allCostOutput,
                    imageWidth,
                    imageWidth,
                    disparity_createParams->numDisparities,
                    disparity_createParams->disparityStep
            );
        }
        else {
            vcop_disparity_sad8_nth_row_cn(
                    disparity_inputLeft + r*srcImagePitch + (disparity_createParams->numDisparities - 1),
                    disparity_inputRight + r*srcImagePitch,
                    srcImagePitch,
                    srcImagePitch,
                    disparity_createParams->winWidth,
                    disparity_createParams->winHeight,
                    dispOutput + r*dstImagePitch,
                    minCostOutput + r*dstImagePitch,
                    natC_allCostOutput,
                    natC_allCostOutput,
                    imageWidth,
                    imageWidth,
                    disparity_createParams->numDisparities,
                    disparity_createParams->disparityStep
            );
        }
#endif
    }

    return 0;
}

