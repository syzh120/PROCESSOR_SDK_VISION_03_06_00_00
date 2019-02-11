/*
* module name       :TI Object Detection
*
* module descripton :Detection of pedestrians, traffic signs and vehicles using TI’s C66x DSP
*
*/
/*

Copyright (c) [2014] – [2017] Texas Instruments Incorporated

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
#include "object_detection_config.h"
#pragma RESET_MISRA ("required")

uint32_t objectDetection_numTestCases;
sObjectDetection_Config gConfig_objectDetection[MAX_TESTCASES];

sTokenMapping gsTokenMap_objectDetection[] =
{
  {(char *)"inFileName"            ,&gConfig_objectDetection[0].inFileName,                       STRING,  SINGLE},
  {(char *)"logFileName"           ,&gConfig_objectDetection[0].logFileName,                      STRING,  SINGLE},
  {(char *)"detListFileName"       ,&gConfig_objectDetection[0].detListFileName,                  STRING,  SINGLE},
  {(char *)"objListFileName"       ,&gConfig_objectDetection[0].objListFileName,                  STRING,  SINGLE},
  {(char *)"maxImageWidth"         ,&gConfig_objectDetection[0].maxImageWidth,                    INT_16,  SINGLE},
  {(char *)"maxImageHeight"        ,&gConfig_objectDetection[0].maxImageHeight,                   INT_16,  SINGLE},
  {(char *)"maxFrames"             ,&gConfig_objectDetection[0].maxFrames,                        INT_16,  SINGLE},
  {(char *)"maxScales"             ,&gConfig_objectDetection[0].maxScales,                        INT_16,  SINGLE},
  {(char *)"detectionMode"         ,&gConfig_objectDetection[0].detectionMode,                     INT_8,  SINGLE},
  {(char *)"roiPreset"             ,&gConfig_objectDetection[0].roiPreset,                         INT_8,  SINGLE},
  {(char *)"refreshInterval"       ,&gConfig_objectDetection[0].refreshInterval,                   INT_8,  SINGLE},

  {(char *)"enablePD"              ,&gConfig_objectDetection[0].pdConfig.enablePD,                 INT_8,  SINGLE},
  {(char *)"detectorTypePD"        ,&gConfig_objectDetection[0].pdConfig.detectorTypePD,           INT_8,  SINGLE},
  {(char *)"trackingMethodPD"      ,&gConfig_objectDetection[0].pdConfig.trackingMethodPD,         INT_8,  SINGLE},
  {(char *)"softCascadeThPD"       ,&gConfig_objectDetection[0].pdConfig.softCascadeThPD,         INT_32,  SINGLE},
  {(char *)"strongCascadeThPD"     ,&gConfig_objectDetection[0].pdConfig.strongCascadeThPD,       INT_32,  SINGLE},
  {(char *)"useExtWeightsPD"       ,&gConfig_objectDetection[0].pdConfig.useExtWeightsPD,          INT_8,  SINGLE},
  {(char *)"pdWeightsFileName"     ,&gConfig_objectDetection[0].pdWeightsFileName,                STRING,  SINGLE},

  {(char *)"enableTSR"             ,&gConfig_objectDetection[0].tsrConfig.enableTSR,               INT_8,  SINGLE},
  {(char *)"detectorTypeTSR"       ,&gConfig_objectDetection[0].tsrConfig.detectorTypeTSR,         INT_8,  SINGLE},
  {(char *)"trackingMethodTSR"     ,&gConfig_objectDetection[0].tsrConfig.trackingMethodTSR,       INT_8,  SINGLE},
  {(char *)"recognitionMethodTSR"  ,&gConfig_objectDetection[0].tsrConfig.recognitionMethodTSR,    INT_8,  SINGLE},
  {(char *)"softCascadeThTSR"      ,&gConfig_objectDetection[0].tsrConfig.softCascadeThTSR,       INT_32,  SINGLE},
  {(char *)"strongCascadeThTSR"    ,&gConfig_objectDetection[0].tsrConfig.strongCascadeThTSR,     INT_32,  SINGLE},
  {(char *)"useExtWeightsTSR"      ,&gConfig_objectDetection[0].tsrConfig.useExtWeightsTSR,        INT_8,  SINGLE},
  {(char *)"tsrWeightsFileName"    ,&gConfig_objectDetection[0].tsrWeightsFileName,               STRING,  SINGLE},

  {(char *)"enableVD"              ,&gConfig_objectDetection[0].vdConfig.enableVD,                 INT_8,  SINGLE},
  {(char *)"detectorTypeVD"        ,&gConfig_objectDetection[0].vdConfig.detectorTypeVD,           INT_8,  SINGLE},
  {(char *)"trackingMethodVD"      ,&gConfig_objectDetection[0].vdConfig.trackingMethodVD,         INT_8,  SINGLE},
  {(char *)"softCascadeThVD"       ,&gConfig_objectDetection[0].vdConfig.softCascadeThVD,         INT_32,  SINGLE},
  {(char *)"strongCascadeThVD"     ,&gConfig_objectDetection[0].vdConfig.strongCascadeThVD,       INT_32,  SINGLE},
  {(char *)"useExtWeightsVD"       ,&gConfig_objectDetection[0].vdConfig.useExtWeightsVD,          INT_8,  SINGLE},
  {(char *)"vdWeightsFileName"     ,&gConfig_objectDetection[0].vdWeightsFileName,                STRING,  SINGLE},

} ;

/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to OD errors                                */
/* Please refer User guide for more details on error strings                  */
/*----------------------------------------------------------------------------*/
static sErrorMapping gErrorStrings[32] =
{
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_IMAGE_WIDTH = 16\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_IMAGE_HEIGHT = 17,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_NUM_SCALES = 18,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_DETECTION_MODE = 19,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_ROI_PRESET = 20,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_REFRESH_INTERVAL = 21,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_CLASSIFIER_TYPE = 22,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_TRACKING_METHOD = 23,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_RECOGNITION_METHOD = 24,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_SOFT_CASCADE_THRESHOLD = 25,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_STRONG_CASCADE_THRESHOLD = 26,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_META_DATA = 27,\0",
  (XDAS_Int8 *)"TI_OD_EDMA_MEMCPY_ERROR = 28,\0",
  (XDAS_Int8 *)"TI_OD_EDMA_SCATTER_GATHER_ERROR = 29,\0",
  (XDAS_Int8 *)"TI_OD_RESERVED_PARAMS_NOT_ZERO = 30,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_PARAMETER = 31,\0"
};

XDAS_Int32 TI_OD_Report_Error(XDAS_Int32 uiErrorMsg)
{
  int i;
  if(uiErrorMsg)
  {
    /*------------------------------------------------------------------------*/
    /* Loop through all the bits in error message and print error string.     */
    /*------------------------------------------------------------------------*/
    for (i = 16; i < 32; i ++)
    {
      if (uiErrorMsg & (1 << i))
      {
        printf("ERROR: %s \n",  gErrorStrings[(i - 16)].errorName);
      }
    }

    return IALG_EFAIL;
  }

  return IALG_EOK;
}
