/*
 *   Copyright (c) Texas Instruments Incorporated 2016-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file bspdrv_ar12xx.c
 *
 *  \brief AR12xx Radar sensor driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/devices/bsp_ar12xx.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <bspdrv_ar12xxPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** List of the sensors supported by the radar driver */
Bsp_ar12xxSensorObj gBspAr12xxSensorCfgList[
    BSP_AR12XX_MAX_CONFIG_SUPPORTED] =
{
    {1U, BSP_AR12XX_AR1243_NAME, &gAr1243RadarConfig},
    {0U, "\0",                   NULL               },
    {0U, "\0",                   NULL               },
    {0U, "\0",                   NULL               },
    {0U, "\0",                   NULL               }
};

/** BSP Driver AR12xx radar object */
Bsp_ar12xxObj       gBspAr12xxObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  Function to check if the necessary initialization parameters are
 *          populated for the radar sensor to work.
 *
 *  \param  initPrms Pointer to the initialization parameters.
 *
 *  \return retVal   Returns BSP_SOK if the parameters are populated correctly.
 *                   BSP_EINVALID_PARAMS is returned otherwise.
 */
static Int32 Bsp_ar12xxCheckInitParams(
    const Bsp_Ar12xxInitParams *initPrms);

/**
 *  \brief  Function to set the CSI AR configuration for trim settings.
 *
 *  \param  None
 *
 *  \return retVal   Returns BSP_SOK if the parameters are populated correctly.
 *                   BSP_EINVALID_PARAMS is returned otherwise.
 */
static Int32 Bsp_ar12xxCsiTrimConfig(void);

/**
*   \brief Set CRC type of async event from AWR1243 MasterSS
*
*   \param [in] deviceMap - Device Index map
*
*   \return int32_t Success - BSP_SOK, Failure - Error Code
*
*/
static int32_t Bsp_ar12xxSetDeviceCrcType(uint8_t deviceMap);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_ar12xxRegisterConfig(
    char                 name[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH],
    Bsp_Ar12xxConfigObj *configObj)
{
    Int32  retVal = BSP_SOK;
    UInt32 i;
    UInt32 numSensorsSupported = sizeof (gBspAr12xxSensorCfgList) /
                                 sizeof (Bsp_ar12xxSensorObj);
    for (i = 0; i < numSensorsSupported; i++)
    {
        if (gBspAr12xxSensorCfgList[i].isUsed == 0U)
        {
            strcpy(gBspAr12xxSensorCfgList[i].radarConfigName, name);
            gBspAr12xxSensorCfgList[i].sensorConfigObj = configObj;
            gBspAr12xxSensorCfgList[i].isUsed          = 1U;
            break;
        }
    }
    if (i == numSensorsSupported)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

Int32 Bsp_ar12xxInit(const Bsp_Ar12xxInitParams *initPrms)
{
    Int32  retVal = BSP_SOK;
    UInt32 numSensorsSupported = sizeof (gBspAr12xxSensorCfgList) /
                                 sizeof (Bsp_ar12xxSensorObj);
    UInt32 i, devId;
    UInt32 devArrMap[] =
    {
        RL_DEVICE_MAP_CASCADED_1,
        RL_DEVICE_MAP_CASCADED_2,
        RL_DEVICE_MAP_CASCADED_3,
        RL_DEVICE_MAP_CASCADED_4
    };
    /* First initialize the driver object with 0s */
    memset(&gBspAr12xxObj, 0, sizeof (Bsp_ar12xxObj));

    /* Check if all necessary input init parameters are okay */
    retVal = Bsp_ar12xxCheckInitParams(initPrms);

    /* Find the configuration structure for the given radar sensor name */
    if (retVal == BSP_SOK)
    {
        for (devId = 0; devId < initPrms->numRadarDevicesInCascade; devId++)
        {
            for (i = 0; i < numSensorsSupported; i++)
            {
                if (0 ==
                    strcmp(initPrms->devParams[devId].radarConfigName,
                           gBspAr12xxSensorCfgList[i].radarConfigName))
                {
                    break;
                }
            }

            if (i == numSensorsSupported)
            {
                retVal = BSP_EFAIL;
            }
            else
            {
                /* Set the radar ID to get the right configuration parameters */
                gBspAr12xxObj.radarConfigId[devId] = i;
            }
        }
    }
    if (retVal == BSP_SOK)
    {
        /* Copy the initialization parameters to a local copy to be
         * used later.
         */
        memcpy(&gBspAr12xxObj.initPrmsCopy, initPrms,
               sizeof (Bsp_Ar12xxInitParams));
        /* Find the device map index */
        gBspAr12xxObj.devIdxMap = 0U;
        for (i = 0U; i < initPrms->numRadarDevicesInCascade; i++)
        {
            gBspAr12xxObj.devIdxMap |= devArrMap[i];
        }
#if defined (BOARD_TYPE_TDA3XX_RVP)
        /* Check if Satellite Radar is used or not */
        /* Set pin mux & GPIO accordingly. */
        if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_DIRECT)
        {
            Bsp_boardTda3xxRvpAr12xxRadarInit(0U);
        }
        else
        {
            Bsp_boardTda3xxRvpAr12xxRadarInit(1U);
        }
#endif
        /* Perform GPIO Initialization based on the input GPIO Instance and
         * Pin number.
         */
        retVal = Bsp_ar12xxGpioInit(&gBspAr12xxObj);
    }
    if (retVal == BSP_SOK)
    {
        /* Create a queue and task used for radar communication */
        retVal = Bsp_ar12xxCreateCommInfra();
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_ar12xxRegisterCallbacks();
    }
    if (retVal == BSP_SOK)
    {
        Bsp_ar12xxUartInit(&gBspAr12xxObj);
    }
    return (retVal);
}

Int32 Bsp_ar12xxBoot(UInt32 downloadFirmware)
{
    Int32 retVal = BSP_SOK;
    UInt32 origDevMap = gBspAr12xxObj.devIdxMap;

    gBspAr12xxObj.devIdxMap = (UInt32) ((UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);
    /* Register the different callbacks used by the radar interface and
     * power on the radar device.
     */
    retVal = Bsp_ar12xxRadarDeviceOn();

    if ((retVal == BSP_SOK) && (downloadFirmware != 0U))
    {
        gBspAr12xxObj.arDeviceRevision = Bsp_ar12xxGetDeviceRevision();
        /* Download the firmware and run it on the AR12XX device */
        retVal = Bsp_ar12xxFmwSpiDwld();
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_ar12xxFmwRun();
    }
    if (retVal == BSP_SOK)
    {
        /* Get and store the device revision */
        gBspAr12xxObj.arDeviceRevision = Bsp_ar12xxGetDeviceRevision();
    }

    if ((((Int32)gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade - (Int32)1)
            > (Int32) 0) && (retVal == BSP_SOK))
    {
        /* Modify the device map to ensure that the Slave device Ids are
         * selected.
         */
        gBspAr12xxObj.devIdxMap = (UInt32)origDevMap &
        (UInt32)~((UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);

        retVal = Bsp_ar12xxBootSlaves();

        if ((retVal == BSP_SOK) && (downloadFirmware != 0U))
        {
            /* Download the firmware and run it on the AR12XX device */
            retVal = Bsp_ar12xxFmwSpiDwld();
        }
        if (retVal == BSP_SOK)
        {
            retVal = Bsp_ar12xxFmwRun();
        }
    }
    gBspAr12xxObj.devIdxMap = origDevMap;
    if (retVal == BSP_SOK)
    {
        /* Print the version of the radar driver */
        retVal = Bsp_ar12xxPrintVersion();
    }
    /* Set the CRC type of the async events from the slave to the master */
    if ((gBspAr12xxObj.arDeviceRevision > 1U) && (retVal == BSP_SOK))
    {
        retVal = Bsp_ar12xxSetDeviceCrcType((UInt8)origDevMap);
    }
    return retVal;
}

Int32 Bsp_ar12xxConfigParams(UInt32 bitMapEnableConfig)
{
    Int32  retVal         = BSP_SOK;
    UInt32 i;
    UInt32 radarConfigIdx;
    Bsp_Ar12xxConfigObj *sensorCfg;
    UInt32 origDevMap = gBspAr12xxObj.devIdxMap;
    /* Set a sleep time of 10 seconds for the AR12xx device boot time. This
     * is kept at a worst possible maximum time.
     */
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
    for (i = 0; i < gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade; i++)
    {
        radarConfigIdx = gBspAr12xxObj.radarConfigId[i];
        gBspAr12xxObj.devIdxMap = (UInt32) ((UInt32)0x1U << (UInt32)i);
        if (radarConfigIdx < BSP_AR12XX_MAX_CONFIG_SUPPORTED)
        {
            sensorCfg = gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
            if ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_CHANNEL) != 0U)
            {
                /* Configure the Rx and Tx channel configuration */
                retVal = (Int32) rlSetChannelConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                    &sensorCfg->rfChanCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_ADC_OUT) != 0U))
            {
                /* Configure ADC Output*/
                retVal = (Int32) rlSetAdcOutConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                   &sensorCfg->adcOutCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_DATA_FORMAT) != 0U))
            {
                /* Configure radar data format */
                retVal = (Int32) rlDeviceSetDataFmtConfig(
                    (rlUInt8_t)gBspAr12xxObj.devIdxMap,
                    &sensorCfg->
                    dataFmtCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_LOW_POWER_MODE) != 0U))
            {
                /* Configure Low power mode */
                retVal = (Int32) rlSetLowPowerModeConfig(
                    (rlUInt8_t)gBspAr12xxObj.devIdxMap,
                    &sensorCfg->
                    rfLpModeCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
            ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_LDO_BYPASS) != 0U))
            {
                /* Configure Low power mode */
                retVal = (Int32) rlRfSetLdoBypassConfig(
                    (rlUInt8_t)gBspAr12xxObj.devIdxMap,
                    &sensorCfg->
                    ldoBypassCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig &
                    (UInt32) BSP_AR12XX_CONFIG_RF_INIT_CAL_MASK) != 0U) &&
                (gBspAr12xxObj.arDeviceRevision != 1U))
            {
                retVal = rlRfInitCalibConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                             &sensorCfg->calibEnArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_RF_INIT) != 0U))
            {
                gBspAr12xxObj.radarRfInitComplete = 0U;
                /* Configure the radar analog system */
                retVal = (Int32) rlRfInit((rlUInt8_t)gBspAr12xxObj.devIdxMap);
                if (retVal == BSP_SOK)
                {
                    while ((gBspAr12xxObj.radarRfInitComplete == 0U)
                        && (timeout > 0U))
                    {
                        BspOsal_sleep(1U);
                        timeout--;
                    }
                    if (timeout == 0U)
                    {
                        retVal = BSP_EFAIL;
                    }
                }
                if (retVal == BSP_SOK)
                {
                    rlRfBootStatusCfg_t data;
                    retVal = rlGetRfBootupStatus((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                 &data);
                    GT_1trace(BspDeviceTrace, GT_INFO,
                                              " AWR12XX: RF Boot Status = 0x%x\r\n",
                                              data.bssSysStatus);
                    GT_1trace(BspDeviceTrace, GT_INFO,
                                              " AWR12XX: RF Boot Time = %d us\r\n",
                                              (data.bssBootUpTime * 5U)/1000U);
                }
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_DATA_PATH) != 0U))
            {
                /* Configure the data path */
                retVal = (Int32) rlDeviceSetDataPathConfig(
                    (rlUInt8_t)gBspAr12xxObj.devIdxMap,
                    &sensorCfg->
                    dataPathCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_LVDS_CLK) != 0U))
            {
                /* Configure CSI2 CLock */
                retVal = (Int32) rlDeviceSetDataPathClkConfig(
                    (rlUInt8_t)gBspAr12xxObj.devIdxMap,
                    &sensorCfg->
                    dataPathClkCfgArgs);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_HSI_CLK) != 0U))
            {
                /* Configure HSI Clock*/
                retVal = (Int32) rlDeviceSetHsiClk((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                   &sensorCfg->hsiClkgs);
            }
            if (retVal == BSP_SOK)
            {
                gBspAr12xxObj.maxSleepTime = Bsp_ar12xxCalcMaxSleepTime(
                    radarConfigIdx);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_PROFILE_PARAM) != 0U))
            {
                retVal = Bsp_ar12xxConfigProfile(radarConfigIdx);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_CHIRP_PARAM) != 0U))
            {
                retVal = Bsp_ar12xxConfigChirp(radarConfigIdx);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_BPM_CHIRP) != 0U))
            {
                retVal = Bsp_ar12xxConfigBpmChirp(radarConfigIdx);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_BPM_COMMON) != 0U))
            {
                retVal = Bsp_ar12xxConfigBpmCommon(radarConfigIdx);
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_CSI_LANES) != 0U))
            {
                retVal = rlDeviceSetCsi2Config((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                               &sensorCfg->csiConfigArgs);
            }
            if (retVal == BSP_SOK)
            {
                retVal = Bsp_ar12xxCsiTrimConfig();
            }
            if ((retVal == BSP_SOK) &&
                ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_FRAME_PARAM) != 0U))
            {
                if (sensorCfg->frameType == BSP_AR12XX_FRAME_TYPE_NORMAL)
                {
                    /* Perform frame configuration */
                    retVal = (Int32) rlSetFrameConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                      sensorCfg->frameCfgArgs);
                    gBspAr12xxObj.triggerType[i] = sensorCfg->frameCfgArgs->triggerSelect;
                }
                else if (sensorCfg->frameType == BSP_AR12XX_FRAME_TYPE_ADVANCED)
                {
                    /* Perform advanced frame configuration */
                    retVal = (Int32) rlSetAdvFrameConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                      &sensorCfg->advFrameCfgArgs);
                    gBspAr12xxObj.triggerType[i] =
                        sensorCfg->advFrameCfgArgs.frameSeq.triggerSelect;
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
            }
            if ((retVal == BSP_SOK) &&
               ((bitMapEnableConfig & (UInt32) BSP_AR12XX_CONFIG_CONT_STREAMING) != 0U))
            {
                /* Perform continuous mode configuration and enable it */
                retVal = (Int32) rlSetContModeConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                  &sensorCfg->contModeCfgArgs);
                if (retVal == BSP_SOK)
                {
                    rlContModeEn_t contModeEn = {
                        .contModeEn = (rlUInt16_t) 1U,
                        .reserved  = (rlUInt16_t) 0U
                    };
                    retVal = (Int32) rlEnableContMode(
                              (rlUInt8_t)gBspAr12xxObj.devIdxMap, &contModeEn);
                }
            }
        }
        else
        {
            retVal = BSP_EFAIL;
        }
        if (retVal != BSP_SOK)
        {
            break;
        }
    }
    gBspAr12xxObj.devIdxMap = origDevMap;
    return retVal;
}

Int32 Bsp_ar12xxGetConfiguredParam(UInt32 deviceOfInterest,
                                   UInt32 paramOfInterest,
                                   UInt32 index, void *ptr)
{
    Int32  retVal         = BSP_SOK;
    UInt32 radarConfigIdx = gBspAr12xxObj.radarConfigId[deviceOfInterest];
    Bsp_Ar12xxConfigObj *sensorCfg;
    if (radarConfigIdx < BSP_AR12XX_MAX_CONFIG_SUPPORTED)
    {
        sensorCfg = gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
        if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_PROFILE_PARAM) != 0U)
        {
            /* For parameter of interest as the profile configuration
             * get the profile configuration corresponding to the index */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                retVal = rlGetProfileConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                            (UInt16)index, (rlProfileCfg_t *) ptr);
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading Profile parameters is not supported in ES1.0!!\r\n");
            }
        }
        else if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_CHIRP_PARAM) != 0U)
        {
            /* For parameter of interest as the chirp configuration
             * get the chirp configuration corresponding to the index */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                retVal = rlGetChirpConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                          (UInt16)index, (UInt16)index, (rlChirpCfg_t *) ptr);
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading Chirp parameters is not supported in ES1.0!!\r\n");
            }
        }
        else if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_FRAME_PARAM) != 0U)
        {
            /* For parameter of interest as the frame configuration
             * get the frame configuration. Only single frame configuration
             * supported.
             */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                if (sensorCfg->frameType == BSP_AR12XX_FRAME_TYPE_NORMAL)
                {
                    retVal =
                        rlGetFrameConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                     (rlFrameCfg_t *) ptr);
                }
                else if (sensorCfg->frameType == BSP_AR12XX_FRAME_TYPE_ADVANCED)
                {
                    retVal =
                        rlGetAdvFrameConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                     (rlAdvFrameCfg_t *) ptr);
                }
                else
                {
                    retVal = BSP_EFAIL;
                }
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading Frame parameters is not supported in ES1.0!!\r\n");
            }
        }
        else if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_DATA_FORMAT) != 0U)
        {
            /* For parameter of interest as the data format configuration
             * get the data format configuration.
             */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                retVal =
                    rlDeviceGetDataFmtConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                     (rlDevDataFmtCfg_t *) ptr);
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading Data Format parameters is not supported in ES1.0!!\r\n");
            }
        }
        else if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_DATA_PATH) != 0U)
        {
            /* For parameter of interest as the data path configuration
             * get the data path configuration.
             */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                retVal =
                    rlDeviceGetDataPathConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                     (rlDevDataPathCfg_t *) ptr);
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading Data Path parameters is not supported in ES1.0!!\r\n");
            }
        }
        else if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_LVDS_CLK) != 0U)
        {
            /* For parameter of interest as the data path clock configuration
             * get the data path clock configuration.
             */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                retVal =
                    rlDeviceGetDataPathClkConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                     (rlDevDataPathClkCfg_t *) ptr);
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading Data Path clock parameters is not supported in ES1.0!!\r\n");
            }
        }
        else if ((paramOfInterest & (UInt32) BSP_AR12XX_CONFIG_CSI_LANES) != 0U)
        {
            /* For parameter of interest as the CSI2 Lane configuration
             * get the CSI2 Lane configuration.
             */
            if (gBspAr12xxObj.arDeviceRevision > 1U)
            {
                retVal =
                    rlDeviceGetCsi2Config((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                     (rlDevCsi2Cfg_t *) ptr);
            }
            else
            {
                /* ES1.0 BSS firmware does not support reading back of params */
                retVal = BSP_EUNSUPPORTED_CMD;
                GT_0trace(
                    BspAppTrace, GT_INFO,
                    " AR12XX: Reading CSI2 Lane parameters is not supported in ES1.0!!\r\n");
            }
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }
    else
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

Int32 Bsp_ar12xxStartRadar(void)
{
    Int32  retVal         = BSP_SOK;
    UInt32 numToWait = (UInt32) gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade - (UInt32) 1;
    UInt32 origDevMap = gBspAr12xxObj.devIdxMap;
    /* Set a sleep time of 10 seconds for the AR12xx device boot time. This
     * is kept at a worst possible maximum time.
     */
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
    if (((Int32)gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade - (Int32)1)
            > (Int32) 0)
    {
        /* Modify the device map to ensure that the Slave device Ids are
         * selected.
         */
        gBspAr12xxObj.devIdxMap = (UInt32) origDevMap &
        ~((UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);
        gBspAr12xxObj.mmwl_bSensorStarted = 0U;
        retVal = (Int32) rlSensorStart((rlUInt8_t)gBspAr12xxObj.devIdxMap);
        if (BSP_SOK == retVal)
        {
            while ((gBspAr12xxObj.mmwl_bSensorStarted != numToWait) && (timeout > 0U))
            {
                BspOsal_sleep(1U);
                timeout--;
            }
            if (gBspAr12xxObj.mmwl_bSensorStarted != numToWait)
            {
                retVal = BSP_EFAIL;
            }
        }

    }

    gBspAr12xxObj.devIdxMap = (UInt32) ((UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);

    gBspAr12xxObj.mmwl_bSensorStarted = 0U;
    timeout = BSP_AR12XX_TIMEOUT_MAX;
    retVal = (Int32) rlSensorStart((rlUInt8_t)gBspAr12xxObj.devIdxMap);
    if (BSP_SOK == retVal)
    {
        while ((gBspAr12xxObj.mmwl_bSensorStarted != 1U) && (timeout > 0U))
        {
            BspOsal_sleep(1U);
            timeout--;
        }
    }
    gBspAr12xxObj.devIdxMap = origDevMap;
    return retVal;
}

Int32 Bsp_ar12xxStartTestPattern(rltestPattern_t * testPatternCfg)
{
    Int32 retVal = BSP_SOK;
    if (testPatternCfg != NULL)
    {
        retVal = (Int32) rlDeviceSetTestPatternConfig (
                        (rlUInt8_t)gBspAr12xxObj.devIdxMap,
                        (rltestPattern_t *) testPatternCfg);
    }
    return retVal;
}

Int32 Bsp_ar12xxGetWidthHeight(UInt32 deviceId, UInt32 *width, UInt32 *height)
{
    /* Expect the width and height of all cascaded devices to be coherent */
    UInt32 radarConfigIdx;
    UInt32 i;
    Int32  retVal = BSP_EFAIL;
    Bsp_Ar12xxConfigObj *sensorCfg;
    UInt32 maxAdcSamples = 0U, metaDataLen = 0U;
    UInt32 numRxAntenna  = 0U, numValsPerAdcSample = 0U;
    UInt32 antEnBitMap = 0U;
    UInt32 maxHeight = 0U, tempHeight = 0U;

    if (deviceId < BSP_AR12XX_MAX_DEVICES_SUPPORTED)
    {
        radarConfigIdx = gBspAr12xxObj.radarConfigId[deviceId];

        if ((radarConfigIdx < BSP_AR12XX_MAX_CONFIG_SUPPORTED) &&
            (height != NULL) &&
            (width != NULL))
        {
            sensorCfg = gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
            for (i = 0U; i < sensorCfg->numProfileCfgArgs; i++)
            {
                if (sensorCfg->profileCfgArgs[i].numAdcSamples > maxAdcSamples)
                {
                    maxAdcSamples = sensorCfg->profileCfgArgs[i].numAdcSamples;
                }
            }
            /* Count the number of Rx antenna */
            antEnBitMap  = (UInt32) sensorCfg->rfChanCfgArgs.rxChannelEn;
            numRxAntenna = (antEnBitMap & 0x1U) ? numRxAntenna + 1U : numRxAntenna;
            numRxAntenna = (antEnBitMap & 0x2U) ? numRxAntenna + 1U : numRxAntenna;
            numRxAntenna = (antEnBitMap & 0x4U) ? numRxAntenna + 1U : numRxAntenna;
            numRxAntenna = (antEnBitMap & 0x8U) ? numRxAntenna + 1U : numRxAntenna;
            /* Data out Format,
             * ------------------
             * b5:0 Packet 0 content selection
             * 000001 - ADC_DATA_ONLY
             * 000110 - CP_ADC_DATA
             * 001001 - ADC_CP_DATA
             * 110110 - CP_ADC_CQ_DATA
             *
             * ===================================================================
             * CP is Chirp Parameter information which is defined for each RX as
             * follows
             * ------------------
             * Bit    Description
             * ------------------
             * 11:0   Chirp number
             * 15:12  Reserved
             * 17:16  Channel number
             * 21:18  Profile number
             * 31:22  Reserved
             */
            if ((sensorCfg->dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 6) ||
                (sensorCfg->dataPathCfgArgs.transferFmtPkt0 == (rlUInt8_t) 9))
            {
                metaDataLen = 2U * numRxAntenna; /* 2 16 bit values */
            }
            if ((sensorCfg->dataFmtCfgArgs.adcFmt == RL_ADC_FORMAT_COMPLEX_1X) ||
                (sensorCfg->dataFmtCfgArgs.adcFmt == RL_ADC_FORMAT_COMPLEX_2X))
            {
                numValsPerAdcSample = 2U;
            }
            else
            {
                numValsPerAdcSample = 1U;
            }
            if (BSP_AR12XX_FRAME_TYPE_NORMAL == sensorCfg->frameType)
            {
                /* If Normal frames enabled calculate the frame Height */
                tempHeight = (UInt32)sensorCfg->frameCfgArgs->numLoops *
                (UInt32)(((UInt32)sensorCfg->frameCfgArgs->chirpEndIdx -
                         (UInt32)sensorCfg->frameCfgArgs->chirpStartIdx) + (UInt32)1);
                if (maxHeight < tempHeight)
                {
                    maxHeight = tempHeight;
                }
                retVal = BSP_SOK;
            }
            else if (BSP_AR12XX_FRAME_TYPE_ADVANCED == sensorCfg->frameType)
            {
                /* If Advanced frames enabled calculate the frame Height */
                for ( i = 0U; i < sensorCfg->advFrameCfgArgs.frameData.numSubFrames; i++)
                {
                    if (maxHeight < sensorCfg->advFrameCfgArgs.frameData.subframeDataCfg[i].totalChirps)
                    {
                        maxHeight = sensorCfg->advFrameCfgArgs.frameData.subframeDataCfg[i].totalChirps;
                    }
                }
                retVal = BSP_SOK;
            }

            if (BSP_SOK == retVal)
            {
                /* Get the width and height of the frame */
                *height = maxHeight;
                *width  = (UInt32)((UInt32)numRxAntenna *
                          (UInt32)numValsPerAdcSample * (UInt32)maxAdcSamples) +
                          (UInt32) metaDataLen;
            }
        }
    }

    return retVal;
}

Int32 Bsp_ar12xxStopRadar(void)
{
    Int32 retVal = BSP_SOK;
    Int32 numToWait = 0;
    /* Set a sleep time of 10 seconds for the AR12xx device boot time. This
     * is kept at a worst possible maximum time.
     */
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
    UInt32 tempDevIdxMap;
    if (gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade > 1U)
    {
        gBspAr12xxObj.mmwl_bSensorStarted = 0U;
        numToWait = (Int32)gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade - 1;
        /* Stop the slave sensor first */
        tempDevIdxMap = gBspAr12xxObj.devIdxMap &
            ~((UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);
        retVal = (Int32) rlSensorStop((rlUInt8_t) tempDevIdxMap);
        if (gBspAr12xxObj.arDeviceRevision > 1U)
        {
            if (BSP_SOK == retVal)
            {
                while ((gBspAr12xxObj.mmwl_bSensorStarted != numToWait) && (timeout > 0U))
                {
                    BspOsal_sleep(1U);
                    timeout--;
                }
                if (gBspAr12xxObj.mmwl_bSensorStarted != numToWait)
                {
                    retVal = BSP_EFAIL;
                }
            }
        }
    }
    if (BSP_SOK == retVal)
    {
        tempDevIdxMap = (UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId;
        gBspAr12xxObj.mmwl_bSensorStarted = 0U;
        numToWait = 1;
        timeout = BSP_AR12XX_TIMEOUT_MAX;
        retVal = (Int32) rlSensorStop((rlUInt8_t) tempDevIdxMap);
        if (gBspAr12xxObj.arDeviceRevision > 1U)
        {
            if (BSP_SOK == retVal)
            {
                while ((gBspAr12xxObj.mmwl_bSensorStarted != numToWait) && (timeout > 0U))
                {
                    BspOsal_sleep(1U);
                    timeout--;
                }
            }
        }
    }
    return retVal;
}

Int32 Bsp_ar12xxDeInit(void)
{
    Int32 retVal = BSP_SOK;
    UInt32 uartDevId = 0U;
    UInt32 ar12DevId = 0U;

    gBspAr12xxObj.stopRadarDevTsk = 1U;
    /* Dummy value post.
     */
    /* Dummy value enqueued to ensure the BspUtils_queGet will complete and
     * then gBspAr12xxObj.stopRadarDevTsk is read.
     */
    retVal = BspUtils_quePut(&gBspAr12xxObj.gpioAsyncEvtQueHandle,
                             &gBspAr12xxObj.stopRadarDevTsk,
                             BSP_OSAL_WAIT_FOREVER);
    BspOsal_sleep(100U);
    if (retVal == BSP_SOK)
    {
        retVal = rlDevicePowerOff();
    }

    if (retVal == BSP_SOK)
    {
        /* Delete the queue and the task created */
        BspUtils_queDelete(&gBspAr12xxObj.gpioAsyncEvtQueHandle);
        BspOsal_taskDelete(&gBspAr12xxObj.radarDevTskHndl);

        for (uartDevId = 0; uartDevId < BSP_AR12XX_NUM_UART_INST; uartDevId++)
        {
            if (gBspAr12xxObj.uartDevMap[uartDevId] != 0xFF)
            {
                /* Delete the UART Instance Handles */
                GIO_delete((GIO_Handle *)
                &gBspAr12xxObj.uartTxHandle[gBspAr12xxObj.
                uartDevMap[uartDevId]]);
                GIO_delete((GIO_Handle *)
                &gBspAr12xxObj.uartRxHandle[gBspAr12xxObj.
                uartDevMap[uartDevId]]);
            }
        }
        for (ar12DevId = 0U; ar12DevId < BSP_AR12XX_MAX_DEVICES_SUPPORTED;
             ar12DevId++)
        {
            gBspAr12xxObj.radarConfigId[ar12DevId] =
                BSP_AR12XX_MAX_CONFIG_SUPPORTED;
        }
    }
    return (retVal);
}

Int32 Bsp_ar12xxUnRegisterConfig(
    char configName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH])
{
    Int32  retVal = BSP_SOK;
    UInt32 i;
    UInt32 numSensorsSupported = sizeof (gBspAr12xxSensorCfgList) /
                                 sizeof (Bsp_ar12xxSensorObj);
    for (i = 0; i < numSensorsSupported; i++)
    {
        if (gBspAr12xxSensorCfgList[i].isUsed == 1U)
        {
            if ((UInt32) strcmp(gBspAr12xxSensorCfgList[i].radarConfigName,
                                configName) == 0U)
            {
                strcpy(gBspAr12xxSensorCfgList[i].radarConfigName, "\0");
                gBspAr12xxSensorCfgList[i].sensorConfigObj = NULL;
                gBspAr12xxSensorCfgList[i].isUsed          = 0U;
                break;
            }
        }
    }
    if (i == numSensorsSupported)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

Int32 Bsp_ar12xxSwitchConfig(
    UInt32 deviceId,
    char configName[BSP_AR12XX_MAX_SENSOR_NAME_LENGTH])
{
    Int32  retVal = BSP_SOK;
    UInt32 i;
    UInt32 numSensorsSupported = sizeof (gBspAr12xxSensorCfgList) /
                                 sizeof (Bsp_ar12xxSensorObj);
    for (i = 0; i < numSensorsSupported; i++)
    {
        if ((UInt32)
            strcmp(gBspAr12xxSensorCfgList[i].radarConfigName, configName) ==
            0U)
        {
            if (deviceId < BSP_AR12XX_MAX_DEVICES_SUPPORTED)
            {
                /* Set the radar ID to get the desired configuration parameters */
                gBspAr12xxObj.radarConfigId[deviceId] = i;
            }
            else
            {
                retVal = BSP_EINVALID_PARAMS;
            }
            break;
        }
    }
    if (i == numSensorsSupported)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

Int32 Bsp_ar12xxEnableDummySource(UInt32 deviceId,
    Bsp_Ar12xxTestSource *testSource)
{
    Int32 retVal = BSP_SOK;
    rlTestSourceEnable_t testSrcEnArgs = {0};
    retVal = rlSetTestSourceConfig((rlUInt8_t)(1U << deviceId), testSource);
    if (retVal == BSP_SOK)
    {
        testSrcEnArgs.tsEnable = 1;
        testSrcEnArgs.reserved = 1;
        retVal = rlTestSourceEnable((rlUInt8_t)(1U << deviceId), &testSrcEnArgs);
    }
    return (retVal);
}

Int32 Bsp_ar12xxSetTestSourceSeeds(void)
{
    Int32  retVal     = BSP_SOK;
    UInt32 tempRegVal = 0U;
    UInt32 addrVal    = 0U;
    UInt32 regVal     = 0U;
    UInt32 i;
    UInt32 addrArr[] = {
                        0x432001A4U,
                        0x432001A8U,
                        0x432001ACU,
                        0x432001B0U,
                        0x432001B4U,
                        0x432001B8U,
                        0x432001BCU,
                        0x432001C0U,
                        0x432001C4U,
                        0x432001C8U
                        };

    for (i = 0U ; i < (sizeof(addrArr)/sizeof(UInt32)) ; i++)
    {
        addrVal = addrArr[i];

        regVal  = 0x0U;
        retVal  = (Int32) Bsp_ar12xxDeviceSetInternalConf(gBspAr12xxObj.devIdxMap,
                                         addrVal, regVal);
    }

    if (retVal == BSP_SOK)
    {
        addrVal = 0x432001D0U;
        retVal  = (Int32) Bsp_ar12xxDeviceGetInternalConf(
            gBspAr12xxObj.devIdxMap, addrVal, &tempRegVal);
    }
    if (retVal == BSP_SOK)
    {
        addrVal = 0x432001D0U;
        tempRegVal = tempRegVal | 0x3U;
        retVal  = (Int32)
            Bsp_ar12xxDeviceSetInternalConf(gBspAr12xxObj.devIdxMap,
                                    addrVal, tempRegVal);
    }
    return retVal;
}

Int32 Bsp_ar12xxEraseFirmware(void)
{
    Int32  retVal      = BSP_SOK;
    UInt32 bkupSopMode = 0;
    UInt32 origDevMap = gBspAr12xxObj.devIdxMap;

    gBspAr12xxObj.devIdxMap = (UInt32) ((UInt32)0x1U << (UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);
    /* Register the different callbacks used by the radar interface and
     * power on the radar device.
     */
    bkupSopMode = gBspAr12xxObj.initPrmsCopy.sopMode;
    /* Power on the device and program the SOP to functional */
    retVal = Bsp_ar12xxRadarDeviceOn();
    if (retVal == BSP_SOK)
    {
        /* Get and store the device revision */
        gBspAr12xxObj.arDeviceRevision = Bsp_ar12xxGetDeviceRevision();
    }
    if (retVal == BSP_SOK)
    {
        BspOsal_sleep(100U);
        gBspAr12xxObj.pauseRadarDevTsk = 1U;
        retVal = Bsp_ar12xxGpioPowerOffDeviceCb(gBspAr12xxObj.initPrmsCopy.masterDevId);
    }
    if (retVal == BSP_SOK)
    {
        BspOsal_sleep(100U);
        gBspAr12xxObj.pauseRadarDevTsk = 0U;
        gBspAr12xxObj.initPrmsCopy.sopMode = 5U;
        /* Power on the device and program the SOP to flashing */
        retVal = Bsp_ar12xxGpioPowerOnDeviceCb(gBspAr12xxObj.initPrmsCopy.masterDevId);
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_ar12xxGpioUartSelect((UInt32)gBspAr12xxObj.initPrmsCopy.masterDevId);
    }
    if (retVal == BSP_SOK)
    {
        /* Allow ROM to run to initialize. Worst case time assumed can be
         * optimized */
        BspOsal_sleep(500U);
        /* Connect to the AR12xx via RS232 */
        retVal = Bsp_ar12xxUartConnect(gBspAr12xxObj.initPrmsCopy.masterDevId, &gBspAr12xxObj);
    }
    if (retVal == BSP_SOK)
    {
        /* Erase the AR12 Flash */
        retVal = Bsp_ar12xxFmwEraseFlash(gBspAr12xxObj.initPrmsCopy.masterDevId, &gBspAr12xxObj);
    }
    /* Restore the input SOP Mode */
    gBspAr12xxObj.initPrmsCopy.sopMode = bkupSopMode;
    gBspAr12xxObj.devIdxMap = origDevMap;
    return retVal;
}

Int32 Bsp_ar12xxFlashFirmware(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 i      = 0;
    for (i = 0U; i < gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade; i++)
    {
        GT_0trace(BspDeviceTrace, GT_INFO, " AR12XX: Flashing BSS...\n\r");
        /* Flash the BIST subsystem firmware */
        retVal = Bsp_ar12xxFmwSectionFlash(i,&gBspAr12xxObj,
                                           BSP_AR12XX_SECTIONTYPE_BSS_BUILD);
        GT_0trace(BspDeviceTrace, GT_INFO,
                  " AR12XX: Flashing BSS finished.\n\r");
        /* Flash the Master subsystem firmware */
        if (retVal == BSP_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_INFO, " AR12XX: Flashing MSS...\n\r");
            retVal = Bsp_ar12xxFmwSectionFlash(i,
                &gBspAr12xxObj,
                BSP_AR12XX_SECTIONTYPE_MSS_BUILD);
            GT_0trace(BspDeviceTrace, GT_INFO,
                      " AR12XX: Flashing MSS finished.\n\r");
        }
        /* Flash the Firmware Configuration */
        if (retVal == BSP_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_INFO,
                      " AR12XX: Flashing Config...\n\r");
            retVal = Bsp_ar12xxFmwSectionFlash(i,
                &gBspAr12xxObj,
                BSP_AR12XX_SECTIONTYPE_CONFIG_INFO);
            GT_0trace(BspDeviceTrace, GT_INFO,
                      " AR12XX: Flashing Config finished.\n\r");
        }
        if (retVal != BSP_SOK)
        {
            break;
        }
    }
    return retVal;
}

Bsp_AR12xxConnType Bsp_ar12xxGetConnType(void)
{
    Bsp_BoardId boardId;

    if ((gBspAr12xxObj.arConnType == BSP_AR12XX_CONN_TYPE_UNKNOWN) ||
            (gBspAr12xxObj.arConnType >= BSP_AR12XX_CONN_TYPE_COUNT))
    {
        boardId = Bsp_boardGetId();
        if ((boardId == BSP_BOARD_TDA3XX_RVP_ALPHA)
                || (boardId == BSP_BOARD_TDA3XX_RVP_BETA)
                || (boardId == BSP_BOARD_TDA3XX_RVP_A))
        {
            if(Bsp_boardGetBaseBoardRev() == BSP_BOARD_RADAR_DC_REV_1){
                gBspAr12xxObj.arConnType = BSP_AR12XX_CONN_TYPE_DIRECT;
            }
            else
            {
                gBspAr12xxObj.arConnType = BSP_AR12XX_CONN_TYPE_FPDLINK;
            }
        }
        else if (boardId == BSP_BOARD_VISION)
        {
            gBspAr12xxObj.arConnType = BSP_AR12XX_CONN_TYPE_FPDLINK;
        }
        else
        {
            gBspAr12xxObj.arConnType = BSP_AR12XX_CONN_TYPE_DIRECT;
        }
    }

    return gBspAr12xxObj.arConnType;
}

Int32 Bsp_ar12xxConfigMonitor(UInt32 deviceId,
                              Bsp_Ar12xxMonConfigObj *sensorMonCfg)
{
    Int32  retVal         = BSP_SOK;
    UInt8 devIdxMap      = (UInt8)(1U << deviceId);
    /* Monitorring is not supported on AWR1243 ES1.0 device */
    if ((gBspAr12xxObj.arDeviceRevision > 1U) &&
       ((gBspAr12xxObj.devIdxMap & (UInt32)devIdxMap) != 0U))
    {
        if (sensorMonCfg->monTimeUnitCfg != NULL)
        {
            retVal = rlRfSetCalMonTimeUnitConfig(devIdxMap,
                            sensorMonCfg->monTimeUnitCfg);
        }
        if ((sensorMonCfg->calMonFreqLimitCfg != NULL) && (retVal == BSP_SOK))
        {
            retVal = rlRfSetCalMonFreqLimitConfig(devIdxMap,
                            sensorMonCfg->calMonFreqLimitCfg);
        }
        if ((sensorMonCfg->monAnaEnable != NULL) && (retVal == BSP_SOK))
        {
            /* Analog monitoring configuration */
            retVal = rlRfAnaMonConfig(devIdxMap,
                                    sensorMonCfg->monAnaEnable);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->tempMonCfg != NULL))
        {
            /* Temperature sensor monitoring configuration */
            retVal = rlRfTempMonConfig(devIdxMap,
                                    sensorMonCfg->tempMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->rxGainPhaseMonCfg != NULL))
        {
            /* RX gain and phase monitoring configuration */
            retVal = rlRfRxGainPhMonConfig(devIdxMap,
                                        sensorMonCfg->rxGainPhaseMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->rxNoiseMonCfg != NULL))
        {
            /* RX noise monitoring configuration */
            retVal = rlRfRxNoiseMonConfig(devIdxMap,
                                        sensorMonCfg->rxNoiseMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->rxIfStageMonCfg != NULL))
        {
            /* RX IF stage monitoring configuration */
            retVal = rlRfRxIfStageMonConfig(devIdxMap,
                                            sensorMonCfg->rxIfStageMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->allTxPowMonCfg != NULL))
        {
            /* TX power monitoring configuration */
            retVal = rlRfTxPowrMonConfig(devIdxMap,
                                        sensorMonCfg->allTxPowMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->allTxBallBreakMonCfg != NULL))
        {
            /* TX ballbreak monitoring configuration */
            retVal = rlRfTxBallbreakMonConfig(devIdxMap,
                                            sensorMonCfg->allTxBallBreakMonCfg);
        }
        if ((retVal == BSP_SOK) &&
            (sensorMonCfg->txGainPhaseMismatchMonCfg != NULL))
        {
            /* TX gain and phase mismatch monitoring configuration */
            retVal = rlRfTxGainPhaseMismatchMonConfig(
                        devIdxMap,
                        sensorMonCfg->txGainPhaseMismatchMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->allTxBpmMonCfg != NULL))
        {
            /* TX BPM monitoring configuration */
            retVal = rlRfTxBpmMonConfig(devIdxMap,
                                        sensorMonCfg->allTxBpmMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->synthFreqMonCfg != NULL))
        {
            /* Synthesizer frequency monitoring configuration */
            retVal = rlRfSynthFreqMonConfig(devIdxMap,
                                            sensorMonCfg->synthFreqMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->extAnaSigMonCfg != NULL))
        {
            /* External analog signals monitoring configuration */
            retVal = rlRfExtAnaSignalsMonConfig(devIdxMap,
                                                sensorMonCfg->extAnaSigMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->allTxIntAnaSigMonCfg != NULL))
        {
            /* Internal signals in the TX path monitoring configuration */
            retVal = rlRfTxIntAnaSignalsMonConfig(
                        devIdxMap,
                        sensorMonCfg->allTxIntAnaSigMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->rxIntAnaSigMonCfg != NULL))
        {
            /* Internal Analog signals monitoring configuration */
            retVal = rlRfRxIntAnaSignalsMonConfig(devIdxMap,
                                                sensorMonCfg->rxIntAnaSigMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->pmClkLoIntAnaSigMonCfg != NULL))
        {
            /* Internal signals for PM, CLK and LO monitoring configuration */
            retVal = rlRfPmClkLoIntAnaSignalsMonConfig(
                        devIdxMap,
                        sensorMonCfg->pmClkLoIntAnaSigMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->gpadcIntAnaSigMonCfg != NULL))
        {
            /* Internal signals for GPADC monitoring configuration */
            retVal = rlRfGpadcIntAnaSignalsMonConfig(
                        devIdxMap,
                        sensorMonCfg->gpadcIntAnaSigMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->pllControlVoltMonCfg != NULL))
        {
            /* Internal signals for PLL control voltage monitoring configuration */
            retVal = rlRfPllContrlVoltMonConfig(
                        devIdxMap,
                        sensorMonCfg->pllControlVoltMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->dualClkCompMonCfg != NULL))
        {
            /* Internal signals for DCC based clock monitoring configuration */
            retVal = rlRfDualClkCompMonConfig(
                        devIdxMap,
                        sensorMonCfg->dualClkCompMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->rxSatMonCfg != NULL))
        {
            /* RX saturation monitoring configuration. The output comes as a
             * part of CQ data.
             */
            retVal = rlRfRxIfSatMonConfig(
                        devIdxMap,
                        sensorMonCfg->rxSatMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->sigImgMonCfg != NULL))
        {
            /* Signal and image band energy monitoring configuration.
             * The output comes as a part of CQ data.
             */
            retVal = rlRfRxSigImgMonConfig(
                        devIdxMap,
                        sensorMonCfg->sigImgMonCfg);
        }
        if ((retVal == BSP_SOK) && (sensorMonCfg->runTimeCalCfg != NULL))
        {
            UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
            gBspAr12xxObj.mmwl_runTimeCalibDone = 0U;
            retVal = rlRfRunTimeCalibConfig(devIdxMap,
                                            sensorMonCfg->runTimeCalCfg);
            while ((gBspAr12xxObj.mmwl_runTimeCalibDone == 0U) &&
                         (timeout > 0U) && (retVal == BSP_SOK))
            {
                BspOsal_sleep(1U);
                timeout--;
            }
            if ((timeout == 0U) || (retVal != BSP_SOK))
            {
                GT_1trace( BspAppTrace, GT_INFO,
                " AR12XX: Run Time Calib Failed %d \r\n",retVal);
                retVal = BSP_EFAIL;
            }
        }
        if ((retVal == BSP_SOK) &&
            (sensorMonCfg->calibDataStoreRestore != NULL))
        {
            retVal = (Int32) rlRfCalibDataStore(devIdxMap,
                                            sensorMonCfg->calibDataStoreRestore);
        }
        /* Register the call back function for monitorring */
        gBspAr12xxObj.monAppCallBack = sensorMonCfg->monReportCallBackFunc;
    }
    else
    {
        retVal = BSP_EUNSUPPORTED_CMD;
    }
    return retVal;
}

Int32 Bsp_ar12xxRestoreCalibData(UInt32 deviceId,
                                 rlCalibrationData_t * calibDataStoreRestore)
{
    Int32 retVal = BSP_SOK;
    UInt32 devIdxMap      = ((UInt32)1U << (UInt32) deviceId);
    if (calibDataStoreRestore != NULL)
    {
        UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
        gBspAr12xxObj.radarRfInitComplete = 0U;
        retVal = (Int32) rlRfCalibDataRestore( (UInt8) devIdxMap,
                                              calibDataStoreRestore);
        while ((gBspAr12xxObj.radarRfInitComplete == 0U)&&
                    (timeout > 0U) && (retVal == BSP_SOK))
        {
            BspOsal_sleep(1U);
            timeout--;
        }
        if ((timeout == 0U) || (retVal != BSP_SOK))
        {
            GT_1trace( BspAppTrace, GT_INFO,
            " AR12XX: Calib Restore Failed %d \r\n",retVal);
            retVal = BSP_EFAIL;
        }
    }
    return retVal;
}

Int32 Bsp_ar12xxGetTemperature(UInt32 deviceId, rlRfTempData_t * readTempData)
{
    Int32 retVal = BSP_SOK;
    if (((UInt32)((UInt32)1U << deviceId) & gBspAr12xxObj.devIdxMap) != 0x0U)
    {
        if (readTempData != NULL)
        {
            retVal =(Int32) rlRfGetTemperatureReport((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                                     readTempData);
        }
        else
        {
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }
    return retVal;
}

Int32 Bsp_ar12xxReconfigChirp(UInt32 deviceId,
                              rlDynChirpCfg_t *dynChirpData,
                              UInt32 numChirpSeg)
{
    Int32 retVal = BSP_SOK;
    UInt32 devIdxMap      = ((UInt32)1U << deviceId);
    if ((dynChirpData != NULL) && ((gBspAr12xxObj.devIdxMap & devIdxMap) != 0U))
    {
        retVal = rlSetDynChirpCfg((UInt8)devIdxMap, (UInt16)numChirpSeg,
                                  &dynChirpData);
        if(retVal == BSP_SOK)
        {
            rlDynChirpEnCfg_t dynChirpEnCfg = {
                .reserved = 0
            };
            /* Enable dynamic chirp */
            retVal = rlSetDynChirpEn ((UInt8)devIdxMap,
                                      &dynChirpEnCfg);
        }
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }
    return retVal;
}
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static Int32 Bsp_ar12xxCheckInitParams(const Bsp_Ar12xxInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    UInt32 i = 0;
    for ( i = 0; i < initPrms->numRadarDevicesInCascade; i++)
    {
        if (initPrms->devParams[i].edmaHandle == NULL)
        {
            retVal += BSP_EINVALID_PARAMS;
        }
        if (initPrms->numRadarDevicesInCascade >
            BSP_AR12XX_MAX_DEVICES_SUPPORTED)
        {
            retVal += BSP_EINVALID_PARAMS;
        }
        if (Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_DIRECT)
        {
            if (initPrms->devParams[i].mcSpiDevInst > BSP_AR12XX_NUM_MCSPI_INST)
            {
                retVal += BSP_EINVALID_PARAMS;
            }
        }
        else
        {
            if (initPrms->devParams[i].i2cDevInst > BSP_DEVICE_I2C_INST_ID_MAX)
            {
                retVal += BSP_EINVALID_PARAMS;
            }
        }
    }
    if (initPrms->masterDevId >= BSP_AR12XX_MAX_DEVICES_SUPPORTED)
    {
        retVal += BSP_EINVALID_PARAMS;
    }
    return retVal;
}
static Int32 Bsp_ar12xxCsiTrimConfig(void)
{
    Int32  retVal     = BSP_SOK;
    UInt32 addrVal    = 0U;
    UInt32 regVal     = 0U;

    /* LVDS Termination resistance programming */
    addrVal = 0xFFFFE14CU;
    regVal  = 0x61616161U;
    retVal  = Bsp_ar12xxDeviceSetInternalConf(
        gBspAr12xxObj.devIdxMap,
        addrVal, regVal);
    if (retVal == BSP_SOK)
    {
        /* LVDS Termination resistance programming */
        addrVal = 0xFFFFE150U;
        regVal  = 0x6161U;
        retVal  = Bsp_ar12xxDeviceSetInternalConf(
            gBspAr12xxObj.devIdxMap,
            addrVal, regVal);
    }
    return retVal;
}

static int32_t Bsp_ar12xxSetDeviceCrcType(uint8_t deviceMap)
{
    int32_t         retVal = BSP_SOK;
    rlDevMiscCfg_t  devMiscCfg = {0};
    /* Set the CRC Type for Async Event from MSS */
    devMiscCfg.aeCrcConfig = RL_CRC_TYPE_16BIT_CCITT;
    retVal = rlDeviceSetMiscConfig(deviceMap, &devMiscCfg);

    return retVal;
}
