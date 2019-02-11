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

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "feature_plane_comp_config.h"
#pragma RESET_MISRA ("required")

uint32_t featurePlaneComp_numTestCases;
sFeaturePlaneComp_Config gConfig_featurePlaneComp[FEATURE_PLANE_COMP_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_featurePlaneComp[MAX_ITEMS_TO_PARSE] =
{
  {(char *)"numTestCases"       ,&featurePlaneComp_numTestCases                  , INT_32, SINGLE},
  {(char *)"fileBased"          ,&gConfig_featurePlaneComp[0].fileBased          , INT_8 , SINGLE},
  {(char *)"inImage"            ,&gConfig_featurePlaneComp[0].inImage            , STRING, SINGLE},
  {(char *)"outImage"           ,&gConfig_featurePlaneComp[0].outImage           , STRING, SINGLE},
  {(char *)"refImage"           ,&gConfig_featurePlaneComp[0].refImage           , STRING, SINGLE},
  {(char *)"srcImageWidth"      ,&gConfig_featurePlaneComp[0].srcImageWidth      , INT_16, SINGLE},
  {(char *)"srcImageHeight"     ,&gConfig_featurePlaneComp[0].srcImageHeight     , INT_16, SINGLE},
  {(char *)"srcImagePitch"      ,&gConfig_featurePlaneComp[0].srcImagePitch      , INT_16, SINGLE},
  {(char *)"cellSize"           ,&gConfig_featurePlaneComp[0].cellSize           , INT_16, SINGLE},
  {(char *)"blockSize"          ,&gConfig_featurePlaneComp[0].blockSize          , INT_16, SINGLE},
  {(char *)"blockOverlap"       ,&gConfig_featurePlaneComp[0].blockOverlap       , INT_16, SINGLE},
  {(char *)"sreachStep"         ,&gConfig_featurePlaneComp[0].sreachStep         , INT_16, SINGLE},
  {(char *)"scaleSteps"         ,&gConfig_featurePlaneComp[0].scaleSteps         , INT_16, SINGLE},
  {(char *)"numScales"          ,&gConfig_featurePlaneComp[0].numScales          , INT_16, SINGLE},
  {(char *)"enableFilter"       ,&gConfig_featurePlaneComp[0].enableFilter       , INT_16, SINGLE},
  {(char *)"enableContrastStretching" ,&gConfig_featurePlaneComp[0].enableContrastStretching, INT_16, SINGLE},
  {(char *)"extFilterParam"     ,&gConfig_featurePlaneComp[0].extFilterParam     , INT_8, SINGLE},
  {(char *)"numBins"            ,&gConfig_featurePlaneComp[0].numBins            , INT_16, SINGLE},
  {(char *)"gradientMethod"     ,&gConfig_featurePlaneComp[0].gradientMethod     , INT_16, SINGLE},
  {(char *)"enableGardMagPlane" ,&gConfig_featurePlaneComp[0].enableGardMagPlane , INT_8, SINGLE},
  {(char *)"enableCellSum"      ,&gConfig_featurePlaneComp[0].enableCellSum      , INT_8, SINGLE},
  {(char *)"enableYPlane"       ,&gConfig_featurePlaneComp[0].enableYPlane       , INT_8, SINGLE},
  {(char *)"enableUVPlane"      ,&gConfig_featurePlaneComp[0].enableUVPlane      , INT_8, SINGLE},
  {(char *)"startFrame"         ,&gConfig_featurePlaneComp[0].startFrame         , INT_32, SINGLE},
  {(char *)"numFrames"          ,&gConfig_featurePlaneComp[0].numFrames          , INT_32, SINGLE},
  {(char *)"outFormat"          ,&gConfig_featurePlaneComp[0].outFormat          , INT_8 , SINGLE},
  {(char *)"testCaseName"       ,&gConfig_featurePlaneComp[0].testCaseName       , STRING, SINGLE},
  {(char *)"testCaseDesc"       ,&gConfig_featurePlaneComp[0].testCaseDesc       , STRING, SINGLE},
  {(char* )"performanceTestcase",&gConfig_featurePlaneComp[0].performanceTestcase, INT_8,  SINGLE},
  {(char* )"RoiSelectionMethod", &gConfig_featurePlaneComp[0].RoiSelectionMethod , INT_8,  SINGLE},
  {(char *)"RoiCenterX"         ,&gConfig_featurePlaneComp[0].RoiCenterX         , INT_16, SINGLE},
  {(char *)"RoiCenterY"         ,&gConfig_featurePlaneComp[0].RoiCenterY         , INT_16, SINGLE},
  {(char *)"RoiWidth"           ,&gConfig_featurePlaneComp[0].RoiWidth           , INT_16, SINGLE},
  {(char *)"RoiHeight"          ,&gConfig_featurePlaneComp[0].RoiHeight          , INT_16, SINGLE},
  {(char *)"scaleParams"        ,gConfig_featurePlaneComp[0].scaleParams         , INT_16, MULTI},
  {(char *)"scaleRatioQ12"      ,&gConfig_featurePlaneComp[0].scaleRatioQ12      , INT_16, MULTI},

} ;

