/*
*
* Copyright (c) 2015-2017 Texas Instruments Incorporated
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
#include "remapExecute_config.h"
#pragma RESET_MISRA ("required")

uint32_t remapExecute_numTestCases;

sremapExecute_Config gConfig_remapExecute[EVELIB_REMAPEXECUTE_NUM_TESTCASES];

sTokenMapping gsTokenMap_remapExecute[] =
{
        {(char* )"numTestCases",          &remapExecute_numTestCases                , INT_32, SINGLE},
        {(char* )"convertedBinMapFile",   &gConfig_remapExecute[0].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile",       &gConfig_remapExecute[0].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth",            &gConfig_remapExecute[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight",           &gConfig_remapExecute[0].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth",            &gConfig_remapExecute[0].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight",           &gConfig_remapExecute[0].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat",           &gConfig_remapExecute[0].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile",             &gConfig_remapExecute[0].inputFile        , STRING, SINGLE},
        {(char* )"outputFile",            &gConfig_remapExecute[0].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile0",          &gConfig_remapExecute[0].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile0",       &gConfig_remapExecute[0].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth0",            &gConfig_remapExecute[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight0",           &gConfig_remapExecute[0].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth0",            &gConfig_remapExecute[0].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight0",           &gConfig_remapExecute[0].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat0",           &gConfig_remapExecute[0].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile0",          &gConfig_remapExecute[0].inputFile        , STRING, SINGLE},
        {(char* )"outputFile0",         &gConfig_remapExecute[0].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile1",          &gConfig_remapExecute[1].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile1",       &gConfig_remapExecute[1].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth1",            &gConfig_remapExecute[1].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight1",           &gConfig_remapExecute[1].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth1",            &gConfig_remapExecute[1].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight1",           &gConfig_remapExecute[1].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat1",           &gConfig_remapExecute[1].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile1",          &gConfig_remapExecute[1].inputFile        , STRING, SINGLE},
        {(char* )"outputFile1",         &gConfig_remapExecute[1].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile2",          &gConfig_remapExecute[2].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile2",       &gConfig_remapExecute[2].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth2",            &gConfig_remapExecute[2].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight2",           &gConfig_remapExecute[2].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth2",            &gConfig_remapExecute[2].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight2",           &gConfig_remapExecute[2].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat2",           &gConfig_remapExecute[2].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile2",          &gConfig_remapExecute[2].inputFile        , STRING, SINGLE},
        {(char* )"outputFile2",         &gConfig_remapExecute[2].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile3",          &gConfig_remapExecute[3].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile3",       &gConfig_remapExecute[3].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth3",            &gConfig_remapExecute[3].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight3",           &gConfig_remapExecute[3].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth3",            &gConfig_remapExecute[3].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight3",           &gConfig_remapExecute[3].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat3",           &gConfig_remapExecute[3].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile3",          &gConfig_remapExecute[3].inputFile        , STRING, SINGLE},
        {(char* )"outputFile3",         &gConfig_remapExecute[3].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile4",          &gConfig_remapExecute[4].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile4",       &gConfig_remapExecute[4].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth4",            &gConfig_remapExecute[4].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight4",           &gConfig_remapExecute[4].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth4",            &gConfig_remapExecute[4].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeigh4",           &gConfig_remapExecute[4].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat4",           &gConfig_remapExecute[4].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile4",          &gConfig_remapExecute[4].inputFile        , STRING, SINGLE},
        {(char* )"outputFile4",         &gConfig_remapExecute[4].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile5",          &gConfig_remapExecute[5].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile5",       &gConfig_remapExecute[5].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth5",            &gConfig_remapExecute[5].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight5",           &gConfig_remapExecute[5].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth5",            &gConfig_remapExecute[5].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight5",           &gConfig_remapExecute[5].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat5",           &gConfig_remapExecute[5].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile5",          &gConfig_remapExecute[5].inputFile        , STRING, SINGLE},
        {(char* )"outputFile5",         &gConfig_remapExecute[5].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile6",          &gConfig_remapExecute[6].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile6",       &gConfig_remapExecute[6].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth6",            &gConfig_remapExecute[6].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight6",           &gConfig_remapExecute[6].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth6",            &gConfig_remapExecute[6].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight6",           &gConfig_remapExecute[6].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat6",           &gConfig_remapExecute[6].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile6",          &gConfig_remapExecute[6].inputFile        , STRING, SINGLE},
        {(char* )"outputFile6",         &gConfig_remapExecute[6].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile7",          &gConfig_remapExecute[7].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile7",       &gConfig_remapExecute[7].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth7",            &gConfig_remapExecute[7].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight7",           &gConfig_remapExecute[7].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth7",            &gConfig_remapExecute[7].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight7",           &gConfig_remapExecute[7].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat7",           &gConfig_remapExecute[7].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile7",          &gConfig_remapExecute[7].inputFile        , STRING, SINGLE},
        {(char* )"outputFile7",         &gConfig_remapExecute[7].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile8",          &gConfig_remapExecute[8].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile8",       &gConfig_remapExecute[8].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth8",            &gConfig_remapExecute[8].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight8",           &gConfig_remapExecute[8].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth8",            &gConfig_remapExecute[8].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight8",           &gConfig_remapExecute[8].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat8",           &gConfig_remapExecute[8].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile8",          &gConfig_remapExecute[8].inputFile        , STRING, SINGLE},
        {(char* )"outputFile8",         &gConfig_remapExecute[8].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile9",          &gConfig_remapExecute[9].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile9",       &gConfig_remapExecute[9].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth9",            &gConfig_remapExecute[9].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight9",           &gConfig_remapExecute[9].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth9",            &gConfig_remapExecute[9].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight9",           &gConfig_remapExecute[9].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat9",           &gConfig_remapExecute[9].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile9",          &gConfig_remapExecute[9].inputFile        , STRING, SINGLE},
        {(char* )"outputFile9",         &gConfig_remapExecute[9].outputFile        , STRING, SINGLE},

};
