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
#include "stereovision_config.h"
#pragma RESET_MISRA ("required")

uint32_t stereovision_numTestCases;
sSTEREOVISION_Config gConfig_STEREOVISION[STEREOVISION_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_STEREOVISION[] =
{
        {(char *)"numTestCases"    ,&stereovision_numTestCases                   , INT_32, SINGLE},
        {(char *)"inImageFileName"      ,&gConfig_STEREOVISION[0].inImageFileName, STRING, SINGLE},
        {(char *)"inDisparityFileName"  ,&gConfig_STEREOVISION[0].inDisparityFileName, STRING, SINGLE},
        {(char *)"inAuxDisparityFileName"  ,&gConfig_STEREOVISION[0].inAuxDisparityFileName, STRING, SINGLE},
        {(char *)"inCostFileName"  ,&gConfig_STEREOVISION[0].inCostFileName, STRING, SINGLE},
        {(char *)"outFileName"     ,&gConfig_STEREOVISION[0].outFileName         , STRING, SINGLE},
        {(char *)"out16BitDispFileName"     ,&gConfig_STEREOVISION[0].out16BitDispFileName         , STRING, SINGLE},
        {(char *)"maxImageWidth"   ,&gConfig_STEREOVISION[0].maxImageWidth       , INT_16, SINGLE},
        {(char *)"maxImageHeight"  ,&gConfig_STEREOVISION[0].maxImageHeight      , INT_16, SINGLE},
        {(char *)"maxFrames"       ,&gConfig_STEREOVISION[0].maxFrames           , INT_16, SINGLE},
        {(char* )"roiWidth"        ,&gConfig_STEREOVISION[0].roiWidth            , INT_16, SINGLE},
        {(char* )"roiHeight"       ,&gConfig_STEREOVISION[0].roiHeight           , INT_16, SINGLE},
        {(char* )"startX"       ,&gConfig_STEREOVISION[0].startX           , INT_16, SINGLE},
        {(char* )"startY"       ,&gConfig_STEREOVISION[0].startY           , INT_16, SINGLE},
        {(char* )"inputBitDepth"   ,&gConfig_STEREOVISION[0].inputBitDepth       , INT_8, SINGLE},
        {(char* )"censusWinWidth"  ,&gConfig_STEREOVISION[0].censusWinWidth      , INT_8, SINGLE},
        {(char* )"censusWinHeight" ,&gConfig_STEREOVISION[0].censusWinHeight     , INT_8, SINGLE},
        {(char* )"censusWinHorzStep" ,&gConfig_STEREOVISION[0].censusWinHorzStep   , INT_8, SINGLE},
        {(char* )"censusWinVertStep" ,&gConfig_STEREOVISION[0].censusWinVertStep   , INT_8, SINGLE},
        {(char* )"costSupportWinWidth" ,&gConfig_STEREOVISION[0].costSupportWinWidth   , INT_8, SINGLE},
        {(char* )"costSupportWinHeight",&gConfig_STEREOVISION[0].costSupportWinHeight  , INT_8, SINGLE},
        {(char* )"numDisparities"    ,&gConfig_STEREOVISION[0].numDisparities      , INT_16, SINGLE},
        {(char* )"disparityStep"     ,&gConfig_STEREOVISION[0].disparityStep       , INT_8, SINGLE},
        {(char* )"searchDir"         ,&gConfig_STEREOVISION[0].searchDir           , INT_8, SINGLE},
        {(char* )"smoothingStrength"  ,&gConfig_STEREOVISION[0].smoothingStrength     , INT_8, SINGLE},
        {(char* )"disparityNumFracBits"  ,&gConfig_STEREOVISION[0].disparityNumFracBits, INT_8, SINGLE},
        {(char* )"disparityMinThreshold"  ,&gConfig_STEREOVISION[0].disparityMinThreshold, INT_8, SINGLE},
        {(char* )"disparityMaxThreshold"  ,&gConfig_STEREOVISION[0].disparityMaxThreshold, INT_8, SINGLE},
        {(char* )"costMaxThreshold"        ,&gConfig_STEREOVISION[0].costMaxThreshold, INT_8, SINGLE},
        {(char* )"minConfidenceThreshold"  ,&gConfig_STEREOVISION[0].minConfidenceThreshold, INT_8, SINGLE},
        {(char* )"holeFillingStrength"  ,&gConfig_STEREOVISION[0].holeFillingStrength, INT_8, SINGLE},
        {(char* )"textureLumaLoThresh"  ,&gConfig_STEREOVISION[0].textureLumaLoThresh, INT_8, SINGLE},
        {(char* )"textureLumaHiThresh"  ,&gConfig_STEREOVISION[0].textureLumaHiThresh, INT_8, SINGLE},
        {(char* )"textureThreshold"  ,&gConfig_STEREOVISION[0].textureThreshold, INT_8, SINGLE},
        {(char* )"maxDispDissimilarity"  ,&gConfig_STEREOVISION[0].maxDispDissimilarity, INT_8, SINGLE},
        {(char* )"lrMaxDiffThreshold"  ,&gConfig_STEREOVISION[0].lrMaxDiffThreshold, INT_8, SINGLE},
        {(char* )"minConfidentNSegment"  ,&gConfig_STEREOVISION[0].minConfidentNSegment, INT_8, SINGLE},
        {(char* )"enable16BitsDispOut"  ,&gConfig_STEREOVISION[0].enable16BitsDispOut, INT_8, SINGLE},

        {(char *)"inImageFileName0"      ,&gConfig_STEREOVISION[0].inImageFileName, STRING, SINGLE},
        {(char *)"inDisparityFileName0"  ,&gConfig_STEREOVISION[0].inDisparityFileName, STRING, SINGLE},
        {(char *)"inAuxDisparityFileName0"  ,&gConfig_STEREOVISION[0].inAuxDisparityFileName, STRING, SINGLE},
        {(char *)"inCostFileName0"  ,&gConfig_STEREOVISION[0].inCostFileName, STRING, SINGLE},
        {(char *)"outFileName0"     ,&gConfig_STEREOVISION[0].outFileName         , STRING, SINGLE},
        {(char *)"out16BitDispFileName0"     ,&gConfig_STEREOVISION[0].out16BitDispFileName         , STRING, SINGLE},
        {(char *)"maxImageWidth0"   ,&gConfig_STEREOVISION[0].maxImageWidth       , INT_16, SINGLE},
        {(char *)"maxImageHeight0"  ,&gConfig_STEREOVISION[0].maxImageHeight      , INT_16, SINGLE},
        {(char *)"maxFrames0"       ,&gConfig_STEREOVISION[0].maxFrames           , INT_16, SINGLE},
        {(char* )"roiWidth0"        ,&gConfig_STEREOVISION[0].roiWidth            , INT_16, SINGLE},
        {(char* )"roiHeight0"       ,&gConfig_STEREOVISION[0].roiHeight           , INT_16, SINGLE},
        {(char* )"startX0"          ,&gConfig_STEREOVISION[0].startX              , INT_16, SINGLE},
        {(char* )"startY0"          ,&gConfig_STEREOVISION[0].startY              , INT_16, SINGLE},
        {(char* )"inputBitDepth0"   ,&gConfig_STEREOVISION[0].inputBitDepth       , INT_8, SINGLE},
        {(char* )"censusWinWidth0"  ,&gConfig_STEREOVISION[0].censusWinWidth      , INT_8, SINGLE},
        {(char* )"censusWinHeight0" ,&gConfig_STEREOVISION[0].censusWinHeight     , INT_8, SINGLE},
        {(char* )"censusWinHorzStep0" ,&gConfig_STEREOVISION[0].censusWinHorzStep   , INT_8, SINGLE},
        {(char* )"censusWinVertStep0" ,&gConfig_STEREOVISION[0].censusWinVertStep   , INT_8, SINGLE},
        {(char* )"costSupportWinWidth0" ,&gConfig_STEREOVISION[0].costSupportWinWidth   , INT_8, SINGLE},
        {(char* )"costSupportWinHeight0",&gConfig_STEREOVISION[0].costSupportWinHeight  , INT_8, SINGLE},
        {(char* )"numDisparities0"    ,&gConfig_STEREOVISION[0].numDisparities      , INT_16, SINGLE},
        {(char* )"disparityStep0"     ,&gConfig_STEREOVISION[0].disparityStep       , INT_8, SINGLE},
        {(char* )"searchDir0"         ,&gConfig_STEREOVISION[0].searchDir           , INT_8, SINGLE},
        {(char* )"smoothingStrength0"  ,&gConfig_STEREOVISION[0].smoothingStrength     , INT_8, SINGLE},
        {(char* )"disparityNumFracBits0"  ,&gConfig_STEREOVISION[0].disparityNumFracBits, INT_8, SINGLE},
        {(char* )"disparityMinThreshold0"  ,&gConfig_STEREOVISION[0].disparityMinThreshold, INT_8, SINGLE},
        {(char* )"disparityMaxThreshold0"  ,&gConfig_STEREOVISION[0].disparityMaxThreshold, INT_8, SINGLE},
        {(char* )"costMaxThreshold0"        ,&gConfig_STEREOVISION[0].costMaxThreshold, INT_8, SINGLE},
        {(char* )"minConfidenceThreshold0"  ,&gConfig_STEREOVISION[0].minConfidenceThreshold, INT_8, SINGLE},
        {(char* )"holeFillingStrength0"  ,&gConfig_STEREOVISION[0].holeFillingStrength, INT_8, SINGLE},
        {(char* )"textureLumaLoThresh0"  ,&gConfig_STEREOVISION[0].textureLumaLoThresh, INT_8, SINGLE},
        {(char* )"textureLumaHiThresh0"  ,&gConfig_STEREOVISION[0].textureLumaHiThresh, INT_8, SINGLE},
        {(char* )"textureThreshold0"  ,&gConfig_STEREOVISION[0].textureThreshold, INT_8, SINGLE},
        {(char* )"maxDispDissimilarity0"  ,&gConfig_STEREOVISION[0].maxDispDissimilarity, INT_8, SINGLE},
        {(char* )"lrMaxDiffThreshold0"  ,&gConfig_STEREOVISION[0].lrMaxDiffThreshold, INT_8, SINGLE},
        {(char* )"minConfidentNSegment0"  ,&gConfig_STEREOVISION[0].minConfidentNSegment, INT_8, SINGLE},
        {(char* )"enable16BitsDispOut0"  ,&gConfig_STEREOVISION[0].enable16BitsDispOut, INT_8, SINGLE},

        {(char *)"inImageFileName1"      ,&gConfig_STEREOVISION[1].inImageFileName, STRING, SINGLE},
        {(char *)"inDisparityFileName1"  ,&gConfig_STEREOVISION[1].inDisparityFileName, STRING, SINGLE},
        {(char *)"inAuxDisparityFileName1"  ,&gConfig_STEREOVISION[1].inAuxDisparityFileName, STRING, SINGLE},
        {(char *)"inCostFileName1"  ,&gConfig_STEREOVISION[1].inCostFileName, STRING, SINGLE},
        {(char *)"outFileName1"     ,&gConfig_STEREOVISION[1].outFileName         , STRING, SINGLE},
        {(char *)"out16BitDispFileName1"     ,&gConfig_STEREOVISION[1].out16BitDispFileName         , STRING, SINGLE},
        {(char *)"maxImageWidth1"   ,&gConfig_STEREOVISION[1].maxImageWidth       , INT_16, SINGLE},
        {(char *)"maxImageHeight1"  ,&gConfig_STEREOVISION[1].maxImageHeight      , INT_16, SINGLE},
        {(char *)"maxFrames1"       ,&gConfig_STEREOVISION[1].maxFrames           , INT_16, SINGLE},
        {(char* )"roiWidth1"        ,&gConfig_STEREOVISION[1].roiWidth            , INT_16, SINGLE},
        {(char* )"roiHeight1"       ,&gConfig_STEREOVISION[1].roiHeight           , INT_16, SINGLE},
        {(char* )"startX1"       ,&gConfig_STEREOVISION[1].startX              , INT_16, SINGLE},
        {(char* )"startY1"       ,&gConfig_STEREOVISION[1].startY              , INT_16, SINGLE},
        {(char* )"inputBitDepth1"   ,&gConfig_STEREOVISION[1].inputBitDepth       , INT_8, SINGLE},
        {(char* )"censusWinWidth1"  ,&gConfig_STEREOVISION[1].censusWinWidth      , INT_8, SINGLE},
        {(char* )"censusWinHeight1" ,&gConfig_STEREOVISION[1].censusWinHeight     , INT_8, SINGLE},
        {(char* )"censusWinHorzStep1" ,&gConfig_STEREOVISION[1].censusWinHorzStep   , INT_8, SINGLE},
        {(char* )"censusWinVertStep1" ,&gConfig_STEREOVISION[1].censusWinVertStep   , INT_8, SINGLE},
        {(char* )"costSupportWinWidth1" ,&gConfig_STEREOVISION[1].costSupportWinWidth   , INT_8, SINGLE},
        {(char* )"costSupportWinHeight1",&gConfig_STEREOVISION[1].costSupportWinHeight  , INT_8, SINGLE},
        {(char* )"numDisparities1"    ,&gConfig_STEREOVISION[1].numDisparities      , INT_16, SINGLE},
        {(char* )"disparityStep1"     ,&gConfig_STEREOVISION[1].disparityStep       , INT_8, SINGLE},
        {(char* )"searchDir1"         ,&gConfig_STEREOVISION[1].searchDir           , INT_8, SINGLE},
        {(char* )"smoothingStrength1"  ,&gConfig_STEREOVISION[1].smoothingStrength     , INT_8, SINGLE},
        {(char* )"disparityNumFracBits1"  ,&gConfig_STEREOVISION[1].disparityNumFracBits, INT_8, SINGLE},
        {(char* )"disparityMinThreshold1"  ,&gConfig_STEREOVISION[1].disparityMinThreshold, INT_8, SINGLE},
        {(char* )"disparityMaxThreshold1"  ,&gConfig_STEREOVISION[1].disparityMaxThreshold, INT_8, SINGLE},
        {(char* )"costMaxThreshold1"        ,&gConfig_STEREOVISION[1].costMaxThreshold, INT_8, SINGLE},
        {(char* )"minConfidenceThreshold1"  ,&gConfig_STEREOVISION[1].minConfidenceThreshold, INT_8, SINGLE},
        {(char* )"holeFillingStrength1"  ,&gConfig_STEREOVISION[1].holeFillingStrength, INT_8, SINGLE},
        {(char* )"textureLumaLoThresh1"  ,&gConfig_STEREOVISION[1].textureLumaLoThresh, INT_8, SINGLE},
        {(char* )"textureLumaHiThresh1"  ,&gConfig_STEREOVISION[1].textureLumaHiThresh, INT_8, SINGLE},
        {(char* )"textureThreshold1"  ,&gConfig_STEREOVISION[1].textureThreshold, INT_8, SINGLE},
        {(char* )"maxDispDissimilarity1"  ,&gConfig_STEREOVISION[1].maxDispDissimilarity, INT_8, SINGLE},
        {(char* )"lrMaxDiffThreshold1"  ,&gConfig_STEREOVISION[1].lrMaxDiffThreshold, INT_8, SINGLE},
        {(char* )"minConfidentNSegment1"  ,&gConfig_STEREOVISION[1].minConfidentNSegment, INT_8, SINGLE},
        {(char* )"enable16BitsDispOut1"  ,&gConfig_STEREOVISION[1].enable16BitsDispOut, INT_8, SINGLE},

        {(char *)"inImageFileName2"      ,&gConfig_STEREOVISION[2].inImageFileName, STRING, SINGLE},
        {(char *)"inDisparityFileName2"  ,&gConfig_STEREOVISION[2].inDisparityFileName, STRING, SINGLE},
        {(char *)"inAuxDisparityFileName2"  ,&gConfig_STEREOVISION[2].inAuxDisparityFileName, STRING, SINGLE},
        {(char *)"inCostFileName2"  ,&gConfig_STEREOVISION[2].inCostFileName, STRING, SINGLE},
        {(char *)"outFileName2"     ,&gConfig_STEREOVISION[2].outFileName         , STRING, SINGLE},
        {(char *)"out16BitDispFileName2"     ,&gConfig_STEREOVISION[2].out16BitDispFileName         , STRING, SINGLE},
        {(char *)"maxImageWidth2"   ,&gConfig_STEREOVISION[2].maxImageWidth       , INT_16, SINGLE},
        {(char *)"maxImageHeight2"  ,&gConfig_STEREOVISION[2].maxImageHeight      , INT_16, SINGLE},
        {(char *)"maxFrames2"       ,&gConfig_STEREOVISION[2].maxFrames           , INT_16, SINGLE},
        {(char* )"roiWidth2"        ,&gConfig_STEREOVISION[2].roiWidth            , INT_16, SINGLE},
        {(char* )"roiHeight2"       ,&gConfig_STEREOVISION[2].roiHeight           , INT_16, SINGLE},
        {(char* )"startX2"       ,&gConfig_STEREOVISION[2].startX              , INT_16, SINGLE},
        {(char* )"startY2"       ,&gConfig_STEREOVISION[2].startY              , INT_16, SINGLE},
        {(char* )"inputBitDepth2"   ,&gConfig_STEREOVISION[2].inputBitDepth       , INT_8, SINGLE},
        {(char* )"censusWinWidth2"  ,&gConfig_STEREOVISION[2].censusWinWidth      , INT_8, SINGLE},
        {(char* )"censusWinHeight2" ,&gConfig_STEREOVISION[2].censusWinHeight     , INT_8, SINGLE},
        {(char* )"censusWinHorzStep2" ,&gConfig_STEREOVISION[2].censusWinHorzStep   , INT_8, SINGLE},
        {(char* )"censusWinVertStep2" ,&gConfig_STEREOVISION[2].censusWinVertStep   , INT_8, SINGLE},
        {(char* )"costSupportWinWidth2" ,&gConfig_STEREOVISION[2].costSupportWinWidth   , INT_8, SINGLE},
        {(char* )"costSupportWinHeight2",&gConfig_STEREOVISION[2].costSupportWinHeight  , INT_8, SINGLE},
        {(char* )"numDisparities2"    ,&gConfig_STEREOVISION[2].numDisparities      , INT_16, SINGLE},
        {(char* )"disparityStep2"     ,&gConfig_STEREOVISION[2].disparityStep       , INT_8, SINGLE},
        {(char* )"searchDir2"         ,&gConfig_STEREOVISION[2].searchDir           , INT_8, SINGLE},
        {(char* )"smoothingStrength2"  ,&gConfig_STEREOVISION[2].smoothingStrength     , INT_8, SINGLE},
        {(char* )"disparityNumFracBits2"  ,&gConfig_STEREOVISION[2].disparityNumFracBits, INT_8, SINGLE},
        {(char* )"disparityMinThreshold2"  ,&gConfig_STEREOVISION[2].disparityMinThreshold, INT_8, SINGLE},
        {(char* )"disparityMaxThreshold2"  ,&gConfig_STEREOVISION[2].disparityMaxThreshold, INT_8, SINGLE},
        {(char* )"costMaxThreshold2"        ,&gConfig_STEREOVISION[2].costMaxThreshold, INT_8, SINGLE},
        {(char* )"minConfidenceThreshold2"  ,&gConfig_STEREOVISION[2].minConfidenceThreshold, INT_8, SINGLE},
        {(char* )"holeFillingStrength2"  ,&gConfig_STEREOVISION[2].holeFillingStrength, INT_8, SINGLE},
        {(char* )"textureLumaLoThresh2"  ,&gConfig_STEREOVISION[2].textureLumaLoThresh, INT_8, SINGLE},
        {(char* )"textureLumaHiThresh2"  ,&gConfig_STEREOVISION[2].textureLumaHiThresh, INT_8, SINGLE},
        {(char* )"textureThreshold2"  ,&gConfig_STEREOVISION[2].textureThreshold, INT_8, SINGLE},
        {(char* )"maxDispDissimilarity2"  ,&gConfig_STEREOVISION[2].maxDispDissimilarity, INT_8, SINGLE},
        {(char* )"lrMaxDiffThreshold2"  ,&gConfig_STEREOVISION[2].lrMaxDiffThreshold, INT_8, SINGLE},
        {(char* )"minConfidentNSegment2"  ,&gConfig_STEREOVISION[2].minConfidentNSegment, INT_8, SINGLE},
        {(char* )"enable16BitsDispOut2"  ,&gConfig_STEREOVISION[2].enable16BitsDispOut, INT_8, SINGLE},
} ;

