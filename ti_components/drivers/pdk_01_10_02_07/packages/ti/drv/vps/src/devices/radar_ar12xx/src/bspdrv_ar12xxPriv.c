/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file bspdrv_ar12xxPriv.c
 *
 *  \brief  This file contains function definitions used privately by the
 *          AR12xx Radar sensor driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bspdrv_ar12xxPriv.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <rl_messages.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Radar Communication Timeout */
#define BSP_AR12XX_RADAR_COMM_TIMEOUT    (1000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  BSP callback to set appropriate flags which indicate certain
 *          necessary radar boot time processes are completed. This status is
 *          indicated via flags.
 *
 *  \param devIdx       AR12 device index
 *  \param sbId         Protocol payload Sub block Id
 *  \param sbLen        Length of sub block
 *  \param payload      Protocol payload message data
 *
 *  \return None
 */
static void Bsp_ar12xxAsyncEvtHandlerCb(UInt8 devIdx, UInt16 sbId, UInt16 sbLen,
                                        UInt8 *payload);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_ar12xxRadarDeviceOn(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 count = Bsp_ar12xxCountBits(gBspAr12xxObj.devIdxMap);

    /* Set a sleep time of 10 seconds for the AR12xx device boot time. This
     * is kept at a worst possible maximum time.
     */
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;

    gBspAr12xxObj.radarInitCompleteFlag = 0U;
    /* Start the first device */
    retVal = rlDevicePowerOn((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                             gBspAr12xxObj.rlApp_ClientCtx);
    if (retVal == BSP_SOK)
    {
        /* Wait for the device to complete its initializaton */
        while ((gBspAr12xxObj.radarInitCompleteFlag != count)
            && (timeout != 0U))
        {
            /* Sleep for 1 ms */
            BspOsal_sleep(1U);
            timeout--;
        }
    }
    if (gBspAr12xxObj.radarInitCompleteFlag != count)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  " AR12XX: Radar Device Power On failed!!\r\n");
        retVal = BSP_EFAIL;
    }
    return retVal;
}

Int32 Bsp_ar12xxRegisterCallbacks(void)
{
    Int32          retVal          = BSP_SOK;
    rlClientCbs_t *RlApp_ClientCtx = &gBspAr12xxObj.rlApp_ClientCtx;

    if(Bsp_ar12xxGetConnType() == BSP_AR12XX_CONN_TYPE_FPDLINK)
    {
        /* Initialize SPI Interface using I2C to SPI Bridge*/
        RlApp_ClientCtx->comIfCb.rlComIfOpen  = &Bsp_spi2cOpenCb;
        RlApp_ClientCtx->comIfCb.rlComIfClose = &Bsp_spi2cCloseCb;
        RlApp_ClientCtx->comIfCb.rlComIfRead  = &Bsp_spi2cReadCb;
        RlApp_ClientCtx->comIfCb.rlComIfWrite = &Bsp_spi2cWriteCb;
        RlApp_ClientCtx->devCtrlCb.rlDeviceEnable =
            &Bsp_ar12xxFPDPowerOnDeviceCb;
	}
    else
    {
        /* Initialize SPI Interface using direct SPI commands*/
        RlApp_ClientCtx->comIfCb.rlComIfOpen  = &Bsp_ar12xxSpiOpenCb;
        RlApp_ClientCtx->comIfCb.rlComIfClose = &Bsp_ar12xxSpiCloseCb;
        RlApp_ClientCtx->comIfCb.rlComIfRead  = &Bsp_ar12xxSpiReadCb;
        RlApp_ClientCtx->comIfCb.rlComIfWrite = &Bsp_ar12xxSpiWriteCb;
        RlApp_ClientCtx->devCtrlCb.rlDeviceEnable =
            &Bsp_ar12xxGpioPowerOnDeviceCb;
    }

    /* Mutex */
    RlApp_ClientCtx->osiCb.mutex.rlOsiMutexCreate = &Bspdrv_A12xxSemObjCreateCb;
    RlApp_ClientCtx->osiCb.mutex.rlOsiMutexLock   = &Bsp_ar12xxSemObjWaitCb;
    RlApp_ClientCtx->osiCb.mutex.rlOsiMutexUnLock = &Bsp_ar12xxSemObjPendCb;
    RlApp_ClientCtx->osiCb.mutex.rlOsiMutexDelete = &Bsp_ar12xxSemObjDeleteCb;

    /* Semaphore */
    RlApp_ClientCtx->osiCb.sem.rlOsiSemCreate = &Bspdrv_A12xxSemObjCreateCb;
    RlApp_ClientCtx->osiCb.sem.rlOsiSemWait   = &Bsp_ar12xxSemObjWaitCb;
    RlApp_ClientCtx->osiCb.sem.rlOsiSemSignal = &Bsp_ar12xxSemObjPendCb;
    RlApp_ClientCtx->osiCb.sem.rlOsiSemDelete = &Bsp_ar12xxSemObjDeleteCb;

    RlApp_ClientCtx->osiCb.queue.rlOsiSpawn      = &Bsp_ar12xxRadarTaskPost;

    RlApp_ClientCtx->devCtrlCb.rlDeviceDisable =
        &Bsp_ar12xxGpioPowerOffDeviceCb;

    RlApp_ClientCtx->devCtrlCb.rlDeviceMaskHostIrq =
        &Bsp_ar12xxGpioIRQMaskCb;
    RlApp_ClientCtx->devCtrlCb.rlDeviceUnMaskHostIrq =
        &Bsp_ar12xxGpioIRQUnMaskCb;
    RlApp_ClientCtx->devCtrlCb.rlDeviceWaitIrqStatus      = NULL;
    RlApp_ClientCtx->devCtrlCb.rlRegisterInterruptHandler =
        &Bsp_ar12xxGpioIntrRegisterCb;
    RlApp_ClientCtx->devCtrlCb.rlDeviceWaitIrqStatus =
        &Bsp_ar12xxGpioWaitHostIrqLow;

    RlApp_ClientCtx->timerCb.rlDelay = &Bsp_ar12xxSleepCb;

    RlApp_ClientCtx->eventCb.rlAsyncEvent = &Bsp_ar12xxAsyncEvtHandlerCb;
    /* Time in milli seconds */
    RlApp_ClientCtx->ackTimeout         = BSP_AR12XX_RADAR_COMM_TIMEOUT;
    RlApp_ClientCtx->crcType            = RL_CRC_TYPE_16BIT_CCITT;
    RlApp_ClientCtx->crcCb.rlComputeCRC = &Bsp_ar12xxComputeCrc;

    RlApp_ClientCtx->dbgCb.dbgLevel=  RL_DBG_LEVEL_VERBOSE;
    RlApp_ClientCtx->dbgCb.rlPrint =  &BspOsal_printf;

    return retVal;
}

Int32 Bsp_ar12xxPrintVersion(void)
{
    Int32       retVal = BSP_EFAIL;
    rlVersion_t ver    = {0};

    retVal = rlDeviceGetVersion((rlUInt8_t)gBspAr12xxObj.devIdxMap, &ver);

    if (retVal == BSP_SOK)
    {
        GT_4trace(BspDeviceTrace, GT_INFO,
                  " AWR12XX: Version Master : %d.%d.%d.%d\r\n",
                  ver.master.fwMajor,
                  ver.master.fwMinor,
                  ver.master.fwBuild,
                  ver.master.fwDebug);

        GT_4trace(BspDeviceTrace, GT_INFO,
                  " AWR12XX: Version RF:%d.%d.%d.%d\r\n",
                  ver.rf.fwMajor,
                  ver.rf.fwMinor,
                  ver.rf.fwBuild,
                  ver.rf.fwDebug);
        GT_4trace(BspDeviceTrace, GT_INFO,
                  " AWR12XX: Version mmWaveLink:%d.%d.%d.%d\r\n",
                  ver.mmWaveLink.major,
                  ver.mmWaveLink.minor,
                  ver.mmWaveLink.build,
                  ver.mmWaveLink.debug);
        GT_3trace(BspDeviceTrace, GT_INFO,
                  " AWR12XX: Version Master Patch[dd.mm.yy]:%d.%d.%d\r\n",
                  ver.master.patchDay,
                  ver.master.patchMonth,
                  ver.master.patchYear);

        GT_3trace(BspDeviceTrace, GT_INFO,
                  " AWR12XX: Version RF Patch[dd.mm.yy]:%d.%d.%d\r\n",
                  ver.rf.patchDay,
                  ver.rf.patchMonth,
                  ver.rf.patchYear);
    }
    return retVal;
}

Int32 Bsp_ar12xxConfigProfile(UInt32 radarConfigIdx)
{
    Int32  retVal = BSP_SOK;
    UInt32 idx    = 0U;
    Bsp_Ar12xxConfigObj *sensorCfg =
        gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;

    for (idx = 0U; idx < sensorCfg->numProfileCfgArgs; idx++)
    {
        /* Configure the profile parameters for all the supported frame
         * indices.
         */
        retVal += rlSetProfileConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap, 1U,
                                     &sensorCfg->profileCfgArgs[idx]);
    }

    return retVal;
}

Int32 Bsp_ar12xxConfigChirp(UInt32 radarConfigIdx)
{
    Int32  retVal = BSP_SOK;
    Bsp_Ar12xxConfigObj *sensorCfg =
        gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
    UInt32 idx    = 0U;
    /* Define this for debug purpose */
    for (idx = 0U; idx < sensorCfg->numChirpCfgArgs; idx++)
    {
        /* Perform the chirp configuration */
        retVal += (Int32) rlSetChirpConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap, 1U,
                                           &sensorCfg->chirpCfgArgs[idx]);
    }
    return retVal;
}

UInt32 Bsp_ar12xxCalcMaxSleepTime(UInt32 radarConfigIdx)
{
    UInt32 maxSleepTime = 0U, maxNumLoops = 0U;
    Bsp_Ar12xxConfigObj *sensorCfg =
        gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
    UInt32 idx;
    UInt32 sleepTime;

    maxNumLoops = sensorCfg->frameCfgArgs->numLoops;

    for (idx = 0; idx < sensorCfg->numProfileCfgArgs; idx++)
    {
        sleepTime = (sensorCfg->profileCfgArgs[idx].idleTimeConst +
                     sensorCfg->profileCfgArgs[idx].rampEndTime) *
                    maxNumLoops;
        if (sleepTime > maxSleepTime)
        {
            maxSleepTime = sleepTime;
        }
    }
    /* Convert to milli seconds */
    maxSleepTime = (maxSleepTime * 10U) / 1000000U;
    return maxSleepTime;
}

Int32 Bsp_ar12xxConfigBpmCommon(UInt32 radarConfigIdx)
{
    Int32 retVal = BSP_SOK;
    Bsp_Ar12xxConfigObj *sensorCfg =
        gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;

    /* Perform the bpm common configuration */
    retVal += (Int32) rlSetBpmCommonConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                           &sensorCfg->bpmCommnCfgArgs);
    return retVal;
}

Int32 Bsp_ar12xxConfigBpmChirp(UInt32 radarConfigIdx)
{
    Int32  retVal = BSP_SOK;
    Bsp_Ar12xxConfigObj *sensorCfg =
        gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
    UInt32 idx    = 0U;
    /* Define this for debug purpose */
    for (idx = 0U; idx < sensorCfg->numBpmChirpCfgArgs; idx++)
    {
        /* Perform the bpm chirp configuration */
        retVal += (Int32) rlSetBpmChirpConfig((rlUInt8_t)gBspAr12xxObj.devIdxMap,
                                              &sensorCfg->bpmChirpCfgArgs[idx]);
    }
    return retVal;
}

UInt32 Bsp_ar12xxGetDeviceRevision(void)
{
    UInt32 arDeviceConnected = 0U;
    rlFwVersionParam_t data  = {0};
    Int32  retVal = BSP_SOK;

    /* Get the version of the silicon and load the firmware
     * accordingly
     */
    retVal = rlDeviceGetMssVersion((rlUInt8_t)gBspAr12xxObj.devIdxMap, &data);
    if (retVal == BSP_SOK)
    {
        /* AR12 ES1.0 MSS ROM version is 0.6.0.7.
         * AR12 ES1.0 MSS Firmware version is 1.6.0.12
         */
        if ((data.hwMajor == (UInt8) 0x1) &&
            (data.hwMinor == (UInt8) 0x0))
        {
            arDeviceConnected = 1U;
        }
        else if ((data.hwMajor == (UInt8) 0x2) &&
                (data.hwMinor == (UInt8) 0x0))
        {
            arDeviceConnected = 2U;
        }
        else
        {
            arDeviceConnected = 3U;
        }
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    switch (arDeviceConnected)
    {
        case 1U:
            GT_0trace(BspAppTrace, GT_INFO,
                      " AR12XX: ES1.0 Device detected!!\r\n");
            break;
        case 2U:
            GT_0trace(BspAppTrace, GT_INFO,
                      " AR12XX: ES2.0 Device detected!!\r\n");
            break;
		case 3U:
            GT_0trace(BspAppTrace, GT_INFO,
                      " AR12XX: ES3.0 Device detected!!\r\n");
            break;
        default:
            GT_0trace(BspAppTrace, GT_ERR,
                      " AR12XX: Device type not detected!!\r\n");
            break;
    }

    return arDeviceConnected;
}

Int32 Bsp_ar12xxBootSlaves(void)
{
    Int32 retVal = BSP_SOK;
    UInt32 radarConfigIdx =
        gBspAr12xxObj.radarConfigId[gBspAr12xxObj.initPrmsCopy.masterDevId];
    Bsp_Ar12xxConfigObj *sensorCfg;
    /* Set a sleep time of 10 seconds for the AR12xx device boot time. This
     * is kept at a worst possible maximum time.
     */
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;

    /* Set the master channel configuration with cascaded enabled to have
     * the clock running for the slaves before power on.
     */
    if (radarConfigIdx < BSP_AR12XX_MAX_CONFIG_SUPPORTED)
    {
        sensorCfg = gBspAr12xxSensorCfgList[radarConfigIdx].sensorConfigObj;
        /* MULTICHIP_MASTER has the cascading set to 1 */
        /* Configure the Rx and Tx channel configuration */
            retVal = (Int32) rlSetChannelConfig(
                        (rlUInt8_t) (0x1U << gBspAr12xxObj.initPrmsCopy.masterDevId),
                        &sensorCfg->rfChanCfgArgs);
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }
    /* Start the rest if required */
    if (retVal == BSP_SOK)
    {
        gBspAr12xxObj.radarInitCompleteFlag = 0;
        retVal = rlDeviceAddDevices((rlUInt8_t)gBspAr12xxObj.devIdxMap);
    }
    if (retVal == BSP_SOK)
    {
        /* Wait for the device to complete its initializaton */
        while ((gBspAr12xxObj.radarInitCompleteFlag !=
            (gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade - 1))
            && (timeout != 0U))
        {
            /* Sleep for 1 ms */
            BspOsal_sleep(1U);
            timeout--;
        }
    }
    if (gBspAr12xxObj.radarInitCompleteFlag !=
        (gBspAr12xxObj.initPrmsCopy.numRadarDevicesInCascade - 1))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  " AR12XX: Radar Slave Device Power On failed!!\r\n");
        retVal = BSP_EFAIL;
    }
    return retVal;
}

UInt32 Bsp_ar12xxCountBits(UInt32 number)
{
    UInt32 count = 0U;
    while (number != 0U)
    {
        number = number & (number -1U);
        count++;
    }
    return count;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void Bsp_ar12xxAsyncEvtHandlerCb(UInt8 devIdx, UInt16 sbId, UInt16 sbLen,
                                        UInt8 * payload)
{
    UInt32 callAppCallBack = 0U;
    /* Read the sub block ID and appropriately take action. For all
     * monitorring events the action is application specific. Hence passing on
     * the payload and sub block ID to the application callback.
     */
    switch (sbId)
    {
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_SYS_RF_POWERUP_SB):
            gBspAr12xxObj.radarDevStartCompleteFlag += 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_INITCALIBSTATUS_SB):
            gBspAr12xxObj.radarRfInitComplete += 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_FRAME_TRIGGER_RDY_SB):
            gBspAr12xxObj.mmwl_bSensorStarted += 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_FRAME_END_SB):
            gBspAr12xxObj.mmwl_bSensorStarted += 1U;
            break;
        /* Async event from the MSS */
        case RL_GET_UNIQUE_SBID(RL_DEV_ASYNC_EVENT_MSG, RL_DEV_AE_MSSPOWERUPDONE_SB):
            gBspAr12xxObj.radarInitCompleteFlag += 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_DEV_ASYNC_EVENT_MSG, RL_DEV_AE_RFPOWERUPDONE_SB):
            gBspAr12xxObj.radarDevStartCompleteFlag += 1U;
            break;
		case RL_GET_UNIQUE_SBID(RL_DEV_ASYNC_EVENT_MSG, RL_DEV_AE_MSS_BOOTERRSTATUS_SB):
			gBspAr12xxObj.radarInitCompleteFlag += 1U;
			break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_RUN_TIME_CALIB_REPORT_SB):
            gBspAr12xxObj.mmwl_runTimeCalibDone += 1U;
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_CPUFAULT_SB):
            GT_0trace(BspAppTrace, GT_ERR,
                " AR12XX: FAULT: BSS CPU fault!!\r\n");
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_ESMFAULT_SB):
            GT_0trace(BspAppTrace, GT_ERR, " AR12XX: FAULT: ESM fault!!\r\n");
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TEMPERATURE_REPORT_SB):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_RX_GAIN_PHASE_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_RX_NOISE_FIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_RX_IF_STAGE_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX0_POWER_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX1_POWER_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX0_BALLBREAK_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TX1_BALLBREAK_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_REPORT_HEADER_SB):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_MSG, RL_RF_AE_MON_TIMING_FAIL_REPORT_SB):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_DEV_ASYNC_EVENT_MSG, RL_DEV_AE_MSS_ESMFAULT_SB):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX_GAIN_MISMATCH_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX0_BPM_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX1_BPM_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_SYNTHESIZER_FREQ_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_EXT_ANALOG_SIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX0_INT_ANA_SIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_TX1_INT_ANA_SIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_RX_INT_ANALOG_SIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_PMCLKLO_INT_ANA_SIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_GPADC_INT_ANA_SIG_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_PLL_CONTROL_VOLT_REPORT):
            callAppCallBack = 1U;
            break;
        case RL_GET_UNIQUE_SBID(RL_RF_ASYNC_EVENT_1_MSG, RL_RF_AE_MON_DCC_CLK_FREQ_REPORT):
            callAppCallBack = 1U;
            break;
        default:
            break;
    }
    if ((callAppCallBack == 1U) && (gBspAr12xxObj.monAppCallBack != NULL))
    {
        gBspAr12xxObj.monAppCallBack(sbId, payload);
    }
}
