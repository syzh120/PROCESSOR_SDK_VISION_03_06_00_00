/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_CHAIN Utility APIs for Radar.
 *
 * \brief  Utility APIs for Radar usecases
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains_common_iss.h
 *
 * \brief Utility APIs for Radar Usecase
 *
 * \version 0.0 (Nov 2017) : [BJ] First version ported to linux
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_ISS_H_
#define _CHAINS_COMMON_ISS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <src/hlos/common/chains_common.h>

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Macros
 *******************************************************************************
 */
#define CHAINS_RADAR_MAX_NUM_RADAR_SENSORS      4U
#define CHAINS_RADAR_MAX_FILE_NAME              200U
#define CHAINS_RADAR_MAX_LINE_LEN               100U
#define RADAR_CONFIG_FILE_DIR                   "/opt/vision_sdk/radar_test_vector/"
#define MASTER_SENSOR_CONFIG_FILENAME           "sensor_master_config.txt"

/*******************************************************************************
 *  Data Structures
 *******************************************************************************
 */
typedef struct
{
    UInt32      numSensors;
    char        feMaster[CHAINS_RADAR_MAX_LINE_LEN];
} ChainsCommon_MasterFileInfo;

typedef struct
{
    char        fileName[CHAINS_RADAR_MAX_NUM_RADAR_SENSORS]
                        [CHAINS_RADAR_MAX_FILE_NAME];
} ChainsCommon_ConfigFileInfo;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32 ChainsCommon_readSensorFileInfo(const char *rootDirName,
                                      const char *sensorFileName,
                                      ChainsCommon_ConfigFileInfo  * cfgInfo);
Int32 ChainsCommon_readMasterFileInfo(const char *rootDirName,
                                      ChainsCommon_MasterFileInfo *mstInfo);

const ChainsCommon_MasterFileInfo *ChainsCommon_getMstFileInfo(const char *rootDirName);

Int32 ChainsCommon_OpenRadarConfigFile(char *rootDirName,
                                       AppCtrl_RadarConfigFiles *pConfigFiles);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CHAINS_COMMON_ISS_H_ */

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */

