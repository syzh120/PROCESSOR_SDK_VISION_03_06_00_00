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
#include "soft_isp_config.h"
#pragma RESET_MISRA ("required")

sSoftIsp_Config gConfig_soft_isp;

sTokenMapping gsTokenMap_soft_isp[] =
{
  {(char* )"inImg",             &gConfig_soft_isp.inImg                , STRING, SINGLE},
  {(char* )"gbceToneCurve",     &gConfig_soft_isp.gbceToneCurve        , STRING, SINGLE},
  {(char* )"outImg",            &gConfig_soft_isp.outImg               , STRING, SINGLE},
  {(char* )"imageWidth",        &gConfig_soft_isp.imageWidth           , INT_16, SINGLE},
  {(char* )"imageHeight",       &gConfig_soft_isp.imageHeight          , INT_16, SINGLE},
  {(char* )"imagePitch",        &gConfig_soft_isp.imagePitch           , INT_16, SINGLE},
  {(char* )"rPosition",         &gConfig_soft_isp.rPosition            , INT_8 , SINGLE},
  {(char* )"sensorBitDepth",    &gConfig_soft_isp.sensorBitDepth       , INT_8 , SINGLE},
  {(char* )"maxPixValue",       &gConfig_soft_isp.maxPixValue          , INT_16, SINGLE},
  {(char* )"enableDecompand",   &gConfig_soft_isp.enableDecompand      , INT_8 , SINGLE},
  {(char* )"pout1",             &gConfig_soft_isp.pout1                , INT_16, SINGLE},
  {(char* )"pout2",             &gConfig_soft_isp.pout2                , INT_16, SINGLE},
  {(char* )"slope1",            &gConfig_soft_isp.slope1               , INT_8 , SINGLE},
  {(char* )"slope2",            &gConfig_soft_isp.slope2               , INT_16, SINGLE},
  {(char* )"blackClamp0",       &gConfig_soft_isp.blackClamp[0]        , INT_8 , SINGLE},
  {(char* )"blackClamp1",       &gConfig_soft_isp.blackClamp[1]        , INT_8 , SINGLE},
  {(char* )"blackClamp2",       &gConfig_soft_isp.blackClamp[2]        , INT_8 , SINGLE},
  {(char* )"blackClamp3",       &gConfig_soft_isp.blackClamp[3]        , INT_8 , SINGLE},
  {(char* )"cBalanceGain0",     &gConfig_soft_isp.cBalanceGain[0]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain1",     &gConfig_soft_isp.cBalanceGain[1]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain2",     &gConfig_soft_isp.cBalanceGain[2]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain3",     &gConfig_soft_isp.cBalanceGain[3]      , INT_8 , SINGLE},
  {(char* )"cBalanceShift",     &gConfig_soft_isp.cBalanceShift        , INT_8 , SINGLE},
  {(char* )"enableExtractR",    &gConfig_soft_isp.enableExtractR       , INT_8 , SINGLE},
  {(char* )"enableStats",       &gConfig_soft_isp.enableStats          , INT_8 , SINGLE},
  {(char* )"statBlkWidth",      &gConfig_soft_isp.statBlkWidth         , INT_16, SINGLE},
  {(char* )"statBlkHeight",     &gConfig_soft_isp.statBlkHeight        , INT_16, SINGLE},
  {(char* )"saturationLimit",   &gConfig_soft_isp.saturationLimit      , INT_16, SINGLE},
  {(char* )"gbceMethod",        &gConfig_soft_isp.gbceMethod           , INT_8 , SINGLE},
  {(char* )"randSeed",          &gConfig_soft_isp.randSeed             , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_soft_isp.numIter              , INT_8 , SINGLE},
  {(char* )"testCaseName",        &gConfig_soft_isp.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase", &gConfig_soft_isp.performanceTestcase  ,  INT_8, SINGLE},
  {(char* )"desc",                &gConfig_soft_isp.testCaseDesc         , STRING, SINGLE},
} ;

