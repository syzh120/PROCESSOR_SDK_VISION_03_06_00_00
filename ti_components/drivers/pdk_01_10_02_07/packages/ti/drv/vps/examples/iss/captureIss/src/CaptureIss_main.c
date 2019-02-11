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
 *  \file CaptureIss_main.c
 *
 *  \brief CAL Capture demo application - Receives via CSI2/Parallel and
 *          write to memory
 *         Most board / EVM specifics are handled in function
 *          appCaptcreateVidSensor () In addition to configuring the sensor
 *          for the given config and enable sensor to stream.
 *         On TDA2EX only CSI2 based capture is supported.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CaptureIss_main.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< CSI2 PHY Clock OV10640
 *      For a 15X15 Package TDA3MAx(15x15), TDA3LAx(15x15), TDA3LRx(15x15). */
#define APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz (400U)

/**< CSI2 PHY Clock IMX224 */
#define APP_CAPT_ISS_CAL_IMX224_PHY_CLK_MHz (150U)

/**< CSI2 PHY Clock for UB964 with 4 SAT0088 modules */
#define APP_CAPT_ISS_CAL_UB964_PHY_CLK_MHz (800U)
/**< CSI2 PHY Clock for UB960 with 4 TIDA00262 modules */
#define APP_CAPT_ISS_CAL_UB960_PHY_CLK_MHz (750U)
/**< CSI2 PHY Clock for OV2775 sensor */
#define APP_CAPT_ISS_CAL_OV2775_PHY_CLK_MHz (480U)
/**< Custom sensor */
#define APP_CAPT_ISS_CAL_SENSOR_BYPASS_PHY_CLK_MHz (400U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void appCaptCreateTask(void);
static void appCaptTask(UArg arg0, UArg arg1);
static void appCaptInit(appCaptObj_t *appObj);
static void appCaptDeInit(appCaptObj_t *appObj);
static void appCapture4GivenConfig(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static void appCaptDeriveCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptCreateDrv(appCaptObj_t *appObj);
static Int32 appCaptDeleteDrv(appCaptObj_t *appObj);
static Int32 appCaptSetDrvCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptAllocAndQFrames(appCaptObj_t *appObj);
static Int32 appCaptFreeFrames(appCaptObj_t *appObj);
static void appCaptCountQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                          UInt32 streamId);
static void appCaptCountDQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                           UInt32 streamId);
static void appCaptChkDQCounts(appCaptObj_t *appObj);
static Int32 appCaptGetTestId(appCaptObj_t *appObj);
static Int32 appCaptcreateVidSensor(appCaptObj_t *instObj, appCaptCfg_t *pCfg);
static void appCaptPrintStatistics(appCaptObj_t *appObj,
                                   UInt32        execTimeInMsecs);
static Int32 appCaptDeleteVidSensor(appCaptObj_t *instObj, appCaptCfg_t *pCfg);
static void appCaptErrCb(const UInt32 *event, UInt32 numEvents, Ptr arg);
static Int32 appCaptEnableErrorReporting(appCaptObj_t *appObj,
                                            appCaptCfg_t *pCfg);
static void appCaptCustomSensorConfig(void);
static Int32 appCaptEnableFrameEventNotification(appCaptObj_t *appObj,
                                                    appCaptCfg_t *pCfg);
static void appCaptChkFrameEvents(appCaptObj_t *appObj);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**< Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gCaptAppTskStackMain, 32)
/**< Place the stack in stack section. */
#pragma DATA_SECTION(gCaptAppTskStackMain, ".bss:taskStackSection")
/**< Demo application stack */
static UInt8 gCaptAppTskStackMain[CAPT_APP_TSK_STACK_MAIN];

/**< demo application object */
appCaptObj_t gCaptAppObj;

/**< Different capture options supported by this demo */
appCaptCfg_t gTestCfg[] = {
    {"OV10640 CSI2 4Lanes capture on ISS",                        0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"IMX224 CSI2 4Lanes capture on ISS",                         0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1312U, 2164U, (1312U * 2U),
     FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"APT AR0132 Sensor Parallel capture on ISS",                 1U,
     TRUE,
     FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0132_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, CAPT_APP_PHY_0},

    {"APT AR0140 1280x800 Sensor Parallel capture on ISS",        1U,
     TRUE,
     FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 800U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0140_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, CAPT_APP_PHY_0},

    {"UB960 & TIDA00262 CSI2 4 channel capture",                  0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 4U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"UB960 & IMI OV10640 CSI2 4 channel capture",                  0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 4U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_IMI_OV10640_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"UB964 & SAT0088 and OV10635 CSI2 4 channel capture ", 0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 4U, 0U, VPS_ISS_CAL_CSI2_YUV422_8B, FVID2_BPP_BITS10,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"OV2775 CSI2 4Lanes capture on ISS",                        0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1920U, 1080U, (1920U * 2U),
     FVID2_VID_SENSOR_OV2775_CSI2_DRV,
     FVID2_STD_1080P_30, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"Sensor Config Bypassed CSI2 4Lanes capture color bars from UB954",   0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RGB888, FVID2_BPP_BITS24,
     CAPT_APP_RUN_COUNT, 640U, 480U, (640U * 3U),
     FVID2_VID_SENSOR_BYPASS_CSI2_DRV,
     FVID2_STD_1080P_30, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS24,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"Sensor Config Bypassed CSI2 2Lanes capture color bars from UB954 on PHY 0",
     0U, TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_2LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RGB888, FVID2_BPP_BITS24,
     CAPT_APP_RUN_COUNT, 640U, 480U, (640U * 3U),
     FVID2_VID_SENSOR_BYPASS_CSI2_DRV,
     FVID2_STD_1080P_30, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS24,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_0},

    {"Sensor Config Bypassed CSI2 2Lanes capture color bars from UB954 on PHY 1",
     0U, TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_2LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RGB888, FVID2_BPP_BITS24,
     CAPT_APP_RUN_COUNT, 640U, 480U, (640U * 3U),
     FVID2_VID_SENSOR_BYPASS_CSI2_DRV,
     FVID2_STD_1080P_30, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS24,
     BSP_BOARD_MODE_DEFAULT, CAPT_APP_PHY_1},
};

/**< Number of options supported */
#define APP_CAPT_NUM_OPTS              (sizeof (gTestCfg) / \
                                        sizeof (gTestCfg[0U]))

static BspUtils_Ub95xI2cParams gUb9542LanesCfg[]={
    {0x4c, 0x01, 0x1},
    {0x58, 0X5e, 0x2},
    {0x1f, 0x02, 0x1},
    {0x12, 0x13, 0x1},
    {0x32, 0x01, 0x1},
    {0x33, 0x23, 0x1}, /* 2 lanes only */
    {0xB0, 0x00, 0x1}, /* Indirect access to pattern genrator */
    {0xB1, 0x01, 0x1}, /* Select Reg PGEN_CTL */
    {0xB2, 0x01, 0x1}, /* Write 1 to it */
    {0x20, 0x00, 0x1}
    };

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
Int32 main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    appCaptCreateTask();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void appCaptCreateTask(void)
{
    Task_Params tskPrms;

    BspUtils_memset(&gCaptAppObj, 0x0, sizeof (appCaptObj_t));
    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = CAPT_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gCaptAppTskStackMain;
    tskPrms.stackSize     = sizeof (gCaptAppTskStackMain);
    tskPrms.arg0          = (UArg) & gCaptAppObj;
    gCaptAppObj.tskHandle = Task_create(appCaptTask, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gCaptAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gCaptAppObj.tskHandle, APP_NAME);

    return;
}

/*
 * Test task main
 */
static void appCaptTask(UArg arg0, UArg arg1)
{
    BspUtils_MemHeapStatus startHeapStat1;
    appCaptObj_t          *appObj = (appCaptObj_t *) arg0;
    UInt32 testId;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    appCaptInit(appObj);

    while (1U)
    {
        /* Get the TestId */
        testId = appCaptGetTestId(appObj);
        if (testId < APP_CAPT_NUM_OPTS)
        {
            BspUtils_memGetHeapStat(&startHeapStat1);

            appCapture4GivenConfig(
                appObj,
                &gTestCfg[testId]);

            BspUtils_memCheckHeapStat(&startHeapStat1);
        }
        else
        {
            /* Exit */
            break;
        }
    }

    appCaptDeInit(appObj);

    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max BSS Memory used for test task: %d bytes\r\n",
              appObj->captIssAppMaxBSSMemHeapUS);
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

static void appCaptInit(appCaptObj_t *appObj)
{
    Int32  retVal;
    UInt32 isI2cInitReq;

    appObj->captIssAppMaxBSSMemHeapUS = 0;

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
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": VPS Initialized\r\n");
    }

    return;
}

static void appCaptDeInit(appCaptObj_t *appObj)
{
    Int32  retVal;
    UInt32 isI2cDeInitReq;

    appObj->captIssAppMaxBSSMemHeapUS = 0;

    /* System de-init */
    isI2cDeInitReq = TRUE;
    retVal         = BspUtils_appDefaultDeInit(isI2cDeInitReq);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": System De-Init Failed!!!\r\n");
    }

    if (retVal == FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": VPS De Initialized\r\n");
    }
    return;
}

/**
 *  appCapture4GivenConfig
 *  Capture test function.
 */
static void appCapture4GivenConfig(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32           retVal = FVID2_SOK;
    UInt32          startTime, endTime, numRegs;
    volatile UInt32 lastFrameNo = 0;

    /* Print test case information */
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Configured to capture %d frames \r\n",
              pCfg->numFrames);
    BspUtils_memcpy(&appObj->testPrms, pCfg, sizeof (appCaptCfg_t));

    appObj->instId = VPS_CAPT_INST_ISS_CAL_A;

    /* Make config required for open */
    appCaptDeriveCfg(appObj, pCfg);

    retVal = appCaptCreateDrv(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptSetDrvCfg(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptEnableErrorReporting(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptEnableFrameEventNotification(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptAllocAndQFrames(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    if (FVID2_VID_SENSOR_BYPASS_CSI2_DRV == pCfg->sensorDrvId)
    {
        /* If 2 lanes are used, use the UB954 config for 2 lanes */
        if (FVID2_VIFW_2LANES == pCfg->interfacewidth)
        {
            numRegs = sizeof(gUb9542LanesCfg) / (sizeof(gUb9542LanesCfg[0]));
            BspUtils_appInitUb954_Ub953(&gUb9542LanesCfg[0U], numRegs);
        }
        else
        {
            BspUtils_appInitUb954_Ub953(NULL, 0);
        }
        appCaptCustomSensorConfig();
    }
    else
    {
        retVal = appCaptcreateVidSensor(appObj, pCfg);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Failed to configure the sensor!!!\r\n");
            return;
        }
    }

    appObj->rcvedFramesCount = 0x0;
    appObj->frameWithCrcErrorCnt = 0x0;
    appObj->frameWithWarning = 0x0;
    appObj->frameErrorCnt = 0x0;
    appObj->sofIntCount = 0x0;
    appObj->unExpectedIntCnt = 0x0;
    appObj->crcErrIntCnt = 0x0;
    appObj->eccErrIntCnt = 0x0;
    appObj->nLineEventIdx = 0x0;
    appObj->eofEventIdx[0U] = 0x0;
    appObj->eofEventIdx[1U] = 0x0;
    appObj->eofEventIdx[2U] = 0x0;
    appObj->eofEventIdx[3U] = 0x0;
    appObj->frameEventTrack = 1U;
    lastFrameNo = 0x0U;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Starting Capture now...\r\n");

    startTime = BspOsal_getCurTimeInMsec();
    retVal    = Fvid2_start(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Start Failed!!!\r\n");
        return;
    }

    /* Wait for reception completion */
    while (appObj->rcvedFramesCount <
           (appObj->numFramesToCapture * pCfg->numStreams))
    {
        if ((0U == lastFrameNo) && (appObj->rcvedFramesCount))
        {
            lastFrameNo = appObj->rcvedFramesCount;
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Stream Detected!!!\r\n");
        }
    }

    /* Disable time stamping of frame events */
    appObj->frameEventTrack = 0U;

    retVal = Fvid2_stop(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\r\n");
        return;
    }
    endTime = BspOsal_getCurTimeInMsec();

    appCaptPrintStatistics(appObj, endTime - startTime);

    retVal = appCaptFreeFrames(appObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\r\n");
        return;
    }

    appCaptChkDQCounts(appObj);

    appCaptChkFrameEvents(appObj);

    retVal = appCaptDeleteDrv(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    if (FVID2_VID_SENSOR_BYPASS_CSI2_DRV != pCfg->sensorDrvId)
    {
        retVal = appCaptDeleteVidSensor(appObj, pCfg);
    }
    else
    {
        BspUtils_appDeInitUb954_Ub953();
    }

    return;
}

/**
 *  appCaptCb
 *  \brief Driver callback function.
 */
static Int32 appCaptCb(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamId, frmIdx;
    static Fvid2_FrameList frmList;
    Fvid2_Frame *pFrm;
    appCaptObj_t *appObj = (appCaptObj_t *) appData;
    GT_assert(BspAppTrace, appData != NULL);

    for (streamId = 0U; streamId < appObj->numStream; streamId++)
    {
        retVal = Fvid2_dequeue(
            appObj->drvHandle,
            &frmList,
            streamId,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK == retVal)
        {
            for (frmIdx = 0; frmIdx < frmList.numFrames; frmIdx++)
            {
                pFrm = frmList.frames[frmIdx];
                if (FVID2_FRAME_STATUS_COMPLETED != pFrm->status)
                {
                    switch (pFrm->status)
                    {
                        case FVID2_FRAME_STATUS_CRC_ERROR:
                            appObj->frameWithCrcErrorCnt++;
                        break;

                        case FVID2_FRAME_STATUS_ECC_CORRECTED:
                            appObj->frameWithWarning++;
                        break;

                        case FVID2_FRAME_STATUS_OVERFLOW:
                        case FVID2_FRAME_STATUS_ECC_ERROR:
                            appObj->frameErrorCnt++;
                        break;
                        default:
                            appObj->frameErrorCnt++;
                        break;
                    }
                }
            }

            appCaptCountDQ(appObj, &frmList, streamId);
            appCaptCountQ(appObj, &frmList, streamId);

            retVal = Fvid2_queue(appObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Queue Failed!!!\r\n");
            }
        }
        appObj->rcvedFramesCount += frmList.numFrames;
        appObj->totalFrmCount    += frmList.numFrames;
    }
    return FVID2_SOK;
}

/**
 *  appCaptDeriveCfg
 *  Initialize the global variables and frame pointers.
 */
static void appCaptDeriveCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    UInt32 streamId;
    Vps_CaptCreateParams  *createPrms;
    vpsissCalCmplxIoCfg_t *pCmplxIoCfg;

    appObj->maxWidth      = 1920U;
    appObj->maxHeight     = 1080U;
    appObj->totalFrmCount = 0U;
    appObj->totalCpuLoad  = 0U;
    appObj->cpuLoadCount  = 0U;

    appObj->instId    = VPS_CAPT_INST_ISS_CAL_A;
    appObj->drvHandle = NULL;
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn   = &appCaptCb;
    appObj->cbPrms.appData = appObj;

    appObj->numStream = pCfg->numStreams;
    GT_assert(BspAppTrace, ((0U < pCfg->numStreams) &&
                            (pCfg->numStreams < VPS_ISS_CAL_MAX_STREAMS)));

    createPrms = &appObj->createPrms;
    VpsCaptCreateParams_init(&appObj->createPrms);
    createPrms->videoIfMode     = pCfg->interfaceType;
    createPrms->videoIfWidth    = pCfg->interfacewidth;
    createPrms->bufCaptMode     = VPS_CAPT_BCM_LAST_FRM_REPEAT;
    createPrms->numCh           = 1U;
    createPrms->numStream       = appObj->numStream;
    createPrms->pAdditionalArgs = &appObj->issOpenPrms;

    if (FVID2_VID_SENSOR_OV10640_CSI2_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock[0] =
            APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz;
    }
    else if (FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock[0] =
            APP_CAPT_ISS_CAL_IMX224_PHY_CLK_MHz;
    }
    else if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock[0] =
                APP_CAPT_ISS_CAL_UB964_PHY_CLK_MHz;
    }
    else if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
            (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId))
    {
        appObj->issOpenPrms.csi2PhyClock[0] =
                APP_CAPT_ISS_CAL_UB960_PHY_CLK_MHz;
    }
    else if (FVID2_VID_SENSOR_BYPASS_CSI2_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock[0] =
                                    APP_CAPT_ISS_CAL_SENSOR_BYPASS_PHY_CLK_MHz;
    }
    else
    {
        appObj->issOpenPrms.csi2PhyClock[0] = APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz;
    }

    if (FVID2_VIFM_SCH_CPI == pCfg->interfaceType)
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


    if ((FVID2_VID_SENSOR_BYPASS_CSI2_DRV == pCfg->sensorDrvId) &&
        (CAPT_APP_PHY_1 == pCfg->physUsed))
    {
        appObj->issOpenPrms.subModules[0U] =
            (VPS_ISS_CAPT_CAL_SUB_PPI_ID_1 |
             VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
             VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
             VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
    }

    if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId))
    {
        appObj->issOpenPrms.subModules[1U] =
            (
                VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 |
                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
        appObj->issOpenPrms.subModules[2U] =
            (
                VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 |
                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
        appObj->issOpenPrms.subModules[3U] =
            (
                VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 |
                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
    }

    if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
             (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId))
    {
        /* For TDA2Ex Entry switch to 2 lanes only */
        if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
        {
            if (BSP_PLATFORM_PACKAGE_TYPE_17x17 ==
                        Bsp_platformGetPackageType())
            {
                pCfg->interfacewidth = FVID2_VIFW_2LANES;
                createPrms->videoIfWidth = FVID2_VIFW_2LANES;
                GT_0trace(BspAppTrace, GT_INFO,
                                    "Updated TDA2Ex 17x17 to 2 Lanes !!!\r\n");
            }
        }
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

    if (FVID2_VID_SENSOR_OV2775_CSI2_DRV == pCfg->sensorDrvId)
    {
        pCmplxIoCfg->clockLane.pol      = FALSE;
        pCmplxIoCfg->clockLane.position = 3U;
        pCmplxIoCfg->data1Lane.pol      = FALSE;
        pCmplxIoCfg->data1Lane.position = 4U;
        pCmplxIoCfg->data2Lane.pol      = FALSE;
        pCmplxIoCfg->data2Lane.position = 2U;
        pCmplxIoCfg->data3Lane.pol      = FALSE;
        pCmplxIoCfg->data3Lane.position = 5U;
        pCmplxIoCfg->data4Lane.pol      = FALSE;
        pCmplxIoCfg->data4Lane.position = 1U;

        appObj->issOpenPrms.csi2PhyClock[0] =
            APP_CAPT_ISS_CAL_OV2775_PHY_CLK_MHz;
    }

    if (FVID2_VIFW_3LANES == pCfg->interfacewidth)
    {
        pCmplxIoCfg->data4Lane.position = 0U;
    }
    if (FVID2_VIFW_2LANES == pCfg->interfacewidth)
    {
        pCmplxIoCfg->data3Lane.position = 0U;
        pCmplxIoCfg->data4Lane.position = 0U;
    }
    if (FVID2_VIFW_1LANES == pCfg->interfacewidth)
    {
        pCmplxIoCfg->data2Lane.position = 0U;
        pCmplxIoCfg->data3Lane.position = 0U;
        pCmplxIoCfg->data4Lane.position = 0U;
    }
    if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId))
    {
        pCmplxIoCfg->clockLane.pol      = FALSE;
        pCmplxIoCfg->clockLane.position = 1U;
        pCmplxIoCfg->data1Lane.pol      = FALSE;
        pCmplxIoCfg->data1Lane.position = 2U;
    }

    if (FVID2_VID_SENSOR_BYPASS_CSI2_DRV == pCfg->sensorDrvId)
    {
        pCmplxIoCfg->clockLane.pol      = FALSE;
        pCmplxIoCfg->clockLane.position = 1U;
        pCmplxIoCfg->data1Lane.pol      = FALSE;
        pCmplxIoCfg->data1Lane.position = 2U;

        if (CAPT_APP_PHY_1 == pCfg->physUsed)
        {
            /* PHY 0, disabled */
            appObj->issOpenPrms.isCmplxIoCfgValid[0U] = FALSE;

            /* Enable PHY 1 and configure */
            appObj->issOpenPrms.isCmplxIoCfgValid[1U] = TRUE;
            appObj->issOpenPrms.csi2PhyClock[1U] =
                                    APP_CAPT_ISS_CAL_SENSOR_BYPASS_PHY_CLK_MHz;

            pCmplxIoCfg                = &appObj->issOpenPrms.cmplxIoCfg[1U];

            pCmplxIoCfg->enable        = TRUE;
            pCmplxIoCfg->clockLane.pol      = FALSE;
            pCmplxIoCfg->clockLane.position = 1U;
            pCmplxIoCfg->data1Lane.pol      = FALSE;
            pCmplxIoCfg->data1Lane.position = 2U;
            pCmplxIoCfg->data2Lane.pol      = FALSE;
            pCmplxIoCfg->data2Lane.position = 3U;
            pCmplxIoCfg->data3Lane.pol      = FALSE;
            pCmplxIoCfg->data3Lane.position = 0U;
            pCmplxIoCfg->data4Lane.pol      = FALSE;
            pCmplxIoCfg->data4Lane.position = 0U;
        }
    }

    for (streamId = 0U; streamId < appObj->numStream; streamId++)
    {
        createPrms->chNumMap[streamId][0U] =
            Vps_captMakeChNum(appObj->instId, streamId, 0U);
    }

    return;
}

static Int32 appCaptCreateDrv(appCaptObj_t *appObj)
{
    Int32 retVal = FVID2_SOK;

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
        retVal = appObj->createStatus.retVal;
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": CAL Capture created\r\n");

    return (retVal);
}

static Int32 appCaptDeleteDrv(appCaptObj_t *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamId;
    static Fvid2_FrameList frmList;

    for (streamId = 0U;
         streamId < appObj->createPrms.numStream;
         streamId++)
    {
        /* Dequeue all the request from the driver */
        while (1U)
        {
            retVal = Fvid2_dequeue(
                appObj->drvHandle,
                &frmList,
                streamId,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                break;
            }
            else
            {
                appCaptCountDQ(appObj, &frmList, streamId);
            }
        }
    }
    retVal = Fvid2_delete(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Delete Failed!!!\r\n");
    }
    else
    {
        appObj->drvHandle = NULL;
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Capture Driver deleted\r\n");

    return (retVal);
}

static Int32 appCaptSetDrvCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    UInt32 i;
    Int32  retVal = FVID2_SOK;
    appObj->numFramesToCapture = pCfg->numFrames;
    appObj->cfg.numStream      = pCfg->numStreams;
    for (i = 0; i < pCfg->numStreams; i++)
    {
        appObj->cfg.streamId[i] = i;

        appObj->cfg.inFmt[i].width  = pCfg->width;
        appObj->cfg.inFmt[i].height = pCfg->height;

        appObj->cfg.inFmt[i].pitch[0]   = pCfg->pitch;
        appObj->cfg.inFmt[i].bpp        = pCfg->inBpp;
        appObj->cfg.inFmt[i].dataFormat = 0x0U;
        appObj->cfg.csi2DataFormat[i]   = pCfg->inCsi2DataFormat;
        appObj->cfg.cmplxIoId[i]        = 0U;
        if (0 == i)
        {
            appObj->cfg.csi2VirtualChanNo[i] = pCfg->virtualChannel;
        }
        else if (1 == i)
        {
            appObj->cfg.csi2VirtualChanNo[i] = 1U;
        }
        else if (2 == i)
        {
            appObj->cfg.csi2VirtualChanNo[i] = 2U;
        }
        else
        {
            appObj->cfg.csi2VirtualChanNo[i] = 3U;
        }
        appObj->cfg.streamType[i] = VPS_ISS_CAL_TAG_PIX_DATA;

        appObj->cfg.isPixProcCfgValid[i] = FALSE;
        appObj->cfg.isBysOutCfgValid[i]  = FALSE;

        if (FVID2_VIFM_SCH_CPI == pCfg->interfaceType)
        {
            appObj->cfg.bysInEnable[0] = TRUE;
        }
        else
        {
            appObj->cfg.bysInEnable[i] = FALSE;
        }
        appObj->cfg.isVportCfgValid[i] = FALSE;

        appObj->cfg.writeToMem[i] = TRUE;

        if (((VPS_ISS_CAL_CSI2_RAW12 == pCfg->inCsi2DataFormat) ||
             (VPS_ISS_CAL_CSI2_RAW14 == pCfg->inCsi2DataFormat)) ||
            (VPS_ISS_CAL_CSI2_RAW10 == pCfg->inCsi2DataFormat))
        {
            appObj->cfg.pixProcCfg[i].extract = VPS_ISS_CAL_PIX_EXRCT_B14_MIPI;
            if (VPS_ISS_CAL_CSI2_RAW12 == pCfg->inCsi2DataFormat)
            {
                appObj->cfg.pixProcCfg[i].extract =
                    VPS_ISS_CAL_PIX_EXRCT_B12_MIPI;
            }
            if (VPS_ISS_CAL_CSI2_RAW10 == pCfg->inCsi2DataFormat)
            {
                appObj->cfg.pixProcCfg[i].extract =
                    VPS_ISS_CAL_PIX_EXRCT_B10_MIPI;
            }
            appObj->cfg.isPixProcCfgValid[i]   = TRUE;
            appObj->cfg.pixProcCfg[i].decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
            appObj->cfg.pixProcCfg[i].enableDpcmInitContext = FALSE;
            appObj->cfg.pixProcCfg[i].encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
            appObj->cfg.pixProcCfg[i].pack     = VPS_ISS_CAL_PIX_PACK_B16;
            /* Write in 16 bit container */
            appObj->cfg.inFmt[i].pitch[0] = appObj->cfg.inFmt[i].width * 2;
            appObj->cfg.inFmt[i].bpp      = FVID2_BPP_BITS16;

            if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId)
            {
                /* SAT0088 + OV10635 sends 10 bit YUV, the UB96x is configured
                    to forward MS 8bits only, hence extract and process 8 bits
                    only */
                appObj->cfg.pixProcCfg[i].extract = VPS_ISS_CAL_PIX_EXRCT_B8;
                appObj->cfg.pixProcCfg[i].pack    = VPS_ISS_CAL_PIX_PACK_B8;
            }
        }
        if ((FVID2_VID_SENSOR_BYPASS_CSI2_DRV == pCfg->sensorDrvId) &&
            (VPS_ISS_CAL_CSI2_RGB888 == pCfg->inCsi2DataFormat))
        {
            appObj->cfg.isPixProcCfgValid[i]   = FALSE;
            appObj->cfg.inFmt[i].pitch[0] = appObj->cfg.inFmt[i].width * 3;
            appObj->cfg.inFmt[i].bpp      = FVID2_BPP_BITS24;
            if (CAPT_APP_PHY_1 == pCfg->physUsed)
            {
                appObj->cfg.cmplxIoId[i] = 1U;
            }
        }
    }

    retVal = Fvid2_control(appObj->drvHandle, IOCTL_VPS_CAPT_SET_ISS_PARAMS,
                           &appObj->cfg, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Set CAL Params Failed!!!\r\n");
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": CAL Capture Configured\r\n");

    return (retVal);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 appCaptAllocAndQFrames(appCaptObj_t *appObj)
{
    Int32                  retVal = FVID2_SOK;
    UInt32                 streamId, idx;
    UInt32                 bufSize;
    Fvid2_Format           fmt;
    Fvid2_Frame           *pFrm;
    static Fvid2_FrameList frmList;
    static Char            fileStr[50U];

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < appObj->createPrms.numStream; streamId++)
    {
        Fvid2Format_init(&fmt);
        fmt.width      = appObj->maxWidth;
        fmt.height     = appObj->maxHeight;
        fmt.pitch[0]   = fmt.width * 2;
        fmt.bpp        = FVID2_BPP_BITS16;
        fmt.dataFormat = FVID2_DF_YUV422I_UYVY;

        idx = streamId * VPS_ISS_CAL_MAX_STREAMS;

        if (idx >= (CAPT_APP_FRAMES_PER_STREAM * VPS_ISS_CAL_MAX_STREAMS))
        {
            GT_assert(BspAppTrace, FALSE);
        }

        pFrm = (Fvid2_Frame *) &appObj->frames[idx];

        /* fill format with channel specific values  */
        fmt.chNum = Vps_captMakeChNum(appObj->instId, streamId, 0U);

        if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
        {
            BspUtils_memClearOnAlloc(TRUE);
        }

        /*
         * alloc memory based on 'format'
         * Allocated frame info is put in frames[]
         * CAPT_APP_FRAMES_PER_STREAM is the number of buffers per channel to
         * allocate
         */
        retVal = BspUtils_memFrameAlloc(&fmt, pFrm,
                                        CAPT_APP_FRAMES_PER_STREAM);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Frame Alloc Failed!!!\r\n");
            break;
        }

        snprintf(fileStr, sizeof (fileStr),
                 "captureOptionInst%uCh%uStr%u",
                 (unsigned int) appObj->instId,
                 (unsigned int) 0,
                 (unsigned int) streamId);
        BspUtils_memFrameGetSize(&fmt, &bufSize, NULL);
        BspOsal_cacheInv(pFrm[0].addr[0][0],
                         (CAPT_APP_FRAMES_PER_STREAM * bufSize),
                         BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
        BspUtils_appPrintSaveRawCmd(
            fileStr,
            pFrm[0].addr[0][0],
            fmt.dataFormat,
            fmt.width,
            fmt.height,
            (CAPT_APP_FRAMES_PER_STREAM * bufSize));

        /* Set number of frame in frame list */
        for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
        {
            /* Associate instance of sub-frame information structure with the
                frame */
            pFrm[idx].subFrameInfo = &appObj->subFrameInfo[idx];
            pFrm[idx].appData = appObj;

            frmList.frames[idx] = &pFrm[idx];
            GT_2trace(BspAppTrace, GT_INFO, APP_NAME ": Captured Frames [%d]"
                      " Available at 0x%x\r\n", idx, pFrm[idx].addr[0][0]);
        }

        frmList.numFrames = CAPT_APP_FRAMES_PER_STREAM;

        if (0x0 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][0]   = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][0]  = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][1U]  = 0U;
                appObj->dQCount[idx][1U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 0);
        }
        if (0x1 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][2U]  = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][2U] = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][3U]  = 0U;
                appObj->dQCount[idx][3U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 1);
        }
        if (0x2 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][4U]  = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][4U] = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][5U]  = 0U;
                appObj->dQCount[idx][5U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 2);
        }
        if (0x3 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][6U]  = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][6U] = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][7U]  = 0U;
                appObj->dQCount[idx][7U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 3);
        }
        /*
         * queue the frames in frmList
         * All allocated frames are queued here as an example.
         * In general atleast 2 frames per stream/channel need to queued
         * before capture can be started.
         * Failing which, frame could be dropped.
         */
        retVal = Fvid2_queue(appObj->drvHandle, &frmList, streamId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Queue Failed!!!\r\n");
            break;
        }
    }

    return (retVal);
}

static Int32 appCaptFreeFrames(appCaptObj_t *appObj)
{
    Int32                  retVal = FVID2_SOK;
    UInt32                 streamId, idx;
    Fvid2_Format           fmt;
    Fvid2_Frame           *pFrm;
    static Fvid2_FrameList frmList;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < appObj->createPrms.numStream; streamId++)
    {
        Fvid2Format_init(&fmt);
        fmt.width      = appObj->maxWidth;
        fmt.height     = appObj->maxHeight;
        fmt.pitch[0]   = fmt.width * 2;
        fmt.bpp        = FVID2_BPP_BITS16;
        fmt.dataFormat = FVID2_DF_YUV422I_UYVY;

        while (1U)
        {
            retVal = Fvid2_dequeue(
                appObj->drvHandle,
                &frmList,
                streamId,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                break;
            }
            else
            {
                appCaptCountDQ(appObj, &frmList, streamId);
            }
        }

        idx  = streamId * VPS_ISS_CAL_MAX_STREAMS;
        pFrm = (Fvid2_Frame *) &appObj->frames[idx];

        retVal = BspUtils_memFrameFree(&fmt, pFrm, CAPT_APP_FRAMES_PER_STREAM);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Frame Free Failed!!!\r\n");
        }

        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

static void appCaptCountQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                          UInt32 streamId)
{
    UInt32 frmIdx, frmAddr, cntIdx;
    for (frmIdx = 0U; frmIdx < frmList->numFrames; frmIdx++)
    {
        frmAddr = (Uint32) frmList->frames[frmIdx];
        for (cntIdx = 0U; cntIdx < CAPT_APP_FRAMES_PER_STREAM; cntIdx++)
        {
            if (0 == streamId)
            {
                if (appObj->qCount[cntIdx][0U] == frmAddr)
                {
                    appObj->qCount[cntIdx][1U]++;
                }
            }
            else if (1 == streamId)
            {
                if (appObj->qCount[cntIdx][2U] == frmAddr)
                {
                    appObj->qCount[cntIdx][3U]++;
                }
            }
            else if (2 == streamId)
            {
                if (appObj->qCount[cntIdx][4U] == frmAddr)
                {
                    appObj->qCount[cntIdx][5U]++;
                }
            }
            else
            {
                if (appObj->qCount[cntIdx][6U] == frmAddr)
                {
                    appObj->qCount[cntIdx][7U]++;
                }
            }
        }
    }
}

static void appCaptCountDQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                           UInt32 streamId)
{
    UInt32 frmIdx, frmAddr, cntIdx;
    for (frmIdx = 0U; frmIdx < frmList->numFrames; frmIdx++)
    {
        frmAddr = (Uint32) frmList->frames[frmIdx];
        for (cntIdx = 0U; cntIdx < CAPT_APP_FRAMES_PER_STREAM; cntIdx++)
        {
            if (0 == streamId)
            {
                if (appObj->dQCount[cntIdx][0U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][1U]++;
                }
            }
            else if (1 == streamId)
            {
                if (appObj->dQCount[cntIdx][2U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][3U]++;
                }
            }
            else if (2 == streamId)
            {
                if (appObj->dQCount[cntIdx][4U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][5U]++;
                }
            }
            else
            {
                if (appObj->dQCount[cntIdx][6U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][7U]++;
                }
            }
        }
    }
}

static void appCaptChkDQCounts(appCaptObj_t *appObj)
{
    UInt32 cntIdx, isError;
    isError = FALSE;
    for (cntIdx = 0U; cntIdx < CAPT_APP_FRAMES_PER_STREAM; cntIdx++)
    {
        if (appObj->dQCount[cntIdx][0U] != appObj->qCount[cntIdx][0U])
        {
            isError = TRUE;
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR Q / DQ address are not in order [%d]!!!\r\n",
                cntIdx);
        }
        if (appObj->dQCount[cntIdx][1U] != appObj->qCount[cntIdx][1U])
        {
            isError = TRUE;
            GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                      ": ERROR Q / DQ counts do not match up [%d]!!!\r\n", cntIdx);
        }
        if (appObj->dQCount[cntIdx][2U] != appObj->qCount[cntIdx][2U])
        {
            isError = TRUE;
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR Q / DQ address are not in order [%d] - Stream 1!!!\r\n",
                cntIdx);
        }
        if (appObj->dQCount[cntIdx][3U] != appObj->qCount[cntIdx][3U])
        {
            isError = TRUE;
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR Q / DQ counts do not match up [%d] - Stream 1!!!\r\n",
                cntIdx);
        }
    }
    if (FALSE == isError)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Q/Dq Counts match up\r\n");
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Q/Dq Order match\r\n");
    }
}

/**
 *  appCaptGetTestId
 *  Return the test ID to run.
 */
static Int32 appCaptGetTestId(appCaptObj_t *appObj)
{
    UInt32       testCnt;
    static Int32 testId = 0;

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "Select test to run as per below table:\r\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    for (testCnt = 0; testCnt < APP_CAPT_NUM_OPTS; testCnt++)
    {
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) ||
            (BSP_PLATFORM_SOC_ID_TDA2PX == Bsp_platformGetSocId()))
        {
            GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\r\n", testCnt, gTestCfg[testCnt].testDescStr);
        }
        else
        {
            if (CAPT_APP_PHY_1 != (gTestCfg[testCnt].physUsed & CAPT_APP_PHY_1))
            {
                GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\r\n", testCnt, gTestCfg[testCnt].testDescStr);
            }
        }
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\r\n", APP_CAPT_NUM_OPTS, "Auto Run\r\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run (in UART console): \r\n");

    while (1U)
    {
        BspUtils_uartGetNum(&testId, BSP_UTILS_UART_RX_WAIT_FOREVER);
        GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
        if ((testId >= 0) && (testId < APP_CAPT_NUM_OPTS))
        {
            break;
        }
        else if (100 == testId)
        {
            break;
        }
        GT_0trace(BspAppTrace, GT_INFO, "Invalid Test ID. Enter Agian!!\r\n");
    }

    return (testId);
}

/**
 *  \brief Sets up the EVM / Board specifics, configures the sensor for a given
 *          config and enables sensor to stream.
 */
static Int32 appCaptcreateVidSensor(appCaptObj_t *instObj, appCaptCfg_t *pCfg)
{
    Int32  retVal;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr, idx;
    Bsp_VidSensorChipIdParams   sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus   sensorChipIdStatus;
    Bsp_VidSensorCreateStatus   sensorCreateStatus;
    Bsp_VidSensorConfigParams   configParams;
    BspUtils_Ub960Status        ub960Status;
    BspUtils_Ub960SourceI2cAddr ub960I2cAddr;

    BspUtils_memset(&ub960I2cAddr, 0x0, sizeof (ub960I2cAddr));
    sensorInstId = Bsp_boardGetVideoDeviceInstId(
        instObj->testPrms.sensorDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    sensorI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        instObj->testPrms.sensorDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        instObj->testPrms.sensorDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);

    if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId))
    {
        ub960I2cAddr.slaveAddr       = UB960_SLAVE_ADDR;
        ub960I2cAddr.numSource       = pCfg->numStreams;

        for (idx = 0U; idx < pCfg->numStreams; idx++)
        {
            sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
                instObj->testPrms.sensorDrvId,
                FVID2_VPS_CAPT_VID_DRV,
                instObj->instId + idx);
            ub960I2cAddr.rSlave2Addr[idx] = sensorI2cAddr;
            if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
            {
                ub960I2cAddr.rSlave1Addr[idx] =
                                            BspUtils_getSerAddrTida00262(idx);
            }
            else if (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId)
            {
                ub960I2cAddr.rSlave1Addr[idx] = BspUtils_getSerAddrIMI(idx);
            }
            else
            {
                ub960I2cAddr.rSlave1Addr[idx] =
                                            BspUtils_getSerAddrSat0088(idx);
            }
        }

        sensorI2cAddr = ub960I2cAddr.rSlave2Addr[0U];
        retVal        = BspUtils_appInitUb960(0U,
                                pCfg->sensorDrvId,
                                &ub960I2cAddr,
                                &ub960Status);
        if (FVID2_SOK == retVal)
        {
            if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
            {
                GT_1trace(BspAppTrace, GT_INFO,
                                        "Detected 0x%x TIDA00262 modules\r\n",
                                        ub960Status.numDetected);
            }
            else if (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId)
            {
                GT_1trace(BspAppTrace, GT_INFO,
                                        "Detected 0x%x IMI modules\r\n",
                                        ub960Status.numDetected);
            }
            else
            {
                GT_1trace(BspAppTrace, GT_INFO,
                                        "Detected 0x%x SAT0088 modules\r\n",
                                        ub960Status.numDetected);
            }
        }
        else
        {
            GT_0trace(BspAppTrace, GT_ERR, "Failed to initialize UB960 !!!\r\n");
        }
    }

    GT_3trace(BspAppTrace, GT_INFO,
              "Sensor Inst ID-%d-Sensor I2C Inst ID %d,sensorI2cAddr: 0x%x\r\n",
              sensorInstId,
              sensorI2cInstId, sensorI2cAddr);

    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        Bsp_boardSetPinMux(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ISS_CAL_A_CPI,
            instObj->testPrms.boardMode);
    }

    if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV != pCfg->sensorDrvId)
    {
        /* Power on video sensor at board level mux */
        retVal = Bsp_boardPowerOnDevice(instObj->testPrms.sensorDrvId,
                                        sensorInstId, TRUE);
    }

    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device power-on failed\r\n");
    }

    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        if (FVID2_SOK == retVal)
        {
            /* select video sensor at board level mux */
            retVal = Bsp_boardSelectDevice(instObj->testPrms.sensorDrvId,
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
                instObj->testPrms.sensorDrvId,
                sensorInstId,
                instObj->testPrms.boardMode);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\r\n");
            }
        }
    }

    for (idx = 0U; ((idx < pCfg->numStreams) && (FVID2_SOK == retVal)); idx++)
    {
        if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId) ||
            (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId))
        {
            sensorI2cAddr = ub960I2cAddr.rSlave2Addr[idx];
            if (BSPUTILS_UB960EVM_NO_SOURCE_DETECTED ==
                ub960Status.portNum[idx])
            {
                instObj->sensorHandle[idx] = NULL;
                continue;
            }
        }

        instObj->sensorCreatePrms.deviceI2cInstId    = sensorI2cInstId;
        instObj->sensorCreatePrms.numDevicesAtPort   = 1U;
        instObj->sensorCreatePrms.deviceI2cAddr[0]   = sensorI2cAddr;
        instObj->sensorCreatePrms.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
        instObj->sensorCreatePrms.sensorCfg          = NULL;
        instObj->sensorCreatePrms.numSensorCfg       = 0U;

        instObj->sensorHandle[idx] = Fvid2_create(
            instObj->testPrms.sensorDrvId,
            sensorInstId,
            &instObj->sensorCreatePrms,
            &sensorCreateStatus,
            NULL);
        GT_assert(BspAppTrace, instObj->sensorHandle[idx] != NULL);

        sensorChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->sensorHandle[idx],
            IOCTL_BSP_VID_SENSOR_GET_CHIP_ID,
            &sensorChipIdPrms,
            &sensorChipIdStatus);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        GT_6trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": CAL DrvInstId %d: VID SENSOR %04x (0x%02x): %04x:%04x:%04x\r\n",
            instObj->instId,
            instObj->testPrms.sensorDrvId,
            instObj->sensorCreatePrms.deviceI2cAddr[0],
            sensorChipIdStatus.chipId,
            sensorChipIdStatus.chipRevision,
            sensorChipIdStatus.firmwareVersion);

        configParams.videoIfWidth = instObj->testPrms.interfacewidth;
        configParams.dataformat   = instObj->testPrms.dataFormat;
        configParams.standard     = instObj->testPrms.standard;
        configParams.fps          = FVID2_FPS_30;
        configParams.bpp          = instObj->testPrms.bpp;

        if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId)
        {
            /* Sensor driver dosen't really apply these parameters YET!!! */
            configParams.videoIfWidth = FVID2_VIFW_8BIT;
            configParams.dataformat   = FVID2_DF_YUV422I_YUYV;
            configParams.standard     = FVID2_STD_720P_60;
            configParams.fps          = FVID2_FPS_30;
            configParams.bpp          = FVID2_BPP_BITS10;
        }
        retVal =
            Fvid2_control(instObj->sensorHandle[idx],
                          IOCTL_BSP_VID_SENSOR_SET_CONFIG,
                          &configParams,
                          NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        /* start sensor, right now only OV sensor driver is implemented */
        retVal = Fvid2_control(instObj->sensorHandle[idx], FVID2_START, NULL,
                               NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));
    }

    /* If interface is CSI2, print the number of lanes configured in sensor */
    if ((FVID2_SOK == retVal) &&
        (FVID2_VID_SENSOR_OV10640_CSI2_DRV == pCfg->sensorDrvId))
    {
        Bsp_VidSensorRegRdWrParams rdParams;
        /* MIPI_CTRL04 */
        UInt16 regAddr = 0x3444;
        UInt16 regValue = 0x0;

        rdParams.deviceNum = 0U;
        rdParams.numRegs   = 1U;
        rdParams.regAddr   = &regAddr;
        rdParams.regValue16 = &regValue;
        rdParams.regValue8  = NULL;

        retVal = Fvid2_control(instObj->sensorHandle[0],
                               IOCTL_BSP_VID_SENSOR_REG_READ,
                               &rdParams,
                               NULL);
        if (FVID2_SOK == retVal)
        {
            GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                      ": CSI2 streaming on %d lanes !!!\r\n", regValue >> 4U);
        }
    }
    return (retVal);
}

static Int32 appCaptDeleteVidSensor(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 idx;

    for (idx = 0U; idx < appObj->createPrms.numStream; idx++)
    {
        if (NULL != appObj->sensorHandle[idx])
        {
            retVal = Fvid2_delete(appObj->sensorHandle[idx], NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Sensor Delete Failed!!!\r\n");
            }
            else
            {
                appObj->sensorHandle[idx] = NULL;
            }
        }
    }
    if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == pCfg->sensorDrvId) ||
        (FVID2_VID_SENSOR_IMI_OV10640_DRV == pCfg->sensorDrvId))
    {
        for (idx = 0U; ((idx < appObj->createPrms.numStream) &&
                (FVID2_VID_SENSOR_MULDES_OV1063X_DRV != pCfg->sensorDrvId));
                    idx++)
        {
            retVal = BspUtils_appDeInitUB913Ser(0U, idx, pCfg->sensorDrvId);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(BspAppTrace, GT_ERR, "Failed to Reset "
                          "TIDA00262 at port 0x%x!!!\r\n", idx);
            }
        }
        retVal = BspUtils_appDeInitUb960(0U, pCfg->sensorDrvId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Failed to De Initialize "
                      "UB960 !!!\r\n");
        }
    }

    return (retVal);
}

static void appCaptPrintStatistics(appCaptObj_t *appObj,
                                   UInt32        execTimeInMsecs)
{
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " Execution Statistics \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " ==================== \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Execution time    : %d.%d s \r\n",
              (execTimeInMsecs / 1000), (execTimeInMsecs % 1000));
    GT_2trace(BspAppTrace, GT_INFO,
              " Total Frame Count : %d (%d fields/sec) \r\n",
              appObj->totalFrmCount,
              (appObj->totalFrmCount * 1000) / execTimeInMsecs);
    GT_1trace(BspAppTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              appObj->totalCpuLoad / appObj->cpuLoadCount);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    /* Print the driver status */
    BspUtils_appPrintCaptStatus(
        appObj->drvHandle,
        appObj->instId,
        appObj->createPrms.numStream,
        appObj->createPrms.numCh,
        execTimeInMsecs);

    GT_2trace(BspAppTrace, GT_INFO,
              " Capture Inst %d Status: Number of Frames with CRC Errors  : "
              "%d\r\n",
              appObj->instId,
              appObj->frameWithCrcErrorCnt);
    GT_2trace(BspAppTrace, GT_INFO,
              " Capture Inst %d Status: Number of Frames with ECC warning  : "
              "%d\r\n",
              appObj->instId,
              appObj->frameWithWarning);
    GT_2trace(BspAppTrace, GT_INFO,
              " Capture Inst %d Status: Number of Frames with un-handled error"
              ": %d\r\n",
              appObj->instId,
              appObj->frameErrorCnt);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    return;
}

static void appCaptErrCb(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    uint32_t idx;
    appCaptObj_t *pAppObj = (appCaptObj_t *)arg;
    for (idx = 0U; idx < numEvents; idx++)
    {
        if (VPS_CAL_CSI2_PPI_VC_SOF1 == event[idx])
        {
            pAppObj->sofIntCount++;
        }
        else if ((VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1 == event[idx]) ||
                 (VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC2 == event[idx]) ||
                 (VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC3 == event[idx]) ||
                 (VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC4 == event[idx]))
        {
            pAppObj->crcErrIntCnt++;
        }
        else if ((VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1 == event[idx]) ||
                 (VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC2 == event[idx]) ||
                 (VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC3 == event[idx]) ||
                 (VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC4 == event[idx]))
        {
            pAppObj->eccErrIntCnt++;
        }
        else
        {
            pAppObj->unExpectedIntCnt++;
        }
    }
}

static Int32 appCaptEnableErrorReporting(appCaptObj_t *appObj,
                                        appCaptCfg_t *pCfg)
{
    Int32 retVal;
    vpsissCalErrorCfg_t errCfg;

    errCfg.numErrorsToMonitor = 8U;
    errCfg.cmplxIoId = 0U;
    if ((FVID2_VID_SENSOR_BYPASS_CSI2_DRV == pCfg->sensorDrvId) &&
        (CAPT_APP_PHY_1 == pCfg->physUsed))
    {
        errCfg.cmplxIoId = 1U;
    }

    errCfg.errSrc[0U] = VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1;
    errCfg.errSrc[1U] = VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC2;
    errCfg.errSrc[2U] = VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC3;
    errCfg.errSrc[3U] = VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC4;
    errCfg.errSrc[4U] = VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1;
    errCfg.errSrc[5U] = VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC2;
    errCfg.errSrc[6U] = VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC3;
    errCfg.errSrc[7U] = VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC4;

    errCfg.appCb = &appCaptErrCb;
    errCfg.pAppCbArgs = (Ptr)appObj;

    retVal = Fvid2_control(appObj->drvHandle, IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS,
                           &errCfg, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Set CAL Params Failed!!!\r\n");
    }
    return retVal;
}

static void appCaptCustomSensorConfig(void)
{
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                                    ": No custom sensors programmed!!!\r\n");
    return ;
}

static Int32 appCaptFrameEventNotifyCb(Fvid2_Handle handle, Fvid2_Frame *pFrame)
{
    appCaptObj_t *appObj;
    UInt32 streamId, idx;
    UInt32 static tsFrameEvents = 1U;

    GT_assert(BspAppTrace, (handle != NULL));
    GT_assert(BspAppTrace, (pFrame != NULL));
    GT_assert(BspAppTrace, (pFrame->subFrameInfo != NULL));
    GT_assert(BspAppTrace, (pFrame->appData != NULL));

    streamId = Vps_captGetStreamId(pFrame->chNum);
    appObj = (appCaptObj_t *)pFrame->appData;

    if ((CAPT_APP_NTH_LINE_FRAME_EVENT == pFrame->subFrameInfo->subFrameNum) &&
        (1U == tsFrameEvents))
    {
        idx = appObj->nLineEventIdx;
        appObj->nLineInfo[idx].subFrameNum  =
                                        pFrame->subFrameInfo->subFrameNum;
        appObj->nLineInfo[idx].numInLines   =
                                        pFrame->subFrameInfo->numInLines;
        appObj->nLineInfo[idx].numOutLines  =
                                        pFrame->subFrameInfo->numOutLines;
        appObj->nLineEventTs[idx] = BspOsal_getCurTimeInMsec();

        idx++;
        if (idx >= CAPT_APP_FRAMES_PER_STREAM)
        {
            idx = 0U;
        }
        appObj->nLineEventIdx = idx;
    }
    if ((CAPT_APP_END_OF_FRAME_EVENT == pFrame->subFrameInfo->subFrameNum) &&
        (1U == tsFrameEvents))
    {
        if (4U > streamId)
        {
            idx = appObj->eofEventIdx[streamId];
            appObj->eofEventFrameAddr[idx][streamId] = (UInt32)pFrame;
            appObj->eofEventTs[idx][streamId] = BspOsal_getCurTimeInMsec();
            idx++;
            if (idx >= CAPT_APP_FRAMES_PER_STREAM)
            {
                idx = 0U;
            }
            appObj->eofEventIdx[streamId] = idx;
        }
        if (1U != appObj->frameEventTrack)
        {
            tsFrameEvents = 0U;
        }
    }

    return (FVID2_SOK);
}

static Int32 appCaptEnableFrameEventNotification(appCaptObj_t *appObj,
                                                    appCaptCfg_t *pCfg)
{
    UInt32 streamId;
    vpsissCalFrameEventNotifyCfg_t ntyCfg;
    Int32 retVal = FVID2_SOK;

        ntyCfg.numStream = 0U;
        for (streamId = 0U; streamId < pCfg->numStreams; streamId++)
        {
            ntyCfg.streamId[streamId] = streamId;
            if (CAPT_APP_NTH_LINE_STREAM_ID == streamId)
            {
                ntyCfg.notifyAfterFirstXLines[streamId] = 200U;
            }
            else
            {
                ntyCfg.notifyAfterFirstXLines[streamId] = 0U;
            }
            ntyCfg.notifyAfterEndOfFrame[streamId] = TRUE;
            ntyCfg.numStream++;
        }

        ntyCfg.appCb = &appCaptFrameEventNotifyCb;
        ntyCfg.pAdditionalArgs = NULL;

        retVal = Fvid2_control(appObj->drvHandle,
                            IOCTL_VPS_CAPT_SET_FRAME_EVENT_NOTIFY_PRMS, &ntyCfg, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
            APP_NAME ": Capture Set CAL Frame Event Notification "
                     "Failed!!!\r\n");
        }
    return retVal;
}

static void appCaptChkFrameEvents(appCaptObj_t *appObj)
{
    UInt32 idx;
    /* Check the order in which events were reported */
    for (idx = 0U; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
    {
        if (appObj->dQCount[idx][0U] != appObj->eofEventFrameAddr[idx][0])
        {
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR DQ/EOF Frame address are not in order [%d]!!!\r\n",
                idx);
            break;
        }
    }

}
