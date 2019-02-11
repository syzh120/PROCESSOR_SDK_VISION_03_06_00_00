/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file M2mDssWb_utils.c
 *
 *  \brief DSS M2M application utils.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <M2mDssWb_main.h>

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

static Int32 M2mDssApp_loadInBufLocal(const M2mDssApp_LoadBufCfg *cfg);
static Int32 M2mDssApp_freeInBufLocal(const M2mDssApp_LoadBufCfg *cfg);
static M2mDssApp_BufInfo *M2mDssApp_getInBufInfo(UInt32 dataFmt, UInt32 pitch);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various load buffer configuration. */
static const M2mDssApp_LoadBufCfg gDispDssLoadBufCfg[] =
{
    /* width, height, pitch, dataFmt, numBuffers */
    {1920U, 1080U, (1920U * 2U), FVID2_DF_YUV422I_YUYV, M2MDSS_APP_NUM_IN_BUFFERS},
    {1920U, 1080U, (1920U * 2U), FVID2_DF_YUV422I_UYVY, M2MDSS_APP_NUM_IN_BUFFERS},
    {1920U, 1080U, 1920U,        FVID2_DF_YUV420SP_UV,  M2MDSS_APP_NUM_IN_BUFFERS},
    {1920U, 1080U, (1920U * 3U), FVID2_DF_BGR24_888,    M2MDSS_APP_NUM_IN_BUFFERS},
    {1920U, 1080U, (1920U * 2U), FVID2_DF_BGR16_565,    M2MDSS_APP_NUM_IN_BUFFERS},
};

/** \brief Used for YUYV422 interleaved frame format */
static M2mDssApp_BufInfo gYuyv422Buffer = {NULL, 0U};
/** \brief Used for UYVY422 interleaved frame format */
static M2mDssApp_BufInfo gUyvy422Buffer = {NULL, 0U};
/** \brief Used for YUV420SP frame format */
static M2mDssApp_BufInfo gYuv420spBuffer = {NULL, 0U};
/** \brief Used for BGR888 24-bit frame format */
static M2mDssApp_BufInfo gBGR24888Buffer = {NULL, 0U};
/** \brief Used for BGR565 16-bit frame format */
static M2mDssApp_BufInfo gBGR16565Buffer = {NULL, 0U};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 M2mDssApp_allocInBuf(void)
{
    Int32  retVal = FVID2_SOK;
    UInt32 bufCfgId;

    /* Load all the input Buffers */
    for (bufCfgId = 0;
         bufCfgId <
         (sizeof (gDispDssLoadBufCfg) / sizeof (M2mDssApp_LoadBufCfg));
         bufCfgId++)
    {
        retVal = M2mDssApp_loadInBufLocal(&gDispDssLoadBufCfg[bufCfgId]);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Load buffer failed!!\r\n");
        }
    }

    return (retVal);
}

Int32 M2mDssApp_freeInBuf(void)
{
    Int32  retVal = FVID2_SOK;
    UInt32 bufCfgId;

    /* Free all the Buffers */
    for (bufCfgId = 0;
         bufCfgId <
            (sizeof (gDispDssLoadBufCfg) / sizeof (M2mDssApp_LoadBufCfg));
         bufCfgId++)
    {
        retVal += M2mDssApp_freeInBufLocal(&gDispDssLoadBufCfg[bufCfgId]);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Free buffer failed!!\r\n");
        }
    }

    return (retVal);
}

Int32 M2mDssApp_allocOutBuf(M2mDssApp_Obj *appObj)
{
    Int32           retVal = FVID2_SOK;
    Fvid2_Format   *outFmt;

    appObj->outSaveBuf = NULL;
    outFmt = &appObj->dssPrms.outPipePrms.outFmt;
    if (Fvid2_isDataFmtSemiPlanar(outFmt->dataFormat))
    {
        appObj->outBufSize =
            (outFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX] * outFmt->height * 3U) / 2U;
    }
    else
    {
        appObj->outBufSize =
            outFmt->pitch[FVID2_YUV_INT_ADDR_IDX] * outFmt->height;
    }

    /* Allocate output buffers */
    appObj->outSaveBuf =
        (UInt8 *) BspUtils_memAlloc(
                      appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS,
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
            appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS);
        /* Flush and invalidate the CPU write */
        BspOsal_cacheWbInv(
            appObj->outSaveBuf,
            appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS,
            BSP_OSAL_CT_ALL,
            BSP_OSAL_WAIT_FOREVER);
        GT_3trace(BspAppTrace, GT_INFO,
            "%s: DSS_WB Out Buffer Address: 0x%p, Size: 0x%p\r\n",
            APP_NAME, appObj->outSaveBuf,
            (appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS));
    }

    return (retVal);
}

Int32 M2mDssApp_freeOutBuf(M2mDssApp_Obj *appObj)
{
    Int32  retVal = FVID2_SOK;

    if (NULL != appObj->outSaveBuf)
    {
        BspUtils_memFree(
            appObj->outSaveBuf,
            appObj->outBufSize * M2MDSS_APP_NUM_OUT_BUFFERS);
    }

    return (retVal);
}

/**
 *  \brief Init framee
 */
void M2mDssApp_initFrames(M2mDssApp_Obj *appObj)
{
    UInt32              frmId, pipeId;
    Fvid2_Frame        *frm;
    M2mDssApp_BufInfo  *bufInfo;
    Fvid2_Format       *inFmt, *outFmt;

    for (pipeId = 0U; pipeId < appObj->testPrms.numInPipeLines; pipeId++)
    {
        inFmt = &appObj->dssPrms.inPipePrms[pipeId].inFmt;
        bufInfo = M2mDssApp_getInBufInfo(inFmt->dataFormat, inFmt->pitch[0]);
        GT_assert(BspAppTrace, NULL != bufInfo);

        /* init memory pointer for all input frames */
        for (frmId = 0U; frmId < M2MDSS_APP_NUM_IN_BUFFERS; frmId++)
        {
            frm = &appObj->inFrames[pipeId][frmId];
            Fvid2Frame_init(frm);

            /* copy chNum from Fvid2_Format */
            frm->chNum      = 0U;
            frm->fid        = FVID2_FID_FRAME;
            frm->appData    = appObj;
            frm->addr[0][0] = bufInfo->bufAddr + (frmId * bufInfo->bufSize);
            if (Fvid2_isDataFmtSemiPlanar(inFmt->dataFormat))
            {
                frm->addr[0U][1U] =
                    (void *) ((UInt32) frm->addr[0U][0U] +
                              (inFmt->pitch[0U] * inFmt->height));
            }
        }
    }

    /* init memory pointer for all output frames */
    outFmt = &appObj->dssPrms.outPipePrms.outFmt;
    for (frmId = 0U; frmId < M2MDSS_APP_NUM_OUT_BUFFERS; frmId++)
    {
        frm = &appObj->outFrames[frmId];
        Fvid2Frame_init(frm);

        /* copy chNum from Fvid2_Format */
        frm->chNum      = 0U;
        frm->fid        = FVID2_FID_FRAME;
        frm->appData    = appObj;
        frm->addr[0][0] = appObj->outSaveBuf + (frmId * appObj->outBufSize);
        if (Fvid2_isDataFmtSemiPlanar(outFmt->dataFormat))
        {
            frm->addr[0U][1U] =
                (void *) ((UInt32) frm->addr[0U][0U] +
                          (outFmt->pitch[0U] * outFmt->height));
        }
    }

    return;
}

/**
 *  M2mDssApp_loadInBufLocal
 */
static Int32 M2mDssApp_loadInBufLocal(const M2mDssApp_LoadBufCfg *cfg)
{
    Int32               retVal = FVID2_SOK;
    char                userInput;
    M2mDssApp_BufInfo  *bufInfo = NULL;
    char                fileNameString[100];
    UInt32              bytesRead;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            bufInfo = &gYuyv422Buffer;
            memcpy(&bufInfo->bufCfg, cfg, sizeof (M2mDssApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 2u)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
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
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Could not allocate buffer\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(BspAppTrace, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_YUV422I_UYVY:
            bufInfo = &gUyvy422Buffer;
            memcpy(&bufInfo->bufCfg, cfg, sizeof (M2mDssApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 2u)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
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
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Could not allocate buffer\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(BspAppTrace, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_YUV420SP_UV:
            bufInfo = &gYuv420spBuffer;
            memcpy(&bufInfo->bufCfg, cfg, sizeof (M2mDssApp_LoadBufCfg));
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
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width);
            }
            else
            {
                /* Calculate the new buffer size */
                bufInfo->bufSize =
                    (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height * 3U) / 2U;
                bufInfo->totalBufSize =
                    bufInfo->bufSize * bufInfo->bufCfg.numBuffers;
                bufInfo->bufAddr = BspUtils_memAlloc(
                    bufInfo->totalBufSize,
                    VPS_BUFFER_ALIGNMENT);
                if (NULL == bufInfo->bufAddr)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Could not allocate buffer\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(BspAppTrace, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_BGR24_888:
            bufInfo = &gBGR24888Buffer;
            memcpy(&bufInfo->bufCfg, cfg, sizeof (M2mDssApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 3u)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 3u);
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
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Could not allocate buffer\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(BspAppTrace, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_BGR16_565:
            bufInfo = &gBGR16565Buffer;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (M2mDssApp_LoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 2u)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(BspAppTrace,
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
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Could not allocate buffer\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(BspAppTrace, NULL != bufInfo->bufAddr);
                }
            }
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
                      "Invalid format: %d\r\n", cfg->dataFmt);
            bufInfo = NULL;
            retVal  = FVID2_EFAIL;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        /* Try Loading the file from SD card if present.
         * If file is not present ask user to load using scripting console */
        BspUtils_appGetFileName(fileNameString,
                                sizeof (fileNameString),
                                "dssm2mwb",
                                bufInfo->bufCfg.dataFmt,
                                bufInfo->bufCfg.width,
                                bufInfo->bufCfg.height);
        BspUtils_appPrintLoadRawCmd(
            "dssm2mwb",
            bufInfo->bufAddr,
            bufInfo->bufCfg.dataFmt,
            bufInfo->bufCfg.width,
            bufInfo->bufCfg.height);
        if (BSP_SOK != BspUtils_appLoadFileFromSd(
                fileNameString,
                "/dssm2mwb_input_files",
                bufInfo->bufAddr,
                bufInfo->totalBufSize,
                &bytesRead))
        {
            GT_5trace(BspAppTrace, GT_INFO,
                      "Load %d %s video frames of size %dx%d to location: 0x%p\r\n",
                      bufInfo->bufCfg.numBuffers,
                      Fvid2_getDataFmtString(bufInfo->bufCfg.dataFmt),
                      bufInfo->bufCfg.width, bufInfo->bufCfg.height,
                      bufInfo->bufAddr);
            GT_1trace(BspAppTrace, GT_INFO,
                "Couldnot load file (/dssm2mwb_input_files/%s) from SD card!!\r\n"
                "Waiting for 1 min to load buffer from scripting console!!\r\n"
                "Press any key (in UART console) after loading buffer\r\n",
                fileNameString);
            BspUtils_uartGetChar(&userInput, 60);
            BspOsal_cacheWbInv(bufInfo->bufAddr, bufInfo->totalBufSize,
                               BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
        }
    }
    return retVal;
}

/**
 *  M2mDssApp_freeInBufLocal
 */
static Int32 M2mDssApp_freeInBufLocal(const M2mDssApp_LoadBufCfg *cfg)
{
    Int32               retVal = FVID2_SOK;
    M2mDssApp_BufInfo  *bufInfo = NULL;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing YUYV422 Buffer...\r\n");
            bufInfo = &gYuyv422Buffer;
            break;

        case FVID2_DF_YUV422I_UYVY:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing YUYV422 Buffer...\r\n");
            bufInfo = &gUyvy422Buffer;
            break;

        case FVID2_DF_YUV420SP_UV:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing YUV420SP Buffer...\r\n");
            bufInfo = &gYuv420spBuffer;
            break;

        case FVID2_DF_BGR24_888:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing BGR24 Buffer...\r\n");
            bufInfo = &gBGR24888Buffer;
            break;

        case FVID2_DF_BGR16_565:
            GT_0trace(BspAppTrace, GT_INFO,
                      "Freeing BGR16 Buffer...\r\n");
            bufInfo = &gBGR16565Buffer;
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
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
        }
    }
    return (retVal);
}

/**
 *  M2mDssApp_getInBufInfo
 */
static M2mDssApp_BufInfo *M2mDssApp_getInBufInfo(UInt32 dataFmt, UInt32 pitch)
{
    M2mDssApp_BufInfo *bufInfo = NULL;

    switch (dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            bufInfo = &gYuyv422Buffer;
            break;

        case FVID2_DF_YUV422I_UYVY:
            bufInfo = &gUyvy422Buffer;
            break;

        case FVID2_DF_YUV420SP_UV:
            bufInfo = &gYuv420spBuffer;
            break;

        case FVID2_DF_BGR24_888:
            bufInfo = &gBGR24888Buffer;
            break;

        case FVID2_DF_BGR16_565:
            bufInfo = &gBGR16565Buffer;
            break;

        default:
            GT_1trace(BspAppTrace, GT_ERR,
                      "Invalid format: %d\r\n", dataFmt);
            bufInfo = NULL;
            break;
    }
    return (bufInfo);
}
