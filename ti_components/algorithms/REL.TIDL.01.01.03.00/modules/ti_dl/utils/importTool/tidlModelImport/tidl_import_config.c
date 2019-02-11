/*
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the  
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "tidl_import_config.h"
#pragma RESET_MISRA ("required")


tidl_import_config gParams;

sTokenMapping gsTokenMap_tidl_import_config[MAX_ITEMS_TO_PARSE] =
{
        {(char* )"randParams",             &gParams.randParams            , INT_32, SINGLE},
        {(char *)"modelType",              &gParams.modelType             , INT_32, SINGLE},
        {(char *)"quantizationStyle",      &gParams.quantizationStyle     , INT_32, SINGLE},
        {(char *)"quantRoundAdd",          &gParams.quantRoundAdd         , INT_32, SINGLE},
        {(char *)"numParamBits",           &gParams.numParamBits          , INT_32, SINGLE},
        {(char *)"preProcType",            &gParams.preProcType           , INT_32, SINGLE},
        {(char *)"inElementType",          &gParams.inElementType         , INT_32, SINGLE},
        {(char *)"inQuantFactor",          &gParams.inQuantFactor         , INT_32, SINGLE},
        {(char *)"rawSampleInData",        &gParams.rawSampleInData       , INT_32, SINGLE},
        {(char *)"numSampleInData",        &gParams.numSampleInData       , INT_32, SINGLE},
        {(char *)"foldBnInConv2D",         &gParams.foldBnInConv2D        , INT_32, SINGLE},
        {(char *)"inWidth",                &gParams.inWidth               , INT_32, SINGLE},
        {(char *)"inHeight",               &gParams.inHeight              , INT_32, SINGLE},
        {(char *)"inNumChannels",          &gParams.inNumChannels         , INT_32, SINGLE},
        {(char *)"sampleInData",           &gParams.sampleInData          , STRING, SINGLE},
        {(char *)"tidlStatsTool",          &gParams.tidlStatsTool         , STRING, SINGLE},
        {(char *)"inputNetFile",           &gParams.inputNetFile          , STRING, SINGLE},
        {(char *)"inputParamsFile",        &gParams.inputParamsFile       , STRING, SINGLE},
        {(char *)"outputNetFile",          &gParams.outputNetFile         , STRING, SINGLE},
        {(char *)"outputParamsFile",       &gParams.outputParamsFile      , STRING, SINGLE},
        {(char *)"conv2dKernelType",       &gParams.conv2dKernelType[0]   , INT_32, MULTI},
        {(char* )"layersGroupId",          &gParams.layersGroupId[0]      , INT_32, MULTI}
} ;





