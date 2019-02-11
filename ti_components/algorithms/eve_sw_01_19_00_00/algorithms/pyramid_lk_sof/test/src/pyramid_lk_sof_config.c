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
#include "pyramid_lk_sof_config.h"
#pragma RESET_MISRA ("required")

#pragma DATA_SECTION (gsTokenMap_sof, ".fardata");
#pragma DATA_SECTION (gParams, ".fardata");

char * SOFKeyPointMethos[] =
{
  "SOF_EXTERNAL_KEY_POINTS",
  "SOF_HARRIS_KEY_POINTS  ",
  "SOF_FAST9_KEY_POINTS   ",
};

config_params gParams ;
sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inVideoSeqFile",            &(gParams.inVideoSeqFile)        , STRING, SINGLE},
  {(char* )"outVideoSeqFile",           &(gParams.outVideoSeqFile)       , STRING, SINGLE},
  {(char* )"currFrameFile",             &(gParams.currFrameFile)         , STRING, SINGLE},
  {(char* )"prevFrameFile",             &(gParams.prevFrameFile)         , STRING, SINGLE},
  {(char* )"gtFileName",                &(gParams.gtFileName)            , STRING, SINGLE},
  {(char* )"outFileName",               &(gParams.outFileName)           , STRING, SINGLE},
  {(char* )"refFileName",               &(gParams.refFileName)           , STRING, SINGLE},
  {(char* )"statsFileName",             &(gParams.statsFileName)         , STRING, SINGLE},
  {(char* )"outMetaDataDir",            &(gParams.outMetaDataDir)         , STRING, SINGLE},
  {(char* )"keyPointFile",              &(gParams.keyPointFile)          , STRING, SINGLE},
  {(char* )"maxNumKeyPoints",           &gParams.maxNumKeyPoints         , INT_32, SINGLE},
  {(char* )"maxPrevTrackPoints",        &gParams.maxPrevTrackPoints      , INT_32, SINGLE},
  {(char* )"numLevels",                 &gParams.numLevels               , INT_32, SINGLE},
  {(char* )"numLevelsPerCall",          &gParams.numLevelsPerCall        , INT_32, SINGLE},
  {(char* )"imWidth",                   &gParams.imWidth                 , INT_32, SINGLE},
  {(char* )"imHeight",                  &gParams.imHeight                , INT_32, SINGLE},
  {(char* )"roiWidth",                  &gParams.roiWidth                , INT_32, SINGLE},
  {(char* )"roiHeight",                 &gParams.roiHeight               , INT_32, SINGLE},
  {(char* )"startX",                    &gParams.startX                  , INT_32, SINGLE},
  {(char* )"startY",                    &gParams.startY                  , INT_32, SINGLE},
  {(char* )"harrisScaling",             &gParams.harrisScaling           , INT_32, SINGLE},
  {(char* )"nmsThreshold",              &gParams.nmsThreshold            , INT_32, SINGLE},
  {(char* )"harrisWindowSize",          &gParams.harrisWindowSize     , INT_8 , SINGLE},
  {(char* )"harrisScoreMethod",         &gParams.harrisScoreMethod    , INT_8 , SINGLE},
  {(char* )"suppressionMethod",         &gParams.suppressionMethod    , INT_8 , SINGLE},
  {(char* )"trackOffsetMethod",         &gParams.trackOffsetMethod    , INT_8 , SINGLE},
  {(char* )"keyPointDetectMethod",      &gParams.keyPointDetectMethod    , INT_8,  SINGLE},
  {(char* )"fast9Threshold",            &gParams.fast9Threshold          , INT_32, SINGLE},
  {(char* )"trackErrThr",               &gParams.trackErrThr             , INT_32, SINGLE},
  {(char* )"trackMinFlowQ4",            &gParams.trackMinFlowQ4          , INT_32, SINGLE},
  {(char* )"trackNmsWinSize",           &gParams.trackNmsWinSize         , INT_32, SINGLE},
  {(char* )"keyPointDetectInterval",    &gParams.keyPointDetectInterval  , INT_32, SINGLE},
  {(char* )"inPutType",                 &gParams.inPutType               , INT_32, SINGLE},
  {(char* )"startFrame",                &gParams.startFrame              , INT_32, SINGLE},
  {(char* )"numFrames",                 &gParams.numFrames               , INT_32, SINGLE},
  {(char* )"maxItersLK",                &gParams.maxItersLK[0]           , INT_32, MULTI},
  {(char* )"minErrValue",               &gParams.minErrValue[0]          , INT_32, MULTI},
  {(char* )"searchRange",               &gParams.searchRange[0]          , INT_32, MULTI},
  {(char *)"testCaseName",              &gParams.testCaseName            , STRING, SINGLE},
  {(char *)"testCaseDesc",              &gParams.testCaseDesc            , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gParams.performanceTestcase     , INT_8,  SINGLE},
} ;

void printConfigParams(config_params *params)
{
  int i;
  printf("currFrameFile          %s\n",params->currFrameFile );
  printf("prevFrameFile          %s\n",params->prevFrameFile );
  printf("gtFileName             %s\n",params->gtFileName    );
  printf("outFileName            %s\n",params->outFileName   );
  printf("statsFileName          %s\n",params->statsFileName );
  printf("keyPointFile           %s\n",params->keyPointFile );
  printf("maxNumKeyPoints        %d\n",params->maxNumKeyPoints );
  printf("maxPrevTrackPoints     %d\n",params->maxPrevTrackPoints);
  printf("numLevels              %d\n",params->numLevels    );
  printf("imWidth                %d\n",params->imWidth      );
  printf("imHeight               %d\n",params->imHeight     );
  printf("roiWidth               %d\n",params->roiWidth     );
  printf("roiHeight              %d\n",params->roiHeight    );
  printf("startX                 %d\n",params->startX       );
  printf("startY                 %d\n",params->startY       );
  printf("harrisScaling          %d\n",params->harrisScaling);
  printf("nmsThreshold           %d\n",params->nmsThreshold );
  printf("keyPointDetectMethod   %s\n",SOFKeyPointMethos[params->keyPointDetectMethod] );
  for(i = 0; i < params->numLevels; i++)
  {
    printf("minErrValue  %d  :         %d\n",i,params->minErrValue[i]  );
    printf("maxItersLK   %d  :         %d\n",i,params->maxItersLK[i]   );
    printf("searchRange  %d  :         %d\n",i,params->searchRange[i]   );
  }
}
