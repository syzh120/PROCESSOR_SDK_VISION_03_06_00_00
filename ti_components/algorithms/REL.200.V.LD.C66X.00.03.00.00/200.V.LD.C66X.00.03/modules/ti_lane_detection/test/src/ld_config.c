/*
* module name       :TI Lane Detection 
*
* module descripton :Lane Detection and departure warning using TI’s C66x DSP
*
*/
/*
 
Copyright (c) [2014] – [2017] Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.
 
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
#include "ld_config.h"
#pragma RESET_MISRA ("required")

uint32_t ld_numTestCases;
sLD_Config gConfig_LD[LD_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_LD[] =
{
  {(char *)"numTestCases"             ,&ld_numTestCases                         , INT_32, SINGLE},
  {(char *)"inFileName"               ,&gConfig_LD[0].inFileName                , STRING, SINGLE},
  {(char *)"outFileName"              ,&gConfig_LD[0].outFileName               , STRING, SINGLE},
  {(char *)"maxImageWidth"            ,&gConfig_LD[0].maxImageWidth             , INT_16, SINGLE},
  {(char *)"maxImageHeight"           ,&gConfig_LD[0].maxImageHeight            , INT_16, SINGLE},
  {(char *)"actualImgWidth"           ,&gConfig_LD[0].actualImgWidth            , INT_16, SINGLE},
  {(char *)"actualImgHeight"          ,&gConfig_LD[0].actualImgHeight           , INT_16, SINGLE},
  {(char *)"maxFrames"                ,&gConfig_LD[0].maxFrames                 , INT_16, SINGLE},
  {(char* )"roiWidth"                 ,&gConfig_LD[0].roiWidth                  , INT_16, SINGLE},
  {(char* )"roiHeight"                ,&gConfig_LD[0].roiHeight                 , INT_16, SINGLE},
  {(char* )"startX"                   ,&gConfig_LD[0].startX                    , INT_16, SINGLE},
  {(char* )"startY"                   ,&gConfig_LD[0].startY                    , INT_16, SINGLE},
  {(char *)"cannyHiThresh"            ,&gConfig_LD[0].cannyHiThresh             , INT_8 , SINGLE},
  {(char *)"cannyLoThresh"            ,&gConfig_LD[0].cannyLoThresh             , INT_8 , SINGLE},
  {(char *)"houghNmsThresh"           ,&gConfig_LD[0].houghNmsThresh            , INT_8 , SINGLE},
  {(char *)"maxRho"                   ,&gConfig_LD[0].maxRho                    , INT_16, SINGLE},
  {(char *)"startThetaLeft"           ,&gConfig_LD[0].startThetaLeft            , INT_16, SINGLE},
  {(char *)"endThetaLeft"             ,&gConfig_LD[0].endThetaLeft              , INT_16, SINGLE},
  {(char *)"startThetaRight"          ,&gConfig_LD[0].startThetaRight           , INT_16, SINGLE},
  {(char *)"endThetaRight"            ,&gConfig_LD[0].endThetaRight             , INT_16, SINGLE},
  {(char *)"thetaStepSize"            ,&gConfig_LD[0].thetaStepSize             , INT_8 , SINGLE},
  {(char *)"trackMethod"              ,&gConfig_LD[0].trackMethod               , INT_8 , SINGLE},
  {(char *)"enableWarning"            ,&gConfig_LD[0].enableWarning             , INT_8 , SINGLE},
  {(char *)"numHoughMaximasDet"       ,&gConfig_LD[0].numHoughMaximasDet        , INT_8 , SINGLE},
  {(char *)"numHoughMaximasTrack"     ,&gConfig_LD[0].numHoughMaximasTrack      , INT_8 , SINGLE},
  {(char *)"departThetaLeftMin"       ,&gConfig_LD[0].departThetaLeftMin        , INT_16, SINGLE},
  {(char *)"departThetaLeftMax"       ,&gConfig_LD[0].departThetaLeftMax        , INT_16, SINGLE},
  {(char *)"departRhoLeftMin"         ,&gConfig_LD[0].departRhoLeftMin          , INT_16, SINGLE},
  {(char *)"departRhoLeftMax"         ,&gConfig_LD[0].departRhoLeftMax          , INT_16, SINGLE},
  {(char *)"departThetaRightMin"      ,&gConfig_LD[0].departThetaRightMin       , INT_16, SINGLE},
  {(char *)"departThetaRightMax"      ,&gConfig_LD[0].departThetaRightMax       , INT_16, SINGLE},
  {(char *)"departRhoRightMin"        ,&gConfig_LD[0].departRhoRightMin         , INT_16, SINGLE},
  {(char *)"departRhoRightMax"        ,&gConfig_LD[0].departRhoRightMax         , INT_16, SINGLE},
  {(char *)"visType"                  ,&gConfig_LD[0].visType                   , INT_8 , SINGLE},
} ;

