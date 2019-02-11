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
 *  \file M2mIssWdrScale_main.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <M2mIssWdr_main.h>
#include <ipipeif_lut.h>
#include <ti/drv/vps/include/iss/vps_cfgglbce.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define APP_TSK_STACK_SIZE      (10U * 1024U)

/* Input Frame Format, WDR flow uses 1280x960 input image with GRBG
 * 12bit companded input data*/
#define IN_WIDTH                (1280u)
#define IN_HEIGHT               (960u)
#define IN_PITCH                (IN_WIDTH * 2)
#define IN_FORMAT               (FVID2_DF_BAYER_GRBG)
#define IN_BPP                  (FVID2_BPP_BITS12)

/* PASS1 Output Frame Format, */
#define PASS1_OUT_WIDTH         (1280u)
#define PASS1_OUT_HEIGHT        (960u)
#define PASS1_OUT_PITCH         (PASS1_OUT_WIDTH * 2)

/** \brief Resizer output format
 *         it could be one of FVID2_DF_YUV420SP_UV, FVID2_DF_YUV422I_UYVY or
 *         FVID2_DF_BAYER_RAW;
 */
#define PASS1_OUT_FORMAT        (FVID2_DF_BAYER_RAW)
#define PASS1_OUT_BPP           (FVID2_BPP_BITS16)

/* PASS1 Output Frame Format */
#define PASS2_OUT_FORMAT        (FVID2_DF_YUV420SP_UV)
/* Bpps not used for the YUV data format */
#define PASS2_OUT_BPP           (FVID2_BPP_BITS12)

/**< Output Frame  */
#define PASS2_OUT_WIDTH         (1280u)
#define PASS2_OUT_HEIGHT        (960u)

#define PASS2_OUT_PITCH         (PASS2_OUT_WIDTH)

#define TEST_REP_CNT            (1u)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct vpsAppPassCfg
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
} vpsAppPassCfg_t;

/** \brief Application Object containing all the parameters
 */
typedef struct vpsAppObject
{
    vpsAppPassCfg_t               p1Cfg;
    vpsAppPassCfg_t               p2Cfg;
    UInt32                        enableP2;

    vpsissRszCtrl_t               rszCtrl;
    /**< Resizer Control structure containing pointer to the
     *   resizer configuration */
    vpsissRszCfg_t                rszCfg;
    /**< Resizer configuration */

    vpsissIpipeifCtrl_t           ipipeifCtrl;
    /**< IPIPE Control structure containing pointer to the
     *   IPIPE configuration */
    vpsissIpipeifWdrCfg_t         wdrCfg;
    /**< IPIPEIF WDR Configuration */
    vpsissIpipeifSaturaInsts_t    satCfg;
    /**< IPIPEIF WDR Configuration */
    vpsissIpipeifDeCompandInsts_t cmpDecmpCfg;
    /**< IPIPEIF Companding/DeCompanding Configuration */
    vpsissIpipeifLutConfig_t      ipipeifLut;
    /**< IPIPEIF Compand/decompanding Luts */

    vpsissIpipeCtrl_t             ipipeCtrl;
    vpsissIpipeDpcLutConfig_t     dpcLutCfg;
    vpsissIpipeGammaConfig_t      gammaCfg;
    vpsissIpipe3DLutConfig_t      lut3d;
    vpsissIpipeEeConfig_t         eeCfg;
    vpsissIpipeGicConfig_t        gicCfg;
    vpsissIpipeLscConfig_t        lscCfg;
    vpsissIpipeNf2Config_t        nf1Cfg;
    vpsissIpipeNf2Config_t        nf2Cfg;
    vpsissIpipeLutFmtCnvt_t       lutFmtCnvt;

    UInt32                        enableLsc;
    UInt32                        enableGic;
    UInt32                        enableYee;
    UInt32                        enable3dLut;
    UInt32                        enableGamma;
    UInt32                        enableNf1;
    UInt32                        enableNf2;

    UInt32                        dpcLutSize;
    UInt32                        dpcLut[1024u];
    vpsissIpipeDpcOtfConfig_t     dpcOtfCfg;

    vpsissNsf3Config_t            nsf3vCfg;

    UInt32                        enableGlbce;
    UInt32                        enableNsf3;
    UInt32                        enableAf;
    UInt32                        enableAewb;
    UInt32                        enableDpc;
    UInt32                        enableCnf;
    UInt32                        enableIpipeifDpc;
    UInt32                        enableIsifVfdc;

    vpsissGlbceConfig_t           glbceCfg;
    vpsissGlbcePerceptConfig_t    glbcePerceptCfg;
    vpsissGlbceCtrl_t             glbceCtrl;

    vpsissCnfConfig_t             cnfCfg;

    Fvid2_Frame                   frames[10U];
    /**< Array of FVID Frames */
    Fvid2_FrameList               inFrmList;
    /**< Input Frames List */
    Fvid2_FrameList               outFrmList;
    /**< Output Frames List */

    Vps_M2mIntfStatsParams        statsPrms;
    /**< Statistics parameters */
} vpsAppObject_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void AppIssWdr_createTask();
static void App_mainTestTask(void);
static Int32 AppOpenDriver(vpsAppObject_t *appObj);
static Int32 AppAllocFrames(vpsAppObject_t *appObj);
static Int32 AppCloseDriver(vpsAppObject_t *appObj);
static Int32 AppSetParams(vpsAppObject_t *appObj);
static Int32 AppSetIpipeifWdrConfig(vpsAppObject_t *appObj, uint32_t isPass2);
static Int32 AppSetSatCfg(vpsAppObject_t *appObj, UInt32 isPass2);
static Int32 AppSetIpipeConfig(vpsAppObject_t *appObj);
static Int32 AppSetNsf3vConfig(vpsAppObject_t *appObj);
static Int32 AppSetGlbceConfig(vpsAppObject_t *appObj);
static Int32 AppSetCnfConfig(vpsAppObject_t *appObj);
static Int32 AppSetRszConfig(vpsAppObject_t *appObj, UInt32 isPass2);

static Int32 AppIssWdr_callback(Fvid2_Handle handle, Ptr appData, Ptr reserved);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8     AppMainTskStack[APP_TSK_STACK_SIZE];

/* Test complete semaphore used to sync between test task and main task. */
Semaphore_Handle AppTestCompleteSem;

Task_Handle      AppIssWdrTaskHandle;

vpsAppObject_t   gAppObj;

static Vps_M2mIntfFrameStats gP1cfgFrmStat[1000];
static Vps_M2mIntfFrameStats gP2cfgFrmStat[1000];

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

    AppIssWdr_createTask();

    BIOS_start();

    return (0);
}

static void AppIssWdr_createTask()
{
    Task_Params tskPrms;

    Task_Params_init(&tskPrms);
    tskPrms.priority    = 10U;
    tskPrms.stack       = AppMainTskStack;
    tskPrms.stackSize   = APP_TSK_STACK_SIZE;
    AppIssWdrTaskHandle = Task_create(
        (Task_FuncPtr) App_mainTestTask,
        &tskPrms,
        NULL);
    GT_assert(BspAppTrace, (AppIssWdrTaskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(AppIssWdrTaskHandle, APP_NAME);
}

/**
 *  App_mainTestTask
 *  Application test task.
 */
static void App_mainTestTask(void)
{
    UInt32                 cnt;
    Int32                  userInput;
    Int32                  retVal = FVID2_SOK;
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

    gAppObj.enableP2    = TRUE;
    gAppObj.enableGlbce = TRUE;
    gAppObj.enableNsf3  = TRUE;
    gAppObj.enableAf    = TRUE;
    gAppObj.enableAewb  = TRUE;
    gAppObj.enableDpc   = TRUE;

    gAppObj.enableLsc        = TRUE;
    gAppObj.enableGic        = TRUE;
    gAppObj.enableYee        = TRUE;
    gAppObj.enable3dLut      = TRUE;
    gAppObj.enableGamma      = TRUE;
    gAppObj.enableCnf        = TRUE;
    gAppObj.enableNf1        = TRUE;
    gAppObj.enableNf2        = TRUE;
    gAppObj.enableIpipeifDpc = FALSE;

    retVal = AppOpenDriver(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Opening Driver\n");
        return;
    }

    retVal = AppSetParams(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error Seting Driver Parameters\r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    if (TRUE == gAppObj.enableNsf3)
    {
        retVal = AppSetNsf3vConfig(&gAppObj);
        if (FVID2_SOK != retVal)
        {
            Bsp_printf("ISSM2MWdrApp: Nsf3v SetConfig Failed\r\n");
            AppCloseDriver(&gAppObj);
            return;
        }
    }

    if (TRUE == gAppObj.enableGlbce)
    {
        retVal = AppSetGlbceConfig(&gAppObj);
        if (FVID2_SOK != retVal)
        {
            Bsp_printf("ISSM2MWdrApp: Glbce SetConfig Failed\r\n");
            AppCloseDriver(&gAppObj);
            return;
        }
    }

    /* Both passes require to be updated */
    retVal = AppSetIpipeifWdrConfig(&gAppObj, FALSE);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed for P1\r\n");
        AppCloseDriver(&gAppObj);
        return;
    }
    retVal = AppSetIpipeifWdrConfig(&gAppObj, TRUE);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPEIF WDR SetConfig Failed for P2\r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    retVal = AppSetIpipeConfig(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    retVal = AppSetRszConfig(&gAppObj, FALSE);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("ISSM2MWdrApp: Resizer SetConfig Failed\r\n");
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
        gAppObj.p1Cfg.drvHandle,
        IOCTL_VPS_M2M_INTF_SET_STATS_PARAMS,
        &gAppObj.statsPrms,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not set Statistics parameters for Pass1 \r\n");
        AppCloseDriver(&gAppObj);
        return;
    }

    retVal = Fvid2_control(
        gAppObj.p2Cfg.drvHandle,
        IOCTL_VPS_M2M_INTF_SET_STATS_PARAMS,
        &gAppObj.statsPrms,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not set Statistics parameters for Pass2 \r\n");
        AppCloseDriver(&gAppObj);
        return;
    }
    BspOsal_printf(
        "ISSM2MWdrApp: Load the input frame (%dx%d) at the address 0x%x\r\n",
        IN_WIDTH, IN_HEIGHT, gAppObj.frames[0U].addr[0u][0u]);
    BspOsal_printf("ISSM2MWdrApp: loadRaw(0x%x, 0, filename, 32, false)\r\n",
                   gAppObj.frames[0U].addr[0u][0u]);
    BspOsal_printf("ISSM2MWdrApp: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    for (cnt = 0U; cnt < TEST_REP_CNT; cnt++)
    {
        BspUtils_memGetHeapStat(&startHeapStat1);

        Fvid2FrameList_init(&gAppObj.inFrmList);
        Fvid2FrameList_init(&gAppObj.outFrmList);

        retVal = AppSetRszConfig(&gAppObj, FALSE);
        if (FVID2_SOK != retVal)
        {
            Bsp_printf("ISSM2MWdrApp: Resizer SetConfig Failed\r\n");
            AppCloseDriver(&gAppObj);
            return;
        }

        retVal = AppSetSatCfg(&gAppObj, FALSE);
        if (FVID2_SOK != retVal)
        {
            Bsp_printf(
                "ISSM2MWdrApp: IPIPEIF Saturation SetConfig Failed\r\n");
            AppCloseDriver(&gAppObj);
            return;
        }

        /* Make input and output frames list */
        gAppObj.inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
            &gAppObj.frames[0U];
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        gAppObj.inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        gAppObj.outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
            &gAppObj.frames[1U];
        /* Always provide number of frames in the frame list to be max
         * streams of isp */
        gAppObj.outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

        /* Submit Processing Request to the driver */
        retVal = Fvid2_processRequest(
            gAppObj.p1Cfg.drvHandle,
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
            gAppObj.p1Cfg.drvHandle,
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
        Bsp_printf("ISSM2MWdrApp: Frame Processing Completed for the Pass1\r\n");

        if (TRUE == gAppObj.enableP2)
        {
            retVal = AppSetRszConfig(&gAppObj, TRUE);
            if (FVID2_SOK != retVal)
            {
                Bsp_printf("ISSM2MWdrApp: Resizer SetConfig Failed\r\n");
                AppCloseDriver(&gAppObj);
                return;
            }

            if (TRUE == gAppObj.enableCnf)
            {
                retVal = AppSetCnfConfig(&gAppObj);
                if (FVID2_SOK != retVal)
                {
                    Bsp_printf("ISSM2MWdrApp: CNF SetConfig Failed\r\n");
                    AppCloseDriver(&gAppObj);
                    return;
                }
            }

            retVal = AppSetSatCfg(&gAppObj, TRUE);
            if (FVID2_SOK != retVal)
            {
                Bsp_printf(
                    "ISSM2MWdrApp: IPIPEIF Saturation SetConfig Failed\r\n");
                AppCloseDriver(&gAppObj);
                return;
            }

            /* Make input and output frames list */
            gAppObj.inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
                &gAppObj.frames[0U];
            gAppObj.inFrmList.frames[VPS_ISS_STREAM_ID_INPUT_N1] =
                &gAppObj.frames[1U];
            /* Always provide number of frames in the frame list to be max
             * streams of isp */
            gAppObj.inFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

            gAppObj.outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A] =
                &gAppObj.frames[2U];
            /* Always provide number of frames in the frame list to be max
             * streams of isp */
            gAppObj.outFrmList.numFrames = VPS_ISS_STREAM_ID_MAX;

            /* Submit Processing Request to the driver */
            retVal = Fvid2_processRequest(
                gAppObj.p2Cfg.drvHandle,
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
                gAppObj.p2Cfg.drvHandle,
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
            Bsp_printf(
                "ISSM2MWdrApp: Frame Processing Completed for the Pass2\r\n");
        }

        BspUtils_memCheckHeapStat(&startHeapStat1);
    }

    BspOsal_printf(
        "ISSM2MWdrApp: Save the output frame (%dx%d) at the address 0x%x\r\n",
        IN_WIDTH, IN_HEIGHT, gAppObj.frames[2U].addr[0u][0u]);
    BspOsal_printf("ISSM2MWdrApp: saveRaw(0, 0x%x, filename, 32, false)\r\n",
                   gAppObj.frames[2U].addr[0u][0u]);
    BspOsal_printf("ISSM2MWdrApp: Enter any number (in UART console) to continue\r\n");
    BspUtils_uartGetNum(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);

    /* Print the Statistics */
    Bsp_printf("PASS1 Statistics ======================\r\n");
    VpsM2mIntfStats_init(&gAppObj.p1Cfg.stats);

    retVal = Fvid2_control(
        gAppObj.p1Cfg.drvHandle,
        IOCTL_VPS_M2M_INTF_GET_STATS,
        &gAppObj.p1Cfg.stats,
        NULL);
    if (FVID2_SOK == retVal)
    {
        Bsp_printf("ISSM2MWdrApp: Processed Request = %d \r\n",
                   gAppObj.p1Cfg.stats.numProcessedReq);
        Bsp_printf("ISSM2MWdrApp: Error Request = %d \r\n",
                   gAppObj.p1Cfg.stats.numErrorReq);
        Bsp_printf("ISSM2MWdrApp: Pending Request = %d \r\n",
                   gAppObj.p1Cfg.stats.numPendingReq);

        for (cnt = 0U; cnt < gAppObj.p1Cfg.stats.numStats; cnt++)
        {
            Bsp_printf("ISSM2MWdrApp: %5d %5d %5d %5d\r\n",
                       gAppObj.p1Cfg.stats.frmStats[cnt].queueTimeStamp,
                       gAppObj.p1Cfg.stats.frmStats[cnt].startProcTimeStamp,
                       gAppObj.p1Cfg.stats.frmStats[cnt].endProcTimeStamp,
                       gAppObj.p1Cfg.stats.frmStats[cnt].dequeueTimeStamp);
        }
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not get Statistics for Pass1 \r\n");
    }

    /* Print the Statistics */
    Bsp_printf("PASS2 Statistics ======================\r\n");
    VpsM2mIntfStats_init(&gAppObj.p2Cfg.stats);

    retVal = Fvid2_control(
        gAppObj.p2Cfg.drvHandle,
        IOCTL_VPS_M2M_INTF_GET_STATS,
        &gAppObj.p2Cfg.stats,
        NULL);
    if (FVID2_SOK == retVal)
    {
        Bsp_printf("ISSM2MWdrApp: Processed Request = %d \r\n",
                   gAppObj.p2Cfg.stats.numProcessedReq);
        Bsp_printf("ISSM2MWdrApp: Error Request = %d \r\n",
                   gAppObj.p2Cfg.stats.numErrorReq);
        Bsp_printf("ISSM2MWdrApp: Pending Request = %d \r\n",
                   gAppObj.p2Cfg.stats.numPendingReq);

        for (cnt = 0U; cnt < gAppObj.p2Cfg.stats.numStats; cnt++)
        {
            Bsp_printf("ISSM2MWdrApp: %5d %5d %5d %5d\r\n",
                       gAppObj.p2Cfg.stats.frmStats[cnt].queueTimeStamp,
                       gAppObj.p2Cfg.stats.frmStats[cnt].startProcTimeStamp,
                       gAppObj.p2Cfg.stats.frmStats[cnt].endProcTimeStamp,
                       gAppObj.p2Cfg.stats.frmStats[cnt].dequeueTimeStamp);
        }
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Could not get Statistics for Pass1 \r\n");
    }

    retVal = AppCloseDriver(&gAppObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Error closing driver\n");
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
        BspUtils_appPrintMemStatus();
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Test Successfull!!\r\n");
    }

    BspUtils_memCheckHeapStat(&startHeapStat);
    return;
}

static Int32 AppIssWdr_callback(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    vpsAppObject_t *appObj = (vpsAppObject_t *) appData;

    if (NULL == appObj)
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

static Int32 AppAllocFrames(vpsAppObject_t *appObj)
{
    Int32 retVal = FVID2_SOK;

    /* Allocate the Buffer for the Input Frame */
    retVal = BspUtils_memFrameAlloc(
        &appObj->p1Cfg.ispPrms.inFmt,
        &appObj->frames[0U],
        2U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
        return (retVal);
    }

    /* Allocate the Buffer for the Output Frame */
    retVal = BspUtils_memFrameAlloc(
        &appObj->rszCfg.instCfg[0U].outFmt,
        &appObj->frames[2U],
        1U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Display Frame Alloc Failed!!!\r\n");
        return (retVal);
    }
    appObj->frames[2U].addr[0U][1U] =
        (Ptr) (((UInt32) appObj->frames[2U].addr[0U][0U]) + PASS2_OUT_WIDTH *
               PASS2_OUT_HEIGHT);

    return (retVal);
}

static Int32 AppOpenDriver(vpsAppObject_t *appObj)
{
    Fvid2CbParams_init(&appObj->p1Cfg.cbPrms);
    appObj->p1Cfg.cbPrms.cbFxn   = AppIssWdr_callback;
    appObj->p1Cfg.cbPrms.appData = appObj;

    VpsM2mIntfCreateParams_init(&appObj->p1Cfg.createPrms);
    appObj->p1Cfg.createPrms.numCh           = 1U;
    appObj->p1Cfg.createPrms.chInQueueLength = 1U;
    appObj->p1Cfg.createPrms.maxStatsInst    = 1000U;
    appObj->p1Cfg.createPrms.frmStats        = gP1cfgFrmStat;
    appObj->p1Cfg.createPrms.pAdditionalArgs = (Ptr) & appObj->p1Cfg.openPrms;

    VpsM2mIntfCreateStatus_init(&appObj->p1Cfg.createStatusPrms);
    appObj->p1Cfg.createStatusPrms.pAdditionalStatus =
        (Ptr) & appObj->p1Cfg.retPrms;

    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = FALSE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = FALSE;
    appObj->p1Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = FALSE;
    appObj->p1Cfg.openPrms.arg = NULL;

    appObj->p1Cfg.drvHandle = Fvid2_create(
        FVID2_VPS_COMMON_M2M_INTF_DRV,
        VPS_M2M_ISS_INST_CAL_ISP,
        &appObj->p1Cfg.createPrms,
        &appObj->p1Cfg.createStatusPrms,
        &appObj->p1Cfg.cbPrms);
    if (NULL == appObj->p1Cfg.drvHandle)
    {
        Bsp_printf("ISSM2MWdrApp: Could not open driver for P1\r\n");
        return -1;
    }

    if (TRUE == appObj->enableP2)
    {
        Fvid2CbParams_init(&appObj->p2Cfg.cbPrms);
        appObj->p2Cfg.cbPrms.cbFxn   = AppIssWdr_callback;
        appObj->p2Cfg.cbPrms.appData = appObj;

        VpsM2mIntfCreateParams_init(&appObj->p2Cfg.createPrms);
        appObj->p2Cfg.createPrms.numCh           = 1U;
        appObj->p2Cfg.createPrms.chInQueueLength = 1U;
        appObj->p2Cfg.createPrms.maxStatsInst    = 1000U;
        appObj->p2Cfg.createPrms.frmStats        = gP2cfgFrmStat;
        appObj->p2Cfg.createPrms.pAdditionalArgs = (Ptr) &
                                                   appObj->p2Cfg.openPrms;

        VpsM2mIntfCreateStatus_init(&appObj->p2Cfg.createStatusPrms);
        appObj->p2Cfg.createStatusPrms.pAdditionalStatus =
            (Ptr) & appObj->p2Cfg.retPrms;

        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3]    = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE]   = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF]    = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE]   = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ]     = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF]     = TRUE;
        appObj->p2Cfg.openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A]     = FALSE;
        appObj->p2Cfg.openPrms.arg = NULL;

        appObj->p2Cfg.drvHandle = Fvid2_create(
            FVID2_VPS_COMMON_M2M_INTF_DRV,
            VPS_M2M_ISS_INST_CAL_ISP,
            &appObj->p2Cfg.createPrms,
            &appObj->p2Cfg.createStatusPrms,
            &appObj->p2Cfg.cbPrms);
        if (NULL == appObj->p2Cfg.drvHandle)
        {
            Bsp_printf("ISSM2MWdrApp: Could not open driver for P2\r\n");
            return -1;
        }
    }
    return (FVID2_SOK);
}

static Int32 AppCloseDriver(vpsAppObject_t *appObj)
{
    Int32 retVal = FVID2_SOK;

    /* Free up the buffer allocated for the input and output frames */
    if (NULL != appObj->frames[0U].addr[0U][0U])
    {
        retVal = BspUtils_memFrameFree(
            &appObj->p1Cfg.ispPrms.inFmt,
            &appObj->frames[0U],
            2U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Input Frame Free Failed!!!\r\n");
        }
        appObj->frames[0U].addr[0U][0U] = NULL;
        appObj->frames[1U].addr[0U][0U] = NULL;
    }
    if (NULL != appObj->frames[2U].addr[0U][0U])
    {
        retVal = BspUtils_memFrameFree(
            &appObj->p1Cfg.ispPrms.inFmt,
            &appObj->frames[2U],
            1U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Output Frame Free Failed!!!\r\n");
        }
        appObj->frames[2U].addr[0U][0U] = NULL;
    }
    if (NULL != appObj->p1Cfg.drvHandle)
    {
        Fvid2_delete(appObj->p1Cfg.drvHandle, NULL);
        appObj->p1Cfg.drvHandle = NULL;
    }
    if (NULL != appObj->p2Cfg.drvHandle)
    {
        Fvid2_delete(appObj->p2Cfg.drvHandle, NULL);
        appObj->p2Cfg.drvHandle = NULL;
    }

    return 0;
}

static Int32 AppSetParams(vpsAppObject_t *appObj)
{
    Int32 status;

    /* Set the Params */
    appObj->p1Cfg.ispPrms.inFmt.width         = IN_WIDTH;
    appObj->p1Cfg.ispPrms.inFmt.height        = IN_HEIGHT;
    appObj->p1Cfg.ispPrms.inFmt.pitch[0u]     = IN_PITCH;
    appObj->p1Cfg.ispPrms.inFmt.bpp           = IN_BPP;
    appObj->p1Cfg.ispPrms.inFmt.dataFormat    = IN_FORMAT;
    appObj->p1Cfg.ispPrms.inFmtN_1.width      = IN_WIDTH;
    appObj->p1Cfg.ispPrms.inFmtN_1.height     = IN_HEIGHT;
    appObj->p1Cfg.ispPrms.inFmtN_1.pitch[0u]  = IN_PITCH;
    appObj->p1Cfg.ispPrms.inFmtN_1.bpp        = IN_BPP;
    appObj->p1Cfg.ispPrms.inFmtN_1.dataFormat = IN_FORMAT;

    appObj->p1Cfg.ispPrms.enableWdrMerge = FALSE;
    appObj->p1Cfg.ispPrms.enableDfs      = FALSE;
    appObj->p1Cfg.ispPrms.nsf3Path       = VPS_ISS_NSF3_PATH_ISP;
    appObj->p1Cfg.ispPrms.glbcePath      =
        VPS_ISS_GLBCE_PATH_DISABLED;
    appObj->p1Cfg.ispPrms.enableDpcPreNsf3          = TRUE;
    appObj->p1Cfg.ispPrms.enableCnf                 = FALSE;
    appObj->p1Cfg.ispPrms.enableRszInputFromIpipeif = TRUE;

    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] = TRUE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A]       = TRUE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1]    = FALSE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B]       = FALSE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AF]          = FALSE;
    appObj->p1Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB]        = FALSE;

    appObj->p1Cfg.ispPrms.useWen = FALSE;
    appObj->p1Cfg.ispPrms.hdPol  = FVID2_POL_HIGH;
    appObj->p1Cfg.ispPrms.vdPol  = FVID2_POL_HIGH;

    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
        &appObj->p1Cfg.ispPrms,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: SetParams Failed for P1\r\n");
        return -1;
    }

    if (TRUE == appObj->enableP2)
    {
        /* Set the Params for Pass2 */
        appObj->p2Cfg.ispPrms.inFmt.width         = IN_WIDTH;
        appObj->p2Cfg.ispPrms.inFmt.height        = IN_HEIGHT;
        appObj->p2Cfg.ispPrms.inFmt.pitch[0u]     = IN_PITCH;
        appObj->p2Cfg.ispPrms.inFmt.bpp           = IN_BPP;
        appObj->p2Cfg.ispPrms.inFmt.dataFormat    = IN_FORMAT;
        appObj->p2Cfg.ispPrms.inFmtN_1.width      = IN_WIDTH;
        appObj->p2Cfg.ispPrms.inFmtN_1.height     = IN_HEIGHT;
        appObj->p2Cfg.ispPrms.inFmtN_1.pitch[0u]  = IN_PITCH;
        appObj->p2Cfg.ispPrms.inFmtN_1.bpp        = IN_BPP;
        appObj->p2Cfg.ispPrms.inFmtN_1.dataFormat = IN_FORMAT;

        appObj->p2Cfg.ispPrms.enableWdrMerge = TRUE;
        appObj->p2Cfg.ispPrms.enableDfs      = FALSE;
        appObj->p2Cfg.ispPrms.nsf3Path       = VPS_ISS_NSF3_PATH_ISP;
        appObj->p2Cfg.ispPrms.glbcePath      =
            VPS_ISS_GLBCE_PATH_ISP;
        appObj->p2Cfg.ispPrms.enableDpcPreNsf3          = TRUE;
        appObj->p2Cfg.ispPrms.enableCnf                 = gAppObj.enableCnf;
        appObj->p2Cfg.ispPrms.enableRszInputFromIpipeif = FALSE;

        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_CAL_RD_INPUT_0] =
            TRUE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_A] =
            TRUE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_INPUT_N1] =
            TRUE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_RSZ_B] =
            FALSE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AF] =
            FALSE;
        appObj->p2Cfg.ispPrms.enableStreams[VPS_ISS_STREAM_ID_AEWB] =
            FALSE;

        appObj->p2Cfg.ispPrms.useWen = FALSE;
        appObj->p2Cfg.ispPrms.hdPol  = FVID2_POL_HIGH;
        appObj->p2Cfg.ispPrms.vdPol  = FVID2_POL_HIGH;

        status = Fvid2_control(
            appObj->p2Cfg.drvHandle,
            IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS,
            &appObj->p2Cfg.ispPrms,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: SetParams Failed for P1\r\n");
            return -1;
        }
    }
    return (status);
}

Int32 AppSetIpipeifWdrConfig(vpsAppObject_t *appObj, uint32_t isPass2)
{
    Int32        status;
    Fvid2_Handle drvHndl;

    drvHndl = appObj->p1Cfg.drvHandle;
    if (TRUE == isPass2)
    {
        drvHndl = appObj->p2Cfg.drvHandle;
    }

    BspUtils_memset(&appObj->ipipeifLut, 0x0, sizeof (appObj->ipipeifLut));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT;
    appObj->ipipeifCtrl.pLutCfg = &appObj->ipipeifLut;

    appObj->ipipeifLut.vportDecompandLut = vport_lut;
    appObj->ipipeifLut.vportLutSize      = 513u * 4u;
    appObj->ipipeifLut.memifDecompandLut = sd_lut;
    appObj->ipipeifLut.memifLutSize      = 513u * 4u;
    appObj->ipipeifLut.wdrCompandLut     = wdr_lut;
    appObj->ipipeifLut.wdrLutSize        = 513u * 4u;

    /* Set the Companding and Decompanding LUTs in ipipeif */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Update LUT Config Failed\r\n");
        return -1;
    }

    BspUtils_memset(&appObj->satCfg, 0x0, sizeof (appObj->satCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG;
    appObj->ipipeifCtrl.pSatCfg = &appObj->satCfg;

    appObj->satCfg.vportSatCfg.enable = TRUE;
    appObj->satCfg.vportSatCfg.sat    = 4095u;
    appObj->satCfg.vportSatCfg.dcClmp = 0u;
    appObj->satCfg.vportSatCfg.dsf    = 0u;

    appObj->satCfg.memifSatCfg.enable = FALSE;
    appObj->satCfg.memifSatCfg.sat    = 4095u;
    appObj->satCfg.memifSatCfg.dcClmp = 0u;
    appObj->satCfg.memifSatCfg.dsf    = 0u;

    appObj->satCfg.isifSatCfg.enable = FALSE;
    appObj->satCfg.isifSatCfg.sat    = 4095u;
    appObj->satCfg.isifSatCfg.dcClmp = 0u;
    appObj->satCfg.isifSatCfg.dsf    = 0u;

    /* Set the Saturation Configuration in all three saturation
     * modules of ipipeif */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Saturation Config Failed\r\n");

        return -1;
    }

    BspUtils_memset(&appObj->cmpDecmpCfg, 0x0, sizeof (appObj->cmpDecmpCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module =
        VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
    appObj->ipipeifCtrl.pCompDecompCfg = &appObj->cmpDecmpCfg;

    appObj->cmpDecmpCfg.modInstId = VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_ALL;
    appObj->cmpDecmpCfg.vportDeCompandCfg.enable = TRUE;
    appObj->cmpDecmpCfg.vportDeCompandCfg.size   = 3u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.useLut = 0u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.xthr1  = 2047u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.xthr2  = 3040u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.xthr3  = 4000u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.ythr1  = 4096u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.ythr2  = 65536u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.ythr3  = 1048575u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.slope1 = 128u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.slope2 = 3960u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.slope3 = 65535u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.slope4 = 0u;
    appObj->cmpDecmpCfg.vportDeCompandCfg.shift  = 6u;

    appObj->cmpDecmpCfg.memifDeCompandCfg.enable = FALSE;
    appObj->cmpDecmpCfg.memifDeCompandCfg.size   = 7u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.useLut = 0u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.xthr1  = 4095u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.xthr2  = 1048575u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.xthr3  = 1048575u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.ythr1  = 4095u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.ythr2  = 1048575u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.ythr3  = 1048575u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.slope1 = 128u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.slope2 = 128u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.slope3 = 1024u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.slope4 = 1024u;
    appObj->cmpDecmpCfg.memifDeCompandCfg.shift  = 7u;

    appObj->cmpDecmpCfg.compandCfg.enable = TRUE;
    appObj->cmpDecmpCfg.compandCfg.size   = 11u;
    appObj->cmpDecmpCfg.compandCfg.useLut = 1u;
    appObj->cmpDecmpCfg.compandCfg.xthr1  = 65535u;
    appObj->cmpDecmpCfg.compandCfg.xthr2  = 1048575u;
    appObj->cmpDecmpCfg.compandCfg.xthr3  = 1048575u;
    appObj->cmpDecmpCfg.compandCfg.ythr1  = 65535u;
    appObj->cmpDecmpCfg.compandCfg.ythr2  = 65535u;
    appObj->cmpDecmpCfg.compandCfg.ythr3  = 65535u;
    appObj->cmpDecmpCfg.compandCfg.slope1 = 256u;
    appObj->cmpDecmpCfg.compandCfg.slope2 = 0u;
    appObj->cmpDecmpCfg.compandCfg.slope3 = 0u;
    appObj->cmpDecmpCfg.compandCfg.slope4 = 0u;
    appObj->cmpDecmpCfg.compandCfg.shift  = 8u;

    appObj->ipipeifCtrl.module =
        VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
    appObj->ipipeifCtrl.pCompDecompCfg = &appObj->cmpDecmpCfg;

    /* Set the Comp/Decomp Configuration in ipipeif */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Comp/Decomp Config Failed\r\n");

        return -1;
    }

    BspUtils_memset(&appObj->wdrCfg, 0x0, sizeof (appObj->wdrCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG;
    appObj->ipipeifCtrl.pWdrCfg = &appObj->wdrCfg;

    /* Get the WDR Default Configuration */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPEIF_IOCTL_GET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Get WDR Config Failed\r\n");

        return -1;
    }

    appObj->wdrCfg.lwb[0U] = 0x200;
    appObj->wdrCfg.lwb[1U] = 0x200;
    appObj->wdrCfg.lwb[2U] = 0x200;
    appObj->wdrCfg.lwb[3U] = 0x200;
    appObj->wdrCfg.swb[0U] = 0x200;
    appObj->wdrCfg.swb[1U] = 0x200;
    appObj->wdrCfg.swb[2U] = 0x200;
    appObj->wdrCfg.swb[3U] = 0x200;

    appObj->wdrCfg.enable     = TRUE;
    appObj->wdrCfg.wdrDir     = FALSE;
    appObj->wdrCfg.dst        = 15u;
    appObj->wdrCfg.sbit       = 8u;
    appObj->wdrCfg.lbit       = 8u;
    appObj->wdrCfg.wgt_sel    = 1u;
    appObj->wdrCfg.afe        = 0x0u;
    appObj->wdrCfg.afm        = 0x0u;
    appObj->wdrCfg.bf         = 0x0u;
    appObj->wdrCfg.gshort     = 32768u;
    appObj->wdrCfg.glong      = 128u;
    appObj->wdrCfg.thr        = 255;
    appObj->wdrCfg.lbk00      = 0u;
    appObj->wdrCfg.lbk01      = 0u;
    appObj->wdrCfg.lbk10      = 0u;
    appObj->wdrCfg.lbk11      = 0u;
    appObj->wdrCfg.sbk00      = 0u;
    appObj->wdrCfg.sbk01      = 0u;
    appObj->wdrCfg.sbk10      = 0u;
    appObj->wdrCfg.sbk11      = 0u;
    appObj->wdrCfg.mas        = 0x0u;
    appObj->wdrCfg.mad        = 65535u;
    appObj->wdrCfg.lwb[0U]    = 512u;
    appObj->wdrCfg.lwb[1U]    = 528u;
    appObj->wdrCfg.lwb[2U]    = 946u;
    appObj->wdrCfg.lwb[3U]    = 512u;
    appObj->wdrCfg.swb[0U]    = 520u;
    appObj->wdrCfg.swb[1U]    = 512u;
    appObj->wdrCfg.swb[2U]    = 1034u;
    appObj->wdrCfg.swb[3U]    = 520u;
    appObj->wdrCfg.mergeShift = 4u;
    appObj->wdrCfg.mergeClip  = 0xFFFFFu;

    /* Set the changed configuration */
    status = Fvid2_control(
        drvHndl,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);
    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set WDR Config Failed\r\n");
        return -1;
    }

    return (FVID2_SOK);
}

Int32 AppSetSatCfg(vpsAppObject_t *appObj, UInt32 isPass2)
{
    Int32 status = FVID2_SOK;

    BspUtils_memset(&appObj->satCfg, 0x0, sizeof (appObj->satCfg));
    BspUtils_memset(&appObj->ipipeifCtrl, 0x0, sizeof (appObj->ipipeifCtrl));

    appObj->ipipeifCtrl.module  = VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG;
    appObj->ipipeifCtrl.pSatCfg = &appObj->satCfg;

    if (TRUE == isPass2)
    {
        appObj->satCfg.vportSatCfg.enable = TRUE;
        appObj->satCfg.vportSatCfg.sat    = 4095u;
        appObj->satCfg.vportSatCfg.dcClmp = 0u;
        appObj->satCfg.vportSatCfg.dsf    = 0u;
    }
    else
    {
        appObj->satCfg.vportSatCfg.enable = TRUE;
        appObj->satCfg.vportSatCfg.sat    = 1048575u;
        appObj->satCfg.vportSatCfg.dcClmp = 0u;
        appObj->satCfg.vportSatCfg.dsf    = 8u;
    }
    appObj->satCfg.memifSatCfg.enable = FALSE;
    appObj->satCfg.memifSatCfg.sat    = 4095u;
    appObj->satCfg.memifSatCfg.dcClmp = 0u;
    appObj->satCfg.memifSatCfg.dsf    = 4u;

    appObj->satCfg.isifSatCfg.enable = FALSE;
    appObj->satCfg.isifSatCfg.sat    = 4095u;
    appObj->satCfg.isifSatCfg.dcClmp = 0u;
    appObj->satCfg.isifSatCfg.dsf    = 0u;

    /* Set the changed configuration */
    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
        &appObj->ipipeifCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: IPIPEIF Set Saturation Config Failed\r\n");
        return -1;
    }

    return (status);
}

static Int32 AppSetIpipeConfig(vpsAppObject_t *appObj)
{
    Int32  status = FVID2_SOK;
    UInt32 cnt;

    if (TRUE == gAppObj.enableDpc)
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

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->dpcOtfCfg.enableOtfDpc = TRUE;
        appObj->dpcOtfCfg.method       = VPS_ISS_IPIPE_DPC_OTF_METHOD_1;;
        appObj->dpcOtfCfg.dThr         = 0x0u;
        appObj->dpcOtfCfg.grThr        = 0x1u;
        appObj->dpcOtfCfg.gbThr        = 0x0u;
        appObj->dpcOtfCfg.bThr         = 800u;
        appObj->dpcOtfCfg.rCor         = 0x0u;
        appObj->dpcOtfCfg.grCor        = 0x1u;
        appObj->dpcOtfCfg.gbCor        = 0x0u;
        appObj->dpcOtfCfg.bCor         = 1023u;
        appObj->dpcOtfCfg.shiftValue   = 0x2u;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gAppObj.enableGamma)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->gammaCfg,
                        0x0,
                        sizeof (appObj->gammaCfg));

        appObj->ipipeCtrl.module   = VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION;
        appObj->ipipeCtrl.gammaCfg = &appObj->gammaCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->lutFmtCnvt.moduleId    = VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION;
        appObj->lutFmtCnvt.gammaLutIn  = gamma_lut;
        appObj->lutFmtCnvt.gammaLutOut = gamma_lut;
        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
            &appObj->lutFmtCnvt,
            NULL);
        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Could not convert 3D Lut format\r\n");

            return -1;
        }

        appObj->gammaCfg.enableRed   = TRUE;
        appObj->gammaCfg.enableGreen = TRUE;
        appObj->gammaCfg.enableBlue  = TRUE;
        appObj->gammaCfg.lutRed      = gamma_lut;
        appObj->gammaCfg.lutGreen    = gamma_lut;
        appObj->gammaCfg.lutBlue     = gamma_lut;
        appObj->gammaCfg.tbl         = VPS_ISS_IPIPE_GAMMA_TBL_RAM;
        appObj->gammaCfg.tblSize     = VPS_ISS_IPIPE_GAMMA_TBL_SIZE_512;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gAppObj.enable3dLut)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->lut3d,
                        0x0,
                        sizeof (appObj->lut3d));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_3D_LUT;
        appObj->ipipeCtrl.colorConvert3DLutCfg = &appObj->lut3d;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        /* Convert Lut to IP expected format */
        appObj->lutFmtCnvt.moduleId    = VPS_ISS_IPIPE_MODULE_3D_LUT;
        appObj->lutFmtCnvt.lut3DRed    = lut3d_red;
        appObj->lutFmtCnvt.lut3DBlue   = lut3d_blue;
        appObj->lutFmtCnvt.lut3DGreen  = lut3d_green;
        appObj->lutFmtCnvt.out3DB0Addr = lutBankAddr[0U];
        appObj->lutFmtCnvt.out3DB1Addr = lutBankAddr[1U];
        appObj->lutFmtCnvt.out3DB2Addr = lutBankAddr[2U];
        appObj->lutFmtCnvt.out3DB3Addr = lutBankAddr[3U];
        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
            &appObj->lutFmtCnvt,
            NULL);
        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Could not convert 3D Lut format\r\n");

            return -1;
        }

        appObj->lut3d.enable = TRUE;
        appObj->lut3d.b0Addr = lutBankAddr[0U];
        appObj->lut3d.b1Addr = lutBankAddr[1U];
        appObj->lut3d.b2Addr = lutBankAddr[2U];
        appObj->lut3d.b3Addr = lutBankAddr[3U];

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gAppObj.enableYee)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->eeCfg,
                        0x0,
                        sizeof (appObj->eeCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER;
        appObj->ipipeCtrl.eeCfg  = &appObj->eeCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->lutFmtCnvt.moduleId  = VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER;
        appObj->lutFmtCnvt.yeeLutIn  = yee_table;
        appObj->lutFmtCnvt.yeeLutOut = yee_table;
        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
            &appObj->lutFmtCnvt,
            NULL);
        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Could not convert YEE format\r\n");

            return -1;
        }

        appObj->eeCfg.enable = TRUE;
        appObj->eeCfg.method = VPS_ISS_IPIPE_EE_MERGE_METHOD_SUM;
        appObj->eeCfg.enableHaloReduction = FALSE;
        appObj->eeCfg.hpfDs           = 4u;
        appObj->eeCfg.hpfMulCoeff[0u] = 0x30U;
        appObj->eeCfg.hpfMulCoeff[1u] = 0x2U;
        appObj->eeCfg.hpfMulCoeff[2u] = 0xFFFFFFFBU;
        appObj->eeCfg.hpfMulCoeff[3u] = 0x2U;
        appObj->eeCfg.hpfMulCoeff[4u] = 0xFFFFFFFEU;
        appObj->eeCfg.hpfMulCoeff[5u] = 0xFFFFFFFDU;
        appObj->eeCfg.hpfMulCoeff[6u] = 0xFFFFFFFBU;
        appObj->eeCfg.hpfMulCoeff[7u] = 0xFFFFFFFDU;
        appObj->eeCfg.hpfMulCoeff[8u] = 0xFFFFFFFFU;
        appObj->eeCfg.hpfThreshold    = 0x0u;

        appObj->eeCfg.gain = 0x0u;
        appObj->eeCfg.hpfThresholdLow  = 0x0u;
        appObj->eeCfg.hpfThresholdHigh = 0x0u;
        appObj->eeCfg.gradientGain     = 0x0u;
        appObj->eeCfg.gradientOffset   = 0x0u;
        appObj->eeCfg.lutAddr          = yee_table;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

            return -1;
        }
        else
        {
            status = Fvid2_control(
                appObj->p2Cfg.drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &appObj->ipipeCtrl,
                NULL);
            if (FVID2_SOK != status)
            {
                BspOsal_printf("ISSM2MWdrApp: IPIPE SetConfig Failed\r\n");

                return -1;
            }
        }
    }

    if (TRUE == gAppObj.enableGic)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->gicCfg,
                        0x0,
                        sizeof (appObj->gicCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_GIC;
        appObj->ipipeCtrl.gicCfg = &appObj->gicCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->gicCfg.enable        = TRUE;
        appObj->gicCfg.type          = VPS_ISS_IPIPE_GIC_ALG_TYPE_AVERAGE;
        appObj->gicCfg.enableLscGain = FALSE;

        appObj->gicCfg.thrSel    = VPS_ISS_IPIPE_GIC_THR_SEL_GIC_REG;
        appObj->gicCfg.gain      = 64u;
        appObj->gicCfg.slope     = 64u;
        appObj->gicCfg.threshold = 32u;
        appObj->gicCfg.nfGain    = 0u;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gAppObj.enableLsc)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->lscCfg,
                        0x0,
                        sizeof (appObj->lscCfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_LSC;
        appObj->ipipeCtrl.lscCfg = &appObj->lscCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->lscCfg.vertOffset   = 0x0U;
        appObj->lscCfg.horzLinCoeff = 0xFFFFF175U;
        appObj->lscCfg.horzQdrCoeff = 2293U;
        appObj->lscCfg.horzLinShift = 13U;
        appObj->lscCfg.horzQdrShift = 10U;
        appObj->lscCfg.vertLinCoeff = 0xFFFFF572U;
        appObj->lscCfg.vertQdrCoeff = 2376U;
        appObj->lscCfg.vertLinShift = 13U;
        appObj->lscCfg.vertQdrShift = 10U;
        appObj->lscCfg.horzOffset   = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_R]    = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_GR]   = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_GB]   = 0x0U;
        appObj->lscCfg.gain[FVID2_BAYER_COLOR_COMP_B]    = 0x0U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_R]  = 64U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_GR] = 0U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_GB] = 0U;
        appObj->lscCfg.offset[FVID2_BAYER_COLOR_COMP_B]  = 64U;
        appObj->lscCfg.shift = 9U;
        appObj->lscCfg.max   = 511U;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gAppObj.enableNf1)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->nf1Cfg,
                        0x0,
                        sizeof (appObj->nf1Cfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_NF1;
        appObj->ipipeCtrl.nf1Cfg = &appObj->nf1Cfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->nf1Cfg.enable        = FALSE;;
        appObj->nf1Cfg.grPixType     = VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX;
        appObj->nf1Cfg.enableLscGain = FALSE;
        appObj->nf1Cfg.useLutSpr     = FALSE;
        appObj->nf1Cfg.downShift     = 2U;
        appObj->nf1Cfg.spreadVal     = 3U;
        appObj->nf1Cfg.threshold[0U] = 11U;
        appObj->nf1Cfg.threshold[1U] = 16U;
        appObj->nf1Cfg.threshold[2U] = 21U;
        appObj->nf1Cfg.threshold[3U] = 27U;
        appObj->nf1Cfg.threshold[4U] = 32U;
        appObj->nf1Cfg.threshold[5U] = 37U;
        appObj->nf1Cfg.threshold[6U] = 42U;
        appObj->nf1Cfg.threshold[7U] = 47U;

        for (cnt = 0U; cnt < VPS_ISS_IPIPE_NF2_MAX_THR; cnt++)
        {
            appObj->nf1Cfg.intensity[cnt] = 31U;
            appObj->nf1Cfg.sprFactor[cnt] = 3U;
        }

        appObj->nf1Cfg.edgeMin = 0x0U;
        appObj->nf1Cfg.edgeMax = 0x0U;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }

    if (TRUE == gAppObj.enableNf2)
    {
        /* Initialize the configuration to zero */
        BspUtils_memset(&appObj->ipipeCtrl,
                        0x0,
                        sizeof (appObj->ipipeCtrl));
        BspUtils_memset(&appObj->nf2Cfg,
                        0x0,
                        sizeof (appObj->nf2Cfg));

        appObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_NF2;
        appObj->ipipeCtrl.nf2Cfg = &appObj->nf2Cfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_GET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }

        appObj->nf2Cfg.enable        = FALSE;;
        appObj->nf2Cfg.grPixType     = VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX;
        appObj->nf2Cfg.enableLscGain = FALSE;
        appObj->nf2Cfg.useLutSpr     = FALSE;
        appObj->nf2Cfg.downShift     = 2U;
        appObj->nf2Cfg.spreadVal     = 3U;
        appObj->nf2Cfg.threshold[0U] = 26U;
        appObj->nf2Cfg.threshold[1U] = 38U;
        appObj->nf2Cfg.threshold[2U] = 50U;
        appObj->nf2Cfg.threshold[3U] = 62U;
        appObj->nf2Cfg.threshold[4U] = 74U;
        appObj->nf2Cfg.threshold[5U] = 86U;
        appObj->nf2Cfg.threshold[6U] = 98U;
        appObj->nf2Cfg.threshold[7U] = 110U;

        for (cnt = 0U; cnt < VPS_ISS_IPIPE_NF2_MAX_THR; cnt++)
        {
            appObj->nf2Cfg.intensity[cnt] = 31U;
            appObj->nf2Cfg.sprFactor[cnt] = 3U;
        }

        appObj->nf2Cfg.edgeMin = 0x0U;
        appObj->nf2Cfg.edgeMax = 0x0U;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
            &appObj->ipipeCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: IPIPE GetConfig Failed\r\n");

            return -1;
        }
    }
    return (status);
}

static Int32 AppSetNsf3vConfig(vpsAppObject_t *appObj)
{
    Int32 status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->nsf3vCfg,
                    0x0,
                    sizeof (vpsissNsf3Config_t));

    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_NSF3_IOCTL_GET_CONFIG,
        &appObj->nsf3vCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: NSF3v GetConfig Failed\r\n");

        return -1;
    }

    appObj->nsf3vCfg.bypass = FALSE;
    appObj->nsf3vCfg.enableBorderReplicate = TRUE;

    status = Fvid2_control(
        appObj->p1Cfg.drvHandle,
        VPS_ISS_NSF3_IOCTL_SET_CONFIG,
        &appObj->nsf3vCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: NSF3v GetConfig Failed\r\n");

        return -1;
    }

    return (status);
}

static Int32 AppSetGlbceConfig(vpsAppObject_t *appObj)
{
    Int32 status = FVID2_SOK;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->glbceCtrl,
                    0x0,
                    sizeof (vpsissGlbceCtrl_t));
    BspUtils_memset(&appObj->glbceCfg,
                    0x0,
                    sizeof (vpsissGlbceConfig_t));

    appObj->glbceCtrl.module   = VPS_ISS_GLBCE_MODULE_GLBCE;
    appObj->glbceCtrl.glbceCfg = &appObj->glbceCfg;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    appObj->glbceCfg.enable = TRUE;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

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
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    appObj->glbcePerceptCfg.enable = FALSE;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

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
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_GET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    appObj->glbcePerceptCfg.enable = FALSE;

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
        &appObj->glbceCtrl,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: GLBCE GetConfig Failed\r\n");

        return -1;
    }

    return (status);
}

static Int32 AppSetCnfConfig(vpsAppObject_t *appObj)
{
    Int32 status = FVID2_SOK;
    vpsissNsf3Config_t *nsf3Cfg;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->cnfCfg,
                    0x0,
                    sizeof (vpsissCnfConfig_t));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_CNF_IOCTL_GET_CONFIG,
        &appObj->cnfCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: CNF GetConfig Failed\r\n");

        return -1;
    }

    nsf3Cfg = &appObj->cnfCfg.nsf3Cfg;
    appObj->cnfCfg.enable    = TRUE;
    appObj->cnfCfg.enableCds = FALSE;
    BspUtils_memcpy(
        nsf3Cfg,
        &gIssHalNsf3DefCfg_Cnf,
        sizeof (vpsissNsf3Config_t));

    status = Fvid2_control(
        appObj->p2Cfg.drvHandle,
        VPS_ISS_CNF_IOCTL_SET_CONFIG,
        &appObj->cnfCfg,
        NULL);

    if (FVID2_SOK != status)
    {
        BspOsal_printf("ISSM2MWdrApp: CNF GetConfig Failed\r\n");

        return -1;
    }

    return (status);
}

Int32 AppSetRszConfig(vpsAppObject_t *appObj, UInt32 isPass2)
{
    Int32 status;

    /* Initialize the configuration to zero */
    BspUtils_memset(&appObj->rszCfg,
                    0x0,
                    sizeof (vpsissRszCfg_t));
    BspUtils_memset(&appObj->rszCtrl, 0x0, sizeof (vpsissRszCtrl_t));

    if (FALSE == isPass2)
    {
        appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
        appObj->rszCtrl.rszCfg = &appObj->rszCfg;

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_GET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Resizer GetConfig Failed\r\n");

            return -1;
        }

        appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_BYPASS;
        appObj->rszCfg.inCfg.procWin.cropStartX = 0u;
        appObj->rszCfg.inCfg.procWin.cropStartY = 0u;
        appObj->rszCfg.inCfg.procWin.cropWidth  = IN_WIDTH;
        appObj->rszCfg.inCfg.procWin.cropHeight = IN_HEIGHT;

        appObj->rszCfg.instCfg[0U].enable = 1U;
        appObj->rszCfg.instCfg[0U].outFmt.dataFormat = PASS1_OUT_FORMAT;
        appObj->rszCfg.instCfg[0U].outFmt.width      = PASS1_OUT_WIDTH;
        appObj->rszCfg.instCfg[0U].outFmt.height     = PASS1_OUT_HEIGHT;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[0U]  = PASS1_OUT_PITCH;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[1U]  = PASS1_OUT_PITCH;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[2U]  = PASS1_OUT_PITCH;

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

        status = Fvid2_control(
            appObj->p1Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_SET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: RSZ SetConfig Failed\r\n");
            return -1;
        }
    }
    else
    {
        appObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
        appObj->rszCtrl.rszCfg = &appObj->rszCfg;

        status = Fvid2_control(
            appObj->p2Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_GET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: Resizer GetConfig Failed\r\n");

            return -1;
        }

        appObj->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
        appObj->rszCfg.inCfg.procWin.cropStartX = 0u;
        appObj->rszCfg.inCfg.procWin.cropStartY = 0u;
        appObj->rszCfg.inCfg.procWin.cropWidth  = IN_WIDTH;
        appObj->rszCfg.inCfg.procWin.cropHeight = IN_HEIGHT;

        appObj->rszCfg.instCfg[0U].outFmt.dataFormat = PASS2_OUT_FORMAT;
        appObj->rszCfg.instCfg[0U].outFmt.width      = PASS2_OUT_WIDTH;
        appObj->rszCfg.instCfg[0U].outFmt.height     = PASS2_OUT_HEIGHT;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[0U]  = PASS2_OUT_PITCH;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[1U]  = PASS2_OUT_PITCH;
        appObj->rszCfg.instCfg[0U].outFmt.pitch[2U]  = PASS2_OUT_PITCH;

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

        appObj->rszCfg.instCfg[0u].intensityCfg.horzLumaIntensity   = 21u;
        appObj->rszCfg.instCfg[0u].intensityCfg.horzChromaIntensity = 22u;
        appObj->rszCfg.instCfg[0u].intensityCfg.vertLumaIntensity   = 14u;
        appObj->rszCfg.instCfg[0u].intensityCfg.vertChromaIntensity = 15u;

        status = Fvid2_control(
            appObj->p2Cfg.drvHandle,
            VPS_ISS_RSZ_IOCTL_SET_CONFIG,
            &appObj->rszCtrl,
            NULL);

        if (FVID2_SOK != status)
        {
            BspOsal_printf("ISSM2MWdrApp: RSZ SetConfig Failed\r\n");
            return -1;
        }
    }

    return (FVID2_SOK);
}

