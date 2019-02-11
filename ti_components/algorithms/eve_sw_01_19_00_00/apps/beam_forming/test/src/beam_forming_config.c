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

#include "beam_forming_config.h"

sBEAM_FORMING_Config gConfig_beam_forming;
sTokenMapping gsTokenMap_beam_forming[] =
{
  {(char* )"testCaseName",              &gConfig_beam_forming.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gConfig_beam_forming.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                      &gConfig_beam_forming.desc                   , STRING, SINGLE},
  {(char* )"requirementId",             &gConfig_beam_forming.requirementId          , STRING, SINGLE},
  {(char* )"antennaData",               &gConfig_beam_forming.antennaData, STRING, SINGLE},
  {(char* )"steeringMatrix",            &gConfig_beam_forming.steeringMatrix, STRING, SINGLE},
  {(char* )"coordinateBuf",             &gConfig_beam_forming.coordinateBuf, STRING, SINGLE},
  {(char* )"numAngles",                 &gConfig_beam_forming.numAngles,  INT_16, SINGLE},
  {(char* )"numAntennas",               &gConfig_beam_forming.numAntennas, INT_16, SINGLE},
  {(char* )"numDetections",             &gConfig_beam_forming.numDetections, INT_16, SINGLE},
  {(char* )"maxNumDetections",          &gConfig_beam_forming.maxNumDetections, INT_16, SINGLE},
  {(char* )"beamFormingScaling",        &gConfig_beam_forming.beamFormingScaling, INT_16, SINGLE},
  {(char* )"energyScaling",             &gConfig_beam_forming.energyScaling, INT_16, SINGLE},
  {(char* )"coordinateBufFormat",       &gConfig_beam_forming.coordinateBufFormat,  INT_8, SINGLE},
  {(char* )"randSeed",                  &gConfig_beam_forming.randSeed       , INT_32, SINGLE}
} ;

