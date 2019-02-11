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
 *  \file st_displayCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <st_dispDss.h>

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
/**
 *  \brief Used for YUYV422 interleaved progressive frame format or interlaced
 *  frame format with fields merged. => 800x480 input
 */
static st_DispDssBufInfo Yuyv422FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for the YUYV422 interleaved interlaced frame format with fields
 *  in seperate planes.. => 800x480 input
 */
static st_DispDssBufInfo Yuyv422InterlacedFieldsSep = {NULL, 0u};
/**
 *  \brief Used for YUV 420 semiplanar progressive frame format or interlaced
 *  frame format with fields merged.
 */
static st_DispDssBufInfo Yuv420SpFieldsMerged = {NULL, 0u};
/**
 *  \brief Used for the YUV 420 semiplanar interlaced frame format with fields
 *  in seperate planes.
 */
static st_DispDssBufInfo Yuv420SpInterlacedFieldsSep = {NULL, 0u};
/**
 *  \brief Used for YUV 422 semiplanar progressive frame format or interlaced
 *  frame format with fields merged.
 */
static st_DispDssBufInfo Yuv422SpFieldsMerged = {NULL, 0u};
/**
 *  \brief Used for the YUV 422 semiplanar interlaced frame format with fields
 *  in seperate planes.
 */
static st_DispDssBufInfo Yuv422SpInterlacedFieldsSep = {NULL, 0u};
/**
 *  \brief Used for BGR888 24-bit progressive frame format with fields merged.
 */
static st_DispDssBufInfo BGR24888FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for ABGR8888 32-bit progressive frame format with fields merged.
 */
static st_DispDssBufInfo ABGR328888FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for UYVY422 interleaved progressive frame format or interlaced
 *  frame format with fields merged. => 800x480 input
 */
static st_DispDssBufInfo Uyvy422FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for the UYVY422 interleaved interlaced frame format with fields
 *  in seperate planes.. => 800x480 input
 */
static st_DispDssBufInfo Uyvy422InterlacedFieldsSep = {NULL, 0u};
/**
 *  \brief Used for BGRA8888 32-bit progressive frame format with fields merged.
 */
static st_DispDssBufInfo BGRA328888FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for XBGR8888 32-bit progressive frame format with fields merged.
 */
static st_DispDssBufInfo XBGR248888FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for BGRX8888 32-bit progressive frame format with fields merged.
 */
static st_DispDssBufInfo BGRX248888FieldsMerged = {NULL, 0u};
/**
 *  \brief Used for BGR565 16-bit progressive frame format with fields merged.
 */
static st_DispDssBufInfo BGR16565FieldsMerged = {NULL, 0u};

static UInt32 glbTestCounter = 0U;
static UInt32 glbPassCounter = 0;
static UInt32 glbFailCounter = 0;

/**
 *  st_dispDssLoadBuf
 */
Int32 st_dispDssLoadBuf(st_DispDssUtObj            *utObj,
                        const st_DispDssLoadBufCfg *cfg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 bCnt;
    st_DispDssBufInfo *bufInfo = NULL;
    char fileNameString[100];
    UInt32           bytesRead;
    char             userInput;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                bufInfo = &Yuyv422InterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuyv422FieldsMerged;
            }
            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
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
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                bufInfo = &Yuv420SpInterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuv420SpFieldsMerged;
            }
            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
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
                bufInfo->bufAddr = (UInt8 *) BspUtils_memAlloc(
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
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                bufInfo = &Yuv422SpInterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuv422SpFieldsMerged;
            }
            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
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
                bufInfo->bufAddr = (UInt8 *) BspUtils_memAlloc(
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

        case FVID2_DF_BGR24_888:
            bufInfo = &BGR24888FieldsMerged;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->bgrBufAddr[bCnt] = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 3u)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
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
                    GT_0trace(utObj->traceMask, GT_ERR,
                              "Could not allocate buffer\r\n");
                    bufInfo->bufSize      = 0u;
                    bufInfo->totalBufSize = 0u;
                    GT_assert(utObj->traceMask, NULL != bufInfo->bufAddr);
                }
            }
            break;

        case FVID2_DF_ABGR32_8888:
            bufInfo = &ABGR328888FieldsMerged;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->abgrBufAddr[bCnt] = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 4u)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 4u);
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

        case FVID2_DF_YUV422I_UYVY:
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                bufInfo = &Uyvy422InterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Uyvy422FieldsMerged;
            }
            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->uyvyBufAddr[bCnt] = NULL;
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
        case FVID2_DF_BGRA32_8888:
            bufInfo = &BGRA328888FieldsMerged;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->bgraBufAddr[bCnt] = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 4u)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 4u);
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

        case FVID2_DF_XBGR24_8888:
            bufInfo = &XBGR248888FieldsMerged;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->xbgrBufAddr[bCnt] = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 4u)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 4u);
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

        case FVID2_DF_BGRX24_8888:
            bufInfo = &BGRX248888FieldsMerged;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->bgrxBufAddr[bCnt] = NULL;
                }
            }

            if (bufInfo->bufCfg.pitch < bufInfo->bufCfg.width * 4u)
            {
                GT_1trace(utObj->traceMask, GT_ERR,
                          "Invalid pitch: %d\r\n", bufInfo->bufCfg.pitch);
                GT_assert(utObj->traceMask,
                          bufInfo->bufCfg.pitch >= bufInfo->bufCfg.width * 4u);
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

        case FVID2_DF_BGR16_565_A8:
            bufInfo = &BGR16565FieldsMerged;

            memcpy(&bufInfo->bufCfg, cfg, sizeof (st_DispDssLoadBufCfg));
            if (NULL != bufInfo->bufAddr)
            {
                /* Free up the buffer */
                BspUtils_memFree(bufInfo->bufAddr, bufInfo->totalBufSize);

                bufInfo->bufAddr      = NULL;
                bufInfo->bufSize      = 0u;
                bufInfo->totalBufSize = 0u;
                for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
                {
                    bufInfo->bgr16565BufAddr[bCnt] = NULL;
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
                    (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height) +
                    (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height / 2U);
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
        for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
        {
            if (FVID2_SF_PROGRESSIVE == cfg->scanFmt)
            {
                bufInfo->yBufAddrEven[bCnt] =
                    (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));

                if (FVID2_DF_YUV422I_YUYV == cfg->dataFmt)
                {
                    bufInfo->yBufAddrEven[bCnt] =
                        (void *) (bufInfo->bufAddr +
                                  (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_BGR24_888 == cfg->dataFmt)
                {
                    bufInfo->bgrBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_ABGR32_8888 == cfg->dataFmt)
                {
                    bufInfo->abgrBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_YUV422I_UYVY == cfg->dataFmt)
                {
                    bufInfo->uyvyBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_BGRA32_8888 == cfg->dataFmt)
                {
                    bufInfo->bgraBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_XBGR24_8888 == cfg->dataFmt)
                {
                    bufInfo->xbgrBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_BGRX24_8888 == cfg->dataFmt)
                {
                    bufInfo->bgrxBufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                }
                else if (FVID2_DF_BGR16_565_A8 == cfg->dataFmt)
                {
                    bufInfo->bgr16565BufAddr[bCnt] =
                        (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));
                    bufInfo->yBufAddrOdd[bCnt] =
                        (void *) (((UInt32) (bufInfo->bgr16565BufAddr[bCnt])) +
                                  (bufInfo->bufCfg.pitch *
                                   bufInfo->bufCfg.height));
                }
                else if (FVID2_DF_YUV420SP_UV == cfg->dataFmt)
                {
                    bufInfo->yBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height * 3u) / 4u;
                    bufInfo->cBufAddrEven[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height);
                    bufInfo->cBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrOdd[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height);
                }

#if 0
                bufInfo->yBufAddrOdd[bCnt] =
                    ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                    + bufInfo->bufCfg.pitch;
                bufInfo->cBufAddrEven[bCnt] =
                    ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                    + (bufInfo->bufCfg.pitch * bufInfo->bufCfg.height);
                bufInfo->cBufAddrOdd[bCnt] =
                    ((UInt8 *) bufInfo->cBufAddrEven[bCnt])
                    + bufInfo->bufCfg.pitch;
#endif
            }
            else
            {
                bufInfo->yBufAddrEven[bCnt] =
                    (void *) (bufInfo->bufAddr + (bCnt * bufInfo->bufSize));

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
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height);
                    bufInfo->cBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrOdd[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height);
                }
                else
                {
                    bufInfo->yBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height * 3u) / 4u;
                    bufInfo->cBufAddrEven[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrEven[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height);
                    bufInfo->cBufAddrOdd[bCnt] =
                        ((UInt8 *) bufInfo->yBufAddrOdd[bCnt])
                        + (bufInfo->bufCfg.pitch *
                           bufInfo->bufCfg.height);
                }
            }
        }
        if (FVID2_SF_PROGRESSIVE == cfg->scanFmt)
        {
            /* Wait for the user to load the image */
            GT_5trace(utObj->traceMask, GT_INFO,
                      UT_NAME ": Load %d %s Progressive video frames of "
                      "size %dx%d to location: 0x%p\r\n",
                      bufInfo->bufCfg.numBuffers,
                      Fvid2_getDataFmtString(cfg->dataFmt),
                      bufInfo->bufCfg.width,
                      bufInfo->bufCfg.height,
                      bufInfo->bufAddr);
            /* Try Loading the file from SD card if present.
            * If file is not present ask user to load using scripting console
            */
            BspUtils_appGetFileName(fileNameString,
                                    sizeof (fileNameString),
                                    "display",
                                    bufInfo->bufCfg.dataFmt,
                                    bufInfo->bufCfg.width,
                                    bufInfo->bufCfg.height);
            if (BSP_SOK != BspUtils_appLoadFileFromSd(
                    fileNameString,
                    "/dss_input_files",
                    bufInfo->bufAddr,
                    bufInfo->totalBufSize,
                    &bytesRead))
            {
                Int32 tempRetVal;
                GT_0trace(BspAppTrace, GT_INFO,
                    "Loading file from SD card failed. \r\n"
                    "Press any key to load from scripting console\r\n");
                tempRetVal = BspUtils_uartGetChar(
                                &userInput, BSP_UTILS_UART_RX_DEFAULT_TIMEOUT);
                BspUtils_appPrintLoadRawCmd(
                    "display",
                    bufInfo->bufAddr,
                    bufInfo->bufCfg.dataFmt,
                    bufInfo->bufCfg.width,
                    bufInfo->bufCfg.height);

                if (tempRetVal == BSP_SOK)
                {
                    GT_0trace(BspAppTrace, GT_INFO,
                        "Enter any key after loading...\r\n");
                    BspUtils_uartGetChar(
                        &userInput, BSP_UTILS_UART_RX_WAIT_FOREVER);
                }
            }

        }
        else
        {
            /* Wait for the user to load the image */
            GT_5trace(utObj->traceMask, GT_INFO,
                      UT_NAME ": Load %d %s Interlaced video frames of "
                      "size %dx%d to location: 0x%p\r\n",
                      bufInfo->bufCfg.numBuffers,
                      Fvid2_getDataFmtString(cfg->dataFmt),
                      bufInfo->bufCfg.width,
                      bufInfo->bufCfg.height,
                      bufInfo->bufAddr);
        }
    }

    return (retVal);
}

Int32 st_dispDssGetBufCfgId(UInt32 dataFmt,
                            UInt32 *bufCfgId)
{
    Int32 retVal = FVID2_EFAIL;
    UInt32 cfgId;
    for (cfgId = 0;
        cfgId <
        (sizeof (gDispDssLoadBufCfg) / sizeof (st_DispDssLoadBufCfg));
        cfgId++)
    {
        if (dataFmt == gDispDssLoadBufCfg[cfgId].dataFmt)
        {
            *bufCfgId = cfgId;
            retVal = FVID2_SOK;
            break;
        }
    }
    return retVal;
}
/**
 *  st_dispDssFreeBuf
 */
Int32 st_dispDssFreeBuf(st_DispDssUtObj            *utObj,
                        const st_DispDssLoadBufCfg *cfg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 bCnt;
    st_DispDssBufInfo *bufInfo = NULL;

    switch (cfg->dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUYV422 Field Separated Buffer...\r\n");

                bufInfo = &Yuyv422InterlacedFieldsSep;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUYV422 Field Merged Buffer...\r\n");

                bufInfo = &Yuyv422FieldsMerged;
            }
            break;

        case FVID2_DF_YUV420SP_UV:
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV420SP Field Separated Buffer...\r\n");
                bufInfo = &Yuv420SpInterlacedFieldsSep;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV420SP Field Merged Buffer...\r\n");
                bufInfo = &Yuv420SpFieldsMerged;
            }
            break;

        case FVID2_DF_YUV422SP_UV:
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV422SP Field Separated Buffer...\r\n");
                bufInfo = &Yuv422SpInterlacedFieldsSep;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing YUV422SP Field Merged Buffer...\r\n");
                bufInfo = &Yuv422SpFieldsMerged;
            }
            break;

        case FVID2_DF_BGR24_888:
            GT_0trace(utObj->traceMask, GT_INFO,
                      "Freeing BGR24 Field Merged Buffer...\r\n");
            bufInfo = &BGR24888FieldsMerged;

            break;

        case FVID2_DF_ABGR32_8888:
            GT_0trace(utObj->traceMask, GT_INFO,
                      "Freeing ARGB32 Field Merged Buffer...\r\n");
            bufInfo = &ABGR328888FieldsMerged;

            break;

        case FVID2_DF_YUV422I_UYVY:
            if ((FVID2_SF_INTERLACED == cfg->scanFmt) &&
                (FALSE == cfg->fieldsMerged))
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing UYVY422 Field Separated Buffer...\r\n");

                bufInfo = &Uyvy422InterlacedFieldsSep;
            }
            else
            {
                GT_0trace(utObj->traceMask, GT_INFO,
                          "Freeing UYVY422 Field Merged Buffer...\r\n");

                bufInfo = &Uyvy422FieldsMerged;
            }
            break;

        case FVID2_DF_BGRA32_8888:
            GT_0trace(utObj->traceMask, GT_INFO,
                      "Freeing RGBA32 Field Merged Buffer...\r\n");
            bufInfo = &BGRA328888FieldsMerged;

            break;

        case FVID2_DF_XBGR24_8888:
            GT_0trace(utObj->traceMask, GT_INFO,
                      "Freeing RGBX24 Field Merged Buffer...\r\n");
            bufInfo = &XBGR248888FieldsMerged;

            break;

        case FVID2_DF_BGRX24_8888:
            GT_0trace(utObj->traceMask, GT_INFO,
                      "Freeing XRGB24 Field Merged Buffer...\r\n");
            bufInfo = &BGRX248888FieldsMerged;

            break;

        case FVID2_DF_BGR16_565_A8:
            GT_0trace(utObj->traceMask, GT_INFO,
                      "Freeing RGB16565 Field Merged Buffer...\r\n");
            bufInfo = &BGR16565FieldsMerged;

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
            for (bCnt = 0u; bCnt < ST_DISP_DSS_MAX_BUFFERS; bCnt++)
            {
                switch (cfg->dataFmt)
                {
                    case FVID2_DF_YUV422I_YUYV:
                        bufInfo->yBufAddrEven[bCnt] = NULL;
                        break;

                    case FVID2_DF_BGR24_888:
                        bufInfo->bgrBufAddr[bCnt] = NULL;
                        break;

                    case FVID2_DF_ABGR32_8888:
                        bufInfo->abgrBufAddr[bCnt] = NULL;
                        break;

                    case FVID2_DF_YUV422I_UYVY:
                        bufInfo->uyvyBufAddr[bCnt] = NULL;
                        break;

                    case FVID2_DF_BGRA32_8888:
                        bufInfo->bgraBufAddr[bCnt] = NULL;
                        break;
                    case FVID2_DF_XBGR24_8888:
                        bufInfo->xbgrBufAddr[bCnt] = NULL;
                        break;
                    case FVID2_DF_BGRX24_8888:
                        bufInfo->bgrxBufAddr[bCnt] = NULL;
                        break;
                    case FVID2_DF_BGR16_565:
                        bufInfo->bgr16565BufAddr[bCnt] = NULL;
                        break;
                }
            }
        }
    }

    return (retVal);
}

/**
 *  st_dispDssCheckHeapStat
 */
Int32 st_dispDssCheckHeapStat(const BspUtils_MemHeapStatus *heapStat,
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
                  UT_NAME,
                  (heapStat->freeSysHeapSize - curStat.freeSysHeapSize));
        retVal = BSP_EFAIL;
    }
    if (heapStat->freeBufHeapSize != curStat.freeBufHeapSize)
    {
        GT_2trace(traceMask, GT_INFO,
                  "%s: Warning: Memory leak (%d bytes) in Buffer Heap!!\r\n",
                  UT_NAME,
                  (heapStat->freeBufHeapSize - curStat.freeBufHeapSize));
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  st_dispDssGetBufInfo
 */
st_DispDssBufInfo *st_dispDssGetBufInfo(st_DispDssAppObj *appObj,
                                        UInt32            dataFmt,
                                        UInt32            scanFmt,
                                        UInt32            fieldsMerged,
                                        UInt32            pitch)
{
    st_DispDssBufInfo *bufInfo = NULL;

    switch (dataFmt)
    {
        case FVID2_DF_YUV422I_YUYV:
            if ((FVID2_SF_INTERLACED == scanFmt) && (FALSE == fieldsMerged))
            {
                bufInfo = &Yuyv422InterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuyv422FieldsMerged;
            }
            break;

        case FVID2_DF_YUV420SP_UV:
            if ((FVID2_SF_INTERLACED == scanFmt) && (FALSE == fieldsMerged))
            {
                bufInfo = &Yuv420SpInterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuv420SpFieldsMerged;
            }
            break;

        case FVID2_DF_YUV422SP_UV:
            if ((FVID2_SF_INTERLACED == scanFmt) && (FALSE == fieldsMerged))
            {
                bufInfo = &Yuv422SpInterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Yuv422SpFieldsMerged;
            }
            break;

        case FVID2_DF_BGR24_888:

            bufInfo = &BGR24888FieldsMerged;
            break;

        case FVID2_DF_ABGR32_8888:

            bufInfo = &ABGR328888FieldsMerged;
            break;

        case FVID2_DF_YUV422I_UYVY:
            if ((FVID2_SF_INTERLACED == scanFmt) && (FALSE == fieldsMerged))
            {
                bufInfo = &Uyvy422InterlacedFieldsSep;
            }
            else
            {
                bufInfo = &Uyvy422FieldsMerged;
            }
            break;

        case FVID2_DF_BGRA32_8888:

            bufInfo = &BGRA328888FieldsMerged;
            break;

        case FVID2_DF_XBGR24_8888:

            bufInfo = &XBGR248888FieldsMerged;
            break;

        case FVID2_DF_BGRX24_8888:

            bufInfo = &BGRX248888FieldsMerged;
            break;

        case FVID2_DF_BGR16_565:
        case FVID2_DF_BGR16_565_A8:
        case FVID2_DF_RGB16_565_A8:

            bufInfo = &BGR16565FieldsMerged;
            break;

        default:
            GT_1trace(appObj->traceMask, GT_ERR,
                      "Invalid format: %d\r\n", dataFmt);
            bufInfo = NULL;
            break;
    }

    return (bufInfo);
}

void st_printTestResult(const st_DispDssUtObj *utObj,
                        UInt32                 skipCount,
                        UInt32                 disableCount)
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

void st_logTestResult(const st_DispDssUtObj *utObj,
                      Int32                  testResult,
                      UInt32                 testCaseId,
                      char                  *testcaseInfo)
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

