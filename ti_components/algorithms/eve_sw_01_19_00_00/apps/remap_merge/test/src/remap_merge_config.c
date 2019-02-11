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
#include "remap_merge_config.h"
#pragma RESET_MISRA ("required")

uint16_t remapMerge_numTestCases;
sRemapMerge_Config gConfig_remapMerge[REMAP_MERGE_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_remapMerge[] =
{
  {(char *)"numTestCases"         ,&remapMerge_numTestCases                    , INT_16, SINGLE},
  {(char *)"testCaseName"         ,&gConfig_remapMerge[0].testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase"  ,&gConfig_remapMerge[0].performanceTestcase  , INT_8,  SINGLE},
  {(char *)"inImage"              ,&gConfig_remapMerge[0].inImage              , STRING, SINGLE},
  {(char *)"outImage"             ,&gConfig_remapMerge[0].outImage             , STRING, SINGLE},
  {(char *)"refImage"             ,&gConfig_remapMerge[0].refImage             , STRING, SINGLE},
  {(char *)"coordMapList"         ,&gConfig_remapMerge[0].coordMapList         , INT_8 , SINGLE},
  {(char *)"isSrcMapFloat"        ,&gConfig_remapMerge[0].isSrcMapFloat        , INT_8 , SINGLE},
  {(char *)"srcFormat"            ,&gConfig_remapMerge[0].srcFormat            , INT_8 , SINGLE},
  {(char *)"dstFormat"            ,&gConfig_remapMerge[0].dstFormat            , INT_8 , SINGLE},
  {(char *)"srcStride"            ,&gConfig_remapMerge[0].srcStride            , INT_32, SINGLE},
  {(char *)"srcHeight"            ,&gConfig_remapMerge[0].srcHeight            , INT_32, SINGLE},
  {(char *)"dstStride"            ,&gConfig_remapMerge[0].dstStride            , INT_32, SINGLE},
  {(char *)"roiWidth"             ,&gConfig_remapMerge[0].roiWidth             , INT_32, SINGLE},
  {(char *)"roiHeight"            ,&gConfig_remapMerge[0].roiHeight            , INT_32, SINGLE},
  {(char *)"blockWidthBB"         ,&gConfig_remapMerge[0].blockWidthBB         , INT_16, SINGLE},
  {(char *)"blockHeightBB"        ,&gConfig_remapMerge[0].blockHeightBB        , INT_16, SINGLE},
  {(char *)"blockWidthTile"       ,&gConfig_remapMerge[0].blockWidthTile       , INT_16, SINGLE},
  {(char *)"blockHeightTile"      ,&gConfig_remapMerge[0].blockHeightTile      , INT_16, SINGLE},
  {(char *)"tileWidth"            ,&gConfig_remapMerge[0].tileWidth            , INT_16, SINGLE},
  {(char *)"tileHeight"           ,&gConfig_remapMerge[0].tileHeight           , INT_16, SINGLE},
  {(char *)"enableMerge"          ,&gConfig_remapMerge[0].enableMerge          , INT_8 , SINGLE},
  {(char *)"remapApproach"        ,&gConfig_remapMerge[0].remapApproach        , INT_8 , SINGLE},
  {(char *)"interpolationLuma"    ,&gConfig_remapMerge[0].interpolationLuma    , INT_8 , SINGLE},
  {(char *)"interpolationChroma"  ,&gConfig_remapMerge[0].interpolationChroma  , INT_8 , SINGLE},
  {(char *)"mapQshift"            ,&gConfig_remapMerge[0].mapQshift            , INT_8 , SINGLE},
  {(char *)"rightShift"           ,&gConfig_remapMerge[0].rightShift           , INT_8 , SINGLE},
  {(char *)"sat_high"             ,&gConfig_remapMerge[0].sat_high             , INT_32, SINGLE},
  {(char *)"sat_high_set"         ,&gConfig_remapMerge[0].sat_high_set         , INT_32, SINGLE},
  {(char *)"sat_low"              ,&gConfig_remapMerge[0].sat_low              , INT_32, SINGLE},
  {(char *)"sat_low_set"          ,&gConfig_remapMerge[0].sat_low_set          , INT_32, SINGLE},
  {(char *)"desc"                 ,&gConfig_remapMerge[0].desc                 , STRING, SINGLE},
} ;

