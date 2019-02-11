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
#include "remapConvertTable_config.h"
#pragma RESET_MISRA ("required")

uint32_t remapConvertTable_numTestCases;

sremapConvertTable_Config gConfig_remapConvertTable[EVELIB_REMAPCONVERTTABLE_NUM_TESTCASES];

sTokenMapping gsTokenMap_remapConvertTable[] =
{
        {(char* )"numTestCases",          &remapConvertTable_numTestCases                , INT_32, SINGLE},
        {(char* )"functionName",          &gConfig_remapConvertTable[0].functionName     , STRING, SINGLE},
        {(char* )"remapWidth",            &gConfig_remapConvertTable[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight",           &gConfig_remapConvertTable[0].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth",            &gConfig_remapConvertTable[0].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight",          &gConfig_remapConvertTable[0].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat",           &gConfig_remapConvertTable[0].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile",          &gConfig_remapConvertTable[0].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat",    &gConfig_remapConvertTable[0].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile",         &gConfig_remapConvertTable[0].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat",   &gConfig_remapConvertTable[0].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift",                &gConfig_remapConvertTable[0].qShift  , INT_8, SINGLE},

        {(char* )"functionName0",          &gConfig_remapConvertTable[0].functionName     , STRING, SINGLE},
        {(char* )"remapWidth0",            &gConfig_remapConvertTable[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight0",           &gConfig_remapConvertTable[0].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth0",            &gConfig_remapConvertTable[0].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight0",          &gConfig_remapConvertTable[0].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat0",           &gConfig_remapConvertTable[0].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile0",          &gConfig_remapConvertTable[0].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat0",    &gConfig_remapConvertTable[0].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile0",         &gConfig_remapConvertTable[0].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat0",   &gConfig_remapConvertTable[0].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift0",                &gConfig_remapConvertTable[0].qShift  , INT_8, SINGLE},

        {(char* )"functionName1",          &gConfig_remapConvertTable[1].functionName     , STRING, SINGLE},
        {(char* )"remapWidth1",            &gConfig_remapConvertTable[1].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight1",           &gConfig_remapConvertTable[1].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth1",            &gConfig_remapConvertTable[1].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight1",          &gConfig_remapConvertTable[1].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat1",           &gConfig_remapConvertTable[1].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile1",          &gConfig_remapConvertTable[1].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat1",    &gConfig_remapConvertTable[1].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile1",         &gConfig_remapConvertTable[1].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat1",   &gConfig_remapConvertTable[1].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift1",                &gConfig_remapConvertTable[1].qShift  , INT_8, SINGLE},

        {(char* )"functionName2",          &gConfig_remapConvertTable[2].functionName     , STRING, SINGLE},
        {(char* )"remapWidth2",            &gConfig_remapConvertTable[2].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight2",           &gConfig_remapConvertTable[2].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth2",            &gConfig_remapConvertTable[2].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight2",           &gConfig_remapConvertTable[2].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat2",           &gConfig_remapConvertTable[2].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile2",          &gConfig_remapConvertTable[2].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat2",    &gConfig_remapConvertTable[2].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile2",         &gConfig_remapConvertTable[2].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat2",   &gConfig_remapConvertTable[2].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift2",                &gConfig_remapConvertTable[2].qShift  , INT_8, SINGLE},

        {(char* )"functionName3",          &gConfig_remapConvertTable[3].functionName     , STRING, SINGLE},
        {(char* )"remapWidth3",            &gConfig_remapConvertTable[3].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight3",           &gConfig_remapConvertTable[3].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth3",            &gConfig_remapConvertTable[3].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight3",           &gConfig_remapConvertTable[3].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat3",           &gConfig_remapConvertTable[3].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile3",          &gConfig_remapConvertTable[3].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat3",    &gConfig_remapConvertTable[3].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile3",         &gConfig_remapConvertTable[3].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat3",   &gConfig_remapConvertTable[3].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift3",                &gConfig_remapConvertTable[3].qShift  , INT_8, SINGLE},

        {(char* )"functionName4",          &gConfig_remapConvertTable[4].functionName     , STRING, SINGLE},
        {(char* )"remapWidth4",            &gConfig_remapConvertTable[4].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight4",           &gConfig_remapConvertTable[4].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth4",            &gConfig_remapConvertTable[4].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight4",           &gConfig_remapConvertTable[4].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat4",           &gConfig_remapConvertTable[4].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile4",          &gConfig_remapConvertTable[4].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat4",    &gConfig_remapConvertTable[4].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile4",         &gConfig_remapConvertTable[4].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat4",   &gConfig_remapConvertTable[4].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift4",                &gConfig_remapConvertTable[4].qShift  , INT_8, SINGLE},

        {(char* )"functionName5",          &gConfig_remapConvertTable[5].functionName     , STRING, SINGLE},
        {(char* )"remapWidth5",            &gConfig_remapConvertTable[5].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight5",           &gConfig_remapConvertTable[5].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth5",            &gConfig_remapConvertTable[5].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight5",           &gConfig_remapConvertTable[5].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat5",           &gConfig_remapConvertTable[5].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile5",          &gConfig_remapConvertTable[5].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat5",    &gConfig_remapConvertTable[5].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile5",         &gConfig_remapConvertTable[5].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat5",   &gConfig_remapConvertTable[5].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift5",                &gConfig_remapConvertTable[5].qShift  , INT_8, SINGLE},

        {(char* )"functionName6",          &gConfig_remapConvertTable[6].functionName     , STRING, SINGLE},
        {(char* )"remapWidth6",            &gConfig_remapConvertTable[6].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight6",           &gConfig_remapConvertTable[6].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth6",            &gConfig_remapConvertTable[6].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight6",           &gConfig_remapConvertTable[6].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat6",           &gConfig_remapConvertTable[6].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile6",          &gConfig_remapConvertTable[6].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat6",    &gConfig_remapConvertTable[6].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile6",         &gConfig_remapConvertTable[6].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat6",   &gConfig_remapConvertTable[6].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift6",                &gConfig_remapConvertTable[6].qShift  , INT_8, SINGLE},

        {(char* )"functionName7",          &gConfig_remapConvertTable[7].functionName     , STRING, SINGLE},
        {(char* )"remapWidth7",            &gConfig_remapConvertTable[7].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight7",           &gConfig_remapConvertTable[7].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth7",            &gConfig_remapConvertTable[7].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight7",           &gConfig_remapConvertTable[7].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat7",           &gConfig_remapConvertTable[7].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile7",          &gConfig_remapConvertTable[7].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat7",    &gConfig_remapConvertTable[7].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile7",         &gConfig_remapConvertTable[7].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat7",   &gConfig_remapConvertTable[7].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift7",                &gConfig_remapConvertTable[7].qShift  , INT_8, SINGLE},

        {(char* )"functionName8",          &gConfig_remapConvertTable[8].functionName     , STRING, SINGLE},
        {(char* )"remapWidth8",            &gConfig_remapConvertTable[8].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight8",           &gConfig_remapConvertTable[8].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth8",            &gConfig_remapConvertTable[8].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight8",           &gConfig_remapConvertTable[8].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat8",           &gConfig_remapConvertTable[8].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile8",          &gConfig_remapConvertTable[8].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat8",    &gConfig_remapConvertTable[8].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile8",         &gConfig_remapConvertTable[8].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat8",   &gConfig_remapConvertTable[8].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift8",                &gConfig_remapConvertTable[8].qShift  , INT_8, SINGLE},

        {(char* )"functionName9",          &gConfig_remapConvertTable[9].functionName     , STRING, SINGLE},
        {(char* )"remapWidth9",            &gConfig_remapConvertTable[9].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight9",           &gConfig_remapConvertTable[9].remapHeight      , INT_32, SINGLE},
        {(char* )"blockWidth9",            &gConfig_remapConvertTable[9].blockWidth       , INT_32, SINGLE},
        {(char* )"blockHeight9",           &gConfig_remapConvertTable[9].blockHeight      , INT_32, SINGLE},
        {(char* )"colorFormat9",           &gConfig_remapConvertTable[9].colorFormat      , INT_8, SINGLE},
        {(char* )"inputMapFile9",          &gConfig_remapConvertTable[9].inputMapFile        , STRING, SINGLE},
        {(char* )"inputMapFileFormat9",    &gConfig_remapConvertTable[9].inputMapFileFormat  , INT_32, SINGLE},
        {(char* )"outputMapFile9",         &gConfig_remapConvertTable[9].outputMapFile        , STRING, SINGLE},
        {(char* )"outputMapFileFormat9",   &gConfig_remapConvertTable[9].outputMapFileFormat  , INT_32, SINGLE},
        {(char* )"qShift9",                &gConfig_remapConvertTable[9].qShift  , INT_8, SINGLE},
};
