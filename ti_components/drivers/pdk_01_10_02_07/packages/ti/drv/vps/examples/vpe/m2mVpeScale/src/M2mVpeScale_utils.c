/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 */

/**
 *  \file M2mVpeScale_utils.c
 *
 *  \brief VPS VPE memory to memory driver example utility file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <M2mVpeScale_utils.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  App_m2mVpeAllocBuf
 *  Allocates input and output buffers depending on format and memory mode.
 */
Int32 App_m2mVpeAllocBuf(App_M2mVpeObj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cnt;
    UInt32 inBufSizeY = 0U, inBufSizeCbCr = 0U;
    UInt32 outBufSizeY = 0U, outBufSizeCbCr = 0U;
    UInt32 cInHeight = 0U, cOutHeight = 0U;
    UInt8 *tempPtr;

    appObj->inLoadBuf  = NULL;
    appObj->outSaveBuf = NULL;
    for (cnt = 0U; cnt < appObj->numInBuffers; cnt++)
    {
        appObj->inBufY[cnt]    = NULL;
        appObj->inBufCbCr[cnt] = NULL;
    }
    for (cnt = 0U; cnt < appObj->numOutBuffers; cnt++)
    {
        appObj->outBufY[cnt]    = NULL;
        appObj->outBufCbCr[cnt] = NULL;
    }

    /* Calculate pitch and make them aligned to VPS_BUFFER_ALIGNMENT.
     * Also calculate the input/output buffer size depending on format */
    if (Fvid2_isDataFmtSemiPlanar(appObj->inDataFmt))
    {
        if (VPS_VPDMA_MT_TILEDMEM == appObj->inMemType)
        {
            if (TRUE == appObj->isInDimSwapped)
            {
                appObj->inPitchY    = VPSUTILS_TILER_CNT_8BIT_SWAP_PITCH;
                appObj->inPitchCbCr = VPSUTILS_TILER_CNT_16BIT_SWAP_PITCH;
            }
            else
            {
                appObj->inPitchY    = VPSUTILS_TILER_CNT_8BIT_PITCH;
                appObj->inPitchCbCr = VPSUTILS_TILER_CNT_16BIT_PITCH;
            }
        }
        else
        {
            appObj->inPitchY =
                VpsUtils_align(appObj->inWidth, VPS_BUFFER_ALIGNMENT);
            appObj->inPitchCbCr = appObj->inPitchY;
        }
        inBufSizeY = VpsUtils_align(appObj->inWidth, VPS_BUFFER_ALIGNMENT) *
                     appObj->inHeight;
        if (Fvid2_isDataFmtYuv420Sp(appObj->inDataFmt))
        {
            inBufSizeCbCr = inBufSizeY / 2U;
            cInHeight     = appObj->inHeight / 2U;
        }
        else
        {
            inBufSizeCbCr = inBufSizeY;
            cInHeight     = appObj->inHeight;
        }
    }
    else if (Fvid2_isDataFmtYuv422I(appObj->inDataFmt))
    {
        appObj->inPitchY =
            VpsUtils_align(appObj->inWidth * 2U, VPS_BUFFER_ALIGNMENT);
        appObj->inPitchCbCr = 0U;
        inBufSizeY          = VpsUtils_align(appObj->inWidth * 2U,
                                             VPS_BUFFER_ALIGNMENT)
                              * appObj->inHeight;
        inBufSizeCbCr = 0U;
        cInHeight     = 0U;
    }
    else
    {
        /* Other formats not supported */
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    if (Fvid2_isDataFmtSemiPlanar(appObj->outDataFmt))
    {
        if (VPS_VPDMA_MT_TILEDMEM == appObj->outMemType)
        {
            if (TRUE == appObj->isOutDimSwapped)
            {
                appObj->outPitchY    = VPSUTILS_TILER_CNT_8BIT_SWAP_PITCH;
                appObj->outPitchCbCr = VPSUTILS_TILER_CNT_16BIT_SWAP_PITCH;
            }
            else
            {
                appObj->outPitchY    = VPSUTILS_TILER_CNT_8BIT_PITCH;
                appObj->outPitchCbCr = VPSUTILS_TILER_CNT_16BIT_PITCH;
            }
        }
        else
        {
            appObj->outPitchY =
                VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT);
            appObj->outPitchCbCr = appObj->outPitchY;
        }
        outBufSizeY =
            VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT) *
            appObj->outHeight;
        if (Fvid2_isDataFmtYuv420Sp(appObj->outDataFmt))
        {
            outBufSizeCbCr = outBufSizeY / 2U;
            cOutHeight     = appObj->outHeight / 2U;
        }
        else
        {
            outBufSizeCbCr = outBufSizeY;
            cOutHeight     = appObj->outHeight;
        }
    }
    else if (Fvid2_isDataFmtYuv422I(appObj->outDataFmt))
    {
        appObj->outPitchY =
            VpsUtils_align(appObj->outWidth * 2U, VPS_BUFFER_ALIGNMENT);
        appObj->outPitchCbCr = 0U;
        outBufSizeY          = appObj->outPitchY * appObj->outHeight;
        outBufSizeCbCr       = 0U;
        cOutHeight           = 0U;
    }
    else if ((FVID2_DF_RGB24_888 == appObj->outDataFmt) ||
             (FVID2_DF_YUV444I == appObj->outDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        appObj->outPitchY =
            VpsUtils_align(appObj->outWidth * 3U, (VPS_BUFFER_ALIGNMENT * 3U));
        appObj->outPitchCbCr = 0U;
        outBufSizeY          = appObj->outPitchY * appObj->outHeight;
        outBufSizeCbCr       = 0U;
        cOutHeight           = 0U;
    }
    else
    {
        /* Other formats not supported */
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    /* Allocate input load and output save memory for all the buffers at one
     * go so that memory is allocated contiguously. */
    appObj->inLoadBuf = (UInt8 *) BspUtils_memAlloc(
        (appObj->numInBuffers * (inBufSizeY + inBufSizeCbCr)),
        VPS_BUFFER_ALIGNMENT);
    if (NULL == appObj->inLoadBuf)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EALLOC;
    }

    appObj->outSaveBuf = (UInt8 *) BspUtils_memAlloc(
        (appObj->numOutBuffers * (outBufSizeY + outBufSizeCbCr)),
        VPS_BUFFER_ALIGNMENT);
    if (NULL == appObj->outSaveBuf)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EALLOC;
    }
    else
    {
        BspUtils_memset(
            appObj->outSaveBuf,
            0U,
            (appObj->numOutBuffers * (outBufSizeY + outBufSizeCbCr)));
        /* Flush and invalidate the CPU write */
        BspOsal_cacheWbInv(
            appObj->outSaveBuf,
            (appObj->numOutBuffers * (outBufSizeY + outBufSizeCbCr)),
            BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
    }

    /* Allocate input buffers from tiler memory or assign pointer depending on
     * whether the input is tiled or non tiled. */
    if (VPS_VPDMA_MT_TILEDMEM == appObj->inMemType)
    {
        for (cnt = 0U; cnt < appObj->numInBuffers; cnt++)
        {
            appObj->inBufY[cnt] = (UInt8 *) BspUtils_tilerAlloc(
                BSPUTILS_TILER_CNT_8BIT,
                appObj->inWidth,
                appObj->inHeight);
            if (NULL == appObj->inBufY[cnt])
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
                retVal = FVID2_EALLOC;
                break;
            }
            if (inBufSizeCbCr > 0U)
            {
                appObj->inBufCbCr[cnt] = (UInt8 *) BspUtils_tilerAlloc(
                    BSPUTILS_TILER_CNT_16BIT,
                    appObj->inWidth,
                    cInHeight);
                if (NULL == appObj->inBufCbCr[cnt])
                {
                    GT_2trace(BspAppTrace, GT_ERR,
                              "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
                    retVal = FVID2_EALLOC;
                    break;
                }
            }
        }
    }
    else
    {
        tempPtr = appObj->inLoadBuf;
        for (cnt = 0U; cnt < appObj->numInBuffers; cnt++)
        {
            appObj->inBufY[cnt] = tempPtr;
            tempPtr += inBufSizeY;
            if (inBufSizeCbCr > 0U)
            {
                appObj->inBufCbCr[cnt] = tempPtr;
                tempPtr += inBufSizeCbCr;
            }
        }
    }

    /* Allocate VPE output buffers from tiler memory or assign pointer
     * depending on whether the output is tiled or non tiled. */
    if (VPS_VPDMA_MT_TILEDMEM == appObj->outMemType)
    {
        for (cnt = 0U; cnt < appObj->numOutBuffers; cnt++)
        {
            appObj->outBufY[cnt] = (UInt8 *) BspUtils_tilerAlloc(
                BSPUTILS_TILER_CNT_8BIT,
                appObj->outWidth,
                appObj->outHeight);
            if (NULL == appObj->outBufY[cnt])
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
                retVal = FVID2_EALLOC;
                break;
            }
            if (outBufSizeCbCr > 0U)
            {
                appObj->outBufCbCr[cnt] = (UInt8 *)
                                          BspUtils_tilerAlloc(
                    BSPUTILS_TILER_CNT_16BIT,
                    appObj->outWidth,
                    cOutHeight);
                if (NULL == appObj->outBufCbCr[cnt])
                {
                    GT_2trace(BspAppTrace, GT_ERR,
                              "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
                    retVal = FVID2_EALLOC;
                    break;
                }
            }
        }
    }
    else
    {
        tempPtr = appObj->outSaveBuf;
        for (cnt = 0U; cnt < appObj->numOutBuffers; cnt++)
        {
            appObj->outBufY[cnt] = tempPtr;
            tempPtr += outBufSizeY;
            if (outBufSizeCbCr > 0U)
            {
                appObj->outBufCbCr[cnt] = tempPtr;
                tempPtr += outBufSizeCbCr;
            }
        }
    }

    /* Free the allocated memory if error occurs */
    if (FVID2_SOK != retVal)
    {
        App_m2mVpeFreeBuf(appObj);
    }
    else
    {
        /* Print buffer address information */
        GT_3trace(BspAppTrace, GT_INFO,
                  "%s: VPE In Buffer Address    : 0x%p, Size: 0x%p\r\n",
                  APP_NAME, appObj->inLoadBuf,
                  appObj->numInBuffers * (inBufSizeY + inBufSizeCbCr));
        appObj->inBufSize = inBufSizeY + inBufSizeCbCr;
        if (NULL != appObj->outSaveBuf)
        {
            GT_3trace(BspAppTrace, GT_INFO,
                      "%s: VPE-WB Out Buffer Address: 0x%p, Size: 0x%p\r\n",
                      APP_NAME, appObj->outSaveBuf,
                      (appObj->numOutBuffers * (outBufSizeY + outBufSizeCbCr)));
            appObj->outBufSize = outBufSizeY + outBufSizeCbCr;
        }
    }

    return (retVal);
}

/**
 *  App_m2mVpeFreeBuf
 *  Frees the allocated input and output buffers.
 */
Int32 App_m2mVpeFreeBuf(App_M2mVpeObj *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cnt;
    UInt32 inBufSizeY, inBufSizeCbCr;
    UInt32 outBufSizeY = 0U, outBufSizeCbCr = 0U;

    /* Calculate the input/output buffer size depending on format */
    if (Fvid2_isDataFmtYuv420Sp(appObj->inDataFmt))
    {
        inBufSizeY = VpsUtils_align(appObj->inWidth, VPS_BUFFER_ALIGNMENT) *
                     appObj->inHeight;
        inBufSizeCbCr = inBufSizeY / 2U;
    }
    else if (Fvid2_isDataFmtYuv422Sp(appObj->inDataFmt))
    {
        inBufSizeY = VpsUtils_align(appObj->inWidth, VPS_BUFFER_ALIGNMENT) *
                     appObj->inHeight;
        inBufSizeCbCr = inBufSizeY;
    }
    else
    {
        inBufSizeY = VpsUtils_align(appObj->inWidth * 2U, VPS_BUFFER_ALIGNMENT)
                     * appObj->inHeight;
        inBufSizeCbCr = 0U;
    }

    if (Fvid2_isDataFmtYuv420Sp(appObj->outDataFmt))
    {
        outBufSizeY = VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT) *
                      appObj->outHeight;
        outBufSizeCbCr = outBufSizeY / 2U;
    }
    else if (Fvid2_isDataFmtYuv422Sp(appObj->outDataFmt))
    {
        outBufSizeY = VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT) *
                      appObj->outHeight;
        outBufSizeCbCr = outBufSizeY;
    }
    else if (Fvid2_isDataFmtYuv422I(appObj->outDataFmt))
    {
        outBufSizeY =
            VpsUtils_align(appObj->outWidth * 2U, VPS_BUFFER_ALIGNMENT)
            * appObj->outHeight;
        outBufSizeCbCr = 0U;
    }
    else if ((FVID2_DF_RGB24_888 == appObj->outDataFmt) ||
             (FVID2_DF_YUV444I == appObj->outDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        outBufSizeY =
            VpsUtils_align(appObj->outWidth * 3U, (VPS_BUFFER_ALIGNMENT * 3U))
            * appObj->outHeight;
        outBufSizeCbCr = 0U;
    }
    else
    {
        /* Other formats not supported */
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    /* Free input load and output save buffers. */
    if (NULL != appObj->inLoadBuf)
    {
        BspUtils_memFree(
            appObj->inLoadBuf,
            (appObj->numInBuffers * (inBufSizeY + inBufSizeCbCr)));
    }
    if (NULL != appObj->outSaveBuf)
    {
        BspUtils_memFree(
            appObj->outSaveBuf,
            (appObj->numOutBuffers * (outBufSizeY + outBufSizeCbCr)));
    }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    /* Free tiled buffers if already allocated */
    BspUtils_tilerFreeAll();
#endif

    /* Reset the buffer address */
    appObj->inLoadBuf  = NULL;
    appObj->outSaveBuf = NULL;
    for (cnt = 0U; cnt < appObj->numInBuffers; cnt++)
    {
        appObj->inBufY[cnt]    = NULL;
        appObj->inBufCbCr[cnt] = NULL;
    }
    for (cnt = 0U; cnt < appObj->numOutBuffers; cnt++)
    {
        appObj->outBufY[cnt]    = NULL;
        appObj->outBufCbCr[cnt] = NULL;
    }

    return (retVal);
}

/**
 *  App_m2mVpeCopyToTilerMem
 *  Copies the input video to the tiler memory space if input memory mode
 *  to test is tiled.
 */
void App_m2mVpeCopyToTilerMem(const App_M2mVpeObj *appObj)
{
    UInt32 cnt;
    UInt32 inBufSizeY, inBufSizeCbCr, cHeight;
    UInt8 *tempPtr;

    /* Calculate the input buffer size depending on format */
    if (Fvid2_isDataFmtYuv420Sp(appObj->inDataFmt))
    {
        inBufSizeY = appObj->inWidth *
                     appObj->inHeight;
        inBufSizeCbCr = inBufSizeY / 2U;
        cHeight       = appObj->inHeight / 2U;
    }
    else if (Fvid2_isDataFmtYuv422Sp(appObj->inDataFmt))
    {
        inBufSizeY = VpsUtils_align(appObj->inWidth, VPS_BUFFER_ALIGNMENT) *
                     appObj->inHeight;
        inBufSizeCbCr = inBufSizeY;
        cHeight       = appObj->inHeight;
    }
    else
    {
        inBufSizeY = VpsUtils_align(appObj->inWidth * 2U, VPS_BUFFER_ALIGNMENT)
                     * appObj->inHeight;
        inBufSizeCbCr = 0U;
        cHeight       = 0U;
    }

    /* Copy the input buffer to tiled input buffer if input memory mode
     * is tiled */
    if ((NULL != appObj->inLoadBuf) &&
        (VPS_VPDMA_MT_TILEDMEM == appObj->inMemType))
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%s: Copying input buffer (0x%p) to tiler space...\r\n",
                  APP_NAME, appObj->inLoadBuf);
        tempPtr = appObj->inLoadBuf;
        for (cnt = 0U; cnt < appObj->numInBuffers; cnt++)
        {
            BspUtils_tilerCopy(
                BSPUTILS_TILER_COPY_FROM_DDR,
                (UInt32) appObj->inBufY[cnt],
                appObj->inWidth,
                appObj->inHeight,
                tempPtr,
                appObj->inWidth);
            tempPtr += inBufSizeY;
            if (NULL != appObj->inBufCbCr[cnt])
            {
                BspUtils_tilerCopy(
                    BSPUTILS_TILER_COPY_FROM_DDR,
                    (UInt32) appObj->inBufCbCr[cnt],
                    appObj->inWidth,
                    cHeight,
                    tempPtr,
                    appObj->inWidth);
                tempPtr += inBufSizeCbCr;
            }
        }
        GT_1trace(BspAppTrace, GT_INFO,
                  "%s: DDR to tiler copy done\r\n", APP_NAME);
    }

    return;
}

/**
 *  App_m2mVpeCopyFromTilerMem
 *  Copies the processed output video from tiler memory space to output memory
 *  when output mode to test is tiled.
 */
void App_m2mVpeCopyFromTilerMem(const App_M2mVpeObj *appObj)
{
    UInt32 cnt;
    UInt32 outBufSizeY = 0U, outBufSizeCbCr = 0U, cHeight = 0U;
    UInt8 *tempPtr;

    /* Calculate the output buffer size depending on format */
    if (Fvid2_isDataFmtYuv420Sp(appObj->outDataFmt))
    {
        outBufSizeY =
            VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT) *
            appObj->outHeight;
        outBufSizeCbCr = outBufSizeY / 2U;
        cHeight        = appObj->outHeight / 2U;
    }
    else if (Fvid2_isDataFmtYuv422Sp(appObj->outDataFmt))
    {
        outBufSizeY =
            VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT) *
            appObj->outHeight;
        outBufSizeCbCr = outBufSizeY;
        cHeight        = appObj->outHeight;
    }
    else if (Fvid2_isDataFmtYuv422I(appObj->outDataFmt))
    {
        outBufSizeY =
            VpsUtils_align(appObj->outWidth * 2U, VPS_BUFFER_ALIGNMENT) *
            appObj->outHeight;
        outBufSizeCbCr = 0U;
        cHeight        = 0U;
    }
    else if ((FVID2_DF_RGB24_888 == appObj->outDataFmt) ||
             (FVID2_DF_YUV444I == appObj->outDataFmt))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        outBufSizeY =
            VpsUtils_align(appObj->outWidth * 3U, (VPS_BUFFER_ALIGNMENT * 3U))
            * appObj->outHeight;
        outBufSizeCbCr = 0U;
        cHeight        = 0U;
    }
    else
    {
        /* Other formats not supported */
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
    }

    /* Copy the processed output buffer from tiler memory to input buffer if
     * output memory mode is tiled */
    if ((NULL != appObj->outSaveBuf) &&
        (VPS_VPDMA_MT_TILEDMEM == appObj->outMemType))
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%s: Copying tiled output buffer to save buffer (0x%p)...\r\n",
                  APP_NAME, appObj->outSaveBuf);
        tempPtr = appObj->outSaveBuf;
        for (cnt = 0U; cnt < appObj->numOutBuffers; cnt++)
        {
            if (NULL != appObj->outBufY[cnt])
            {
                BspUtils_tilerCopy(
                    BSPUTILS_TILER_COPY_TO_DDR,
                    (UInt32) appObj->outBufY[cnt],
                    appObj->outWidth,
                    appObj->outHeight,
                    tempPtr,
                    VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT));
                tempPtr += outBufSizeY;
            }
            if (NULL != appObj->outBufCbCr[cnt])
            {
                BspUtils_tilerCopy(
                    BSPUTILS_TILER_COPY_TO_DDR,
                    (UInt32) appObj->outBufCbCr[cnt],
                    appObj->outWidth,
                    cHeight,
                    tempPtr,
                    VpsUtils_align(appObj->outWidth, VPS_BUFFER_ALIGNMENT));
                tempPtr += outBufSizeCbCr;
            }
        }
        GT_1trace(BspAppTrace, GT_INFO,
                  "%s: Tiler to DDR copy done\r\n", APP_NAME);
    }

    return;
}

/**
 *  App_m2mVpeProgramScCoeff
 *  Programs the scaler coefficient.
 */
Int32 App_m2mVpeProgramScCoeff(App_M2mVpeObj *appObj)
{
    Int32 retVal = FVID2_SOK;
    Vps_ScCoeffParams coeffPrms;

    VpsScCoeffParams_init(&coeffPrms);
    coeffPrms.scalerId    = VPS_M2M_VPE_SCALER_ID_SC0;
    coeffPrms.hScalingSet = VPS_SC_DS_SET_8_16;
    coeffPrms.vScalingSet = VPS_SC_DS_SET_8_16;

    /* Program VPE scaler coefficient - Always used */
    GT_1trace(BspAppTrace, GT_INFO,
              "%s: Programming VPE Scaler coefficients ...\r\n", APP_NAME);
    retVal = Fvid2_control(
        appObj->fvidHandle,
        IOCTL_VPS_SET_COEFFS,
        &coeffPrms,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_1trace(BspAppTrace, GT_ERR,
                  "%s: Programming of coefficients failed\r\n", APP_NAME);
    }
    else
    {
        GT_1trace(BspAppTrace, GT_INFO,
                  "%s: Programming VPE Scaler coefficients Done\r\n", APP_NAME);
    }

    return (retVal);
}

/**
 *  App_m2mVpeSetFmdCfg
 *  Set DEI the film mode enable/disable config
 */
Int32 App_m2mVpeSetFmdCfg(App_M2mVpeObj *appObj, UInt16 fmdEnable)
{
    Int32 retVal = FVID2_SOK;
    Vps_DeiFmdConfig fmdCfg;

    /* Currently FMD only support single channel */
    if (appObj->numCh > 1U)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "FMD not supported for more than one channel!!\r\n");
        retVal = FVID2_EFAIL;
    }
    else
    {
        /* Set film mode detection to enable */
        fmdCfg.chNum      = 0; /* Only single channel is supported for FMD */
        fmdCfg.filmMode   = fmdEnable;
        fmdCfg.bed        = 1U;
        fmdCfg.window     = 0U;
        fmdCfg.lock       = 0U;
        fmdCfg.jamDir     = 0U;
        fmdCfg.windowMinx = 0U;
        fmdCfg.windowMiny = 0U;
        fmdCfg.windowMaxx = appObj->inWidth - 1U;
        fmdCfg.windowMaxy = appObj->inHeight - 1U;

        GT_1trace(BspAppTrace, GT_INFO,
                  "%s: Program DEI FMD config registers...\r\n", APP_NAME);
        retVal = Fvid2_control(
            appObj->fvidHandle,
            IOCTL_VPS_SET_DEI_FMD_CFG,
            &fmdCfg,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_3trace(BspAppTrace, GT_ERR,
                      "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal,
                      __LINE__);
        }
    }

    return (retVal);
}

