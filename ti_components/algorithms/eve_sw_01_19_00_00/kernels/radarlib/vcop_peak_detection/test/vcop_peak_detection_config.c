/*
*
* Copyright (c) 2016-2017 Texas Instruments Incorporated
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


#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_peak_detection_config.h"

sPeak_detection_Config gConfig_Peak_detection;
sTokenMapping gsTokenMap_Peak_detection[] =
{
  {(char* )"inputData",               &gConfig_Peak_detection.inputData, STRING, SINGLE},
  {(char* )"outData",                 &gConfig_Peak_detection.outData, STRING, SINGLE},
  {(char* )"inputEnergy",             &gConfig_Peak_detection.inputEnergy, STRING, SINGLE},
  {(char* )"numTx",                   &gConfig_Peak_detection.numTx, INT_16, SINGLE},
  {(char* )"numRx",                   &gConfig_Peak_detection.numRx, INT_16, SINGLE},
  {(char* )"numHorzPtPerAntenna",     &gConfig_Peak_detection.numHorzPtPerAntenna, INT_16, SINGLE},
  {(char* )"numRows",                 &gConfig_Peak_detection.numRows, INT_16, SINGLE},
  {(char* )"pitch",                   &gConfig_Peak_detection.pitch, INT_16, SINGLE},
  {(char* )"offsetBwTx",              &gConfig_Peak_detection.offsetBwTx, INT_16, SINGLE},
  {(char* )"offsetBwRx",              &gConfig_Peak_detection.offsetBwRx, INT_16, SINGLE},
  {(char* )"lutQFormat",              &gConfig_Peak_detection.lutQFormat, INT_8, SINGLE},
  {(char* )"alphaQFormat",            &gConfig_Peak_detection.alphaQFormat, INT_8, SINGLE},
  {(char* )"noiseLen",                &gConfig_Peak_detection.noiseLen, INT_16, SINGLE},
  {(char* )"gaurdLen",                &gConfig_Peak_detection.gaurdLen, INT_16, SINGLE},
  {(char* )"const1",                  &gConfig_Peak_detection.const1, INT_16, SINGLE},
  {(char* )"const2",                  &gConfig_Peak_detection.const2, INT_16, SINGLE},
  {(char* )"dopplerIdxOffset",        &gConfig_Peak_detection.dopplerIdxOffset, INT_16, SINGLE},
  {(char* )"vertCoordinateShift",     &gConfig_Peak_detection.vertCoordinateShift, INT_16, SINGLE},
  {(char* )"testType",                &gConfig_Peak_detection.testType, INT_8, SINGLE},
  {(char* )"randSeed",                &gConfig_Peak_detection.randSeed     , INT_32, SINGLE},
  {(char *)"testCaseName",            &gConfig_Peak_detection.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase",     &gConfig_Peak_detection.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc",                    &gConfig_Peak_detection.desc                 , STRING, SINGLE},
} ;

