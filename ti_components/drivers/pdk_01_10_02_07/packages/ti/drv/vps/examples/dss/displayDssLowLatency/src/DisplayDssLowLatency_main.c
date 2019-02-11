/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file DisplayDssLowLatency_main.c
 *
 *  \brief DSS Display sample application to test low latency feature of DSS.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <DisplayDssLowLatency_main.h>

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

static void DispApp_createTsk(void);
static void DispApp_tskMain(UArg arg0, UArg arg1);

static void DispApp_init(DispApp_Obj *appObj);
static void DispApp_deInit(DispApp_Obj *appObj);

static void DispApp_runTest(DispApp_Obj              *appObj,
                            const DispApp_TestParams *testPrms);

static void DispApp_create(DispApp_Obj *appObj);
static void DispApp_delete(DispApp_Obj *appObj);
static Int32 DispApp_configDctrl(DispApp_Obj *appObj);

static Int32 DispApp_configureVideoPllAndClkSrc(DispApp_Obj *appObj,
                                                UInt32 pixelClk);
static Int32 DispApp_configDctrlPipe(DispApp_Obj *appObj);

static Int32 DispApp_allocAndQueueFrames(DispApp_Obj *appObj,
                                         DispApp_InstObj   *instObj);
static void DispApp_initParams(DispApp_Obj *appObj);
static void DispApp_printStatistics(DispApp_Obj *appObj,
                                    UInt32       execTimeInMsecs);

static void DispApp_configureLCD(DispApp_Obj *appObj);
static void DispApp_turnoffLCD(DispApp_Obj *appObj);

static Int32 DispApp_LoadBuf(DispApp_Obj              *appObj,
                             const DispApp_LoadBufCfg *cfg);
static Int32 DispApp_FreeBuf(DispApp_Obj              *appObj,
                             const DispApp_LoadBufCfg *cfg);
static DispApp_BufInfo *DispApp_GetBufInfo(const DispApp_Obj *appObj,
                                           UInt32             dataFmt,
                                           UInt32             scanFmt,
                                           UInt32             fieldsMerged,
                                           UInt32             pitch);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gDispAppTskStackMain, 32)
#pragma DATA_SECTION(gDispAppTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8           gDispAppTskStackMain[DISP_APP_TSK_STACK_MAIN];

/* Test application object */
static DispApp_Obj     gDispAppObj;

/**
 *  \brief Used for YUYV422 interleaved progressive frame format or interlaced
 *  frame format with fields merged. => 800x480 input
 */
static DispApp_BufInfo Yuyv422FieldsMerged = {NULL, 0u};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    DispApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void DispApp_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = DISP_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gDispAppTskStackMain;
    tskPrms.stackSize     = sizeof (gDispAppTskStackMain);
    tskPrms.arg0          = (UArg) & gDispAppObj;
    gDispAppObj.tskHandle = Task_create(DispApp_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gDispAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gDispAppObj.tskHandle, APP_NAME);

    return;
}

/*
 * Test task main
 */
static void DispApp_tskMain(UArg arg0, UArg arg1)
{
    Bsp_BoardId boardId;
    DispApp_Obj              *appObj = (DispApp_Obj *) arg0;
    const DispApp_TestParams *testPrms;
    BspUtils_MemHeapStatus    startHeapStat, startHeapStat1;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    BspUtils_memGetHeapStat(&startHeapStat);
    DispApp_init(appObj);

    appObj->enableAutoRun = (UInt32) FALSE;
    boardId = Bsp_boardGetId();

    testPrms = &gDispAppTestPrms[0U];
    if (testPrms->boardId & boardId)
    {
        BspUtils_memGetHeapStat(&startHeapStat1);
        BspUtils_appServiceWatchdog();
        DispApp_runTest(appObj, testPrms);

        BspUtils_memCheckHeapStat(&startHeapStat1);
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Skipping test case!!!\r\n");
    }

    DispApp_deInit(appObj);

    BspUtils_memCheckHeapStat(&startHeapStat);
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max stack used for test task: %d bytes\r\n",
              BspOsal_getTaskStackUsage(NULL));
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max system stack used (ISR): %d bytes\r\n",
              BspOsal_getSystemStackUsage());
    BspUtils_appPrintMemStatus();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - DONE !!!\r\n");

    return;
}

static void DispApp_init(DispApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 isI2cInitReq;
    UInt32 defPixelClk;
    UInt32 bufCfgId;

    /* System init */
    isI2cInitReq = TRUE;
    retVal       = BspUtils_appDefaultInit(isI2cInitReq);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Create DCTRL handle, used for common driver configuration */
        appObj->dctrlHandle = Fvid2_create(
            FVID2_VPS_DCTRL_DRV,
            VPS_DCTRL_INST_0,
            NULL,                       /* NULL for VPS_DCTRL_INST_0 */
            NULL,                       /* NULL for VPS_DCTRL_INST_0 */
            NULL);                      /* NULL for VPS_DCTRL_INST_0 */
        if (NULL == appObj->dctrlHandle)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Create Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Set default video PLL clock - This will be changed later based
         * on detected LCD */
        defPixelClk = 29232U * 4U;

        /* No Internal Dividers present in DSS in Tda3xx platform,
         * so default it to 29232 itself. */
        if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
        {
            defPixelClk = 29232U;
        }
        DispApp_configureVideoPllAndClkSrc(appObj, defPixelClk);

        /* Needed onlt for TDA2xx platform. Other platform will do nothing
         * and return OK */
        retVal = Bsp_platformEnableHdmiPll(TRUE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Enabling HDMI PLL Failed!!!\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Load all the Buffers */
        for (bufCfgId = 0;
             bufCfgId <
             (sizeof (gDispDssLoadBufCfg) / sizeof (DispApp_LoadBufCfg));
             bufCfgId++)
        {
            retVal = DispApp_LoadBuf(appObj, &gDispDssLoadBufCfg[bufCfgId]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Load buffer failed!!\r\n");
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": DispApp_init() - DONE !!!\r\n");
    }

    return;
}

static void DispApp_deInit(DispApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 isI2cDeInitReq;
    UInt32 bufCfgId;

    /* Delete DCTRL handle */
    retVal = Fvid2_delete(appObj->dctrlHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL handle delete failed!!!\r\n");
    }
    if (FVID2_SOK == retVal)
    {
        /* Free all the Buffers */
        for (bufCfgId = 0;
             bufCfgId <
             (sizeof (gDispDssLoadBufCfg) / sizeof (DispApp_LoadBufCfg));
             bufCfgId++)
        {
            retVal = DispApp_FreeBuf(appObj, &gDispDssLoadBufCfg[bufCfgId]);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Load buffer failed!!\r\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* System de-init */
        isI2cDeInitReq = TRUE;
        retVal         = BspUtils_appDefaultDeInit(isI2cDeInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": System De-Init Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Needed onlt for TDA2xx platform. Other platform will do nothing
         * and return OK */
        retVal = Bsp_platformEnableHdmiPll(FALSE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Disabling HDMI PLL Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": DispApp_deInit() - DONE !!!\r\n");
    }

    return;
}
/**
 *  DispApp_runTest
 *  Display test function.
 */
static void DispApp_runTest(DispApp_Obj              *appObj,
                            const DispApp_TestParams *testPrms)
{
    Int32            retVal = FVID2_SOK;
    UInt32           displayTime, curTime, prevTime;
    UInt32           loopCount, prevFldCount, curFldCount, fldCount;
    DispApp_InstObj *instObj = &appObj->instObj;
    Fvid2_FrameList  frmList;
    UInt32           frmId;

    loopCount = 0;
    curTime   = prevTime = curFldCount = prevFldCount = 0;
    BspUtils_memcpy(&appObj->testPrms, testPrms, sizeof (appObj->testPrms));

    /* Print test case information */
    GT_2trace(BspAppTrace, GT_INFO,
              APP_NAME ": RUN COUNT %d: INPUT:%d !!!\r\n",
              appObj->testPrms.runCount,
              appObj->testPrms.inDataFmt);

    appObj->startTime = BspOsal_getCurTimeInMsec();

    /* Create driver */
    DispApp_create(appObj);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Starting display ... !!!\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Display in progress ... DO NOT HALT !!!\r\n");

    /* Start the load calculation */
    BspUtils_prfLoadCalcStart();

    /* Start driver */
    retVal = Fvid2_start(instObj->drvHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Start Failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Queue the second frame */
        Semaphore_pend(instObj->cbSem, BIOS_WAIT_FOREVER);

        /* Don't queue immediately - replicate after processing time */
        BspOsal_sleep(DISP_APP_QUEUE_DELAY);

        /* Queue the remaining buffers after display start */
        Fvid2FrameList_init(&frmList);
        for (frmId = DISP_APP_NUM_FRAMES_TO_PRIME;
             frmId < DISP_APP_MAX_FRAMES_PER_HANDLE;
             frmId++)
        {
            /* Set number of frame in frame list - one at a time */
            frmList.numFrames  = 1U;
            frmList.frames[0U] = &instObj->frames[frmId];

            /*
             * queue the frames in frmList
             * All allocate frames are queued here as an example.
             * In general atleast 2 frames per channel need to queued
             * before starting display,
             * else frame will get dropped until frames are queued
             */
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Display Queue Failed!!!\r\n");
                break;
            }

            if (appObj->queueTimeIdx < DISP_APP_NUM_LOG_ENTRIES)
            {
                appObj->queueTime[appObj->queueTimeIdx] =
                    BspOsal_getCurTimeInMsec() - appObj->startTime;
                appObj->queueTimeIdx++;
            }
            if (appObj->allTimeIdx < DISP_APP_NUM_EVT_LOG_ENTRIES)
            {
                appObj->allTime[appObj->allTimeIdx] =
                    BspOsal_getCurTimeInMsec() - appObj->startTime;
                appObj->evtType[appObj->allTimeIdx] = DISP_APP_DSS_QUE_EVT;
                appObj->allTimeIdx++;
            }
        }

        while (loopCount < (appObj->testPrms.runCount * DISP_APP_LCD_FPS))
        {
            /* Wait till we get a callback */
            Semaphore_pend(instObj->cbSem, BIOS_WAIT_FOREVER);

            /* dequeue immediately - replicate processing time */
            retVal = Fvid2_dequeue(
                instObj->drvHandle,
                &frmList,
                0U,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK == retVal)
            {
                if (appObj->dequeueTimeIdx < DISP_APP_NUM_LOG_ENTRIES)
                {
                    appObj->dequeueTime[appObj->dequeueTimeIdx] =
                        BspOsal_getCurTimeInMsec() - appObj->startTime;
                    appObj->dequeueTimeIdx++;
                }
                if (appObj->allTimeIdx < DISP_APP_NUM_EVT_LOG_ENTRIES)
                {
                    appObj->allTime[appObj->allTimeIdx] =
                        BspOsal_getCurTimeInMsec() - appObj->startTime;
                    appObj->evtType[appObj->allTimeIdx] = DISP_APP_DSS_DQUE_EVT;
                    appObj->allTimeIdx++;
                }
            }

            /* Don't queue immediately - replicate after processing time */
            BspOsal_sleep(DISP_APP_QUEUE_DELAY);

            if (FVID2_SOK == retVal)
            {
                retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Display Queue Failed!!!\r\n");
                }
                if (appObj->queueTimeIdx < DISP_APP_NUM_LOG_ENTRIES)
                {
                    appObj->queueTime[appObj->queueTimeIdx] =
                        BspOsal_getCurTimeInMsec() - appObj->startTime;
                    appObj->queueTimeIdx++;
                }
                if (appObj->allTimeIdx < DISP_APP_NUM_EVT_LOG_ENTRIES)
                {
                    appObj->allTime[appObj->allTimeIdx] =
                        BspOsal_getCurTimeInMsec() - appObj->startTime;
                    appObj->evtType[appObj->allTimeIdx] = DISP_APP_DSS_QUE_EVT;
                    appObj->allTimeIdx++;
                }
            }

            if ((loopCount != 0) && ((loopCount % DISP_APP_LCD_FPS) == 0))
            {
                /* Get CPU load */
                appObj->totalCpuLoad += Load_getCPULoad();
                appObj->cpuLoadCount++;
            }

            /* Do runtime print every 5 sec */
            if ((loopCount != 0) && ((loopCount % (5 * DISP_APP_LCD_FPS)) == 0))
            {
                curTime     = BspOsal_getCurTimeInMsec() - appObj->startTime;
                curFldCount = appObj->totalFldCount;

                displayTime = curTime - prevTime;
                fldCount    = curFldCount - prevFldCount;

                prevTime     = curTime;
                prevFldCount = curFldCount;

                Bsp_rprintf(APP_NAME ": %5d.%3ds: Fields = %5d (%3d fps)\r\n",
                            (curTime / 1000), (curTime % 1000),
                            fldCount, ((fldCount * 1000) / displayTime));
            }

            loopCount++;
        }

        /* Stop driver */
        retVal  = Fvid2_stop(instObj->drvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Stop Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Stop the load calculation */
        BspUtils_prfLoadCalcStop();

        displayTime = (BspOsal_getCurTimeInMsec() - appObj->startTime);

        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Stopping display ... DONE !!!\r\n");

        DispApp_printStatistics(appObj, displayTime);

        /* Delete driver */
        DispApp_delete(appObj);

        /* Print the load */
        BspUtils_prfLoadPrintAll(TRUE);
        /* Reset the load */
        BspUtils_prfLoadCalcReset();
    }

    return;
}

/**
 *  DispApp_cbFxn
 *  \brief Driver callback function.
 */
static Int32 DispApp_cbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32            retVal  = FVID2_SOK;
    DispApp_InstObj *instObj = (DispApp_InstObj *) appData;

    /* Transfer complete. Signal it */
    Semaphore_post(instObj->cbSem);

    if (instObj->appObj->isrTimeIdx < DISP_APP_NUM_LOG_ENTRIES)
    {
        instObj->appObj->isrTime[instObj->appObj->isrTimeIdx] =
            BspOsal_getCurTimeInMsec() - instObj->appObj->startTime;
        instObj->appObj->isrTimeIdx++;
    }
    if (instObj->appObj->allTimeIdx < DISP_APP_NUM_EVT_LOG_ENTRIES)
    {
        instObj->appObj->allTime[instObj->appObj->allTimeIdx] =
            BspOsal_getCurTimeInMsec() - instObj->appObj->startTime;
        instObj->appObj->evtType[instObj->appObj->allTimeIdx] =
            DISP_APP_DSS_ISR_EVT;
        instObj->appObj->allTimeIdx++;
    }

    instObj->appObj->callBackCount++;

    return (retVal);
}

static void DispApp_create(DispApp_Obj *appObj)
{
    Int32               retVal = FVID2_SOK;
    DispApp_InstObj    *instObj = &appObj->instObj;
    Semaphore_Params    semPrms;

    DispApp_initParams(appObj);

    /* Configure the Video Encoders/LCD controllers if required */
    /* For J6 Entry change the default venc from LCD1 to LCD3. */
#if defined (SOC_TDA2EX)
    if ((Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_17x17) &&
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD1))
    {
        appObj->testPrms.vencId = VPS_DCTRL_DSS_VENC_LCD3;
    }
#endif

    if (appObj->testPrms.encDrvId == FVID2_LCD_CTRL_DRV)
    {
        UInt32 instId = VPS_DSS_DISPC_OVLY_DPI1;
        if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3)
        {
            instId = VPS_DSS_DISPC_OVLY_DPI3;
        }
        retVal = Bsp_boardSetPinMux(FVID2_VPS_DCTRL_DRV,
                                    instId,
                                    appObj->testPrms.boardMode);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Pin Muxing Failed \r\n");
        }
    }

    /* Configure LCD only if platform is EVM and non SD-Display*/
    if (appObj->testPrms.encDrvId == FVID2_LCD_CTRL_DRV)
    {
        DispApp_configureLCD(appObj);
    }

    DispApp_configDctrl(appObj);

    Semaphore_Params_init(&semPrms);
    instObj->cbSem = Semaphore_create(0, &semPrms, NULL);
    if (NULL == instObj->cbSem)
    {
        GT_1trace(BspAppTrace, GT_ERR, "%s: Sem alloc failed\r\n", APP_NAME);
        retVal = FVID2_EALLOC;
    }

    instObj->drvHandle = Fvid2_create(
        FVID2_VPS_DISP_DRV,
        instObj->instId,
        &instObj->createPrms,
        &instObj->createStatus,
        &instObj->cbPrms);
    if ((NULL == instObj->drvHandle) ||
        (instObj->createStatus.retVal != FVID2_SOK))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Create Failed!!!\r\n");
        retVal = instObj->createStatus.retVal;
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_appPrintDispCreateStatus(&instObj->createStatus);

        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_VPS_DISP_SET_DSS_PARAMS,
            &instObj->dssPrms,
            NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DSS Set Params IOCTL Failed!!!\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        retVal = DispApp_allocAndQueueFrames(appObj, instObj);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Alloc and Queue Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Display create complete!!\r\n");
    }

    return;
}

static Int32 DispApp_configureVideoPllAndClkSrc(DispApp_Obj *appObj,
                                                UInt32 pixelClk)
{
    Bsp_PlatformSetPllFreq vPllCfg;
    Bsp_PlatformVencSrc    vencClkCfg;
    Int32 retVal = FVID2_SOK;

    vPllCfg.videoPll = BSP_PLATFORM_PLL_VIDEO1;
    vPllCfg.pixelClk = pixelClk;
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
        if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3)
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

static void DispApp_delete(DispApp_Obj *appObj)
{
    Int32            retVal;
    DispApp_InstObj *instObj = &appObj->instObj;
    Fvid2_FrameList  frmList;
    Vps_DctrlConfig *dctrlCfg;

    dctrlCfg = &appObj->dctrlCfg;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        NULL);

    /* Turn Off the Video Encoders/LCD controllers if required */
    if (appObj->testPrms.encDrvId == FVID2_LCD_CTRL_DRV)
    {
        DispApp_turnoffLCD(appObj);
    }

    /* Dequeue all the request from the driver */
    while (1U)
    {
        retVal = Fvid2_dequeue(
            instObj->drvHandle,
            &frmList,
            0U,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Delete Failed!!!\r\n");
    }

    Semaphore_delete(&instObj->cbSem);

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Display delete complete!!\r\n");
    }

    return;
}

static Int32 DispApp_configDctrl(DispApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    Vps_DctrlConfig             *dctrlCfg;
    Vps_DssDispcOvlyPanelConfig *panelCfg;
    Fvid2_ModeInfo              *mInfo;
    Vps_DctrlVencDivisorInfo vencDivisors;
    Vps_DctrlOutputInfo vencOutput;
    UInt32 pixelClk;
    DispApp_InstObj *instObj = &appObj->instObj;
    Vps_DssDispcAdvLcdTdmConfig  advTdmPrms;

    dctrlCfg           = &appObj->dctrlCfg;
    VpsDctrlConfig_init(dctrlCfg);
    dctrlCfg->useCase  = VPS_DCTRL_USERSETTINGS;
    dctrlCfg->numEdges = 0U;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
    if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_HDMI)
    {
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_HDMI_BLENDER;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_HDMI_OUTPUT;
        dctrlCfg->numEdges++;

        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_HDMI;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[0U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.standard;
    }
#endif

    if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD1)
    {
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;
#endif

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_LCD1_BLENDER;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_DPI1_OUTPUT;
        dctrlCfg->numEdges++;

        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD1;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[1U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.standard;
    }
    if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3)
    {
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID2_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_VID3_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;
#endif

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_GFX1_INPUT_PATH;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->numEdges++;

        dctrlCfg->edgeInfo[dctrlCfg->numEdges].startNode =
            VPS_DCTRL_DSS_LCD3_BLENDER;
        dctrlCfg->edgeInfo[dctrlCfg->numEdges].endNode =
            VPS_DCTRL_DSS_DPI3_OUTPUT;
        dctrlCfg->numEdges++;

        dctrlCfg->vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD3;
        Fvid2ModeInfo_init(&dctrlCfg->vencInfo.modeInfo[1U].mInfo);
        dctrlCfg->vencInfo.modeInfo[0U].mInfo.standard =
            appObj->testPrms.standard;
    }

    dctrlCfg->vencInfo.numVencs = 1U;

    mInfo = &dctrlCfg->vencInfo.modeInfo[0U].mInfo;
    if (FVID2_STD_CUSTOM == appObj->testPrms.standard)
    {
        if ((appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD1) ||
            (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD2) ||
            (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3))
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
            /* Configure custom timings */
            BspUtils_memcpy(
                mInfo, &appObj->lcdPanelInfo.modeInfo, sizeof (Fvid2_ModeInfo));
        #endif
        }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
        if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_HDMI)
        {
            /* Configure custom timings for 1080P */
            Fvid2ModeInfo_init(mInfo);
            mInfo->standard = FVID2_STD_CUSTOM;

            mInfo->width      = 1920;
            mInfo->height     = 1080;
            mInfo->scanFormat = appObj->testPrms.inScanFormat;

            mInfo->pixelClock  = 74250;
            mInfo->fps         = 60U;
            mInfo->hBackPorch  = 148U;
            mInfo->hSyncLen    = 44U;
            mInfo->hFrontPorch = 88U;
            mInfo->vBackPorch  = 15U;
            mInfo->vSyncLen    = 5U;
            mInfo->vFrontPorch = 2U;
        }
#endif
    }
    else
    {
        /* We are extracting the Pixel Clock frequency which will be used to
         * configure the PLL */
        Fvid2_getModeInfo(mInfo);
        mInfo->scanFormat = appObj->testPrms.inScanFormat;
    }
    dctrlCfg->vencInfo.tiedVencs = 0U;

    panelCfg = &appObj->panelCfg;

    panelCfg->alphaBlenderEnable = 0;
    panelCfg->backGroundColor    = 0x00;
    panelCfg->colorKeyEnable     = 1;
    /* Source transparency color key selected */
    panelCfg->colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    panelCfg->deltaLinesPerPanel = 0;
    panelCfg->transColorKey      = 0x00;

    vencDivisors.vencId     = appObj->testPrms.vencId;
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;

    vencOutput.actVidPolarity   = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.dvoFormat        = VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    vencOutput.hsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.vsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.dataFormat       = FVID2_DF_RGB24_888;
    vencOutput.videoIfWidth     = FVID2_VIFW_24BIT;

    if ((appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3))
    {
        panelCfg->vencId  = appObj->testPrms.vencId;
        vencOutput.vencId = appObj->testPrms.vencId;

        /* Setting hync and vsync pol to be negative as LCD panel expects
         * it to be */
        if (appObj->testPrms.encDrvId == FVID2_LCD_CTRL_DRV)
        {
            /*
             * Due to HW bug, polarity cannot be set by
             * vencOutput.pixelClkPolarity So need to change the register
             * SMA_SW_1 which mirrors some fields of the control register.
             * Only to be called for LCD, not for HDMI.
             */
            if (FVID2_POL_LOW == appObj->lcdPanelInfo.pixelClkPolarity)
            {
                Bsp_platformSetLcdClkPolarity(
                    BSP_PLATFORM_VENC_LCD1, FVID2_POL_LOW);
            }
            vencOutput.hsPolarity   = appObj->lcdPanelInfo.hsPolarity;
            vencOutput.vsPolarity   = appObj->lcdPanelInfo.vsPolarity;
            vencOutput.dataFormat   = appObj->lcdPanelInfo.videoDataFormat;
            vencOutput.videoIfWidth = appObj->lcdPanelInfo.videoIfWidth;

            /* Set display width/height equal to that of LCD width/height */
            if (DISP_APP_USE_LCD_WIDTH == appObj->testPrms.inWidth)
            {
                if (appObj->lcdPanelInfo.modeInfo.width <=
                    DISP_APP_BUF_WIDTH)
                {
                    appObj->testPrms.inWidth =
                        appObj->lcdPanelInfo.modeInfo.width;
                    instObj->inWidth = appObj->lcdPanelInfo.modeInfo.width;
                    instObj->dssPrms.inFmt.width = instObj->inWidth;
                    instObj->dssPrms.tarWidth    = instObj->inWidth;
                }
                else
                {
                    if(VPS_DISP_INST_DSS_GFX1 ==
                        appObj->testPrms.instId)
                    {
                        appObj->testPrms.inWidth = DISP_APP_BUF_WIDTH;
                        instObj->inWidth = DISP_APP_BUF_WIDTH;
                        instObj->dssPrms.inFmt.width = instObj->inWidth;
                        instObj->dssPrms.tarWidth    = instObj->inWidth;
                    }
                    else
                    {
                        /* LCD width is greater than buffer width.
                        * vid in width is kept same as buf width.
                        * vid out width is kept same as LCD width */
                        appObj->testPrms.inWidth =
                            DISP_APP_BUF_WIDTH;
                        instObj->inWidth = DISP_APP_BUF_WIDTH;
                        instObj->dssPrms.inFmt.width = DISP_APP_BUF_WIDTH;
                        instObj->dssPrms.tarWidth    =
                            appObj->lcdPanelInfo.modeInfo.width;
                        instObj->dssPrms.vidCfg->pipeCfg.scEnable = TRUE;
                    }
                }
            }
            if (DISP_APP_USE_LCD_HEIGHT ==
                appObj->testPrms.inHeight)
            {
                if (appObj->lcdPanelInfo.modeInfo.height <=
                    DISP_APP_BUF_HEIGHT)
                {
                    appObj->testPrms.inHeight =
                        appObj->lcdPanelInfo.modeInfo.height;
                    instObj->inHeight =
                        appObj->lcdPanelInfo.modeInfo.height;
                    instObj->dssPrms.inFmt.height = instObj->inHeight;
                    instObj->dssPrms.tarHeight    = instObj->inHeight;
                }
                else
                {
                    if (VPS_DISP_INST_DSS_GFX1 ==
                        appObj->testPrms.instId)
                    {
                        appObj->testPrms.inHeight =
                            DISP_APP_BUF_HEIGHT;
                        instObj->inHeight = DISP_APP_BUF_HEIGHT;
                        instObj->dssPrms.inFmt.height = instObj->inHeight;
                        instObj->dssPrms.tarHeight    = instObj->inHeight;
                    }
                    else
                    {
                        /* LCD height is greater than buffer height.
                        * vid in height is kept same as buf height.
                        * vid out height is kept same as LCD height */
                        appObj->testPrms.inHeight =
                            DISP_APP_BUF_HEIGHT;
                        instObj->inHeight = DISP_APP_BUF_HEIGHT;
                        instObj->dssPrms.inFmt.height = DISP_APP_BUF_HEIGHT;
                        instObj->dssPrms.tarHeight    =
                            appObj->lcdPanelInfo.modeInfo.height;
                        instObj->dssPrms.vidCfg->pipeCfg.scEnable = TRUE;
                    }
                }
            }
        }
    }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
    if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_HDMI)
    {
        panelCfg->vencId = VPS_DCTRL_DSS_VENC_HDMI;

        vencOutput.hsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencOutput.vsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencOutput.vencId     = VPS_DCTRL_DSS_VENC_HDMI;
    }
#endif

    /* This IOCTL should be called before SET_CONFIG_IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_VENC_OUTPUT,
        &vencOutput,
        NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Venc Output IOCTL Failed!!!\r\n");
    }

    if (appObj->testPrms.vencId != VPS_DCTRL_DSS_VENC_HDMI)
    {
        /* TDM param configuration is not applicable for HDMI Overlay. */
        VpsDssDispcAdvLcdTdmConfig_init(&advTdmPrms);
        if (appObj->testPrms.boardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
        {
            advTdmPrms.tdmEnable = 1;
            advTdmPrms.vencId    = appObj->testPrms.vencId;
        }
        else
        {
            /* Disable TDM mode if enabled before for TDM use cases.*/
            advTdmPrms.tdmEnable = 0;
            advTdmPrms.vencId    = appObj->testPrms.vencId;
        }
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
                  APP_NAME ": DCTRL Set OVLY Params IOCTL Failed!!!\r\n");
    }

    /* Setting LCD and PCD values */
    if ((appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3))
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
        /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
        * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed to
        * output 29.232 * 4 MHz and set PCD as 4. */
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
            GT_0trace(BspAppTrace, GT_ERR,
                    APP_NAME ": DCTRL Set Venc Divisors IOCTL Failed!!!\r\n");
        }
#endif
    }
    retVal = DispApp_configDctrlPipe(appObj);

    if ((appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3))
    {
        if (appObj->testPrms.encDrvId == FVID2_LCD_CTRL_DRV)
        {
            /* Reconfigure video PLL clock to match LCD required clock */
            pixelClk = appObj->lcdPanelInfo.modeInfo.pixelClock *
                       vencDivisors.divisorPCD;
            retVal = DispApp_configureVideoPllAndClkSrc(appObj, pixelClk);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
    }

    return (retVal);
}

static Int32 DispApp_configDctrlPipe(DispApp_Obj *appObj)
{
    Vps_DssDispcOvlyPipeConfig *ovlpipecfg;
    DispApp_InstObj *instObj = &appObj->instObj;
    Int32 retVal = FVID2_SOK;

    ovlpipecfg = &instObj->ovlpipeconfig;

    ovlpipecfg->pipeLine    = instObj->instId;
    ovlpipecfg->globalAlpha = 0xFF;
    /* Z-order is in order GFX - 3, VID3 -2 ,VID2 - 1 and VID1 - 0 */
    ovlpipecfg->zorder = instObj->instId;

    if (ovlpipecfg->pipeLine == VPS_DSS_DISPC_PIPE_GFX1)
    {
        /* 50 % blending selected - 0xFF is opaque and 0x00 is
         * transparent */
        ovlpipecfg->globalAlpha = 0x7F;

        /* For tda3xx platform we have only 3 pipeline - so Z-order 2
         * is max */
        if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
        {
            ovlpipecfg->zorder = 2;
        }
    }

    ovlpipecfg->zorderEnable     = 1;
    ovlpipecfg->preMultiplyAlpha = 0;

    retVal += Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS,
        ovlpipecfg,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL Set Pipeline params IOCTL Failed!!!\r\n");
    }

    return retVal;
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 DispApp_allocAndQueueFrames(DispApp_Obj *appObj,
                                         DispApp_InstObj   *instObj)
{
    Int32            retVal = FVID2_SOK;
    UInt32           frmId;
    UInt32           numFrames;
    UInt32           yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format    *fmt;
    Fvid2_Frame     *frm;
    Fvid2_FrameList  frmList;
    DispApp_BufInfo *bufInfo;

    Fvid2FrameList_init(&frmList);

    fmt = &instObj->allocFmt;
    Fvid2Format_init(fmt);
    frm = &instObj->frames[0U];

    /* fill format with channel specific values  */
    fmt->chNum          = 0U;
    fmt->width          = appObj->maxWidth;
    fmt->height         = appObj->maxHeight + DISP_APP_PADDING_LINES;
    fmt->pitch[0]       = instObj->pitch[0];
    fmt->pitch[1]       = instObj->pitch[1];
    fmt->pitch[2]       = instObj->pitch[2];
    fmt->fieldMerged[0] = instObj->isFieldMerge;
    fmt->fieldMerged[1] = FALSE;
    fmt->fieldMerged[2] = FALSE;
    fmt->dataFormat     = instObj->inDataFmt;
    fmt->scanFormat     = instObj->inScanFormat;
    fmt->bpp = FVID2_BPP_BITS16;    /* ignored */

    bufInfo = DispApp_GetBufInfo(appObj, instObj->inDataFmt,
                                 instObj->inScanFormat,
                                 instObj->isFieldMerge, instObj->pitch[0]);
    GT_assert(BspAppTrace, NULL != bufInfo);
    numFrames = bufInfo->totalBufSize / bufInfo->bufSize;
    /* init memory pointer for 'numFrames'  */
    for (frmId = 0U; frmId < numFrames; frmId++)
    {
        /* init Fvid2_Frame to 0's  */
        Fvid2Frame_init(&frm[frmId]);

        /* copy chNum from Fvid2_Format */
        frm[frmId].chNum      = fmt->chNum;
        frm[frmId].addr[0][0] = bufInfo->bufAddr + (frmId * bufInfo->bufSize);
        frm[frmId].fid        = FVID2_FID_FRAME;
        frm[frmId].appData    = instObj;

        /* Since BspUtils_memFrameAlloc is setting the address
         * for only top field, set addresses for bottom fields. */
        if (Fvid2_isDataFmtYuv422I(fmt->dataFormat) ||
            Fvid2_isDataFmtRgb(fmt->dataFormat))
        {
            if (fmt->fieldMerged[0] == TRUE)
            {
                yFld1Offset = (UInt32) frm[frmId].addr[0U][0U] +
                              fmt->pitch[0U];
                frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
            }
            else
            {
                yFld1Offset = (UInt32) frm[frmId].addr[0U][0U] +
                              ((fmt->pitch[0U] * appObj->maxHeight) / 2);
                frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
            }
        }
        if (Fvid2_isDataFmtSemiPlanar(fmt->dataFormat))
        {
            if (fmt->fieldMerged[0] == TRUE)
            {
                yFld1Offset =
                    (UInt32) frm[frmId].addr[0U][0U] + fmt->pitch[0U];
                cbCrFld0Offset =
                    (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                              (fmt->pitch[0U] * appObj->maxHeight * 2U));
                cbCrFld1Offset =
                    (UInt32) (cbCrFld0Offset + fmt->pitch[0U]);
            }
            else
            {
                yFld1Offset =
                    (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                              (fmt->pitch[0U] * appObj->maxHeight * 3U) / 2);

                cbCrFld0Offset =
                    (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                              (fmt->pitch[0U] * appObj->maxHeight));

                cbCrFld1Offset =
                    (UInt32) (yFld1Offset +
                              (fmt->pitch[0U] * appObj->maxHeight));
            }
            frm[frmId].addr[0U][1U] = (Ptr) cbCrFld0Offset;
            frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
            frm[frmId].addr[1U][1U] = (Ptr) cbCrFld1Offset;
        }
    }

    /* Queue only some at the start */
    for (frmId = 0U; frmId < DISP_APP_NUM_FRAMES_TO_PRIME; frmId++)
    {
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
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Queue Failed!!!\r\n");
            break;
        }

        if (appObj->queueTimeIdx < DISP_APP_NUM_LOG_ENTRIES)
        {
            appObj->queueTime[appObj->queueTimeIdx] =
                BspOsal_getCurTimeInMsec() - appObj->startTime;
            appObj->queueTimeIdx++;
        }
        if (appObj->allTimeIdx < DISP_APP_NUM_EVT_LOG_ENTRIES)
        {
            appObj->allTime[appObj->allTimeIdx] =
                BspOsal_getCurTimeInMsec() - appObj->startTime;
            appObj->evtType[appObj->allTimeIdx] = DISP_APP_DSS_QUE_EVT;
            appObj->allTimeIdx++;
        }
    }

    return (retVal);
}

/**
 *  DispApp_initParams
 *  Initialize the global variables and frame pointers.
 */
static void DispApp_initParams(DispApp_Obj *appObj)
{
    Vps_DispDssParams *dssPrms;
    DispApp_InstObj   *instObj = &appObj->instObj;

    appObj->maxWidth  = DISP_APP_BUF_WIDTH;
    appObj->maxHeight = DISP_APP_BUF_HEIGHT;

    appObj->totalFldCount = 0U;
    appObj->totalCpuLoad  = 0U;
    appObj->cpuLoadCount  = 0U;
    appObj->callBackCount = 0U;
    appObj->lcdCtrlhdl    = NULL;

    BspUtils_memset(&appObj->allTime[0U], 0U, sizeof (appObj->allTime));
    BspUtils_memset(&appObj->isrTime[0U], 0U, sizeof (appObj->isrTime));
    BspUtils_memset(&appObj->queueTime[0U], 0U, sizeof (appObj->queueTime));
    BspUtils_memset(&appObj->dequeueTime[0U], 0U, sizeof (appObj->dequeueTime));
    appObj->allTimeIdx = 0U;
    appObj->isrTimeIdx = 0U;
    appObj->queueTimeIdx = 0U;
    appObj->dequeueTimeIdx = 0U;

    instObj->inDataFmt = appObj->testPrms.inDataFmt;

    if (Fvid2_isDataFmtSemiPlanar(instObj->inDataFmt))
    {
        instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            VpsUtils_align(appObj->maxWidth, VPS_BUFFER_ALIGNMENT);
        instObj->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX];
    }
    else if (Fvid2_isDataFmtYuv422I(instObj->inDataFmt))
    {
        instObj->pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(appObj->maxWidth * 2U, VPS_BUFFER_ALIGNMENT);
    }
    else if (Fvid2_isDataFmtRgb16bit(instObj->inDataFmt))
    {
        instObj->pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(appObj->maxWidth * 2U, VPS_BUFFER_ALIGNMENT);
    }
    else if (Fvid2_isDataFmtRgb24bit(instObj->inDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        instObj->pitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(appObj->maxWidth * 3U,
                           (VPS_BUFFER_ALIGNMENT * 3U));
    }
    else if (Fvid2_isDataFmtRgb32bit(instObj->inDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        instObj->pitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(appObj->maxWidth * 4U,
                           (VPS_BUFFER_ALIGNMENT));
    }

    instObj->inWidth      = appObj->testPrms.inWidth;
    instObj->inHeight     = appObj->testPrms.inHeight;
    instObj->isFieldMerge = appObj->testPrms.isFieldMerge;
    instObj->inScanFormat = appObj->testPrms.inScanFormat;
    instObj->posx         = appObj->testPrms.posx;
    instObj->posy         = appObj->testPrms.posy;
    instObj->instId       = appObj->testPrms.instId;
    instObj->drvHandle    = NULL;
    Fvid2CbParams_init(&instObj->cbPrms);
    instObj->cbPrms.cbFxn   = &DispApp_cbFxn;
    instObj->cbPrms.appData = instObj;
    instObj->appObj         = appObj;

    VpsDispCreateParams_init(&instObj->createPrms);

    dssPrms = &instObj->dssPrms;
    VpsDispDssParams_init(&instObj->dssPrms);
    dssPrms->inFmt.chNum           = 0U;
    dssPrms->inFmt.width           = instObj->inWidth;
    dssPrms->inFmt.height          = instObj->inHeight;
    dssPrms->inFmt.pitch[0U]       = instObj->pitch[0U];
    dssPrms->inFmt.pitch[1U]       = instObj->pitch[1U];
    dssPrms->inFmt.pitch[2U]       = instObj->pitch[2U];
    dssPrms->inFmt.fieldMerged[0U] = instObj->isFieldMerge;
    dssPrms->inFmt.fieldMerged[1U] = FALSE;
    dssPrms->inFmt.fieldMerged[2U] = FALSE;
    dssPrms->inFmt.dataFormat      = instObj->inDataFmt;
    dssPrms->inFmt.scanFormat      = instObj->inScanFormat;
    dssPrms->inFmt.bpp      = FVID2_BPP_BITS16;
    dssPrms->inFmt.reserved = NULL;
    dssPrms->tarWidth       = dssPrms->inFmt.width;
    dssPrms->tarHeight      = dssPrms->inFmt.height;
    dssPrms->posX           = instObj->posx;
    dssPrms->posY           = instObj->posy;

    VpsDssDispcVidConfig_init(&instObj->vidCfg);
    VpsDssDispcGfxConfig_init(&instObj->gfxCfg);

    if (Vps_dispIsVidInst(instObj->instId))
    {
        dssPrms->vidCfg = &instObj->vidCfg;
    }
    if (Vps_dispIsGfxInst(instObj->instId))
    {
        dssPrms->gfxCfg = &instObj->gfxCfg;
    }

    return;
}

static void DispApp_printStatistics(DispApp_Obj *appObj,
                                    UInt32       execTimeInMsecs)
{
    UInt32 idx, firstTs = 0U;
    DispApp_InstObj *instObj = &appObj->instObj;
    char *evtArray[] = {"Q", "ISR", "DQ"};
    UInt32 avgCpuLoad = 0U;

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " Execution Statistics \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " ==================== \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Execution time    : %d.%d s \r\n",
              (execTimeInMsecs / 1000), (execTimeInMsecs % 1000));
    GT_2trace(BspAppTrace, GT_INFO,
              " Total field Count : %d (%d fields/sec) \r\n",
              appObj->totalFldCount,
              (appObj->totalFldCount * 1000) / execTimeInMsecs);
    if (appObj->cpuLoadCount != 0U)
    {
        avgCpuLoad = appObj->totalCpuLoad / appObj->cpuLoadCount;
    }
    GT_1trace(BspAppTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              avgCpuLoad);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    /* Print the driver status */
    BspUtils_appPrintDispStatus(
        instObj->drvHandle,
        instObj->instId,
        execTimeInMsecs);

    /* Print the Display Controller error status */
    BspUtils_appPrintDctrlStatus(
        appObj->dctrlHandle);

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    GT_0trace(BspAppTrace, GT_INFO, " Timestamp Statistics in ms\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " --------------------------\r\n");
        GT_0trace(BspAppTrace, GT_INFO, " Index Event    TS(Diff)\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " -----------------------\r\n");
    for (idx = 0U; idx < appObj->allTimeIdx; idx++)
    {
        UInt32 allDiff;

        if (0U == idx)
        {
            firstTs = appObj->allTime[idx];
            allDiff = 0U;
        }
        else
        {
            allDiff = appObj->allTime[idx] - appObj->allTime[idx - 1U];
        }

        GT_4trace(BspAppTrace, GT_INFO, " %5d %-6s %6d(%2d)\r\n",
                  idx,
                  evtArray[appObj->evtType[idx]],
                  (appObj->allTime[idx] - firstTs), allDiff);
    }
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    GT_0trace(BspAppTrace, GT_INFO, " Index QUE_TS(Diff) ISR_TS(Diff) DEQUE_TS(Diff)\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " ----------------------------------------------\r\n");
    for (idx = 0U; idx < DISP_APP_NUM_LOG_ENTRIES; idx++)
    {
        UInt32 isrDiff, qDiff, dqDiff;

        if (0U == idx)
        {
            isrDiff = 0U;
            qDiff = 0U;
            dqDiff = 0U;
        }
        else
        {
            if (idx >= appObj->isrTimeIdx)
            {
                isrDiff = 0U;
            }
            else
            {
                isrDiff = appObj->isrTime[idx] - appObj->isrTime[idx - 1U];
            }
            if (idx >= appObj->queueTimeIdx)
            {
                qDiff = 0U;
            }
            else
            {
                qDiff = appObj->queueTime[idx] - appObj->queueTime[idx - 1U];
            }
            if (idx >= appObj->dequeueTimeIdx)
            {
                dqDiff = 0U;
            }
            else
            {
                dqDiff = appObj->dequeueTime[idx] - appObj->dequeueTime[idx - 1U];
            }
        }

        GT_7trace(BspAppTrace, GT_INFO, " %5d %6d(%2d)   %6d(%2d)   %8d(%2d)\r\n",
                  idx,
                  (appObj->queueTime[idx] - firstTs), qDiff,
                  (appObj->isrTime[idx] - firstTs), isrDiff,
                  (appObj->dequeueTime[idx] - firstTs), dqDiff);
    }

    return;
}

static void DispApp_configureLCD(DispApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 lcdCtrlInstId;
    UInt32 lcdCtrlDrvId;
#if defined (SOC_TDA2PX)
#else
    UInt32 lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    UInt32 brightVal;
    UInt32 syncMode;
#endif
    UInt32 instId = VPS_DSS_DISPC_OVLY_DPI1;
    if (appObj->testPrms.vencId == VPS_DCTRL_DSS_VENC_LCD3)
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
        appObj->testPrms.boardMode);
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

    appObj->lcdCtrlhdl = Fvid2_create(
        FVID2_LCD_CTRL_DRV,
        0,
        &appObj->lcdCtrlCreatePrms,
        NULL,
        NULL);

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_POWER_ON,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Lcd powering on Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl,
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
        appObj->lcdCtrlhdl,
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
        appObj->lcdCtrlhdl,
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
        appObj->lcdCtrlhdl,
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

static void DispApp_turnoffLCD(DispApp_Obj *appObj)
{
#if defined (SOC_TDA2PX)
#else
    Int32 retVal = FVID2_SOK;
    retVal = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_DISABLE_BACKLIGHT,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Disable backlight failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->lcdCtrlhdl,
        IOCTL_BSP_LCDCTRL_POWER_OFF,
        NULL,
        NULL);

    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Lcd powering Off Failed!!!\r\n");
    }

    retVal = Fvid2_delete(appObj->lcdCtrlhdl, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": LCD Ctrl handle delete failed!!!\r\n");
    }
#endif
    return;
}

/**
 *  DispApp_LoadBuf
 */
static Int32 DispApp_LoadBuf(DispApp_Obj              *appObj,
                             const DispApp_LoadBufCfg *cfg)
{
    Int32            retVal = FVID2_SOK;
    char             userInput;
    UInt32           bCnt;
    DispApp_BufInfo *bufInfo = NULL;
    char fileNameString[100];
    UInt32           bytesRead;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            bufInfo = &Yuyv422FieldsMerged;
            memcpy(&bufInfo->bufCfg, cfg, sizeof (DispApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < DISP_APP_MAX_FRAMES_PER_HANDLE; bCnt++)
                {
                    bufInfo->yBufAddrEven[bCnt] = NULL;
                    bufInfo->yBufAddrOdd[bCnt]  = NULL;
                    bufInfo->cBufAddrEven[bCnt] = NULL;
                    bufInfo->cBufAddrOdd[bCnt]  = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 2u)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 2u);
            }
            else
            {
                /* Calculate the new buffer size */
                bufInfo->bufSize =
                    bufInfo->bufCfg.pitch * bufInfo->bufCfg.height;
                bufInfo->totalBufSize =
                    bufInfo->bufSize * bufInfo->bufCfg.numBuffers;
                bufInfo->bufAddr = BspUtils_memAlloc(
                    bufInfo->totalBufSize,
                    VPS_BUFFER_ALIGNMENT);
                if (NULL == bufInfo->bufAddr)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Could not allocate buffer\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(BspAppTrace, NULL != bufInfo->bufAddr);
                }
            }
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
                      "Invalid format: %d\r\n", cfg->dataFmt);
            bufInfo = NULL;
            retVal  = FVID2_EFAIL;
            break;
    }
    if (FVID2_SOK == retVal)
    {
        /* Assign the buffer addresses */
        for (bCnt = 0u; bCnt < DISP_APP_MAX_FRAMES_PER_HANDLE; bCnt++)
        {
            if (FVID2_SF_PROGRESSIVE == cfg->scanFmt)
            {
                bufInfo->yBufAddrEven[bCnt] =
                    (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));

                if (FVID2_DF_YUV422I_YUYV == cfg->dataFmt)
                {
                    bufInfo->yBufAddrEven[bCnt] =
                        (void *) (bufInfo->bufAddr +
                                  (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_BGR24_888 == cfg->dataFmt)
                {
                    bufInfo->bgrBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
            }
            else
            {
                bufInfo->yBufAddrEven[bCnt] =
                    (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));

                if (FVID2_DF_YUV422I_YUYV == cfg->dataFmt)
                {
                    bufInfo->yBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height) / 2u;
                }
            }
        }
        GT_5trace(BspAppTrace, GT_INFO,
                  "Load %d %s video frames of size %dx%d to location: 0x%p\r\n",
                  bufInfo->bufCfg.numBuffers,
                  Fvid2_getDataFmtString(
                      bufInfo->bufCfg.dataFmt),
                  bufInfo->bufCfg.width, bufInfo->bufCfg.height,
                  bufInfo->bufAddr);
        /* Try Loading the file from SD card if present.
         * If file is not present ask user to load using scripting console
         */
        GT_0trace(BspAppTrace, GT_INFO,
                  "Trying to Load buffer from SD card. \r\n" );
        BspUtils_appGetFileName(fileNameString,
                                sizeof (fileNameString),
                                "display",
                                bufInfo->bufCfg.dataFmt,
                                bufInfo->bufCfg.width,
                                bufInfo->bufCfg.height);
        if (BSP_SOK != BspUtils_appLoadFileFromSd(
                fileNameString,
                "/dss_input_files",
                bufInfo->bufAddr,
                bufInfo->totalBufSize,
                &bytesRead))
        {
            GT_0trace(BspAppTrace, GT_INFO,
                "Couldnot Load buffer from SD card.\r\n"
                "waiting for 1 min to load buffer from scripting console"
                "Press any key (in UART console) after loading buffer\r\n");
            BspUtils_appPrintLoadRawCmd(
                "display",
                bufInfo->bufAddr,
                bufInfo->bufCfg.dataFmt,
                bufInfo->bufCfg.width,
                bufInfo->bufCfg.height);
            BspUtils_uartGetChar(&userInput, 60);
            BspOsal_cacheWbInv(bufInfo->bufAddr, bufInfo->totalBufSize,
                               BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
        }
    }
    return retVal;
}

/**
 *  DispApp_LoadBuf
 */
static Int32 DispApp_FreeBuf(DispApp_Obj              *appObj,
                             const DispApp_LoadBufCfg *cfg)
{
    Int32            retVal = FVID2_SOK;
    UInt32           bCnt;
    DispApp_BufInfo *bufInfo = NULL;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing YUYV422 Field Merged Buffer...\r\n");
            bufInfo = &Yuyv422FieldsMerged;
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
                      "Invalid format: %d\r\n", cfg->dataFmt);
            retVal  = FVID2_EFAIL;
            bufInfo = NULL;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        if (NULL != bufInfo->bufAddr)
        {
            /* Free up the buffer */
            BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

            bufInfo->bufAddr      = NULL;
            bufInfo->bufSize      = 0u;
            bufInfo->totalBufSize = 0u;
            for (bCnt = 0u; bCnt < DISP_APP_MAX_FRAMES_PER_HANDLE; bCnt++)
            {
                switch (cfg->dataFmt)
                {
                    case FVID2_DF_YUV422I_YUYV:
                        bufInfo->yBufAddrEven[bCnt] = NULL;
                        break;
                }
            }
        }
    }
    return (retVal);
}

/**
 *  DispApp_GetBufInfo
 */
static DispApp_BufInfo *DispApp_GetBufInfo(const DispApp_Obj *appObj,
                                           UInt32             dataFmt,
                                           UInt32             scanFmt,
                                           UInt32             fieldsMerged,
                                           UInt32             pitch)
{
    DispApp_BufInfo *bufInfo = NULL;

    switch (dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            bufInfo = &Yuyv422FieldsMerged;
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
                      "Invalid format: %d\r\n", dataFmt);
            bufInfo = NULL;
            break;
    }
    return (bufInfo);
}
