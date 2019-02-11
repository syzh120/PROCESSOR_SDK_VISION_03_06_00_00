/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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
#include "soft_isp16_config.h"
#pragma RESET_MISRA ("required")

uint32_t softIsp16_numTestCases;

sSoftIsp16_Config gConfig_softIsp16[EVELIB_SOFT_ISP16_NUM_TESTCASES];

sTokenMapping gsTokenMap_softIsp16[] =
{
        {(char* )"numTestCases",          &softIsp16_numTestCases                   , INT_32, SINGLE},

        {(char* )"inImage",               &gConfig_softIsp16[0].inImage             , STRING, SINGLE},
        {(char* )"srcImageWidth",         &gConfig_softIsp16[0].srcImageWidth       , INT_32, SINGLE},
        {(char* )"srcImageHeight",        &gConfig_softIsp16[0].srcImageHeight      , INT_32, SINGLE},
        {(char* )"dstImageWidth",         &gConfig_softIsp16[0].dstImageWidth       , INT_32, SINGLE},
        {(char* )"dstImageHeight",        &gConfig_softIsp16[0].dstImageHeight      , INT_32, SINGLE},
        {(char* )"roiWidth",              &gConfig_softIsp16[0].roiWidth            , INT_32, SINGLE},
        {(char* )"roiHeight",             &gConfig_softIsp16[0].roiHeight           , INT_32, SINGLE},
        {(char* )"srcOffsetX",            &gConfig_softIsp16[0].srcOffsetX          , INT_16, SINGLE},
        {(char* )"srcOffsetY",            &gConfig_softIsp16[0].srcOffsetY          , INT_16, SINGLE},
        {(char* )"dstOffsetX",            &gConfig_softIsp16[0].dstOffsetX          , INT_16, SINGLE},
        {(char* )"dstOffsetY",            &gConfig_softIsp16[0].dstOffsetY          , INT_16, SINGLE},
        {(char* )"outImage",              &gConfig_softIsp16[0].outImage            , STRING, SINGLE},
        {(char* )"pattern",               &gConfig_softIsp16[0].pattern             , INT_8 , SINGLE},
        {(char* )"bayerPattern",          &gConfig_softIsp16[0].bayerPattern             , INT_8 , SINGLE},
        {(char* )"inputBitDepth",         &gConfig_softIsp16[0].inputBitDepth       , INT_8 , SINGLE},
        {(char *)"testCaseName",          &gConfig_softIsp16[0].testCaseName        , STRING, SINGLE},
        {(char* )"performanceTestcase",   &gConfig_softIsp16[0].performanceTestcase , INT_8 , SINGLE},
        {(char *)"desc",                  &gConfig_softIsp16[0].desc                , STRING, SINGLE},

} ;
