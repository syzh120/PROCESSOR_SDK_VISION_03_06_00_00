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
 *  \file DisplayDssWb_main.c
 *
 *  \brief DSS Display writeback sample application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <DisplayDssWb_main.h>

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

static void DispWbApp_createTsk(void);
static void DispWbApp_tskMain(UArg arg0, UArg arg1);

static void DispWbApp_init(DispWbApp_Obj *appObj);
static void DispWbApp_deInit(DispWbApp_Obj *appObj);

static void DispWbApp_runTest(DispWbApp_Obj              *appObj,
                              const DispWbApp_TestParams *testPrms);

static void DispWbApp_create(DispWbApp_Obj *appObj);
static void DispWbApp_delete(DispWbApp_Obj *appObj);
static void DispWbApp_wbCreate(DispWbApp_Obj *appObj);
static void DispWbApp_WbDelete(DispWbApp_Obj *appObj);
static Int32 DispWbApp_configDctrl(DispWbApp_Obj *appObj);

static Int32 DispWbApp_configureVideoPllAndClkSrc(DispWbApp_Obj *appObj,
                                                  UInt32 pixelClk);
static Int32 DispWbApp_configDctrlPipe(DispWbApp_Obj *appObj);

static Int32 DispWbApp_allocAndQueueFrames(const DispWbApp_Obj *appObj,
                                           DispWbApp_InstObj   *instObj);
static Int32 DispWbApp_wbAllocAndQueueFrames(const DispWbApp_Obj *appObj,
                                             DispWbApp_InstObj   *instObj);
static void DispWbApp_initParams(DispWbApp_Obj *appObj);
static void DispWbApp_printStatistics(DispWbApp_Obj *appObj,
                                      UInt32         execTimeInMsecs);
static Int32 DispWbApp_getTestId(DispWbApp_Obj *appObj);

static void DispWbApp_configureLCD(DispWbApp_Obj *appObj);
static void DispWbApp_turnoffLCD(DispWbApp_Obj *appObj);

static Int32 DispWbApp_configureOffChipHdmi(DispWbApp_Obj *appObj,
                                            UInt32         encInst);
static Int32 DispWbApp_deConfigureOffChipHdmi(DispWbApp_Obj *appObj,
                                              UInt32         encInst);

static Int32 DispWbApp_LoadBuf(DispWbApp_Obj              *appObj,
                               const DispWbApp_LoadBufCfg *cfg);
static Int32 DispWbApp_FreeBuf(DispWbApp_Obj              *appObj,
                               const DispWbApp_LoadBufCfg *cfg);
static DispWbApp_BufInfo *DispWbApp_GetBufInfo(
    const DispWbApp_Obj *appObj,
    UInt32               dataFmt,
    UInt32               scanFmt,
    UInt32
    fieldsMerged,
    UInt32               pitch);
static Int32 DispWbApp_updateFieldFromDetectedLcd(
    DispWbApp_Obj *appObj, UInt32 *fieldAddr, DispWbApp_LcdFieldType fieldType);
static Int32 DispWbApp_getTestIndex(Int32 testId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

UInt32                   currentFrameBytes = 0;
UInt32                   numWbFrames       = 0;
UInt32                   wbFrameNo         = 0;
UInt8                   *wbBufAddr;
UInt8                   *wbBufAllocatedAddr;
UInt8                   *wbBufDisplayAddr;
Bool                     wbBufDisplay;

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else

#pragma DATA_ALIGN(gDispAppTskStackMain, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gDispAppTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8             gDispAppTskStackMain[DISP_APP_TSK_STACK_MAIN];

/* Test application object */
static DispWbApp_Obj     gDispAppObj;

/**
 *  \brief Used for YUYV422 interleaved progressive frame format or interlaced
 *  frame format with fields merged. => 800x480 input
 */
static DispWbApp_BufInfo Yuyv422FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for the YUYV422 interleaved interlaced frame format with fields
 *  in seperate planes.. => 800x480 input
 */
static DispWbApp_BufInfo Yuyv422InterlacedFieldsSep = {NULL, 0u};
/**
 *  \brief Used for BGR888 24-bit progressive frame format with fields merged.
 */
static DispWbApp_BufInfo BGR24888FieldsMerged = {NULL, 0u};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
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

/*
 * Application main
 */
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
    DispWbApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void DispWbApp_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = DISP_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gDispAppTskStackMain;
    tskPrms.stackSize     = sizeof (gDispAppTskStackMain);
    tskPrms.arg0          = (UArg) & gDispAppObj;
    gDispAppObj.tskHandle = Task_create(DispWbApp_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gDispAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gDispAppObj.tskHandle, APP_NAME);

    return;
}

/*
 * Test task main
 */
static void DispWbApp_tskMain(UArg arg0, UArg arg1)
{
    Int32                       testId;
    Bsp_BoardId                 boardId;
    DispWbApp_Obj              *appObj = (DispWbApp_Obj *) arg0;
    const DispWbApp_TestParams *testPrms;
    BspUtils_MemHeapStatus      startHeapStat, startHeapStat1;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    BspUtils_memGetHeapStat(&startHeapStat);
    DispWbApp_init(appObj);

    appObj->enableAutoRun = (UInt32) FALSE;
    boardId = Bsp_boardGetId();
    while (1U)
    {
        /* Get the TestId */
        testId = DispWbApp_getTestId(appObj);
        if ((testId >= 0) && (testId < DISP_WB_APP_NUM_TESTS))
        {
            testPrms = &gDispWbAppTestPrms[testId];
            if (testPrms->boardId & boardId)
            {
                BspUtils_memGetHeapStat(&startHeapStat1);

                DispWbApp_runTest(appObj, testPrms);

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

    DispWbApp_deInit(appObj);

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

static void DispWbApp_init(DispWbApp_Obj *appObj)
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
            DispWbApp_configureVideoPllAndClkSrc(appObj, defPixelClk);
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
             (sizeof (gDispDssLoadBufCfg) / sizeof (DispWbApp_LoadBufCfg));
             bufCfgId++)
        {
            retVal = DispWbApp_LoadBuf(appObj, &gDispDssLoadBufCfg[bufCfgId]);
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
                  APP_NAME ": DispWbApp_init() - DONE !!!\r\n");
    }

    return;
}

static void DispWbApp_deInit(DispWbApp_Obj *appObj)
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
             (sizeof (gDispDssLoadBufCfg) / sizeof (DispWbApp_LoadBufCfg));
             bufCfgId++)
        {
            retVal = DispWbApp_FreeBuf(appObj, &gDispDssLoadBufCfg[bufCfgId]);
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
                  APP_NAME ": DispWbApp_deInit() - DONE !!!\r\n");
    }

    return;
}

static Int32 DispWbApp_configVidPipeFromWbConf(DispWbApp_Obj *appObj)
{
    Vps_DispDssParams *dssPrms = NULL;
    UInt32 instCnt;
    DispWbApp_InstObj *wbInstObj  = NULL;
    DispWbApp_InstObj *vidInstObj = NULL;
    UInt32 numFrames, frmCnt;
    Fvid2_FrameList    frmList;
    DispWbApp_BufInfo *bufInfo;
    Int32 retVal = FVID2_SOK;
    Vps_DctrlConfig   *dctrlCfg;
    Fvid2_ModeInfo    *mInfo;

    dctrlCfg = &appObj->dctrlCfg;
    mInfo    = &dctrlCfg->vencInfo.modeInfo[0U].mInfo;

    vidInstObj = &appObj->instObj[0];
    dssPrms    = &vidInstObj->dssPrms;
    bufInfo    = DispWbApp_GetBufInfo(appObj, vidInstObj->inDataFmt,
                                      vidInstObj->inScanFormat,
                                      vidInstObj->isFieldMerge,
                                      vidInstObj->pitch[0]);
    GT_assert(BspAppTrace, NULL != bufInfo);

    numFrames = bufInfo->totalBufSize / bufInfo->bufSize;

    instCnt   = appObj->testPrms.numHandles;
    wbInstObj = &appObj->instObj[instCnt];

    dssPrms->inFmt.width           = wbInstObj->wbWidth;
    dssPrms->inFmt.height          = wbInstObj->wbHeight;
    dssPrms->inFmt.pitch[0U]       = wbInstObj->pitch[0U];
    dssPrms->inFmt.pitch[1U]       = wbInstObj->pitch[1U];
    dssPrms->inFmt.pitch[2U]       = wbInstObj->pitch[2U];
    dssPrms->inFmt.fieldMerged[0U] = wbInstObj->wbFieldMerge;
    dssPrms->inFmt.fieldMerged[1U] = FALSE;
    dssPrms->inFmt.fieldMerged[2U] = FALSE;
    dssPrms->inFmt.dataFormat      = wbInstObj->wbDataFmt;
    dssPrms->inFmt.scanFormat      = wbInstObj->wbScanFormat;
    dssPrms->inFmt.bpp      = FVID2_BPP_BITS16;
    dssPrms->inFmt.reserved = NULL;
    dssPrms->tarWidth       = wbInstObj->wbWidth;
    dssPrms->tarHeight      = wbInstObj->wbHeight;
    dssPrms->posX           = 0U;
    dssPrms->posY           = 0U;
    if (dssPrms->tarHeight > mInfo->height)
    {
        dssPrms->tarHeight = mInfo->height;
        dssPrms->vidCfg->pipeCfg.scEnable = TRUE;
    }
    if (dssPrms->tarWidth > mInfo->width)
    {
        dssPrms->tarWidth = mInfo->width;
        dssPrms->vidCfg->pipeCfg.scEnable = TRUE;
    }
    retVal = Fvid2_control(
        vidInstObj->drvHandle,
        IOCTL_VPS_DISP_SET_DSS_PARAMS,
        &vidInstObj->dssPrms,
        NULL);

    wbBufDisplay     = TRUE;
    wbBufDisplayAddr = wbBufAllocatedAddr;

    /* dequeue all buffers from vid pipe driver instance */
    for (frmCnt = 0; frmCnt < numFrames; frmCnt++)
    {
        retVal = Fvid2_dequeue(
            vidInstObj->drvHandle,
            &frmList,
            0U,
            FVID2_TIMEOUT_NONE);
        /* Set number of frame in frame list */
        frmList.frames[0U]->addr[0][0] = wbBufDisplayAddr;
        frmList.frames[0U]->addr[1][0] = wbBufDisplayAddr + currentFrameBytes /
                                         2;
        frmList.numFrames = 1U;

        retVal = Fvid2_queue(vidInstObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Queue Failed!!!\r\n");
            break;
        }
    }
    if (retVal == FVID2_SOK)
    {
        Fvid2_start(vidInstObj->drvHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Start Failed!!!\r\n");
        }
    }

    return retVal;
}

/**
 *  DispWbApp_runTest
 *  Display test function.
 */
static void DispWbApp_runTest(DispWbApp_Obj              *appObj,
                              const DispWbApp_TestParams *testPrms)
{
    Int32  retVal = FVID2_SOK;
    Int32  instCnt;
    UInt32 displayTime, curTime, prevTime;
    UInt32 loopCount, prevFldCount, curFldCount, fldCount;
    DispWbApp_InstObj *instObj = NULL;

    wbBufDisplay = FALSE;
    loopCount    = 0;
    curTime      = prevTime = curFldCount = prevFldCount = 0;
    BspUtils_memcpy(&appObj->testPrms, testPrms, sizeof (appObj->testPrms));

    /* Print test case information */
    GT_3trace(BspAppTrace, GT_INFO,
              APP_NAME ": HANDLES %d: RUN COUNT %d: INPUT:%d !!!\r\n",
              appObj->testPrms.numHandles,
              appObj->testPrms.runCount,
              appObj->testPrms.inDataFmt[0]);
    /* Initialize App Object */
    DispWbApp_initParams(appObj);
    /* Create driver */
    DispWbApp_create(appObj);
    /* Create Write back driver */
    DispWbApp_wbCreate(appObj);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Starting display ... !!!\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Display in progress ... DO NOT HALT !!!\r\n");

    appObj->startTime = BspOsal_getCurTimeInMsec();

    /* Start the load calculation */
    BspUtils_prfLoadCalcStart();

    /* Start driver */
    for (instCnt = 0U;
         instCnt <
         (appObj->testPrms.numHandles + appObj->testPrms.numCaptHandles);
         instCnt++)
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

        /* Stop driver First stop wb pipe driver then vid pipe driver */
        for (instCnt =
                 (appObj->testPrms.numHandles +
                  appObj->testPrms.numCaptHandles - 1);
             instCnt >= 0; instCnt--)
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

    if (retVal == FVID2_SOK)
    {
        UInt32 dispFramCnt;
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Displaying written back frames.\r\n");
        BspOsal_sleep(1000);
        retVal = DispWbApp_configVidPipeFromWbConf(appObj);
        for (dispFramCnt = 0; dispFramCnt < numWbFrames; dispFramCnt++)
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Written back frames No %d\r\n",
                      dispFramCnt);
            BspOsal_sleep(1000);
            wbBufDisplayAddr += currentFrameBytes;
        }
        Fvid2_stop((&appObj->instObj[0])->drvHandle, NULL);
    }
    if (FVID2_SOK == retVal)
    {
        /* Stop the load calculation */
        BspUtils_prfLoadCalcStop();

        displayTime = (BspOsal_getCurTimeInMsec() - appObj->startTime);

        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Stopping display ... DONE !!!\r\n");

        DispWbApp_printStatistics(appObj, displayTime);

        /* Delete driver */
        DispWbApp_delete(appObj);
        DispWbApp_WbDelete(appObj);

        /* Print the load */
        BspUtils_prfLoadPrintAll(TRUE);
        /* Reset the load */
        BspUtils_prfLoadCalcReset();
    }

    return;
}

static void DispWbApp_create(DispWbApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt, encInst;
    DispWbApp_InstObj    *instObj;
    Bsp_LcdCtrlPanelInfo *lcdPanelInfo;

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
            (appObj->testPrms.encDrvId[encInst] == FVID2_VID_ENC_SII9022A_DRV))
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
                DispWbApp_configureLCD(appObj);
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
        else if (appObj->testPrms.encDrvId[encInst] ==
                 FVID2_VID_ENC_SII9022A_DRV)
        {
            /* Configure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = DispWbApp_configureOffChipHdmi(appObj, encInst);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(
                        BspAppTrace, GT_ERR,
                        APP_NAME
                        ": Configuring Off-Chip HDMI Failed !!!\r\n");
                }
            }
        }
    }

    DispWbApp_configDctrl(appObj);

    for (encInst = 0; encInst < appObj->testPrms.numEnc; encInst++)
    {
        GT_assert(BspAppTrace, appObj->testPrms.numEnc < VPS_DISP_ENC_INST_MAX);
        if ((FVID2_SOK == retVal) &&
            (appObj->testPrms.encDrvId[encInst] ==
             FVID2_VID_ENC_SII9022A_DRV))
        {
            retVal = Fvid2_start(appObj->hdmiHandle, NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Error: Off-chip HDMI start failed!!\r\n");
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
            retVal = DispWbApp_allocAndQueueFrames(appObj, instObj);
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

static void DispWbApp_wbCreate(DispWbApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    DispWbApp_InstObj  *instObj;
    Vps_CaptDssWbParams dssWbPrms;

    for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[appObj->testPrms.numHandles + instCnt];
        instObj->drvHandle = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            instObj->captInstId,
            &instObj->captCreatePrms,
            &instObj->captCreateStatus,
            &instObj->cbPrms);
        if ((NULL == instObj->drvHandle) ||
            (instObj->captCreateStatus.retVal != FVID2_SOK))
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Create Failed!!!\r\n");
            retVal = instObj->captCreateStatus.retVal;
        }

        /* If the width/height values are to be based on LCD width/Height,
         * Update them here as LCD is detected by this time.
         * If its not based on LCD width/height, The function
         * DispWbApp_updateFieldFromDetectedLcd will not alter the value.
         * Its kept to value initialized in DispWbApp_initParams.
         */
        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbInSourceWidth,
                                             DISPWBAPP_FIELD_LCD_WIDTH);
        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbInSourceHeight,
                                             DISPWBAPP_FIELD_LCD_HEIGHT);

        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbInWidth,
                                             DISPWBAPP_FIELD_LCD_WIDTH);
        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbInHeight,
                                             DISPWBAPP_FIELD_LCD_HEIGHT);

        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbWidth,
                                             DISPWBAPP_FIELD_LCD_WIDTH);
        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbHeight,
                                             DISPWBAPP_FIELD_LCD_HEIGHT);

        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbPosx,
                                             DISPWBAPP_FIELD_LCD_WIDTH);
        DispWbApp_updateFieldFromDetectedLcd(appObj, &instObj->wbPosy,
                                             DISPWBAPP_FIELD_LCD_HEIGHT);

        /* Update the pitch here after getting actual wbWidth */
        /* Pitch should not be increased to allign to word boundry etc.
         * as writeback pipe doesnot support pitch. */
        if (Fvid2_isDataFmtSemiPlanar(instObj->wbDataFmt))
        {
            instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX]    = instObj->wbWidth;
            instObj->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                instObj->pitch[FVID2_YUV_SP_Y_ADDR_IDX];
        }
        else if (Fvid2_isDataFmtYuv422I(instObj->wbDataFmt))
        {
            instObj->pitch[FVID2_YUV_INT_ADDR_IDX] = instObj->wbWidth * 2U;
        }
        else if (Fvid2_isDataFmtRgb16bit(instObj->wbDataFmt))
        {
            instObj->pitch[FVID2_YUV_INT_ADDR_IDX] = instObj->wbWidth * 2U;
        }
        else if (Fvid2_isDataFmtRgb24bit(instObj->wbDataFmt))
        {
            instObj->pitch[FVID2_RGB_ADDR_IDX] = instObj->wbWidth * 3U;
        }
        else if (Fvid2_isDataFmtRgb32bit(instObj->wbDataFmt))
        {
            instObj->pitch[FVID2_RGB_ADDR_IDX] = instObj->wbWidth * 4U;
        }
        VpsCaptDssWbParams_init(&dssWbPrms);

        dssWbPrms.inFmt.dataFormat = FVID2_DF_BGR24_888;
        dssWbPrms.inFmt.width      = instObj->wbInSourceWidth;
        dssWbPrms.inFmt.height     = instObj->wbInSourceHeight;
        dssWbPrms.outStreamInfo[0].outFmt.chNum          = 0;
        dssWbPrms.outStreamInfo[0].outFmt.height         = instObj->wbHeight;
        dssWbPrms.outStreamInfo[0].outFmt.width          = instObj->wbWidth;
        dssWbPrms.outStreamInfo[0].outFmt.pitch[0]       = instObj->pitch[0];
        dssWbPrms.outStreamInfo[0].outFmt.dataFormat     = instObj->wbDataFmt;
        dssWbPrms.outStreamInfo[0].outFmt.fieldMerged[0] = TRUE;
        dssWbPrms.outStreamInfo[0].outFmt.scanFormat     =
            instObj->wbScanFormat;
        dssWbPrms.outStreamInfo[0].advDmaCfg        = NULL;
        dssWbPrms.outStreamInfo[0].scEnable         = TRUE;
        dssWbPrms.outStreamInfo[0].cscFullRngEnable = TRUE;
        dssWbPrms.inCropCfg.cropHeight = instObj->wbInHeight;
        dssWbPrms.inCropCfg.cropWidth  = instObj->wbInWidth;
        dssWbPrms.inCropCfg.cropStartX = instObj->wbPosx;
        dssWbPrms.inCropCfg.cropStartY = instObj->wbPosy;
        if ((dssWbPrms.inFmt.width != dssWbPrms.inCropCfg.cropWidth) ||
            (dssWbPrms.inFmt.height != dssWbPrms.inCropCfg.cropHeight))
        {
            dssWbPrms.outStreamInfo[0].cropEnable = TRUE;
        }
        else
        {
            dssWbPrms.outStreamInfo[0].cropEnable = FALSE;
        }
        dssWbPrms.inNode = VPS_DSS_DISPC_WB_IN_NODE_LCD1;
        if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)
        {
            dssWbPrms.inNode = VPS_DSS_DISPC_WB_IN_NODE_LCD3;
        }
        if (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_HDMI)
        {
            dssWbPrms.inNode = VPS_DSS_DISPC_WB_IN_NODE_TV;
        }
        dssWbPrms.wbMode = VPS_DSS_DISPC_WB_CAPT;

        if (FVID2_SOK == retVal)
        {
            retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_VPS_CAPT_SET_DSSWB_PARAMS,
                &dssWbPrms,
                NULL);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": DSS WB Set Params IOCTL Failed!!!\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            retVal = DispWbApp_wbAllocAndQueueFrames(appObj, instObj);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Alloc and Queue Failed!!!\r\n");
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

static Int32 DispWbApp_configureVideoPllAndClkSrc(DispWbApp_Obj *appObj,
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

static void DispWbApp_delete(DispWbApp_Obj *appObj)
{
    Int32              retVal;
    UInt32             instCnt, encInst, sdVencEnable;
    DispWbApp_InstObj *instObj;
    Fvid2_FrameList    frmList;
    Vps_DctrlConfig   *dctrlCfg;

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
                DispWbApp_turnoffLCD(appObj);
            }
        }
        else if (appObj->testPrms.encDrvId[encInst] ==
                 FVID2_VID_ENC_SII9022A_DRV)
        {
            /* DeConfigure Video Encoder only if platform is EVM */
            if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
            {
                retVal = DispWbApp_deConfigureOffChipHdmi(appObj, encInst);
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

static void DispWbApp_WbDelete(DispWbApp_Obj *appObj)
{
    Int32              retVal = FVID2_SOK;
    UInt32             instCnt, bytesWritten;
    DispWbApp_InstObj *instObj;
    Fvid2_FrameList    frmList;
    Fvid2_Frame       *frm;
    Char fileStr[30U];
    Char fileNameString[100U];

    for (instCnt = 0U; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[appObj->testPrms.numHandles + instCnt];

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

        /* Delete the allocated frames */
        frm = &instObj->wbFrames[0];
        if (frm[0U].addr[0U][0U] != NULL)
        {
            snprintf(fileStr, 30U, "DispWbOption%uInst%u",
                     (unsigned int) appObj->testPrms.testId,
                     (unsigned int) instObj->captInstId);
            BspUtils_appGetFileName(fileNameString,
                                    sizeof (fileNameString),
                                    fileStr,
                                    instObj->wbDataFmt,
                                    instObj->wbWidth,
                                    instObj->wbHeight);
            BspOsal_cacheInv(wbBufAllocatedAddr, instObj->wbFramesSize,
                             BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
            BspUtils_appPrintSaveRawCmd(
                fileStr,
                wbBufAllocatedAddr,
                instObj->wbDataFmt,
                instObj->wbWidth,
                instObj->wbHeight,
                DISP_APP_WB_NUM_FRAMES_TO_SAVE * currentFrameBytes);

            GT_0trace(BspAppTrace, GT_INFO,
                      "Trying to save buffer to SD card. \r\n" );
            if (BSP_SOK != BspUtils_appSaveFileToSd(
                fileNameString,
                "/dssWb_output_files",
                wbBufAllocatedAddr,
                DISP_APP_WB_NUM_FRAMES_TO_SAVE * currentFrameBytes,
                &bytesWritten))
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          "Couldnot save buffer to SD card. \r\n" );
            }
            else
            {
                GT_0trace(BspAppTrace, GT_INFO,
                          "saved buffer to SD card. \r\n" );
            }

            BspUtils_memFree(wbBufAllocatedAddr, instObj->wbFramesSize);
        }

        retVal = Fvid2_delete(instObj->drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": WB Delete Failed!!!\r\n");
            break;
        }
    }
    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": WB delete complete!!\r\n");
    }

    return;
}

static Int32 DispWbApp_configDctrl(DispWbApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;
    Vps_DctrlConfig             *dctrlCfg;
    Vps_DssDispcOvlyPanelConfig *panelCfg;
    Fvid2_ModeInfo              *mInfo;
    Vps_DctrlVencDivisorInfo vencDivisors;
    Vps_DctrlOutputInfo vencInfo;
    UInt32 pixelClk, instCnt, sdVencEnable;
    DispWbApp_InstObj           *instObj;
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
                        if (VPS_DISP_INST_DSS_GFX1 ==
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
                            appObj->testPrms.inWidth[instCnt] = DISP_APP_BUF_WIDTH;
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

        vencInfo.hsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencInfo.vsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
        vencInfo.vencId     = VPS_DCTRL_DSS_VENC_HDMI;
    }
#endif

    /* This IOCTL should be called before SET_CONFIG_IOCTL */
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
    if (appObj->testPrms.vencId[0] != VPS_DCTRL_DSS_VENC_HDMI)
    {
        if (appObj->testPrms.boardMode == BSP_BOARD_MODE_VIDEO_8BIT_TDM)
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
        else
        {
            /* Disable TDM mode if enabled before for TDM use cases.*/
            VpsDssDispcAdvLcdTdmConfig_init(&advTdmPrms);
            advTdmPrms.tdmEnable = 0;
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

    retVal = DispWbApp_configDctrlPipe(appObj);

    if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) &&
        ((appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD1) ||
         (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD2) ||
         (appObj->testPrms.vencId[0] == VPS_DCTRL_DSS_VENC_LCD3)))
    {
        if (appObj->testPrms.isSdVenc == TRUE)
        {
            pixelClk = 54000U;
            retVal   = DispWbApp_configureVideoPllAndClkSrc(appObj, pixelClk);
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
            retVal = DispWbApp_configureVideoPllAndClkSrc(appObj, pixelClk);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Configuring Video PLL  Failed!!!\r\n");
            }
        }
        else if (appObj->testPrms.encDrvId[0] == FVID2_VID_ENC_SII9022A_DRV)
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
            retVal = DispWbApp_configureVideoPllAndClkSrc(appObj, pixelClk);
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

static Int32 DispWbApp_configDctrlPipe(DispWbApp_Obj *appObj)
{
    Vps_DssDispcOvlyPipeConfig *ovlpipecfg;
    UInt32 instCnt;
    DispWbApp_InstObj          *instObj;
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

/**
 *  DispWbApp_cbFxn
 *  \brief Driver callback function.
 */
static Int32 DispWbApp_cbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32              retVal  = FVID2_SOK;
    DispWbApp_InstObj *instObj = (DispWbApp_InstObj *) appData;
    Fvid2_FrameList    frmList;

    retVal = Fvid2_dequeue(
        instObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        if (wbBufDisplay == TRUE)
        {
            frmList.frames[0U]->addr[0][0] = wbBufDisplayAddr;
            frmList.frames[0U]->addr[1][0] = wbBufDisplayAddr +
                                             currentFrameBytes / 2;
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
 *  DispWbApp_wbCbFxn
 *  \brief Driver callback function.
 */
static Int32 DispWbApp_wbCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32              retVal  = FVID2_SOK;
    DispWbApp_InstObj *instObj = (DispWbApp_InstObj *) appData;
    Fvid2_FrameList    frmList;
    retVal = Fvid2_dequeue(
        instObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        if (wbFrameNo < numWbFrames)
        {
            wbFrameNo++;
            frmList.frames[0U]->addr[0][0] = wbBufAddr;
            frmList.frames[0U]->addr[1][0] = wbBufAddr + currentFrameBytes / 2;
            wbBufAddr += currentFrameBytes;
        }
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Display Queue Failed!!!\r\n");
        }
    }
    instObj->appObj->callBackCountWb++;

    return (retVal);
}

/**
 *  DispWbApp_LoadBuf
 */
static Int32 DispWbApp_LoadBuf(DispWbApp_Obj              *appObj,
                               const DispWbApp_LoadBufCfg *cfg)
{
    Int32  retVal = FVID2_SOK;
    char   userInput;
    UInt32 bCnt;
    DispWbApp_BufInfo *bufInfo = NULL;
    char fileNameString[100];
    UInt32 bytesRead;

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
            memcpy(&bufInfo->bufCfg, cfg, sizeof (DispWbApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < DISP_APP_MAX_BUFFERS; bCnt++)
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

            memcpy(&bufInfo->bufCfg, cfg, sizeof (DispWbApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < DISP_APP_MAX_BUFFERS; bCnt++)
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
        for (bCnt = 0u; bCnt < DISP_APP_MAX_BUFFERS; bCnt++)
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
 *  DispWbApp_LoadBuf
 */
static Int32 DispWbApp_FreeBuf(DispWbApp_Obj              *appObj,
                               const DispWbApp_LoadBufCfg *cfg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 bCnt;
    DispWbApp_BufInfo *bufInfo = NULL;

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
            for (bCnt = 0u; bCnt < DISP_APP_MAX_BUFFERS; bCnt++)
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
 *  DispWbApp_GetBufInfo
 */
static DispWbApp_BufInfo *DispWbApp_GetBufInfo(
    const DispWbApp_Obj *appObj,
    UInt32               dataFmt,
    UInt32               scanFmt,
    UInt32
    fieldsMerged,
    UInt32               pitch)
{
    DispWbApp_BufInfo *bufInfo = NULL;

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
static Int32 DispWbApp_allocAndQueueFrames(const DispWbApp_Obj *appObj,
                                           DispWbApp_InstObj   *instObj)
{
    Int32              retVal = FVID2_SOK;
    UInt32             frmId;
    UInt32             numFrames;
    UInt32             yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format      *fmt;
    Fvid2_Frame       *frm;
    Fvid2_FrameList    frmList;
    DispWbApp_BufInfo *bufInfo;

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

    bufInfo = DispWbApp_GetBufInfo(appObj, instObj->inDataFmt,
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
 *  \brief Allocate and queue frames to driver
 */
static Int32 DispWbApp_wbAllocAndQueueFrames(const DispWbApp_Obj *appObj,
                                             DispWbApp_InstObj   *instObj)
{
    Int32           retVal = FVID2_SOK;
    UInt32          frmId;
    UInt32          bufSize;
    UInt32          yFld1Offset, cbCrFld0Offset, cbCrFld1Offset;
    Fvid2_Format   *fmt;
    Fvid2_Frame    *frm;
    Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);

    fmt = &instObj->allocFmt;
    Fvid2Format_init(fmt);
    frm = &instObj->wbFrames[0];

    /* fill format with channel specific values  */
    fmt->chNum  = 0U;
    fmt->width  = instObj->wbWidth;
    fmt->height = instObj->wbHeight;
    /* Allocate WB buffer of size input source width */
    /* Pitch should not be increased to allign to word boundry etc.
     * as writeback pipe doesnot support pitch. */

    if (Fvid2_isDataFmtSemiPlanar(instObj->wbDataFmt))
    {
        fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX]    = fmt->width;
        fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX];
    }
    else if (Fvid2_isDataFmtYuv422I(instObj->wbDataFmt))
    {
        fmt->pitch[FVID2_YUV_INT_ADDR_IDX] = fmt->width * 2U;
    }
    else if (Fvid2_isDataFmtRgb16bit(instObj->wbDataFmt))
    {
        fmt->pitch[FVID2_YUV_INT_ADDR_IDX] = fmt->width * 2U;
    }
    else if (Fvid2_isDataFmtRgb24bit(instObj->wbDataFmt))
    {
        fmt->pitch[FVID2_RGB_ADDR_IDX] = fmt->width * 3U;
    }
    else if (Fvid2_isDataFmtRgb32bit(instObj->wbDataFmt))
    {
        fmt->pitch[FVID2_RGB_ADDR_IDX] = fmt->width * 4U;
    }

    fmt->fieldMerged[0] = instObj->wbFieldMerge;
    fmt->fieldMerged[1] = FALSE;
    fmt->fieldMerged[2] = FALSE;
    fmt->dataFormat     = instObj->wbDataFmt;
    fmt->scanFormat     = instObj->wbScanFormat;
    fmt->bpp = FVID2_BPP_BITS16;    /* ignored */

    currentFrameBytes = fmt->pitch[0] * fmt->height;
    /*
     * alloc memory based on 'format'
     * Allocated frame info is put in frames[]
     * LPBK_APP_FRAMES_PER_CH is the number of buffers per channel to
     * allocate
     */
    retVal = BspUtils_memFrameAlloc(fmt, frm, DISP_APP_WB_MAX_FRAMES_PER_HANDLE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Frame Alloc Failed!!!\r\n");
    }
    else
    {
        BspUtils_memFrameGetSize(fmt, &bufSize, NULL);
        instObj->wbFramesSize = DISP_APP_WB_MAX_FRAMES_PER_HANDLE * bufSize;
        numWbFrames           = instObj->wbFramesSize / currentFrameBytes;
        wbBufAddr          = frm->addr[0][0];
        wbBufAllocatedAddr = frm->addr[0][0];
        wbFrameNo          = DISP_APP_WB_MAX_FRAMES_PER_HANDLE;
        /* Queue only 4 buffers max */
        if (wbFrameNo > 4)
        {
            wbFrameNo = 4;
        }

        /* Initialize writeback buffer to zero */
        BspUtils_memset(frm->addr[0][0], 0x0U, instObj->wbFramesSize);
        /* Flush and invalidate the CPU write */
        BspOsal_cacheWbInv(
            frm[0U].addr[0U][0U],
            instObj->wbFramesSize,
            BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);

        for (frmId = 0U; frmId < wbFrameNo; frmId++)
        {
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
                                  ((fmt->pitch[0U] * fmt->height) / 2);
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
                                  (fmt->pitch[0U] * fmt->height * 2U));
                    cbCrFld1Offset =
                        (UInt32) (cbCrFld0Offset + fmt->pitch[0U]);
                }
                else
                {
                    yFld1Offset =
                        (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                                  (fmt->pitch[0U] * fmt->height * 3U) / 2);

                    cbCrFld0Offset =
                        (UInt32) ((UInt32) frm[frmId].addr[0U][0U] +
                                  (fmt->pitch[0U] * fmt->height));

                    cbCrFld1Offset =
                        (UInt32) (yFld1Offset +
                                  (fmt->pitch[0U] * fmt->height));
                }
                frm[frmId].addr[0U][1U] = (Ptr) cbCrFld0Offset;
                frm[frmId].addr[1U][0U] = (Ptr) yFld1Offset;
                frm[frmId].addr[1U][1U] = (Ptr) cbCrFld1Offset;
            }

            /* Set number of frame in frame list */
            frmList.frames[0U] = &frm[frmId];
            frmList.frames[0U]->addr[0][0] = wbBufAddr;
            frmList.numFrames = 1U;

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
            wbBufAddr += currentFrameBytes;
        }
    }
    return (retVal);
}

/**
 *  DispWbApp_initParams
 *  Initialize the global variables and frame pointers.
 */
static void DispWbApp_initParams(DispWbApp_Obj *appObj)
{
    UInt32 instCnt;
    Vps_DispDssParams    *dssPrms;
    DispWbApp_InstObj    *instObj;
    Vps_CaptCreateParams *createPrms;

    appObj->totalFldCount   = 0U;
    appObj->totalCpuLoad    = 0U;
    appObj->cpuLoadCount    = 0U;
    appObj->callBackCount   = 0U;
    appObj->callBackCountWb = 0U;
    appObj->lcdCtrlhdl      = NULL;

    for (instCnt = 0U; instCnt < appObj->testPrms.numHandles; instCnt++)
    {
        appObj->maxWidth   = DISP_APP_BUF_WIDTH;
        appObj->maxHeight  = DISP_APP_BUF_HEIGHT;
        instObj            = &appObj->instObj[instCnt];
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
        instObj->cbPrms.cbFxn   = &DispWbApp_cbFxn;
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
    for (instCnt = 0; instCnt < appObj->testPrms.numCaptHandles; instCnt++)
    {
        instObj = &appObj->instObj[appObj->testPrms.numHandles + instCnt];
        instObj->wbDataFmt = appObj->testPrms.wbDataFmt[instCnt];

        instObj->wbInSourceWidth   = appObj->testPrms.wbInSourceWidth[instCnt];
        instObj->wbInSourceHeight  = appObj->testPrms.wbInSourceHeight[instCnt];
        instObj->wbInSourceDataFmt = FVID2_DF_BGR24_888;
        instObj->wbInWidth         = appObj->testPrms.wbInWidth[instCnt];
        instObj->wbInHeight        = appObj->testPrms.wbInHeight[instCnt];
        instObj->wbWidth           = appObj->testPrms.wbWidth[instCnt];
        instObj->wbHeight          = appObj->testPrms.wbHeight[instCnt];
        instObj->wbFieldMerge      = appObj->testPrms.wbFieldMerge[instCnt];
        instObj->wbScanFormat      = appObj->testPrms.inScanFormat[instCnt];
        instObj->wbPosx     = appObj->testPrms.wbposx[instCnt];
        instObj->wbPosy     = appObj->testPrms.wbposy[instCnt];
        instObj->captInstId = appObj->testPrms.captInstId[instCnt];
        instObj->drvHandle  = NULL;
        Fvid2CbParams_init(&instObj->cbPrms);
        instObj->cbPrms.cbFxn   = &DispWbApp_wbCbFxn;
        instObj->cbPrms.appData = instObj;

        createPrms = &instObj->captCreatePrms;
        VpsCaptCreateParams_init(createPrms);
        createPrms->videoIfMode  = appObj->testPrms.captVideoIfMode;
        createPrms->videoIfWidth = appObj->testPrms.captVideoIfWidth;
        createPrms->bufCaptMode  = VPS_CAPT_BCM_LAST_FRM_REPEAT;
        createPrms->numCh        = DISP_APP_NUM_CAPT_CH;
        createPrms->numStream    = DISP_APP_NUM_CAPT_STREAM;

        instObj->appObj = appObj;
    }

    return;
}

static void DispWbApp_printStatistics(DispWbApp_Obj *appObj,
                                      UInt32         execTimeInMsecs)
{
    UInt32 instCnt;
    DispWbApp_InstObj *instObj;

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

static void DispWbApp_configureLCD(DispWbApp_Obj *appObj)
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
}

static void DispWbApp_turnoffLCD(DispWbApp_Obj *appObj)
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
    return;
#endif
}

static Int32 DispWbApp_configureOffChipHdmi(DispWbApp_Obj *appObj,
                                            UInt32         encInst)
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

static Int32 DispWbApp_deConfigureOffChipHdmi(DispWbApp_Obj *appObj,
                                              UInt32         encInst)
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
 *  DispWbApp_getTestId
 *  Return the test ID to run.
 */
static Int32 DispWbApp_getTestId(DispWbApp_Obj *appObj)
{
    UInt32       testCnt;
    Int32        retVal;
    static Int32 testIdx = 0;
    Int32        testId = 0;
    static UInt32 timeoutVal = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "Select test to run as per below table:\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    for (testCnt = 0; testCnt < DISP_WB_APP_NUM_TESTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO, "%3d: %s\r\n",
            gDispWbAppTestPrms[testCnt].testId,
            gDispWbAppTestPrms[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\r\n", DISP_WB_APP_AUTORUN_OPT, "Auto Run\r\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", DISP_WB_APP_EXIT_OPT);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run (in UART console): \r\n");

    if (TRUE == appObj->enableAutoRun)
    {
        testIdx++;
        if (testIdx < DISP_WB_APP_NUM_TESTS)
        {
            GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                gDispWbAppTestPrms[testIdx].testId,
                gDispWbAppTestPrms[testIdx].testDescStr);
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
                    gDispWbAppTestPrms[testIdx].testId,
                    gDispWbAppTestPrms[testIdx].testDescStr);
                    break;
            }
            else
            {
                timeoutVal = BSP_UTILS_UART_RX_WAIT_FOREVER;
            }
            testIdx = DispWbApp_getTestIndex(testId);

            if ((testIdx >= 0) && (testIdx < DISP_WB_APP_NUM_TESTS))
            {
                GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
                break;
            }
            if (testId == DISP_WB_APP_AUTORUN_OPT)
            {
                appObj->enableAutoRun = (UInt32) TRUE;
                testIdx = 0;
                GT_2trace(BspAppTrace, GT_INFO, "%d: %s\r\n",
                    gDispWbAppTestPrms[testIdx].testId,
                    gDispWbAppTestPrms[testIdx].testDescStr);
                break;
            }
            else if (DISP_WB_APP_EXIT_OPT == testId)
            {
                testIdx = DISP_WB_APP_EXIT_OPT;
                break;
            }
            GT_0trace(BspAppTrace, GT_INFO, "Invalid Test ID. Enter Agian!!\r\n");
        }
    }

    return (testIdx);
}

static Int32 DispWbApp_getTestIndex(Int32 testId)
{
    Int32  testIdx;
    UInt32 testIdFound = FALSE;
    for (testIdx = 0; testIdx <DISP_WB_APP_NUM_TESTS; testIdx++)
    {
        if(testId == gDispWbAppTestPrms[testIdx].testId)
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

static Int32 DispWbApp_updateFieldFromDetectedLcd(
    DispWbApp_Obj *appObj, UInt32 *fieldAddr, DispWbApp_LcdFieldType fieldType)
{
    Int32 retVal = FVID2_SOK;
    if (fieldType == DISPWBAPP_FIELD_LCD_WIDTH)
    {
        if ((*fieldAddr) == DISP_APP_USE_LCD_WIDTH)
        {
            *fieldAddr = appObj->lcdPanelInfo.modeInfo.width;
        }
        else if ((*fieldAddr) == DISP_APP_USE_LCD_WIDTH_BY2)
        {
            *fieldAddr = appObj->lcdPanelInfo.modeInfo.width / 2;
        }
        else
        {
            /* Field value is absolute and not based on LCD.
             * No need to update here */
        }
    }
    else if (fieldType == DISPWBAPP_FIELD_LCD_HEIGHT)
    {
        if ((*fieldAddr) == DISP_APP_USE_LCD_HEIGHT)
        {
            (*fieldAddr) = appObj->lcdPanelInfo.modeInfo.height;
        }
        else if ((*fieldAddr) == DISP_APP_USE_LCD_HEIGHT_BY2)
        {
            (*fieldAddr) = appObj->lcdPanelInfo.modeInfo.height / 2;
        }
        else if ((*fieldAddr) == DISP_APP_USE_LCD_HEIGHT_MINUS10)
        {
            (*fieldAddr) = appObj->lcdPanelInfo.modeInfo.height - 10;
        }
        else
        {
            /* Field value is absolute and not based on LCD.
             * No need to update here */
        }
    }
    else
    {
        retVal = FVID2_EFAIL;
    }
    return (retVal);
}

