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
#include "glcm_config.h"
#pragma RESET_MISRA ("required")

sGlcm_Config gConfig_glcm;

sTokenMapping gsTokenMap_glcm[] =
{
        {(char  * )"inImage",                &gConfig_glcm.inImage               , STRING, SINGLE},
        {(char  * )"srcImageWidth",          &gConfig_glcm.srcImageWidth         , INT_16, SINGLE},
        {(char  * )"srcImageHeight",         &gConfig_glcm.srcImageHeight        , INT_16, SINGLE},
        {(char  * )"srcImagePitch",          &gConfig_glcm.srcImagePitch         , INT_16, SINGLE},

        {(char  * )"outGlcm",                &gConfig_glcm.outGlcm               , STRING, SINGLE},

        {(char  * )"loPixelVal",             &gConfig_glcm.loPixelVal            , INT_8 , SINGLE},
        {(char  * )"hiPixelVal",             &gConfig_glcm.hiPixelVal            , INT_8 , SINGLE},
        {(char  * )"numLevels",              &gConfig_glcm.numLevels             , INT_8 , SINGLE},

        {(char  * )"numDirections",          &gConfig_glcm.numDirections         , INT_8 , SINGLE},
        {(char  * )"rowOffset0",             &gConfig_glcm.rowOffset[0]         , INT_8 , SINGLE},
        {(char  * )"colOffset0",             &gConfig_glcm.colOffset[0]         , INT_8 , SINGLE},
        {(char  * )"rowOffset1",             &gConfig_glcm.rowOffset[1]         , INT_8 , SINGLE},
        {(char  * )"colOffset1",             &gConfig_glcm.colOffset[1]         , INT_8 , SINGLE},
        {(char  * )"rowOffset2",             &gConfig_glcm.rowOffset[2]         , INT_8 , SINGLE},
        {(char  * )"colOffset2",             &gConfig_glcm.colOffset[2]         , INT_8 , SINGLE},
        {(char  * )"rowOffset3",             &gConfig_glcm.rowOffset[3]         , INT_8 , SINGLE},
        {(char  * )"colOffset3",             &gConfig_glcm.colOffset[3]         , INT_8 , SINGLE},
        {(char  * )"rowOffset4",             &gConfig_glcm.rowOffset[4]         , INT_8 , SINGLE},
        {(char  * )"colOffset4",             &gConfig_glcm.colOffset[4]         , INT_8 , SINGLE},
        {(char  * )"rowOffset5",             &gConfig_glcm.rowOffset[5]         , INT_8 , SINGLE},
        {(char  * )"colOffset5",             &gConfig_glcm.colOffset[5]         , INT_8 , SINGLE},
        {(char  * )"rowOffset6",             &gConfig_glcm.rowOffset[6]         , INT_8 , SINGLE},
        {(char  * )"colOffset6",             &gConfig_glcm.colOffset[6]         , INT_8 , SINGLE},
        {(char  * )"rowOffset7",             &gConfig_glcm.rowOffset[7]         , INT_8 , SINGLE},
        {(char  * )"colOffset7",             &gConfig_glcm.colOffset[7]         , INT_8 , SINGLE},

        {(char  * )"randSeed",               &gConfig_glcm.randSeed             , INT_32, SINGLE},
        {(char  * )"testCaseName",           &gConfig_glcm.testCaseName         , STRING, SINGLE},
        {(char  * )"performanceTestcase",    &gConfig_glcm.performanceTestcase  ,  INT_8, SINGLE},
        {(char  * )"desc",                   &gConfig_glcm.testCaseDesc         , STRING, SINGLE},
} ;

