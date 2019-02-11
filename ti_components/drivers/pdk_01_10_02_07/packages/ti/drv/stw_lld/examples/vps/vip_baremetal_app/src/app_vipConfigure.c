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

#include <ti/drv/vps/include/vip/vps_vipDrv.h>
#include <ti/drv/vps/include/vps_dataTypes.h>

#include <app_vipConfigure.h>
#include <app_frameBufMgmt.h>

#define NUM_LINES_PER_SUBFRM (72U)

/* Maximum number of continuous interrupts*/
#define MAX_CONTI_OF_INTERRUPTS 2

/* Important parameters are marked "Important" in comments */
/* Parameters are marked "Ignore" - default values are already set */

extern volatile int         gNLinIntCount_s0portA;
extern volatile int         subFrmAdd[];
extern Fvid2_SubFrameInfo   gSubFrmInfo_s0portA;
extern volatile UInt32      gsubFrmCbCnt_s0portA;
extern volatile UInt32      gsubFrmAdd_s0portA;

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
VpsCore_VipParams           gVipParams_template =
{
    FVID2_DF_YUV422I_YUYV,
    0,                    /* srcWidth - Ignore - required only if scaler is used
                          **/
    0,                    /* srcHeight - Ignore - required only if scaler is
                           *used */
    1,                    /* numStreams - Ignore */
    {
        /* dstColorSpace[] - only first entry valid for use-case since
         * numStreams == 1 */
        FVID2_DF_RAW08,
        0,
        0,
        0
    },
    {
        0,
        0,
        0,
        0
    },
    /* tarWidth - Ignore -required only if scaler is used */
    {
        0,
        0,
        0,
        0
    },
    /* tarHeight - Ignore -required only if scaler is used */
    {
        /* pitch[][] - only (0,0) entry valid since (numStreams == 1)
         * and single plane (Luma/Chroma  interleaved) output. */
        {BUF_STRIDE,      0,  0}, /*pitch*/
        {0,               0,  0},
        {0,               0,  0},
        {0,               0,  0}
    },
    {
        0,
        0,
        0,
        0
    },
    /*scActive - Ignore - required only if scaler is used  */
    {
        0,
        NULL
    },
    /*edgeInfoList - Ignore */
    {0},
    /*portCfg - Important -set in App_configureVIP() */
    {0},
    /*inCropCfg - Ignore -required only if scaler is used  */
    {0},
    /*scCfg - Ignore - required only if scaler is used  */
    {0},
    /*cscCfg - Ignore - required only if CSC is used  */
    {
        /* subFrmPrms -Important - set in App_configureVIP() */
        {0,               0},
        {0,               0},
        {0,               0},
        {0,               0}
    },
    {
        {0,               0},
        {0,               0},
        {0,               0},
        {0,               0}
    },
    /* maxOutWidth[][]- Important Only (0,0) entry valid since
     * (numStreams == 1) and single plane (Luma/Chroma] interleaved)
     *  output.  Set in App_configureVIP() */
    {
        {0,               0},
        {0,               0},
        {0,               0},
        {0,               0}
    },
    /* maxOutWidth[][]- Important Only (0,0) entry valid since
     * (numStreams == 1) and single plane (Luma/Chroma] interleaved)
     *  output.  Set in App_configureVIP() */
    {
        0,
        0,
        0,
        0
    },
    /* memType- Ignore required if TILER is used */
};

/* Required for VpsDrv_captSetParams */
Vps_VipPortConfig           vipPortConfig =
{
    VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV, /* syncType
                                       * For embedded sync, change to
                                       * VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV
                                       * Important
                                       */
    TRUE,                             /* actCropEnable */
    FALSE,                            /* ancCropEnable */
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
        1280, /* cropWidth  */
        720,  /* cropHeight */
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
                               &captureOpenParams_s0PortA,
                               &gVipOpenParams_s1portA);
    }
    else if ((VPSHAL_VIP_S1 == sliceId) && (VPSHAL_VIP_PORT_B == portId))
    {
        pObj = VpsDrv_captOpen(vipInstId,
                               &captureOpenParams_s0PortB,
                               &gVipOpenParams_s1portB);
    }
    else
    {
        /*
         *  Do nothing
         */
    }

    return pObj;
}

Int32 App_coreClose(VpsDrv_CaptInstObj *pObj)
{
    Int32 retVal;

    retVal = VpsDrv_captControl(pObj, IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR, NULL, NULL);
    retVal += VpsDrv_captClose(pObj);

    return retVal;
}

Int32 App_coreStart(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_captStart(pObj);
}

Int32 App_coreStop(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_captStop(pObj);
}

Int32 App_SubFrmCbFxn_portA(VpsDrv_CaptInstObj  *pObj,
                            const VpsCore_Frame *subFrame)
{
    // TODO: Stub implementation
    /* only addr fields of variable subFrame will be valid */
    gsubFrmAdd_s0portA = (UInt32) subFrame->addr[0][0];
    gsubFrmCbCnt_s0portA++;

    gSubFrmInfo_s0portA.subFrameNum = gsubFrmCbCnt_s0portA;
    gSubFrmInfo_s0portA.numOutLines =
        (gsubFrmCbCnt_s0portA * NUM_LINES_PER_SUBFRM);

    gNLinIntCount_s0portA++;
    return BSP_SOK;
}

extern volatile int gNLinIntCount_s0portB;
Int32 App_SubFrmCbFxn_portB(VpsDrv_CaptInstObj  *pObj,
                            const VpsCore_Frame *subFrame)
{
    // TODO: Stub implementation
    // Current driver implementation does not return any valid information in
    // the variable "subFrame"
    gNLinIntCount_s0portB++;
    return BSP_SOK;
}

Int32 App_configureVIP(VpsDrv_CaptInstObj *pObj,
                       UInt32              sliceId,
                       UInt32              portId)
{
    Int32 retVal;
    VpsDrv_VipParams   drvVipPrms;
    VpsCore_VipParams *pathCfg = &gVipParams_template;
    Vps_OverflowParams overflowParams;

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
    pathCfg->subFrmPrms[0].numLinesPerSubFrame = NUM_LINES_PER_SUBFRM;
    pathCfg->subFrmPrms[0].interruptMode       = VPS_INTR_END_OF_EVERY_NTH_LINE;

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
    else
    {
        /*
         * Do nothing
         */
    }

    /*
     * VPDMA supports max-width/max-height setting based on pixels.
     * In raw mode, pixel size is assumed to be two bytes.
     * Therefore, 1280 pixel setting will allow raw-data width of
     * (1280*2) bytes to be captured.
     */
    pathCfg->maxOutWidth[0][0]  = VPS_VPDMA_MAX_OUT_WIDTH_1280_PIXELS;
    pathCfg->maxOutHeight[0][0] = VPS_VPDMA_MAX_OUT_HEIGHT_720_LINES;

    retVal =
        VpsDrv_captControl(pObj, IOCTL_VPS_CAPT_SET_VIP_PARAMS, &drvVipPrms,
                           NULL);

    if (retVal == BSP_SOK)
    {
        /* Give the callback function which should be called on overflow*/
        overflowParams.overflowCbFxn =
            (VpsDrv_VipOverflowFxn) & App_overflowIsr;
        /* Give the parameter that needs to be passed to the overflow ISR*/
        overflowParams.retParams = (void *) pObj;

        /* Register for interrupts. You can use
         * IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR
         * to unregister from the interrupts.
         */
        retVal =
            VpsDrv_captControl(pObj, IOCTL_VPS_CAPT_REGISTER_OVF_INTR,
                               &overflowParams,
                               NULL);
    }

    return retVal;
}

/* This will called in the case of overflow */
Int32 App_overflowIsr(VpsDrv_CaptInstObj *pObj)
{
    /* If the overflow keeps comming, and we are not able to exit from the ISR,
     *  stop the VIP. This will set the s/w reset bit in VIP_FIQ registers.
     */
    if (pObj->overflowCount > MAX_CONTI_OF_INTERRUPTS)
    {
        VpsDrv_captControl(pObj, IOCTL_VPS_CAPT_RESET_VIP_PORT,
                           NULL,
                           NULL);
    }
    return BSP_SOK;
}

Int32 App_checkOverflow(VpsDrv_CaptInstObj      *pObj,
                        Vps_OverflowCheckParams *overflow)
{
    Int32 retVal = BSP_SOK;
    /*Call driver to check if overflow is occured or not*/
    retVal = VpsDrv_captControl(pObj, IOCTL_VPS_CAPT_CHECK_OVERFLOW,
                                NULL,
                                overflow);
    return retVal;
}

Int32 App_portReset(VpsDrv_CaptInstObj *pObj)
{
    return VpsDrv_resetPort(pObj);
}

