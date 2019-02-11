/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 *  \file st_vpeCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_vpe.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void st_vpsSetDefaultChPrms(st_VpeHandleObj *hObj,
                                   st_VpeChObj     *chObj,
                                   UInt32           chNum);
static Int32 st_vpeAllocOutBuf(const st_VpeHandleObj *hObj, st_VpeChObj *chObj);
static Int32 st_vpeFreeOutBuf(st_VpeChObj *chObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Used for YUYV422 progressive frame format.
 */
static st_VpeBufInfo Yuyv422Progressive = {NULL, 0u};
/**
 *  \brief Used for the YUYV422 interleaved interlaced frame format.
 */
static st_VpeBufInfo Yuyv422Interlaced = {NULL, 0u};
/**
 *  \brief Used for YUV 420 semiplanar progressive frame format.
 */
static st_VpeBufInfo Yuv420SpProgressive = {NULL, 0u};
/**
 *  \brief Used for the YUV 420 semiplanar interlaced frame format.
 */
static st_VpeBufInfo Yuv420SpInterlaced = {NULL, 0u};
/**
 *  \brief Used for YUV 422 semiplanar progressive frame format.
 */
static st_VpeBufInfo Yuv422SpProgressive = {NULL, 0u};
/**
 *  \brief Used for the YUV 422 semiplanar interlaced frame format.
 */
static st_VpeBufInfo Yuv422SpInterlaced = {NULL, 0u};

static UInt32        glbTestCounter = 0;
static UInt32        glbPassCounter = 0;
static UInt32        glbFailCounter = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_vpeInitVariables
 *  Initialize the global variables and frame pointers.
 */
Int32 st_vpeInitVariables(st_VpeHandleObj *hObj)
{
    Int32              retVal = FVID2_SOK;
    UInt32             chCnt, frmCnt, fListCnt;
    Fvid2_Frame       *frm;
    Fvid2_FrameList   *fList;
    Fvid2_ProcessList *pList;
    Semaphore_Params   semPrms;

    hObj->fvidHandle       = NULL;
    hObj->prfTsHandle      = NULL;
    hObj->reqCompleteSem   = NULL;
    hObj->completedLoopCnt = 0u;
    hObj->drvPrevTimeStamp = 0u;
    hObj->minCbTime        = 0xFFFFu;
    hObj->maxCbTime        = 0u;
    hObj->totalCbTime      = 0u;
    hObj->totalCbCount     = 0u;
    hObj->lastCbTime       = 0u;
    hObj->asyncClkHandle   = NULL;
    hObj->asyncTimerOn     = FALSE;
    hObj->asyncCbCnt       = 0u;
    hObj->asyncTimerValue  = 0u;
    for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
    {
        /* Init channel params */
        st_vpsSetDefaultChPrms(hObj, &hObj->chObj[chCnt], chCnt);
    }

    /* Init create params */
    VpsM2mCreateParams_init(&hObj->createPrms);
    hObj->createPrms.numCh           = hObj->numCh;
    hObj->createPrms.chInQueueLength = hObj->handleCfg.chInQueueLength;
    hObj->createPrms.isDeiFmdEnable  = hObj->handleCfg.isDeiFmdEnable;

    /* Init proc list */
    pList = &hObj->processList;
    Fvid2ProcessList_init(pList);
    pList->inFrameList[0u]  = &hObj->frameList[0u];
    pList->outFrameList[0u] = &hObj->frameList[1u];
    pList->numInLists       = 1u;
    pList->numOutLists      = 1u;

    /* Init frame list */
    for (fListCnt = 0u; fListCnt < VPE_NUM_FRAMELIST_PER_PLIST; fListCnt++)
    {
        fList = &hObj->frameList[fListCnt];
        Fvid2FrameList_init(fList);
        fList->numFrames = hObj->numCh;
        for (frmCnt = 0u; frmCnt < hObj->numCh; frmCnt++)
        {
            frm = &hObj->frames[fListCnt][frmCnt];
            fList->frames[frmCnt] = frm;
            Fvid2Frame_init(frm);
            frm->chNum = frmCnt;
        }
    }

    /* Init error process list */
    BspUtils_memset(
        &hObj->errProcessList, 0u, sizeof (hObj->errProcessList));

    /* Create TimeStamp object */
    hObj->prfTsHandle = BspUtils_prfTsCreate(APP_NAME);
    GT_assert(hObj->traceMask, (hObj->prfTsHandle != NULL));

    Semaphore_Params_init(&semPrms);
    hObj->reqCompleteSem = Semaphore_create(0, &semPrms, NULL);
    if (NULL == hObj->reqCompleteSem)
    {
        GT_0trace(hObj->traceMask, GT_ERR, "Sem create failed\r\n");
        retVal = FVID2_EALLOC;
    }

    if (FVID2_SOK == retVal)
    {
        for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
        {
            /* Allocate output buffers */
            retVal = st_vpeAllocOutBuf(hObj, &hObj->chObj[chCnt]);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(hObj->traceMask, GT_ERR,
                          "%s: Channel alloc buffer failed!!\r\n", APP_NAME);
                break;
            }
        }
    }

    if (FVID2_SOK != retVal)
    {
        st_vpeFreeVariables(hObj);
    }

    /* Print channel info */
    st_vpePrintChPrms(hObj);

    return (retVal);
}

/**
 *  st_vpeFreeVariables
 *  Free the allocated handles and buffers.
 */
void st_vpeFreeVariables(st_VpeHandleObj *hObj)
{
    Int32  retVal;
    UInt32 chCnt;

    for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
    {
        /* Free the allocated buffer memory */
        if (hObj->chObj[chCnt].outSaveBuf != NULL)
        {
            retVal = st_vpeFreeOutBuf(&hObj->chObj[chCnt]);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(hObj->traceMask, GT_ERR,
                          "%s: Channel free buffer failed!!\r\n", APP_NAME);
            }
        }
    }

    if (NULL != hObj->prfTsHandle)
    {
        BspUtils_prfTsDelete(hObj->prfTsHandle);
        hObj->prfTsHandle = NULL;
    }
    if (NULL != hObj->reqCompleteSem)
    {
        Semaphore_delete(&hObj->reqCompleteSem);
        hObj->reqCompleteSem = NULL;
    }

    return;
}

/**
 *  st_vpePrintChPrms
 *  \brief Prints the channel parameter.
 */
void st_vpePrintChPrms(const st_VpeHandleObj *hObj)
{
    UInt32             chCnt;
    const st_VpeChObj *chObj;
    static char       *enableDisableName[] = {"OFF", "ON"};
    static char        printBuf[300];

    GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(
        hObj->traceMask, GT_INFO1,
        " Ch.No | InWidth InHeight   InFormat     outWidth outHeight   outFormat"
        "     DEI   Subframe\r\n");
    GT_0trace(
        hObj->traceMask, GT_INFO1,
        "---------------------------------------------------------------------"
        "--------------------\r\n");
    for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
    {
        chObj = &hObj->chObj[chCnt];
        snprintf(
            printBuf, sizeof (printBuf),
#if defined(__GNUC__) && !defined(__ti__)
            "    %2d   %5d   %5d    %-15.15s %5d   %5d     %-15.15s %-5.5s %-5.5s",
#else
            "    %0.2d   %5d   %5d    %-15.15s %5d   %5d     %-15.15s %-5.5s %-5.5s",
#endif
            (unsigned int) chObj->chId,
            (unsigned int) chObj->chCfg.inWidth,
            (unsigned int) chObj->chCfg.inHeight,
            Fvid2_getDataFmtString(chObj->chCfg.inDataFmt),
            (unsigned int) chObj->chCfg.outWidth,
            (unsigned int) chObj->chCfg.outHeight,
            Fvid2_getDataFmtString(chObj->chCfg.outDataFmt),
            enableDisableName[!chObj->deiBypassFlag],
            enableDisableName[chObj->chCfg.subFrmPrms.subFrameEnable]);

        GT_1trace(hObj->traceMask, GT_INFO1, "%s\r\n", printBuf);
    }
    GT_0trace(hObj->traceMask, GT_INFO1, " \r\n");

    return;
}

/**
 *  st_vpePrintM2mVpeCreateStatus
 *  \brief Prints the M2M VPE driver create status information.
 */
void st_vpePrintM2mVpeCreateStatus(const st_VpeHandleObj     *hObj,
                                   const Vps_M2mCreateStatus *createStatus)
{
    GT_2trace(hObj->traceMask, GT_INFO1,
              "%s: VPE Create Status: Max Handles        : %d\r\n",
              APP_NAME, createStatus->maxHandles);
    GT_2trace(hObj->traceMask, GT_INFO1,
              "%s: VPE Create Status: Max Ch per Handle  : %d\r\n",
              APP_NAME, createStatus->maxChPerHandle);
    GT_2trace(hObj->traceMask, GT_INFO1,
              "%s: VPE Create Status: Max same Ch per Req: %d\r\n",
              APP_NAME, createStatus->maxSameChPerRequest);

    return;
}

/**
 *  st_vpeCalcPerformance
 */
Int32 st_vpeCalcPerformance(st_VpeHandleObj *hObj, UInt32 durationMs)
{
    UInt32       chCnt;
    UInt32       maxWidth, maxHeight, percent;
    UInt64       totalProcessedPixels;
    st_VpeChObj *chObj;

    totalProcessedPixels = 0u;
    for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
    {
        chObj    = &hObj->chObj[chCnt];
        maxWidth = st_vpeGetMax(chObj->chCfg.inWidth, chObj->chCfg.outWidth);
        if (TRUE == chObj->deiBypassFlag)
        {
            maxHeight =
                st_vpeGetMax(chObj->chCfg.inHeight, chObj->chCfg.outHeight);
        }
        else
        {
            maxHeight = st_vpeGetMax(
                chObj->chCfg.inHeight * 2u,
                chObj->chCfg.outHeight);
        }
        chObj->processedPixels = maxWidth * maxHeight * chObj->submittedFrames;
        totalProcessedPixels  += chObj->processedPixels;
    }

    /* Calculate performance */
    hObj->mps = (UInt32)
                ((totalProcessedPixels / (UInt64) 1000) / (UInt64) durationMs);

    percent = (hObj->mps * 100) / ST_VPE_CLK_TDA2XX;
    if (TRUE == Bsp_platformIsTI814xFamilyBuild())
    {
        percent = (hObj->mps * 100) / ST_VPE_CLK_TI814X;
    }
    GT_0trace(hObj->traceMask, GT_INFO, " \r\n");
    GT_4trace(
        hObj->traceMask, GT_INFO,
        "%s: Performance (Mega Pixels Per Second): %d MP/s (%d%s) \r\n",
        APP_NAME, hObj->mps, percent, "%");
    if (percent < ST_VPE_EXPECTED_PERFORMANCE)
    {
        GT_5trace(
            hObj->traceMask, GT_INFO,
            "%s: Warning: Performance (%d%s) is less than expected (%d%s)!!\r\n",
            APP_NAME, percent, "%", ST_VPE_EXPECTED_PERFORMANCE, "%");
    }

    return (FVID2_SOK);
}

/**
 *  st_vpePrintTimeStatus
 */
Int32 st_vpePrintTimeStatus(st_VpeHandleObj *hObj, Bool rtPrintEnable)
{
    static char printStr[256u];
    UInt32      avgCbDuration = 0U;

    if (hObj->totalCbCount != 0U)
    {
        avgCbDuration = (hObj->totalCbTime / hObj->totalCbCount);
    }
    sprintf(printStr,
            "<%d> %s: CallBack Interval: "
            "Avg (%dms), Min (%dms), Max (%dms)\r\n",
            (unsigned int) BspOsal_getCurTimeInMsec(), (char *) APP_NAME, (unsigned int) avgCbDuration,
            (unsigned int) hObj->minCbTime, (unsigned int) hObj->maxCbTime);
    if (TRUE == rtPrintEnable)
    {
        Bsp_rprintf(printStr);
    }
    else
    {
        Bsp_printf(printStr);
    }

    // TODO
#if 0
    /* Check if FPS is within range */
    if ((avgCbDuration < (expCbDuration - 1u)) ||
        (avgCbDuration > (expCbDuration + 1u)))
    {
        sprintf(printStr, "<%d> %s: Warning: FPS doesn't match the expected "
                "FPS!!\r\n", BspOsal_getCurTimeInMsec(), APP_NAME);
        if (TRUE == rtPrintEnable)
        {
            Bsp_rprintf(printStr);
        }
        else
        {
            Bsp_printf(printStr);
        }
    }
#endif

    return (FVID2_SOK);
}

/**
 *  st_vpeCheckHeapStat
 */
Int32 st_vpeCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
                          UInt32                        traceMask)
{
    Int32 retVal = BSP_SOK;
    BspUtils_MemHeapStatus curStat;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL != heapStat));

    BspUtils_memGetHeapStat(&curStat);

    if (heapStat->freeSysHeapSize != curStat.freeSysHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  "%s: Warning: Memory leak (%d bytes) in System Heap!!\r\n",
                  APP_NAME,
                  (heapStat->freeSysHeapSize - curStat.freeSysHeapSize));
        retVal = BSP_EFAIL;
    }
    if (heapStat->freeBufHeapSize != curStat.freeBufHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  "%s: Warning: Memory leak (%d bytes) in Buffer Heap!!\r\n",
                  APP_NAME,
                  (heapStat->freeBufHeapSize - curStat.freeBufHeapSize));
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  st_vpeProgramScCoeff
 *  Programs the scaler coefficient.
 */
Int32 st_vpeProgramScCoeff(st_VpeHandleObj *hObj)
{
    Int32 retVal = FVID2_SOK;
    Vps_ScCoeffParams coeffPrms;

    VpsScCoeffParams_init(&coeffPrms);
    coeffPrms.scalerId    = VPS_M2M_VPE_SCALER_ID_SC0;
    coeffPrms.hScalingSet = VPS_SC_DS_SET_8_16;
    coeffPrms.vScalingSet = VPS_SC_DS_SET_8_16;

    /* Program VPE scaler coefficient - Always used */
    GT_1trace(hObj->traceMask, GT_INFO1,
              "%s: Programming VPE Scaler coefficients ...\r\n", APP_NAME);
    retVal = Fvid2_control(
        hObj->fvidHandle,
        IOCTL_VPS_SET_COEFFS,
        &coeffPrms,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_1trace(hObj->traceMask, GT_ERR,
                  "%s: Programming of coefficients failed\r\n", APP_NAME);
        return (retVal);
    }
    else
    {
        GT_1trace(hObj->traceMask, GT_INFO1,
                  "%s: Programming VPE Scaler coefficients Done\r\n", APP_NAME);
    }

    return (retVal);
}

/**
 *  st_vpeLoadBuf
 */
Int32 st_vpeLoadBuf(const st_VpeUtObj *utObj, const st_VpeLoadBufCfg *cfg)
{
    Int32          retVal = FVID2_SOK;
    UInt32         bCnt;
    char           userInput;
    st_VpeBufInfo *bufInfo = NULL;
    char           fileNameString[100];
    UInt32         bytesRead;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            if (FVID2_SF_INTERLACED == cfg->scanFmt)
            {
                bufInfo = &Yuyv422Interlaced;
            }
            else
            {
                bufInfo = &Yuyv422Progressive;
            }
            BspUtils_memcpy(&bufInfo->bufCfg, cfg, sizeof (st_VpeLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_VPE_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->yBufAddrEven[bCnt] = NULL;
                    bufInfo->yBufAddrOdd[bCnt]  = NULL;
                    bufInfo->cBufAddrEven[bCnt] = NULL;
                    bufInfo->cBufAddrOdd[bCnt]  = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 2u)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 2u);
            }
            else
            {
                /* Calculate the new buffer size */
                bufInfo->bufSize =
                    bufInfo->bufCfg.pitch * bufInfo->bufCfg.height;
                bufInfo->totalBufSize =
                    bufInfo->bufSize * bufInfo->bufCfg.numBuffers;
                bufInfo->bufAddr = BspUtils_memAlloc(
                    bufInfo->totalBufSize,
                    VPS_BUFFER_ALIGNMENT);
                if (NULL == bufInfo->bufAddr)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Could not allocate buffer\r\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(utObj->traceMask, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_YUV420SP_UV:
            if (FVID2_SF_INTERLACED == cfg->scanFmt)
            {
                bufInfo = &Yuv420SpInterlaced;
            }
            else
            {
                bufInfo = &Yuv420SpProgressive;
            }
            BspUtils_memcpy(&bufInfo->bufCfg, cfg, sizeof (st_VpeLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width);
            }
            else
            {
                /* Calculate the new buffer size */
                bufInfo->bufSize =
                    (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height * 3u) / 2u;
                bufInfo->totalBufSize =
                    bufInfo->bufSize * bufInfo->bufCfg.numBuffers;
                bufInfo->bufAddr = BspUtils_memAlloc(
                    bufInfo->totalBufSize,
                    VPS_BUFFER_ALIGNMENT);
                if (NULL == bufInfo->bufAddr)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Could not allocate buffer\r\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(utObj->traceMask, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_YUV422SP_UV:
            if (FVID2_SF_INTERLACED == cfg->scanFmt)
            {
                bufInfo = &Yuv422SpInterlaced;
            }
            else
            {
                bufInfo = &Yuv422SpProgressive;
            }
            BspUtils_memcpy(&bufInfo->bufCfg, cfg, sizeof (st_VpeLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width);
            }
            else
            {
                /* Calculate the new buffer size */
                bufInfo->bufSize =
                    (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height * 2u);
                bufInfo->totalBufSize =
                    bufInfo->bufSize * bufInfo->bufCfg.numBuffers;
                bufInfo->bufAddr = BspUtils_memAlloc(
                    bufInfo->totalBufSize,
                    VPS_BUFFER_ALIGNMENT);
                if (NULL == bufInfo->bufAddr)
                {
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Could not allocate buffer\r\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(utObj->traceMask, NULL != bufInfo->bufAddr);
                }
            }
            break;

        default:
            GT_1trace(utObj->traceMask, GT_ERR,
                      "Invalid format: %d\r\n", cfg->dataFmt);
            bufInfo = NULL;
            retVal = FVID2_EFAIL;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        /* Assign the buffer addresses */
        for (bCnt = 0u; bCnt < bufInfo->bufCfg.numBuffers; bCnt++)
        {
            bufInfo->yBufAddrEven[bCnt] =
                (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
            if (FVID2_SF_PROGRESSIVE == cfg->scanFmt)
            {
                bufInfo->yBufAddrOdd[bCnt] =
                    ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                    + bufInfo->bufCfg.pitch;
                bufInfo->cBufAddrEven[bCnt] =
                    ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                    + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                bufInfo->cBufAddrOdd[bCnt] =
                    ((UInt8 *) bufInfo->cBufAddrEven[bCnt])
                    + bufInfo->bufCfg.pitch;
            }
            else
            {
                if (FVID2_DF_YUV422I_YUYV == cfg->dataFmt)
                {
                    bufInfo->yBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height) / 2u;
                }
                else if (FVID2_DF_YUV422SP_UV == cfg->dataFmt)
                {
                    bufInfo->yBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                    bufInfo->cBufAddrEven[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                    bufInfo->cBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrOdd[bCnt])
                        + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                }
                else
                {
                    bufInfo->yBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height * 3u) / 4u;
                    bufInfo->cBufAddrEven[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                    bufInfo->cBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrOdd[bCnt])
                        + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                }
            }
        }

        if (FVID2_SF_PROGRESSIVE == cfg->scanFmt)
        {
            /* Wait for the user to load the image */
            GT_6trace(utObj->traceMask, GT_INFO,
                      APP_NAME ": Load %d progressive %s video frames of "
                      "size %dx%d (Pitch: %d) to location: 0x%p\r\n",
                      bufInfo->bufCfg.numBuffers,
                      Fvid2_getDataFmtString(cfg->dataFmt),
                      bufInfo->bufCfg.width,
                      bufInfo->bufCfg.height,
                      bufInfo->bufCfg.pitch,
                      bufInfo->bufAddr);
        }
        else
        {
            GT_6trace(utObj->traceMask, GT_INFO,
                      APP_NAME ": Load %d interlaced %s video frames of "
                      "size %dx%d (Pitch: %d) to location: 0x%p\r\n",
                      bufInfo->bufCfg.numBuffers,
                      Fvid2_getDataFmtString(cfg->dataFmt),
                      bufInfo->bufCfg.width,
                      bufInfo->bufCfg.height,
                      bufInfo->bufCfg.pitch,
                      bufInfo->bufAddr);
        }
        BspUtils_appGetFileName(
            fileNameString,
            sizeof(fileNameString),
            "vpe",
            cfg->dataFmt,
            bufInfo->bufCfg.width,
            bufInfo->bufCfg.height);
        if (BSP_SOK != BspUtils_appLoadFileFromSd(
                fileNameString,
                "/vpe_input_files",
                (void *) bufInfo->bufAddr,
                bufInfo->totalBufSize,
                &bytesRead))
        {
            GT_1trace(utObj->traceMask, GT_INFO,
                "Loading file /vpe_input_files/%s from SD card failed. \r\n",
                fileNameString);
            BspUtils_appPrintLoadRawCmd(
                "vpe",
                (void *) bufInfo->bufAddr,
                cfg->dataFmt,
                bufInfo->bufCfg.width,
                bufInfo->bufCfg.height);

            if (TRUE != utObj->sysCtrl.skipHaltTests)
            {
                GT_1trace(utObj->traceMask, GT_INFO,
                          "%s: Enter any key after loading...\r\n", APP_NAME);
                BspUtils_uartGetChar(&userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);
            }
        }
    }

    return (retVal);
}

/**
 *  st_vpeFreeBuf
 */
Int32 st_vpeFreeBuf(const st_VpeUtObj *utObj, const st_VpeLoadBufCfg *cfg)
{
    Int32          retVal = FVID2_SOK;
    UInt32         bCnt;
    st_VpeBufInfo *bufInfo = NULL;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            if (FVID2_SF_INTERLACED == cfg->scanFmt)
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUYV422 Interlaced Buffer...\r\n");
                bufInfo = &Yuyv422Interlaced;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUYV422 Progressive Buffer...\r\n");
                bufInfo = &Yuyv422Progressive;
            }
            break;

        case FVID2_DF_YUV420SP_UV:
            if (FVID2_SF_INTERLACED == cfg->scanFmt)
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV420SP Interlaced Buffer...\r\n");
                bufInfo = &Yuv420SpInterlaced;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV420SP Progressive Buffer...\r\n");
                bufInfo = &Yuv420SpProgressive;
            }
            break;

        case FVID2_DF_YUV422SP_UV:
            if (FVID2_SF_INTERLACED == cfg->scanFmt)
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV422SP Interlaced Buffer...\r\n");
                bufInfo = &Yuv422SpInterlaced;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV422SP Progressive Buffer...\r\n");
                bufInfo = &Yuv422SpProgressive;
            }
            break;

        default:
            GT_1trace(utObj->traceMask, GT_ERR,
                      "Invalid format: %d\r\n", cfg->dataFmt);
            retVal  = FVID2_EFAIL;
            bufInfo = NULL;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        if (NULL != bufInfo->bufAddr)
        {
            /* Free up the buffer */
            BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

            bufInfo->bufAddr      = NULL;
            bufInfo->bufSize      = 0u;
            bufInfo->totalBufSize = 0u;
            for (bCnt = 0u; bCnt < ST_VPE_MAX_BUFFERS; bCnt++)
            {
                bufInfo->yBufAddrEven[bCnt] = NULL;
                bufInfo->yBufAddrOdd[bCnt]  = NULL;
                bufInfo->cBufAddrEven[bCnt] = NULL;
                bufInfo->cBufAddrOdd[bCnt]  = NULL;
            }
        }
    }

    return (retVal);
}

/**
 *  st_vpeGetBufInfo
 */
st_VpeBufInfo *st_vpeGetBufInfo(UInt32 dataFmt,
                                UInt32 scanFmt,
                                UInt32 traceMask)
{
    st_VpeBufInfo *bufInfo = NULL;

    switch (dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            if (FVID2_SF_INTERLACED == scanFmt)
            {
                bufInfo = &Yuyv422Interlaced;
            }
            else
            {
                bufInfo = &Yuyv422Progressive;
            }
            break;

        case FVID2_DF_YUV420SP_UV:
            if (FVID2_SF_INTERLACED == scanFmt)
            {
                bufInfo = &Yuv420SpInterlaced;
            }
            else
            {
                bufInfo = &Yuv420SpProgressive;
            }
            break;

        case FVID2_DF_YUV422SP_UV:
            if (FVID2_SF_INTERLACED == scanFmt)
            {
                bufInfo = &Yuv422SpInterlaced;
            }
            else
            {
                bufInfo = &Yuv422SpProgressive;
            }
            break;

        default:
            GT_1trace(traceMask, GT_ERR, "Invalid format: %d\r\n", dataFmt);
            bufInfo = NULL;
            break;
    }

    return (bufInfo);
}

void st_logTestResult(const st_VpeUtObj *utObj,
                      Int32              testResult,
                      UInt32             testCaseId,
                      char              *testcaseInfo)
{
    if (FVID2_SOK == testResult)
    {
        glbPassCounter++;
        GT_1trace(utObj->traceMask, GT_INFO,
                  "|TEST RESULT|PASS|%d|\r\n", testCaseId);
    }
    else
    {
        glbFailCounter++;
        GT_1trace(utObj->traceMask, GT_INFO,
                  "|TEST RESULT|FAIL|%d|\r\n", testCaseId);
    }

    glbTestCounter++;
    GT_1trace(utObj->traceMask, GT_INFO,
              "|TEST INFO|:: %s ::\r\n", testcaseInfo);
    GT_1trace(utObj->traceMask, GT_INFO,
              "|TEST END|:: %d ::\r\n", testCaseId);

    return;
}

void st_printTestResult(const st_VpeUtObj *utObj,
                        UInt32             skipCount,
                        UInt32             disableCount)
{
    GT_0trace(utObj->traceMask, GT_INFO,
              "\r\n*********Test Case Statistics*****************");
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case         : %d",
              (glbTestCounter + skipCount + disableCount));
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Executed: %d", glbTestCounter);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Passed  : %d", glbPassCounter);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Failed  : %d", glbFailCounter);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Skipped : %d", skipCount);
    GT_1trace(utObj->traceMask, GT_INFO,
              "\r\n      Total Test Case Disabled: %d", disableCount);
    GT_0trace(utObj->traceMask, GT_INFO,
              "\r\n*********************************************\r\n\r\n");

    return;
}

void st_resetTestResult(void)
{
    glbTestCounter = 0;
    glbPassCounter = 0;
    glbFailCounter = 0;

    return;
}

UInt32 st_calcBufferCrc(UInt8 *bufPtr, UInt32 numBytes)
{
    UInt32 crc32;

    /* Invalidate the buffer before access to get proper data that VPDMA has
     * written */
    BspOsal_cacheInv(bufPtr, numBytes, BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);

    crc32 = BspUtils_appGetCrc(bufPtr, numBytes);

    return (crc32);
}

/**
 *
 *  Sets the default channel parameters.
 */
static void st_vpsSetDefaultChPrms(st_VpeHandleObj *hObj,
                                   st_VpeChObj     *chObj,
                                   UInt32           chNum)
{
    UInt32 cntxIdx;
    Fvid2_Format     *fmt;
    Vps_M2mVpeParams *vpePrms;
    st_VpeChCfg      *chCfg;

    vpePrms = &chObj->vpePrms;
    chCfg   = &chObj->chCfg;

    /* Get buffer info as per required input format */
    chObj->inBufInfo = st_vpeGetBufInfo(
        chCfg->inDataFmt,
        chCfg->inScanFmt,
        hObj->traceMask);
    GT_assert(hObj->traceMask, (chObj->inBufInfo != NULL));

    chObj->chId            = chNum;
    chObj->numOutBuffers   = chObj->inBufInfo->bufCfg.numBuffers;
    chObj->outSaveBuf      = NULL;
    chObj->inBufIdx        = 0u;
    chObj->outBufIdx       = 0u;
    chObj->fid             = 0u;
    chObj->submittedFrames = 0u;
    chObj->processedPixels = 0u;
    chObj->subFrmIdx       = 0u;

    /* Set output buffer pitch */
    if (Fvid2_isDataFmtSemiPlanar(chCfg->outDataFmt))
    {
        chObj->outPitchY =
            VpsUtils_align(chCfg->outWidth, VPS_BUFFER_ALIGNMENT);
        chObj->outPitchCbCr = chObj->outPitchY;
    }
    else if (Fvid2_isDataFmtYuv422I(chCfg->outDataFmt))
    {
        chObj->outPitchY =
            VpsUtils_align(chCfg->outWidth * 2u, VPS_BUFFER_ALIGNMENT);
        chObj->outPitchCbCr = 0u;
    }
    else if ((FVID2_DF_RGB24_888 == chCfg->outDataFmt) ||
             (FVID2_DF_YUV444I == chCfg->outDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch aligined
         * to VPS_BUFFER_ALIGNMENT may not be multiple of 3 bytes (1 pixel) */
        chObj->outPitchY =
            VpsUtils_align(chCfg->outWidth * 3u, (VPS_BUFFER_ALIGNMENT * 3u));
        chObj->outPitchCbCr = 0u;
    }
    else
    {
        /* Other formats not supported */
        GT_assert(hObj->traceMask, FALSE);
    }

    VpsM2mVpeParams_init(vpePrms);
    vpePrms->chNum      = chNum;
    vpePrms->inMemType  = chCfg->inMemType;
    vpePrms->outMemType = chCfg->outMemType;

    /* Set the FVID2 format for VPE input */
    fmt         = &vpePrms->inFmt;
    fmt->chNum  = chNum;
    fmt->width  = chCfg->inWidth;
    fmt->height = chCfg->inHeight;
    if (Fvid2_isDataFmtSemiPlanar(chCfg->inDataFmt))
    {
        fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            chObj->inBufInfo->bufCfg.pitch;
        fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            chObj->inBufInfo->bufCfg.pitch;
        fmt->fieldMerged[FVID2_YUV_SP_Y_ADDR_IDX]    = FALSE;
        fmt->fieldMerged[FVID2_YUV_SP_CBCR_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
        if (Fvid2_isDataFmtYuv420Sp(chCfg->inDataFmt))
        {
            fmt->bpp = FVID2_BPP_BITS12;
        }
    }
    else
    {
        fmt->pitch[FVID2_YUV_INT_ADDR_IDX] =
            chObj->inBufInfo->bufCfg.pitch;
        fmt->fieldMerged[FVID2_YUV_INT_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
    }
    fmt->dataFormat = chCfg->inDataFmt;
    fmt->scanFormat = chCfg->inScanFmt;

    /* Set the FVID2 format for VPE writeback output */
    fmt         = &vpePrms->outFmt;
    fmt->chNum  = chNum;
    fmt->width  = chCfg->outWidth;
    fmt->height = chCfg->outHeight;
    if (Fvid2_isDataFmtSemiPlanar(chCfg->outDataFmt))
    {
        fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX]          = chObj->outPitchY;
        fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]       = chObj->outPitchCbCr;
        fmt->fieldMerged[FVID2_YUV_SP_Y_ADDR_IDX]    = FALSE;
        fmt->fieldMerged[FVID2_YUV_SP_CBCR_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
        if (Fvid2_isDataFmtYuv420Sp(chCfg->outDataFmt))
        {
            fmt->bpp = FVID2_BPP_BITS12;
        }
    }
    else
    {
        fmt->pitch[FVID2_YUV_INT_ADDR_IDX]       = chObj->outPitchY;
        fmt->fieldMerged[FVID2_YUV_INT_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
        if ((FVID2_DF_RGB24_888 == chCfg->outDataFmt) ||
            (FVID2_DF_YUV444I == chCfg->outDataFmt))
        {
            fmt->bpp = FVID2_BPP_BITS24;
        }
    }
    fmt->dataFormat = chCfg->outDataFmt;
    fmt->scanFormat = chCfg->outScanFmt;

    /* Set DEI cfg */
    BspUtils_memcpy(&vpePrms->deiCfg, &chCfg->deiCfg, sizeof (vpePrms->deiCfg));
    if (TRUE == vpePrms->deiCfg.bypass)
    {
        chObj->deiBypassFlag = TRUE;
    }
    else
    {
        chObj->deiBypassFlag = FALSE;
    }

    /* Set SC cfg */
    BspUtils_memcpy(&vpePrms->scCfg, &chCfg->scCfg, sizeof (vpePrms->scCfg));
    BspUtils_memcpy(
        &vpePrms->scCropCfg,
        &chCfg->scCropCfg,
        sizeof (vpePrms->scCropCfg));

    /* Set sub-frame params */
    BspUtils_memcpy(
        &vpePrms->subFramePrms,
        &chCfg->subFrmPrms,
        sizeof (vpePrms->subFramePrms));
    Fvid2SubFrameInfo_init(&chObj->subFrameInfoIn);
    Fvid2SubFrameInfo_init(&chObj->subFrameInfoOut);

    chObj->freeCntxFrameIndex = 0u;
    for (cntxIdx = 0u; cntxIdx < VPE_NO_OF_BUF_REQ_BEFORE_RES; cntxIdx++)
    {
        Fvid2Frame_init(&chObj->cntxFrames[cntxIdx]);
        chObj->cntxFrames[cntxIdx].chNum = chNum;
    }

    return;
}

/**
 *  st_vpeAllocOutBuf
 *  Allocates input and output buffers depending on format and memory mode.
 */
static Int32 st_vpeAllocOutBuf(const st_VpeHandleObj *hObj, st_VpeChObj *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cnt;
    UInt32 outBufSizeY, outBufSizeCbCr, printOutWidth;
    UInt8 *tempPtr;
    Char   fileStr[30u];

    chObj->outSaveBuf = NULL;
    for (cnt = 0u; cnt < chObj->numOutBuffers; cnt++)
    {
        chObj->outBufY[cnt]    = NULL;
        chObj->outBufCbCr[cnt] = NULL;
    }
    printOutWidth = 0u;

    /* Calculate the output buffer size depending on format */
    if (Fvid2_isDataFmtSemiPlanar(chObj->chCfg.outDataFmt))
    {
        outBufSizeY = chObj->outPitchY * chObj->chCfg.outHeight;
        if (Fvid2_isDataFmtYuv420Sp(chObj->chCfg.outDataFmt))
        {
            outBufSizeCbCr = outBufSizeY / 2u;
        }
        else
        {
            outBufSizeCbCr = outBufSizeY;
        }
        printOutWidth = chObj->outPitchY;
    }
    else if (Fvid2_isDataFmtYuv422I(chObj->chCfg.outDataFmt))
    {
        outBufSizeY    = chObj->outPitchY * chObj->chCfg.outHeight;
        outBufSizeCbCr = 0u;
        printOutWidth  = chObj->outPitchY / 2u;
    }
    else if ((FVID2_DF_RGB24_888 == chObj->chCfg.outDataFmt) ||
             (FVID2_DF_YUV444I == chObj->chCfg.outDataFmt))
    {
        outBufSizeY    = chObj->outPitchY * chObj->chCfg.outHeight;
        outBufSizeCbCr = 0u;
        printOutWidth  = chObj->outPitchY / 3u;
    }
    else
    {
        /* Other formats not supported */
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate output save memory for all the buffers at one
        * go so that memory is allocated contiguously. */
        chObj->outSaveBufSize =
            chObj->numOutBuffers * (outBufSizeY + outBufSizeCbCr);
        chObj->outSaveBuf =
            (UInt8 *) BspUtils_memAlloc(
                chObj->outSaveBufSize,
                VPS_BUFFER_ALIGNMENT);
        if (NULL == chObj->outSaveBuf)
        {
            retVal = FVID2_EALLOC;
        }
        else
        {
            if (Bsp_platformGetId() == BSP_PLATFORM_ID_EVM)
            {
                BspUtils_memset(chObj->outSaveBuf, 0u, chObj->outSaveBufSize);
                /* Flush the CPU access */
                BspOsal_cacheWbInv(
                    chObj->outSaveBuf,
                    chObj->outSaveBufSize,
                    BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Assign VPE writeback output buffers from out save buffer */
        tempPtr = chObj->outSaveBuf;
        for (cnt = 0u; cnt < chObj->numOutBuffers; cnt++)
        {
            chObj->outBufY[cnt] = tempPtr;
            tempPtr += outBufSizeY;
            if (outBufSizeCbCr > 0u)
            {
                chObj->outBufCbCr[cnt] = tempPtr;
                tempPtr += outBufSizeCbCr;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Print buffer address information */
        GT_3trace(hObj->traceMask, GT_INFO1,
                  "%s: VPE-WB Out Buffer Address: 0x%p, Size: 0x%p\r\n",
                  APP_NAME, chObj->outSaveBuf,
                  chObj->outSaveBufSize);
        snprintf(
#if defined(__GNUC__) && !defined(__ti__)
            fileStr, sizeof (fileStr), "vpeUtTC%4dCh%d",
#else
            fileStr, sizeof (fileStr), "vpeUtTC%0.4dCh%d",
#endif
            (unsigned int) hObj->testPrms->testCaseId, (unsigned int) (hObj->startChIdx + chObj->chId));
        if (GT_INFO1 & hObj->traceMask)
        {
            BspUtils_appPrintSaveRawCmd(
                fileStr,
                chObj->outSaveBuf,
                chObj->chCfg.outDataFmt,
                printOutWidth,
                chObj->chCfg.outHeight,
                chObj->outSaveBufSize);
        }
    }

    return (retVal);
}

/**
 *  st_vpeFreeOutBuf
 *  Frees the allocated input and output buffers.
 */
static Int32 st_vpeFreeOutBuf(st_VpeChObj *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cnt;

    if (NULL != chObj->outSaveBuf)
    {
        BspUtils_memFree(chObj->outSaveBuf, chObj->outSaveBufSize);
    }

    /* Reset the buffer address */
    chObj->outSaveBuf = NULL;
    for (cnt = 0u; cnt < chObj->numOutBuffers; cnt++)
    {
        chObj->outBufY[cnt]    = NULL;
        chObj->outBufCbCr[cnt] = NULL;
    }

    return (retVal);
}
