/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 *  \file st_captureTestCase.c
 *
 *  \brief Code for testing CAPTURE driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_capture.h>

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
static Int32 st_captInitPhase(st_CaptApp_Obj     *appObj,
                              const st_CaptUtObj *utObj);
static Int32 st_captDeInitPhase(st_CaptApp_Obj     *appObj,
                                const st_CaptUtObj *utObj);
static Int32 st_captCreatePhase(st_CaptApp_Obj     *appObj,
                                const st_CaptUtObj *utObj);
static Int32 st_captDeletePhase(st_CaptApp_Obj     *appObj,
                                const st_CaptUtObj *utObj);
static Int32 st_captStartPhase(st_CaptApp_Obj     *appObj,
                               const st_CaptUtObj *utObj);
static Int32 st_captStopPhase(st_CaptApp_Obj     *appObj,
                              const st_CaptUtObj *utObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_captMainTestCase
 *  Capture test function.
 */
Int32 st_captMainTestCase(st_CaptApp_Obj *appObj, st_CaptUtObj  *utObj)
{
    Int32          retVal = FVID2_SOK, tempRetVal;
    Bool           createFlag;
    UInt32         openCloseCnt, startStopCnt;
    st_SystemCtrl *sysCtrl = (st_SystemCtrl *) appObj->sysCtrl;
    UInt32         captureTime, curTime, prevTime = 0U;
    UInt32         loopCount = 0, prevFldCount = 0U, curFldCount, fldCount;

    retVal = st_captInitPhase(appObj, utObj);

    if (sysCtrl->openCloseCnt > 1u)
    {
        GT_2trace(utObj->traceMask, GT_INFO,
                  "%s: |Open/Close Test Case: %d times|\r\n",
                  UT_NAME, sysCtrl->openCloseCnt);
    }
    openCloseCnt = 0u;
    while (openCloseCnt < sysCtrl->openCloseCnt)
    {
        /* Create phase */
        createFlag = FALSE;
        retVal     = st_captCreatePhase(appObj, utObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(utObj->traceMask, GT_ERR, "Create phase failed\r\n");
        }
        else
        {
            createFlag = TRUE;
        }

        if (FVID2_SOK == retVal)
        {
            if ((1u == sysCtrl->openCloseCnt) &&
                (sysCtrl->startStopCnt > 1u))
            {
                GT_2trace(utObj->traceMask, GT_INFO,
                          "%s: |Start/Stop Test Case: %d times|\r\n",
                          UT_NAME, sysCtrl->startStopCnt);
            }
            startStopCnt = 0u;
            while (startStopCnt < sysCtrl->startStopCnt)
            {
                loopCount = 0u;

                appObj->startTime = BspOsal_getCurTimeInMsec();

                retVal = st_captStartPhase(appObj, utObj);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(utObj->traceMask, GT_ERR,
                              "Start phase failed @ %d start/stop count\r\n",
                              startStopCnt);
                    break;
                }
                startStopCnt++;
                if ((startStopCnt > 0u) &&
                    ((startStopCnt % (START_STOP_CNT_SS / 10u)) == 0u))
                {
                    GT_2trace(utObj->traceMask, GT_INFO,
                              "%s: Start/Stop Test Count: %d\r\n",
                              UT_NAME, startStopCnt);
                }
                if (FVID2_SOK == retVal)
                {
                    /* Capture frames, check status */
                    while (loopCount < appObj->testPrms->testConfig.runCount)
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

                        /* Get CPU load */
                        appObj->totalCpuLoad += Load_getCPULoad();
                        appObj->cpuLoadCount++;

                        /* Do runtime print every 5 sec */
                        if ((loopCount != 0) && ((loopCount % 5) == 0))
                        {
                            curTime = BspOsal_getCurTimeInMsec() -
                                      appObj->startTime;
                            curFldCount = appObj->totalFldCount;

                            captureTime = curTime - prevTime;
                            fldCount    = curFldCount - prevFldCount;

                            prevTime     = curTime;
                            prevFldCount = curFldCount;

                            Bsp_rprintf(
                                UT_NAME
                                ": %5d.%3ds: Fields = %5d (%3d fps)\r\n",
                                (curTime / 1000), (curTime % 1000),
                                fldCount,
                                ((fldCount * 1000) / captureTime));
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
                                          UT_NAME ": Captured %d frames!!\r\n",
                                          appObj->callBackCount);
                            }
                            loopCount = appObj->callBackCount;
                        }
                    }
                    retVal = st_captStopPhase(appObj, utObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_1trace(utObj->traceMask, GT_ERR,
                                  "Stop phase failed @ %d start/stop count\r\n",
                                  startStopCnt);
                        break;
                    }
                }
            }
        }
        if (TRUE == createFlag)
        {
            /* Delete phase */
            tempRetVal = st_captDeletePhase(appObj, utObj);
            if (FVID2_SOK != tempRetVal)
            {
                retVal = tempRetVal;
                GT_0trace(utObj->traceMask, GT_ERR, "Delete phase failed\r\n");
            }
        }

        if (FVID2_SOK != retVal)
        {
            GT_1trace(utObj->traceMask, GT_ERR,
                      "Open/Close failed @ %d count\r\n", openCloseCnt);
            break;
        }

        openCloseCnt++;
        if ((openCloseCnt > 0u) &&
            ((openCloseCnt % (OPEN_CLOSE_CNT_OC / 10u)) == 0u))
        {
            GT_2trace(utObj->traceMask, GT_INFO,
                      "%s: Open/Close Test Count: %d\r\n", UT_NAME,
                      openCloseCnt);
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_2trace(utObj->traceMask, GT_INFO,
                  "%s: Capture Test Case %d Successful!!\r\n",
                  UT_NAME, appObj->testPrms->testConfig.testCaseId);
    }
    else
    {
        GT_2trace(utObj->traceMask, GT_INFO,
                  "%s: Capture Test Case %d Failed!!\r\n",
                  UT_NAME, appObj->testPrms->testConfig.testCaseId);
    }

    retVal = st_captDeInitPhase(appObj, utObj);

    return (retVal);
}

static Int32 st_captInitPhase(st_CaptApp_Obj     *appObj,
                              const st_CaptUtObj *utObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 boardId;

    if (FVID2_SOK == retVal)
    {
        /* Create global capture handle, used for common driver configuration */
        appObj->fvidHandleAll = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ALL,
            NULL,                       /* NULL for VPS_CAPT_INST_ALL */
            NULL,                       /* NULL for VPS_CAPT_INST_ALL */
            NULL);                      /* NULL for VPS_CAPT_INST_ALL */
        if (NULL == appObj->fvidHandleAll)
        {
            GT_0trace(utObj->traceMask, GT_ERR,
                      UT_NAME ": Global Handle Create Failed!!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        boardId = Bsp_boardGetId();

        if (BSP_BOARD_MULTIDES == boardId)
        {
            retVal = BspUtils_appInitSerDeSer();
            if (retVal != FVID2_SOK)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": MultiDes Board Init failed!!!\r\n");
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        GT_0trace(utObj->traceMask, GT_INFO,
                  UT_NAME ": CaptApp_init() - DONE !!!\r\n");
    }

    return retVal;
}

static Int32 st_captDeInitPhase(st_CaptApp_Obj     *appObj,
                                const st_CaptUtObj *utObj)
{
    Int32 retVal = FVID2_SOK;

    /* Delete global VIP capture handle */
    retVal = Fvid2_delete(appObj->fvidHandleAll, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(utObj->traceMask, GT_ERR,
                  UT_NAME ": Global handle delete failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
        {
            retVal =
                BspUtils_appDeInitSerDeSer();
            if (retVal != FVID2_SOK)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": MultiDes Board DeInit failed!!!\r\n");
            }
        }
    }

    if (retVal == FVID2_SOK)
    {
        GT_0trace(utObj->traceMask, GT_INFO,
                  UT_NAME ": CaptApp_deInit() - DONE !!!\r\n");
    }
    return retVal;
}

static Int32 st_captCreatePhase(st_CaptApp_Obj     *appObj,
                                const st_CaptUtObj *utObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    UInt32 streamId, chId;
    st_CaptApp_InstObj    *instObj;
    Vps_VpdmaMaxSizeParams vipMaxSizePrms;
    Vps_CaptFrameSkip      frmSkipPrms;

    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->drvHandle = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            instObj->instId,
            &instObj->createPrms,
            &instObj->createStatus,
            &instObj->cbPrms);
        if ((NULL == instObj->drvHandle) ||
            (instObj->createStatus.retVal != FVID2_SOK))
        {
            GT_0trace(utObj->traceMask, GT_ERR,
                      UT_NAME ": Capture Create Failed!!!\r\n");
            retVal = instObj->createStatus.retVal;
        }

        if (FVID2_SOK == retVal)
        {
            retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_VPS_CAPT_SET_VIP_PARAMS,
                &instObj->vipPrms,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": VIP Set Params IOCTL Failed!!!\r\n");
                Fvid2_delete(instObj->drvHandle, NULL);
                return (retVal);
            }
        }
        if (FVID2_SOK == retVal)
        {
            /* Set frame skip for each channel */
            VpsCaptFrameSkip_init(&frmSkipPrms);
            for (streamId = 0U; streamId < instObj->createPrms.numStream;
                 streamId++)
            {
                for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
                {
                    /* This IOCTL is supported only for frame drop mode */
                    if (instObj->createPrms.bufCaptMode ==
                        VPS_CAPT_BCM_FRM_DROP)
                    {
                        frmSkipPrms.chNum =
                            Vps_captMakeChNum(instObj->instId, streamId, chId);
                        frmSkipPrms.frmSkipMask = ST_CAPT_FRAME_SKIP_PATTERN;
                        retVal = Fvid2_control(
                            instObj->drvHandle,
                            IOCTL_VPS_CAPT_SET_FRAME_SKIP,
                            &frmSkipPrms,
                            NULL);
                        if (retVal != FVID2_SOK)
                        {
                            GT_0trace(
                                utObj->traceMask, GT_ERR,
                                UT_NAME
                                ": VIP Set frame skip IOCTL Failed!!\r\n");
                            break;
                        }
                    }
                }
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            if (!Bsp_platformIsTI814xFamilyBuild())
            {
                VpsVpdmaMaxSizeParams_init(&vipMaxSizePrms);
                vipMaxSizePrms.instId = Vps_captGetVipId(
                    instObj->instId);
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
                        utObj->traceMask, GT_ERR,
                        UT_NAME
                        ": VIP Set Max Frame Size Params IOCTL Failed!!!\r\n");
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            retVal = st_captAllocAndQueueFrames(appObj, instObj, FALSE, utObj);

            if (retVal != FVID2_SOK)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": Capture Alloc and Queue Failed!!!\r\n");
            }
        }

        if (retVal == FVID2_SOK)
        {
            Vps_CaptOverflowParams overflowParams;
            /* Fill the overflowParams with the callback function in case of
             * overflow and the application object corrosponding to that
             * instance of VIP
             */
            overflowParams.overflowCbFxn = (Vps_CaptVipOverflowFxn) &
                                           st_captOverflowCbFxn;
            overflowParams.retParams = (void *) instObj;

            /* Register for overflow intrrupt
             * User can deregister from the interrupt using
             * IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR
             */
            retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_VPS_CAPT_REGISTER_OVF_INTR,
                &overflowParams,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(utObj->traceMask, GT_ERR,
                          UT_NAME ": VIP Set Params IOCTL Failed!!!\r\n");
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
                    (FVID2_VID_SENSOR_OV2659_DRV == instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_APT_AR0132_DRV == instObj->decDrvId) ||
                    (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId))
                {
                    st_captCreateVidSensor(appObj, instObj, utObj, instCnt);
                }
                else if (0U != instObj->decDrvId)
                {
                    st_captCreateVidDec(appObj, instObj, utObj, instCnt);
                }
                else
                {
                    GT_0trace(utObj->traceMask, GT_INFO,
                              UT_NAME ": Skip decoder config!!\r\n");
                }
            }
        }

        if (FVID2_SOK == retVal)
        {
            retVal = Bsp_boardSetPinMux(FVID2_VPS_CAPT_VID_DRV,
                                        instObj->instId,
                                        appObj->testPrms->testConfig.boardMode);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(utObj->traceMask, GT_ERR, "Pin Muxing Failed \r\n");
            }
        }

        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    GT_0trace(utObj->traceMask, GT_INFO,
              UT_NAME ": Capture create complete!!\r\n");

    return (retVal);
}

static Int32 st_captDeletePhase(st_CaptApp_Obj     *appObj,
                                const st_CaptUtObj *utObj)

{
    Int32               retVal = FVID2_SOK;
    UInt32              instCnt, streamId, sensorInstId, boardId;
    st_CaptApp_InstObj *instObj;
    Fvid2_FrameList     frmList;

    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        for (streamId = 0U;
             streamId < instObj->createPrms.numStream;
             streamId++)
        {
            /* Dequeue all the request from the driver */
            while (1U)
            {
                retVal = Fvid2_dequeue(
                    instObj->drvHandle,
                    &frmList,
                    streamId,
                    FVID2_TIMEOUT_NONE);
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }
        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR,
            NULL,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(
                BspAppTrace, GT_ERR,
                UT_NAME
                ": Unregister From Overflow Interrupt Failed!!!\r\n");
        }

        retVal = Fvid2_delete(instObj->drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      UT_NAME ": Capture Delete Failed!!!\r\n");
        }

        /* free frame memory */
        retVal = st_captFreeFrames(appObj, instObj, FALSE, utObj);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      UT_NAME ": Capture Free Frames Failed!!!\r\n");
        }

        if (NULL != instObj->decHandle)
        {
            retVal = Fvid2_delete(instObj->decHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          UT_NAME ": Decoder Delete Failed!!!\r\n");
            }
            instObj->decHandle = NULL;
        }

        /* DeConfiguring a particular instance of SerDeSer */
        boardId = Bsp_boardGetId();

        if ((BSP_BOARD_MULTIDES == boardId) &&
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == instObj->decDrvId))
        {
            sensorInstId = Bsp_boardGetVideoDeviceInstId(
                instObj->decDrvId,
                FVID2_VPS_CAPT_VID_DRV,
                instObj->instId);

            retVal =
                BspUtils_appDeConfSerDeSer(instObj->decDrvId, sensorInstId);
            if (retVal != FVID2_SOK)
            {
                GT_1trace(
                    BspAppTrace, GT_ERR,
                    UT_NAME
                    ": DeConfiguring MultiDes instance %d failed!!!\r\n",
                    sensorInstId);
            }
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, UT_NAME ": Capture delete complete!!\r\n");

    return (retVal);
}

static Int32 st_captStartPhase(st_CaptApp_Obj     *appObj,
                               const st_CaptUtObj *utObj)
{
    st_CaptApp_InstObj *instObj;
    UInt32 instCnt;
    Int32  retVal = FVID2_SOK;

    /* Start decoder*/
    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        if (NULL != instObj->decHandle)
        {
            Fvid2_start(instObj->decHandle, NULL);
        }
    }

    GT_0trace(BspAppTrace, GT_INFO,
              UT_NAME ": Starting capture ... !!!\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              UT_NAME ": Capture in progress ... DO NOT HALT !!!\r\n");
    /* Start driver */
    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        retVal = Fvid2_start(instObj->drvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      UT_NAME ": Capture Start Failed!!!\r\n");
            break;
        }
    }

    return retVal;
}

static Int32 st_captStopPhase(st_CaptApp_Obj     *appObj,
                              const st_CaptUtObj *utObj)
{
    st_CaptApp_InstObj *instObj;
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    UInt32 captureTime;

    /* Stop driver */
    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        retVal  = Fvid2_stop(instObj->drvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      UT_NAME ": Capture Stop Failed!!!\r\n");
        }
    }

    captureTime = (BspOsal_getCurTimeInMsec() - appObj->startTime);

    /* Stop decoder */
    for (instCnt = 0U; instCnt < appObj->testPrms->testConfig.numHandles;
         instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        if (instObj->decHandle)
        {
            Fvid2_stop(instObj->decHandle, NULL);
        }
    }

    st_captPrintStatistics(appObj, captureTime);

    return retVal;
}

