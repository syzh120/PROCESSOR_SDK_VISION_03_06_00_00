/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <ti/drv/vps/src/vpslib/common/irm_resrcMgr.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/common/cal_evtmgr.h>
#include <ti/drv/vps/src/vpslib/calcore/vpscore_capture.h>

#include <ti/drv/stw_lld/uartconsole/uartStdio.h>

#include <app_framebufmgnt.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * \brief Info texts
 */
#define CAL_APP_UTIL                "CAL App "
#define CAL_APP_ERR                 " : Error :"
#define CAL_APP_INFO                " Info : "

/*
 * \brief Specific to CSI2 transmitter, below config is for UB954 EVM
 */
#define CAL_APP_NUM_LANES       (4)
/**< Number of active lanes, excluding clock */
#define CAL_APP_CSI2_PHY_MHZ    (400U)
/**< DDR Clock, CSI2 Clock */

#define CAL_APP_IN_WIDTH        (640U)
#define CAL_APP_IN_HEIGHT       (480U)
#define CAL_APP_IN_PITCH        (CAL_APP_IN_WIDTH * 3U)
/**< For RAW 12, this should be width * 2U */
#define CAL_APP_IN_BPP          (FVID2_BPP_BITS24)
/**< For RAW 12, this should be FVID2_BPP_BITS12 */

#define CAL_APP_CSI2_DATA_FMT   (VPS_ISS_CAL_CSI2_RGB888)
/**< In coming data format on CSI2 i/f.
     For RAW 12 this should be VPS_ISS_CAL_CSI2_RAW12 */

#define CAL_APP_INSTANCE_ID     (0U)
/**< CAL A */

#define CAL_APP_NOTIFY_LINE_NUM (16U)
/**< Enable notification on detection of above line number */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Application Object containing all the parameters
 */
typedef struct vpsAppObject
{
    UInt32                      instId;
    /**< CAL ID */
    volatile UInt32             frmDone;
    /**< Variable to wait for the frame completion interrupt */
    const VpsCore_Ops           *coreOps;
    /**< Core Operations of CAL core */
    VpsCore_Handle              *calCoreHndl;
    /**< CAL core handle */
    vcoreissCaptOpenRetParams_t coreOpenRtnParams;
    /**< Core allocated resources */
    const VpsCore_Frame         *pFramesCaptured[CAL_APP_NUM_FRAMES+1U];
    /**< Addresses of frames captured */
    volatile UInt32             index;
    /**< Index used to remember last frame captured */
    UInt32                      capFrameStatus[CAL_APP_NUM_FRAMES+1U];
    /**< Status of the captured frames */

    UInt32                      subFrmIndex;
    /**< Index used to remember last frame captured */
    Fvid2_SubFrameInfo          subFrameInfo[CAL_APP_TOTAL_NUM_SUB_FRAMES+1U];
    /**< Sub frame info returned */
    UInt32                      subFrameStatus[CAL_APP_TOTAL_NUM_SUB_FRAMES+1U];
    /**< status of frame returned at sub-frame/eof callback */
    const VpsCore_Frame         *pSubFramesCaptured[CAL_APP_NUM_FRAMES+1U];
    /**< Addresses of frames, returned by sub-frame CB */

    UInt32                      eofFrmIndex;
    /**< Index used to remember last frame captured */
    const VpsCore_Frame         *pEofFramesCaptured[CAL_APP_NUM_FRAMES+1U];
    /**< Addresses of frames, returned by end of frame CB */
    UInt32                      eofFrameStatus[CAL_APP_NUM_FRAMES+1U];
    /**< status of frame returned at sub-frame/eof callback */

    const VpsCore_Frame         *pFramesCapturedSeq[CAL_APP_NUM_CB+2U][2U];
    /**< Frames pointers, stored in order of notification in CB */
    UInt32                      frmSeqIndex;
    /**< Index for above */

    UInt32                      errUnkownCbEof[CAL_APP_NUM_FRAMES+1U];
    /**< Debug counter, to check if any classified callbacks are issued */
    UInt32                      errUnkownCbIdx;
    /**< Index for above */

    UInt32                      dataChk[CAL_APP_NUM_FRAMES+1U];
    /**< Data check, check to ensure data is present */
    UInt32                      dataChkIndex;
    /**< Index for above */

    UInt32                      timeTickVal[CAL_APP_NUM_FRAMES+1U];
    /**< Time stamp for frames returned */
    UInt32                      subFrameTimeTickVal[CAL_APP_NUM_FRAMES+1U];
    /**< Time stamp for sub-frame callback */
    UInt32                      eofFrameTimeTickVal[CAL_APP_NUM_FRAMES+1U];
    /**< Time stamp for end-frame callback */

} vpsAppObject_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 AppCalInit(vpsAppObject_t *appObj);
Int32 AppCalDeInit(vpsAppObject_t *appObj);
Int32 AppCalOpen(vpsAppObject_t *appObj);
Int32 AppCalClose(vpsAppObject_t *appObj);
Int32 AppCalApplyCfg(vpsAppObject_t *appObj);
Int32 AppCalRegErrCb(vpsAppObject_t *appObj);
Int32 AppCalRegEofFrmSubFrmCb(vpsAppObject_t *appObj);
Int32 AppCalSubFrame_FrameCapturedCb (void                 *drvData,
                                        const VpsCore_Frame *frame,
                                        Fvid2_SubFrameInfo  *subFrmInfo);
Int32 AppCalFrameCapturedCb(void *drvData, const VpsCore_Frame *frame);
VpsCore_Frame *AppCalReqFrameCb(void *drvData, UInt32 streamId, UInt32 chId);
Int32 AppCalCheckReceivedFrames(vpsAppObject_t *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* \brief Global Application Object */
vpsAppObject_t         gAppObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AppCalPrintErrorCode(Fvid2_FrameStatus status)
{
    UARTprintf(CAL_APP_UTIL CAL_APP_ERR, "");
    switch (status)
    {
        case FVID2_FRAME_STATUS_ECC_CORRECTED:
            UARTprintf("1 Bit ECC error detected and corrected \n");
        break;
        case FVID2_FRAME_STATUS_CRC_ERROR:
            UARTprintf("CRC error detected \n");
        break;
        case FVID2_FRAME_STATUS_ECC_ERROR:
            UARTprintf("ECC error detected \n");
        break;
        default:
            UARTprintf("UN Known error detected \n");
        break;
    }
}

Int32 AppCalDeInit(vpsAppObject_t *appObj)
{
    return VpsLib_deInit(NULL);
}

Int32 AppCalInit(vpsAppObject_t *appObj)
{
    Int32 status;

    CalAppUtils_IntrInit();

    status          = VpsLib_init(NULL);
    appObj->coreOps = VpsCore_issCaptGetCoreOps();

    return status;
}

Int32 AppCalClose(vpsAppObject_t *appObj)
{
    return appObj->coreOps->close(appObj->calCoreHndl);
}

Int32 AppCalOpen(vpsAppObject_t *appObj)
{
    VpsCore_OpenPrms         coreOpenFxns;
    vcoreissCaptOpenParams_t coreOpenParams;
    VpsCore_Inst coreInst;
    vpsissCalCmplxIoCfg_t   *pCmplxIoCfg;

    coreOpenFxns.drvData         = appObj;
    coreOpenFxns.reqFrmCb        = (VpsCore_ReqFrameCb) &AppCalReqFrameCb;
    coreOpenFxns.frmDoneCb       = (VpsCore_FrameDoneCb) &AppCalFrameCapturedCb;
    coreOpenFxns.frmDoneNotifyCb = NULL;

    coreOpenParams.csi2PhyClock[0U] = CAL_APP_CSI2_PHY_MHZ;
    coreOpenParams.captIf           = VPSCORE_ISS_CAPT_IF_CSI2;
    coreOpenParams.numStreams       = 1;
    coreOpenParams.subModules[0x0]  =
        (VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 |
         VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
         VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
         VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
         VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
         VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
         VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
         VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);

    coreOpenParams.isCmplxIoCfgValid[0U] = TRUE;
    pCmplxIoCfg                      = &coreOpenParams.cmplxIoCfg[0];
    pCmplxIoCfg->enable              = TRUE;
    pCmplxIoCfg->clockLane.pol       = FALSE;
    pCmplxIoCfg->clockLane.position  = 1;
    pCmplxIoCfg->data1Lane.pol       = FALSE;
    pCmplxIoCfg->data1Lane.position  = 2;
    pCmplxIoCfg->data2Lane.pol       = FALSE;
    pCmplxIoCfg->data2Lane.position  = 3;
    pCmplxIoCfg->data3Lane.pol       = FALSE;
    pCmplxIoCfg->data3Lane.position  = 4;
    pCmplxIoCfg->data4Lane.pol       = FALSE;
    pCmplxIoCfg->data4Lane.position  = 5;

    coreOpenParams.arg = NULL;

    coreInst = VpsCore_issCaptGetCoreInstObj(VPS_ISS_CAPT_CAL_A_ID);
    if(appObj->coreOps->open != NULL)
    {
        appObj->calCoreHndl = (VpsCore_Handle *) appObj->coreOps->open(
            coreInst,
            &coreOpenFxns,
            (const void *) &coreOpenParams,
            (void *) &appObj->coreOpenRtnParams);
        appObj->frmDone = 0x0;
        appObj->index   = 0;
        appObj->subFrmIndex = 0U;
        appObj->eofFrmIndex = 0U;
        appObj->frmSeqIndex = 0U;
        appObj->errUnkownCbIdx  = 0U;
        appObj->dataChkIndex = 0U;
    }
    return FVID2_SOK;
}

Int32 AppCalApplyCfg(vpsAppObject_t *appObj)
{
    Int32           status = FVID2_SOK;
    UInt32          i;
    vpsissCalCfg_t  cfg;

    cfg.numStream       = 1U;
    for (i = 0U; i < cfg.numStream; i++)
    {
        cfg.streamId[i]         = i;
        cfg.inFmt[i].width      = CAL_APP_IN_WIDTH;
        cfg.inFmt[i].height     = CAL_APP_IN_HEIGHT;

        cfg.inFmt[i].pitch[0]   = CAL_APP_IN_PITCH;
        cfg.inFmt[i].bpp        = CAL_APP_IN_BPP;
        cfg.csi2DataFormat[i]       = CAL_APP_CSI2_DATA_FMT;
        cfg.inFmt[i].dataFormat = 0x0U;

        cfg.csi2VirtualChanNo[i]    = 0x0U;
        cfg.streamType[i]           = VPS_ISS_CAL_TAG_PIX_DATA;
        cfg.isPixProcCfgValid[i]    = FALSE;
        cfg.isBysOutCfgValid[i]     = FALSE;
        cfg.bysInEnable[i]          = FALSE;
        cfg.isVportCfgValid[i]      = FALSE;
        cfg.writeToMem[i]           = TRUE;

        if (VPS_ISS_CAL_CSI2_RAW12 == CAL_APP_CSI2_DATA_FMT)
        {
            cfg.isPixProcCfgValid[i]   = TRUE;
            cfg.pixProcCfg[i].decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
            cfg.pixProcCfg[i].enableDpcmInitContext = FALSE;
            cfg.pixProcCfg[i].encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
            cfg.pixProcCfg[i].pack     = VPS_ISS_CAL_PIX_PACK_B16;
        }
        /* For VPS_ISS_CAL_CSI2_RGB888, there is no native support and hence
            treating it as 8 bit stream */
    }
    status = appObj->coreOps->control(appObj->calCoreHndl,
                                        VCORE_ISS_CAPT_CAL_SET_PARAMS,
                                        &cfg, NULL);
    return status;
}

Int32 AppCalRegErrCb(vpsAppObject_t *appObj)
{
    vpsissCalErrorCfg_t errSrcCfg;
    Int32        status = FVID2_SOK;

    errSrcCfg.cmplxIoId = 0U; /* Only 1, in TDA3x */
    errSrcCfg.numErrorsToMonitor = 0U;

    /* Un Correctable ECC errors */
    errSrcCfg.errSrc[errSrcCfg.numErrorsToMonitor] =
                                    VPS_CAL_CSI2_PPI_CMPLXIO_ECC_NO_CORRECTION;
    errSrcCfg.numErrorsToMonitor++;

    /* CRC errors */
    errSrcCfg.errSrc[errSrcCfg.numErrorsToMonitor] =
                                    VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1;
    errSrcCfg.numErrorsToMonitor++;

    /* Like to be notified of 1 bit ECC errors, which were corrected */
    errSrcCfg.errSrc[errSrcCfg.numErrorsToMonitor] =
                                    VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1;
    errSrcCfg.numErrorsToMonitor++;

    /* No callback provided, we will rely on frame status to determine if there
        were any errors.
        If require application could provide a callback here, which would called
        when error are detected */
    errSrcCfg.appCb = NULL;

    errSrcCfg.pAppCbArgs = NULL;
    errSrcCfg.pAdditionalArgs = NULL;

    status = appObj->coreOps->control(appObj->calCoreHndl,
                                        VCORE_ISS_CAPT_CAL_SET_ERR_PRMS,
                                        &errSrcCfg, NULL);

    return (status);
}

Int32 AppCalRegEofFrmSubFrmCb(vpsAppObject_t *appObj)
{
    Int32 status;
    UInt32 idx;
    vcoreissCaptSubFrameCfg_t subFrmCfg;

    subFrmCfg.numStream = 0U;
    for (idx = 0U; idx < CAL_APP_NUM_SUB_FRAMES; idx++)
    {
        subFrmCfg.numStream++;
        subFrmCfg.streamId[idx]                 = 0x0U;
        subFrmCfg.notifyAfterFirstXLines[idx]   = CAL_APP_NOTIFY_LINE_NUM;
        subFrmCfg.notifyAfterEndOfFrame[idx]    = TRUE;
    }

    subFrmCfg.appCb = (VpsCore_SubFrameCbFxn) &AppCalSubFrame_FrameCapturedCb;
    subFrmCfg.pAppCbArgs = appObj;
    subFrmCfg.pAdditionalArgs = NULL;
    status = appObj->coreOps->control(appObj->calCoreHndl,
                                        VCORE_ISS_CAPT_CAL_SET_SUB_FRM_PRMS,
                                        &subFrmCfg, NULL);

    return (status);
}

/* Callback, will be called for Nth line and end of frame */
Int32 AppCalSubFrame_FrameCapturedCb (void                 *drvData,
                                        const VpsCore_Frame *frame,
                                        Fvid2_SubFrameInfo  *subFrmInfo)
{
    vpsAppObject_t *pAppObj;
    Fvid2_SubFrameInfo *pSubFrmInfo;

    pAppObj = (vpsAppObject_t *) drvData;

    /* Nth line / Sub frame callback */
    if ((CAL_APP_NUM_SUB_FRAMES > subFrmInfo->subFrameNum) &&
        (CAL_APP_TOTAL_NUM_SUB_FRAMES > pAppObj->subFrmIndex))
    {
        pSubFrmInfo = &pAppObj->subFrameInfo[pAppObj->subFrmIndex];

        /* Sub frame Info */
        pSubFrmInfo->subFrameNum = subFrmInfo->subFrameNum;
        pSubFrmInfo->numOutLines = subFrmInfo->numOutLines;
        pSubFrmInfo->numInLines  = 0U;

        /* Book keeping for error, sequence checks */
        pAppObj->subFrameStatus[pAppObj->subFrmIndex] = frame->status;
        pAppObj->pSubFramesCaptured[pAppObj->subFrmIndex] = frame;
        pAppObj->subFrameTimeTickVal[pAppObj->subFrmIndex] =
                                                        BspOsal_getClockTicks();
        pAppObj->subFrmIndex++;

        if (pAppObj->frmSeqIndex < CAL_APP_NUM_CB)
        {
            pAppObj->pFramesCapturedSeq[pAppObj->frmSeqIndex][0U] = frame;
            pAppObj->pFramesCapturedSeq[pAppObj->frmSeqIndex]
                                                        [1U] = CAL_APP_SUB_F_CB;
            pAppObj->frmSeqIndex++;
        }
        if (CAL_APP_NUM_FRAMES > pAppObj->dataChkIndex)
        {
            pAppObj->dataChk[pAppObj->dataChkIndex] =
                *((UInt32 *)((UInt32) frame->addr[0U][0U] +
                            ((CAL_APP_IN_PITCH) * CAL_APP_NOTIFY_LINE_NUM)));
            pAppObj->dataChkIndex++;
        }

    } else

    /* End of frame */
    if ((CAL_APP_NUM_SUB_FRAMES == subFrmInfo->subFrameNum) &&
        (CAL_APP_NUM_FRAMES > pAppObj->eofFrmIndex))
    {
        /* frame : Pointer to just captured frame */

        /* Book keeping for error, sequence checks */
        if (pAppObj->frmSeqIndex < CAL_APP_NUM_CB)
        {
            pAppObj->pFramesCapturedSeq[pAppObj->frmSeqIndex][0U] = frame;
            pAppObj->pFramesCapturedSeq[pAppObj->frmSeqIndex]
                                                        [1U] = CAL_APP_EOF_CB;
            pAppObj->frmSeqIndex++;
        }
        pAppObj->eofFrameStatus[pAppObj->eofFrmIndex] = frame->status;
        pAppObj->pEofFramesCaptured[pAppObj->eofFrmIndex] = frame;
        pAppObj->eofFrameTimeTickVal[pAppObj->eofFrmIndex] =
                                                        BspOsal_getClockTicks();
        pAppObj->eofFrmIndex++;
    }
    else if (CAL_APP_NUM_SUB_FRAMES < subFrmInfo->subFrameNum)
    {
        pAppObj->errUnkownCbEof[pAppObj->errUnkownCbIdx] =
                                                        subFrmInfo->subFrameNum;
        pAppObj->errUnkownCbIdx++;
    }
    else
    {
        /* Beyond the storage allocated to store status, this can occur stop
            */
    }

    return 0x0;
}

Int32 AppCalFrameCapturedCb(void *drvData, const VpsCore_Frame *frame)
{
    vpsAppObject_t *pAppObj;
    pAppObj = (vpsAppObject_t *) drvData;
    if(gAppObj.index < CAL_APP_NUM_FRAMES)
    {
        if (pAppObj->frmSeqIndex < CAL_APP_NUM_CB)
        {
            pAppObj->pFramesCapturedSeq[pAppObj->frmSeqIndex][0U] = frame;
            pAppObj->pFramesCapturedSeq[pAppObj->frmSeqIndex]
                                                        [1U] = CAL_APP_CAPT_F_CB;
            pAppObj->frmSeqIndex++;
        }

        gAppObj.timeTickVal[gAppObj.index] = BspOsal_getClockTicks();
        gAppObj.capFrameStatus[gAppObj.index] = frame->status;
        gAppObj.pFramesCaptured[gAppObj.index++] = frame;
    }

    pAppObj->frmDone++;
    return 0x0;
}

VpsCore_Frame *AppCalReqFrameCb(void *drvData, UInt32 streamId, UInt32 chId)
{
    VpsCore_Frame *pCoreFrame = NULL;
    pCoreFrame = CalAppUtils_GetFrameBuf();

    /* Ensure to clear location used to check */
    *((UInt32 *)((UInt32) pCoreFrame->addr[0U][0U] +
                ((CAL_APP_IN_PITCH) * CAL_APP_NOTIFY_LINE_NUM))) = 0xFEEDFEED;

    return pCoreFrame;
}


Int32 main(void)
{
    Int32 status, totalBytes;

    /* Initialize dependencies, UART, I2C, PM */
    CalAppUtils_BoardInit();

    /* Initialize platform, ISS control, power up CAL / ISP */
    gAppObj.instId = CAL_APP_INSTANCE_ID;
    status         = AppCalInit(&gAppObj);
    if(FVID2_SOK != status)
    {
        UARTprintf(CAL_APP_UTIL CAL_APP_ERR "Core Init Failed\n");
    }
    else
    {
        /* Initialize Buffer Manager Utils */
        CalAppUtils_FrameBufInit();

        status = AppCalOpen(&gAppObj);
        if(FVID2_SOK != status)
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR "Core Open Failed\n");
        }
        else
        {
            status = AppCalApplyCfg(&gAppObj);
            if(FVID2_SOK != status)
            {
                UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                        "ISS CAL App: Core could not apply config\n");
            }

            if(FVID2_SOK == status)
            {
                AppCalRegErrCb(&gAppObj);
                if(FVID2_SOK != status)
                {
                    UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                        "ISS CAL App: Core could not register error CB's \n");
                }
            }

            if(FVID2_SOK == status)
            {
                AppCalRegEofFrmSubFrmCb(&gAppObj);
                if(FVID2_SOK != status)
                {
                    UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                    "ISS CAL App: Core could not register EOF/SUB Frm CB's \n");
                }
            }

            if(FVID2_SOK == status)
            {
                UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                                            "Configured CAL to receive!!!\n");
                UARTprintf(CAL_APP_UTIL CAL_APP_INFO "Configuring Sensor!!!\n");

                /* With external sensor, remove this API, initialize the
                    sensor here */
                CalAppUtils_appInitUb954_Ub953();

                UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                                        "Sensor configured & Streaming!!!\n");

                UARTprintf(CAL_APP_UTIL CAL_APP_INFO "Starting Capture Now!!!\n");
                status = gAppObj.coreOps->start(gAppObj.calCoreHndl);

                while(gAppObj.frmDone < CAL_APP_NUM_FRAMES)
                {
                    static uint32_t lastFrameNo = 0;
                    uint32_t        temp;
                    if(lastFrameNo != gAppObj.frmDone)
                    {
                        temp        = lastFrameNo;
                        lastFrameNo = gAppObj.frmDone;
                        UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                        "Received Frame %x of %x\n", temp, CAL_APP_NUM_FRAMES);
                    }
                }

                status = gAppObj.coreOps->stop(gAppObj.calCoreHndl);

                UARTprintf(CAL_APP_UTIL CAL_APP_INFO
                                        "Frame reception is completed \n");
                totalBytes = (CAL_APP_IN_PITCH * CAL_APP_IN_HEIGHT) / 4U;

                CalAppUtils_appDeInitUb954_Ub953();

                AppCalCheckReceivedFrames(&gAppObj);

                while(gAppObj.index)
                {
                    gAppObj.index--;

                    if (FVID2_FRAME_STATUS_COMPLETED ==
                            gAppObj.capFrameStatus[gAppObj.index])
                    {
                        UARTprintf("saveRaw(0, 0x%x, "
                           "\"D:\\\\RGB888_%dx%d.yuv\","
                           "%d, 32, false)\n",
                           gAppObj.pFramesCaptured[gAppObj.index]->addr[0U][0U],
                           CAL_APP_IN_WIDTH, CAL_APP_IN_HEIGHT,
                           totalBytes);
                    }
                    else
                    {
                        UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                            "Detected following error (s) \n");
                        AppCalPrintErrorCode( (Fvid2_FrameStatus)
                                    gAppObj.capFrameStatus[gAppObj.index]);
                        UARTprintf("saveRaw(0, 0x%x, "
                           "\"D:\\\\RGB888_%dx%d.yuv\","
                           "%d, 32, false)\n",
                           gAppObj.pFramesCaptured[gAppObj.index]->addr[0U][0U],
                           CAL_APP_IN_WIDTH, CAL_APP_IN_HEIGHT,
                           totalBytes);
                    }
                }
                UARTprintf (CAL_APP_UTIL CAL_APP_INFO "Put a break point here"
                        ", In case you want to save frames using above "
                        "commands \n");
                AppCalClose(&gAppObj);

                AppCalDeInit(&gAppObj);

                UARTprintf (CAL_APP_UTIL CAL_APP_INFO "ISS CAL App: Passed\n");
            }
        }
    }
    return 0;
}

Int32 AppCalCheckReceivedFrames(vpsAppObject_t *appObj)
{
    UInt32 idx;
    /* Checks performed
        Check 1 : Ensure correct frames are returned.
                    i.e. Received frame address should same for sub-frame,
                    start of frame and end of frame
        Check 2 : Captured line numbers are marked correctly
        Check 3 : Ensure frames are received in correct order.
                    i.e. First should be Sub Frame CB, End of Frame and
                    captured frame
        Check 4 : Data Available in DDR, when sub-frame callback is received.
        Check 5 : Time stamp : Check if in order
    */
    /* Check 1 : Ensure correct frames are returned. */
    for (idx = 0U; idx < CAL_APP_NUM_FRAMES; idx++)
    {
        if (appObj->pEofFramesCaptured[idx] != appObj->pFramesCaptured[idx])
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                "Frames returned in EoF and Frame captured CB don't match \n");
        }
        if (appObj->pSubFramesCaptured[idx] != appObj->pFramesCaptured[idx])
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                "Frames returned in SubFrame CB and Frame captured CB "
                "don't match \n");
        }
    }
    if (idx != CAL_APP_NUM_FRAMES)
    {
        UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                            "Eof and frame captured CB don't add up \n");
    }
    else
    {
        UARTprintf (CAL_APP_UTIL CAL_APP_INFO "Received 0x%x Sub Frame CB \n",
                        appObj->subFrmIndex);
        UARTprintf (CAL_APP_UTIL CAL_APP_INFO "Received 0x%x EOF CB \n",
                        appObj->eofFrmIndex);
        UARTprintf (CAL_APP_UTIL CAL_APP_INFO "Received 0x%x Frame Done CB \n",
                        appObj->index);
        if (0U != appObj->errUnkownCbIdx)
        {
            UARTprintf (CAL_APP_UTIL CAL_APP_INFO "Received 0x%x Error CB \n",
                            appObj->errUnkownCbIdx);
        }
    }

    /* Check 2 : Captured line numbers are marked correctly */
    for (idx = 0U; idx < appObj->errUnkownCbIdx; idx++)
    {
        UARTprintf (CAL_APP_UTIL CAL_APP_INFO
                    "Received 0x%x Error CB Sub Frame no\n",
                    appObj->errUnkownCbEof[idx]);
    }

    /* Check 3 : Ensure frames are received in correct order. */
    for (idx = 0U; idx < CAL_APP_NUM_CB; idx +=3U)
    {
        if ((appObj->pFramesCapturedSeq[idx+0U][0U] !=
             appObj->pFramesCapturedSeq[idx+1U][0U]) ||
            (appObj->pFramesCapturedSeq[idx+0U][0U] !=
             appObj->pFramesCapturedSeq[idx+2U][0U]))
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                "Frames returned in Sub Frame, End Of Frame and Capture"
                " completed don't match !!!\n");
        }
        if ((appObj->pFramesCapturedSeq[idx+0U][1U] != CAL_APP_SUB_F_CB) ||
            (appObj->pFramesCapturedSeq[idx+1U][1U] != CAL_APP_EOF_CB) ||
            (appObj->pFramesCapturedSeq[idx+2U][1U] != CAL_APP_CAPT_F_CB))
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                "Sequence of CB isn't correct !!! \n"
                "Expected sequence is SubFrame, End of Frame and"
                " Capture completed \n");
        }
    }

    /* Check 4 : Data Available in DDR, when sub-frame callback is received */
    for (idx = 0U; idx < CAL_APP_NUM_FRAMES; idx++)
    {
        if (appObj->dataChk[idx] != 0xAAAAAAAA)
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                        "Data is in-consistent in SubFrame CB !!!\n");
        }
    }
    /* Check 5 : Time stamp : Check if in order */
    for (idx = 0U; idx < CAL_APP_NUM_FRAMES; idx++)
    {
        if (appObj->subFrameTimeTickVal[idx] >=
            appObj->eofFrameTimeTickVal[idx])
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                        "End of sub-frame was notified after EOF !!!\n");
        }
        else if (appObj->eofFrameTimeTickVal[idx] >=
                    appObj->timeTickVal[idx])
        {
            UARTprintf(CAL_APP_UTIL CAL_APP_ERR
                    "End of frame was notified after frame was returned !!!\n");
        }
        else
        {
            /* Everything in order */
        }
    }
    return 0x0;
}
