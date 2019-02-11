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
 *  \file st_vpeConfig.h
 *
 *  \brief This file defines the common configurations like driver handle
 *  config, channel config etc...
 */

#ifndef _ST_VPE_CONFIG_H_
#define _ST_VPE_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_vpe.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Defined the following so that it is easy to understand a particular config */
#define USE_DEF_QLEN                    (ST_VPE_USE_DEF)
#define USE_DEF_LP_CNT                  (ST_VPE_USE_DEF)
#define USE_DEF_SS_CNT                  (ST_VPE_USE_DEF)
#define USE_DEF_OC_CNT                  (ST_VPE_USE_DEF)
#define USE_DEF_FSR                     (ST_VPE_USE_DEF)
#define TSKCTX_ENABLE                   (TRUE)
#define TSKCTX_DISABLE                  (FALSE)
#define TIMEST_ENABLE                   (TRUE)
#define TIMEST_DISABLE                  (FALSE)
#define PRF_ENABLE                      (TRUE)
#define PRF_DISABLE                     (FALSE)
#define ASYNCQ_ENABLE                   (TRUE)
#define ASYNCQ_DISABLE                  (FALSE)
#define FRAMEDROP_ENABLE                (TRUE)
#define FRAMEDROP_DISABLE               (FALSE)
#define DEF_FRAMEDROP_PATTERN           (0U)
#define TEST_ENABLE                     (TRUE)
#define TEST_DISABLE                    (FALSE)
#define PRINT_ENABLE                    (TRUE)
#define PRINT_DISABLE                   (FALSE)
#define FMD_ENABLE                      (TRUE)
#define FMD_DISABLE                     (FALSE)
#define LAZY_LOAD_ENABLE                (TRUE)
#define LAZY_LOAD_DISABLE               (FALSE)
#define DEI_BYPASS                      (TRUE)
#define DEI_ENABLE                      (FALSE)
#define DEI_TEMPINP_ENABLE              (TRUE)
#define DEI_TEMPINP_DISABLE             (FALSE)
#define DEI_TEMPINPCHR_ENABLE           (TRUE)
#define DEI_TEMPINPCHR_DISABLE          (FALSE)
#define DEI_SPATMAX_BYPASS              (TRUE)
#define DEI_SPATMAX_ENABLE              (FALSE)
#define DEI_TEMPMAX_BYPASS              (TRUE)
#define DEI_TEMPMAX_ENABLE              (FALSE)
#define SC_BYPASS                       (TRUE)
#define SC_ENABLE                       (FALSE)
#define SC_NONLINEAR_ENABLE             (TRUE)
#define SC_NONLINEAR_DISABLE            (FALSE)
#define SC_EDGEDETECT_ENABLE            (TRUE)
#define SC_EDGEDETECT_DISABLE           (FALSE)
#define SC_PEAKING_ENABLE               (TRUE)
#define SC_PEAKING_DISABLE              (FALSE)
#define SUBFRAME_ENABLE                 (TRUE)
#define SUBFRAME_DISABLE                (FALSE)
#define CRCCHECK_ENABLE                 (TRUE)
#define CRCCHECK_DISABLE                (FALSE)

#define VPE_MAX_HANDLE_CFG              ((sizeof (gStVpeHandleCfg)) / \
                                         (sizeof (st_VpeHandleCfg)))

#define VPE_MAX_CH_CFG                  ((sizeof (gStVpeChCfg)) / \
                                         (sizeof (st_VpeChCfg)))

#define DEF_NUM_SUBFRM                  (1u)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various load buffer configuration. */
static const st_VpeLoadBufCfg gVpeUtLoadBufCfg[] =
{
    /* width, height, pitch, dataFmt, scanFmt, fieldsMerged, numBuffers */
    {1920u, 1080u, 3840u, FVID2_DF_YUV422I_YUYV, FVID2_SF_PROGRESSIVE, 4u},
    {720u,  240u,  1440u, FVID2_DF_YUV422I_YUYV, FVID2_SF_INTERLACED,  4u},
    {1920u, 1080u, 1920u, FVID2_DF_YUV420SP_UV,  FVID2_SF_PROGRESSIVE, 4u},
    {720u,  240u,  720u,  FVID2_DF_YUV420SP_UV,  FVID2_SF_INTERLACED,  4u},
    {1920u, 1080u, 1920u, FVID2_DF_YUV422SP_UV,  FVID2_SF_PROGRESSIVE, 4u},
    {720u,  240u,  720u,  FVID2_DF_YUV422SP_UV,  FVID2_SF_INTERLACED,  4u}
};

/** \brief Defines the various handle configuration. */
static const st_VpeHandleCfg  gStVpeHandleCfg[] =
{
    /* handleCfgId,
     * chInQueueLength, isDeiFmdEnable,
     * loopCnt, startStopCnt, openCloseCnt,
     * frameSwitchRate, taskCtxEnable, timeStampEnable,
     * prfEnable, asyncQueEnable, frmDropEnable, frmDropPattern
     */
    /*
     * All parameters are default.
     */
    {
        ST_VPE_HCID_DEFAULT,
        USE_DEF_QLEN, FMD_DISABLE,
        USE_DEF_LP_CNT, USE_DEF_SS_CNT, USE_DEF_OC_CNT,
        USE_DEF_FSR, TSKCTX_ENABLE, TIMEST_DISABLE,
        PRF_ENABLE, ASYNCQ_DISABLE, FRAMEDROP_DISABLE, DEF_FRAMEDROP_PATTERN
    },
    /*
     * Different start/stop handle configuration.
     */
    {
        ST_VPE_HCID_START_STOP,
        USE_DEF_QLEN, FMD_DISABLE,
        LOOP_CNT_SS, START_STOP_CNT_SS, USE_DEF_OC_CNT,
        USE_DEF_FSR, TSKCTX_ENABLE, TIMEST_DISABLE,
        PRF_DISABLE, ASYNCQ_DISABLE, FRAMEDROP_DISABLE, DEF_FRAMEDROP_PATTERN
    },
    /*
     * Different open/close handle configuration.
     */
    {
        ST_VPE_HCID_OPEN_CLOSE,
        USE_DEF_QLEN, FMD_DISABLE,
        LOOP_CNT_OC, START_STOP_CNT_OC, OPEN_CLOSE_CNT_OC,
        USE_DEF_FSR, TSKCTX_ENABLE, TIMEST_DISABLE,
        PRF_DISABLE, ASYNCQ_DISABLE, FRAMEDROP_DISABLE, DEF_FRAMEDROP_PATTERN
    },
    /*
     * Misc configuration
     */
    {   /* ISR context enabled */
        ST_VPE_HCID_MISC_ISR_CTX,
        USE_DEF_QLEN, FMD_DISABLE,
        USE_DEF_LP_CNT, USE_DEF_SS_CNT, USE_DEF_OC_CNT,
        USE_DEF_FSR, TSKCTX_DISABLE, TIMEST_DISABLE,
        PRF_ENABLE, ASYNCQ_DISABLE, FRAMEDROP_DISABLE, DEF_FRAMEDROP_PATTERN
    },
    {   /* Timestamp enabled */
        ST_VPE_HCID_MISC_TIMESTAMP,
        USE_DEF_QLEN, FMD_DISABLE,
        LOOP_CNT_TIMESTAMP, USE_DEF_SS_CNT, USE_DEF_OC_CNT,
        USE_DEF_FSR, TSKCTX_ENABLE, TIMEST_ENABLE,
        PRF_DISABLE, ASYNCQ_DISABLE, FRAMEDROP_DISABLE, DEF_FRAMEDROP_PATTERN
    },
    {   /* Async Q enabled */
        ST_VPE_HCID_MISC_ASYNCQ,
        USE_DEF_QLEN, FMD_DISABLE,
        USE_DEF_LP_CNT, USE_DEF_SS_CNT, USE_DEF_OC_CNT,
        USE_DEF_FSR, TSKCTX_ENABLE, TIMEST_DISABLE,
        PRF_DISABLE, ASYNCQ_ENABLE, FRAMEDROP_DISABLE, DEF_FRAMEDROP_PATTERN
    },
    {   /* Frame drop feature */
        ST_VPE_HCID_MISC_FRAMEDROP_ALTERNATE,
        USE_DEF_QLEN, FMD_DISABLE,
        USE_DEF_LP_CNT, USE_DEF_SS_CNT, USE_DEF_OC_CNT,
        USE_DEF_FSR, TSKCTX_ENABLE, TIMEST_DISABLE,
        PRF_ENABLE, ASYNCQ_DISABLE, FRAMEDROP_ENABLE, 0xAAAAAAAAU
    },
};

/** \brief Defines the various channel configuration. */
static const st_VpeChCfg      gStVpeChCfg[] =
{
    /*
     * Different YUYV422I to YUYV422I configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 720P */
        ST_VPE_CCID_D1_YUYV422I_TO_720P_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        1280u, 720u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* WXGA to 1080P */
        ST_VPE_CCID_WXGA_YUYV422I_TO_1080P_YUYV422I_P_TO_P,
        1280u, 800u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1280u, 800u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* WXGA to 640x400 */
        ST_VPE_CCID_WXGA_YUYV422I_TO_640x400_YUYV422I_P_TO_P,
        1280u, 800u, FVID2_DF_YUV422I_YUYV,
        640u, 400u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1280u, 800u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* CIF to D1 */
        ST_VPE_CCID_CIF_YUYV422I_TO_D1_YUYV422I_P_TO_P,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 360u, 240u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* 1080P to 1080P with Sub-frame mode */
        ST_VPE_CCID_1080P_YUYV422I_TO_1080P_YUYV422I_P_TO_P_4SUBFRM,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1920u, 1080u
        },
        {
            SUBFRAME_ENABLE, (1080u / 4u), VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        4u
    },

    /*
     * Different YUYV422I to YUYV422I configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 720P */
        ST_VPE_CCID_D1_YUYV422I_TO_720P_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        1280u, 720u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV420SPUV to YUYV422I configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 720P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_720P_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1280u, 720u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* WXGA to 1080P */
        ST_VPE_CCID_WXGA_YUV420SPUV_TO_1080P_YUYV422I_P_TO_P,
        1280u, 800u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1280u, 800u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* WXGA to 640x400 */
        ST_VPE_CCID_WXGA_YUV420SPUV_TO_640x400_YUYV422I_P_TO_P,
        1280u, 800u, FVID2_DF_YUV420SP_UV,
        640u, 400u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1280u, 800u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* CIF to D1 */
        ST_VPE_CCID_CIF_YUV420SPUV_TO_D1_YUYV422I_P_TO_P,
        360u, 240u, FVID2_DF_YUV420SP_UV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 360u, 240u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV420SPUV to YUYV422I configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUV420SPUV_TO_CIF_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV420SP_UV,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUV420SPUV_TO_D1_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV420SP_UV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 720P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_720P_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV420SP_UV,
        1280u, 720u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV422SPUV to YUYV422I configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUV422SPUV_TO_CIF_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 720P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_720P_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        1280u, 720u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUYV422I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* WXGA to 1080P */
        ST_VPE_CCID_WXGA_YUV422SPUV_TO_1080P_YUYV422I_P_TO_P,
        1280u, 800u, FVID2_DF_YUV422SP_UV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1280u, 800u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* CIF to D1 */
        ST_VPE_CCID_CIF_YUV422SPUV_TO_D1_YUYV422I_P_TO_P,
        360u, 240u, FVID2_DF_YUV422SP_UV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 360u, 240u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV422SPUV to YUYV422I configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUV422SPUV_TO_CIF_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422SP_UV,
        360u, 240u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUV422SPUV_TO_D1_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422SP_UV,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 720P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_720P_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422SP_UV,
        1280u, 720u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUYV422I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422SP_UV,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to YUV420SPUV configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV420SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV420SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV420SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to YUV420SPUV configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV420SPUV_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV420SPUV_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV420SPUV_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to YUV422SPUV configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV422SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV422SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV422SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to YUV422SPUV configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV422SPUV_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV422SPUV_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV422SPUV_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to RGB888 configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_RGB888_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_RGB24_888,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_RGB888_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_RGB24_888,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_RGB888_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_RGB24_888,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* 1080P to 1080P */
        ST_VPE_CCID_1080P_YUYV422I_TO_1080P_RGB888_P_TO_P,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_RGB24_888,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1920u, 1080u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to RGB888 configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_RGB888_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_RGB24_888,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_RGB888_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_RGB24_888,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_RGB888_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_RGB24_888,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to YUV444I configuration with DEI OFF.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV444I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV444I,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV444I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV444I,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV444I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV444I,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* 1080P to 1080P */
        ST_VPE_CCID_1080P_YUYV422I_TO_1080P_YUV444I_P_TO_P,
        1920u, 1080u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV444I,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 1920u, 1080u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUYV422I to YUV444I configuration with DEI ON.
     */
    {
        /* D1 to CIF */
        ST_VPE_CCID_D1_YUYV422I_TO_CIF_YUV444I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        360u, 240u, FVID2_DF_YUV444I,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to D1 */
        ST_VPE_CCID_D1_YUYV422I_TO_D1_YUV444I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        720u, 480u, FVID2_DF_YUV444I,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_BYPASS, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUYV422I_TO_1080P_YUV444I_I_TO_P,
        720u, 240u, FVID2_DF_YUV422I_YUYV,
        1920u, 1080u, FVID2_DF_YUV444I,
        FVID2_SF_INTERLACED, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_ENABLE, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV420SPUV to YUV420SPUV configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV420SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV420SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV420SPUV to YUV422SPUV configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV422SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV420SPUV to RGB888 configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_RGB888_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_RGB24_888,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV420SPUV to YUV444I configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV420SPUV_TO_1080P_YUV444I_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV444I,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV422SPUV to YUV420SPUV configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV420SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV420SP_UV,
        1920u, 1080u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV422SPUV to YUV422SPUV configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV422SPUV_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        1920u, 1080u, FVID2_DF_YUV422SP_UV,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV422SPUV to RGB888 configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_RGB888_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        1920u, 1080u, FVID2_DF_RGB24_888,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },

    /*
     * Different YUV422SPUV to YUV444I configuration with DEI OFF.
     */
    {
        /* D1 to 1080P */
        ST_VPE_CCID_D1_YUV422SPUV_TO_1080P_YUV444I_P_TO_P,
        720u, 480u, FVID2_DF_YUV422SP_UV,
        1920u, 1080u, FVID2_DF_YUV444I,
        FVID2_SF_PROGRESSIVE, FVID2_SF_PROGRESSIVE,
        VPS_VPDMA_MT_NONTILEDMEM, VPS_VPDMA_MT_NONTILEDMEM,
        {
            DEI_BYPASS, VPS_DEI_EDIMODE_LUMA_CHROMA,
            DEI_TEMPINP_ENABLE, DEI_TEMPINPCHR_ENABLE,
            DEI_SPATMAX_ENABLE, DEI_TEMPMAX_ENABLE
        },
        {
            SC_ENABLE, SC_NONLINEAR_DISABLE,
            0u, SC_EDGEDETECT_DISABLE,
            SC_PEAKING_ENABLE, NULL
        },
        {
            0u, 0u, 720u, 480u
        },
        {
            SUBFRAME_DISABLE, 0u, VPS_INTR_END_OF_EVERY_NTH_LINE, NULL
        },
        DEF_NUM_SUBFRM
    },
};

#endif /* #ifndef _ST_VPE_CONFIG_H_ */
