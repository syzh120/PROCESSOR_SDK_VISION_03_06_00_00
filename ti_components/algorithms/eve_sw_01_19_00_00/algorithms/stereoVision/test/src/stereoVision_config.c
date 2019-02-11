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
#include "stereoVision_config.h"
#pragma RESET_MISRA ("required")

uint32_t stereoVision_numTestCases;

sstereoVision_Config gConfig_stereoVision[EVELIB_STEREOVISION_NUM_TESTCASES];

sTokenMapping gsTokenMap_stereoVision[] =
{
        {(char* )"numTestCases",           &stereoVision_numTestCases         , INT_32, SINGLE},

        {(char* )"inImageLeft",           &gConfig_stereoVision[0].inImageLeft         , STRING, SINGLE},
        {(char* )"inImageRight",          &gConfig_stereoVision[0].inImageRight        , STRING, SINGLE},
        {(char* )"gtImage",               &gConfig_stereoVision[0].gtImage             , STRING, SINGLE},
        {(char* )"gtScale",               &gConfig_stereoVision[0].gtScale             , INT_8 , SINGLE},
        {(char* )"stereoMode",            &gConfig_stereoVision[0].stereoMode          , STRING , SINGLE},
        {(char* )"imageWidth",            &gConfig_stereoVision[0].imageWidth          , INT_32, SINGLE},
        {(char* )"imageHeight",           &gConfig_stereoVision[0].imageHeight         , INT_32, SINGLE},
        {(char* )"srcImagePitch",         &gConfig_stereoVision[0].srcImagePitch       , INT_32, SINGLE},
        {(char* )"remapWidth",         &gConfig_stereoVision[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight",        &gConfig_stereoVision[0].remapHeight      , INT_32, SINGLE},

        {(char* )"outImage",              &gConfig_stereoVision[0].outImage            , STRING, SINGLE},
        {(char* )"dstImagePitch",         &gConfig_stereoVision[0].dstImagePitch       , INT_32, SINGLE},
        {(char* )"pattern",               &gConfig_stereoVision[0].pattern             , INT_8 , SINGLE},
        {(char* )"inputBitDepth",         &gConfig_stereoVision[0].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"censusWinWidth",        &gConfig_stereoVision[0].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"censusWinHeight",       &gConfig_stereoVision[0].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"censusWinHorzStep",     &gConfig_stereoVision[0].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"censusWinVertStep",     &gConfig_stereoVision[0].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"disparityWinWidth",     &gConfig_stereoVision[0].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"disparityWinHeight",    &gConfig_stereoVision[0].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"numDisparities",        &gConfig_stereoVision[0].numDisparities      , INT_16 , SINGLE},
        {(char* )"disparityStep",         &gConfig_stereoVision[0].disparityStep       , INT_8 , SINGLE},
        {(char* )"maxMinCostRatio",       &gConfig_stereoVision[0].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"offset_x",              &gConfig_stereoVision[0].offset_x       , INT_32, SINGLE},
        {(char* )"offset_y",              &gConfig_stereoVision[0].offset_y       , INT_32, SINGLE},
        {(char* )"searchDir",               &gConfig_stereoVision[0].searchDir  , INT_8, SINGLE},
        {(char* )"lrCheck",                 &gConfig_stereoVision[0].lrCheck  , INT_8, SINGLE},
        {(char* )"isRectifyMapInEveFormat", &gConfig_stereoVision[0].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"saveRectifyMapInEveFormat", &gConfig_stereoVision[0].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"enableRectify",    		&gConfig_stereoVision[0].enableRectify  , INT_8, SINGLE},
        {(char* )"remapLeft",           	&gConfig_stereoVision[0].remapLeft         , STRING, SINGLE},
        {(char* )"remapRight",           	&gConfig_stereoVision[0].remapRight         , STRING, SINGLE},
        {(char* )"disparityOffset",         &gConfig_stereoVision[0].disparityOffset    , STRING, SINGLE},
        
        {(char* )"0inImageLeft",           &gConfig_stereoVision[0].inImageLeft         , STRING, SINGLE},
        {(char* )"0inImageRight",          &gConfig_stereoVision[0].inImageRight        , STRING, SINGLE},
        {(char* )"0gtImage",               &gConfig_stereoVision[0].gtImage             , STRING, SINGLE},
        {(char* )"0gtScale",               &gConfig_stereoVision[0].gtScale             , INT_8 , SINGLE},
        {(char* )"0stereoMode",            &gConfig_stereoVision[0].stereoMode          , STRING , SINGLE},
        {(char* )"0imageWidth",         &gConfig_stereoVision[0].imageWidth       , INT_32, SINGLE},
        {(char* )"0imageHeight",        &gConfig_stereoVision[0].imageHeight      , INT_32, SINGLE},
        {(char* )"0srcImagePitch",         &gConfig_stereoVision[0].srcImagePitch       , INT_32, SINGLE},
        {(char* )"0remapWidth",         &gConfig_stereoVision[0].remapWidth       , INT_32, SINGLE},
        {(char* )"0remapHeight",        &gConfig_stereoVision[0].remapHeight      , INT_32, SINGLE},

        {(char* )"0outImage",              &gConfig_stereoVision[0].outImage            , STRING, SINGLE},
        {(char* )"0dstImagePitch",         &gConfig_stereoVision[0].dstImagePitch       , INT_32, SINGLE},
        {(char* )"0pattern",               &gConfig_stereoVision[0].pattern             , INT_8 , SINGLE},
        {(char* )"0inputBitDepth",         &gConfig_stereoVision[0].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"0censusWinWidth",        &gConfig_stereoVision[0].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"0censusWinHeight",       &gConfig_stereoVision[0].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"0censusWinHorzStep",     &gConfig_stereoVision[0].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"0censusWinVertStep",     &gConfig_stereoVision[0].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"0disparityWinWidth",     &gConfig_stereoVision[0].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"0disparityWinHeight",    &gConfig_stereoVision[0].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"0numDisparities",        &gConfig_stereoVision[0].numDisparities      , INT_16 , SINGLE},
        {(char* )"0disparityStep",         &gConfig_stereoVision[0].disparityStep       , INT_8 , SINGLE},
        {(char* )"0maxMinCostRatio",       &gConfig_stereoVision[0].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"0offset_x",         &gConfig_stereoVision[0].offset_x       , INT_32, SINGLE},
        {(char* )"0offset_y",         &gConfig_stereoVision[0].offset_y       , INT_32, SINGLE},
        {(char* )"0searchDir",    &gConfig_stereoVision[0].searchDir  , INT_8, SINGLE},
        {(char* )"0lrCheck",                 &gConfig_stereoVision[0].lrCheck  , INT_8, SINGLE},
        {(char* )"0isRectifyMapInEveFormat", &gConfig_stereoVision[0].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"0saveRectifyMapInEveFormat", &gConfig_stereoVision[0].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"0enableRectify",    		&gConfig_stereoVision[0].enableRectify  , INT_8, SINGLE},
        {(char* )"0remapLeft",           	&gConfig_stereoVision[0].remapLeft         , STRING, SINGLE},
        {(char* )"0remapRight",           	&gConfig_stereoVision[0].remapRight         , STRING, SINGLE},
        {(char* )"0disparityOffset",        &gConfig_stereoVision[0].disparityOffset    , STRING, SINGLE},

        {(char* )"1inImageLeft",           &gConfig_stereoVision[1].inImageLeft         , STRING, SINGLE},
        {(char* )"1inImageRight",          &gConfig_stereoVision[1].inImageRight        , STRING, SINGLE},
        {(char* )"1gtImage",               &gConfig_stereoVision[1].gtImage             , STRING, SINGLE},
        {(char* )"1gtScale",               &gConfig_stereoVision[1].gtScale             , INT_8 , SINGLE},
        {(char* )"1stereoMode",            &gConfig_stereoVision[1].stereoMode          , STRING , SINGLE},
        {(char* )"1imageWidth",         &gConfig_stereoVision[1].imageWidth       , INT_32, SINGLE},
        {(char* )"1imageHeight",        &gConfig_stereoVision[1].imageHeight      , INT_32, SINGLE},
        {(char* )"1srcImagePitch",         &gConfig_stereoVision[1].srcImagePitch       , INT_32, SINGLE},
        {(char* )"1remapWidth",         &gConfig_stereoVision[1].remapWidth       , INT_32, SINGLE},
        {(char* )"1remapHeight",        &gConfig_stereoVision[1].remapHeight      , INT_32, SINGLE},

        {(char* )"1outImage",              &gConfig_stereoVision[1].outImage            , STRING, SINGLE},
        {(char* )"1dstImagePitch",         &gConfig_stereoVision[1].dstImagePitch       , INT_32, SINGLE},
        {(char* )"1pattern",               &gConfig_stereoVision[1].pattern             , INT_8 , SINGLE},
        {(char* )"1inputBitDepth",         &gConfig_stereoVision[1].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"1censusWinWidth",        &gConfig_stereoVision[1].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"1censusWinHeight",       &gConfig_stereoVision[1].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"1censusWinHorzStep",     &gConfig_stereoVision[1].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"1censusWinVertStep",     &gConfig_stereoVision[1].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"1disparityWinWidth",     &gConfig_stereoVision[1].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"1disparityWinHeight",    &gConfig_stereoVision[1].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"1numDisparities",        &gConfig_stereoVision[1].numDisparities      , INT_16 , SINGLE},
        {(char* )"1disparityStep",         &gConfig_stereoVision[1].disparityStep       , INT_8 , SINGLE},
        {(char* )"1maxMinCostRatio",       &gConfig_stereoVision[1].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"1offset_x",         &gConfig_stereoVision[1].offset_x       , INT_32, SINGLE},
        {(char* )"1offset_y",         &gConfig_stereoVision[1].offset_y       , INT_32, SINGLE},
        {(char* )"1searchDir",    &gConfig_stereoVision[1].searchDir  , INT_8, SINGLE},
        {(char* )"1lrCheck",                 &gConfig_stereoVision[1].lrCheck  , INT_8, SINGLE},
        {(char* )"1isRectifyMapInEveFormat", &gConfig_stereoVision[1].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"1saveRectifyMapInEveFormat", &gConfig_stereoVision[1].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"1enableRectify",    		&gConfig_stereoVision[1].enableRectify  , INT_8, SINGLE},
        {(char* )"1remapLeft",           	&gConfig_stereoVision[1].remapLeft         , STRING, SINGLE},
        {(char* )"1remapRight",           	&gConfig_stereoVision[1].remapRight         , STRING, SINGLE},
        {(char* )"1disparityOffset",         &gConfig_stereoVision[1].disparityOffset    , STRING, SINGLE},
        
        {(char* )"2inImageLeft",           &gConfig_stereoVision[2].inImageLeft         , STRING, SINGLE},
        {(char* )"2inImageRight",          &gConfig_stereoVision[2].inImageRight        , STRING, SINGLE},
        {(char* )"2gtImage",               &gConfig_stereoVision[2].gtImage             , STRING, SINGLE},
        {(char* )"2gtScale",               &gConfig_stereoVision[2].gtScale             , INT_8 , SINGLE},
        {(char* )"2stereoMode",            &gConfig_stereoVision[2].stereoMode          , STRING , SINGLE},
        {(char* )"2imageWidth",         &gConfig_stereoVision[2].imageWidth       , INT_32, SINGLE},
        {(char* )"2imageHeight",        &gConfig_stereoVision[2].imageHeight      , INT_32, SINGLE},
        {(char* )"2srcImagePitch",         &gConfig_stereoVision[2].srcImagePitch       , INT_32, SINGLE},
        {(char* )"2remapWidth",          &gConfig_stereoVision[2].remapWidth       , INT_32, SINGLE},
        {(char* )"2remapHeight",         &gConfig_stereoVision[2].remapHeight      , INT_32, SINGLE},

        {(char* )"2outImage",              &gConfig_stereoVision[2].outImage            , STRING, SINGLE},
        {(char* )"2dstImagePitch",         &gConfig_stereoVision[2].dstImagePitch       , INT_32, SINGLE},
        {(char* )"2pattern",               &gConfig_stereoVision[2].pattern             , INT_8 , SINGLE},
        {(char* )"2inputBitDepth",         &gConfig_stereoVision[2].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"2censusWinWidth",        &gConfig_stereoVision[2].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"2censusWinHeight",       &gConfig_stereoVision[2].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"2censusWinHorzStep",     &gConfig_stereoVision[2].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"2censusWinVertStep",     &gConfig_stereoVision[2].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"2disparityWinWidth",     &gConfig_stereoVision[2].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"2disparityWinHeight",    &gConfig_stereoVision[2].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"2numDisparities",        &gConfig_stereoVision[2].numDisparities      , INT_16 , SINGLE},
        {(char* )"2disparityStep",         &gConfig_stereoVision[2].disparityStep       , INT_8 , SINGLE},
        {(char* )"2maxMinCostRatio",       &gConfig_stereoVision[2].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"2offset_x",         &gConfig_stereoVision[2].offset_x       , INT_32, SINGLE},
        {(char* )"2offset_y",         &gConfig_stereoVision[2].offset_y       , INT_32, SINGLE},
        {(char* )"2searchDir",    &gConfig_stereoVision[2].searchDir  , INT_8, SINGLE},
        {(char* )"2lrCheck",                 &gConfig_stereoVision[2].lrCheck  , INT_8, SINGLE},
        {(char* )"2isRectifyMapInEveFormat", &gConfig_stereoVision[2].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"2saveRectifyMapInEveFormat", &gConfig_stereoVision[2].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"2enableRectify",    		&gConfig_stereoVision[2].enableRectify  , INT_8, SINGLE},
        {(char* )"2remapLeft",           	&gConfig_stereoVision[2].remapLeft         , STRING, SINGLE},
        {(char* )"2remapRight",           	&gConfig_stereoVision[2].remapRight         , STRING, SINGLE},
        {(char* )"2disparityOffset",        &gConfig_stereoVision[2].disparityOffset    , STRING, SINGLE},
        
        {(char* )"3inImageLeft",           &gConfig_stereoVision[3].inImageLeft         , STRING, SINGLE},
        {(char* )"3inImageRight",          &gConfig_stereoVision[3].inImageRight        , STRING, SINGLE},
        {(char* )"3gtImage",               &gConfig_stereoVision[3].gtImage             , STRING, SINGLE},
        {(char* )"3gtScale",               &gConfig_stereoVision[3].gtScale             , INT_8 , SINGLE},
        {(char* )"3stereoMode",            &gConfig_stereoVision[3].stereoMode          , STRING , SINGLE},
        {(char* )"3imageWidth",         &gConfig_stereoVision[3].imageWidth       , INT_32, SINGLE},
        {(char* )"3imageHeight",        &gConfig_stereoVision[3].imageHeight      , INT_32, SINGLE},
        {(char* )"3srcImagePitch",         &gConfig_stereoVision[3].srcImagePitch       , INT_32, SINGLE},
        {(char* )"3remapWidth",          &gConfig_stereoVision[3].remapWidth       , INT_32, SINGLE},
        {(char* )"3remapHeight",         &gConfig_stereoVision[3].remapHeight      , INT_32, SINGLE},

        {(char* )"3outImage",              &gConfig_stereoVision[3].outImage            , STRING, SINGLE},
        {(char* )"3dstImagePitch",         &gConfig_stereoVision[3].dstImagePitch       , INT_32, SINGLE},
        {(char* )"3pattern",               &gConfig_stereoVision[3].pattern             , INT_8 , SINGLE},
        {(char* )"3inputBitDepth",         &gConfig_stereoVision[3].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"3censusWinWidth",        &gConfig_stereoVision[3].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"3censusWinHeight",       &gConfig_stereoVision[3].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"3censusWinHorzStep",     &gConfig_stereoVision[3].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"3censusWinVertStep",     &gConfig_stereoVision[3].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"3disparityWinWidth",     &gConfig_stereoVision[3].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"3disparityWinHeight",    &gConfig_stereoVision[3].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"3numDisparities",        &gConfig_stereoVision[3].numDisparities      , INT_16 , SINGLE},
        {(char* )"3disparityStep",         &gConfig_stereoVision[3].disparityStep       , INT_8 , SINGLE},
        {(char* )"3maxMinCostRatio",       &gConfig_stereoVision[3].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"3offset_x",         &gConfig_stereoVision[3].offset_x       , INT_32, SINGLE},
        {(char* )"3offset_y",         &gConfig_stereoVision[3].offset_y       , INT_32, SINGLE},
        {(char* )"3searchDir",    &gConfig_stereoVision[3].searchDir  , INT_8, SINGLE},
        {(char* )"3lrCheck",                 &gConfig_stereoVision[3].lrCheck  , INT_8, SINGLE},
        {(char* )"3isRectifyMapInEveFormat", &gConfig_stereoVision[3].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"3saveRectifyMapInEveFormat", &gConfig_stereoVision[3].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"3enableRectify",    		&gConfig_stereoVision[3].enableRectify  , INT_8, SINGLE},
        {(char* )"3remapLeft",           	&gConfig_stereoVision[3].remapLeft         , STRING, SINGLE},
        {(char* )"3remapRight",           	&gConfig_stereoVision[3].remapRight         , STRING, SINGLE},
        {(char* )"3disparityOffset",        &gConfig_stereoVision[3].disparityOffset    , STRING, SINGLE},
        
        {(char* )"4inImageLeft",           &gConfig_stereoVision[4].inImageLeft         , STRING, SINGLE},
        {(char* )"4inImageRight",          &gConfig_stereoVision[4].inImageRight        , STRING, SINGLE},
        {(char* )"4gtImage",               &gConfig_stereoVision[4].gtImage             , STRING, SINGLE},
        {(char* )"4gtScale",               &gConfig_stereoVision[4].gtScale             , INT_8 , SINGLE},
        {(char* )"4stereoMode",            &gConfig_stereoVision[4].stereoMode          , STRING , SINGLE},
        {(char* )"4imageWidth",         &gConfig_stereoVision[4].imageWidth       , INT_32, SINGLE},
        {(char* )"4imageHeight",        &gConfig_stereoVision[4].imageHeight      , INT_32, SINGLE},
        {(char* )"4srcImagePitch",         &gConfig_stereoVision[4].srcImagePitch       , INT_32, SINGLE},
        {(char* )"4remapWidth",         &gConfig_stereoVision[4].remapWidth       , INT_32, SINGLE},
        {(char* )"4remapHeight",        &gConfig_stereoVision[4].remapHeight      , INT_32, SINGLE},

        {(char* )"4outImage",              &gConfig_stereoVision[4].outImage            , STRING, SINGLE},
        {(char* )"4dstImagePitch",         &gConfig_stereoVision[4].dstImagePitch       , INT_32, SINGLE},
        {(char* )"4pattern",               &gConfig_stereoVision[4].pattern             , INT_8 , SINGLE},
        {(char* )"4inputBitDepth",         &gConfig_stereoVision[4].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"4censusWinWidth",        &gConfig_stereoVision[4].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"4censusWinHeight",       &gConfig_stereoVision[4].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"4censusWinHorzStep",     &gConfig_stereoVision[4].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"4censusWinVertStep",     &gConfig_stereoVision[4].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"4disparityWinWidth",     &gConfig_stereoVision[4].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"4disparityWinHeight",    &gConfig_stereoVision[4].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"4numDisparities",        &gConfig_stereoVision[4].numDisparities      , INT_16 , SINGLE},
        {(char* )"4disparityStep",         &gConfig_stereoVision[4].disparityStep       , INT_8 , SINGLE},
        {(char* )"4maxMinCostRatio",       &gConfig_stereoVision[4].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"4offset_x",         &gConfig_stereoVision[4].offset_x       , INT_32, SINGLE},
        {(char* )"4offset_y",         &gConfig_stereoVision[4].offset_y       , INT_32, SINGLE},
        {(char* )"4searchDir",    &gConfig_stereoVision[4].searchDir  , INT_8, SINGLE},
        {(char* )"4lrCheck",                 &gConfig_stereoVision[4].lrCheck  , INT_8, SINGLE},
        {(char* )"4isRectifyMapInEveFormat", &gConfig_stereoVision[4].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"4saveRectifyMapInEveFormat", &gConfig_stereoVision[4].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"4enableRectify",    		&gConfig_stereoVision[4].enableRectify  , INT_8, SINGLE},
        {(char* )"4remapLeft",           	&gConfig_stereoVision[4].remapLeft         , STRING, SINGLE},
        {(char* )"4remapRight",           	&gConfig_stereoVision[4].remapRight         , STRING, SINGLE},
        {(char* )"4disparityOffset",        &gConfig_stereoVision[4].disparityOffset    , STRING, SINGLE},
        
        {(char* )"5inImageLeft",           &gConfig_stereoVision[5].inImageLeft         , STRING, SINGLE},
        {(char* )"5inImageRight",          &gConfig_stereoVision[5].inImageRight        , STRING, SINGLE},
        {(char* )"5gtImage",               &gConfig_stereoVision[5].gtImage             , STRING, SINGLE},
        {(char* )"5gtScale",               &gConfig_stereoVision[5].gtScale             , INT_8 , SINGLE},
        {(char* )"5stereoMode",            &gConfig_stereoVision[5].stereoMode          , STRING , SINGLE},
        {(char* )"5imageWidth",         &gConfig_stereoVision[5].imageWidth       , INT_32, SINGLE},
        {(char* )"5imageHeight",        &gConfig_stereoVision[5].imageHeight      , INT_32, SINGLE},
        {(char* )"5srcImagePitch",         &gConfig_stereoVision[5].srcImagePitch       , INT_32, SINGLE},
        {(char* )"5remapWidth",         &gConfig_stereoVision[5].remapWidth       , INT_32, SINGLE},
        {(char* )"5remapHeight",        &gConfig_stereoVision[5].remapHeight      , INT_32, SINGLE},

        {(char* )"5outImage",              &gConfig_stereoVision[5].outImage            , STRING, SINGLE},
        {(char* )"5dstImagePitch",         &gConfig_stereoVision[5].dstImagePitch       , INT_32, SINGLE},
        {(char* )"5pattern",               &gConfig_stereoVision[5].pattern             , INT_8 , SINGLE},
        {(char* )"5inputBitDepth",         &gConfig_stereoVision[5].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"5censusWinWidth",        &gConfig_stereoVision[5].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"5censusWinHeight",       &gConfig_stereoVision[5].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"5censusWinHorzStep",     &gConfig_stereoVision[5].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"5censusWinVertStep",     &gConfig_stereoVision[5].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"5disparityWinWidth",     &gConfig_stereoVision[5].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"5disparityWinHeight",    &gConfig_stereoVision[5].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"5numDisparities",        &gConfig_stereoVision[5].numDisparities      , INT_16 , SINGLE},
        {(char* )"5disparityStep",         &gConfig_stereoVision[5].disparityStep       , INT_8 , SINGLE},
        {(char* )"5maxMinCostRatio",       &gConfig_stereoVision[5].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"5offset_x",         &gConfig_stereoVision[5].offset_x       , INT_32, SINGLE},
        {(char* )"5offset_y",         &gConfig_stereoVision[5].offset_y       , INT_32, SINGLE},
        {(char* )"5searchDir",    &gConfig_stereoVision[5].searchDir  , INT_8, SINGLE},
        {(char* )"5lrCheck",                 &gConfig_stereoVision[5].lrCheck  , INT_8, SINGLE},
        {(char* )"5isRectifyMapInEveFormat", &gConfig_stereoVision[5].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"5saveRectifyMapInEveFormat", &gConfig_stereoVision[5].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"5enableRectify",    		&gConfig_stereoVision[5].enableRectify  , INT_8, SINGLE},
        {(char* )"5remapLeft",           	&gConfig_stereoVision[5].remapLeft         , STRING, SINGLE},
        {(char* )"5remapRight",           	&gConfig_stereoVision[5].remapRight         , STRING, SINGLE},
        {(char* )"5disparityOffset",        &gConfig_stereoVision[5].disparityOffset    , STRING, SINGLE},
        
        {(char* )"6inImageLeft",           &gConfig_stereoVision[6].inImageLeft         , STRING, SINGLE},
        {(char* )"6inImageRight",          &gConfig_stereoVision[6].inImageRight        , STRING, SINGLE},
        {(char* )"6gtImage",               &gConfig_stereoVision[6].gtImage             , STRING, SINGLE},
        {(char* )"6gtScale",               &gConfig_stereoVision[6].gtScale             , INT_8 , SINGLE},
        {(char* )"6stereoMode",            &gConfig_stereoVision[6].stereoMode          , STRING , SINGLE},
        {(char* )"6imageWidth",         &gConfig_stereoVision[6].imageWidth       , INT_32, SINGLE},
        {(char* )"6imageHeight",        &gConfig_stereoVision[6].imageHeight      , INT_32, SINGLE},
        {(char* )"6srcImagePitch",         &gConfig_stereoVision[6].srcImagePitch       , INT_32, SINGLE},
        {(char* )"6remapWidth",         &gConfig_stereoVision[6].remapWidth       , INT_32, SINGLE},
        {(char* )"6remapHeight",        &gConfig_stereoVision[6].remapHeight      , INT_32, SINGLE},

        {(char* )"6outImage",              &gConfig_stereoVision[6].outImage            , STRING, SINGLE},
        {(char* )"6dstImagePitch",         &gConfig_stereoVision[6].dstImagePitch       , INT_32, SINGLE},
        {(char* )"6pattern",               &gConfig_stereoVision[6].pattern             , INT_8 , SINGLE},
        {(char* )"6inputBitDepth",         &gConfig_stereoVision[6].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"6censusWinWidth",        &gConfig_stereoVision[6].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"6censusWinHeight",       &gConfig_stereoVision[6].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"6censusWinHorzStep",     &gConfig_stereoVision[6].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"6censusWinVertStep",     &gConfig_stereoVision[6].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"6disparityWinWidth",     &gConfig_stereoVision[6].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"6disparityWinHeight",    &gConfig_stereoVision[6].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"6numDisparities",        &gConfig_stereoVision[6].numDisparities      , INT_16 , SINGLE},
        {(char* )"6disparityStep",         &gConfig_stereoVision[6].disparityStep       , INT_8 , SINGLE},
        {(char* )"6maxMinCostRatio",       &gConfig_stereoVision[6].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"6offset_x",         &gConfig_stereoVision[6].offset_x       , INT_32, SINGLE},
        {(char* )"6offset_y",         &gConfig_stereoVision[6].offset_y       , INT_32, SINGLE},
        {(char* )"6searchDir",    &gConfig_stereoVision[6].searchDir  , INT_8, SINGLE},
        {(char* )"6lrCheck",                 &gConfig_stereoVision[6].lrCheck  , INT_8, SINGLE},
        {(char* )"6isRectifyMapInEveFormat", &gConfig_stereoVision[6].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"7saveRectifyMapInEveFormat", &gConfig_stereoVision[7].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"6enableRectify",    		&gConfig_stereoVision[6].enableRectify  , INT_8, SINGLE},
        {(char* )"6remapLeft",           	&gConfig_stereoVision[6].remapLeft         , STRING, SINGLE},
        {(char* )"6remapRight",           	&gConfig_stereoVision[6].remapRight         , STRING, SINGLE},
        {(char* )"6disparityOffset",        &gConfig_stereoVision[6].disparityOffset    , STRING, SINGLE},
        
        {(char* )"7inImageLeft",           &gConfig_stereoVision[7].inImageLeft         , STRING, SINGLE},
        {(char* )"7inImageRight",          &gConfig_stereoVision[7].inImageRight        , STRING, SINGLE},
        {(char* )"7gtImage",               &gConfig_stereoVision[7].gtImage             , STRING, SINGLE},
        {(char* )"7gtScale",               &gConfig_stereoVision[7].gtScale             , INT_8 , SINGLE},
        {(char* )"7stereoMode",            &gConfig_stereoVision[7].stereoMode          , STRING , SINGLE},
        {(char* )"7imageWidth",         &gConfig_stereoVision[7].imageWidth       , INT_32, SINGLE},
        {(char* )"7imageHeight",        &gConfig_stereoVision[7].imageHeight      , INT_32, SINGLE},
        {(char* )"7srcImagePitch",         &gConfig_stereoVision[7].srcImagePitch       , INT_32, SINGLE},
        {(char* )"7remapWidth",         &gConfig_stereoVision[7].remapWidth       , INT_32, SINGLE},
        {(char* )"7remapHeight",        &gConfig_stereoVision[7].remapHeight      , INT_32, SINGLE},

        {(char* )"7outImage",              &gConfig_stereoVision[7].outImage            , STRING, SINGLE},
        {(char* )"7dstImagePitch",         &gConfig_stereoVision[7].dstImagePitch       , INT_32, SINGLE},
        {(char* )"7pattern",               &gConfig_stereoVision[7].pattern             , INT_8 , SINGLE},
        {(char* )"7inputBitDepth",         &gConfig_stereoVision[7].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"7censusWinWidth",        &gConfig_stereoVision[7].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"7censusWinHeight",       &gConfig_stereoVision[7].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"7censusWinHorzStep",     &gConfig_stereoVision[7].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"7censusWinVertStep",     &gConfig_stereoVision[7].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"7disparityWinWidth",     &gConfig_stereoVision[7].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"7disparityWinHeight",    &gConfig_stereoVision[7].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"7numDisparities",        &gConfig_stereoVision[7].numDisparities      , INT_16 , SINGLE},
        {(char* )"7disparityStep",         &gConfig_stereoVision[7].disparityStep       , INT_8 , SINGLE},
        {(char* )"7maxMinCostRatio",       &gConfig_stereoVision[7].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"7offset_x",         &gConfig_stereoVision[7].offset_x       , INT_32, SINGLE},
        {(char* )"7offset_y",         &gConfig_stereoVision[7].offset_y       , INT_32, SINGLE},
        {(char* )"7searchDir",    &gConfig_stereoVision[7].searchDir  , INT_8, SINGLE},
        {(char* )"7lrCheck",                 &gConfig_stereoVision[7].lrCheck  , INT_8, SINGLE},
        {(char* )"7isRectifyMapInEveFormat", &gConfig_stereoVision[7].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"7enableRectify",    		&gConfig_stereoVision[7].enableRectify  , INT_8, SINGLE},
        {(char* )"7remapLeft",           	&gConfig_stereoVision[7].remapLeft         , STRING, SINGLE},
        {(char* )"7remapRight",           	&gConfig_stereoVision[7].remapRight         , STRING, SINGLE},
        {(char* )"7disparityOffset",        &gConfig_stereoVision[7].disparityOffset    , STRING, SINGLE},

        {(char* )"8inImageLeft",           &gConfig_stereoVision[8].inImageLeft         , STRING, SINGLE},
        {(char* )"8inImageRight",          &gConfig_stereoVision[8].inImageRight        , STRING, SINGLE},
        {(char* )"8gtImage",               &gConfig_stereoVision[8].gtImage             , STRING, SINGLE},
        {(char* )"8gtScale",               &gConfig_stereoVision[8].gtScale             , INT_8 , SINGLE},
        {(char* )"8stereoMode",            &gConfig_stereoVision[8].stereoMode          , STRING , SINGLE},
        {(char* )"8imageWidth",            &gConfig_stereoVision[8].imageWidth       , INT_32, SINGLE},
        {(char* )"8imageHeight",           &gConfig_stereoVision[8].imageHeight      , INT_32, SINGLE},
        {(char* )"8srcImagePitch",         &gConfig_stereoVision[8].srcImagePitch       , INT_32, SINGLE},
        {(char* )"8remapWidth",            &gConfig_stereoVision[8].remapWidth       , INT_32, SINGLE},
        {(char* )"8remapHeight",           &gConfig_stereoVision[8].remapHeight      , INT_32, SINGLE},
        
        {(char* )"8outImage",              &gConfig_stereoVision[8].outImage            , STRING, SINGLE},
        {(char* )"8dstImagePitch",         &gConfig_stereoVision[8].dstImagePitch       , INT_32, SINGLE},
        {(char* )"8pattern",               &gConfig_stereoVision[8].pattern             , INT_8 , SINGLE},
        {(char* )"8inputBitDepth",         &gConfig_stereoVision[8].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"8censusWinWidth",        &gConfig_stereoVision[8].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"8censusWinHeight",       &gConfig_stereoVision[8].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"8censusWinHorzStep",     &gConfig_stereoVision[8].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"8censusWinVertStep",     &gConfig_stereoVision[8].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"8disparityWinWidth",     &gConfig_stereoVision[8].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"8disparityWinHeight",    &gConfig_stereoVision[8].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"8numDisparities",        &gConfig_stereoVision[8].numDisparities      , INT_16 , SINGLE},
        {(char* )"8disparityStep",         &gConfig_stereoVision[8].disparityStep       , INT_8 , SINGLE},
        {(char* )"8maxMinCostRatio",       &gConfig_stereoVision[8].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"8offset_x",                &gConfig_stereoVision[8].offset_x       , INT_32, SINGLE},
        {(char* )"8offset_y",                &gConfig_stereoVision[8].offset_y       , INT_32, SINGLE},
        {(char* )"8searchDir",               &gConfig_stereoVision[8].searchDir  , INT_8, SINGLE},
        {(char* )"8lrCheck",                 &gConfig_stereoVision[8].lrCheck  , INT_8, SINGLE},
        {(char* )"8isRectifyMapInEveFormat", &gConfig_stereoVision[8].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"8saveRectifyMapInEveFormat", &gConfig_stereoVision[8].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"8enableRectify",    		&gConfig_stereoVision[8].enableRectify  , INT_8, SINGLE},
        {(char* )"8remapLeft",           	&gConfig_stereoVision[8].remapLeft         , STRING, SINGLE},
        {(char* )"8remapRight",           	&gConfig_stereoVision[8].remapRight         , STRING, SINGLE},
        {(char* )"8disparityOffset",        &gConfig_stereoVision[8].disparityOffset    , STRING, SINGLE},
        
        {(char* )"9inImageLeft",           &gConfig_stereoVision[9].inImageLeft         , STRING, SINGLE},
        {(char* )"9inImageRight",          &gConfig_stereoVision[9].inImageRight        , STRING, SINGLE},
        {(char* )"9gtImage",               &gConfig_stereoVision[9].gtImage             , STRING, SINGLE},
        {(char* )"9gtScale",               &gConfig_stereoVision[9].gtScale             , INT_8 , SINGLE},
        {(char* )"9stereoMode",            &gConfig_stereoVision[9].stereoMode          , STRING , SINGLE},
        {(char* )"9imageWidth",            &gConfig_stereoVision[9].imageWidth       , INT_32, SINGLE},
        {(char* )"9imageHeight",           &gConfig_stereoVision[9].imageHeight      , INT_32, SINGLE},
        {(char* )"9srcImagePitch",         &gConfig_stereoVision[9].srcImagePitch       , INT_32, SINGLE},
        {(char* )"9remapWidth",            &gConfig_stereoVision[9].remapWidth       , INT_32, SINGLE},
        {(char* )"9remapHeight",           &gConfig_stereoVision[9].remapHeight      , INT_32, SINGLE},
        
        {(char* )"9outImage",              &gConfig_stereoVision[9].outImage            , STRING, SINGLE},
        {(char* )"9dstImagePitch",         &gConfig_stereoVision[9].dstImagePitch       , INT_32, SINGLE},
        {(char* )"9pattern",               &gConfig_stereoVision[9].pattern             , INT_8 , SINGLE},
        {(char* )"9inputBitDepth",         &gConfig_stereoVision[9].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"9censusWinWidth",        &gConfig_stereoVision[9].censusWinWidth      , INT_8 , SINGLE},
        {(char* )"9censusWinHeight",       &gConfig_stereoVision[9].censusWinHeight     , INT_8 , SINGLE},
        {(char* )"9censusWinHorzStep",     &gConfig_stereoVision[9].censusWinHorzStep   , INT_8 , SINGLE},
        {(char* )"9censusWinVertStep",     &gConfig_stereoVision[9].censusWinVertStep   , INT_8 , SINGLE},
        {(char* )"9disparityWinWidth",     &gConfig_stereoVision[9].disparityWinWidth   , INT_8 , SINGLE},
        {(char* )"9disparityWinHeight",    &gConfig_stereoVision[9].disparityWinHeight  , INT_8 , SINGLE},
        {(char* )"9numDisparities",        &gConfig_stereoVision[9].numDisparities      , INT_16 , SINGLE},
        {(char* )"9disparityStep",         &gConfig_stereoVision[9].disparityStep       , INT_8 , SINGLE},
        {(char* )"9maxMinCostRatio",       &gConfig_stereoVision[9].maxMinCostRatio     , FLOAT , SINGLE},
        {(char* )"9offset_x",                &gConfig_stereoVision[9].offset_x       , INT_32, SINGLE},
        {(char* )"9offset_y",                &gConfig_stereoVision[9].offset_y       , INT_32, SINGLE},
        {(char* )"9searchDir",               &gConfig_stereoVision[9].searchDir  , INT_8, SINGLE},
        {(char* )"9lrCheck",                 &gConfig_stereoVision[9].lrCheck  , INT_8, SINGLE},
        {(char* )"9isRectifyMapInEveFormat", &gConfig_stereoVision[9].isRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"9saveRectifyMapInEveFormat", &gConfig_stereoVision[9].saveRectifyMapInEveFormat  , INT_8, SINGLE},
        {(char* )"9enableRectify",          &gConfig_stereoVision[9].enableRectify  , INT_8, SINGLE},
        {(char* )"9remapLeft",              &gConfig_stereoVision[9].remapLeft         , STRING, SINGLE},
        {(char* )"9remapRight",             &gConfig_stereoVision[9].remapRight         , STRING, SINGLE},
        {(char* )"9disparityOffset",        &gConfig_stereoVision[9].disparityOffset    , STRING, SINGLE},
} ;
