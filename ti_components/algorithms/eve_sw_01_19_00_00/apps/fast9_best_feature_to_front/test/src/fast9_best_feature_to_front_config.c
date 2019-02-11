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
#include "fast9_best_feature_to_front_config.h"
#pragma RESET_MISRA ("required")

uint32_t numTestCases;
sFast9BestFeatureToFront_Config gConfig_Fast9BestFeatureToFront[FAST9_BFTF_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_Fast9BestFeatureToFront[MAX_ITEMS_TO_PARSE] =
{
  {(char *)"numTestCases" ,           &numTestCases                                           , INT_32, SINGLE},
  {(char *)"testCaseName" ,           &gConfig_Fast9BestFeatureToFront[0].testCaseName        , STRING, SINGLE},
  {(char* )"performanceTestcase" ,    &gConfig_Fast9BestFeatureToFront[0].performanceTestcase , INT_8,  SINGLE},
  {(char *)"desc" ,                   &gConfig_Fast9BestFeatureToFront[0].desc                , STRING, SINGLE},

  /* Test Case 0 */
  {(char *)"fileBased",               &gConfig_Fast9BestFeatureToFront[0].fileBased        , INT_8, SINGLE},
  {(char *)"numLevels",               &gConfig_Fast9BestFeatureToFront[0].numLevels        , INT_8, SINGLE},
  {(char *)"fast9threshold",          &gConfig_Fast9BestFeatureToFront[0].fast9threshold   , INT_8,  SINGLE},
  {(char *)"XYInDmem",                &gConfig_Fast9BestFeatureToFront[0].XYInDmem         , INT_8, SINGLE},
  {(char *)"writeOutput",             &gConfig_Fast9BestFeatureToFront[0].writeOutput      , INT_8, SINGLE},
  {(char *)"maxFeatures",             &gConfig_Fast9BestFeatureToFront[0].maxFeatures      , INT_16, SINGLE},
  {(char *)"maxbestNFeatures",        &gConfig_Fast9BestFeatureToFront[0].maxbestNFeatures , INT_16, SINGLE},
  {(char *)"suppressionMethod",       &gConfig_Fast9BestFeatureToFront[0].suppressionMethod, INT_8, SINGLE},

  {(char *)"inImage0",               &gConfig_Fast9BestFeatureToFront[0].inImage[0]       , STRING, SINGLE},
  {(char *)"inImage1",               &gConfig_Fast9BestFeatureToFront[0].inImage[1]       , STRING, SINGLE},
  {(char *)"inImage2",               &gConfig_Fast9BestFeatureToFront[0].inImage[2]       , STRING, SINGLE},
  {(char *)"inXYList0",              &gConfig_Fast9BestFeatureToFront[0].inXYList[0]      , STRING, SINGLE},
  {(char *)"inXYList1",              &gConfig_Fast9BestFeatureToFront[0].inXYList[1]      , STRING, SINGLE},
  {(char *)"inXYList2",              &gConfig_Fast9BestFeatureToFront[0].inXYList[2]      , STRING, SINGLE},
  {(char *)"outImage0",              &gConfig_Fast9BestFeatureToFront[0].outXY[0]         , STRING, SINGLE},
  {(char *)"outImage1",              &gConfig_Fast9BestFeatureToFront[0].outXY[1]         , STRING, SINGLE},
  {(char *)"outImage2",              &gConfig_Fast9BestFeatureToFront[0].outXY[2]         , STRING, SINGLE},
  {(char *)"srcImageWidth",          &gConfig_Fast9BestFeatureToFront[0].srcImageWidth    , INT_16, MULTI},
  {(char *)"srcImageHeight",         &gConfig_Fast9BestFeatureToFront[0].srcImageHeight   , INT_16, MULTI},
  {(char *)"total_features",         &gConfig_Fast9BestFeatureToFront[0].total_features   , INT_16, MULTI},
  {(char *)"bestNFeatures",          &gConfig_Fast9BestFeatureToFront[0].bestNFeatures    , INT_16, MULTI},

  /* Test Case 1 */
} ;
