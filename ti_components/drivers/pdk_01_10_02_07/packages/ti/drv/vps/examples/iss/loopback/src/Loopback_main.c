
/**
 *  \file Loopback_main.c
 *
 *  \brief ISP Integration Sample application
 *
 */

/*
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 */
/*
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
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <Loopback_main.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define LPBK_APP_ISS_NUM_OPTS        (sizeof (gLpbkAppTestCfg) / \
                                      sizeof (gLpbkAppTestCfg[0]))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8          AppMainTskStack[ISS_LOOPBACK_APP_TSK_STACK_MAIN];

LpbkApp_Obj           gLpbkAppObj;

volatile unsigned int gStop = 0;

LpbkApp_testCfg       gLpbkAppTestCfg[] = {
    {
        "Parallel Capture from AR132 -> ISP M2M -> LDC+VTNF -> Display",
        FALSE,
        ISS_LOOPBACK_APP_NUM_PROC_FRAMES,
        1280U, 720U, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12, 1280U * 2U,
        FVID2_VID_SENSOR_APT_AR0132_DRV, FVID2_VIFM_SCH_CPI,
        FVID2_VIFW_12BIT, VPS_ISS_CAL_CSI2_RAW12, 0U,
        TRUE,
        FVID2_DF_YUV420SP_UV, 1280U, 720U, FVID2_BPP_BITS12, 1280U
    },
    {
        "Parallel Capture from AR140 -> ISP M2M -> LDC+VTNF -> Display",
        FALSE,
        ISS_LOOPBACK_APP_NUM_PROC_FRAMES,
        1280U, 720U, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12, 1280U * 2U,
        FVID2_VID_SENSOR_APT_AR0140_DRV, FVID2_VIFM_SCH_CPI,
        FVID2_VIFW_12BIT, VPS_ISS_CAL_CSI2_RAW12, 0U,
        TRUE,
        FVID2_DF_YUV420SP_UV, 1280U, 720U, FVID2_BPP_BITS12, 1280U
    },
};

/**< Flag used to dump raw captured frame. When this flag is set, the last
 *      captured frame would not be processed, until this flag is cleared. */
volatile UInt32       gDump1Frame;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 LpbkApp_getTestId();
static void LpbkApp_createTask();
static void LpbkApp_mainTestTask(void);
static void LpbkApp_allocFrames(void);
static void LpbkApp_freeFrames(void);
static void LpbkApp_wdrLoopback(LpbkApp_testCfg *testCfg);
static void LpbkApp_ispLoopback(LpbkApp_testCfg *testCfg);

/* ========================================================================== */
/*                          Function Definition                               */
/* ========================================================================== */
/**
 *  main
 *  Application main function.
 */
Int32 main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    LpbkApp_createTask();

    BIOS_start();

    return (0);
}

static void LpbkApp_createTask()
{
    Task_Params tskPrms;

    Task_Params_init(&tskPrms);
    tskPrms.stack              = AppMainTskStack;
    tskPrms.stackSize          = ISS_LOOPBACK_APP_TSK_STACK_MAIN;
    gLpbkAppObj.mainTaskHandle = Task_create(
        (Task_FuncPtr) LpbkApp_mainTestTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (gLpbkAppObj.mainTaskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gLpbkAppObj.mainTaskHandle, APP_NAME);
}

/**
 *  LpbkApp_mainTestTask
 *  Application test task.
 */
static void LpbkApp_mainTestTask(void)
{
    Int32  status;
    UInt32 testId;
    UInt32 isI2cInitReq, isI2cDeInitReq;
    BspUtils_MemHeapStatus startHeapStat;

    /* System init */
    isI2cInitReq = isI2cDeInitReq = TRUE;
    status       = BspUtils_appDefaultInit(isI2cInitReq);
    if (status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME "System Init Failed!!!\r\n");
        GT_assert(BspAppTrace, FALSE);
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": VPS Initialized\r\n");
    }

    /* Get the TestId */
    testId = LpbkApp_getTestId();
    if (testId < LPBK_APP_ISS_NUM_OPTS)
    {
        BspUtils_memGetHeapStat(&startHeapStat);

        if (TRUE == gLpbkAppTestCfg[testId].enableWdrMode)
        {
            LpbkApp_wdrLoopback(
                &gLpbkAppTestCfg[testId]);
        }
        else
        {
            LpbkApp_ispLoopback(
                &gLpbkAppTestCfg[testId]);
        }

        BspUtils_memCheckHeapStat(&startHeapStat);
    }

    status = BspUtils_appDefaultDeInit(isI2cDeInitReq);
    if (status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": System De-Init Failed!!!\r\n");
    }

    if (status == FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_INFO, "\r\n");
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": VPS De Initialized\r\n");
    }

    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max BSS Memory used for test task: %d bytes\r\n",
              gLpbkAppObj.maxHeapMemReq);
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

/**
 *  LpbkApp_wdrLoopback
 *  Application test task.
 */
static void LpbkApp_wdrLoopback(LpbkApp_testCfg *testCfg)
{
    UInt32           numFramesCaptured, numFramesDisplayed;
    UInt32           frmCnt;
    Semaphore_Params semPrms;
    Fvid2_Frame     *prevFrm = NULL, *curFrm = NULL, *outFrm = NULL;
    Fvid2_Frame     *captFrames[ISS_MAX_RAW_FRAMES],
    *dispFrames[5U], *frameToDump;

    Semaphore_Params_init(&semPrms);
    semPrms.mode = Semaphore_Mode_BINARY;
    gLpbkAppObj.semCaptWait = Semaphore_create(0U, &semPrms, NULL);
    Semaphore_Params_init(&semPrms);
    semPrms.mode = Semaphore_Mode_BINARY;
    gLpbkAppObj.semDispWait = Semaphore_create(0U, &semPrms, NULL);
    if ((NULL == gLpbkAppObj.semDispWait) || (NULL == gLpbkAppObj.semCaptWait))
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        GT_assert(BspAppTrace, FALSE);
    }

    /* Initialize global Data structures */
    gLpbkAppObj.processFrmCnt = 0U;
    for (frmCnt = 0U; frmCnt < ISS_MAX_RAW_FRAMES; frmCnt++)
    {
        gLpbkAppObj.pRawFrames[frmCnt] = &gLpbkAppObj.rawFrames[frmCnt];
    }
    for (frmCnt = 0U; frmCnt < ISS_MAX_YUV_FRAMES; frmCnt++)
    {
        gLpbkAppObj.pYuvFrames[frmCnt] = &gLpbkAppObj.yuvFrames[frmCnt];
    }

    LpbkApp_allocFrames();

    /* Create All the drivers*/
    LpbkApp_m2mWdrCreate(testCfg);
    LpbkApp_m2mSimcopCreate(testCfg);

    /* Create the capture driver,
     * capture driver uses given semaphore handle for releasing the task */
    LpbkApp_captCreate(testCfg, &gLpbkAppObj.semCaptWait);
    LpbkApp_dispCreate(testCfg, &gLpbkAppObj.semDispWait);

    /* Prime Frames to the capture and display drivers */
    LpbkApp_captPutFrames(0U, ISS_MAX_RAW_FRAMES, gLpbkAppObj.pRawFrames);

    /* Frame number-0 is used for storing the WDR output and Frame
     * number-1 is used current output of Simcop */
    LpbkApp_dispPutFrames(
        0U,
        ISS_MAX_YUV_FRAMES - 2U,
        &gLpbkAppObj.pYuvFrames[2U]);

    /* Start Display and Capture driver */
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Starting Capture!!!\r\n");
    LpbkApp_captStart();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Starting Display!!!\r\n");
    LpbkApp_dispStart();

    curFrm  = &gLpbkAppObj.yuvFrames[0U];
    prevFrm = &gLpbkAppObj.yuvFrames[0U];
    outFrm  = &gLpbkAppObj.yuvFrames[1U];

    gDump1Frame = 0x0;
    frameToDump = NULL;

    while (gLpbkAppObj.processFrmCnt < ISS_LOOPBACK_APP_NUM_PROC_FRAMES)
    {
        /* Wait for the Capture callback */
        Semaphore_pend(gLpbkAppObj.semCaptWait, BIOS_WAIT_FOREVER);

        /* Get the captured frame */
        LpbkApp_captGetFrames(0U, &numFramesCaptured, captFrames);

        if (numFramesCaptured > 1U)
        {
            LpbkApp_captPutFrames(0U, (numFramesCaptured - 1U), captFrames);

            captFrames[0x0]   = captFrames[numFramesCaptured - 1U];
            numFramesCaptured = 1;
        }

        if ((0x0 != gDump1Frame) && (NULL == frameToDump))
        {
            frameToDump = captFrames[0];
            GT_1trace(BspAppTrace, GT_INFO, APP_NAME ": Save Frame @ 0x%x \r\n",
                      frameToDump->addr[0][0]);
            continue;
        }

        LpbkApp_m2mWdrProcessFrame(
            captFrames[0U],
            curFrm);

        /* Since M2M processing is done, return capture frame
         * back to the driver */
        LpbkApp_captPutFrames(0U, numFramesCaptured, captFrames);
        if ((0x0 == gDump1Frame) && (NULL != frameToDump))
        {
            /* ReUse this frame, put it back to capture */
            LpbkApp_captPutFrames(0U, 0x1, &frameToDump);
            GT_1trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Released Frame 0x%x \r\n",
                      frameToDump->addr[0][0]);
            frameToDump = NULL;
            /* Let the normal process continue for that current captured
             *  frame.*/
        }

        LpbkApp_m2mSimcopProcessFrame(curFrm, prevFrm, outFrm);

        if (0U < gLpbkAppObj.processFrmCnt)
        {
            dispFrames[0U] = prevFrm;
            /* Since M2M processing is done, return capture frame
             * back to the driver */
            LpbkApp_dispPutFrames(0U, 1U, dispFrames);
        }
        prevFrm = outFrm;

        /* Wait for the display callback */
        Semaphore_pend(gLpbkAppObj.semDispWait, BIOS_WAIT_FOREVER);

        /* Get the displayed frame */
        LpbkApp_dispGetFrames(0U, &numFramesDisplayed, dispFrames);

        if (numFramesDisplayed > 1U)
        {
            GT_0trace(
                BspAppTrace, GT_ERR,
                APP_NAME
                "Disp:Supports only one frame processing at a time!!!\r\n");
            break;
        }
        outFrm = dispFrames[0U];

        gLpbkAppObj.processFrmCnt++;
    }
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Stopping Capture!!!\r\n");
    LpbkApp_captStop();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Stopping Display!!!\r\n");
    LpbkApp_dispStop();

    LpbkApp_captClose();
    LpbkApp_dispClose();
    LpbkApp_m2mSimcopClose();
    LpbkApp_m2mWdrClose();

    LpbkApp_freeFrames();
    Semaphore_delete(&gLpbkAppObj.semDispWait);
    Semaphore_delete(&gLpbkAppObj.semCaptWait);

    gLpbkAppObj.maxHeapMemReq = 0;
}

/**
 *  LpbkApp_ispLoopback
 *  Application test task.
 */
static void LpbkApp_ispLoopback(LpbkApp_testCfg *testCfg)
{
    UInt32           numFramesCaptured, numFramesDisplayed;
    UInt32           frmCnt;
    Semaphore_Params semPrms;
    Fvid2_Frame     *prevFrm = NULL, *curFrm = NULL, *outFrm = NULL;
    Fvid2_Frame     *captFrames[5U], *dispFrames[5U], *frameToDump;

    Semaphore_Params_init(&semPrms);
    semPrms.mode = Semaphore_Mode_BINARY;
    gLpbkAppObj.semCaptWait = Semaphore_create(0U, &semPrms, NULL);
    Semaphore_Params_init(&semPrms);
    semPrms.mode = Semaphore_Mode_BINARY;
    gLpbkAppObj.semDispWait = Semaphore_create(0U, &semPrms, NULL);
    if ((NULL == gLpbkAppObj.semDispWait) || (NULL == gLpbkAppObj.semCaptWait))
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        GT_assert(BspAppTrace, FALSE);
    }

    /* Initialize global Data structures */
    gLpbkAppObj.processFrmCnt = 0U;
    for (frmCnt = 0U; frmCnt < ISS_MAX_RAW_FRAMES; frmCnt++)
    {
        gLpbkAppObj.pRawFrames[frmCnt] = &gLpbkAppObj.rawFrames[frmCnt];
    }
    for (frmCnt = 0U; frmCnt < ISS_MAX_YUV_FRAMES; frmCnt++)
    {
        gLpbkAppObj.pYuvFrames[frmCnt] = &gLpbkAppObj.yuvFrames[frmCnt];
    }

    LpbkApp_allocFrames();

    /* Create All the drivers*/
    LpbkApp_m2mIspCreate(testCfg);
    LpbkApp_m2mSimcopCreate(testCfg);

    /* Create the capture driver,
     * capture driver uses given semaphore handle for releasing the task */
    LpbkApp_captCreate(testCfg, &gLpbkAppObj.semCaptWait);
    LpbkApp_dispCreate(testCfg, &gLpbkAppObj.semDispWait);

    /* Prime Frames to the capture and display drivers */
    LpbkApp_captPutFrames(0U, ISS_MAX_RAW_FRAMES, gLpbkAppObj.pRawFrames);

    /* Frame number-0 is used for storing the WDR output and Frame
     * number-1 is used current output of Simcop */
    LpbkApp_dispPutFrames(
        0U,
        ISS_MAX_YUV_FRAMES - 2U,
        &gLpbkAppObj.pYuvFrames[2U]);

    /* Start Display and Capture driver */
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Starting Capture!!!\r\n");
    LpbkApp_captStart();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Starting Display!!!\r\n");
    LpbkApp_dispStart();

    curFrm  = &gLpbkAppObj.yuvFrames[0U];
    prevFrm = &gLpbkAppObj.yuvFrames[0U];
    outFrm  = &gLpbkAppObj.yuvFrames[1U];

    gDump1Frame = 0x0;
    frameToDump = NULL;
    while (gLpbkAppObj.processFrmCnt < ISS_LOOPBACK_APP_NUM_PROC_FRAMES)
    {
        /* Wait for the Capture callback */
        Semaphore_pend(gLpbkAppObj.semCaptWait, BIOS_WAIT_FOREVER);

        /* Get the captured frame */
        LpbkApp_captGetFrames(0U, &numFramesCaptured, captFrames);

        for (frmCnt = 0U; frmCnt < numFramesCaptured; frmCnt++)
        {
            if ((0x0 != gDump1Frame) && (NULL == frameToDump))
            {
                frameToDump = captFrames[frmCnt];
                GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                          ": Save Frame @ 0x%x \r\n",
                          frameToDump->addr[0][0]);
                continue;
            }

            LpbkApp_m2mIspProcessFrame(
                captFrames[frmCnt],
                curFrm);

            /* Since M2M processing is done, return capture frame
             * back to the driver */
            LpbkApp_captPutFrames(0U, 1, &captFrames[frmCnt]);

            if ((0x0 == gDump1Frame) && (NULL != frameToDump))
            {
                /* ReUse this frame, put it back to capture */
                LpbkApp_captPutFrames(0U, 0x1, &frameToDump);
                GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                          ": Released Frame 0x%x \r\n",
                          frameToDump->addr[0][0]);
                frameToDump = NULL;
                /* Let the normal process continue for that current captured
                 *  frame.*/
            }

            LpbkApp_m2mSimcopProcessFrame(curFrm, prevFrm, outFrm);

            if (0U < gLpbkAppObj.processFrmCnt)
            {
                dispFrames[0U] = prevFrm;
                /* Since M2M processing is done, return capture frame
                 * back to the driver */
                LpbkApp_dispPutFrames(0U, 1U, dispFrames);
            }
            prevFrm = outFrm;

            /* Wait for the display callback */
            Semaphore_pend(gLpbkAppObj.semDispWait, BIOS_WAIT_FOREVER);

            /* Get the displayed frame */
            LpbkApp_dispGetFrames(0U, &numFramesDisplayed, dispFrames);

            if (numFramesDisplayed > 1U)
            {
                GT_0trace(
                    BspAppTrace, GT_ERR,
                    APP_NAME
                    "Disp:Supports only one frame processing at a time!!!\r\n");
                break;
            }
            outFrm = dispFrames[0U];

            gLpbkAppObj.processFrmCnt++;
        }
    }
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Stopping Capture!!!\r\n");
    LpbkApp_captStop();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME
              ": Stopping Display!!!\r\n");
    LpbkApp_dispStop();

    LpbkApp_captClose();
    LpbkApp_dispClose();
    LpbkApp_m2mIspClose();
    LpbkApp_m2mSimcopClose();

    LpbkApp_freeFrames();
    Semaphore_delete(&gLpbkAppObj.semDispWait);
    Semaphore_delete(&gLpbkAppObj.semCaptWait);

    gLpbkAppObj.maxHeapMemReq = 0;
}

void LpbkApp_allocFrames(void)
{
    Int32        status = FVID2_SOK;
    Fvid2_Format fmt;

    BspUtils_memClearOnAlloc(TRUE);

    fmt.width      = 1920;
    fmt.height     = 1080;
    fmt.dataFormat = FVID2_DF_BAYER_BGGR;
    fmt.bpp        = FVID2_BPP_BITS12;
    fmt.pitch[0U]  = 1920 * 2;
    fmt.pitch[1U]  = 1920 * 2;
    fmt.pitch[2U]  = 1920 * 2;

    /* Allocate the buffers for the RAW frames */
    status = BspUtils_memFrameAlloc(
        &fmt,
        &gLpbkAppObj.rawFrames[0U],
        ISS_MAX_RAW_FRAMES);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed for RAW Frames!!!\r\n");

        GT_assert(BspAppTrace, FALSE);
    }

    fmt.width      = 1280;
    fmt.height     = 720;
    fmt.dataFormat = FVID2_DF_YUV420SP_UV;
    fmt.bpp        = FVID2_BPP_BITS12;

    if (FVID2_DF_YUV420SP_UV == fmt.dataFormat)
    {
        fmt.pitch[0U] = 1280;
        fmt.pitch[1U] = 1280;
        fmt.pitch[2U] = 1280;
    }
    else
    {
        fmt.pitch[0U] = 1280 * 2;
        fmt.pitch[1U] = 1280 * 2;
        fmt.pitch[2U] = 1280 * 2;
    }

    /* Allocate the buffers for the YUV frames */
    status = BspUtils_memFrameAlloc(
        &fmt,
        &gLpbkAppObj.yuvFrames[0U],
        ISS_MAX_YUV_FRAMES);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed for YUV Frames!!!\r\n");

        GT_assert(BspAppTrace, FALSE);
    }
}

void LpbkApp_freeFrames(void)
{
    Int32        status = FVID2_SOK;
    Fvid2_Format fmt;

    fmt.width      = 1920;
    fmt.height     = 1080;
    fmt.dataFormat = FVID2_DF_BAYER_BGGR;
    fmt.bpp        = FVID2_BPP_BITS12;
    fmt.pitch[0U]  = 1920 * 2;
    fmt.pitch[1U]  = 1920 * 2;
    fmt.pitch[2U]  = 1920 * 2;

    /* Free the buffers space of the RAW frames */
    status = BspUtils_memFrameFree(
        &fmt,
        &gLpbkAppObj.rawFrames[0U],
        ISS_MAX_RAW_FRAMES);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed for RAW Frames!!!\r\n");

        GT_assert(BspAppTrace, FALSE);
    }

    fmt.width      = 1280;
    fmt.height     = 720;
    fmt.dataFormat = FVID2_DF_YUV420SP_UV;
    fmt.bpp        = FVID2_BPP_BITS12;

    if (FVID2_DF_YUV420SP_UV == fmt.dataFormat)
    {
        fmt.pitch[0U] = 1280;
        fmt.pitch[1U] = 1280;
        fmt.pitch[2U] = 1280;
    }
    else
    {
        fmt.pitch[0U] = 1280 * 2;
        fmt.pitch[1U] = 1280 * 2;
        fmt.pitch[2U] = 1280 * 2;
    }

    /* Free up the buffers space of the YUV frames */
    status = BspUtils_memFrameFree(
        &fmt,
        &gLpbkAppObj.yuvFrames[0U],
        ISS_MAX_YUV_FRAMES);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed for YUV Frames!!!\r\n");

        GT_assert(BspAppTrace, FALSE);
    }
}

/**
 *  LpbkApp_getTestId
 *  Return the test ID to run.
 */
static Int32 LpbkApp_getTestId()
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
    for (testCnt = 0; testCnt < LPBK_APP_ISS_NUM_OPTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\r\n", testCnt, gLpbkAppTestCfg[testCnt].testDescStr);
    }
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\r\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run (in UART console): \r\n");

    while (1U)
    {
        BspUtils_uartGetNum(&testId, BSP_UTILS_UART_RX_WAIT_FOREVER);
        GT_1trace(BspAppTrace, GT_INFO, "%d\r\n", testId);
        if ((testId >= 0) && (testId < LPBK_APP_ISS_NUM_OPTS))
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

