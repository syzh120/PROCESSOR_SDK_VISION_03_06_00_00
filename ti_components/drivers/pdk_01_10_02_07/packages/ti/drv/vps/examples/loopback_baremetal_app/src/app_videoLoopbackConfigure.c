/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
 *
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
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/csl/soc.h>

#include <ti/drv/vps/include/vip/vps_vipDrv.h>

#include <app_videoLoopbackConfigure.h>
#include <app_frameBufMgmt.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>

extern Int32                gTestStatus;

static Int32 DispApp_configureVideoPllAndClkSrc(UInt32 pixelClk);

/* Important parameters are marked "Important" in comments */
/* Parameters are marked "Ignore" - default values are already set */

/* Required for VpsDrv_captOpen */
const VpsCore_OpenPrms      captureOpenParams_s0PortA =
{
    (void *) BUF_ARRAY_IDX_PORTA,
    (VpsCore_ReqFrameCb) App_queBufs,
    (VpsCore_FrameDoneCb) App_deQueBufs
};

/* Required for VpsDrv_captOpen */
const VpsCore_OpenPrms      captureOpenParams_s0PortB =
{
    (void *) BUF_ARRAY_IDX_PORTB,
    (VpsCore_ReqFrameCb) App_queBufs,
    (VpsCore_FrameDoneCb) App_deQueBufs
};

/* Required for VpsDrv_captOpen */
const VpsCore_OpenPrms      captureOpenParams_s1PortA =
{
    (void *) BUF_ARRAY_IDX_PORTA,
    (VpsCore_ReqFrameCb) App_queBufs,
    (VpsCore_FrameDoneCb) App_deQueBufs
};

/* Required for VpsDrv_captOpen */
const VpsCore_OpenPrms      captureOpenParams_s1PortB =
{
    (void *) BUF_ARRAY_IDX_PORTB,
    (VpsCore_ReqFrameCb) App_queBufs,
    (VpsCore_FrameDoneCb) App_deQueBufs
};

/* Required for VpsDrv_captOpen */
const VpsCore_VipOpenParams gVipOpenParams_s0portA =
{
    S0_PORTA_08,         /*    src                */
    1,                   /*    numChannels        */
    0                    /*    muxModeStartChId   */
};

/* Required for VpsDrv_captOpen */
const VpsCore_VipOpenParams gVipOpenParams_s0portB =
{
    S0_PORTB_08,         /*    src                */
    1,                   /*    numChannels        */
    0                    /*    muxModeStartChId   */
};

/* Required for VpsDrv_captOpen */
const VpsCore_VipOpenParams gVipOpenParams_s1portA =
{
    S1_PORTA_08,         /*    src                */
    1,                   /*    numChannels        */
    0                    /*    muxModeStartChId   */
};

/* Required for VpsDrv_captOpen */
const VpsCore_VipOpenParams gVipOpenParams_s1portB =
{
    S1_PORTB_08,         /*    src                */
    1,                   /*    numChannels        */
    0                    /*    muxModeStartChId   */
};

/* Required for VpsDrv_captSetParams */
VpsCore_VipParams           gVipPortAParams_template =
{
    FVID2_DF_YUV422P,
    /* srcWidth - Ignore - required only if scaler is used */
    1280,
    /* srcHeight - Ignore - required only if scaler is used */
    720,
    /* numStreams - Ignore */
    1,
    /* dstColorSpace[] - only first entry valid for use-case since
     * numStreams == 1
     */
    {
        FVID2_DF_YUV422I_YUYV,
        0,
        0,
        0
    },
#if defined (SOC_TDA2XX) || defined (SOC_TDA2EX)
    {
        720,
        0,
        0,
        0
    },
    /* tarWidth - Ignore
     * required only if scaler is used
     */
    {
        480,
        0,
        0,
        0
    },
    /* tarHeight - Ignore
     * required only if scaler is used
     */
    {
        /*
         * pitch[][] - only (0,0) entry valid since (numStreams == 1) and
         * single plane (Luma/Chroma interleaved) output.
         */
        {
            1440,
            0,
            0
        },
        /*pitch*/
        {
            0,
            0,
            0
        },
        {
            0,
            0,
            0
        },
        {
            0,
            0,
            0
        }
#elif defined (SOC_TDA3XX) || defined (SOC_TDA2PX)
    {
        1280,
        0,
        0,
        0
    },
    /* tarWidth - Ignore
     * required only if scaler is used
     */
    {
        720,
        0,
        0,
        0
    },
    /* tarHeight - Ignore
     * required only if scaler is used
     */
    {
        /*
         * pitch[][] - only (0,0) entry valid since (numStreams == 1) and
         * single plane (Luma/Chroma interleaved) output.
         */
        {
            2560,
            0,
            0
        },
        /*pitch*/
        {
            0,
            0,
            0
        },
        {
            0,
            0,
            0
        },
        {
            0,
            0,
            0
        }
#endif
    },
    /*scActive - Ignore - required only if scaler is used  */
    {
        1,
        0,
        0,
        0
    },
    /*edgeInfoList - Ignore */
    {
        0,
        NULL
    },
    /*portCfg - Important - set in App_configureVIP() */
    {0},
    /*inCropCfg - Ignore - required only if scaler is used  */
    {
        0,
        0,
        1280,
        720
    },
    /*scCfg - Ignore - required only if scaler is used  */
    {
        0,
        0,
        0,
        1,
        1
    },
    /*cscCfg - Ignore - required only if CSC is used  */
    {0},

    {
        /* subFrmPrms - Important - set in App_configureVIP() */
        {0,                   0 },
        {0,                   0 },
        {0,                   0 },
        {0,                   0 }
    },
    /*
     * *maxOutWidth[][]
     * Important: only (0,0) entry valid, since (numStreams == 1) and
     * single plane (Luma/Chroma interleaved output)
     * Set in App_configureVIP()
     */
    {
        {0,                   0 },
        {0,                   0 },
        {0,                   0 },
        {0,                   0 }
    },
    /*
     * *maxOutWidth[][]
     * Important: only (0,0) entry valid, since (numStreams == 1) and
     * single plane (Luma/Chroma interleaved output)
     * Set in App_configureVIP()
     */
    {
        {0,                   0 },
        {0,                   0 },
        {0,                   0 },
        {0,                   0 }
    },
    /*
     * memType
     * Ignore. Required if Tiler is used
     */
    {
        0,
        0,
        0,
        0
    },
};

/* Required for VpsDrv_captSetParams */
VpsCore_VipParams           gVipPortBParams_template =
{
    FVID2_DF_YUV422P,
    /* srcWidth - Ignore - required only if scaler is used */
    1280,
    /* srcHeight - Ignore - required only if scaler is used */
    720,
    /* numStreams - Ignore */
    1,
    /* dstColorSpace[] - only first entry valid for use-case since
     * numStreams == 1
     */
    {
        FVID2_DF_YUV422I_YUYV,
        0,
        0,
        0
    },
    {
        720,
        0,
        0,
        0
    },
    /* tarWidth - Ignore
     * required only if scaler is used
     */
    {
        480,
        0,
        0,
        0
    },
    /* tarHeight - Ignore
     * required only if scaler is used
     */
    {
        /*
         * pitch[][] - only (0,0) entry valid since (numStreams == 1) and
         * single plane (Luma/Chroma interleaved) output.
         */
        {
            1440,
            0,
            0
        },
        /*pitch*/
        {
            0,
            0,
            0
        },
        {
            0,
            0,
            0
        },
        {
            0,
            0,
            0
        }
    },
    /*scActive - Ignore - required only if scaler is used  */
    {
        0,
        0,
        0,
        0
    },
    /*edgeInfoList - Ignore */
    {
        0,
        NULL
    },
    /*portCfg - Important - set in App_configureVIP() */
    {0},
    /*inCropCfg - Ignore - required only if scaler is used  */
    {
        0,
        0,
        1280,
        720
    },
    /*scCfg - Ignore - required only if scaler is used  */
    {
        1,
        0,
        0,
        1,
        1
    },
    /*cscCfg - Ignore - required only if CSC is used  */
    {0},

    {
        /* subFrmPrms - Important - set in App_configureVIP() */
        {0,                   0 },
        {0,                   0 },
        {0,                   0 },
        {0,                   0 }
    },
    /*
     * *maxOutWidth[][]
     * Important: only (0,0) entry valid, since (numStreams == 1) and
     * single plane (Luma/Chroma interleaved output)
     * Set in App_configureVIP()
     */
    {
        {0,                   0 },
        {0,                   0 },
        {0,                   0 },
        {0,                   0 }
    },
    /*
     * *maxOutWidth[][]
     * Important: only (0,0) entry valid, since (numStreams == 1) and
     * single plane (Luma/Chroma interleaved output)
     * Set in App_configureVIP()
     */
    {
        {0,                   0 },
        {0,                   0 },
        {0,                   0 },
        {0,                   0 }
    },
    /*
     * memType
     * Ignore. Required if Tiler is used
     */
    {
        0,
        0,
        0,
        0
    },
};

/* Required for VpsDrv_captSetParams */
Vps_VipPortConfig           vipPortConfig =
{
    VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV,  /* syncType
                                        * For embedded sync, change to
                                        * VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV
                                        * Important
                                        */
    FALSE,                             /* actCropEnable */
    FALSE,                             /* ancCropEnable */
    {
        /* Vps_VipPortIntfCfg intfCfg - Important */
        FALSE,            /* clipActive */
        FALSE,            /* clipBlank  */
        FVID2_VIFW_8BIT
    },
    {
        /* Vps_VipPortEmbCfg embCfg - Ignore */
        FALSE,                                     /* errCorrEnable */
        VPS_VIP_SRC_NUM_POS_LS_NIBBLE_OF_CODEWORD, /* srcNumPos     */
    },
    {
        /* Vps_VipPortDisCfg disCfg - Important */
        0,                                  /* fidSkewPostCnt    */
        0,                                  /* fidSkewPreCnt     */
        VPS_VIP_LINE_CAPTURE_STYLE_HSYNC,   /* lineCaptureStyle -
                                             * other option is
                                             * VPS_VIP_LINE_CAPTURE_STYLE_HSYNC
                                             */
        VPS_VIP_FID_DETECT_MODE_PIN,        /* fidDetectMode     */
        FVID2_POL_HIGH,                     /* actvidPol         */
        FVID2_POL_HIGH,                     /* vsyncPol          */
        FVID2_POL_HIGH,                     /* hsyncPol          */
        TRUE,                               /* discreteBasicMode */
    },
    {
        /* Vps_VipPortComCfg comCfg */
        VPS_VIP_CTRL_CHAN_SEL_7_0,       /* ctrlChanSel - Ignore      */
        VPS_VIP_ANC_CH_SEL_8B_LUMA_SIDE, /* ancChSel8b  - Ignore      */
        FVID2_EDGE_POL_RISING,           /* pixClkEdgePol - Important */
        FALSE,                           /* invertFidPol  - Important */
        FALSE,                           /* enablePort- enabled later */
        FALSE,                           /* clrAsyncFifoRd  - Ignore  */
        FALSE,                           /* clrAsyncFifoWr  - Ignore  */
        0,                               /* expectedNumLines - Ignore */
        0,                               /* expectedNumPix   - Ignore */
        VPS_VIP_REPACK_DONT_CARE,        /* repackerMode     - Ignore */
    },
    {
        /* Vps_VipPortCropCfg actCropCfg - Ignore for now since no cropping */
        0,    /* srcNum     */
        0,    /* cropStartX */
        0,    /* cropStartY */
        0,    /* cropWidth  */
        0,    /* cropHeight */
    },
    {
        /* Vps_VipPortCropCfg ancCropCfg - Ignore */
        0, /* srcNum     */
        0, /* cropStartX */
        0, /* cropStartY */
        0, /* cropWidth  */
        0, /* cropHeight */
    }
};

/**
 * Open Capture Handle
 */
VpsDrv_CaptInstObj *App_coreOpen(UInt32 vipInstId,
                                 UInt32 sliceId,
                                 UInt32 portId)
{
    VpsDrv_CaptInstObj *pObj = NULL;

    if ((VPSHAL_VIP_S0 == sliceId) && (VPSHAL_VIP_PORT_A == portId))
    {
        pObj = VpsDrv_captOpen(vipInstId,
                               &captureOpenParams_s0PortA,
                               &gVipOpenParams_s0portA);
    }
    else if ((VPSHAL_VIP_S0 == sliceId) && (VPSHAL_VIP_PORT_B == portId))
    {
        pObj = VpsDrv_captOpen(vipInstId,
                               &captureOpenParams_s0PortB,
                               &gVipOpenParams_s0portB);
    }
    else if ((VPSHAL_VIP_S1 == sliceId) && (VPSHAL_VIP_PORT_A == portId))
    {
        pObj = VpsDrv_captOpen(vipInstId,
                               &captureOpenParams_s1PortA,
                               &gVipOpenParams_s1portA);
    }
    else if ((VPSHAL_VIP_S1 == sliceId) && (VPSHAL_VIP_PORT_B == portId))
    {
        pObj = VpsDrv_captOpen(vipInstId,
                               &captureOpenParams_s1PortB,
                               &gVipOpenParams_s1portB);
    }
    else
    {
        /*
         * Do nothing;
         */
    }
    return pObj;
}

Int32 App_coreClose(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_captClose(pObj);
}

Int32 App_coreStart(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_captStart(pObj);
}

Int32 App_coreStop(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_captStop(pObj);
}

extern volatile int gNLinIntCount_sxportA;
Int32 App_SubFrmCbFxn_portA(VpsDrv_CaptInstObj  *pObj,
                            const VpsCore_Frame *subFrame)
{
    gNLinIntCount_sxportA++;
    return BSP_SOK;
}

extern volatile int gNLinIntCount_sxportB;
Int32 App_SubFrmCbFxn_portB(VpsDrv_CaptInstObj  *pObj,
                            const VpsCore_Frame *subFrame)
{
    gNLinIntCount_sxportB++;
    return BSP_SOK;
}

Int32 App_configureVIP(VpsDrv_CaptInstObj *pObj,
                       UInt32              sliceId,
                       UInt32              portId)
{
    VpsDrv_VipParams   drvVipPrms;
    VpsCore_VipParams *pathCfg;

    if (VPSHAL_VIP_PORT_A == portId)
    {
        pathCfg = &gVipPortAParams_template;
    }
    else
    {
        pathCfg = &gVipPortBParams_template;
    }

    memcpy(&pathCfg->portCfg,
           &vipPortConfig,
           sizeof (Vps_VipPortConfig));

    drvVipPrms.pathCfg = pathCfg;

    /*Generate sub-frame interrupts*/
    pathCfg->subFrmPrms[0].subFrameEnable = TRUE;
    /*Size of each sub-frame - no. of interrupts per frame will be
     * Number of lines/Size of sub-frame.
     * If number of lines is exact multiple, last interrupt will not be
     * generated
     */
    pathCfg->subFrmPrms[0].numLinesPerSubFrame = 32;
    pathCfg->subFrmPrms[0].interruptMode       = VPS_INTR_END_OF_NTH_LINE;

    if (((VPSHAL_VIP_S0 == sliceId) && (VPSHAL_VIP_PORT_A == portId)) ||
        ((VPSHAL_VIP_S1 == sliceId) && (VPSHAL_VIP_PORT_A == portId)))
    {
        drvVipPrms.subFrameCb[0] = (VpsDrv_SubFrameCb) App_SubFrmCbFxn_portA;
    }
    else if (((VPSHAL_VIP_S0 == sliceId) && (VPSHAL_VIP_PORT_B == portId)) ||
             ((VPSHAL_VIP_S1 == sliceId) && (VPSHAL_VIP_PORT_B == portId)))
    {
        drvVipPrms.subFrameCb[0] = (VpsDrv_SubFrameCb) App_SubFrmCbFxn_portB;
    }

    /*
     * VPDMA supports max-width/max-height setting based on pixels.
     * In raw mode, pixel size is assumed to be two bytes.
     * Therefore, 1280 pixel setting will allow raw-data width of
     * (1280*2) bytes to be captured.
     */
    pathCfg->maxOutWidth[0][0]         = VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED;
    pathCfg->maxOutHeight[0][0]        = VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED;
    pathCfg->portCfg.actCropEnable     = 1;
    pathCfg->portCfg.actCropCfg.srcNum = 0;
    pathCfg->portCfg.actCropCfg.cropCfg.cropStartX = 0;
    pathCfg->portCfg.actCropCfg.cropCfg.cropStartY = 0;
    pathCfg->portCfg.actCropCfg.cropCfg.cropWidth  = 1280;
    pathCfg->portCfg.actCropCfg.cropCfg.cropHeight = 720;

    return VpsDrv_captSetParams(pObj, &drvVipPrms);
}

Int32 App_portReset(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_resetPort(pObj);
}

/**
 * Open Dctrl Handle
 */
VpsDrv_DctrlInstObj *App_dctrlcoreOpen(void)
{
    VpsDrv_DctrlInstObj *pObj = NULL;

    pObj = VpsDrv_dctrlOpen();

    return pObj;
}

Int32 App_dctrlcoreClose(VpsDrv_DctrlInstObj *pObj)
{
    return VpsDrv_dctrlClose(pObj);
}

/* Display Handle */

/**
 * Open Capture Handle
 */
VpsDrv_DispInstObj *App_dsscoreOpen(UInt32 dssInstId)
{
    VpsDrv_DispInstObj   *pObj = NULL;
    VpsCore_OpenPrms      openParams;
    VpsCore_DssOpenParams dssOpenParams;

    openParams.reqFrmCb  = (VpsCore_ReqFrameCb) App_DssqueBufs;
    openParams.frmDoneCb = (VpsCore_FrameDoneCb) App_DssdeQueBufs;

    pObj = VpsDrv_dssOpen(dssInstId, &openParams, &dssOpenParams);

    return pObj;
}

Int32 App_dsscoreClose(VpsDrv_DispInstObj *pObj)
{
    return VpsDrv_dssClose(pObj);
}

Int32 App_dsscoreStart(VpsDrv_DispInstObj *pObj)
{
    return VpsDrv_dssStart(pObj);
}

Int32 App_dsscoreStop(VpsDrv_DispInstObj *pObj)
{
    return VpsDrv_dssStop(pObj);
}

Int32 App_configureDctrl(VpsDrv_DctrlInstObj *pObj)
{
    Vps_DctrlConfig             dctrlCfg;
    Vps_DssDispcOvlyPanelConfig panelCfg;
    Vps_DctrlVencDivisorInfo    vencDivisors;
    Int32  retVal, idx = 0;
    UInt32 pixelClock;
    UInt32 blenderNode, dpiOutputNode, vencId;

    blenderNode     = VPS_DCTRL_DSS_LCD1_BLENDER;
    dpiOutputNode   = VPS_DCTRL_DSS_DPI1_OUTPUT;
    vencId          = VPS_DCTRL_DSS_VENC_LCD1;
#if defined (SOC_TDA2EX)
    if (CSL_getSocSiliconPackageType() == CSL_SOC_SILICON_PACKAGE_TYPE_17X17)
    {
        blenderNode     = VPS_DCTRL_DSS_LCD3_BLENDER;
        dpiOutputNode   = VPS_DCTRL_DSS_DPI3_OUTPUT;
        vencId          = VPS_DCTRL_DSS_VENC_LCD3;
    }

#endif

    dctrlCfg.useCase = VPS_DCTRL_USERSETTINGS;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID1_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID2_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID3_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;
#endif

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_GFX1_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;

    dctrlCfg.edgeInfo[idx].startNode = blenderNode;
    dctrlCfg.edgeInfo[idx].endNode   = dpiOutputNode;
    idx++;

    dctrlCfg.numEdges = (UInt32) idx;

    dctrlCfg.vencInfo.numVencs = (UInt32) 1U;
    dctrlCfg.vencInfo.modeInfo[0U].vencId = vencId;

    /* Configure custom timings */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.standard = FVID2_STD_CUSTOM;
#if defined (SOC_TDA2XX)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 800;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 480;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per LCD connected(Three 7 LCD)
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 29232U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 40U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 40U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 48U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 13U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 29U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 3U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif

#if defined (SOC_TDA3XX) || defined (SOC_TDA2EX)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 1280;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 800;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per LCD connected(10 Inch LG)
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 74500U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 80U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 62U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 48U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 12U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 35U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 6U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif
#if defined (SOC_TDA2PX)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 1280;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 720;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per 720P
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 74250U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 72U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 216U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 80U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 3U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 22U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 5U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif

    retVal = vpsDrv_DctrlSetConfig(pObj, &dctrlCfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("DCTRL Set Config Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

    panelCfg.vencId = vencId;
    panelCfg.alphaBlenderEnable = (UInt32) 0;
    panelCfg.backGroundColor    = 0x101010;
    panelCfg.colorKeyEnable     = 1;
    /* Source transparency color key selected */
    panelCfg.colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    panelCfg.deltaLinesPerPanel = (UInt32) 0;
    panelCfg.transColorKey      = 0x00;

    vpsDrv_DctrlSetOvlyParams(pObj, &panelCfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf(": DCTRL Set Config Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

    /* Setting LCD and PCD values to 1 */
    vencDivisors.vencId     = vencId;
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (OMAP5X_BUILD)
    /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
     * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed to
     * output 29.232 * 4 MHz and set PCD as 4. */
    if (29232U == dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock)
    {
        vencDivisors.divisorPCD = 4U;
    }
#endif
    vpsDrv_DctrlSetVencDivisor(pObj, &vencDivisors);
    if (retVal != BSP_SOK)
    {
        Bsp_printf("DCTRL Set Venc Divisors Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

    pixelClock = dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock *
                 vencDivisors.divisorPCD;
    DispApp_configureVideoPllAndClkSrc(pixelClock);

    return retVal;
}

Int32 App_configureDctrlPipe(VpsDrv_DctrlInstObj *pObj)
{
    Vps_DssDispcOvlyPipeConfig ovlpipecfg;
    Int32 retVal = BSP_SOK;

    ovlpipecfg.pipeLine    = VPS_DSS_DISPC_PIPE_VID1;
    ovlpipecfg.globalAlpha = 0xFF;
    /* Z-order is in order GFX - 3, VID3 -2 ,VID2 - 1 and VID1 - 0 */
    ovlpipecfg.zorder = VPS_DSS_DISPC_PIPE_VID1;

    ovlpipecfg.zorderEnable     = 1;
    ovlpipecfg.preMultiplyAlpha = 0;

    retVal = vpsDrv_DctrlSetPipelineParams(pObj, &ovlpipecfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf(": DCTRL Set Config IOCTL Failed!!!\r\n");
    }
    return retVal;
}

Int32 App_dssconfigure(VpsDrv_DispInstObj *pObj)
{
    VpsDrv_DispDssParams  dssPrms;
    Vps_DssDispcVidConfig videoCfg;
    UInt32 dataFormat = FVID2_DF_YUV422I_YUYV;

    dssPrms.inFmt.dataFormat = dataFormat;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2EX)
    dssPrms.inFmt.width  = 720U;
    dssPrms.inFmt.height = 480U;
#elif defined (SOC_TDA3XX) || defined (SOC_TDA2PX)
    dssPrms.inFmt.width  = 1280U;
    dssPrms.inFmt.height = 720U;
#endif
    if (Fvid2_isDataFmtSemiPlanar(dataFormat))
    {
        dssPrms.inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtYuv422I(dataFormat))
    {
        dssPrms.inFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width * 2U, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtRgb16bit(dataFormat))
    {
        dssPrms.inFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width * 2U, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtRgb24bit(dataFormat))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        dssPrms.inFmt.pitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width * 3U,
                           (VPS_BUFFER_ALIGNMENT * 3U));
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtRgb32bit(dataFormat))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        dssPrms.inFmt.pitch[FVID2_RGB_ADDR_IDX] = VpsUtils_align(
            dssPrms.inFmt.width * 4U,
            (
                VPS_BUFFER_ALIGNMENT));;
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    dssPrms.inFmt.chNum           = 0U;
    dssPrms.inFmt.fieldMerged[0U] = FALSE;
    dssPrms.inFmt.fieldMerged[1U] = FALSE;
    dssPrms.inFmt.fieldMerged[2U] = FALSE;
    dssPrms.inFmt.scanFormat      = FVID2_SF_PROGRESSIVE;
    dssPrms.inFmt.bpp      = FVID2_BPP_BITS16;
    dssPrms.inFmt.reserved = NULL;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2EX)
    dssPrms.tarWidth  = 720U;
    dssPrms.tarHeight = 480U;
    dssPrms.posX      = 40U;
    dssPrms.posY      = 0;

#elif defined (SOC_TDA3XX)
    dssPrms.tarWidth  = 1280U;
    dssPrms.tarHeight = 800U;
    dssPrms.posX      = 0U;
    dssPrms.posY      = 0;

#elif defined (SOC_TDA2PX)
    dssPrms.tarWidth  = 1280U;
    dssPrms.tarHeight = 720U;
    dssPrms.posX      = 0U;
    dssPrms.posY      = 0;

#endif

    videoCfg.pipeCfg.repliEnable = FALSE;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    videoCfg.pipeCfg.scEnable = FALSE;
#elif defined (SOC_TDA3XX)
    videoCfg.pipeCfg.scEnable = TRUE;
#endif
    videoCfg.pipeCfg.cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;
    videoCfg.pipeCfg.chromaSampling   = 0U;
    videoCfg.advDmaCfg = NULL;
    videoCfg.vc1Cfg    = NULL;

    dssPrms.vidCfg = &videoCfg;

    return VpsDrv_dssSetParams(pObj, &dssPrms);
}

static Int32 DispApp_configureVideoPllAndClkSrc(UInt32 pixelClk)
{
    Int32  retVal = BSP_EFAIL;
    pmhalPrcmNodeId_t videopllId;
    UInt32 timeDelay = 0xFFFFFFFFU;

#if defined (SOC_TDA3XX)
    videopllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
#else
    videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
#endif
    retVal = PMLIBVideopllSetFreq(videopllId, pixelClk,
                                  PMLIB_VIDEO_PLL_CALC_MAX_MN, timeDelay);
    if (retVal != FVID2_SOK)
    {
        Bsp_printf("Configuring Pll Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (FVID2_SOK == retVal)
    {
        pmlibVideoPllVenc_t vidPllVencId = PMLIB_VIDEOPLL_VENC_LCD1;
        pmlibVideoPllClkSrc_t vidPllClkSrc =
            PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1;
    #if defined (SOC_TDA2EX)
        if (CSL_getSocSiliconPackageType() == CSL_SOC_SILICON_PACKAGE_TYPE_17X17)
        {
            vidPllVencId = PMLIB_VIDEOPLL_VENC_LCD3;
            vidPllClkSrc = PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3;
        }
    #endif
        retVal = PMLIBVideopllSetVencClkSrc(vidPllVencId, vidPllClkSrc);
    }
#endif

    return retVal;
}

