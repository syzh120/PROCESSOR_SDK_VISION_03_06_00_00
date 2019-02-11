/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file IssIntf_simcop.c
 *
 *  \brief Simcop LDC And VTNF M2M application.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <Loopback_main.h>
#include <ti/drv/vps/include/vps_capture.h>
#include <ti/drv/vps/include/iss/vps_captureIss.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/devices/bsp_videoSensor.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ISS_CAPT_INST_ID        (VPS_CAPT_INST_ISS_CAL_A)

/**< CSI2 PHY Clock
 *      For a 15X15 Package TDA3MAx(15x15), TDA3LAx(15x15), TDA3LRx(15x15). */
#define ISS_INTG_APP_CAL_PHY_CLK_MHz        (400U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief
 */
typedef struct
{
    Vps_CaptIssOpenParams_t   issOpenPrms;
    /**< ISS create time parameters */
    Fvid2_VideoIfMode         videoIfMode;
    /**< CSI2, LVDS, Parallel etc... */
    Fvid2_VideoIfWidth        videoIfWidth;
    /**< Number of lanes in case CSI2 and number of bits in case of parallel */
    UInt32                    numStream;
    /**< Number of channel in multi-ch case, must be 1 for single channel. */
    UInt32                    virtualChannel;
    /**< Virtual channel of CSI2, if mode is CSI2 */
    vpsissCalCsi2DataFormat   dataFormat;
    /**< Data format of CSI2 stream */
    UInt32                    instId;
    /**< ISS Instance ID. As defined in bspdrivers_\include\vps\vps_capture.h*/

    /* FVID2 Capture Driver parameters */
    Vps_CaptCreateParams      createPrms;
    /**< Create time parameters. */
    Vps_CaptCreateStatus      createStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Fvid2_Handle              drvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams            cbPrms;
    /**< Callback params. */

    vpsissCalCfg_t            cfg;
    /**< TODO currently done for 1 stream, update for mutiple streams */

    Semaphore_Handle         *semHandle;
    /**< Semaphore handle which is used to unblock integration task */

    Fvid2_FrameList           frmList;
    /**< Frame List used for queueing and dequeueing frames */

    /* Sensor Parameters */
    Fvid2_Handle              sensorHandle;
    /**< Handle to the Sensor driver */
    UInt32                    sensorDrvId;
    /**< Sensor FVID2 Id */
    Bsp_VidSensorCreateParams sensorCreatePrms;
} LpbkApp_captObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 LpbkApp_captCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved);
static Int32 LpbkApp_captCreateVidSensor(
    LpbkApp_testCfg *testCfg,
    LpbkApp_captObj *instObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

LpbkApp_captObj gLpbkAppCaptObj;

/* ========================================================================== */
/*                          Functional Simulator                              */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  IntgApp_createM2mSimcopDrv
 *  Application test task.
 */
void LpbkApp_captCreate(
    LpbkApp_testCfg  *testCfg,
    Semaphore_Handle *semHandle)
{
    UInt32 streamId = 0U;
    Vps_CaptCreateParams  *createPrms  = NULL;
    vpsissCalCmplxIoCfg_t *pCmplxIoCfg = NULL;
    LpbkApp_captObj       *appObj      = &gLpbkAppCaptObj;

    appObj->instId    = ISS_CAPT_INST_ID;
    appObj->drvHandle = NULL;

    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn   = &LpbkApp_captCallback;
    appObj->cbPrms.appData = appObj;

    appObj->numStream = 1U;
    appObj->semHandle = semHandle;

    createPrms = &appObj->createPrms;
    VpsCaptCreateParams_init(&appObj->createPrms);
    createPrms->videoIfMode     = testCfg->intfType;
    createPrms->videoIfWidth    = testCfg->csi2NumLanes;
    createPrms->bufCaptMode     = VPS_CAPT_BCM_LAST_FRM_REPEAT;
    createPrms->numCh           = 1U;
    createPrms->numStream       = appObj->numStream;
    createPrms->pAdditionalArgs = &appObj->issOpenPrms;

    appObj->issOpenPrms.csi2PhyClock[0U] = ISS_INTG_APP_CAL_PHY_CLK_MHz;
    if (FVID2_VIFM_SCH_CPI == createPrms->videoIfMode)
    {
        appObj->issOpenPrms.subModules[0U] =
            (VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
             VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID |
             VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID);
    }
    else
    {
        appObj->issOpenPrms.subModules[0U] =
            (VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 |
             VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
             VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
             VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
    }

    for (streamId = 0U; streamId < VPS_ISS_CAL_MAX_CMPLXIO_INST; streamId++)
    {
        appObj->issOpenPrms.isCmplxIoCfgValid[streamId] = FALSE;
    }
    appObj->issOpenPrms.isCmplxIoCfgValid[0] = TRUE;

    pCmplxIoCfg                = &appObj->issOpenPrms.cmplxIoCfg[0U];
    pCmplxIoCfg->enable        = TRUE;
    pCmplxIoCfg->clockLane.pol = FALSE;
    pCmplxIoCfg->clockLane.pol      = FALSE;
    pCmplxIoCfg->clockLane.position = 2U;
    pCmplxIoCfg->data1Lane.pol      = FALSE;
    pCmplxIoCfg->data1Lane.position = 1U;
    pCmplxIoCfg->data2Lane.pol      = FALSE;
    pCmplxIoCfg->data2Lane.position = 3U;
    pCmplxIoCfg->data3Lane.pol      = FALSE;
    pCmplxIoCfg->data3Lane.position = 4U;
    pCmplxIoCfg->data4Lane.pol      = FALSE;
    pCmplxIoCfg->data4Lane.position = 5U;

    if (FVID2_VIFW_3LANES == testCfg->csi2NumLanes)
    {
        pCmplxIoCfg->data4Lane.position = 0;
    }
    if (FVID2_VIFW_2LANES == testCfg->csi2NumLanes)
    {
        pCmplxIoCfg->data3Lane.position = 0;
        pCmplxIoCfg->data4Lane.position = 0;
    }
    if (FVID2_VIFW_1LANES == testCfg->csi2NumLanes)
    {
        pCmplxIoCfg->data2Lane.position = 0;
        pCmplxIoCfg->data3Lane.position = 0;
        pCmplxIoCfg->data4Lane.position = 0;
    }
    for (streamId = 0U; streamId < appObj->numStream; streamId++)
    {
        createPrms->chNumMap[streamId][0] =
            Vps_captMakeChNum(appObj->instId, streamId, 0);
    }

    Int32 status = FVID2_SOK;

    appObj->drvHandle = Fvid2_create(
        FVID2_VPS_CAPT_VID_DRV,
        appObj->instId,
        &appObj->createPrms,
        &appObj->createStatus,
        &appObj->cbPrms);
    if ((NULL == appObj->drvHandle) ||
        (appObj->createStatus.retVal != FVID2_SOK))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Create Failed!!!\r\n");

        GT_assert(BspAppTrace, FALSE);
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": ISS Capture created\r\n");

    appObj->cfg.numStream   = 1;
    appObj->cfg.streamId[0] = 0U;

    appObj->cfg.inFmt[0].width  = testCfg->inWidth;
    appObj->cfg.inFmt[0].height = testCfg->inHeight;

    appObj->cfg.inFmt[0].pitch[0]    = testCfg->inPitch;
    appObj->cfg.inFmt[0].bpp         = testCfg->inBpp;
    appObj->cfg.inFmt[0].dataFormat  = 0x0U;
    appObj->cfg.csi2DataFormat[0]    = testCfg->csi2DataFormat;
    appObj->cfg.csi2VirtualChanNo[0] = testCfg->csi2VertChNum;

    appObj->cfg.streamType[0] = VPS_ISS_CAL_TAG_PIX_DATA;

    appObj->cfg.isPixProcCfgValid[0] = FALSE;
    appObj->cfg.isBysOutCfgValid[0]  = FALSE;
    appObj->cfg.bysInEnable[0]       = FALSE;
    appObj->cfg.isVportCfgValid[0]   = FALSE;

    appObj->cfg.writeToMem[0] = TRUE;

    if (FVID2_VIFM_SCH_CPI == appObj->createPrms.videoIfMode)
    {
        appObj->cfg.bysInEnable[0] = TRUE;
    }
    else
    {
        appObj->cfg.bysInEnable[0] = FALSE;
    }
    /* Some how, simulator requiers an 16 bit writes */
    if (((VPS_ISS_CAL_CSI2_RAW12 == appObj->cfg.csi2DataFormat[0]) ||
         (VPS_ISS_CAL_CSI2_RAW14 == appObj->cfg.csi2DataFormat[0])) ||
        (VPS_ISS_CAL_CSI2_RAW10 == appObj->cfg.csi2DataFormat[0]))
    {
        appObj->cfg.pixProcCfg[0].extract = VPS_ISS_CAL_PIX_EXRCT_B14_MIPI;
        if (VPS_ISS_CAL_CSI2_RAW12 == appObj->cfg.csi2DataFormat[0])
        {
            appObj->cfg.pixProcCfg[0].extract = VPS_ISS_CAL_PIX_EXRCT_B12_MIPI;
        }
        if (VPS_ISS_CAL_CSI2_RAW10 == appObj->cfg.csi2DataFormat[0])
        {
            appObj->cfg.pixProcCfg[0].extract = VPS_ISS_CAL_PIX_EXRCT_B10_MIPI;
        }
        appObj->cfg.isPixProcCfgValid[0]   = TRUE;
        appObj->cfg.pixProcCfg[0].decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
        appObj->cfg.pixProcCfg[0].enableDpcmInitContext = FALSE;
        appObj->cfg.pixProcCfg[0].encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
        appObj->cfg.pixProcCfg[0].pack     = VPS_ISS_CAL_PIX_PACK_B16;
        /* Write in 16 bit container */
        appObj->cfg.inFmt[0].pitch[0] = appObj->cfg.inFmt[0].width * 2;
    }

    status = Fvid2_control(appObj->drvHandle, IOCTL_VPS_CAPT_SET_ISS_PARAMS,
                           &appObj->cfg, NULL);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Set ISS Params Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }

    LpbkApp_captCreateVidSensor(testCfg, appObj);

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": ISS Capture Configured\r\n");
}

void LpbkApp_captPutFrames(
    UInt32       streamId,
    UInt32       numFrames,
    Fvid2_Frame *frames[])
{
    Int32            status = FVID2_SOK;
    UInt32           frmCnt;
    LpbkApp_captObj *appObj = &gLpbkAppCaptObj;

    Fvid2FrameList_init(&appObj->frmList);

    for (frmCnt = 0U; frmCnt < numFrames; frmCnt++)
    {
        appObj->frmList.frames[frmCnt] = frames[frmCnt];

        frames[frmCnt]->chNum = Vps_captMakeChNum(appObj->instId, streamId, 0U);
    }
    appObj->frmList.numFrames = numFrames;

    status = Fvid2_queue(appObj->drvHandle, &appObj->frmList, streamId);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Queue Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }
}

void LpbkApp_captGetFrames(
    UInt32       streamId,
    UInt32      *numFrames,
    Fvid2_Frame *frames[])
{
    Int32            status = FVID2_SOK;
    UInt32           frmCnt;
    LpbkApp_captObj *appObj = &gLpbkAppCaptObj;

    Fvid2FrameList_init(&appObj->frmList);

    status = Fvid2_dequeue(
        appObj->drvHandle,
        &appObj->frmList,
        streamId,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == status)
    {
        for (frmCnt = 0U; frmCnt < appObj->frmList.numFrames; frmCnt++)
        {
            frames[frmCnt] = appObj->frmList.frames[frmCnt];
        }
        *numFrames = appObj->frmList.numFrames;
    }
    else
    {
        GT_assert(BspAppTrace, FALSE);
    }
}

void LpbkApp_captStart(void)
{
    Int32 status = FVID2_SOK;
    LpbkApp_captObj *appObj = &gLpbkAppCaptObj;

    status = Fvid2_start(appObj->drvHandle, NULL);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Start Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }
}

void LpbkApp_captStop(void)
{
    Int32 status = FVID2_SOK;
    LpbkApp_captObj *appObj = &gLpbkAppCaptObj;

    status = Fvid2_stop(appObj->drvHandle, NULL);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture stop Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }
}

void LpbkApp_captClose(void)
{
    Int32            status = FVID2_SOK;
    UInt32           strmCnt;
    LpbkApp_captObj *appObj = &gLpbkAppCaptObj;

    for (strmCnt = 0U; strmCnt < appObj->cfg.numStream; strmCnt++)
    {
        /* Dequeue all the request from the driver */
        while (1U)
        {
            status = Fvid2_dequeue(
                appObj->drvHandle,
                &appObj->frmList,
                strmCnt,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != status)
            {
                break;
            }
        }
    }

    if (NULL != appObj->drvHandle)
    {
        status = Fvid2_delete(appObj->drvHandle, NULL);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Sensor Delete Failed!!!\r\n");
        }
        else
        {
            appObj->drvHandle = NULL;
        }
    }
    if (NULL != appObj->sensorHandle)
    {
        status = Fvid2_delete(appObj->sensorHandle, NULL);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Sensor Delete Failed!!!\r\n");
        }
        else
        {
            appObj->sensorHandle = NULL;
        }
    }
}

/**
 *  LpbkApp_captCallback
 *  \brief Driver callback function.
 */
static Int32 LpbkApp_captCallback(
    Fvid2_Handle handle,
    Ptr          appData,
    Ptr          reserved)
{
    LpbkApp_captObj *appObj = (LpbkApp_captObj *) appData;

    GT_assert(BspAppTrace, appData != NULL);

    Semaphore_post(*appObj->semHandle);

    return FVID2_SOK;
}

/**
 *  \brief Create and configure video sensor.
 */
static Int32 LpbkApp_captCreateVidSensor(
    LpbkApp_testCfg *testCfg,
    LpbkApp_captObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr;
    Bsp_VidSensorChipIdParams sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus sensorChipIdStatus;
    Bsp_VidSensorCreateStatus sensorCreateStatus;
    Bsp_VidSensorConfigParams configParams;

    sensorInstId = Bsp_boardGetVideoDeviceInstId(
        testCfg->sensorId,
        FVID2_VPS_CAPT_VID_DRV,
        ISS_CAPT_INST_ID);
    sensorI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        testCfg->sensorId,
        FVID2_VPS_CAPT_VID_DRV,
        ISS_CAPT_INST_ID);
    sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        testCfg->sensorId,
        FVID2_VPS_CAPT_VID_DRV,
        ISS_CAPT_INST_ID);

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Sensor Inst ID-%d-Sensor I2C Inst ID %d,sensorI2cAddr: 0x%x\r\n",
              sensorInstId,
              sensorI2cInstId, sensorI2cAddr);

    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        Bsp_boardSetPinMux(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ISS_CAL_A_CPI,
            BSP_BOARD_MODE_VIDEO_16BIT);
    }

    /* Power on video sensor at board level mux */
    retVal = Bsp_boardPowerOnDevice(testCfg->sensorId, sensorInstId,
                                    TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device power-on failed\r\n");
    }

    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        if (FVID2_SOK == retVal)
        {
            /* select video sensor at board level mux */
            retVal = Bsp_boardSelectDevice(testCfg->sensorId,
                                           sensorInstId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Select specific mode */
            retVal = Bsp_boardSelectMode(
                testCfg->sensorId,
                sensorInstId,
                BSP_BOARD_MODE_DEFAULT);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        instObj->sensorCreatePrms.deviceI2cInstId    = sensorI2cInstId;
        instObj->sensorCreatePrms.numDevicesAtPort   = 1U;
        instObj->sensorCreatePrms.deviceI2cAddr[0]   = sensorI2cAddr;
        instObj->sensorCreatePrms.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
        instObj->sensorCreatePrms.sensorCfg          = NULL;
        instObj->sensorCreatePrms.numSensorCfg       = 0U;
        instObj->sensorHandle = Fvid2_create(
            testCfg->sensorId,
            sensorInstId,
            &instObj->sensorCreatePrms,
            &sensorCreateStatus,
            NULL);
        GT_assert(BspAppTrace, instObj->sensorHandle != NULL);

        sensorChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->sensorHandle,
            IOCTL_BSP_VID_SENSOR_GET_CHIP_ID,
            &sensorChipIdPrms,
            &sensorChipIdStatus);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        GT_6trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": ISS DrvInstId %d: VID SENSOR %04x (0x%02x): %04x:%04x:%04x\r\n",
            ISS_CAPT_INST_ID,
            testCfg->sensorId,
            instObj->sensorCreatePrms.deviceI2cAddr[0],
            sensorChipIdStatus.chipId,
            sensorChipIdStatus.chipRevision,
            sensorChipIdStatus.firmwareVersion);

        /* Right now this IOCTL Do not act on the config specified below.
         *  Always configures to stream 720P @ 30 fps. */
        configParams.videoIfWidth = testCfg->csi2NumLanes;
        configParams.dataformat   = testCfg->csi2DataFormat;
        configParams.standard     = FVID2_STD_WXGA_30;
        configParams.fps          = FVID2_FPS_30;
        configParams.bpp          = testCfg->inBpp;
        retVal =
            Fvid2_control(instObj->sensorHandle,
                          IOCTL_BSP_VID_SENSOR_SET_CONFIG,
                          &configParams,
                          NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        /* start sensor, right now only OV sensor driver is implemented */
        retVal = Fvid2_control(instObj->sensorHandle, FVID2_START, NULL, NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));
    }

    /* If interface is CSI2, print the number of lanes configured in sensor */
    if ((FVID2_SOK == retVal) &&
        (FVID2_VIFM_SCH_CSI2 == instObj->createPrms.videoIfMode))
    {
        Bsp_VidSensorRegRdWrParams rdParams;
        /* MIPI_CTRL04 */
        UInt16 regAddr = 0x3444;
        UInt8 regValue = 0x0;

        rdParams.deviceNum = 0U;
        rdParams.numRegs   = 1U;
        rdParams.regAddr   = &regAddr;
        rdParams.regValue8 = &regValue;

        retVal = Fvid2_control(instObj->sensorHandle,
                               IOCTL_BSP_VID_SENSOR_REG_READ,
                               &rdParams,
                               NULL);
        if (FVID2_SOK == retVal)
        {
            GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                      ": CSI2 streaming on %d lanes !!!\r\n", regValue >> 4U);
        }
    }
    if ((FVID2_SOK == retVal) &&
        (FVID2_VID_SENSOR_APT_AR0140_DRV == testCfg->sensorId))
    {
        Bsp_VidSensorGainParams gain;
        Bsp_VidSensorExposureParams exp;

        gain.analogGain = 10000;
        retVal = Fvid2_control(instObj->sensorHandle,
                              IOCTL_BSP_VID_SENSOR_SET_GAIN_PARAMS,
                              &gain, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                      ": Cannot set Analog gain !!!\n");
        }

        exp.exposureTime = 10000;
        retVal = Fvid2_control(instObj->sensorHandle,
                              IOCTL_BSP_VID_SENSOR_SET_EXP_PARAMS,
                              &exp, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                      ": Cannot set exposure gain !!!\n");
        }
    }

    return (retVal);
}

