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
#include "hough_for_lines_config.h"
#pragma RESET_MISRA ("required")

uint32_t houghForLines_numTestCases;
sHoughForLines_Config gConfig_houghForLines[HOUGH_FOR_LINES_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_houghForLines[] =
{
  {(char *)"numTestCases"        ,&houghForLines_numTestCases              , INT_32, SINGLE},
  {(char *)"edgeMapList"         ,&gConfig_houghForLines[0].edgeMapList    , STRING, SINGLE},
  {(char *)"votedRhoThetaSpace" ,&gConfig_houghForLines[0].votedRhoThetaSpace, STRING, SINGLE},
  {(char *)"refImage"        ,&gConfig_houghForLines[0].refImage       , STRING, SINGLE},
  {(char *)"srcImageWidth"   ,&gConfig_houghForLines[0].srcImageWidth  , INT_16, SINGLE},
  {(char *)"srcImageHeight"  ,&gConfig_houghForLines[0].srcImageHeight , INT_16, SINGLE},
  {(char* )"listSize",        &gConfig_houghForLines[0].listSize        , INT_32, SINGLE},
  {(char* )"thetaStart",      &gConfig_houghForLines[0].thetaStart      , INT_16, SINGLE},
  {(char* )"thetaEnd",        &gConfig_houghForLines[0].thetaEnd        , INT_16, SINGLE},
  {(char* )"thetaStepSize",   &gConfig_houghForLines[0].thetaStepSize   , INT_8, SINGLE},
  {(char* )"rhoMaxLength",    &gConfig_houghForLines[0].rhoMaxLength    , INT_16, SINGLE},
  {(char* )"randSeed",        &gConfig_houghForLines[0].randSeed        , INT_32, SINGLE},
  {(char* )"testCaseName",           &gConfig_houghForLines[0].testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_houghForLines[0].performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                   &gConfig_houghForLines[0].desc                   , STRING, SINGLE}

} ;

