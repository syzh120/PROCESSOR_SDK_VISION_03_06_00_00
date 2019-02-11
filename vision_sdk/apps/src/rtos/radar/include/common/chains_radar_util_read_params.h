/******************************************************************************
Copyright (c) [2012 - 2018] Texas Instruments Incorporated

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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
 * \defgroup EXAMPLES_UTIL APIs for reading configurations from files.
 *
 * \brief  APIs for reading configurations from files.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains_radar_util_common.h
 *
 * \brief APIs for reading configurations from files.
 *
 * \version 0.0 (Nov 2018) : First version
 *
 *******************************************************************************
 */

#ifndef _CHAINS_RADAR_UTIL_COMMON_H_
#define _CHAINS_RADAR_UTIL_COMMON_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <include/common/chains_radar.h>
#include <include/link_api/system_trace.h>
#include <src/rtos/utils_common/include/file_api.h>
#include <mmwavelink.h>
#include <ti/drv/vps/include/devices/bsp_ar12xx.h>

#include <include/alg_fxns/radarDspProcess_if.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define RADAR_CONFIG_PARAM_DIR_NAME  "radar_test_vector/"
#define MASTER_SENSOR_CONFIG_FILENAME "sensor_master_config.txt"

#define CHAINS_RADAR_MAX_NUM_RADAR_SENSORS  4
#define CHAINS_RADAR_UTIL_MAX_LINE_LEN      100
#define CHAINS_RADAR_UTIL_MAX_FILE_NAME     200
#define CHAINS_RADAR_NUM_BYTES_PER_SAMPLE   4

#define RADAR_LINK_MAX_NUM_PROFILE_CONFIG   16U
#define RADAR_LINK_MAX_NUM_CHIRP_CONFIG     16U
#define RADAR_LINK_MAX_NUM_TX_ANTENNA       3U
#define RADAR_LINK_MAX_NUM_SENSORS          4U

 /*******************************************************************************
  *  Data structure's
  *******************************************************************************
  */
typedef struct
{
    UInt8                   sensorId;
    UInt8                   txAntEnableMask;
    UInt8                   rxAntEnableMask;
    UInt8                   numChirpCfg;
    UInt8                   numProfileCfg;
    UInt8                   enableAdvFrameCfg;
    rlDevDataPathClkCfg_t   dataPathClk;
    rlDevDataPathCfg_t      dataPathCfgArgs;
    rlDevHsiClk_t           hsiClkCfgArgs;
    rlProfileCfg_t          profileCfgArgs[RADAR_LINK_MAX_NUM_PROFILE_CONFIG];
    rlChirpCfg_t            chirpCfgArgs[CHAINS_RADAR_MAX_NUM_CHIRP_CFG];
    rlFrameCfg_t            frameCfgArgs;
    rlAdvFrameCfg_t         advFrameCfgArgs;
} rlFrontEndCfg_t;

typedef struct
{
    /** Number of sensors inthe system. */
    UInt16                numSensors;

    /* Sensor configuration. */
    rlFrontEndCfg_t         cfg[RADAR_LINK_MAX_NUM_SENSORS];

} ChainsUtil_RlFrontEndConfig;

typedef struct
{
    UInt32      numSensors;
    char        feMaster[CHAINS_RADAR_UTIL_MAX_FILE_NAME];
    char        fftMaster[CHAINS_RADAR_UTIL_MAX_FILE_NAME];
    char        dspAlgoMaster[CHAINS_RADAR_UTIL_MAX_FILE_NAME];
} ChainsUtil_MasterFileInfo;

typedef struct
{
    char        fileName[RADAR_LINK_MAX_NUM_SENSORS]
                        [CHAINS_RADAR_UTIL_MAX_FILE_NAME];
} ChainsUtil_ConfigFileInfo;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
const ChainsUtil_MasterFileInfo *ChainsUtil_getMstFileInfo(const char *rootDirName);

Int32 ChainsUtil_readSensorFile(const char *rootDirName,
                                const char *sensorFileName,
                                ChainsUtil_ConfigFileInfo *cfgInfo);

Void ChainsUtil_setFeParams(Bsp_Ar12xxConfigObj *ar12xxCfgObj,
                            rlFrontEndCfg_t *feCfgParams);

Void ChainsUtil_readFeParams(Void *feCfgFileBuf,
                             UInt32 fileSize,
                             rlFrontEndCfg_t * cfgParams);

Int32 ChainsUtil_readFeCfgParams(const char *rootDirName,
                                 ChainsUtil_RlFrontEndConfig *feCfg);

Int32 ChainsUtil_updateFftAlgoParams(const char *rootDirName,
                                     AlgorithmFxn_RadarFftCreateParams *pFftParams,
                                     UInt32 deviceId);

Int32 ChainsUtil_updateCascadeDspProcessParams(const char *rootDirName,
                                               AlgorithmFxn_RadarDspProcessCreateParams *pDspProcParams);

#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
