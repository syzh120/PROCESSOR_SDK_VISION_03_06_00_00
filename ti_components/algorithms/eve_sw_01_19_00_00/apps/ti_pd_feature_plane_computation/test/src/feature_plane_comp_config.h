/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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


#ifndef FEATURE_PLANE_COMP_CONFIG_H_
#define FEATURE_PLANE_COMP_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "iti_pd_feature_plane_computation_ti.h"

#define FILE_NAME_SIZE  (256)
#define FEATURE_PLANE_COMP_NUM_MAX_TESTCASES 20
#define MAX_SCALE_STEPS (8)

typedef struct
{
    uint8_t inImage[FILE_NAME_SIZE];
    uint8_t outImage[FILE_NAME_SIZE];
    uint8_t refImage[FILE_NAME_SIZE];
    uint8_t testCaseName[FILE_NAME_SIZE];
    uint8_t testCaseDesc[FILE_NAME_SIZE];
    uint16_t srcImageWidth;
    uint16_t srcImageHeight;
    uint16_t srcImagePitch;
    uint32_t startFrame;
    uint32_t numFrames;
    uint8_t fileBased;
    uint16_t cellSize;
    uint16_t blockSize;
    uint16_t blockOverlap;
    uint16_t sreachStep;
    uint16_t scaleSteps;
    uint16_t numScales;
    uint16_t enableFilter;
    uint16_t enableContrastStretching;
    uint8_t extFilterParam;
    uint16_t numBins;
    uint16_t gradientMethod;
    uint8_t enableGardMagPlane;
    uint8_t enableCellSum;
    uint8_t enableYPlane;
    uint8_t enableUVPlane;
    uint8_t outFormat;
    uint8_t performanceTestcase ;
    uint8_t RoiSelectionMethod;
    uint16_t RoiCenterX;
    uint16_t RoiCenterY;
    uint16_t RoiWidth  ;
    uint16_t RoiHeight ;
    uint16_t scaleRatioQ12[MAX_SCALE_STEPS];
    uint16_t scaleParams[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES*5];
} sFeaturePlaneComp_Config;

extern uint32_t featurePlaneComp_numTestCases;
extern sFeaturePlaneComp_Config gConfig_featurePlaneComp[FEATURE_PLANE_COMP_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_featurePlaneComp[MAX_ITEMS_TO_PARSE];

#endif /*FEATURE_PLANE_COMP_CONFIG_H_*/

