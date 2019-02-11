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
#include "harris_best_feature_to_front_config.h"
#pragma RESET_MISRA ("required")

uint32_t numTestCases;
sHarrisBestFeatureToFront_Config gConfig_harrisBestFeatureToFront[HARRIS_BFTF_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_harrisBestFeatureToFront[MAX_ITEMS_TO_PARSE] =
{
  {(char *)"numTestCases" ,            &numTestCases                                            , INT_32, SINGLE},
  {(char *)"testCaseName" ,            &gConfig_harrisBestFeatureToFront[0].testCaseName        , STRING, SINGLE},
  {(char* )"performanceTestcase" ,     &gConfig_harrisBestFeatureToFront[0].performanceTestcase , INT_8,  SINGLE},
  {(char *)"desc" ,                    &gConfig_harrisBestFeatureToFront[0].desc                , STRING, SINGLE},
  /* Test Case 0 */
  {(char  * )"numLevels",              &gConfig_harrisBestFeatureToFront[0].numLevels             , INT_8 , SINGLE},
  {(char  * )"maxNumFeaturesIn",       &gConfig_harrisBestFeatureToFront[0].maxNumFeaturesIn      , INT_16 , SINGLE},
  {(char  * )"bestNFeaturesOut",       &gConfig_harrisBestFeatureToFront[0].bestNFeaturesOut      , INT_16 , SINGLE},
  {(char  * )"harrisSensitivityParam", &gConfig_harrisBestFeatureToFront[0].sensitivityParam      , INT_16 , SINGLE},

  {(char  * )"inImage0",               &gConfig_harrisBestFeatureToFront[0].inImage[0]            , STRING, SINGLE},
  {(char  * )"inImage1",               &gConfig_harrisBestFeatureToFront[0].inImage[1]            , STRING, SINGLE},
  {(char  * )"inImage2",               &gConfig_harrisBestFeatureToFront[0].inImage[2]            , STRING, SINGLE},
  {(char  * )"inXyList0",              &gConfig_harrisBestFeatureToFront[0].inXyList[0]           , STRING, SINGLE},
  {(char  * )"inXyList1",              &gConfig_harrisBestFeatureToFront[0].inXyList[1]           , STRING, SINGLE},
  {(char  * )"inXyList2",              &gConfig_harrisBestFeatureToFront[0].inXyList[2]           , STRING, SINGLE},
  {(char  * )"srcImageWidth",          &gConfig_harrisBestFeatureToFront[0].srcImageWidth         , INT_16, MULTI},
  {(char  * )"srcImageHeight",         &gConfig_harrisBestFeatureToFront[0].srcImageHeight        , INT_16, MULTI},
  {(char  * )"srcImagePitch",          &gConfig_harrisBestFeatureToFront[0].srcImagePitch         , INT_16, MULTI},
  {(char  * )"xyListInDmem",           &gConfig_harrisBestFeatureToFront[0].xyListInDmem          ,  INT_8, SINGLE},
  {(char  * )"numPoints",              &gConfig_harrisBestFeatureToFront[0].numPoints             , INT_16, MULTI},
  {(char  * )"outXyList",              &gConfig_harrisBestFeatureToFront[0].outXyList             , STRING, SINGLE},
  {(char  * )"outLevelIds",            &gConfig_harrisBestFeatureToFront[0].outLevelIds           , STRING, SINGLE},
  {(char  * )"fileBased",              &gConfig_harrisBestFeatureToFront[0].fileBased             , INT_8 , SINGLE},
  {(char  * )"randSeed",               &gConfig_harrisBestFeatureToFront[0].randSeed              , INT_32, SINGLE}
  /* Test Case 1 */
} ;

