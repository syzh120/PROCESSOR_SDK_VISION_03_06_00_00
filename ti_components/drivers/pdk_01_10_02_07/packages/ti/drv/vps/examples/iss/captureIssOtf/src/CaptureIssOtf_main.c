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
 *  \file CaptureIssOtf_main.c
 *
 *  \brief ISS Capture demo application - Receives via CSI2/Parallel and
 *          write to memory
 *         Most board / EVM specifics are handled in function
 *          appCaptcreateVidSensor () In addition to configuring the sensor
 *          for the given config and enable sensor to stream.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CaptureIssOtf_main.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< CSI2 PHY Clock OV10640
 *      For a 15X15 Package TDA3MAx(15x15), TDA3LAx(15x15), TDA3LRx(15x15). */
#define APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz (400U)

/**< CSI2 PHY Clock IMX224 */
#define APP_CAPT_ISS_CAL_IMX224_PHY_CLK_MHz (150U)

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
static Int32 appCaptAllocAndQFrames(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptFreeFrames(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptChkTimeStamps(appCaptObj_t *appObj);
static Int32 appCaptGetTestId(appCaptObj_t *appObj);
static Int32 appCaptcreateVidSensor(appCaptObj_t *instObj);
static void appCaptPrintStatistics(appCaptObj_t *appObj,
                                   UInt32        execTimeInMsecs);

static Int32 appCaptCheckMakeStrmMap(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptSetOtfStrmMap(appCaptObj_t *appObj);
static Int32 appCaptSetIpipeCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptSetRszCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptSetIsifCfg(appCaptObj_t *appObj);
static Int32 appCaptSetCnfCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptSetH3aCfg(appCaptObj_t *appObj);
static Int32 appCaptSetGlbceCfg(appCaptObj_t *appObj);
static Int32 appCaptSetNsf3vCfg(appCaptObj_t *appObj);
static Int32 appCaptSetIssStreamPri(appCaptObj_t *appObj, appCaptCfg_t *pCfg,
                                    UInt32 restore);

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
    {"OV10640 Parallel over LI i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ByPass : NSF3 ByPass",
     0U, TRUE, FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CPI_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_DISABLED, VPS_ISS_NSF3_PATH_DISABLED,
     FVID2_DF_YUV420SP_UV, FALSE},

    {"OV10640 Parallel over LI i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ISP : NSF3 ByPass",
     0U, TRUE, FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CPI_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_ISP, VPS_ISS_NSF3_PATH_DISABLED,
     FVID2_DF_YUV420SP_UV, TRUE},

    {"OV10640 Parallel over LI i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ByPass : NSF3 ISP",
     0U, TRUE, FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CPI_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_DISABLED, VPS_ISS_NSF3_PATH_ISP,
     FVID2_DF_YUV420SP_UV, TRUE},

    {"OV10640 Parallel over LI i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ISP : NSF3 ISP",
     0U, TRUE, FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CPI_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_ISP, VPS_ISS_NSF3_PATH_ISP,
     FVID2_DF_YUV420SP_UV, TRUE},

    {"OV10640 CSI2 4Lanes i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE CAL : NSF3 ByPass",
     0U, TRUE, FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_CAL, VPS_ISS_NSF3_PATH_DISABLED, FVID2_DF_YUV420SP_UV,
     TRUE},

    {"OV10640 CSI2 4Lanes i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ISP : NSF3 ByPass",
     0U, TRUE, FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_ISP, VPS_ISS_NSF3_PATH_DISABLED, FVID2_DF_YUV420SP_UV,
     FALSE},

    {"OV10640 CSI2 4Lanes i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ByPass : NSF3 ISP",
     0U, TRUE, FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_DISABLED, VPS_ISS_NSF3_PATH_ISP, FVID2_DF_YUV420SP_UV,
     FALSE},

    {"OV10640 CSI2 4Lanes i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ByPass : NSF3 CAL",
     0U, TRUE, FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_DISABLED, VPS_ISS_NSF3_PATH_CAL, FVID2_DF_YUV420SP_UV,
     TRUE},

    {"OV10640 CSI2 4Lanes i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE CAL : NSF3 ISP",
     0U, TRUE, FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_CAL, VPS_ISS_NSF3_PATH_ISP, FVID2_DF_YUV420SP_UV,
     TRUE},

    {"OV10640 CSI2 4Lanes i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x720 "
     "GLBCE ISP : NSF3 CAL",
     0U, TRUE, FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_ISP, VPS_ISS_NSF3_PATH_CAL, FVID2_DF_YUV420SP_UV,
     TRUE},

    {"APT AR0140 Parallel i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x800 "
     "GLBCE ByPass : NSF3 ByPass",
     1U, TRUE, FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 800U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0140_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_DISABLED, VPS_ISS_NSF3_PATH_DISABLED,
     FVID2_DF_YUV420SP_UV, FALSE},

    {"APT AR0140 Parallel i/f, RAW12 "
     "& convert it to YUV using ISP - 1280x800 "
     "GLBCE ByPass : NSF3 ISP",
     1U, TRUE, FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 800U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0140_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT, VPS_CAPT_INST_ISS_CAL_A_OTF,
     VPS_ISS_GLBCE_PATH_ISP, VPS_ISS_NSF3_PATH_ISP,
     FVID2_DF_YUV420SP_UV, FALSE},
};

static vpsissNsf3Config_t gIssHalNsf3DefCfg_Cnf;

/**< Number of options supported */
#define APP_CAPT_NUM_OPTS              (sizeof (gTestCfg) / \
                                        sizeof (gTestCfg[0U]))

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
    UInt32 testId, temp;

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
        else if (testId == APP_CAPT_NUM_OPTS)
        {
            for (testId = 0U; testId < APP_CAPT_NUM_OPTS; testId++)
            {
                GT_1trace(BspAppTrace, GT_INFO,
                          "Capture via %s\r\n", gTestCfg[testId].testDescStr);
                BspUtils_memGetHeapStat(&startHeapStat1);

                appCapture4GivenConfig(
                    appObj,
                    &gTestCfg[testId]);

                BspUtils_memCheckHeapStat(&startHeapStat1);
                temp = 0U;
                Bsp_printf("Press any number to continue...\r\n\n");
                while (TRUE)
                {
                    BspOsal_scanf("%d", &temp);
                    if (temp > 0U)
                    {
                        break;
                    }
                }
            }
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
    UInt32          startTime, endTime;
    volatile UInt32 lastFrameNo = 0;

    /* Print test case information */
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Configured to capture %d frames \r\n",
              pCfg->numFrames);
    BspUtils_memcpy(&appObj->testPrms, pCfg, sizeof (appCaptCfg_t));

    appObj->instId = pCfg->calInstId;

    appObj->expectedFrameRate = FVID2_FPS_MAX;
    /* Calculates number of streams required based on useage of GLBCE & NSF3 */
    retVal = appCaptCheckMakeStrmMap(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        return;
    }

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

    if (VPS_CAPT_INST_ISS_CAL_A_OTF == appObj->instId)
    {
        retVal = appCaptSetOtfStrmMap(appObj);
        if (FVID2_SOK != retVal)
        {
            return;
        }
        retVal = appCaptSetIpipeCfg(appObj, pCfg);
        if (FVID2_SOK != retVal)
        {
            return;
        }

        retVal = appCaptSetRszCfg(appObj, pCfg);
        if (FVID2_SOK != retVal)
        {
            return;
        }

        retVal = appCaptSetIsifCfg(appObj);
        if (FVID2_SOK != retVal)
        {
            return;
        }

        if (TRUE == appObj->enableCnf)
        {
            retVal = appCaptSetCnfCfg(appObj, pCfg);
            if (FVID2_SOK != retVal)
            {
                return;
            }
        }

        retVal = appCaptSetH3aCfg(appObj);
        if (FVID2_SOK != retVal)
        {
            return;
        }

        retVal = appCaptSetGlbceCfg(appObj);
        if (FVID2_SOK != retVal)
        {
            return;
        }

        retVal = appCaptSetNsf3vCfg(appObj);
        if (FVID2_SOK != retVal)
        {
            return;
        }

        retVal = appCaptSetIssStreamPri(appObj, pCfg, FALSE);
        if (FVID2_SOK != retVal)
        {
            return;
        }
    }

    retVal = appCaptAllocAndQFrames(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptcreateVidSensor(appObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Failed to configure the sensor!!!\r\n");
        return;
    }

    appObj->rcvedFramesCount = 0x0;
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
    while (appObj->rcvedFramesCount < appObj->numFramesToCapture)
    {
        if ((0U == lastFrameNo) && (appObj->rcvedFramesCount))
        {
            lastFrameNo = appObj->rcvedFramesCount;
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Stream Detected!!!\r\n");
        }
    }

    retVal = Fvid2_stop(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\r\n");
        return;
    }
    endTime = BspOsal_getCurTimeInMsec();

    appCaptPrintStatistics(appObj, endTime - startTime);

    retVal = appCaptSetIssStreamPri(appObj, pCfg, TRUE);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    /* Check if the frame interval reception is within 10% of the average
     *  frame interval */
    retVal = appCaptChkTimeStamps(appObj);
    retVal = appCaptFreeFrames(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\r\n");
        return;
    }

    retVal = appCaptDeleteDrv(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
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
    UInt32 streamId, frmNo;
    static Fvid2_FrameList frmList;
    appCaptObj_t          *appObj = (appCaptObj_t *) appData;
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
            if (appObj->rszOutStrmId == streamId)
            {
                for (frmNo = 0; ((frmNo < frmList.numFrames) &&
                                 (CAPT_APP_RUN_COUNT > appObj->tsIdx)); frmNo++)
                {
                    appObj->ts[appObj->tsIdx++] =
                        frmList.frames[frmNo]->timeStamp;
                }
            }

            retVal = Fvid2_queue(appObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Queue Failed!!!\r\n");
            }
        }
        if (appObj->rszOutStrmId == streamId)
        {
            appObj->rcvedFramesCount += frmList.numFrames;
        }
        appObj->totalFrmCount += frmList.numFrames;
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

    appObj->totalFrmCount = 0U;
    appObj->totalCpuLoad  = 0U;
    appObj->cpuLoadCount  = 0U;

    appObj->instId    = pCfg->calInstId;
    appObj->drvHandle = NULL;
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn   = &appCaptCb;
    appObj->cbPrms.appData = appObj;

    pCfg->numStreams  = appObj->otfStrmMap.numStream + appObj->numCalStreams;
    appObj->numStream = pCfg->numStreams;
    GT_assert(BspAppTrace, ((0U < pCfg->numStreams) &&
                            (pCfg->numStreams < VPS_ISS_CAL_MAX_STREAMS)));

    BspUtils_memset(&appObj->issOpenPrms, 0x0,
                    sizeof (Vps_CaptIssOpenParams_t));

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

    if (VPS_CAPT_INST_ISS_CAL_A_OTF == appObj->instId)
    {
        /* The stream will not be written out, instead will be sent out via
         *  VPORT to ISP */
        appObj->issOpenPrms.subModules[0U] &= ~VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID;
        appObj->issOpenPrms.subModules[0U] |= VPS_ISS_CAPT_CAL_SUB_VPORT_ID;

        if ((VPS_ISS_GLBCE_PATH_CAL == pCfg->glbcePath) ||
            (VPS_ISS_NSF3_PATH_CAL == pCfg->nsf3Path))
        {
            /* Captured stream will be sent out to NSF3 / GLBCE via BYS Out
             *  and brought back in via BYS IN */
            appObj->issOpenPrms.subModules[0U] &=
                ~VPS_ISS_CAPT_CAL_SUB_VPORT_ID;
            appObj->issOpenPrms.subModules[0U] |=
                VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID;

            appObj->issOpenPrms.subModules[1U] =
                (VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID |
                 VPS_ISS_CAPT_CAL_SUB_VPORT_ID |
                 VPS_ISS_CAPT_CAL_SUB_CPORT_ID);
        }

        BspUtils_memset(&appObj->ispOpenPrms, 0x0,
                        sizeof (vpsissIspOpenParams_t));
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = TRUE;
        appObj->ispOpenPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = FALSE;
        /* OTF Check */

        appObj->issOpenPrms.otfOpenPrms = &appObj->ispOpenPrms;

        appObj->enableCnf   = FALSE;
        appObj->enableDpc   = FALSE;
        appObj->enableLsc   = FALSE;
        appObj->enableGic   = FALSE;
        appObj->enableYee   = FALSE;
        appObj->enable3dLut = FALSE;
        appObj->enableGamma = FALSE;
        appObj->enableNf1   = FALSE;
        appObj->enableNf2   = FALSE;
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

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": ISS Capture created\r\n");

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

    if (NULL != appObj->sensorHandle)
    {
        retVal = Fvid2_delete(appObj->sensorHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Sensor Delete Failed!!!\r\n");
        }
        else
        {
            appObj->sensorHandle = NULL;
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Capture Driver deleted\r\n");

    return (retVal);
}

static Int32 appCaptSetDrvCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    UInt32 index, ispStartNo;
    Int32  retVal = FVID2_SOK;
    appObj->numFramesToCapture = pCfg->numFrames;

    appObj->cfg.numStream       = pCfg->numStreams;
    appObj->cfg.streamId[0]     = 0U;
    appObj->cfg.inFmt[0].width  = pCfg->width;
    appObj->cfg.inFmt[0].height = pCfg->height;

    appObj->cfg.inFmt[0].pitch[0]    = pCfg->pitch;
    appObj->cfg.inFmt[0].bpp         = pCfg->inBpp;
    appObj->cfg.inFmt[0].dataFormat  = 0x0U;
    appObj->cfg.csi2DataFormat[0]    = pCfg->inCsi2DataFormat;
    appObj->cfg.csi2VirtualChanNo[0] = pCfg->virtualChannel;
    appObj->cfg.streamType[0]        = VPS_ISS_CAL_TAG_PIX_DATA;

    appObj->cfg.isPixProcCfgValid[0] = FALSE;
    appObj->cfg.isBysOutCfgValid[0]  = FALSE;

    if (FVID2_VIFM_SCH_CPI == pCfg->interfaceType)
    {
        appObj->cfg.bysInEnable[0] = TRUE;
    }
    else
    {
        appObj->cfg.bysInEnable[0] = FALSE;
    }
    appObj->cfg.isVportCfgValid[0] = FALSE;

    appObj->cfg.writeToMem[0] = TRUE;

    if (((VPS_ISS_CAL_CSI2_RAW12 == pCfg->inCsi2DataFormat) ||
         (VPS_ISS_CAL_CSI2_RAW14 == pCfg->inCsi2DataFormat)) ||
        (VPS_ISS_CAL_CSI2_RAW10 == pCfg->inCsi2DataFormat))
    {
        appObj->cfg.pixProcCfg[0].extract = VPS_ISS_CAL_PIX_EXRCT_B14_MIPI;
        if (VPS_ISS_CAL_CSI2_RAW12 == pCfg->inCsi2DataFormat)
        {
            appObj->cfg.pixProcCfg[0].extract = VPS_ISS_CAL_PIX_EXRCT_B12_MIPI;
        }
        if (VPS_ISS_CAL_CSI2_RAW10 == pCfg->inCsi2DataFormat)
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
        appObj->cfg.inFmt[0].bpp      = FVID2_BPP_BITS16;
    }

    if (VPS_CAPT_INST_ISS_CAL_A_OTF == appObj->instId)
    {
        appObj->cfg.writeToMem[0] = FALSE;

        appObj->cfg.isVportCfgValid[0]    = TRUE;
        appObj->cfg.vportCfg[0U].enable   = TRUE;
        appObj->cfg.vportCfg[0U].pixClock = 32768U;

        appObj->cfg.vportCfg[0U].width   = 1U;
        appObj->cfg.vportCfg[0U].xBlk    = 0x4U;
        appObj->cfg.vportCfg[0U].yBlk    = 0x3CU;
        appObj->cfg.vportCfg[0U].rdyThr  = 0U;
        appObj->cfg.vportCfg[0U].fsReset = TRUE;

        if ((VPS_ISS_GLBCE_PATH_CAL == pCfg->glbcePath) ||
            (VPS_ISS_NSF3_PATH_CAL == pCfg->nsf3Path))
        {
            appObj->cfg.writeToMem[0U]                   = FALSE;
            appObj->cfg.isVportCfgValid[0U]              = FALSE;
            appObj->cfg.vportCfg[0U].enable              = FALSE;
            appObj->cfg.isBysOutCfgValid[0U]             = TRUE;
            appObj->cfg.bysOutCfg[0U].enable             = TRUE;
            appObj->cfg.bysOutCfg[0U].pixClock           = 16384U;
            appObj->cfg.bysOutCfg[0U].yBlk               = 0x18U;
            appObj->cfg.bysOutCfg[0U].xBlk               = 0x4U;
            appObj->cfg.bysOutCfg[0U].copyStreamToEncode = FALSE;
            appObj->cfg.bysOutCfg[0U].freeRun            = FALSE;

            appObj->cfg.streamId[1U]       = 1U;
            appObj->cfg.csi2DataFormat[1U] =
                VPS_ISS_CAL_CSI2_DISABLE_CONTEXT;
            appObj->cfg.csi2VirtualChanNo[1U] = 0U;
            appObj->cfg.streamType[1U]        = VPS_ISS_CAL_TAG_MAX;
            appObj->cfg.isPixProcCfgValid[1U] = FALSE;
            appObj->cfg.isBysOutCfgValid[1U]  = FALSE;
            appObj->cfg.writeToMem[1U]        = FALSE;

            appObj->cfg.bysInEnable[1U] = TRUE;

            appObj->cfg.isVportCfgValid[1U] = TRUE;

            appObj->cfg.vportCfg[1U].enable   = TRUE;
            appObj->cfg.vportCfg[1U].pixClock = 32768U;
            appObj->cfg.vportCfg[1U].width    = 1U;
            appObj->cfg.vportCfg[1U].xBlk     = 0x4U;
            appObj->cfg.vportCfg[1U].yBlk     = 0x14U;
            appObj->cfg.vportCfg[1U].rdyThr   = 0U;
            appObj->cfg.vportCfg[1U].fsReset  = TRUE;
        }

        ispStartNo = appObj->numCalStreams;
        for (index = ispStartNo; index < pCfg->numStreams; index++)
        {
            appObj->cfg.streamId[index] = index;
            appObj->cfg.csi2DataFormat[index]
                = VPS_ISS_CAL_CSI2_DISABLE_CONTEXT;
            appObj->cfg.csi2VirtualChanNo[index] = 0U;
            appObj->cfg.streamType[index]        = VPS_ISS_CAL_TAG_MAX;
            appObj->cfg.isPixProcCfgValid[index] = FALSE;
            appObj->cfg.isBysOutCfgValid[index]  = FALSE;
            appObj->cfg.bysInEnable[index]       = FALSE;
            appObj->cfg.isVportCfgValid[index]   = FALSE;
            appObj->cfg.writeToMem[index]        = FALSE;
        }

        BspUtils_memset(&appObj->ispPrms, 0x0, sizeof (vpsissIspParams_t));

        appObj->ispPrms.inFmt.width      = pCfg->width;
        appObj->ispPrms.inFmt.height     = pCfg->height;
        appObj->ispPrms.inFmt.dataFormat = pCfg->dataFormat;
        appObj->ispPrms.inFmt.bpp        = pCfg->bpp;

        appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A] = TRUE;
        appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] = pCfg->enaRszB;
        appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB]  = TRUE;
        appObj->ispPrms.enableWdrMerge            = FALSE;
        appObj->ispPrms.enableDfs                 = FALSE;
        appObj->ispPrms.glbcePath                 = pCfg->glbcePath;
        appObj->ispPrms.nsf3Path                  = pCfg->nsf3Path;
        appObj->ispPrms.enableDpcPreNsf3          = FALSE; /* OTF Check */
        appObj->ispPrms.enableCnf                 = FALSE; /* OTF Check */
        appObj->ispPrms.enableRszInputFromIpipeif = FALSE;
        appObj->ispPrms.useWen = FALSE;
        appObj->ispPrms.hdPol  = FVID2_POL_HIGH;
        appObj->ispPrms.vdPol  = FVID2_POL_HIGH;
        appObj->cfg.pIspArgs   = &appObj->ispPrms;
    }

    retVal = Fvid2_control(appObj->drvHandle, IOCTL_VPS_CAPT_SET_ISS_PARAMS,
                           &appObj->cfg, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Set ISS Params Failed!!!\r\n");
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": ISS Capture Configured\r\n");

    return (retVal);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 appCaptAllocAndQFrames(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
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
    for (streamId = appObj->numCalStreams;
         streamId < appObj->createPrms.numStream; streamId++)
    {
        Fvid2Format_init(&fmt);
        fmt.width      = pCfg->width;
        fmt.height     = pCfg->height;
        fmt.pitch[0]   = fmt.width * 2;
        fmt.bpp        = FVID2_BPP_BITS16;
        fmt.dataFormat = pCfg->outFmt;
        if (FVID2_DF_YUV420SP_UV == pCfg->outFmt)
        {
            fmt.pitch[0]  = fmt.width;
            fmt.pitch[1U] = fmt.width;
            fmt.pitch[2U] = fmt.width;
        }

        idx = streamId * VPS_ISS_CAL_MAX_STREAMS;

        if (idx >= (CAPT_APP_FRAMES_PER_STREAM * VPS_ISS_CAL_MAX_STREAMS))
        {
            GT_assert(BspAppTrace, FALSE);
        }

        pFrm = (Fvid2_Frame *) &appObj->frames[idx];

        pFrm->timeStamp   = 0x0U;
        pFrm->timeStamp64 = 0x0U;
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

        for (idx = 0; idx < appObj->otfStrmMap.numStream; idx++)
        {
            if (appObj->otfStrmMap.captStreamId[idx] == streamId)
            {
                break;
            }
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

        switch (appObj->otfStrmMap.ispStreamId[idx])
        {
            case VPS_ISS_STREAM_ID_RSZ_A:
                Bsp_printf(APP_NAME ":Output of Resizer A "
                           "is available at...\r\n");
                break;
            case VPS_ISS_STREAM_ID_RSZ_B:
                Bsp_printf(APP_NAME ":Output of Resizer B "
                           "is available at...\r\n");
                break;
            case VPS_ISS_STREAM_ID_AEWB:
                Bsp_printf(APP_NAME ":Output of AEWB is available at...\r\n");
                break;
            default:
                Bsp_printf(APP_NAME ":ISP Stream not recognized\r\n");
                break;
        }

        /* Set number of frame in frame list */
        for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
        {
            frmList.frames[idx] = &pFrm[idx];
            GT_2trace(BspAppTrace, GT_INFO, APP_NAME ": Captured Frames [%d]"
                      " Available at 0x%x\r\n", idx, pFrm[idx].addr[0][0]);
        }

        frmList.numFrames = CAPT_APP_FRAMES_PER_STREAM;

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

    appObj->tsIdx = 0U;
    BspUtils_memset(&appObj->ts,
                    0x0,
                    sizeof (appObj->ts));
    return (retVal);
}

static Int32 appCaptFreeFrames(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32                  retVal = FVID2_SOK;
    UInt32                 streamId, idx;
    Fvid2_Format           fmt;
    Fvid2_Frame           *pFrm;
    static Fvid2_FrameList frmList;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = appObj->numCalStreams;
         streamId < appObj->createPrms.numStream; streamId++)
    {
        Fvid2Format_init(&fmt);
        fmt.width      = pCfg->width;
        fmt.height     = pCfg->height;
        fmt.pitch[0]   = fmt.width * 2;
        fmt.bpp        = FVID2_BPP_BITS16;
        fmt.dataFormat = pCfg->outFmt;
        if (FVID2_DF_YUV420SP_UV == pCfg->outFmt)
        {
            fmt.pitch[0]  = fmt.width;
            fmt.pitch[1U] = fmt.width;
            fmt.pitch[2U] = fmt.width;
        }

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

static Int32 appCaptChkTimeStamps(appCaptObj_t *appObj)
{
    UInt32 idx, diff;
    float  frameInterval;

    switch (appObj->expectedFrameRate)
    {
        case FVID2_FPS_30:
            frameInterval = (1.0 / 30.0) * 1000U;
            break;
        case FVID2_FPS_60:
            frameInterval = (1.0 / 60.0) * 1000U;
            break;
        default:
            Bsp_printf(APP_NAME ": Warning - Time stamps of frame is not"
                       " checked...");
            frameInterval = FVID2_EFAIL;
            break;
    }

    if (FVID2_EFAIL != frameInterval)
    {
        /* Rounding up */
        frameInterval++;
        for (idx = 1U; idx < CAPT_APP_RUN_COUNT; idx++)
        {
            diff = appObj->ts[idx] - appObj->ts[idx - 1U];
            if (diff > frameInterval)
            {
                Bsp_printf(APP_NAME ": Frame interval (%d / %d) > than "
                           "average frame interval (%d) !!!\r\n",
                           idx, diff, frameInterval);
            }
        }
    }
    return FVID2_SOK;
}

/**
 *  appCaptGetTestId
 *  Return the test ID to run.
 */
static Int32 appCaptGetTestId(appCaptObj_t *appObj)
{
    UInt32       testCnt;
    static Int32 testId = 0;
    Int32        retVal = BSP_SOK;
    static UInt32 timeoutVal = BSP_UTILS_UART_RX_DEFAULT_TIMEOUT;

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
        GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\r\n", testCnt, gTestCfg[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\r\n", APP_CAPT_NUM_OPTS, "Auto Run\r\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run (in UART console): \r\n");

    while (1U)
    {
        retVal = BspUtils_uartGetNum(&testId, timeoutVal);
        if (retVal == BSP_ETIMEOUT)
        {
            /* No user input within the timeout. Continue with Autorun */
            testId = APP_CAPT_NUM_OPTS;
            break;
        }
        else
        {
            timeoutVal = BSP_UTILS_UART_RX_WAIT_FOREVER;
        }
        GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
        if ((testId >= 0) && (testId <= APP_CAPT_NUM_OPTS))
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
static Int32 appCaptcreateVidSensor(appCaptObj_t *instObj)
{
    Int32  retVal;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr;
    Bsp_VidSensorChipIdParams sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus sensorChipIdStatus;
    Bsp_VidSensorCreateStatus sensorCreateStatus;
    Bsp_VidSensorConfigParams configParams;

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

    /* Power on video sensor at board level mux */
    retVal = Bsp_boardPowerOnDevice(instObj->testPrms.sensorDrvId, sensorInstId,
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

    if (FVID2_SOK == retVal)
    {
        instObj->sensorCreatePrms.deviceI2cInstId    = sensorI2cInstId;
        instObj->sensorCreatePrms.numDevicesAtPort   = 1U;
        instObj->sensorCreatePrms.deviceI2cAddr[0]   = sensorI2cAddr;
        instObj->sensorCreatePrms.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
        instObj->sensorCreatePrms.sensorCfg          = NULL;
        instObj->sensorCreatePrms.numSensorCfg       = 0U;

        instObj->sensorHandle = Fvid2_create(
            instObj->testPrms.sensorDrvId,
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
            instObj->instId,
            instObj->testPrms.sensorDrvId,
            instObj->sensorCreatePrms.deviceI2cAddr[0],
            sensorChipIdStatus.chipId,
            sensorChipIdStatus.chipRevision,
            sensorChipIdStatus.firmwareVersion);

        /* Right now, this IOCTL is not implemented. TODO. */
        configParams.videoIfWidth = instObj->testPrms.interfacewidth;
        configParams.dataformat   = instObj->testPrms.dataFormat;
        configParams.standard     = instObj->testPrms.standard;
        configParams.fps          = FVID2_FPS_30;
        configParams.bpp          = instObj->testPrms.bpp;
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
        UInt16 regAddr  = 0x3444;
        UInt16 regValue = 0x0;

        rdParams.deviceNum  = 0U;
        rdParams.numRegs    = 1U;
        rdParams.regAddr    = &regAddr;
        rdParams.regValue16 = &regValue;
        rdParams.regValue8  = NULL;

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
    if (FVID2_SOK == retVal)
    {
        instObj->expectedFrameRate = configParams.fps;
    }

    return (retVal);
}

static void appCaptPrintStatistics(appCaptObj_t *appObj,
                                   UInt32        execTimeInMsecs)
{
    UInt32           cpuLoad = 0U;

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
    if(appObj->cpuLoadCount != 0U)
    {
        /* Load count is non Zero, Valid CPU load value is updated. */
        cpuLoad = appObj->totalCpuLoad / appObj->cpuLoadCount;
    }
    GT_1trace(BspAppTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              cpuLoad);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    /* Print the driver retVal */
    BspUtils_appPrintCaptStatus(
        appObj->drvHandle,
        appObj->instId,
        appObj->createPrms.numStream,
        appObj->createPrms.numCh,
        execTimeInMsecs);

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return;
}

static Int32 appCaptCheckMakeStrmMap(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 index, ispCaptStrmId;

    /* Data has to be received either via CSI2 / BYS IN */
    appObj->numCalStreams = 1;

    if (VPS_CAPT_INST_ISS_CAL_A_OTF == appObj->instId)
    {
        if ((VPS_ISS_GLBCE_PATH_CAL == pCfg->glbcePath) &&
            (VPS_ISS_NSF3_PATH_CAL == pCfg->nsf3Path))
        {
            Bsp_printf("Error - Cannot have NSF3 & GLBCE in CAL Path!!!\r\n");
            retVal = FVID2_EBADARGS;
        }

        if (((VPS_ISS_GLBCE_PATH_CAL == pCfg->glbcePath) ||
             (VPS_ISS_NSF3_PATH_CAL == pCfg->nsf3Path)) &&
            (FVID2_VIFM_SCH_CPI == pCfg->interfaceType))
        {
            Bsp_printf("Error - Cannot have NSF3 & GLBCE in CAL Path when"
                       " receiving from parallel interface!!!\r\n");
            retVal = FVID2_EBADARGS;
        }
        BspUtils_memset(&appObj->otfStrmMap,
                        0x0,
                        sizeof (appObj->otfStrmMap));

        index = 0U;
        if ((VPS_ISS_GLBCE_PATH_CAL == pCfg->glbcePath) ||
            (VPS_ISS_NSF3_PATH_CAL == pCfg->nsf3Path))
        {
            /* NSF3 or GLBCE is in CAL path, CAL will have to send out data via
             *  BYS out and bring it back in via BYS IN and send it out via
             *  VPORT to ISP */
            appObj->numCalStreams++;
        }

        ispCaptStrmId = appObj->numCalStreams;
        appObj->otfStrmMap.captStreamId[index] = ispCaptStrmId;
        appObj->otfStrmMap.ispStreamId[index]  = VPS_ISS_STREAM_ID_RSZ_A;
        /* Identify the primary out stream, the main loop will capture
         *  configured number of frames based on this */
        appObj->rszOutStrmId = appObj->otfStrmMap.captStreamId[index];
        index++;
        ispCaptStrmId++;

        if (TRUE == pCfg->enaRszB)
        {
            appObj->otfStrmMap.captStreamId[index] = ispCaptStrmId;
            appObj->otfStrmMap.ispStreamId[index]  = VPS_ISS_STREAM_ID_RSZ_B;
            index++;
            ispCaptStrmId++;
        }

        appObj->otfStrmMap.captStreamId[index] = ispCaptStrmId;
        appObj->otfStrmMap.ispStreamId[index]  = VPS_ISS_STREAM_ID_AEWB;
        index++;
        ispCaptStrmId++;

        appObj->otfStrmMap.numStream = index;

        switch (pCfg->glbcePath)
        {
            case VPS_ISS_GLBCE_PATH_DISABLED:
                Bsp_printf(APP_NAME ":GLBCE is Disabled!\r\n");
                break;
            case VPS_ISS_GLBCE_PATH_CAL:
                Bsp_printf(APP_NAME ":GLBCE is in CAL Path!\r\n");
                break;
            case VPS_ISS_GLBCE_PATH_ISP:
                Bsp_printf(APP_NAME ":GLBCE is in ISP Path!\r\n");
                break;
            default:
                Bsp_printf(APP_NAME ":Error Illegal GLBCE Path!!!\r\n");
                break;
        }

        switch (pCfg->nsf3Path)
        {
            case VPS_ISS_NSF3_PATH_DISABLED:
                Bsp_printf(APP_NAME ":NSF3 is Disabled!\r\n");
                break;
            case VPS_ISS_NSF3_PATH_CAL:
                Bsp_printf(APP_NAME ":NSF3 is in CAL Path!\r\n");
                break;
            case VPS_ISS_NSF3_PATH_ISP:
                Bsp_printf(APP_NAME ":NSF3 is in ISP Path!\r\n");
                break;
            default:
                Bsp_printf(APP_NAME ":Error Illegal NSF3 Path!!!\r\n");
                break;
        }
    }

    return retVal;
}

static Int32 appCaptSetOtfStrmMap(appCaptObj_t *appObj)
{
    Int32 retVal = FVID2_SOK;

    retVal = Fvid2_control(appObj->drvHandle,
                           IOCTL_VPS_CAPT_SET_ISS_STREAM_MAP,
                           &appObj->otfStrmMap, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Could not set the stream map!!!\r\n");
    }

    return (retVal);
}

static Int32 appCaptSetIpipeCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32 retVal = FVID2_SOK;
    vpsissIpipeWbConfig_t ipipeWb;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->ipipeCtrl,
                    0x0,
                    sizeof (appObj->ipipeCtrl));
    BspUtils_memset(&appObj->inputCfg,
                    0x0,
                    sizeof (appObj->inputCfg));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
    appObj->ipipeCtrl.inCfg  = &appObj->inputCfg;

    retVal = Fvid2_control(appObj->drvHandle, VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
                           &appObj->ipipeCtrl, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("IPIPE GetConfig Failed\r\n");

        return -1;
    }
    appObj->inputCfg.dataPath           = VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422;
    appObj->inputCfg.procWin.cropStartX = 0U;
    appObj->inputCfg.procWin.cropStartY = 0U;
    appObj->inputCfg.procWin.cropWidth  = pCfg->width;
    appObj->inputCfg.procWin.cropHeight = pCfg->height;

    retVal = Fvid2_control(appObj->drvHandle, VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                           &appObj->ipipeCtrl, NULL);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("IPIPE SetConfig Failed\r\n");

        return -1;
    }

    if (TRUE == appObj->enableDpc)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->dpcOtfCfg,
                        0x0,
                        sizeof (appObj->dpcOtfCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_DPC_OTF;
        appObj->ipipeCtrl.dpcOtf = &appObj->dpcOtfCfg;

        retVal = Fvid2_control(appObj->drvHandle,
                               VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
                               &appObj->ipipeCtrl, NULL);

        if (FVID2_SOK != retVal)
        {
            Bsp_printf("IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->dpcOtfCfg.enableOtfDpc = TRUE;
        appObj->dpcOtfCfg.method       = VPS_ISS_IPIPE_DPC_OTF_METHOD_1;
        appObj->dpcOtfCfg.dThr         = 0x0u;
        appObj->dpcOtfCfg.grThr        = 0x1u;
        appObj->dpcOtfCfg.gbThr        = 0x0u;
        appObj->dpcOtfCfg.bThr         = 800u;
        appObj->dpcOtfCfg.rCor         = 0x0u;
        appObj->dpcOtfCfg.grCor        = 0x1u;
        appObj->dpcOtfCfg.gbCor        = 0x0u;
        appObj->dpcOtfCfg.bCor         = 1023u;
        appObj->dpcOtfCfg.shiftValue   = 0x2u;

        retVal = Fvid2_control(appObj->drvHandle,
                               VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                               &appObj->ipipeCtrl, NULL);

        if (FVID2_SOK != retVal)
        {
            Bsp_printf("IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &ipipeWb;

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
                           &appObj->ipipeCtrl, NULL);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("IPIPE SetConfig Failed\r\n");

        return -1;
    }

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
    appObj->ipipeCtrl.wbCfg  = &ipipeWb;

    if (VPS_ISS_GLBCE_PATH_DISABLED == appObj->ispPrms.glbcePath)
    {
        ipipeWb.gain[0]   = 0x600;
        ipipeWb.gain[1]   = 0x600;
        ipipeWb.gain[2]   = 0x600;
        ipipeWb.gain[3]   = 0x600;
        ipipeWb.offset[0] = 0x000;
        ipipeWb.offset[1] = 0x000;
        ipipeWb.offset[2] = 0x000;
        ipipeWb.offset[3] = 0x000;
    }

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                           &appObj->ipipeCtrl, NULL);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("IPIPE SetConfig Failed\r\n");

        return -1;
    }

    return (retVal);
}

static Int32 appCaptSetRszCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32 retVal;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->rszCfg,
                    0x0,
                    sizeof (vpsissRszCfg_t));
    BspUtils_memset(&appObj->rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));

    appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    appObj->rszCtrl.rszCfg = &appObj->rszCfg;

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_RSZ_IOCTL_GET_CONFIG,
                           &appObj->rszCtrl, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Resizer GetConfig Failed\r\n");

        return -1;
    }

    appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
    appObj->rszCfg.inCfg.procWin.cropStartX = 0u;
    appObj->rszCfg.inCfg.procWin.cropStartY = 0u;
    appObj->rszCfg.inCfg.procWin.cropWidth  = pCfg->width;
    appObj->rszCfg.inCfg.procWin.cropHeight = pCfg->height;

    appObj->rszCfg.instCfg[0U].enable = 1U;
    appObj->rszCfg.instCfg[0U].outFmt.dataFormat = pCfg->outFmt;
    appObj->rszCfg.instCfg[0U].outFmt.width      = pCfg->width;
    appObj->rszCfg.instCfg[0U].outFmt.height     = pCfg->height;

    if (FVID2_DF_YUV420SP_UV == appObj->rszCfg.instCfg[0U].outFmt.dataFormat)
    {
        appObj->rszCfg.instCfg[0U].outFmt.pitch[0U] = pCfg->pitch / 2U;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[1U] = pCfg->pitch / 2U;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[2U] = pCfg->pitch / 2U;
    }
    else
    {
        appObj->rszCfg.instCfg[0U].outFmt.pitch[0U] = pCfg->pitch;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[1U] = pCfg->pitch;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[2U] = pCfg->pitch;
    }

    appObj->rszCfg.instCfg[0u].flipCtrl =
        VPS_ISS_RSZ_STR_MODE_NORMAL;
    appObj->rszCfg.instCfg[0u].startPos.startX = 0u;
    appObj->rszCfg.instCfg[0u].startPos.startY = 0u;
    appObj->rszCfg.instCfg[0u].scaleMode       =
        VPS_ISS_RSZ_SCALE_MODE_NORMAL;
    appObj->rszCfg.instCfg[0u].filtCfg.horzLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0u].filtCfg.vertLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0u].filtCfg.horzChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0u].filtCfg.vertChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;

    appObj->rszCfg.instCfg[0u].intensityCfg.horzLumaIntensity   = 0x595u;
    appObj->rszCfg.instCfg[0u].intensityCfg.horzChromaIntensity = 0x0u;
    appObj->rszCfg.instCfg[0u].intensityCfg.vertLumaIntensity   = 0x3CFu;
    appObj->rszCfg.instCfg[0u].intensityCfg.vertChromaIntensity = 0x0u;

    appObj->rszCfg.instCfg[1U].enable = 0U;
    if (TRUE == pCfg->enaRszB)
    {
        appObj->rszCfg.instCfg[1U].enable = 1U;
    }

    appObj->rszCfg.instCfg[1U].outFmt.dataFormat = FVID2_DF_YUV420SP_UV;
    appObj->rszCfg.instCfg[1U].outFmt.width      = pCfg->width / 2U;
    appObj->rszCfg.instCfg[1U].outFmt.height     = pCfg->height / 2U;

    if (FVID2_DF_YUV420SP_UV == appObj->rszCfg.instCfg[0U].outFmt.dataFormat)
    {
        appObj->rszCfg.instCfg[1U].outFmt.pitch[0U] = pCfg->pitch / 2U;
        appObj->rszCfg.instCfg[1U].outFmt.pitch[1U] = pCfg->pitch / 2U;
        appObj->rszCfg.instCfg[1U].outFmt.pitch[2U] = pCfg->pitch / 2U;
    }
    else
    {
        appObj->rszCfg.instCfg[1U].outFmt.pitch[0U] = pCfg->pitch;
        appObj->rszCfg.instCfg[1U].outFmt.pitch[1U] = pCfg->pitch;
        appObj->rszCfg.instCfg[1U].outFmt.pitch[2U] = pCfg->pitch;
    }

    appObj->rszCfg.instCfg[1u].flipCtrl =
        VPS_ISS_RSZ_STR_MODE_NORMAL;
    appObj->rszCfg.instCfg[1u].startPos.startX = 0u;
    appObj->rszCfg.instCfg[1u].startPos.startY = 0u;
    appObj->rszCfg.instCfg[1u].scaleMode       =
        VPS_ISS_RSZ_SCALE_MODE_NORMAL;
    appObj->rszCfg.instCfg[1u].filtCfg.horzLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[1u].filtCfg.vertLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[1u].filtCfg.horzChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[1u].filtCfg.vertChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;

    appObj->rszCfg.instCfg[1u].intensityCfg.horzLumaIntensity   = 0x595u;
    appObj->rszCfg.instCfg[1u].intensityCfg.horzChromaIntensity = 0x0u;
    appObj->rszCfg.instCfg[1u].intensityCfg.vertLumaIntensity   = 0x3CFu;
    appObj->rszCfg.instCfg[1u].intensityCfg.vertChromaIntensity = 0x0u;

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_RSZ_IOCTL_SET_CONFIG,
                           &appObj->rszCtrl, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Resizer SetConfig Failed\r\n");

        return -1;
    }

    return (retVal);
}

static Int32 appCaptSetIsifCfg(appCaptObj_t *appObj)
{
    Int32  status;
    UInt32 outCnt;
    UInt32 colorCnt;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->isifWbCfg,
                    0x0,
                    sizeof (vpsissIsifGainOfstConfig_t));
    BspUtils_memset(&appObj->isifCtrl, 0x0, sizeof (vpsissIsifCtrl_t));

    appObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_WB;
    appObj->isifCtrl.wbCfg  = &appObj->isifWbCfg;

    status = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_ISIF_IOCTL_GET_CONFIG,
                           &appObj->isifCtrl, NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("ISIF GetConfig Failed\r\n");

        return -1;
    }

    /* Enable Gains and Offsets for all three outputs */
    for (outCnt = 0u; outCnt < VPS_ISS_ISIF_MAX_OUTPUT; outCnt++)
    {
        appObj->isifWbCfg.gainEnable[outCnt]   = TRUE;
        appObj->isifWbCfg.offsetEnable[outCnt] = TRUE;
    }

    /* Setting gains to unit */
    for (colorCnt = 0u; colorCnt < FVID2_BAYER_COLOR_COMP_MAX; colorCnt++)
    {
        appObj->isifWbCfg.gain[colorCnt] = 0x200u;
    }

    /* Setting Offset to 0 */
    appObj->isifWbCfg.offset = 0x0u;

    status = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_ISIF_IOCTL_SET_CONFIG,
                           &appObj->isifCtrl, NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("ISIF SetConfig Failed\r\n");

        return -1;
    }

    return (status);
}

static Int32 appCaptSetCnfCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32 retVal = FVID2_SOK;
    vpsissNsf3Config_t *nsf3Cfg;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->cnfCfg,
                    0x0,
                    sizeof (vpsissCnfConfig_t));

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_CNF_IOCTL_GET_CONFIG,
                           &appObj->cnfCfg, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("CNF GetConfig Failed\r\n");

        return -1;
    }

    nsf3Cfg = &appObj->cnfCfg.nsf3Cfg;
    appObj->cnfCfg.enable    = TRUE;
    appObj->cnfCfg.enableCds = FALSE;
    BspUtils_memcpy(
        nsf3Cfg,
        &gIssHalNsf3DefCfg_Cnf,
        sizeof (vpsissNsf3Config_t));

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_CNF_IOCTL_SET_CONFIG,
                           &appObj->cnfCfg, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("CNF SetConfig Failed\r\n");
    }

    return (retVal);
}

static Int32 appCaptSetH3aCfg(appCaptObj_t *appObj)
{
    Int32           retVal = FVID2_SOK;
    vpsissH3aCtrl_t h3aCtrlCfg;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->h3aCfg,
                    0x0,
                    sizeof (vpsissH3aAewbConfig_t));

    h3aCtrlCfg.module  = VPS_ISS_H3A_MODULE_AEWB;
    h3aCtrlCfg.aewbCfg = &appObj->h3aCfg;

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_H3A_IOCTL_GET_CONFIG,
                           &h3aCtrlCfg, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("H3A GetConfig Failed\r\n");

        return -1;
    }

    /* For OV10640 */
    h3aCtrlCfg.module  = VPS_ISS_H3A_MODULE_AEWB;
    h3aCtrlCfg.aewbCfg = &appObj->h3aCfg;
    appObj->h3aCfg.enableALowComp     = FALSE;
    appObj->h3aCfg.enableMedFilt      = FALSE;
    appObj->h3aCfg.midFiltThreshold   = 0xFFFU;
    appObj->h3aCfg.winCfg.pos.startX  = 32U;
    appObj->h3aCfg.winCfg.pos.startX  = 106U;
    appObj->h3aCfg.winCfg.width       = 64U;
    appObj->h3aCfg.winCfg.height      = 8U;
    appObj->h3aCfg.winCfg.horzCount   = 16U;
    appObj->h3aCfg.winCfg.vertCount   = 64U;
    appObj->h3aCfg.winCfg.horzIncr    = 4U;
    appObj->h3aCfg.winCfg.vertIncr    = 4U;
    appObj->h3aCfg.blackLineVertStart = 718U;
    appObj->h3aCfg.blackLineHeight    = 2U;
    appObj->h3aCfg.outMode  = VPS_ISS_H3A_OUTPUT_MODE_SUM_ONLY;
    appObj->h3aCfg.sumShift = 0;
    appObj->h3aCfg.satLimit = 1023U;
    appObj->h3aCfg.mode     = VPS_ISS_H3A_MODE_NORMAL;

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_H3A_IOCTL_SET_CONFIG,
                           &h3aCtrlCfg, NULL);

    if (FVID2_SOK != retVal)
    {
        Bsp_printf("H3A SetConfig Failed\r\n");
    }

    return (retVal);
}

Int32 appCaptSetGlbceCfg(appCaptObj_t *appObj)
{
    Int32 status = FVID2_SOK;
    vpsissIspVp2Config_t vp2Cfg;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->glbceCfg,
                    0x0,
                    sizeof (vpsissGlbceConfig_t));

    appObj->glbceCtrl.module   = VPS_ISS_GLBCE_MODULE_GLBCE;
    appObj->glbceCtrl.glbceCfg = &appObj->glbceCfg;

    status = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
                           &appObj->glbceCtrl, NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("GLBCE GetConfig Failed\r\n");
        return -1;
    }

    appObj->glbceCfg.enable = TRUE;

    status = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
                           &appObj->glbceCtrl, NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("GLBCE GetConfig Failed\r\n");
        return -1;
    }
    /* set the width at VP2 port also */
    status = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_IPIPE_IOCTL_GET_VP2_CONFIG,
                           &vp2Cfg, NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("VP2 GetConfig Failed\r\n");
        return -1;
    }

    vp2Cfg.outMsbPos = VPS_ISS_OUTPUT_MSB_POS_BIT15;

    status = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_IPIPE_IOCTL_SET_VP2_CONFIG,
                           &vp2Cfg, NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("VP2 GetConfig Failed\r\n");
        return -1;
    }

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->glbcePerceptCfg,
                    0x0,
                    sizeof (vpsissGlbcePerceptConfig_t));

    appObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_FWD_PERCEPT;
    appObj->glbceCtrl.fwdPrcptCfg = &appObj->glbcePerceptCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("GLBCE GetConfig Failed\r\n");
        return -1;
    }

    appObj->glbcePerceptCfg.enable = FALSE;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("GLBCE GetConfig Failed\r\n");
        return -1;
    }

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->glbcePerceptCfg,
                    0x0,
                    sizeof (vpsissGlbcePerceptConfig_t));

    appObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_REV_PERCEPT;
    appObj->glbceCtrl.revPrcptCfg = &appObj->glbcePerceptCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("GLBCE GetConfig Failed\r\n");
        return -1;
    }

    appObj->glbcePerceptCfg.enable = FALSE;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("GLBCE GetConfig Failed\r\n");
        return -1;
    }

    return (status);
}

static Int32 appCaptSetNsf3vCfg(appCaptObj_t *appObj)
{
    int32_t status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->nsf3vCfg,
                    0x0,
                    sizeof (vpsissNsf3Config_t));

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_NSF3_IOCTL_GET_CONFIG,
        &appObj->nsf3vCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("NSF3v GetConfig Failed\r\n");
        return -1;
    }

    appObj->nsf3vCfg.bypass = FALSE;
    appObj->nsf3vCfg.enableBorderReplicate = TRUE;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_NSF3_IOCTL_SET_CONFIG,
        &appObj->nsf3vCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        Bsp_printf("NSF3v GetConfig Failed\r\n");
        return -1;
    }

    return (status);
}

/* Setup the RSZ A, AEWB and RSZ B output as real time traffic.
 *          i.e. highest priority with in ISS */
static Int32 appCaptSetIssStreamPri(appCaptObj_t *appObj, appCaptCfg_t *pCfg,
                                    UInt32 restore)
{
    Int32 retVal;

    vpsissRoutingConfig_t cfg;
    vpsissL3RoutingPri_t  pri = VPS_ISS_L3_ROUTING_OCPM1;

    if (TRUE == restore)
    {
        pri = VPS_ISS_L3_ROUTING_OCPM2;
    }

    cfg.cportId[0U] = 0U;
    cfg.cportId[1U] = 0U;
    cfg.cportId[3U] = 0U;
    cfg.numStreams  = 2U;

    cfg.source[0U]   = VPS_ISS_INIT_RSZ_A;
    cfg.priority[0U] = pri;

    cfg.source[1U]   = VPS_ISS_INIT_ISIF_H3A;
    cfg.priority[1U] = pri;

    if (TRUE == pCfg->enaRszB)
    {
        cfg.numStreams++;
        cfg.source[2U]   = VPS_ISS_INIT_RSZ_B;
        cfg.priority[2U] = pri;
    }

    retVal = Fvid2_control(appObj->drvHandle,
                           VPS_ISS_SET_ISS_STREAM_PRI_CONFIG,
                           &cfg, NULL);

    return (retVal);
}

/****************************LUTs required by various submodules. */
static vpsissNsf3Config_t gIssHalNsf3DefCfg_Cnf =
{
    FALSE,                              // Bypass
    VPS_ISS_NSF3_OP_MODE_YUV420_CHROMA, // mode
    TRUE,                               // border replicate
    FALSE,                              // chroma desaturation
    {
        /* hPos */
        {
            {0u,   16u,  128u, 1024u},
            {0u,   16u,  128u, 1024u},
            {0u,   16u,  128u, 1024u},
            {0u,   16u,  128u, 1024u}
        },
        /* vpos */
        {
            {30u,  30u,  30u,  30u  },
            {30u,  30u,  30u,  30u  },
            {30u,  30u,  30u,  30u  },
            {30u,  30u,  30u,  30u  },
        },
        /* Slope */
        {
            {0u,   0u,   0u,   0u   },
            {0u,   0u,   0u,   0u   },
            {0u,   0u,   0u,   0u   },
            {0u,   0u,   0u,   0u   },
        },
        32u, 32u,
        {
            63u, 80u, 128u
        }
    },
    {
        {128u, 128u, 128u},
        {128u, 128u, 128u},
        {128u, 128u, 128u},
        {128u, 128u, 128u}
    },
    {
        {128u, 128u, 128u},
        {128u, 128u, 128u},
        {128u, 128u, 128u},
        {128u, 128u, 128u}
    },
    {
        FALSE,  // ee_enable
        {
            {64u,  64u,  64u},
            {64u,  64u,  64u},
            {64u,  64u,  64u},
            {64u,  64u,  64u}
        },
        {
            {64u,  64u,  64u},
            {64u,  64u,  64u},
            {64u,  64u,  64u},
            {64u,  64u,  64u}
        },
        0u, 0u, 0u, 0u
    },
    {
        FALSE,  // shading gain enable
        {0u,   0u},
        {0u,   0u},
        {0u,   0u},
        0u, 0u, 0u, 0u, 0u,
        0u, 0u, 0u, 0u, 99u
    },
};
