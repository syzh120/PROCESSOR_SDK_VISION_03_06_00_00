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
#include "blockSort_u32_config.h"
#pragma RESET_MISRA ("required")

uint32_t blockSort_u32_numTestCases;

sblockSort_u32_Config gConfig_blockSort_u32[EVELIB_BLOCKSORT_NUM_TESTCASES];

sTokenMapping gsTokenMap_blockSort_u32[] =
{
        {(char* )"numTestCases",           &blockSort_u32_numTestCases                       , INT_32, SINGLE},

        {(char* )"0inImage",               &gConfig_blockSort_u32[0].inImage              , STRING, SINGLE},
        {(char* )"0srcImageWidth",          &gConfig_blockSort_u32[0].srcImageWidth       , INT_32, SINGLE},
        {(char* )"0srcImageHeight",         &gConfig_blockSort_u32[0].srcImageHeight      , INT_32, SINGLE},
        {(char* )"0srcImagePitch",         &gConfig_blockSort_u32[0].srcImagePitch       , INT_32, SINGLE},

        {(char* )"0outImage",              &gConfig_blockSort_u32[0].outImage           , STRING, SINGLE},
        {(char* )"0dstImagePitch",         &gConfig_blockSort_u32[0].dstImagePitch      , INT_32, SINGLE},
        {(char* )"0blockWidth",         &gConfig_blockSort_u32[0].blockWidth      , INT_16, SINGLE},
        {(char* )"0blockHeight",         &gConfig_blockSort_u32[0].blockHeight      , INT_16, SINGLE},
        {(char* )"0pattern",                &gConfig_blockSort_u32[0].pattern             , INT_32 , SINGLE},
        {(char* )"0testCaseName",          &gConfig_blockSort_u32[0].testCaseName         , STRING, SINGLE},
        {(char* )"0performanceTestcase",   &gConfig_blockSort_u32[0].performanceTestcase  , INT_32, SINGLE},
        {(char* )"0desc",                  &gConfig_blockSort_u32[0].desc                 , STRING, SINGLE},

        {(char* )"1inImage",               &gConfig_blockSort_u32[1].inImage              , STRING, SINGLE},
        {(char* )"1srcImageWidth",          &gConfig_blockSort_u32[1].srcImageWidth       , INT_32, SINGLE},
        {(char* )"1srcImageHeight",         &gConfig_blockSort_u32[1].srcImageHeight      , INT_32, SINGLE},
        {(char* )"1srcImagePitch",         &gConfig_blockSort_u32[1].srcImagePitch       , INT_32, SINGLE},

        {(char* )"1outImage",              &gConfig_blockSort_u32[1].outImage           , STRING, SINGLE},
        {(char* )"1dstImagePitch",         &gConfig_blockSort_u32[1].dstImagePitch      , INT_32, SINGLE},
        {(char* )"1blockWidth",         &gConfig_blockSort_u32[1].blockWidth      , INT_16, SINGLE},
        {(char* )"1blockHeight",         &gConfig_blockSort_u32[1].blockHeight      , INT_16, SINGLE},
        {(char* )"1pattern",                &gConfig_blockSort_u32[1].pattern             , INT_32 , SINGLE},
        {(char* )"1testCaseName",          &gConfig_blockSort_u32[1].testCaseName         , STRING, SINGLE},
        {(char* )"1performanceTestcase",   &gConfig_blockSort_u32[1].performanceTestcase  , INT_32, SINGLE},
        {(char* )"1desc",                  &gConfig_blockSort_u32[1].desc                 , STRING, SINGLE},

        {(char* )"2inImage",               &gConfig_blockSort_u32[2].inImage              , STRING, SINGLE},
        {(char* )"2srcImageWidth",          &gConfig_blockSort_u32[2].srcImageWidth       , INT_32, SINGLE},
        {(char* )"2srcImageHeight",         &gConfig_blockSort_u32[2].srcImageHeight      , INT_32, SINGLE},
        {(char* )"2srcImagePitch",         &gConfig_blockSort_u32[2].srcImagePitch       , INT_32, SINGLE},

        {(char* )"2outImage",              &gConfig_blockSort_u32[2].outImage           , STRING, SINGLE},
        {(char* )"2dstImagePitch",         &gConfig_blockSort_u32[2].dstImagePitch      , INT_32, SINGLE},
        {(char* )"2blockWidth",         &gConfig_blockSort_u32[2].blockWidth      , INT_16, SINGLE},
        {(char* )"2blockHeight",         &gConfig_blockSort_u32[2].blockHeight      , INT_16, SINGLE},
        {(char* )"2pattern",                &gConfig_blockSort_u32[2].pattern             , INT_32 , SINGLE},
        {(char* )"2testCaseName",          &gConfig_blockSort_u32[2].testCaseName         , STRING, SINGLE},
        {(char* )"2performanceTestcase",   &gConfig_blockSort_u32[2].performanceTestcase  , INT_32, SINGLE},
        {(char* )"2desc",                  &gConfig_blockSort_u32[2].desc                 , STRING, SINGLE},

        {(char* )"3inImage",               &gConfig_blockSort_u32[3].inImage              , STRING, SINGLE},
        {(char* )"3srcImageWidth",          &gConfig_blockSort_u32[3].srcImageWidth       , INT_32, SINGLE},
        {(char* )"3srcImageHeight",         &gConfig_blockSort_u32[3].srcImageHeight      , INT_32, SINGLE},
        {(char* )"3srcImagePitch",         &gConfig_blockSort_u32[3].srcImagePitch       , INT_32, SINGLE},

        {(char* )"3outImage",              &gConfig_blockSort_u32[3].outImage           , STRING, SINGLE},
        {(char* )"3dstImagePitch",         &gConfig_blockSort_u32[3].dstImagePitch      , INT_32, SINGLE},
        {(char* )"3blockWidth",         &gConfig_blockSort_u32[3].blockWidth      , INT_16, SINGLE},
        {(char* )"3blockHeight",         &gConfig_blockSort_u32[3].blockHeight      , INT_16, SINGLE},
        {(char* )"3pattern",                &gConfig_blockSort_u32[3].pattern             , INT_32 , SINGLE},
        {(char* )"3testCaseName",          &gConfig_blockSort_u32[3].testCaseName         , STRING, SINGLE},
        {(char* )"3performanceTestcase",   &gConfig_blockSort_u32[3].performanceTestcase  , INT_32, SINGLE},
        {(char* )"3desc",                  &gConfig_blockSort_u32[3].desc                 , STRING, SINGLE},

        {(char* )"4inImage",               &gConfig_blockSort_u32[4].inImage              , STRING, SINGLE},
        {(char* )"4srcImageWidth",          &gConfig_blockSort_u32[4].srcImageWidth       , INT_32, SINGLE},
        {(char* )"4srcImageHeight",         &gConfig_blockSort_u32[4].srcImageHeight      , INT_32, SINGLE},
        {(char* )"4srcImagePitch",         &gConfig_blockSort_u32[4].srcImagePitch       , INT_32, SINGLE},

        {(char* )"4outImage",              &gConfig_blockSort_u32[4].outImage           , STRING, SINGLE},
        {(char* )"4dstImagePitch",         &gConfig_blockSort_u32[4].dstImagePitch      , INT_32, SINGLE},
        {(char* )"4blockWidth",         &gConfig_blockSort_u32[4].blockWidth      , INT_16, SINGLE},
        {(char* )"4blockHeight",         &gConfig_blockSort_u32[4].blockHeight      , INT_16, SINGLE},
        {(char* )"4pattern",                &gConfig_blockSort_u32[4].pattern             , INT_32 , SINGLE},
        {(char* )"4testCaseName",          &gConfig_blockSort_u32[4].testCaseName         , STRING, SINGLE},
        {(char* )"4performanceTestcase",   &gConfig_blockSort_u32[4].performanceTestcase  , INT_32, SINGLE},
        {(char* )"4desc",                  &gConfig_blockSort_u32[4].desc                 , STRING, SINGLE},

        {(char* )"5inImage",               &gConfig_blockSort_u32[5].inImage              , STRING, SINGLE},
        {(char* )"5srcImageWidth",          &gConfig_blockSort_u32[5].srcImageWidth       , INT_32, SINGLE},
        {(char* )"5srcImageHeight",         &gConfig_blockSort_u32[5].srcImageHeight      , INT_32, SINGLE},
        {(char* )"5srcImagePitch",         &gConfig_blockSort_u32[5].srcImagePitch       , INT_32, SINGLE},

        {(char* )"5outImage",              &gConfig_blockSort_u32[5].outImage           , STRING, SINGLE},
        {(char* )"5dstImagePitch",         &gConfig_blockSort_u32[5].dstImagePitch      , INT_32, SINGLE},
        {(char* )"5blockWidth",         &gConfig_blockSort_u32[5].blockWidth      , INT_16, SINGLE},
        {(char* )"5blockHeight",         &gConfig_blockSort_u32[5].blockHeight      , INT_16, SINGLE},
        {(char* )"5pattern",                &gConfig_blockSort_u32[5].pattern             , INT_32 , SINGLE},
        {(char* )"5testCaseName",          &gConfig_blockSort_u32[5].testCaseName         , STRING, SINGLE},
        {(char* )"5performanceTestcase",   &gConfig_blockSort_u32[5].performanceTestcase  , INT_32, SINGLE},
        {(char* )"5desc",                  &gConfig_blockSort_u32[5].desc                 , STRING, SINGLE},

        {(char* )"6inImage",               &gConfig_blockSort_u32[6].inImage              , STRING, SINGLE},
        {(char* )"6srcImageWidth",          &gConfig_blockSort_u32[6].srcImageWidth       , INT_32, SINGLE},
        {(char* )"6srcImageHeight",         &gConfig_blockSort_u32[6].srcImageHeight      , INT_32, SINGLE},
        {(char* )"6srcImagePitch",         &gConfig_blockSort_u32[6].srcImagePitch       , INT_32, SINGLE},

        {(char* )"6outImage",              &gConfig_blockSort_u32[6].outImage           , STRING, SINGLE},
        {(char* )"6dstImagePitch",         &gConfig_blockSort_u32[6].dstImagePitch      , INT_32, SINGLE},
        {(char* )"6blockWidth",         &gConfig_blockSort_u32[6].blockWidth      , INT_16, SINGLE},
        {(char* )"6blockHeight",         &gConfig_blockSort_u32[6].blockHeight      , INT_16, SINGLE},
        {(char* )"6pattern",                &gConfig_blockSort_u32[6].pattern             , INT_32 , SINGLE},
        {(char* )"6testCaseName",          &gConfig_blockSort_u32[6].testCaseName         , STRING, SINGLE},
        {(char* )"6performanceTestcase",   &gConfig_blockSort_u32[6].performanceTestcase  , INT_32, SINGLE},
        {(char* )"6desc",                  &gConfig_blockSort_u32[6].desc                 , STRING, SINGLE},

        {(char* )"7inImage",               &gConfig_blockSort_u32[7].inImage              , STRING, SINGLE},
        {(char* )"7srcImageWidth",          &gConfig_blockSort_u32[7].srcImageWidth       , INT_32, SINGLE},
        {(char* )"7srcImageHeight",         &gConfig_blockSort_u32[7].srcImageHeight      , INT_32, SINGLE},
        {(char* )"7srcImagePitch",         &gConfig_blockSort_u32[7].srcImagePitch       , INT_32, SINGLE},

        {(char* )"7outImage",              &gConfig_blockSort_u32[7].outImage           , STRING, SINGLE},
        {(char* )"7dstImagePitch",         &gConfig_blockSort_u32[7].dstImagePitch      , INT_32, SINGLE},
        {(char* )"7blockWidth",         &gConfig_blockSort_u32[7].blockWidth      , INT_16, SINGLE},
        {(char* )"7blockHeight",         &gConfig_blockSort_u32[7].blockHeight      , INT_16, SINGLE},
        {(char* )"7pattern",                &gConfig_blockSort_u32[7].pattern             , INT_32 , SINGLE},
        {(char* )"7testCaseName",          &gConfig_blockSort_u32[7].testCaseName         , STRING, SINGLE},
        {(char* )"7performanceTestcase",   &gConfig_blockSort_u32[7].performanceTestcase  , INT_32, SINGLE},
        {(char* )"7desc",                  &gConfig_blockSort_u32[7].desc                 , STRING, SINGLE},

        {(char* )"8inImage",               &gConfig_blockSort_u32[8].inImage              , STRING, SINGLE},
        {(char* )"8srcImageWidth",          &gConfig_blockSort_u32[8].srcImageWidth       , INT_32, SINGLE},
        {(char* )"8srcImageHeight",         &gConfig_blockSort_u32[8].srcImageHeight      , INT_32, SINGLE},
        {(char* )"8srcImagePitch",         &gConfig_blockSort_u32[8].srcImagePitch       , INT_32, SINGLE},

        {(char* )"8outImage",              &gConfig_blockSort_u32[8].outImage           , STRING, SINGLE},
        {(char* )"8dstImagePitch",         &gConfig_blockSort_u32[8].dstImagePitch      , INT_32, SINGLE},
        {(char* )"8blockWidth",         &gConfig_blockSort_u32[8].blockWidth      , INT_16, SINGLE},
        {(char* )"8blockHeight",         &gConfig_blockSort_u32[8].blockHeight      , INT_16, SINGLE},
        {(char* )"8pattern",                &gConfig_blockSort_u32[8].pattern             , INT_32 , SINGLE},
        {(char* )"8testCaseName",          &gConfig_blockSort_u32[8].testCaseName         , STRING, SINGLE},
        {(char* )"8performanceTestcase",   &gConfig_blockSort_u32[8].performanceTestcase  , INT_32, SINGLE},
        {(char* )"8desc",                  &gConfig_blockSort_u32[8].desc                 , STRING, SINGLE},

        {(char* )"9inImage",               &gConfig_blockSort_u32[9].inImage              , STRING, SINGLE},
        {(char* )"9srcImageWidth",          &gConfig_blockSort_u32[9].srcImageWidth       , INT_32, SINGLE},
        {(char* )"9srcImageHeight",         &gConfig_blockSort_u32[9].srcImageHeight      , INT_32, SINGLE},
        {(char* )"9srcImagePitch",         &gConfig_blockSort_u32[9].srcImagePitch       , INT_32, SINGLE},

        {(char* )"9outImage",              &gConfig_blockSort_u32[9].outImage           , STRING, SINGLE},
        {(char* )"9dstImagePitch",         &gConfig_blockSort_u32[9].dstImagePitch      , INT_32, SINGLE},
        {(char* )"9blockWidth",         &gConfig_blockSort_u32[9].blockWidth      , INT_16, SINGLE},
        {(char* )"9blockHeight",         &gConfig_blockSort_u32[9].blockHeight      , INT_16, SINGLE},
        {(char* )"9pattern",                &gConfig_blockSort_u32[9].pattern             , INT_32 , SINGLE},
        {(char* )"9testCaseName",          &gConfig_blockSort_u32[9].testCaseName         , STRING, SINGLE},
        {(char* )"9performanceTestcase",   &gConfig_blockSort_u32[9].performanceTestcase  , INT_32, SINGLE},
        {(char* )"9desc",                  &gConfig_blockSort_u32[9].desc                 , STRING, SINGLE},



} ;
