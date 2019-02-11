/*
* module name : Ground Plane Estimation
*
* module descripton : Generates ground plane information from sparse 3D points
*
*/
/*
 
Copyright (c) 2015-2017 Texas Instruments Incorporated
 
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
 
*/#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "gpe_ti_config.h"
#pragma RESET_MISRA ("required")

uint32_t gpe_numTestCases;
sGPE_Config gConfig_GPE[GPE_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_GPE[] =
{
  {(char *)"numTestCases"        ,&gpe_numTestCases                   , INT_32, SINGLE},
  {(char *)"inYUVFileName"       ,&gConfig_GPE[0].inYUVFileName       , STRING, SINGLE},
  {(char *)"outYUVFileName"      ,&gConfig_GPE[0].outYUVFileName      , STRING, SINGLE},
  {(char *)"inObjFileName"       ,&gConfig_GPE[0].inObjFileName       , STRING, SINGLE},
  {(char *)"inPointCloudFileName",&gConfig_GPE[0].inPointCloudFileName, STRING, SINGLE},
  {(char *)"outGpeFileName"      ,&gConfig_GPE[0].outGpeFileName      , STRING, SINGLE},
  {(char *)"refGpeFileName"      ,&gConfig_GPE[0].refGpeFileName      , STRING, SINGLE},
  {(char *)"compFileName"        ,&gConfig_GPE[0].compFileName        , STRING, SINGLE},
  {(char *)"imgWidth"            ,&gConfig_GPE[0].imgWidth            , INT_16, SINGLE},
  {(char *)"imgHeight"           ,&gConfig_GPE[0].imgHeight           , INT_16, SINGLE},
  {(char *)"fps"                 ,&gConfig_GPE[0].fps                 , FLOAT,  SINGLE},
  {(char *)"startFrame"          ,&gConfig_GPE[0].startFrame          , INT_32, SINGLE},
  {(char *)"maxFrames"           ,&gConfig_GPE[0].maxFrames           , INT_32, SINGLE},
  {(char *)"maxNumPointCloud"    ,&gConfig_GPE[0].maxNumPointCloud    , INT_32, SINGLE},
  {(char *)"maxNumObjects"       ,&gConfig_GPE[0].maxNumObjects       , INT_32, SINGLE},
  {(char *)"cameraHeight"        ,&gConfig_GPE[0].gpePrms.cameraHeight     , FLOAT,  SINGLE},
  {(char *)"fracWidthTrpzd"      ,&gConfig_GPE[0].gpePrms.fracWidthTrpzd   , FLOAT,  SINGLE},
  {(char *)"fracHeightTrpzd"     ,&gConfig_GPE[0].gpePrms.fracHeightTrpzd  , FLOAT,  SINGLE},
  {(char *)"ptOnPlaneDistTh"     ,&gConfig_GPE[0].gpePrms.ptOnPlaneDistTh  , FLOAT,  SINGLE},
  {(char *)"maxCostTh"           ,&gConfig_GPE[0].gpePrms.maxCostTh        , FLOAT,  SINGLE},
  {(char *)"trpzdImpFac"         ,&gConfig_GPE[0].gpePrms.trpzdImpFac      , FLOAT,  SINGLE},
  {(char *)"baseRoll"            ,&gConfig_GPE[0].gpePrms.baseRoll         , FLOAT,  SINGLE},
  {(char *)"deltaRoll"           ,&gConfig_GPE[0].gpePrms.deltaRoll        , FLOAT,  SINGLE},
  {(char *)"basePitch"           ,&gConfig_GPE[0].gpePrms.basePitch        , FLOAT,  SINGLE},
  {(char *)"deltaPitch"          ,&gConfig_GPE[0].gpePrms.deltaPitch       , FLOAT,  SINGLE},
  {(char *)"pointsOnlyInTrpzd"   ,&gConfig_GPE[0].gpePrms.pointsOnlyInTrpzd , INT_8,  SINGLE},
  {(char *)"noMovingObjectPtCloud" ,&gConfig_GPE[0].gpePrms.noMovingObjectPtCloud , INT_8,  SINGLE},
  {(char *)"startY"                ,&gConfig_GPE[0].gpePrms.startY                , INT_16,  SINGLE},
  {(char *)"minPtsForRansac"       ,&gConfig_GPE[0].gpePrms.minPtsForRansac       , INT_16,  SINGLE},
  {(char *)"numRansacIteration"    ,&gConfig_GPE[0].gpePrms.numRansacIteration    , INT_16,  SINGLE},

} ;

GPE_TI_configParams gpePrmsDefault =
{
  1.58,   /*float            cameraHeight  ;        */
  0.5f,   /*float            fracWidthTrpzd;        */
  0.4f,   /*float            fracHeightTrpzd;       */
  50,     /*float            ptOnPlaneDistTh;       */
  100,    /*float            maxCostTh;             */
  2.0,    /*float            trpzdImpFac;           */
  0.0,    /*float            baseRoll;              */
  5.73,   /*float            deltaRoll;             */
  0.0,    /*float            basePitch;             */
  4.0,    /*float            deltaPitch;            */
  0,      /*uint8_t          pointsOnlyInTrpzd;     */
  1,      /*uint8_t          noMovingObjectPtCloud; */
  0,      /*uint16_t         startY;                */
  100,    /*uint16_t         minPtsForRansac;       */
  3000,   /*uint16_t         numRansacIteration;    */
};

