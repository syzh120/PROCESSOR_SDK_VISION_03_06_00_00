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


#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_hough_for_circles_config.h"

sHough_for_circles_Config gConfig_hough_for_circles;
sTokenMapping gsTokenMap_hough_for_circles[] =
{
  {(char* )"gradDir",              &gConfig_hough_for_circles.gradDir              , STRING, SINGLE},
  {(char* )"xyList",               &gConfig_hough_for_circles.xyList               , STRING, SINGLE},
  {(char* )"houghIdx",             &gConfig_hough_for_circles.houghIdx             , STRING, SINGLE},
  {(char* )"testCase",             &gConfig_hough_for_circles.testCase             ,  INT_8, SINGLE},
  {(char* )"listSize",             &gConfig_hough_for_circles.listSize             , INT_16, SINGLE},
  {(char* )"imgWidth",             &gConfig_hough_for_circles.imgWidth             , INT_16, SINGLE},
  {(char* )"imgHeight",            &gConfig_hough_for_circles.imgHeight            , INT_16, SINGLE},
  {(char* )"radius",               &gConfig_hough_for_circles.radius               ,  INT_8, SINGLE},
  {(char* )"houghSpaceDownScale",  &gConfig_hough_for_circles.houghSpaceDownScale  ,  INT_8, SINGLE},
  {(char* )"houghScoreThreshold",  &gConfig_hough_for_circles.houghScoreThreshold  ,  INT_8, SINGLE},
  {(char* )"startX",               &gConfig_hough_for_circles.startX               , INT_16, SINGLE},
  {(char* )"startY",               &gConfig_hough_for_circles.startY               , INT_16, SINGLE},
  {(char* )"randSeedGrad",         &gConfig_hough_for_circles.randSeedGrad         , INT_32, SINGLE},
  {(char* )"randSeedXY",           &gConfig_hough_for_circles.randSeedXY           , INT_32, SINGLE},
  {(char* )"randSeedHoughIdx",     &gConfig_hough_for_circles.randSeedHoughIdx     , INT_32, SINGLE},
  {(char* )"numIter",              &gConfig_hough_for_circles.numIter              ,  INT_8, SINGLE},
} ;

