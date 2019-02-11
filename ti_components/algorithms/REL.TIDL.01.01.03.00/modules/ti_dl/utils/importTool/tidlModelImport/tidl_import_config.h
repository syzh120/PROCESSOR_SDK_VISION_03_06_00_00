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


#ifndef _EVELIB_YUV_SCALAR_CONFIG_H_
#define _EVELIB_YUV_SCALAR_CONFIG_H_

#include "configparser.h"
#include "ti_dl.h"

#define FILE_NAME_SIZE  (256)

typedef struct
{
    int32_t  randParams;
    int32_t  modelType;
    int32_t  quantizationStyle;
    int32_t  quantRoundAdd;
    int32_t  numParamBits;
    int32_t  rawSampleInData;
    int32_t  numSampleInData;
    int32_t  foldBnInConv2D;
    int32_t  preProcType;
    int32_t  inElementType;
    int32_t  inQuantFactor;
    /* Parameters to overwrite the proto txt first feature dimension */
    int32_t  inWidth; 
    int32_t  inHeight; 
    int32_t  inNumChannels;
    uint8_t  sampleInData[FILE_NAME_SIZE];
    uint8_t  tidlStatsTool[FILE_NAME_SIZE];
    uint8_t  inputNetFile[FILE_NAME_SIZE];
    uint8_t  inputParamsFile[FILE_NAME_SIZE];
    uint8_t  outputNetFile[FILE_NAME_SIZE];
    uint8_t  outputParamsFile[FILE_NAME_SIZE];
    uint8_t  configLine[FILE_NAME_SIZE];
    uint8_t  configParam[FILE_NAME_SIZE];
    int32_t  layersGroupId[TIDL_NUM_MAX_LAYERS];
    int32_t  conv2dKernelType[TIDL_NUM_MAX_LAYERS];
} tidl_import_config;

extern tidl_import_config gParams;
extern sTokenMapping gsTokenMap_tidl_import_config[MAX_ITEMS_TO_PARSE];

#endif /* _EVELIB_YUV_SCALAR_CONFIG_H_*/
