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
 *  \file M2mSimcopLdcVtnf_main.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <M2mSimcopLdcVtnf_main.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define APP_TSK_STACK_SIZE      (10U * 1024U)

/* Input Frame Format, SIMCOP LDC flow uses 1920x1080 input image with 8bit
 * FVID2_DF_YUV422I_YUYV input data*/
#define IN_WIDTH                 (1920U)
#define IN_HEIGHT                (1080U)
#define IN_PITCH                 (IN_WIDTH)
#define IN_FORMAT                (FVID2_DF_YUV420SP_UV)
#define IN_BPP                   (FVID2_BPP_BITS12)

#define MESH_TABLE_PITCH         (1984U)

#define OB_WIDTH                 (32U)
#define OB_HEIGHT                (36U)

#define OUT_WIDTH                (IN_WIDTH)
#define OUT_HEIGHT               (IN_HEIGHT)

#define LDC_PIX_PAD              (2U)
#define LDC_PIX_PAD              (2U)
#define LDC_INTERPOLATION_METHOD (VPS_ISS_LDC_LUMA_INTRP_BICUBIC)
/* VPS_ISS_LDC_LUMA_INTRP_BILINEAR */

#define APP_NUM_FRAMES           (4U)
#define APP_MESHTBL_FRM_IDX      (0U)
#define APP_INP_FRM_IDX          (APP_MESHTBL_FRM_IDX + 1U)
#define APP_OUT_FRM_IDX          (APP_INP_FRM_IDX + APP_NUM_FRAMES)
#define APP_DUMMY_FRM_IDX        (APP_OUT_FRM_IDX + APP_NUM_FRAMES)
#define APP_MAX_FRAMES_ALLOCATED (APP_DUMMY_FRM_IDX + 1)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Application Object containing all the parameters
 */
typedef struct vpsAppObject
{
    Fvid2_Handle             drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams           cbPrms;
    /**< Callback params. */

    Vps_M2mIntfCreateParams  createPrms;
    /**< Create Parameters */
    Vps_M2mIntfCreateStatus  createStatusPrms;
    /**< Create Status Parameters */

    Vps_M2mIntfStats         stats;

    Fvid2_Format             frameFmt;
    Fvid2_Format             meshTableFmt;
    vpsissSimcopOpenParams_t simcopCoreOpenParams;
    vpsissSimcopCfgPrms_t    simcopCfgPrms;
    vpsissldcConfig_t        ldcCfg;
    vpsissvtnfConfig_t       vtnfCfg;

    Fvid2_Frame              frames[APP_MAX_FRAMES_ALLOCATED];
    /**< Array of FVID Frames */
    Fvid2_FrameList          inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList          outFrmList;
    /**< Output Frames List */

    Vps_M2mIntfStatsParams   statsPrms;
    /**< Statistics parameters */
} vpsAppObject_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void AppSimcop_createTask();
static void App_mainTestTask(void);
static Int32 AppOpenDriver(vpsAppObject_t *pAppObj);
static Int32 AppAllocFrames(vpsAppObject_t *pAppObj);
static Int32 AppCloseDriver(vpsAppObject_t *pAppObj);
static Int32 AppSetParams(vpsAppObject_t *pAppObj);

static Int32 AppSimcop_callback(Fvid2_Handle handle, Ptr appData, Ptr reserved);

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

Task_Handle                  AppSimcopTaskHandle;

vpsAppObject_t               gAppObj;

static Vps_M2mIntfFrameStats gFrmStat[1000];

/* #define VTNF_BYPASS */
#ifdef VTNF_BYPASS
vpsissvtnfConfig_t           gVtnfCfg =
{
    FVID2_DF_YUV420SP_UV,          /* outDataFormat */
    TRUE,                          /* isAdvCfgValid */
    {
        OB_WIDTH,                  /* blockWidth */
        OB_HEIGHT,                 /* blockHeight */
        3,                         /* roundBitCount */
        0,                         /* colorWeight1 */
        0,                         /* colorWeight2 */
        {                          /* lut1[ISSHAL_VTNF_LUT_SIZE] */
            0, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24, 16,
            8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {   /* lut2[ISSHAL_VTNF_LUT_SIZE] */
            0, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24, 16,
            8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        ISSHAL_VTNF_TRG_SRC_HWSEQ, /* triggerSource */
        TRUE                       /* intrEnable */
    }
};
#else
vpsissvtnfConfig_t           gVtnfCfg =
{
    FVID2_DF_YUV420SP_UV,          /* outDataFormat */
    TRUE,                          /* isAdvCfgValid */
    {
        OB_WIDTH,                  /* blockWidth */
        OB_HEIGHT,                 /* blockHeight */
        5,                         /* roundBitCount */
        4,                         /* colorWeight1 */
        4,                         /* colorWeight2 */
        {                          /* lut1[ISSHAL_VTNF_LUT_SIZE] */
            192, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24,
            16,
            8,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {   /* lut2[ISSHAL_VTNF_LUT_SIZE] */
            192, 176, 160, 144, 128, 112, 96, 80, 72, 64, 56, 48, 40, 32, 24,
            16,
            8,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        ISSHAL_VTNF_TRG_SRC_HWSEQ,  /* triggerSource */
        TRUE                        /* intrEnable */
    }
};
#endif

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

    AppSimcop_createTask();

    BIOS_start();

    return (0);
}

static void AppSimcop_createTask()
{
    Task_Params tskPrms;

    Task_Params_init(&tskPrms);
    tskPrms.priority    = 10U;
    tskPrms.stack       = AppMainTskStack;
    tskPrms.stackSize   = APP_TSK_STACK_SIZE;
    AppSimcopTaskHandle = Task_create(
        (Task_FuncPtr) App_mainTestTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (AppSimcopTaskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(AppSimcopTaskHandle, APP_NAME);
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
    Semaphore_Params       semPrms;
    BspUtils_MemHeapStatus startHeapStat, startHeapStat1;

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

    BspOsal_printf("M2mSimcopLdcVtnfApp: Load the input frame (%d x ",
                   IN_WIDTH);
    BspOsal_printf("%d) ", IN_HEIGHT);
    BspOsal_printf("@ 0x%x \r\n", gAppObj.frames[APP_INP_FRM_IDX].addr[0U][0U]);

    BspOsal_printf(
        "M2mSimcopLdcVtnfApp: loadRaw(0x%x, 0, filename, 32, false)\r\n",
        gAppObj.frames[APP_INP_FRM_IDX].addr[0U][0U],
        APP_INP_FRM_IDX);

    BspOsal_printf(
        "M2mSimcopLdcVtnfApp: Load the mesh table at the address ");
    BspOsal_printf("@ 0x%x \r\n",
                   gAppObj.frames[APP_MESHTBL_FRM_IDX].addr[0U][0U]);

    BspOsal_printf(
        "M2mSimcopLdcVtnfApp: \
    loadRaw( 0x%x, 0, filename, 32, false)\r\n",
        gAppObj.frames[APP_MESHTBL_FRM_IDX].addr[0U][0U]);
    BspOsal_printf("M2mSimcopLdcVtnfApp: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    for (cnt = 0U; cnt < APP_NUM_FRAMES; cnt++)
    {
        BspUtils_memGetHeapStat(&startHeapStat1);

        Fvid2FrameList_init(&gAppObj.inFrmList);
        Fvid2FrameList_init(&gAppObj.outFrmList);

        /* Make input and output frames list */
        gAppObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_CUR_FRAME] =
            &gAppObj.frames[APP_INP_FRM_IDX + cnt];
        gAppObj.outFrmList.frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME] =
            &gAppObj.frames[APP_OUT_FRM_IDX + cnt];
        gAppObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_MESH_TABLE] =
            &gAppObj.frames[APP_MESHTBL_FRM_IDX];

        if (0U == cnt)
        {
            gAppObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME] =
                &gAppObj.frames[APP_DUMMY_FRM_IDX];
        }
        else
        {
            gAppObj.inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME] =
                &gAppObj.frames[APP_OUT_FRM_IDX + cnt - 1];
        }

        gAppObj.inFrmList.numFrames  = VPS_SIMCOP_STREAM_ID_MAX + 1;
        gAppObj.outFrmList.numFrames = VPS_SIMCOP_STREAM_ID_MAX + 1;

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
        "M2mSimcopLdcVtnfApp: Save the output frame (%d x ",
        IN_WIDTH);
    BspOsal_printf("%d) ", IN_HEIGHT);
    BspOsal_printf("@ 0x%x \r\n", gAppObj.frames[APP_OUT_FRM_IDX].addr[0U][0U]);
    BspOsal_printf(
        "M2mSimcopLdcVtnfApp: saveRaw(0, 0x%x, filename, %d, 32, false)\r\n",
        gAppObj.frames[APP_OUT_FRM_IDX].addr[0U][0U],
        ((IN_WIDTH * IN_HEIGHT * 3) >> 1));
    BspOsal_printf("M2mSimcopLdcVtnfApp: Enter any number (in UART console) to continue\r\n");
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
        Bsp_printf("M2mSimcopLdcVtnfApp: Processed Request = %d \r\n",
                   gAppObj.stats.numProcessedReq);
        Bsp_printf("M2mSimcopLdcVtnfApp: Error Request = %d \r\n",
                   gAppObj.stats.numErrorReq);
        Bsp_printf("M2mSimcopLdcVtnfApp: Pending Request = %d \r\n",
                   gAppObj.stats.numPendingReq);

        Bsp_printf("===========================\r\n");
        Bsp_printf("M2mSimcopLdcVtnfApp: Processing Time \r\n");
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

static Int32 AppSimcop_callback(Fvid2_Handle handle, Ptr appData, Ptr reserved)
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
        &pAppObj->frameFmt,
        &pAppObj->frames[APP_INP_FRM_IDX],
        APP_NUM_FRAMES);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Input Frame Alloc Failed!!!\r\n");
        return (retVal);
    }
    BspUtils_memset(pAppObj->frames[APP_INP_FRM_IDX].addr[0][0], 0x00U,
                    ((((pAppObj->frameFmt.width *
                        pAppObj->frameFmt.height) * 3U) / 2U) *
                     APP_NUM_FRAMES));

    /* Allocate the Buffer for the Output Frame */
    retVal = BspUtils_memFrameAlloc(
        &pAppObj->frameFmt,
        &pAppObj->frames[APP_OUT_FRM_IDX],
        APP_NUM_FRAMES);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Output Frame Alloc Failed!!!\r\n");
        return (retVal);
    }

    /* Allocate the Buffer for the Mesh Table */
    retVal = BspUtils_memFrameAlloc(
        &pAppObj->meshTableFmt,
        &pAppObj->frames[APP_MESHTBL_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Mesh Table Alloc Failed!!!\r\n");
        return (retVal);
    }

    /* Allocate the Buffer for the VNTF Reference Frame */
    retVal = BspUtils_memFrameAlloc(
        &pAppObj->frameFmt,
        &pAppObj->frames[APP_DUMMY_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Dummy Frame Alloc Failed!!!\r\n");
        return (retVal);
    }
    BspUtils_memset(pAppObj->frames[APP_DUMMY_FRM_IDX].addr[0][0], 0x00U,
                    (((pAppObj->frameFmt.width *
                       pAppObj->frameFmt.height) * 3U) / 2U));

    return (retVal);
}

static Int32 AppOpenDriver(vpsAppObject_t *pAppObj)
{
    Fvid2CbParams_init(&pAppObj->cbPrms);
    pAppObj->cbPrms.cbFxn   = AppSimcop_callback;
    pAppObj->cbPrms.appData = pAppObj;

    Fvid2Format_init(&pAppObj->frameFmt);
    pAppObj->frameFmt.width      = IN_WIDTH;
    pAppObj->frameFmt.height     = IN_HEIGHT;
    pAppObj->frameFmt.pitch[0U]  = IN_PITCH;
    pAppObj->frameFmt.pitch[1U]  = IN_PITCH;
    pAppObj->frameFmt.bpp        = IN_BPP;
    pAppObj->frameFmt.dataFormat = IN_FORMAT;

    Fvid2Format_init(&pAppObj->meshTableFmt);
    pAppObj->meshTableFmt.width      = MESH_TABLE_PITCH;
    pAppObj->meshTableFmt.height     = IN_HEIGHT;
    pAppObj->meshTableFmt.pitch[0U]  = MESH_TABLE_PITCH;
    pAppObj->meshTableFmt.bpp        = FVID2_BPP_BITS8;
    pAppObj->meshTableFmt.dataFormat = FVID2_DF_RAW08;

    VpsM2mIntfCreateParams_init(&pAppObj->createPrms);

    pAppObj->createPrms.numCh           = 1U;
    pAppObj->createPrms.chInQueueLength = 1U;
    pAppObj->createPrms.maxStatsInst    = 1000U;
    pAppObj->createPrms.frmStats        = gFrmStat;
    pAppObj->createPrms.pAdditionalArgs = (Ptr) & pAppObj->simcopCoreOpenParams;

    VpsM2mIntfCreateStatus_init(&pAppObj->createStatusPrms);

    pAppObj->simcopCoreOpenParams.mode = VPS_ISS_SIMCOP_LDC_VTNF;
    pAppObj->simcopCoreOpenParams.arg  = NULL; /* Reserved */
    pAppObj->simcopCoreOpenParams.ldcRdMaxTagCnt = 0xF;

    pAppObj->drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_SIMCOP,
        &pAppObj->createPrms,
        &pAppObj->createStatusPrms,
        &pAppObj->cbPrms);
    if (NULL == pAppObj->drvHandle)
    {
        Bsp_printf("M2mSimcopLdcVtnfApp: Could not open driver for P1\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

static Int32 AppCloseDriver(vpsAppObject_t *pAppObj)
{
    Int32 retVal = FVID2_SOK;

    /* Free up the buffer allocated for the input and output frames */
    retVal = BspUtils_memFrameFree(
        &pAppObj->frameFmt,
        &pAppObj->frames[APP_INP_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Input Frame Free Failed!!!\r\n");
    }

    retVal = BspUtils_memFrameFree(
        &pAppObj->frameFmt,
        &pAppObj->frames[APP_OUT_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Output Frame Free Failed!!!\r\n");
    }

    retVal = BspUtils_memFrameFree(
        &pAppObj->meshTableFmt,
        &pAppObj->frames[APP_MESHTBL_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Mesh Table Frame Free Failed!!!\r\n");
    }

    retVal = BspUtils_memFrameFree(
        &pAppObj->frameFmt,
        &pAppObj->frames[APP_DUMMY_FRM_IDX],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Reference Frame Free Failed!!!\r\n");
    }

    pAppObj->frames[0U].addr[0U][0U] = NULL;
    pAppObj->frames[1U].addr[0U][0U] = NULL;
    pAppObj->frames[2U].addr[0U][0U] = NULL;

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
    vpsissldcConfig_t  *pLdcCfg;
    vpsissldcPerspectiveTransformCfg_t *pLdcPTxCfg;
    vpsissldcLutCfg_t  *pLdcLutCfg;

    vpsissvtnfConfig_t *pVtnfCfg;

    /* Set the Params */

    /* SIMCOP Configuration */
    pAppObj->simcopCfgPrms.inpFrmPitch   = IN_PITCH;
    pAppObj->simcopCfgPrms.prevFrmPitch  = IN_WIDTH;
    pAppObj->simcopCfgPrms.outFrmPitch   = OUT_WIDTH;
    pAppObj->simcopCfgPrms.inFrameWidth  = IN_WIDTH;
    pAppObj->simcopCfgPrms.inFrameHeight = IN_HEIGHT;
    pAppObj->simcopCfgPrms.blkWidth      = OB_WIDTH;
    pAppObj->simcopCfgPrms.blkHeight     = OB_HEIGHT;

    /* LDC Configuration */
    pLdcCfg       = &(pAppObj->simcopCfgPrms.ldcCfg);
    pLdcCfg->mode = VPS_ISS_LDC_MODE_YUV420_LDC;
    pLdcCfg->bayerDataFormat =
        VPS_ISS_LDC_BAYER_DATA_FORMAT_UNPACKED_12BIT;
    pLdcCfg->enableBackMapping         = TRUE;
    pLdcCfg->advCfg.enableCircAddrMode = FALSE;
    pLdcCfg->advCfg.circBuffSize       = 0x0;
    pLdcCfg->advCfg.enableConstOutAddr = TRUE;
    pLdcCfg->lumeIntrType             = LDC_INTERPOLATION_METHOD;
    pLdcCfg->bayerInitColor           = VPS_ISS_LDC_BAYER_INIT_COLOR_R;
    pLdcCfg->inputFrameWidth          = IN_WIDTH;
    pLdcCfg->inputFrameHeight         = IN_HEIGHT;
    pLdcCfg->advCfg.outputBlockWidth  = OB_WIDTH;
    pLdcCfg->advCfg.outputBlockHeight = OB_HEIGHT;
    pLdcCfg->advCfg.outputFrameWidth  = OUT_WIDTH;
    pLdcCfg->advCfg.outputFrameHeight = OUT_HEIGHT;
    pLdcCfg->isAdvCfgValid            = TRUE;
    pLdcCfg->advCfg.outputStartX      = 0x0;
    pLdcCfg->advCfg.outputStartY      = 0x0;
    pLdcCfg->pixelPad = LDC_PIX_PAD;

    pLdcPTxCfg = &(pLdcCfg->perspTrnsformCfg);
    pLdcPTxCfg->enableWarp      = FALSE;
    pLdcPTxCfg->enableExpandFmt = FALSE;
    pLdcPTxCfg->coeffA          = 4096U;
    pLdcPTxCfg->coeffB          = 0U;
    pLdcPTxCfg->coeffC          = 0U;
    pLdcPTxCfg->coeffD          = 0U;
    pLdcPTxCfg->coeffE          = 4096U;
    pLdcPTxCfg->coeffF          = 0U;
    pLdcPTxCfg->coeffG          = 0U;
    pLdcPTxCfg->coeffH          = 0U;

    pLdcLutCfg          = &(pLdcCfg->lutCfg);
    pLdcLutCfg->address =
        (uint32_t) pAppObj->frames[APP_MESHTBL_FRM_IDX].addr[0][0];
    pLdcLutCfg->lineOffset      = MESH_TABLE_PITCH;
    pLdcLutCfg->downScaleFactor = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_4;

    /* VTNF Configuration */
    pVtnfCfg = &(pAppObj->simcopCfgPrms.vtnfCfg);
    BspUtils_memcpy(pVtnfCfg, &gVtnfCfg, sizeof (vpsissvtnfConfig_t));
    pVtnfCfg->outDataFormat        = IN_FORMAT;
    pVtnfCfg->advCfg.triggerSource = ISSHAL_VTNF_TRG_SRC_HWSEQ;
    pVtnfCfg->advCfg.blockWidth    = OB_WIDTH;
    pVtnfCfg->advCfg.blockHeight   = OB_HEIGHT;
    pVtnfCfg->advCfg.intrEnable    = TRUE;

    status = Fvid2_control(
        pAppObj->drvHandle,
        IOCTL_VPS_SIMCOP_M2M_SET_PARAMS,
        &pAppObj->simcopCfgPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("M2mSimcopLdcVtnfApp: SetParams Failed for P1\r\n");
        return -1;
    }

    return (status);
}

