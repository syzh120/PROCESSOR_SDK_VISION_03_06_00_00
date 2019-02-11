/*
 *  Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file SyncLoopback_main.c
 *
 *  \brief Capture->Display synchronous low latency loopback sample application
 *  main file. Description of this test is in SyncLoopback_test.c
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <SyncLoopback_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CM_L3INSTR_L3_3_CLKCTRL_LOCAL       (0x4A008E20U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_LOCAL   (0x4A008E28U)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x200U + (1U * 4U))
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief Offset of DRM SUSPEND_CTRL2 register */
#define DRM_SUSPEND_CTRL2               (0x200U + (2U * 4U))
/** \brief DRM_SUSPEND_CTRL2 is mapped to DCAN2 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN2          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL2)

/** \brief Offset of DRM SUSPEND_CTRL31 register */
#define DRM_SUSPEND_CTRL31               (0x200U + (31 * 4U))
/** \brief DRM_SUSPEND_CTRL31 is mapped to 32Ktimer Suspend Output line */
#define DRM_SUSPEND_CTRL_32KTIMER       (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL31)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void LpbkApp_createTsk(void);
static void LpbkApp_tskMain(UArg arg0, UArg arg1);

static void LpbkApp_init(LpbkApp_Obj *appObj);
static void LpbkApp_deInit(LpbkApp_Obj *appObj);

static Int32 LpbkApp_getTestId(LpbkApp_Obj *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gLpbkAppTskStackMain, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gLpbkAppTskStackMain, ".bss:taskStackSection")
/* Test application stack */
static UInt8              gLpbkAppTskStackMain[LPBK_APP_TSK_STACK_MAIN];

/* Test application object */
LpbkApp_Obj               gLpbkAppObj;

/* Task struct Object for static allocation */
static Task_Struct        gTskStruct;

static LpbkApp_TestParams gLpbkAppTestPrms[] =
{
    {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX)
    },
};

#define LPBK_APP_NUM_TESTS              (sizeof (gLpbkAppTestPrms) / \
                                         sizeof (gLpbkAppTestPrms[0U]))

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
    LpbkApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void LpbkApp_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority  = LPBK_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gLpbkAppTskStackMain;
    tskPrms.stackSize = sizeof (gLpbkAppTskStackMain);
    tskPrms.arg0      = (UArg) & gLpbkAppObj;
    Task_construct(&gTskStruct, LpbkApp_tskMain, &tskPrms, NULL);
    gLpbkAppObj.tskHandle = Task_handle(&gTskStruct);
    GT_assert(BspAppTrace, (gLpbkAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gLpbkAppObj.tskHandle, APP_NAME);

    return;
}

/*
 * Test task main
 */
static void LpbkApp_tskMain(UArg arg0, UArg arg1)
{
    Int32       testId;
    Bsp_BoardId boardId;
    LpbkApp_Obj           *appObj = (LpbkApp_Obj *) arg0;
    LpbkApp_TestParams    *testPrms;
    BspUtils_MemHeapStatus startHeapStat, startHeapStat1;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");
    BspUtils_memGetHeapStat(&startHeapStat);
    LpbkApp_init(appObj);

    appObj->enableAutoRun = (UInt32) FALSE;
    boardId = Bsp_boardGetId();
    while (1U)
    {
        /* Get the TestId */
        testId = LpbkApp_getTestId(appObj);
        if ((testId >= 0) && (testId < LPBK_APP_NUM_TESTS))
        {
            testPrms = &gLpbkAppTestPrms[testId];
            if (testPrms->boardId & boardId)
            {
                BspUtils_memGetHeapStat(&startHeapStat1);

                testPrms->testId = testId;
                LpbkApp_runTest(appObj, testPrms);

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

    LpbkApp_deInit(appObj);

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

static void LpbkApp_init(LpbkApp_Obj *appObj)
{
    Int32  retVal;
    UInt32 isI2cInitReq;
    UInt32 defPixelClk;
    UInt32 regAddr, regVal;

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
        /*
         * Put all used modules to free running mode
         */
        /* Enable DRM */
        regAddr = CM_L3INSTR_L3_3_CLKCTRL_LOCAL;
        regVal  = 0x1U;
        HW_WR_REG32(regAddr, regVal);   /* Provide L3_3 clock */
        regAddr = CM_L3INSTR_L3_INSTR_CLKCTRL_LOCAL;
        regVal  = 0x1U;
        HW_WR_REG32(regAddr, regVal);   /* Provide L3 instr clock */

        /* Claim ownership of debug registers */
        regAddr = 0x54160050U;
        regVal  = 0x40000000;
        HW_WR_REG32(regAddr, regVal);
        regAddr = 0x54160050U;
        regVal  = 0x80000000U;
        HW_WR_REG32(regAddr, regVal);

        /* Set 32k counter to free running mode */
        regAddr = DRM_SUSPEND_CTRL_32KTIMER;
        regVal  = HW_RD_REG32(regAddr);
        regVal &= ~((UInt32) 0x00000009U);
        HW_WR_REG32(regAddr, regVal);
    }

    if (FVID2_SOK == retVal)
    {
        /* Create global capture handle, used for common driver configuration */
        appObj->fvidHandleAll = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ALL,
            NULL,
            NULL,
            NULL);
        if (NULL == appObj->fvidHandleAll)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Global Handle Create Failed!!!\r\n");
            retVal = FVID2_EBADARGS;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Create DCTRL handle, used for common driver configuration */
        appObj->dctrlHandle = Fvid2_create(
            FVID2_VPS_DCTRL_DRV,
            VPS_DCTRL_INST_0,
            NULL,
            NULL,
            NULL);
        if (NULL == appObj->dctrlHandle)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Create Failed!!!\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) && (FVID2_SOK == retVal))
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

        retVal = LpbkApp_configureVideoPllAndClkSrc(appObj, defPixelClk);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Configuring PLL Failed!!!\r\n");
        }

        if (FVID2_SOK == retVal)
        {
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
            if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
            {
                retVal =
                    BspUtils_appInitSerDeSer();
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": MultiDes Board Init failed!!!\r\n");
                }
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_init() - DONE !!!\r\n");
    }

    return;
}

static void LpbkApp_deInit(LpbkApp_Obj *appObj)
{
    Int32  retVal;
    UInt32 isI2cDeInitReq;

    /* Delete DCTRL handle */
    retVal = Fvid2_delete(appObj->dctrlHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL handle delete failed!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Delete global VIP capture handle */
        retVal = Fvid2_delete(appObj->fvidHandleAll, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Global handle delete failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
        {
            retVal =
                BspUtils_appDeInitSerDeSer();
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": MultiDes Board DeInit failed!!!\r\n");
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
                  APP_NAME ": LpbkApp_deInit() - DONE !!!\r\n");
    }

    return;
}

/**
 *  LpbkApp_getTestId
 *  Return the test ID to run.
 */
static Int32 LpbkApp_getTestId(LpbkApp_Obj *appObj)
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
    for (testCnt = 0; testCnt < LPBK_APP_NUM_TESTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\r\n", testCnt, gLpbkAppTestPrms[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\r\n", LPBK_APP_NUM_TESTS, "Auto Run\r\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run: \r\n");

    if (TRUE == appObj->enableAutoRun)
    {
        testId++;
        if (testId < LPBK_APP_NUM_TESTS)
        {
            GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
        }
    }
    else
    {
        while (1U)
        {
            testId = LPBK_APP_NUM_TESTS;  /* BspOsal_scanf("%d", &testId); */
            if ((testId >= 0) && (testId < LPBK_APP_NUM_TESTS))
            {
                break;
            }
            else if (testId == LPBK_APP_NUM_TESTS)
            {
                appObj->enableAutoRun = (UInt32) TRUE;
                testId = 0;
                break;
            }
            else if (100 == testId)
            {
                break;
            }
            GT_0trace(BspAppTrace, GT_INFO,
                      "Invalid Test ID. Enter Agian!!\r\n");
        }
    }

    return (testId);
}

/**
 *  \brief Return current count timer value in us.
 */
UInt64 LpbkApp_getCounterValue(void)
{
    UInt32 regVal;
    UInt64 tickValue;

    regVal    = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    tickValue = ((((UInt64) regVal) * ((UInt64) 1000000)) / ((UInt64) 32786));

    return ((UInt64) tickValue);
}

/**
 *  \brief Return current elapsed value of timer in us.
 *  This takes care of one time overflow. It is expected that the check
 *  itself doesn't happen for more than 32K timer wrap around time of
 *  31.25us x 2^32 = 134217 seconds ~37 hrs.
 *
 *  \param  origValue       Reference value to which current value is compared
 *                          to get elapsed count.
 */
UInt64 LpbkApp_getElapsedValue(UInt64 origValue)
{
    UInt32 regVal;
    UInt64 tickValue;

    regVal    = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    tickValue = ((((UInt64) regVal) * ((UInt64) 1000000)) / ((UInt64) 32786));
    if (tickValue < origValue)
    {
        /* Counter overflow occured */
        tickValue =
            (((((UInt64) 0xFFFFFFFFU) *
               ((UInt64) 1000000)) / ((UInt64) 32786)) - origValue)
            + tickValue + (1 * ((UInt64) 1000000) / ((UInt64) 32786));
    }

    return (tickValue - origValue);
}
