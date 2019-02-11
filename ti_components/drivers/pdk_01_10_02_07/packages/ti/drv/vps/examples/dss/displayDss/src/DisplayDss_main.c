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
 *  \file DisplayDss_main.c
 *
 *  \brief DSS Display sample application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <DisplayDss_main.h>

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

static Int32 DispApp_allocAndQueueFrames(const DispApp_Obj *appObj,
                                         DispApp_InstObj   *instObj);
static void DispApp_initParams(DispApp_Obj *appObj);
static void DispApp_printStatistics(DispApp_Obj *appObj,
                                    UInt32       execTimeInMsecs);
static Int32 DispApp_getTestId(DispApp_Obj *appObj);

static void DispApp_configureLCD(DispApp_Obj *appObj);
static void DispApp_turnoffLCD(DispApp_Obj *appObj);

static Int32 DispApp_configureEncoder(DispApp_Obj *appObj, UInt32 encInst);
static Int32 DispApp_deConfigureEncoder(DispApp_Obj *appObj, UInt32 encInst);

static Int32 DispApp_LoadBuf(DispApp_Obj              *appObj,
                             const DispApp_LoadBufCfg *cfg);
static Int32 DispApp_FreeBuf(DispApp_Obj              *appObj,
                             const DispApp_LoadBufCfg *cfg);
static DispApp_BufInfo *DispApp_GetBufInfo(const DispApp_Obj *appObj,
                                           UInt32             dataFmt,
                                           UInt32             scanFmt,
                                           UInt32             fieldsMerged,
                                           UInt32             pitch);
static void DispApp_updateRtParam(DispApp_InstObj *instObj,
                                  Vps_DssDispcRtParams *rtParam);
static void DispApp_changePattern(DispApp_InstObj *instObj,
                                  DispApp_rtParamPattern *rtParamPattern,
                                  UInt32 patternNum);
static Bool DispApp_isScalingRatioSupported(DispApp_InstObj *instObj,
                                            Vps_DssDispcRtParams *rtParam);
static Int32 DispApp_getTestIndex(Int32 testId);

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
/**
 *  \brief Used for the YUYV422 interleaved interlaced frame format with fields
 *  in seperate planes.. => 800x480 input
 */
static DispApp_BufInfo Yuyv422InterlacedFieldsSep = {NULL, 0u};
/**
 *  \brief Used for BGR888 24-bit progressive frame format with fields merged.
 */
static DispApp_BufInfo BGR24888FieldsMerged = {NULL, 0u};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#define PDK_RAW_BOOT
static Board_STATUS DispApp_boardInit(void)
{
    Board_STATUS ret;
    Board_initCfg boardCfg;

#ifdef PDK_RAW_BOOT
    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_MODULE_CLOCK;
#endif

    boardCfg |= BOARD_INIT_UART_STDIO;
    ret = Board_init(boardCfg);
    return (ret);
}
#endif

int main(void)
{
    static Char stdin_buf[BUFSIZ];

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    UInt32                  tempFuncPtr;
    BspOsal_InitParams_t    bspOsalInitPrms = {0};

    DispApp_boardInit();

    /* Initialize the UART prints */
    BspUtils_uartInit();
    tempFuncPtr = (UInt32) & BspUtils_uartPrint;
    bspOsalInitPrms.printFxn = (BspOsal_PrintFxn) (tempFuncPtr);
    BspOsal_Init(&bspOsalInitPrms);
#endif

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
    Int32       testId;
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
    while (1U)
    {
        /* Get the TestId */
        testId = DispApp_getTestId(appObj);
        if ((testId >= 0) && (testId < DISP_APP_NUM_TESTS))
        {
            testPrms = &gDispAppTestPrms[testId];
            if (testPrms->boardId & boardId)
            {
                BspUtils_memGetHeapStat(&startHeapStat1);
                BspUtils_appServiceWatchdog();
                DispApp_runTest(appObj, testPrms);

                BspUtils_memCheckHeapStat(&startHeapStat1);
            }
            else
            {
                GT_1trace(BspAppTrace, GT_INFO,
                          APP_NAME ": Skipping test case %d!!!\r\n", testId);
            }
        }
        else
        {
            /* Exit */
            break;
        }
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
        if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
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
        }

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
    UInt32           instCnt;
    UInt32           displayTime, curTime, prevTime;
    UInt32           loopCount, prevFldCount, curFldCount, fldCount;
    DispApp_InstObj *instObj = NULL;

    loopCount = 0;
    curTime   = prevTime = curFldCount = prevFldCount = 0;
    BspUtils_memcpy(&appObj->testPrms, testPrms, sizeof (appObj->testPrms));

    /* Print test case information */
    GT_3trace(BspAppTrace, GT_INFO,
              APP_NAME ": HANDLES %d: RUN COUNT %d: INPUT:%d !!!\r\n",
              appObj->testPrms.numHandles,
              appObj->testPrms.runCount,
              appObj->testPrms.inDataFmt[0]);

    /* Create driver */
    DispApp_create(appObj);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Starting display ... !!!\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Display in progress ... DO NOT HALT !!!\r\n");

    appObj->startTime = BspOsal_getCurTimeInMsec();

    /* Start the load calculation */
    BspUtils_prfLoadCalcStart();

    /* Start driver */
    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        retVal = Fvid2_start(instObj->drvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Start Failed!!!\r\n");
            break;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Display frames, check status */
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

            /* Get CPU load */
            appObj->totalCpuLoad += Load_getCPULoad();
            appObj->cpuLoadCount++;

            /* Do runtime print every 5 sec */
            if ((loopCount != 0) && ((loopCount % 5) == 0))
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

            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                loopCount++;
            }
            else
            {
                if (loopCount != appObj->callBackCount)
                {
                    GT_1trace(BspAppTrace, GT_INFO,
                              APP_NAME ": Displayed %d frames!!\r\n",
                              appObj->callBackCount);
                }
                loopCount = appObj->callBackCount;
            }
        }

        /* Stop driver */
        for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            retVal  = Fvid2_stop(instObj->drvHandle, NULL);
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

static void DispApp_create(DispApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt, encInst;
    DispApp_InstObj      *instObj;
    Bsp_LcdCtrlPanelInfo *lcdPanelInfo;

    DispApp_initParams(appObj);

    /* Configure the Video Encoders/LCD controllers if required */
    for (encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {

        /* For J6 Entry change the default venc from LCD1 to LCD3. */
    #if defined (SOC_TDA2EX)
        if ((Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_17x17) &&
            (appObj->testPrms.vencId[encInst] == VPS_DCTRL_DSS_VENC_LCD1))
        {
            appObj->testPrms.vencId[encInst] = VPS_DCTRL_DSS_VENC_LCD3;
        }
    #endif

        if ((appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV) ||
            (appObj->testPrms.encDrvId[encInst] ==
             FVID2_VID_ENC_SII9022A_DRV) ||
            (appObj->testPrms.encDrvId[encInst] == FVID2_VID_ENC_DS90UH925_DRV))
        {
            UInt32 instId = VPS_DSS_DISPC_OVLY_DPI1;
            if (appObj->testPrms.vencId[encInst] == VPS_DCTRL_DSS_VENC_LCD3)
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

        if (appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
        {
            /* Configure LCD only if platform is EVM and non SD-Display*/
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                DispApp_configureLCD(appObj);
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
                lcdPanelInfo->videoIfMode     = FVID2_VIFM_SCH_DS_HSYNC_VSYNC;

                lcdPanelInfo->vsPolarity       = FVID2_POL_HIGH;
                lcdPanelInfo->hsPolarity       = FVID2_POL_HIGH;
                lcdPanelInfo->actVidPolarity   = FVID2_POL_HIGH;
                lcdPanelInfo->fidPolarity      = FVID2_POL_HIGH;
                lcdPanelInfo->pixelClkPolarity = FVID2_POL_HIGH;
            }
        }
        else if ((appObj->testPrms.encDrvId[encInst] ==
                  FVID2_VID_ENC_SII9022A_DRV) ||
                 (appObj->testPrms.encDrvId[encInst] ==
                  FVID2_VID_ENC_DS90UH925_DRV))
        {
            /* Configure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = DispApp_configureEncoder(appObj, encInst);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Configuring Encoder Failed !!!\r\n");
                }
            }
        }
    }

    DispApp_configDctrl(appObj);

    /* Start the Encoder */
    for (encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        if ((FVID2_SOK == retVal) &&
            (appObj->testPrms.encDrvId[encInst] ==
             FVID2_VID_ENC_SII9022A_DRV))
        {
            retVal = Fvid2_start(appObj->hdmiHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Error: decoder start failed!!\r\n");
            }
        }
    }

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
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

        if (FVID2_SOK != retVal)
        {
            break;
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

static void DispApp_delete(DispApp_Obj *appObj)
{
    Int32            retVal;
    UInt32           instCnt, encInst, sdVencEnable;
    DispApp_InstObj *instObj;
    Fvid2_FrameList  frmList;
    Vps_DctrlConfig *dctrlCfg;

    dctrlCfg = &appObj->dctrlCfg;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_VPS_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        NULL);

    /* Turn Off the Video Encoders/LCD controllers if required */
    for (encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        if (appObj->testPrms.encDrvId[encInst] == FVID2_LCD_CTRL_DRV)
        {
            /* Turn off LCD controller only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                DispApp_turnoffLCD(appObj);
            }
        }
        else if ((appObj->testPrms.encDrvId[encInst] ==
                  FVID2_VID_ENC_SII9022A_DRV) ||
                 (appObj->testPrms.encDrvId[encInst] ==
                  FVID2_VID_ENC_DS90UH925_DRV))
        {
            /* DeConfigure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = DispApp_deConfigureEncoder(appObj, encInst);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": Error: DeConfiguring Encoder failed!!\r\n");
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

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

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
            break;
        }
    }
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
    UInt32 pixelClk, instCnt, sdVencEnable;
    DispApp_InstObj *instObj;
    Vps_DssDispcAdvLcdTdmConfig  advTdmPrms;
    Vps_DctrlSDVencVideoStandard vidStd;

    dctrlCfg           = &appObj->dctrlCfg;
    VpsDctrlConfig_init(dctrlCfg);
    dctrlCfg->useCase  = VPS_DCTRL_USERSETTINGS;
    dctrlCfg->numEdges = 0U;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
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
            appObj->testPrms.standard[0U];
    }
#endif

    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1)
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
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
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
            appObj->testPrms.standard[0U];
    }
    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)
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
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
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
            appObj->testPrms.standard[0U];
    }

    dctrlCfg->vencInfo.numVencs = 1U;

    mInfo = &dctrlCfg->vencInfo.modeInfo[0U].mInfo;
    if (FVID2_STD_CUSTOM == appObj->testPrms.standard[0U])
    {
        if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
            (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
            (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
        {
        #if defined (SOC_TDA2PX)
            /* For TDA2Px DPI to HDMI converter is connected, so configure the
             * the standard timing of 1080P. */
            mInfo->standard = FVID2_STD_1080P_60;
            Fvid2_getModeInfo(mInfo);
            mInfo->scanFormat = appObj->testPrms.inScanFormat[0];
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
        defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
        if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
        {
            /* Configure custom timings for 1080P */
            Fvid2ModeInfo_init(mInfo);
            mInfo->standard = FVID2_STD_CUSTOM;

            mInfo->width      = 1920;
            mInfo->height     = 1080;
            mInfo->scanFormat = appObj->testPrms.inScanFormat[0];

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
        mInfo->scanFormat = appObj->testPrms.inScanFormat[0];
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

    vencDivisors.vencId     = appObj->testPrms.vencId[0];
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;

    vencOutput.actVidPolarity   = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.dvoFormat        = VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    vencOutput.hsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.vsPolarity       = VPS_DCTRL_POLARITY_ACT_HIGH;
    vencOutput.dataFormat       = FVID2_DF_RGB24_888;
    vencOutput.videoIfWidth     = FVID2_VIFW_24BIT;

    if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
    {
        panelCfg->vencId  = appObj->testPrms.vencId[0];
        vencOutput.vencId = appObj->testPrms.vencId[0];

        /* Setting hync and vsync pol to be negative as LCD panel expects
         * it to be */
        if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
            (appObj->testPrms.encDrvId[0] == FVID2_LCD_CTRL_DRV))
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
            for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
            {
                instObj = &appObj->instObj[instCnt];

                if (DISP_APP_USE_LCD_WIDTH == appObj->testPrms.inWidth[instCnt])
                {
                    if (appObj->lcdPanelInfo.modeInfo.width <=
                        DISP_APP_BUF_WIDTH)
                    {
                        appObj->testPrms.inWidth[instCnt] =
                            appObj->lcdPanelInfo.modeInfo.width;
                        instObj->inWidth = appObj->lcdPanelInfo.modeInfo.width;
                        instObj->dssPrms.inFmt.width = instObj->inWidth;
                        instObj->dssPrms.tarWidth    = instObj->inWidth;
                    }
                    else
                    {
                        if(VPS_DISP_INST_DSS_GFX1 ==
                            appObj->testPrms.instId[instCnt])
                        {
                            appObj->testPrms.inWidth[instCnt] = DISP_APP_BUF_WIDTH;
                            instObj->inWidth = DISP_APP_BUF_WIDTH;
                            instObj->dssPrms.inFmt.width = instObj->inWidth;
                            instObj->dssPrms.tarWidth    = instObj->inWidth;
                        }
                        else
                        {
                            /* LCD width is greater than buffer width.
                            * vid in width is kept same as buf width.
                            * vid out width is kept same as LCD width */
                            appObj->testPrms.inWidth[instCnt] =
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
                    appObj->testPrms.inHeight[instCnt])
                {
                    if (appObj->lcdPanelInfo.modeInfo.height <=
                        DISP_APP_BUF_HEIGHT)
                    {
                        appObj->testPrms.inHeight[instCnt] =
                            appObj->lcdPanelInfo.modeInfo.height;
                        instObj->inHeight =
                            appObj->lcdPanelInfo.modeInfo.height;
                        instObj->dssPrms.inFmt.height = instObj->inHeight;
                        instObj->dssPrms.tarHeight    = instObj->inHeight;
                    }
                    else
                    {
                        if (VPS_DISP_INST_DSS_GFX1 ==
                            appObj->testPrms.instId[instCnt])
                        {
                            appObj->testPrms.inHeight[instCnt] =
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
                            appObj->testPrms.inHeight[instCnt] =
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
    }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
    if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
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

    if (appObj->testPrms.vencId[0] != VPS_DCTRL_DSS_VENC_HDMI)
    {
        /* TDM param configuration is not applicable for HDMI Overlay. */
        VpsDssDispcAdvLcdTdmConfig_init(&advTdmPrms);
        if (appObj->testPrms.boardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
        {
            advTdmPrms.tdmEnable = 1;
            advTdmPrms.vencId    = appObj->testPrms.vencId[0];
        }
        else
        {
            /* Disable TDM mode if enabled before for TDM use cases.*/
            advTdmPrms.tdmEnable = 0;
            advTdmPrms.vencId    = appObj->testPrms.vencId[0];
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
    if ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
        (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3))
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || \
    defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD) || defined (SOC_AM574x)
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

    if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
        ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
         (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
         (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)))
    {
        if (appObj->testPrms.isSdVenc == TRUE)
        {
            pixelClk = 54000U;
            retVal   = DispApp_configureVideoPllAndClkSrc(appObj, pixelClk);
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
            retVal = DispApp_configureVideoPllAndClkSrc(appObj, pixelClk);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
        else if ((appObj->testPrms.encDrvId[0] ==
                  FVID2_VID_ENC_SII9022A_DRV) ||
                 (appObj->testPrms.encDrvId[0] == FVID2_VID_ENC_DS90UH925_DRV))
        {
            /* Reconfigure video PLL clock to match Sil9022a clock */
            if (appObj->testPrms.boardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
            {
                pixelClk = mInfo->pixelClock * 3;
            }
            else
            {
                pixelClk = mInfo->pixelClock;
            }
            retVal = DispApp_configureVideoPllAndClkSrc(appObj, pixelClk);
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
        vidStd.videoStandard = appObj->testPrms.standard[0U];

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

static Int32 DispApp_configDctrlPipe(DispApp_Obj *appObj)
{
    Vps_DssDispcOvlyPipeConfig *ovlpipecfg;
    UInt32           instCnt;
    DispApp_InstObj *instObj;
    Int32 retVal = FVID2_SOK;

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

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
            break;
        }
    }
    return retVal;
}

static void DispApp_changePattern(DispApp_InstObj *instObj,
                                  DispApp_rtParamPattern *rtParamPattern,
                                  UInt32 patternNum)
{
    switch(patternNum)
    {
        case 0:
            /* Display in centre of the LCD */
            rtParamPattern->outWidthDecCnt  = 2;
            rtParamPattern->outHeightDecCnt = 2;
            rtParamPattern->posxIncCnt      = 1;
            rtParamPattern->posyIncCnt      = 1;
        break;
        case 1:
            /* Display in first quadrant of LCD */
            rtParamPattern->outWidthDecCnt  = 2;
            rtParamPattern->outHeightDecCnt = 1;
            rtParamPattern->posxIncCnt      = 0;
            rtParamPattern->posyIncCnt      = 0;
            break;
        case 2:
            /* Display in second quadrant of LCD */
            rtParamPattern->outWidthDecCnt  = 2;
            rtParamPattern->outHeightDecCnt = 1;
            rtParamPattern->posxIncCnt      = 2;
            rtParamPattern->posyIncCnt      = 0;
        break;
        case 3:
            /* Display in third quadrant of LCD */
            rtParamPattern->outWidthDecCnt  = 2;
            rtParamPattern->outHeightDecCnt = 1;
            rtParamPattern->posxIncCnt      = 2;
            rtParamPattern->posyIncCnt      = 1;
        break;
        default:
            /* Display in forth quadrant of LCD */
            rtParamPattern->outWidthDecCnt  = 2;
            rtParamPattern->outHeightDecCnt = 1;
            rtParamPattern->posxIncCnt      = 0;
            rtParamPattern->posyIncCnt      = 1;
        break;
    }
    rtParamPattern->inWidthDecCnt   = 0;
    rtParamPattern->inHeightDecCnt  = 0;
    rtParamPattern->currentFrameCnt = 0;
    /* Display till height reaches 1/3 of original value */
    rtParamPattern->rtPramDisplayFrameCnt =
        ((instObj->dssPrms.inFmt.height * DISP_APP_MAX_FRAMES_PER_HANDLE) /
         (3 * rtParamPattern->outHeightDecCnt));
    rtParamPattern->patternNum = patternNum;
}

static Bool DispApp_isScalingRatioSupported(DispApp_InstObj *instObj,
                                            Vps_DssDispcRtParams *rtParam)
{
    Bool retVal = TRUE;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
    float supportedScalingRatio;
    float currentScalingRatio;
    Vps_DctrlConfig *dctrlCfg;
    Fvid2_ModeInfo  *mInfo;

    /* Check for max scaling factor. There is a limitation with scaling in
     * TDA2xx/TDA2Ex/AM571x/AM572x/DRA75x/AM574x platforms. Max horizontal scaling
     * ratio supported is the ratio of (the dss functional clock) / (pixel clk)
     * for both up and down scaling.
     */
    dctrlCfg = &instObj->appObj->dctrlCfg;
    mInfo    = &dctrlCfg->vencInfo.modeInfo[0U].mInfo;
    supportedScalingRatio = (float)DISP_APP_DSS_FUNC_CLK/mInfo->pixelClock;

    if (rtParam->inWidth >= rtParam->outWidth)
    {
        /* Down scaling ratio. */
        currentScalingRatio = (float)rtParam->inWidth / rtParam->outWidth;
    }
    else
    {
        /* Up scaling ratio. */
        currentScalingRatio = (float)rtParam->outWidth / rtParam->inWidth;
    }

    if (currentScalingRatio > supportedScalingRatio)
    {
        /* scaling ratio specified in rtParam is not supported. */
        retVal = FALSE;
    }
#endif
    return retVal;
}

static void DispApp_updateRtParam(DispApp_InstObj *instObj,
                                  Vps_DssDispcRtParams *rtParam)
{
    UInt32           displayNextPattern = 0;

    instObj->rtParamPattern.currentFrameCnt++;
    if(instObj->rtParamPattern.currentFrameCnt <
            instObj->rtParamPattern.rtPramDisplayFrameCnt)
    {
        /* Update the RT Params based on pattern we are displaying. */
        rtParam->inWidth   -= instObj->rtParamPattern.inWidthDecCnt;
        rtParam->inHeight  -= instObj->rtParamPattern.inHeightDecCnt;
        rtParam->outWidth  -= instObj->rtParamPattern.outWidthDecCnt;
        rtParam->outHeight -= instObj->rtParamPattern.outHeightDecCnt;
        rtParam->posX += instObj->rtParamPattern.posxIncCnt;
        rtParam->posY += instObj->rtParamPattern.posyIncCnt;
        rtParam->scEnable = TRUE;
        rtParam->pitch[0] = instObj->dssPrms.inFmt.pitch[0];
        /* Check if the scaling ratio is supported */
        if (TRUE != DispApp_isScalingRatioSupported(instObj, rtParam))
        {
            displayNextPattern = 1;
        }
    }
    else
    {
        /* We have reached the frame count for current pattern.
         * display Next pattern.
         */
        displayNextPattern = 1;
    }

    if (displayNextPattern == 1)
    {
        /* Reset the rtParams to default value. */
        rtParam->inWidth   = instObj->dssPrms.inFmt.width;
        rtParam->inHeight  = instObj->dssPrms.inFmt.height;
        rtParam->outWidth  = instObj->dssPrms.tarWidth;
        rtParam->outHeight = instObj->dssPrms.tarHeight;
        rtParam->posX      = instObj->dssPrms.posX;
        rtParam->posY      = instObj->dssPrms.posY;
        rtParam->scEnable = TRUE;
        rtParam->pitch[0] = instObj->dssPrms.inFmt.pitch[0];
        if((instObj->rtParamPattern.currentFrameCnt) >
                (instObj->rtParamPattern.rtPramDisplayFrameCnt +
                 DISP_APP_MAX_FRAMES_PER_HANDLE))
        {
            /* Display Next pattern. Currently we have 5 patterns in the test */
            DispApp_changePattern(instObj, &instObj->rtParamPattern,
                ((instObj->rtParamPattern.patternNum + 1) % 5));
        }
    }
}

/**
 *  DispApp_cbFxn
 *  \brief Driver callback function.
 */
static Int32 DispApp_cbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32            retVal  = FVID2_SOK;
    DispApp_InstObj *instObj = (DispApp_InstObj *) appData;
    Fvid2_FrameList  frmList;
    Vps_DssDispcRtParams *rtParam = NULL;

    retVal = Fvid2_dequeue(
        instObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        rtParam = frmList.frames[0U]->perFrameCfg;
        if (rtParam != NULL)
        {
            DispApp_updateRtParam(instObj, rtParam);
        }
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Queue Failed!!!\r\n");
        }
    }

    instObj->appObj->callBackCount++;

    return (retVal);
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
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                bufInfo = &Yuyv422InterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuyv422FieldsMerged;
            }
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

        case FVID2_DF_BGR24_888:
            bufInfo = &BGR24888FieldsMerged;

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
                    bufInfo->bgrBufAddr[bCnt] = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 3u)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 3u);
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
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          "Freeing YUYV422 Field Separated Buffer...\r\n");

                bufInfo = &Yuyv422InterlacedFieldsSep;
            }
            else
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          "Freeing YUYV422 Field Merged Buffer...\r\n");

                bufInfo = &Yuyv422FieldsMerged;
            }
            break;

        case FVID2_DF_BGR24_888:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing BGR24 Field Merged Buffer...\r\n");
            bufInfo = &BGR24888FieldsMerged;

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
            if ((FVID2_SF_INTERLACED == scanFmt) && (FALSE == fieldsMerged))
            {
                bufInfo = &Yuyv422InterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuyv422FieldsMerged;
            }
            break;

        case FVID2_DF_BGR24_888:

            bufInfo = &BGR24888FieldsMerged;
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
                      "Invalid format: %d\r\n", dataFmt);
            bufInfo = NULL;
            break;
    }
    return (bufInfo);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 DispApp_allocAndQueueFrames(const DispApp_Obj *appObj,
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

        if(appObj->testPrms.isRtParamUpdateTest == TRUE)
        {
            /* Initiate RT Param object and assign to each frame */
            instObj->rtParam[frmId].inWidth   = instObj->dssPrms.inFmt.width;
            instObj->rtParam[frmId].inHeight  = instObj->dssPrms.inFmt.height;
            instObj->rtParam[frmId].outWidth  = instObj->dssPrms.tarWidth;
            instObj->rtParam[frmId].outHeight = instObj->dssPrms.tarHeight;
            instObj->rtParam[frmId].posX      = instObj->dssPrms.posX;
            instObj->rtParam[frmId].posY      = instObj->dssPrms.posY;
            instObj->rtParam[frmId].pitch[0]  = instObj->dssPrms.inFmt.pitch[0];
            instObj->rtParam[frmId].scEnable  = TRUE;
            DispApp_changePattern(instObj, &instObj->rtParamPattern, 0);
            frm[frmId].perFrameCfg = &instObj->rtParam[frmId];
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
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
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
 *  DispApp_initParams
 *  Initialize the global variables and frame pointers.
 */
static void DispApp_initParams(DispApp_Obj *appObj)
{
    UInt32 instCnt;
    Vps_DispDssParams *dssPrms;
    DispApp_InstObj   *instObj;

    appObj->maxWidth  = DISP_APP_BUF_WIDTH;
    appObj->maxHeight = DISP_APP_BUF_HEIGHT;

    appObj->totalFldCount = 0U;
    appObj->totalCpuLoad  = 0U;
    appObj->cpuLoadCount  = 0U;
    appObj->callBackCount = 0U;
    appObj->lcdCtrlhdl    = NULL;

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        instObj->inDataFmt = appObj->testPrms.inDataFmt[instCnt];

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

        instObj->inWidth      = appObj->testPrms.inWidth[instCnt];
        instObj->inHeight     = appObj->testPrms.inHeight[instCnt];
        instObj->isFieldMerge = appObj->testPrms.isFieldMerge[instCnt];
        instObj->inScanFormat = appObj->testPrms.inScanFormat[instCnt];
        instObj->posx         = appObj->testPrms.posx[instCnt];
        instObj->posy         = appObj->testPrms.posy[instCnt];
        instObj->instId       = appObj->testPrms.instId[instCnt];
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
    }

    return;
}

static void DispApp_printStatistics(DispApp_Obj *appObj,
                                    UInt32       execTimeInMsecs)
{
    UInt32           instCnt;
    DispApp_InstObj *instObj;

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
    GT_1trace(BspAppTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              appObj->totalCpuLoad / appObj->cpuLoadCount);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Print the driver status */
        BspUtils_appPrintDispStatus(
            instObj->drvHandle,
            instObj->instId,
            execTimeInMsecs);
    }

    /* Print the Display Controller error status */
    BspUtils_appPrintDctrlStatus(
        appObj->dctrlHandle);

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return;
}

static void DispApp_configureLCD(DispApp_Obj *appObj)
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

/* This will configure Venc with LCD timings and enable the color bar */
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)

    *(UInt32 *) 0x4810a000 = 0x4003B023;
    *(UInt32 *) 0x4810a004 = 0x1FD01E24;
    *(UInt32 *) 0x4810a008 = 0x02DC020C;
    *(UInt32 *) 0x4810a00C = 0x00DA004A;
    *(UInt32 *) 0x4810a010 = 0x020C1E6C;
    *(UInt32 *) 0x4810a014 = 0x02001F88;
    *(UInt32 *) 0x4810a018 = 0x00200000;
    *(UInt32 *) 0x4810a01C = 0x1B6C0C77;
    *(UInt32 *) 0x4810a020 = 0x1C0C0C30;
    *(UInt32 *) 0x4810a024 = 0x1C0C0C30;
    *(UInt32 *) 0x4810a028 = 0x842EE672;
    *(UInt32 *) 0x4810a02C = 0x3F000018;
    *(UInt32 *) 0x4810a030 = 0xD0320100;
    *(UInt32 *) 0x4810a034 = 0x000002E8;
    *(UInt32 *) 0x4810a038 = 0x000C39E7;
    *(UInt32 *) 0x4810a03C = 0xD0320100;
    *(UInt32 *) 0x4810a040 = 0x0001A64B;
    *(UInt32 *) 0x4810a044 = 0x002D0000;
    *(UInt32 *) 0x4810a048 = 0x05000000;
    *(UInt32 *) 0x4810a04C = 0x00003000;
    *(UInt32 *) 0x4810a050 = 0x00000000;
    *(UInt32 *) 0x4810a054 = 0xD0320100;
    *(UInt32 *) 0x4810a058 = 0x0001A64B;
    *(UInt32 *) 0x4810a05C = 0x002D0000;
    *(UInt32 *) 0x4810a060 = 0x05000000;
    *(UInt32 *) 0x4810a064 = 0x00003000;
    *(UInt32 *) 0x4810a068 = 0x00000000;
    *(UInt32 *) 0x4810a06C = 0x00000000;
    *(UInt32 *) 0x4810a070 = 0x00000000;
    *(UInt32 *) 0x4810a074 = 0x00000000;

#endif
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

static Int32 DispApp_configureEncoder(DispApp_Obj *appObj, UInt32 encInst)
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
        appObj->testPrms.boardMode);
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
            appObj->testPrms.encDrvId[encInst],
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

    if (appObj->testPrms.encDrvId[encInst] == FVID2_VID_ENC_SII9022A_DRV)
    {
        if (FVID2_SOK == retVal)
        {
            retVal = Fvid2_control(
                appObj->hdmiHandle,
                IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID,
                &hdmiId,
                NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(
                    BspAppTrace, GT_ERR,
                    APP_NAME
                    ": Error: Could not get detailed chip ID!!\r\n");
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
    }

    if (FVID2_SOK == retVal)
    {
        BspVidEncConfigParams_init(&modePrms);
        modePrms.standard        = appObj->testPrms.standard[encInst];
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

static Int32 DispApp_deConfigureEncoder(DispApp_Obj *appObj, UInt32 encInst)
{
    Int32 retVal = FVID2_SOK;

    if (NULL != appObj->hdmiHandle)
    {
        retVal = Fvid2_stop(appObj->hdmiHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Error: Encoder stop failed!!\r\n");
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
 *  DispApp_getTestId
 *  Return the test ID to run.
 */
static Int32 DispApp_getTestId(DispApp_Obj *appObj)
{
    UInt32       testCnt;
    static Int32 testIdx = 0;
    Int32 testId = 0;
    Int32        retVal = BSP_SOK;
    static UInt32 timeoutVal = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

    if (TRUE != appObj->enableAutoRun)
    {
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
        GT_0trace(BspAppTrace, GT_INFO,
                "--------------------------------------\r\n");
        GT_0trace(BspAppTrace, GT_INFO,
                "Select test to run as per below table:\r\n");
        GT_0trace(BspAppTrace, GT_INFO,
                "--------------------------------------\r\n");
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
        for (testCnt = 0; testCnt < DISP_APP_NUM_TESTS; testCnt++)
        {
            GT_2trace(BspAppTrace, GT_INFO,
                    "%3d: %s\r\n", gDispAppTestPrms[testCnt].testCaseId,
                                    gDispAppTestPrms[testCnt].testDescStr);
        }
        GT_2trace(BspAppTrace, GT_INFO,
                "%3d: %s\r\n", DISP_APP_AUTORUN_OPT, "Auto Run\r\n");
        GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", DISP_APP_EXIT_OPT);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
        GT_0trace(BspAppTrace, GT_INFO,
            "Enter Test to Run (in UART console): \r\n");
    }

    if (TRUE == appObj->enableAutoRun)
    {
        testIdx++;
        if (testIdx < DISP_APP_NUM_TESTS)
        {
            GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                gDispAppTestPrms[testIdx].testCaseId,
                gDispAppTestPrms[testIdx].testDescStr);
        }
    }
    else
    {
        while (1U)
        {
            retVal = BspUtils_uartGetNum(&testId, timeoutVal);
            if (retVal == BSP_ETIMEOUT)
            {
                /* No user input within the timeout */
                appObj->enableAutoRun = (UInt32) TRUE;
                testIdx = 0;
                GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                    gDispAppTestPrms[testIdx].testCaseId,
                    gDispAppTestPrms[testIdx].testDescStr);
                break;
            }
            else
            {
                timeoutVal = BSP_UTILS_UART_RX_WAIT_FOREVER;
            }
            testIdx = DispApp_getTestIndex(testId);
            if ((testIdx >= 0) && (testIdx < DISP_APP_NUM_TESTS))
            {
                GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
                break;
            }
            if (DISP_APP_AUTORUN_OPT == testId)
            {
                appObj->enableAutoRun = (UInt32) TRUE;
                testIdx = 0;
                GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                    gDispAppTestPrms[testIdx].testCaseId,
                    gDispAppTestPrms[testIdx].testDescStr);
                break;
            }
            else if (DISP_APP_EXIT_OPT == testId)
            {
                testIdx = DISP_APP_EXIT_OPT;
                break;
            }
            GT_0trace(BspAppTrace, GT_INFO, "Invalid Test ID. Enter Agian!!\r\n");
        }
    }

    return (testIdx);
}

static Int32 DispApp_getTestIndex(Int32 testId)
{
    Int32  testIdx;
    UInt32 testIdFound = FALSE;
    for (testIdx = 0; testIdx <DISP_APP_NUM_TESTS; testIdx++)
    {
        if(testId == gDispAppTestPrms[testIdx].testCaseId)
        {
            testIdFound = TRUE;
            break;
        }
    }
    if(testIdFound == FALSE)
    {
        testIdx = -1;
    }
    return testIdx;
}
