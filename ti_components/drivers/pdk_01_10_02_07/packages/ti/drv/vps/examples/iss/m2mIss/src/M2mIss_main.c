
/**
 *  \file main.c
 *
 *  \brief ISP Mem2mem Example Application. This demo application implements
 *          methods that illustrates RAW 12 (Bayer) to YUV420 conversion and
 *          ReSizer (Resizes YUV frame to required size).
 *
 *          Implemented as 2 separate tasks, one task converts RAW and other
 *          resizes YUV frames.
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
#include <M2mIss_main.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_TSK_STACK_SIZE      (10U * 1024U)
/**< Test application stack size. */
#define ISP_INST_ID             (VPSCORE_ISS_M2M_ISP_INST_0)
/**< Instance ID of ISS driver */
#define NUMBER_OUT_FRAMES       (4U)
/**< Number of frame allocated for each task. Effectively this value * 2 number
 *      of frames are allocated */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Describe input and output frame characteristics.
 *          Used to define the operation required for each task.
 */
typedef struct
{
    UInt32             inWidth;
    /**< Input frame Width */
    UInt32             inHeight;
    /**< Input frame height */
    UInt32             inPitch;
    /**< Input frame pitch */
    Fvid2_DataFormat   inFormat;
    /**< Input frame data format */
    Fvid2_BitsPerPixel inBpp;
    /**< Input frame bits per pixel */

    UInt32             outAWidth;
    /**< Output frame width */
    UInt32             outAHeight;
    /**< Output frame height */
    UInt32             outAPitch;
    /**< Output frame pitch */
    Fvid2_DataFormat   outAFormat;
    /**< Output frame data format */
    Fvid2_BitsPerPixel outABpp;
    /**< Output frame bits per pixel */

    UInt32             numFrames;
    /**< Number of times frames should be processed */
}vpsAppFrmConfig_t;

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

    vpsissIspParams_t        ispPrms;
    /**< isp parameters */

    vpsissIspOpenParams_t    openPrms;
    /**< Core Open Parameters */
    vpsissIspOpenRetParams_t retPrms;
    /**< Core Returns Parameters */
    Vps_M2mIntfStats         stats;

    vpsissRszCtrl_t          rszCtrl;
    /**< Resizer Control structure containing pointer to the
     *   resizer configuration */
    vpsissRszCfg_t           rszCfg;
    /**< Resizer configuration */

    vpsissIpipeCtrl_t        ipipeCtrl;
    /**< IPIPE Control */
    vpsissIpipeInConfig_t    ipipeInputCfg;
    /**< IPIPE Input frame configuration */

    Fvid2_Frame              inFrames[NUMBER_OUT_FRAMES];
    /**< Space holder for allocated input frames */
    Fvid2_Frame              outFrames[NUMBER_OUT_FRAMES];
    /**< Space holder for allocated output frames */
    /**< Array of FVID Frames */
    Fvid2_FrameList          inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList          outFrmList;
    /**< Output Frames List */

    Vps_M2mIntfStatsParams   statsPrms;
    /**< Statistics parameters */

    UInt32                   intrCnt;
    /**< Frame completion counter */
    Semaphore_Handle         frameCompletionSem;
    /**< Completion callback and task sync */
    Semaphore_Handle         ispLock;
    /**< Exclusive access to ISP */

    UInt32                   exitTask;
    /**< Flag used to indicate, that this task can be deleted */

    vpsAppFrmConfig_t       *pTestCfg;
    /**< Input frame and output frame config */
} vpsAppObject_t;

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */
vpsAppFrmConfig_t gTestConfig[2U] = {
    /* Processes Raw input and output could be FVID2_DF_YUV420SP_UV,
     *      FVID2_DF_YUV422I_UYVY, FVID2_DF_BAYER_RAW */
    {1280U, 736U, (1280U * 2U), FVID2_DF_BAYER_GRBG,  FVID2_BPP_BITS12,
     1280U, 736U, (1280U), FVID2_DF_YUV420SP_UV, FVID2_BPP_BITS16, 4U},
    /* Processes YUV input frames
     *      Input FVID2_DF_YUV422I_UYVY, FVID2_DF_YUV422I_YUYV, OR
     *              FVID2_DF_YUV420SP_UV
     *      Output FVID2_DF_YUV422I_UYVY OR FVID2_DF_YUV420SP_UV */
    /* If input is YUV420 output should be YUV420 */
    {720U,  480U, (720U),       FVID2_DF_YUV420SP_UV, FVID2_BPP_BITS16,
     1920U, 1080U, (1920U), FVID2_DF_YUV420SP_UV, FVID2_BPP_BITS16, 4U}
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void AppIssMainTask();
static void AppIssRawTask(UArg arg0, UArg arg1);
static void AppIssYuvTask(UArg arg0, UArg arg1);
static Int32 AppOpenDriver(vpsAppObject_t *appObj);
static Int32 AppSetParams(vpsAppObject_t *appObj, vpsAppFrmConfig_t *cfg);
static Int32 AppSetRszConfig(vpsAppObject_t *appObj, vpsAppFrmConfig_t *cfg);
static Int32 AppSetIpipeConfig(vpsAppObject_t *appObj, vpsAppFrmConfig_t *cfg);
static Int32 AppAllocFrames(vpsAppObject_t *appObj, vpsAppFrmConfig_t *pCfg);
static Int32 AppCloseDriver(vpsAppObject_t *appObj);
static void AppReleaseResources(vpsAppObject_t *appObj);
static Int32 AppIssFrameProcessedCb(Fvid2_Handle handle, Ptr appData,
                                    Ptr reserved);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8      AppMainTskStack[APP_TSK_STACK_SIZE];

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppIssRawTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppIssRawTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8      AppIssRawTskStack[APP_TSK_STACK_SIZE];
/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppIssYuvTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppIssYuvTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8      AppIssYuvTskStack[APP_TSK_STACK_SIZE];

Task_Handle       AppIssRawTaskHandle, AppIssYuvTaskHandle,
                  AppIssMainTaskHandle;
/**< Various tasks required for the demo application */

/** \brief Global Application Object.
 *  0x0 is used for processing raw frames
 *  0x1 is used for processing YUV frames */
vpsAppObject_t    gAppObj[2U];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  main
 *  Creates the main task
 */
Int32 main(void)
{
    static Char stdin_buf[BUFSIZ];
    Task_Params tskPrms;

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    Task_Params_init(&tskPrms);
    tskPrms.priority     = 10U;
    tskPrms.stack        = AppMainTskStack;
    tskPrms.stackSize    = APP_TSK_STACK_SIZE;
    AppIssMainTaskHandle = Task_create(
        (Task_FuncPtr) AppIssMainTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (AppIssMainTaskHandle != NULL));

    BIOS_start();

    return (0);
}

/** \brief Utility function used to open the driver
 */
static Int32 AppOpenDriver(vpsAppObject_t *appObj)
{
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn   = AppIssFrameProcessedCb;
    appObj->cbPrms.appData = appObj;

    VpsM2mIntfCreateParams_init(&appObj->createPrms);
    appObj->createPrms.numCh           = 1U;
    appObj->createPrms.chInQueueLength = NUMBER_OUT_FRAMES;
    appObj->createPrms.maxStatsInst    = 0U;
    appObj->createPrms.frmStats        = NULL;
    appObj->createPrms.pAdditionalArgs = (Ptr) & appObj->openPrms;

    VpsM2mIntfCreateStatus_init(&appObj->createStatusPrms);
    appObj->createStatusPrms.pAdditionalStatus = (Ptr) & appObj->retPrms;

    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = FALSE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = FALSE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = FALSE;
    appObj->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = FALSE;
    appObj->openPrms.arg = NULL;

    appObj->drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CAL_ISP,
        &appObj->createPrms,
        &appObj->createStatusPrms,
        &appObj->cbPrms);
    if (NULL == appObj->drvHandle)
    {
        Bsp_printf("ISSM2MApp: Could not open driver for P1\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

/** \brief Utility function used to configure the resizer sub-block of ISS
 */
static Int32 AppSetRszConfig(vpsAppObject_t *appObj, vpsAppFrmConfig_t *cfg)
{
    Int32 status;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->rszCfg,
                    0x0,
                    sizeof (vpsissRszCfg_t));
    BspUtils_memset(&appObj->rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));

    appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
    appObj->rszCtrl.rszCfg = &appObj->rszCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_RSZ_IOCTL_GET_CONFIG,
        &appObj->rszCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: Resizer GetConfig Failed\r\n");

        return -1;
    }

    appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
    appObj->rszCfg.inCfg.procWin.cropStartX = 0U;
    appObj->rszCfg.inCfg.procWin.cropStartY = 0U;
    appObj->rszCfg.inCfg.procWin.cropWidth  = cfg->inWidth;
    appObj->rszCfg.inCfg.procWin.cropHeight = cfg->inHeight;

    appObj->rszCfg.instCfg[0U].enable = TRUE;
    appObj->rszCfg.instCfg[0U].outFmt.dataFormat = cfg->outAFormat;
    appObj->rszCfg.instCfg[0U].outFmt.width      = cfg->outAWidth;
    appObj->rszCfg.instCfg[0U].outFmt.height     = cfg->outAHeight;
    appObj->rszCfg.instCfg[0U].outFmt.pitch[0U]  = cfg->outAPitch;
    appObj->rszCfg.instCfg[0U].outFmt.pitch[1U]  = cfg->outAPitch;
    appObj->rszCfg.instCfg[0U].outFmt.pitch[2U]  = cfg->outAPitch;

    appObj->rszCfg.instCfg[0U].flipCtrl =
        VPS_ISS_RSZ_STR_MODE_NORMAL;
    appObj->rszCfg.instCfg[0U].startPos.startX = 0U;
    appObj->rszCfg.instCfg[0U].startPos.startY = 0U;
    appObj->rszCfg.instCfg[0U].scaleMode       =
        VPS_ISS_RSZ_SCALE_MODE_NORMAL;
    appObj->rszCfg.instCfg[0U].filtCfg.horzLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0U].filtCfg.vertLumaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0U].filtCfg.horzChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;
    appObj->rszCfg.instCfg[0U].filtCfg.vertChromaFilter =
        VPS_ISS_RSZ_FILTER_4TAP_CUBIC;

    if (FVID2_DF_BAYER_GRBG == cfg->inFormat)
    {
        appObj->rszCfg.instCfg[0U].intensityCfg.horzLumaIntensity   = 0x595u;
        appObj->rszCfg.instCfg[0U].intensityCfg.horzChromaIntensity = 0x0u;
        appObj->rszCfg.instCfg[0U].intensityCfg.vertLumaIntensity   = 0x3CFu;
        appObj->rszCfg.instCfg[0U].intensityCfg.vertChromaIntensity = 0x0u;
    }
    else
    {
        appObj->rszCfg.instCfg[0U].intensityCfg.horzLumaIntensity   = 21u;
        appObj->rszCfg.instCfg[0U].intensityCfg.horzChromaIntensity = 22u;
        appObj->rszCfg.instCfg[0U].intensityCfg.vertLumaIntensity   = 14u;
        appObj->rszCfg.instCfg[0U].intensityCfg.vertChromaIntensity = 15u;
    }
    appObj->rszCfg.instCfg[1U].enable = FALSE;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_RSZ_IOCTL_SET_CONFIG,
        &appObj->rszCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: RSZ SetConfig Failed\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

/** \brief Utility function used to configure basic parameters required for
 *              the driver.
 */
static Int32 AppSetParams(vpsAppObject_t *appObj, vpsAppFrmConfig_t *cfg)
{
    Int32 status;

    /* Set the Params */
    appObj->ispPrms.inFmt.width         = cfg->inWidth;
    appObj->ispPrms.inFmt.height        = cfg->inHeight;
    appObj->ispPrms.inFmt.pitch[0U]     = cfg->inPitch;
    appObj->ispPrms.inFmt.pitch[1U]     = cfg->inPitch;
    appObj->ispPrms.inFmt.pitch[2U]     = cfg->inPitch;
    appObj->ispPrms.inFmt.bpp           = cfg->inBpp;
    appObj->ispPrms.inFmt.dataFormat    = cfg->inFormat;
    appObj->ispPrms.inFmtN_1.width      = cfg->inWidth;
    appObj->ispPrms.inFmtN_1.height     = cfg->inHeight;
    appObj->ispPrms.inFmtN_1.pitch[0U]  = cfg->inPitch;
    appObj->ispPrms.inFmtN_1.bpp        = cfg->inBpp;
    appObj->ispPrms.inFmtN_1.dataFormat = cfg->inFormat;

    appObj->ispPrms.enableWdrMerge            = FALSE;
    appObj->ispPrms.enableDfs                 = FALSE;
    appObj->ispPrms.glbcePath                 = VPS_ISS_GLBCE_PATH_DISABLED;
    appObj->ispPrms.nsf3Path                  = VPS_ISS_NSF3_PATH_DISABLED;
    appObj->ispPrms.enableDpcPreNsf3          = FALSE;
    appObj->ispPrms.enableCnf                 = FALSE;
    appObj->ispPrms.enableRszInputFromIpipeif = FALSE;

    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] = TRUE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A]       = TRUE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1]    = FALSE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B]       = FALSE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_AF]          = FALSE;
    appObj->ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB]        = FALSE;

    appObj->ispPrms.useWen = FALSE;
    appObj->ispPrms.hdPol  = FVID2_POL_HIGH;
    appObj->ispPrms.vdPol  = FVID2_POL_HIGH;

    status = Fvid2_control(
        appObj->drvHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &appObj->ispPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: SetParams Failed \r\n");
        return -1;
    }

    return (FVID2_SOK);
}

/** \brief Utility function used to configure the IPIPE sub-block of ISS
 */
static Int32 AppSetIpipeConfig(vpsAppObject_t *appObj, vpsAppFrmConfig_t *cfg)
{
    Int32 status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->ipipeInputCfg,
                    0x0,
                    sizeof (vpsissIpipeInConfig_t));
    BspUtils_memset(&appObj->ipipeCtrl, 0x0, sizeof (vpsissIpipeCtrl_t));

    appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
    appObj->ipipeCtrl.inCfg  = &appObj->ipipeInputCfg;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: IPIPE GetConfig Failed\r\n");

        return -1;
    }

    if (FVID2_DF_BAYER_GRBG == cfg->inFormat)
    {
        appObj->ipipeInputCfg.dataPath = VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422;
    }
    else
    {
        appObj->ipipeInputCfg.dataPath = VPS_ISS_IPIPE_DATA_PATH_YUV422_YUV422;
    }
    appObj->ipipeInputCfg.procWin.cropStartX = 0U;
    appObj->ipipeInputCfg.procWin.cropStartY = 0U;
    appObj->ipipeInputCfg.procWin.cropWidth  = cfg->inWidth;
    appObj->ipipeInputCfg.procWin.cropHeight = cfg->inHeight;

    status = Fvid2_control(
        appObj->drvHandle,
        VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
        &appObj->ipipeCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MApp: IPIPE GetConfig Failed\r\n");

        return -1;
    }

    /* ISS_TODO Enable YEE here for YUV input case only */
    return (status);
}

/** \brief Utility function used to allocate input & output frames
 */
static Int32 AppAllocFrames(vpsAppObject_t *appObj, vpsAppFrmConfig_t *pCfg)
{
    Int32        status = FVID2_SOK;
    UInt32       frmCnt;
    Fvid2_Format fmt;

    Fvid2Format_init(&fmt);
    fmt.width      = pCfg->inWidth;
    fmt.height     = pCfg->inHeight;
    fmt.pitch[0U]  = pCfg->inPitch;
    fmt.pitch[1U]  = pCfg->inPitch;
    fmt.pitch[2U]  = pCfg->inPitch;
    fmt.dataFormat = pCfg->inFormat;
    fmt.bpp        = pCfg->inBpp;

    /* Allocate the Buffer for the Input Frame */
    status = BspUtils_memFrameAlloc(&fmt, &appObj->inFrames[0U], 1U);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
        return (status);
    }
    /* Copy same FVID2 frames for all inputs */
    for (frmCnt = 1U; frmCnt < NUMBER_OUT_FRAMES; frmCnt++)
    {
        BspUtils_memcpy(
            &appObj->inFrames[frmCnt],
            &appObj->inFrames[0U],
            sizeof (Fvid2_Frame));
    }

    /* Allocate the Buffer for the Output Frame */
    Fvid2Format_init(&fmt);
    fmt.width      = pCfg->outAWidth;
    fmt.height     = pCfg->outAHeight;
    fmt.pitch[0U]  = pCfg->outAPitch;
    fmt.pitch[1U]  = pCfg->outAPitch;
    fmt.pitch[2U]  = pCfg->outAPitch;
    fmt.dataFormat = pCfg->outAFormat;
    fmt.bpp        = pCfg->outABpp;
    status         = BspUtils_memFrameAlloc(&fmt, appObj->outFrames,
                                            NUMBER_OUT_FRAMES);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
        return (status);
    }

    return (status);
}

/** \brief Utility function used to close the driver
 */
static Int32 AppCloseDriver(vpsAppObject_t *appObj)
{
    if (NULL != appObj->drvHandle)
    {
        Fvid2_delete(appObj->drvHandle, NULL);
        appObj->drvHandle = NULL;
    }

    return 0;
}

/** \brief Utility function used to release acquired resources
 */
static void AppReleaseResources(vpsAppObject_t *appObj)
{
    int32_t status, frmCnt;

    Semaphore_delete(&appObj->frameCompletionSem);
    /* Free up the buffer allocated for the input and output frames */
    if (NULL != appObj->inFrames[0U].addr[0U][0U])
    {
        status = BspUtils_memFrameFree(
            &appObj->ispPrms.inFmt,
            &appObj->inFrames[0U],
            1U);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Input Frame Free Failed!!!\r\n");
        }
        /* Set the chroma address */
        for (frmCnt = 0U; frmCnt < NUMBER_OUT_FRAMES; frmCnt++)
        {
            appObj->inFrames[frmCnt].addr[0U][0U] = NULL;
            appObj->inFrames[frmCnt].addr[0U][1U] = NULL;
        }
    }

    /* Free up the buffer allocated for the output frames */
    if (NULL != appObj->outFrames[0U].addr[0U][0U])
    {
        status = BspUtils_memFrameFree(
            &appObj->rszCfg.instCfg[0U].outFmt,
            &appObj->outFrames[0U],
            1U);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Input Frame Free Failed!!!\r\n");
        }

        /* Set the chroma address */
        for (frmCnt = 0U; frmCnt < NUMBER_OUT_FRAMES; frmCnt++)
        {
            appObj->outFrames[frmCnt].addr[0U][0U] = NULL;
            appObj->outFrames[frmCnt].addr[0U][1U] = NULL;
        }
    }
}

/** \brief Callback function provided to driver, will be called once frame
 *          processing is completed. Will be called in an ISR context.
 */
static Int32 AppIssFrameProcessedCb(Fvid2_Handle handle, Ptr appData,
                                    Ptr reserved)
{
    vpsAppObject_t *pAppObj = (vpsAppObject_t *) appData;

    if (NULL == handle)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Handle is null in isr !!\r\n");
    }
    if (NULL == pAppObj)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME
                  ": App Object is null in isr !!\r\n");
    }
    else
    {
        Semaphore_post(pAppObj->frameCompletionSem);
    }

    return (FVID2_SOK);
}

/** \brief Main task that creates 2 tasks to process frames, creates semaphores
 *          and others required for tasks.
 */
static void AppIssMainTask()
{
    int32_t                status;
    UInt32                 size;
    UInt32                 isI2cInitReq, appMaxBSSMemHeapUS, cnt;
    Int32                  userInput;
    Task_Params            tskPrms;
    Semaphore_Params       semPrms;
    Semaphore_Handle       ispLock;
    BspUtils_MemHeapStatus startHeapStat;

    BspUtils_memGetHeapStat(&startHeapStat);

    isI2cInitReq = FALSE;
    status       = BspUtils_appDefaultInit(isI2cInitReq);
    if (status != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME "System Init Failed!!!\r\n");
    }

    /* Create semaphores required for each task */
    Semaphore_Params_init(&semPrms);
    gAppObj[0x0].frameCompletionSem = Semaphore_create(0U, &semPrms, NULL);
    if (NULL == gAppObj[0x0].frameCompletionSem)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        return;
    }
    Semaphore_Params_init(&semPrms);
    gAppObj[0x1].frameCompletionSem = Semaphore_create(0U, &semPrms, NULL);
    if (NULL == gAppObj[0x1].frameCompletionSem)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        return;
    }

    /* Exclusive access to ISP */
    Semaphore_Params_init(&semPrms);
    ispLock = Semaphore_create(1U, &semPrms, NULL);
    if (NULL == ispLock)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        return;
    }
    gAppObj[0x0].ispLock = ispLock;
    gAppObj[0x1].ispLock = ispLock;

    /* Memory for input / output frames */

    status = AppAllocFrames(&gAppObj[0x0], &gTestConfig[0x0]);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error in Allocating Buffers \r\n");
        return;
    }
    status = AppAllocFrames(&gAppObj[0x1], &gTestConfig[0x1]);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error in Allocating Buffers \r\n");
        return;
    }

    /* Associate input, output frame configuration with test tasks */
    gAppObj[0x0].pTestCfg = &gTestConfig[0x0];
    gAppObj[0x1].pTestCfg = &gTestConfig[0x1];

    BspOsal_printf(
        APP_NAME ": Load a RAW 12 BPP frame (%dx%d) at the address 0x%x \r\n",
        gAppObj[0x0].pTestCfg->inWidth, gAppObj[0x0].pTestCfg->inHeight,
        gAppObj[0x0].inFrames[0U].addr[0U][0U]);

    BspOsal_printf("ISSM2MApp: loadRaw(0x%x, 0, filename, 32, false)\r\n",
                   gAppObj[0x0].inFrames[0U].addr[0U][0U]);

    BspOsal_printf(
        APP_NAME ": Load a YUV frame (%dx%d) at the address 0x%x \r\n",
        gAppObj[0x1].pTestCfg->inWidth, gAppObj[0x1].pTestCfg->inHeight,
        gAppObj[0x1].inFrames[0U].addr[0U][0U]);
    BspOsal_printf("ISSM2MApp: loadRaw(0x%x, 0, filename, 32, false)\r\n",
                   gAppObj[0x1U].inFrames[0U].addr[0U][0U]);

    BspOsal_printf("ISSM2MApp: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    gAppObj[0x0].exitTask = FALSE;
    gAppObj[0x1].exitTask = FALSE;
    Task_Params_init(&tskPrms);
    tskPrms.priority    = 10U;
    tskPrms.stack       = AppIssRawTskStack;
    tskPrms.stackSize   = APP_TSK_STACK_SIZE;
    tskPrms.arg0        = (UArg) & gAppObj[0x0];
    AppIssRawTaskHandle = Task_create(
        (Task_FuncPtr) AppIssRawTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (AppIssRawTaskHandle != NULL));
    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(AppIssRawTaskHandle, APP_NAME);

    Task_Params_init(&tskPrms);
    tskPrms.priority    = 10U;
    tskPrms.stack       = AppIssYuvTskStack;
    tskPrms.stackSize   = APP_TSK_STACK_SIZE;
    tskPrms.arg0        = (UArg) & gAppObj[0x1];
    AppIssYuvTaskHandle = Task_create(
        (Task_FuncPtr) AppIssYuvTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (AppIssYuvTaskHandle != NULL));
    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(AppIssYuvTaskHandle, APP_NAME);

    /* Start the tasks */
    Semaphore_post(gAppObj[0x0].frameCompletionSem);
    Semaphore_post(gAppObj[0x1].frameCompletionSem);

    /* Wait for the test tasks to complete */
    while ((FALSE == gAppObj[0x0].exitTask) ||
           (FALSE == gAppObj[0x1].exitTask))
    {
        Task_sleep(100);
    }

    BspOsal_printf("ISSM2MApp: Processed %d frames \r\n", gAppObj[0x0].intrCnt);
    BspOsal_printf(
        APP_NAME ": Save the output frame (%dx%d) \r\n",
        gAppObj[0x0].pTestCfg->outAWidth, gAppObj[0x0].pTestCfg->outAHeight);
    size = gAppObj[0x0].pTestCfg->outAWidth * gAppObj[0x0].pTestCfg->outAHeight;
    if (FVID2_DF_YUV420SP_UV == gAppObj[0x0].pTestCfg->outAFormat)
    {
        size = (size * 3U) / 2U;
    }
    else
    {
        size *= 2U;
    }
    size /= 4U;

    for (cnt = 0U; cnt < NUMBER_OUT_FRAMES; cnt++)
    {
        BspOsal_printf(
            "ISSM2MApp: saveRaw(0, 0x%x, filename, %d, 32, false)\r\n",
            gAppObj[0x0].outFrames[cnt].addr[0U][0U], size);
    }
    BspOsal_printf(
        APP_NAME ": Save the output frame (%dx%d) \r\n",
        gAppObj[0x1].pTestCfg->outAWidth, gAppObj[0x1].pTestCfg->outAHeight);
    size = gAppObj[0x1].pTestCfg->outAWidth * gAppObj[0x1].pTestCfg->outAHeight;
    if (FVID2_DF_YUV420SP_UV == gAppObj[0x1].pTestCfg->outAFormat)
    {
        size = (size * 3U) / 2U;
    }
    else
    {
        size *= 2U;
    }
    size /= 4U;
    for (cnt = 0U; cnt < NUMBER_OUT_FRAMES; cnt++)
    {
        BspOsal_printf(
            "ISSM2MApp: saveRaw(0, 0x%x, filename, %d, 32, false)\r\n",
            gAppObj[0x1].outFrames[cnt].addr[0U][0U], size);
    }
    BspOsal_printf("ISSM2MApp: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    AppReleaseResources(&gAppObj[0x0]);
    AppReleaseResources(&gAppObj[0x1]);
    Semaphore_delete(&ispLock);
    BspUtils_prfLoadUnRegister(AppIssRawTaskHandle);
    BspUtils_prfLoadUnRegister(AppIssYuvTaskHandle);

    if (FVID2_SOK == status)
    {
        /* System de-init */
        status = BspUtils_appDefaultDeInit(isI2cInitReq);
        if (status != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System De-Init Failed!!!\r\n");
        }

        appMaxBSSMemHeapUS = 0;
    }

    if (FVID2_SOK == status)
    {
        GT_1trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Max BSS Memory used for test task: %d bytes\r\n",
                  appMaxBSSMemHeapUS);
        GT_1trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": Max stack used for main task (init sequence): %d bytes\r\n",
            BspOsal_getTaskStackUsage(NULL));
        GT_1trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Max system stack used (ISR): %d bytes\r\n",
                  BspOsal_getSystemStackUsage());
        BspUtils_appPrintMemStatus();
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Test Successful!!\r\n");
    }

    Task_delete(&AppIssRawTaskHandle);
    Task_delete(&AppIssYuvTaskHandle);
    BspUtils_memCheckHeapStat(&startHeapStat);
}

/**
 *  AppIssRawTask
 *  Reads in a 12 bit RAW / Bayer frame and converts it to configured output.
 */
static void AppIssRawTask(UArg arg0, UArg arg1)
{
    UInt32          frmNum;
    Fvid2_FrameList inFrmList;
    Fvid2_FrameList outFrmList;
    Int32           status  = FVID2_SOK;
    vpsAppObject_t *pAppObj = NULL;

    pAppObj = (vpsAppObject_t *) arg0;
    GT_assert(BspAppTrace, (NULL != pAppObj));

    /* Wait for the command to start */
    Semaphore_pend(pAppObj->frameCompletionSem, BIOS_WAIT_FOREVER);
    Semaphore_pend(pAppObj->ispLock, BIOS_WAIT_FOREVER);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Bayer/RAW Processing task starts !!!\r\n");

    pAppObj->intrCnt = 0U;
    status           = AppOpenDriver(pAppObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
        return;
    }

    status = AppSetParams(pAppObj, pAppObj->pTestCfg);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: SetParams Failed\r\n");
        AppCloseDriver(pAppObj);
        return;
    }

    status = AppSetRszConfig(pAppObj, pAppObj->pTestCfg);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: Resizer SetConfig Failed\r\n");
        AppCloseDriver(pAppObj);
        return;
    }

    status = AppSetIpipeConfig(pAppObj, pAppObj->pTestCfg);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: IPIPE SetConfig Failed\r\n");
        AppCloseDriver(pAppObj);
        return;
    }
    Semaphore_post(pAppObj->ispLock);
    Task_yield();

    while ((FVID2_SOK == status) &&
           (pAppObj->pTestCfg->numFrames > pAppObj->intrCnt))
    {
        Fvid2FrameList_init(&inFrmList);
        Fvid2FrameList_init(&outFrmList);

        frmNum = pAppObj->intrCnt % NUMBER_OUT_FRAMES;

        /* Make input and output frames list */
        inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
            &pAppObj->inFrames[frmNum];
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
            &pAppObj->outFrames[frmNum];
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        /* Lock is require here to ensure other tasks do not change config
         *  while processing a frame */
        Semaphore_pend(pAppObj->ispLock, BIOS_WAIT_FOREVER);

        status = AppSetParams(pAppObj, pAppObj->pTestCfg);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MApp: RAW Task SetParams Failed\r\n");
            break;
        }

        status = AppSetRszConfig(pAppObj, pAppObj->pTestCfg);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MApp: Resizer SetConfig Failed\r\n");
            break;
        }

        /* Submit Processing Request to the driver */
        status = Fvid2_processRequest( /* Raw Task */
            pAppObj->drvHandle,
            &inFrmList,
            &outFrmList);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Submitting request \r\n");
            AppCloseDriver(pAppObj);
            break;
        }
        /* Wait for the frame to be processed */
        Semaphore_pend(pAppObj->frameCompletionSem, BIOS_WAIT_FOREVER);
        Semaphore_post(pAppObj->ispLock);

        status = Fvid2_getProcessedRequest( /* Raw Task */
            pAppObj->drvHandle,
            &inFrmList,
            &outFrmList,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Getting completed Request\r\n");
            AppCloseDriver(pAppObj);
            break;
        }

        /* Check retrived Frames */
        if (inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] !=
            &pAppObj->inFrames[frmNum])
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Wrong Input Frame %d\r\n", frmNum);
            break;
        }
        if (outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] !=
            &pAppObj->outFrames[frmNum])
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Wrong Output Frame %d\r\n", frmNum);
            break;
        }

        /* If there are changes required
         *  Semaphore_pend(pAppObj->ispLock, BIOS_WAIT_FOREVER);
         *
         *  Apply any config updates here
         *
         *  Semaphore_post(pAppObj->ispLock);
         */
        pAppObj->intrCnt++;
        Task_yield();
    }

    status = AppCloseDriver(pAppObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
    }

    pAppObj->exitTask = TRUE;
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Bayer/RAW Processing task completes !!!\r\n");
    return;
}

/**
 *  AppIssYuvTask
 *  Reads in a 16 bit YUV frame and scales it to configured output.
 */
static void AppIssYuvTask(UArg arg0, UArg arg1)
{
    UInt32          frmNum;
    Fvid2_FrameList inFrmList;
    Fvid2_FrameList outFrmList;
    Int32           status  = FVID2_SOK;
    vpsAppObject_t *pAppObj = NULL;

    pAppObj = (vpsAppObject_t *) arg0;
    GT_assert(BspAppTrace, (NULL != pAppObj));

    /* Wait for the command to start */
    Semaphore_pend(pAppObj->frameCompletionSem, BIOS_WAIT_FOREVER);
    Semaphore_pend(pAppObj->ispLock, BIOS_WAIT_FOREVER);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": YUV Processing task starts !!!\r\n");

    pAppObj->intrCnt = 0U;
    status           = AppOpenDriver(pAppObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
        return;
    }

    status = AppSetParams(pAppObj, pAppObj->pTestCfg);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: SetParams Failed\r\n");
        AppCloseDriver(pAppObj);
        return;
    }

    status = AppSetRszConfig(pAppObj, pAppObj->pTestCfg);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: Resizer SetConfig Failed\r\n");
        AppCloseDriver(pAppObj);
        return;
    }

    status = AppSetIpipeConfig(pAppObj, pAppObj->pTestCfg);
    if (FVID2_SOK != status)
    {
        Bsp_printf("ISSM2MApp: IPIPE SetConfig Failed\r\n");
        AppCloseDriver(pAppObj);
        return;
    }
    Semaphore_post(pAppObj->ispLock);

    while ((FVID2_SOK == status) &&
           (pAppObj->pTestCfg->numFrames > pAppObj->intrCnt))
    {
        Fvid2FrameList_init(&inFrmList);
        Fvid2FrameList_init(&outFrmList);

        frmNum = pAppObj->intrCnt % NUMBER_OUT_FRAMES;

        /* Make input and output frames list */
        inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
            &pAppObj->inFrames[frmNum];
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
            &pAppObj->outFrames[frmNum];
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        /* Submit Processing Request to the driver */
        /* Lock is require here to ensure other tasks do not change config
         *  while processing a frame */
        Semaphore_pend(pAppObj->ispLock, BIOS_WAIT_FOREVER);

        status = AppSetParams(pAppObj, pAppObj->pTestCfg);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MApp: SetParams Failed\r\n");
            break;
        }
        status = AppSetRszConfig(pAppObj, pAppObj->pTestCfg);
        if (FVID2_SOK != status)
        {
            Bsp_printf("ISSM2MApp: Resizer SetConfig Failed\r\n");
            break;
        }

        status = Fvid2_processRequest( /* YUV Task */
            pAppObj->drvHandle,
            &inFrmList,
            &outFrmList);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Submitting request \r\n");
            AppCloseDriver(pAppObj);
            break;
        }

        /* Wait for the frame to be processed */
        Semaphore_pend(pAppObj->frameCompletionSem, BIOS_WAIT_FOREVER);
        Semaphore_post(pAppObj->ispLock);
        status = Fvid2_getProcessedRequest(
            pAppObj->drvHandle,
            &inFrmList,
            &outFrmList,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Error Getting completed Request\r\n");
            AppCloseDriver(pAppObj);
            break;
        }

        /* Check retrived Frames */
        if (inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] !=
            &pAppObj->inFrames[frmNum])
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Wrong Input Frame %d\r\n", frmNum);
            break;
        }
        if (outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] !=
            &pAppObj->outFrames[frmNum])
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      APP_NAME ": Wrong Output Frame %d\r\n", frmNum);
            break;
        }

        /* If there are changes required
         *  Semaphore_pend(pAppObj->ispLock, BIOS_WAIT_FOREVER);
         *
         *  Apply any config updates here
         *
         *  Semaphore_post(pAppObj->ispLock);
         */
        pAppObj->intrCnt++;
    }

    status = AppCloseDriver(pAppObj);
    if (FVID2_SOK != status)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
    }

    pAppObj->exitTask = TRUE;
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": YUV Processing task completes !!!\r\n");
    return;
}

