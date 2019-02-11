/*
* module name : Forward Collision Warning
*
* module descripton : Generates distance of objects presents in scene
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
#include "fcw_config.h"
#pragma RESET_MISRA ("required")

uint32_t fcw_numTestCases;
sFCW_Config gConfig_FCW[FCW_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_FCW[] =
{
  {(char *)"numTestCases"        ,&fcw_numTestCases                   , INT_32, SINGLE},
  {(char *)"inYUVFileName"       ,&gConfig_FCW[0].inYUVFileName       , STRING, SINGLE},
  {(char *)"outYUVFileName"      ,&gConfig_FCW[0].outYUVFileName      , STRING, SINGLE},
  {(char *)"inObjFileName"       ,&gConfig_FCW[0].inObjFileName       , STRING, SINGLE},
  {(char *)"outTTCFileName"      ,&gConfig_FCW[0].outTTCFileName      , STRING, SINGLE},
  {(char *)"camExtPrmFileName"   ,&gConfig_FCW[0].camExtPrmFileName   , STRING, SINGLE},
  {(char *)"grndPlnPrmFileName"  ,&gConfig_FCW[0].grndPlnPrmFileName  , STRING, SINGLE},
  {(char *)"refTTCFileName"      ,&gConfig_FCW[0].refTTCFileName      , STRING, SINGLE},
  {(char *)"minObjHeight"        ,&gConfig_FCW[0].minObjHeight        , FLOAT,  SINGLE},
  {(char *)"maxObjHeight"        ,&gConfig_FCW[0].maxObjHeight        , FLOAT,  SINGLE},
  {(char *)"imgHeight"           ,&gConfig_FCW[0].imgHeight           , INT_16, SINGLE},
  {(char *)"fps"                 ,&gConfig_FCW[0].fps                 , FLOAT,  SINGLE},
  {(char *)"startFrame"          ,&gConfig_FCW[0].startFrame          , INT_32, SINGLE},
  {(char *)"maxFrames"           ,&gConfig_FCW[0].maxFrames           , INT_32, SINGLE},
  {(char *)"maxNumObjects"       ,&gConfig_FCW[0].maxNumObjects       , INT_32, SINGLE},
  {(char *)"minObjDist"          ,&gConfig_FCW[0].minObjDist          , FLOAT,  SINGLE},
  {(char *)"maxObjDist"          ,&gConfig_FCW[0].maxObjDist          , FLOAT,  SINGLE}
} ;

