/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file m2mIssCal_main.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <m2mIssCal_main.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Application Object containing all the parameters
 */
typedef struct vpsAppObject
{
    Fvid2_Handle                drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams              cbPrms;
    /**< Callback params. */

    Vps_M2mIntfCreateParams     createPrms;
    /**< Create Parameters */
    Vps_M2mIntfCreateStatus     createStatusPrms;
    /**< Create Status Parameters */

    Vps_M2mIntfStats            stats;

    Fvid2_Format                inFrameFmt;
    Fvid2_Format                outFrameFmt;
    vpsissCalm2mOpenParams_t    isscalCoreOpenParams;
    vpsissCalm2mParams_t        isscalCfgPrms;

    Fvid2_Frame                 frames[APP_MAX_FRAMES_ALLOCATED];
    /**< Array of FVID Frames */
    Fvid2_FrameList             inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList             outFrmList;
    /**< Output Frames List */

    Vps_M2mIntfStatsParams      statsPrms;
    /**< Statistics parameters */
} vpsAppObject_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void AppIsscal_createTask();
static void App_mainTestTask(void);
static Int32 AppOpenDriver(vpsAppObject_t *pAppObj);
static Int32 AppAllocFrames(vpsAppObject_t *pAppObj);
static Int32 AppCloseDriver(vpsAppObject_t *pAppObj);
static Int32 AppSetParams(vpsAppObject_t *pAppObj);
static void AppProcessFrames (UInt32 cnt);

static Int32 AppIsscal_callback(Fvid2_Handle handle, Ptr appData, Ptr reserved);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8                 AppMainTskStack[APP_TSK_STACK_SIZE];

/* Test complete semaphore used to sync between test task and main task. */
Semaphore_Handle             AppTestCompleteSem;

Task_Handle                  AppIsscalTaskHandle;

vpsAppObject_t               gAppObj;

static Vps_M2mIntfFrameStats gFrmStat[1000];

/* ========================================================================== */
/*                          Function Definitions                              */
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

    AppIsscal_createTask();

    BIOS_start();

    return (0);
}

static void AppIsscal_createTask()
{
    Task_Params tskPrms;

    Task_Params_init(&tskPrms);
    tskPrms.priority    = 10U;
    tskPrms.stack       = AppMainTskStack;
    tskPrms.stackSize   = APP_TSK_STACK_SIZE;
    AppIsscalTaskHandle = Task_create(
        (Task_FuncPtr) App_mainTestTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (AppIsscalTaskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(AppIsscalTaskHandle, APP_NAME);
}

/**
 *  App_mainTestTask
 *  Application test task.
 */
static void App_mainTestTask(void)
{
    UInt32                 cnt;
    Int32                  userInput;
    Int32                  retVal       = FVID2_SOK;
    UInt32                 isI2cInitReq = FALSE, isI2cDeInitReq = FALSE;
    UInt32                 perfLoopCnt;
    Semaphore_Params       semPrms;
    BspUtils_MemHeapStatus startHeapStat, startHeapStat1;
    vpsissCalm2mDmaCtrlParams_t calDmaParam;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\r\n");

    BspUtils_memGetHeapStat(&startHeapStat);

    /* Create semaphore */
    Semaphore_Params_init(&semPrms);
    AppTestCompleteSem = Semaphore_create(0U, &semPrms, NULL);
    if (NULL == AppTestCompleteSem)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
        GT_assert(BspAppTrace, FALSE);
    }

    if (FVID2_SOK == retVal)
    {
        /* System init */
        isI2cInitReq = isI2cDeInitReq = FALSE;
        retVal       = BspUtils_appDefaultInit(isI2cInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System Init Failed!!!\r\n");
        }
    }

    retVal = AppOpenDriver(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
    }

    retVal = AppSetParams(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Setting Driver Parameters\r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    retVal = AppAllocFrames(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error in Allocating Buffers \r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    gAppObj.statsPrms.enable = TRUE;
    retVal = Fvid2_control(
        gAppObj.drvHandle,
        IOCTL_VPS_M2M_INTF_SET_STATS_PARAMS,
        &gAppObj.statsPrms,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not set Statistics parameters \r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    BspOsal_printf("M2MISSCAL_APP: Load the input frame (%d x %d) @ 0x%x \r\n",
                   IN_WIDTH, IN_HEIGHT, gAppObj.frames[APP_INP_FRM_IDX].addr[0U][0U]);

    BspUtils_appPrintLoadRawCmd(
        "m2mIssCal",
        gAppObj.frames[APP_INP_FRM_IDX].addr[0U][0U],
        gAppObj.inFrameFmt.dataFormat,
        gAppObj.inFrameFmt.width,
        gAppObj.inFrameFmt.height);

    BspOsal_printf("M2MISSCAL_APP: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    for (cnt = 0U; cnt < APP_NUM_FRAMES; cnt++)
    {
        BspOsal_printf("M2MISSCAL_APP: Prossing frmae no: %d\r\n", cnt);
        BspUtils_memGetHeapStat(&startHeapStat1);

        Fvid2FrameList_init(&gAppObj.inFrmList);
        Fvid2FrameList_init(&gAppObj.outFrmList);

        /* Make input and output frames list */
        gAppObj.inFrmList.frames[0U] =
            &gAppObj.frames[APP_INP_FRM_IDX + cnt];
        gAppObj.outFrmList.frames[0U] =
            &gAppObj.frames[APP_OUT_FRM_IDX + cnt];

        gAppObj.inFrmList.numFrames  = 1U;
        gAppObj.outFrmList.numFrames = 1U;

        /* Submit Processing Request to the driver */
        retVal = Fvid2_processRequest(
            gAppObj.drvHandle,
            &gAppObj.inFrmList,
            &gAppObj.outFrmList);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Submitting request \r\n");
            AppCloseDriver(&gAppObj);
            return;
        }

        /* Wait for test to complete */
        Semaphore_pend(AppTestCompleteSem, BIOS_WAIT_FOREVER);

        /* Submit Processing Request to the driver */
        retVal = Fvid2_getProcessedRequest(
            gAppObj.drvHandle,
            &gAppObj.inFrmList,
            &gAppObj.outFrmList,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Getting completed Request\r\n");
            AppCloseDriver(&gAppObj);
            return;
        }

        BspUtils_memCheckHeapStat(&startHeapStat1);
    }

    BspOsal_printf(
        "M2MISSCAL_APP: Save the output frame (%d x %d) @ 0x%x \r\n",
        IN_WIDTH, IN_HEIGHT, gAppObj.frames[APP_OUT_FRM_IDX].addr[0U][0U]);
    BspOsal_printf(
        "M2MISSCAL_APP: saveRaw(0, 0x%x, filename, %d, 32, false)\r\n",
        gAppObj.frames[APP_OUT_FRM_IDX].addr[0U][0U],
        ((IN_WIDTH * IN_HEIGHT * 3) >> 1));
    BspUtils_appPrintSaveRawCmd(
        "m2mIssCal",
        gAppObj.frames[APP_OUT_FRM_IDX].addr[0U][0U],
        OUT_FORMAT,
        OUT_WIDTH,
        OUT_HEIGHT,
        APP_NUM_FRAMES * OUT_PITCH * OUT_HEIGHT);

    BspOsal_printf("M2MISSCAL_APP: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    /* Print the Statistics */
    VpsM2mIntfStats_init(&gAppObj.stats);

    retVal = Fvid2_control(
        gAppObj.drvHandle,
        IOCTL_VPS_M2M_INTF_GET_STATS,
        &gAppObj.stats,
        NULL);
    if (FVID2_SOK == retVal)
    {
        Bsp_printf("M2MISSCAL_APP: Processed Request = %d \r\n",
                   gAppObj.stats.numProcessedReq);
        Bsp_printf("M2MISSCAL_APP: Error Request = %d \r\n",
                   gAppObj.stats.numErrorReq);
        Bsp_printf("M2MISSCAL_APP: Pending Request = %d \r\n",
                   gAppObj.stats.numPendingReq);

        Bsp_printf("===========================\r\n");
        Bsp_printf("M2MISSCAL_APP: Processing Time \r\n");
        Bsp_printf("===========================\r\n");
        Bsp_printf("Iteration  | HW Time in msecs | SW Overhead in msecs\r\n");
        for (cnt = 0U; cnt < gAppObj.stats.numStats; cnt++)
        {
            Bsp_printf("-----------------------------------------------------\r\n");
            Bsp_printf("%10d | %14d   | %18d   |\r\n", cnt,
                       gAppObj.stats.frmStats[cnt].dequeueTimeStamp -
                       gAppObj.stats.frmStats[cnt].queueTimeStamp,
                       (gAppObj.stats.frmStats[cnt].startProcTimeStamp -
                        gAppObj.stats.frmStats[cnt].queueTimeStamp) +
                       (gAppObj.stats.frmStats[cnt].dequeueTimeStamp -
                        gAppObj.stats.frmStats[cnt].endProcTimeStamp));
        }
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not get Statistics \r\n");
    }

    perfLoopCnt = 1000U;
    BspUtils_PrfTsHndl *appTsHndl;
    appTsHndl = BspUtils_prfTsCreate ("ISS_CAL_M2M");
    BspOsal_printf("M2MISSCAL_APP: Running Performance test\r\n");

    BspOsal_printf("M2MISSCAL_APP: Process %d frames at max BW\r\n", perfLoopCnt);
    BspUtils_prfTsBegin(appTsHndl);
    AppProcessFrames(perfLoopCnt);
    BspUtils_prfTsEnd(appTsHndl, perfLoopCnt);
    BspUtils_prfTsPrint(appTsHndl, TRUE);

    BspOsal_printf("M2MISSCAL_APP: Limit BW and capture %d frames\r\n", perfLoopCnt);
    calDmaParam.bwLimit   = 200U;
    calDmaParam.ocpTagCnt = 1U;
    calDmaParam.pixClock  = 0x10000U;

    retVal = Fvid2_control (
        gAppObj.drvHandle,
        VPS_ISS_CALM2M_IOCTL_SET_DMA_PARAMS,
        &calDmaParam,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not set dma params\n");
    }

    BspUtils_prfTsBegin(appTsHndl);
    AppProcessFrames(perfLoopCnt);
    BspUtils_prfTsEnd(appTsHndl, perfLoopCnt);
    BspUtils_prfTsPrint(appTsHndl, TRUE);

    BspOsal_printf("M2MISSCAL_APP: Performance test Completed\r\n");
    retVal = AppCloseDriver(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
    }

    if (FVID2_SOK == retVal)
    {
        Semaphore_delete(&AppTestCompleteSem);
        GT_1trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": Max stack used for main task (init sequence): %d bytes\r\n",
            BspOsal_getTaskStackUsage(NULL));
        GT_1trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Max system stack used (ISR): %d bytes\r\n",
                  BspOsal_getSystemStackUsage());
    }

    if (FVID2_SOK == retVal)
    {
        /* System de-init */
        retVal = BspUtils_appDefaultDeInit(isI2cDeInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System De-Init Failed!!!\r\n");
        }
        BspUtils_appPrintMemStatus();
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Test Successful!!\r\n");
    }

    BspUtils_memCheckHeapStat(&startHeapStat);
    return;
}

static void AppProcessFrames (UInt32 cnt)
{
    Int32                  retVal       = FVID2_SOK;

    Fvid2FrameList_init(&gAppObj.inFrmList);
    Fvid2FrameList_init(&gAppObj.outFrmList);

    /* Make input and output frames list */
    gAppObj.inFrmList.frames[0U]  = &gAppObj.frames[APP_INP_FRM_IDX];
    gAppObj.outFrmList.frames[0U] = &gAppObj.frames[APP_OUT_FRM_IDX];

    gAppObj.inFrmList.numFrames  = 1U;
    gAppObj.outFrmList.numFrames = 1U;

    for (cnt = 0U; cnt < 1000U; cnt++)
    {
        /* Submit Processing Request to the driver */
        retVal = Fvid2_processRequest(
            gAppObj.drvHandle,
            &gAppObj.inFrmList,
            &gAppObj.outFrmList);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Submitting request \r\n");
            AppCloseDriver(&gAppObj);
            return;
        }

        /* Wait for test to complete */
        Semaphore_pend(AppTestCompleteSem, BIOS_WAIT_FOREVER);

        /* Submit Processing Request to the driver */
        retVal = Fvid2_getProcessedRequest(
            gAppObj.drvHandle,
            &gAppObj.inFrmList,
            &gAppObj.outFrmList,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Getting completed Request\r\n");
            AppCloseDriver(&gAppObj);
            return;
        }
    }
}

static Int32 AppIsscal_callback(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    vpsAppObject_t *pAppObj = (vpsAppObject_t *) appData;

    if (NULL == pAppObj)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Object is null in isr !!\r\n");
    }
    if (NULL == handle)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Handle is null in isr !!\r\n");
    }

    /* Mark Frame As completed */
    Semaphore_post(AppTestCompleteSem);

    return (FVID2_SOK);
}

static Int32 AppAllocFrames(vpsAppObject_t *pAppObj)
{
    Int32 retVal = FVID2_SOK;

    BspUtils_memset(&pAppObj->frames, 0x00U, sizeof (pAppObj->frames));

    /* Allocate the Buffer for the Input Frame */
    retVal = BspUtils_memFrameAlloc(
        &pAppObj->inFrameFmt,
        &pAppObj->frames[APP_INP_FRM_IDX],
        APP_NUM_FRAMES);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Input Frame Alloc Failed!!!\r\n");
        return (retVal);
    }
    BspUtils_memset(pAppObj->frames[APP_INP_FRM_IDX].addr[0][0], 0x00U,
                    (((pAppObj->inFrameFmt.pitch[0U] *
                       pAppObj->inFrameFmt.height)  *
                      APP_NUM_FRAMES)));

    /* Allocate the Buffer for the Output Frame */
    retVal = BspUtils_memFrameAlloc(
        &pAppObj->outFrameFmt,
        &pAppObj->frames[APP_OUT_FRM_IDX],
        APP_NUM_FRAMES);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Output Frame Alloc Failed!!!\r\n");
        return (retVal);
    }
    BspUtils_memset(pAppObj->frames[APP_OUT_FRM_IDX].addr[0][0], 0x00U,
                    (((pAppObj->outFrameFmt.pitch[0U] *
                       pAppObj->outFrameFmt.height)  *
                      APP_NUM_FRAMES)));

    return (retVal);
}

static Int32 AppOpenDriver(vpsAppObject_t *pAppObj)
{
    Fvid2CbParams_init(&pAppObj->cbPrms);
    pAppObj->cbPrms.cbFxn   = AppIsscal_callback;
    pAppObj->cbPrms.appData = pAppObj;

    Fvid2Format_init(&pAppObj->inFrameFmt);
    pAppObj->inFrameFmt.width      = IN_WIDTH;
    pAppObj->inFrameFmt.height     = IN_HEIGHT;
    pAppObj->inFrameFmt.pitch[0U]  = IN_PITCH;
    pAppObj->inFrameFmt.pitch[1U]  = IN_PITCH;
    pAppObj->inFrameFmt.bpp        = IN_BPP;
    pAppObj->inFrameFmt.dataFormat = IN_FORMAT;

    Fvid2Format_init(&pAppObj->outFrameFmt);
    pAppObj->outFrameFmt.width      = OUT_WIDTH;
    pAppObj->outFrameFmt.height     = OUT_HEIGHT;
    pAppObj->outFrameFmt.pitch[0U]  = OUT_PITCH;
    pAppObj->outFrameFmt.pitch[1U]  = OUT_PITCH;
    pAppObj->outFrameFmt.bpp        = OUT_BPP;
    pAppObj->outFrameFmt.dataFormat = OUT_FORMAT;

    VpsM2mIntfCreateParams_init(&pAppObj->createPrms);

    pAppObj->createPrms.numCh           = 1U;
    pAppObj->createPrms.chInQueueLength = 1U;
    pAppObj->createPrms.maxStatsInst    = 1000U;
    pAppObj->createPrms.frmStats        = gFrmStat;
    pAppObj->createPrms.pAdditionalArgs = (Ptr) & pAppObj->isscalCoreOpenParams;

    VpsM2mIntfCreateStatus_init(&pAppObj->createStatusPrms);

    pAppObj->isscalCoreOpenParams.arg  = NULL; /* Reserved */

    pAppObj->drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CALM2M,
        &pAppObj->createPrms,
        &pAppObj->createStatusPrms,
        &pAppObj->cbPrms);
    if (NULL == pAppObj->drvHandle)
    {
        Bsp_printf("M2MISSCAL_APP: Could not open driver for P1\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 AppCloseDriver(vpsAppObject_t *pAppObj)
{
    Int32 retVal = FVID2_SOK;
    UInt32 cnt;

    /* Free up the buffer allocated for the input and output frames */
    retVal = BspUtils_memFrameFree(
        &pAppObj->inFrameFmt,
        &pAppObj->frames[APP_INP_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Input Frame Free Failed!!!\r\n");
    }

    retVal = BspUtils_memFrameFree(
        &pAppObj->outFrameFmt,
        &pAppObj->frames[APP_OUT_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Output Frame Free Failed!!!\r\n");
    }

    for (cnt = 0U; cnt < APP_MAX_FRAMES_ALLOCATED; cnt++)
    {
        pAppObj->frames[cnt].addr[0U][0U] = NULL;
    }

    if (NULL != pAppObj->drvHandle)
    {
        Fvid2_delete(pAppObj->drvHandle, NULL);
        pAppObj->drvHandle = NULL;
    }

    return 0;
}

static Int32 AppSetParams(vpsAppObject_t *pAppObj)
{
    Int32 status;

    /* CALM2M Configuration */
    pAppObj->isscalCfgPrms.inWidth = IN_WIDTH;
    pAppObj->isscalCfgPrms.inHeight = IN_HEIGHT;
    pAppObj->isscalCfgPrms.inPitch = IN_PITCH;
    pAppObj->isscalCfgPrms.inBpp = IN_BPP;
    pAppObj->isscalCfgPrms.inPixExtract = IN_PIX_EXTRACT;
    
    pAppObj->isscalCfgPrms.outWidth = OUT_WIDTH;
    pAppObj->isscalCfgPrms.outHeight = OUT_HEIGHT;
    pAppObj->isscalCfgPrms.outPitch = OUT_PITCH;
    pAppObj->isscalCfgPrms.outBpp = OUT_BPP;
    pAppObj->isscalCfgPrms.outPixPack = OUT_PIX_PACK;

    status = Fvid2_control(
        pAppObj->drvHandle,
        IOCTL_VPS_ISS_CAL_M2M_SET_PARAMS,
        &pAppObj->isscalCfgPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("M2MISSCAL_APP: SetParams Failed. \r\n");
        return -1;
    }

    return (status);
}

