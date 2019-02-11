/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file Loopback_test.c
 *
 *  \brief Capture->Display loopback sample application test file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <Loopback_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void LpbkApp_captCreate(LpbkApp_Obj *appObj);
static void LpbkApp_captDelete(LpbkApp_Obj *appObj);

static Int32 LpbkApp_captAllocQueueFrm(const LpbkApp_Obj *appObj,
                                       LpbkApp_InstObj   *instObj,
                                       UInt32             fieldMerged);
static Int32 LpbkApp_captFreeFrm(LpbkApp_Obj     *appObj,
                                 LpbkApp_InstObj *instObj,
                                 UInt32           fieldMerged);

static Int32 LpbkApp_dispBoardSetup(LpbkApp_Obj *appObj);
static Int32 LpbkApp_startEncoder(LpbkApp_Obj *appObj);
static void LpbkApp_dispCreate(LpbkApp_Obj *appObj);
static void LpbkApp_dispDelete(LpbkApp_Obj *appObj);
static Int32 LpbkApp_dispConfigDctrl(LpbkApp_Obj *appObj);
static Int32 LpbkApp_configDctrlPipe(LpbkApp_Obj *appObj);

static Int32 LpbkApp_dispAllocQueueFrm(const LpbkApp_Obj *appObj,
                                       LpbkApp_InstObj   *instObj);
static Int32 LpbkApp_dispFreeFrm(LpbkApp_Obj     *appObj,
                                 LpbkApp_InstObj *instObj);

static void LpbkApp_configureLCD(LpbkApp_Obj *appObj);
static void LpbkApp_turnoffLCD(LpbkApp_Obj *appObj);
static Int32 LpbkApp_configureOffChipHdmi(LpbkApp_Obj *appObj, UInt32 encInst);
static Int32 LpbkApp_deConfigureOffChipHdmi(LpbkApp_Obj *appObj,
                                            UInt32       encInst);

static Int32 LpbkApp_createVidDec(LpbkApp_Obj     *appObj,
                                  LpbkApp_InstObj *instObj);
static Int32 LpbkApp_createVidSensor(const LpbkApp_Obj *appObj,
                                     LpbkApp_InstObj   *instObj);
static Int32 LpbkApp_detectVideo(LpbkApp_Obj     *appObj,
                                 LpbkApp_InstObj *instObj);
static Int32 LpbkApp_selectSimVideoSource(const LpbkApp_Obj *appObj,
                                          LpbkApp_InstObj   *instObj);

static void LpbkApp_initParams(LpbkApp_Obj *appObj);
static void LpbkApp_printStatistics(LpbkApp_Obj *appObj,
                                    UInt32       execTimeInMsecs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define MAX_CONTI_OF_INTERRUPTS     (2U)

/* Smaphore to sync between the reset and the callback function */
BspOsal_SemHandle overflowSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  LpbkApp_runTest
 *  Lpbkure test function.
 */
void LpbkApp_runTest(LpbkApp_Obj *appObj, const LpbkApp_TestParams *testPrms)
{
    Int32            retVal = FVID2_SOK;
    UInt32           instCnt;
    UInt32           runTime, curTime, prevTime;
    UInt32           loopCount, prevFldCount, curFldCount, fldCount;
    #if defined (SOC_TDA2EX)
    UInt32           encInst;
    #endif
    LpbkApp_InstObj *instObj = NULL;

    loopCount = 0;
    curTime   = prevTime = curFldCount = prevFldCount = 0;
    BspUtils_memcpy(&appObj->testPrms, testPrms, sizeof (appObj->testPrms));

    #if defined (SOC_TDA2EX)
    if (Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_17x17)
    {
        for (encInst = 0; encInst < appObj->testPrms.numDispHandles; encInst++)
        {
            /* On J6 Entry Evm LCD is connected on DPI3.
             * So update the venc to LCD3.
             */
            if (appObj->testPrms.vencId[encInst] == VPS_DCTRL_DSS_VENC_LCD1)
            {
                appObj->testPrms.vencId[encInst] = VPS_DCTRL_DSS_VENC_LCD3;
            }

            /* On J6 Entry Evm for the multideserializer options display is
             * configured to on chip HDMI as DPI3 and MULDESCAM 2 pins are muxed
             */
            if (appObj->testPrms.decDrvId[0] ==
                FVID2_VID_SENSOR_MULDES_OV1063X_DRV)
            {
                appObj->testPrms.vencId[encInst] =
                    VPS_DCTRL_DSS_VENC_HDMI;
                appObj->testPrms.encDrvId[encInst]     = 0U;
                appObj->testPrms.dispStandard[encInst] = FVID2_STD_1080P_60;
                appObj->testPrms.tarWidth      = 1920;
                appObj->testPrms.tarHeight     = 1080;
                appObj->testPrms.dispBoardMode = BSP_BOARD_MODE_DEFAULT;
            }
        }
    }
    #endif

    /* Print test case information */
    GT_5trace(BspAppTrace, GT_INFO,
              APP_NAME ": CAPT HANDLES %d: DISP HANDLES %d: MODE %04x : "
              "RUN COUNT %d: OUTPUT:%d !!\r\n",
              appObj->testPrms.numCaptHandles,
              appObj->testPrms.numDispHandles,
              appObj->testPrms.captVideoIfMode,
              appObj->testPrms.runCount,
              appObj->testPrms.captOutDataFmt);

    /* Create driver */
    LpbkApp_initParams(appObj);
    LpbkApp_captCreate(appObj);
    LpbkApp_dispCreate(appObj);

    /* Start decoder*/
    for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        if (NULL != instObj->decHandle)
        {
            Fvid2_start(instObj->decHandle, NULL);
        }
    }

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Starting loopback ... !!!\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Loopback in progress ... DO NOT HALT !!!\r\n");

    appObj->startTime = BspOsal_getCurTimeInMsec();

    /* Start the load calculation */
    BspUtils_prfLoadCalcStart();

    /* Start display driver */
    for (instCnt = 0U; instCnt < appObj->testPrms.numDispHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        retVal = Fvid2_start(instObj->dispDrvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Start Failed!!!\r\n");
            break;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Start capture driver */
        for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];

            retVal = Fvid2_start(instObj->captDrvHandle, NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Start Failed!!!\r\n");
                break;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Capture frames, check status */
        while (loopCount < appObj->testPrms.runCount)
        {
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                /* check status every sec */
                BspOsal_sleep(1000);
            }
            else
            {
                BspOsal_sleep(1);
            }

            /* Change current capture instance every few sec */
            if ((loopCount != 0) &&
                ((loopCount % LPBK_APP_CH_SWITCH_RATE) == 0))
            {
                if (appObj->curCaptInstance <
                    (appObj->testPrms.numCaptHandles - 1))
                {
                    appObj->curCaptInstance++;
                }
                else
                {
                    appObj->curCaptInstance = 0U;
                }
            }

            /* Get CPU load */
            appObj->totalCpuLoad += Load_getCPULoad();
            appObj->cpuLoadCount++;

            /* Do runtime print every 5 sec */
            if ((loopCount != 0) && ((loopCount % 5) == 0))
            {
                curTime     = BspOsal_getCurTimeInMsec() - appObj->startTime;
                curFldCount = appObj->totalCaptFldCount;

                runTime  = curTime - prevTime;
                fldCount = curFldCount - prevFldCount;

                prevTime     = curTime;
                prevFldCount = curFldCount;

                Bsp_rprintf(APP_NAME ": %5d.%3ds: Fields = %5d (%3d fps)\r\n",
                            (curTime / 1000), (curTime % 1000),
                            fldCount, ((fldCount * 1000) / runTime));
            }

            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                loopCount++;
            }
            else
            {
                if (loopCount != appObj->callBackCount)
                {
                    GT_1trace(BspAppTrace, GT_INFO,
                              APP_NAME ": Captured %d frames!!\r\n",
                              appObj->callBackCount);
                }
                loopCount = appObj->callBackCount;
            }
        }

        /* Stop capture driver */
        for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            retVal  = Fvid2_stop(instObj->captDrvHandle, NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Stop Failed!!!\r\n");
                break;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Stop display driver */
        for (instCnt = 0U; instCnt < appObj->testPrms.numDispHandles; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            retVal  = Fvid2_stop(instObj->dispDrvHandle, NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Display Stop Failed!!!\r\n");
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Stop the load calculation */
        BspUtils_prfLoadCalcStop();
        runTime = (BspOsal_getCurTimeInMsec() - appObj->startTime);

        /* Stop decoder */
        for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            if (instObj->decHandle)
            {
                Fvid2_stop(instObj->decHandle, NULL);
            }
        }

        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Stopping loopback ... DONE !!!\r\n");

        LpbkApp_printStatistics(appObj, runTime);

        /* Delete driver */
        LpbkApp_dispDelete(appObj);
        LpbkApp_captDelete(appObj);

        /* Print the load */
        BspUtils_prfLoadPrintAll(TRUE);
        /* Reset the load */
        BspUtils_prfLoadCalcReset();
    }

    return;
}

/*
 *  Callback function, recieved when overflow occues in VIP
 */
Int32 LpbkApp_overflowCbFxn(LpbkApp_InstObj *instObj)
{
    Int32 retVal = FVID2_SOK;
    /* Most of the time VIP recovers automatically. This is to give
     * some time to VIP to recover automatically
     */
    GT_assert(BspAppTrace, (instObj != NULL));

    instObj->overflowCount++;
    if (instObj->overflowCount > MAX_CONTI_OF_INTERRUPTS)
    {
        retVal = Fvid2_control(
            instObj->captDrvHandle,
            IOCTL_VPS_CAPT_RESET_VIP_PORT,
            NULL,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": VIP Reset Failed!!!\r\n");
        }
    }

    BspOsal_semPost(overflowSem);

    return retVal;
}

static void LpbkApp_captCreate(LpbkApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    UInt32 streamId, chId;
    LpbkApp_InstObj       *instObj;
    Vps_VpdmaMaxSizeParams vipMaxSizePrms;
    Vps_CaptFrameSkip      frmSkipPrms;

    for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->captDrvHandle = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            instObj->captInstId,
            &instObj->captCreatePrms,
            &instObj->captCreateStatus,
            &instObj->captCbPrms);
        if ((NULL == instObj->captDrvHandle) ||
            (instObj->captCreateStatus.retVal != FVID2_SOK))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Create Failed!!!\r\n");
            retVal = instObj->captCreateStatus.retVal;
        }
        if (FVID2_SOK == retVal)
        {
            retVal = Fvid2_control(
                instObj->captDrvHandle,
                IOCTL_VPS_CAPT_SET_VIP_PARAMS,
                &instObj->vipPrms,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": VIP Set Params IOCTL Failed!!!\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Set frame skip for each channel */
            VpsCaptFrameSkip_init(&frmSkipPrms);
            for (streamId = 0U; streamId < instObj->captCreatePrms.numStream;
                 streamId++)
            {
                for (chId = 0U; chId < instObj->captCreatePrms.numCh; chId++)
                {
                    /* This IOCTL is supported only for frame drop mode */
                    if (instObj->captCreatePrms.bufCaptMode ==
                        VPS_CAPT_BCM_FRM_DROP)
                    {
                        frmSkipPrms.chNum =
                            Vps_captMakeChNum(instObj->captInstId, streamId,
                                              chId);
                        frmSkipPrms.frmSkipMask = LPBK_APP_FRAME_SKIP_PATTERN;
                        retVal = Fvid2_control(
                            instObj->captDrvHandle,
                            IOCTL_VPS_CAPT_SET_FRAME_SKIP,
                            &frmSkipPrms,
                            NULL);
                        if (retVal != FVID2_SOK)
                        {
                            GT_0trace(
                                BspAppTrace, GT_ERR,
                                APP_NAME
                                ": VIP Set frame skip IOCTL Failed!!\r\n");
                            break;
                        }
                    }
                }
            }
        }

        if (!Bsp_platformIsTI814xFamilyBuild() && (FVID2_SOK == retVal))
        {
            VpsVpdmaMaxSizeParams_init(&vipMaxSizePrms);
            vipMaxSizePrms.instId =
                Vps_captGetVipId(appObj->testPrms.captInstId[instCnt]);
            vipMaxSizePrms.maxOutWidth[0U]  = instObj->maxOutWidth[0U];
            vipMaxSizePrms.maxOutHeight[0U] = instObj->maxOutHeight[0U];
            vipMaxSizePrms.maxOutWidth[1U]  = instObj->maxOutWidth[1U];
            vipMaxSizePrms.maxOutHeight[1U] = instObj->maxOutHeight[1U];
            vipMaxSizePrms.maxOutWidth[2U]  = instObj->maxOutWidth[2U];
            vipMaxSizePrms.maxOutHeight[2U] = instObj->maxOutHeight[2U];

            retVal = Fvid2_control(
                appObj->fvidHandleAll,
                IOCTL_VPS_CAPT_SET_VIP_MAX_SIZE,
                &vipMaxSizePrms,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(
                    BspAppTrace, GT_ERR,
                    APP_NAME
                    ": VIP Set Max Frame Size Params IOCTL Failed!!!\r\n");
            }
        }
        if (FVID2_SOK == retVal)
        {
            retVal = LpbkApp_captAllocQueueFrm(appObj, instObj, FALSE);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Alloc and Queue Failed!!!\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            instObj->decHandle = NULL;
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                if ((FVID2_VID_SENSOR_MT9V022_DRV == instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_MULDES_OV1063X_DRV ==
                     instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_GW4200_IMX290_DRV ==
                     instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_OV2659_DRV == instObj->decDrvId))
                {
                    LpbkApp_createVidSensor(appObj, instObj);
                }
                else if (0U != instObj->decDrvId)
                {
                    LpbkApp_createVidDec(appObj, instObj);
                }
                else
                {
                    GT_0trace(BspAppTrace, GT_INFO,
                              APP_NAME ": Skip decoder config!!\r\n");
                }
            }
            else if ((BSP_PLATFORM_ID_SIM == Bsp_platformGetId()) ||
                     (BSP_PLATFORM_ID_VIRTIO == Bsp_platformGetId()))
            {
                LpbkApp_selectSimVideoSource(appObj, instObj);
            }
        }

        if (FVID2_SOK == retVal)
        {
            retVal = Bsp_boardSetPinMux(FVID2_VPS_CAPT_VID_DRV,
                                        instObj->captInstId,
                                        appObj->testPrms.captBoardMode);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Pin Muxing Failed \r\n");
            }
        }

        if (retVal == FVID2_SOK)
        {
            Vps_CaptOverflowParams overflowParams;
            overflowParams.overflowCbFxn =
                (Vps_CaptVipOverflowFxn) & LpbkApp_overflowCbFxn;
            overflowParams.retParams = (void *) instObj;
            retVal = Fvid2_control(
                instObj->captDrvHandle,
                IOCTL_VPS_CAPT_REGISTER_OVF_INTR,
                &overflowParams,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": VIP Set Params IOCTL Failed!!!\r\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Capture create complete!!\r\n");
    }

    return;
}

static void LpbkApp_captDelete(LpbkApp_Obj *appObj)
{
    Int32            retVal = FVID2_SOK;
    UInt32           instCnt, streamId, boardId, sensorInstId;
    LpbkApp_InstObj *instObj;
    Fvid2_FrameList  frmList;

    for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        for (streamId = 0U;
             streamId < instObj->captCreatePrms.numStream;
             streamId++)
        {
            /* Dequeue all the request from the driver */
            while (1U)
            {
                retVal = Fvid2_dequeue(
                    instObj->captDrvHandle,
                    &frmList,
                    streamId,
                    FVID2_TIMEOUT_NONE);
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }

        /* Unregister from the overflow interrupt*/
        retVal = Fvid2_control(
            instObj->captDrvHandle,
            IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR,
            NULL,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(
                BspAppTrace, GT_ERR,
                APP_NAME
                ": Unregister From Overflow Interrupt Failed!!!\r\n");
        }

        retVal = Fvid2_delete(instObj->captDrvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Delete Failed!!!\r\n");
        }

        /* free frame memory */
        retVal = LpbkApp_captFreeFrm(appObj, instObj, FALSE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Free Frames Failed!!!\r\n");
        }

        if (NULL != instObj->decHandle)
        {
            retVal = Fvid2_delete(instObj->decHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Decoder Delete Failed!!!\r\n");
            }
            instObj->decHandle = NULL;
        }

        /* DeConfiguring a particular instance of SerDeSer */
        boardId = Bsp_boardGetId();

        if ((BSP_BOARD_MULTIDES == boardId) &&
            ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId) ||
             (FVID2_VID_SENSOR_GW4200_IMX290_DRV == instObj->decDrvId)))
        {
            sensorInstId = Bsp_boardGetVideoDeviceInstId(
                instObj->decDrvId,
                FVID2_VPS_CAPT_VID_DRV,
                instObj->captInstId);

            retVal = BspUtils_appDeConfSerDeSer(instObj->decDrvId,
                                                sensorInstId);
            if (retVal != FVID2_SOK)
            {
                GT_1trace(
                    BspAppTrace, GT_ERR,
                    APP_NAME
                    ": DeConfiguring MultiDes instance \
                      %d failed!!!\r\n",
                    sensorInstId);
            }
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Capture delete complete!!\r\n");

    return;
}

static Int32 LpbkApp_dispBoardSetup(LpbkApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 encInst;
    Bsp_LcdCtrlPanelInfo *lcdPanelInfo;

    /* Configure the Video Encoders/LCD controllers if required */
    appObj->lcdCtrlHandle = NULL;
    for (encInst = 0; encInst < appObj->testPrms.numDispHandles; encInst++)
    {
        if ((appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV) ||
            (appObj->testPrms.encDrvId[encInst] == FVID2_VID_ENC_SII9022A_DRV))
        {
            UInt32 instId = VPS_DSS_DISPC_OVLY_DPI1;
            if (appObj->testPrms.vencId[encInst] == VPS_DCTRL_DSS_VENC_LCD3)
            {
                instId = VPS_DSS_DISPC_OVLY_DPI3;
            }
            retVal = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                        instId,
                                        appObj->testPrms.dispBoardMode);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Pin Muxing Failed \r\n");
            }

            if (appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
            {
                /* Configure LCD only if platform is EVM */
                if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
                {
                    LpbkApp_configureLCD(appObj);
                }
                else
                {
                    /* Set some default modes so that test case runs in Zebu */
                    lcdPanelInfo = &appObj->lcdPanelInfo;
                    Fvid2ModeInfo_init(&lcdPanelInfo->modeInfo);
                    lcdPanelInfo->modeInfo.standard    = FVID2_STD_CUSTOM;
                    lcdPanelInfo->modeInfo.width       = 800U;
                    lcdPanelInfo->modeInfo.height      = 480U;
                    lcdPanelInfo->modeInfo.scanFormat  = FVID2_SF_PROGRESSIVE;
                    lcdPanelInfo->modeInfo.pixelClock  = 29232U;
                    lcdPanelInfo->modeInfo.fps         = 60U;
                    lcdPanelInfo->modeInfo.hBackPorch  = 40U;
                    lcdPanelInfo->modeInfo.hSyncLen    = 48U;
                    lcdPanelInfo->modeInfo.hFrontPorch = 40U;
                    lcdPanelInfo->modeInfo.vBackPorch  = 29U;
                    lcdPanelInfo->modeInfo.vSyncLen    = 3U;
                    lcdPanelInfo->modeInfo.vFrontPorch = 13U;

                    lcdPanelInfo->videoIfWidth    = FVID2_VIFW_24BIT;
                    lcdPanelInfo->videoDataFormat = FVID2_DF_RGB24_888;
                    lcdPanelInfo->videoIfMode     =
                        FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                    lcdPanelInfo->vsPolarity       = FVID2_POL_HIGH;
                    lcdPanelInfo->hsPolarity       = FVID2_POL_HIGH;
                    lcdPanelInfo->actVidPolarity   = FVID2_POL_HIGH;
                    lcdPanelInfo->fidPolarity      = FVID2_POL_HIGH;
                    lcdPanelInfo->pixelClkPolarity = FVID2_POL_HIGH;
                }
            }
            else if (appObj->testPrms.encDrvId[encInst] ==
                     FVID2_VID_ENC_SII9022A_DRV)
            {
                /* Configure Video Encoder only if platform is EVM */
                if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
                {
                    retVal = LpbkApp_configureOffChipHdmi(appObj, encInst);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(
                            BspAppTrace, GT_ERR,
                            APP_NAME
                            ": Configuring Off-Chip HDMI Failed!!!\r\n");
                    }
                }
            }
        }
    }

    return (retVal);
}

static Int32 LpbkApp_startEncoder(LpbkApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 encInst;

    for (encInst = 0; encInst < appObj->testPrms.numDispHandles; encInst++)
    {
        if (appObj->testPrms.encDrvId[encInst] ==
            FVID2_VID_ENC_SII9022A_DRV)
        {
            /* Configure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = Fvid2_start(appObj->hdmiHandle, NULL);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": Error: Off-chip HDMI start failed!!\r\n");
                }
            }
        }
    }

    return (retVal);
}

static void LpbkApp_dispCreate(LpbkApp_Obj *appObj)
{
    Int32            retVal = FVID2_SOK;
    UInt32           instCnt;
    LpbkApp_InstObj *instObj;

    LpbkApp_dispBoardSetup(appObj);
    LpbkApp_dispConfigDctrl(appObj);
    LpbkApp_startEncoder(appObj);

    for (instCnt = 0U; instCnt < appObj->testPrms.numDispHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->dispDrvHandle = Fvid2_create(
            FVID2_VPS_DISP_DRV,
            instObj->dispInstId,
            &instObj->dispCreatePrms,
            &instObj->dispCreateStatus,
            &instObj->dispCbPrms);
        if ((NULL == instObj->dispDrvHandle) ||
            (instObj->dispCreateStatus.retVal != FVID2_SOK))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Create Failed!!!\r\n");
            retVal = instObj->dispCreateStatus.retVal;
        }
        if (FVID2_SOK == retVal)
        {
            BspUtils_appPrintDispCreateStatus(&instObj->dispCreateStatus);

            /* Set the pitch same as that of capture */
            instObj->dispDssPrms.inFmt.pitch[0U] =
                instObj->captAllocFmt.pitch[0U];
            instObj->dispDssPrms.inFmt.pitch[1U] =
                instObj->captAllocFmt.pitch[1U];
            instObj->dispDssPrms.inFmt.pitch[2U] =
                instObj->captAllocFmt.pitch[2U];
            retVal = Fvid2_control(
                instObj->dispDrvHandle,
                IOCTL_VPS_DISP_SET_DSS_PARAMS,
                &instObj->dispDssPrms,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": DSS Set Params IOCTL Failed!!!\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            retVal = LpbkApp_dispAllocQueueFrm(appObj, instObj);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Display Alloc and Queue Failed!!!\r\n");
            }
        }
    }

    if (retVal != FVID2_SOK)
    {
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_CLEAR_CONFIG,
            &appObj->dctrlCfg,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL SetConfig IOCTL Failed!!!\r\n");
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Display create complete!!\r\n");

    return;
}

static void LpbkApp_dispDelete(LpbkApp_Obj *appObj)
{
    Int32            retVal;
    UInt32           instCnt, encInst, sdVencEnable;
    LpbkApp_InstObj *instObj;
    Fvid2_FrameList  frmList;
    Vps_DctrlConfig *dctrlCfg;

    dctrlCfg = &appObj->dctrlCfg;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        NULL);

    for (encInst = 0; encInst < appObj->testPrms.numDispHandles; encInst++)
    {
        if (appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
        {
            /* Configure LCD only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                LpbkApp_turnoffLCD(appObj);
            }
        }
        else if (appObj->testPrms.encDrvId[encInst] ==
                 FVID2_VID_ENC_SII9022A_DRV)
        {
            /* DeConfigure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = LpbkApp_deConfigureOffChipHdmi(appObj, encInst);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": Error: DeConfiguring off-chip HDMI failed!!\r\n");
                }
            }
        }
        else if (appObj->testPrms.isSdVenc == TRUE)
        {
            sdVencEnable = FALSE;
            /* SD-VENC Power off */
            retVal = Fvid2_control(
                appObj->dctrlHandle,
                IOCTL_VPS_DCTRL_ENABLE_SDVENC,
                &sdVencEnable,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Disabling SD-VENC IOCTL Failed!!!\r\n");
            }
        }
        else
        {
            /* Do nothing */
        }
    }

    for (instCnt = 0U; instCnt < appObj->testPrms.numDispHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Dequeue all the request from the driver */
        while (1U)
        {
            retVal = Fvid2_dequeue(
                instObj->dispDrvHandle,
                &frmList,
                0U,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }

        retVal = Fvid2_delete(instObj->dispDrvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Delete Failed!!!\r\n");
        }
        else
        {
            /* free frame memory */
            retVal = LpbkApp_dispFreeFrm(appObj, instObj);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Display Free Frames Failed!!!\r\n");
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Display delete complete!!\r\n");
    }

    return;
}

static Int32 LpbkApp_dispConfigDctrl(LpbkApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    Vps_DctrlConfig             *dctrlCfg;
    Vps_DssDispcOvlyPanelConfig *panelCfg;
    Fvid2_ModeInfo              *mInfo;
    Vps_DctrlVencDivisorInfo vencDivisors;
    Vps_DssDispcAdvLcdTdmConfig advTdmPrms;
    UInt32 pixelClk, instCnt, sdVencEnable;
    LpbkApp_InstObj             *instObj;
    Vps_DctrlOutputInfo          vencInfo;
    Vps_DctrlSDVencVideoStandard vidStd;

    dctrlCfg = &appObj->dctrlCfg;
    VpsDctrlConfig_init(dctrlCfg);
    dctrlCfg->useCase  = VPS_DCTRL_USERSETTINGS;
    dctrlCfg->numEdges = 2U;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
    {
        dctrlCfg->edgeInfo[0U].startNode       = VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[0U].endNode         = VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->edgeInfo[1U].startNode       = VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->edgeInfo[1U].endNode         = VPS_DCTRL_DSS_HDMI_OUTPUT;
        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_HDMI;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[0U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.dispStandard[0U];
    }
#endif

    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1)
    {
        dctrlCfg->edgeInfo[0U].startNode       = VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[0U].endNode         = VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->edgeInfo[1U].startNode       = VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->edgeInfo[1U].endNode         = VPS_DCTRL_DSS_DPI1_OUTPUT;
        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD1;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[0U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.dispStandard[0U];
    }
    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)
    {
        dctrlCfg->edgeInfo[0U].startNode       = VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[0U].endNode         = VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->edgeInfo[1U].startNode       = VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->edgeInfo[1U].endNode         = VPS_DCTRL_DSS_DPI3_OUTPUT;
        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD3;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[0U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.dispStandard[0U];
    }
    dctrlCfg->vencInfo.numVencs = 1U;
    mInfo = &dctrlCfg->vencInfo.modeInfo[0U].mInfo;
    if (FVID2_STD_CUSTOM == appObj->testPrms.dispStandard[0U])
    {
        /* Configure custom timings */
        if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
            (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
            (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
        {
        #if defined (SOC_TDA2PX)
            /* For TDA2Px DPI to HDMI converter is connected, so configure the
             * the standard timing of 1080P. */
            mInfo->standard = FVID2_STD_1080P_60;
            Fvid2_getModeInfo(mInfo);
            mInfo->scanFormat = FVID2_SF_PROGRESSIVE;
            /* Configure custom timings */
            BspUtils_memcpy(
                &appObj->lcdPanelInfo.modeInfo, mInfo, sizeof (Fvid2_ModeInfo));
            appObj->lcdPanelInfo.videoIfWidth    = FVID2_VIFW_24BIT;
            appObj->lcdPanelInfo.videoDataFormat = FVID2_DF_RGB24_888;
            appObj->lcdPanelInfo.videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;
            appObj->lcdPanelInfo.vsPolarity       = FVID2_POL_HIGH;
            appObj->lcdPanelInfo.hsPolarity       = FVID2_POL_HIGH;
            appObj->lcdPanelInfo.actVidPolarity   = FVID2_POL_HIGH;
            appObj->lcdPanelInfo.fidPolarity      = FVID2_POL_HIGH;
            appObj->lcdPanelInfo.pixelClkPolarity = FVID2_POL_HIGH;
        #else
            BspUtils_memcpy(
                mInfo, &appObj->lcdPanelInfo.modeInfo, sizeof (Fvid2_ModeInfo));
        #endif
        }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
        if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
        {
            /* Configure custom timings for 1080P */
            Fvid2ModeInfo_init(mInfo);
            mInfo->standard = FVID2_STD_CUSTOM;

            mInfo->width       = 1920;
            mInfo->height      = 1080;
            mInfo->scanFormat  = FVID2_SF_PROGRESSIVE;
            mInfo->pixelClock  = 74250;
            mInfo->fps         = 60U;
            mInfo->hBackPorch  = 88U;
            mInfo->hSyncLen    = 148U;
            mInfo->hFrontPorch = 44U;
            mInfo->vBackPorch  = 2U;
            mInfo->vSyncLen    = 15U;
            mInfo->vFrontPorch = 5U;
        }
#endif
    }
    else
    {
        /* We are extracting the Pixel Clock frequency which will be used to
         * configure the PLL */
        Fvid2_getModeInfo(mInfo);
    }

    dctrlCfg->vencInfo.tiedVencs = 0U;

    panelCfg         = &appObj->panelCfg;
    panelCfg->vencId = appObj->testPrms.vencId[0];
    panelCfg->alphaBlenderEnable = 0;
    panelCfg->backGroundColor    = 0x00;
    panelCfg->colorKeyEnable     = 1;
    /* Source transparency color key selected */
    panelCfg->colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    panelCfg->deltaLinesPerPanel = 0;
    panelCfg->transColorKey      = 0x00;

    vencDivisors.vencId     = appObj->testPrms.vencId[0];
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;

    /* Setting LCD and PCD values to 1 */
    if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
        if (appObj->testPrms.vencId[0] != VPS_DCTRL_DSS_VENC_HDMI)
        {
            /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
             * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed
             * to output 29.232 * 4 MHz and set PCD as 4. */
            if (29232U == appObj->lcdPanelInfo.modeInfo.pixelClock)
            {
                vencDivisors.divisorPCD = 4U;
            }

            retVal = Fvid2_control(
                appObj->dctrlHandle,
                IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS,
                &vencDivisors,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(
                    BspAppTrace,
                    GT_ERR,
                    APP_NAME
                    ": DCTRL Set Venc Divisors IOCTL Failed!!!\r\n");
            }
        }
#endif
    }

    vencInfo.actVidPolarity   = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.dvoFormat        = VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    vencInfo.hsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.vsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencInfo.dataFormat       = FVID2_DF_RGB24_888;
    vencInfo.videoIfWidth     = FVID2_VIFW_24BIT;

    if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
    {
        panelCfg->vencId = appObj->testPrms.vencId[0];
        vencInfo.vencId  = appObj->testPrms.vencId[0];

        /* Setting hync and vsync pol to be negative as LCD panel expects
         * it to be */
        if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
            (appObj->testPrms.encDrvId[0] == FVID2_LCD_CTRL_DRV))
        {
            /*
             * Due to HW bug, polarity cannot be set by
             * vencInfo.pixelClkPolarity So need to change the register
             * SMA_SW_1 which mirrors some fields of the control register.
             * Only to be called for LCD, not for HDMI.
             */
            if (FVID2_POL_LOW == appObj->lcdPanelInfo.pixelClkPolarity)
            {
                Bsp_platformSetLcdClkPolarity(
                    BSP_PLATFORM_VENC_LCD1, FVID2_POL_LOW);
            }

            vencInfo.hsPolarity   = appObj->lcdPanelInfo.hsPolarity;
            vencInfo.vsPolarity   = appObj->lcdPanelInfo.vsPolarity;
            vencInfo.dataFormat   = appObj->lcdPanelInfo.videoDataFormat;
            vencInfo.videoIfWidth = appObj->lcdPanelInfo.videoIfWidth;

            /* Set display width/height equal to that of LCD width/height */
            for (instCnt = 0U;
                 instCnt < appObj->testPrms.numDispHandles;
                 instCnt++)
            {
                instObj = &appObj->instObj[instCnt];
                if (LPBK_APP_USE_LCD_WIDTH == appObj->testPrms.tarWidth)
                {
                    instObj->dispDssPrms.tarWidth =
                        appObj->lcdPanelInfo.modeInfo.width;
                }
                if (LPBK_APP_USE_LCD_HEIGHT == appObj->testPrms.tarHeight)
                {
                    instObj->dispDssPrms.tarHeight =
                        appObj->lcdPanelInfo.modeInfo.height;
                }
            }
        }
    }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
    {
        panelCfg->vencId = VPS_DCTRL_DSS_VENC_HDMI;

        vencInfo.hsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencInfo.vsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencInfo.vencId     = VPS_DCTRL_DSS_VENC_HDMI;
    }
#endif

    /* This IOCTL should be called before SET_CONFIG */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_VENC_OUTPUT,
        &vencInfo,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Venc Output IOCTL Failed!!!\r\n");
    }

    if (appObj->testPrms.dispBoardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
    {
        VpsDssDispcAdvLcdTdmConfig_init(&advTdmPrms);
        advTdmPrms.tdmEnable = 1;
        advTdmPrms.vencId    = appObj->testPrms.vencId[0];

        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_TDM_PARAMS,
            &advTdmPrms,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Set ADV TDM Pramas Failed!!!\r\n");
        }
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_CONFIG,
        dctrlCfg,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_OVLY_PARAMS,
        panelCfg,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
    }

    retVal = LpbkApp_configDctrlPipe(appObj);

    if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
        ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
         (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
         (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)))
    {
        if (appObj->testPrms.isSdVenc == TRUE)
        {
            pixelClk = 54000U;
            retVal   = LpbkApp_configureVideoPllAndClkSrc(appObj, pixelClk);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
        else if (appObj->testPrms.encDrvId[0] == FVID2_LCD_CTRL_DRV)
        {
            /* Reconfigure video PLL clock to match LCD required clock */
            pixelClk = appObj->lcdPanelInfo.modeInfo.pixelClock *
                       vencDivisors.divisorPCD;
            retVal = LpbkApp_configureVideoPllAndClkSrc(appObj, pixelClk);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
        else if (appObj->testPrms.encDrvId[0] == FVID2_VID_ENC_SII9022A_DRV)
        {
            /* Reconfigure video PLL clock to match Sil9022a clock */
            if (appObj->testPrms.dispBoardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
            {
                pixelClk = mInfo->pixelClock * 3;
            }
            else
            {
                pixelClk = mInfo->pixelClock;
            }
            retVal = LpbkApp_configureVideoPllAndClkSrc(appObj, pixelClk);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
    }

    if (appObj->testPrms.isSdVenc == TRUE)
    {
        sdVencEnable = TRUE;
        /* SD-VENC Power on and Configure IOCTL's */
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_ENABLE_SDVENC,
            &sdVencEnable,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Enabling SD-VENC IOCTL Failed!!!\r\n");
        }

        VpsDctrlSDVencVideoStandard_init(&vidStd);
        vidStd.videoStandard = appObj->testPrms.dispStandard[0U];

        /* SD-VENC Configure the Mode IOCTL's */
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_SET_SDVENC_MODE,
            &vidStd,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Set SD-VENC Mode IOCTL Failed!!!\r\n");
        }
    }

    return (retVal);
}

static Int32 LpbkApp_configDctrlPipe(LpbkApp_Obj *appObj)
{
    Vps_DssDispcOvlyPipeConfig *ovlPipeCfg;
    UInt32           instCnt;
    LpbkApp_InstObj *instObj;
    Int32 retVal = FVID2_SOK;

    for (instCnt = 0U; instCnt < appObj->testPrms.numDispHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        ovlPipeCfg = &instObj->ovlPipeCfg;

        ovlPipeCfg->pipeLine    = instObj->dispInstId;
        ovlPipeCfg->globalAlpha = 0xFF;
        /* Z-order is in order GFX - 3, VID3 -2 ,VID2 - 1 and VID1 - 0 */
        /* There is no blending between background and Layer-0 (ZORDER=0),
         * it is either background or layer-0 pixel (if it is present in that
         * location).so ZORDER is other than 0 */
        ovlPipeCfg->zorder = 1;

        if (ovlPipeCfg->pipeLine == VPS_DSS_DISPC_PIPE_GFX1)
        {
            /* 50 % blending selected - 0xFF is opaque and 0x00 is
             * transparent */
            ovlPipeCfg->globalAlpha = 0x7F;
        }

        ovlPipeCfg->zorderEnable     = 1;
        ovlPipeCfg->preMultiplyAlpha = 0;

        retVal += Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS,
            ovlPipeCfg,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Set Config IOCTL Failed!!!\r\n");
            break;
        }
    }

    return (retVal);
}

/**
 *  LpbkApp_captCbFxn
 *  \brief Driver callback function.
 */
static Int32 LpbkApp_captCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32              retVal = FVID2_SOK;
    UInt32             streamId;
    LpbkApp_InstObj   *instObj = (LpbkApp_InstObj *) appData;
    LpbkApp_Obj       *appObj  = instObj->appObj;
    Fvid2_FrameList    frmList, newFrmList;
    LpbkApp_FrameInfo *frmInfo;

    for (streamId = 0U;
         streamId < instObj->captCreatePrms.numStream;
         streamId++)
    {
        retVal = Fvid2_dequeue(
            instObj->captDrvHandle,
            &frmList,
            streamId,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK == retVal)
        {
            if ((instObj->dispDrvHandle != NULL) &&
                (appObj->testPrms.numCaptHandles ==
                 appObj->testPrms.numDispHandles))
            {
                if (FVID2_SF_INTERLACED == appObj->testPrms.captScanFormat)
                {
                    GT_assert(BspAppTrace, (frmList.numFrames == 1U));

                    if (frmList.frames[0U] == &instObj->captDropFrame)
                    {
                        /* Ignore drop frame and set that it is with app */
                        instObj->isDropFrmWithDriver = FALSE;
                    }
                    else
                    {
                        /*
                         * Queue even field as frame only when we receive odd
                         * field
                         */
                        frmInfo =
                            (LpbkApp_FrameInfo *) frmList.frames[0U]->appData;
                        if ((frmInfo->bufFid != frmList.frames[0U]->fid) &&
                            (instObj->isDropFrmWithDriver == FALSE))
                        {
                            instObj->isDropFrmWithDriver = TRUE;

                            /* Fields are swapped - queue drop field */
                            Fvid2FrameList_init(&newFrmList);
                            newFrmList.frames[0U] = &instObj->captDropFrame;
                            newFrmList.numFrames++;

                            retVal =
                                Fvid2_queue(
                                    instObj->captDrvHandle,
                                    &newFrmList,
                                    0U);
                            if (FVID2_SOK != retVal)
                            {
                                GT_0trace(
                                    BspAppTrace, GT_ERR,
                                    APP_NAME
                                    ": Capture Queue Failed!!!\r\n");
                            }
                        }

                        if (frmInfo->bufFid == FVID2_FID_BOTTOM)
                        {
                            /* Swap odd field with even frame for display */
                            frmList.frames[0U] = frmInfo->bufPair;
                            retVal = Fvid2_queue(
                                instObj->dispDrvHandle,
                                &frmList,
                                streamId);
                            if (FVID2_SOK != retVal)
                            {
                                GT_0trace(
                                    BspAppTrace, GT_ERR,
                                    APP_NAME
                                    ": Display Queue Failed!!!\r\n");
                            }
                        }
                    }
                }
                else
                {
                    retVal = Fvid2_queue(
                        instObj->dispDrvHandle,
                        &frmList,
                        streamId);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": Display Queue Failed!!!\r\n");
                    }
                }
            }
            else
            {
                /* Multi-capture to single display scenario
                 * If the the current capture instance is matching, then
                 * queue to display(0) otherwise queue back to capture */
                if (&appObj->instObj[appObj->curCaptInstance] == instObj)
                {
                    GT_assert(BspAppTrace,
                              appObj->instObj[0U].dispDrvHandle != NULL);
                    retVal = Fvid2_queue(
                        appObj->instObj[0U].dispDrvHandle,
                        &frmList,
                        streamId);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": Display Queue Failed!!!\r\n");
                    }
                }
                else
                {
                    /* Queue back to same capture instance */
                    retVal = Fvid2_queue(
                        instObj->captDrvHandle,
                        &frmList,
                        streamId);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": Capture Queue Failed!!!\r\n");
                    }
                }
            }
        }
    }

    instObj->appObj->callBackCount++;

    return (retVal);
}

/**
 *  LpbkApp_dispCbFxn
 *  \brief Driver callback function.
 */
static Int32 LpbkApp_dispCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32              retVal = FVID2_SOK;
    UInt32             captInstId, instCnt;
    LpbkApp_InstObj   *instObj     = (LpbkApp_InstObj *) appData;
    LpbkApp_InstObj   *captInstObj = NULL;
    LpbkApp_Obj       *appObj      = instObj->appObj;
    Fvid2_FrameList    frmList, newFrmList;
    LpbkApp_FrameInfo *frmInfo;

    retVal = Fvid2_dequeue(
        instObj->dispDrvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        /* Figure out to which capture instance the frame belongs to */
        captInstId = Vps_captGetInstId(frmList.frames[0U]->chNum);
        for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
        {
            if (appObj->instObj[instCnt].captInstId == captInstId)
            {
                captInstObj = &appObj->instObj[instCnt];
            }
        }

        if (captInstObj != NULL)
        {
            if (FVID2_SF_INTERLACED == appObj->testPrms.captScanFormat)
            {
                GT_assert(BspAppTrace, (frmList.numFrames == 1U));

                /* In case of interlaced, display one frame is two fields of
                 * capture. Convert the frame to two fields of capture */
                frmInfo = (LpbkApp_FrameInfo *) frmList.frames[0U]->appData;

                Fvid2FrameList_init(&newFrmList);

                newFrmList.frames[0U] = frmList.frames[0U];
                newFrmList.numFrames++;
                newFrmList.frames[1U] = frmInfo->bufPair;
                newFrmList.numFrames++;

                retVal =
                    Fvid2_queue(captInstObj->captDrvHandle, &newFrmList, 0U);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Capture Queue Failed!!!\r\n");
                }
            }
            else
            {
                retVal = Fvid2_queue(captInstObj->captDrvHandle, &frmList, 0U);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Capture Queue Failed!!!\r\n");
                }
            }
        }
    }

    return (retVal);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 LpbkApp_captAllocQueueFrm(const LpbkApp_Obj *appObj,
                                       LpbkApp_InstObj   *instObj,
                                       UInt32             fieldMerged)
{
    Int32               retVal = FVID2_SOK;
    UInt32              streamId, chId, frmId, idx;
    UInt32              bufSize;
    UInt32              yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format       *fmt;
    Fvid2_Frame        *frm;
    Fvid2_FrameList     frmList;
    Vps_CaptVipOutInfo *outInfo;
    Char fileStr[30U];

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < instObj->captCreatePrms.numStream;
         streamId++)
    {
        for (chId = 0U; chId < instObj->captCreatePrms.numCh; chId++)
        {
            outInfo = &instObj->vipPrms.outStreamInfo[streamId];
            fmt     = &instObj->captAllocFmt;
            Fvid2Format_init(fmt);

            /* base index for instObj->captFrames[] */
            idx =
                (VPS_CAPT_CH_PER_PORT_MAX * LPBK_APP_FRAMES_PER_CH
                 * streamId) + (LPBK_APP_FRAMES_PER_CH * chId);

            if (idx >= LPBK_APP_CAPT_MAX_FRM)
            {
                idx = 0U;
            }
            frm = &instObj->captFrames[idx];

            /* fill format with channel specific values  */
            fmt->chNum =
                Vps_captMakeChNum(instObj->captInstId, streamId, chId);
            fmt->width  = appObj->maxWidth;
            fmt->height = appObj->maxHeight + LPBK_APP_PADDING_LINES;
            if (fieldMerged)
            {
                fmt->height *= 2;
            }
            fmt->pitch[0U] = outInfo->outFmt.pitch[0U];
            fmt->pitch[1U] = outInfo->outFmt.pitch[1U];
            fmt->pitch[2U] = outInfo->outFmt.pitch[2U];
            if (FVID2_SF_INTERLACED == appObj->testPrms.captScanFormat)
            {
                /* Field merge capture - pitch is already doubled */
                fmt->pitch[0U] /= 2U;
                fmt->pitch[1U] /= 2U;
                fmt->pitch[2U] /= 2U;
            }
            fmt->fieldMerged[0U] = FALSE;
            fmt->fieldMerged[1U] = FALSE;
            fmt->fieldMerged[2U] = FALSE;
            fmt->dataFormat      = outInfo->outFmt.dataFormat;
            fmt->scanFormat      = FVID2_SF_PROGRESSIVE;
            fmt->bpp = FVID2_BPP_BITS8; /* ignored */

            Fvid2Frame_init(&instObj->captDropFrame);
            instObj->captDropFrame.chNum = fmt->chNum;
            instObj->isDropFrmWithDriver = FALSE;

            /*
             * alloc memory based on 'format'
             * Allocated frame info is put in frames[]
             * LPBK_APP_FRAMES_PER_CH is the number of buffers per channel to
             * allocate
             */
            retVal = BspUtils_memFrameAlloc(fmt, frm, LPBK_APP_FRAMES_PER_CH);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Frame Alloc Failed!!!\r\n");
                break;
            }

            snprintf(fileStr, 30U, "loopbackOption%uInst%uCh%uStr%u",
                     (unsigned int) appObj->testPrms.testId,
                     (unsigned int) instObj->captInstId,
                     (unsigned int) chId,
                     (unsigned int) streamId);
            BspUtils_memFrameGetSize(fmt, &bufSize, NULL);
            BspOsal_cacheInv(frm[0U].addr[0U][0U],
                             (LPBK_APP_FRAMES_PER_CH * bufSize),
                             BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
            BspUtils_appPrintSaveRawCmd(
                fileStr,
                frm[0U].addr[0U][0U],
                outInfo->outFmt.dataFormat,
                fmt->width,
                fmt->height,
                (LPBK_APP_FRAMES_PER_CH * bufSize));

            if (BSP_PLATFORM_ID_ZEBU != Bsp_platformGetId())
            {
                /* Fill with background color */
                BspUtils_memset(
                    frm[0U].addr[0U][0U],
                    0x10U,
                    (LPBK_APP_FRAMES_PER_CH * bufSize));
                /* Flush and invalidate the CPU write */
                BspOsal_cacheWbInv(
                    frm[0U].addr[0U][0U],
                    (LPBK_APP_FRAMES_PER_CH * bufSize),
                    BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
            }

            for (frmId = 0U; frmId < LPBK_APP_FRAMES_PER_CH; frmId++)
            {
                /* Fill frame info */
                instObj->captFrameInfo[frmId].bufFid  = FVID2_FID_TOP;
                instObj->captFrameInfo[frmId].bufPair =
                    &instObj->captFramesOdd[frmId];
                instObj->captFrameInfo[frmId].instObj = instObj;

                frm[frmId].fid     = FVID2_FID_FRAME;
                frm[frmId].appData = &instObj->captFrameInfo[frmId];

                /* Since BspUtils_memFrameAlloc is setting the address
                 * for only top field, set addresses for bottom fields. */
                if (Fvid2_isDataFmtYuv422I(fmt->dataFormat))
                {
                    yFld1Offset = (UInt32) frm[frmId].addr[0U][0U] +
                                  fmt->pitch[0U];
                    frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                }
                if (Fvid2_isDataFmtSemiPlanar(fmt->dataFormat))
                {
                    yFld1Offset =
                        (UInt32) frm[frmId].addr[0U][0U] + fmt->pitch[0U];
                    cbCrFld0Offset =
                        (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                                  (fmt->pitch[0U] * appObj->maxHeight));
                    cbCrFld1Offset =
                        (UInt32) (cbCrFld0Offset + fmt->pitch[0U]);
                    frm[frmId].addr[0U][1U] = (Ptr) cbCrFld0Offset;
                    frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                    frm[frmId].addr[1U][1U] = (Ptr) cbCrFld1Offset;
                }

                /* Set number of frame in frame list */
                frmList.frames[0U] = &frm[frmId];
                frmList.numFrames  = 1U;

                /* In case of field capture give odd field frame */
                if (FVID2_SF_INTERLACED == appObj->testPrms.captScanFormat)
                {
                    BspUtils_memcpy(
                        &instObj->captFramesOdd[frmId],
                        &frm[frmId],
                        sizeof (Fvid2_Frame));

                    /* Fill frame info */
                    instObj->captFrameInfoOdd[frmId].bufFid  = FVID2_FID_BOTTOM;
                    instObj->captFrameInfoOdd[frmId].bufPair =
                        &instObj->captFrames[frmId];
                    instObj->captFrameInfoOdd[frmId].instObj = instObj;

                    /* Set the odd address and app data */
                    instObj->captFramesOdd[frmId].appData =
                        &instObj->captFrameInfoOdd[frmId];
                    instObj->captFramesOdd[frmId].addr[0U][0U] =
                        instObj->captFramesOdd[frmId].addr[1U][0U];
                    instObj->captFramesOdd[frmId].addr[0U][1U] =
                        instObj->captFramesOdd[frmId].addr[1U][1U];
                    instObj->captFramesOdd[frmId].addr[0U][2U] =
                        instObj->captFramesOdd[frmId].addr[1U][2U];

                    /* Queue the odd frame */
                    frmList.frames[1U] = &instObj->captFramesOdd[frmId];
                    frmList.numFrames++;
                }

                /*
                 * queue the frames in frmList
                 * All allocate frames are queued here as an example.
                 * In general atleast 2 frames per channel need to queued
                 * before starting capture,
                 * else frame will get dropped until frames are queued
                 */
                retVal =
                    Fvid2_queue(instObj->captDrvHandle, &frmList, streamId);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Capture Queue Failed!!!\r\n");
                    break;
                }
            }

            if (FVID2_SOK != retVal)
            {
                break;
            }
        }

        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief Free frames
 */
static Int32 LpbkApp_captFreeFrm(LpbkApp_Obj     *appObj,
                                 LpbkApp_InstObj *instObj,
                                 UInt32           fieldMerged)
{
    Int32         retVal = FVID2_SOK;
    UInt32        streamId, chId, idx;
    Fvid2_Format *fmt;
    Fvid2_Frame  *frm;

    /* for every stream and channel in a capture handle */
    for (streamId = 0U; streamId < instObj->captCreatePrms.numStream;
         streamId++)
    {
        for (chId = 0U; chId < instObj->captCreatePrms.numCh; chId++)
        {
            fmt = &instObj->captAllocFmt;

            /* base index for instObj->captFrames[] */
            idx =
                (VPS_CAPT_CH_PER_PORT_MAX * LPBK_APP_FRAMES_PER_CH
                 * streamId) + (LPBK_APP_FRAMES_PER_CH * chId);

            if (idx >= LPBK_APP_CAPT_MAX_FRM)
            {
                idx = 0U;
            }
            frm = &instObj->captFrames[idx];

            retVal |= BspUtils_memFrameFree(fmt, frm, LPBK_APP_FRAMES_PER_CH);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Frame Free Failed!!!\r\n");
            }
        }
    }

    return (retVal);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 LpbkApp_dispAllocQueueFrm(const LpbkApp_Obj *appObj,
                                       LpbkApp_InstObj   *instObj)
{
    Int32           retVal = FVID2_SOK;
    UInt32          frmId;
    UInt32          bufSize;
    UInt32          yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format   *fmt;
    Fvid2_Frame    *frm;
    Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);

    fmt = &instObj->dispAllocFmt;
    Fvid2Format_init(fmt);
    frm = &instObj->dispFrames[0U];

    /* fill format with channel specific values  */
    /* Set channel number as invalid so that the blank frame is used only
     * at the start */
    fmt->chNum = Vps_captMakeChNum(
        VPS_CAPT_INST_MAX,
        VPS_CAPT_STREAM_ID_MAX,
        VPS_CAPT_CH_PER_PORT_MAX);
    fmt->width           = instObj->captAllocFmt.width;
    fmt->height          = instObj->captAllocFmt.height;
    fmt->pitch[0U]       = instObj->captAllocFmt.pitch[0U];
    fmt->pitch[1U]       = instObj->captAllocFmt.pitch[1U];
    fmt->pitch[2U]       = instObj->captAllocFmt.pitch[2U];
    fmt->fieldMerged[0U] = FALSE;
    fmt->fieldMerged[1U] = FALSE;
    fmt->fieldMerged[2U] = FALSE;
    fmt->dataFormat      = instObj->captAllocFmt.dataFormat;
    fmt->scanFormat      = FVID2_SF_PROGRESSIVE;
    fmt->bpp = FVID2_BPP_BITS16;    /* ignored */

    /*
     * alloc memory based on 'format'
     * Allocated frame info is put in frames[]
     * LPBK_APP_DISP_MAX_FRM is the number of buffers per channel to
     * allocate
     */
    retVal = BspUtils_memFrameAlloc(fmt, frm, LPBK_APP_DISP_MAX_FRM);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
    }

    for (frmId = 0U; frmId < LPBK_APP_DISP_MAX_FRM; frmId++)
    {
        frm[frmId].fid     = FVID2_FID_FRAME;
        frm[frmId].appData = instObj;

        if (BSP_PLATFORM_ID_ZEBU != Bsp_platformGetId())
        {
            /* Fill with background color */
            BspUtils_memFrameGetSize(fmt, &bufSize, NULL);
            BspUtils_memset(frm[frmId].addr[0U][0U], 0x10U, bufSize);
            /* Flush and invalidate the CPU write */
            BspOsal_cacheWbInv(
                frm[frmId].addr[0U][0U],
                bufSize,
                BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
        }

        /* Since BspUtils_memFrameAlloc is setting the address
         * for only top field, set addresses for bottom fields. */
        if (Fvid2_isDataFmtYuv422I(fmt->dataFormat))
        {
            yFld1Offset = (UInt32) frm[frmId].addr[0U][0U] +
                          fmt->pitch[0U];
            frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
        }
        if (Fvid2_isDataFmtSemiPlanar(fmt->dataFormat))
        {
            yFld1Offset =
                (UInt32) frm[frmId].addr[0U][0U] + fmt->pitch[0U];
            cbCrFld0Offset =
                (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                          (fmt->pitch[0U] * appObj->maxHeight));
            cbCrFld1Offset =
                (UInt32) (cbCrFld0Offset + fmt->pitch[0U]);
            frm[frmId].addr[0U][1U] = (Ptr) cbCrFld0Offset;
            frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
            frm[frmId].addr[1U][1U] = (Ptr) cbCrFld1Offset;
        }

        /* Set number of frame in frame list - one at a time */
        frmList.numFrames  = 1U;
        frmList.frames[0U] = &frm[frmId];

        /*
         * queue the frames in frmList
         * All allocate frames are queued here as an example.
         * In general atleast 2 frames per channel need to queued
         * before starting display,
         * else frame will get dropped until frames are queued
         */
        retVal = Fvid2_queue(instObj->dispDrvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Queue Failed!!!\r\n");
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief Free frames
 */
static Int32 LpbkApp_dispFreeFrm(LpbkApp_Obj     *appObj,
                                 LpbkApp_InstObj *instObj)
{
    Int32         retVal = FVID2_SOK;
    Fvid2_Format *fmt;
    Fvid2_Frame  *frm;

    fmt = &instObj->dispAllocFmt;
    frm = &instObj->dispFrames[0U];

    retVal |= BspUtils_memFrameFree(fmt, frm, LPBK_APP_DISP_MAX_FRM);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Free Failed!!!\r\n");
    }

    return (retVal);
}

static void LpbkApp_configureLCD(LpbkApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 lcdCtrlInstId;
#if defined (SOC_TDA2PX)
#else
    UInt32 lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    UInt32 brightVal;
    UInt32 syncMode;
#endif
    UInt32 lcdCtrlDrvId;

    UInt32 instId = VPS_DSS_DISPC_OVLY_DPI1;
    if (appObj->testPrms.vencId[0U] == VPS_DCTRL_DSS_VENC_LCD3)
    {
        instId = VPS_DSS_DISPC_OVLY_DPI3;
    }
    lcdCtrlDrvId = FVID2_LCD_CTRL_DRV;

    lcdCtrlInstId = Bsp_boardGetVideoDeviceInstId(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        instId);

    /* Power on LCD controller */
    retVal = Bsp_boardPowerOnDevice(lcdCtrlDrvId, lcdCtrlInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device Power On failed\r\n");
    }

    /* select lcd Controller at board level mux */
    retVal = Bsp_boardSelectDevice(lcdCtrlDrvId, lcdCtrlInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
    }

    /* Perform any reset needed at board level */
    retVal = Bsp_boardResetDevice(lcdCtrlDrvId, lcdCtrlInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device reset failed\r\n");
    }

    /* Select specific mode */
    retVal = Bsp_boardSelectMode(
        lcdCtrlDrvId,
        lcdCtrlInstId,
        appObj->testPrms.dispBoardMode);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
    }

    /* After TLC is powered on, some delay to get it stabilized */
    BspOsal_sleep(5);

#if defined (SOC_TDA2PX)
#else
    lcdCtrlI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        instId);

    lcdCtrlI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        lcdCtrlDrvId,
        FVID2_VPS_DCTRL_DRV,
        instId);

    appObj->lcdCtrlCreatePrms.deviceI2cAddr[0]   = lcdCtrlI2cAddr;
    appObj->lcdCtrlCreatePrms.deviceResetGpio[0] = 0;
    appObj->lcdCtrlCreatePrms.deviceI2cInstId    = lcdCtrlI2cInstId;
    appObj->lcdCtrlCreatePrms.numDevices         = 1;

    appObj->lcdCtrlHandle = Fvid2_create(
        FVID2_LCD_CTRL_DRV,
        0,
        &appObj->lcdCtrlCreatePrms,
        NULL,
        NULL);

    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_POWER_ON,
        NULL,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Lcd powering on Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_ENABLE_BACKLIGHT,
        NULL,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Enabling backlight failed!!!\r\n");
    }

    syncMode = BSP_LCD_CTRL_MODE_DE;

    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_SELECT_MODE_DE_OR_SYNC,
        &syncMode,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Selecting sync mode failed!!!\r\n");
    }

    /* Brightness Value is 75% */
    brightVal = 75;

    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_CONTROL_BRIGHTNESS,
        &brightVal,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Controlling LCD brightness Failed!!!\r\n");
    }

    /* Get the LCD timings */
    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_GET_PANEL_INFO,
        &appObj->lcdPanelInfo,
        NULL);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Get LCD timing failed!!!\r\n");
    }
#endif

    return;
}

static void LpbkApp_turnoffLCD(LpbkApp_Obj *appObj)
{
#if defined (SOC_TDA2PX)
#else
    Int32 retVal = FVID2_SOK;

    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT,
        NULL,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Disable backlight failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->lcdCtrlHandle,
        IOCTL_BSP_LCDCTRL_POWER_OFF,
        NULL,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Lcd powering Off Failed!!!\r\n");
    }

    retVal = Fvid2_delete(appObj->lcdCtrlHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": LCD Ctrl handle delete failed!!!\r\n");
    }
#endif
}

static Int32 LpbkApp_configureOffChipHdmi(LpbkApp_Obj *appObj, UInt32 encInst)
{
    Int32  retVal = FVID2_SOK;
    UInt32 vidEncInstId, vidEncI2cInstId, vidEncI2cAddr;
    UInt32 vidEncDrvId;
    Bsp_VidEncCreateParams encCreateParams;
    Bsp_Sii9022aHpdParams  hpdPrms;
    Bsp_Sii9022aHdmiChipId hdmiId;
    Bsp_VidEncConfigParams modePrms;
    Bsp_VidEncCreateStatus encCreateStatus;

    vidEncDrvId = appObj->testPrms.encDrvId[encInst];

    vidEncInstId = Bsp_boardGetVideoDeviceInstId(
        vidEncDrvId,
        FVID2_VPS_DCTRL_DRV,
        VPS_DSS_DISPC_OVLY_DPI1);

    vidEncI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        vidEncDrvId,
        FVID2_VPS_DCTRL_DRV,
        VPS_DSS_DISPC_OVLY_DPI1);

    vidEncI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        vidEncDrvId,
        FVID2_VPS_DCTRL_DRV,
        VPS_DSS_DISPC_OVLY_DPI1);

    /* Power on Video Encoder */
    retVal = Bsp_boardPowerOnDevice(vidEncDrvId, vidEncInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device Power On failed\r\n");
    }

    /* select Video Encoder at board level mux */
    retVal = Bsp_boardSelectDevice(vidEncDrvId, vidEncInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
    }

    /* Perform any reset needed at board level */
    retVal = Bsp_boardResetDevice(vidEncDrvId, vidEncInstId);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device reset failed\r\n");
    }

    /* Select specific mode */
    retVal = Bsp_boardSelectMode(
        vidEncDrvId,
        vidEncInstId,
        appObj->testPrms.dispBoardMode);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Open HDMI Tx */
        encCreateParams.deviceI2cInstId     = vidEncI2cInstId;
        encCreateParams.deviceI2cAddr       = vidEncI2cAddr;
        encCreateParams.inpClk              = 0u;
        encCreateParams.hotPlugGpioIntrLine = 0u;
        encCreateParams.clkEdge             = FALSE;

        appObj->hdmiHandle = Fvid2_create(
            FVID2_VID_ENC_SII9022A_DRV,
            0u,
            &encCreateParams,
            &encCreateStatus,
            NULL);
        if (NULL == appObj->hdmiHandle)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: SII9022 create failed!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID,
            &hdmiId,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Could not get detailed chip ID!!\r\n");
        }
        else
        {
            GT_4trace(
                BspAppTrace, GT_DEBUG,
                APP_NAME
                "\r\nhdmiId.deviceId = %d,hdmiId.deviceProdRevId = %d, \
                hdmiId.hdcpRevTpi = %d,hdmiId.tpiRevId = %d\r\n",
                hdmiId.deviceId,
                hdmiId.deviceProdRevId, hdmiId.hdcpRevTpi,
                hdmiId.tpiRevId);
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_SII9022A_QUERY_HPD,
            &hpdPrms,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Could not detect HPD!!\r\n");
        }
        else
        {
            GT_3trace(
                BspAppTrace, GT_DEBUG,
                APP_NAME
                "\r\nhpdPrms.busError= %d, hpdPrms.hpdEvtPending= %d, \
                hpdPrms.hpdStatus= %d\r\n",
                hpdPrms.busError,
                hpdPrms.hpdEvtPending,
                hpdPrms.hpdStatus);
        }
    }

    if (FVID2_SOK == retVal)
    {
        BspVidEncConfigParams_init(&modePrms);
        modePrms.standard        = appObj->testPrms.dispStandard[encInst];
        modePrms.videoIfMode     = FVID2_VIFM_SCH_DS_AVID_VSYNC;
        modePrms.videoIfWidth    = FVID2_VIFW_24BIT;
        modePrms.videoDataFormat = FVID2_DF_RGB24_888;

        retVal = Fvid2_control(
            appObj->hdmiHandle,
            IOCTL_BSP_VID_ENC_SET_MODE,
            &modePrms,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Could not set mode!!\r\n");
        }
    }

    if ((FVID2_SOK != retVal) && (NULL != appObj->hdmiHandle))
    {
        /* Close HDMI transmitter */
        retVal += Fvid2_delete(appObj->hdmiHandle, NULL);
        appObj->hdmiHandle = NULL;
    }

    return retVal;
}

static Int32 LpbkApp_deConfigureOffChipHdmi(LpbkApp_Obj *appObj,
                                            UInt32       encInst)
{
    Int32 retVal = FVID2_SOK;

    if (NULL != appObj->hdmiHandle)
    {
        retVal = Fvid2_stop(appObj->hdmiHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Off-chip HDMI stop failed!!\r\n");
        }
    }

    if (NULL != appObj->hdmiHandle)
    {
        /* Close HDMI transmitter */
        retVal += Fvid2_delete(appObj->hdmiHandle, NULL);
        appObj->hdmiHandle = NULL;
    }

    return (retVal);
}

/**
 *  \brief Create and configure video decoder.
 */
static Int32 LpbkApp_createVidDec(LpbkApp_Obj     *appObj,
                                  LpbkApp_InstObj *instObj)
{
    Int32  retVal;
    UInt32 decInstId, decI2cInstId, decI2cAddr;
    Vps_CaptCreateParams  *pVipCreatePrms;
    Bsp_VidDecChipIdParams decChipIdPrms;
    Bsp_VidDecChipIdStatus decChipIdStatus;
    Bsp_VidDecCreateStatus decCreateStatus;

    pVipCreatePrms = &instObj->captCreatePrms;

    decInstId = Bsp_boardGetVideoDeviceInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->captInstId);
    decI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->captInstId);
    decI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->captInstId);

    /* Power on video decoder */
    retVal = Bsp_boardPowerOnDevice(instObj->decDrvId, decInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device power-on failed\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* select video decoder at board level mux */
        retVal = Bsp_boardSelectDevice(instObj->decDrvId, decInstId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
        }
    }

    if (FVID2_SOK != retVal)
    {
        /* Perform any reset needed at board level */
        retVal = Bsp_boardResetDevice(instObj->decDrvId, decInstId);
        if (FVID2_SOK == retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Device reset failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Select specific mode */
        retVal = Bsp_boardSelectMode(
            instObj->decDrvId,
            decInstId,
            appObj->testPrms.captBoardMode);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
        }
    }

    if ((FVID2_VID_DEC_TVP7002_DRV == instObj->decDrvId) &&
        (FVID2_SOK == retVal))
    {
        /* Enable THS filter */
        retVal = Bsp_boardEnableTvp7002Filter(
            decInstId,
            appObj->testPrms.captStandard);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "THS filter programming failed\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        instObj->decCreatePrms.deviceI2cInstId     = decI2cInstId;
        instObj->decCreatePrms.numDevicesAtPort    = 1U;
        instObj->decCreatePrms.deviceI2cAddr[0U]   = decI2cAddr;
        instObj->decCreatePrms.deviceResetGpio[0U] = BSP_VID_DEC_GPIO_NONE;
        instObj->decHandle = Fvid2_create(
            instObj->decDrvId,
            decInstId,
            &instObj->decCreatePrms,
            &decCreateStatus,
            NULL);
        GT_assert(BspAppTrace, instObj->decHandle != NULL);

        decChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->decHandle,
            IOCTL_BSP_VID_DEC_GET_CHIP_ID,
            &decChipIdPrms,
            &decChipIdStatus);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        instObj->decVideoModePrms.videoIfWidth =
            pVipCreatePrms->videoIfWidth;
        instObj->decVideoModePrms.videoDataFormat =
            appObj->testPrms.captInDataFmt;
        instObj->decVideoModePrms.standard =
            appObj->testPrms.captStandard;
        instObj->decVideoModePrms.videoIfMode = pVipCreatePrms->videoIfMode;
        /* TVP7002 supports only ACTVID/VSYNC mode of operation in single
         * channel
         * discrete sync mode */
        if ((instObj->decDrvId == FVID2_VID_DEC_TVP7002_DRV) &&
            (pVipCreatePrms->videoIfMode != FVID2_VIFM_SCH_ES))
        {
            instObj->decVideoModePrms.videoIfMode =
                FVID2_VIFM_SCH_DS_AVID_VSYNC;
        }
        instObj->decVideoModePrms.videoSystem =
            BSP_VID_DEC_VIDEO_SYSTEM_AUTO_DETECT;
        instObj->decVideoModePrms.videoAutoDetectTimeout =
            FVID2_TIMEOUT_FOREVER;
        instObj->decVideoModePrms.videoCropEnable = FALSE;

        GT_6trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": VIP %d: VID DEC %04x (0x%02x): %04x:%04x:%04x\r\n",
            instObj->captInstId,
            instObj->decDrvId,
            instObj->decCreatePrms.deviceI2cAddr[0U],
            decChipIdStatus.chipId,
            decChipIdStatus.chipRevision,
            decChipIdStatus.firmwareVersion);

        LpbkApp_detectVideo(appObj, instObj);
    }
    return (retVal);
}

/**
 *  \brief Create and configure video sensor.
 */
static Int32 LpbkApp_createVidSensor(const LpbkApp_Obj *appObj,
                                     LpbkApp_InstObj   *instObj)
{
    Int32  retVal;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr;
    Bsp_VidSensorChipIdParams sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus sensorChipIdStatus;
    Bsp_VidSensorCreateStatus sensorCreateStatus;

    sensorInstId = Bsp_boardGetVideoDeviceInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->captInstId);
    sensorI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->captInstId);
    sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        instObj->decDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->captInstId);

    /* Power on video sensor at board level mux */
    retVal = Bsp_boardPowerOnDevice(instObj->decDrvId, sensorInstId, TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device power-on failed\r\n");
    }
    else
    {
        /* select video sensor at board level mux */
        retVal = Bsp_boardSelectDevice(instObj->decDrvId, sensorInstId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Device select failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Select specific mode */
        retVal = Bsp_boardSelectMode(
            instObj->decDrvId,
            sensorInstId,
            appObj->testPrms.captBoardMode);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
        }
    }

    if ((BSP_BOARD_MULTIDES == Bsp_boardGetId()) &&
        ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_GW4200_IMX290_DRV == instObj->decDrvId)) &&
        (FVID2_SOK == retVal))
    {
        retVal = BspUtils_appConfSerDeSer(instObj->decDrvId, sensorInstId);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                APP_NAME
                ": Configuring MultiDes instance %d failed!!!\r\n",
                sensorInstId);
        }
    }

    if (FVID2_SOK == retVal)
    {
        instObj->sensorCreatePrms.deviceI2cInstId     = sensorI2cInstId;
        instObj->sensorCreatePrms.numDevicesAtPort    = 1U;
        instObj->sensorCreatePrms.deviceI2cAddr[0U]   = sensorI2cAddr;
        instObj->sensorCreatePrms.deviceResetGpio[0U] =
            BSP_VID_SENSOR_GPIO_NONE;
        instObj->sensorCreatePrms.sensorCfg    = NULL;
        instObj->sensorCreatePrms.numSensorCfg = 0U;
        instObj->decHandle = Fvid2_create(
            instObj->decDrvId,
            sensorInstId,
            &instObj->sensorCreatePrms,
            &sensorCreateStatus,
            NULL);
        GT_assert(BspAppTrace, instObj->decHandle != NULL);

        sensorChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->decHandle,
            IOCTL_BSP_VID_SENSOR_GET_CHIP_ID,
            &sensorChipIdPrms,
            &sensorChipIdStatus);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        GT_6trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": VIP %d: VID SENSOR %04x (0x%02x): %04x:%04x:%04x\r\n",
            instObj->captInstId,
            instObj->decDrvId,
            instObj->sensorCreatePrms.deviceI2cAddr[0U],
            sensorChipIdStatus.chipId,
            sensorChipIdStatus.chipRevision,
            sensorChipIdStatus.firmwareVersion);
    }

    /* Configure sensor in UYVY 8-bit 1280x720 @ 30FPS, OV only supports
     *   1280x720 @ 30FPS and VIP expects data in UYVY . */
    if (((FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_OV2659_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_GW4200_IMX290_DRV == instObj->decDrvId)) &&
        (FVID2_SOK == retVal))
    {
        Bsp_VidSensorConfigParams configParams;
        configParams.videoIfWidth = appObj->testPrms.captVideoIfWidth;
        configParams.dataformat   = FVID2_DF_YUV422I_UYVY;
        configParams.standard     = appObj->testPrms.captStandard;
        configParams.fps          = FVID2_FPS_30;
        retVal =
            Fvid2_control(instObj->decHandle, IOCTL_BSP_VID_SENSOR_SET_CONFIG,
                          &configParams,
                          NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));
    }

    /* start sensor, right now only OV sensor driver is implemented */
    if (((FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_OV2659_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId) ||
         (FVID2_VID_SENSOR_GW4200_IMX290_DRV == instObj->decDrvId)) &&
        (FVID2_SOK == retVal))
    {
        retVal = Fvid2_control(instObj->decHandle, FVID2_START, NULL, NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));
    }

    return (retVal);
}

static Int32 LpbkApp_detectVideo(LpbkApp_Obj     *appObj,
                                 LpbkApp_InstObj *instObj)
{
    Int32  retVal;
    UInt32 chId, repeatCnt;
    Bsp_VidDecVideoStatusParams videoStatusPrms;
    Bsp_VidDecVideoStatus       videoStatus;

    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Detect video in progress for inst %d !!!\r\n",
              instObj->captInstId);

    retVal = Fvid2_control(
        instObj->decHandle,
        IOCTL_BSP_VID_DEC_SET_VIDEO_MODE,
        &instObj->decVideoModePrms,
        NULL);
    GT_assert(BspAppTrace, (retVal == FVID2_SOK));

    for (chId = 0U; chId < instObj->captCreatePrms.numCh; chId++)
    {
        repeatCnt = 25;
        while (--repeatCnt != 0)
        {
            videoStatusPrms.channelNum = chId;
            retVal = Fvid2_control(
                instObj->decHandle,
                IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS,
                &videoStatusPrms,
                &videoStatus);
            GT_assert(BspAppTrace, (retVal == FVID2_SOK));

            if (videoStatus.isVideoDetect)
            {
                GT_5trace(
                    BspAppTrace, GT_INFO,
                    APP_NAME
                    ": Detected video at CH%d (%dx%d@%dHz, %d)!!!\r\n",
                    chId,
                    videoStatus.frameWidth,
                    videoStatus.frameHeight,
                    (1000000U / videoStatus.frameInterval),
                    videoStatus.isInterlaced);
                break;
            }
            BspOsal_sleep(100);
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Detect video Done !!!\r\n");

    return (FVID2_SOK);
}

static Int32 LpbkApp_selectSimVideoSource(const LpbkApp_Obj *appObj,
                                          LpbkApp_InstObj   *instObj)
{
    UInt32 instId, fileId, pixelClk;

    /*
     * Select input source file,
     *
     * Assumes that the simulator VIP super file contents are like below
     *
     * 1 <user path>\output_bt656_QCIF.bin - 8 -bit YUV422 single CH input
     * 2 <user path>\output_bt1120_QCIF.bin - 16-bit YUV422 single CH input
     * 3 <user path>\output_bt1120_QCIF_RGB.bin - 24-bit RGB888 single CH input
     * 4 <user path>\output_tvp5158_8CH_bt656_QCIF.bin - 8-bit YUV422 multi
     * CH input
     */
    pixelClk = 1300 * 1000;

    switch (appObj->testPrms.captVideoIfMode)
    {
        case FVID2_VIFM_SCH_ES:
            switch (appObj->testPrms.captVideoIfWidth)
            {
                case FVID2_VIFW_8BIT:
                    fileId = 1;
                    break;

                case FVID2_VIFW_16BIT:
                    fileId = 2;
                    break;

                case FVID2_VIFW_24BIT:
                    fileId = 3;
                    break;

                default:
                    /* Default to 8-bit */
                    fileId = 1;
                    break;
            }
            break;

        case FVID2_VIFM_MCH_LINE_MUX_ES:
            fileId    = 4;
            pixelClk *= 8; /* assumes eight CHs in input file */
            break;

        default:
            /* Default to 8-bit */
            fileId = 1;
            break;
    }

    for (instId = 0U; instId < VPS_CAPT_INST_MAX; instId++)
    {
        Bsp_platformSimVideoInputSelect(instId, fileId, pixelClk);
    }

    return (FVID2_SOK);
}

Int32 LpbkApp_configureVideoPllAndClkSrc(LpbkApp_Obj *appObj, UInt32 pixelClk)
{
    Bsp_PlatformSetPllFreq vPllCfg;
    Bsp_PlatformVencSrc    vencClkCfg;
    Int32 retVal = FVID2_SOK;

    vPllCfg.videoPll         = BSP_PLATFORM_PLL_VIDEO1;
    vPllCfg.pixelClk         = pixelClk;
    vPllCfg.chooseMaxorMinMN = (UInt32) BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN;

    if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
    {
        vPllCfg.videoPll = BSP_PLATFORM_PLL_EVE_VID_DSP;
    }

    retVal = Bsp_platformSetPllFreq(&vPllCfg);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Configuring Pll Failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        if (appObj->testPrms.vencId[0U] == VPS_DCTRL_DSS_VENC_LCD3)
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD3;
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT3;
        }
        else
        {
            vencClkCfg.outputVenc = BSP_PLATFORM_VENC_LCD1;
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_VIDEO1_CLKOUT1;
        }

        if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
        {
            vencClkCfg.vencClkSrc = BSP_PLATFORM_CLKSRC_DPLL_EVE_VID_DSP;
        }

        retVal = Bsp_platformSetVencClkSrc(&vencClkCfg);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Setting Venc clock source Failed!!!\r\n");
        }
    }

    return retVal;
}

/**
 *  LpbkApp_initParams
 *  Initialize the global variables and frame pointers.
 */
static void LpbkApp_initParams(LpbkApp_Obj *appObj)
{
    UInt32 streamId, chId, instCnt, plId;
    Vps_CaptCreateParams *createPrms;
    Vps_CaptVipParams    *vipPrms;
    Vps_CaptVipScParams  *scPrms;
    Vps_CaptVipOutInfo   *outInfo;
    Vps_DispDssParams    *dssPrms;
    LpbkApp_InstObj      *instObj;
    UInt32 maxHandles;

    appObj->maxWidth          = LPBK_APP_BUF_WIDTH;
    appObj->maxHeight         = LPBK_APP_BUF_HEIGHT;
    appObj->totalCaptFldCount = 0U;
    appObj->totalDispCount    = 0U;
    appObj->totalCpuLoad      = 0U;
    appObj->cpuLoadCount      = 0U;
    appObj->callBackCount     = 0U;
    appObj->curCaptInstance   = 0U;

    maxHandles = appObj->testPrms.numCaptHandles;
    if (maxHandles < appObj->testPrms.numDispHandles)
    {
        maxHandles = appObj->testPrms.numDispHandles;
    }
    for (instCnt = 0U; instCnt < maxHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->captInstId    = appObj->testPrms.captInstId[instCnt];
        instObj->dispInstId    = appObj->testPrms.dispInstId[instCnt];
        instObj->decDrvId      = appObj->testPrms.decDrvId[instCnt];
        instObj->encDrvId      = appObj->testPrms.encDrvId[instCnt];
        instObj->captDrvHandle = NULL;
        instObj->dispDrvHandle = NULL;
        Fvid2CbParams_init(&instObj->captCbPrms);
        instObj->captCbPrms.cbFxn   = &LpbkApp_captCbFxn;
        instObj->captCbPrms.appData = instObj;
        Fvid2CbParams_init(&instObj->dispCbPrms);
        instObj->dispCbPrms.cbFxn   = &LpbkApp_dispCbFxn;
        instObj->dispCbPrms.appData = instObj;
        instObj->appObj = appObj;

        createPrms = &instObj->captCreatePrms;
        VpsCaptCreateParams_init(createPrms);
        createPrms->videoIfMode  = appObj->testPrms.captVideoIfMode;
        createPrms->videoIfWidth = appObj->testPrms.captVideoIfWidth;
        createPrms->bufCaptMode  = VPS_CAPT_BCM_LAST_FRM_REPEAT;
        createPrms->numCh        = LPBK_APP_NUM_CAPT_CH;
        createPrms->numStream    = LPBK_APP_NUM_CAPT_STREAM;

        vipPrms = &instObj->vipPrms;
        VpsCaptVipParams_init(vipPrms);
        vipPrms->inFmt.chNum           = 0U;
        vipPrms->inFmt.width           = appObj->testPrms.captInWidth;
        vipPrms->inFmt.height          = appObj->testPrms.captInHeight;
        vipPrms->inFmt.pitch[0U]       = 0U;
        vipPrms->inFmt.pitch[1U]       = 0U;
        vipPrms->inFmt.pitch[2U]       = 0U;
        vipPrms->inFmt.fieldMerged[0U] = FALSE;
        vipPrms->inFmt.fieldMerged[1U] = FALSE;
        vipPrms->inFmt.fieldMerged[2U] = FALSE;
        vipPrms->inFmt.dataFormat      = appObj->testPrms.captInDataFmt;
        vipPrms->inFmt.scanFormat      = FVID2_SF_PROGRESSIVE;
        vipPrms->inFmt.bpp      = FVID2_BPP_BITS16;
        vipPrms->inFmt.reserved = NULL;

        scPrms          = &instObj->vipScPrms;
        vipPrms->scPrms = scPrms;
        VpsCaptVipScParams_init(scPrms);
        scPrms->inCropCfg.cropStartX   = 0U;
        scPrms->inCropCfg.cropStartY   = 0U;
        scPrms->inCropCfg.cropWidth    = vipPrms->inFmt.width;
        scPrms->inCropCfg.cropHeight   = vipPrms->inFmt.height;
        scPrms->scCfg.bypass           = FALSE;
        scPrms->scCfg.nonLinear        = FALSE;
        scPrms->scCfg.stripSize        = 0U;
        scPrms->scCfg.enableEdgeDetect = TRUE;
        scPrms->scCfg.enablePeaking    = TRUE;
        scPrms->scCfg.advCfg           = NULL;
        scPrms->scCoeffCfg      = NULL;
        scPrms->enableCoeffLoad = FALSE;
        vipPrms->vipPortCfg     = NULL;

        Bsp_platformSetVipClkInversion(instObj->captInstId, FALSE);
        if (FVID2_VID_SENSOR_MT9V022_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;
        }
        else if ((FVID2_VID_SENSOR_OV1063X_DRV == instObj->decDrvId) ||
                 (FVID2_VID_SENSOR_LI_OV1063X_DRV == instObj->decDrvId) ||
                 (FVID2_VID_SENSOR_OV2659_DRV == instObj->decDrvId) ||
                 (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId))
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;

            /* Enable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = TRUE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1280U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 720U;
        }
        else if (FVID2_VID_SENSOR_GW4200_IMX290_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;

            /* Enable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = TRUE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 20U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 11U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1920U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 1080U;
        }
        else if (FVID2_VID_DEC_SII9127_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_HIGH;

            /* Disable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = FALSE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1920U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 1080U;
        }
        else if (FVID2_VID_DEC_ADV7611_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol  = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.hsyncPol  = FVID2_POL_LOW;

            /* Disable VIP cropping */
            instObj->vipPortCfg.actCropEnable     = FALSE;
            instObj->vipPortCfg.actCropCfg.srcNum = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartX = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropStartY = 0U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropWidth  = 1920U;
            instObj->vipPortCfg.actCropCfg.cropCfg.cropHeight = 1080U;
        }
        else if (FVID2_VID_DEC_TVP5158_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.comCfg.pixClkEdgePol = FVID2_EDGE_POL_FALLING;
            Bsp_platformSetVipClkInversion(instObj->captInstId, TRUE);
        }
        else if (FVID2_VID_DEC_DS90UH926_DRV == instObj->decDrvId)
        {
            vipPrms->vipPortCfg = &instObj->vipPortCfg;
            VpsVipPortConfig_init(&instObj->vipPortCfg);
            instObj->vipPortCfg.disCfg.actvidPol     = FVID2_POL_HIGH;
            instObj->vipPortCfg.disCfg.vsyncPol      = FVID2_POL_LOW;
            instObj->vipPortCfg.disCfg.hsyncPol      = FVID2_POL_LOW;
            instObj->vipPortCfg.comCfg.pixClkEdgePol = FVID2_EDGE_POL_FALLING;
            Bsp_platformSetVipClkInversion(instObj->captInstId, TRUE);
        }
        vipPrms->cscCfg = NULL;

        for (streamId = 0U; streamId < LPBK_APP_NUM_CAPT_STREAM; streamId++)
        {
            for (chId = 0U; chId < VPS_CAPT_CH_PER_PORT_MAX; chId++)
            {
                createPrms->chNumMap[streamId][chId] =
                    Vps_captMakeChNum(instObj->captInstId, streamId, chId);
            }
            outInfo = &vipPrms->outStreamInfo[streamId];
            outInfo->outFmt.chNum           = 0U;
            outInfo->outFmt.width           = appObj->testPrms.captOutWidth;
            outInfo->outFmt.height          = appObj->testPrms.captOutHeight;
            outInfo->outFmt.fieldMerged[0U] = FALSE;
            outInfo->outFmt.fieldMerged[1U] = FALSE;
            outInfo->outFmt.fieldMerged[2U] = FALSE;
            outInfo->outFmt.dataFormat      = appObj->testPrms.captOutDataFmt;
            outInfo->outFmt.scanFormat      = FVID2_SF_PROGRESSIVE;
            outInfo->outFmt.bpp       = FVID2_BPP_BITS16;
            outInfo->outFmt.pitch[0U] = 0U;
            outInfo->outFmt.pitch[1U] = 0U;
            outInfo->outFmt.pitch[2U] = 0U;
            if (Fvid2_isDataFmtSemiPlanar(outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth, VPS_BUFFER_ALIGNMENT);
                outInfo->outFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                    outInfo->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX];
            }
            else if (Fvid2_isDataFmtYuv422I(outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth * 2U, VPS_BUFFER_ALIGNMENT);
            }
            else if (Fvid2_isDataFmtRgb32bit(outInfo->outFmt.dataFormat))
            {
                outInfo->outFmt.pitch[FVID2_RGB_ADDR_IDX] =
                    VpsUtils_align(appObj->maxWidth * 4U, VPS_BUFFER_ALIGNMENT);
            }
            else
            {
                /* Align the pitch to BPP boundary as well since the pitch
                 * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
                 * bytes (1 pixel) */
                outInfo->outFmt.pitch[FVID2_RGB_ADDR_IDX] =
                    VpsUtils_align(
                        appObj->maxWidth * 3U, (VPS_BUFFER_ALIGNMENT * 3U));
            }

            if (FVID2_SF_INTERLACED == appObj->testPrms.captScanFormat)
            {
                /* Field merge capture - double the pitch */
                outInfo->outFmt.pitch[0U] *= 2U;
                outInfo->outFmt.pitch[1U] *= 2U;
                outInfo->outFmt.pitch[2U] *= 2U;
            }

            outInfo->bufFmt  = FVID2_BUF_FMT_FRAME;
            outInfo->memType = VPS_VPDMA_MT_NONTILEDMEM;
            if (!Bsp_platformIsTI814xFamilyBuild())
            {
                outInfo->maxOutWidth[0U]  = VPS_VPDMA_MAX_OUT_WIDTH_REG1;
                outInfo->maxOutHeight[0U] = VPS_VPDMA_MAX_OUT_HEIGHT_REG1;
                for (plId = 1U; plId < FVID2_MAX_PLANES; plId++)
                {
                    outInfo->maxOutWidth[plId]  = VPS_VPDMA_MAX_OUT_WIDTH_REG2;
                    outInfo->maxOutHeight[plId] =
                        VPS_VPDMA_MAX_OUT_HEIGHT_REG2;
                }
            }
            else
            {
                for (plId = 0U; plId < FVID2_MAX_PLANES; plId++)
                {
                    outInfo->maxOutWidth[plId] =
                        VPS_VPDMA_MAX_OUT_WIDTH_1920_PIXELS;
                    outInfo->maxOutHeight[plId] =
                        VPS_VPDMA_MAX_OUT_HEIGHT_1080_LINES;
                }
            }

            outInfo->scEnable = FALSE;
            if (LPBK_APP_SC_ENABLE_ALL == appObj->testPrms.captScEnable)
            {
                outInfo->scEnable = TRUE;
            }
            if ((0U == streamId) &&
                (LPBK_APP_SC_ENABLE_0 == appObj->testPrms.captScEnable))
            {
                outInfo->scEnable = TRUE;
            }
            if ((1U == streamId) &&
                (LPBK_APP_SC_ENABLE_1 == appObj->testPrms.captScEnable))
            {
                outInfo->scEnable = TRUE;
            }
            outInfo->subFrmPrms.subFrameEnable      = FALSE;
            outInfo->subFrmPrms.numLinesPerSubFrame = 0U;
            outInfo->subFrmPrms.subFrameCb          = NULL;
        }

        instObj->maxOutWidth[0U]  = LPBK_APP_MAXSIZE_1_WIDTH;
        instObj->maxOutHeight[0U] = LPBK_APP_MAXSIZE_1_HEIGHT;
        instObj->maxOutWidth[1U]  = LPBK_APP_MAXSIZE_2_WIDTH;
        instObj->maxOutHeight[1U] = LPBK_APP_MAXSIZE_2_HEIGHT;
        instObj->maxOutWidth[2U]  = LPBK_APP_MAXSIZE_3_WIDTH;
        instObj->maxOutHeight[2U] = LPBK_APP_MAXSIZE_3_HEIGHT;

        VpsDispCreateParams_init(&instObj->dispCreatePrms);

        dssPrms = &instObj->dispDssPrms;
        VpsDispDssParams_init(dssPrms);
        dssPrms->inFmt.chNum           = 0U;
        dssPrms->inFmt.width           = appObj->testPrms.dispInWidth;
        dssPrms->inFmt.height          = appObj->testPrms.dispInHeight;
        dssPrms->inFmt.fieldMerged[0U] = TRUE;
        dssPrms->inFmt.fieldMerged[1U] = TRUE;
        dssPrms->inFmt.fieldMerged[2U] = TRUE;
        dssPrms->inFmt.dataFormat      = appObj->testPrms.captOutDataFmt;
        dssPrms->inFmt.scanFormat      = FVID2_SF_PROGRESSIVE;
        if (TRUE == appObj->testPrms.isSdVenc)
        {
            dssPrms->inFmt.scanFormat = FVID2_SF_INTERLACED;
        }
        dssPrms->inFmt.bpp      = FVID2_BPP_BITS16;
        dssPrms->inFmt.reserved = NULL;
        dssPrms->tarWidth       = appObj->testPrms.tarWidth;
        dssPrms->tarHeight      = appObj->testPrms.tarHeight;
        dssPrms->posX           = 0U;
        dssPrms->posY           = 0U;
        VpsDssDispcVidConfig_init(&instObj->dispVidCfg);
        VpsDssDispcGfxConfig_init(&instObj->dispGfxCfg);
        /*
         * If input resolution and output resolution is different, enable
         * scaling
         */
        if ((dssPrms->tarWidth != dssPrms->inFmt.width) ||
            (dssPrms->tarHeight != dssPrms->inFmt.height))
        {
            instObj->dispVidCfg.pipeCfg.scEnable = TRUE;
        }
        else
        {
            instObj->dispVidCfg.pipeCfg.scEnable = FALSE;
        }

        if (Vps_dispIsVidInst(instObj->dispInstId))
        {
            dssPrms->vidCfg = &instObj->dispVidCfg;
        }
        if (Vps_dispIsGfxInst(instObj->dispInstId))
        {
            dssPrms->gfxCfg = &instObj->dispGfxCfg;
        }
    }

    return;
}

static void LpbkApp_printStatistics(LpbkApp_Obj *appObj,
                                    UInt32       execTimeInMsecs)
{
    UInt32           instCnt;
    LpbkApp_InstObj *instObj;
    UInt32           cpuLoad = 0U;

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " Execution Statistics \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " ==================== \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Execution time    : %d.%d s \r\n",
              (execTimeInMsecs / 1000), (execTimeInMsecs % 1000));
    GT_2trace(BspAppTrace, GT_INFO,
              " Total field Count : %d (%d fields/sec) \r\n",
              appObj->totalCaptFldCount,
              (appObj->totalCaptFldCount * 1000) / execTimeInMsecs);
    if (appObj->cpuLoadCount != 0U)
    {
        /* Load count is non Zero, Valid CPU load value is updated. */
        cpuLoad = appObj->totalCpuLoad / appObj->cpuLoadCount;
    }
    GT_1trace(BspAppTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              cpuLoad);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Print the capture driver status */
        BspUtils_appPrintCaptStatus(
            instObj->captDrvHandle,
            instObj->captInstId,
            instObj->captCreatePrms.numStream,
            instObj->captCreatePrms.numCh,
            execTimeInMsecs);
    }

    for (instCnt = 0U; instCnt < appObj->testPrms.numDispHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Print the display driver status */
        BspUtils_appPrintDispStatus(
            instObj->dispDrvHandle,
            instObj->dispInstId,
            execTimeInMsecs);
    }

    /* Print the Display Controller error status */
    BspUtils_appPrintDctrlStatus(
        appObj->dctrlHandle);

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return;
}

