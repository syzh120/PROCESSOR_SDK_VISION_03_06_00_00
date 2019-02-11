/*
 
Copyright (c) [2015] – [2017] Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI ("TI Devices").  No hardware patent is licensed hereunder.
 
Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution
 
Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:
 
*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.
 
*       any redistribution and use are licensed by TI for use only with TI Devices.
 
*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
 
If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:
 
*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.
 
*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.
 
Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.
 
DISCLAIMER.
 
THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "clr_config.h"
#pragma RESET_MISRA ("required")

uint32_t clr_numTestCases;
sCLR_Config gConfig_CLR[CLR_NUM_MAX_TESTCASES];


sTokenMapping gsTokenMap_CLR[] =
{
  {(char *)"numTestCases"          ,&clr_numTestCases                         , INT_32, SINGLE},
  {(char *)"inFileNameYUV"         ,&gConfig_CLR[0].inFileNameYUV             , STRING, SINGLE},
  {(char *)"outFileName"           ,&gConfig_CLR[0].outFileName               , STRING, SINGLE},
  {(char *)"outFileNameYUV"        ,&gConfig_CLR[0].outFileNameYUV            , STRING, SINGLE},
  {(char *)"traceNameYUV"          ,&gConfig_CLR[0].traceNameYUV              , STRING, SINGLE},
  {(char *)"maxImageWidth"         ,&gConfig_CLR[0].maxImageWidth             , INT_16, SINGLE},
  {(char *)"maxImageHeight"        ,&gConfig_CLR[0].maxImageHeight            , INT_16, SINGLE},
  {(char *)"actualImgWidth"        ,&gConfig_CLR[0].actualImgWidth            , INT_16, SINGLE},
  {(char *)"actualImgHeight"       ,&gConfig_CLR[0].actualImgHeight           , INT_16, SINGLE},
  {(char *)"maxFrames"             ,&gConfig_CLR[0].maxFrames                 , INT_16, SINGLE},
  {(char *)"startFrame"            ,&gConfig_CLR[0].startFrame                 , INT_16, SINGLE},
  {(char* )"roiWidth"              ,&gConfig_CLR[0].roiWidth                  , INT_16, SINGLE},
  {(char* )"roiHeight"             ,&gConfig_CLR[0].roiHeight                 , INT_16, SINGLE},
  {(char* )"startX"                ,&gConfig_CLR[0].startX                    , INT_16, SINGLE},
  {(char* )"startY"                ,&gConfig_CLR[0].startY                    , INT_16, SINGLE},
  {(char *)"maxNumRadius"          ,&gConfig_CLR[0].maxNumRadius              , INT_8 , SINGLE},
  {(char *)"numRadius"             ,&gConfig_CLR[0].numRadius                 , INT_8 , SINGLE},
  {(char *)"trackingMethod"        ,&gConfig_CLR[0].trackingMethod            , INT_8 , SINGLE},
  {(char *)"groupingWindowSize"    ,&gConfig_CLR[0].groupingWindowSize        , INT_16 , SINGLE}, 
  {(char *)"morphologyMethod"      ,&gConfig_CLR[0].morphologyMethod          , INT_8 , SINGLE}, 
  {(char *)"lightSelection"        ,&gConfig_CLR[0].lightSelection            , INT_8 , SINGLE}, 
  {(char *)"useCacheForList"       ,&gConfig_CLR[0].useCacheForList           , INT_8 , SINGLE}, 
  {(char *)"lightBrightnessThr"    ,&gConfig_CLR[0].lightBrightnessThr[0]     , INT_8 , MULTI},
  {(char *)"lightColor"            ,&gConfig_CLR[0].lightColor[0]             , INT_8 , MULTI},
  {(char *)"lightThr1"             ,&gConfig_CLR[0].lightThr1[0]              , INT_8 , MULTI},
  {(char *)"lightThr2"             ,&gConfig_CLR[0].lightThr2[0]              , INT_8 , MULTI},
  {(char *)"circleDetectionThr"    ,&gConfig_CLR[0].circleDetectionThr[0]     , INT_16 , MULTI},
  {(char *)"radius"                ,&gConfig_CLR[0].radius[0]                 , INT_16 , MULTI},
  {(char *)"scalingFactor"         ,&gConfig_CLR[0].scalingFactor[0]          , INT_16 , MULTI},
  {(char *)"falseFilterThr"        ,&gConfig_CLR[0].falseFilterThr[0]          , INT_32 , MULTI},
} ;

