/*
* module name : Structure From Motion
*
* module descripton : Generates sparse 3D points from optical flow information in camera captured images
*
*/
/*
 
Copyright (c) 2009-2017 Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.
 
Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution
 
Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:
 
*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.
 
*       any redistribution and use are licensed by TI for use only with TI Devices.
 
*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
 
If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:
 
*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.
 
*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.
 
Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.
 
DISCLAIMER.
 
THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "sfm_ti_config.h"

uint32_t sfm_numTestCases;
ssfm_Config gConfig_sfm[MAX_TESTCASES];

sTokenMapping gsTokenMap_sfm[] =
{
  {(char *)"inFeatFileName"            ,&gConfig_sfm[0].inFeatFileName,                       STRING,  SINGLE},
  {(char *)"inImgFileName"             ,&gConfig_sfm[0].inImgFileName,                        STRING,  SINGLE},
  {(char *)"outFeatFileName"           ,&gConfig_sfm[0].outFeatFileName,                      STRING,  SINGLE},
  {(char *)"outImgFileName"            ,&gConfig_sfm[0].outImgFileName,                       STRING,  SINGLE},
  {(char *)"inCamPrmFileName"          ,&gConfig_sfm[0].inCamPrmFileName,                     STRING,  SINGLE},
  {(char *)"imageWidth"                ,&gConfig_sfm[0].imageWidth,                           INT_16,  SINGLE},
  {(char *)"imageHeight"               ,&gConfig_sfm[0].imageHeight,                          INT_16,  SINGLE},
  {(char *)"startFrame"                ,&gConfig_sfm[0].startFrame,                           INT_16,  SINGLE},
  {(char *)"maxFrames"                 ,&gConfig_sfm[0].maxFrames,                            INT_16,  SINGLE},
  {(char *)"maxNumTracks"              ,&gConfig_sfm[0].maxNumTracks,                         INT_16,  SINGLE},
  {(char *)"maxRansacItr"              ,&gConfig_sfm[0].maxRansacItr,                         INT_32,  SINGLE},
  {(char *)"maxTriangItr"              ,&gConfig_sfm[0].maxTriangItr,                         INT_32,  SINGLE},
  {(char *)"camExtPrmNormType"         ,&gConfig_sfm[0].camExtPrmNormType,                    INT_32,  SINGLE},
  {(char *)"curPrev3DPtFlag"           ,&gConfig_sfm[0].curPrev3DPtFlag,                      INT_8,   SINGLE},
  {(char *)"profileEn"                 ,&gConfig_sfm[0].profileEn,                            INT_16,  SINGLE},
  {(char *)"compareEn"                 ,&gConfig_sfm[0].compareEn,                            INT_16,  SINGLE},
  {(char *)"compareRsultPath"          ,&gConfig_sfm[0].compareRsultPath,                     STRING,  SINGLE},
  {(char *)"sfmEn"                     ,&gConfig_sfm[0].sfmEn,                                INT_16,  SINGLE},
  {(char *)"refFeatFileName"           ,&gConfig_sfm[0].refFeatFileName,                      STRING,  SINGLE},
  {(char *)"fMatrixCalcMethod"         ,&gConfig_sfm[0].fMatrixCalcMethod,                    INT_16,  SINGLE},
  {(char *)"fMatrixPrunEn"             ,&gConfig_sfm[0].fMatrixPrunEn,                        INT_16,  SINGLE},
  {(char *)"fMatrixInTh"               ,&gConfig_sfm[0].fMatrixInTh,                          INT_16,  SINGLE},
  {(char *)"pointPruneAngle"           ,&gConfig_sfm[0].pointPruneAngle,                      FLOAT,   SINGLE},

} ;
double HSV_COLOR_MAP[64][3] = {
  1.0000,         0,         0,
  1.0000,    0.0938,         0,
  1.0000,    0.1875,         0,
  1.0000,    0.2813,         0,
  1.0000,    0.3750,         0,
  1.0000,    0.4688,         0,
  1.0000,    0.5625,         0,
  1.0000,    0.6563,         0,
  1.0000,    0.7500,         0,
  1.0000,    0.8438,         0,
  1.0000,    0.9375,         0,
  0.9688,    1.0000,         0,
  0.8750,    1.0000,         0,
  0.7813,    1.0000,         0,
  0.6875,    1.0000,         0,
  0.5938,    1.0000,         0,
  0.5000,    1.0000,         0,
  0.4063,    1.0000,         0,
  0.3125,    1.0000,         0,
  0.2188,    1.0000,         0,
  0.1250,    1.0000,         0,
  0.0313,    1.0000,         0,
  0,    1.0000,    0.0625,
  0,    1.0000,    0.1563,
  0,    1.0000,    0.2500,
  0,    1.0000,    0.3438,
  0,    1.0000,    0.4375,
  0,    1.0000,    0.5313,
  0,    1.0000,    0.6250,
  0,    1.0000,    0.7188,
  0,    1.0000,    0.8125,
  0,    1.0000,    0.9063,
  0,    1.0000,    1.0000,
  0,    0.9063,    1.0000,
  0,    0.8125,    1.0000,
  0,    0.7188,    1.0000,
  0,    0.6250,    1.0000,
  0,    0.5313,    1.0000,
  0,    0.4375,    1.0000,
  0,    0.3438,    1.0000,
  0,    0.2500,    1.0000,
  0,    0.1563,    1.0000,
  0,    0.0625,    1.0000,
  0.0313,         0,    1.0000,
  0.1250,         0,    1.0000,
  0.2188,         0,    1.0000,
  0.3125,         0,    1.0000,
  0.4063,         0,    1.0000,
  0.5000,         0,    1.0000,
  0.5938,         0,    1.0000,
  0.6875,         0,    1.0000,
  0.7813,         0,    1.0000,
  0.8750,         0,    1.0000,
  0.9688,         0,    1.0000,
  1.0000,         0,    0.9375,
  1.0000,         0,    0.8438,
  1.0000,         0,    0.7500,
  1.0000,         0,    0.6563,
  1.0000,         0,    0.5625,
  1.0000,         0,    0.4688,
  1.0000,         0,    0.3750,
  1.0000,         0,    0.2813,
  1.0000,         0,    0.1875,
  1.0000,         0,    0.0938,
};

