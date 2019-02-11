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
#pragma RESET_MISRA ("required")

#include "fft_config.h"

sFFT_Config gConfig_fft;
sTokenMapping gsTokenMap_fft[] =
{
  {(char* )"testCaseName",              &gConfig_fft.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gConfig_fft.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                      &gConfig_fft.desc                   , STRING, SINGLE},
  {(char* )"requirementId",             &gConfig_fft.requirementId          , STRING, SINGLE},
  {(char* )"inputData",                 &gConfig_fft.inputData                , STRING, SINGLE},
  {(char* )"outputData",                &gConfig_fft.outputData               , STRING, SINGLE},
  {(char* )"winCoefficients",           &gConfig_fft.winCoefficients, STRING, SINGLE},
  {(char* )"dopplerCorrectionCoefficients",&gConfig_fft.dopplerCorrectionCoefficients, STRING, SINGLE},
  {(char* )"outputContainerFormat",     &gConfig_fft.outputContainerFormat, INT_8, SINGLE},
  {(char* )"numPoints",                 &gConfig_fft.numPoints,  INT_16, SINGLE},
  {(char* )"numLines",                  &gConfig_fft.numLines, INT_16, SINGLE},
  {(char* )"numAntennas",               &gConfig_fft.numAntennas, INT_16, SINGLE},
  {(char* )"numPointsZeroPadding",      &gConfig_fft.numPointsZeroPadding, INT_16, SINGLE},
  {(char* )"numChunks",                 &gConfig_fft.numChunks, INT_8, SINGLE},
  {(char* )"fftDirection",              &gConfig_fft.fftDirection,  INT_8, SINGLE},
  {(char* )"enableDcoffset",            &gConfig_fft.enableDcoffset,  INT_8, SINGLE},
  {(char* )"enableWindowing",           &gConfig_fft.enableWindowing,  INT_8, SINGLE},
  {(char* )"enableInterferenceZeroOut", &gConfig_fft.enableInterferenceZeroOut,  INT_8, SINGLE},
  {(char* )"enableDopplerCorrection",   &gConfig_fft.enableDopplerCorrection,  INT_8, SINGLE},
  {(char* )"enableOverFlowDetection",   &gConfig_fft.enableOverFlowDetection,  INT_8, SINGLE},
  {(char* )"enable32bitsIntermResults", &gConfig_fft.enable32bitsIntermResults,  INT_8, SINGLE},
  {(char* )"inDataRange",               &gConfig_fft.inDataRange,  INT_8, SINGLE},
  {(char* )"numValidBits",              &gConfig_fft.numValidBits,  INT_8, SINGLE},
  {(char* )"windowingScaleFactor",      &gConfig_fft.windowingScaleFactor,  INT_16, SINGLE},
  {(char* )"irregularityFrequency",     &gConfig_fft.irregularityFrequency,  INT_16, SINGLE},
  {(char* )"offsetBwAntenna",           &gConfig_fft.offsetBwAntenna,  INT_16, SINGLE},
  {(char* )"offsetBwAntenna1",          &gConfig_fft.offsetBwAntenna1,  INT_16, SINGLE},
  {(char* )"dopplerCorrectionScaleFactor",&gConfig_fft.dopplerCorrectionScaleFactor,  INT_16, SINGLE},
  {(char* )"scaleFactors",              &gConfig_fft.scaleFactors,  INT_16, MULTI},
  {(char* )"interferenceThreshold",     &gConfig_fft.interferenceThreshold,  INT_16, SINGLE},
  {(char* )"dopplerOutputPitch",        &gConfig_fft.dopplerOutputPitch,  INT_32, SINGLE },
  {(char* )"randSeed",                  &gConfig_fft.randSeed       , INT_32, SINGLE}
} ;

