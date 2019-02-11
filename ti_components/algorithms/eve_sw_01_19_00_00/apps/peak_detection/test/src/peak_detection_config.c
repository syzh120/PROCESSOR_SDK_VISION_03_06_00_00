/*
*
* Copyright (c) 2017 Texas Instruments Incorporated
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

#include "peak_detection_config.h"

sPEAK_DETECTION_Config gConfig_peak_detection;
sTokenMapping gsTokenMap_peak_detection[] =
{
  {(char* )"testCaseName",              &gConfig_peak_detection.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gConfig_peak_detection.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                      &gConfig_peak_detection.desc                   , STRING, SINGLE},
  {(char* )"requirementId",             &gConfig_peak_detection.requirementId          , STRING, SINGLE},
  {(char* )"antennaData",               &gConfig_peak_detection.antennaData, STRING, SINGLE},
  {(char* )"rangeDopplerList",          &gConfig_peak_detection.rangeDopplerList, STRING, SINGLE},
  {(char* )"energyList",                &gConfig_peak_detection.energyList, STRING, SINGLE},
  {(char* )"numHorzPtPerAntenna",       &gConfig_peak_detection.numHorzPtPerAntenna,  INT_16, SINGLE},
  {(char* )"numTx",                     &gConfig_peak_detection.numTx,  INT_16, SINGLE},
  {(char* )"numRx",                     &gConfig_peak_detection.numRx,  INT_16, SINGLE},
  {(char* )"rangeDim",                  &gConfig_peak_detection.rangeDim, INT_16, SINGLE},
  {(char* )"dopplerDim",                &gConfig_peak_detection.dopplerDim, INT_16, SINGLE},
  {(char* )"offsetBwTx",                &gConfig_peak_detection.offsetBwTx, INT_16, SINGLE},
  {(char* )"offsetBwRx",                &gConfig_peak_detection.offsetBwRx, INT_16, SINGLE},
  {(char* )"noiseLen",                  &gConfig_peak_detection.noiseLen, INT_16, SINGLE},
  {(char* )"gaurdLen",                  &gConfig_peak_detection.gaurdLen,  INT_16, SINGLE},
  {(char* )"const1",                    &gConfig_peak_detection.const1,  INT_16, SINGLE},
  {(char* )"const2",                    &gConfig_peak_detection.const2,  INT_16, SINGLE},
  {(char* )"detectionMethod",           &gConfig_peak_detection.detectionMethod,  INT_8, SINGLE},
  {(char* )"enableTxDecoding",          &gConfig_peak_detection.enableTxDecoding,  INT_8, SINGLE},
  {(char* )"enableAntennaDataOut",      &gConfig_peak_detection.enableAntennaDataOut,  INT_8, SINGLE},
  {(char *)"txDecodingCoeff",           &gConfig_peak_detection.txDecodingCoeff, INT_16, MULTI},
  {(char* )"randSeed",                  &gConfig_peak_detection.randSeed       , INT_32, SINGLE}
} ;

