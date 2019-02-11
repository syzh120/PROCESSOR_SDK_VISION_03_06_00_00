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
 * \defgroup EXAMPLES_CHAIN APIs for selecting the usecase chain.
 *
 * \brief  APIs for selecting the required usecase chain and run
 *         time menu configurations .
 *         It also provide API's for instrumentation of load and heap usage
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains_radar_cfg.h
 *
 * \brief APIs for selecting the required usecase chain.
 *
 * \version 0.0 (Feb 2018) : [SL] First version
 *
 *******************************************************************************
 */

#ifndef CHAINS_RADAR_CFG_H_
#define CHAINS_RADAR_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <system_cfg.h>
#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <ti/drv/vps/include/devices/bsp_ar12xx.h>
#include <ti/drv/stw_lld/platform/platform.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/**< \brief Maximum Number of profiles which is possible from the AR device */
#define CHAINS_AR1243_MAX_PROFILES  (4U)

/** \brief Maximum Number of Radars */
#define CHAINS_MAX_NUM_RADARS   (4U)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
/**
 * \brief Structure which holds the radar configuration parameters.
 *        Different parameter set can be assigned per radar.
 */
typedef struct {

    UInt32 csi2OutWidth;
    /**< CSI output width - Number of pixels */
    UInt32 csi2OutHeight;
    /**< CSI output height */
    UInt32 numTxAntenna[CHAINS_AR1243_MAX_PROFILES];
    /**< Number of transmit antennas */
    UInt32 numRxAntenna[CHAINS_AR1243_MAX_PROFILES];
    /**< Number of recieve antennas */
    UInt32 inBufAddrOffset;
    /**< Input buffer offset. This is set to a non-zero value only when
     *   the CP data comes before the ADC data.
     */
    UInt32 offsetBwAntennas [CHAINS_AR1243_MAX_PROFILES];
    /**< Input buffer offset between antenna data to take care of offsets
     *   for ADC data and the CP and CQ data.
     */
    Bsp_Ar12xxConfigObj   ar12xxConfig;
    /**< Radar Configuration Object */
    char configName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH];
    /**< Configuration name */
    UInt32 radarWidth [CHAINS_AR1243_MAX_PROFILES];
    /**< Radar Sensor chirp length */
    UInt32 radarHeight [CHAINS_AR1243_MAX_PROFILES];
    /**< Radar sensor number of chirps */
    float rangeRes [CHAINS_AR1243_MAX_PROFILES];
    /**< Range Resolution */
    float velocityRes [CHAINS_AR1243_MAX_PROFILES];
    /**< Velocity Resolution */
    UInt32 numProfiles;
    /**< Number of profiles being used in the usecase */
    UInt32 numValidBits;
    /**< Number of valid bits in input data. If numValidBits is 16 then
     *   sign extension is disabled.
     */
    UInt32 currProfileId;
    /**< Current Profile Id */
    UInt32 bpmEnabled;
    /**< Flag to show if BPM is enabled or not */
    rlChirpRow_t *chirpRow;
    /**< Pointer to Chirp Row arguments */
    UInt32       numChirpRow;
    /**< Number of chirpRow elements */
} ChainsCommon_RadarParams;

/**
 * \brief Structure which holds the AR12xx configuration parameters.
 */
typedef struct {

    UInt32 numRadars;
    /**< Number of Radars being connected */
    ChainsCommon_RadarParams radarParams[CHAINS_MAX_NUM_RADARS];
    /**< Parameters per Radar */
    UInt32 frameType;
    /**< 0 - Normal Frame, 1 - Advanced Frame */
    UInt32 fusionEnabled;
    /**< Flag to show if Fusion is enabled or not */
} ChainsCommon_Ar12xxConfigOut;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */


